#include <TVector3.h>
#include <TLorentzVector.h>

#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>
#include <xAODTruth/TruthVertexContainer.h>

#include "EJsAnalysis/SecondaryVertexContainer.h"
#include "EJsAnalysis/VsiBonsaiTool.h"
#include "EJsAnalysis/EJsHelperFunctions.h"

using namespace EJs;

SecondaryVertexContainer :: SecondaryVertexContainer ( const std::string& name, const std::string& detailStr, float units,
						       bool mc, bool emtopo, bool pflow ) :
  VertexContainer ( name, detailStr, units, mc )
{
  m_doEMTopo = emtopo;
  m_doPFlow  = pflow;
  
  if ( m_debug ) Info( "EJs::SecondaryVertexContainer()", "setting up" );

  m_ID                           = new std::vector<int>;
  m_index                        = new std::vector<int>;
  m_x                            = new std::vector<float>;
  m_y                            = new std::vector<float>;
  m_z                            = new std::vector<float>;
  m_r                            = new std::vector<float>;
  m_pt                           = new std::vector<float>;
  m_eta                          = new std::vector<float>;
  m_phi                          = new std::vector<float>;
  m_mass                         = new std::vector<float>;
  m_mass_nonAssoc                = new std::vector<float>;
  m_covariance                   = new std::vector<std::vector<float>>;
  m_chi2                         = new std::vector<float>;
  m_direction                    = new std::vector<float>;
  m_charge                       = new std::vector<int>;
  m_H                            = new std::vector<float>;
  m_Ht                           = new std::vector<float>;
  m_minOpAng                     = new std::vector<float>;
  m_maxOpAng                     = new std::vector<float>;
  m_mind0                        = new std::vector<float>;
  m_maxd0                        = new std::vector<float>;
  m_distToPV                     = new std::vector<float>;

  m_pt_clean                     = new std::vector<float>;
  m_eta_clean                    = new std::vector<float>;
  m_phi_clean                    = new std::vector<float>;
  m_mass_clean                   = new std::vector<float>;
  m_mass_nonAssoc_clean          = new std::vector<float>;
  m_direction_clean              = new std::vector<float>;
  m_charge_clean                 = new std::vector<int>;
  m_H_clean                      = new std::vector<float>;
  m_Ht_clean                     = new std::vector<float>;
  m_minOpAng_clean               = new std::vector<float>;
  m_maxOpAng_clean               = new std::vector<float>;
  m_mind0_clean                  = new std::vector<float>;
  m_maxd0_clean                  = new std::vector<float>;
  
  m_pt_bare                      = new std::vector<float>;
  m_eta_bare                     = new std::vector<float>;
  m_phi_bare                     = new std::vector<float>;
  m_mass_bare                    = new std::vector<float>;
  m_mass_nonAssoc_bare           = new std::vector<float>;
  m_direction_bare               = new std::vector<float>;
  m_charge_bare                  = new std::vector<int>;
  m_H_bare                       = new std::vector<float>;
  m_Ht_bare                      = new std::vector<float>;
  m_minOpAng_bare                = new std::vector<float>;
  m_maxOpAng_bare                = new std::vector<float>;
  m_mind0_bare                   = new std::vector<float>;
  m_maxd0_bare                   = new std::vector<float>;
  
  m_minOneTrackRemovedMass       = new std::vector<float>;
  m_twoTracksMass                = new std::vector<std::vector<float>>;
  m_twoTracksMassRest            = new std::vector<std::vector<float>>;
  m_twoTracksCharge              = new std::vector<std::vector<int>>;

  m_minOneTrackRemovedMass_clean = new std::vector<float>;
  m_twoTracksMass_clean          = new std::vector<std::vector<float>>;
  m_twoTracksMassRest_clean      = new std::vector<std::vector<float>>;
  m_twoTracksCharge_clean        = new std::vector<std::vector<int>>;
  
  m_minOneTrackRemovedMass_bare  = new std::vector<float>;
  m_twoTracksMass_bare           = new std::vector<std::vector<float>>;
  m_twoTracksMassRest_bare       = new std::vector<std::vector<float>>;
  m_twoTracksCharge_bare         = new std::vector<std::vector<int>>;
  
  m_ntrk                         = new std::vector<int>;
  m_ntrk_sel                     = new std::vector<int>;
  m_ntrk_assoc                   = new std::vector<int>;
  m_ntrk_clean                   = new std::vector<int>;
  m_ntrk_clean_sel               = new std::vector<int>;
  m_ntrk_clean_assoc             = new std::vector<int>;
  m_ntrk_filt                    = new std::vector<int>;
  m_ntrk_filt_sel                = new std::vector<int>;
  m_ntrk_filt_assoc              = new std::vector<int>;

  // tracks
  if ( m_infoSwitch.m_tracks ) {
    m_trk_ID                 = new std::vector<std::vector<int>>;
    m_trk_index              = new std::vector<std::vector<int>>;
    m_trk_qOverP             = new std::vector<std::vector<float>>;
    m_trk_theta              = new std::vector<std::vector<float>>;
    m_trk_vz                 = new std::vector<std::vector<float>>;
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

    m_trk_pt_wrtSV           = new std::vector<std::vector<float>>;
    m_trk_eta_wrtSV          = new std::vector<std::vector<float>>;
    m_trk_phi_wrtSV          = new std::vector<std::vector<float>>;
    m_trk_d0_wrtSV           = new std::vector<std::vector<float>>;
    m_trk_z0_wrtSV           = new std::vector<std::vector<float>>;
    m_trk_errd0_wrtSV        = new std::vector<std::vector<float>>;
    m_trk_errz0_wrtSV        = new std::vector<std::vector<float>>;
    m_trk_errP_wrtSV         = new std::vector<std::vector<float>>;
    m_trk_chi2_toSV          = new std::vector<std::vector<float>>;

    m_trk_charge             = new std::vector<std::vector<int>>;
    m_trk_isFinal            = new std::vector<std::vector<uint8_t>>;
    m_trk_isSelected         = new std::vector<std::vector<uint8_t>>;
    m_trk_isAssociated       = new std::vector<std::vector<uint8_t>>;
    m_trk_isClean            = new std::vector<std::vector<uint8_t>>;
    m_trk_isFiltered         = new std::vector<std::vector<uint8_t>>;
    m_trk_nPixelHits         = new std::vector<std::vector<uint8_t>>;
    m_trk_nSCTHits           = new std::vector<std::vector<uint8_t>>;
    m_trk_nTRTHits           = new std::vector<std::vector<uint8_t>>;
    m_trk_nPixelBarrelLayers = new std::vector<std::vector<uint8_t>>;
    m_trk_nPixelEndCapLayers = new std::vector<std::vector<uint8_t>>;
    m_trk_nSCTBarrelLayers   = new std::vector<std::vector<uint8_t>>;
    m_trk_nSCTEndCapLayers   = new std::vector<std::vector<uint8_t>>;
    m_trk_hitPattern         = new std::vector<std::vector<uint32_t>>;
    m_trk_dEdx               = new std::vector<std::vector<float>>;
    m_trk_nUsedHitsdEdx      = new std::vector<std::vector<uint8_t>>;
    m_trk_nIBLOverflowsdEdx  = new std::vector<std::vector<uint8_t>>;
    m_trk_radiusOfFirstHit   = new std::vector<std::vector<float>>;
 
    if ( m_mc ) {
      m_trk_truthProb        = new std::vector<std::vector<float>>;
      m_trk_truthID          = new std::vector<std::vector<int>>;
      m_trk_truthIndex       = new std::vector<std::vector<int>>;
      m_trk_truthBarcode     = new std::vector<std::vector<int>>;
      m_trk_truthPdgId       = new std::vector<std::vector<int>>;
      m_trk_truthIsDesc      = new std::vector<std::vector<uint8_t>>;
    }
  }

  // truth vertex matching
  if ( m_infoSwitch.m_truthMatching && m_mc ) {
    m_closestTruthVtx_llpDecay          = new std::vector<std::string>;
    m_closestTruthVtx_isReconstructible = new std::vector<uint8_t>;
    m_closestTruthVtx_ID                = new std::vector<int>;
    m_closestTruthVtx_index             = new std::vector<int>;
    m_closestTruthVtx_x                 = new std::vector<float>;
    m_closestTruthVtx_y                 = new std::vector<float>;
    m_closestTruthVtx_z                 = new std::vector<float>;
    m_closestTruthVtx_r                 = new std::vector<float>;
    m_closestTruthVtx_phi               = new std::vector<float>;
    m_closestTruthVtx_barcode           = new std::vector<int>;
    m_closestTruthVtx_distance          = new std::vector<float>;
    m_closestTruthVtxPhysPos_ID         = new std::vector<int>;
    m_closestTruthVtxPhysPos_x          = new std::vector<float>;
    m_closestTruthVtxPhysPos_y          = new std::vector<float>;
    m_closestTruthVtxPhysPos_z          = new std::vector<float>;
    m_closestTruthVtxPhysPos_r          = new std::vector<float>;
    m_closestTruthVtxPhysPos_phi        = new std::vector<float>;
    m_closestTruthVtxPhysPos_distance   = new std::vector<float>;

    m_matchedTruthVtx_n                 = new std::vector<int>;
    m_matchedTruthVtx_llpDecay          = new std::vector<std::vector<std::string>>;
    m_matchedTruthVtx_ID                = new std::vector<std::vector<int>>;
    m_matchedTruthVtx_index             = new std::vector<std::vector<int>>;
    m_matchedTruthVtx_x                 = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_y                 = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_z                 = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_r                 = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_pt                = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_eta               = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_phi               = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_mass              = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_barcode           = new std::vector<std::vector<int>>;
    m_matchedTruthVtx_distance          = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_nDesc             = new std::vector<std::vector<int>>;
    m_matchedTruthVtx_descSumPt         = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_descSumEta        = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_descSumPhi        = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_descSumM          = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_nRecoDesc         = new std::vector<std::vector<int>>;
    m_matchedTruthVtx_recoDescSumPt     = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_recoDescSumEta    = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_recoDescSumPhi    = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_recoDescSumM      = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_massFraction      = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_multFraction      = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_cleanMassFraction = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_cleanMultFraction = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_bareMassFraction  = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_bareMultFraction  = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_matchScore        = new std::vector<std::vector<float>>;
    m_matchedTruthVtxReprPhysPos_ID     = new std::vector<std::vector<int>>;
    m_matchedTruthVtxReprPhysPos_x      = new std::vector<std::vector<float>>;
    m_matchedTruthVtxReprPhysPos_y      = new std::vector<std::vector<float>>;
    m_matchedTruthVtxReprPhysPos_z      = new std::vector<std::vector<float>>;
    m_matchedTruthVtxReprPhysPos_r      = new std::vector<std::vector<float>>;
    m_matchedTruthVtxReprPhysPos_phi    = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_residual_x        = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_residual_y        = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_residual_z        = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_residual_r        = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_residual_phi      = new std::vector<std::vector<float>>;
    m_matchedTruthVtx_residual_distance = new std::vector<std::vector<float>>;
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


SecondaryVertexContainer :: ~SecondaryVertexContainer ()
{
  if ( m_debug ) Info( "EJs::SecondaryVertexContainer()", "deleting" );

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
  delete m_mass_nonAssoc;
  delete m_covariance;
  delete m_chi2;
  delete m_direction;
  delete m_charge;
  delete m_H;
  delete m_Ht;
  delete m_minOpAng;
  delete m_maxOpAng;
  delete m_mind0;
  delete m_maxd0;
  delete m_distToPV;

  delete m_pt_clean;
  delete m_eta_clean;
  delete m_phi_clean;
  delete m_mass_clean;
  delete m_mass_nonAssoc_clean;
  delete m_direction_clean;
  delete m_charge_clean;
  delete m_H_clean;
  delete m_Ht_clean;
  delete m_minOpAng_clean;
  delete m_maxOpAng_clean;
  delete m_mind0_clean;
  delete m_maxd0_clean;
  
  delete m_pt_bare;
  delete m_eta_bare;
  delete m_phi_bare;
  delete m_mass_bare;
  delete m_mass_nonAssoc_bare;
  delete m_direction_bare;
  delete m_charge_bare;
  delete m_H_bare;
  delete m_Ht_bare;
  delete m_minOpAng_bare;
  delete m_maxOpAng_bare;
  delete m_mind0_bare;
  delete m_maxd0_bare;
  
  delete m_minOneTrackRemovedMass;
  delete m_twoTracksMass;
  delete m_twoTracksMassRest;
  delete m_twoTracksCharge;

  delete m_minOneTrackRemovedMass_clean;
  delete m_twoTracksMass_clean;
  delete m_twoTracksMassRest_clean;
  delete m_twoTracksCharge_clean;
  
  delete m_minOneTrackRemovedMass_bare;
  delete m_twoTracksMass_bare;
  delete m_twoTracksMassRest_bare;
  delete m_twoTracksCharge_bare;
  
  delete m_ntrk;
  delete m_ntrk_sel;
  delete m_ntrk_assoc;
  delete m_ntrk_clean;
  delete m_ntrk_clean_sel;
  delete m_ntrk_clean_assoc;
  delete m_ntrk_filt;
  delete m_ntrk_filt_sel;
  delete m_ntrk_filt_assoc;

  // tracks
  if ( m_infoSwitch.m_tracks ) {
    delete m_trk_ID;
    delete m_trk_index;
    delete m_trk_qOverP;
    delete m_trk_theta;
    delete m_trk_vz;
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

    delete m_trk_pt_wrtSV;
    delete m_trk_eta_wrtSV;
    delete m_trk_phi_wrtSV;
    delete m_trk_d0_wrtSV;
    delete m_trk_z0_wrtSV;
    delete m_trk_errd0_wrtSV;
    delete m_trk_errz0_wrtSV;
    delete m_trk_errP_wrtSV;
    delete m_trk_chi2_toSV;

    delete m_trk_charge;
    delete m_trk_isFinal;
    delete m_trk_isSelected;
    delete m_trk_isAssociated;
    delete m_trk_isClean;
    delete m_trk_isFiltered;
    delete m_trk_nPixelHits;
    delete m_trk_nSCTHits;
    delete m_trk_nTRTHits;
    delete m_trk_nPixelBarrelLayers;
    delete m_trk_nPixelEndCapLayers;
    delete m_trk_nSCTBarrelLayers;
    delete m_trk_nSCTEndCapLayers;
    delete m_trk_hitPattern;
    delete m_trk_dEdx;
    delete m_trk_nUsedHitsdEdx;
    delete m_trk_nIBLOverflowsdEdx;
    delete m_trk_radiusOfFirstHit;

    if ( m_mc ) {
      delete m_trk_truthProb;
      delete m_trk_truthID;
      delete m_trk_truthIndex;
      delete m_trk_truthBarcode;
      delete m_trk_truthPdgId;
      delete m_trk_truthIsDesc;
    }
  }

  // truth vertex matching
  if ( m_infoSwitch.m_truthMatching && m_mc ) {
    delete m_closestTruthVtx_llpDecay;
    delete m_closestTruthVtx_isReconstructible;
    delete m_closestTruthVtx_ID;
    delete m_closestTruthVtx_index;
    delete m_closestTruthVtx_x;
    delete m_closestTruthVtx_y;
    delete m_closestTruthVtx_z;
    delete m_closestTruthVtx_r;
    delete m_closestTruthVtx_phi;
    delete m_closestTruthVtx_barcode;
    delete m_closestTruthVtx_distance;
    delete m_closestTruthVtxPhysPos_ID;
    delete m_closestTruthVtxPhysPos_x;
    delete m_closestTruthVtxPhysPos_y;
    delete m_closestTruthVtxPhysPos_z;
    delete m_closestTruthVtxPhysPos_r;
    delete m_closestTruthVtxPhysPos_phi;
    delete m_closestTruthVtxPhysPos_distance;

    delete m_matchedTruthVtx_n;
    delete m_matchedTruthVtx_llpDecay;
    delete m_matchedTruthVtx_ID;
    delete m_matchedTruthVtx_index;
    delete m_matchedTruthVtx_x;
    delete m_matchedTruthVtx_y;
    delete m_matchedTruthVtx_z;
    delete m_matchedTruthVtx_r;
    delete m_matchedTruthVtx_pt;
    delete m_matchedTruthVtx_eta;
    delete m_matchedTruthVtx_phi;
    delete m_matchedTruthVtx_mass;
    delete m_matchedTruthVtx_barcode;
    delete m_matchedTruthVtx_distance;
    delete m_matchedTruthVtx_nDesc;
    delete m_matchedTruthVtx_descSumPt;
    delete m_matchedTruthVtx_descSumEta;
    delete m_matchedTruthVtx_descSumPhi;
    delete m_matchedTruthVtx_descSumM;
    delete m_matchedTruthVtx_nRecoDesc;
    delete m_matchedTruthVtx_recoDescSumPt;
    delete m_matchedTruthVtx_recoDescSumEta;
    delete m_matchedTruthVtx_recoDescSumPhi;
    delete m_matchedTruthVtx_recoDescSumM;
    delete m_matchedTruthVtx_massFraction;
    delete m_matchedTruthVtx_multFraction;
    delete m_matchedTruthVtx_cleanMassFraction;
    delete m_matchedTruthVtx_cleanMultFraction;
    delete m_matchedTruthVtx_bareMassFraction;
    delete m_matchedTruthVtx_bareMultFraction;
    delete m_matchedTruthVtx_matchScore;
    delete m_matchedTruthVtxReprPhysPos_ID;
    delete m_matchedTruthVtxReprPhysPos_x;
    delete m_matchedTruthVtxReprPhysPos_y;
    delete m_matchedTruthVtxReprPhysPos_z;
    delete m_matchedTruthVtxReprPhysPos_r;
    delete m_matchedTruthVtxReprPhysPos_phi;
    delete m_matchedTruthVtx_residual_x;
    delete m_matchedTruthVtx_residual_y;
    delete m_matchedTruthVtx_residual_z;
    delete m_matchedTruthVtx_residual_r;
    delete m_matchedTruthVtx_residual_phi;
    delete m_matchedTruthVtx_residual_distance;
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


void SecondaryVertexContainer :: setTree ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::SecondaryVertexContainer::setTree()", "setting tree" );

  VertexContainer::setTree ( tree );

  connectBranch<int>                ( tree, "ID",                           &m_ID                           );
  connectBranch<int>                ( tree, "index",                        &m_index                        );
  connectBranch<float>              ( tree, "x",                            &m_x                            );
  connectBranch<float>              ( tree, "y",                            &m_y                            );
  connectBranch<float>              ( tree, "z",                            &m_z                            );
  connectBranch<float>              ( tree, "r",                            &m_r                            );
  connectBranch<float>              ( tree, "pt",                           &m_pt                           );
  connectBranch<float>              ( tree, "eta",                          &m_eta                          );
  connectBranch<float>              ( tree, "phi",                          &m_phi                          );
  connectBranch<float>              ( tree, "mass",                         &m_mass                         );
  connectBranch<float>              ( tree, "mass_nonAssoc",                &m_mass_nonAssoc                );
  connectBranch<std::vector<float>> ( tree, "covariance",                   &m_covariance                   );
  connectBranch<float>              ( tree, "chi2",                         &m_chi2                         );
  connectBranch<float>              ( tree, "direction",                    &m_direction                    );
  connectBranch<int>                ( tree, "charge",                       &m_charge                       );
  connectBranch<float>              ( tree, "H",                            &m_H                            );
  connectBranch<float>              ( tree, "Ht",                           &m_Ht                           );
  connectBranch<float>              ( tree, "minOpAng",                     &m_minOpAng                     );
  connectBranch<float>              ( tree, "maxOpAng",                     &m_maxOpAng                     );
  connectBranch<float>              ( tree, "mind0",                        &m_mind0                        );
  connectBranch<float>              ( tree, "maxd0",                        &m_maxd0                        );
  connectBranch<float>              ( tree, "distToPV",                     &m_distToPV                     );

  connectBranch<float>              ( tree, "pt_clean",                     &m_pt_clean                     );
  connectBranch<float>              ( tree, "eta_clean",                    &m_eta_clean                    );
  connectBranch<float>              ( tree, "phi_clean",                    &m_phi_clean                    );
  connectBranch<float>              ( tree, "mass_clean",                   &m_mass_clean                   );
  connectBranch<float>              ( tree, "mass_nonAssoc_clean",          &m_mass_nonAssoc_clean          );
  connectBranch<float>              ( tree, "direction_clean",              &m_direction_clean              );
  connectBranch<int>                ( tree, "charge_clean",                 &m_charge_clean                 );
  connectBranch<float>              ( tree, "H_clean",                      &m_H_clean                      );
  connectBranch<float>              ( tree, "Ht_clean",                     &m_Ht_clean                     );
  connectBranch<float>              ( tree, "minOpAng_clean",               &m_minOpAng_clean               );
  connectBranch<float>              ( tree, "maxOpAng_clean",               &m_maxOpAng_clean               );
  connectBranch<float>              ( tree, "mind0_clean",                  &m_mind0_clean                  );
  connectBranch<float>              ( tree, "maxd0_clean",                  &m_maxd0_clean                  );
  
  connectBranch<float>              ( tree, "pt_bare",                      &m_pt_bare                      );
  connectBranch<float>              ( tree, "eta_bare",                     &m_eta_bare                     );
  connectBranch<float>              ( tree, "phi_bare",                     &m_phi_bare                     );
  connectBranch<float>              ( tree, "mass_bare",                    &m_mass_bare                    );
  connectBranch<float>              ( tree, "mass_nonAssoc_bare",           &m_mass_nonAssoc_bare           );
  connectBranch<float>              ( tree, "direction_bare",               &m_direction_bare               );
  connectBranch<int>                ( tree, "charge_bare",                  &m_charge_bare                  );
  connectBranch<float>              ( tree, "H_bare",                       &m_H_bare                       );
  connectBranch<float>              ( tree, "Ht_bare",                      &m_Ht_bare                      );
  connectBranch<float>              ( tree, "minOpAng_bare",                &m_minOpAng_bare                );
  connectBranch<float>              ( tree, "maxOpAng_bare",                &m_maxOpAng_bare                );
  connectBranch<float>              ( tree, "mind0_bare",                   &m_mind0_bare                   );
  connectBranch<float>              ( tree, "maxd0_bare",                   &m_maxd0_bare                   );
  
  connectBranch<float>              ( tree, "minOneTrackRemovedMass",       &m_minOneTrackRemovedMass       );
  connectBranch<std::vector<float>> ( tree, "twoTracksMass",                &m_twoTracksMass                );
  connectBranch<std::vector<float>> ( tree, "twoTracksMassRest",            &m_twoTracksMassRest            );
  connectBranch<std::vector<int>>   ( tree, "twoTracksCharge",              &m_twoTracksCharge              );

  connectBranch<float>              ( tree, "minOneTrackRemovedMass_clean", &m_minOneTrackRemovedMass_clean );
  connectBranch<std::vector<float>> ( tree, "twoTracksMass_clean",          &m_twoTracksMass_clean          );
  connectBranch<std::vector<float>> ( tree, "twoTracksMassRest_clean",      &m_twoTracksMassRest_clean      );
  connectBranch<std::vector<int>>   ( tree, "twoTracksCharge_clean",        &m_twoTracksCharge_clean        );
  
  connectBranch<float>              ( tree, "minOneTrackRemovedMass_bare",  &m_minOneTrackRemovedMass_bare  );
  connectBranch<std::vector<float>> ( tree, "twoTracksMass_bare",           &m_twoTracksMass_bare           );
  connectBranch<std::vector<float>> ( tree, "twoTracksMassRest_bare",       &m_twoTracksMassRest_bare       );
  connectBranch<std::vector<int>>   ( tree, "twoTracksCharge_bare",         &m_twoTracksCharge_bare         );
  
  connectBranch<int>                ( tree, "ntrk",                         &m_ntrk                         );
  connectBranch<int>                ( tree, "ntrk_sel",                     &m_ntrk_sel                     );
  connectBranch<int>                ( tree, "ntrk_assoc",                   &m_ntrk_assoc                   );
  connectBranch<int>                ( tree, "ntrk_clean",                   &m_ntrk_clean                   );
  connectBranch<int>                ( tree, "ntrk_clean_sel",               &m_ntrk_clean_sel               );
  connectBranch<int>                ( tree, "ntrk_clean_assoc",             &m_ntrk_clean_assoc             );
  connectBranch<int>                ( tree, "ntrk_filt",                    &m_ntrk_filt                    );
  connectBranch<int>                ( tree, "ntrk_filt_sel",                &m_ntrk_filt_sel                );
  connectBranch<int>                ( tree, "ntrk_filt_assoc",              &m_ntrk_filt_assoc              );

  // tracks
  if ( m_infoSwitch.m_tracks ) {
    connectBranch<std::vector<int>>       ( tree, "trk_ID",                 &m_trk_ID                 );
    connectBranch<std::vector<int>>       ( tree, "trk_index",              &m_trk_index              );
    connectBranch<std::vector<float>>     ( tree, "trk_qOverP",             &m_trk_qOverP             );
    connectBranch<std::vector<float>>     ( tree, "trk_theta",              &m_trk_theta              );
    connectBranch<std::vector<float>>     ( tree, "trk_vz",                 &m_trk_vz                 );
    connectBranch<std::vector<float>>     ( tree, "trk_E",                  &m_trk_E                  );
    connectBranch<std::vector<float>>     ( tree, "trk_M",                  &m_trk_M                  );
    connectBranch<std::vector<float>>     ( tree, "trk_pt",                 &m_trk_pt                 );
    connectBranch<std::vector<float>>     ( tree, "trk_eta",                &m_trk_eta                );
    connectBranch<std::vector<float>>     ( tree, "trk_phi",                &m_trk_phi                );
    connectBranch<std::vector<float>>     ( tree, "trk_d0",                 &m_trk_d0                 );
    connectBranch<std::vector<float>>     ( tree, "trk_z0",                 &m_trk_z0                 );
    connectBranch<std::vector<float>>     ( tree, "trk_errd0",              &m_trk_errd0              );
    connectBranch<std::vector<float>>     ( tree, "trk_errz0",              &m_trk_errz0              );
    connectBranch<std::vector<float>>     ( tree, "trk_chi2",               &m_trk_chi2               );

    connectBranch<std::vector<float>>     ( tree, "trk_pt_wrtSV",           &m_trk_pt_wrtSV           );
    connectBranch<std::vector<float>>     ( tree, "trk_eta_wrtSV",          &m_trk_eta_wrtSV          );
    connectBranch<std::vector<float>>     ( tree, "trk_phi_wrtSV",          &m_trk_phi_wrtSV          );
    connectBranch<std::vector<float>>     ( tree, "trk_d0_wrtSV",           &m_trk_d0_wrtSV           );
    connectBranch<std::vector<float>>     ( tree, "trk_z0_wrtSV",           &m_trk_z0_wrtSV           );
    connectBranch<std::vector<float>>     ( tree, "trk_errd0_wrtSV",        &m_trk_errd0_wrtSV        );
    connectBranch<std::vector<float>>     ( tree, "trk_errz0_wrtSV",        &m_trk_errz0_wrtSV        );
    connectBranch<std::vector<float>>     ( tree, "trk_errP_wrtSV",         &m_trk_errP_wrtSV         );
    connectBranch<std::vector<float>>     ( tree, "trk_chi2_toSV",          &m_trk_chi2_toSV          );

    connectBranch<std::vector<int>>       ( tree, "trk_charge",             &m_trk_charge             );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_isFinal",            &m_trk_isFinal            );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_isSelected",         &m_trk_isSelected         );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_isAssociated",       &m_trk_isAssociated       );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_isClean",            &m_trk_isClean            );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_isFiltered",         &m_trk_isFiltered         );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_nPixelHits",         &m_trk_nPixelHits         );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_nSCTHits",           &m_trk_nSCTHits           );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_nTRTHits",           &m_trk_nTRTHits           );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_nPixelBarrelLayers", &m_trk_nPixelBarrelLayers );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_nPixelEndCapLayers", &m_trk_nPixelEndCapLayers );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_nSCTBarrelLayers",   &m_trk_nSCTBarrelLayers   );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_nSCTEndCapLayers",   &m_trk_nSCTEndCapLayers   );
    connectBranch<std::vector<uint32_t>>  ( tree, "trk_hitPattern",         &m_trk_hitPattern         );
    connectBranch<std::vector<float>>     ( tree, "trk_dEdx",               &m_trk_dEdx               );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_nUsedHitsdEdx",      &m_trk_nUsedHitsdEdx      );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_nIBLOverflowsdEdx",  &m_trk_nIBLOverflowsdEdx  );
    connectBranch<std::vector<float>>     ( tree, "trk_radiusOfFirstHit",   &m_trk_radiusOfFirstHit   );

    // truth matched to tracks
    if ( m_mc ) {
      connectBranch<std::vector<float>>   ( tree, "trk_truthProb",          &m_trk_truthProb          );
      connectBranch<std::vector<int>>     ( tree, "trk_truthID",            &m_trk_truthID            );
      connectBranch<std::vector<int>>     ( tree, "trk_truthIndex",         &m_trk_truthIndex         );
      connectBranch<std::vector<int>>     ( tree, "trk_truthBarcode",       &m_trk_truthBarcode       );
      connectBranch<std::vector<int>>     ( tree, "trk_truthPdgId",         &m_trk_truthPdgId         );
      connectBranch<std::vector<uint8_t>> ( tree, "trk_truthIsDesc",        &m_trk_truthIsDesc        );
    }
  }

  // truth vertex matching
  if ( m_infoSwitch.m_truthMatching && m_mc ) {
    connectBranch<std::string>              ( tree, "closestTruthVtx_llpDecay",          &m_closestTruthVtx_llpDecay          );
    connectBranch<uint8_t>                  ( tree, "closestTruthVtx_isReconstructible", &m_closestTruthVtx_isReconstructible );
    connectBranch<int>                      ( tree, "closestTruthVtx_ID",                &m_closestTruthVtx_ID                );
    connectBranch<int>                      ( tree, "closestTruthVtx_index",             &m_closestTruthVtx_index             );
    connectBranch<float>                    ( tree, "closestTruthVtx_x",                 &m_closestTruthVtx_x                 );
    connectBranch<float>                    ( tree, "closestTruthVtx_y",                 &m_closestTruthVtx_y                 );
    connectBranch<float>                    ( tree, "closestTruthVtx_z",                 &m_closestTruthVtx_z                 );
    connectBranch<float>                    ( tree, "closestTruthVtx_r",                 &m_closestTruthVtx_r                 );
    connectBranch<float>                    ( tree, "closestTruthVtx_phi",               &m_closestTruthVtx_phi               );
    connectBranch<int>                      ( tree, "closestTruthVtx_barcode",           &m_closestTruthVtx_barcode           );
    connectBranch<float>                    ( tree, "closestTruthVtx_distance",          &m_closestTruthVtx_distance          );
    connectBranch<int>                      ( tree, "closestTruthVtxPhysPos_ID",         &m_closestTruthVtxPhysPos_ID         );
    connectBranch<float>                    ( tree, "closestTruthVtxPhysPos_x",          &m_closestTruthVtxPhysPos_x          );
    connectBranch<float>                    ( tree, "closestTruthVtxPhysPos_y",          &m_closestTruthVtxPhysPos_y          );
    connectBranch<float>                    ( tree, "closestTruthVtxPhysPos_z",          &m_closestTruthVtxPhysPos_z          );
    connectBranch<float>                    ( tree, "closestTruthVtxPhysPos_r",          &m_closestTruthVtxPhysPos_r          );
    connectBranch<float>                    ( tree, "closestTruthVtxPhysPos_phi",        &m_closestTruthVtxPhysPos_phi        );
    connectBranch<float>                    ( tree, "closestTruthVtxPhysPos_distance",   &m_closestTruthVtxPhysPos_distance   );

    connectBranch<int>                      ( tree, "matchedTruthVtx_n",                 &m_matchedTruthVtx_n                 );
    connectBranch<std::vector<std::string>> ( tree, "matchedTruthVtx_llpDecay",          &m_matchedTruthVtx_llpDecay          );
    connectBranch<std::vector<int>>         ( tree, "matchedTruthVtx_ID",                &m_matchedTruthVtx_ID                );
    connectBranch<std::vector<int>>         ( tree, "matchedTruthVtx_index",             &m_matchedTruthVtx_index             );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_x",                 &m_matchedTruthVtx_x                 );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_y",                 &m_matchedTruthVtx_y                 );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_z",                 &m_matchedTruthVtx_z                 );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_r",                 &m_matchedTruthVtx_r                 );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_pt",                &m_matchedTruthVtx_pt                );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_eta",               &m_matchedTruthVtx_eta               );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_phi",               &m_matchedTruthVtx_phi               );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_mass",              &m_matchedTruthVtx_mass              );
    connectBranch<std::vector<int>>         ( tree, "matchedTruthVtx_barcode",           &m_matchedTruthVtx_barcode           );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_distance",          &m_matchedTruthVtx_distance          );
    connectBranch<std::vector<int>>         ( tree, "matchedTruthVtx_nDesc",             &m_matchedTruthVtx_nDesc             );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_descSumPt",         &m_matchedTruthVtx_descSumPt         );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_descSumEta",        &m_matchedTruthVtx_descSumEta        );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_descSumPhi",        &m_matchedTruthVtx_descSumPhi        );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_descSumM",          &m_matchedTruthVtx_descSumM          );
    connectBranch<std::vector<int>>         ( tree, "matchedTruthVtx_nRecoDesc",         &m_matchedTruthVtx_nRecoDesc         );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_recoDescSumPt",     &m_matchedTruthVtx_recoDescSumPt     );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_recoDescSumEta",    &m_matchedTruthVtx_recoDescSumEta    );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_recoDescSumPhi",    &m_matchedTruthVtx_recoDescSumPhi    );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_recoDescSumM",      &m_matchedTruthVtx_recoDescSumM      );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_massFraction",      &m_matchedTruthVtx_massFraction      );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_multFraction",      &m_matchedTruthVtx_multFraction      );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_cleanMassFraction", &m_matchedTruthVtx_cleanMassFraction );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_cleanMultFraction", &m_matchedTruthVtx_cleanMultFraction );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_bareMassFraction",  &m_matchedTruthVtx_bareMassFraction  );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_bareMultFraction",  &m_matchedTruthVtx_bareMultFraction  );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_matchScore",        &m_matchedTruthVtx_matchScore        );
    connectBranch<std::vector<int>>         ( tree, "matchedTruthVtxReprPhysPos_ID",     &m_matchedTruthVtxReprPhysPos_ID     );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtxReprPhysPos_x",      &m_matchedTruthVtxReprPhysPos_x      );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtxReprPhysPos_y",      &m_matchedTruthVtxReprPhysPos_y      );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtxReprPhysPos_z",      &m_matchedTruthVtxReprPhysPos_z      );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtxReprPhysPos_r",      &m_matchedTruthVtxReprPhysPos_r      );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtxReprPhysPos_phi",    &m_matchedTruthVtxReprPhysPos_phi    );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_x",        &m_matchedTruthVtx_residual_x        );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_y",        &m_matchedTruthVtx_residual_y        );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_z",        &m_matchedTruthVtx_residual_z        );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_r",        &m_matchedTruthVtx_residual_r        );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_phi",      &m_matchedTruthVtx_residual_phi      );
    connectBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_distance", &m_matchedTruthVtx_residual_distance );
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


void SecondaryVertexContainer :: setBranches ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::SecondaryVertexContainer::setBranches()", "setting branches" );

  VertexContainer::setBranches ( tree );

  setBranch<int>                ( tree, "ID",                           m_ID                           );
  setBranch<int>                ( tree, "index",                        m_index                        );
  setBranch<float>              ( tree, "x",                            m_x                            );
  setBranch<float>              ( tree, "y",                            m_y                            );
  setBranch<float>              ( tree, "z",                            m_z                            );
  setBranch<float>              ( tree, "r",                            m_r                            );
  setBranch<float>              ( tree, "pt",                           m_pt                           );
  setBranch<float>              ( tree, "eta",                          m_eta                          );
  setBranch<float>              ( tree, "phi",                          m_phi                          );
  setBranch<float>              ( tree, "mass",                         m_mass                         );
  setBranch<float>              ( tree, "mass_nonAssoc",                m_mass_nonAssoc                );
  setBranch<std::vector<float>> ( tree, "covariance",                   m_covariance                   );
  setBranch<float>              ( tree, "chi2",                         m_chi2                         );
  setBranch<float>              ( tree, "direction",                    m_direction                    );
  setBranch<int>                ( tree, "charge",                       m_charge                       );
  setBranch<float>              ( tree, "H",                            m_H                            );
  setBranch<float>              ( tree, "Ht",                           m_Ht                           );
  setBranch<float>              ( tree, "minOpAng",                     m_minOpAng                     );
  setBranch<float>              ( tree, "maxOpAng",                     m_maxOpAng                     );
  setBranch<float>              ( tree, "mind0",                        m_mind0                        );
  setBranch<float>              ( tree, "maxd0",                        m_maxd0                        );
  setBranch<float>              ( tree, "distToPV",                     m_distToPV                     );

  setBranch<float>              ( tree, "pt_clean",                     m_pt_clean                     );
  setBranch<float>              ( tree, "eta_clean",                    m_eta_clean                    );
  setBranch<float>              ( tree, "phi_clean",                    m_phi_clean                    );
  setBranch<float>              ( tree, "mass_clean",                   m_mass_clean                   );
  setBranch<float>              ( tree, "mass_nonAssoc_clean",          m_mass_nonAssoc_clean          );
  setBranch<float>              ( tree, "direction_clean",              m_direction_clean              );
  setBranch<int>                ( tree, "charge_clean",                 m_charge_clean                 );
  setBranch<float>              ( tree, "H_clean",                      m_H_clean                      );
  setBranch<float>              ( tree, "Ht_clean",                     m_Ht_clean                     );
  setBranch<float>              ( tree, "minOpAng_clean",               m_minOpAng_clean               );
  setBranch<float>              ( tree, "maxOpAng_clean",               m_maxOpAng_clean               );
  setBranch<float>              ( tree, "mind0_clean",                  m_mind0_clean                  );
  setBranch<float>              ( tree, "maxd0_clean",                  m_maxd0_clean                  );
  
  setBranch<float>              ( tree, "pt_bare",                      m_pt_bare                      );
  setBranch<float>              ( tree, "eta_bare",                     m_eta_bare                     );
  setBranch<float>              ( tree, "phi_bare",                     m_phi_bare                     );
  setBranch<float>              ( tree, "mass_bare",                    m_mass_bare                    );
  setBranch<float>              ( tree, "mass_nonAssoc_bare",           m_mass_nonAssoc_bare           );
  setBranch<float>              ( tree, "direction_bare",               m_direction_bare               );
  setBranch<int>                ( tree, "charge_bare",                  m_charge_bare                  );
  setBranch<float>              ( tree, "H_bare",                       m_H_bare                       );
  setBranch<float>              ( tree, "Ht_bare",                      m_Ht_bare                      );
  setBranch<float>              ( tree, "minOpAng_bare",                m_minOpAng_bare                );
  setBranch<float>              ( tree, "maxOpAng_bare",                m_maxOpAng_bare                );
  setBranch<float>              ( tree, "mind0_bare",                   m_mind0_bare                   );
  setBranch<float>              ( tree, "maxd0_bare",                   m_maxd0_bare                   );

  setBranch<float>              ( tree, "minOneTrackRemovedMass",       m_minOneTrackRemovedMass       );
  setBranch<std::vector<float>> ( tree, "twoTracksMass",                m_twoTracksMass                );
  setBranch<std::vector<float>> ( tree, "twoTracksMassRest",            m_twoTracksMassRest            );
  setBranch<std::vector<int>>   ( tree, "twoTracksCharge",              m_twoTracksCharge              );

  setBranch<float>              ( tree, "minOneTrackRemovedMass_clean", m_minOneTrackRemovedMass_clean );
  setBranch<std::vector<float>> ( tree, "twoTracksMass_clean",          m_twoTracksMass_clean          );
  setBranch<std::vector<float>> ( tree, "twoTracksMassRest_clean",      m_twoTracksMassRest_clean      );
  setBranch<std::vector<int>>   ( tree, "twoTracksCharge_clean",        m_twoTracksCharge_clean        );
  
  setBranch<float>              ( tree, "minOneTrackRemovedMass_bare",  m_minOneTrackRemovedMass_bare  );
  setBranch<std::vector<float>> ( tree, "twoTracksMass_bare",           m_twoTracksMass_bare           );
  setBranch<std::vector<float>> ( tree, "twoTracksMassRest_bare",       m_twoTracksMassRest_bare       );
  setBranch<std::vector<int>>   ( tree, "twoTracksCharge_bare",         m_twoTracksCharge_bare         );

  setBranch<int>                ( tree, "ntrk",                   m_ntrk                   );
  setBranch<int>                ( tree, "ntrk_sel",               m_ntrk_sel               );
  setBranch<int>                ( tree, "ntrk_assoc",             m_ntrk_assoc             );
  setBranch<int>                ( tree, "ntrk_clean",             m_ntrk_clean             );
  setBranch<int>                ( tree, "ntrk_clean_sel",         m_ntrk_clean_sel         );
  setBranch<int>                ( tree, "ntrk_clean_assoc",       m_ntrk_clean_assoc       );
  setBranch<int>                ( tree, "ntrk_filt",              m_ntrk_filt              );
  setBranch<int>                ( tree, "ntrk_filt_sel",          m_ntrk_filt_sel          );
  setBranch<int>                ( tree, "ntrk_filt_assoc",        m_ntrk_filt_assoc        );

  // tracks
  if ( m_infoSwitch.m_tracks ) {
    setBranch<std::vector<int>>       ( tree, "trk_ID",                  m_trk_ID                );
    setBranch<std::vector<int>>       ( tree, "trk_index",               m_trk_index             );
    setBranch<std::vector<float>>     ( tree, "trk_qOverP",              m_trk_qOverP            );
    setBranch<std::vector<float>>     ( tree, "trk_theta",               m_trk_theta             );
    setBranch<std::vector<float>>     ( tree, "trk_vz",                  m_trk_vz                );
    setBranch<std::vector<float>>     ( tree, "trk_E",                   m_trk_E                 );
    setBranch<std::vector<float>>     ( tree, "trk_M",                   m_trk_M                 );
    setBranch<std::vector<float>>     ( tree, "trk_pt",                  m_trk_pt                );
    setBranch<std::vector<float>>     ( tree, "trk_eta",                 m_trk_eta               );
    setBranch<std::vector<float>>     ( tree, "trk_phi",                 m_trk_phi               );
    setBranch<std::vector<float>>     ( tree, "trk_d0",                  m_trk_d0                );
    setBranch<std::vector<float>>     ( tree, "trk_z0",                  m_trk_z0                );
    setBranch<std::vector<float>>     ( tree, "trk_errd0",               m_trk_errd0             );
    setBranch<std::vector<float>>     ( tree, "trk_errz0",               m_trk_errz0             );
    setBranch<std::vector<float>>     ( tree, "trk_chi2",                m_trk_chi2              );  

    setBranch<std::vector<float>>     ( tree, "trk_pt_wrtSV",            m_trk_pt_wrtSV          );
    setBranch<std::vector<float>>     ( tree, "trk_eta_wrtSV",           m_trk_eta_wrtSV         );
    setBranch<std::vector<float>>     ( tree, "trk_phi_wrtSV",           m_trk_phi_wrtSV         );
    setBranch<std::vector<float>>     ( tree, "trk_d0_wrtSV",            m_trk_d0_wrtSV          );
    setBranch<std::vector<float>>     ( tree, "trk_z0_wrtSV",            m_trk_z0_wrtSV          );
    setBranch<std::vector<float>>     ( tree, "trk_errd0_wrtSV",         m_trk_errd0_wrtSV       );
    setBranch<std::vector<float>>     ( tree, "trk_errz0_wrtSV",         m_trk_errz0_wrtSV       );
    setBranch<std::vector<float>>     ( tree, "trk_errP_wrtSV",          m_trk_errP_wrtSV        );
    setBranch<std::vector<float>>     ( tree, "trk_chi2_toSV",           m_trk_chi2_toSV         ); 

    setBranch<std::vector<int>>       ( tree, "trk_charge",             m_trk_charge             );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_isFinal",            m_trk_isFinal            );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_isSelected",         m_trk_isSelected         );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_isAssociated",       m_trk_isAssociated       );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_isClean",            m_trk_isClean            );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_isFiltered",         m_trk_isFiltered         );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_nPixelBarrelLayers", m_trk_nPixelBarrelLayers );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_nPixelEndCapLayers", m_trk_nPixelEndCapLayers );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_nSCTBarrelLayers",   m_trk_nSCTBarrelLayers   );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_nSCTEndCapLayers",   m_trk_nSCTEndCapLayers   );
    setBranch<std::vector<uint32_t>>  ( tree, "trk_hitPattern",         m_trk_hitPattern         );
    setBranch<std::vector<float>>     ( tree, "trk_dEdx",               m_trk_dEdx               );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_nUsedHitsdEdx",      m_trk_nUsedHitsdEdx      );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_nIBLOverflowsdEdx",  m_trk_nIBLOverflowsdEdx  );
    setBranch<std::vector<float>>     ( tree, "trk_radiusOfFirstHit",   m_trk_radiusOfFirstHit   );

    if ( m_mc ) {
      setBranch<std::vector<float>>   ( tree, "trk_truthProb",          m_trk_truthProb          );
      setBranch<std::vector<int>>     ( tree, "trk_truthID",            m_trk_truthID            );
      setBranch<std::vector<int>>     ( tree, "trk_truthIndex",         m_trk_truthIndex         );
      setBranch<std::vector<int>>     ( tree, "trk_truthBarcode",       m_trk_truthBarcode       );
      setBranch<std::vector<int>>     ( tree, "trk_truthPdgId",         m_trk_truthPdgId         );
      setBranch<std::vector<uint8_t>> ( tree, "trk_truthIsDesc",        m_trk_truthIsDesc        );
    }
  }

  // truth vertex matching
  if ( m_infoSwitch.m_truthMatching && m_mc ) {
    setBranch<std::string>              ( tree, "closestTruthVtx_llpDecay",          m_closestTruthVtx_llpDecay          );
    setBranch<uint8_t>                  ( tree, "closestTruthVtx_isReconstructible", m_closestTruthVtx_isReconstructible );
    setBranch<int>                      ( tree, "closestTruthVtx_ID",                m_closestTruthVtx_ID                );
    setBranch<int>                      ( tree, "closestTruthVtx_index",             m_closestTruthVtx_index             );
    setBranch<float>                    ( tree, "closestTruthVtx_x",                 m_closestTruthVtx_x                 );
    setBranch<float>                    ( tree, "closestTruthVtx_y",                 m_closestTruthVtx_y                 );
    setBranch<float>                    ( tree, "closestTruthVtx_z",                 m_closestTruthVtx_z                 );
    setBranch<float>                    ( tree, "closestTruthVtx_r",                 m_closestTruthVtx_r                 );
    setBranch<float>                    ( tree, "closestTruthVtx_phi",               m_closestTruthVtx_phi               );
    setBranch<int>                      ( tree, "closestTruthVtx_barcode",           m_closestTruthVtx_barcode           );
    setBranch<float>                    ( tree, "closestTruthVtx_distance",          m_closestTruthVtx_distance          );
    setBranch<int>                      ( tree, "closestTruthVtxPhysPos_ID",         m_closestTruthVtxPhysPos_ID         );
    setBranch<float>                    ( tree, "closestTruthVtxPhysPos_x",          m_closestTruthVtxPhysPos_x          );
    setBranch<float>                    ( tree, "closestTruthVtxPhysPos_y",          m_closestTruthVtxPhysPos_y          );
    setBranch<float>                    ( tree, "closestTruthVtxPhysPos_z",          m_closestTruthVtxPhysPos_z          );
    setBranch<float>                    ( tree, "closestTruthVtxPhysPos_r",          m_closestTruthVtxPhysPos_r          );
    setBranch<float>                    ( tree, "closestTruthVtxPhysPos_phi",        m_closestTruthVtxPhysPos_phi        );
    setBranch<float>                    ( tree, "closestTruthVtxPhysPos_distance",   m_closestTruthVtxPhysPos_distance   );

    setBranch<int>                      ( tree, "matchedTruthVtx_n",                 m_matchedTruthVtx_n                 );
    setBranch<std::vector<std::string>> ( tree, "matchedTruthVtx_llpDecay",          m_matchedTruthVtx_llpDecay          );
    setBranch<std::vector<int>>         ( tree, "matchedTruthVtx_ID",                m_matchedTruthVtx_ID                );
    setBranch<std::vector<int>>         ( tree, "matchedTruthVtx_index",             m_matchedTruthVtx_index             );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_x",                 m_matchedTruthVtx_x                 );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_y",                 m_matchedTruthVtx_y                 );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_z",                 m_matchedTruthVtx_z                 );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_r",                 m_matchedTruthVtx_r                 );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_pt",                m_matchedTruthVtx_pt                );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_eta",               m_matchedTruthVtx_eta               );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_phi",               m_matchedTruthVtx_phi               );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_mass",              m_matchedTruthVtx_mass              );
    setBranch<std::vector<int>>         ( tree, "matchedTruthVtx_barcode",           m_matchedTruthVtx_barcode           );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_distance",          m_matchedTruthVtx_distance          );
    setBranch<std::vector<int>>         ( tree, "matchedTruthVtx_nDesc",             m_matchedTruthVtx_nDesc             );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_descSumPt",         m_matchedTruthVtx_descSumPt         );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_descSumEta",        m_matchedTruthVtx_descSumEta        );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_descSumPhi",        m_matchedTruthVtx_descSumPhi        );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_descSumM",          m_matchedTruthVtx_descSumM          );
    setBranch<std::vector<int>>         ( tree, "matchedTruthVtx_nRecoDesc",         m_matchedTruthVtx_nRecoDesc         );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_recoDescSumPt",     m_matchedTruthVtx_recoDescSumPt     );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_recoDescSumEta",    m_matchedTruthVtx_recoDescSumEta    );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_recoDescSumPhi",    m_matchedTruthVtx_recoDescSumPhi    );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_recoDescSumM",      m_matchedTruthVtx_recoDescSumM      );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_massFraction",      m_matchedTruthVtx_massFraction      );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_multFraction",      m_matchedTruthVtx_multFraction      );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_cleanMassFraction", m_matchedTruthVtx_cleanMassFraction );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_cleanMultFraction", m_matchedTruthVtx_cleanMultFraction );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_bareMassFraction",  m_matchedTruthVtx_bareMassFraction  );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_bareMultFraction",  m_matchedTruthVtx_bareMultFraction  );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_matchScore",        m_matchedTruthVtx_matchScore        );
    setBranch<std::vector<int>>         ( tree, "matchedTruthVtxReprPhysPos_ID",     m_matchedTruthVtxReprPhysPos_ID     );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtxReprPhysPos_x",      m_matchedTruthVtxReprPhysPos_x      );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtxReprPhysPos_y",      m_matchedTruthVtxReprPhysPos_y      );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtxReprPhysPos_z",      m_matchedTruthVtxReprPhysPos_z      );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtxReprPhysPos_r",      m_matchedTruthVtxReprPhysPos_r      );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtxReprPhysPos_phi",    m_matchedTruthVtxReprPhysPos_phi    );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_x",        m_matchedTruthVtx_residual_x        );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_y",        m_matchedTruthVtx_residual_y        );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_z",        m_matchedTruthVtx_residual_z        );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_r",        m_matchedTruthVtx_residual_r        );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_phi",      m_matchedTruthVtx_residual_phi      );
    setBranch<std::vector<float>>       ( tree, "matchedTruthVtx_residual_distance", m_matchedTruthVtx_residual_distance );
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


void SecondaryVertexContainer :: clear ()
{
  if ( m_debug ) Info( "EJs::SecondaryVertexContainer::clear()", "clearing branches" );

  VertexContainer::clear ();

  m_ID                           ->clear();
  m_index                        ->clear();
  m_x                            ->clear();
  m_y                            ->clear();
  m_z                            ->clear();
  m_r                            ->clear();
  m_pt                           ->clear();
  m_eta                          ->clear();
  m_phi                          ->clear();
  m_mass                         ->clear();
  m_mass_nonAssoc                ->clear();
  m_covariance                   ->clear();
  m_chi2                         ->clear();
  m_direction                    ->clear();
  m_charge                       ->clear();
  m_H                            ->clear();
  m_Ht                           ->clear();
  m_minOpAng                     ->clear();
  m_maxOpAng                     ->clear();
  m_mind0                        ->clear();
  m_maxd0                        ->clear();
  m_distToPV                     ->clear();

  m_pt_clean                     ->clear();
  m_eta_clean                    ->clear();
  m_phi_clean                    ->clear();
  m_mass_clean                   ->clear();
  m_mass_nonAssoc_clean          ->clear();
  m_direction_clean              ->clear();
  m_charge_clean                 ->clear();
  m_H_clean                      ->clear();
  m_Ht_clean                     ->clear();
  m_minOpAng_clean               ->clear();
  m_maxOpAng_clean               ->clear();
  m_mind0_clean                  ->clear();
  m_maxd0_clean                  ->clear();
  
  m_pt_bare                      ->clear();
  m_eta_bare                     ->clear();
  m_phi_bare                     ->clear();
  m_mass_bare                    ->clear();
  m_mass_nonAssoc_bare           ->clear();
  m_direction_bare               ->clear();
  m_charge_bare                  ->clear();
  m_H_bare                       ->clear();
  m_Ht_bare                      ->clear();
  m_minOpAng_bare                ->clear();
  m_maxOpAng_bare                ->clear();
  m_mind0_bare                   ->clear();
  m_maxd0_bare                   ->clear();
  
  m_minOneTrackRemovedMass       ->clear();
  m_twoTracksMass                ->clear();
  m_twoTracksMassRest            ->clear();
  m_twoTracksCharge              ->clear();

  m_minOneTrackRemovedMass_clean ->clear();
  m_twoTracksMass_clean          ->clear();
  m_twoTracksMassRest_clean      ->clear();
  m_twoTracksCharge_clean        ->clear();
  
  m_minOneTrackRemovedMass_bare  ->clear();
  m_twoTracksMass_bare           ->clear();
  m_twoTracksMassRest_bare       ->clear();
  m_twoTracksCharge_bare         ->clear();

  m_ntrk                         ->clear();
  m_ntrk_sel                     ->clear();
  m_ntrk_assoc                   ->clear();
  m_ntrk_clean                   ->clear();
  m_ntrk_clean_sel               ->clear();
  m_ntrk_clean_assoc             ->clear();
  m_ntrk_filt                    ->clear();
  m_ntrk_filt_sel                ->clear();
  m_ntrk_filt_assoc              ->clear();

  // tracks
  if ( m_infoSwitch.m_tracks ) {
    m_trk_ID                 ->clear();
    m_trk_index              ->clear();
    m_trk_qOverP             ->clear();
    m_trk_theta              ->clear();
    m_trk_vz                 ->clear();
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

    m_trk_pt_wrtSV           ->clear();
    m_trk_eta_wrtSV          ->clear();
    m_trk_phi_wrtSV          ->clear();
    m_trk_d0_wrtSV           ->clear();
    m_trk_z0_wrtSV           ->clear();
    m_trk_errd0_wrtSV        ->clear();
    m_trk_errz0_wrtSV        ->clear();
    m_trk_errP_wrtSV         ->clear();
    m_trk_chi2_toSV          ->clear();

    m_trk_charge             ->clear();
    m_trk_isFinal            ->clear();
    m_trk_isSelected         ->clear();
    m_trk_isAssociated       ->clear();
    m_trk_isClean            ->clear();
    m_trk_isFiltered         ->clear();
    m_trk_nPixelHits         ->clear();
    m_trk_nSCTHits           ->clear();
    m_trk_nTRTHits           ->clear();
    m_trk_nPixelBarrelLayers ->clear();
    m_trk_nPixelEndCapLayers ->clear();
    m_trk_nSCTBarrelLayers   ->clear();
    m_trk_nSCTEndCapLayers   ->clear();
    m_trk_hitPattern         ->clear();
    m_trk_dEdx               ->clear();
    m_trk_nUsedHitsdEdx      ->clear();
    m_trk_nIBLOverflowsdEdx  ->clear();
    m_trk_radiusOfFirstHit   ->clear();

    if ( m_mc ) {
      m_trk_truthProb        ->clear();
      m_trk_truthID          ->clear();
      m_trk_truthIndex       ->clear();
      m_trk_truthBarcode     ->clear();
      m_trk_truthPdgId       ->clear();
      m_trk_truthIsDesc      ->clear();
    }
  }

  // truth vertex matching
  if ( m_infoSwitch.m_truthMatching && m_mc ) {
    m_closestTruthVtx_llpDecay          ->clear();
    m_closestTruthVtx_isReconstructible ->clear();
    m_closestTruthVtx_ID                ->clear();
    m_closestTruthVtx_index             ->clear();
    m_closestTruthVtx_x                 ->clear();
    m_closestTruthVtx_y                 ->clear();
    m_closestTruthVtx_z                 ->clear();
    m_closestTruthVtx_r                 ->clear();
    m_closestTruthVtx_phi               ->clear();
    m_closestTruthVtx_barcode           ->clear();
    m_closestTruthVtx_distance          ->clear();
    m_closestTruthVtxPhysPos_ID         ->clear();
    m_closestTruthVtxPhysPos_x          ->clear();
    m_closestTruthVtxPhysPos_y          ->clear();
    m_closestTruthVtxPhysPos_z          ->clear();
    m_closestTruthVtxPhysPos_r          ->clear();
    m_closestTruthVtxPhysPos_phi        ->clear();
    m_closestTruthVtxPhysPos_distance   ->clear();

    m_matchedTruthVtx_n                 ->clear();
    m_matchedTruthVtx_llpDecay          ->clear();
    m_matchedTruthVtx_ID                ->clear();
    m_matchedTruthVtx_index             ->clear();
    m_matchedTruthVtx_x                 ->clear();
    m_matchedTruthVtx_y                 ->clear();
    m_matchedTruthVtx_z                 ->clear();
    m_matchedTruthVtx_r                 ->clear();
    m_matchedTruthVtx_pt                ->clear();
    m_matchedTruthVtx_eta               ->clear();
    m_matchedTruthVtx_phi               ->clear();
    m_matchedTruthVtx_mass              ->clear();
    m_matchedTruthVtx_barcode           ->clear();
    m_matchedTruthVtx_distance          ->clear();
    m_matchedTruthVtx_nDesc             ->clear();
    m_matchedTruthVtx_descSumPt         ->clear();
    m_matchedTruthVtx_descSumEta        ->clear();
    m_matchedTruthVtx_descSumPhi        ->clear();
    m_matchedTruthVtx_descSumM          ->clear();
    m_matchedTruthVtx_nRecoDesc         ->clear();
    m_matchedTruthVtx_recoDescSumPt     ->clear();
    m_matchedTruthVtx_recoDescSumEta    ->clear();
    m_matchedTruthVtx_recoDescSumPhi    ->clear();
    m_matchedTruthVtx_recoDescSumM      ->clear();
    m_matchedTruthVtx_massFraction      ->clear();
    m_matchedTruthVtx_multFraction      ->clear();
    m_matchedTruthVtx_cleanMassFraction ->clear();
    m_matchedTruthVtx_cleanMultFraction ->clear();
    m_matchedTruthVtx_bareMassFraction  ->clear();
    m_matchedTruthVtx_bareMultFraction  ->clear();
    m_matchedTruthVtx_matchScore        ->clear();
    m_matchedTruthVtxReprPhysPos_ID     ->clear();
    m_matchedTruthVtxReprPhysPos_x      ->clear();
    m_matchedTruthVtxReprPhysPos_y      ->clear();
    m_matchedTruthVtxReprPhysPos_z      ->clear();
    m_matchedTruthVtxReprPhysPos_r      ->clear();
    m_matchedTruthVtxReprPhysPos_phi    ->clear();
    m_matchedTruthVtx_residual_x        ->clear();
    m_matchedTruthVtx_residual_y        ->clear();
    m_matchedTruthVtx_residual_z        ->clear();
    m_matchedTruthVtx_residual_r        ->clear();
    m_matchedTruthVtx_residual_phi      ->clear();
    m_matchedTruthVtx_residual_distance ->clear();
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


void SecondaryVertexContainer :: FillSecondaryVertex ( const xAOD::Vertex* secVtx, const std::vector<std::string>& truthVtxLLPs,
						       const std::string treeName, const xAOD::Vertex* pv )
{
  if ( m_debug ) Info( "EJs::SecondaryVertexContainer::FillSecondaryVertex()", "filling branches" );

  // fill common vertex container branches
  VertexContainer::FillVertex ();

  // get vector of all (bare) tracks
  std::vector< const xAOD::TrackParticle* > allTracks;
  EJsHelper::getAllTracks( secVtx, allTracks );

  // get vector of clean tracks
  std::vector< const xAOD::TrackParticle* > cleanTracks;
  EJsHelper::getCleanTracks( secVtx, cleanTracks );

  // get vector of filtered tracks
  std::vector< const xAOD::TrackParticle* > filteredTracks;
  EJsHelper::getFilteredTracks( secVtx, filteredTracks );

  // build vectors of non-associated tracks + count selected/associated
  size_t ntrk_sel   = 0;
  size_t ntrk_assoc = 0;
  std::vector< const xAOD::TrackParticle* > allTracks_nonAssoc;
  for ( const auto& trk : allTracks ) {
    bool trkIsNonAssoc = true;
    if ( trk->isAvailable<char>( "is_selected" ) )
      if ( trk->auxdataConst<char>( "is_selected" ) )
	++ntrk_sel;
    if ( trk->isAvailable<char>( "is_associated" ) )
      if ( trk->auxdataConst<char>( "is_associated" ) ) {
	++ntrk_assoc;
	trkIsNonAssoc = false;
      }
    if ( trkIsNonAssoc ) allTracks_nonAssoc.push_back( trk );
  }
  size_t ntrk_clean_sel   = 0;
  size_t ntrk_clean_assoc = 0;
  std::vector< const xAOD::TrackParticle* > cleanTracks_nonAssoc;
  for ( const auto& cleanTrk : cleanTracks ) {
    bool cleanTrkIsNonAssoc = true;
    if ( cleanTrk->isAvailable<char>( "is_selected" ) )
      if ( cleanTrk->auxdataConst<char>( "is_selected" ) )
	++ntrk_clean_sel;
    if ( cleanTrk->isAvailable<char>( "is_associated" ) )
      if ( cleanTrk->auxdataConst<char>( "is_associated" ) ) {
	++ntrk_clean_assoc;
	cleanTrkIsNonAssoc = false;
      }
    if ( cleanTrkIsNonAssoc ) cleanTracks_nonAssoc.push_back( cleanTrk );
  }
  size_t ntrk_filt_sel   = 0;
  size_t ntrk_filt_assoc = 0;
  std::vector< const xAOD::TrackParticle* > filteredTracks_nonAssoc;
  for ( const auto& filtTrk : filteredTracks ) {
    bool filtTrkIsNonAssoc = true;
    if ( filtTrk->isAvailable<char>( "is_selected" ) )
      if ( filtTrk->auxdataConst<char>( "is_selected" ) )
	++ntrk_filt_sel;
    if ( filtTrk->isAvailable<char>( "is_associated" ) )
      if ( filtTrk->auxdataConst<char>( "is_associated" ) ) {
	++ntrk_filt_assoc;
	filtTrkIsNonAssoc = false;
      }
    if ( filtTrkIsNonAssoc ) filteredTracks_nonAssoc.push_back( filtTrk );
  }
  m_ntrk             ->push_back( allTracks.size()          );
  m_ntrk_sel         ->push_back( ntrk_sel                  );
  m_ntrk_assoc       ->push_back( ntrk_assoc                );
  m_ntrk_clean       ->push_back( cleanTracks.size()        );
  m_ntrk_clean_sel   ->push_back( ntrk_clean_sel            );
  m_ntrk_clean_assoc ->push_back( ntrk_clean_assoc          );
  m_ntrk_filt        ->push_back( filteredTracks.size()     );
  m_ntrk_filt_sel    ->push_back( ntrk_filt_sel             );
  m_ntrk_filt_assoc  ->push_back( ntrk_filt_assoc           );
  

  // re-calculate vertex kinematic variables using filtered tracks
  const TLorentzVector& sumP4       = VsiBonsai::sumP4       ( filteredTracks );
  const double          scalarSumP  = VsiBonsai::scalarSumP  ( filteredTracks );
  const double          scalarSumPt = VsiBonsai::scalarSumPt ( filteredTracks );
  const int             sumCharge   = VsiBonsai::sumCharge   ( filteredTracks );
  double minOpAngle = AlgConsts::invalidFloat;
  double maxOpAngle = AlgConsts::invalidFloat;
  double mind0      = AlgConsts::invalidFloat;
  double maxd0      = AlgConsts::invalidFloat;
  if ( filteredTracks.size() >= 2 ) {
    minOpAngle = VsiBonsai::minOpAng ( filteredTracks );
    maxOpAngle = VsiBonsai::maxOpAng ( filteredTracks );
    mind0      = VsiBonsai::mind0    ( filteredTracks );
    maxd0      = VsiBonsai::maxd0    ( filteredTracks );
  }
  // re-calculate clean vertex kinematic variables using clean tracks (no other filtering)
  const TLorentzVector& sumP4_clean       = VsiBonsai::sumP4       ( cleanTracks );
  const double          scalarSumP_clean  = VsiBonsai::scalarSumP  ( cleanTracks );
  const double          scalarSumPt_clean = VsiBonsai::scalarSumPt ( cleanTracks );
  const int             sumCharge_clean   = VsiBonsai::sumCharge   ( cleanTracks );
  const double          minOpAngle_clean  = VsiBonsai::minOpAng    ( cleanTracks );
  const double          maxOpAngle_clean  = VsiBonsai::maxOpAng    ( cleanTracks );
  const double          mind0_clean       = VsiBonsai::mind0       ( cleanTracks );
  const double          maxd0_clean       = VsiBonsai::maxd0       ( cleanTracks );
  // calculate bare vertex kinematic variables using all tracks
  const TLorentzVector& sumP4_bare       = VsiBonsai::sumP4       ( allTracks );
  const double          scalarSumP_bare  = VsiBonsai::scalarSumP  ( allTracks );
  const double          scalarSumPt_bare = VsiBonsai::scalarSumPt ( allTracks );
  const int             sumCharge_bare   = VsiBonsai::sumCharge   ( allTracks );
  const double          minOpAngle_bare  = VsiBonsai::minOpAng    ( allTracks );
  const double          maxOpAngle_bare  = VsiBonsai::maxOpAng    ( allTracks );
  const double          mind0_bare       = VsiBonsai::mind0       ( allTracks );
  const double          maxd0_bare       = VsiBonsai::maxd0       ( allTracks );

  const TVector3 pos( secVtx->x(), secVtx->y(), secVtx->z() );
  
  const double dir       = sumP4      .Vect().Dot( pos ) / sumP4      .Vect().Mag() / pos.Mag();
  const double dir_clean = sumP4_clean.Vect().Dot( pos ) / sumP4_clean.Vect().Mag() / pos.Mag();
  const double dir_bare  = sumP4_bare .Vect().Dot( pos ) / sumP4_bare .Vect().Mag() / pos.Mag();

  float mass_nonAssoc       = VsiBonsai::sumP4( filteredTracks_nonAssoc ).M();
  float mass_nonAssoc_clean = VsiBonsai::sumP4( cleanTracks_nonAssoc    ).M();
  float mass_nonAssoc_bare  = VsiBonsai::sumP4( allTracks_nonAssoc      ).M();

  float dv_distToPV = AlgConsts::invalidFloat;
  if ( pv ) dv_distToPV = ( pv->position() - secVtx->position() ).perp();

  m_ID                  ->push_back( AUXDYN( secVtx, int, "ID"                ) );
  m_index               ->push_back( AUXDYN( secVtx, int, "index"             ) );
  m_x                   ->push_back( secVtx->x()                                );
  m_y                   ->push_back( secVtx->y()                                );
  m_z                   ->push_back( secVtx->z()                                );
  m_r                   ->push_back( secVtx->position().perp()                  );
  m_pt                  ->push_back( sumP4.Pt()           / m_units             );
  m_eta                 ->push_back( sumP4.Eta()                                );
  m_phi                 ->push_back( sumP4.Phi()                                ); 
  m_mass                ->push_back( sumP4.M()            / m_units             );
  m_mass_nonAssoc       ->push_back( mass_nonAssoc        / m_units             ); // --> need to change def
  m_covariance          ->push_back( secVtx->covariance()                       );
  m_chi2                ->push_back( secVtx->chiSquared() / secVtx->numberDoF() );
  m_direction           ->push_back( dir                                        );
  m_charge              ->push_back( sumCharge                                  );
  m_H                   ->push_back( scalarSumP           / m_units             );
  m_Ht                  ->push_back( scalarSumPt          / m_units             );
  m_minOpAng            ->push_back( minOpAngle                                 );
  m_maxOpAng            ->push_back( maxOpAngle                                 );
  m_mind0               ->push_back( mind0                                      );
  m_maxd0               ->push_back( maxd0                                      );
  m_distToPV            ->push_back( dv_distToPV                                );

  m_pt_clean            ->push_back( sumP4_clean.Pt()     / m_units             );
  m_eta_clean           ->push_back( sumP4_clean.Eta()                          );
  m_phi_clean           ->push_back( sumP4_clean.Phi()                          ); 
  m_mass_clean          ->push_back( sumP4_clean.M()      / m_units             );
  m_mass_nonAssoc_clean ->push_back( mass_nonAssoc_clean  / m_units             );
  m_direction_clean     ->push_back( dir_clean                                  );
  m_charge_clean        ->push_back( sumCharge_clean                            );
  m_H_clean             ->push_back( scalarSumP_clean     / m_units             );
  m_Ht_clean            ->push_back( scalarSumPt_clean    / m_units             );
  m_minOpAng_clean      ->push_back( minOpAngle_clean                           );
  m_maxOpAng_clean      ->push_back( maxOpAngle_clean                           );
  m_mind0_clean         ->push_back( mind0_clean                                );
  m_maxd0_clean         ->push_back( maxd0_clean                                );
  
  m_pt_bare             ->push_back( sumP4_bare.Pt()      / m_units             );
  m_eta_bare            ->push_back( sumP4_bare.Eta()                           );
  m_phi_bare            ->push_back( sumP4_bare.Phi()                           ); 
  m_mass_bare           ->push_back( sumP4_bare.M()       / m_units             );
  m_mass_nonAssoc_bare  ->push_back( mass_nonAssoc_bare   / m_units             );
  m_direction_bare      ->push_back( dir_bare                                   );
  m_charge_bare         ->push_back( sumCharge_bare                             );
  m_H_bare              ->push_back( scalarSumP_bare      / m_units             );
  m_Ht_bare             ->push_back( scalarSumPt_bare     / m_units             );
  m_minOpAng_bare       ->push_back( minOpAngle_bare                            );
  m_maxOpAng_bare       ->push_back( maxOpAngle_bare                            );
  m_mind0_bare          ->push_back( mind0_bare                                 );
  m_maxd0_bare          ->push_back( maxd0_bare                                 );


  const auto twoTrackMassTuples = VsiBonsai::allTwoTracksMassCombinations ( filteredTracks );
  double minOneTrackRemovedMass = AlgConsts::invalidFloat;
  std::vector<float> twoTracksMass;
  std::vector<float> twoTracksMassRest;
  std::vector<int>   twoTracksCharge;
  if ( filteredTracks.size() >= 2 ) {
    minOneTrackRemovedMass = VsiBonsai::minOneTrackRemovedMass( filteredTracks );
    for ( const auto& tuple : twoTrackMassTuples ) {
      double mass     = std::get<0>( tuple );
      double massRest = std::get<1>( tuple );
      
      const auto* trk1 = std::get<2>( tuple ).first;
      const auto* trk2 = std::get<2>( tuple ).second;
      
      int charge = trk1->charge() + trk2->charge();
      
      twoTracksMass     .push_back( mass     / m_units );
      twoTracksMassRest .push_back( massRest / m_units );
      twoTracksCharge   .push_back( charge             );
    }
  }
  m_minOneTrackRemovedMass ->push_back( minOneTrackRemovedMass / m_units );
  m_twoTracksMass          ->push_back( twoTracksMass                    );
  m_twoTracksMassRest      ->push_back( twoTracksMassRest                );
  m_twoTracksCharge        ->push_back( twoTracksCharge                  );

  const auto   twoTrackMassTuples_clean     = VsiBonsai::allTwoTracksMassCombinations ( cleanTracks );
  const double minOneTrackRemovedMass_clean = VsiBonsai::minOneTrackRemovedMass       ( cleanTracks );
  std::vector<float> twoTracksMass_clean;
  std::vector<float> twoTracksMassRest_clean;
  std::vector<int>   twoTracksCharge_clean;
  for ( const auto& cleanTuple : twoTrackMassTuples_clean ) {
    double cleanMass     = std::get<0>( cleanTuple );
    double cleanMassRest = std::get<1>( cleanTuple );

    const auto* cleanTrk1 = std::get<2>( cleanTuple ).first;
    const auto* cleanTrk2 = std::get<2>( cleanTuple ).second;

    int cleanCharge = cleanTrk1->charge() + cleanTrk2->charge();

    twoTracksMass_clean     .push_back( cleanMass     / m_units );
    twoTracksMassRest_clean .push_back( cleanMassRest / m_units );
    twoTracksCharge_clean   .push_back( cleanCharge             );
  }
  m_minOneTrackRemovedMass_clean ->push_back( minOneTrackRemovedMass_clean / m_units );
  m_twoTracksMass_clean          ->push_back( twoTracksMass_clean                    );
  m_twoTracksMassRest_clean      ->push_back( twoTracksMassRest_clean                );
  m_twoTracksCharge_clean        ->push_back( twoTracksCharge_clean                  );
  
  const auto   twoTrackMassTuples_bare     = VsiBonsai::allTwoTracksMassCombinations ( allTracks );
  const double minOneTrackRemovedMass_bare = VsiBonsai::minOneTrackRemovedMass       ( allTracks );
  std::vector<float> twoTracksMass_bare;
  std::vector<float> twoTracksMassRest_bare;
  std::vector<int>   twoTracksCharge_bare;
  for ( const auto& bareTuple : twoTrackMassTuples_bare ) {
    double bareMass     = std::get<0>( bareTuple );
    double bareMassRest = std::get<1>( bareTuple );

    const auto* bareTrk1 = std::get<2>( bareTuple ).first;
    const auto* bareTrk2 = std::get<2>( bareTuple ).second;

    int bareCharge = bareTrk1->charge() + bareTrk2->charge();

    twoTracksMass_bare     .push_back( bareMass     / m_units );
    twoTracksMassRest_bare .push_back( bareMassRest / m_units );
    twoTracksCharge_bare   .push_back( bareCharge             );
  }
  m_minOneTrackRemovedMass_bare ->push_back( minOneTrackRemovedMass_bare / m_units );
  m_twoTracksMass_bare          ->push_back( twoTracksMass_bare                    );
  m_twoTracksMassRest_bare      ->push_back( twoTracksMassRest_bare                );
  m_twoTracksCharge_bare        ->push_back( twoTracksCharge_bare                  );


  // tracks associated to DVs
  if ( m_infoSwitch.m_tracks ) {
    recordTracks( allTracks );
  }


  // truth matching w/ TruthVertexPosition --> truthVtx/physPos matches
  if ( m_infoSwitch.m_truthMatching && m_mc ) {

    std::string closeTV_llpDecay = "";
    uint8_t     closeTV_isReco   = false;
    int         closeTV_ID       = AlgConsts::invalidInt;
    int         closeTV_index    = AlgConsts::invalidInt;
    float       closeTV_x        = AlgConsts::invalidFloat;
    float       closeTV_y        = AlgConsts::invalidFloat;
    float       closeTV_z        = AlgConsts::invalidFloat;
    float       closeTV_r        = AlgConsts::invalidFloat;
    float       closeTV_phi      = AlgConsts::invalidFloat;
    int         closeTV_barcode  = AlgConsts::invalidInt;
    float       closeTV_dist     = AlgConsts::invalidFloat;
    
    // get closest truth vertex / physical truth position
    static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLink_t> closestTruthAccess("closestTruthVertexLink");
    if ( closestTruthAccess.isAvailable( *secVtx ) ) {
      try {
	const EJsHelper::TruthVertexLink_t& closestTruthLink = closestTruthAccess( *secVtx );
	
	TVector3 closeTV_pos ( (*closestTruthLink)->x(), (*closestTruthLink)->y(), (*closestTruthLink)->z() );
	
	for ( size_t i = 0; i != truthVtxLLPs.size(); ++i )
	  if ( EJsHelper::pdgIdFuncs[truthVtxLLPs.at(i)]( (*closestTruthLink) ) )
	    closeTV_llpDecay = truthVtxLLPs.at(i);
	closeTV_isReco  = AUXDYN( (*closestTruthLink), char, "isReconstructible" );
	closeTV_ID      = AUXDYN( (*closestTruthLink), int,  "ID"                );
	closeTV_index   = AUXDYN( (*closestTruthLink), int,  "index"             );
	closeTV_x       = (*closestTruthLink)->x();
	closeTV_y       = (*closestTruthLink)->y();
	closeTV_z       = (*closestTruthLink)->z();
	closeTV_r       = (*closestTruthLink)->perp();
	closeTV_phi     = (*closestTruthLink)->phi();
	closeTV_barcode = (*closestTruthLink)->barcode();
	closeTV_dist    = ( pos - closeTV_pos ).Mag();
      } catch(...) {}
    }
    
    int      closestTruthPosID    = AUXDYN( secVtx, int,      "closestTruthVertexPhysPosID"       );
    TVector3 closestTruthPosition = AUXDYN( secVtx, TVector3, "closestTruthVertexPhysPosition"    );
    float    closestTruthPosDist  = AUXDYN( secVtx, float,    "closestTruthVertexPhysPosDistance" );

    m_closestTruthVtx_llpDecay          ->push_back( closeTV_llpDecay            );
    m_closestTruthVtx_isReconstructible ->push_back( closeTV_isReco              );
    m_closestTruthVtx_ID                ->push_back( closeTV_ID                  );
    m_closestTruthVtx_index             ->push_back( closeTV_index               );
    m_closestTruthVtx_x                 ->push_back( closeTV_x                   );
    m_closestTruthVtx_y                 ->push_back( closeTV_y                   );
    m_closestTruthVtx_z                 ->push_back( closeTV_z                   );
    m_closestTruthVtx_r                 ->push_back( closeTV_r                   );
    m_closestTruthVtx_phi               ->push_back( closeTV_phi                 );
    m_closestTruthVtx_barcode           ->push_back( closeTV_barcode             );
    m_closestTruthVtx_distance          ->push_back( closeTV_dist                );
    m_closestTruthVtxPhysPos_ID         ->push_back( closestTruthPosID           );
    m_closestTruthVtxPhysPos_x          ->push_back( closestTruthPosition.x()    );
    m_closestTruthVtxPhysPos_y          ->push_back( closestTruthPosition.y()    );
    m_closestTruthVtxPhysPos_z          ->push_back( closestTruthPosition.z()    );
    m_closestTruthVtxPhysPos_r          ->push_back( closestTruthPosition.Perp() );
    m_closestTruthVtxPhysPos_phi        ->push_back( closestTruthPosition.Phi()  );
    m_closestTruthVtxPhysPos_distance   ->push_back( closestTruthPosDist         );


    // get truth vertices / truth positions to which reco vertex is matched
    // --> truth-linked track-pt weighted matching representative physical truth position
    std::vector<const xAOD::TruthVertex*> matchedTruthVerts;
    // access matched truth vertex links
    static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLinkVector_t> matchedTruthAccess("truthVertexMatchLinks");
    if ( matchedTruthAccess.isAvailable( *secVtx ) ) {
      const EJsHelper::TruthVertexLinkVector_t& matchedTruthLinks = matchedTruthAccess( *secVtx );
      // loop over matched truth vertex links + fill vector
      for ( const auto& matchlink : matchedTruthLinks ) {
	if ( !matchlink.isValid() ) continue;
	matchedTruthVerts.push_back( *matchlink );
      }
    }
    std::vector<float>    matchedTruthVerts_score;
    std::vector<int>      matchedTruthVerts_reprTruthPosID;
    std::vector<TVector3> matchedTruthVerts_reprTruthPosition;
    std::vector<TVector3> matchedTruthVerts_residual;
    if ( secVtx->isAvailable<std::vector<float>>("truthVertexMatchScores") )
      matchedTruthVerts_score = secVtx->auxdataConst<std::vector<float>>("truthVertexMatchScores");
    if ( secVtx->isAvailable<std::vector<int>>("truthVertexMatchReprTruthPosIDs") )
      matchedTruthVerts_reprTruthPosID = secVtx->auxdataConst<std::vector<int>>("truthVertexMatchReprTruthPosIDs");
    if ( secVtx->isAvailable<std::vector<TVector3>>("truthVertexMatchReprTruthPositions") )
      matchedTruthVerts_reprTruthPosition = secVtx->auxdataConst<std::vector<TVector3>>("truthVertexMatchReprTruthPositions");
    if ( secVtx->isAvailable<std::vector<TVector3>>("truthVertexMatchResiduals") )
      matchedTruthVerts_residual = secVtx->auxdataConst<std::vector<TVector3>>("truthVertexMatchResiduals");


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
    std::vector<int>         matchTV_barcode;
    std::vector<float>       matchTV_dist;
    std::vector<int>         matchTV_nDesc;
    std::vector<float>       matchTV_descSumPt;
    std::vector<float>       matchTV_descSumEta;
    std::vector<float>       matchTV_descSumPhi;
    std::vector<float>       matchTV_descSumM;
    std::vector<int>         matchTV_nRecoDesc;
    std::vector<float>       matchTV_recoDescSumPt;
    std::vector<float>       matchTV_recoDescSumEta;
    std::vector<float>       matchTV_recoDescSumPhi;
    std::vector<float>       matchTV_recoDescSumM;
    std::vector<float>       matchTV_massFrac;
    std::vector<float>       matchTV_multFrac;
    std::vector<float>       matchTV_cleanMassFrac;
    std::vector<float>       matchTV_cleanMultFrac;
    std::vector<float>       matchTV_bareMassFrac;
    std::vector<float>       matchTV_bareMultFrac;
    std::vector<float>       matchTV_matchScore;
    std::vector<int>         matchTV_reprPosID;
    std::vector<float>       matchTV_reprPosX;
    std::vector<float>       matchTV_reprPosY;
    std::vector<float>       matchTV_reprPosZ;
    std::vector<float>       matchTV_reprPosR;
    std::vector<float>       matchTV_reprPosPhi;
    std::vector<float>       matchTV_residualX;
    std::vector<float>       matchTV_residualY;
    std::vector<float>       matchTV_residualZ;
    std::vector<float>       matchTV_residualR;
    std::vector<float>       matchTV_residualPhi;
    std::vector<float>       matchTV_residualDist;
    
    // loop over matched truth vertices + fill branches
    int match_index = 0;
    for ( const auto& match : matchedTruthVerts ) {

      TVector3 matchTV_pos ( match->x(), match->y(), match->z() );
      
      std::string llpDecayType = "";
      for ( size_t i = 0; i != truthVtxLLPs.size(); ++i )
	if ( EJsHelper::pdgIdFuncs[truthVtxLLPs.at(i)]( match ) ) llpDecayType = truthVtxLLPs.at(i);
      matchTV_llpDecay .push_back( llpDecayType                      );
      matchTV_ID       .push_back( match->auxdataConst<int>("ID")    );
      matchTV_index    .push_back( match->auxdataConst<int>("index") );
      matchTV_x        .push_back( match->x()                        );
      matchTV_y        .push_back( match->y()                        );
      matchTV_z        .push_back( match->z()                        );
      matchTV_r        .push_back( match->perp()                     );
      matchTV_eta      .push_back( match->eta()                      );
      matchTV_phi      .push_back( match->phi()                      );
      matchTV_barcode  .push_back( match->barcode()                  );
      matchTV_dist     .push_back( ( pos - matchTV_pos ).Mag()       );

      // get pt, mass from sum-p4 of outgoing particles
      std::vector<const xAOD::TruthParticle*> matchOutParts;
      for ( size_t j = 0; j != match->nOutgoingParticles(); ++j ) {
	const auto* matchOutP = match->outgoingParticle(j);
	if ( !matchOutP ) continue;
	matchOutParts .push_back( matchOutP );
      }
      const TLorentzVector& matchSumP4 = EJsHelper::truthSumP4 ( matchOutParts );
      matchTV_pt   .push_back( matchSumP4.Pt() / m_units );
      matchTV_mass .push_back( matchSumP4.M()  / m_units );

      // access reconstructible descendant links + fill set(s)
      std::set<const xAOD::TruthParticle*> matchReconstructibleDescendants;
      std::set<const xAOD::TruthParticle*> matchReconstructedDescendants;
      static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLinkVector_t>
	matchDescAccess("reconstructibleDescendantLinks");
      if ( matchDescAccess.isAvailable( *match ) ) {
	const EJsHelper::TruthParticleLinkVector_t& matchDescLinks = matchDescAccess( *match );
	for ( const auto& desclink : matchDescLinks ) {
	  if ( !desclink.isValid() ) continue;
	  bool descIsReco = AUXDYN( (*desclink), char, "isTrackMatch" );
	  matchReconstructibleDescendants.emplace( *desclink );
	  if ( descIsReco ) matchReconstructedDescendants.emplace( *desclink );
	}
      }
      const TLorentzVector& matchDesc_sumP4     = EJsHelper::truthSumP4 ( matchReconstructibleDescendants );
      const TLorentzVector& matchRecoDesc_sumP4 = EJsHelper::truthSumP4 ( matchReconstructedDescendants   );
      matchTV_nDesc          .push_back( matchReconstructibleDescendants.size() );
      matchTV_descSumPt      .push_back( matchDesc_sumP4.Pt() / m_units         );
      matchTV_descSumEta     .push_back( matchDesc_sumP4.Eta()                  );
      matchTV_descSumPhi     .push_back( matchDesc_sumP4.Phi()                  );
      matchTV_descSumM       .push_back( matchDesc_sumP4.M()  / m_units         ); 
      matchTV_nRecoDesc      .push_back( matchReconstructedDescendants.size()   );
      matchTV_recoDescSumPt  .push_back( matchRecoDesc_sumP4.Pt() / m_units     );
      matchTV_recoDescSumEta .push_back( matchRecoDesc_sumP4.Eta()              );
      matchTV_recoDescSumPhi .push_back( matchRecoDesc_sumP4.Phi()              );
      matchTV_recoDescSumM   .push_back( matchRecoDesc_sumP4.M()  / m_units     );

      matchTV_massFrac      .push_back( matchRecoDesc_sumP4.M()              / sumP4.M()                      );
      matchTV_multFrac      .push_back( matchReconstructedDescendants.size() / float( filteredTracks.size() ) );
      matchTV_cleanMassFrac .push_back( matchRecoDesc_sumP4.M()              / sumP4_clean.M()                );
      matchTV_cleanMultFrac .push_back( matchReconstructedDescendants.size() / float( cleanTracks.size()    ) );
      matchTV_bareMassFrac  .push_back( matchRecoDesc_sumP4.M()              / sumP4_bare.M()                 );
      matchTV_bareMultFrac  .push_back( matchReconstructedDescendants.size() / float( allTracks.size()      ) );

      matchTV_matchScore   .push_back( matchedTruthVerts_score             .at(match_index)        );
      matchTV_reprPosID    .push_back( matchedTruthVerts_reprTruthPosID    .at(match_index)        );
      matchTV_reprPosX     .push_back( matchedTruthVerts_reprTruthPosition .at(match_index).x()    );
      matchTV_reprPosY     .push_back( matchedTruthVerts_reprTruthPosition .at(match_index).y()    );
      matchTV_reprPosZ     .push_back( matchedTruthVerts_reprTruthPosition .at(match_index).z()    );
      matchTV_reprPosR     .push_back( matchedTruthVerts_reprTruthPosition .at(match_index).Perp() );
      matchTV_reprPosPhi   .push_back( matchedTruthVerts_reprTruthPosition .at(match_index).Phi()  );
      matchTV_residualX    .push_back( matchedTruthVerts_residual          .at(match_index).x()    );
      matchTV_residualY    .push_back( matchedTruthVerts_residual          .at(match_index).y()    );
      matchTV_residualZ    .push_back( matchedTruthVerts_residual          .at(match_index).z()    );
      matchTV_residualR    .push_back( matchedTruthVerts_residual          .at(match_index).Perp() );
      matchTV_residualPhi  .push_back( matchedTruthVerts_residual          .at(match_index).Phi()  );
      matchTV_residualDist .push_back( matchedTruthVerts_residual          .at(match_index).Mag()  );

      ++match_index;
    }

    m_matchedTruthVtx_n                 ->push_back( match_index            );
    m_matchedTruthVtx_llpDecay          ->push_back( matchTV_llpDecay       );
    m_matchedTruthVtx_ID                ->push_back( matchTV_ID             );
    m_matchedTruthVtx_index             ->push_back( matchTV_index          );
    m_matchedTruthVtx_x                 ->push_back( matchTV_x              );
    m_matchedTruthVtx_y                 ->push_back( matchTV_y              );
    m_matchedTruthVtx_z                 ->push_back( matchTV_z              );
    m_matchedTruthVtx_r                 ->push_back( matchTV_r              );
    m_matchedTruthVtx_pt                ->push_back( matchTV_pt             );
    m_matchedTruthVtx_eta               ->push_back( matchTV_eta            );
    m_matchedTruthVtx_phi               ->push_back( matchTV_phi            );
    m_matchedTruthVtx_mass              ->push_back( matchTV_mass           );
    m_matchedTruthVtx_barcode           ->push_back( matchTV_barcode        );
    m_matchedTruthVtx_distance          ->push_back( matchTV_dist           );
    m_matchedTruthVtx_nDesc             ->push_back( matchTV_nDesc          );
    m_matchedTruthVtx_descSumPt         ->push_back( matchTV_descSumPt      );
    m_matchedTruthVtx_descSumEta        ->push_back( matchTV_descSumEta     );
    m_matchedTruthVtx_descSumPhi        ->push_back( matchTV_descSumPhi     );
    m_matchedTruthVtx_descSumM          ->push_back( matchTV_descSumM       );
    m_matchedTruthVtx_nRecoDesc         ->push_back( matchTV_nRecoDesc      );
    m_matchedTruthVtx_recoDescSumPt     ->push_back( matchTV_recoDescSumPt  );
    m_matchedTruthVtx_recoDescSumEta    ->push_back( matchTV_recoDescSumEta );
    m_matchedTruthVtx_recoDescSumPhi    ->push_back( matchTV_recoDescSumPhi );
    m_matchedTruthVtx_recoDescSumM      ->push_back( matchTV_recoDescSumM   );
    m_matchedTruthVtx_massFraction      ->push_back( matchTV_massFrac       );
    m_matchedTruthVtx_multFraction      ->push_back( matchTV_multFrac       );
    m_matchedTruthVtx_cleanMassFraction ->push_back( matchTV_cleanMassFrac  );
    m_matchedTruthVtx_cleanMultFraction ->push_back( matchTV_cleanMultFrac  );
    m_matchedTruthVtx_bareMassFraction  ->push_back( matchTV_bareMassFrac   );
    m_matchedTruthVtx_bareMultFraction  ->push_back( matchTV_bareMultFrac   );
    m_matchedTruthVtx_matchScore        ->push_back( matchTV_matchScore     );
    m_matchedTruthVtxReprPhysPos_ID     ->push_back( matchTV_reprPosID      );
    m_matchedTruthVtxReprPhysPos_x      ->push_back( matchTV_reprPosX       );
    m_matchedTruthVtxReprPhysPos_y      ->push_back( matchTV_reprPosY       );
    m_matchedTruthVtxReprPhysPos_z      ->push_back( matchTV_reprPosZ       );
    m_matchedTruthVtxReprPhysPos_r      ->push_back( matchTV_reprPosR       );
    m_matchedTruthVtxReprPhysPos_phi    ->push_back( matchTV_reprPosPhi     );
    m_matchedTruthVtx_residual_x        ->push_back( matchTV_residualX      );
    m_matchedTruthVtx_residual_y        ->push_back( matchTV_residualY      );
    m_matchedTruthVtx_residual_z        ->push_back( matchTV_residualZ      );
    m_matchedTruthVtx_residual_r        ->push_back( matchTV_residualR      );
    m_matchedTruthVtx_residual_phi      ->push_back( matchTV_residualPhi    );
    m_matchedTruthVtx_residual_distance ->push_back( matchTV_residualDist   );
    
  } // end truth matching switch


  // jet matching (jets to which DVs are dR-matched)
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    std::string jet_str = treeName;
    if ( treeName == "nominal" ) jet_str = "";
    uint8_t isTruthJetMatch  = false;
    if ( secVtx->isAvailable<char>("isMatchedToTruthJet") )
      isTruthJetMatch  = secVtx->auxdataConst<char>("isMatchedToTruthJet");
    uint8_t isDarkJetMatch   = false;
    if ( secVtx->isAvailable<char>("isMatchedToDarkJet")  )
      isDarkJetMatch   = secVtx->auxdataConst<char>("isMatchedToDarkJet");
    uint8_t isEMTopoJetMatch = false;
    std::string emtopo_str   = "";
    if ( secVtx->isAvailable<char>("isMatchedToRecoJet_EMTopo" + jet_str) ) {
      isEMTopoJetMatch = secVtx->auxdataConst<char>("isMatchedToRecoJet_EMTopo" + jet_str);
      emtopo_str       = jet_str;
    }
    else if ( secVtx->isAvailable<char>("isMatchedToRecoJet_EMTopo") )
      isEMTopoJetMatch = secVtx->auxdataConst<char>("isMatchedToRecoJet_EMTopo");
    uint8_t isPFlowJetMatch  = false;
    std::string pflow_str    = "";
    if ( secVtx->isAvailable<char>("isMatchedToRecoJet_PFlow" + jet_str) ) {
      isPFlowJetMatch  = secVtx->auxdataConst<char>("isMatchedToRecoJet_PFlow" + jet_str);
      pflow_str        = jet_str;
    }
    else if ( secVtx->isAvailable<char>("isMatchedToRecoJet_PFlow") )
      isPFlowJetMatch  = secVtx->auxdataConst<char>("isMatchedToRecoJet_PFlow");

    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      m_truthJetMatch          ->push_back( isTruthJetMatch                               );
      m_truthJetMatch_ID       ->push_back( AUXDYN( secVtx, int,   "truthJetMatchID"    ) );
      m_truthJetMatch_index    ->push_back( AUXDYN( secVtx, int,   "truthJetMatchIndex" ) );
      m_truthJetMatch_dR       ->push_back( AUXDYN( secVtx, float, "truthJetMatchDR"    ) );
      m_darkJetMatch           ->push_back( isDarkJetMatch                                );
      m_darkJetMatch_ID        ->push_back( AUXDYN( secVtx, int,   "darkJetMatchID"     ) );
      m_darkJetMatch_index     ->push_back( AUXDYN( secVtx, int,   "darkJetMatchIndex"  ) );
      m_darkJetMatch_dR        ->push_back( AUXDYN( secVtx, float, "darkJetMatchDR"     ) );
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	m_emtopoJetMatch       ->push_back( isEMTopoJetMatch                                                 );
	m_emtopoJetMatch_ID    ->push_back( AUXDYN( secVtx, int,   "recoJetMatchID_EMTopo"    + emtopo_str ) );
	m_emtopoJetMatch_index ->push_back( AUXDYN( secVtx, int,   "recoJetMatchIndex_EMTopo" + emtopo_str ) );
	m_emtopoJetMatch_dR    ->push_back( AUXDYN( secVtx, float, "recoJetMatchDR_EMTopo"    + emtopo_str ) );
      }
      if ( m_doPFlow  ) {
	m_pflowJetMatch        ->push_back( isPFlowJetMatch                                                  );
	m_pflowJetMatch_ID     ->push_back( AUXDYN( secVtx, int,   "recoJetMatchID_PFlow"     + pflow_str  ) );
	m_pflowJetMatch_index  ->push_back( AUXDYN( secVtx, int,   "recoJetMatchIndex_PFlow"  + pflow_str  ) );
	m_pflowJetMatch_dR     ->push_back( AUXDYN( secVtx, float, "recoJetMatchDR_PFlow"     + pflow_str  ) );
      }
    }   
  }


  

}


void SecondaryVertexContainer :: recordTracks ( const std::vector<const xAOD::TrackParticle*>& tracks )
{
  if ( m_debug ) Info( "EJs::SecondaryVertexContainer::recordTracks()", "filling vertex track branches" );

  std::vector<int>      trk_ID;
  std::vector<int>      trk_index;
  std::vector<float>    trk_qOverP;
  std::vector<float>    trk_theta;
  std::vector<float>    trk_vz;
  std::vector<float>    trk_E;
  std::vector<float>    trk_M;
  std::vector<float>    trk_pt;
  std::vector<float>    trk_eta;
  std::vector<float>    trk_phi;
  std::vector<float>    trk_d0;
  std::vector<float>    trk_z0;
  std::vector<float>    trk_errd0;
  std::vector<float>    trk_errz0;
  std::vector<float>    trk_chi2;

  std::vector<float>    trk_pt_wrtSV;
  std::vector<float>    trk_eta_wrtSV;
  std::vector<float>    trk_phi_wrtSV;
  std::vector<float>    trk_d0_wrtSV;
  std::vector<float>    trk_z0_wrtSV;
  std::vector<float>    trk_errd0_wrtSV;
  std::vector<float>    trk_errz0_wrtSV;
  std::vector<float>    trk_errP_wrtSV;
  std::vector<float>    trk_chi2_toSV;

  std::vector<int>      trk_charge;
  std::vector<uint8_t>  trk_isFinal;
  std::vector<uint8_t>  trk_isSelected;
  std::vector<uint8_t>  trk_isAssociated;
  std::vector<uint8_t>  trk_isClean;
  std::vector<uint8_t>  trk_isFiltered;
  std::vector<uint8_t>  trk_nPixelHits;
  std::vector<uint8_t>  trk_nSCTHits;
  std::vector<uint8_t>  trk_nTRTHits;
  std::vector<uint8_t>  trk_nPixelBarrelLayers;
  std::vector<uint8_t>  trk_nPixelEndCapLayers;
  std::vector<uint8_t>  trk_nSCTBarrelLayers;
  std::vector<uint8_t>  trk_nSCTEndCapLayers;
  std::vector<uint32_t> trk_hitPattern;
  std::vector<float>    trk_dEdx;
  std::vector<uint8_t>  trk_nUsedHitsdEdx;
  std::vector<uint8_t>  trk_nIBLOverflowsdEdx;
  std::vector<float>    trk_radiusOfFirstHit;

  std::vector<float>    trk_truthProb;
  std::vector<int>      trk_truthID;
  std::vector<int>      trk_truthIndex;
  std::vector<int>      trk_truthBarcode;
  std::vector<int>      trk_truthPdgId;
  std::vector<uint8_t>  trk_truthIsDesc;

  for ( const auto& trk : tracks ) {
    if ( !trk ) continue;

    trk_ID     .push_back( AUXDYN( trk, int, "ID"                ) );
    trk_index  .push_back( AUXDYN( trk, int, "index"             ) );
    trk_qOverP .push_back( trk->qOverP()                           );
    trk_theta  .push_back( trk->theta()                            );
    trk_vz     .push_back( trk->vz()                               );
    trk_E      .push_back( trk->e()  / m_units                     );
    trk_M      .push_back( trk->m()  / m_units                     );
    trk_pt     .push_back( trk->pt() / m_units                     );
    trk_eta    .push_back( trk->eta()                              );
    trk_phi    .push_back( trk->phi()                              );
    trk_d0     .push_back( trk->d0()                               );
    trk_z0     .push_back( trk->z0()                               );
    trk_errd0  .push_back( trk->definingParametersCovMatrix()(0,0) );
    trk_errz0  .push_back( trk->definingParametersCovMatrix()(1,1) );
    trk_chi2   .push_back( trk->chiSquared() / trk->numberDoF()    );

    trk_pt_wrtSV    .push_back( AUXDYN( trk, float, "pt_wrtSV"    ) / m_units );
    trk_eta_wrtSV   .push_back( AUXDYN( trk, float, "eta_wrtSV"   )           );
    trk_phi_wrtSV   .push_back( AUXDYN( trk, float, "phi_wrtSV"   )           );
    trk_d0_wrtSV    .push_back( AUXDYN( trk, float, "d0_wrtSV"    )           );
    trk_z0_wrtSV    .push_back( AUXDYN( trk, float, "z0_wrtSV"    )           );
    trk_errd0_wrtSV .push_back( AUXDYN( trk, float, "errd0_wrtSV" )           );
    trk_errz0_wrtSV .push_back( AUXDYN( trk, float, "errz0_wrtSV" )           );
    trk_errP_wrtSV  .push_back( AUXDYN( trk, float, "errP_wrtSV"  )           );
    trk_chi2_toSV   .push_back( AUXDYN( trk, float, "chi2_toSV"   )           );

    trk_charge       .push_back( trk->charge()                         );
    trk_isFinal      .push_back( AUXDYN( trk, char, "is_svtrk_final" ) );
    trk_isSelected   .push_back( AUXDYN( trk, char, "is_selected"    ) );
    trk_isAssociated .push_back( AUXDYN( trk, char, "is_associated"  ) );
    trk_isClean      .push_back( AUXDYN( trk, char, "isClean"        ) );
    trk_isFiltered   .push_back( AUXDYN( trk, char, "isFiltered"     ) );

    uint8_t nPixelHits = 0;
    uint8_t nSCTHits   = 0;
    uint8_t nTRTHits   = 0;
    float   pixeldEdx  = 0;
    trk->summaryValue ( nPixelHits, xAOD::numberOfPixelHits );
    trk->summaryValue ( nSCTHits,   xAOD::numberOfSCTHits   );
    trk->summaryValue ( nTRTHits,   xAOD::numberOfTRTHits   );
    trk->summaryValue ( pixeldEdx,  xAOD::pixeldEdx         );

    uint8_t nPixelBarrelLayers = VsiTool::nPixelBarrelLayers ( trk->hitPattern() );
    uint8_t nPixelEndCapLayers = VsiTool::nPixelEndCapLayers ( trk->hitPattern() );
    uint8_t nSCTBarrelLayers   = VsiTool::nSctBarrelLayers   ( trk->hitPattern() );
    uint8_t nSCTEndCapLayers   = VsiTool::nSctEndCapLayers   ( trk->hitPattern() );
    
    trk_nPixelHits         .push_back( nPixelHits                      );
    trk_nSCTHits           .push_back( nSCTHits                        );
    trk_nTRTHits           .push_back( nTRTHits                        );
    trk_nPixelBarrelLayers .push_back( nPixelBarrelLayers              );
    trk_nPixelEndCapLayers .push_back( nPixelEndCapLayers              );
    trk_nSCTBarrelLayers   .push_back( nSCTBarrelLayers                );
    trk_nSCTEndCapLayers   .push_back( nSCTEndCapLayers                );
    trk_hitPattern         .push_back( trk->hitPattern()               );
    trk_dEdx               .push_back( pixeldEdx                       );
    trk_nUsedHitsdEdx      .push_back( trk->numberOfUsedHitsdEdx()     );
    trk_nIBLOverflowsdEdx  .push_back( trk->numberOfIBLOverflowsdEdx() );
    trk_radiusOfFirstHit   .push_back( trk->radiusOfFirstHit()         );

    const xAOD::TruthParticle* truthPart = 0;
    static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLink_t> truthAccess("truthParticleLink");
    if ( truthAccess.isAvailable( *trk ) ) {
      try {
	const EJsHelper::TruthParticleLink_t& truthPartLink = truthAccess( *trk );
	truthPart = *truthPartLink;
      } catch(...) {}
    }
    if ( truthPart ) {
      trk_truthProb    .push_back( trk->auxdataConst<float>("truthMatchProbability")        );
      trk_truthID      .push_back( AUXDYN( truthPart, int, "ID"                           ) );
      trk_truthIndex   .push_back( AUXDYN( truthPart, int, "index"                        ) );
      trk_truthBarcode .push_back( truthPart->barcode()                                     );
      trk_truthPdgId   .push_back( truthPart->pdgId()                                       );
      trk_truthIsDesc  .push_back( AUXDYN( truthPart, char, "isReconstructibleDescendant" ) );
    }
    else {
      trk_truthProb    .push_back( AlgConsts::invalidFloat    );
      trk_truthID      .push_back( AlgConsts::invalidInt      );
      trk_truthIndex   .push_back( AlgConsts::invalidInt      );
      trk_truthBarcode .push_back( AlgConsts::invalidInt      );
      trk_truthPdgId   .push_back( AlgConsts::invalidInt      );
      trk_truthIsDesc  .push_back( AlgConsts::invalidUnsigned );
    }
    
  }

  m_trk_ID     ->push_back( trk_ID     );
  m_trk_index  ->push_back( trk_index  );
  m_trk_qOverP ->push_back( trk_qOverP );
  m_trk_theta  ->push_back( trk_theta  );
  m_trk_vz     ->push_back( trk_vz     );
  m_trk_E      ->push_back( trk_E      );
  m_trk_M      ->push_back( trk_M      );
  m_trk_pt     ->push_back( trk_pt     );
  m_trk_eta    ->push_back( trk_eta    );
  m_trk_phi    ->push_back( trk_phi    );
  m_trk_d0     ->push_back( trk_d0     );
  m_trk_z0     ->push_back( trk_z0     );
  m_trk_errd0  ->push_back( trk_errd0  );
  m_trk_errz0  ->push_back( trk_errz0  );
  m_trk_chi2   ->push_back( trk_chi2   );

  m_trk_pt_wrtSV    ->push_back( trk_pt_wrtSV    );
  m_trk_eta_wrtSV   ->push_back( trk_eta_wrtSV   );
  m_trk_phi_wrtSV   ->push_back( trk_phi_wrtSV   );
  m_trk_d0_wrtSV    ->push_back( trk_d0_wrtSV    );
  m_trk_z0_wrtSV    ->push_back( trk_z0_wrtSV    );
  m_trk_errd0_wrtSV ->push_back( trk_errd0_wrtSV );
  m_trk_errz0_wrtSV ->push_back( trk_errz0_wrtSV );
  m_trk_errP_wrtSV  ->push_back( trk_errP_wrtSV  );
  m_trk_chi2_toSV   ->push_back( trk_chi2_toSV   );

  m_trk_charge             ->push_back( trk_charge             );
  m_trk_isFinal            ->push_back( trk_isFinal            );
  m_trk_isSelected         ->push_back( trk_isSelected         );
  m_trk_isAssociated       ->push_back( trk_isAssociated       );
  m_trk_isClean            ->push_back( trk_isClean            );
  m_trk_isFiltered         ->push_back( trk_isFiltered         );
  m_trk_nPixelHits         ->push_back( trk_nPixelHits         );
  m_trk_nSCTHits           ->push_back( trk_nSCTHits           );
  m_trk_nTRTHits           ->push_back( trk_nTRTHits           );
  m_trk_nPixelBarrelLayers ->push_back( trk_nPixelBarrelLayers );
  m_trk_nPixelEndCapLayers ->push_back( trk_nPixelEndCapLayers );
  m_trk_nSCTBarrelLayers   ->push_back( trk_nSCTBarrelLayers   );
  m_trk_nSCTEndCapLayers   ->push_back( trk_nSCTEndCapLayers   );
  m_trk_hitPattern         ->push_back( trk_hitPattern         );
  m_trk_dEdx               ->push_back( trk_dEdx               );
  m_trk_nUsedHitsdEdx      ->push_back( trk_nUsedHitsdEdx      );
  m_trk_nIBLOverflowsdEdx  ->push_back( trk_nIBLOverflowsdEdx  );
  m_trk_radiusOfFirstHit   ->push_back( trk_radiusOfFirstHit   );

  if ( m_mc ) {
    m_trk_truthProb    ->push_back( trk_truthProb    );
    m_trk_truthID      ->push_back( trk_truthID      );
    m_trk_truthIndex   ->push_back( trk_truthIndex   );
    m_trk_truthBarcode ->push_back( trk_truthBarcode );
    m_trk_truthPdgId   ->push_back( trk_truthPdgId   );
    m_trk_truthIsDesc  ->push_back( trk_truthIsDesc  );
  }

} // end recordTracks
