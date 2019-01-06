#!/bin/bash
# script for submitting local test jobs w/ grid datasets (data)

input="$EJ_PATH/EJsAnalysis/scripts/samples.data17.txt"

jo="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"

subdir="test.data17"

xAH_run.py --files ${input} --config ${jo} \
	   --inputList --inputRucio \
	   --submitDir ${subdir} --nevents 10 direct
