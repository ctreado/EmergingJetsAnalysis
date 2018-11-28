#!/bin/bash
# script for submitting grid jobs (mc)


input="$EJ_PATH/EJsAnalysis/scripts/samples.mc.ejs.txt"

jo="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"

subdir="grid.MC16.EJs.firsttest.v0"

TAG="firsttest.v0"


xAH_run.py --files ${input} --config ${jo} \
	   --inputList --inputRucio \
	   --submitDir ${subdir} --isMC \
	   prun --optGridMergeOutput=1 --optGridNFilesPerJob=1.0 --optGridNJobs=1 \
	   --optGridOutputSampleName="user.%nickname%.%in:name[1]%.%in:name[2]%.%in:name[6]%.EJsAna.$TAG"
