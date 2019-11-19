#!/bin/bash
# script for running local tree-to-histogram jobs on local ntuples


##### MAKE SURE RUNNING ORIGINAL XAH_RUN SCANDIR IMPLEMENTATION #####


# run over ALL LATEST trees
input="$EJ_PATH/../output/localOutput/latest/tree/"
output="$EJ_PATH/../output/localOutput/latest/"
#runEJsHistogrammer.py --inDir ${input} --outDir ${output} --renameAndMove --mergeDatasets


# run over ALL LATEST MC or DATA trees
intags_mc="mc16"
intags_data="data"
#runEJsHistogrammer.py --inDir ${input} --outDir ${output} --inTags ${intags_mc}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input} --outDir ${output} --inTags ${intags_data} --renameAndMove --mergeDatasets

# run over SUB-SET of trees
intags_a="mc16,ModelA"
intags_bkgd="jetjet"
intags_17="data17"
#runEJsHistogrammer.py --inDir ${input} --outDir ${output} --inTags ${intags_a}    --mergeDatasets --renameAndMove
#runEJsHistogrammer.py --inDir ${input} --outDir ${output} --inTags ${intags_bkgd} --mergeDatasets --renameAndMove
#runEJsHistogrammer.py --inDir ${input} --outDir ${output} --inTags ${intags_17}   --mergeDatasets --renameAndMove

# run over benchmark mc / single data run trees for TESTING
output_bench="local.hists.benchmark.test"
intags_bench_a="ModelA_1000_150"
intags_bench_b="ModelB_1000_5"
intags_17_331804="data17,00331804"
intags_bkgd="jetjet"
runEJsHistogrammer.py --inDir ${input} --outDir ${output_bench} --inTags ${intags_bench_a}   --renameAndMove
#runEJsHistogrammer.py --inDir ${input} --outDir ${output_bench} --inTags ${intags_bench_b}   --renameAndMove
#runEJsHistogrammer.py --inDir ${input} --outDir ${output_bench} --inTags ${intags_17_331804} --renameAndMove
#runEJsHistogrammer.py --inDir ${input} --outDir ${output_bench} --inTags ${intags_bkgd}      --renameAndMove

# run over latest TRIGGER mc trees
jo_trig="$EJ_PATH/EJsAnalysis/config/EJsHistoConfig_trig.py"
input_trig="$EJ_PATH/../output/localOutput/latest-trigger/tree/"
output_trig="$EJ_PATH/../output/localOutput/latest-trigger/"
intags_trig="mc16"
#runEJsHistogrammer.py --inDir ${input_trig} --outDir ${output_trig} --outTag "trig" --jo ${jo_trig}  --mergeDatasets --renameAndMove

