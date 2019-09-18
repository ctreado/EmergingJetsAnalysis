#include <xAODTruth/TruthVertex.h>
#include <xAODTruth/TruthParticle.h>

#include "EJsAnalysis/TruthVertexContainer.h"
#include "EJsAnalysis/TruthVertexPosition.h"
#include "EJsAnalysis/EJsHelperFunctions.h"
#include "EJsAnalysis/VsiBonsaiTool.h"
#include "EJsAnalysis/AlgConsts.h"

using namespace EJs;

TruthVertexContainer :: TruthVertexContainer ( const std::string& name, const std::string& detailStr, float units,
					       bool mc, bool emtopo, bool pflow ) :
  VertexContainer ( name, detailStr, units, mc )
{
  m_doEMTopo = emtopo;
  m_doPFlow  = pflow;
  
  if ( m_debug ) Info( "EJs::TruthVertexContainer()", "setting up" );

  m_passSel             = new std::vector<uint8_t>;
  m_llpDecay            = new std::vector<std::string>;
  m_ID                  = new std::vector<int>;
  m_index               = new std::vector<int>;
  m_x                   = new std::vector<float>;
  m_y                   = new std::vector<float>;
  m_z                   = new std::vector<float>;
  m_r                   = new std::vector<float>;
  m_pt                  = new std::vector<float>;
  m_eta                 = new std::vector<float>;
  m_phi                 = new std::vector<float>;
  m_mass                = new std::vector<float>;
  m_nOutP               = new std::vector<int>;
  m_barcode             = new std::vector<int>;
  m_childOpenAngle      = new std::vector<float>;
  m_parent_ID           = new std::vector<int>;
  m_parent_index        = new std::vector<int>;
  m_parent_pt           = new std::vector<float>;
  m_parent_eta          = new std::vector<float>;
  m_parent_phi          = new std::vector<float>;
  m_parent_E            = new std::vector<float>;
  m_parent_M            = new std::vector<float>;
  m_parent_charge       = new std::vector<float>;
  m_parent_pdgId        = new std::vector<int>;
  m_parent_status       = new std::vector<int>;
  m_parent_barcode      = new std::vector<int>;
  m_parent_prod_ID      = new std::vector<int>;
  m_parent_prod_index   = new std::vector<int>;
  m_parent_prod_x       = new std::vector<float>;
  m_parent_prod_y       = new std::vector<float>;
  m_parent_prod_z       = new std::vector<float>;
  m_parent_prod_r       = new std::vector<float>;
  m_parent_prod_pt      = new std::vector<float>;
  m_parent_prod_eta     = new std::vector<float>;
  m_parent_prod_phi     = new std::vector<float>;
  m_parent_prod_mass    = new std::vector<float>;
  m_parent_prod_nOutP   = new std::vector<int>;
  m_parent_prod_barcode = new std::vector<int>;
  m_outP_ID             = new std::vector<std::vector<int>>;
  m_outP_index          = new std::vector<std::vector<int>>;
  m_outP_pt             = new std::vector<std::vector<float>>;
  m_outP_eta            = new std::vector<std::vector<float>>;
  m_outP_phi            = new std::vector<std::vector<float>>;
  m_outP_E              = new std::vector<std::vector<float>>;
  m_outP_M              = new std::vector<std::vector<float>>;
  m_outP_charge         = new std::vector<std::vector<float>>;
  m_outP_pdgId          = new std::vector<std::vector<int>>;
  m_outP_status         = new std::vector<std::vector<int>>;
  m_outP_barcode        = new std::vector<std::vector<int>>;
  m_outP_isReco         = new std::vector<std::vector<uint8_t>>;
  m_outP_isSelected     = new std::vector<std::vector<uint8_t>>;
  m_outP_isAssociated   = new std::vector<std::vector<uint8_t>>;
  m_outP_recoProb       = new std::vector<std::vector<float>>;
  m_outP_recoID         = new std::vector<std::vector<int>>;
  m_outP_recoIndex      = new std::vector<std::vector<int>>;
  m_outP_isStable       = new std::vector<std::vector<uint8_t>>;
  m_outP_isInteracting  = new std::vector<std::vector<uint8_t>>;
  m_outP_isDark         = new std::vector<std::vector<uint8_t>>;

  // reco matching
  if ( m_infoSwitch.m_recoMatching ) {
    m_isReconstructible                = new std::vector<uint8_t>;
    
    m_descendant_n                     = new std::vector<int>;
    m_descendant_nReco                 = new std::vector<int>;
    m_descendant_nSelected             = new std::vector<int>;
    m_descendant_sumPt                 = new std::vector<float>;
    m_descendant_sumEta                = new std::vector<float>;
    m_descendant_sumPhi                = new std::vector<float>;
    m_descendant_sumE                  = new std::vector<float>;
    m_descendant_sumM                  = new std::vector<float>;
    m_descendant_recoSumPt             = new std::vector<float>;
    m_descendant_recoSumEta            = new std::vector<float>;
    m_descendant_recoSumPhi            = new std::vector<float>;
    m_descendant_recoSumE              = new std::vector<float>;
    m_descendant_recoSumM              = new std::vector<float>;
    m_descendant_truthPosID            = new std::vector<std::vector<int>>;
    m_descendant_ID                    = new std::vector<std::vector<int>>;
    m_descendant_index                 = new std::vector<std::vector<int>>;
    m_descendant_pt                    = new std::vector<std::vector<float>>;
    m_descendant_eta                   = new std::vector<std::vector<float>>;
    m_descendant_phi                   = new std::vector<std::vector<float>>;
    m_descendant_E                     = new std::vector<std::vector<float>>;
    m_descendant_M                     = new std::vector<std::vector<float>>;
    m_descendant_charge                = new std::vector<std::vector<float>>;
    m_descendant_pdgId                 = new std::vector<std::vector<int>>;
    m_descendant_barcode               = new std::vector<std::vector<int>>;
    m_descendant_isReco                = new std::vector<std::vector<uint8_t>>;
    m_descendant_isSelected            = new std::vector<std::vector<uint8_t>>;
    m_descendant_isAssociated          = new std::vector<std::vector<uint8_t>>;
    m_descendant_recoProb              = new std::vector<std::vector<float>>;
    m_descendant_recoID                = new std::vector<std::vector<int>>;
    m_descendant_recoIndex             = new std::vector<std::vector<int>>;
    m_descendant_recoD0                = new std::vector<std::vector<float>>;
    m_descendant_recoZ0                = new std::vector<std::vector<float>>;
    m_descendant_prod_x                = new std::vector<std::vector<float>>;
    m_descendant_prod_y                = new std::vector<std::vector<float>>;
    m_descendant_prod_z                = new std::vector<std::vector<float>>;
    m_descendant_prod_r                = new std::vector<std::vector<float>>;
    m_descendant_prod_phi              = new std::vector<std::vector<float>>;
    m_descendant_prod_barcode          = new std::vector<std::vector<int>>;
    m_descendant_decay_x               = new std::vector<std::vector<float>>;
    m_descendant_decay_y               = new std::vector<std::vector<float>>;
    m_descendant_decay_z               = new std::vector<std::vector<float>>;
    m_descendant_decay_r               = new std::vector<std::vector<float>>;
    m_descendant_decay_phi             = new std::vector<std::vector<float>>;
    m_descendant_decay_barcode         = new std::vector<std::vector<int>>;

    m_physPos_n                        = new std::vector<int>;
    m_physPos_maxSeparation            = new std::vector<float>;
    m_physPos_ID                       = new std::vector<std::vector<int>>;
    m_physPos_x                        = new std::vector<std::vector<float>>;
    m_physPos_y                        = new std::vector<std::vector<float>>;
    m_physPos_z                        = new std::vector<std::vector<float>>;
    m_physPos_r                        = new std::vector<std::vector<float>>;
    m_physPos_phi                      = new std::vector<std::vector<float>>;
    m_physPos_nDesc                    = new std::vector<std::vector<int>>;
    m_physPos_sumPt                    = new std::vector<std::vector<float>>;
    m_physPos_sumEta                   = new std::vector<std::vector<float>>;
    m_physPos_sumPhi                   = new std::vector<std::vector<float>>;
    m_physPos_sumE                     = new std::vector<std::vector<float>>;
    m_physPos_sumM                     = new std::vector<std::vector<float>>;

    m_closestRecoVtx_ID                = new std::vector<std::vector<int>>;
    m_closestRecoVtx_index             = new std::vector<std::vector<int>>;
    m_closestRecoVtx_x                 = new std::vector<std::vector<float>>;
    m_closestRecoVtx_y                 = new std::vector<std::vector<float>>;
    m_closestRecoVtx_z                 = new std::vector<std::vector<float>>;
    m_closestRecoVtx_r                 = new std::vector<std::vector<float>>;
    m_closestRecoVtx_phi               = new std::vector<std::vector<float>>;
    m_closestRecoVtx_distance          = new std::vector<std::vector<float>>;

    m_matchedRecoVtx_n                 = new std::vector<int>;
    m_matchedRecoVtx_ID                = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_index             = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_x                 = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_y                 = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_z                 = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_r                 = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_pt                = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_eta               = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_phi               = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_mass              = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_pt_clean          = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_eta_clean         = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_phi_clean         = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_mass_clean        = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_pt_bare           = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_eta_bare          = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_phi_bare          = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_mass_bare         = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_chi2              = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_ntrk              = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_ntrk_sel          = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_ntrk_assoc        = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_ntrk_clean        = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_ntrk_clean_sel    = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_ntrk_clean_assoc  = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_ntrk_filt         = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_ntrk_filt_sel     = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_ntrk_filt_assoc   = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_massFraction      = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_multFraction      = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_cleanMassFraction = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_cleanMultFraction = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_bareMassFraction  = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_bareMultFraction  = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_matchScore        = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_reprTruthPosID    = new std::vector<std::vector<int>>;
    m_matchedRecoVtx_reprTruthPosX     = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_reprTruthPosY     = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_reprTruthPosZ     = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_reprTruthPosR     = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_reprTruthPosPhi   = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_residual_x        = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_residual_y        = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_residual_z        = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_residual_r        = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_residual_phi      = new std::vector<std::vector<float>>;
    m_matchedRecoVtx_residual_distance = new std::vector<std::vector<float>>;
  }

  // matched to jets
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      m_truthJetMatch          = new std::vector<uint8_t>;
      m_truthJetMatch_ID       = new std::vector<int>;
      m_truthJetMatch_index    = new std::vector<int>;
      m_truthJetMatch_dR       = new std::vector<float>;
      m_darkJetMatch           = new std::vector<uint8_t>;
      m_darkJetMatch_ID        = new std::vector<int>;
      m_darkJetMatch_index     = new std::vector<int>;
      m_darkJetMatch_dR        = new std::vector<float>;
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	m_emtopoJetMatch       = new std::vector<uint8_t>;
	m_emtopoJetMatch_ID    = new std::vector<int>;
	m_emtopoJetMatch_index = new std::vector<int>;
	m_emtopoJetMatch_dR    = new std::vector<float>;
      }
      if ( m_doPFlow  ) {
	m_pflowJetMatch        = new std::vector<uint8_t>;
	m_pflowJetMatch_ID     = new std::vector<int>;
	m_pflowJetMatch_index  = new std::vector<int>;
	m_pflowJetMatch_dR     = new std::vector<float>;
      }
    }
  }
}


TruthVertexContainer :: ~TruthVertexContainer ()
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer()", "deleting" );

  delete m_passSel;
  delete m_llpDecay;
  delete m_ID;
  delete m_index;
  delete m_x;
  delete m_y;
  delete m_z;
  delete m_r;
  delete m_pt;
  delete m_eta;
  delete m_phi;
  delete m_mass;
  delete m_nOutP;
  delete m_barcode;
  delete m_childOpenAngle;
  delete m_parent_ID;
  delete m_parent_index;
  delete m_parent_pt;
  delete m_parent_eta;
  delete m_parent_phi;
  delete m_parent_E;
  delete m_parent_M;
  delete m_parent_charge;
  delete m_parent_pdgId;
  delete m_parent_status;
  delete m_parent_barcode;
  delete m_parent_prod_ID;
  delete m_parent_prod_index;
  delete m_parent_prod_x;
  delete m_parent_prod_y;
  delete m_parent_prod_z;
  delete m_parent_prod_r;
  delete m_parent_prod_pt;
  delete m_parent_prod_eta;
  delete m_parent_prod_phi;
  delete m_parent_prod_mass;
  delete m_parent_prod_nOutP;
  delete m_parent_prod_barcode;
  delete m_outP_ID;
  delete m_outP_index;
  delete m_outP_pt;
  delete m_outP_eta;
  delete m_outP_phi;
  delete m_outP_E;
  delete m_outP_M;
  delete m_outP_charge;
  delete m_outP_pdgId;
  delete m_outP_status;
  delete m_outP_barcode;
  delete m_outP_isReco;
  delete m_outP_isSelected;
  delete m_outP_isAssociated;
  delete m_outP_recoProb;
  delete m_outP_recoID;
  delete m_outP_recoIndex;
  delete m_outP_isStable;
  delete m_outP_isInteracting;
  delete m_outP_isDark;

  // reco vertex matching
  if ( m_infoSwitch.m_recoMatching ) {
    delete m_isReconstructible;
    
    delete m_descendant_n;
    delete m_descendant_nReco;
    delete m_descendant_nSelected;
    delete m_descendant_sumPt;
    delete m_descendant_sumEta;
    delete m_descendant_sumPhi;
    delete m_descendant_sumE;
    delete m_descendant_sumM;
    delete m_descendant_recoSumPt;
    delete m_descendant_recoSumEta;
    delete m_descendant_recoSumPhi;
    delete m_descendant_recoSumE;
    delete m_descendant_recoSumM;
    delete m_descendant_truthPosID;
    delete m_descendant_ID;
    delete m_descendant_index;
    delete m_descendant_pt;
    delete m_descendant_eta;
    delete m_descendant_phi;
    delete m_descendant_E;
    delete m_descendant_M;
    delete m_descendant_charge;
    delete m_descendant_pdgId;
    delete m_descendant_barcode;
    delete m_descendant_isReco;
    delete m_descendant_isSelected;
    delete m_descendant_isAssociated;
    delete m_descendant_recoProb;
    delete m_descendant_recoID;
    delete m_descendant_recoIndex;
    delete m_descendant_recoD0;
    delete m_descendant_recoZ0;
    delete m_descendant_prod_x;
    delete m_descendant_prod_y;
    delete m_descendant_prod_z;
    delete m_descendant_prod_r;
    delete m_descendant_prod_phi;
    delete m_descendant_prod_barcode;
    delete m_descendant_decay_x;
    delete m_descendant_decay_y;
    delete m_descendant_decay_z;
    delete m_descendant_decay_r;
    delete m_descendant_decay_phi;
    delete m_descendant_decay_barcode;

    delete m_physPos_n;
    delete m_physPos_maxSeparation;
    delete m_physPos_ID;
    delete m_physPos_x;
    delete m_physPos_y;
    delete m_physPos_z;
    delete m_physPos_r;
    delete m_physPos_phi;
    delete m_physPos_nDesc;
    delete m_physPos_sumPt;
    delete m_physPos_sumEta;
    delete m_physPos_sumPhi;
    delete m_physPos_sumE;
    delete m_physPos_sumM;

    delete m_closestRecoVtx_ID;
    delete m_closestRecoVtx_index;
    delete m_closestRecoVtx_x;
    delete m_closestRecoVtx_y;
    delete m_closestRecoVtx_z;
    delete m_closestRecoVtx_r;
    delete m_closestRecoVtx_phi;
    delete m_closestRecoVtx_distance;

    delete m_matchedRecoVtx_n;
    delete m_matchedRecoVtx_ID;
    delete m_matchedRecoVtx_index;
    delete m_matchedRecoVtx_x;
    delete m_matchedRecoVtx_y;
    delete m_matchedRecoVtx_z;
    delete m_matchedRecoVtx_r;
    delete m_matchedRecoVtx_pt;
    delete m_matchedRecoVtx_eta;
    delete m_matchedRecoVtx_phi;
    delete m_matchedRecoVtx_mass;
    delete m_matchedRecoVtx_pt_clean;
    delete m_matchedRecoVtx_eta_clean;
    delete m_matchedRecoVtx_phi_clean;
    delete m_matchedRecoVtx_mass_clean;
    delete m_matchedRecoVtx_pt_bare;
    delete m_matchedRecoVtx_eta_bare;
    delete m_matchedRecoVtx_phi_bare;
    delete m_matchedRecoVtx_mass_bare;
    delete m_matchedRecoVtx_chi2;
    delete m_matchedRecoVtx_ntrk;
    delete m_matchedRecoVtx_ntrk_sel;
    delete m_matchedRecoVtx_ntrk_assoc;
    delete m_matchedRecoVtx_ntrk_clean;
    delete m_matchedRecoVtx_ntrk_clean_sel;
    delete m_matchedRecoVtx_ntrk_clean_assoc;
    delete m_matchedRecoVtx_ntrk_filt;
    delete m_matchedRecoVtx_ntrk_filt_sel;
    delete m_matchedRecoVtx_ntrk_filt_assoc;
    delete m_matchedRecoVtx_massFraction;
    delete m_matchedRecoVtx_multFraction;
    delete m_matchedRecoVtx_cleanMassFraction;
    delete m_matchedRecoVtx_cleanMultFraction;
    delete m_matchedRecoVtx_bareMassFraction;
    delete m_matchedRecoVtx_bareMultFraction;
    delete m_matchedRecoVtx_matchScore;
    delete m_matchedRecoVtx_reprTruthPosID;
    delete m_matchedRecoVtx_reprTruthPosX;
    delete m_matchedRecoVtx_reprTruthPosY;
    delete m_matchedRecoVtx_reprTruthPosZ;
    delete m_matchedRecoVtx_reprTruthPosR;
    delete m_matchedRecoVtx_reprTruthPosPhi;
    delete m_matchedRecoVtx_residual_x;
    delete m_matchedRecoVtx_residual_y;
    delete m_matchedRecoVtx_residual_z;
    delete m_matchedRecoVtx_residual_r;
    delete m_matchedRecoVtx_residual_phi;
    delete m_matchedRecoVtx_residual_distance;
  }

  // matched to jets
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      delete m_truthJetMatch;
      delete m_truthJetMatch_ID;
      delete m_truthJetMatch_index;
      delete m_truthJetMatch_dR;
      delete m_darkJetMatch;
      delete m_darkJetMatch_ID;
      delete m_darkJetMatch_index;
      delete m_darkJetMatch_dR;
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	delete m_emtopoJetMatch;
	delete m_emtopoJetMatch_ID;
	delete m_emtopoJetMatch_index;
	delete m_emtopoJetMatch_dR;
      }
      if ( m_doPFlow  ) {
	delete m_pflowJetMatch;
	delete m_pflowJetMatch_ID;
	delete m_pflowJetMatch_index;
	delete m_pflowJetMatch_dR;
      }
    }
  }
}


void TruthVertexContainer :: setTree ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::setTree()", "setting tree" );

  VertexContainer::setTree ( tree );

  connectBranch<uint8_t>              ( tree, "passSel",             &m_passSel             );
  connectBranch<std::string>          ( tree, "llpDecay",            &m_llpDecay            );
  connectBranch<int>                  ( tree, "ID",                  &m_ID                  );
  connectBranch<int>                  ( tree, "index",               &m_index               );
  connectBranch<float>                ( tree, "x",                   &m_x                   );
  connectBranch<float>                ( tree, "y",                   &m_y                   );
  connectBranch<float>                ( tree, "z",                   &m_z                   );
  connectBranch<float>                ( tree, "r",                   &m_r                   );
  connectBranch<float>                ( tree, "pt",                  &m_pt                  );
  connectBranch<float>                ( tree, "eta",                 &m_eta                 );
  connectBranch<float>                ( tree, "phi",                 &m_phi                 );
  connectBranch<float>                ( tree, "mass",                &m_mass                );
  connectBranch<int>                  ( tree, "nOutP",               &m_nOutP               );
  connectBranch<int>                  ( tree, "barcode",             &m_barcode             );
  connectBranch<float>                ( tree, "childOpenAngle",      &m_childOpenAngle      );
  connectBranch<int>                  ( tree, "parent_ID",           &m_parent_ID           );
  connectBranch<int>                  ( tree, "parent_index",        &m_parent_index        );
  connectBranch<float>                ( tree, "parent_pt",           &m_parent_pt           );
  connectBranch<float>                ( tree, "parent_eta",          &m_parent_eta          );
  connectBranch<float>                ( tree, "parent_phi",          &m_parent_phi          );
  connectBranch<float>                ( tree, "parent_E",            &m_parent_E            );
  connectBranch<float>                ( tree, "parent_M",            &m_parent_M            );
  connectBranch<float>                ( tree, "parent_charge",       &m_parent_charge       );
  connectBranch<int>                  ( tree, "parent_pdgId",        &m_parent_pdgId        );
  connectBranch<int>                  ( tree, "parent_status",       &m_parent_status       );
  connectBranch<int>                  ( tree, "parent_barcode",      &m_parent_barcode      );
  connectBranch<int>                  ( tree, "parent_prod_ID",      &m_parent_prod_ID      );
  connectBranch<int>                  ( tree, "parent_prod_index",   &m_parent_prod_index   );
  connectBranch<float>                ( tree, "parent_prod_x",       &m_parent_prod_x       );
  connectBranch<float>                ( tree, "parent_prod_y",       &m_parent_prod_y       );
  connectBranch<float>                ( tree, "parent_prod_z",       &m_parent_prod_z       );
  connectBranch<float>                ( tree, "parent_prod_r",       &m_parent_prod_r       );
  connectBranch<float>                ( tree, "parent_prod_pt",      &m_parent_prod_pt      );
  connectBranch<float>                ( tree, "parent_prod_eta",     &m_parent_prod_eta     );
  connectBranch<float>                ( tree, "parent_prod_phi",     &m_parent_prod_phi     );
  connectBranch<float>                ( tree, "parent_prod_mass",    &m_parent_prod_mass    );
  connectBranch<int>                  ( tree, "parent_prod_nOutP",   &m_parent_prod_nOutP   );
  connectBranch<int>                  ( tree, "parent_prod_barcode", &m_parent_prod_barcode );
  connectBranch<std::vector<int>>     ( tree, "outP_ID",             &m_outP_ID             );
  connectBranch<std::vector<int>>     ( tree, "outP_index",          &m_outP_index          );
  connectBranch<std::vector<float>>   ( tree, "outP_pt",             &m_outP_pt             );
  connectBranch<std::vector<float>>   ( tree, "outP_eta",            &m_outP_eta            );
  connectBranch<std::vector<float>>   ( tree, "outP_phi",            &m_outP_phi            );
  connectBranch<std::vector<float>>   ( tree, "outP_E",              &m_outP_E              );
  connectBranch<std::vector<float>>   ( tree, "outP_M",              &m_outP_M              );
  connectBranch<std::vector<float>>   ( tree, "outP_charge",         &m_outP_charge         );
  connectBranch<std::vector<int>>     ( tree, "outP_pdgId",          &m_outP_pdgId          );
  connectBranch<std::vector<int>>     ( tree, "outP_status",         &m_outP_status         );
  connectBranch<std::vector<int>>     ( tree, "outP_barcode",        &m_outP_barcode        );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isReco",         &m_outP_isReco         );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isSelected",     &m_outP_isSelected     );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isAssociated",   &m_outP_isAssociated   );
  connectBranch<std::vector<float>>   ( tree, "outP_recoProb",       &m_outP_recoProb       );
  connectBranch<std::vector<int>>     ( tree, "outP_recoID",         &m_outP_recoID         );
  connectBranch<std::vector<int>>     ( tree, "outP_recoIndex",      &m_outP_recoIndex      );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isStable",       &m_outP_isStable       );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isInteracting",  &m_outP_isInteracting  );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isDark",         &m_outP_isDark         );

  // reco vertex matching
  if ( m_infoSwitch.m_recoMatching ) {
    connectBranch<uint8_t>              ( tree, "isReconstructible",                &m_isReconstructible                );
    
    connectBranch<int>                  ( tree, "descendant_n",                     &m_descendant_n                     );
    connectBranch<int>                  ( tree, "descendant_nReco",                 &m_descendant_nReco                 );
    connectBranch<int>                  ( tree, "descendant_nSelected",             &m_descendant_nSelected             );
    connectBranch<float>                ( tree, "descendant_sumPt",                 &m_descendant_sumPt                 );
    connectBranch<float>                ( tree, "descendant_sumEta",                &m_descendant_sumEta                );
    connectBranch<float>                ( tree, "descendant_sumPhi",                &m_descendant_sumPhi                );
    connectBranch<float>                ( tree, "descendant_sumE",                  &m_descendant_sumE                  );
    connectBranch<float>                ( tree, "descendant_sumM",                  &m_descendant_sumM                  );
    connectBranch<float>                ( tree, "descendant_recoSumPt",             &m_descendant_recoSumPt             );
    connectBranch<float>                ( tree, "descendant_recoSumEta",            &m_descendant_recoSumEta            );
    connectBranch<float>                ( tree, "descendant_recoSumPhi",            &m_descendant_recoSumPhi            );
    connectBranch<float>                ( tree, "descendant_recoSumE",              &m_descendant_recoSumE              );
    connectBranch<float>                ( tree, "descendant_recoSumM",              &m_descendant_recoSumM              );
    connectBranch<std::vector<int>>     ( tree, "descendant_truthPosID",            &m_descendant_truthPosID            );
    connectBranch<std::vector<int>>     ( tree, "descendant_ID",                    &m_descendant_ID                    );
    connectBranch<std::vector<int>>     ( tree, "descendant_index",                 &m_descendant_index                 );
    connectBranch<std::vector<float>>   ( tree, "descendant_pt",                    &m_descendant_pt                    );
    connectBranch<std::vector<float>>   ( tree, "descendant_eta",                   &m_descendant_eta                   );
    connectBranch<std::vector<float>>   ( tree, "descendant_phi",                   &m_descendant_phi                   );
    connectBranch<std::vector<float>>   ( tree, "descendant_E",                     &m_descendant_E                     );
    connectBranch<std::vector<float>>   ( tree, "descendant_M",                     &m_descendant_M                     );
    connectBranch<std::vector<float>>   ( tree, "descendant_charge",                &m_descendant_charge                );
    connectBranch<std::vector<int>>     ( tree, "descendant_pdgId",                 &m_descendant_pdgId                 );
    connectBranch<std::vector<int>>     ( tree, "descendant_barcode",               &m_descendant_barcode               );
    connectBranch<std::vector<uint8_t>> ( tree, "descendant_isReco",                &m_descendant_isReco                );
    connectBranch<std::vector<uint8_t>> ( tree, "descendant_isSelected",            &m_descendant_isSelected            );
    connectBranch<std::vector<uint8_t>> ( tree, "descendant_isAssociated",          &m_descendant_isAssociated          );
    connectBranch<std::vector<float>>   ( tree, "descendant_recoProb",              &m_descendant_recoProb              );
    connectBranch<std::vector<int>>     ( tree, "descendant_recoID",                &m_descendant_recoID                );
    connectBranch<std::vector<int>>     ( tree, "descendant_recoIndex",             &m_descendant_recoIndex             );
    connectBranch<std::vector<float>>   ( tree, "descendant_recoD0",                &m_descendant_recoD0                );
    connectBranch<std::vector<float>>   ( tree, "descendant_recoZ0",                &m_descendant_recoZ0                );
    connectBranch<std::vector<float>>   ( tree, "descendant_prod_x",                &m_descendant_prod_x                );
    connectBranch<std::vector<float>>   ( tree, "descendant_prod_y",                &m_descendant_prod_y                );
    connectBranch<std::vector<float>>   ( tree, "descendant_prod_z",                &m_descendant_prod_z                );
    connectBranch<std::vector<float>>   ( tree, "descendant_prod_r",                &m_descendant_prod_r                );
    connectBranch<std::vector<float>>   ( tree, "descendant_prod_phi",              &m_descendant_prod_phi              );
    connectBranch<std::vector<int>>     ( tree, "descendant_prod_barcode",          &m_descendant_prod_barcode          );
    connectBranch<std::vector<float>>   ( tree, "descendant_decay_x",               &m_descendant_decay_x               );
    connectBranch<std::vector<float>>   ( tree, "descendant_decay_y",               &m_descendant_decay_y               );
    connectBranch<std::vector<float>>   ( tree, "descendant_decay_z",               &m_descendant_decay_z               );
    connectBranch<std::vector<float>>   ( tree, "descendant_decay_r",               &m_descendant_decay_r               );
    connectBranch<std::vector<float>>   ( tree, "descendant_decay_phi",             &m_descendant_decay_phi             );
    connectBranch<std::vector<int>>     ( tree, "descendant_decay_barcode",         &m_descendant_decay_barcode         );

    connectBranch<int>                  ( tree, "physPos_n",                        &m_physPos_n                        );
    connectBranch<float>                ( tree, "physPos_maxSeparation",            &m_physPos_maxSeparation            );
    connectBranch<std::vector<int>>     ( tree, "physPos_ID",                       &m_physPos_ID                       );
    connectBranch<std::vector<float>>   ( tree, "physPos_x",                        &m_physPos_x                        );
    connectBranch<std::vector<float>>   ( tree, "physPos_y",                        &m_physPos_y                        );
    connectBranch<std::vector<float>>   ( tree, "physPos_z",                        &m_physPos_z                        );
    connectBranch<std::vector<float>>   ( tree, "physPos_r",                        &m_physPos_r                        );
    connectBranch<std::vector<float>>   ( tree, "physPos_phi",                      &m_physPos_phi                      );
    connectBranch<std::vector<int>>     ( tree, "physPos_nDesc",                    &m_physPos_nDesc                    );
    connectBranch<std::vector<float>>   ( tree, "physPos_sumPt",                    &m_physPos_sumPt                    );
    connectBranch<std::vector<float>>   ( tree, "physPos_sumEta",                   &m_physPos_sumEta                   );
    connectBranch<std::vector<float>>   ( tree, "physPos_sumPhi",                   &m_physPos_sumPhi                   );
    connectBranch<std::vector<float>>   ( tree, "physPos_sumE",                     &m_physPos_sumE                     );
    connectBranch<std::vector<float>>   ( tree, "physPos_sumM",                     &m_physPos_sumM                     );

    connectBranch<std::vector<int>>     ( tree, "closestRecoVtx_ID",                &m_closestRecoVtx_ID                );
    connectBranch<std::vector<int>>     ( tree, "closestRecoVtx_index",             &m_closestRecoVtx_index             );
    connectBranch<std::vector<float>>   ( tree, "closestRecoVtx_x",                 &m_closestRecoVtx_x                 );
    connectBranch<std::vector<float>>   ( tree, "closestRecoVtx_y",                 &m_closestRecoVtx_y                 );
    connectBranch<std::vector<float>>   ( tree, "closestRecoVtx_z",                 &m_closestRecoVtx_z                 );
    connectBranch<std::vector<float>>   ( tree, "closestRecoVtx_r",                 &m_closestRecoVtx_r                 );
    connectBranch<std::vector<float>>   ( tree, "closestRecoVtx_phi",               &m_closestRecoVtx_phi               );
    connectBranch<std::vector<float>>   ( tree, "closestRecoVtx_distance",          &m_closestRecoVtx_distance          );

    connectBranch<int>                  ( tree, "matchedRecoVtx_n",                 &m_matchedRecoVtx_n                 );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ID",                &m_matchedRecoVtx_ID                );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_index",             &m_matchedRecoVtx_index             );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_x",                 &m_matchedRecoVtx_x                 );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_y",                 &m_matchedRecoVtx_y                 );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_z",                 &m_matchedRecoVtx_z                 );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_r",                 &m_matchedRecoVtx_r                 );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_pt",                &m_matchedRecoVtx_pt                );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_eta",               &m_matchedRecoVtx_eta               );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_phi",               &m_matchedRecoVtx_phi               );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_mass",              &m_matchedRecoVtx_mass              );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_pt_clean",          &m_matchedRecoVtx_pt_clean          );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_eta_clean",         &m_matchedRecoVtx_eta_clean         );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_phi_clean",         &m_matchedRecoVtx_phi_clean         );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_mass_clean",        &m_matchedRecoVtx_mass_clean        );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_pt_bare",           &m_matchedRecoVtx_pt_bare           );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_eta_bare",          &m_matchedRecoVtx_eta_bare          );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_phi_bare",          &m_matchedRecoVtx_phi_bare          );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_mass_bare",         &m_matchedRecoVtx_mass_bare         );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_chi2",              &m_matchedRecoVtx_chi2              );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk",              &m_matchedRecoVtx_ntrk              );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_sel",          &m_matchedRecoVtx_ntrk_sel          );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_assoc",        &m_matchedRecoVtx_ntrk_assoc        );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_clean",        &m_matchedRecoVtx_ntrk_clean        );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_clean_sel",    &m_matchedRecoVtx_ntrk_clean_sel    );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_clean_assoc",  &m_matchedRecoVtx_ntrk_clean_assoc  );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_filt",         &m_matchedRecoVtx_ntrk_filt         );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_filt_sel",     &m_matchedRecoVtx_ntrk_filt_sel     );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_filt_assoc",   &m_matchedRecoVtx_ntrk_filt_assoc   );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_massFraction",      &m_matchedRecoVtx_massFraction      );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_multFraction",      &m_matchedRecoVtx_multFraction      );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_cleanMassFraction", &m_matchedRecoVtx_cleanMassFraction );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_cleanMultFraction", &m_matchedRecoVtx_cleanMultFraction );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_bareMassFraction",  &m_matchedRecoVtx_bareMassFraction  );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_bareMultFraction",  &m_matchedRecoVtx_bareMultFraction  );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_matchScore",        &m_matchedRecoVtx_matchScore        );
    connectBranch<std::vector<int>>     ( tree, "matchedRecoVtx_reprTruthPosID",    &m_matchedRecoVtx_reprTruthPosID    );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_reprTruthPosX",     &m_matchedRecoVtx_reprTruthPosX     );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_reprTruthPosY",     &m_matchedRecoVtx_reprTruthPosY     );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_reprTruthPosZ",     &m_matchedRecoVtx_reprTruthPosZ     );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_reprTruthPosR",     &m_matchedRecoVtx_reprTruthPosR     );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_reprTruthPosPhi",   &m_matchedRecoVtx_reprTruthPosPhi   );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_x",        &m_matchedRecoVtx_residual_x        );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_y",        &m_matchedRecoVtx_residual_y        );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_z",        &m_matchedRecoVtx_residual_z        );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_r",        &m_matchedRecoVtx_residual_r        );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_phi",      &m_matchedRecoVtx_residual_phi      );
    connectBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_distance", &m_matchedRecoVtx_residual_distance );
  }
  
  // matched to jets
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      connectBranch<uint8_t>   ( tree, "isTruthJetMatched",    &m_truthJetMatch       );
      connectBranch<int>       ( tree, "truthJetMatch_ID",     &m_truthJetMatch_ID    );
      connectBranch<int>       ( tree, "truthJetMatch_index",  &m_truthJetMatch_index );
      connectBranch<float>     ( tree, "truthJetMatch_dR",     &m_truthJetMatch_dR    );
      connectBranch<uint8_t>   ( tree, "isDarkJetMatched",     &m_darkJetMatch        );
      connectBranch<int>       ( tree, "darkJetMatch_ID",      &m_darkJetMatch_ID     );
      connectBranch<int>       ( tree, "darkJetMatch_index",   &m_darkJetMatch_index  );
      connectBranch<float>     ( tree, "darkJetMatch_dR",      &m_darkJetMatch_dR     );
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	connectBranch<uint8_t> ( tree, "isEMTopoJetMatched",   &m_emtopoJetMatch       );
	connectBranch<int>     ( tree, "EMTopoJetMatch_ID",    &m_emtopoJetMatch_ID    );
	connectBranch<int>     ( tree, "EMTopoJetMatch_index", &m_emtopoJetMatch_index );
	connectBranch<float>   ( tree, "EMTopoJetMatch_dR",    &m_emtopoJetMatch_dR    );
      }
      if ( m_doPFlow  ) {
	connectBranch<uint8_t> ( tree, "isPFlowJetMatched",    &m_pflowJetMatch        );
	connectBranch<int>     ( tree, "PFlowJetMatch_ID",     &m_pflowJetMatch_ID     );
	connectBranch<int>     ( tree, "PFlowJetMatch_index",  &m_pflowJetMatch_index  );
	connectBranch<float>   ( tree, "PFlowJetMatch_dR",     &m_pflowJetMatch_dR     );
      }
    }
  }
}


void TruthVertexContainer :: setBranches ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::setBranches()", "setting branches" );

  VertexContainer::setBranches ( tree );

  setBranch<uint8_t>              ( tree, "passSel",             m_passSel             );
  setBranch<std::string>          ( tree, "llpDecay",            m_llpDecay            );
  setBranch<int>                  ( tree, "ID",                  m_ID                  );
  setBranch<int>                  ( tree, "index",               m_index               );
  setBranch<float>                ( tree, "x",                   m_x                   );
  setBranch<float>                ( tree, "y",                   m_y                   );
  setBranch<float>                ( tree, "z",                   m_z                   );
  setBranch<float>                ( tree, "r",                   m_r                   );
  setBranch<float>                ( tree, "pt",                  m_pt                  );
  setBranch<float>                ( tree, "eta",                 m_eta                 );
  setBranch<float>                ( tree, "phi",                 m_phi                 );
  setBranch<float>                ( tree, "mass",                m_mass                );
  setBranch<int>                  ( tree, "nOutP",               m_nOutP               );
  setBranch<int>                  ( tree, "barcode",             m_barcode             );
  setBranch<float>                ( tree, "childOpenAngle",      m_childOpenAngle      );
  setBranch<int>                  ( tree, "parent_ID",           m_parent_ID           );
  setBranch<int>                  ( tree, "parent_index",        m_parent_index        );
  setBranch<float>                ( tree, "parent_pt",           m_parent_pt           );
  setBranch<float>                ( tree, "parent_eta",          m_parent_eta          );
  setBranch<float>                ( tree, "parent_phi",          m_parent_phi          );
  setBranch<float>                ( tree, "parent_E",            m_parent_E            );
  setBranch<float>                ( tree, "parent_M",            m_parent_M            );
  setBranch<float>                ( tree, "parent_charge",       m_parent_charge       );
  setBranch<int>                  ( tree, "parent_pdgId",        m_parent_pdgId        );
  setBranch<int>                  ( tree, "parent_status",       m_parent_status       );
  setBranch<int>                  ( tree, "parent_barcode",      m_parent_barcode      );
  setBranch<int>                  ( tree, "parent_prod_ID",      m_parent_prod_ID      );
  setBranch<int>                  ( tree, "parent_prod_index",   m_parent_prod_index   );
  setBranch<float>                ( tree, "parent_prod_x",       m_parent_prod_x       );
  setBranch<float>                ( tree, "parent_prod_y",       m_parent_prod_y       );
  setBranch<float>                ( tree, "parent_prod_z",       m_parent_prod_z       );
  setBranch<float>                ( tree, "parent_prod_r",       m_parent_prod_r       );
  setBranch<float>                ( tree, "parent_prod_pt",      m_parent_prod_pt      );
  setBranch<float>                ( tree, "parent_prod_eta",     m_parent_prod_eta     );
  setBranch<float>                ( tree, "parent_prod_phi",     m_parent_prod_phi     );
  setBranch<float>                ( tree, "parent_prod_mass",    m_parent_prod_mass    );
  setBranch<int>                  ( tree, "parent_prod_nOutP",   m_parent_prod_nOutP   );
  setBranch<int>                  ( tree, "parent_prod_barcode", m_parent_prod_barcode );
  setBranch<std::vector<int>>     ( tree, "outP_ID",             m_outP_ID             );
  setBranch<std::vector<int>>     ( tree, "outP_index",          m_outP_index          );
  setBranch<std::vector<float>>   ( tree, "outP_pt",             m_outP_pt             );
  setBranch<std::vector<float>>   ( tree, "outP_eta",            m_outP_eta            );
  setBranch<std::vector<float>>   ( tree, "outP_phi",            m_outP_phi            );
  setBranch<std::vector<float>>   ( tree, "outP_E",              m_outP_E              );
  setBranch<std::vector<float>>   ( tree, "outP_M",              m_outP_M              );
  setBranch<std::vector<float>>   ( tree, "outP_charge",         m_outP_charge         );
  setBranch<std::vector<int>>     ( tree, "outP_pdgId",          m_outP_pdgId          );
  setBranch<std::vector<int>>     ( tree, "outP_status",         m_outP_status         );
  setBranch<std::vector<int>>     ( tree, "outP_barcode",        m_outP_barcode        );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isReco",         m_outP_isReco         );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isSelected",     m_outP_isSelected     );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isAssociated",   m_outP_isAssociated   );
  setBranch<std::vector<float>>   ( tree, "outP_recoProb",       m_outP_recoProb       );
  setBranch<std::vector<int>>     ( tree, "outP_recoID",         m_outP_recoID         );
  setBranch<std::vector<int>>     ( tree, "outP_recoIndex",      m_outP_recoIndex      );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isStable",       m_outP_isStable       );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isInteracting",  m_outP_isInteracting  );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isDark",         m_outP_isDark         );

  // reco vertex matching
  if ( m_infoSwitch.m_recoMatching ) {
    setBranch<uint8_t>              ( tree, "isReconstructible",                m_isReconstructible                );
    
    setBranch<int>                  ( tree, "descendant_n",                     m_descendant_n                     );
    setBranch<int>                  ( tree, "descendant_nReco",                 m_descendant_nReco                 );
    setBranch<int>                  ( tree, "descendant_nSelected",             m_descendant_nSelected             );
    setBranch<float>                ( tree, "descendant_sumPt",                 m_descendant_sumPt                 );
    setBranch<float>                ( tree, "descendant_sumEta",                m_descendant_sumEta                );
    setBranch<float>                ( tree, "descendant_sumPhi",                m_descendant_sumPhi                );
    setBranch<float>                ( tree, "descendant_sumE",                  m_descendant_sumE                  );
    setBranch<float>                ( tree, "descendant_sumM",                  m_descendant_sumM                  );
    setBranch<float>                ( tree, "descendant_recoSumPt",             m_descendant_recoSumPt             );
    setBranch<float>                ( tree, "descendant_recoSumEta",            m_descendant_recoSumEta            );
    setBranch<float>                ( tree, "descendant_recoSumPhi",            m_descendant_recoSumPhi            );
    setBranch<float>                ( tree, "descendant_recoSumE",              m_descendant_recoSumE              );
    setBranch<float>                ( tree, "descendant_recoSumM",              m_descendant_recoSumM              );
    setBranch<std::vector<int>>     ( tree, "descendant_truthPosID",            m_descendant_truthPosID            );
    setBranch<std::vector<int>>     ( tree, "descendant_ID",                    m_descendant_ID                    );
    setBranch<std::vector<int>>     ( tree, "descendant_index",                 m_descendant_index                 );
    setBranch<std::vector<float>>   ( tree, "descendant_pt",                    m_descendant_pt                    );
    setBranch<std::vector<float>>   ( tree, "descendant_eta",                   m_descendant_eta                   );
    setBranch<std::vector<float>>   ( tree, "descendant_phi",                   m_descendant_phi                   );
    setBranch<std::vector<float>>   ( tree, "descendant_E",                     m_descendant_E                     );
    setBranch<std::vector<float>>   ( tree, "descendant_M",                     m_descendant_M                     );
    setBranch<std::vector<float>>   ( tree, "descendant_charge",                m_descendant_charge                );
    setBranch<std::vector<int>>     ( tree, "descendant_pdgId",                 m_descendant_pdgId                 );
    setBranch<std::vector<int>>     ( tree, "descendant_barcode",               m_descendant_barcode               );
    setBranch<std::vector<uint8_t>> ( tree, "descendant_isReco",                m_descendant_isReco                );
    setBranch<std::vector<uint8_t>> ( tree, "descendant_isSelected",            m_descendant_isSelected            );
    setBranch<std::vector<uint8_t>> ( tree, "descendant_isAssociated",          m_descendant_isAssociated          );
    setBranch<std::vector<float>>   ( tree, "descendant_recoProb",              m_descendant_recoProb              );
    setBranch<std::vector<int>>     ( tree, "descendant_recoID",                m_descendant_recoID                );
    setBranch<std::vector<int>>     ( tree, "descendant_recoIndex",             m_descendant_recoIndex             );
    setBranch<std::vector<float>>   ( tree, "descendant_recoD0",                m_descendant_recoD0                );
    setBranch<std::vector<float>>   ( tree, "descendant_recoZ0",                m_descendant_recoZ0                );
    setBranch<std::vector<float>>   ( tree, "descendant_prod_x",                m_descendant_prod_x                );
    setBranch<std::vector<float>>   ( tree, "descendant_prod_y",                m_descendant_prod_y                );
    setBranch<std::vector<float>>   ( tree, "descendant_prod_z",                m_descendant_prod_z                );
    setBranch<std::vector<float>>   ( tree, "descendant_prod_r",                m_descendant_prod_r                );
    setBranch<std::vector<float>>   ( tree, "descendant_prod_phi",              m_descendant_prod_phi              );
    setBranch<std::vector<int>>     ( tree, "descendant_prod_barcode",          m_descendant_prod_barcode          );
    setBranch<std::vector<float>>   ( tree, "descendant_decay_x",               m_descendant_decay_x               );
    setBranch<std::vector<float>>   ( tree, "descendant_decay_y",               m_descendant_decay_y               );
    setBranch<std::vector<float>>   ( tree, "descendant_decay_z",               m_descendant_decay_z               );
    setBranch<std::vector<float>>   ( tree, "descendant_decay_r",               m_descendant_decay_r               );
    setBranch<std::vector<float>>   ( tree, "descendant_decay_phi",             m_descendant_decay_phi             );
    setBranch<std::vector<int>>     ( tree, "descendant_decay_barcode",         m_descendant_decay_barcode         );

    setBranch<int>                  ( tree, "physPos_n",                        m_physPos_n                        );
    setBranch<float>                ( tree, "physPos_maxSeparation",            m_physPos_maxSeparation            );
    setBranch<std::vector<int>>     ( tree, "physPos_ID",                       m_physPos_ID                       );
    setBranch<std::vector<float>>   ( tree, "physPos_x",                        m_physPos_x                        );
    setBranch<std::vector<float>>   ( tree, "physPos_y",                        m_physPos_y                        );
    setBranch<std::vector<float>>   ( tree, "physPos_z",                        m_physPos_z                        );
    setBranch<std::vector<float>>   ( tree, "physPos_r",                        m_physPos_r                        );
    setBranch<std::vector<float>>   ( tree, "physPos_phi",                      m_physPos_phi                      );
    setBranch<std::vector<int>>     ( tree, "physPos_nDesc",                    m_physPos_nDesc                    );
    setBranch<std::vector<float>>   ( tree, "physPos_sumPt",                    m_physPos_sumPt                    );
    setBranch<std::vector<float>>   ( tree, "physPos_sumEta",                   m_physPos_sumEta                   );
    setBranch<std::vector<float>>   ( tree, "physPos_sumPhi",                   m_physPos_sumPhi                   );
    setBranch<std::vector<float>>   ( tree, "physPos_sumE",                     m_physPos_sumE                     );
    setBranch<std::vector<float>>   ( tree, "physPos_sumM",                     m_physPos_sumM                     );

    setBranch<std::vector<int>>     ( tree, "closestRecoVtx_ID",                m_closestRecoVtx_ID                );
    setBranch<std::vector<int>>     ( tree, "closestRecoVtx_index",             m_closestRecoVtx_index             );
    setBranch<std::vector<float>>   ( tree, "closestRecoVtx_x",                 m_closestRecoVtx_x                 );
    setBranch<std::vector<float>>   ( tree, "closestRecoVtx_y",                 m_closestRecoVtx_y                 );
    setBranch<std::vector<float>>   ( tree, "closestRecoVtx_z",                 m_closestRecoVtx_z                 );
    setBranch<std::vector<float>>   ( tree, "closestRecoVtx_r",                 m_closestRecoVtx_r                 );
    setBranch<std::vector<float>>   ( tree, "closestRecoVtx_phi",               m_closestRecoVtx_phi               );
    setBranch<std::vector<float>>   ( tree, "closestRecoVtx_distance",          m_closestRecoVtx_distance          );

    setBranch<int>                  ( tree, "matchedRecoVtx_n",                 m_matchedRecoVtx_n                 );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ID",                m_matchedRecoVtx_ID                );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_index",             m_matchedRecoVtx_index             );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_x",                 m_matchedRecoVtx_x                 );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_y",                 m_matchedRecoVtx_y                 );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_z",                 m_matchedRecoVtx_z                 );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_r",                 m_matchedRecoVtx_r                 );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_pt",                m_matchedRecoVtx_pt                );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_eta",               m_matchedRecoVtx_eta               );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_phi",               m_matchedRecoVtx_phi               );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_mass",              m_matchedRecoVtx_mass              );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_pt_clean",          m_matchedRecoVtx_pt_clean          );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_eta_clean",         m_matchedRecoVtx_eta_clean         );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_phi_clean",         m_matchedRecoVtx_phi_clean         );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_mass_clean",        m_matchedRecoVtx_mass_clean        );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_pt_bare",           m_matchedRecoVtx_pt_bare           );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_eta_bare",          m_matchedRecoVtx_eta_bare          );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_phi_bare",          m_matchedRecoVtx_phi_bare          );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_mass_bare",         m_matchedRecoVtx_mass_bare         );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_chi2",              m_matchedRecoVtx_chi2              );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk",              m_matchedRecoVtx_ntrk              );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_sel",          m_matchedRecoVtx_ntrk_sel          );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_assoc",        m_matchedRecoVtx_ntrk_assoc        );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_clean",        m_matchedRecoVtx_ntrk_clean        );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_clean_sel",    m_matchedRecoVtx_ntrk_clean_sel    );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_clean_assoc",  m_matchedRecoVtx_ntrk_clean_assoc  );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_filt",         m_matchedRecoVtx_ntrk_filt         );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_filt_sel",     m_matchedRecoVtx_ntrk_filt_sel     );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_ntrk_filt_assoc",   m_matchedRecoVtx_ntrk_filt_assoc   );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_massFraction",      m_matchedRecoVtx_massFraction      );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_multFraction",      m_matchedRecoVtx_multFraction      );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_cleanMassFraction", m_matchedRecoVtx_cleanMassFraction );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_cleanMultFraction", m_matchedRecoVtx_cleanMultFraction );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_bareMassFraction",  m_matchedRecoVtx_bareMassFraction  );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_bareMultFraction",  m_matchedRecoVtx_bareMultFraction  );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_matchScore",        m_matchedRecoVtx_matchScore        );
    setBranch<std::vector<int>>     ( tree, "matchedRecoVtx_reprTruthPosID",    m_matchedRecoVtx_reprTruthPosID    );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_reprTruthPosX",     m_matchedRecoVtx_reprTruthPosX     );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_reprTruthPosY",     m_matchedRecoVtx_reprTruthPosY     );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_reprTruthPosZ",     m_matchedRecoVtx_reprTruthPosZ     );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_reprTruthPosR",     m_matchedRecoVtx_reprTruthPosR     );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_reprTruthPosPhi",   m_matchedRecoVtx_reprTruthPosPhi   );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_x",        m_matchedRecoVtx_residual_x        );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_y",        m_matchedRecoVtx_residual_y        );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_z",        m_matchedRecoVtx_residual_z        );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_r",        m_matchedRecoVtx_residual_r        );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_phi",      m_matchedRecoVtx_residual_phi      );
    setBranch<std::vector<float>>   ( tree, "matchedRecoVtx_residual_distance", m_matchedRecoVtx_residual_distance );
  }
  
  // matched to jets
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      setBranch<uint8_t>   ( tree, "isTruthJetMatched",    m_truthJetMatch       );
      setBranch<int>       ( tree, "truthJetMatch_ID",     m_truthJetMatch_ID    );
      setBranch<int>       ( tree, "truthJetMatch_index",  m_truthJetMatch_index );
      setBranch<float>     ( tree, "truthJetMatch_dR",     m_truthJetMatch_dR    );
      setBranch<uint8_t>   ( tree, "isDarkJetMatched",     m_darkJetMatch        );
      setBranch<int>       ( tree, "darkJetMatch_ID",      m_darkJetMatch_ID     );
      setBranch<int>       ( tree, "darkJetMatch_index",   m_darkJetMatch_index  );
      setBranch<float>     ( tree, "darkJetMatch_dR",      m_darkJetMatch_dR     );
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	setBranch<uint8_t> ( tree, "isEMTopoJetMatched",   m_emtopoJetMatch       );
	setBranch<int>     ( tree, "EMTopoJetMatch_ID",    m_emtopoJetMatch_ID    );
	setBranch<int>     ( tree, "EMTopoJetMatch_index", m_emtopoJetMatch_index );
	setBranch<float>   ( tree, "EMTopoJetMatch_dR",    m_emtopoJetMatch_dR    );
      }
      if ( m_doPFlow  ) {
	setBranch<uint8_t> ( tree, "isPFlowJetMatched",    m_pflowJetMatch        );
	setBranch<int>     ( tree, "PFlowJetMatch_ID",     m_pflowJetMatch_ID     );
	setBranch<int>     ( tree, "PFlowJetMatch_index",  m_pflowJetMatch_index  );
	setBranch<float>   ( tree, "PFlowJetMatch_dR",     m_pflowJetMatch_dR     );
      }
    }
  }
}


void TruthVertexContainer :: clear ()
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::clear()", "clearing branches" );

  VertexContainer::clear ();

  m_passSel             ->clear();
  m_llpDecay            ->clear();
  m_ID                  ->clear();
  m_index               ->clear();
  m_x                   ->clear();
  m_y                   ->clear();
  m_z                   ->clear();
  m_r                   ->clear();
  m_pt                  ->clear();
  m_eta                 ->clear();
  m_phi                 ->clear();
  m_mass                ->clear();
  m_nOutP               ->clear();
  m_barcode             ->clear();
  m_childOpenAngle      ->clear();
  m_parent_ID           ->clear();
  m_parent_index        ->clear();
  m_parent_pt           ->clear();
  m_parent_eta          ->clear();
  m_parent_phi          ->clear();
  m_parent_E            ->clear();
  m_parent_M            ->clear();
  m_parent_charge       ->clear();
  m_parent_pdgId        ->clear();
  m_parent_status       ->clear();
  m_parent_barcode      ->clear();
  m_parent_prod_ID      ->clear();
  m_parent_prod_index   ->clear();
  m_parent_prod_x       ->clear();
  m_parent_prod_y       ->clear();
  m_parent_prod_z       ->clear();
  m_parent_prod_r       ->clear();
  m_parent_prod_pt      ->clear();
  m_parent_prod_eta     ->clear();
  m_parent_prod_phi     ->clear();
  m_parent_prod_mass    ->clear();
  m_parent_prod_nOutP   ->clear();
  m_parent_prod_barcode ->clear();
  m_outP_ID             ->clear();
  m_outP_index          ->clear();
  m_outP_pt             ->clear();
  m_outP_eta            ->clear();
  m_outP_phi            ->clear();
  m_outP_E              ->clear();
  m_outP_M              ->clear();
  m_outP_charge         ->clear();
  m_outP_pdgId          ->clear();
  m_outP_status         ->clear();
  m_outP_barcode        ->clear();
  m_outP_isReco         ->clear();
  m_outP_isSelected     ->clear();
  m_outP_isAssociated   ->clear();
  m_outP_recoProb       ->clear();
  m_outP_recoID         ->clear();
  m_outP_recoIndex      ->clear();
  m_outP_isStable       ->clear();
  m_outP_isInteracting  ->clear();
  m_outP_isDark         ->clear();

  // reco vertex matching
  if ( m_infoSwitch.m_recoMatching ) {
    m_isReconstructible                ->clear();
    
    m_descendant_n                     ->clear();
    m_descendant_nReco                 ->clear();
    m_descendant_nSelected             ->clear();
    m_descendant_sumPt                 ->clear();
    m_descendant_sumEta                ->clear();
    m_descendant_sumPhi                ->clear();
    m_descendant_sumE                  ->clear();
    m_descendant_sumM                  ->clear();
    m_descendant_recoSumPt             ->clear();
    m_descendant_recoSumEta            ->clear();
    m_descendant_recoSumPhi            ->clear();
    m_descendant_recoSumE              ->clear();
    m_descendant_recoSumM              ->clear();
    m_descendant_truthPosID            ->clear();
    m_descendant_ID                    ->clear();
    m_descendant_index                 ->clear();
    m_descendant_pt                    ->clear();
    m_descendant_eta                   ->clear();
    m_descendant_phi                   ->clear();
    m_descendant_E                     ->clear();
    m_descendant_M                     ->clear();
    m_descendant_charge                ->clear();
    m_descendant_pdgId                 ->clear();
    m_descendant_barcode               ->clear();
    m_descendant_isReco                ->clear();
    m_descendant_isSelected            ->clear();
    m_descendant_isAssociated          ->clear();
    m_descendant_recoProb              ->clear();
    m_descendant_recoID                ->clear();
    m_descendant_recoIndex             ->clear();
    m_descendant_recoD0                ->clear();
    m_descendant_recoZ0                ->clear();
    m_descendant_prod_x                ->clear();
    m_descendant_prod_y                ->clear();
    m_descendant_prod_z                ->clear();
    m_descendant_prod_r                ->clear();
    m_descendant_prod_phi              ->clear();
    m_descendant_prod_barcode          ->clear();
    m_descendant_decay_x               ->clear();
    m_descendant_decay_y               ->clear();
    m_descendant_decay_z               ->clear();
    m_descendant_decay_r               ->clear();
    m_descendant_decay_phi             ->clear();
    m_descendant_decay_barcode         ->clear();

    m_physPos_n                        ->clear();
    m_physPos_maxSeparation            ->clear();
    m_physPos_ID                       ->clear();
    m_physPos_x                        ->clear();
    m_physPos_y                        ->clear();
    m_physPos_z                        ->clear();
    m_physPos_r                        ->clear();
    m_physPos_phi                      ->clear();
    m_physPos_nDesc                    ->clear();
    m_physPos_sumPt                    ->clear();
    m_physPos_sumEta                   ->clear();
    m_physPos_sumPhi                   ->clear();
    m_physPos_sumE                     ->clear();
    m_physPos_sumM                     ->clear();

    m_closestRecoVtx_ID                ->clear();
    m_closestRecoVtx_index             ->clear();
    m_closestRecoVtx_x                 ->clear();
    m_closestRecoVtx_y                 ->clear();
    m_closestRecoVtx_z                 ->clear();
    m_closestRecoVtx_r                 ->clear();
    m_closestRecoVtx_phi               ->clear();
    m_closestRecoVtx_distance          ->clear();

    m_matchedRecoVtx_n                 ->clear();
    m_matchedRecoVtx_ID                ->clear();
    m_matchedRecoVtx_index             ->clear();
    m_matchedRecoVtx_x                 ->clear();
    m_matchedRecoVtx_y                 ->clear();
    m_matchedRecoVtx_z                 ->clear();
    m_matchedRecoVtx_r                 ->clear();
    m_matchedRecoVtx_pt                ->clear();
    m_matchedRecoVtx_eta               ->clear();
    m_matchedRecoVtx_phi               ->clear();
    m_matchedRecoVtx_mass              ->clear();
    m_matchedRecoVtx_pt_clean          ->clear();
    m_matchedRecoVtx_eta_clean         ->clear();
    m_matchedRecoVtx_phi_clean         ->clear();
    m_matchedRecoVtx_mass_clean        ->clear();
    m_matchedRecoVtx_pt_bare           ->clear();
    m_matchedRecoVtx_eta_bare          ->clear();
    m_matchedRecoVtx_phi_bare          ->clear();
    m_matchedRecoVtx_mass_bare         ->clear();
    m_matchedRecoVtx_chi2              ->clear();
    m_matchedRecoVtx_ntrk              ->clear();
    m_matchedRecoVtx_ntrk_sel          ->clear();
    m_matchedRecoVtx_ntrk_assoc        ->clear();
    m_matchedRecoVtx_ntrk_clean        ->clear();
    m_matchedRecoVtx_ntrk_clean_sel    ->clear();
    m_matchedRecoVtx_ntrk_clean_assoc  ->clear();
    m_matchedRecoVtx_ntrk_filt         ->clear();
    m_matchedRecoVtx_ntrk_filt_sel     ->clear();
    m_matchedRecoVtx_ntrk_filt_assoc   ->clear();
    m_matchedRecoVtx_massFraction      ->clear();
    m_matchedRecoVtx_multFraction      ->clear();
    m_matchedRecoVtx_cleanMassFraction ->clear();
    m_matchedRecoVtx_cleanMultFraction ->clear();
    m_matchedRecoVtx_bareMassFraction  ->clear();
    m_matchedRecoVtx_bareMultFraction  ->clear();
    m_matchedRecoVtx_matchScore        ->clear();
    m_matchedRecoVtx_reprTruthPosID    ->clear();
    m_matchedRecoVtx_reprTruthPosX     ->clear();
    m_matchedRecoVtx_reprTruthPosY     ->clear();
    m_matchedRecoVtx_reprTruthPosZ     ->clear();
    m_matchedRecoVtx_reprTruthPosR     ->clear();
    m_matchedRecoVtx_reprTruthPosPhi   ->clear();
    m_matchedRecoVtx_residual_x        ->clear();
    m_matchedRecoVtx_residual_y        ->clear();
    m_matchedRecoVtx_residual_z        ->clear();
    m_matchedRecoVtx_residual_r        ->clear();
    m_matchedRecoVtx_residual_phi      ->clear();
    m_matchedRecoVtx_residual_distance ->clear();
  }

  // matched to jets
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      m_truthJetMatch          ->clear();
      m_truthJetMatch_ID       ->clear();
      m_truthJetMatch_index    ->clear();
      m_truthJetMatch_dR       ->clear();
      m_darkJetMatch           ->clear();
      m_darkJetMatch_ID        ->clear();
      m_darkJetMatch_index     ->clear();
      m_darkJetMatch_dR        ->clear();
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	m_emtopoJetMatch       ->clear();
	m_emtopoJetMatch_ID    ->clear();
	m_emtopoJetMatch_index ->clear();
	m_emtopoJetMatch_dR    ->clear();
      }
      if ( m_doPFlow  ) {
	m_pflowJetMatch        ->clear();
	m_pflowJetMatch_ID     ->clear();
	m_pflowJetMatch_index  ->clear();
	m_pflowJetMatch_dR     ->clear();
      }
    }
  }
}


void TruthVertexContainer :: FillTruthVertex ( const xAOD::TruthVertex* truthVtx, const std::vector<std::string>& truthVtxLLPs,
					       const std::string treeName )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::FillTruthVertex()", "filling branches" );

  VertexContainer::FillVertex ();
  
  bool passSel = true;
  if ( truthVtx->isAvailable<char>("passSel") )
    if ( !truthVtx->auxdataConst<char>("passSel") )
      passSel = false;
  m_passSel ->push_back( passSel );

  std::string llpDecayType = "";
  for ( size_t i = 0; i != truthVtxLLPs.size(); ++i )
    if ( EJsHelper::pdgIdFuncs[truthVtxLLPs.at(i)]( truthVtx ) ) llpDecayType = truthVtxLLPs.at(i);
  m_llpDecay ->push_back( llpDecayType );

  m_ID      ->push_back( AUXDYN( truthVtx, int, "ID"    ) );
  m_index   ->push_back( AUXDYN( truthVtx, int, "index" ) );
  m_x       ->push_back( truthVtx->x()                    );
  m_y       ->push_back( truthVtx->y()                    );
  m_z       ->push_back( truthVtx->z()                    );
  m_r       ->push_back( truthVtx->perp()                 );
  m_eta     ->push_back( truthVtx->eta()                  );
  m_phi     ->push_back( truthVtx->phi()                  );
  m_nOutP   ->push_back( truthVtx->nOutgoingParticles()   );
  m_barcode ->push_back( truthVtx->barcode()              );

  // max distance b/w any two outgoing particles
  double childOpenAngle = -1.0;
  for ( size_t i1 = 0; i1 != truthVtx->nOutgoingParticles(); ++i1 ) {
    const auto* outP1 = truthVtx->outgoingParticle(i1);
    for ( size_t i2 = 0; i2 != truthVtx->nOutgoingParticles(); ++i2 ) {
      const auto* outP2 = truthVtx->outgoingParticle(i2);
      if ( outP1 == outP2 ) continue;
      float dR = EJsHelper::deltaR( outP1->eta(), outP2->eta(), outP1->phi(), outP2->phi() );
      if ( dR > childOpenAngle ) childOpenAngle = dR;
    }
  }
  m_childOpenAngle ->push_back( childOpenAngle );

  int   parent_ID      = AlgConsts::invalidInt;
  int   parent_index   = AlgConsts::invalidInt;
  float parent_pt      = AlgConsts::invalidFloat;
  float parent_eta     = AlgConsts::invalidFloat;
  float parent_phi     = AlgConsts::invalidFloat;
  float parent_E       = AlgConsts::invalidFloat;
  float parent_M       = AlgConsts::invalidFloat;
  float parent_charge  = AlgConsts::invalidFloat;
  float parent_pdgId   = AlgConsts::invalidInt;
  int   parent_status  = AlgConsts::invalidInt;
  int   parent_barcode = AlgConsts::invalidInt;

  int   pProd_ID      = AlgConsts::invalidInt;
  int   pProd_index   = AlgConsts::invalidInt;
  float pProd_x       = AlgConsts::invalidFloat;
  float pProd_y       = AlgConsts::invalidFloat;
  float pProd_z       = AlgConsts::invalidFloat;
  float pProd_r       = AlgConsts::invalidFloat;
  float pProd_pt      = AlgConsts::invalidFloat;
  float pProd_eta     = AlgConsts::invalidFloat;
  float pProd_phi     = AlgConsts::invalidFloat;
  float pProd_mass    = AlgConsts::invalidFloat;
  int   pProd_nOutP   = AlgConsts::invalidInt;
  int   pProd_barcode = AlgConsts::invalidInt;
  
  const auto* parent = truthVtx->incomingParticle(0);
  if ( parent ) {
    parent_ID      = AUXDYN( parent, int, "ID"    );
    parent_index   = AUXDYN( parent, int, "index" );
    parent_pt      = parent->pt() / m_units;
    parent_eta     = parent->eta();
    parent_phi     = parent->phi();
    parent_E       = parent->e()  / m_units;
    parent_M       = parent->m()  / m_units;
    parent_charge  = parent->charge();
    parent_pdgId   = parent->pdgId();
    parent_status  = parent->status();
    parent_barcode = parent->barcode();

    const auto* prodVtx = parent->prodVtx();
    std::vector<const xAOD::TruthParticle*> pProd_outParts;
    if ( prodVtx ) {
      pProd_ID      = AUXDYN( prodVtx, int, "ID"    );
      pProd_index   = AUXDYN( prodVtx, int, "index" );
      pProd_x       = prodVtx->x();
      pProd_y       = prodVtx->y();
      pProd_z       = prodVtx->z();
      pProd_r       = prodVtx->perp();
      pProd_eta     = prodVtx->eta();
      pProd_phi     = prodVtx->phi();
      pProd_nOutP   = prodVtx->nOutgoingParticles();
      pProd_barcode = prodVtx->barcode();

      for ( size_t i = 0; i != prodVtx->nOutgoingParticles(); ++i ) {
	const auto* pProd_outP = prodVtx->outgoingParticle(i);
	if ( !pProd_outP ) continue;
	pProd_outParts .push_back( pProd_outP );
      }
      const TLorentzVector& pProd_sumP4 = EJsHelper::truthSumP4 ( pProd_outParts );
      pProd_pt   = pProd_sumP4.Pt() / m_units;
      pProd_mass = pProd_sumP4.M()  / m_units;
    }
  }

  m_parent_ID      ->push_back( parent_ID      );
  m_parent_index   ->push_back( parent_index   );
  m_parent_pt      ->push_back( parent_pt      );
  m_parent_eta     ->push_back( parent_eta     );
  m_parent_phi     ->push_back( parent_phi     );
  m_parent_E       ->push_back( parent_E       );
  m_parent_M       ->push_back( parent_M       );
  m_parent_charge  ->push_back( parent_charge  );
  m_parent_pdgId   ->push_back( parent_pdgId   );
  m_parent_status  ->push_back( parent_status  );
  m_parent_barcode ->push_back( parent_barcode );

  m_parent_prod_ID      ->push_back( pProd_ID      );
  m_parent_prod_index   ->push_back( pProd_index   );
  m_parent_prod_x       ->push_back( pProd_x       );
  m_parent_prod_y       ->push_back( pProd_y       );
  m_parent_prod_z       ->push_back( pProd_z       );
  m_parent_prod_r       ->push_back( pProd_r       );
  m_parent_prod_pt      ->push_back( pProd_pt      );
  m_parent_prod_eta     ->push_back( pProd_eta     );
  m_parent_prod_phi     ->push_back( pProd_phi     );
  m_parent_prod_mass    ->push_back( pProd_mass    );
  m_parent_prod_nOutP   ->push_back( pProd_nOutP   );
  m_parent_prod_barcode ->push_back( pProd_barcode );

  std::vector<const xAOD::TruthParticle*> outParts;
  
  std::vector<int>     outP_ID;
  std::vector<int>     outP_index;
  std::vector<float>   outP_pt;
  std::vector<float>   outP_eta;
  std::vector<float>   outP_phi;
  std::vector<float>   outP_E;
  std::vector<float>   outP_M;
  std::vector<float>   outP_charge;
  std::vector<int>     outP_pdgId;
  std::vector<int>     outP_status;
  std::vector<int>     outP_barcode;
  std::vector<uint8_t> outP_isReco;
  std::vector<uint8_t> outP_isSelected;
  std::vector<uint8_t> outP_isAssociated;
  std::vector<float>   outP_recoProb;
  std::vector<int>     outP_recoID;
  std::vector<int>     outP_recoIndex;
  std::vector<uint8_t> outP_isStable;
  std::vector<uint8_t> outP_isInteracting;
  std::vector<uint8_t> outP_isDark;
  
  for ( size_t i = 0; i != truthVtx->nOutgoingParticles(); ++i ) {
    const auto* outP = truthVtx->outgoingParticle(i);
    if ( !outP )        continue;
    outParts            .push_back( outP                                           );
    outP_ID             .push_back( AUXDYN( outP, int, "ID"                      ) );
    outP_index          .push_back( AUXDYN( outP, int, "index"                   ) );
    outP_pt             .push_back( outP->pt() / m_units                           );
    outP_eta            .push_back( outP->eta()                                    );
    outP_phi            .push_back( outP->phi()                                    );
    outP_E              .push_back( outP->e()  / m_units                           );
    outP_M              .push_back( outP->m()  / m_units                           );
    outP_charge         .push_back( outP->charge()                                 );
    outP_pdgId          .push_back( outP->pdgId()                                  );
    outP_status         .push_back( outP->status()                                 );
    outP_barcode        .push_back( outP->barcode()                                );
    outP_isReco         .push_back( AUXDYN( outP, char,  "isTrackMatch"          ) );
    outP_recoProb       .push_back( AUXDYN( outP, float, "trackMatchProbability" ) );
    outP_isStable       .push_back( EJsHelper::isStable      ( outP              ) );
    outP_isInteracting  .push_back( EJsHelper::isInteracting ( outP              ) );
    outP_isDark         .push_back( EJsHelper::isDark        ( outP              ) );
    // get linked track
    int     recoID      = AlgConsts::invalidInt;
    int     recoIndex   = AlgConsts::invalidInt;
    uint8_t recoIsSel   = AlgConsts::invalidUnsigned;
    uint8_t recoIsAssoc = AlgConsts::invalidUnsigned;
    static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> recoAccess("trackLink");
    if ( recoAccess.isAvailable( *outP ) ) {
      try {
	const EJsHelper::TrackLink_t& recoLink = recoAccess( *outP );
	recoID      = AUXDYN( (*recoLink), int,  "ID"            );
	recoIndex   = AUXDYN( (*recoLink), int,  "index"         );
	recoIsSel   = AUXDYN( (*recoLink), char, "is_selected"   );
	recoIsAssoc = AUXDYN( (*recoLink), char, "is_associated" );
      } catch(...){}
    }
    outP_recoID       .push_back( recoID      );
    outP_recoIndex    .push_back( recoIndex   );
    outP_isSelected   .push_back( recoIsSel   );
    outP_isAssociated .push_back( recoIsAssoc );
  }

  const TLorentzVector& sumP4 = EJsHelper::truthSumP4 ( outParts );
  m_pt   ->push_back( sumP4.Pt() / m_units );
  m_mass ->push_back( sumP4.M()  / m_units );

  m_outP_ID            ->push_back( outP_ID            );
  m_outP_index         ->push_back( outP_index         );
  m_outP_pt            ->push_back( outP_pt            );
  m_outP_eta           ->push_back( outP_eta           );
  m_outP_phi           ->push_back( outP_phi           );
  m_outP_E             ->push_back( outP_E             );
  m_outP_M             ->push_back( outP_M             );
  m_outP_charge        ->push_back( outP_charge        );
  m_outP_pdgId         ->push_back( outP_pdgId         );
  m_outP_status        ->push_back( outP_status        );
  m_outP_barcode       ->push_back( outP_barcode       );
  m_outP_isReco        ->push_back( outP_isReco        );
  m_outP_isSelected    ->push_back( outP_isSelected    );
  m_outP_isAssociated  ->push_back( outP_isAssociated  );
  m_outP_recoProb      ->push_back( outP_recoProb      );
  m_outP_recoID        ->push_back( outP_recoID        );
  m_outP_recoIndex     ->push_back( outP_recoIndex     );
  m_outP_isStable      ->push_back( outP_isStable      );
  m_outP_isInteracting ->push_back( outP_isInteracting );
  m_outP_isDark        ->push_back( outP_isDark        );


  // reco matching w/ TruthVertexPosition -- reconstructible descendants, physical positions, secVtx matches
  if ( m_infoSwitch.m_recoMatching ) {
    
    std::set<const xAOD::TruthParticle*> reconstructibleDescendants;
    std::set<const xAOD::TruthParticle*> reconstructedDescendants;
    
    // access reconstructible descendant links
    static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLinkVector_t> recoDescAccess("reconstructibleDescendantLinks");
    if ( recoDescAccess.isAvailable( *truthVtx ) ) {
      const EJsHelper::TruthParticleLinkVector_t& recoDescLinks = recoDescAccess( *truthVtx ); 
      // loop over reconstructible descendant links + fill set(s)
      for ( const auto& desclink : recoDescLinks ) {
	if ( !desclink.isValid() ) continue;
	bool descIsReco = AUXDYN( (*desclink), char, "isTrackMatch" );
	reconstructibleDescendants.emplace( *desclink );
	if ( descIsReco ) reconstructedDescendants.emplace( *desclink );
      }
    } // end descendant link access

    // fill TruthVertexPosition vector
    std::vector<EJs::TruthVertexPosition> truthVtxPhysPositions;
    int pos_index = 0;
    for ( const auto* truth : reconstructibleDescendants ) {
      if ( !truth->hasProdVtx() ) continue;
      if ( !truth->prodVtx()    ) continue;
      bool found_pos = false;
      for ( auto& pos : truthVtxPhysPositions ) {
      	// add truth particle descendant to set associated w/ this position (if compatible, i.e w/in certain 3d distance)
      	if ( pos.isCompatibleWith( truth ) ) {
      	  pos.emplace( truth );
      	  found_pos = true;
      	  break;
      	}
      }
      // otherwise, add new position for this truth particle
      if ( !found_pos ) {
      	truthVtxPhysPositions.emplace_back( EJs::TruthVertexPosition( truth, pos_index, truthVtx ) );
	++pos_index;
      }
    }
    // associate tracks to truth vertex position
    for ( auto& pos : truthVtxPhysPositions )
      pos.storeTracks();

    // fill closestRecoVerts vector (closest reco vertex to each physical truth position)
    std::vector<const xAOD::Vertex*> closestRecoVerts;
    // access closest reco vertex links
    static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> closestRecoAccess("closestRecoVertexLinks");
    if ( closestRecoAccess.isAvailable( *truthVtx ) ) {
      const EJsHelper::VertexLinkVector_t& closestRecoLinks = closestRecoAccess( *truthVtx );
      // loop over closest reco vertex links + fill vector
      for ( const auto& closelink : closestRecoLinks ) {
	if ( !closelink.isValid() ) continue;
	closestRecoVerts.push_back( *closelink );
      }
    }
    std::vector<float> closestRecoVerts_distance;
    if ( truthVtx->isAvailable<std::vector<float>>("closestRecoVertexDistances") )
      closestRecoVerts_distance = truthVtx->auxdataConst<std::vector<float>>("closestRecoVertexDistances");

    // fill matchedRecoVerts vector (truth-linked track-pt weighted matching to representative physical truth position)
    std::vector<const xAOD::Vertex*> matchedRecoVerts;
    // access matched reco vertex links
    static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> matchedRecoAccess("matchedRecoVertexLinks");
    if ( matchedRecoAccess.isAvailable( *truthVtx ) ) {
      const EJsHelper::VertexLinkVector_t& matchedRecoLinks = matchedRecoAccess( *truthVtx );
      // loop over matched reco vertex links + fill vector
      for ( const auto& matchlink : matchedRecoLinks ) {
	if ( !matchlink.isValid() ) continue;
	matchedRecoVerts.push_back( *matchlink );
      }
    }
    std::vector<float>    matchedRecoVerts_score;
    std::vector<int>      matchedRecoVerts_reprTruthPosID;
    std::vector<TVector3> matchedRecoVerts_reprTruthPosition;
    std::vector<TVector3> matchedRecoVerts_residual;
    if ( truthVtx->isAvailable<std::vector<float>>("matchedRecoVertexMatchScores") )
      matchedRecoVerts_score = truthVtx->auxdataConst<std::vector<float>>("matchedRecoVertexMatchScores");
    if ( truthVtx->isAvailable<std::vector<int>>("matchedRecoVertexReprTruthPosIDs") )
      matchedRecoVerts_reprTruthPosID = truthVtx->auxdataConst<std::vector<int>>("matchedRecoVertexReprTruthPosIDs");
    if ( truthVtx->isAvailable<std::vector<TVector3>>("matchedRecoVertexReprTruthPositions") )
      matchedRecoVerts_reprTruthPosition = truthVtx->auxdataConst<std::vector<TVector3>>("matchedRecoVertexReprTruthPositions");
    if ( truthVtx->isAvailable<std::vector<TVector3>>("matchedRecoVertexResiduals") )
      matchedRecoVerts_residual = truthVtx->auxdataConst<std::vector<TVector3>>("matchedRecoVertexResiduals");


    m_isReconstructible ->push_back( AUXDYN( truthVtx, char, "isReconstructible" ) );

      
    int                  desc_n         = 0;
    int                  desc_nReco     = 0;
    int                  desc_nSelected = 0;
    std::vector<int>     desc_ID;
    std::vector<int>     desc_index;
    std::vector<float>   desc_pt;
    std::vector<float>   desc_eta;
    std::vector<float>   desc_phi;
    std::vector<float>   desc_E;
    std::vector<float>   desc_M;
    std::vector<float>   desc_charge;
    std::vector<int>     desc_pdgId;
    std::vector<int>     desc_barcode;
    std::vector<uint8_t> desc_isReco;
    std::vector<uint8_t> desc_isSelected;
    std::vector<uint8_t> desc_isAssociated;
    std::vector<float>   desc_recoProb;
    std::vector<int>     desc_recoID;
    std::vector<int>     desc_recoIndex;
    std::vector<float>   desc_recoD0;
    std::vector<float>   desc_recoZ0;
    std::vector<int>     desc_truthPosID;
    std::vector<float>   desc_prod_x;
    std::vector<float>   desc_prod_y;
    std::vector<float>   desc_prod_z;
    std::vector<float>   desc_prod_r;
    std::vector<float>   desc_prod_phi;
    std::vector<int>     desc_prod_barcode;
    std::vector<float>   desc_decay_x;
    std::vector<float>   desc_decay_y;
    std::vector<float>   desc_decay_z;
    std::vector<float>   desc_decay_r;
    std::vector<float>   desc_decay_phi;
    std::vector<int>     desc_decay_barcode;
    
    // loop over reconstructible descendants + fill branches
    for ( const auto& desc : reconstructibleDescendants ) {
      desc_ID      .push_back( AUXDYN( desc, int, "ID"    ) );
      desc_index   .push_back( AUXDYN( desc, int, "index" ) );
      desc_pt      .push_back( desc->pt() / m_units         );
      desc_eta     .push_back( desc->eta()                  );
      desc_phi     .push_back( desc->phi()                  );
      desc_E       .push_back( desc->e()  / m_units         );
      desc_M       .push_back( desc->m()  / m_units         );
      desc_charge  .push_back( desc->charge()               );
      desc_pdgId   .push_back( desc->pdgId()                );
      desc_barcode .push_back( desc->barcode()              );

      // get linked track
      uint8_t isReco      = AUXDYN( desc, char, "isTrackMatch" );
      uint8_t recoIsSel   = AlgConsts::invalidUnsigned;
      uint8_t recoIsAssoc = AlgConsts::invalidUnsigned;
      int     recoID      = AlgConsts::invalidInt;
      int     recoIndex   = AlgConsts::invalidInt;
      float   recoD0      = AlgConsts::invalidFloat;
      float   recoZ0      = AlgConsts::invalidFloat;
      static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> trackAccess("trackLink");
      if ( trackAccess.isAvailable( *desc ) ) {
	try {
	  const EJsHelper::TrackLink_t& trackLink = trackAccess( *desc );
	  recoIsSel   = AUXDYN( (*trackLink), char, "is_selected"   );
	  recoIsAssoc = AUXDYN( (*trackLink), char, "is_associated" );
	  recoID      = AUXDYN( (*trackLink), int,  "ID"            );
	  recoIndex   = AUXDYN( (*trackLink), int,  "index"         );
	  recoD0      = (*trackLink)->d0();
	  recoZ0      = (*trackLink)->z0();
	} catch(...) {}
      }
      desc_isReco       .push_back( isReco                                         );
      desc_isSelected   .push_back( recoIsSel                                      );
      desc_isAssociated .push_back( recoIsAssoc                                    );
      desc_recoProb     .push_back( AUXDYN( desc, float, "trackMatchProbability" ) );
      desc_recoID       .push_back( recoID                                         );
      desc_recoIndex    .push_back( recoIndex                                      );
      desc_recoD0       .push_back( recoD0                                         );
      desc_recoZ0       .push_back( recoZ0                                         );

      // get truth position
      int truthPositionID = AlgConsts::invalidInt;
      for ( const auto& pos : truthVtxPhysPositions ) {
	if ( pos.isCompatibleWith( desc ) ) {
	  truthPositionID = pos.ID();
	  break;
	}
      }
      desc_truthPosID .push_back( truthPositionID );

      // get production vertex
      float prodX       = AlgConsts::invalidFloat;
      float prodY       = AlgConsts::invalidFloat;
      float prodZ       = AlgConsts::invalidFloat;
      float prodR       = AlgConsts::invalidFloat;
      float prodPhi     = AlgConsts::invalidFloat;
      int   prodBarcode = AlgConsts::invalidInt;
      const auto* prodVtx = desc->prodVtx();
      if ( prodVtx ) {
	prodX       = prodVtx->x();
	prodY       = prodVtx->y();
	prodZ       = prodVtx->z();
	prodR       = prodVtx->perp();
	prodPhi     = prodVtx->phi();
	prodBarcode = prodVtx->barcode();
      }
      desc_prod_x       .push_back( prodX       );
      desc_prod_y       .push_back( prodY       );
      desc_prod_z       .push_back( prodZ       );
      desc_prod_r       .push_back( prodR       );
      desc_prod_phi     .push_back( prodPhi     );
      desc_prod_barcode .push_back( prodBarcode );

      // get decay vertex
      float decayX       = AlgConsts::invalidFloat;
      float decayY       = AlgConsts::invalidFloat;
      float decayZ       = AlgConsts::invalidFloat;
      float decayR       = AlgConsts::invalidFloat;
      float decayPhi     = AlgConsts::invalidFloat;
      int   decayBarcode = AlgConsts::invalidInt;
      const auto* decayVtx = desc->decayVtx();
      if ( decayVtx ) {
	decayX       = decayVtx->x();
	decayY       = decayVtx->y();
	decayZ       = decayVtx->z();
	decayR       = decayVtx->perp();
	decayPhi     = decayVtx->phi();
	decayBarcode = decayVtx->barcode();
      }
      desc_decay_x       .push_back( decayX       );
      desc_decay_y       .push_back( decayY       );
      desc_decay_z       .push_back( decayZ       );
      desc_decay_r       .push_back( decayR       );
      desc_decay_phi     .push_back( decayPhi     );
      desc_decay_barcode .push_back( decayBarcode );

      ++desc_n;
      if ( isReco    ) ++desc_nReco;
      if ( recoIsSel ) ++desc_nSelected;
    }
    
    const TLorentzVector& desc_sumP4      = EJsHelper::truthSumP4 ( reconstructibleDescendants );
    const TLorentzVector& desc_reco_sumP4 = EJsHelper::truthSumP4 ( reconstructedDescendants   );
    
    m_descendant_n             ->push_back( desc_n                         );
    m_descendant_nReco         ->push_back( desc_nReco                     );
    m_descendant_nSelected     ->push_back( desc_nSelected                 );
    m_descendant_sumPt         ->push_back( desc_sumP4.Pt()      / m_units );
    m_descendant_sumEta        ->push_back( desc_sumP4.Eta()               );
    m_descendant_sumPhi        ->push_back( desc_sumP4.Phi()               );
    m_descendant_sumE          ->push_back( desc_sumP4.E()       / m_units );
    m_descendant_sumM          ->push_back( desc_sumP4.M()       / m_units );
    m_descendant_recoSumPt     ->push_back( desc_reco_sumP4.Pt() / m_units );
    m_descendant_recoSumEta    ->push_back( desc_reco_sumP4.Eta()          );
    m_descendant_recoSumPhi    ->push_back( desc_reco_sumP4.Phi()          );
    m_descendant_recoSumE      ->push_back( desc_reco_sumP4.E()  / m_units );
    m_descendant_recoSumM      ->push_back( desc_reco_sumP4.M()  / m_units );
    m_descendant_truthPosID    ->push_back( desc_truthPosID                );
    m_descendant_ID            ->push_back( desc_ID                        );
    m_descendant_index         ->push_back( desc_index                     );
    m_descendant_pt            ->push_back( desc_pt                        );
    m_descendant_eta           ->push_back( desc_eta                       );
    m_descendant_phi           ->push_back( desc_phi                       );
    m_descendant_E             ->push_back( desc_E                         );
    m_descendant_M             ->push_back( desc_M                         );
    m_descendant_charge        ->push_back( desc_charge                    );
    m_descendant_pdgId         ->push_back( desc_pdgId                     );
    m_descendant_isReco        ->push_back( desc_isReco                    );
    m_descendant_isSelected    ->push_back( desc_isSelected                );
    m_descendant_isAssociated  ->push_back( desc_isAssociated              );
    m_descendant_recoProb      ->push_back( desc_recoProb                  );
    m_descendant_recoID        ->push_back( desc_recoID                    );
    m_descendant_recoIndex     ->push_back( desc_recoIndex                 );
    m_descendant_recoD0        ->push_back( desc_recoD0                    );
    m_descendant_recoZ0        ->push_back( desc_recoZ0                    );
    m_descendant_prod_x        ->push_back( desc_prod_x                    );
    m_descendant_prod_y        ->push_back( desc_prod_y                    );
    m_descendant_prod_z        ->push_back( desc_prod_z                    );
    m_descendant_prod_r        ->push_back( desc_prod_r                    );
    m_descendant_prod_phi      ->push_back( desc_prod_phi                  );
    m_descendant_prod_barcode  ->push_back( desc_prod_barcode              );
    m_descendant_decay_x       ->push_back( desc_decay_x                   );
    m_descendant_decay_y       ->push_back( desc_decay_y                   );
    m_descendant_decay_z       ->push_back( desc_decay_z                   );
    m_descendant_decay_r       ->push_back( desc_decay_r                   );
    m_descendant_decay_phi     ->push_back( desc_decay_phi                 );
    m_descendant_decay_barcode ->push_back( desc_decay_barcode             );


    int                physPos_n = 0;
    std::vector<int>   physPos_ID;
    std::vector<float> physPos_x;
    std::vector<float> physPos_y;
    std::vector<float> physPos_z;
    std::vector<float> physPos_r;
    std::vector<float> physPos_phi;
    std::vector<int>   physPos_nDesc;
    std::vector<float> physPos_sumPt;
    std::vector<float> physPos_sumEta;
    std::vector<float> physPos_sumPhi;
    std::vector<float> physPos_sumE;
    std::vector<float> physPos_sumM;
    
    // loop over physical positions + fill branches
    for ( const auto& pos : truthVtxPhysPositions ) {
      physPos_ID  .push_back( pos.ID()              );
      physPos_x   .push_back( pos.position().x()    );
      physPos_y   .push_back( pos.position().y()    );
      physPos_z   .push_back( pos.position().z()    );
      physPos_r   .push_back( pos.position().Perp() );
      physPos_phi .push_back( pos.position().Phi()  );

      const auto& pos_truths       = pos.truth_set();
      const auto& pos_truths_sumP4 = EJsHelper::truthSumP4 ( pos_truths );
      physPos_nDesc  .push_back( pos_truths.size()               );
      physPos_sumPt  .push_back( pos_truths_sumP4.Pt() / m_units );
      physPos_sumEta .push_back( pos_truths_sumP4.Eta()          );
      physPos_sumPhi .push_back( pos_truths_sumP4.Phi()          );
      physPos_sumE   .push_back( pos_truths_sumP4.E()  / m_units );
      physPos_sumM   .push_back( pos_truths_sumP4.M()  / m_units );

      ++physPos_n;
    }
    // calculate max separation b/w truth vertex physical positions
    double physPos_maxSep = AlgConsts::invalidFloat;
    for ( const auto& p1 : truthVtxPhysPositions ) {
      for ( const auto& p2 : truthVtxPhysPositions ) {
	if ( p1.ID() == p2.ID() ) continue;
	double distance = ( p1.position() - p2.position() ).Mag();
	if ( distance > physPos_maxSep ) physPos_maxSep = distance;
      }
    }
    
    m_physPos_n             ->push_back( physPos_n      );
    m_physPos_maxSeparation ->push_back( physPos_maxSep );
    m_physPos_ID            ->push_back( physPos_ID     );
    m_physPos_x             ->push_back( physPos_x      );
    m_physPos_y             ->push_back( physPos_y      );
    m_physPos_z             ->push_back( physPos_z      );
    m_physPos_r             ->push_back( physPos_r      );
    m_physPos_phi           ->push_back( physPos_phi    );
    m_physPos_nDesc         ->push_back( physPos_nDesc  );
    m_physPos_sumPt         ->push_back( physPos_sumPt  );
    m_physPos_sumEta        ->push_back( physPos_sumEta );
    m_physPos_sumPhi        ->push_back( physPos_sumPhi );
    m_physPos_sumE          ->push_back( physPos_sumE   );
    m_physPos_sumM          ->push_back( physPos_sumM   );


    std::vector<int>   closeDV_ID;
    std::vector<int>   closeDV_index;
    std::vector<float> closeDV_x;
    std::vector<float> closeDV_y;
    std::vector<float> closeDV_z;
    std::vector<float> closeDV_r;
    std::vector<float> closeDV_phi;
    std::vector<float> closeDV_dist;
    
    // loop over closest reco vertices + fill branches
    int close_index = 0;
    for ( const auto& close : closestRecoVerts ) {
      closeDV_ID    .push_back( close->auxdataConst<int>("ID")            );
      closeDV_index .push_back( close->auxdataConst<int>("index")         );
      closeDV_x     .push_back( close->x()                                );
      closeDV_y     .push_back( close->y()                                );
      closeDV_z     .push_back( close->z()                                );
      closeDV_r     .push_back( close->position().perp()                  );
      closeDV_phi   .push_back( close->position().phi()                   );
      closeDV_dist  .push_back( closestRecoVerts_distance.at(close_index) );
      ++close_index;
    }

    m_closestRecoVtx_ID       ->push_back( closeDV_ID    );
    m_closestRecoVtx_index    ->push_back( closeDV_index );
    m_closestRecoVtx_x        ->push_back( closeDV_x     );
    m_closestRecoVtx_y        ->push_back( closeDV_y     );
    m_closestRecoVtx_z        ->push_back( closeDV_z     );
    m_closestRecoVtx_r        ->push_back( closeDV_r     );
    m_closestRecoVtx_phi      ->push_back( closeDV_phi   );
    m_closestRecoVtx_distance ->push_back( closeDV_dist  );


    std::vector<int>   matchDV_ID;
    std::vector<int>   matchDV_index;
    std::vector<float> matchDV_x;
    std::vector<float> matchDV_y;
    std::vector<float> matchDV_z;
    std::vector<float> matchDV_r;
    std::vector<float> matchDV_pt;
    std::vector<float> matchDV_eta;
    std::vector<float> matchDV_phi;
    std::vector<float> matchDV_mass;
    std::vector<float> matchDV_cleanPt;
    std::vector<float> matchDV_cleanEta;
    std::vector<float> matchDV_cleanPhi;
    std::vector<float> matchDV_cleanMass;
    std::vector<float> matchDV_barePt;
    std::vector<float> matchDV_bareEta;
    std::vector<float> matchDV_barePhi;
    std::vector<float> matchDV_bareMass;
    std::vector<float> matchDV_chi2;
    std::vector<int>   matchDV_ntrk;
    std::vector<int>   matchDV_ntrk_sel;
    std::vector<int>   matchDV_ntrk_assoc;
    std::vector<int>   matchDV_ntrk_clean;
    std::vector<int>   matchDV_ntrk_clean_sel;
    std::vector<int>   matchDV_ntrk_clean_assoc;
    std::vector<int>   matchDV_ntrk_filt;
    std::vector<int>   matchDV_ntrk_filt_sel;
    std::vector<int>   matchDV_ntrk_filt_assoc;
    std::vector<float> matchDV_massFrac;
    std::vector<float> matchDV_multFrac;
    std::vector<float> matchDV_cleanMassFrac;
    std::vector<float> matchDV_cleanMultFrac;
    std::vector<float> matchDV_bareMassFrac;
    std::vector<float> matchDV_bareMultFrac;
    std::vector<float> matchDV_matchScore;
    std::vector<int>   matchDV_reprTruthPosID;
    std::vector<float> matchDV_reprTruthPosX;
    std::vector<float> matchDV_reprTruthPosY;
    std::vector<float> matchDV_reprTruthPosZ;
    std::vector<float> matchDV_reprTruthPosR;
    std::vector<float> matchDV_reprTruthPosPhi;
    std::vector<float> matchDV_residual_x;
    std::vector<float> matchDV_residual_y;
    std::vector<float> matchDV_residual_z;
    std::vector<float> matchDV_residual_r;
    std::vector<float> matchDV_residual_phi;
    std::vector<float> matchDV_residual_dist;
    
    // loop over matched reco vertices + fill branches
    int match_index = 0;
    for ( const auto& match : matchedRecoVerts ) {
      
      // get vector of filtered, clean, and  bare tracks + calculate sum-p4's
      std::vector<const xAOD::TrackParticle*> filteredTracks;
      std::vector<const xAOD::TrackParticle*> cleanTracks;
      std::vector<const xAOD::TrackParticle*> allTracks;
      EJsHelper::getFilteredTracks( match, filteredTracks );
      EJsHelper::getCleanTracks   ( match, cleanTracks    );
      EJsHelper::getAllTracks     ( match, allTracks      );
      const TLorentzVector& matchSumP4       = VsiBonsai::sumP4 ( filteredTracks );
      const TLorentzVector& matchSumP4_clean = VsiBonsai::sumP4 ( cleanTracks    );
      const TLorentzVector& matchSumP4_bare  = VsiBonsai::sumP4 ( allTracks      );
      
      matchDV_ID        .push_back( match->auxdataConst<int>("ID")             );
      matchDV_index     .push_back( match->auxdataConst<int>("index")          );
      matchDV_x         .push_back( match->x()                                 );
      matchDV_y         .push_back( match->y()                                 );
      matchDV_z         .push_back( match->z()                                 );
      matchDV_r         .push_back( match->position().perp()                   );
      matchDV_pt        .push_back( matchSumP4.Pt()       / m_units            );
      matchDV_eta       .push_back( matchSumP4.Eta()                           );
      matchDV_phi       .push_back( matchSumP4.Phi()                           ); // not the same as position-phi
      matchDV_mass      .push_back( matchSumP4.M()        / m_units            );
      matchDV_cleanPt   .push_back( matchSumP4_clean.Pt() / m_units            );
      matchDV_cleanEta  .push_back( matchSumP4_clean.Eta()                     );
      matchDV_cleanPhi  .push_back( matchSumP4_clean.Phi()                     ); // not the same as position-phi
      matchDV_cleanMass .push_back( matchSumP4_clean.M()  / m_units            );
      matchDV_barePt    .push_back( matchSumP4_bare.Pt()  / m_units            );
      matchDV_bareEta   .push_back( matchSumP4_bare.Eta()                      );
      matchDV_barePhi   .push_back( matchSumP4_bare.Phi()                      ); // not the same as position-phi
      matchDV_bareMass  .push_back( matchSumP4_bare.M()   / m_units            );
      matchDV_chi2      .push_back( match->chiSquared()   / match->numberDoF() );

      size_t ntrk_sel   = 0;
      size_t ntrk_assoc = 0;
      for ( const auto& trk : allTracks ) {
	if ( trk->isAvailable<char>("is_selected") )
	  if ( trk->auxdataConst<char>("is_selected") )   ++ntrk_sel;
	if ( trk->isAvailable<char>("is_associated") )
	  if ( trk->auxdataConst<char>("is_associated") ) ++ntrk_assoc;
      }
      size_t ntrk_clean_sel   = 0;
      size_t ntrk_clean_assoc = 0;
      for ( const auto& cleanTrk : cleanTracks ) {
	if ( cleanTrk->isAvailable<char>("is_selected") )
	  if ( cleanTrk->auxdataConst<char>("is_selected") )   ++ntrk_clean_sel;
	if ( cleanTrk->isAvailable<char>("is_associated") )
	  if ( cleanTrk->auxdataConst<char>("is_associated") ) ++ntrk_clean_assoc;
      } 
      size_t ntrk_filt_sel   = 0;
      size_t ntrk_filt_assoc = 0;
      for ( const auto& filtTrk : filteredTracks ) {
	if ( filtTrk->isAvailable<char>("is_selected") )
	  if ( filtTrk->auxdataConst<char>("is_selected") )   ++ntrk_filt_sel;
	if ( filtTrk->isAvailable<char>("is_associated") )
	  if ( filtTrk->auxdataConst<char>("is_associated") ) ++ntrk_filt_assoc;
      } 
      matchDV_ntrk             .push_back( allTracks.size()      );
      matchDV_ntrk_sel         .push_back( ntrk_sel              );
      matchDV_ntrk_assoc       .push_back( ntrk_assoc            );
      matchDV_ntrk_clean       .push_back( cleanTracks.size()    );
      matchDV_ntrk_clean_sel   .push_back( ntrk_clean_sel        );
      matchDV_ntrk_clean_assoc .push_back( ntrk_clean_assoc      );
      matchDV_ntrk_filt        .push_back( filteredTracks.size() );
      matchDV_ntrk_filt_sel    .push_back( ntrk_filt_sel         );
      matchDV_ntrk_filt_assoc  .push_back( ntrk_filt_assoc       );

      matchDV_massFrac      .push_back( matchSumP4.M()        / desc_reco_sumP4.M()                    );
      matchDV_multFrac      .push_back( filteredTracks.size() / float(reconstructedDescendants.size()) );
      matchDV_cleanMassFrac .push_back( matchSumP4_clean.M()  / desc_reco_sumP4.M()                    );
      matchDV_cleanMultFrac .push_back( cleanTracks.size()    / float(reconstructedDescendants.size()) );
      matchDV_bareMassFrac  .push_back( matchSumP4_bare.M()   / desc_reco_sumP4.M()                    );
      matchDV_bareMultFrac  .push_back( allTracks.size()      / float(reconstructedDescendants.size()) );

      matchDV_matchScore      .push_back( matchedRecoVerts_score             .at(match_index)        );
      matchDV_reprTruthPosID  .push_back( matchedRecoVerts_reprTruthPosID    .at(match_index)        );
      matchDV_reprTruthPosX   .push_back( matchedRecoVerts_reprTruthPosition .at(match_index).x()    );
      matchDV_reprTruthPosY   .push_back( matchedRecoVerts_reprTruthPosition .at(match_index).y()    );
      matchDV_reprTruthPosZ   .push_back( matchedRecoVerts_reprTruthPosition .at(match_index).z()    );
      matchDV_reprTruthPosR   .push_back( matchedRecoVerts_reprTruthPosition .at(match_index).Perp() );
      matchDV_reprTruthPosPhi .push_back( matchedRecoVerts_reprTruthPosition .at(match_index).Phi()  );
      matchDV_residual_x      .push_back( matchedRecoVerts_residual          .at(match_index).x()    );
      matchDV_residual_y      .push_back( matchedRecoVerts_residual          .at(match_index).y()    );
      matchDV_residual_z      .push_back( matchedRecoVerts_residual          .at(match_index).z()    );
      matchDV_residual_r      .push_back( matchedRecoVerts_residual          .at(match_index).Perp() );
      matchDV_residual_phi    .push_back( matchedRecoVerts_residual          .at(match_index).Phi()  );
      matchDV_residual_dist   .push_back( matchedRecoVerts_residual          .at(match_index).Mag()  );
      
      ++match_index;
    }

    m_matchedRecoVtx_n                 ->push_back( match_index              );
    m_matchedRecoVtx_ID                ->push_back( matchDV_ID               );
    m_matchedRecoVtx_index             ->push_back( matchDV_index            );
    m_matchedRecoVtx_x                 ->push_back( matchDV_x                );
    m_matchedRecoVtx_y                 ->push_back( matchDV_y                );
    m_matchedRecoVtx_z                 ->push_back( matchDV_z                );
    m_matchedRecoVtx_r                 ->push_back( matchDV_r                ); 
    m_matchedRecoVtx_pt                ->push_back( matchDV_pt               );
    m_matchedRecoVtx_eta               ->push_back( matchDV_eta              );
    m_matchedRecoVtx_phi               ->push_back( matchDV_phi              );
    m_matchedRecoVtx_mass              ->push_back( matchDV_mass             );
    m_matchedRecoVtx_pt_clean          ->push_back( matchDV_cleanPt          );
    m_matchedRecoVtx_eta_clean         ->push_back( matchDV_cleanEta         );
    m_matchedRecoVtx_phi_clean         ->push_back( matchDV_cleanPhi         );
    m_matchedRecoVtx_mass_clean        ->push_back( matchDV_cleanMass        );
    m_matchedRecoVtx_pt_bare           ->push_back( matchDV_barePt           );
    m_matchedRecoVtx_eta_bare          ->push_back( matchDV_bareEta          );
    m_matchedRecoVtx_phi_bare          ->push_back( matchDV_barePhi          );
    m_matchedRecoVtx_mass_bare         ->push_back( matchDV_bareMass         );
    m_matchedRecoVtx_chi2              ->push_back( matchDV_chi2             );
    m_matchedRecoVtx_ntrk              ->push_back( matchDV_ntrk             );
    m_matchedRecoVtx_ntrk_sel          ->push_back( matchDV_ntrk_sel         );
    m_matchedRecoVtx_ntrk_assoc        ->push_back( matchDV_ntrk_assoc       );
    m_matchedRecoVtx_ntrk_clean        ->push_back( matchDV_ntrk_clean       );
    m_matchedRecoVtx_ntrk_clean_sel    ->push_back( matchDV_ntrk_clean_sel   );
    m_matchedRecoVtx_ntrk_clean_assoc  ->push_back( matchDV_ntrk_clean_assoc );
    m_matchedRecoVtx_ntrk_filt         ->push_back( matchDV_ntrk_filt        );
    m_matchedRecoVtx_ntrk_filt_sel     ->push_back( matchDV_ntrk_filt_sel    );
    m_matchedRecoVtx_ntrk_filt_assoc   ->push_back( matchDV_ntrk_filt_assoc  );
    m_matchedRecoVtx_massFraction      ->push_back( matchDV_massFrac         );
    m_matchedRecoVtx_multFraction      ->push_back( matchDV_multFrac         );
    m_matchedRecoVtx_cleanMassFraction ->push_back( matchDV_cleanMassFrac    );
    m_matchedRecoVtx_cleanMultFraction ->push_back( matchDV_cleanMultFrac    );
    m_matchedRecoVtx_bareMassFraction  ->push_back( matchDV_bareMassFrac     );
    m_matchedRecoVtx_bareMultFraction  ->push_back( matchDV_bareMultFrac     );
    m_matchedRecoVtx_matchScore        ->push_back( matchDV_matchScore       );
    m_matchedRecoVtx_reprTruthPosID    ->push_back( matchDV_reprTruthPosID   );
    m_matchedRecoVtx_reprTruthPosX     ->push_back( matchDV_reprTruthPosX    );
    m_matchedRecoVtx_reprTruthPosY     ->push_back( matchDV_reprTruthPosY    );
    m_matchedRecoVtx_reprTruthPosZ     ->push_back( matchDV_reprTruthPosZ    );
    m_matchedRecoVtx_reprTruthPosR     ->push_back( matchDV_reprTruthPosR    );
    m_matchedRecoVtx_reprTruthPosPhi   ->push_back( matchDV_reprTruthPosPhi  );
    m_matchedRecoVtx_residual_x        ->push_back( matchDV_residual_x       );
    m_matchedRecoVtx_residual_y        ->push_back( matchDV_residual_y       );
    m_matchedRecoVtx_residual_z        ->push_back( matchDV_residual_z       );
    m_matchedRecoVtx_residual_r        ->push_back( matchDV_residual_r       );
    m_matchedRecoVtx_residual_phi      ->push_back( matchDV_residual_phi     );
    m_matchedRecoVtx_residual_distance ->push_back( matchDV_residual_dist    );
    
  } // end reco matching switch


  // jet matching (jets to which DVs are dR-matched)
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    std::string jet_str = treeName;
    if ( treeName == "nominal" ) jet_str = "";
    uint8_t isTruthJetMatch  = false;
    if ( truthVtx->isAvailable<char>("isMatchedToTruthJet") )
      isTruthJetMatch  = truthVtx->auxdataConst<char>("isMatchedToTruthJet");
    uint8_t isDarkJetMatch   = false;
    if ( truthVtx->isAvailable<char>("isMatchedToDarkJet")  )
      isDarkJetMatch   = truthVtx->auxdataConst<char>("isMatchedToDarkJet");
    uint8_t isEMTopoJetMatch = false;
    std::string emtopo_str   = "";
    if ( truthVtx->isAvailable<char>("isMatchedToRecoJet_EMTopo" + jet_str) ) {
      isEMTopoJetMatch = truthVtx->auxdataConst<char>("isMatchedToRecoJet_EMTopo" + jet_str);
      emtopo_str       = jet_str;
    }
    else if ( truthVtx->isAvailable<char>("isMatchedToRecoJet_EMTopo") )
      isEMTopoJetMatch = truthVtx->auxdataConst<char>("isMatchedToRecoJet_EMTopo");
    uint8_t isPFlowJetMatch  = false;
    std::string pflow_str    = "";
    if ( truthVtx->isAvailable<char>("isMatchedToRecoJet_PFlow" + jet_str) ) {
      isPFlowJetMatch  = truthVtx->auxdataConst<char>("isMatchedToRecoJet_PFlow" + jet_str);
      pflow_str        = jet_str;
    }
    else if ( truthVtx->isAvailable<char>("isMatchedToRecoJet_PFlow") )
      isPFlowJetMatch  = truthVtx->auxdataConst<char>("isMatchedToRecoJet_PFlow");

    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      m_truthJetMatch          ->push_back( isTruthJetMatch                               );
      m_truthJetMatch_ID       ->push_back( AUXDYN( truthVtx, int,   "truthJetMatchID"    ) );
      m_truthJetMatch_index    ->push_back( AUXDYN( truthVtx, int,   "truthJetMatchIndex" ) );
      m_truthJetMatch_dR       ->push_back( AUXDYN( truthVtx, float, "truthJetMatchDR"    ) );
      m_darkJetMatch           ->push_back( isDarkJetMatch                                );
      m_darkJetMatch_ID        ->push_back( AUXDYN( truthVtx, int,   "darkJetMatchID"     ) );
      m_darkJetMatch_index     ->push_back( AUXDYN( truthVtx, int,   "darkJetMatchIndex"  ) );
      m_darkJetMatch_dR        ->push_back( AUXDYN( truthVtx, float, "darkJetMatchDR"     ) );
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	m_emtopoJetMatch       ->push_back( isEMTopoJetMatch                                                 );
	m_emtopoJetMatch_ID    ->push_back( AUXDYN( truthVtx, int,   "recoJetMatchID_EMTopo"    + emtopo_str ) );
	m_emtopoJetMatch_index ->push_back( AUXDYN( truthVtx, int,   "recoJetMatchIndex_EMTopo" + emtopo_str ) );
	m_emtopoJetMatch_dR    ->push_back( AUXDYN( truthVtx, float, "recoJetMatchDR_EMTopo"    + emtopo_str ) );
      }
      if ( m_doPFlow  ) {
	m_pflowJetMatch        ->push_back( isPFlowJetMatch                                                  );
	m_pflowJetMatch_ID     ->push_back( AUXDYN( truthVtx, int,   "recoJetMatchID_PFlow"     + pflow_str  ) );
	m_pflowJetMatch_index  ->push_back( AUXDYN( truthVtx, int,   "recoJetMatchIndex_PFlow"  + pflow_str  ) );
	m_pflowJetMatch_dR     ->push_back( AUXDYN( truthVtx, float, "recoJetMatchDR_PFlow"     + pflow_str  ) );
      }
    }
  } // end jet-matched switch
}
