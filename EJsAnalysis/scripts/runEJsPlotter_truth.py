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
    command_fvr         = command + " --draw1D --outSubdir fix_v_run --histList ':kshort=vrsh' --lxint 0.015 --lyint 0.050"
    command_s_fvr_A     = command_fvr + s_fvr_A + " --outName fix-vs-run.A" + \
      " --histTitle 'fixed vs running coupling: Model A (#pi_{dm} = 5 GeV); #chi_{dm} = 1000 GeV; c#tau = 150 mm'"
    command_s_fvr_B     = command_fvr + s_fvr_B + " --outName fix-vs-run.B" + \
      " --histTitle 'fixed vs running coupling: Model B (#pi_{dm} = 2 GeV); #chi_{dm} = 1000 GeV; c#tau = 5 mm'"
    command_s_fvr_A_S1  = command_s_fvr_A + command_S1
    command_s_fvr_B_S1  = command_s_fvr_B + command_S1
    command_s_fvr_A_All = command_s_fvr_A + command_All
    command_s_fvr_B_All = command_s_fvr_B + command_All

    #os.system( command_s_fvr_A_S1  )
    #os.system( command_s_fvr_B_S1  )
    #os.system( command_s_fvr_A_All )
    #os.system( command_s_fvr_B_All )


    # truth grid --> play around with lifetime colors, samples to plot against each other (plot by model, by xdm, by lifetime, etc.)
    # --> fix input/output paths above; add argument to override sampleDict colors
    #command_grid        = command + " --draw1D --outSubdir grid --histList 'Xd_M,Xd_phi,d0'"
    command_grid        = command + " --draw1D --outSubdir grid --histList ':kshort=vrsh'"
    
    s_150               = " --sgnlType modA_1400_150_,modA_1000_150_,modA_600_150_,modB_1400_150_,modB_1000_150_,modB_600_150_," + \
      "modC_1400_150_,modC_1000_150_,modC_600_150_,modD_1400_150_,modD_1000_150_,modD_600_150_,modE_1400_150_,modE_1000_150_,modE_600_150_"
    command_s_150       = command_grid + s_150 + " --outName grid.150 --histTitle 'ctau = 150 mm' --lstyleEnum 3 --legLenEnum 4" + \
      " --lxint 0.007 --lyint 0.025"
    command_s_150_S1    = command_s_150 + command_S1

    s_mod_150_style     = " --lstyleEnum 3 --legLenEnum 7"
    s_1400_150          = " --sgnlType modA_1400_150_,modB_1400_150_,modC_1400_150_,modD_1400_150_,modE_1400_150_"
    s_1000_150          = " --sgnlType modA_1000_150_,modB_1000_150_,modC_1000_150_,modD_1000_150_,modE_1000_150_"
    s_600_150           = " --sgnlType modA_600_150_,modB_600_150_,modC_600_150_,modD_600_150_,modE_600_150_"
    command_s_1400_150    = command_grid + s_1400_150 + s_mod_150_style + " --outName grid.1400.150" + \
      " --histTitle '#chi_{dm} = 1400 GeV, c#tau = 150 mm'"
    command_s_1000_150    = command_grid + s_1000_150 + s_mod_150_style + " --outName grid.1000.150" + \
      " --histTitle '#chi_{dm} = 1000 GeV, c#tau = 150 mm'"
    command_s_600_150     = command_grid + s_600_150  + s_mod_150_style  + " --outName grid.600.150"  + \
      " --histTitle '#chi_{dm} = 600 GeV, c#tau = 150 mm'"
    command_s_1400_150_S1 = command_s_1400_150 + command_S1
    command_s_1000_150_S1 = command_s_1000_150 + command_S1
    command_s_600_150_S1  = command_s_600_150  + command_S1

    s_mod_style         = " --lstyleEnum 2 --legLenEnum 10 --lxint 0.0125 --lyint 0.05"
    s_A_1400            = " --sgnlType modA_1400_300_,modA_1400_150_,modA_1400_75_,modA_1400_20_,modA_1400_5_,modA_1400_2_"
    s_A_1000            = " --sgnlType modA_1000_300_,modA_1000_150_,modA_1000_75_,modA_1000_5_,modA_1000_2_,modA_1000_1_"
    s_A_600             = " --sgnlType modA_600_300_,modA_600_150_,modA_600_20_,modA_600_2_,modA_600_1_,modA_600_0p5_"
    command_A_1400      = command_grid + s_A_1400 + s_mod_style + " --outName grid.A.1400" + \
      " --histTitle 'Model A (#pi_{dm} = 5 GeV), #chi_{dm} = 1400 GeV'"
    command_A_1000      = command_grid + s_A_1000 + s_mod_style + " --outName grid.A.1000" + \
      " --histTitle 'Model A (#pi_{dm} = 5 GeV), #chi_{dm} = 1000 GeV'"
    command_A_600       = command_grid + s_A_600  + s_mod_style + " --outName grid.A.600"  + \
      " --histTitle 'Model A (#pi_{dm} = 5 GeV), #chi_{dm} = 600 GeV'"
    command_A_1400_S1   = command_A_1400 + command_S1
    command_A_1000_S1   = command_A_1000 + command_S1
    command_A_600_S1    = command_A_600  + command_S1

    s_B_1400            = " --sgnlType modB_1400_300_,modB_1400_150_,modB_1400_75_,modB_1400_20_,modB_1400_5_,modB_1400_2_"
    s_B_1000            = " --sgnlType modB_1000_300_,modB_1000_150_,modB_1000_75_,modB_1000_5_,modB_1000_2_,modB_1000_1_"
    s_B_600             = " --sgnlType modB_600_300_,modB_600_150_,modB_600_20_,modB_600_2_,modB_600_1_,modB_600_0p5_"
    command_B_1400      = command_grid + s_B_1400 + s_mod_style + " --outName grid.B.1400" + \
      " --histTitle 'Model B (#pi_{dm} = 2 GeV), #chi_{dm} = 1400 GeV'"
    command_B_1000      = command_grid + s_B_1000 + s_mod_style + " --outName grid.B.1000" + \
      " --histTitle 'Model B (#pi_{dm} = 2 GeV), #chi_{dm} = 1000 GeV'"
    command_B_600       = command_grid + s_B_600  + s_mod_style + " --outName grid.B.600"  + \
      " --histTitle 'Model B (#pi_{dm} = 2 GeV), #chi_{dm} = 600 GeV'"
    command_B_1400_S1   = command_B_1400 + command_S1
    command_B_1000_S1   = command_B_1000 + command_S1
    command_B_600_S1    = command_B_600  + command_S1

    s_C_1400            = " --sgnlType modC_1400_300_,modC_1400_150_,modC_1400_75_,modC_1400_20_,modC_1400_5_,modC_1400_2_"
    s_C_1000            = " --sgnlType modC_1000_300_,modC_1000_150_,modC_1000_75_,modC_1000_5_,modC_1000_2_,modC_1000_1_"
    s_C_600             = " --sgnlType modC_600_300_,modC_600_150_,modC_600_20_,modC_600_2_,modC_600_1_,modC_600_0p5_"
    command_C_1400      = command_grid + s_C_1400 + s_mod_style + " --outName grid.C.1400" + \
      " --histTitle 'Model C (#pi_{dm} = 10 GeV), #chi_{dm} = 1400 GeV'"
    command_C_1000      = command_grid + s_C_1000 + s_mod_style + " --outName grid.C.1000" + \
      " --histTitle 'Model C (#pi_{dm} = 10 GeV), #chi_{dm} = 1000 GeV'"
    command_C_600       = command_grid + s_C_600  + s_mod_style + " --outName grid.C.600"  + \
      " --histTitle 'Model C (#pi_{dm} = 10 GeV), #chi_{dm} = 600 GeV'"
    command_C_1400_S1   = command_C_1400 + command_S1
    command_C_1000_S1   = command_C_1000 + command_S1
    command_C_600_S1    = command_C_600  + command_S1

    s_D_1400            = " --sgnlType modD_1400_300_,modD_1400_150_,modD_1400_75_,modD_1400_20_,modD_1400_5_,modD_1400_2_"
    s_D_1000            = " --sgnlType modD_1000_300_,modD_1000_150_,modD_1000_75_,modD_1000_5_,modD_1000_2_,modD_1000_1_"
    s_D_600             = " --sgnlType modD_600_300_,modD_600_150_,modD_600_20_,modD_600_2_,modD_600_1_,modD_600_0p5_"
    command_D_1400      = command_grid + s_D_1400 + s_mod_style + " --outName grid.D.1400" + \
      " --histTitle 'Model D (#pi_{dm} = 20 GeV), #chi_{dm} = 1400 GeV'"
    command_D_1000      = command_grid + s_D_1000 + s_mod_style + " --outName grid.D.1000" + \
      " --histTitle 'Model D (#pi_{dm} = 20 GeV), #chi_{dm} = 1000 GeV'"
    command_D_600       = command_grid + s_D_600  + s_mod_style + " --outName grid.D.600"  + \
      " --histTitle 'Model D (#pi_{dm} = 20 GeV), #chi_{dm} = 600 GeV'"
    command_D_1400_S1   = command_D_1400 + command_S1
    command_D_1000_S1   = command_D_1000 + command_S1
    command_D_600_S1    = command_D_600  + command_S1

    s_E_1400            = " --sgnlType modE_1400_300_,modE_1400_150_,modE_1400_75_,modE_1400_20_,modE_1400_5_,modE_1400_2_"
    s_E_1000            = " --sgnlType modE_1000_300_,modE_1000_150_,modE_1000_75_,modE_1000_5_,modE_1000_2_,modE_1000_1_"
    s_E_600             = " --sgnlType modE_600_300_,modE_600_150_,modE_600_20_,modE_600_2_,modE_600_1_,modE_600_0p5_"
    command_E_1400      = command_grid + s_E_1400 + s_mod_style + " --outName grid.E.1400" + \
      " --histTitle 'Model E (#pi_{dm} = 0.8 GeV), #chi_{dm} = 1400 GeV'"
    command_E_1000      = command_grid + s_E_1000 + s_mod_style + " --outName grid.E.1000" + \
      " --histTitle 'Model E (#pi_{dm} = 0.8 GeV), #chi_{dm} = 1000 GeV'"
    command_E_600       = command_grid + s_E_600  + s_mod_style + " --outName grid.E.600"  + \
      " --histTitle 'Model E (#pi_{dm} = 0.8 GeV), #chi_{dm} = 600 GeV'"
    command_E_1400_S1   = command_E_1400 + command_S1
    command_E_1000_S1   = command_E_1000 + command_S1
    command_E_600_S1    = command_E_600  + command_S1

    s_mod_mix_style     = " --lstyleEnum 4 --legLenEnum 9 --lyint 0.035"
    s_A_mix             = " --sgnlType modA_1400_300_,modA_1400_75_,modA_1400_2_,modA_1000_150_,modA_1000_5_,modA_1000_1_," + \
      "modA_600_150_,modA_600_20_,modA_600_0p5_"   
    s_B_mix             = " --sgnlType modB_1400_150_,modB_1400_75_,modB_1400_2_,modB_1000_150_,modB_1000_5_,modB_1000_1_," + \
      "modB_600_300_,modB_600_20_,modB_600_1_"
    s_C_mix             = " --sgnlType modC_1400_300_,modC_1400_20_,modC_1400_5_,modC_1000_300_,modC_1000_75_,modC_1000_2_," + \
      "modC_600_150_,modC_600_2_,modC_600_1_"
    s_D_mix             = " --sgnlType modD_1400_150_,modD_1400_20_,modD_1400_5_,modD_1000_300_,modD_1000_75_,modD_1000_1_," + \
      "modD_600_150_,modD_600_2_,modD_600_0p5_"
    s_E_mix             = " --sgnlType modE_1400_150_,modE_1400_20_,modE_1400_2_,modE_1000_75_,modE_1000_5_,modE_1000_2_," + \
      "modE_600_300_,modE_600_20_,modE_600_1_"
    command_A_mix       = command_grid + s_A_mix + s_mod_mix_style + " --outName grid.A.mix" + \
      " --histTitle 'Model A (#pi_{dm} = 5 GeV)'"
    command_B_mix       = command_grid + s_B_mix + s_mod_mix_style + " --outName grid.B.mix" + \
      " --histTitle 'Model B (#pi_{dm} = 2 GeV)'"
    command_C_mix       = command_grid + s_C_mix + s_mod_mix_style + " --outName grid.C.mix" + \
      " --histTitle 'Model C (#pi_{dm} = 10 GeV)'"
    command_D_mix       = command_grid + s_D_mix + s_mod_mix_style + " --outName grid.D.mix" + \
      " --histTitle 'Model D (#pi_{dm} = 20 GeV)'"
    command_E_mix       = command_grid + s_E_mix + s_mod_mix_style + " --outName grid.E.mix" + \
      " --histTitle 'Model E (#pi_{dm} = 0.8 GeV)'"
    command_A_mix_S1    = command_A_mix + command_S1
    command_B_mix_S1    = command_B_mix + command_S1
    command_C_mix_S1    = command_C_mix + command_S1
    command_D_mix_S1    = command_D_mix + command_S1
    command_E_mix_S1    = command_E_mix + command_S1

    s_xdm_mix_style     = " --lstyleEnum 3 --legLenEnum 6 --lxint 0.0125 --lyint 0.04"
    s_1400_mix          = " --sgnlType modA_1400_20_,modB_1400_300_,modC_1400_2_,modD_1400_75_,modE_1400_5_"
    s_1000_mix          = " --sgnlType modA_1000_150_,modB_1000_5_,modC_1000_75_,modD_1000_2_,modE_1000_300_"
    s_600_mix           = " --sgnlType modA_600_2_,modB_600_1_,modC_600_0p5_,modD_600_150_,modE_600_20_"
    command_1400_mix    = command_grid + s_1400_mix + s_xdm_mix_style + " --outName grid.1400.mix" + \
      " --histTitle '#chi_{dm} = 1400 GeV'"
    command_1000_mix    = command_grid + s_1000_mix + s_xdm_mix_style + " --outName grid.1000.mix" + \
      " --histTitle '#chi_{dm} = 1000 GeV'"
    command_600_mix     = command_grid + s_600_mix  + s_xdm_mix_style + " --outName grid.600.mix" + \
      " --histTitle '#chi_{dm} = 600 GeV'"
    command_1400_mix_S1 = command_1400_mix + command_S1
    command_1000_mix_S1 = command_1000_mix + command_S1
    command_600_mix_S1  = command_600_mix  + command_S1
    

    os.system( command_s_150_S1 )
    os.system( command_s_1400_150_S1 )
    os.system( command_s_1000_150_S1 )
    os.system( command_s_600_150_S1  )
    #os.system( command_A_1400_S1     )
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
    #os.system( command_A_mix_S1      )
    #os.system( command_B_mix_S1      )
    #os.system( command_C_mix_S1      )
    #os.system( command_D_mix_S1      )
    #os.system( command_E_mix_S1      )
    #os.system( command_1400_mix_S1   )
    #os.system( command_1000_mix_S1   )
    #os.system( command_600_mix_S1    )
    


if __name__ == "__main__":
    main()

    
