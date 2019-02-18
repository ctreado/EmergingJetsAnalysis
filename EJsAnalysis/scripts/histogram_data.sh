#!/bin/bash
# script for running tree-to-histogram jobs

inpath="$EJ_PATH/../run/local.data/data-tree/"
#inpath="$EJ_PATH/../run/local.data17.00328333/"
input_17="${inpath}data17_13TeV.00328333.physics_Main.deriv.DAOD_EXOT23.r10203_r10658_p3578_p3664.root"
input_16="${inpath}data16_13TeV.00302872.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664.root"
input_15="${inpath}data15_13TeV.00284285.physics_Main.deriv.DAOD_EXOT23.r9264_r10573_p3578_p3664.root"

jo="$EJ_PATH/EJsanalysis/config/EJsHistoConfig.py"

subdir_17="hists.local.data17.00328333"
subdir_16="hists.local.data16.00302872"
subdir_15="hists.local.data15.00284285"

tree="EJsMiniNtup/nominal"

xAH_run.py --files ${input_17} --config ${jo} --submitDir ${subdir_17} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_16} --config ${jo} --submitDir ${subdir_16} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_15} --config ${jo} --submitDir ${subdir_15} --nevents -1 --treeName ${tree} direct
