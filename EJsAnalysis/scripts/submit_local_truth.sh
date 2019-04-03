#!/bin/bash
# script for submitting local jobs (mc)

input="$HOME/emerging_jets/datasets/montecarlo/pythia8/TRUTH_DAOD/pythia8230/modA_1000_150_211ctau/*"
input_list="$HOME/emerging_jets/datasets/montecarlo/pythia8/TRUTH_DAOD/pythia8183/modA_run/* $HOME/emerging_jets/datasets/montecarlo/pythia8/TRUTH_DAOD/pythia8183/modB_run/* $HOME/emerging_jets/datasets/montecarlo/pythia8/TRUTH_DAOD/pythia8230/modA_1000_150/* $HOME/emerging_jets/datasets/montecarlo/pythia8/TRUTH_DAOD/pythia8230/modB_1000_5/* $HOME/emerging_jets/datasets/montecarlo/pythia8/TRUTH_DAOD/pythia8230/modA_1000_150_211ctau/* $HOME/emerging_jets/datasets/montecarlo/pythia8/TRUTH_DAOD/pythia8230/modB_1000_5_211ctau/*"

jo="$EJ_PATH/EJsAnalysis/config/EJsTruthConfig.py"

subdir="local.truth.pythia82.A.211ctau"
subdir_list="local.truth"

#xAH_run.py --files ${input} --config ${jo} --submitDir ${subdir} --nevents -1 --isMC direct
xAH_run.py --files ${input_list} --config ${jo} --submitDir ${subdir_list} --nevents -1 --isMC direct
