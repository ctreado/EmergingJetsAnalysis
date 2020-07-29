#!/usr/bin/env python

##################################################################
# plotEJsHistograms.py                                           # 
##################################################################
# code for combining, stacking, and plotting histograms          #
# produced from EJsNtupleToHists alg / EJsHistogramManager class #
# -- based on scripts from BMinusLChargino analysis              #
##################################################################
# Colleen Treado                                                 #
##################################################################

# TO RUN ON LOCAL MACHINE (NOT CERNVM) NEED TO RUN W/ PYTHON3 --> make compatible with both python versions...
# --> also need to source root directory: 'source /usr/local/Cellar/root/6.16.00/bin/thisroot.sh'
# --> also need to set EJ_PATH in EmergingJetsAnalysis repo when running outside athena: 'export EJ_PATH=$(pwd)'

import os, sys, time
import argparse
import ROOT
from enum import Enum
import re
import plotHelpers

### command line arguments ###
parser = argparse.ArgumentParser( description = "histogram plotter options",
                                      formatter_class = argparse.ArgumentDefaultsHelpFormatter )

# input / output arguments
parser.add_argument( "--inDir", dest = "inDir", default = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-01_n1/EJsNtupToHistOutput/",
                         help = "Input directory containing all histogram root files." )
parser.add_argument( "--inSgnlDir", dest = "inSgnlDir", default = None,
                         help = "Input directory containing all signal histogram root files." )
parser.add_argument( "--inBkgdDir", dest = "inBkgdDir", default = None,
                         help = "Input directory containing all background histogram root files." )
parser.add_argument( "--inDataDir", dest = "inDataDir", default = None,
                         help = "Input directory containing all data histogram root files." )
parser.add_argument( "--regionDir", dest = "regionDir", default = "all",
                         help = "ROOT file TDirectory of region-specific histograms to plot." )
parser.add_argument( "--outDir", dest = "outDir", default = "", help = "Output directory where plots will be stored. \
                         Default is 'plots' subdirectory of inDir parent directory" )
parser.add_argument( "--outSubdir", dest = "outSubdir", default = "", help = "Output subdirectory for storing plots." )
parser.add_argument( "--outName", dest = "outName", default = "", help = "Output tag for augmenting plot names \
                         with sample information." )
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
parser.add_argument( "--histTitle", dest = "histTitle", default = "", help = "Histogram / plot title." )
parser.add_argument( "--histList", dest = "histList", default = "",
                         help = "Comma-separated list of histograms to plot. Tags can be logically combined \
                         with '+' (and) and '=' (or) and ':' (not). For example: '--histList jet+ntrk+dR:DV,DV+pid=ks,PV' \
                         will grab all histograms with names containg 'jet' and 'ntrk' and 'dR' but not 'DV', \
                         all histograms with names containing 'DV' and 'pid' or 'DV' and 'ks', \
                         and all histograms with names containing 'PV'." )
parser.add_argument( "--histVars", dest = "histVars", default = "",
                         help = "Comma-separated list of variable histogram types to plot on top of each other. \
                         The histograms corresponding to these variables should all contain the same base name to compare \
                         parameters for different criteria (i.e. vertex positions for truth-matched vs un-matched vertices)." )
parser.add_argument( "--sbdVars", dest = "sbdVars", default = "",
                         help = "Comma-separated list of variable signal, background, and data histogram types to plot against each other. \
                         The histograms corresponding to these variables should all contain the same base name to compare \
                         parameters for different criteria (i.e. vertex positions for truth-matched vs un-matched vertices) \
                         across different samples. Histogram types must be entered in signal-background-data order. \
                         To omit given sample type, leave blank space. Colons can be used to submit multiple cases. \
                         For example: '--sbdVars 2trkDV,,3trkDV:darkPionDV,nomatchDV' will plot 2-track signal DVs \
                         vs 3-track data DVs and dark pion signal DVs vs unmatched background DVs." )
parser.add_argument( "--varEnum", dest = "varEnum", type = int, default = 5,
                         help = "Enumerator for variable histogram type (i.e. DV, DV_NTRK). Input must be integer." )
parser.add_argument( "--baseDV", dest = "baseDV", default = "bare", help = "Base DV type." )
# output combined histograms
parser.add_argument( "--outDirCombined", dest = "outDirCombined", default = None,
                         help = "Output directory where combined histogram files are written. \
                         If no directory specified, combined histograms not written to disk." )
# running / plotting options
parser.add_argument( "--scaleData", dest = "scaleData", action = "store_true", default = False,
                         help = "Scale data to full Run2 (for use when running over subset." )
parser.add_argument( "--metadataDir", dest = "metadataDir", default = "../v0_2020-01_full/metadata/",
                         help = "Directory of metadata event counts for scaling data." )
parser.add_argument( "--draw1D", dest = "draw1D", action = "store_true", default = False, help = "Draw 1D stack plots." )
parser.add_argument( "--draw2D", dest = "draw2D", action = "store_true", default = False, help = "Draw individual 2D plots." )
parser.add_argument( "--drawMulti1D", dest = "drawMulti1D", action = "store_true", default = False,
                         help = "Draw 1D multivariate stack plots over multiple variables." )
parser.add_argument( "--drawSOverB", dest = "drawSOverB", action = "store_true", default = False, help = "Draw S/B plots." )
parser.add_argument( "--drawOpt1D", dest = "drawOpt1D", default = "nostack hist", help = "Draw option(s) for 1D stack plots." )
parser.add_argument( "--drawOpt2D", dest = "drawOpt2D", default = "colz", help = "Draw option(s) for 2D plots." )
parser.add_argument( "--drawOptMulti1D", dest = "drawOptMulti1D", default = "nostack hist",
                         help = "Draw option(s) for 1D multivariate stack plots." )
parser.add_argument( "--doMultiSmpl", dest = "doMultiSmpl", action = "store_true", default = False,
                         help = "Plot histograms from different samples against each other." )
parser.add_argument( "--doProfileX", dest = "doProfileX", action = "store_true", default = False, help = "Project 2d histogram into profile along x-axis." )
parser.add_argument( "--doProfileY", dest = "doProfileY", action = "store_true", default = False, help = "Project 2d histogram into profile along y-axis." )
parser.add_argument( "--doTruthSvB", dest = "doTruthSvB", action = "store_true", default = False,
                         help = "Do truth-matched signal vs background plots (for purposes of default legend, out-name strings)." )
parser.add_argument( "--legLenEnum", dest = "legLenEnum", type = int, default = 1,
                         help = "Enumerator for legend entry string length. Input must be integer." )
parser.add_argument( "--lxint", dest = "lxint", type = float, default = 0.008, help = "Legend x-length per entry string length." )
parser.add_argument( "--lyint", dest = "lyint", type = float, default = 0.030, help = "Legend y-length per entry." )
parser.add_argument( "--lxl", dest = "lxl", type = float, default = 0.600, help = "Legend left x-pos (override for multivariate plots)." )
parser.add_argument( "--format", dest = "format", default = "pdf", help = "File format to save plots in." )
parser.add_argument( "--lstyleEnum", dest = "lstyleEnum", type = int, default = 1,
                         help = "Enumerator for changing default line colors and styles based on types of signal points being \
                         plotted against one another. The default (ALL) sets the base color by model and the line style \
                         by mediator mass and varies the lifetime color around the base color. MOD sets the base color by \
                         lifetime and keeps the colors the same between models, and CTAU varies the base color by model and \
                         keeps the colors the same across all lifetimes." )
parser.add_argument( "--fillBkgd", dest = "fillBkgd", action = "store_true", default = False, help = "Fill in background." )
# --> add argument to override sampleDict colors -- just grab colors from plotHelpers instead; change legend to print strings in black in this case

args = parser.parse_args()


# add ratio plots (for calculating efficiencies)



## --- SET GLOBAL VARIABLES --- ##

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
    
# --> output file format
if not args.format.startswith('.'):
    args.format = '.' + args.format
    
# --> sample type output subdirectory
typeNames = []
if args.sgnlType: typeNames.append( "sgnl" )
if args.bkgdType: typeNames.append( "bkgd" )
if args.dataType: typeNames.append( "data" )
tname = ""
for typeName in typeNames:
    tname += typeName + "_"
tname = tname[:-1]

# --> enumerators
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
    MID4    = 10
    SHORT   = 11
class varType( Enum ):
    DV      = 1
    DV_NTRK = 2
    JET     = 3
    TRK     = 4
    NONE    = 5
class lineStyleType( Enum ):
    ALL  = 1
    CTAU = 2
    XDM  = 3
    MOOD = 4
    MIX  = 5


### SKIP NORM FOR CUTFLOWS AND/OR EFFICIENCIES ?? ###
### AVERAGE EFFICIENCY HISTS WHEN COMBINING (divide by number of files) ###


## --- RETRIEVE HISTOGRAM INFORMATION --- ##
def getSampleHistos():
    
    if not args.inSgnlDir: args.inSgnlDir = args.inDir
    if not args.inBkgdDir: args.inBkgdDir = args.inDir
    if not args.inDataDir: args.inDataDir = args.inDir

    histDir    = os.path.join( args.histDir, args.histTree  )
    region_dir = os.path.join(      histDir, args.regionDir )

    # get samples
    sampleNames, sampleTypes, sampleDicts, sampleFiles = plotHelpers.getSamples(
        args.inSgnlDir, args.inBkgdDir, args.inDataDir, args.sgnlType, args.bkgdType, args.dataType, lineStyleType( args.lstyleEnum ).value )

    # get histograms
    combOutDir = None
    if args.outDirCombined:
        combOutDir = os.path.join( parentDir, args.outDirCombined )
    if args.metadataDir:
        metadataDir = os.path.join( parentDir, args.metadataDir )
    histNames, hists = plotHelpers.getSampleHists( args.histList, region_dir, sampleFiles, sampleNames, sampleTypes,
                                                       args.scaleData, metadataDir, combOutDir )

    ## set global metadata weights for samples (for scaling)
    #sampleWeights.append( getMetaDataWeights( getFileList( args.in*Dir, *Type.split('+') ) ) ) # for each sample type
    #global xsec, kfactor, genFiltEff, lumi
    #xsec, kfactor, genFiltEff, lumi = [], [], [], []
    #for weight in sampleWeights:
    #     xsec       .append( weight[0] )
    #     kfactor    .append( weight[1] )
    #     genFiltEff .append( weight[2] )
    #     lumi       .append( weight[3] )

    ## get lumi scale from getHists: lumiScales.append( lumiScale )
    ## set global lumi-scales for scaling data subsets
    #global luminosityScale
    #luminosityScale = lumiScales
    ## set global metadata event counts for samples
    #global nInitEvents, nSelEvents, initSumw, selSumw, initSumw2, selSumw2
    #nInitEvents, nSelEvents, initSumw, selSumw, initSumw2, selSumw2 = [], [], [], [], [], []
    #for iHL, histList in enumerate( hists ):
    #    for iH, hist in enumerate( histList ):
    #        if "MetaData_EventCount" in hist.GetName():
    #            nInitEvents .append( hist.GetBinContent(1) )
    #            nSelEvents  .append( hist.GetBinContent(2) )
    #            initSumw    .append( hist.GetBinContent(3) )
    #            selSumw     .append( hist.GetBinContent(4) )
    #            initSumw2   .append( hist.GetBinContent(5) )
    #            selSumw2    .append( hist.GetBinContent(6) )

    # return lists
    return sampleNames, sampleTypes, sampleDicts, histNames, hists



## --- PLOT HISTOGRAMS --- ##
def plotHistos( sampleNames, sampleTypes, sampleDicts, histNames, hists ):
    
    # rearrange hists from [sample][histName] to [histName][sample]
    newHists = plotHelpers.getNewHists( sampleTypes, histNames, hists )

    # rearrange hists from [sample][histName] to [baseName][sample/histVar] (for desired subset)
    varHists, baseNames = plotHelpers.getVarHists( sampleTypes, histNames, hists, args.histVars )

    # --> plot same histos from different samples against each other
    for iName, name in enumerate( histNames ):
        hists = newHists[iName]

        # skip metadata hists (may need to get at some point for something...)
        if "MetaData" in name: continue
        
        # draw 1D stack plots (multiple samples per plot)
        if args.draw1D:
            plot1D(     hists, name, sampleNames, sampleTypes, sampleDicts )
            if not isinstance( hists[0], ROOT.TH2 ):
                if "eff" not in name.lower() and "accept" not in name.lower() or "cutflow" in name.lower():
                    plot1D( hists, name, sampleNames, sampleTypes, sampleDicts, True        ) # log-y
                else:
                    plot1D( hists, name, sampleNames, sampleTypes, sampleDicts, False, True ) # log-x
            # do s/b plots 
            if args.drawSOverB:
                plot1D(     hists, name, sampleNames, sampleTypes, sampleDicts, False, False, True )
                if not isinstance( hists[0], ROOT.TH2 ):
                    if "eff" not in name.lower() and "accept" not in name.lower() or "cutflow" in name.lower():
                        plot1D( hists, name, sampleNames, sampleTypes, sampleDicts, True,  False, True ) # log-y
                    else:
                        plot1D( hists, name, sampleNames, sampleTypes, sampleDicts, False, True,  True ) # log-x

        # draw 2D plots (one histo per plot) -- add handling of 2d projections (grab 3d histos and make projections, if applicable)
        if args.draw2D:
            if isinstance( hists[0], ROOT.TH2 ) and not isinstance( hists[0], ROOT.TH3 ):
                for iH, hist in enumerate( hists ):
                    plot2D( hist, name, sampleNames[iH], sampleTypes[iH], sampleDicts[iH] )

                    
    # --> plot different histos from same or different samples against each other
    for iBase, base in enumerate( baseNames ):
        hists = varHists[iBase]

        if len(hists) <= 0: continue

        if args.drawMulti1D:
            #if isinstance( hists[0], ROOT.TH1 ) and not isinstance( hists[0], ROOT.TH2 ) and not isinstance( hists[0], ROOT.TH3 ):
            # draw 1D multi-variate stack plots from SAME samples (multiple histos, single samples per plot)
            if not args.doMultiSmpl:
                for iS, sample in enumerate( sampleNames ):
                    hb = iS    * len( args.histVars.split(',') )
                    he = (iS+1)* len( args.histVars.split(',') )
                    plotMulti1D( hists[hb:he], base, sample, sampleTypes[iS], sampleDicts[iS] )
                    if not isinstance( hists[0], ROOT.TH2 ):
                        if "eff" not in name.lower() and "accept" not in name.lower():
                            plotMulti1D( hists[hb:he], base, sample, sampleTypes[iS], sampleDicts[iS], True        ) # log-y
                        else:
                            plotMulti1D( hists[hb:he], base, sample, sampleTypes[iS], sampleDicts[iS], False, True ) # log-x
            # draw 1D multi-variate stack plots from DIFFERENT samples (multiple histos, multiple samples per plot)
            elif args.doMultiSmpl:
                for iSBD, sbd in enumerate( args.sbdVars.split(':') ):
                    htitle = args.histTitle.split(':')[iSBD]
                    # --> need to update plotMultiSmpl1D to handle profile plots; for now, just exclude 2d/3d histos
                    if isinstance( hists[0], ROOT.TH1 ) and not isinstance( hists[0], ROOT.TH2 ) and not isinstance( hists[0], ROOT.TH3 ):
                        plotMultiSmpl1D( hists, base, sampleTypes, sampleDicts, sbd, htitle )
                        plotMultiSmpl1D( hists, base, sampleTypes, sampleDicts, sbd, htitle, True ) # log-y
                        # do s/b plots --> EVENTUALLY WANT TO CHANGE TO GENERAL 'doRatio' WITH CONFIGURABLE ENUM FOR RATIO TYPE AND 
                        if args.drawSOverB:
                            #if hists[0].GetName().split('_')[-1] == "n" or "count" in base or "cut" in base:
                            plotMultiSmpl1D( hists, base, sampleTypes, sampleDicts, sbd, htitle, False, True )
                            plotMultiSmpl1D( hists, base, sampleTypes, sampleDicts, sbd, htitle, True,  True ) # log-y
                        # --> eventually want to add "doRatio" option to other plotting functions...
                


## --- DRAW 1D STACK PLOTS --- ##
def plot1D( hists, histName, sampleNames, sampleTypes, sampleDicts, doLogy = False, doLogx = False, doSOverB = False ):
    
    iBkgd = -1
    for iS, stype in enumerate( sampleTypes ):
        if stype == plotHelpers.sampleType.BKGD:
            iBkgd = iS
            
    # set canvas
    c = ROOT.TCanvas( histName )
    # set stack
    hs = ROOT.THStack( histName, "" )
    # set legend
    xlover = None
    ylint  = args.lyint
    if doSOverB:
        xlover  = args.lxl
        ylint  -= 0.004
    l = plotHelpers.configLeg( sampleTypes, sampleDicts, legStrLen( args.legLenEnum ).value, args.lxint, ylint, [], xlover )

    if "testCutflow" in histName and "jet" in histName.lower():
        if hists[0].GetNbinsX() > 20:
            c.SetCanvasSize( 1000, 400 )

    if doSOverB:
        c.SetCanvasSize( 400, 400 )
        if "testCutflow" in histName and "jet" in histName.lower():
            if hists[0].GetNbinsX() > 20:
                c.SetCanvasSize( 600, 400 )
        p1 = ROOT.TPad( "p1", "p1", 0,  0.3, 1,   1 )
        p2 = ROOT.TPad( "p2", "p2", 0, 0.01, 1, 0.3 )
        p1.Draw()
        p2.Draw()
        p1.cd()

    isProfileX = False
    isProfileY = False

    hslen = 0
    for iH, tmpHist in enumerate( hists ):
        # copy histogram
        hist = tmpHist.Clone()
        if isinstance( hist, ROOT.TH2 ):
            if   args.doProfileX:
                hist = hist.ProfileX()
                isProfileX = True
            elif args.doProfileY:
                hist = hist.ProfileY()
                isProfileY = True
            else:
                continue

        # skip empty histograms
        if not hist.GetEntries():
            continue

        # set line attributes
        hist.SetLineColorAlpha( sampleDicts[iH]["lcolor"], sampleDicts[iH]["lalpha"] )
        hist.SetLineStyle( sampleDicts[iH]["lstyle"] )
        hist.SetLineWidth( plotHelpers.setLineWidth( sampleDicts[iH]["lstyle"] ) )
        if iBkgd >= 0 and iBkgd == iH and args.fillBkgd:
            hist.SetFillColorAlpha( sampleDicts[iH]["lcolor"], 0.15 )

        # normalize
        if hist.Integral() and not isProfileX and not isProfileY:
            plotHelpers.doNorm( hist )

        # set maximum
        max_scale      = 1.2
        max_scale_log  = len( hists )
        max_scale_logx = max_scale
        #if "Vtx" in histName or "Trk" in histName:
        #    if "avgMu" in histName or "phi" in histName or "eta" in histName or "score" in histName or \
        #        ( isProfileX and "resid" in histName or "desc" in histName ):
        #        max_scale       = 1.5
        #    if "recoeff_r" in histName.lower() or "seedeff_r" in histName.lower() or \
        #      "stdeff_r" in histName.lower() or "lrteff_r" in histName.lower() or \
        #      ( "nSelDesc" in histName and "eff" in histName.lower() ):
        #        max_scale_logx = 1.5
        if len( hists ) > 12:
            if "_dR" in histName or "eta" in histName or "rapid" in histName or "phi" in histName or "pt_s" in histName:
                max_scale_log *= 7
                if "dR" in histName or "phi" in histName or "pt_s" in histName:
                    max_scale += len( hists ) * 0.05
        
        maxy = hist.GetMaximum()
        if   doLogy: maxy *= max_scale_log
        elif doLogx: maxy *= max_scale_logx
        else:        maxy *= max_scale
        hist.SetMaximum( maxy )

        # add legend entry
        l.AddEntry( hist, plotHelpers.setLegStr( sampleTypes[iH], sampleDicts[iH], legStrLen( args.legLenEnum ).value ) ) \
          .SetTextColor( sampleDicts[iH]["lcolor"] )

        # add histo to stack
        hs.Add( hist )
        hslen += 1

    if hslen == 0:
        return
    
    # draw stack
    hs.Draw( args.drawOpt1D )

    if "Vtx" in histName:
        if "accept" in histName.lower() or "algeff" in histName.lower() or \
            "coreeff" in histName.lower() or "seedeff" in histName.lower() or "recoeff" in histName.lower():
            hs.SetMaximum(  1.60 )
            hs.SetMinimum( -0.25 )
    
    # draw legend
    l.Draw()

    # set axes
    if "cutflow" not in histName.lower() or "_N" in histName:
        xtitle = plotHelpers.setXaxisTitle( hist, True, args.histTitle, varType( args.varEnum ).value ).lstrip()
        hs.GetXaxis().SetTitle( xtitle    ) 
        hs.GetXaxis().SetTitleSize( 0.03  )
        hs.GetXaxis().SetTitleOffset( 1.4 )
        ytitle = hists[0].GetYaxis().GetTitle()
        ytitle_pre = ""
        if ytitle.startswith('n') or ytitle.startswith('fraction'):
            ytitle_pre = ytitle.split( ' ' )[0]
            ytitle     = ' '.join( ytitle.split( ' ' )[1:] )
        for iw, word in enumerate( ytitle.split( ' ' ) ):
            if word != xtitle.split( ' ' )[iw]:
                ytitle = ' '.join( ytitle.split( ' ' )[iw:] )
                break
        if ytitle_pre: ytitle = ytitle_pre + " " + ytitle
        if "Trk" in histName or "Vtx" in histName:
            if "accept" in histName.lower() or "eff" in histName.lower():
                if   "accept"  in histName.lower():
                    ytitle = "acceptance"
                elif "recoeff" in histName.lower():
                    if   "Trk" in histName:
                        ytitle = "inclusive tracking efficiency"
                    elif "Vtx" in histName:
                        ytitle = "reconstruction efficiency"
                elif "stdeff"  in histName.lower():
                    ytitle = "standard tracking efficiency"
                elif "lrteff"  in histName.lower():
                    ytitle = "large-radius tracking efficiency"
                elif "algeff"  in histName.lower():
                    ytitle = "algorithmic efficiency"
                elif "coreeff" in histName.lower():
                    ytitle = "core efficiency"
                elif "seedeff" in histName.lower():
                    ytitle = "seed efficiency"
                if   "sgnl"    in histName.lower():
                    ytitle = "signal " + ytitle
                elif "loose"   in histName.lower():
                    ytitle = "loose "  + ytitle
                elif "mid"     in histName.lower():
                    ytitle = "medium " + ytitle
                elif "tight"   in histName.lower():
                    ytitle = "tight "  + ytitle
                hs.GetYaxis().SetTitle( ytitle )
        if isProfileX:
            ytitle = "average " + ytitle
            hs.GetYaxis().SetTitle( ytitle )
    else:
        obj = ""
        if "DV" in histName:
            obj = "DV"
        elif "jet" in histName.lower():
            obj = "jet"
            if "lead" in histName.lower():
                obj = "N-lead jet"
        ytitle = " of overall " + obj + "s in all events"
        if "Efficiency" in histName:
            ytitle = "fraction" + ytitle
        else:
            ytitle = "number" + ytitle
        hs.GetYaxis().SetTitle( ytitle )

    
    # add text
    text = plotHelpers.configText( args.histTitle, args.regionDir )
    for txt in text:
        txt.Draw("same")

    if doLogy:
        ROOT.gPad.SetLogy()
    if doLogx:
        ROOT.gPad.SetLogx()

        
    # draw ratios
    if doSOverB:
        rhs = ROOT.THStack( histName, "" )
        iBkgd = -1
        for iS, stype in enumerate( sampleTypes ):
            if stype == plotHelpers.sampleType.BKGD:
                iBkgd = iS
        p2.cd()
        for iH, tmpHist in enumerate( hists ):
            # copy histogram
            rhist = tmpHist.Clone()
            if isinstance( hist, ROOT.TH2 ):
                if   args.doProfileX:
                    rhist = hist.ProfileX()
                    isProfileX = True
                elif args.doProfileY:
                    rhist = hist.ProfileY()
                    isProfileY = True
                else:
                    continue
            
            # skip empty histograms
            if not rhist.GetEntries():
                continue
            
            # set line attributes
            rhist.SetLineColorAlpha( sampleDicts[iH]["lcolor"], sampleDicts[iH]["lalpha"] )
            rhist.SetLineStyle( sampleDicts[iH]["lstyle"] )
            rhist.SetLineWidth( plotHelpers.setLineWidth( sampleDicts[iH]["lstyle"] ) )
            rhist.SetMarkerColor( sampleDicts[iH]["lcolor"] )
            rhist.SetMarkerStyle(20)
            rhist.SetMarkerSize(0.6)
            
            # divide by background for S/B plots
            if doSOverB and iBkgd >= 0:
                bkgdHist = hists[iBkgd]
                if rhist != bkgdHist: # don't divide background histogram
                    rhist.Divide( rhist, bkgdHist )
        
            # normalize
            if rhist.Integral() and not isProfileX and not isProfileY:
                plotHelpers.doNorm( rhist )

            # skip background histograms for S/B plots
            if doSOverB and iH == iBkgd: continue

            # add histo to stack
            rhs.Add( rhist )

        # draw stack
        rhs.Draw( "nostack p" )

        rhs.GetYaxis().SetNdivisions(5,2,1)
        rhs.GetYaxis().SetLabelSize(0.075)
        rhs.GetXaxis().SetLabelOffset(999)
        rhs.GetXaxis().SetLabelSize(0)
        rhs.GetYaxis().SetTitle( "S/B" )
        rhs.GetYaxis().SetTitleSize( 0.1 )
        rhs.GetYaxis().SetTitleOffset( 0.5 )
        

    # print plot
    # --> set output plot name
    outName = args.outName
    if outName and not outName.endswith('.'):
        outName += "."
    outName = tname + "." + outName
    rOutName = outName + args.regionDir
    if args.histVars:
        bname = args.histVars.split(',')[0] + "."
    else:
        bname = ""
    hname = histName
    if doSOverB:   hname += "-SOverB"
    if isProfileX: hname += ".profx"
    if isProfileY: hname += ".profy"
    cname = "1d." + hname + "." + rOutName
    if doLogy:
        ROOT.gPad.SetLogy()
        cname += "_logy"
    if doLogx:
        ROOT.gPad.SetLogx()
        cname += "_logx"
    # --> set output subdirectory
    poutDir = os.path.join(  outDir, rOutName )
    coutDir = os.path.join( poutDir, outName + bname + args.regionDir )
    if not os.path.exists( coutDir ):
        os.makedirs( coutDir )
    # --> save
    c.SaveAs( os.path.join( coutDir, cname + args.format ) )

    # close canvas
    c.Update()
    c.Clear()
    c.Close()
    del c
    if doSOverB:
        del p1
        del p2
    


## --- DRAW 2D PLOTS --- ##
def plot2D( hist, histName, sampleName, sampleType, sampleDict ):
    
    # logx, logy ??
    # make profile plot ??

    if histName.startswith('ABCD'):
        histName = '_'.join( histName.split('_')[1:] )

    # set canvas
    c = ROOT.TCanvas( histName, histName, 500, 400 )

    # draw 2D plot
    hist.SetContour(10000) # change for certain 2d histos?
    hist.Draw( args.drawOpt2D )
    hist.SetStats(0)
    hist.SetTitle("")
    c.SetRightMargin(0.125)

    # set axes
    hist.GetXaxis().SetTitleSize( 0.03  )
    hist.GetYaxis().SetTitleSize( 0.03  )
    hist.GetXaxis().SetTitleOffset( 1.4 )
    hist.GetYaxis().SetTitleOffset( 1.4 )

    # add text
    text = plotHelpers.configText( plotHelpers.setLegStr( sampleType, sampleDict, 1 ), args.regionDir )
    for txt in text:
        txt.Draw("same")

    # print plot
    # --> set output plot name
    outName = args.outName
    if outName and not outName.endswith('.'):
        outName += "."
    outName = tname + "." + outName + sampleName + "."
    rOutName = outName + args.regionDir
    if args.histVars:
        bname = args.histVars.split(',')[0] + "."
    else:
        bname = ""
    cname = "2d." + histName + "." + rOutName
    # --> set output subdirectory
    poutDir = os.path.join(  outDir, rOutName )
    coutDir = os.path.join( poutDir,  outName + bname + args.regionDir )
    if not os.path.exists( coutDir ):
        os.makedirs( coutDir )
    # --> save
    c.SaveAs( os.path.join( coutDir, cname + args.format ) )

    # close canvas
    c.Update()
    c.Clear()
    c.Close()
    del c



## --- DRAW 1D MULTIVARIATE STACK PLOTS --- ##
def plotMulti1D( hists, baseName, sampleName, sampleType, sampleDict, doLogy = False, doLogx = False ):

    # fill tmp sampleTypes, sampleDicts lists for configuring legend
    sampleTypes, sampleDicts = [], []
    for h in hists:
        sampleTypes.append( sampleType )
        sampleDicts.append( sampleDict )

    # set canvas
    c = ROOT.TCanvas( baseName )
    # set stack
    hs = ROOT.THStack( baseName, "" )
    # set legend
    l = plotHelpers.configLeg( sampleTypes, sampleDicts, legStrLen( args.legLenEnum ).value, args.lxint, args.lyint, [], args.lxl )

    isProfileX = False
    isProfileY = False
    
    hslen = 0
    for iH, tmpHist in enumerate( hists ):
        # copy histogram
        hist = tmpHist.Clone()
        if isinstance( hist, ROOT.TH2 ):
            if   args.doProfileX:
                hist = hist.ProfileX()
                isProfileX = True
            elif args.doProfileY:
                hist = hist.ProfileY()
                isProfileY = True
            else:
                continue
        
        # skip empty histograms
        if not hist.GetEntries():
            continue

        iH_ix = iH
        for ihvar, hvar in enumerate( args.histVars.split(',') ):
            if hvar in hist.GetName(): iH_ix = ihvar

        # set line attributes
        lcolor = plotHelpers.sgnlColors()[iH_ix]
        lalpha = 1.00
        #if iH: lalpha = 0.65
        lstyle = 1
        hist.SetLineColorAlpha( lcolor, lalpha )
        hist.SetLineStyle( lstyle )
        hist.SetLineWidth( plotHelpers.setLineWidth( lstyle ) )
        
        # normalize
        if hist.Integral() and not isProfileX and not isProfileY:
            plotHelpers.doNorm( hist )

        # set maximum
        max_scale     = 1.2
        max_scale_log = 4
        if isProfileX and "DarkPionDecayVtx" in hist.GetName() and "desc" in hist.GetName().lower() and "frac" not in hist.GetName():
            max_scale = 1.5
        maxy = hist.GetMaximum()
        if doLogy: maxy *= max_scale_log
        else:      maxy *= max_scale 
        hist.SetMaximum( maxy )

        # add legend entry
        l.AddEntry( hist, plotHelpers.setMultiLegStr( hist.GetName(),
              sampleType, sampleDict, varType( args.varEnum ).value, False, args.doTruthSvB ) ).SetTextColor( lcolor )
 
        # add histo to stack
        hs.Add( hist )
        hslen += 1

    if hslen == 0:
        return

    # draw stack
    hs.Draw( args.drawOptMulti1D )

    # draw legend
    l.Draw()

    # set titles and axes
    xtitle = plotHelpers.setXaxisTitle( hist, True, args.histTitle, varType( args.varEnum ).value ).lstrip() # add if isProfileY option (to include 'average' in x-axis title)
    hs.GetXaxis().SetTitle( xtitle    ) 
    hs.GetXaxis().SetTitleSize( 0.03  )
    hs.GetXaxis().SetTitleOffset( 1.4 )
    ytitle = hists[0].GetYaxis().GetTitle()
    ytitle_pre = ""
    if ytitle.startswith('n') or ytitle.startswith('fraction'):
        ytitle_pre = ytitle.split( ' ' )[0]
        ytitle     = ' '.join( ytitle.split( ' ' )[1:] )
    for iw, word in enumerate( ytitle.split( ' ' ) ):
        if word != xtitle.split( ' ' )[iw]:
            ytitle = ' '.join( ytitle.split( ' ' )[iw:] )
            break
    if ytitle_pre: ytitle = ytitle_pre + " " + ytitle
    if "Trk" in hist.GetName() and "eff" in hist.GetName().lower():
        ytitle = "tracking efficiency"
        hs.GetYaxis().SetTitle( ytitle )
    if isProfileX:
        ytitle = "average " + ytitle
        hs.GetYaxis().SetTitle( ytitle )
        
    
    # add text
    text = plotHelpers.configText( plotHelpers.setLegStr( sampleType, sampleDict, 1 ), args.regionDir )
    for txt in text:
        txt.Draw("same")
    
    # print plot
    # --> set output plot name
    outName = args.outName
    if outName and not outName.endswith('.'):
        outName += "."
    if   varType( args.varEnum ) == varType.DV:
        outName = "dvtype-" + outName
    elif varType( args.varEnum ) == varType.DV_NTRK:
        outName = "ntrkdv-" + outName
    elif varType( args.varEnum ) == varType.JET:
        outName = "jettype-" + outName
    elif varType( args.varEnum ) == varType.TRK:
        outName = "trk-" + outName
    outName = tname + "." + sampleName + "." + outName + args.regionDir
    cname = "multi1d." + baseName
    if isProfileX:
        cname += ".profx"
    if isProfileY:
        cname += ".profy"
    cname += "." + outName
    if doLogy:
        ROOT.gPad.SetLogy()
        cname += "_logy"
    if doLogx:
        ROOT.gPad.SetLogx()
        cname += "_logx"
    # --> set output directory
    poutDir = os.path.join( outDir, tname + "." + sampleName + "." + args.regionDir )
    coutDir = os.path.join( poutDir, outName )
    if not os.path.exists( coutDir ):
        os.makedirs( coutDir )
    # --> save
    c.SaveAs( os.path.join( coutDir, cname + args.format ) )

    # close canvas
    c.Update()
    c.Clear()
    c.Close()
    del c



## --- DRAW 1D MULTI-VARIATE - MULTI-SAMPLE STACK PLOTS --- ##
def plotMultiSmpl1D( hists, baseName, sampleTypes, sampleDicts, sbdVars, htitle, doLogy = False, doSOverB = False ):

    iBkgd  = -1
    isbd_b = -1
    for iS, stype in enumerate( sampleTypes ):
        if stype == plotHelpers.sampleType.BKGD:
            iBkgd = iS
            for iSBD, sbd in enumerate( sbdVars.split(',') ):
                if stype == iSBD+1:
                    for ihv, hvar in enumerate( args.histVars.split(',') ):
                        if sbd == hvar: isbd_b = ihv
    
    # build list of booleans to configure legend based on samples of desired type
    doPlotTypes = []
    for stype in sampleTypes:
        # only include samples specified in sbdVars
        doPlotType = False
        for iSBD, sbd in enumerate( sbdVars.split(',') ):
            if stype == iSBD+1:
                doPlotType = True
        #if doSOverB and stype == plotHelpers.sampleType.BKGD:
        #    doPlotType = False
        doPlotTypes.append( doPlotType )

    # set canvas
    c = ROOT.TCanvas( baseName )
    # set stack
    hs = ROOT.THStack( baseName, "" )
    # set legend
    xlover = args.lxl
    ylint  = args.lyint
    #if doSOverB:
    #    xlover += 0.025
    #    ylint  -= 0.005
    l = plotHelpers.configLeg( sampleTypes, sampleDicts, legStrLen( args.legLenEnum ).value,
                                   args.lxint, ylint, doPlotTypes, xlover )

    if "testCutflow" in baseName and "jet" in hists[0].GetName().lower():
        if hists[0].GetNbinsX() > 20:
            c.SetCanvasSize( 1000, 400 )

    if doSOverB:
        c.SetCanvasSize( 400, 400 )
        if "testCutflow" in baseName and "jet" in hists[0].GetName().lower():
            if hists[0].GetNbinsX() > 20:
                c.SetCanvasSize( 600, 400 )
        p1 = ROOT.TPad( "p1", "p1", 0,  0.3, 1,   1 )
        p2 = ROOT.TPad( "p2", "p2", 0, 0.01, 1, 0.3 )
        p1.Draw()
        p2.Draw()
        p1.cd()

    hslen = 0
    for iH, tmpHist in enumerate( hists ):
        # copy histogram
        hist = tmpHist.Clone()
        
        # skip empty histograms
        if not hist.GetEntries():
            continue

        # skip histograms not corresponding to given sbdVar, sampleType
        sampleHistMatch = False
        for iSBD, sbd in enumerate( sbdVars.split(',') ):
            if sampleTypes[int(iH/len(args.histVars.split(',')))] == iSBD+1:
                #if sbd and sbd.lower() in hist.GetName().lower():
                if sbd and sbd in hist.GetName(): # --> check this works! may have to change back or make sure sbd case sensitive
                    sampleHistMatch = True
        if not sampleHistMatch: continue

        # set line attributes
        lcolor = sampleDicts[int(iH/len(args.histVars.split(',')))]["lcolor"]
        lalpha = sampleDicts[int(iH/len(args.histVars.split(',')))]["lalpha"]
        lstyle = sampleDicts[int(iH/len(args.histVars.split(',')))]["lstyle"]
        hist.SetLineColorAlpha( lcolor, lalpha )
        hist.SetLineStyle( lstyle )
        hist.SetLineWidth( plotHelpers.setLineWidth( lstyle ) )
        if iBkgd >= 0 and int(iH/len(args.histVars.split(','))) == iBkgd and args.fillBkgd:
            hist.SetFillColorAlpha( sampleDicts[int(iH/len(args.histVars.split(',')))]["lcolor"], 0.15 )

        # normalize
        if hist.Integral():
            plotHelpers.doNorm( hist )

        # set maximum
        maxy = hist.GetMaximum()
        if   doLogy: maxy *= 4
        else:        maxy *= 1.2
        hist.SetMaximum( maxy )

        # add legend entry
        lstr = hist.GetName().split('_')[1]
        if "_evt" in hist.GetName():
            lstr = hist.GetName().split('_')[3]
        l.AddEntry( hist, plotHelpers.setMultiLegStr( lstr,
              sampleTypes[int(iH/len(args.histVars.split(',')))], sampleDicts[int(iH/len(args.histVars.split(',')))],
              varType( args.varEnum ).value, True, args.doTruthSvB, legStrLen( args.legLenEnum ).value ) ).SetTextColor( lcolor )

        # add histo to stack
        hs.Add( hist )
        hslen += 1

    if hslen == 0:
        return

    # draw stack
    hs.Draw( args.drawOptMulti1D )

    # draw legend
    l.Draw()

    # set titles and axes
    if "cutflow" not in baseName.lower() or "_N" in baseName:
        hs.GetXaxis().SetTitle( plotHelpers.setXaxisTitle( hist, True, "", varType( args.varEnum ).value ) )
        hs.GetXaxis().SetTitleSize( 0.03  )
        hs.GetXaxis().SetTitleOffset( 1.4 )
    else:
        obj = ""
        if "DV" in hist.GetName():
            obj = "DV"
        elif "jet" in hist.GetName().lower():
            obj = "jet"
            if "lead" in hist.GetName().lower():
                obj = "N-lead jet"
        ytitle = " of overall " + obj + "s in all events"
        if "Efficiency" in baseName:
            ytitle = "fraction" + ytitle
        else:
            ytitle = "number" + ytitle
        hs.GetYaxis().SetTitle( ytitle )

    # add text
    text = plotHelpers.configText( htitle, args.regionDir )
    for txt in text:
        txt.Draw("same")
        
    if doLogy:
        ROOT.gPad.SetLogy()


    # draw ratios
    if doSOverB:
        rhs = ROOT.THStack( baseName, "" )
        iBkgd = -1
        for iS, stype in enumerate( sampleTypes ):
            if stype == plotHelpers.sampleType.BKGD:
                iBkgd = iS
        p2.cd()
        for iH, tmpHist in enumerate( hists ):
            # copy histogram
            rhist = tmpHist.Clone()
            
            # skip empty histograms
            if not rhist.GetEntries():
                continue

            # skip histograms not corresponding to given sbdVar, sampleType
            sampleHistMatch = False
            for iSBD, sbd in enumerate( sbdVars.split(',') ):
                if sampleTypes[int(iH/len(args.histVars.split(',')))] == iSBD+1:
                    #if sbd and sbd.lower() in rhist.GetName().lower():
                    if sbd and sbd in rhist.GetName(): # --> check this works! may have to change back or make sure sbd case sensitive
                        sampleHistMatch = True
            if not sampleHistMatch: continue
            
            # set line attributes
            lcolor = sampleDicts[int(iH/len(args.histVars.split(',')))]["lcolor"]
            lalpha = sampleDicts[int(iH/len(args.histVars.split(',')))]["lalpha"]
            lstyle = sampleDicts[int(iH/len(args.histVars.split(',')))]["lstyle"]
            rhist.SetLineColorAlpha( lcolor, lalpha )
            rhist.SetLineStyle( lstyle )
            rhist.SetLineWidth( plotHelpers.setLineWidth( lstyle ) )
            rhist.SetMarkerColor( lcolor )
            rhist.SetMarkerStyle(20)
            rhist.SetMarkerSize(0.6)
            
            # divide by background for S/B plots
            if doSOverB and iBkgd >= 0:
                bkgdHist = hists[iBkgd*len(args.histVars.split(','))+isbd_b]
                if rhist != bkgdHist: # don't divide background histogram
                    rhist.Divide( rhist, bkgdHist )
        
            # normalize
            if rhist.Integral(): plotHelpers.doNorm( rhist )

            # skip background histograms for S/B plots
            if doSOverB and int(iH/len(args.histVars.split(','))) == iBkgd: continue

            # add histo to stack
            rhs.Add( rhist )

        # draw stack
        rhs.Draw( "nostack p" )

        rhs.GetYaxis().SetNdivisions(5,2,1)
        rhs.GetYaxis().SetLabelSize(0.075)
        rhs.GetXaxis().SetLabelOffset(999)
        rhs.GetXaxis().SetLabelSize(0)
        rhs.GetYaxis().SetTitle( "S/B" )
        rhs.GetYaxis().SetTitleSize( 0.1 )
        rhs.GetYaxis().SetTitleOffset( 0.5 )


    # print plot
    # --> set output plot name
    outName = args.outName
    if outName and not outName.endswith('.'):
        outName += "."
    outName  = tname + "." + outName
    rOutName = outName + args.regionDir

    baseDV = "bare"
    bname = ""
    if args.doTruthSvB:
        sbd_bname, sbd_tname = [], []
        for sbd in sbdVars.split(','):
            if sbd:
                if   varType( args.varEnum ) == varType.DV:
                    if "darkPion".lower() in sbd.lower():
                        sbd_bname.append( re.split( 'darkPion',  sbd, flags=re.IGNORECASE )[0] )
                        sbd_tname.append( 'darkPionDV'  )
                    elif "kshort".lower() in sbd.lower():
                        sbd_bname.append( re.split( 'kshort',    sbd, flags=re.IGNORECASE )[0] )
                        sbd_tname.append( 'kshortDV'    )
                    elif "nomatch".lower() in sbd.lower():
                        sbd_bname.append( re.split( 'nomatch',   sbd, flags=re.IGNORECASE )[0] )
                        sbd_tname.append( 'nomatchDV'   )
                    elif args.baseDV.lower() in sbd.lower():
                        sbd_bname.append( re.split( args.baseDV, sbd, flags=re.IGNORECASE )[0] )
                        sbd_tname.append( args.baseDV )
                    else:
                        sbd_bname.append( re.split( 'DV',        sbd, flags=re.IGNORECASE )[0] )
                        sbd_tname.append( args.baseDV )
                elif varType( args.varEnum ) == varType.JET:
                    if "darkMatch".lower() in sbd.lower():
                        sbd_jet_bname = re.split( 'darkMatch', sbd, flags=re.IGNORECASE )[0]
                        sbd_jet_tname = "darkMatchJet"
                    else:
                        sbd_jet_bname = re.split( 'jet', sbd, flags=re.IGNORECASE )[0]
                        sbd_jet_tname = "jet"
                    if   "0" in sbd: sbd_jet_bname += "0"
                    elif "1" in sbd: sbd_jet_bname += "1"
                    elif "2" in sbd: sbd_jet_bname += "2"
                    elif "3" in sbd: sbd_jet_bname += "3"
                    sbd_tname .append( sbd_jet_tname )
                    sbd_bname .append( sbd_jet_bname )
        bname_tmp = sbd_bname[0]
        bname += bname_tmp
        if bname: bname += "."
        for sbd_b in sbd_bname:
            if sbd_b != bname_tmp:
                bname_tmp = sbd_b
                bname += bname_tmp + "."
        for sbd_t in sbd_tname:
            bname += sbd_t + "."
    else:
        for sbd in sbdVars.split(','):
            if sbd: bname += sbd + "."
    if varType( args.varEnum ) == varType.DV:
        histName = hist.GetName().split('_')[1]
        if   histName.startswith("2trk"): bname += "2trk."
        elif histName.startswith("3trk"): bname += "3trk."
        elif histName.startswith("4trk"): bname += "4trk."
        elif histName.startswith("5trk"): bname += "5trk."
    baseName = bname + baseName
    if doSOverB: baseName += "-SOverB"
    cname = "multismpl1d." + baseName + "." + rOutName
    if doLogy:
        ROOT.gPad.SetLogy()
        cname += "_logy"
    # --> set output directory
    poutDir = os.path.join(  outDir, rOutName )
    coutDir = os.path.join( poutDir, outName + bname + args.regionDir )
    if not os.path.exists( coutDir ):
        os.makedirs( coutDir )
    # --> save
    c.SaveAs( os.path.join( coutDir, cname + args.format ) )

    # close canvas
    c.Update()
    c.Clear()
    c.Close()
    del c
    if doSOverB:
        del p1
        del p2




### --- RUN PROGRAM --- ###
if __name__ == "__main__":
    sampleNames, sampleTypes, sampleDicts, sampleHists, hists = getSampleHistos()
    plotHistos( sampleNames, sampleTypes, sampleDicts, sampleHists, hists )
