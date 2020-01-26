#!/usr/bin/env python

###############################################
# submitGridEJsJobs.py                        #
###############################################
# code for submitting grid EJsMiniNtuple jobs #
###############################################
# Colleen Treado                              #
###############################################

import os, sys, glob, subprocess, time, shutil
import argparse


### command line arguments ###
parser = argparse.ArgumentParser( description = "grid job submission options",
                                       formatter_class = argparse.ArgumentDefaultsHelpFormatter )
# xAH_run-related arguments
parser.add_argument( "--vtag", dest = "vtag", default = "v0", help = "Version tag." )
parser.add_argument( "--inFiles", dest = "inFiles",
                         default = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/sample_lists/samples.mc16d.ejs_sub0.txt", 
                         help = "Text file of input files to run over." )
parser.add_argument( "--jo", dest = "jo", default = os.getenv('EJ_PATH') + "/EJsAnalysis/config/EJsConfig_mc16d.py",
                         help = "Job configuration file." )
parser.add_argument( "--subDir", dest = "subDir", default = "grid.MC16d.EJs.sub0", help = "Output submission directory." )
parser.add_argument( "--nFiles", dest = "nFiles", default = "-1", help = "Number of input files to run over." )
parser.add_argument( "--outName", dest = "outName", default = "", help = "Output directory name." )
parser.add_argument( "--isMC", dest = "isMC", action = "store_true", default = False, help = "Running over MC sample(s)." )
parser.add_argument( "--driver", dest = "driver", default = "prun", help = "Driver to use to run the code." )


args = parser.parse_args()


def main():
    tag = time.strftime("%Y-%m-%d", time.localtime())
    if args.vtag:
        tag = tag + "." + args.vtag

    outName = "user.%nickname%.%in:name[1]%.%in:name[2]%.%in:name[6]%.EJsAna."
    if args.outName:
        outName += args.outName + "."
    outName += tag
    
    # submit xAH_run job
    command  = "xAH_run.py"
    command += " --files "                   + args.inFiles
    command += " --config "                  + args.jo
    command += " --inputList --inputRucio"
    command += " --submitDir "               + args.subDir + "." + tag
    if args.isMC:
        command += " --isMC"
    command += " "                           + args.driver
    command += " --optGridMergeOutput=1"
    command += " --optGridNFiles="           + args.nFiles
    command += " --optGridOutputSampleName " + outName
    
    print(command)
    os.system( command )


if __name__ == "__main__":
  main()
