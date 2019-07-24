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

  m_ID            = new std::vector<int>;
  m_index         = new std::vector<int>;
  m_x             = new std::vector<float>;
  m_y             = new std::vector<float>;
  m_z             = new std::vector<float>;
  m_r             = new std::vector<float>;
  m_pt            = new std::vector<float>;
  m_eta           = new std::vector<float>;
  m_phi           = new std::vector<float>;
  m_mass          = new std::vector<float>;
  m_mass_nonAssoc = new std::vector<float>;
  m_covariance    = new std::vector<std::vector<float>>;
  m_chi2          = new std::vector<float>;
  m_direction     = new std::vector<float>;
  m_charge        = new std::vector<int>;
  m_H             = new std::vector<float>;
  m_Ht            = new std::vector<float>;
  m_minOpAng      = new std::vector<float>;
  m_maxOpAng      = new std::vector<float>;
  m_mind0         = new std::vector<float>;
  m_maxd0         = new std::vector<float>;
  m_distToPV      = new std::vector<float>;
  
  m_minOneTrackRemovedMass = new std::vector<float>;
  m_twoTracksMass          = new std::vector<std::vector<float>>;
  m_twoTracksMassRest      = new std::vector<std::vector<float>>;
  m_twoTracksCharge        = new std::vector<std::vector<int>>;
  
  m_ntrk       = new std::vector<uint32_t>;
  m_ntrk_sel   = new std::vector<uint32_t>;
  m_ntrk_assoc = new std::vector<uint32_t>;

  // tracks
  if ( m_infoSwitch.m_tracks ) {
    m_trk_ID     = new std::vector<std::vector<int>>;
    m_trk_index  = new std::vector<std::vector<int>>;
    m_trk_qOverP = new std::vector<std::vector<float>>;
    m_trk_theta  = new std::vector<std::vector<float>>;
    m_trk_vz     = new std::vector<std::vector<float>>;
    m_trk_E      = new std::vector<std::vector<float>>;
    m_trk_M      = new std::vector<std::vector<float>>;
    m_trk_pt     = new std::vector<std::vector<float>>;
    m_trk_eta    = new std::vector<std::vector<float>>;
    m_trk_phi    = new std::vector<std::vector<float>>;
    m_trk_d0     = new std::vector<std::vector<float>>;
    m_trk_z0     = new std::vector<std::vector<float>>;
    m_trk_errd0  = new std::vector<std::vector<float>>;
    m_trk_errz0  = new std::vector<std::vector<float>>;
    m_trk_chi2   = new std::vector<std::vector<float>>;

    m_trk_pt_wrtSV    = new std::vector<std::vector<float>>;
    m_trk_eta_wrtSV   = new std::vector<std::vector<float>>;
    m_trk_phi_wrtSV   = new std::vector<std::vector<float>>;
    m_trk_d0_wrtSV    = new std::vector<std::vector<float>>;
    m_trk_z0_wrtSV    = new std::vector<std::vector<float>>;
    m_trk_errd0_wrtSV = new std::vector<std::vector<float>>;
    m_trk_errz0_wrtSV = new std::vector<std::vector<float>>;
    m_trk_errP_wrtSV  = new std::vector<std::vector<float>>;
    m_trk_chi2_toSV   = new std::vector<std::vector<float>>;

    m_trk_charge             = new std::vector<std::vector<int>>;
    m_trk_isFinal            = new std::vector<std::vector<uint8_t>>;
    m_trk_isSelected         = new std::vector<std::vector<uint8_t>>;
    m_trk_isAssociated       = new std::vector<std::vector<uint8_t>>;
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
      m_trk_truthProb    = new std::vector<std::vector<float>>;
      m_trk_truthID      = new std::vector<std::vector<int>>;
      m_trk_truthIndex   = new std::vector<std::vector<int>>;
      m_trk_truthBarcode = new std::vector<std::vector<int>>;
      m_trk_truthPdgId   = new std::vector<std::vector<int>>;
    }
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
  
  delete m_minOneTrackRemovedMass;
  delete m_twoTracksMass;
  delete m_twoTracksMassRest;
  delete m_twoTracksCharge;
  
  delete m_ntrk;
  delete m_ntrk_sel;
  delete m_ntrk_assoc;

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
    }
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

  connectBranch<int>                ( tree, "ID",            &m_ID            );
  connectBranch<int>                ( tree, "index",         &m_index         );
  connectBranch<float>              ( tree, "x",             &m_x             );
  connectBranch<float>              ( tree, "y",             &m_y             );
  connectBranch<float>              ( tree, "z",             &m_z             );
  connectBranch<float>              ( tree, "r",             &m_r             );
  connectBranch<float>              ( tree, "pt",            &m_pt            );
  connectBranch<float>              ( tree, "eta",           &m_eta           );
  connectBranch<float>              ( tree, "phi",           &m_phi           );
  connectBranch<float>              ( tree, "mass",          &m_mass          );
  connectBranch<float>              ( tree, "mass_nonAssoc", &m_mass_nonAssoc );
  connectBranch<std::vector<float>> ( tree, "covariance",    &m_covariance    );
  connectBranch<float>              ( tree, "chi2",          &m_chi2          );
  connectBranch<float>              ( tree, "direction",     &m_direction     );
  connectBranch<int>                ( tree, "charge",        &m_charge        );
  connectBranch<float>              ( tree, "H",             &m_H             );
  connectBranch<float>              ( tree, "Ht",            &m_Ht            );
  connectBranch<float>              ( tree, "minOpAng",      &m_minOpAng      );
  connectBranch<float>              ( tree, "maxOpAng",      &m_maxOpAng      );
  connectBranch<float>              ( tree, "mind0",         &m_mind0         );
  connectBranch<float>              ( tree, "maxd0",         &m_maxd0         );
  connectBranch<float>              ( tree, "distToPV",      &m_distToPV      );
  
  connectBranch<float>              ( tree, "minOneTrackRemovedMass", &m_minOneTrackRemovedMass );
  connectBranch<std::vector<float>> ( tree, "twoTracksMass",          &m_twoTracksMass          );
  connectBranch<std::vector<float>> ( tree, "twoTracksMassRest",      &m_twoTracksMassRest      );
  connectBranch<std::vector<int>>   ( tree, "twoTracksCharge",        &m_twoTracksCharge        );
  
  connectBranch<uint32_t> ( tree, "ntrk",       &m_ntrk       );
  connectBranch<uint32_t> ( tree, "ntrk_sel",   &m_ntrk_sel   );
  connectBranch<uint32_t> ( tree, "ntrk_assoc", &m_ntrk_assoc );

  // tracks
  if ( m_infoSwitch.m_tracks ) {
    connectBranch<std::vector<int>>   ( tree, "trk_ID",     &m_trk_ID     );
    connectBranch<std::vector<int>>   ( tree, "trk_index",  &m_trk_index  );
    connectBranch<std::vector<float>> ( tree, "trk_qOverP", &m_trk_qOverP );
    connectBranch<std::vector<float>> ( tree, "trk_theta",  &m_trk_theta  );
    connectBranch<std::vector<float>> ( tree, "trk_vz",     &m_trk_vz     );
    connectBranch<std::vector<float>> ( tree, "trk_E",      &m_trk_E      );
    connectBranch<std::vector<float>> ( tree, "trk_M",      &m_trk_M      );
    connectBranch<std::vector<float>> ( tree, "trk_pt",     &m_trk_pt     );
    connectBranch<std::vector<float>> ( tree, "trk_eta",    &m_trk_eta    );
    connectBranch<std::vector<float>> ( tree, "trk_phi",    &m_trk_phi    );
    connectBranch<std::vector<float>> ( tree, "trk_d0",     &m_trk_d0     );
    connectBranch<std::vector<float>> ( tree, "trk_z0",     &m_trk_z0     );
    connectBranch<std::vector<float>> ( tree, "trk_errd0",  &m_trk_errd0  );
    connectBranch<std::vector<float>> ( tree, "trk_errz0",  &m_trk_errz0  );
    connectBranch<std::vector<float>> ( tree, "trk_chi2",   &m_trk_chi2   );

    connectBranch<std::vector<float>> ( tree, "trk_pt_wrtSV",    &m_trk_pt_wrtSV    );
    connectBranch<std::vector<float>> ( tree, "trk_eta_wrtSV",   &m_trk_eta_wrtSV   );
    connectBranch<std::vector<float>> ( tree, "trk_phi_wrtSV",   &m_trk_phi_wrtSV   );
    connectBranch<std::vector<float>> ( tree, "trk_d0_wrtSV",    &m_trk_d0_wrtSV    );
    connectBranch<std::vector<float>> ( tree, "trk_z0_wrtSV",    &m_trk_z0_wrtSV    );
    connectBranch<std::vector<float>> ( tree, "trk_errd0_wrtSV", &m_trk_errd0_wrtSV );
    connectBranch<std::vector<float>> ( tree, "trk_errz0_wrtSV", &m_trk_errz0_wrtSV );
    connectBranch<std::vector<float>> ( tree, "trk_errP_wrtSV",  &m_trk_errP_wrtSV  );
    connectBranch<std::vector<float>> ( tree, "trk_chi2_toSV",   &m_trk_chi2_toSV   );

    connectBranch<std::vector<int>>      ( tree, "trk_charge",             &m_trk_charge             );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_isFinal",            &m_trk_isFinal            );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_isSelected",         &m_trk_isSelected         );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_isAssociated",       &m_trk_isAssociated       );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_nPixelHits",         &m_trk_nPixelHits         );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_nSCTHits",           &m_trk_nSCTHits           );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_nTRTHits",           &m_trk_nTRTHits           );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_nPixelBarrelLayers", &m_trk_nPixelBarrelLayers );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_nPixelEndCapLayers", &m_trk_nPixelEndCapLayers );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_nSCTBarrelLayers",   &m_trk_nSCTBarrelLayers   );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_nSCTEndCapLayers",   &m_trk_nSCTEndCapLayers   );
    connectBranch<std::vector<uint32_t>> ( tree, "trk_hitPattern",         &m_trk_hitPattern         );
    connectBranch<std::vector<float>>    ( tree, "trk_dEdx",               &m_trk_dEdx               );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_nUsedHitsdEdx",      &m_trk_nUsedHitsdEdx      );
    connectBranch<std::vector<uint8_t>>  ( tree, "trk_nIBLOverflowsdEdx",  &m_trk_nIBLOverflowsdEdx  );
    connectBranch<std::vector<float>>    ( tree, "trk_radiusOfFirstHit",   &m_trk_radiusOfFirstHit   );

    // truth matched to tracks
    if ( m_mc ) {
      connectBranch<std::vector<float>> ( tree, "trk_truthProb",    &m_trk_truthProb    );
      connectBranch<std::vector<int>>   ( tree, "trk_truthID",      &m_trk_truthID      );
      connectBranch<std::vector<int>>   ( tree, "trk_truthIndex",   &m_trk_truthIndex   );
      connectBranch<std::vector<int>>   ( tree, "trk_truthBarcode", &m_trk_truthBarcode );
      connectBranch<std::vector<int>>   ( tree, "trk_truthPdgId",   &m_trk_truthPdgId   );
    }
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

  setBranch<int>                ( tree, "ID",            m_ID            );
  setBranch<int>                ( tree, "index",         m_index         );
  setBranch<float>              ( tree, "x",             m_x             );
  setBranch<float>              ( tree, "y",             m_y             );
  setBranch<float>              ( tree, "z",             m_z             );
  setBranch<float>              ( tree, "r",             m_r             );
  setBranch<float>              ( tree, "pt",            m_pt            );
  setBranch<float>              ( tree, "eta",           m_eta           );
  setBranch<float>              ( tree, "phi",           m_phi           );
  setBranch<float>              ( tree, "mass",          m_mass          );
  setBranch<float>              ( tree, "mass_nonAssoc", m_mass_nonAssoc );
  setBranch<std::vector<float>> ( tree, "covariance",    m_covariance    );
  setBranch<float>              ( tree, "chi2",          m_chi2          );
  setBranch<float>              ( tree, "direction",     m_direction     );
  setBranch<int>                ( tree, "charge",        m_charge        );
  setBranch<float>              ( tree, "H",             m_H             );
  setBranch<float>              ( tree, "Ht",            m_Ht            );
  setBranch<float>              ( tree, "minOpAng",      m_minOpAng      );
  setBranch<float>              ( tree, "maxOpAng",      m_maxOpAng      );
  setBranch<float>              ( tree, "mind0",         m_mind0         );
  setBranch<float>              ( tree, "maxd0",         m_maxd0         );
  setBranch<float>              ( tree, "distToPV",      m_distToPV      );

  setBranch<float>              ( tree, "minOneTrackRemovedMass", m_minOneTrackRemovedMass );
  setBranch<std::vector<float>> ( tree, "twoTracksMass",          m_twoTracksMass          );
  setBranch<std::vector<float>> ( tree, "twoTracksMassRest",      m_twoTracksMassRest      );
  setBranch<std::vector<int>>   ( tree, "twoTracksCharge",        m_twoTracksCharge        );

  setBranch<uint32_t> ( tree, "ntrk",       m_ntrk       );
  setBranch<uint32_t> ( tree, "ntrk_sel",   m_ntrk_sel   );
  setBranch<uint32_t> ( tree, "ntrk_assoc", m_ntrk_assoc );

  // tracks
  if ( m_infoSwitch.m_tracks ) {
    setBranch<std::vector<int>>   ( tree, "trk_ID",     m_trk_ID     );
    setBranch<std::vector<int>>   ( tree, "trk_index",  m_trk_index  );
    setBranch<std::vector<float>> ( tree, "trk_qOverP", m_trk_qOverP );
    setBranch<std::vector<float>> ( tree, "trk_theta",  m_trk_theta  );
    setBranch<std::vector<float>> ( tree, "trk_vz",     m_trk_vz     );
    setBranch<std::vector<float>> ( tree, "trk_E",      m_trk_E      );
    setBranch<std::vector<float>> ( tree, "trk_M",      m_trk_M      );
    setBranch<std::vector<float>> ( tree, "trk_pt",     m_trk_pt     );
    setBranch<std::vector<float>> ( tree, "trk_eta",    m_trk_eta    );
    setBranch<std::vector<float>> ( tree, "trk_phi",    m_trk_phi    );
    setBranch<std::vector<float>> ( tree, "trk_d0",     m_trk_d0     );
    setBranch<std::vector<float>> ( tree, "trk_z0",     m_trk_z0     );
    setBranch<std::vector<float>> ( tree, "trk_errd0",  m_trk_errd0  );
    setBranch<std::vector<float>> ( tree, "trk_errz0",  m_trk_errz0  );
    setBranch<std::vector<float>> ( tree, "trk_chi2",   m_trk_chi2   );

    setBranch<std::vector<float>> ( tree, "trk_pt_wrtSV",    m_trk_pt_wrtSV    );
    setBranch<std::vector<float>> ( tree, "trk_eta_wrtSV",   m_trk_eta_wrtSV   );
    setBranch<std::vector<float>> ( tree, "trk_phi_wrtSV",   m_trk_phi_wrtSV   );
    setBranch<std::vector<float>> ( tree, "trk_d0_wrtSV",    m_trk_d0_wrtSV    );
    setBranch<std::vector<float>> ( tree, "trk_z0_wrtSV",    m_trk_z0_wrtSV    );
    setBranch<std::vector<float>> ( tree, "trk_errd0_wrtSV", m_trk_errd0_wrtSV );
    setBranch<std::vector<float>> ( tree, "trk_errz0_wrtSV", m_trk_errz0_wrtSV );
    setBranch<std::vector<float>> ( tree, "trk_errP_wrtSV",  m_trk_errP_wrtSV  );
    setBranch<std::vector<float>> ( tree, "trk_chi2_toSV",   m_trk_chi2_toSV   );

    setBranch<std::vector<int>>      ( tree, "trk_charge",             m_trk_charge             );
    setBranch<std::vector<uint8_t>>  ( tree, "trk_isFinal",            m_trk_isFinal            );
    setBranch<std::vector<uint8_t>>  ( tree, "trk_isSelected",         m_trk_isSelected         );
    setBranch<std::vector<uint8_t>>  ( tree, "trk_isAssociated",       m_trk_isAssociated       );
    setBranch<std::vector<uint8_t>>  ( tree, "trk_nPixelBarrelLayers", m_trk_nPixelBarrelLayers );
    setBranch<std::vector<uint8_t>>  ( tree, "trk_nPixelEndCapLayers", m_trk_nPixelEndCapLayers );
    setBranch<std::vector<uint8_t>>  ( tree, "trk_nSCTBarrelLayers",   m_trk_nSCTBarrelLayers   );
    setBranch<std::vector<uint8_t>>  ( tree, "trk_nSCTEndCapLayers",   m_trk_nSCTEndCapLayers   );
    setBranch<std::vector<uint32_t>> ( tree, "trk_hitPattern",         m_trk_hitPattern         );
    setBranch<std::vector<float>>    ( tree, "trk_dEdx",               m_trk_dEdx               );
    setBranch<std::vector<uint8_t>>  ( tree, "trk_nUsedHitsdEdx",      m_trk_nUsedHitsdEdx      );
    setBranch<std::vector<uint8_t>>  ( tree, "trk_nIBLOverflowsdEdx",  m_trk_nIBLOverflowsdEdx  );
    setBranch<std::vector<float>>    ( tree, "trk_radiusOfFirstHit",   m_trk_radiusOfFirstHit   );

    if ( m_mc ) {
      setBranch<std::vector<float>> ( tree, "trk_truthProb",    m_trk_truthProb    );
      setBranch<std::vector<int>>   ( tree, "trk_truthID",      m_trk_truthID      );
      setBranch<std::vector<int>>   ( tree, "trk_truthIndex",   m_trk_truthIndex   );
      setBranch<std::vector<int>>   ( tree, "trk_truthBarcode", m_trk_truthBarcode );
      setBranch<std::vector<int>>   ( tree, "trk_truthPdgId",   m_trk_truthPdgId   );
    }
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

  m_ID            ->clear();
  m_index         ->clear();
  m_x             ->clear();
  m_y             ->clear();
  m_z             ->clear();
  m_r             ->clear();
  m_pt            ->clear();
  m_eta           ->clear();
  m_phi           ->clear();
  m_mass          ->clear();
  m_mass_nonAssoc ->clear();
  m_covariance    ->clear();
  m_chi2          ->clear();
  m_direction     ->clear();
  m_charge        ->clear();
  m_H             ->clear();
  m_Ht            ->clear();
  m_minOpAng      ->clear();
  m_maxOpAng      ->clear();
  m_mind0         ->clear();
  m_maxd0         ->clear();
  m_distToPV      ->clear();
  
  m_minOneTrackRemovedMass ->clear();
  m_twoTracksMass          ->clear();
  m_twoTracksMassRest      ->clear();
  m_twoTracksCharge        ->clear();

  m_ntrk       ->clear();
  m_ntrk_sel   ->clear();
  m_ntrk_assoc ->clear();

  // tracks
  if ( m_infoSwitch.m_tracks ) {
    m_trk_ID     ->clear();
    m_trk_index  ->clear();
    m_trk_qOverP ->clear();
    m_trk_theta  ->clear();
    m_trk_vz     ->clear();
    m_trk_E      ->clear();
    m_trk_M      ->clear();
    m_trk_pt     ->clear();
    m_trk_eta    ->clear();
    m_trk_phi    ->clear();
    m_trk_d0     ->clear();
    m_trk_z0     ->clear();
    m_trk_errd0  ->clear();
    m_trk_errz0  ->clear();
    m_trk_chi2   ->clear();

    m_trk_pt_wrtSV    ->clear();
    m_trk_eta_wrtSV   ->clear();
    m_trk_phi_wrtSV   ->clear();
    m_trk_d0_wrtSV    ->clear();
    m_trk_z0_wrtSV    ->clear();
    m_trk_errd0_wrtSV ->clear();
    m_trk_errz0_wrtSV ->clear();
    m_trk_errP_wrtSV  ->clear();
    m_trk_chi2_toSV   ->clear();

    m_trk_charge             ->clear();
    m_trk_isFinal            ->clear();
    m_trk_isSelected         ->clear();
    m_trk_isAssociated       ->clear();
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
      m_trk_truthProb    ->clear();
      m_trk_truthID      ->clear();
      m_trk_truthIndex   ->clear();
      m_trk_truthBarcode ->clear();
      m_trk_truthPdgId   ->clear();
    }
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

  // skip vertex if failed track trimming selections
  bool secVtx_passTrimSel = true;
  if ( secVtx->isAvailable<char>("passTrimSel") )
    secVtx_passTrimSel = secVtx->auxdataConst<char>("passTrimSel");
  if ( !secVtx_passTrimSel ) return;

  // get vector of filtered tracks
  std::vector< const xAOD::TrackParticle* > filteredTracks;
  EJsHelper::getFilteredTracks( secVtx, filteredTracks );
  if ( filteredTracks.size() < 2 ) return; // skip if less than two filtered tracks

  // fill common vertex container branches
  VertexContainer::FillVertex ();

  const TVector3 pos( secVtx->x(), secVtx->y(), secVtx->z() );
  
  // re-calculate vertex kinematic variables using filtered tracks
  const TLorentzVector& sumP4       = VsiBonsai::sumP4       ( filteredTracks );
  const double          scalarSumP  = VsiBonsai::scalarSumP  ( filteredTracks );
  const double          scalarSumPt = VsiBonsai::scalarSumPt ( filteredTracks );
  const int             sumCharge   = VsiBonsai::sumCharge   ( filteredTracks );
  const double          minOpAngle  = VsiBonsai::minOpAng    ( filteredTracks );
  const double          maxOpAngle  = VsiBonsai::maxOpAng    ( filteredTracks );
  const double          mind0       = VsiBonsai::mind0       ( filteredTracks );
  const double          maxd0       = VsiBonsai::maxd0       ( filteredTracks );
  
  const double dir  = sumP4.Vect().Dot( pos ) / sumP4.Vect().Mag() / pos.Mag();

  float mass_nonAssoc = AUXDYN( secVtx, float, "mass_selectedTracks" );

  m_ID            ->push_back( AUXDYN( secVtx, int, "ID"                ) );
  m_index         ->push_back( AUXDYN( secVtx, int, "index"             ) );
  m_x             ->push_back( secVtx->x()                                );
  m_y             ->push_back( secVtx->y()                                );
  m_z             ->push_back( secVtx->z()                                );
  m_r             ->push_back( secVtx->position().perp()                  );
  m_pt            ->push_back( sumP4.Pt() / m_units                       );
  m_eta           ->push_back( sumP4.Eta()                                );
  m_phi           ->push_back( sumP4.Phi()                                ); 
  m_mass          ->push_back( sumP4.M() / m_units                        );
  m_mass_nonAssoc ->push_back( mass_nonAssoc / m_units                    );
  m_covariance    ->push_back( secVtx->covariance()                       );
  m_chi2          ->push_back( secVtx->chiSquared() / secVtx->numberDoF() );
  m_direction     ->push_back( dir                                        );
  m_charge        ->push_back( sumCharge                                  );
  m_H             ->push_back( scalarSumP / m_units                       );
  m_Ht            ->push_back( scalarSumPt / m_units                      );
  m_minOpAng      ->push_back( minOpAngle                                 );
  m_maxOpAng      ->push_back( maxOpAngle                                 );
  m_mind0         ->push_back( mind0                                      );
  m_maxd0         ->push_back( maxd0                                      );

  float dv_distToPV = AlgConsts::invalidFloat;
  if ( pv ) dv_distToPV = ( pv->position() - secVtx->position() ).perp();
  m_distToPV ->push_back( dv_distToPV );

  const double minOneTrackRemovedMass = VsiBonsai::minOneTrackRemovedMass       ( filteredTracks );
  const auto   twoTrackMassTuples     = VsiBonsai::allTwoTracksMassCombinations ( filteredTracks );

  std::vector<float> twoTracksMass;
  std::vector<float> twoTracksMassRest;
  std::vector<int>   twoTracksCharge;
  for ( const auto& tuple : twoTrackMassTuples ) {
    double mass     = std::get<0>( tuple );
    double massRest = std::get<1>( tuple );

    const auto* trk1 = std::get<2>( tuple ).first;
    const auto* trk2 = std::get<2>( tuple ).second;
    
    int charge = trk1->charge() + trk2->charge();

    twoTracksMass     .push_back( mass / m_units     );
    twoTracksMassRest .push_back( massRest / m_units );
    twoTracksCharge   .push_back( charge             );
  }

  m_minOneTrackRemovedMass ->push_back( minOneTrackRemovedMass / m_units );
  m_twoTracksMass          ->push_back( twoTracksMass                    );
  m_twoTracksMassRest      ->push_back( twoTracksMassRest                );
  m_twoTracksCharge        ->push_back( twoTracksCharge                  );

  size_t ntrk_sel = 0;
  size_t ntrk_assoc = 0;
  for ( const auto& trk : filteredTracks ) {
    if ( trk->isAvailable<char>( "is_selected" ) )
      if ( trk->auxdataConst<char>( "is_selected" ) ) ++ntrk_sel;
    if ( trk->isAvailable<char>( "is_associated" ) )
      if ( trk->auxdataConst<char>( "is_associated" ) ) ++ntrk_assoc;
  }

  m_ntrk       ->push_back( filteredTracks.size() );
  m_ntrk_sel   ->push_back( ntrk_sel              );
  m_ntrk_assoc ->push_back( ntrk_assoc            );


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


  //////////////////////////////
  // tracks associated to DVs //
  //////////////////////////////
  if ( m_infoSwitch.m_tracks ) {
    recordTracks( filteredTracks );
  }

}


void SecondaryVertexContainer :: recordTracks ( const std::vector<const xAOD::TrackParticle*>& filteredTracks )
{
  if ( m_debug ) Info( "EJs::SecondaryVertexContainer::recordTracks()", "filling vertex track branches" );

  std::vector<int>   trk_ID;
  std::vector<int>   trk_index;
  std::vector<float> trk_qOverP;
  std::vector<float> trk_theta;
  std::vector<float> trk_vz;
  std::vector<float> trk_E;
  std::vector<float> trk_M;
  std::vector<float> trk_pt;
  std::vector<float> trk_eta;
  std::vector<float> trk_phi;
  std::vector<float> trk_d0;
  std::vector<float> trk_z0;
  std::vector<float> trk_errd0;
  std::vector<float> trk_errz0;
  std::vector<float> trk_chi2;

  std::vector<float> trk_pt_wrtSV;
  std::vector<float> trk_eta_wrtSV;
  std::vector<float> trk_phi_wrtSV;
  std::vector<float> trk_d0_wrtSV;
  std::vector<float> trk_z0_wrtSV;
  std::vector<float> trk_errd0_wrtSV;
  std::vector<float> trk_errz0_wrtSV;
  std::vector<float> trk_errP_wrtSV;
  std::vector<float> trk_chi2_toSV;

  std::vector<int>      trk_charge;
  std::vector<uint8_t>  trk_isFinal;
  std::vector<uint8_t>  trk_isSelected;
  std::vector<uint8_t>  trk_isAssociated;
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

  std::vector<float> trk_truthProb;
  std::vector<int>   trk_truthID;
  std::vector<int>   trk_truthIndex;
  std::vector<int>   trk_truthBarcode;
  std::vector<int>   trk_truthPdgId;

  for ( const auto& trk : filteredTracks ) {
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
      trk_truthProb    .push_back( trk->auxdataConst<float>("truthMatchProbability") );
      trk_truthID      .push_back( AUXDYN( truthPart, int, "ID"                    ) );
      trk_truthIndex   .push_back( AUXDYN( truthPart, int, "index"                 ) );
      trk_truthBarcode .push_back( truthPart->barcode()                              );
      trk_truthPdgId   .push_back( truthPart->pdgId()                                );
    }
    else {
      trk_truthProb    .push_back( AlgConsts::invalidFloat );
      trk_truthID      .push_back( AlgConsts::invalidInt   );
      trk_truthIndex   .push_back( AlgConsts::invalidInt   );
      trk_truthBarcode .push_back( AlgConsts::invalidInt   );
      trk_truthPdgId   .push_back( AlgConsts::invalidInt   );
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
  }

} // end recordTracks
