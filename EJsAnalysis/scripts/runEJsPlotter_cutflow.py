#!/usr/bin/env python

###################################################################
# runEJsPlotter_cutflow.py                                        #
###################################################################
# script for running "plotEJsHistograms" for signal cutflow plots #
# #################################################################
# Colleen Treado                                                  #
###################################################################

# TO RUN ON LOCAL MACHINE (NOT CERNVM) NEED TO RUN W/ PYTHON3 --> make compatible with both python versions...
# --> also need to source root directory: 'source /usr/local/Cellar/root/6.16.00/bin/thisroot.sh'
# --> also need to set EJ_PATH in EmergingJetsAnalysis repo when running outside athena: 'export EJ_PATH=$(pwd)'
# --> also need to run with 'python3'

# don't forget to lumi-scale data !!

import os

def main():

    # --> do fill background?
    doFillBkgd = True
        
    ## --- initialize plotting commands --- ##
    # --> change when needed
    inDir   = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-06_mod/EJsNtupToHistOutput/njetx_abcd/"
    outDir  = os.getenv('EJ_PATH') + "/../output/gridOutput/v0_2020-06_mod/plots/njetx_abcd/"
    #inDir   = os.getenv('EJ_PATH') + "/../run/test.histos/EJsNtupToHistOutput/"
    pscript = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/plotting/plotEJsHistograms.py"
    #command = "python "  + pscript + " --inDir " + inDir + " --outDir " + outDir
    command = "python3 " + pscript + " --inDir " + inDir + " --outDir " + outDir # for running outside of athena

    # signal
    s_14         = " --sgnlType 312004,312022,312039,312060,312075" # xdm-1400
    s_10         = " --sgnlType 312008,312028,312046,312066,312080" # xdm-1000
    s_06         = " --sgnlType 312017,312031,312052,312067,312090" # xdm-600
    command_s    = command
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


    # 1d plots -- comparing same cutflows over different samples
    nej = [ "0LEJ", "1LEJ", "2LEJ", "0TEJ", "1TEJ", "2TEJ" ]
    ndv = [ "2LDV", "3LDV", "4LDV", "2MDV", "3MDV", "4MDV", "2TDV", "3TDV", "4TDV" ]
    histList_1d = "cutflow+signal"
    command_1d  = " --draw1D --outSubdir 1d_sgnlcut --lstyleEnum 1 --legLenEnum 5 --drawSOverB --lxl 0.590"
    if doFillBkgd:
        command_1d += " --fillBkgd"
    command_1d_l1 = " --lxint 0.006 --lyint 0.025" # for s vs b
    command_1d_l2 = " --lxint 0.015 --lyint 0.040" # for b vs d
    command_1di = []
    for ej in nej :
        for dv in ndv:
            histList = ej + "+" + dv
            histList += "+" + histList_1d
            command_1di.append( command_1d + " --histList " + histList )
    command_sb_14_1d_S, command_sb_14_1d_SJ = [], []
    command_sb_10_1d_S, command_sb_10_1d_SJ = [], []
    command_sb_06_1d_S, command_sb_06_1d_SJ = [], []
    command_bd_1d_V,    command_bd_1d_VJ    = [], []
    for iC, command in enumerate( command_1di ):
        command_sb_14_1d_S  .append( command_sb_14 + command + command_1d_l1 + command_S  ) # xdm-1400 signal vs background
        command_sb_14_1d_SJ .append( command_sb_14 + command + command_1d_l1 + command_SJ )
        command_sb_10_1d_S  .append( command_sb_10 + command + command_1d_l1 + command_S  ) # xdm-1000 signal vs background
        command_sb_10_1d_SJ .append( command_sb_10 + command + command_1d_l1 + command_SJ )
        command_sb_06_1d_S  .append( command_sb_06 + command + command_1d_l1 + command_S  ) # xdm-600 signal vs background
        command_sb_06_1d_SJ .append( command_sb_06 + command + command_1d_l1 + command_SJ )
        command_bd_1d_V     .append( command_bd    + command + command_1d_l2 + command_V  ) # background vs data
        command_bd_1d_VJ    .append( command_bd    + command + command_1d_l2 + command_VJ )


    ## --- run plotting jobs --- ##
    # 1d: signal vs background
    #for c_sb14S  in command_sb_14_1d_S:  # xdm-1400
    #    os.system( c_sb14S  )
    #for c_sb14SJ in command_sb_14_1d_SJ:
    #    os.system( c_sb14SJ )
    #for c_sb10S  in command_sb_10_1d_S:  # xdm-1000
    #    os.system( c_sb10S  )
    for c_sb10SJ in command_sb_10_1d_SJ:
        os.system( c_sb10SJ )
    for c_sb06S  in command_sb_06_1d_S:  # xdm-600
        os.system( c_sb06S  )
    for c_sb06SJ in command_sb_06_1d_SJ:
        os.system( c_sb06SJ )
    ## 1d: background vs data
    #for c_bdV  in command_bd_1d_V:
    #    os.system( c_bdV  )
    #for c_bdVJ in command_bd_1d_VJ:
    #    os.system( c_bdVJ )


    
# run main
if __name__ == "__main__":
    main()
