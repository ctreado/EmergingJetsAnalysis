import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()

Dict_EJsNtupleToHists = {
    "m_name"                      : "EJsHists",
    "m_msgLevel"                  : "info",
    "m_regionName"                : "all search valid", # must be all lowercase
    "m_detailStr"                 : "abcd pileup pv kinematics NLeadJets4",
    "m_jetBranchName"             : "jet",
    "m_otherJetBranchName"        : "pflowJet",
    "m_trackPartBranchName"       : "track",
    "m_secondaryVertexBranchName" : "secVtx",
}

c.algorithm ( "EJsNtupleToHists", Dict_EJsNtupleToHists )
