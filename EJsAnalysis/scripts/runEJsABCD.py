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
    inDir      = os.getenv('EJ_PATH')  + "/../output/gridOutput/v0_2020-06_mod/EJsNtupToHistOutput/njetx_abcd/"
    outDir     = os.getenv('EJ_PATH')  + "/../output/gridOutput/v0_2020-06_mod/plots/njetx_abcd/"
    outTextDir = os.getenv('EJ_PATH')  + "/../output/gridOutput/v0_2020-06_mod/text_files/njetx_abcd/"
    #inDir      = os.getenv('EJ_PATH')  + "/../run/test.histos/EJsNtupToHistOutput/"
    pscript    = os.getenv('EJ_PATH')  + "/EJsAnalysis/scripts/plotting/plotEJsABCD.py"
    pscript2   = os.getenv('EJ_PATH')  + "/EJsAnalysis/scripts/plotting/plotEJsHistograms.py"
    #command    = "python "  + pscript  + " --inDir " + inDir + " --outDir " + outDir + " --outTextDir " + outTextDir
    command    = "python3 " + pscript  + " --inDir " + inDir + " --outDir " + outDir + " --outTextDir " + outTextDir # for running outside of athena
    command2   = "python3 " + pscript2 + " --inDir " + inDir + " --outDir " + outDir

    # signal
    s_sub15    = " --sgnlType 312004,312008,312017,312022,312028,312031,312039,312046,312052,312060,312066,312067,312075,312080,312090"
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
    d        = " --dataType data17 --scaleData " \
      + " --metadataDir " + os.getenv('EJ_PATH')  + "/../output/gridOutput/v0_2020-01_full/metadata/"

    # signal vs background
    command_sbd           = command
    command_sbd          += b
    command_sbd          += d
    # all sub-15 signal samples
    command_sbd_sub15     = command_sbd + s_sub15
    command_sbd_sub15    += " --outSgnlName sub15"
    # Models A, B, C, D, and E; Xdm-1400
    command_sbd_abcde_14  = command_sbd + s_abcde_14
    command_sbd_abcde_14 += " --outSgnlName ModABCDE_Xdm-14"
    # Models A, B, C, D, and E; Xdm-1000
    command_sbd_abcde_10  = command_sbd + s_abcde_10
    command_sbd_abcde_10 += " --outSgnlName ModABCDE_Xdm-10"
    # Models A, B, C, D, and E; Xdm-600
    command_sbd_abcde_06  = command_sbd + s_abcde_06
    command_sbd_abcde_06 += " --outSgnlName ModABCDE_Xdm-06"
    # Models A and B; Xdm-1400
    command_sbd_ab_14     = command_sbd + s_ab_14
    command_sbd_ab_14    += " --outSgnlName ModAB_Xdm-14"
    # Models A and B; Xdm-1000
    command_sbd_ab_10     = command_sbd + s_ab_10
    command_sbd_ab_10    += " --outSgnlName ModAB_Xdm-10"
    # Models A and B; Xdm-600
    command_sbd_ab_06     = command_sbd + s_ab_06
    command_sbd_ab_06    += " --outSgnlName ModAB_Xdm-6"
    # Models C, D, and E; Xdm-1400
    command_sbd_cde_14    = command_sbd + s_cde_14
    command_sbd_cde_14   += " --outSgnlName ModCDE_Xdm-14"
    # Models C, D, and E; Xdm-1000
    command_sbd_cde_10    = command_sbd + s_cde_10
    command_sbd_cde_10   += " --outSgnlName ModCDE_Xdm-10"
    # Models C, D, and E; Xdm-600
    command_sbd_cde_06    = command_sbd + s_cde_06
    command_sbd_cde_06   += " --outSgnlName ModCDE_Xdm-6"
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

    # profile plots
    command2_b            = command2 + b
    command2_b           += " --histTitle 'background'"
    command2_b           += " --outName bkgd"
    command2_bd           = command2 + b + d
    command2_bd          += " --histTitle 'background vs data'"
    command2_bd          += " --outName bkgd-data"
    command2_s_14         = command2 + s_abcde_14
    command2_s_14        += " --histTitle 'X_{dm} = 1400 GeV signal vs background'"
    command2_s_14        += " --outName xdm-14"
    command2_s_10         = command2 + s_abcde_10
    command2_s_10        += " --histTitle 'X_{dm} = 1000 GeV signal vs background'"
    command2_s_10        += " --outName xdm-10"
    command2_s_06         = command2 + s_abcde_06
    command2_s_06        += " --histTitle 'X_{dm} = 600 GeV signal vs background'"
    command2_s_06        += " --outName xdm-6"

    
    ## --- update plotting commands --- ##
    command_S   = " --searchDir search"
    command_SJ  = " --searchDir jz4w-slice-search"
    command_V   = " --validDir valid"
    command_VJ  = " --validDir jz4w-slice-validation"
    command2_S  = " --regionDir search"
    command2_SJ = " --regionDir jz4w-slice-search"
    command2_V  = " --regionDir valid"
    command2_VJ = " --regionDir jz4w-slice-validation"
    
    # abcd plots
    #command_abcd        = " --drawABCD --drawNoCutABCD --validOff" # no cuts/counts; plots only w/o lines
    command_abcd        = " --drawABCD --validOff --histList :vrsh"
    #command_abcd        = " --doABCD --drawABCD"
    command_abcd_noplot = " --doABCD --histList ABCD:vrsh"

    command_abcd_S     = command_abcd        + command_S
    command_abcd_SJ    = command_abcd        + command_SJ
    command_abcd_np_S  = command_abcd_noplot + command_S  + " --validOff"
    command_abcd_np_SJ = command_abcd_noplot + command_SJ + " --validOff"
    command_abcd_np_V  = command_abcd_noplot + command_V  + " --searchOff"
    command_abcd_np_VJ = command_abcd_noplot + command_VJ + " --searchOff"

    command_sbd_sub15_S ,   command_sbd_sub15_SJ    = [], []
    command_sbd_V,          command_sbd_VJ          = [], []
    command_sbd_abcde_14_S, command_sbd_abcde_14_SJ = [], []
    command_sbd_abcde_10_S, command_sbd_abcde_10_SJ = [], []
    command_sbd_abcde_06_S, command_sbd_abcde_06_SJ = [], []
    command_sbd_ab_14_S,    command_sbd_ab_14_SJ    = [], []
    command_sbd_ab_10_S,    command_sbd_ab_10_SJ    = [], []
    command_sbd_ab_06_S,    command_sbd_ab_06_SJ    = [], []
    command_sbd_cde_14_S,   command_sbd_cde_14_SJ   = [], []
    command_sbd_cde_10_S,   command_sbd_cde_10_SJ   = [], []
    command_sbd_cde_06_S,   command_sbd_cde_06_SJ   = [], []
    command_sbd_a_S,        command_sbd_a_SJ        = [], []
    command_sbd_b_S,        command_sbd_b_SJ        = [], []
    command_sbd_c_S,        command_sbd_c_SJ        = [], []
    command_sbd_d_S,        command_sbd_d_SJ        = [], []
    command_sbd_e_S,        command_sbd_e_SJ        = [], []
    command_sbd_04_S,       command_sbd_04_SJ       = [], []
    command_sbd_08_S,       command_sbd_08_SJ       = [], []
    command_sbd_17_S,       command_sbd_17_SJ       = [], []
    command_sbd_22_S,       command_sbd_22_SJ       = [], []
    command_sbd_28_S,       command_sbd_28_SJ       = [], []
    command_sbd_31_S,       command_sbd_31_SJ       = [], []
    command_sbd_39_S,       command_sbd_39_SJ       = [], []
    command_sbd_46_S,       command_sbd_46_SJ       = [], []
    command_sbd_52_S,       command_sbd_52_SJ       = [], []
    command_sbd_60_S,       command_sbd_60_SJ       = [], []
    command_sbd_66_S,       command_sbd_66_SJ       = [], []
    command_sbd_67_S,       command_sbd_67_SJ       = [], []
    command_sbd_75_S,       command_sbd_75_SJ       = [], []
    command_sbd_80_S,       command_sbd_80_SJ       = [], []
    command_sbd_90_S,       command_sbd_90_SJ       = [], []
    for i in range(1,15): # x cuts
        for j in range(2,5): # y cuts
            xycut = " --xCutABCDEnum " + str(i) + " --yCutABCDEnum " + str(j)
            config = " --lxint 0.09 --lyint 0.042 --lxl 0.300 --lxr 0.850 --ncontours 10"
            command_sbd_sub15_S     .append( command_sbd_sub15    + command_abcd_np_S  + xycut          )
            command_sbd_sub15_SJ    .append( command_sbd_sub15    + command_abcd_np_SJ + xycut          )
            command_sbd_V           .append( command_sbd          + command_abcd_np_V  + xycut          )
            command_sbd_VJ          .append( command_sbd          + command_abcd_np_VJ + xycut          )
            command_sbd_abcde_14_S  .append( command_sbd_abcde_14 + command_abcd_S     + xycut + config )
            command_sbd_abcde_14_SJ .append( command_sbd_abcde_14 + command_abcd_SJ    + xycut + config )
            command_sbd_abcde_10_S  .append( command_sbd_abcde_10 + command_abcd_S     + xycut + config )
            command_sbd_abcde_10_SJ .append( command_sbd_abcde_10 + command_abcd_SJ    + xycut + config )
            command_sbd_abcde_06_S  .append( command_sbd_abcde_06 + command_abcd_S     + xycut + config )
            command_sbd_abcde_06_SJ .append( command_sbd_abcde_06 + command_abcd_SJ    + xycut + config )
            command_sbd_ab_14_S     .append( command_sbd_ab_14    + command_abcd_S     + xycut + config )
            command_sbd_ab_14_SJ    .append( command_sbd_ab_14    + command_abcd_SJ    + xycut + config )
            command_sbd_ab_10_S     .append( command_sbd_ab_10    + command_abcd_S     + xycut + config )
            command_sbd_ab_10_SJ    .append( command_sbd_ab_10    + command_abcd_SJ    + xycut + config )
            command_sbd_ab_06_S     .append( command_sbd_ab_06    + command_abcd_S     + xycut + config )
            command_sbd_ab_06_SJ    .append( command_sbd_ab_06    + command_abcd_SJ    + xycut + config )
            command_sbd_cde_14_S    .append( command_sbd_cde_14   + command_abcd_S     + xycut + config )
            command_sbd_cde_14_SJ   .append( command_sbd_cde_14   + command_abcd_SJ    + xycut + config )
            command_sbd_cde_10_S    .append( command_sbd_cde_10   + command_abcd_S     + xycut + config )
            command_sbd_cde_10_SJ   .append( command_sbd_cde_10   + command_abcd_SJ    + xycut + config )
            command_sbd_cde_06_S    .append( command_sbd_cde_06   + command_abcd_S     + xycut + config )
            command_sbd_cde_06_SJ   .append( command_sbd_cde_06   + command_abcd_SJ    + xycut + config )
            command_sbd_a_S         .append( command_sbd_a        + command_abcd_S     + xycut + config )
            command_sbd_a_SJ        .append( command_sbd_a        + command_abcd_SJ    + xycut + config )
            command_sbd_b_S         .append( command_sbd_b        + command_abcd_S     + xycut + config )
            command_sbd_b_SJ        .append( command_sbd_b        + command_abcd_SJ    + xycut + config )
            command_sbd_c_S         .append( command_sbd_c        + command_abcd_S     + xycut + config )
            command_sbd_c_SJ        .append( command_sbd_c        + command_abcd_SJ    + xycut + config )
            command_sbd_d_S         .append( command_sbd_d        + command_abcd_S     + xycut + config )
            command_sbd_d_SJ        .append( command_sbd_d        + command_abcd_SJ    + xycut + config )
            command_sbd_e_S         .append( command_sbd_e        + command_abcd_S     + xycut + config )
            command_sbd_e_SJ        .append( command_sbd_e        + command_abcd_SJ    + xycut + config )
            command_sbd_04_S        .append( command_sbd_04       + command_abcd_S     + xycut + config )
            command_sbd_04_SJ       .append( command_sbd_04       + command_abcd_SJ    + xycut + config )
            command_sbd_08_S        .append( command_sbd_08       + command_abcd_S     + xycut + config )
            command_sbd_08_SJ       .append( command_sbd_08       + command_abcd_SJ    + xycut + config )
            command_sbd_17_S        .append( command_sbd_17       + command_abcd_S     + xycut + config )
            command_sbd_17_SJ       .append( command_sbd_17       + command_abcd_SJ    + xycut + config )
            command_sbd_22_S        .append( command_sbd_22       + command_abcd_S     + xycut + config )
            command_sbd_22_SJ       .append( command_sbd_22       + command_abcd_SJ    + xycut + config )
            command_sbd_28_S        .append( command_sbd_28       + command_abcd_S     + xycut + config )
            command_sbd_28_SJ       .append( command_sbd_28       + command_abcd_SJ    + xycut + config )
            command_sbd_31_S        .append( command_sbd_31       + command_abcd_S     + xycut + config )
            command_sbd_31_SJ       .append( command_sbd_31       + command_abcd_SJ    + xycut + config )
            command_sbd_39_S        .append( command_sbd_39       + command_abcd_S     + xycut + config )
            command_sbd_39_SJ       .append( command_sbd_39       + command_abcd_SJ    + xycut + config )
            command_sbd_46_S        .append( command_sbd_46       + command_abcd_S     + xycut + config )
            command_sbd_46_SJ       .append( command_sbd_46       + command_abcd_SJ    + xycut + config )
            command_sbd_52_S        .append( command_sbd_52       + command_abcd_S     + xycut + config )
            command_sbd_52_SJ       .append( command_sbd_52       + command_abcd_SJ    + xycut + config )  
            command_sbd_60_S        .append( command_sbd_60       + command_abcd_S     + xycut + config )
            command_sbd_60_SJ       .append( command_sbd_60       + command_abcd_SJ    + xycut + config )
            command_sbd_66_S        .append( command_sbd_66       + command_abcd_S     + xycut + config )
            command_sbd_66_SJ       .append( command_sbd_66       + command_abcd_SJ    + xycut + config )
            command_sbd_67_S        .append( command_sbd_67       + command_abcd_S     + xycut + config )
            command_sbd_67_SJ       .append( command_sbd_67       + command_abcd_SJ    + xycut + config )
            command_sbd_75_S        .append( command_sbd_75       + command_abcd_S     + xycut + config )
            command_sbd_75_SJ       .append( command_sbd_75       + command_abcd_SJ    + xycut + config )
            command_sbd_80_S        .append( command_sbd_80       + command_abcd_S     + xycut + config )
            command_sbd_80_SJ       .append( command_sbd_80       + command_abcd_SJ    + xycut + config )
            command_sbd_90_S        .append( command_sbd_90       + command_abcd_S     + xycut + config )
            command_sbd_90_SJ       .append( command_sbd_90       + command_abcd_SJ    + xycut + config )

            
    # abcd profile plots
    histList_prof         = "ABCD:vrsh"
    command_prof          = " --draw1D --outSubdir abcd_prof --histList " + histList_prof + " --doProfileX"
    command_prof_l1       = " --lxint 0.006 --lyint 0.030" # for s vs b
    command_prof_l2       = " --lxint 0.015 --lyint 0.040" # for b vs d
    command2_bd_prof_V    = command2_bd   + command_prof + command2_V  + command_prof_l2
    command2_bd_prof_VJ   = command2_bd   + command_prof + command2_VJ + command_prof_l2
    command2_b_prof_S     = command2_b    + command_prof + command2_S  + command_prof_l2
    command2_b_prof_SJ    = command2_b    + command_prof + command2_SJ + command_prof_l2
    command2_s_14_prof_S  = command2_s_14 + command_prof + command2_S  + command_prof_l1
    command2_s_14_prof_SJ = command2_s_14 + command_prof + command2_SJ + command_prof_l1
    command2_s_10_prof_S  = command2_s_10 + command_prof + command2_S  + command_prof_l1
    command2_s_10_prof_SJ = command2_s_10 + command_prof + command2_SJ + command_prof_l1
    command2_s_06_prof_S  = command2_s_06 + command_prof + command2_S  + command_prof_l1
    command2_s_06_prof_SJ = command2_s_06 + command_prof + command2_SJ + command_prof_l1


    ## --- run jobs --- ##
    # NEED TO UPDATE LEGEND SIZES / POSITIONS -- test subset of each run before running over full set
    # ... also want to update text files to output all info, background estimates only, run over data, etc.
    # signal vs background
    #for ic, cmnd in enumerate( command_sbd_sub15_S ):
        #os.system( command_sbd_sub15_S   [ic] )
        #os.system( command_sbd_sub15_SJ  [ic] )
        #os.system( command_sbd_V         [ic] )
        #os.system( command_sbd_VJ        [ic] )
        # --> Models A, B, C, D, and E
        #os.system( command_sbd_abcde_14_S [ic] ) # Xdm-1400
        #os.system( command_sbd_abcde_14_SJ[ic] )
        #os.system( command_sbd_abcde_10_S [ic] ) # Xdm-1000
        #os.system( command_sbd_abcde_10_SJ[ic] )
        #os.system( command_sbd_abcde_06_S [ic] ) # Xdm-600
        #os.system( command_sbd_abcde_06_SJ[ic] )
        ## --> Models A and B
        #os.system( command_sbd_ab_14_S    [ic] ) # Xdm-1400
        ##os.system( command_sbd_ab_14_SJ   [ic] )
        #os.system( command_sbd_ab_10_S    [ic] ) # Xdm-1000
        ##os.system( command_sbd_ab_10_SJ   [ic] )
        #os.system( command_sbd_ab_06_S    [ic] ) # Xdm-600
        ##os.system( command_sbd_ab_06_SJ   [ic] )
        ## --> Models C, D, and E
        #os.system( command_sbd_cde_14_S   [ic] ) # Xdm-1400
        ##os.system( command_sbd_cde_14_SJ  [ic] )
        #os.system( command_sbd_cde_10_S   [ic] ) # Xdm-1000
        ##os.system( command_sbd_cde_10_SJ  [ic] )
        #os.system( command_sbd_cde_06_S   [ic] ) # Xdm-600
        ##os.system( command_sbd_cde_06_SJ  [ic] )
        ## --> individual models
        #os.system( command_sbd_a_S        [ic] ) # Model A
        ##os.system( command_sbd_a_SJ       [ic] )
        #os.system( command_sbd_b_S        [ic] ) # Model B
        ##os.system( command_sbd_b_SJ       [ic] )
        #os.system( command_sbd_c_S        [ic] ) # Model C
        ##os.system( command_sbd_c_SJ       [ic] )
        #os.system( command_sbd_d_S        [ic] ) # Model D
        ##os.system( command_sbd_d_SJ       [ic] )
        #os.system( command_sbd_e_S        [ic] ) # Model E
        ##os.system( command_sbd_e_SJ       [ic] )
        ## --> individual signal points
        #os.system( command_sbd_04_S       [ic] ) # 312004
        ##os.system( command_sbd_04_SJ      [ic] )
        #os.system( command_sbd_08_S       [ic] ) # 312008
        ##os.system( command_sbd_08_SJ      [ic] )
        #os.system( command_sbd_17_S       [ic] ) # 312017
        ##os.system( command_sbd_17_SJ      [ic] )
        #os.system( command_sbd_22_S       [ic] ) # 312022
        ##os.system( command_sbd_22_SJ      [ic] )
        #os.system( command_sbd_28_S       [ic] ) # 312028
        ##os.system( command_sbd_28_SJ      [ic] )
        #os.system( command_sbd_31_S       [ic] ) # 312031
        ##os.system( command_sbd_31_SJ      [ic] )
        #os.system( command_sbd_39_S       [ic] ) # 312039
        ##os.system( command_sbd_39_SJ      [ic] )
        #os.system( command_sbd_46_S       [ic] ) # 312046
        ##os.system( command_sbd_46_SJ      [ic] ) 
        #os.system( command_sbd_52_S       [ic] ) # 312052
        ##os.system( command_sbd_52_SJ      [ic] )
        #os.system( command_sbd_60_S       [ic] ) # 312060
        ##os.system( command_sbd_60_SJ      [ic] )
        #os.system( command_sbd_66_S       [ic] ) # 312066
        ##os.system( command_sbd_66_SJ      [ic] )
        #os.system( command_sbd_67_S       [ic] ) # 312067
        ##os.system( command_sbd_67_SJ      [ic] )
        #os.system( command_sbd_75_S       [ic] ) # 312075
        ##os.system( command_sbd_75_SJ      [ic] )
        #os.system( command_sbd_80_S       [ic] ) # 312080
        ##os.system( command_sbd_80_SJ      [ic] )
        #os.system( command_sbd_90_S       [ic] ) # 312090
        ##os.system( command_sbd_90_SJ      [ic] )


    os.system( command2_bd_prof_V    )
    os.system( command2_bd_prof_VJ   )
    os.system( command2_b_prof_S     )
    os.system( command2_b_prof_SJ    )
    #os.system( command2_s_14_prof_S  )
    #os.system( command2_s_14_prof_SJ )
    #os.system( command2_s_10_prof_S  )
    #os.system( command2_s_10_prof_SJ )
    #os.system( command2_s_06_prof_S  )
    #os.system( command2_s_06_prof_SJ )
    


     
if __name__ == "__main__":
    main()
