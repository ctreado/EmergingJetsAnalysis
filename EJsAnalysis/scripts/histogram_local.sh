#!/bin/bash
# script for running local tree-to-histogram jobs on local ntuples


##### MAKE SURE RUNNING ORIGINAL XAH_RUN SCANDIR IMPLEMENTATION #####


# run over all latest trees
input="$EJ_PATH/../output/localOutput/latest/tree/"
output="$EJ_PATH/../output/localOutput/latest/"
runEJsHistogrammer.py --inDir ${input} --outDir ${output} --mergeDatasets --renameAndMove

# run over sub-set of trees
intags_a="mc16,ModelA"
intags_17="data17"
intags_bkgd="jetjet"
#runEJsHistogrammer.py --inDir ${input} --outDir ${output} --inTags ${intags_a}    --mergeDatasets --renameAndMove
#runEJsHistogrammer.py --inDir ${input} --outDir ${output} --inTags ${intags_17}   --mergeDatasets --renameAndMove
#runEJsHistogrammer.py --inDir ${input} --outDir ${output} --inTags ${intags_bkgd} --mergeDatasets --renameAndMove

# run over latest trigger trees
input_trig="$EJ_PATH/../output/localOutput/latest-trigger/tree/"
output_trig="$EJ_PATH/../output/localOutput/latest-trigger/"
jo_trig="$EJ_PATH/EJsanalysis/config/EJsHistoConfig_trig.py"
#runEJsHistogrammer.py --inDir ${input_trig} --outTag "trig" --jo ${jo_trig} --outDir ${output_trig} --mergeDatasets --renameAndMove

