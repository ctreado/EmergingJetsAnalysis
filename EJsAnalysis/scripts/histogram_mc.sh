#!/bin/bash
# script for running tree-to-histogram jobs

inpath="$EJ_PATH/../run/local.MC16d/data-tree/"
#inpath="$EJ_PATH/../run/local.MC16d.EJ_ModelA_1400_20/data-tree/"
input_A_1400_20="${inpath}*ModelA_1400_20*.root"
input_A_1000_150="${inpath}*ModelA_1000_150*.root"
input_B_1400_20="${inpath}*ModelB_1400_20*.root"
input_B_1000_5="${inpath}*ModelB_1000_5*.root"
input_C_1400_20="${inpath}*ModelC_1400_20*.root"
input_C_1000_75="${inpath}*ModelC_1000_75*.root"
input_C_600_20="${inpath}*ModelC_600_20*.root"
input_D_600_300="${inpath}*ModelD_600_300*.root"
input_E_600_75="${inpath}*ModelE_600_75*.root"

jo="$EJ_PATH/EJsanalysis/config/EJsHistoConfig.py"

#subdir_A_1400_20="hists.test.local.MC16d.EJ_ModelA_1400_20"
subdir_A_1400_20="hists.local.MC16d.EJ_ModelA_1400_20"
subdir_A_1000_150="hists.local.MC16d.EJ_ModelA_1000_150"
subdir_B_1400_20="hists.local.MC16d.EJ_ModelB_1400_20"
subdir_B_1000_5="hists.local.MC16d.EJ_ModelB_1000_5"
subdir_C_1400_20="hists.local.MC16d.EJ_ModelC_1400_20"
subdir_C_1000_75="hists.local.MC16d.EJ_ModelC_1000_75"
subdir_C_600_20="hists.local.MC16d.EJ_ModelC_600_20"
subdir_D_600_300="hists.local.MC16d.EJ_ModelD_600_300"
subdir_E_600_75="hists.local.MC16d.EJ_ModelE_600_75"

tree="EJsMiniNtup/nominal"

xAH_run.py --files ${input_A_1400_20}  --config ${jo} --submitDir ${subdir_A_1400_20}  --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_A_1000_150} --config ${jo} --submitDir ${subdir_A_1000_150} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_B_1400_20}  --config ${jo} --submitDir ${subdir_B_1400_20}  --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_B_1000_5}   --config ${jo} --submitDir ${subdir_B_1000_5}   --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_C_1400_20}  --config ${jo} --submitDir ${subdir_C_1400_20}  --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_C_1000_75}  --config ${jo} --submitDir ${subdir_C_1000_75}  --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_C_600_20}   --config ${jo} --submitDir ${subdir_C_600_20}   --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_D_600_300}  --config ${jo} --submitDir ${subdir_D_600_300}  --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_E_600_75}   --config ${jo} --submitDir ${subdir_E_600_75}   --nevents -1 --treeName ${tree} direct
