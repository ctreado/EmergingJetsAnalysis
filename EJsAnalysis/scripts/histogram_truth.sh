#!/bin/bash
# script for running tree-to-histogram jobs

inpath="$EJ_PATH/../run/localOutput/tree/local.truth/data-tree/"
#inpath="$EJ_PATH/../run/localOutput/tree/local.truth.pythia81.A/data-tree/"
input_81_A="${inpath}modA_run.root"
input_81_B="${inpath}modB_run.root"
input_82_A="${inpath}modA_1000_150.root"
input_82_B="${inpath}modB_1000_5.root"
input_82_A_211ctau="${inpath}modA_1000_150_211ctau.root"
input_82_B_211ctau="${inpath}modB_1000_5_211ctau.root"

jo="$EJ_PATH/EJsanalysis/config/EJsTruthHistoConfig.py"

subdir_81_A="hists.local.truth.py81.A_1000_150"
subdir_81_B="hists.local.truth.py81.B_1000_5"
subdir_82_A="hists.local.truth.py82.A_1000_150"
subdir_82_B="hists.local.truth.py82.B_1000_5"
subdir_82_A_211ctau="hists.local.truth.py82.A_1000_150.211ctau"
subdir_82_B_211ctau="hists.local.truth.py82.B_1000_5.211ctau"

tree="EJsMiniNtup/nominal"

xAH_run.py --files ${input_81_A}          --config ${jo} --submitDir ${subdir_81_A}          --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_81_B}          --config ${jo} --submitDir ${subdir_81_B}          --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_82_A}          --config ${jo} --submitDir ${subdir_82_A}          --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_82_B}          --config ${jo} --submitDir ${subdir_82_B}          --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_82_A_211ctau}  --config ${jo} --submitDir ${subdir_82_A_211ctau}  --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_82_B_211ctau}  --config ${jo} --submitDir ${subdir_82_B_211ctau}  --nevents -1 --treeName ${tree} direct
