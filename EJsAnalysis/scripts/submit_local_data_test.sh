#!/bin/bash
# script for submitting local jobs (data)

##### OMIT ASTERISKS IN INPUT FILE PATHS WHEN RUNNING W/ HACKED XAH_RUN (TO RUN OVER MULTIPLE FILES PER SAMPLE) #####

## single sample test
input="$HOME/emerging_jets/datasets/data/data17/DAOD/official/exot23/data17_13TeV.00328333.physics_Main.deriv.DAOD_EXOT23.r10203_r10658_p3578_p3664/*"
subdir="local.data17.00328333"

## comparing test runs from different data years
input_list="$HOME/emerging_jets/datasets/data/data17/DAOD/official/exot23/data17_13TeV.00328333.physics_Main.deriv.DAOD_EXOT23.r10203_r10658_p3578_p3664/* $HOME/emerging_jets/datasets/data/data16/DAOD/official/exot23/data16_13TeV.00302872.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/* $HOME/emerging_jets/datasets/data/data15/DAOD/official/exot23/data15_13TeV.00284285.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/*"
subdir_list="local.data"


jo="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"


#xAH_run.py --files ${input} --config ${jo} --submitDir ${subdir} --nevents -1 direct
xAH_run.py --files ${input_list} --config ${jo} --submitDir ${subdir_list} --nevents -1 direct
