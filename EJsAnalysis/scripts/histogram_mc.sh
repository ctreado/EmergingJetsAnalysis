#!/bin/bash
# script for running tree-to-histogram jobs

input="$EJ_PATH/../run/local.MC16d.EJ_ModelA_1400_20/data-tree/*"

jo="$EJ_PATH/EJsanalysis/config/EJsHistoConfig.py"

subdir="hists.local.MC16d.EJ_ModelA_1400_20"

tree="EJsMiniNtuple/nominal"

xAH_run.py --files ${input} --config ${jo} --submitDir ${subdir} --nevents 10 --treeName ${tree} direct
