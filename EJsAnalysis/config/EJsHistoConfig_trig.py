import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()

Dict_EJsNtupleToHists = {
    "m_name"                      : "EJsHists",
    "m_msgLevel"                  : "info",
    "m_regionName"                : "all",      # --> don't want to implement signal trigger yet
    "m_detailStr"                 : "trigTest", # --> study trigger efficiencies
    "m_jetBranchName"             : "jet",
    "m_otherJetBranchName"        : "pflowJet",
    "m_secondaryVertexBranchName" : "secVtx",
    "m_doTruthJets"               : False,
    "m_doTruthDarkJets"           : False,
    "m_doTracks"                  : False,
    "m_doTruthParts"              : False,
    "m_unblind"                   : False,
}

c.algorithm ( "EJsNtupleToHists", Dict_EJsNtupleToHists )
