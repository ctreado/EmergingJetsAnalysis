import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()


## --- algorithm configuration dictionaries --- ##

# basic event selection
Dict_BasicEventSelection = {
    "m_name"           : "BaseEvtSel",
    "m_msgLevel"       : "info",
    "m_useMetaData"    : False,
    "m_truthLevelOnly" : True,
}

# object matching
Dict_ObjectMatcher = {
    "m_name"           : "ObjectMatch",
    "m_msgLevel"       : "info",
    "m_truthLevelOnly" : True,
}

# analysis selection
Dict_EJsxAODAnalysis = {
    "m_name"               : "EJsAna",
    "m_msgLevel"           : "info",
    "m_inJetContainerName" : "AntiKt4TruthJets",
    "m_inJetBinName"       : "Truth",
    "m_applyRegionCuts"    : False,
    "m_truthLevelOnly"     : True,
}

# tree output
Dict_EJsMiniNtuple = {
    "m_name"                     : "EJsMiniNtup",
    "m_msgLevel"                 : "info",
    "m_evtDetailStr"             : "",
    "m_truthJetDetailStr"        : "kinematic rapidity energyLight constituent constituentAll match",
    "m_truthJetContainerName"    : "AntiKt4TruthJets AntiKt4TruthDarkJets",
    "m_truthJetBranchName"       : "truthJet darkJet",
    "m_truthPartDetailStr"       : "kinematic parents children",
    "m_truthPartContainerName"   : "TruthParticles",
    "m_truthPartBranchName"      : "truthPart",
    "m_truthVertexDetailStr"     : "isMatched",
    "m_truthVertexContainerName" : "TruthVertices",
    "m_truthVertexBranchName"    : "truthVtx",
    "m_truthLevelOnly"           : True,
}



## --- algorithms to run --- ##

# Basic Setup
c.algorithm ( "BasicEventSelection", Dict_BasicEventSelection )

# Object Matching
c.algorithm ( "ObjectMatcher",       Dict_ObjectMatcher       )

# EJs Analysis Selection
c.algorithm ( "EJsxAODAnalysis",     Dict_EJsxAODAnalysis     )

# EJs Ntuple
c.algorithm ( "EJsMiniNtuple",       Dict_EJsMiniNtuple       )
