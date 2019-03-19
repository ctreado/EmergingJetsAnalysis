import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()


## --- systematics --- ##

systName = ""        # no systematics
#systName = "All"     # do systematics

systVal = 0
systematicsValue = 1
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
    "m_uncertConfig"          : "rel21/Fall2018/R4_GlobalReduction_FullJER.config", # --> randomly chosen for testing only; will (probably) need to change --> does nothing w/o systematics set (need to set "m_systName" to non-empty string to run systematics ("All" to run all available))
    "m_doCleaning"            : True,
    "m_jetCleanCutLevel"      : "LooseBad", # --> consider using '(Very)LooseBadLLP' ...
    "m_jetCleanUgly"          : False,
    "m_saveAllCleanDecisions" : True,       # --> do we care about this ?? set to False ??
    "m_redoJVT"               : True,       # --> do we care about this ?? set to False ??
    "m_calculatefJVT"         : True,       # --> do we care about this ?? set to False ??
    "m_systName"              : systName,
    "m_systVal"               : systVal,
}

Dict_JetCalibrator_PFlow = {
    "m_name"                  : "JetCalib_AntiKt4EMPFlow",
    "m_msgLevel"              : "info",
    "m_inContainerName"       : "AntiKt4EMPFlowJets",
    "m_outContainerName"      : "AntiKt4EMPFlowJets_Calib",
    "m_jetAlgo"               : "AntiKt4EMPFlow",
    "m_outputAlgo"            : "AntiKt4EMPFlowJets_Calib_Algo",
    "m_writeSystToMetadata"   : True,
    "m_calibConfigData"       : "JES_data2017_2016_2015_Consolidated_PFlow_2018_Rel21.config",
    "m_calibConfigFullSim"    : "JES_data2017_2016_2015_Consolidated_PFlow_2018_Rel21.config",
    "m_uncertConfig"          : "rel21/Fall2018/R4_GlobalReduction_FullJER.config",
    "m_doCleaning"            : True,
    "m_jetCleanCutLevel"      : "LooseBad",
    "m_jetCleanUgly"          : False,
    "m_saveAllCleanDecisions" : True,
    "m_redoJVT"               : True,
    "m_calculatefJVT"         : True,
    "m_systName"              : systName,
    "m_systVal"               : systVal,
}


# object selection
Dict_JetSelector_EMTopo = { # require two jets ??
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
    "m_doJVF"                   : False, # --> do we want to cut on this ?? if yes, use defaults ??
    "m_doJVT"                   : True,  # --> check JVT ... use defaults ??
    "m_noJVTVeto"               : True,  # --> save JVT decision, but don't reject jet
    "m_SFFileJVT"               : "JetJvtEfficiency/Moriond2018/JvtSFFile_EMTopoJets.root",
    "m_systNameJVT"             : "",    # --> do we need/want to do JVT systematics ??
    "m_systValJVT"              : 0,     # --> --> ??
    "m_dofJVT"                  : True,  # --> check fJVT ... use defaults ??
    "m_dofJVTVeto"              : False, # --> save fJVT decision, but don't reject jet
    "m_SFFilefJVT"              : "JetJvtEfficiency/Moriond2018/fJvtSFFile.root",
    "m_systNamefJVT"            : "",    # --> do we need/want to do fJVT systematics ??
    "m_systValfJVT"             : 0,     # --> --> ??
    "m_singleJetTrigChains"     : "",    # --> DO WE WANT TO DO TRIGGER-JET MATCHING ??
    "m_diJetTrigChains"         : "",    # --> DO WE WANT TO DO TRIGGER-JET MATCHING ??
}

Dict_JetSelector_PFlow = {
    "m_name"                    : "JetSelect_AntiKt4EMPFlow",
    "m_msgLevel"                : "info",
    "m_inContainerName"         : "AntiKt4EMPFlowJets_Calib",
    "m_outContainerName"        : "AntiKt4EMPFlowJets_Calib_Select",
    "m_inputAlgo"               : "AntiKt4EMPFlowJets_Calib_Algo",
    "m_outputAlgo"              : "AntiKt4EMPFlowJets_Calib_Select_Algo",
    "m_writeSystToMetadata"     : True,
    "m_decorateSelectedObjects" : True,
    "m_createSelectedContainer" : True,
    "m_cleanJets"               : True,
    "m_cleanEvent"              : False,
    "m_markCleanEvent"          : True,
    "m_pT_min"                  : 50e3,
    "m_eta_max"                 : 2.7,
    "m_doJVF"                   : False,
    "m_doJVT"                   : True,
    "m_noJVTVeto"               : True,
    "m_SFFileJVT"               : "JetJvtEfficiency/Moriond2018/JvtSFFile_EMTopoJets.root",
    "m_systNameJVT"             : "",
    "m_systValJVT"              : 0,
    "m_dofJVT"                  : True,
    "m_dofJVTVeto"              : False,
    "m_SFFilefJVT"              : "JetJvtEfficiency/Moriond2018/fJvtSFFile.root",
    "m_systNamefJVT"            : "",
    "m_systValfJVT"             : 0,
    "m_singleJetTrigChains"     : "",
    "m_diJetTrigChains"         : "",
}

# track selector ...

# truth particle selector ...

# secondary vertex selector ...
Dict_SecondaryVertexSelector = {
    "m_name"     : "SecVtxSel",
    "m_msgLevel" : "info",
}


# object matching
Dict_ObjectMatcher = {
    "m_name"                           : "ObjectMatch",
    "m_msgLevel"                       : "info",
    "m_inJetContainerName"             : "AntiKt4EMTopoJets_Calib_Select AntiKt4EMPFlowJets_Calib_Select",
    "m_inTrackPartContainerName"       : "InDetTrackParticles",                 # --> use selected tracks
    "m_inSecondaryVertexContainerName" : "VrtSecInclusive_SecondaryVertices",   # --> use selected vertices
    "m_inputAlgo"                      : "AntiKt4EMTopoJets_Calib_Select_Algo",
    "m_jetSystsContainerIndex"         : 0,
}


# analysis selection
Dict_EJsxAODAnalysis = {
    "m_name"                   : "EJsAna",
    "m_msgLevel"               : "info",
    "m_inJetContainerName"     : "AntiKt4EMTopoJets_Calib_Select AntiKt4EMPFlowJets_Calib_Select",
    "m_inJetBinName"           : "EMTopo PFlow",
    "m_inputAlgo"              : "AntiKt4EMTopoJets_Calib_Select_Algo",
    "m_outputAlgo"             : "AntiKt4EMTopoJets_Calib_Select_EJsxAODAna_Algo",
    "m_jetSystsContainerIndex" : 0,
    "m_signalTrigList"         : fourJetTriggers,
    "m_validTrigList"          : singleJetTriggers,
    #"m_ctrlTrigList"           : singleJetTriggers, # --> change ...
}
    

# tree output
Dict_EJsMiniNtuple = {
    "m_name"                         : "EJsMiniNtup",
    "m_msgLevel"                     : "info",
    "m_evtDetailStr"                 : "pileup",
    "m_trigDetailStr"                : "basic passTriggers prescales",
    "m_jetDetailStr"                 : "kinematic rapidity clean energy truth trackAll JVT allTrack allTrackDetail constituent charge ghost match",
    "m_jetContainerName"             : "AntiKt4EMTopoJets_Calib_Select AntiKt4EMPFlowJets_Calib_Select",
    "m_jetBranchName"                : "jet pflowJet",
    "m_jetSystsVec"                  : "AntiKt4EMTopoJets_Calib_Select_Algo",
    "m_jetSystsContainerIndex"       : 0,
    "m_truthJetDetailStr"            : "kinematic rapidity energyLight constituent constituentAll match emtopo pflow",
    "m_truthJetContainerName"        : "AntiKt4TruthJets AntiKt4TruthDarkJets",
    "m_truthJetBranchName"           : "truthJet darkJet",
    "m_truthPartDetailStr"           : "kinematic parents children",
    "m_truthPartContainerName"       : "TruthParticles",                    # --> use selected truth particles
    "m_truthPartBranchName"          : "truthPart",
    "m_trackPartDetailStr"           : "kinematic numbers vertex",
    "m_trackPartContainerName"       : "InDetTrackParticles",               # --> use selected tracks
    "m_trackPartBranchName"          : "track",
    "m_truthVertexDetailStr"         : "isMatched emtopo pflow",
    "m_truthVertexContainerName"     : "TruthVertices",
    "m_truthVertexBranchName"        : "truthVtx",
    "m_secondaryVertexDetailStr"     : "tracks truth jetMatched emtopo pflow",
    "m_secondaryVertexContainerName" : "VrtSecInclusive_SecondaryVertices", # --> use selected DVs
    "m_secondaryVertexBranchName"    : "secVtx",
}
# --> "truth_details" in jet-detail-string causes issue when running over data ("nonexistent aux data item `::GhostPartons'") --> need to add "isMC" check in JetContainer --> leave out for now (probably don't need anyway, and can always add manually in EJsHelpTreeBase, if necessary --> consider contacting xAODAnaHelpers experts about issue, though (not sure if I can develop myself)



## --- algorithms to run --- ##

# Basic Setup
c.algorithm ( "BasicEventSelection",     Dict_BasicEventSelection     )

# Jet Calibration
c.algorithm ( "JetCalibrator",           Dict_JetCalibrator_EMTopo    )
c.algorithm ( "JetCalibrator",           Dict_JetCalibrator_PFlow     )

# Jet Selection
c.algorithm ( "JetSelector",             Dict_JetSelector_EMTopo      )
c.algorithm ( "JetSelector",             Dict_JetSelector_PFlow       )
# Secondary Vertex Selection
c.algorithm ( "SecondaryVertexSelector", Dict_SecondaryVertexSelector )


# Object Matching
c.algorithm ( "ObjectMatcher",           Dict_ObjectMatcher           )

# EJs Analysis Selection
c.algorithm ( "EJsxAODAnalysis",         Dict_EJsxAODAnalysis         )

# EJs Ntuple
c.algorithm ( "EJsMiniNtuple",           Dict_EJsMiniNtuple           )
