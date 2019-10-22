#include "EJsAnalysis/EJsHelpTreeBase.h"
#include "EJsAnalysis/EJsHelperFunctions.h"
#include "EJsAnalysis/AlgConsts.h"


EJsHelpTreeBase :: EJsHelpTreeBase ( xAOD::TEvent* event, TTree* tree, TFile* file, const float units, bool debug,
				     xAOD::TStore* store, bool emtopo, bool pflow, bool truth,
				     const std::vector<std::string>& truthVtxLLPs ) :
  HelpTreeBase ( event, tree, file, units, debug, store )
{
  m_truthVtxLLPs   = truthVtxLLPs;
  m_doEMTopoJets   = emtopo;
  m_doPFlowJets    = pflow;
  m_truthLevelOnly = truth;
  if ( m_truthLevelOnly ) { m_doEMTopoJets = false; m_doPFlowJets = false; }
  
  if ( m_debug ) Info( "EJsHelpTreeBase()", "creating output EJs TTree" );

  m_treeName = m_tree->GetName();
  
  m_pv_x        = 0;
  m_pv_y        = 0;
  m_pv_z        = 0;
  m_pv_r        = 0;
  m_pv_phi      = 0;
  m_pv_nTracks  = 0;
  m_pv_location = 0;

  m_eventIsMC             = 0;
  
  if ( !m_truthLevelOnly ) {
    m_signalTrig          = 0;
    m_validTrig           = 0;
  }
  
  if ( m_doEMTopoJets ) {
    m_signal_emtopo       = 0;
    m_valid_emtopo        = 0;
    m_ctrl_emtopo         = 0;
    m_signalNJet_emtopo   = 0;
    m_signalJetPt_emtopo  = 0;
    m_signalJetEta_emtopo = 0;
    m_signalNJetHt_emtopo = 0;
    m_validNJetMin_emtopo = 0;
    m_validNJetMax_emtopo = 0;
    m_validJetPt_emtopo   = 0;
    m_validJetEta_emtopo  = 0;
    m_njetHt_emtopo       = 0;
  }
  if ( m_doPFlowJets ) {
    m_signal_pflow        = 0;
    m_valid_pflow         = 0;
    m_ctrl_pflow          = 0;
    m_signalNJet_pflow    = 0;
    m_signalJetPt_pflow   = 0;
    m_signalJetEta_pflow  = 0;
    m_signalNJetHt_pflow  = 0; 
    m_validNJetMin_pflow  = 0;
    m_validNJetMax_pflow  = 0;
    m_validJetPt_pflow    = 0;
    m_validJetEta_pflow   = 0;
    m_njetHt_pflow        = 0;
  }
  if ( m_truthLevelOnly ) {
    m_signal_truth        = 0;
    m_valid_truth         = 0;
    m_ctrl_truth          = 0;
    m_signalNJet_truth    = 0;
    m_signalJetPt_truth   = 0;
    m_signalJetEta_truth  = 0;
    m_signalNJetHt_truth  = 0;
    m_signalNEJ_truth     = 0;
    m_validNJetMin_truth  = 0;
    m_validNJetMax_truth  = 0;
    m_validJetPt_truth    = 0;
    m_validJetEta_truth   = 0;
    m_njetHt_truth        = 0;
  }

  m_tp_ID                            = new std::vector<int>;
  m_tp_index                         = new std::vector<int>;
  m_tp_M                             = new std::vector<float>;
  m_tp_charge                        = new std::vector<float>;
  m_tp_isReco                        = new std::vector<uint8_t>;
  m_tp_isSelected                    = new std::vector<uint8_t>;
  m_tp_isAssociated                  = new std::vector<uint8_t>;
  m_tp_recoProb                      = new std::vector<float>;
  m_tp_recoID                        = new std::vector<int>;
  m_tp_recoIndex                     = new std::vector<int>;
  m_tp_isStable                      = new std::vector<uint8_t>;
  m_tp_isInteracting                 = new std::vector<uint8_t>;
  m_tp_isDark                        = new std::vector<uint8_t>;
  m_tp_isDescendant                  = new std::vector<uint8_t>;
  m_tp_ancestor_llpDecay             = new std::vector<std::vector<std::string>>;
  m_tp_ancestor_ID                   = new std::vector<std::vector<int>>;
  m_tp_ancestor_index                = new std::vector<std::vector<int>>;
  m_tp_parent_ID                     = new std::vector<std::vector<int>>;
  m_tp_parent_index                  = new std::vector<std::vector<int>>;
  m_tp_child_ID                      = new std::vector<std::vector<int>>;
  m_tp_child_index                   = new std::vector<std::vector<int>>;
  m_tp_pVtx                          = new std::vector<uint8_t>;
  m_tp_pVtx_llpDecay                 = new std::vector<std::string>;
  m_tp_pVtx_ID                       = new std::vector<int>;
  m_tp_pVtx_index                    = new std::vector<int>;
  m_tp_pVtx_barcode                  = new std::vector<int>;
  m_tp_pVtx_r                        = new std::vector<float>;
  m_tp_dVtx                          = new std::vector<uint8_t>;
  m_tp_dVtx_llpDecay                 = new std::vector<std::string>;
  m_tp_dVtx_ID                       = new std::vector<int>;
  m_tp_dVtx_index                    = new std::vector<int>;
  m_tp_dVtx_barcode                  = new std::vector<int>;
  m_tp_dVtx_r                        = new std::vector<float>;
  m_tp_truthJetMatch                 = new std::vector<uint8_t>;
  m_tp_truthJetMatch_ID              = new std::vector<int>;
  m_tp_truthJetMatch_index           = new std::vector<int>;
  m_tp_truthJetMatch_dR              = new std::vector<float>;
  m_tp_darkJetMatch                  = new std::vector<uint8_t>;
  m_tp_darkJetMatch_ID               = new std::vector<int>;
  m_tp_darkJetMatch_index            = new std::vector<int>;
  m_tp_darkJetMatch_dR               = new std::vector<float>;
  if ( m_doEMTopoJets ) {
    m_tp_emtopoJetMatch              = new std::vector<uint8_t>;
    m_tp_emtopoJetMatch_ID           = new std::vector<int>;
    m_tp_emtopoJetMatch_index        = new std::vector<int>;
    m_tp_emtopoJetMatch_dR           = new std::vector<float>;
  }
  if ( m_doPFlowJets ) {
    m_tp_pflowJetMatch               = new std::vector<uint8_t>;
    m_tp_pflowJetMatch_ID            = new std::vector<int>;
    m_tp_pflowJetMatch_index         = new std::vector<int>;
    m_tp_pflowJetMatch_dR            = new std::vector<float>;
  }

  m_trk_ID                           = new std::vector<int>;
  m_trk_index                        = new std::vector<int>;
  m_trk_M                            = new std::vector<float>;
  m_trk_d0                           = new std::vector<float>;
  m_trk_errd0                        = new std::vector<float>;
  m_trk_errz0                        = new std::vector<float>;
  m_trk_chiSquared                   = new std::vector<float>;
  m_trk_numberDoF                    = new std::vector<float>;
  m_trk_chi2                         = new std::vector<float>;
  m_trk_charge                       = new std::vector<float>;
  m_trk_nPixelHits                   = new std::vector<uint8_t>;
  m_trk_nPixelHoles                  = new std::vector<uint8_t>;
  m_trk_nPixelSharedHits             = new std::vector<uint8_t>;
  m_trk_nPixelDeadSensors            = new std::vector<uint8_t>;
  m_trk_expectInnerPixelLayerHit     = new std::vector<uint8_t>;
  m_trk_nInnerPixelLayerHits         = new std::vector<uint8_t>;
  m_trk_expectNextInnerPixelLayerHit = new std::vector<uint8_t>;
  m_trk_nNextInnerPixelLayerHits     = new std::vector<uint8_t>;
  m_trk_nSCTHits                     = new std::vector<uint8_t>;
  m_trk_nSCTHoles                    = new std::vector<uint8_t>;
  m_trk_nSCTSharedHits               = new std::vector<uint8_t>;
  m_trk_nSCTDeadSensors              = new std::vector<uint8_t>;
  m_trk_nTRTHits                     = new std::vector<uint8_t>;
  m_trk_nTRTOutliers                 = new std::vector<uint8_t>;
  m_trk_isLRT                        = new std::vector<uint8_t>;
  m_trk_isSelected                   = new std::vector<uint8_t>;
  m_trk_isAssociated                 = new std::vector<uint8_t>;
  m_trk_isSecVtxTrk                  = new std::vector<uint8_t>;
  m_trk_isSecVtxCleanTrk             = new std::vector<uint8_t>;
  m_trk_isSecVtxFiltTrk              = new std::vector<uint8_t>;
  m_trk_isSecVtxFinalTrk             = new std::vector<uint8_t>;
  m_trk_secVtxID                     = new std::vector<int>;
  m_trk_secVtxIndex                  = new std::vector<int>;
  if ( m_isMC ) {
    m_trk_isTruth                    = new std::vector<uint8_t>;
    m_trk_truthProb                  = new std::vector<float>;
    m_trk_truthID                    = new std::vector<int>;
    m_trk_truthIndex                 = new std::vector<int>;
    m_trk_truthBarcode               = new std::vector<int>;
    m_trk_truthPdgId                 = new std::vector<int>;
    m_trk_truthIsDesc                = new std::vector<uint8_t>;
    m_trk_truthAncestorLLPDecay      = new std::vector<std::vector<std::string>>;
    m_trk_truthAncestorID            = new std::vector<std::vector<int>>;
    m_trk_truthAncestorIndex         = new std::vector<std::vector<int>>;
    m_trk_truthJetMatch              = new std::vector<uint8_t>;
    m_trk_truthJetMatch_ID           = new std::vector<int>;
    m_trk_truthJetMatch_index        = new std::vector<int>;
    m_trk_truthJetMatch_dR           = new std::vector<float>;
    m_trk_darkJetMatch               = new std::vector<uint8_t>;
    m_trk_darkJetMatch_ID            = new std::vector<int>;
    m_trk_darkJetMatch_index         = new std::vector<int>;
    m_trk_darkJetMatch_dR            = new std::vector<float>;
  }
  if ( m_doEMTopoJets ) {
    m_trk_emtopoJetMatch             = new std::vector<uint8_t>;
    m_trk_emtopoJetMatch_ID          = new std::vector<int>;
    m_trk_emtopoJetMatch_index       = new std::vector<int>;
    m_trk_emtopoJetMatch_dR          = new std::vector<float>;
  }
  if ( m_doPFlowJets ) {
    m_trk_pflowJetMatch              = new std::vector<uint8_t>;
    m_trk_pflowJetMatch_ID           = new std::vector<int>;
    m_trk_pflowJetMatch_index        = new std::vector<int>;
    m_trk_pflowJetMatch_dR           = new std::vector<float>;
  }
  
}

EJsHelpTreeBase :: ~EJsHelpTreeBase()
{
  if ( m_debug ) Info( "EJsHelpTreeBase()", "deleting" );
  
  // truth vertices
  for ( auto truthVtx : m_truthVerts )
    delete truthVtx.second;

  // secondary vertices
  for ( auto secVtx : m_secVerts )
    delete secVtx.second;

  // jets
  for ( auto jet : m_jets )
    delete jet.second;
}



/******************
 * TRUTH VERTICES *
 ******************/

void EJsHelpTreeBase :: AddTruthVerts ( const std::string detailStr, const std::string truthVtxName )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddTruthVerts()", "adding truth vertex variables" );

  m_truthVerts[ truthVtxName ] =
    new EJs::TruthVertexContainer( truthVtxName, detailStr, m_units, m_isMC, m_doEMTopoJets, m_doPFlowJets );
  EJs::TruthVertexContainer* thisTruthVtx = m_truthVerts[ truthVtxName ];
  thisTruthVtx->setBranches( m_tree );
}

void EJsHelpTreeBase :: FillTruthVerts ( const xAOD::TruthVertexContainer* truthVerts, const std::string truthVtxName )
{
  this->ClearTruthVerts ( truthVtxName );

  for ( const auto& truthVtx : *truthVerts )
    this->FillTruthVertex( truthVtx, truthVtxName );
}

void EJsHelpTreeBase :: FillTruthVertex ( const xAOD::TruthVertex* truthVtx, const std::string truthVtxName )
{
  EJs::TruthVertexContainer* thisTruthVtx = m_truthVerts[ truthVtxName ];
  thisTruthVtx->FillTruthVertex( truthVtx, m_truthVtxLLPs, m_treeName );
}

void EJsHelpTreeBase :: ClearTruthVerts ( const std::string truthVtxName )
{
  EJs::TruthVertexContainer* thisTruthVtx = m_truthVerts[ truthVtxName ];
  thisTruthVtx->clear();
}



/**********************
 * SECONDARY VERTICES *
 **********************/

void EJsHelpTreeBase :: AddSecondaryVerts ( const std::string detailStr, const std::string secVtxName )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddSecondaryVerts()", "adding secondary vertex variables" );

  m_secVerts[ secVtxName ] = new EJs::SecondaryVertexContainer( secVtxName, detailStr, m_units, m_isMC, m_doEMTopoJets, m_doPFlowJets );
  EJs::SecondaryVertexContainer* thisSecVtx = m_secVerts[ secVtxName ];
  thisSecVtx->setBranches( m_tree );
}

void EJsHelpTreeBase :: FillSecondaryVerts ( const xAOD::VertexContainer* secVerts, const std::string secVtxName,
					     const xAOD::Vertex* pv )
{
  this->ClearSecondaryVerts ( secVtxName );

  for ( const auto& secVtx : *secVerts )
    this->FillSecondaryVertex( secVtx, secVtxName, pv );
}

void EJsHelpTreeBase :: FillSecondaryVertex ( const xAOD::Vertex* secVtx, const std::string secVtxName,
					      const xAOD::Vertex* pv )
{
  EJs::SecondaryVertexContainer* thisSecVtx = m_secVerts[ secVtxName ];
  thisSecVtx->FillSecondaryVertex( secVtx, m_truthVtxLLPs, m_treeName, pv );
}

void EJsHelpTreeBase :: ClearSecondaryVerts ( const std::string secVtxName )
{
  EJs::SecondaryVertexContainer* thisSecVtx = m_secVerts[ secVtxName ];
  thisSecVtx->clear();
}



/******************
 * PRIMARY VERTEX *
 ******************/

void EJsHelpTreeBase :: AddPV ( )
{

  if ( m_debug ) Info( "EJsHelpTreeBase::AddPV()", "adding primary vertex variables" );

  m_tree->Branch( "PV_x",        &m_pv_x,        "PV_x/F"        );
  m_tree->Branch( "PV_y",        &m_pv_y,        "PV_y/F"        );
  m_tree->Branch( "PV_z",        &m_pv_z,        "PV_z/F"        );
  m_tree->Branch( "PV_r",        &m_pv_r,        "PV_r/F"        );
  m_tree->Branch( "PV_phi",      &m_pv_phi,      "PV_phi/F"      );
  m_tree->Branch( "PV_nTracks",  &m_pv_nTracks,  "PV_nTracks/I"  );
  m_tree->Branch( "PV_location", &m_pv_location, "PV_location/I" );
}

void EJsHelpTreeBase :: FillPV ( const xAOD::Vertex* pv, int pvLocation )
{
  m_pv_x        = pv->x();
  m_pv_y        = pv->y();
  m_pv_z        = pv->z();
  m_pv_r        = pv->position().perp();
  m_pv_phi      = pv->position().phi();
  m_pv_nTracks  = pv->nTrackParticles();
  m_pv_location = pvLocation;
}

void EJsHelpTreeBase :: ClearPV ( )
{
  m_pv_x        = 0;
  m_pv_y        = 0;
  m_pv_z        = 0;
  m_pv_r        = 0;
  m_pv_phi      = 0;
  m_pv_nTracks  = 0;
  m_pv_location = 0;
}



/***************
 * USER EVENTS *
 **************/

void EJsHelpTreeBase :: AddEventUser ( const std::string detailStr )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddEventUser()", "adding EJs-user event variables" );

  m_tree->Branch( "isMC", &m_eventIsMC );

  if ( !m_truthLevelOnly ) {
    m_tree->Branch( "passesSignalTrigger", &m_signalTrig );
    m_tree->Branch( "passesValidTrigger",  &m_validTrig  );
  }
  
  if ( m_doEMTopoJets ) {
    m_tree->Branch( "isSignal_EMTopo",           &m_signal_emtopo       );
    m_tree->Branch( "isValid_EMTopo",            &m_valid_emtopo        );
    m_tree->Branch( "isCtrl_EMTopo",             &m_ctrl_emtopo         );

    m_tree->Branch( "passesSignalNJet_EMTopo",   &m_signalNJet_emtopo   );
    m_tree->Branch( "passesSignalJetPt_EMTopo",  &m_signalJetPt_emtopo  );
    m_tree->Branch( "passesSignalJetEta_EMTopo", &m_signalJetEta_emtopo );
    m_tree->Branch( "passesSignalNJetHt_EMTopo", &m_signalNJetHt_emtopo );
  
    m_tree->Branch( "passesValidNJetMin_EMTopo", &m_validNJetMin_emtopo );
    m_tree->Branch( "passesValidNJetMax_EMTopo", &m_validNJetMax_emtopo );
    m_tree->Branch( "passesValidJetPt_EMTopo",   &m_validJetPt_emtopo   );
    m_tree->Branch( "passesValidJetEta_EMTopo",  &m_validJetEta_emtopo  );
    
    m_tree->Branch( "NJetHt_EMTopo",             &m_njetHt_emtopo       );
  }
  
  if ( m_doPFlowJets ) {
    m_tree->Branch( "isSignal_PFlow",           &m_signal_pflow       );
    m_tree->Branch( "isValid_PFlow",            &m_valid_pflow        );
    m_tree->Branch( "isCtrl_PFlow",             &m_ctrl_pflow         );

    m_tree->Branch( "passesSignalNJet_PFlow",   &m_signalNJet_pflow   );
    m_tree->Branch( "passesSignalJetPt_PFlow",  &m_signalJetPt_pflow  );
    m_tree->Branch( "passesSignalJetEta_PFlow", &m_signalJetEta_pflow );
    m_tree->Branch( "passesSignalNJetHt_PFlow", &m_signalNJetHt_pflow );
    
    m_tree->Branch( "passesValidNJetMin_PFlow", &m_validNJetMin_pflow );
    m_tree->Branch( "passesValidNJetMax_PFlow", &m_validNJetMax_pflow );
    m_tree->Branch( "passesValidJetPt_PFlow",   &m_validJetPt_pflow   );
    m_tree->Branch( "passesValidJetEta_PFlow",  &m_validJetEta_pflow  );
  
    m_tree->Branch( "NJetHt_PFlow",             &m_njetHt_pflow       );
  }

  if ( m_truthLevelOnly ) {
    m_tree->Branch( "isSignal_Truth",           &m_signal_truth       );
    m_tree->Branch( "isValid_Truth",            &m_valid_truth        );
    m_tree->Branch( "isCtrl_Truth",             &m_ctrl_truth         );

    m_tree->Branch( "passesSignalNJet_Truth",   &m_signalNJet_truth   );
    m_tree->Branch( "passesSignalJetPt_Truth",  &m_signalJetPt_truth  );
    m_tree->Branch( "passesSignalJetEta_Truth", &m_signalJetEta_truth );
    m_tree->Branch( "passesSignalNJetHt_Truth", &m_signalNJetHt_truth );
    m_tree->Branch( "passesSignalNEJ_Truth",    &m_signalNEJ_truth    );
    
    m_tree->Branch( "passesValidNJetMin_Truth", &m_validNJetMin_truth );
    m_tree->Branch( "passesValidNJetMax_Truth", &m_validNJetMax_truth );
    m_tree->Branch( "passesValidJetPt_Truth",   &m_validJetPt_truth   );
    m_tree->Branch( "passesValidJetEta_Truth",  &m_validJetEta_truth  );
  
    m_tree->Branch( "NJetHt_Truth",             &m_njetHt_truth       );
  }
}

void EJsHelpTreeBase :: FillEventUser ( const xAOD::EventInfo* event )
{
  std::string treeName = m_treeName;
  if ( treeName == "nominal" ) treeName = "";

  m_eventIsMC = m_isMC;
  
  if ( event->isAvailable<char>( "passSignalTrigSel" ) ) {
    m_signalTrig = event->auxdataConst<char>( "passSignalTrigSel" );
    m_validTrig  = event->auxdataConst<char>( "passValidTrigSel"  );
  }

  if ( m_doEMTopoJets ) {
    // if running EMTopo systematics...
    if ( event->isAvailable<char>( "passSignalSel_EMTopo" + treeName ) ) {
      m_signal_emtopo = event->auxdataConst<char>( "passSignalSel_EMTopo" + treeName );
      m_valid_emtopo  = event->auxdataConst<char>( "passValidSel_EMTopo"  + treeName );
      m_ctrl_emtopo   = event->auxdataConst<char>( "passCtrlSel_EMTopo"   + treeName );

      m_signalNJet_emtopo   = event->auxdataConst<char>( "passSignalNJetSel_EMTopo"   + treeName );
      m_signalJetPt_emtopo  = event->auxdataConst<char>( "passSignalJetPtSel_EMTopo"  + treeName );
      m_signalJetEta_emtopo = event->auxdataConst<char>( "passSignalJetEtaSel_EMTopo" + treeName );
      m_signalNJetHt_emtopo = event->auxdataConst<char>( "passSignalNJetHtSel_EMTopo" + treeName );
      
      m_validNJetMin_emtopo = event->auxdataConst<char>( "passValidNJetMinSel_EMTopo" + treeName );
      m_validNJetMax_emtopo = event->auxdataConst<char>( "passValidNJetMaxSel_EMTopo" + treeName );
      m_validJetPt_emtopo   = event->auxdataConst<char>( "passValidJetPtSel_EMTopo"   + treeName );
      m_validJetEta_emtopo  = event->auxdataConst<char>( "passValidJetEtaSel_EMTopo"  + treeName );
    }
    // otherwise, get decorators for nominal case...
    else if ( event->isAvailable<char>( "passSignalSel_EMTopo" ) ) {
      m_signal_emtopo = event->auxdataConst<char>( "passSignalSel_EMTopo" );
      m_valid_emtopo  = event->auxdataConst<char>( "passValidSel_EMTopo"  );
      m_ctrl_emtopo   = event->auxdataConst<char>( "passCtrlSel_EMTopo"   );
      
      m_signalNJet_emtopo   = event->auxdataConst<char>( "passSignalNJetSel_EMTopo"   );
      m_signalJetPt_emtopo  = event->auxdataConst<char>( "passSignalJetPtSel_EMTopo"  );
      m_signalJetEta_emtopo = event->auxdataConst<char>( "passSignalJetEtaSel_EMTopo" );
      m_signalNJetHt_emtopo = event->auxdataConst<char>( "passSignalNJetHtSel_EMTopo" );

      m_validNJetMin_emtopo = event->auxdataConst<char>( "passValidNJetMinSel_EMTopo" );
      m_validNJetMax_emtopo = event->auxdataConst<char>( "passValidNJetMaxSel_EMTopo" );
      m_validJetPt_emtopo   = event->auxdataConst<char>( "passValidJetPtSel_EMTopo"   );
      m_validJetEta_emtopo  = event->auxdataConst<char>( "passValidJetEtaSel_EMTopo"  );
    }

    if ( event->isAvailable<double>( "NJetHt_EMTopo" + treeName ) )
      m_njetHt_emtopo = event->auxdataConst<double>( "NJetHt_EMTopo" + treeName );
    else if ( event->isAvailable<double>( "NJetHt_EMTopo" ) )
      m_njetHt_emtopo = event->auxdataConst<double>( "NJetHt_EMTopo" );
  }

  if ( m_doPFlowJets ) {
    // if running PFlow systematics...
    if ( event->isAvailable<char>( "passSignalSel_PFlow" + treeName ) ) {  
      m_signal_pflow  = event->auxdataConst<char>( "passSignalSel_PFlow" + treeName );
      m_valid_pflow   = event->auxdataConst<char>( "passValidSel_PFlow"  + treeName );
      m_ctrl_pflow    = event->auxdataConst<char>( "passCtrlSel_PFlow"   + treeName );
      
      m_signalNJet_pflow    = event->auxdataConst<char>( "passSignalNJetSel_PFlow"   + treeName );
      m_signalJetPt_pflow   = event->auxdataConst<char>( "passSignalJetPtSel_PFlow"  + treeName );
      m_signalJetEta_pflow  = event->auxdataConst<char>( "passSignalJetEtaSel_PFlow" + treeName );
      m_signalNJetHt_pflow  = event->auxdataConst<char>( "passSignalNJetHtSel_PFlow" + treeName );
      
      m_validNJetMin_pflow  = event->auxdataConst<char>( "passValidNJetMinSel_PFlow" + treeName );
      m_validNJetMax_pflow  = event->auxdataConst<char>( "passValidNJetMaxSel_PFlow" + treeName );
      m_validJetPt_pflow    = event->auxdataConst<char>( "passValidJetPtSel_PFlow"   + treeName );
      m_validJetEta_pflow   = event->auxdataConst<char>( "passValidJetEtaSel_PFlow"  + treeName );
    }
    // otherwise, get decorators for nominal case...
    else if ( event->isAvailable<char>( "passSignalSel_PFlow" ) ) {
      m_signal_pflow  = event->auxdataConst<char>( "passSignalSel_PFlow" );
      m_valid_pflow   = event->auxdataConst<char>( "passValidSel_PFlow"  );
      m_ctrl_pflow    = event->auxdataConst<char>( "passCtrlSel_PFlow"   );
      
      m_signalNJet_pflow    = event->auxdataConst<char>( "passSignalNJetSel_PFlow"   );
      m_signalJetPt_pflow   = event->auxdataConst<char>( "passSignalJetPtSel_PFlow"  );
      m_signalJetEta_pflow  = event->auxdataConst<char>( "passSignalJetEtaSel_PFlow" );
      m_signalNJetHt_pflow  = event->auxdataConst<char>( "passSignalNJetHtSel_PFlow" );

      m_validNJetMin_pflow  = event->auxdataConst<char>( "passValidNJetMinSel_PFlow" );
      m_validNJetMax_pflow  = event->auxdataConst<char>( "passValidNJetMaxSel_PFlow" );
      m_validJetPt_pflow    = event->auxdataConst<char>( "passValidJetPtSel_PFlow"   );
      m_validJetEta_pflow   = event->auxdataConst<char>( "passValidJetEtaSel_PFlow"  );
    }

    if ( event->isAvailable<double>( "NJetHt_PFlow" + treeName ) )
      m_njetHt_pflow = event->auxdataConst<double>( "NJetHt_PFlow" + treeName );
    else if ( event->isAvailable<double>( "NJetHt_PFlow" ) )
      m_njetHt_pflow = event->auxdataConst<double>( "NJetHt_PFlow" );
  }

  if ( m_truthLevelOnly ) {
    if ( event->isAvailable<char>( "passSignalSel_Truth" ) ) {
      m_signal_truth  = event->auxdataConst<char>( "passSignalSel_Truth" );
      m_valid_truth   = event->auxdataConst<char>( "passValidSel_Truth"  );
      m_ctrl_truth    = event->auxdataConst<char>( "passCtrlSel_Truth"   );
      
      m_signalNJet_truth    = event->auxdataConst<char>( "passSignalNJetSel_Truth"   );
      m_signalJetPt_truth   = event->auxdataConst<char>( "passSignalJetPtSel_Truth"  );
      m_signalJetEta_truth  = event->auxdataConst<char>( "passSignalJetEtaSel_Truth" );
      m_signalNJetHt_truth  = event->auxdataConst<char>( "passSignalNJetHtSel_Truth" );
      m_signalNEJ_truth     = event->auxdataConst<char>( "passSignalNEJSel_Truth"    );

      m_validNJetMin_truth  = event->auxdataConst<char>( "passValidNJetMinSel_Truth" );
      m_validNJetMax_truth  = event->auxdataConst<char>( "passValidNJetMaxSel_Truth" );
      m_validJetPt_truth    = event->auxdataConst<char>( "passValidJetPtSel_Truth"   );
      m_validJetEta_truth   = event->auxdataConst<char>( "passValidJetEtaSel_Truth"  );
    }
    if ( event->isAvailable<double>( "NJetHt_Truth" ) )
      m_njetHt_truth = event->auxdataConst<double>( "NJetHt_Truth" );
  }
    
}

void EJsHelpTreeBase :: ClearEventUser ( )
{
  m_eventIsMC = 0;

  if ( !m_truthLevelOnly ) {
    m_signalTrig = 0;
    m_validTrig  = 0;
  }

  if ( m_doEMTopoJets ) {
    m_signal_emtopo       = 0;
    m_valid_emtopo        = 0;
    m_ctrl_emtopo         = 0;
    
    m_signalNJet_emtopo   = 0;
    m_signalJetPt_emtopo  = 0;
    m_signalJetEta_emtopo = 0;
    m_signalNJetHt_emtopo = 0;
    
    m_validNJetMin_emtopo = 0;
    m_validNJetMax_emtopo = 0;
    m_validJetPt_emtopo   = 0;
    m_validJetEta_emtopo  = 0;
    
    m_njetHt_emtopo       = 0;
  }

  if ( m_doPFlowJets ) {
    m_signal_pflow       = 0;
    m_valid_pflow        = 0;
    m_ctrl_pflow         = 0;
    
    m_signalNJet_pflow   = 0;  
    m_signalJetPt_pflow  = 0; 
    m_signalJetEta_pflow = 0;
    m_signalNJetHt_pflow = 0;
    
    m_validNJetMin_pflow = 0; 
    m_validNJetMax_pflow = 0; 
    m_validJetPt_pflow   = 0; 
    m_validJetEta_pflow  = 0;
    
    m_njetHt_pflow       = 0;
  }

  if ( m_truthLevelOnly ) {
    m_signal_truth       = 0;
    m_valid_truth        = 0;
    m_ctrl_truth         = 0;
    
    m_signalNJet_truth   = 0;  
    m_signalJetPt_truth  = 0; 
    m_signalJetEta_truth = 0;
    m_signalNJetHt_truth = 0;
    m_signalNEJ_truth    = 0;
    
    m_validNJetMin_truth = 0; 
    m_validNJetMax_truth = 0; 
    m_validJetPt_truth   = 0; 
    m_validJetEta_truth  = 0;
    
    m_njetHt_truth       = 0;
  }
}



/*************
 * USER JETS *
 *************/

void EJsHelpTreeBase :: AddJetsUser ( const std::string detailStr, const std::string jetName )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddJetsUser()", "adding EJs-user jet variables" );

  m_jets[ jetName ] = new EJs::JetContainer( jetName, detailStr, m_units, m_isMC, m_doEMTopoJets, m_doPFlowJets );
  EJs::JetContainer* thisJet = m_jets[ jetName ];
  thisJet->setBranches( m_tree );
}

void EJsHelpTreeBase :: FillJetsUser ( const xAOD::Jet* jet, const std::string jetName )
{
  EJs::JetContainer* thisJet = m_jets[ jetName ];
  thisJet->FillJet( jet, m_truthVtxLLPs, m_treeName );
}

void EJsHelpTreeBase :: ClearJetsUser ( const std::string jetName )
{
  EJs::JetContainer* thisJet = m_jets[ jetName ];
  thisJet->clear();
}



/************************
 * USER TRUTH PARTICLES *
 ************************/
void EJsHelpTreeBase :: AddTruthUser ( const std::string truthName, const std::string detailStr )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddTruthUser()", "adding EJs-user truth particle variables" );

  setBranch<int>                      ( truthName, "ID",                   m_tp_ID                   );
  setBranch<int>                      ( truthName, "index",                m_tp_index                );
  setBranch<float>                    ( truthName, "M",                    m_tp_M                    );
  setBranch<float>                    ( truthName, "charge",               m_tp_charge               );
  setBranch<uint8_t>                  ( truthName, "isReco",               m_tp_isReco               );
  setBranch<uint8_t>                  ( truthName, "isSelected",           m_tp_isSelected           );
  setBranch<uint8_t>                  ( truthName, "isAssociated",         m_tp_isAssociated         );
  setBranch<float>                    ( truthName, "recoProb",             m_tp_recoProb             );
  setBranch<int>                      ( truthName, "recoID",               m_tp_recoID               );
  setBranch<int>                      ( truthName, "recoIndex",            m_tp_recoIndex            );
  setBranch<uint8_t>                  ( truthName, "isStable",             m_tp_isStable             );
  setBranch<uint8_t>                  ( truthName, "isInteracting",        m_tp_isInteracting        );
  setBranch<uint8_t>                  ( truthName, "isDark",               m_tp_isDark               );
  setBranch<uint8_t>                  ( truthName, "isDescendant",         m_tp_isDescendant         );
  setBranch<std::vector<std::string>> ( truthName, "ancestor_llpDecay",    m_tp_ancestor_llpDecay    );
  setBranch<std::vector<int>>         ( truthName, "ancestor_ID",          m_tp_ancestor_ID          );
  setBranch<std::vector<int>>         ( truthName, "ancestor_index",       m_tp_ancestor_index       );
  setBranch<std::vector<int>>         ( truthName, "parent_ID",            m_tp_parent_ID            );
  setBranch<std::vector<int>>         ( truthName, "parent_index",         m_tp_parent_index         );
  setBranch<std::vector<int>>         ( truthName, "child_ID",             m_tp_child_ID             );
  setBranch<std::vector<int>>         ( truthName, "child_index",          m_tp_child_index          );
  setBranch<uint8_t>                  ( truthName, "hasProdVtx",           m_tp_pVtx                 );
  setBranch<std::string>              ( truthName, "prodVtx_llpDecay",     m_tp_pVtx_llpDecay        );
  setBranch<int>                      ( truthName, "prodVtx_ID",           m_tp_pVtx_ID              );
  setBranch<int>                      ( truthName, "prodVtx_index",        m_tp_pVtx_index           );
  setBranch<int>                      ( truthName, "prodVtx_barcode",      m_tp_pVtx_barcode         );
  setBranch<float>                    ( truthName, "prodVtx_r",            m_tp_pVtx_r               );
  setBranch<uint8_t>                  ( truthName, "hasDecayVtx",          m_tp_dVtx                 );
  setBranch<std::string>              ( truthName, "decayVtx_llpDecay",    m_tp_dVtx_llpDecay        );
  setBranch<int>                      ( truthName, "decayVtx_ID",          m_tp_dVtx_ID              );
  setBranch<int>                      ( truthName, "decayVtx_index",       m_tp_dVtx_index           );
  setBranch<int>                      ( truthName, "decayVtx_barcode",     m_tp_dVtx_barcode         );
  setBranch<float>                    ( truthName, "decayVtx_r",           m_tp_dVtx_r               );
  setBranch<uint8_t>                  ( truthName, "truthJetMatch",        m_tp_truthJetMatch        );
  setBranch<int>                      ( truthName, "truthJetMatch_ID",     m_tp_truthJetMatch_ID     );
  setBranch<int>                      ( truthName, "truthJetMatch_index",  m_tp_truthJetMatch_index  );
  setBranch<float>                    ( truthName, "truthJetMatch_dR",     m_tp_truthJetMatch_dR     );
  setBranch<uint8_t>                  ( truthName, "darkJetMatch",         m_tp_darkJetMatch         );
  setBranch<int>                      ( truthName, "darkJetMatch_ID",      m_tp_darkJetMatch_ID      );
  setBranch<int>                      ( truthName, "darkJetMatch_index",   m_tp_darkJetMatch_index   );
  setBranch<float>                    ( truthName, "darkJetMatch_dR",      m_tp_darkJetMatch_dR      );
  if ( m_doEMTopoJets ) {
    setBranch<uint8_t>                ( truthName, "emtopoJetMatch",       m_tp_emtopoJetMatch       );
    setBranch<int>                    ( truthName, "emtopoJetMatch_ID",    m_tp_emtopoJetMatch_ID    );
    setBranch<int>                    ( truthName, "emtopoJetMatch_index", m_tp_emtopoJetMatch_index );
    setBranch<float>                  ( truthName, "emtopoJetMatch_dR",    m_tp_emtopoJetMatch_dR    );
  }
  if ( m_doPFlowJets ) {
    setBranch<uint8_t>                ( truthName, "pflowJetMatch",        m_tp_pflowJetMatch        );
    setBranch<int>                    ( truthName, "pflowJetMatch_ID",     m_tp_pflowJetMatch_ID     );
    setBranch<int>                    ( truthName, "pflowJetMatch_index",  m_tp_pflowJetMatch_index  );
    setBranch<float>                  ( truthName, "pflowJetMatch_dR",     m_tp_pflowJetMatch_dR     );
  }
}

void EJsHelpTreeBase :: FillTruthUser ( const std::string truthName, const xAOD::TruthParticle* truthPart )
{
  std::string treeName = m_treeName;
  if ( treeName == "nominal" ) treeName = "";

  int     tp_recoID      = AlgConsts::invalidInt;
  int     tp_recoIndex   = AlgConsts::invalidInt;
  uint8_t tp_recoIsSel   = AlgConsts::invalidUnsigned;
  uint8_t tp_recoIsAssoc = AlgConsts::invalidUnsigned;
  static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> recoAccess("trackLink");
  if ( recoAccess.isAvailable( *truthPart ) ) {
    try {
      const EJsHelper::TrackLink_t& recolink = recoAccess( *truthPart );
      tp_recoID      = AUXDYN( (*recolink), int,  "ID"            );
      tp_recoIndex   = AUXDYN( (*recolink), int,  "index"         );
      tp_recoIsSel   = AUXDYN( (*recolink), char, "is_selected"   );
      tp_recoIsAssoc = AUXDYN( (*recolink), char, "is_associated" );
    } catch(...) {}
  }
  m_tp_ID            ->push_back( AUXDYN( truthPart, int,   "ID"                          ) );
  m_tp_index         ->push_back( AUXDYN( truthPart, int,   "index"                       ) );
  m_tp_M             ->push_back( truthPart->m() / m_units                                  );
  m_tp_charge        ->push_back( truthPart->charge()                                       );
  m_tp_isReco        ->push_back( AUXDYN( truthPart, char,  "isTrackMatch"                ) );
  m_tp_isSelected    ->push_back( tp_recoIsSel                                              );
  m_tp_isAssociated  ->push_back( tp_recoIsAssoc                                            );
  m_tp_recoProb      ->push_back( AUXDYN( truthPart, float, "trackMatchProbability"       ) );
  m_tp_recoID        ->push_back( tp_recoID                                                 );
  m_tp_recoIndex     ->push_back( tp_recoIndex                                              );
  m_tp_isStable      ->push_back( EJsHelper::isStable       ( truthPart                   ) );
  m_tp_isInteracting ->push_back( EJsHelper::isInteracting  ( truthPart                   ) );
  m_tp_isDark        ->push_back( EJsHelper::isDark         ( truthPart                   ) );
  m_tp_isDescendant  ->push_back( AUXDYN( truthPart, char,  "isReconstructibleDescendant" ) );

  std::vector<std::string> ancestor_llpDecay;
  std::vector<int>         ancestor_ID;
  std::vector<int>         ancestor_index;
  static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLinkVector_t> ancestorAccess("truthVertexAncestorLinks");
  if ( ancestorAccess.isAvailable( *truthPart ) ) {
    const EJsHelper::TruthVertexLinkVector_t& ancestorVtxLinks = ancestorAccess( *truthPart );
    for ( const auto& ancestorlink : ancestorVtxLinks ) {
      if ( !ancestorlink.isValid() ) continue;
      std::string llpDecayType = "";
      for ( size_t i = 0; i != m_truthVtxLLPs.size(); ++i )
	if ( EJsHelper::pdgIdFuncs[m_truthVtxLLPs.at(i)]( *ancestorlink ) ) llpDecayType = m_truthVtxLLPs.at(i);
      ancestor_llpDecay .push_back( llpDecayType                            );
      ancestor_ID       .push_back( AUXDYN( (*ancestorlink), int, "ID"    ) );
      ancestor_index    .push_back( AUXDYN( (*ancestorlink), int, "index" ) );
    }
  }
  m_tp_ancestor_llpDecay ->push_back( ancestor_llpDecay );
  m_tp_ancestor_ID       ->push_back( ancestor_ID       );
  m_tp_ancestor_index    ->push_back( ancestor_index    );
  
  std::vector<int> parent_ID;
  std::vector<int> parent_index;
  for ( size_t i = 0; i != truthPart->nParents(); ++i ) {
    const auto* parent = truthPart->parent(i);
    if ( !parent ) continue;
    parent_ID    .push_back( AUXDYN( parent, int, "ID"    ) );
    parent_index .push_back( AUXDYN( parent, int, "index" ) );
  }
  m_tp_parent_ID    ->push_back( parent_ID    );
  m_tp_parent_index ->push_back( parent_index );
  
  std::vector<int> child_ID;
  std::vector<int> child_index;
  for ( size_t i = 0; i != truthPart->nChildren(); ++i ) {
    const auto* child = truthPart->child(i);
    if ( !child ) continue;
    child_ID    .push_back( AUXDYN( child, int, "ID"    ) );
    child_index .push_back( AUXDYN( child, int, "index" ) );
  }
  m_tp_child_ID    ->push_back( child_ID    );
  m_tp_child_index ->push_back( child_index );
  
  std::string pVtx_llpDecay = "";
  int         pVtx_ID       = AlgConsts::invalidInt;
  int         pVtx_index    = AlgConsts::invalidInt;
  int         pVtx_barcode  = AlgConsts::invalidInt;
  float       pVtx_r        = AlgConsts::invalidFloat;
  if ( truthPart->hasProdVtx() ) {
    const auto* pVtx = truthPart->prodVtx();
    if ( pVtx ) {
      for ( size_t i = 0; i != m_truthVtxLLPs.size(); ++i )
	if ( EJsHelper::pdgIdFuncs[m_truthVtxLLPs.at(i)]( pVtx ) ) pVtx_llpDecay = m_truthVtxLLPs.at(i);
      pVtx_ID              = AUXDYN( pVtx, int, "ID"    );
      pVtx_index           = AUXDYN( pVtx, int, "index" );
      pVtx_barcode         = pVtx->barcode();
      pVtx_r               = pVtx->perp();
    }
  }
  m_tp_pVtx          ->push_back( truthPart->hasProdVtx() );
  m_tp_pVtx_llpDecay ->push_back( pVtx_llpDecay           );
  m_tp_pVtx_ID       ->push_back( pVtx_ID                 );
  m_tp_pVtx_index    ->push_back( pVtx_index              );
  m_tp_pVtx_barcode  ->push_back( pVtx_barcode            );
  m_tp_pVtx_r        ->push_back( pVtx_r                  );
  
  std::string dVtx_llpDecay = "";
  int         dVtx_ID       = AlgConsts::invalidInt;
  int         dVtx_index    = AlgConsts::invalidInt;
  int         dVtx_barcode  = AlgConsts::invalidInt;
  float       dVtx_r        = AlgConsts::invalidFloat;
  if ( truthPart->hasDecayVtx() ) {
    const auto* dVtx = truthPart->decayVtx();
    if ( dVtx ) {
      for ( size_t i = 0; i != m_truthVtxLLPs.size(); ++i )
	if ( EJsHelper::pdgIdFuncs[m_truthVtxLLPs.at(i)]( dVtx ) ) dVtx_llpDecay = m_truthVtxLLPs.at(i);
      dVtx_ID              = AUXDYN( dVtx, int, "ID"    );
      dVtx_index           = AUXDYN( dVtx, int, "index" );
      dVtx_barcode         = dVtx->barcode();
      dVtx_r               = dVtx->perp();
    }
  }
  m_tp_dVtx          ->push_back( truthPart->hasDecayVtx() );
  m_tp_dVtx_llpDecay ->push_back( dVtx_llpDecay            );
  m_tp_dVtx_ID       ->push_back( dVtx_ID                  );
  m_tp_dVtx_index    ->push_back( dVtx_index               );
  m_tp_dVtx_barcode  ->push_back( dVtx_barcode             );
  m_tp_dVtx_r        ->push_back( dVtx_r                   );
  
  // jet matching (jets to which truth particles are dR-matched)
  uint8_t isTruthJetMatch  = false;
  if ( truthPart->isAvailable<char>("isMatchedToTruthJet") )
    isTruthJetMatch  = truthPart->auxdataConst<char>("isMatchedToTruthJet");
  uint8_t isDarkJetMatch   = false;
  if ( truthPart->isAvailable<char>("isMatchedToDarkJet")  )
    isDarkJetMatch   = truthPart->auxdataConst<char>("isMatchedToDarkJet");
  uint8_t isEMTopoJetMatch = false;
  std::string emtopo_str   = "";
  if ( truthPart->isAvailable<char>("isMatchedToRecoJet_EMTopo" + treeName) ) {
    isEMTopoJetMatch = truthPart->auxdataConst<char>("isMatchedToRecoJet_EMTopo" + treeName);
    emtopo_str       = treeName;
  }
  else if ( truthPart->isAvailable<char>("isMatchedToRecoJet_EMTopo") )
    isEMTopoJetMatch = truthPart->auxdataConst<char>("isMatchedToRecoJet_EMTopo");
  uint8_t isPFlowJetMatch  = false;
  std::string pflow_str    = "";
  if ( truthPart->isAvailable<char>("isMatchedToRecoJet_PFlow" + treeName) ) {
    isPFlowJetMatch  = truthPart->auxdataConst<char>("isMatchedToRecoJet_PFlow" + treeName);
    pflow_str        = treeName;
  }
  else if ( truthPart->isAvailable<char>("isMatchedToRecoJet_PFlow") )
    isPFlowJetMatch  = truthPart->auxdataConst<char>("isMatchedToRecoJet_PFlow");
  
  m_tp_truthJetMatch        ->push_back( isTruthJetMatch                                  );
  m_tp_truthJetMatch_ID     ->push_back( AUXDYN( truthPart, int,   "truthJetMatchID"    ) );
  m_tp_truthJetMatch_index  ->push_back( AUXDYN( truthPart, int,   "truthJetMatchIndex" ) );
  m_tp_truthJetMatch_dR     ->push_back( AUXDYN( truthPart, float, "truthJetMatchDR"    ) );
  m_tp_darkJetMatch         ->push_back( isDarkJetMatch                                   );
  m_tp_darkJetMatch_ID      ->push_back( AUXDYN( truthPart, int,   "darkJetMatchID"     ) );
  m_tp_darkJetMatch_index   ->push_back( AUXDYN( truthPart, int,   "darkJetMatchIndex"  ) );
  m_tp_darkJetMatch_dR      ->push_back( AUXDYN( truthPart, float, "darkJetMatchDR"     ) );
  if ( m_doEMTopoJets ) {
    m_tp_emtopoJetMatch       ->push_back( isEMTopoJetMatch                                                    );
    m_tp_emtopoJetMatch_ID    ->push_back( AUXDYN( truthPart, int,   "recoJetMatchID_EMTopo"    + emtopo_str ) );
    m_tp_emtopoJetMatch_index ->push_back( AUXDYN( truthPart, int,   "recoJetMatchIndex_EMTopo" + emtopo_str ) );
    m_tp_emtopoJetMatch_dR    ->push_back( AUXDYN( truthPart, float, "recoJetMatchDR_EMTopo"    + emtopo_str ) );
  }
  if ( m_doPFlowJets  ) {
    m_tp_pflowJetMatch        ->push_back( isPFlowJetMatch                                                     );
    m_tp_pflowJetMatch_ID     ->push_back( AUXDYN( truthPart, int,   "recoJetMatchID_PFlow"     + pflow_str  ) );
    m_tp_pflowJetMatch_index  ->push_back( AUXDYN( truthPart, int,   "recoJetMatchIndex_PFlow"  + pflow_str  ) );
    m_tp_pflowJetMatch_dR     ->push_back( AUXDYN( truthPart, float, "recoJetMatchDR_PFlow"     + pflow_str  ) );
  }
}

void EJsHelpTreeBase :: ClearTruthUser ( const std::string truthName )
{
  m_tp_ID                     ->clear();
  m_tp_index                  ->clear();
  m_tp_M                      ->clear();
  m_tp_charge                 ->clear();
  m_tp_isReco                 ->clear();
  m_tp_isSelected             ->clear();
  m_tp_isAssociated           ->clear();
  m_tp_recoProb               ->clear();
  m_tp_recoID                 ->clear();
  m_tp_recoIndex              ->clear();
  m_tp_isStable               ->clear();
  m_tp_isInteracting          ->clear();
  m_tp_isDark                 ->clear();
  m_tp_isDescendant           ->clear();
  m_tp_ancestor_llpDecay      ->clear();
  m_tp_ancestor_ID            ->clear();
  m_tp_ancestor_index         ->clear();
  m_tp_parent_ID              ->clear();
  m_tp_parent_index           ->clear();
  m_tp_child_ID               ->clear();
  m_tp_child_index            ->clear();
  m_tp_pVtx                   ->clear();
  m_tp_pVtx_llpDecay          ->clear();
  m_tp_pVtx_ID                ->clear();
  m_tp_pVtx_index             ->clear();
  m_tp_pVtx_barcode           ->clear();
  m_tp_pVtx_r                 ->clear();
  m_tp_dVtx                   ->clear();
  m_tp_dVtx_llpDecay          ->clear();
  m_tp_dVtx_ID                ->clear();
  m_tp_dVtx_index             ->clear();
  m_tp_dVtx_barcode           ->clear();
  m_tp_dVtx_r                 ->clear();
  m_tp_truthJetMatch          ->clear();
  m_tp_truthJetMatch_ID       ->clear();
  m_tp_truthJetMatch_index    ->clear();
  m_tp_truthJetMatch_dR       ->clear();
  m_tp_darkJetMatch           ->clear();
  m_tp_darkJetMatch_ID        ->clear();
  m_tp_darkJetMatch_index     ->clear();
  m_tp_darkJetMatch_dR        ->clear();
  if ( m_doEMTopoJets ) {
    m_tp_emtopoJetMatch       ->clear();
    m_tp_emtopoJetMatch_ID    ->clear();
    m_tp_emtopoJetMatch_index ->clear();
    m_tp_emtopoJetMatch_dR    ->clear();
  }
  if ( m_doPFlowJets ) {
    m_tp_pflowJetMatch        ->clear();
    m_tp_pflowJetMatch_ID     ->clear();
    m_tp_pflowJetMatch_index  ->clear();
    m_tp_pflowJetMatch_dR     ->clear();
  }
}



/***************
 * USER TRACKS *
 ***************/
void EJsHelpTreeBase :: AddTracksUser ( const std::string trackName, const std::string detailStr )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddTracksUser()", "adding EJs-user track variables" );
  
  setBranch<int>                        ( trackName, "ID",                           m_trk_ID                           );
  setBranch<int>                        ( trackName, "index",                        m_trk_index                        );
  setBranch<float>                      ( trackName, "M",                            m_trk_M                            );
  setBranch<float>                      ( trackName, "d0",                           m_trk_d0                           );
  setBranch<float>                      ( trackName, "errd0",                        m_trk_errd0                        );
  setBranch<float>                      ( trackName, "errz0",                        m_trk_errz0                        );
  setBranch<float>                      ( trackName, "chiSquared",                   m_trk_chiSquared                   );
  setBranch<float>                      ( trackName, "numberDoF",                    m_trk_numberDoF                    );
  setBranch<float>                      ( trackName, "chi2",                         m_trk_chi2                         );
  setBranch<float>                      ( trackName, "charge",                       m_trk_charge                       );
  setBranch<uint8_t>                    ( trackName, "nPixelHits",                   m_trk_nPixelHits                   );
  setBranch<uint8_t>                    ( trackName, "nPixelHoles",                  m_trk_nPixelHoles                  );
  setBranch<uint8_t>                    ( trackName, "nPixelSharedHits",             m_trk_nPixelSharedHits             );
  setBranch<uint8_t>                    ( trackName, "nPixelDeadSensors",            m_trk_nPixelDeadSensors            );
  setBranch<uint8_t>                    ( trackName, "expectInnerPixelLayerHit",     m_trk_expectInnerPixelLayerHit     );
  setBranch<uint8_t>                    ( trackName, "nInnerPixelLayerHits",         m_trk_nInnerPixelLayerHits         );
  setBranch<uint8_t>                    ( trackName, "expectNextInnerPixelLayerHit", m_trk_expectNextInnerPixelLayerHit );
  setBranch<uint8_t>                    ( trackName, "nNextInnerPixelLayerHits",     m_trk_nNextInnerPixelLayerHits     );
  setBranch<uint8_t>                    ( trackName, "nSCTHits",                     m_trk_nSCTHits                     );
  setBranch<uint8_t>                    ( trackName, "nSCTHoles",                    m_trk_nSCTHoles                    );
  setBranch<uint8_t>                    ( trackName, "nSCTSharedHits",               m_trk_nSCTSharedHits               );
  setBranch<uint8_t>                    ( trackName, "nSCTDeadSensors",              m_trk_nSCTDeadSensors              );
  setBranch<uint8_t>                    ( trackName, "nTRTHits",                     m_trk_nTRTHits                     );
  setBranch<uint8_t>                    ( trackName, "nTRTOutliers",                 m_trk_nTRTOutliers                 );
  setBranch<uint8_t>                    ( trackName, "isLRT",                        m_trk_isLRT                        );
  setBranch<uint8_t>                    ( trackName, "isSelected",                   m_trk_isSelected                   );
  setBranch<uint8_t>                    ( trackName, "isAssociated",                 m_trk_isAssociated                 );
  setBranch<uint8_t>                    ( trackName, "isSecVtxTrk",                  m_trk_isSecVtxTrk                  );
  setBranch<uint8_t>                    ( trackName, "isSecVtxCleanTrk",             m_trk_isSecVtxCleanTrk             );
  setBranch<uint8_t>                    ( trackName, "isSecVtxFiltTrk",              m_trk_isSecVtxFiltTrk              );
  setBranch<uint8_t>                    ( trackName, "isSecVtxFinalTrk",             m_trk_isSecVtxFinalTrk             );
  setBranch<int>                        ( trackName, "secVtxID",                     m_trk_secVtxID                     );
  setBranch<int>                        ( trackName, "secVtxIndex",                  m_trk_secVtxIndex                  );
  if ( m_isMC ) {
    setBranch<uint8_t>                  ( trackName, "isTruth",                      m_trk_isTruth                      );
    setBranch<float>                    ( trackName, "truthProb",                    m_trk_truthProb                    );
    setBranch<int>                      ( trackName, "truthID",                      m_trk_truthID                      );
    setBranch<int>                      ( trackName, "truthIndex",                   m_trk_truthIndex                   );
    setBranch<int>                      ( trackName, "truthBarcode",                 m_trk_truthBarcode                 );
    setBranch<int>                      ( trackName, "truthPdgId",                   m_trk_truthPdgId                   );
    setBranch<uint8_t>                  ( trackName, "truthIsDesc",                  m_trk_truthIsDesc                  );
    setBranch<std::vector<std::string>> ( trackName, "truthAncestorLLPDecay",        m_trk_truthAncestorLLPDecay        );
    setBranch<std::vector<int>>         ( trackName, "truthAncestorID",              m_trk_truthAncestorID              );
    setBranch<std::vector<int>>         ( trackName, "truthAncestorIndex",           m_trk_truthAncestorIndex           );
    setBranch<uint8_t>                  ( trackName, "truthJetMatch",                m_trk_truthJetMatch                );
    setBranch<int>                      ( trackName, "truthJetMatch_ID",             m_trk_truthJetMatch_ID             );
    setBranch<int>                      ( trackName, "truthJetMatch_index",          m_trk_truthJetMatch_index          );
    setBranch<float>                    ( trackName, "truthJetMatch_dR",             m_trk_truthJetMatch_dR             );
    setBranch<uint8_t>                  ( trackName, "darkJetMatch",                 m_trk_darkJetMatch                 );
    setBranch<int>                      ( trackName, "darkJetMatch_ID",              m_trk_darkJetMatch_ID              );
    setBranch<int>                      ( trackName, "darkJetMatch_index",           m_trk_darkJetMatch_index           );
    setBranch<float>                    ( trackName, "darkJetMatch_dR",              m_trk_darkJetMatch_dR              );
  }
  if ( m_doEMTopoJets ) {
    setBranch<uint8_t>                  ( trackName, "emtopoJetMatch",               m_trk_emtopoJetMatch               );
    setBranch<int>                      ( trackName, "emtopoJetMatch_ID",            m_trk_emtopoJetMatch_ID            );
    setBranch<int>                      ( trackName, "emtopoJetMatch_index",         m_trk_emtopoJetMatch_index         );
    setBranch<float>                    ( trackName, "emtopoJetMatch_dR",            m_trk_emtopoJetMatch_dR            );
  }
  if ( m_doPFlowJets ) {
    setBranch<uint8_t>                  ( trackName, "pflowJetMatch",                m_trk_pflowJetMatch                );
    setBranch<int>                      ( trackName, "pflowJetMatch_ID",             m_trk_pflowJetMatch_ID             );
    setBranch<int>                      ( trackName, "pflowJetMatch_index",          m_trk_pflowJetMatch_index          );
    setBranch<float>                    ( trackName, "pflowJetMatch_dR",             m_trk_pflowJetMatch_dR             );
  }
}

void EJsHelpTreeBase :: FillTracksUser ( const std::string trackName, const xAOD::TrackParticle* track )
{
  std::string treeName = m_treeName;
  if ( treeName == "nominal" ) treeName = "";
  
  bool is_selected = false;
  if ( track->isAvailable<char>("is_selected") )
    if ( track->auxdataConst<char>("is_selected") )
      is_selected = true;
  
  bool is_associated = false;
  if ( track->isAvailable<char>("is_associated") )
    if ( track->auxdataConst<char>("is_associated") )
      is_associated = true;
  
  m_trk_ID                      ->push_back( AUXDYN( track, int,     "ID"                                        ) );
  m_trk_index                   ->push_back( AUXDYN( track, int,     "index"                                     ) );
  m_trk_M                       ->push_back( track->m() / m_units                                                  );
  m_trk_d0                      ->push_back( track->d0()                                                           );
  m_trk_errd0                   ->push_back( track->definingParametersCovMatrix()(0,0)                             );
  m_trk_errz0                   ->push_back( track->definingParametersCovMatrix()(1,1)                             );
  m_trk_chiSquared              ->push_back( track->chiSquared()                                                   );
  m_trk_numberDoF               ->push_back( track->numberDoF()                                                    );
  m_trk_chi2                    ->push_back( track->chiSquared() / (track->numberDoF() + AlgConsts::infinitesimal) );
  m_trk_charge                  ->push_back( track->charge()                                                       );
  m_trk_isLRT                   ->push_back( track->patternRecoInfo().test(xAOD::SiSpacePointsSeedMaker_LargeD0)   );
  m_trk_isSelected              ->push_back( is_selected                                                           );
  m_trk_isAssociated            ->push_back( is_associated                                                         );


  // get track summary information
  uint8_t nPix       = 0;
  uint8_t nPixHole   = 0;
  uint8_t nPixShare  = 0;
  uint8_t nPixDead   = 0;
  uint8_t nInPix     = 0;
  uint8_t nNextInPix = 0;
  uint8_t nSCT       = 0;
  uint8_t nSCTHole   = 0;
  uint8_t nSCTShare  = 0;
  uint8_t nSCTDead   = 0;
  uint8_t nTRT       = 0;
  uint8_t nTRTOut    = 0;
  track->summaryValue( nPix,       xAOD::numberOfPixelHits                     );
  track->summaryValue( nPixHole,   xAOD::numberOfPixelHoles                    );
  track->summaryValue( nPixShare,  xAOD::numberOfPixelSharedHits               );
  track->summaryValue( nPixDead,   xAOD::numberOfPixelDeadSensors              );
  track->summaryValue( nInPix,     xAOD::numberOfInnermostPixelLayerHits       );
  track->summaryValue( nNextInPix, xAOD::numberOfNextToInnermostPixelLayerHits );
  track->summaryValue( nSCT,       xAOD::numberOfSCTHits                       );
  track->summaryValue( nSCTHole,   xAOD::numberOfSCTHoles                      );
  track->summaryValue( nSCTShare,  xAOD::numberOfSCTSharedHits                 );
  track->summaryValue( nSCTDead,   xAOD::numberOfSCTDeadSensors                );
  track->summaryValue( nTRT,       xAOD::numberOfTRTHits                       );
  track->summaryValue( nTRTOut,    xAOD::numberOfTRTOutliers                   );
  
  m_trk_nPixelHits                   ->push_back( nPix                                                           );
  m_trk_nPixelHoles                  ->push_back( nPixHole                                                       );
  m_trk_nPixelSharedHits             ->push_back( nPixShare                                                      );
  m_trk_nPixelDeadSensors            ->push_back( nPixDead                                                       );
  m_trk_expectInnerPixelLayerHit     ->push_back( AUXDYN( track, uint8_t, "expectInnermostPixelLayerHit"       ) );
  m_trk_nInnerPixelLayerHits         ->push_back( nNextInPix                                                     );
  m_trk_expectNextInnerPixelLayerHit ->push_back( AUXDYN( track, uint8_t, "expectNextToInnermostPixelLayerHit" ) );
  m_trk_nNextInnerPixelLayerHits     ->push_back( nNextInPix                                                     );
  m_trk_nSCTHits                     ->push_back( nSCT                                                           );
  m_trk_nSCTHoles                    ->push_back( nSCTHole                                                       );
  m_trk_nSCTSharedHits               ->push_back( nSCTShare                                                      );
  m_trk_nSCTDeadSensors              ->push_back( nSCTDead                                                       );
  m_trk_nTRTHits                     ->push_back( nTRT                                                           );
  m_trk_nTRTOutliers                 ->push_back( nTRTOut                                                        );
  

  // get linked secondary vertex
  bool trackIsSecVtxTrk      = false;
  bool trackIsSecVtxCleanTrk = false;
  bool trackIsSecVtxFiltTrk  = false;
  bool trackIsSecVtxFinalTrk = false;
  int  secVtxID              = AlgConsts::invalidInt;
  int  secVtxIndex           = AlgConsts::invalidInt;
  static SG::AuxElement::ConstAccessor<EJsHelper::VertexLink_t> secVtxAccess("secondaryVertexLink");
  if ( secVtxAccess.isAvailable( *track ) ) {
    try {
      const EJsHelper::VertexLink_t& secvtxlink = secVtxAccess( *track );
      if ( (*secvtxlink) ) trackIsSecVtxTrk = true;
      secVtxID    = AUXDYN( (*secvtxlink), int, "ID" );
      secVtxIndex = AUXDYN( (*secvtxlink), int, "index" );
    } catch(...) {}
  }
  if ( trackIsSecVtxTrk ) {
    trackIsSecVtxCleanTrk = AUXDYN( track, char, "isClean"        );
    trackIsSecVtxFiltTrk  = AUXDYN( track, char, "isFiltered"     );
    trackIsSecVtxFinalTrk = AUXDYN( track, char, "is_svtrk_final" );
  }
  m_trk_isSecVtxTrk         ->push_back( trackIsSecVtxTrk      );
  m_trk_isSecVtxCleanTrk    ->push_back( trackIsSecVtxCleanTrk );
  m_trk_isSecVtxFiltTrk     ->push_back( trackIsSecVtxFiltTrk  );
  m_trk_isSecVtxFinalTrk    ->push_back( trackIsSecVtxFinalTrk );
  m_trk_secVtxID            ->push_back( secVtxID              );
  m_trk_secVtxIndex         ->push_back( secVtxIndex           );

  // get linked truth particle
  if ( m_isMC ) {
    bool trackHasTruthLink = false;
    int  truthID           = AlgConsts::invalidInt;
    int  truthIndex        = AlgConsts::invalidInt;
    int  truthBarcode      = AlgConsts::invalidInt;
    int  truthPdgId        = AlgConsts::invalidInt;
    bool truthIsDesc       = false;
    std::vector<std::string> truthAncestor_llpDecay;
    std::vector<int>         truthAncestor_ID;
    std::vector<int>         truthAncestor_index;
    static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLink_t> truthAccess("truthParticleLink");
    if ( truthAccess.isAvailable( *track ) ) {
      try {
	const EJsHelper::TruthParticleLink_t& truthlink = truthAccess( *track );
	if ( (*truthlink) ) trackHasTruthLink = true;
	truthID      = AUXDYN( (*truthlink), int, "ID"                           );
	truthIndex   = AUXDYN( (*truthlink), int, "index"                        );
	truthBarcode = (*truthlink)->barcode();
	truthPdgId   = (*truthlink)->pdgId();
	truthIsDesc  = AUXDYN( (*truthlink), char, "isReconstructibleDescendant" );

	static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLinkVector_t>
	  truthAncestorAccess("truthVertexAncestorLinks");
	if ( truthAncestorAccess.isAvailable( **truthlink ) ) {
	  const EJsHelper::TruthVertexLinkVector_t& truthAncestorVtxLinks = truthAncestorAccess( **truthlink );
	  for ( const auto& truthancestorlink : truthAncestorVtxLinks ) {
	    if ( !truthancestorlink.isValid() ) continue;
	    std::string llpDecayType = "";
	    for ( size_t i = 0; i != m_truthVtxLLPs.size(); ++i )
	      if ( EJsHelper::pdgIdFuncs[m_truthVtxLLPs.at(i)]( *truthancestorlink ) ) llpDecayType = m_truthVtxLLPs.at(i);
	    truthAncestor_llpDecay .push_back( llpDecayType                                 );
	    truthAncestor_ID       .push_back( AUXDYN( (*truthancestorlink), int, "ID"    ) );
	    truthAncestor_index    .push_back( AUXDYN( (*truthancestorlink), int, "index" ) );
	  }
	}
      } catch(...) {}
    }
    m_trk_isTruth               ->push_back( trackHasTruthLink                                   );
    m_trk_truthProb             ->push_back( track->auxdataConst<float>("truthMatchProbability") );
    m_trk_truthID               ->push_back( truthID                                             );
    m_trk_truthIndex            ->push_back( truthIndex                                          );
    m_trk_truthBarcode          ->push_back( truthBarcode                                        );
    m_trk_truthPdgId            ->push_back( truthPdgId                                          );
    m_trk_truthIsDesc           ->push_back( truthIsDesc                                         );
    m_trk_truthAncestorLLPDecay ->push_back( truthAncestor_llpDecay                              );
    m_trk_truthAncestorID       ->push_back( truthAncestor_ID                                    );
    m_trk_truthAncestorIndex    ->push_back( truthAncestor_index                                 );
  }

  // jet matching (jets to which tracks are dR-matched)
  uint8_t isTruthJetMatch  = false;
  if ( track->isAvailable<char>("isMatchedToTruthJet") )
    isTruthJetMatch  = track->auxdataConst<char>("isMatchedToTruthJet");
  uint8_t isDarkJetMatch   = false;
  if ( track->isAvailable<char>("isMatchedToDarkJet")  )
    isDarkJetMatch   = track->auxdataConst<char>("isMatchedToDarkJet");
  uint8_t isEMTopoJetMatch = false;
  std::string emtopo_str   = "";
  if ( track->isAvailable<char>("isMatchedToRecoJet_EMTopo" + treeName) ) {
    isEMTopoJetMatch = track->auxdataConst<char>("isMatchedToRecoJet_EMTopo" + treeName);
    emtopo_str       = treeName;
  }
  else if ( track->isAvailable<char>("isMatchedToRecoJet_EMTopo") )
    isEMTopoJetMatch = track->auxdataConst<char>("isMatchedToRecoJet_EMTopo");
  uint8_t isPFlowJetMatch  = false;
  std::string pflow_str    = "";
  if ( track->isAvailable<char>("isMatchedToRecoJet_PFlow" + treeName) ) {
    isPFlowJetMatch  = track->auxdataConst<char>("isMatchedToRecoJet_PFlow" + treeName);
    pflow_str        = treeName;
  }
  else if ( track->isAvailable<char>("isMatchedToRecoJet_PFlow") )
    isPFlowJetMatch  = track->auxdataConst<char>("isMatchedToRecoJet_PFlow");

  if ( m_isMC ) {
    m_trk_truthJetMatch        ->push_back( isTruthJetMatch                              );
    m_trk_truthJetMatch_ID     ->push_back( AUXDYN( track, int,   "truthJetMatchID"    ) );
    m_trk_truthJetMatch_index  ->push_back( AUXDYN( track, int,   "truthJetMatchIndex" ) );
    m_trk_truthJetMatch_dR     ->push_back( AUXDYN( track, float, "truthJetMatchDR"    ) );
    m_trk_darkJetMatch         ->push_back( isDarkJetMatch                               );
    m_trk_darkJetMatch_ID      ->push_back( AUXDYN( track, int,   "darkJetMatchID"     ) );
    m_trk_darkJetMatch_index   ->push_back( AUXDYN( track, int,   "darkJetMatchIndex"  ) );
    m_trk_darkJetMatch_dR      ->push_back( AUXDYN( track, float, "darkJetMatchDR"     ) );
  }
  if ( m_doEMTopoJets ) {
    m_trk_emtopoJetMatch       ->push_back( isEMTopoJetMatch                                                );
    m_trk_emtopoJetMatch_ID    ->push_back( AUXDYN( track, int,   "recoJetMatchID_EMTopo"    + emtopo_str ) );
    m_trk_emtopoJetMatch_index ->push_back( AUXDYN( track, int,   "recoJetMatchIndex_EMTopo" + emtopo_str ) );
    m_trk_emtopoJetMatch_dR    ->push_back( AUXDYN( track, float, "recoJetMatchDR_EMTopo"    + emtopo_str ) );
  }
  if ( m_doPFlowJets  ) {
    m_trk_pflowJetMatch        ->push_back( isPFlowJetMatch                                                 );
    m_trk_pflowJetMatch_ID     ->push_back( AUXDYN( track, int,   "recoJetMatchID_PFlow"     + pflow_str  ) );
    m_trk_pflowJetMatch_index  ->push_back( AUXDYN( track, int,   "recoJetMatchIndex_PFlow"  + pflow_str  ) );
    m_trk_pflowJetMatch_dR     ->push_back( AUXDYN( track, float, "recoJetMatchDR_PFlow"     + pflow_str  ) );
  }
}

void EJsHelpTreeBase :: ClearTracksUser ( const std::string trackName )
{
  m_trk_ID                           ->clear();
  m_trk_index                        ->clear();
  m_trk_M                            ->clear();
  m_trk_d0                           ->clear();
  m_trk_errd0                        ->clear();
  m_trk_errz0                        ->clear();
  m_trk_chiSquared                   ->clear();
  m_trk_numberDoF                    ->clear();
  m_trk_chi2                         ->clear();
  m_trk_charge                       ->clear();
  m_trk_nPixelHits                   ->clear();
  m_trk_nPixelHoles                  ->clear();
  m_trk_nPixelSharedHits             ->clear();
  m_trk_nPixelDeadSensors            ->clear();
  m_trk_expectInnerPixelLayerHit     ->clear();
  m_trk_nInnerPixelLayerHits         ->clear();
  m_trk_expectNextInnerPixelLayerHit ->clear();
  m_trk_nNextInnerPixelLayerHits     ->clear();
  m_trk_nSCTHits                     ->clear();
  m_trk_nSCTHoles                    ->clear();
  m_trk_nSCTSharedHits               ->clear();
  m_trk_nSCTDeadSensors              ->clear();
  m_trk_nTRTHits                     ->clear();
  m_trk_nTRTOutliers                 ->clear();
  m_trk_isLRT                        ->clear();
  m_trk_isSelected                   ->clear();
  m_trk_isAssociated                 ->clear();
  m_trk_isSecVtxTrk                  ->clear();
  m_trk_isSecVtxCleanTrk             ->clear();
  m_trk_isSecVtxFiltTrk              ->clear();
  m_trk_isSecVtxFinalTrk             ->clear();
  m_trk_secVtxID                     ->clear();
  m_trk_secVtxIndex                  ->clear();
  if ( m_isMC ) {
    m_trk_isTruth                    ->clear();
    m_trk_truthProb                  ->clear();
    m_trk_truthID                    ->clear();
    m_trk_truthIndex                 ->clear();
    m_trk_truthBarcode               ->clear();
    m_trk_truthPdgId                 ->clear();
    m_trk_truthIsDesc                ->clear();
    m_trk_truthAncestorLLPDecay      ->clear();
    m_trk_truthAncestorID            ->clear();
    m_trk_truthAncestorIndex         ->clear();
    m_trk_truthJetMatch              ->clear();
    m_trk_truthJetMatch_ID           ->clear();
    m_trk_truthJetMatch_index        ->clear();
    m_trk_truthJetMatch_dR           ->clear();
    m_trk_darkJetMatch               ->clear();
    m_trk_darkJetMatch_ID            ->clear();
    m_trk_darkJetMatch_index         ->clear();
    m_trk_darkJetMatch_dR            ->clear();
  }
  if ( m_doEMTopoJets ) {
    m_trk_emtopoJetMatch              ->clear();
    m_trk_emtopoJetMatch_ID           ->clear();
    m_trk_emtopoJetMatch_index        ->clear();
    m_trk_emtopoJetMatch_dR           ->clear();
  }
  if ( m_doPFlowJets ) {
    m_trk_pflowJetMatch              ->clear();
    m_trk_pflowJetMatch_ID           ->clear();
    m_trk_pflowJetMatch_index        ->clear();
    m_trk_pflowJetMatch_dR           ->clear();
  }
}
