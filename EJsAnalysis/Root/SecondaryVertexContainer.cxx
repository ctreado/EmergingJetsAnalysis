#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>

#include "EJsAnalysis/SecondaryVertexContainer.h"
#include "EJsAnalysis/VsiBonsaiTool.h"

using namespace EJs;

SecondaryVertexContainer :: SecondaryVertexContainer ( const std::string& name,
						       const std::string& detailStr,
						       float units ) :
  VertexContainer ( name, detailStr, units )
{
  if ( m_debug ) Info( "SecondaryVertexContainer()", "setting up" );
  
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
  
  m_minOneTrackRemovedMass = new std::vector<float>;
  m_twoTracksMass          = new std::vector<std::vector<float>>;
  m_twoTracksMassRest      = new std::vector<std::vector<float>>;
  m_twoTracksCharge        = new std::vector<std::vector<int>>;
  
  m_ntrk       = new std::vector<uint32_t>;
  m_ntrk_sel   = new std::vector<uint32_t>;
  m_ntrk_assoc = new std::vector<uint32_t>;


  if ( m_infoSwitch.m_tracks ) {
    m_trk_qOverP = new std::vector<std::vector<float>>;
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

    // do we want to require "truth" info switch too ??
    m_trk_truthPid             = new std::vector<std::vector<int>>;
    m_trk_truthIsFromClosestTV = new std::vector<std::vector<uint8_t>>;
    m_trk_truthIsFromReprTV    = new std::vector<std::vector<uint8_t>>;
  }
}


SecondaryVertexContainer :: ~SecondaryVertexContainer ()
{
  if ( m_debug ) Info( "SecondaryVertexContainer()", "deleting" );

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
  
  delete m_minOneTrackRemovedMass;
  delete m_twoTracksMass;
  delete m_twoTracksMassRest;
  delete m_twoTracksCharge;
  
  delete m_ntrk;
  delete m_ntrk_sel;
  delete m_ntrk_assoc;


  if ( m_infoSwitch.m_tracks ) {
    delete m_trk_qOverP;
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
 
    delete m_trk_truthPid;
    delete m_trk_truthIsFromClosestTV;
    delete m_trk_truthIsFromReprTV;
  }
}


void SecondaryVertexContainer :: setTree ( TTree* tree )
{
  if ( m_debug ) Info( "SecondaryVertexContainer::setTree()", "setting tree" );
  
  VertexContainer::setTree ( tree );

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
  
  connectBranch<float>              ( tree, "minOneTrackRemovedMass", &m_minOneTrackRemovedMass );
  connectBranch<std::vector<float>> ( tree, "twoTracksMass",          &m_twoTracksMass          );
  connectBranch<std::vector<float>> ( tree, "twoTracksMassRest",      &m_twoTracksMassRest      );
  connectBranch<std::vector<int>>   ( tree, "twoTracksCharge",        &m_twoTracksCharge        );
  
  connectBranch<uint32_t> ( tree, "ntrk",       &m_ntrk       );
  connectBranch<uint32_t> ( tree, "ntrk_sel",   &m_ntrk_sel   );
  connectBranch<uint32_t> ( tree, "ntrk_assoc", &m_ntrk_assoc );

  
  if ( m_infoSwitch.m_tracks ) {
    connectBranch<std::vector<float>> ( tree, "trk_qOverP", &m_trk_qOverP );
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
    
    connectBranch<std::vector<int>>     ( tree, "trk_truthPid",             &m_trk_truthPid             );
    connectBranch<std::vector<uint8_t>> ( tree, "trk_truthIsFromClosestTV", &m_trk_truthIsFromClosestTV );
    connectBranch<std::vector<uint8_t>> ( tree, "trk_truthIsFromReprTV",    &m_trk_truthIsFromReprTV    );
  }
}


void SecondaryVertexContainer :: setBranches ( TTree* tree )
{
  if ( m_debug ) Info( "SecondaryVertexContainer::setBranches()", "setting branches" );
  
  VertexContainer::setBranches ( tree );

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

  setBranch<float>              ( tree, "minOneTrackRemovedMass", m_minOneTrackRemovedMass );
  setBranch<std::vector<float>> ( tree, "twoTracksMass",          m_twoTracksMass          );
  setBranch<std::vector<float>> ( tree, "twoTracksMassRest",      m_twoTracksMassRest      );
  setBranch<std::vector<int>>   ( tree, "twoTracksCharge",        m_twoTracksCharge        );

  setBranch<uint32_t> ( tree, "ntrk",       m_ntrk       );
  setBranch<uint32_t> ( tree, "ntrk_sel",   m_ntrk_sel   );
  setBranch<uint32_t> ( tree, "ntrk_assoc", m_ntrk_assoc );


  if ( m_infoSwitch.m_tracks ) {
    setBranch<std::vector<float>> ( tree, "trk_qOverP", m_trk_qOverP );
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

    setBranch<std::vector<int>>     ( tree, "trk_truthPid",             m_trk_truthPid             );
    setBranch<std::vector<uint8_t>> ( tree, "trk_truthIsFromClosestTV", m_trk_truthIsFromClosestTV );
    setBranch<std::vector<uint8_t>> ( tree, "trk_truthIsFromReprTV",    m_trk_truthIsFromReprTV    );
  }
}


void SecondaryVertexContainer :: clear ()
{
  if ( m_debug ) Info( "SecondaryVertexContainer::clear()", "clearing branches" );
  
  VertexContainer::clear ();

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
  
  m_minOneTrackRemovedMass ->clear();
  m_twoTracksMass          ->clear();
  m_twoTracksMassRest      ->clear();
  m_twoTracksCharge        ->clear();
  
  m_ntrk       ->clear();
  m_ntrk_sel   ->clear();
  m_ntrk_assoc ->clear();


  if ( m_infoSwitch.m_tracks ) {
    m_trk_qOverP ->clear();
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
    
    m_trk_truthPid             ->clear();
    m_trk_truthIsFromClosestTV ->clear();
    m_trk_truthIsFromReprTV    ->clear();
  }
}


void SecondaryVertexContainer :: FillSecondaryVertex ( const xAOD::Vertex* secVtx )
{
  if ( m_debug ) Info( "SecondaryVertexContainer::FillSecondaryVertex()", "filling branches" );
  
  VertexContainer::FillVertex ();

  // // check if vertex passed selections ...
  // bool secVtx_passSel = secVtx->auxdataConst<char>("passSel");
  // std::cout << "SECONDARY VERTEX: passed selections ?? " << secVtx_passSel << std::endl;

  const TVector3 pos( secVtx->x(), secVtx->y(), secVtx->z() );
  
  // get vector of filtered tracks
  std::vector< const xAOD::TrackParticle* > filteredTracks;
  for ( size_t itrk = 0; itrk != secVtx->nTrackParticles(); ++itrk ) {
    const auto* trk = secVtx->trackParticle( itrk );
    bool trk_isFilt = trk->auxdataConst<char>( "isFiltered" );
    if ( trk_isFilt ) filteredTracks.push_back( trk );
  }
  //std::cout << "N SECONDARY VERTEX TRACKS: " << secVtx->nTrackParticles();
  //std::cout << " " << filteredTracks.size() << std::endl;
  
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

  float mass_nonAssoc = AlgConsts::invalidFloat;
  if ( secVtx->isAvailable<float>( "mass_selectedTracks" ) )
    mass_nonAssoc = secVtx->auxdataConst<float>( "mass_selectedTracks" );

  /* pt = sqrt( px*px + py*py ) (same as 'sumP4.Pt())
     eta = pz / TMath::Abs(p)  * TMath::ACosH(p/pt) (same as 'sumP4.Eta()')
     phi = py / TMath::Abs(py) * TMath::ACos(px/pt) (same as 'sumP4.Phi()')
     --> NOT the same as 'secVtx->position().phi()' ... which is right ???? 

     --> not sure why 'sumP4.P*[M]()' differs from "vtx_p*[mass]" decorator, 
     but stick w/ 'sumP4.P*()' since "vtx_p*" decorator will become irrelevant
     once we start filtering tracks ...

     --> do we want to save px/y/z ?? do we want to save sumP4 as a whole ??
     do we want to save p4 (using track parameters wrt pv instead of dv) ?? */

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

  
  const double minOneTrackRemovedMass = VsiBonsai::minOneTrackRemovedMass       ( filteredTracks );
  const auto   twoTrackMassTuples     = VsiBonsai::allTwoTracksMassCombinations ( filteredTracks );

  std::vector<float> twoTracksMass;
  std::vector<float> twoTracksMassRest;
  std::vector<int>    twoTracksCharge;
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


  //////////////////////////////
  // tracks associated to DVs //
  //////////////////////////////
  if ( m_infoSwitch.m_tracks ) {
    recordTracks ( filteredTracks );
  }


  // ////////////////////////////
  // // DV-Jets (experimental) //
  // ////////////////////////////
  // if ( m_infoSwitch.m_jets ) {
  //   processDVJets ( filteredTracks );
  // }


  // ////////////////////
  // // truth matching //
  // ////////////////////
  // if ( m_infoSwitch.m_truth || m_infoSwitch.m_closest || m_infoSwitch.m_linked ) {
  //   // distance-based
  //   if ( m_infoSwitch.m_truth || m_infoSwitch.closest )
  //     processClosestTruth ( secVtx, filteredTracks, recoTracks, truthVertices );
  //   // track-truth-linked based
  //   if ( m_infoSwitch.m_truth || m_infoSwitch.linked  )
  //     processLinkedTruth  ( secVtx, filteredTracks, recoTracks, truthVertices );
  // }
  // // may want to change "linked" name -- figure out exactly how matching done first...
  // // --> don't like "repr" (for "representative") because not sure exactly how to define this yet...
  // // --> maybe want to keep as "representative" though and just modify function to use appropriate def...


}



void SecondaryVertexContainer :: recordTracks ( std::vector< const xAOD::TrackParticle* >& filteredTracks )
{
  if ( m_debug ) Info( "SecondaryVertexContainer::recordTracks()", "filling vertex track branches" );
  
  std::vector<float> trk_qOverP;
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

  for ( const auto& trk : filteredTracks ) {
    if ( !trk ) continue;

    trk_qOverP .push_back( trk->qOverP()                           );
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
    trk_chi2_toSV   .push_back( AUXDYN( trk, float, "chi2_toSV"   )           );

    trk_charge .push_back( trk->charge() );
    if ( trk->isAvailable<char>( "is_svtrk_final" ) )
      trk_isFinal      .push_back( trk->auxdataConst<char>( "is_svtrk_final" ) );
    if ( trk->isAvailable<char>( "is_selected"    ) )
      trk_isSelected   .push_back( trk->auxdataConst<char>( "is_selected"    ) );
    if ( trk->isAvailable<char>( "is_associated"  ) )
      trk_isAssociated .push_back( trk->auxdataConst<char>( "is_associated"  ) );

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

  }

  m_trk_qOverP ->push_back( trk_qOverP );
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
  m_trk_chi2_toSV   ->push_back( trk_chi2_toSV   );

  m_trk_charge             ->push_back( trk_charge       );
  m_trk_isFinal            ->push_back( trk_isFinal      );
  m_trk_isSelected         ->push_back( trk_isSelected   );
  m_trk_isAssociated       ->push_back( trk_isAssociated );
  m_trk_nPixelHits         ->push_back( trk_nPixelHits   );
  m_trk_nSCTHits           ->push_back( trk_nSCTHits     );
  m_trk_nTRTHits           ->push_back( trk_nTRTHits     );
  m_trk_nPixelBarrelLayers ->push_back( trk_nPixelBarrelLayers );
  m_trk_nPixelEndCapLayers ->push_back( trk_nPixelEndCapLayers );
  m_trk_nSCTBarrelLayers   ->push_back( trk_nSCTBarrelLayers   );
  m_trk_nSCTEndCapLayers   ->push_back( trk_nSCTEndCapLayers   );
  m_trk_hitPattern         ->push_back( trk_hitPattern         );
  m_trk_dEdx               ->push_back( trk_dEdx               );
  m_trk_nUsedHitsdEdx      ->push_back( trk_nUsedHitsdEdx      );
  m_trk_nIBLOverflowsdEdx  ->push_back( trk_nIBLOverflowsdEdx  );
  m_trk_radiusOfFirstHit   ->push_back( trk_radiusOfFirstHit   );

  // m_trk_truthPid, m_trk_truthIsFromClosestTV, m_trk_truthIsFromReprTV

}
