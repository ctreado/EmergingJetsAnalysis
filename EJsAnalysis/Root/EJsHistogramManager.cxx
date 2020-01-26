#include <map>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/EJsHistogramManager.h"
#include "EJsAnalysis/AlgConsts.h"


EJsHistogramManager :: EJsHistogramManager ( const std::string& name, const std::string& detailStr, const std::string& jetStr,
					     const std::map<std::string, float>& metadata, float lumi,
					     bool debug, bool mc, bool unblind )
  : HistogramManager ( name, detailStr )
{
  m_histoInfoSwitch = new EJsHelperClasses::HistogramInfoSwitch( detailStr );
  m_jetStr          = jetStr;
  m_jetStrOth       = ( jetStr == "EMTopo" ) ? "PFlow" : "EMTopo";
  m_nEvents_init    = metadata.find( "eventCount_init" )->second;
  m_nEvents_sel     = metadata.find( "eventCount_sel"  )->second;
  m_sumw_init       = metadata.find( "sumw_init"       )->second;
  m_sumw_sel        = metadata.find( "sumw_sel"        )->second;
  m_sumw2_init      = metadata.find( "sumw2_init"      )->second;
  m_sumw2_sel       = metadata.find( "sumw2_sel"       )->second;
  m_xsec            = metadata.find( "crossSection"    )->second;
  m_kfactor         = metadata.find( "kFactor"         )->second;
  m_filteff         = metadata.find( "genFilterEff"    )->second;
  m_lumi            = lumi;
  m_debug           = debug;
  m_mc              = mc;
  m_unblind         = unblind;
  m_numLeadJets     = m_histoInfoSwitch->m_numLeadingJets;
  m_numVtxTrks      = m_histoInfoSwitch->m_numVtxTrks;

  if ( m_debug ) Info( "EJsHistogramManager()", "setting up" );

  // event branches
  m_runNumber          = 0;
  m_eventNumber        = 0;
  m_lumiBlock          = 0;
  m_bcid               = 0;
  m_mcEventNumber      = 0;
  m_mcChannelNumber    = 0;
  m_mcEventWeight      = 0;
  m_weight_pileup      = 0;
  m_npv                = 0;
  m_actualMu           = 0;
  m_averageMu          = 0;
  m_corrActualMu       = 0;
  m_corrAverageMu      = 0;
  m_corrScaleActualMu  = 0;
  m_corrScaleAverageMu = 0;
  m_randRunNr          = 0;
  m_randLumiBlockNr    = 0;
  m_searchMinusOne     = 0;
  m_search             = 0;
  m_signal             = 0;
  m_valid              = 0;
  m_njetHt             = 0;
  m_signal_njet        = 0;
  m_signal_jetPt       = 0;
  m_signal_jetEta      = 0;
  m_signal_njetHt      = 0;
  m_pv_x               = 0;
  m_pv_y               = 0;
  m_pv_z               = 0;
  m_pv_r               = 0;
  m_pv_phi             = 0;
  m_pv_ntrk            = 0;
  m_pv_location        = 0;

  // trigger branches
  m_passedTriggers   = new std::vector<std::string>;
  m_disabledTriggers = new std::vector<std::string>;
  m_triggerPrescales = new std::vector<float>;

  // jet branches
  m_jet_n            = 0;
  m_jet_ID           = new std::vector<int>;
  m_jet_index        = new std::vector<int>;
  m_jet_pt           = new std::vector<float>;
  m_jet_eta          = new std::vector<float>;
  m_jet_phi          = new std::vector<float>;
  m_jet_E            = new std::vector<float>;
  m_jet_M            = new std::vector<float>;
  m_jet_rapid        = new std::vector<float>;
  m_jet_passJVT      = new std::vector<int>;
  m_jet_trk_n        = new std::vector<int>;
  m_jet_trk_ID       = new std::vector<std::vector<int>>;
  m_jet_trk_index    = new std::vector<std::vector<int>>;
  m_jet_trk_dR       = new std::vector<std::vector<float>>;
  m_jet_secVtx_n     = new std::vector<int>;
  m_jet_secVtx_ID    = new std::vector<std::vector<int>>;
  m_jet_secVtx_index = new std::vector<std::vector<int>>;
  m_jet_secVtx_dR    = new std::vector<std::vector<float>>;
  // --> truth (dark) jet matching
  // other jet branches
  m_jetOth_n         = 0;
  m_jetOth_pt        = new std::vector<float>;
  m_jetOth_eta       = new std::vector<float>;
  m_jetOth_passJVT   = new std::vector<int>;

  // track branches
  m_trk_n      = 0;
  m_trk_ID     = new std::vector<int>;
  m_trk_index  = new std::vector<int>;
  m_trk_qOverP = new std::vector<float>;
  m_trk_theta  = new std::vector<float>;
  m_trk_pt     = new std::vector<float>;
  m_trk_eta    = new std::vector<float>;
  m_trk_phi    = new std::vector<float>;
  m_trk_d0     = new std::vector<float>;
  m_trk_z0     = new std::vector<float>;
  m_trk_errd0  = new std::vector<float>;
  m_trk_errz0  = new std::vector<float>;
  m_trk_errP   = new std::vector<float>;
  m_trk_chi2   = new std::vector<float>;
  m_trk_chiSq  = new std::vector<float>;
  m_trk_ndof   = new std::vector<int>;
  m_trk_charge = new std::vector<float>;
  m_trk_isLRT  = new std::vector<uint8_t>;

  // truth vertex branches
  m_truthVtx_n            = 0;
  m_truthVtx_llp          = new std::vector<std::string>;
  m_truthVtx_ID           = new std::vector<int>;
  m_truthVtx_index        = new std::vector<int>;
  m_truthVtx_x            = new std::vector<float>;
  m_truthVtx_y            = new std::vector<float>;
  m_truthVtx_z            = new std::vector<float>;
  m_truthVtx_r            = new std::vector<float>;
  m_truthVtx_pt           = new std::vector<float>;
  m_truthVtx_eta          = new std::vector<float>;
  m_truthVtx_phi          = new std::vector<float>;
  m_truthVtx_mass         = new std::vector<float>;
  m_truthVtx_nOutP        = new std::vector<int>;
  m_truthVtx_parent_pdgId = new std::vector<int>;
  m_truthVtx_nDesc        = new std::vector<int>;
  m_truthVtx_nRecoDesc    = new std::vector<int>;
  m_truthVtx_nSelDesc     = new std::vector<int>;
  m_truthVtx_nPos         = new std::vector<int>;
  m_truthVtx_reco_n       = new std::vector<int>;
  m_truthVtx_reco_ID      = new std::vector<std::vector<int>>;
  m_truthVtx_reco_index   = new std::vector<std::vector<int>>;
  m_truthVtx_reco_score   = new std::vector<std::vector<float>>;
  m_truthVtx_reco_posID   = new std::vector<std::vector<int>>;
  m_truthVtx_reco_resid   = new std::vector<std::vector<float>>;


  // secondary vertex branches
  m_secVtx_n               = 0;
  m_secVtx_ID              = new std::vector<int>;
  m_secVtx_index           = new std::vector<int>;
  m_secVtx_x               = new std::vector<float>;
  m_secVtx_y               = new std::vector<float>;
  m_secVtx_z               = new std::vector<float>;
  m_secVtx_r               = new std::vector<float>;
  m_secVtx_pt              = new std::vector<float>;
  m_secVtx_eta             = new std::vector<float>;
  m_secVtx_phi             = new std::vector<float>;
  m_secVtx_mass            = new std::vector<float>;
  m_secVtx_massNA          = new std::vector<float>;
  m_secVtx_direction       = new std::vector<float>;
  m_secVtx_minOpAng        = new std::vector<float>;
  m_secVtx_maxOpAng        = new std::vector<float>;
  m_secVtx_mind0           = new std::vector<float>;
  m_secVtx_maxd0           = new std::vector<float>;
  m_secVtx_pt_clean        = new std::vector<float>;
  m_secVtx_eta_clean       = new std::vector<float>;
  m_secVtx_phi_clean       = new std::vector<float>;
  m_secVtx_mass_clean      = new std::vector<float>;
  m_secVtx_massNA_clean    = new std::vector<float>;
  m_secVtx_direction_clean = new std::vector<float>;
  m_secVtx_minOpAng_clean  = new std::vector<float>;
  m_secVtx_maxOpAng_clean  = new std::vector<float>;
  m_secVtx_mind0_clean     = new std::vector<float>;
  m_secVtx_maxd0_clean     = new std::vector<float>;
  m_secVtx_pt_bare         = new std::vector<float>;
  m_secVtx_eta_bare        = new std::vector<float>;
  m_secVtx_phi_bare        = new std::vector<float>;
  m_secVtx_mass_bare       = new std::vector<float>;
  m_secVtx_massNA_bare     = new std::vector<float>;
  m_secVtx_direction_bare  = new std::vector<float>;
  m_secVtx_minOpAng_bare   = new std::vector<float>;
  m_secVtx_maxOpAng_bare   = new std::vector<float>;
  m_secVtx_mind0_bare      = new std::vector<float>;
  m_secVtx_maxd0_bare      = new std::vector<float>;
  m_secVtx_chi2            = new std::vector<float>;
  m_secVtx_ntrk            = new std::vector<int>;
  m_secVtx_ntrk_clean      = new std::vector<int>;
  m_secVtx_ntrk_filt       = new std::vector<int>;
  m_secVtx_covariance      = new std::vector<std::vector<float>>;
  m_secVtx_trk_ID          = new std::vector<std::vector<int>>;
  m_secVtx_trk_index       = new std::vector<std::vector<int>>;
  m_secVtx_trk_pt_sv       = new std::vector<std::vector<float>>;
  m_secVtx_trk_eta_sv      = new std::vector<std::vector<float>>;
  m_secVtx_trk_phi_sv      = new std::vector<std::vector<float>>;
  m_secVtx_trk_d0_sv       = new std::vector<std::vector<float>>;
  m_secVtx_trk_z0_sv       = new std::vector<std::vector<float>>;
  m_secVtx_trk_errd0_sv    = new std::vector<std::vector<float>>;
  m_secVtx_trk_errz0_sv    = new std::vector<std::vector<float>>;
  m_secVtx_trk_errP_sv     = new std::vector<std::vector<float>>;
  m_secVtx_trk_chi2_sv     = new std::vector<std::vector<float>>;
  m_secVtx_trk_isFinal     = new std::vector<std::vector<uint8_t>>;
  m_secVtx_trk_isSel       = new std::vector<std::vector<uint8_t>>;
  m_secVtx_trk_isAssoc     = new std::vector<std::vector<uint8_t>>;
  m_secVtx_trk_isClean     = new std::vector<std::vector<uint8_t>>;
  m_secVtx_trk_isFilt      = new std::vector<std::vector<uint8_t>>;
  m_secVtx_truth_n         = new std::vector<int>;
  m_secVtx_truth_llp       = new std::vector<std::vector<std::string>>;
  m_secVtx_truth_ID        = new std::vector<std::vector<int>>;
  m_secVtx_truth_index     = new std::vector<std::vector<int>>;
  m_secVtx_truth_dist      = new std::vector<std::vector<float>>;
  m_secVtx_truth_score     = new std::vector<std::vector<float>>;
  m_secVtx_truth_posID     = new std::vector<std::vector<int>>;
  m_secVtx_truth_resid     = new std::vector<std::vector<float>>;
  m_secVtx_jetMatched      = new std::vector<uint8_t>;
  m_secVtx_jetMatch_ID     = new std::vector<int>;
  m_secVtx_jetMatch_index  = new std::vector<int>;
  m_secVtx_jetMatch_dR     = new std::vector<float>;
}


EJsHistogramManager :: ~EJsHistogramManager ()
{
  if ( m_debug ) Info( "EJsHistogramManager()", "deleting" );

  if ( m_histoInfoSwitch ) delete m_histoInfoSwitch;

  // trigger branches
  delete m_passedTriggers;
  delete m_disabledTriggers;
  delete m_triggerPrescales;

  // jet branches
  delete m_jet_ID;
  delete m_jet_index;
  delete m_jet_pt;
  delete m_jet_eta;
  delete m_jet_phi;
  delete m_jet_E;
  delete m_jet_M;
  delete m_jet_rapid;
  delete m_jet_trk_n;
  delete m_jet_trk_ID;
  delete m_jet_trk_index;
  delete m_jet_trk_dR;
  delete m_jet_secVtx_n;
  delete m_jet_secVtx_ID;
  delete m_jet_secVtx_index;
  delete m_jet_secVtx_dR;
  // other jet branches
  delete m_jetOth_pt;
  delete m_jetOth_eta;

  // track branches
  delete m_trk_ID;
  delete m_trk_index;
  delete m_trk_qOverP;
  delete m_trk_theta;
  delete m_trk_pt;
  delete m_trk_eta;
  delete m_trk_phi;
  delete m_trk_d0;
  delete m_trk_z0;
  delete m_trk_errd0;
  delete m_trk_errz0;
  delete m_trk_errP;
  delete m_trk_chi2;
  delete m_trk_chiSq;
  delete m_trk_ndof;
  delete m_trk_charge;
  delete m_trk_isLRT;

  // truth vertex branches
  delete m_truthVtx_llp;
  delete m_truthVtx_ID;
  delete m_truthVtx_index;
  delete m_truthVtx_x;
  delete m_truthVtx_y;
  delete m_truthVtx_z;
  delete m_truthVtx_r;
  delete m_truthVtx_pt;
  delete m_truthVtx_eta;
  delete m_truthVtx_phi;
  delete m_truthVtx_mass;
  delete m_truthVtx_nOutP;
  delete m_truthVtx_parent_pdgId;
  delete m_truthVtx_nDesc;
  delete m_truthVtx_nRecoDesc;
  delete m_truthVtx_nSelDesc;
  delete m_truthVtx_nPos;
  delete m_truthVtx_reco_n;
  delete m_truthVtx_reco_ID;
  delete m_truthVtx_reco_index;
  delete m_truthVtx_reco_score;
  delete m_truthVtx_reco_posID;
  delete m_truthVtx_reco_resid;

  // secondary vertex branches
  delete m_secVtx_ID;
  delete m_secVtx_index;
  delete m_secVtx_x;
  delete m_secVtx_y;
  delete m_secVtx_z;
  delete m_secVtx_r;
  delete m_secVtx_pt;
  delete m_secVtx_eta;
  delete m_secVtx_phi;
  delete m_secVtx_mass;
  delete m_secVtx_massNA;
  delete m_secVtx_direction;
  delete m_secVtx_minOpAng;
  delete m_secVtx_maxOpAng;
  delete m_secVtx_mind0;
  delete m_secVtx_maxd0;
  delete m_secVtx_pt_clean;
  delete m_secVtx_eta_clean;
  delete m_secVtx_phi_clean;
  delete m_secVtx_mass_clean;
  delete m_secVtx_massNA_clean;
  delete m_secVtx_direction_clean;
  delete m_secVtx_minOpAng_clean;
  delete m_secVtx_maxOpAng_clean;
  delete m_secVtx_mind0_clean;
  delete m_secVtx_maxd0_clean;
  delete m_secVtx_pt_bare;
  delete m_secVtx_eta_bare;
  delete m_secVtx_phi_bare;
  delete m_secVtx_mass_bare;
  delete m_secVtx_massNA_bare;
  delete m_secVtx_direction_bare;
  delete m_secVtx_minOpAng_bare;
  delete m_secVtx_maxOpAng_bare;
  delete m_secVtx_mind0_bare;
  delete m_secVtx_maxd0_bare;
  delete m_secVtx_chi2;
  delete m_secVtx_ntrk;
  delete m_secVtx_ntrk_clean;
  delete m_secVtx_ntrk_filt;
  delete m_secVtx_covariance;
  delete m_secVtx_trk_ID;
  delete m_secVtx_trk_index;
  delete m_secVtx_trk_pt_sv;
  delete m_secVtx_trk_eta_sv;
  delete m_secVtx_trk_phi_sv;
  delete m_secVtx_trk_d0_sv;
  delete m_secVtx_trk_z0_sv;
  delete m_secVtx_trk_errd0_sv;
  delete m_secVtx_trk_errz0_sv;
  delete m_secVtx_trk_chi2_sv;
  delete m_secVtx_trk_isFinal;
  delete m_secVtx_trk_isSel;
  delete m_secVtx_trk_isAssoc;
  delete m_secVtx_trk_isClean;
  delete m_secVtx_trk_isFilt;
  delete m_secVtx_truth_n;
  delete m_secVtx_truth_llp;
  delete m_secVtx_truth_ID;
  delete m_secVtx_truth_index;
  delete m_secVtx_truth_dist;
  delete m_secVtx_truth_score;
  delete m_secVtx_truth_posID;
  delete m_secVtx_truth_resid;
  delete m_secVtx_jetMatched;
  delete m_secVtx_jetMatch_ID;
  delete m_secVtx_jetMatch_index;
  delete m_secVtx_jetMatch_dR;
}



StatusCode EJsHistogramManager :: connectEvents ( TTree* tree )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectEvents()", "connecting event branches" );

  using namespace EJsHelper;

  // event info basics
  connectBranch<int>      ( tree, "runNumber",       &m_runNumber       );
  connectBranch<Long64_t> ( tree, "eventNumber",     &m_eventNumber     );
  connectBranch<int>      ( tree, "lumiBlock",       &m_lumiBlock       );
  connectBranch<int>      ( tree, "bcid",            &m_bcid            );  
  if ( m_mc ) {
    connectBranch<int>    ( tree, "mcEventNumber",   &m_mcEventNumber   );
    connectBranch<int>    ( tree, "mcChannelNumber", &m_mcChannelNumber );
  }

  // event weights
  if ( m_mc )
    connectBranch<float>  ( tree, "mcEventWeight", &m_mcEventWeight );
  connectBranch<float>    ( tree, "weight_pileup", &m_weight_pileup );

  // pileup
  connectBranch<int>      ( tree, "NPV",                            &m_npv                );
  connectBranch<float>    ( tree, "actualInteractionsPerCrossing",  &m_actualMu           );
  connectBranch<float>    ( tree, "averageInteractionsPerCrossing", &m_averageMu          );
  connectBranch<float>    ( tree, "correctedActualMu",              &m_corrActualMu       );
  connectBranch<float>    ( tree, "correctedAverageMu",             &m_corrAverageMu      );
  connectBranch<float>    ( tree, "correctedAndScaledActualMu",     &m_corrScaleActualMu  );
  connectBranch<float>    ( tree, "correctedAndScaledAverageMu",    &m_corrScaleAverageMu );
  if ( m_mc ) {
    connectBranch<int>    ( tree, "rand_run_nr",                    &m_randRunNr          );
    connectBranch<int>    ( tree, "rand_lumiblock_nr",              &m_randLumiBlockNr    );
  }

  // region selections
  connectBranch<uint8_t>  ( tree, "isSearchMinusOne_"   + m_jetStr, &m_searchMinusOne );
  connectBranch<uint8_t>  ( tree, "isSearch_"           + m_jetStr, &m_search         );
  connectBranch<uint8_t>  ( tree, "isSignal_"           + m_jetStr, &m_signal         );
  connectBranch<uint8_t>  ( tree, "isValid_"            + m_jetStr, &m_valid          );
  connectBranch<float>    ( tree, "NJetHt_"             + m_jetStr, &m_njetHt         );
  connectBranch<uint8_t>  ( tree, "passesSignalNJet_"   + m_jetStr, &m_signal_njet    );
  connectBranch<uint8_t>  ( tree, "passesSignalJetPt_"  + m_jetStr, &m_signal_jetPt   );
  connectBranch<uint8_t>  ( tree, "passesSignalJetEta_" + m_jetStr, &m_signal_jetEta  );
  connectBranch<uint8_t>  ( tree, "passesSignalNJetHt_" + m_jetStr, &m_signal_njetHt  );

  // PV info
  connectBranch<float>    ( tree, "PV_x",        &m_pv_x        );
  connectBranch<float>    ( tree, "PV_y",        &m_pv_y        );
  connectBranch<float>    ( tree, "PV_z",        &m_pv_z        );
  connectBranch<float>    ( tree, "PV_r",        &m_pv_r        );
  connectBranch<float>    ( tree, "PV_phi",      &m_pv_phi      );
  connectBranch<int>      ( tree, "PV_nTracks",  &m_pv_ntrk     );
  connectBranch<int>      ( tree, "PV_location", &m_pv_location );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTriggers ( TTree* tree )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTriggers()", "connecting trigger branches" );

  using namespace EJsHelper;

  connectBranchVec<std::string> ( tree, "passedTriggers",   &m_passedTriggers   );
  connectBranchVec<std::string> ( tree, "disabledTriggers", &m_disabledTriggers );
  if ( !m_mc )
    connectBranchVec<float>     ( tree, "triggerPrescales", &m_triggerPrescales );
  
  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectJets ( TTree* tree, const std::string& jetName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectJets()", "connecting jet branches" );

  std::string name = jetName;

  using namespace EJsHelper;

  connectBranch<int> ( tree, "n" + name, &m_jet_n );

  using namespace HelperFunctions;

  connectBranch<int>   ( name, tree, "ID",             &m_jet_ID      );
  connectBranch<int>   ( name, tree, "index",          &m_jet_index   );
  connectBranch<float> ( name, tree, "pt",             &m_jet_pt      );
  connectBranch<float> ( name, tree, "eta",            &m_jet_eta     );
  connectBranch<float> ( name, tree, "phi",            &m_jet_phi     );
  connectBranch<float> ( name, tree, "E",              &m_jet_E       );
  connectBranch<float> ( name, tree, "M",              &m_jet_M       );
  connectBranch<float> ( name, tree, "rapidity",       &m_jet_rapid   );
  connectBranch<int>   ( name, tree, "JvtPass_Medium", &m_jet_passJVT );

  connectBranch<int>                ( name, tree, "trkCount",  &m_jet_trk_n     );
  connectBranch<std::vector<int>>   ( name, tree, "trk_ID",    &m_jet_trk_ID    );
  connectBranch<std::vector<int>>   ( name, tree, "trk_index", &m_jet_trk_index );
  connectBranch<std::vector<float>> ( name, tree, "trk_dR",    &m_jet_trk_dR    );

  connectBranch<int>                ( name, tree, "secVtxCount",  &m_jet_secVtx_n     );
  connectBranch<std::vector<int>>   ( name, tree, "secVtx_ID",    &m_jet_secVtx_ID    );
  connectBranch<std::vector<int>>   ( name, tree, "secVtx_index", &m_jet_secVtx_index );
  connectBranch<std::vector<float>> ( name, tree, "secVtx_dR",    &m_jet_secVtx_dR    );
  
  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectOtherJets ( TTree* tree, const std::string& jetOthName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectOtherJets()", "connecting other jet branchees" );

  std::string name = jetOthName;

  using namespace EJsHelper;

  connectBranch<int> ( tree, "n" + name, &m_jetOth_n );

  using namespace HelperFunctions;

  connectBranch<float> ( name, tree, "pt",             &m_jetOth_pt      );
  connectBranch<float> ( name, tree, "eta",            &m_jetOth_eta     );
  connectBranch<int>   ( name, tree, "JvtPass_Medium", &m_jetOth_passJVT );
  
  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTrigJets ( TTree* tree, const std::string& trigJetName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTrigJets()", "connecting trigger jet branches" );
  
  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthJets ( TTree* tree, const std::string& truthJetName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthJets()", "connecting truth jet branches" );
  
  return StatusCode::SUCCESS;
}


StatusCode EJsHistogramManager :: connectTruthDarkJets ( TTree* tree, const std::string& darkJetName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthDarkJets()", "connecting truth dark jet branches" );
  
  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTracks ( TTree* tree, const std::string& trackName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTracks()", "connecting track branches" );

  std::string name = trackName;

  using namespace EJsHelper;

  connectBranch<int> ( tree, "n" + name, &m_trk_n );

  using namespace HelperFunctions;

  connectBranch<int>     ( name, tree, "ID",         &m_trk_ID     );
  connectBranch<int>     ( name, tree, "index",      &m_trk_index  );
  connectBranch<float>   ( name, tree, "qOverP",     &m_trk_qOverP );
  connectBranch<float>   ( name, tree, "theta",      &m_trk_theta  );
  connectBranch<float>   ( name, tree, "pt",         &m_trk_pt     );
  connectBranch<float>   ( name, tree, "eta",        &m_trk_eta    );
  connectBranch<float>   ( name, tree, "phi",        &m_trk_phi    );
  connectBranch<float>   ( name, tree, "d0",         &m_trk_d0     );
  connectBranch<float>   ( name, tree, "z0",         &m_trk_z0     );
  connectBranch<float>   ( name, tree, "errd0",      &m_trk_errd0  );
  connectBranch<float>   ( name, tree, "errz0",      &m_trk_errz0  );
  connectBranch<float>   ( name, tree, "errP",       &m_trk_errP   );
  connectBranch<float>   ( name, tree, "chi2",       &m_trk_chi2   );
  connectBranch<float>   ( name, tree, "chiSquared", &m_trk_chiSq  );
  connectBranch<int>     ( name, tree, "numberDoF",  &m_trk_ndof   );
  connectBranch<float>   ( name, tree, "charge",     &m_trk_charge );
  connectBranch<uint8_t> ( name, tree, "isLRT",      &m_trk_isLRT  );
  
  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthParts ( TTree* tree, const std::string& truthPartName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthParts()", "connecting truth particle branches" );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectSecondaryVerts ( TTree* tree, const std::string& secVtxName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectSecondaryVerts()", "connecting secondary vertex branches" );

  std::string name = secVtxName;

  using namespace EJsHelper;

  connectBranch<int> ( tree, "n" + name, &m_secVtx_n );
  
  using namespace HelperFunctions;

  connectBranch<int>   ( name, tree, "ID",                  &m_secVtx_ID              );
  connectBranch<int>   ( name, tree, "index",               &m_secVtx_index           );
  connectBranch<float> ( name, tree, "x",                   &m_secVtx_x               );
  connectBranch<float> ( name, tree, "y",                   &m_secVtx_y               );
  connectBranch<float> ( name, tree, "z",                   &m_secVtx_z               );
  connectBranch<float> ( name, tree, "r",                   &m_secVtx_r               );
  connectBranch<float> ( name, tree, "pt",                  &m_secVtx_pt              );
  connectBranch<float> ( name, tree, "eta",                 &m_secVtx_eta             );
  connectBranch<float> ( name, tree, "phi",                 &m_secVtx_phi             );
  connectBranch<float> ( name, tree, "mass",                &m_secVtx_mass            );
  connectBranch<float> ( name, tree, "mass_nonAssoc",       &m_secVtx_massNA          );
  connectBranch<float> ( name, tree, "direction",           &m_secVtx_direction       );
  connectBranch<float> ( name, tree, "minOpAng",            &m_secVtx_minOpAng        );
  connectBranch<float> ( name, tree, "maxOpAng",            &m_secVtx_maxOpAng        );
  connectBranch<float> ( name, tree, "mind0",               &m_secVtx_mind0           );
  connectBranch<float> ( name, tree, "maxd0",               &m_secVtx_maxd0           );
  connectBranch<float> ( name, tree, "pt_clean",            &m_secVtx_pt_clean        );
  connectBranch<float> ( name, tree, "eta_clean",           &m_secVtx_eta_clean       );
  connectBranch<float> ( name, tree, "phi_clean",           &m_secVtx_phi_clean       );
  connectBranch<float> ( name, tree, "mass_clean",          &m_secVtx_mass_clean      );
  connectBranch<float> ( name, tree, "mass_nonAssoc_clean", &m_secVtx_massNA_clean    );
  connectBranch<float> ( name, tree, "direction_clean",     &m_secVtx_direction_clean );
  connectBranch<float> ( name, tree, "minOpAng_clean",      &m_secVtx_minOpAng_clean  );
  connectBranch<float> ( name, tree, "maxOpAng_clean",      &m_secVtx_maxOpAng_clean  );
  connectBranch<float> ( name, tree, "mind0_clean",         &m_secVtx_mind0_clean     );
  connectBranch<float> ( name, tree, "maxd0_clean",         &m_secVtx_maxd0_clean     );
  connectBranch<float> ( name, tree, "pt_bare",             &m_secVtx_pt_bare         );
  connectBranch<float> ( name, tree, "eta_bare",            &m_secVtx_eta_bare        );
  connectBranch<float> ( name, tree, "phi_bare",            &m_secVtx_phi_bare        );
  connectBranch<float> ( name, tree, "mass_bare",           &m_secVtx_mass_bare       );
  connectBranch<float> ( name, tree, "mass_nonAssoc_bare",  &m_secVtx_massNA_bare     );
  connectBranch<float> ( name, tree, "direction_bare",      &m_secVtx_direction_bare  );
  connectBranch<float> ( name, tree, "minOpAng_bare",       &m_secVtx_minOpAng_bare   );
  connectBranch<float> ( name, tree, "maxOpAng_bare",       &m_secVtx_maxOpAng_bare   );
  connectBranch<float> ( name, tree, "mind0_bare",          &m_secVtx_mind0_bare      );
  connectBranch<float> ( name, tree, "maxd0_bare",          &m_secVtx_maxd0_bare      );
  connectBranch<float> ( name, tree, "chi2",                &m_secVtx_chi2            );

  connectBranch<std::vector<float>> ( name, tree, "covariance", &m_secVtx_covariance );
  
  connectBranch<int> ( name, tree, "ntrk",       &m_secVtx_ntrk       );
  connectBranch<int> ( name, tree, "ntrk_clean", &m_secVtx_ntrk_clean );
  connectBranch<int> ( name, tree, "ntrk_filt",  &m_secVtx_ntrk_filt  );

  connectBranch<std::vector<int>>     ( name, tree, "trk_ID",           &m_secVtx_trk_ID       );
  connectBranch<std::vector<int>>     ( name, tree, "trk_index",        &m_secVtx_trk_index    );
  connectBranch<std::vector<float>>   ( name, tree, "trk_pt_wrtSV",     &m_secVtx_trk_pt_sv    );
  connectBranch<std::vector<float>>   ( name, tree, "trk_eta_wrtSV",    &m_secVtx_trk_eta_sv   );
  connectBranch<std::vector<float>>   ( name, tree, "trk_phi_wrtSV",    &m_secVtx_trk_phi_sv   );
  connectBranch<std::vector<float>>   ( name, tree, "trk_d0_wrtSV",     &m_secVtx_trk_d0_sv    );
  connectBranch<std::vector<float>>   ( name, tree, "trk_z0_wrtSV",     &m_secVtx_trk_z0_sv    );
  connectBranch<std::vector<float>>   ( name, tree, "trk_errd0_wrtSV",  &m_secVtx_trk_errd0_sv );
  connectBranch<std::vector<float>>   ( name, tree, "trk_errz0_wrtSV",  &m_secVtx_trk_errz0_sv );
  connectBranch<std::vector<float>>   ( name, tree, "trk_errP_wrtSV",   &m_secVtx_trk_errP_sv  );
  connectBranch<std::vector<float>>   ( name, tree, "trk_chi2_toSV",    &m_secVtx_trk_chi2_sv  );
  connectBranch<std::vector<uint8_t>> ( name, tree, "trk_isFinal",      &m_secVtx_trk_isFinal  );
  connectBranch<std::vector<uint8_t>> ( name, tree, "trk_isSelected",   &m_secVtx_trk_isSel    );
  connectBranch<std::vector<uint8_t>> ( name, tree, "trk_isAssociated", &m_secVtx_trk_isAssoc  );
  connectBranch<std::vector<uint8_t>> ( name, tree, "trk_isClean",      &m_secVtx_trk_isClean  );
  connectBranch<std::vector<uint8_t>> ( name, tree, "trk_isFiltered",   &m_secVtx_trk_isFilt   );

  if ( m_mc ) {
    connectBranch<int>                      ( name, tree, "matchedTruthVtx_n",                 &m_secVtx_truth_n     );
    connectBranch<std::vector<std::string>> ( name, tree, "matchedTruthVtx_llpDecay",          &m_secVtx_truth_llp   );
    connectBranch<std::vector<int>>         ( name, tree, "matchedTruthVtx_ID",                &m_secVtx_truth_ID    );
    connectBranch<std::vector<int>>         ( name, tree, "matchedTruthVtx_index",             &m_secVtx_truth_index );
    connectBranch<std::vector<float>>       ( name, tree, "matchedTruthVtx_distance",          &m_secVtx_truth_dist  );
    connectBranch<std::vector<float>>       ( name, tree, "matchedTruthVtx_matchScore",        &m_secVtx_truth_score );
    connectBranch<std::vector<int>>         ( name, tree, "matchedTruthVtx_reprPhysPos_ID",    &m_secVtx_truth_posID );
    connectBranch<std::vector<float>>       ( name, tree, "matchedTruthVtx_residual_distance", &m_secVtx_truth_resid );
  }

  connectBranch<uint8_t> ( name, tree, "is" + m_jetStr + "JetMatched", &m_secVtx_jetMatched     );
  connectBranch<int>     ( name, tree, m_jetStr + "JetMatch_ID",       &m_secVtx_jetMatch_ID    );
  connectBranch<int>     ( name, tree, m_jetStr + "JetMatch_index",    &m_secVtx_jetMatch_index );
  connectBranch<float>   ( name, tree, m_jetStr + "JetMatch_dR",       &m_secVtx_jetMatch_dR    );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthVerts ( TTree* tree, const std::string& truthVtxName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthVerts()", "connecting truth vertex branches" );

  std::string name = truthVtxName;

  using namespace EJsHelper;

  connectBranch<int> ( tree, "n" + name, &m_truthVtx_n );
  
  using namespace HelperFunctions;

  connectBranch<std::string> ( name, tree, "llpDecay", &m_truthVtx_llp   );
  connectBranch<int>         ( name, tree, "ID",       &m_truthVtx_ID    );
  connectBranch<int>         ( name, tree, "index",    &m_truthVtx_index );
  connectBranch<float>       ( name, tree, "x",        &m_truthVtx_x     );
  connectBranch<float>       ( name, tree, "y",        &m_truthVtx_y     );
  connectBranch<float>       ( name, tree, "z",        &m_truthVtx_z     );
  connectBranch<float>       ( name, tree, "r",        &m_truthVtx_r     );
  connectBranch<float>       ( name, tree, "pt",       &m_truthVtx_pt    );
  connectBranch<float>       ( name, tree, "eta",      &m_truthVtx_eta   );
  connectBranch<float>       ( name, tree, "phi",      &m_truthVtx_phi   );
  connectBranch<float>       ( name, tree, "mass",     &m_truthVtx_mass  );
  connectBranch<int>         ( name, tree, "nOutP",    &m_truthVtx_nOutP );

  connectBranch<int> ( name, tree, "parent_pdgId", &m_truthVtx_parent_pdgId );
  
  connectBranch<int> ( name, tree, "descendant_n",         &m_truthVtx_nDesc     );
  connectBranch<int> ( name, tree, "descendant_nReco",     &m_truthVtx_nRecoDesc );
  connectBranch<int> ( name, tree, "descendant_nSelected", &m_truthVtx_nSelDesc  );

  connectBranch<int> ( name, tree, "physPos_n", &m_truthVtx_nPos );

  connectBranch<int>                ( name, tree, "matchedRecoVtx_n",                 &m_truthVtx_reco_n     );
  connectBranch<std::vector<int>>   ( name, tree, "matchedRecoVtx_ID",                &m_truthVtx_reco_ID    );
  connectBranch<std::vector<int>>   ( name, tree, "matchedRecoVtx_index",             &m_truthVtx_reco_index );
  connectBranch<std::vector<float>> ( name, tree, "matchedRecoVtx_matchScore",        &m_truthVtx_reco_score );
  connectBranch<std::vector<int>>   ( name, tree, "matchedRecoVtx_reprTruthPosID",    &m_truthVtx_reco_posID );
  connectBranch<std::vector<float>> ( name, tree, "matchedRecoVtx_residual_distance", &m_truthVtx_reco_resid );
  
  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: initialize ( const std::string& outFileName, const std::vector<EJsHelper::Region>& regions,
					       const std::string& jetHistName )
{
  if ( m_debug ) Info( "EJsHistogramManager::initialize()", "booking histograms" );

  // set jet histo strings
  std::string hjetStr    = m_jetStr    + " jet";
  std::string hjetStrOth = m_jetStrOth + " jet";
  std::string hjet       = jetHistName;
  std::string htjet      = "truthJet";
  std::string hdjet      = "darkJet";

  // loop over regions + book histograms
  for ( size_t ireg = 0; ireg != regions.size(); ++ireg ) {
    const EJsHelper::Region region = regions.at(ireg);
    const std::string       name   = m_name + outFileName + "/" + region.name + "/";

    // initialize count vectors
    m_nTypeDVs                    .push_back( 0 );
    m_nEntries                    .push_back( 0 );
    if ( m_histoInfoSwitch->m_trigTest ) {
      m_nFourJets                 .push_back( 0 );
      m_nSearch                   .push_back( 0 );
      m_nTrig_4j120               .push_back( 0 );
      m_nOffTrig_4j120            .push_back( 0 );
      m_nOffTrig_4j120_other      .push_back( 0 );
      m_nOffTrigJVT_4j120         .push_back( 0 );
      m_nOffTrigJVT_4j120_other   .push_back( 0 );
      m_nTrig_fourJet             .push_back( 0 );
      m_nOffTrig_fourJet          .push_back( 0 );
      m_nOthOffTrig_fourJet       .push_back( 0 );
      m_nOffTrigJVT_fourJet       .push_back( 0 );
      m_nOthOffTrigJVT_fourJet    .push_back( 0 );
      m_nTrig_search              .push_back( 0 );
      m_nOffTrig_search           .push_back( 0 );
      m_nOthOffTrig_search        .push_back( 0 );
      m_nOffTrigJVT_search        .push_back( 0 );
      m_nOthOffTrigJVT_search     .push_back( 0 );
    }

    // set bins
    float njetht_xmin = 0;
    if      ( region.type == EJsHelper::SEARCH     ) njetht_xmin = 950;
    else if ( region.type == EJsHelper::VALIDATION ) njetht_xmin = 200;

    // --- METADATA --- //
    h_MetaData_EventCount .push_back( book( name, "MetaData_EventCount", "", 6, 1, 7 ) );
    h_MetaData_EventCount .at(ireg) ->GetXaxis()->SetBinLabel( 1, "nEvents initial"              );
    h_MetaData_EventCount .at(ireg) ->GetXaxis()->SetBinLabel( 2, "nEvents selected"             );
    h_MetaData_EventCount .at(ireg) ->GetXaxis()->SetBinLabel( 3, "sumOfWeights initial"         );
    h_MetaData_EventCount .at(ireg) ->GetXaxis()->SetBinLabel( 4, "sumOfWeights selected"        );
    h_MetaData_EventCount .at(ireg) ->GetXaxis()->SetBinLabel( 5, "sumOfWeightsSquared initial"  );
    h_MetaData_EventCount .at(ireg) ->GetXaxis()->SetBinLabel( 6, "sumOfWeightsSquared selected" );
    h_MetaData_Weights    .push_back( book( name, "MetaData_Weights", "", 4, 1, 5 ) );
    h_MetaData_Weights    .at(ireg) ->GetXaxis()->SetBinLabel( 1, "cross-section [fb]" );
    h_MetaData_Weights    .at(ireg) ->GetXaxis()->SetBinLabel( 2, "k-factor"           );
    h_MetaData_Weights    .at(ireg) ->GetXaxis()->SetBinLabel( 3, "gen-filter eff"     );
    h_MetaData_Weights    .at(ireg) ->GetXaxis()->SetBinLabel( 4, "lumi scale [ifb]"   ); // --> luminosity to scale to 
    
    // --- EVENT INFO --- //
    // event info: pileup
    if ( m_histoInfoSwitch->m_pileup ) {
      h_npv       .push_back( book( name, "nPV",       "n primary vertices",               50, 0,  50 ) );
      h_actualMu  .push_back( book( name, "actualMu",  "actual interactions / crossing",  100, 0, 100 ) );
      h_averageMu .push_back( book( name, "averageMu", "average interactions / crossing", 100, 0, 100 ) );
      
      h_corrActualMu
	.push_back( book( name, "corrActualMu",       "corrected actual interactions / crossing",           100, 0, 100 ) );
      h_corrAverageMu
	.push_back( book( name, "corrAverageMu",      "corrected average interactions / crossing",          100, 0, 100 ) );
      h_corrScaleActualMu
	.push_back( book( name, "corrScaleActualMu",  "corrected + scaled actual interactions / crossing",  100, 0, 100 ) );
      h_corrScaleAverageMu
	.push_back( book( name, "corrScaleAverageMu", "corrected + scaled average interactions / crossing", 100, 0, 100 ) );
    }
    // event info: primary vertex
    if ( m_histoInfoSwitch->m_pv ) {
      h_pv_x    .push_back( book( name, "pv_x",    "PV x-pos [mm]", 100, -1.5, 1.5 ) );
      h_pv_y    .push_back( book( name, "pv_y",    "PV y-pos [mm]", 100, -1.5, 1.5 ) );
      h_pv_z    .push_back( book( name, "pv_z",    "PV z-pos [mm]", 100, -150, 150 ) );
      h_pv_r    .push_back( book( name, "pv_r",    "PV r-pos [mm]", 100,    0, 1.5 ) );
      h_pv_phi  .push_back( book( name, "pv_phi",  "PV phi",        100, -3.5, 3.5 ) );
      h_pv_ntrk .push_back( book( name, "pv_nTrk", "n PV tracks",   100,    0, 250 ) );
    }
    // event info: leading N-jet Ht
    h_njetHt .push_back( book( name, "NJetHt", "leading N " + m_jetStr + " Jet H_{T} [GeV]", 100, njetht_xmin, 3500 ) );
    // --> use capital "Jet" for denoting NJet quantities

    
    // --- RECO JETS --- //
    // jets: basics / kinematics
    h_jet_n     .push_back( book( name, hjet + "_n",     "n " + hjetStr + "s",       20,    0,   20 ) );
    h_jet_pt    .push_back( book( name, hjet + "_pt",    hjetStr + " p_{T} [GeV]",  100,    0, 1500 ) );
    h_jet_pt_l  .push_back( book( name, hjet + "_pt_l",  hjetStr + " p_{T} [GeV]",  100,    0, 2500 ) );
    h_jet_pt_m  .push_back( book( name, hjet + "_pt_m",  hjetStr + " p_{T} [GeV]",  100,    0,  500 ) );
    h_jet_pt_s  .push_back( book( name, hjet + "_pt_s",  hjetStr + " p_{T} [GeV]",  100,    0,  200 ) );
    h_jet_eta   .push_back( book( name, hjet + "_eta",   hjetStr + " eta",          100,   -5,    5 ) );
    h_jet_phi   .push_back( book( name, hjet + "_phi",   hjetStr + " phi",          100, -3.5,  3.5 ) );
    h_jet_E     .push_back( book( name, hjet + "_E",     hjetStr + " energy [GeV]", 100,    0, 2500 ) );
    h_jet_M     .push_back( book( name, hjet + "_M",     hjetStr + " mass [GeV]",   100,    0,  250 ) );
    h_jet_rapid .push_back( book( name, hjet + "_rapid", hjetStr + " rapidity",     100,   -5,    5 ) );
    // jets: extra kinematics
    if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
      h_jet_px   .push_back( book( name, hjet + "_px",   hjetStr + " p_{x} [GeV]", 100, -1500, 1500 ) );
      h_jet_py   .push_back( book( name, hjet + "_py",   hjetStr + " p_{y} [GeV]", 100, -1500, 1500 ) );
      h_jet_pz   .push_back( book( name, hjet + "_pz",   hjetStr + " p_{z} [GeV]", 100, -2500, 2500 ) );
      h_jet_Et   .push_back( book( name, hjet + "_Et",   hjetStr + " E_{T} [GeV]", 100,     0, 1500 ) );
      h_jet_Et_m .push_back( book( name, hjet + "_Et_m", hjetStr + " E_{T} [GeV]", 100,     0,  500 ) );
      h_jet_Et_s .push_back( book( name, hjet + "_Et_s", hjetStr + " E_{T} [GeV]", 100,     0,  200 ) );
    }

    // jets: matched tracks
    h_jet_nTrk   .push_back( book( name, hjet + "_nTrk",   "n matched tracks per " + hjetStr,          100, 0, 200 ) );
    h_jet_trk_dR .push_back( book( name, hjet + "_trk_dR", "dR b/w " + hjetStr + " and matched track", 100, 0, 0.6 ) );
    // jets: matched tracks vs dR to jet center
    h_jet_nTrk_vs_dR
      .push_back( book( name, hjet + "_nTrk_vs_dR",
			"dR b/w " + hjetStr + " and matched track", 100, 0, 0.6, "nTrk", 100, 0, 200 ) );
    
    // jets: matched secondary vertices
    h_jet_nDV   .push_back( book( name, hjet + "_nDV",   "n matched DVs per " + hjetStr,           10, 0,  10 ) );
    h_jet_DV_dR .push_back( book( name, hjet + "_DV_dR", "dR b/w " + hjetStr + " and matched DV", 100, 0, 0.6 ) );
    // jets: matched seconadry vertices vs dR to jet center
    h_jet_nDV_vs_dR
      .push_back( book( name, hjet + "_nDV_vs_dR",
			"dR b/w " + hjetStr + " and matched DV", 100, 0, 0.6, "n matched DVs per " + hjetStr, 10, 0, 10 ) );
    
    // N leading jets
    if ( m_numLeadJets ) {
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
      std::vector<TH1F*> h_nlead_Et_m;
      std::vector<TH1F*> h_nlead_Et_s;
      for ( int i = 0; i != m_numLeadJets; ++i ) {
	std::string njet     = std::to_string(i);
	std::string hnjet    = hjet + njet;
	std::string hnjetStr = hjetStr + "-" + njet;
	h_nlead_pt    .push_back( book( name, hnjet + "_pt",    hnjetStr + " p_{T} [GeV]",  100,    0, 1500 ) );
	h_nlead_pt_l  .push_back( book( name, hnjet + "_pt_l",  hnjetStr + " p_{T} [GeV]",  100,    0, 2500 ) );
	h_nlead_pt_m  .push_back( book( name, hnjet + "_pt_m",  hnjetStr + " p_{T} [GeV]",  100,    0,  500 ) );
	h_nlead_pt_s  .push_back( book( name, hnjet + "_pt_s",  hnjetStr + " p_{T} [GeV]",  100,    0,  200 ) );
	h_nlead_eta   .push_back( book( name, hnjet + "_eta",   hnjetStr + " eta",          100,   -5,    5 ) );
	h_nlead_phi   .push_back( book( name, hnjet + "_phi",   hnjetStr + " phi",          100, -3.5,  3.5 ) );
	h_nlead_E     .push_back( book( name, hnjet + "_E",     hnjetStr + " energy [GeV]", 100,    0, 2500 ) );
	h_nlead_M     .push_back( book( name, hnjet + "_M",     hnjetStr + " mass [GeV]",   100,    0,  250 ) );
	h_nlead_rapid .push_back( book( name, hnjet + "_rapid", hnjetStr + " rapidity",     100,   -5,    5 ) );
	h_nlead_Et    .push_back( book( name, hnjet + "_Et",    hnjetStr + " E_{T} [GeV]",  100,    0, 1500 ) );
	h_nlead_Et_m  .push_back( book( name, hnjet + "_Et_m",  hnjetStr + " E_{T} [GeV]",  100,    0,  500 ) );
	h_nlead_Et_s  .push_back( book( name, hnjet + "_Et_s",  hnjetStr + " E_{T} [GeV]",  100,    0,  200 ) );
      }
      h_jetN_pt    .push_back( h_nlead_pt    );
      h_jetN_pt_l  .push_back( h_nlead_pt_l  );
      h_jetN_pt_m  .push_back( h_nlead_pt_m  );
      h_jetN_pt_s  .push_back( h_nlead_pt_s  );
      h_jetN_eta   .push_back( h_nlead_eta   );
      h_jetN_phi   .push_back( h_nlead_phi   );
      h_jetN_E     .push_back( h_nlead_E     );
      h_jetN_M     .push_back( h_nlead_M     );
      h_jetN_rapid .push_back( h_nlead_rapid );
      // N leading jets: extra kinematics
      if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	h_jetN_Et   .push_back( h_nlead_Et   );
	h_jetN_Et_m .push_back( h_nlead_Et_m );
	h_jetN_Et_s .push_back( h_nlead_Et_s );
      }
    }

    
    // --- TRACKS --- //
    // tracks: basics / kinematics
    h_trk_n .push_back( book( name, "trk_n", "n tracks", 100, 0, 10000 ) );


    // --- TRUTH VERTICES --- //
    if ( m_mc ) {
      // truth vertices: basics / kinematics
      h_truthVtx_n .push_back( book( name, "truthVtx_n", "n truth vertices", 125, 0, 250 ) );
      // truth vertices -- dark pion decays: basics / kinematics
      if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_darkPions ) {
	h_truthDarkPionDecay_n    .push_back( book( name, "truthDarkPionDecay_n",    "n truth dark pion decays",          125,     0,  125 ) );
	h_truthDarkPionDecay_x    .push_back( book( name, "truthDarkPionDecay_x",    "truth dark pion decay x-pos [mm]",  100,  -600,  600 ) );
	h_truthDarkPionDecay_y    .push_back( book( name, "truthDarkPionDecay_y",    "truth dark pion decay y-pos [mm]",  100,  -600,  600 ) );
	h_truthDarkPionDecay_z    .push_back( book( name, "truthDarkPionDecay_z",    "truth dark pion decay z-pos [mm]",  100, -3000, 3000 ) );
	h_truthDarkPionDecay_r    .push_back( book( name, "truthDarkPionDecay_r",    "truth dark pion decay r-pos [mm]",  100,     0,  600 ) );
	h_truthDarkPionDecay_pt   .push_back( book( name, "truthDarkPionDecay_pt",   "truth dark pion decay p_{T} [GeV]", 100,     0,  500 ) );
	h_truthDarkPionDecay_eta  .push_back( book( name, "truthDarkPionDecay_eta",  "truth dark pion decay eta",         100,   -10,   10 ) );
	h_truthDarkPionDecay_phi  .push_back( book( name, "truthDarkPionDecay_phi",  "truth dark pion decay phi",         100,  -3.5,  3.5 ) );
	h_truthDarkPionDecay_mass .push_back( book( name, "truthDarkPionDecay_mass", "truth dark pion decay mass [GeV]",  125,     0,   25 ) );
	
	h_truthDarkPionDecay_nOutP
	  .push_back( book( name, "truthDarkPionDecay_nOutP", "n truth dark pion decay outgoing particles", 5, 0, 5 ) );

	h_truthDarkPionDecay_nDesc
	  .push_back( book( name, "truthDarkPionDecay_nDesc",     "n truth dark pion decay reconstructible descendants", 10, 0, 10 ) );
	h_truthDarkPionDecay_nRecoDesc
	  .push_back( book( name, "truthDarkPionDecay_nRecoDesc", "n truth dark pion decay reconstructed descendants",   10, 0, 10 ) );
	h_truthDarkPionDecay_nSelDesc
	  .push_back( book( name, "truthDarkPionDecay_nSelDesc",  "n truth dark pion decay selected descendants",        10, 0, 10 ) );

	h_truthDarkPionDecay_nPos
	  .push_back( book( name, "truthDarkPionDecay_nPos", "n truth dark pion decay physical positions", 5, 0, 5 ) );
      }
      // truth vertices -- k-short decays: basics / kinematics
      if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_kshorts ) {
	h_truthKshortDecay_n    .push_back( book( name, "truthKshortDecay_n",    "n truth k-short decays",           10,     0,   10 ) );
	h_truthKshortDecay_x    .push_back( book( name, "truthKshortDecay_x",    "truth k-short decay x-pos [mm]",  100,  -600,  600 ) );
	h_truthKshortDecay_y    .push_back( book( name, "truthKshortDecay_y",    "truth k-short decay y-pos [mm]",  100,  -600,  600 ) );
	h_truthKshortDecay_z    .push_back( book( name, "truthKshortDecay_z",    "truth k-short decay z-pos [mm]",  100, -3000, 3000 ) );
	h_truthKshortDecay_r    .push_back( book( name, "truthKshortDecay_r",    "truth k-short decay r-pos [mm]",  100,     0,  600 ) );
	h_truthKshortDecay_pt   .push_back( book( name, "truthKshortDecay_pt",   "truth k-short decay p_{T} [GeV]", 100,     0,  200 ) );
	h_truthKshortDecay_eta  .push_back( book( name, "truthKshortDecay_eta",  "truth k-short decay eta",         100,    -8,    8 ) );
	h_truthKshortDecay_phi  .push_back( book( name, "truthKshortDecay_phi",  "truth k-short decay phi",         100,  -3.5,  3.5 ) );
	h_truthKshortDecay_mass .push_back( book( name, "truthKshortDecay_mass", "truth k-short decay mass [GeV]",  100,     0,    1 ) );

	h_truthKshortDecay_nOutP
	  .push_back( book( name, "truthKshortDecay_nOutP", "n truth k-short decay outgoing particles", 5, 0, 5 ) );

	h_truthKshortDecay_nDesc
	  .push_back( book( name, "truthKshortDecay_nDesc",     "n truth k-short decay reconstructible descendants", 10, 0, 10 ) );
	h_truthKshortDecay_nRecoDesc
	  .push_back( book( name, "truthKshortDecay_nRecoDesc", "n truth k-short decay reconstructed descendants",   10, 0, 10 ) );
	h_truthKshortDecay_nSelDesc
	  .push_back( book( name, "truthKshortDecay_nSelDesc",  "n truth k-short decay selected descendants",        10, 0, 10 ) );

	h_truthKshortDecay_nPos
	  .push_back( book( name, "truthKshortDecay_nPos", "n truth k-short decay physical positions", 5, 0, 5 ) );
      }
    }


    // --- SECONDARY VERTICES -- //
    // // vertices: basics / kinematics
    // h_DV_n .push_back( book( name, "DV_n", "n secondary vertices", 15, 0, 15 ) );
    // // vertices nearby to (lead) jets
    // h_byJetDV_n     .push_back( book( name, "byJetDV_n",     "n DVs w/in dR=0.6 of "           + m_jetStr + " jets", 12, 0, 12 ) );
    // h_byLeadJetDV_n .push_back( book( name, "byLeadJetDV_n", "n DVs w/in dR=0.6 of N leading " + m_jetStr + " jets", 10, 0, 10 ) );

    std::vector<std::string> hDV;
    std::vector<std::string> hDVstr;

    // fix k-short mass window removal --> try one at a time (don't add to dark pions yet)
    // --> make sure to initialize all new vertex types (set counters)
    // add clean+final, track trim matched (ie. clean dark pions, filtered dark pions), combined (i.e. fiducial + ksm), other cuts (i.e. mind0)
    // add config switch to turn off all histograms but counters (to turn "doHists" on or off)
    // fix abcd plotting / calculation -- add separate calc python script for counting, estimating, scaled estimating, etc.
    // add efficiency plots / calculations (to / as supplement to python plotting script)
    
    
    // bare vertices (at least two tracks)
    std::string bDV    = "bare";
    std::string bDVstr = "bare ";
    if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_bareVerts ) {
      hDV    .push_back( bDV    + "DV" );
      hDVstr .push_back( bDVstr + "DV" );
      ++m_nTypeDVs.at(ireg);
    }
    // clean vertices (at least two CLEAN tracks)
    std::string cDV    = "clean";
    std::string cDVstr = "clean ";
    if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_cleanVerts ) {
      hDV    .push_back( cDV    + "DV" );
      hDVstr .push_back( cDVstr + "DV" );
      ++m_nTypeDVs.at(ireg);
    }
    // filtered vertices (at least two FILTERED tracks)
    std::string fDV    = "filt";
    std::string fDVstr = "filtered ";
    if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_filtVerts ) {
      hDV    .push_back( fDV    + "DV" );
      hDVstr .push_back( fDVstr + "DV" );
      ++m_nTypeDVs.at(ireg);
    }
    // --> add other track filtering tests
    // vertices by (leading) jets
    std::string jDV     = "byJet";
    std::string ljDV    = "byLeadJet";
    std::string jDVstr  = "by-jet ";
    std::string ljDVstr = "by-lead-jet ";
    if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_byJetVerts ) {
      hDV    .push_back( jDV     + "DV" );
      hDV    .push_back( ljDV    + "DV" );
      hDVstr .push_back( jDVstr  + "DV" );
      hDVstr .push_back( ljDVstr + "DV" );
      ++m_nTypeDVs.at(ireg);
      ++m_nTypeDVs.at(ireg);
    }
    // vertices passing fiducial cuts (fiducial volume, chi2)
    std::string fidDV    = "fiducial";
    std::string fidDVstr = "fiducial-cut ";
    if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_fiducialVerts ) {
      hDV    .push_back( fidDV    + "DV" );
      hDVstr .push_back( fidDVstr + "DV" );
      ++m_nTypeDVs.at(ireg);
    }
    // // vertices w/ k-short mass window removed (loose = 2-track bare mass b/w 450-550 MeV; tight = bare mass above 550 MeV)
    // std::string ksmlDV    = "ksmLoose";
    // std::string ksmlDVstr = "ksm-loose-cut ";
    // if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_ksmVerts ) {
    //   hDV    .push_back( ksmlDV    + "DV" );
    //   hDVstr .push_back( ksmlDVstr + "DV" );
    //   ++m_nTypeDVs.at(ireg);
    // }
    // truth-matched vertices (testing matching criteria)
    // --> matching criteria:
    // --> --> v0 = match score > 0; no requirement on number / type of truth matches (may be matched to both multiple llps)
    // --> add other versions of matching criteria; add clean/filtered truth-matched DVs ...
    if ( m_mc && m_histoInfoSwitch->m_vtxTruth ) {
      std::vector<std::string> mDV     = { "darkPionDV",   "kshortDV",    "nomatchDV"    };
      std::vector<std::string> mDVstr  = { "dark pion DV", "k-short DV",  "unmatched DV" };
      std::vector<std::string> miDV    = { jDV,    ljDV,    fidDV    };
      std::vector<std::string> miDVstr = { jDVstr, ljDVstr, fidDVstr };
      for ( size_t i = 0; i != mDV.size(); ++i ) {
	hDV    .push_back( mDV    .at(i) );
	hDVstr .push_back( mDVstr .at(i) );
	++m_nTypeDVs.at(ireg);
	for ( size_t j = 0; j != miDV.size(); ++j ) {
	  std::string mDVs = mDV.at(i); mDVs[0] = toupper(mDVs[0]);
	  hDV    .push_back( miDV    .at(j) +       mDVs         );
	  hDVstr .push_back( miDVstr .at(j) + " " + mDVstr.at(i) );
	  ++m_nTypeDVs.at(ireg);
	}
      }
    }

    std::vector<TH1F*> h_dv_n;
    std::vector<TH1F*> h_dv_x;
    std::vector<TH1F*> h_dv_y;
    std::vector<TH1F*> h_dv_z;
    std::vector<TH1F*> h_dv_r;
    std::vector<TH1F*> h_dv_x_s;
    std::vector<TH1F*> h_dv_y_s;
    std::vector<TH1F*> h_dv_z_s;
    std::vector<TH1F*> h_dv_r_s;
    std::vector<TH1F*> h_dv_phipos;
    std::vector<TH1F*> h_dv_pt;
    std::vector<TH1F*> h_dv_eta;
    std::vector<TH1F*> h_dv_phi;
    std::vector<TH1F*> h_dv_mass;
    std::vector<TH1F*> h_dv_mass_l;
    std::vector<TH1F*> h_dv_mass_s;
    std::vector<TH1F*> h_dv_mass_xs;
    std::vector<TH1F*> h_dv_massNA;
    std::vector<TH1F*> h_dv_massNA_l;
    std::vector<TH1F*> h_dv_massNA_s;
    std::vector<TH1F*> h_dv_massNA_xs;
    std::vector<TH1F*> h_dv_direction;
    std::vector<TH1F*> h_dv_minOpAng;
    std::vector<TH1F*> h_dv_maxOpAng;
    std::vector<TH1F*> h_dv_chi2;
    std::vector<TH1F*> h_dv_chi2_s;
    std::vector<TH1F*> h_dv_ntrk;
    std::vector<TH1F*> h_dv_ntrk_final;
    std::vector<TH1F*> h_dv_ntrk_sel;
    std::vector<TH1F*> h_dv_ntrk_assoc;
    std::vector<TH1F*> h_dv_ntrk_lrt;
    std::vector<TH1F*> h_dv_errx;
    std::vector<TH1F*> h_dv_erry;
    std::vector<TH1F*> h_dv_errz;
    std::vector<TH1F*> h_dv_errr;
    std::vector<TH1F*> h_dv_errphi;
    std::vector<TH1F*> h_dv_sqrterrx;
    std::vector<TH1F*> h_dv_sqrterry;
    std::vector<TH1F*> h_dv_sqrterrz;
    std::vector<TH1F*> h_dv_sqrterrr;
    std::vector<TH1F*> h_dv_sqrterrphi;
    std::vector<TH1F*> h_dv_fracerrx;
    std::vector<TH1F*> h_dv_fracerry;
    std::vector<TH1F*> h_dv_fracerrz;
    std::vector<TH1F*> h_dv_fracerrr;
    std::vector<TH1F*> h_dv_fracerrphi;
    std::vector<TH1F*> h_dv_signifx;
    std::vector<TH1F*> h_dv_signify;
    std::vector<TH1F*> h_dv_signifz;
    std::vector<TH1F*> h_dv_signifr;
    std::vector<TH1F*> h_dv_signifphi;
    std::vector<TH1F*> h_dv_trk_qOverP;
    std::vector<TH1F*> h_dv_trk_theta;
    std::vector<TH1F*> h_dv_trk_pt;
    std::vector<TH1F*> h_dv_trk_eta;
    std::vector<TH1F*> h_dv_trk_phi;
    std::vector<TH1F*> h_dv_trk_d0;
    std::vector<TH1F*> h_dv_trk_z0;
    std::vector<TH1F*> h_dv_trk_errd0;
    std::vector<TH1F*> h_dv_trk_errz0;
    std::vector<TH1F*> h_dv_trk_sqrterrd0;
    std::vector<TH1F*> h_dv_trk_sqrterrz0;
    std::vector<TH1F*> h_dv_trk_fracerrd0;
    std::vector<TH1F*> h_dv_trk_fracerrz0;
    std::vector<TH1F*> h_dv_trk_signifd0;
    std::vector<TH1F*> h_dv_trk_signifz0;
    std::vector<TH1F*> h_dv_trk_errP;
    std::vector<TH1F*> h_dv_trk_sqrterrP;
    std::vector<TH1F*> h_dv_trk_fracerrP;
    std::vector<TH1F*> h_dv_trk_signifP;
    std::vector<TH1F*> h_dv_trk_chi2;
    std::vector<TH1F*> h_dv_trk_chiSq;
    std::vector<TH1F*> h_dv_trk_qOverP_sv;
    std::vector<TH1F*> h_dv_trk_theta_sv;
    std::vector<TH1F*> h_dv_trk_pt_sv;
    std::vector<TH1F*> h_dv_trk_eta_sv;
    std::vector<TH1F*> h_dv_trk_phi_sv;
    std::vector<TH1F*> h_dv_trk_d0_sv;
    std::vector<TH1F*> h_dv_trk_z0_sv;
    std::vector<TH1F*> h_dv_trk_errd0_sv;
    std::vector<TH1F*> h_dv_trk_errz0_sv;
    std::vector<TH1F*> h_dv_trk_sqrterrd0_sv;
    std::vector<TH1F*> h_dv_trk_sqrterrz0_sv;
    std::vector<TH1F*> h_dv_trk_fracerrd0_sv;
    std::vector<TH1F*> h_dv_trk_fracerrz0_sv;
    std::vector<TH1F*> h_dv_trk_signifd0_sv;
    std::vector<TH1F*> h_dv_trk_signifz0_sv;
    std::vector<TH1F*> h_dv_trk_errP_sv;
    std::vector<TH1F*> h_dv_trk_sqrterrP_sv;
    std::vector<TH1F*> h_dv_trk_fracerrP_sv;
    std::vector<TH1F*> h_dv_trk_signifP_sv;
    std::vector<TH1F*> h_dv_trk_chi2_sv;
    std::vector<TH1F*> h_dv_trk_chiSq_sv;
    std::vector<TH1F*> h_dv_sumd0;
    std::vector<TH1F*> h_dv_sumz0;
    std::vector<TH1F*> h_dv_sumP;
    std::vector<TH1F*> h_dv_sumErrd0;
    std::vector<TH1F*> h_dv_sumErrz0;
    std::vector<TH1F*> h_dv_sumErrP;
    std::vector<TH1F*> h_dv_sumSqrterrd0;
    std::vector<TH1F*> h_dv_sumSqrterrz0;
    std::vector<TH1F*> h_dv_sumSqrterrP;
    std::vector<TH1F*> h_dv_sumFracerrd0;
    std::vector<TH1F*> h_dv_sumFracerrz0;
    std::vector<TH1F*> h_dv_sumFracerrP;
    std::vector<TH1F*> h_dv_sumSignifd0;
    std::vector<TH1F*> h_dv_sumSignifz0;
    std::vector<TH1F*> h_dv_sumSignifP;
    std::vector<TH1F*> h_dv_sumd0_sv;
    std::vector<TH1F*> h_dv_sumz0_sv;
    std::vector<TH1F*> h_dv_sumP_sv;
    std::vector<TH1F*> h_dv_sumErrd0_sv;
    std::vector<TH1F*> h_dv_sumErrz0_sv;
    std::vector<TH1F*> h_dv_sumErrP_sv;
    std::vector<TH1F*> h_dv_sumSqrterrd0_sv;
    std::vector<TH1F*> h_dv_sumSqrterrz0_sv;
    std::vector<TH1F*> h_dv_sumSqrterrP_sv;
    std::vector<TH1F*> h_dv_sumFracerrd0_sv;
    std::vector<TH1F*> h_dv_sumFracerrz0_sv;
    std::vector<TH1F*> h_dv_sumFracerrP_sv;
    std::vector<TH1F*> h_dv_sumSignifd0_sv;
    std::vector<TH1F*> h_dv_sumSignifz0_sv;
    std::vector<TH1F*> h_dv_sumSignifP_sv;
    std::vector<TH1F*> h_dv_mind0;
    std::vector<TH1F*> h_dv_minz0;
    std::vector<TH1F*> h_dv_minP;
    std::vector<TH1F*> h_dv_minErrd0;
    std::vector<TH1F*> h_dv_minErrz0;
    std::vector<TH1F*> h_dv_minErrP;
    std::vector<TH1F*> h_dv_minSqrterrd0;
    std::vector<TH1F*> h_dv_minSqrterrz0;
    std::vector<TH1F*> h_dv_minSqrterrP;
    std::vector<TH1F*> h_dv_minFracerrd0;
    std::vector<TH1F*> h_dv_minFracerrz0;
    std::vector<TH1F*> h_dv_minFracerrP;
    std::vector<TH1F*> h_dv_minSignifd0;
    std::vector<TH1F*> h_dv_minSignifz0;
    std::vector<TH1F*> h_dv_minSignifP;
    std::vector<TH1F*> h_dv_mind0_sv;
    std::vector<TH1F*> h_dv_minz0_sv;
    std::vector<TH1F*> h_dv_minP_sv;
    std::vector<TH1F*> h_dv_minErrd0_sv;
    std::vector<TH1F*> h_dv_minErrz0_sv;
    std::vector<TH1F*> h_dv_minErrP_sv;
    std::vector<TH1F*> h_dv_minSqrterrd0_sv;
    std::vector<TH1F*> h_dv_minSqrterrz0_sv;
    std::vector<TH1F*> h_dv_minSqrterrP_sv;
    std::vector<TH1F*> h_dv_minFracerrd0_sv;
    std::vector<TH1F*> h_dv_minFracerrz0_sv;
    std::vector<TH1F*> h_dv_minFracerrP_sv;
    std::vector<TH1F*> h_dv_minSignifd0_sv;
    std::vector<TH1F*> h_dv_minSignifz0_sv;
    std::vector<TH1F*> h_dv_minSignifP_sv;
    std::vector<TH1F*> h_dv_maxd0;
    std::vector<TH1F*> h_dv_maxz0;
    std::vector<TH1F*> h_dv_maxP;
    std::vector<TH1F*> h_dv_maxErrd0;
    std::vector<TH1F*> h_dv_maxErrz0;
    std::vector<TH1F*> h_dv_maxErrP;
    std::vector<TH1F*> h_dv_maxSqrterrd0;
    std::vector<TH1F*> h_dv_maxSqrterrz0;
    std::vector<TH1F*> h_dv_maxSqrterrP;
    std::vector<TH1F*> h_dv_maxFracerrd0;
    std::vector<TH1F*> h_dv_maxFracerrz0;
    std::vector<TH1F*> h_dv_maxFracerrP;
    std::vector<TH1F*> h_dv_maxSignifd0;
    std::vector<TH1F*> h_dv_maxSignifz0;
    std::vector<TH1F*> h_dv_maxSignifP;
    std::vector<TH1F*> h_dv_maxd0_sv;
    std::vector<TH1F*> h_dv_maxz0_sv;
    std::vector<TH1F*> h_dv_maxP_sv;
    std::vector<TH1F*> h_dv_maxErrd0_sv;
    std::vector<TH1F*> h_dv_maxErrz0_sv;
    std::vector<TH1F*> h_dv_maxErrP_sv;
    std::vector<TH1F*> h_dv_maxSqrterrd0_sv;
    std::vector<TH1F*> h_dv_maxSqrterrz0_sv;
    std::vector<TH1F*> h_dv_maxSqrterrP_sv;
    std::vector<TH1F*> h_dv_maxFracerrd0_sv;
    std::vector<TH1F*> h_dv_maxFracerrz0_sv;
    std::vector<TH1F*> h_dv_maxFracerrP_sv;
    std::vector<TH1F*> h_dv_maxSignifd0_sv;
    std::vector<TH1F*> h_dv_maxSignifz0_sv;
    std::vector<TH1F*> h_dv_maxSignifP_sv;
    std::vector<TH2F*> h_dv_z_r;
    std::vector<TH2F*> h_dv_mass_r;
    std::vector<TH2F*> h_dv_z_chi2;
    std::vector<TH2F*> h_dv_r_chi2;
    std::vector<TH2F*> h_dv_mass_chi2;
    std::vector<TH2F*> h_dv_z_r_s;
    std::vector<TH2F*> h_dv_mass_r_s;
    std::vector<TH2F*> h_dv_z_chi2_s;
    std::vector<TH2F*> h_dv_r_chi2_s;
    std::vector<TH2F*> h_dv_mass_chi2_s;
    std::vector<TH2F*> h_dv_errx_x;
    std::vector<TH2F*> h_dv_erry_y;
    std::vector<TH2F*> h_dv_errz_z;
    std::vector<TH2F*> h_dv_errr_r;
    std::vector<TH2F*> h_dv_errphi_phi;
    std::vector<TH2F*> h_dv_sqrterrx_x;
    std::vector<TH2F*> h_dv_sqrterry_y;
    std::vector<TH2F*> h_dv_sqrterrz_z;
    std::vector<TH2F*> h_dv_sqrterrr_r;
    std::vector<TH2F*> h_dv_sqrterrphi_phi;
    std::vector<TH2F*> h_dv_sumErrd0_r;
    std::vector<TH2F*> h_dv_sumErrz0_z;
    std::vector<TH2F*> h_dv_sumErrP_pt;
    std::vector<TH2F*> h_dv_sumSqrterrd0_r;
    std::vector<TH2F*> h_dv_sumSqrterrz0_z;
    std::vector<TH2F*> h_dv_sumSqrterrP_pt;
    std::vector<TH2F*> h_dv_sumErrd0sv_r;
    std::vector<TH2F*> h_dv_sumErrz0sv_z;
    std::vector<TH2F*> h_dv_sumErrPsv_pt;
    std::vector<TH2F*> h_dv_sumSqrterrd0sv_r;
    std::vector<TH2F*> h_dv_sumSqrterrz0sv_z;
    std::vector<TH2F*> h_dv_sumSqrterrPsv_pt;
    std::vector<TH2F*> h_dv_minErrd0_r;
    std::vector<TH2F*> h_dv_minErrz0_z;
    std::vector<TH2F*> h_dv_minErrP_pt;
    std::vector<TH2F*> h_dv_minSqrterrd0_r;
    std::vector<TH2F*> h_dv_minSqrterrz0_z;
    std::vector<TH2F*> h_dv_minSqrterrP_pt;
    std::vector<TH2F*> h_dv_minErrd0sv_r;
    std::vector<TH2F*> h_dv_minErrz0sv_z;
    std::vector<TH2F*> h_dv_minErrPsv_pt;
    std::vector<TH2F*> h_dv_minSqrterrd0sv_r;
    std::vector<TH2F*> h_dv_minSqrterrz0sv_z;
    std::vector<TH2F*> h_dv_minSqrterrPsv_pt;
    std::vector<TH2F*> h_dv_maxErrd0_r;
    std::vector<TH2F*> h_dv_maxErrz0_z;
    std::vector<TH2F*> h_dv_maxErrP_pt;
    std::vector<TH2F*> h_dv_maxSqrterrd0_r;
    std::vector<TH2F*> h_dv_maxSqrterrz0_z;
    std::vector<TH2F*> h_dv_maxSqrterrP_pt;
    std::vector<TH2F*> h_dv_maxErrd0sv_r;
    std::vector<TH2F*> h_dv_maxErrz0sv_z;
    std::vector<TH2F*> h_dv_maxErrPsv_pt;
    std::vector<TH2F*> h_dv_maxSqrterrd0sv_r;
    std::vector<TH2F*> h_dv_maxSqrterrz0sv_z;
    std::vector<TH2F*> h_dv_maxSqrterrPsv_pt;
    std::vector<TH2F*> h_dv_trkd0_r;
    std::vector<TH2F*> h_dv_trkz0_z;
    std::vector<TH2F*> h_dv_trkP_pt;
    std::vector<TH2F*> h_dv_trkErrd0_r;
    std::vector<TH2F*> h_dv_trkErrz0_z;
    std::vector<TH2F*> h_dv_trkErrP_pt;
    std::vector<TH2F*> h_dv_trkSqrterrd0_r;
    std::vector<TH2F*> h_dv_trkSqrterrz0_z;
    std::vector<TH2F*> h_dv_trkSqrterrP_pt;
    std::vector<TH2F*> h_dv_trkd0sv_r;
    std::vector<TH2F*> h_dv_trkz0sv_z;
    std::vector<TH2F*> h_dv_trkPsv_pt;
    std::vector<TH2F*> h_dv_trkErrd0sv_r;
    std::vector<TH2F*> h_dv_trkErrz0sv_z;
    std::vector<TH2F*> h_dv_trkErrPsv_pt;
    std::vector<TH2F*> h_dv_trkSqrterrd0sv_r;
    std::vector<TH2F*> h_dv_trkSqrterrz0sv_z;
    std::vector<TH2F*> h_dv_trkSqrterrPsv_pt;
    std::vector<TH2F*> h_dv_trkErrd0_trkd0;
    std::vector<TH2F*> h_dv_trkErrz0_trkz0;
    std::vector<TH2F*> h_dv_trkErrP_trkP;
    std::vector<TH2F*> h_dv_trkSqrterrd0_trkd0;
    std::vector<TH2F*> h_dv_trkSqrterrz0_trkz0;
    std::vector<TH2F*> h_dv_trkSqrterrP_trkP;
    std::vector<TH2F*> h_dv_trkErrd0sv_trkd0sv;
    std::vector<TH2F*> h_dv_trkErrz0sv_trkz0sv;
    std::vector<TH2F*> h_dv_trkErrPsv_trkPsv;
    std::vector<TH2F*> h_dv_trkSqrterrd0sv_trkd0sv;
    std::vector<TH2F*> h_dv_trkSqrterrz0sv_trkz0sv;
    std::vector<TH2F*> h_dv_trkSqrterrPsv_trkPsv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_n;
    std::vector<std::vector<TH1F*>> h_ntrkdv_z;
    std::vector<std::vector<TH1F*>> h_ntrkdv_z_s;
    std::vector<std::vector<TH1F*>> h_ntrkdv_r;
    std::vector<std::vector<TH1F*>> h_ntrkdv_r_s;
    std::vector<std::vector<TH1F*>> h_ntrkdv_mass;
    std::vector<std::vector<TH1F*>> h_ntrkdv_mass_s;
    std::vector<std::vector<TH1F*>> h_ntrkdv_direction;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minOpAng;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxOpAng;
    std::vector<std::vector<TH1F*>> h_ntrkdv_chi2;
    std::vector<std::vector<TH1F*>> h_ntrkdv_chi2_s;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sqrterrx;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sqrterry;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sqrterrz;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sqrterrr;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sqrterrphi;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumSqrterrd0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumSqrterrz0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumSqrterrP;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumSqrterrd0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumSqrterrz0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumSqrterrP_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minSqrterrd0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minSqrterrz0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minSqrterrP;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minSqrterrd0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minSqrterrz0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minSqrterrP_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxSqrterrd0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxSqrterrz0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxSqrterrP;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxSqrterrd0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxSqrterrz0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxSqrterrP_sv;
    for ( size_t i = 0; i != hDV.size(); ++i ) {
      // vertex basics
      h_dv_n          .push_back( book( name, hDV.at(i) + "_n",          "n " + hDVstr.at(i) + "s",                   15,    0,  15 ) );
      h_dv_x          .push_back( book( name, hDV.at(i) + "_x",          hDVstr.at(i) + " x-pos [mm]",               100, -400,  400 ) );
      h_dv_y          .push_back( book( name, hDV.at(i) + "_y",          hDVstr.at(i) + " y-pos [mm]",               100, -400,  400 ) );
      h_dv_z          .push_back( book( name, hDV.at(i) + "_z",          hDVstr.at(i) + " z-pos [mm]",               100, -800,  800 ) );
      h_dv_r          .push_back( book( name, hDV.at(i) + "_r",          hDVstr.at(i) + " r-pos [mm]",               100,    0,  400 ) );
      h_dv_x_s        .push_back( book( name, hDV.at(i) + "_x_s",        hDVstr.at(i) + " x-pos [mm]",               100, -300,  300 ) );
      h_dv_y_s        .push_back( book( name, hDV.at(i) + "_y_s",        hDVstr.at(i) + " y-pos [mm]",               100, -300,  300 ) );
      h_dv_z_s        .push_back( book( name, hDV.at(i) + "_z_s",        hDVstr.at(i) + " z-pos [mm]",               100, -300,  300 ) );
      h_dv_r_s        .push_back( book( name, hDV.at(i) + "_r_s",        hDVstr.at(i) + " r-pos [mm]",               100,    0,  300 ) );
      h_dv_phipos     .push_back( book( name, hDV.at(i) + "_phipos",     hDVstr.at(i) + " phi-pos",                  100, -3.5,  3.5 ) );
      h_dv_pt         .push_back( book( name, hDV.at(i) + "_pt",         hDVstr.at(i) + " p_{T} [GeV]",              100,    0,  100 ) );
      h_dv_eta        .push_back( book( name, hDV.at(i) + "_eta",        hDVstr.at(i) + " eta",                      100,   -5,    5 ) );
      h_dv_phi        .push_back( book( name, hDV.at(i) + "_phi",        hDVstr.at(i) + " phi",                      100, -3.5,  3.5 ) );
      h_dv_mass       .push_back( book( name, hDV.at(i) + "_mass",       hDVstr.at(i) + " mass [GeV]",               100,    0,   50 ) );
      h_dv_mass_l     .push_back( book( name, hDV.at(i) + "_mass_l",     hDVstr.at(i) + " mass [GeV]",               100,    0,  100 ) );
      h_dv_mass_s     .push_back( book( name, hDV.at(i) + "_mass_s",     hDVstr.at(i) + " mass [GeV]",               100,    0,   25 ) );
      h_dv_mass_xs    .push_back( book( name, hDV.at(i) + "_mass_xs",    hDVstr.at(i) + " mass [GeV]",               100,    0,    5 ) );
      h_dv_massNA     .push_back( book( name, hDV.at(i) + "_massNA",     hDVstr.at(i) + " non-assoc. mass [GeV]",    100,    0,   50 ) );
      h_dv_massNA_l   .push_back( book( name, hDV.at(i) + "_massNA_l",   hDVstr.at(i) + " non-assoc. mass [GeV]",    100,    0,  100 ) );
      h_dv_massNA_s   .push_back( book( name, hDV.at(i) + "_massNA_s",   hDVstr.at(i) + " non-assoc. mass [GeV]",    100,    0,   25 ) );
      h_dv_massNA_xs  .push_back( book( name, hDV.at(i) + "_massNA_xs",  hDVstr.at(i) + " non-assoc. mass [GeV]",    100,    0,    5 ) );
      h_dv_direction  .push_back( book( name, hDV.at(i) + "_direction",  hDVstr.at(i) + " direction",                100, -1.1,  1.1 ) );
      h_dv_minOpAng   .push_back( book( name, hDV.at(i) + "_minOpAng",   hDVstr.at(i) + " cos min opening angle",    100, -1.1,  1.1 ) );
      h_dv_maxOpAng   .push_back( book( name, hDV.at(i) + "_maxOpAng",   hDVstr.at(i) + " cos max opening angle",    100, -1.1,  1.1 ) );
      h_dv_chi2       .push_back( book( name, hDV.at(i) + "_chi2",       hDVstr.at(i) + " chi2 / nDoF",              100,    0,   10 ) );
      h_dv_chi2_s     .push_back( book( name, hDV.at(i) + "_chi2_s",     hDVstr.at(i) + " chi2 / nDoF",              100,    0,    5 ) );
      h_dv_ntrk       .push_back( book( name, hDV.at(i) + "_ntrk",       "n " + hDVstr.at(i) + " tracks",             10,    2,   12 ) );
      h_dv_ntrk_final .push_back( book( name, hDV.at(i) + "_ntrk_final", "n " + hDVstr.at(i) + " final tracks",       10,    2,   12 ) );
      h_dv_ntrk_sel   .push_back( book( name, hDV.at(i) + "_ntrk_sel",   "n " + hDVstr.at(i) + " selected tracks",    10,    2,   12 ) );
      h_dv_ntrk_assoc .push_back( book( name, hDV.at(i) + "_ntrk_assoc", "n " + hDVstr.at(i) + " associated tracks",  10,    2,   12 ) );
      h_dv_ntrk_lrt   .push_back( book( name, hDV.at(i) + "_ntrk_lrt",   "n " + hDVstr.at(i) + " large-radius tracks",10,    2,   12 ) );
      h_dv_errx       .push_back( book( name, hDV.at(i) + "_errx",       hDVstr.at(i) + " x-pos uncert.",            100,    0,   25 ) );
      h_dv_erry       .push_back( book( name, hDV.at(i) + "_erry",       hDVstr.at(i) + " y-pos uncert.",            100,    0,   25 ) );
      h_dv_errz       .push_back( book( name, hDV.at(i) + "_errz",       hDVstr.at(i) + " z-pos uncert.",            100,    0,   25 ) );
      h_dv_errr       .push_back( book( name, hDV.at(i) + "_errr",       hDVstr.at(i) + " r-pos uncert.",            100,    0,   25 ) );
      h_dv_errphi     .push_back( book( name, hDV.at(i) + "_errphi",     hDVstr.at(i) + " phi uncert.",              100,    0, 0.15 ) );
      h_dv_sqrterrx   .push_back( book( name, hDV.at(i) + "_sqrterrx",   hDVstr.at(i) + " x-pos sqrt-uncert.",       100,    0,    5 ) );
      h_dv_sqrterry   .push_back( book( name, hDV.at(i) + "_sqrterry",   hDVstr.at(i) + " y-pos sqrt-uncert.",       100,    0,    5 ) );
      h_dv_sqrterrz   .push_back( book( name, hDV.at(i) + "_sqrterrz",   hDVstr.at(i) + " z-pos sqrt-uncert.",       100,    0,    5 ) );
      h_dv_sqrterrr   .push_back( book( name, hDV.at(i) + "_sqrterrr",   hDVstr.at(i) + " r-pos sqrt-uncert.",       100,    0,    5 ) );
      h_dv_sqrterrphi .push_back( book( name, hDV.at(i) + "_sqrterrphi", hDVstr.at(i) + " phi sqrt-uncert.",         100,    0,  0.4 ) );
      h_dv_fracerrx   .push_back( book( name, hDV.at(i) + "_fracerrx",   hDVstr.at(i) + " x-pos fractional uncert.", 100,    0,  0.1 ) );
      h_dv_fracerry   .push_back( book( name, hDV.at(i) + "_fracerry",   hDVstr.at(i) + " y-pos fractional uncert.", 100,    0,  0.1 ) );
      h_dv_fracerrz   .push_back( book( name, hDV.at(i) + "_fracerrz",   hDVstr.at(i) + " z-pos fractional uncert.", 100,    0,  0.1 ) );
      h_dv_fracerrr   .push_back( book( name, hDV.at(i) + "_fracerrr",   hDVstr.at(i) + " r-pos fractional uncert.", 100,    0,  0.1 ) );
      h_dv_fracerrphi .push_back( book( name, hDV.at(i) + "_fracerrphi", hDVstr.at(i) + " phi fractional uncert.",   100,    0,  0.1 ) );
      h_dv_signifx    .push_back( book( name, hDV.at(i) + "_signifx",    hDVstr.at(i) + " x-pos significance",       100,    0, 1000 ) );
      h_dv_signify    .push_back( book( name, hDV.at(i) + "_signify",    hDVstr.at(i) + " y-pos significance",       100,    0, 1000 ) );
      h_dv_signifz    .push_back( book( name, hDV.at(i) + "_signifz",    hDVstr.at(i) + " z-pos significance",       100,    0, 1000 ) );
      h_dv_signifr    .push_back( book( name, hDV.at(i) + "_signifr",    hDVstr.at(i) + " r-pos significance",       100,    0, 1000 ) );
      h_dv_signifphi  .push_back( book( name, hDV.at(i) + "_signifphi",  hDVstr.at(i) + " phi-pos significance",     100,    0, 1000 ) );

      // vertex tracks
      std::string hDVtrk    = hDV.at(i)    + "_trk";
      std::string hDVtrkstr = hDVstr.at(i) + " track";
      if ( m_histoInfoSwitch->m_vtxTrks ) {
	h_dv_trk_qOverP       .push_back( book( name, hDVtrk + "_qOverP",       hDVtrkstr + " q/p [e/GeV]",             100,  -1.1,   1.1 ) );
	h_dv_trk_theta        .push_back( book( name, hDVtrk + "_theta",        hDVtrkstr + " theta",                   100,     0,  3.15 ) );
	h_dv_trk_pt           .push_back( book( name, hDVtrk + "_pt",           hDVtrkstr + " p_{T} [GeV]",             100,     0,   100 ) );
	h_dv_trk_eta          .push_back( book( name, hDVtrk + "_eta",          hDVtrkstr + " eta",                     100,    -3,     3 ) );
	h_dv_trk_phi          .push_back( book( name, hDVtrk + "_phi",          hDVtrkstr + " phi",                     100,  -3.5,   3.5 ) );
	h_dv_trk_d0           .push_back( book( name, hDVtrk + "_d0",           hDVtrkstr + " d0 [mm]",                 100,  -300,   300 ) );
	h_dv_trk_z0           .push_back( book( name, hDVtrk + "_z0",           hDVtrkstr + " z0 [mm]",                 100, -1500,  1500 ) );
	h_dv_trk_errd0        .push_back( book( name, hDVtrk + "_errd0",        hDVtrkstr + " d0 uncert.",              100,     0,     3 ) );
	h_dv_trk_errz0        .push_back( book( name, hDVtrk + "_errz0",        hDVtrkstr + " z0 uncert.",              100,     0,    15 ) );
	h_dv_trk_sqrterrd0    .push_back( book( name, hDVtrk + "_sqrterrd0",    hDVtrkstr + " d0 sqrt-uncert.",         100,     0,     2 ) );
	h_dv_trk_sqrterrz0    .push_back( book( name, hDVtrk + "_sqrterrz0",    hDVtrkstr + " z0 sqrt-uncert.",         100,     0,     4 ) );
	h_dv_trk_fracerrd0    .push_back( book( name, hDVtrk + "_fracerrd0",    hDVtrkstr + " d0 fractional uncert.",   100,     0,  0.25 ) );
	h_dv_trk_fracerrz0    .push_back( book( name, hDVtrk + "_fracerrz0",    hDVtrkstr + " z0 fractional uncert.",   100,     0,  0.25 ) );
	h_dv_trk_signifd0     .push_back( book( name, hDVtrk + "_signifd0",     hDVtrkstr + " d0 significance",         100,     0,   500 ) );
	h_dv_trk_signifz0     .push_back( book( name, hDVtrk + "_signifz0",     hDVtrkstr + " z0 significance",         100,     0,   500 ) );
	h_dv_trk_errP         .push_back( book( name, hDVtrk + "_errP",         hDVtrkstr + " q/p uncert.",             100,     0,  0.05 ) );
	h_dv_trk_sqrterrP     .push_back( book( name, hDVtrk + "_sqrterrP",     hDVtrkstr + " q/p sqrt-uncert.",        100,     0,  0.25 ) );
	h_dv_trk_fracerrP     .push_back( book( name, hDVtrk + "_fracerrP",     hDVtrkstr + " q/p fractional uncert.",  100,     0,   0.1 ) );
	h_dv_trk_signifP      .push_back( book( name, hDVtrk + "_signifP",      hDVtrkstr + " q/p significance",        100,     0,   150 ) );
	h_dv_trk_chi2         .push_back( book( name, hDVtrk + "_chi2",         hDVtrkstr + " chi2 / nDoF",             100,     0,   7.5 ) );
	h_dv_trk_chiSq        .push_back( book( name, hDVtrk + "_chiSq",        hDVtrkstr + " chi2",                    100,     0,   250 ) );
	h_dv_trk_qOverP_sv    .push_back( book( name, hDVtrk + "_qOverP_sv",    hDVtrkstr + " q/p wrt SV [e/GeV]",      100,  -1.1,   1.1 ) );
	h_dv_trk_theta_sv     .push_back( book( name, hDVtrk + "_theta_sv",     hDVtrkstr + " theta wrt SV",            100,     0,  3.15 ) );
	h_dv_trk_pt_sv        .push_back( book( name, hDVtrk + "_pt_sv",        hDVtrkstr + " p_{T} wrt SV [GeV]",      100,     0,   100 ) );
	h_dv_trk_eta_sv       .push_back( book( name, hDVtrk + "_eta_sv",       hDVtrkstr + " eta wrt SV",              100,    -3,     3 ) );
	h_dv_trk_phi_sv       .push_back( book( name, hDVtrk + "_phi_sv",       hDVtrkstr + " phi wrt SV",              100,  -3.5,   3.5 ) );
	h_dv_trk_d0_sv        .push_back( book( name, hDVtrk + "_d0_sv",        hDVtrkstr + " d0 wrt SV [mm]",          100,   -30,    30 ) );
	h_dv_trk_z0_sv        .push_back( book( name, hDVtrk + "_z0_sv",        hDVtrkstr + " z0 wrt SV [mm]",          100,  -100,   100 ) );
	h_dv_trk_errd0_sv     .push_back( book( name, hDVtrk + "_errd0_sv",     hDVtrkstr + " d0 wrt SV uncert.",       100,     0,     3 ) );
	h_dv_trk_errz0_sv     .push_back( book( name, hDVtrk + "_errz0_sv",     hDVtrkstr + " z0 wrt SV uncert.",       100,     0,    15 ) );
	h_dv_trk_sqrterrd0_sv .push_back( book( name, hDVtrk + "_sqrterrd0_sv", hDVtrkstr + " d0 wrt SV sqrt-uncert.",  100,     0,     2 ) );
	h_dv_trk_sqrterrz0_sv .push_back( book( name, hDVtrk + "_sqrterrz0_sv", hDVtrkstr + " z0 wrt SV sqrt-uncert.",  100,     0,     4 ) );
	h_dv_trk_fracerrd0_sv .push_back( book( name, hDVtrk + "_fracerrd0_sv", hDVtrkstr + " d0 wrt SV fractional uncert.", 100, 0,   75 ) );
	h_dv_trk_fracerrz0_sv .push_back( book( name, hDVtrk + "_fracerrz0_sv", hDVtrkstr + " z0 wrt SV fractional uncert.", 100, 0,   75 ) );
	h_dv_trk_signifd0_sv  .push_back( book( name, hDVtrk + "_signifd0_sv",  hDVtrkstr + " d0 wrt SV significance",  100,     0,    50 ) );
	h_dv_trk_signifz0_sv  .push_back( book( name, hDVtrk + "_signifz0_sv",  hDVtrkstr + " z0 wrt SV significance",  100,     0,    50 ) );
	h_dv_trk_errP_sv      .push_back( book( name, hDVtrk + "_errP_sv",      hDVtrkstr + " q/p wrt SV uncert.",      100,     0,  0.05 ) );
	h_dv_trk_sqrterrP_sv  .push_back( book( name, hDVtrk + "_sqrterrP_sv",  hDVtrkstr + " q/p wrt SV sqrt-uncert.", 100,     0,  0.25 ) );
	h_dv_trk_fracerrP_sv  .push_back( book( name, hDVtrk + "_fracerrP_sv",  hDVtrkstr + " q/p wrt SV fractional uncert.", 100, 0, 0.2 ) );
	h_dv_trk_signifP_sv   .push_back( book( name, hDVtrk + "_signifP_sv",   hDVtrkstr + " q/p wrt SV significance", 100,     0,   150 ) );
	h_dv_trk_chi2_sv      .push_back( book( name, hDVtrk + "_chi2_sv",      hDVtrkstr + " chi2 to SV / nDoF",       100,     0,    10 ) );
	h_dv_trk_chiSq_sv     .push_back( book( name, hDVtrk + "_chiSq_sv",     hDVtrkstr + " chi2 to SV",              100,     0,   100 ) );
      }
      
      // sum, min, max vertex track errors
      std::string hDVsum    = hDV.at(i)    + "_sum";
      std::string hDVsumstr = hDVstr.at(i) + " sum track";
      h_dv_sumd0           .push_back( book( name, hDVsum + "d0",           hDVsumstr + " |d0| [mm]",                     100, 0,  500 ) );
      h_dv_sumz0           .push_back( book( name, hDVsum + "z0",           hDVsumstr + " |z0| [mm]",                     100, 0, 2000 ) );
      h_dv_sumP            .push_back( book( name, hDVsum + "P",            hDVsumstr + " |q/|p [e/GeV]",                 100, 0,    5 ) );
      h_dv_sumErrd0        .push_back( book( name, hDVsum + "Errd0",        hDVsumstr + " d0 uncert.",                    100, 0,    5 ) );
      h_dv_sumErrz0        .push_back( book( name, hDVsum + "Errz0",        hDVsumstr + " z0 uncert.",                    100, 0,   25 ) );
      h_dv_sumErrP         .push_back( book( name, hDVsum + "ErrP",         hDVsumstr + " q/p uncert.",                   100, 0,  0.1 ) );
      h_dv_sumSqrterrd0    .push_back( book( name, hDVsum + "Sqrterrd0",    hDVsumstr + " d0 sqrt-uncert.",               100, 0,  2.5 ) );
      h_dv_sumSqrterrz0    .push_back( book( name, hDVsum + "Sqrterrz0",    hDVsumstr + " z0 sqrt-uncert.",               100, 0,    5 ) );
      h_dv_sumSqrterrP     .push_back( book( name, hDVsum + "SqrterrP",     hDVsumstr + " q/p sqrt-uncert.",              100, 0,  0.3 ) );
      h_dv_sumFracerrd0    .push_back( book( name, hDVsum + "Fracerrd0",    hDVsumstr + " d0 fractional uncert.",         100, 0,    1 ) );
      h_dv_sumFracerrz0    .push_back( book( name, hDVsum + "Fracerrz0",    hDVsumstr + " z0 fractional uncert.",         100, 0,    1 ) );
      h_dv_sumFracerrP     .push_back( book( name, hDVsum + "FracerrP",     hDVsumstr + " q/p fractional uncert.",        100, 0, 0.25 ) );
      h_dv_sumSignifd0     .push_back( book( name, hDVsum + "Signifd0",     hDVsumstr + " d0 significance",               100, 0, 1000 ) );
      h_dv_sumSignifz0     .push_back( book( name, hDVsum + "Signifz0",     hDVsumstr + " z0 significance",               100, 0, 1000 ) );
      h_dv_sumSignifP      .push_back( book( name, hDVsum + "SignifP",      hDVsumstr + " q/p significance",              100, 0,  250 ) );
      h_dv_sumd0_sv        .push_back( book( name, hDVsum + "d0_sv",        hDVsumstr + " |d0| wrt SV [mm]",              100, 0,   50 ) );
      h_dv_sumz0_sv        .push_back( book( name, hDVsum + "z0_sv",        hDVsumstr + " |z0| wrt SV [mm]",              100, 0,  150 ) );
      h_dv_sumP_sv         .push_back( book( name, hDVsum + "P_sv",         hDVsumstr + " |q/p| wrt SV [e/GeV]",          100, 0,    5 ) );
      h_dv_sumErrd0_sv     .push_back( book( name, hDVsum + "Errd0_sv",     hDVsumstr + " d0 wrt SV uncert.",             100, 0,    5 ) );
      h_dv_sumErrz0_sv     .push_back( book( name, hDVsum + "Errz0_sv",     hDVsumstr + " z0 wrt SV uncert.",             100, 0,   25 ) );
      h_dv_sumErrP_sv      .push_back( book( name, hDVsum + "ErrP_sv",      hDVsumstr + " q/p wrt SV uncert.",            100, 0,  0.1 ) );
      h_dv_sumSqrterrd0_sv .push_back( book( name, hDVsum + "Sqrterrd0_sv", hDVsumstr + " d0 wrt SV sqrt-uncert.",        100, 0,  2.5 ) );
      h_dv_sumSqrterrz0_sv .push_back( book( name, hDVsum + "Sqrterrz0_sv", hDVsumstr + " z0 wrt SV sqrt-uncert.",        100, 0,    5 ) );
      h_dv_sumSqrterrP_sv  .push_back( book( name, hDVsum + "SqrterrP_sv",  hDVsumstr + " q/p wrt SV sqrt-uncert.",       100, 0,  0.3 ) );
      h_dv_sumFracerrd0_sv .push_back( book( name, hDVsum + "Fracerrd0_sv", hDVsumstr + " d0 wrt SV fractional uncert.",  100, 0,  150 ) );
      h_dv_sumFracerrz0_sv .push_back( book( name, hDVsum + "Fracerrz0_sv", hDVsumstr + " z0 wrt SV fractional uncert.",  100, 0,  150 ) );
      h_dv_sumFracerrP_sv  .push_back( book( name, hDVsum + "FracerrP_sv",  hDVsumstr + " q/p wrt SV fractional uncert.", 100, 0, 0.25 ) );
      h_dv_sumSignifd0_sv  .push_back( book( name, hDVsum + "Signifd0_sv",  hDVsumstr + " d0 wrt SV significance",        100, 0,   75 ) );
      h_dv_sumSignifz0_sv  .push_back( book( name, hDVsum + "Signifz0_sv",  hDVsumstr + " z0 wrt SV significance",        100, 0,   75 ) );
      h_dv_sumSignifP_sv   .push_back( book( name, hDVsum + "SignifP_sv",   hDVsumstr + " q/p wrt SV significance",       100, 0,  250 ) );
      std::string hDVmin    = hDV.at(i)    + "_min";
      std::string hDVminstr = hDVstr.at(i) + " min track";
      h_dv_mind0           .push_back( book( name, hDVmin + "d0",           hDVminstr + " |d0| [mm]",               100, 0,  200 ) );
      h_dv_minz0           .push_back( book( name, hDVmin + "z0",           hDVminstr + " |z0| [mm]",               100, 0, 1000 ) );
      h_dv_minP            .push_back( book( name, hDVmin + "P",            hDVminstr + " |q/p| [e/GeV]",           100, 0,    1 ) );
      h_dv_minErrd0        .push_back( book( name, hDVmin + "Errd0",        hDVminstr + " d0 uncert.",              100, 0,    2 ) );
      h_dv_minErrz0        .push_back( book( name, hDVmin + "Errz0",        hDVminstr + " z0 uncert.",              100, 0,   10 ) );
      h_dv_minErrP         .push_back( book( name, hDVmin + "ErrP",         hDVminstr + " q/p uncert.",             100, 0, 0.02 ) );
      h_dv_minSqrterrd0    .push_back( book( name, hDVmin + "Sqrterrd0",    hDVminstr + " d0 sqrt-uncert.",         100, 0,  1.5 ) );
      h_dv_minSqrterrz0    .push_back( book( name, hDVmin + "Sqrterrz0",    hDVminstr + " z0 sqrt-uncert.",         100, 0,  3.5 ) );
      h_dv_minSqrterrP     .push_back( book( name, hDVmin + "SqrterrP",     hDVminstr + " q/p sqrt-uncert.",        100, 0, 0.15 ) );
      h_dv_minFracerrd0    .push_back( book( name, hDVmin + "Fracerrd0",    hDVminstr + " d0 fractional uncert.",   100, 0, 0.15 ) );
      h_dv_minFracerrz0    .push_back( book( name, hDVmin + "Fracerrz0",    hDVminstr + " z0 fractional uncert.",   100, 0, 0.15 ) );
      h_dv_minFracerrP     .push_back( book( name, hDVmin + "FracerrP",     hDVminstr + " q/p fractional uncert.",  100, 0, 0.05 ) );
      h_dv_minSignifd0     .push_back( book( name, hDVmin + "Signifd0",     hDVminstr + " d0 significance",         100, 0,  350 ) );
      h_dv_minSignifz0     .push_back( book( name, hDVmin + "Signifz0",     hDVminstr + " z0 significance",         100, 0,  350 ) );
      h_dv_minSignifP      .push_back( book( name, hDVmin + "SignifP",      hDVminstr + " q/p significance",        100, 0,  100 ) );
      h_dv_mind0_sv        .push_back( book( name, hDVmin + "d0_sv",        hDVminstr + " |d0| wrt SV [mm]",        100, 0,   15 ) );
      h_dv_minz0_sv        .push_back( book( name, hDVmin + "z0_sv",        hDVminstr + " |z0| wrt SV [mm]",        100, 0,   50 ) );
      h_dv_minP_sv         .push_back( book( name, hDVmin + "P_sv",         hDVminstr + " |q/p| wrt SV [e/GeV]",    100, 0,    1 ) );
      h_dv_minErrd0_sv     .push_back( book( name, hDVmin + "Errd0_sv",     hDVminstr + " d0 wrt SV uncert.",       100, 0,    2 ) );
      h_dv_minErrz0_sv     .push_back( book( name, hDVmin + "Errz0_sv",     hDVminstr + " z0 wrt SV uncert.",       100, 0,   10 ) );
      h_dv_minErrP_sv      .push_back( book( name, hDVmin + "ErrP_sv",      hDVminstr + " q/p wrt SV uncert.",      100, 0, 0.02 ) );
      h_dv_minSqrterrd0_sv .push_back( book( name, hDVmin + "Sqrterrd0_sv", hDVminstr + " d0 wrt SV sqrt-uncert.",  100, 0,  1.5 ) );
      h_dv_minSqrterrz0_sv .push_back( book( name, hDVmin + "Sqrterrz0_sv", hDVminstr + " z0 wrt SV sqrt-uncert.",  100, 0,  3.5 ) );
      h_dv_minSqrterrP_sv  .push_back( book( name, hDVmin + "SqrterrP_sv",  hDVminstr + " q/p wrt SV sqrt-uncert.", 100, 0, 0.15 ) );
      h_dv_minFracerrd0_sv .push_back( book( name, hDVmin + "Fracerrd0_sv", hDVminstr + " d0 wrt SV fractional uncert.",  100, 0,  50 ) );
      h_dv_minFracerrz0_sv .push_back( book( name, hDVmin + "Fracerrz0_sv", hDVminstr + " z0 wrt SV fractional uncert.",  100, 0,  50 ) );
      h_dv_minFracerrP_sv  .push_back( book( name, hDVmin + "FracerrP_sv",  hDVminstr + " q/p wrt SV fractional uncert.", 100, 0, 0.1 ) );
      h_dv_minSignifd0_sv  .push_back( book( name, hDVmin + "Signifd0_sv",  hDVminstr + " d0 wrt SV significance",  100, 0,   25 ) );
      h_dv_minSignifz0_sv  .push_back( book( name, hDVmin + "Signifz0_sv",  hDVminstr + " z0 wrt SV significance",  100, 0,   25 ) );
      h_dv_minSignifP_sv   .push_back( book( name, hDVmin + "SignifP_sv",   hDVminstr + " q/p wrt SV significance", 100, 0,  100 ) );
      std::string hDVmax    = hDV.at(i)    + "_max";
      std::string hDVmaxstr = hDVstr.at(i) + " max track";
      h_dv_maxd0           .push_back( book( name, hDVmax + "d0",           hDVmaxstr + " |d0| [mm]",               100, 0,  300 ) );
      h_dv_maxz0           .push_back( book( name, hDVmax + "z0",           hDVmaxstr + " |z0| [mm]",               100, 0, 1500 ) );
      h_dv_maxP            .push_back( book( name, hDVmax + "P",            hDVmaxstr + " |q/p| [e/GeV]",           100, 0,  1.1 ) );
      h_dv_maxErrd0        .push_back( book( name, hDVmax + "Errd0",        hDVmaxstr + " d0 uncert.",              100, 0,    3 ) );
      h_dv_maxErrz0        .push_back( book( name, hDVmax + "Errz0",        hDVmaxstr + " z0 uncert.",              100, 0,   15 ) );
      h_dv_maxErrP         .push_back( book( name, hDVmax + "ErrP",         hDVmaxstr + " q/p uncert.",             100, 0, 0.05 ) );
      h_dv_maxSqrterrd0    .push_back( book( name, hDVmax + "Sqrterrd0",    hDVmaxstr + " d0 sqrt-uncert.",         100, 0,    2 ) );
      h_dv_maxSqrterrz0    .push_back( book( name, hDVmax + "Sqrterrz0",    hDVmaxstr + " z0 sqrt-uncert.",         100, 0,    4 ) );
      h_dv_maxSqrterrP     .push_back( book( name, hDVmax + "SqrterrP",     hDVmaxstr + " q/p sqrt-uncert.",        100, 0, 0.25 ) );
      h_dv_maxFracerrd0    .push_back( book( name, hDVmax + "Fracerrd0",    hDVmaxstr + " d0 fractional uncert.",   100, 0, 0.25 ) );
      h_dv_maxFracerrz0    .push_back( book( name, hDVmax + "Fracerrz0",    hDVmaxstr + " z0 fractional uncert.",   100, 0, 0.25 ) );
      h_dv_maxFracerrP     .push_back( book( name, hDVmax + "FracerrP",     hDVmaxstr + " q/p fractional uncert.",  100, 0,  0.1 ) );
      h_dv_maxSignifd0     .push_back( book( name, hDVmax + "Signifd0",     hDVmaxstr + " d0 significance",         100, 0,  500 ) );
      h_dv_maxSignifz0     .push_back( book( name, hDVmax + "Signifz0",     hDVmaxstr + " z0 significance",         100, 0,  500 ) );
      h_dv_maxSignifP      .push_back( book( name, hDVmax + "SignifP",      hDVmaxstr + " q/p significance",        100, 0,  150 ) );
      h_dv_maxd0_sv        .push_back( book( name, hDVmax + "d0_sv",        hDVmaxstr + " |d0| wrt SV [mm]",        100, 0,   30 ) );
      h_dv_maxz0_sv        .push_back( book( name, hDVmax + "z0_sv",        hDVmaxstr + " |z0| wrt SV [mm]",        100, 0,  100 ) );
      h_dv_maxP_sv         .push_back( book( name, hDVmax + "P_sv",         hDVmaxstr + " |q/p| wrt SV [e/GeV]",    100, 0,  1.1 ) );
      h_dv_maxErrd0_sv     .push_back( book( name, hDVmax + "Errd0_sv",     hDVmaxstr + " d0 wrt SV uncert.",       100, 0,    3 ) );
      h_dv_maxErrz0_sv     .push_back( book( name, hDVmax + "Errz0_sv",     hDVmaxstr + " z0 wrt SV uncert.",       100, 0,   15 ) );
      h_dv_maxErrP_sv      .push_back( book( name, hDVmax + "ErrP_sv",      hDVmaxstr + " q/p wrt SV uncert.",      100, 0, 0.05 ) );
      h_dv_maxSqrterrd0_sv .push_back( book( name, hDVmax + "Sqrterrd0_sv", hDVmaxstr + " d0 wrt SV sqrt-uncert.",  100, 0,    2 ) );
      h_dv_maxSqrterrz0_sv .push_back( book( name, hDVmax + "Sqrterrz0_sv", hDVmaxstr + " z0 wrt SV sqrt-uncert.",  100, 0,    4 ) );
      h_dv_maxSqrterrP_sv  .push_back( book( name, hDVmax + "SqrterrP_sv",  hDVmaxstr + " q/p wrt SV sqrt-uncert.", 100, 0, 0.25 ) );
      h_dv_maxFracerrd0_sv .push_back( book( name, hDVmax + "Fracerrd0_sv", hDVmaxstr + " d0 wrt SV fractional uncert.",  100, 0,  75 ) );
      h_dv_maxFracerrz0_sv .push_back( book( name, hDVmax + "Fracerrz0_sv", hDVmaxstr + " z0 wrt SV fractional uncert.",  100, 0,  75 ) );
      h_dv_maxFracerrP_sv  .push_back( book( name, hDVmax + "FracerrP_sv",  hDVmaxstr + " q/p wrt SV fractional uncert.", 100, 0, 0.2 ) );
      h_dv_maxSignifd0_sv  .push_back( book( name, hDVmax + "Signifd0_sv",  hDVmaxstr + " d0 wrt SV significance",  100, 0,   50 ) );
      h_dv_maxSignifz0_sv  .push_back( book( name, hDVmax + "Signifz0_sv",  hDVmaxstr + " z0 wrt SV significance",  100, 0,   50 ) );
      h_dv_maxSignifP_sv   .push_back( book( name, hDVmax + "SignifP_sv",   hDVmaxstr + " q/p wrt SV significance", 100, 0,  150 ) );
      // --> look at sum, min, max for final, selected, associated tracks
      // --> look at min, max track chi2 ?

      // 2d vertex / track histos
      h_dv_z_r                    .push_back( book( name, hDV.at(i) + "_z_r",             hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
      						    hDVstr.at(i) + " z-pos [mm]",           100,  -800,  800 ) );
      h_dv_mass_r                 .push_back( book( name, hDV.at(i) + "_mass_r",          hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVstr.at(i) + " mass [GeV]",           100,     0,   50 ) );
      h_dv_z_chi2                 .push_back( book( name, hDV.at(i) + "_z_chi2",          hDVstr.at(i) + " chi2 / nDoF",     100,     0,   10,
						    hDVstr.at(i) + " z-pos [mm]",           100,  -800,  800 ) );
      h_dv_r_chi2                 .push_back( book( name, hDV.at(i) + "_r_chi2",          hDVstr.at(i) + " chi2 / nDoF",     100,     0,   10,
						    hDVstr.at(i) + " r-pos [mm]",           100,     0,  400 ) );
      h_dv_mass_chi2              .push_back( book( name, hDV.at(i) + "_mass_chi2",       hDVstr.at(i) + " chi2 / nDoF",     100,     0,   10,
						    hDVstr.at(i) + " mass [GeV]",           100,     0,   50 ) );
      h_dv_z_r_s                  .push_back( book( name, hDV.at(i) + "_z_r_s",           hDVstr.at(i) + " r-pos [mm]",      100,     0,  300,
      						    hDVstr.at(i) + " z-pos [mm]",           100,  -300,  300 ) );
      h_dv_mass_r_s               .push_back( book( name, hDV.at(i) + "_mass_r_s",        hDVstr.at(i) + " r-pos [mm]",      100,     0,  300,
						    hDVstr.at(i) + " mass [GeV]",           100,     0,   25 ) );
      h_dv_z_chi2_s               .push_back( book( name, hDV.at(i) + "_z_chi2_s",        hDVstr.at(i) + " chi2 / nDoF",     100,     0,    5,
						    hDVstr.at(i) + " z-pos [mm]",           100,  -300,  300 ) );
      h_dv_r_chi2_s               .push_back( book( name, hDV.at(i) + "_r_chi2_s",        hDVstr.at(i) + " chi2 / nDoF",     100,     0,    5,
						    hDVstr.at(i) + " r-pos [mm]",           100,     0,  300 ) );
      h_dv_mass_chi2_s            .push_back( book( name, hDV.at(i) + "_mass_chi2_s",     hDVstr.at(i) + " chi2 / nDoF",     100,     0,    5,
						    hDVstr.at(i) + " mass [GeV]",           100,     0,   25 ) );
      h_dv_errx_x                 .push_back( book( name, hDV.at(i) + "_errx_x",          hDVstr.at(i) + " x-pos [mm]",      100,  -400,  400,
						    hDVstr.at(i) + " x-pos uncert.",        100,     0,   25 ) );
      h_dv_erry_y                 .push_back( book( name, hDV.at(i) + "_errr_y",          hDVstr.at(i) + " y-pos [mm]",      100,  -400,  400,
						    hDVstr.at(i) + " y-pos uncert.",        100,     0,   25 ) );
      h_dv_errz_z                 .push_back( book( name, hDV.at(i) + "_errz_z",          hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVstr.at(i) + " z-pos uncert.",        100,     0,   25 ) );
      h_dv_errr_r                 .push_back( book( name, hDV.at(i) + "_errr_r",          hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVstr.at(i) + " r-pos uncert.",        100,     0,   25 ) );
      h_dv_errphi_phi             .push_back( book( name, hDV.at(i) + "_errphi_phi",      hDVstr.at(i) + " phi-pos [mm]",    100,  -3.5,  3.5,
						    hDVstr.at(i) + " phi-pos uncert.",      100,     0, 0.15 ) );
      h_dv_sqrterrx_x             .push_back( book( name, hDV.at(i) + "_sqrterrx_x",      hDVstr.at(i) + " x-pos [mm]",      100,  -400,  400,
						    hDVstr.at(i) + " x-pos sqrt-uncert.",   100,     0,    5 ) );
      h_dv_sqrterry_y             .push_back( book( name, hDV.at(i) + "_sqrterry_y",      hDVstr.at(i) + " y-pos [mm]",      100,  -400,  400,
						    hDVstr.at(i) + " y-pos sqrt-uncert.",   100,     0,    5 ) );
      h_dv_sqrterrz_z             .push_back( book( name, hDV.at(i) + "_sqrterrz_z",      hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVstr.at(i) + " z-pos sqrt-uncert.",   100,     0,    5 ) );
      h_dv_sqrterrr_r             .push_back( book( name, hDV.at(i) + "_sqrterrr_r",      hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVstr.at(i) + " r-pos sqrt-uncert.",   100,     0,    5 ) );
      h_dv_sqrterrphi_phi         .push_back( book( name, hDV.at(i) + "_sqrterrphi_phi",  hDVstr.at(i) + " phi-pos [mm]",    100,  -3.5,  3.5,
						    hDVstr.at(i) + " phi-pos sqrt-uncert.", 100,     0,  0.4 ) );
      h_dv_sumErrd0_r             .push_back( book( name, hDVsum + "Errd0_r",             hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVsumstr + " d0 uncert.",              100,     0,    5 ) );
      h_dv_sumErrz0_z             .push_back( book( name, hDVsum + "Errz0_z",             hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVsumstr + " z0 uncert.",              100,     0,   25 ) );
      h_dv_sumErrP_pt             .push_back( book( name, hDVsum + "ErrP_pt",             hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVsumstr + " q/p uncert.",             100,     0,  0.1 ) );
      h_dv_sumSqrterrd0_r         .push_back( book( name, hDVsum + "Sqrterrd0_r",         hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVsumstr + " d0 sqrt-uncert.",         100,     0,  2.5 ) );
      h_dv_sumSqrterrz0_z         .push_back( book( name, hDVsum + "Sqrterrz0_z",         hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVsumstr + " z0 sqrt-uncert.",         100,     0,    5 ) );
      h_dv_sumSqrterrP_pt         .push_back( book( name, hDVsum + "SqrterrP_pt",         hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVsumstr + " q/p sqrt-uncert.",        100,     0,  0.3 ) );
      h_dv_sumErrd0sv_r           .push_back( book( name, hDVsum + "Errd0sv_r",           hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVsumstr + " d0 wrt SV uncert.",       100,     0,    5 ) );
      h_dv_sumErrz0sv_z           .push_back( book( name, hDVsum + "Errz0sv_z",           hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVsumstr + " z0 wrt SV uncert.",       100,     0,   25 ) );
      h_dv_sumErrPsv_pt           .push_back( book( name, hDVsum + "ErrPsv_pt",           hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVsumstr + " q/p wrt SV uncert.",      100,     0,  0.1 ) );
      h_dv_sumSqrterrd0sv_r       .push_back( book( name, hDVsum + "Sqrterrd0sv_r",       hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVsumstr + " d0 wrt SV sqrt-uncert.",  100,     0,  2.5 ) );
      h_dv_sumSqrterrz0sv_z       .push_back( book( name, hDVsum + "Sqrterrz0sv_z",       hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVsumstr + " z0 wrt SV sqrt-uncert.",  100,     0,    5 ) );
      h_dv_sumSqrterrPsv_pt       .push_back( book( name, hDVsum + "SqrterrPsv_pt",       hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVsumstr + " q/p wrt SV sqrt-uncert.", 100,     0,  0.3 ) );
      h_dv_minErrd0_r             .push_back( book( name, hDVmin + "Errd0_r",             hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVminstr + " d0 uncert.",              100,     0,    2 ) );
      h_dv_minErrz0_z             .push_back( book( name, hDVmin + "Errz0_z",             hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVminstr + " z0 uncert.",              100,     0,   10 ) );
      h_dv_minErrP_pt             .push_back( book( name, hDVmin + "ErrP_pt",             hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVminstr + " q/p uncert.",             100,     0, 0.02 ) );
      h_dv_minSqrterrd0_r         .push_back( book( name, hDVmin + "Sqrterrd0_r",         hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVminstr + " d0 sqrt-uncert.",         100,     0,  1.5 ) );
      h_dv_minSqrterrz0_z         .push_back( book( name, hDVmin + "Sqrterrz0_z",         hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVminstr + " z0 sqrt-uncert.",         100,     0,  3.5 ) );
      h_dv_minSqrterrP_pt         .push_back( book( name, hDVmin + "SqrterrP_pt",         hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVminstr + " q/p sqrt-uncert.",        100,     0, 0.15 ) );
      h_dv_minErrd0sv_r           .push_back( book( name, hDVmin + "Errd0sv_r",           hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVminstr + " d0 wrt SV uncert.",       100,     0,    2 ) );
      h_dv_minErrz0sv_z           .push_back( book( name, hDVmin + "Errz0sv_z",           hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVminstr + " z0 wrt SV uncert.",       100,     0,   10 ) );
      h_dv_minErrPsv_pt           .push_back( book( name, hDVmin + "ErrPsv_pt",           hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVminstr + " q/p wrt SV uncert.",      100,     0, 0.02 ) );
      h_dv_minSqrterrd0sv_r       .push_back( book( name, hDVmin + "Sqrterrd0sv_r",       hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVminstr + " d0 wrt SV sqrt-uncert.",  100,     0,  1.5 ) );
      h_dv_minSqrterrz0sv_z       .push_back( book( name, hDVmin + "Sqrterrz0sv_z",       hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVminstr + " z0 wrt SV sqrt-uncert.",  100,     0,  3.5 ) );
      h_dv_minSqrterrPsv_pt       .push_back( book( name, hDVmin + "SqrterrPsv_pt",       hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVminstr + " q/p wrt SV sqrt-uncert.", 100,     0, 0.15 ) );
      h_dv_maxErrd0_r             .push_back( book( name, hDVmax + "Errd0_r",             hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVmaxstr + " d0 uncert.",              100,     0,    3 ) );
      h_dv_maxErrz0_z             .push_back( book( name, hDVmax + "Errz0_z",             hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVmaxstr + " z0 uncert.",              100,     0,   15 ) );
      h_dv_maxErrP_pt             .push_back( book( name, hDVmax + "ErrP_pt",             hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVmaxstr + " q/p uncert.",             100,     0, 0.05 ) );
      h_dv_maxSqrterrd0_r         .push_back( book( name, hDVmax + "Sqrterrd0_r",         hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVmaxstr + " d0 sqrt-uncert.",         100,     0,    2 ) );
      h_dv_maxSqrterrz0_z         .push_back( book( name, hDVmax + "Sqrterrz0_z",         hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVmaxstr + " z0 sqrt-uncert.",         100,     0,    4 ) );
      h_dv_maxSqrterrP_pt         .push_back( book( name, hDVmax + "SqrterrP_pt",         hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVmaxstr + " q/p sqrt-uncert.",        100,     0, 0.25 ) );
      h_dv_maxErrd0sv_r           .push_back( book( name, hDVmax + "Errd0sv_r",           hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVmaxstr + " d0 wrt SV uncert.",       100,     0,    3 ) );
      h_dv_maxErrz0sv_z           .push_back( book( name, hDVmax + "Errz0sv_z",           hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVmaxstr + " z0 wrt SV uncert.",       100,     0,   15 ) );
      h_dv_maxErrPsv_pt           .push_back( book( name, hDVmax + "ErrPsv_pt",           hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVmaxstr + " q/p wrt SV uncert.",      100,     0, 0.05 ) );
      h_dv_maxSqrterrd0sv_r       .push_back( book( name, hDVmax + "Sqrterrd0sv_r",       hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVmaxstr + " d0 wrt SV sqrt-uncert.",  100,     0,    2 ) );
      h_dv_maxSqrterrz0sv_z       .push_back( book( name, hDVmax + "Sqrterrz0sv_z",       hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVmaxstr + " z0 wrt SV sqrt-uncert.",  100,     0,    4 ) );
      h_dv_maxSqrterrPsv_pt       .push_back( book( name, hDVmax + "SqrterrPsv_pt",       hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVmaxstr + " q/p wrt SV sqrt-uncert.", 100,     0, 0.25 ) );
      h_dv_trkd0_r                .push_back( book( name, hDVtrk + "d0_r",                hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVtrkstr + " d0 [mm]",                 100,  -300,  300 ) );
      h_dv_trkz0_z                .push_back( book( name, hDVtrk + "z0_z",                hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVtrkstr + " z0 [mm]",                 100, -1500, 1500 ) );
      h_dv_trkP_pt                .push_back( book( name, hDVtrk + "P_pt",                hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVtrkstr + " q/p [e/GeV]",             100,  -1.1,  1.1 ) );
      h_dv_trkErrd0_r             .push_back( book( name, hDVtrk + "Errd0_r",             hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVtrkstr + " d0 uncert.",              100,     0,    5 ) );
      h_dv_trkErrz0_z             .push_back( book( name, hDVtrk + "Errz0_z",             hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVtrkstr + " z0 uncert.",              100,     0,   25 ) );
      h_dv_trkErrP_pt             .push_back( book( name, hDVtrk + "ErrP_pt",             hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVtrkstr + " q/p uncert.",             100,     0, 0.05 ) );
      h_dv_trkSqrterrd0_r         .push_back( book( name, hDVtrk + "Sqrterrd0_r",         hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVtrkstr + " d0 sqrt-uncert.",         100,     0,  2.5 ) );
      h_dv_trkSqrterrz0_z         .push_back( book( name, hDVtrk + "Sqrterrz0_z",         hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVtrkstr + " z0 sqrt-uncert.",         100,     0,    5 ) );
      h_dv_trkSqrterrP_pt         .push_back( book( name, hDVtrk + "SqrterrP_pt",         hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVtrkstr + " q/p sqrt-uncert.",        100,     0, 0.25 ) );
      h_dv_trkd0sv_r              .push_back( book( name, hDVtrk + "d0sv_r",              hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVtrkstr + " d0 wrt SV [mm]",          100,   -60,   60 ) );
      h_dv_trkz0sv_z              .push_back( book( name, hDVtrk + "z0sv_z",              hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVtrkstr + " z0 wrt SV [mm]",          100,  -300,  300 ) );
      h_dv_trkPsv_pt              .push_back( book( name, hDVtrk + "Psv_pt",              hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVtrkstr + " q/P wrt SV [e/GeV]",      100,  -1.1,  1.1 ) );
      h_dv_trkErrd0sv_r           .push_back( book( name, hDVtrk + "Errd0sv_r",           hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVtrkstr + " d0 wrt SV uncert.",       100,     0,    5 ) );
      h_dv_trkErrz0sv_z           .push_back( book( name, hDVtrk + "Errz0sv_z",           hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVtrkstr + " z0 wrt SV uncert.",       100,     0,   25 ) );
      h_dv_trkErrPsv_pt           .push_back( book( name, hDVtrk + "ErrPsv_pt",           hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVtrkstr + " q/p wrt SV uncert.",      100,     0, 0.05 ) );
      h_dv_trkSqrterrd0sv_r       .push_back( book( name, hDVtrk + "Sqrterrd0sv_r",       hDVstr.at(i) + " r-pos [mm]",      100,     0,  400,
						    hDVtrkstr + " d0 wrt SV sqrt-uncert.",  100,     0,  2.5 ) );
      h_dv_trkSqrterrz0sv_z       .push_back( book( name, hDVtrk + "Sqrterrz0sv_z",       hDVstr.at(i) + " z-pos [mm]",      100,  -800,  800,
						    hDVtrkstr + " z0 wrt SV sqrt-uncert.",  100,     0,    5 ) );
      h_dv_trkSqrterrPsv_pt       .push_back( book( name, hDVtrk + "SqrterrPsv_pt",       hDVstr.at(i) + " p_{T} [GeV]",     100,     0,  100,
						    hDVtrkstr + " q/p wrt SV sqrt-uncert.", 100,     0, 0.25 ) );
      h_dv_trkErrd0_trkd0         .push_back( book( name, hDVtrk + "Errd0_trkd0",         hDVtrkstr + " d0 [mm]",            100,  -300,  300,
						    hDVtrkstr + " d0 uncert.",              100,     0,    5 ) );
      h_dv_trkErrz0_trkz0         .push_back( book( name, hDVtrk + "Errz0sv_trkz0",       hDVtrkstr + " z0 [mm]",            100, -1500, 1500,
						    hDVtrkstr + " z0 uncert.",              100,     0,   25 ) );
      h_dv_trkErrP_trkP           .push_back( book( name, hDVtrk + "ErrP_trkP",           hDVtrkstr + " q/p [e/GeV]",        100,  -1.1,  1.1,
						    hDVtrkstr + " q/p uncert.",             100,     0, 0.05 ) );
      h_dv_trkSqrterrd0_trkd0     .push_back( book( name, hDVtrk + "Sqrterrd0_trkd0",     hDVtrkstr + " d0 [mm]",            100,  -300,  300,
						    hDVtrkstr + " d0 sqrt-uncert.",         100,     0,  2.5 ) );
      h_dv_trkSqrterrz0_trkz0     .push_back( book( name, hDVtrk + "Sqrterrz0_trkz0",     hDVtrkstr + " z0 [mm]",            100, -1500, 1500,
						    hDVtrkstr + " z0 sqrt-uncert.",         100,     0,    5 ) );
      h_dv_trkSqrterrP_trkP       .push_back( book( name, hDVtrk + "SqrterrP_trkP",       hDVtrkstr + " q/p [e/GeV]",        100,  -1.1,  1.1,
						    hDVtrkstr + " q/p sqrt-uncert.",        100,     0, 0.25 ) );
      h_dv_trkErrd0sv_trkd0sv     .push_back( book( name, hDVtrk + "Errd0sv_trkd0sv",     hDVtrkstr + " d0 wrt SV [mm]",     100,   -60,   60,
						    hDVtrkstr + " d0 wrt SV uncert.",       100,     0,    5 ) );
      h_dv_trkErrz0sv_trkz0sv     .push_back( book( name, hDVtrk + "Errz0sv_trkz0sv",     hDVtrkstr + " z0 wrt SV [mm]",     100,  -300,  300,
						    hDVtrkstr + " z0 wrt SV uncert.",       100,     0,   25 ) );
      h_dv_trkErrPsv_trkPsv       .push_back( book( name, hDVtrk + "ErrPsv_trkPsv",       hDVtrkstr + " q/p wrt SV [e/GeV]", 100,  -1.1,  1.1,
						    hDVtrkstr + " q/p wrt SV uncert.",      100,     0, 0.05 ) );
      h_dv_trkSqrterrd0sv_trkd0sv .push_back( book( name, hDVtrk + "Sqrterrd0sv_trkd0sv", hDVtrkstr + " d0 wrt SV [mm]",     100,   -60,   60,
						    hDVtrkstr + " d0 wrt SV sqrt-uncert.",  100,     0,  2.5 ) );
      h_dv_trkSqrterrz0sv_trkz0sv .push_back( book( name, hDVtrk + "Sqrterrz0sv_trkz0sv", hDVtrkstr + " z0 wrt SV [mm]",     100,  -300,  300,
						    hDVtrkstr + " z0 wrt SV sqrt-uncert.",  100,     0,    5 ) );
      h_dv_trkSqrterrPsv_trkPsv   .push_back( book( name, hDVtrk + "SqrterrPsv_trkPsv",   hDVtrkstr + " q/p wrt SV [e/GeV]", 100,  -1.1,  1.1,
						    hDVtrkstr + " q/p wrt SV sqrt-uncert.", 100,     0, 0.25 ) );
      
      // n-track vertices
      if ( m_numVtxTrks ) {
	std::vector<TH1F*> h_njtrkdv_n;
	std::vector<TH1F*> h_njtrkdv_z;
	std::vector<TH1F*> h_njtrkdv_z_s;
	std::vector<TH1F*> h_njtrkdv_r;
	std::vector<TH1F*> h_njtrkdv_r_s;
	std::vector<TH1F*> h_njtrkdv_mass;
	std::vector<TH1F*> h_njtrkdv_mass_s;
	std::vector<TH1F*> h_njtrkdv_direction;
	std::vector<TH1F*> h_njtrkdv_minOpAng;
	std::vector<TH1F*> h_njtrkdv_maxOpAng;
	std::vector<TH1F*> h_njtrkdv_chi2;
	std::vector<TH1F*> h_njtrkdv_chi2_s;
	std::vector<TH1F*> h_njtrkdv_sqrterrx;
	std::vector<TH1F*> h_njtrkdv_sqrterry;
	std::vector<TH1F*> h_njtrkdv_sqrterrz;
	std::vector<TH1F*> h_njtrkdv_sqrterrr;
	std::vector<TH1F*> h_njtrkdv_sqrterrphi;
	std::vector<TH1F*> h_njtrkdv_sumSqrterrd0;
	std::vector<TH1F*> h_njtrkdv_sumSqrterrz0;
	std::vector<TH1F*> h_njtrkdv_sumSqrterrP;
	std::vector<TH1F*> h_njtrkdv_sumSqrterrd0_sv;
	std::vector<TH1F*> h_njtrkdv_sumSqrterrz0_sv;
	std::vector<TH1F*> h_njtrkdv_sumSqrterrP_sv;
	std::vector<TH1F*> h_njtrkdv_minSqrterrd0;
	std::vector<TH1F*> h_njtrkdv_minSqrterrz0;
	std::vector<TH1F*> h_njtrkdv_minSqrterrP;
	std::vector<TH1F*> h_njtrkdv_minSqrterrd0_sv;
	std::vector<TH1F*> h_njtrkdv_minSqrterrz0_sv;
	std::vector<TH1F*> h_njtrkdv_minSqrterrP_sv;
	std::vector<TH1F*> h_njtrkdv_maxSqrterrd0;
	std::vector<TH1F*> h_njtrkdv_maxSqrterrz0;
	std::vector<TH1F*> h_njtrkdv_maxSqrterrP;
	std::vector<TH1F*> h_njtrkdv_maxSqrterrd0_sv;
	std::vector<TH1F*> h_njtrkdv_maxSqrterrz0_sv;
	std::vector<TH1F*> h_njtrkdv_maxSqrterrP_sv;
	for ( int j = 1; j != m_numVtxTrks; ++j ) {
	  std::string ntrk = std::to_string(j+1);
	  std::string iDV = hDV.at(i); iDV[0] = std::toupper(iDV[0]);
	  std::string ntrkDV = ntrk + "trk" + iDV;
	  std::string ntrkDVstr = ntrk + "-track " + hDVstr.at(i);
	  if ( j+1 == m_numVtxTrks ) ntrkDVstr = ntrk + "-plus-track " + hDVstr.at(i);
	  h_njtrkdv_n          .push_back( book( name, ntrkDV + "_n",          "n " + ntrkDVstr + "s",                15,    0,  15 ) );
	  h_njtrkdv_z          .push_back( book( name, ntrkDV + "_z",          ntrkDVstr + " z-pos [mm]",            100, -800, 800 ) );
	  h_njtrkdv_z_s        .push_back( book( name, ntrkDV + "_z_s",        ntrkDVstr + " z-pos [mm]",            100, -300, 300 ) );
	  h_njtrkdv_r          .push_back( book( name, ntrkDV + "_r",          ntrkDVstr + " r-pos [mm]",            100,    0, 400 ) );
	  h_njtrkdv_r_s        .push_back( book( name, ntrkDV + "_r_s",        ntrkDVstr + " r-pos [mm]",            100,    0, 300 ) );
	  h_njtrkdv_mass       .push_back( book( name, ntrkDV + "_mass",       ntrkDVstr + " mass [GeV]",            100,    0,  50 ) );
	  h_njtrkdv_mass_s     .push_back( book( name, ntrkDV + "_mass_s",     ntrkDVstr + " mass [GeV]",            100,    0,  25 ) );
	  h_njtrkdv_direction  .push_back( book( name, ntrkDV + "_direction",  ntrkDVstr + " direction",             100, -1.1, 1.1 ) );
	  h_njtrkdv_minOpAng   .push_back( book( name, ntrkDV + "_minOpAng",   ntrkDVstr + " cos min opening angle", 100, -1.1, 1.1 ) );
	  h_njtrkdv_maxOpAng   .push_back( book( name, ntrkDV + "_maxOpAng",   ntrkDVstr + " mos max opening angle", 100, -1.1, 1.1 ) );
	  h_njtrkdv_chi2       .push_back( book( name, ntrkDV + "_chi2",       ntrkDVstr + " chi2 / ndof",           100,    0,  10 ) );
	  h_njtrkdv_chi2_s     .push_back( book( name, ntrkDV + "_chi2_s",     ntrkDVstr + " chi2 / ndof",           100,    0,   5 ) );
	  h_njtrkdv_sqrterrx   .push_back( book( name, ntrkDV + "_sqrterrx",   ntrkDVstr + " x-pos sqrt-uncert.",    100,    0,   5 ) );
	  h_njtrkdv_sqrterry   .push_back( book( name, ntrkDV + "_sqrterry",   ntrkDVstr + " y-pos sqrt-uncert.",    100,    0,   5 ) );
	  h_njtrkdv_sqrterrz   .push_back( book( name, ntrkDV + "_sqrterrz",   ntrkDVstr + " z-pos sqrt-uncert.",    100,    0,   5 ) );
	  h_njtrkdv_sqrterrr   .push_back( book( name, ntrkDV + "_sqrterrr",   ntrkDVstr + " r-pos sqrt-uncert.",    100,    0,   5 ) );
	  h_njtrkdv_sqrterrphi .push_back( book( name, ntrkDV + "_sqrterrphi", ntrkDVstr + " phi-pos sqrt-uncert.",  100,    0, 0.4 ) );
	  std::string ntrkDVsum    = ntrkDV    + "_sum";
	  std::string ntrkDVsumstr = ntrkDVstr + " sum track";
	  std::string ntrkDVmin    = ntrkDV    + "_min";
	  std::string ntrkDVminstr = ntrkDVstr + " min track";
	  std::string ntrkDVmax    = ntrkDV    + "_max";
	  std::string ntrkDVmaxstr = ntrkDVstr + " max track";
	  h_njtrkdv_sumSqrterrd0    .push_back( book( name, ntrkDVsum + "Sqrterrd0",    ntrkDVsumstr + " d0 sqrt-uncert.",        100, 0, 2.5 ) );
	  h_njtrkdv_sumSqrterrz0    .push_back( book( name, ntrkDVsum + "Sqrterrz0",    ntrkDVsumstr + " z0 sqrt-uncert.",        100, 0,   5 ) );
	  h_njtrkdv_sumSqrterrP     .push_back( book( name, ntrkDVsum + "SqrterrP",     ntrkDVsumstr + " q/p sqrt-uncert.",       100, 0, 0.3 ) );
	  h_njtrkdv_sumSqrterrd0_sv .push_back( book( name, ntrkDVsum + "Sqrterrd0_sv", ntrkDVsumstr + " d0 wrt SV sqrt-uncert.", 100, 0, 2.5 ) );
	  h_njtrkdv_sumSqrterrz0_sv .push_back( book( name, ntrkDVsum + "Sqrterrz0_sv", ntrkDVsumstr + " z0 wrt SV sqrt-uncert.", 100, 0,   5 ) );
	  h_njtrkdv_sumSqrterrP_sv  .push_back( book( name, ntrkDVsum + "SqrterrP_sv",  ntrkDVsumstr + " q/p wrt SV sqrt-uncert.",100, 0, 0.3 ) );
	  h_njtrkdv_minSqrterrd0    .push_back( book( name, ntrkDVmin + "Sqrterrd0",    ntrkDVminstr + " d0 sqrt-uncert.",        100, 0, 1.5 ) );
	  h_njtrkdv_minSqrterrz0    .push_back( book( name, ntrkDVmin + "Sqrterrz0",    ntrkDVminstr + " z0 sqrt-uncert.",        100, 0, 3.5 ) );
	  h_njtrkdv_minSqrterrP     .push_back( book( name, ntrkDVmin + "SqrterrP",     ntrkDVminstr + " q/p sqrt-uncert.",       100, 0,0.15 ) );
	  h_njtrkdv_minSqrterrd0_sv .push_back( book( name, ntrkDVmin + "Sqrterrd0_sv", ntrkDVminstr + " d0 wrt SV sqrt-uncert.", 100, 0, 1.5 ) );
	  h_njtrkdv_minSqrterrz0_sv .push_back( book( name, ntrkDVmin + "Sqrterrz0_sv", ntrkDVminstr + " z0 wrt SV sqrt-uncert.", 100, 0, 3.5 ) );
	  h_njtrkdv_minSqrterrP_sv  .push_back( book( name, ntrkDVmin + "SqrterrP_sv",  ntrkDVminstr + " q/p wrt SV sqrt-uncert.",100, 0,0.15 ) );
	  h_njtrkdv_maxSqrterrd0    .push_back( book( name, ntrkDVmax + "Sqrterrd0",    ntrkDVmaxstr + " d0 sqrt-uncert.",        100, 0,   2 ) );
	  h_njtrkdv_maxSqrterrz0    .push_back( book( name, ntrkDVmax + "Sqrterrz0",    ntrkDVmaxstr + " z0 sqrt-uncert.",        100, 0,   4 ) );
	  h_njtrkdv_maxSqrterrP     .push_back( book( name, ntrkDVmax + "SqrterrP",     ntrkDVmaxstr + " q/p sqrt-uncert.",       100, 0,0.25 ) );
	  h_njtrkdv_maxSqrterrd0_sv .push_back( book( name, ntrkDVmax + "Sqrterrd0_sv", ntrkDVmaxstr + " d0 wrt SV sqrt-uncert.", 100, 0,   2 ) );
	  h_njtrkdv_maxSqrterrz0_sv .push_back( book( name, ntrkDVmax + "Sqrterrz0_sv", ntrkDVmaxstr + " z0 wrt SV sqrt-uncert.", 100, 0,   4 ) );
	  h_njtrkdv_maxSqrterrP_sv  .push_back( book( name, ntrkDVmax + "SqrterrP_sv",  ntrkDVmaxstr + " q/p wrt SV sqrt-uncert.",100, 0,0.25 ) );
	}
	h_ntrkdv_n               .push_back( h_njtrkdv_n               );
	h_ntrkdv_z               .push_back( h_njtrkdv_z               );
	h_ntrkdv_z_s             .push_back( h_njtrkdv_z_s             );
	h_ntrkdv_r               .push_back( h_njtrkdv_r               );
	h_ntrkdv_r_s             .push_back( h_njtrkdv_r_s             );
	h_ntrkdv_mass            .push_back( h_njtrkdv_mass            );
	h_ntrkdv_mass_s          .push_back( h_njtrkdv_mass_s          );
	h_ntrkdv_direction       .push_back( h_njtrkdv_direction       );
	h_ntrkdv_minOpAng        .push_back( h_njtrkdv_minOpAng        );
	h_ntrkdv_maxOpAng        .push_back( h_njtrkdv_maxOpAng        );
	h_ntrkdv_chi2            .push_back( h_njtrkdv_chi2            );
	h_ntrkdv_chi2_s          .push_back( h_njtrkdv_chi2_s          );
	h_ntrkdv_sqrterrx        .push_back( h_njtrkdv_sqrterrx        );
	h_ntrkdv_sqrterry        .push_back( h_njtrkdv_sqrterry        );
	h_ntrkdv_sqrterrz        .push_back( h_njtrkdv_sqrterrz        );
	h_ntrkdv_sqrterrr        .push_back( h_njtrkdv_sqrterrr        );
	h_ntrkdv_sqrterrphi      .push_back( h_njtrkdv_sqrterrphi      );
	h_ntrkdv_sumSqrterrd0    .push_back( h_njtrkdv_sumSqrterrd0    );
	h_ntrkdv_sumSqrterrz0    .push_back( h_njtrkdv_sumSqrterrz0    );
	h_ntrkdv_sumSqrterrP     .push_back( h_njtrkdv_sumSqrterrP     );
	h_ntrkdv_sumSqrterrd0_sv .push_back( h_njtrkdv_sumSqrterrd0_sv );
	h_ntrkdv_sumSqrterrz0_sv .push_back( h_njtrkdv_sumSqrterrz0_sv );
	h_ntrkdv_sumSqrterrP_sv  .push_back( h_njtrkdv_sumSqrterrP_sv  );
	h_ntrkdv_minSqrterrd0    .push_back( h_njtrkdv_minSqrterrd0    );
	h_ntrkdv_minSqrterrz0    .push_back( h_njtrkdv_minSqrterrz0    );
	h_ntrkdv_minSqrterrP     .push_back( h_njtrkdv_minSqrterrP     );
	h_ntrkdv_minSqrterrd0_sv .push_back( h_njtrkdv_minSqrterrd0_sv );
	h_ntrkdv_minSqrterrz0_sv .push_back( h_njtrkdv_minSqrterrz0_sv );
	h_ntrkdv_minSqrterrP_sv  .push_back( h_njtrkdv_minSqrterrP_sv  );
	h_ntrkdv_maxSqrterrd0    .push_back( h_njtrkdv_maxSqrterrd0    );
	h_ntrkdv_maxSqrterrz0    .push_back( h_njtrkdv_maxSqrterrz0    );
	h_ntrkdv_maxSqrterrP     .push_back( h_njtrkdv_maxSqrterrP     );
	h_ntrkdv_maxSqrterrd0_sv .push_back( h_njtrkdv_maxSqrterrd0_sv );
	h_ntrkdv_maxSqrterrz0_sv .push_back( h_njtrkdv_maxSqrterrz0_sv );
	h_ntrkdv_maxSqrterrP_sv  .push_back( h_njtrkdv_maxSqrterrP_sv  );
      }
    }
    h_DV_n                      .push_back( h_dv_n                      );
    h_DV_x                      .push_back( h_dv_x                      );
    h_DV_y                      .push_back( h_dv_y                      );
    h_DV_z                      .push_back( h_dv_z                      );
    h_DV_r                      .push_back( h_dv_r                      );
    h_DV_x_s                    .push_back( h_dv_x_s                    );
    h_DV_y_s                    .push_back( h_dv_y_s                    );
    h_DV_z_s                    .push_back( h_dv_z_s                    );
    h_DV_r_s                    .push_back( h_dv_r_s                    );
    h_DV_phipos                 .push_back( h_dv_phipos                 );
    h_DV_pt                     .push_back( h_dv_pt                     );
    h_DV_eta                    .push_back( h_dv_eta                    );
    h_DV_phi                    .push_back( h_dv_phi                    );
    h_DV_mass                   .push_back( h_dv_mass                   );
    h_DV_mass_l                 .push_back( h_dv_mass_l                 );
    h_DV_mass_s                 .push_back( h_dv_mass_s                 );
    h_DV_mass_xs                .push_back( h_dv_mass_xs                );
    h_DV_massNA                 .push_back( h_dv_massNA                 );
    h_DV_massNA_l               .push_back( h_dv_massNA_l               );
    h_DV_massNA_s               .push_back( h_dv_massNA_s               );
    h_DV_massNA_xs              .push_back( h_dv_massNA_xs              );
    h_DV_direction              .push_back( h_dv_direction              );
    h_DV_minOpAng               .push_back( h_dv_minOpAng               );
    h_DV_maxOpAng               .push_back( h_dv_maxOpAng               );
    h_DV_chi2                   .push_back( h_dv_chi2                   );
    h_DV_chi2_s                 .push_back( h_dv_chi2_s                 );
    h_DV_ntrk                   .push_back( h_dv_ntrk                   );
    h_DV_ntrk_final             .push_back( h_dv_ntrk_final             );
    h_DV_ntrk_sel               .push_back( h_dv_ntrk_sel               );
    h_DV_ntrk_assoc             .push_back( h_dv_ntrk_assoc             );
    h_DV_ntrk_lrt               .push_back( h_dv_ntrk_lrt               );
    h_DV_errx                   .push_back( h_dv_errx                   );
    h_DV_erry                   .push_back( h_dv_erry                   );
    h_DV_errz                   .push_back( h_dv_errz                   );
    h_DV_errr                   .push_back( h_dv_errr                   );
    h_DV_errphi                 .push_back( h_dv_errphi                 );
    h_DV_sqrterrx               .push_back( h_dv_sqrterrx               );
    h_DV_sqrterry               .push_back( h_dv_sqrterry               );
    h_DV_sqrterrz               .push_back( h_dv_sqrterrz               );
    h_DV_sqrterrr               .push_back( h_dv_sqrterrr               );
    h_DV_sqrterrphi             .push_back( h_dv_sqrterrphi             );
    h_DV_fracerrx               .push_back( h_dv_fracerrx               );
    h_DV_fracerry               .push_back( h_dv_fracerry               );
    h_DV_fracerrz               .push_back( h_dv_fracerrz               );
    h_DV_fracerrr               .push_back( h_dv_fracerrr               );
    h_DV_fracerrphi             .push_back( h_dv_fracerrphi             );
    h_DV_signifx                .push_back( h_dv_signifx                );
    h_DV_signify                .push_back( h_dv_signify                );
    h_DV_signifz                .push_back( h_dv_signifz                );
    h_DV_signifr                .push_back( h_dv_signifr                );
    h_DV_signifphi              .push_back( h_dv_signifphi              );
    if ( m_histoInfoSwitch->m_vtxTrks ) {
      h_DV_trk_qOverP           .push_back( h_dv_trk_qOverP             );
      h_DV_trk_theta            .push_back( h_dv_trk_theta              );
      h_DV_trk_pt               .push_back( h_dv_trk_pt                 );
      h_DV_trk_eta              .push_back( h_dv_trk_eta                );
      h_DV_trk_phi              .push_back( h_dv_trk_phi                );
      h_DV_trk_d0               .push_back( h_dv_trk_d0                 );
      h_DV_trk_z0               .push_back( h_dv_trk_z0                 );
      h_DV_trk_errd0            .push_back( h_dv_trk_errd0              );
      h_DV_trk_errz0            .push_back( h_dv_trk_errz0              );
      h_DV_trk_sqrterrd0        .push_back( h_dv_trk_sqrterrd0          );
      h_DV_trk_sqrterrz0        .push_back( h_dv_trk_sqrterrz0          );
      h_DV_trk_fracerrd0        .push_back( h_dv_trk_fracerrd0          );
      h_DV_trk_fracerrz0        .push_back( h_dv_trk_fracerrz0          );
      h_DV_trk_signifd0         .push_back( h_dv_trk_signifd0           );
      h_DV_trk_signifz0         .push_back( h_dv_trk_signifz0           );
      h_DV_trk_errP             .push_back( h_dv_trk_errP               );
      h_DV_trk_sqrterrP         .push_back( h_dv_trk_sqrterrP           );
      h_DV_trk_fracerrP         .push_back( h_dv_trk_fracerrP           );
      h_DV_trk_signifP          .push_back( h_dv_trk_signifP            );
      h_DV_trk_chi2             .push_back( h_dv_trk_chi2               );
      h_DV_trk_chiSq            .push_back( h_dv_trk_chiSq              );
      h_DV_trk_qOverP_sv        .push_back( h_dv_trk_qOverP_sv          );
      h_DV_trk_theta_sv         .push_back( h_dv_trk_theta_sv           );
      h_DV_trk_pt_sv            .push_back( h_dv_trk_pt_sv              );
      h_DV_trk_eta_sv           .push_back( h_dv_trk_eta_sv             );
      h_DV_trk_phi_sv           .push_back( h_dv_trk_phi_sv             );
      h_DV_trk_d0_sv            .push_back( h_dv_trk_d0_sv              );
      h_DV_trk_z0_sv            .push_back( h_dv_trk_z0_sv              );
      h_DV_trk_errd0_sv         .push_back( h_dv_trk_errd0_sv           );
      h_DV_trk_errz0_sv         .push_back( h_dv_trk_errz0_sv           );
      h_DV_trk_sqrterrd0_sv     .push_back( h_dv_trk_sqrterrd0_sv       );
      h_DV_trk_sqrterrz0_sv     .push_back( h_dv_trk_sqrterrz0_sv       );
      h_DV_trk_fracerrd0_sv     .push_back( h_dv_trk_fracerrd0_sv       );
      h_DV_trk_fracerrz0_sv     .push_back( h_dv_trk_fracerrz0_sv       );
      h_DV_trk_signifd0_sv      .push_back( h_dv_trk_signifd0_sv        );
      h_DV_trk_signifz0_sv      .push_back( h_dv_trk_signifz0_sv        );
      h_DV_trk_errP_sv          .push_back( h_dv_trk_errP_sv            );
      h_DV_trk_sqrterrP_sv      .push_back( h_dv_trk_sqrterrP_sv        );
      h_DV_trk_fracerrP_sv      .push_back( h_dv_trk_fracerrP_sv        );
      h_DV_trk_signifP_sv       .push_back( h_dv_trk_signifP_sv         );
      h_DV_trk_chi2_sv          .push_back( h_dv_trk_chi2_sv            );
      h_DV_trk_chiSq_sv         .push_back( h_dv_trk_chiSq_sv           );
    }
    h_DV_sumd0                  .push_back( h_dv_sumd0                  );
    h_DV_sumz0                  .push_back( h_dv_sumz0                  );
    h_DV_sumP                   .push_back( h_dv_sumP                   );
    h_DV_sumErrd0               .push_back( h_dv_sumErrd0               );
    h_DV_sumErrz0               .push_back( h_dv_sumErrz0               );
    h_DV_sumErrP                .push_back( h_dv_sumErrP                );
    h_DV_sumSqrterrd0           .push_back( h_dv_sumSqrterrd0           );
    h_DV_sumSqrterrz0           .push_back( h_dv_sumSqrterrz0           );
    h_DV_sumSqrterrP            .push_back( h_dv_sumSqrterrP            );
    h_DV_sumFracerrd0           .push_back( h_dv_sumFracerrd0           );
    h_DV_sumFracerrz0           .push_back( h_dv_sumFracerrz0           );
    h_DV_sumFracerrP            .push_back( h_dv_sumFracerrP            );
    h_DV_sumSignifd0            .push_back( h_dv_sumSignifd0            );
    h_DV_sumSignifz0            .push_back( h_dv_sumSignifz0            );
    h_DV_sumSignifP             .push_back( h_dv_sumSignifP             );
    h_DV_sumd0_sv               .push_back( h_dv_sumd0_sv               );
    h_DV_sumz0_sv               .push_back( h_dv_sumz0_sv               );
    h_DV_sumP_sv                .push_back( h_dv_sumP_sv                );
    h_DV_sumErrd0_sv            .push_back( h_dv_sumErrd0_sv            );
    h_DV_sumErrz0_sv            .push_back( h_dv_sumErrz0_sv            );
    h_DV_sumErrP_sv             .push_back( h_dv_sumErrP_sv             );
    h_DV_sumSqrterrd0_sv        .push_back( h_dv_sumSqrterrd0_sv        );
    h_DV_sumSqrterrz0_sv        .push_back( h_dv_sumSqrterrz0_sv        );
    h_DV_sumSqrterrP_sv         .push_back( h_dv_sumSqrterrP_sv         );
    h_DV_sumFracerrd0_sv        .push_back( h_dv_sumFracerrd0_sv        );
    h_DV_sumFracerrz0_sv        .push_back( h_dv_sumFracerrz0_sv        );
    h_DV_sumFracerrP_sv         .push_back( h_dv_sumFracerrP_sv         );
    h_DV_sumSignifd0_sv         .push_back( h_dv_sumSignifd0_sv         );
    h_DV_sumSignifz0_sv         .push_back( h_dv_sumSignifz0_sv         );
    h_DV_sumSignifP_sv          .push_back( h_dv_sumSignifP_sv          );
    h_DV_mind0                  .push_back( h_dv_mind0                  );
    h_DV_minz0                  .push_back( h_dv_minz0                  );
    h_DV_minP                   .push_back( h_dv_minP                   );
    h_DV_minErrd0               .push_back( h_dv_minErrd0               );
    h_DV_minErrz0               .push_back( h_dv_minErrz0               );
    h_DV_minErrP                .push_back( h_dv_minErrP                );
    h_DV_minSqrterrd0           .push_back( h_dv_minSqrterrd0           );
    h_DV_minSqrterrz0           .push_back( h_dv_minSqrterrz0           );
    h_DV_minSqrterrP            .push_back( h_dv_minSqrterrP            );
    h_DV_minFracerrd0           .push_back( h_dv_minFracerrd0           );
    h_DV_minFracerrz0           .push_back( h_dv_minFracerrz0           );
    h_DV_minFracerrP            .push_back( h_dv_minFracerrP            );
    h_DV_minSignifd0            .push_back( h_dv_minSignifd0            );
    h_DV_minSignifz0            .push_back( h_dv_minSignifz0            );
    h_DV_minSignifP             .push_back( h_dv_minSignifP             );
    h_DV_mind0_sv               .push_back( h_dv_mind0_sv               );
    h_DV_minz0_sv               .push_back( h_dv_minz0_sv               );
    h_DV_minP_sv                .push_back( h_dv_minP_sv                );
    h_DV_minErrd0_sv            .push_back( h_dv_minErrd0_sv            );
    h_DV_minErrz0_sv            .push_back( h_dv_minErrz0_sv            );
    h_DV_minErrP_sv             .push_back( h_dv_minErrP_sv             );
    h_DV_minSqrterrd0_sv        .push_back( h_dv_minSqrterrd0_sv        );
    h_DV_minSqrterrz0_sv        .push_back( h_dv_minSqrterrz0_sv        );
    h_DV_minSqrterrP_sv         .push_back( h_dv_minSqrterrP_sv         );
    h_DV_minFracerrd0_sv        .push_back( h_dv_minFracerrd0_sv        );
    h_DV_minFracerrz0_sv        .push_back( h_dv_minFracerrz0_sv        );
    h_DV_minFracerrP_sv         .push_back( h_dv_minFracerrP_sv         );
    h_DV_minSignifd0_sv         .push_back( h_dv_minSignifd0_sv         );
    h_DV_minSignifz0_sv         .push_back( h_dv_minSignifz0_sv         );
    h_DV_minSignifP_sv          .push_back( h_dv_minSignifP_sv          );
    h_DV_maxd0                  .push_back( h_dv_maxd0                  );
    h_DV_maxz0                  .push_back( h_dv_maxz0                  );
    h_DV_maxP                   .push_back( h_dv_maxP                   );
    h_DV_maxErrd0               .push_back( h_dv_maxErrd0               );
    h_DV_maxErrz0               .push_back( h_dv_maxErrz0               );
    h_DV_maxErrP                .push_back( h_dv_maxErrP                );
    h_DV_maxSqrterrd0           .push_back( h_dv_maxSqrterrd0           );
    h_DV_maxSqrterrz0           .push_back( h_dv_maxSqrterrz0           );
    h_DV_maxSqrterrP            .push_back( h_dv_maxSqrterrP            );
    h_DV_maxFracerrd0           .push_back( h_dv_maxFracerrd0           );
    h_DV_maxFracerrz0           .push_back( h_dv_maxFracerrz0           );
    h_DV_maxFracerrP            .push_back( h_dv_maxFracerrP            );
    h_DV_maxSignifd0            .push_back( h_dv_maxSignifd0            );
    h_DV_maxSignifz0            .push_back( h_dv_maxSignifz0            );
    h_DV_maxSignifP             .push_back( h_dv_maxSignifP             );
    h_DV_maxd0_sv               .push_back( h_dv_maxd0_sv               );
    h_DV_maxz0_sv               .push_back( h_dv_maxz0_sv               );
    h_DV_maxP_sv                .push_back( h_dv_maxP_sv                );
    h_DV_maxErrd0_sv            .push_back( h_dv_maxErrd0_sv            );
    h_DV_maxErrz0_sv            .push_back( h_dv_maxErrz0_sv            );
    h_DV_maxErrP_sv             .push_back( h_dv_maxErrP_sv             );
    h_DV_maxSqrterrd0_sv        .push_back( h_dv_maxSqrterrd0_sv        );
    h_DV_maxSqrterrz0_sv        .push_back( h_dv_maxSqrterrz0_sv        );
    h_DV_maxSqrterrP_sv         .push_back( h_dv_maxSqrterrP_sv         );
    h_DV_maxFracerrd0_sv        .push_back( h_dv_maxFracerrd0_sv        );
    h_DV_maxFracerrz0_sv        .push_back( h_dv_maxFracerrz0_sv        );
    h_DV_maxFracerrP_sv         .push_back( h_dv_maxFracerrP_sv         );
    h_DV_maxSignifd0_sv         .push_back( h_dv_maxSignifd0_sv         );
    h_DV_maxSignifz0_sv         .push_back( h_dv_maxSignifz0_sv         );
    h_DV_maxSignifP_sv          .push_back( h_dv_maxSignifP_sv          );
    h_DV_z_r                    .push_back( h_dv_z_r                    );
    h_DV_mass_r                 .push_back( h_dv_mass_r                 );
    h_DV_z_chi2                 .push_back( h_dv_z_chi2                 );
    h_DV_r_chi2                 .push_back( h_dv_r_chi2                 );
    h_DV_mass_chi2              .push_back( h_dv_mass_chi2              );
    h_DV_z_r_s                  .push_back( h_dv_z_r_s                  );
    h_DV_mass_r_s               .push_back( h_dv_mass_r_s               );
    h_DV_z_chi2_s               .push_back( h_dv_z_chi2_s               );
    h_DV_r_chi2_s               .push_back( h_dv_r_chi2_s               );
    h_DV_mass_chi2_s            .push_back( h_dv_mass_chi2_s            );
    h_DV_errx_x                 .push_back( h_dv_errx_x                 );
    h_DV_erry_y                 .push_back( h_dv_erry_y                 );
    h_DV_errz_z                 .push_back( h_dv_errz_z                 );
    h_DV_errr_r                 .push_back( h_dv_errr_r                 );
    h_DV_errphi_phi             .push_back( h_dv_errphi_phi             );
    h_DV_sqrterrx_x             .push_back( h_dv_sqrterrx_x             );
    h_DV_sqrterry_y             .push_back( h_dv_sqrterry_y             );
    h_DV_sqrterrz_z             .push_back( h_dv_sqrterrz_z             );
    h_DV_sqrterrr_r             .push_back( h_dv_sqrterrr_r             );
    h_DV_sqrterrphi_phi         .push_back( h_dv_sqrterrphi_phi         );
    h_DV_sumErrd0_r             .push_back( h_dv_sumErrd0_r             );
    h_DV_sumErrz0_z             .push_back( h_dv_sumErrz0_z             );
    h_DV_sumErrP_pt             .push_back( h_dv_sumErrP_pt             );
    h_DV_sumSqrterrd0_r         .push_back( h_dv_sumSqrterrd0_r         );
    h_DV_sumSqrterrz0_z         .push_back( h_dv_sumSqrterrz0_z         );
    h_DV_sumSqrterrP_pt         .push_back( h_dv_sumSqrterrP_pt         );
    h_DV_sumErrd0sv_r           .push_back( h_dv_sumErrd0sv_r           );
    h_DV_sumErrz0sv_z           .push_back( h_dv_sumErrz0sv_z           );
    h_DV_sumErrPsv_pt           .push_back( h_dv_sumErrPsv_pt           );
    h_DV_sumSqrterrd0sv_r       .push_back( h_dv_sumSqrterrd0sv_r       );
    h_DV_sumSqrterrz0sv_z       .push_back( h_dv_sumSqrterrz0sv_z       );
    h_DV_sumSqrterrPsv_pt       .push_back( h_dv_sumSqrterrPsv_pt       );
    h_DV_minErrd0_r             .push_back( h_dv_minErrd0_r             );
    h_DV_minErrz0_z             .push_back( h_dv_minErrz0_z             );
    h_DV_minErrP_pt             .push_back( h_dv_minErrP_pt             );
    h_DV_minSqrterrd0_r         .push_back( h_dv_minSqrterrd0_r         );
    h_DV_minSqrterrz0_z         .push_back( h_dv_minSqrterrz0_z         );
    h_DV_minSqrterrP_pt         .push_back( h_dv_minSqrterrP_pt         );
    h_DV_minErrd0sv_r           .push_back( h_dv_minErrd0sv_r           );
    h_DV_minErrz0sv_z           .push_back( h_dv_minErrz0sv_z           );
    h_DV_minErrPsv_pt           .push_back( h_dv_minErrPsv_pt           );
    h_DV_minSqrterrd0sv_r       .push_back( h_dv_minSqrterrd0sv_r       );
    h_DV_minSqrterrz0sv_z       .push_back( h_dv_minSqrterrz0sv_z       );
    h_DV_minSqrterrPsv_pt       .push_back( h_dv_minSqrterrPsv_pt       );
    h_DV_maxErrd0_r             .push_back( h_dv_maxErrd0_r             );
    h_DV_maxErrz0_z             .push_back( h_dv_maxErrz0_z             );
    h_DV_maxErrP_pt             .push_back( h_dv_maxErrP_pt             );
    h_DV_maxSqrterrd0_r         .push_back( h_dv_maxSqrterrd0_r         );
    h_DV_maxSqrterrz0_z         .push_back( h_dv_maxSqrterrz0_z         );
    h_DV_maxSqrterrP_pt         .push_back( h_dv_maxSqrterrP_pt         );
    h_DV_maxErrd0sv_r           .push_back( h_dv_maxErrd0sv_r           );
    h_DV_maxErrz0sv_z           .push_back( h_dv_maxErrz0sv_z           );
    h_DV_maxErrPsv_pt           .push_back( h_dv_maxErrPsv_pt           );
    h_DV_maxSqrterrd0sv_r       .push_back( h_dv_maxSqrterrd0sv_r       );
    h_DV_maxSqrterrz0sv_z       .push_back( h_dv_maxSqrterrz0sv_z       );
    h_DV_maxSqrterrPsv_pt       .push_back( h_dv_maxSqrterrPsv_pt       );
    h_DV_trkd0_r                .push_back( h_dv_trkd0_r                );
    h_DV_trkz0_z                .push_back( h_dv_trkz0_z                );
    h_DV_trkP_pt                .push_back( h_dv_trkP_pt                );
    h_DV_trkErrd0_r             .push_back( h_dv_trkErrd0_r             );
    h_DV_trkErrz0_z             .push_back( h_dv_trkErrz0_z             );
    h_DV_trkErrP_pt             .push_back( h_dv_trkErrP_pt             );
    h_DV_trkSqrterrd0_r         .push_back( h_dv_trkSqrterrd0_r         );
    h_DV_trkSqrterrz0_z         .push_back( h_dv_trkSqrterrz0_z         );
    h_DV_trkSqrterrP_pt         .push_back( h_dv_trkSqrterrP_pt         );
    h_DV_trkd0sv_r              .push_back( h_dv_trkd0sv_r              );
    h_DV_trkz0sv_z              .push_back( h_dv_trkz0sv_z              );
    h_DV_trkPsv_pt              .push_back( h_dv_trkPsv_pt              );
    h_DV_trkErrd0sv_r           .push_back( h_dv_trkErrd0sv_r           );
    h_DV_trkErrz0sv_z           .push_back( h_dv_trkErrz0sv_z           );
    h_DV_trkErrPsv_pt           .push_back( h_dv_trkErrPsv_pt           );
    h_DV_trkSqrterrd0sv_r       .push_back( h_dv_trkSqrterrd0sv_r       );
    h_DV_trkSqrterrz0sv_z       .push_back( h_dv_trkSqrterrz0sv_z       );
    h_DV_trkSqrterrPsv_pt       .push_back( h_dv_trkSqrterrPsv_pt       );
    h_DV_trkErrd0_trkd0         .push_back( h_dv_trkErrd0_trkd0         );
    h_DV_trkErrz0_trkz0         .push_back( h_dv_trkErrz0_trkz0         );
    h_DV_trkErrP_trkP           .push_back( h_dv_trkErrP_trkP           );
    h_DV_trkSqrterrd0_trkd0     .push_back( h_dv_trkSqrterrd0_trkd0     );
    h_DV_trkSqrterrz0_trkz0     .push_back( h_dv_trkSqrterrz0_trkz0     );
    h_DV_trkSqrterrP_trkP       .push_back( h_dv_trkSqrterrP_trkP       );
    h_DV_trkErrd0sv_trkd0sv     .push_back( h_dv_trkErrd0sv_trkd0sv     );
    h_DV_trkErrz0sv_trkz0sv     .push_back( h_dv_trkErrz0sv_trkz0sv     );
    h_DV_trkErrPsv_trkPsv       .push_back( h_dv_trkErrPsv_trkPsv       );
    h_DV_trkSqrterrd0sv_trkd0sv .push_back( h_dv_trkSqrterrd0sv_trkd0sv );
    h_DV_trkSqrterrz0sv_trkz0sv .push_back( h_dv_trkSqrterrz0sv_trkz0sv );
    h_DV_trkSqrterrPsv_trkPsv   .push_back( h_dv_trkSqrterrPsv_trkPsv   );
    if ( m_numVtxTrks ) {
      h_ntrkDV_n                .push_back( h_ntrkdv_n                  );
      h_ntrkDV_z                .push_back( h_ntrkdv_z                  );
      h_ntrkDV_z_s              .push_back( h_ntrkdv_z_s                );
      h_ntrkDV_r                .push_back( h_ntrkdv_r                  );
      h_ntrkDV_r_s              .push_back( h_ntrkdv_r_s                );
      h_ntrkDV_mass             .push_back( h_ntrkdv_mass               );
      h_ntrkDV_mass_s           .push_back( h_ntrkdv_mass_s             );
      h_ntrkDV_direction        .push_back( h_ntrkdv_direction          );
      h_ntrkDV_minOpAng         .push_back( h_ntrkdv_minOpAng           );
      h_ntrkDV_maxOpAng         .push_back( h_ntrkdv_maxOpAng           );
      h_ntrkDV_chi2             .push_back( h_ntrkdv_chi2               );
      h_ntrkDV_chi2_s           .push_back( h_ntrkdv_chi2_s             );
      h_ntrkDV_sqrterrx         .push_back( h_ntrkdv_sqrterrx           );
      h_ntrkDV_sqrterry         .push_back( h_ntrkdv_sqrterry           );
      h_ntrkDV_sqrterrz         .push_back( h_ntrkdv_sqrterrz           );
      h_ntrkDV_sqrterrr         .push_back( h_ntrkdv_sqrterrr           );
      h_ntrkDV_sqrterrphi       .push_back( h_ntrkdv_sqrterrphi         );
      h_ntrkDV_sumSqrterrd0     .push_back( h_ntrkdv_sumSqrterrd0       );
      h_ntrkDV_sumSqrterrz0     .push_back( h_ntrkdv_sumSqrterrz0       );
      h_ntrkDV_sumSqrterrP      .push_back( h_ntrkdv_sumSqrterrP        );
      h_ntrkDV_sumSqrterrd0_sv  .push_back( h_ntrkdv_sumSqrterrd0_sv    );
      h_ntrkDV_sumSqrterrz0_sv  .push_back( h_ntrkdv_sumSqrterrz0_sv    );
      h_ntrkDV_sumSqrterrP_sv   .push_back( h_ntrkdv_sumSqrterrP_sv     );
      h_ntrkDV_minSqrterrd0     .push_back( h_ntrkdv_minSqrterrd0       );
      h_ntrkDV_minSqrterrz0     .push_back( h_ntrkdv_minSqrterrz0       );
      h_ntrkDV_minSqrterrP      .push_back( h_ntrkdv_minSqrterrP        );
      h_ntrkDV_minSqrterrd0_sv  .push_back( h_ntrkdv_minSqrterrd0_sv    );
      h_ntrkDV_minSqrterrz0_sv  .push_back( h_ntrkdv_minSqrterrz0_sv    );
      h_ntrkDV_minSqrterrP_sv   .push_back( h_ntrkdv_minSqrterrP_sv     );
      h_ntrkDV_maxSqrterrd0     .push_back( h_ntrkdv_maxSqrterrd0       );
      h_ntrkDV_maxSqrterrz0     .push_back( h_ntrkdv_maxSqrterrz0       );
      h_ntrkDV_maxSqrterrP      .push_back( h_ntrkdv_maxSqrterrP        );
      h_ntrkDV_maxSqrterrd0_sv  .push_back( h_ntrkdv_maxSqrterrd0_sv    );
      h_ntrkDV_maxSqrterrz0_sv  .push_back( h_ntrkdv_maxSqrterrz0_sv    );
      h_ntrkDV_maxSqrterrP_sv   .push_back( h_ntrkdv_maxSqrterrP_sv     );
    }


    // --- ABCD HISTOS --- //
    // --> add ntrack vertices (i.e. 3+, 4+, 5+ for each vertex type)
    if ( m_histoInfoSwitch->m_abcd ) {
      std::vector<TH2F*> h_abcd_ndv_njetHt;
      for ( size_t i = 0; i != hDV.size(); ++i ) {
	h_abcd_ndv_njetHt .push_back( book( name, "ABCD_n" + hDV.at(i) + "_NJetHt", "Leading N " + m_jetStr + " Jet H_{T} [GeV]",
					    100, njetht_xmin, 3000, "n " + hDVstr.at(i) + "s", 16, -1, 15 ) );
      }
      h_abcd_nDV_njetHt .push_back( h_abcd_ndv_njetHt );
    }


    // --- TRIGGER STUDIES --- //
    if ( m_histoInfoSwitch->m_trigTest ) {
      // nth jet pt distributions
      h_nthJetPt
	.push_back( book( name, "nthJetPt",
			  "nth leading " + hjetStr    + " p_{T} [GeV] (n-" + m_jetStr + "-jet event)",
			  100, 50, 500 ) );
      h_nthJetPt_trig
	.push_back( book( name, "nthJetPt_trig",
			  "nth leading " + hjetStr    + " p_{T} [GeV] (HLT trigger event)",
			  100, 50, 500 ) );
      h_nthJetPt_offTrig
	.push_back( book( name, "nthJetPt_offTrig",
			  "nth leading " + hjetStr    + " p_{T} [GeV] (offline "     + hjetStr    + " trigger event)",
			  100, 50, 500 ) );
      h_nthJetPt_othOffTrig
	.push_back( book( name, "nthJetPt_othOffTrig",
			  "nth leading " + hjetStr    + " p_{T} [GeV] (offline "     + hjetStrOth + " trigger event)",
			  100, 50, 500 ) );
      h_nthJetPt_offTrigJVT
	.push_back( book( name, "nthJetPt_offTrigJVT",
			  "nth leading " + hjetStr    + " p_{T} [GeV] (offline JVT " + hjetStr    + " trigger event)",
			  100, 50, 500 ) );
      h_nthJetPt_othOffTrigJVT
	.push_back( book( name, "nthJetPt_othOffTrigJVT",
			  "nth leading " + hjetStr    + " p_{T} [GeV] (offline JVT " + hjetStrOth + " trigger event)",
			  100, 50, 500 ) );
      
      // trigger efficiency: nthJetPt_trig / nthJetPt
      h_trigEff_nthJetPt
	.push_back( book( name, "trigEff_nthJetPt",
			  "nth leading " + hjetStr + " p_{T} [GeV]",    100, 50, 500 ) );
      h_trigEff_nthJetPt
	.at(ireg)->GetYaxis()->SetTitle( "HLT trigger efficiency" );
      // trigger efficiency: nthJetPt_offTrig / nthJetPt
      h_offTrigEff_nthJetPt
      	.push_back( book( name, "offTrigEff_nthJetPt",
      			  "nth leading " + hjetStr + " p_{T} [GeV]",    100, 50, 500 ) );
      h_offTrigEff_nthJetPt
	.at(ireg)->GetYaxis()->SetTitle( ( "offline " + hjetStr    + " trigger efficiency" ).c_str() );
      // trigger efficiency: nthJetPt_othOffTrig / nthJetPt
      h_othOffTrigEff_nthJetPt
      	.push_back( book( name, "othOffTrigEff_nthJetPt",
      			  "nth leading " + hjetStr + " p_{T} [GeV]",    100, 50, 500 ) );
      h_othOffTrigEff_nthJetPt
	.at(ireg)->GetYaxis()->SetTitle( ( "offline " + hjetStrOth + " trigger efficiency" ).c_str() );
      // trigger efficiency: nthJetPt_offTrigJVT / nthJetPt
      h_offTrigJVTEff_nthJetPt
	.push_back( book( name, "offTrigJVTEff_nthJetPt",
			  "nth leading " + hjetStr + " p_{T} [GeV]",    100, 50, 500 ) );
      h_offTrigJVTEff_nthJetPt
	.at(ireg)->GetYaxis()->SetTitle( ( "offline " + hjetStr    + " JVT trigger efficiency" ).c_str() );
      // trigger efficiency: nthJetPt_othOffTrigJVT / nthJetPt
      h_othOffTrigJVTEff_nthJetPt
	.push_back( book( name, "othOffTrigJVTEff_nthJetPt",
			  "nth leading " + hjetStr + " p_{T} [GeV]",    100, 50, 500 ) );
      h_othOffTrigJVTEff_nthJetPt
	.at(ireg)->GetYaxis()->SetTitle( ( "offline " + hjetStrOth + " JVT trigger efficiency" ).c_str() );
      
      // overall trigger efficiency comparison
      std::vector<std::string> trigEffLabels = { "HLT_4j120",
						 "offline EM 4j120",       "offline PF 4j120",
						 "offline EM 4j120 + JVT", "offline PF 4j120 + JVT" };
      int nTEL = trigEffLabels.size();
      h_triggerEfficiency           .push_back( book( name, "triggerEfficiency",         "", nTEL, 1, nTEL+1 ) );
      h_triggerEfficiency_fourJet   .push_back( book( name, "triggerEfficiency_fourJet", "", nTEL, 1, nTEL+1 ) );
      h_triggerEfficiency_search    .push_back( book( name, "triggerEfficiency_search",  "", nTEL, 1, nTEL+1 ) );
      h_searchTriggerEfficiency     .push_back( book( name, "searchTriggerEfficiency",   "", nTEL, 1, nTEL+1 ) );
      for ( int i = 0; i != nTEL; ++i ) {
	h_triggerEfficiency         .at(ireg)->GetXaxis()->SetBinLabel( i+1, (trigEffLabels.at(i)).c_str() );
	h_triggerEfficiency_fourJet .at(ireg)->GetXaxis()->SetBinLabel( i+1, (trigEffLabels.at(i)).c_str() );
       	h_triggerEfficiency_search  .at(ireg)->GetXaxis()->SetBinLabel( i+1, (trigEffLabels.at(i)).c_str() );
       	h_searchTriggerEfficiency   .at(ireg)->GetXaxis()->SetBinLabel( i+1, (trigEffLabels.at(i)).c_str() );
      }
      h_triggerEfficiency           .at(ireg)->GetYaxis()->SetTitle( "overall trigger efficiency"          );
      h_triggerEfficiency_fourJet   .at(ireg)->GetYaxis()->SetTitle( "four-jet trigger efficiency"         );
      h_triggerEfficiency_search    .at(ireg)->GetYaxis()->SetTitle( "search-region trigger efficiency"    );
      h_searchTriggerEfficiency     .at(ireg)->GetYaxis()->SetTitle( "search-region efficiency vs trigger" );
      
    } // end trigger study
  
  } // end loop over regions

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: execute ( TTree* tree, Long64_t treeEntry, const std::vector<EJsHelper::Region>& regions )
{
  if ( m_debug ) Info( "EJsHistogramManager::execute()", "filling histograms" );

  tree->GetEntry( treeEntry );

  // set weights
  if ( m_mc ) weight = m_mcEventWeight * m_filteff * m_xsec * 1e6 * lumi / m_sumw_init; // --> include pileup? k-factor? branching ratio?
  // --> sum of weights only includes mcEventWeight; rest is just scaling factor we can apply at once to histograms as a whole
    
  // loop over regions + fill histograms
  for ( size_t ireg = 0; ireg != regions.size(); ++ireg ) {
    const EJsHelper::Region region = regions.at(ireg);

    // skip events outside specified region
    if      ( region.type == EJsHelper::SEARCH_MINUS_ONE ) { if ( !m_searchMinusOne ) continue; }
    else if ( region.type == EJsHelper::SEARCH           ) { if ( !m_search         ) continue; }
    else if ( region.type == EJsHelper::VALIDATION       ) { if ( !m_valid          ) continue; }
    else if ( region.type == EJsHelper::SIGNAL           ) { if ( !m_signal || ( !m_mc && !m_unblind ) ) continue; }
    // --> skip signal events in data until we unblind

    bool doHists = true;
    if ( region.type == EJsHelper::SEARCH || region.type == EJsHelper::SEARCH_MINUS_ONE )
      { if ( !m_mc && !m_unblind ) doHists = false; }
    // --> skip search (and search-minus-one) histos (except ABCD) in data for now

    
    // ------------------ //
    // --- EVENT INFO --- //
    // ------------------ //
    if ( doHists ) {
      // pileup
      if ( m_histoInfoSwitch->m_pileup ) {
	h_npv                .at(ireg) ->Fill( m_npv,                weight );
	h_actualMu           .at(ireg) ->Fill( m_actualMu,           weight );
	h_averageMu          .at(ireg) ->Fill( m_averageMu,          weight );
	h_corrActualMu       .at(ireg) ->Fill( m_corrActualMu,       weight );
	h_corrAverageMu      .at(ireg) ->Fill( m_corrAverageMu,      weight );
	h_corrScaleActualMu  .at(ireg) ->Fill( m_corrScaleActualMu,  weight );
	h_corrScaleAverageMu .at(ireg) ->Fill( m_corrScaleAverageMu, weight );
      }
      // primary vertex
      if ( m_histoInfoSwitch->m_pv ) {
	h_pv_x    .at(ireg) ->Fill( m_pv_x,    weight );
	h_pv_y    .at(ireg) ->Fill( m_pv_y,    weight );
	h_pv_z    .at(ireg) ->Fill( m_pv_z,    weight );
	h_pv_r    .at(ireg) ->Fill( m_pv_r,    weight );
	h_pv_phi  .at(ireg) ->Fill( m_pv_phi,  weight );
	h_pv_ntrk .at(ireg) ->Fill( m_pv_ntrk, weight );
      }
      // leading N-jet Ht
      h_njetHt    .at(ireg) ->Fill( m_njetHt,  weight );
    }


    
    // ----------------- //
    // --- RECO JETS --- //
    // ----------------- //
    if ( doHists )
      h_jet_n .at(ireg) ->Fill( m_jet_n );
    
    // loop over jets
    for ( int i = 0; i != m_jet_n; ++i ) {
      
      // get jet four-momentum
      TLorentzVector jet_p4;
      jet_p4.SetPtEtaPhiM( m_jet_pt->at(i), m_jet_eta->at(i), m_jet_phi->at(i), m_jet_M->at(i) );

      if ( !doHists ) continue;
      
      h_jet_pt    .at(ireg) ->Fill( m_jet_pt    ->at(i), weight );
      h_jet_pt_l  .at(ireg) ->Fill( m_jet_pt    ->at(i), weight );
      h_jet_pt_m  .at(ireg) ->Fill( m_jet_pt    ->at(i), weight );
      h_jet_pt_s  .at(ireg) ->Fill( m_jet_pt    ->at(i), weight );
      h_jet_eta   .at(ireg) ->Fill( m_jet_eta   ->at(i), weight );
      h_jet_phi   .at(ireg) ->Fill( m_jet_phi   ->at(i), weight );
      h_jet_E     .at(ireg) ->Fill( m_jet_E     ->at(i), weight );
      h_jet_M     .at(ireg) ->Fill( m_jet_M     ->at(i), weight );
      h_jet_rapid .at(ireg) ->Fill( m_jet_rapid ->at(i), weight );
      // extra jet kinematics
      if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	h_jet_px   .at(ireg) ->Fill( jet_p4.Px(), weight );
	h_jet_py   .at(ireg) ->Fill( jet_p4.Py(), weight );
	h_jet_pz   .at(ireg) ->Fill( jet_p4.Pz(), weight );
	h_jet_Et   .at(ireg) ->Fill( jet_p4.Et(), weight );
	h_jet_Et_m .at(ireg) ->Fill( jet_p4.Et(), weight );
	h_jet_Et_s .at(ireg) ->Fill( jet_p4.Et(), weight );
      }
      
      // matched tracks
      int nJetTrk = m_jet_trk_n->at(i);
      h_jet_nTrk .at(ireg) ->Fill( nJetTrk, weight );
      // loop over matched tracks
      if ( m_histoInfoSwitch->m_jetTrks ) {
	for ( int j = 0; j != nJetTrk; ++j ) {
	  double dR = m_jet_trk_dR ->at(i).at(j);
	  h_jet_trk_dR .at(ireg) ->Fill( dR, weight );
	  h_jet_nTrk_vs_dR .at(ireg) ->Fill( dR, nJetTrk, weight );
	}
      }
      
      // matched secondary vertices
      int nJetDV = m_jet_secVtx_n->at(i);
      h_jet_nDV .at(ireg) ->Fill( nJetDV, weight );
      // loop over matched secondary vertices
      if ( m_histoInfoSwitch->m_jetVerts ) {
	for ( int j = 0; j != nJetDV; ++j ) {
	  double dR = m_jet_secVtx_dR ->at(i).at(j);
	  h_jet_DV_dR .at(ireg) ->Fill( dR, weight );
	  h_jet_nDV_vs_dR .at(ireg) ->Fill( dR, nJetDV, weight );
	}
      }
      
      // leading jets
      if ( m_numLeadJets ) {
	if ( i < m_numLeadJets ) {
	  h_jetN_pt     .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i), weight );
	  h_jetN_pt_l   .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i), weight );
	  h_jetN_pt_m   .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i), weight );
	  h_jetN_pt_s   .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i), weight );
	  h_jetN_eta    .at(ireg).at(i) ->Fill( m_jet_eta   ->at(i), weight );
	  h_jetN_phi    .at(ireg).at(i) ->Fill( m_jet_phi   ->at(i), weight );
	  h_jetN_E      .at(ireg).at(i) ->Fill( m_jet_E     ->at(i), weight );
	  h_jetN_M      .at(ireg).at(i) ->Fill( m_jet_M     ->at(i), weight );
	  h_jetN_rapid  .at(ireg).at(i) ->Fill( m_jet_rapid ->at(i), weight );
	  if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	    h_jetN_Et   .at(ireg).at(i) ->Fill( jet_p4.Et(), weight );
	    h_jetN_Et_m .at(ireg).at(i) ->Fill( jet_p4.Et(), weight );
	    h_jetN_Et_s .at(ireg).at(i) ->Fill( jet_p4.Et(), weight );
	  }
	}
      }
    } // end loop over jets
    
    

    // -------------- //
    // --- TRACKS --- //
    // -------------- //
    if ( doHists )
      h_trk_n .at(ireg) ->Fill( m_trk_n, weight );



    // ---------------------- //
    // --- TRUTH VERTICES --- //
    // ---------------------- //
    if ( m_mc ) {
      if ( doHists )
	h_truthVtx_n .at(ireg) ->Fill( m_truthVtx_n, weight );

      int nTruthVtx_darkPion = 0;
      int nTruthVtx_kshort   = 0;
      int nTruthVtx_other    = 0;
      // loop over truth vertices
      for ( int i = 0; i != m_truthVtx_n; ++i ) {
	
	// look for truth dark pion / k-short decays
	bool truthVtx_isDarkPion = false;
	bool truthVtx_isKshort   = false;
	bool truthVtx_isOther    = false;
	if      ( m_truthVtx_llp ->at(i) == "DarkPion" ) truthVtx_isDarkPion = true;
	else if ( m_truthVtx_llp ->at(i) == "Kshort"   ) truthVtx_isKshort   = true;
	else if ( m_truthVtx_llp ->at(i) == ""         ) truthVtx_isOther    = true;
	
	// truth dark pion decay
	if ( truthVtx_isDarkPion && ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_darkPions ) ) {
	  ++nTruthVtx_darkPion;

	  if ( !doHists ) continue;
	  
	  h_truthDarkPionDecay_x     .at(ireg)->Fill( m_truthVtx_x     ->at(i), weight );
	  h_truthDarkPionDecay_y     .at(ireg)->Fill( m_truthVtx_y     ->at(i), weight );
	  h_truthDarkPionDecay_z     .at(ireg)->Fill( m_truthVtx_z     ->at(i), weight );
	  h_truthDarkPionDecay_r     .at(ireg)->Fill( m_truthVtx_r     ->at(i), weight );
	  h_truthDarkPionDecay_pt    .at(ireg)->Fill( m_truthVtx_pt    ->at(i), weight );
	  h_truthDarkPionDecay_eta   .at(ireg)->Fill( m_truthVtx_eta   ->at(i), weight );
	  h_truthDarkPionDecay_phi   .at(ireg)->Fill( m_truthVtx_phi   ->at(i), weight );
	  h_truthDarkPionDecay_mass  .at(ireg)->Fill( m_truthVtx_mass  ->at(i), weight );
	  h_truthDarkPionDecay_nOutP .at(ireg)->Fill( m_truthVtx_nOutP ->at(i), weight );
	  
	  h_truthDarkPionDecay_nDesc     .at(ireg)->Fill( m_truthVtx_nDesc     ->at(i), weight );
	  h_truthDarkPionDecay_nRecoDesc .at(ireg)->Fill( m_truthVtx_nRecoDesc ->at(i), weight );
	  h_truthDarkPionDecay_nSelDesc  .at(ireg)->Fill( m_truthVtx_nSelDesc  ->at(i), weight );
	  
	  h_truthDarkPionDecay_nPos .at(ireg)->Fill( m_truthVtx_nPos ->at(i), weight );
	}
	// truth k-short decay
	else if ( truthVtx_isKshort && ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_kshorts ) ) {
	  ++nTruthVtx_kshort;

	  if ( !doHists ) continue;
	  
	  h_truthKshortDecay_x     .at(ireg)->Fill( m_truthVtx_x     ->at(i), weight );
	  h_truthKshortDecay_y     .at(ireg)->Fill( m_truthVtx_y     ->at(i), weight );
	  h_truthKshortDecay_z     .at(ireg)->Fill( m_truthVtx_z     ->at(i), weight );
	  h_truthKshortDecay_r     .at(ireg)->Fill( m_truthVtx_r     ->at(i), weight );
	  h_truthKshortDecay_pt    .at(ireg)->Fill( m_truthVtx_pt    ->at(i), weight );
	  h_truthKshortDecay_eta   .at(ireg)->Fill( m_truthVtx_eta   ->at(i), weight );
	  h_truthKshortDecay_phi   .at(ireg)->Fill( m_truthVtx_phi   ->at(i), weight );
	  h_truthKshortDecay_mass  .at(ireg)->Fill( m_truthVtx_mass  ->at(i), weight );
	  h_truthKshortDecay_nOutP .at(ireg)->Fill( m_truthVtx_nOutP ->at(i), weight );
	  
	  h_truthKshortDecay_nDesc     .at(ireg)->Fill( m_truthVtx_nDesc     ->at(i), weight );
	  h_truthKshortDecay_nRecoDesc .at(ireg)->Fill( m_truthVtx_nRecoDesc ->at(i), weight );
	  h_truthKshortDecay_nSelDesc  .at(ireg)->Fill( m_truthVtx_nSelDesc  ->at(i), weight );
	  
	  h_truthKshortDecay_nPos .at(ireg)->Fill( m_truthVtx_nPos ->at(i), weight );
	}
      }

      if ( doHists ) {
	if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_darkPions )
	  h_truthDarkPionDecay_n .at(ireg) ->Fill( nTruthVtx_darkPion, weight );
	if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_kshorts   )
	  h_truthKshortDecay_n   .at(ireg) ->Fill( nTruthVtx_kshort,   weight );
      }
    }



    // -------------------------- //
    // --- SECONDARY VERTICES --- //
    // -------------------------- //
    //h_DV_n             .at(ireg) ->Fill( m_secVtx_n,               weight );
    //h_byJetDV_n        .at(ireg) ->Fill( m_nDV_nearJets,           weight );
    //h_byLeadJetDV_n    .at(ireg) ->Fill( m_nDV_nearLeadJets,       weight );

    // eventually will decide on DV type to use and can make generic "DV" histograms w/ no info switch

    // --> look at fiducial volume cuts
    // --> look at vertices matched to truth dark pion decays
    // --> look at vertex tracks --> figure out WHAT to cut / filter on 

    // set vector of nDV, ntrkDV counters
    std::vector<int> n_DV ( m_nTypeDVs.at(ireg), 0 );
    // set vector of map of ntrkDV counters
    std::vector<std::map<int,int>> n_ntrkDV;
    for ( size_t idv = 0; idv != n_DV.size(); ++idv ) {
      std::map<int,int> ntrkDV;
      if ( m_numVtxTrks ) {
    	for ( int itrk = 1; itrk != m_numVtxTrks; ++itrk )
    	  ntrkDV[itrk+1] = 0;
    	n_ntrkDV .push_back( ntrkDV );
      }
    }
    
    // loop over vertices
    for ( int i = 0; i != m_secVtx_n; ++i ) {

      // set vectors of DV types
      std::vector<int>         DV;
      std::vector<std::string> DVstr;
      
      // test track filtering / DV cleaning
      // --> bare vertices
      bool bareDV = false;
      if ( m_secVtx_ntrk ->at(i) > 1 ) bareDV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_bareVerts ) {
	DV    .push_back( bareDV );
	DVstr .push_back( "bare" );
      }
      // --> clean vertices
      bool cleanDV = false;
      if ( m_secVtx_ntrk_clean ->at(i) > 1 ) cleanDV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_cleanVerts ) {
	DV    .push_back( cleanDV );
	DVstr .push_back( "clean" );
      }
      // --> filtered vertices
      bool filtDV = false;
      if ( m_secVtx_ntrk_filt ->at(i) > 1 ) filtDV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_filtVerts ) {
	DV    .push_back( filtDV );
	DVstr .push_back( "filt" );
      }
      
      // --> vertices near (leading) jets
      bool byJetDV     = false;
      bool byLeadJetDV = false;
      if ( m_secVtx_jetMatched ->at(i) ) byJetDV = true;
      if ( m_secVtx_jetMatched ->at(i) && m_secVtx_jetMatch_index ->at(i) < m_nJets ) byLeadJetDV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_byJetVerts ) {
	DV    .push_back( byJetDV     );
	DV    .push_back( byLeadJetDV ); 
	DVstr .push_back( "byJet"     );
	DVstr .push_back( "byLeadJet" );
      }

      // --> fiducial vertices --> cut on r, z, chi2
      bool fiducDV = false;
      if ( m_secVtx_r    ->at(i) < 300 && fabs( m_secVtx_z ->at(i) ) < 300 &&
	   m_secVtx_chi2 ->at(i) < 5 ) fiducDV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_fiducialVerts ) {
	DV    .push_back( fiducDV    );
	DVstr .push_back( "fiducial" );
      }

      // test truth-matching criteria
      // --> look at match scores, (residual) distances to close(st) / matched vertices; ...
      // ... choose singular best match; compare different match score criteria (no requirement, > 0.5, etc.) for a match; ...
      // ... compare other matching criteria, like distance, matched tracks, etc.
      // --> look into split rate (truth vertices w/ multiple reco matches)
      // --> look at representative truth position reco vertex pointing to
      // --> can have more than one reco vertex matched to truth, but want singular truth matched to reco (right?)
      bool darkPionDV = false;
      bool kshortDV   = false;
      bool nomatchDV  = false;
      if ( m_mc ) {
      	if ( m_secVtx_truth_n ->at(i) ) {
      	  // get truth matches
      	  // --> for now, count every DV "DarkPion" llp decay truth match, regardless of match score, distance, other matches, etc.
      	  // --> will eventually want to choose singular best truth match if more than one ...
      	  // ... and cut on some combination of score, distance, corresponding truth vertex parameters ...
      	  // ... (like number of [reco/selected] descendants, "isReconstructible" flag), etc.
      	  // --> to choose single best match, look at match score first (choose highest), then (residual) distance (choose lowest)
      	  for ( int itruth = 0; itruth != m_secVtx_truth_n ->at(i); ++itruth ) {
	    // matching criteria:
	    // --> v0 = match score > 0; no requirement on number / type of truth matches (may be matched to both multiple llps)
      	    if ( m_secVtx_truth_llp ->at(i).at(itruth) == "DarkPion" ) darkPionDV = true;
      	    if ( m_secVtx_truth_llp ->at(i).at(itruth) == "Kshort"   ) kshortDV   = true;
      	  }
      	}
      	if ( !darkPionDV && !kshortDV ) nomatchDV = true;
	if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_vtxTruth ) {
	  std::vector<int>         mDV     = { darkPionDV,  kshortDV, nomatchDV };
	  std::vector<std::string> mDVstr  = { "darkPion", "kshort", "nomatch"  };
	  std::vector<int>         miDV    = { byJetDV,  byLeadJetDV, fiducDV   };
	  std::vector<std::string> miDVstr = { "byJet", "byLeadJet", "fiducial" };
	  for ( size_t i = 0; i != mDV.size(); ++i ) {
	    DV    .push_back( mDV    .at(i) );
	    DVstr .push_back( mDVstr .at(i) );
	    for ( size_t j = 0; j != miDV.size(); ++j ) {
	      std::string mDVstrs = mDVstr.at(i); mDVstrs[0] = toupper(mDVstrs[0]);
	      DV    .push_back( mDV.at(i)     && miDV.at(j) );
	      DVstr .push_back( miDVstr.at(j)  + mDVstrs    );
	    }
	  }
	}
      }
      
      // --> "good" vertices --> this will eventually be our final version to use for analysis
      // --> --> require clean vertices --> remove "isFinal=false" tracks too (not extrapolated back to DV) ??? ...
      // ... ... (will need to re-compute vertex parameters, if so)
      // --> --> cut on k-short mass window (450-550 MeV) --> cut out all DVs with (bare? 2-track?) mass < 0.55 / 0.6 GeV or so
      // --> --> cut on fiducial volume (r, z < 300mm [check]), chi2 ( < 5 [check])
      // --> --> cut on distance to PV --> need at least a few mm between them to exclude prompt
      // --> --> cut on other discriminating variables gleaned from truth matching studies (like errors)
      
      // loop over DV types and fill histograms
      for ( size_t idv = 0; idv != DV.size(); ++idv ) {
	
      	if ( !DV.at(idv) ) continue;

	++n_DV.at(idv);

	float secVtx_pt       = 0;
	float secVtx_eta      = 0;
	float secVtx_phi      = 0;
	float secVtx_mass     = 0;
	float secVtx_massNA   = 0;
	float secVtx_dir      = 0;
	float secVtx_minOpAng = 0;
	float secVtx_maxOpAng = 0;
	float secVtx_mind0    = 0;
	float secVtx_maxd0    = 0;
	int   secVtx_ntrk     = 0;
	if      ( DVstr.at(idv) == "clean" ) {
	  secVtx_pt       = m_secVtx_pt_clean        ->at(i);
	  secVtx_eta      = m_secVtx_eta_clean       ->at(i);
	  secVtx_phi      = m_secVtx_phi_clean       ->at(i);
	  secVtx_mass     = m_secVtx_mass_clean      ->at(i);
	  secVtx_massNA   = m_secVtx_massNA_clean    ->at(i);
	  secVtx_dir      = m_secVtx_direction_clean ->at(i);
	  secVtx_minOpAng = m_secVtx_minOpAng_clean  ->at(i);
	  secVtx_maxOpAng = m_secVtx_maxOpAng_clean  ->at(i);
	  secVtx_mind0    = m_secVtx_mind0_clean     ->at(i);
	  secVtx_maxd0    = m_secVtx_maxd0_clean     ->at(i);
	  secVtx_ntrk     = m_secVtx_ntrk_clean      ->at(i);
	}
	else if ( DVstr.at(idv) == "filt"  ) {
	  secVtx_pt       = m_secVtx_pt              ->at(i);
	  secVtx_eta      = m_secVtx_eta             ->at(i);
	  secVtx_phi      = m_secVtx_phi             ->at(i);
	  secVtx_mass     = m_secVtx_mass            ->at(i);
	  secVtx_massNA   = m_secVtx_massNA          ->at(i);
	  secVtx_dir      = m_secVtx_direction       ->at(i);
	  secVtx_minOpAng = m_secVtx_minOpAng        ->at(i);
	  secVtx_maxOpAng = m_secVtx_maxOpAng        ->at(i);
	  secVtx_mind0    = m_secVtx_mind0           ->at(i);
	  secVtx_maxd0    = m_secVtx_maxd0           ->at(i);
	  secVtx_ntrk     = m_secVtx_ntrk_filt       ->at(i);
	}
	else {
	  secVtx_pt       = m_secVtx_pt_bare         ->at(i);
	  secVtx_eta      = m_secVtx_eta_bare        ->at(i);
	  secVtx_phi      = m_secVtx_phi_bare        ->at(i);
	  secVtx_mass     = m_secVtx_mass_bare       ->at(i);
	  secVtx_massNA   = m_secVtx_massNA_bare     ->at(i);
	  secVtx_dir      = m_secVtx_direction_bare  ->at(i);
	  secVtx_minOpAng = m_secVtx_minOpAng_bare   ->at(i);
	  secVtx_maxOpAng = m_secVtx_maxOpAng_bare   ->at(i);
	  secVtx_mind0    = m_secVtx_mind0_bare      ->at(i);
	  secVtx_maxd0    = m_secVtx_maxd0_bare      ->at(i);
	  secVtx_ntrk     = m_secVtx_ntrk            ->at(i);
	}

	int ntrk = secVtx_ntrk;
	if ( m_numVtxTrks ) {
	  if ( ntrk >= m_numVtxTrks ) ntrk = m_numVtxTrks;
	  ++n_ntrkDV.at(idv)[ntrk];
	}

	const TVector3 secVtx_pos( m_secVtx_x ->at(i), m_secVtx_y ->at(i), m_secVtx_z ->at(i) );

	if ( !doHists ) continue;
	
      	h_DV_x         .at(ireg).at(idv) ->Fill( m_secVtx_x    ->at(i), weight );
      	h_DV_y         .at(ireg).at(idv) ->Fill( m_secVtx_y    ->at(i), weight );
      	h_DV_z         .at(ireg).at(idv) ->Fill( m_secVtx_z    ->at(i), weight );
      	h_DV_r         .at(ireg).at(idv) ->Fill( m_secVtx_r    ->at(i), weight );
	h_DV_x_s       .at(ireg).at(idv) ->Fill( m_secVtx_x    ->at(i), weight );
	h_DV_y_s       .at(ireg).at(idv) ->Fill( m_secVtx_y    ->at(i), weight );
	h_DV_z_s       .at(ireg).at(idv) ->Fill( m_secVtx_z    ->at(i), weight );
	h_DV_r_s       .at(ireg).at(idv) ->Fill( m_secVtx_r    ->at(i), weight );
	h_DV_phipos    .at(ireg).at(idv) ->Fill( secVtx_pos     .Phi(), weight );
	h_DV_pt        .at(ireg).at(idv) ->Fill( secVtx_pt,             weight );
	h_DV_eta       .at(ireg).at(idv) ->Fill( secVtx_eta,            weight );
	h_DV_phi       .at(ireg).at(idv) ->Fill( secVtx_phi,            weight );
	h_DV_mass      .at(ireg).at(idv) ->Fill( secVtx_mass,           weight );
	h_DV_mass_l    .at(ireg).at(idv) ->Fill( secVtx_mass,           weight );
	h_DV_mass_s    .at(ireg).at(idv) ->Fill( secVtx_mass,           weight );
	h_DV_mass_xs   .at(ireg).at(idv) ->Fill( secVtx_mass,           weight );
	h_DV_massNA    .at(ireg).at(idv) ->Fill( secVtx_massNA,         weight );
	h_DV_massNA_l  .at(ireg).at(idv) ->Fill( secVtx_massNA,         weight );
	h_DV_massNA_s  .at(ireg).at(idv) ->Fill( secVtx_massNA,         weight );
	h_DV_massNA_xs .at(ireg).at(idv) ->Fill( secVtx_massNA,         weight );
	h_DV_direction .at(ireg).at(idv) ->Fill( secVtx_dir,            weight ); // cos-phi, phi = ang. b/w vtx pos + track sum-p4 vectors
	h_DV_minOpAng  .at(ireg).at(idv) ->Fill( secVtx_minOpAng,       weight ); // wrt SV
	h_DV_maxOpAng  .at(ireg).at(idv) ->Fill( secVtx_maxOpAng,       weight );
	h_DV_chi2      .at(ireg).at(idv) ->Fill( m_secVtx_chi2 ->at(i), weight );
	h_DV_chi2_s    .at(ireg).at(idv) ->Fill( m_secVtx_chi2 ->at(i), weight );
	h_DV_ntrk      .at(ireg).at(idv) ->Fill( secVtx_ntrk,           weight );
	// --> look at mass_selected (is this the same as non-associated? check), mass_LRT
	// --> --> need to calculate sumP4 using only tracks of interest

	// 2d plots
	h_DV_z_r         .at(ireg).at(idv) ->Fill( m_secVtx_r    ->at(i), m_secVtx_z    ->at(i), weight );
	h_DV_mass_r      .at(ireg).at(idv) ->Fill( m_secVtx_r    ->at(i), m_secVtx_mass ->at(i), weight );
	h_DV_z_chi2      .at(ireg).at(idv) ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_z    ->at(i), weight );
	h_DV_r_chi2      .at(ireg).at(idv) ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_r    ->at(i), weight );
	h_DV_mass_chi2   .at(ireg).at(idv) ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_mass ->at(i), weight );
	h_DV_z_r_s       .at(ireg).at(idv) ->Fill( m_secVtx_r    ->at(i), m_secVtx_z    ->at(i), weight );
	h_DV_mass_r_s    .at(ireg).at(idv) ->Fill( m_secVtx_r    ->at(i), m_secVtx_mass ->at(i), weight );
	h_DV_z_chi2_s    .at(ireg).at(idv) ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_z    ->at(i), weight );
	h_DV_r_chi2_s    .at(ireg).at(idv) ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_r    ->at(i), weight );
	h_DV_mass_chi2_s .at(ireg).at(idv) ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_mass ->at(i), weight );

	// squared errors
	float secVtx_x2     = pow( m_secVtx_x ->at(i), 2 );
	float secVtx_y2     = pow( m_secVtx_y ->at(i), 2 );
	float secVtx_r2     = pow( m_secVtx_r ->at(i), 2 );
	float secVtx_xy     = m_secVtx_x ->at(i) * m_secVtx_y ->at(i);
	float secVtx_errx   = m_secVtx_covariance ->at(i).at(0);
	float secVtx_errxy  = m_secVtx_covariance ->at(i).at(1); // xz=3, xz=4
	float secVtx_erry   = m_secVtx_covariance ->at(i).at(2);
	float secVtx_errz   = m_secVtx_covariance ->at(i).at(5);
	float secVtx_errr   = ( secVtx_x2 * secVtx_errx + secVtx_y2 * secVtx_erry + 2 * secVtx_xy * secVtx_errxy ) / secVtx_r2;
	float secVtx_errphi = ( secVtx_y2 * secVtx_errx + secVtx_x2 * secVtx_erry - 2 * secVtx_xy * secVtx_errxy ) / pow( secVtx_r2, 2 );
	h_DV_errx           .at(ireg).at(idv) ->Fill( sqrt(secVtx_errx),                                    weight );
	h_DV_erry           .at(ireg).at(idv) ->Fill( sqrt(secVtx_erry),                                    weight );
	h_DV_errz           .at(ireg).at(idv) ->Fill( sqrt(secVtx_errz),                                    weight );
	h_DV_errr           .at(ireg).at(idv) ->Fill( sqrt(secVtx_errr),                                    weight );
	h_DV_errphi         .at(ireg).at(idv) ->Fill( sqrt(secVtx_errphi),                                  weight );
	h_DV_sqrterrx       .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_errx)),                              weight );
	h_DV_sqrterry       .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_erry)),                              weight );
	h_DV_sqrterrz       .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_errz)),                              weight );
	h_DV_sqrterrr       .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_errr)),                              weight );
	h_DV_sqrterrphi     .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_errphi)),                            weight );
	h_DV_fracerrx       .at(ireg).at(idv) ->Fill( sqrt(secVtx_errx)        / fabs(m_secVtx_x ->at(i)),  weight );
	h_DV_fracerry       .at(ireg).at(idv) ->Fill( sqrt(secVtx_erry)        / fabs(m_secVtx_y ->at(i)),  weight );
	h_DV_fracerrz       .at(ireg).at(idv) ->Fill( sqrt(secVtx_errz)        / fabs(m_secVtx_z ->at(i)),  weight );
	h_DV_fracerrr       .at(ireg).at(idv) ->Fill( sqrt(secVtx_errr)        / fabs(m_secVtx_r ->at(i)),  weight );
	h_DV_fracerrphi     .at(ireg).at(idv) ->Fill( sqrt(secVtx_errphi)      / fabs(secVtx_pos  .Phi()),  weight );
	h_DV_signifx        .at(ireg).at(idv) ->Fill( fabs(m_secVtx_x ->at(i)) / sqrt(secVtx_errx),         weight );
	h_DV_signify        .at(ireg).at(idv) ->Fill( fabs(m_secVtx_y ->at(i)) / sqrt(secVtx_erry),         weight );
	h_DV_signifz        .at(ireg).at(idv) ->Fill( fabs(m_secVtx_z ->at(i)) / sqrt(secVtx_errz),         weight );
	h_DV_signifr        .at(ireg).at(idv) ->Fill( fabs(m_secVtx_r ->at(i)) / sqrt(secVtx_errr),         weight );
	h_DV_signifphi      .at(ireg).at(idv) ->Fill( fabs(secVtx_pos  .Phi()) / sqrt(secVtx_errphi),       weight );
	h_DV_errx_x         .at(ireg).at(idv) ->Fill( m_secVtx_x ->at(i),        sqrt(secVtx_errx),         weight );
	h_DV_erry_y         .at(ireg).at(idv) ->Fill( m_secVtx_y ->at(i),        sqrt(secVtx_erry),         weight );
	h_DV_errz_z         .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i),        sqrt(secVtx_errz),         weight );
	h_DV_errr_r         .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i),        sqrt(secVtx_errr),         weight );
	h_DV_errphi_phi     .at(ireg).at(idv) ->Fill( secVtx_pos  .Phi(),        sqrt(secVtx_errphi),       weight );
	h_DV_sqrterrx_x     .at(ireg).at(idv) ->Fill( m_secVtx_x ->at(i),        sqrt(sqrt(secVtx_errx)),   weight );
	h_DV_sqrterry_y     .at(ireg).at(idv) ->Fill( m_secVtx_y ->at(i),        sqrt(sqrt(secVtx_erry)),   weight );
	h_DV_sqrterrz_z     .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i),        sqrt(sqrt(secVtx_errz)),   weight );
	h_DV_sqrterrr_r     .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i),        sqrt(sqrt(secVtx_errr)),   weight );
	h_DV_sqrterrphi_phi .at(ireg).at(idv) ->Fill( secVtx_pos  .Phi(),        sqrt(sqrt(secVtx_errphi)), weight );
	
	// loop over vertex tracks
	int   ntrk_final             = 0;
	int   ntrk_sel               = 0;
	int   ntrk_assoc             = 0;
	int   ntrk_lrt               = 0;
	float secVtx_sumd0           = 0;
	float secVtx_sumz0           = 0;
	float secVtx_sumP            = 0;
	float secVtx_sumd0_sv        = 0;
	float secVtx_sumz0_sv        = 0;
	float secVtx_sumP_sv         = 0;
	float secVtx_sumerrd0        = 0;
	float secVtx_sumerrz0        = 0;
	float secVtx_sumerrP         = 0;
	float secVtx_sumerrd0_sv     = 0;
	float secVtx_sumerrz0_sv     = 0;
	float secVtx_sumerrP_sv      = 0;
	float secVtx_sumfracerrd0    = 0;
	float secVtx_sumfracerrz0    = 0;
	float secVtx_sumfracerrP     = 0;
	float secVtx_sumfracerrd0_sv = 0;
	float secVtx_sumfracerrz0_sv = 0;
	float secVtx_sumfracerrP_sv  = 0;
	float secVtx_sumsignifd0     = 0;
	float secVtx_sumsignifz0     = 0;
	float secVtx_sumsignifP      = 0;
	float secVtx_sumsignifd0_sv  = 0;
	float secVtx_sumsignifz0_sv  = 0;
	float secVtx_sumsignifP_sv   = 0;
	float secVtx_minz0           = AlgConsts::maxValue;
	float secVtx_minP            = AlgConsts::maxValue;
	float secVtx_mind0_sv        = AlgConsts::maxValue;
	float secVtx_minz0_sv        = AlgConsts::maxValue;
	float secVtx_minP_sv         = AlgConsts::maxValue;
	float secVtx_minerrd0        = AlgConsts::maxValue;
	float secVtx_minerrz0        = AlgConsts::maxValue;
	float secVtx_minerrP         = AlgConsts::maxValue;
	float secVtx_minerrd0_sv     = AlgConsts::maxValue;
	float secVtx_minerrz0_sv     = AlgConsts::maxValue;
	float secVtx_minerrP_sv      = AlgConsts::maxValue;
	float secVtx_minfracerrd0    = AlgConsts::maxValue;
	float secVtx_minfracerrz0    = AlgConsts::maxValue;
	float secVtx_minfracerrP     = AlgConsts::maxValue;
	float secVtx_minfracerrd0_sv = AlgConsts::maxValue;
	float secVtx_minfracerrz0_sv = AlgConsts::maxValue;
	float secVtx_minfracerrP_sv  = AlgConsts::maxValue;
	float secVtx_minsignifd0     = AlgConsts::maxValue;
	float secVtx_minsignifz0     = AlgConsts::maxValue;
	float secVtx_minsignifP      = AlgConsts::maxValue;
	float secVtx_minsignifd0_sv  = AlgConsts::maxValue;
	float secVtx_minsignifz0_sv  = AlgConsts::maxValue;
	float secVtx_minsignifP_sv   = AlgConsts::maxValue;
	float secVtx_maxz0           = 0;
	float secVtx_maxP            = 0;
	float secVtx_maxd0_sv        = 0;
	float secVtx_maxz0_sv        = 0;
	float secVtx_maxP_sv         = 0;
	float secVtx_maxerrd0        = 0;
	float secVtx_maxerrz0        = 0;
	float secVtx_maxerrP         = 0;
	float secVtx_maxerrd0_sv     = 0;
	float secVtx_maxerrz0_sv     = 0;
	float secVtx_maxerrP_sv      = 0;
	float secVtx_maxfracerrd0    = 0;
	float secVtx_maxfracerrz0    = 0;
	float secVtx_maxfracerrP     = 0;
	float secVtx_maxfracerrd0_sv = 0;
	float secVtx_maxfracerrz0_sv = 0;
	float secVtx_maxfracerrP_sv  = 0;
	float secVtx_maxsignifd0     = 0;
	float secVtx_maxsignifz0     = 0;
	float secVtx_maxsignifP      = 0;
	float secVtx_maxsignifd0_sv  = 0;
	float secVtx_maxsignifz0_sv  = 0;
	float secVtx_maxsignifP_sv   = 0;
	for ( int j = 0; j != m_secVtx_ntrk ->at(i); ++ j ) {
	  if ( DVstr.at(idv) == "clean" && !m_secVtx_trk_isClean ->at(i).at(j) ) continue;
	  if ( DVstr.at(idv) == "filt"  && !m_secVtx_trk_isFilt  ->at(i).at(j) ) continue;

	  int trkIx = m_secVtx_trk_index ->at(i).at(j);

	  float trk_theta_sv  = 2 * atan( exp( -1 * m_secVtx_trk_eta_sv ->at(i).at(j) ) ); // eta = -ln(tan(theta/2))
	  float trk_p_sv      = m_secVtx_trk_pt_sv ->at(i).at(j) / sin( trk_theta_sv );    // pt  =  p*sin(theta)
	  float trk_qOverP_sv = m_trk_charge ->at(trkIx) / trk_p_sv;
	  float trk_chi2_sv   = m_secVtx_trk_chi2_sv ->at(i).at(j) / m_trk_ndof ->at(trkIx);

	  // squared errors
	  float trk_errd0     = m_trk_errd0              ->at(trkIx);
	  float trk_errz0     = m_trk_errz0              ->at(trkIx);
	  float trk_errP      = m_trk_errP               ->at(trkIx)   * 1e6;
	  float trk_errd0_sv  = m_secVtx_trk_errd0_sv    ->at(i).at(j);
	  float trk_errz0_sv  = m_secVtx_trk_errz0_sv    ->at(i).at(j);
	  float trk_errP_sv   = m_secVtx_trk_errP_sv     ->at(i).at(j) * 1e6;
	  // squared fractional errors
	  float trk_fracerrd0    = trk_errd0    / pow(m_trk_d0           ->at(trkIx),        2);
	  float trk_fracerrz0    = trk_errz0    / pow(m_trk_z0           ->at(trkIx),        2);
	  float trk_fracerrP     = trk_errP     / pow(m_trk_qOverP       ->at(trkIx) * 1000, 2);
	  float trk_fracerrd0_sv = trk_errd0_sv / pow(m_secVtx_trk_d0_sv ->at(i).at(j),      2);
	  float trk_fracerrz0_sv = trk_errz0_sv / pow(m_secVtx_trk_z0_sv ->at(i).at(j),      2);
	  float trk_fracerrP_sv  = trk_errP_sv  / pow(trk_qOverP_sv,                         2);
	  
	  if ( m_histoInfoSwitch->m_vtxTrks ) {
	    h_DV_trk_qOverP        .at(ireg).at(idv) ->Fill( 1000 * m_trk_qOverP  ->at(trkIx),   weight );
	    h_DV_trk_theta         .at(ireg).at(idv) ->Fill( m_trk_theta          ->at(trkIx),   weight );
	    h_DV_trk_pt            .at(ireg).at(idv) ->Fill( m_trk_pt             ->at(trkIx),   weight );
	    h_DV_trk_eta           .at(ireg).at(idv) ->Fill( m_trk_eta            ->at(trkIx),   weight );
	    h_DV_trk_phi           .at(ireg).at(idv) ->Fill( m_trk_phi            ->at(trkIx),   weight );
	    h_DV_trk_d0            .at(ireg).at(idv) ->Fill( m_trk_d0             ->at(trkIx),   weight );
	    h_DV_trk_z0            .at(ireg).at(idv) ->Fill( m_trk_z0             ->at(trkIx),   weight );
	    h_DV_trk_errd0         .at(ireg).at(idv) ->Fill( sqrt(trk_errd0),                    weight );
	    h_DV_trk_errz0         .at(ireg).at(idv) ->Fill( sqrt(trk_errz0),                    weight );
	    h_DV_trk_sqrterrd0     .at(ireg).at(idv) ->Fill( sqrt(sqrt(trk_errd0)),              weight );
	    h_DV_trk_sqrterrz0     .at(ireg).at(idv) ->Fill( sqrt(sqrt(trk_errz0)),              weight );
	    h_DV_trk_fracerrd0     .at(ireg).at(idv) ->Fill( sqrt(trk_fracerrd0),                weight );
	    h_DV_trk_fracerrz0     .at(ireg).at(idv) ->Fill( sqrt(trk_fracerrz0),                weight );
	    h_DV_trk_signifd0      .at(ireg).at(idv) ->Fill( 1/sqrt(trk_fracerrd0),              weight );
	    h_DV_trk_signifz0      .at(ireg).at(idv) ->Fill( 1/sqrt(trk_fracerrz0),              weight );
	    h_DV_trk_errP          .at(ireg).at(idv) ->Fill( sqrt(trk_errP),                     weight );
	    h_DV_trk_sqrterrP      .at(ireg).at(idv) ->Fill( sqrt(sqrt(trk_errP)),               weight );
	    h_DV_trk_fracerrP      .at(ireg).at(idv) ->Fill( sqrt(trk_fracerrP),                 weight );
	    h_DV_trk_signifP       .at(ireg).at(idv) ->Fill( 1/sqrt(trk_fracerrP),               weight );
	    h_DV_trk_chi2          .at(ireg).at(idv) ->Fill( m_trk_chi2           ->at(trkIx),   weight );
	    h_DV_trk_chiSq         .at(ireg).at(idv) ->Fill( m_trk_chiSq          ->at(trkIx),   weight );
	    h_DV_trk_qOverP_sv     .at(ireg).at(idv) ->Fill( trk_qOverP_sv,                      weight );
	    h_DV_trk_theta_sv      .at(ireg).at(idv) ->Fill( trk_theta_sv,                       weight );
	    h_DV_trk_pt_sv         .at(ireg).at(idv) ->Fill( m_secVtx_trk_pt_sv   ->at(i).at(j), weight );
	    h_DV_trk_eta_sv        .at(ireg).at(idv) ->Fill( m_secVtx_trk_eta_sv  ->at(i).at(j), weight );
	    h_DV_trk_phi_sv        .at(ireg).at(idv) ->Fill( m_secVtx_trk_phi_sv  ->at(i).at(j), weight );
	    h_DV_trk_d0_sv         .at(ireg).at(idv) ->Fill( m_secVtx_trk_d0_sv   ->at(i).at(j), weight );
	    h_DV_trk_z0_sv         .at(ireg).at(idv) ->Fill( m_secVtx_trk_z0_sv   ->at(i).at(j), weight );
	    h_DV_trk_errd0_sv      .at(ireg).at(idv) ->Fill( sqrt(trk_errd0_sv),                 weight );
	    h_DV_trk_errz0_sv      .at(ireg).at(idv) ->Fill( sqrt(trk_errz0_sv),                 weight );
	    h_DV_trk_sqrterrd0_sv  .at(ireg).at(idv) ->Fill( sqrt(sqrt(trk_errd0_sv)),           weight );
	    h_DV_trk_sqrterrz0_sv  .at(ireg).at(idv) ->Fill( sqrt(sqrt(trk_errz0_sv)),           weight );
	    h_DV_trk_fracerrd0_sv  .at(ireg).at(idv) ->Fill( sqrt(trk_fracerrd0_sv),             weight );
	    h_DV_trk_fracerrz0_sv  .at(ireg).at(idv) ->Fill( sqrt(trk_fracerrz0_sv),             weight );
	    h_DV_trk_signifd0_sv   .at(ireg).at(idv) ->Fill( 1/sqrt(trk_fracerrd0_sv),           weight );
	    h_DV_trk_signifz0_sv   .at(ireg).at(idv) ->Fill( 1/sqrt(trk_fracerrz0_sv),           weight );
	    h_DV_trk_errP_sv       .at(ireg).at(idv) ->Fill( sqrt(trk_errP_sv),                  weight );
	    h_DV_trk_sqrterrP_sv   .at(ireg).at(idv) ->Fill( sqrt(sqrt(trk_errP_sv)),            weight );
	    h_DV_trk_fracerrP_sv   .at(ireg).at(idv) ->Fill( sqrt(trk_fracerrP_sv),              weight );
	    h_DV_trk_signifP_sv    .at(ireg).at(idv) ->Fill( 1/sqrt(trk_fracerrP_sv),            weight );
	    h_DV_trk_chi2_sv       .at(ireg).at(idv) ->Fill( trk_chi2_sv,                        weight );
	    h_DV_trk_chiSq_sv      .at(ireg).at(idv) ->Fill( m_secVtx_trk_chi2_sv ->at(i).at(j), weight );
	  }

	  // count track types
	  if ( m_secVtx_trk_isFinal ->at(i).at(j) ) ++ntrk_final;
	  if ( m_secVtx_trk_isSel   ->at(i).at(j) ) ++ntrk_sel;
	  if ( m_secVtx_trk_isAssoc ->at(i).at(j) ) ++ntrk_assoc;
	  if ( m_trk_isLRT          ->at(trkIx)   ) ++ntrk_lrt;
	  
	  // sum vertex track parameters
	  // --> all tracks
	  secVtx_sumd0           += fabs(m_trk_d0           ->at(trkIx));
	  secVtx_sumz0           += fabs(m_trk_z0           ->at(trkIx));
	  secVtx_sumP            += fabs(m_trk_qOverP       ->at(trkIx) * 1000);
	  secVtx_sumd0_sv        += fabs(m_secVtx_trk_d0_sv ->at(i).at(j));
	  secVtx_sumz0_sv        += fabs(m_secVtx_trk_z0_sv ->at(i).at(j));
	  secVtx_sumP_sv         += fabs(trk_qOverP_sv);
	  secVtx_sumerrd0        += trk_errd0;
	  secVtx_sumerrz0        += trk_errz0;
	  secVtx_sumerrP         += trk_errP;
	  secVtx_sumerrd0_sv     += trk_errd0_sv;
	  secVtx_sumerrz0_sv     += trk_errz0_sv;
	  secVtx_sumerrP_sv      += trk_errP_sv;
	  secVtx_sumfracerrd0    += trk_fracerrd0;
	  secVtx_sumfracerrz0    += trk_fracerrz0;
	  secVtx_sumfracerrP     += trk_fracerrP;
	  secVtx_sumfracerrd0_sv += trk_fracerrd0_sv;
	  secVtx_sumfracerrz0_sv += trk_fracerrz0_sv;
	  secVtx_sumfracerrP_sv  += trk_fracerrP_sv;
	  secVtx_sumsignifd0     += 1/trk_fracerrd0;
	  secVtx_sumsignifz0     += 1/trk_fracerrz0;
	  secVtx_sumsignifP      += 1/trk_fracerrP;
	  secVtx_sumsignifd0_sv  += 1/trk_fracerrd0_sv;
	  secVtx_sumsignifz0_sv  += 1/trk_fracerrz0_sv;
	  secVtx_sumsignifP_sv   += 1/trk_fracerrP_sv;
	  // --> final tracks
	  // --> selected tracks
	  // --> associated tracks
	  // --> chi2 (prob min/max only; not sum)
	  // --> vs r, z, mass, d0/z0/P, etc.
	  
	  // find min/max track parameters
	  // --> d0, z0, q/p
	  float fabsz0    = fabs( m_trk_z0           ->at(trkIx)   );
	  float fabsP     = fabs( 1000*m_trk_qOverP  ->at(trkIx)   );
	  float fabsd0_sv = fabs( m_secVtx_trk_d0_sv ->at(i).at(j) );
	  float fabsz0_sv = fabs( m_secVtx_trk_z0_sv ->at(i).at(j) );
	  float fabsP_sv  = fabs( trk_qOverP_sv                    );
	  if ( fabsz0             < secVtx_minz0           ) secVtx_minz0           = fabsz0;
	  if ( fabsP              < secVtx_minP            ) secVtx_minP            = fabsP;
	  if ( fabsd0_sv          < secVtx_mind0_sv        ) secVtx_mind0_sv        = fabsd0_sv;
	  if ( fabsz0_sv          < secVtx_minz0_sv        ) secVtx_minz0_sv        = fabsz0_sv;
	  if ( fabsP_sv           < secVtx_minP_sv         ) secVtx_minP_sv         = fabsP_sv;
	  if ( fabsz0             > secVtx_maxz0           ) secVtx_maxz0           = fabsz0;
	  if ( fabsP              > secVtx_maxP            ) secVtx_maxP            = fabsP;
	  if ( fabsd0_sv          > secVtx_maxd0_sv        ) secVtx_maxd0_sv        = fabsd0_sv;
	  if ( fabsz0_sv          > secVtx_maxz0_sv        ) secVtx_maxz0_sv        = fabsz0_sv;
	  if ( fabsP_sv           > secVtx_maxP_sv         ) secVtx_maxP_sv         = fabsP_sv;
	  // --> errors
	  if ( trk_errd0          < secVtx_minerrd0        ) secVtx_minerrd0        = trk_errd0;
	  if ( trk_errz0          < secVtx_minerrz0        ) secVtx_minerrz0        = trk_errz0;
	  if ( trk_errP           < secVtx_minerrP         ) secVtx_minerrP         = trk_errP;
	  if ( trk_errd0_sv       < secVtx_minerrd0_sv     ) secVtx_minerrd0_sv     = trk_errd0_sv;
	  if ( trk_errz0_sv       < secVtx_minerrz0_sv     ) secVtx_minerrz0_sv     = trk_errz0_sv;
	  if ( trk_errP_sv        < secVtx_minerrP_sv      ) secVtx_minerrP_sv      = trk_errP_sv;
	  if ( trk_errd0          > secVtx_maxerrd0        ) secVtx_maxerrd0        = trk_errd0;
	  if ( trk_errz0          > secVtx_maxerrz0        ) secVtx_maxerrz0        = trk_errz0;
	  if ( trk_errP           > secVtx_maxerrP         ) secVtx_maxerrP         = trk_errP;
	  if ( trk_errd0_sv       > secVtx_maxerrd0_sv     ) secVtx_maxerrd0_sv     = trk_errd0_sv;
	  if ( trk_errz0_sv       > secVtx_maxerrz0_sv     ) secVtx_maxerrz0_sv     = trk_errz0_sv;
	  if ( trk_errP_sv        > secVtx_maxerrP_sv      ) secVtx_maxerrP_sv      = trk_errP_sv;
	  // --> fractional errors
	  if ( trk_fracerrd0      < secVtx_minfracerrd0    ) secVtx_minfracerrd0    = trk_fracerrd0;
	  if ( trk_fracerrz0      < secVtx_minfracerrz0    ) secVtx_minfracerrz0    = trk_fracerrz0;
	  if ( trk_fracerrP       < secVtx_minfracerrP     ) secVtx_minfracerrP     = trk_fracerrP;
	  if ( trk_fracerrd0_sv   < secVtx_minfracerrd0_sv ) secVtx_minfracerrd0_sv = trk_fracerrd0_sv;
	  if ( trk_fracerrz0_sv   < secVtx_minfracerrz0_sv ) secVtx_minfracerrz0_sv = trk_fracerrz0_sv;
	  if ( trk_fracerrP_sv    < secVtx_minfracerrP_sv  ) secVtx_minfracerrP_sv  = trk_fracerrP_sv;
	  if ( trk_fracerrd0      > secVtx_maxfracerrd0    ) secVtx_maxfracerrd0    = trk_fracerrd0;
	  if ( trk_fracerrz0      > secVtx_maxfracerrz0    ) secVtx_maxfracerrz0    = trk_fracerrz0;
	  if ( trk_fracerrP       > secVtx_maxfracerrP     ) secVtx_maxfracerrP     = trk_fracerrP;
	  if ( trk_fracerrd0_sv   > secVtx_maxfracerrd0_sv ) secVtx_maxfracerrd0_sv = trk_fracerrd0_sv;
	  if ( trk_fracerrz0_sv   > secVtx_maxfracerrz0_sv ) secVtx_maxfracerrz0_sv = trk_fracerrz0_sv;
	  if ( trk_fracerrP_sv    > secVtx_maxfracerrP_sv  ) secVtx_maxfracerrP_sv  = trk_fracerrP_sv;
	  // --> significances
	  if ( 1/trk_fracerrd0    < secVtx_minsignifd0     ) secVtx_minsignifd0     = 1/trk_fracerrd0;
	  if ( 1/trk_fracerrz0    < secVtx_minsignifz0     ) secVtx_minsignifz0     = 1/trk_fracerrz0;
	  if ( 1/trk_fracerrP     < secVtx_minsignifP      ) secVtx_minsignifP      = 1/trk_fracerrP;
	  if ( 1/trk_fracerrd0_sv < secVtx_minsignifd0_sv  ) secVtx_minsignifd0_sv  = 1/trk_fracerrd0_sv;
	  if ( 1/trk_fracerrz0_sv < secVtx_minsignifz0_sv  ) secVtx_minsignifz0_sv  = 1/trk_fracerrz0_sv;
	  if ( 1/trk_fracerrP_sv  < secVtx_minsignifP_sv   ) secVtx_minsignifP_sv   = 1/trk_fracerrP_sv;
	  if ( 1/trk_fracerrd0    > secVtx_maxsignifd0     ) secVtx_maxsignifd0     = 1/trk_fracerrd0;
	  if ( 1/trk_fracerrz0    > secVtx_maxsignifz0     ) secVtx_maxsignifz0     = 1/trk_fracerrz0;
	  if ( 1/trk_fracerrP     > secVtx_maxsignifP      ) secVtx_maxsignifP      = 1/trk_fracerrP;
	  if ( 1/trk_fracerrd0_sv > secVtx_maxsignifd0_sv  ) secVtx_maxsignifd0_sv  = 1/trk_fracerrd0_sv;
	  if ( 1/trk_fracerrz0_sv > secVtx_maxsignifz0_sv  ) secVtx_maxsignifz0_sv  = 1/trk_fracerrz0_sv;
	  if ( 1/trk_fracerrP_sv  > secVtx_maxsignifP_sv   ) secVtx_maxsignifP_sv   = 1/trk_fracerrP_sv;
	  // --> opening angle (wrt PV), dR b/w tracks, chi2 ??

	  h_DV_trkd0_r          .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), m_trk_d0            ->at(trkIx),    weight );
	  h_DV_trkz0_z          .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), m_trk_z0            ->at(trkIx),    weight );
	  h_DV_trkP_pt          .at(ireg).at(idv) ->Fill( secVtx_pt,          1000 * m_trk_qOverP ->at(trkIx),    weight );
	  h_DV_trkErrd0_r       .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(trk_errd0),                    weight );
	  h_DV_trkErrz0_z       .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(trk_errz0),                    weight );
	  h_DV_trkErrP_pt       .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(trk_errP),                     weight );
	  h_DV_trkSqrterrd0_r   .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(trk_errd0)),              weight );
	  h_DV_trkSqrterrz0_z   .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(trk_errz0)),              weight );
	  h_DV_trkSqrterrP_pt   .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(sqrt(trk_errP)),               weight );
	  h_DV_trkd0sv_r        .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), m_secVtx_trk_d0_sv ->at(i).at(j),   weight );
	  h_DV_trkz0sv_z        .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), m_secVtx_trk_z0_sv ->at(i).at(j),   weight );
	  h_DV_trkPsv_pt        .at(ireg).at(idv) ->Fill( secVtx_pt,          trk_qOverP_sv,                      weight );
	  h_DV_trkErrd0sv_r     .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(trk_errd0_sv),                 weight );
	  h_DV_trkErrz0sv_z     .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(trk_errz0_sv),                 weight );
	  h_DV_trkErrPsv_pt     .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(trk_errP_sv),                  weight );
	  h_DV_trkSqrterrd0sv_r .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(trk_errd0_sv)),           weight );
	  h_DV_trkSqrterrz0sv_z .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(trk_errz0_sv)),           weight );
	  h_DV_trkSqrterrPsv_pt .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(sqrt(trk_errP_sv)),            weight );

	  h_DV_trkErrd0_trkd0         .at(ireg).at(idv) ->Fill( m_trk_d0            ->at(trkIx),   sqrt(trk_errd0),          weight );
	  h_DV_trkErrz0_trkz0         .at(ireg).at(idv) ->Fill( m_trk_z0            ->at(trkIx),   sqrt(trk_errz0),          weight );
	  h_DV_trkErrP_trkP           .at(ireg).at(idv) ->Fill( 1000 * m_trk_qOverP ->at(trkIx),   sqrt(trk_errP),           weight );
	  h_DV_trkSqrterrd0_trkd0     .at(ireg).at(idv) ->Fill( m_trk_d0            ->at(trkIx),   sqrt(sqrt(trk_errd0)),    weight );
	  h_DV_trkSqrterrz0_trkz0     .at(ireg).at(idv) ->Fill( m_trk_z0            ->at(trkIx),   sqrt(sqrt(trk_errz0)),    weight );
	  h_DV_trkSqrterrP_trkP       .at(ireg).at(idv) ->Fill( 1000 * m_trk_qOverP ->at(trkIx),   sqrt(sqrt(trk_errP)),     weight );
	  h_DV_trkErrd0sv_trkd0sv     .at(ireg).at(idv) ->Fill( m_secVtx_trk_d0_sv  ->at(i).at(j), sqrt(trk_errd0_sv),       weight );
	  h_DV_trkErrz0sv_trkz0sv     .at(ireg).at(idv) ->Fill( m_secVtx_trk_z0_sv  ->at(i).at(j), sqrt(trk_errz0_sv),       weight );
	  h_DV_trkErrPsv_trkPsv       .at(ireg).at(idv) ->Fill( trk_qOverP_sv,                     sqrt(trk_errP),           weight );
	  h_DV_trkSqrterrd0sv_trkd0sv .at(ireg).at(idv) ->Fill( m_secVtx_trk_d0_sv  ->at(i).at(j), sqrt(sqrt(trk_errd0_sv)), weight );
	  h_DV_trkSqrterrz0sv_trkz0sv .at(ireg).at(idv) ->Fill( m_secVtx_trk_z0_sv  ->at(i).at(j), sqrt(sqrt(trk_errz0_sv)), weight );
	  h_DV_trkSqrterrPsv_trkPsv   .at(ireg).at(idv) ->Fill( trk_qOverP_sv,                     sqrt(sqrt(trk_errP)),     weight );
	  
	} // end loop over tracks

	h_DV_ntrk_final .at(ireg).at(idv) ->Fill( ntrk_final, weight );
	h_DV_ntrk_sel   .at(ireg).at(idv) ->Fill( ntrk_sel,   weight );
	h_DV_ntrk_assoc .at(ireg).at(idv) ->Fill( ntrk_assoc, weight );
	h_DV_ntrk_lrt   .at(ireg).at(idv) ->Fill( ntrk_lrt,   weight );

	h_DV_sumd0           .at(ireg).at(idv) ->Fill( secVtx_sumd0,                   weight );
	h_DV_sumz0           .at(ireg).at(idv) ->Fill( secVtx_sumz0,                   weight );
	h_DV_sumP            .at(ireg).at(idv) ->Fill( secVtx_sumP,                    weight );
	h_DV_sumErrd0        .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumerrd0),          weight );
	h_DV_sumErrz0        .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumerrz0),          weight );
	h_DV_sumErrP         .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumerrP),           weight );
	h_DV_sumSqrterrd0    .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_sumerrd0)),    weight );
	h_DV_sumSqrterrz0    .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_sumerrz0)),    weight );
	h_DV_sumSqrterrP     .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_sumerrP)),     weight );
	h_DV_sumFracerrd0    .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumfracerrd0),      weight );
	h_DV_sumFracerrz0    .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumfracerrz0),      weight );
	h_DV_sumFracerrP     .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumfracerrP),       weight );
	h_DV_sumSignifd0     .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumsignifd0),       weight );
	h_DV_sumSignifz0     .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumsignifz0),       weight );
	h_DV_sumSignifP      .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumsignifP),        weight );
	h_DV_sumd0_sv        .at(ireg).at(idv) ->Fill( secVtx_sumd0_sv,                weight );
	h_DV_sumz0_sv        .at(ireg).at(idv) ->Fill( secVtx_sumz0_sv,                weight );
	h_DV_sumP_sv         .at(ireg).at(idv) ->Fill( secVtx_sumP_sv,                 weight );
	h_DV_sumErrd0_sv     .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumerrd0_sv),       weight );
	h_DV_sumErrz0_sv     .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumerrz0_sv),       weight );
	h_DV_sumErrP_sv      .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumerrP_sv),        weight );
	h_DV_sumSqrterrd0_sv .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_sumerrd0_sv)), weight );
	h_DV_sumSqrterrz0_sv .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_sumerrz0_sv)), weight );
	h_DV_sumSqrterrP_sv  .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_sumerrP_sv)),  weight );
	h_DV_sumFracerrd0_sv .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumfracerrd0_sv),   weight );
	h_DV_sumFracerrz0_sv .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumfracerrz0_sv),   weight );
	h_DV_sumFracerrP_sv  .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumfracerrP_sv),    weight );
	h_DV_sumSignifd0_sv  .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumsignifd0_sv),    weight );
	h_DV_sumSignifz0_sv  .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumsignifz0_sv),    weight );
	h_DV_sumSignifP_sv   .at(ireg).at(idv) ->Fill( sqrt(secVtx_sumsignifP_sv),     weight );

	h_DV_mind0           .at(ireg).at(idv) ->Fill( secVtx_mind0,                   weight );
	h_DV_minz0           .at(ireg).at(idv) ->Fill( secVtx_minz0,                   weight );
	h_DV_minP            .at(ireg).at(idv) ->Fill( secVtx_minP,                    weight );
	h_DV_minErrd0        .at(ireg).at(idv) ->Fill( sqrt(secVtx_minerrd0),          weight );
	h_DV_minErrz0        .at(ireg).at(idv) ->Fill( sqrt(secVtx_minerrz0),          weight );
	h_DV_minErrP         .at(ireg).at(idv) ->Fill( sqrt(secVtx_minerrP),           weight );
	h_DV_minSqrterrd0    .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_minerrd0)),    weight );
	h_DV_minSqrterrz0    .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_minerrz0)),    weight );
	h_DV_minSqrterrP     .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_minerrP)),     weight );
	h_DV_minFracerrd0    .at(ireg).at(idv) ->Fill( sqrt(secVtx_minfracerrd0),      weight );
	h_DV_minFracerrz0    .at(ireg).at(idv) ->Fill( sqrt(secVtx_minfracerrz0),      weight );
	h_DV_minFracerrP     .at(ireg).at(idv) ->Fill( sqrt(secVtx_minfracerrP),       weight );
	h_DV_minSignifd0     .at(ireg).at(idv) ->Fill( sqrt(secVtx_minsignifd0),       weight );
	h_DV_minSignifz0     .at(ireg).at(idv) ->Fill( sqrt(secVtx_minsignifz0),       weight );
	h_DV_minSignifP      .at(ireg).at(idv) ->Fill( sqrt(secVtx_minsignifP),        weight );
	h_DV_mind0_sv        .at(ireg).at(idv) ->Fill( secVtx_mind0_sv,                weight );
	h_DV_minz0_sv        .at(ireg).at(idv) ->Fill( secVtx_minz0_sv,                weight );
	h_DV_minP_sv         .at(ireg).at(idv) ->Fill( secVtx_minP_sv,                 weight );
	h_DV_minErrd0_sv     .at(ireg).at(idv) ->Fill( sqrt(secVtx_minerrd0_sv),       weight );
	h_DV_minErrz0_sv     .at(ireg).at(idv) ->Fill( sqrt(secVtx_minerrz0_sv),       weight );
	h_DV_minErrP_sv      .at(ireg).at(idv) ->Fill( sqrt(secVtx_minerrP_sv),        weight );
	h_DV_minSqrterrd0_sv .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_minerrd0_sv)), weight );
	h_DV_minSqrterrz0_sv .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_minerrz0_sv)), weight );
	h_DV_minSqrterrP_sv  .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_minerrP_sv)),  weight );
	h_DV_minFracerrd0_sv .at(ireg).at(idv) ->Fill( sqrt(secVtx_minfracerrd0_sv),   weight );
	h_DV_minFracerrz0_sv .at(ireg).at(idv) ->Fill( sqrt(secVtx_minfracerrz0_sv),   weight );
	h_DV_minFracerrP_sv  .at(ireg).at(idv) ->Fill( sqrt(secVtx_minfracerrP_sv),    weight );
	h_DV_minSignifd0_sv  .at(ireg).at(idv) ->Fill( sqrt(secVtx_minsignifd0_sv),    weight );
	h_DV_minSignifz0_sv  .at(ireg).at(idv) ->Fill( sqrt(secVtx_minsignifz0_sv),    weight );
	h_DV_minSignifP_sv   .at(ireg).at(idv) ->Fill( sqrt(secVtx_minsignifP_sv),     weight );

	h_DV_maxd0           .at(ireg).at(idv) ->Fill( secVtx_maxd0,                   weight );
	h_DV_maxz0           .at(ireg).at(idv) ->Fill( secVtx_maxz0,                   weight );
	h_DV_maxP            .at(ireg).at(idv) ->Fill( secVtx_maxP,                    weight );
	h_DV_maxErrd0        .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxerrd0),          weight );
	h_DV_maxErrz0        .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxerrz0),          weight );
	h_DV_maxErrP         .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxerrP),           weight );
	h_DV_maxSqrterrd0    .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_maxerrd0)),    weight );
	h_DV_maxSqrterrz0    .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_maxerrz0)),    weight );
	h_DV_maxSqrterrP     .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_maxerrP)),     weight );
	h_DV_maxFracerrd0    .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxfracerrd0),      weight );
	h_DV_maxFracerrz0    .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxfracerrz0),      weight );
	h_DV_maxFracerrP     .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxfracerrP),       weight );
	h_DV_maxSignifd0     .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxsignifd0),       weight );
	h_DV_maxSignifz0     .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxsignifz0),       weight );
	h_DV_maxSignifP      .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxsignifP),        weight );
	h_DV_maxd0_sv        .at(ireg).at(idv) ->Fill( secVtx_maxd0_sv,                weight );
	h_DV_maxz0_sv        .at(ireg).at(idv) ->Fill( secVtx_maxz0_sv,                weight );
	h_DV_maxP_sv         .at(ireg).at(idv) ->Fill( secVtx_maxP_sv,                 weight );
	h_DV_maxErrd0_sv     .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxerrd0_sv),       weight );
	h_DV_maxErrz0_sv     .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxerrz0_sv),       weight );
	h_DV_maxErrP_sv      .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxerrP_sv),        weight );
	h_DV_maxSqrterrd0_sv .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_maxerrd0_sv)), weight );
	h_DV_maxSqrterrz0_sv .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_maxerrz0_sv)), weight );
	h_DV_maxSqrterrP_sv  .at(ireg).at(idv) ->Fill( sqrt(sqrt(secVtx_maxerrP_sv)),  weight );
	h_DV_maxFracerrd0_sv .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxfracerrd0_sv),   weight );
	h_DV_maxFracerrz0_sv .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxfracerrz0_sv),   weight );
	h_DV_maxFracerrP_sv  .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxfracerrP_sv),    weight );
	h_DV_maxSignifd0_sv  .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxsignifd0_sv),    weight );
	h_DV_maxSignifz0_sv  .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxsignifz0_sv),    weight );
	h_DV_maxSignifP_sv   .at(ireg).at(idv) ->Fill( sqrt(secVtx_maxsignifP_sv),     weight );

	// 2d plots
	h_DV_sumErrd0_r       .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_sumerrd0),          weight );
	h_DV_sumErrz0_z       .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_sumerrz0),          weight );
	h_DV_sumErrP_pt       .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(secVtx_sumerrP),           weight );
	h_DV_sumSqrterrd0_r   .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_sumerrd0)),    weight );
	h_DV_sumSqrterrz0_z   .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_sumerrz0)),    weight );
	h_DV_sumSqrterrP_pt   .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_sumerrP)),     weight );
	h_DV_sumErrd0sv_r     .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_sumerrd0_sv),       weight );
	h_DV_sumErrz0sv_z     .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_sumerrz0_sv),       weight );
	h_DV_sumErrPsv_pt     .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(secVtx_sumerrP_sv),        weight );
	h_DV_sumSqrterrd0sv_r .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_sumerrd0_sv)), weight );
	h_DV_sumSqrterrz0sv_z .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_sumerrz0_sv)), weight );
	h_DV_sumSqrterrPsv_pt .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_sumerrP_sv)),  weight );

	h_DV_minErrd0_r       .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_minerrd0),          weight );
	h_DV_minErrz0_z       .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_minerrz0),          weight );
	h_DV_minErrP_pt       .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(secVtx_minerrP),           weight );
	h_DV_minSqrterrd0_r   .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_minerrd0)),    weight );
	h_DV_minSqrterrz0_z   .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_minerrz0)),    weight );
	h_DV_minSqrterrP_pt   .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_minerrP)),     weight );
	h_DV_minErrd0sv_r     .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_minerrd0_sv),       weight );
	h_DV_minErrz0sv_z     .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_minerrz0_sv),       weight );
	h_DV_minErrPsv_pt     .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(secVtx_minerrP_sv),        weight );
	h_DV_minSqrterrd0sv_r .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_minerrd0_sv)), weight );
	h_DV_minSqrterrz0sv_z .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_minerrz0_sv)), weight );
	h_DV_minSqrterrPsv_pt .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_minerrP_sv)),  weight );

	h_DV_maxErrd0_r       .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_maxerrd0),          weight );
	h_DV_maxErrz0_z       .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_maxerrz0),          weight );
	h_DV_maxErrP_pt       .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(secVtx_maxerrP),           weight );
	h_DV_maxSqrterrd0_r   .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_maxerrd0)),    weight );
	h_DV_maxSqrterrz0_z   .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_maxerrz0)),    weight );
	h_DV_maxSqrterrP_pt   .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_maxerrP)),     weight );
	h_DV_maxErrd0sv_r     .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_maxerrd0_sv),       weight );
	h_DV_maxErrz0sv_z     .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_maxerrz0_sv),       weight );
	h_DV_maxErrPsv_pt     .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(secVtx_maxerrP_sv),        weight );
	h_DV_maxSqrterrd0sv_r .at(ireg).at(idv) ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_maxerrd0_sv)), weight );
	h_DV_maxSqrterrz0sv_z .at(ireg).at(idv) ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_maxerrz0_sv)), weight );
	h_DV_maxSqrterrPsv_pt .at(ireg).at(idv) ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_maxerrP_sv)),  weight );

	// n-track vertices
	if ( m_numVtxTrks ) {
	  //int ntrk = secVtx_ntrk;
	  //if ( ntrk >= m_numVtxTrks ) ntrk = m_numVtxTrks;
	  //++n_ntrkDV.at(idv)[ntrk];
	  h_ntrkDV_z               .at(ireg).at(idv).at(ntrk-2)->Fill( m_secVtx_z ->at(i),             weight );
	  h_ntrkDV_z_s             .at(ireg).at(idv).at(ntrk-2)->Fill( m_secVtx_z ->at(i),             weight );
	  h_ntrkDV_r               .at(ireg).at(idv).at(ntrk-2)->Fill( m_secVtx_r ->at(i),             weight );
	  h_ntrkDV_r_s             .at(ireg).at(idv).at(ntrk-2)->Fill( m_secVtx_r ->at(i),             weight );
	  h_ntrkDV_mass            .at(ireg).at(idv).at(ntrk-2)->Fill( secVtx_mass,                    weight );
	  h_ntrkDV_mass_s          .at(ireg).at(idv).at(ntrk-2)->Fill( secVtx_mass,                    weight );
	  h_ntrkDV_direction       .at(ireg).at(idv).at(ntrk-2)->Fill( secVtx_dir,                     weight );
	  h_ntrkDV_minOpAng        .at(ireg).at(idv).at(ntrk-2)->Fill( secVtx_minOpAng,                weight );
	  h_ntrkDV_maxOpAng        .at(ireg).at(idv).at(ntrk-2)->Fill( secVtx_maxOpAng,                weight );
	  h_ntrkDV_chi2            .at(ireg).at(idv).at(ntrk-2)->Fill( m_secVtx_chi2 ->at(i),          weight );
	  h_ntrkDV_chi2_s          .at(ireg).at(idv).at(ntrk-2)->Fill( m_secVtx_chi2 ->at(i),          weight );
	  h_ntrkDV_sqrterrx        .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_errx)),        weight );
	  h_ntrkDV_sqrterry        .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_erry)),        weight );
	  h_ntrkDV_sqrterrz        .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_errz)),        weight );
	  h_ntrkDV_sqrterrr        .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_errr)),        weight );
	  h_ntrkDV_sqrterrphi      .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_errphi)),      weight );
	  h_ntrkDV_sumSqrterrd0    .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_sumerrd0)),    weight );
	  h_ntrkDV_sumSqrterrz0    .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_sumerrz0)),    weight );
	  h_ntrkDV_sumSqrterrP     .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_sumerrP)),     weight );
	  h_ntrkDV_sumSqrterrd0_sv .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_sumerrd0_sv)), weight );
	  h_ntrkDV_sumSqrterrz0_sv .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_sumerrz0_sv)), weight );
	  h_ntrkDV_sumSqrterrP_sv  .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_sumerrP_sv)),  weight );
	  h_ntrkDV_minSqrterrd0    .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_minerrd0)),    weight );
	  h_ntrkDV_minSqrterrz0    .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_minerrz0)),    weight );
	  h_ntrkDV_minSqrterrP     .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_minerrP)),     weight );
	  h_ntrkDV_minSqrterrd0_sv .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_minerrd0_sv)), weight );
	  h_ntrkDV_minSqrterrz0_sv .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_minerrz0_sv)), weight );
	  h_ntrkDV_minSqrterrP_sv  .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_minerrP_sv)),  weight );
	  h_ntrkDV_maxSqrterrd0    .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_maxerrd0)),    weight );
	  h_ntrkDV_maxSqrterrz0    .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_maxerrz0)),    weight );
	  h_ntrkDV_maxSqrterrP     .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_maxerrP)),     weight );
	  h_ntrkDV_maxSqrterrd0_sv .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_maxerrd0_sv)), weight );
	  h_ntrkDV_maxSqrterrz0_sv .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_maxerrz0_sv)), weight );
	  h_ntrkDV_maxSqrterrP_sv  .at(ireg).at(idv).at(ntrk-2)->Fill( sqrt(sqrt(secVtx_maxerrP_sv)),  weight );
	}
	
      } // end loop over DV types

    } // end loop over vertices

    // fill DV count histograms
    if ( doHists ) {
      for ( size_t idv = 0; idv != n_DV.size(); ++idv ) {
	h_DV_n .at(ireg).at(idv) ->Fill( n_DV.at(idv), weight );
	if ( m_numVtxTrks ) {
	  for ( const auto& ntrkDV : n_ntrkDV.at(idv) )
	    h_ntrkDV_n .at(ireg).at(idv).at(ntrkDV.first-2) ->Fill( ntrkDV.second, weight );
	}
      }
    }



    // --- ABCD PLANE TESTS --- //
    // -- tentative ABCD variables
    if ( m_histoInfoSwitch->m_abcd ) {
      for ( size_t idv = 0; idv != n_DV.size(); ++idv ) {
	h_abcd_nDV_njetHt .at(ireg).at(idv) ->Fill( m_njetHt, n_DV.at(idv), weight );
      }
    }



    // --- TRIGGER STUDY --- //
    // do trigger efficiency studies
    if ( m_histoInfoSwitch->m_trigTest ) {
      // count number of four-jet events
      bool fourJetEvent = false;
      if ( m_jet_n >= m_nJets ) {
	fourJetEvent  = true;
	++m_nFourJets .at(ireg);
      }
      bool fourJetOthEvent = false;
      if ( m_jetOth_n >= m_nJets )
	fourJetOthEvent     = true;
      // count number of search-region events (excluding trigger requirement)
      bool searchRegionEvent = false;
      if ( m_signal_njet && m_signal_jetPt && m_signal_jetEta && m_signal_njetHt ) {
      	searchRegionEvent = true;
      	++m_nSearch .at(ireg);
      }
      // count number of events passing trigger
      bool passTrig_4j120 = false;
      for ( size_t i = 0; i != m_passedTriggers ->size(); ++i ) {
	if ( m_passedTriggers ->at(i) == "HLT_4j120" ) {
	  passTrig_4j120  = true;
	  ++m_nTrig_4j120 .at(ireg);
	}
      }
      // count number of events passing emulated trigger (offline pt, eta cuts [w/ JVT])
      bool passOffTrig_4j120    = false;
      bool passOffTrigJVT_4j120 = false;
      if ( fourJetEvent ) {
	bool passEta = false;
	bool passJVT = false;
	for ( int ijet = 0; ijet != m_nJets; ++ijet ) {
	  if ( fabs( m_jet_eta ->at(ijet) ) > m_trigJetEta ) break;
	  passEta = true;
	  if ( !m_jet_passJVT ->at(ijet) ) break;
	  passJVT = true;
	}
	if ( passEta && m_jet_pt ->at(3) >= m_trigJetPt ) {
	  passOffTrig_4j120  = true;
	  ++m_nOffTrig_4j120 .at(ireg);
	  if ( passJVT ) {
	    passOffTrigJVT_4j120  = true;
	    ++m_nOffTrigJVT_4j120 .at(ireg);
	  }
	}
      }
      bool passOffTrig_4j120_other    = false;
      bool passOffTrigJVT_4j120_other = false;
      if ( fourJetOthEvent ) {
	bool passEta = false;
	bool passJVT = false;
	for ( int ijet = 0; ijet != m_nJets; ++ijet ) {
	  if ( fabs( m_jetOth_eta ->at(ijet) ) > m_trigJetEta ) break;
	  passEta = true;
	  if ( !m_jetOth_passJVT ->at(ijet) ) break;
	  passJVT = true;
	}
	if ( passEta && m_jetOth_pt ->at(3) >= m_trigJetPt ) {
	  passOffTrig_4j120_other  = true;
	  ++m_nOffTrig_4j120_other .at(ireg);
	  if ( passJVT ) {
	    passOffTrigJVT_4j120_other  = true;
	    ++m_nOffTrigJVT_4j120_other .at(ireg);
	  }
	}
      }
      // --> TEST JVT
      // count number of four-jet events passing trigger and fill pt distributions
      if ( fourJetEvent ) {
      	double nth_jet_pt = m_jet_pt ->at(m_nJets-1);
      	h_nthJetPt                   .at(ireg) ->Fill( nth_jet_pt, weight );
      	if ( passTrig_4j120             ) {
      	  h_nthJetPt_trig            .at(ireg) ->Fill( nth_jet_pt, weight );
      	  ++m_nTrig_fourJet          .at(ireg);
      	}
      	if ( passOffTrig_4j120          ) {
      	  h_nthJetPt_offTrig         .at(ireg) ->Fill( nth_jet_pt, weight );
      	  ++m_nOffTrig_fourJet       .at(ireg);
      	}
      	if ( passOffTrig_4j120_other    ) {
      	  h_nthJetPt_othOffTrig      .at(ireg) ->Fill( nth_jet_pt, weight );
      	  ++m_nOthOffTrig_fourJet    .at(ireg);
      	}
      	if ( passOffTrigJVT_4j120       ) {
      	  h_nthJetPt_offTrigJVT      .at(ireg) ->Fill( nth_jet_pt, weight );
      	  ++m_nOffTrigJVT_fourJet    .at(ireg);
      	}
      	if ( passOffTrigJVT_4j120_other ) {
      	  h_nthJetPt_othOffTrigJVT   .at(ireg) ->Fill( nth_jet_pt, weight );
      	  ++m_nOthOffTrigJVT_fourJet .at(ireg);
      	}
      }
      // count number of search-region events passing trigger
      if ( searchRegionEvent ) {
      	if ( passTrig_4j120               ) ++m_nTrig_search             .at(ireg);
      	if ( passOffTrig_4j120            ) ++m_nOffTrig_search          .at(ireg);
      	if ( passOffTrig_4j120_other      ) ++m_nOthOffTrig_search       .at(ireg);
      	if ( passOffTrigJVT_4j120         ) ++m_nOffTrigJVT_search       .at(ireg);
      	if ( passOffTrigJVT_4j120_other   ) ++m_nOthOffTrigJVT_search    .at(ireg);
      }  
    } // end trigger test

    ++m_nEntries .at(ireg);
    
  } // end loop over regions

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: finalize ( const std::vector<EJsHelper::Region>& regions )
{
  
  for ( int ireg = 0; ireg != regions.size(); ++ireg ) {

    // fill metadata histograms
    h_MetaData_EventCount .at(ireg) ->Fill( 1, m_nEvents_init );
    h_MetaData_EventCount .at(ireg) ->Fill( 2, m_nEvents_sel  );
    h_MetaData_EventCount .at(ireg) ->Fill( 3, m_sumw_init    );
    h_MetaData_EventCount .at(ireg) ->Fill( 4, m_sumw_sel     );
    h_MetaData_EventCount .at(ireg) ->Fill( 5, m_sumw2_init   );
    h_MetaData_EventCount .at(ireg) ->Fill( 6, m_sumw2_sel    );
    h_MetaData_Weights    .at(ireg) ->Fill( 1, m_xsec * 1e6   ); // [fb]
    h_MetaData_Weights    .at(ireg) ->Fill( 2, m_kfactor      );
    h_MetaData_Weights    .at(ireg) ->Fill( 3, m_filteff      );
    h_MetaData_Weights    .at(ireg) ->Fill( 4, m_lumi         ); // [ifb]
    
    if ( m_histoInfoSwitch->m_trigTest ) {
      // trigger efficiency as function of nth leading jet pt
      h_trigEff_nthJetPt             .at(ireg) ->Divide( h_nthJetPt_trig             .at(ireg), h_nthJetPt    .at(ireg) );
      h_offTrigEff_nthJetPt          .at(ireg) ->Divide( h_nthJetPt_offTrig          .at(ireg), h_nthJetPt    .at(ireg) );
      h_othOffTrigEff_nthJetPt       .at(ireg) ->Divide( h_nthJetPt_othOffTrig       .at(ireg), h_nthJetPt    .at(ireg) );
      h_offTrigJVTEff_nthJetPt       .at(ireg) ->Divide( h_nthJetPt_offTrigJVT       .at(ireg), h_nthJetPt    .at(ireg) );
      h_othOffTrigJVTEff_nthJetPt    .at(ireg) ->Divide( h_nthJetPt_othOffTrigJVT    .at(ireg), h_nthJetPt    .at(ireg) );
      
      // overall trigger efficiency (kA / nA = n trig events / n initial events)
      // --> nA = initial number of events in sample A
      // --> --> sample A = total events, four-jet events, ...
      // ... search region events (excluding trigger requirement), signal region events (region A, excluding trigger)
      // --> kA = final number of events in sample A after requiring trigger
      std::vector<int> nTrigEvents
      	= { m_nTrig_4j120            .at(ireg),
      	    m_nOffTrig_4j120         .at(ireg), m_nOffTrig_4j120_other    .at(ireg),
      	    m_nOffTrigJVT_4j120      .at(ireg), m_nOffTrigJVT_4j120_other .at(ireg) };
      std::vector<int> nFourJetTrigEvents
      	= { m_nTrig_fourJet          .at(ireg), // four-jet region
	    m_nOffTrig_fourJet       .at(ireg), m_nOthOffTrig_fourJet       .at(ireg),
	    m_nOffTrigJVT_fourJet    .at(ireg), m_nOthOffTrigJVT_fourJet    .at(ireg) };
      std::vector<int> nSearchTrigEvents
      	= { m_nTrig_search           .at(ireg), // jet search region
	    m_nOffTrig_search        .at(ireg), m_nOthOffTrig_search       .at(ireg),
	    m_nOffTrigJVT_search     .at(ireg), m_nOthOffTrigJVT_search    .at(ireg) };
      for ( size_t i = 0; i != nTrigEvents.size(); ++i ) {
      	h_triggerEfficiency          .at(ireg) // trigger efficiency for all events
      	  ->Fill( i+1,   nTrigEvents        .at(i) / float( m_nEntries        .at(ireg) ) );
	h_triggerEfficiency_fourJet  .at(ireg) // trigger efficiency for four-jet events
      	  ->Fill( i+1,   nFourJetTrigEvents .at(i) / float( m_nFourJets       .at(ireg) ) );
      	h_triggerEfficiency_search   .at(ireg) // trigger efficiency for search-region events
      	  ->Fill( i+1,   nSearchTrigEvents  .at(i) / float( m_nSearch         .at(ireg) ) );
      	h_searchTriggerEfficiency    .at(ireg) // search region efficiency
      	  ->Fill( i+1,   nSearchTrigEvents  .at(i) / float( m_nEntries        .at(ireg) ) );
      }
    } // end trigger study
    
  } // end loop over regions
  
  return StatusCode::SUCCESS;
}
