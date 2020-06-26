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

Dict_JetSelector_Truth = {
    "m_name"                    : "JetSelect_AntiKt4Truth",
    "m_msgLevel"                : "info",
    "m_useCutFlow"              : True,
    "m_inContainerName"         : "AntiKt4TruthJets",
    "m_outContainerName"        : "AntiKt4TruthJets_Select",
    "m_decorateSelectedObjects" : True,
    "m_createSelectedContainer" : True,
    "m_pass_min"                : 2,
    "m_pT_min"                  : 50e3,
    "m_eta_max"                 : 2.7,
}

Dict_TruthVertexSelector = {
    "m_name"                    : "TruthVtxSelect",
    "m_msgLevel"                : "info",
    "m_inContainerName"         : "TruthVertices",
    "m_outContainerName"        : "TruthVertices_Select",
    "m_decorateSelectedObjects" : True,
    "m_createSelectedContainer" : True,
    "m_truthLLP"                : "DarkPion Kshort",
    "m_r_max"                   : 563,
    "m_z_max"                   : 2720,
    "m_nVisOutP_min"            : 2,
}

# object matching
Dict_ObjectMatcher = {
    "m_name"                        : "ObjectMatch",
    "m_msgLevel"                    : "info",
    "m_inTruthJetContainerName"     : "AntiKt4TruthJets_Select",
    "m_inTruthDarkJetContainerName" : "AntiKt4TruthDarkJets",
    "m_inTruthPartContainerName"    : "TruthParticles",
    "m_inTruthVertexContainerName"  : "TruthVertices_Select",
    "m_jet_matchRadius"             : 0.3,
    "m_jet_vtx_matchRadius"         : 0.6,
    "m_jet_trk_matchRadius"         : 0.6,
    "m_truthLevelOnly"              : True,
}

# vertex matching
Dict_VertexMatcher = {
    "m_name"                       : "VtxMatch",
    "m_msgLevel"                   : "info",
    "m_inTruthPartContainerName"   : "TruthParticles",
    "m_inTruthVertexContainerName" : "TruthVertices_Select",
    "m_truthLLP"                   : "DarkPion Kshort",
    "m_filterTruthVertex_llp"      : True,
    "m_distanceCutoff"             : 10, 
    "m_setObjectIdentifiers"       : False, # already done in ObjectMatcher above...
    "m_vtx_matchScore"             : 0,     # off for now --> can apply score requirement later (i.e. in histo alg)...
    "m_truthLevelOnly"             : True,
}

# analysis selection
Dict_EJsxAODAnalysis = {
    "m_name"               : "EJsAna",
    "m_msgLevel"           : "info",
    "m_inJetContainerName" : "AntiKt4TruthJets_Select",
    "m_inJetBinName"       : "Truth",
    "m_cutflowJets"        : "Truth",
    "m_applyRegionCuts"    : False,
    "m_truthLevelOnly"     : True,
}

# tree output
Dict_EJsMiniNtuple = {
    "m_name"                     : "EJsMiniNtup",
    "m_msgLevel"                 : "info",
    "m_evtDetailStr"             : "",
    "m_truthJetDetailStr"        : "kinematic rapidity energyLight constituent constituentAll area truthJets truthVerts truthParts detail",
    "m_truthJetContainerName"    : "AntiKt4TruthJets_Select AntiKt4TruthDarkJets",
    "m_truthJetBranchName"       : "truthJet darkJet",
    "m_truthPartDetailStr"       : "kinematic parents children",
    "m_truthPartContainerName"   : "TruthParticles",
    "m_truthPartBranchName"      : "truthPart",
    "m_truthVertexDetailStr"     : "outPartDetail truthJetMatched recoMatching", # recoMatching needed for desc, physPos info
    "m_truthVertexContainerName" : "TruthVertices_Select",
    "m_truthVertexBranchName"    : "truthVtx",
    "m_truthLLP"                 : "DarkPion Kshort",
    "m_truthLevelOnly"           : True,
}



## --- algorithms to run --- ##

# Basic Setup
c.algorithm ( "BasicEventSelection", Dict_BasicEventSelection )

# Truth Jet Selection
c.algorithm ( "JetSelector",         Dict_JetSelector_Truth   )

# Truth Vertex Selection
c.algorithm ( "TruthVertexSelector", Dict_TruthVertexSelector )

# Object Matching
c.algorithm ( "ObjectMatcher",       Dict_ObjectMatcher       )

# Vertex Matching
c.algorithm ( "VertexMatcher",       Dict_VertexMatcher       )

# EJs Analysis Selection
c.algorithm ( "EJsxAODAnalysis",     Dict_EJsxAODAnalysis     )

# EJs Ntuple
c.algorithm ( "EJsMiniNtuple",       Dict_EJsMiniNtuple       )
