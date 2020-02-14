#!/usr/bin/env python

####################################
# runEJsABCD.py                    #
####################################
# script for running "plotEJsABCD" #
# ##################################
# Colleen Treado                   #
####################################

# don't forget to lumi-scale data !!

import os

def main():

    ## --- initialize commands --- ##
    # --> change when needed
    inDir   = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-01_n1/tmp_hists/"
    pscript = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/plotting/plotEJsABCD.py"
    command = "python " + pscript + " --inDir " + inDir

    # signal vs background
    command_sbd  = command
    command_sbd += " --bkgdType 361024 --dataType data17 --scaleData" # --> change to to 'data'
    # --> Models A and B; Xdm-1400
    command_sbd_ab14  = command_sbd
    command_sbd_ab14 += " --sgnlType 312004,312022"
    command_sbd_ab14 += " --outSgnlName ModAB_Xdm14"
    # --> Models A and B; Xdm-1000
    command_sbd_ab10  = command_sbd
    command_sbd_ab10 += " --sgnlType 312008,312028"
    command_sbd_ab10 += " --outSgnlName ModAB_Xdm10"
    # --> Models A and B; Xdm-600
    command_sbd_ab06  = command_sbd
    command_sbd_ab06 += " --sgnlType 312017,312031"
    command_sbd_ab06 += " --outSgnlName ModAB_Xdm06"
    # --> Model C; Xdm-1400
    command_sbd_c14   = command_sbd
    command_sbd_c14  += " --sgnlType 312039"
    command_sbd_c14  += " --outSgnlName ModC_Xdm14"
    # --> Model C; Xdm-1000
    command_sbd_c10   = command_sbd
    command_sbd_c10  += " --sgnlType 312046"
    command_sbd_c10  += " --outSgnlName ModC_Xdm10"
    # --> Model C; Xdm-600
    command_sbd_c06   = command_sbd
    command_sbd_c06  += " --sgnlType 312052"
    command_sbd_c06  += " --outSgnlName ModC_Xdm06"
    # --> Models D and E; Xdm-1400
    command_sbd_de14  = command_sbd
    command_sbd_de14 += " --sgnlType 312060,312075"
    command_sbd_de14 += " --outSgnlName ModDE_Xdm14"
    # --> Models D and E; Xdm-1000
    command_sbd_de10  = command_sbd
    command_sbd_de10 += " --sgnlType 312066,312080"
    command_sbd_de10 += " --outSgnlName ModDE_Xdm10"
    # --> Models D and E; Xdm-600
    command_sbd_de06  = command_sbd
    command_sbd_de06 += " --sgnlType 312067,312090"
    command_sbd_de06 += " --outSgnlName ModDE_Xdm06"
    # --> Xdm-1000; no plots
    command_sbd_10    = command_sbd
    command_sbd_10   += " --sgnlType 312008,312028,312046,312066,312080"
    command_sbd_10   += " --outName Xdm10"
    # --> all; no plots
    command_sbd_all   = command_sbd
    command_sbd_all  += " --sgnlType 312004,312008,312017,312022,312028,312031,312039,312046,312052,312060,312066,312067,312075,312080,312090"
    command_sbd_all  += " --outName all"


    ## --- update commands --- ##
    # abcd plots
    command_abcd    = " --doABCD --drawABCD"
    command_abcd_np = " --doABCD"
    # --> Models A and B; Xdm-1400
    command_sbd_ab14 += command_abcd
    # --> Models A and B; Xdm-1000
    command_sbd_ab10 += command_abcd
    # --> Models A and B; Xdm-600
    command_sbd_ab06 += command_abcd
    # --> Model C; Xdm-1400
    command_sbd_c14  += command_abcd
    # --> Model C; Xdm-1000
    command_sbd_c10  += command_abcd
    # --> Model C; Xdm-600
    command_sbd_c06  += command_abcd
    # --> Models D and E; Xdm-1400
    command_sbd_de14 += command_abcd
    # --> Models D and E; Xdm-1000
    command_sbd_de10 += command_abcd
    # --> Models D and E; Xdm-600
    command_sbd_de06 += command_abcd
    # --> Xdm-1000; no plots
    command_sbd_10   += command_abcd_np
    # --> all; no plots
    command_sbd_all  += command_abcd_np


    
    ## --- run jobs --- ##
    # signal vs background
    ## --> Models A and B; Xdm-1400
    #os.system( command_sbd_ab14 )
    ## --> Models A and B; Xdm-1000
    #os.system( command_sbd_ab10 )
    ## --> Models A and B; Xdm-600
    #os.system( command_sbd_ab06 )
    ## --> Model C; Xdm-1400
    #os.system( command_sbd_c14  )
    ## --> Model C; Xdm-1000
    #os.system( command_sbd_c10  )
    ## --> Model C; Xdm-600
    #os.system( command_sbd_c06  )
    ## --> Models D and E; Xdm-1400
    #os.system( command_sbd_de14 )
    ## --> Models D and E; Xdm-1000
    #os.system( command_sbd_de10 )
    ## --> Models D and E; Xdm-600
    #os.system( command_sbd_de06 )
    ## --> Xdm-1000; no plots
    #os.system( command_sbd_10   )
    # --> all; no plots
    os.system( command_sbd_all  )


    
if __name__ == "__main__":
    main()
