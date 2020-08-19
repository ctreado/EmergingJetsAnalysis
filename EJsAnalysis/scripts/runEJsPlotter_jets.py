#!/usr/bin/env python

########################################################
# runEJsPlotter_jets.py                                #
########################################################
# script for running "plotEJsHistograms" for jet plots #
# ######################################################
# Colleen Treado                                       #
########################################################

# TO RUN ON LOCAL MACHINE (NOT CERNVM) NEED TO RUN W/ PYTHON3 --> make compatible with both python versions...
# --> also need to source root directory: 'source /usr/local/Cellar/root/6.16.00/bin/thisroot.sh'
# --> also need to set EJ_PATH in EmergingJetsAnalysis repo when running outside athena: 'export EJ_PATH=$(pwd)'
# --> also need to run with 'python3'

# don't forget to lumi-scale data !!

import os

def main():

    # initialize jets
    # --> hard jets
    #hardJs      = [ "HardPt",  "HardEta",  "HardMass",  "HardPtEta",   "Hard" ]
    #hardJts     = [ "hard-pt", "hard-eta", "hard-mass", "hard-pt-eta", "hard" ]
    #hardJs      = [ "HardPt",  "HardEta",  "HardMass"  ]
    #hardJts     = [ "hard-pt", "hard-eta", "hard-mass" ]
    hardJs      = [ "Hard" ]
    hardJts     = [ "hard" ]
    # --> emerging jets
    baseJSV     = "Clean"
    baseJSVt    = "clean"
    #jsvs        = [ baseJSV,  "Loose", "Mid", "Tight" ]
    #jsvts       = [ baseJSVt, "loose", "mid", "tight" ]
    jsvs        = [ "Loose", "Mid", "Tight" ]
    jsvts       = [ "loose", "mid", "tight" ]
    emergingJs  = []
    emergingJts = []
    for ijsv, jsv in enumerate( jsvs ):
        emergingJs  .append(      "Emerging" + jsv    + "SV"  )
        emergingJs  .append( "LooseEmerging" + jsv    + "SV"  )
        emergingJs  .append( "TightEmerging" + jsv    + "SV"  )
        emergingJts .append(       "EJ ("    + jsv[0] + "SV)" )
        emergingJts .append( "Loose EJ ("    + jsv[0] + "SV)" )
        emergingJts .append( "Tight EJ ("    + jsv[0] + "SV)" )
    # --> nsv jets
    jsvpts     = [ "Low", "Mid", "High" ]
    njsvtrks   = [ "2", "4", "6", "8" ]
    njsvs      = [ "1", "2" ]
    bJSVs,  p4JSVs,  ptJSVs,  htJSVs,  hJSVs,  ntrkJSVs,  njtrkJSVs,  trkJSVs,  nJSVs  = [], [], [], [], [], [], [], [], []
    bJSVts, p4JSVts, ptJSVts, htJSVts, hJSVts, ntrkJSVts, njtrkJSVts, trkJSVts, nJSVts = [], [], [], [], [], [], [], [], []
    for ijsv, jsv in enumerate( jsvs ):
        bJSVs          .append( jsv +  "SV" )
        bJSVts         .append( "" )
    for ijsv, jsv in enumerate( jsvs ):
        p4JSVs         .append( jsv + "SVP4" )
        p4JSVts        .append( "" )
        #for jsvpt in jsvpts:
        #    p4JSVs     .append( jsv + "SV" + jsvpt + "P4" )
        #    p4JSVts    .append( jsvpt + "-" + jsvts[ijsv] + "-SV-pt" )
    for ijsv, jsv in enumerate( jsvs ):
        ptJSVs         .append( jsv + "SVPt" )
        ptJSVts        .append( "" )
        #for jsvpt in jsvpts:
        #    ptJSVs     .append( jsv + "SV" + jsvpt + "Pt" )
        #    ptJSVts    .append( jsvpt + "-" + jsvts[ijsv] + "-SV-sum-pt" )
    for ijsv, jsv in enumerate( jsvs ):
        htJSVs         .append( jsv + "SVHt" )
        htJSVts        .append( "" )
        #for jsvpt in jsvpts:
        #    htJSVs     .append( jsv + "SV" + jsvpt + "Ht" )
        #    htJSVts    .append( jsvpt + "-" + jsvts[ijsv] + "-SV-Ht" )
    for ijsv, jsv in enumerate( jsvs ):
        hJSVs          .append( jsv + "SVH" )
        hJSVts         .append( "" )
        #for jsvpt in jsvpts:
        #    hJSVs      .append( jsv + "SV" + jsvpt + "H" )
        #    hJSVts     .append( jsvpt + "-" + jsvts[ijsv] + "-SV-H" )
    for ijsv, jsv in enumerate( jsvs ):
        ntrkJSVs       .append( jsv + "SVNtrk" )
        ntrkJSVts      .append( "" )
        #for njsvtrk in njsvtrks:
        #    ntrkJSVs   .append( jsv + "SVNtrk"  + njsvtrk )
        #    ntrkJSVts  .append( njsvtrk + "-" + jsvts[ijsv] + "-SV-Ntrk"  )
    for ijsv, jsv in enumerate( jsvs ):
        njtrkJSVs      .append( jsv + "SVNjtrk" )
        njtrkJSVts     .append( "" )
        #for njsvtrk in njsvtrks:
        #    njtrkJSVs  .append( jsv + "SVNjtrk" + njsvtrk )
        #    njtrkJSVts .append( njsvtrk + "-" + jsvts[ijsv] + "-SV-Njtrk" )
    for ijsv, jsv in enumerate( jsvs ):
        trkJSVs        .append( jsv + "SVTrk" )
        trkJSVts       .append( "" )
        #for njsvtrk in njsvtrks:
        #    trkJSVs    .append( jsv + "SVTrk"   + njsvtrk )
        #    trkJSVts   .append( njsvtrk + "-" + jsvts[ijsv] + "-SV-trk"    )
    #for ijsv, jsv in enumerate( jsvs ):
    #    for njsv    in njsvs:
    #        nJSVs     .append( jsv + "SV"      + njsv    )
    #        nJSVts    .append( njsv    + "-" + jsvts[ijsv] + "-SV"        )
    # --> nsv tight jets
    ntrktJSVs,  njtrktJSVs,  trktJSVs,  ntJSVs  = [], [], [], []
    ntrktJSVts, njtrktJSVts, trktJSVts, ntJSVts = [], [], [], []
    #for intrkjsv,  ntrkjsv  in enumerate( ntrkJSVs  ):
    #    ntrktJSVs   .append( ntrkjsv               +  "Tight" )
    #    ntrktJSVts  .append( ntrkJSVts [intrkjsv]  + " tight" )
    #for injtrkjsv, njtrkjsv in enumerate( njtrkJSVs ):
    #    njtrktJSVs  .append( njtrkjsv              +  "Tight" )
    #    njtrktJSVts .append( njtrkJSVts[injtrkjsv] + " tight" )
    #for itrkjsv,   trkjsv   in enumerate( trkJSVs   ):
    #    trktJSVs    .append( trkjsv                +  "Tight" )
    #    trktJSVts   .append( trkJSVts  [itrkjsv]   + " tight" )
    #for injsv,     njsv     in enumerate( nJSVs     ):
    #    ntJSVs      .append( njsv                  +  "Tight" )
    #    ntJSVts     .append( nJSVts    [injsv]     + " tight" )
    # --> emerging jets
    # --> set jet-cut type, title, exclusion lists
    jetCuts, jetTitles, exclCuts = [], [], []
    #jetCuts   = hardJs  + bJSVs  + p4JSVs  + ptJSVs  + htJSVs  + hJSVs  + ntrkJSVs  + njtrkJSVs  + trkJSVs  + nJSVs  \
    #  + ntrktJSVs  + njtrktJSVs  + trktJSVs  + ntJSVs
    #jetTitles = hardJts + bJSVts + p4JSVts + ptJSVts + htJSVts + hJSVts + ntrkJSVts + njtrkJSVts + trkJSVts + nJSVts \
    #  + ntrktJSVts + njtrktJSVts + trktJSVts + ntJSVts
    #exclCuts  = hardJs  + bJSVs  + p4JSVs  + ptJSVs  + htJSVs  + hJSVs  + ntrkJSVs  + njtrkJSVs  + trkJSVs  + nJSVs  \
    #  + ntrktJSVs  + njtrktJSVs  + trktJSVs  + ntJSVs
    jetCuts   = emergingJs
    jetTitles = emergingJts
    exclCuts  = emergingJs
    jetTypes, exclJetTypes = [], []
    for iC, cut in enumerate( jetCuts ):
        lowcut     = cut         [0].lower() + cut         [1:]
        lowexclcut = exclCuts[iC][0].lower() + exclCuts[iC][1:]
        jetTypes     .append( lowcut     )
        exclJetTypes .append( lowexclcut )
    # --> do fill background?
    doFillBkgd = True
        
    
    ## --- initialize plotting commands --- ##
    # --> change when needed
    #inDir   = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-01_n1/EJsNtupToHistOutput/"
    #inDir   = os.getenv('EJ_PATH') + "/../output/localOutput/tmp_search-minus-one/EJsNtupToHistOutput/"
    #inDir   = os.getenv('EJ_PATH') + "/../run/test.histos/EJsNtupToHistOutput/"
    inDir   = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-06_mod/EJsNtupToHistOutput/njetx_abcd/"
    outDir  = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-06_mod/plots/njetx_abcd/"
    #inDir   = os.getenv('EJ_PATH') + "/../run/test.histos/EJsNtupToHistOutput/"
    pscript = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/plotting/plotEJsHistograms.py"
    #command = "python "  + pscript + " --inDir " + inDir + " --outDir " + outDir
    command = "python3 " + pscript + " --inDir " + inDir + " --outDir " + outDir # for running outside of athena

    # signal
    s_ab         = " --sgnlType 312008,312028"                      # ab benchmark test
    s_14         = " --sgnlType 312004,312022,312039,312060,312075" # xdm-1400
    s_10         = " --sgnlType 312008,312028,312046,312066,312080" # xdm-1000
    s_06         = " --sgnlType 312017,312031,312052,312067,312090" # xdm-600
    command_s    = command
    command_s_ab = command_s + s_ab
    command_s_14 = command_s + s_14
    command_s_10 = command_s + s_10
    command_s_06 = command_s + s_06

    # background
    b            = " --bkgdType 361024"
    command_b    = command
    command_b   += b

    # data
    d            = " --dataType data --scaleData " \
      #+ " --metadataDir ../../output/gridOutput/v0_2020-01_full/metadata/" # --> for ab test; give path from parent of inDir
    command_d    = command
    command_d   += d
    
    # signal vs background
    command_sb     = command
    command_sb    += b
    # --> AB benchmark test
    command_sb_ab  = command_sb
    command_sb_ab += s_ab
    command_sb_ab += " --histTitle 'Model A/B benchmark signal vs background'"
    command_sb_ab += " --outName ab-bench"
    # --> xdm-1400
    command_sb_14  = command_sb
    command_sb_14 += s_14
    command_sb_14 += " --histTitle 'Xdm-1400 signal vs background'"
    command_sb_14 += " --outName xdm-1400"
    # --> xdm-1000
    command_sb_10  = command_sb
    command_sb_10 += s_10
    command_sb_10 += " --histTitle 'Xdm-1000 signal vs background'"
    command_sb_10 += " --outName xdm-1000"
    # --> xdm-600
    command_sb_06  = command_sb
    command_sb_06 += s_06
    command_sb_06 += " --histTitle 'Xdm-600 signal vs background'"
    command_sb_06 += " --outName xdm-600"

    # background vs data
    command_bd     = command
    command_bd    += b
    command_bd    += d
    command_bd    += " --histTitle 'background vs data'"


    ## --- update plotting commands --- ##
    command_S   = " --regionDir search"
    command_S1  = " --regionDir search-minus-one"
    command_V   = " --regionDir valid"
    command_SJ  = " --regionDir jz4w-slice-search"
    command_S1J = " --regionDir jz4w-slice-search-minus-one"
    command_VJ  = " --regionDir jz4w-slice-validation"

    
    # 1d plots -- comparing same jet histos over different samples
    #histList_1d     = "jet+cutflow=_jj_=_Nj_=NJet:DV=darkMatch=nomatch=jet0=jet1=jet1=jet3=_truthJet"
    histList_1d     = "jet+NJet=cutflow:DV=darkMatch=nomatch=truthJet=darkJet=jet0=jet1=jet1=jet3=_SV"
    command_1d_j    = []
    command_1d      = " --draw1D --drawSOverB --outSubdir 1d_jet --legLenEnum 5"
    if doFillBkgd:
        command_1d += " --fillBkgd"
    command_1d_l1   = " --lxint 0.006 --lyint 0.030" # for s vs b
    command_1d_l2   = " --lxint 0.015 --lyint 0.040" # for b vs d
    # --> loop over jet types and configure plotting script
    jtype = [ "jet", "leadJet" ]
    for jt, jett in enumerate(jetTypes):
        jtype.append(                 jett + "Jet" )
        jtype.append( "lead" + jetCuts[jt] + "Jet" )
    for ij, j in enumerate( jtype ):
        hlist = j
        if histList_1d:
            hlist += "+" + histList_1d
        if "lead" not in j:
            if ':' not in hlist: hlist += ':'
            else:                hlist += '='
            hlist += "lead"
            if j == "jet":
                for ejt in exclJetTypes:
                    hlist += "=" + ejt
        command_1d_j.append( command_1d + " --histList " + hlist + " --histVars " + j )
    # --> complete commands
    command_sb_ab_1d_S, command_sb_ab_1d_SJ = [], [] # --> AB benchmark test
    command_sb_14_1d_S, command_sb_14_1d_SJ = [], [] # --> xdm-1400 signal vs background
    command_sb_10_1d_S, command_sb_10_1d_SJ = [], [] # --> xdm-1000 signal vs background
    command_sb_06_1d_S, command_sb_06_1d_SJ = [], [] # --> xdm-600  signal vs background
    command_bd_1d_V,    command_bd_1d_VJ    = [], [] # --> background vs data
    for iC, command in enumerate( command_1d_j ):
        command_sb_ab_1d_S .append( command_sb_ab + command + command_1d_l1 + command_S  )
        command_sb_ab_1d_SJ.append( command_sb_ab + command + command_1d_l1 + command_SJ )
        command_sb_14_1d_S .append( command_sb_14 + command + command_1d_l1 + command_S  )
        command_sb_14_1d_SJ.append( command_sb_14 + command + command_1d_l1 + command_SJ )
        command_sb_10_1d_S .append( command_sb_10 + command + command_1d_l1 + command_S  )
        command_sb_10_1d_SJ.append( command_sb_10 + command + command_1d_l1 + command_SJ )
        command_sb_06_1d_S .append( command_sb_06 + command + command_1d_l1 + command_S  )
        command_sb_06_1d_SJ.append( command_sb_06 + command + command_1d_l1 + command_SJ )
        command_bd_1d_V    .append( command_bd    + command + command_1d_l2 + command_V  )
        command_bd_1d_VJ   .append( command_bd    + command + command_1d_l2 + command_VJ )


    # 2d plots -- one jet histo per plot
    histList_2d = "jet:DV" # --> skip dark-matched jets for background; add different hist lists for signal and background?
    command_2d  = " --draw2D --outSubdir 2d_jet --histList " + histList_2d
    # --> signal
    command_s_ab_2d_S  = command_s_ab + command_2d + command_S
    command_s_ab_2d_S1 = command_s_ab + command_2d + command_S1
    command_s_14_2d_S  = command_s_14 + command_2d + command_S
    command_s_14_2d_S1 = command_s_14 + command_2d + command_S1
    command_s_10_2d_S  = command_s_10 + command_2d + command_S
    command_s_10_2d_S1 = command_s_10 + command_2d + command_S1
    command_s_06_2d_S  = command_s_06 + command_2d + command_S
    command_s_06_2d_S1 = command_s_06 + command_2d + command_S1
    # --> background
    command_b_2d_S     = command_b    + command_2d + command_S
    command_b_2d_S1    = command_b    + command_2d + command_S1
    command_b_2d_V     = command_b    + command_2d + command_V
    # --> data
    command_d_2d_V     = command_d    + command_2d + command_V


    # multi-hist 1d plots -- comparing dark-matched to unmatched jets in same sample
    histList_multi = "jet:DV"
    command_multi  = []
    command_multi1d = " --drawMulti1D --outSubdir multi_jet --legLenEnum 5 --lxint 0.007 --lyint 0.027" # --lxl 0.600"
    # --> set hist vars for given jet types
    jet1   = [ "darkMatchJet" ]
    jet2   = [ "nomatchJet"   ]
    jetout = [ "match"        ]
    histvars, histttls, outnames = [], [], []
    for ij in range( len(jet1) ):
        histvars.append( jet1[ij] + "," + jet2[ij] )
        histttls.append( "''"       )
        outnames.append( jetout[ij] )
        getLeadMulti( jet1[ij], jet2[ij], jetout[ij], histvars, histttls, outnames )
        for jetType in jetTypes:
            upjet1   = jet1  [ij][0].upper() + jet1  [ij][1:]
            upjet2   = jet2  [ij][0].upper() + jet2  [ij][1:]
            upjetout = jetout[ij][0].upper() + jetout[ij][1:]
            histvars.append( jetType + upjet1 + "," + jetType + upjet2 )
            histttls.append( "'" + jetType + "'" )
            outnames.append( jetType + upjetout  )
            getLeadMulti( jetType + upjet1, jetType + upjet2, jetType + upjetout, histvars, histttls, outnames )
    # --> loop over hist vars and configure plotting script
    for iVar, var in enumerate( histvars ):
        histList = var
        if histList_multi:
            hlist = histList.split(',')
            histList = ""
            for hl in hlist:
                hl += "+" + histList_multi
                histList += hl + ","
            if histList.endswith(','): histList = histList[:-1]
        command_multi.append( command_multi1d + " --histVars " + var + " --outName " + outnames[iVar] + \
                                  " --histList " + histList + " --histTitle " + histttls[iVar] + " --varEnum 3" )
    # --> complete commands
    command_s_ab_multi_S, command_s_ab_multi_S1 = [], [] # ab benchmark test
    command_s_14_multi_S, command_s_14_multi_S1 = [], []
    command_s_10_multi_S, command_s_10_multi_S1 = [], []
    command_s_06_multi_S, command_s_06_multi_S1 = [], []
    command_b_multi_S,    command_b_multi_S1    = [], []
    for command in command_multi:
        command_s_ab_multi_S  .append( command_s_ab + command + command_S  )
        command_s_ab_multi_S1 .append( command_s_ab + command + command_S1 )
        command_s_14_multi_S  .append( command_s_14 + command + command_S  )
        command_s_14_multi_S1 .append( command_s_14 + command + command_S1 )
        command_s_10_multi_S  .append( command_s_10 + command + command_S  )
        command_s_10_multi_S1 .append( command_s_10 + command + command_S1 )
        command_s_06_multi_S  .append( command_s_06 + command + command_S  )
        command_s_06_multi_S1 .append( command_s_06 + command + command_S1 )
        command_b_multi_S     .append( command_b    + command + command_S  )
        command_b_multi_S1    .append( command_b    + command + command_S1 )
    
    
    # multi-hist multi-sample 1d plots -- comparing different jet-type histos over different samples
    #histList_multismpl  = "jet+_pt=_eta=_M=_sum=_njtrk=_cutflow:DV=_jj_=_Nj_=assoctrk=seltrk=LRTtrk=SVtrk=_min=_max=_sumr=_sumz"
    histList_multismpl  = "jet+_cutflow:DV=_jj_=_Nj_=assoctrk=seltrk=LRTtrk=SVtrk=_min=_max=_sumr=_sumz"
    command_multismpl   = []
    command_multismpl1d = " --drawMulti1D --drawSOverB --doMultiSmpl --doTruthSvB --outSubdir multismpl_jet --legLenEnum 6 --lxint 0.007 --lyint 0.030 --lxl 0.525"
    if doFillBkgd:
        command_multismpl1d += " --fillBkgd"
    # --> set hist vars, titles for given jet types
    j1  = [ "darkMatchJet" ]
    j2  = [ "jet"          ]
    jt1 = [ "dark-matched" ]
    jt2 = [ ""             ]
    hvars, httls = [], []
    for ij in range( len(j1) ):
        hvars.append( j1[ij] + "," + j2[ij] )
        if jt1[ij]: jt1[ij] += " "
        if jt2[ij]: jt2[ij] += " "
        httls.append( "'" + jt1[ij] + "signal vs " + jt2[ij] + "background'" )
        getLeadMultiSmpl( j1[ij], j2[ij], jt1[ij], jt2[ij], hvars, httls, jsvs )
        for jt, jetType in enumerate( jetTypes ):
            upj1 = j1[ij][0].upper() + j1[ij][1:]
            upj2 = j2[ij][0].upper() + j2[ij][1:]
            hvars.append( jetType + upj1 + "," + jetType + upj2 )
            jttl1 = jetTitles[jt] + " "
            jttl2 = jetTitles[jt] + " "
            if jt1[ij]: jttl1 += jt1[ij]
            if jt2[ij]: jttl2 += jt2[ij]
            httls.append( "'" + jttl1 + "signal vs " + jttl2 + "background'" )
            getLeadMultiSmpl( jetType + upj1, jetType + upj2, jttl1, jttl2, hvars, httls, jsvs )
    # --> loop over hist vars and configure plotting script
    for iVar, var in enumerate( hvars ):
        histList = var
        if histList_multismpl:
            hlist = histList.split(',')
            histList = ""
            for hl in hlist:
                hl += "+" + histList_multismpl
                histList += hl + ","
            if histList.endswith(','): histList = histList[:-1]
        command_multismpl.append( command_multismpl1d + " --histVars " + var + " --sbdVars " + var + \
                                      " --histList " + histList + " --histTitle " + httls[iVar] + " --varEnum 3" )
    # --> complete commands
    command_sb_ab_multismpl_S, command_sb_ab_multismpl_SJ = [], [] # --> ab benchmark test
    command_sb_14_multismpl_S, command_sb_14_multismpl_SJ = [], []
    command_sb_10_multismpl_S, command_sb_10_multismpl_SJ = [], []
    command_sb_06_multismpl_S, command_sb_06_multismpl_SJ = [], []
    for iC, command in enumerate( command_multismpl ):
        htitle_14 = "'X_{dm} = 1400 GeV '" + httls[iC]
        htitle_10 = "'X_{dm} = 1000 GeV '" + httls[iC]
        htitle_06 = "'X_{dm} = 600 GeV '"  + httls[iC]
        command_sb_ab_multismpl_S  .append( command_sb_ab + command + command_S  + " --histTitle " + htitle_10 )
        command_sb_ab_multismpl_SJ .append( command_sb_ab + command + command_SJ + " --histTitle " + htitle_10 )
        command_sb_14_multismpl_S  .append( command_sb_14 + command + command_S  + " --histTitle " + htitle_14 )
        command_sb_14_multismpl_SJ .append( command_sb_14 + command + command_SJ + " --histTitle " + htitle_14 )
        command_sb_10_multismpl_S  .append( command_sb_10 + command + command_S  + " --histTitle " + htitle_10 )
        command_sb_10_multismpl_SJ .append( command_sb_10 + command + command_SJ + " --histTitle " + htitle_10 )
        command_sb_06_multismpl_S  .append( command_sb_06 + command + command_S  + " --histTitle " + htitle_06 )
        command_sb_06_multismpl_SJ .append( command_sb_06 + command + command_SJ + " --histTitle " + htitle_06 )


    ## --- run plotting jobs --- ##

    ## 1d: signal vs background
    #for c_sbabS  in command_sb_ab_1d_S: # ab benchmark test
    #    os.system( c_sbabS  )
    #for c_sbabSJ in command_sb_ab_1d_SJ:
    #    os.system( c_sbabSJ )
    for c_sb14S  in command_sb_14_1d_S: # xdm-1400
        os.system( c_sb14S  )
    for c_sb14SJ in command_sb_14_1d_SJ:
        os.system( c_sb14SJ )
    for c_sb10S  in command_sb_10_1d_S: # xdm-1000
        os.system( c_sb10S  )
    for c_sb10SJ in command_sb_10_1d_SJ:
        os.system( c_sb10SJ )
    for c_sb06S  in command_sb_06_1d_S: # xdm-600
        os.system( c_sb06S  )
    for c_sb06SJ in command_sb_06_1d_SJ:
        os.system( c_sb06SJ )
    ## 1d: background vs data
    #for c_bdV in command_bd_1d_V:
    #    os.system( c_bdV )
    #for c_bdVJ in command_bd_1d_VJ:
    #    os.system( c_bdVJ )

    ### 2d: signal
    #os.system( command_s_ab_2d_S  ) # ab benchmark test
    ##os.system( command_s_ab_2d_S1 )
    ##os.system( command_s_14_2d_S  ) # xdm-1400
    ##os.system( command_s_14_2d_S1 )
    ##os.system( command_s_10_2d_S  ) # xdm-1000
    ##os.system( command_s_10_2d_S1 )
    ##os.system( command_s_06_2d_S  ) # xdm-600
    ##os.system( command_s_06_2d_S1 )
    ### 2d: background
    #os.system( command_b_2d_S    )
    ##os.system( command_b_2d_S1   )
    #os.system( command_b_2d_V    )
    ### 2d: data
    #os.system( command_d_2d_V    )
    
    ## multi 1d
    #for cm_sabS  in command_s_ab_multi_S: # ab benchmark test
    #    os.system( cm_sabS  )
    #for cm_sabS1 in command_s_ab_multi_S1:
    #    os.system( cm_sabS1 )
    #for cm_s14S  in command_s_14_multi_S: # xdm-1400
    #    os.system( cm_s14S  )
    #for cm_s14S1 in command_s_14_multi_S1:
    #    os.system( cm_s14S1 )
    #for cm_s10S  in command_s_10_multi_S: # xdm-1000
    #    os.system( cm_s10S  )
    #for cm_s10S1 in command_s_10_multi_S1:
    #    os.system( cm_s10S1 )
    #for cm_s06S  in command_s_06_multi_S: # xdm-600
    #    os.system( cm_s06S  )
    #for cm_s06S1 in command_s_06_multi_S1:
    #    os.system( cm_s06S1 )
    #for cm_bS    in command_b_multi_S:    # background
    #    os.system( cm_bS    )
    #for cm_bS1   in command_b_multi_S1:
    #    os.system( cm_bS1   )
        
    ## multi-sample 1d
    #for cms_sbabS  in command_sb_ab_multismpl_S:
    #    os.system( cms_sbabS  )
    #for cms_sbabSJ in command_sb_ab_multismpl_SJ:
    #    os.system( cms_sbabSJ )
    #for cms_sb14S  in command_sb_14_multismpl_S:
    #    os.system( cms_sb14S  )
    #for cms_sb14SJ in command_sb_14_multismpl_SJ:
    #    os.system( cms_sb14SJ )
    #for cms_sb10S  in command_sb_10_multismpl_S:
    #    os.system( cms_sb10S  )
    #for cms_sb10SJ in command_sb_10_multismpl_SJ:
    #    os.system( cms_sb10SJ )
    #for cms_sb06S  in command_sb_06_multismpl_S:
    #    os.system( cms_sb06S  )
    #for cms_sb06SJ in command_sb_06_multismpl_SJ:
    #    os.system( cms_sb06SJ )



def getLeadMulti( jet1, jet2, jetout, hvars, httls, onames ):
    upjet1   = jet1  [0].upper() + jet1  [1:]
    upjet2   = jet2  [0].upper() + jet2  [1:]
    upjetout = jetout[0].upper() + jetout[1:]
    for ijet in range(5):
        njet = str(ijet-1)
        if njet == "-1": njet = ""
        htitle = "'lead"
        if njet: htitle += "-"
        htitle += njet + "'"
        hvars .append( "lead" + upjet1 + njet + ",lead" + upjet2 + njet )
        httls .append( htitle                   )
        onames.append( "lead" + upjetout + njet )

def getLeadMultiSmpl( jet1, jet2, jetTitle1, jetTitle2, hvars, httls, jsvs ):
    jsv_cuts = [ "SV", "SVP4", "SVPt", "SVHt", "SVH", "SVNtrk", "SVNjtrk", "SVTrk" ]
    upjet1 = jet1[0].upper() + jet1[1:] 
    upjet2 = jet2[0].upper() + jet2[1:]
    if "Jet" in upjet1:
        upjet1 = upjet1.split("Jet")[0]
        upjet2 = upjet2.split("Jet")[0]
        jet1   =   jet1.split("Jet")[0]
        jet2   =   jet2.split("Jet")[0]
    #for ijet in range(5):
    for ijet in range(1):
        njet = str(ijet-1)
        if njet == "-1": njet = ""
        htitle = "'"
        if njet:
            hnjet = njet
            if   njet == "0": hnjet = "1st"
            elif njet == "1": hnjet = "2nd"
            elif njet == "2": hnjet = "3rd"
            elif njet == "3": hnjet = "4th"
            htitle += hnjet + " "
        htitle += "N-leading "
        htitle += jetTitle1 + "signal vs " + jetTitle2 + "background'"
        swapOrder = False
        for jsv in jsvs:
            for jsvc in jsv_cuts:
                if upjet2 == jsv + jsvc or upjet2 == "Emerging" + jsv + jsvc: swapOrder = True
        if swapOrder: hvars.append( jet1   + "LeadJet"      + njet + ","     + jet2   + "LeadJet" + njet )
        else:         hvars.append( "lead" + upjet1 + "Jet" + njet + ",lead" + upjet2 + "Jet"     + njet )
        httls.append( htitle )

    

if __name__ == "__main__":
    main()
