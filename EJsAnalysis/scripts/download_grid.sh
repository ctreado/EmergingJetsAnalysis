#!/bin/bash
# script for getting analysis output from grid

## --> CHANGE ACCORDINGLY; CHANGE OUTPATH TO "LATEST"; REMOVE HOUR STRING FROM CONTAINER NAME
#otag="TEST"
#dtag="2019.12.31"
#vtag="v0"

#types="cutflow,hist-output,metadata,tree"
#outpath="$EJ_PATH/../output/gridOutput/tmp_test/"

## --> ADD DATA18/7/6/5, MC16A/D/E (SUB0,SUB1)
### data
#cont17="user.ctreado.data17_13TeV.*.EJsAna."${otag}"."${dtag}"_12h."${vtag}"*.root"

### mc16
#contd0="user.ctreado.mc16_13TeV.3120*.*r10739*.EJsAna.sub0."${otag}"."${dtag}"_12h."${vtag}"*.root"

##downloadAndMerge.py --container ${cont17} --types ${types} --outPath ${outpath}
#downloadAndMerge.py --container ${contd0} --types ${types} --outPath ${outpath}


dtag="2020-01"
vtag="v0"

types="tree"
outpath="$EJ_PATH/../output/gridOutput/v0_2020-01_n1/"

## data
cont15="user.ctreado.data15_13TeV.*.EJsAna."${dtag}"*."${vtag}"*.root"
cont16="user.ctreado.data16_13TeV.*.EJsAna."${dtag}"*."${vtag}"*.root"
cont17="user.ctreado.data17_13TeV.*.EJsAna."${dtag}"*."${vtag}"*.root"
cont18="user.ctreado.data18_13TeV.*.EJsAna."${dtag}"*."${vtag}"*.root"

## mc16
# --> signal
conta0="user.ctreado.mc16_13TeV.3120*.*r10740*.EJsAna.sub0."${dtag}"*."${vtag}"*.root"
contd0="user.ctreado.mc16_13TeV.312075*.*r10739*.EJsAna.sub0."${dtag}"*."${vtag}"*.root"
conte0="user.ctreado.mc16_13TeV.3120*.*r11265*.EJsAna.sub0."${dtag}"*."${vtag}"*.root"
# --> background
contab="user.ctreado.mc16_13TeV.361024.*r10847*.EJsAna.bkgd."${dtag}"*."${vtag}"*.root"
contdb="user.ctreado.mc16_13TeV.361024.*r10848*.EJsAna.bkgd."${dtag}"*."${vtag}"*.root"

#downloadAndMergeEJs.py --container ${cont15} --types ${types} --outPath ${outpath} --nrandom 1
#downloadAndMergeEJs.py --container ${cont16} --types ${types} --outPath ${outpath} --nrandom 1
#downloadAndMergeEJs.py --container ${cont17} --types ${types} --outPath ${outpath} --nrandom 1 # --> downloads one from every period...
#downloadAndMergeEJs.py --container ${cont18} --types ${types} --outPath ${outpath} --nrandom 1
#downloadAndMergeEJs.py --container ${conta0} --types ${types} --outPath ${outpath} --nrandom 1
downloadAndMergeEJs.py --container ${contd0} --types ${types} --outPath ${outpath} --nrandom 1
#downloadAndMergeEJs.py --container ${conte0} --types ${types} --outPath ${outpath} --nrandom 1
#downloadAndMergeEJs.py --container ${contab} --types ${types} --outPath ${outpath} --nrandom 3
#downloadAndMergeEJs.py --container ${contdb} --types ${types} --outPath ${outpath} --nrandom 3
# --> can't download full datasets locally (too large); instead use above modified script to download specified number of files per sample
# --> CHECK NRANDOM FOR DATA AND BKGD...



