import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()

Dict_EJsNtupleToHists = {
    "m_name"                      : "EJsHists",
    "m_msgLevel"                  : "info",
    "m_detailStr"                 : "kinematic match vsMu jetEConstit jetTrkMom jetGhost NLeading4 NVtxTrk5",
    "m_regionName"                : "all signal valid ctrl",
    "m_jetBranchName"             : "jet",
    #"m_jetBranchName"             : "pflowJet",
    "m_truthJetBranchName"        : "truthJet",
    "m_truthDarkJetBranchName"    : "darkJet",
    "m_truthPartBranchName"       : "truthPart",
    "m_trackPartBranchName"       : "trackPart",
    "m_truthVertexBranchName"     : "truthVtx",
    "m_secondaryVertexBranchName" : "secVtx",
}

c.algorithm ( "EJsNtupleToHists", Dict_EJsNtupleToHists )


## TEST INFO SWITCHES
