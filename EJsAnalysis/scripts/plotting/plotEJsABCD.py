#!/usr/bin/env python

############################################################
# plotEJsABCD.py                                           # 
############################################################
# code for running ABCD method and making ABCD plots       #
# --> based off Duncan Rocha's ABCD package                #
############################################################
# Colleen Treado                                           #
############################################################

# TO RUN ON LOCAL MACHINE (NOT CERNVM) NEED TO RUN W/ PYTHON3 --> make compatible with both python versions...
# --> also need to source root directory: 'source /usr/local/Cellar/root/6.16.00/bin/thisroot.sh'
# --> also need to set EJ_PATH in EmergingJetsAnalysis repo when running outside athena: 'export EJ_PATH=$(pwd)'

import os, sys, time
import argparse
import ROOT
import math
from enum import Enum
import plotHelpers


### command line arguments ###
parser = argparse.ArgumentParser( description = "histogram plotter options",
                                      formatter_class = argparse.ArgumentDefaultsHelpFormatter )

# input / output parameters
parser.add_argument( "--inDir", dest = "inDir",
                         default = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-01_n1/EJsNtupToHistOutput/",
                         help = "Input directory containing all histogram root files." )
parser.add_argument( "--inSgnlDir", dest = "inSgnlDir", default = None,
                         help = "Input directory containing all signal histogram root files." )
parser.add_argument( "--inBkgdDir", dest = "inBkgdDir", default = None,
                         help = "Input directory containing all background histogram root files." )
parser.add_argument( "--inDataDir", dest = "inDataDir", default = None,
                         help = "Input directory containing all data histogram root files." )
parser.add_argument( "--outDir", dest = "outDir", default = "", help = "Output directory where plots will be stored. \
                         Default is 'plots' subdirectory of inDir parent directory" )
parser.add_argument( "--outSubdir", dest = "outSubdir", default = "abcd", help = "Output subdirectory for storing plots." )
parser.add_argument( "--outName", dest = "outName", default = "", help = "Output tag for augmenting plot names \
                         with sample information." )
parser.add_argument( "--outSgnlName", dest = "outSgnlName", default = "", help = "Output signal tag for augmenting plot names \
                         with signal sample information." )
parser.add_argument( "--outBkgdName", dest = "outBkgdName", default = "", help = "Output background tag for augmenting plot names \
                         with background sample information." )
parser.add_argument( "--outDataName", dest = "outDataName", default = "", help = "Output data tag for augmenting plot names \
                         with data sample information." )
parser.add_argument( "--sgnlType", dest = "sgnlType", default = "",
                         help = "Comma separated list of signal samples to plot. A list of tags common to all files \
                         in the sample to run over can be appended to the sample name with a colon ':'. \
                         Tags can be logically combined with '+' (and) and '=' (or). No tag-list will cause the program to search all \
                         signal files for the sample name itself. For example: \
                         '--sgnlType EJ_AB:ModelA-ModelB,EJ_A_1400.600:ModelA+1400=600' defines two samples: one named EJ_AB \
                         containing all files with 'ModelA' or 'ModelB' in the name and one named EJ_A_1400.600 \
                         containing all files with 'ModelA' and either '1400' or '600' in the name." )
parser.add_argument( "--bkgdType", dest = "bkgdType", default = "",
                         help = "Comma separated list of background samples to plots. See 'sgnlType' for details and usage." )
parser.add_argument( "--dataType", dest = "dataType", default = "",
                         help = "Comma separated list of data samples to plots. See 'sgnlType' for details and usage." )
parser.add_argument( "--histDir", dest = "histDir", default = "EJsHists",
                         help = "Input file sub-directory where histograms are stored. \
                         Default 'EJsHists' set by EJsNtupleToHists algorithm." )
parser.add_argument( "--histTree", dest = "histTree", default = "nominal",
                         help = "Nominal / systematics tree containing histograms to run over." )
parser.add_argument( "--histList", dest = "histList", default = "ABCD:darkPion=kshort=nomatch",
                         help = "Comma-separated list of histograms to plot. Tags can be logically combined \
                         with '+' (and) and '=' (or) and ':' (not). For example: '--histList jet+ntrk+dR:DV,DV+pid=ks,PV' \
                         will grab all histograms with names containg 'jet' and 'ntrk' and 'dR' but not 'DV', \
                         all histograms with names containing 'DV' and 'pid' or 'DV' and 'ks', \
                         and all histograms with names containing 'PV'." )
# output combined histograms
parser.add_argument( "--outDirCombined", dest = "outDirCombined", default = None,
                         help = "Output directory where combined histogram files are written. \
                         If no directory specified, combined histograms not written to disk." )
# running / plotting options
parser.add_argument( "--scaleData", dest = "scaleData", action = "store_true", default = False,
                         help = "Scale data to full Run2 (for use when running over subset." )
#parser.add_argument( "--metadataDir", dest = "metadataDir", default = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-01_full/metadata/",
parser.add_argument( "--metadataDir", dest = "metadataDir", default = "../v0_2020-01_full/metadata/",
                         help = "Directory of metadata event counts for scaling data." )
parser.add_argument( "--doABCD", dest = "doABCD", action = "store_true", default = False,
                         help = "Do ABCD calculations: count events and calculate efficiencies in ABCD regions; \
                         estimate background in A with standard ABCD method." )
parser.add_argument( "--doABCD_shift", dest = "doABCD_shift", action = "store_true", default = False,
                         help = "Do shifted ABCD calculations: count events and calculate efficiencies in (shifted) ABCD regions; \
                         estimate background in A with shifted ABCD method." )
parser.add_argument( "--drawABCD", dest = "drawABCD", action = "store_true", default = False, help = "Draw ABCD plane plots." )
parser.add_argument( "--drawNoCutABCD", dest = "drawNoCutABCD", action = "store_true", default = False,
                         help = "Draw ABCD plane plots without lines/regions defined by x/y cuts." )
parser.add_argument( "--xCutABCD", dest = "xCutABCD", type = float, default = 1385, help = "x-axis cut for defining ABCD regions." )
parser.add_argument( "--yCutABCD", dest = "yCutABCD", type = float, default = 2, help = "y-axis cut for defining ABCD regions." )
parser.add_argument( "--unblind", dest = "unblind", action = "store_true", default = False, help = "Unblind data." )
parser.add_argument( "--searchEnum", dest = "searchEnum", type = int, default = 1,
                         help = "Enumerator for sample types to plot against each other in ABCD search-region plane." )
parser.add_argument( "--validEnum", dest = "validEnum", type = int, default = 2,
                         help = "Enumerator for sample types to plot against each other in ABCD validation-region plane." )
parser.add_argument( "--legLenEnum", dest = "legLenEnum", type = int, default = 1,
                         help = "Enumerator for legend entry string length. Input must be integer." )
parser.add_argument( "--lxint", dest = "lxint", type = float, default = 0.008, help = "Legend x-length per entry string length." )
parser.add_argument( "--lyint", dest = "lyint", type = float, default = 0.030, help = "Legend y-length per entry." )
parser.add_argument( "--format", dest = "format", default = "pdf", help = "File format to save plots in." )

args = parser.parse_args()


## -- SET GLOBAL VARIABLES -- ##

# --> output directory
parentDir = args.inDir + "../"
outSubdir = time.strftime( "%Y.%m.%d_%Hh", time.localtime() )
if args.outSubdir:
    outSubdir = args.outSubdir + "_" + outSubdir  
outDir = args.outDir
if not outDir:
    outDir = os.path.join( parentDir, "plots" )
outDir = os.path.join( outDir, outSubdir )
if not os.path.exists( outDir ):
    os.makedirs( outDir )
    
# --> output plot file format
if not args.format.startswith('.'):
    args.format = '.' + args.format

# --> output text file with ABCD calculations
if args.doABCD or args.doABCD_shift:
    outTextDir = os.path.join( parentDir, "text_files", outSubdir )
    if not os.path.exists( outTextDir ):
        os.makedirs( outTextDir )
    outName = args.outName
    if outName:          outName += "."
    if args.outSgnlName: outName += args.outSgnlName + "."
    if args.outBkgdName: outName += args.outBkgdName + "."
    if args.outDataName: outName += args.outDataName + "."
    abcd_file = open( os.path.join( outTextDir, "abcd." + outName + "txt" ), "w+" ) # --> make file name configurable...

# --> enumerators
# --> --> sample types to plot against one another
class plotTypes( Enum ):
    SGNL_BKGD = 1 # sgnl vs bkgd
    BKGD_DATA = 2 # bkgd vs data
    SGNL_DATA = 3 # sgnl vs data
    ALL       = 4 # sgnl vs bkgd vs data
# --> --> legend string length
class legStrLen( Enum ):
    LONG    = 1
    LONG_SM = 2
    MID0    = 3
    MID0_SM = 4
    MID1    = 5
    MID1_SM = 6
    MID2    = 7
    MID2_SM = 8
    MID3    = 9
    SHORT   = 10



## --- RETRIEVE HISTOGRAM INFORMATION --- ##
def getSampleHistos():

    if not args.inSgnlDir: args.inSgnlDir = args.inDir
    if not args.inBkgdDir: args.inBkgdDir = args.inDir
    if not args.inDataDir: args.inDataDir = args.inDir

    histDir    = os.path.join( args.histDir, args.histTree )
    valid_dir  = os.path.join(      histDir,      "valid"  )
    search_dir = os.path.join(      histDir,      "search" )

    # get samples
    sampleNames, sampleTypes, sampleDicts, sampleFiles = plotHelpers.getSamples(
        args.inSgnlDir, args.inBkgdDir, args.inDataDir, args.sgnlType, args.bkgdType, args.dataType )

    # get histograms
    combOutDir = None
    if args.outDirCombined:
        combOutDir = os.path.join( parentDir, args.outDirCombined )
    metadataDir = None
    if args.metadataDir:
        metadataDir = os.path.join( parentDir, args.metadataDir )
    validHistNames,  validHists  = plotHelpers.getSampleHists( args.histList, valid_dir,  sampleFiles, sampleNames, sampleTypes,
                                                                   args.scaleData, metadataDir, combOutDir )
    searchHistNames, searchHists = plotHelpers.getSampleHists( args.histList, search_dir, sampleFiles, sampleNames, sampleTypes,
                                                                   args.scaleData, metadataDir, combOutDir )

    # get data-scale
    dataScale = 1
    for iS, stype in enumerate( sampleTypes ):
        if stype == plotHelpers.sampleType.DATA:
            data_initSumw = []
            for iF, sfile in enumerate( sampleFiles[iS] ):
                f = ROOT.TFile.Open( sfile, "READ" )
                f.cd( search_dir )
                for key in f.CurrentDirectory().GetListOfKeys():
                    if "MetaData_EventCount" in key.GetName():
                        h = f.CurrentDirectory().Get( key.GetName() )
                        data_initSumw.append( h.GetBinContent(3) )
            if args.scaleData:
                dataScale = plotHelpers.getDataScale( data_initSumw, plotHelpers.getDataNEvents( metadataDir ) )

    # return lists
    return sampleNames, sampleTypes, sampleDicts, validHistNames, validHists, searchHistNames, searchHists, dataScale


## --- PLOT HISTOGRAMS --- ##
def plotHistos( sampleNames, sampleTypes, sampleDicts, validHistNames, validHists, searchHistNames, searchHists, dataScale ):

    # rearrange hists from [sample][histName] to [histName][sample]
    newValidHists  = plotHelpers.getNewHists( sampleTypes, validHistNames,  validHists  )
    newSearchHists = plotHelpers.getNewHists( sampleTypes, searchHistNames, searchHists )

    # get metadata (should be the same for every region, so only need to do once)
    metaEventHists, MetaWeightHists = [], []
    for iHN, histName in enumerate( searchHistNames ):
        hists = newSearchHists[iHN]
        if "MetaData_EventCount" in histName:
            metaEventHists  = hists
        elif "MetaData_Weights" in histName:
            metaWeightHists = hists
    
    ## do ABCD calculations ##

    # may be able to do in single loop...
    
    # --> validation region
    for iName, name in enumerate( validHistNames ):
        hists = newValidHists[iName]
        if isinstance( hists[0], ROOT.TH2 ) and "ABCD" in name:
            # draw ABCD plots
            if args.drawABCD or args.drawNoCutABCD:
                plotABCD( hists, name, sampleTypes, sampleDicts, "valid", plotTypes( args.validEnum ) )
                
    # --> search region
    for iName, name in enumerate( searchHistNames ):
        hists = newSearchHists[iName]
        if isinstance( hists[0], ROOT.TH2 ) and "ABCD" in name:
            # do ABCD calculations
            if args.doABCD: # or args.doABCD_shift -- may need to do separately since working with multiple regions and shifted data...come back to this...
                # get ABCD region event counts
                nSearch, effSearch = countABCD( hists, metaEventHists, metaWeightHists, sampleTypes, "search", dataScale )
                # use standard ABCD method to estimate background in A
                estA_search, errA_search, zA_search = estimateABCD( nSearch )
                # get significance
                sb0_search, sb1_search, sb2_search, sb3_search = significanceABCD( nSearch, estA_search, sampleTypes )

                
            # write out ABCD info
            if args.doABCD: # or shift
                writeABCD( hists, name, sampleNames, sampleTypes, nSearch, effSearch, estA_search, errA_search, zA_search,
                               sb0_search, sb1_search, sb2_search, sb3_search )
            # draw ABCD plots
            if args.drawABCD or args.drawNoCutABCD:
                plotABCD( hists, name, sampleTypes, sampleDicts, "search", plotTypes( args.searchEnum ) )



## --- COUNT ABCD REGION EVENTS --- ##
def countABCD( hists, metaEventHists, metaWeightHists, sampleTypes, region, dataScale ):
    
    count, efficiency = [], []
    for iH, hist in enumerate( hists ):
        # get bins defining regions
        xbin = hist.GetXaxis().FindBin( args.xCutABCD )
        ybin = hist.GetYaxis().FindBin( args.yCutABCD )

        # count events in each region
        nA_iH = hist.Integral( xbin,     -1, ybin,     -1 )
        nB_iH = hist.Integral( xbin,     -1,   -1, ybin-1 )
        nC_iH = hist.Integral( -1,   xbin-1, ybin,     -1 )
        nD_iH = hist.Integral( -1,   xbin-1,   -1, ybin-1 )
        # --> get raw counts, too ??

        # calculate efficiencies in each region
        scale = 1
        if sampleTypes[iH] == plotHelpers.sampleType.DATA:
            scale = dataScale
        else:
            scale = metaWeightHists[iH].GetBinContent(1) * metaWeightHists[iH].GetBinContent(3) * \
              metaWeightHists[iH].GetBinContent(4) / metaEventHists[iH].GetBinContent(3)
        effA_iH = nA_iH / scale / metaEventHists[iH].GetBinContent(3)
        effB_iH = nB_iH / scale / metaEventHists[iH].GetBinContent(3)
        effC_iH = nC_iH / scale / metaEventHists[iH].GetBinContent(3)
        effD_iH = nD_iH / scale / metaEventHists[iH].GetBinContent(3)

        # blind data
        if sampleTypes[iH] == plotHelpers.sampleType.DATA  and region == "search" and not args.unblind:
            nA_iH   = -999
            nB_iH   = -999
            nC_iH   = -999
            effA_iH = -999
            effB_iH = -999
            effC_iH = -999

        count     .append( [ nA_iH,   nB_iH,   nC_iH,   nD_iH   ] )
        efficiency.append( [ effA_iH, effB_iH, effC_iH, effD_iH ] )

    return count, efficiency


## --- ESTIMATE EVENTS IN A WITH STANDARD ABCD METHOD --- ##
def estimateABCD( count ):

    A_estimate, A_errors, A_z = [], [], []
    for c in count:
        # do ABCD method to estimate number of events in A
        if c[3]: estA = c[1] * c[2] / c[3]
        else:    estA = c[1] * c[2] # what else can we do when c[3] = 0 ??
        
        # calculate statistical uncertainty
        estA_statErr = 0
        estA_systErr = 0
        estA_z = 0
        if c[0] and c[1] and c[2] and c[3]:
            estA_statErr = math.sqrt( estA )
            estA_systErr = estA * math.sqrt( abs(1./c[1]) + abs(1./c[2]) + abs(1./c[3]) )
            # --> dA = |A| * sqrt( (dB/B)^2 + (dC/C)^2 + (dD/D)^2 ); dN = sqrt(N)
            estA_z       = ( c[0] - estA ) / math.sqrt( pow(estA_statErr,2) + pow(estA_systErr,2) )
            # --> z = (M-mu) / SE

        # placeholders for blinded search region data
        if c[0] == -999 or c[1] == -999 or c[2] == -999 or c[3] == -999:
            estA         = -999
            estA_statErr = -999
            estA_systErr = -999
            estA_z       = -999

        A_estimate.append( estA )
        A_errors  .append( [ estA_statErr, estA_systErr ] )
        A_z       .append( estA_z )

    return A_estimate, A_errors, A_z


## --- ESTIMATE EVENTS IN A WITH SHIFTED ABCD METHOD --- ## --> DO TODAY !!!
# --> need to add scaled histos in EJsHistogramManager; will need to pass counts from search and validation regions...


## --- CALCULATE SIGNIFICANCE IN A --- ##
def significanceABCD( count, A_est, sampleTypes ):
    # pass boolean or string or enum saying whether to use MC background or data as b...
    # also may want way to decide to use standard ABCD or shifted ABCD estimate (or just pass in the one we want to use without caring what it is)

    b = 0
    for iS, stype in enumerate( sampleTypes ):
        if stype == plotHelpers.sampleType.BKGD:
            b      = A_est[iS]    # ABCD estimated value
            b_true = count[iS][0] # true value

    signif_v0, signif_v1, signif_v2, signif_v3 = [], [], [], []
    for iC, c in enumerate( count ):
        if sampleTypes[iC] == plotHelpers.sampleType.SGNL:
            s = c[0]
            signif_v0.append( s/b                  )
            signif_v1.append( s/(b + 0.1*b)        )
            signif_v2.append( s/(b + pow(0.1*b,2)) )
            signif_v3.append( s/math.sqrt(b)       )

    return signif_v0, signif_v1, signif_v2, signif_v3
        
    


## --- WRITE OUT ABCD INFO TO TEXT FILE --- ##
def writeABCD( hists, histName, sampleNames, sampleTypes, count, efficiency, A_est, A_err, A_z, sb0, sb1, sb2, sb3 ):
    # add "onlyA" argument; if true, only output values for A; make this argparse and update text file name accordingly
    # set number of decimal points? turn certain output on/off?
    ## --> consider using histName to write out more meaningful string (i.e. "n bare DVs vs N-jet Ht"), removing "ABCD_"...
    abcd_file.write( "------------------------------------------------------- \n" )
    abcd_file.write( "ABCD HISTOGRAM: " + histName + " --> \n" )
    # print x/y cuts
    abcd_file.write( "\n" )

    isig = 0
    abcd_string = [ "A", "B", "C", "D" ]
    for iH, hist in enumerate( hists ):
        # skip data for now...
        #if sampleTypes[iH] == plotHelpers.sampleType.DATA:
        #    continue
        
        abcd_file.write( "SAMPLE: " + sampleNames[iH] + "\n" ) # add sample type ??
        
        abcd_file.write( "########## ABCD counts ##################### \n" )
        for i in range(len(abcd_string)):
            abcd_file.write( "n events in " + abcd_string[i] + ": " + str(count[iH][i]) + "\n" )
        # --> add raw (unweighted) yields ?? -->
        # --> --> print "Raw / Weighted Yield in A:", nAi, nAi / ( xsec[iH] * genFiltEff[iH] * lumi[iH] / initSumw[iH] )
        
        abcd_file.write( "########## ABCD efficiencies ############### \n" )
        for i in range(len(abcd_string)):
            abcd_file.write( "efficiency in " + abcd_string[i] + ": " + str(efficiency[iH][i]) + "\n" )
            
        abcd_file.write( "########## ABCD method ##################### \n" )
        a_err = math.sqrt(abs(count[iH][0]))
        if count[iH][0] == -999: a_err = -999
        abcd_file.write( "Region A estimate: " + str(A_est[iH]) + " +- " +
                             str(A_err[iH][0]) + " (stat) +- " + str(A_err[iH][1]) + " (syst) \n" )
        abcd_file.write( "True value: " + str(count[iH][0]) + " +- " + str(a_err) + "\n" )
        abcd_file.write( "Standardized difference: " + str(A_z[iH]) + "\n" )

        # scaled ABCD estimates

        # significances
        # --> add "expected signal (s), expected background (b) in A"
        if sampleTypes[iH] == plotHelpers.sampleType.SGNL:
            abcd_file.write( "########## ABCD significances ########## \n" )
            abcd_file.write( "s/b: "               + str(sb0[isig]) + "\n" )
            abcd_file.write( "s/(b + 0.1*b): "     + str(sb1[isig]) + "\n" )
            abcd_file.write( "s/(b + (0.1*b)^2): " + str(sb2[isig]) + "\n" )
            abcd_file.write( "s/sqrt(b): "         + str(sb3[isig]) + "\n" )
            isig += 1

        abcd_file.write( "\n" )
        
    abcd_file.write( "\n" )

    isig = 0
    abcd_file.write( "SIGNAL EFFICIENCY AND S/B: \n" )
    for iS, stype in enumerate( sampleTypes ):
        if stype == plotHelpers.sampleType.SGNL:
            abcd_file.write( sampleNames[iS] + ": " + str(efficiency[iS][0]) + " | " + str(sb0[isig]) + "\n" )
            isig += 1
    abcd_file.write( "\n" )
    abcd_file.write( "BACKGROUND REJECTION: \n" )
    for iS, stype in enumerate( sampleTypes ):
        if stype == plotHelpers.sampleType.BKGD:
            abcd_file.write( sampleNames[iS] + ": " +str(1-efficiency[iS][0]) + "\n" ) # should we estimated value of A instead of true value? YES! need to calculate efficiency of expected value (and return and pass in here) when doing estimate above...
        # add data ...
    abcd_file.write( "\n" )

                


## --- DRAW ABCD PLOTS --- ##
def plotABCD( hists, histName, sampleTypes, sampleDicts, region, plotType ):

    if histName.startswith('ABCD'):
        histName = '_'.join( histName.split('_')[1:] )

    # build list of booleans to plot samples of desired type
    doPlotTypes = []
    for stype in sampleTypes:
        # only plot samples specified in plotType
        doPlotType = False
        for p in str(plotType).split('.')[-1].split('_'):
            if stype == getattr( plotHelpers.sampleType, p ):
                doPlotType = True
        doPlotTypes.append( doPlotType )
        
    # set canvas
    c = ROOT.TCanvas( histName, histName ) # 1100,800 ??

    # set legend
    l = plotHelpers.configLeg( sampleTypes, sampleDicts, legStrLen( args.legLenEnum ).value, args.lxint, args.lyint, doPlotTypes )

    ROOT.gPad.SetTicks(1,1)
    ROOT.gStyle.SetOptStat(0)

    # need to draw something to generate pad
    htemp = hists[0]
    htemp.Draw("col2")
    htemp.SetTitle( "ABCD Plane" )

    # draw contour plots
    xtitle = ytitle = ""
    for iH, hist in enumerate( hists ):

        # skip plots not specified in plotType
        if not doPlotTypes[iH]: continue                
                
        # blind data
        if sampleTypes[iH] == plotHelpers.sampleType.DATA  and region == "search" and not args.unblind:
            continue
        
        # draw palette
        texec = sampleDicts[iH]["palette"]
        texec.Draw()

        ## set max scale
        #hist.SetMaximum( plotHelpers.getMaxBinContent( hist ) * 1.4 )

        # set line / contour attributes
        hist.SetLineColor( sampleDicts[iH]["lcolor"] )
        hist.SetLineStyle( sampleDicts[iH]["lstyle"] )
        hist.SetLineWidth(3)
        hist.SetContour(10)

        # draw histogram
        hist.DrawNormalized( "cont0 same" ) # surface colors
        hist.DrawNormalized( "cont1 same" ) # line styles

        # get axis titles
        xtitle = hist.GetXaxis().GetTitle()
        ytitle = hist.GetYaxis().GetTitle()

        # add to legend
        l.AddEntry( hist, plotHelpers.setLegStr( sampleTypes[iH], sampleDicts[iH], legStrLen( args.legLenEnum ).value ) ) \
          .SetTextColor( sampleDicts[iH]["lcolor"] )

    # return palette to default
    plotHelpers.texec_default().Draw()

    # draw legend
    l.Draw()

    # set axes
    htemp.GetXaxis().SetTitle( xtitle )
    htemp.GetYaxis().SetTitle( ytitle )
    htemp.GetXaxis().SetTitleSize( 0.03 )
    htemp.GetYaxis().SetTitleSize( 0.03 )
    htemp.GetXaxis().SetTitleOffset( 1.4 )

    # draw ABCD cut regions
    p = ROOT.TPad( "p", "p", 0., 0., 1., 1. )
    p.SetFillStyle(0)
    p.Draw()
    p.cd()
    # --> get bins where region cuts applied and draw lines
    if not args.drawNoCutABCD:
        nxbin = hist.GetNbinsX()
        nybin = hist.GetNbinsY()
        xbin  = hist.GetXaxis().FindBin( args.xCutABCD )
        ybin  = hist.GetYaxis().FindBin( args.yCutABCD )
        xcut  = hist.GetXaxis().GetBinLowEdge( xbin ) # --> cut at low edge of x-bin containing input x-cut
        ycut  = hist.GetYaxis().GetBinLowEdge( ybin ) # --> cut at low edge of y-bin containing input y-cut
        edge  = 0.1
        width = 1. - 2*edge
        xloc  = edge + width * (xbin-1) / nxbin
        yloc  = edge + width * (ybin-1) / nybin
        linex = ROOT.TLine( xloc, edge, xloc, edge + width )
        linex.SetLineColor(ROOT.kRed)
        linex.SetLineWidth(4)
        linex.Draw()
        liney = ROOT.TLine( edge, yloc, edge + width, yloc )
        liney.SetLineColor(ROOT.kRed)
        liney.SetLineWidth(4)
        liney.Draw()
        # add ABCD labels --> change positions?
        xlo = ( edge + xloc  ) / 2
        ylo = ( edge + yloc  ) / 2
        xhi = ( width + xloc ) / 2
        yhi = ( width + yloc ) / 2
        ttxtA = ROOT.TText( xhi, yhi, "A" )
        ttxtB = ROOT.TText( xhi, ylo, "B" )
        ttxtC = ROOT.TText( xlo, yhi, "C" )
        ttxtD = ROOT.TText( xlo, ylo, "D" )
        ttxtA.SetTextColor(ROOT.kRed)
        ttxtB.SetTextColor(ROOT.kRed)
        ttxtC.SetTextColor(ROOT.kRed)
        ttxtD.SetTextColor(ROOT.kRed)
        ttxtA.Draw()
        ttxtB.Draw()
        ttxtC.Draw()
        ttxtD.Draw()
    # add text --> CONFIGURE; add details of search/validation region; optimize box and text size, attributes; etc.
    tp = ROOT.TPaveText( 0.13, 0.80, 0.25, 0.87 )
    if   ( region == "search" ):
        tp.AddText( "SEARCH REGION" )
    elif ( region == "valid" ):
        tp.AddText( "VALIDATION REGION" )
    tp.Draw()

    # print plot
    # --> set output plot name
    outName = args.outName
    if outName:
        outName += "."
    if args.outSgnlName and "sgnl" in str(plotType).split('.')[-1].lower():
        outName += args.outSgnlName + "."
    if args.outBkgdName and "bkgd" in str(plotType).split('.')[-1].lower():
        outName += args.outBkgdName + "."
    if args.outDataName and "data" in str(plotType).split('.')[-1].lower():
        outName += args.outDataName + "."
    outName = str(plotType).split('.')[-1].lower() + "." + outName + region
    cname = "abcd." + histName + "." + outName
    # --> set output subdirectory
    coutDir = os.path.join( outDir, outName )
    if not os.path.exists( coutDir ):
        os.makedirs( coutDir )
    # --> save
    c.SaveAs( os.path.join( coutDir, cname + args.format ) )

    # close canvas
    c.Update()
    c.Clear()
    c.Close()
    del c




   
   



### --- RUN PROGRAM --- ###
if __name__ == "__main__":
    sampleNames, sampleTypes, sampleDicts, validHistNames, validHists, searchHistNames, searchHists, dataScale = getSampleHistos()
    plotHistos( sampleNames, sampleTypes, sampleDicts, validHistNames, validHists, searchHistNames, searchHists, dataScale )
    abcd_file.close()
