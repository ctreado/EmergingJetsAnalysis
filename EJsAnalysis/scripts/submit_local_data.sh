#!/bin/bash
# script for submitting local jobs (data)


##### OMIT ASTERISKS IN INPUT FILE PATHS WHEN RUNNING W/ HACKED XAH_RUN (TO RUN OVER MULTIPLE FILES PER SAMPLE) #####


## single sample test
input_18_1="$HOME/emerging_jets/datasets/data/data18/DAOD/official/exot23/data18_13TeV.00363830.physics_Main.deriv.DAOD_EXOT23.f1002_m1831_r10799_p3651_p3664/"
input_17_1="$HOME/emerging_jets/datasets/data/data17/DAOD/official/exot23/data17_13TeV.00331804.physics_Main.deriv.DAOD_EXOT23.r10203_r10658_p3578_p3664/"
input_16_1="$HOME/emerging_jets/datasets/data/data16/DAOD/official/exot23/data16_13TeV.00303208.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/"
input_15_1="$HOME/emerging_jets/datasets/data/data15/DAOD/official/exot23/data15_13TeV.00280862.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664/"


## multiple runs per year
input_18="$EJ_PATH/EJsAnalysis/scripts/sample_lists/local.samples.data18.txt"
input_17="$EJ_PATH/EJsAnalysis/scripts/sample_lists/local.samples.data17.txt"
input_16="$EJ_PATH/EJsAnalysis/scripts/sample_lists/local.samples.data16.txt"
input_15="$EJ_PATH/EJsAnalysis/scripts/sample_lists/local.samples.data15.txt"


## config files
jo_18="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16e.py"
jo_17="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16d.py"
jo_16="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16a.py"
jo_15="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16a.py"


## tags
tag="test"


## job steering
submitLocalEJsJobs.py --inFiles ${input_18_1} --jo ${jo_18} --nevents 1 --move --delete --outTag ${tag}
submitLocalEJsJobs.py --inFiles ${input_17_1} --jo ${jo_17} --nevents 1 --move --delete --outTag ${tag}
submitLocalEJsJobs.py --inFiles ${input_16_1} --jo ${jo_16} --nevents 1 --move --delete --outTag ${tag}
submitLocalEJsJobs.py --inFiles ${input_15_1} --jo ${jo_15} --nevents 1 --move --delete --outTag ${tag}

#submitLocalEJsJobs.py --inFiles ${input_18}   --jo ${jo_18}   --nevents 100 --move --delete
#submitLocalEJsJobs.py --inFiles ${input_17}   --jo ${jo_17}   --nevents 100 --move --delete
#submitLocalEJsJobs.py --inFiles ${input_16}   --jo ${jo_16}   --nevents 100 --move --delete
#submitLocalEJsJobs.py --inFiles ${input_15}   --jo ${jo_15}   --nevents 100 --move --delete


## trigger study
jo_17_trig="$EJ_PATH/EJsAnalysis/config/EJsConfig_trig_data_mc16d.py"
tag_trig="latest-trigger"
#submitLocalEJsJobs.py --inFiles ${input_17} --jo ${jo_17_trig} --nevents -1 --move --delete --outTag ${tag_trig}
