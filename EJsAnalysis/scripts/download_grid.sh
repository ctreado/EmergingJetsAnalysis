#!/bin/bash
# script for getting analysis output from grid

# --> CHANGE ACCORDINGLY; CHANGE OUTPATH TO "LATEST"; REMOVE HOUR STRING FROM CONTAINER NAME
otag="TEST"
dtag="2019.12.31"
vtag="v0"

types="cutflow,hist-output,metadata,tree"
outpath="$EJ_PATH/../output/gridOutput/tmp_test/"

# --> ADD DATA18/7/6/5, MC16A/D/E (SUB0,SUB1)
## data
cont17="user.ctreado.data17_13TeV.*.EJsAna."${otag}"."${dtag}"_12h."${vtag}"*.root"

## mc16
contd0="user.ctreado.mc16_13TeV.3120*.*r10739*.EJsAna.sub0."${otag}"."${dtag}"_12h."${vtag}"*.root"

#downloadAndMerge.py --container ${cont17} --types ${types} --outPath ${outpath}
downloadAndMerge.py --container ${contd0} --types ${types} --outPath ${outpath}

## --> ADD SCRIPT TO CHANGE MC NAMES (TO INCLUDE MODEL INFO) --> CALL AFTER DOWNLOAD AND MERGE
## --> --> see B-L chargino code; can just be simple "if DSID = xxx", add corresponding signal point (or background type) to name...
## --> --> ...will need to split string, add relevant info, and put it back together --> can rename file with "os.rename(src,dest)"



