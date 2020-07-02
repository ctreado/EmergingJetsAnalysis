#!/bin/bash
# script for getting analysis output from grid

# with new rucio setup, must be run in fresh shell (no analysis release) from directory containing "downloadAndMergeEJs.py"

# old dtag="2020-01-08" (or "2020-01-23" for one mc sample), vtag="v0"

dtag_d="2020-06-15" # update
vtag_d="v1"
dtag_s="2020-06-17"
vtag_s="v0"
dtag_b="2020-06-15" # update
vtag_b="v1"

types="tree"
outpath="$EJ_PATH/../output/gridOutput/v0_2020-06_mod/"
#outpath="/eos/atlas/user/c/ctreado/EmergingJets/analysis_ntuples/gridOutput/v0_2020-06_mod/"

## data
cont15="user.ctreado.data15_13TeV.*.EJsAna."${dtag_d}"."${vtag_d}"*.root"
cont16="user.ctreado.data16_13TeV.*.EJsAna."${dtag_d}"."${vtag_d}"*.root"
cont17="user.ctreado.data17_13TeV.*.EJsAna."${dtag_d}"."${vtag_d}"*.root"
cont18="user.ctreado.data18_13TeV.*.EJsAna."${dtag_d}"."${vtag_d}"*.root"

## mc16
# --> signal
conta36="user.ctreado.mc16_13TeV.3120*.*r10740*.EJsAna.sub36."${dtag_s}"."${vtag_s}"*.root"
contd36="user.ctreado.mc16_13TeV.3120*.*r10739*.EJsAna.sub36."${dtag_s}"."${vtag_s}"*.root" # change dtag_s for next 21 points
conte36="user.ctreado.mc16_13TeV.3120*.*r11265*.EJsAna.sub36."${dtag_s}"."${vtag_s}"*.root"
# --> background
contab="user.ctreado.mc16_13TeV.361024.*r10847*.EJsAna.bkgd."${dtag_b}"."${vtag_b}"*.root"
contdb="user.ctreado.mc16_13TeV.361024.*r10848*.EJsAna.bkgd."${dtag_b}"."${vtag_b}"*.root"


## to download subset of files
#python downloadAndMergeEJs.py --container ${cont15}  --types ${types} --outPath ${outpath} --nrandom 1
#python downloadAndMergeEJs.py --container ${cont16}  --types ${types} --outPath ${outpath} --nrandom 1
#python downloadAndMergeEJs.py --container ${cont17}  --types ${types} --outPath ${outpath} --nrandom 1 # --> downloads one from every period...
#python downloadAndMergeEJs.py --container ${cont18}  --types ${types} --outPath ${outpath} --nrandom 1
#python downloadAndMergeEJs.py --container ${conta36} --types ${types} --outPath ${outpath} --nrandom 1
python downloadAndMergeEJs.py --container ${contd36} --types ${types} --outPath ${outpath} --nrandom 1
#python downloadAndMergeEJs.py --container ${conte36} --types ${types} --outPath ${outpath} --nrandom 1
#python downloadAndMergeEJs.py --container ${contab}  --types ${types} --outPath ${outpath} --nrandom 3
#python downloadAndMergeEJs.py --container ${contdb}  --types ${types} --outPath ${outpath} --nrandom 3
# --> can't download full datasets locally (too large); instead use above modified script to download specified number of files per sample


## to download full datasets
#python downloadAndMergeEJs.py --container ${contd36} --types ${types} --outPath ${outpath}



