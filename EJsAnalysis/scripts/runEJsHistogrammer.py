#!/usr/bin/env python

####################################################################
# runEJsHistogrammer.py                                            #
####################################################################
# code for running EJsNtupleToHists jobs over many trees locally   #
# or on the grid -- based on scripts from BMinusLChargino analysis #
# ##################################################################
# Colleen Treado                                                   #
####################################################################

import os, sys, glob, subprocess, time, shutil
import argparse
import ROOT # --> figure out how to get this running outside of athena

### command line arguments ###
parser = argparse.ArgumentParser( description= "histogramming options", formatter_class = argparse.ArgumentDefaultsHelpFormatter )

# xAH run-related arguments
# --> will eventually want to change default directories to "gridOutput" (and remove "latest" from path)
parser.add_argument( "--inDir", dest = "inDir", default = os.getenv('EJ_PATH') + "/../output/localOutput/latest/tree/",
                         help = "Input directory containing ntuples to run over." )
parser.add_argument( "--inTags", dest = "inTags", default = "", help = "Comma separated list of tags for choosing input files." )
parser.add_argument( "--outTag", dest = "outTag", default = "", help = "Output tag for histogram root files." )
parser.add_argument( "--jo", dest = "jo", default = os.getenv('EJ_PATH') + "/EJsAnalysis/config/EJsHistoConfig.py",
                         help = "Job configuration file." )
parser.add_argument( "--subDir", dest = "subDir", default = "local.histos", help = "Histogram output submission directory." )
parser.add_argument( "--nevents", dest = "nevents", default = "-1", help = "Number of events to run over per file." )
parser.add_argument( "--driver", dest = "driver", default = "direct", help = "Driver to use to run the code." )
parser.add_argument( "--treeDir", dest = "treeDir", default = "EJsMiniNtup", help = "ROOT file sub-directory containing TTrees." )
parser.add_argument( "--treeList", dest = "treeList", default = "", help = "Comma separated list of TTrees to process. \
                         If none specified, all trees in file (sub-directory) will be processed." )
parser.add_argument( "--doDuplicates", dest = "doDuplicates", action = "store_true", default = False,
                         help = "Run over duplicates ntuples (if in same directory as regular ntuples)." )
# general job running arguments
parser.add_argument( "--outDir", dest = "outDir", default = os.getenv('EJ_PATH') + "/../output/localOutput/latest/",
                         help = "Parent output directory where histograms and logs will finally be stored." )
parser.add_argument( "--ncores", dest = "ncores", default = 8, type = int, help = "Number of parallel jobs" )
parser.add_argument( "--mergeDatasets", dest = "mergeDatasets", action = "store_true", default = False,
                         help = "Merge nominal and systematics histograms into single file for given sample." )
parser.add_argument( "--renameAndMove", dest = "renameAndMove", action = "store_true", default = False,
                         help = "Rename and move histograms into common output directory." )
parser.add_argument( "--forceMove", dest = "forceMove", action = "store_true", default = False,
                         help = "Force move and overwrite existing files in output directories." )

args = parser.parse_args()


def main():

    # get all files in input directory
    inFiles = glob.glob( os.path.join( args.inDir, "*" ) )
    print inFiles

    # select files matching input tag(s)
    tags = args.inTags.split(',')
    files = []
    for inFile in inFiles:
        tagMatch = True
        for tag in tags:
            if not tag in inFile.split("/")[-1]:
                tagMatch = False
        if not args.doDuplicates:
            if "duplicates" in inFile:
                tagMatch = False
        if tagMatch:
            files.append( inFile )

    outTag = get_outTag()
        
    # create initial output log directory
    logDir = get_logDir()
    if not os.path.exists( logDir ):
        os.makedirs( logDir )

    # get list of trees to process
    treeList = []
    if len( args.treeList ) > 0:
        treeList = list( args.treeList.split(",") )
    print "tree list (search) = ", treeList
    trees = []
    treeDir = "EJsMiniNtup"
    f = ROOT.TFile( files[0], "READ" )
    d = f.GetDirectory( treeDir )
    for key in d.GetListOfKeys():
        kobj = key.ReadObj()
        if ( isinstance( kobj, ROOT.TTree ) ):
            if len( treeList ) == 0:         # process all trees
                if not kobj.GetName() in trees:
                    trees.append( kobj.GetName() )
            elif kobj.GetName() in treeList: # only process trees in list
                if not kobj.GetName() in trees:
                    trees.append( kobj.GetName() )
    if len( trees ) == 0:
        print "No trees found! Exiting"
        return
    print "tree list (found) = ", trees

    # set final output histogram name
    inDir = args.inDir
    if inDir.endswith("/"):
        inDir = inDir[:-1]
    outHistName = "hist-" + inDir.split("/")[-1] + ".root"
        
    ### submit xAH_run histogram jobs ###
    processes, logFiles = [], []
    emptyFiles = []
    # loop over selected files
    for file in files:
        # not sure why we need this?
        if len( processes ) >= args.ncores:
            wait_completion( processes, logFiles )
        
        # create output submission directories for histogram files 
        file_tag = os.path.basename(file)[:-5] + outTag
        subDir = os.path.join( args.subDir, file_tag )
        if not os.path.exists( subDir ):
            os.makedirs( subDir )
        # set log file names
        logFile = os.path.join( logDir, "EJsNtupleToHists_{0}".format(file_tag) + ".log" )

        # loop over selected trees
        for tree in trees:
            if len( processes ) >= args.ncores:
                wait_completion( processes, logFiles )
                
            command = "xAH_run.py -f"
            command += " --files "     + file
            command += " --config "    + args.jo
            command += " --submitDir " + os.path.join( subDir, tree )
            command += " --nevents "   + args.nevents
            command += " --treeName "  + os.path.join( treeDir, tree )
            command += " "             + args.driver
            command += " | tee "       + logFile # need this when running os.system(command) --> remove when Popen call fixed
            print(command)

            # check tree in file
            f = ROOT.TFile( file, "READ" )
            d = f.GetDirectory( treeDir )
            if not tree in d.GetListOfKeys():
                emptyFiles.append( file )
                continue

            os.system( command ) # temporary...try to get below to work (efficiently); will probably want to use once running over more, larger files --> meanwhile, consider changing submit script back to using os.system( command ) (seems faster; checks)
            #process_result = submit_local_job( command, logFile ) # --> CAUSING ALL SORTS OF PROBLEMS; FIX !!! also seems really slow...
            #processes.append( process_result[0])
            #logFiles.append( process_result[1])

    ## wait for jobs to finish and close log files
    #wait_all( processes, logFiles )
    #for f in logFiles:
    #    f.close()

    # hadd files so nominal and systematics in same file for given sample
    if args.mergeDatasets:
        mergeDatasets( files, emptyFiles, trees, outHistName )

    # collect and move output to final destination
    if args.renameAndMove:
        renameAndMove( outHistName )


def submit_local_job( exec_seq, logfile ):
    log_out = open( logfile, 'w' )
    proc = subprocess.Popen( exec_seq, shell = True, stderr = log_out, stdout = log_out )
    time.sleep( 0.5 ) # wait to prevent opening / closing of several files
    return proc, log_out


def wait_completion( pids, logs ):
    print "'Wait for completion of one of launched jobs'"
    while True:
        for pid in pids:
            if pid.poll() is not None:
                print "\nProcess", pid.pid, "has completed"
                logs.pop( pids.index(pid) ).close() # remove log file from list and close it
                pids.remove( pid )
                return
        print ".",
        sys.stdout.flush()
        time.sleep( 3 ) # wait before retrying

        
def wait_all( pids, logs ):
    print "'Wait for completion of all launched jobs'"
    while len( pids ) > 0:
        wait_completion( pids, logs )
    print "All jobs finished!"


def get_outTag():
    outTag = args.outTag
    if outTag:
        outTag = "_" + outTag
    return outTag

def get_logDir():
    logDir = args.subDir
    if logDir.endswith("/"):
        logDir = logDir[:-1]
    logDir += ".logs"
    return logDir


# THIS IS NOT WORKING FOR BIG JOBS --> SEEMINGLY DELETING TREES BEFORE HADD FINISHES ?? --> TURN OFF FOR NOW AND FIX !!!
def mergeDatasets( files, emptyFiles, trees, outHistName ):
    # check that hadd exists
    devnull = open( os.devnull )
    try:
        subprocess.call( ["hadd"], stdout = devnull, stderr = devnull )
    except OSError as e:
        print "Error: hadd not available. Exiting. Re-run without 'mergeDatasets' option."
        exit(1)

    for file in files:
        if file in emptyFiles:
            continue
        outTag = get_outTag()
        file_tag = os.path.basename(file)[:-5] + outTag
        subDir = os.path.join( args.subDir, file_tag )
        outHistFile = os.path.join( subDir, outHistName )
        inHistFiles = os.path.join( subDir, "*/" + outHistName )
        os.system( "hadd " + outHistFile + " " + inHistFiles )
        for tree in trees:
            shutil.rmtree( os.path.join( subDir, tree ) )


def renameAndMove( outHistName ):
    histOutDir = os.path.join( args.outDir, "EJsNtupToHistOutput" )
    if not os.path.exists( histOutDir ):
        os.makedirs( histOutDir )
    print "Moving files to", histOutDir
    histDirs = glob.glob( os.path.join( args.subDir, "*" ) )
    # output histograms named "hist-[tree_dir].root" by default; rename and move
    for histDir in histDirs:
        print histDir, outHistName
        if outHistName in os.listdir( histDir ):
            histFile = os.path.join( histDir, outHistName )
            renamedHistFile = os.path.join( histOutDir, "hist-" + os.path.basename( histDir ) + ".root" )
            if not os.path.exists( renamedHistFile ) or args.forceMove:
                print "Moving", histFile, "to", renamedHistFile
                shutil.move( histFile, renamedHistFile )
                print "Deleting", histDir
                shutil.rmtree( histDir )
            else:
                print "Destination path", histFile, "already exists. Not moving or deleting. Either re-run with --forceMove, choose a different outDir, and/or rm -rf it yourself."
        ## RUNS IF DATASETS NOT MERGED --> ONLY USE THIS WHEN MAKING NOMINAL HISTOS ONLY (otherwise other trees will be deleted)
        elif outHistName in os.listdir( os.path.join( histDir, "nominal" ) ):
            nomHistDir = os.path.join( histDir, "nominal" )
            histFile = os.path.join( nomHistDir, outHistName )
            renamedHistFile = os.path.join( histOutDir, "hist-" + os.path.basename( histDir ) + ".root" )
            if not os.path.exists( renamedHistFile ) or args.forceMove:
                print "Moving", histFile, "to", renamedHistFile
                shutil.move( histFile, renamedHistFile )
                print "Deleting", histDir
                shutil.rmtree( histDir )
            else:
                print "Destination path", histFile, "already exists. Not moving or deleting. Either re-run with --forceMove, choose a different outDir, and/or rm -rf it yourself."
            
    # delete empty initial directory
    if not len( os.listdir( args.subDir ) ):
        shutil.rmtree( args.subDir )

    logTag = time.strftime("%Y.%m.%d_%Hh%Mm%Ss", time.localtime())
    if args.outTag:
        logTag = args.outTag + "_" + logTag
    logOutDir = os.path.join( args.outDir, "logs/hist_" + logTag )
    if not os.path.exists( logOutDir ):
        os.makedirs( logOutDir )
    print "Moving log files to", logOutDir
    log_files = os.listdir( get_logDir() )
    for lf in log_files:
        logFile = os.path.join( get_logDir(), lf )
        movedLogFile = os.path.join( logOutDir, lf )
        if not os.path.exists( movedLogFile ) or args.forceMove:
            print "Moving", logFile, "to", movedLogFile
            shutil.move( logFile, movedLogFile )
        else:
            print "Destination path", logFile, "already exists. Not moving or deleting. Either re-run with --forceMove, choose a different outDir, and/or rm -rf it yourself."
    # delete empty initial log directory
    if not len( os.listdir( get_logDir() ) ):
        shutil.rmtree( get_logDir() )


if __name__ == "__main__":
    main()
