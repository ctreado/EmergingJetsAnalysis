import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()


## --- systematics --- ##

systName = "All"     # do systematics
#systName = ""        # no systematics

systematicsValue = 1
systVal = 0
if systName != "":
    systVal = systematicsValue


## --- trigger lists --- ##

# signal triggers
fourJetTriggerList = [ "HLT_4j90",
                       "HLT_4j100",
                       "HLT_4j110",
                       "HLT_4j120",
                       "HLT_4j130",
                       "HLT_4j140",
                       "HLT_4j150" ]
# background triggers
singleJetTriggerList = [ "HLT_j15",
                         "HLT_j25",
                         "HLT_j35",
                         "HLT_j45",
                         "HLT_j55",
                         "HLT_j60",
                         "HLT_j85",
                         "HLT_j100",
                         "HLT_j110",
                         "HLT_j150",
                         "HLT_j175",
                         "HLT_j200",
                         "HLT_j260",
                         "HLT_j300",
                         "HLT_j320",
                         "HLT_j340",
                         "HLT_j360",
                         "HLT_j380",
                         "HLT_j400",
                         "HLT_j420",
                         "HLT_j440",
                         "HLT_j450",
                         "HLT_j460",
                         "HLT_j480",
                         "HLT_j500",
                         "HLT_j520" ]

fourJetTriggers   = ",".join( fourJetTriggerList )
singleJetTriggers = ",".join( singleJetTriggerList )
triggers          = ",".join( fourJetTriggerList + singleJetTriggerList )



## --- algorithm configuration dictionaries --- ##

# basic event selection
Dict_BasicEventSelection = {
    "m_name"                  : "BaseEvtSel",
    "m_msgLevel"              : "info",
    "m_applyGRLCut"           : False, # --> set to True once we have a GRL xml to work with
    "m_GRLxml"                : "",    # --> set
    "m_GRLExcludeList"        : "",    # --> may or may not need to set (probably not)
    "m_doPUreweighting"       : False, # --> set to True once we have lumicalc/prw files to work with
    "m_doPUreweightingSys"    : False, # --> do we want to turn this on when doing systematics ???
    "m_lumiCalcFileNames"     : "",    # --> set
    "m_PRWFileNames"          : "",    # --> set
    "m_applyPrimaryVertexCut" : True,
    "m_PVNTrack"              : 2,
    "m_applyEventCleaningCut" : True,
    "m_applyCoreFlagsCut"     : True,
    "m_triggerSelection"      : triggers,
    "m_applyTriggerCut"       : True,  # --> doesn't affect DAODs -- already trigger-skimmed
    "m_storeTrigDecisions"    : True,
    "m_storePassL1"           : True,  # --> do we need this ?? set to False ??
    "m_storePassHLT"          : True,  # --> do we need this ?? set to False ??
    "m_storeTrigKeys"         : True,  # --> do we need this ?? set to False ??
    "m_useMetaData"           : False, # --> for testing only; set to True before submitting jobs
}


# object calibration
Dict_JetCalibrator_EMTopo = {
    "m_name"                  : "JetCalib_AntiKt4EMTopo",
    "m_msgLevel"              : "info",  # --> use "verbose" for testing only; otherwise use "info"
    "m_inContainerName"       : "AntiKt4EMTopoJets",
    "m_outContainerName"      : "AntiKt4EMTopoJets_Calib",
    "m_jetAlgo"               : "AntiKt4EMTopo",
    "m_outputAlgo"            : "AntiKt4EMTopoJets_Calib_Algo",
    "m_writeSystToMetadata"   : True,       # --> True for testing only; set to False
    "m_calibConfigData"       : "JES_data2017_2016_2015_Consolidated_EMTopo_2018_Rel21.config",
    "m_calibConfigFullSim"    : "JES_data2017_2016_2015_Consolidated_EMTopo_2018_Rel21.config",
    "m_uncertConfig"          : "rel21/Fall2018/R4_CategoryReduction_FullJER.config", # --> randomly chosen for testing only; will (probably) need to change --> does nothing w/o systematics set (need to set "m_systName" to non-empty string to run systematics ("All" to run all available))
    "m_doCleaning"            : True,
    "m_jetCleanCutLevel"      : "LooseBad", # --> consider using '(Very)LooseBadLLP' ...
    "m_jetCleanUgly"          : False,
    "m_saveAllCleanDecisions" : True,       # --> do we care about this ?? set to False ??
    "m_redoJVT"               : True,       # --> do we care about this ?? set to False ??
    "m_calculatefJVT"         : True,       # --> do we care about this ?? set to False ??
    "m_systName"              : systName,
    "m_systVal"               : systVal,
}


# object selection
Dict_JetSelector_EMTopo = {
    "m_name"                    : "JetSelect_AntiKt4EMTopo",
    "m_msgLevel"                : "info",
    "m_inContainerName"         : "AntiKt4EMTopoJets_Calib",
    "m_outContainerName"        : "AntiKt4EMTopoJets_Calib_Select",
    "m_inputAlgo"               : "AntiKt4EMTopoJets_Calib_Algo",
    "m_outputAlgo"              : "AntiKt4EMTopoJets_Calib_Select_Algo",
    "m_writeSystToMetadata"     : True,  # --> True for testing only; set to False
    "m_decorateSelectedObjects" : True,  # --> do we want to cut or decorate ?? both ??
    "m_createSelectedContainer" : True,  # --> do we want to cut or decorate ?? both ??
    "m_cleanJets"               : True,
    "m_cleanEvent"              : False, # --> recommendation to kill events w/ any unclean jets
    "m_markCleanEvent"          : True,  # --> --> but do we want to cut here or just decorate ??
    "m_pT_min"                  : 50e3,  # --> CHECK
    "m_eta_max"                 : 2.7,   # --> CHECK
    "m_doJVF"                   : True,  # --> do we want to cut on this ?? if yes, use defaults ??
    "m_doJVT"                   : True,  # --> do we want to cut on this ?? if yes, use defaults ??
    "m_dofJVT"                  : True,  # --> do we want to cut on this ?? if yes, use defaults ??
    "m_SFFileJVT"               : "JetJvtEfficiency/Moriond2018/JvtSFFile_EMTopoJets.root",
    "m_SFFilefJVT"              : "JetJvtEfficiency/Moriond2018/fJvtSFFile.root",
    "m_singleJetTrigChains"     : "",    # --> DO WE WANT TO DO TRIGGER-JET MATCHING ??
    "m_diJetTrigChains"         : "",    # --> DO WE WANT TO DO TRIGGER-JET MATCHING ??
    "m_systNameJVT"             : systName,
    "m_systValJVT"              : systVal,
    "m_systNamefJVT"            : systName,
    "m_systValfJVT"             : systVal,
    "m_systName"                : systName,
    "m_systVal"                 : systVal,
}
    

# tree output
Dict_EJsMiniNtuple = {
    "m_name"             : "EJsMiniNtuple",
    "m_msgLevel"         : "info",
    "m_evtDetailStr"     : "pileup",
    "m_trigDetailStr"    : "basic passTriggers prescales",
    "m_jetDetailStr"     : "kinematic energyLight truth truth_details trackAll JVT allTrack allTrackDetail constituent charge",
    "m_jetContainerName" : "AntiKt4EMTopoJets AntiKt4EMTopoJets_Calib AntiKt4EMTopoJets_Calib_Select",
    "m_jetBranchName"    : "jet jetCalib jetCalibSelect",
}



## --- algorithms to run --- ##

# Basic Setup
c.algorithm ( "BasicEventSelection", Dict_BasicEventSelection )

# Jet Calibration
c.algorithm ( "JetCalibrator", Dict_JetCalibrator_EMTopo )

# Jet Selection
c.algorithm ( "JetSelector", Dict_JetSelector_EMTopo )

# EJs Ntuple
c.algorithm ( "EJsMiniNtuple", Dict_EJsMiniNtuple )
