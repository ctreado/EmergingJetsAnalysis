#!/bin/bash
# script for submitting local jobs (mc)


##### OMIT ASTERISKS IN INPUT FILE PATHS WHEN RUNNING W/ HACKED XAH_RUN (TO RUN OVER MULTIPLE FILES PER SAMPLE) #####


## single sample test
input_310328="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310328.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1000_150_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/"
subdir_310328="local.MC16d.oldoff.310328.EJ_ModelA_1000_150"

input_310346="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310346.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1000_5_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/"
subdir_310346="local.MC16d.oldoff.310346.EJ_ModelB_1000_5"

input_312008="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312008.EJ_ModelA_1000_150_4TJF.update.25k.local.deriv.DAOD_EXOT23/"
subdir_312008="local.MC16d.private.312008.EJ_ModelA_1000_150"

input_312028="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312028.EJ_ModelB_1000_5_4TJF.update.25k.local.deriv.DAOD_EXOT23/"
subdir_312028="local.MC16d.private.312028.EJ_ModelB_1000_5"


## pythia di-jet backgrounds
input_bkgd="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/background/DAOD/exot23/mc16_13TeV.361024.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ4W.deriv.e3668_s3126_r10848_r10706_p3719/"
subdir_bkgd="local.MC16d.bkgd.jz4w"


## comparing all old official mc16d samples
input_list_oldoff="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310325.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310328.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1000_150_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310340.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310346.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1000_5_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310355.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310359.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1000_75_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310365.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_600_20_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310377.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelD_600_300_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.310394.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelE_600_75_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/*"
subdir_list_oldoff="local.MC16d.oldoff"


## comparing old vs new evgen private mc16d samples
input_list_update="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.310328.EJ_ModelA_1000_150_4TJF.update.25k.local.deriv.DAOD_EXOT23/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.310346.EJ_ModelB_1000_5_4TJF.update.25k.local.deriv.DAOD_EXOT23/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312008.EJ_ModelA_1000_150_4TJF.update.25k.local.deriv.DAOD_EXOT23/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312028.EJ_ModelB_1000_5_4TJF.update.25k.local.deriv.DAOD_EXOT23/"
subdir_list_update="local.MC16d.updatetest"


## comparing private mc16d samples w/ new evgen
input_list_private="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312008.EJ_ModelA_1000_150_4TJF.update.25k.local.deriv.DAOD_EXOT23/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312028.EJ_ModelB_1000_5_4TJF.update.25k.local.deriv.DAOD_EXOT23/"
subdir_list_private="local.MC16d.private"



## config files
jo_a="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16a.py"
jo_d="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16d.py"
jo_e="$EJ_PATH/EJsAnalysis/config/EJsConfig_data_mc16e.py"

jo_test="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"


## job steering
#xAH_run.py --files ${input_310328} --config ${jo_d} --submitDir ${subdir_310328} --nevents 100 --isMC direct
#xAH_run.py --files ${input_310346} --config ${jo_d} --submitDir ${subdir_310346} --nevents 100 --isMC direct
#xAH_run.py --files ${input_312008} --config ${jo_d} --submitDir ${subdir_312008} --nevents 100 --isMC direct
#xAH_run.py --files ${input_312028} --config ${jo_d} --submitDir ${subdir_312028} --nevents 100 --isMC direct

xAH_run.py --files ${input_bkgd} --config ${jo_test} --submitDir ${subdir_bkgd} --nevents -1 --isMC direct

#xAH_run.py --files ${input_list_oldoff}  --config ${jo_d} --submitDir ${subdir_list_oldoff}  --nevents 5000 --isMC direct
#xAH_run.py --files ${input_list_update}  --config ${jo_d} --submitDir ${subdir_list_update}  --nevents 5000 --isMC direct
#xAH_run.py --files ${input_list_private} --config ${jo_d} --submitDir ${subdir_list_private} --nevents 5000 --isMC direct


# --isMC option doesn't seem wholly necessary -->
# --> if not set, xAH::Algorithm will check eventInfo object to determine if data or mc
