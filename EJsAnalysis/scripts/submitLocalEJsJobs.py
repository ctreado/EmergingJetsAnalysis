#!/usr/bin/env python

################################################
# submitLocalEJsJobs.py                        #
################################################
# code for submitting local EJsMiniNtuple jobs #
################################################
# Colleen Treado                               #
################################################

import os, sys, glob, subprocess, time, shutil
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
parser.add_argument( "--subDir", dest = "subDir", default = "local.trees", help = "Output submission directory." )
parser.add_argument( "--nevents", dest = "nevents", default = "-1", help = "Number of events to run over per file." )
parser.add_argument( "--isMC", dest = "isMC", action = "store_true", default = False, help = "Running over MC sample(s)." )
parser.add_argument( "--driver", dest = "driver", default = "direct", help = "Driver to use to run the code." )
parser.add_argument( "--txtInput", dest = "txtInput", action = "store_true", default = False,
                         help = "Run over list of files in input text file" )
# arguments to move files to another output directory
parser.add_argument( "--outDir", dest = "outDir", default = os.getenv('EJ_PATH') + "/../output/localOutput/",
                         help = "Output directory into which final trees are moved." )
parser.add_argument( "--outTag", dest = "outTag", default = "latest",
                         help = "Output directory tag to differentiate b/w ntuple versions (i.e. 'latest', 'trigger')." )
parser.add_argument( "--move", dest = "move", action = "store_true", default = False,
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
    # set log file name
    log = "EJsMiniNtuple_{0}".format(args.subDir) + ".log"

    # submit xAH_run job
    command = "xAH_run.py"
    command += " --files "     + inFiles
    command += " --config "    + args.jo
    command += " --submitDir " + args.subDir
    command += " --nevents "   + args.nevents
    if args.isMC:
        command += " --isMC"
    command += " "             + args.driver
    command += " | tee "       + log # need this when running os.system(command) --> remove when Popen call fixed
    
    print(command)
    os.system( command )
    #process_result = submit_local_job( command, log )

    ## wait for job to finish and close log file
    #wait( process_result[0], process_result[1] )
    #process_result[1].close()

    # move output trees and log
    if args.move:
      moveOutFiles( log )


def submit_local_job( exec_seq, logfile ):
    log_out = open( logfile, 'w' )
    proc = subprocess.Popen( exec_seq, shell = True, stderr = log_out, stdout = log_out )
    time.sleep( 0.5 ) # wait to prevent opening / closing of several files
    return proc, log_out


def wait( pid, logfile ):
    print "'Wait for completion of launched job'"
    while True:
        if pid.poll() is not None:
            print "\nProcess", pid.pid, "has completed"
            logfile.close()
            return
        print ".",
        sys.stdout.flush()
        time.sleep(3) # wait before retrying

        
def moveOutFiles( logfile ):
    outDir = os.path.join( args.outDir, args.outTag )
    datasetTypes = args.moveTypes.split(',')
    subdir = args.subDir

    # prepare general output directory
    if not os.path.exists( outDir ):
      os.makedirs( outDir )

    # create output log directory and move log file there
    outLogDir = os.path.join( outDir, "logs/ntup_" + time.strftime("%Y.%m.%d_%Hh%Mm%Ss", time.localtime()) )
    if not os.path.exists( outLogDir ):
        os.makedirs( outLogDir )
    out_logFile = os.path.join( outLogDir, logfile )
    if not os.path.exists( out_logFile ) or args.forceMove:
        print "Moving " + logfile + " to " + outLogDir
        shutil.move( logfile, out_logFile )

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
        successfulMove = True
        files = glob.glob(subdir_type + "*")
        for file in files:
            file_split = file.split("/")
            print file_split[-1]
            out_file = os.path.join( out_directory, file_split[-1] )
            if not os.path.exists( out_file ) or args.forceMove:
                print "Moving " + file + " to " + out_directory
                shutil.move( file, out_file )
            else:
                print "Destination path " + out_file + " already exists. Not moving or deleting. Either re-run with --forceMove, choose a different outDir and/or rm -rf it yourself."
                successfulMove = False
                return
    # delete initial submission directory (assuming files successfully moved)
    if ( args.deleteSubDir and successfulMove ):
        print "Deleting " + subdir
        shutil.rmtree( subdir )

    
if __name__ == "__main__":
  main()
