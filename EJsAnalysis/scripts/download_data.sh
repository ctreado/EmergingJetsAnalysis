#!/bin/bash
# script for getting analysis output from grid (data17)

#container="user.ctreado.data17_13TeV.00325713.r10260_r10658_p3578_p3664.EJsAna.firsttest.*.root"
container="user.ctreado.data17_13TeV.003*.r102*_r10658_p3578_p3664.EJsAna.firsttest.*.root"
types="cutflow,hist-output,metadata,tree"
outpath="./tmp_grid_download/"

#downloadAndMerge.py --container ${container} --types ${types} --outPath ${outpath}
downloadAndMerge.py --container ${container} --types ${types}
