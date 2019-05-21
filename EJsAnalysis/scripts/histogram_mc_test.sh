#!/bin/bash
# script for running mc tree-to-histogram jobs

##### MAKE SURE RUNNING ORIGINAL XAH_RUN SCANDIR IMPLEMENTATION #####

jo="$EJ_PATH/EJsanalysis/config/EJsHistoConfig.py"
tree="EJsMiniNtup/nominal"

## mc16d old official
inpath_old="$EJ_PATH/../run/localOutput/tree/local.MC16d.oldoff/data-tree/"
input_A_1400_20="${inpath_old}*ModelA_1400_20*.root"
input_A_1000_150="${inpath_old}*ModelA_1000_150*.root"
input_B_1400_20="${inpath_old}*ModelB_1400_20*.root"
input_B_1000_5="${inpath_old}*ModelB_1000_5*.root"
input_C_1400_20="${inpath_old}*ModelC_1400_20*.root"
input_C_1000_75="${inpath_old}*ModelC_1000_75*.root"
input_C_600_20="${inpath_old}*ModelC_600_20*.root"
input_D_600_300="${inpath_old}*ModelD_600_300*.root"
input_E_600_75="${inpath_old}*ModelE_600_75*.root"
subdir_A_1400_20="hists.local.MC16d.oldoff.EJ_ModelA_1400_20"
subdir_A_1000_150="hists.local.MC16d.oldoff.EJ_ModelA_1000_150"
subdir_B_1400_20="hists.local.MC16d.oldoff.EJ_ModelB_1400_20"
subdir_B_1000_5="hists.local.MC16d.oldoff.EJ_ModelB_1000_5"
subdir_C_1400_20="hists.local.MC16d.oldoff.EJ_ModelC_1400_20"
subdir_C_1000_75="hists.local.MC16d.oldoff.EJ_ModelC_1000_75"
subdir_C_600_20="hists.local.MC16d.oldoff.EJ_ModelC_600_20"
subdir_D_600_300="hists.local.MC16d.oldoff.EJ_ModelD_600_300"
subdir_E_600_75="hists.local.MC16d.oldoff.EJ_ModelE_600_75"
#xAH_run.py --files ${input_A_1400_20}  --config ${jo} --submitDir ${subdir_A_1400_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1000_150} --config ${jo} --submitDir ${subdir_A_1000_150} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1400_20}  --config ${jo} --submitDir ${subdir_B_1400_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1000_5}   --config ${jo} --submitDir ${subdir_B_1000_5}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1400_20}  --config ${jo} --submitDir ${subdir_C_1400_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1000_75}  --config ${jo} --submitDir ${subdir_C_1000_75}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_600_20}   --config ${jo} --submitDir ${subdir_C_600_20}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_600_300}  --config ${jo} --submitDir ${subdir_D_600_300}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_600_75}   --config ${jo} --submitDir ${subdir_E_600_75}   --nevents -1 --treeName ${tree} direct

## mc16d_updatetest -- old vs new evgen
inpath_up="$EJ_PATH/../run/localOutput/tree/local.MC16d.updatetest/data-tree/"
input_A_1000_150_999999="${inpath_up}*999999.EJ_ModelA_1000_150_4TJF_update*.root"
input_B_1000_5_999999="${inpath_up}*999999.EJ_ModelB_1000_5_4TJF_update*.root"
input_A_1000_150_310328="${inpath_up}*310328.EJ_ModelA_1000_150_4TJF_update*.root"
input_B_1000_5_310346="${inpath_up}*310346.EJ_ModelB_1000_5_4TJF_update*.root"
subdir_A_1000_150_999999="hists.local.MC16d.updatetest.EJ_ModelA_1000_150.999999"
subdir_B_1000_5_999999="hists.local.MC16d.updatetest.EJ_ModelB_1000_5.999999"
subdir_A_1000_150_310328="hists.local.MC16d.updatetest.EJ_ModelA_1000_150.310328"
subdir_B_1000_5_310346="hists.local.MC16d.updatetest.EJ_ModelB_1000_5.310346"
xAH_run.py --files ${input_A_1000_150_999999} --config ${jo} --submitDir ${subdir_A_1000_150_999999} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_B_1000_5_999999}   --config ${jo} --submitDir ${subdir_B_1000_5_999999}   --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_A_1000_150_310328} --config ${jo} --submitDir ${subdir_A_1000_150_310328} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_B_1000_5_310346}   --config ${jo} --submitDir ${subdir_B_1000_5_310346}   --nevents -1 --treeName ${tree} direct
