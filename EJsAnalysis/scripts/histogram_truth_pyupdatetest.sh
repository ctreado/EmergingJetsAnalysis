#!/bin/bash
# script for running truth tree-to-histogram jobs

##### MAKE SURE RUNNING ORIGINAL XAH_RUN SCANDIR IMPLEMENTATION #####

jo="$EJ_PATH/EJsanalysis/config/EJsTruthHistoConfig.py"
tree="EJsMiniNtup/nominal"

##single sample test
#input="$EJ_PATH/../run/localOutput/tree/local.truth.mc15update.A.1400.300/data-tree/*"
#subdir="hists.local.truth.mc15update.A.1400.300.singletest.root"
#xAH_run.py --files ${input} --config ${jo} --submitDir ${subdir} --nevents -1 --treeName ${tree} direct

## py81 vs py82 vs py82_211ctau
#inpath_py="$EJ_PATH/../run/localOutput/tree/local.truth.pytest/data-tree/"
#input_81_A="${inpath_py}modA_run.root"
#input_81_B="${inpath_py}modB_run.root"
#input_82_A="${inpath_py}modA_1000_150.root"
#input_82_B="${inpath_py}modB_1000_5.root"
#input_82_A_211ctau="${inpath_py}modA_1000_150_211ctau.root"
#input_82_B_211ctau="${inpath_py}modB_1000_5_211ctau.root"
#subdir_81_A="hists.local.truth.pytest.py81.A_1000_150"
#subdir_81_B="hists.local.truth.pytest.py81.B_1000_5"
#subdir_82_A="hists.local.truth.pytest.py82.A_1000_150"
#subdir_82_B="hists.local.truth.pytest.py82.B_1000_5"
#subdir_82_A_211ctau="hists.local.truth.pytest.py82.A_1000_150.211ctau"
#subdir_82_B_211ctau="hists.local.truth.pytest.py82.B_1000_5.211ctau"
#xAH_run.py --files ${input_81_A}         --config ${jo} --submitDir ${subdir_81_A}         --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_81_B}         --config ${jo} --submitDir ${subdir_81_B}         --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_82_A}         --config ${jo} --submitDir ${subdir_82_A}         --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_82_B}         --config ${jo} --submitDir ${subdir_82_B}         --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_82_A_211ctau} --config ${jo} --submitDir ${subdir_82_A_211ctau} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_82_B_211ctau} --config ${jo} --submitDir ${subdir_82_B_211ctau} --nevents -1 --treeName ${tree} direct

## mc15_4tjf vs mc15_211ctau_4tjf
#inpath_mc="$EJ_PATH/../run/localOutput/tree/local.truth.mc15test/data-tree/"
#input_A="${inpath_mc}modA_1000_150_4TJF.root"
#input_B="${inpath_mc}modB_1000_5_4TJF.root"
#input_A_211ctau="${inpath_mc}modA_1000_150_211ctau_4TJF.root"
#input_B_211ctau="${inpath_mc}modB_1000_5_211ctau_4TJF.root"
#subdir_A="hists.local.truth.mc15test.A_1000_150_4TJF"
#subdir_B="hists.local.truth.mc15test.B_1000_5_4TJF"
#subdir_A_211ctau="hists.local.truth.mc15test.A_1000_150_211ctau_4TJF"
#subdir_B_211ctau="hists.local.truth.mc15test.B_1000_5_211ctau_4TJF"
#xAH_run.py --files ${input_A}         --config ${jo} --submitDir ${subdir_A}         --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B}         --config ${jo} --submitDir ${subdir_B}         --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_211ctau} --config ${jo} --submitDir ${subdir_A_211ctau} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_211ctau} --config ${jo} --submitDir ${subdir_B_211ctau} --nevents -1 --treeName ${tree} direct

## mc_official vs mc15_update
#inpath_up="$EJ_PATH/../run/localOutput/tree/local.truth.mc15updatetest/data-tree/"
#input_A_999999="${inpath_up}modA_1000_150_999999.root"
#input_B_999999="${inpath_up}modB_1000_5_999999.root"
#input_A_310328="${inpath_up}modA_1000_150_310328.root"
#input_B_310346="${inpath_up}modB_1000_5_310346.root"
#subdir_A_999999="hists.local.truth.mc15updatetest.999999.A_1000_150_4TJF"
#subdir_B_999999="hists.local.truth.mc15updatetest.999999.B_1000_5_4TJF"
#subdir_A_310328="hists.local.truth.mc15updatetest.310328.A_1000_150_4TJF"
#subdir_B_310346="hists.local.truth.mc15updatetest.310346.B_1000_5_4TJF"
#xAH_run.py --files ${input_A_999999} --config ${jo} --submitDir ${subdir_A_999999} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_999999} --config ${jo} --submitDir ${subdir_B_999999} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_310328} --config ${jo} --submitDir ${subdir_A_310328} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_310346} --config ${jo} --submitDir ${subdir_B_310346} --nevents -1 --treeName ${tree} direct

## mc_official vs mc15_update (10k)
inpath_up_10k="$EJ_PATH/../run/localOutput/tree/local.truth.mc15updatetest.10k/data-tree/"
input_A_999999_10k="${inpath_up_10k}modA_1000_150_999999_10k.root"
input_B_999999_10k="${inpath_up_10k}modB_1000_5_999999_10k.root"
input_A_310328_10k="${inpath_up_10k}modA_1000_150_310328_10k.root"
input_B_310346_10k="${inpath_up_10k}modB_1000_5_310346_10k.root"
subdir_A_999999_10k="hists.local.truth.mc15updatetest.10k.999999.A_1000_150_4TJF"
subdir_B_999999_10k="hists.local.truth.mc15updatetest.10k.999999.B_1000_5_4TJF"
subdir_A_310328_10k="hists.local.truth.mc15updatetest.10k.310328.A_1000_150_4TJF"
subdir_B_310346_10k="hists.local.truth.mc15updatetest.10k.310346.B_1000_5_4TJF"
xAH_run.py --files ${input_A_999999_10k} --config ${jo} --submitDir ${subdir_A_999999_10k} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_B_999999_10k} --config ${jo} --submitDir ${subdir_B_999999_10k} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_A_310328_10k} --config ${jo} --submitDir ${subdir_A_310328_10k} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_B_310346_10k} --config ${jo} --submitDir ${subdir_B_310346_10k} --nevents -1 --treeName ${tree} direct



## mc15_211ctau_4TJF -- ALL POINTS ##
truthtype="mc15update"
intype="211ctau_"
#truthtype="mc15oldoff"
#intype=""

inpath_A="$EJ_PATH/../run/localOutput/tree/local.truth.${truthtype}.A/data-tree/" ## Model A
# ModelA_1400
input_A_1400_300="${inpath_A}modA_1400_300_${intype}4TJF.root"
input_A_1400_150="${inpath_A}modA_1400_150_${intype}4TJF.root"
input_A_1400_75="${inpath_A}modA_1400_75_${intype}4TJF.root"
input_A_1400_20="${inpath_A}modA_1400_20_${intype}4TJF.root"
input_A_1400_5="${inpath_A}modA_1400_5_${intype}4TJF.root"
input_A_1400_2="${inpath_A}modA_1400_2_${intype}4TJF.root"
input_A_1400_1="${inpath_A}modA_1400_1_${intype}4TJF.root"
input_A_1400_0p5="${inpath_A}modA_1400_0p5_${intype}4TJF.root"
subdir_A_1400_300="hists.local.truth.${truthtype}.A_1400_300_4TJF"
subdir_A_1400_150="hists.local.truth.${truthtype}.A_1400_150_4TJF"
subdir_A_1400_75="hists.local.truth.${truthtype}.A_1400_75_4TJF"
subdir_A_1400_20="hists.local.truth.${truthtype}.A_1400_20_4TJF"
subdir_A_1400_5="hists.local.truth.${truthtype}.A_1400_5_4TJF"
subdir_A_1400_2="hists.local.truth.${truthtype}.A_1400_2_4TJF"
subdir_A_1400_1="hists.local.truth.${truthtype}.A_1400_1_4TJF"
subdir_A_1400_0p5="hists.local.truth.${truthtype}.A_1400_0p5_4TJF"
#xAH_run.py --files ${input_A_1400_300} --config ${jo} --submitDir ${subdir_A_1400_300} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1400_150} --config ${jo} --submitDir ${subdir_A_1400_150} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1400_75}  --config ${jo} --submitDir ${subdir_A_1400_75}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1400_20}  --config ${jo} --submitDir ${subdir_A_1400_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1400_5}   --config ${jo} --submitDir ${subdir_A_1400_5}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1400_2}   --config ${jo} --submitDir ${subdir_A_1400_2}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1400_1}   --config ${jo} --submitDir ${subdir_A_1400_1}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1400_0p5} --config ${jo} --submitDir ${subdir_A_1400_0p5} --nevents -1 --treeName ${tree} direct
# ModelA_1000
input_A_1400_0p5="${inpath_A}modA_1400_0p5_${intype}4TJF.root" 
input_A_1000_300="${inpath_A}modA_1000_300_${intype}4TJF.root"
input_A_1000_150="${inpath_A}modA_1000_150_${intype}4TJF.root"
input_A_1000_75="${inpath_A}modA_1000_75_${intype}4TJF.root"
input_A_1000_20="${inpath_A}modA_1000_20_${intype}4TJF.root"
input_A_1000_5="${inpath_A}modA_1000_5_${intype}4TJF.root"
input_A_1000_2="${inpath_A}modA_1000_2_${intype}4TJF.root"
input_A_1000_1="${inpath_A}modA_1000_1_${intype}4TJF.root"
input_A_1000_0p5="${inpath_A}modA_1000_0p5_${intype}4TJF.root"
subdir_A_1000_300="hists.local.truth.${truthtype}.A_1000_300_4TJF"
subdir_A_1000_150="hists.local.truth.${truthtype}.A_1000_150_4TJF"
subdir_A_1000_75="hists.local.truth.${truthtype}.A_1000_75_4TJF"
subdir_A_1000_20="hists.local.truth.${truthtype}.A_1000_20_4TJF"
subdir_A_1000_5="hists.local.truth.${truthtype}.A_1000_5_4TJF"
subdir_A_1000_2="hists.local.truth.${truthtype}.A_1000_2_4TJF"
subdir_A_1000_1="hists.local.truth.${truthtype}.A_1000_1_4TJF"
subdir_A_1000_0p5="hists.local.truth.${truthtype}.A_1000_0p5_4TJF"
#xAH_run.py --files ${input_A_1000_300} --config ${jo} --submitDir ${subdir_A_1000_300} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1000_150} --config ${jo} --submitDir ${subdir_A_1000_150} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1000_75}  --config ${jo} --submitDir ${subdir_A_1000_75}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1000_20}  --config ${jo} --submitDir ${subdir_A_1000_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1000_5}   --config ${jo} --submitDir ${subdir_A_1000_5}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1000_2}   --config ${jo} --submitDir ${subdir_A_1000_2}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1000_1}   --config ${jo} --submitDir ${subdir_A_1000_1}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_1000_0p5} --config ${jo} --submitDir ${subdir_A_1000_0p5} --nevents -1 --treeName ${tree} direct
# ModelA_600
input_A_600_300="${inpath_A}modA_600_300_${intype}4TJF.root"
input_A_600_150="${inpath_A}modA_600_150_${intype}4TJF.root"
input_A_600_75="${inpath_A}modA_600_75_${intype}4TJF.root"
input_A_600_20="${inpath_A}modA_600_20_${intype}4TJF.root"
input_A_600_5="${inpath_A}modA_600_5_${intype}4TJF.root"
input_A_600_2="${inpath_A}modA_600_2_${intype}4TJF.root"
input_A_600_1="${inpath_A}modA_600_1_${intype}4TJF.root"
input_A_600_0p5="${inpath_A}modA_600_0p5_${intype}4TJF.root"
subdir_A_600_300="hists.local.truth.${truthtype}.A_600_300_4TJF"
subdir_A_600_150="hists.local.truth.${truthtype}.A_600_150_4TJF"
subdir_A_600_75="hists.local.truth.${truthtype}.A_600_75_4TJF"
subdir_A_600_20="hists.local.truth.${truthtype}.A_600_20_4TJF"
subdir_A_600_5="hists.local.truth.${truthtype}.A_600_5_4TJF"
subdir_A_600_2="hists.local.truth.${truthtype}.A_600_2_4TJF"
subdir_A_600_1="hists.local.truth.${truthtype}.A_600_1_4TJF"
subdir_A_600_0p5="hists.local.truth.${truthtype}.A_600_0p5_4TJF"
#xAH_run.py --files ${input_A_600_300}  --config ${jo} --submitDir ${subdir_A_600_300}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_600_150}  --config ${jo} --submitDir ${subdir_A_600_150}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_600_75}   --config ${jo} --submitDir ${subdir_A_600_75}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_600_20}   --config ${jo} --submitDir ${subdir_A_600_20}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_600_5}    --config ${jo} --submitDir ${subdir_A_600_5}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_600_2}    --config ${jo} --submitDir ${subdir_A_600_2}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_600_1}    --config ${jo} --submitDir ${subdir_A_600_1}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_A_600_0p5}  --config ${jo} --submitDir ${subdir_A_600_0p5}  --nevents -1 --treeName ${tree} direct

inpath_B="$EJ_PATH/../run/localOutput/tree/local.truth.${truthtype}.B/data-tree/" # ModelB
# ModelB_1400
input_B_1400_300="${inpath_B}modB_1400_300_${intype}4TJF.root"
input_B_1400_150="${inpath_B}modB_1400_150_${intype}4TJF.root"
input_B_1400_75="${inpath_B}modB_1400_75_${intype}4TJF.root"
input_B_1400_20="${inpath_B}modB_1400_20_${intype}4TJF.root"
input_B_1400_5="${inpath_B}modB_1400_5_${intype}4TJF.root"
input_B_1400_2="${inpath_B}modB_1400_2_${intype}4TJF.root"
input_B_1400_1="${inpath_B}modB_1400_1_${intype}4TJF.root"
input_B_1400_0p5="${inpath_B}modB_1400_0p5_${intype}4TJF.root"
subdir_B_1400_300="hists.local.truth.${truthtype}.B_1400_300_4TJF"
subdir_B_1400_150="hists.local.truth.${truthtype}.B_1400_150_4TJF"
subdir_B_1400_75="hists.local.truth.${truthtype}.B_1400_75_4TJF"
subdir_B_1400_20="hists.local.truth.${truthtype}.B_1400_20_4TJF"
subdir_B_1400_5="hists.local.truth.${truthtype}.B_1400_5_4TJF"
subdir_B_1400_2="hists.local.truth.${truthtype}.B_1400_2_4TJF"
subdir_B_1400_1="hists.local.truth.${truthtype}.B_1400_1_4TJF"
subdir_B_1400_0p5="hists.local.truth.${truthtype}.B_1400_0p5_4TJF"
#xAH_run.py --files ${input_B_1400_300} --config ${jo} --submitDir ${subdir_B_1400_300} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1400_150} --config ${jo} --submitDir ${subdir_B_1400_150} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1400_75}  --config ${jo} --submitDir ${subdir_B_1400_75}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1400_20}  --config ${jo} --submitDir ${subdir_B_1400_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1400_5}   --config ${jo} --submitDir ${subdir_B_1400_5}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1400_2}   --config ${jo} --submitDir ${subdir_B_1400_2}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1400_1}   --config ${jo} --submitDir ${subdir_B_1400_1}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1400_0p5} --config ${jo} --submitDir ${subdir_B_1400_0p5} --nevents -1 --treeName ${tree} direct
# ModelB_1000
input_B_1400_0p5="${inpath_B}modB_1400_0p5_${intype}4TJF.root" 
input_B_1000_300="${inpath_B}modB_1000_300_${intype}4TJF.root"
input_B_1000_150="${inpath_B}modB_1000_150_${intype}4TJF.root"
input_B_1000_75="${inpath_B}modB_1000_75_${intype}4TJF.root"
input_B_1000_20="${inpath_B}modB_1000_20_${intype}4TJF.root"
input_B_1000_5="${inpath_B}modB_1000_5_${intype}4TJF.root"
input_B_1000_2="${inpath_B}modB_1000_2_${intype}4TJF.root"
input_B_1000_1="${inpath_B}modB_1000_1_${intype}4TJF.root"
input_B_1000_0p5="${inpath_B}modB_1000_0p5_${intype}4TJF.root"
subdir_B_1000_300="hists.local.truth.${truthtype}.B_1000_300_4TJF"
subdir_B_1000_150="hists.local.truth.${truthtype}.B_1000_150_4TJF"
subdir_B_1000_75="hists.local.truth.${truthtype}.B_1000_75_4TJF"
subdir_B_1000_20="hists.local.truth.${truthtype}.B_1000_20_4TJF"
subdir_B_1000_5="hists.local.truth.${truthtype}.B_1000_5_4TJF"
subdir_B_1000_2="hists.local.truth.${truthtype}.B_1000_2_4TJF"
subdir_B_1000_1="hists.local.truth.${truthtype}.B_1000_1_4TJF"
subdir_B_1000_0p5="hists.local.truth.${truthtype}.B_1000_0p5_4TJF"
#xAH_run.py --files ${input_B_1000_300} --config ${jo} --submitDir ${subdir_B_1000_300} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1000_150} --config ${jo} --submitDir ${subdir_B_1000_150} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1000_75}  --config ${jo} --submitDir ${subdir_B_1000_75}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1000_20}  --config ${jo} --submitDir ${subdir_B_1000_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1000_5}   --config ${jo} --submitDir ${subdir_B_1000_5}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1000_2}   --config ${jo} --submitDir ${subdir_B_1000_2}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1000_1}   --config ${jo} --submitDir ${subdir_B_1000_1}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_1000_0p5} --config ${jo} --submitDir ${subdir_B_1000_0p5} --nevents -1 --treeName ${tree} direct
# ModelB_600
input_B_600_300="${inpath_B}modB_600_300_${intype}4TJF.root"
input_B_600_150="${inpath_B}modB_600_150_${intype}4TJF.root"
input_B_600_75="${inpath_B}modB_600_75_${intype}4TJF.root"
input_B_600_20="${inpath_B}modB_600_20_${intype}4TJF.root"
input_B_600_5="${inpath_B}modB_600_5_${intype}4TJF.root"
input_B_600_2="${inpath_B}modB_600_2_${intype}4TJF.root"
input_B_600_1="${inpath_B}modB_600_1_${intype}4TJF.root"
input_B_600_0p5="${inpath_B}modB_600_0p5_${intype}4TJF.root"
subdir_B_600_300="hists.local.truth.${truthtype}.B_600_300_4TJF"
subdir_B_600_150="hists.local.truth.${truthtype}.B_600_150_4TJF"
subdir_B_600_75="hists.local.truth.${truthtype}.B_600_75_4TJF"
subdir_B_600_20="hists.local.truth.${truthtype}.B_600_20_4TJF"
subdir_B_600_5="hists.local.truth.${truthtype}.B_600_5_4TJF"
subdir_B_600_2="hists.local.truth.${truthtype}.B_600_2_4TJF"
subdir_B_600_1="hists.local.truth.${truthtype}.B_600_1_4TJF"
subdir_B_600_0p5="hists.local.truth.${truthtype}.B_600_0p5_4TJF"
#xAH_run.py --files ${input_B_600_300}  --config ${jo} --submitDir ${subdir_B_600_300}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_600_150}  --config ${jo} --submitDir ${subdir_B_600_150}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_600_75}   --config ${jo} --submitDir ${subdir_B_600_75}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_600_20}   --config ${jo} --submitDir ${subdir_B_600_20}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_600_5}    --config ${jo} --submitDir ${subdir_B_600_5}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_600_2}    --config ${jo} --submitDir ${subdir_B_600_2}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_600_1}    --config ${jo} --submitDir ${subdir_B_600_1}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_B_600_0p5}  --config ${jo} --submitDir ${subdir_B_600_0p5}  --nevents -1 --treeName ${tree} direct

inpath_C="$EJ_PATH/../run/localOutput/tree/local.truth.${truthtype}.C/data-tree/" # ModelC
# ModelC_1400
input_C_1400_300="${inpath_C}modC_1400_300_${intype}4TJF.root"
input_C_1400_150="${inpath_C}modC_1400_150_${intype}4TJF.root"
input_C_1400_75="${inpath_C}modC_1400_75_${intype}4TJF.root"
input_C_1400_20="${inpath_C}modC_1400_20_${intype}4TJF.root"
input_C_1400_5="${inpath_C}modC_1400_5_${intype}4TJF.root"
input_C_1400_2="${inpath_C}modC_1400_2_${intype}4TJF.root"
input_C_1400_1="${inpath_C}modC_1400_1_${intype}4TJF.root"
input_C_1400_0p5="${inpath_C}modC_1400_0p5_${intype}4TJF.root"
subdir_C_1400_300="hists.local.truth.${truthtype}.C_1400_300_4TJF"
subdir_C_1400_150="hists.local.truth.${truthtype}.C_1400_150_4TJF"
subdir_C_1400_75="hists.local.truth.${truthtype}.C_1400_75_4TJF"
subdir_C_1400_20="hists.local.truth.${truthtype}.C_1400_20_4TJF"
subdir_C_1400_5="hists.local.truth.${truthtype}.C_1400_5_4TJF"
subdir_C_1400_2="hists.local.truth.${truthtype}.C_1400_2_4TJF"
subdir_C_1400_1="hists.local.truth.${truthtype}.C_1400_1_4TJF"
subdir_C_1400_0p5="hists.local.truth.${truthtype}.C_1400_0p5_4TJF"
#xAH_run.py --files ${input_C_1400_300} --config ${jo} --submitDir ${subdir_C_1400_300} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1400_150} --config ${jo} --submitDir ${subdir_C_1400_150} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1400_75}  --config ${jo} --submitDir ${subdir_C_1400_75}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1400_20}  --config ${jo} --submitDir ${subdir_C_1400_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1400_5}   --config ${jo} --submitDir ${subdir_C_1400_5}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1400_2}   --config ${jo} --submitDir ${subdir_C_1400_2}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1400_1}   --config ${jo} --submitDir ${subdir_C_1400_1}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1400_0p5} --config ${jo} --submitDir ${subdir_C_1400_0p5} --nevents -1 --treeName ${tree} direct
# ModelC_1000
input_C_1400_0p5="${inpath_C}modC_1400_0p5_${intype}4TJF.root" 
input_C_1000_300="${inpath_C}modC_1000_300_${intype}4TJF.root"
input_C_1000_150="${inpath_C}modC_1000_150_${intype}4TJF.root"
input_C_1000_75="${inpath_C}modC_1000_75_${intype}4TJF.root"
input_C_1000_20="${inpath_C}modC_1000_20_${intype}4TJF.root"
input_C_1000_5="${inpath_C}modC_1000_5_${intype}4TJF.root"
input_C_1000_2="${inpath_C}modC_1000_2_${intype}4TJF.root"
input_C_1000_1="${inpath_C}modC_1000_1_${intype}4TJF.root"
input_C_1000_0p5="${inpath_C}modC_1000_0p5_${intype}4TJF.root"
subdir_C_1000_300="hists.local.truth.${truthtype}.C_1000_300_4TJF"
subdir_C_1000_150="hists.local.truth.${truthtype}.C_1000_150_4TJF"
subdir_C_1000_75="hists.local.truth.${truthtype}.C_1000_75_4TJF"
subdir_C_1000_20="hists.local.truth.${truthtype}.C_1000_20_4TJF"
subdir_C_1000_5="hists.local.truth.${truthtype}.C_1000_5_4TJF"
subdir_C_1000_2="hists.local.truth.${truthtype}.C_1000_2_4TJF"
subdir_C_1000_1="hists.local.truth.${truthtype}.C_1000_1_4TJF"
subdir_C_1000_0p5="hists.local.truth.${truthtype}.C_1000_0p5_4TJF"
#xAH_run.py --files ${input_C_1000_300} --config ${jo} --submitDir ${subdir_C_1000_300} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1000_150} --config ${jo} --submitDir ${subdir_C_1000_150} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1000_75}  --config ${jo} --submitDir ${subdir_C_1000_75}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1000_20}  --config ${jo} --submitDir ${subdir_C_1000_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1000_5}   --config ${jo} --submitDir ${subdir_C_1000_5}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1000_2}   --config ${jo} --submitDir ${subdir_C_1000_2}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1000_1}   --config ${jo} --submitDir ${subdir_C_1000_1}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_1000_0p5} --config ${jo} --submitDir ${subdir_C_1000_0p5} --nevents -1 --treeName ${tree} direct
# ModelC_600
input_C_600_300="${inpath_C}modC_600_300_${intype}4TJF.root"
input_C_600_150="${inpath_C}modC_600_150_${intype}4TJF.root"
input_C_600_75="${inpath_C}modC_600_75_${intype}4TJF.root"
input_C_600_20="${inpath_C}modC_600_20_${intype}4TJF.root"
input_C_600_5="${inpath_C}modC_600_5_${intype}4TJF.root"
input_C_600_2="${inpath_C}modC_600_2_${intype}4TJF.root"
input_C_600_1="${inpath_C}modC_600_1_${intype}4TJF.root"
input_C_600_0p5="${inpath_C}modC_600_0p5_${intype}4TJF.root"
subdir_C_600_300="hists.local.truth.${truthtype}.C_600_300_4TJF"
subdir_C_600_150="hists.local.truth.${truthtype}.C_600_150_4TJF"
subdir_C_600_75="hists.local.truth.${truthtype}.C_600_75_4TJF"
subdir_C_600_20="hists.local.truth.${truthtype}.C_600_20_4TJF"
subdir_C_600_5="hists.local.truth.${truthtype}.C_600_5_4TJF"
subdir_C_600_2="hists.local.truth.${truthtype}.C_600_2_4TJF"
subdir_C_600_1="hists.local.truth.${truthtype}.C_600_1_4TJF"
subdir_C_600_0p5="hists.local.truth.${truthtype}.C_600_0p5_4TJF"
#xAH_run.py --files ${input_C_600_300}  --config ${jo} --submitDir ${subdir_C_600_300}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_600_150}  --config ${jo} --submitDir ${subdir_C_600_150}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_600_75}   --config ${jo} --submitDir ${subdir_C_600_75}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_600_20}   --config ${jo} --submitDir ${subdir_C_600_20}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_600_5}    --config ${jo} --submitDir ${subdir_C_600_5}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_600_2}    --config ${jo} --submitDir ${subdir_C_600_2}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_600_1}    --config ${jo} --submitDir ${subdir_C_600_1}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_C_600_0p5}  --config ${jo} --submitDir ${subdir_C_600_0p5}  --nevents -1 --treeName ${tree} direct

inpath_D="$EJ_PATH/../run/localOutput/tree/local.truth.${truthtype}.D/data-tree/" # ModelD
# ModelD_1400
input_D_1400_300="${inpath_D}modD_1400_300_${intype}4TJF.root"
input_D_1400_150="${inpath_D}modD_1400_150_${intype}4TJF.root"
input_D_1400_75="${inpath_D}modD_1400_75_${intype}4TJF.root"
input_D_1400_20="${inpath_D}modD_1400_20_${intype}4TJF.root"
input_D_1400_5="${inpath_D}modD_1400_5_${intype}4TJF.root"
input_D_1400_2="${inpath_D}modD_1400_2_${intype}4TJF.root"
input_D_1400_1="${inpath_D}modD_1400_1_${intype}4TJF.root"
input_D_1400_0p5="${inpath_D}modD_1400_0p5_${intype}4TJF.root"
subdir_D_1400_300="hists.local.truth.${truthtype}.D_1400_300_4TJF"
subdir_D_1400_150="hists.local.truth.${truthtype}.D_1400_150_4TJF"
subdir_D_1400_75="hists.local.truth.${truthtype}.D_1400_75_4TJF"
subdir_D_1400_20="hists.local.truth.${truthtype}.D_1400_20_4TJF"
subdir_D_1400_5="hists.local.truth.${truthtype}.D_1400_5_4TJF"
subdir_D_1400_2="hists.local.truth.${truthtype}.D_1400_2_4TJF"
subdir_D_1400_1="hists.local.truth.${truthtype}.D_1400_1_4TJF"
subdir_D_1400_0p5="hists.local.truth.${truthtype}.D_1400_0p5_4TJF"
#xAH_run.py --files ${input_D_1400_300} --config ${jo} --submitDir ${subdir_D_1400_300} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1400_150} --config ${jo} --submitDir ${subdir_D_1400_150} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1400_75}  --config ${jo} --submitDir ${subdir_D_1400_75}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1400_20}  --config ${jo} --submitDir ${subdir_D_1400_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1400_5}   --config ${jo} --submitDir ${subdir_D_1400_5}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1400_2}   --config ${jo} --submitDir ${subdir_D_1400_2}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1400_1}   --config ${jo} --submitDir ${subdir_D_1400_1}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1400_0p5} --config ${jo} --submitDir ${subdir_D_1400_0p5} --nevents -1 --treeName ${tree} direct
# ModelD_1000
input_D_1400_0p5="${inpath_D}modD_1400_0p5_${intype}4TJF.root" 
input_D_1000_300="${inpath_D}modD_1000_300_${intype}4TJF.root"
input_D_1000_150="${inpath_D}modD_1000_150_${intype}4TJF.root"
input_D_1000_75="${inpath_D}modD_1000_75_${intype}4TJF.root"
input_D_1000_20="${inpath_D}modD_1000_20_${intype}4TJF.root"
input_D_1000_5="${inpath_D}modD_1000_5_${intype}4TJF.root"
input_D_1000_2="${inpath_D}modD_1000_2_${intype}4TJF.root"
input_D_1000_1="${inpath_D}modD_1000_1_${intype}4TJF.root"
input_D_1000_0p5="${inpath_D}modD_1000_0p5_${intype}4TJF.root"
subdir_D_1000_300="hists.local.truth.${truthtype}.D_1000_300_4TJF"
subdir_D_1000_150="hists.local.truth.${truthtype}.D_1000_150_4TJF"
subdir_D_1000_75="hists.local.truth.${truthtype}.D_1000_75_4TJF"
subdir_D_1000_20="hists.local.truth.${truthtype}.D_1000_20_4TJF"
subdir_D_1000_5="hists.local.truth.${truthtype}.D_1000_5_4TJF"
subdir_D_1000_2="hists.local.truth.${truthtype}.D_1000_2_4TJF"
subdir_D_1000_1="hists.local.truth.${truthtype}.D_1000_1_4TJF"
subdir_D_1000_0p5="hists.local.truth.${truthtype}.D_1000_0p5_4TJF"
#xAH_run.py --files ${input_D_1000_300} --config ${jo} --submitDir ${subdir_D_1000_300} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1000_150} --config ${jo} --submitDir ${subdir_D_1000_150} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1000_75}  --config ${jo} --submitDir ${subdir_D_1000_75}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1000_20}  --config ${jo} --submitDir ${subdir_D_1000_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1000_5}   --config ${jo} --submitDir ${subdir_D_1000_5}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1000_2}   --config ${jo} --submitDir ${subdir_D_1000_2}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1000_1}   --config ${jo} --submitDir ${subdir_D_1000_1}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_1000_0p5} --config ${jo} --submitDir ${subdir_D_1000_0p5} --nevents -1 --treeName ${tree} direct
# ModelD_600
input_D_600_300="${inpath_D}modD_600_300_${intype}4TJF.root"
input_D_600_150="${inpath_D}modD_600_150_${intype}4TJF.root"
input_D_600_75="${inpath_D}modD_600_75_${intype}4TJF.root"
input_D_600_20="${inpath_D}modD_600_20_${intype}4TJF.root"
input_D_600_5="${inpath_D}modD_600_5_${intype}4TJF.root"
input_D_600_2="${inpath_D}modD_600_2_${intype}4TJF.root"
input_D_600_1="${inpath_D}modD_600_1_${intype}4TJF.root"
input_D_600_0p5="${inpath_D}modD_600_0p5_${intype}4TJF.root"
subdir_D_600_300="hists.local.truth.${truthtype}.D_600_300_4TJF"
subdir_D_600_150="hists.local.truth.${truthtype}.D_600_150_4TJF"
subdir_D_600_75="hists.local.truth.${truthtype}.D_600_75_4TJF"
subdir_D_600_20="hists.local.truth.${truthtype}.D_600_20_4TJF"
subdir_D_600_5="hists.local.truth.${truthtype}.D_600_5_4TJF"
subdir_D_600_2="hists.local.truth.${truthtype}.D_600_2_4TJF"
subdir_D_600_1="hists.local.truth.${truthtype}.D_600_1_4TJF"
subdir_D_600_0p5="hists.local.truth.${truthtype}.D_600_0p5_4TJF"
#xAH_run.py --files ${input_D_600_300}  --config ${jo} --submitDir ${subdir_D_600_300}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_600_150}  --config ${jo} --submitDir ${subdir_D_600_150}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_600_75}   --config ${jo} --submitDir ${subdir_D_600_75}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_600_20}   --config ${jo} --submitDir ${subdir_D_600_20}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_600_5}    --config ${jo} --submitDir ${subdir_D_600_5}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_600_2}    --config ${jo} --submitDir ${subdir_D_600_2}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_600_1}    --config ${jo} --submitDir ${subdir_D_600_1}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_D_600_0p5}  --config ${jo} --submitDir ${subdir_D_600_0p5}  --nevents -1 --treeName ${tree} direct

inpath_E="$EJ_PATH/../run/localOutput/tree/local.truth.${truthtype}.E/data-tree/" # ModelE
# ModelE_1400
input_E_1400_300="${inpath_E}modE_1400_300_${intype}4TJF.root"
input_E_1400_150="${inpath_E}modE_1400_150_${intype}4TJF.root"
input_E_1400_75="${inpath_E}modE_1400_75_${intype}4TJF.root"
input_E_1400_20="${inpath_E}modE_1400_20_${intype}4TJF.root"
input_E_1400_5="${inpath_E}modE_1400_5_${intype}4TJF.root"
input_E_1400_2="${inpath_E}modE_1400_2_${intype}4TJF.root"
input_E_1400_1="${inpath_E}modE_1400_1_${intype}4TJF.root"
input_E_1400_0p5="${inpath_E}modE_1400_0p5_${intype}4TJF.root"
subdir_E_1400_300="hists.local.truth.${truthtype}.E_1400_300_4TJF"
subdir_E_1400_150="hists.local.truth.${truthtype}.E_1400_150_4TJF"
subdir_E_1400_75="hists.local.truth.${truthtype}.E_1400_75_4TJF"
subdir_E_1400_20="hists.local.truth.${truthtype}.E_1400_20_4TJF"
subdir_E_1400_5="hists.local.truth.${truthtype}.E_1400_5_4TJF"
subdir_E_1400_2="hists.local.truth.${truthtype}.E_1400_2_4TJF"
subdir_E_1400_1="hists.local.truth.${truthtype}.E_1400_1_4TJF"
subdir_E_1400_0p5="hists.local.truth.${truthtype}.E_1400_0p5_4TJF"
#xAH_run.py --files ${input_E_1400_300} --config ${jo} --submitDir ${subdir_E_1400_300} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1400_150} --config ${jo} --submitDir ${subdir_E_1400_150} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1400_75}  --config ${jo} --submitDir ${subdir_E_1400_75}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1400_20}  --config ${jo} --submitDir ${subdir_E_1400_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1400_5}   --config ${jo} --submitDir ${subdir_E_1400_5}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1400_2}   --config ${jo} --submitDir ${subdir_E_1400_2}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1400_1}   --config ${jo} --submitDir ${subdir_E_1400_1}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1400_0p5} --config ${jo} --submitDir ${subdir_E_1400_0p5} --nevents -1 --treeName ${tree} direct
# ModelE_1000
input_E_1400_0p5="${inpath_E}modE_1400_0p5_${intype}4TJF.root" 
input_E_1000_300="${inpath_E}modE_1000_300_${intype}4TJF.root"
input_E_1000_150="${inpath_E}modE_1000_150_${intype}4TJF.root"
input_E_1000_75="${inpath_E}modE_1000_75_${intype}4TJF.root"
input_E_1000_20="${inpath_E}modE_1000_20_${intype}4TJF.root"
input_E_1000_5="${inpath_E}modE_1000_5_${intype}4TJF.root"
input_E_1000_2="${inpath_E}modE_1000_2_${intype}4TJF.root"
input_E_1000_1="${inpath_E}modE_1000_1_${intype}4TJF.root"
input_E_1000_0p5="${inpath_E}modE_1000_0p5_${intype}4TJF.root"
subdir_E_1000_300="hists.local.truth.${truthtype}.E_1000_300_4TJF"
subdir_E_1000_150="hists.local.truth.${truthtype}.E_1000_150_4TJF"
subdir_E_1000_75="hists.local.truth.${truthtype}.E_1000_75_4TJF"
subdir_E_1000_20="hists.local.truth.${truthtype}.E_1000_20_4TJF"
subdir_E_1000_5="hists.local.truth.${truthtype}.E_1000_5_4TJF"
subdir_E_1000_2="hists.local.truth.${truthtype}.E_1000_2_4TJF"
subdir_E_1000_1="hists.local.truth.${truthtype}.E_1000_1_4TJF"
subdir_E_1000_0p5="hists.local.truth.${truthtype}.E_1000_0p5_4TJF"
#xAH_run.py --files ${input_E_1000_300} --config ${jo} --submitDir ${subdir_E_1000_300} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1000_150} --config ${jo} --submitDir ${subdir_E_1000_150} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1000_75}  --config ${jo} --submitDir ${subdir_E_1000_75}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1000_20}  --config ${jo} --submitDir ${subdir_E_1000_20}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1000_5}   --config ${jo} --submitDir ${subdir_E_1000_5}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1000_2}   --config ${jo} --submitDir ${subdir_E_1000_2}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1000_1}   --config ${jo} --submitDir ${subdir_E_1000_1}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_1000_0p5} --config ${jo} --submitDir ${subdir_E_1000_0p5} --nevents -1 --treeName ${tree} direct
# ModelE_600
input_E_600_300="${inpath_E}modE_600_300_${intype}4TJF.root"
input_E_600_150="${inpath_E}modE_600_150_${intype}4TJF.root"
input_E_600_75="${inpath_E}modE_600_75_${intype}4TJF.root"
input_E_600_20="${inpath_E}modE_600_20_${intype}4TJF.root"
input_E_600_5="${inpath_E}modE_600_5_${intype}4TJF.root"
input_E_600_2="${inpath_E}modE_600_2_${intype}4TJF.root"
input_E_600_1="${inpath_E}modE_600_1_${intype}4TJF.root"
input_E_600_0p5="${inpath_E}modE_600_0p5_${intype}4TJF.root"
subdir_E_600_300="hists.local.truth.${truthtype}.E_600_300_4TJF"
subdir_E_600_150="hists.local.truth.${truthtype}.E_600_150_4TJF"
subdir_E_600_75="hists.local.truth.${truthtype}.E_600_75_4TJF"
subdir_E_600_20="hists.local.truth.${truthtype}.E_600_20_4TJF"
subdir_E_600_5="hists.local.truth.${truthtype}.E_600_5_4TJF"
subdir_E_600_2="hists.local.truth.${truthtype}.E_600_2_4TJF"
subdir_E_600_1="hists.local.truth.${truthtype}.E_600_1_4TJF"
subdir_E_600_0p5="hists.local.truth.${truthtype}.E_600_0p5_4TJF"
#xAH_run.py --files ${input_E_600_300}  --config ${jo} --submitDir ${subdir_E_600_300}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_600_150}  --config ${jo} --submitDir ${subdir_E_600_150}  --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_600_75}   --config ${jo} --submitDir ${subdir_E_600_75}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_600_20}   --config ${jo} --submitDir ${subdir_E_600_20}   --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_600_5}    --config ${jo} --submitDir ${subdir_E_600_5}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_600_2}    --config ${jo} --submitDir ${subdir_E_600_2}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_600_1}    --config ${jo} --submitDir ${subdir_E_600_1}    --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_E_600_0p5}  --config ${jo} --submitDir ${subdir_E_600_0p5}  --nevents -1 --treeName ${tree} direct
