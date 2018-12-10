## super basic config file for testing purposes ##

import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()



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
    "m_GRLxml"                : "",
    "m_applyGRLCut"           : False, # --> True when GRLxml set
    "m_PRWFileNames"          : "",
    "m_lumiCalcFileNames"     : "",
    "m_doPUreweighting"       : False, # --> True when *FileNames set
    "m_triggerSelection"      : triggers,
    "m_applyTriggerCut"       : False, # True ??
    "m_storeTrigDecisions"    : True, 
    "m_storePassL1"           : True,
    "m_storePassHLT"          : True,
    "m_storeTrigKeys"         : True,
    "m_applyEventCleaningCut" : True,
    "m_applyCoreFlagsCut"     : True,
    "m_applyPrimaryVertexCut" : False, # True ??
    "m_useMetaData"           : False, # True ??
}
  
# output
Dict_EJsMiniNtuple = {
    "m_name"                          : "EJsMiniNtuple",
    "m_msgLevel"                      : "info",
    #"m_evtDetailStr"                 : "pileup",
    #"m_trigDetailStr"                : "basic passTriggers",
    #"m_jetContainerName"             : "AntiKt4EMTopoJets",
    #"m_jetBranchName"                : "jet",
    #"m_jetDetailStr"                 : "kinematic trigger energy scales trackAll allTrack "
    #                                    "allTrackDetail constituent constituentAll truth",
    #"m_trigJetContainerName"         : "HLT_xAOD__JetContainer_a4tcemsubjesFS",
    #"m_trigJetBranchName"            : "trigJet",
    #"m_trigJetDetailStr"             : "kinematic",
    #"m_truthJetContainerName"        : "AntiKt4TruthJets AntiKt4TruthDarkJets",
    #"m_truthJetBranchName"           : "truthJet truthDarkJet",
    #"m_truthJetDetailStr"            : "kinematic constituent constituentAll",
    #"m_truthPartContainerName"       : "TruthParticles",
    #"m_truthPartBranchName"          : "truthPart",
    #"m_truthPartDetailStr"           : "kinematic parents children",
    "m_trackPartContainerName"       : "InDetTrackParticles",
    "m_trackPartBranchName"          : "tracks",
    "m_trackPartDetailStr"           : "kinematic numbers vertex",
    "m_truthVertexContainerName"     : "TruthVertices",
    "m_truthVertexBranchName"        : "truthVtx",
    "m_secondaryVertexContainerName" : "VrtSecInclusive_SecondaryVertices",
    "m_secondaryVertexBranchName"    : "secVtx",
    "m_systsVec"                     : "" # empty string = nominal case
}

## will need to manually add truth-jet width, track chi2,d0,numberDoF


    
## --- algorithms --- ##

# Basic Setup
c.algorithm ( "BasicEventSelection", Dict_BasicEventSelection )

# EJs Ntuple
c.algorithm ( "EJsMiniNtuple", Dict_EJsMiniNtuple )
