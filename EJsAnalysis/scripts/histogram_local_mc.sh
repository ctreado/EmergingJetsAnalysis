#!/bin/bash
# script for running mc tree-to-histogram jobs on local ntuples


##### MAKE SURE RUNNING ORIGINAL XAH_RUN SCANDIR IMPLEMENTATION #####


jo="$EJ_PATH/EJsanalysis/config/EJsHistoConfig.py"
tree="EJsMiniNtup/nominal"

## mc16d old official
inpath_old="$EJ_PATH/../output/localOutput/tree/local.MC16d.oldoff/data-tree/"
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

## mc16d update test -- old vs new evgen
inpath_up="$EJ_PATH/../output/localOutput/tree/local.MC16d.updatetest/data-tree/"
input_A_1000_150_999999="${inpath_up}*999999.EJ_ModelA_1000_150_4TJF_update*.root"
input_B_1000_5_999999="${inpath_up}*999999.EJ_ModelB_1000_5_4TJF_update*.root"
input_A_1000_150_310328="${inpath_up}*310328.EJ_ModelA_1000_150_4TJF_update*.root"
input_B_1000_5_310346="${inpath_up}*310346.EJ_ModelB_1000_5_4TJF_update*.root"
subdir_A_1000_150_999999="hists.local.MC16d.updatetest.EJ_ModelA_1000_150.999999"
subdir_B_1000_5_999999="hists.local.MC16d.updatetest.EJ_ModelB_1000_5.999999"
subdir_A_1000_150_310328="hists.local.MC16d.updatetest.EJ_ModelA_1000_150.310328"
subdir_B_1000_5_310346="hists.local.MC16d.updatetest.EJ_ModelB_1000_5.310346"
#xAH_run.py --files ${input_A_1000_150_999999} --config ${jo} --submitDir ${subdir_A_1000_150_999999} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1000_5_999999}   --config ${jo} --submitDir ${subdir_B_1000_5_999999}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1000_150_310328} --config ${jo} --submitDir ${subdir_A_1000_150_310328} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1000_5_310346}   --config ${jo} --submitDir ${subdir_B_1000_5_310346}   --nevents -1 --treeName ${tree} direct

## mc16d official (update)
inpath="$EJ_PATH/../output/localOutput/tree/local.MC16d/data-tree/"
#inpath="$EJ_PATH/../output/localOutput/tree/local.MC16d.312008.EJ_ModelA_1000_150/data-tree/"
input_312004="${inpath}*.312004.*EJ_ModelA_1400_20*.root"
input_312008="${inpath}*.312008.*EJ_ModelA_1000_150*.root"
input_312017="${inpath}*.312017.*EJ_ModelA_600_1*.root"
input_312022="${inpath}*.312022.*EJ_ModelB_1400_20*.root"
input_312028="${inpath}*.312028.*EJ_ModelB_1000_5*.root"
input_312031="${inpath}*.312031.*EJ_ModelB_600_300*.root"
input_312039="${inpath}*.312039.*EJ_ModelC_1400_75*.root"
input_312046="${inpath}*.312046.*EJ_ModelC_1000_5*.root"
input_312052="${inpath}*.312052.*EJ_ModelC_600_2*.root"
input_312060="${inpath}*.312060.*EJ_ModelD_1400_2*.root"
input_312066="${inpath}*.312066.*EJ_ModelD_1000_1*.root"
input_312067="${inpath}*.312067.*EJ_ModelD_600_300*.root"
input_312075="${inpath}*.312075.*EJ_ModelE_1400_75*.root"
input_312080="${inpath}*.312080.*EJ_ModelE_1000_150*.root"
input_312090="${inpath}*.312090.*EJ_ModelE_600_0p5*.root"
subdir_312004="hists.local.MC16d.312004.EJ_ModelA_1400_20"
subdir_312008="hists.local.MC16d.312008.EJ_ModelA_1000_150"
subdir_312017="hists.local.MC16d.312017.EJ_ModelA_600_1"
subdir_312022="hists.local.MC16d.312022.EJ_ModelB_1400_20"
subdir_312028="hists.local.MC16d.312028.EJ_ModelB_1000_5"
subdir_312031="hists.local.MC16d.312031.EJ_ModelB_600_300"
subdir_312039="hists.local.MC16d.312039.EJ_ModelC_1400_75"
subdir_312046="hists.local.MC16d.312046.EJ_ModelC_1000_5"
subdir_312052="hists.local.MC16d.312052.EJ_ModelC_600_2"
subdir_312060="hists.local.MC16d.312060.EJ_ModelD_1400_2"
subdir_312066="hists.local.MC16d.312066.EJ_ModelD_1000_1"
subdir_312067="hists.local.MC16d.312067.EJ_ModelD_600_300"
subdir_312075="hists.local.MC16d.312075.EJ_ModelE_1400_75"
subdir_312080="hists.local.MC16d.312080.EJ_ModelE_1000_150"
subdir_312090="hists.local.MC16d.312090.EJ_ModelE_600_0p5"
xAH_run.py --files ${input_312004} --config ${jo} --submitDir ${subdir_312004} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312008} --config ${jo} --submitDir ${subdir_312008} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312017} --config ${jo} --submitDir ${subdir_312017} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312022} --config ${jo} --submitDir ${subdir_312022} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312028} --config ${jo} --submitDir ${subdir_312028} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312031} --config ${jo} --submitDir ${subdir_312031} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312039} --config ${jo} --submitDir ${subdir_312039} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312046} --config ${jo} --submitDir ${subdir_312046} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312052} --config ${jo} --submitDir ${subdir_312052} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312060} --config ${jo} --submitDir ${subdir_312060} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312066} --config ${jo} --submitDir ${subdir_312066} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312067} --config ${jo} --submitDir ${subdir_312067} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312075} --config ${jo} --submitDir ${subdir_312075} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312080} --config ${jo} --submitDir ${subdir_312080} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_312090} --config ${jo} --submitDir ${subdir_312090} --nevents -1 --treeName ${tree} direct

## mc16d pythia di-jet background
inpath_jz4w="$EJ_PATH/../output/localOutput/tree/local.MC16d.bkgd.jz4w/data-tree/"
input_jz4w="${inpath_jz4w}*jetjet_JZ4W*.root"
subdir_jz4w="hists.local.MC16d.bkgd.jz4w"
xAH_run.py --files ${input_jz4w} --config ${jo} --submitDir ${subdir_jz4w} --nevents -1 --treeName ${tree} direct
