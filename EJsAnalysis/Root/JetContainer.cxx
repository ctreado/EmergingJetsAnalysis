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
  m_index  = new std::vector<int>;
  m_M      = new std::vector<float>;
  m_radius = new std::vector<float>;

  if ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTracks ) {
    m_GhostTrack_ID                 = new std::vector<std::vector<int>>;
    m_GhostTrack_index              = new std::vector<std::vector<int>>;
    m_GhostTrack_m                  = new std::vector<std::vector<float>>;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTrackDetail ) {
      m_GhostTrack_errd0            = new std::vector<std::vector<float>>;
      m_GhostTrack_errz0            = new std::vector<std::vector<float>>;
      m_GhostTrack_chi2             = new std::vector<std::vector<float>>;
      m_GhostTrack_charge           = new std::vector<std::vector<float>>;
      m_GhostTrack_isSelected       = new std::vector<std::vector<uint8_t>>;
      m_GhostTrack_isAssociated     = new std::vector<std::vector<uint8_t>>;
      m_GhostTrack_isSecVtxTrk      = new std::vector<std::vector<uint8_t>>;
      m_GhostTrack_isSecVtxCleanTrk = new std::vector<std::vector<uint8_t>>;
      m_GhostTrack_isSecVtxFiltTrk  = new std::vector<std::vector<uint8_t>>;
      m_GhostTrack_secVtxID         = new std::vector<std::vector<int>>;
      m_GhostTrack_secVtxIndex      = new std::vector<std::vector<int>>;
      if ( m_mc ) {
	m_GhostTrack_isTruth        = new std::vector<std::vector<uint8_t>>;
	m_GhostTrack_truthProb      = new std::vector<std::vector<float>>;
	m_GhostTrack_truthID        = new std::vector<std::vector<int>>;
	m_GhostTrack_truthIndex     = new std::vector<std::vector<int>>;
	m_GhostTrack_truthBarcode   = new std::vector<std::vector<int>>;
	m_GhostTrack_truthPdgId     = new std::vector<std::vector<int>>;
      }
    }
  }
  if ( ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTruth ) && m_mc ) {
    m_GhostTruthCount             = new std::vector<int>;
    m_GhostTruthPt                = new std::vector<float>;
    m_GhostTruth_ID               = new std::vector<std::vector<int>>;
    m_GhostTruth_index            = new std::vector<std::vector<int>>;
    m_GhostTruth_pt               = new std::vector<std::vector<float>>;
    m_GhostTruth_eta              = new std::vector<std::vector<float>>;
    m_GhostTruth_phi              = new std::vector<std::vector<float>>;
    m_GhostTruth_e                = new std::vector<std::vector<float>>;
    m_GhostTruth_m                = new std::vector<std::vector<float>>;
    m_GhostTruth_charge           = new std::vector<std::vector<float>>;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTruthDetail ) {
      m_GhostTruth_pdgId          = new std::vector<std::vector<int>>;
      m_GhostTruth_status         = new std::vector<std::vector<int>>;
      m_GhostTruth_barcode        = new std::vector<std::vector<int>>;
      m_GhostTruth_isReco         = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_isSelected     = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_isAssociated   = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_recoProb       = new std::vector<std::vector<float>>;
      m_GhostTruth_recoID         = new std::vector<std::vector<int>>;
      m_GhostTruth_recoIndex      = new std::vector<std::vector<int>>;
      m_GhostTruth_isStable       = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_isInteracting  = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_isDark         = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_pVtx_llpDecay  = new std::vector<std::vector<std::string>>;
      m_GhostTruth_pVtx_ID        = new std::vector<std::vector<int>>;
      m_GhostTruth_pVtx_index     = new std::vector<std::vector<int>>;
      m_GhostTruth_dVtx_llpDecay  = new std::vector<std::vector<std::string>>;
      m_GhostTruth_dVtx_ID        = new std::vector<std::vector<int>>;
      m_GhostTruth_dVtx_index     = new std::vector<std::vector<int>>;
    }
  }

  if ( m_infoSwitch.m_constituentAll ) {
    m_girth                       = new std::vector<float>;
    m_constituentPt               = new std::vector<float>;
    m_constituent_dR              = new std::vector<std::vector<float>>;
    m_constituent_m               = new std::vector<std::vector<float>>;
    if ( jet_type == TRUTH || jet_type == DARK ) {
      m_constituent_ID            = new std::vector<std::vector<int>>;
      m_constituent_index         = new std::vector<std::vector<int>>;
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_constituentDetail ) {
	m_constituent_charge        = new std::vector<std::vector<float>>;
	m_constituent_pdgId         = new std::vector<std::vector<int>>;
	m_constituent_status        = new std::vector<std::vector<int>>;
	m_constituent_barcode       = new std::vector<std::vector<int>>;
	m_constituent_isStable      = new std::vector<std::vector<uint8_t>>;
	m_constituent_isInteracting = new std::vector<std::vector<uint8_t>>;
	m_constituent_isDark        = new std::vector<std::vector<uint8_t>>;
	m_constituent_pVtx          = new std::vector<std::vector<uint8_t>>;
	m_constituent_pVtx_r        = new std::vector<std::vector<float>>;
	m_constituent_dVtx          = new std::vector<std::vector<uint8_t>>;
	m_constituent_dVtx_r        = new std::vector<std::vector<float>>;
      }
    }
  }

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    if ( jet_type == RECO ) {
      m_isTruthMatched       = new std::vector<uint8_t>;
      m_truthMatch_ID        = new std::vector<int>;
      m_truthMatch_index     = new std::vector<int>;
      m_truthMatch_dR        = new std::vector<float>;
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	m_truthMatch_E       = new std::vector<float>;
	m_truthMatch_M       = new std::vector<float>;
	m_truthMatch_pt      = new std::vector<float>;
	m_truthMatch_eta     = new std::vector<float>;
	m_truthMatch_phi     = new std::vector<float>;
      }
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      m_isDarkMatched        = new std::vector<uint8_t>;
      m_darkMatch_ID         = new std::vector<int>;
      m_darkMatch_index      = new std::vector<int>;
      m_darkMatch_dR         = new std::vector<float>;
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	m_darkMatch_E        = new std::vector<float>;
	m_darkMatch_M        = new std::vector<float>;
	m_darkMatch_pt       = new std::vector<float>;
	m_darkMatch_eta      = new std::vector<float>;
	m_darkMatch_phi      = new std::vector<float>;
      }
    }
    if ( jet_type == DARK ) {
      m_isMatchedToTruth     = new std::vector<uint8_t>;
      m_matchedTruthID       = new std::vector<int>;
      m_matchedTruthIndex    = new std::vector<int>;
      m_matchedTruthDR       = new std::vector<float>;
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	m_isMatchedToEMTopo  = new std::vector<uint8_t>;
	m_matchedEMTopoID    = new std::vector<int>;
	m_matchedEMTopoIndex = new std::vector<int>;
	m_matchedEMTopoDR    = new std::vector<float>;
      }
      if ( m_doPFlow ) {
	m_isMatchedToPFlow   = new std::vector<uint8_t>;
	m_matchedPFlowID     = new std::vector<int>;
	m_matchedPFlowIndex  = new std::vector<int>;
	m_matchedPFlowDR     = new std::vector<float>;
      }
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_recoVerts ) {
    m_secVtxCount                = new std::vector<int>;
    m_secVtx_ID                  = new std::vector<std::vector<int>>;
    m_secVtx_index               = new std::vector<std::vector<int>>;
    m_secVtx_x                   = new std::vector<std::vector<float>>;
    m_secVtx_y                   = new std::vector<std::vector<float>>;
    m_secVtx_z                   = new std::vector<std::vector<float>>;
    m_secVtx_r                   = new std::vector<std::vector<float>>;
    m_secVtx_chi2                = new std::vector<std::vector<float>>;
    m_secVtx_ntrk                = new std::vector<std::vector<int>>;
    m_secVtx_ntrk_clean          = new std::vector<std::vector<int>>;
    m_secVtx_ntrk_filt           = new std::vector<std::vector<int>>;
    m_secVtx_dR                  = new std::vector<std::vector<float>>;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_recoVtxDetail ) {
      m_secVtxPt                 = new std::vector<float>;
      m_secVtxCleanPt            = new std::vector<float>;
      m_secVtxBarePt             = new std::vector<float>;
      m_secVtx_pt                = new std::vector<std::vector<float>>;
      m_secVtx_eta               = new std::vector<std::vector<float>>;
      m_secVtx_phi               = new std::vector<std::vector<float>>;
      m_secVtx_mass              = new std::vector<std::vector<float>>;
      m_secVtx_pt_clean          = new std::vector<std::vector<float>>;
      m_secVtx_eta_clean         = new std::vector<std::vector<float>>;
      m_secVtx_phi_clean         = new std::vector<std::vector<float>>;
      m_secVtx_mass_clean        = new std::vector<std::vector<float>>;
      m_secVtx_pt_bare           = new std::vector<std::vector<float>>;
      m_secVtx_eta_bare          = new std::vector<std::vector<float>>;
      m_secVtx_phi_bare          = new std::vector<std::vector<float>>;
      m_secVtx_mass_bare         = new std::vector<std::vector<float>>;
      m_secVtx_distToPV          = new std::vector<std::vector<float>>;
      m_secVtx_ntrk_sel          = new std::vector<std::vector<int>>;
      m_secVtx_ntrk_assoc        = new std::vector<std::vector<int>>;
      m_secVtx_ntrk_clean_sel    = new std::vector<std::vector<int>>;
      m_secVtx_ntrk_clean_assoc  = new std::vector<std::vector<int>>;
      m_secVtx_ntrk_filt_sel     = new std::vector<std::vector<int>>;
      m_secVtx_ntrk_filt_assoc   = new std::vector<std::vector<int>>;
      m_secVtx_isTruthMatched    = new std::vector<std::vector<uint8_t>>;
    }
  }
  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_truthVerts ) && m_mc ) {
    m_truthVtxCount                = new std::vector<int>;
    m_truthVtx_llpDecay            = new std::vector<std::vector<std::string>>;
    m_truthVtx_ID                  = new std::vector<std::vector<int>>;
    m_truthVtx_index               = new std::vector<std::vector<int>>;
    m_truthVtx_x                   = new std::vector<std::vector<float>>;
    m_truthVtx_y                   = new std::vector<std::vector<float>>;
    m_truthVtx_z                   = new std::vector<std::vector<float>>;
    m_truthVtx_r                   = new std::vector<std::vector<float>>;
    m_truthVtx_nOutP               = new std::vector<std::vector<int>>;
    m_truthVtx_dR                  = new std::vector<std::vector<float>>;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_truthVtxDetail ) {
      m_truthVtxPt                 = new std::vector<float>;
      m_truthVtx_pt                = new std::vector<std::vector<float>>;
      m_truthVtx_eta               = new std::vector<std::vector<float>>;
      m_truthVtx_phi               = new std::vector<std::vector<float>>;
      m_truthVtx_mass              = new std::vector<std::vector<float>>;
      m_truthVtx_barcode           = new std::vector<std::vector<int>>;
      m_truthVtx_isReconstructible = new std::vector<std::vector<uint8_t>>;
      m_truthVtx_isRecoMatched     = new std::vector<std::vector<uint8_t>>;
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    m_trkCount               = new std::vector<int>;
    m_trkPt                  = new std::vector<float>;
    m_trk_ID                 = new std::vector<std::vector<int>>;
    m_trk_index              = new std::vector<std::vector<int>>;
    m_trk_qOverP             = new std::vector<std::vector<float>>;
    m_trk_E                  = new std::vector<std::vector<float>>;
    m_trk_M                  = new std::vector<std::vector<float>>;
    m_trk_pt                 = new std::vector<std::vector<float>>;
    m_trk_eta                = new std::vector<std::vector<float>>;
    m_trk_phi                = new std::vector<std::vector<float>>;
    m_trk_d0                 = new std::vector<std::vector<float>>;
    m_trk_z0                 = new std::vector<std::vector<float>>;
    m_trk_dR                 = new std::vector<std::vector<float>>;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_trackPartDetail ) {
      m_trk_errd0            = new std::vector<std::vector<float>>;
      m_trk_errz0            = new std::vector<std::vector<float>>;
      m_trk_chi2             = new std::vector<std::vector<float>>;
      m_trk_charge           = new std::vector<std::vector<float>>;
      m_trk_isSelected       = new std::vector<std::vector<uint8_t>>;
      m_trk_isAssociated     = new std::vector<std::vector<uint8_t>>;
      m_trk_isSecVtxTrk      = new std::vector<std::vector<uint8_t>>;
      m_trk_isSecVtxCleanTrk = new std::vector<std::vector<uint8_t>>;
      m_trk_isSecVtxFiltTrk  = new std::vector<std::vector<uint8_t>>;
      m_trk_secVtxID         = new std::vector<std::vector<int>>;
      m_trk_secVtxIndex      = new std::vector<std::vector<int>>;
      if ( m_mc ) {
	m_trk_isTruth        = new std::vector<std::vector<uint8_t>>;
	m_trk_truthProb      = new std::vector<std::vector<float>>;
	m_trk_truthID        = new std::vector<std::vector<int>>;
	m_trk_truthIndex     = new std::vector<std::vector<int>>;
	m_trk_truthBarcode   = new std::vector<std::vector<int>>;
	m_trk_truthPdgId     = new std::vector<std::vector<int>>;
      }
    }
  }
  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthParts ) && m_mc ) {
    m_tpCount              = new std::vector<int>;
    m_tpPt                 = new std::vector<float>;
    m_tp_ID                = new std::vector<std::vector<int>>;
    m_tp_index             = new std::vector<std::vector<int>>;
    m_tp_pt                = new std::vector<std::vector<float>>;
    m_tp_eta               = new std::vector<std::vector<float>>;
    m_tp_phi               = new std::vector<std::vector<float>>;
    m_tp_E                 = new std::vector<std::vector<float>>;
    m_tp_M                 = new std::vector<std::vector<float>>;
    m_tp_charge            = new std::vector<std::vector<float>>;
    m_tp_dR                = new std::vector<std::vector<float>>;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthPartDetail ) {
      m_tp_pdgId           = new std::vector<std::vector<int>>;
      m_tp_status          = new std::vector<std::vector<int>>;
      m_tp_barcode         = new std::vector<std::vector<int>>;
      m_tp_isReco          = new std::vector<std::vector<uint8_t>>;
      m_tp_isSelected      = new std::vector<std::vector<uint8_t>>;
      m_tp_isAssociated    = new std::vector<std::vector<uint8_t>>;
      m_tp_recoProb        = new std::vector<std::vector<float>>;
      m_tp_recoID          = new std::vector<std::vector<int>>;
      m_tp_recoIndex       = new std::vector<std::vector<int>>;
      m_tp_isStable        = new std::vector<std::vector<uint8_t>>;
      m_tp_isInteracting   = new std::vector<std::vector<uint8_t>>;
      m_tp_isDark          = new std::vector<std::vector<uint8_t>>;
      m_tp_pVtx_llpDecay   = new std::vector<std::vector<std::string>>;
      m_tp_pVtx_ID         = new std::vector<std::vector<int>>;
      m_tp_pVtx_index      = new std::vector<std::vector<int>>;
      m_tp_dVtx_llpDecay   = new std::vector<std::vector<std::string>>;
      m_tp_dVtx_ID         = new std::vector<std::vector<int>>;
      m_tp_dVtx_index      = new std::vector<std::vector<int>>;
    }
  }
}


JetContainer :: ~JetContainer ()
{
  if ( m_debug ) Info( "EJs::JetContainer()", "deleting" );

  delete m_ID;
  delete m_index;
  delete m_M;
  delete m_radius;

  if ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTracks ) {
    delete m_GhostTrack_ID;
    delete m_GhostTrack_index;
    delete m_GhostTrack_m;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTrackDetail ) {
      delete m_GhostTrack_errd0;
      delete m_GhostTrack_errz0;
      delete m_GhostTrack_chi2;
      delete m_GhostTrack_charge;
      delete m_GhostTrack_isSelected;
      delete m_GhostTrack_isAssociated;
      delete m_GhostTrack_isSecVtxTrk;
      delete m_GhostTrack_isSecVtxCleanTrk;
      delete m_GhostTrack_isSecVtxFiltTrk;
      delete m_GhostTrack_secVtxID;
      delete m_GhostTrack_secVtxIndex;
      if ( m_mc ) {
	delete m_GhostTrack_isTruth;
	delete m_GhostTrack_truthProb;
	delete m_GhostTrack_truthID;
	delete m_GhostTrack_truthIndex;
	delete m_GhostTrack_truthBarcode;
	delete m_GhostTrack_truthPdgId;
      }
    }
  }
  if ( ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTruth ) && m_mc ) {
    delete m_GhostTruthCount;
    delete m_GhostTruthPt;
    delete m_GhostTruth_ID;
    delete m_GhostTruth_index;
    delete m_GhostTruth_pt;
    delete m_GhostTruth_eta; 
    delete m_GhostTruth_phi;
    delete m_GhostTruth_e;
    delete m_GhostTruth_m;
    delete m_GhostTruth_charge;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTruthDetail ) {
      delete m_GhostTruth_pdgId;
      delete m_GhostTruth_status;
      delete m_GhostTruth_barcode;
      delete m_GhostTruth_isReco;
      delete m_GhostTruth_isSelected;
      delete m_GhostTruth_isAssociated;
      delete m_GhostTruth_recoProb;
      delete m_GhostTruth_recoID;
      delete m_GhostTruth_recoIndex;
      delete m_GhostTruth_isStable;
      delete m_GhostTruth_isInteracting;
      delete m_GhostTruth_isDark;
      delete m_GhostTruth_pVtx_llpDecay;
      delete m_GhostTruth_pVtx_ID;
      delete m_GhostTruth_pVtx_index;
      delete m_GhostTruth_dVtx_llpDecay;
      delete m_GhostTruth_dVtx_ID;
      delete m_GhostTruth_dVtx_index;
    }
  }

  if ( m_infoSwitch.m_constituentAll ) {
    delete m_girth;
    delete m_constituentPt;
    delete m_constituent_dR;
    delete m_constituent_m;
    if ( jet_type == TRUTH || jet_type == DARK ) {
      delete m_constituent_ID;
      delete m_constituent_index;
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_constituentDetail ) {
	delete m_constituent_charge;
	delete m_constituent_pdgId;
	delete m_constituent_status;
	delete m_constituent_barcode;
	delete m_constituent_isStable;
	delete m_constituent_isInteracting;
	delete m_constituent_isDark;
	delete m_constituent_pVtx;
	delete m_constituent_pVtx_r;
	delete m_constituent_dVtx;
	delete m_constituent_dVtx_r;
      }
    }
  }

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    if ( jet_type == RECO ) {
      delete m_isTruthMatched;
      delete m_truthMatch_ID;
      delete m_truthMatch_index;
      delete m_truthMatch_dR;
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	delete m_truthMatch_E;
	delete m_truthMatch_M;
	delete m_truthMatch_pt;
	delete m_truthMatch_eta;
	delete m_truthMatch_phi;
      }
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      delete m_isDarkMatched;
      delete m_darkMatch_ID;
      delete m_darkMatch_index;
      delete m_darkMatch_dR;
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	delete m_darkMatch_E;
	delete m_darkMatch_M;
	delete m_darkMatch_pt;
	delete m_darkMatch_eta;
	delete m_darkMatch_phi;
      }
    }
    if ( jet_type == DARK ) {
      delete m_isMatchedToTruth;
      delete m_matchedTruthID;
      delete m_matchedTruthIndex;
      delete m_matchedTruthDR;
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	delete m_isMatchedToEMTopo;
	delete m_matchedEMTopoID;
	delete m_matchedEMTopoIndex;
	delete m_matchedEMTopoDR;
      }
      if ( m_doPFlow ) {
	delete m_isMatchedToPFlow;
	delete m_matchedPFlowID;
	delete m_matchedPFlowIndex;
	delete m_matchedPFlowDR;
      }
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_recoVerts ) {
    delete m_secVtxCount;
    delete m_secVtx_ID;
    delete m_secVtx_index;
    delete m_secVtx_x;
    delete m_secVtx_y;
    delete m_secVtx_z;
    delete m_secVtx_r;
    delete m_secVtx_chi2;
    delete m_secVtx_ntrk;
    delete m_secVtx_ntrk_clean;
    delete m_secVtx_ntrk_filt;
    delete m_secVtx_dR;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_recoVtxDetail ) {
      delete m_secVtxPt;
      delete m_secVtxCleanPt;
      delete m_secVtxBarePt;
      delete m_secVtx_pt;
      delete m_secVtx_eta;
      delete m_secVtx_phi;
      delete m_secVtx_mass;
      delete m_secVtx_pt_clean;
      delete m_secVtx_eta_clean;
      delete m_secVtx_phi_clean;
      delete m_secVtx_mass_clean;
      delete m_secVtx_pt_bare;
      delete m_secVtx_eta_bare;
      delete m_secVtx_phi_bare;
      delete m_secVtx_mass_bare;
      delete m_secVtx_distToPV;
      delete m_secVtx_ntrk_sel;
      delete m_secVtx_ntrk_assoc;
      delete m_secVtx_ntrk_clean_sel;
      delete m_secVtx_ntrk_clean_assoc;
      delete m_secVtx_ntrk_filt_sel;
      delete m_secVtx_ntrk_filt_assoc;
      delete m_secVtx_isTruthMatched;
    }
  }
  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_truthVerts ) && m_mc ) {
    delete m_truthVtxCount;
    delete m_truthVtx_llpDecay;
    delete m_truthVtx_ID;
    delete m_truthVtx_index;
    delete m_truthVtx_x;
    delete m_truthVtx_y;
    delete m_truthVtx_z;
    delete m_truthVtx_r;
    delete m_truthVtx_nOutP;
    delete m_truthVtx_dR;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_truthVtxDetail ) {
      delete m_truthVtxPt;
      delete m_truthVtx_pt;
      delete m_truthVtx_eta;
      delete m_truthVtx_phi;
      delete m_truthVtx_mass;
      delete m_truthVtx_barcode;
      delete m_truthVtx_isReconstructible;
      delete m_truthVtx_isRecoMatched;
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    delete m_trkCount;
    delete m_trkPt;
    delete m_trk_ID;
    delete m_trk_index;
    delete m_trk_qOverP;
    delete m_trk_E;
    delete m_trk_M;
    delete m_trk_pt;
    delete m_trk_eta;
    delete m_trk_phi;
    delete m_trk_d0;
    delete m_trk_z0;
    delete m_trk_dR;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_trackPartDetail ) {
      delete m_trk_errd0;
      delete m_trk_errz0;
      delete m_trk_chi2;
      delete m_trk_charge;
      delete m_trk_isSelected;
      delete m_trk_isAssociated;
      delete m_trk_isSecVtxTrk;
      delete m_trk_isSecVtxCleanTrk;
      delete m_trk_isSecVtxFiltTrk;
      delete m_trk_secVtxID;
      delete m_trk_secVtxIndex;
      if ( m_mc ) {
	delete m_trk_isTruth;
	delete m_trk_truthProb;
	delete m_trk_truthID;
	delete m_trk_truthIndex;
	delete m_trk_truthBarcode;
	delete m_trk_truthPdgId;
      }
    }
  }
  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthParts ) && m_mc ) {
    delete m_tpCount;
    delete m_tpPt;
    delete m_tp_ID;
    delete m_tp_index;
    delete m_tp_pt;
    delete m_tp_eta;
    delete m_tp_phi;
    delete m_tp_E ;
    delete m_tp_M;
    delete m_tp_charge;
    delete m_tp_dR;
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthPartDetail ) {
      delete m_tp_pdgId;
      delete m_tp_status;
      delete m_tp_barcode;
      delete m_tp_isReco;
      delete m_tp_isSelected;
      delete m_tp_isAssociated;
      delete m_tp_recoProb;
      delete m_tp_recoID;
      delete m_tp_recoIndex;
      delete m_tp_isStable;
      delete m_tp_isInteracting;
      delete m_tp_isDark;
      delete m_tp_pVtx_llpDecay;
      delete m_tp_pVtx_ID;
      delete m_tp_pVtx_index;
      delete m_tp_dVtx_llpDecay;
      delete m_tp_dVtx_ID;
      delete m_tp_dVtx_index;
    }
  }
}


void JetContainer :: setTree ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::JetContainer::setTree()", "setting tree" );

  connectBranch<int>   ( tree, "ID",     &m_ID     );
  connectBranch<int>   ( tree, "index",  &m_index  );
  connectBranch<float> ( tree, "M",      &m_M      );
  connectBranch<float> ( tree, "radius", &m_radius );

  if ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTracks ) {
    connectBranch<std::vector<int>>         ( tree, "GhostTrack_ID",               &m_GhostTrack_ID               );
    connectBranch<std::vector<int>>         ( tree, "GhostTrack_index",            &m_GhostTrack_index            );
    connectBranch<std::vector<float>>       ( tree, "GhostTrack_m",                &m_GhostTrack_m                );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTrackDetail ) {
      connectBranch<std::vector<float>>     ( tree, "GhostTrack_errd0",            &m_GhostTrack_errd0            );
      connectBranch<std::vector<float>>     ( tree, "GhostTrack_errz0",            &m_GhostTrack_errz0            );
      connectBranch<std::vector<float>>     ( tree, "GhostTrack_chi2",             &m_GhostTrack_chi2             );
      connectBranch<std::vector<float>>     ( tree, "GhostTrack_charge",           &m_GhostTrack_charge           );
      connectBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSelected",       &m_GhostTrack_isSelected       );
      connectBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isAssociated",     &m_GhostTrack_isAssociated     );
      connectBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSecVtxTrk",      &m_GhostTrack_isSecVtxTrk      );
      connectBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSecVtxCleanTrk", &m_GhostTrack_isSecVtxCleanTrk );
      connectBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSecVtxFiltTrk",  &m_GhostTrack_isSecVtxFiltTrk  );
      connectBranch<std::vector<int>>       ( tree, "GhostTrack_secVtxID",         &m_GhostTrack_secVtxID         );
      connectBranch<std::vector<int>>       ( tree, "GhostTrack_secVtxIndex",      &m_GhostTrack_secVtxIndex      );
      if ( m_mc ) {
	connectBranch<std::vector<uint8_t>> ( tree, "GhostTrack_isTruth",          &m_GhostTrack_isTruth          );
	connectBranch<std::vector<float>>   ( tree, "GhostTrack_truthProb",        &m_GhostTrack_truthProb        );
	connectBranch<std::vector<int>>     ( tree, "GhostTrack_truthID",          &m_GhostTrack_truthID          );
	connectBranch<std::vector<int>>     ( tree, "GhostTrack_truthIndex",       &m_GhostTrack_truthIndex       );
	connectBranch<std::vector<int>>     ( tree, "GhostTrack_truthBarcode",     &m_GhostTrack_truthBarcode     );
	connectBranch<std::vector<int>>     ( tree, "GhostTrack_truthPdgId",       &m_GhostTrack_truthPdgId       );
      }
    }
  }
  if ( ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTruth ) && m_mc ) {
    connectBranch<int>                        ( tree, "GhostTruthCount",          &m_GhostTruthCount          );
    connectBranch<float>                      ( tree, "GhostTruthPt",             &m_GhostTruthPt             );
    connectBranch<std::vector<int>>           ( tree, "GhostTruth_ID",            &m_GhostTruth_ID            );
    connectBranch<std::vector<int>>           ( tree, "GhostTruth_index",         &m_GhostTruth_index         );
    connectBranch<std::vector<float>>         ( tree, "GhostTruth_pt",            &m_GhostTruth_pt            );
    connectBranch<std::vector<float>>         ( tree, "GhostTruth_eta",           &m_GhostTruth_eta           );
    connectBranch<std::vector<float>>         ( tree, "GhostTruth_phi",           &m_GhostTruth_phi           );
    connectBranch<std::vector<float>>         ( tree, "GhostTruth_e",             &m_GhostTruth_e             );
    connectBranch<std::vector<float>>         ( tree, "GhostTruth_m",             &m_GhostTruth_m             );
    connectBranch<std::vector<float>>         ( tree, "GhostTruth_charge",        &m_GhostTruth_charge        );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTruthDetail ) {
      connectBranch<std::vector<int>>         ( tree, "GhostTruth_pdgId",         &m_GhostTruth_pdgId         );
      connectBranch<std::vector<int>>         ( tree, "GhostTruth_status",        &m_GhostTruth_status        );
      connectBranch<std::vector<int>>         ( tree, "GhostTruth_barcode",       &m_GhostTruth_barcode       );
      connectBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isReco",        &m_GhostTruth_isReco        );
      connectBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isSelected",    &m_GhostTruth_isSelected    );
      connectBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isAssociated",  &m_GhostTruth_isAssociated  );
      connectBranch<std::vector<float>>       ( tree, "GhostTruth_recoProb",      &m_GhostTruth_recoProb      );
      connectBranch<std::vector<int>>         ( tree, "GhostTruth_recoID",        &m_GhostTruth_recoID        );
      connectBranch<std::vector<int>>         ( tree, "GhostTruth_recoIndex",     &m_GhostTruth_recoIndex     );
      connectBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isStable",      &m_GhostTruth_isStable      );
      connectBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isInteracting", &m_GhostTruth_isInteracting );
      connectBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isDark",        &m_GhostTruth_isDark        );
      connectBranch<std::vector<std::string>> ( tree, "GhostTruth_pVtx_llpDecay", &m_GhostTruth_pVtx_llpDecay );
      connectBranch<std::vector<int>>         ( tree, "GhostTruth_pVtx_ID",       &m_GhostTruth_pVtx_ID       );
      connectBranch<std::vector<int>>         ( tree, "GhostTruth_pVtx_index",    &m_GhostTruth_pVtx_index    );
      connectBranch<std::vector<std::string>> ( tree, "GhostTruth_dVtx_llpDecay", &m_GhostTruth_dVtx_llpDecay );
      connectBranch<std::vector<int>>         ( tree, "GhostTruth_dVtx_ID",       &m_GhostTruth_dVtx_ID       );
      connectBranch<std::vector<int>>         ( tree, "GhostTruth_dVtx_index",    &m_GhostTruth_dVtx_index    );
    }
  }
    
  if ( m_infoSwitch.m_constituentAll ) {
    connectBranch<float>                    ( tree, "girth",                     &m_girth                     );
    connectBranch<float>                    ( tree, "constituentPt",             &m_constituentPt             );
    connectBranch<std::vector<float>>       ( tree, "constituent_dR",            &m_constituent_dR            );
    connectBranch<std::vector<float>>       ( tree, "constituent_m",             &m_constituent_m             );
    if ( jet_type == TRUTH || jet_type == DARK ) {
      connectBranch<std::vector<int>>       ( tree, "constituent_ID",            &m_constituent_ID            );
      connectBranch<std::vector<int>>       ( tree, "constituent_index",         &m_constituent_index         );
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_constituentDetail ) {
	connectBranch<std::vector<float>>   ( tree, "constituent_charge",        &m_constituent_charge        );
	connectBranch<std::vector<int>>     ( tree, "constituent_pdgId",         &m_constituent_pdgId         );
	connectBranch<std::vector<int>>     ( tree, "constituent_status",        &m_constituent_status        );
	connectBranch<std::vector<int>>     ( tree, "constituent_barcode",       &m_constituent_barcode       );
	connectBranch<std::vector<uint8_t>> ( tree, "constituent_isStable",      &m_constituent_isStable      );
	connectBranch<std::vector<uint8_t>> ( tree, "constituent_isInteracting", &m_constituent_isInteracting );
	connectBranch<std::vector<uint8_t>> ( tree, "constituent_isDark",        &m_constituent_isDark        );
	connectBranch<std::vector<uint8_t>> ( tree, "constituent_hasProdVtx",    &m_constituent_pVtx          );
	connectBranch<std::vector<float>>   ( tree, "constituent_prodVtx_r",     &m_constituent_pVtx_r        );
	connectBranch<std::vector<uint8_t>> ( tree, "constituent_hasDecayVtx",   &m_constituent_dVtx          );
	connectBranch<std::vector<float>>   ( tree, "constituent_decayVtx_r",    &m_constituent_dVtx_r        );
      }
    }
  }

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    if ( jet_type == RECO ) {
      connectBranch<uint8_t>   ( tree, "isTruthMatched",     &m_isTruthMatched     );
      connectBranch<int>       ( tree, "truthMatch_ID",      &m_truthMatch_ID      );
      connectBranch<int>       ( tree, "truthMatch_index",   &m_truthMatch_index   );
      connectBranch<float>     ( tree, "truthMatch_dR",      &m_truthMatch_dR      );
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	connectBranch<float>   ( tree, "truthMatch_E",       &m_truthMatch_E       );
	connectBranch<float>   ( tree, "truthMatch_M",       &m_truthMatch_M       );
	connectBranch<float>   ( tree, "truthMatch_pt",      &m_truthMatch_pt      );
	connectBranch<float>   ( tree, "truthMatch_eta",     &m_truthMatch_eta     );
	connectBranch<float>   ( tree, "truthMatch_phi",     &m_truthMatch_phi     );
      }
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      connectBranch<uint8_t>   ( tree, "isDarkMatched",      &m_isDarkMatched      );
      connectBranch<int>       ( tree, "darkMatch_ID",       &m_darkMatch_ID       );
      connectBranch<int>       ( tree, "darkMatch_index",    &m_darkMatch_index    );
      connectBranch<float>     ( tree, "darkMatch_dR",       &m_darkMatch_dR       );
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	connectBranch<float>   ( tree, "darkMatch_E",        &m_darkMatch_E        );
	connectBranch<float>   ( tree, "darkMatch_M",        &m_darkMatch_M        );
	connectBranch<float>   ( tree, "darkMatch_pt",       &m_darkMatch_pt       );
	connectBranch<float>   ( tree, "darkMatch_eta",      &m_darkMatch_eta      );
	connectBranch<float>   ( tree, "darkMatch_phi",      &m_darkMatch_phi      );
      }
    }
    if ( jet_type == DARK ) {
      connectBranch<uint8_t>   ( tree, "isMatchedToTruth",   &m_isMatchedToTruth   );
      connectBranch<int>       ( tree, "matchedTruthID",     &m_matchedTruthID     );
      connectBranch<int>       ( tree, "matchedTruthIndex",  &m_matchedTruthIndex  );
      connectBranch<float>     ( tree, "matchedTruthDR",     &m_matchedTruthDR     );
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	connectBranch<uint8_t> ( tree, "isMatchedToEMTopo",  &m_isMatchedToEMTopo  );
	connectBranch<int>     ( tree, "matchedEMTopoID",    &m_matchedEMTopoID    );
	connectBranch<int>     ( tree, "matchedEMTopoIndex", &m_matchedEMTopoIndex );
	connectBranch<float>   ( tree, "matchedEMTopoDR",    &m_matchedEMTopoDR    );
      }
      if ( m_doPFlow ) {
	connectBranch<uint8_t> ( tree, "isMatchedToPFlow",   &m_isMatchedToPFlow   );
	connectBranch<int>     ( tree, "matchedPFlowID",     &m_matchedPFlowID     );
	connectBranch<int>     ( tree, "matchedPFlowIndex",  &m_matchedPFlowIndex  );
	connectBranch<float>   ( tree, "matchedPFlowDR",     &m_matchedPFlowDR     );
      }
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_recoVerts ) {
    connectBranch<int>                      ( tree, "secVtxCount",                &m_secVtxCount                );
    connectBranch<std::vector<int>>         ( tree, "secVtx_ID",                  &m_secVtx_ID                  );
    connectBranch<std::vector<int>>         ( tree, "secVtx_index",               &m_secVtx_index               );
    connectBranch<std::vector<float>>       ( tree, "secVtx_x",                   &m_secVtx_x                   );
    connectBranch<std::vector<float>>       ( tree, "secVtx_y",                   &m_secVtx_y                   );
    connectBranch<std::vector<float>>       ( tree, "secVtx_z",                   &m_secVtx_z                   );
    connectBranch<std::vector<float>>       ( tree, "secVtx_r",                   &m_secVtx_r                   );
    connectBranch<std::vector<float>>       ( tree, "secVtx_chi2",                &m_secVtx_chi2                );
    connectBranch<std::vector<int>>         ( tree, "secVtx_ntrk",                &m_secVtx_ntrk                );
    connectBranch<std::vector<int>>         ( tree, "secVtx_ntrk_clean",          &m_secVtx_ntrk_clean          );
    connectBranch<std::vector<int>>         ( tree, "secVtx_ntrk_filt",           &m_secVtx_ntrk_filt           );
    connectBranch<std::vector<float>>       ( tree, "secVtx_dR",                  &m_secVtx_dR                  );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_recoVtxDetail ) {
      connectBranch<float>                  ( tree, "secVtxPt",                   &m_secVtxPt                   );
      connectBranch<float>                  ( tree, "secVtxCleanPt",              &m_secVtxCleanPt              );
      connectBranch<float>                  ( tree, "secVtxBarePt",               &m_secVtxBarePt               );
      connectBranch<std::vector<float>>     ( tree, "secVtx_pt",                  &m_secVtx_pt                  );
      connectBranch<std::vector<float>>     ( tree, "secVtx_eta",                 &m_secVtx_eta                 );
      connectBranch<std::vector<float>>     ( tree, "secVtx_phi",                 &m_secVtx_phi                 );
      connectBranch<std::vector<float>>     ( tree, "secVtx_mass",                &m_secVtx_mass                );
      connectBranch<std::vector<float>>     ( tree, "secVtx_pt_clean",            &m_secVtx_pt_clean            );
      connectBranch<std::vector<float>>     ( tree, "secVtx_eta_clean",           &m_secVtx_eta_clean           );
      connectBranch<std::vector<float>>     ( tree, "secVtx_phi_clean",           &m_secVtx_phi_clean           );
      connectBranch<std::vector<float>>     ( tree, "secVtx_mass_clean",          &m_secVtx_mass_clean          );
      connectBranch<std::vector<float>>     ( tree, "secVtx_pt_bare",             &m_secVtx_pt_bare             );
      connectBranch<std::vector<float>>     ( tree, "secVtx_eta_bare",            &m_secVtx_eta_bare            );
      connectBranch<std::vector<float>>     ( tree, "secVtx_phi_bare",            &m_secVtx_phi_bare            );
      connectBranch<std::vector<float>>     ( tree, "secVtx_mass_bare",           &m_secVtx_mass_bare           );
      connectBranch<std::vector<float>>     ( tree, "secVtx_distToPV",            &m_secVtx_distToPV            );
      connectBranch<std::vector<int>>       ( tree, "secVtx_ntrk_sel",            &m_secVtx_ntrk_sel            );
      connectBranch<std::vector<int>>       ( tree, "secVtx_ntrk_assoc",          &m_secVtx_ntrk_assoc          );
      connectBranch<std::vector<int>>       ( tree, "secVtx_ntrk_clean_sel",      &m_secVtx_ntrk_clean_sel      );
      connectBranch<std::vector<int>>       ( tree, "secVtx_ntrk_clean_assoc",    &m_secVtx_ntrk_clean_assoc    );
      connectBranch<std::vector<int>>       ( tree, "secVtx_ntrk_filt_sel",       &m_secVtx_ntrk_filt_sel       );
      connectBranch<std::vector<int>>       ( tree, "secVtx_ntrk_filt_assoc",     &m_secVtx_ntrk_filt_assoc     );
      connectBranch<std::vector<uint8_t>>   ( tree, "secVtx_isTruthMatched",      &m_secVtx_isTruthMatched      );
    }
  }
  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_truthVerts ) && m_mc ) {
    connectBranch<int>                      ( tree, "truthVtxCount",              &m_truthVtxCount              );
    connectBranch<std::vector<std::string>> ( tree, "truthVtx_llpDecay",          &m_truthVtx_llpDecay          );
    connectBranch<std::vector<int>>         ( tree, "truthVtx_ID",                &m_truthVtx_ID                );
    connectBranch<std::vector<int>>         ( tree, "truthVtx_index",             &m_truthVtx_index             );
    connectBranch<std::vector<float>>       ( tree, "truthVtx_x",                 &m_truthVtx_x                 );
    connectBranch<std::vector<float>>       ( tree, "truthVtx_y",                 &m_truthVtx_y                 );
    connectBranch<std::vector<float>>       ( tree, "truthVtx_z",                 &m_truthVtx_z                 );
    connectBranch<std::vector<float>>       ( tree, "truthVtx_r",                 &m_truthVtx_r                 );
    connectBranch<std::vector<int>>         ( tree, "truthVtx_nOutP",             &m_truthVtx_nOutP             );
    connectBranch<std::vector<float>>       ( tree, "truthVtx_dR",                &m_truthVtx_dR                );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_truthVtxDetail ) {
      connectBranch<float>                  ( tree, "truthVtxPt",                 &m_truthVtxPt                 );
      connectBranch<std::vector<float>>     ( tree, "truthVtx_pt",                &m_truthVtx_pt                );
      connectBranch<std::vector<float>>     ( tree, "truthVtx_eta",               &m_truthVtx_eta               );
      connectBranch<std::vector<float>>     ( tree, "truthVtx_phi",               &m_truthVtx_phi               );
      connectBranch<std::vector<float>>     ( tree, "truthVtx_mass",              &m_truthVtx_mass              );
      connectBranch<std::vector<int>>       ( tree, "truthVtx_barcode",           &m_truthVtx_barcode           );
      connectBranch<std::vector<uint8_t>>   ( tree, "truthVtx_isReconstructible", &m_truthVtx_isReconstructible );
      connectBranch<std::vector<uint8_t>>   ( tree, "truthVtx_isRecoMatched",     &m_truthVtx_isRecoMatched     );
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    connectBranch<int>                      ( tree, "trkCount",             &m_trkCount             );
    connectBranch<float>                    ( tree, "trkPt",                &m_trkPt                );
    connectBranch<std::vector<int>>         ( tree, "trk_ID",               &m_trk_ID               );
    connectBranch<std::vector<int>>         ( tree, "trk_index",            &m_trk_index            );
    connectBranch<std::vector<float>>       ( tree, "trk_qOverP",           &m_trk_qOverP           );
    connectBranch<std::vector<float>>       ( tree, "trk_E",                &m_trk_E                );
    connectBranch<std::vector<float>>       ( tree, "trk_M",                &m_trk_M                );
    connectBranch<std::vector<float>>       ( tree, "trk_pt",               &m_trk_pt               );
    connectBranch<std::vector<float>>       ( tree, "trk_eta",              &m_trk_eta              );
    connectBranch<std::vector<float>>       ( tree, "trk_phi",              &m_trk_phi              );
    connectBranch<std::vector<float>>       ( tree, "trk_d0",               &m_trk_d0               );
    connectBranch<std::vector<float>>       ( tree, "trk_z0",               &m_trk_z0               );
    connectBranch<std::vector<float>>       ( tree, "trk_dR",               &m_trk_dR               );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_trackPartDetail ) {
      connectBranch<std::vector<float>>     ( tree, "trk_errd0",            &m_trk_errd0            );
      connectBranch<std::vector<float>>     ( tree, "trk_errz0",            &m_trk_errz0            );
      connectBranch<std::vector<float>>     ( tree, "trk_chi2",             &m_trk_chi2             );
      connectBranch<std::vector<float>>     ( tree, "trk_charge",           &m_trk_charge           );
      connectBranch<std::vector<uint8_t>>   ( tree, "trk_isSelected",       &m_trk_isSelected       );
      connectBranch<std::vector<uint8_t>>   ( tree, "trk_isAssociated",     &m_trk_isAssociated     );
      connectBranch<std::vector<uint8_t>>   ( tree, "trk_isSecVtxTrk",      &m_trk_isSecVtxTrk      );
      connectBranch<std::vector<uint8_t>>   ( tree, "trk_isSecVtxCleanTrk", &m_trk_isSecVtxCleanTrk );
      connectBranch<std::vector<uint8_t>>   ( tree, "trk_isSecVtxFiltTrk",  &m_trk_isSecVtxFiltTrk  );
      connectBranch<std::vector<int>>       ( tree, "trk_secVtxID",         &m_trk_secVtxID         );
      connectBranch<std::vector<int>>       ( tree, "trk_secVtxIndex",      &m_trk_secVtxIndex      );
      if ( m_mc ) {
	connectBranch<std::vector<uint8_t>> ( tree, "trk_isTruth",          &m_trk_isTruth          );
	connectBranch<std::vector<float>>   ( tree, "trk_truthProb",        &m_trk_truthProb        );
	connectBranch<std::vector<int>>     ( tree, "trk_truthID",          &m_trk_truthID          );
	connectBranch<std::vector<int>>     ( tree, "trk_truthIndex",       &m_trk_truthIndex       );
	connectBranch<std::vector<int>>     ( tree, "trk_truthBarcode",     &m_trk_truthBarcode     );
	connectBranch<std::vector<int>>     ( tree, "trk_truthPdgId",       &m_trk_truthPdgId       );
      }
    }
  }
  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthParts ) && m_mc ) {
    connectBranch<int>                        ( tree, "tpCount",          &m_tpCount          );
    connectBranch<float>                      ( tree, "tpPt",             &m_tpPt             );
    connectBranch<std::vector<int>>           ( tree, "tp_ID",            &m_tp_ID            );
    connectBranch<std::vector<int>>           ( tree, "tp_index",         &m_tp_index         );
    connectBranch<std::vector<float>>         ( tree, "tp_pt",            &m_tp_pt            );
    connectBranch<std::vector<float>>         ( tree, "tp_eta",           &m_tp_eta           );
    connectBranch<std::vector<float>>         ( tree, "tp_phi",           &m_tp_phi           );
    connectBranch<std::vector<float>>         ( tree, "tp_E",             &m_tp_E             );
    connectBranch<std::vector<float>>         ( tree, "tp_M",             &m_tp_M             );
    connectBranch<std::vector<float>>         ( tree, "tp_charge",        &m_tp_charge        );
    connectBranch<std::vector<float>>         ( tree, "tp_dR",            &m_tp_dR            );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthPartDetail ) {
      connectBranch<std::vector<int>>         ( tree, "tp_pdgId",         &m_tp_pdgId         );
      connectBranch<std::vector<int>>         ( tree, "tp_status",        &m_tp_status        );
      connectBranch<std::vector<int>>         ( tree, "tp_barcode",       &m_tp_barcode       );
      connectBranch<std::vector<uint8_t>>     ( tree, "tp_isReco",        &m_tp_isReco        );
      connectBranch<std::vector<uint8_t>>     ( tree, "tp_isSelected",    &m_tp_isSelected    );
      connectBranch<std::vector<uint8_t>>     ( tree, "tp_isAssociated",  &m_tp_isAssociated  );
      connectBranch<std::vector<float>>       ( tree, "tp_recoProb",      &m_tp_recoProb      );
      connectBranch<std::vector<int>>         ( tree, "tp_recoID",        &m_tp_recoID        );
      connectBranch<std::vector<int>>         ( tree, "tp_recoIndex",     &m_tp_recoIndex     );
      connectBranch<std::vector<uint8_t>>     ( tree, "tp_isStable",      &m_tp_isStable      );
      connectBranch<std::vector<uint8_t>>     ( tree, "tp_isInteracting", &m_tp_isInteracting );
      connectBranch<std::vector<uint8_t>>     ( tree, "tp_isDark",        &m_tp_isDark        );
      connectBranch<std::vector<std::string>> ( tree, "tp_pVtx_llpDecay", &m_tp_pVtx_llpDecay );
      connectBranch<std::vector<int>>         ( tree, "tp_pVtx_ID",       &m_tp_pVtx_ID       );
      connectBranch<std::vector<int>>         ( tree, "tp_pVtx_index",    &m_tp_pVtx_index    );
      connectBranch<std::vector<std::string>> ( tree, "tp_dVtx_llpDecay", &m_tp_dVtx_llpDecay );
      connectBranch<std::vector<int>>         ( tree, "tp_dVtx_ID",       &m_tp_dVtx_ID       );
      connectBranch<std::vector<int>>         ( tree, "tp_dVtx_index",    &m_tp_dVtx_index    );
    }
  }
}


void JetContainer :: setBranches ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::JetContainer::setBranches()", "setting branches" );

  setBranch<int>   ( tree, "ID",     m_ID     );
  setBranch<int>   ( tree, "index",  m_index  );
  setBranch<float> ( tree, "M",      m_M      );
  setBranch<float> ( tree, "radius", m_radius );

  if ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTracks ) {
    setBranch<std::vector<int>>         ( tree, "GhostTrack_ID",               m_GhostTrack_ID               );
    setBranch<std::vector<int>>         ( tree, "GhostTrack_index",            m_GhostTrack_index            );
    setBranch<std::vector<float>>       ( tree, "GhostTrack_m",                m_GhostTrack_m                );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTrackDetail ) {
      setBranch<std::vector<float>>     ( tree, "GhostTrack_errd0",            m_GhostTrack_errd0            );
      setBranch<std::vector<float>>     ( tree, "GhostTrack_errz0",            m_GhostTrack_errz0            );
      setBranch<std::vector<float>>     ( tree, "GhostTrack_chi2",             m_GhostTrack_chi2             );
      setBranch<std::vector<float>>     ( tree, "GhostTrack_charge",           m_GhostTrack_charge           );
      setBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSelected",       m_GhostTrack_isSelected       );
      setBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isAssociated",     m_GhostTrack_isAssociated     );
      setBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSecVtxTrk",      m_GhostTrack_isSecVtxTrk      );
      setBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSecVtxCleanTrk", m_GhostTrack_isSecVtxCleanTrk );
      setBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSecVtxFiltTrk",  m_GhostTrack_isSecVtxFiltTrk  );
      setBranch<std::vector<int>>       ( tree, "GhostTrack_secVtxID",         m_GhostTrack_secVtxID         );
      setBranch<std::vector<int>>       ( tree, "GhostTrack_secVtxIndex",      m_GhostTrack_secVtxIndex      );
      if ( m_mc ) {
	setBranch<std::vector<uint8_t>> ( tree, "GhostTrack_isTruth",          m_GhostTrack_isTruth          );
	setBranch<std::vector<float>>   ( tree, "GhostTrack_truthProb",        m_GhostTrack_truthProb        );
	setBranch<std::vector<int>>     ( tree, "GhostTrack_truthID",          m_GhostTrack_truthID          );
	setBranch<std::vector<int>>     ( tree, "GhostTrack_truthIndex",       m_GhostTrack_truthIndex       );
	setBranch<std::vector<int>>     ( tree, "GhostTrack_truthBarcode",     m_GhostTrack_truthBarcode     );
	setBranch<std::vector<int>>     ( tree, "GhostTrack_truthPdgId",       m_GhostTrack_truthPdgId       );
      }
    }
  }
  if ( ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTruth ) && m_mc ) { 
    setBranch<int>                        ( tree, "GhostTruthCount",          m_GhostTruthCount          );
    setBranch<float>                      ( tree, "GhostTruthPt",             m_GhostTruthPt             );
    setBranch<std::vector<int>>           ( tree, "GhostTruth_ID",            m_GhostTruth_ID            );
    setBranch<std::vector<int>>           ( tree, "GhostTruth_index",         m_GhostTruth_index         );
    setBranch<std::vector<float>>         ( tree, "GhostTruth_pt",            m_GhostTruth_pt            );
    setBranch<std::vector<float>>         ( tree, "GhostTruth_eta",           m_GhostTruth_eta           );
    setBranch<std::vector<float>>         ( tree, "GhostTruth_phi",           m_GhostTruth_phi           );
    setBranch<std::vector<float>>         ( tree, "GhostTruth_e",             m_GhostTruth_e             );
    setBranch<std::vector<float>>         ( tree, "GhostTruth_m",             m_GhostTruth_m             );
    setBranch<std::vector<float>>         ( tree, "GhostTruth_charge",        m_GhostTruth_charge        );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTruthDetail ) {
      setBranch<std::vector<int>>         ( tree, "GhostTruth_pdgId",         m_GhostTruth_pdgId         );
      setBranch<std::vector<int>>         ( tree, "GhostTruth_status",        m_GhostTruth_status        );
      setBranch<std::vector<int>>         ( tree, "GhostTruth_barcode",       m_GhostTruth_barcode       );
      setBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isReco",        m_GhostTruth_isReco        );
      setBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isSelected",    m_GhostTruth_isSelected    );
      setBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isAssociated",  m_GhostTruth_isAssociated  );
      setBranch<std::vector<float>>       ( tree, "GhostTruth_recoProb",      m_GhostTruth_recoProb      );
      setBranch<std::vector<int>>         ( tree, "GhostTruth_recoID",        m_GhostTruth_recoID        );
      setBranch<std::vector<int>>         ( tree, "GhostTruth_recoIndex",     m_GhostTruth_recoIndex     );
      setBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isStable",      m_GhostTruth_isStable      );
      setBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isInteracting", m_GhostTruth_isInteracting );
      setBranch<std::vector<uint8_t>>     ( tree, "GhostTruth_isDark",        m_GhostTruth_isDark        );
      setBranch<std::vector<std::string>> ( tree, "GhostTruth_pVtx_llpDecay", m_GhostTruth_pVtx_llpDecay );
      setBranch<std::vector<int>>         ( tree, "GhostTruth_pVtx_ID",       m_GhostTruth_pVtx_ID       );
      setBranch<std::vector<int>>         ( tree, "GhostTruth_pVtx_index",    m_GhostTruth_pVtx_index    );
      setBranch<std::vector<std::string>> ( tree, "GhostTruth_dVtx_llpDecay", m_GhostTruth_dVtx_llpDecay );
      setBranch<std::vector<int>>         ( tree, "GhostTruth_dVtx_ID",       m_GhostTruth_dVtx_ID       );
      setBranch<std::vector<int>>         ( tree, "GhostTruth_dVtx_index",    m_GhostTruth_dVtx_index    );
    }
  }

  if ( m_infoSwitch.m_constituentAll ) {
    setBranch<float>                    ( tree, "girth",                     m_girth                     );
    setBranch<float>                    ( tree, "constituentPt",             m_constituentPt             );
    setBranch<std::vector<float>>       ( tree, "constituent_dR",            m_constituent_dR            );
    setBranch<std::vector<float>>       ( tree, "constituent_m",             m_constituent_m             );
    if ( jet_type == TRUTH || jet_type == DARK ) {
      setBranch<std::vector<int>>       ( tree, "constituent_ID",            m_constituent_ID            );
      setBranch<std::vector<int>>       ( tree, "constituent_index",         m_constituent_index         );
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_constituentDetail ) {
	setBranch<std::vector<float>>   ( tree, "constituent_charge",        m_constituent_charge        );
	setBranch<std::vector<int>>     ( tree, "constituent_pdgId",         m_constituent_pdgId         );
	setBranch<std::vector<int>>     ( tree, "constituent_status",        m_constituent_status        );
	setBranch<std::vector<int>>     ( tree, "constituent_barcode",       m_constituent_barcode       );
	setBranch<std::vector<uint8_t>> ( tree, "constituent_isStable",      m_constituent_isStable      );
	setBranch<std::vector<uint8_t>> ( tree, "constituent_isInteracting", m_constituent_isInteracting );
	setBranch<std::vector<uint8_t>> ( tree, "constituent_isDark",        m_constituent_isDark        );
	setBranch<std::vector<uint8_t>> ( tree, "constituent_hasProdVtx",    m_constituent_pVtx          );
	setBranch<std::vector<float>>   ( tree, "constituent_prodVtx_r",     m_constituent_pVtx_r        );
	setBranch<std::vector<uint8_t>> ( tree, "constituent_hasDecayVtx",   m_constituent_dVtx          );
	setBranch<std::vector<float>>   ( tree, "constituent_decayVtx_r",    m_constituent_dVtx_r        );
      }
    }
  }

   if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    if ( jet_type == RECO ) {
      setBranch<uint8_t>   ( tree, "isTruthMatched",     m_isTruthMatched     );
      setBranch<int>       ( tree, "truthMatch_ID",      m_truthMatch_ID      );
      setBranch<int>       ( tree, "truthMatch_index",   m_truthMatch_index   );
      setBranch<float>     ( tree, "truthMatch_dR",      m_truthMatch_dR      );
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	setBranch<float>   ( tree, "truthMatch_E",       m_truthMatch_E       );
	setBranch<float>   ( tree, "truthMatch_M",       m_truthMatch_M       );
	setBranch<float>   ( tree, "truthMatch_pt",      m_truthMatch_pt      );
	setBranch<float>   ( tree, "truthMatch_eta",     m_truthMatch_eta     );
	setBranch<float>   ( tree, "truthMatch_phi",     m_truthMatch_phi     );
      }
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      setBranch<uint8_t>   ( tree, "isDarkMatched",      m_isDarkMatched      );
      setBranch<int>       ( tree, "darkMatch_ID",       m_darkMatch_ID       );
      setBranch<int>       ( tree, "darkMatch_index",    m_darkMatch_index    );
      setBranch<float>     ( tree, "darkMatch_dR",       m_darkMatch_dR       );
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	setBranch<float>   ( tree, "darkMatch_E",        m_darkMatch_E        );
	setBranch<float>   ( tree, "darkMatch_M",        m_darkMatch_M        );
	setBranch<float>   ( tree, "darkMatch_pt",       m_darkMatch_pt       );
	setBranch<float>   ( tree, "darkMatch_eta",      m_darkMatch_eta      );
	setBranch<float>   ( tree, "darkMatch_phi",      m_darkMatch_phi      );
      }
    }
    if ( jet_type == DARK ) {
      setBranch<uint8_t>   ( tree, "isMatchedToTruth",   m_isMatchedToTruth   );
      setBranch<int>       ( tree, "matchedTruthID",     m_matchedTruthID     );
      setBranch<int>       ( tree, "matchedTruthIndex",  m_matchedTruthIndex  );
      setBranch<float>     ( tree, "matchedTruthDR",     m_matchedTruthDR     );
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	setBranch<uint8_t> ( tree, "isMatchedToEMTopo",  m_isMatchedToEMTopo  );
	setBranch<int>     ( tree, "matchedEMTopoID",    m_matchedEMTopoID    );
	setBranch<int>     ( tree, "matchedEMTopoIndex", m_matchedEMTopoIndex );
	setBranch<float>   ( tree, "matchedEMTopoDR",    m_matchedEMTopoDR    );
      }
      if ( m_doPFlow ) {
	setBranch<uint8_t> ( tree, "isMatchedToPFlow",   m_isMatchedToPFlow   );
	setBranch<int>     ( tree, "matchedPFlowID",     m_matchedPFlowID     );
	setBranch<int>     ( tree, "matchedPFlowIndex",  m_matchedPFlowIndex  );
	setBranch<float>   ( tree, "matchedPFlowDR",     m_matchedPFlowDR     );
      }
    }
  }

   if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_recoVerts) {
     setBranch<int>                      ( tree, "secVtxCount",                m_secVtxCount                );
     setBranch<std::vector<int>>         ( tree, "secVtx_ID",                  m_secVtx_ID                  );
     setBranch<std::vector<int>>         ( tree, "secVtx_index",               m_secVtx_index               );
     setBranch<std::vector<float>>       ( tree, "secVtx_x",                   m_secVtx_x                   );
     setBranch<std::vector<float>>       ( tree, "secVtx_y",                   m_secVtx_y                   );
     setBranch<std::vector<float>>       ( tree, "secVtx_z",                   m_secVtx_z                   );
     setBranch<std::vector<float>>       ( tree, "secVtx_r",                   m_secVtx_r                   );
     setBranch<std::vector<float>>       ( tree, "secVtx_chi2",                m_secVtx_chi2                );
     setBranch<std::vector<int>>         ( tree, "secVtx_ntrk",                m_secVtx_ntrk                );
     setBranch<std::vector<int>>         ( tree, "secVtx_ntrk_clean",          m_secVtx_ntrk_clean          );
     setBranch<std::vector<int>>         ( tree, "secVtx_ntrk_filt",           m_secVtx_ntrk_filt           );
     setBranch<std::vector<float>>       ( tree, "secVtx_dR",                  m_secVtx_dR                  );
     if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_recoVtxDetail ) {
       setBranch<float>                  ( tree, "secVtxPt",                   m_secVtxPt                   );
       setBranch<float>                  ( tree, "secVtxCleanPt",              m_secVtxCleanPt              );
       setBranch<float>                  ( tree, "secVtxBarePt",               m_secVtxBarePt               );
       setBranch<std::vector<float>>     ( tree, "secVtx_pt",                  m_secVtx_pt                  );
       setBranch<std::vector<float>>     ( tree, "secVtx_eta",                 m_secVtx_eta                 );
       setBranch<std::vector<float>>     ( tree, "secVtx_phi",                 m_secVtx_phi                 );
       setBranch<std::vector<float>>     ( tree, "secVtx_mass",                m_secVtx_mass                );
       setBranch<std::vector<float>>     ( tree, "secVtx_pt_clean",            m_secVtx_pt_clean            );
       setBranch<std::vector<float>>     ( tree, "secVtx_eta_clean",           m_secVtx_eta_clean           );
       setBranch<std::vector<float>>     ( tree, "secVtx_phi_clean",           m_secVtx_phi_clean           );
       setBranch<std::vector<float>>     ( tree, "secVtx_mass_clean",          m_secVtx_mass_clean          );
       setBranch<std::vector<float>>     ( tree, "secVtx_pt_bare",             m_secVtx_pt_bare             );
       setBranch<std::vector<float>>     ( tree, "secVtx_eta_bare",            m_secVtx_eta_bare            );
       setBranch<std::vector<float>>     ( tree, "secVtx_phi_bare",            m_secVtx_phi_bare            );
       setBranch<std::vector<float>>     ( tree, "secVtx_mass_bare",           m_secVtx_mass_bare           );
       setBranch<std::vector<float>>     ( tree, "secVtx_distToPV",            m_secVtx_distToPV            );
       setBranch<std::vector<int>>       ( tree, "secVtx_ntrk_sel",            m_secVtx_ntrk_sel            );
       setBranch<std::vector<int>>       ( tree, "secVtx_ntrk_assoc",          m_secVtx_ntrk_assoc          );
       setBranch<std::vector<int>>       ( tree, "secVtx_ntrk_clean_sel",      m_secVtx_ntrk_clean_sel      );
       setBranch<std::vector<int>>       ( tree, "secVtx_ntrk_clean_assoc",    m_secVtx_ntrk_clean_assoc    );
       setBranch<std::vector<int>>       ( tree, "secVtx_ntrk_filt_sel",       m_secVtx_ntrk_filt_sel       );
       setBranch<std::vector<int>>       ( tree, "secVtx_ntrk_filt_assoc",     m_secVtx_ntrk_filt_assoc     );
       setBranch<std::vector<uint8_t>>   ( tree, "secVtx_isTruthMatched",      m_secVtx_isTruthMatched      );
     }
   }
   if ( ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_truthVerts ) && m_mc ) {
     setBranch<int>                      ( tree, "truthVtxCount",              m_truthVtxCount              );
     setBranch<std::vector<std::string>> ( tree, "truthVtx_llpDecay",          m_truthVtx_llpDecay          );
     setBranch<std::vector<int>>         ( tree, "truthVtx_ID",                m_truthVtx_ID                );
     setBranch<std::vector<int>>         ( tree, "truthVtx_index",             m_truthVtx_index             );
     setBranch<std::vector<float>>       ( tree, "truthVtx_x",                 m_truthVtx_x                 );
     setBranch<std::vector<float>>       ( tree, "truthVtx_y",                 m_truthVtx_y                 );
     setBranch<std::vector<float>>       ( tree, "truthVtx_z",                 m_truthVtx_z                 );
     setBranch<std::vector<float>>       ( tree, "truthVtx_r",                 m_truthVtx_r                 );
     setBranch<std::vector<int>>         ( tree, "truthVtx_nOutP",             m_truthVtx_nOutP             );
     setBranch<std::vector<float>>       ( tree, "truthVtx_dR",                m_truthVtx_dR                );
     if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_truthVtxDetail ) {
       setBranch<float>                  ( tree, "truthVtxPt",                 m_truthVtxPt                 );
       setBranch<std::vector<float>>     ( tree, "truthVtx_pt",                m_truthVtx_pt                );
       setBranch<std::vector<float>>     ( tree, "truthVtx_eta",               m_truthVtx_eta               );
       setBranch<std::vector<float>>     ( tree, "truthVtx_phi",               m_truthVtx_phi               );
       setBranch<std::vector<float>>     ( tree, "truthVtx_mass",              m_truthVtx_mass              );
       setBranch<std::vector<int>>       ( tree, "truthVtx_barcode",           m_truthVtx_barcode           );
       setBranch<std::vector<uint8_t>>   ( tree, "truthVtx_isReconstructible", m_truthVtx_isReconstructible );
       setBranch<std::vector<uint8_t>>   ( tree, "truthVtx_isRecoMatched",     m_truthVtx_isRecoMatched     );
     }
   }

   if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
     setBranch<int>                      ( tree, "trkCount",             m_trkCount             );
     setBranch<float>                    ( tree, "trkPt",                m_trkPt                );
     setBranch<std::vector<int>>         ( tree, "trk_ID",               m_trk_ID               );
     setBranch<std::vector<int>>         ( tree, "trk_index",            m_trk_index            );
     setBranch<std::vector<float>>       ( tree, "trk_qOverP",           m_trk_qOverP           );
     setBranch<std::vector<float>>       ( tree, "trk_E",                m_trk_E                );
     setBranch<std::vector<float>>       ( tree, "trk_M",                m_trk_M                );
     setBranch<std::vector<float>>       ( tree, "trk_pt",               m_trk_pt               );
     setBranch<std::vector<float>>       ( tree, "trk_eta",              m_trk_eta              );
     setBranch<std::vector<float>>       ( tree, "trk_phi",              m_trk_phi              );
     setBranch<std::vector<float>>       ( tree, "trk_d0",               m_trk_d0               );
     setBranch<std::vector<float>>       ( tree, "trk_z0",               m_trk_z0               );
     setBranch<std::vector<float>>       ( tree, "trk_dR",               m_trk_dR               );
     if ( m_infoSwitch.m_detail || m_infoSwitch.m_trackPartDetail ) {
       setBranch<std::vector<float>>     ( tree, "trk_errd0",            m_trk_errd0            );
       setBranch<std::vector<float>>     ( tree, "trk_errz0",            m_trk_errz0            );
       setBranch<std::vector<float>>     ( tree, "trk_chi2",             m_trk_chi2             );
       setBranch<std::vector<float>>     ( tree, "trk_charge",           m_trk_charge           );
       setBranch<std::vector<uint8_t>>   ( tree, "trk_isSelected",       m_trk_isSelected       );
       setBranch<std::vector<uint8_t>>   ( tree, "trk_isAssociated",     m_trk_isAssociated     );
       setBranch<std::vector<uint8_t>>   ( tree, "trk_isSecVtxTrk",      m_trk_isSecVtxTrk      );
       setBranch<std::vector<uint8_t>>   ( tree, "trk_isSecVtxCleanTrk", m_trk_isSecVtxCleanTrk );
       setBranch<std::vector<uint8_t>>   ( tree, "trk_isSecVtxFiltTrk",  m_trk_isSecVtxFiltTrk  );
       setBranch<std::vector<int>>       ( tree, "trk_secVtxID",         m_trk_secVtxID         );
       setBranch<std::vector<int>>       ( tree, "trk_secVtxIndex",      m_trk_secVtxIndex      );
       if ( m_mc ) {
	 setBranch<std::vector<uint8_t>> ( tree, "trk_isTruth",          m_trk_isTruth          );
	 setBranch<std::vector<float>>   ( tree, "trk_truthProb",        m_trk_truthProb        );
	 setBranch<std::vector<int>>     ( tree, "trk_truthID",          m_trk_truthID          );
	 setBranch<std::vector<int>>     ( tree, "trk_truthIndex",       m_trk_truthIndex       );
	 setBranch<std::vector<int>>     ( tree, "trk_truthBarcode",     m_trk_truthBarcode     );
	 setBranch<std::vector<int>>     ( tree, "trk_truthPdgId",       m_trk_truthPdgId       );
       }
     }
   }
   if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthParts ) && m_mc ) {
    setBranch<int>                        ( tree, "tpCount",          m_tpCount          );
    setBranch<float>                      ( tree, "tpPt",             m_tpPt             );
    setBranch<std::vector<int>>           ( tree, "tp_ID",            m_tp_ID            );
    setBranch<std::vector<int>>           ( tree, "tp_index",         m_tp_index         );
    setBranch<std::vector<float>>         ( tree, "tp_pt",            m_tp_pt            );
    setBranch<std::vector<float>>         ( tree, "tp_eta",           m_tp_eta           );
    setBranch<std::vector<float>>         ( tree, "tp_phi",           m_tp_phi           );
    setBranch<std::vector<float>>         ( tree, "tp_E",             m_tp_E             );
    setBranch<std::vector<float>>         ( tree, "tp_M",             m_tp_M             );
    setBranch<std::vector<float>>         ( tree, "tp_charge",        m_tp_charge        );
    setBranch<std::vector<float>>         ( tree, "tp_dR",            m_tp_dR            );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthPartDetail ) {
      setBranch<std::vector<int>>         ( tree, "tp_pdgId",         m_tp_pdgId         );
      setBranch<std::vector<int>>         ( tree, "tp_status",        m_tp_status        );
      setBranch<std::vector<int>>         ( tree, "tp_barcode",       m_tp_barcode       );
      setBranch<std::vector<uint8_t>>     ( tree, "tp_isReco",        m_tp_isReco        );
      setBranch<std::vector<uint8_t>>     ( tree, "tp_isSelected",    m_tp_isSelected    );
      setBranch<std::vector<uint8_t>>     ( tree, "tp_isAssociated",  m_tp_isAssociated  );
      setBranch<std::vector<float>>       ( tree, "tp_recoProb",      m_tp_recoProb      );
      setBranch<std::vector<int>>         ( tree, "tp_recoID",        m_tp_recoID        );
      setBranch<std::vector<int>>         ( tree, "tp_recoIndex",     m_tp_recoIndex     );
      setBranch<std::vector<uint8_t>>     ( tree, "tp_isStable",      m_tp_isStable      );
      setBranch<std::vector<uint8_t>>     ( tree, "tp_isInteracting", m_tp_isInteracting );
      setBranch<std::vector<uint8_t>>     ( tree, "tp_isDark",        m_tp_isDark        );
      setBranch<std::vector<std::string>> ( tree, "tp_pVtx_llpDecay", m_tp_pVtx_llpDecay );
      setBranch<std::vector<int>>         ( tree, "tp_pVtx_ID",       m_tp_pVtx_ID       );
      setBranch<std::vector<int>>         ( tree, "tp_pVtx_index",    m_tp_pVtx_index    );
      setBranch<std::vector<std::string>> ( tree, "tp_dVtx_llpDecay", m_tp_dVtx_llpDecay );
      setBranch<std::vector<int>>         ( tree, "tp_dVtx_ID",       m_tp_dVtx_ID       );
      setBranch<std::vector<int>>         ( tree, "tp_dVtx_index",    m_tp_dVtx_index    );
    }
  }
}


void JetContainer :: clear ()
{
  if ( m_debug ) Info( "EJs::JetContainer::clear()", "clearing branches" );

  m_ID     ->clear();
  m_index  ->clear();
  m_M      ->clear();
  m_radius ->clear();

  if ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTracks ) {
    m_GhostTrack_ID                 ->clear();
    m_GhostTrack_index              ->clear();
    m_GhostTrack_m                  ->clear();
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTrackDetail ) {
      m_GhostTrack_errd0            ->clear();
      m_GhostTrack_errz0            ->clear();
      m_GhostTrack_chi2             ->clear();
      m_GhostTrack_charge           ->clear();
      m_GhostTrack_isSelected       ->clear();
      m_GhostTrack_isAssociated     ->clear();
      m_GhostTrack_isSecVtxTrk      ->clear();
      m_GhostTrack_isSecVtxCleanTrk ->clear();
      m_GhostTrack_isSecVtxFiltTrk  ->clear();
      m_GhostTrack_secVtxID         ->clear();
      m_GhostTrack_secVtxIndex      ->clear();
      if ( m_mc ) {
	m_GhostTrack_isTruth        ->clear();
	m_GhostTrack_truthProb      ->clear();
	m_GhostTrack_truthID        ->clear();
	m_GhostTrack_truthIndex     ->clear();
	m_GhostTrack_truthBarcode   ->clear();
	m_GhostTrack_truthPdgId     ->clear();
      }
    }
  }
  if ( ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTruth ) && m_mc ) {
    m_GhostTruthCount             ->clear();
    m_GhostTruthPt                ->clear();
    m_GhostTruth_ID               ->clear();
    m_GhostTruth_index            ->clear();
    m_GhostTruth_pt               ->clear();
    m_GhostTruth_eta              ->clear();
    m_GhostTruth_phi              ->clear();
    m_GhostTruth_e                ->clear();
    m_GhostTruth_m                ->clear();
    m_GhostTruth_charge           ->clear();
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTruthDetail ) {
      m_GhostTruth_pdgId          ->clear();
      m_GhostTruth_status         ->clear();
      m_GhostTruth_barcode        ->clear();
      m_GhostTruth_isReco         ->clear();
      m_GhostTruth_isSelected     ->clear();
      m_GhostTruth_isAssociated   ->clear();
      m_GhostTruth_recoProb       ->clear();
      m_GhostTruth_recoID         ->clear();
      m_GhostTruth_recoIndex      ->clear();
      m_GhostTruth_isStable       ->clear();
      m_GhostTruth_isInteracting  ->clear();
      m_GhostTruth_isDark         ->clear();
      m_GhostTruth_pVtx_llpDecay  ->clear();
      m_GhostTruth_pVtx_ID        ->clear();
      m_GhostTruth_pVtx_index     ->clear();
      m_GhostTruth_dVtx_llpDecay  ->clear();
      m_GhostTruth_dVtx_ID        ->clear();
      m_GhostTruth_dVtx_index     ->clear();
    }
  }

  if ( m_infoSwitch.m_constituentAll ) {
    m_girth          ->clear();
    m_constituentPt  ->clear();
    m_constituent_dR ->clear();
    m_constituent_m  ->clear();
    if ( jet_type == TRUTH || jet_type == DARK ) {
      m_constituent_ID              ->clear();
      m_constituent_index           ->clear();
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_constituentDetail ) {
	m_constituent_charge        ->clear();
	m_constituent_pdgId         ->clear();
	m_constituent_status        ->clear();
	m_constituent_barcode       ->clear();
	m_constituent_isStable      ->clear();
	m_constituent_isInteracting ->clear();
	m_constituent_isDark        ->clear();
	m_constituent_pVtx          ->clear();
	m_constituent_pVtx_r        ->clear();
	m_constituent_dVtx          ->clear();
	m_constituent_dVtx_r        ->clear();
      }
    }
  }

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    if ( jet_type == RECO ) {
      m_isTruthMatched       ->clear();
      m_truthMatch_ID        ->clear();
      m_truthMatch_index     ->clear();
      m_truthMatch_dR        ->clear();
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	m_truthMatch_E       ->clear();
	m_truthMatch_M       ->clear();
	m_truthMatch_pt      ->clear();
	m_truthMatch_eta     ->clear();
	m_truthMatch_phi     ->clear();
      }
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      m_isDarkMatched        ->clear();
      m_darkMatch_ID         ->clear();
      m_darkMatch_index      ->clear();
      m_darkMatch_dR         ->clear();
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	m_darkMatch_E        ->clear();
	m_darkMatch_M        ->clear();
	m_darkMatch_pt       ->clear();
	m_darkMatch_eta      ->clear();
	m_darkMatch_phi      ->clear();
      }
    }
    if ( jet_type == DARK ) {
      m_isMatchedToTruth     ->clear();
      m_matchedTruthID       ->clear();
      m_matchedTruthIndex    ->clear();
      m_matchedTruthDR       ->clear();
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	m_isMatchedToEMTopo  ->clear();
	m_matchedEMTopoID    ->clear();
	m_matchedEMTopoIndex ->clear();
	m_matchedEMTopoDR    ->clear();
      }
      if ( m_doPFlow ) {
	m_isMatchedToPFlow   ->clear();
	m_matchedPFlowID     ->clear();
	m_matchedPFlowIndex  ->clear();
	m_matchedPFlowDR     ->clear();
      }
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_recoVerts ) {
    m_secVtxCount                ->clear();
    m_secVtx_ID                  ->clear();
    m_secVtx_index               ->clear();
    m_secVtx_x                   ->clear();
    m_secVtx_y                   ->clear();
    m_secVtx_z                   ->clear();
    m_secVtx_r                   ->clear();
    m_secVtx_chi2                ->clear();
    m_secVtx_ntrk                ->clear();
    m_secVtx_ntrk_clean          ->clear();
    m_secVtx_ntrk_filt           ->clear();
    m_secVtx_dR                  ->clear();
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_recoVtxDetail ) {
      m_secVtxPt                 ->clear();
      m_secVtxCleanPt            ->clear();
      m_secVtxBarePt             ->clear();
      m_secVtx_pt                ->clear();
      m_secVtx_eta               ->clear();
      m_secVtx_phi               ->clear();
      m_secVtx_mass              ->clear();
      m_secVtx_pt_clean          ->clear();
      m_secVtx_eta_clean         ->clear();
      m_secVtx_phi_clean         ->clear();
      m_secVtx_mass_clean        ->clear();
      m_secVtx_pt_bare           ->clear();
      m_secVtx_eta_bare          ->clear();
      m_secVtx_phi_bare          ->clear();
      m_secVtx_mass_bare         ->clear();
      m_secVtx_distToPV          ->clear();
      m_secVtx_ntrk_sel          ->clear();
      m_secVtx_ntrk_assoc        ->clear();
      m_secVtx_ntrk_clean_sel    ->clear();
      m_secVtx_ntrk_clean_assoc  ->clear();
      m_secVtx_ntrk_filt_sel     ->clear();
      m_secVtx_ntrk_filt_assoc   ->clear();
      m_secVtx_isTruthMatched    ->clear();
    }
  }
  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_truthVerts ) && m_mc ) {
    m_truthVtxCount                ->clear();
    m_truthVtx_llpDecay            ->clear();
    m_truthVtx_ID                  ->clear();
    m_truthVtx_index               ->clear();
    m_truthVtx_x                   ->clear();
    m_truthVtx_y                   ->clear();
    m_truthVtx_z                   ->clear();
    m_truthVtx_r                   ->clear();
    m_truthVtx_nOutP               ->clear();
    m_truthVtx_dR                  ->clear();
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_truthVtxDetail ) {
      m_truthVtxPt                 ->clear();
      m_truthVtx_pt                ->clear();
      m_truthVtx_eta               ->clear();
      m_truthVtx_phi               ->clear();
      m_truthVtx_mass              ->clear();
      m_truthVtx_barcode           ->clear();
      m_truthVtx_isReconstructible ->clear();
      m_truthVtx_isRecoMatched     ->clear();
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    m_trkCount               ->clear();
    m_trkPt                  ->clear();
    m_trk_ID                 ->clear();
    m_trk_index              ->clear();
    m_trk_qOverP             ->clear();
    m_trk_E                  ->clear();
    m_trk_M                  ->clear();
    m_trk_pt                 ->clear();
    m_trk_eta                ->clear();
    m_trk_phi                ->clear();
    m_trk_d0                 ->clear();
    m_trk_z0                 ->clear();
    m_trk_dR                 ->clear();
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_trackPartDetail ) {
      m_trk_errd0            ->clear();
      m_trk_errz0            ->clear();
      m_trk_chi2             ->clear();
      m_trk_charge           ->clear();
      m_trk_isSelected       ->clear();
      m_trk_isAssociated     ->clear();
      m_trk_isSecVtxTrk      ->clear();
      m_trk_isSecVtxCleanTrk ->clear();
      m_trk_isSecVtxFiltTrk  ->clear();
      m_trk_secVtxID         ->clear();
      m_trk_secVtxIndex      ->clear();
      if ( m_mc ) {
	m_trk_isTruth        ->clear();
	m_trk_truthProb      ->clear();
	m_trk_truthID        ->clear();
	m_trk_truthIndex     ->clear();
	m_trk_truthBarcode   ->clear();
	m_trk_truthPdgId     ->clear();
      }
    }
  }
  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthParts ) && m_mc ) {
    m_tpCount            ->clear();
    m_tpPt               ->clear();
    m_tp_ID              ->clear();
    m_tp_index           ->clear();
    m_tp_pt              ->clear();
    m_tp_eta             ->clear();
    m_tp_phi             ->clear();
    m_tp_E               ->clear();
    m_tp_M               ->clear();
    m_tp_charge          ->clear();
    m_tp_dR              ->clear();
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthPartDetail ) {
      m_tp_pdgId         ->clear();
      m_tp_status        ->clear();
      m_tp_barcode       ->clear();
      m_tp_isReco        ->clear();
      m_tp_isSelected    ->clear();
      m_tp_isAssociated  ->clear();
      m_tp_recoProb      ->clear();
      m_tp_recoID        ->clear();
      m_tp_recoIndex     ->clear();
      m_tp_isStable      ->clear();
      m_tp_isInteracting ->clear();
      m_tp_isDark        ->clear();
      m_tp_pVtx_llpDecay ->clear();
      m_tp_pVtx_ID       ->clear();
      m_tp_pVtx_index    ->clear();
      m_tp_dVtx_llpDecay ->clear();
      m_tp_dVtx_ID       ->clear();
      m_tp_dVtx_index    ->clear();
    }
  }
}


void JetContainer :: FillJet ( const xAOD::Jet* jet, const std::vector<std::string>& truthVtxLLPs,
			       const std::string treeName )
{
  if ( m_debug ) Info( "EJs::JetContainer::FillJet()", "filling branches" );

  std::string jet_str = treeName;
  if ( treeName == "nominal" ) jet_str = "";

  m_ID     ->push_back( AUXDYN( jet, int, "ID"    ) );
  m_index  ->push_back( AUXDYN( jet, int, "index" ) );
  m_M      ->push_back( jet->m() / m_units          );
  m_radius ->push_back( jet->getSizeParameter()     );

  if ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTracks ) {
    std::vector<int>     ghostTrack_ID;
    std::vector<int>     ghostTrack_index;
    std::vector<float>   ghostTrack_m;
    std::vector<float>   ghostTrack_errd0;
    std::vector<float>   ghostTrack_errz0;
    std::vector<float>   ghostTrack_chi2;
    std::vector<float>   ghostTrack_charge;
    std::vector<uint8_t> ghostTrack_isSelected;
    std::vector<uint8_t> ghostTrack_isAssociated;
    std::vector<uint8_t> ghostTrack_isSecVtxTrk;
    std::vector<uint8_t> ghostTrack_isSecVtxCleanTrk;
    std::vector<uint8_t> ghostTrack_isSecVtxFiltTrk;
    std::vector<int>     ghostTrack_secVtxID;
    std::vector<int>     ghostTrack_secVtxIndex;
    std::vector<uint8_t> ghostTrack_isTruth;
    std::vector<float>   ghostTrack_truthProb;
    std::vector<int>     ghostTrack_truthID;
    std::vector<int>     ghostTrack_truthIndex;
    std::vector<int>     ghostTrack_truthBarcode;
    std::vector<int>     ghostTrack_truthPdgId;
    
    // access ghost tracks
    static SG::AuxElement::ConstAccessor<std::vector<ElementLink<DataVector<xAOD::IParticle> > > > ghostTrackAccess("GhostTrack");
    if ( ghostTrackAccess.isAvailable( *jet ) ) {
      std::vector<ElementLink<DataVector<xAOD::IParticle> > > ghostTrackLinks = ghostTrackAccess( *jet );
      for ( const auto& ghosttrklink : ghostTrackLinks ) {
	if ( !ghosttrklink.isValid() ) continue;
	const xAOD::TrackParticle* ghosttrack = dynamic_cast<const xAOD::TrackParticle*>( *ghosttrklink );
	ghostTrack_ID             .push_back( AUXDYN( ghosttrack, int, "ID"                                               ) );
	ghostTrack_index          .push_back( AUXDYN( ghosttrack, int, "index"                                            ) );
	ghostTrack_m              .push_back( ghosttrack->m()  / m_units                                                    );
	
	if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTrackDetail ) {
	  ghostTrack_errd0        .push_back( ghosttrack->definingParametersCovMatrix()(0,0)                                );
	  ghostTrack_errz0        .push_back( ghosttrack->definingParametersCovMatrix()(1,1)                                );
	  ghostTrack_chi2         .push_back( ghosttrack->chiSquared() / ghosttrack->numberDoF() / AlgConsts::infinitesimal );
	  ghostTrack_charge       .push_back( ghosttrack->charge()                                                          );
	  ghostTrack_isSelected   .push_back( AUXDYN( ghosttrack, char, "is_selected"                                     ) );
	  ghostTrack_isAssociated .push_back( AUXDYN( ghosttrack, char, "is_associated"                                   ) );
	  
	  // get linked secondary vertex
	  bool ghosttrackIsSecVtxTrk      = false;
	  bool ghosttrackIsSecVtxCleanTrk = false;
	  bool ghosttrackIsSecVtxFiltTrk  = false;
	  int  secVtxID                   = AlgConsts::invalidInt;
	  int  secVtxIndex                = AlgConsts::invalidInt;
	  static SG::AuxElement::ConstAccessor<EJsHelper::VertexLink_t> ghostSecVtxAccess("secondaryVertexLink");
	  if ( ghostSecVtxAccess.isAvailable( *ghosttrack ) ) {
	    try {
	      const EJsHelper::VertexLink_t& ghostSecVtxLink = ghostSecVtxAccess( *ghosttrack );
	      if ( *ghostSecVtxLink ) ghosttrackIsSecVtxTrk = true;
	      if ( ghosttrack->isAvailable<char>("isClean") )
		ghosttrackIsSecVtxCleanTrk = ghosttrack->auxdataConst<char>("isClean");
	      if ( ghosttrack->isAvailable<char>("isFiltered") )
		ghosttrackIsSecVtxFiltTrk  = ghosttrack->auxdataConst<char>("isFiltered");
	      secVtxID    = AUXDYN( (*ghostSecVtxLink), int, "ID"    );
	      secVtxIndex = AUXDYN( (*ghostSecVtxLink), int, "index" );
	    } catch(...) {}
	  }
	  ghostTrack_isSecVtxTrk      .push_back( ghosttrackIsSecVtxTrk      );
	  ghostTrack_isSecVtxCleanTrk .push_back( ghosttrackIsSecVtxCleanTrk );
	  ghostTrack_isSecVtxFiltTrk  .push_back( ghosttrackIsSecVtxFiltTrk  );
	  ghostTrack_secVtxID         .push_back( secVtxID                   );
	  ghostTrack_secVtxIndex      .push_back( secVtxIndex                );
	  
	  // get linked truth particle
	  if ( m_mc ) {
	    bool ghosttrackHasTruthLink = false;
	    int  truthID                = AlgConsts::invalidInt;
	    int  truthIndex             = AlgConsts::invalidInt;
	    int  truthBarcode           = AlgConsts::invalidInt;
	    int  truthPdgId             = AlgConsts::invalidInt;
	    static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLink_t> ghosttruthAccess("truthParticleLink");
	    if ( ghosttruthAccess.isAvailable( *ghosttrack ) ) {
	      try {
		const EJsHelper::TruthParticleLink_t& ghosttruthLink = ghosttruthAccess( *ghosttrack );
		if ( *ghosttruthLink ) ghosttrackHasTruthLink = true;
		truthID      = AUXDYN( (*ghosttruthLink), int, "ID"    );
		truthIndex   = AUXDYN( (*ghosttruthLink), int, "index" );
		truthBarcode = (*ghosttruthLink)->barcode();
		truthPdgId   = (*ghosttruthLink)->pdgId(); 
	      } catch(...) {}
	    }
	    ghostTrack_isTruth      .push_back( ghosttrackHasTruthLink                                   );
	    ghostTrack_truthProb    .push_back( ghosttrack->auxdataConst<float>("truthMatchProbability") );
	    ghostTrack_truthID      .push_back( truthID                                                  );
	    ghostTrack_truthIndex   .push_back( truthIndex                                               );
	    ghostTrack_truthBarcode .push_back( truthBarcode                                             );
	    ghostTrack_truthPdgId   .push_back( truthPdgId                                               );
	  }
	}
      } // end loop over ghost track links
    } // end ghost track access
      
    m_GhostTrack_ID                 ->push_back( ghostTrack_ID               );
    m_GhostTrack_index              ->push_back( ghostTrack_index            );
    m_GhostTrack_m                  ->push_back( ghostTrack_m                );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTrackDetail ) {
      m_GhostTrack_errd0            ->push_back( ghostTrack_errd0            );
      m_GhostTrack_errz0            ->push_back( ghostTrack_errz0            );
      m_GhostTrack_chi2             ->push_back( ghostTrack_chi2             );
      m_GhostTrack_charge           ->push_back( ghostTrack_charge           );
      m_GhostTrack_isSelected       ->push_back( ghostTrack_isSelected       );
      m_GhostTrack_isAssociated     ->push_back( ghostTrack_isAssociated     );
      m_GhostTrack_isSecVtxTrk      ->push_back( ghostTrack_isSecVtxTrk      );
      m_GhostTrack_isSecVtxCleanTrk ->push_back( ghostTrack_isSecVtxCleanTrk );
      m_GhostTrack_isSecVtxFiltTrk  ->push_back( ghostTrack_isSecVtxFiltTrk  );
      m_GhostTrack_secVtxID         ->push_back( ghostTrack_secVtxID         );
      m_GhostTrack_secVtxIndex      ->push_back( ghostTrack_secVtxIndex      );
      if ( m_mc ) {
	m_GhostTrack_isTruth        ->push_back( ghostTrack_isTruth          );
	m_GhostTrack_truthProb      ->push_back( ghostTrack_truthProb        );
	m_GhostTrack_truthID        ->push_back( ghostTrack_truthID          );
	m_GhostTrack_truthIndex     ->push_back( ghostTrack_truthIndex       );
	m_GhostTrack_truthBarcode   ->push_back( ghostTrack_truthBarcode     );
	m_GhostTrack_truthPdgId     ->push_back( ghostTrack_truthPdgId       );
      }
    }
  } // end ghost track switch

  if ( ( m_infoSwitch.m_ghost || m_infoSwitch.m_ghostTruth ) && m_mc ) {
    std::vector<int>         ghostTruth_ID;
    std::vector<int>         ghostTruth_index;
    std::vector<float>       ghostTruth_pt;
    std::vector<float>       ghostTruth_eta;
    std::vector<float>       ghostTruth_phi;
    std::vector<float>       ghostTruth_e;
    std::vector<float>       ghostTruth_m;
    std::vector<float>       ghostTruth_charge;
    std::vector<int>         ghostTruth_pdgId;
    std::vector<int>         ghostTruth_status;
    std::vector<int>         ghostTruth_barcode;
    std::vector<uint8_t>     ghostTruth_isReco;
    std::vector<uint8_t>     ghostTruth_isSelected;
    std::vector<uint8_t>     ghostTruth_isAssociated;
    std::vector<float>       ghostTruth_recoProb;
    std::vector<int>         ghostTruth_recoID;
    std::vector<int>         ghostTruth_recoIndex;
    std::vector<uint8_t>     ghostTruth_isStable;
    std::vector<uint8_t>     ghostTruth_isInteracting;
    std::vector<uint8_t>     ghostTruth_isDark;
    std::vector<std::string> ghostTruth_pVtx_llpDecay;
    std::vector<int>         ghostTruth_pVtx_ID;
    std::vector<int>         ghostTruth_pVtx_index;
    std::vector<std::string> ghostTruth_dVtx_llpDecay;
    std::vector<int>         ghostTruth_dVtx_ID;
    std::vector<int>         ghostTruth_dVtx_index;

    // access ghost truth particles
    static SG::AuxElement::ConstAccessor<std::vector<ElementLink<DataVector<xAOD::IParticle> > > > ghostTruthAccess("GhostTruth");
    if ( ghostTruthAccess.isAvailable( *jet ) ) {
      std::vector<ElementLink<DataVector<xAOD::IParticle> > > ghostTruthLinks = ghostTruthAccess( *jet );
      for ( const auto& ghostlink : ghostTruthLinks ) {
	if ( !ghostlink.isValid() ) continue;
	const xAOD::TruthParticle* ghosttruth = dynamic_cast<const xAOD::TruthParticle*>( *ghostlink );
	ghostTruth_ID              .push_back( AUXDYN( ghosttruth, int, "ID"         ) );
	ghostTruth_index           .push_back( AUXDYN( ghosttruth, int, "index"      ) );
	ghostTruth_pt              .push_back( ghosttruth->pt() / m_units              );
	ghostTruth_eta             .push_back( ghosttruth->eta()                       );
	ghostTruth_phi             .push_back( ghosttruth->phi()                       );
	ghostTruth_e               .push_back( ghosttruth->e()  / m_units              );
	ghostTruth_m               .push_back( ghosttruth->m()  / m_units              );
	ghostTruth_charge          .push_back( ghosttruth->charge()                    );

	if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTruthDetail ) {
	  ghostTruth_pdgId         .push_back( ghosttruth->pdgId()                     );
	  ghostTruth_status        .push_back( ghosttruth->status()                    );
	  ghostTruth_barcode       .push_back( ghosttruth->barcode()                   );
	  ghostTruth_isStable      .push_back( EJsHelper::isStable      ( ghosttruth ) );
	  ghostTruth_isInteracting .push_back( EJsHelper::isInteracting ( ghosttruth ) );
	  ghostTruth_isDark        .push_back( EJsHelper::isDark        ( ghosttruth ) );
	  
	  // get linked track
	  int     recoID      = AlgConsts::invalidInt;
	  int     recoIndex   = AlgConsts::invalidInt;
	  uint8_t recoIsSel   = AlgConsts::invalidUnsigned;
	  uint8_t recoIsAssoc = AlgConsts::invalidUnsigned;
	  static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> ghostrecoAccess("trackLink");
	  if ( ghostrecoAccess.isAvailable( *ghosttruth ) ) {
	    try {
	      const EJsHelper::TrackLink_t& ghostrecoLink = ghostrecoAccess( *ghosttruth );
	      recoID      = AUXDYN( (*ghostrecoLink), int,  "ID"            );
	      recoIndex   = AUXDYN( (*ghostrecoLink), int,  "index"         );
	      recoIsSel   = AUXDYN( (*ghostrecoLink), char, "is_selected"   );
	      recoIsAssoc = AUXDYN( (*ghostrecoLink), char, "is_associated" );
	    } catch(...) {}
	  }
	  ghostTruth_isReco       .push_back( AUXDYN( ghosttruth, char, "isTrackMatch"           ) );
	  ghostTruth_recoProb     .push_back( AUXDYN( ghosttruth, float, "trackMatchProbability" ) );
	  ghostTruth_recoID       .push_back( recoID                                               );
	  ghostTruth_recoIndex    .push_back( recoIndex                                            );
	  ghostTruth_isSelected   .push_back( recoIsSel                                            );
	  ghostTruth_isAssociated .push_back( recoIsAssoc                                          );
	  
	  // get production vertex
	  std::string pVtx_llpDecay = "";
	  int         pVtx_ID       = AlgConsts::invalidInt;
	  int         pVtx_index    = AlgConsts::invalidInt;
	  if ( ghosttruth->hasProdVtx() ) {
	    const auto* pVtx = ghosttruth->prodVtx();
	    if ( pVtx ) {
	      for ( size_t i = 0; i != truthVtxLLPs.size(); ++i )
		if ( EJsHelper::pdgIdFuncs[truthVtxLLPs.at(i)]( pVtx ) ) pVtx_llpDecay = truthVtxLLPs.at(i);
	      pVtx_ID    = AUXDYN( pVtx, int, "ID"    );
	      pVtx_index = AUXDYN( pVtx, int, "index" );
	    }
	  }
	  ghostTruth_pVtx_llpDecay .push_back( pVtx_llpDecay );
	  ghostTruth_pVtx_ID       .push_back( pVtx_ID       );
	  ghostTruth_pVtx_index    .push_back( pVtx_index    );
	  
	  // get decay vertex
	  std::string dVtx_llpDecay = "";
	  int         dVtx_ID       = AlgConsts::invalidInt;
	  int         dVtx_index    = AlgConsts::invalidInt;
	  if ( ghosttruth->hasDecayVtx() ) {
	    const auto* dVtx = ghosttruth->decayVtx();
	    if ( dVtx ) {
	      for ( size_t i = 0; i != truthVtxLLPs.size(); ++i )
		if ( EJsHelper::pdgIdFuncs[truthVtxLLPs.at(i)]( dVtx ) ) dVtx_llpDecay = truthVtxLLPs.at(i);
	      dVtx_ID    = AUXDYN( dVtx, int, "ID"    );
	      dVtx_index = AUXDYN( dVtx, int, "index" );
	    }
	  }
	  ghostTruth_dVtx_llpDecay .push_back( dVtx_llpDecay );
	  ghostTruth_dVtx_ID       .push_back( dVtx_ID       );
	  ghostTruth_dVtx_index    .push_back( dVtx_index    );
	}
	  
      } // end loop over ghost truth links
    } // end ghost truth access
      
    m_GhostTruthCount            ->push_back( AUXDYN( jet, int,   "GhostTruthCount" )           );
    m_GhostTruthPt               ->push_back( AUXDYN( jet, float, "GhostTruthPt"    ) / m_units );
    m_GhostTruth_ID              ->push_back( ghostTruth_ID                                     );
    m_GhostTruth_index           ->push_back( ghostTruth_index                                  );
    m_GhostTruth_pt              ->push_back( ghostTruth_pt                                     );
    m_GhostTruth_eta             ->push_back( ghostTruth_eta                                    );
    m_GhostTruth_phi             ->push_back( ghostTruth_phi                                    );
    m_GhostTruth_e               ->push_back( ghostTruth_e                                      );
    m_GhostTruth_m               ->push_back( ghostTruth_m                                      );
    m_GhostTruth_charge          ->push_back( ghostTruth_charge                                 );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_ghostDetail || m_infoSwitch.m_ghostTruthDetail ) {
      m_GhostTruth_pdgId         ->push_back( ghostTruth_pdgId                                  );
      m_GhostTruth_status        ->push_back( ghostTruth_status                                 );
      m_GhostTruth_barcode       ->push_back( ghostTruth_barcode                                );
      m_GhostTruth_isReco        ->push_back( ghostTruth_isReco                                 );
      m_GhostTruth_isSelected    ->push_back( ghostTruth_isSelected                             );
      m_GhostTruth_isAssociated  ->push_back( ghostTruth_isAssociated                           );
      m_GhostTruth_recoProb      ->push_back( ghostTruth_recoProb                               );
      m_GhostTruth_recoID        ->push_back( ghostTruth_recoID                                 );
      m_GhostTruth_recoIndex     ->push_back( ghostTruth_recoIndex                              );
      m_GhostTruth_isStable      ->push_back( ghostTruth_isStable                               );
      m_GhostTruth_isInteracting ->push_back( ghostTruth_isInteracting                          );
      m_GhostTruth_isDark        ->push_back( ghostTruth_isDark                                 );
      m_GhostTruth_pVtx_llpDecay ->push_back( ghostTruth_pVtx_llpDecay                          );
      m_GhostTruth_pVtx_ID       ->push_back( ghostTruth_pVtx_ID                                );
      m_GhostTruth_pVtx_index    ->push_back( ghostTruth_pVtx_index                             );
      m_GhostTruth_dVtx_llpDecay ->push_back( ghostTruth_dVtx_llpDecay                          );
      m_GhostTruth_dVtx_ID       ->push_back( ghostTruth_dVtx_ID                                );
      m_GhostTruth_dVtx_index    ->push_back( ghostTruth_dVtx_index                             );
    }
  } // end ghost truth switch
  

  if ( m_infoSwitch.m_constituentAll ) {
    double               jconstitPtWeightedDR = 0;
    double               constituentPt        = 0;
    std::vector<float>   constituent_dR;
    std::vector<float>   constituent_m;
    std::vector<int>     constituent_ID;
    std::vector<int>     constituent_index;
    std::vector<float>   constituent_charge;
    std::vector<int>     constituent_pdgId;
    std::vector<int>     constituent_status;
    std::vector<int>     constituent_barcode;
    std::vector<uint8_t> constituent_isStable;
    std::vector<uint8_t> constituent_isInteracting;
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
	  constituent_ID              .push_back( AUXDYN( jconstit_tp, int, "ID"         ) );
	  constituent_index           .push_back( AUXDYN( jconstit_tp, int, "index"      ) );

	  if ( m_infoSwitch.m_detail || m_infoSwitch.m_constituentDetail ) {
	    constituent_charge        .push_back( jconstit_tp->charge()                    );
	    constituent_pdgId         .push_back( jconstit_tp->pdgId()                     );
	    constituent_status        .push_back( jconstit_tp->status()                    );
	    constituent_barcode       .push_back( jconstit_tp->barcode()                   );
	    constituent_isStable      .push_back( EJsHelper::isStable      ( jconstit_tp ) );
	    constituent_isInteracting .push_back( EJsHelper::isInteracting ( jconstit_tp ) );
	    constituent_isDark        .push_back( EJsHelper::isDark        ( jconstit_tp ) );
	  
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
	}
	
      } // end loop over constituents
    }
    
    float girth      = jconstitPtWeightedDR / jet->pt();
    m_girth          ->push_back( girth                   );
    m_constituentPt  ->push_back( constituentPt / m_units ); 
    m_constituent_dR ->push_back( constituent_dR          );
    m_constituent_m  ->push_back( constituent_m           );
    
    if ( jet_type == TRUTH || jet_type == DARK ) {
      m_constituent_ID              ->push_back( constituent_ID            );
      m_constituent_index           ->push_back( constituent_index         );
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_constituentDetail ) {
	m_constituent_charge        ->push_back( constituent_charge        );
	m_constituent_pdgId         ->push_back( constituent_pdgId         );
	m_constituent_status        ->push_back( constituent_status        );
	m_constituent_barcode       ->push_back( constituent_barcode       );
	m_constituent_isStable      ->push_back( constituent_isStable      );
	m_constituent_isInteracting ->push_back( constituent_isInteracting );
	m_constituent_isDark        ->push_back( constituent_isDark        );
	m_constituent_pVtx          ->push_back( constituent_pVtx          );
	m_constituent_pVtx_r        ->push_back( constituent_pVtx_r        );
	m_constituent_dVtx          ->push_back( constituent_dVtx          );
	m_constituent_dVtx_r        ->push_back( constituent_dVtx_r        );
      }
    }
  } // end constituentAll switch


  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    float truthJet_E   = AlgConsts::invalidFloat;
    float truthJet_M   = AlgConsts::invalidFloat;
    float truthJet_pt  = AlgConsts::invalidFloat;
    float truthJet_eta = AlgConsts::invalidFloat;
    float truthJet_phi = AlgConsts::invalidFloat;
    float darkJet_E    = AlgConsts::invalidFloat;
    float darkJet_M    = AlgConsts::invalidFloat;
    float darkJet_pt   = AlgConsts::invalidFloat;
    float darkJet_eta  = AlgConsts::invalidFloat;
    float darkJet_phi  = AlgConsts::invalidFloat;

    if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
      // access matched truth jet link
      const xAOD::Jet* truthJet = 0;
      static SG::AuxElement::ConstAccessor<EJsHelper::JetLink_t> truthJetAccess("truthJetMatchLink");
      if ( truthJetAccess.isAvailable( *jet ) ) {
	try {
	  const EJsHelper::JetLink_t& truthJetLink = truthJetAccess( *jet );
	  if ( truthJetLink.isValid() ) truthJet = *truthJetLink;
	} catch(...) {}
      }
      if ( truthJet ) {
	truthJet_E   = truthJet->e()  / m_units;
	truthJet_M   = truthJet->m()  / m_units;
	truthJet_pt  = truthJet->pt() / m_units;
	truthJet_eta = truthJet->eta();
	truthJet_phi = truthJet->phi();
      }
      
      // access matched truth dark jet link
      const xAOD::Jet* darkJet = 0;
      static SG::AuxElement::ConstAccessor<EJsHelper::JetLink_t> darkJetAccess("darkJetMatchLink");
      if ( darkJetAccess.isAvailable( *jet ) ) {
	try {
	  const EJsHelper::JetLink_t& darkJetLink = darkJetAccess( *jet );
	  if ( darkJetLink.isValid() ) darkJet = *darkJetLink;
	} catch(...) {}
      }
      if ( darkJet ) {
	darkJet_E   = darkJet->e()  / m_units;
	darkJet_M   = darkJet->m()  / m_units;
	darkJet_pt  = darkJet->pt() / m_units;
	darkJet_eta = darkJet->eta();
	darkJet_phi = darkJet->phi();
      }
    }

    if ( jet_type == RECO ) {
      m_isTruthMatched   ->push_back( AUXDYN( jet, char,  "hasTruthJetMatch"   ) );
      m_truthMatch_ID    ->push_back( AUXDYN( jet, int,   "truthJetMatchID"    ) );
      m_truthMatch_index ->push_back( AUXDYN( jet, int,   "truthJetMatchIndex" ) );
      m_truthMatch_dR    ->push_back( AUXDYN( jet, float, "truthJetMatchDR"    ) );
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	m_truthMatch_E   ->push_back( truthJet_E                                 );
	m_truthMatch_M   ->push_back( truthJet_M                                 );
	m_truthMatch_pt  ->push_back( truthJet_pt                                );
	m_truthMatch_eta ->push_back( truthJet_eta                               );
	m_truthMatch_phi ->push_back( truthJet_phi                               );
      }
    }
    if ( jet_type == RECO || jet_type == TRUTH ) {
      m_isDarkMatched    ->push_back( AUXDYN( jet, char,  "hasDarkJetMatch"    ) );
      m_darkMatch_ID     ->push_back( AUXDYN( jet, int,   "darkJetMatchID"     ) );
      m_darkMatch_index  ->push_back( AUXDYN( jet, int,   "darkJetMatchIndex"  ) );
      m_darkMatch_dR     ->push_back( AUXDYN( jet, float, "darkJetMatchDR"     ) );
      if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthJetDetail ) {
	m_darkMatch_E    ->push_back( darkJet_E                                  );
	m_darkMatch_M    ->push_back( darkJet_M                                  );
	m_darkMatch_pt   ->push_back( darkJet_pt                                 );
	m_darkMatch_eta  ->push_back( darkJet_eta                                );
	m_darkMatch_phi  ->push_back( darkJet_phi                                );
      }
    }
    if ( jet_type == DARK ) {
      m_isMatchedToTruth       ->push_back( AUXDYN( jet, char,  "isTruthMatched"  ) );
      m_matchedTruthID         ->push_back( AUXDYN( jet, int,   "truthMatchID"    ) );
      m_matchedTruthIndex      ->push_back( AUXDYN( jet, int,   "truthMatchIndex" ) );
      m_matchedTruthDR         ->push_back( AUXDYN( jet, float, "truthMatchDR"    ) );
    }
    if ( jet_type == DARK || jet_type == TRUTH ) {
      if ( m_doEMTopo ) {
	if ( jet->isAvailable<char>("isRecoMatched_EMTopo" + jet_str) ) {
	  m_isMatchedToEMTopo  ->push_back( jet->auxdataConst<char> ( "isRecoMatched_EMTopo"  + jet_str ) );
	  m_matchedEMTopoID    ->push_back( jet->auxdataConst<int>  ( "recoMatchID_EMTopo"    + jet_str ) );
	  m_matchedEMTopoIndex ->push_back( jet->auxdataConst<int>  ( "recoMatchIndex_EMTopo" + jet_str ) );
	  m_matchedEMTopoDR    ->push_back( jet->auxdataConst<float>( "recoMatchDR_EMTopo"    + jet_str ) );
	}
	else {
	  m_isMatchedToEMTopo  ->push_back( AUXDYN( jet, char,  "isRecoMatched_EMTopo"  ) );
	  m_matchedEMTopoID    ->push_back( AUXDYN( jet, int,   "recoMatchID_EMTopo"    ) );
	  m_matchedEMTopoIndex ->push_back( AUXDYN( jet, int,   "recoMatchIndex_EMTopo" ) );
	  m_matchedEMTopoDR    ->push_back( AUXDYN( jet, float, "recoMatchDR_EMTopo"    ) );
	}
      }
      if ( m_doPFlow ) {
	if ( jet->isAvailable<char>("isRecoMatched_PFlow" + jet_str) ) {
	  m_isMatchedToPFlow  ->push_back( jet->auxdataConst<char> ( "isRecoMatched_PFlow"  + jet_str  ) );
	  m_matchedPFlowID    ->push_back( jet->auxdataConst<int>  ( "recoMatchID_PFlow"    + jet_str  ) );
	  m_matchedPFlowIndex ->push_back( jet->auxdataConst<int>  ( "recoMatchIndex_PFlow" + jet_str  ) );
	  m_matchedPFlowDR    ->push_back( jet->auxdataConst<float>( "recoMatchDR_PFlow"    + jet_str  ) );
	}
	else {
	  m_isMatchedToPFlow  ->push_back( AUXDYN( jet, char,  "isRecoMatched_PFlow"  ) );
	  m_matchedPFlowID    ->push_back( AUXDYN( jet, int,   "recoMatchID_PFlow"    ) );
	  m_matchedPFlowIndex ->push_back( AUXDYN( jet, int,   "recoMatchIndex_PFlow" ) );
	  m_matchedPFlowDR    ->push_back( AUXDYN( jet, float, "recoMatchDR_PFlow"    ) );
	}
      }
    }
  } // end jet-match switch


  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_recoVerts ) {
    int                  matchDVCount   = 0;
    double               matchDVPt      = 0;
    double               matchDVCleanPt = 0;
    double               matchDVBarePt  = 0;
    std::vector<int>     matchDV_ID;
    std::vector<int>     matchDV_index;
    std::vector<float>   matchDV_x;
    std::vector<float>   matchDV_y;
    std::vector<float>   matchDV_z;
    std::vector<float>   matchDV_r;
    std::vector<float>   matchDV_pt;
    std::vector<float>   matchDV_eta;
    std::vector<float>   matchDV_phi;
    std::vector<float>   matchDV_mass;
    std::vector<float>   matchDV_cleanPt;
    std::vector<float>   matchDV_cleanEta;
    std::vector<float>   matchDV_cleanPhi;
    std::vector<float>   matchDV_cleanMass;
    std::vector<float>   matchDV_barePt;
    std::vector<float>   matchDV_bareEta;
    std::vector<float>   matchDV_barePhi;
    std::vector<float>   matchDV_bareMass;
    std::vector<float>   matchDV_chi2;
    std::vector<float>   matchDV_distToPV;
    std::vector<int>     matchDV_ntrk;
    std::vector<int>     matchDV_ntrk_sel;
    std::vector<int>     matchDV_ntrk_assoc;
    std::vector<int>     matchDV_ntrk_clean;
    std::vector<int>     matchDV_ntrk_clean_sel;
    std::vector<int>     matchDV_ntrk_clean_assoc;
    std::vector<int>     matchDV_ntrk_filt;
    std::vector<int>     matchDV_ntrk_filt_sel;
    std::vector<int>     matchDV_ntrk_filt_assoc;
    std::vector<float>   matchDV_dR;
    std::vector<uint8_t> matchDV_isTruth;
      
    // acccess matched secondary vertex links
    static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> matchDVAccess("matchedSecondaryVertexLinks");
    if ( matchDVAccess.isAvailable( *jet ) ) {
      const EJsHelper::VertexLinkVector_t& matchDVLinks = matchDVAccess( *jet );
	
      // loop over matched secondary vertex links
      for ( const auto& dvlink : matchDVLinks ) {
	if ( !dvlink.isValid() ) continue;
      
	// get vectors of vertex tracks
	std::vector<const xAOD::TrackParticle*> filteredTracks;
	std::vector<const xAOD::TrackParticle*> cleanTracks;
	std::vector<const xAOD::TrackParticle*> allTracks;
	EJsHelper::getFilteredTracks( (*dvlink), filteredTracks );
	EJsHelper::getCleanTracks   ( (*dvlink), cleanTracks    );
	EJsHelper::getAllTracks     ( (*dvlink), allTracks      );
	
	++matchDVCount;
	matchDV_ID               .push_back( AUXDYN( (*dvlink), int, "ID"                   ) );
	matchDV_index            .push_back( AUXDYN( (*dvlink), int, "index"                ) );
	matchDV_x                .push_back( (*dvlink)->x()                                   );
	matchDV_y                .push_back( (*dvlink)->y()                                   );
	matchDV_z                .push_back( (*dvlink)->z()                                   );
	matchDV_r                .push_back( (*dvlink)->position().perp()                     );
	matchDV_chi2             .push_back( (*dvlink)->chiSquared() / (*dvlink)->numberDoF() );
	matchDV_ntrk             .push_back( allTracks.size()                                 );
	matchDV_ntrk_clean       .push_back( cleanTracks.size()                               );
	matchDV_ntrk_filt        .push_back( filteredTracks.size()                            );


	if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_recoVtxDetail ) {
	  // get vector four-momentum
	  TLorentzVector dvP4       = VsiBonsai::sumP4 ( filteredTracks );
	  TLorentzVector dvP4_clean = VsiBonsai::sumP4 ( cleanTracks    );
	  TLorentzVector dvP4_bare  = VsiBonsai::sumP4 ( allTracks      );
	  
	  // count selected / associated tracks
	  size_t ntrk_sel = 0;
	  size_t ntrk_assoc = 0;
	  for ( const auto& trk : allTracks ) {
	    if ( trk->isAvailable<char>( "is_selected" ) )
	      if ( trk->auxdataConst<char>( "is_selected" ) ) ++ntrk_sel;
	    if ( trk->isAvailable<char>( "is_associated" ) )
	      if ( trk->auxdataConst<char>( "is_associated" ) ) ++ntrk_assoc;
	  }
	  size_t ntrk_clean_sel = 0;
	  size_t ntrk_clean_assoc = 0;
	  for ( const auto& cleanTrk : cleanTracks ) {
	    if ( cleanTrk->isAvailable<char>( "is_selected" ) )
	      if ( cleanTrk->auxdataConst<char>( "is_selected" ) ) ++ntrk_clean_sel;
	    if ( cleanTrk->isAvailable<char>( "is_associated" ) )
	      if ( cleanTrk->auxdataConst<char>( "is_associated" ) ) ++ntrk_clean_assoc;
	  }
	  size_t ntrk_filt_sel = 0;
	  size_t ntrk_filt_assoc = 0;
	  for ( const auto& filtTrk : filteredTracks ) {
	    if ( filtTrk->isAvailable<char>( "is_selected" ) )
	      if ( filtTrk->auxdataConst<char>( "is_selected" ) ) ++ntrk_filt_sel;
	    if ( filtTrk->isAvailable<char>( "is_associated" ) )
	      if ( filtTrk->auxdataConst<char>( "is_associated" ) ) ++ntrk_filt_assoc;
	  }
	  
	  // is vertex truth-matched ??
	  bool isTruthMatched = false;
	  if ( (*dvlink)->isAvailable<std::vector<float>>("truthVertexMatchScores") )
	    if ( !(*dvlink)->auxdataConst<std::vector<float>>("truthVertexMatchScores").empty() )
	      isTruthMatched = true;
	  
	  matchDVPt      += dvP4       .Pt();
	  matchDVCleanPt += dvP4_clean .Pt();
	  matchDVBarePt  += dvP4_bare  .Pt();	
	  
	  matchDV_pt               .push_back( dvP4.Pt()       / m_units                        );
	  matchDV_eta              .push_back( dvP4.Eta()                                       );
	  matchDV_phi              .push_back( dvP4.Phi()                                       );
	  matchDV_mass             .push_back( dvP4.M()        / m_units                        );
	  matchDV_cleanPt          .push_back( dvP4_clean.Pt() / m_units                        );
	  matchDV_cleanEta         .push_back( dvP4_clean.Eta()                                 );
	  matchDV_cleanPhi         .push_back( dvP4_clean.Phi()                                 );
	  matchDV_cleanMass        .push_back( dvP4_clean.M()  / m_units                        );
	  matchDV_barePt           .push_back( dvP4_bare.Pt()  / m_units                        );
	  matchDV_bareEta          .push_back( dvP4_bare.Eta()                                  );
	  matchDV_barePhi          .push_back( dvP4_bare.Phi()                                  );
	  matchDV_bareMass         .push_back( dvP4_bare.M()   / m_units                        );
	  matchDV_distToPV         .push_back( AUXDYN( (*dvlink), float, "distToPV"           ) );
	  matchDV_ntrk_sel         .push_back( ntrk_sel                                         );
	  matchDV_ntrk_assoc       .push_back( ntrk_assoc                                       );
	  matchDV_ntrk_clean_sel   .push_back( ntrk_clean_sel                                   );
	  matchDV_ntrk_clean_assoc .push_back( ntrk_clean_assoc                                 );
	  matchDV_ntrk_filt_sel    .push_back( ntrk_filt_sel                                    );
	  matchDV_ntrk_filt_assoc  .push_back( ntrk_filt_assoc                                  );
	  matchDV_isTruth          .push_back( isTruthMatched                                   );
	}
	  
      } // end loop over matched DV links
    } // end matched secondary vertex link access
      
    m_secVtxCount               ->push_back( matchDVCount                                          );
    m_secVtx_ID                 ->push_back( matchDV_ID                                            );
    m_secVtx_index              ->push_back( matchDV_index                                         );
    m_secVtx_x                  ->push_back( matchDV_x                                             );
    m_secVtx_y                  ->push_back( matchDV_y                                             );
    m_secVtx_z                  ->push_back( matchDV_z                                             );
    m_secVtx_r                  ->push_back( matchDV_r                                             );
    m_secVtx_chi2               ->push_back( matchDV_chi2                                          );
    m_secVtx_ntrk               ->push_back( matchDV_ntrk                                          );
    m_secVtx_ntrk_clean         ->push_back( matchDV_ntrk_clean                                    );
    m_secVtx_ntrk_filt          ->push_back( matchDV_ntrk_filt                                     );
    m_secVtx_dR                 ->push_back( AUXDYNVEC ( jet, float, "matchedSecondaryVertex_dR" ) );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_recoVtxDetail ) {
      m_secVtxPt                ->push_back( matchDVPt      / m_units                              );
      m_secVtxCleanPt           ->push_back( matchDVCleanPt / m_units                              );
      m_secVtxBarePt            ->push_back( matchDVBarePt  / m_units                              );
      m_secVtx_pt               ->push_back( matchDV_pt                                            );
      m_secVtx_eta              ->push_back( matchDV_eta                                           );
      m_secVtx_phi              ->push_back( matchDV_phi                                           );
      m_secVtx_mass             ->push_back( matchDV_mass                                          );
      m_secVtx_pt_clean         ->push_back( matchDV_cleanPt                                       );
      m_secVtx_eta_clean        ->push_back( matchDV_cleanEta                                      );
      m_secVtx_phi_clean        ->push_back( matchDV_cleanPhi                                      );
      m_secVtx_mass_clean       ->push_back( matchDV_cleanMass                                     );
      m_secVtx_pt_bare          ->push_back( matchDV_barePt                                        );
      m_secVtx_eta_bare         ->push_back( matchDV_bareEta                                       );
      m_secVtx_phi_bare         ->push_back( matchDV_barePhi                                       );
      m_secVtx_mass_bare        ->push_back( matchDV_bareMass                                      );
      m_secVtx_distToPV         ->push_back( matchDV_distToPV                                      );
      m_secVtx_ntrk_sel         ->push_back( matchDV_ntrk_sel                                      );
      m_secVtx_ntrk_assoc       ->push_back( matchDV_ntrk_assoc                                    );
      m_secVtx_ntrk_clean_sel   ->push_back( matchDV_ntrk_clean_sel                                );
      m_secVtx_ntrk_clean_assoc ->push_back( matchDV_ntrk_clean_assoc                              );
      m_secVtx_ntrk_filt_sel    ->push_back( matchDV_ntrk_filt_sel                                 );
      m_secVtx_ntrk_filt_assoc  ->push_back( matchDV_ntrk_filt_assoc                               );
      m_secVtx_isTruthMatched   ->push_back( matchDV_isTruth                                       );
    }
  } // end reco-vertex switch

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_vertices || m_infoSwitch.m_truthVerts ) && m_mc ) {
    int                      matchTVCount = 0;
    double                   matchTVPt    = 0;
    std::vector<std::string> matchTV_llpDecay;
    std::vector<int>         matchTV_ID;
    std::vector<int>         matchTV_index;
    std::vector<float>       matchTV_x;
    std::vector<float>       matchTV_y;
    std::vector<float>       matchTV_z;
    std::vector<float>       matchTV_r;
    std::vector<float>       matchTV_pt;
    std::vector<float>       matchTV_eta;
    std::vector<float>       matchTV_phi;
    std::vector<float>       matchTV_mass;
    std::vector<int>         matchTV_nOutP;
    std::vector<int>         matchTV_barcode;
    std::vector<float>       matchTV_dR;
    std::vector<uint8_t>     matchTV_isReconstructible;
    std::vector<uint8_t>     matchTV_isReco;

    // access matched truth vertex links
    static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLinkVector_t> matchTVAccess("matchedTruthVertexLinks");
    if ( matchTVAccess.isAvailable( *jet ) ) {
      const EJsHelper::TruthVertexLinkVector_t& matchTVLinks = matchTVAccess( *jet );

      // loop over matched truth vertex links
      for ( const auto& tvlink : matchTVLinks ) {
	if ( !tvlink.isValid() ) continue;

	++matchTVCount;

	std::string llpDecayType = "";
	for ( size_t i = 0; i != truthVtxLLPs.size(); ++i )
	  if ( EJsHelper::pdgIdFuncs[truthVtxLLPs.at(i)]( (*tvlink) ) ) llpDecayType = truthVtxLLPs.at(i);
	  
	matchTV_llpDecay .push_back( llpDecayType                        );
	matchTV_ID       .push_back( AUXDYN( (*tvlink), int,   "ID"    ) );
	matchTV_index    .push_back( AUXDYN( (*tvlink), int,   "index" ) );
	matchTV_x        .push_back( (*tvlink)->x()                      );
	matchTV_y        .push_back( (*tvlink)->y()                      );
	matchTV_z        .push_back( (*tvlink)->z()                      );
	matchTV_r        .push_back( (*tvlink)->perp()                   );
	matchTV_nOutP    .push_back( (*tvlink)->nOutgoingParticles()     );

	
	if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_truthVtxDetail ) {
	  std::vector<const xAOD::TruthParticle*> tvOutParts;
	  for ( size_t i = 0; i != (*tvlink)->nOutgoingParticles(); ++i ) {
	    const auto* tvOutP = (*tvlink)->outgoingParticle(i);
	    if ( tvOutP ) tvOutParts .push_back( tvOutP );
	  }
	  const TLorentzVector& tvSumP4 = EJsHelper::truthSumP4( tvOutParts );
	  matchTV_pt      .push_back( tvSumP4.Pt() / m_units );
	  matchTV_mass    .push_back( tvSumP4.M()  / m_units );

	  matchTVPt += tvSumP4.Pt();
	  
	  bool isRecoMatched = false;
	  if ( (*tvlink)->isAvailable<std::vector<float>>("matchedRecoVertexMatchScores") )
	    if ( !(*tvlink)->auxdataConst<std::vector<float>>("matchedRecoVertexMatchScores").empty() )
	      isRecoMatched = true;
	  
	  matchTV_eta               .push_back( (*tvlink)->eta()                               );
	  matchTV_phi               .push_back( (*tvlink)->phi()                               );
	  matchTV_barcode           .push_back( (*tvlink)->barcode()                           );
	  matchTV_isReco            .push_back( isRecoMatched                                  );
	  matchTV_isReconstructible .push_back( AUXDYN( (*tvlink), char, "isReconstructible" ) );
	}
	  
      } // end loop over matched truth vertex links
    } // end matched truth vertex link access

    m_truthVtxCount                ->push_back( matchTVCount                                     );
    m_truthVtx_llpDecay            ->push_back( matchTV_llpDecay                                 );
    m_truthVtx_ID                  ->push_back( matchTV_ID                                       );
    m_truthVtx_index               ->push_back( matchTV_index                                    );
    m_truthVtx_x                   ->push_back( matchTV_x                                        );
    m_truthVtx_y                   ->push_back( matchTV_y                                        );
    m_truthVtx_z                   ->push_back( matchTV_z                                        );
    m_truthVtx_r                   ->push_back( matchTV_r                                        );
    m_truthVtx_nOutP               ->push_back( matchTV_nOutP                                    );
    m_truthVtx_dR                  ->push_back( AUXDYNVEC( jet, float, "matchedTruthVertex_dR" ) );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_vertexDetail || m_infoSwitch.m_truthVtxDetail ) {
      m_truthVtxPt                 ->push_back( matchTVPt / m_units                              );
      m_truthVtx_pt                ->push_back( matchTV_pt                                       );
      m_truthVtx_eta               ->push_back( matchTV_eta                                      );
      m_truthVtx_phi               ->push_back( matchTV_phi                                      );
      m_truthVtx_mass              ->push_back( matchTV_mass                                     );
      m_truthVtx_barcode           ->push_back( matchTV_barcode                                  );
      m_truthVtx_isReconstructible ->push_back( matchTV_isReconstructible                        );
      m_truthVtx_isRecoMatched     ->push_back( matchTV_isReco                                   );
    }
  } // end truth-vertex switch


  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    int                  matchTrkCount = 0;
    double               matchTrkPt    = 0;
    std::vector<int>     matchTrk_ID;
    std::vector<int>     matchTrk_index;
    std::vector<float>   matchTrk_qOverP;
    std::vector<float>   matchTrk_E;
    std::vector<float>   matchTrk_M;
    std::vector<float>   matchTrk_pt;
    std::vector<float>   matchTrk_eta;
    std::vector<float>   matchTrk_phi;
    std::vector<float>   matchTrk_d0;
    std::vector<float>   matchTrk_z0;
    std::vector<float>   matchTrk_errd0;
    std::vector<float>   matchTrk_errz0;
    std::vector<float>   matchTrk_chi2;
    std::vector<float>   matchTrk_charge;
    std::vector<uint8_t> matchTrk_isSelected;
    std::vector<uint8_t> matchTrk_isAssociated;
    std::vector<uint8_t> matchTrk_isSecVtxTrk;
    std::vector<uint8_t> matchTrk_isSecVtxCleanTrk;
    std::vector<uint8_t> matchTrk_isSecVtxFiltTrk;
    std::vector<int>     matchTrk_secVtxID;
    std::vector<int>     matchTrk_secVtxIndex;
    std::vector<uint8_t> matchTrk_isTruth;
    std::vector<float>   matchTrk_truthProb;
    std::vector<int>     matchTrk_truthID;
    std::vector<int>     matchTrk_truthIndex;
    std::vector<int>     matchTrk_truthBarcode;
    std::vector<int>     matchTrk_truthPdgId;

    // access matched track links
    static SG::AuxElement::ConstAccessor<EJsHelper::TrackLinkVector_t> matchTrkAccess("matchedTrackLinks");
    if ( matchTrkAccess.isAvailable( *jet ) ) {
      const EJsHelper::TrackLinkVector_t& matchTrkLinks = matchTrkAccess( *jet );

      // loop over matched track links
      for ( const auto& trklink : matchTrkLinks ) {
	if ( !trklink.isValid() ) continue;
	
	++matchTrkCount;
	matchTrkPt += (*trklink)->pt();
	
	matchTrk_ID             .push_back( AUXDYN( (*trklink), int, "ID"                                               ) );
	matchTrk_index          .push_back( AUXDYN( (*trklink), int, "index"                                            ) );
	matchTrk_qOverP         .push_back( (*trklink)->qOverP() * m_units                                                );
	matchTrk_E              .push_back( (*trklink)->e()      / m_units                                                );
	matchTrk_M              .push_back( (*trklink)->m()      / m_units                                                );
	matchTrk_pt             .push_back( (*trklink)->pt()     / m_units                                                );
	matchTrk_eta            .push_back( (*trklink)->eta()                                                             );
	matchTrk_phi            .push_back( (*trklink)->phi()                                                             );
	matchTrk_d0             .push_back( (*trklink)->d0()                                                              );
	matchTrk_z0             .push_back( (*trklink)->z0()                                                              );

	if ( m_infoSwitch.m_detail || m_infoSwitch.m_trackPartDetail ) {
	  matchTrk_errd0        .push_back( (*trklink)->definingParametersCovMatrix()(0,0)                                );
	  matchTrk_errz0        .push_back( (*trklink)->definingParametersCovMatrix()(1,1)                                );
	  matchTrk_chi2         .push_back( (*trklink)->chiSquared() / (*trklink)->numberDoF() / AlgConsts::infinitesimal );
	  matchTrk_charge       .push_back( (*trklink)->charge()                                                          );
	  matchTrk_isSelected   .push_back( AUXDYN( (*trklink), char, "is_selected"                                     ) );
	  matchTrk_isAssociated .push_back( AUXDYN( (*trklink), char, "is_associated"                                   ) );

	  // get linked secondary vertex
	  bool matchTrackIsSecVtxTrk      = false;
	  bool matchTrackIsSecVtxCleanTrk = false;
	  bool matchTrackIsSecVtxFiltTrk  = false;
	  int  secVtxID                   = AlgConsts::invalidInt;
	  int  secVtxIndex                = AlgConsts::invalidInt;
	  static SG::AuxElement::ConstAccessor<EJsHelper::VertexLink_t> secVtxAccess("secondaryVertexLink");
	  if ( secVtxAccess.isAvailable( **trklink ) ) {
	    try {
	      const EJsHelper::VertexLink_t& secVtxLink = secVtxAccess( **trklink );
	      if ( *secVtxLink ) matchTrackIsSecVtxTrk = true;
	      if ( (*trklink)->isAvailable<char>("isClean") )
		matchTrackIsSecVtxCleanTrk = (*trklink)->auxdataConst<char>("isClean");
	      if ( (*trklink)->isAvailable<char>("isFiltered") )
		matchTrackIsSecVtxFiltTrk  = (*trklink)->auxdataConst<char>("isFiltered");
	      secVtxID    = AUXDYN( (*secVtxLink), int, "ID" );
	      secVtxIndex = AUXDYN( (*secVtxLink), int, "index" );
	    } catch(...) {}
	  }
	  matchTrk_isSecVtxTrk      .push_back( matchTrackIsSecVtxTrk      );
	  matchTrk_isSecVtxCleanTrk .push_back( matchTrackIsSecVtxCleanTrk );
	  matchTrk_isSecVtxFiltTrk  .push_back( matchTrackIsSecVtxFiltTrk  );
	  matchTrk_secVtxID         .push_back( secVtxID                   );
	  matchTrk_secVtxIndex      .push_back( secVtxIndex                );
	  
	  // get linked truth particle
	  if ( m_mc ) {
	    bool matchTrackHasTruthLink = false;
	    int  truthID                = AlgConsts::invalidInt;
	    int  truthIndex             = AlgConsts::invalidInt;
	    int  truthBarcode           = AlgConsts::invalidInt;
	    int  truthPdgId             = AlgConsts::invalidInt;
	    static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLink_t> truthAccess("truthParticleLink");
	    if ( truthAccess.isAvailable( **trklink ) ) {
	      try {
		const EJsHelper::TruthParticleLink_t& truthLink = truthAccess( **trklink );
		if ( *truthLink ) matchTrackHasTruthLink = true;
		truthID      = AUXDYN( (*truthLink), int, "ID"    );
		truthIndex   = AUXDYN( (*truthLink), int, "index" );
		truthBarcode = (*truthLink)->barcode();
		truthPdgId   = (*truthLink)->pdgId();
	      } catch(...) {}
	    }
	    matchTrk_isTruth      .push_back( matchTrackHasTruthLink                                   );
	    matchTrk_truthProb    .push_back( (*trklink)->auxdataConst<float>("truthMatchProbability") );
	    matchTrk_truthID      .push_back( truthID                                                  );
	    matchTrk_truthIndex   .push_back( truthIndex                                               );
	    matchTrk_truthBarcode .push_back( truthBarcode                                             );
	    matchTrk_truthPdgId   .push_back( truthPdgId                                               );
	  }
	}
	  
      } // end loop over matched track links
    } // end matched track link access

    m_trkCount               ->push_back( matchTrkCount                              );
    m_trkPt                  ->push_back( matchTrkPt / m_units                       );
    m_trk_ID                 ->push_back( matchTrk_ID                                );
    m_trk_index              ->push_back( matchTrk_index                             );
    m_trk_qOverP             ->push_back( matchTrk_qOverP                            );
    m_trk_E                  ->push_back( matchTrk_E                                 );
    m_trk_M                  ->push_back( matchTrk_M                                 );
    m_trk_pt                 ->push_back( matchTrk_pt                                );
    m_trk_eta                ->push_back( matchTrk_eta                               );
    m_trk_phi                ->push_back( matchTrk_phi                               );
    m_trk_d0                 ->push_back( matchTrk_d0                                );
    m_trk_z0                 ->push_back( matchTrk_z0                                );
    m_trk_dR                 ->push_back( AUXDYNVEC( jet, float, "matchedTrack_dR" ) );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_trackPartDetail ) {
      m_trk_errd0            ->push_back( matchTrk_errd0                             );
      m_trk_errz0            ->push_back( matchTrk_errz0                             );
      m_trk_chi2             ->push_back( matchTrk_chi2                              );
      m_trk_charge           ->push_back( matchTrk_charge                            );
      m_trk_isSelected       ->push_back( matchTrk_isSelected                        );
      m_trk_isAssociated     ->push_back( matchTrk_isAssociated                      );
      m_trk_isSecVtxTrk      ->push_back( matchTrk_isSecVtxTrk                       );
      m_trk_isSecVtxCleanTrk ->push_back( matchTrk_isSecVtxCleanTrk                  );
      m_trk_isSecVtxFiltTrk  ->push_back( matchTrk_isSecVtxFiltTrk                   );
      m_trk_secVtxID         ->push_back( matchTrk_secVtxID                          );
      m_trk_secVtxIndex      ->push_back( matchTrk_secVtxIndex                       );
      if ( m_mc ) {
	m_trk_isTruth        ->push_back( matchTrk_isTruth                           );
	m_trk_truthProb      ->push_back( matchTrk_truthProb                         );
	m_trk_truthID        ->push_back( matchTrk_truthID                           );
	m_trk_truthIndex     ->push_back( matchTrk_truthIndex                        );
	m_trk_truthBarcode   ->push_back( matchTrk_truthBarcode                      );
	m_trk_truthPdgId     ->push_back( matchTrk_truthPdgId                        );
      }
    }
  } // end track-match switch

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthParts ) && m_mc ) {
    int                      matchTruthCount = 0;
    double                   matchTruthPt    = 0;
    std::vector<int>         matchTruth_ID;
    std::vector<int>         matchTruth_index;
    std::vector<float>       matchTruth_pt;
    std::vector<float>       matchTruth_eta;
    std::vector<float>       matchTruth_phi;
    std::vector<float>       matchTruth_E;
    std::vector<float>       matchTruth_M;
    std::vector<float>       matchTruth_charge;
    std::vector<int>         matchTruth_pdgId;
    std::vector<int>         matchTruth_status;
    std::vector<int>         matchTruth_barcode;
    std::vector<float>       matchTruth_dR;
    std::vector<uint8_t>     matchTruth_isReco;
    std::vector<uint8_t>     matchTruth_isSelected;
    std::vector<uint8_t>     matchTruth_isAssociated;
    std::vector<float>       matchTruth_recoProb;
    std::vector<int>         matchTruth_recoID;
    std::vector<int>         matchTruth_recoIndex;
    std::vector<uint8_t>     matchTruth_isStable;
    std::vector<uint8_t>     matchTruth_isInteracting;
    std::vector<uint8_t>     matchTruth_isDark;
    std::vector<std::string> matchTruth_pVtx_llpDecay;
    std::vector<int>         matchTruth_pVtx_ID;
    std::vector<int>         matchTruth_pVtx_index;
    std::vector<std::string> matchTruth_dVtx_llpDecay;
    std::vector<int>         matchTruth_dVtx_ID;
    std::vector<int>         matchTruth_dVtx_index;

    // access matched truth particle links
    static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLinkVector_t> matchTruthAccess("matchedTruthParticleLinks");
    if ( matchTruthAccess.isAvailable( *jet ) ) {
      const EJsHelper::TruthParticleLinkVector_t& matchTruthLinks = matchTruthAccess( *jet );

      // loop over matched truth particle links
      for ( const auto& truthlink : matchTruthLinks ) {
	if ( !truthlink.isValid() ) continue;

	++matchTruthCount;
	matchTruthPt += (*truthlink)->pt();

	matchTruth_ID              .push_back( AUXDYN( (*truthlink), int, "ID"         ) );
	matchTruth_index           .push_back( AUXDYN( (*truthlink), int, "index"      ) );
	matchTruth_pt              .push_back( (*truthlink)->pt() / m_units              );
	matchTruth_eta             .push_back( (*truthlink)->eta()                       );
	matchTruth_phi             .push_back( (*truthlink)->phi()                       );
	matchTruth_E               .push_back( (*truthlink)->e()  / m_units              );
	matchTruth_M               .push_back( (*truthlink)->m()  / m_units              );
	matchTruth_charge          .push_back( (*truthlink)->charge()                    );

	if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthPartDetail ) {
	  matchTruth_pdgId         .push_back( (*truthlink)->pdgId()                     );
	  matchTruth_status        .push_back( (*truthlink)->status()                    );
	  matchTruth_barcode       .push_back( (*truthlink)->barcode()                   );
	  matchTruth_isStable      .push_back( EJsHelper::isStable      ( (*truthlink) ) );
	  matchTruth_isInteracting .push_back( EJsHelper::isInteracting ( (*truthlink) ) );
	  matchTruth_isDark        .push_back( EJsHelper::isDark        ( (*truthlink) ) );
	  
	  // get linked track
	  int     recoID      = AlgConsts::invalidInt;
	  int     recoIndex   = AlgConsts::invalidInt;
	  uint8_t recoIsSel   = AlgConsts::invalidUnsigned;
	  uint8_t recoIsAssoc = AlgConsts::invalidUnsigned;
	  static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> recoAccess("trackLink");
	  if ( recoAccess.isAvailable( **truthlink ) ) {
	    try {
	      const EJsHelper::TrackLink_t& recoLink = recoAccess( **truthlink );
	      recoID      = AUXDYN( (*recoLink), int,  "ID"            );
	      recoIndex   = AUXDYN( (*recoLink), int,  "index"         );
	      recoIsSel   = AUXDYN( (*recoLink), char, "is_selected"   );
	      recoIsAssoc = AUXDYN( (*recoLink), char, "is_associated" );
	    } catch(...) {}
	  }
	  matchTruth_isReco       .push_back( AUXDYN( (*truthlink), char,  "isTrackMatch"          ) );
	  matchTruth_recoProb     .push_back( AUXDYN( (*truthlink), float, "trackMatchProbability" ) );
	  matchTruth_recoID       .push_back( recoID                                                 );
	  matchTruth_recoIndex    .push_back( recoIndex                                              );
	  matchTruth_isSelected   .push_back( recoIsSel                                              );
	  matchTruth_isAssociated .push_back( recoIsAssoc                                            );
	  
	  // get production vertex
	  std::string pVtx_llpDecay = "";
	  int         pVtx_ID       = AlgConsts::invalidInt;
	  int         pVtx_index    = AlgConsts::invalidInt;
	  if ( (*truthlink)->hasProdVtx() ) {
	    const auto* pVtx = (*truthlink)->prodVtx();
	    if ( pVtx ) {
	      for ( size_t i = 0; i != truthVtxLLPs.size(); ++i )
		if ( EJsHelper::pdgIdFuncs[truthVtxLLPs.at(i)]( pVtx ) ) pVtx_llpDecay = truthVtxLLPs.at(i);
	      pVtx_ID    = AUXDYN( pVtx, int, "ID"    );
	      pVtx_index = AUXDYN( pVtx, int, "index" );
	    }
	  }
	  matchTruth_pVtx_llpDecay .push_back( pVtx_llpDecay );
	  matchTruth_pVtx_ID       .push_back( pVtx_ID       );
	  matchTruth_pVtx_index    .push_back( pVtx_index    );
	  
	  // get decay vertex
	  std::string dVtx_llpDecay = "";
	  int         dVtx_ID       = AlgConsts::invalidInt;
	  int         dVtx_index    = AlgConsts::invalidInt;
	  if ( (*truthlink)->hasDecayVtx() ) {
	    const auto* dVtx = (*truthlink)->decayVtx();
	    if ( dVtx ) {
	      for ( size_t i = 0; i != truthVtxLLPs.size(); ++i )
		if ( EJsHelper::pdgIdFuncs[truthVtxLLPs.at(i)]( dVtx ) ) dVtx_llpDecay = truthVtxLLPs.at(i);
	      dVtx_ID    = AUXDYN( dVtx, int, "ID"    );
	      dVtx_index = AUXDYN( dVtx, int, "index" );
	    }
	  }
	  matchTruth_dVtx_llpDecay .push_back( dVtx_llpDecay );
	  matchTruth_dVtx_ID       .push_back( dVtx_ID       );
	  matchTruth_dVtx_index    .push_back( dVtx_index    );
	}
	  
      } // end loop over matched truth particle links
    } // end matched truth particle link access

    m_tpCount            ->push_back( matchTruthCount                                    );
    m_tpPt               ->push_back( matchTruthPt / m_units                             );
    m_tp_ID              ->push_back( matchTruth_ID                                      );
    m_tp_index           ->push_back( matchTruth_index                                   );
    m_tp_pt              ->push_back( matchTruth_pt                                      ); 
    m_tp_eta             ->push_back( matchTruth_eta                                     );
    m_tp_phi             ->push_back( matchTruth_phi                                     );
    m_tp_E               ->push_back( matchTruth_E                                       );
    m_tp_M               ->push_back( matchTruth_M                                       );
    m_tp_charge          ->push_back( matchTruth_charge                                  );
    m_tp_dR              ->push_back( AUXDYNVEC( jet, float, "matchedTruthParticle_dR" ) );
    if ( m_infoSwitch.m_detail || m_infoSwitch.m_truthPartDetail ) {
      m_tp_pdgId         ->push_back( matchTruth_pdgId                                   );
      m_tp_status        ->push_back( matchTruth_status                                  );
      m_tp_barcode       ->push_back( matchTruth_barcode                                 );
      m_tp_isReco        ->push_back( matchTruth_isReco                                  );
      m_tp_isSelected    ->push_back( matchTruth_isSelected                              );
      m_tp_isAssociated  ->push_back( matchTruth_isAssociated                            );
      m_tp_recoProb      ->push_back( matchTruth_recoProb                                );
      m_tp_recoID        ->push_back( matchTruth_recoID                                  );
      m_tp_recoIndex     ->push_back( matchTruth_recoIndex                               );
      m_tp_isStable      ->push_back( matchTruth_isStable                                );
      m_tp_isInteracting ->push_back( matchTruth_isInteracting                           );
      m_tp_isDark        ->push_back( matchTruth_isDark                                  );
      m_tp_pVtx_llpDecay ->push_back( matchTruth_pVtx_llpDecay                           );
      m_tp_pVtx_ID       ->push_back( matchTruth_pVtx_ID                                 );
      m_tp_pVtx_index    ->push_back( matchTruth_pVtx_index                              );
      m_tp_dVtx_llpDecay ->push_back( matchTruth_dVtx_llpDecay                           );
      m_tp_dVtx_ID       ->push_back( matchTruth_dVtx_ID                                 );
      m_tp_dVtx_index    ->push_back( matchTruth_dVtx_index                              );
    }
  } // end truth particle switch

}
