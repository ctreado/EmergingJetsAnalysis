#!/bin/bash
# script for submitting local jobs (mc)


## NOTE: to run over multiple files per sample, omit asterisk at end of input path and use hacked version of xAH_run.py -->
## --> replace 'ROOT.SH.scanDir(sh_all, sh_list, fname_base, os.path.basename(sample_dir))' with ...
## ... 'ROOT.SH.ScanDir().scan(sh_all, fname)'


## single sample test (mc16d)
input_08_d="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312008.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_1000_150_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/*"
input_16_d="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312016.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelA_600_2_4jetFilter.deriv.DAOD_EXOT23.e7941_s3126_r10739_p3719/*"
input_28_d="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312028.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelB_1000_5_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719/*"
input_43_d="$HOME/emerging_jets/datasets/montecarlo/MC16/MC16d/signal/DAOD/grid_official/exot23/mc16_13TeV.312043.Pythia8EvtGen_A14NNPDF23LO_EJ_ModelC_1000_300_4jetFilter.deriv.DAOD_EXOT23.e7941_s3126_r10739_p3719/*"
sub_08_d="local.trees.mc16d.312008"
sub_16_d="local.trees.mc16d.312016"
sub_28_d="local.trees.mc16d.312028"
sub_43_d="local.trees.mc16d.312043"

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
#tag="tmp_search-minus-one"
tag="tmp_rel-update_test"


## job steering -- single sample tests
#submitLocalEJsJobs.py --inFiles ${input_08_d} --jo ${jo_d} --subDir ${sub_08_d} --nevents 100 --isMC --move --delete --outTag ${tag}
submitLocalEJsJobs.py --inFiles ${input_16_d} --jo ${jo_d} --subDir ${sub_16_d} --nevents 100 --isMC --move --delete --outTag ${tag}
#submitLocalEJsJobs.py --inFiles ${input_28_d} --jo ${jo_d} --subDir ${sub_28_d} --nevents 100 --isMC --move --delete --outTag ${tag}
#submitLocalEJsJobs.py --inFiles ${input_43_d} --jo ${jo_d} --subDir ${sub_43_d} --nevents 100 --isMC --move --delete --outTag ${tag}

## job steering -- official signal samples
#submitLocalEJsJobs.py --inFiles ${input_d} --jo ${jo_d} --subDir ${sub_d} --nevents -1 --isMC --move --delete

# job steering -- pythia di-jet background
#submitLocalEJsJobs.py --inFiles ${input_bkgd_d} --jo ${jo_d} --subDir ${sub_bkgd_d} --nevents 100 --isMC --move --delete --outTag ${tag}
