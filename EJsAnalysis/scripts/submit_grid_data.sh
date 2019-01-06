#!/bin/bash
# script for submitting grid jobs (data)


input="$EJ_PATH/EJsAnalysis/scripts/samples.data17.txt"

jo="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"

subdir="grid.data17.test060119.v0"

TAG="test060119.v0"


# --optGridNFiles sets number of input files to run over (set to 1.0 for testing)
xAH_run.py --files ${input} --config ${jo} \
	   --inputList --inputRucio \
	   --submitDir ${subdir} \
	   prun --optGridMergeOutput=1 --optGridNFiles=1.0 \
	   --optGridOutputSampleName="user.%nickname%.%in:name[1]%.%in:name[2]%.%in:name[6]%.EJsAna.$TAG"
