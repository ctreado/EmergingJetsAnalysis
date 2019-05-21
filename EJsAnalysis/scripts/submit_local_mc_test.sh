#!/bin/bash
# script for submitting local jobs (mc)

##### OMIT ASTERISKS IN INPUT FILE PATHS WHEN RUNNING W/ HACKED XAH_RUN (TO RUN OVER MULTIPLE FILES PER SAMPLE) #####

## single sample test
input="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310325.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/*"
subdir="local.MC16d.EJ_ModelA_1400_20"

## mc16d old official
#input_list="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310325.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310328.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1000_150_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310340.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310346.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1000_5_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310355.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310359.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1000_75_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310365.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_600_20_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310377.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelD_600_300_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310394.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelE_600_75_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/*"
#subdir_list="local.MC16d.oldoff"

## mc16d_updatetest -- old vs new evgen
#input_list="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/310328.EJ_ModelA_1000_150_4TJF_update.r10739.exot23/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/310346.EJ_ModelB_1000_5_4TJF_update.r10739.exot23/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/999999.EJ_ModelA_1000_150_4TJF_update.r10739.exot23/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/999999.EJ_ModelB_1000_5_4TJF_update.r10739.exot23/*"
input_list="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/310328.EJ_ModelA_1000_150_4TJF_update.r10739.exot23/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/999999.EJ_ModelA_1000_150_4TJF_update.r10739.exot23/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/310346.EJ_ModelB_1000_5_4TJF_update.r10739.exot23/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/999999.EJ_ModelB_1000_5_4TJF_update.r10739.exot23/*"
subdir_list="local.MC16d.updatetest"


jo="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"


#xAH_run.py --files ${input}--config ${jo} --submitDir ${subdir} --nevents 100 --isMC direct
xAH_run.py --files ${input_list} --config ${jo} --submitDir ${subdir_list} --nevents -1 --isMC direct

# --isMC option doesn't seem wholly necessary -->
# --> if not set, xAH::Algorithm will check eventInfo object to determine if data or mc
