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
parser.add_argument( "--varEnum", dest = "varEnum", type = int, default = 1,
                         help = "Enumerator for variable histogram type (i.e. DV, DV_NTRK). Input must be integer." )
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
parser.add_argument( "--drawOpt1D", dest = "drawOpt1D", default = "nostack hist", help = "Draw option(s) for 1D stack plots." )
parser.add_argument( "--drawOpt2D", dest = "drawOpt2D", default = "colz", help = "Draw option(s) for 2D plots." )
parser.add_argument( "--drawOptMulti1D", dest = "drawOptMulti1D", default = "nostack hist",
                         help = "Draw option(s) for 1D multivariate stack plots." )
parser.add_argument( "--doMultiSmpl", dest = "doMultiSmpl", action = "store_true", default = False,
                         help = "Plot histograms from different samples against each other." )
parser.add_argument( "--legLenEnum", dest = "legLenEnum", type = int, default = 1,
                         help = "Enumerator for legend entry string length. Input must be integer." )
parser.add_argument( "--lxint", dest = "lxint", type = float, default = 0.008, help = "Legend x-length per entry string length." )
parser.add_argument( "--lyint", dest = "lyint", type = float, default = 0.030, help = "Legend y-length per entry." )
parser.add_argument( "--lxl", dest = "lxl", type = float, default = 0.600, help = "Legend left x-pos (override for multivariate plots)." )
parser.add_argument( "--format", dest = "format", default = "pdf", help = "File format to save plots in." )

args = parser.parse_args()



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
    SHORT   = 10
class varType( Enum ):
    DV      = 1
    DV_NTRK = 2



## --- RETRIEVE HISTOGRAM INFORMATION --- ##
def getSampleHistos():
    
    if not args.inSgnlDir: args.inSgnlDir = args.inDir
    if not args.inBkgdDir: args.inBkgdDir = args.inDir
    if not args.inDataDir: args.inDataDir = args.inDir

    histDir    = os.path.join( args.histDir, args.histTree  )
    region_dir = os.path.join(      histDir, args.regionDir )

    # get samples
    sampleNames, sampleTypes, sampleDicts, sampleFiles = plotHelpers.getSamples(
        args.inSgnlDir, args.inBkgdDir, args.inDataDir, args.sgnlType, args.bkgdType, args.dataType )

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
            if isinstance( hists[0], ROOT.TH1 ) and not isinstance( hists[0], ROOT.TH2 ):
                plot1D( hists, name, sampleNames, sampleTypes, sampleDicts )
                plot1D( hists, name, sampleNames, sampleTypes, sampleDicts, True ) # log-y

        # draw 1D plots (one histo per plot)
        if args.draw2D:
            if isinstance( hists[0], ROOT.TH2 ):
                for iH, hist in enumerate( hists ):
                    plot2D( hist, name, sampleNames[iH], sampleTypes[iH], sampleDicts[iH] )

                    
    # --> plot different histos from same or different samples against each other
    for iBase, base in enumerate( baseNames ):
        hists = varHists[iBase]

        if len(hists) <= 0: continue

        if args.drawMulti1D:
            if isinstance( hists[0], ROOT.TH1 ) and not isinstance( hists[0], ROOT.TH2 ):
                # draw 1D multi-variate stack plots from SAME samples (multiple histos, single samples per plot)
                if not args.doMultiSmpl:
                    for iS, sample in enumerate( sampleNames ):
                        hb = iS    * len( args.histVars.split(',') )
                        he = (iS+1)* len( args.histVars.split(',') )
                        plotMulti1D( hists[hb:he], base, sample, sampleTypes[iS], sampleDicts[iS] )
                        plotMulti1D( hists[hb:he], base, sample, sampleTypes[iS], sampleDicts[iS], True ) # log-y
                # draw 1D multi-variate stack plots from DIFFERENT samples (multiplee histos, multiple samples per plot)
                elif args.doMultiSmpl:
                    for iSBD, sbd in enumerate( args.sbdVars.split(':') ):
                        htitle = args.histTitle.split(':')[iSBD]
                        plotMultiSmpl1D( hists, base, sampleTypes, sampleDicts, sbd, htitle )
                        plotMultiSmpl1D( hists, base, sampleTypes, sampleDicts, sbd, htitle, True ) # log-y
                    
                


## --- DRAW 1D STACK PLOTS --- ##
def plot1D( hists, histName, sampleNames, sampleTypes, sampleDicts, doLogy = False ):

    # set canvas
    c = ROOT.TCanvas( histName )
    # set stack
    hs = ROOT.THStack( histName, "" )
    # set legend
    l = plotHelpers.configLeg( sampleTypes, sampleDicts, legStrLen( args.legLenEnum ).value, args.lxint, args.lyint )

    hslen = 0
    for iH, hist in enumerate( hists ):
        # skip empty histograms
        if not hist.GetEntries():
            continue
        
        # set line attributes
        hist.SetLineColorAlpha( sampleDicts[iH]["lcolor"], sampleDicts[iH]["lalpha"] )
        hist.SetLineStyle( sampleDicts[iH]["lstyle"] )
        hist.SetLineWidth( plotHelpers.setLineWidth( sampleDicts[iH]["lstyle"] ) )
        hist.Scale( 1 / hist.Integral() )
        
        # set maximum --> may want to play around with scale factors...
        maxy = hist.GetMaximum()
        if doLogy: maxy *= 4
        else:      maxy *= 1.2
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
    
    # draw legend
    l.Draw()
    
    # set axes
    hs.GetXaxis().SetTitle( plotHelpers.setXaxisTitle( hist ) )
    hs.GetXaxis().SetTitleSize( 0.03 )
    hs.GetXaxis().SetTitleOffset( 1.4 )

    # add text
    text = plotHelpers.configText( args.histTitle, args.regionDir )
    for txt in text:
        txt.Draw("same")

    # print plot
    # --> set output plot name
    outName = args.outName
    if outName and not outName.endswith('.'):
        outName += "."
    outName = tname + "." + outName + args.regionDir
    cname = "1d." + histName + "." + outName
    if doLogy:
        ROOT.gPad.SetLogy()
        cname += "_logy"
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



## --- DRAW 2D PLOTS --- ##
def plot2D( hist, histName, sampleName, sampleType, sampleDict ):
    
    # logx, logy ??
    # make profile plot ??

    if histName.startswith('ABCD'):
        histName = '_'.join( histName.split('_')[1:] )

    # set canvas
    c = ROOT.TCanvas( histName )

    # draw 2D plot
    hist.Draw( args.drawOpt2D )
    hist.SetStats(0)
    hist.SetTitle("")

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
    outName = tname + "." + outName + sampleName + "." + args.regionDir
    cname = "2d." + histName + "." + outName
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



## --- DRAW 1D MULTIVARIATE STACK PLOTS --- ##
def plotMulti1D( hists, baseName, sampleName, sampleType, sampleDict, doLogy = False ):

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

    hslen = 0
    for iH, hist in enumerate( hists ):
        # skip empty histograms
        if not hist.GetEntries():
            continue

        # set line attributes
        lcolor = plotHelpers.sgnlColors()[iH]
        lalpha = 1.00
        #if iH: lalpha = 0.65
        lstyle = 1
        hist.SetLineColorAlpha( lcolor, lalpha )
        hist.SetLineStyle( lstyle )
        hist.SetLineWidth( plotHelpers.setLineWidth( lstyle ) )
        
        # normalize
        if hist.Integral():
            hist.Scale( 1 / hist.Integral() )

        # set maximum
        maxy = hist.GetMaximum()
        if doLogy: maxy *= 4
        else:      maxy *= 1.2

        # add legend entry
        l.AddEntry( hist, plotHelpers.setMultiLegStr( hist.GetName().split('_')[1],
              sampleType, sampleDict, varType( args.varEnum ).value ) ).SetTextColor( lcolor )
 
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
    hs.GetXaxis().SetTitle( plotHelpers.setXaxisTitle( hist, True, varType( args.varEnum ).value ) )
    hs.GetXaxis().SetTitleSize( 0.03  )
    hs.GetXaxis().SetTitleOffset( 1.4 )

    # add text
    text = plotHelpers.configText( plotHelpers.setLegStr( sampleType, sampleDict, 1 ), args.regionDir )
    for txt in text:
        txt.Draw("same")
    
    # print plot
    # --> set output plot name
    outName = args.outName
    if outName and not outName.endswith('.'):
        outName += "."
    if varType( args.varEnum ) == varType.DV:
        outName = "dvtype-" + outName
    elif varType( args.varEnum ) == varType.DV_NTRK:
        outName = "ntrkdv-" + outName
    outName = tname + "." + sampleName + "." + outName + args.regionDir
    cname = "multi1d." + baseName + "." + outName
    if doLogy:
        ROOT.gPad.SetLogy()
        cname += "_logy"
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
def plotMultiSmpl1D( hists, baseName, sampleTypes, sampleDicts, sbdVars, htitle, doLogy = False ):

    # build list of booleans to configure legend based on samples of desired type
    doPlotTypes = []
    for stype in sampleTypes:
        # only include samples specified in sbdVars
        doPlotType = False
        for iSBD, sbd in enumerate( sbdVars.split(',') ):
            if stype == iSBD+1:
                doPlotType = True
        doPlotTypes.append( doPlotType )

    # set canvas
    c = ROOT.TCanvas( baseName )
    # set stack
    hs = ROOT.THStack( baseName, "" )
    # set legend
    l = plotHelpers.configLeg( sampleTypes, sampleDicts, legStrLen( args.legLenEnum ).value,
                                   args.lxint, args.lyint, doPlotTypes, args.lxl )

    hslen = 0
    for iH, hist in enumerate( hists ):
        # skip empty histograms
        if not hist.GetEntries():
            continue

        # skip histograms not corresponding to give sbdVar, sampleType
        sampleHistMatch = False
        for iSBD, sbd in enumerate( sbdVars.split(',') ):
            if sampleTypes[iH/len(args.histVars.split(','))] == iSBD+1:
                if sbd and sbd.lower() in hist.GetName().lower():
                    sampleHistMatch = True
        if not sampleHistMatch: continue

        # set line attributes
        lcolor = sampleDicts[iH/len(args.histVars.split(','))]["lcolor"]
        lalpha = sampleDicts[iH/len(args.histVars.split(','))]["lalpha"]
        lstyle = sampleDicts[iH/len(args.histVars.split(','))]["lstyle"]
        hist.SetLineColorAlpha( lcolor, lalpha )
        hist.SetLineStyle( lstyle )
        hist.SetLineWidth( plotHelpers.setLineWidth( lstyle ) )

        # normalize
        if hist.Integral():
            hist.Scale( 1 / hist.Integral() )

        # set maximum
        maxy = hist.GetMaximum()
        if doLogy: maxy *= 4
        else:      maxy *= 1.2

        # add legend entry
        l.AddEntry( hist, plotHelpers.setMultiLegStr( hist.GetName().split('_')[1],
              sampleTypes[iH/len(args.histVars.split(','))], sampleDicts[iH/len(args.histVars.split(','))],
              varType( args.varEnum ).value, True ) ).SetTextColor( lcolor )

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
    hs.GetXaxis().SetTitle( plotHelpers.setXaxisTitle( hist, True, varType( args.varEnum ).value ) )
    hs.GetXaxis().SetTitleSize( 0.03  )
    hs.GetXaxis().SetTitleOffset( 1.4 )

    # add text
    text = plotHelpers.configText( htitle, args.regionDir )
    for txt in text:
        txt.Draw("same")

    # print plot
    # --> set output plot name
    outName = args.outName
    if outName and not outName.endswith('.'):
        outName += "."
    outName  = tname + "." + outName
    rOutName = outName + args.regionDir
    bname = ""
    for sbd in sbdVars.split(','):
        if sbd: bname += sbd + "."
    baseName = bname + baseName
    cname = "multismpl1d." + baseName + "." + rOutName
    if doLogy:
        ROOT.gPad.SetLogy()
        cname += "_logy"
    # --> set output directory
    poutDir = os.path.join( outDir, rOutName )
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
    
        
    



### --- RUN PROGRAM --- ###
if __name__ == "__main__":
    sampleNames, sampleTypes, sampleDicts, sampleHists, hists = getSampleHistos()
    plotHistos( sampleNames, sampleTypes, sampleDicts, sampleHists, hists )
