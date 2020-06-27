#!/bin/bash
# script for running local tree-to-histogram jobs on grid- or locally-produced ntuples


# locally produced ntuples
jo="$EJ_PATH/EJsAnalysis/config/EJsTruthHistoConfig.py"

# --> pythia 8.183 truth derivations: fixed vs running coupling
input_81="$EJ_PATH/../output/localOutput/truth_fix-vs-run/tree/"
output_81="$EJ_PATH/../output/localOutput/truth_fix-vs-run/"

#runEJsHistogrammer.py --inDir ${input_81} --outDir ${output_81} --jo ${jo} --renameAndMove --mergeDatasets --inTags ""


# --> pythia 8.230 truth derivations: full signal grid
input="$EJ_PATH/../output/localOutput/truth_grid/tree/"
output="$EJ_PATH/../output/localOutput/truth_grid/"

runEJsHistogrammer.py --inDir ${input} --outDir ${output} --jo ${jo} --renameAndMove --mergeDatasets --inTags "A"
runEJsHistogrammer.py --inDir ${input} --outDir ${output} --jo ${jo} --renameAndMove --mergeDatasets --inTags "B"
runEJsHistogrammer.py --inDir ${input} --outDir ${output} --jo ${jo} --renameAndMove --mergeDatasets --inTags "C"
runEJsHistogrammer.py --inDir ${input} --outDir ${output} --jo ${jo} --renameAndMove --mergeDatasets --inTags "D"
runEJsHistogrammer.py --inDir ${input} --outDir ${output} --jo ${jo} --renameAndMove --mergeDatasets --inTags "E"


