#!/bin/bash
# script for submitting local jobs (mc)


##### OMIT ASTERISKS IN INPUT FILE PATHS WHEN RUNNING W/ HACKED XAH_RUN (TO RUN OVER MULTIPLE FILES PER SAMPLE) #####


## single sample test (mc16d)
input_08_d="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312008.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1000_150_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_08_d="local.MC16d.312008.EJ_ModelA_1000_150"
log_08_d="log.MC16d.312008.EJ_ModelA_1000_150.out"

## official signal samples (mc16d)
input_d="$EJ_PATH/EJsAnalysis/scripts/sample_lists/local.samples.mc16d.ejs.txt"
subdir_d="local.MC16d"
log_d="log.MC16d.out"

## pythia di-jet background (mc16d)
input_bkgd_d="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/background/DAOD/exot23/mc16_13TeV.361024.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ4W.deriv.DAOD_EXOT23.e3668_s3126_r10848_p3719/"
subdir_bkgd_d="local.MC16d.bkgd.jz4w"
log_bkgd_d="log.MC16d.bkgd.jz4w.out"


## config files
jo_a="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16a.py"
jo_d="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16d.py"
jo_e="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16e.py"


## job steering -- single sample test
#submitLocalEJsJobs.py --inFiles ${input_08_d} --jo ${jo_d} --subDir ${subdir_08_d} --nevents 100 --isMC --log ${log_08_d} \
#		       --doMove --delete

## job steering -- official signal samples
submitLocalEJsJobs.py --inFiles ${input_d} --jo ${jo_d} --subDir ${subdir_d} --nevents 100 --isMC --log ${log_d} \
		      --doMove --delete

# job steering -- pythia di-jet background
submitLocalEJsJobs.py --inFiles ${input_bkgd_d} --jo ${jo_d} --subDir ${subdir_bkgd_d} --nevents 100 --isMC --log ${log_bkgd_d} \
		      --doMove --delete


## trigger study
subdir_d_trig="local.MC16d.trigger"
log_d_trig="log.MC16d.trigger.out"
jo_d_trig="$EJ_PATH/EJsAnalysis/config/EJsConfig_trig_mc16d.py"
tag_trig="latest-trigger"
#submitLocalEJsJobs.py --inFiles ${input_d} --jo ${jo_d_trig} --subDir ${subdir_d_trig} --nevents -1 --isMC --log ${log_d_trig} \
#		      --outTag ${tag_trig} --doMove --delete
#submitLocalEJsJobs.py --inFiles ${input_bkgd_d} --jo ${jo_d_trig} --subDir ${subdir_bkgd_d_trig} --nevents -1 --isMC \
#		      --log ${log_bkgd_d_trig} --outTag ${tag_trig} --doMove --delete
