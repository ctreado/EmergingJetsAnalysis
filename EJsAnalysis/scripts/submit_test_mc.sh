#!/bin/bash
# script for submitting local test jobs w/ grid datasets (MC)

input="$EJ_PATH/EJsAnalysis/scripts/samples.mc.ejs.txt"

jo="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"

subdir="test.MC16.EJs"

xAH_run.py --files ${input} --config ${jo} \
	   --inputList --inputRucio \
	   --submitDir ${subdir} --nevents 10 direct
