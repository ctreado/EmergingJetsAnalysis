#!/bin/bash
# script for submitting local jobs (data)


##### OMIT ASTERISKS IN INPUT FILE PATHS WHEN RUNNING W/ HACKED XAH_RUN (TO RUN OVER MULTIPLE FILES PER SAMPLE) #####


## single sample test
input_18_1="$HOME/emerging_jets/datasets/data/data18/DAOD/official/exot23/data18_13TeV.00363830.physics_Main.deriv.DAOD_EXOT23.f1002_m1831_r10799_p3651_p3664/"
subdir_18_1="local.data18.00363830"
log_18_1="log.data18.00363830.out"

input_17_1="$HOME/emerging_jets/datasets/data/data17/DAOD/official/exot23/data17_13TeV.00331804.physics_Main.deriv.DAOD_EXOT23.r10203_r10658_p3578_p3664/"
subdir_17_1="local.data17.00331804"
log_17_1="log.data17.00331804.out"

input_16_1="$HOME/emerging_jets/datasets/data/data16/DAOD/official/exot23/data16_13TeV.00303208.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/"
subdir_16_1="local.data16.00303208"
log_16_1="log.data16.00303208.out"

input_15_1="$HOME/emerging_jets/datasets/data/data15/DAOD/official/exot23/data15_13TeV.00280862.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/"
subdir_15_1="local.data15.00280862"
log_15_1="log.data15.00280862.out"


## multiple runs per year
input_18="$EJ_PATH/EJsAnalysis/scripts/sample_lists/local.samples.data18.txt"
subdir_18="local.data18"
log_18="log.data18.out"

input_17="$EJ_PATH/EJsAnalysis/scripts/sample_lists/local.samples.data17.txt"
subdir_17="local.data17"
log_17="log.data17.out"

input_16="$EJ_PATH/EJsAnalysis/scripts/sample_lists/local.samples.data16.txt"
subdir_16="local.data16"
log_16="log.data16.out"

input_15="$EJ_PATH/EJsAnalysis/scripts/sample_lists/local.samples.data15.txt"
subdir_15="local.data15"
log_15="log.data15.out"


## config files
jo_18="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16e.py"
jo_17="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16d.py"
jo_16="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16a.py"
jo_15="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16a.py"


## job steering
#submitLocalEJsJobs.py --inFiles ${input_18_1} --jo ${jo_18} --subDir ${subdir_18_1} --nevents 1 --log ${log_18_1} \
#		      --doMove --delete
#submitLocalEJsJobs.py --inFiles ${input_17_1} --jo ${jo_17} --subDir ${subdir_17_1} --nevents 1 --log ${log_17_1} \
#		      --doMove --delete
#submitLocalEJsJobs.py --inFiles ${input_16_1} --jo ${jo_16} --subDir ${subdir_16_1} --nevents 1 --log ${log_16_1} \
#		      --doMove --delete
#submitLocalEJsJobs.py --inFiles ${input_15_1} --jo ${jo_15} --subDir ${subdir_15_1} --nevents 1 --log ${log_15_1} \
#		      --doMove --delete

submitLocalEJsJobs.py --inFiles ${input_18}   --jo ${jo_18} --subDir ${subdir_18}   --nevents 100 --log ${log_18} \
		      --doMove --delete
submitLocalEJsJobs.py --inFiles ${input_17}   --jo ${jo_17} --subDir ${subdir_17}   --nevents 100 --log ${log_17} \
		      --doMove --delete
submitLocalEJsJobs.py --inFiles ${input_16}   --jo ${jo_16} --subDir ${subdir_16}   --nevents 100 --log ${log_16} \
		      --doMove --delete
submitLocalEJsJobs.py --inFiles ${input_15}   --jo ${jo_15} --subDir ${subdir_15}   --nevents 100 --log ${log_15} \
		      --doMove --delete


## trigger study
subdir_17_trig="local.data17.trigger"
log_17_trig="log.data17.trigger.out"
jo_17_trig="$EJ_PATH/EJsAnalysis/config/EJsConfig_trig_data_mc16d.py"
tag_trig="latest-trigger"
#submitLocalEJsJobs.py --inFiles ${input_17} --jo ${jo_17_trig} --subDir ${subdir_17_trig} --nevents -1 --log ${log_17_trig} \
#		      --outTag ${tag_trig} --doMove --delete
