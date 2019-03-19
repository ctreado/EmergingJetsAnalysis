#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/EJsHistogramManager.h"
#include "EJsAnalysis/EJsHelperFunctions.h"


EJsHistogramManager :: EJsHistogramManager ( std::string name, std::string detailStr ) :
  HistogramManager ( name, detailStr )
{
  m_histoInfoSwitch = new EJsHelperClasses::HistogramInfoSwitch( detailStr );
  m_debug = false;

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
  
  m_pv_x            = 0;
  m_pv_y            = 0;
  m_pv_z            = 0;
  m_pv_r            = 0;
  m_pv_phi          = 0;
  m_pv_nTrk         = 0;

  
  m_passL1           = 0;
  m_passHLT          = 0;
  m_passedTriggers   = new std::vector<std::string>;
  m_disabledTriggers = new std::vector<std::string>;

  
  m_jet_n          = 0;
  m_jet_pt         = new std::vector<float>;
  m_jet_eta        = new std::vector<float>;
  m_jet_phi        = new std::vector<float>;
  m_jet_E          = new std::vector<float>;
  m_jet_M          = new std::vector<float>;
  m_jet_width      = new std::vector<float>;
  m_jet_numConstit = new std::vector<int>;
  
  m_jet_isTruthMatched = new std::vector<uint8_t>;
  m_jet_truthMatch_dR  = new std::vector<float>;
  m_jet_isDarkMatched  = new std::vector<uint8_t>;
  m_jet_darkMatch_dR   = new std::vector<float>;

  m_jet_secVtxCount   = new std::vector<int>;
  m_jet_secVtxPt      = new std::vector<float>;
  m_jet_secVtx_dR     = new std::vector<std::vector<float>>;
  m_jet_truthVtxCount = new std::vector<int>;
  m_jet_truthVtxPt    = new std::vector<float>;
  m_jet_truthVtx_dR   = new std::vector<std::vector<float>>;

  m_jet_trkCount = new std::vector<int>;
  m_jet_trkPt    = new std::vector<float>;
  m_jet_trk_dR   = new std::vector<std::vector<float>>;
  m_jet_tpCount  = new std::vector<int>;
  m_jet_tpPt     = new std::vector<float>;
  m_jet_tp_dR    = new std::vector<std::vector<float>>;

  m_jet_GhostTrackCount = new std::vector<int>;
  m_jet_GhostTrackPt    = new std::vector<float>;
  m_jet_GhostTruthCount = new std::vector<int>;
  m_jet_GhostTruthPt    = new std::vector<float>;


  m_truthJet_n          = 0;
  m_truthJet_pt         = new std::vector<float>;
  m_truthJet_eta        = new std::vector<float>;
  m_truthJet_phi        = new std::vector<float>;
  m_truthJet_E          = new std::vector<float>;
  m_truthJet_M          = new std::vector<float>;
  m_truthJet_width      = new std::vector<float>;
  m_truthJet_numConstit = new std::vector<int>;
  
  m_truthJet_isDarkMatched  = new std::vector<uint8_t>;
  m_truthJet_darkMatch_dR   = new std::vector<float>;

  m_truthJet_secVtxCount   = new std::vector<int>;
  m_truthJet_secVtxPt      = new std::vector<float>;
  m_truthJet_secVtx_dR     = new std::vector<std::vector<float>>;
  m_truthJet_truthVtxCount = new std::vector<int>;
  m_truthJet_truthVtxPt    = new std::vector<float>;
  m_truthJet_truthVtx_dR   = new std::vector<std::vector<float>>;

  m_truthJet_trkCount = new std::vector<int>;
  m_truthJet_trkPt    = new std::vector<float>;
  m_truthJet_trk_dR   = new std::vector<std::vector<float>>;
  m_truthJet_tpCount  = new std::vector<int>;
  m_truthJet_tpPt     = new std::vector<float>;
  m_truthJet_tp_dR    = new std::vector<std::vector<float>>;

  m_truthJet_girth      = new std::vector<float>;
  m_truthJet_constitPt  = new std::vector<float>;
  m_truthJet_constit_dR = new std::vector<std::vector<float>>;


  m_darkJet_n          = 0;
  m_darkJet_pt         = new std::vector<float>;
  m_darkJet_eta        = new std::vector<float>;
  m_darkJet_phi        = new std::vector<float>;
  m_darkJet_E          = new std::vector<float>;
  m_darkJet_M          = new std::vector<float>;
  m_darkJet_numConstit = new std::vector<int>;

  m_darkJet_secVtxCount   = new std::vector<int>;
  m_darkJet_secVtxPt      = new std::vector<float>;
  m_darkJet_secVtx_dR     = new std::vector<std::vector<float>>;
  m_darkJet_truthVtxCount = new std::vector<int>;
  m_darkJet_truthVtxPt    = new std::vector<float>;
  m_darkJet_truthVtx_dR   = new std::vector<std::vector<float>>;

  m_darkJet_trkCount = new std::vector<int>;
  m_darkJet_trkPt    = new std::vector<float>;
  m_darkJet_trk_dR   = new std::vector<std::vector<float>>;
  m_darkJet_tpCount  = new std::vector<int>;
  m_darkJet_tpPt     = new std::vector<float>;
  m_darkJet_tp_dR    = new std::vector<std::vector<float>>;

  m_darkJet_girth      = new std::vector<float>;
  m_darkJet_constitPt  = new std::vector<float>;
  m_darkJet_constit_dR = new std::vector<std::vector<float>>;

  
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
  m_secVtx_charge        = new std::vector<int>;
  m_secVtx_Ht            = new std::vector<float>;
  m_secVtx_mind0         = new std::vector<float>;
  m_secVtx_maxd0         = new std::vector<float>;

  m_secVtx_twoTracksMass     = new std::vector<std::vector<float>>;
  m_secVtx_twoTracksMassRest = new std::vector<std::vector<float>>;
  m_secVtx_twoTracksCharge   = new std::vector<std::vector<int>>;

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
  delete m_jet_width;
  delete m_jet_numConstit;

  delete m_jet_isTruthMatched;
  delete m_jet_truthMatch_dR;
  delete m_jet_isDarkMatched;
  delete m_jet_darkMatch_dR;

  delete m_jet_secVtxCount;
  delete m_jet_secVtxPt;
  delete m_jet_secVtx_dR;
  delete m_jet_truthVtxCount;
  delete m_jet_truthVtxPt;
  delete m_jet_truthVtx_dR;

  delete m_jet_trkCount;
  delete m_jet_trkPt;
  delete m_jet_trk_dR;
  delete m_jet_tpCount;
  delete m_jet_tpPt;
  delete m_jet_tp_dR;

  delete m_jet_GhostTrackCount;
  delete m_jet_GhostTrackPt;
  delete m_jet_GhostTruthCount;
  delete m_jet_GhostTruthPt;


  delete m_truthJet_pt;
  delete m_truthJet_eta;
  delete m_truthJet_phi;
  delete m_truthJet_E;
  delete m_truthJet_M;
  delete m_truthJet_width;
  delete m_truthJet_numConstit;

  delete m_truthJet_isDarkMatched;
  delete m_truthJet_darkMatch_dR;

  delete m_truthJet_secVtxCount;
  delete m_truthJet_secVtxPt;
  delete m_truthJet_secVtx_dR;
  delete m_truthJet_truthVtxCount;
  delete m_truthJet_truthVtxPt;
  delete m_truthJet_truthVtx_dR;

  delete m_truthJet_trkCount;
  delete m_truthJet_trkPt;
  delete m_truthJet_trk_dR;
  delete m_truthJet_tpCount;
  delete m_truthJet_tpPt;
  delete m_truthJet_tp_dR;

  delete m_truthJet_girth;
  delete m_truthJet_constitPt;
  delete m_truthJet_constit_dR;


  delete m_darkJet_pt;
  delete m_darkJet_eta;
  delete m_darkJet_phi;
  delete m_darkJet_E;
  delete m_darkJet_M;
  delete m_darkJet_numConstit;

  delete m_darkJet_secVtxCount;
  delete m_darkJet_secVtxPt;
  delete m_darkJet_secVtx_dR;
  delete m_darkJet_truthVtxCount;
  delete m_darkJet_truthVtxPt;
  delete m_darkJet_truthVtx_dR;

  delete m_darkJet_trkCount;
  delete m_darkJet_trkPt;
  delete m_darkJet_trk_dR;
  delete m_darkJet_tpCount;
  delete m_darkJet_tpPt;
  delete m_darkJet_tp_dR;

  delete m_darkJet_girth;
  delete m_darkJet_constitPt;
  delete m_darkJet_constit_dR;
  
  
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
  delete m_secVtx_charge;
  delete m_secVtx_Ht;
  delete m_secVtx_mind0;
  delete m_secVtx_maxd0;

  delete m_secVtx_twoTracksMass;
  delete m_secVtx_twoTracksMassRest;
  delete m_secVtx_twoTracksCharge;

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
  connectBranch<float>      ( tree, "PV_x",                           &m_pv_x            );
  connectBranch<float>      ( tree, "PV_y",                           &m_pv_y            );
  connectBranch<float>      ( tree, "PV_z",                           &m_pv_z            );
  connectBranch<float>      ( tree, "PV_r",                           &m_pv_r            );
  connectBranch<float>      ( tree, "PV_phi",                         &m_pv_phi          );
  connectBranch<uint32_t>   ( tree, "PV_nTracks",                     &m_pv_nTrk         );

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
  connectBranch<float> ( name, tree, "pt",              &m_jet_pt         );
  connectBranch<float> ( name, tree, "eta",             &m_jet_eta        );
  connectBranch<float> ( name, tree, "phi",             &m_jet_phi        );
  connectBranch<float> ( name, tree, "E",               &m_jet_E          );
  connectBranch<float> ( name, tree, "M",               &m_jet_M          );
  connectBranch<float> ( name, tree, "Width",           &m_jet_width      );
  connectBranch<int>   ( name, tree, "numConstituents", &m_jet_numConstit );

  connectBranch<uint8_t> ( name, tree, "isTruthMatched", &m_jet_isTruthMatched );
  connectBranch<float>   ( name, tree, "truthMatch_dR",  &m_jet_truthMatch_dR  );
  connectBranch<uint8_t> ( name, tree, "isDarkMatched",  &m_jet_isDarkMatched  );
  connectBranch<float>   ( name, tree, "darkMatch_dR",   &m_jet_darkMatch_dR   );

  connectBranch<int>                ( name, tree, "secVtxCount",   &m_jet_secVtxCount   );
  connectBranch<float>              ( name, tree, "secVtxPt",      &m_jet_secVtxPt      );
  connectBranch<std::vector<float>> ( name, tree, "secVtx_dR",     &m_jet_secVtx_dR     );
  connectBranch<int>                ( name, tree, "truthVtxCount", &m_jet_truthVtxCount );
  connectBranch<float>              ( name, tree, "truthVtxPt",    &m_jet_truthVtxPt    );
  connectBranch<std::vector<float>> ( name, tree, "truthVtx_dR",   &m_jet_truthVtx_dR   );

  connectBranch<int>                ( name, tree, "trkCount", &m_jet_trkCount );
  connectBranch<float>              ( name, tree, "trkPt",    &m_jet_trkPt    );
  connectBranch<std::vector<float>> ( name, tree, "trk_dR",   &m_jet_trk_dR   );
  connectBranch<int>                ( name, tree, "tpCount",  &m_jet_tpCount  );
  connectBranch<float>              ( name, tree, "tpPt",     &m_jet_tpPt     );
  connectBranch<std::vector<float>> ( name, tree, "tp_dR",    &m_jet_tp_dR    );

  connectBranch<int>   ( name, tree, "GhostTrackCount", &m_jet_GhostTrackCount );
  connectBranch<float> ( name, tree, "GhostTrackPt",    &m_jet_GhostTrackPt    );
  connectBranch<int>   ( name, tree, "GhostTruthCount", &m_jet_GhostTruthCount );
  connectBranch<float> ( name, tree, "GhostTruthPt",    &m_jet_GhostTruthPt    );

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
  connectBranch<float> ( name, tree, "pt",              &m_truthJet_pt         );
  connectBranch<float> ( name, tree, "eta",             &m_truthJet_eta        );
  connectBranch<float> ( name, tree, "phi",             &m_truthJet_phi        );
  connectBranch<float> ( name, tree, "E",               &m_truthJet_E          );
  connectBranch<float> ( name, tree, "M",               &m_truthJet_M          );
  connectBranch<float> ( name, tree, "Width",           &m_truthJet_width      );
  connectBranch<int>   ( name, tree, "numConstituents", &m_truthJet_numConstit );

  connectBranch<uint8_t> ( name, tree, "isDarkMatched",  &m_truthJet_isDarkMatched  );
  connectBranch<float>   ( name, tree, "darkMatch_dR",   &m_truthJet_darkMatch_dR   );

  connectBranch<int>                ( name, tree, "secVtxCount",   &m_truthJet_secVtxCount   );
  connectBranch<float>              ( name, tree, "secVtxPt",      &m_truthJet_secVtxPt      );
  connectBranch<std::vector<float>> ( name, tree, "secVtx_dR",     &m_truthJet_secVtx_dR     );
  connectBranch<int>                ( name, tree, "truthVtxCount", &m_truthJet_truthVtxCount );
  connectBranch<float>              ( name, tree, "truthVtxPt",    &m_truthJet_truthVtxPt    );
  connectBranch<std::vector<float>> ( name, tree, "truthVtx_dR",   &m_truthJet_truthVtx_dR   );

  connectBranch<int>                ( name, tree, "trkCount", &m_truthJet_trkCount );
  connectBranch<float>              ( name, tree, "trkPt",    &m_truthJet_trkPt    );
  connectBranch<std::vector<float>> ( name, tree, "trk_dR",   &m_truthJet_trk_dR   );
  connectBranch<int>                ( name, tree, "tpCount",  &m_truthJet_tpCount  );
  connectBranch<float>              ( name, tree, "tpPt",     &m_truthJet_tpPt     );
  connectBranch<std::vector<float>> ( name, tree, "tp_dR",    &m_truthJet_tp_dR    );

  connectBranch<float>              ( name, tree, "girth",          &m_truthJet_girth      );
  connectBranch<float>              ( name, tree, "constituentPt",  &m_truthJet_constitPt  );
  connectBranch<std::vector<float>> ( name, tree, "constituent_dR", &m_truthJet_constit_dR );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthDarkJets ( TTree* tree, const std::string darkJetName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthDarkJets()", "connecting truth dark jet branches" );

  std::string name = darkJetName;

  using namespace EJsHelper;
  connectBranch<int> ( tree, "n"+name, &m_darkJet_n );

  using namespace HelperFunctions;
  connectBranch<float> ( name, tree, "pt",              &m_darkJet_pt         );
  connectBranch<float> ( name, tree, "eta",             &m_darkJet_eta        );
  connectBranch<float> ( name, tree, "phi",             &m_darkJet_phi        );
  connectBranch<float> ( name, tree, "E",               &m_darkJet_E          );
  connectBranch<float> ( name, tree, "M",               &m_darkJet_M          );
  connectBranch<int>   ( name, tree, "numConstituents", &m_darkJet_numConstit );

  connectBranch<int>                ( name, tree, "secVtxCount",   &m_darkJet_secVtxCount   );
  connectBranch<float>              ( name, tree, "secVtxPt",      &m_darkJet_secVtxPt      );
  connectBranch<std::vector<float>> ( name, tree, "secVtx_dR",     &m_darkJet_secVtx_dR     );
  connectBranch<int>                ( name, tree, "truthVtxCount", &m_darkJet_truthVtxCount );
  connectBranch<float>              ( name, tree, "truthVtxPt",    &m_darkJet_truthVtxPt    );
  connectBranch<std::vector<float>> ( name, tree, "truthVtx_dR",   &m_darkJet_truthVtx_dR   );

  connectBranch<int>                ( name, tree, "trkCount", &m_darkJet_trkCount );
  connectBranch<float>              ( name, tree, "trkPt",    &m_darkJet_trkPt    );
  connectBranch<std::vector<float>> ( name, tree, "trk_dR",   &m_darkJet_trk_dR   );
  connectBranch<int>                ( name, tree, "tpCount",  &m_darkJet_tpCount  );
  connectBranch<float>              ( name, tree, "tpPt",     &m_darkJet_tpPt     );
  connectBranch<std::vector<float>> ( name, tree, "tp_dR",    &m_darkJet_tp_dR    );

  connectBranch<float>              ( name, tree, "girth",          &m_darkJet_girth      );
  connectBranch<float>              ( name, tree, "constituentPt",  &m_darkJet_constitPt  );
  connectBranch<std::vector<float>> ( name, tree, "constituent_dR", &m_darkJet_constit_dR );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthParts ( TTree* tree, const std::string truthName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthParts()", "connecting truth particle branches" );

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
  connectBranch<int>   ( name, tree, "charge",        &m_secVtx_charge        );
  connectBranch<float> ( name, tree, "Ht",            &m_secVtx_Ht            );
  connectBranch<float> ( name, tree, "mind0",         &m_secVtx_mind0         );
  connectBranch<float> ( name, tree, "maxd0",         &m_secVtx_maxd0         );

  connectBranch<std::vector<float>> ( name, tree, "twoTracksMass",     &m_secVtx_twoTracksMass     );
  connectBranch<std::vector<float>> ( name, tree, "twoTracksMassRest", &m_secVtx_twoTracksMassRest );
  connectBranch<std::vector<int>>   ( name, tree, "twoTracksCharge",   &m_secVtx_twoTracksCharge   );

  connectBranch<uint32_t> ( name, tree, "ntrk",       &m_secVtx_ntrk       );
  connectBranch<uint32_t> ( name, tree, "ntrk_sel",   &m_secVtx_ntrk_sel   );
  connectBranch<uint32_t> ( name, tree, "ntrk_assoc", &m_secVtx_ntrk_assoc );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: initialize ( const std::string outFileName, const std::vector<std::string>& regions, bool mc )
{
  if ( m_debug ) Info( "EJsHistogramManger::initialize()", "booking histograms" );
  
  // book histograms -- use info switches

  for ( const auto& region : regions ) {
    const std::string name = m_name + outFileName + "/" + region + "/";

    // event info
    h_npv       .push_back( book( name, "nPV",       "n primary vertices",               50, 0,  50 ) );
    h_actualMu  .push_back( book( name, "actualMu",  "actual interactions / crossing",  100, 0, 100 ) );
    h_averageMu .push_back( book( name, "averageMu", "average interactions / crossing", 100, 0, 100 ) );
    // pv info
    h_pv_x    .push_back( book( name, "pv_x",      "PV x-pos [mm]", 100, -1.5,  1.5 ) );
    h_pv_y    .push_back( book( name, "pv_y",      "PV y-pos [mm]", 100, -1.5,  1.5 ) );
    h_pv_z    .push_back( book( name, "pv_z",      "PV z-pos [mm]", 100, -150,  150 ) );
    h_pv_r    .push_back( book( name, "pv_r",      "PV r-pos [mm]", 100, -1.5,  1.5 ) );
    h_pv_phi  .push_back( book( name, "pv_phi",    "PV phi",        100, -3.5,  3.5 ) );
    h_pv_nTrk .push_back( book( name, "pv_nTrk",   "n PV tracks",   100,    0,  350 ) );


    // jet basics
    h_jet_n          .push_back( book( name, "jet_n",          "n jets",             15,    0,   15 ) );
    h_jet_pt         .push_back( book( name, "jet_pt",         "jet p_{T} [GeV]",   100,    0, 1500 ) );
    h_jet_eta        .push_back( book( name, "jet_eta",        "jet eta",           100,   -5,    5 ) );
    h_jet_phi        .push_back( book( name, "jet_phi",        "jet phi",           100, -3.5,  3.5 ) );
    h_jet_E          .push_back( book( name, "jet_E",          "jet energy [GeV]",  100,    0, 2500 ) );
    h_jet_M          .push_back( book( name, "jet_M",          "jet mass [GeV]",    100,    0,  250 ) );
    h_jet_width      .push_back( book( name, "jet_width",      "jet width",         100,    0,  0.4 ) );
    h_jet_numConstit .push_back( book( name, "jet_numConstit", "n jet constituents", 75,    0,   75 ) );
    
    // jet-matched DVs
    h_jet_secVtxCount   .push_back( book( name, "jet_secVtxCount",   "jet-matched secondary vertex count",             7, 0,   7 ) );
    h_jet_secVtxPt      .push_back( book( name, "jet_secVtxPt",      "jet-matched secondary vertex sum-p_{T} [GeV]", 100, 0,  500 ) );
    h_jet_secVtx_dR     .push_back( book( name, "jet_secVtx_dR",     "jet - matched-secondary-vertex dR",            100, 0,  0.4 ) );
    // jet matched TVs
    h_jet_truthVtxCount .push_back( book( name, "jet_truthVtxCount", "jet-matched truth vertex count",               100, 0,  200 ) );
    h_jet_truthVtxPt    .push_back( book( name, "jet_truthVtxPt",    "jet-matched truth vertex sum-p_{T} [GeV]",     100, 0, 5000 ) );
    h_jet_truthVtx_dR   .push_back( book( name, "jet_truthVtx_dR",   "jet - matched-truth-vertex dR",                100, 0,  0.4 ) );
    
    // jet matched tracks
    h_jet_trkCount .push_back( book( name, "jet_trkCount", "jet-matched track count",                    100, 0,   200 ) );
    h_jet_trkPt    .push_back( book( name, "jet_trkPt",    "jet-matched track sum-p_{T} [GeV]",          100, 0, 50000 ) );
    h_jet_trk_dR   .push_back( book( name, "jet_trk_dR",   "jet - matched-track dR",                     100, 0,   0.4 ) );
    // jet matched truth parts
    h_jet_tpCount  .push_back( book( name, "jet_tpCount",  "jet-matched truth particle count",           100, 0,   500 ) );
    h_jet_tpPt     .push_back( book( name, "jet_tpPt",     "jet-matched truth particle sum-p_{T} [GeV]", 100, 0, 50000 ) );
    h_jet_tp_dR    .push_back( book( name, "jet_tp_dR",    "jet - matched-truth-particle dR",            100, 0,   0.4 ) );

    // jet ghost tracks
    h_jet_GhostTrackCount .push_back( book( name, "jet_GhostTrackCount", "jet-matched ghost track count",           100, 0,   250 ) );
    h_jet_GhostTrackPt    .push_back( book( name, "jet_GhostTrackPt",    "jet-matched ghost track sum-p_{T} [GeV]", 100, 0, 50000 ) );
    // jet ghost truth
    h_jet_GhostTruthCount .push_back( book( name, "jet_GhostTruthCount", "jet-matched ghost truth count",           100, 0,   250 ) );
    h_jet_GhostTruthPt    .push_back( book( name, "jet_GhostTruthPt",    "jet-matched ghost truth sum-p_{T} [GeV]", 100, 0,  2000 ) );


    // truth jet basics
    h_truthJet_n          .push_back( book( name, "truthJet_n",          "n truth jets",              75,    0,   75 ) );
    h_truthJet_pt         .push_back( book( name, "truthJet_pt",         "truth jet p_{T} [GeV]",    100,    0, 1500 ) );
    h_truthJet_eta        .push_back( book( name, "truthJet_eta",        "truth jet eta",            100,   -5,    5 ) );
    h_truthJet_phi        .push_back( book( name, "truthJet_phi",        "truth jet phi",            100, -3.5,  3.5 ) );
    h_truthJet_E          .push_back( book( name, "truthJet_E",          "truth jet energy [GeV]",   100,    0, 2500 ) );
    h_truthJet_M          .push_back( book( name, "truthJet_M",          "truth jet mass [GeV]",     100,    0,  300 ) );
    h_truthJet_width      .push_back( book( name, "truthJet_width",      "truth jet width",          100,    0,  0.4 ) );
    h_truthJet_numConstit .push_back( book( name, "truthJet_numConstit", "n truth jet constituents", 100,    0,  200 ) );

    // truth-jet matched DVs
    h_truthJet_secVtxCount   .push_back( book( name, "truthJet_secVtxCount",   "truth-jet-matched secondary vertex count",             7, 0,    7 ) );
    h_truthJet_secVtxPt      .push_back( book( name, "truthJet_secVtxPt",      "truth-jet-matched secondary vertex sum-p_{T} [GeV]", 100, 0, 1000 ) );
    h_truthJet_secVtx_dR     .push_back( book( name, "truthJet_secVtx_dR",     "truth-jet - matched-secondary-vertex dR",            100, 0,  0.4 ) );
    // truth-jet matched TVs
    h_truthJet_truthVtxCount .push_back( book( name, "truthJet_truthVtxCount", "truth-jet-matched truth vertex count",               100, 0,  200 ) );
    h_truthJet_truthVtxPt    .push_back( book( name, "truthJet_truthVtxPt",    "truth-jet-matched truth vertex sum-p_{T} [GeV]",     100, 0, 1000 ) );
    h_truthJet_truthVtx_dR   .push_back( book( name, "truthJet_truthVtx_dR",   "truth-jet - matched-truth-vertex dR",                100, 0,  0.4 ) );

    // truth-jet matched tracks
    h_truthJet_trkCount .push_back( book( name, "truthJet_trkCount", "truth-jet-matched track count",                    100, 0,    200 ) );
    h_truthJet_trkPt    .push_back( book( name, "truthJet_trkPt",    "truth-jet-matched track sum-p_{T} [GeV]",          100, 0, 100000 ) );
    h_truthJet_trk_dR   .push_back( book( name, "truthJet_trk_dR",   "truth-jet - matched-track dR",                     100, 0,    0.4 ) );
    // truth-jet matched truth parts
    h_truthJet_tpCount  .push_back( book( name, "truthJet_tpCount",  "truth-jet-matched truth particle count",           100, 0,    500 ) );
    h_truthJet_tpPt     .push_back( book( name, "truthJet_tpPt",     "truth-jet-matched truth particle sum-p_{T} [GeV]", 100, 0,  50000 ) );
    h_truthJet_tp_dR    .push_back( book( name, "truthJet_tp_dR",    "truth-jet - matched-truth-particle dR",            100, 0,   0.4 ) );

    // truth jet constituents
    h_truthJet_girth      .push_back( book( name, "truthJet_girth",      "truth jet girth",                       100, 0,  0.4 ) );
    h_truthJet_constitPt  .push_back( book( name, "truthJet_constitPt",  "truth-jet constituent sum-p_{T} [GeV]", 100, 0, 2000 ) );
    h_truthJet_constit_dR .push_back( book( name, "truthJet_constit_dR", "truth-jet - constituent dR",            100, 0,  0.4 ) );


    // dark jet basics
    h_darkJet_n          .push_back( book( name, "darkJet_n",          "n dark jets",             50,    0,   50 ) );
    h_darkJet_pt         .push_back( book( name, "darkJet_pt",         "dark jet p_{T} [GeV]",   100,    0, 1500 ) );
    h_darkJet_eta        .push_back( book( name, "darkJet_eta",        "dark jet eta",           100,   -5,    5 ) );
    h_darkJet_phi        .push_back( book( name, "darkJet_phi",        "dark jet phi",           100, -3.5,  3.5 ) );
    h_darkJet_E          .push_back( book( name, "darkJet_E",          "dark jet energy [GeV]",  100,    0, 3000 ) );
    h_darkJet_M          .push_back( book( name, "darkJet_M",          "dark jet mass [GeV]",    100,    0,  300 ) );
    h_darkJet_numConstit .push_back( book( name, "darkJet_numConstit", "n dark jet constituents", 25,    0,   25 ) );

    // dark-jet matched DVs
    h_darkJet_secVtxCount   .push_back( book( name, "darkJet_secVtxCount",   "dark-jet-matched secondary vertex count",             7, 0,    7 ) );
    h_darkJet_secVtxPt      .push_back( book( name, "darkJet_secVtxPt",      "dark-jet-matched secondary vertex sum-p_{T} [GeV]", 100, 0, 1000 ) );
    h_darkJet_secVtx_dR     .push_back( book( name, "darkJet_secVtx_dR",     "dark-jet - matched-secondary-vertex dR",            100, 0,  0.4 ) );
    // dark-jet matched TVs
    h_darkJet_truthVtxCount .push_back( book( name, "darkJet_truthVtxCount", "dark-jet-matched truth vertex count",               100, 0,  200 ) );
    h_darkJet_truthVtxPt    .push_back( book( name, "darkJet_truthVtxPt",    "dark-jet-matched truth vertex sum-p_{T} [GeV]",     100, 0, 1000 ) );
    h_darkJet_truthVtx_dR   .push_back( book( name, "darkJet_truthVtx_dR",   "dark-jet - matched-truth-vertex dR",                100, 0,  0.4 ) );

    // dark-jet matched tracks
    h_darkJet_trkCount .push_back( book( name, "darkJet_trkCount", "dark-jet-matched track count",                    100, 0,    200 ) );
    h_darkJet_trkPt    .push_back( book( name, "darkJet_trkPt",    "dark-jet-matched track sum-p_{T} [GeV]",          100, 0, 100000 ) );
    h_darkJet_trk_dR   .push_back( book( name, "darkJet_trk_dR",   "dark-jet - matched-track dR",                     100, 0,    0.4 ) );
    // dark-jet matched truth parts
    h_darkJet_tpCount  .push_back( book( name, "darkJet_tpCount",  "dark-jet-matched truth particle count",           100, 0,    500 ) );
    h_darkJet_tpPt     .push_back( book( name, "darkJet_tpPt",     "dark-jet-matched truth particle sum-p_{T} [GeV]", 100, 0,  50000 ) );
    h_darkJet_tp_dR    .push_back( book( name, "darkJet_tp_dR",    "dark-jet - matched-truth-particle dR",            100, 0,    0.4 ) );

    // dark jet constituents
    h_darkJet_girth      .push_back( book( name, "darkJet_girth",      "dark jet girth",                       100, 0,  0.4 ) );
    h_darkJet_constitPt  .push_back( book( name, "darkJet_constitPt",  "dark-jet constituent sum-p_{T} [GeV]", 100, 0, 2000 ) );
    h_darkJet_constit_dR .push_back( book( name, "darkJet_constit_dR", "dark-jet - constituent dR",            100, 0,  0.4 ) );
    

    // secondary vertex basics
    h_secVtx_n             .push_back( book( name, "secVtx_n",             "n secondary vertices",                           20,     0,   20 ) );
    h_secVtx_x             .push_back( book( name, "secVtx_x",             "secondary vertex x-pos [mm]",                   100,  -500,  500 ) );
    h_secVtx_y             .push_back( book( name, "secVtx_y",             "secondary vertex y-pos [mm]",                   100,  -500,  500 ) );
    h_secVtx_z             .push_back( book( name, "secVtx_z",             "secondary vertex z-pos [mm]",                   100, -1000, 1000 ) );
    h_secVtx_r             .push_back( book( name, "secVtx_r",             "secondary vertex r-pos [mm]",                   100,     0,  500 ) );
    h_secVtx_pt            .push_back( book( name, "secVtx_pt",            "secondary vertex p_{T} [GeV]",                  100,     0, 1000 ) );
    h_secVtx_eta           .push_back( book( name, "secVtx_eta",           "secondary vertex eta",                          100,    -5,    5 ) );
    h_secVtx_phi           .push_back( book( name, "secVtx_phi",           "secondary vertex phi",                          100,  -3.5,  3.5 ) );
    h_secVtx_mass          .push_back( book( name, "secVtx_mass",          "secondary vertex mass [GeV]",                   100,     0,  100 ) );
    h_secVtx_mass_nonAssoc .push_back( book( name, "secVtx_mass_nonAssoc", "secondary vertex mass (selected tracks) [GeV]", 100,     0,  100 ) );
    h_secVtx_chi2          .push_back( book( name, "secVtx_chi2",          "secondary vertex chi2 / DoF",                   100,     0,  100 ) );
    h_secVtx_charge        .push_back( book( name, "secVtx_charge",        "secondary vertex charge",                        11,    -5,    5 ) );
    h_secVtx_Ht            .push_back( book( name, "secVtx_Ht",            "secondary vertex scalar sum-p_{T} [GeV]",       100,     0, 1000 ) );
    h_secVtx_mind0         .push_back( book( name, "secVtx_mind0",         "minimum secondary vertex track d0",             100,     0,  250 ) );
    h_secVtx_maxd0         .push_back( book( name, "secVtx_maxd0",         "maximum secondary vertex track d0",             100,     0,  250 ) );

    // secondary vertex arbitrary two-track systems
    h_secVtx_twoTracksMass     .push_back( book( name, "secVtx_twoTracksMass",     "secondary vertex arbitrary 2-track mass [GeV]",   100,  0, 100 ) );
    h_secVtx_twoTracksMassRest .push_back( book( name, "secVtx_twoTracksMassRest", "secondary vertex arbitrary n-2 track mass [GeV]", 100,  0, 100 ) );
    h_secVtx_twoTracksCharge   .push_back( book( name, "secVtx_twoTracksCharge",   "secondary vertex arbitrary 2-track charge",         7, -3,   3 ) );

    // secondary vertex tracks
    h_secVtx_ntrk       .push_back( book( name, "secVtx_ntrk",       "n secondary vertex tracks",            10, 2, 12 ) );
    h_secVtx_ntrk_sel   .push_back( book( name, "secVtx_ntrk_sel",   "n secondary vertex selected tracks",   10, 2, 12 ) );
    h_secVtx_ntrk_assoc .push_back( book( name, "secVtx_ntrk_assoc", "n secondary vertex associated tracks", 10, 2, 12 ) );

    // secondary vertex parameters vs n tracks
    h_secVtx_r_vs_ntrk    .push_back( book( name, "secVtx_r_vs_ntrk",    "n secondary vertex tracks",    10, 2,   12,
				  "secondary vertex r-pos [mm]", 100, 0,  500 ) );
    h_secVtx_mass_vs_ntrk .push_back( book( name, "secVtx_mass_vs_ntrk", "n secondary vertex tracks",    10, 2,   12,
				  "secondary vertex mass [GeV]", 100, 0,   50 ) );
  }

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: execute ( TTree* tree, Long64_t treeEntry, const std::vector<std::string>& regions, bool mc )
{
  if ( m_debug ) Info( "EJsHistogramManager::execute()", "filling histograms" );

  // fill histograms -- use info switches

  tree->GetEntry( treeEntry );

  // loop over regions ...
  for ( size_t ireg = 0; ireg != regions.size(); ++ireg ) {
    const std::string region = regions.at(ireg);

    
    // ------------------ //
    // --- EVENT INFO --- //
    // ------------------ //
    
    // event info
    h_npv       .at(ireg) ->Fill( m_npv       );
    h_actualMu  .at(ireg) ->Fill( m_actualMu  );
    h_averageMu .at(ireg) ->Fill( m_averageMu );
    
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
  
    // reco jets
    h_jet_n .at(ireg)->Fill( m_jet_n );
    for ( int i = 0; i != m_jet_n; ++i ) {
      h_jet_pt         .at(ireg)->Fill( m_jet_pt         ->at(i) );
      h_jet_eta        .at(ireg)->Fill( m_jet_eta        ->at(i) );
      h_jet_phi        .at(ireg)->Fill( m_jet_phi        ->at(i) );
      h_jet_E          .at(ireg)->Fill( m_jet_E          ->at(i) );
      h_jet_M          .at(ireg)->Fill( m_jet_M          ->at(i) );
      h_jet_width      .at(ireg)->Fill( m_jet_width      ->at(i) );
      h_jet_numConstit .at(ireg)->Fill( m_jet_numConstit ->at(i) );

      // count truth / dark matched jets; fill dR

      // matched secondary vertices
      h_jet_secVtxCount   .at(ireg)->Fill( m_jet_secVtxCount   ->at(i) );
      h_jet_secVtxPt      .at(ireg)->Fill( m_jet_secVtxPt      ->at(i) );
      for ( int j = 0; j != m_jet_secVtxCount->at(i); ++j )
	h_jet_secVtx_dR   .at(ireg)->Fill( m_jet_secVtx_dR     ->at(i).at(j) );
      // matched truth vertices
      h_jet_truthVtxCount .at(ireg)->Fill( m_jet_truthVtxCount ->at(i) );
      h_jet_truthVtxPt    .at(ireg)->Fill( m_jet_truthVtxPt    ->at(i) );
      for ( int j = 0; j != m_jet_truthVtxCount->at(i); ++j )
	h_jet_truthVtx_dR .at(ireg)->Fill( m_jet_truthVtx_dR   ->at(i).at(j) );
    
      // matched tracks
      h_jet_trkCount .at(ireg)->Fill( m_jet_trkCount ->at(i) );
      h_jet_trkPt    .at(ireg)->Fill( m_jet_trkPt    ->at(i) );
      for ( int j = 0; j != m_jet_trkCount->at(i); ++j )
	h_jet_trk_dR .at(ireg)->Fill( m_jet_trk_dR   ->at(i).at(j) );
      // matched truth particles
      h_jet_tpCount  .at(ireg)->Fill( m_jet_tpCount  ->at(i) );
      h_jet_tpPt     .at(ireg)->Fill( m_jet_tpPt     ->at(i) );
      for ( int j = 0; j != m_jet_tpCount->at(i); ++j )
	h_jet_tp_dR  .at(ireg)->Fill( m_jet_tp_dR    ->at(i).at(j) );
      
      // ghost tracks
      h_jet_GhostTrackCount .at(ireg)->Fill( m_jet_GhostTrackCount ->at(i) );
      h_jet_GhostTrackPt    .at(ireg)->Fill( m_jet_GhostTrackPt    ->at(i) );
      // ghost truth particles
      h_jet_GhostTruthCount .at(ireg)->Fill( m_jet_GhostTruthCount ->at(i) );
      h_jet_GhostTruthPt    .at(ireg)->Fill( m_jet_GhostTruthPt    ->at(i) );
    }
    
    
    // truth jets
    h_truthJet_n .at(ireg)->Fill( m_truthJet_n );
    for ( int i = 0; i != m_truthJet_n; ++i ) {
      h_truthJet_pt         .at(ireg)->Fill( m_truthJet_pt         ->at(i) );
      h_truthJet_eta        .at(ireg)->Fill( m_truthJet_eta        ->at(i) );
      h_truthJet_phi        .at(ireg)->Fill( m_truthJet_phi        ->at(i) );
      h_truthJet_E          .at(ireg)->Fill( m_truthJet_E          ->at(i) );
      h_truthJet_M          .at(ireg)->Fill( m_truthJet_M          ->at(i) );
      h_truthJet_width      .at(ireg)->Fill( m_truthJet_width      ->at(i) );
      h_truthJet_numConstit .at(ireg)->Fill( m_truthJet_numConstit ->at(i) );
      
      // count dark matched truth jets; fill dR
      
      // matched secondary vertices
      h_truthJet_secVtxCount   .at(ireg)->Fill( m_truthJet_secVtxCount   ->at(i) );
      h_truthJet_secVtxPt      .at(ireg)->Fill( m_truthJet_secVtxPt      ->at(i) );
      for ( int j = 0; j != m_truthJet_secVtxCount->at(i); ++j )
	h_truthJet_secVtx_dR   .at(ireg)->Fill( m_truthJet_secVtx_dR     ->at(i).at(j) );
      // matched truth vertices
      h_truthJet_truthVtxCount .at(ireg)->Fill( m_truthJet_truthVtxCount ->at(i) );
      h_truthJet_truthVtxPt    .at(ireg)->Fill( m_truthJet_truthVtxPt    ->at(i) );
      for ( int j = 0; j != m_truthJet_truthVtxCount->at(i); ++j )
	h_truthJet_truthVtx_dR .at(ireg)->Fill( m_truthJet_truthVtx_dR   ->at(i).at(j) );
      
      // matched tracks
      h_truthJet_trkCount .at(ireg)->Fill( m_truthJet_trkCount ->at(i) );
      h_truthJet_trkPt    .at(ireg)->Fill( m_truthJet_trkPt    ->at(i) );
      for ( int j = 0; j != m_truthJet_trkCount->at(i); ++j )
	h_truthJet_trk_dR .at(ireg)->Fill( m_truthJet_trk_dR   ->at(i).at(j) );
      // matched truth particles
      h_truthJet_tpCount  .at(ireg)->Fill( m_truthJet_tpCount  ->at(i) );
      h_truthJet_tpPt     .at(ireg)->Fill( m_truthJet_tpPt     ->at(i) );
      for ( int j = 0; j != m_truthJet_tpCount->at(i); ++j )
	h_truthJet_tp_dR  .at(ireg)->Fill( m_truthJet_tp_dR    ->at(i).at(j) );
      
      // constituents
      h_truthJet_girth        .at(ireg)->Fill( m_truthJet_girth     ->at(i) );
      h_truthJet_constitPt    .at(ireg)->Fill( m_truthJet_constitPt ->at(i) );
      for ( size_t j = 0; j != m_truthJet_constit_dR->at(i).size(); ++j )
	h_truthJet_constit_dR .at(ireg)->Fill( m_truthJet_constit_dR ->at(i).at(j) );
    }
    
    
    // dark jets
    h_darkJet_n .at(ireg)->Fill( m_darkJet_n );
    for ( int i = 0; i != m_darkJet_n; ++i ) {
      h_darkJet_pt         .at(ireg)->Fill( m_darkJet_pt         ->at(i) );
      h_darkJet_eta        .at(ireg)->Fill( m_darkJet_eta        ->at(i) );
      h_darkJet_phi        .at(ireg)->Fill( m_darkJet_phi        ->at(i) );
      h_darkJet_E          .at(ireg)->Fill( m_darkJet_E          ->at(i) );
      h_darkJet_M          .at(ireg)->Fill( m_darkJet_M          ->at(i) );
      h_darkJet_numConstit .at(ireg)->Fill( m_darkJet_numConstit ->at(i) );
      
      // matched secondary vertices
      h_darkJet_secVtxCount   .at(ireg)->Fill( m_darkJet_secVtxCount   ->at(i) );
      h_darkJet_secVtxPt      .at(ireg)->Fill( m_darkJet_secVtxPt      ->at(i) );
      for ( int j = 0; j != m_darkJet_secVtxCount->at(i); ++j )
	h_darkJet_secVtx_dR   .at(ireg)->Fill( m_darkJet_secVtx_dR     ->at(i).at(j) );
      // matched truth vertices
      h_darkJet_truthVtxCount .at(ireg)->Fill( m_darkJet_truthVtxCount ->at(i) );
      h_darkJet_truthVtxPt    .at(ireg)->Fill( m_darkJet_truthVtxPt    ->at(i) );
      for ( int j = 0; j != m_darkJet_truthVtxCount->at(i); ++j )
	h_darkJet_truthVtx_dR .at(ireg)->Fill( m_darkJet_truthVtx_dR   ->at(i).at(j) );
      
      // matched tracks
      h_darkJet_trkCount .at(ireg)->Fill( m_darkJet_trkCount ->at(i) );
      h_darkJet_trkPt    .at(ireg)->Fill( m_darkJet_trkPt    ->at(i) );
      for ( int j = 0; j != m_darkJet_trkCount->at(i); ++j )
	h_darkJet_trk_dR .at(ireg)->Fill( m_darkJet_trk_dR   ->at(i).at(j) );
      // matched truth particles
      h_darkJet_tpCount  .at(ireg)->Fill( m_darkJet_tpCount  ->at(i) );
      h_darkJet_tpPt     .at(ireg)->Fill( m_darkJet_tpPt     ->at(i) );
      for ( int j = 0; j != m_darkJet_tpCount->at(i); ++j )
	h_darkJet_tp_dR  .at(ireg)->Fill( m_darkJet_tp_dR    ->at(i).at(j) );
      
      // constituents
      h_darkJet_girth        .at(ireg)->Fill( m_darkJet_girth     ->at(i) );
      h_darkJet_constitPt    .at(ireg)->Fill( m_darkJet_constitPt ->at(i) );
      for ( size_t j = 0; j != m_darkJet_constit_dR->at(i).size(); ++j )
	h_darkJet_constit_dR .at(ireg)->Fill( m_darkJet_constit_dR ->at(i).at(j) );
    }
    
    
    
    // ---------------- //
    // --- VERTICES --- //
    // ---------------- //
    
    // secondary vertices
    h_secVtx_n .at(ireg)->Fill( m_secVtx_n );
    for ( int i = 0; i != m_secVtx_n; ++i ) {
      h_secVtx_x             .at(ireg)->Fill( m_secVtx_x             ->at(i) );
      h_secVtx_y             .at(ireg)->Fill( m_secVtx_y             ->at(i) );
      h_secVtx_z             .at(ireg)->Fill( m_secVtx_z             ->at(i) );
      h_secVtx_r             .at(ireg)->Fill( m_secVtx_r             ->at(i) );
      h_secVtx_pt            .at(ireg)->Fill( m_secVtx_pt            ->at(i) );
      h_secVtx_eta           .at(ireg)->Fill( m_secVtx_eta           ->at(i) );
      h_secVtx_phi           .at(ireg)->Fill( m_secVtx_phi           ->at(i) );
      h_secVtx_mass          .at(ireg)->Fill( m_secVtx_mass          ->at(i) );
      h_secVtx_mass_nonAssoc .at(ireg)->Fill( m_secVtx_mass_nonAssoc ->at(i) );
      h_secVtx_chi2          .at(ireg)->Fill( m_secVtx_chi2          ->at(i) );
      h_secVtx_charge        .at(ireg)->Fill( m_secVtx_charge        ->at(i) );
      h_secVtx_Ht            .at(ireg)->Fill( m_secVtx_Ht            ->at(i) );
      h_secVtx_mind0         .at(ireg)->Fill( m_secVtx_mind0         ->at(i) );
      h_secVtx_maxd0         .at(ireg)->Fill( m_secVtx_maxd0         ->at(i) );
      
      for ( size_t j = 0; j != m_secVtx_twoTracksMass->at(i).size(); ++j ) {
	h_secVtx_twoTracksMass     .at(ireg)->Fill( m_secVtx_twoTracksMass     ->at(i).at(j) );
	h_secVtx_twoTracksMassRest .at(ireg)->Fill( m_secVtx_twoTracksMassRest ->at(i).at(j) );
	h_secVtx_twoTracksCharge   .at(ireg)->Fill( m_secVtx_twoTracksCharge   ->at(i).at(j) );
      }
      
      h_secVtx_ntrk       .at(ireg)->Fill( m_secVtx_ntrk       ->at(i) );
      h_secVtx_ntrk_sel   .at(ireg)->Fill( m_secVtx_ntrk_sel   ->at(i) );
      h_secVtx_ntrk_assoc .at(ireg)->Fill( m_secVtx_ntrk_assoc ->at(i) );
      
      h_secVtx_r_vs_ntrk    .at(ireg)->Fill( m_secVtx_ntrk ->at(i), m_secVtx_r    ->at(i) );
      h_secVtx_mass_vs_ntrk .at(ireg)->Fill( m_secVtx_ntrk ->at(i), m_secVtx_mass ->at(i) );
    }
    
  } // end loop over regions
  
  return StatusCode::SUCCESS;
}
