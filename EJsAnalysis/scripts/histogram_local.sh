#!/bin/bash
# script for running local tree-to-histogram jobs on grid- or locally-produced ntuples


# locally produced ntuples
input_local="$EJ_PATH/../output/localOutput/latest/tree/"
output_local="$EJ_PATH/../output/localOutput/latest/"
# grid produced ntuples
input_grid="$EJ_PATH/../output/gridOutput/v0_2020-01_n1/tree/"
output_grid="$EJ_PATH/../output/gridOutput/v0_2020-01_n1/"
# grid produced ntuples -- update
input_grid_up="$EJ_PATH/../output/gridOutput/v0_2020-06_mod/tree/"
output_grid_up="$EJ_PATH/../output/gridOutput/v0_2020-06_mod/"

intags_mc="mc16"
intags_b="mc16,ModelB"
intags_08="mc16,312008"
intags_28="mc16,312028"
intags_39="mc16,312039"
intags_46="mc16,312046"
intags_60="mc16,312060"
intags_66="mc16,312066"
intags_75="mc16,312075"
intags_80="mc16,312080"
intags_bkgd="bkgd"
intags_17="data17,331804"
intags_data="data"

# run over ALL LATEST trees
#runEJsHistogrammer.py --inDir ${input_local} --outDir ${output_local} --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid}  --outDir ${output_grid}  --renameAndMove --mergeDatasets

# run over ALL LATEST LOCAL MC or DATA trees
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_08}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_39}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_46}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_60}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_66}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_75}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_80}   --renameAndMove --mergeDatasets
runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_mc}   --renameAndMove --mergeDatasets
runEJsHistogrammer.py --inDir ${input_grid}    --outDir ${output_grid_up} --inTags ${intags_mc}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid}    --outDir ${output_grid_up} --inTags ${intags_data} --renameAndMove --mergeDatasets

# run over SUB-SET of trees
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_08}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_28}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_46}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_66}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_80}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid}    --outDir ${output_grid}    --inTags ${intags_bkgd} --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_local} --outDir ${output_local} --inTags ${intags_b}    --mergeDatasets --renameAndMove
#runEJsHistogrammer.py --inDir ${input_local} --outDir ${output_local} --inTags ${intags_bkgd} --mergeDatasets --renameAndMove
#runEJsHistogrammer.py --inDir ${input_local} --outDir ${output_local} --inTags ${intags_17}   --mergeDatasets --renameAndMove

####################### LOCAL TESTS #######################
# run over benchmark mc / single data year trees
#input_bench="$EJ_PATH/../output/localOutput/tmp_search-minus-one/tree/"
input_bench="$EJ_PATH/../output/localOutput/tmp_rel-update/tree/"
#output_bench="$EJ_PATH/../output/localOutput/tmp_search-minus-one/"
output_test="$EJ_PATH/../run/test.histos/"
#runEJsHistogrammer.py --inDir ${input_bench}   --outDir ${output_test} --inTags ${intags_mc}   --mergeDatasets --renameAndMove --nevents -1
#runEJsHistogrammer.py --inDir ${input_bench}   --outDir ${output_test} --inTags ${intags_b}    --mergeDatasets --renameAndMove --nevents -1
#runEJsHistogrammer.py --inDir ${input_bench}   --outDir ${output_test} --inTags ${intags_bkgd} --mergeDatasets --renameAndMove --nevents -1
#runEJsHistogrammer.py --inDir ${input_bench}   --outDir ${output_test} --inTags ${intags_17}   --mergeDatasets --renameAndMove --nevents -1

#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_test} --inTags ${intags_08}   --mergeDatasets --renameAndMove --nevents -1
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_test} --inTags ${intags_28}   --mergeDatasets --renameAndMove --nevents 1000
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_test} --inTags ${intags_39}   --mergeDatasets --renameAndMove --nevents 1000
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_test} --inTags ${intags_60}   --mergeDatasets --renameAndMove --nevents 1000
#runEJsHistogrammer.py --inDir ${input_grid}    --outDir ${output_test} --inTags ${intags_bkgd} --mergeDatasets --renameAndMove --nevents -1

# run over latest TRIGGER mc trees
jo_trig="$EJ_PATH/EJsAnalysis/config/EJsHistoConfig_trig.py"
input_trig="$EJ_PATH/../output/localOutput/latest-trigger/tree/"
output_trig="$EJ_PATH/../output/localOutput/latest-trigger/"
intags_trig="mc16"
#runEJsHistogrammer.py --inDir ${input_trig} --outDir ${output_trig} --outTag "trig" --jo ${jo_trig}  --mergeDatasets --renameAndMove
###########################################################

