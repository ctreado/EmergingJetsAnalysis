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
    SHORT   = 10

class legSize:
    BIG   = 1
    MED   = 2
    SMALL = 3

class histVarType:
    DV      = 1
    DV_NTRK = 2
    # add NONE option ?? would want to update usage in if statements here; would need to update enum in plotEJsHistogram, too...


## --- GET SAMPLES --- ##
def getSamples( inSgnlDir, inBkgdDir, inDataDir, sgnlType, bkgdType, dataType ):

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
            sampleDicts   .append( getSampleDict( sgnlName, sampleType.SGNL ) )
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
            sampleDicts   .append( getSampleDict( bkgdName, sampleType.BKGD ) )
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
            sampleDicts   .append( getSampleDict( dataName, sampleType.DATA ) )
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
            print ( "ERROR: TDirectory not in TFile. Exiting." )
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

        f.Close()

    # scale data to full Run2 (if running over subset)
    if scaleData and stype == sampleType.DATA:
        dataScale = getDataScale( data_initSumw, getDataNEvents( metadir ) )
        for hist in CombinedHists:
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
    varHists, baseNames = [], []
    if len( histVars ) > 0:
        histVars = histVars.split(',')
        for iType, type in enumerate( stypes ):
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
    return varHists, baseNames



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
            " GeV); #chi_{dm} = " + str(sdict["xdm"]) + " GeV; c#tau = " + str(sdict["ctau"]) + " mm"
        # long strings w/o pid mass 
        elif lslen == legStrLen.LONG_SM:
            legend_string = "Model " + sdict["model"] + "; #chi_{dm} = " + str(sdict["xdm"]) + \
              " GeV; c#tau = " + str(sdict["ctau"]) + " mm"
        # mid-length strings: model, xdm
        elif lslen == legStrLen.MID0:
            legend_string = "Model " + sdict["model"] + " (#pi_{dm} = " + str(sdict["pidm"]) + \
            " GeV); #chi_{dm} = " + str(sdict["xdm"]) + " GeV"
        elif lslen == legStrLen.MID0_SM:
            legend_string = "Model " + sdict["model"] + "; #chi_{dm} = " + str(sdict["xdm"]) + " GeV"
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
            legend_string = "#chi_{dm} " + str(sdict["xdm"]) + " GeV; c#tau = " + str(sdict["ctau"]) + " mm"
        # short strings: abbreviated
        elif lslen == legStrLen.SHORT:
            legend_string = "Mod" + sdict["model"] + "_" + str(sdict["pidm"]) + "_" + \
              str(sdict["xdm"]) + "_" + str(sdict["ctau"])
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
def setMultiLegStr( hname, stype, sdict, hvar, doMultiSmpl = False ):
    legend_string = ""

    if hvar == histVarType.DV:
        if "byJet"     .lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "by-jet DV"
        if "byLeadJet" .lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "by-lead-jet DV"
        if "fiducial"  .lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "fiducial-cut DV"
        if "bareDV"    .lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "bare DV"
        if "cleanDV"   .lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "clean DV"
        if "filtDV"    .lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "filtered DV"
        if "darkPionDV".lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "dark-pion-decay matched DV"
        if "kshortDV"  .lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "k-short-decay matched DV"
        if "nomatchDV" .lower() in hname.lower():
            if legend_string:
                legend_string += " "
            legend_string += "unmatched DV"
        if not legend_string:
            legend_string = hname
    elif hvar == histVarType.DV_NTRK:
        if hname.startswith("2trk"):
            legend_string = "2-track DV"
        elif hname.startswith("3trk"):
            legend_string = "3-track DV"
        elif hname.startswith("4trk"):
            legend_string = "4-track DV"
        elif hname.startswith("5trk"):
            legend_string = "5-plus-track DV"
        else:
            legend_string = hname
    if doMultiSmpl:
        legend_string += " (" + setLegStr( stype, sdict, 10 ) + ")"
        
    #if doMultiSample:
    #    ... add sample info (maybe in parentheses); would need to add "doMultiSample" argument -->
    # --> # legend_string += " " + setLegStr( sampleType, sampleDict, False )

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
def setXaxisTitle( hist, doMulti = False, hvar = histVarType.DV ):
    xtitle = hist.GetXaxis().GetTitle()

    if doMulti:
        histName = hist.GetName().split('_')[1]
        if hvar == histVarType.DV:
            xtitle = "DV" + xtitle.split('DV')[-1]
            if   histName.startswith("2trk"):
                xtitle = "2-track " + xtitle
            elif histName.startswith("3trk"):
                xtitle = "3-track " + xtitle
            elif histName.startswith("4trk"):
                xtitle = "4-track " + xtitle
            elif histName.startswith("5trk"):
                xtitle = "5-plus-track " + xtitle
        elif hvar == histVarType.DV_NTRK:
            xtitle = "DV" + xtitle.split('DV')[-1]
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
def getDataNEvents( metadir = None, useInit = True ):
    
    # --> from COMA period stream reports -- maybe overcounting bad-physics events?
    n18 = 6400342575
    n17 = 5649254354
    n16 = 5387156693
    n15 = 1694552005
    nCOMA = n18 + n17 + n16 + n15

    # --> from total number of initial sum of weights in all data samples -- maybe only includes events passing filter?
    nInit = 0
    if metadir:
        for item in os.listdir( metadir ):
            f = ROOT.TFile.Open( os.path.join( metadir, item ), "READ" ) # --> add error handling; don't crash if file can't be opened
            for key in f.GetListOfKeys():
                if "MetaData_EventCount" in key.GetName():
                    h = f.Get( key.GetName() )
                    nInit += h.GetBinContent(3)

    # add argument to choose nCOMA or nInit --> nInit ~ 1/3 nCOMA ... which is right ???
    if useInit and nInit: n = nInit
    else:                 n = nCOMA

    return n




## --- SET SAMPLE INFO DICTIONARIES --- ##
def getSampleDict( sname, stype ):
    sampledict = {}
    # signal sample dictionary
    if stype == sampleType.SGNL:
        dictlist = []
        if   "312004" in sname or "ModelA" in sname and "1400" in sname and "20" in sname:
            dictlist = [ 312004, "A", 5, 1400, 20 ]
        elif "312008" in sname or "ModelA" in sname and "1000" in sname and "150" in sname:
            dictlist = [ 312008, "A", 5, 1000, 150 ]
        elif "312017" in sname or "ModelA" in sname and "600" in sname and "1" in sname:
            dictlist = [ 312017, "A", 5, 600, 1 ]
        elif "312022" in sname or "ModelB" in sname and "1400" in sname and "20" in sname:
            dictlist = [ 312022, "B", 2, 1400, 20 ]
        elif "312028" in sname or "ModelB" in sname and "1000" in sname and "5" in sname:
            dictlist = [ 312028, "B", 2, 1000, 5 ]
        elif "312031" in sname or "ModelB" in sname and "600" in sname and "300" in sname:
            dictlist = [ 312031, "B", 2, 600, 300 ]
        elif "312039" in sname or "ModelC" in sname and "1400" in sname and "75" in sname:
            dictlist = [ 312039, "C", 10, 1400, 75 ]
        elif "312046" in sname or "ModelC" in sname and "1000" in sname and "5" in sname:
            dictlist = [ 312046, "C", 10, 1000, 5 ]
        elif "312052" in sname or "ModelC" in sname and "600" in sname and "2" in sname:
            dictlist = [ 312053, "C", 10, 600, 2 ]
        elif "312060" in sname or "ModelD" in sname and "1400" in sname and "2" in sname:
            dictlist = [ 312060, "D", 20, 1400, 2 ]
        elif "312066" in sname or "ModelD" in sname and "1000" in sname and "1" in sname:
            dictlist = [ 312066, "D", 20, 1000, 1 ]
        elif "312067" in sname or "ModelD" in sname and "600" in sname and "300" in sname:
            dictlist = [ 312067, "D", 20, 600, 300 ]
        elif "312075" in sname or "ModelB" in sname and "1400" in sname and "75" in sname:
            dictlist = [ 312075, "E", 0.8, 1400, 75 ]
        elif "312080" in sname or "ModelB" in sname and "1000" in sname and "150" in sname:
            dictlist = [ 312080, "E", 0.8, 1000, 150 ]
        elif "312090" in sname or "ModelB" in sname and "600" in sname and "0.5" in sname:
            dictlist = [ 312090, "E", 0.8, 600, 0.5 ]
        # set line attributes and color palettes
        color   = ROOT.kWhite
        palette = texec_default()
        # set line color / palette by model
        if   dictlist[1] == "A":
            color   = sgnlColors()[0]
            palette = texec_sgnl()[0]
        elif dictlist[1] == "B":
            color   = sgnlColors()[1]
            palette = texec_sgnl()[1]
        elif dictlist[1] == "C":
            color   = sgnlColors()[2]
            palette = texec_sgnl()[2]
        elif dictlist[1] == "D":
            color   = sgnlColors()[3]
            palette = texec_sgnl()[3]
        elif dictlist[1] == "E":
            color   = sgnlColors()[4]
            palette = texec_sgnl()[4]
        # set line style by mediator mass
        if   dictlist[3] == 1400:
            style = 1
        elif dictlist[3] == 1000:
            style = 3
        elif dictlist[3] == 600:
            style = 7
        ## # vary base colors by lifetime --> TEST COLORS (want one to be base color, so add zero)
        ## # --> don't need for now, since available samples have singular lifetimes per model-Xdm point
        ## if args.varyCtauCols:
        ##     if   dictlist[4] == 300:
        ##         color = color + 1
        ##     elif dictlist[4] == 150:
        ##         color = color + 2
        ##     elif dictlist[4] == 75:
        ##         color = color + 3
        ##     elif dictlist[4] == 20:
        ##         color = color + 4
        ##     elif dictlist[4] == 5:
        ##         color = color + 5
        ##     elif dictlist[4] == 2:
        ##         color = color + 6
        ##     elif dictlist[4] == 1:
        ##         color = color + 7
        ##     elif dictlist[4] == 0.5:
        ##         color = color + 8
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
    if lstyle != 1:
        lwidth = 4

    return lwidth


## --- SET COLORS / PALETTES --- ##
## --> colors
def sgnlColors():
    return [ ROOT.kRed, ROOT.kGreen + 1, ROOT.kBlue, ROOT.kViolet, ROOT.kOrange + 1 ]
# one base color per model; one line / marker style per Xdm; one color (close to base) per lifetime

def bkgdColors():
    return [ ROOT.kGray + 2 ]

def dataColors():
    return [ ROOT.kBlack, ROOT.kGray+3, ROOT.kGray+1, ROOT.kGray ]
# TEMP PLACEHOLDERS --> FIX

## --> palettes 
def sgnlPalette():
    return [ ROOT.kCherry, ROOT.kAvocado, ROOT.kDeepSea, ROOT.kFuchsia, ROOT.kDarkBodyRadiator ]

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
