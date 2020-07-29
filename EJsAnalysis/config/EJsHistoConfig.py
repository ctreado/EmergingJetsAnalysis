import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()

## --- metadata --- ##
metadataPath = "EJsAnalysis/"

Dict_EJsNtupleToHists = {
    "m_name"                      : "EJsHists",
    "m_msgLevel"                  : "info",
    "m_regionName"                : "search valid jz4w-slice-search jz4w-slice-validation", # must all be lowercase --> add search, jz4w-slice for jet studies; remove search(-minus-one) for data except for abcd
    "m_baseDVName"                : "clean",
    #"m_detailStr"                 : "kinematics jetCalo jetTrkMom jetTruth jetTrks jetVerts baseJetVerts dijets njets NLeadJets4 vertices vtxTruth vtxErrors vtxTrks vtxOverallTrk NVtxTrks5", # [pileup pv abcd]
    #"m_detailStr"                 : "jetTruth tightJets nsvJets comboJets baseJetVerts dijets njets NLeadJets4 abcd",
    #"m_detailStr"                  : "jetTruth tightJets nsvP4Jets nsvPtJets nsvHtJets nsvHJets nsvNtrkJets nsvNjtrkJets nsvTrkJets cutflow abcdcutOnly",
    #"m_detailStr"                 : "jetTruth tightJets comboJets jetVerts baseJetVerts cutflow",
    "m_detailStr"                  : "abcdcutOnly",
    #"m_detailStr"                 : "dijets njets nDVs abcdcutOnly",
    #"m_detailStr"                 : "vtxTruth vtxTrks vtxErrors vtxOverallTrk vtx2D cutflow", # vertices comboVerts
    #"m_detailStr"                 : "llps llpRecoEff",
    "m_jetBranchName"             : "jet",
    "m_truthJetBranchName"        : "truthJet",
    "m_truthDarkJetBranchName"    : "darkJet",
    "m_trackPartBranchName"       : "track",
    "m_truthPartBranchName"       : "truthPart",
    "m_secondaryVertexBranchName" : "secVtx",
    "m_truthVertexBranchName"     : "truthVtx",
    "m_metadataFileName"          : metadataPath + "mc16.metadata.txt"
}

c.algorithm ( "EJsNtupleToHists", Dict_EJsNtupleToHists )
