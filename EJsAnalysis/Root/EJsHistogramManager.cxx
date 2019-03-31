#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/EJsHistogramManager.h"


EJsHistogramManager :: EJsHistogramManager ( std::string name, std::string detailStr, bool debug, bool emtopo, bool pflow, bool truth ) :
  HistogramManager ( name, detailStr )
{
  m_histoInfoSwitch = new EJsHelperClasses::HistogramInfoSwitch( detailStr );
  m_debug           = debug;
  m_doEMTopoJets    = emtopo;
  m_doPFlowJets     = pflow;
  m_truthLevelOnly  = truth;
  
  if      ( m_doEMTopoJets ) m_jetStr = "EMTopo";
  else if ( m_doPFlowJets  ) m_jetStr = "PFlow";

  m_numLead   = m_histoInfoSwitch ->m_numLeading;
  m_numVtxTrk = m_histoInfoSwitch ->m_numVtxTrk;

  if ( m_debug ) Info( "EJsHistogramManager()", "setting up" );

  m_runNumber       = 0;
  m_eventNumber     = 0;
  m_lumiBlock       = 0;
  m_bcid            = 0;
  m_mcEventNumber   = 0;
  m_mcChannelNumber = 0;
  m_mcEventWeight   = 0;
  m_npv             = 0;
  m_actualMu        = 0;
  m_averageMu       = 0;
  m_weight_pileup   = 0;
  m_isMC            = 0;
  m_signal          = 0;
  m_valid           = 0;
  m_ctrl            = 0;
  m_njetHt          = 0;
  
  m_pv_x            = 0;
  m_pv_y            = 0;
  m_pv_z            = 0;
  m_pv_r            = 0;
  m_pv_phi          = 0;
  m_pv_nTrk         = 0;
  m_pv_location     = 0;

  
  m_passL1           = 0;
  m_passHLT          = 0;
  m_passedTriggers   = new std::vector<std::string>;
  m_disabledTriggers = new std::vector<std::string>;

  
  m_jet_n     = 0;
  m_jet_pt    = new std::vector<float>;
  m_jet_eta   = new std::vector<float>;
  m_jet_phi   = new std::vector<float>;
  m_jet_E     = new std::vector<float>;
  m_jet_M     = new std::vector<float>;
  m_jet_rapid = new std::vector<float>;
  
  m_jet_hecFrac    = new std::vector<float>;
  m_jet_emFrac     = new std::vector<float>;
  m_jet_centroidR  = new std::vector<float>;
  m_jet_width      = new std::vector<float>;
  m_jet_numConstit = new std::vector<int>;
  
  m_jet_numTrkPt10   = new std::vector<std::vector<int>>;
  m_jet_sumPtTrkPt10 = new std::vector<std::vector<float>>;
  m_jet_trkWidthPt10 = new std::vector<std::vector<float>>;
  m_jet_numTrkPt5    = new std::vector<std::vector<int>>;
  m_jet_sumPtTrkPt5  = new std::vector<std::vector<float>>;
  m_jet_trkWidthPt5  = new std::vector<std::vector<float>>;
  
  m_jet_GhostTrackCount = new std::vector<int>;
  m_jet_GhostTrackPt    = new std::vector<float>;
  m_jet_GhostTruthCount = new std::vector<int>;
  m_jet_GhostTruthPt    = new std::vector<float>;
  
  m_jet_trkCount        = new std::vector<int>;
  m_jet_trkPt           = new std::vector<float>;
  m_jet_trk_dR          = new std::vector<std::vector<float>>;
  m_jet_tpCount         = new std::vector<int>;
  m_jet_tpPt            = new std::vector<float>;
  m_jet_tp_dR           = new std::vector<std::vector<float>>;
  
  m_jet_secVtxCount   = new std::vector<int>;
  m_jet_secVtxPt      = new std::vector<float>;
  m_jet_secVtx_dR     = new std::vector<std::vector<float>>;
  m_jet_truthVtxCount = new std::vector<int>;
  m_jet_truthVtxPt    = new std::vector<float>;
  m_jet_truthVtx_dR   = new std::vector<std::vector<float>>;

  m_jet_isTruthMatched = new std::vector<uint8_t>;
  m_jet_truthMatch_dR  = new std::vector<float>;
  m_jet_isDarkMatched  = new std::vector<uint8_t>;
  m_jet_darkMatch_dR   = new std::vector<float>;


  m_truthJet_n     = 0;
  m_truthJet_pt    = new std::vector<float>;
  m_truthJet_eta   = new std::vector<float>;
  m_truthJet_phi   = new std::vector<float>;
  m_truthJet_E     = new std::vector<float>;
  m_truthJet_M     = new std::vector<float>;  
  m_truthJet_rapid = new std::vector<float>;

  m_truthJet_width      = new std::vector<float>;
  m_truthJet_girth      = new std::vector<float>;
  m_truthJet_numConstit = new std::vector<int>;
  m_truthJet_constitPt  = new std::vector<float>;
  m_truthJet_constit_dR = new std::vector<std::vector<float>>;

  m_truthJet_trkCount = new std::vector<int>;
  m_truthJet_trkPt    = new std::vector<float>;
  m_truthJet_trk_dR   = new std::vector<std::vector<float>>;
  m_truthJet_tpCount  = new std::vector<int>;
  m_truthJet_tpPt     = new std::vector<float>;
  m_truthJet_tp_dR    = new std::vector<std::vector<float>>;

  m_truthJet_secVtxCount   = new std::vector<int>;
  m_truthJet_secVtxPt      = new std::vector<float>;
  m_truthJet_secVtx_dR     = new std::vector<std::vector<float>>;
  m_truthJet_truthVtxCount = new std::vector<int>;
  m_truthJet_truthVtxPt    = new std::vector<float>;
  m_truthJet_truthVtx_dR   = new std::vector<std::vector<float>>;

  m_truthJet_isDarkMatched = new std::vector<uint8_t>;
  m_truthJet_darkMatch_dR  = new std::vector<float>;


  m_darkJet_n     = 0;
  m_darkJet_pt    = new std::vector<float>;
  m_darkJet_eta   = new std::vector<float>;
  m_darkJet_phi   = new std::vector<float>;
  m_darkJet_E     = new std::vector<float>;
  m_darkJet_M     = new std::vector<float>;
  m_darkJet_rapid = new std::vector<float>;

  m_darkJet_girth      = new std::vector<float>;
  m_darkJet_numConstit = new std::vector<int>;
  m_darkJet_constitPt  = new std::vector<float>;
  m_darkJet_constit_dR = new std::vector<std::vector<float>>;

  m_darkJet_trkCount = new std::vector<int>;
  m_darkJet_trkPt    = new std::vector<float>;
  m_darkJet_trk_dR   = new std::vector<std::vector<float>>;
  m_darkJet_tpCount  = new std::vector<int>;
  m_darkJet_tpPt     = new std::vector<float>;
  m_darkJet_tp_dR    = new std::vector<std::vector<float>>;

  m_darkJet_secVtxCount   = new std::vector<int>;
  m_darkJet_secVtxPt      = new std::vector<float>;
  m_darkJet_secVtx_dR     = new std::vector<std::vector<float>>;
  m_darkJet_truthVtxCount = new std::vector<int>;
  m_darkJet_truthVtxPt    = new std::vector<float>;
  m_darkJet_truthVtx_dR   = new std::vector<std::vector<float>>;


  m_tp_n             = 0;
  m_tp_pt            = new std::vector<float>;
  m_tp_eta           = new std::vector<float>;
  m_tp_phi           = new std::vector<float>;
  m_tp_E             = new std::vector<float>;
  m_tp_M             = new std::vector<float>;
  m_tp_charge        = new std::vector<float>;
  m_tp_pdgId         = new std::vector<int>;
  m_tp_status        = new std::vector<int>;
  m_tp_isDark        = new std::vector<uint8_t>;
  m_tp_nParents      = new std::vector<int>;
  m_tp_parent_pdgId  = new std::vector<std::vector<int>>;
  m_tp_parent_status = new std::vector<std::vector<int>>;
  m_tp_nChildren     = new std::vector<int>;
  m_tp_child_pdgId   = new std::vector<std::vector<int>>;
  m_tp_child_status  = new std::vector<std::vector<int>>;
  m_tp_hasPVtx       = new std::vector<uint8_t>;
  m_tp_pVtx_r        = new std::vector<float>;
  m_tp_hasDVtx       = new std::vector<uint8_t>;
  m_tp_dVtx_r        = new std::vector<float>;

  
  m_secVtx_n             = 0;
  m_secVtx_x             = new std::vector<float>;
  m_secVtx_y             = new std::vector<float>;
  m_secVtx_z             = new std::vector<float>;
  m_secVtx_r             = new std::vector<float>;
  m_secVtx_pt            = new std::vector<float>;
  m_secVtx_eta           = new std::vector<float>;
  m_secVtx_phi           = new std::vector<float>;
  m_secVtx_mass          = new std::vector<float>;
  m_secVtx_mass_nonAssoc = new std::vector<float>;
  m_secVtx_chi2          = new std::vector<float>;
  m_secVtx_direction     = new std::vector<float>;
  m_secVtx_charge        = new std::vector<int>;
  m_secVtx_Ht            = new std::vector<float>;
  m_secVtx_minOpAng      = new std::vector<float>;
  m_secVtx_maxOpAng      = new std::vector<float>;
  m_secVtx_mind0         = new std::vector<float>;
  m_secVtx_maxd0         = new std::vector<float>;

  m_secVtx_minOneTrkRmvMass = new std::vector<float>;
  m_secVtx_twoTrkMass       = new std::vector<std::vector<float>>;
  m_secVtx_twoTrkMassRest   = new std::vector<std::vector<float>>;
  m_secVtx_twoTrkCharge     = new std::vector<std::vector<int>>;

  m_secVtx_ntrk       = new std::vector<uint32_t>;
  m_secVtx_ntrk_sel   = new std::vector<uint32_t>;
  m_secVtx_ntrk_assoc = new std::vector<uint32_t>;
}


EJsHistogramManager :: ~EJsHistogramManager ()
{
  if ( m_debug ) Info( "EJsHistogramManager()", "deleting" );

  if ( m_histoInfoSwitch ) delete m_histoInfoSwitch;

  delete m_passedTriggers;
  delete m_disabledTriggers;


  delete m_jet_pt;
  delete m_jet_eta;
  delete m_jet_phi;
  delete m_jet_E;
  delete m_jet_M;
  delete m_jet_rapid;
  
  delete m_jet_hecFrac;
  delete m_jet_emFrac;
  delete m_jet_centroidR;
  delete m_jet_width;
  delete m_jet_numConstit;
  
  delete m_jet_numTrkPt10;
  delete m_jet_sumPtTrkPt10;
  delete m_jet_trkWidthPt10;
  delete m_jet_numTrkPt5;
  delete m_jet_sumPtTrkPt5;
  delete m_jet_trkWidthPt5;

  delete m_jet_GhostTrackCount;
  delete m_jet_GhostTrackPt;
  delete m_jet_GhostTruthCount;
  delete m_jet_GhostTruthPt;
  
  delete m_jet_trkCount;
  delete m_jet_trkPt;
  delete m_jet_trk_dR;
  delete m_jet_tpCount;
  delete m_jet_tpPt;
  delete m_jet_tp_dR;

  delete m_jet_secVtxCount;
  delete m_jet_secVtxPt;
  delete m_jet_secVtx_dR;
  delete m_jet_truthVtxCount;
  delete m_jet_truthVtxPt;
  delete m_jet_truthVtx_dR;

  delete m_jet_isTruthMatched;
  delete m_jet_truthMatch_dR;
  delete m_jet_isDarkMatched;
  delete m_jet_darkMatch_dR;

  
  delete m_truthJet_pt;
  delete m_truthJet_eta;
  delete m_truthJet_phi;
  delete m_truthJet_E;
  delete m_truthJet_M;
  delete m_truthJet_rapid;
  
  delete m_truthJet_width;
  delete m_truthJet_girth;
  delete m_truthJet_numConstit;
  delete m_truthJet_constitPt;
  delete m_truthJet_constit_dR;

  delete m_truthJet_trkCount;
  delete m_truthJet_trkPt;
  delete m_truthJet_trk_dR;
  delete m_truthJet_tpCount;
  delete m_truthJet_tpPt;
  delete m_truthJet_tp_dR;

  delete m_truthJet_secVtxCount;
  delete m_truthJet_secVtxPt;
  delete m_truthJet_secVtx_dR;
  delete m_truthJet_truthVtxCount;
  delete m_truthJet_truthVtxPt;
  delete m_truthJet_truthVtx_dR;

  delete m_truthJet_isDarkMatched;
  delete m_truthJet_darkMatch_dR;


  delete m_darkJet_pt;
  delete m_darkJet_eta;
  delete m_darkJet_phi;
  delete m_darkJet_E;
  delete m_darkJet_M;
  delete m_darkJet_rapid;

  delete m_darkJet_girth;
  delete m_darkJet_numConstit;
  delete m_darkJet_constitPt;
  delete m_darkJet_constit_dR;

  delete m_darkJet_trkCount;
  delete m_darkJet_trkPt;
  delete m_darkJet_trk_dR;
  delete m_darkJet_tpCount;
  delete m_darkJet_tpPt;
  delete m_darkJet_tp_dR;
  
  delete m_darkJet_secVtxCount;
  delete m_darkJet_secVtxPt;
  delete m_darkJet_secVtx_dR;
  delete m_darkJet_truthVtxCount;
  delete m_darkJet_truthVtxPt;
  delete m_darkJet_truthVtx_dR;


  delete m_tp_pt;
  delete m_tp_eta;
  delete m_tp_phi;
  delete m_tp_E;
  delete m_tp_M;
  delete m_tp_charge;
  delete m_tp_pdgId;
  delete m_tp_status;
  delete m_tp_isDark;
  delete m_tp_nParents;
  delete m_tp_parent_pdgId;
  delete m_tp_parent_status;
  delete m_tp_nChildren;
  delete m_tp_child_pdgId;
  delete m_tp_child_status;
  delete m_tp_hasPVtx;
  delete m_tp_pVtx_r;
  delete m_tp_hasDVtx;
  delete m_tp_dVtx_r;

  
  delete m_secVtx_x;
  delete m_secVtx_y;
  delete m_secVtx_z;
  delete m_secVtx_r;
  delete m_secVtx_pt;
  delete m_secVtx_eta;
  delete m_secVtx_phi;
  delete m_secVtx_mass;
  delete m_secVtx_mass_nonAssoc;
  delete m_secVtx_chi2;
  delete m_secVtx_direction;
  delete m_secVtx_charge;
  delete m_secVtx_Ht;
  delete m_secVtx_minOpAng;
  delete m_secVtx_maxOpAng;
  delete m_secVtx_mind0;
  delete m_secVtx_maxd0;

  delete m_secVtx_minOneTrkRmvMass;
  delete m_secVtx_twoTrkMass;
  delete m_secVtx_twoTrkMassRest;
  delete m_secVtx_twoTrkCharge;
  
  delete m_secVtx_ntrk;
  delete m_secVtx_ntrk_sel;
  delete m_secVtx_ntrk_assoc;
}



StatusCode EJsHistogramManager :: connectEvents ( TTree* tree, bool mc )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectEvents()", "connecting event branches" );

  using namespace EJsHelper;
  connectBranch<int>        ( tree, "runNumber",                      &m_runNumber       );
  connectBranch<Long64_t>   ( tree, "eventNumber",                    &m_eventNumber     );
  connectBranch<int>        ( tree, "lumiBlock",                      &m_lumiBlock       );
  connectBranch<int>        ( tree, "bcid",                           &m_bcid            );
  connectBranch<int>        ( tree, "NPV",                            &m_npv             );
  connectBranch<float>      ( tree, "actualInteractionsPerCrossing",  &m_actualMu        );
  connectBranch<float>      ( tree, "averageInteractionsPerCrossing", &m_averageMu       );
  connectBranch<float>      ( tree, "weight_pileup",                  &m_weight_pileup   );
  if ( mc ) {
    connectBranch<int>      ( tree, "mcEventNumber",                  &m_mcEventNumber   );
    connectBranch<int>      ( tree, "mcChannelNumber",                &m_mcChannelNumber );
    connectBranch<float>    ( tree, "mcEventWeight",                  &m_mcEventWeight   );
  }
  connectBranch<uint8_t>    ( tree, "isMC",                           &m_isMC            );

  if ( !m_truthLevelOnly ) {
    connectBranch<uint8_t>    ( tree, "isSignal_" + m_jetStr,           &m_signal          );
    connectBranch<uint8_t>    ( tree, "isValid_"  + m_jetStr,           &m_valid           );
    connectBranch<uint8_t>    ( tree, "isCtrl_"   + m_jetStr,           &m_ctrl            );
    connectBranch<float>      ( tree, "NJetHt_"   + m_jetStr,           &m_njetHt          );
  
    connectBranch<float>      ( tree, "PV_x",                           &m_pv_x            );
    connectBranch<float>      ( tree, "PV_y",                           &m_pv_y            );
    connectBranch<float>      ( tree, "PV_z",                           &m_pv_z            );
    connectBranch<float>      ( tree, "PV_r",                           &m_pv_r            );
    connectBranch<float>      ( tree, "PV_phi",                         &m_pv_phi          );
    connectBranch<uint32_t>   ( tree, "PV_nTracks",                     &m_pv_nTrk         );
    connectBranch<int>        ( tree, "PV_location",                    &m_pv_location     );
  }

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTriggers ( TTree* tree, bool mc )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTriggers()", "connecting trigger branches" );

  using namespace EJsHelper;
  connectBranch<int>            ( tree, "passL1",           &m_passL1           );
  connectBranch<int>            ( tree, "passHLT",          &m_passHLT          );
  connectBranchVec<std::string> ( tree, "passedTriggers",   &m_passedTriggers   );
  connectBranchVec<std::string> ( tree, "disabledTriggers", &m_disabledTriggers );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectJets ( TTree* tree, const std::string jetName, bool mc )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectJets()", "connecting jet branches" );

  std::string name = jetName;

  using namespace EJsHelper;
  connectBranch<int> ( tree, "n"+name, &m_jet_n );

  using namespace HelperFunctions;
  connectBranch<float> ( name, tree, "pt",       &m_jet_pt    );
  connectBranch<float> ( name, tree, "eta",      &m_jet_eta   );
  connectBranch<float> ( name, tree, "phi",      &m_jet_phi   );
  connectBranch<float> ( name, tree, "E",        &m_jet_E     );
  connectBranch<float> ( name, tree, "M",        &m_jet_M     );
  connectBranch<float> ( name, tree, "rapidity", &m_jet_rapid );

  if ( m_histoInfoSwitch ->m_jetEConstit ) {
    connectBranch<float> ( name, tree, "HECFrac",          &m_jet_hecFrac    );
    connectBranch<float> ( name, tree, "EMFrac",           &m_jet_emFrac     );
    connectBranch<float> ( name, tree, "CentroidR",        &m_jet_centroidR  );
    connectBranch<float> ( name, tree, "Width",            &m_jet_width      );
    connectBranch<int>   ( name, tree, "numConstituents",  &m_jet_numConstit );
  }

  if ( m_histoInfoSwitch ->m_jetTrkMom ) {
    connectBranch<std::vector<int>>   ( name, tree, "NumTrkPt1000",     &m_jet_numTrkPt10   );
    connectBranch<std::vector<float>> ( name, tree, "SumPtTrkPt1000",   &m_jet_sumPtTrkPt10 );
    connectBranch<std::vector<float>> ( name, tree, "TrackWidthPt1000", &m_jet_trkWidthPt10 ); // pt-weighted dR
    connectBranch<std::vector<int>>   ( name, tree, "NumTrkPt500",      &m_jet_numTrkPt5    );
    connectBranch<std::vector<float>> ( name, tree, "SumPtTrkPt500",    &m_jet_sumPtTrkPt5  );
    connectBranch<std::vector<float>> ( name, tree, "TrackWidthPt500",  &m_jet_trkWidthPt5  );
  }

  if ( m_histoInfoSwitch ->m_jetGhost ) {
    connectBranch<int>     ( name, tree, "GhostTrackCount", &m_jet_GhostTrackCount );
    connectBranch<float>   ( name, tree, "GhostTrackPt",    &m_jet_GhostTrackPt    );
    if ( mc ) {
      connectBranch<int>   ( name, tree, "GhostTruthCount", &m_jet_GhostTruthCount );
      connectBranch<float> ( name, tree, "GhostTruthPt",    &m_jet_GhostTruthPt    );
    }
  }

  if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTrk ) {
    connectBranch<int>                  ( name, tree, "trkCount", &m_jet_trkCount );
    connectBranch<float>                ( name, tree, "trkPt",    &m_jet_trkPt    );
    connectBranch<std::vector<float>>   ( name, tree, "trk_dR",   &m_jet_trk_dR   );
    if ( mc ) {
      connectBranch<int>                ( name, tree, "tpCount",  &m_jet_tpCount  );
      connectBranch<float>              ( name, tree, "tpPt",     &m_jet_tpPt     );
      connectBranch<std::vector<float>> ( name, tree, "tp_dR",    &m_jet_tp_dR    );
    }
  }

  if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetVtx ) {
    connectBranch<int>                  ( name, tree, "secVtxCount",   &m_jet_secVtxCount   );
    connectBranch<float>                ( name, tree, "secVtxPt",      &m_jet_secVtxPt      );
    connectBranch<std::vector<float>>   ( name, tree, "secVtx_dR",     &m_jet_secVtx_dR     );
    if ( mc ) {
      connectBranch<int>                ( name, tree, "truthVtxCount", &m_jet_truthVtxCount );
      connectBranch<float>              ( name, tree, "truthVtxPt",    &m_jet_truthVtxPt    );
      connectBranch<std::vector<float>> ( name, tree, "truthVtx_dR",   &m_jet_truthVtx_dR   );
    }
  }

  if ( ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTruth ) && mc ) {
    connectBranch<uint8_t> ( name, tree, "isTruthMatched", &m_jet_isTruthMatched );
    connectBranch<float>   ( name, tree, "truthMatch_dR",  &m_jet_truthMatch_dR  );
    connectBranch<uint8_t> ( name, tree, "isDarkMatched",  &m_jet_isDarkMatched  );
    connectBranch<float>   ( name, tree, "darkMatch_dR",   &m_jet_darkMatch_dR   );
  }

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTrigJets ( TTree* tree, const std::string trigJetName, bool mc )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTrigJets()", "connecting trigger jet branches" );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthJets ( TTree* tree, const std::string truthJetName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthJets()", "connecting truth jet branches" );

  std::string name = truthJetName;

  using namespace EJsHelper;
  connectBranch<int> ( tree, "n"+name, &m_truthJet_n );

  using namespace HelperFunctions;
  connectBranch<float> ( name, tree, "pt",       &m_truthJet_pt    );
  connectBranch<float> ( name, tree, "eta",      &m_truthJet_eta   );
  connectBranch<float> ( name, tree, "phi",      &m_truthJet_phi   );
  connectBranch<float> ( name, tree, "E",        &m_truthJet_E     );
  connectBranch<float> ( name, tree, "M",        &m_truthJet_M     );
  connectBranch<float> ( name, tree, "rapidity", &m_truthJet_rapid );

  if ( m_histoInfoSwitch ->m_jetEConstit ) {
    connectBranch<float>              ( name, tree, "Width",           &m_truthJet_width      );
    connectBranch<float>              ( name, tree, "girth",           &m_truthJet_girth      );
    connectBranch<int>                ( name, tree, "numConstituents", &m_truthJet_numConstit );
    connectBranch<float>              ( name, tree, "constituentPt",   &m_truthJet_constitPt  );
    connectBranch<std::vector<float>> ( name, tree, "constituent_dR",  &m_truthJet_constit_dR );
  }

  if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTrk ) {
    connectBranch<int>                ( name, tree, "trkCount", &m_truthJet_trkCount );
    connectBranch<float>              ( name, tree, "trkPt",    &m_truthJet_trkPt    );
    connectBranch<std::vector<float>> ( name, tree, "trk_dR",   &m_truthJet_trk_dR   );
    connectBranch<int>                ( name, tree, "tpCount",  &m_truthJet_tpCount  );
    connectBranch<float>              ( name, tree, "tpPt",     &m_truthJet_tpPt     );
    connectBranch<std::vector<float>> ( name, tree, "tp_dR",    &m_truthJet_tp_dR    );
  }

  if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetVtx ) {
    connectBranch<int>                ( name, tree, "secVtxCount",   &m_truthJet_secVtxCount   );
    connectBranch<float>              ( name, tree, "secVtxPt",      &m_truthJet_secVtxPt      );
    connectBranch<std::vector<float>> ( name, tree, "secVtx_dR",     &m_truthJet_secVtx_dR     );
    connectBranch<int>                ( name, tree, "truthVtxCount", &m_truthJet_truthVtxCount );
    connectBranch<float>              ( name, tree, "truthVtxPt",    &m_truthJet_truthVtxPt    );
    connectBranch<std::vector<float>> ( name, tree, "truthVtx_dR",   &m_truthJet_truthVtx_dR   );
  }

  if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTruth ) {
    connectBranch<uint8_t> ( name, tree, "isDarkMatched",  &m_truthJet_isDarkMatched  );
    connectBranch<float>   ( name, tree, "darkMatch_dR",   &m_truthJet_darkMatch_dR   );
  }

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthDarkJets ( TTree* tree, const std::string darkJetName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthDarkJets()", "connecting truth dark jet branches" );

  std::string name = darkJetName;

  using namespace EJsHelper;
  connectBranch<int> ( tree, "n"+name, &m_darkJet_n );

  using namespace HelperFunctions;
  connectBranch<float> ( name, tree, "pt",       &m_darkJet_pt    );
  connectBranch<float> ( name, tree, "eta",      &m_darkJet_eta   );
  connectBranch<float> ( name, tree, "phi",      &m_darkJet_phi   );
  connectBranch<float> ( name, tree, "E",        &m_darkJet_E     );
  connectBranch<float> ( name, tree, "M",        &m_darkJet_M     );
  connectBranch<float> ( name, tree, "rapidity", &m_darkJet_rapid );

  if ( m_histoInfoSwitch ->m_jetEConstit ) {
    connectBranch<float>              ( name, tree, "girth",           &m_darkJet_girth      );
    connectBranch<int>                ( name, tree, "numConstituents", &m_darkJet_numConstit );
    connectBranch<float>              ( name, tree, "constituentPt",   &m_darkJet_constitPt  );
    connectBranch<std::vector<float>> ( name, tree, "constituent_dR",  &m_darkJet_constit_dR );
  }

  if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTrk ) {
    connectBranch<int>                ( name, tree, "trkCount", &m_darkJet_trkCount );
    connectBranch<float>              ( name, tree, "trkPt",    &m_darkJet_trkPt    );
    connectBranch<std::vector<float>> ( name, tree, "trk_dR",   &m_darkJet_trk_dR   );
    connectBranch<int>                ( name, tree, "tpCount",  &m_darkJet_tpCount  );
    connectBranch<float>              ( name, tree, "tpPt",     &m_darkJet_tpPt     );
    connectBranch<std::vector<float>> ( name, tree, "tp_dR",    &m_darkJet_tp_dR    );
  }

  if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetVtx ) {
    connectBranch<int>                ( name, tree, "secVtxCount",   &m_darkJet_secVtxCount   );
    connectBranch<float>              ( name, tree, "secVtxPt",      &m_darkJet_secVtxPt      );
    connectBranch<std::vector<float>> ( name, tree, "secVtx_dR",     &m_darkJet_secVtx_dR     );
    connectBranch<int>                ( name, tree, "truthVtxCount", &m_darkJet_truthVtxCount );
    connectBranch<float>              ( name, tree, "truthVtxPt",    &m_darkJet_truthVtxPt    );
    connectBranch<std::vector<float>> ( name, tree, "truthVtx_dR",   &m_darkJet_truthVtx_dR   );
  }

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthParts ( TTree* tree, const std::string truthName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthParts()", "connecting truth particle branches" );

  std::string name = truthName;
  
  using namespace EJsHelper;
  connectBranch<int> ( tree, "n"+name, &m_tp_n );

  using namespace HelperFunctions;
  connectBranch<float>                ( name, tree, "pt",            &m_tp_pt            );
  connectBranch<float>                ( name, tree, "eta",           &m_tp_eta           ); 
  connectBranch<float>                ( name, tree, "phi",           &m_tp_phi           );
  connectBranch<float>                ( name, tree, "E",             &m_tp_E             );
  connectBranch<float>                ( name, tree, "M",             &m_tp_M             );
  connectBranch<float>                ( name, tree, "charge",        &m_tp_charge        );
  connectBranch<int>                  ( name, tree, "pdgId",         &m_tp_pdgId         );
  connectBranch<int>                  ( name, tree, "status",        &m_tp_status        );
  connectBranch<uint8_t>              ( name, tree, "isDark",        &m_tp_isDark        );
  connectBranch<int>                  ( name, tree, "nParents",      &m_tp_nParents      );
  connectBranch<std::vector<int>>     ( name, tree, "parent_pdgId",  &m_tp_parent_pdgId  );
  connectBranch<std::vector<int>>     ( name, tree, "parent_status", &m_tp_parent_status );
  connectBranch<int>                  ( name, tree, "nChildren",     &m_tp_nChildren     );
  connectBranch<std::vector<int>>     ( name, tree, "child_pdgId",   &m_tp_child_pdgId   );
  connectBranch<std::vector<int>>     ( name, tree, "child_status",  &m_tp_child_status  );
  connectBranch<uint8_t>              ( name, tree, "hasProdVtx",    &m_tp_hasPVtx       );
  connectBranch<float>                ( name, tree, "prodVtx_r",     &m_tp_pVtx_r        );
  connectBranch<uint8_t>              ( name, tree, "hasDecayVtx",   &m_tp_hasDVtx       );
  connectBranch<float>                ( name, tree, "decayVtx_r",    &m_tp_dVtx_r        );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTracks ( TTree* tree, const std::string trackName, bool mc )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTracks()", "connecting track branches" );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthVerts ( TTree* tree, const std::string truthVtxName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthVerts()", "connecting truth vertex branches" );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectSecondaryVerts ( TTree* tree, const std::string secVtxName, bool mc )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectSecondaryVerts()", "connecting secondary vertex branches" );

  std::string name = secVtxName;

  using namespace EJsHelper;
  connectBranch<int> ( tree, "n"+name, &m_secVtx_n );

  using namespace HelperFunctions;
  connectBranch<float> ( name, tree, "x",             &m_secVtx_x             );
  connectBranch<float> ( name, tree, "y",             &m_secVtx_y             );
  connectBranch<float> ( name, tree, "z",             &m_secVtx_z             );
  connectBranch<float> ( name, tree, "r",             &m_secVtx_r             );
  connectBranch<float> ( name, tree, "pt",            &m_secVtx_pt            );
  connectBranch<float> ( name, tree, "eta",           &m_secVtx_eta           );
  connectBranch<float> ( name, tree, "phi",           &m_secVtx_phi           );
  connectBranch<float> ( name, tree, "mass",          &m_secVtx_mass          );
  connectBranch<float> ( name, tree, "mass_nonAssoc", &m_secVtx_mass_nonAssoc );
  connectBranch<float> ( name, tree, "chi2",          &m_secVtx_chi2          );
  connectBranch<float> ( name, tree, "direction",     &m_secVtx_direction     );
  connectBranch<int>   ( name, tree, "charge",        &m_secVtx_charge        );
  connectBranch<float> ( name, tree, "Ht",            &m_secVtx_Ht            );
  connectBranch<float> ( name, tree, "minOpAng",      &m_secVtx_minOpAng      );
  connectBranch<float> ( name, tree, "maxOpAng",      &m_secVtx_maxOpAng      );
  connectBranch<float> ( name, tree, "mind0",         &m_secVtx_mind0         );
  connectBranch<float> ( name, tree, "maxd0",         &m_secVtx_maxd0         );

  connectBranch<float>              ( name, tree, "minOneTrackRemovedMass", &m_secVtx_minOneTrkRmvMass );
  connectBranch<std::vector<float>> ( name, tree, "twoTracksMass",          &m_secVtx_twoTrkMass       );
  connectBranch<std::vector<float>> ( name, tree, "twoTracksMassRest",      &m_secVtx_twoTrkMassRest   );
  connectBranch<std::vector<int>>   ( name, tree, "twoTracksCharge",        &m_secVtx_twoTrkCharge     );
  
  connectBranch<uint32_t> ( name, tree, "ntrk",       &m_secVtx_ntrk       );
  connectBranch<uint32_t> ( name, tree, "ntrk_sel",   &m_secVtx_ntrk_sel   );
  connectBranch<uint32_t> ( name, tree, "ntrk_assoc", &m_secVtx_ntrk_assoc );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: initialize ( const std::string jetName, const std::string outFileName, const std::vector<std::string>& regions, bool mc )
{
  if ( m_debug ) Info( "EJsHistogramManger::initialize()", "booking histograms" );
  
  // book histograms -- use info switches

  std::string hjet      = jetName;
  std::string hjetUpper = jetName; hjetUpper[0] = toupper(hjetUpper[0]);

  for ( const auto& region : regions ) {
    const std::string name = m_name + outFileName + "/" + region + "/";

    // event info
    h_npv       .push_back( book( name, "nPV",                  "n primary vertices",               50, 0,   50 ) );
    h_actualMu  .push_back( book( name, "actualMu",             "actual interactions / crossing",  100, 0,  100 ) );
    h_averageMu .push_back( book( name, "averageMu",            "average interactions / crossing", 100, 0,  100 ) );
    h_njetHt    .push_back( book( name, "N" + hjetUpper + "Ht", "N-jet scalar sum-p_{T} [GeV]",    100, 0, 5000 ) );
    // pv info
    h_pv_x    .push_back( book( name, "pv_x",    "PV x-pos [mm]", 100, -1.5,  1.5 ) );
    h_pv_y    .push_back( book( name, "pv_y",    "PV y-pos [mm]", 100, -1.5,  1.5 ) );
    h_pv_z    .push_back( book( name, "pv_z",    "PV z-pos [mm]", 100, -150,  150 ) );
    h_pv_r    .push_back( book( name, "pv_r",    "PV r-pos [mm]", 100, -1.5,  1.5 ) );
    h_pv_phi  .push_back( book( name, "pv_phi",  "PV phi",        100, -3.5,  3.5 ) );
    h_pv_nTrk .push_back( book( name, "pv_nTrk", "n PV tracks",   100,    0,  350 ) );


    // jet basics
    h_jet_n      .push_back( book( name, hjet + "_n",     "n jets",           15,     0,   15 ) );
    h_jet_pt     .push_back( book( name, hjet + "_pt",    "jet p_{T} [GeV]",  100,    0, 1500 ) );
    h_jet_pt_l   .push_back( book( name, hjet + "_pt_l",  "jet p_{T} [GeV]",  100,    0, 2500 ) );
    h_jet_pt_m   .push_back( book( name, hjet + "_pt_m",  "jet p_{T} [GeV]",  100,    0,  500 ) );
    h_jet_pt_s   .push_back( book( name, hjet + "_pt_s",  "jet p_{T} [GeV]",  100,    0,  200 ) );
    h_jet_eta    .push_back( book( name, hjet + "_eta",   "jet eta",          100,   -5,    5 ) );
    h_jet_phi    .push_back( book( name, hjet + "_phi",   "jet phi",          100, -3.5,  3.5 ) );
    h_jet_E      .push_back( book( name, hjet + "_E",     "jet energy [GeV]", 100,    0, 2500 ) );
    h_jet_M      .push_back( book( name, hjet + "_M",     "jet mass [GeV]",   100,    0,  300 ) );
    h_jet_rapid  .push_back( book( name, hjet + "_rapid", "jet rapidity",     100,   -5,    5 ) );
    // jet kinematics
    if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
      h_jet_px   .push_back( book( name, hjet + "_px",    "jet p_{x} [GeV]",  100, -1500, 1500 ) );
      h_jet_py   .push_back( book( name, hjet + "_py",    "jet p_{y} [GeV]",  100, -1500, 1500 ) );
      h_jet_pz   .push_back( book( name, hjet + "_pz",    "jet p_{z} [GeV]",  100, -2500, 2500 ) );
      h_jet_Et   .push_back( book( name, hjet + "_Et",    "jet E_{T} [GeV]",  100,     0, 1500 ) );
      h_jet_Et_l .push_back( book( name, hjet + "_Et_l",  "jet E_{T} [GeV]",  100,     0, 2500 ) );
      h_jet_Et_m .push_back( book( name, hjet + "_Et_m",  "jet E_{T} [GeV]",  100,     0,  500 ) );
      h_jet_Et_s .push_back( book( name, hjet + "_Et_s",  "jet E_{T} [GeV]",  100,     0,  200 ) );
    }
    // leading jets
    if ( m_numLead ) {
      std::vector<TH1F*> h_nlead_pt;
      std::vector<TH1F*> h_nlead_pt_l;
      std::vector<TH1F*> h_nlead_pt_m;
      std::vector<TH1F*> h_nlead_pt_s;
      std::vector<TH1F*> h_nlead_eta;
      std::vector<TH1F*> h_nlead_phi;
      std::vector<TH1F*> h_nlead_E;
      std::vector<TH1F*> h_nlead_M;
      std::vector<TH1F*> h_nlead_rapid;
      std::vector<TH1F*> h_nlead_Et;
      std::vector<TH1F*> h_nlead_Et_l;
      std::vector<TH1F*> h_nlead_Et_m;
      std::vector<TH1F*> h_nlead_Et_s;
      for ( int i = 0; i != m_numLead; ++i ) {
	std::string njet = std::to_string(i);
	h_nlead_pt    .push_back( book( name, ( hjet + njet + "_pt"    ), ( "jet-" + njet + " p_{T} [GeV]"  ), 100,    0, 1500 ) );
	h_nlead_pt_l  .push_back( book( name, ( hjet + njet + "_pt_l"  ), ( "jet-" + njet + " p_{T} [GeV]"  ), 100,    0, 2500 ) );
	h_nlead_pt_m  .push_back( book( name, ( hjet + njet + "_pt_m"  ), ( "jet-" + njet + " p_{T} [GeV]"  ), 100,    0,  500 ) );
	h_nlead_pt_s  .push_back( book( name, ( hjet + njet + "_pt_s"  ), ( "jet-" + njet + " p_{T} [GeV]"  ), 100,    0,  200 ) );
	h_nlead_eta   .push_back( book( name, ( hjet + njet + "_eta"   ), ( "jet-" + njet + " eta"          ), 100,   -5,    5 ) );
	h_nlead_phi   .push_back( book( name, ( hjet + njet + "_phi"   ), ( "jet-" + njet + " phi"          ), 100, -3.5,  3.5 ) );
	h_nlead_E     .push_back( book( name, ( hjet + njet + "_E"     ), ( "jet-" + njet + " energy [GeV]" ), 100,    0, 2500 ) );
	h_nlead_M     .push_back( book( name, ( hjet + njet + "_M"     ), ( "jet-" + njet + " mass [GeV]"   ), 100,    0,  300 ) );
	h_nlead_rapid .push_back( book( name, ( hjet + njet + "_rapid" ), ( "jet-" + njet + " rapidity"     ), 100,   -5,    5 ) );
	h_nlead_Et    .push_back( book( name, ( hjet + njet + "_Et"    ), ( "jet-" + njet + " E_{T} [GeV]"  ), 100,    0, 1500 ) );
	h_nlead_Et_l  .push_back( book( name, ( hjet + njet + "_Et_l"  ), ( "jet-" + njet + " E_{T} [GeV]"  ), 100,    0, 2500 ) );
	h_nlead_Et_m  .push_back( book( name, ( hjet + njet + "_Et_m"  ), ( "jet-" + njet + " E_{T} [GeV]"  ), 100,    0,  500 ) );
	h_nlead_Et_s  .push_back( book( name, ( hjet + njet + "_Et_s"  ), ( "jet-" + njet + " E_{T} [GeV]"  ), 100,    0,  200 ) );
      }
      h_jetN_pt     .push_back( h_nlead_pt    );
      h_jetN_pt_l   .push_back( h_nlead_pt_l  );
      h_jetN_pt_m   .push_back( h_nlead_pt_m  );
      h_jetN_pt_s   .push_back( h_nlead_pt_s  );
      h_jetN_eta    .push_back( h_nlead_eta   );
      h_jetN_phi    .push_back( h_nlead_phi   );
      h_jetN_E      .push_back( h_nlead_E     );
      h_jetN_M      .push_back( h_nlead_M     );
      h_jetN_rapid  .push_back( h_nlead_rapid );
      // leading jet kinematics
      if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
	h_jetN_Et   .push_back( h_nlead_Et    );
	h_jetN_Et_l .push_back( h_nlead_Et_l  );
	h_jetN_Et_m .push_back( h_nlead_Et_m  );
	h_jetN_Et_s .push_back( h_nlead_Et_s  );
      }
    }

    // jet energy, width, constituents
    if ( m_histoInfoSwitch ->m_jetEConstit ) {
      h_jet_hecFrac    .push_back( book( name, hjet + "_hecFrac",   "HEC calo jet energy fraction", 100, -0.1,  1.1 ) );
      h_jet_emFrac     .push_back( book( name, hjet + "_emFrac",    "EM calo jet energy fraction",  100, -0.1,  1.1 ) );
      h_jet_centroidR  .push_back( book( name, hjet + "_centroidR", "jet centroid R",               100,    0, 6000 ) );
      h_jet_width      .push_back( book( name, hjet + "_width",     "jet width",                    100,    0,  0.4 ) );
      h_jet_numConstit .push_back( book( name, hjet + "_numConstit", "n jet constituents",           75,    0,   75 ) );
    }
    
    // jet track moments (PV)
    if ( m_histoInfoSwitch ->m_jetTrkMom ) {
      h_jet_numTrkPt10     .push_back( book( name, hjet + "_numTrkPt1000",     "n p_{T} > 1.0 GeV jet tracks",               75,  0,   75 ) );
      h_jet_sumPtTrkPt10   .push_back( book( name, hjet + "_sumPtTrkPt1000",   "p_{T} > 1.0 GeV jet track sum-p_{T} [GeV]", 100,  0,  800 ) );
      h_jet_sumPtTrkPt10_l .push_back( book( name, hjet + "_sumPtTrkPt1000_l", "p_{T} > 1.0 GeV jet track sum-p_{T} [GeV]", 100, 0,  1500 ) );
      h_jet_sumPtTrkPt10_m .push_back( book( name, hjet + "_sumPtTrkPt1000_m", "p_{T} > 1.0 GeV jet track sum-p_{T} [GeV]", 100, 0,   350 ) );
      h_jet_sumPtTrkPt10_s .push_back( book( name, hjet + "_sumPtTrkPt1000_s", "p_{T} > 1.0 GeV jet track sum-p_{T} [GeV]", 100, 0,   100 ) );
      h_jet_trkWidthPt10   .push_back( book( name, hjet + "_trkWidthPt1000",   "p_{T} > 1.0 GeV jet track width",           100,  0, 0.42 ) );
      h_jet_numTrkPt5      .push_back( book( name, hjet + "_numTrkPt500",      "n p_{T} > 0.5 GeV jet tracks",               75,  0,   75 ) );
      h_jet_sumPtTrkPt5    .push_back( book( name, hjet + "_sumPtTrkPt500",    "p_{T} > 0.5 GeV jet track sum-p_{T} [GeV]", 100,  0,  800 ) );
      h_jet_sumPtTrkPt5_l  .push_back( book( name, hjet + "_sumPtTrkPt500_l",  "p_{T} > 0.5 GeV jet track sum-p_{T} [GeV]", 100, 0,  1500 ) );
      h_jet_sumPtTrkPt5_m  .push_back( book( name, hjet + "_sumPtTrkPt500_m",  "p_{T} > 0.5 GeV jet track sum-p_{T} [GeV]", 100, 0,   350 ) );
      h_jet_sumPtTrkPt5_s  .push_back( book( name, hjet + "_sumPtTrkPt500_s",  "p_{T} > 0.5 GeV jet track sum-p_{T} [GeV]", 100, 0,   100 ) );
      h_jet_trkWidthPt5    .push_back( book( name, hjet + "_trkWidthPt500",    "p_{T} > 0.5 GeV jet track width",           100,  0, 0.42 ) );
    }
    
    // ghost-associated jet tracks / truth particles
    if ( m_histoInfoSwitch ->m_jetGhost ) {
      // ghost tracks
      h_jet_GhostTrackCount   .push_back( book( name, hjet + "_GhostTrackCount", "ghost-associated jet track count",           125, 0,    250 ) );
      h_jet_GhostTrackPt      .push_back( book( name, hjet + "_GhostTrackPt",    "ghost-associated jet track sum-p_{T} [GeV]", 100, 0,   2500 ) );
      h_jet_GhostTrackPt_l    .push_back( book( name, hjet + "_GhostTrackPt_l",  "ghost-associated jet track sum-p_{T} [GeV]", 100, 0,   5000 ) );
      h_jet_GhostTrackPt_m    .push_back( book( name, hjet + "_GhostTrackPt_m",  "ghost-associated jet track sum-p_{T} [GeV]", 100, 0,   1500 ) );
      h_jet_GhostTrackPt_s    .push_back( book( name, hjet + "_GhostTrackPt_s",  "ghost-associated jet track sum-p_{T} [GeV]", 100, 0,    500 ) );
      // ghost truth
      if ( mc ) {
	h_jet_GhostTruthCount .push_back( book( name, hjet + "_GhostTruthCount", "ghost-associated jet truth count",           125, 0,    250 ) );
	h_jet_GhostTruthPt    .push_back( book( name, hjet + "_GhostTruthPt",    "ghost-associated jet truth sum-p_{T} [GeV]", 100, 0,   1500 ) );
	h_jet_GhostTruthPt_l  .push_back( book( name, hjet + "_GhostTruthPt_l",  "ghost-associated jet truth sum-p_{T} [GeV]", 100, 0,   2500 ) );
	h_jet_GhostTruthPt_m  .push_back( book( name, hjet + "_GhostTruthPt_m",  "ghost-associated jet truth sum-p_{T} [GeV]", 100, 0,    500 ) );
	h_jet_GhostTruthPt_s  .push_back( book( name, hjet + "_GhostTruthPt_s",  "ghost-associated jet truth sum-p_{T} [GeV]", 100, 0,    200 ) );
      }
    }

    // jet associated tracks / truth particles
    if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTrk ) {
      // dR-matched tracks
      h_jet_trkCount  .push_back( book( name, hjet + "_trkCount", "jet-matched track count",                    125, 0,   250 ) );
      h_jet_trkPt     .push_back( book( name, hjet + "_trkPt",    "jet-matched track sum-p_{T} [GeV]",          100, 0,  2500 ) );
      h_jet_trkPt_l   .push_back( book( name, hjet + "_trkPt_l",  "jet-matched track sum-p_{T} [GeV]",          100, 0,  5000 ) );
      h_jet_trkPt_m   .push_back( book( name, hjet + "_trkPt_m",  "jet-matched track sum-p_{T} [GeV]",          100, 0,  1500 ) );
      h_jet_trkPt_s   .push_back( book( name, hjet + "_trkPt_s",  "jet-matched track sum-p_{T} [GeV]",          100, 0,   500 ) );
      h_jet_trk_dR    .push_back( book( name, hjet + "_trk_dR",   "jet - matched-track dR",                     100, 0,   0.4 ) );
      // dR-matched truth parts --> may want to add count / pt-sum histos for charged/stable/interacting TPs ...
      if ( mc ) {
	h_jet_tpCount .push_back( book( name, hjet + "_tpCount",  "jet-matched truth particle count",           100, 0,   500 ) );
	h_jet_tpPt    .push_back( book( name, hjet + "_tpPt",     "jet-matched truth particle sum-p_{T} [GeV]", 100, 0, 25000 ) );
	h_jet_tpPt_l  .push_back( book( name, hjet + "_tpPt_l",   "jet-matched truth particle sum-p_{T} [GeV]", 100, 0, 50000 ) );
	h_jet_tpPt_m  .push_back( book( name, hjet + "_tpPt_m",   "jet-matched truth particle sum-p_{T} [GeV]", 100, 0, 15000 ) );
	h_jet_tpPt_s  .push_back( book( name, hjet + "_tpPt_s",   "jet-matched truth particle sum-p_{T} [GeV]", 100, 0,  5000 ) );
	h_jet_tp_dR   .push_back( book( name, hjet + "_tp_dR",    "jet - matched-truth-particle dR",            100, 0,   0.4 ) );
      }
    }

    // jet associated vertices
    if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetVtx ) {
      // dR-matched DVs
      h_jet_secVtxCount     .push_back( book( name, hjet + "_secVtxCount",   "jet-matched secondary vertex count",             7, 0,    7 ) );
      h_jet_secVtxPt        .push_back( book( name, hjet + "_secVtxPt",      "jet-matched secondary vertex sum-p_{T} [GeV]", 100, 0,  100 ) );
      h_jet_secVtx_dR       .push_back( book( name, hjet + "_secVtx_dR",     "jet - matched-secondary-vertex dR",            100, 0,  0.4 ) );
      // dR matched TVs --> may want to add count / pt-sum histos for some subset of DV-like TVs ...
      if ( mc ) {
	h_jet_truthVtxCount .push_back( book( name, hjet + "_truthVtxCount", "jet-matched truth vertex count",               150, 0,  150 ) );
	h_jet_truthVtxPt    .push_back( book( name, hjet + "_truthVtxPt",    "jet-matched truth vertex sum-p_{T} [GeV]",     100, 0, 2500 ) );
	h_jet_truthVtx_dR   .push_back( book( name, hjet + "_truthVtx_dR",   "jet - matched-truth-vertex dR",                100, 0,  0.4 ) );
      }
    }

    // jets vs mu
    if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_jet )  {
      h_jet_n_vs_avgMu             .push_back( book( name, hjet + "_n_vs_avgMu",           "< #mu >", 100, 0,  100,
						     "n jets",                                         15, 0,   15 ) );
      h_jet_pt_vs_avgMu            .push_back( book( name, hjet + "_pt_vs_avgMu",          "< #mu >", 100, 0,  100,
						     "jet p_{T} [GeV]",                               100, 0, 1500 ) );
      h_jet_n_vs_actMu             .push_back( book( name, hjet + "_n_vs_actMu",             "#mu",   100, 0,  100,
						     "n jets",                                         15, 0,   15 ) );
      h_jet_pt_vs_actMu            .push_back( book( name, hjet + "_pt_vs_actMu",            "#mu",   100, 0,  100,
						     "jet p_{T} [GeV]",                               100, 0, 1500 ) );
      if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTrk ) {
	h_jet_trkCount_vs_avgMu    .push_back( book( name, hjet + "_trkCount_vs_avgMu",    "< #mu >", 100, 0,  100,
						     "jet-matched track count",                       125, 0,  250 ) );
	h_jet_trkPt_vs_avgMu       .push_back( book( name, hjet + "_trkPt_vs_avgMu",       "< #mu >", 100, 0,  100,
						     "jet-matched track sum-p_{T} [GeV]",             100, 0, 2500 ) );
	h_jet_trk_dR_vs_avgMu      .push_back( book( name, hjet + "_trk_dR_vs_avgMu",      "< #mu >", 100, 0,  100,
						     "jet - matched track dR",                        100, 0,  0.4 ) );
	h_jet_trkCount_vs_actMu    .push_back( book( name, hjet + "_trkCount_vs_actMu",      "#mu",   100, 0,  100,
						     "jet-matched track count",                       125, 0,  250 ) );
	h_jet_trkPt_vs_actMu       .push_back( book( name, hjet + "_trkPt_vs_actMu",         "#mu",   100, 0,  100,
						     "jet-matched track sum-p_{T} [GeV]",             100, 0, 2500 ) );
	h_jet_trk_dR_vs_actMu      .push_back( book( name, hjet + "_trk_dR_vs_actMu",        "#mu",   100, 0,  100,
						     "jet - matched track dR",                        100, 0,  0.4 ) );
      }
      if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetVtx ) {
	h_jet_secVtxCount_vs_avgMu .push_back( book( name, hjet + "_secVtxCount_vs_avgMu", "< #mu >", 100, 0, 100,
						     "jet-matched secondary vertex count",              7, 0,   7 ) );
	h_jet_secVtxPt_vs_avgMu    .push_back( book( name, hjet + "_secVtxPt_vs_avgMu",    "< #mu >", 100, 0, 100,
						     "jet-matched secondary vertex sum-p_{T} [GeV]",  100, 0, 100 ) );
	h_jet_secVtx_dR_vs_avgMu   .push_back( book( name, hjet + "_secVtx_dR_vs_avgMu",   "< #mu >", 100, 0, 100,
						     "jet - matched secondary vertex dR",             100, 0, 0.4 ) );
	h_jet_secVtxCount_vs_actMu .push_back( book( name, hjet + "_secVtxCount_vs_actMu",   "#mu",   100, 0, 100,
						     "jet-matched secondary vertex count",              7, 0,   7 ) );
	h_jet_secVtxPt_vs_actMu    .push_back( book( name, hjet + "_secVtxPt_vs_actMu",      "#mu",   100, 0, 100,
						     "jet-matched secondary vertex sum-p_{T} [GeV]",  100, 0, 100 ) );
	h_jet_secVtx_dR_vs_actMu   .push_back( book( name, hjet + "_secVtx_dR_vs_actMu",     "#mu",   100, 0, 100,
						     "jet - matched secondary vertex dR",             100, 0, 0.4 ) );
      }
    }


    if ( mc ) {
      // truth jet basics
      h_truthJet_n      .push_back( book( name, "truthJet_n",     "n truth jets",            75,    0,   75 ) );
      h_truthJet_pt     .push_back( book( name, "truthJet_pt",    "truth jet p_{T} [GeV]",  100,    0, 1500 ) );
      h_truthJet_pt_l   .push_back( book( name, "truthJet_pt_l",  "truth jet p_{T} [GeV]",  100,    0, 2500 ) );
      h_truthJet_pt_m   .push_back( book( name, "truthJet_pt_m",  "truth jet p_{T} [GeV]",  100,    0,  500 ) );
      h_truthJet_pt_s   .push_back( book( name, "truthJet_pt_s",  "truth jet p_{T} [GeV]",  100,    0,  200 ) );
      h_truthJet_eta    .push_back( book( name, "truthJet_eta",   "truth jet eta",          100,   -5,    5 ) );
      h_truthJet_phi    .push_back( book( name, "truthJet_phi",   "truth jet phi",          100, -3.5,  3.5 ) );
      h_truthJet_E      .push_back( book( name, "truthJet_E",     "truth jet energy [GeV]", 100,    0, 2500 ) );
      h_truthJet_M      .push_back( book( name, "truthJet_M",     "truth jet mass [GeV]",   100,    0,  300 ) );
      h_truthJet_rapid  .push_back( book( name, "truthJet_rapid", "truth jet rapidity",     100,   -5,    5 ) );
      // truth jet kinematics
      if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
	h_truthJet_px   .push_back( book( name, "truthJet_px",    "truth jet p_{x} [GeV]",  100, -1500, 1500 ) );
	h_truthJet_py   .push_back( book( name, "truthJet_py",    "truth jet p_{y} [GeV]",  100, -1500, 1500 ) );
	h_truthJet_pz   .push_back( book( name, "truthJet_pz",    "truth jet p_{z} [GeV]",  100, -2500, 2500 ) );
	h_truthJet_Et   .push_back( book( name, "truthJet_Et",    "truth jet E_{T} [GeV]",  100,     0, 1500 ) );
	h_truthJet_Et_l .push_back( book( name, "truthJet_Et_l",  "truth jet E_{T} [GeV]",  100,     0, 2500 ) );
	h_truthJet_Et_m .push_back( book( name, "truthJet_Et_m",  "truth jet E_{T} [GeV]",  100,     0,  500 ) );
	h_truthJet_Et_s .push_back( book( name, "truthJet_Et_s",  "truth jet E_{T} [GeV]",  100,     0,  200 ) );
      }
      // leading truth jets
      if ( m_numLead ) {
	std::vector<TH1F*> h_nleadtruth_pt;
	std::vector<TH1F*> h_nleadtruth_pt_l;
	std::vector<TH1F*> h_nleadtruth_pt_m;
	std::vector<TH1F*> h_nleadtruth_pt_s;
	std::vector<TH1F*> h_nleadtruth_eta;
	std::vector<TH1F*> h_nleadtruth_phi;
	std::vector<TH1F*> h_nleadtruth_E;
	std::vector<TH1F*> h_nleadtruth_M;
	std::vector<TH1F*> h_nleadtruth_rapid;
	std::vector<TH1F*> h_nleadtruth_Et;
	std::vector<TH1F*> h_nleadtruth_Et_l;
	std::vector<TH1F*> h_nleadtruth_Et_m;
	std::vector<TH1F*> h_nleadtruth_Et_s;
	for ( int i = 0; i != m_numLead; ++i ) {
	  std::string njet = std::to_string(i);
	  h_nleadtruth_pt    .push_back( book( name, ( "truthJet" + njet + "_pt"    ), ( "truth-jet-" + njet + " p_{T} [GeV]"  ), 100,    0, 1500 ) );
	  h_nleadtruth_pt_l  .push_back( book( name, ( "truthJet" + njet + "_pt_l"  ), ( "truth-jet-" + njet + " p_{T} [GeV]"  ), 100,    0, 2500 ) );
	  h_nleadtruth_pt_m  .push_back( book( name, ( "truthJet" + njet + "_pt_m"  ), ( "truth-jet-" + njet + " p_{T} [GeV]"  ), 100,    0,  500 ) );
	  h_nleadtruth_pt_s  .push_back( book( name, ( "truthJet" + njet + "_pt_s"  ), ( "truth-jet-" + njet + " p_{T} [GeV]"  ), 100,    0,  200 ) );
	  h_nleadtruth_eta   .push_back( book( name, ( "truthJet" + njet + "_eta"   ), ( "truth-jet-" + njet + " eta"          ), 100,   -5,    5 ) );
	  h_nleadtruth_phi   .push_back( book( name, ( "truthJet" + njet + "_phi"   ), ( "truth-jet-" + njet + " phi"          ), 100, -3.5,  3.5 ) );
	  h_nleadtruth_E     .push_back( book( name, ( "truthJet" + njet + "_E"     ), ( "truth-jet-" + njet + " energy [GeV]" ), 100,    0, 2500 ) );
	  h_nleadtruth_M     .push_back( book( name, ( "truthJet" + njet + "_M"     ), ( "truth-jet-" + njet + " mass [GeV]"   ), 100,    0,  300 ) );
	  h_nleadtruth_rapid .push_back( book( name, ( "truthJet" + njet + "_rapid" ), ( "truth-jet-" + njet + " rapidity"     ), 100,   -5,    5 ) );
	  h_nleadtruth_Et    .push_back( book( name, ( "truthJet" + njet + "_Et"    ), ( "truth-jet-" + njet + " E_{T} [GeV]"  ), 100,    0, 1500 ) );
	  h_nleadtruth_Et_l  .push_back( book( name, ( "truthJet" + njet + "_Et_l"  ), ( "truth-jet-" + njet + " E_{T} [GeV]"  ), 100,    0, 2500 ) );
	  h_nleadtruth_Et_m  .push_back( book( name, ( "truthJet" + njet + "_Et_m"  ), ( "truth-jet-" + njet + " E_{T} [GeV]"  ), 100,    0,  500 ) );
	  h_nleadtruth_Et_s  .push_back( book( name, ( "truthJet" + njet + "_Et_s"  ), ( "truth-jet-" + njet + " E_{T} [GeV]"  ), 100,    0,  200 ) );
	}
	h_truthJetN_pt    .push_back( h_nleadtruth_pt    );
	h_truthJetN_pt_l  .push_back( h_nleadtruth_pt_l  );
	h_truthJetN_pt_m  .push_back( h_nleadtruth_pt_m  );
	h_truthJetN_pt_s  .push_back( h_nleadtruth_pt_s  );
	h_truthJetN_eta   .push_back( h_nleadtruth_eta   );
	h_truthJetN_phi   .push_back( h_nleadtruth_phi   );
	h_truthJetN_E     .push_back( h_nleadtruth_E     );
	h_truthJetN_M     .push_back( h_nleadtruth_M     );
	h_truthJetN_rapid .push_back( h_nleadtruth_rapid );
	// leading truth jet kinematics
	if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
	  h_truthJetN_Et   .push_back( h_nleadtruth_Et   );
	  h_truthJetN_Et_l .push_back( h_nleadtruth_Et_l );
	  h_truthJetN_Et_m .push_back( h_nleadtruth_Et_m );
	  h_truthJetN_Et_s .push_back( h_nleadtruth_Et_s );
	}
      }
      
      // truth jet width, constituents
      if ( m_histoInfoSwitch ->m_jetEConstit ) {
	h_truthJet_width      .push_back( book( name, "truthJet_width",      "truth jet width",                       100, 0,  0.4 ) );
	h_truthJet_girth      .push_back( book( name, "truthJet_girth",      "truth jet girth",                       100, 0,  0.5 ) );
	h_truthJet_numConstit .push_back( book( name, "truthJet_numConstit", "n truth jet constituents",              100, 0,  200 ) );
	h_truthJet_constitPt  .push_back( book( name, "truthJet_constitPt",  "truth-jet constituent sum-p_{T} [GeV]", 100, 0, 2000 ) );
	h_truthJet_constit_dR .push_back( book( name, "truthJet_constit_dR", "truth-jet - constituent dR",            100, 0,  4.5 ) );
      }
      
      // truth-jet associated tracks / truth particles
      if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTrk ) {
	// dR-matched tracks
	h_truthJet_trkCount .push_back( book( name, "truthJet_trkCount", "truth-jet-matched track count",                    125, 0,   250 ) );
	h_truthJet_trkPt    .push_back( book( name, "truthJet_trkPt",    "truth-jet-matched track sum-p_{T} [GeV]",          100, 0,  2500 ) );
	h_truthJet_trkPt_l  .push_back( book( name, "truthJet_trkPt_l",  "truth-jet-matched track sum-p_{T} [GeV]",          100, 0,  5000 ) );
	h_truthJet_trkPt_m  .push_back( book( name, "truthJet_trkPt_m",  "truth-jet-matched track sum-p_{T} [GeV]",          100, 0,  1500 ) );
	h_truthJet_trkPt_s  .push_back( book( name, "truthJet_trkPt_s",  "truth-jet-matched track sum-p_{T} [GeV]",          100, 0,   500 ) );
	h_truthJet_trk_dR   .push_back( book( name, "truthJet_trk_dR",   "truth-jet - matched-track dR",                     100, 0,   0.4 ) );
	// dR-matched truth parts --> may want to add count / pt-sum histos for charged/stable/interacting TPs ...
	h_truthJet_tpCount  .push_back( book( name, "truthJet_tpCount",  "truth-jet-matched truth particle count",           100, 0,   500 ) );
	h_truthJet_tpPt     .push_back( book( name, "truthJet_tpPt",     "truth-jet-matched truth particle sum-p_{T} [GeV]", 100, 0, 25000 ) );
	h_truthJet_tpPt_l   .push_back( book( name, "truthJet_tpPt_l",   "truth-jet-matched truth particle sum-p_{T} [GeV]", 100, 0, 50000 ) );
	h_truthJet_tpPt_m   .push_back( book( name, "truthJet_tpPt_m",   "truth-jet-matched truth particle sum-p_{T} [GeV]", 100, 0, 15000 ) );
	h_truthJet_tpPt_s   .push_back( book( name, "truthJet_tpPt_s",   "truth-jet-matched truth particle sum-p_{T} [GeV]", 100, 0,  5000 ) );
	h_truthJet_tp_dR    .push_back( book( name, "truthJet_tp_dR",    "truth-jet - matched-truth-particle dR",            100, 0,   0.4 ) );
      }
      
      // truth-jet associated vertices
      if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetVtx ) {
	// dR-matched DVs
	h_truthJet_secVtxCount   .push_back( book( name, "truthJet_secVtxCount",   "truth-jet-matched secondary vertex count",             7, 0,    7 ) );
	h_truthJet_secVtxPt      .push_back( book( name, "truthJet_secVtxPt",      "truth-jet-matched secondary vertex sum-p_{T} [GeV]", 100, 0,  100 ) );
	h_truthJet_secVtx_dR     .push_back( book( name, "truthJet_secVtx_dR",     "truth-jet - matched-secondary-vertex dR",            100, 0,  0.4 ) );
	// dR-matched TVs --> may want to add count / pt-sum histos for some subset of DV-like TVs ...
	h_truthJet_truthVtxCount .push_back( book( name, "truthJet_truthVtxCount", "truth-jet-matched truth vertex count",               100, 0,  150 ) );
	h_truthJet_truthVtxPt    .push_back( book( name, "truthJet_truthVtxPt",    "truth-jet-matched truth vertex sum-p_{T} [GeV]",     100, 0, 2500 ) );
	h_truthJet_truthVtx_dR   .push_back( book( name, "truthJet_truthVtx_dR",   "truth-jet - matched-truth-vertex dR",                100, 0,  0.4 ) );
      }

      // truth jets vs mu
      if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_jet ) {
	h_truthJet_n_vs_avgMu  .push_back( book( name, "truthJet_n_vs_avgMu",  "< #mu >", 100, 0, 100, "n truth jets",           75, 0,   75 ) );
	h_truthJet_pt_vs_avgMu .push_back( book( name, "truthJet_pt_vs_avgMu", "< #mu >", 100, 0, 100, "truth jet p_{T} [GeV]", 100, 0, 1500 ) );
	h_truthJet_n_vs_actMu  .push_back( book( name, "truthJet_n_vs_actMu",    "#mu",   100, 0, 100, "n truth jets",           75, 0,   75 ) );
	h_truthJet_pt_vs_actMu .push_back( book( name, "truthJet_pt_vs_actMu",   "#mu",   100, 0, 100, "truth jet p_{T} [GeV]", 100, 0, 1500 ) );
      }


      // dark jet basics
      h_darkJet_n     .push_back( book( name, "darkJet_n",     "n dark jets",            50,    0,   50 ) );
      h_darkJet_pt    .push_back( book( name, "darkJet_pt",    "dark jet p_{T} [GeV]",  100,    0, 1500 ) );
      h_darkJet_pt_l  .push_back( book( name, "darkJet_pt_l",  "dark jet p_{T} [GeV]",  100,    0, 2500 ) );
      h_darkJet_pt_m  .push_back( book( name, "darkJet_pt_m",  "dark jet p_{T} [GeV]",  100,    0,  500 ) );
      h_darkJet_pt_s  .push_back( book( name, "darkJet_pt_s",  "dark jet p_{T} [GeV]",  100,    0,  200 ) );
      h_darkJet_eta   .push_back( book( name, "darkJet_eta",   "dark jet eta",          100,   -5,    5 ) );
      h_darkJet_phi   .push_back( book( name, "darkJet_phi",   "dark jet phi",          100, -3.5,  3.5 ) );
      h_darkJet_E     .push_back( book( name, "darkJet_E",     "dark jet energy [GeV]", 100,    0, 2500 ) );
      h_darkJet_M     .push_back( book( name, "darkJet_M",     "dark jet mass [GeV]",   100,    0,  300 ) );
      h_darkJet_rapid .push_back( book( name, "darkJet_rapid", "dark jet rapidity",     100,   -5,    5 ) );
      // dark jet kinematics
      if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
	h_darkJet_px   .push_back( book( name, "darkJet_px",    "dark jet p_{x} [GeV]",  100, -1500, 1500 ) );
	h_darkJet_py   .push_back( book( name, "darkJet_py",    "dark jet p_{y} [GeV]",  100, -1500, 1500 ) );
	h_darkJet_pz   .push_back( book( name, "darkJet_pz",    "dark jet p_{z} [GeV]",  100, -2500, 2500 ) );
	h_darkJet_Et   .push_back( book( name, "darkJet_Et",    "dark jet E_{T} [GeV]",  100,     0, 1500 ) );
	h_darkJet_Et_l .push_back( book( name, "darkJet_Et_l",  "dark jet E_{T} [GeV]",  100,     0, 2500 ) );
	h_darkJet_Et_m .push_back( book( name, "darkJet_Et_m",  "dark jet E_{T} [GeV]",  100,     0,  500 ) );
	h_darkJet_Et_s .push_back( book( name, "darkJet_Et_s",  "dark jet E_{T} [GeV]",  100,     0,  200 ) );
      }
      // leading dark jets
      if ( m_numLead ) {
	std::vector<TH1F*> h_nleaddark_pt;
	std::vector<TH1F*> h_nleaddark_pt_l;
	std::vector<TH1F*> h_nleaddark_pt_m;
	std::vector<TH1F*> h_nleaddark_pt_s;
	std::vector<TH1F*> h_nleaddark_eta;
	std::vector<TH1F*> h_nleaddark_phi;
	std::vector<TH1F*> h_nleaddark_E;
	std::vector<TH1F*> h_nleaddark_M;
	std::vector<TH1F*> h_nleaddark_rapid;
	std::vector<TH1F*> h_nleaddark_Et;
	std::vector<TH1F*> h_nleaddark_Et_l;
	std::vector<TH1F*> h_nleaddark_Et_m;
	std::vector<TH1F*> h_nleaddark_Et_s;
	for ( int i = 0; i != m_numLead; ++i ) {
	  std::string njet = std::to_string(i);
	  h_nleaddark_pt    .push_back( book( name, ( "darkJet" + njet + "_pt"    ), ( "dark-jet-" + njet + " p_{T} [GeV]"  ), 100,    0, 1500 ) );
	  h_nleaddark_pt_l  .push_back( book( name, ( "darkJet" + njet + "_pt_l"  ), ( "dark-jet-" + njet + " p_{T} [GeV]"  ), 100,    0, 2500 ) );
	  h_nleaddark_pt_m  .push_back( book( name, ( "darkJet" + njet + "_pt_m"  ), ( "dark-jet-" + njet + " p_{T} [GeV]"  ), 100,    0,  500 ) );
	  h_nleaddark_pt_s  .push_back( book( name, ( "darkJet" + njet + "_pt_s"  ), ( "dark-jet-" + njet + " p_{T} [GeV]"  ), 100,    0,  200 ) );
	  h_nleaddark_eta   .push_back( book( name, ( "darkJet" + njet + "_eta"   ), ( "dark-jet-" + njet + " eta"          ), 100,   -5,    5 ) );
	  h_nleaddark_phi   .push_back( book( name, ( "darkJet" + njet + "_phi"   ), ( "dark-jet-" + njet + " phi"          ), 100, -3.5,  3.5 ) );
	  h_nleaddark_E     .push_back( book( name, ( "darkJet" + njet + "_E"     ), ( "dark-jet-" + njet + " energy [GeV]" ), 100,    0, 2500 ) );
	  h_nleaddark_M     .push_back( book( name, ( "darkJet" + njet + "_M"     ), ( "dark-jet-" + njet + " mass [GeV]"   ), 100,    0,  300 ) );
	  h_nleaddark_rapid .push_back( book( name, ( "darkJet" + njet + "_rapid" ), ( "dark-jet-" + njet + " rapidity"     ), 100,   -5,    5 ) );
	  h_nleaddark_Et    .push_back( book( name, ( "darkJet" + njet + "_Et"    ), ( "dark-jet-" + njet + " E_{T} [GeV]"  ), 100,    0, 1500 ) );
	  h_nleaddark_Et_l  .push_back( book( name, ( "darkJet" + njet + "_Et_l"  ), ( "dark-jet-" + njet + " E_{T} [GeV]"  ), 100,    0, 2500 ) );
	  h_nleaddark_Et_m  .push_back( book( name, ( "darkJet" + njet + "_Et_m"  ), ( "dark-jet-" + njet + " E_{T} [GeV]"  ), 100,    0,  500 ) );
	  h_nleaddark_Et_s  .push_back( book( name, ( "darkJet" + njet + "_Et_s"  ), ( "dark-jet-" + njet + " E_{T} [GeV]"  ), 100,    0,  200 ) );
	}
	h_darkJetN_pt    .push_back( h_nleaddark_pt    );
	h_darkJetN_pt_l  .push_back( h_nleaddark_pt_l  );
	h_darkJetN_pt_m  .push_back( h_nleaddark_pt_m  );
	h_darkJetN_pt_s  .push_back( h_nleaddark_pt_s  );
	h_darkJetN_eta   .push_back( h_nleaddark_eta   );
	h_darkJetN_phi   .push_back( h_nleaddark_phi   );
	h_darkJetN_E     .push_back( h_nleaddark_E     );
	h_darkJetN_M     .push_back( h_nleaddark_M     );
	h_darkJetN_rapid .push_back( h_nleaddark_rapid );
	// leading dark jet kinematics
	if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
	  h_darkJetN_Et   .push_back( h_nleaddark_Et   );
	  h_darkJetN_Et_l .push_back( h_nleaddark_Et_l );
	  h_darkJetN_Et_m .push_back( h_nleaddark_Et_m );
	  h_darkJetN_Et_s .push_back( h_nleaddark_Et_s );
	}
      }
      
      // dark jet constituents
      if ( m_histoInfoSwitch ->m_jetEConstit ) {
	h_darkJet_girth      .push_back( book( name, "darkJet_girth",      "dark jet girth",                       100, 0,  0.5 ) );
	h_darkJet_numConstit .push_back( book( name, "darkJet_numConstit", "n dark jet constituents",               25, 0,   25 ) );
	h_darkJet_constitPt  .push_back( book( name, "darkJet_constitPt",  "dark-jet constituent sum-p_{T} [GeV]", 100, 0, 2000 ) );
	h_darkJet_constit_dR .push_back( book( name, "darkJet_constit_dR", "dark-jet - constituent dR",            100, 0,  0.4 ) );
      }

      // dark-jet associated tracks / truth particles
      if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTrk ) {
	// dR-matched tracks
	h_darkJet_trkCount .push_back( book( name, "darkJet_trkCount", "dark-jet-matched track count",                    125, 0,   250 ) );
	h_darkJet_trkPt    .push_back( book( name, "darkJet_trkPt",    "dark-jet-matched track sum-p_{T} [GeV]",          100, 0,  2500 ) );
	h_darkJet_trkPt_l  .push_back( book( name, "darkJet_trkPt_l",  "dark-jet-matched track sum-p_{T} [GeV]",          100, 0,  5000 ) );
	h_darkJet_trkPt_m  .push_back( book( name, "darkJet_trkPt_m",  "dark-jet-matched track sum-p_{T} [GeV]",          100, 0,  1500 ) );
	h_darkJet_trkPt_s  .push_back( book( name, "darkJet_trkPt_s",  "dark-jet-matched track sum-p_{T} [GeV]",          100, 0,   500 ) );
	h_darkJet_trk_dR   .push_back( book( name, "darkJet_trk_dR",   "dark-jet - matched-track dR",                     100, 0,   0.4 ) );
	// dR-matched truth parts --> may want to add count / pt-sum histos for charged/stable/interacting TPs ...
	h_darkJet_tpCount  .push_back( book( name, "darkJet_tpCount",  "dark-jet-matched truth particle count",           100, 0,   500 ) );
	h_darkJet_tpPt     .push_back( book( name, "darkJet_tpPt",     "dark-jet-matched truth particle sum-p_{T} [GeV]", 100, 0, 25000 ) );
	h_darkJet_tpPt_l   .push_back( book( name, "darkJet_tpPt_l",   "dark-jet-matched truth particle sum-p_{T} [GeV]", 100, 0, 50000 ) );
	h_darkJet_tpPt_m   .push_back( book( name, "darkJet_tpPt_m",   "dark-jet-matched truth particle sum-p_{T} [GeV]", 100, 0, 15000 ) );
	h_darkJet_tpPt_s   .push_back( book( name, "darkJet_tpPt_s",   "dark-jet-matched truth particle sum-p_{T} [GeV]", 100, 0,  5000 ) );
	h_darkJet_tp_dR    .push_back( book( name, "darkJet_tp_dR",    "dark-jet - matched-truth-particle dR",            100, 0,   0.4 ) );
      }

      // dark-jet associated vertices
      if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetVtx ) {
	// dR-matched DVs
	h_darkJet_secVtxCount   .push_back( book( name, "darkJet_secVtxCount",   "dark-jet-matched secondary vertex count",             7, 0,    7 ) );
	h_darkJet_secVtxPt      .push_back( book( name, "darkJet_secVtxPt",      "dark-jet-matched secondary vertex sum-p_{T} [GeV]", 100, 0,  100 ) );
	h_darkJet_secVtx_dR     .push_back( book( name, "darkJet_secVtx_dR",     "dark-jet - matched-secondary-vertex dR",            100, 0,  0.4 ) );
	// dR-matched TVs --> may want to add count / pt-sum histos for some subset of DV-like TVs ...
	h_darkJet_truthVtxCount .push_back( book( name, "darkJet_truthVtxCount", "dark-jet-matched truth vertex count",               100, 0,  150 ) );
	h_darkJet_truthVtxPt    .push_back( book( name, "darkJet_truthVtxPt",    "dark-jet-matched truth vertex sum-p_{T} [GeV]",     100, 0, 2500 ) );
	h_darkJet_truthVtx_dR   .push_back( book( name, "darkJet_truthVtx_dR",   "dark-jet - matched-truth-vertex dR",                100, 0,  0.4 ) );
      }

      // dark jets vs mu
      if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_jet ) {
	h_darkJet_n_vs_avgMu  .push_back( book( name, "darkJet_n_vs_avgMu",  "< #mu >", 100, 0, 100, "n dark jets",           50, 0,   50 ) );
	h_darkJet_pt_vs_avgMu .push_back( book( name, "darkJet_pt_vs_avgMu", "< #mu >", 100, 0, 100, "dark jet p_{T} [GeV]", 100, 0, 1500 ) );
	h_darkJet_n_vs_actMu  .push_back( book( name, "darkJet_n_vs_actMu",    "#mu",   100, 0, 100, "n dark jets",           50, 0,   50 ) );
	h_darkJet_pt_vs_actMu .push_back( book( name, "darkJet_pt_vs_actMu",   "#mu",   100, 0, 100, "dark jet p_{T} [GeV]", 100, 0, 1500 ) );
      }
    } // end if mc (truth (dark) jets)


    if ( mc ) {
      // heavy scalar mediator (Xd) basics
      h_Xd_n                 .push_back( book( name, "Xd_n",                 "n scalar mediators",                                    5,       0,       5 ) );
      h_Xd_pt                .push_back( book( name, "Xd_pt",                "scalar mediator p_{T} [GeV]",                         100,       0,    2500 ) );
      h_Xd_eta               .push_back( book( name, "Xd_eta",               "scalar mediator eta",                                 100,      -5,       5 ) );
      h_Xd_phi               .push_back( book( name, "Xd_phi",               "scalar mediator phi",                                 100,    -3.5,     3.5 ) );
      h_Xd_E                 .push_back( book( name, "Xd_E",                 "scalar mediator energy [GeV]",                        100,       0,    4000 ) );
      h_Xd_M                 .push_back( book( name, "Xd_M",                 "scalar mediator mass [GeV]",                          100,       0,    2000 ) );
      h_Xd_charge            .push_back( book( name, "Xd_charge",            "scalar mediator charge",                              100,      -1,       1 ) );
      h_Xd_nParents          .push_back( book( name, "Xd_nParents",          "n scalar mediator parents",                             5,       0,       5 ) );
      h_Xd_parentPdgId       .push_back( book( name, "Xd_parentPdgId",       "scalar mediator parent pdgId",                          5, 4900000, 4900005 ) );
      h_Xd_parentStatus      .push_back( book( name, "Xd_parentStatus",      "scalar mediator parent status",                       100,       0,     100 ) );
      h_Xd_nChildren         .push_back( book( name, "Xd_nChildren",         "n scalar mediator children",                            5,       0,       5 ) );
      h_Xd_childPdgId        .push_back( book( name, "Xd_childPdgId",        "scalar mediator child pdgId",                         100,       0, 4900105 ) );
      h_Xd_childStatus       .push_back( book( name, "Xd_childStatus",       "scalar mediator child status",                        100,       0,     100 ) );
      h_Xd_prodVtx_r         .push_back( book( name, "Xd_prodVtx_r",         "scalar mediator production vertex r-pos [mm]",        100,       0,       1 ) );
      h_Xd_decayVtx_r        .push_back( book( name, "Xd_decayVtx_r",        "scalar mediator decay vertex r-pos [mm]",             100,       0,       1 ) );
      // dark quark (qd) basics
      h_qd_n                 .push_back( book( name, "qd_n",                 "n dark quarks",                                         5,       0,       5 ) );
      h_qd_pt                .push_back( book( name, "qd_pt",                "dark quark p_{T} [GeV]",                              100,       0,    1500 ) );
      h_qd_eta               .push_back( book( name, "qd_eta",               "dark quark eta",                                      100,      -5,       5 ) );
      h_qd_phi               .push_back( book( name, "qd_phi",               "dark quark phi",                                      100,    -3.5,     3.5 ) );
      h_qd_E                 .push_back( book( name, "qd_E",                 "dark quark energy [GeV]",                             100,       0,    2000 ) );
      h_qd_M                 .push_back( book( name, "qd_M",                 "dark quark mass [GeV]",                               100,       0,      50 ) );
      h_qd_charge            .push_back( book( name, "qd_charge",            "dark quark charge",                                   100,      -1,       1 ) );
      h_qd_nParents          .push_back( book( name, "qd_nParents",          "n dark quark parents",                                  5,       0,       5 ) );
      h_qd_parentPdgId       .push_back( book( name, "qd_parentPdgId",       "dark quarks parent pdgId",                              5, 4900100, 4900105 ) );
      h_qd_parentStatus      .push_back( book( name, "qd_parentStatus",      "dark quark parent status",                            100,       0,     100 ) );
      h_qd_nChildren         .push_back( book( name, "qd_nChildren",         "n dark quark children",                               100,       0,     100 ) );
      h_qd_childPdgId        .push_back( book( name, "qd_childPdgId",        "dark quark child pdgId",                              125, 4900100, 4900225 ) );
      h_qd_childStatus       .push_back( book( name, "qd_childStatus",       "dark quark child status",                             100,       0,     100 ) );
      h_qd_prodVtx_r         .push_back( book( name, "qd_prodVtx_r",         "dark quark production vertex r-pos [mm]",             100,       0,       1 ) );
      h_qd_decayVtx_r        .push_back( book( name, "qd_decayVtx_r",        "dark quark decay vertex r-pos [mm]",                  100,       0,       1 ) );
      // dark pion (pid) basics
      h_pid_n                .push_back( book( name, "pid_n",                "n dark pions",                                        150,       0,     150 ) );
      h_pid_pt               .push_back( book( name, "pid_pt",               "dark pion p_{T} [GeV]",                               100,       0,     350 ) );
      h_pid_eta              .push_back( book( name, "pid_eta",              "dark pion eta",                                       100,      -5,       5 ) );
      h_pid_phi              .push_back( book( name, "pid_phi",              "dark pion phi",                                       100,    -3.5,     3.5 ) );
      h_pid_E                .push_back( book( name, "pid_E",                "dark pion energy [GeV]",                              100,       0,     500 ) );
      h_pid_M                .push_back( book( name, "pid_M",                "dark pion mass [GeV]",                                100,       0,      25 ) );
      h_pid_charge           .push_back( book( name, "pid_charge",           "dark pion charge",                                    100,      -1,       1 ) );
      h_pid_nParents         .push_back( book( name, "pid_nParents",         "n dark pion parents",                                   5,       0,       5 ) );
      h_pid_parentPdgId      .push_back( book( name, "pid_parentPdgId",      "dark pion parent pdgId",                              125, 4900000, 4900125 ) );
      h_pid_parentStatus     .push_back( book( name, "pid_parentStatus",     "dark pion parent status",                             100,       0,     100 ) );
      h_pid_nChildren        .push_back( book( name, "pid_nChildren",        "n dark pion children",                                  5,       0,       5 ) );
      h_pid_childPdgId       .push_back( book( name, "pid_childPdgId",       "dark pion child pdgId",                                 5,       0,       5 ) );
      h_pid_childStatus      .push_back( book( name, "pid_childStatus",      "dark pion child status",                              100,       0,     100 ) );
      h_pid_prodVtx_r        .push_back( book( name, "pid_prodVtx_r",        "dark pion production vertex r-pos [mm]",              100,       0,       1 ) );
      h_pid_decayVtx_r       .push_back( book( name, "pid_decayVtx_r",       "dark pion decay vertex r-pos [mm]",                   100,       0,    2500 ) );
      // off-diagonal dark pion (offpid) basics
      h_offpid_n             .push_back( book( name, "offpid_n",             "n off-diagaonal dark pions",                          150,       0,     150 ) );
      h_offpid_pt            .push_back( book( name, "offpid_pt",            "off-diagonal dark pion p_{T} [GeV]",                  100,       0,     350 ) );
      h_offpid_eta           .push_back( book( name, "offpid_eta",           "off-diagonal dark pion eta",                          100,      -5,       5 ) );
      h_offpid_phi           .push_back( book( name, "offpid_phi",           "off-diagonal dark pion phi",                          100,    -3.5,     3.5 ) );
      h_offpid_E             .push_back( book( name, "offpid_E",             "off-diagonal dark pion energy [GeV]",                 100,       0,     500 ) );
      h_offpid_M             .push_back( book( name, "offpid_M",             "off-diagonal dark pion mass [GeV]",                   100,       0,      25 ) );
      h_offpid_charge        .push_back( book( name, "offpid_charge",        "off-diagonal dark pion charge",                       100,    -1.5,     1.5 ) );
      h_offpid_nParents      .push_back( book( name, "offpid_nParents",      "off-diagonal n dark pion parents",                    100,       0,     100 ) );
      h_offpid_parentPdgId   .push_back( book( name, "offpid_parentPdgId",   "off-diagonal dark pion parent pdgId",                 225, 4900000, 4900225 ) );
      h_offpid_parentStatus  .push_back( book( name, "offpid_parentStatus",  "off-diagonal dark pion parent status",                100,       0,     100 ) );
      h_offpid_nChildren     .push_back( book( name, "offpid_nChildren",     "n off-diagonal dark pion children",                     5,       0,       5 ) );
      h_offpid_childPdgId    .push_back( book( name, "offpid_childPdgId",    "off-diagonal dark pion child pdgId",                    5,       0,       5 ) );
      h_offpid_childStatus   .push_back( book( name, "offpid_childStatus",   "off-diagonal dark pion child status",                 100,       0,     100 ) );
      h_offpid_prodVtx_r     .push_back( book( name, "offpid_prodVtx_r",     "off-diagonal dark pion production vertex r-pos [mm]", 100,       0,       1 ) );
      h_offpid_decayVtx_r    .push_back( book( name, "offpid_decayVtx_r",    "off-diagonal dark pion decay vertex r-pos [mm]",      100,       0,    2500 ) );
      // inclusive (standard + off-diagonal) dark pion (allpid) basics
      h_allpid_n             .push_back( book( name, "allpid_n",             "n inclusive dark pions",                              150,       0,     150 ) );
      h_allpid_pt            .push_back( book( name, "allpid_pt",            "inclusive dark pion p_{T} [GeV]",                     100,       0,     350 ) );
      h_allpid_eta           .push_back( book( name, "allpid_eta",           "inclusive dark pion eta",                             100,      -5,       5 ) );
      h_allpid_phi           .push_back( book( name, "allpid_phi",           "inclusive dark pion phi",                             100,    -3.5,     3.5 ) );
      h_allpid_E             .push_back( book( name, "allpid_E",             "inclusive dark pion energy [GeV]",                    100,       0,     500 ) );
      h_allpid_M             .push_back( book( name, "allpid_M",             "inclusive dark pion mass [GeV]",                      100,       0,      25 ) );
      h_allpid_charge        .push_back( book( name, "allpid_charge",        "inclusive dark pion charge",                          100,    -1.5,     1.5 ) );
      h_allpid_nParents      .push_back( book( name, "allpid_nParents",      "n inclusive dark pion parents",                       100,       0,     100 ) );
      h_allpid_parentPdgId   .push_back( book( name, "allpid_parentPdgId",   "inclusive dark pion parent pdgId",                    225, 4900000, 4900225 ) );
      h_allpid_parentStatus  .push_back( book( name, "allpid_parentStatus",  "inclusive dark pion parent status",                   100,       0,     100 ) );
      h_allpid_nChildren     .push_back( book( name, "allpid_nChildren",     "n inclusive dark pion children",                        5,       0,       5 ) );
      h_allpid_childPdgId    .push_back( book( name, "allpid_childPdgId",    "inclusive dark pion child pdgId",                       5,       0,       5 ) );
      h_allpid_childStatus   .push_back( book( name, "allpid_childStatus",   "inclusive dark pion child status",                    100,       0,     100 ) );
      h_allpid_prodVtx_r     .push_back( book( name, "allpid_prodVtx_r",     "inclusive dark pion production vertex r-pos [mm]",    100,       0,       1 ) );
      h_allpid_decayVtx_r    .push_back( book( name, "allpid_decayVtx_r",    "inclusive dark pion decay vertex r-pos [mm]",         100,       0,    2500 ) );
      // dark rho (rhod) basics
      h_rhod_n               .push_back( book( name, "rhod_n",               "n dark rhos",                                          50,       0,      50 ) );
      h_rhod_pt              .push_back( book( name, "rhod_pt",              "dark rho p_{T} [GeV]",                                100,       0,     500 ) );
      h_rhod_eta             .push_back( book( name, "rhod_eta",             "dark rho eta",                                        100,      -5,       5 ) );
      h_rhod_phi             .push_back( book( name, "rhod_phi",             "dark rho phi",                                        100,    -3.5,     3.5 ) );
      h_rhod_E               .push_back( book( name, "rhod_E",               "dark rho energy [GeV]",                               100,       0,     750 ) );
      h_rhod_M               .push_back( book( name, "rhod_M",               "dark rho mass [GeV]",                                 100,       0,     100 ) );
      h_rhod_charge          .push_back( book( name, "rhod_charge",          "dark rho charge",                                     100,      -1,       1 ) );
      h_rhod_nParents        .push_back( book( name, "rhod_nParents",        "n dark rho parents",                                  100,       0,     100 ) );
      h_rhod_parentPdgId     .push_back( book( name, "rhod_parentPdgId",     "dark rho parent pdgId",                               125, 4900000, 4900125 ) );
      h_rhod_parentStatus    .push_back( book( name, "rhod_parentStatus",    "dark rho parent status",                              100,       0,     100 ) );
      h_rhod_nChildren       .push_back( book( name, "rhod_nChildren",       "n dark rho children",                                  15,       0,      15 ) );
      h_rhod_childPdgId      .push_back( book( name, "rhod_childPdgId",      "dark rho child pdgId",                                100,       0, 4900125 ) );
      h_rhod_childStatus     .push_back( book( name, "rhod_childStatus",     "dark rho child status",                               100,       0,     100 ) );
      h_rhod_prodVtx_r       .push_back( book( name, "rhod_prodVtx_r",       "dark rho production vertex r-pos [mm]",               100,       0,       1 ) );
      h_rhod_decayVtx_r      .push_back( book( name, "rhod_decayVtx_r",      "dark rho decay vertex r-pos [mm]",                    100,       0,       1 ) );
      // off-diagonal dark rho (offrhod) basics
      h_offrhod_n            .push_back( book( name, "offrhod_n",            "n off-diagaonal dark rhos",                            50,       0,      50 ) );
      h_offrhod_pt           .push_back( book( name, "offrhod_pt",           "off-diagonal dark rho p_{T} [GeV]",                   100,       0,     500 ) );
      h_offrhod_eta          .push_back( book( name, "offrhod_eta",          "off-diagonal dark rho eta",                           100,      -5,       5 ) );
      h_offrhod_phi          .push_back( book( name, "offrhod_phi",          "off-diagonal dark rho phi",                           100,    -3.5,     3.5 ) );
      h_offrhod_E            .push_back( book( name, "offrhod_E",            "off-diagonal dark rho energy [GeV]",                  100,       0,     750 ) );
      h_offrhod_M            .push_back( book( name, "offrhod_M",            "off-diagonal dark rho mass [GeV]",                    100,       0,     100 ) );
      h_offrhod_charge       .push_back( book( name, "offrhod_charge",       "off-diagonal dark rho charge",                        100,    -1.5,     1.5 ) );
      h_offrhod_nParents     .push_back( book( name, "offrhod_nParents",     "off-diagonal n dark rho parents",                     100,       0,     100 ) );
      h_offrhod_parentPdgId  .push_back( book( name, "offrhod_parentPdgId",  "off-diagonal dark rho parent pdgId",                  225, 4900000, 4900225 ) );
      h_offrhod_parentStatus .push_back( book( name, "offrhod_parentStatus", "off-diagonal dark rho parent status",                 100,       0,     100 ) );
      h_offrhod_nChildren    .push_back( book( name, "offrhod_nChildren",    "n off-diagonal dark rho children",                     15,       0,      15 ) );
      h_offrhod_childPdgId   .push_back( book( name, "offrhod_childPdgId",   "off-diagonal dark rho child pdgId",                   100,       0, 4900225 ) );
      h_offrhod_childStatus  .push_back( book( name, "offrhod_childStatus",  "off-diagonal dark rho child status",                  100,       0,     100 ) );
      h_offrhod_prodVtx_r    .push_back( book( name, "offrhod_prodVtx_r",    "off-diagonal dark rho production vertex r-pos [mm]",  100,       0,       1 ) );
      h_offrhod_decayVtx_r   .push_back( book( name, "offrhod_decayVtx_r",   "off-diagonal dark rho decay vertex r-pos [mm]",       100,       0,       1 ) );
      // inclusive (standard + off-diagonal) dark rho (allrhod) basics
      h_allrhod_n            .push_back( book( name, "allrhod_n",            "n inclusive dark rhos",                                50,       0,      50 ) );
      h_allrhod_pt           .push_back( book( name, "allrhod_pt",           "inclusive dark rho p_{T} [GeV]",                      100,       0,     500 ) );
      h_allrhod_eta          .push_back( book( name, "allrhod_eta",          "inclusive dark rho eta",                              100,      -5,       5 ) );
      h_allrhod_phi          .push_back( book( name, "allrhod_phi",          "inclusive dark rho phi",                              100,    -3.5,     3.5 ) );
      h_allrhod_E            .push_back( book( name, "allrhod_E",            "inclusive dark rho energy [GeV]",                     100,       0,     750 ) );
      h_allrhod_M            .push_back( book( name, "allrhod_M",            "inclusive dark rho mass [GeV]",                       100,       0,     100 ) );
      h_allrhod_charge       .push_back( book( name, "allrhod_charge",       "inclusive dark rho charge",                           100,    -1.5,     1.5 ) );
      h_allrhod_nParents     .push_back( book( name, "allrhod_nParents",     "n inclusive dark rho parents",                        100,       0,     100 ) );
      h_allrhod_parentPdgId  .push_back( book( name, "allrhod_parentPdgId",  "inclusive dark rho parent pdgId",                     225, 4900000, 4900225 ) );
      h_allrhod_parentStatus .push_back( book( name, "allrhod_parentStatus", "inclusive dark rho parent status",                    100,       0,     100 ) );
      h_allrhod_nChildren    .push_back( book( name, "allrhod_nChildren",    "n inclusive dark rho children",                        15,       0,      15 ) );
      h_allrhod_childPdgId   .push_back( book( name, "allrhod_childPdgId",   "inclusive dark rho child pdgId",                      100,       0, 4900225 ) );
      h_allrhod_childStatus  .push_back( book( name, "allrhod_childStatus",  "inclusive dark rho child status",                     100,       0,     100 ) );
      h_allrhod_prodVtx_r    .push_back( book( name, "allrhod_prodVtx_r",    "inclusive dark rho production vertex r-pos [mm]",     100,       0,       1 ) );
      h_allrhod_decayVtx_r   .push_back( book( name, "allrhod_decayVtx_r",   "inclusive dark rho decay vertex r-pos [mm]",          100,       0,       1 ) );
    } // end if mc (truth particles)


    // secondary vertex basics
    h_secVtx_n                .push_back( book( name, "secVtx_n",                "n secondary vertices",                             20,     0,   20 ) );
    h_secVtx_x                .push_back( book( name, "secVtx_x",                "secondary vertex x-pos [mm]",                     100,  -500,  500 ) );
    h_secVtx_y                .push_back( book( name, "secVtx_y",                "secondary vertex y-pos [mm]",                     100,  -500,  500 ) );
    h_secVtx_z                .push_back( book( name, "secVtx_z",                "secondary vertex z-pos [mm]",                     100, -1000, 1000 ) );
    h_secVtx_r                .push_back( book( name, "secVtx_r",                "secondary vertex r-pos [mm]",                     100,     0,  300 ) );
    h_secVtx_r_l              .push_back( book( name, "secVtx_r_l",              "secondary vertex r-pos [mm]",                     100,     0,  500 ) );
    h_secVtx_r_s              .push_back( book( name, "secVtx_r_s",              "secondary vertex r-pos [mm]",                     100,     0,  100 ) );
    h_secVtx_pt               .push_back( book( name, "secVtx_pt",               "secondary vertex p_{T} [GeV]",                    100,     0,  100 ) );
    h_secVtx_eta              .push_back( book( name, "secVtx_eta",              "secondary vertex eta",                            100,    -5,    5 ) );
    h_secVtx_phi              .push_back( book( name, "secVtx_phi",              "secondary vertex phi",                            100,  -3.5,  3.5 ) );
    h_secVtx_mass             .push_back( book( name, "secVtx_mass",             "secondary vertex mass [GeV]",                     100,     0,   50 ) );
    h_secVtx_mass_l           .push_back( book( name, "secVtx_mass_l",           "secondary vertex mass [GeV]",                     100,     0,  100 ) );
    h_secVtx_mass_s           .push_back( book( name, "secVtx_mass_s",           "secondary vertex mass [GeV]",                     100,     0,   25 ) );
    h_secVtx_mass_nonAssoc    .push_back( book( name, "secVtx_mass_nonAssoc",    "secondary vertex mass (excl. assoc. trks) [GeV]", 100,     0,   50 ) );
    h_secVtx_mass_nonAssoc_l  .push_back( book( name, "secVtx_mass_nonAssoc_l",  "secondary vertex mass (excl. assoc. trks) [GeV]", 100,     0,  100 ) );
    h_secVtx_mass_nonAssoc_s  .push_back( book( name, "secVtx_mass_nonAssoc_s",  "secondary vertex mass (excl. assoc. trks) [GeV]", 100,     0,   25 ) );
    h_secVtx_chi2             .push_back( book( name, "secVtx_chi2",             "secondary vertex chi2 / DoF",                     100,     0,   20 ) );
    h_secVtx_direction        .push_back( book( name, "secVtx_direction",        "secondary vertex direction",                      100,  -1.1,  1.1 ) );
    h_secVtx_charge           .push_back( book( name, "secVtx_charge",           "secondary vertex charge",                          11,    -5,    5 ) );
    h_secVtx_Ht               .push_back( book( name, "secVtx_Ht",               "secondary vertex scalar sum-p_{T} [GeV]",         100,     0,  100 ) );
    h_secVtx_minOpAng         .push_back( book( name, "secVtx_minOpAng",         "secondary vertex minimum opening angle",          100,  -1.1,  1.1 ) );
    h_secVtx_maxOpAng         .push_back( book( name, "secVtx_maxOpAng",         "secondary vertex maximum opening angle",          100,  -1.1,  1.1 ) );
    h_secVtx_mind0            .push_back( book( name, "secVtx_mind0",            "secondary vertex minimum track d0",               100,     0,  250 ) );
    h_secVtx_maxd0            .push_back( book( name, "secVtx_maxd0",            "secondary vertex maximum track d0",               100,     0,  250 ) );
    h_secVtx_minOneTrkRmvMass .push_back( book( name, "secVtx_minOneTrkRmvMass", "secondary vertex minimum n-1 track mass [GeV]",   100,     0,   15 ) );
    h_secVtx_twoTrkMass       .push_back( book( name, "secVtx_twoTrkMass",       "secondary vertex arbitrary 2-track mass [GeV]",   100,     0,   50 ) );
    h_secVtx_twoTrkMassRest   .push_back( book( name, "secVtx_twoTrkMassRest",   "secondary vertex arbitrary n-2 track mass [GeV]", 100,     0,   50 ) );
    h_secVtx_twoTrkCharge     .push_back( book( name, "secVtx_twoTrkCharge",     "secondary vertex arbitrary 2-track charge",         7,    -3,    3 ) );
    h_secVtx_ntrk             .push_back( book( name, "secVtx_ntrk",             "secondary vertex n tracks",                        10,     2,   12 ) );
    h_secVtx_ntrk_sel         .push_back( book( name, "secVtx_ntrk_sel",         "secondary vertex n selected tracks",               10,     0,   10 ) );
    h_secVtx_ntrk_assoc       .push_back( book( name, "secVtx_ntrk_assoc",       "secondary vertex n associated tracks",             10,     0,   10 ) );

    // secondary vertex parameters vs n tracks
    if ( m_numVtxTrk ) {
      h_secVtx_r_vs_ntrk                 .push_back( book( name, "secVtx_r_vs_ntrk",                  "n secondary vertex tracks",           10, 2,  12,
							   "secondary vertex r-pos [mm]",                                                   100, 0, 500 ) );
      h_secVtx_pt_vs_ntrk                .push_back( book( name, "secVtx_pt_vs_ntrk",                 "n secondary vertex tracks",           10, 2,  12,
							   "secondary vertex p_{T} [GeV]",                                                  100, 0, 100 ) );
      h_secVtx_mass_vs_ntrk              .push_back( book( name, "secVtx_mass_vs_ntrk",               "n secondary vertex tracks",           10, 2,  12,
							   "secondary vertex mass [GeV]",                                                   100, 0,  50 ) );
      h_secVtx_massNonAssoc_vs_ntrk      .push_back( book( name, "secVtx_massNonAssoc_vs_ntrk",       "n secondary vertex tracks",           10, 2,  12,
							   "secondary vertex mass (excl. assoc. trks) [GeV]",                               100, 0,  50 ) );
      h_secVtx_r_vs_ntrkSel              .push_back( book( name, "secVtx_r_vs_ntrkSel",              "n secondary vertex selected tracks",   10, 0,  10,
							   "secondary vertex r-pos [mm]",                                                   100, 0, 500 ) );
      h_secVtx_pt_vs_ntrkSel             .push_back( book( name, "secVtx_pt_vs_ntrkSel",             "n secondary vertex selected tracks",   10, 0,  10,
							   "secondary vertex p_{T} [GeV]",                                                  100, 0, 100 ) );
      h_secVtx_mass_vs_ntrkSel           .push_back( book( name, "secVtx_mass_vs_ntrkSel",           "n secondary vertex selected tracks",   10, 0,  10,
							   "secondary vertex mass [GeV]",                                                   100, 0,  50 ) );
      h_secVtx_massNonAssoc_vs_ntrkSel   .push_back( book( name, "secVtx_massNonAssoc_vs_ntrkSel",   "n secondary vertex selected tracks",   10, 0,  10,
							   "secondary vertex mass (excl. assoc. trks) [GeV]",                               100, 0,  50 ) );
      h_secVtx_r_vs_ntrkAssoc            .push_back( book( name, "secVtx_r_vs_ntrkAssoc",            "n secondary vertex associated tracks", 10, 0,  10,
							   "secondary vertex r-pos [mm]",                                                   100, 0, 500 ) );
      h_secVtx_pt_vs_ntrkAssoc           .push_back( book( name, "secVtx_pt_vs_ntrkAssoc",           "n secondary vertex associated tracks", 10, 0,  10,
							   "secondary vertex p_{T} [GeV]",                                                  100, 0, 100 ) );
      h_secVtx_mass_vs_ntrkAssoc         .push_back( book( name, "secVtx_mass_vs_ntrkAssoc",         "n secondary vertex associated tracks", 10, 0,  10,
							   "secondary vertex mass [GeV]",                                                   100, 0,  50 ) );
      h_secVtx_massNonAssoc_vs_ntrkAssoc .push_back( book( name, "secVtx_massNonAssoc_vs_ntrkAssoc", "n secondary vertex associated tracks", 10, 0,  10,
							   "secondary vertex mass (excl. assoc. trks) [GeV]",                               100, 0,  50 ) );

      std::vector<TH1F*> h_ntrk_n;
      std::vector<TH1F*> h_ntrk_x;
      std::vector<TH1F*> h_ntrk_y;
      std::vector<TH1F*> h_ntrk_z;
      std::vector<TH1F*> h_ntrk_r;
      std::vector<TH1F*> h_ntrk_r_l;
      std::vector<TH1F*> h_ntrk_r_s;
      std::vector<TH1F*> h_ntrk_pt;
      std::vector<TH1F*> h_ntrk_eta;
      std::vector<TH1F*> h_ntrk_phi;
      std::vector<TH1F*> h_ntrk_mass;
      std::vector<TH1F*> h_ntrk_mass_l;
      std::vector<TH1F*> h_ntrk_mass_s;
      std::vector<TH1F*> h_ntrk_massNon;
      std::vector<TH1F*> h_ntrk_massNon_l;
      std::vector<TH1F*> h_ntrk_massNon_s;
      std::vector<TH1F*> h_ntrk_chi2;
      std::vector<TH1F*> h_ntrk_direction;
      std::vector<TH1F*> h_ntrk_charge;
      std::vector<TH1F*> h_ntrk_Ht;
      std::vector<TH1F*> h_ntrk_minOpAng;
      std::vector<TH1F*> h_ntrk_maxOpAng;
      std::vector<TH1F*> h_ntrk_mind0;
      std::vector<TH1F*> h_ntrk_maxd0;
      std::vector<TH1F*> h_ntrk_ntrkSel;
      std::vector<TH1F*> h_ntrk_ntrkAssoc;
      for ( int i = 1; i != m_numVtxTrk; ++i ) {
	std::string ntrk = std::to_string(i+1);
	h_ntrk_n         .push_back( book( name, ( "secVtx" + ntrk + "trk_n"               ),
					   ( "n " + ntrk + "-track secondary vertices"                       ),  20,     0,   20 ) );
	h_ntrk_x         .push_back( book( name, ( "secVtx" + ntrk + "trk_x"               ),
					   ( ntrk + "-track secondary vertex x-pos [mm]"                     ), 100,  -500,  500 ) );
	h_ntrk_y         .push_back( book( name, ( "secVtx" + ntrk + "trk_y"               ),
					   ( ntrk + "-track secondary vertex y-pos [mm]"                     ), 100,  -500,  500 ) );
	h_ntrk_z         .push_back( book( name, ( "secVtx" + ntrk + "trk_z"               ),
					   ( ntrk + "-track secondary vertex z-pos [mm]"                     ), 100, -1000, 1000 ) );
	h_ntrk_r         .push_back( book( name, ( "secVtx" + ntrk + "trk_r"               ),
					   ( ntrk + "-track secondary vertex r-pos [mm]"                     ), 100,     0,  300 ) );
	h_ntrk_r_l       .push_back( book( name, ( "secVtx" + ntrk + "trk_r_l"             ),
					   ( ntrk + "-track secondary vertex r-pos [mm]"                     ), 100,     0,  500 ) );
	h_ntrk_r_s       .push_back( book( name, ( "secVtx" + ntrk + "trk_r_s"             ),
					   ( ntrk + "-track secondary vertex r-pos [mm]"                     ), 100,     0,  100 ) );
	h_ntrk_pt        .push_back( book( name, ( "secVtx" + ntrk + "trk_pt"              ),
					   ( ntrk + "-track secondary vertex p_{T} [GeV]"                    ), 100,     0,  100 ) );
	h_ntrk_eta       .push_back( book( name, ( "secVtx" + ntrk + "trk_eta"             ),
					   ( ntrk + "-track secondary vertex eta"                            ), 100,    -5,    5 ) );
	h_ntrk_phi       .push_back( book( name, ( "secVtx" + ntrk + "trk_phi"             ),
					   ( ntrk + "-track secondary vertex phi"                            ), 100,  -3.5,  3.5 ) );
	h_ntrk_mass      .push_back( book( name, ( "secVtx" + ntrk + "trk_mass"            ),
					   ( ntrk + "-track secondary vertex mass [GeV]"                     ), 100,     0,   50 ) );
	h_ntrk_mass_l    .push_back( book( name, ( "secVtx" + ntrk + "trk_mass_l"          ),
					   ( ntrk + "-track secondary vertex mass [GeV]"                     ), 100,     0,  100 ) );
	h_ntrk_mass_s    .push_back( book( name, ( "secVtx" + ntrk + "trk_mass_s"          ),
					   ( ntrk + "-track secondary vertex mass [GeV]"                     ), 100,     0,   25 ) );
	h_ntrk_massNon   .push_back( book( name, ( "secVtx" + ntrk + "trk_mass_nonAssoc"   ),
					   ( ntrk + "-track secondary vertex mass (excl. assoc. trks) [GeV]" ), 100,     0,   50 ) );
	h_ntrk_massNon_l .push_back( book( name, ( "secVtx" + ntrk + "trk_mass_nonAssoc_l" ),
					   ( ntrk + "-track secondary vertex mass (excl. assoc. trks) [GeV]" ), 100,     0,  100 ) );
	h_ntrk_massNon_s .push_back( book( name, ( "secVtx" + ntrk + "trk_mass_nonAssoc_s" ),
					   ( ntrk + "-track secondary vertex mass (excl. assoc. trks) [GeV]" ), 100,     0,   25 ) );
	h_ntrk_chi2      .push_back( book( name, ( "secVtx" + ntrk + "trk_chi2"            ),
					   ( ntrk + "-track secondary vertex chi2 / DoF"                     ), 100,     0,   20 ) );
	h_ntrk_direction .push_back( book( name, ( "secVtx" + ntrk + "trk_direction"       ),
					   ( ntrk + "-track secondary vertex direction"                      ), 100,  -1.1,  1.1 ) );
	h_ntrk_charge    .push_back( book( name, ( "secVtx" + ntrk + "trk_charge"          ),
					   ( ntrk + "-track secondary vertex charge"                         ), 100,    -5,    5 ) );
	h_ntrk_Ht        .push_back( book( name, ( "secVtx" + ntrk + "trk_Ht"              ),
					   ( ntrk + "-track secondary vertex scalar sum-p_{T} [GeV]"         ), 100,     0,  100 ) );
	h_ntrk_minOpAng  .push_back( book( name, ( "secVtx" + ntrk + "trk_minOpAng"        ),
					   ( ntrk + "-track secondary vertex minimum opening angle"          ), 100,  -1.1,  1.1 ) );
	h_ntrk_maxOpAng  .push_back( book( name, ( "secVtx" + ntrk + "trk_maxOpAng"        ),
					   ( ntrk + "-track secondary vertex maximum opening angle"          ), 100,  -1.1,  1.1 ) );
	h_ntrk_mind0     .push_back( book( name, ( "secVtx" + ntrk + "trk_mind0"           ),
					   ( ntrk + "-track secondary vertex minimum track d0"               ), 100,     0,  250 ) );
	h_ntrk_maxd0     .push_back( book( name, ( "secVtx" + ntrk + "trk_maxd0"           ),
					   ( ntrk + "-track secondary vertex maximum track d0"               ), 100,     0,  250 ) );
	h_ntrk_ntrkSel   .push_back( book( name, ( "secVtx" + ntrk + "trk_ntrk_sel"        ),
					   ( ntrk + "-track secondary vertex n selected tracks"              ),  10,     0,   10 ) );
	h_ntrk_ntrkAssoc .push_back( book( name, ( "secVtx" + ntrk + "trk_ntrk_assoc"      ),
					   ( ntrk + "-track secondary vertex n associated tracks"            ),  10,     0,   10 ) );
      }
      h_secVtxNtrk_n               .push_back( h_ntrk_n         );
      h_secVtxNtrk_x               .push_back( h_ntrk_x         );
      h_secVtxNtrk_y               .push_back( h_ntrk_y         );
      h_secVtxNtrk_z               .push_back( h_ntrk_z         );
      h_secVtxNtrk_r               .push_back( h_ntrk_r         );
      h_secVtxNtrk_r_l             .push_back( h_ntrk_r_l       );
      h_secVtxNtrk_r_s             .push_back( h_ntrk_r_s       );
      h_secVtxNtrk_pt              .push_back( h_ntrk_pt        );
      h_secVtxNtrk_eta             .push_back( h_ntrk_eta       );
      h_secVtxNtrk_phi             .push_back( h_ntrk_phi       );
      h_secVtxNtrk_mass            .push_back( h_ntrk_mass      );
      h_secVtxNtrk_mass_l          .push_back( h_ntrk_mass_l    );
      h_secVtxNtrk_mass_s          .push_back( h_ntrk_mass_s    );
      h_secVtxNtrk_mass_nonAssoc   .push_back( h_ntrk_massNon   );
      h_secVtxNtrk_mass_nonAssoc_l .push_back( h_ntrk_massNon_l );
      h_secVtxNtrk_mass_nonAssoc_s .push_back( h_ntrk_massNon_s );
      h_secVtxNtrk_chi2            .push_back( h_ntrk_chi2      );
      h_secVtxNtrk_direction       .push_back( h_ntrk_direction );
      h_secVtxNtrk_charge          .push_back( h_ntrk_charge    );
      h_secVtxNtrk_Ht              .push_back( h_ntrk_Ht        );
      h_secVtxNtrk_minOpAng        .push_back( h_ntrk_minOpAng  );
      h_secVtxNtrk_maxOpAng        .push_back( h_ntrk_maxOpAng  );
      h_secVtxNtrk_mind0           .push_back( h_ntrk_mind0     );
      h_secVtxNtrk_maxd0           .push_back( h_ntrk_maxd0     );
      h_secVtxNtrk_ntrk_sel        .push_back( h_ntrk_ntrkSel   );
      h_secVtxNtrk_ntrk_assoc      .push_back( h_ntrk_ntrkAssoc );
    }

    // secondary vertices vs mu
    if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_vtx ) {
      h_secVtx_n_vs_avgMu          .push_back( book( name, "secVtx_n_vs_avgMu",          "< #mu >", 100,    0, 100,
						     "n secondary vertices",                         20,    0,  20 ) );
      h_secVtx_r_vs_avgMu          .push_back( book( name, "secVtx_r_vs_avgMu",          "< #mu >", 100,    0, 100,
						     "secondary vertex r-pos [mm]",                 100,    0, 300 ) );
      h_secVtx_pt_vs_avgMu         .push_back( book( name, "secVtx_pt_vs_avgMu",         "< #mu >", 100,    0, 100,
						     "secondary vertex p_{T} [GeV]",                100,    0, 100 ) );
      h_secVtx_eta_vs_avgMu        .push_back( book( name, "secVtx_eta_vs_avgMu",        "< #mu >", 100,    0, 100,
						     "secondary vertex eta",                        100,   -5,   5 ) );
      h_secVtx_phi_vs_avgMu        .push_back( book( name, "secVtx_phi_vs_avgMu",        "< #mu >", 100,    0, 100,
						     "secondary vertex phi",                        100, -3.5, 3.5 ) );
      h_secVtx_mass_vs_avgMu       .push_back( book( name, "secVtx_mass_vs_avgMu",       "< #mu >", 100,    0, 100,
						     "secondary vertex mass [GeV]",                 100,    0,  50 ) );
      h_secVtx_ntrk_vs_avgMu       .push_back( book( name, "secVtx_ntrk_vs_avgMu",       "< #mu >", 100,    0, 100,
						     "secondary vertex n tracks",                    10,    2,  12 ) );
      h_secVtx_ntrk_sel_vs_avgMu   .push_back( book( name, "secVtx_ntrk_sel_vs_avgMu",   "< #mu >", 100,    0, 100,
						     "secondary vertex n selected tracks",           10,    0,  10 ) );
      h_secVtx_ntrk_assoc_vs_avgMu .push_back( book( name, "secVtx_ntrk_assoc_vs_avgMu", "< #mu >", 100,    0, 100,
						     "secondary vertex n associated tracks",         10,    0,  10 ) );
      h_secVtx_n_vs_actMu          .push_back( book( name, "secVtx_n_vs_actMu",            "#mu",   100,    0, 100,
						     "n secondary vertices",                         20,    0,  20 ) );
      h_secVtx_r_vs_actMu          .push_back( book( name, "secVtx_r_vs_actMu",            "#mu",   100,    0, 100,
						     "secondary vertex r-pos [mm]",                 100,    0, 300 ) );
      h_secVtx_pt_vs_actMu         .push_back( book( name, "secVtx_pt_vs_actMu",           "#mu",   100,    0, 100,
						     "secondary vertex p_{T} [GeV]",                100,    0, 100 ) );
      h_secVtx_eta_vs_actMu        .push_back( book( name, "secVtx_eta_vs_actMu",          "#mu",   100,    0, 100,
						     "secondary vertex eta",                        100,   -5,   5 ) );
      h_secVtx_phi_vs_actMu        .push_back( book( name, "secVtx_phi_vs_actMu",          "#mu",   100,    0, 100,
						     "secondary vertex phi",                        100, -3.5, 3.5 ) );
      h_secVtx_mass_vs_actMu       .push_back( book( name, "secVtx_mass_vs_actMu",         "#mu",   100,    0, 100,
						     "secondary vertex mass [GeV]",                 100,    0,  50 ) );
      h_secVtx_ntrk_vs_actMu       .push_back( book( name, "secVtx_ntrk_vs_actMu",         "#mu",   100,    0, 100,
						     "secondary vertex n tracks",                    10,    2,  12 ) );
      h_secVtx_ntrk_sel_vs_actMu   .push_back( book( name, "secVtx_ntrk_sel_vs_actMu",     "#mu",   100,    0, 100,
						     "secondary vertex n selected tracks",           10,    0,  10 ) );
      h_secVtx_ntrk_assoc_vs_actMu .push_back( book( name, "secVtx_ntrk_assoc_vs_actMu",   "#mu",   100,    0, 100,
						     "secondary vertex n associated tracks",         10,    0,  10 ) );

      // ntrk secondary vertices vs mu
      if ( m_numVtxTrk ) {
	std::vector<TH2F*> h_ntrk_n_vs_avgMu;
	std::vector<TH2F*> h_ntrk_r_vs_avgMu;
	std::vector<TH2F*> h_ntrk_pt_vs_avgMu;
	std::vector<TH2F*> h_ntrk_eta_vs_avgMu;
	std::vector<TH2F*> h_ntrk_phi_vs_avgMu;
	std::vector<TH2F*> h_ntrk_mass_vs_avgMu;
	std::vector<TH2F*> h_ntrk_ntrkSel_vs_avgMu;
	std::vector<TH2F*> h_ntrk_ntrkAssoc_vs_avgMu;
	std::vector<TH2F*> h_ntrk_n_vs_actMu;
	std::vector<TH2F*> h_ntrk_r_vs_actMu;
	std::vector<TH2F*> h_ntrk_pt_vs_actMu;
	std::vector<TH2F*> h_ntrk_eta_vs_actMu;
	std::vector<TH2F*> h_ntrk_phi_vs_actMu;
	std::vector<TH2F*> h_ntrk_mass_vs_actMu;
	std::vector<TH2F*> h_ntrk_ntrkSel_vs_actMu;
	std::vector<TH2F*> h_ntrk_ntrkAssoc_vs_actMu;
	for ( int i = 1; i != m_numVtxTrk; ++i ) {
	  std::string ntrk = std::to_string(i+1);
	  h_ntrk_n_vs_avgMu         .push_back( book( name, ( "secVtx" + ntrk + "trk_n_vs_avgMu"             ), "< #mu >", 100,    0, 100,
						      ( "n " + ntrk + "-track secondary vertices"            ),             20,    0,  20 ) );
	  h_ntrk_r_vs_avgMu         .push_back( book( name, ( "secVtx" + ntrk + "trk_r_vs_avgMu"             ), "< #mu >", 100,    0, 100,
						      ( ntrk + "-track secondary vertex r-pos [mm]"          ),            100,    0, 300 ) );
	  h_ntrk_pt_vs_avgMu        .push_back( book( name, ( "secVtx" + ntrk + "trk_pt_vs_avgMu"            ), "< #mu >", 100,    0, 100,
						      ( ntrk + "-track secondary vertex p_{T} [GeV]"         ),            100,    0, 100 ) );
	  h_ntrk_eta_vs_avgMu       .push_back( book( name, ( "secVtx" + ntrk + "trk_eta_vs_avgMu"           ), "< #mu >", 100,    0, 100,
						      ( ntrk + "-track secondary vertex eta"                 ),            100,   -5,   5 ) );
	  h_ntrk_phi_vs_avgMu       .push_back( book( name, ( "secVtx" + ntrk + "trk_phi_vs_avgMu"           ), "< #mu >", 100,    0, 100,
						      ( ntrk + "-track secondary vertex phi"                 ),            100, -3.5, 3.5 ) );
	  h_ntrk_mass_vs_avgMu      .push_back( book( name, ( "secVtx" + ntrk + "trk_mass_vs_avgMu"          ), "< #mu >", 100,    0, 100,
						      ( ntrk + "-track secondary vertex mass [GeV]"          ),            100,    0,  50 ) );
	  h_ntrk_ntrkSel_vs_avgMu   .push_back( book( name, ( "secVtx" + ntrk + "trk_ntrk_sel_vs_avgMu"      ), "< #mu >", 100,    0, 100,
						      ( ntrk + "-track secondary vertex n selected tracks"   ),             10,    0,  10 ) );
	  h_ntrk_ntrkAssoc_vs_avgMu .push_back( book( name, ( "secVtx" + ntrk + "trk_ntrk_assoc_vs_avgMu"    ), "< #mu >", 100,    0, 100,
						      ( ntrk + "-track secondary vertex n associated tracks" ),             10,    0,  10 ) );
	  h_ntrk_n_vs_actMu         .push_back( book( name, ( "secVtx" + ntrk + "trk_n_vs_actMu"             ),   "#mu",   100,    0, 100,
						      ( "n " + ntrk + "-track secondary vertices"            ),             20,    0,  20 ) );
	  h_ntrk_r_vs_actMu         .push_back( book( name, ( "secVtx" + ntrk + "trk_r_vs_actMu"             ),   "#mu",   100,    0, 100,
						      ( ntrk + "-track secondary vertex r-pos [mm]"          ),            100,    0, 300 ) );
	  h_ntrk_pt_vs_actMu        .push_back( book( name, ( "secVtx" + ntrk + "trk_pt_vs_actMu"            ),   "#mu",   100,    0, 100,
						      ( ntrk + "-track secondary vertex p_{T} [GeV]"         ),            100,    0, 100 ) );
	  h_ntrk_eta_vs_actMu       .push_back( book( name, ( "secVtx" + ntrk + "trk_eta_vs_actMu"           ),   "#mu",   100,    0, 100,
						      ( ntrk + "-track secondary vertex eta"                 ),            100,   -5,   5 ) );
	  h_ntrk_phi_vs_actMu       .push_back( book( name, ( "secVtx" + ntrk + "trk_phi_vs_actMu"           ),   "#mu",   100,    0, 100,
						      ( ntrk + "-track secondary vertex phi"                 ),            100, -3.5, 3.5 ) );
	  h_ntrk_mass_vs_actMu      .push_back( book( name, ( "secVtx" + ntrk + "trk_mass_vs_actMu"          ),   "#mu",   100,    0, 100,
						      ( ntrk + "-track secondary vertex mass [GeV]"          ),            100,    0,  50 ) );
	  h_ntrk_ntrkSel_vs_actMu   .push_back( book( name, ( "secVtx" + ntrk + "trk_ntrk_sel_vs_actMu"      ),   "#mu",   100,    0, 100,
						      ( ntrk + "-track secondary vertex n selected tracks"   ),             10,    0,  10 ) );
	  h_ntrk_ntrkAssoc_vs_actMu .push_back( book( name, ( "secVtx" + ntrk + "trk_ntrk_assoc_vs_actMu"    ),   "#mu",   100,    0, 100,
						      ( ntrk + "-track secondary vertex n associated tracks" ),             10,    0,  10 ) );
	}
	h_secVtxNtrk_n_vs_avgMu          .push_back( h_ntrk_n_vs_avgMu );
	h_secVtxNtrk_r_vs_avgMu          .push_back( h_ntrk_r_vs_avgMu );
	h_secVtxNtrk_pt_vs_avgMu         .push_back( h_ntrk_pt_vs_avgMu );
	h_secVtxNtrk_eta_vs_avgMu        .push_back( h_ntrk_eta_vs_avgMu );
	h_secVtxNtrk_phi_vs_avgMu        .push_back( h_ntrk_phi_vs_avgMu );
	h_secVtxNtrk_mass_vs_avgMu       .push_back( h_ntrk_mass_vs_avgMu );
	h_secVtxNtrk_ntrk_sel_vs_avgMu   .push_back( h_ntrk_ntrkSel_vs_avgMu );
	h_secVtxNtrk_ntrk_assoc_vs_avgMu .push_back( h_ntrk_ntrkAssoc_vs_avgMu );
	h_secVtxNtrk_n_vs_actMu          .push_back( h_ntrk_n_vs_actMu );
	h_secVtxNtrk_r_vs_actMu          .push_back( h_ntrk_r_vs_actMu );
	h_secVtxNtrk_pt_vs_actMu         .push_back( h_ntrk_pt_vs_actMu );
	h_secVtxNtrk_eta_vs_actMu        .push_back( h_ntrk_eta_vs_actMu );
	h_secVtxNtrk_phi_vs_actMu        .push_back( h_ntrk_phi_vs_actMu );
	h_secVtxNtrk_mass_vs_actMu       .push_back( h_ntrk_mass_vs_actMu );
	h_secVtxNtrk_ntrk_sel_vs_actMu   .push_back( h_ntrk_ntrkSel_vs_actMu );
	h_secVtxNtrk_ntrk_assoc_vs_actMu .push_back( h_ntrk_ntrkAssoc_vs_actMu );
      }
    }

    
  } // end loop over regions

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: execute ( TTree* tree, Long64_t treeEntry, const std::vector<EJsHelper::Region>& regions, bool mc )
{
  if ( m_debug ) Info( "EJsHistogramManager::execute()", "filling histograms" );

  // fill histograms -- use info switches

  tree->GetEntry( treeEntry );

  // loop over regions ...
  for ( size_t ireg = 0; ireg != regions.size(); ++ireg ) {
    const EJsHelper::Region region = regions.at(ireg);

    if      ( region.type == EJsHelper::SIGNAL     ) { if ( !m_signal ) continue; }
    else if ( region.type == EJsHelper::VALIDATION ) { if ( !m_valid  ) continue; }
    else if ( region.type == EJsHelper::CONTROL    ) { if ( !m_ctrl   ) continue; }
 
    // ------------------ //
    // --- EVENT INFO --- //
    // ------------------ //
    
    // event info
    h_npv       .at(ireg) ->Fill( m_npv       );
    h_actualMu  .at(ireg) ->Fill( m_actualMu  );
    h_averageMu .at(ireg) ->Fill( m_averageMu );
    h_njetHt    .at(ireg) ->Fill( m_njetHt    );
    
    
    // PV info
    h_pv_x    .at(ireg)->Fill( m_pv_x    );
    h_pv_y    .at(ireg)->Fill( m_pv_y    );
    h_pv_z    .at(ireg)->Fill( m_pv_z    );
    h_pv_r    .at(ireg)->Fill( m_pv_r    );
    h_pv_phi  .at(ireg)->Fill( m_pv_phi  );
    h_pv_nTrk .at(ireg)->Fill( m_pv_nTrk );


    
    // ------------ //
    // --- JETS --- //
    // ------------ //
  
    // RECO JETS
    h_jet_n .at(ireg)->Fill( m_jet_n );  
    if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_jet ) {
      h_jet_n_vs_avgMu .at(ireg)->Fill( m_averageMu, m_jet_n );
      h_jet_n_vs_actMu .at(ireg)->Fill( m_actualMu,  m_jet_n );
    }
      
    for ( int i = 0; i != m_jet_n; ++i ) {
      
      TLorentzVector jet_p4;
      jet_p4.SetPtEtaPhiM( m_jet_pt->at(i), m_jet_eta->at(i), m_jet_phi->at(i), m_jet_M->at(i) );
      
      // basics
      h_jet_pt     .at(ireg)->Fill( m_jet_pt    ->at(i) );
      h_jet_pt_l   .at(ireg)->Fill( m_jet_pt    ->at(i) );
      h_jet_pt_m   .at(ireg)->Fill( m_jet_pt    ->at(i) );
      h_jet_pt_s   .at(ireg)->Fill( m_jet_pt    ->at(i) );
      h_jet_eta    .at(ireg)->Fill( m_jet_eta   ->at(i) );
      h_jet_phi    .at(ireg)->Fill( m_jet_phi   ->at(i) );
      h_jet_E      .at(ireg)->Fill( m_jet_E     ->at(i) );
      h_jet_M      .at(ireg)->Fill( m_jet_M     ->at(i) );
      h_jet_rapid  .at(ireg)->Fill( m_jet_rapid ->at(i) );
      // kinematics
      if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
	h_jet_px   .at(ireg)->Fill( jet_p4.Px() );
	h_jet_py   .at(ireg)->Fill( jet_p4.Py() );
	h_jet_pz   .at(ireg)->Fill( jet_p4.Pz() );
	h_jet_Et   .at(ireg)->Fill( jet_p4.Et() );
	h_jet_Et_l .at(ireg)->Fill( jet_p4.Et() );
	h_jet_Et_m .at(ireg)->Fill( jet_p4.Et() );
	h_jet_Et_s .at(ireg)->Fill( jet_p4.Et() );
      }
      // leading
      if ( m_numLead ) {
	if ( i < m_numLead ) {
	  h_jetN_pt     .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i) );
	  h_jetN_pt_l   .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i) );
	  h_jetN_pt_m   .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i) );
	  h_jetN_pt_s   .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i) );
	  h_jetN_eta    .at(ireg).at(i) ->Fill( m_jet_eta   ->at(i) );
	  h_jetN_phi    .at(ireg).at(i) ->Fill( m_jet_phi   ->at(i) );
	  h_jetN_E      .at(ireg).at(i) ->Fill( m_jet_E     ->at(i) );
	  h_jetN_M      .at(ireg).at(i) ->Fill( m_jet_M     ->at(i) );
	  h_jetN_rapid  .at(ireg).at(i) ->Fill( m_jet_rapid ->at(i) );
	  if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
	    h_jetN_Et   .at(ireg).at(i) ->Fill( jet_p4.Et() );
	    h_jetN_Et_l .at(ireg).at(i) ->Fill( jet_p4.Et() );
	    h_jetN_Et_m .at(ireg).at(i) ->Fill( jet_p4.Et() );
	    h_jetN_Et_s .at(ireg).at(i) ->Fill( jet_p4.Et() );
	  }
	}
      }

      // energy, width, constituents
      if ( m_histoInfoSwitch ->m_jetEConstit ) {
	h_jet_hecFrac    .at(ireg)->Fill( m_jet_hecFrac      ->at(i) );
	h_jet_emFrac     .at(ireg)->Fill( m_jet_emFrac       ->at(i) );
	h_jet_centroidR  .at(ireg)->Fill( m_jet_centroidR    ->at(i) );
	h_jet_width      .at(ireg)->Fill( m_jet_width        ->at(i) );
	h_jet_numConstit .at(ireg)->Fill( m_jet_numConstit   ->at(i) );
      }
      
      // track moments (PV)
      if ( m_histoInfoSwitch ->m_jetTrkMom ) {
	h_jet_numTrkPt10     .at(ireg)->Fill( m_jet_numTrkPt10   ->at(i).at(m_pv_location) );
	h_jet_sumPtTrkPt10   .at(ireg)->Fill( m_jet_sumPtTrkPt10 ->at(i).at(m_pv_location) );
	h_jet_sumPtTrkPt10_l .at(ireg)->Fill( m_jet_sumPtTrkPt10 ->at(i).at(m_pv_location) );
	h_jet_sumPtTrkPt10_m .at(ireg)->Fill( m_jet_sumPtTrkPt10 ->at(i).at(m_pv_location) );
	h_jet_sumPtTrkPt10_s .at(ireg)->Fill( m_jet_sumPtTrkPt10 ->at(i).at(m_pv_location) );
	h_jet_trkWidthPt10   .at(ireg)->Fill( m_jet_trkWidthPt10 ->at(i).at(m_pv_location) );
	h_jet_numTrkPt5      .at(ireg)->Fill( m_jet_numTrkPt5    ->at(i).at(m_pv_location) );
	h_jet_sumPtTrkPt5    .at(ireg)->Fill( m_jet_sumPtTrkPt5  ->at(i).at(m_pv_location) );
	h_jet_sumPtTrkPt5_l  .at(ireg)->Fill( m_jet_sumPtTrkPt5  ->at(i).at(m_pv_location) );
	h_jet_sumPtTrkPt5_m  .at(ireg)->Fill( m_jet_sumPtTrkPt5  ->at(i).at(m_pv_location) );
	h_jet_sumPtTrkPt5_s  .at(ireg)->Fill( m_jet_sumPtTrkPt5  ->at(i).at(m_pv_location) );
	h_jet_trkWidthPt5    .at(ireg)->Fill( m_jet_trkWidthPt5  ->at(i).at(m_pv_location) );
      }
      
      // ghost-associated tracks / truth particles
      if ( m_histoInfoSwitch ->m_jetGhost ) {
	// ghost tracks
	h_jet_GhostTrackCount   .at(ireg)->Fill( m_jet_GhostTrackCount ->at(i) );
	h_jet_GhostTrackPt      .at(ireg)->Fill( m_jet_GhostTrackPt    ->at(i) );
	h_jet_GhostTrackPt_l    .at(ireg)->Fill( m_jet_GhostTrackPt    ->at(i) );
	h_jet_GhostTrackPt_m    .at(ireg)->Fill( m_jet_GhostTrackPt    ->at(i) );
	h_jet_GhostTrackPt_s    .at(ireg)->Fill( m_jet_GhostTrackPt    ->at(i) );
	// ghost truth particles
	if ( mc ) {
	  h_jet_GhostTruthCount .at(ireg)->Fill( m_jet_GhostTruthCount ->at(i) );
	  h_jet_GhostTruthPt    .at(ireg)->Fill( m_jet_GhostTruthPt    ->at(i) );
	  h_jet_GhostTruthPt_l  .at(ireg)->Fill( m_jet_GhostTruthPt    ->at(i) );
	  h_jet_GhostTruthPt_m  .at(ireg)->Fill( m_jet_GhostTruthPt    ->at(i) );
	  h_jet_GhostTruthPt_s  .at(ireg)->Fill( m_jet_GhostTruthPt    ->at(i) );
	}
      }
	
      // associated tracks / truth particles
      if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTrk ) {
	// dR-matched tracks
	h_jet_trkCount  .at(ireg)->Fill( m_jet_trkCount ->at(i) );
	h_jet_trkPt     .at(ireg)->Fill( m_jet_trkPt    ->at(i) );
	h_jet_trkPt_l   .at(ireg)->Fill( m_jet_trkPt    ->at(i) );
	h_jet_trkPt_m   .at(ireg)->Fill( m_jet_trkPt    ->at(i) );
	h_jet_trkPt_s   .at(ireg)->Fill( m_jet_trkPt    ->at(i) );
	for ( int j = 0; j != m_jet_trkCount->at(i); ++j )
	  h_jet_trk_dR  .at(ireg)->Fill( m_jet_trk_dR   ->at(i).at(j) );
	// dR-matched truth particles
	if ( mc ) {
	  h_jet_tpCount .at(ireg)->Fill( m_jet_tpCount  ->at(i) );
	  h_jet_tpPt    .at(ireg)->Fill( m_jet_tpPt     ->at(i) );
	  h_jet_tpPt_l  .at(ireg)->Fill( m_jet_tpPt     ->at(i) );
	  h_jet_tpPt_m  .at(ireg)->Fill( m_jet_tpPt     ->at(i) );
	  h_jet_tpPt_s  .at(ireg)->Fill( m_jet_tpPt     ->at(i) );
	  for ( int j = 0; j != m_jet_tpCount->at(i); ++j )
	    h_jet_tp_dR .at(ireg)->Fill( m_jet_tp_dR    ->at(i).at(j) );
	}
      }

      // associated vertices
      if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetVtx ) {
	// dR-matched secondary vertices
	h_jet_secVtxCount     .at(ireg)->Fill( m_jet_secVtxCount   ->at(i) );
	h_jet_secVtxPt        .at(ireg)->Fill( m_jet_secVtxPt      ->at(i) );
	for ( int j = 0; j != m_jet_secVtxCount->at(i); ++j )
	  h_jet_secVtx_dR     .at(ireg)->Fill( m_jet_secVtx_dR     ->at(i).at(j) );
	// dR-matched truth vertices
	if ( mc ) {
	  h_jet_truthVtxCount .at(ireg)->Fill( m_jet_truthVtxCount ->at(i) );
	  h_jet_truthVtxPt    .at(ireg)->Fill( m_jet_truthVtxPt    ->at(i) );
	  for ( int j = 0; j != m_jet_truthVtxCount->at(i); ++j )
	    h_jet_truthVtx_dR .at(ireg)->Fill( m_jet_truthVtx_dR   ->at(i).at(j) );
	}
      }

      // count truth / dark matched jets; fill dR

      // jets vs mu
      if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_jet ) {
	h_jet_pt_vs_avgMu .at(ireg)->Fill( m_averageMu, m_jet_pt ->at(i) );
	h_jet_pt_vs_actMu .at(ireg)->Fill( m_actualMu,  m_jet_pt ->at(i) );
	if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTrk ) {
	  h_jet_trkCount_vs_avgMu    .at(ireg)->Fill( m_averageMu, m_jet_trkCount ->at(i) );
	  h_jet_trkPt_vs_avgMu       .at(ireg)->Fill( m_averageMu, m_jet_trkPt    ->at(i) );
	  for ( int j = 0; j != m_jet_trkCount->at(i); ++j ) {
	    h_jet_trk_dR_vs_avgMu    .at(ireg)->Fill( m_averageMu, m_jet_trk_dR ->at(i).at(j) );
	    h_jet_trk_dR_vs_actMu    .at(ireg)->Fill( m_actualMu,  m_jet_trk_dR ->at(i).at(j) );
	  }
	  h_jet_trkCount_vs_actMu    .at(ireg)->Fill( m_actualMu, m_jet_trkCount ->at(i) );
	  h_jet_trkPt_vs_actMu       .at(ireg)->Fill( m_actualMu, m_jet_trkPt    ->at(i) );
	}
	if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetVtx ){
	  h_jet_secVtxCount_vs_avgMu .at(ireg)->Fill( m_averageMu, m_jet_secVtxCount ->at(i) );
	  h_jet_secVtxPt_vs_avgMu    .at(ireg)->Fill( m_averageMu, m_jet_secVtxPt    ->at(i) );
	  for ( int j = 0; j != m_jet_secVtxCount->at(i); ++j ) {
	    h_jet_secVtx_dR_vs_avgMu .at(ireg)->Fill( m_averageMu, m_jet_secVtx_dR ->at(i).at(j) );
	    h_jet_secVtx_dR_vs_actMu .at(ireg)->Fill( m_actualMu,  m_jet_secVtx_dR ->at(i).at(j) );
	  }
	  h_jet_secVtxCount_vs_actMu .at(ireg)->Fill( m_actualMu, m_jet_secVtxCount ->at(i) );
	  h_jet_secVtxPt_vs_actMu    .at(ireg)->Fill( m_actualMu, m_jet_secVtxPt    ->at(i) );
	}
      }
    }
    

    if ( mc ) {
      
      // TRUTH JETS
      h_truthJet_n .at(ireg)->Fill( m_truthJet_n );
      if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_jet ) {
	h_truthJet_n_vs_avgMu .at(ireg)->Fill( m_averageMu, m_truthJet_n  );
	h_truthJet_n_vs_actMu .at(ireg)->Fill( m_actualMu,  m_truthJet_n  );
      }
      
      for ( int i = 0; i != m_truthJet_n; ++i ) {

	TLorentzVector truthJet_p4;
	truthJet_p4.SetPtEtaPhiM( m_truthJet_pt->at(i), m_truthJet_eta->at(i), m_truthJet_phi->at(i), m_truthJet_M->at(i) );
	
	// basics
	h_truthJet_pt    .at(ireg)->Fill( m_truthJet_pt    ->at(i) );
	h_truthJet_pt_l  .at(ireg)->Fill( m_truthJet_pt    ->at(i) );
	h_truthJet_pt_m  .at(ireg)->Fill( m_truthJet_pt    ->at(i) );
	h_truthJet_pt_s  .at(ireg)->Fill( m_truthJet_pt    ->at(i) );
	h_truthJet_eta   .at(ireg)->Fill( m_truthJet_eta   ->at(i) );
	h_truthJet_phi   .at(ireg)->Fill( m_truthJet_phi   ->at(i) );
	h_truthJet_E     .at(ireg)->Fill( m_truthJet_E     ->at(i) );
	h_truthJet_M     .at(ireg)->Fill( m_truthJet_M     ->at(i) );
	h_truthJet_rapid .at(ireg)->Fill( m_truthJet_rapid ->at(i) );
	// kinematics
	if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
	  h_truthJet_px   .at(ireg)->Fill( truthJet_p4.Px() );
	  h_truthJet_py   .at(ireg)->Fill( truthJet_p4.Py() );
	  h_truthJet_pz   .at(ireg)->Fill( truthJet_p4.Pz() );
	  h_truthJet_Et   .at(ireg)->Fill( truthJet_p4.Et() );
	  h_truthJet_Et_l .at(ireg)->Fill( truthJet_p4.Et() );
	  h_truthJet_Et_m .at(ireg)->Fill( truthJet_p4.Et() );
	  h_truthJet_Et_s .at(ireg)->Fill( truthJet_p4.Et() );
	}
	// leading
	if ( m_numLead ) {
	  if ( i < m_numLead ) {
	    h_truthJetN_pt    .at(ireg).at(i) ->Fill( m_truthJet_pt    ->at(i) );
	    h_truthJetN_pt_l  .at(ireg).at(i) ->Fill( m_truthJet_pt    ->at(i) );
	    h_truthJetN_pt_m  .at(ireg).at(i) ->Fill( m_truthJet_pt    ->at(i) );
	    h_truthJetN_pt_s  .at(ireg).at(i) ->Fill( m_truthJet_pt    ->at(i) );
	    h_truthJetN_eta   .at(ireg).at(i) ->Fill( m_truthJet_eta   ->at(i) );
	    h_truthJetN_phi   .at(ireg).at(i) ->Fill( m_truthJet_phi   ->at(i) );
	    h_truthJetN_E     .at(ireg).at(i) ->Fill( m_truthJet_E     ->at(i) );
	    h_truthJetN_M     .at(ireg).at(i) ->Fill( m_truthJet_M     ->at(i) );
	    h_truthJetN_rapid .at(ireg).at(i) ->Fill( m_truthJet_rapid ->at(i) );
	    if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
	      h_truthJetN_Et   .at(ireg).at(i) ->Fill( truthJet_p4.Et() );
	      h_truthJetN_Et_l .at(ireg).at(i) ->Fill( truthJet_p4.Et() );
	      h_truthJetN_Et_m .at(ireg).at(i) ->Fill( truthJet_p4.Et() );
	      h_truthJetN_Et_s .at(ireg).at(i) ->Fill( truthJet_p4.Et() );
	    }
	  }
	}

	// width, constituents
	if ( m_histoInfoSwitch ->m_jetEConstit ) {
	  h_truthJet_width        .at(ireg)->Fill( m_truthJet_width      ->at(i) );
	  h_truthJet_girth        .at(ireg)->Fill( m_truthJet_girth      ->at(i) );
	  h_truthJet_numConstit   .at(ireg)->Fill( m_truthJet_numConstit ->at(i) );
	  h_truthJet_constitPt    .at(ireg)->Fill( m_truthJet_constitPt  ->at(i) );
	  for ( size_t j = 0; j != m_truthJet_constit_dR->at(i).size(); ++j )
	    h_truthJet_constit_dR .at(ireg)->Fill( m_truthJet_constit_dR ->at(i).at(j) );
	}

	// associated tracks / truth particles
	if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTrk ) {
	  // dR-matched tracks
	  h_truthJet_trkCount .at(ireg)->Fill( m_truthJet_trkCount ->at(i) );
	  h_truthJet_trkPt    .at(ireg)->Fill( m_truthJet_trkPt    ->at(i) );
	  h_truthJet_trkPt_l  .at(ireg)->Fill( m_truthJet_trkPt    ->at(i) );
	  h_truthJet_trkPt_m  .at(ireg)->Fill( m_truthJet_trkPt    ->at(i) );
	  h_truthJet_trkPt_s  .at(ireg)->Fill( m_truthJet_trkPt    ->at(i) );
	  for ( int j = 0; j != m_truthJet_trkCount->at(i); ++j )
	    h_truthJet_trk_dR .at(ireg)->Fill( m_truthJet_trk_dR   ->at(i).at(j) );
	  // dR-matched truth particles
	  h_truthJet_tpCount  .at(ireg)->Fill( m_truthJet_tpCount  ->at(i) );
	  h_truthJet_tpPt     .at(ireg)->Fill( m_truthJet_tpPt     ->at(i) );
	  h_truthJet_tpPt_l   .at(ireg)->Fill( m_truthJet_tpPt     ->at(i) );
	  h_truthJet_tpPt_m   .at(ireg)->Fill( m_truthJet_tpPt     ->at(i) );
	  h_truthJet_tpPt_s   .at(ireg)->Fill( m_truthJet_tpPt     ->at(i) );
	  for ( int j = 0; j != m_truthJet_tpCount->at(i); ++j )
	    h_truthJet_tp_dR  .at(ireg)->Fill( m_truthJet_tp_dR    ->at(i).at(j) );
	}

	// associated vertices
	if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetVtx ) {
	  // dR-matched secondary vertices
	  h_truthJet_secVtxCount   .at(ireg)->Fill( m_truthJet_secVtxCount   ->at(i) );
	  h_truthJet_secVtxPt      .at(ireg)->Fill( m_truthJet_secVtxPt      ->at(i) );
	  for ( int j = 0; j != m_truthJet_secVtxCount->at(i); ++j )
	    h_truthJet_secVtx_dR   .at(ireg)->Fill( m_truthJet_secVtx_dR     ->at(i).at(j) );
	  // dR-matched truth vertices
	  h_truthJet_truthVtxCount .at(ireg)->Fill( m_truthJet_truthVtxCount ->at(i) );
	  h_truthJet_truthVtxPt    .at(ireg)->Fill( m_truthJet_truthVtxPt    ->at(i) );
	  for ( int j = 0; j != m_truthJet_truthVtxCount->at(i); ++j )
	    h_truthJet_truthVtx_dR .at(ireg)->Fill( m_truthJet_truthVtx_dR   ->at(i).at(j) );
	}
      
	// count dark matched truth jets; fill dR

	// truth jets vs mu
	if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_jet ) {
	  h_truthJet_pt_vs_avgMu .at(ireg)->Fill( m_averageMu, m_truthJet_pt ->at(i) );
	  h_truthJet_pt_vs_actMu .at(ireg)->Fill( m_actualMu,  m_truthJet_pt ->at(i) );
	}
      }
    
    
      // DARK JETS
      h_darkJet_n .at(ireg)->Fill( m_darkJet_n );
      if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_jet ) {
	h_darkJet_n_vs_avgMu .at(ireg)->Fill( m_averageMu, m_darkJet_n );
	h_darkJet_n_vs_actMu .at(ireg)->Fill( m_actualMu,  m_darkJet_n );
      }
      
      for ( int i = 0; i != m_darkJet_n; ++i ) {

	TLorentzVector darkJet_p4;
	darkJet_p4.SetPtEtaPhiM( m_darkJet_pt->at(i), m_darkJet_eta->at(i), m_darkJet_phi->at(i), m_darkJet_M->at(i) );

	// basics
	h_darkJet_pt    .at(ireg)->Fill( m_darkJet_pt    ->at(i) );
	h_darkJet_pt_l  .at(ireg)->Fill( m_darkJet_pt    ->at(i) );
	h_darkJet_pt_m  .at(ireg)->Fill( m_darkJet_pt    ->at(i) );
	h_darkJet_pt_s  .at(ireg)->Fill( m_darkJet_pt    ->at(i) );
	h_darkJet_eta   .at(ireg)->Fill( m_darkJet_eta   ->at(i) );
	h_darkJet_phi   .at(ireg)->Fill( m_darkJet_phi   ->at(i) );
	h_darkJet_E     .at(ireg)->Fill( m_darkJet_E     ->at(i) );
	h_darkJet_M     .at(ireg)->Fill( m_darkJet_M     ->at(i) );
	h_darkJet_rapid .at(ireg)->Fill( m_darkJet_rapid ->at(i) );
	// kinematics
	if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
	  h_darkJet_px   .at(ireg)->Fill( darkJet_p4.Px() );
	  h_darkJet_py   .at(ireg)->Fill( darkJet_p4.Py() );
	  h_darkJet_pz   .at(ireg)->Fill( darkJet_p4.Pz() );
	  h_darkJet_Et   .at(ireg)->Fill( darkJet_p4.Et() );
	  h_darkJet_Et_l .at(ireg)->Fill( darkJet_p4.Et() );
	  h_darkJet_Et_m .at(ireg)->Fill( darkJet_p4.Et() );
	  h_darkJet_Et_s .at(ireg)->Fill( darkJet_p4.Et() );
	}
	// leading
	if ( m_numLead ) {
	  if ( i < m_numLead ) {
	    h_darkJetN_pt     .at(ireg).at(i) ->Fill( m_darkJet_pt    ->at(i) );
	    h_darkJetN_pt_l   .at(ireg).at(i) ->Fill( m_darkJet_pt    ->at(i) );
	    h_darkJetN_pt_m   .at(ireg).at(i) ->Fill( m_darkJet_pt    ->at(i) );
	    h_darkJetN_pt_s   .at(ireg).at(i) ->Fill( m_darkJet_pt    ->at(i) );
	    h_darkJetN_eta    .at(ireg).at(i) ->Fill( m_darkJet_eta   ->at(i) );
	    h_darkJetN_phi    .at(ireg).at(i) ->Fill( m_darkJet_phi   ->at(i) );
	    h_darkJetN_E      .at(ireg).at(i) ->Fill( m_darkJet_E     ->at(i) );
	    h_darkJetN_M      .at(ireg).at(i) ->Fill( m_darkJet_M     ->at(i) );
	    h_darkJetN_rapid  .at(ireg).at(i) ->Fill( m_darkJet_rapid ->at(i) );
	    if ( m_histoInfoSwitch ->m_kinematic || m_histoInfoSwitch ->m_kinematic_jet ) {
	      h_darkJetN_Et   .at(ireg).at(i) ->Fill( darkJet_p4.Et() );
	      h_darkJetN_Et_l .at(ireg).at(i) ->Fill( darkJet_p4.Et() );
	      h_darkJetN_Et_m .at(ireg).at(i) ->Fill( darkJet_p4.Et() );
	      h_darkJetN_Et_s .at(ireg).at(i) ->Fill( darkJet_p4.Et() );
	    }
	  }
	}

	// constituents
	if ( m_histoInfoSwitch ->m_jetEConstit ) {
	  h_darkJet_girth        .at(ireg)->Fill( m_darkJet_girth      ->at(i) );
	  h_darkJet_numConstit   .at(ireg)->Fill( m_darkJet_numConstit ->at(i) );
	  h_darkJet_constitPt    .at(ireg)->Fill( m_darkJet_constitPt  ->at(i) );
	  for ( size_t j = 0; j != m_darkJet_constit_dR->at(i).size(); ++j )
	    h_darkJet_constit_dR .at(ireg)->Fill( m_darkJet_constit_dR ->at(i).at(j) );
	}

	// associated tracks / truth particles
	if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetTrk ) {
	  // dR-matched tracks
	  h_darkJet_trkCount .at(ireg)->Fill( m_darkJet_trkCount ->at(i) );
	  h_darkJet_trkPt    .at(ireg)->Fill( m_darkJet_trkPt    ->at(i) );
	  h_darkJet_trkPt_l  .at(ireg)->Fill( m_darkJet_trkPt    ->at(i) );
	  h_darkJet_trkPt_m  .at(ireg)->Fill( m_darkJet_trkPt    ->at(i) );
	  h_darkJet_trkPt_s  .at(ireg)->Fill( m_darkJet_trkPt    ->at(i) );
	  for ( int j = 0; j != m_darkJet_trkCount->at(i); ++j )
	    h_darkJet_trk_dR .at(ireg)->Fill( m_darkJet_trk_dR   ->at(i).at(j) );
	  // dR-matched truth particles
	  h_darkJet_tpCount  .at(ireg)->Fill( m_darkJet_tpCount  ->at(i) );
	  h_darkJet_tpPt     .at(ireg)->Fill( m_darkJet_tpPt     ->at(i) );
	  h_darkJet_tpPt_l   .at(ireg)->Fill( m_darkJet_tpPt     ->at(i) );
	  h_darkJet_tpPt_m   .at(ireg)->Fill( m_darkJet_tpPt     ->at(i) );
	  h_darkJet_tpPt_s   .at(ireg)->Fill( m_darkJet_tpPt     ->at(i) );
	  for ( int j = 0; j != m_darkJet_tpCount->at(i); ++j )
	    h_darkJet_tp_dR  .at(ireg)->Fill( m_darkJet_tp_dR    ->at(i).at(j) );
	}
      
	// associated vertices
	if ( m_histoInfoSwitch ->m_match || m_histoInfoSwitch ->m_match_jet || m_histoInfoSwitch ->m_match_jetVtx ) {
	  // dR-matched secondary vertices
	  h_darkJet_secVtxCount   .at(ireg)->Fill( m_darkJet_secVtxCount   ->at(i) );
	  h_darkJet_secVtxPt      .at(ireg)->Fill( m_darkJet_secVtxPt      ->at(i) );
	  for ( int j = 0; j != m_darkJet_secVtxCount->at(i); ++j )
	    h_darkJet_secVtx_dR   .at(ireg)->Fill( m_darkJet_secVtx_dR     ->at(i).at(j) );
	  // dR-matched truth vertices
	  h_darkJet_truthVtxCount .at(ireg)->Fill( m_darkJet_truthVtxCount ->at(i) );
	  h_darkJet_truthVtxPt    .at(ireg)->Fill( m_darkJet_truthVtxPt    ->at(i) );
	  for ( int j = 0; j != m_darkJet_truthVtxCount->at(i); ++j )
	    h_darkJet_truthVtx_dR .at(ireg)->Fill( m_darkJet_truthVtx_dR   ->at(i).at(j) );
	}

	// dark jets vs mu
	if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_jet ) {
	  h_darkJet_pt_vs_avgMu .at(ireg)->Fill( m_averageMu, m_darkJet_pt ->at(i) );
	  h_darkJet_pt_vs_actMu .at(ireg)->Fill( m_actualMu,  m_darkJet_pt ->at(i) );
	}
      }
    }



    // -------------------------------- //
    // --- TRACKS / TRUTH PARTICLES --- //
    // -------------------------------- //
    
    if ( mc ) {
      
      // truth particles
      int n_Xd      = 0;
      int n_qd      = 0;
      int n_pid     = 0;
      int n_rhod    = 0;
      int n_offpid  = 0;
      int n_offrhod = 0;
      int n_allpid  = 0;
      int n_allrhod = 0;
      
      for ( int i = 0; i != m_tp_n; ++i ) {

	if ( !(m_tp_isDark ->at(i)) ) continue; // skip non-dark particles for now...

	// dark scalar mediators (Xd)
	if ( fabs( m_tp_pdgId ->at(i) ) == 4900001 && m_tp_status ->at(i) == 62 ) {
	  ++n_Xd;
	  h_Xd_pt             .at(ireg)->Fill( m_tp_pt                 ->at(i) );
	  h_Xd_eta            .at(ireg)->Fill( m_tp_eta                ->at(i) );
	  h_Xd_phi            .at(ireg)->Fill( m_tp_phi                ->at(i) );
	  h_Xd_E              .at(ireg)->Fill( m_tp_E                  ->at(i) );
	  h_Xd_M              .at(ireg)->Fill( m_tp_M                  ->at(i) );
	  h_Xd_charge         .at(ireg)->Fill( m_tp_charge             ->at(i) );
	  h_Xd_nParents       .at(ireg)->Fill( m_tp_nParents           ->at(i) );
	  h_Xd_nChildren      .at(ireg)->Fill( m_tp_nChildren          ->at(i) );
	  for ( int j = 0; j != m_tp_nParents->at(i); ++j ) {
	    h_Xd_parentPdgId  .at(ireg)->Fill( fabs( m_tp_parent_pdgId ->at(i).at(j) ) );
	    h_Xd_parentStatus .at(ireg)->Fill( m_tp_parent_status      ->at(i).at(j) );
	  }
	  for ( int j = 0; j != m_tp_nChildren->at(i); ++j ) {
	    h_Xd_childPdgId   .at(ireg)->Fill( fabs( m_tp_child_pdgId  ->at(i).at(j) ) );
	    h_Xd_childStatus  .at(ireg)->Fill( m_tp_child_status       ->at(i).at(j) );
	  }
	  if ( m_tp_hasPVtx )
	    h_Xd_prodVtx_r    .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	  if ( m_tp_hasDVtx )
	    h_Xd_decayVtx_r   .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	}
	// dark quarks (qd)
	else if ( fabs( m_tp_pdgId ->at(i) ) == 4900101 && m_tp_status ->at(i) == 71 ) {
	  ++n_qd;
	  h_qd_pt             .at(ireg)->Fill( m_tp_pt                 ->at(i) );
	  h_qd_eta            .at(ireg)->Fill( m_tp_eta                ->at(i) );
	  h_qd_phi            .at(ireg)->Fill( m_tp_phi                ->at(i) );
	  h_qd_E              .at(ireg)->Fill( m_tp_E                  ->at(i) );
	  h_qd_M              .at(ireg)->Fill( m_tp_M                  ->at(i) );
	  h_qd_charge         .at(ireg)->Fill( m_tp_charge             ->at(i) );
	  h_qd_nParents       .at(ireg)->Fill( m_tp_nParents           ->at(i) );
	  h_qd_nChildren      .at(ireg)->Fill( m_tp_nChildren          ->at(i) );
	  for ( int j = 0; j != m_tp_nParents->at(i); ++j ) {
	    h_qd_parentPdgId  .at(ireg)->Fill( fabs( m_tp_parent_pdgId ->at(i).at(j) ) );
	    h_qd_parentStatus .at(ireg)->Fill( m_tp_parent_status      ->at(i).at(j) );
	  }
	  for ( int j = 0; j != m_tp_nChildren->at(i); ++j ) {
	    h_qd_childPdgId   .at(ireg)->Fill( fabs( m_tp_child_pdgId  ->at(i).at(j) ) );
	    h_qd_childStatus  .at(ireg)->Fill( m_tp_child_status       ->at(i).at(j) );
	  }
	  if ( m_tp_hasPVtx )
	    h_qd_prodVtx_r    .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	  if ( m_tp_hasDVtx )
	    h_qd_decayVtx_r   .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	}
	// inclusive (standard + off-diagonal) dark pions (allpid)
	else if ( fabs( m_tp_pdgId ->at(i) ) == 4900111 || fabs( m_tp_pdgId ->at(i) ) == 4900211 ) {
	  ++n_allpid;
	  h_allpid_pt               .at(ireg)->Fill( m_tp_pt                 ->at(i) );
	  h_allpid_eta              .at(ireg)->Fill( m_tp_eta                ->at(i) );
	  h_allpid_phi              .at(ireg)->Fill( m_tp_phi                ->at(i) );
	  h_allpid_E                .at(ireg)->Fill( m_tp_E                  ->at(i) );
	  h_allpid_M                .at(ireg)->Fill( m_tp_M                  ->at(i) );
	  h_allpid_charge           .at(ireg)->Fill( m_tp_charge             ->at(i) );
	  h_allpid_nParents         .at(ireg)->Fill( m_tp_nParents           ->at(i) );
	  h_allpid_nChildren        .at(ireg)->Fill( m_tp_nChildren          ->at(i) );
	  for ( int j = 0; j != m_tp_nParents->at(i); ++j ) {
	    h_allpid_parentPdgId    .at(ireg)->Fill( fabs( m_tp_parent_pdgId ->at(i).at(j) ) );
	    h_allpid_parentStatus   .at(ireg)->Fill( m_tp_parent_status      ->at(i).at(j) );
	  }
	  for ( int j = 0; j != m_tp_nChildren->at(i); ++j ) {
	    h_allpid_childPdgId     .at(ireg)->Fill( fabs( m_tp_child_pdgId  ->at(i).at(j) ) );
	    h_allpid_childStatus    .at(ireg)->Fill( m_tp_child_status       ->at(i).at(j) );
	  }
	  if ( m_tp_hasPVtx )
	    h_allpid_prodVtx_r      .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	  if ( m_tp_hasDVtx )
	    h_allpid_decayVtx_r     .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	  // standard dark pions (pid)
	  if ( fabs( m_tp_pdgId ->at(i) ) == 4900111 ) {
	    ++n_pid;
	    h_pid_pt                .at(ireg)->Fill( m_tp_pt                 ->at(i) );
	    h_pid_eta               .at(ireg)->Fill( m_tp_eta                ->at(i) );
	    h_pid_phi               .at(ireg)->Fill( m_tp_phi                ->at(i) );
	    h_pid_E                 .at(ireg)->Fill( m_tp_E                  ->at(i) );
	    h_pid_M                 .at(ireg)->Fill( m_tp_M                  ->at(i) );
	    h_pid_charge            .at(ireg)->Fill( m_tp_charge             ->at(i) );
	    h_pid_nParents          .at(ireg)->Fill( m_tp_nParents           ->at(i) );
	    h_pid_nChildren         .at(ireg)->Fill( m_tp_nChildren          ->at(i) );
	    for ( int j = 0; j != m_tp_nParents->at(i); ++j ) {
	      h_pid_parentPdgId     .at(ireg)->Fill( fabs( m_tp_parent_pdgId ->at(i).at(j) ) );
	      h_pid_parentStatus    .at(ireg)->Fill( m_tp_parent_status      ->at(i).at(j) );
	    }
	    for ( int j = 0; j != m_tp_nChildren->at(i); ++j ) {
	      h_pid_childPdgId      .at(ireg)->Fill( fabs( m_tp_child_pdgId  ->at(i).at(j) ) );
	      h_pid_childStatus     .at(ireg)->Fill( m_tp_child_status       ->at(i).at(j) );
	    }
	    if ( m_tp_hasPVtx )
	      h_pid_prodVtx_r       .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	    if ( m_tp_hasDVtx )
	      h_pid_decayVtx_r      .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	  }
	  // off-diagonal dark pions (offpid)
	  else if ( fabs( m_tp_pdgId ->at(i) ) == 4900211 ) {
	    ++n_offpid;
	    h_offpid_pt             .at(ireg)->Fill( m_tp_pt                 ->at(i) );
	    h_offpid_eta            .at(ireg)->Fill( m_tp_eta                ->at(i) );
	    h_offpid_phi            .at(ireg)->Fill( m_tp_phi                ->at(i) );
	    h_offpid_E              .at(ireg)->Fill( m_tp_E                  ->at(i) );
	    h_offpid_M              .at(ireg)->Fill( m_tp_M                  ->at(i) );
	    h_offpid_charge         .at(ireg)->Fill( m_tp_charge             ->at(i) );
	    h_offpid_nParents       .at(ireg)->Fill( m_tp_nParents           ->at(i) );
	    h_offpid_nChildren      .at(ireg)->Fill( m_tp_nChildren          ->at(i) );
	    for ( int j = 0; j != m_tp_nParents->at(i); ++j ) {
	      h_offpid_parentPdgId  .at(ireg)->Fill( fabs( m_tp_parent_pdgId ->at(i).at(j) ) );
	      h_offpid_parentStatus .at(ireg)->Fill( m_tp_parent_status      ->at(i).at(j) );
	    }
	    for ( int j = 0; j != m_tp_nChildren->at(i); ++j ) {
	      h_offpid_childPdgId   .at(ireg)->Fill( fabs( m_tp_child_pdgId  ->at(i).at(j) ) );
	      h_offpid_childStatus  .at(ireg)->Fill( m_tp_child_status       ->at(i).at(j) );
	    }
	    if ( m_tp_hasPVtx )
	      h_offpid_prodVtx_r    .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	    if ( m_tp_hasDVtx )
	      h_offpid_decayVtx_r   .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	  }
	}
	// inclusive (standard + off-diagonal) dark rhos (allrhod)
	else if ( fabs( m_tp_pdgId ->at(i) ) == 4900113 || fabs( m_tp_pdgId ->at(i) ) == 4900213 ) {
	  ++n_allrhod;
	  h_allrhod_pt               .at(ireg)->Fill( m_tp_pt                 ->at(i) );
	  h_allrhod_eta              .at(ireg)->Fill( m_tp_eta                ->at(i) );
	  h_allrhod_phi              .at(ireg)->Fill( m_tp_phi                ->at(i) );
	  h_allrhod_E                .at(ireg)->Fill( m_tp_E                  ->at(i) );
	  h_allrhod_M                .at(ireg)->Fill( m_tp_M                  ->at(i) );
	  h_allrhod_charge           .at(ireg)->Fill( m_tp_charge             ->at(i) );
	  h_allrhod_nParents         .at(ireg)->Fill( m_tp_nParents           ->at(i) );
	  h_allrhod_nChildren        .at(ireg)->Fill( m_tp_nChildren          ->at(i) );
	  for ( int j = 0; j != m_tp_nParents->at(i); ++j ) {
	    h_allrhod_parentPdgId    .at(ireg)->Fill( fabs( m_tp_parent_pdgId ->at(i).at(j) ) );
	    h_allrhod_parentStatus   .at(ireg)->Fill( m_tp_parent_status      ->at(i).at(j) );
	  }
	  for ( int j = 0; j != m_tp_nChildren->at(i); ++j ) {
	    h_allrhod_childPdgId     .at(ireg)->Fill( fabs( m_tp_child_pdgId  ->at(i).at(j) ) );
	    h_allrhod_childStatus    .at(ireg)->Fill( m_tp_child_status       ->at(i).at(j) );
	  }
	  if ( m_tp_hasPVtx )
	    h_allrhod_prodVtx_r      .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	  if ( m_tp_hasDVtx )
	    h_allrhod_decayVtx_r     .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	  // standard dark rhos (rhod)
	  if ( fabs( m_tp_pdgId ->at(i) ) == 4900113 ) {
	    ++n_rhod;
	    h_rhod_pt                .at(ireg)->Fill( m_tp_pt                 ->at(i) );
	    h_rhod_eta               .at(ireg)->Fill( m_tp_eta                ->at(i) );
	    h_rhod_phi               .at(ireg)->Fill( m_tp_phi                ->at(i) );
	    h_rhod_E                 .at(ireg)->Fill( m_tp_E                  ->at(i) );
	    h_rhod_M                 .at(ireg)->Fill( m_tp_M                  ->at(i) );
	    h_rhod_charge            .at(ireg)->Fill( m_tp_charge             ->at(i) );
	    h_rhod_nParents          .at(ireg)->Fill( m_tp_nParents           ->at(i) );
	    h_rhod_nChildren         .at(ireg)->Fill( m_tp_nChildren          ->at(i) );
	    for ( int j = 0; j != m_tp_nParents->at(i); ++j ) {
	      h_rhod_parentPdgId     .at(ireg)->Fill( fabs( m_tp_parent_pdgId ->at(i).at(j) ) );
	      h_rhod_parentStatus    .at(ireg)->Fill( m_tp_parent_status      ->at(i).at(j) );
	    }
	    for ( int j = 0; j != m_tp_nChildren->at(i); ++j ) {
	      h_rhod_childPdgId      .at(ireg)->Fill( fabs( m_tp_child_pdgId  ->at(i).at(j) ) );
	      h_rhod_childStatus     .at(ireg)->Fill( m_tp_child_status       ->at(i).at(j) );
	    }
	    if ( m_tp_hasPVtx )
	      h_rhod_prodVtx_r       .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	    if ( m_tp_hasDVtx )
	      h_rhod_decayVtx_r      .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	  }
	  // off-diagonal dark rhos (offrhod)
	  else if ( fabs( m_tp_pdgId ->at(i) ) == 4900213 ) {
	    ++n_offrhod;
	    h_offrhod_pt             .at(ireg)->Fill( m_tp_pt                 ->at(i) );
	    h_offrhod_eta            .at(ireg)->Fill( m_tp_eta                ->at(i) );
	    h_offrhod_phi            .at(ireg)->Fill( m_tp_phi                ->at(i) );
	    h_offrhod_E              .at(ireg)->Fill( m_tp_E                  ->at(i) );
	    h_offrhod_M              .at(ireg)->Fill( m_tp_M                  ->at(i) );
	    h_offrhod_charge         .at(ireg)->Fill( m_tp_charge             ->at(i) );
	    h_offrhod_nParents       .at(ireg)->Fill( m_tp_nParents           ->at(i) );
	    h_offrhod_nChildren      .at(ireg)->Fill( m_tp_nChildren          ->at(i) );
	    for ( int j = 0; j != m_tp_nParents->at(i); ++j ) {
	      h_offrhod_parentPdgId  .at(ireg)->Fill( fabs( m_tp_parent_pdgId ->at(i).at(j) ) );
	      h_offrhod_parentStatus .at(ireg)->Fill( m_tp_parent_status      ->at(i).at(j) );
	    }
	    for ( int j = 0; j != m_tp_nChildren->at(i); ++j ) {
	      h_offrhod_childPdgId   .at(ireg)->Fill( fabs( m_tp_child_pdgId  ->at(i).at(j) ) );
	      h_offrhod_childStatus  .at(ireg)->Fill( m_tp_child_status       ->at(i).at(j) );
	    }
	    if ( m_tp_hasPVtx )
	      h_offrhod_prodVtx_r    .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	    if ( m_tp_hasDVtx )
	      h_offrhod_decayVtx_r   .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	  }
	}
  
      } // end loop over truth particles
      
      h_Xd_n      .at(ireg)->Fill( n_Xd      );
      h_qd_n      .at(ireg)->Fill( n_qd      );
      h_pid_n     .at(ireg)->Fill( n_pid     );
      h_offpid_n  .at(ireg)->Fill( n_offpid  );
      h_allpid_n  .at(ireg)->Fill( n_allpid  );
      h_rhod_n    .at(ireg)->Fill( n_rhod    );
      h_offrhod_n .at(ireg)->Fill( n_offrhod );
      h_allrhod_n .at(ireg)->Fill( n_allrhod );
      
    } // end if mc (truth particles)
    
    
    
    // ---------------- //
    // --- VERTICES --- //
    // ---------------- //
    
    // secondary vertices
    h_secVtx_n .at(ireg)->Fill( m_secVtx_n );
    if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_vtx ) {
      h_secVtx_n_vs_avgMu .at(ireg)->Fill( m_averageMu, m_secVtx_n );
      h_secVtx_n_vs_actMu .at(ireg)->Fill( m_actualMu,  m_secVtx_n );
    }

    // map of number of Ntrk vertices
    std::map<int, int> nNtrkVerts;
    if ( m_numVtxTrk ) {
      for ( int k = 1; k != m_numVtxTrk; ++k ) {
	int ntrk = k + 1;
	nNtrkVerts[ntrk] = 0;
      }
    }
    
    for ( int i = 0; i != m_secVtx_n; ++i ) {
      h_secVtx_x                .at(ireg)->Fill( m_secVtx_x                ->at(i) );
      h_secVtx_y                .at(ireg)->Fill( m_secVtx_y                ->at(i) );
      h_secVtx_z                .at(ireg)->Fill( m_secVtx_z                ->at(i) );
      h_secVtx_r                .at(ireg)->Fill( m_secVtx_r                ->at(i) );
      h_secVtx_r_l              .at(ireg)->Fill( m_secVtx_r                ->at(i) );
      h_secVtx_r_s              .at(ireg)->Fill( m_secVtx_r                ->at(i) );
      h_secVtx_pt               .at(ireg)->Fill( m_secVtx_pt               ->at(i) );
      h_secVtx_eta              .at(ireg)->Fill( m_secVtx_eta              ->at(i) );
      h_secVtx_phi              .at(ireg)->Fill( m_secVtx_phi              ->at(i) );
      h_secVtx_mass             .at(ireg)->Fill( m_secVtx_mass             ->at(i) );
      h_secVtx_mass_l           .at(ireg)->Fill( m_secVtx_mass             ->at(i) );
      h_secVtx_mass_s           .at(ireg)->Fill( m_secVtx_mass             ->at(i) );
      h_secVtx_mass_nonAssoc    .at(ireg)->Fill( m_secVtx_mass_nonAssoc    ->at(i) );
      h_secVtx_mass_nonAssoc_l  .at(ireg)->Fill( m_secVtx_mass_nonAssoc    ->at(i) );
      h_secVtx_mass_nonAssoc_s  .at(ireg)->Fill( m_secVtx_mass_nonAssoc    ->at(i) );
      h_secVtx_chi2             .at(ireg)->Fill( m_secVtx_chi2             ->at(i) );
      h_secVtx_direction        .at(ireg)->Fill( m_secVtx_direction        ->at(i) );
      h_secVtx_charge           .at(ireg)->Fill( m_secVtx_charge           ->at(i) );
      h_secVtx_Ht               .at(ireg)->Fill( m_secVtx_Ht               ->at(i) );
      h_secVtx_minOpAng         .at(ireg)->Fill( m_secVtx_minOpAng         ->at(i) );
      h_secVtx_maxOpAng         .at(ireg)->Fill( m_secVtx_maxOpAng         ->at(i) );
      h_secVtx_mind0            .at(ireg)->Fill( m_secVtx_mind0            ->at(i) );
      h_secVtx_maxd0            .at(ireg)->Fill( m_secVtx_maxd0            ->at(i) );
      h_secVtx_minOneTrkRmvMass .at(ireg)->Fill( m_secVtx_minOneTrkRmvMass ->at(i) );
      for ( size_t j = 0; j != m_secVtx_twoTrkMass->at(i).size(); ++j ) {
	h_secVtx_twoTrkMass     .at(ireg)->Fill( m_secVtx_twoTrkMass       ->at(i).at(j) );
	h_secVtx_twoTrkMassRest .at(ireg)->Fill( m_secVtx_twoTrkMassRest   ->at(i).at(j) );
	h_secVtx_twoTrkCharge   .at(ireg)->Fill( m_secVtx_twoTrkCharge     ->at(i).at(j) );
      }   
      h_secVtx_ntrk             .at(ireg)->Fill( m_secVtx_ntrk             ->at(i) );
      h_secVtx_ntrk_sel         .at(ireg)->Fill( m_secVtx_ntrk_sel         ->at(i) );
      h_secVtx_ntrk_assoc       .at(ireg)->Fill( m_secVtx_ntrk_assoc       ->at(i) );

      if ( m_numVtxTrk ) {
	h_secVtx_r_vs_ntrk                 .at(ireg)->Fill( m_secVtx_ntrk       ->at(i), m_secVtx_r             ->at(i) );
	h_secVtx_pt_vs_ntrk                .at(ireg)->Fill( m_secVtx_ntrk       ->at(i), m_secVtx_pt            ->at(i) );
	h_secVtx_mass_vs_ntrk              .at(ireg)->Fill( m_secVtx_ntrk       ->at(i), m_secVtx_mass          ->at(i) );
	h_secVtx_massNonAssoc_vs_ntrk      .at(ireg)->Fill( m_secVtx_ntrk       ->at(i), m_secVtx_mass_nonAssoc ->at(i) );
	h_secVtx_r_vs_ntrkSel              .at(ireg)->Fill( m_secVtx_ntrk_sel   ->at(i), m_secVtx_r             ->at(i) );
	h_secVtx_pt_vs_ntrkSel             .at(ireg)->Fill( m_secVtx_ntrk_sel   ->at(i), m_secVtx_pt            ->at(i) );
	h_secVtx_mass_vs_ntrkSel           .at(ireg)->Fill( m_secVtx_ntrk_sel   ->at(i), m_secVtx_mass          ->at(i) );
	h_secVtx_massNonAssoc_vs_ntrkSel   .at(ireg)->Fill( m_secVtx_ntrk_sel   ->at(i), m_secVtx_mass_nonAssoc ->at(i) );
	h_secVtx_r_vs_ntrkAssoc            .at(ireg)->Fill( m_secVtx_ntrk_assoc ->at(i), m_secVtx_r             ->at(i) );
	h_secVtx_pt_vs_ntrkAssoc           .at(ireg)->Fill( m_secVtx_ntrk_assoc ->at(i), m_secVtx_pt            ->at(i) );
	h_secVtx_mass_vs_ntrkAssoc         .at(ireg)->Fill( m_secVtx_ntrk_assoc ->at(i), m_secVtx_mass          ->at(i) );
	h_secVtx_massNonAssoc_vs_ntrkAssoc .at(ireg)->Fill( m_secVtx_ntrk_assoc ->at(i), m_secVtx_mass_nonAssoc ->at(i) );

	int ntrk = m_secVtx_ntrk ->at(i);
	if ( ntrk <= m_numVtxTrk ) {
	  ++nNtrkVerts[ntrk];
	  h_secVtxNtrk_x               .at(ireg).at(ntrk-2)->Fill( m_secVtx_x             ->at(i) );
	  h_secVtxNtrk_y               .at(ireg).at(ntrk-2)->Fill( m_secVtx_y             ->at(i) );
	  h_secVtxNtrk_z               .at(ireg).at(ntrk-2)->Fill( m_secVtx_z             ->at(i) );
	  h_secVtxNtrk_r               .at(ireg).at(ntrk-2)->Fill( m_secVtx_r             ->at(i) );
	  h_secVtxNtrk_r_l             .at(ireg).at(ntrk-2)->Fill( m_secVtx_r             ->at(i) );
	  h_secVtxNtrk_r_s             .at(ireg).at(ntrk-2)->Fill( m_secVtx_r             ->at(i) );
	  h_secVtxNtrk_pt              .at(ireg).at(ntrk-2)->Fill( m_secVtx_pt            ->at(i) );
	  h_secVtxNtrk_eta             .at(ireg).at(ntrk-2)->Fill( m_secVtx_eta           ->at(i) );
	  h_secVtxNtrk_phi             .at(ireg).at(ntrk-2)->Fill( m_secVtx_phi           ->at(i) );
	  h_secVtxNtrk_mass            .at(ireg).at(ntrk-2)->Fill( m_secVtx_mass          ->at(i) );
	  h_secVtxNtrk_mass_l          .at(ireg).at(ntrk-2)->Fill( m_secVtx_mass          ->at(i) );
	  h_secVtxNtrk_mass_s          .at(ireg).at(ntrk-2)->Fill( m_secVtx_mass          ->at(i) );
	  h_secVtxNtrk_mass_nonAssoc   .at(ireg).at(ntrk-2)->Fill( m_secVtx_mass_nonAssoc ->at(i) );
	  h_secVtxNtrk_mass_nonAssoc_l .at(ireg).at(ntrk-2)->Fill( m_secVtx_mass_nonAssoc ->at(i) );
	  h_secVtxNtrk_mass_nonAssoc_s .at(ireg).at(ntrk-2)->Fill( m_secVtx_mass_nonAssoc ->at(i) );
	  h_secVtxNtrk_chi2            .at(ireg).at(ntrk-2)->Fill( m_secVtx_chi2          ->at(i) );
	  h_secVtxNtrk_direction       .at(ireg).at(ntrk-2)->Fill( m_secVtx_direction     ->at(i) );
	  h_secVtxNtrk_charge          .at(ireg).at(ntrk-2)->Fill( m_secVtx_charge        ->at(i) );
	  h_secVtxNtrk_Ht              .at(ireg).at(ntrk-2)->Fill( m_secVtx_Ht            ->at(i) );
	  h_secVtxNtrk_minOpAng        .at(ireg).at(ntrk-2)->Fill( m_secVtx_minOpAng      ->at(i) );
	  h_secVtxNtrk_maxOpAng        .at(ireg).at(ntrk-2)->Fill( m_secVtx_maxOpAng      ->at(i) );
	  h_secVtxNtrk_mind0           .at(ireg).at(ntrk-2)->Fill( m_secVtx_mind0         ->at(i) );
	  h_secVtxNtrk_maxd0           .at(ireg).at(ntrk-2)->Fill( m_secVtx_maxd0         ->at(i) );
	  h_secVtxNtrk_ntrk_sel        .at(ireg).at(ntrk-2)->Fill( m_secVtx_ntrk_sel      ->at(i) );
	  h_secVtxNtrk_ntrk_assoc      .at(ireg).at(ntrk-2)->Fill( m_secVtx_ntrk_assoc    ->at(i) );
	}
      }

      if ( m_histoInfoSwitch ->m_vsMu || m_histoInfoSwitch ->m_vsMu_vtx ) {
	h_secVtx_r_vs_avgMu          .at(ireg)->Fill( m_averageMu, m_secVtx_r          ->at(i) );
	h_secVtx_pt_vs_avgMu         .at(ireg)->Fill( m_averageMu, m_secVtx_pt         ->at(i) );
	h_secVtx_eta_vs_avgMu        .at(ireg)->Fill( m_averageMu, m_secVtx_eta        ->at(i) );
	h_secVtx_phi_vs_avgMu        .at(ireg)->Fill( m_averageMu, m_secVtx_phi        ->at(i) );
	h_secVtx_mass_vs_avgMu       .at(ireg)->Fill( m_averageMu, m_secVtx_mass       ->at(i) );
	h_secVtx_ntrk_vs_avgMu       .at(ireg)->Fill( m_averageMu, m_secVtx_ntrk       ->at(i) );
	h_secVtx_ntrk_sel_vs_avgMu   .at(ireg)->Fill( m_averageMu, m_secVtx_ntrk_sel   ->at(i) );
	h_secVtx_ntrk_assoc_vs_avgMu .at(ireg)->Fill( m_averageMu, m_secVtx_ntrk_assoc ->at(i) );
	h_secVtx_r_vs_actMu          .at(ireg)->Fill( m_actualMu,  m_secVtx_r          ->at(i) );
	h_secVtx_pt_vs_actMu         .at(ireg)->Fill( m_actualMu,  m_secVtx_pt         ->at(i) );
	h_secVtx_eta_vs_actMu        .at(ireg)->Fill( m_actualMu,  m_secVtx_eta        ->at(i) );
	h_secVtx_phi_vs_actMu        .at(ireg)->Fill( m_actualMu,  m_secVtx_phi        ->at(i) );
	h_secVtx_mass_vs_actMu       .at(ireg)->Fill( m_actualMu,  m_secVtx_mass       ->at(i) );
	h_secVtx_ntrk_vs_actMu       .at(ireg)->Fill( m_actualMu,  m_secVtx_ntrk       ->at(i) );
	h_secVtx_ntrk_sel_vs_actMu   .at(ireg)->Fill( m_actualMu,  m_secVtx_ntrk_sel   ->at(i) );
	h_secVtx_ntrk_assoc_vs_actMu .at(ireg)->Fill( m_actualMu,  m_secVtx_ntrk_assoc ->at(i) );

	int ntrk = m_secVtx_ntrk ->at(i);
	if ( ntrk <= m_numVtxTrk ) {
	  h_secVtxNtrk_r_vs_avgMu          .at(ireg).at(ntrk-2)->Fill( m_averageMu, m_secVtx_r          ->at(i) );
	  h_secVtxNtrk_pt_vs_avgMu         .at(ireg).at(ntrk-2)->Fill( m_averageMu, m_secVtx_pt         ->at(i) );
	  h_secVtxNtrk_eta_vs_avgMu        .at(ireg).at(ntrk-2)->Fill( m_averageMu, m_secVtx_eta        ->at(i) );
	  h_secVtxNtrk_phi_vs_avgMu        .at(ireg).at(ntrk-2)->Fill( m_averageMu, m_secVtx_phi        ->at(i) );
	  h_secVtxNtrk_mass_vs_avgMu       .at(ireg).at(ntrk-2)->Fill( m_averageMu, m_secVtx_mass       ->at(i) );
	  h_secVtxNtrk_ntrk_sel_vs_avgMu   .at(ireg).at(ntrk-2)->Fill( m_averageMu, m_secVtx_ntrk_sel   ->at(i) );
	  h_secVtxNtrk_ntrk_assoc_vs_avgMu .at(ireg).at(ntrk-2)->Fill( m_averageMu, m_secVtx_ntrk_assoc ->at(i) );
	  h_secVtxNtrk_r_vs_actMu          .at(ireg).at(ntrk-2)->Fill( m_actualMu,  m_secVtx_r          ->at(i) );
	  h_secVtxNtrk_pt_vs_actMu         .at(ireg).at(ntrk-2)->Fill( m_actualMu,  m_secVtx_pt         ->at(i) );
	  h_secVtxNtrk_eta_vs_actMu        .at(ireg).at(ntrk-2)->Fill( m_actualMu,  m_secVtx_eta        ->at(i) );
	  h_secVtxNtrk_phi_vs_actMu        .at(ireg).at(ntrk-2)->Fill( m_actualMu,  m_secVtx_phi        ->at(i) );
	  h_secVtxNtrk_mass_vs_actMu       .at(ireg).at(ntrk-2)->Fill( m_actualMu,  m_secVtx_mass       ->at(i) );
	  h_secVtxNtrk_ntrk_sel_vs_actMu   .at(ireg).at(ntrk-2)->Fill( m_actualMu,  m_secVtx_ntrk_sel   ->at(i) );
	  h_secVtxNtrk_ntrk_assoc_vs_actMu .at(ireg).at(ntrk-2)->Fill( m_actualMu,  m_secVtx_ntrk_assoc ->at(i) );
	}
      }
      
    }

    // loop over nNtrkVerts map
    for ( const auto& nNtrkVtx : nNtrkVerts ) {
      int ntrk = nNtrkVtx.first;
      int nvtx = nNtrkVtx.second;
      h_secVtxNtrk_n .at(ireg).at(ntrk-2)->Fill( nvtx );
      if ( m_numVtxTrk ) {
	h_secVtxNtrk_n_vs_avgMu .at(ireg).at(ntrk-2)->Fill( m_averageMu, nvtx );
	h_secVtxNtrk_n_vs_actMu .at(ireg).at(ntrk-2)->Fill( m_actualMu,  nvtx );
      }
    }
    
  } // end loop over regions
  
  return StatusCode::SUCCESS;
}
