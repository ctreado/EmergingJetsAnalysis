#!/usr/bin/env python

####################################
# runEJsABCD.py                    #
####################################
# script for running "plotEJsABCD" #
# ##################################
# Colleen Treado                   #
####################################

# TO RUN ON LOCAL MACHINE (NOT CERNVM) NEED TO RUN W/ PYTHON3 --> make compatible with both python versions...
# --> also need to source root directory: 'source /usr/local/Cellar/root/6.16.00/bin/thisroot.sh'
# --> also need to set EJ_PATH in EmergingJetsAnalysis repo when running outside athena: 'export EJ_PATH=$(pwd)'
# --> also need to run with 'python3'

# don't forget to lumi-scale data !!

import os

def main():

    ## --- initialize plotting commands --- ##
    # --> change when needed
    inDir   = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-06_mod/EJsNtupToHistOutput/njetx_abcd/"
    outDir  = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-06_mod/plots/njetx_abcd/"
    #inDir   = os.getenv('EJ_PATH') + "/../run/test.histos/EJsNtupToHistOutput/"
    pscript = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/plotting/plotEJsABCD.py"
    command = "python "  + pscript + " --inDir " + inDir + " --outDir " + outDir
    #command = "python3 " + pscript + " --inDir " + inDir + " --outDir " + outDir # for running outside of athena

    # signal
    s_abcde_14 = " --sgnlType 312004,312022,312039,312060,312075"
    s_abcde_10 = " --sgnlType 312008,312028,312046,312066,312080"
    s_abcde_06 = " --sgnlType 312017,312031,312052,312067,312090"
    s_ab_14    = " --sgnlType 312004,312022"
    s_ab_10    = " --sgnlType 312008,312028"
    s_ab_06    = " --sgnlType 312017,312031"
    s_cde_14   = " --sgnlType 312039,312060,312075"
    s_cde_10   = " --sgnlType 312046,312066,312080"
    s_cde_06   = " --sgnlType 312052,312067,312090"
    s_a        = " --sgnlType 312004,312008,312017"
    s_b        = " --sgnlType 312022,312028,312031"
    s_c        = " --sgnlType 312039,312046,312052"
    s_d        = " --sgnlType 312060,312066,312067"
    s_e        = " --sgnlType 312075,312080,312090"
    s_04       = " --sgnlType 312004"
    s_08       = " --sgnlType 312008"
    s_17       = " --sgnlType 312017"
    s_22       = " --sgnlType 312022"
    s_28       = " --sgnlType 312028"
    s_31       = " --sgnlType 312031"
    s_39       = " --sgnlType 312039"
    s_46       = " --sgnlType 312046"
    s_52       = " --sgnlType 312052"
    s_60       = " --sgnlType 312060"
    s_66       = " --sgnlType 312066"
    s_67       = " --sgnlType 312067"
    s_75       = " --sgnlType 312075"
    s_80       = " --sgnlType 312080"
    s_90       = " --sgnlType 312090"
    # background
    b        = " --bkgdType 361024"
    # data
    d        = " --dataType data17 --scaleData"

    # signal vs background
    command_sbd           = command
    command_sbd          += b
    #command_sbd          += d
    # Models A, B, C, D, and E; Xdm-1400
    command_sbd_abcde_14  = command_sbd + s_abcde_14
    command_sbd_abcde_14 += " --outSgnlName ModABCDE_Xdm14"
    # Models A, B, C, D, and E; Xdm-1000
    command_sbd_abcde_10  = command_sbd + s_abcde_10
    command_sbd_abcde_10 += " --outSgnlName ModABCDE_Xdm10"
    # Models A, B, C, D, and E; Xdm-600
    command_sbd_abcde_06  = command_sbd + s_abcde_06
    command_sbd_abcde_06 += " --outSgnlName ModABCDE_Xdm06"
    # Models A and B; Xdm-1400
    command_sbd_ab_14     = command_sbd + s_ab_14
    command_sbd_ab_14    += " --outSgnlName ModAB_Xdm14"
    # Models A and B; Xdm-1000
    command_sbd_ab_10     = command_sbd + s_ab_10
    command_sbd_ab_10    += " --outSgnlName ModAB_Xdm10"
    # Models A and B; Xdm-600
    command_sbd_ab_06     = command_sbd + s_ab_06
    command_sbd_ab_06    += " --outSgnlName ModAB_Xdm6"
    # Models C, D, and E; Xdm-1400
    command_sbd_cde_14    = command_sbd + s_cde_14
    command_sbd_cde_14   += " --outSgnlName ModCDE_Xdm14"
    # Models C, D, and E; Xdm-1000
    command_sbd_cde_10    = command_sbd + s_cde_10
    command_sbd_cde_10   += " --outSgnlName ModCDE_Xdm10"
    # Models C, D, and E; Xdm-600
    command_sbd_cde_06    = command_sbd + s_cde_06
    command_sbd_cde_06   += " --outSgnlName ModCDE_Xdm6"
    # Model A
    command_sbd_a         = command_sbd + s_a
    command_sbd_a        += " --outSgnlName ModA"
    # Model B
    command_sbd_b         = command_sbd + s_b
    command_sbd_b        += " --outSgnlName ModB"
    # Model C
    command_sbd_c         = command_sbd + s_c
    command_sbd_c        += " --outSgnlName ModC"
    # Model D
    command_sbd_d         = command_sbd + s_d
    command_sbd_d        += " --outSgnlName ModD"
    # Model E
    command_sbd_e         = command_sbd + s_e
    command_sbd_e        += " --outSgnlName ModE"
    # DSID-312004: Model A, Xdm-1400, ctau-20
    command_sbd_04        = command_sbd + s_04
    command_sbd_04       += " --outSgnlName 312004"
    # DSID-312008: Model A, Xdm-1000, ctau-150
    command_sbd_08        = command_sbd + s_08
    command_sbd_08       += " --outSgnlName 312008"
    # DSID-312017: Model A, Xdm-600, ctau-1
    command_sbd_17        = command_sbd + s_17
    command_sbd_17       += " --outSgnlName 312017"
    # DSID-312022: Model B, Xdm-1400, ctau-20
    command_sbd_22        = command_sbd + s_22
    command_sbd_22       += " --outSgnlName 312022"
    # DSID-312028: Model B, Xdm-1000, ctau-5
    command_sbd_28        = command_sbd + s_28
    command_sbd_28       += " --outSgnlName 312028"
    # DSID-312031: Model B, Xdm-600, ctau-300
    command_sbd_31        = command_sbd + s_31
    command_sbd_31       += " --outSgnlName 312031"
    # DSID-312039: Model C, Xdm-1400, ctau-75
    command_sbd_39        = command_sbd + s_39
    command_sbd_39       += " --outSgnlName 312039"
    # DSID-312046: Model C, Xdm-1000, ctau-5
    command_sbd_46        = command_sbd + s_46
    command_sbd_46       += " --outSgnlName 312046"
    # DSID-312052: Model C, Xdm-600, ctau-20
    command_sbd_52        = command_sbd + s_52
    command_sbd_52       += " --outSgnlName 312052"
    # DSID-312060: Model D, Xdm-1400, ctau-20
    command_sbd_60        = command_sbd + s_60
    command_sbd_60       += " --outSgnlName 312060"
    # DSID-312066: Model D, Xdm-1000, ctau-150
    command_sbd_66        = command_sbd + s_66
    command_sbd_66       += " --outSgnlName 312066"
    # DSID-312067: Model D, Xdm-600, ctau-300
    command_sbd_67        = command_sbd + s_67
    command_sbd_67       += " --outSgnlName 312067"
    # DSID-312075: Model A, Xdm-1400, ctau-75
    command_sbd_75        = command_sbd + s_75
    command_sbd_75       += " --outSgnlName 312075"
    # DSID-312080: Model A, Xdm-1000, ctau-150
    command_sbd_80        = command_sbd + s_80
    command_sbd_80       += " --outSgnlName 312080"
    # DSID-312090: Model A, Xdm-600, ctau-0.5
    command_sbd_90        = command_sbd + s_90
    command_sbd_90       += " --outSgnlName 312090"

    
    ## --- update plotting commands --- ##
    command_S  = " --searchDir search"
    command_SJ = " --searchDir jz4w-slice-search"
    command_V  = " --validDir valid"
    command_VJ = " --validDir jz4w-slice-validation"
    
    # abcd plots
    command_abcd        = " --drawABCD --drawNoCutABCD --validOff" # no cuts/counts; plots only w/o lines
    #command_abcd        = " --doABCD --drawABCD"
    command_abcd_noplot = " --doABCD"

    command_sbd_abcde_14_S  = command_sbd_abcde_14 + command_abcd + command_S
    command_sbd_abcde_14_SJ = command_sbd_abcde_14 + command_abcd + command_SJ
    command_sbd_abcde_10_S  = command_sbd_abcde_10 + command_abcd + command_S
    command_sbd_abcde_10_SJ = command_sbd_abcde_10 + command_abcd + command_SJ
    command_sbd_abcde_06_S  = command_sbd_abcde_06 + command_abcd + command_S
    command_sbd_abcde_06_SJ = command_sbd_abcde_06 + command_abcd + command_SJ
    command_sbd_ab_14_S     = command_sbd_ab_14    + command_abcd + command_S
    command_sbd_ab_14_SJ    = command_sbd_ab_14    + command_abcd + command_SJ
    command_sbd_ab_10_S     = command_sbd_ab_10    + command_abcd + command_S
    command_sbd_ab_10_SJ    = command_sbd_ab_10    + command_abcd + command_SJ
    command_sbd_ab_06_S     = command_sbd_ab_06    + command_abcd + command_S
    command_sbd_ab_06_SJ    = command_sbd_ab_06    + command_abcd + command_SJ
    command_sbd_cde_14_S    = command_sbd_cde_14   + command_abcd + command_S
    command_sbd_cde_14_SJ   = command_sbd_cde_14   + command_abcd + command_SJ
    command_sbd_cde_10_S    = command_sbd_cde_10   + command_abcd + command_S
    command_sbd_cde_10_SJ   = command_sbd_cde_10   + command_abcd + command_SJ
    command_sbd_cde_06_S    = command_sbd_cde_06   + command_abcd + command_S
    command_sbd_cde_06_SJ   = command_sbd_cde_06   + command_abcd + command_SJ
    command_sbd_a_S         = command_sbd_a        + command_abcd + command_S
    command_sbd_a_SJ        = command_sbd_a        + command_abcd + command_SJ
    command_sbd_b_S         = command_sbd_b        + command_abcd + command_S
    command_sbd_b_SJ        = command_sbd_b        + command_abcd + command_SJ
    command_sbd_c_S         = command_sbd_c        + command_abcd + command_S
    command_sbd_c_SJ        = command_sbd_c        + command_abcd + command_SJ
    command_sbd_d_S         = command_sbd_d        + command_abcd + command_S
    command_sbd_d_SJ        = command_sbd_d        + command_abcd + command_SJ
    command_sbd_e_S         = command_sbd_e        + command_abcd + command_S
    command_sbd_e_SJ        = command_sbd_e        + command_abcd + command_SJ
    command_sbd_04_S        = command_sbd_04       + command_abcd + command_S
    command_sbd_04_SJ       = command_sbd_04       + command_abcd + command_SJ
    command_sbd_08_S        = command_sbd_08       + command_abcd + command_S
    command_sbd_08_SJ       = command_sbd_08       + command_abcd + command_SJ
    command_sbd_17_S        = command_sbd_17       + command_abcd + command_S
    command_sbd_17_SJ       = command_sbd_17       + command_abcd + command_SJ
    command_sbd_22_S        = command_sbd_22       + command_abcd + command_S
    command_sbd_22_SJ       = command_sbd_22       + command_abcd + command_SJ
    command_sbd_28_S        = command_sbd_28       + command_abcd + command_S
    command_sbd_28_SJ       = command_sbd_28       + command_abcd + command_SJ
    command_sbd_31_S        = command_sbd_31       + command_abcd + command_S
    command_sbd_31_SJ       = command_sbd_31       + command_abcd + command_SJ
    command_sbd_39_S        = command_sbd_31       + command_abcd + command_S
    command_sbd_39_SJ       = command_sbd_31       + command_abcd + command_SJ
    command_sbd_46_S        = command_sbd_46       + command_abcd + command_S
    command_sbd_46_SJ       = command_sbd_46       + command_abcd + command_SJ
    command_sbd_52_S        = command_sbd_52       + command_abcd + command_S
    command_sbd_52_SJ       = command_sbd_52       + command_abcd + command_SJ
    command_sbd_60_S        = command_sbd_60       + command_abcd + command_S
    command_sbd_60_SJ       = command_sbd_60       + command_abcd + command_SJ
    command_sbd_66_S        = command_sbd_66       + command_abcd + command_S
    command_sbd_66_SJ       = command_sbd_66       + command_abcd + command_SJ
    command_sbd_67_S        = command_sbd_67       + command_abcd + command_S
    command_sbd_67_SJ       = command_sbd_67       + command_abcd + command_SJ
    command_sbd_75_S        = command_sbd_75       + command_abcd + command_S
    command_sbd_75_SJ       = command_sbd_75       + command_abcd + command_SJ
    command_sbd_80_S        = command_sbd_80       + command_abcd + command_S
    command_sbd_80_SJ       = command_sbd_80       + command_abcd + command_SJ
    command_sbd_90_S        = command_sbd_90       + command_abcd + command_S
    command_sbd_90_SJ       = command_sbd_90       + command_abcd + command_SJ


    ## --- run jobs --- ##
    # signal vs background
    # --> Models A, B, C, D, and E; Xdm-1400
    os.system( command_sbd_abcde_14_S  )
    os.system( command_sbd_abcde_14_SJ )
    os.system( command_sbd_abcde_10_S  )
    os.system( command_sbd_abcde_10_SJ )
    os.system( command_sbd_abcde_06_S  )
    os.system( command_sbd_abcde_06_SJ )
    # --> Models A and B; Xdm-1400
    os.system( command_sbd_ab_14_S     )
    os.system( command_sbd_ab_14_SJ    )
    # --> Models A and B; Xdm-1000
    os.system( command_sbd_ab_10_S     )
    os.system( command_sbd_ab_10_SJ    )
    # --> Models A and B; Xdm-600
    os.system( command_sbd_ab_06_S     )
    os.system( command_sbd_ab_06_SJ    )
    # --> Models C, D, and E; Xdm-1400
    os.system( command_sbd_cde_14_S    )
    os.system( command_sbd_cde_14_SJ   )
    # --> Models C, D, and E; Xdm-1000
    os.system( command_sbd_cde_10_S    )
    os.system( command_sbd_cde_10_SJ   )
    # --> Models C, D, and E; Xdm-600
    os.system( command_sbd_cde_06_S    )
    os.system( command_sbd_cde_06_SJ   )
    # --> Model A
    os.system( command_sbd_a_S         )
    os.system( command_sbd_a_SJ        )
    # --> Model B
    os.system( command_sbd_b_S         )
    os.system( command_sbd_b_SJ        )
    # --> Model C
    os.system( command_sbd_c_S         )
    os.system( command_sbd_c_SJ        )
    # --> Model D
    os.system( command_sbd_d_S         )
    os.system( command_sbd_d_SJ        )
    # --> Model E
    os.system( command_sbd_e_S         )
    os.system( command_sbd_e_SJ        )
    # --> 312004
    os.system( command_sbd_04_S        )
    os.system( command_sbd_04_SJ       )
    # --> 312008
    os.system( command_sbd_08_S        )
    os.system( command_sbd_08_SJ       )
    # --> 312017
    os.system( command_sbd_17_S        )
    os.system( command_sbd_17_SJ       )
    # --> 312022
    os.system( command_sbd_22_S        )
    os.system( command_sbd_22_SJ       )
    # --> 312028
    os.system( command_sbd_28_S        )
    os.system( command_sbd_28_SJ       )
    # --> 312031
    os.system( command_sbd_31_S        )
    os.system( command_sbd_31_SJ       )
    # --> 312039
    os.system( command_sbd_39_S        )
    os.system( command_sbd_39_SJ       )
    # --> 312046
    os.system( command_sbd_46_S        )
    os.system( command_sbd_46_SJ       )
    # --> 312052
    os.system( command_sbd_52_S        )
    os.system( command_sbd_52_SJ       )
    # --> 312060
    os.system( command_sbd_60_S        )
    os.system( command_sbd_60_SJ       )
    # --> 312066
    os.system( command_sbd_66_S        )
    os.system( command_sbd_66_SJ       )
    # --> 312067
    os.system( command_sbd_67_S        )
    os.system( command_sbd_67_SJ       )
    # --> 312075
    os.system( command_sbd_75_S        )
    os.system( command_sbd_75_SJ       )
    # --> 312080
    os.system( command_sbd_80_S        )
    os.system( command_sbd_80_SJ       )
    # --> 312090
    os.system( command_sbd_90_S        )
    os.system( command_sbd_90_SJ       )
    


     
if __name__ == "__main__":
    main()
