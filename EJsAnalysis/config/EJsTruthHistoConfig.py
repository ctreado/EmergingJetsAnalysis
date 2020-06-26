import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()

Dict_EJsNtupleToHists = {
    "m_name"                      : "EJsHists",
    "m_msgLevel"                  : "info",
    "m_regionName"                : "all search-minus-one",
    "m_detailStr"                 : "llps llpDesc tjetVerts djetVerts tjetTrks djetTrks abcd",
    "m_truthJetBranchName"        : "truthJet",
    "m_truthDarkJetBranchName"    : "darkJet",
    "m_truthPartBranchName"       : "truthPart",
    "m_truthVertexBranchName"     : "truthVtx",
    "m_truthLevelOnly"            : True,
}

c.algorithm ( "EJsNtupleToHists", Dict_EJsNtupleToHists )
