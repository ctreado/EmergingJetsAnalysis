#!/bin/bash
# script for submitting grid jobs (data)


input="$EJ_PATH/EJsAnalysis/scripts/samples.data17.txt"

jo="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"

subdir="grid.data17.firsttest.v0"

TAG="firsttest.v0"


xAH_run.py --files ${input} --config ${jo} \
	   --inputList --inputRucio \
	   --submitDir ${subdir} \
	   prun --optGridMergeOutput=1 --optGridNFilesPerJob=1.0 --optGridNJobs=1 \
	   --optGridOutputSampleName="user.%nickname%.%in:name[1]%.%in:name[2]%.%in:name[6]%.EJsAna.$TAG"
