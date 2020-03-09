import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()

## --- metadata --- ##
metadataPath = "EJsAnalysis/"

Dict_EJsNtupleToHists = {
    "m_name"                      : "EJsHists",
    "m_msgLevel"                  : "info",
    "m_regionName"                : "search search-minus-one valid", # must all be lowercase
    "m_baseDVName"                : "bare",
    "m_detailStr"                 : "kinematics jetTruth jetTrks jetVerts dijets NLeadJets4",
    #"m_detailStr"                 : "vertices vtxTruth vtxErrors NVtxTrks3 abcd", # [pileup pv kinematics NLeadJets4 llps vtxTrks vtx2D NVtxTrks5]
    #"m_detailStr"                 : "vertices vtxTruth vtxTrks",
    "m_jetBranchName"             : "jet",
    "m_otherJetBranchName"        : "pflowJet",
    "m_truthJetBranchName"        : "truthJet",
    "m_truthDarkJetBranchName"    : "darkJet",
    "m_trackPartBranchName"       : "track",
    "m_secondaryVertexBranchName" : "secVtx",
    "m_truthVertexBranchName"     : "truthVtx",
    "m_metadataFileName"          : metadataPath + "mc16.metadata.txt"
}

c.algorithm ( "EJsNtupleToHists", Dict_EJsNtupleToHists )
