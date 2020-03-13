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
    
    # signal vs background
    command_sb  = command
    command_sb += " --bkgdType 361024"
    # --> AB benchmark test
    command_sb_ab = command_sb
    command_sb_ab += " --sgnlType 312008,312028"
    command_sb_ab += " --histTitle 'Model A/B benchmark signal vs background'"
    command_sb_ab += " --outName ab-bench"


    ## --- update plotting commands --- ##
    command_S  = " --regionDir search"
    command_S1 = " --regionDir search-minus-one"
    command_V  = " --regionDir valid"
    
    ## multi-hist multi-sample 1d plots -- comparing different jet-type histos over different samples
    histList_multismpl  = "_pt"
    command_multismpl   = []
    command_multismpl1d = " --drawMulti1D --doMultiSmpl --doTruthSvB --outSubdir multismpl_jet --legLenEnum 3 --lxint 0.007 --lyint 0.027"
    hvars, httls = [], []
    hvars.append( "darkMatchJet,jet"         )
    hvars.append( "leadDarkMatchJet,leadJet" )
    httls.append( "'dark-matched signal vs background'"         )
    httls.append( "'leading dark-matched signal vs background'" )
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
    command_sb_ab_multismpl_S = []
    for iC, command in enumerate( command_multismpl ):
        command_sb_ab_multismpl_S.append( command_sb_ab + command + command_S )


    ## --- run plotting jobs --- ##

    ## multi-sample 1d
    for cms_sbabS in command_sb_ab_multismpl_S:
        print cms_sbabS
        os.system( cms_sbabS )

    

if __name__ == "__main__":
    main()
