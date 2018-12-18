#!/bin/bash
# script for getting analysis output from grid (mc)

container="user.ctreado.mc16_13TeV.310325.e6853_e5984_s3126_r10739_p3663.EJsAna.firsttest.*.root"
#container="user.ctreado.mc16_13TeV.3103*.e6853_e5984_s3126_r10739_p3663.EJsAna.firsttest.*.root"
types="cutflow,hist-output,metadata,tree"
outpath="./tmp_grid_download/"

#downloadAndMerge.py --container ${container} --types ${types} --outPath ${outpath}
downloadAndMerge.py --container ${container} --types ${types}
