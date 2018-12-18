import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()


#Dict_HistogramEJsTree = {
#    "m_name"     : "EJsHist",
#    "m_msgLevel" : "info" 
#    }

#c.algorithm ( "HistogramEJsTree", Dict_HistogramEJsTree )



Dict_EJsNtupleToHists = {
    "m_name"                      : "EJsHists",
    "m_msgLevel"                  : "info",
    "m_secondaryVertexBranchName" : "secVtx",
    #"m_secondaryVertexDetailStr"  : "tracks",
}

c.algorithm ( "EJsNtupleToHists", Dict_EJsNtupleToHists )
