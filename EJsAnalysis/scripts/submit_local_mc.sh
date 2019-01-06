#!/bin/bash
# script for submitting local jobs (mc)

input="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310325.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/*"
input_list="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310325.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310328.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1000_150_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310340.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310346.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1000_5_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310355.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310359.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1000_75_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310365.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_600_20_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310377.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelD_600_300_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310394.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelE_600_75_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663/*"

#jo="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"
jo="$EJ_PATH/EJsAnalysis/config/EJsConfig_Basic.py"

subdir="local.MC16d.EJ_ModelA_1400_20"
subdir_list="local.MC16d"

xAH_run.py --files ${input} --config ${jo} --submitDir ${subdir} --nevents 10 --isMC direct
#xAH_run.py --files ${input_list} --config ${jo} --submitDir ${subdir_list} --nevents 10 --isMC direct

# --isMC option doesn't seem wholly necessary -->
# --> if not set, xAH::Algorithm will check eventInfo object to determine if data or mc
