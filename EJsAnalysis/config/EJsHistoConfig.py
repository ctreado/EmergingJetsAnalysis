import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()

Dict_EJsNtupleToHists = {
    "m_name"                      : "EJsHists",
    "m_msgLevel"                  : "info",
    "m_regionName"                : "search-minus-one valid", # [search] --> must all be lowercase
    "m_detailStr"                 : "vertices vtxTruth NVtxTrks5 vtxTrks abcd", # [llps pileup pv kinematics NLeadJets4 abcd]
    "m_jetBranchName"             : "jet",
    "m_otherJetBranchName"        : "pflowJet",
    "m_trackPartBranchName"       : "track",
    "m_secondaryVertexBranchName" : "secVtx",
    "m_truthVertexBranchName"     : "truthVtx",
}

c.algorithm ( "EJsNtupleToHists", Dict_EJsNtupleToHists )
