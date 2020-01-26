#!/bin/bash
# script for submitting grid jobs (data)


## input samples
input18="$EJ_PATH/EJsAnalysis/scripts/sample_lists/samples.data18.txt"
input17="$EJ_PATH/EJsAnalysis/scripts/sample_lists/samples.data17.txt"
input16="$EJ_PATH/EJsAnalysis/scripts/sample_lists/samples.data16.txt"
input15="$EJ_PATH/EJsAnalysis/scripts/sample_lists/samples.data15.txt"

## config files
jo18="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16e.py"
jo17="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16d.py"
jo16="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16a.py"
jo15="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16a.py"

## submission directories
subdir18="grid.data18"
subdir17="grid.data17"
subdir16="grid.data16"
subdir15="grid.data15"

## tags
vtag="v0"


## job steering
submitGridEJsJobs.py --inFiles ${input18} --jo ${jo18} --subDir ${subdir18} --vtag ${vtag} --nFiles -1
submitGridEJsJobs.py --inFiles ${input17} --jo ${jo17} --subDir ${subdir17} --vtag ${vtag} --nFiles -1
submitGridEJsJobs.py --inFiles ${input16} --jo ${jo16} --subDir ${subdir16} --vtag ${vtag} --nFiles -1
submitGridEJsJobs.py --inFiles ${input15} --jo ${jo15} --subDir ${subdir15} --vtag ${vtag} --nFiles -1


## TEST
input17_test="$EJ_PATH/EJsAnalysis/scripts/sample_lists/samples.data17.test.txt"
subdir17_test="grid.data17.test"
outName17_test="TEST"
#submitGridEJsJobs.py --inFiles ${input17_test} --jo ${jo17} --subDir ${subdir17_test} --nFiles 1.0 --outName ${outName17_test}
