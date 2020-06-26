#!/usr/bin/env python

##########################################################
# runEJsPlotter_jets.py                                  #
##########################################################
# script for running "plotEJsHistograms" for truth plots #
# ########################################################
# Colleen Treado                                         #
##########################################################

# don't forget to lumi-scale data !!

import os

def main():

    ## --- initialize plotting commands --- ##
    # --> change when needed
    #inDir   = os.getenv('EJ_PATH') + "/../output/localOutput/truth_fix-vs-run/EJsNtupToHistOutput/"
    inDir   = os.getenv('EJ_PATH') + "/../output/localOutput/truth_grid/EJsNtupToHistOutput/"
    pscript = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/plotting/plotEJsHistograms.py"
    command = "python " + pscript + " --inDir " + inDir

    command_S1  = " --regionDir search-minus-one"
    command_All = " --regionDir all"

    
    # fixed vs running coupling
    s_fvr_A             = " --sgnlType ModA_run,ModA_fix"
    s_fvr_B             = " --sgnlType ModB_run,ModB_fix"
    command_fvr         = command + " --draw1D --outSubdir fix_v_run --histList ':kshort' --lxint 0.015 --lyint 0.050"
    command_s_fvr_A     = command_fvr + s_fvr_A + " --outName fix-vs-run.A --histTitle 'fixed vs running coupling: ModelA_1000_150'"
    command_s_fvr_B     = command_fvr + s_fvr_B + " --outName fix-vs-run.B --histTitle 'fixed vs running coupling: ModelB_1000_5'"
    command_s_fvr_A_S1  = command_s_fvr_A + command_S1
    command_s_fvr_B_S1  = command_s_fvr_B + command_S1
    command_s_fvr_A_All = command_s_fvr_A + command_All
    command_s_fvr_B_All = command_s_fvr_B + command_All

    #os.system( command_s_fvr_A_S1  )
    #os.system( command_s_fvr_B_S1  )
    ##os.system( command_s_fvr_A_All )
    ##os.system( command_s_fvr_B_All )


    # truth grid --> play around with lifetime colors, samples to plot against each other (plot by model, by xdm, by lifetime, etc.)
    # --> fix input/output paths above; add argument to override sampleDict colors
    command_grid        = command + " --draw1D --outSubdir grid --histList 'NJetHt,DecayVtx_r:kshort=vrsh'"
    
    s_150               = " --sgnlType modA_1400_150,modA_1000_150,modA_600_150,modB_1400_150,modB_1000_150,modB_600_150," + \
      "modC_1400_150,modC_1000_150,modC_600_150,modD_1400_150,modD_1000_150,modD_600_150,modE_1400_150,modE_1000_150,modE_600_150"
    command_s_150       = command_grid + s_150 + " --outName grid.150 --histTitle 'ctau = 150 mm' --lstyleEnum 3 --legLenEnum 4 " + \
      "--lxint 0.007 --lyint 0.025"
    command_s_150_S1    = command_s_150 + command_S1

    s_1400_150          = " --sgnlType modA_1400_150,modB_1400_150,modC_1400_150,modD_1400_150,modD_1400_150"
    s_1000_150          = " --sgnlType modA_1000_150,modB_1000_150,modC_1000_150,modD_1000_150,modD_1000_150"
    s_600_150           = " --sgnlType modA_600_150,modB_600_150,modC_600_150,modD_600_150,modD_600_150"
    command_s_1400_150    = command_grid + s_1400_150 + " --outName grid.1400.150 --histTitle 'Xdm = 1400 GeV, ctau = 150 mm'"
    command_s_1000_150    = command_grid + s_1000_150 + " --outName grid.1000.150 --histTitle 'Xdm = 1000 GeV, ctau = 150 mm'"
    command_s_600_150     = command_grid + s_600_150  + " --outName grid.600.150 --histTitle 'Xdm = 600 GeV, ctau = 150 mm'"
    command_s_1400_150_S1 = command_s_1400_150 + command_S1
    command_s_1000_150_S1 = command_s_1000_150 + command_S1
    command_s_600_150_S1  = command_s_600_150  + command_S1

    s_A_style           = " --lstyleEnum 2 --legLenEnum 10 --lxint 0.01 --lyint 0.035"
    s_A_1400            = " --sgnlType modA_1400_300,modA_1400_150,modA_1400_75,modA_1400_20,modA_1400_5,modA_1400_2"
    s_A_1000            = " --sgnlType modA_1000_300,modA_1000_150,modA_1000_75,modA_1000_5,modA_1000_2,modA_1000_1"
    s_A_600             = " --sgnlType modA_600_300,modA_600_150,modA_600_20,modA_600_2,modA_600_1,modA_600_20p5"
    command_A_1400      = command_grid + s_A_1400 + s_A_style + " --outName grid.A.1400 --histTitle 'Model A, Xdm = 1400 GeV'"
    command_A_1000      = command_grid + s_A_1000 + s_A_style + " --outName grid.A.1000 --histTitle 'Model A, Xdm = 1000 GeV'"
    command_A_600       = command_grid + s_A_600  + s_A_style + " --outName grid.A.600 --histTitle 'Model A, Xdm = 600 GeV'"
    command_A_1400_S1   = command_A_1400 + command_S1
    command_A_1000_S1   = command_A_1000 + command_S1
    command_A_600_S1    = command_A_600  + command_S1
    
    s_B_1400            = " --sgnlType modB_1400_300,modB_1400_150,modB_1400_75,modB_1400_20,modB_1400_5,modB_1400_2"
    s_B_1000            = " --sgnlType modB_1000_300,modB_1000_150,modB_1000_75,modB_1000_5,modB_1000_2,modB_1000_1"
    s_B_600             = " --sgnlType modB_600_300,modB_600_150,modB_600_20,modB_600_2,modB_600_1,modB_600_20p5"
    command_B_1400      = command + command_grid + s_B_1400 + " --outName grid.B.1400 --histTitle 'Model B, Xdm = 1400 GeV'"
    command_B_1000      = command + command_grid + s_B_1000 + " --outName grid.B.1000 --histTitle 'Model B, Xdm = 1000 GeV'"
    command_B_600       = command + command_grid + s_B_600  + " --outName grid.B.600 --histTitle 'Model B, Xdm = 600 GeV'"
    command_B_1400_S1   = command_B_1400 + command_S1
    command_B_1000_S1   = command_B_1000 + command_S1
    command_B_600_S1    = command_B_600  + command_S1

    s_C_1400            = " --sgnlType modC_1400_300,modC_1400_150,modC_1400_75,modC_1400_20,modC_1400_5,modC_1400_2"
    s_C_1000            = " --sgnlType modC_1000_300,modC_1000_150,modC_1000_75,modC_1000_5,modC_1000_2,modC_1000_1"
    s_C_600             = " --sgnlType modC_600_300,modC_600_150,modC_600_20,modC_600_2,modC_600_1,modC_600_20p5"
    command_C_1400      = command + command_grid + s_C_1400 + " --outName grid.C.1400 --histTitle 'Model C, Xdm = 1400 GeV'"
    command_C_1000      = command + command_grid + s_C_1000 + " --outName grid.C.1000 --histTitle 'Model C, Xdm = 1000 GeV'"
    command_C_600       = command + command_grid + s_C_600  + " --outName grid.C.600 --histTitle 'Model C, Xdm = 600 GeV'"
    command_C_1400_S1   = command_C_1400 + command_S1
    command_C_1000_S1   = command_C_1000 + command_S1
    command_C_600_S1    = command_C_600  + command_S1

    s_D_1400            = " --sgnlType modD_1400_300,modD_1400_150,modD_1400_75,modD_1400_20,modD_1400_5,modD_1400_2"
    s_D_1000            = " --sgnlType modD_1000_300,modD_1000_150,modD_1000_75,modD_1000_5,modD_1000_2,modD_1000_1"
    s_D_600             = " --sgnlType modD_600_300,modD_600_150,modD_600_20,modD_600_2,modD_600_1,modD_600_20p5"
    command_D_1400      = command + command_grid + s_D_1400 + " --outName grid.D.1400 --histTitle 'Model D, Xdm = 1400 GeV'"
    command_D_1000      = command + command_grid + s_D_1000 + " --outName grid.D.1000 --histTitle 'Model D, Xdm = 1000 GeV'"
    command_D_600       = command + command_grid + s_D_600  + " --outName grid.D.600 --histTitle 'Model D, Xdm = 600 GeV'"
    command_D_1400_S1   = command_D_1400 + command_S1
    command_D_1000_S1   = command_D_1000 + command_S1
    command_D_600_S1    = command_D_600  + command_S1

    s_E_1400            = " --sgnlType modE_1400_300,modE_1400_150,modE_1400_75,modE_1400_20,modE_1400_5,modE_1400_2"
    s_E_1000            = " --sgnlType modE_1000_300,modE_1000_150,modE_1000_75,modE_1000_5,modE_1000_2,modE_1000_1"
    s_E_600             = " --sgnlType modE_600_300,modE_600_150,modE_600_20,modE_600_2,modE_600_1,modE_600_20p5"
    command_E_1400      = command + command_grid + s_E_1400 + " --outName grid.E.1400 --histTitle 'Model E, Xdm = 1400 GeV'"
    command_E_1000      = command + command_grid + s_E_1000 + " --outName grid.E.1000 --histTitle 'Model E, Xdm = 1000 GeV'"
    command_E_600       = command + command_grid + s_E_600  + " --outName grid.E.600 --histTitle 'Model E, Xdm = 600 GeV'"
    command_E_1400_S1   = command_E_1400 + command_S1
    command_E_1000_S1   = command_E_1000 + command_S1
    command_E_600_S1    = command_E_600  + command_S1

    s_1400_mix          = " --sgnlType ModA_1400_20,modB_1400_300,modC_1400_2,modD_1400_75,modE_1400_5"
    s_1000_mix          = " --sgnlType ModA_1000_150,modB_1000_5,modC_1000_75,modD_1000_2,modE_1000_300"
    s_600_mix           = " --sgnlType ModA_600_2,modB_600_5,modC_600_0p5,modD_600_150,modE_600_20"
    command_1400_mix    = command + command_grid + s_1400_mix + " --outName grid.1400.mix --histTitle 'Xdm = 1400 GeV'"
    command_1000_mix    = command + command_grid + s_1000_mix + " --outName grid.1000.mix --histTitle 'Xdm = 1000 GeV'"
    command_600_mix     = command + command_grid + s_600_mix  + " --outName grid.600.mix --histTitle 'Xdm = 600 GeV'"
    command_1400_mix_S1 = command_1400_mix + command_S1
    command_1000_mix_S1 = command_1000_mix + command_S1
    command_600_mix_S1  = command_600_mix  + command_S1
    

    os.system( command_s_150_S1 )
    #os.system( command_s_1400_150_S1 )
    #os.system( command_s_1000_150_S1 )
    #os.system( command_s_600_150_S1  )
    os.system( command_A_1400_S1     )
    #os.system( command_A_1000_S1     )
    #os.system( command_A_600_S1      )
    #os.system( command_B_1400_S1     )
    #os.system( command_B_1000_S1     )
    #os.system( command_B_600_S1      )
    #os.system( command_C_1400_S1     )
    #os.system( command_C_1000_S1     )
    #os.system( command_C_600_S1      )
    #os.system( command_D_1400_S1     )
    #os.system( command_D_1000_S1     )
    #os.system( command_D_600_S1      )
    #os.system( command_E_1400_S1     )
    #os.system( command_E_1000_S1     )
    #os.system( command_E_600_S1      )
    #os.system( command_1400_mix_S1   )
    #os.system( command_1000_mix_S1   )
    #os.system( command_600_mix_S1    )
    


if __name__ == "__main__":
    main()

    
