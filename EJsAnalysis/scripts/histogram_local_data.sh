#!/bin/bash
# script for running data tree-to-histogram jobs on local ntuples


##### MAKE SURE RUNNING ORIGINAL XAH_RUN SCANDIR IMPLEMENTATION #####


jo="$EJ_PATH/EJsanalysis/config/EJsHistoConfig.py"
tree="EJsMiniNtup/nominal"
inpath="$EJ_PATH/../output/localOutput/latest/tree/"

input_18_363830="${inpath}data18_13TeV.00363830.*.root" ## single sample test
input_18_357451="${inpath}data18_13TeV.00357451.*.root"
input_18_350144="${inpath}data18_13TeV.00350144.*.root"
subdir_18_363830="hists.local.data18.363830"
subdir_18_357451="hists.local.data18.357451"
subdir_18_350144="hists.local.data18.350144"
xAH_run.py --files ${input_18_363830} --config ${jo} --submitDir ${subdir_18_363830} --nevents -1 --treeName ${tree} direct ##
xAH_run.py --files ${input_18_357451} --config ${jo} --submitDir ${subdir_18_357451} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_18_350144} --config ${jo} --submitDir ${subdir_18_350144} --nevents -1 --treeName ${tree} direct

input_17_340030="${inpath}data17_13TeV.00340030.*.root"
input_17_335022="${inpath}data17_13TeV.00335022.*.root"
input_17_331804="${inpath}data17_13TeV.00331804.*.root" ## single sample test
subdir_17_340030="hists.local.data17.340030"
subdir_17_335022="hists.local.data17.335022"
subdir_17_331804="hists.local.data17.331804"
xAH_run.py --files ${input_17_340030} --config ${jo} --submitDir ${subdir_17_340030} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_17_335022} --config ${jo} --submitDir ${subdir_17_335022} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_17_331804} --config ${jo} --submitDir ${subdir_17_331804} --nevents -1 --treeName ${tree} direct ##

input_16_309440="${inpath}data16_13TeV.00309440.*.root"
input_16_303208="${inpath}data16_13TeV.00303208.*.root" ## single sample test
input_16_301973="${inpath}data16_13TeV.00301973.*.root"
subdir_16_309440="hists.local.data16.309440"
subdir_16_303208="hists.local.data16.303208"
subdir_16_301973="hists.local.data16.301973"
xAH_run.py --files ${input_16_309440} --config ${jo} --submitDir ${subdir_16_309440} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_16_303208} --config ${jo} --submitDir ${subdir_16_303208} --nevents -1 --treeName ${tree} direct ##
xAH_run.py --files ${input_16_301973} --config ${jo} --submitDir ${subdir_16_301973} --nevents -1 --treeName ${tree} direct

input_15_283608="${inpath}data15_13TeV.00283608.*.root"
input_15_281411="${inpath}data15_13TeV.00281411.*.root"
input_15_280862="${inpath}data15_13TeV.00280862.*.root" ## single sample test
subdir_15_283608="hists.local.data15.283608"
subdir_15_281411="hists.local.data15.281411"
subdir_15_280862="hists.local.data15.280862"
xAH_run.py --files ${input_15_283608} --config ${jo} --submitDir ${subdir_15_283608} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_15_281411} --config ${jo} --submitDir ${subdir_15_281411} --nevents -1 --treeName ${tree} direct
xAH_run.py --files ${input_15_280862} --config ${jo} --submitDir ${subdir_15_280862} --nevents -1 --treeName ${tree} direct ##


## trigger study
inpath_trig="$EJ_PATH/../output/localOutput/latest-trigger/tree/"
input_17_340030_trig="${inpath_trig}data17_13TeV.00340030.*.root"
input_17_335022_trig="${inpath_trig}data17_13TeV.00335022.*.root"
input_17_331804_trig="${inpath_trig}data17_13TeV.00331804.*.root"
subdir_17_340030_trig="hists.local.data17.340030.trigger"
subdir_17_335022_trig="hists.local.data17.335022.trigger"
subdir_17_331804_trig="hists.local.data17.331804.trigger"
jo_trig="$EJ_PATH/EJsanalysis/config/EJsHistoConfig_trig.py"
#xAH_run.py --files ${input_17_340030_trig} --config ${jo_trig} --submitDir ${subdir_17_340030_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_17_335022_trig} --config ${jo_trig} --submitDir ${subdir_17_335022_trig} --nevents -1 --treeName ${tree} direct
#xAH_run.py --files ${input_17_331804_trig} --config ${jo_trig} --submitDir ${subdir_17_331804_trig} --nevents -1 --treeName ${tree} direct ##
