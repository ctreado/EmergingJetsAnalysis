#!/bin/bash
# script for running tree-to-histogram jobs

input="$EJ_PATH/../run/local.data17.00328333/data-tree/*"

jo="$EJ_PATH/EJsanalysis/config/EJsHistoConfig.py"

subdir="hists.local.data17.EJ_00328333"

tree="EJsMiniNtuple/nominal"

xAH_run.py --files ${input} --config ${jo} --submitDir ${subdir} --nevents 10 --treeName ${tree} direct
