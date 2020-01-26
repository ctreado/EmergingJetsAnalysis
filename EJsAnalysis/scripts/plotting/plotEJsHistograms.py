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
import re
from enum import Enum
import math

### command line arguments ###
parser = argparse.ArgumentParser( description = "histogram plotter options",
                                      formatter_class = argparse.ArgumentDefaultsHelpFormatter )

# input / output arguments
# --> will eventually want to change default directoriese to "gridOutput" (and remove "latest" from path)
parser.add_argument( "--inDir", dest = "inDir", default = os.getenv('EJ_PATH') + "/../output/localOutput/latest/EJsNtupToHistOutput/",
                         help = "Input directory containing all histogram root files." )
parser.add_argument( "--inSgnlDir", dest = "inSgnlDir", default = None,
                         help = "Input directory containing all signal histogram root files." )
parser.add_argument( "--inBkgdDir", dest = "inBkgdDir", default = None,
                         help = "Input directory containing all background histogram root files." )
parser.add_argument( "--inDataDir", dest = "inDataDir", default = None,
                         help = "Input directory containing all data histogram root files." )
parser.add_argument( "--regionDir", dest = "regionDir", default = "all",
                         help = "ROOT file TDirectory of region-specific histograms to plot." )
parser.add_argument( "--histDir", dest = "histDir", default = "EJsHists",
                         help = "Input file sub-directory where histograms are stored. \
                         Default 'EJsHists' set by EJsNtupleToHists algorithm." )
parser.add_argument( "--outDir", dest = "outDir", default = os.getenv('EJ_PATH') + "/../output/localOutput/latest/plots/",
                         help = "Output directory where plots will be stored." )
parser.add_argument( "--outTag", dest = "outTag", default = "", help = "Output tag for plot directory." )
parser.add_argument( "--outName", dest = "outName", default = "", help = "Base output name for saved plots." )
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
parser.add_argument( "--varEnum", dest = "varEnum", type = int, default = 0,
                         help = "Enumerator for variable histogram type (i.e. DV, DV_NTRK). Input must be integer." )
# plotting options / configurations
parser.add_argument( "--doMultiSmpl", dest = "doMultiSmpl", action = "store_true", default = False,
                         help = "Plot histograms from different samples against each other." )
parser.add_argument( "--draw1D", dest = "draw1D", action = "store_true", default = False, help = "Draw 1D stack plots." )
parser.add_argument( "--drawOpt1D", dest = "drawOpt1D", default = "nostack hist", help = "Draw option(s) for 1D stack plots." )
parser.add_argument( "--drawMulti1D", dest = "drawMulti1D", action = "store_true", default = False,
                         help = "Draw 1D multivariate stack plots over multiple variables." )
parser.add_argument( "--drawOptMulti1D", dest = "drawOptMulti1D", default = "nostack hist",
                         help = "Draw option(s) for 1D multivariate stack plots." )
parser.add_argument( "--draw2D", dest = "draw2D", action = "store_true", default = False, help = "Draw individual 2D plots." )
parser.add_argument( "--drawOpt2D", dest = "drawOpt2D", default = "colz", help = "Draw option(s) for 2D plots." )
parser.add_argument( "--drawABCD", dest = "drawABCD", action = "store_true", default = False, help = "Draw ABCD plane plots." )
parser.add_argument( "--xCutABCD", dest = "xCutABCD", type = float, default = 1385, help = "X-axis cut for ABCD regions." )
parser.add_argument( "--yCutABCD", dest = "yCutABCD", type = float, default = 2, help = "Y-axis cut for ABCD regions." )
parser.add_argument( "--format", dest = "format", default = "pdf", help = "File format to save plots in." )
parser.add_argument( "--varyCtauCols", dest = "varyCtauCols", action = "store_true", default = False,
                         help = "Vary model's base line color for different lifetimes." )
# ABCD calculations
parser.add_argument( "--doABCD_count", dest = "doABCD_count", action = "store_true", default = False,
                         help = "Count events in ABCD regions." )
parser.add_argument( "--doABCD_est", dest = "doABCD_est", action = "store_true", default = False,
                         help = "Estimate background estimates in signal using ABCD method." )
# extra arguments
parser.add_argument( "--writeCombined", dest = "writeCombined", action = "store_true", default = False,
                         help = "Write combined histograms to new root file for each sample. \
                         Requires use with '--outCombDir' argument." )
parser.add_argument( "--outCombDir", dest = "outCombDir", default = None,
                         help = "Output directory where combined histogram files are written." )
# lumicalc scale args -- do, file names, etc.
parser.add_argument( "--doLumiScale", dest = "doLumiScale", action = "store_true", default = False,
                         help = "Scale data to full (or specified) luminosity -- for use when running over subset of data." )
parser.add_argument( "--lumiCalcDir", dest = "lumiCalcDir", default = os.getenv('EJ_PATH') + "/EJsAnalysis/data/",
                         help = "Directory containing lumi-calc files." )

args = parser.parse_args()


# --> finish formatting -- okay for now...
# --> --> still need to play around with line colors / attributes for all plotting methods, especially for background and data ...
# --> --> fix legend configuration -- okay for now, but come back to...
# --> --> fix text box (for 1d) [once fixed, can remove region from histogram title]
# --> add to run script -- done for current needs; still needs to be updated (need to include 2D, ABCD plots)
# --> update abcd functions --> move calculations to separate c++ code --> return counts, efficiencies s/(root)b's, etc. [see Duncan's code] to then fill histos / plot here
# --> --> output text files with numbers (yields, efficiencies, etc.) rather than just writing to log files

# --> continue making other matched-vs-unmatched histograms to plot
# --> move on to look at tracks, k-short mass window, dR b/w tracks and DV center, fiducial cuts, etc. (see mattermost)


### --- SET GLOBAL VARIABLES --- ###
subdir = os.path.join( args.histDir, args.histTree, args.regionDir )

# make plot output directory
outTag = time.strftime("%Y.%m.%d_%Hh", time.localtime())
if args.outTag:
    outTag = args.outTag + "_" + outTag
outDir = os.path.join( args.outDir, outTag )
if not os.path.exists( outDir ):
    os.makedirs( outDir )

if not args.format.startswith('.'):
    args.format = '.' + args.format

class sampleType( Enum ):
    SGNL = 1
    BKGD = 2
    DATA = 3

class legSize( Enum ):
    BIG = 1
    MED = 2
    SML = 3

class varType( Enum ):
    NONE    = 0
    DV      = 1
    DV_NTRK = 2

# set line colors and palettes
# --> for signal: one base color per model; one line / marker style per Xdm; one color (close to base) per lifetime
sgnlColors = [ ROOT.kRed, ROOT.kGreen + 1, ROOT.kBlue, ROOT.kViolet, ROOT.kOrange + 1 ]
bkgdColors = [ ROOT.kGray + 2 ]
dataColors = [ ROOT.kBlack, ROOT.kGray+3, ROOT.kGray+1, ROOT.kGray ] # TEMP PLACEHOLDERS --> FIX

sgnlPalettes = [ ROOT.kCherry, ROOT.kAvocado, ROOT.kDeepSea, ROOT.kFuchsia, ROOT.kDarkBodyRadiator ]
bkgdPalettes = [ ROOT.kGreyScale ]
dataPalettes = [ ROOT.kAlpine, ROOT.kAtlantic, ROOT.kPearl, ROOT.kCividis ]

texec_sgnl, texec_bkgd, texec_data = [], [], []
for iS, spal in enumerate( sgnlPalettes ):
    sgnlPalStr = "gStyle->SetPalette(" + str(sgnlPalettes[iS]) + ", 0, 0.3); TColor::InvertPalette();"
    texec_sgnl.append( ROOT.TExec( "sgnlEx_" + str(iS), sgnlPalStr ) )
for iB, bpal in enumerate( bkgdPalettes ):
    bkgdPalStr = "gStyle->SetPalette(" + str(bkgdPalettes[iB]) + ", 0, 0.5); TColor::InvertPalette();"
    texec_bkgd.append( ROOT.TExec( "bkgdEx_" + str(iB), bkgdPalStr ) )
for iD, dpal in enumerate( dataPalettes ):
    dataPalStr = "gStyle->SetPalette(" + str(dataPalettes[iD]) + ", 0, 0.5); TColor::InvertPalette();"
    texec_data.append( ROOT.TExec( "dataEx_" + str(iD), dataPalStr ) )
texec_default = ROOT.TExec( "texec_" + str(iS+1), "gStyle->SetPalette(kBird)" ) # default palette

# data run events (for scaling)
datarunDict = {
    "280862" : 813113,  # data15
    "281411" : 1116747,
    "283608" : 167097,
    "301973" : 3575638, # data16
    "303208" : 3986284,
    "309440" : 2788829,
    "331804" : 2455740, # data17
    "335022" : 1556499,
    "340030" : 3802048,
    "350144" : 2690990, # data18
    "357451" : 2137686,
    "363830" : 2409360,
}



### --- RETRIEVE HISTOGRAM INFORMATION --- ##
def getSampleHistos():
    
    if not args.inSgnlDir: args.inSgnlDir = args.inDir
    if not args.inBkgdDir: args.inBkgdDir = args.inDir
    if not args.inDataDir: args.inDataDir = args.inDir

    sampleNames, sampleTypes, sampleDicts, sampleFiles, sampleWeights = [], [], [], [], []
    
    ## get signal files
    if len( args.sgnlType ) > 0:
        sgnlTypes = args.sgnlType.split(',')
        for sgnlType in sgnlTypes:
            if ':' in sgnlType:
                sgnlName = sgnlType.split(':')[0]
                sgnlType = sgnlType.split(':')[-1]
            else:
                sgnlName = sgnlType
            sampleNames   .append( sgnlName )
            sampleTypes   .append( sampleType.SGNL )
            sampleDicts   .append( getSampleDict( sgnlName, sampleType.SGNL ) )
            sampleFiles   .append( getFileList( args.inSgnlDir, sgnlType.split('+') ) )
            sampleWeights .append( getMetaDataWeights( getFileList( args.inSgnlDir, sgnlType.split('+') ) ) )

    ## get background files
    if len( args.bkgdType ) > 0:
        bkgdTypes = args.bkgdType.split(',')
        for bkgdType in bkgdTypes:
            if ':' in bkgdType:
                bkgdName = bkgdType.split(':')[0]
                bkgdType = bkgdType.split(':')[-1]
            else:
                bkgdName = bkgdType
            sampleNames   .append( bkgdName )
            sampleTypes   .append( sampleType.BKGD )
            sampleDicts   .append( getSampleDict( bkgdName, sampleType.BKGD ) )
            sampleFiles   .append( getFileList( args.inBkgdDir, bkgdType.split('+') ) )
            sampleWeights .append( getMetaDataWeights( getFileList( args.inBkgdDir, bkgdType.split('+') ) ) )
            
    ## get data files
    if len( args.dataType ) > 0:
        dataTypes = args.dataType.split(',')
        for dataType in dataTypes:
            if ':' in dataType:
                dataName = dataType.split(':')[0]
                dataType = dataType.split(':')[-1]
            else:
                dataName = dataType
            sampleNames   .append( dataName )
            sampleTypes   .append( sampleType.DATA )
            sampleDicts   .append( getSampleDict( dataName, sampleType.DATA ) )
            sampleFiles   .append( getFileList( args.inDataDir, dataType.split('+') ) )
            sampleWeights .append( getMetaDataWeights( getFileList( args.inDataDir, dataType.split('+') ) ) )

    ## set global metadata weights for samples (for scaling)
    global xsec, kfactor, genFiltEff, lumi
    xsec, kfactor, genFiltEff, lumi = [], [], [], []
    for weight in sampleWeights:
         xsec       .append( weight[0] )
         kfactor    .append( weight[1] )
         genFiltEff .append( weight[2] )
         lumi       .append( weight[3] )

    ## get list of histograms common to all files
    sampleHists = []
    histList = args.histList.split(',')
    for tag in histList:
        exclTag = ""
        if ':' in tag:
            inclTag = tag.split(':')[0]
            exclTag = tag.split(':')[-1]
        else:
            inclTag = tag
        tmpHists = getHistList( sampleFiles, inclTag.split('+'), exclTag.split('+') )
        for iH, hist in enumerate( tmpHists ):
            if hist not in sampleHists:
                sampleHists.append( hist )
    
    ## get all histogram objects
    hists = []
    lumiScales = []
    for iSample, sampleName in enumerate( sampleNames ):
        combHists, lumiScale = getHists( sampleName, sampleTypes[iSample], sampleFiles[iSample], sampleHists )
        hists.append( combHists )
        lumiScales.append( lumiScale )

    ## set global lumi-scales for scaling data subsets
    global luminosityScale
    luminosityScale = lumiScales
    ## set global metadata event counts for samples
    global nInitEvents, nSelEvents, initSumw, selSumw, initSumw2, selSumw2
    nInitEvents, nSelEvents, initSumw, selSumw, initSumw2, selSumw2 = [], [], [], [], [], []
    for iHL, histList in enumerate( hists ):
        for iH, hist in enumerate( histList ):
            if "MetaData_EventCount" in hist.GetName():
                nInitEvents .append( hist.GetBinContent(1) )
                nSelEvents  .append( hist.GetBinContent(2) )
                initSumw    .append( hist.GetBinContent(3) )
                selSumw     .append( hist.GetBinContent(4) )
                initSumw2   .append( hist.GetBinContent(5) )
                selSumw2    .append( hist.GetBinContent(6) )

    ## set TExec color palette list
    global texec
    texec = []
    for sdict in sampleDicts:
        texec.append( sdict["palette"] )
    
    ## return lists
    return sampleNames, sampleTypes, sampleDicts, sampleHists, hists


    
### --- RETRIEVE FILE LIST --- ##
def getFileList( histDir, histTag ):

    # get list of files matching hist-tags in hist-directory
    histFiles = []
    for f in os.listdir(histDir):
        passedTags = True
        for tag in histTag:
            orTags = tag.split('=')
            if not any( ot in f for ot in orTags ):
                passedTags = False
        if passedTags:
            histFiles.append( os.path.join( histDir, f ) )
        
    return histFiles



## --- RETRIEVE HISTOGRAM LIST --- ##
def getHistList( histFiles, inTag, exTag ):

    allFiles     = sum( histFiles, [] ) # combine into single list
    allHists     = []
    hists        = []

    # loop over files and get list of histograms (keys)
    for file in allFiles:
        allHists.append( [] ) # save list of histograms for each file
        f = ROOT.TFile( file, "READ" )
        d = f.GetDirectory( args.histDir )
        dir = d.Get( os.path.join( args.histTree, args.regionDir ) )
        if not dir:
            print ( "ERROR: TDirectory not in TFile. Exiting." )
            exit(1)
        # grab histograms of interest
        for key in dir.GetListOfKeys():
            # skip metadata weight histograms -- already got info we need...
            if "MetaData_Weights" in key.GetName():
                continue
            # get rest of histograms in directory
            passedInTags = True
            passedExTags = True
            for intag in inTag:
                orInTags = intag.split('=')
                if not any( oit.lower() in key.GetName().lower() for oit in orInTags ):
                    passedInTags = False
                for extag in exTag:
                    if extag:
                        orExTags = extag.split('=')
                        if any( oet.lower() in key.GetName().lower() for oet in orExTags ):
                            passedExTags = False
            if passedInTags and passedExTags:
                allHists[-1].append( key.GetName() )
        
        f.Close()

    # save singular list of histograms common to all files
    for hist in allHists[0]:
        if all( hist in histList for histList in allHists ):
            hists.append( hist )
        else:
            print ( "histogram", hist, "missing from file(s)...skipping" )
            
    # return list of histograms
    return hists



## --- RETRIEVE HISTOGRAMS --- ##
def getHists( sampleName, sampleType, fileList, histList ):

    # combine common histograms across all files in sample
    CombinedHists = []
    data_initSumw = []
    data_fileList = []
    for iFile, file in enumerate( fileList ):
        f = ROOT.TFile.Open( file, "READ" )
        f.cd( subdir )
        for iHist, hist in enumerate( histList ):
            h = f.CurrentDirectory().Get( hist )

            # scale histograms...

            # get initial sum of weights for data files -- needed to scale to full lumi
            if sampleType == sampleType.DATA and "MetaData_EventCount" in h.GetName():
                data_initSumw.append( h.GetBinContent(3) )
                data_fileList.append( file )

            # combine histograms
            if iFile == 0:
                CombinedHists.append( h.Clone( sampleName + "_" + h.GetName() ) ) # make new combined histogram
                CombinedHists[-1].SetDirectory(0)
            else:
                CombinedHists[iHist].Add(h) # add to existing histogram histogram

        f.Close()

    lumiScale = 1
    if args.doLumiScale and sampleType == sampleType.DATA:
        lumiScale = getLumiCalcScale( data_initSumw, data_fileList )
        for hist in CombinedHists:
            hist.Scale( lumiScale )

    # add overflow/underflow...

    # save
    if args.writeCombined:
        if not args.outCombDir:
            print ( "No output directory specified: not writing combined histograms to disk." )
        else:
            if not os.path.exists( args.outCombDir ):
                os.makedirs( args.outCombDir )
            f = ROOT.TFile( os.path.join( args.outCombDir, sampleName + ".root" ), "recreate" )
            if not f.GetDirectory( subdir ):
                f.mkdir( subdir )
            f.cd( subdir )
            for hist in CombinedHists:
                hist.Write()

    return CombinedHists, lumiScale



## --- PLOT HISTOGRAMS --- ##
def plotHistos( sampleNames, sampleTypes, sampleDicts, histNames, hists ):

    # rearrange hists from [sample][histName] to [histName][sample]
    newHists = []
    for iName, name in enumerate( histNames ):
        newHists.append( [] )
        for iType, type in enumerate( sampleTypes ):
            newHists[-1].append( hists[iType][iName] )

    # rearrange hists from [sample][histName] to [baseName][sample/histVar] (for desired subset only)
    varHists, baseNames = [], []
    if len( args.histVars ) > 0:
        histVars = args.histVars.split(',')
        for iType, type in enumerate( sampleTypes ):
            for iName, name in enumerate( histNames ):
                getBaseHists = False
                for iVar, var in enumerate( histVars ):
                    if var.lower() in name.lower():
                        getBaseHists = True
                if getBaseHists:
                    baseName = '_'.join( name.split('_')[1:] )
                    if baseName not in baseNames:
                        baseNames.append( baseName )
                        varHists.append( [] )
            for iBase, base in enumerate( baseNames ):
                for iVar, var in enumerate( histVars ):
                    for iName, name in enumerate( histNames ):
                        if var.lower() + "_" + base.lower() == name.lower():
                            varHists[iBase].append( hists[iType][iName] )

    # initialize lists for ABCD estimates
    nA, nB, nC, nD = [], [], [], []
    effA, effB, effC, effD = [], [], [], []
    
    # --> plot same histos from different samples against each other
    for iName, name in enumerate( histNames ):
        hists = newHists[iName]

        # skip metadata hists
        if "MetaData" in name:
            continue
        
        # draw 1D stack plots (multiple samples per plot)
        if args.draw1D:
            if isinstance( hists[0], ROOT.TH1 ) and not isinstance( hists[0], ROOT.TH2 ):
                plot1D( hists, name, sampleNames, sampleTypes, sampleDicts )
                plot1D( hists, name, sampleNames, sampleTypes, sampleDicts, True ) # log-y

        # draw 2D plots (one hist per plot)
        if args.draw2D:
            if isinstance( hists[0], ROOT.TH2 ):
                for iH, hist in enumerate( hists ):
                    plot2D( hist, name, sampleNames[iH], sampleTypes[iH], sampleDicts[iH] )

        # do ABCD calculations --> return counts, efficiencies, estimates, errors so we can print to histos?
        if isinstance( hists[0], ROOT.TH2 ) and "ABCD" in name:
            if args.doABCD_count:
                nA, nB, nC, nD, effA, effB, effC, effD = ABCD_count( hists, sampleTypes )
            if args.doABCD_est:
                ABCD_est( nA, nB, nC, nD, sampleTypes )
            # draw ABCD plots
            if args.drawABCD:
                plotABCD( hists, nsame, sampleNames, sampleTypes, sampleDicts )


    # --> plot different histos from same or different samples against each other
    for iBase, base in enumerate( baseNames ):
        hists = varHists[iBase]

        if args.drawMulti1D:
            if isinstance( hists[0], ROOT.TH1 ) and not isinstance( hists[0], ROOT.TH2 ):
                # draw 1D stack plots (multiple histos, single samples per plot)
                if not args.doMultiSmpl:
                    for iS, sample in enumerate( sampleNames ):
                        hb = iS     * len( args.histVars.split(',') )
                        he = (iS+1) * len( args.histVars.split(',') )
                        plotMulti1D( hists[hb:he], base, sample, sampleTypes[iS], sampleDicts[iS] )
                        plotMulti1D( hists[hb:he], base, sample, sampleTypes[iS], sampleDicts[iS], True ) # log-y
                # draw 1D stack plots (multiple histos, multiple samples per plot)
                if args.doMultiSmpl:
                    for iSbd, sbd in enumerate( args.sbdVars.split(':') ):
                        htitle = args.histTitle.split(':')[iSbd]
                        plotMultiSmpl1D( hists, base, sampleTypes, sampleDicts, sbd, htitle )
                        plotMultiSmpl1D( hists, base, sampleTypes, sampleDicts, sbd, htitle, True ) # log-y



## --- DRAW 1D STACK PLOTS --- ##
def plot1D( hists, histName, sampleNames, sampleTypes, sampleDicts, doLogy = False ):

    # set canvas
    c = ROOT.TCanvas( histName )
    # set stack
    hs = ROOT.THStack( histName, "" )
    # set legend
    l = configLeg( len(hists), legSize.SML )

    hslen = 0
    for iH, hist in enumerate( hists ):
        # skip empty histograms
        if not hist.GetEntries():
            continue
        
        # set line attributes
        hist.SetLineColorAlpha( sampleDicts[iH]["lcolor"], sampleDicts[iH]["lalpha"] )
        hist.SetLineStyle( sampleDicts[iH]["lstyle"] )
        hist.SetLineWidth( setLineWidth( sampleDicts[iH]["lstyle"] ) )
        hist.Scale( 1 / hist.Integral() )
        # set maximum --> may want to play around with scale factors...
        maxy = hist.GetMaximum()
        if doLogy:
            maxy *= 4
        else:
            maxy *= 1.2
        hist.SetMaximum( maxy )
        # --> do we want to cut on x-axis so search and validation region axis ranges are the same???
        # add legend entry
        l.AddEntry( hist, setLegStr( sampleTypes[iH], sampleDicts[iH], False ) ).SetTextColor( sampleDicts[iH]["lcolor"] )
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
    hs.GetXaxis().SetTitle( setXaxisTitle( hist ) )
    hs.GetXaxis().SetTitleSize( 0.03 )
    hs.GetXaxis().SetTitleOffset( 1.4 )

    # add text
    text = configText( args.histTitle )
    for txt in text:
        txt.Draw("same")

    # print plot
    outName = args.outName
    moutDir = outDir
    if outName:
        moutDir = os.path.join( outDir, outName )
        outName = outName + "."
    cname = "th1." + outName + histName + "." + args.regionDir
    if doLogy:
        ROOT.gPad.SetLogy()
        cname += "_logy"
    if not os.path.exists( moutDir ):
        os.makedirs( moutDir )
    c.SaveAs( os.path.join( moutDir, cname + args.format ) )

    # close canvas
    c.Update()
    c.Clear()
    c.Close()
    del c



## -- DRAW 1D MULTIVARIATE STACK PLOTS -- ##
def plotMulti1D( hists, baseName, sampleName, sampleType, sampleDict, doLogy = False ):

    # set canvas
    c = ROOT.TCanvas( baseName )
    # set stack
    hs = ROOT.THStack( baseName, "" )
    # set legend
    l = configLeg( len(hists), legSize.SML, True )

    hslen = 0
    for iH, hist in enumerate( hists ):
        # skip empty histograms
        if not hist.GetEntries():
            continue
        
        # set line attributes
        lcolor = sgnlColors[iH]
        lalpha = 1.00
        if iH:
            lalpha = 0.65
        lstyle = 1
        hist.SetLineColorAlpha( lcolor, lalpha )
        hist.SetLineStyle( lstyle )
        hist.SetLineWidth( setLineWidth( lstyle ) )
        hist.Scale( 1 / hist.Integral() )
        # set maximum --> may want to play around with scale factors...
        maxy = hist.GetMaximum()
        if doLogy:
            maxy *= 4
        else:
            maxy *= 1.2
        hist.SetMaximum( maxy )
        # add legend entry
        l.AddEntry( hist, setMultiLegStr( hist.GetName().split('_')[1], sampleType, sampleDict ) ).SetTextColor( lcolor )
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
    hs.GetXaxis().SetTitle( setXaxisTitle( hist, True ) )
    hs.GetXaxis().SetTitleSize( 0.03 )
    hs.GetXaxis().SetTitleOffset( 1.4 )

    # add text
    text = configText(setLegStr( sampleType, sampleDict ) )
    for txt in text:
        txt.Draw("same")

    # print plot
    # --> set output plot name
    outName = args.outName
    if outName:
        baseName = outName + "." + baseName
    bname = ""
    if   varType( args.varEnum ) == varType.DV:
        bname = "vsDV"
    elif varType( args.varEnum ) == varType.DV_NTRK:
        bname = "ntrkDV"
    if bname:
        baseName = bname + "." + baseName
    if outName:
        outName = bname + "." + outName
    cname = "th1.multi." + baseName + "." + sampleName + "." + args.regionDir
    # --> set output subdirectory
    moutDir = os.path.join( outDir, outName, sampleName )
    if not os.path.exists( moutDir ):
        os.makedirs( moutDir )
    # --> set logy
    if doLogy:
        ROOT.gPad.SetLogy()
        cname += "_logy"
    # --> save
    c.SaveAs( os.path.join( moutDir, cname + args.format ) )

    # close canvas
    c.Update()
    c.Clear()
    c.Close()
    del c



## --- DRAW 1D MULTIVARIATE / MULTI-SAMPLE STACK PLOTS --- ##
def plotMultiSmpl1D( hists, baseName, sampleTypes, sampleDicts, sbdVars, htitle, doLogy = False ):

    # set canvas
    c  = ROOT.TCanvas( baseName )
    # set stack
    hs = ROOT.THStack( baseName, "" )
    # set legend
    l  = configLeg( len(hists)/len(args.histVars.split(',')), legSize.SML, True )

    hslen = 0
    for iH, hist in enumerate( hists ):
        # skip empty histograms
        if not hist.GetEntries():
            continue

        # skip histograms not corresponding to given sbdVar, sampleType
        sampleHistMatch = False
        for iSBD, sbd in enumerate( sbdVars.split(',') ):
            if sampleType( iSBD+1 ) == sampleTypes[iH/len(args.histVars.split(','))]:
                if sbd and sbd.lower() in hist.GetName().lower():
                    sampleHistMatch = True
        if not sampleHistMatch:
            continue
            
        # set line attributes
        hist.SetLineColorAlpha( sampleDicts[iH/len(args.histVars.split(','))]["lcolor"],
                                sampleDicts[iH/len(args.histVars.split(','))]["lalpha"] )
        hist.SetLineStyle( sampleDicts[iH/len(args.histVars.split(','))]["lstyle"] )
        hist.SetLineWidth( setLineWidth( sampleDicts[iH/len(args.histVars.split(','))]["lstyle"] ) )
        hist.Scale( 1 / hist.Integral() )
        # set maximum --> may want to play around with scale factors...
        maxy = hist.GetMaximum()
        if doLogy:
            maxy *= 4
        else:
            maxy *= 1.2
        hist.SetMaximum( maxy )
        # add legend entry
        l.AddEntry( hist, setMultiLegStr( hist.GetName().split('_')[1],
           sampleTypes[iH/len(args.histVars.split(','))],
           sampleDicts[iH/len(args.histVars.split(','))] ) ).SetTextColor( sampleDicts[iH/len(args.histVars.split(','))]["lcolor"] )
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
    hs.GetXaxis().SetTitle( setXaxisTitle( hist, True ) )
    hs.GetXaxis().SetTitleSize( 0.03 )
    hs.GetXaxis().SetTitleOffset( 1.4 )

    # add text
    text = configText( htitle )
    for txt in text:
        txt.Draw("same")
        
    # print plot
    # --> set output plot name
    outName = args.outName
    if outName:
        baseName = outName + "." + baseName
    bname = ""
    for sbd in sbdVars.split(','):
        if sbd:
            bname += sbd + "."
    baseName = bname + baseName
    cname = "th1.multi." + baseName + "." + args.regionDir
    # --> set output subdirectory
    moutDir = os.path.join( outDir, bname[:-1] )
    if not os.path.exists( moutDir ):
        os.makedirs( moutDir )
    # --> set logy
    if doLogy:
        ROOT.gPad.SetLogy()
        cname += "_logy"
    # --> save
    c.SaveAs( os.path.join( moutDir, cname + args.format ) )

    # close canvas
    c.Update()
    c.Clear()
    c.Close()
    del c

    

## --- DRAW 2D PLOTS --- ##
def plot2D( hist, histName, sampleName, sampleType, sampleDict ):

    if histName.startswith('ABCD'):
        histName = '_'.join( histName.split('_')[1:] )
        
    # set canvas
    c = ROOT.TCanvas( histName )

    # draw 2D plot
    hist.Draw(args.drawOpt2D)
    hist.SetStats(0);
    hist.SetTitle("")

    # set axes
    hist.GetXaxis().SetTitleSize( 0.03  )
    hist.GetXaxis().SetTitleOffset( 1.4 )
    hist.GetYaxis().SetTitleSize( 0.03  )
    hist.GetYaxis().SetTitleOffset( 1.4 )

    # add text
    text = configText( setLegStr( sampleType, sampleDict ) )
    for txt in text:
        txt.Draw("same")

    # print plot
    # --> set output plot name
    outName = args.outName
    if args.outName:
        outName = outName + "."
    cname = "th2." + outName + histName + "." + sampleName + "." + args.regionDir
    # --> set output subdirectory
    moutDir = os.path.join( outDir, "2d", sampleName )
    if not os.path.exists( moutDir ):
        os.makedirs( moutDir )
    # --> save
    c.SaveAs( os.path.join( moutDir, cname + args.format ) )

    # close canvas
    c.Update()
    c.Clear()
    c.Close()
    del c
    



## --- MAKE ABCD PLOTS --- ##
def plotABCD( hists, histName, sampleNames, sampleTypes, sampleDicts ):

    print "in plotABCD()"
    
    # set canvas
    c = ROOT.TCanvas( histName, histName, 1100, 800 )

    # set legend
    l = configLeg( len(hists), legSize.BIG )

    ROOT.gPad.SetTicks(1,1)
    ROOT.gStyle.SetOptStat(0)

    # need to draw something to generate pad
    htemp = hists[0]
    htemp.Draw("col2")
    htemp.SetTitle( "ABCD Plane" )

    # draw contour plots
    xtitle = ytitle = ""
    for iH, hist in enumerate( hists ):
        # blind data
        if sampleTypes[iH] == sampleType.DATA and \
            ( args.regionDir == "sgnl" or args.regionDir == "signal" or args.regionDir == "search" ):
            continue
        
        texec[iH].Draw() # draw palette
        #hist.SetMaximum( getMaxBinContent( hist ) * 1.4 ) # sets max scale
        # set line attributes / contour
        hist.SetLineColor( sampleDicts[iH]["lcolor"] )
        hist.SetLineStyle( sampleDicts[iH]["lstyle"] )
        hist.SetLineWidth(3);
        hist.SetContour(4) # --> Duncan uses 4; may want more than that, but less than 10...play around with it...
        # draw histogram
        hist.DrawNormalized( "cont0 same" ) # surface colors
        hist.DrawNormalized( "cont1 same" ) # line styles
        
        # get axis titles
        xtitle = hist.GetXaxis().GetTitle()
        ytitle = hist.GetYaxis().GetTitle()

        # add to legend
        l.AddEntry( hist, setLegStr( sampleTypes[iH], sampleDicts[iH] ) ).SetTextColor( sampleDicts[iH]["lcolor"] )

    # return palette to default
    texec_default.Draw()

    # draw legend
    l.Draw()

    # set axes
    htemp.GetXaxis().SetTitle( xtitle )
    htemp.GetYaxis().SetTitle( ytitle )
    htemp.GetXaxis().SetTitleSize( 0.03 )
    htemp.GetYaxis().SetTitleSize( 0.03 )
    htemp.GetXaxis().SetTitleOffset( 1.4 )

    # draw ABCD cut regions --> consider moving this and ABCD event counting to separate function(s)
    p = ROOT.TPad( "p", "p", 0., 0., 1., 1. )
    p.SetFillStyle(0)
    p.Draw()
    p.cd()
    # get bins where region cuts applied and draw lines
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
    # add text --> CONFIGURE; add details of search/validation region; optimize box and text size; etc.
    tp = ROOT.TPaveText( 0.13, 0.77, 0.33, 0.87 )
    if ( args.regionDir == "search" ):
        tp.AddText( "SEARCH REGION" )
    elif ( args.regionDir == "valid" ):
        tp.AddText( "VALIDATION REGION" )
    #tp.SetBorderSize(1)
    #tp.SetFillColorAlpha(0,1)
    tp.Draw()
    # add ABCD labels --> CHANGE LOCATIONS IN PLOT
    xlo = ( edge + xloc ) / 2
    ylo = ( edge + yloc ) / 2
    xhi = ( width + xloc ) / 2
    yhi = ( width + yloc ) / 2
    #xlo = .15
    #ylo = .15
    #xhi = .85
    #yhi = .85
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

    # print plot
    outName = ""
    for sName in sampleNames:
        outName += "." + sName
    c.Print( "abcd." + histName + outName + "." + args.regionDir + args.format )
    # --> png fills whole plot with palette; pdf leaves background white outside of contour

    # close canvas
    c.Update()
    c.Clear()
    c.Close()
    del c


## --- DO ABCD CALCULATIONS --- ##
# count events and calculate efficiencies in ABCD regions #
def ABCD_count( hists, sampleTypes ):
    
    nA, nB, nC, nD = [], [], [], []
    effA, effB, effC, effD = [], [], [], []
    for iH, hist in enumerate( hists ):
        # get bins defining regions
        xbin  = hist.GetXaxis().FindBin( args.xCutABCD )
        ybin  = hist.GetYaxis().FindBin( args.yCutABCD )

        # count events in each region
        nAi = hist.Integral( xbin,     -1, ybin,     -1 )
        nBi = hist.Integral( xbin,     -1,   -1, ybin-1 )
        nCi = hist.Integral(   -1, xbin-1, ybin,     -1 )
        nDi = hist.Integral(   -1, xbin-1,   -1, ybin-1 )

        # calculate efficiencies in each region
        scale = luminosityScale[iH]
        if not sampleTypes[iH] == sampleType.DATA:
            scale *= xsec[iH] * genFiltEff[iH] * lumi[iH] / initSumw[iH]
        effAi = nAi / scale / initSumw[iH]
        effBi = nBi / scale / initSumw[iH]
        effCi = nCi / scale / initSumw[iH]
        effDi = nDi / scale / initSumw[iH]

        # blind data
        if sampleTypes[iH] == sampleType.DATA \
          and ( args.regionDir == "sgnl" or args.regionDir == "signal" or args.regionDir == "search" ):
            nAi     = -999
            nBi     = -999
            nCi     = -999
            effAi   = -999
            effBi   = -999
            effCi   = -999
            
        # fill output lists
        nA         .append( nAi   )
        nB         .append( nBi   )
        nC         .append( nCi   )
        nD         .append( nDi   )
        effA       .append( effAi )
        effB       .append( effBi )
        effC       .append( effCi )
        effD       .append( effDi )

        # print output --> PRINT SAMPLE NAME
        print "########## ABCD counts ##########"
        print "Sample Type:", sampleTypes[iH]
        print "Raw / Weighted Yield in A:", nAi, nAi / ( xsec[iH] * genFiltEff[iH] * lumi[iH] / initSumw[iH] )
        print "Raw / Weighted Yield in B:", nBi, nBi / ( xsec[iH] * genFiltEff[iH] * lumi[iH] / initSumw[iH] )
        print "Raw / Weighted Yield in C:", nCi, nCi / ( xsec[iH] * genFiltEff[iH] * lumi[iH] / initSumw[iH] )
        print "Raw / Weighted Yield in D:", nDi, nDi / ( xsec[iH] * genFiltEff[iH] * lumi[iH] / initSumw[iH] )
        print "Efficiency in A: ", effAi
        print "Efficiency in A: ", effBi
        print "Efficiency in A: ", effCi
        print "Efficiency in A: ", effDi

        # fill efficiency histograms

    # return counts and efficiencies
    return nA, nB, nC, nD, effA, effB, effC, effD


## --- DO ABCD CALCULATIONS --- ##
# estimate backgrounds (and errors) in signal region #
def ABCD_est( nA, nB, nC, nD, sampleTypes ):

    nA_exp, nA_exp_err, z = [], [], []
    for iS, sample in enumerate( sampleTypes ):

        # estimate n background events in A using basic ABCD method
        # --> if we end up doing some kind of fitting, write and call separate C++ function...
        nAi_exp = nC[iS] * nB[iS] / nD[iS]
        if sampleTypes[iS] == sampleType.DATA \
          and ( args.regionDir == "sgnl" or args.regionDir == "signal" or args.regionDir == "search" ):
            nAi_exp = -999 # for now; figure out another way to estimate data in search region ...

        # calculate background estimate error
        nAi_exp_err = 0
        zi = 0
        if nA[iS] and nB[iS] and nC[iS] and nD[iS]:
            if nAi_exp == -999:
                nAi_exp_err = -999
                zi = -999
            else:
                nAi_exp_err = nA[iS] * math.sqrt( 1./nB[iS] + 1./nC[iS] + 1./nD[iS] )
                zi = ( nA[iS] - nAi_exp ) / math.sqrt( nA[iS] + pow( nAi_exp_err, 2 ) )

        # fill output lists
        nA_exp     .append( nAi_exp )
        nA_exp_err .append( nAi_exp_err )
        z          .append( zi )

        # print output
        print "########## ABCD method ##########"
        print "Sample Type:", sampleTypes[iS]
        print "Region A Estimate:", nAi_exp, "+/-", nAi_exp_err
        print "True Value: ", nA[iS], "+/-", math.sqrt(nA[iS])
        print "Standardized difference:", zi
        



### --- HELPER FUNCTIONS --- ###
# get 2D histogram maximum bin content --> add analogue for 1d ??
def getMaxBinContent( hist ):
    max_entry = 0
    for i in range( 0, hist.GetNbinsX() ):
        for j in range( 0, hist.GetNbinsY() ):
            entry = hist.GetBinContent( i+1, j+1 )
            if entry > max_entry:
                max_entry = entry
                
    return max_entry


# configure legend
def configLeg( nEntries, size = legSize.BIG, doMulti = False ):

    # --> may need some more configuration, like for long legends when plotting many samples on same plot...
    # --> --> need to update so legends with smaller strings are further shifted to right...
    
    if   size == legSize.BIG:
        xl   = 0.500
        xr   = 0.880
        yt   = 0.870
        yint = 0.030
    elif size == legSize.SML:
        xl   = 0.600
        xr   = 0.900
        yt   = 0.870
        yint = 0.030

    if doMulti:
        varEnum = varType( args.varEnum )
        if varEnum == varType.DV_NTRK:
            xl = xl + 0.15
    if args.doMultiSmpl:
        xl = xl - 0.10
        
    yb = yt - yint * nEntries
    

    leg = ROOT.TLegend( xl, yb, xr, yt )
    leg.SetBorderSize(0)
    leg.SetFillColorAlpha(0,0)

    return leg
    
    
# set strings for legend entries
def setLegStr( sampleType, sampleDict, longstr = True ):
    legend_string = ""
    if sampleType == sampleType.SGNL:
        if longstr:
            legend_string = "Model " + sampleDict["model"] + " (#pi_{dm} = " + str(sampleDict["pidm"]) + \
            " GeV); #chi_{dm} = " + str(sampleDict["xdm"]) + " GeV, c#tau = " + str(sampleDict["ctau"]) + " mm"
        else:
            legend_string = "Mod" + sampleDict["model"] + "_" + str(sampleDict["pidm"]) + "_" + \
            str(sampleDict["xdm"]) + "_" + str(sampleDict["ctau"])
    elif sampleType == sampleType.BKGD:
        if longstr:
            legend_string = sampleDict["sample"] + " MC background (" + sampleDict["jzxw"] + ")"
        else:
            legend_string = sampleDict["jzxw"] + " MC bkgd"
    elif sampleType == sampleType.DATA:
        legend_string = sampleDict["year"]

    return legend_string


# set strings for multivariate legend entries
def setMultiLegStr( histName, sampleType, sampleDict ):

    varEnum = varType( args.varEnum )
    if varEnum == varType.DV:
        legend_string = ""
        if "byJet"     .lower() in histName.lower():
            if legend_string:
                legend_string += " "
            legend_string += "by-jet"
        if "byLeadJet" .lower() in histName.lower():
            if legend_string:
                legend_string += " "
            legend_string += "by-lead-jet"
        if "fiducial"  .lower() in histName.lower():
            if legend_string:
                legend_string += " "
            legend_string += "fiducial-cut"
        if "bareDV"    .lower() in histName.lower():
            if legend_string:
                legend_string += " "
            legend_string += "bare"
        if "cleanDV"   .lower() in histName.lower():
            if legend_string:
                legend_string += " "
            legend_string += "clean"
        if "filtDV"    .lower() in histName.lower():
            if legend_string:
                legend_string += " "
            legend_string += "filtered"
        if "darkPionDV".lower() in histName.lower():
            if legend_string:
                legend_string += " "
            legend_string += "dark-pion-decay matched"
        if "kshortDV"  .lower() in histName.lower():
            if legend_string:
                legend_string += " "
            legend_string += "k-short-decay matched"
        if "nomatchDV" .lower() in histName.lower():
            if legend_string:
                legend_string += " "
            legend_string += "unmatched"
        if not legend_string:
            legend_string = histName
    elif varEnum == varType.DV_NTRK:
        if histName.startswith("2trk"):
            legend_string = "2-track"
        elif histName.startswith("3trk"):
            legend_string = "3-track"
        elif histName.startswith("4trk"):
            legend_string = "4-track"
        elif histName.startswith("5trk"):
            legend_string = "5-plus-track"
        else:
            legend_string = histName
    elif varEnum == varType.NONE:
        legend_string = histName
    if args.doMultiSmpl:
        legend_string += " " + setLegStr( sampleType, sampleDict, False )

    return legend_string


# configure plot text
def configText( titleStr ):
    ttxt  = 0.025
    xrtxt = 1 - ttxt*8.5
    xltxt = 0.100
    ytxt  = 0.950
    sxtxt = ttxt + 0.32*ttxt
    sytxt = ttxt + 0.50*ttxt
    
    atlstr  = "#it{ATLAS} Internal"
    lumistr = "#sqrt{s} = 13TeV"
    atltxt  = ROOT.TLatex( xrtxt,         ytxt,         atlstr  )
    lumitxt = ROOT.TLatex( xrtxt + sxtxt, ytxt - sytxt, lumistr )
    atltxt   .SetTextSize( ttxt )
    lumitxt  .SetTextSize( ttxt )
    atltxt   .SetNDC( ROOT.kTRUE )
    lumitxt  .SetNDC( ROOT.kTRUE )

    smplstr = titleStr
    smpltxt = ROOT.TLatex( xltxt, ytxt, smplstr )
    smpltxt  .SetTextSize( ttxt )
    smpltxt  .SetNDC( ROOT.kTRUE )

    regstr = ""
    if   ( args.regionDir == "search-minus-one" ):
        regstr = "SEARCH-MINUS-ONE REGION"
    elif ( args.regionDir == "search" ):
        regstr = "SEARCH REGION"
    elif ( args.regionDir == "valid" ):
        regstr = "VALIDATION REGION"
    regtxt = ROOT.TLatex( xltxt, ytxt - sytxt, regstr )
    regtxt  .SetTextSize( ttxt )
    regtxt  .SetNDC( ROOT.kTRUE )
    
    txtlist = []
    txtlist.append( atltxt  )
    txtlist.append( lumitxt )
    txtlist.append( smpltxt )
    txtlist.append( regtxt  )

    return txtlist


# set x-axis title
def setXaxisTitle( hist, doMulti = False ):
    xtitle = hist.GetXaxis().GetTitle()

    if doMulti:
        varEnum  = varType( args.varEnum )
        histName = hist.GetName().split('_')[1]
        if varEnum != varType.NONE:
            xtitle = "DV" + xtitle.split('DV')[-1]
            if   varEnum == varType.DV:
                if   histName.startswith("2trk"):
                    xtitle = "2-track " + xtitle
                elif histName.startswith("3trk"):
                    xtitle = "3-track " + xtitle
                elif histName.startswith("4trk"):
                    xtitle = "4-track " + xtitle
                elif histName.startswith("5trk"):
                    xtitle = "5-plus-track " + xtitle
            elif varEnum == varType.DV_NTRK:
                title = ""
                if "byJet" .lower() in histName.lower():
                    if title:
                        title += " "
                    title += "by-jet"
                if "byLeadJet" .lower() in histName.lower():
                    if title:
                        title += " "
                    title += "by-lead-jet"
                if "fiducial" .lower() in histName.lower():
                    if title:
                        title += " "
                    title += "fiducial-cut"
                if "bareDV".lower() in histName.lower():
                    if title:
                        title += " "
                    title += "bare"
                if "cleanDV".lower() in histName.lower():
                    if title:
                        title += " "
                    title += "clean"
                if "filtDV".lower() in histName.lower():
                    if title:
                        title += " "
                    title += "filtered"
                if "darkPionDV".lower() in histName.lower():
                    if title:
                        title += " "
                    title += "dark-pion-decay matched"
                if "kshortDV".lower() in histName.lower():
                    if title:
                        title += " "
                    title += "k-short-decay matched"
                if "nomatchDV".lower() in histName.lower():
                    if title:
                        title += " "
                    title += "unmatched"
                xtitle = title + " " + xtitle

    return xtitle


# set line width
def setLineWidth( lstyle ):
    lwidth = 2
    if lstyle != 1:
        lwidth = 4

    return lwidth


# get lumicalc info for scaling data subset to desired lumi
def getLumiCalcScale( nDataEvents, dataFileList ):

    lumi_sum = 0
    for iF, file in enumerate( dataFileList ):
        year = os.path.basename(file).split('.')[0].split('-')[-1].split('_')[0]
        run  = os.path.basename(file).split('.')[1][2:]
        lcdir = os.path.join( args.lumiCalcDir, year )
        lcfile = ""
        for item in os.listdir( lcdir ):
            if "OflLumi" in item and not "actualMu" in item:
                lcfile = item
        f = ROOT.TFile.Open( os.path.join( lcdir, lcfile ), "READ" )
        # grab histograms
        for key in f.GetListOfKeys():
            if run in key.GetName() and "intlumi" in key.GetName():
                h = f.Get( key.GetName() )
                run_lumi = float( h.GetTitle().split('=')[1].split(' ')[1] ) / 1e9
                lumi_sum += run_lumi * nDataEvents[iF] / datarunDict[str(run)]

    return lumi[-1] / lumi_sum # lumi same for all samples (at least should be)


# get metadata weights
def getMetaDataWeights( files ):
    xsec = kfactor = genFiltEff = lumi = 0
    for file in files:
        f = ROOT.TFile( file, "READ" )
        f.cd( subdir )
        # grab MetaData_Weights histogram --> only need histo from first file
        for key in f.CurrentDirectory().GetListOfKeys():
            if "MetaData_Weights" in key.GetName():
                xsec       = f.CurrentDirectory().Get( key.GetName() ).GetBinContent(1)
                kfactor    = f.CurrentDirectory().Get( key.GetName() ).GetBinContent(2)
                genFiltEff = f.CurrentDirectory().Get( key.GetName() ).GetBinContent(3)
                lumi       = f.CurrentDirectory().Get( key.GetName() ).GetBinContent(4)
                break
            
    return xsec, kfactor, genFiltEff, lumi
            
    


# set and get dictionaries for sample information (i.e. signal point parameters)
def getSampleDict( sampleName, sampleType ):
    sampledict = {}
    # signal sample dictionary
    if sampleType == sampleType.SGNL:
        dictlist = []
        if   "312004" in sampleName or "ModelA" in sampleName and "1400" in sampleName and "20" in sampleName:
            dictlist = [ 312004, "A", 5, 1400, 20 ]
        elif "312008" in sampleName or "ModelA" in sampleName and "1000" in sampleName and "150" in sampleName:
            dictlist = [ 312008, "A", 5, 1000, 150 ]
        elif "312017" in sampleName or "ModelA" in sampleName and "600" in sampleName and "1" in sampleName:
            dictlist = [ 312017, "A", 5, 600, 1 ]
        elif "312022" in sampleName or "ModelB" in sampleName and "1400" in sampleName and "20" in sampleName:
            dictlist = [ 312022, "B", 2, 1400, 20 ]
        elif "312028" in sampleName or "ModelB" in sampleName and "1000" in sampleName and "5" in sampleName:
            dictlist = [ 312028, "B", 2, 1000, 5 ]
        elif "312031" in sampleName or "ModelB" in sampleName and "600" in sampleName and "300" in sampleName:
            dictlist = [ 312031, "B", 2, 600, 300 ]
        elif "312039" in sampleName or "ModelC" in sampleName and "1400" in sampleName and "75" in sampleName:
            dictlist = [ 312039, "C", 10, 1400, 75 ]
        elif "312046" in sampleName or "ModelC" in sampleName and "1000" in sampleName and "5" in sampleName:
            dictlist = [ 312046, "C", 10, 1000, 5 ]
        elif "312052" in sampleName or "ModelC" in sampleName and "600" in sampleName and "2" in sampleName:
            dictlist = [ 312053, "C", 10, 600, 2 ]
        elif "312060" in sampleName or "ModelD" in sampleName and "1400" in sampleName and "2" in sampleName:
            dictlist = [ 312060, "D", 20, 1400, 2 ]
        elif "312066" in sampleName or "ModelD" in sampleName and "1000" in sampleName and "1" in sampleName:
            dictlist = [ 312066, "D", 20, 1000, 1 ]
        elif "312067" in sampleName or "ModelD" in sampleName and "600" in sampleName and "300" in sampleName:
            dictlist = [ 312067, "D", 20, 600, 300 ]
        elif "312075" in sampleName or "ModelB" in sampleName and "1400" in sampleName and "75" in sampleName:
            dictlist = [ 312075, "E", 0.8, 1400, 75 ]
        elif "312080" in sampleName or "ModelB" in sampleName and "1000" in sampleName and "150" in sampleName:
            dictlist = [ 312080, "E", 0.8, 1000, 150 ]
        elif "312090" in sampleName or "ModelB" in sampleName and "600" in sampleName and "0.5" in sampleName:
            dictlist = [ 312090, "E", 0.8, 600, 0.5 ]
        # --> add cases for combined samples (i.e. all Model A, all Xdm-1400, etc.) ???
        # set line attributes and color palettes
        color   = ROOT.kWhite
        palette = texec_default
        # set line color / palette by model
        if   dictlist[1] == "A":
            color   = sgnlColors[0]
            palette = texec_sgnl[0]
        elif dictlist[1] == "B":
            color   = sgnlColors[1]
            palette = texec_sgnl[1]
        elif dictlist[1] == "C":
            color   = sgnlColors[2]
            palette = texec_sgnl[2]
        elif dictlist[1] == "D":
            color   = sgnlColors[3]
            palette = texec_sgnl[3]
        elif dictlist[1] == "E":
            color   = sgnlColors[4]
            palette = texec_sgnl[4]
        # set line style by mediator mass
        if   dictlist[3] == 1400:
            style = 1
        elif dictlist[3] == 1000:
            style = 3
        elif dictlist[3] == 600:
            style = 7
        # vary base colors by lifetime --> TEST COLORS (want one to be base color, so add zero)
        # --> don't need for now, since available samples have singular lifetimes per model-Xdm point
        if args.varyCtauCols:
            if   dictlist[4] == 300:
                color = color + 1
            elif dictlist[4] == 150:
                color = color + 2
            elif dictlist[4] == 75:
                color = color + 3
            elif dictlist[4] == 20:
                color = color + 4
            elif dictlist[4] == 5:
                color = color + 5
            elif dictlist[4] == 2:
                color = color + 6
            elif dictlist[4] == 1:
                color = color + 7
            elif dictlist[4] == 0.5:
                color = color + 8
        sampledict = {
            "dsid"     : dictlist[0], # mc channel number / dsid
            "model"    : dictlist[1], # model (A, B, C, D, or E)
            "pidm"     : dictlist[2], # dark pion mass [GeV]
            "xdm"      : dictlist[3], # scalar mediator mass [GeV]
            "ctau"     : dictlist[4], # dark pion lifetime [mm]
            "lcolor"   : color,       # line color
            "palette"  : palette,     # color palette
            "lstyle"   : style,       # line style
            "lalpha"   : 1.00,        # line color alpha
        }
    # background sample dictionary
    if sampleType == sampleType.BKGD:
        dictlist = []
        color    = bkgdColors[0]
        palette  = texec_bkgd[0]
        style    = 1
        if "361024" in sampleName or "JZ4W" in sampleName:
            dictlist = [ 361024, "Pythia dijet", "JZ4W", 400, 800 ]
            color    = bkgdColors[0]
            palette  = texec_bkgd[0]
        sampledict = {
            "dsid"    : dictlist[0], # mc channel number / dsid
            "sample"  : dictlist[1], # mc background sample type (i.e. 'Pythia dijet')
            "jzxw"    : dictlist[2], # JZXW pT slice
            "ptlow"   : dictlist[3], # truth jet pT low [GeV]
            "pthigh"  : dictlist[4], # truth jet pT high [GeV]
            "lcolor"  : color,       # line color
            "palette" : palette,     # color palette
            "lstyle"  : style,       # line style
            "lalpha"  : 0.65,        # line color alpha
        }
    # data sample dictionary
    if sampleType == sampleType.DATA:
        dictlist = []
        yearlist = []
        color    = dataColors[0]
        palette  = texec_data[0]
        style    = 7
        if "15" in sampleName:
            yearlist.append( "15" )
            color   = dataColors[0]
            palette = texec_data[0]
        if "16" in sampleName:
            yearlist.append( "16" )
            color   = dataColors[1]
            palette = texec_data[1]
        if "17" in sampleName:
            yearlist.append( "17" )
            color   = dataColors[2]
            palette = texec_data[2]
        if "18" in sampleName:
            yearlist.append( "18" )
            color   = dataColors[3]
            palette = texec_data[3]
        yearstr = "data"
        for year in yearlist:
            yearstr += year + "+"
        if yearstr.endswith('+'):
            yearstr = yearstr[:-1]
        dictlist = [ yearstr ]
        sampledict = {
            "year"    : dictlist[0], # data year(s)
            "lcolor"  : color,       # line color
            "palette" : palette,     # color palette
            "lstyle"  : style,       # line style
            "lalpha"  : 1.00,        # line color alpha
        }

    return sampledict
        


### --- RUN PROGRAM --- ###
if __name__ == "__main__":
    sampleNames, sampleTypes, sampleDicts, sampleHists, hists = getSampleHistos()
    plotHistos( sampleNames, sampleTypes, sampleDicts, sampleHists, hists )

    
