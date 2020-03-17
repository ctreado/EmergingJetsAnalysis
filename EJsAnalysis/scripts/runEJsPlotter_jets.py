#!/usr/bin/env python

########################################################
# runEJsPlotter_jets.py                                #
########################################################
# script for running "plotEJsHistograms" for jet plots #
# ######################################################
# Colleen Treado                                       #
########################################################

# don't forget to lumi-scale data !!

import os

def main():
    
    ## --- initialize plotting commands --- ##
    # --> change when needed
    #inDir   = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-01_n1/EJsNtupToHistOutput/"
    #inDir   = os.getenv('EJ_PATH') + "/../output/localOutput/tmp_search-minus-one/EJsNtupToHistOutput/"
    inDir   = os.getenv('EJ_PATH') + "/../run/test.histos/EJsNtupToHistOutput/"
    pscript = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/plotting/plotEJsHistograms.py"
    command = "python " + pscript + " --inDir " + inDir


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
    d            = " --dataType data --scaleData " + \
      " --metadataDir ../../output/gridOutput/v0_2020-01_full/metadata/" # --> for ab test; give path from parent of inDir
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
    command_S  = " --regionDir search"
    command_S1 = " --regionDir search-minus-one"
    command_V  = " --regionDir valid"

    
    # 1d plots -- comparing same jet histos over different samples
    histList_1d = "jet:DV=darkMatch=nomatch"
    command_1d = " --draw1D --outSubdir 1d_jet --legLenEnum 5 --histList " + histList_1d
    command_1d_l1 = " --lxint 0.006 --lyint 0.025" # for s vs b
    command_1d_l2 = " --lxint 0.015 --lyint 0.040" # for b vs d
    # --> AB benchmark test
    command_sb_ab_1d    = command_sb_ab    + command_1d + command_1d_l1
    command_sb_ab_1d_S  = command_sb_ab_1d + command_S
    command_sb_ab_1d_S1 = command_sb_ab_1d + command_S1
    # --> xdm-1400 signal vs background
    command_sb_14_1d    = command_sb_14    + command_1d + command_1d_l1
    command_sb_14_1d_S  = command_sb_14_1d + command_S
    command_sb_14_1d_S1 = command_sb_14_1d + command_S1
    # --> xdm-1000 signal vs background
    command_sb_10_1d    = command_sb_10    + command_1d + command_1d_l1
    command_sb_10_1d_S  = command_sb_10_1d + command_S
    command_sb_10_1d_S1 = command_sb_10_1d + command_S1
    # --> xdm-600 signal vs background
    command_sb_06_1d    = command_sb_06    + command_1d + command_1d_l1
    command_sb_06_1d_S  = command_sb_06_1d + command_S
    command_sb_06_1d_S1 = command_sb_06_1d + command_S1
    # --> background vs data
    command_bd_1d       = command_bd       + command_1d + command_1d_l2
    command_bd_1d_V     = command_bd_1d    + command_V


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
    command_multi1d = " --drawMulti1D --outSubdir multi_jet --legLenEnum 5 --lxint 0.007 --lyint 0.027 --lxl 0.700"
    # --> set hist vars for given jet types
    histvars, histttls, outnames = [], [], []
    histvars.append( "darkMatchJet,nomatchJet"         )
    histvars.append( "leadDarkMatchJet,leadNomatchJet" )
    histttls.append( "''"     )
    histttls.append( "'lead'" )
    outnames.append( "match"     )
    outnames.append( "leadMatch" )
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
    histList_multismpl  = "jet:DV"
    command_multismpl   = []
    command_multismpl1d = " --drawMulti1D --doMultiSmpl --doTruthSvB --outSubdir multismpl_jet --legLenEnum 3 --lxint 0.007 --lyint 0.027"
    # --> set hist vars, titles for given jet types
    hvars, httls = [], []
    hvars.append( "darkMatchJet,jet"         )
    hvars.append( "leadDarkMatchJet,leadJet" )
    httls.append( "'dark-matched signal vs background'"         )
    httls.append( "'leading dark-matched signal vs background'" )
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
    command_sb_ab_multismpl_S, command_sb_ab_multismpl_S1 = [], [] # --> ab benchmark test
    command_sb_14_multismpl_S, command_sb_14_multismpl_S1 = [], []
    command_sb_10_multismpl_S, command_sb_10_multismpl_S1 = [], []
    command_sb_06_multismpl_S, command_sb_06_multismpl_S1 = [], []
    for iC, command in enumerate( command_multismpl ):
        command_sb_ab_multismpl_S  .append( command_sb_ab + command + command_S  )
        command_sb_ab_multismpl_S1 .append( command_sb_ab + command + command_S1 )
        command_sb_14_multismpl_S  .append( command_sb_14 + command + command_S  )
        command_sb_14_multismpl_S1 .append( command_sb_14 + command + command_S1 )
        command_sb_10_multismpl_S  .append( command_sb_10 + command + command_S  )
        command_sb_10_multismpl_S1 .append( command_sb_10 + command + command_S1 )
        command_sb_06_multismpl_S  .append( command_sb_06 + command + command_S  )
        command_sb_06_multismpl_S1 .append( command_sb_06 + command + command_S1 )



    ## --- run plotting jobs --- ##

    # --> add other signal/sample types, regions for each plot type as needed

    ## 1d: signal vs background
    os.system( command_sb_ab_1d_S  ) # ab benchmark test
    ##os.system( command_sb_ab_1d_S1 )
    ##os.system( command_sb_14_1d_S  ) # xdm-1400
    ##os.system( command_sb_14_1d_S1 )
    ##os.system( command_sb_10_1d_S  ) # xdm-1000
    ##os.system( command_sb_10_1d_S1 )
    ##os.system( command_sb_06_1d_S  ) # xdm-600
    ##os.system( command_sb_06_1d_S1 )
    ### 1d: background vs data
    #os.system( command_bd_1d_V     )

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
    
    ### multi 1d
    #for cm_sabS  in command_s_ab_multi_S: # ab benchmark test
    #    os.system( cm_sabS  )
    ##for cm_sabS1 in command_s_ab_multi_S1:
    ##    os.system( cm_sabS1 )
    ##for cm_s14S  in command_s_14_multi_S: # xdm-1400
    ##    os.system( cm_s14S  )
    ##for cm_s14S1 in command_s_14_multi_S1:
    ##    os.system( cm_s14S1 )
    ##for cm_s10S  in command_s_10_multi_S: # xdm-1000
    ##    os.system( cm_s10S  )
    ##for cm_s10S1 in command_s_10_multi_S1:
    ##    os.system( cm_s10S1 )
    ##for cm_s06S  in command_s_06_multi_S: # xdm-600
    ##    os.system( cm_s06S  )
    ##for cm_s06S1 in command_s_06_multi_S1:
    ##    os.system( cm_s06S1 )
    ##for cm_bS    in command_b_multi_S:    # background
    ##    os.system( cm_bS    )
    ##for cm_bS1   in command_b_multi_S1:
    ##    os.system( cm_bS1   )
        
    ## multi-sample 1d
    for cms_sbabS  in command_sb_ab_multismpl_S:
        os.system( cms_sbabS  )
    ##for cms_sbabS1 in command_sb_ab_multismpl_S1:
    ##    os.system( cms_sbabS1 )
    ##for cms_sb14S  in command_sb_14_multismpl_S:
    ##    os.system( cms_sb14S  )
    ##for cms_sb14S1 in command_sb_14_multismpl_S1:
    ##    os.system( cms_sb14S1 )
    ##for cms_sb10S  in command_sb_10_multismpl_S:
    ##    os.system( cms_sb10S  )
    ##for cms_sb10S1 in command_sb_10_multismpl_S1:
    ##    os.system( cms_sb10S1 )
    ##for cms_sb06S  in command_sb_06_multismpl_S:
    ##    os.system( cms_sb06S  )
    ##for cms_sb06S1 in command_sb_06_multismpl_S1:
    ##    os.system( cms_sb06S1 )

    

if __name__ == "__main__":
    main()
