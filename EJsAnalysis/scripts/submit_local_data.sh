#!/bin/bash
# script for submitting local jobs (data)


input="$HOME/emerging_jets/datasets/data/data17/DAOD/local/exot23/data17_13TeV.00328333.exot23/*"

jo="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"

subdir="local.data17.00328333"


xAH_run.py --files ${input} --config ${jo} --submitDir ${subdir} direct
