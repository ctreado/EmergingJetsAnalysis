#!/usr/bin/env python

################################################
# submitLocalEJsJobs.py                        #
################################################
# code for submitting local EJsMiniNtuple jobs #
################################################
# Colleen Treado                               #
################################################

import os, sys, glob, shutil
import argparse


### command line arguments ###
parser = argparse.ArgumentParser( description = "local job submission options",
                                       formatter_class = argparse.ArgumentDefaultsHelpFormatter )

# xAH_run-related arguments
parser.add_argument( "--inFiles", dest = "inFiles",
                         default = os.getenv('EJ_PATH') + "/EJsAnalysis/scripts/sample_lists/local.samples.mc16d.ejs.txt", 
                         help = "Input files to run over. If passing text files containing lists of file names, \
                         make sure to enable '--txtInput' option or pass file with a .txt extension. \
                         File lists passed here need to be enclosed in quotes (i.e. '--inFiles \"File1 File2\"')" )
parser.add_argument( "--jo", dest = "jo", default = os.getenv('EJ_PATH') + "/EJsAnalysis/config/EJsConfig_mc16d.py",
                         help = "Job configuration file." )
parser.add_argument( "--subDir", dest = "subDir", default = "local.MC16d", help = "Output submission directory." )
parser.add_argument( "--nevents", dest = "nevents", default = "-1", help = "Number of events to run over per file." )
parser.add_argument( "--isMC", dest = "isMC", action = "store_true", default = False, help = "Running over MC sample(s)." )
parser.add_argument( "--driver", dest = "driver", default = "direct", help = "Driver to use to run the code." )
parser.add_argument( "--log", dest = "log", default = "log.MC16d.out", help = "Output log file." )
parser.add_argument( "--txtInput", dest = "txtInput", action = "store_true", default = False,
                         help = "Run over list of files in input text file" )
# arguments to move files to another output directory
parser.add_argument( "--outDir", dest = "outDir", default = os.getenv('EJ_PATH') + "/../output/localOutput/",
                         help = "Output directory into which final trees are moved." )
parser.add_argument( "--outTag", dest = "outTag", default = "latest",
                         help = "Output directory tag to differentiate b/w ntuple versions (i.e. 'latest', 'trigger')" )
parser.add_argument( "--doMove", dest = "doMove", action = "store_true", default = False,
                         help = "Move final trees into output directory." )
parser.add_argument( "--moveTypes", dest = "moveTypes", default = "tree,cutflow,duplicates,metadata,hist-output",
                         help = "Comma separated list of types of datasets to move and save \
                         (i.e. 'tree', 'cutflow', 'duplicates', 'metadata', 'hist-output')." )
parser.add_argument( "--forceMove", dest = "forceMove", action = "store_true", default = False,
                         help = "Force move and overwrite existing files in output directories." )
parser.add_argument( "--delete", dest = "deleteSubDir", action = "store_true", default = False,
                         help = "Delete initial submission directory after moving output files of interest." )

args = parser.parse_args()


def main():
    # read input file list(s)
    inFiles = ""
    files = args.inFiles.split()
    for file in files:
        if args.txtInput or ".txt" in file:
            with open( file, 'r' ) as f:
                for line in f:
                    if line.startswith('#') : continue
                    if not line.strip()     : continue
                    line = line.strip()
                    inFiles += " " + line
        else:
            inFiles += " " + file

    # submit xAH_run job
    command = "xAH_run.py"
    command += " --files "     + inFiles
    command += " --config "    + args.jo
    command += " --submitDir " + args.subDir
    command += " --nevents "   + args.nevents
    if args.isMC:
        command += " --isMC"
    command += " "             + args.driver
    command += " | tee "       + args.log
    
    print(command)
    os.system(command)

    # move output trees
    if args.doMove:
      moveOutFiles()


def moveOutFiles():
    outDir = os.path.join( args.outDir, args.outTag )
    datasetTypes = args.moveTypes.split(',')
    subdir = args.subDir

    # prepare general output directory
    if not os.path.exists( outDir ):
      os.makedirs( outDir ) 

    # prepare specific output directories for dataset types + grab datasets to move
    for type in datasetTypes:
        directory = type + "/"
        out_directory = os.path.join( outDir, directory )
        if not os.path.exists( out_directory ):
            os.makedirs( out_directory )
        if "tree" in type:
            subdir_type = os.path.join( subdir, "data-tree/" )
        elif "cutflow" in type:
            subdir_type = os.path.join( subdir, "data-cutflow/" )
        elif "duplicates" in type:
            subdir_type = os.path.join( subdir, "data-duplicates_tree/" )
        elif "metadata" in type:
            subdir_type = os.path.join( subdir, "data-metadata/" )
        elif "hist" in type:
            subdir_type = os.path.join( subdir, "hist-" )
        # move datasets to output directories and delete submitDir
        files = glob.glob(subdir_type + "*")
        for file in files:
            file_split = file.split("/")
            print file_split[-1]
            out_file = os.path.join( out_directory, file_split[-1] )
            if not os.path.exists( out_file ) or args.forceMove:
                print "Moving " + file + " to " + out_directory
                shutil.move( file, out_file )
            else:
                print "Destination path " + out_file + "already exists. Either re-run with --forceMove, choose a different --outDir and/or --outTag, or rm -rf it yourself."
                return
    if ( args.deleteSubDir ):
        print "Deleting " + subdir
        shutil.rmtree( subdir )

    
if __name__ == "__main__":
  main()
