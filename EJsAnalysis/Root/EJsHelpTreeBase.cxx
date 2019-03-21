#include "EJsAnalysis/EJsHelpTreeBase.h"
#include "EJsAnalysis/EJsHelperFunctions.h"
#include "EJsAnalysis/AlgConsts.h"


EJsHelpTreeBase :: EJsHelpTreeBase ( xAOD::TEvent* event, TTree* tree, TFile* file, const float units,
				     bool debug, xAOD::TStore* store, bool emtopo, bool pflow ) :
  HelpTreeBase ( event, tree, file, units, debug, store )
{
  if ( m_debug ) Info( "EJsHelpTreeBase()", "creating output EJs TTree" );

  m_treeName = m_tree->GetName();
  
  m_doEMTopoJets = emtopo;
  m_doPFlowJets  = pflow;
  
  m_pv_x        = 0;
  m_pv_y        = 0;
  m_pv_z        = 0;
  m_pv_r        = 0;
  m_pv_phi      = 0;
  m_pv_nTracks  = 0;
  m_pv_location = 0;

  m_eventIsMC = 0;

  m_signalTrig          = 0;
  m_validTrig           = 0;
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
    m_cleanJets_emtopo    = 0;
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
    m_cleanJets_pflow     = 0;
  }
  
  m_tp_ID               = new std::vector<int>;
  m_tp_M                = new std::vector<float>;
  m_tp_charge           = new std::vector<float>;
  m_tp_isReco           = new std::vector<uint8_t>;
  m_tp_recoProb         = new std::vector<float>;
  m_tp_recoID           = new std::vector<int>;
  m_tp_recoIsSelected   = new std::vector<uint8_t>;
  m_tp_recoIsAssociated = new std::vector<uint8_t>;
  m_tp_isStable         = new std::vector<uint8_t>;
  m_tp_isInteracting    = new std::vector<uint8_t>;
  m_tp_isReconstructible = new std::vector<uint8_t>;
  m_tp_isDark            = new std::vector<uint8_t>;

  m_tp_parent_ID                = new std::vector<std::vector<int>>;
  m_tp_parent_isReco            = new std::vector<std::vector<uint8_t>>;
  m_tp_parent_recoProb          = new std::vector<std::vector<float>>;
  m_tp_parent_recoID            = new std::vector<std::vector<int>>;
  m_tp_parent_isStable          = new std::vector<std::vector<uint8_t>>;
  m_tp_parent_isInteracting     = new std::vector<std::vector<uint8_t>>;
  m_tp_parent_isReconstructible = new std::vector<std::vector<uint8_t>>;
  m_tp_parent_isDark            = new std::vector<std::vector<uint8_t>>;

  m_tp_child_ID                = new std::vector<std::vector<int>>;
  m_tp_child_isReco            = new std::vector<std::vector<uint8_t>>;
  m_tp_child_recoProb          = new std::vector<std::vector<float>>;
  m_tp_child_recoID            = new std::vector<std::vector<int>>;
  m_tp_child_isStable          = new std::vector<std::vector<uint8_t>>;
  m_tp_child_isInteracting     = new std::vector<std::vector<uint8_t>>;
  m_tp_child_isReconstructible = new std::vector<std::vector<uint8_t>>;
  m_tp_child_isDark            = new std::vector<std::vector<uint8_t>>;

  m_tp_pVtx                 = new std::vector<uint8_t>;
  m_tp_pVtx_isDarkPionDecay = new std::vector<uint8_t>;
  m_tp_pVtx_ID              = new std::vector<int>;
  m_tp_pVtx_barcode         = new std::vector<int>;
  m_tp_pVtx_r               = new std::vector<float>;

  m_tp_dVtx                 = new std::vector<uint8_t>;
  m_tp_dVtx_isDarkPionDecay = new std::vector<uint8_t>;
  m_tp_dVtx_ID              = new std::vector<int>;
  m_tp_dVtx_barcode         = new std::vector<int>;
  m_tp_dVtx_r               = new std::vector<float>;

  m_tp_truthJetMatch     = new std::vector<uint8_t>;
  m_tp_truthJetMatch_ID  = new std::vector<std::vector<int>>;
  m_tp_truthJetMatch_dR  = new std::vector<std::vector<float>>;
  m_tp_darkJetMatch      = new std::vector<uint8_t>;
  m_tp_darkJetMatch_ID   = new std::vector<std::vector<int>>;
  m_tp_darkJetMatch_dR   = new std::vector<std::vector<float>>;
  if ( m_doEMTopoJets ) {
    m_tp_emtopoJetMatch    = new std::vector<uint8_t>;
    m_tp_emtopoJetMatch_ID = new std::vector<std::vector<int>>;
    m_tp_emtopoJetMatch_dR = new std::vector<std::vector<float>>;
  }
  if ( m_doPFlowJets ) {
    m_tp_pflowJetMatch     = new std::vector<uint8_t>;
    m_tp_pflowJetMatch_ID  = new std::vector<std::vector<int>>;
    m_tp_pflowJetMatch_dR  = new std::vector<std::vector<float>>;
  }

  m_trk_ID           = new std::vector<int>;
  m_trk_d0           = new std::vector<float>;
  m_trk_errd0        = new std::vector<float>;
  m_trk_errz0        = new std::vector<float>;
  m_trk_chi2         = new std::vector<float>;
  m_trk_isSelected   = new std::vector<uint8_t>;
  m_trk_isAssociated = new std::vector<uint8_t>;
  m_trk_nSelected   = 0;
  m_trk_nAssociated = 0;
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
  
  m_truthVerts[ truthVtxName ] = new EJs::TruthVertexContainer( truthVtxName, detailStr, m_units, m_isMC, m_doEMTopoJets, m_doPFlowJets );
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
  //std::string treeName = m_tree->GetName();
  EJs::TruthVertexContainer* thisTruthVtx = m_truthVerts[ truthVtxName ];
  thisTruthVtx->FillTruthVertex( truthVtx, m_treeName );
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

void EJsHelpTreeBase :: FillSecondaryVerts ( const xAOD::VertexContainer* secVerts, const std::string secVtxName )
{
  this->ClearSecondaryVerts ( secVtxName );

  for ( const auto& secVtx : *secVerts )
    this->FillSecondaryVertex( secVtx, secVtxName );
}

void EJsHelpTreeBase :: FillSecondaryVertex ( const xAOD::Vertex* secVtx, const std::string secVtxName )
{
  //std::string treeName = m_tree->GetName();
  EJs::SecondaryVertexContainer* thisSecVtx = m_secVerts[ secVtxName ];
  thisSecVtx->FillSecondaryVertex( secVtx, m_treeName );
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
  m_tree->Branch( "PV_nTracks",  &m_pv_nTracks,  "PV_nTracks/i"  );
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



/*************
 * USER EVENTS *
 *************/

void EJsHelpTreeBase :: AddEventUser ( const std::string detailStr )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddEventUser()", "adding EJs-user event variables" );

  m_tree->Branch( "isMC", &m_eventIsMC );

  m_tree->Branch( "passesSignalTrigger", &m_signalTrig );
  m_tree->Branch( "passesValidTrigger",  &m_validTrig  );
  
  if ( m_doEMTopoJets ) {
    m_tree->Branch( "isSignal_EMTopo", &m_signal_emtopo );
    m_tree->Branch( "isValid_EMTopo",  &m_valid_emtopo  );
    m_tree->Branch( "isCtrl_EMTopo",   &m_ctrl_emtopo   );

    m_tree->Branch( "passesSignalNJet_EMTopo",   &m_signalNJet_emtopo   );
    m_tree->Branch( "passesSignalJetPt_EMTopo",  &m_signalJetPt_emtopo  );
    m_tree->Branch( "passesSignalJetEta_EMTopo", &m_signalJetEta_emtopo );
    m_tree->Branch( "passesSignalNJetHt_EMTopo", &m_signalNJetHt_emtopo );
  
    m_tree->Branch( "passesValidNJetMin_EMTopo", &m_validNJetMin_emtopo );
    m_tree->Branch( "passesValidNJetMax_EMTopo", &m_validNJetMax_emtopo );
    m_tree->Branch( "passesValidJetPt_EMTopo",   &m_validJetPt_emtopo   );
    m_tree->Branch( "passesValidJetEta_EMTopo",  &m_validJetEta_emtopo  );
    
    m_tree->Branch( "NJetHt_EMTopo", &m_njetHt_emtopo );

    m_tree->Branch( "cleanJetEvent_EMTopo", &m_cleanJets_emtopo );
  }
  
  if ( m_doPFlowJets ) {
    m_tree->Branch( "isSignal_PFlow", &m_signal_pflow );
    m_tree->Branch( "isValid_PFlow",  &m_valid_pflow  );
    m_tree->Branch( "isCtrl_PFlow",   &m_ctrl_pflow   );

    m_tree->Branch( "passesSignalNJet_PFlow",   &m_signalNJet_pflow   );
    m_tree->Branch( "passesSignalJetPt_PFlow",  &m_signalJetPt_pflow  );
    m_tree->Branch( "passesSignalJetEta_PFlow", &m_signalJetEta_pflow );
    m_tree->Branch( "passesSignalNJetHt_PFlow", &m_signalNJetHt_pflow );
    
    m_tree->Branch( "passesValidNJetMin_PFlow", &m_validNJetMin_pflow );
    m_tree->Branch( "passesValidNJetMax_PFlow", &m_validNJetMax_pflow );
    m_tree->Branch( "passesValidJetPt_PFlow",   &m_validJetPt_pflow   );
    m_tree->Branch( "passesValidJetEta_PFlow",  &m_validJetEta_pflow  );
  
    m_tree->Branch( "NJetHt_PFlow", &m_njetHt_pflow );

    m_tree->Branch( "cleanJetEvent_PFlow", &m_cleanJets_pflow );
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

    if ( event->isAvailable<char>( "cleanEvent_JetSelect_AntiKt4EMTopo" ) )
      m_cleanJets_emtopo = event->auxdataConst<char>( "cleanEvent_JetSelect_AntiKt4EMTopo" );
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

    if ( event->isAvailable<char>( "cleanEvent_JetSelect_AntiKt4EMPFlow" ) )
      m_cleanJets_pflow = event->auxdataConst<char>( "cleanEvent_JetSelect_AntiKt4EMPFlow" );
  }
    
}

void EJsHelpTreeBase :: ClearEventUser ( )
{
  m_eventIsMC = 0;
  
  m_signalTrig = 0;
  m_validTrig  = 0;

  if ( m_doEMTopoJets ) {
    m_signal_emtopo = 0;
    m_valid_emtopo  = 0;
    m_ctrl_emtopo   = 0;
    
    m_signalNJet_emtopo   = 0;
    m_signalJetPt_emtopo  = 0;
    m_signalJetEta_emtopo = 0;
    m_signalNJetHt_emtopo = 0;
    
    m_validNJetMin_emtopo = 0;
    m_validNJetMax_emtopo = 0;
    m_validJetPt_emtopo   = 0;
    m_validJetEta_emtopo  = 0;
    
    m_njetHt_emtopo = 0;

    m_cleanJets_emtopo = 0;
  }

  if ( m_doPFlowJets ) {
    m_signal_pflow = 0;
    m_valid_pflow  = 0;
    m_ctrl_pflow   = 0;
    
    m_signalNJet_pflow   = 0;  
    m_signalJetPt_pflow  = 0; 
    m_signalJetEta_pflow = 0;
    m_signalNJetHt_pflow = 0;
    
    m_validNJetMin_pflow = 0; 
    m_validNJetMax_pflow = 0; 
    m_validJetPt_pflow   = 0; 
    m_validJetEta_pflow  = 0;
    
    m_njetHt_pflow = 0;

    m_cleanJets_pflow = 0;
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
  //std::string treeName = m_tree->GetName();
  EJs::JetContainer* thisJet = m_jets[ jetName ];
  thisJet->FillJet( jet, m_treeName );
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

  setBranch<int>     ( truthName, "ID",                m_tp_ID                );
  setBranch<float>   ( truthName, "M",                 m_tp_M                 );
  setBranch<float>   ( truthName, "charge",            m_tp_charge            );
  setBranch<uint8_t> ( truthName, "isReco",            m_tp_isReco            );
  setBranch<float>   ( truthName, "recoProb",          m_tp_recoProb          );
  setBranch<int>     ( truthName, "recoID",            m_tp_recoID            );
  setBranch<uint8_t> ( truthName, "recoIsSelected",    m_tp_recoIsSelected    );
  setBranch<uint8_t> ( truthName, "recoIsAssociated",  m_tp_recoIsAssociated  );
  setBranch<uint8_t> ( truthName, "isStable",          m_tp_isStable          );
  setBranch<uint8_t> ( truthName, "isInteracting",     m_tp_isInteracting     );
  setBranch<uint8_t> ( truthName, "isReconstructible", m_tp_isReconstructible );
  setBranch<uint8_t> ( truthName, "isDark",            m_tp_isDark            );

  setBranch<std::vector<int>>     ( truthName, "parent_ID",                m_tp_parent_ID                );
  setBranch<std::vector<uint8_t>> ( truthName, "parent_isReco",            m_tp_parent_isReco            );
  setBranch<std::vector<float>>   ( truthName, "parent_recoProb",          m_tp_parent_recoProb          );
  setBranch<std::vector<int>>     ( truthName, "parent_recoID",            m_tp_parent_recoID            );
  setBranch<std::vector<uint8_t>> ( truthName, "parent_isStable",          m_tp_parent_isStable          );
  setBranch<std::vector<uint8_t>> ( truthName, "parent_isInteracting",     m_tp_parent_isInteracting     );
  setBranch<std::vector<uint8_t>> ( truthName, "parent_isReconstructible", m_tp_parent_isReconstructible );
  setBranch<std::vector<uint8_t>> ( truthName, "parent_isDark",            m_tp_parent_isDark            );

  setBranch<std::vector<int>>     ( truthName, "child_ID",                m_tp_child_ID                );
  setBranch<std::vector<uint8_t>> ( truthName, "child_isReco",            m_tp_child_isReco            );
  setBranch<std::vector<float>>   ( truthName, "child_recoProb",          m_tp_child_recoProb          );
  setBranch<std::vector<int>>     ( truthName, "child_recoID",            m_tp_child_recoID            );
  setBranch<std::vector<uint8_t>> ( truthName, "child_isStable",          m_tp_child_isStable          );
  setBranch<std::vector<uint8_t>> ( truthName, "child_isInteracting",     m_tp_child_isInteracting     );
  setBranch<std::vector<uint8_t>> ( truthName, "child_isReconstructible", m_tp_child_isReconstructible );
  setBranch<std::vector<uint8_t>> ( truthName, "child_isDark",            m_tp_child_isDark            );

  setBranch<uint8_t> ( truthName, "hasProdVtx",              m_tp_pVtx                 );
  setBranch<uint8_t> ( truthName, "prodVtx_isDarkPionDecay", m_tp_pVtx_isDarkPionDecay );
  setBranch<int>     ( truthName, "prodVtx_ID",              m_tp_pVtx_ID              );
  setBranch<int>     ( truthName, "prodVtx_barcode",         m_tp_pVtx_barcode         );
  setBranch<float>   ( truthName, "prodVtx_r",               m_tp_pVtx_r               );

  setBranch<uint8_t> ( truthName, "hasDecayVtx",              m_tp_dVtx                 );
  setBranch<uint8_t> ( truthName, "decayVtx_isDarkPionDecay", m_tp_dVtx_isDarkPionDecay );
  setBranch<int>     ( truthName, "decayVtx_ID",              m_tp_dVtx_ID              );
  setBranch<int>     ( truthName, "decayVtx_barcode",         m_tp_dVtx_barcode         );
  setBranch<float>   ( truthName, "decayVtx_r",               m_tp_dVtx_r               );

  setBranch<uint8_t>              ( truthName, "isTruthJetMatched",  m_tp_truthJetMatch     );
  setBranch<std::vector<int>>     ( truthName, "truthJetMatch_ID",   m_tp_truthJetMatch_ID  );
  setBranch<std::vector<float>>   ( truthName, "truthJetMatch_dR",   m_tp_truthJetMatch_dR  );
  setBranch<uint8_t>              ( truthName, "isDarkJetMatched",   m_tp_darkJetMatch      );
  setBranch<std::vector<int>>     ( truthName, "darkJetMatch_ID",    m_tp_darkJetMatch_ID   );
  setBranch<std::vector<float>>   ( truthName, "darkJetMatch_dR",    m_tp_darkJetMatch_dR   );
  if ( m_doEMTopoJets ) {
    setBranch<uint8_t>            ( truthName, "isEMTopoJetMatched", m_tp_emtopoJetMatch    );
    setBranch<std::vector<int>>   ( truthName, "EMTopoJetMatch_ID",  m_tp_emtopoJetMatch_ID );
    setBranch<std::vector<float>> ( truthName, "EMTopoJetMatch_dR",  m_tp_emtopoJetMatch_dR );
  }
  if ( m_doPFlowJets ) {
    setBranch<uint8_t>            ( truthName, "isPFlowJetMatched",  m_tp_pflowJetMatch     );
    setBranch<std::vector<int>>   ( truthName, "PFlowJetMatch_ID",   m_tp_pflowJetMatch_ID  );
    setBranch<std::vector<float>> ( truthName, "PFlowJetMatch_dR",   m_tp_pflowJetMatch_dR  );
  }
}

void EJsHelpTreeBase :: FillTruthUser ( const std::string truthName, const xAOD::TruthParticle* truthPart )
{
  std::string treeName = m_treeName;
  if ( treeName == "nominal" ) treeName = "";
  
  int     tp_recoID      = 0;
  uint8_t tp_recoIsSel   = 0;
  uint8_t tp_recoIsAssoc = 0;
  static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> recoAccess("trackLink");
  if ( recoAccess.isAvailable( *truthPart ) ) {
    try {
      const EJsHelper::TrackLink_t& recoLink = recoAccess( *truthPart );
      tp_recoID      = AUXDYN( (*recoLink), int,   "ID"           );
      tp_recoIsSel   = AUXDYN( (*recoLink), char, "is_selected"   );
      tp_recoIsAssoc = AUXDYN( (*recoLink), char, "is_associated" );
    } catch(...) {}
  }
  m_tp_ID                ->push_back( AUXDYN( truthPart, int,    "ID"                    ) );
  m_tp_M                 ->push_back( truthPart->m() / m_units                             );
  m_tp_charge            ->push_back( truthPart->charge()                                  );
  m_tp_isReco            ->push_back( AUXDYN( truthPart, char,   "isTrackMatch"          ) );
  m_tp_recoProb          ->push_back( AUXDYN( truthPart, double, "trackMatchProbability" ) );
  m_tp_recoID            ->push_back( tp_recoID      );
  m_tp_recoIsSelected    ->push_back( tp_recoIsSel   );
  m_tp_recoIsAssociated  ->push_back( tp_recoIsAssoc );
  m_tp_isStable          ->push_back( EJsHelper::isStable          ( truthPart ) );
  m_tp_isInteracting     ->push_back( EJsHelper::isInteracting     ( truthPart ) );
  m_tp_isReconstructible ->push_back( EJsHelper::isReconstructible ( truthPart ) );
  m_tp_isDark            ->push_back( EJsHelper::isDark            ( truthPart ) );

  std::vector<int>     parent_ID;
  std::vector<uint8_t> parent_isReco;
  std::vector<float>   parent_recoProb;
  std::vector<int>     parent_recoID;
  std::vector<uint8_t> parent_isStable;
  std::vector<uint8_t> parent_isInteracting;
  std::vector<uint8_t> parent_isReconstructible;
  std::vector<uint8_t> parent_isDark;
  for ( size_t i = 0; i != truthPart->nParents(); ++i ) {
    const auto* parent = truthPart->parent(i);
    if ( !parent ) continue;
    parent_ID       .push_back( AUXDYN( parent, int,    "ID"                    ) );
    parent_isReco   .push_back( AUXDYN( parent, char,   "isTrackMatch"          ) );
    parent_recoProb .push_back( AUXDYN( parent, double, "trackMatchProbability" ) );
    static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> parentRecoAccess("trackLink");
    if ( parentRecoAccess.isAvailable( *parent ) ) {
      try {
	const EJsHelper::TrackLink_t& parentRecoLink = parentRecoAccess( *parent );
	parent_recoID .push_back( AUXDYN( (*parentRecoLink), int, "ID" ) );
      } catch(...) {}
    }
    parent_isStable          .push_back( EJsHelper::isStable          ( parent ) );
    parent_isInteracting     .push_back( EJsHelper::isInteracting     ( parent ) );
    parent_isReconstructible .push_back( EJsHelper::isReconstructible ( parent ) );
    parent_isDark            .push_back( EJsHelper::isDark            ( parent ) );
  }
  m_tp_parent_ID                ->push_back( parent_ID                );
  m_tp_parent_isReco            ->push_back( parent_isReco            );
  m_tp_parent_recoProb          ->push_back( parent_recoProb          );
  m_tp_parent_recoID            ->push_back( parent_recoID            );
  m_tp_parent_isStable          ->push_back( parent_isStable          );
  m_tp_parent_isInteracting     ->push_back( parent_isInteracting     );
  m_tp_parent_isReconstructible ->push_back( parent_isReconstructible );
  m_tp_parent_isDark            ->push_back( parent_isDark            );

  std::vector<int>     child_ID;
  std::vector<uint8_t> child_isReco;
  std::vector<float>   child_recoProb;
  std::vector<int>     child_recoID;
  std::vector<uint8_t> child_isStable;
  std::vector<uint8_t> child_isInteracting;
  std::vector<uint8_t> child_isReconstructible;
  std::vector<uint8_t> child_isDark;
  for ( size_t i = 0; i != truthPart->nChildren(); ++i ) {
    const auto* child = truthPart->child(i);
    if ( !child ) continue;
    child_ID .push_back( AUXDYN( child, int, "ID" ) );
    child_isReco .push_back( AUXDYN( child, char, "isTrackMatch" ) );
    child_recoProb .push_back( AUXDYN( child, double, "trackMatchProbability" ) );
    static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> childRecoAccess("trackLink");
    if ( childRecoAccess.isAvailable( *child ) ) {
      try {
  	const EJsHelper::TrackLink_t& childRecoLink = childRecoAccess( *child );
  	child_recoID .push_back( AUXDYN( (*childRecoLink), int, "ID" ) );
      } catch(...) {}
    }
    child_isStable          .push_back( EJsHelper::isStable          ( child ) );
    child_isInteracting     .push_back( EJsHelper::isInteracting     ( child ) );
    child_isReconstructible .push_back( EJsHelper::isReconstructible ( child ) );
    child_isDark            .push_back( EJsHelper::isDark            ( child ) );
  }
  m_tp_child_ID                ->push_back( child_ID                );
  m_tp_child_isReco            ->push_back( child_isReco            );
  m_tp_child_recoProb          ->push_back( child_recoProb          );
  m_tp_child_recoID            ->push_back( child_recoID            );
  m_tp_child_isStable          ->push_back( child_isStable          );
  m_tp_child_isInteracting     ->push_back( child_isInteracting     );
  m_tp_child_isReconstructible ->push_back( child_isReconstructible );
  m_tp_child_isDark            ->push_back( child_isDark            );

  bool  pVtx_isDarkPionDecay = false;
  int   pVtx_ID              = AlgConsts::invalidInt;
  int   pVtx_barcode         = AlgConsts::invalidInt;
  float pVtx_r               = AlgConsts::invalidFloat;
  if ( truthPart->hasProdVtx() ) {
    const auto* pVtx = truthPart->prodVtx();
    if ( pVtx ) {
      pVtx_isDarkPionDecay = EJsHelper::selectDarkPion( pVtx );
      pVtx_ID              = AUXDYN( pVtx, int, "ID" );
      pVtx_barcode         = pVtx->barcode();
      pVtx_r               = pVtx->perp();
    }
  }
  m_tp_pVtx                 ->push_back( truthPart->hasProdVtx() );
  m_tp_pVtx_isDarkPionDecay ->push_back( pVtx_isDarkPionDecay    );
  m_tp_pVtx_ID              ->push_back( pVtx_ID                 );
  m_tp_pVtx_barcode         ->push_back( pVtx_barcode            );
  m_tp_pVtx_r               ->push_back( pVtx_r                  );

  bool  dVtx_isDarkPionDecay = false;
  int   dVtx_ID              = AlgConsts::invalidInt;
  int   dVtx_barcode         = AlgConsts::invalidInt;
  float dVtx_r               = AlgConsts::invalidFloat;
  if ( truthPart->hasDecayVtx() ) {
    const auto* dVtx = truthPart->decayVtx();
    if ( dVtx ) {
      dVtx_isDarkPionDecay = EJsHelper::selectDarkPion( dVtx );
      dVtx_ID              = AUXDYN( dVtx, int, "ID" );
      dVtx_barcode         = dVtx->barcode();
      dVtx_r               = dVtx->perp();
    }
  }
  m_tp_dVtx                 ->push_back( truthPart->hasDecayVtx() );
  m_tp_dVtx_isDarkPionDecay ->push_back( dVtx_isDarkPionDecay     );
  m_tp_dVtx_ID              ->push_back( dVtx_ID                  );
  m_tp_dVtx_barcode         ->push_back( dVtx_barcode             );
  m_tp_dVtx_r               ->push_back( dVtx_r                   );

  bool isTruthJetMatch = false; bool isDarkJetMatch  = false;
  if ( truthPart->isAvailable<char>("isMatchedToTruthJet") ) {
    isTruthJetMatch = truthPart->auxdataConst<char>("isMatchedToTruthJet");
    isDarkJetMatch  = truthPart->auxdataConst<char>("isMatchedToDarkJet");
  }
  bool isEMTopoJetMatch = false; std::string emtopo_str = "";
  if ( truthPart->isAvailable<char>("isMatchedToRecoJet_EMTopo" + treeName ) ) {
    isEMTopoJetMatch = truthPart->auxdataConst<char>("isMatchedToRecoJet_EMTopo" + treeName );
    emtopo_str = treeName;
  }
  else if ( truthPart->isAvailable<char>("isMatchedToRecoJet_EMTopo") )
    isEMTopoJetMatch = truthPart->auxdataConst<char>("isMatchedToRecoJet_EMTopo");
  bool isPFlowJetMatch = false; std::string pflow_str = "";
  if ( truthPart->isAvailable<char>("isMatchedToRecoJet_PFlow" + treeName ) ) {
    isPFlowJetMatch = truthPart->auxdataConst<char>("isMatchedToRecoJet_PFlow" + treeName );
    pflow_str = treeName;
  }
  else if ( truthPart->isAvailable<char>("isMatchedToRecoJet_PFlow") )
    isPFlowJetMatch = truthPart->auxdataConst<char>("isMatchedToRecoJet_PFlow");

  m_tp_truthJetMatch    ->push_back( isTruthJetMatch );
  m_tp_truthJetMatch_ID ->push_back( AUXDYNVEC( truthPart, int,   "truthJetMatchIDs" ) );
  m_tp_truthJetMatch_dR ->push_back( AUXDYNVEC( truthPart, float, "truthJetMatchDRs" ) );
  m_tp_darkJetMatch     ->push_back( isDarkJetMatch );
  m_tp_darkJetMatch_ID  ->push_back( AUXDYNVEC( truthPart, int,   "darkJetMatchIDs"  ) );
  m_tp_darkJetMatch_dR  ->push_back( AUXDYNVEC( truthPart, float, "darkJetMatchDRs"  ) );
  if ( m_doEMTopoJets ) {
    m_tp_emtopoJetMatch    ->push_back( isEMTopoJetMatch );
    m_tp_emtopoJetMatch_ID ->push_back( AUXDYNVEC( truthPart, int,   "recoJetMatchIDs_EMTopo" ) );
    m_tp_emtopoJetMatch_dR ->push_back( AUXDYNVEC( truthPart, float, "recoJetMatchDRs_EMTopo" ) );
  }
  if ( m_doPFlowJets ) {
    m_tp_pflowJetMatch     ->push_back( isPFlowJetMatch );
    m_tp_pflowJetMatch_ID  ->push_back( AUXDYNVEC( truthPart, int,   "recoJetMatchIDs_PFlow"  ) );
    m_tp_pflowJetMatch_dR  ->push_back( AUXDYNVEC( truthPart, float, "recoJetMatchDRs_PFlow"  ) );
  }
}

void EJsHelpTreeBase :: ClearTruthUser ( const std::string truthName )
{
  m_tp_ID                ->clear();
  m_tp_M                 ->clear();
  m_tp_charge            ->clear();
  m_tp_isReco            ->clear();
  m_tp_recoProb          ->clear();
  m_tp_recoID            ->clear();
  m_tp_recoIsSelected    ->clear();
  m_tp_recoIsAssociated  ->clear();
  m_tp_isStable          ->clear();
  m_tp_isInteracting     ->clear();
  m_tp_isReconstructible ->clear();
  m_tp_isDark            ->clear();

  m_tp_parent_ID                ->clear();
  m_tp_parent_isReco            ->clear();
  m_tp_parent_recoProb          ->clear();
  m_tp_parent_recoID            ->clear();
  m_tp_parent_isStable          ->clear();
  m_tp_parent_isInteracting     ->clear();
  m_tp_parent_isReconstructible ->clear();
  m_tp_parent_isDark            ->clear();

  m_tp_child_ID                ->clear();
  m_tp_child_isReco            ->clear();
  m_tp_child_recoProb          ->clear();
  m_tp_child_recoID            ->clear();
  m_tp_child_isStable          ->clear();
  m_tp_child_isInteracting     ->clear();
  m_tp_child_isReconstructible ->clear();
  m_tp_child_isDark            ->clear();

  m_tp_pVtx                 ->clear();
  m_tp_pVtx_isDarkPionDecay ->clear();
  m_tp_pVtx_ID              ->clear();
  m_tp_pVtx_barcode         ->clear();
  m_tp_pVtx_r               ->clear();

  m_tp_dVtx                 ->clear();
  m_tp_dVtx_isDarkPionDecay ->clear();
  m_tp_dVtx_ID              ->clear();
  m_tp_dVtx_barcode         ->clear();
  m_tp_dVtx_r               ->clear();

  m_tp_truthJetMatch       ->clear();
  m_tp_truthJetMatch_ID    ->clear();
  m_tp_truthJetMatch_dR    ->clear();
  m_tp_darkJetMatch        ->clear();
  m_tp_darkJetMatch_ID     ->clear();
  m_tp_darkJetMatch_dR     ->clear();
  if ( m_doEMTopoJets ) {
    m_tp_emtopoJetMatch    ->clear();
    m_tp_emtopoJetMatch_ID ->clear();
    m_tp_emtopoJetMatch_dR ->clear();
  }
  if ( m_doPFlowJets ) {
    m_tp_pflowJetMatch     ->clear();
    m_tp_pflowJetMatch_ID  ->clear();
    m_tp_pflowJetMatch_dR  ->clear();
  }
}



/***************
 * USER TRACKS *
 ***************/
void EJsHelpTreeBase :: AddTracksUser ( const std::string trackName, const std::string detailStr )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddTracksUser()", "adding EJs-user track variables" );

  setBranch<int>      ( trackName, "ID",           m_trk_ID           );
  setBranch<float>    ( trackName, "d0",           m_trk_d0           );
  setBranch<float>    ( trackName, "errd0",        m_trk_errd0        );
  setBranch<float>    ( trackName, "errz0",        m_trk_errz0        );
  setBranch<float>    ( trackName, "chi2",         m_trk_chi2         );
  setBranch<uint8_t>  ( trackName, "isSelected",   m_trk_isSelected   );
  setBranch<uint8_t>  ( trackName, "isAssociated", m_trk_isAssociated );

  std::string selCounterName   = "n" + trackName + "Selected";
  std::string assocCounterName = "n" + trackName + "Associated";
  m_tree->Branch( selCounterName  .c_str(), &m_trk_nSelected,   (selCounterName  +"/i").c_str() );
  m_tree->Branch( assocCounterName.c_str(), &m_trk_nAssociated, (assocCounterName+"/i").c_str() );
}

void EJsHelpTreeBase :: FillTracksUser ( const std::string trackName, const xAOD::TrackParticle* track )
{
  bool is_selected = false;
  if ( track->isAvailable<char>("is_selected") ) {
    if ( track->auxdataConst<char>("is_selected") ) {
      is_selected = true;
      m_trk_nSelected++;
    }
  }
  bool is_associated = false;
  if ( track->isAvailable<char>("is_associated") ) {
    if ( track->auxdataConst<char>("is_associated") ) {
      is_associated = true;
      m_trk_nAssociated++;
    }
  }

  m_trk_ID           ->push_back( AUXDYN( track, int, "ID" )                                            );
  m_trk_d0           ->push_back( track->d0()                                                           );
  m_trk_errd0        ->push_back( track->definingParametersCovMatrix()(0,0)                             );
  m_trk_errz0        ->push_back( track->definingParametersCovMatrix()(1,1)                             );
  m_trk_chi2         ->push_back( track->chiSquared() / (track->numberDoF() + AlgConsts::infinitesimal) );
  m_trk_isSelected   ->push_back( is_selected                                                           );
  m_trk_isAssociated ->push_back( is_associated                                                         );
}

void EJsHelpTreeBase :: ClearTracksUser ( const std::string trackName )
{
  m_trk_nSelected   = 0;
  m_trk_nAssociated = 0;

  m_trk_ID           ->clear();
  m_trk_d0           ->clear();
  m_trk_errd0        ->clear();
  m_trk_errz0        ->clear();
  m_trk_chi2         ->clear();
  m_trk_isSelected   ->clear();
  m_trk_isAssociated ->clear();
}
