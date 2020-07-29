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
# grid produced ntuples -- lxplus
input_grid_lxp_o="/eos/atlas/user/c/ctreado/EmergingJets/analysis_ntuples/gridOutput/v0_2020-01_n2/tree/"
input_grid_lxp_c="/eos/atlas/user/c/ctreado/EmergingJets/analysis_ntuples/gridOutput/v0_2020-06_mod/tree/"
input_grid_lxp_k="/eos/user/k/kegraham/ejets/data/analysis_ntuples/gridOutput/v0_2020-06_mod/tree/"

intags_mc="mc16"
intags_b="mc16,ModelB"
intags_04="mc16,312004"
intags_08="mc16,312008"
intags_17="mc16,312017"
intags_22="mc16,312022"
intags_28="mc16,312028"
intags_31="mc16,312031"
intags_39="mc16,312039"
intags_46="mc16,312046"
intags_52="mc16,312052,v0_01"
intags_60="mc16,312060"
intags_66="mc16,312066,v0_02"
intags_67="mc16,312067,v0_03"
intags_75="mc16,312075"
intags_80="mc16,312080"
intags_90="mc16,31209"
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
#runEJsHistogrammer.py --inDir ${input_grid_up} --outDir ${output_grid_up} --inTags ${intags_mc}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid}    --outDir ${output_grid_up} --inTags ${intags_mc}   --renameAndMove --mergeDatasets
#runEJsHistogrammer.py --inDir ${input_grid}    --outDir ${output_grid_up} --inTags ${intags_data} --renameAndMove --mergeDatasets

# run over ALL LATEST LOCAL MC or DATA trees on lxplus
runEJsHistogrammer.py --inDir ${input_grid_lxp_c} --outDir ${output_grid_up} --inTags ${intags_04} --renameAndMove --mergeDatasets --nevents 10000 #9956
runEJsHistogrammer.py --inDir ${input_grid_lxp_c} --outDir ${output_grid_up} --inTags ${intags_08} --renameAndMove --mergeDatasets --nevents 10000 #9788
runEJsHistogrammer.py --inDir ${input_grid_lxp_c} --outDir ${output_grid_up} --inTags ${intags_17} --renameAndMove --mergeDatasets --nevents 12000 #11831
runEJsHistogrammer.py --inDir ${input_grid_lxp_c} --outDir ${output_grid_up} --inTags ${intags_22} --renameAndMove --mergeDatasets --nevents 10000 #9944
runEJsHistogrammer.py --inDir ${input_grid_lxp_c} --outDir ${output_grid_up} --inTags ${intags_28} --renameAndMove --mergeDatasets --nevents 12000 #11941
runEJsHistogrammer.py --inDir ${input_grid_lxp_c} --outDir ${output_grid_up} --inTags ${intags_31} --renameAndMove --mergeDatasets --nevents 30000 #28135
runEJsHistogrammer.py --inDir ${input_grid_lxp_c} --outDir ${output_grid_up} --inTags ${intags_39} --renameAndMove --mergeDatasets --nevents 16000 #15801
runEJsHistogrammer.py --inDir ${input_grid_lxp_c} --outDir ${output_grid_up} --inTags ${intags_46} --renameAndMove --mergeDatasets --nevents 42000 #41753
runEJsHistogrammer.py --inDir ${input_grid_lxp_c} --outDir ${output_grid_up} --inTags ${intags_60} --renameAndMove --mergeDatasets --nevents 32000 #31874
runEJsHistogrammer.py --inDir ${input_grid_lxp_k} --outDir ${output_grid_up} --inTags ${intags_52} --renameAndMove --mergeDatasets --nevents 42000 #41344
runEJsHistogrammer.py --inDir ${input_grid_lxp_k} --outDir ${output_grid_up} --inTags ${intags_66} --renameAndMove --mergeDatasets --nevents 90000 #89415
runEJsHistogrammer.py --inDir ${input_grid_lxp_k} --outDir ${output_grid_up} --inTags ${intags_67} --renameAndMove --mergeDatasets --nevents 18000 #17423
runEJsHistogrammer.py --inDir ${input_grid_lxp_k} --outDir ${output_grid_up} --inTags ${intags_75} --renameAndMove --mergeDatasets --nevents 12000 #11913
runEJsHistogrammer.py --inDir ${input_grid_lxp_k} --outDir ${output_grid_up} --inTags ${intags_80} --renameAndMove --mergeDatasets --nevents 30000 #27518
runEJsHistogrammer.py --inDir ${input_grid_lxp_k} --outDir ${output_grid_up} --inTags ${intags_90} --renameAndMove --mergeDatasets --nevents 12000 #11874
runEJsHistogrammer.py --inDir ${input_grid_lxp_o} --outDir ${output_grid_up} --inTags ${intags_mc} --renameAndMove --mergeDatasets --nevents 110000 #106079

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

