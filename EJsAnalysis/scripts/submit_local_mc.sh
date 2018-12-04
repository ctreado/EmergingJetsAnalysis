#!/bin/bash
# script for submitting local jobs (mc)

input="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_local/exot23/310325.EJ_ModelA_1400_20_4jetFilter.r10739.exot23/*"

jo="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"

subdir="local.MC16d.EJ_ModelA_1400_20"

xAH_run.py --files ${input} --config ${jo} --submitDir ${subdir} --nevents 10 --isMC direct
# --isMC option doesn't seem wholly necessary -->
# --> if not set, xAH::Algorithm will check eventInfo object to determine if data or mc
