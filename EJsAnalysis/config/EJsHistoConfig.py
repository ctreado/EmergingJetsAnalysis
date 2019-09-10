import ROOT
from xAODAnaHelpers import Config as xAH_config
import sys, os

c = xAH_config()

#Dict_EJsNtupleToHists = {
#    "m_name"                      : "EJsHists",
#    "m_msgLevel"                  : "info",
#    "m_detailStr"                 : "kinematic match vsMu jetEConstit jetTrkMom jetGhost NLeading4 NVtxTrk5",
#    "m_regionName"                : "all signal valid ctrl",
#    "m_jetBranchName"             : "jet",
#    #"m_jetBranchName"             : "pflowJet",
#    "m_truthJetBranchName"        : "truthJet",
#    "m_truthDarkJetBranchName"    : "darkJet",
#    "m_truthPartBranchName"       : "truthPart",
#    "m_trackPartBranchName"       : "trackPart",
#    "m_truthVertexBranchName"     : "truthVtx",
#    "m_secondaryVertexBranchName" : "secVtx",
#}

Dict_EJsNtupleToHists = {
    "m_name"                      : "EJsHists",
    "m_msgLevel"                  : "info",
    "m_regionName"                : "all signal valid",
    "m_detailStr"                 : "eventInfo pileup pv \
                                     jets jet_energy jet_constit jet_trkMoms jet_ghost match_jet_trk match_jet_vtx match_jet_truth \
                                     tjets tjet_energy tjet_constit match_tjet_tp match_tjet_tvtx match_tjet_truth \
                                     djets djet_constit match_djet_tp match_djet_tvtx match_djet_truth \
                                     tps tps_xd tps_qd tps_pid tps_rhod \
                                     verts tverts \
                                     kinematics NLeadJets4 NLeadTJets4 NLeadDJets4 NVtxTrks5",
    "m_jetStr"                    : "PFlow",
    "m_jetBranchName"             : "pflowJet",
    "m_truthJetBranchName"        : "truthJet",
    "m_truthDarkJetBranchName"    : "darkJet",
    "m_truthPartBranchName"       : "truthPart",
    "m_secondaryVertexBranchName" : "secVtx",
    "m_truthVertexBranchName"     : "truthVtx",
}

c.algorithm ( "EJsNtupleToHists", Dict_EJsNtupleToHists )


## TEST INFO SWITCHES
