#!/bin/bash
# script for submitting grid jobs (mc)


## input samples
input_a0="$EJ_PATH/EJsAnalysis/scripts/sample_lists/samples.mc16a.ejs_sub0.txt"
input_d0="$EJ_PATH/EJsAnalysis/scripts/sample_lists/samples.mc16d.ejs_sub0.test.txt"
input_e0="$EJ_PATH/EJsAnalysis/scripts/sample_lists/samples.mc16e.ejs_sub0.test.txt"
input_bkgd_a="$EJ_PATH/EJsAnalysis/scripts/sample_lists/samples.mc16a.bkgd.txt"
input_bkgd_d="$EJ_PATH/EJsAnalysis/scripts/sample_lists/samples.mc16d.bkgd.txt"

## config files
jo_a="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16a.py"
jo_d="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16d.py"
jo_e="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16e.py"

## submission directories
subdir_a0="grid.MC16a.EJs.sub0"
subdir_d0="grid.MC16d.EJs.sub0"
subdir_e0="grid.MC16e.EJs.sub0"
subdir_ab="grid.MC16a.bkgd"
subdir_db="grid.MC16d.bkgd"

## output sample names
out_sub0="sub0"
out_bkgd="bkgd"

## tags
vtag="v0"


## job steering
#submitGridEJsJobs.py --inFiles ${input_a0}     --jo ${jo_a} --subDir ${subdir_a0} --outName ${out_sub0} --vtag ${vtag} --nFiles -1 --isMC
submitGridEJsJobs.py --inFiles ${input_d0}     --jo ${jo_d} --subDir ${subdir_d0} --outName ${out_sub0} --vtag ${vtag} --nFiles -1 --isMC
submitGridEJsJobs.py --inFiles ${input_e0}     --jo ${jo_e} --subDir ${subdir_e0} --outName ${out_sub0} --vtag ${vtag} --nFiles -1 --isMC
#submitGridEJsJobs.py --inFiles ${input_bkgd_a} --jo ${jo_a} --subDir ${subdir_ab} --outName ${out_bkgd} --vtag ${vtag} --nFiles -1 --isMC
#submitGridEJsJobs.py --inFiles ${input_bkgd_d} --jo ${jo_d} --subDir ${subdir_db} --outName ${out_bkgd} --vtag ${vtag} --nFiles -1 --isMC


## TEST
input_d_test="$EJ_PATH/EJsAnalysis/scripts/sample_lists/samples.mc16d.ejs_sub0.test.txt"
subdir_d_test="grid.MC16d.EJs.sub0.test"
out_sub0_test="sub0.TEST"
#submitGridEJsJobs.py --inFiles ${input_d_test} --jo ${jo_d} --subDir ${subdir_d_test} --nFiles 1.0 --outName ${out_sub0_test} --isMC
