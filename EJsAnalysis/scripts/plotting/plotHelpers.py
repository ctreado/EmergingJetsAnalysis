#!/usr/bin/env python

############################################################
# plotHelpers.py                                           # 
############################################################
# helper functions for plotting scripts                    #
############################################################
# Colleen Treado                                           #
############################################################

# TO RUN ON LOCAL MACHINE (NOT CERNVM) NEED TO RUN W/ PYTHON3 --> make compatible with both python versions...
# --> also need to source root directory: 'source /usr/local/Cellar/root/6.16.00/bin/thisroot.sh'
# --> also need to set EJ_PATH in EmergingJetsAnalysis repo when running outside athena: 'export EJ_PATH=$(pwd)'

import os
import ROOT


class sampleType:
    SGNL = 1
    BKGD = 2
    DATA = 3

class legStrLen:
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

class legSize:
    BIG   = 1
    MED   = 2
    SMALL = 3

class histVarType:
    DV      = 1
    DV_NTRK = 2
    JET     = 3
    TRK     = 4
    NONE    = 5

class lineStyleType:
    ALL  = 1
    CTAU = 2
    XDM  = 3
    MOOD = 4
    MIX  = 5


## --- GET SAMPLES --- ##
def getSamples( inSgnlDir, inBkgdDir, inDataDir, sgnlType, bkgdType, dataType, hlsty = lineStyleType.ALL ):

    sampleNames, sampleTypes, sampleDicts, sampleFiles = [], [], [], []
    
    ## get signal files
    if len( sgnlType ) > 0:
        sgnlTypes = sgnlType.split(',')
        for sgnlType in sgnlTypes:
            if ':' in sgnlType:
                sgnlName = sgnlType.split(':')[0]
                sgnlType = sgnlType.split(':')[-1]
            else:
                sgnlName = sgnlType
            sampleNames   .append( sgnlName )
            sampleTypes   .append( sampleType.SGNL )
            sampleDicts   .append( getSampleDict( sgnlName, sampleType.SGNL, hlsty ) )
            sampleFiles   .append( getFileList( inSgnlDir, sgnlType.split('+') ) )

    ## get background files
    if len( bkgdType ) > 0:
        bkgdTypes = bkgdType.split(',')
        for bkgdType in bkgdTypes:
            if ':' in bkgdType:
                bkgdName = bkgdType.split(':')[0]
                bkgdType = bkgdType.split(':')[-1]
            else:
                bkgdName = bkgdType
            sampleNames   .append( bkgdName )
            sampleTypes   .append( sampleType.BKGD )
            sampleDicts   .append( getSampleDict( bkgdName, sampleType.BKGD, hlsty ) )
            sampleFiles   .append( getFileList( inBkgdDir, bkgdType.split('+') ) )

    ## get data files
    if len( dataType ) > 0:
        dataTypes = dataType.split(',')
        for dataType in dataTypes:
            if ':' in dataType:
                dataName = dataType.split(':')[0]
                dataType = dataType.split(':')[-1]
            else:
                dataName = dataType
            sampleNames   .append( dataName )
            sampleTypes   .append( sampleType.DATA )
            sampleDicts   .append( getSampleDict( dataName, sampleType.DATA, hlsty ) )
            sampleFiles   .append( getFileList( inDataDir, dataType.split('+') ) )

    return sampleNames, sampleTypes, sampleDicts, sampleFiles



## --- GET SAMPLE HISTOGRAMS --- ##
def getSampleHists( histList, subdir, sampleFiles, sampleNames, sampleTypes, scaleData = False, metadir = None, outdir = None ):
    
    # get list of histograms common to all files in sample
    sampleHists = []
    histList = histList.split(',')
    for tag in histList:
        exclTag = ""
        if ':' in tag:
            inclTag = tag.split(':')[0]
            exclTag = tag.split(':')[-1]
        else:
            inclTag = tag
        tmpHists = getHistList( sampleFiles, subdir, inclTag.split('+'), exclTag.split('+') )
        for iH, hist in enumerate( tmpHists ):
            if hist not in sampleHists:
                sampleHists.append( hist )

    # get histogram objects
    hists = []
    for iS, sampleName in enumerate( sampleNames ):
        combHists = getHists( sampleName, sampleTypes[iS], sampleFiles[iS], sampleHists, subdir, scaleData, metadir, outdir )
        hists.append( combHists )

    return sampleHists, hists



## --- RETRIEVE FILE LIST --- ##
def getFileList( histDir, histTag ):
    
    # get list of files matching hist-tags in hist-directory
    histFiles = []
    for f in os.listdir( histDir ):
        passedTags = True
        for tag in histTag:
            orTags = tag.split('=')
            if not any( ot in f for ot in orTags ):
                passedTags = False
        if passedTags:
            histFiles.append( os.path.join( histDir, f ) )

    return histFiles



## --- RETRIEVE HISTOGRAM LIST --- ##
def getHistList( histFiles, subdir, inTag, exTag ):
    
    allFiles = sum( histFiles, [] ) # combine into single list
    allHists = []
    hists    = []

    # loop over files and get list of histograms (keys)
    for file in allFiles:
        allHists.append( [] ) # save list of histograms for each file
        f = ROOT.TFile( file, "READ" )
        d = f.GetDirectory( subdir )
        if not d:
            print ( "ERROR: TDirectory " + subdir + " not in TFile " + file + ". Exiting." )
            exit(1)
        # grab histograms of interest
        for key in d.GetListOfKeys():
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
            # always get metadata hists no matter what
            if "MetaData" in key.GetName():
                passedInTags = True
                passedExTags = True
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
def getHists( sname, stype, flist, hlist, subdir, scaleData = False, metadir = None, outdir = None ):
    
    # combine common histograms across all files in sample
    CombinedHists = []
    data_initSumw = []
    for iFile, file in enumerate( flist ):
        f = ROOT.TFile.Open( file, "READ" )
        f.cd( subdir )
        for iHist, hist in enumerate( hlist ):
            h = f.CurrentDirectory().Get( hist )

            # scale ???

            # get initial sum of weights for data files -- needed to scale to full lumi
            if stype == sampleType.DATA and "MetaData_EventCount" in h.GetName():
                data_initSumw.append( h.GetBinContent(3) )

            # combine histograms
            if iFile == 0:
                CombinedHists.append( h.Clone( sname + "_" + h.GetName() ) ) # make new combined histogram
                CombinedHists[-1].SetDirectory(0)
            else:
                CombinedHists[iHist].Add(h) # add to existing histogram

            if "efficiency" in h.GetName() or "cutflowEff" in h.GetName() or "cutflowTotEff" in h.GetName(): # change back to 'efficiency'
                CombinedHists[iHist].Scale(1./len(flist)) # average efficiency histograms over all files

        f.Close()

    # scale data to full Run2 (if running over subset)
    if scaleData and stype == sampleType.DATA:
        dataScale = getDataScale( data_initSumw, getDataNEvents( metadir ) )
        for hist in CombinedHists:
            # skip metadata hists -- don't want them scaled...
            if "MetaData" in hist.GetName(): continue
            hist.Scale( dataScale )
    
    # add overflow/underflow

    # save
    if outdir:
        if not os.path.exists( outdir ):
            os.makedirs( outdir )
        f = ROOT.TFile( os.path.join( outdir, sname + ".root" ), "recreate" )
        if not f.GetDirectory( subdir ):
            f.mkdir( subdir )
        f.cd( subdir )
        for hist in CombinedHists:
            hist.Write()

    return CombinedHists



## --- REARRANGE HISTOGRAM LISTS --- ##
# --> for plotting same histograms from different samples against each other
def getNewHists( stypes, histNames, hists ):
    
    newHists = []
    for iName, name in enumerate( histNames ):
        newHists.append( [] )
        for iType, type in enumerate( stypes ):
            newHists[-1].append( hists[iType][iName] )
    return newHists

# --> for plotting different histograms from same or different samples against each other
def getVarHists( stypes, histNames, hists, histVars ):
    varHists, baseNames, baseNames_pre, baseNames_post = [], [], [], []
    if len( histVars ) > 0:
        histVars = histVars.split(',')
        for iType, stype in enumerate( stypes ):
            for iName, name in enumerate( histNames ):
                getBaseHists = False
                for iVar, var in enumerate( histVars ):
                    if var in name:
                        baseName_pre  = '_'.join( name.split(var)[:-1] )
                        baseName_post = '_'.join( name.split(var)[1:]  )
                        if baseName_pre.endswith('_'):
                            baseName_pre = baseName_pre[:-1]
                        if baseName_post.startswith('_'):
                            baseName_post = baseName_post[1:]
                        baseName = baseName_pre
                        if baseName and baseName_post:
                            baseName += "_"
                        baseName += baseName_post
                        if baseName not in baseNames:
                            baseNames      .append( baseName      )
                            baseNames_pre  .append( baseName_pre  )
                            baseNames_post .append( baseName_post )
                            varHists.append( [] )
            for iBase, base in enumerate( baseNames ):
                for iVar, var in enumerate( histVars ):
                    for iName, name in enumerate( histNames ):
                        hname = baseNames_pre[iBase]
                        if hname:
                            hname += "_"
                        hname += var
                        if baseNames_post[iBase]:
                            hname += "_" + baseNames_post[iBase]
                        if hname == name:
                            varHists[iBase].append( hists[iType][iName] )
                
    return varHists, baseNames



## --- DO NORMALIZATION --- ##
def doNorm( hist, norm_factor = 1 ):
    # skip cutflow, count, and efficiency histograms
    if "cutflow"    in hist.GetName().lower():
        return
    if "count"      in hist.GetName().lower():
        return
    if "efficiency" in hist.GetName().lower():
        return
    if "cuteff"     in hist.GetName().lower():
        return
    if "eff"        in hist.GetName().lower():
        return
    if "accept"     in hist.GetName().lower():
        return

    # add other histos to skip as needed...

    # add handling of s/b ??

    hist.Scale( norm_factor / hist.Integral() )

    return



## --- CONFIGURE LEGEND --- ##
def configLeg( stypes, sdicts, lslen, xint = 0.008, yint = 0.030, doPlotTypes = [], xl_override = None ):
    
    max_len  = 0
    nEntries = 0
    for iS, stype in enumerate( stypes ):
        if len( doPlotTypes ) > 0:
            if not doPlotTypes[iS]: continue
        legStr = setLegStr( stype, sdicts[iS], lslen )
        if len(legStr) > max_len:
            max_len = len(legStr)
        nEntries += 1

    xr   = 0.870
    yt   = 0.870
    xl   = xr - xint * max_len
    yb   = yt - yint * nEntries

    if xl_override:
        xl = xl_override
    
    leg = ROOT.TLegend( xl, yb, xr, yt )
    leg.SetBorderSize(0)
    #leg.SetFillColorAlpha(0,0)

    return leg


## --- SET STRING FOR LEGEND ENTRY --- ##
def setLegStr( stype, sdict, lslen ):
    
    legend_string = ""
    
    # --> signal samples
    if stype == sampleType.SGNL:
        # long strings: full model, xdm, ctau info
        if   lslen == legStrLen.LONG:
            legend_string = "Model " + sdict["model"] + " (#pi_{dm} = " + str(sdict["pidm"]) + \
            " GeV); X_{dm} = " + str(sdict["xdm"]) + " GeV; c#tau = " + str(sdict["ctau"]) + " mm"
        # long strings w/o pid mass 
        elif lslen == legStrLen.LONG_SM:
            legend_string = "Model " + sdict["model"] + "; X_{dm} = " + str(sdict["xdm"]) + \
              " GeV; c#tau = " + str(sdict["ctau"]) + " mm"
        # mid-length strings: model, xdm
        elif lslen == legStrLen.MID0:
            legend_string = "Model " + sdict["model"] + " (#pi_{dm} = " + str(sdict["pidm"]) + \
            " GeV); X_{dm} = " + str(sdict["xdm"]) + " GeV"
        elif lslen == legStrLen.MID0_SM:
            legend_string = "Model " + sdict["model"] + "; X_{dm} = " + str(sdict["xdm"]) + " GeV"
        # mid-length strings: model, ctau
        elif lslen == legStrLen.MID1:
            legend_string = "Model " + sdict["model"] + " (#pi_{dm} = " + str(sdict["pidm"]) + \
            " GeV); c#tau = " + str(sdict["ctau"]) + " mm"
        elif lslen == legStrLen.MID1_SM:
            legend_string = "Model " + sdict["model"] + "; c#tau = " + str(sdict["ctau"]) + " mm"
        # mid-length strings: model
        elif lslen == legStrLen.MID2:
            legend_string = "Model " + sdict["model"] + " (#pi_{dm} = " + str(sdict["pidm"]) + " GeV)"
        elif lslen == legStrLen.MID2_SM:
            legend_string = "Model " + sdict["model"]
        # mid-length strings: xdm, ctau
        elif lslen == legStrLen.MID3:
            legend_string = "X_{dm} = " + str(sdict["xdm"]) + " GeV; c#tau = " + str(sdict["ctau"]) + " mm"
        # mid-length strings: ctau
        elif lslen == legStrLen.MID4:
            legend_string = "c#tau = " + str(sdict["ctau"]) + " mm"
        # short strings: abbreviated
        elif lslen == legStrLen.SHORT:
            legend_string = "Mod" + sdict["model"] + "_" + str(sdict["pidm"]) + "_" + \
              str(sdict["xdm"]) + "_" + str(sdict["ctau"])
        ## fixed vs running coupling
        if sdict["coupling"]:
            legend_string = sdict["coupling"] + " coupling"
    # --> background samples
    elif stype == sampleType.BKGD:
        if   lslen == legStrLen.LONG or lslen == legStrLen.LONG_SM:
            legend_string = sdict["sample"] + " MC background (" + sdict["jzxw"] + ")"
        else:
            legend_string = sdict["jzxw"] + " MC bkgd"
    # --> data samples
    elif stype == sampleType.DATA:
        legend_string = sdict["year"]

    return legend_string


## --- SET STRING FOR MULTIVARIATE LEGEND ENTRY --- ##
def setMultiLegStr( hname, stype, sdict, hvar, doMultiSmpl = False, doSvBStr = False, lslen = 11 ):
    legend_string = ""

    if hvar == histVarType.DV:
        if doSvBStr:
            if "darkPion".lower() in hname.lower():
                legend_string = "dark pion DV"
            elif "kshort".lower() in hname.lower():
                legend_string = "k-short DV"
            elif "nomatch".lower() in hname.lower():
                legend_string = "unmatched DV"
            else:
                legend_string = "DV"
        else:
            if "bare"    .lower() in hname.lower():
                if legend_string:
                    legend_string += " "
                legend_string += "bare"
            if "clean"   .lower() in hname.lower():
                if legend_string:
                    legend_string += " "
                legend_string += "clean"
            if "filt"    .lower() in hname.lower():
                if legend_string:
                    legend_string += " "
                legend_string += "filt"
            if "byJet"   .lower() in hname.lower():
                if legend_string:
                    legend_string += " "
                legend_string += "by-jet"
            if "byNJet"  .lower() in hname.lower():
                if legend_string:
                    legend_string += " "
                legend_string += "by-N-lead-jet"
            if "fiduc"   .lower() in hname.lower():
                if legend_string:
                    legend_string += " "
                legend_string += "fiduc"
            if "ksm"     .lower() in hname.lower():
                if legend_string:
                    legend_string += " "
                legend_string += "ksm"
            # add other cuts
            if "good"    .lower() in hname.lower():
                if legend_string:
                    legend_string += " "
                legend_string += "good"
            if "darkPion".lower() in hname.lower():
                if legend_string:
                    legend_string += " "
                legend_string += "dark pion"
            if "kshort"  .lower() in hname.lower():
                if legend_string:
                    legend_string += " "
                legend_string += "k-short"
            if "nomatch" .lower() in hname.lower():
                if legend_string:
                    legend_string += " "
                legend_string += "unmatched"
            if not legend_string or len(legend_string) > 100:
                legend_string = hname.split('_')[1]
            else:
                legend_string += " DV"
    elif hvar == histVarType.DV_NTRK:
        if hname.split('_')[1].startswith("2trk"):
            legend_string = "2-track DV"
        elif hname.split('_')[1].startswith("3trk"):
            legend_string = "3-track DV"
        elif hname.split('_')[1].startswith("4trk"):
            legend_string = "4-track DV"
        elif hname.split('_')[1].startswith("5trk"):
            legend_string = "5-plus-track DV"
        else:
            legend_string = hname.split('_')[1]
    elif hvar == histVarType.JET:
        if "lead"      .lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "lead"
        if "darkMatch" .lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "dark-matched"
        if "nomatch"   .lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "unmatched"
        if not legend_string:
            legend_string = hname.split('_')[1]
        else:
            legend_string += " jet"
    elif hvar == histVarType.TRK:
        if "desc" not in hname.lower():
            if   "reco" in hname.lower():
                legend_string = "inclusive tracks"
            elif "std"  in hname.lower():
                legend_string = "standard tracks"
            elif "lrt"  in hname.lower():
                legend_string = "large-radius tracks"
        else:
            legend_string = "truth tracks"
            if   "recodesc" in hname.lower():
                legend_string = "reconstructed " + legend_string
            elif "vtxdesc" in hname.lower():
                legend_string = "vertexed "      + legend_string
                if   "loosevtxdesc"  in hname.lower():
                    legend_string = "loose "  + legend_string
                elif "mediumvtxdesc" in hname.lower():
                    legend_string = "medium " + legend_string
                elif "tightvtxdesc"  in hname.lower():
                    legend_string = "tight "  + legend_string
                                                 

    if doMultiSmpl:
        legend_string += " (" + setLegStr( stype, sdict, lslen ) + ")"

    return legend_string



## --- GET 2D MAX BIN CONTENT --- ##
def getMaxBinContent( hist ):
    max_entry = 0
    for i in range( 0, hist.GetNbinsX() ):
        for j in range( 0, hist.GetNbinsY() ):
            entry = hist.GetBinContent( i+1, j+1 )
            if entry > max_entry:
                max_entry = entry
                
    return max_entry



## --- SET X-AXIS TITLE --- ##
def setXaxisTitle( hist, doMulti = False, multiObjStr = "", hvar = histVarType.DV, doSOverB = False, jetType = "EMTopo" ):
    xtitle = hist.GetXaxis().GetTitle()

    if doMulti:
        histName = hist.GetName().split('_')[1]
        if   hvar == histVarType.DV or hvar == histVarType.DV_NTRK:
            dvStr = "DV"
            if multiObjStr: dvStr = multiObjStr + " " + dvStr
            xtitle = dvStr  + xtitle.split('DV') [-1]
            if   histName.startswith("2trk"):
                xtitle = "2-track " + xtitle
            elif histName.startswith("3trk"):
                xtitle = "3-track " + xtitle
            elif histName.startswith("4trk"):
                xtitle = "4-track " + xtitle
            elif histName.startswith("5trk"):
                xtitle = "5-plus-track " + xtitle
        elif hvar == histVarType.JET:
            jetStr = jetType + " jet"
            if multiObjStr: jetStr = multiObjStr + " " + jetStr
            oldJetStr = jetType + " jet"
            if "darkMatch".lower() in histName.lower(): oldJetStr = "dark-matched " + oldJetStr
            if "nomatch"  .lower() in histName.lower(): oldJetStr = "unmatched "    + oldJetStr
            if "lead"     .lower() in histName.lower(): oldJetStr = "lead "         + oldJetStr
            xtitle = xtitle.replace( oldJetStr, jetStr )
        elif hvar == histVarType.TRK:
            if "standard"       in xtitle:
                xtitle = xtitle.split('standard')    [-1]
            elif "large-radius" in xtitle:
                xtitle = xtitle.split('large-radius')[-1]
            else:
                xtitle = xtitle
        else:
            xtitle = xtitle

    if doSOverB:
        xtitle += " (S/B)"

    return xtitle



## --- CONFIGURE PLOT TEXT --- ##
def configText( titleStr, region ):
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
    if   ( region == "search-minus-one" ):
        regstr = "SEARCH-MINUS-ONE REGION"
    elif ( region == "search" ):
        regstr = "SEARCH REGION"
    elif ( region == "valid" ):
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



## --- SCALE SUB DATASET TO FULL --- ##
def getDataScale( nSub, nTot ):
    nsum = 0
    for nsub in nSub:
        nsum += nsub
    nScale = nTot / nsum
    
    return nScale



## --- GET TOTAL N-EVENTS FOR FULL RUN2 DATA --- ##
def getDataNEvents( metadir = None ):

    # --> from total number of initial sum of weights in all data samples -- maybe only includes events passing filter?
    nInit = 0
    nSel  = 0
    if metadir:
        for item in os.listdir( metadir ):
            # --> add error handling; don't crash if file can't be opened
            f = ROOT.TFile.Open( os.path.join( metadir, item ), "READ" ) 
            for key in f.GetListOfKeys():
                if "MetaData_EventCount" in key.GetName():
                    h = f.Get( key.GetName() )
                    nInit += h.GetBinContent(3)
                    nSel  += h.GetBinContent(4)

    # not sure what we're supposed to scale to -- nInit (unskimmed daod_rpvll)? nSel (skimmed daod_exot23)?
    # --> shouldn't matter if we use nInit or nSel, since we'll use same count in numerator, so scale will be the same...
    n = nInit

    return n




## --- SET SAMPLE INFO DICTIONARIES --- ##
def getSampleDict( sname, stype, hlsty ):
    sampledict = {}
    # signal sample dictionary
    if stype == sampleType.SGNL:
        dictlist = []
        if   "312001" in sname or "A_1400_300" in sname:
            dictlist = [ 312001, "A",   5, 1400, 300 ]
        elif "312002" in sname or "A_1400_150" in sname:
            dictlist = [ 312002, "A",   5, 1400, 150 ]
        elif "312003" in sname or "A_1400_75"  in sname:
            dictlist = [ 312003, "A",   5, 1400,  75 ]
        elif "312004" in sname or "A_1400_20"  in sname:
            dictlist = [ 312004, "A",   5, 1400,  20 ]
        elif "312005" in sname or "A_1400_5"   in sname:
            dictlist = [ 312005, "A",   5, 1400,   5 ]
        elif "312006" in sname or "A_1400_2"   in sname and "A_1400_20" not in sname:
            dictlist = [ 312006, "A",   5, 1400,   2 ]
        elif "312007" in sname or "A_1000_300" in sname:
            dictlist = [ 312007, "A",   5, 1000, 300 ]
        elif "312008" in sname or "A_1000_150" in sname or "ModA_run" in sname or "ModA_fix" in sname:
            dictlist = [ 312008, "A",   5, 1000, 150 ]
        elif "312009" in sname or "A_1000_75"  in sname:
            dictlist = [ 312009, "A",   5, 1000,  75 ]
        elif "312010" in sname or "A_1000_5"   in sname:
            dictlist = [ 312010, "A",   5, 1000,   5 ]
        elif "312011" in sname or "A_1000_2"   in sname and "A_1000_20" not in sname:
            dictlist = [ 312011, "A",   5, 1000,   2 ]
        elif "312012" in sname or "A_1000_1"   in sname and "A_1000_150" not in sname:
            dictlist = [ 312012, "A",   5, 1000,   1 ]
        elif "312013" in sname or "A_600_300"  in sname:
            dictlist = [ 312013, "A",   5,  600, 300 ]
        elif "312014" in sname or "A_600_150"  in sname:
            dictlist = [ 312014, "A",   5,  600, 150 ]
        elif "312015" in sname or "A_600_20"   in sname:
            dictlist = [ 312015, "A",   5,  600,  20 ]
        elif "312016" in sname or "A_600_2"    in sname and "A_600_20" not in sname:
            dictlist = [ 312016, "A",   5,  600,   2 ]
        elif "312017" in sname or "A_600_1"    in sname and "A_600_150" not in sname:
            dictlist = [ 312017, "A",   5,  600,   1 ]
        elif "312018" in sname or "A_600_0p5"  in sname:
            dictlist = [ 312018, "A",   5,  600, 0.5 ]
        elif "312019" in sname or "B_1400_300" in sname:
            dictlist = [ 312019, "B",   2, 1400, 300 ]
        elif "312020" in sname or "B_1400_150" in sname:
            dictlist = [ 312020, "B",   2, 1400, 150 ]
        elif "312021" in sname or "B_1400_75"  in sname:
            dictlist = [ 312021, "B",   2, 1400,  75 ]
        elif "312022" in sname or "B_1400_20"  in sname:
            dictlist = [ 312022, "B",   2, 1400,  20 ]
        elif "312023" in sname or "B_1400_5"   in sname:
            dictlist = [ 312023, "B",   2, 1400,   5 ]
        elif "312024" in sname or "B_1400_2"   in sname and "B_1400_20" not in sname:
            dictlist = [ 312024, "B",   2, 1400,   2 ]
        elif "312025" in sname or "B_1000_300" in sname:
            dictlist = [ 312025, "B",   2, 1000, 300 ]
        elif "312026" in sname or "B_1000_150" in sname:
            dictlist = [ 312026, "B",   2, 1000, 150 ]
        elif "312027" in sname or "B_1000_75"  in sname:
            dictlist = [ 312027, "B",   2, 1000,  75 ]
        elif "312028" in sname or "B_1000_5"   in sname or "ModB_run" in sname or "ModB_fix" in sname:
            dictlist = [ 312028, "B",   2, 1000,   5 ]
        elif "312029" in sname or "B_1000_2"   in sname and "B_1000_20" not in sname:
            dictlist = [ 312029, "B",   2, 1000,   2 ]
        elif "312030" in sname or "B_1000_1"   in sname and "B_1000_150" not in sname:
            dictlist = [ 312030, "B",   2, 1000,   1 ]
        elif "312031" in sname or "B_600_300"  in sname:
            dictlist = [ 312031, "B",   2,  600, 300 ]
        elif "312032" in sname or "B_600_150"  in sname:
            dictlist = [ 312032, "B",   2,  600, 150 ]
        elif "312033" in sname or "B_600_20"   in sname:
            dictlist = [ 312033, "B",   2,  600,  20 ]
        elif "312034" in sname or "B_600_2"    in sname and "B_600_20" not in sname:
            dictlist = [ 312034, "B",   2,  600,   2 ]
        elif "312035" in sname or "B_600_1"    in sname and "B_600_150" not in sname:
            dictlist = [ 312035, "B",   2,  600,   1 ]
        elif "312036" in sname or "B_600_0p5"  in sname:
            dictlist = [ 312036, "B",   2,  600, 0.5 ]
        elif "312037" in sname or "C_1400_300" in sname:
            dictlist = [ 312037, "C",  10, 1400, 300 ]
        elif "312038" in sname or "C_1400_150" in sname:
            dictlist = [ 312038, "C",  10, 1400, 150 ]
        elif "312039" in sname or "C_1400_75"  in sname:
            dictlist = [ 312039, "C",  10, 1400,  75 ]
        elif "312040" in sname or "C_1400_20"  in sname:
            dictlist = [ 312040, "C",  10, 1400,  20 ]
        elif "312041" in sname or "C_1400_5"   in sname:
            dictlist = [ 312041, "C",  10, 1400,   5 ]
        elif "312042" in sname or "C_1400_2"   in sname and "C_1400_20" not in sname:
            dictlist = [ 312042, "C",  10, 1400,   2 ]
        elif "312043" in sname or "C_1000_300" in sname:
            dictlist = [ 312043, "C",  10, 1000, 300 ]
        elif "312044" in sname or "C_1000_150" in sname:
            dictlist = [ 312044, "C",  10, 1000, 150 ]
        elif "312045" in sname or "C_1000_75"  in sname:
            dictlist = [ 312045, "C",  10, 1000,  75 ]
        elif "312046" in sname or "C_1000_5"   in sname:
            dictlist = [ 312046, "C",  10, 1000,   5 ]
        elif "312047" in sname or "C_1000_2"   in sname and "C_1000_20" not in sname:
            dictlist = [ 312047, "C",  10, 1000,   2 ]
        elif "312048" in sname or "C_1000_1"   in sname and "C_1000_150" not in sname:
            dictlist = [ 312048, "C",  10, 1000,   1 ]
        elif "312049" in sname or "C_600_300"  in sname:
            dictlist = [ 312049, "C",  10,  600, 300 ]
        elif "312050" in sname or "C_600_150"  in sname:
            dictlist = [ 312050, "C",  10,  600, 150 ]
        elif "312051" in sname or "C_600_20"   in sname:
            dictlist = [ 312051, "C",  10,  600,  20 ]
        elif "312052" in sname or "C_600_2"    in sname and "C_600_20" not in sname:
            dictlist = [ 312052, "C",  10,  600,   2 ]
        elif "312053" in sname or "C_600_1"    in sname and "C_600_150" not in sname:
            dictlist = [ 312053, "C",  10,  600,   1 ]
        elif "312054" in sname or "C_600_0p5"  in sname:
            dictlist = [ 312054, "C",  10,  600, 0.5 ]
        elif "312055" in sname or "D_1400_300" in sname:
            dictlist = [ 312055, "D",  20, 1400, 300 ]
        elif "312056" in sname or "D_1400_150" in sname:
            dictlist = [ 312056, "D",  20, 1400, 150 ]
        elif "312057" in sname or "D_1400_75"  in sname:
            dictlist = [ 312057, "D",  20, 1400,  75 ]
        elif "312058" in sname or "D_1400_20"  in sname:
            dictlist = [ 312058, "D",  20, 1400,  20 ]
        elif "312059" in sname or "D_1400_5"   in sname:
            dictlist = [ 312059, "D",  20, 1400,   5 ]
        elif "312060" in sname or "D_1400_2"   in sname and "D_1400_20" not in sname:
            dictlist = [ 312060, "D",  20, 1400,   2 ]
        elif "312061" in sname or "D_1000_300" in sname:
            dictlist = [ 312061, "D",  20, 1000, 300 ]
        elif "312062" in sname or "D_1000_150" in sname:
            dictlist = [ 312062, "D",  20, 1000, 150 ]
        elif "312063" in sname or "D_1000_75"  in sname:
            dictlist = [ 312063, "D",  20, 1000,  75 ]
        elif "312064" in sname or "D_1000_5"   in sname:
            dictlist = [ 312064, "D",  20, 1000,   5 ]
        elif "312065" in sname or "D_1000_2"   in sname and "D_1000_20" not in sname:
            dictlist = [ 312065, "D",  20, 1000,   2 ]
        elif "312066" in sname or "D_1000_1"   in sname and "D_1000_150" not in sname:
            dictlist = [ 312066, "D",  20, 1000,   1 ]
        elif "312067" in sname or "D_600_300"  in sname:
            dictlist = [ 312067, "D",  20,  600, 300 ]
        elif "312068" in sname or "D_600_150"  in sname:
            dictlist = [ 312068, "D",  20,  600, 150 ]
        elif "312069" in sname or "D_600_20"   in sname:
            dictlist = [ 312069, "D",  20,  600,  20 ]
        elif "312070" in sname or "D_600_2"    in sname and "D_600_20" not in sname:
            dictlist = [ 312070, "D",  20,  600,   2 ]
        elif "312071" in sname or "D_600_1"    in sname and "D_600_150" not in sname:
            dictlist = [ 312071, "D",  20,  600,   1 ]
        elif "312072" in sname or "D_600_0p5"  in sname:
            dictlist = [ 312072, "D",  20,  600, 0.5 ]
        elif "312073" in sname or "E_1400_300" in sname:
            dictlist = [ 312073, "E", 0.8, 1400, 300 ]
        elif "312074" in sname or "E_1400_150" in sname:
            dictlist = [ 312074, "E", 0.8, 1400, 150 ]
        elif "312075" in sname or "E_1400_75"  in sname:
            dictlist = [ 312075, "E", 0.8, 1400,  75 ]
        elif "312076" in sname or "E_1400_20"  in sname:
            dictlist = [ 312076, "E", 0.8, 1400,  20 ]
        elif "312077" in sname or "E_1400_5"   in sname:
            dictlist = [ 312077, "E", 0.8, 1400,   5 ]
        elif "312078" in sname or "E_1400_2"   in sname and "E_1400_20" not in sname:
            dictlist = [ 312078, "E", 0.8, 1400,   2 ]
        elif "312079" in sname or "E_1000_300" in sname:
            dictlist = [ 312079, "E", 0.8, 1000, 300 ]
        elif "312080" in sname or "E_1000_150" in sname:
            dictlist = [ 312080, "E", 0.8, 1000, 150 ]
        elif "312081" in sname or "E_1000_75"  in sname:
            dictlist = [ 312081, "E", 0.8, 1000,  75 ]
        elif "312082" in sname or "E_1000_5"   in sname:
            dictlist = [ 312082, "E", 0.8, 1000,   5 ]
        elif "312083" in sname or "E_1000_2"   in sname and "E_1000_20" not in sname:
            dictlist = [ 312083, "E", 0.8, 1000,   2 ]
        elif "312084" in sname or "E_1000_1"   in sname and "E_1000_150" not in sname:
            dictlist = [ 312084, "E", 0.8, 1000,   1 ]
        elif "312085" in sname or "E_600_300"  in sname:
            dictlist = [ 312085, "E", 0.8,  600, 300 ]
        elif "312086" in sname or "E_600_150"  in sname:
            dictlist = [ 312086, "E", 0.8,  600, 150 ]
        elif "312087" in sname or "E_600_20"   in sname:
            dictlist = [ 312087, "E", 0.8,  600,  20 ]
        elif "312088" in sname or "E_600_2"    in sname and "E_600_20" not in sname:
            dictlist = [ 312088, "E", 0.8,  600,   2 ]
        elif "312089" in sname or "E_600_1"    in sname and "E_600_150" not in sname:
            dictlist = [ 312089, "E", 0.8,  600,   1 ]
        elif "312090" in sname or "E_600_0.5"  in sname:
            dictlist = [ 312090, "E", 0.8,  600, 0.5 ]
            
        # set line attributes and color palettes
        color   = ROOT.kWhite
        palette = texec_default()

        # --> set line style by mediator mass
        if   dictlist[3] == 1400:
            style = 1
        elif dictlist[3] == 1000:
            style = 3
        elif dictlist[3] == 600:
            style = 7

        # --> set color/style of every point or every model - mediator mass point (all lifetimes the same)
        if   hlsty == lineStyleType.ALL or hlsty == lineStyleType.CTAU or hlsty == lineStyleType.XDM:
            # set line color / palette by model
            col_ix = 0
            if   dictlist[1] == "A":
                col_ix = 0
            elif dictlist[1] == "B":
                col_ix = 1
            elif dictlist[1] == "C":
                col_ix = 2
            elif dictlist[1] == "D":
                col_ix = 3
            elif dictlist[1] == "E":
                col_ix = 4
            color   = sgnlColors()[col_ix]
            palette = texec_sgnl()[col_ix]
            if  hlsty == lineStyleType.CTAU:
                # vary base colors by lifetime
                if dictlist[0] % 6 == 0:
                    color = color
                elif dictlist[0] % 6 == 1:
                    color = color + 1
                elif dictlist[0] % 6 == 2:
                    color = color + 2
                elif dictlist[0] % 6 == 3:
                    color = color +3
                elif dictlist[0] % 6 == 4:
                    color = color - 1
                elif dictlist[0] % 6 == 5:
                    color = color - 2
            elif hlsty == lineStyleType.XDM:
                # vary base color by mediator mass
                if   dictlist[3] == 1400:
                    color = varSgnlColors()[col_ix][0]
                elif dictlist[3] == 1000:
                    color = varSgnlColors()[col_ix][1]
                elif dictlist[3] == 600:
                    color = varSgnlColors()[col_ix][2]
        # --> set color/style of every model point
        elif hlsty == lineStyleType.MOD:
            if   dictlist[0] % 6 == 1:
                color   = sgnlColors()[0]
                palette = texec_sgnl()[0]
            elif dictlist[0] % 6 == 2:
                color   = sgnlColors()[1]
                palette = texec_sgnl()[1]
            elif dictlist[0] % 6 == 3:
                color   = sgnlColors()[2]
                palette = texec_sgnl()[2]
            elif dictlist[0] % 6 == 4:
                color   = sgnlColors()[3]
                palette = texec_sgnl()[3]
            elif dictlist[0] % 6 == 5:
                color   = sgnlColors()[4]
                palette = texec_sgnl()[4]
            elif dictlist[0] % 6 == 0:
                color   = sgnlColors()[5]
                palette = texec_sgnl()[5]
        # --> set color/style of every mediator mass - lifetime point (same for all models)
        elif hlsty == lineStyleType.MIX:
            if   dictlist[3] == 1400:
                color = sgnlColors()[0]
                palette = texec_sgnl()[0]
            elif dictlist[3] == 1000:
                color = sgnlColors()[1]
                palette = texec_sgnl()[1]
            elif dictlist[3] == 600:
                color = sgnlColors()[2]
                palette = texec_sgnl()[2]
            if   dictlist[0] % 6 == 1:
                style = 1
            elif dictlist[0] % 6 == 2:
                style = 3
            elif dictlist[0] % 6 == 3:
                style = 4
            elif dictlist[0] % 6 == 4:
                style = 6
            elif dictlist[0] % 6 == 5:
                style = 7
            elif dictlist[0] % 6 == 0:
                style = 9
            
        # --> set specific colors / styles for truth fixed vs running coupling plots
        coupling = ""
        if   "ModA_run" in sname or "ModB_run" in sname or "ModA_fix" in sname or "ModB_fix" in sname:
            if   "run"  in sname:
                color     = sgnlColors()[0]
                palette   = texec_sgnl()[0]
                coupling  = "running"
            elif "fix"  in sname:
                color     = sgnlColors()[2]
                palette   = texec_sgnl()[2]
                coupling  = "fixed"
            if   "ModA" in sname:
                style     = 1
            elif "ModB" in sname:
                style     = 3
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
            "coupling" : coupling,    # running or fixed gauge coupling
        }
    # background sample dictionary
    if stype == sampleType.BKGD:
        dictlist = []
        color    = bkgdColors()[0]
        palette  = texec_bkgd()[0]
        style    = 1
        if "361024" in sname or "JZ4W" in sname:
            dictlist = [ 361024, "Pythia dijet", "JZ4W", 400, 800 ]
            color    = bkgdColors()[0]
            palette  = texec_bkgd()[0]
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
    if stype == sampleType.DATA:
        dictlist = []
        yearlist = []
        color    = dataColors()[0]
        palette  = texec_data()[0]
        style    = 7
        if "15" in sname:
            yearlist.append( "15" )
            color   = dataColors()[0]
            palette = texec_data()[0]
        if "16" in sname:
            yearlist.append( "16" )
            color   = dataColors()[1]
            palette = texec_data()[1]
        if "17" in sname:
            yearlist.append( "17" )
            color   = dataColors()[2]
            palette = texec_data()[2]
        if "18" in sname:
            yearlist.append( "18" )
            color   = dataColors()[3]
            palette = texec_data()[3]
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



## --- SET LINE WIDTH --- ##
def setLineWidth( lstyle ):
    lwidth = 2
    if   lstyle == 3:
        lwidth = 4
    #elif lstyle == 7:
    #    lwidth = 3

    return lwidth


## --- SET COLORS / PALETTES --- ##
## --> colors
def sgnlColors():
    return [ ROOT.kRed, ROOT.kGreen + 1, ROOT.kBlue, ROOT.kViolet, ROOT.kOrange + 1, ROOT.kCyan+1 ]
# one base color per model; one line / marker style per Xdm; one color (close to base) per lifetime

def varSgnlColors():
    return [ [ ROOT.kRed,        ROOT.kRed    + 2, ROOT.kRed    - 6 ],
             [ ROOT.kGreen  + 1, ROOT.kGreen  + 4, ROOT.kGreen  - 5 ],
             [ ROOT.kBlue,       ROOT.kBlue   + 3, ROOT.kBlue   - 6 ],
             [ ROOT.kViolet,     ROOT.kViolet + 3, ROOT.kViolet - 8 ],
             [ ROOT.kOrange + 1, ROOT.kOrange + 3, ROOT.kOrange + 7 ] ]

def bkgdColors():
    return [ ROOT.kGray + 2 ]

def dataColors():
    return [ ROOT.kBlack, ROOT.kGray+3, ROOT.kGray+1, ROOT.kGray ]
# TEMP PLACEHOLDERS --> FIX

## --> palettes 
def sgnlPalette():
    return [ ROOT.kCherry, ROOT.kAvocado, ROOT.kDeepSea, ROOT.kFuchsia, ROOT.kDarkBodyRadiator, ROOT.kAquamarine ]

def bkgdPalette():
    return [ ROOT.kGreyScale ]

def dataPalette():
    return [ ROOT.kAlpine, ROOT.kAtlantic, ROOT.kPearl, ROOT.kCividis ]

## --> texecs
def texec_default():
    return ROOT.TExec( "texec_" + str(len(sgnlPalette())+1), "gStyle->SetPalette(kBird)" )

def texec_sgnl():
    texec_sgnl = []
    for iS, spal in enumerate( sgnlPalette() ):
        sgnlPalStr = "gStyle->SetPalette(" + str(sgnlPalette()[iS]) + ", 0, 0.3); TColor::InvertPalette();"
        texec_sgnl.append( ROOT.TExec( "sgnlEx_" + str(iS), sgnlPalStr ) )
    return texec_sgnl

def texec_bkgd():
    texec_bkgd = []
    for iB, bpal in enumerate( bkgdPalette() ):
        bkgdPalStr = "gStyle->SetPalette(" + str(bkgdPalette()[iB]) + ", 0, 0.5); TColor::InvertPalette();"
        texec_bkgd.append( ROOT.TExec( "bkgdEx_" + str(iB), bkgdPalStr ) )
    return texec_bkgd

def texec_data():
    texec_data = []
    for iD, dpal in enumerate( dataPalette() ):
        dataPalStr = "gStyle->SetPalette(" + str(dataPalette()[iD]) + ", 0, 0.5); TColor::InvertPalette();"
        texec_data.append( ROOT.TExec( "dataEx_" + str(iD), dataPalStr ) )
    return texec_data
