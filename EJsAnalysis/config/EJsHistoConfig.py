import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()

## --- metadata --- ##
metadataPath = "EJsAnalysis/"

Dict_EJsNtupleToHists = {
    "m_name"                      : "EJsHists",
    "m_msgLevel"                  : "info",
    "m_regionName"                : "search valid", # must all be lowercase [search-minus-one]
    "m_baseDVName"                : "bare",
    #"m_detailStr"                 : "kinematics jetCalo jetTrkMom jetTruth jetTrks jetVerts baseJetVerts dijets njets NLeadJets4 vertices vtxTruth vtxErrors vtxTrks vtxOverallTrk NVtxTrks5", # [pileup pv abcd]
    "m_detailStr"                 : "jetTruth NLeadJets4 baseVerts abcd",
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
