#include <TLorentzVector.h>

#include "EJsAnalysis/JetContainer.h"
#include "EJsAnalysis/EJsHelperFunctions.h"
#include "EJsAnalysis/VsiBonsaiTool.h"

using namespace EJs;

JetContainer :: JetContainer ( const std::string& name, const std::string& detailStr, float units,
			       bool mc, bool emtopo, bool pflow ) :
  VertexContainer ( name, detailStr, units, mc )
{
  m_doEMTopo = emtopo;
  m_doPFlow  = pflow;
  
  if ( m_debug ) Info( "EJs::JetContainer()", "setting up" );

  if ( name.find("dark")  != std::string::npos || name.find("Dark")  != std::string::npos )
    jet_type = DARK;
  else if ( name.find("truth") != std::string::npos || name.find("Truth") != std::string::npos )
    jet_type = TRUTH;
  else
    jet_type = RECO;

  m_ID     = new std::vector<int>;
  m_M      = new std::vector<float>;
  m_radius = new std::vector<float>;

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    if ( jet_type == RECO ) {
      m_isTruthMatched      = new std::vector<uint8_t>;
      m_truthMatch_ID       = new std::vector<int>;
      m_truthMatch_dR       = new std::vector<float>;
      m_truthMatch_E        = new std::vector<float>;
      m_truthMatch_M        = new std::vector<float>;
      m_truthMatch_pt       = new std::vector<float>;
      m_truthMatch_eta      = new std::vector<float>;
      m_truthMatch_phi      = new std::vector<float>;
      m_truthMatch_rapidity = new std::vector<float>;
      m_truthNonmatch_IDs   = new std::vector<std::vector<int>>;
      m_truthNonmatch_dRs   = new std::vector<std::vector<float>>;
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      m_isDarkMatched       = new std::vector<uint8_t>;
      m_darkMatch_ID        = new std::vector<int>;
      m_darkMatch_dR        = new std::vector<float>;
      m_darkMatch_E         = new std::vector<float>;
      m_darkMatch_M         = new std::vector<float>;
      m_darkMatch_pt        = new std::vector<float>;
      m_darkMatch_eta       = new std::vector<float>;
      m_darkMatch_phi       = new std::vector<float>;
      m_darkMatch_rapidity  = new std::vector<float>;
      m_darkNonmatch_IDs    = new std::vector<std::vector<int>>;
      m_darkNonmatch_dRs    = new std::vector<std::vector<float>>;
    }
    if ( jet_type == DARK ) {
      m_isMatchedToTruth    = new std::vector<uint8_t>;
      m_matchedTruthID      = new std::vector<int>;
      m_matchedTruthDR      = new std::vector<float>;
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	m_isMatchedToEMTopo = new std::vector<uint8_t>;
	m_matchedEMTopoID   = new std::vector<int>;
	m_matchedEMTopoDR   = new std::vector<float>;
      }
      if ( m_doPFlow ) {
	m_isMatchedToPFlow  = new std::vector<uint8_t>;
	m_matchedPFlowID    = new std::vector<int>;
	m_matchedPFlowDR    = new std::vector<float>;
      }
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    m_secVtxCount                                        = new std::vector<int>;
    m_secVtxPt                                           = new std::vector<float>;
    m_secVtx_ID                                          = new std::vector<std::vector<int>>;
    m_secVtx_x                                           = new std::vector<std::vector<float>>;
    m_secVtx_y                                           = new std::vector<std::vector<float>>;
    m_secVtx_z                                           = new std::vector<std::vector<float>>;
    m_secVtx_r                                           = new std::vector<std::vector<float>>;
    m_secVtx_pt                                          = new std::vector<std::vector<float>>;
    m_secVtx_eta                                         = new std::vector<std::vector<float>>;
    m_secVtx_phi                                         = new std::vector<std::vector<float>>;
    m_secVtx_mass                                        = new std::vector<std::vector<float>>;
    m_secVtx_chi2                                        = new std::vector<std::vector<float>>;
    m_secVtx_ntrk                                        = new std::vector<std::vector<int>>;
    m_secVtx_dR                                          = new std::vector<std::vector<float>>;
    if ( m_mc ) {
      m_secVtx_closestTruth_isDarkPionDecay              = new std::vector<std::vector<uint8_t>>;
      m_secVtx_closestTruth_isOffdiagDarkPionDecay       = new std::vector<std::vector<uint8_t>>;
      m_secVtx_closestTruth_ID                           = new std::vector<std::vector<int>>;
      m_secVtx_closestTruth_barcode                      = new std::vector<std::vector<int>>;
      m_secVtx_closestTruth_distance                     = new std::vector<std::vector<float>>;
      m_secVtx_maxlinkTruth_isDarkPionDecay              = new std::vector<std::vector<uint8_t>>;
      m_secVtx_maxlinkTruth_isOffdiagDarkPionDecay       = new std::vector<std::vector<uint8_t>>;
      m_secVtx_maxlinkTruth_ID                           = new std::vector<std::vector<int>>;
      m_secVtx_maxlinkTruth_barcode                      = new std::vector<std::vector<int>>;
      m_secVtx_maxlinkTruth_score                        = new std::vector<std::vector<float>>;
      m_secVtx_maxlinkParentTruth_isDarkPionDecay        = new std::vector<std::vector<uint8_t>>;
      m_secVtx_maxlinkParentTruth_isOffdiagDarkPionDecay = new std::vector<std::vector<uint8_t>>;
      m_secVtx_maxlinkParentTruth_ID                     = new std::vector<std::vector<int>>;
      m_secVtx_maxlinkParentTruth_barcode                = new std::vector<std::vector<int>>;
      m_secVtx_maxlinkParentTruth_score                  = new std::vector<std::vector<float>>;
      m_truthVtxCount                                    = new std::vector<int>;
      m_truthVtxPt                                       = new std::vector<float>;
      m_truthVtx_isDarkPionDecay                         = new std::vector<std::vector<uint8_t>>;
      m_truthVtx_isOffdiagDarkPionDecay                  = new std::vector<std::vector<uint8_t>>;
      m_truthVtx_ID                                      = new std::vector<std::vector<int>>;
      m_truthVtx_x                                       = new std::vector<std::vector<float>>;
      m_truthVtx_y                                       = new std::vector<std::vector<float>>;
      m_truthVtx_z                                       = new std::vector<std::vector<float>>;
      m_truthVtx_r                                       = new std::vector<std::vector<float>>;
      m_truthVtx_pt                                      = new std::vector<std::vector<float>>;
      m_truthVtx_eta                                     = new std::vector<std::vector<float>>;
      m_truthVtx_phi                                     = new std::vector<std::vector<float>>;
      m_truthVtx_mass                                    = new std::vector<std::vector<float>>;
      m_truthVtx_nOutP                                   = new std::vector<std::vector<int>>;
      m_truthVtx_barcode                                 = new std::vector<std::vector<int>>;
      m_truthVtx_dR                                      = new std::vector<std::vector<float>>;
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    m_trkCount               = new std::vector<int>;
    m_trkPt                  = new std::vector<float>;
    m_trk_ID                 = new std::vector<std::vector<int>>;
    m_trk_qOverP             = new std::vector<std::vector<float>>;
    m_trk_E                  = new std::vector<std::vector<float>>;
    m_trk_M                  = new std::vector<std::vector<float>>;
    m_trk_pt                 = new std::vector<std::vector<float>>;
    m_trk_eta                = new std::vector<std::vector<float>>;
    m_trk_phi                = new std::vector<std::vector<float>>;
    m_trk_d0                 = new std::vector<std::vector<float>>;
    m_trk_z0                 = new std::vector<std::vector<float>>;
    m_trk_errd0              = new std::vector<std::vector<float>>;
    m_trk_errz0              = new std::vector<std::vector<float>>;
    m_trk_chi2               = new std::vector<std::vector<float>>;
    m_trk_charge             = new std::vector<std::vector<float>>;
    m_trk_isSelected         = new std::vector<std::vector<uint8_t>>;
    m_trk_isAssociated       = new std::vector<std::vector<uint8_t>>;
    m_trk_dR                 = new std::vector<std::vector<float>>;
    if ( m_mc ) {
      m_trk_isTruth          = new std::vector<std::vector<uint8_t>>;
      m_trk_truthProb        = new std::vector<std::vector<float>>;
      m_trk_truthID          = new std::vector<std::vector<int>>;
      m_trk_truthBarcode     = new std::vector<std::vector<int>>;
      m_trk_truthPdgId       = new std::vector<std::vector<int>>;
      m_tpCount              = new std::vector<int>;
      m_tpPt                 = new std::vector<float>;
      m_tp_ID                = new std::vector<std::vector<int>>;
      m_tp_pt                = new std::vector<std::vector<float>>;
      m_tp_eta               = new std::vector<std::vector<float>>;
      m_tp_phi               = new std::vector<std::vector<float>>;
      m_tp_E                 = new std::vector<std::vector<float>>;
      m_tp_M                 = new std::vector<std::vector<float>>;
      m_tp_charge            = new std::vector<std::vector<float>>;
      m_tp_pdgId             = new std::vector<std::vector<int>>;
      m_tp_status            = new std::vector<std::vector<int>>;
      m_tp_barcode           = new std::vector<std::vector<int>>;
      m_tp_dR                = new std::vector<std::vector<float>>;
      m_tp_isReco            = new std::vector<std::vector<uint8_t>>;
      m_tp_recoProb          = new std::vector<std::vector<float>>;
      m_tp_recoID            = new std::vector<std::vector<int>>;
      m_tp_recoIsSelected    = new std::vector<std::vector<uint8_t>>;
      m_tp_recoIsAssociated  = new std::vector<std::vector<uint8_t>>;
      m_tp_isStable          = new std::vector<std::vector<uint8_t>>;
      m_tp_isInteracting     = new std::vector<std::vector<uint8_t>>;
      m_tp_isReconstructible = new std::vector<std::vector<uint8_t>>;
      m_tp_isDark            = new std::vector<std::vector<uint8_t>>;
    }
  }

  if ( m_infoSwitch.m_ghost ) {
    m_GhostTrack_ID                  = new std::vector<std::vector<int>>;
    m_GhostTrack_m                   = new std::vector<std::vector<float>>;
    m_GhostTrack_errd0               = new std::vector<std::vector<float>>;
    m_GhostTrack_errz0               = new std::vector<std::vector<float>>;
    m_GhostTrack_chi2                = new std::vector<std::vector<float>>;
    m_GhostTrack_charge              = new std::vector<std::vector<float>>;
    m_GhostTrack_isSelected          = new std::vector<std::vector<uint8_t>>;
    m_GhostTrack_isAssociated        = new std::vector<std::vector<uint8_t>>;
    if ( m_mc ) {
      m_GhostTrack_isTruth           = new std::vector<std::vector<uint8_t>>;
      m_GhostTrack_truthProb         = new std::vector<std::vector<float>>;
      m_GhostTrack_truthID           = new std::vector<std::vector<int>>;
      m_GhostTrack_truthBarcode      = new std::vector<std::vector<int>>;
      m_GhostTrack_truthPdgId        = new std::vector<std::vector<int>>;
      m_GhostTruthCount              = new std::vector<int>;
      m_GhostTruthPt                 = new std::vector<float>;
      m_GhostTruth_ID                = new std::vector<std::vector<int>>;
      m_GhostTruth_pt                = new std::vector<std::vector<float>>;
      m_GhostTruth_eta               = new std::vector<std::vector<float>>;
      m_GhostTruth_phi               = new std::vector<std::vector<float>>;
      m_GhostTruth_e                 = new std::vector<std::vector<float>>;
      m_GhostTruth_m                 = new std::vector<std::vector<float>>;
      m_GhostTruth_charge            = new std::vector<std::vector<float>>;
      m_GhostTruth_pdgId             = new std::vector<std::vector<int>>;
      m_GhostTruth_status            = new std::vector<std::vector<int>>;
      m_GhostTruth_barcode           = new std::vector<std::vector<int>>;
      m_GhostTruth_isReco            = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_recoProb          = new std::vector<std::vector<float>>;
      m_GhostTruth_recoID            = new std::vector<std::vector<int>>;
      m_GhostTruth_recoIsSelected    = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_recoIsAssociated  = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_isStable          = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_isInteracting     = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_isReconstructible = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_isDark            = new std::vector<std::vector<uint8_t>>;
    }
  }

  if ( m_infoSwitch.m_constituentAll ) {
    m_girth          = new std::vector<float>;
    m_constituentPt  = new std::vector<float>;
    m_constituent_dR = new std::vector<std::vector<float>>;
    m_constituent_m  = new std::vector<std::vector<float>>;
    if ( jet_type == TRUTH || jet_type == DARK ) {
      m_constituent_ID                = new std::vector<std::vector<int>>;
      m_constituent_charge            = new std::vector<std::vector<float>>;
      m_constituent_pdgId             = new std::vector<std::vector<int>>;
      m_constituent_status            = new std::vector<std::vector<int>>;
      m_constituent_barcode           = new std::vector<std::vector<int>>;
      m_constituent_isStable          = new std::vector<std::vector<uint8_t>>;
      m_constituent_isInteracting     = new std::vector<std::vector<uint8_t>>;
      m_constituent_isReconstructible = new std::vector<std::vector<uint8_t>>;
      m_constituent_isDark            = new std::vector<std::vector<uint8_t>>;
      m_constituent_pVtx              = new std::vector<std::vector<uint8_t>>;
      m_constituent_pVtx_r            = new std::vector<std::vector<float>>;
      m_constituent_dVtx              = new std::vector<std::vector<uint8_t>>;
      m_constituent_dVtx_r            = new std::vector<std::vector<float>>;
    }
  }
}


JetContainer :: ~JetContainer ()
{
  if ( m_debug ) Info( "EJs::JetContainer()", "deleting" );

  delete m_ID;
  delete m_M;
  delete m_radius;

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    if ( jet_type == RECO ) {
      delete m_isTruthMatched;
      delete m_truthMatch_ID;
      delete m_truthMatch_dR;
      delete m_truthMatch_E;
      delete m_truthMatch_M;
      delete m_truthMatch_pt;
      delete m_truthMatch_eta;
      delete m_truthMatch_phi;
      delete m_truthMatch_rapidity;
      delete m_truthNonmatch_IDs;
      delete m_truthNonmatch_dRs;
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      delete m_isDarkMatched;
      delete m_darkMatch_ID;
      delete m_darkMatch_dR;
      delete m_darkMatch_E;
      delete m_darkMatch_M;
      delete m_darkMatch_pt;
      delete m_darkMatch_eta;
      delete m_darkMatch_phi;
      delete m_darkMatch_rapidity;
      delete m_darkNonmatch_IDs;
      delete m_darkNonmatch_dRs;
    }
    if ( jet_type == DARK ) {
      delete m_isMatchedToTruth;
      delete m_matchedTruthID;
      delete m_matchedTruthDR;
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	delete m_isMatchedToEMTopo;
	delete m_matchedEMTopoID;
	delete m_matchedEMTopoDR;
      }
      if ( m_doPFlow ) {
	delete m_isMatchedToPFlow;
	delete m_matchedPFlowID;
	delete m_matchedPFlowDR;
      }
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    delete m_secVtxCount;
    delete m_secVtxPt;
    delete m_secVtx_ID;
    delete m_secVtx_x;
    delete m_secVtx_y;
    delete m_secVtx_z;
    delete m_secVtx_r;
    delete m_secVtx_pt;
    delete m_secVtx_eta;
    delete m_secVtx_phi;
    delete m_secVtx_mass;
    delete m_secVtx_chi2;
    delete m_secVtx_ntrk;
    delete m_secVtx_dR;
    if ( m_mc ) {
      delete m_secVtx_closestTruth_isDarkPionDecay;
      delete m_secVtx_closestTruth_isOffdiagDarkPionDecay;
      delete m_secVtx_closestTruth_ID;
      delete m_secVtx_closestTruth_barcode;
      delete m_secVtx_closestTruth_distance;
      delete m_secVtx_maxlinkTruth_isDarkPionDecay;
      delete m_secVtx_maxlinkTruth_isOffdiagDarkPionDecay;
      delete m_secVtx_maxlinkTruth_ID;
      delete m_secVtx_maxlinkTruth_barcode;
      delete m_secVtx_maxlinkTruth_score;
      delete m_secVtx_maxlinkParentTruth_isDarkPionDecay;
      delete m_secVtx_maxlinkParentTruth_isOffdiagDarkPionDecay;
      delete m_secVtx_maxlinkParentTruth_ID;
      delete m_secVtx_maxlinkParentTruth_barcode;
      delete m_secVtx_maxlinkParentTruth_score;
      delete m_truthVtxCount;
      delete m_truthVtxPt;
      delete m_truthVtx_isDarkPionDecay;
      delete m_truthVtx_isOffdiagDarkPionDecay;
      delete m_truthVtx_ID;
      delete m_truthVtx_x;
      delete m_truthVtx_y;
      delete m_truthVtx_z;
      delete m_truthVtx_r;
      delete m_truthVtx_pt;
      delete m_truthVtx_eta;
      delete m_truthVtx_phi;
      delete m_truthVtx_mass;
      delete m_truthVtx_nOutP;
      delete m_truthVtx_barcode;
      delete m_truthVtx_dR;
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    delete m_trkCount;
    delete m_trkPt;
    delete m_trk_ID;
    delete m_trk_qOverP;
    delete m_trk_E;
    delete m_trk_M;
    delete m_trk_pt;
    delete m_trk_eta;
    delete m_trk_phi;
    delete m_trk_d0;
    delete m_trk_z0;
    delete m_trk_errd0;
    delete m_trk_errz0;
    delete m_trk_chi2;
    delete m_trk_charge;
    delete m_trk_isSelected;
    delete m_trk_isAssociated;
    delete m_trk_dR;
    if ( m_mc ) {
      delete m_trk_isTruth;
      delete m_trk_truthProb;
      delete m_trk_truthID;
      delete m_trk_truthBarcode;
      delete m_trk_truthPdgId;
      delete m_tpCount;
      delete m_tpPt;
      delete m_tp_ID;
      delete m_tp_pt;
      delete m_tp_eta;
      delete m_tp_phi;
      delete m_tp_E;
      delete m_tp_M;
      delete m_tp_charge;
      delete m_tp_pdgId;
      delete m_tp_status;
      delete m_tp_barcode;
      delete m_tp_dR;
      delete m_tp_isReco;
      delete m_tp_recoProb;
      delete m_tp_recoID;
      delete m_tp_recoIsSelected;
      delete m_tp_recoIsAssociated;
      delete m_tp_isStable;
      delete m_tp_isInteracting;
      delete m_tp_isReconstructible;
      delete m_tp_isDark;
    }
  }

  if ( m_infoSwitch.m_ghost ) {
    delete m_GhostTrack_ID;
    delete m_GhostTrack_m;
    delete m_GhostTrack_errd0;
    delete m_GhostTrack_errz0;
    delete m_GhostTrack_chi2;
    delete m_GhostTrack_charge;
    delete m_GhostTrack_isSelected;
    delete m_GhostTrack_isAssociated;
    if ( m_mc ) {
      delete m_GhostTrack_isTruth;
      delete m_GhostTrack_truthProb;
      delete m_GhostTrack_truthID;
      delete m_GhostTrack_truthBarcode;
      delete m_GhostTrack_truthPdgId;
      delete m_GhostTruthCount;
      delete m_GhostTruthPt;
      delete m_GhostTruth_ID;
      delete m_GhostTruth_pt;
      delete m_GhostTruth_eta; 
      delete m_GhostTruth_phi;
      delete m_GhostTruth_e;
      delete m_GhostTruth_m;
      delete m_GhostTruth_charge;
      delete m_GhostTruth_pdgId;
      delete m_GhostTruth_status;
      delete m_GhostTruth_barcode;
      delete m_GhostTruth_isReco;
      delete m_GhostTruth_recoProb;
      delete m_GhostTruth_recoID;
      delete m_GhostTruth_recoIsSelected;
      delete m_GhostTruth_recoIsAssociated;
      delete m_GhostTruth_isStable;
      delete m_GhostTruth_isInteracting;
      delete m_GhostTruth_isReconstructible;
      delete m_GhostTruth_isDark;
    }
  }

  if ( m_infoSwitch.m_constituentAll ) {
    delete m_girth;
    delete m_constituentPt;
    delete m_constituent_dR;
    delete m_constituent_m;
    if ( jet_type == TRUTH || jet_type == DARK ) {
      delete m_constituent_ID;
      delete m_constituent_charge;
      delete m_constituent_pdgId;
      delete m_constituent_status;
      delete m_constituent_barcode;
      delete m_constituent_isStable;
      delete m_constituent_isInteracting;
      delete m_constituent_isReconstructible;
      delete m_constituent_isDark;
      delete m_constituent_pVtx;
      delete m_constituent_pVtx_r;
      delete m_constituent_dVtx;
      delete m_constituent_dVtx_r;
    }
  }
}


void JetContainer :: setTree ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::JetContainer::setTree()", "setting tree" );

  connectBranch<int>   ( tree, "ID",     &m_ID     );
  connectBranch<float> ( tree, "M",      &m_M      );
  connectBranch<float> ( tree, "radius", &m_radius );

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    if ( jet_type == RECO ) {
      connectBranch<uint8_t>            ( tree, "isTruthMatched",      &m_isTruthMatched      );
      connectBranch<int>                ( tree, "truthMatch_ID",       &m_truthMatch_ID       );
      connectBranch<float>              ( tree, "truthMatch_dR",       &m_truthMatch_dR       );
      connectBranch<float>              ( tree, "truthMatch_E",        &m_truthMatch_E        );
      connectBranch<float>              ( tree, "truthMatch_M",        &m_truthMatch_M        );
      connectBranch<float>              ( tree, "truthMatch_pt",       &m_truthMatch_pt       );
      connectBranch<float>              ( tree, "truthMatch_eta",      &m_truthMatch_eta      );
      connectBranch<float>              ( tree, "truthMatch_phi",      &m_truthMatch_phi      );
      connectBranch<float>              ( tree, "truthMatch_rapidity", &m_truthMatch_rapidity );
      connectBranch<std::vector<int>>   ( tree, "truthNonmatch_IDs",   &m_truthNonmatch_IDs   );
      connectBranch<std::vector<float>> ( tree, "truthNonmatch_dRs",   &m_truthNonmatch_dRs   );
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      connectBranch<uint8_t>            ( tree, "isDarkMatched",       &m_isDarkMatched       );
      connectBranch<int>                ( tree, "darkMatch_ID",        &m_darkMatch_ID        );
      connectBranch<float>              ( tree, "darkMatch_dR",        &m_darkMatch_dR        );
      connectBranch<float>              ( tree, "darkMatch_E",         &m_darkMatch_E         );
      connectBranch<float>              ( tree, "darkMatch_M",         &m_darkMatch_M         );
      connectBranch<float>              ( tree, "darkMatch_pt",        &m_darkMatch_pt        );
      connectBranch<float>              ( tree, "darkMatch_eta",       &m_darkMatch_eta       );
      connectBranch<float>              ( tree, "darkMatch_phi",       &m_darkMatch_phi       );
      connectBranch<float>              ( tree, "darkMatch_rapidity",  &m_darkMatch_rapidity  );
      connectBranch<std::vector<int>>   ( tree, "darkNonmatch_IDs",    &m_darkNonmatch_IDs    );
      connectBranch<std::vector<float>> ( tree, "darkNonmatch_dRs",    &m_darkNonmatch_dRs    );
    }
    if ( jet_type == DARK ) {
      connectBranch<uint8_t>            ( tree, "isMatchedToTruth",    &m_isMatchedToTruth    );
      connectBranch<int>                ( tree, "matchedTruthID",      &m_matchedTruthID      );
      connectBranch<float>              ( tree, "matchedTruthDR",      &m_matchedTruthDR      );
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	connectBranch<uint8_t>          ( tree, "isMatchedToEMTopo",   &m_isMatchedToEMTopo   );
	connectBranch<int>              ( tree, "matchedEMTopoID",     &m_matchedEMTopoID     );
	connectBranch<float>            ( tree, "matchedEMTopoDR",     &m_matchedEMTopoDR     );
      }
      if ( m_doPFlow ) {
	connectBranch<uint8_t>          ( tree, "isMatchedToPFlow",    &m_isMatchedToPFlow    );
	connectBranch<int>              ( tree, "matchedPFlowID",      &m_matchedPFlowID      );
	connectBranch<float>            ( tree, "matchedPFlowDR",      &m_matchedPFlowDR      );
      }
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    connectBranch<int>                    ( tree, "secVtxCount",                                      &m_secVtxCount                                      );
    connectBranch<float>                  ( tree, "secVtxPt",                                         &m_secVtxPt                                         );
    connectBranch<std::vector<int>>       ( tree, "secVtx_ID",                                        &m_secVtx_ID                                        );
    connectBranch<std::vector<float>>     ( tree, "secVtx_x",                                         &m_secVtx_x                                         );
    connectBranch<std::vector<float>>     ( tree, "secVtx_y",                                         &m_secVtx_y                                         );
    connectBranch<std::vector<float>>     ( tree, "secVtx_z",                                         &m_secVtx_z                                         );
    connectBranch<std::vector<float>>     ( tree, "secVtx_r",                                         &m_secVtx_r                                         );
    connectBranch<std::vector<float>>     ( tree, "secVtx_pt",                                        &m_secVtx_pt                                        );
    connectBranch<std::vector<float>>     ( tree, "secVtx_eta",                                       &m_secVtx_eta                                       );
    connectBranch<std::vector<float>>     ( tree, "secVtx_phi",                                       &m_secVtx_phi                                       );
    connectBranch<std::vector<float>>     ( tree, "secVtx_mass",                                      &m_secVtx_mass                                      );
    connectBranch<std::vector<float>>     ( tree, "secVtx_chi2",                                      &m_secVtx_chi2                                      );
    connectBranch<std::vector<int>>       ( tree, "secVtx_ntrk",                                      &m_secVtx_ntrk                                      );
    connectBranch<std::vector<float>>     ( tree, "secVtx_dR",                                        &m_secVtx_dR                                        );
    if ( m_mc ) {
      connectBranch<std::vector<uint8_t>> ( tree, "secVtx_closestTruth_isDarkPionDecay",              &m_secVtx_closestTruth_isDarkPionDecay              );
      connectBranch<std::vector<uint8_t>> ( tree, "secVtx_closestTruth_isOffdiagDarkPionDecay",       &m_secVtx_closestTruth_isOffdiagDarkPionDecay       );
      connectBranch<std::vector<int>>     ( tree, "secVtx_closestTruth_ID",                           &m_secVtx_closestTruth_ID                           );
      connectBranch<std::vector<int>>     ( tree, "secVtx_closestTruth_barcode",                      &m_secVtx_closestTruth_barcode                      );
      connectBranch<std::vector<float>>   ( tree, "secVtx_closestTruth_distance",                     &m_secVtx_closestTruth_distance                     );
      connectBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkTruth_isDarkPionDecay",              &m_secVtx_maxlinkTruth_isDarkPionDecay              );
      connectBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkTruth_isOffdiagDarkPionDecay",       &m_secVtx_maxlinkTruth_isOffdiagDarkPionDecay       );
      connectBranch<std::vector<int>>     ( tree, "secVtx_maxlinkTruth_ID",                           &m_secVtx_maxlinkTruth_ID                           );
      connectBranch<std::vector<int>>     ( tree, "secVtx_maxlinkTruth_barcode",                      &m_secVtx_maxlinkTruth_barcode                      );
      connectBranch<std::vector<float>>   ( tree, "secVtx_maxlinkTruth_score",                        &m_secVtx_maxlinkTruth_score                        );
      connectBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkParentTruth_isDarkPionDecay",        &m_secVtx_maxlinkParentTruth_isDarkPionDecay        );
      connectBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkParentTruth_isOffdiagDarkPionDecay", &m_secVtx_maxlinkParentTruth_isOffdiagDarkPionDecay );
      connectBranch<std::vector<int>>     ( tree, "secVtx_maxlinkParentTruth_ID",                     &m_secVtx_maxlinkParentTruth_ID                     );
      connectBranch<std::vector<int>>     ( tree, "secVtx_maxlinkParentTruth_barcode",                &m_secVtx_maxlinkParentTruth_barcode                );
      connectBranch<std::vector<float>>   ( tree, "secVtx_maxlinkParentTruth_score",                  &m_secVtx_maxlinkParentTruth_score                  );
      connectBranch<int>                  ( tree, "truthVtxCount",                                    &m_truthVtxCount                                    );
      connectBranch<float>                ( tree, "truthVtxPt",                                       &m_truthVtxPt                                       );
      connectBranch<std::vector<uint8_t>> ( tree, "truthVtx_isDarkPionDecay",                         &m_truthVtx_isDarkPionDecay                         );
      connectBranch<std::vector<uint8_t>> ( tree, "truthVtx_isOffdiagDarkPionDecay",                  &m_truthVtx_isOffdiagDarkPionDecay                  );
      connectBranch<std::vector<int>>     ( tree, "truthVtx_ID",                                      &m_truthVtx_ID                                      );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_x",                                       &m_truthVtx_x                                       );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_y",                                       &m_truthVtx_y                                       );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_z",                                       &m_truthVtx_z                                       );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_r",                                       &m_truthVtx_r                                       );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_pt",                                      &m_truthVtx_pt                                      );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_eta",                                     &m_truthVtx_eta                                     );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_phi",                                     &m_truthVtx_phi                                     );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_mass",                                    &m_truthVtx_mass                                    );
      connectBranch<std::vector<int>>     ( tree, "truthVtx_nOutP",                                   &m_truthVtx_nOutP                                   );
      connectBranch<std::vector<int>>     ( tree, "truthVtx_barcode",                                 &m_truthVtx_barcode                                 );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_dR",                                      &m_truthVtx_dR                                      );
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    connectBranch<int>                    ( tree, "trkCount",             &m_trkCount             );
    connectBranch<float>                  ( tree, "trkPt",                &m_trkPt                );
    connectBranch<std::vector<int>>       ( tree, "trk_ID",               &m_trk_ID               );
    connectBranch<std::vector<float>>     ( tree, "trk_qOverP",           &m_trk_qOverP           );
    connectBranch<std::vector<float>>     ( tree, "trk_E",                &m_trk_E                );
    connectBranch<std::vector<float>>     ( tree, "trk_M",                &m_trk_M                );
    connectBranch<std::vector<float>>     ( tree, "trk_pt",               &m_trk_pt               );
    connectBranch<std::vector<float>>     ( tree, "trk_eta",              &m_trk_eta              );
    connectBranch<std::vector<float>>     ( tree, "trk_phi",              &m_trk_phi              );
    connectBranch<std::vector<float>>     ( tree, "trk_d0",               &m_trk_d0               );
    connectBranch<std::vector<float>>     ( tree, "trk_z0",               &m_trk_z0               );
    connectBranch<std::vector<float>>     ( tree, "trk_errd0",            &m_trk_errd0            );
    connectBranch<std::vector<float>>     ( tree, "trk_errz0",            &m_trk_errz0            );
    connectBranch<std::vector<float>>     ( tree, "trk_chi2",             &m_trk_chi2             );
    connectBranch<std::vector<float>>     ( tree, "trk_charge",           &m_trk_charge           );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_isSelected",       &m_trk_isSelected       );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_isAssociated",     &m_trk_isAssociated     );
    connectBranch<std::vector<float>>     ( tree, "trk_dR",               &m_trk_dR               );
    if ( m_mc ) {
      connectBranch<std::vector<uint8_t>> ( tree, "trk_isTruth",          &m_trk_isTruth          );
      connectBranch<std::vector<float>>   ( tree, "trk_truthProb",        &m_trk_truthProb        );
      connectBranch<std::vector<int>>     ( tree, "trk_truthID",          &m_trk_truthID          );
      connectBranch<std::vector<int>>     ( tree, "trk_truthBarcode",     &m_trk_truthBarcode     );
      connectBranch<std::vector<int>>     ( tree, "trk_truthPdgId",       &m_trk_truthPdgId       );
      connectBranch<int>                  ( tree, "tpCount",              &m_tpCount              );
      connectBranch<float>                ( tree, "tpPt",                 &m_tpPt                 );
      connectBranch<std::vector<int>>     ( tree, "tp_ID",                &m_tp_ID                );
      connectBranch<std::vector<float>>   ( tree, "tp_pt",                &m_tp_pt                );
      connectBranch<std::vector<float>>   ( tree, "tp_eta",               &m_tp_eta               );
      connectBranch<std::vector<float>>   ( tree, "tp_phi",               &m_tp_phi               );
      connectBranch<std::vector<float>>   ( tree, "tp_E",                 &m_tp_E                 );
      connectBranch<std::vector<float>>   ( tree, "tp_M",                 &m_tp_M                 );
      connectBranch<std::vector<float>>   ( tree, "tp_charge",            &m_tp_charge            );
      connectBranch<std::vector<int>>     ( tree, "tp_pdgId",             &m_tp_pdgId             );
      connectBranch<std::vector<int>>     ( tree, "tp_status",            &m_tp_status            );
      connectBranch<std::vector<int>>     ( tree, "tp_barcode",           &m_tp_barcode           );
      connectBranch<std::vector<float>>   ( tree, "tp_dR",                &m_tp_dR                );
      connectBranch<std::vector<uint8_t>> ( tree, "tp_isReco",            &m_tp_isReco            );
      connectBranch<std::vector<float>>   ( tree, "tp_recoProb",          &m_tp_recoProb          );
      connectBranch<std::vector<int>>     ( tree, "tp_recoID",            &m_tp_recoID            );
      connectBranch<std::vector<uint8_t>> ( tree, "tp_recoIsSelected",    &m_tp_recoIsSelected    );
      connectBranch<std::vector<uint8_t>> ( tree, "tp_recoIsAssociated",  &m_tp_recoIsAssociated  );
      connectBranch<std::vector<uint8_t>> ( tree, "tp_isStable",          &m_tp_isStable          );
      connectBranch<std::vector<uint8_t>> ( tree, "tp_isInteracting",     &m_tp_isInteracting     );
      connectBranch<std::vector<uint8_t>> ( tree, "tp_isReconstructible", &m_tp_isReconstructible );
      connectBranch<std::vector<uint8_t>> ( tree, "tp_isDark",            &m_tp_isDark            );
    }
  }

  if ( m_infoSwitch.m_ghost ) {
    connectBranch<std::vector<int>>       ( tree, "GhostTrack_ID",                &m_GhostTrack_ID                );
    connectBranch<std::vector<float>>     ( tree, "GhostTrack_m",                 &m_GhostTrack_m                 );
    connectBranch<std::vector<float>>     ( tree, "GhostTrack_errd0",             &m_GhostTrack_errd0             );
    connectBranch<std::vector<float>>     ( tree, "GhostTrack_errz0",             &m_GhostTrack_errz0             );
    connectBranch<std::vector<float>>     ( tree, "GhostTrack_chi2",              &m_GhostTrack_chi2              );
    connectBranch<std::vector<float>>     ( tree, "GhostTrack_charge",            &m_GhostTrack_charge            );
    connectBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSelected",        &m_GhostTrack_isSelected        );
    connectBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isAssociated",      &m_GhostTrack_isAssociated      );
    if ( m_mc ) {
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTrack_isTruth",           &m_GhostTrack_isTruth           );
      connectBranch<std::vector<float>>   ( tree, "GhostTrack_truthProb",         &m_GhostTrack_truthProb         );
      connectBranch<std::vector<int>>     ( tree, "GhostTrack_truthID",           &m_GhostTrack_truthID           );
      connectBranch<std::vector<int>>     ( tree, "GhostTrack_truthBarcode",      &m_GhostTrack_truthBarcode      );
      connectBranch<std::vector<int>>     ( tree, "GhostTrack_truthPdgId",        &m_GhostTrack_truthPdgId        );
      connectBranch<int>                  ( tree, "GhostTruthCount",              &m_GhostTruthCount              );
      connectBranch<float>                ( tree, "GhostTruthPt",                 &m_GhostTruthPt                 );
      connectBranch<std::vector<int>>     ( tree, "GhostTruth_ID",                &m_GhostTruth_ID                );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_pt",                &m_GhostTruth_pt                );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_eta",               &m_GhostTruth_eta               );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_phi",               &m_GhostTruth_phi               );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_e",                 &m_GhostTruth_e                 );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_m",                 &m_GhostTruth_m                 );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_charge",            &m_GhostTruth_charge            );
      connectBranch<std::vector<int>>     ( tree, "GhostTruth_pdgId",             &m_GhostTruth_pdgId             );
      connectBranch<std::vector<int>>     ( tree, "GhostTruth_status",            &m_GhostTruth_status            );
      connectBranch<std::vector<int>>     ( tree, "GhostTruth_barcode",           &m_GhostTruth_barcode           );
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isReco",            &m_GhostTruth_isReco            );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_recoProb",          &m_GhostTruth_recoProb          );
      connectBranch<std::vector<int>>     ( tree, "GhostTruth_recoID",            &m_GhostTruth_recoID            );
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTruth_recoIsSelected",    &m_GhostTruth_recoIsSelected    );
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTruth_recoIsAssociated",  &m_GhostTruth_recoIsAssociated  );
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isStable",          &m_GhostTruth_isStable          );
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isInteracting",     &m_GhostTruth_isInteracting     );
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isReconstructible", &m_GhostTruth_isReconstructible );
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isDark",            &m_GhostTruth_isDark            );
    }
  }
    
  if ( m_infoSwitch.m_constituentAll ) {
    connectBranch<float>                  ( tree, "girth",                         &m_girth                         );
    connectBranch<float>                  ( tree, "constituentPt",                 &m_constituentPt                 );
    connectBranch<std::vector<float>>     ( tree, "constituent_dR",                &m_constituent_dR                );
    connectBranch<std::vector<float>>     ( tree, "constituent_m",                 &m_constituent_m                 );
    if ( jet_type == TRUTH || jet_type == DARK ) {
      connectBranch<std::vector<int>>     ( tree, "constituent_ID",                &m_constituent_ID                );
      connectBranch<std::vector<float>>   ( tree, "constituent_charge",            &m_constituent_charge            );
      connectBranch<std::vector<int>>     ( tree, "constituent_pdgId",             &m_constituent_pdgId             );
      connectBranch<std::vector<int>>     ( tree, "constituent_status",            &m_constituent_status            );
      connectBranch<std::vector<int>>     ( tree, "constituent_barcode",           &m_constituent_barcode           );
      connectBranch<std::vector<uint8_t>> ( tree, "constituent_isStable",          &m_constituent_isStable          );
      connectBranch<std::vector<uint8_t>> ( tree, "constituent_isInteracting",     &m_constituent_isInteracting     );
      connectBranch<std::vector<uint8_t>> ( tree, "constituent_isReconstructible", &m_constituent_isReconstructible );
      connectBranch<std::vector<uint8_t>> ( tree, "constituent_isDark",            &m_constituent_isDark            );
      connectBranch<std::vector<uint8_t>> ( tree, "constituent_hasProdVtx",        &m_constituent_pVtx              );
      connectBranch<std::vector<float>>   ( tree, "constituent_prodVtx_r",         &m_constituent_pVtx_r            );
      connectBranch<std::vector<uint8_t>> ( tree, "constituent_hasDecayVtx",       &m_constituent_dVtx              );
      connectBranch<std::vector<float>>   ( tree, "constituent_decayVtx_r",        &m_constituent_dVtx_r            );
    }
  }
}


void JetContainer :: setBranches ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::JetContainer::setBranches()", "setting branches" );

  setBranch<int>   ( tree, "ID",     m_ID     );
  setBranch<float> ( tree, "M",      m_M      );
  setBranch<float> ( tree, "radius", m_radius );

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    if ( jet_type == RECO ) {
      setBranch<uint8_t>            ( tree, "isTruthMatched",        m_isTruthMatched        );
      setBranch<int>                ( tree, "truthMatch_ID",         m_truthMatch_ID         );
      setBranch<float>              ( tree, "truthMatch_dR",         m_truthMatch_dR         );
      setBranch<float>              ( tree, "truthMatch_E",          m_truthMatch_E          );
      setBranch<float>              ( tree, "truthMatch_M",          m_truthMatch_M          );
      setBranch<float>              ( tree, "truthMatch_pt",         m_truthMatch_pt         );
      setBranch<float>              ( tree, "truthMatch_eta",        m_truthMatch_eta        );
      setBranch<float>              ( tree, "truthMatch_phi",        m_truthMatch_phi        );
      setBranch<float>              ( tree, "truthMatch_rapidity",   m_truthMatch_rapidity   );
      setBranch<std::vector<int>>   ( tree, "truthNonmatch_IDs",     m_truthNonmatch_IDs     );
      setBranch<std::vector<float>> ( tree, "truthNonmatch_dRs",     m_truthNonmatch_dRs     );
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      setBranch<uint8_t>            ( tree, "isDarkMatched",      m_isDarkMatched      );
      setBranch<int>                ( tree, "darkMatch_ID",       m_darkMatch_ID       );
      setBranch<float>              ( tree, "darkMatch_dR",       m_darkMatch_dR       );
      setBranch<float>              ( tree, "darkMatch_E",        m_darkMatch_E        );
      setBranch<float>              ( tree, "darkMatch_M",        m_darkMatch_M        );
      setBranch<float>              ( tree, "darkMatch_pt",       m_darkMatch_pt       );
      setBranch<float>              ( tree, "darkMatch_eta",      m_darkMatch_eta      );
      setBranch<float>              ( tree, "darkMatch_phi",      m_darkMatch_phi      );
      setBranch<float>              ( tree, "darkMatch_rapidity", m_darkMatch_rapidity );
      setBranch<std::vector<int>>   ( tree, "darkNonmatch_IDs",   m_darkNonmatch_IDs   );
      setBranch<std::vector<float>> ( tree, "darkNonmatch_dRs",   m_darkNonmatch_dRs   );
    }
    if ( jet_type == DARK ) {
      setBranch<uint8_t>            ( tree, "isMatchedToTruth",   m_isMatchedToTruth   );
      setBranch<int>                ( tree, "matchedTruthID",     m_matchedTruthID     );
      setBranch<float>              ( tree, "matchedTruthDR",     m_matchedTruthDR     );
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	setBranch<uint8_t>          ( tree, "isMatchedToEMTopo",  m_isMatchedToEMTopo  );
	setBranch<int>              ( tree, "matchedEMTopoID",    m_matchedEMTopoID    );
	setBranch<float>            ( tree, "matchedEMTopoDR",    m_matchedEMTopoDR    );
      }
      if ( m_doPFlow ) {
	setBranch<uint8_t>          ( tree, "isMatchedToPFlow",   m_isMatchedToPFlow   );
	setBranch<int>              ( tree, "matchedPFlowID",     m_matchedPFlowID     );
	setBranch<float>            ( tree, "matchedPFlowDR",     m_matchedPFlowDR     );
      }
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    setBranch<int>                    ( tree, "secVtxCount",                                      m_secVtxCount                                      );
    setBranch<float>                  ( tree, "secVtxPt",                                         m_secVtxPt                                         );
    setBranch<std::vector<int>>       ( tree, "secVtx_ID",                                        m_secVtx_ID                                        );
    setBranch<std::vector<float>>     ( tree, "secVtx_x",                                         m_secVtx_x                                         );
    setBranch<std::vector<float>>     ( tree, "secVtx_y",                                         m_secVtx_y                                         );
    setBranch<std::vector<float>>     ( tree, "secVtx_z",                                         m_secVtx_z                                         );
    setBranch<std::vector<float>>     ( tree, "secVtx_r",                                         m_secVtx_r                                         );
    setBranch<std::vector<float>>     ( tree, "secVtx_pt",                                        m_secVtx_pt                                        );
    setBranch<std::vector<float>>     ( tree, "secVtx_eta",                                       m_secVtx_eta                                       );
    setBranch<std::vector<float>>     ( tree, "secVtx_phi",                                       m_secVtx_phi                                       );
    setBranch<std::vector<float>>     ( tree, "secVtx_mass",                                      m_secVtx_mass                                      );
    setBranch<std::vector<float>>     ( tree, "secVtx_chi2",                                      m_secVtx_chi2                                      );
    setBranch<std::vector<int>>       ( tree, "secVtx_ntrk",                                      m_secVtx_ntrk                                      );
    setBranch<std::vector<float>>     ( tree, "secVtx_dR",                                        m_secVtx_dR                                        );
    if ( m_mc ) {
      setBranch<std::vector<uint8_t>> ( tree, "secVtx_closestTruth_isDarkPionDecay",              m_secVtx_closestTruth_isDarkPionDecay              );
      setBranch<std::vector<uint8_t>> ( tree, "secVtx_closestTruth_isOffdiagDarkPionDecay",       m_secVtx_closestTruth_isOffdiagDarkPionDecay       );
      setBranch<std::vector<int>>     ( tree, "secVtx_closestTruth_ID",                           m_secVtx_closestTruth_ID                           );
      setBranch<std::vector<int>>     ( tree, "secVtx_closestTruth_barcode",                      m_secVtx_closestTruth_barcode                      );
      setBranch<std::vector<float>>   ( tree, "secVtx_closestTruth_distance",                     m_secVtx_closestTruth_distance                     );
      setBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkTruth_isDarkPionDecay",              m_secVtx_maxlinkTruth_isDarkPionDecay              );
      setBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkTruth_isOffdiagDarkPionDecay",       m_secVtx_maxlinkTruth_isOffdiagDarkPionDecay       );
      setBranch<std::vector<int>>     ( tree, "secVtx_maxlinkTruth_ID",                           m_secVtx_maxlinkTruth_ID                           );
      setBranch<std::vector<int>>     ( tree, "secVtx_maxlinkTruth_barcode",                      m_secVtx_maxlinkTruth_barcode                      );
      setBranch<std::vector<float>>   ( tree, "secVtx_maxlinkTruth_score",                        m_secVtx_maxlinkTruth_score                        );
      setBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkParentTruth_isDarkPionDecay",        m_secVtx_maxlinkParentTruth_isDarkPionDecay        );
      setBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkParentTruth_isOffdiagDarkPionDecay", m_secVtx_maxlinkParentTruth_isOffdiagDarkPionDecay );
      setBranch<std::vector<int>>     ( tree, "secVtx_maxlinkParentTruth_ID",                     m_secVtx_maxlinkParentTruth_ID                     );
      setBranch<std::vector<int>>     ( tree, "secVtx_maxlinkParentTruth_barcode",                m_secVtx_maxlinkParentTruth_barcode                );
      setBranch<std::vector<float>>   ( tree, "secVtx_maxlinkParentTruth_score",                  m_secVtx_maxlinkParentTruth_score                  );
      setBranch<int>                  ( tree, "truthVtxCount",                                    m_truthVtxCount                                    );
      setBranch<float>                ( tree, "truthVtxPt",                                       m_truthVtxPt                                       );
      setBranch<std::vector<uint8_t>> ( tree, "truthVtx_isDarkPionDecay",                         m_truthVtx_isDarkPionDecay                         );
      setBranch<std::vector<uint8_t>> ( tree, "truthVtx_isOffdiagDarkPionDecay",                  m_truthVtx_isOffdiagDarkPionDecay                  );
      setBranch<std::vector<int>>     ( tree, "truthVtx_ID",                                      m_truthVtx_ID                                      );
      setBranch<std::vector<float>>   ( tree, "truthVtx_x",                                       m_truthVtx_x                                       );
      setBranch<std::vector<float>>   ( tree, "truthVtx_y",                                       m_truthVtx_y                                       );
      setBranch<std::vector<float>>   ( tree, "truthVtx_z",                                       m_truthVtx_z                                       );
      setBranch<std::vector<float>>   ( tree, "truthVtx_r",                                       m_truthVtx_r                                       );
      setBranch<std::vector<float>>   ( tree, "truthVtx_pt",                                      m_truthVtx_pt                                      );
      setBranch<std::vector<float>>   ( tree, "truthVtx_eta",                                     m_truthVtx_eta                                     );
      setBranch<std::vector<float>>   ( tree, "truthVtx_phi",                                     m_truthVtx_phi                                     );
      setBranch<std::vector<float>>   ( tree, "truthVtx_mass",                                    m_truthVtx_mass                                    );
      setBranch<std::vector<int>>     ( tree, "truthVtx_nOutP",                                   m_truthVtx_nOutP                                   );
      setBranch<std::vector<int>>     ( tree, "truthVtx_barcode",                                 m_truthVtx_barcode                                 );
      setBranch<std::vector<float>>   ( tree, "truthVtx_dR",                                      m_truthVtx_dR                                      );
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    setBranch<int>                    ( tree, "trkCount",             m_trkCount             );
    setBranch<float>                  ( tree, "trkPt",                m_trkPt                );
    setBranch<std::vector<int>>       ( tree, "trk_ID",               m_trk_ID               );
    setBranch<std::vector<float>>     ( tree, "trk_qOverP",           m_trk_qOverP           );
    setBranch<std::vector<float>>     ( tree, "trk_E",                m_trk_E                );
    setBranch<std::vector<float>>     ( tree, "trk_M",                m_trk_M                );
    setBranch<std::vector<float>>     ( tree, "trk_pt",               m_trk_pt               );
    setBranch<std::vector<float>>     ( tree, "trk_eta",              m_trk_eta              );
    setBranch<std::vector<float>>     ( tree, "trk_phi",              m_trk_phi              );
    setBranch<std::vector<float>>     ( tree, "trk_d0",               m_trk_d0               );
    setBranch<std::vector<float>>     ( tree, "trk_z0",               m_trk_z0               );
    setBranch<std::vector<float>>     ( tree, "trk_errd0",            m_trk_errd0            );
    setBranch<std::vector<float>>     ( tree, "trk_errz0",            m_trk_errz0            );
    setBranch<std::vector<float>>     ( tree, "trk_chi2",             m_trk_chi2             );
    setBranch<std::vector<float>>     ( tree, "trk_charge",           m_trk_charge           );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_isSelected",       m_trk_isSelected       );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_isAssociated",     m_trk_isAssociated     );
    setBranch<std::vector<float>>     ( tree, "trk_dR",               m_trk_dR               );
    if ( m_mc ) {
      setBranch<std::vector<uint8_t>> ( tree, "trk_isTruth",          m_trk_isTruth          );
      setBranch<std::vector<float>>   ( tree, "trk_truthProb",        m_trk_truthProb        );
      setBranch<std::vector<int>>     ( tree, "trk_truthID",          m_trk_truthID          );
      setBranch<std::vector<int>>     ( tree, "trk_truthBarcode",     m_trk_truthBarcode     );
      setBranch<std::vector<int>>     ( tree, "trk_truthPdgId",       m_trk_truthPdgId       );
      setBranch<int>                  ( tree, "tpCount",              m_tpCount              );
      setBranch<float>                ( tree, "tpPt",                 m_tpPt                 );
      setBranch<std::vector<int>>     ( tree, "tp_ID",                m_tp_ID                );
      setBranch<std::vector<float>>   ( tree, "tp_pt",                m_tp_pt                );
      setBranch<std::vector<float>>   ( tree, "tp_eta",               m_tp_eta               );
      setBranch<std::vector<float>>   ( tree, "tp_phi",               m_tp_phi               );
      setBranch<std::vector<float>>   ( tree, "tp_E",                 m_tp_E                 );
      setBranch<std::vector<float>>   ( tree, "tp_M",                 m_tp_M                 );
      setBranch<std::vector<float>>   ( tree, "tp_charge",            m_tp_charge            );
      setBranch<std::vector<int>>     ( tree, "tp_pdgId",             m_tp_pdgId             );
      setBranch<std::vector<int>>     ( tree, "tp_status",            m_tp_status            );
      setBranch<std::vector<int>>     ( tree, "tp_barcode",           m_tp_barcode           );
      setBranch<std::vector<float>>   ( tree, "tp_dR",                m_tp_dR                );
      setBranch<std::vector<uint8_t>> ( tree, "tp_isReco",            m_tp_isReco            );
      setBranch<std::vector<float>>   ( tree, "tp_recoProb",          m_tp_recoProb          );
      setBranch<std::vector<int>>     ( tree, "tp_recoID",            m_tp_recoID            );
      setBranch<std::vector<uint8_t>> ( tree, "tp_recoIsSelected",    m_tp_recoIsSelected    );
      setBranch<std::vector<uint8_t>> ( tree, "tp_recoIsAssociated",  m_tp_recoIsAssociated  );
      setBranch<std::vector<uint8_t>> ( tree, "tp_isStable",          m_tp_isStable          );
      setBranch<std::vector<uint8_t>> ( tree, "tp_isInteracting",     m_tp_isInteracting     );
      setBranch<std::vector<uint8_t>> ( tree, "tp_isReconstructible", m_tp_isReconstructible );
      setBranch<std::vector<uint8_t>> ( tree, "tp_isDark",            m_tp_isDark            );
    }
  }

  if ( m_infoSwitch.m_ghost ) {
    setBranch<std::vector<int>>       ( tree, "GhostTrack_ID",                m_GhostTrack_ID                );
    setBranch<std::vector<float>>     ( tree, "GhostTrack_m",                 m_GhostTrack_m                 );
    setBranch<std::vector<float>>     ( tree, "GhostTrack_errd0",             m_GhostTrack_errd0             );
    setBranch<std::vector<float>>     ( tree, "GhostTrack_errz0",             m_GhostTrack_errz0             );
    setBranch<std::vector<float>>     ( tree, "GhostTrack_chi2",              m_GhostTrack_chi2              );
    setBranch<std::vector<float>>     ( tree, "GhostTrack_charge",            m_GhostTrack_charge            );
    setBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSelected",        m_GhostTrack_isSelected        );
    setBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isAssociated",      m_GhostTrack_isAssociated      );
    if ( m_mc ) {
      setBranch<std::vector<uint8_t>> ( tree, "GhostTrack_isTruth",           m_GhostTrack_isTruth           );
      setBranch<std::vector<float>>   ( tree, "GhostTrack_truthProb",         m_GhostTrack_truthProb         );
      setBranch<std::vector<int>>     ( tree, "GhostTrack_truthID",           m_GhostTrack_truthID           );
      setBranch<std::vector<int>>     ( tree, "GhostTrack_truthBarcode",      m_GhostTrack_truthBarcode      );
      setBranch<std::vector<int>>     ( tree, "GhostTrack_truthPdgId",        m_GhostTrack_truthPdgId        );
      setBranch<int>                  ( tree, "GhostTruthCount",              m_GhostTruthCount              );
      setBranch<float>                ( tree, "GhostTruthPt",                 m_GhostTruthPt                 );
      setBranch<std::vector<int>>     ( tree, "GhostTruth_ID",                m_GhostTruth_ID                );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_pt",                m_GhostTruth_pt                );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_eta",               m_GhostTruth_eta               );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_phi",               m_GhostTruth_phi               );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_e",                 m_GhostTruth_e                 );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_m",                 m_GhostTruth_m                 );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_charge",            m_GhostTruth_charge            );
      setBranch<std::vector<int>>     ( tree, "GhostTruth_pdgId",             m_GhostTruth_pdgId             );
      setBranch<std::vector<int>>     ( tree, "GhostTruth_status",            m_GhostTruth_status            );
      setBranch<std::vector<int>>     ( tree, "GhostTruth_barcode",           m_GhostTruth_barcode           );
      setBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isReco",            m_GhostTruth_isReco            );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_recoProb",          m_GhostTruth_recoProb          );
      setBranch<std::vector<int>>     ( tree, "GhostTruth_recoID",            m_GhostTruth_recoID            );
      setBranch<std::vector<uint8_t>> ( tree, "GhostTruth_recoIsSelected",    m_GhostTruth_recoIsSelected    );
      setBranch<std::vector<uint8_t>> ( tree, "GhostTruth_recoIsAssociated",  m_GhostTruth_recoIsAssociated  );
      setBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isStable",          m_GhostTruth_isStable          );
      setBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isInteracting",     m_GhostTruth_isInteracting     );
      setBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isReconstructible", m_GhostTruth_isReconstructible );
      setBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isDark",            m_GhostTruth_isDark            );
    }
  }

  if ( m_infoSwitch.m_constituentAll ) {
    setBranch<float>                  ( tree, "girth",                         m_girth                         );
    setBranch<float>                  ( tree, "constituentPt",                 m_constituentPt                 );
    setBranch<std::vector<float>>     ( tree, "constituent_dR",                m_constituent_dR                );
    setBranch<std::vector<float>>     ( tree, "constituent_m",                 m_constituent_m                 );
    if ( jet_type == TRUTH || jet_type == DARK ) {
      setBranch<std::vector<int>>     ( tree, "constituent_ID",                m_constituent_ID                );
      setBranch<std::vector<float>>   ( tree, "constituent_charge",            m_constituent_charge            );
      setBranch<std::vector<int>>     ( tree, "constituent_pdgId",             m_constituent_pdgId             );
      setBranch<std::vector<int>>     ( tree, "constituent_status",            m_constituent_status            );
      setBranch<std::vector<int>>     ( tree, "constituent_barcode",           m_constituent_barcode           );
      setBranch<std::vector<uint8_t>> ( tree, "constituent_isStable",          m_constituent_isStable          );
      setBranch<std::vector<uint8_t>> ( tree, "constituent_isInteracting",     m_constituent_isInteracting     );
      setBranch<std::vector<uint8_t>> ( tree, "constituent_isReconstructible", m_constituent_isReconstructible );
      setBranch<std::vector<uint8_t>> ( tree, "constituent_isDark",            m_constituent_isDark            );
      setBranch<std::vector<uint8_t>> ( tree, "constituent_hasProdVtx",        m_constituent_pVtx              );
      setBranch<std::vector<float>>   ( tree, "constituent_prodVtx_r",         m_constituent_pVtx_r            );
      setBranch<std::vector<uint8_t>> ( tree, "constituent_hasDecayVtx",       m_constituent_dVtx              );
      setBranch<std::vector<float>>   ( tree, "constituent_decayVtx_r",        m_constituent_dVtx_r            );
    }
  }
}


void JetContainer :: clear ( )
{
  if ( m_debug ) Info( "EJs::JetContainer::clear()", "clearing branches" );

  m_ID     ->clear();
  m_M      ->clear();
  m_radius ->clear();

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    if ( jet_type == RECO ) {
      m_isTruthMatched      ->clear();
      m_truthMatch_ID       ->clear();
      m_truthMatch_dR       ->clear();
      m_truthMatch_E        ->clear();
      m_truthMatch_M        ->clear();
      m_truthMatch_pt       ->clear();
      m_truthMatch_eta      ->clear();
      m_truthMatch_phi      ->clear();
      m_truthMatch_rapidity ->clear();
      m_truthNonmatch_IDs   ->clear();
      m_truthNonmatch_dRs   ->clear();
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      m_isDarkMatched       ->clear();
      m_darkMatch_ID        ->clear();
      m_darkMatch_dR        ->clear();
      m_darkMatch_E         ->clear();
      m_darkMatch_M         ->clear();
      m_darkMatch_pt        ->clear();
      m_darkMatch_eta       ->clear();
      m_darkMatch_phi       ->clear();
      m_darkMatch_rapidity  ->clear();
      m_darkNonmatch_IDs    ->clear();
      m_darkNonmatch_dRs    ->clear();
    }
    if ( jet_type == DARK ) {
      m_isMatchedToTruth    ->clear();
      m_matchedTruthID      ->clear();
      m_matchedTruthDR      ->clear();
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	m_isMatchedToEMTopo ->clear();
	m_matchedEMTopoID   ->clear();
	m_matchedEMTopoDR   ->clear();
      }
      if ( m_doPFlow ) {
	m_isMatchedToPFlow  ->clear();
	m_matchedPFlowID    ->clear();
	m_matchedPFlowDR    ->clear();
      }
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    m_secVtxCount                                        ->clear();
    m_secVtxPt                                           ->clear();
    m_secVtx_ID                                          ->clear();
    m_secVtx_x                                           ->clear();
    m_secVtx_y                                           ->clear();
    m_secVtx_z                                           ->clear();
    m_secVtx_r                                           ->clear();
    m_secVtx_pt                                          ->clear();
    m_secVtx_eta                                         ->clear();
    m_secVtx_phi                                         ->clear();
    m_secVtx_mass                                        ->clear();
    m_secVtx_chi2                                        ->clear();
    m_secVtx_ntrk                                        ->clear();
    m_secVtx_dR                                          ->clear();
    if ( m_mc ) {
      m_secVtx_closestTruth_isDarkPionDecay              ->clear();
      m_secVtx_closestTruth_isOffdiagDarkPionDecay       ->clear();
      m_secVtx_closestTruth_ID                           ->clear();
      m_secVtx_closestTruth_barcode                      ->clear();
      m_secVtx_closestTruth_distance                     ->clear();
      m_secVtx_maxlinkTruth_isDarkPionDecay              ->clear();
      m_secVtx_maxlinkTruth_isOffdiagDarkPionDecay       ->clear();
      m_secVtx_maxlinkTruth_ID                           ->clear();
      m_secVtx_maxlinkTruth_barcode                      ->clear();
      m_secVtx_maxlinkTruth_score                        ->clear();
      m_secVtx_maxlinkParentTruth_isDarkPionDecay        ->clear();
      m_secVtx_maxlinkParentTruth_isOffdiagDarkPionDecay ->clear();
      m_secVtx_maxlinkParentTruth_ID                     ->clear();
      m_secVtx_maxlinkParentTruth_barcode                ->clear();
      m_secVtx_maxlinkParentTruth_score                  ->clear();
      m_truthVtxCount                                    ->clear();
      m_truthVtxPt                                       ->clear();
      m_truthVtx_isDarkPionDecay                         ->clear();
      m_truthVtx_isOffdiagDarkPionDecay                  ->clear();
      m_truthVtx_ID                                      ->clear();
      m_truthVtx_x                                       ->clear();
      m_truthVtx_y                                       ->clear();
      m_truthVtx_z                                       ->clear();
      m_truthVtx_r                                       ->clear();
      m_truthVtx_pt                                      ->clear();
      m_truthVtx_eta                                     ->clear();
      m_truthVtx_phi                                     ->clear();
      m_truthVtx_mass                                    ->clear();
      m_truthVtx_nOutP                                   ->clear();
      m_truthVtx_barcode                                 ->clear();
      m_truthVtx_dR                                      ->clear();
    }
  }
  
  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    m_trkCount               ->clear();
    m_trkPt                  ->clear();
    m_trk_ID                 ->clear();
    m_trk_qOverP             ->clear();
    m_trk_E                  ->clear();
    m_trk_M                  ->clear();
    m_trk_pt                 ->clear();
    m_trk_eta                ->clear();
    m_trk_phi                ->clear();
    m_trk_d0                 ->clear();
    m_trk_z0                 ->clear();
    m_trk_errd0              ->clear();
    m_trk_errz0              ->clear();
    m_trk_chi2               ->clear();
    m_trk_charge             ->clear();
    m_trk_isSelected         ->clear();
    m_trk_isAssociated       ->clear();
    m_trk_dR                 ->clear();
    if ( m_mc ) {
      m_trk_isTruth          ->clear();
      m_trk_truthProb        ->clear();
      m_trk_truthID          ->clear();
      m_trk_truthBarcode     ->clear();
      m_trk_truthPdgId       ->clear();
      m_tpCount              ->clear();
      m_tpPt                 ->clear();
      m_tp_ID                ->clear();
      m_tp_pt                ->clear();
      m_tp_eta               ->clear();
      m_tp_phi               ->clear();
      m_tp_E                 ->clear();
      m_tp_M                 ->clear();
      m_tp_charge            ->clear();
      m_tp_pdgId             ->clear();
      m_tp_status            ->clear();
      m_tp_barcode           ->clear();
      m_tp_dR                ->clear();
      m_tp_isReco            ->clear();
      m_tp_recoProb          ->clear();
      m_tp_recoID            ->clear();
      m_tp_recoIsSelected    ->clear();
      m_tp_recoIsAssociated  ->clear();
      m_tp_isStable          ->clear();
      m_tp_isInteracting     ->clear();
      m_tp_isReconstructible ->clear();
      m_tp_isDark            ->clear();
    }
  }

  if ( m_infoSwitch.m_ghost ) {
    m_GhostTrack_ID                  ->clear();
    m_GhostTrack_m                   ->clear();
    m_GhostTrack_errd0               ->clear();
    m_GhostTrack_errz0               ->clear();
    m_GhostTrack_chi2                ->clear();
    m_GhostTrack_charge              ->clear();
    m_GhostTrack_isSelected          ->clear();
    m_GhostTrack_isAssociated        ->clear();
    if ( m_mc ) {
      m_GhostTrack_isTruth           ->clear();
      m_GhostTrack_truthProb         ->clear();
      m_GhostTrack_truthID           ->clear();
      m_GhostTrack_truthBarcode      ->clear();
      m_GhostTrack_truthPdgId        ->clear();
      m_GhostTruthCount              ->clear();
      m_GhostTruthPt                 ->clear();
      m_GhostTruth_ID                ->clear();
      m_GhostTruth_pt                ->clear();
      m_GhostTruth_eta               ->clear();
      m_GhostTruth_phi               ->clear();
      m_GhostTruth_e                 ->clear();
      m_GhostTruth_m                 ->clear();
      m_GhostTruth_charge            ->clear();
      m_GhostTruth_pdgId             ->clear();
      m_GhostTruth_status            ->clear();
      m_GhostTruth_barcode           ->clear();
      m_GhostTruth_isReco            ->clear();
      m_GhostTruth_recoProb          ->clear();
      m_GhostTruth_recoID            ->clear();
      m_GhostTruth_recoIsSelected    ->clear();
      m_GhostTruth_recoIsAssociated  ->clear();
      m_GhostTruth_isStable          ->clear();
      m_GhostTruth_isInteracting     ->clear();
      m_GhostTruth_isReconstructible ->clear();
      m_GhostTruth_isDark            ->clear();
    }
  }

  if ( m_infoSwitch.m_constituentAll ) {
    m_girth          ->clear();
    m_constituentPt  ->clear();
    m_constituent_dR ->clear();
    m_constituent_m  ->clear();
    if ( jet_type == TRUTH || jet_type == DARK ) {
      m_constituent_ID                ->clear();
      m_constituent_charge            ->clear();
      m_constituent_pdgId             ->clear();
      m_constituent_status            ->clear();
      m_constituent_barcode           ->clear();
      m_constituent_isStable          ->clear();
      m_constituent_isInteracting     ->clear();
      m_constituent_isReconstructible ->clear();
      m_constituent_isDark            ->clear();
      m_constituent_pVtx              ->clear();
      m_constituent_pVtx_r            ->clear();
      m_constituent_dVtx              ->clear();
      m_constituent_dVtx_r            ->clear();
    }
  }
}


void JetContainer :: FillJet ( const xAOD::Jet* jet, const std::string treeName )
{
  if ( m_debug ) Info( "EJs::JetContainer::FillJet()", "filling branches" );

  std::string jet_str = treeName;
  if ( treeName == "nominal" ) jet_str = "";

  m_ID     ->push_back( AUXDYN( jet, int, "ID" ) );
  m_M      ->push_back( jet->m() / m_units       );
  m_radius ->push_back( jet->getSizeParameter()  );

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    float truthJet_E        = AlgConsts::invalidFloat;
    float truthJet_M        = AlgConsts::invalidFloat;
    float truthJet_pt       = AlgConsts::invalidFloat;
    float truthJet_eta      = AlgConsts::invalidFloat;
    float truthJet_phi      = AlgConsts::invalidFloat;
    float truthJet_rapidity = AlgConsts::invalidFloat;
    float darkJet_E         = AlgConsts::invalidFloat;
    float darkJet_M         = AlgConsts::invalidFloat;
    float darkJet_pt        = AlgConsts::invalidFloat;
    float darkJet_eta       = AlgConsts::invalidFloat;
    float darkJet_phi       = AlgConsts::invalidFloat;
    float darkJet_rapidity  = AlgConsts::invalidFloat;

    // access matched truth jet link
    const xAOD::Jet* truthJet = 0;
    static SG::AuxElement::ConstAccessor<EJsHelper::JetLink_t> truthJetAccess("truthJetMatchLink");
    if ( truthJetAccess.isAvailable( *jet ) ) {
      try {
	const EJsHelper::JetLink_t& truthJetLink = truthJetAccess( *jet );
	truthJet = *truthJetLink;
      } catch(...) {}
    }
    if ( truthJet ) {
      truthJet_E        = truthJet->e()  / m_units;
      truthJet_M        = truthJet->m()  / m_units;
      truthJet_pt       = truthJet->pt() / m_units;
      truthJet_eta      = truthJet->eta();
      truthJet_phi      = truthJet->phi();
      truthJet_rapidity = truthJet->rapidity();
    }

    // access matched truth dark jet link
    const xAOD::Jet* darkJet = 0;
    static SG::AuxElement::ConstAccessor<EJsHelper::JetLink_t> darkJetAccess("darkJetMatchLink");
    if ( darkJetAccess.isAvailable( *jet ) ) {
      try {
	const EJsHelper::JetLink_t& darkJetLink = darkJetAccess( *jet );
	darkJet = *darkJetLink;
      } catch(...) {}
    }
    if ( darkJet ) {
      darkJet_E        = darkJet->e()  / m_units;
      darkJet_M        = darkJet->m()  / m_units;
      darkJet_pt       = darkJet->pt() / m_units;
      darkJet_eta      = darkJet->eta();
      darkJet_phi      = darkJet->phi();
      darkJet_rapidity = darkJet->rapidity();
    }

    if ( jet_type == RECO ) {
      m_isTruthMatched      ->push_back( AUXDYN(    jet, char,   "hasTruthJetMatch"   ) );
      m_truthMatch_ID       ->push_back( AUXDYN(    jet, int,    "truthJetMatchID"    ) );
      m_truthMatch_dR       ->push_back( AUXDYN(    jet, double, "truthJetMatchDR"    ) );
      m_truthMatch_E        ->push_back( truthJet_E                                     );
      m_truthMatch_M        ->push_back( truthJet_M                                     );
      m_truthMatch_pt       ->push_back( truthJet_pt                                    );
      m_truthMatch_eta      ->push_back( truthJet_eta                                   );
      m_truthMatch_phi      ->push_back( truthJet_phi                                   );
      m_truthMatch_rapidity ->push_back( truthJet_rapidity                              );
      m_truthNonmatch_IDs   ->push_back( AUXDYNVEC( jet, int,    "truthJetNoMatchIDs" ) );
      m_truthNonmatch_dRs   ->push_back( AUXDYNVEC( jet, float,  "truthJetNoMatchDRs" ) );
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      m_isDarkMatched       ->push_back( AUXDYN(    jet, char,   "hasDarkJetMatch"    ) );
      m_darkMatch_ID        ->push_back( AUXDYN(    jet, int,    "darkJetMatchID"     ) );
      m_darkMatch_dR        ->push_back( AUXDYN(    jet, double, "darkJetMatchDR"     ) );
      m_darkMatch_E         ->push_back( darkJet_E                                      );
      m_darkMatch_M         ->push_back( darkJet_M                                      );
      m_darkMatch_pt        ->push_back( darkJet_pt                                     );
      m_darkMatch_eta       ->push_back( darkJet_eta                                    );
      m_darkMatch_phi       ->push_back( darkJet_phi                                    );
      m_darkMatch_rapidity  ->push_back( darkJet_rapidity                               );
      m_darkNonmatch_IDs    ->push_back( AUXDYNVEC( jet, int,    "darkJetNoMatchIDs"  ) );
      m_darkNonmatch_dRs    ->push_back( AUXDYNVEC( jet, float,  "darkJetNoMatchDRs"  ) );
    }
    if ( jet_type == DARK ) {
      m_isMatchedToTruth    ->push_back( AUXDYN(    jet, char,   "isTruthMatched"     ) );
      m_matchedTruthID      ->push_back( AUXDYN(    jet, int,    "truthMatchID"       ) );
      m_matchedTruthDR      ->push_back( AUXDYN(    jet, double, "truthMatchDR"       ) );
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	if ( jet->isAvailable<char>("isRecoMatched_EMTopo" + jet_str) ) {
	  m_isMatchedToEMTopo ->push_back( jet->auxdataConst<char>(   "isRecoMatched_EMTopo" + jet_str ) );
	  m_matchedEMTopoID   ->push_back( jet->auxdataConst<int>(    "recoMatchID_EMTopo"   + jet_str ) );
	  m_matchedEMTopoDR   ->push_back( jet->auxdataConst<double>( "recoMatchDR_EMTopo"   + jet_str ) );
	}
	else {
	  m_isMatchedToEMTopo ->push_back( AUXDYN( jet, char,   "isRecoMatched_EMTopo" ) );
	  m_matchedEMTopoID   ->push_back( AUXDYN( jet, int,    "recoMatchID_EMTopo"   ) );
	  m_matchedEMTopoDR   ->push_back( AUXDYN( jet, double, "recoMatchDR_EMTopo"   ) );
	}
      }
      if ( m_doPFlow ) {
	if ( jet->isAvailable<char>("isRecoMatched_PFlow" + jet_str) ) {
	  m_isMatchedToPFlow  ->push_back( jet->auxdataConst<char>(   "isRecoMatched_PFlow" + jet_str  ) );
	  m_matchedPFlowID    ->push_back( jet->auxdataConst<int>(    "recoMatchID_PFlow"   + jet_str  ) );
	  m_matchedPFlowDR    ->push_back( jet->auxdataConst<double>( "recoMatchDR_PFlow"   + jet_str  ) );
	}
	else {
	  m_isMatchedToPFlow  ->push_back( AUXDYN( jet, char,   "isRecoMatched_PFlow"  ) );
	  m_matchedPFlowID    ->push_back( AUXDYN( jet, int,    "recoMatchID_PFlow"    ) );
	  m_matchedPFlowDR    ->push_back( AUXDYN( jet, double, "recoMatchDR_PFlow"    ) );
	}
      }
    }
  }

  
  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    int                  matchDVCount = 0;
    double               matchDVPt    = 0;
    std::vector<int>     matchDV_ID;
    std::vector<float>   matchDV_x;
    std::vector<float>   matchDV_y;
    std::vector<float>   matchDV_z;
    std::vector<float>   matchDV_r;
    std::vector<float>   matchDV_pt;
    std::vector<float>   matchDV_eta;
    std::vector<float>   matchDV_phi;
    std::vector<float>   matchDV_mass;
    std::vector<float>   matchDV_chi2;
    std::vector<int>     matchDV_ntrk;
    std::vector<uint8_t> matchDV_closeTV_isPid;
    std::vector<uint8_t> matchDV_closeTV_isOffPid;
    std::vector<int>     matchDV_closeTV_ID;
    std::vector<int>     matchDV_closeTV_barcode;
    std::vector<float>   matchDV_closeTV_dist;
    std::vector<uint8_t> matchDV_maxTV_isPid;
    std::vector<uint8_t> matchDV_maxTV_isOffPid;
    std::vector<int>     matchDV_maxTV_ID;
    std::vector<int>     matchDV_maxTV_barcode;
    std::vector<float>   matchDV_maxTV_score;
    std::vector<uint8_t> matchDV_maxPTV_isPid;
    std::vector<uint8_t> matchDV_maxPTV_isOffPid;
    std::vector<int>     matchDV_maxPTV_ID;
    std::vector<int>     matchDV_maxPTV_barcode;
    std::vector<float>   matchDV_maxPTV_score;
    int                  matchTVCount = 0;
    double               matchTVPt    = 0;
    std::vector<uint8_t> matchTV_isPid;
    std::vector<uint8_t> matchTV_isOffPid;
    std::vector<int>     matchTV_ID;
    std::vector<float>   matchTV_x;
    std::vector<float>   matchTV_y;
    std::vector<float>   matchTV_z;
    std::vector<float>   matchTV_r;
    std::vector<float>   matchTV_pt;
    std::vector<float>   matchTV_eta;
    std::vector<float>   matchTV_phi;
    std::vector<float>   matchTV_mass;
    std::vector<int>     matchTV_nOutP;
    std::vector<int>     matchTV_barcode;
   
    // access matched secondary vertex links
    static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> matchDVAccess("matchedSecondaryVertexLinks");
    if ( matchDVAccess.isAvailable( *jet ) ) {
      const EJsHelper::VertexLinkVector_t& matchDVLinks = matchDVAccess( *jet );
    
      // loop over matched secondary vertex links
      for ( const auto& dvlink : matchDVLinks ) {
	if ( !dvlink.isValid() ) continue;

	// get vertex pt, eta, phi, mass from four-momentum; get filtered tracks
	TLorentzVector dvP4;
	std::vector<const xAOD::TrackParticle*> filteredTracks;
	EJsHelper::getFilteredTracks( (*dvlink), filteredTracks );
	// grab 4-mom from decorator, if available
	if ( (*dvlink)->isAvailable<TLorentzVector>("sumP4") )
	  dvP4 = (*dvlink)->auxdataConst<TLorentzVector>("sumP4");
	// otherwise, calculate from filtered tracks
	else	
	  dvP4 = VsiBonsai::sumP4( filteredTracks );

	++matchDVCount;
	matchDVPt += dvP4.Pt();
      
	matchDV_ID   .push_back( AUXDYN( (*dvlink), int, "ID" )                   );
	matchDV_x    .push_back( (*dvlink)->x()                                   );
	matchDV_y    .push_back( (*dvlink)->y()                                   );
	matchDV_z    .push_back( (*dvlink)->z()                                   );
	matchDV_r    .push_back( (*dvlink)->position().perp()                     );
	matchDV_pt   .push_back( dvP4.Pt() / m_units                              );
	matchDV_eta  .push_back( dvP4.Eta()                                       );
	matchDV_phi  .push_back( dvP4.Phi()                                       );
	matchDV_mass .push_back( dvP4.M()  / m_units                              );
	matchDV_chi2 .push_back( (*dvlink)->chiSquared() / (*dvlink)->numberDoF() ); 
	matchDV_ntrk .push_back( filteredTracks.size()                            );
      
	// get closest TV link
	uint8_t closeTV_isPid    = AlgConsts::invalidUnsigned;
	uint8_t closeTV_isOffPid = AlgConsts::invalidUnsigned;
	int     closeTV_ID       = AlgConsts::invalidInt;
	int     closeTV_barcode  = AlgConsts::invalidInt;
	static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLink_t> closeTVAccess("closestTruthVertexLink");
	if ( closeTVAccess.isAvailable( **dvlink ) ) {
	  try {
	    const EJsHelper::TruthVertexLink_t& closeTVLink = closeTVAccess( **dvlink );
	    closeTV_isPid    = EJsHelper::selectDarkPion        ( (*closeTVLink) );
	    closeTV_isOffPid = EJsHelper::selectOffdiagDarkPion ( (*closeTVLink) );
	    closeTV_ID       = AUXDYN( (*closeTVLink), int, "ID" );
	    closeTV_barcode  = (*closeTVLink)->barcode();
	  } catch(...) {}
	}
	matchDV_closeTV_isPid    .push_back( closeTV_isPid    );
	matchDV_closeTV_isOffPid .push_back( closeTV_isOffPid );
	matchDV_closeTV_ID       .push_back( closeTV_ID       );
	matchDV_closeTV_barcode  .push_back( closeTV_barcode  );
	matchDV_closeTV_dist     .push_back( AUXDYN( (*dvlink), double, "closestTruthVertex_dist" ) );

	// get max-linked TV link
	uint8_t maxTV_isPid    = AlgConsts::invalidUnsigned;
	uint8_t maxTV_isOffPid = AlgConsts::invalidUnsigned;
	int     maxTV_ID       = AlgConsts::invalidInt;
	int     maxTV_barcode  = AlgConsts::invalidInt;
	static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLink_t> maxTVAccess("maxlinkedTruthVertexLink");
	if ( maxTVAccess.isAvailable( **dvlink ) ) {
	  try {
	    const EJsHelper::TruthVertexLink_t& maxTVLink = maxTVAccess( **dvlink );
	    maxTV_isPid    = EJsHelper::selectDarkPion        ( (*maxTVLink) );
	    maxTV_isOffPid = EJsHelper::selectOffdiagDarkPion ( (*maxTVLink) );
	    maxTV_ID       = AUXDYN( (*maxTVLink), int, "ID" );
	    maxTV_barcode  = (*maxTVLink)->barcode();
	  } catch(...) {}
	}
	matchDV_maxTV_isPid    .push_back( maxTV_isPid    );
	matchDV_maxTV_isOffPid .push_back( maxTV_isOffPid );
	matchDV_maxTV_ID       .push_back( maxTV_ID       );
	matchDV_maxTV_barcode  .push_back( maxTV_barcode  );
	matchDV_maxTV_score    .push_back( AUXDYN( (*dvlink), double, "maxlinkedTruthVertex_score" ) );

	// get max-linked PTV link
	uint8_t maxPTV_isPid    = AlgConsts::invalidUnsigned;
	uint8_t maxPTV_isOffPid = AlgConsts::invalidUnsigned;
	int     maxPTV_ID       = AlgConsts::invalidInt;
	int     maxPTV_barcode  = AlgConsts::invalidInt;
	static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLink_t> maxPTVAccess("maxlinkedParentTruthVertexLink");
	if ( maxPTVAccess.isAvailable( **dvlink ) ) {
	  try {
	    const EJsHelper::TruthVertexLink_t& maxPTVLink = maxPTVAccess( **dvlink );
	    maxPTV_isPid    = EJsHelper::selectDarkPion        ( (*maxPTVLink ) );
	    maxPTV_isOffPid = EJsHelper::selectOffdiagDarkPion ( (*maxPTVLink ) );
	    maxPTV_ID       = AUXDYN( (*maxPTVLink), int, "ID" );
	    maxPTV_barcode  = (*maxPTVLink)->barcode();
	  } catch(...) {}
	}
	matchDV_maxPTV_isPid    .push_back( maxPTV_isPid    );
	matchDV_maxPTV_isOffPid .push_back( maxPTV_isOffPid );
	matchDV_maxPTV_ID       .push_back( maxPTV_ID       );
	matchDV_maxPTV_barcode  .push_back( maxPTV_barcode  );
	matchDV_maxPTV_score    .push_back( AUXDYN( (*dvlink), double, "maxlinkedParentTruthVertex_score" ) );
      
      } // end loop over matched DV links
    
    } // end matched secondary vertex link access

    
    // access matched truth vertex links
    static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLinkVector_t> matchTVAccess("matchedTruthVertexLinks");
    if ( matchTVAccess.isAvailable( *jet ) ) {
      const EJsHelper::TruthVertexLinkVector_t& matchTVLinks = matchTVAccess( *jet );
      // loop over matched truth vertex links
      for ( const auto& tvlink : matchTVLinks ) {
	if ( !tvlink.isValid() ) continue;

	std::vector<const xAOD::TruthParticle*> outParts;
	for ( size_t i = 0; i != (*tvlink)->nOutgoingParticles(); ++i ) {
	  const auto* outP = (*tvlink)->outgoingParticle(i);
	  if ( !outP ) continue;
	  outParts .push_back( outP );
	}
	const TLorentzVector& tvP4 = EJsHelper::truthSumP4( outParts );
	
	++matchTVCount;
	matchTVPt += tvP4.Pt();
	
	matchTV_isPid    .push_back( EJsHelper::selectDarkPion        ( (*tvlink) ) );
	matchTV_isOffPid .push_back( EJsHelper::selectOffdiagDarkPion ( (*tvlink) ) );
	matchTV_ID       .push_back( AUXDYN( (*tvlink), int, "ID" )                 );
	matchTV_x        .push_back( (*tvlink)->x()                                 );
	matchTV_y        .push_back( (*tvlink)->y()                                 );
	matchTV_z        .push_back( (*tvlink)->z()                                 );
	matchTV_r        .push_back( (*tvlink)->perp()                              );
	matchTV_pt       .push_back( tvP4.Pt() / m_units                            );
	matchTV_eta      .push_back( (*tvlink)->eta()                               );
	matchTV_phi      .push_back( (*tvlink)->phi()                               );
	matchTV_mass     .push_back( tvP4.M()  / m_units                            );
	matchTV_nOutP    .push_back( (*tvlink)->nOutgoingParticles()                );
	matchTV_barcode  .push_back( (*tvlink)->barcode()                           );
      }
    }

    m_secVtxCount                                        ->push_back( matchDVCount                                         );
    m_secVtxPt                                           ->push_back( matchDVPt / m_units                                  );
    m_secVtx_ID                                          ->push_back( matchDV_ID                                           );
    m_secVtx_x                                           ->push_back( matchDV_x                                            );
    m_secVtx_y                                           ->push_back( matchDV_y                                            );
    m_secVtx_z                                           ->push_back( matchDV_z                                            );
    m_secVtx_r                                           ->push_back( matchDV_r                                            );
    m_secVtx_pt                                          ->push_back( matchDV_pt                                           );
    m_secVtx_eta                                         ->push_back( matchDV_eta                                          );
    m_secVtx_phi                                         ->push_back( matchDV_phi                                          );
    m_secVtx_mass                                        ->push_back( matchDV_mass                                         );
    m_secVtx_chi2                                        ->push_back( matchDV_chi2                                         );
    m_secVtx_ntrk                                        ->push_back( matchDV_ntrk                                         );
    m_secVtx_dR                                          ->push_back( AUXDYNVEC( jet, float, "matchedSecondaryVertex_dR" ) );
    if ( m_mc ) {
      m_secVtx_closestTruth_isDarkPionDecay              ->push_back( matchDV_closeTV_isPid                                );
      m_secVtx_closestTruth_isOffdiagDarkPionDecay       ->push_back( matchDV_closeTV_isOffPid                             );
      m_secVtx_closestTruth_ID                           ->push_back( matchDV_closeTV_ID                                   );
      m_secVtx_closestTruth_barcode                      ->push_back( matchDV_closeTV_barcode                              );
      m_secVtx_closestTruth_distance                     ->push_back( matchDV_closeTV_dist                                 );
      m_secVtx_maxlinkTruth_isDarkPionDecay              ->push_back( matchDV_maxTV_isPid                                  );
      m_secVtx_maxlinkTruth_isOffdiagDarkPionDecay       ->push_back( matchDV_maxTV_isOffPid                               );
      m_secVtx_maxlinkTruth_ID                           ->push_back( matchDV_maxTV_ID                                     );
      m_secVtx_maxlinkTruth_barcode                      ->push_back( matchDV_maxTV_barcode                                );
      m_secVtx_maxlinkTruth_score                        ->push_back( matchDV_maxTV_score                                  );
      m_secVtx_maxlinkParentTruth_isDarkPionDecay        ->push_back( matchDV_maxPTV_isPid                                 );
      m_secVtx_maxlinkParentTruth_isOffdiagDarkPionDecay ->push_back( matchDV_maxPTV_isOffPid                              );
      m_secVtx_maxlinkParentTruth_ID                     ->push_back( matchDV_maxPTV_ID                                    );
      m_secVtx_maxlinkParentTruth_barcode                ->push_back( matchDV_maxPTV_barcode                               );
      m_secVtx_maxlinkParentTruth_score                  ->push_back( matchDV_maxPTV_score                                 );
      m_truthVtxCount                                    ->push_back( matchTVCount                                         );
      m_truthVtxPt                                       ->push_back( matchTVPt / m_units                                  );
      m_truthVtx_isDarkPionDecay                         ->push_back( matchTV_isPid                                        );
      m_truthVtx_isOffdiagDarkPionDecay                  ->push_back( matchTV_isOffPid                                     );
      m_truthVtx_ID                                      ->push_back( matchTV_ID                                           );
      m_truthVtx_x                                       ->push_back( matchTV_x                                            );
      m_truthVtx_y                                       ->push_back( matchTV_y                                            );
      m_truthVtx_z                                       ->push_back( matchTV_z                                            );
      m_truthVtx_r                                       ->push_back( matchTV_r                                            );
      m_truthVtx_pt                                      ->push_back( matchTV_pt                                           );
      m_truthVtx_eta                                     ->push_back( matchTV_eta                                          );
      m_truthVtx_phi                                     ->push_back( matchTV_phi                                          );
      m_truthVtx_mass                                    ->push_back( matchTV_mass                                         );
      m_truthVtx_nOutP                                   ->push_back( matchTV_nOutP                                        );
      m_truthVtx_barcode                                 ->push_back( matchTV_barcode                                      );
      m_truthVtx_dR                                      ->push_back( AUXDYNVEC( jet, float, "matchedTruthVertex_dR"     ) );
    }
  }

  
  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    int                  trkCount = 0;
    double               trkPt    = 0;
    std::vector<int>     trk_ID;
    std::vector<float>   trk_qOverP;
    std::vector<float>   trk_E;
    std::vector<float>   trk_M;
    std::vector<float>   trk_pt;
    std::vector<float>   trk_eta;
    std::vector<float>   trk_phi;
    std::vector<float>   trk_d0;
    std::vector<float>   trk_z0;
    std::vector<float>   trk_errd0;
    std::vector<float>   trk_errz0;
    std::vector<float>   trk_chi2;
    std::vector<float>   trk_charge;
    std::vector<uint8_t> trk_isSelected;
    std::vector<uint8_t> trk_isAssociated;
    std::vector<uint8_t> trk_isTruth;
    std::vector<float>   trk_truthProb;
    std::vector<int>     trk_truthID;
    std::vector<int>     trk_truthBarcode;
    std::vector<int>     trk_truthPdgId;
    int                  tpCount = 0;
    double               tpPt    = 0;
    std::vector<int>     tp_ID;
    std::vector<float>   tp_pt;
    std::vector<float>   tp_eta;
    std::vector<float>   tp_phi;
    std::vector<float>   tp_E;
    std::vector<float>   tp_M;
    std::vector<float>   tp_charge;
    std::vector<int>     tp_pdgId;
    std::vector<int>     tp_status;
    std::vector<int>     tp_barcode;
    std::vector<uint8_t> tp_isReco;
    std::vector<float>   tp_recoProb;
    std::vector<int>     tp_recoID;
    std::vector<uint8_t> tp_recoIsSelected;
    std::vector<uint8_t> tp_recoIsAssociated;
    std::vector<uint8_t> tp_isStable;
    std::vector<uint8_t> tp_isInteracting;
    std::vector<uint8_t> tp_isReconstructible;
    std::vector<uint8_t> tp_isDark;

    // access matched track links
    static SG::AuxElement::ConstAccessor<EJsHelper::TrackLinkVector_t> trkAccess("matchedTrackLinks");
    if ( trkAccess.isAvailable( *jet ) ) {
      const EJsHelper::TrackLinkVector_t& trkLinks = trkAccess( *jet );
    
      // loop over matched track links
      for ( const auto& trklink : trkLinks ) {
	if ( !trklink.isValid() ) continue;

	++trkCount;
	trkPt += (*trklink)->pt();
	
	trk_ID           .push_back( AUXDYN( (*trklink), int, "ID" )                                               );
	trk_qOverP       .push_back( (*trklink)->qOverP() * m_units                                                );
	trk_E            .push_back( (*trklink)->e()      / m_units                                                );
	trk_M            .push_back( (*trklink)->m()      / m_units                                                );
	trk_pt           .push_back( (*trklink)->pt()     / m_units                                                );
	trk_eta          .push_back( (*trklink)->eta()                                                             );
	trk_phi          .push_back( (*trklink)->phi()                                                             );
	trk_d0           .push_back( (*trklink)->d0()                                                              );
	trk_z0           .push_back( (*trklink)->z0()                                                              ); // xAH saves z0 wrt PV ...
	trk_errd0        .push_back( (*trklink)->definingParametersCovMatrix()(0,0)                                );
	trk_errz0        .push_back( (*trklink)->definingParametersCovMatrix()(1,1)                                );
	trk_chi2         .push_back( (*trklink)->chiSquared() / (*trklink)->numberDoF() / AlgConsts::infinitesimal );
	trk_charge       .push_back( (*trklink)->charge()                                                          );
	trk_isSelected   .push_back( AUXDYN( (*trklink), char, "is_selected"   )                                   );
	trk_isAssociated .push_back( AUXDYN( (*trklink), char, "is_associated" )                                   );
      
	// get linked truth particle
	if ( m_mc ) {
	  bool trackHasTruthLink = false;
	  int  truthID           = AlgConsts::invalidInt;
	  int  truthBarcode      = AlgConsts::invalidInt;
	  int  truthPdgId        = AlgConsts::invalidInt;
	  static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLink_t> truthAccess("truthParticleLink");
	  if ( truthAccess.isAvailable( **trklink ) ) {
	    try {
	      const EJsHelper::TruthParticleLink_t& truthLink = truthAccess( **trklink );
	      if ( (*truthLink) ) trackHasTruthLink = true;
	      truthID      = AUXDYN( (*truthLink), int, "ID" );
	      truthBarcode = (*truthLink)->barcode();
	      truthPdgId   = (*truthLink)->pdgId();
	    } catch(...) {}
	  }
	  trk_isTruth      .push_back( trackHasTruthLink                                        );
	  trk_truthProb    .push_back( (*trklink)->auxdataConst<float>("truthMatchProbability") );
	  trk_truthID      .push_back( truthID                                                  );
	  trk_truthBarcode .push_back( truthBarcode                                             );
	  trk_truthPdgId   .push_back( truthPdgId                                               );
	}
      
      } // end loop over matched track links
    
    } // end matched track link access

    
    // access matched truth particle links
    static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLinkVector_t> tpAccess("matchedTruthParticleLinks");
    if ( tpAccess.isAvailable( *jet ) ) {
      const EJsHelper::TruthParticleLinkVector_t& tpLinks = tpAccess( *jet );
    
      // loop over matched truth particle links
      for ( const auto& tplink : tpLinks ) {
	if ( !tplink.isValid() ) continue;

	++tpCount;
	tpPt += (*tplink)->pt();
	
	tp_ID      .push_back( AUXDYN( (*tplink), int, "ID" ) );
	tp_pt      .push_back( (*tplink)->pt() / m_units      );
	tp_eta     .push_back( (*tplink)->eta()               );
	tp_phi     .push_back( (*tplink)->phi()               );
	tp_E       .push_back( (*tplink)->e()  / m_units      );
	tp_M       .push_back( (*tplink)->m()  / m_units      );
	tp_charge  .push_back( (*tplink)->charge()            );
	tp_pdgId   .push_back( (*tplink)->pdgId()             );
	tp_status  .push_back( (*tplink)->status()            );
	tp_barcode .push_back( (*tplink)->barcode()           );

	// get linked reco particle (track)
	int     recoID      = AlgConsts::invalidInt;
	uint8_t recoIsSel   = AlgConsts::invalidUnsigned;
	uint8_t recoIsAssoc = AlgConsts::invalidUnsigned;
	static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> recoAccess("trackLink");
	if ( recoAccess.isAvailable( **tplink ) ) {
	  try {
	    const EJsHelper::TrackLink_t& recoLink = recoAccess( **tplink );
	    recoID      = AUXDYN( (*recoLink), int,  "ID"            );
	    recoIsSel   = AUXDYN( (*recoLink), char, "is_selected"   );
	    recoIsAssoc = AUXDYN( (*recoLink), char, "is_associated" );
	  } catch(...) {}
	}
	tp_isReco            .push_back( AUXDYN( (*tplink), char,   "isTrackMatch"          ) );
	tp_recoProb          .push_back( AUXDYN( (*tplink), double, "trackMatchProbability" ) );
	tp_recoID            .push_back( recoID                                               );
	tp_recoIsSelected    .push_back( recoIsSel                                            );
	tp_recoIsAssociated  .push_back( recoIsAssoc                                          );
	tp_isStable          .push_back( EJsHelper::isStable          ( (*tplink) )           );
	tp_isInteracting     .push_back( EJsHelper::isInteracting     ( (*tplink) )           );
	tp_isReconstructible .push_back( EJsHelper::isReconstructible ( (*tplink) )           );
	tp_isDark            .push_back( EJsHelper::isDark            ( (*tplink) )           );
  
      } // end loop over matched truth links
    
    } // end matched truth link access

    m_trkCount               ->push_back( trkCount                                           );
    m_trkPt                  ->push_back( trkPt / m_units                                    );
    m_trk_ID                 ->push_back( trk_ID                                             );
    m_trk_qOverP             ->push_back( trk_qOverP                                         );
    m_trk_E                  ->push_back( trk_E                                              );
    m_trk_M                  ->push_back( trk_M                                              );
    m_trk_pt                 ->push_back( trk_pt                                             );
    m_trk_eta                ->push_back( trk_eta                                            );
    m_trk_phi                ->push_back( trk_phi                                            );
    m_trk_d0                 ->push_back( trk_d0                                             );
    m_trk_z0                 ->push_back( trk_z0                                             );
    m_trk_errd0              ->push_back( trk_errd0                                          );
    m_trk_errz0              ->push_back( trk_errz0                                          );
    m_trk_chi2               ->push_back( trk_chi2                                           );
    m_trk_charge             ->push_back( trk_charge                                         );
    m_trk_isSelected         ->push_back( trk_isSelected                                     );
    m_trk_isAssociated       ->push_back( trk_isAssociated                                   );
    m_trk_dR                 ->push_back( AUXDYNVEC( jet, float, "matchedTrack_dR"         ) );
    if ( m_mc ) {
      m_trk_isTruth          ->push_back( trk_isTruth                                        );
      m_trk_truthProb        ->push_back( trk_truthProb                                      );
      m_trk_truthID          ->push_back( trk_truthID                                        );
      m_trk_truthBarcode     ->push_back( trk_truthBarcode                                   );
      m_trk_truthPdgId       ->push_back( trk_truthPdgId                                     );
      m_tpCount              ->push_back( tpCount                                            );
      m_tpPt                 ->push_back( tpPt / m_units                                     );
      m_tp_ID                ->push_back( tp_ID                                              );
      m_tp_pt                ->push_back( tp_pt                                              );
      m_tp_eta               ->push_back( tp_eta                                             );
      m_tp_phi               ->push_back( tp_phi                                             );
      m_tp_E                 ->push_back( tp_E                                               );
      m_tp_M                 ->push_back( tp_M                                               );
      m_tp_charge            ->push_back( tp_charge                                          );
      m_tp_pdgId             ->push_back( tp_pdgId                                           );
      m_tp_status            ->push_back( tp_status                                          );
      m_tp_barcode           ->push_back( tp_barcode                                         );
      m_tp_dR                ->push_back( AUXDYNVEC( jet, float, "matchedTruthParticle_dR" ) );
      m_tp_isReco            ->push_back( tp_isReco                                          );
      m_tp_recoProb          ->push_back( tp_recoProb                                        );
      m_tp_recoID            ->push_back( tp_recoID                                          );
      m_tp_recoIsSelected    ->push_back( tp_recoIsSelected                                  );
      m_tp_recoIsAssociated  ->push_back( tp_recoIsAssociated                                );
      m_tp_isStable          ->push_back( tp_isStable                                        );
      m_tp_isInteracting     ->push_back( tp_isInteracting                                   );
      m_tp_isReconstructible ->push_back( tp_isReconstructible                               );
      m_tp_isDark            ->push_back( tp_isDark                                          );
    }
  }


  if ( m_infoSwitch.m_ghost ) {
    std::vector<int>     ghostTrack_ID;
    std::vector<float>   ghostTrack_m;
    std::vector<float>   ghostTrack_errd0;
    std::vector<float>   ghostTrack_errz0;
    std::vector<float>   ghostTrack_chi2;
    std::vector<float>   ghostTrack_charge;
    std::vector<uint8_t> ghostTrack_isSelected;
    std::vector<uint8_t> ghostTrack_isAssociated;
    std::vector<uint8_t> ghostTrack_isTruth;
    std::vector<float>   ghostTrack_truthProb;
    std::vector<int>     ghostTrack_truthID;
    std::vector<int>     ghostTrack_truthBarcode;
    std::vector<int>     ghostTrack_truthPdgId;
    std::vector<int>     ghostTruth_ID;
    std::vector<float>   ghostTruth_pt;
    std::vector<float>   ghostTruth_eta;
    std::vector<float>   ghostTruth_phi;
    std::vector<float>   ghostTruth_e;
    std::vector<float>   ghostTruth_m;
    std::vector<float>   ghostTruth_charge;
    std::vector<int>     ghostTruth_pdgId;
    std::vector<int>     ghostTruth_status;
    std::vector<int>     ghostTruth_barcode;
    std::vector<uint8_t> ghostTruth_isReco;
    std::vector<float>   ghostTruth_recoProb;
    std::vector<int>     ghostTruth_recoID;
    std::vector<uint8_t> ghostTruth_recoIsSelected;
    std::vector<uint8_t> ghostTruth_recoIsAssociated;
    std::vector<uint8_t> ghostTruth_isStable;
    std::vector<uint8_t> ghostTruth_isInteracting;
    std::vector<uint8_t> ghostTruth_isReconstructible;
    std::vector<uint8_t> ghostTruth_isDark;
    
    // access ghost tracks
    static SG::AuxElement::ConstAccessor<std::vector<ElementLink<DataVector<xAOD::IParticle> > > > ghostTrackAccess("GhostTrack");
    if ( ghostTrackAccess.isAvailable( *jet ) ) {
      std::vector<ElementLink<DataVector<xAOD::IParticle> > > ghostTrackLinks = ghostTrackAccess( *jet );
      for ( const auto& ghosttrklink : ghostTrackLinks ) {
	if ( !ghosttrklink.isValid() ) continue;
	const xAOD::TrackParticle* ghosttrack = dynamic_cast<const xAOD::TrackParticle*>( *ghosttrklink );
	ghostTrack_ID           .push_back( AUXDYN( ghosttrack, int, "ID" )                                               );
	ghostTrack_m            .push_back( ghosttrack->m()  / m_units                                                    );
	ghostTrack_errd0        .push_back( ghosttrack->definingParametersCovMatrix()(0,0)                                );
	ghostTrack_errz0        .push_back( ghosttrack->definingParametersCovMatrix()(1,1)                                );
	ghostTrack_chi2         .push_back( ghosttrack->chiSquared() / ghosttrack->numberDoF() / AlgConsts::infinitesimal );
	ghostTrack_charge       .push_back( ghosttrack->charge()                                                          );
	ghostTrack_isSelected   .push_back( AUXDYN( ghosttrack, char, "is_selected"   )                                   );
	ghostTrack_isAssociated .push_back( AUXDYN( ghosttrack, char, "is_associated" )                                   );
	
	// get linked truth particle
	if ( m_mc ) {
	  bool ghosttrackHasTruthLink = false;
	  int  truthID                = AlgConsts::invalidInt;
	  int  truthBarcode           = AlgConsts::invalidInt;
	  int  truthPdgId             = AlgConsts::invalidInt;
	  static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLink_t> ghosttruthAccess("truthParticleLink");
	  if ( ghosttruthAccess.isAvailable( *ghosttrack ) ) {
	    try {
	      const EJsHelper::TruthParticleLink_t& ghosttruthLink = ghosttruthAccess( *ghosttrack );
	      if ( (*ghosttruthLink) ) ghosttrackHasTruthLink = true;
	      truthID      = AUXDYN( (*ghosttruthLink), int, "ID" );
	      truthBarcode = (*ghosttruthLink)->barcode();
	      truthPdgId   = (*ghosttruthLink)->pdgId(); 
	    } catch(...) {}
	  }
	  ghostTrack_isTruth      .push_back( ghosttrackHasTruthLink                                   );
	  ghostTrack_truthProb    .push_back( ghosttrack->auxdataConst<float>("truthMatchProbability") );
	  ghostTrack_truthID      .push_back( truthID                                                  );
	  ghostTrack_truthBarcode .push_back( truthBarcode                                             );
	  ghostTrack_truthPdgId   .push_back( truthPdgId                                               );
	}
      }
    }

    // access ghost truth particles
    static SG::AuxElement::ConstAccessor<std::vector<ElementLink<DataVector<xAOD::IParticle> > > > ghostTruthAccess("GhostTruth");
    if ( ghostTruthAccess.isAvailable( *jet ) ) {
      std::vector<ElementLink<DataVector<xAOD::IParticle> > > ghostTruthLinks = ghostTruthAccess( *jet );
      for ( const auto& ghostlink : ghostTruthLinks ) {
	if ( !ghostlink.isValid() ) continue;
	const xAOD::TruthParticle* ghosttruth = dynamic_cast<const xAOD::TruthParticle*>( *ghostlink );
	ghostTruth_ID      .push_back( AUXDYN( ghosttruth, int, "ID" ) );
	ghostTruth_pt      .push_back( ghosttruth->pt() / m_units      );
	ghostTruth_eta     .push_back( ghosttruth->eta()               );
	ghostTruth_phi     .push_back( ghosttruth->phi()               );
	ghostTruth_e       .push_back( ghosttruth->e()  / m_units      );
	ghostTruth_m       .push_back( ghosttruth->m()  / m_units      );
	ghostTruth_charge  .push_back( ghosttruth->charge()            );
	ghostTruth_pdgId   .push_back( ghosttruth->pdgId()             );
	ghostTruth_status  .push_back( ghosttruth->status()            );
	ghostTruth_barcode .push_back( ghosttruth->barcode()           );
	
	// get linked reco particle (track)
	int     recoID      = AlgConsts::invalidInt;
	uint8_t recoIsSel   = AlgConsts::invalidUnsigned;
	uint8_t recoIsAssoc = AlgConsts::invalidUnsigned;
	static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> ghostrecoAccess("trackLink");
	if ( ghostrecoAccess.isAvailable( *ghosttruth ) ) {
	  try {
	    const EJsHelper::TrackLink_t& ghostrecoLink = ghostrecoAccess( *ghosttruth );
	    recoID      = AUXDYN( (*ghostrecoLink), int,  "ID"            );
	    recoIsSel   = AUXDYN( (*ghostrecoLink), char, "is_selected"   );
	    recoIsAssoc = AUXDYN( (*ghostrecoLink), char, "is_associated" ); 
	  } catch(...) {}
	}
	ghostTruth_isReco            .push_back( AUXDYN( ghosttruth, char,   "isTrackMatch"          ) );
	ghostTruth_recoProb          .push_back( AUXDYN( ghosttruth, double, "trackMatchProbability" ) );
	ghostTruth_recoID            .push_back( recoID                                                );
	ghostTruth_recoIsSelected    .push_back( recoIsSel                                             );
	ghostTruth_recoIsAssociated  .push_back( recoIsAssoc                                           );
	ghostTruth_isStable          .push_back( EJsHelper::isStable          ( ghosttruth )           );
	ghostTruth_isInteracting     .push_back( EJsHelper::isInteracting     ( ghosttruth )           );
	ghostTruth_isReconstructible .push_back( EJsHelper::isReconstructible ( ghosttruth )           );
	ghostTruth_isDark            .push_back( EJsHelper::isDark            ( ghosttruth )           );	
      }
    }
    
    m_GhostTrack_ID                  ->push_back( ghostTrack_ID                                     );
    m_GhostTrack_m                   ->push_back( ghostTrack_m                                      );
    m_GhostTrack_errd0               ->push_back( ghostTrack_errd0                                  );
    m_GhostTrack_errz0               ->push_back( ghostTrack_errz0                                  );
    m_GhostTrack_chi2                ->push_back( ghostTrack_chi2                                   );
    m_GhostTrack_charge              ->push_back( ghostTrack_charge                                 );
    m_GhostTrack_isSelected          ->push_back( ghostTrack_isSelected                             );
    m_GhostTrack_isAssociated        ->push_back( ghostTrack_isAssociated                           );
    if ( m_mc ) {
      m_GhostTrack_isTruth           ->push_back( ghostTrack_isTruth                                );
      m_GhostTrack_truthProb         ->push_back( ghostTrack_truthProb                              );
      m_GhostTrack_truthID           ->push_back( ghostTrack_truthID                                );
      m_GhostTrack_truthBarcode      ->push_back( ghostTrack_truthBarcode                           );
      m_GhostTrack_truthPdgId        ->push_back( ghostTrack_truthPdgId                             );
      m_GhostTruthCount              ->push_back( AUXDYN( jet, int,   "GhostTruthCount" )           );
      m_GhostTruthPt                 ->push_back( AUXDYN( jet, float, "GhostTruthPt"    ) / m_units );
      m_GhostTruth_ID                ->push_back( ghostTruth_ID                                     );
      m_GhostTruth_pt                ->push_back( ghostTruth_pt                                     );
      m_GhostTruth_eta               ->push_back( ghostTruth_eta                                    );
      m_GhostTruth_phi               ->push_back( ghostTruth_phi                                    );
      m_GhostTruth_e                 ->push_back( ghostTruth_e                                      );
      m_GhostTruth_m                 ->push_back( ghostTruth_m                                      );
      m_GhostTruth_charge            ->push_back( ghostTruth_charge                                 );
      m_GhostTruth_pdgId             ->push_back( ghostTruth_pdgId                                  );
      m_GhostTruth_status            ->push_back( ghostTruth_status                                 );
      m_GhostTruth_barcode           ->push_back( ghostTruth_barcode                                );
      m_GhostTruth_isReco            ->push_back( ghostTruth_isReco                                 );
      m_GhostTruth_recoProb          ->push_back( ghostTruth_recoProb                               );
      m_GhostTruth_recoID            ->push_back( ghostTruth_recoID                                 );
      m_GhostTruth_recoIsSelected    ->push_back( ghostTruth_recoIsSelected                         );
      m_GhostTruth_recoIsAssociated  ->push_back( ghostTruth_recoIsAssociated                       );
      m_GhostTruth_isStable          ->push_back( ghostTruth_isStable                               );
      m_GhostTruth_isInteracting     ->push_back( ghostTruth_isInteracting                          );
      m_GhostTruth_isReconstructible ->push_back( ghostTruth_isReconstructible                      );
      m_GhostTruth_isDark            ->push_back( ghostTruth_isDark                                 );
    }
  }
  

  if ( m_infoSwitch.m_constituentAll ) {
    double               jconstitPtWeightedDR = 0;
    double               constituentPt        = 0;
    std::vector<float>   constituent_dR;
    std::vector<float>   constituent_m;
    std::vector<int>     constituent_ID;
    std::vector<float>   constituent_charge;
    std::vector<int>     constituent_pdgId;
    std::vector<int>     constituent_status;
    std::vector<int>     constituent_barcode;
    std::vector<uint8_t> constituent_isStable;
    std::vector<uint8_t> constituent_isInteracting;
    std::vector<uint8_t> constituent_isReconstructible;
    std::vector<uint8_t> constituent_isDark;
    std::vector<uint8_t> constituent_pVtx;
    std::vector<float>   constituent_pVtx_r;
    std::vector<uint8_t> constituent_dVtx;
    std::vector<float>   constituent_dVtx_r;
    // access constituents
    xAOD::JetConstituentVector jcv = jet->getConstituents();
    if ( jcv.isValid() ) {
      for ( const auto& jconstit : jcv ) {
	double dR = EJsHelper::deltaR( jet->eta(), jconstit->eta(), jet->phi(), jconstit->phi() );
	jconstitPtWeightedDR += dR * jconstit->pt();
	constituentPt        += jconstit->pt();
	constituent_dR .push_back( dR                      );
	constituent_m  .push_back( jconstit->m() / m_units );
	
	if ( jet_type == TRUTH || jet_type == DARK ) {
	  const xAOD::IParticle*     jconstit_ipart = jconstit->rawConstituent();
	  const xAOD::TruthParticle* jconstit_tp    = dynamic_cast<const xAOD::TruthParticle*>(jconstit_ipart);
	  constituent_ID                .push_back( AUXDYN( jconstit_tp, int, "ID"             ) );
	  constituent_charge            .push_back( jconstit_tp->charge()                        );
	  constituent_pdgId             .push_back( jconstit_tp->pdgId()                         );
	  constituent_status            .push_back( jconstit_tp->status()                        );
	  constituent_barcode           .push_back( jconstit_tp->barcode()                       );
	  constituent_isStable          .push_back( EJsHelper::isStable          ( jconstit_tp ) );
	  constituent_isInteracting     .push_back( EJsHelper::isInteracting     ( jconstit_tp ) );
	  constituent_isReconstructible .push_back( EJsHelper::isReconstructible ( jconstit_tp ) );
	  constituent_isDark            .push_back( EJsHelper::isDark            ( jconstit_tp ) );
	  
	  float constit_pVtx_r = AlgConsts::invalidFloat;
	  if ( jconstit_tp->hasProdVtx() )
	    constit_pVtx_r = jconstit_tp->prodVtx()->perp();
	  float constit_dVtx_r = AlgConsts::invalidFloat;
	  if ( jconstit_tp->hasDecayVtx() )
	    constit_dVtx_r = jconstit_tp->decayVtx()->perp();
	  constituent_pVtx   .push_back( jconstit_tp->hasProdVtx()  );
	  constituent_pVtx_r .push_back( constit_pVtx_r             );
	  constituent_dVtx   .push_back( jconstit_tp->hasDecayVtx() );
	  constituent_dVtx_r .push_back( constit_dVtx_r             );
	}
	
      } // end loop over constituents
    }
    
    float girth      = jconstitPtWeightedDR / jet->pt();
    m_girth          ->push_back( girth                   );
    m_constituentPt  ->push_back( constituentPt / m_units ); 
    m_constituent_dR ->push_back( constituent_dR          );
    m_constituent_m  ->push_back( constituent_m           );
    
    if ( jet_type == TRUTH || jet_type == DARK ) {
      m_constituent_ID                ->push_back( constituent_ID                );
      m_constituent_charge            ->push_back( constituent_charge            );
      m_constituent_pdgId             ->push_back( constituent_pdgId             );
      m_constituent_status            ->push_back( constituent_status            );
      m_constituent_barcode           ->push_back( constituent_barcode           );
      m_constituent_isStable          ->push_back( constituent_isStable          );
      m_constituent_isInteracting     ->push_back( constituent_isInteracting     );
      m_constituent_isReconstructible ->push_back( constituent_isReconstructible );
      m_constituent_isDark            ->push_back( constituent_isDark            );
      m_constituent_pVtx              ->push_back( constituent_pVtx              );
      m_constituent_pVtx_r            ->push_back( constituent_pVtx_r            );
      m_constituent_dVtx              ->push_back( constituent_dVtx              );
      m_constituent_dVtx_r            ->push_back( constituent_dVtx_r            );
    }
  }
  
}
