#!/bin/bash
# script for submitting local jobs (mc)


##### OMIT ASTERISKS IN INPUT FILE PATHS WHEN RUNNING W/ HACKED XAH_RUN (TO RUN OVER MULTIPLE FILES PER SAMPLE) #####


## single sample tests -- old official
input_310328="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_oldofficial/exot23/mc16_13TeV.310328.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1000_150_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/"
subdir_310328="local.MC16d.oldoff.310328.EJ_ModelA_1000_150"
log_310328="log.MC16d.oldoff.310328.EJ_ModelA_1000_150.out"
input_310346="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_oldofficial/exot23/mc16_13TeV.310346.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1000_5_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/"
subdir_310346="local.MC16d.oldoff.310346.EJ_ModelB_1000_5"
log_310346="log.MC16d.oldoff.310346.EJ_ModelB_1000_5.out"

## single sample tests -- private update
input_312008_private="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312008.EJ_ModelA_1000_150_4TJF.update.25k.local.deriv.DAOD_EXOT23/"
subdir_312008_private="local.MC16d.private.312008.EJ_ModelA_1000_150"
log_312008="log.MC16d.private.312008.EJ_ModelA_1000_150.out"
input_312028_private="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312028.EJ_ModelB_1000_5_4TJF.update.25k.local.deriv.DAOD_EXOT23/"
subdir_312028_private="local.MC16d.private.312028.EJ_ModelB_1000_5"
log_312028="log.MC16d.private.312028.EJ_ModelB_1000_5.out"


## single sample tests -- official (update)
input_312004="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312004.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1400_20_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312004="local.MC16d.312004.EJ_ModelA_1400_20"
log_312004="log.MC16d.312004.EJ_ModelA_1400_20.out"

input_312008="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312008.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1000_150_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312008="local.MC16d.312008.EJ_ModelA_1000_150"
log_312008="log.MC16d.312008.EJ_ModelA_1000_150.out"

input_312017="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312017.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_600_1_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312017="local.MC16d.312017.EJ_ModelA_600_1"
log_312017="log.MC16d.312017.EJ_ModelA_600_1.out"

input_312022="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312022.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1400_20_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312022="local.MC16d.312022.EJ_ModelB_1400_20"
log_312022="log.MC16d.312022.EJ_ModelB_1400_20.out"

input_312028="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312028.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1000_5_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312028="local.MC16d.312028.EJ_ModelB_1000_5"
log_312028="log.MC16d.312028.EJ_ModelB_1000_5.out"

input_312031="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312031.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_600_300_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312031="local.MC16d.312031.EJ_ModelB_600_300"
log_312031="log.MC16d.312031.EJ_ModelB_600_300.out"

input_312039="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312039.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1400_75_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312039="local.MC16d.312039.EJ_ModelC_1400_75"
log_312039="log.MC16d.312039.EJ_ModelC_1400_75.out"

input_312046="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312046.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1000_5_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312046="local.MC16d.312046.EJ_ModelC_1000_5"
log_312046="log.MC16d.312046.EJ_ModelC_1000_5.out"

input_312052="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312052.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_600_2_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312052="local.MC16d.312052.EJ_ModelC_600_2"
log_312052="log.MC16d.312052.EJ_ModelC_600_2.out"

input_312060="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312060.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelD_1400_2_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312060="local.MC16d.312060.EJ_ModelD_1400_2"
log_312060="log.MC16d.312060.EJ_ModelD_1400_2.out"

input_312066="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312066.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelD_1000_1_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312066="local.MC16d.312066.EJ_ModelD_1000_1"
log_312066="log.MC16d.312066.EJ_ModelD_1000_5.out"

input_312067="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312067.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelD_600_300_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312067="local.MC16d.312067.EJ_ModelD_600_300"
log_312067="log.MC16d.312067.EJ_ModelD_600_300.out"

input_312075="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312075.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelE_1400_75_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312075="local.MC16d.312075.EJ_ModelE_1400_75"
log_312075="log.MC16d.312075.EJ_ModelE_1400_75.out"

input_312080="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312080.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelE_1000_150_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312080="local.MC16d.312080.EJ_ModelE_1000_150"
log_312080="log.MC16d.312080.EJ_ModelE_1000_150.out"

input_312090="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312090.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelE_600_0p5_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_312090="local.MC16d.312090.EJ_ModelE_600_0p5"
log_312090="log.MC16d.312090.EJ_ModelE_600_0p5.out"


## pythia di-jet background(s)
input_bkgd="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/background/DAOD/exot23/mc16_13TeV.361024.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ4W.deriv.DAOD_EXOT23.e3668_s3126_r10848_p3719/"
subdir_bkgd="local.MC16d.bkgd.jz4w"
log_bkgd="log.MC16d.bkgd.jz4w.out"


## comparing all old official mc16d signal samples
input_list_oldoff="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_oldofficial/exot23/mc16_13TeV.310325.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_oldofficial/exot23/mc16_13TeV.310328.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1000_150_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_oldofficial/exot23/mc16_13TeV.310340.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_oldofficial/exot23/mc16_13TeV.310346.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1000_5_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_oldofficial/exot23/mc16_13TeV.310355.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1400_20_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_oldofficial/exot23/mc16_13TeV.310359.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1000_75_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_oldofficial/exot23/mc16_13TeV.310365.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_600_20_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_oldofficial/exot23/mc16_13TeV.310377.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelD_600_300_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/* $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_oldofficial/exot23/mc16_13TeV.310394.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelE_600_75_4jetFilter.deriv.DAOD_EXOT23.e6853_s3126_r10739_p3663/*"
subdir_list_oldoff="local.MC16d.oldoff"
log_list_oldoff="log.MC16d.oldoff.out"


## comparing old vs new evgen private mc16d signal samples
input_list_update="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.310328.EJ_ModelA_1000_150_4TJF.update.25k.local.deriv.DAOD_EXOT23/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.310346.EJ_ModelB_1000_5_4TJF.update.25k.local.deriv.DAOD_EXOT23/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312008.EJ_ModelA_1000_150_4TJF.update.25k.local.deriv.DAOD_EXOT23/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312028.EJ_ModelB_1000_5_4TJF.update.25k.local.deriv.DAOD_EXOT23/"
subdir_list_update="local.MC16d.updatetest"
log_list_update="log.MC16d.updatetest.out"


## comparing private mc16d signal samples w/ new evgen
input_list_private="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312008.EJ_ModelA_1000_150_4TJF.update.25k.local.deriv.DAOD_EXOT23/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_test_update/exot23/MC16.312028.EJ_ModelB_1000_5_4TJF.update.25k.local.deriv.DAOD_EXOT23/"
subdir_list_private="local.MC16d.private"
log_list_private="log.MC16d.private.out"


## official mc16d signal samples (updated)
input_list="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312004.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1400_20_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312008.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1000_150_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312017.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_600_1_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312022.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1400_20_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312028.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1000_5_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312031.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_600_300_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312039.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1400_75_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312046.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1000_5_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312052.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_600_2_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312060.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelD_1400_2_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312066.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelD_1000_1_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312067.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelD_600_300_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312075.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelE_1400_75_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312080.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelE_1000_150_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/ $HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312090.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelE_600_0p5_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/"
subdir_list="local.MC16d"
log_list="log.MC16d.out"



## config files
jo_a="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16a.py"
jo_d="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16d.py"
jo_e="$EJ_PATH/EJsAnalysis/config/EJsConfig_mc16e.py"

jo_test="$EJ_PATH/EJsAnalysis/config/EJsConfig.py"



## job steering -- old / private samples
#xAH_run.py --files ${input_310328} --config ${jo_d} --submitDir ${subdir_310328} --nevents 100 --isMC direct | tee ${log_310328}
#xAH_run.py --files ${input_310346} --config ${jo_d} --submitDir ${subdir_310346} --nevents 100 --isMC direct | tee ${log_310346}
#xAH_run.py --files ${input_312008_private} --config ${jo_d} --submitDir ${subdir_312008_private} --nevents 100 --isMC direct | tee ${log_312008_private}
#xAH_run.py --files ${input_312028_private} --config ${jo_d} --submitDir ${subdir_312028_private} --nevents 100 --isMC direct | tee ${log_312028_private}

#xAH_run.py --files ${input_list_oldoff}  --config ${jo_d} --submitDir ${subdir_list_oldoff}  --nevents 1000 --isMC direct | tee ${log_list_oldoff}
#xAH_run.py --files ${input_list_update}  --config ${jo_d} --submitDir ${subdir_list_update}  --nevents 1000 --isMC direct | tee ${log_list_update}
#xAH_run.py --files ${input_list_private} --config ${jo_d} --submitDir ${subdir_list_private} --nevents 1000 --isMC direct | tee ${log_list_private}


## job steering -- official signal
#xAH_run.py --files ${input_312004} --config ${jo_d} --submitDir ${subdir_312004} --nevents 100 --isMC direct | tee ${log_312004}
xAH_run.py --files ${input_312008} --config ${jo_d} --submitDir ${subdir_312008} --nevents -1 --isMC direct | tee ${log_312008}
#xAH_run.py --files ${input_312017} --config ${jo_d} --submitDir ${subdir_312017} --nevents 100 --isMC direct | tee ${log_312017}
#xAH_run.py --files ${input_312022} --config ${jo_d} --submitDir ${subdir_312022} --nevents 100 --isMC direct | tee ${log_312022}
#xAH_run.py --files ${input_312028} --config ${jo_d} --submitDir ${subdir_312028} --nevents 100 --isMC direct | tee ${log_312028}
#xAH_run.py --files ${input_312031} --config ${jo_d} --submitDir ${subdir_312031} --nevents 100 --isMC direct | tee ${log_312031}
#xAH_run.py --files ${input_312039} --config ${jo_d} --submitDir ${subdir_312039} --nevents 100 --isMC direct | tee ${log_312039}
#xAH_run.py --files ${input_312046} --config ${jo_d} --submitDir ${subdir_312046} --nevents 100 --isMC direct | tee ${log_312056}
#xAH_run.py --files ${input_312052} --config ${jo_d} --submitDir ${subdir_312052} --nevents 100 --isMC direct | tee ${log_312052}
#xAH_run.py --files ${input_312060} --config ${jo_d} --submitDir ${subdir_312060} --nevents 100 --isMC direct | tee ${log_312060}
#xAH_run.py --files ${input_312066} --config ${jo_d} --submitDir ${subdir_312066} --nevents 100 --isMC direct | tee ${log_312066}
#xAH_run.py --files ${input_312067} --config ${jo_d} --submitDir ${subdir_312067} --nevents 100 --isMC direct | tee ${log_312067}
#xAH_run.py --files ${input_312075} --config ${jo_d} --submitDir ${subdir_312075} --nevents 100 --isMC direct | tee ${log_312075}
#xAH_run.py --files ${input_312080} --config ${jo_d} --submitDir ${subdir_312080} --nevents 100 --isMC direct | tee ${log_312080}
#xAH_run.py --files ${input_312090} --config ${jo_d} --submitDir ${subdir_312090} --nevents 100 --isMC direct | tee ${log_312090}

#xAH_run.py --files ${input_list} --config ${jo_d} --submitDir ${subdir_list} --nevents -1 --isMC direct | tee ${log_list}


## job steering -- background
#xAH_run.py --files ${input_bkgd} --config ${jo_d} --submitDir ${subdir_bkgd} --nevents -1 --isMC direct | tee ${log_bkgd}


## job steering with valgrind -- memory checks --> DOES NOT SEEM TO WORK ON CERNVM -- TEST ON LXPLUS
#valgrind --leak-check=yes --trace-children=yes --num-callers=25 --show-reachable=yes --track-origins=yes --smc-check=all `which python` xAH_run.py --files ${input_312008} --config ${jo_d} --submitDir ${subdir_312008} --nevents 10 --isMC direct | tee valgrind.log.mc.312008.out


# --isMC option doesn't seem wholly necessary -->
# --> if not set, xAH::Algorithm will check eventInfo object to determine if data or mc
