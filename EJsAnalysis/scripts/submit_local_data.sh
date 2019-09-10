#!/bin/bash
# script for submitting local jobs (data)


##### OMIT ASTERISKS IN INPUT FILE PATHS WHEN RUNNING W/ HACKED XAH_RUN (TO RUN OVER MULTIPLE FILES PER SAMPLE) #####


## single sample test
input_18="$HOME/emerging_jets/datasets/data/data18/DAOD/official/exot23/data18_13TeV.00363830.physics_Main.deriv.DAOD_EXOT23.f1002_m1831_r10799_p3651_p3664/"
subdir_18="local.data18.00363830"
log_18="log.data18.00363830.out"

input_17="$HOME/emerging_jets/datasets/data/data17/DAOD/official/exot23/data17_13TeV.00331804.physics_Main.deriv.DAOD_EXOT23.r10203_r10658_p3578_p3664/"
subdir_17="local.data17.00331804"
log_17="log.data17.00331804.out"

input_16="$HOME/emerging_jets/datasets/data/data16/DAOD/official/exot23/data16_13TeV.00303208.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/"
subdir_16="local.data16.00303208"
log_16="log.data16.00303208.out"

input_15="$HOME/emerging_jets/datasets/data/data15/DAOD/official/exot23/data15_13TeV.00280862.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/"
subdir_15="local.data15.00280862"
log_15="log.data15.00280862.out"


## comparing all test runs from data18
input_list_18="$HOME/emerging_jets/datasets/data/data18/DAOD/official/exot23/data18_13TeV.00357451.physics_Main.deriv.DAOD_EXOT23.f958_m1831_r10799_p3651_p3664/ $HOME/emerging_jets/datasets/data/data18/DAOD/official/exot23/data18_13TeV.00363830.physics_Main.deriv.DAOD_EXOT23.f1002_m1831_r10799_p3651_p3664/ $HOME/emerging_jets/datasets/data/data18/DAOD/official/exot23/data18_13TeV.00350144.physics_Main.deriv.DAOD_EXOT23.f933_m1831_r10799_p3651_p3664/"
subdir_list_18="local.data18"
log_list_18="log.data18.out"

input_list_17="$HOME/emerging_jets/datasets/data/data17/DAOD/official/exot23/data17_13TeV.00335022.physics_Main.deriv.DAOD_EXOT23.r10258_r10658_p3578_p3664/ $HOME/emerging_jets/datasets/data/data17/DAOD/official/exot23/data17_13TeV.00331804.physics_Main.deriv.DAOD_EXOT23.r10203_r10658_p3578_p3664/ $HOME/emerging_jets/datasets/data/data17/DAOD/official/exot23/data17_13TeV.00340030.physics_Main.deriv.DAOD_EXOT23.r10426_r10658_p3578_p3664/"
subdir_list_17="local.data17"
log_list_17="log.data17.out"

input_list_16="$HOME/emerging_jets/datasets/data/data16/DAOD/official/exot23/data16_13TeV.00301973.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/ $HOME/emerging_jets/datasets/data/data16/DAOD/official/exot23/data16_13TeV.00303208.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/ $HOME/emerging_jets/datasets/data/data16/DAOD/official/exot23/data16_13TeV.00309440.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/"
subdir_list_16="local.data16"
log_list_16="log.data16.out"

input_list_15="$HOME/emerging_jets/datasets/data/data15/DAOD/official/exot23/data15_13TeV.00283608.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/ $HOME/emerging_jets/datasets/data/data15/DAOD/official/exot23/data15_13TeV.00280862.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/ $HOME/emerging_jets/datasets/data/data15/DAOD/official/exot23/data15_13TeV.00281411.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/"
subdir_list_15="local.data15"
log_list_15="log.data15.out"


## config files
jo_18="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16e.py"
jo_17="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16d.py"
jo_16="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16a.py"
jo_15="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16a.py"

jo_test="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"


## job steering
#xAH_run.py --files ${input_18} --config ${jo_18} --submitDir ${subdir_18} --nevents 100 direct | tee ${log_18}
#xAH_run.py --files ${input_17} --config ${jo_17} --submitDir ${subdir_17} --nevents 100 direct | tee ${log_17}
#xAH_run.py --files ${input_16} --config ${jo_16} --submitDir ${subdir_16} --nevents 100 direct | tee ${log_16}
#xAH_run.py --files ${input_15} --config ${jo_15} --submitDir ${subdir_15} --nevents 100 direct | tee ${log_15}

#xAH_run.py --files ${input_list_18} --config ${jo_18} --submitDir ${subdir_list_18} --nevents -1 direct | tee ${log_list_18}
#xAH_run.py --files ${input_list_17} --config ${jo_17} --submitDir ${subdir_list_17} --nevents -1 direct | tee ${log_list_17}
xAH_run.py --files ${input_list_16} --config ${jo_16} --submitDir ${subdir_list_16} --nevents -1 direct | tee ${log_list_16}
xAH_run.py --files ${input_list_15} --config ${jo_15} --submitDir ${subdir_list_15} --nevents -1 direct | tee ${log_list_15}


## job steering with valgrind -- memory checks --> DOES NOT SEEM TO WORK ON CERNVM -- TEST ON LXPLUS
#valgrind --leak-check=yes --trace-children=yes --num-callers=25 --show-reachable=yes --track-origins=yes --smc-check=all `which python` `xAH_run.py --files ${input_17} --config ${jo_17} --submitDir ${subdir_17} --nevents 100 direct` | tee valgrind.log.data17.out
