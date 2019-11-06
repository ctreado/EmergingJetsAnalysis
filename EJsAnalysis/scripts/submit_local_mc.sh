#!/bin/bash
# script for submitting local jobs (mc)


##### OMIT ASTERISKS IN INPUT FILE PATHS WHEN RUNNING W/ HACKED XAH_RUN (TO RUN OVER MULTIPLE FILES PER SAMPLE) #####


## single sample test (mc16d)
input_08_d="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312008.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1000_150_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
input_28_d="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312028.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1000_5_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
sub_08_d="local.trees.mc16d.312008"
sub_28_d="local.trees.mc16d.312028"

## official signal samples (mc16d)
input_d="$EJ_PATH/EJsAnalysis/scripts/sample_lists/local.samples.mc16d.ejs.txt"
sub_d="local.trees.mc16d"

## pythia di-jet background (mc16d)
input_bkgd_d="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/background/DAOD/exot23/mc16_13TeV.361024.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ4W.deriv.DAOD_EXOT23.e3668_s3126_r10848_p3719/"
sub_bkgd_d="local.trees.mc16d.bkgd"


## config files
jo_a="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16a.py"
jo_d="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16d.py"
jo_e="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16e.py"


## tags
tag="test"


## job steering -- single sample tests
submitLocalEJsJobs.py --inFiles ${input_08_d} --jo ${jo_d} --subDir ${sub_08_d} --nevents 1 --isMC --outTag ${tag}
#submitLocalEJsJobs.py --inFiles ${input_28_d} --jo ${jo_d} --subDir ${sub_28_d} --nevents 1 --isMC --outTag ${tag}

## job steering -- official signal samples
#submitLocalEJsJobs.py --inFiles ${input_d} --jo ${jo_d} --subDir ${sub_d} --nevents 1 --isMC --move --delete --outTag ${tag}

# job steering -- pythia di-jet background
#submitLocalEJsJobs.py --inFiles ${input_bkgd_d} --jo ${jo_d} --subDir ${sub_bkgd_d} --nevents 1 --isMC --move --delete --outTag ${tag}


## trigger study
sub_d_trig="local.trees.mc16d.trigger"
sub_bkgd_d_trig="local.trees.mc16d.bkgd.trigger"
jo_d_trig="$EJ_PATH/EJsAnalysis/config/EJsConfig_trig_mc16d.py"
tag_trig="latest-trigger"
#submitLocalEJsJobs.py --inFiles ${input_d} --jo ${jo_d_trig} --subDir ${sub_d_trig} --nevents -1 --isMC --outTag ${tag_trig} --move --delete
#submitLocalEJsJobs.py --inFiles ${input_bkgd_d} --jo ${jo_d_trig} --subDir ${sub_bkgd_d_trig} --nevents -1 --isMC --outTag ${tag_trig} --move --delete
