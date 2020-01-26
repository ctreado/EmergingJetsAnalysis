#!/bin/bash
# script for running local tree-to-histogram jobs on grid- or locally-produced ntuples


# locally produced ntuples
input_local="$EJ_PATH/../output/localOutput/latest/tree/"
output_local="$EJ_PATH/../output/localOutput/latest/"
# grid produced ntuples
input_grid="$EJ_PATH/../output/gridOutput/latest/tree/"
output_grid="$EJ_PATH/../output/gridOutput/latest/"

# run over ALL LATEST trees
#runEJsHistogrammer.py --inDir ${input_local} --outDir ${output_local} --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid} --outDir ${output_grid} --renameAndMove --mergeDatasets

# run over ALL LATEST MC or DATA trees
intags_mc="mc16"
intags_data="data"
#runEJsHistogrammer.py --inDir ${input_local} --outDir ${output_local} --inTags ${intags_mc}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_local} --outDir ${output_local} --inTags ${intags_data} --renameAndMove --mergeDatasets

# run over SUB-SET of trees
intags_a="mc16,ModelA"
intags_bkgd="jetjet"
#intags_17="data17"
#runEJsHistogrammer.py --inDir ${input_local} --outDir ${output_local} --inTags ${intags_a}    --mergeDatasets --renameAndMove
#runEJsHistogrammer.py --inDir ${input_local} --outDir ${output_local} --inTags ${intags_bkgd} --mergeDatasets --renameAndMove
#runEJsHistogrammer.py --inDir ${input_local} --outDir ${output_local} --inTags ${intags_17}   --mergeDatasets --renameAndMove

####################### LOCAL TESTS #######################
# run over benchmark mc / single data year trees
input_bench="$EJ_PATH/../output/localOutput/tmp_search-minus-one/tree/"
#output_bench="$EJ_PATH/../output/localOutput/tmp_search-minus-one/"
output_bench="$EJ_PATH/../run/tmp_hist_test/"
intags_mc="mc16,ModelA"
intags_17="data17,331804"
runEJsHistogrammer.py --inDir ${input_bench} --outDir ${output_bench} --inTags ${intags_mc}   --mergeDatasets --renameAndMove
#runEJsHistogrammer.py --inDir ${input_bench} --outDir ${output_bench} --inTags ${intags_17}   --mergeDatasets --renameAndMove

# run over latest TRIGGER mc trees
jo_trig="$EJ_PATH/EJsAnalysis/config/EJsHistoConfig_trig.py"
input_trig="$EJ_PATH/../output/localOutput/latest-trigger/tree/"
output_trig="$EJ_PATH/../output/localOutput/latest-trigger/"
intags_trig="mc16"
#runEJsHistogrammer.py --inDir ${input_trig} --outDir ${output_trig} --outTag "trig" --jo ${jo_trig}  --mergeDatasets --renameAndMove
###########################################################

