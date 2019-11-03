#!/bin/bash
# script for running mc tree-to-histogram jobs on local ntuples


##### MAKE SURE RUNNING ORIGINAL XAH_RUN SCANDIR IMPLEMENTATION #####


jo="$EJ_PATH/EJsanalysis/config/EJsHistoConfig.py"
tree="EJsMiniNtup/nominal"

## mc16d official
inpath="$EJ_PATH/../output/localOutput/latest/tree/"
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
input_jz4w="${inpath}*jetjet_JZ4W*.root"
subdir_jz4w="hists.local.MC16d.bkgd.jz4w"
#xAH_run.py --files ${input_jz4w} --config ${jo} --submitDir ${subdir_jz4w} --nevents -1 --treeName ${tree} direct


## trigger study
inpath_trig="$EJ_PATH/../output/localOutput/latest-trigger/tree/"
input_312004_trig="${inpath_trig}*.312004.*EJ_ModelA_1400_20*.root"
input_312008_trig="${inpath_trig}*.312008.*EJ_ModelA_1000_150*.root"
input_312017_trig="${inpath_trig}*.312017.*EJ_ModelA_600_1*.root"
input_312022_trig="${inpath_trig}*.312022.*EJ_ModelB_1400_20*.root"
input_312028_trig="${inpath_trig}*.312028.*EJ_ModelB_1000_5*.root"
input_312031_trig="${inpath_trig}*.312031.*EJ_ModelB_600_300*.root"
input_312039_trig="${inpath_trig}*.312039.*EJ_ModelC_1400_75*.root"
input_312046_trig="${inpath_trig}*.312046.*EJ_ModelC_1000_5*.root"
input_312052_trig="${inpath_trig}*.312052.*EJ_ModelC_600_2*.root"
input_312060_trig="${inpath_trig}*.312060.*EJ_ModelD_1400_2*.root"
input_312066_trig="${inpath_trig}*.312066.*EJ_ModelD_1000_1*.root"
input_312067_trig="${inpath_trig}*.312067.*EJ_ModelD_600_300*.root"
input_312075_trig="${inpath_trig}*.312075.*EJ_ModelE_1400_75*.root"
input_312080_trig="${inpath_trig}*.312080.*EJ_ModelE_1000_150*.root"
input_312090_trig="${inpath_trig}*.312090.*EJ_ModelE_600_0p5*.root"
subdir_312004_trig="hists.local.MC16d.312004.EJ_ModelA_1400_20.trigger"
subdir_312008_trig="hists.local.MC16d.312008.EJ_ModelA_1000_150.trigger"
subdir_312017_trig="hists.local.MC16d.312017.EJ_ModelA_600_1.trigger"
subdir_312022_trig="hists.local.MC16d.312022.EJ_ModelB_1400_20.trigger"
subdir_312028_trig="hists.local.MC16d.312028.EJ_ModelB_1000_5.trigger"
subdir_312031_trig="hists.local.MC16d.312031.EJ_ModelB_600_300.trigger"
subdir_312039_trig="hists.local.MC16d.312039.EJ_ModelC_1400_75.trigger"
subdir_312046_trig="hists.local.MC16d.312046.EJ_ModelC_1000_5.trigger"
subdir_312052_trig="hists.local.MC16d.312052.EJ_ModelC_600_2.trigger"
subdir_312060_trig="hists.local.MC16d.312060.EJ_ModelD_1400_2.trigger"
subdir_312066_trig="hists.local.MC16d.312066.EJ_ModelD_1000_1.trigger"
subdir_312067_trig="hists.local.MC16d.312067.EJ_ModelD_600_300.trigger"
subdir_312075_trig="hists.local.MC16d.312075.EJ_ModelE_1400_75.trigger"
subdir_312080_trig="hists.local.MC16d.312080.EJ_ModelE_1000_150.trigger"
subdir_312090_trig="hists.local.MC16d.312090.EJ_ModelE_600_0p5.trigger"
jo_trig="$EJ_PATH/EJsanalysis/config/EJsHistoConfig_trig.py"
#xAH_run.py --files ${input_312004_trig} --config ${jo_trig} --submitDir ${subdir_312004_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312008_trig} --config ${jo_trig} --submitDir ${subdir_312008_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312017_trig} --config ${jo_trig} --submitDir ${subdir_312017_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312022_trig} --config ${jo_trig} --submitDir ${subdir_312022_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312028_trig} --config ${jo_trig} --submitDir ${subdir_312028_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312031_trig} --config ${jo_trig} --submitDir ${subdir_312031_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312039_trig} --config ${jo_trig} --submitDir ${subdir_312039_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312046_trig} --config ${jo_trig} --submitDir ${subdir_312046_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312052_trig} --config ${jo_trig} --submitDir ${subdir_312052_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312060_trig} --config ${jo_trig} --submitDir ${subdir_312060_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312066_trig} --config ${jo_trig} --submitDir ${subdir_312066_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312067_trig} --config ${jo_trig} --submitDir ${subdir_312067_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312075_trig} --config ${jo_trig} --submitDir ${subdir_312075_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312080_trig} --config ${jo_trig} --submitDir ${subdir_312080_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_312090_trig} --config ${jo_trig} --submitDir ${subdir_312090_trig} --nevents -1 --treeName ${tree} direct
