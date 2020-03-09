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
  m_jet_isDark       = new std::vector<uint8_t>;
  m_jet_darkID       = new std::vector<int>;
  m_jet_darkIndex    = new std::vector<int>;
  m_jet_darkDR       = new std::vector<float>;
  m_jet_isTruth      = new std::vector<uint8_t>;
  m_jet_truthID      = new std::vector<int>;
  m_jet_truthIndex   = new std::vector<int>;
  m_jet_truthDR      = new std::vector<float>;
  m_jet_trk_n        = new std::vector<int>; // m_jet_ntrk
  m_jet_trk_ID       = new std::vector<std::vector<int>>;
  m_jet_trk_index    = new std::vector<std::vector<int>>;
  m_jet_trk_dR       = new std::vector<std::vector<float>>;
  m_jet_secVtx_n     = new std::vector<int>;
  m_jet_secVtx_ID    = new std::vector<std::vector<int>>;
  m_jet_secVtx_index = new std::vector<std::vector<int>>;
  m_jet_secVtx_dR    = new std::vector<std::vector<float>>;
  // other jet branches
  m_jetOth_n         = 0;
  m_jetOth_pt        = new std::vector<float>;
  m_jetOth_eta       = new std::vector<float>;
  m_jetOth_passJVT   = new std::vector<int>;

  // truth jet branches
  m_truthJet_n         = 0;
  m_truthJet_ID        = new std::vector<int>;
  m_truthJet_index     = new std::vector<int>;
  m_truthJet_isDark    = new std::vector<uint8_t>;
  m_truthJet_darkID    = new std::vector<int>;
  m_truthJet_darkIndex = new std::vector<int>;
  m_truthJet_darkDR    = new std::vector<float>;

  // dark jet branches
  m_darkJet_n        = 0;
  m_darkJet_ID       = new std::vector<int>;
  m_darkJet_index    = new std::vector<int>;
  m_darkJet_nConstit = new std::vector<int>;

  // track branches
  m_trk_n          = 0;
  m_trk_ID         = new std::vector<int>;
  m_trk_index      = new std::vector<int>;
  m_trk_qOverP     = new std::vector<float>;
  m_trk_theta      = new std::vector<float>;
  m_trk_pt         = new std::vector<float>;
  m_trk_eta        = new std::vector<float>;
  m_trk_phi        = new std::vector<float>;
  m_trk_d0         = new std::vector<float>;
  m_trk_z0         = new std::vector<float>;
  m_trk_errd0      = new std::vector<float>;
  m_trk_errz0      = new std::vector<float>;
  m_trk_errP       = new std::vector<float>;
  m_trk_chi2       = new std::vector<float>;
  m_trk_chiSq      = new std::vector<float>;
  m_trk_ndof       = new std::vector<int>;
  m_trk_charge     = new std::vector<float>;
  m_trk_isLRT      = new std::vector<uint8_t>;
  m_trk_isSel      = new std::vector<uint8_t>;
  m_trk_isAssoc    = new std::vector<uint8_t>;
  m_trk_isSV       = new std::vector<uint8_t>;
  m_trk_isCleanSV  = new std::vector<uint8_t>;
  m_trk_isFiltSV   = new std::vector<uint8_t>;
  m_trk_isFinalSV  = new std::vector<uint8_t>;

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
  delete m_jet_passJVT;
  delete m_jet_isDark;
  delete m_jet_darkID;
  delete m_jet_darkIndex;
  delete m_jet_darkDR;
  delete m_jet_isTruth;
  delete m_jet_truthID;
  delete m_jet_truthIndex;
  delete m_jet_truthDR;
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
  delete m_jetOth_passJVT;

  // truth jet branches
  delete m_truthJet_ID;
  delete m_truthJet_index;
  delete m_truthJet_isDark;
  delete m_truthJet_darkID;
  delete m_truthJet_darkIndex;
  delete m_truthJet_darkDR;

  // dark jet branches
  delete m_darkJet_ID;
  delete m_darkJet_index;
  delete m_darkJet_nConstit;

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
  delete m_trk_isSel;
  delete m_trk_isAssoc;
  delete m_trk_isSV;
  delete m_trk_isCleanSV;
  delete m_trk_isFiltSV;
  delete m_trk_isFinalSV;

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

  connectBranch<uint8_t> ( name, tree, "isDarkMatched",   &m_jet_isDark    );
  connectBranch<int>     ( name, tree, "darkMatch_ID",    &m_jet_darkID    );
  connectBranch<int>     ( name, tree, "darkMatch_index", &m_jet_darkIndex );
  connectBranch<float>   ( name, tree, "darkMatch_dR",    &m_jet_darkDR    );

  connectBranch<uint8_t> ( name, tree, "isTruthMatched",   &m_jet_isTruth    );
  connectBranch<int>     ( name, tree, "truthMatch_ID",    &m_jet_truthID    );
  connectBranch<int>     ( name, tree, "truthMatch_index", &m_jet_truthIndex );
  connectBranch<float>   ( name, tree, "truthMatch_dR",    &m_jet_truthDR    );

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

  std::string name = truthJetName;

  using namespace EJsHelper;

  connectBranch<int> ( tree, "n" + name, &m_truthJet_n );

  using namespace HelperFunctions;

  connectBranch<int>   ( name, tree, "ID",             &m_truthJet_ID      );
  connectBranch<int>   ( name, tree, "index",          &m_truthJet_index   );

  connectBranch<uint8_t> ( name, tree, "isDarkMatched",   &m_truthJet_isDark    );
  connectBranch<int>     ( name, tree, "darkMatch_ID",    &m_truthJet_darkID    );
  connectBranch<int>     ( name, tree, "darkMatch_index", &m_truthJet_darkIndex );
  connectBranch<float>   ( name, tree, "darkMatch_dR",    &m_truthJet_darkDR    );
  
  return StatusCode::SUCCESS;
}


StatusCode EJsHistogramManager :: connectTruthDarkJets ( TTree* tree, const std::string& darkJetName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthDarkJets()", "connecting truth dark jet branches" );

  std::string name = darkJetName;

  using namespace EJsHelper;

  connectBranch<int> ( tree, "n" + name, &m_darkJet_n );

  using namespace HelperFunctions;

  connectBranch<int> ( name, tree, "ID",    &m_darkJet_ID    );
  connectBranch<int> ( name, tree, "index", &m_darkJet_index );

  connectBranch<int> ( name, tree, "numConstituents", &m_darkJet_nConstit );
  
  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTracks ( TTree* tree, const std::string& trackName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTracks()", "connecting track branches" );

  std::string name = trackName;

  using namespace EJsHelper;

  connectBranch<int> ( tree, "n" + name, &m_trk_n );

  using namespace HelperFunctions;

  connectBranch<int>     ( name, tree, "ID",                &m_trk_ID        );
  connectBranch<int>     ( name, tree, "index",             &m_trk_index     );
  connectBranch<float>   ( name, tree, "qOverP",            &m_trk_qOverP    );
  connectBranch<float>   ( name, tree, "theta",             &m_trk_theta     );
  connectBranch<float>   ( name, tree, "pt",                &m_trk_pt        );
  connectBranch<float>   ( name, tree, "eta",               &m_trk_eta       );
  connectBranch<float>   ( name, tree, "phi",               &m_trk_phi       );
  connectBranch<float>   ( name, tree, "d0",                &m_trk_d0        );
  connectBranch<float>   ( name, tree, "z0",                &m_trk_z0        );
  connectBranch<float>   ( name, tree, "errd0",             &m_trk_errd0     );
  connectBranch<float>   ( name, tree, "errz0",             &m_trk_errz0     );
  connectBranch<float>   ( name, tree, "errP",              &m_trk_errP      );
  connectBranch<float>   ( name, tree, "chi2",              &m_trk_chi2      );
  connectBranch<float>   ( name, tree, "chiSquared",        &m_trk_chiSq     );
  connectBranch<int>     ( name, tree, "numberDoF",         &m_trk_ndof      );
  connectBranch<float>   ( name, tree, "charge",            &m_trk_charge    );
  connectBranch<uint8_t> ( name, tree, "isLRT",             &m_trk_isLRT     );
  connectBranch<uint8_t> ( name, tree, "isSelected",        &m_trk_isSel     );
  connectBranch<uint8_t> ( name, tree, "isAssociated",      &m_trk_isAssoc   );
  connectBranch<uint8_t> ( name, tree, "isSecVtxTrk",       &m_trk_isSV      );
  connectBranch<uint8_t> ( name, tree, "isSecVtxCleanTrk",  &m_trk_isCleanSV );
  connectBranch<uint8_t> ( name, tree, "isSecVtxFiltTrk",   &m_trk_isFiltSV  );
  connectBranch<uint8_t> ( name, tree, "isSecVtxFinalTrk",  &m_trk_isFinalSV );
  
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
					       const std::string& jetHistName, const EJsHelper::BaseDV& base_dv )
{
  if ( m_debug ) Info( "EJsHistogramManager::initialize()", "booking histograms" );

  // initialize object types
  
  // --> jets
  std::vector<std::string> hJ, hJstr;
  // base jets (EMTopo or PFlow; no cuts beyond search/validation region pt, eta cuts)
  hJ    .push_back( "" );
  hJstr .push_back( "" );
  // lead jets (N top-pt)
  hJ    .push_back( "lead" );
  hJstr .push_back( "lead" );
  // truth-(dark-)matched jets
  // --> dark = has truth match + dark match (highest pT w/in dR = 0.3), with dark also matched to truth match
  // --> need additional cut on dark matching; averaging 3/4 dark-matched lead jets (should be 2/4)
  if ( m_mc && m_histoInfoSwitch->m_jetTruth ) {
    std::vector<std::string> mJ    = { "darkMatch",    "nomatch"   };
    std::vector<std::string> mJstr = { "dark-matched", "unmatched" };
    std::vector<std::string> miJ, miJstr;
    for ( size_t ihj = 0; ihj != hJ.size(); ++ihj ) {
      miJ    .push_back( hJ    [ihj] );
      miJstr .push_back( hJstr [ihj] );
    }
    for ( size_t i = 0; i != mJ.size(); ++i ) {
      hJ    .push_back( mJ    [i] );
      hJstr .push_back( mJstr [i] );
      for ( size_t j = 0; j != miJ.size(); ++j ) {
	if ( j == 0 ) continue; // skip base jet name for nominal case
	std::string mJs = mJ[i]; mJs[0] = toupper(mJs[0]);
	hJ    .push_back( miJ    [j] +       mJs      );
	hJstr .push_back( miJstr [j] + " " + mJstr[i] );
      }
    }
  }
  m_nTypeJs = hJ.size();
  
  // --> tracks
  std::vector<std::string> hTrk, hTrkstr;
  hTrk    .push_back( ""                          );
  hTrkstr .push_back( ""                          );
  hTrk    .push_back( "LRT"                       );
  hTrkstr .push_back( "LRT"                       );
  hTrk    .push_back( "sel"                       );
  hTrkstr .push_back( "selected"                  );
  hTrk    .push_back( "assoc"                     );
  hTrkstr .push_back( "associated"                );
  hTrk    .push_back( "SV"                        );
  hTrkstr .push_back( "secondary vertex"          );
  hTrk    .push_back( "cleanSV"                   );
  hTrkstr .push_back( "secondary vertex clean"    );
  hTrk    .push_back( "filtSV"                    );
  hTrkstr .push_back( "secondary vertex filtered" );
  hTrk    .push_back( "finalSV"                   );
  hTrkstr .push_back( "secondary vertex final"    );
  m_nTypeTrks = hTrk.size();
  std::vector<int> ntrk_xmax  = { 5000, 4000, 500, 20, 50, 50, 50, 50 };
  std::vector<int> njtrk_xmax = {  250,  200,  50, 10, 15, 15, 15, 15 };

  // --> secondary vertices
  std::vector<std::string> hDV, hDVstr;
  // base vertices (bare or clean or filtered or custom-trimmed --> starting point for all further cuts)
  std::string baseDV    = "";
  std::string baseDVstr = base_dv.name;
  if      ( base_dv.type == EJsHelper::BARE     ) baseDV = "bare";
  else if ( base_dv.type == EJsHelper::CLEAN    ) baseDV = "clean";
  else if ( base_dv.type == EJsHelper::FILTERED ) baseDV = "filt";
  else if ( base_dv.type == EJsHelper::TRIMMED  ) baseDV = "trim";
  if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_baseVerts ) {
    hDV    .push_back( baseDV    );
    hDVstr .push_back( baseDVstr );
  }
  // vertices by (leading) jets
  std::string jDV     = "byJet";
  std::string ljDV    = "byLeadJet";
  std::string jDVstr  = "by-jet";
  std::string ljDVstr = "by-lead-jet";
  if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_byJetVerts ) {
    hDV    .push_back( jDV     );
    hDV    .push_back( ljDV    );
    hDVstr .push_back( jDVstr  );
    hDVstr .push_back( ljDVstr );
  }
  // vertices passing fiducial cuts (fiducial volume, chi2)
  std::string fidDV    = "fiducial";
  std::string fidDVstr = "fiducial-cut";
  if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_fiducialVerts ) {
    hDV    .push_back( fidDV    );
    hDVstr .push_back( fidDVstr );
  }
  // vertices w/ k-short mass window removed
  std::string ksmDV    = "ksm";
  std::string ksmDVstr = "ksm-cut";
  if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_ksmVerts ) {
    hDV    .push_back( ksmDV    );
    hDVstr .push_back( ksmDVstr );
  }
  // vertices passing low-pt cut
  std::string ptDV   = "pt";
  std::string ptDVstr = "pt-cut";
  if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_ptVerts ) {
    hDV    .push_back( ptDV    );
    hDVstr .push_back( ptDVstr );
  }
  // vertices pass min-d0 cut
  // --> add max/sum-d0 (wrt SV) cuts if necessary...
  std::string mind0DV    = "mind0";
  std::string mind0DVstr = "mind0-cut";
  if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_d0Verts ) {
    hDV    .push_back( mind0DV    );
    hDVstr .push_back( mind0DVstr );
  }
  // vertices passing min-z0 cut
  // --> add max/sum-z0 (wrt SV) cuts if necessary...
  std::string minz0DV    = "minz0";
  std::string minz0DVstr = "minz0-cut";
  if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_z0Verts ) {
    hDV    .push_back( minz0DV    );
    hDVstr .push_back( minz0DVstr );
  }
  // vertices passing min-sqrterr-d0/z0 cut
  // --> add max/sum-sqrterr-d0/z0 (wrt SV) cuts if necessary...
  std::string minsqerrd0DV    = "minsqerrd0";
  std::string minsqerrz0DV    = "minsqerrz0";
  std::string minsqerrd0DVstr = "minsqerrd0-cut";
  std::string minsqerrz0DVstr = "minsqerrz0-cut";
  if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_d0z0ErrVerts ) {
    hDV    .push_back( minsqerrd0DV    );
    hDV    .push_back( minsqerrz0DV    );
    hDVstr .push_back( minsqerrd0DVstr );
    hDVstr .push_back( minsqerrz0DVstr );
  }
  
  // combination-cut vertices
  // --> can we do this is in more methodical way (YES)? loop over individual cuts and do all possible combinations...
  // vertices by (leading) jets and passing fiducial cuts
  std::string jfidDV     = "byJetFiducial";
  std::string ljfidDV    = "byLeadJetFiducial";
  std::string jfidDVstr  = "by-jet-fiducial-cut";
  std::string ljfidDVstr = "by-lead-jet-fiducial-cut";
  if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts && m_histoInfoSwitch->m_fiducialVerts ) ) {
    hDV    .push_back( jfidDV     );
    hDV    .push_back( ljfidDV    );
    hDVstr .push_back( jfidDVstr  );
    hDVstr .push_back( ljfidDVstr );
  }
  // vertices by (leading) jets and passing k-short mass cuts
  std::string jksmDV     = "byJetKsm";
  std::string ljksmDV    = "byLeadJetKsm";
  std::string jksmDVstr  = "by-jet-ksm-cut";
  std::string ljksmDVstr = "by-lead-jet-ksm-cut";
  if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts && m_histoInfoSwitch->m_ksmVerts ) ) {
    hDV    .push_back( jksmDV     );
    hDV    .push_back( ljksmDV    );
    hDVstr .push_back( jksmDVstr  );
    hDVstr .push_back( ljksmDVstr );
  }
  // vertices by (leading) jets and passing low-pt cuts
  std::string jptDV     = "byJetPt";
  std::string ljptDV    = "byLeadJetPt";
  std::string jptDVstr  = "by-jet-pt-cut";
  std::string ljptDVstr = "by-lead-jet-pt-cut";
  if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts && m_histoInfoSwitch->m_ptVerts ) ) {
    hDV    .push_back( jptDV     );
    hDV    .push_back( ljptDV    );
    hDVstr .push_back( jptDVstr  );
    hDVstr .push_back( ljptDVstr );
  }
  // vertices by (leading) jets and passing min-d0 cuts
  std::string jmind0DV     = "byJetMind0";
  std::string ljmind0DV    = "byLeadJetMind0";
  std::string jmind0DVstr  = "by-jet-mind0-cut";
  std::string ljmind0DVstr = "by-lead-jet-mind0-cut";
  if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts && m_histoInfoSwitch->m_d0Verts ) ) {
    hDV    .push_back( jmind0DV     );
    hDV    .push_back( ljmind0DV    );
    hDVstr .push_back( jmind0DVstr  );
    hDVstr .push_back( ljmind0DVstr );
  }
  // vertices by (leading) jets and passing min-z0 cuts
  std::string jminz0DV     = "byJetMinz0";
  std::string ljminz0DV    = "byLeadJetMinz0";
  std::string jminz0DVstr  = "by-jet-minz0-cut";
  std::string ljminz0DVstr = "by-lead-jet-minz0-cut";
  if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts && m_histoInfoSwitch->m_z0Verts ) ) {
    hDV    .push_back( jminz0DV     );
    hDV    .push_back( ljminz0DV    );
    hDVstr .push_back( jminz0DVstr  );
    hDVstr .push_back( ljminz0DVstr );
  }
  // --> ADD MIN SQRT ERR BY (LEAD) JETS
  // --> ADD OTHER COMBINATIONS OF MIN (SQRT-ERR) D0/Z0 (i.e. with each other, fiducial, ksm cuts, etc.)s
  // vertices passing fiducial + k-short-mass cuts
  std::string fidksmDV    = "fiducKsm";
  std::string fidksmDVstr = "fiduc-ksm-cut";
  if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_fiducialVerts && m_histoInfoSwitch->m_ksmVerts ) ) {
    hDV    .push_back( fidksmDV    );
    hDVstr .push_back( fidksmDVstr );
  }
  // vertices by (leading) jets and passing fiducial + k-short-mass cuts
  std::string jfidksmDV     = "byJetFiducKsm";
  std::string ljfidksmDV    = "byLeadJetFiducKsm";
  std::string jfidksmDVstr  = "by-jet-fiduc-ksm-cut";
  std::string ljfidksmDVstr = "by-lead-jet-fiduc-ksm-cut";
  if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts    &&
					  m_histoInfoSwitch->m_fiducialVerts && m_histoInfoSwitch->m_ksmVerts ) ) {
    hDV    .push_back( jfidksmDV     );
    hDV    .push_back( ljfidksmDV    );
    hDVstr .push_back( jfidksmDVstr  );
    hDVstr .push_back( ljfidksmDVstr );
  }
  // --> eventually add further above individual cuts to these combinations after seeing impact on variables of interest...
  // --> don't forget to add to truth dv's as well
  // --> maybe start with n-1 combinations and go backwards ??
    
  // truth-matched vertices (testing matching criteria)
  // --> initial matching criteria (v0): match score > 0; no requirement on no. / type of matches (may be matched to multiple llps)
  // --> --> test other criteria: additional distance-based requirement; require single match or llp type
  if ( m_mc && m_histoInfoSwitch->m_vtxTruth ) {
    //std::vector<std::string> mDV     = { "darkPion",  "kshort",   "nomatch"   };
    //std::vector<std::string> mDVstr  = { "dark pion", "k-short",  "unmatched" };
    std::vector<std::string> mDV     = { "darkPion"  };
    std::vector<std::string> mDVstr  = { "dark pion" };
    std::vector<std::string> miDV, miDVstr;
    for ( size_t ihdv = 0; ihdv != hDV.size(); ++ihdv ) {
      miDV    .push_back( hDV    [ihdv] );
      miDVstr .push_back( hDVstr [ihdv] );
    }
    for ( size_t i = 0; i != mDV.size(); ++i ) {
      hDV    .push_back( mDV    [i] );
      hDVstr .push_back( mDVstr [i] );
      for ( size_t j = 0; j != miDV.size(); ++j ) {
	if ( j == 0 ) continue; // skip base DV name for nominal case
	std::string mDVs = mDV[i]; mDVs[0] = toupper(mDVs[0]);
	hDV    .push_back( miDV    [j] +       mDVs      );
	hDVstr .push_back( miDVstr [j] + " " + mDVstr[i] );
      }
    }
  }
  m_nTypeDVs = hDV.size();

  // loop over regions + book histograms
  for ( size_t ireg = 0; ireg != regions.size(); ++ireg ) {
    const EJsHelper::Region region = regions[ireg];
    const std::string       name   = m_name + outFileName + "/" + region.name + "/";

    // initialize count vectors
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
    h_MetaData_EventCount [ireg] ->GetXaxis()->SetBinLabel( 1, "nEvents initial"              );
    h_MetaData_EventCount [ireg] ->GetXaxis()->SetBinLabel( 2, "nEvents selected"             );
    h_MetaData_EventCount [ireg] ->GetXaxis()->SetBinLabel( 3, "sumOfWeights initial"         );
    h_MetaData_EventCount [ireg] ->GetXaxis()->SetBinLabel( 4, "sumOfWeights selected"        );
    h_MetaData_EventCount [ireg] ->GetXaxis()->SetBinLabel( 5, "sumOfWeightsSquared initial"  );
    h_MetaData_EventCount [ireg] ->GetXaxis()->SetBinLabel( 6, "sumOfWeightsSquared selected" );
    h_MetaData_Weights    .push_back( book( name, "MetaData_Weights", "", 4, 1, 5 ) );
    h_MetaData_Weights    [ireg] ->GetXaxis()->SetBinLabel( 1, "cross-section [fb]" );
    h_MetaData_Weights    [ireg] ->GetXaxis()->SetBinLabel( 2, "k-factor"           );
    h_MetaData_Weights    [ireg] ->GetXaxis()->SetBinLabel( 3, "gen-filter eff"     );
    h_MetaData_Weights    [ireg] ->GetXaxis()->SetBinLabel( 4, "lumi scale [ifb]"   ); // --> luminosity to scale to 
    
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
    h_njetHt      .push_back( book( name, "NJetHt",      "leading N " + m_jetStr + " Jet H_{T} [GeV]",            100, njetht_xmin, 3500 ) );
    h_njetHt_vrsh .push_back( book( name, "NJetHt_vrsh", "leading N " + m_jetStr + " Jet H_{T} [GeV] (VR-shift)", 100, njetht_xmin, 3500 ) );

    
    // --- RECO JETS --- //
    std::vector<TH1F*> h_j_n;
    std::vector<TH1F*> h_j_pt;
    std::vector<TH1F*> h_j_pt_l;
    std::vector<TH1F*> h_j_pt_m;
    std::vector<TH1F*> h_j_pt_s;
    std::vector<TH1F*> h_j_eta;
    std::vector<TH1F*> h_j_phi;
    std::vector<TH1F*> h_j_E;
    std::vector<TH1F*> h_j_M;
    std::vector<TH1F*> h_j_rapid;
    std::vector<TH1F*> h_j_px;
    std::vector<TH1F*> h_j_py;
    std::vector<TH1F*> h_j_pz;
    std::vector<TH1F*> h_j_Et;
    std::vector<TH1F*> h_j_Et_m;
    std::vector<TH1F*> h_j_Et_s;
    std::vector<std::vector<TH1F*>> h_j_ntrk;
    std::vector<std::vector<TH1F*>> h_j_trk_dR;
    std::vector<TH1F*> h_j_nsv;
    std::vector<TH1F*> h_j_sv_dR;
    std::vector<TH1F*> h_jj_n;
    std::vector<TH1F*> h_jj_pt;
    std::vector<TH1F*> h_jj_eta;
    std::vector<TH1F*> h_jj_phi;
    std::vector<TH1F*> h_jj_m;
    std::vector<TH1F*> h_jj_sumPt;
    std::vector<TH1F*> h_jj_dR;
    std::vector<TH1F*> h_jj_max_pt;
    std::vector<TH1F*> h_jj_max_eta;
    std::vector<TH1F*> h_jj_max_phi;
    std::vector<TH1F*> h_jj_max_m;
    std::vector<TH1F*> h_jj_max_sumPt;
    std::vector<TH1F*> h_jj_max_dR;
    std::vector<TH1F*> h_jj_min_pt;
    std::vector<TH1F*> h_jj_min_eta;
    std::vector<TH1F*> h_jj_min_phi;
    std::vector<TH1F*> h_jj_min_m;
    std::vector<TH1F*> h_jj_min_sumPt;
    std::vector<TH1F*> h_jj_min_dR;
    std::vector<TH1F*> h_jj_avg_pt;
    std::vector<TH1F*> h_jj_avg_eta;
    std::vector<TH1F*> h_jj_avg_phi;
    std::vector<TH1F*> h_jj_avg_m;
    std::vector<TH1F*> h_jj_avg_sumPt;
    std::vector<TH1F*> h_jj_avg_dR;
    std::vector<TH1F*> h_nj_pt;
    std::vector<TH1F*> h_nj_eta;
    std::vector<TH1F*> h_nj_phi;
    std::vector<TH1F*> h_nj_m;
    std::vector<TH1F*> h_nj_sumPt;
    for ( size_t i = 0; i != hJ.size(); ++i ) {
      std::string jetHistNameUp = jetHistName; jetHistNameUp[0] = toupper(jetHistNameUp[0]);
      std::string hjName   = "";
      std::string hjjName  = "";
      std::string hjString = "";
      if ( hJ [i].empty() ) {
	hjName  = hJ[i]        + jetHistName;
	hjjName = hJ[i] + "di" + jetHistName;
      }
      else {
	hjName  = hJ[i]        + jetHistNameUp;
	hjjName = hJ[i] + "Di" + jetHistName;
      }
      if ( hJstr[i].empty() ) hjString = hJstr[i];
      else                    hjString = hJstr[i] + " ";
      std::string hj     = hjName;
      std::string hjstr  = hjString + m_jetStr + " jet";
      std::string hjj    = hjjName;
      std::string hjjstr = hjString + m_jetStr + " dijet";
      std::string hnj    = hJ[i]    + "N" + jetHistName;
      std::string hnjstr = hjString + m_jetStr + "N-jet";
      
      h_j_n      .push_back( book( name, hj + "_n",     "n " + hjstr + "s",       20,     0,   20 ) );
      h_j_pt     .push_back( book( name, hj + "_pt",    hjstr + " p_{T} [GeV]",  100,     0, 1500 ) );
      h_j_pt_l   .push_back( book( name, hj + "_pt_l",  hjstr + " p_{T} [GeV]",  100,     0, 2500 ) );
      h_j_pt_m   .push_back( book( name, hj + "_pt_m",  hjstr + " p_{T} [GeV]",  100,     0,  500 ) );
      h_j_pt_s   .push_back( book( name, hj + "_pt_s",  hjstr + " p_{T} [GeV]",  100,     0,  200 ) );
      h_j_eta    .push_back( book( name, hj + "_eta",   hjstr + " eta",          100,    -5,    5 ) );
      h_j_phi    .push_back( book( name, hj + "_phi",   hjstr + " phi",          100,  -3.5,  3.5 ) );
      h_j_E      .push_back( book( name, hj + "_E",     hjstr + " energy [GeV]", 100,     0, 2500 ) );
      h_j_M      .push_back( book( name, hj + "_M",     hjstr + " mass [GeV]",   100,     0,  250 ) );
      h_j_rapid  .push_back( book( name, hj + "_rapid", hjstr + " rapidity",     100,    -5,    5 ) );
      // jets: extra kinematics
      if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	h_j_px   .push_back( book( name, hj + "_px",    hjstr + " p_{x} [GeV]",  100, -1500, 1500 ) );
	h_j_py   .push_back( book( name, hj + "_py",    hjstr + " p_{y} [GeV]",  100, -1500, 1500 ) );
	h_j_pz   .push_back( book( name, hj + "_pz",    hjstr + " p_{z} [GeV]",  100, -2500, 2500 ) );
	h_j_Et   .push_back( book( name, hj + "_Et",    hjstr + " E_{T} [GeV]",  100,     0, 1500 ) );
	h_j_Et_m .push_back( book( name, hj + "_Et_m",  hjstr + " E_{T} [GeV]",  100,     0,  500 ) );
	h_j_Et_s .push_back( book( name, hj + "_Et_s",  hjstr + " E_{T} [GeV]",  100,     0,  200 ) );
      }
      
      // jets: matched tracks
      std::vector<TH1F*> h_j_ntrack;
      std::vector<TH1F*> h_j_track_dR;
      for ( size_t j = 0; j != hTrk.size(); ++j ) {
	std::string ht    = hTrk[j] + "trk";
	std::string hjt   = hj + "_" + ht;
	std::string htstr = "matched";
	if ( hTrkstr[j].empty() ) htstr += " ";
	htstr += hTrkstr[j] + " track";
	int nbin = njtrk_xmax[j];
	if ( j < 2 ) nbin = njtrk_xmax[j] / 2;
	h_j_ntrack     .push_back( book( name, hj + "_n" + ht, "n " + htstr + "s per " + hjstr, nbin, 0, njtrk_xmax[j] ) );
	if ( m_histoInfoSwitch->m_jetTrks ) {
	  h_j_track_dR .push_back( book( name, hjt + "_dR",    hjstr + " - " + htstr + " dR",   100,  0,              0.6 ) );
	}
      }
      h_j_ntrk     .push_back( h_j_ntrack   );
      if ( m_histoInfoSwitch->m_jetTrks ) {
	h_j_trk_dR .push_back( h_j_track_dR );
      }
      
      // jets: matched secondary vertices --> eventually will want to look at matched "good" DVs (when cuts finalized)...
      h_j_nsv     .push_back( book( name, hj + "_nsv",   "n matched secondary vertices per " + hjstr, 10,  0,  10 ) );
      if ( m_histoInfoSwitch->m_jetVerts ) {
	h_j_sv_dR .push_back( book( name, hj + "_sv_dR", hjstr + " - secondary vertex dR",            100, 0, 0.6 ) );
      }
      
      // dijets
      if ( m_histoInfoSwitch->m_dijets ) {
	h_jj_n         .push_back( book( name, hjj + "_n",           "n " + hjjstr + "s",                     100,    0,   60 ) );
	h_jj_pt        .push_back( book( name, hjj + "_pt",          hjjstr + " p_{T} [GeV]",                 100,    0, 3000 ) );
	h_jj_eta       .push_back( book( name, hjj + "_eta",         hjjstr + " eta",                         100,   -5,    5 ) );
	h_jj_phi       .push_back( book( name, hjj + "_phi",         hjjstr + " phi",                         100, -3.5,  3.5 ) );
	h_jj_m         .push_back( book( name, hjj + "_m",           hjjstr + " invariant mass [GeV]",        100,    0, 4500 ) );
	h_jj_sumPt     .push_back( book( name, hjj + "_sumPt",       hjjstr + " sum-p_{T} [GeV]",             100,    0, 4500 ) );
	h_jj_dR        .push_back( book( name, hjj + "_dR",          hjjstr + " dR",                          100,    0,   10 ) );
	// max dijet system
	h_jj_max_pt    .push_back( book( name, hjj + "_maxP4_pt",    hjjstr + " max-p4 p_{T} [GeV]",          100,    0, 3000 ) );
	h_jj_max_eta   .push_back( book( name, hjj + "_maxP4_eta",   hjjstr + " max-p4 eta",                  100,   -5,    5 ) );
	h_jj_max_phi   .push_back( book( name, hjj + "_maxP4_phi",   hjjstr + " max-p4 phi",                  100, -3.5,  3.5 ) );
	h_jj_max_m     .push_back( book( name, hjj + "_maxP4_m",     hjjstr + " max-p4 invariant mass [GeV]", 100,    0, 4500 ) );
	h_jj_max_sumPt .push_back( book( name, hjj + "_maxP4_sumPt", hjjstr + " max-p4 sum-p_{T} [GeV]",      100,    0, 4500 ) );
	h_jj_max_dR    .push_back( book( name, hjj + "_maxP4_dR",    hjjstr + " max-p4 dR",                   100,    0,   10 ) );
	// min dijet system
	h_jj_min_pt    .push_back( book( name, hjj + "_minP4_pt",    hjjstr + " min-p4 p_{T} [GeV]",          100,    0, 3000 ) );
	h_jj_min_eta   .push_back( book( name, hjj + "_minP4_eta",   hjjstr + " min-p4 eta",                  100,   -5,    5 ) );
	h_jj_min_phi   .push_back( book( name, hjj + "_minP4_phi",   hjjstr + " min-p4 phi",                  100, -3.5,  3.5 ) );
	h_jj_min_m     .push_back( book( name, hjj + "_minP4_m",     hjjstr + " min-p4 invariant mass [GeV]", 100,    0, 4500 ) );
	h_jj_min_sumPt .push_back( book( name, hjj + "_minP4_sumPt", hjjstr + " min-p4 sum-p_{T} [GeV]",      100,    0, 4500 ) );
	h_jj_min_dR    .push_back( book( name, hjj + "_minP4_dR",    hjjstr + " min-p4 dR",                   100,    0,   10 ) );
	// avg dijet system
	h_jj_avg_pt    .push_back( book( name, hjj + "_avgP4_pt",    hjjstr + " avg-p4 p_{T} [GeV]",          100,    0, 3000 ) );
	h_jj_avg_eta   .push_back( book( name, hjj + "_avgP4_eta",   hjjstr + " avg-p4 eta",                  100,   -5,    5 ) );
	h_jj_avg_phi   .push_back( book( name, hjj + "_avgP4_phi",   hjjstr + " avg-p4 phi",                  100, -3.5,  3.5 ) );
	h_jj_avg_m     .push_back( book( name, hjj + "_avgP4_m",     hjjstr + " avg-p4 invariant mass [GeV]", 100,    0, 4500 ) );
	h_jj_avg_sumPt .push_back( book( name, hjj + "_avgP4_sumPt", hjjstr + " avg-p4 sum-p_{T} [GeV]",      100,    0, 4500 ) );
	h_jj_avg_dR    .push_back( book( name, hjj + "_avgP4_dR",    hjjstr + " avg-p4 dR",                   100,    0,   10 ) );
      }
      
      // event-level jets (all jets in event)
      h_nj_pt    .push_back( book( name, hnj + "_pt",    hnjstr + " p_{T} [GeV]",          100,    0, 1000 ) );
      h_nj_eta   .push_back( book( name, hnj + "_eta",   hnjstr + " eta",                  100,  -10,   10 ) );
      h_nj_phi   .push_back( book( name, hnj + "_phi",   hnjstr + " phi",                  100, -3.5,  3.5 ) );
      h_nj_m     .push_back( book( name, hnj + "_m",     hnjstr + " invariant mass [GeV]", 100,    0, 7500 ) );
      h_nj_sumPt .push_back( book( name, hnj + "_sumPt", hnjstr + " sum-p_{T} [GeV]",      100,    0, 6000 ) );
    }
    h_jet_n      .push_back( h_j_n     );
    h_jet_pt     .push_back( h_j_pt    );
    h_jet_pt_l   .push_back( h_j_pt_l  );
    h_jet_pt_m   .push_back( h_j_pt_m  );
    h_jet_pt_s   .push_back( h_j_pt_s  );
    h_jet_eta    .push_back( h_j_eta   );
    h_jet_phi    .push_back( h_j_phi   );
    h_jet_E      .push_back( h_j_E     );
    h_jet_M      .push_back( h_j_M     );
    h_jet_rapid  .push_back( h_j_rapid );
    if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
      h_jet_px   .push_back( h_j_px    );
      h_jet_py   .push_back( h_j_py    );
      h_jet_pz   .push_back( h_j_pz    );
      h_jet_Et   .push_back( h_j_Et    );
      h_jet_Et_m .push_back( h_j_Et_m  );
      h_jet_Et_s .push_back( h_j_Et_s  );
    }
    h_jet_ntrk     .push_back( h_j_ntrk   );
    if ( m_histoInfoSwitch->m_jetTrks ) {
      h_jet_trk_dR .push_back( h_j_trk_dR );
    }
    h_jet_nsv      .push_back( h_j_nsv    );
    if ( m_histoInfoSwitch->m_jetVerts ) {
      h_jet_sv_dR  .push_back( h_j_sv_dR  );
    }

    // N leading jets
    if ( m_numLeadJets ) {
      std::vector<TH1F*> h_nleadj_pt;
      std::vector<TH1F*> h_nleadj_pt_l;
      std::vector<TH1F*> h_nleadj_pt_m;
      std::vector<TH1F*> h_nleadj_pt_s;
      std::vector<TH1F*> h_nleadj_eta;
      std::vector<TH1F*> h_nleadj_phi;
      std::vector<TH1F*> h_nleadj_E;
      std::vector<TH1F*> h_nleadj_M;
      std::vector<TH1F*> h_nleadj_rapid;
      std::vector<TH1F*> h_nleadj_Et;
      std::vector<TH1F*> h_nleadj_Et_m;
      std::vector<TH1F*> h_nleadj_Et_s;
      std::vector<TH1F*> h_nleadj_ntrk;
      std::vector<TH1F*> h_nleadj_trk_dR;
      std::vector<TH1F*> h_nleadj_nsv;
      std::vector<TH1F*> h_nleadj_sv_dR;
      for ( int i = 0; i != m_numLeadJets; ++i ) {
	std::string njet     = std::to_string(i);
	std::string hnjet    = jetHistName + njet;
	std::string hnjetStr = m_jetStr + " jet" + "-" + njet;
	h_nleadj_pt     .push_back( book( name, hnjet + "_pt",    hnjetStr + " p_{T} [GeV]",                       100,    0, 1500 ) );
	h_nleadj_pt_l   .push_back( book( name, hnjet + "_pt_l",  hnjetStr + " p_{T} [GeV]",                       100,    0, 2500 ) );
	h_nleadj_pt_m   .push_back( book( name, hnjet + "_pt_m",  hnjetStr + " p_{T} [GeV]",                       100,    0,  500 ) );
	h_nleadj_pt_s   .push_back( book( name, hnjet + "_pt_s",  hnjetStr + " p_{T} [GeV]",                       100,    0,  200 ) );
	h_nleadj_eta    .push_back( book( name, hnjet + "_eta",   hnjetStr + " eta",                               100,   -5,    5 ) );
	h_nleadj_phi    .push_back( book( name, hnjet + "_phi",   hnjetStr + " phi",                               100, -3.5,  3.5 ) );
	h_nleadj_E      .push_back( book( name, hnjet + "_E",     hnjetStr + " energy [GeV]",                      100,    0, 2500 ) );
	h_nleadj_M      .push_back( book( name, hnjet + "_M",     hnjetStr + " mass [GeV]",                        100,    0,  250 ) );
	h_nleadj_rapid  .push_back( book( name, hnjet + "_rapid", hnjetStr + " rapidity",                          100,   -5,    5 ) );
	h_nleadj_Et     .push_back( book( name, hnjet + "_Et",    hnjetStr + " E_{T} [GeV]",                       100,    0, 1500 ) );
	h_nleadj_Et_m   .push_back( book( name, hnjet + "_Et_m",  hnjetStr + " E_{T} [GeV]",                       100,    0,  500 ) );
	h_nleadj_Et_s   .push_back( book( name, hnjet + "_Et_s",  hnjetStr + " E_{T} [GeV]",                       100,    0,  200 ) );
	h_nleadj_ntrk   .push_back( book( name, hnjet + "_ntrk",   "n matched tracks per " + hnjetStr,             100,    0,  200 ) );
	h_nleadj_trk_dR .push_back( book( name, hnjet + "_trk_dR", hnjetStr + " - track dR",                       100,    0,  0.6 ) );
	h_nleadj_nsv    .push_back( book( name, hnjet + "_nsv",    "n matched secondary vertices per " + hnjetStr,  10,    0,   10 ) );
	h_nleadj_sv_dR  .push_back( book( name, hnjet + "_sv_dR",  hnjetStr + " - secondary vertex dR",            100,    0,  0.6 ) );
      }
      h_jetN_pt     .push_back( h_nleadj_pt    );
      h_jetN_pt_l   .push_back( h_nleadj_pt_l  );
      h_jetN_pt_m   .push_back( h_nleadj_pt_m  );
      h_jetN_pt_s   .push_back( h_nleadj_pt_s  );
      h_jetN_eta    .push_back( h_nleadj_eta   );
      h_jetN_phi    .push_back( h_nleadj_phi   );
      h_jetN_E      .push_back( h_nleadj_E     );
      h_jetN_M      .push_back( h_nleadj_M     );
      h_jetN_rapid  .push_back( h_nleadj_rapid );
      if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	h_jetN_Et   .push_back( h_nleadj_Et    );
	h_jetN_Et_m .push_back( h_nleadj_Et_m  );
	h_jetN_Et_s .push_back( h_nleadj_Et_s  );
      }
      h_jetN_ntrk     .push_back( h_nleadj_ntrk   );
      if ( m_histoInfoSwitch->m_jetTrks ) {
	h_jetN_trk_dR .push_back( h_nleadj_trk_dR );
      }
      h_jetN_nsv      .push_back( h_nleadj_nsv    );
      if ( m_histoInfoSwitch->m_jetVerts ) {
	h_jetN_sv_dR  .push_back( h_nleadj_sv_dR   );
      }
    }
    
    if ( m_histoInfoSwitch->m_dijets ) {
      h_dijet_n           .push_back( h_jj_n         );
      h_dijet_pt          .push_back( h_jj_pt        );
      h_dijet_eta         .push_back( h_jj_eta       );
      h_dijet_phi         .push_back( h_jj_phi       );
      h_dijet_m           .push_back( h_jj_m         );
      h_dijet_sumPt       .push_back( h_jj_sumPt     );
      h_dijet_dR          .push_back( h_jj_dR        );
      h_dijet_maxp4_pt    .push_back( h_jj_max_pt    );
      h_dijet_maxp4_eta   .push_back( h_jj_max_eta   );
      h_dijet_maxp4_phi   .push_back( h_jj_max_phi   );
      h_dijet_maxp4_m     .push_back( h_jj_max_m     );
      h_dijet_maxp4_sumPt .push_back( h_jj_max_sumPt );
      h_dijet_maxp4_dR    .push_back( h_jj_max_dR    );
      h_dijet_minp4_pt    .push_back( h_jj_min_pt    );
      h_dijet_minp4_eta   .push_back( h_jj_min_eta   );
      h_dijet_minp4_phi   .push_back( h_jj_min_phi   );
      h_dijet_minp4_m     .push_back( h_jj_min_m     );
      h_dijet_minp4_sumPt .push_back( h_jj_min_sumPt );
      h_dijet_minp4_dR    .push_back( h_jj_min_dR    );
      h_dijet_avgp4_pt    .push_back( h_jj_avg_pt    );
      h_dijet_avgp4_eta   .push_back( h_jj_avg_eta   );
      h_dijet_avgp4_phi   .push_back( h_jj_avg_phi   );
      h_dijet_avgp4_m     .push_back( h_jj_avg_m     );
      h_dijet_avgp4_sumPt .push_back( h_jj_avg_sumPt );
      h_dijet_avgp4_dR    .push_back( h_jj_avg_dR    );
    }
    h_njet_pt    .push_back( h_nj_pt    );
    h_njet_eta   .push_back( h_nj_eta   );
    h_njet_phi   .push_back( h_nj_phi   );
    h_njet_m     .push_back( h_nj_m     );
    h_njet_sumPt .push_back( h_nj_sumPt );

    h_NJetMjj         .push_back( book( name, "h_NJetMjj",
					"leading N " + m_jetStr + " dijet invariant mass [GeV]",                  100, 0, 3500 ) );
    h_NJetMjjDiff     .push_back( book( name, "h_NJetMjjDiff",
					"leading N " + m_jetStr + " dijet invariant mass difference [GeV]",       100, 0, 2000 ) );
    h_NJetMjj_all     .push_back( book( name, "h_NJetMjj_all",
					"leading N " + m_jetStr + " dijet invariant mass (all) [GeV]",            100, 0, 3500 ) );
    h_NJetMjjDiff_all .push_back( book( name, "h_NJetMjjDiff_all",
					"leading N " + m_jetStr + " dijet invariant mass difference (all) [GeV]", 100, 0, 4500 ) );

    
    // --- TRACKS --- //
    // tracks: basics / kinematics
    std::vector<TH1F*> h_track_n;
    for ( size_t i = 0; i != hTrk.size(); ++i ) {
      std::string ht    = hTrk   [i] + "trk";
      std::string htstr = hTrkstr[i] + " track";
      int nbin = 100;
      if ( i > 2 ) nbin = ntrk_xmax[i];
      h_track_n .push_back( book( name, ht + "_n", "n " + htstr + "s", nbin, 0, ntrk_xmax[i] ) );
    }
    h_trk_n .push_back( h_track_n );
    
    
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
    std::vector<TH1F*> h_dv_pt_s;
    std::vector<TH1F*> h_dv_pt_xs;
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
    std::vector<TH1F*> h_dv_ntrk_d0;
    std::vector<TH1F*> h_dv_ntrk_seld0;
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
    std::vector<TH1F*> h_dv_jetDR;
    std::vector<TH1F*> h_dv_leadJetDR;
    std::vector<TH1F*> h_dv_trk_qOverP;
    std::vector<TH1F*> h_dv_trk_theta;
    std::vector<TH1F*> h_dv_trk_pt;
    std::vector<TH1F*> h_dv_trk_eta;
    std::vector<TH1F*> h_dv_trk_phi;
    std::vector<TH1F*> h_dv_trk_d0;
    std::vector<TH1F*> h_dv_trk_d0_xs;
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
    std::vector<TH1F*> h_dv_seltrk_d0;
    std::vector<TH1F*> h_dv_seltrk_d0_xs;
    std::vector<TH1F*> h_dv_sumd0;
    std::vector<TH1F*> h_dv_sumz0;
    std::vector<TH1F*> h_dv_sumP;
    std::vector<TH1F*> h_dv_sumsqrtd0;
    std::vector<TH1F*> h_dv_sumsqrtz0;
    std::vector<TH1F*> h_dv_sumsqrtP;
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
    std::vector<TH1F*> h_dv_sumsqrtd0_sv;
    std::vector<TH1F*> h_dv_sumsqrtz0_sv;
    std::vector<TH1F*> h_dv_sumsqrtP_sv;
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
    std::vector<TH1F*> h_dv_minsqrtd0;
    std::vector<TH1F*> h_dv_minsqrtz0;
    std::vector<TH1F*> h_dv_minsqrtP;
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
    std::vector<TH1F*> h_dv_minsqrtd0_sv;
    std::vector<TH1F*> h_dv_minsqrtz0_sv;
    std::vector<TH1F*> h_dv_minsqrtP_sv;
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
    std::vector<TH1F*> h_dv_maxsqrtd0;
    std::vector<TH1F*> h_dv_maxsqrtz0;
    std::vector<TH1F*> h_dv_maxsqrtP;
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
    std::vector<TH1F*> h_dv_maxsqrtd0_sv;
    std::vector<TH1F*> h_dv_maxsqrtz0_sv;
    std::vector<TH1F*> h_dv_maxsqrtP_sv;
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
    std::vector<std::vector<TH1F*>> h_ntrkdv_mass_xs;
    std::vector<std::vector<TH1F*>> h_ntrkdv_direction;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minOpAng;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxOpAng;
    std::vector<std::vector<TH1F*>> h_ntrkdv_chi2;
    std::vector<std::vector<TH1F*>> h_ntrkdv_chi2_s;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumd0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumz0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumP;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumd0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumz0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumP_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumsqrtd0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumsqrtz0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumsqrtP;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumsqrtd0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumsqrtz0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_sumsqrtP_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_mind0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minz0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minP;
    std::vector<std::vector<TH1F*>> h_ntrkdv_mind0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minz0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minP_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minsqrtd0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minsqrtz0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minsqrtP;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minsqrtd0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minsqrtz0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_minsqrtP_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxd0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxz0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxP;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxd0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxz0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxP_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxsqrtd0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxsqrtz0;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxsqrtP;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxsqrtd0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxsqrtz0_sv;
    std::vector<std::vector<TH1F*>> h_ntrkdv_maxsqrtP_sv;
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
      std::string hdv    = hDV   [i] +  "DV";
      std::string hdvstr = hDVstr[i] + " DV";
      h_dv_n            .push_back( book( name, hdv + "_n",          "n " + hdvstr + "s",                   15,    0,  15 ) );
      h_dv_x            .push_back( book( name, hdv + "_x",          hdvstr + " x-pos [mm]",               100, -400,  400 ) );
      h_dv_y            .push_back( book( name, hdv + "_y",          hdvstr + " y-pos [mm]",               100, -400,  400 ) );
      h_dv_z            .push_back( book( name, hdv + "_z",          hdvstr + " z-pos [mm]",               100, -800,  800 ) );
      h_dv_r            .push_back( book( name, hdv + "_r",          hdvstr + " r-pos [mm]",               100,    0,  400 ) );
      h_dv_x_s          .push_back( book( name, hdv + "_x_s",        hdvstr + " x-pos [mm]",               100, -300,  300 ) );
      h_dv_y_s          .push_back( book( name, hdv + "_y_s",        hdvstr + " y-pos [mm]",               100, -300,  300 ) );
      h_dv_z_s          .push_back( book( name, hdv + "_z_s",        hdvstr + " z-pos [mm]",               100, -300,  300 ) );
      h_dv_r_s          .push_back( book( name, hdv + "_r_s",        hdvstr + " r-pos [mm]",               100,    0,  300 ) );
      h_dv_phipos       .push_back( book( name, hdv + "_phipos",     hdvstr + " phi-pos",                  100, -3.5,  3.5 ) );
      h_dv_pt           .push_back( book( name, hdv + "_pt",         hdvstr + " p_{T} [GeV]",              100,    0,  100 ) );
      h_dv_pt_s         .push_back( book( name, hdv + "_pt_s",       hdvstr + " p_{T} [GeV]",              100,    0,   50 ) );
      h_dv_pt_xs        .push_back( book( name, hdv + "_pt_xs",      hdvstr + " p_{T} [GeV]",              100,    0,   10 ) );
      h_dv_eta          .push_back( book( name, hdv + "_eta",        hdvstr + " eta",                      100,   -5,    5 ) );
      h_dv_phi          .push_back( book( name, hdv + "_phi",        hdvstr + " phi",                      100, -3.5,  3.5 ) );
      h_dv_mass         .push_back( book( name, hdv + "_mass",       hdvstr + " mass [GeV]",               100,    0,   50 ) );
      h_dv_mass_l       .push_back( book( name, hdv + "_mass_l",     hdvstr + " mass [GeV]",               100,    0,  100 ) );
      h_dv_mass_s       .push_back( book( name, hdv + "_mass_s",     hdvstr + " mass [GeV]",               100,    0,   25 ) );
      h_dv_mass_xs      .push_back( book( name, hdv + "_mass_xs",    hdvstr + " mass [GeV]",               100,    0,    5 ) );
      h_dv_massNA       .push_back( book( name, hdv + "_massNA",     hdvstr + " non-assoc. mass [GeV]",    100,    0,   50 ) );
      h_dv_massNA_l     .push_back( book( name, hdv + "_massNA_l",   hdvstr + " non-assoc. mass [GeV]",    100,    0,  100 ) );
      h_dv_massNA_s     .push_back( book( name, hdv + "_massNA_s",   hdvstr + " non-assoc. mass [GeV]",    100,    0,   25 ) );
      h_dv_massNA_xs    .push_back( book( name, hdv + "_massNA_xs",  hdvstr + " non-assoc. mass [GeV]",    100,    0,    5 ) );
      h_dv_direction    .push_back( book( name, hdv + "_direction",  hdvstr + " direction",                100, -1.1,  1.1 ) );
      h_dv_minOpAng     .push_back( book( name, hdv + "_minOpAng",   hdvstr + " cos min opening angle",    100, -1.1,  1.1 ) );
      h_dv_maxOpAng     .push_back( book( name, hdv + "_maxOpAng",   hdvstr + " cos max opening angle",    100, -1.1,  1.1 ) );
      h_dv_chi2         .push_back( book( name, hdv + "_chi2",       hdvstr + " chi2 / nDoF",              100,    0,   10 ) );
      h_dv_chi2_s       .push_back( book( name, hdv + "_chi2_s",     hdvstr + " chi2 / nDoF",              100,    0,    5 ) );
      h_dv_ntrk         .push_back( book( name, hdv + "_ntrk",       "n " + hdvstr + " tracks",             10,    2,   12 ) );
      h_dv_ntrk_final   .push_back( book( name, hdv + "_ntrk_final", "n " + hdvstr + " final tracks",       10,    2,   12 ) );
      h_dv_ntrk_sel     .push_back( book( name, hdv + "_ntrk_sel",   "n " + hdvstr + " selected tracks",    10,    2,   12 ) );
      h_dv_ntrk_assoc   .push_back( book( name, hdv + "_ntrk_assoc", "n " + hdvstr + " associated tracks",  10,    2,   12 ) );
      h_dv_ntrk_lrt     .push_back( book( name, hdv + "_ntrk_lrt",   "n " + hdvstr + " large-radius tracks",10,    2,   12 ) );
      h_dv_ntrk_d0      .push_back( book( name, hdv + "_ntrk_d0",    "n " + hdvstr + " |d0| > 2.0 tracks",  10,    0,   10 ) );
      h_dv_ntrk_seld0   .push_back( book( name, hdv + "_ntrk_seld0", "n " + hdvstr + " |d0| > 2.0 selected tracks",10,0,10 ) );
      if ( m_histoInfoSwitch->m_vtxErrors ) {
	h_dv_errx       .push_back( book( name, hdv + "_errx",       hdvstr + " x-pos uncert.",            100,    0,   25 ) );
	h_dv_erry       .push_back( book( name, hdv + "_erry",       hdvstr + " y-pos uncert.",            100,    0,   25 ) );
	h_dv_errz       .push_back( book( name, hdv + "_errz",       hdvstr + " z-pos uncert.",            100,    0,   25 ) );
	h_dv_errr       .push_back( book( name, hdv + "_errr",       hdvstr + " r-pos uncert.",            100,    0,   25 ) );
	h_dv_errphi     .push_back( book( name, hdv + "_errphi",     hdvstr + " phi uncert.",              100,    0, 0.15 ) );
	h_dv_sqrterrx   .push_back( book( name, hdv + "_sqrterrx",   hdvstr + " x-pos sqrt-uncert.",       100,    0,    5 ) );
	h_dv_sqrterry   .push_back( book( name, hdv + "_sqrterry",   hdvstr + " y-pos sqrt-uncert.",       100,    0,    5 ) );
	h_dv_sqrterrz   .push_back( book( name, hdv + "_sqrterrz",   hdvstr + " z-pos sqrt-uncert.",       100,    0,    5 ) );
	h_dv_sqrterrr   .push_back( book( name, hdv + "_sqrterrr",   hdvstr + " r-pos sqrt-uncert.",       100,    0,    5 ) );
	h_dv_sqrterrphi .push_back( book( name, hdv + "_sqrterrphi", hdvstr + " phi sqrt-uncert.",         100,    0,  0.4 ) );
	h_dv_fracerrx   .push_back( book( name, hdv + "_fracerrx",   hdvstr + " x-pos fractional uncert.", 100,    0,  0.1 ) );
	h_dv_fracerry   .push_back( book( name, hdv + "_fracerry",   hdvstr + " y-pos fractional uncert.", 100,    0,  0.1 ) );
	h_dv_fracerrz   .push_back( book( name, hdv + "_fracerrz",   hdvstr + " z-pos fractional uncert.", 100,    0,  0.1 ) );
	h_dv_fracerrr   .push_back( book( name, hdv + "_fracerrr",   hdvstr + " r-pos fractional uncert.", 100,    0,  0.1 ) );
	h_dv_fracerrphi .push_back( book( name, hdv + "_fracerrphi", hdvstr + " phi fractional uncert.",   100,    0,  0.1 ) );
	h_dv_signifx    .push_back( book( name, hdv + "_signifx",    hdvstr + " x-pos significance",       100,    0, 1000 ) );
	h_dv_signify    .push_back( book( name, hdv + "_signify",    hdvstr + " y-pos significance",       100,    0, 1000 ) );
	h_dv_signifz    .push_back( book( name, hdv + "_signifz",    hdvstr + " z-pos significance",       100,    0, 1000 ) );
	h_dv_signifr    .push_back( book( name, hdv + "_signifr",    hdvstr + " r-pos significance",       100,    0, 1000 ) );
	h_dv_signifphi  .push_back( book( name, hdv + "_signifphi",  hdvstr + " phi-pos significance",     100,    0, 1000 ) );
      }
      // vertex nearby jets
      h_dv_jetDR        .push_back( book( name, hdv + "_jetDR",      hdvstr + " - jet dR",                 100,    0,  0.6 ) );
      h_dv_leadJetDR    .push_back( book( name, hdv + "_leadJetDR",  hdvstr + " - lead jet dR",            100,    0,  0.6 ) );

      // vertex tracks
      std::string hDVtrk       = hdv    + "_trk";
      std::string hDVtrkstr    = hdvstr + " track";
      std::string hDVseltrk    = hdv    + "_seltrk";
      std::string hDVseltrkstr = hdvstr + " selected track";
      if ( m_histoInfoSwitch->m_vtxTrks ) {
	h_dv_trk_qOverP       .push_back( book( name, hDVtrk + "_qOverP",       hDVtrkstr + " q/p [e/GeV]",             100,  -1.1,   1.1 ) );
	h_dv_trk_theta        .push_back( book( name, hDVtrk + "_theta",        hDVtrkstr + " theta",                   100,     0,  3.15 ) );
	h_dv_trk_pt           .push_back( book( name, hDVtrk + "_pt",           hDVtrkstr + " p_{T} [GeV]",             100,     0,   100 ) );
	h_dv_trk_eta          .push_back( book( name, hDVtrk + "_eta",          hDVtrkstr + " eta",                     100,    -3,     3 ) );
	h_dv_trk_phi          .push_back( book( name, hDVtrk + "_phi",          hDVtrkstr + " phi",                     100,  -3.5,   3.5 ) );
	h_dv_trk_d0           .push_back( book( name, hDVtrk + "_d0",           hDVtrkstr + " d0 [mm]",                 100,  -300,   300 ) );
	h_dv_trk_d0_xs        .push_back( book( name, hDVtrk + "_d0_xs",        hDVtrkstr + " d0 [mm]",                 100,    -5,     5 ) );
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
	h_dv_seltrk_d0        .push_back( book( name, hDVseltrk + "_d0",        hDVseltrkstr + " d0 [mm]",              100,  -300,   300 ) );
	h_dv_seltrk_d0_xs     .push_back( book( name, hDVseltrk + "_d0_xs",     hDVseltrkstr + " d0 [mm]",              100,    -5,     5 ) );
      }
      
      // sum, min, max vertex track errors
      std::string hDVsum    = hdv    + "_sum";
      std::string hDVsumstr = hdvstr + " sum track";
      std::string hDVmin    = hdv    + "_min";
      std::string hDVminstr = hdvstr + " min track";
      std::string hDVmax    = hdv    + "_max";
      std::string hDVmaxstr = hdvstr + " max track";
      h_dv_sumd0             .push_back( book( name, hDVsum + "d0",           hDVsumstr + " |d0| [mm]",               100, 0,  500 ) );
      h_dv_sumz0             .push_back( book( name, hDVsum + "z0",           hDVsumstr + " |z0| [mm]",               100, 0, 2000 ) );
      h_dv_sumP              .push_back( book( name, hDVsum + "P",            hDVsumstr + " |q/p| [e/GeV]",           100, 0,    5 ) );
      h_dv_sumd0_sv          .push_back( book( name, hDVsum + "d0_sv",        hDVsumstr + " |d0| wrt SV [mm]",        100, 0,   50 ) );
      h_dv_sumz0_sv          .push_back( book( name, hDVsum + "z0_sv",        hDVsumstr + " |z0| wrt SV [mm]",        100, 0,  150 ) );
      h_dv_sumP_sv           .push_back( book( name, hDVsum + "P_sv",         hDVsumstr + " |q/p| wrt SV [e/GeV]",    100, 0,    5 ) );
      h_dv_sumsqrtd0         .push_back( book( name, hDVsum + "sqrtd0",       hDVsumstr + " sqrt |d0| [mm]",          100, 0, 22.5 ) );
      h_dv_sumsqrtz0         .push_back( book( name, hDVsum + "sqrtz0",       hDVsumstr + " sqrt |z0| [mm]",          100, 0,   45 ) );
      h_dv_sumsqrtP          .push_back( book( name, hDVsum + "sqrtP",        hDVsumstr + " sqrt |q/p| [e/GeV]",      100, 0, 2.25 ) );
      h_dv_sumsqrtd0_sv      .push_back( book( name, hDVsum + "sqrtd0_sv",    hDVsumstr + " sqrt |d0| wrt SV [mm]",   100, 0,    7 ) );
      h_dv_sumsqrtz0_sv      .push_back( book( name, hDVsum + "sqrtz0_sv",    hDVsumstr + " sqrt |z0| wrt SV [mm]",   100, 0,12.25 ) );
      h_dv_sumsqrtP_sv       .push_back( book( name, hDVsum + "sqrtP_sv",     hDVsumstr + " sqrt |q/p| wrt SV [e/GeV]",100,0, 2.25 ) );
      h_dv_mind0             .push_back( book( name, hDVmin + "d0",           hDVminstr + " |d0| [mm]",               100, 0,  200 ) );
      h_dv_minz0             .push_back( book( name, hDVmin + "z0",           hDVminstr + " |z0| [mm]",               100, 0, 1000 ) );
      h_dv_minP              .push_back( book( name, hDVmin + "P",            hDVminstr + " |q/p| [e/GeV]",           100, 0,    1 ) );
      h_dv_mind0_sv          .push_back( book( name, hDVmin + "d0_sv",        hDVminstr + " |d0| wrt SV [mm]",        100, 0,   15 ) );
      h_dv_minz0_sv          .push_back( book( name, hDVmin + "z0_sv",        hDVminstr + " |z0| wrt SV [mm]",        100, 0,   50 ) );
      h_dv_minP_sv           .push_back( book( name, hDVmin + "P_sv",         hDVminstr + " |q/p| wrt SV [e/GeV]",    100, 0,    1 ) );
      h_dv_minsqrtd0         .push_back( book( name, hDVmin + "sqrtd0",       hDVminstr + " sqrt |d0| [mm]",          100, 0,   14 ) );
      h_dv_minsqrtz0         .push_back( book( name, hDVmin + "sqrtz0",       hDVminstr + " sqrt |z0| [mm]",          100, 0,   32 ) );
      h_dv_minsqrtP          .push_back( book( name, hDVmin + "sqrtP",        hDVminstr + " sqrt |q/p| [e/GeV]",      100, 0,    1 ) );
      h_dv_minsqrtd0_sv      .push_back( book( name, hDVmin + "sqrtd0_sv",    hDVminstr + " sqrt |d0| wrt SV [mm]",   100, 0,    4 ) );
      h_dv_minsqrtz0_sv      .push_back( book( name, hDVmin + "sqrtz0_sv",    hDVminstr + " sqrt |z0| wrt SV [mm]",   100, 0,    7 ) );
      h_dv_minsqrtP_sv       .push_back( book( name, hDVmin + "sqrtP_sv",     hDVminstr + " sqrt |q/p| wrt SV [e/GeV]",100,0,    1 ) );
      h_dv_maxd0             .push_back( book( name, hDVmax + "d0",           hDVmaxstr + " |d0| [mm]",               100, 0,  300 ) );
      h_dv_maxz0             .push_back( book( name, hDVmax + "z0",           hDVmaxstr + " |z0| [mm]",               100, 0, 1500 ) );
      h_dv_maxP              .push_back( book( name, hDVmax + "P",            hDVmaxstr + " |q/p| [e/GeV]",           100, 0,  1.1 ) );
      h_dv_maxd0_sv          .push_back( book( name, hDVmax + "d0_sv",        hDVmaxstr + " |d0| wrt SV [mm]",        100, 0,   30 ) );
      h_dv_maxz0_sv          .push_back( book( name, hDVmax + "z0_sv",        hDVmaxstr + " |z0| wrt SV [mm]",        100, 0,  100 ) );
      h_dv_maxP_sv           .push_back( book( name, hDVmax + "P_sv",         hDVmaxstr + " |q/p| wrt SV [e/GeV]",    100, 0,  1.1 ) );
      h_dv_maxsqrtd0         .push_back( book( name, hDVmax + "sqrtd0",       hDVmaxstr + " sqrt |d0| [mm]",          100, 0, 17.5 ) );
      h_dv_maxsqrtz0         .push_back( book( name, hDVmax + "sqrtz0",       hDVmaxstr + " sqrt |z0| [mm]",          100, 0,   40 ) );
      h_dv_maxsqrtP          .push_back( book( name, hDVmax + "sqrtP",        hDVmaxstr + " sqrt |q/p| [e/GeV]",      100, 0,    1 ) );
      h_dv_maxsqrtd0_sv      .push_back( book( name, hDVmax + "sqrtd0_sv",    hDVmaxstr + " sqrt |d0| wrt SV [mm]",   100, 0,  5.5 ) );
      h_dv_maxsqrtz0_sv      .push_back( book( name, hDVmax + "sqrtz0_sv",    hDVmaxstr + " sqrt |z0| wrt SV [mm]",   100, 0,   10 ) );
      h_dv_maxsqrtP_sv       .push_back( book( name, hDVmax + "sqrtP_sv",     hDVmaxstr + " sqrt |q/p| wrt SV [e/GeV]",100,0,    1 ) );
      if ( m_histoInfoSwitch->m_vtxErrors ) {
	// --> sum
	h_dv_sumErrd0        .push_back( book( name, hDVsum + "Errd0",        hDVsumstr + " d0 uncert.",              100, 0,    5 ) );
	h_dv_sumErrz0        .push_back( book( name, hDVsum + "Errz0",        hDVsumstr + " z0 uncert.",              100, 0,   25 ) );
	h_dv_sumErrP         .push_back( book( name, hDVsum + "ErrP",         hDVsumstr + " q/p uncert.",             100, 0,  0.1 ) );
	h_dv_sumSqrterrd0    .push_back( book( name, hDVsum + "Sqrterrd0",    hDVsumstr + " d0 sqrt-uncert.",         100, 0,  2.5 ) );
	h_dv_sumSqrterrz0    .push_back( book( name, hDVsum + "Sqrterrz0",    hDVsumstr + " z0 sqrt-uncert.",         100, 0,    5 ) );
	h_dv_sumSqrterrP     .push_back( book( name, hDVsum + "SqrterrP",     hDVsumstr + " q/p sqrt-uncert.",        100, 0,  0.3 ) );
	h_dv_sumFracerrd0    .push_back( book( name, hDVsum + "Fracerrd0",    hDVsumstr + " d0 fractional uncert.",   100, 0,    1 ) );
	h_dv_sumFracerrz0    .push_back( book( name, hDVsum + "Fracerrz0",    hDVsumstr + " z0 fractional uncert.",   100, 0,    1 ) );
	h_dv_sumFracerrP     .push_back( book( name, hDVsum + "FracerrP",     hDVsumstr + " q/p fractional uncert.",  100, 0, 0.25 ) );
	h_dv_sumSignifd0     .push_back( book( name, hDVsum + "Signifd0",     hDVsumstr + " d0 significance",         100, 0, 1000 ) );
	h_dv_sumSignifz0     .push_back( book( name, hDVsum + "Signifz0",     hDVsumstr + " z0 significance",         100, 0, 1000 ) );
	h_dv_sumSignifP      .push_back( book( name, hDVsum + "SignifP",      hDVsumstr + " q/p significance",        100, 0,  250 ) );
	h_dv_sumErrd0_sv     .push_back( book( name, hDVsum + "Errd0_sv",     hDVsumstr + " d0 wrt SV uncert.",       100, 0,    5 ) );
	h_dv_sumErrz0_sv     .push_back( book( name, hDVsum + "Errz0_sv",     hDVsumstr + " z0 wrt SV uncert.",       100, 0,   25 ) );
	h_dv_sumErrP_sv      .push_back( book( name, hDVsum + "ErrP_sv",      hDVsumstr + " q/p wrt SV uncert.",      100, 0,  0.1 ) );
	h_dv_sumSqrterrd0_sv .push_back( book( name, hDVsum + "Sqrterrd0_sv", hDVsumstr + " d0 wrt SV sqrt-uncert.",  100, 0,  2.5 ) );
	h_dv_sumSqrterrz0_sv .push_back( book( name, hDVsum + "Sqrterrz0_sv", hDVsumstr + " z0 wrt SV sqrt-uncert.",  100, 0,    5 ) );
	h_dv_sumSqrterrP_sv  .push_back( book( name, hDVsum + "SqrterrP_sv",  hDVsumstr + " q/p wrt SV sqrt-uncert.", 100, 0,  0.3 ) );
	h_dv_sumFracerrd0_sv .push_back( book( name, hDVsum + "Fracerrd0_sv", hDVsumstr + " d0 wrt SV fractional uncert.",  100, 0,  150 ) );
	h_dv_sumFracerrz0_sv .push_back( book( name, hDVsum + "Fracerrz0_sv", hDVsumstr + " z0 wrt SV fractional uncert.",  100, 0,  150 ) );
	h_dv_sumFracerrP_sv  .push_back( book( name, hDVsum + "FracerrP_sv",  hDVsumstr + " q/p wrt SV fractional uncert.", 100, 0, 0.25 ) );
	h_dv_sumSignifd0_sv  .push_back( book( name, hDVsum + "Signifd0_sv",  hDVsumstr + " d0 wrt SV significance",  100, 0,   75 ) );
	h_dv_sumSignifz0_sv  .push_back( book( name, hDVsum + "Signifz0_sv",  hDVsumstr + " z0 wrt SV significance",  100, 0,   75 ) );
	h_dv_sumSignifP_sv   .push_back( book( name, hDVsum + "SignifP_sv",   hDVsumstr + " q/p wrt SV significance", 100, 0,  250 ) );
	// --> min
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
	// --> max
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
      }

      // 2d vertex / track histos
      if ( m_histoInfoSwitch->m_vtx2D ) {
	h_dv_z_r                    .push_back( book( name, hdv + "_z_r",             hdvstr + " r-pos [mm]",      100,     0,  400,
						      hdvstr + " z-pos [mm]",           100,  -800,  800 ) );
	h_dv_mass_r                 .push_back( book( name, hdv + "_mass_r",          hdvstr + " r-pos [mm]",      100,     0,  400,
						      hdvstr + " mass [GeV]",           100,     0,   50 ) );
	h_dv_z_chi2                 .push_back( book( name, hdv + "_z_chi2",          hdvstr + " chi2 / nDoF",     100,     0,   10,
						      hdvstr + " z-pos [mm]",           100,  -800,  800 ) );
	h_dv_r_chi2                 .push_back( book( name, hdv + "_r_chi2",          hdvstr + " chi2 / nDoF",     100,     0,   10,
						      hdvstr + " r-pos [mm]",           100,     0,  400 ) );
	h_dv_mass_chi2              .push_back( book( name, hdv + "_mass_chi2",       hdvstr + " chi2 / nDoF",     100,     0,   10,
						      hdvstr + " mass [GeV]",           100,     0,   50 ) );
	h_dv_z_r_s                  .push_back( book( name, hdv + "_z_r_s",           hdvstr + " r-pos [mm]",      100,     0,  300,
						      hdvstr + " z-pos [mm]",           100,  -300,  300 ) );
	h_dv_mass_r_s               .push_back( book( name, hdv + "_mass_r_s",        hdvstr + " r-pos [mm]",      100,     0,  300,
						      hdvstr + " mass [GeV]",           100,     0,   25 ) );
	h_dv_z_chi2_s               .push_back( book( name, hdv + "_z_chi2_s",        hdvstr + " chi2 / nDoF",     100,     0,    5,
						      hdvstr + " z-pos [mm]",           100,  -300,  300 ) );
	h_dv_r_chi2_s               .push_back( book( name, hdv + "_r_chi2_s",        hdvstr + " chi2 / nDoF",     100,     0,    5,
						      hdvstr + " r-pos [mm]",           100,     0,  300 ) );
	h_dv_mass_chi2_s            .push_back( book( name, hdv + "_mass_chi2_s",     hdvstr + " chi2 / nDoF",     100,     0,    5,
						      hdvstr + " mass [GeV]",           100,     0,   25 ) );
      }
      if ( m_histoInfoSwitch->m_vtx2D && m_histoInfoSwitch->m_vtxErrors ) {
	h_dv_errx_x                 .push_back( book( name, hdv + "_errx_x",          hdvstr + " x-pos [mm]",      100,  -400,  400,
						      hdvstr + " x-pos uncert.",        100,     0,   25 ) );
	h_dv_erry_y                 .push_back( book( name, hdv + "_errr_y",          hdvstr + " y-pos [mm]",      100,  -400,  400,
						      hdvstr + " y-pos uncert.",        100,     0,   25 ) );
	h_dv_errz_z                 .push_back( book( name, hdv + "_errz_z",          hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hdvstr + " z-pos uncert.",        100,     0,   25 ) );
	h_dv_errr_r                 .push_back( book( name, hdv + "_errr_r",          hdvstr + " r-pos [mm]",      100,     0,  400,
						      hdvstr + " r-pos uncert.",        100,     0,   25 ) );
	h_dv_errphi_phi             .push_back( book( name, hdv + "_errphi_phi",      hdvstr + " phi-pos [mm]",    100,  -3.5,  3.5,
						      hdvstr + " phi-pos uncert.",      100,     0, 0.15 ) );
	h_dv_sqrterrx_x             .push_back( book( name, hdv + "_sqrterrx_x",      hdvstr + " x-pos [mm]",      100,  -400,  400,
						      hdvstr + " x-pos sqrt-uncert.",   100,     0,    5 ) );
	h_dv_sqrterry_y             .push_back( book( name, hdv + "_sqrterry_y",      hdvstr + " y-pos [mm]",      100,  -400,  400,
						      hdvstr + " y-pos sqrt-uncert.",   100,     0,    5 ) );
	h_dv_sqrterrz_z             .push_back( book( name, hdv + "_sqrterrz_z",      hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hdvstr + " z-pos sqrt-uncert.",   100,     0,    5 ) );
	h_dv_sqrterrr_r             .push_back( book( name, hdv + "_sqrterrr_r",      hdvstr + " r-pos [mm]",      100,     0,  400,
						      hdvstr + " r-pos sqrt-uncert.",   100,     0,    5 ) );
	h_dv_sqrterrphi_phi         .push_back( book( name, hdv + "_sqrterrphi_phi",  hdvstr + " phi-pos [mm]",    100,  -3.5,  3.5,
						      hdvstr + " phi-pos sqrt-uncert.", 100,     0,  0.4 ) );
	h_dv_sumErrd0_r             .push_back( book( name, hDVsum + "Errd0_r",             hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVsumstr + " d0 uncert.",              100,     0,    5 ) );
	h_dv_sumErrz0_z             .push_back( book( name, hDVsum + "Errz0_z",             hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVsumstr + " z0 uncert.",              100,     0,   25 ) );
	h_dv_sumErrP_pt             .push_back( book( name, hDVsum + "ErrP_pt",             hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVsumstr + " q/p uncert.",             100,     0,  0.1 ) );
	h_dv_sumSqrterrd0_r         .push_back( book( name, hDVsum + "Sqrterrd0_r",         hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVsumstr + " d0 sqrt-uncert.",         100,     0,  2.5 ) );
	h_dv_sumSqrterrz0_z         .push_back( book( name, hDVsum + "Sqrterrz0_z",         hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVsumstr + " z0 sqrt-uncert.",         100,     0,    5 ) );
	h_dv_sumSqrterrP_pt         .push_back( book( name, hDVsum + "SqrterrP_pt",         hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVsumstr + " q/p sqrt-uncert.",        100,     0,  0.3 ) );
	h_dv_sumErrd0sv_r           .push_back( book( name, hDVsum + "Errd0sv_r",           hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVsumstr + " d0 wrt SV uncert.",       100,     0,    5 ) );
	h_dv_sumErrz0sv_z           .push_back( book( name, hDVsum + "Errz0sv_z",           hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVsumstr + " z0 wrt SV uncert.",       100,     0,   25 ) );
	h_dv_sumErrPsv_pt           .push_back( book( name, hDVsum + "ErrPsv_pt",           hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVsumstr + " q/p wrt SV uncert.",      100,     0,  0.1 ) );
	h_dv_sumSqrterrd0sv_r       .push_back( book( name, hDVsum + "Sqrterrd0sv_r",       hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVsumstr + " d0 wrt SV sqrt-uncert.",  100,     0,  2.5 ) );
	h_dv_sumSqrterrz0sv_z       .push_back( book( name, hDVsum + "Sqrterrz0sv_z",       hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVsumstr + " z0 wrt SV sqrt-uncert.",  100,     0,    5 ) );
	h_dv_sumSqrterrPsv_pt       .push_back( book( name, hDVsum + "SqrterrPsv_pt",       hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVsumstr + " q/p wrt SV sqrt-uncert.", 100,     0,  0.3 ) );
	h_dv_minErrd0_r             .push_back( book( name, hDVmin + "Errd0_r",             hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVminstr + " d0 uncert.",              100,     0,    2 ) );
	h_dv_minErrz0_z             .push_back( book( name, hDVmin + "Errz0_z",             hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVminstr + " z0 uncert.",              100,     0,   10 ) );
	h_dv_minErrP_pt             .push_back( book( name, hDVmin + "ErrP_pt",             hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVminstr + " q/p uncert.",             100,     0, 0.02 ) );
	h_dv_minSqrterrd0_r         .push_back( book( name, hDVmin + "Sqrterrd0_r",         hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVminstr + " d0 sqrt-uncert.",         100,     0,  1.5 ) );
	h_dv_minSqrterrz0_z         .push_back( book( name, hDVmin + "Sqrterrz0_z",         hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVminstr + " z0 sqrt-uncert.",         100,     0,  3.5 ) );
	h_dv_minSqrterrP_pt         .push_back( book( name, hDVmin + "SqrterrP_pt",         hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVminstr + " q/p sqrt-uncert.",        100,     0, 0.15 ) );
	h_dv_minErrd0sv_r           .push_back( book( name, hDVmin + "Errd0sv_r",           hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVminstr + " d0 wrt SV uncert.",       100,     0,    2 ) );
	h_dv_minErrz0sv_z           .push_back( book( name, hDVmin + "Errz0sv_z",           hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVminstr + " z0 wrt SV uncert.",       100,     0,   10 ) );
	h_dv_minErrPsv_pt           .push_back( book( name, hDVmin + "ErrPsv_pt",           hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVminstr + " q/p wrt SV uncert.",      100,     0, 0.02 ) );
	h_dv_minSqrterrd0sv_r       .push_back( book( name, hDVmin + "Sqrterrd0sv_r",       hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVminstr + " d0 wrt SV sqrt-uncert.",  100,     0,  1.5 ) );
	h_dv_minSqrterrz0sv_z       .push_back( book( name, hDVmin + "Sqrterrz0sv_z",       hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVminstr + " z0 wrt SV sqrt-uncert.",  100,     0,  3.5 ) );
	h_dv_minSqrterrPsv_pt       .push_back( book( name, hDVmin + "SqrterrPsv_pt",       hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVminstr + " q/p wrt SV sqrt-uncert.", 100,     0, 0.15 ) );
	h_dv_maxErrd0_r             .push_back( book( name, hDVmax + "Errd0_r",             hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVmaxstr + " d0 uncert.",              100,     0,    3 ) );
	h_dv_maxErrz0_z             .push_back( book( name, hDVmax + "Errz0_z",             hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVmaxstr + " z0 uncert.",              100,     0,   15 ) );
	h_dv_maxErrP_pt             .push_back( book( name, hDVmax + "ErrP_pt",             hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVmaxstr + " q/p uncert.",             100,     0, 0.05 ) );
	h_dv_maxSqrterrd0_r         .push_back( book( name, hDVmax + "Sqrterrd0_r",         hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVmaxstr + " d0 sqrt-uncert.",         100,     0,    2 ) );
	h_dv_maxSqrterrz0_z         .push_back( book( name, hDVmax + "Sqrterrz0_z",         hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVmaxstr + " z0 sqrt-uncert.",         100,     0,    4 ) );
	h_dv_maxSqrterrP_pt         .push_back( book( name, hDVmax + "SqrterrP_pt",         hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVmaxstr + " q/p sqrt-uncert.",        100,     0, 0.25 ) );
	h_dv_maxErrd0sv_r           .push_back( book( name, hDVmax + "Errd0sv_r",           hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVmaxstr + " d0 wrt SV uncert.",       100,     0,    3 ) );
	h_dv_maxErrz0sv_z           .push_back( book( name, hDVmax + "Errz0sv_z",           hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVmaxstr + " z0 wrt SV uncert.",       100,     0,   15 ) );
	h_dv_maxErrPsv_pt           .push_back( book( name, hDVmax + "ErrPsv_pt",           hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVmaxstr + " q/p wrt SV uncert.",      100,     0, 0.05 ) );
	h_dv_maxSqrterrd0sv_r       .push_back( book( name, hDVmax + "Sqrterrd0sv_r",       hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVmaxstr + " d0 wrt SV sqrt-uncert.",  100,     0,    2 ) );
	h_dv_maxSqrterrz0sv_z       .push_back( book( name, hDVmax + "Sqrterrz0sv_z",       hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVmaxstr + " z0 wrt SV sqrt-uncert.",  100,     0,    4 ) );
	h_dv_maxSqrterrPsv_pt       .push_back( book( name, hDVmax + "SqrterrPsv_pt",       hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVmaxstr + " q/p wrt SV sqrt-uncert.", 100,     0, 0.25 ) );
      }
      if ( m_histoInfoSwitch->m_vtx2D && m_histoInfoSwitch->m_vtxTrks ) {
	h_dv_trkd0_r                .push_back( book( name, hDVtrk + "d0_r",                hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVtrkstr + " d0 [mm]",                 100,  -300,  300 ) );
	h_dv_trkz0_z                .push_back( book( name, hDVtrk + "z0_z",                hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVtrkstr + " z0 [mm]",                 100, -1500, 1500 ) );
	h_dv_trkP_pt                .push_back( book( name, hDVtrk + "P_pt",                hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVtrkstr + " q/p [e/GeV]",             100,  -1.1,  1.1 ) );
	h_dv_trkErrd0_r             .push_back( book( name, hDVtrk + "Errd0_r",             hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVtrkstr + " d0 uncert.",              100,     0,    5 ) );
	h_dv_trkErrz0_z             .push_back( book( name, hDVtrk + "Errz0_z",             hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVtrkstr + " z0 uncert.",              100,     0,   25 ) );
	h_dv_trkErrP_pt             .push_back( book( name, hDVtrk + "ErrP_pt",             hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVtrkstr + " q/p uncert.",             100,     0, 0.05 ) );
	h_dv_trkSqrterrd0_r         .push_back( book( name, hDVtrk + "Sqrterrd0_r",         hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVtrkstr + " d0 sqrt-uncert.",         100,     0,  2.5 ) );
	h_dv_trkSqrterrz0_z         .push_back( book( name, hDVtrk + "Sqrterrz0_z",         hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVtrkstr + " z0 sqrt-uncert.",         100,     0,    5 ) );
	h_dv_trkSqrterrP_pt         .push_back( book( name, hDVtrk + "SqrterrP_pt",         hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVtrkstr + " q/p sqrt-uncert.",        100,     0, 0.25 ) );
	h_dv_trkd0sv_r              .push_back( book( name, hDVtrk + "d0sv_r",              hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVtrkstr + " d0 wrt SV [mm]",          100,   -60,   60 ) );
	h_dv_trkz0sv_z              .push_back( book( name, hDVtrk + "z0sv_z",              hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVtrkstr + " z0 wrt SV [mm]",          100,  -300,  300 ) );
	h_dv_trkPsv_pt              .push_back( book( name, hDVtrk + "Psv_pt",              hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVtrkstr + " q/P wrt SV [e/GeV]",      100,  -1.1,  1.1 ) );
	h_dv_trkErrd0sv_r           .push_back( book( name, hDVtrk + "Errd0sv_r",           hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVtrkstr + " d0 wrt SV uncert.",       100,     0,    5 ) );
	h_dv_trkErrz0sv_z           .push_back( book( name, hDVtrk + "Errz0sv_z",           hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVtrkstr + " z0 wrt SV uncert.",       100,     0,   25 ) );
	h_dv_trkErrPsv_pt           .push_back( book( name, hDVtrk + "ErrPsv_pt",           hdvstr + " p_{T} [GeV]",     100,     0,  100,
						      hDVtrkstr + " q/p wrt SV uncert.",      100,     0, 0.05 ) );
	h_dv_trkSqrterrd0sv_r       .push_back( book( name, hDVtrk + "Sqrterrd0sv_r",       hdvstr + " r-pos [mm]",      100,     0,  400,
						      hDVtrkstr + " d0 wrt SV sqrt-uncert.",  100,     0,  2.5 ) );
	h_dv_trkSqrterrz0sv_z       .push_back( book( name, hDVtrk + "Sqrterrz0sv_z",       hdvstr + " z-pos [mm]",      100,  -800,  800,
						      hDVtrkstr + " z0 wrt SV sqrt-uncert.",  100,     0,    5 ) );
	h_dv_trkSqrterrPsv_pt       .push_back( book( name, hDVtrk + "SqrterrPsv_pt",       hdvstr + " p_{T} [GeV]",     100,     0,  100,
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
      }
	
      // n-track vertices
      if ( m_numVtxTrks ) {
	std::vector<TH1F*> h_njtrkdv_n;
	std::vector<TH1F*> h_njtrkdv_z;
	std::vector<TH1F*> h_njtrkdv_z_s;
	std::vector<TH1F*> h_njtrkdv_r;
	std::vector<TH1F*> h_njtrkdv_r_s;
	std::vector<TH1F*> h_njtrkdv_mass;
	std::vector<TH1F*> h_njtrkdv_mass_s;
	std::vector<TH1F*> h_njtrkdv_mass_xs;
	std::vector<TH1F*> h_njtrkdv_direction;
	std::vector<TH1F*> h_njtrkdv_minOpAng;
	std::vector<TH1F*> h_njtrkdv_maxOpAng;
	std::vector<TH1F*> h_njtrkdv_chi2;
	std::vector<TH1F*> h_njtrkdv_chi2_s;
	std::vector<TH1F*> h_njtrkdv_sumd0;
	std::vector<TH1F*> h_njtrkdv_sumz0;
	std::vector<TH1F*> h_njtrkdv_sumP;
	std::vector<TH1F*> h_njtrkdv_sumd0_sv;
	std::vector<TH1F*> h_njtrkdv_sumz0_sv;
	std::vector<TH1F*> h_njtrkdv_sumP_sv;
	std::vector<TH1F*> h_njtrkdv_sumsqrtd0;
	std::vector<TH1F*> h_njtrkdv_sumsqrtz0;
	std::vector<TH1F*> h_njtrkdv_sumsqrtP;
	std::vector<TH1F*> h_njtrkdv_sumsqrtd0_sv;
	std::vector<TH1F*> h_njtrkdv_sumsqrtz0_sv;
	std::vector<TH1F*> h_njtrkdv_sumsqrtP_sv;
	std::vector<TH1F*> h_njtrkdv_mind0;
	std::vector<TH1F*> h_njtrkdv_minz0;
	std::vector<TH1F*> h_njtrkdv_minP;
	std::vector<TH1F*> h_njtrkdv_mind0_sv;
	std::vector<TH1F*> h_njtrkdv_minz0_sv;
	std::vector<TH1F*> h_njtrkdv_minP_sv;
	std::vector<TH1F*> h_njtrkdv_minsqrtd0;
	std::vector<TH1F*> h_njtrkdv_minsqrtz0;
	std::vector<TH1F*> h_njtrkdv_minsqrtP;
	std::vector<TH1F*> h_njtrkdv_minsqrtd0_sv;
	std::vector<TH1F*> h_njtrkdv_minsqrtz0_sv;
	std::vector<TH1F*> h_njtrkdv_minsqrtP_sv;
	std::vector<TH1F*> h_njtrkdv_maxd0;
	std::vector<TH1F*> h_njtrkdv_maxz0;
	std::vector<TH1F*> h_njtrkdv_maxP;
	std::vector<TH1F*> h_njtrkdv_maxd0_sv;
	std::vector<TH1F*> h_njtrkdv_maxz0_sv;
	std::vector<TH1F*> h_njtrkdv_maxP_sv;
	std::vector<TH1F*> h_njtrkdv_maxsqrtd0;
	std::vector<TH1F*> h_njtrkdv_maxsqrtz0;
	std::vector<TH1F*> h_njtrkdv_maxsqrtP;
	std::vector<TH1F*> h_njtrkdv_maxsqrtd0_sv;
	std::vector<TH1F*> h_njtrkdv_maxsqrtz0_sv;
	std::vector<TH1F*> h_njtrkdv_maxsqrtP_sv;
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
	  std::string ntrk      = std::to_string(j+1);
	  std::string iDV       = hdv; iDV[0] = std::toupper(iDV[0]);
	  std::string ntrkDV    = ntrk + "trk" + iDV;
	  std::string ntrkDVstr = ntrk + "-track " + hdvstr;
	  if ( j+1 == m_numVtxTrks ) ntrkDVstr = ntrk + "-plus-track " + hdvstr;
	  std::string ntrkDVsum    = ntrkDV    + "_sum";
	  std::string ntrkDVsumstr = ntrkDVstr + " sum track";
	  std::string ntrkDVmin    = ntrkDV    + "_min";
	  std::string ntrkDVminstr = ntrkDVstr + " min track";
	  std::string ntrkDVmax    = ntrkDV    + "_max";
	  std::string ntrkDVmaxstr = ntrkDVstr + " max track";
	  h_njtrkdv_n                 .push_back( book( name, ntrkDV    + "_n",           "n " + ntrkDVstr + "s",                    15, 0,   15 ) );
	  h_njtrkdv_z                 .push_back( book( name, ntrkDV    + "_z",           ntrkDVstr    + " z-pos [mm]",            100,-800, 800 ) );
	  h_njtrkdv_z_s               .push_back( book( name, ntrkDV    + "_z_s",         ntrkDVstr    + " z-pos [mm]",            100,-300, 300 ) );
	  h_njtrkdv_r                 .push_back( book( name, ntrkDV    + "_r",           ntrkDVstr    + " r-pos [mm]",             100, 0,  400 ) );
	  h_njtrkdv_r_s               .push_back( book( name, ntrkDV    + "_r_s",         ntrkDVstr    + " r-pos [mm]",             100, 0,  300 ) );
	  h_njtrkdv_mass              .push_back( book( name, ntrkDV    + "_mass",        ntrkDVstr    + " mass [GeV]",             100, 0,   50 ) );
	  h_njtrkdv_mass_s            .push_back( book( name, ntrkDV    + "_mass_s",      ntrkDVstr    + " mass [GeV]",             100, 0,   25 ) );
	  h_njtrkdv_mass_xs           .push_back( book( name, ntrkDV    + "_mass_xs",     ntrkDVstr    + " mass [GeV]",             100, 0,    5 ) );
	  h_njtrkdv_direction         .push_back( book( name, ntrkDV    + "_direction",   ntrkDVstr    + " direction",             100,-1.1, 1.1 ) );
	  h_njtrkdv_minOpAng          .push_back( book( name, ntrkDV    + "_minOpAng",    ntrkDVstr    + " cos min opening angle", 100,-1.1, 1.1 ) );
	  h_njtrkdv_maxOpAng          .push_back( book( name, ntrkDV    + "_maxOpAng",    ntrkDVstr    + " mos max opening angle", 100,-1.1, 1.1 ) );
	  h_njtrkdv_chi2              .push_back( book( name, ntrkDV    + "_chi2",        ntrkDVstr    + " chi2 / ndof",            100, 0,   10 ) );
	  h_njtrkdv_chi2_s            .push_back( book( name, ntrkDV    + "_chi2_s",      ntrkDVstr    + " chi2 / ndof",            100, 0,    5 ) );
	  h_njtrkdv_sumd0             .push_back( book( name, ntrkDVsum + "d0",           ntrkDVsumstr + " |d0| [mm]",              100, 0,  500 ) );
	  h_njtrkdv_sumz0             .push_back( book( name, ntrkDVsum + "z0",           ntrkDVsumstr + " |z0| [mm]",              100, 0, 2000 ) );
	  h_njtrkdv_sumP              .push_back( book( name, ntrkDVsum + "P",            ntrkDVsumstr + " |q/p| [e/GeV]",          100, 0,    5 ) );
	  h_njtrkdv_sumd0_sv          .push_back( book( name, ntrkDVsum + "d0_sv",        ntrkDVsumstr + " |d0| wrt SV [mm]",       100, 0,   50 ) );
	  h_njtrkdv_sumz0_sv          .push_back( book( name, ntrkDVsum + "z0_sv",        ntrkDVsumstr + " |z0| wrt SV [mm]",       100, 0,  150 ) );
	  h_njtrkdv_sumP_sv           .push_back( book( name, ntrkDVsum + "P_sv",         ntrkDVsumstr + " |q/p| wrt SV [e/GeV]",   100, 0,    5 ) );
	  h_njtrkdv_sumsqrtd0         .push_back( book( name, ntrkDVsum + "sqrtd0",       ntrkDVsumstr + " sqrt |d0| [mm]",         100, 0, 22.5 ) );
	  h_njtrkdv_sumsqrtz0         .push_back( book( name, ntrkDVsum + "sqrtz0",       ntrkDVsumstr + " sqrt |z0| [mm]",         100, 0,   45 ) );
	  h_njtrkdv_sumsqrtP          .push_back( book( name, ntrkDVsum + "sqrtP",        ntrkDVsumstr + " sqrt |q/p| [e/GeV]",     100, 0, 2.25 ) );
	  h_njtrkdv_sumsqrtd0_sv      .push_back( book( name, ntrkDVsum + "sqrtd0_sv",    ntrkDVsumstr + " sqrt |d0| wrt SV [mm]",  100, 0,    7 ) );
	  h_njtrkdv_sumsqrtz0_sv      .push_back( book( name, ntrkDVsum + "sqrtz0_sv",    ntrkDVsumstr + " sqrt |z0| wrt SV [mm]",  100, 0,12.25 ) );
	  h_njtrkdv_sumsqrtP_sv       .push_back( book( name, ntrkDVsum + "sqrtP_sv",     ntrkDVsumstr + " sqrt |q/p| wrt SV [e/GeV]",100,0,2.25 ) );
	  h_njtrkdv_mind0             .push_back( book( name, ntrkDVmin + "d0",           ntrkDVminstr + " |d0| [mm]",              100, 0,  200 ) );
	  h_njtrkdv_minz0             .push_back( book( name, ntrkDVmin + "z0",           ntrkDVminstr + " |z0| [mm]",              100, 0, 1000 ) );
	  h_njtrkdv_minP              .push_back( book( name, ntrkDVmin + "P",            ntrkDVminstr + " |q/p| [e/GeV]",          100, 0,    1 ) );
	  h_njtrkdv_mind0_sv          .push_back( book( name, ntrkDVmin + "d0_sv",        ntrkDVminstr + " |d0| wrt SV [mm]",       100, 0,   15 ) );
	  h_njtrkdv_minz0_sv          .push_back( book( name, ntrkDVmin + "z0_sv",        ntrkDVminstr + " |z0| wrt SV [mm]",       100, 0,   50 ) );
	  h_njtrkdv_minP_sv           .push_back( book( name, ntrkDVmin + "P_sv",         ntrkDVminstr + " |q/p| wrt SV [e/GeV]",   100, 0,    1 ) );
	  h_njtrkdv_minsqrtd0         .push_back( book( name, ntrkDVmin + "sqrtd0",       ntrkDVminstr + " sqrt |d0| [mm]",         100, 0,   14 ) );
	  h_njtrkdv_minsqrtz0         .push_back( book( name, ntrkDVmin + "sqrtz0",       ntrkDVminstr + " sqrt |z0| [mm]",         100, 0,   32 ) );
	  h_njtrkdv_minsqrtP          .push_back( book( name, ntrkDVmin + "sqrtP",        ntrkDVminstr + " sqrt |q/p| [e/GeV]",     100, 0,    1 ) );
	  h_njtrkdv_minsqrtd0_sv      .push_back( book( name, ntrkDVmin + "sqrtd0_sv",    ntrkDVminstr + " sqrt |d0| wrt SV [mm]",  100, 0,    4 ) );
	  h_njtrkdv_minsqrtz0_sv      .push_back( book( name, ntrkDVmin + "sqrtz0_sv",    ntrkDVminstr + " sqrt |z0| wrt SV [mm]",  100, 0,    7 ) );
	  h_njtrkdv_minsqrtP_sv       .push_back( book( name, ntrkDVmin + "sqrtP_sv",     ntrkDVminstr + " sqrt |q/p| wrt SV [e/GeV]",100,0,   1 ) );
	  h_njtrkdv_maxd0             .push_back( book( name, ntrkDVmax + "d0",           ntrkDVmaxstr + " |d0| [mm]",              100, 0,  300 ) );
	  h_njtrkdv_maxz0             .push_back( book( name, ntrkDVmax + "z0",           ntrkDVmaxstr + " |z0| [mm]",              100, 0, 1500 ) );
	  h_njtrkdv_maxP              .push_back( book( name, ntrkDVmax + "P",            ntrkDVmaxstr + " |q/p| [e/GeV]",          100, 0,  1.1 ) );
	  h_njtrkdv_maxd0_sv          .push_back( book( name, ntrkDVmax + "d0_sv",        ntrkDVmaxstr + " |d0| wrt SV [mm]",       100, 0,   30 ) );
	  h_njtrkdv_maxz0_sv          .push_back( book( name, ntrkDVmax + "z0_sv",        ntrkDVmaxstr + " |z0| wrt SV [mm]",       100, 0,  100 ) );
	  h_njtrkdv_maxP_sv           .push_back( book( name, ntrkDVmax + "P_sv",         ntrkDVmaxstr + " |q/p| wrt SV [e/GeV]",   100, 0,  1.1 ) );
	  h_njtrkdv_maxsqrtd0         .push_back( book( name, ntrkDVmax + "sqrtd0",       ntrkDVmaxstr + " sqrt |d0| [mm]",         100, 0, 17.5 ) );
	  h_njtrkdv_maxsqrtz0         .push_back( book( name, ntrkDVmax + "sqrtz0",       ntrkDVmaxstr + " sqrt |z0| [mm]",         100, 0,   40 ) );
	  h_njtrkdv_maxsqrtP          .push_back( book( name, ntrkDVmax + "sqrtP",        ntrkDVmaxstr + " sqrt |q/p| [e/GeV]",     100, 0,    1 ) );
	  h_njtrkdv_maxsqrtd0_sv      .push_back( book( name, ntrkDVmax + "sqrtd0_sv",    ntrkDVmaxstr + " sqrt |d0| wrt SV [mm]",  100, 0,  5.5 ) );
	  h_njtrkdv_maxsqrtz0_sv      .push_back( book( name, ntrkDVmax + "sqrtz0_sv",    ntrkDVmaxstr + " sqrt |z0| wrt SV [mm]",  100, 0,   10 ) );
	  h_njtrkdv_maxsqrtP_sv       .push_back( book( name, ntrkDVmax + "sqrtP_sv",     ntrkDVmaxstr + " sqrt |q/p| wrt SV [e/GeV]",100,0,   1 ) );
	  if ( m_histoInfoSwitch->m_vtxErrors ) {
	    h_njtrkdv_sqrterrx        .push_back( book( name, ntrkDV    + "_sqrterrx",    ntrkDVstr    + " x-pos sqrt-uncert.",     100, 0,    5 ) );
	    h_njtrkdv_sqrterry        .push_back( book( name, ntrkDV    + "_sqrterry",    ntrkDVstr    + " y-pos sqrt-uncert.",     100, 0,    5 ) );
	    h_njtrkdv_sqrterrz        .push_back( book( name, ntrkDV    + "_sqrterrz",    ntrkDVstr    + " z-pos sqrt-uncert.",     100, 0,    5 ) );
	    h_njtrkdv_sqrterrr        .push_back( book( name, ntrkDV    + "_sqrterrr",    ntrkDVstr    + " r-pos sqrt-uncert.",     100, 0,    5 ) );
	    h_njtrkdv_sqrterrphi      .push_back( book( name, ntrkDV    + "_sqrterrphi",  ntrkDVstr    + " phi-pos sqrt-uncert.",   100, 0,  0.4 ) );
	    h_njtrkdv_sumSqrterrd0    .push_back( book( name, ntrkDVsum + "Sqrterrd0",    ntrkDVsumstr + " d0 sqrt-uncert.",        100, 0,  2.5 ) );
	    h_njtrkdv_sumSqrterrz0    .push_back( book( name, ntrkDVsum + "Sqrterrz0",    ntrkDVsumstr + " z0 sqrt-uncert.",        100, 0,    5 ) );
	    h_njtrkdv_sumSqrterrP     .push_back( book( name, ntrkDVsum + "SqrterrP",     ntrkDVsumstr + " q/p sqrt-uncert.",       100, 0,  0.3 ) );
	    h_njtrkdv_sumSqrterrd0_sv .push_back( book( name, ntrkDVsum + "Sqrterrd0_sv", ntrkDVsumstr + " d0 wrt SV sqrt-uncert.", 100, 0,  2.5 ) );
	    h_njtrkdv_sumSqrterrz0_sv .push_back( book( name, ntrkDVsum + "Sqrterrz0_sv", ntrkDVsumstr + " z0 wrt SV sqrt-uncert.", 100, 0,    5 ) );
	    h_njtrkdv_sumSqrterrP_sv  .push_back( book( name, ntrkDVsum + "SqrterrP_sv",  ntrkDVsumstr + " q/p wrt SV sqrt-uncert.",100, 0,  0.3 ) );
	    h_njtrkdv_minSqrterrd0    .push_back( book( name, ntrkDVmin + "Sqrterrd0",    ntrkDVminstr + " d0 sqrt-uncert.",        100, 0,  1.5 ) );
	    h_njtrkdv_minSqrterrz0    .push_back( book( name, ntrkDVmin + "Sqrterrz0",    ntrkDVminstr + " z0 sqrt-uncert.",        100, 0,  3.5 ) );
	    h_njtrkdv_minSqrterrP     .push_back( book( name, ntrkDVmin + "SqrterrP",     ntrkDVminstr + " q/p sqrt-uncert.",       100, 0, 0.15 ) );
	    h_njtrkdv_minSqrterrd0_sv .push_back( book( name, ntrkDVmin + "Sqrterrd0_sv", ntrkDVminstr + " d0 wrt SV sqrt-uncert.", 100, 0,  1.5 ) );
	    h_njtrkdv_minSqrterrz0_sv .push_back( book( name, ntrkDVmin + "Sqrterrz0_sv", ntrkDVminstr + " z0 wrt SV sqrt-uncert.", 100, 0,  3.5 ) );
	    h_njtrkdv_minSqrterrP_sv  .push_back( book( name, ntrkDVmin + "SqrterrP_sv",  ntrkDVminstr + " q/p wrt SV sqrt-uncert.",100, 0, 0.15 ) );
	    h_njtrkdv_maxSqrterrd0    .push_back( book( name, ntrkDVmax + "Sqrterrd0",    ntrkDVmaxstr + " d0 sqrt-uncert.",        100, 0,    2 ) );
	    h_njtrkdv_maxSqrterrz0    .push_back( book( name, ntrkDVmax + "Sqrterrz0",    ntrkDVmaxstr + " z0 sqrt-uncert.",        100, 0,    4 ) );
	    h_njtrkdv_maxSqrterrP     .push_back( book( name, ntrkDVmax + "SqrterrP",     ntrkDVmaxstr + " q/p sqrt-uncert.",       100, 0, 0.25 ) );
	    h_njtrkdv_maxSqrterrd0_sv .push_back( book( name, ntrkDVmax + "Sqrterrd0_sv", ntrkDVmaxstr + " d0 wrt SV sqrt-uncert.", 100, 0,    2 ) );
	    h_njtrkdv_maxSqrterrz0_sv .push_back( book( name, ntrkDVmax + "Sqrterrz0_sv", ntrkDVmaxstr + " z0 wrt SV sqrt-uncert.", 100, 0,    4 ) );
	    h_njtrkdv_maxSqrterrP_sv  .push_back( book( name, ntrkDVmax + "SqrterrP_sv",  ntrkDVmaxstr + " q/p wrt SV sqrt-uncert.",100, 0, 0.25 ) );
	  }
	}
	h_ntrkdv_n               .push_back( h_njtrkdv_n               );
	h_ntrkdv_z               .push_back( h_njtrkdv_z               );
	h_ntrkdv_z_s             .push_back( h_njtrkdv_z_s             );
	h_ntrkdv_r               .push_back( h_njtrkdv_r               );
	h_ntrkdv_r_s             .push_back( h_njtrkdv_r_s             );
	h_ntrkdv_mass            .push_back( h_njtrkdv_mass            );
	h_ntrkdv_mass_s          .push_back( h_njtrkdv_mass_s          );
	h_ntrkdv_mass_xs         .push_back( h_njtrkdv_mass_xs         );
	h_ntrkdv_direction       .push_back( h_njtrkdv_direction       );
	h_ntrkdv_minOpAng        .push_back( h_njtrkdv_minOpAng        );
	h_ntrkdv_maxOpAng        .push_back( h_njtrkdv_maxOpAng        );
	h_ntrkdv_chi2            .push_back( h_njtrkdv_chi2            );
	h_ntrkdv_chi2_s          .push_back( h_njtrkdv_chi2_s          );
	h_ntrkdv_sumd0           .push_back( h_njtrkdv_sumd0           );
	h_ntrkdv_sumz0           .push_back( h_njtrkdv_sumz0           );
	h_ntrkdv_sumP            .push_back( h_njtrkdv_sumP            );
	h_ntrkdv_sumd0_sv        .push_back( h_njtrkdv_sumd0_sv        );
	h_ntrkdv_sumz0_sv        .push_back( h_njtrkdv_sumz0_sv        );
	h_ntrkdv_sumP_sv         .push_back( h_njtrkdv_sumP_sv         );
	h_ntrkdv_sumsqrtd0       .push_back( h_njtrkdv_sumsqrtd0       );
	h_ntrkdv_sumsqrtz0       .push_back( h_njtrkdv_sumsqrtz0       );
	h_ntrkdv_sumsqrtP        .push_back( h_njtrkdv_sumsqrtP        );
	h_ntrkdv_sumsqrtd0_sv    .push_back( h_njtrkdv_sumsqrtd0_sv    );
	h_ntrkdv_sumsqrtz0_sv    .push_back( h_njtrkdv_sumsqrtz0_sv    );
	h_ntrkdv_sumsqrtP_sv     .push_back( h_njtrkdv_sumsqrtP_sv     );
	h_ntrkdv_mind0           .push_back( h_njtrkdv_mind0           );
	h_ntrkdv_minz0           .push_back( h_njtrkdv_minz0           );
	h_ntrkdv_minP            .push_back( h_njtrkdv_minP            );
	h_ntrkdv_mind0_sv        .push_back( h_njtrkdv_mind0_sv        );
	h_ntrkdv_minz0_sv        .push_back( h_njtrkdv_minz0_sv        );
	h_ntrkdv_minP_sv         .push_back( h_njtrkdv_minP_sv         );
	h_ntrkdv_minsqrtd0       .push_back( h_njtrkdv_minsqrtd0       );
	h_ntrkdv_minsqrtz0       .push_back( h_njtrkdv_minsqrtz0       );
	h_ntrkdv_minsqrtP        .push_back( h_njtrkdv_minsqrtP        );
	h_ntrkdv_minsqrtd0_sv    .push_back( h_njtrkdv_minsqrtd0_sv    );
	h_ntrkdv_minsqrtz0_sv    .push_back( h_njtrkdv_minsqrtz0_sv    );
	h_ntrkdv_minsqrtP_sv     .push_back( h_njtrkdv_minsqrtP_sv     );
	h_ntrkdv_maxd0           .push_back( h_njtrkdv_maxd0           );
	h_ntrkdv_maxz0           .push_back( h_njtrkdv_maxz0           );
	h_ntrkdv_maxP            .push_back( h_njtrkdv_maxP            );
	h_ntrkdv_maxd0_sv        .push_back( h_njtrkdv_maxd0_sv        );
	h_ntrkdv_maxz0_sv        .push_back( h_njtrkdv_maxz0_sv        );
	h_ntrkdv_maxP_sv         .push_back( h_njtrkdv_maxP_sv         );
	h_ntrkdv_maxsqrtd0       .push_back( h_njtrkdv_maxsqrtd0       );
	h_ntrkdv_maxsqrtz0       .push_back( h_njtrkdv_maxsqrtz0       );
	h_ntrkdv_maxsqrtP        .push_back( h_njtrkdv_maxsqrtP        );
	h_ntrkdv_maxsqrtd0_sv    .push_back( h_njtrkdv_maxsqrtd0_sv    );
	h_ntrkdv_maxsqrtz0_sv    .push_back( h_njtrkdv_maxsqrtz0_sv    );
	h_ntrkdv_maxsqrtP_sv     .push_back( h_njtrkdv_maxsqrtP_sv     );
	if ( m_histoInfoSwitch->m_vtxErrors ) {
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
    }
    h_DV_n                        .push_back( h_dv_n                      );
    h_DV_x                        .push_back( h_dv_x                      );
    h_DV_y                        .push_back( h_dv_y                      );
    h_DV_z                        .push_back( h_dv_z                      );
    h_DV_r                        .push_back( h_dv_r                      );
    h_DV_x_s                      .push_back( h_dv_x_s                    );
    h_DV_y_s                      .push_back( h_dv_y_s                    );
    h_DV_z_s                      .push_back( h_dv_z_s                    );
    h_DV_r_s                      .push_back( h_dv_r_s                    );
    h_DV_phipos                   .push_back( h_dv_phipos                 );
    h_DV_pt                       .push_back( h_dv_pt                     );
    h_DV_pt_s                     .push_back( h_dv_pt_s                   );
    h_DV_pt_xs                    .push_back( h_dv_pt_xs                  );
    h_DV_eta                      .push_back( h_dv_eta                    );
    h_DV_phi                      .push_back( h_dv_phi                    );
    h_DV_mass                     .push_back( h_dv_mass                   );
    h_DV_mass_l                   .push_back( h_dv_mass_l                 );
    h_DV_mass_s                   .push_back( h_dv_mass_s                 );
    h_DV_mass_xs                  .push_back( h_dv_mass_xs                );
    h_DV_massNA                   .push_back( h_dv_massNA                 );
    h_DV_massNA_l                 .push_back( h_dv_massNA_l               );
    h_DV_massNA_s                 .push_back( h_dv_massNA_s               );
    h_DV_massNA_xs                .push_back( h_dv_massNA_xs              );
    h_DV_direction                .push_back( h_dv_direction              );
    h_DV_minOpAng                 .push_back( h_dv_minOpAng               );
    h_DV_maxOpAng                 .push_back( h_dv_maxOpAng               );
    h_DV_chi2                     .push_back( h_dv_chi2                   );
    h_DV_chi2_s                   .push_back( h_dv_chi2_s                 );
    h_DV_ntrk                     .push_back( h_dv_ntrk                   );
    h_DV_ntrk_final               .push_back( h_dv_ntrk_final             );
    h_DV_ntrk_sel                 .push_back( h_dv_ntrk_sel               );
    h_DV_ntrk_assoc               .push_back( h_dv_ntrk_assoc             );
    h_DV_ntrk_lrt                 .push_back( h_dv_ntrk_lrt               );
    h_DV_ntrk_d0                  .push_back( h_dv_ntrk_d0                );
    h_DV_ntrk_seld0               .push_back( h_dv_ntrk_seld0             );
    if ( m_histoInfoSwitch->m_vtxErrors ) {
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
    }
    h_DV_jetDR                    .push_back( h_dv_jetDR                  );
    h_DV_leadJetDR                .push_back( h_dv_leadJetDR              );
    if ( m_histoInfoSwitch->m_vtxTrks ) {
      h_DV_trk_qOverP             .push_back( h_dv_trk_qOverP             );
      h_DV_trk_theta              .push_back( h_dv_trk_theta              );
      h_DV_trk_pt                 .push_back( h_dv_trk_pt                 );
      h_DV_trk_eta                .push_back( h_dv_trk_eta                );
      h_DV_trk_phi                .push_back( h_dv_trk_phi                );
      h_DV_trk_d0                 .push_back( h_dv_trk_d0                 );
      h_DV_trk_d0_xs              .push_back( h_dv_trk_d0_xs              );
      h_DV_trk_z0                 .push_back( h_dv_trk_z0                 );
      h_DV_trk_errd0              .push_back( h_dv_trk_errd0              );
      h_DV_trk_errz0              .push_back( h_dv_trk_errz0              );
      h_DV_trk_sqrterrd0          .push_back( h_dv_trk_sqrterrd0          );
      h_DV_trk_sqrterrz0          .push_back( h_dv_trk_sqrterrz0          );
      h_DV_trk_fracerrd0          .push_back( h_dv_trk_fracerrd0          );
      h_DV_trk_fracerrz0          .push_back( h_dv_trk_fracerrz0          );
      h_DV_trk_signifd0           .push_back( h_dv_trk_signifd0           );
      h_DV_trk_signifz0           .push_back( h_dv_trk_signifz0           );
      h_DV_trk_errP               .push_back( h_dv_trk_errP               );
      h_DV_trk_sqrterrP           .push_back( h_dv_trk_sqrterrP           );
      h_DV_trk_fracerrP           .push_back( h_dv_trk_fracerrP           );
      h_DV_trk_signifP            .push_back( h_dv_trk_signifP            );
      h_DV_trk_chi2               .push_back( h_dv_trk_chi2               );
      h_DV_trk_chiSq              .push_back( h_dv_trk_chiSq              );
      h_DV_trk_qOverP_sv          .push_back( h_dv_trk_qOverP_sv          );
      h_DV_trk_theta_sv           .push_back( h_dv_trk_theta_sv           );
      h_DV_trk_pt_sv              .push_back( h_dv_trk_pt_sv              );
      h_DV_trk_eta_sv             .push_back( h_dv_trk_eta_sv             );
      h_DV_trk_phi_sv             .push_back( h_dv_trk_phi_sv             );
      h_DV_trk_d0_sv              .push_back( h_dv_trk_d0_sv              );
      h_DV_trk_z0_sv              .push_back( h_dv_trk_z0_sv              );
      h_DV_trk_errd0_sv           .push_back( h_dv_trk_errd0_sv           );
      h_DV_trk_errz0_sv           .push_back( h_dv_trk_errz0_sv           );
      h_DV_trk_sqrterrd0_sv       .push_back( h_dv_trk_sqrterrd0_sv       );
      h_DV_trk_sqrterrz0_sv       .push_back( h_dv_trk_sqrterrz0_sv       );
      h_DV_trk_fracerrd0_sv       .push_back( h_dv_trk_fracerrd0_sv       );
      h_DV_trk_fracerrz0_sv       .push_back( h_dv_trk_fracerrz0_sv       );
      h_DV_trk_signifd0_sv        .push_back( h_dv_trk_signifd0_sv        );
      h_DV_trk_signifz0_sv        .push_back( h_dv_trk_signifz0_sv        );
      h_DV_trk_errP_sv            .push_back( h_dv_trk_errP_sv            );
      h_DV_trk_sqrterrP_sv        .push_back( h_dv_trk_sqrterrP_sv        );
      h_DV_trk_fracerrP_sv        .push_back( h_dv_trk_fracerrP_sv        );
      h_DV_trk_signifP_sv         .push_back( h_dv_trk_signifP_sv         );
      h_DV_trk_chi2_sv            .push_back( h_dv_trk_chi2_sv            );
      h_DV_trk_chiSq_sv           .push_back( h_dv_trk_chiSq_sv           );
      h_DV_seltrk_d0              .push_back( h_dv_seltrk_d0              );
      h_DV_seltrk_d0_xs           .push_back( h_dv_seltrk_d0_xs           );
    }
    h_DV_sumd0                    .push_back( h_dv_sumd0                  );
    h_DV_sumz0                    .push_back( h_dv_sumz0                  );
    h_DV_sumP                     .push_back( h_dv_sumP                   );
    h_DV_sumd0_sv                 .push_back( h_dv_sumd0_sv               );
    h_DV_sumz0_sv                 .push_back( h_dv_sumz0_sv               );
    h_DV_sumP_sv                  .push_back( h_dv_sumP_sv                );
    h_DV_sumsqrtd0                .push_back( h_dv_sumsqrtd0              );
    h_DV_sumsqrtz0                .push_back( h_dv_sumsqrtz0              );
    h_DV_sumsqrtP                 .push_back( h_dv_sumsqrtP               );
    h_DV_sumsqrtd0_sv             .push_back( h_dv_sumsqrtd0_sv           );
    h_DV_sumsqrtz0_sv             .push_back( h_dv_sumsqrtz0_sv           );
    h_DV_sumsqrtP_sv              .push_back( h_dv_sumsqrtP_sv            );
    h_DV_mind0                    .push_back( h_dv_mind0                  );
    h_DV_minz0                    .push_back( h_dv_minz0                  );
    h_DV_minP                     .push_back( h_dv_minP                   );
    h_DV_mind0_sv                 .push_back( h_dv_mind0_sv               );
    h_DV_minz0_sv                 .push_back( h_dv_minz0_sv               );
    h_DV_minP_sv                  .push_back( h_dv_minP_sv                );
    h_DV_minsqrtd0                .push_back( h_dv_minsqrtd0              );
    h_DV_minsqrtz0                .push_back( h_dv_minsqrtz0              );
    h_DV_minsqrtP                 .push_back( h_dv_minsqrtP               );
    h_DV_minsqrtd0_sv             .push_back( h_dv_minsqrtd0_sv           );
    h_DV_minsqrtz0_sv             .push_back( h_dv_minsqrtz0_sv           );
    h_DV_minsqrtP_sv              .push_back( h_dv_minsqrtP_sv            );
    h_DV_maxd0                    .push_back( h_dv_maxd0                  );
    h_DV_maxz0                    .push_back( h_dv_maxz0                  );
    h_DV_maxP                     .push_back( h_dv_maxP                   );
    h_DV_maxd0_sv                 .push_back( h_dv_maxd0_sv               );
    h_DV_maxz0_sv                 .push_back( h_dv_maxz0_sv               );
    h_DV_maxP_sv                  .push_back( h_dv_maxP_sv                );
    h_DV_maxsqrtd0                .push_back( h_dv_maxsqrtd0              );
    h_DV_maxsqrtz0                .push_back( h_dv_maxsqrtz0              );
    h_DV_maxsqrtP                 .push_back( h_dv_maxsqrtP               );
    h_DV_maxsqrtd0_sv             .push_back( h_dv_maxsqrtd0_sv           );
    h_DV_maxsqrtz0_sv             .push_back( h_dv_maxsqrtz0_sv           );
    h_DV_maxsqrtP_sv              .push_back( h_dv_maxsqrtP_sv            );
    if ( m_histoInfoSwitch->m_vtxErrors ) {
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
    }
    if ( m_histoInfoSwitch->m_vtx2D ) {
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
    }
    if ( m_histoInfoSwitch->m_vtx2D && m_histoInfoSwitch->m_vtxErrors ) {
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
    }
    if ( m_histoInfoSwitch->m_vtx2D && m_histoInfoSwitch->m_vtxTrks ) {
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
    }
    if ( m_numVtxTrks ) {
      h_ntrkDV_n                  .push_back( h_ntrkdv_n                  );
      h_ntrkDV_z                  .push_back( h_ntrkdv_z                  );
      h_ntrkDV_z_s                .push_back( h_ntrkdv_z_s                );
      h_ntrkDV_r                  .push_back( h_ntrkdv_r                  );
      h_ntrkDV_r_s                .push_back( h_ntrkdv_r_s                );
      h_ntrkDV_mass               .push_back( h_ntrkdv_mass               );
      h_ntrkDV_mass_s             .push_back( h_ntrkdv_mass_s             );
      h_ntrkDV_mass_xs            .push_back( h_ntrkdv_mass_xs            );
      h_ntrkDV_direction          .push_back( h_ntrkdv_direction          );
      h_ntrkDV_minOpAng           .push_back( h_ntrkdv_minOpAng           );
      h_ntrkDV_maxOpAng           .push_back( h_ntrkdv_maxOpAng           );
      h_ntrkDV_chi2               .push_back( h_ntrkdv_chi2               );
      h_ntrkDV_chi2_s             .push_back( h_ntrkdv_chi2_s             );
      h_ntrkDV_sumd0              .push_back( h_ntrkdv_sumd0              );
      h_ntrkDV_sumz0              .push_back( h_ntrkdv_sumz0              );
      h_ntrkDV_sumP               .push_back( h_ntrkdv_sumP               );
      h_ntrkDV_sumd0_sv           .push_back( h_ntrkdv_sumd0_sv           );
      h_ntrkDV_sumz0_sv           .push_back( h_ntrkdv_sumz0_sv           );
      h_ntrkDV_sumP_sv            .push_back( h_ntrkdv_sumP_sv            );
      h_ntrkDV_sumsqrtd0          .push_back( h_ntrkdv_sumsqrtd0          );
      h_ntrkDV_sumsqrtz0          .push_back( h_ntrkdv_sumsqrtz0          );
      h_ntrkDV_sumsqrtP           .push_back( h_ntrkdv_sumsqrtP           );
      h_ntrkDV_sumsqrtd0_sv       .push_back( h_ntrkdv_sumsqrtd0_sv       );
      h_ntrkDV_sumsqrtz0_sv       .push_back( h_ntrkdv_sumsqrtz0_sv       );
      h_ntrkDV_sumsqrtP_sv        .push_back( h_ntrkdv_sumsqrtP_sv        );
      h_ntrkDV_mind0              .push_back( h_ntrkdv_mind0              );
      h_ntrkDV_minz0              .push_back( h_ntrkdv_minz0              );
      h_ntrkDV_minP               .push_back( h_ntrkdv_minP               );
      h_ntrkDV_mind0_sv           .push_back( h_ntrkdv_mind0_sv           );
      h_ntrkDV_minz0_sv           .push_back( h_ntrkdv_minz0_sv           );
      h_ntrkDV_minP_sv            .push_back( h_ntrkdv_minP_sv            );
      h_ntrkDV_minsqrtd0          .push_back( h_ntrkdv_minsqrtd0          );
      h_ntrkDV_minsqrtz0          .push_back( h_ntrkdv_minsqrtz0          );
      h_ntrkDV_minsqrtP           .push_back( h_ntrkdv_minsqrtP           );
      h_ntrkDV_minsqrtd0_sv       .push_back( h_ntrkdv_minsqrtd0_sv       );
      h_ntrkDV_minsqrtz0_sv       .push_back( h_ntrkdv_minsqrtz0_sv       );
      h_ntrkDV_minsqrtP_sv        .push_back( h_ntrkdv_minsqrtP_sv        );
      h_ntrkDV_maxd0              .push_back( h_ntrkdv_maxd0              );
      h_ntrkDV_maxz0              .push_back( h_ntrkdv_maxz0              );
      h_ntrkDV_maxP               .push_back( h_ntrkdv_maxP               );
      h_ntrkDV_maxd0_sv           .push_back( h_ntrkdv_maxd0_sv           );
      h_ntrkDV_maxz0_sv           .push_back( h_ntrkdv_maxz0_sv           );
      h_ntrkDV_maxP_sv            .push_back( h_ntrkdv_maxP_sv            );
      h_ntrkDV_maxsqrtd0          .push_back( h_ntrkdv_maxsqrtd0          );
      h_ntrkDV_maxsqrtz0          .push_back( h_ntrkdv_maxsqrtz0          );
      h_ntrkDV_maxsqrtP           .push_back( h_ntrkdv_maxsqrtP           );
      h_ntrkDV_maxsqrtd0_sv       .push_back( h_ntrkdv_maxsqrtd0_sv       );
      h_ntrkDV_maxsqrtz0_sv       .push_back( h_ntrkdv_maxsqrtz0_sv       );
      h_ntrkDV_maxsqrtP_sv        .push_back( h_ntrkdv_maxsqrtP_sv        );
      if ( m_histoInfoSwitch->m_vtxErrors ) {
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
    }


    // --- ABCD HISTOS --- //
    // --> add ntrack vertices (i.e. 3+, 4+, 5+ for each vertex type)
    if ( m_histoInfoSwitch->m_abcd ) {
      std::vector<TH2F*> h_abcd_ndv_njetHt;
      std::vector<TH2F*> h_abcd_ndv_njetHt_vrsh;
      std::vector<TH2F*> h_abcd_raw_ndv_njetHt;
      std::vector<TH2F*> h_abcd_raw_ndv_njetHt_vrsh;
      for ( size_t i = 0; i != hDV.size(); ++i ) {
	std::string hdv    = hDV   [i] +  "DV";
	std::string hdvstr = hDVstr[i] + " DV";
	h_abcd_ndv_njetHt          .push_back( book( name, "ABCD_n" + hdv + "_NJetHt",
						     "Leading N " + m_jetStr + " Jet H_{T} [GeV]",
						     100, njetht_xmin, 3000, "n " + hdvstr + "s", 16, -1, 15 ) );
	h_abcd_ndv_njetHt_vrsh     .push_back( book( name, "ABCD_n" + hdv + "_NJetHt_vrsh",
						     "Leading N " + m_jetStr + " Jet H_{T} [GeV] (VR-shift)",
						     100, njetht_xmin, 3000, "n " + hdvstr + "s", 16, -1, 15 ) );
	h_abcd_raw_ndv_njetHt      .push_back( book( name, "ABCD_raw_n" + hdv + "_NJetHt",
						     "Leading N " + m_jetStr + " Jet H_{T} [GeV]",
						     100, njetht_xmin, 3000, "n " + hdvstr + "s", 16, -1, 15 ) );
	h_abcd_raw_ndv_njetHt_vrsh .push_back( book( name, "ABCD_raw_n" + hdv + "_NJetHt_vrsh",
						     "Leading N " + m_jetStr + " Jet H_{T} [GeV] (VR-shift)",
						     100, njetht_xmin, 3000, "n " + hdvstr + "s", 16, -1, 15 ) );
      }
      h_abcd_nDV_njetHt          .push_back( h_abcd_ndv_njetHt          );
      h_abcd_nDV_njetHt_vrsh     .push_back( h_abcd_ndv_njetHt_vrsh     );
      h_abcd_raw_nDV_njetHt      .push_back( h_abcd_raw_ndv_njetHt      );
      h_abcd_raw_nDV_njetHt_vrsh .push_back( h_abcd_raw_ndv_njetHt_vrsh );
    }


    // --- TRIGGER STUDIES --- //
    if ( m_histoInfoSwitch->m_trigTest ) {
      std::string hjetStr    = m_jetStr    + " jet";
      std::string hjetStrOth = m_jetStrOth + " jet";
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
	[ireg]->GetYaxis()->SetTitle( "HLT trigger efficiency" );
      // trigger efficiency: nthJetPt_offTrig / nthJetPt
      h_offTrigEff_nthJetPt
      	.push_back( book( name, "offTrigEff_nthJetPt",
      			  "nth leading " + hjetStr + " p_{T} [GeV]",    100, 50, 500 ) );
      h_offTrigEff_nthJetPt
	[ireg]->GetYaxis()->SetTitle( ( "offline " + hjetStr    + " trigger efficiency" ).c_str() );
      // trigger efficiency: nthJetPt_othOffTrig / nthJetPt
      h_othOffTrigEff_nthJetPt
      	.push_back( book( name, "othOffTrigEff_nthJetPt",
      			  "nth leading " + hjetStr + " p_{T} [GeV]",    100, 50, 500 ) );
      h_othOffTrigEff_nthJetPt
	[ireg]->GetYaxis()->SetTitle( ( "offline " + hjetStrOth + " trigger efficiency" ).c_str() );
      // trigger efficiency: nthJetPt_offTrigJVT / nthJetPt
      h_offTrigJVTEff_nthJetPt
	.push_back( book( name, "offTrigJVTEff_nthJetPt",
			  "nth leading " + hjetStr + " p_{T} [GeV]",    100, 50, 500 ) );
      h_offTrigJVTEff_nthJetPt
	[ireg]->GetYaxis()->SetTitle( ( "offline " + hjetStr    + " JVT trigger efficiency" ).c_str() );
      // trigger efficiency: nthJetPt_othOffTrigJVT / nthJetPt
      h_othOffTrigJVTEff_nthJetPt
	.push_back( book( name, "othOffTrigJVTEff_nthJetPt",
			  "nth leading " + hjetStr + " p_{T} [GeV]",    100, 50, 500 ) );
      h_othOffTrigJVTEff_nthJetPt
	[ireg]->GetYaxis()->SetTitle( ( "offline " + hjetStrOth + " JVT trigger efficiency" ).c_str() );
      
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
	h_triggerEfficiency         [ireg]->GetXaxis()->SetBinLabel( i+1, (trigEffLabels[i]).c_str() );
	h_triggerEfficiency_fourJet [ireg]->GetXaxis()->SetBinLabel( i+1, (trigEffLabels[i]).c_str() );
       	h_triggerEfficiency_search  [ireg]->GetXaxis()->SetBinLabel( i+1, (trigEffLabels[i]).c_str() );
       	h_searchTriggerEfficiency   [ireg]->GetXaxis()->SetBinLabel( i+1, (trigEffLabels[i]).c_str() );
      }
      h_triggerEfficiency           [ireg]->GetYaxis()->SetTitle( "overall trigger efficiency"          );
      h_triggerEfficiency_fourJet   [ireg]->GetYaxis()->SetTitle( "four-jet trigger efficiency"         );
      h_triggerEfficiency_search    [ireg]->GetYaxis()->SetTitle( "search-region trigger efficiency"    );
      h_searchTriggerEfficiency     [ireg]->GetYaxis()->SetTitle( "search-region efficiency vs trigger" );
      
    } // end trigger study
  
  } // end loop over regions

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: execute ( TTree* tree, Long64_t treeEntry, const std::vector<EJsHelper::Region>& regions,
					    const EJsHelper::BaseDV& base_dv )
{
  if ( m_debug ) Info( "EJsHistogramManager::execute()", "filling histograms" );

  tree->GetEntry( treeEntry );

  // set weights
  if ( m_mc ) weight = m_mcEventWeight * m_filteff * m_xsec * 1e6 * lumi / m_sumw_init; // --> include pileup? k-factor? branching ratio?
  // --> sum of weights only includes mcEventWeight; rest is just scaling factor we can apply at once to histograms as a whole
    
  // loop over regions + fill histograms
  for ( size_t ireg = 0; ireg != regions.size(); ++ireg ) {
    const EJsHelper::Region region = regions[ireg];

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
	h_npv                [ireg] ->Fill( m_npv,                weight );
	h_actualMu           [ireg] ->Fill( m_actualMu,           weight );
	h_averageMu          [ireg] ->Fill( m_averageMu,          weight );
	h_corrActualMu       [ireg] ->Fill( m_corrActualMu,       weight );
	h_corrAverageMu      [ireg] ->Fill( m_corrAverageMu,      weight );
	h_corrScaleActualMu  [ireg] ->Fill( m_corrScaleActualMu,  weight );
	h_corrScaleAverageMu [ireg] ->Fill( m_corrScaleAverageMu, weight );
      }
      // primary vertex
      if ( m_histoInfoSwitch->m_pv ) {
	h_pv_x    [ireg] ->Fill( m_pv_x,    weight );
	h_pv_y    [ireg] ->Fill( m_pv_y,    weight );
	h_pv_z    [ireg] ->Fill( m_pv_z,    weight );
	h_pv_r    [ireg] ->Fill( m_pv_r,    weight );
	h_pv_phi  [ireg] ->Fill( m_pv_phi,  weight );
	h_pv_ntrk [ireg] ->Fill( m_pv_ntrk, weight );
      }
      // leading N-jet Ht
      h_njetHt      [ireg] ->Fill( m_njetHt,                    weight );
      h_njetHt_vrsh [ireg] ->Fill( m_njetHt * m_VRShift_njetHt, weight );
    }


    
    // ----------------- //
    // --- RECO JETS --- //
    // ----------------- //

    // set vector of nJet
    std::vector<int> n_jet ( m_nTypeJs, 0 );

    // set vectors of dijet four-vectors
    TLorentzVector p4jj_max;
    TLorentzVector p4jj_min;
    p4jj_max.SetPtEtaPhiM( 0, 0, 0, 0 );
    p4jj_min.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<TLorentzVector> p4_dijet_max ( m_nTypeJs, p4jj_max );
    std::vector<TLorentzVector> p4_dijet_min ( m_nTypeJs, p4jj_min );
    
    std::pair<int, int> p4jj_max_ix = std::make_pair( -1, -1 );
    std::pair<int, int> p4jj_min_ix = std::make_pair( -1, -1 );
    std::vector<std::pair<int,int>> p4_dijet_max_ix ( m_nTypeJs, p4jj_max_ix );
    std::vector<std::pair<int,int>> p4_dijet_min_ix ( m_nTypeJs, p4jj_min_ix );

    std::vector<float> p4_dijet_sum_pt    ( m_nTypeJs, 0 );
    std::vector<float> p4_dijet_sum_eta   ( m_nTypeJs, 0 );
    std::vector<float> p4_dijet_sum_phi   ( m_nTypeJs, 0 );
    std::vector<float> p4_dijet_sum_m     ( m_nTypeJs, 0 );
    std::vector<float> p4_dijet_sum_sumpt ( m_nTypeJs, 0 );
    std::vector<float> p4_dijet_sum_dr    ( m_nTypeJs, 0 );
    std::vector<int>   p4_dijet_sum_count ( m_nTypeJs, 0 );

    // set vectors of all-jet sums
    TLorentzVector jp4sum;
    jp4sum.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<TLorentzVector> jet_p4_sum   ( m_nTypeJs, jp4sum );
    std::vector<float>          jet_p4_sumPt ( m_nTypeJs, 0      );
  
    // loop over jets
    for ( int i = 0; i != m_jet_n; ++i ) {

      // get jet four-momentum
      TLorentzVector jet_p4;
      jet_p4.SetPtEtaPhiM( m_jet_pt->at(i), m_jet_eta->at(i), m_jet_phi->at(i), m_jet_M->at(i) );

      // set vector of jet types
      std::vector<int> jet;

      // --> base jets (always true)
      jet .push_back( true );
      // --> leading jets
      bool leadJ = false;
      if ( m_jet_index ->at(i) < m_nJets ) leadJ = true;
      jet .push_back( leadJ );

      // truth-matching (to dark jets)
      // --> avg 3/4 lead jets dark-matched; look for further discrimination to get avg closer to 2/4...
      bool darkJ        = false;
      bool nomatchJ     = false;
      if ( m_mc ) {
	if ( m_jet_isDark ->at(i) && m_jet_isTruth ->at(i) ) {
	  int truthIx = m_jet_truthIndex ->at(i);
	  if ( m_jet_darkID ->at(i) == m_truthJet_darkID ->at(truthIx) )
	    darkJ = true;
	}
	if ( !darkJ ) nomatchJ = true;
	if ( m_histoInfoSwitch->m_jetTruth ) {
	  std::vector<int> mJ = { darkJ, nomatchJ };
	  std::vector<int> miJ;
	  for ( size_t ij = 0; ij != jet.size(); ++ij )
	    miJ .push_back( jet[ij] );
	  for ( size_t ii = 0; ii != mJ.size(); ++ii )
	    for ( size_t jj = 0; jj != miJ.size(); ++jj )
	      jet .push_back( mJ[ii] && miJ[jj] );
	}
      }

      // loop over jet types and fill histograms
      for ( size_t ij = 0; ij != jet.size(); ++ij ) {
	
	if ( !jet[ij] ) continue; // --> skip jet failing ijth jet type selection
	++n_jet[ij];

	// double loop over jets to calculate di-jet parameters
	if ( m_histoInfoSwitch->m_dijets ) {
	  for ( int i2 = i+1; i2 != m_jet_n; ++i2 ) {
	    
	    // set vector of jet2 types
	    std::vector<int> jet2;
	    
	    // --> base jets (always true)
	    jet2 .push_back( true );
	    // --> leading jets
	    bool leadJ2 = false;
	    if ( m_jet_index ->at(i2) < m_nJets ) leadJ2 = true;
	    jet2 .push_back( leadJ2 );
	    // --> truth-matching (to dark jets)
	    bool darkJ2      = false;
	    bool darktruthJ2 = false;
	    bool nomatchJ2   = false;
	    if ( m_mc ) {
	      if ( m_jet_isDark ->at(i2) ) {
		darkJ2 = true;
		if ( m_jet_isTruth ->at(i2) ) {
		  int truthIx2 = m_jet_truthIndex ->at(i2);
		  if ( m_jet_darkID ->at(i2) == m_truthJet_darkID ->at(truthIx2) )
		    darktruthJ2 = true;
		}
	      }
	      if ( !darkJ2 ) nomatchJ2 = true;
	      if ( m_histoInfoSwitch->m_jetTruth ) {
		std::vector<int> mJ2 = { darkJ2, darktruthJ2, nomatchJ2 };
		std::vector<int> miJ2;
		for ( size_t ij2 = 0; ij2 != jet2.size(); ++ij2 )
		  miJ2 .push_back( jet2[ij2] );
		for ( size_t ii2 = 0; ii2 != mJ2.size(); ++ii2 )
		  for ( size_t jj2 = 0; jj2 != miJ2.size(); ++jj2 )
		    jet2 .push_back( mJ2[ii2] && miJ2[jj2] );
	      }
	    }
	    
	    if ( !jet2[ij] ) continue; // --> skip jet2 if not passing ijth jet type cut from above
	    
	    // get jet2 four-momentum
	    TLorentzVector jet2_p4;
	    jet2_p4.SetPtEtaPhiM( m_jet_pt->at(i2), m_jet_eta->at(i2), m_jet_phi->at(i2), m_jet_M->at(i2) );
	    
	    // calculate dijet four-momentum
	    TLorentzVector jj_p4 = jet_p4 + jet2_p4;
	    
	    // sum pt, calculate dR for jet pairs
	    float jj_sumPt = jet_p4.Pt() + jet2_p4.Pt();
	    float jj_dR    = EJsHelper::deltaR( jet_p4.Eta(), jet2_p4.Eta(), jet_p4.Phi(), jet2_p4.Phi() );
	    
	    if ( doHists ) {
	      h_dijet_pt    [ireg][ij] ->Fill( jj_p4.Pt(),  weight );
	      h_dijet_eta   [ireg][ij] ->Fill( jj_p4.Eta(), weight );
	      h_dijet_phi   [ireg][ij] ->Fill( jj_p4.Phi(), weight );
	      h_dijet_m     [ireg][ij] ->Fill( jj_p4.M(),   weight );
	      h_dijet_sumPt [ireg][ij] ->Fill( jj_sumPt,    weight );
	      h_dijet_dR    [ireg][ij] ->Fill( jj_dR,       weight );
	    }
	    
	    // get max/min dijet four-momentum
	    if ( jj_p4.M() > p4_dijet_max[ij].M() ) {
	      p4_dijet_max    [ij] = jj_p4;
	      p4_dijet_max_ix [ij] = std::make_pair( i, i2 );
	    }
	    if ( jj_p4.M() < p4_dijet_min[ij].M() || ( i == 0 && i2 == 1 ) ) { // save first pair as initial min
	      p4_dijet_min    [ij] = jj_p4;
	      p4_dijet_min_ix [ij] = std::make_pair( i, i2 );
	    }
	    
	    // sum dijet system variables
	    p4_dijet_sum_pt    [ij] += jj_p4.Pt();
	    p4_dijet_sum_eta   [ij] += jj_p4.Eta();
	    p4_dijet_sum_phi   [ij] += jj_p4.Phi();
	    p4_dijet_sum_m     [ij] += jj_p4.M();
	    p4_dijet_sum_sumpt [ij] += jj_sumPt;
	    p4_dijet_sum_dr    [ij] += jj_dR;
	    p4_dijet_sum_count [ij] += 1;
	    
	  } // end loop over dijets
	} // end if m_dijets info switch

	// sum p4 for all jets in event
	jet_p4_sum   [ij] += jet_p4;
	jet_p4_sumPt [ij] += jet_p4.Pt();
	  
	if ( !doHists ) continue;
	
	h_jet_pt    [ireg][ij] ->Fill( m_jet_pt    ->at(i), weight );
	h_jet_pt_l  [ireg][ij] ->Fill( m_jet_pt    ->at(i), weight );
	h_jet_pt_m  [ireg][ij] ->Fill( m_jet_pt    ->at(i), weight );
	h_jet_pt_s  [ireg][ij] ->Fill( m_jet_pt    ->at(i), weight );
	h_jet_eta   [ireg][ij] ->Fill( m_jet_eta   ->at(i), weight );
	h_jet_phi   [ireg][ij] ->Fill( m_jet_phi   ->at(i), weight );
	h_jet_E     [ireg][ij] ->Fill( m_jet_E     ->at(i), weight );
	h_jet_M     [ireg][ij] ->Fill( m_jet_M     ->at(i), weight );
	h_jet_rapid [ireg][ij] ->Fill( m_jet_rapid ->at(i), weight );
	// extra jet kinematics
	if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	  h_jet_px   [ireg][ij] ->Fill( jet_p4.Px(), weight );
	  h_jet_py   [ireg][ij] ->Fill( jet_p4.Py(), weight );
	  h_jet_pz   [ireg][ij] ->Fill( jet_p4.Pz(), weight );
	  h_jet_Et   [ireg][ij] ->Fill( jet_p4.Et(), weight );
	  h_jet_Et_m [ireg][ij] ->Fill( jet_p4.Et(), weight );
	  h_jet_Et_s [ireg][ij] ->Fill( jet_p4.Et(), weight );
	}

	
	// matched tracks
	std::vector<int> n_jettrk ( m_nTypeTrks, 0 );
	// loop over matched tracks
	for ( int jtrk = 0; jtrk != m_jet_trk_n ->at(i); ++jtrk ) {
	  int jetTrkIx = m_jet_trk_index ->at(i)[jtrk];
	  // set vector of matched track types
	  std::vector<int> jettrk;
	  getTrkTypes( jetTrkIx, jettrk );
	  // loop over matched track types
	  for ( size_t jt = 0; jt != jettrk.size(); ++jt ) {
	    if ( !jettrk[jt] ) continue;
	    ++n_jettrk[jt];
	    if ( !doHists ) continue;
	    //if ( m_histoInfoSwitch->m_jetTrks )
	  } // end loop over matched track types
	} // end loop over matched tracks
	
	// fill matched track count histograms
	if ( doHists )
	  for ( size_t jt = 0; jt != n_jettrk.size(); ++jt )
	    h_jet_ntrk [ireg][ij][jt] ->Fill( n_jettrk[jt], weight );
	

	// matched secondary vertices
	int nJetSV = m_jet_secVtx_n ->at(i);
	h_jet_nsv [ireg][ij] ->Fill( nJetSV, weight );
	// loop over matched svs
	if ( m_histoInfoSwitch->m_jetVerts ) {
	  for ( int jsv = 0; jsv != nJetSV; ++jsv ) {
	    double dR = m_jet_secVtx_dR ->at(i)[jsv];
	    h_jet_sv_dR [ireg][ij] ->Fill( dR, weight );
	  }
	}

	// --> look at min/max/sum track/vtx parameters (esp. min/max dR)
	// --> look at number of selected, LRT, vtx tracks, etc.
	
      } // end loop over jet types

      // leading jets
      if ( m_numLeadJets && doHists ) {
	if ( i < m_numLeadJets ) {
	  h_jetN_pt     [ireg][i] ->Fill( m_jet_pt    ->at(i), weight );
	  h_jetN_pt_l   [ireg][i] ->Fill( m_jet_pt    ->at(i), weight );
	  h_jetN_pt_m   [ireg][i] ->Fill( m_jet_pt    ->at(i), weight );
	  h_jetN_pt_s   [ireg][i] ->Fill( m_jet_pt    ->at(i), weight );
	  h_jetN_eta    [ireg][i] ->Fill( m_jet_eta   ->at(i), weight );
      	  h_jetN_phi    [ireg][i] ->Fill( m_jet_phi   ->at(i), weight );
      	  h_jetN_E      [ireg][i] ->Fill( m_jet_E     ->at(i), weight );
       	  h_jetN_M      [ireg][i] ->Fill( m_jet_M     ->at(i), weight );
       	  h_jetN_rapid  [ireg][i] ->Fill( m_jet_rapid ->at(i), weight );
	  if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
      	    h_jetN_Et   [ireg][i] ->Fill( jet_p4.Et(),         weight );
      	    h_jetN_Et_m [ireg][i] ->Fill( jet_p4.Et(),         weight );
      	    h_jetN_Et_s [ireg][i] ->Fill( jet_p4.Et(),         weight );
      	  }
	  h_jetN_ntrk [ireg][i] ->Fill( m_jet_trk_n ->at(i), weight );
	  if ( m_histoInfoSwitch->m_jetTrks ) {
	    for ( int jtrk = 0; jtrk != m_jet_trk_n ->at(i); ++jtrk ) {
	      double dR = m_jet_trk_dR ->at(i)[jtrk];
	      h_jetN_trk_dR [ireg][i] ->Fill( dR, weight );
	    }
	  }
	  h_jetN_nsv [ireg][i] ->Fill( m_jet_secVtx_n ->at(i), weight );
	  if ( m_histoInfoSwitch->m_jetVerts ) {
	    for ( int jsv = 0; jsv != m_jet_secVtx_n ->at(i); ++jsv ) {
	      double dR = m_jet_secVtx_dR ->at(i)[jsv];
	      h_jetN_sv_dR [ireg][i] ->Fill( dR, weight );
	    }
	  }
	}
      } // end if leading jets
      
    } // end loop over jets

    // fill jet-count, min/max/avg-dijet, njet histograms
    if ( doHists ) {
      for ( size_t ij = 0; ij != n_jet.size(); ++ij ) {
	h_jet_n [ireg][ij] ->Fill( n_jet[ij], weight );

	// add counts
	if ( m_histoInfoSwitch->m_dijets ) {
	  int   max_ix1   = p4_dijet_max_ix[ij].first;
	  int   max_ix2   = p4_dijet_max_ix[ij].second;
	  float max_sumpt = 0;
	  float max_dr    = 0;
	  if ( max_ix1 != -1 && max_ix2 != -1 ) {
	    max_sumpt = m_jet_pt->at(max_ix1) + m_jet_pt->at(max_ix2);
	    max_dr    = EJsHelper::deltaR( m_jet_eta->at(max_ix1), m_jet_eta->at(max_ix2), m_jet_phi->at(max_ix1), m_jet_phi->at(max_ix2) );
	  }
	  h_dijet_maxp4_pt    [ireg][ij] ->Fill( p4_dijet_max[ij].Pt(),  weight );
	  h_dijet_maxp4_eta   [ireg][ij] ->Fill( p4_dijet_max[ij].Eta(), weight );
	  h_dijet_maxp4_phi   [ireg][ij] ->Fill( p4_dijet_max[ij].Phi(), weight );
	  h_dijet_maxp4_m     [ireg][ij] ->Fill( p4_dijet_max[ij].M(),   weight );
	  h_dijet_maxp4_sumPt [ireg][ij] ->Fill( max_sumpt,                 weight );
	  h_dijet_maxp4_dR    [ireg][ij] ->Fill( max_dr,                    weight );
	  
	  int   min_ix1   = p4_dijet_min_ix[ij].first;
	  int   min_ix2   = p4_dijet_min_ix[ij].second;
	  float min_sumpt = 0;
	  float min_dr    = 0;
	  if ( min_ix1 != -1 && min_ix2 != -1 ) {
	    min_sumpt = m_jet_pt->at(min_ix1) + m_jet_pt->at(min_ix2);
	    min_dr    = EJsHelper::deltaR( m_jet_eta->at(min_ix1), m_jet_eta->at(min_ix2), m_jet_phi->at(min_ix1), m_jet_phi->at(min_ix2) );
	  }
	  h_dijet_minp4_pt    [ireg][ij] ->Fill( p4_dijet_min[ij].Pt(),  weight );
	  h_dijet_minp4_eta   [ireg][ij] ->Fill( p4_dijet_min[ij].Eta(), weight );
	  h_dijet_minp4_phi   [ireg][ij] ->Fill( p4_dijet_min[ij].Phi(), weight );
	  h_dijet_minp4_m     [ireg][ij] ->Fill( p4_dijet_min[ij].M(),   weight );
	  h_dijet_minp4_sumPt [ireg][ij] ->Fill( min_sumpt,                 weight );
	  h_dijet_minp4_dR    [ireg][ij] ->Fill( min_dr,                    weight );

	  int sum_ct = p4_dijet_sum_count [ij];
	  h_dijet_avgp4_pt    [ireg][ij] ->Fill( p4_dijet_sum_pt   [ij]/sum_ct, weight );
	  h_dijet_avgp4_eta   [ireg][ij] ->Fill( p4_dijet_sum_eta  [ij]/sum_ct, weight );
	  h_dijet_avgp4_phi   [ireg][ij] ->Fill( p4_dijet_sum_phi  [ij]/sum_ct, weight );
	  h_dijet_avgp4_m     [ireg][ij] ->Fill( p4_dijet_sum_m    [ij]/sum_ct, weight );
	  h_dijet_avgp4_sumPt [ireg][ij] ->Fill( p4_dijet_sum_sumpt[ij]/sum_ct, weight );
	  h_dijet_avgp4_dR    [ireg][ij] ->Fill( p4_dijet_sum_dr   [ij]/sum_ct, weight );
	  h_dijet_n           [ireg][ij] ->Fill(                           sum_ct, weight );
	}

	// event level jet variables
	h_njet_pt    [ireg][ij] ->Fill( jet_p4_sum  [ij].Pt(),  weight );
	h_njet_eta   [ireg][ij] ->Fill( jet_p4_sum  [ij].Eta(), weight );
	h_njet_phi   [ireg][ij] ->Fill( jet_p4_sum  [ij].Phi(), weight );
	h_njet_m     [ireg][ij] ->Fill( jet_p4_sum  [ij].M(),   weight );
	h_njet_sumPt [ireg][ij] ->Fill( jet_p4_sumPt[ij],       weight );
      }
    }

    // find singular dijet invariant mass (average of dijet pairs of leading four jets with smallest difference between them)
    // --> note: this method only works for specific case of m_nJets = 4
    std::vector<std::pair<int,int>> dijet_indices;
    for ( int i = 0; i != m_jet_n; ++i ) {
      for ( int j = i+1; j != m_jet_n; ++j ) {
	if ( i >= m_nJets || j >= m_nJets ) continue;
	dijet_indices.push_back( std::make_pair( i, j ) );
      }
    }
    float mindiff      = AlgConsts::maxValue;
    float mindiff_invM = 0;
    for ( int i = 0; i != dijet_indices.size(); ++i ) {
      for ( int j = i+1; j != dijet_indices.size(); ++j ) {
	if ( dijet_indices[i].first  == dijet_indices[j].first  ||
	     dijet_indices[i].first  == dijet_indices[j].second ||
	     dijet_indices[i].second == dijet_indices[j].first  ||
	     dijet_indices[i].second == dijet_indices[j].second ) continue;
	TLorentzVector p4_j1, p4_j2, p4_j3, p4_j4;
	int ix_j1 = dijet_indices[i].first;
	int ix_j2 = dijet_indices[i].second;
	int ix_j3 = dijet_indices[j].first;
	int ix_j4 = dijet_indices[j].second;
	p4_j1.SetPtEtaPhiM( m_jet_pt->at(ix_j1), m_jet_eta->at(ix_j1), m_jet_phi->at(ix_j1), m_jet_M->at(ix_j1) );
	p4_j2.SetPtEtaPhiM( m_jet_pt->at(ix_j2), m_jet_eta->at(ix_j2), m_jet_phi->at(ix_j2), m_jet_M->at(ix_j2) );
	p4_j3.SetPtEtaPhiM( m_jet_pt->at(ix_j3), m_jet_eta->at(ix_j3), m_jet_phi->at(ix_j3), m_jet_M->at(ix_j3) );
	p4_j4.SetPtEtaPhiM( m_jet_pt->at(ix_j4), m_jet_eta->at(ix_j4), m_jet_phi->at(ix_j4), m_jet_M->at(ix_j4) );
	float invM_j12 = ( p4_j1 + p4_j2 ).M();
	float invM_j34 = ( p4_j3 + p4_j4 ).M();
	float avg_invM  =     ( invM_j12 + invM_j34 ) / 2;
	float diff_invM = fabs( invM_j12 - invM_j34 );
	h_NJetMjj_all     [ireg] ->Fill( avg_invM,  weight );
	h_NJetMjjDiff_all [ireg] ->Fill( diff_invM, weight );
	if ( diff_invM < mindiff ) {
	  mindiff      = diff_invM;
	  mindiff_invM = avg_invM;
	}	
      }
    }
    h_NJetMjj     [ireg] ->Fill( mindiff_invM, weight );
    h_NJetMjjDiff [ireg] ->Fill( mindiff,      weight );
    

    
    // -------------- //
    // --- TRACKS --- //
    // -------------- //

    // set vector of ntrk counters
    std::vector<int> n_trk ( m_nTypeTrks, 0 );

    int n_svTrks = 0;
    
    // loop over tracks
    for ( int i = 0; i != m_trk_n; ++i ) {
      if ( m_trk_isSV ->at(i) ) ++n_svTrks;
      // set vector of track types
      std::vector<int> trk;
      getTrkTypes( i, trk );
      // loop over track types and fill histograms
      for ( size_t it = 0; it != trk.size(); ++it ) {
	if ( !trk[it] ) continue;
	++n_trk[it];
	//if ( !doHists ) continue;
      } // end loop over track types
    } // end loop over tracks

    // fill track count histograms
    if ( doHists )
      for ( size_t it = 0; it != n_trk.size(); ++it )
	h_trk_n [ireg][it] ->Fill( n_trk[it], weight );



    // ---------------------- //
    // --- TRUTH VERTICES --- //
    // ---------------------- //
    if ( m_mc ) {
      if ( doHists )
	h_truthVtx_n [ireg] ->Fill( m_truthVtx_n, weight );

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
	  
	  h_truthDarkPionDecay_x     [ireg]->Fill( m_truthVtx_x     ->at(i), weight );
	  h_truthDarkPionDecay_y     [ireg]->Fill( m_truthVtx_y     ->at(i), weight );
	  h_truthDarkPionDecay_z     [ireg]->Fill( m_truthVtx_z     ->at(i), weight );
	  h_truthDarkPionDecay_r     [ireg]->Fill( m_truthVtx_r     ->at(i), weight );
	  h_truthDarkPionDecay_pt    [ireg]->Fill( m_truthVtx_pt    ->at(i), weight );
	  h_truthDarkPionDecay_eta   [ireg]->Fill( m_truthVtx_eta   ->at(i), weight );
	  h_truthDarkPionDecay_phi   [ireg]->Fill( m_truthVtx_phi   ->at(i), weight );
	  h_truthDarkPionDecay_mass  [ireg]->Fill( m_truthVtx_mass  ->at(i), weight );
	  h_truthDarkPionDecay_nOutP [ireg]->Fill( m_truthVtx_nOutP ->at(i), weight );
	  
	  h_truthDarkPionDecay_nDesc     [ireg]->Fill( m_truthVtx_nDesc     ->at(i), weight );
	  h_truthDarkPionDecay_nRecoDesc [ireg]->Fill( m_truthVtx_nRecoDesc ->at(i), weight );
	  h_truthDarkPionDecay_nSelDesc  [ireg]->Fill( m_truthVtx_nSelDesc  ->at(i), weight );
	  
	  h_truthDarkPionDecay_nPos [ireg]->Fill( m_truthVtx_nPos ->at(i), weight );
	}
	// truth k-short decay
	else if ( truthVtx_isKshort && ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_kshorts ) ) {
	  ++nTruthVtx_kshort;

	  if ( !doHists ) continue;
	  
	  h_truthKshortDecay_x     [ireg]->Fill( m_truthVtx_x     ->at(i), weight );
	  h_truthKshortDecay_y     [ireg]->Fill( m_truthVtx_y     ->at(i), weight );
	  h_truthKshortDecay_z     [ireg]->Fill( m_truthVtx_z     ->at(i), weight );
	  h_truthKshortDecay_r     [ireg]->Fill( m_truthVtx_r     ->at(i), weight );
	  h_truthKshortDecay_pt    [ireg]->Fill( m_truthVtx_pt    ->at(i), weight );
	  h_truthKshortDecay_eta   [ireg]->Fill( m_truthVtx_eta   ->at(i), weight );
	  h_truthKshortDecay_phi   [ireg]->Fill( m_truthVtx_phi   ->at(i), weight );
	  h_truthKshortDecay_mass  [ireg]->Fill( m_truthVtx_mass  ->at(i), weight );
	  h_truthKshortDecay_nOutP [ireg]->Fill( m_truthVtx_nOutP ->at(i), weight );
	  
	  h_truthKshortDecay_nDesc     [ireg]->Fill( m_truthVtx_nDesc     ->at(i), weight );
	  h_truthKshortDecay_nRecoDesc [ireg]->Fill( m_truthVtx_nRecoDesc ->at(i), weight );
	  h_truthKshortDecay_nSelDesc  [ireg]->Fill( m_truthVtx_nSelDesc  ->at(i), weight );
	  
	  h_truthKshortDecay_nPos [ireg]->Fill( m_truthVtx_nPos ->at(i), weight );
	}
      }

      if ( doHists ) {
	if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_darkPions )
	  h_truthDarkPionDecay_n [ireg] ->Fill( nTruthVtx_darkPion, weight );
	if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_kshorts   )
	  h_truthKshortDecay_n   [ireg] ->Fill( nTruthVtx_kshort,   weight );
      }
    }



    // -------------------------- //
    // --- SECONDARY VERTICES --- //
    // -------------------------- //
    // eventually will decide on DV type to use and can make generic "DV" histograms w/ no info switch

    // set vector of nDV, ntrkDV counters
    std::vector<int> n_DV ( m_nTypeDVs, 0 );
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

      // set kinematic variables based on base DV type
      float secVtx_pt              = 0;
      float secVtx_eta             = 0;
      float secVtx_phi             = 0;
      float secVtx_mass            = 0;
      float secVtx_massNA          = 0;
      float secVtx_dir             = 0;
      float secVtx_minOpAng        = 0;
      float secVtx_maxOpAng        = 0;
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
      float secVtx_mind0           = 0;
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
      float secVtx_maxd0           = 0;
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
      int   secVtx_ntrk            = 0;
      int   secVtx_ntrk_final      = 0;
      int   secVtx_ntrk_sel        = 0;
      int   secVtx_ntrk_assoc      = 0;
      int   secVtx_ntrk_lrt        = 0;
      int   secVtx_ntrk_d0         = 0;
      int   secVtx_ntrk_seld0      = 0;
      if      ( base_dv.type == EJsHelper::BARE     ) {
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
      else if ( base_dv.type == EJsHelper::CLEAN    ) {
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
      else if ( base_dv.type == EJsHelper::FILTERED ) {
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
      // else if ( base_dv.type == EJsHelper::TRIMMED ) {...}
      // --> will have to loop over tracks and re-calculate kinematic variables using only trimmed tracks...

      // loop over tracks
      for ( int itrk = 0; itrk != m_secVtx_ntrk ->at(i); ++itrk ) {
	if ( base_dv.type == EJsHelper::CLEAN    && !m_secVtx_trk_isClean ->at(i)[itrk] ) continue;
	if ( base_dv.type == EJsHelper::FILTERED && !m_secVtx_trk_isFilt  ->at(i)[itrk] ) continue;
	// if ( base_dv.type == EJsHelper::TRIMMED && *track fails trimming cuts* ) continue;
	
	int trkIx = m_secVtx_trk_index ->at(i)[itrk];

	if ( m_secVtx_trk_isFinal ->at(i)[itrk]      ) ++secVtx_ntrk_final;
	if ( m_secVtx_trk_isSel   ->at(i)[itrk]      ) ++secVtx_ntrk_sel;
	if ( m_secVtx_trk_isAssoc ->at(i)[itrk]      ) ++secVtx_ntrk_assoc;
	if ( m_trk_isLRT          ->at(trkIx)        ) ++secVtx_ntrk_lrt;
	if ( m_trk_d0             ->at(trkIx) >= 2.0 ) ++secVtx_ntrk_d0;
	if ( m_secVtx_trk_isSel   ->at(i)[itrk] &&
	     m_trk_d0             ->at(trkIx) >= 2.0 ) ++secVtx_ntrk_seld0;

	float trk_theta_sv  = 2 * atan( exp( -1 * m_secVtx_trk_eta_sv ->at(i)[itrk] ) );
	float trk_p_sv      = m_secVtx_trk_pt_sv ->at(i)[itrk] / sin( trk_theta_sv ); 
	float trk_qOverP_sv = m_trk_charge ->at(trkIx) / trk_p_sv;
	
	// squared errors
	float trk_errd0     = m_trk_errd0              ->at(trkIx);
	float trk_errz0     = m_trk_errz0              ->at(trkIx);
	float trk_errP      = m_trk_errP               ->at(trkIx)   * 1e6;
	float trk_errd0_sv  = m_secVtx_trk_errd0_sv    ->at(i)[itrk];
	float trk_errz0_sv  = m_secVtx_trk_errz0_sv    ->at(i)[itrk];
	float trk_errP_sv   = m_secVtx_trk_errP_sv     ->at(i)[itrk] * 1e6;
	// squared fractional errors
	float trk_fracerrd0    = trk_errd0    / pow(m_trk_d0           ->at(trkIx),        2);
	float trk_fracerrz0    = trk_errz0    / pow(m_trk_z0           ->at(trkIx),        2);
	float trk_fracerrP     = trk_errP     / pow(m_trk_qOverP       ->at(trkIx) * 1000, 2);
	float trk_fracerrd0_sv = trk_errd0_sv / pow(m_secVtx_trk_d0_sv ->at(i)[itrk],   2);
	float trk_fracerrz0_sv = trk_errz0_sv / pow(m_secVtx_trk_z0_sv ->at(i)[itrk],   2);
	float trk_fracerrP_sv  = trk_errP_sv  / pow(trk_qOverP_sv,                         2);
	  
	// sum vertex track parameters
	secVtx_sumd0           += fabs(m_trk_d0           ->at(trkIx));
	secVtx_sumz0           += fabs(m_trk_z0           ->at(trkIx));
	secVtx_sumP            += fabs(m_trk_qOverP       ->at(trkIx) * 1000);
	secVtx_sumd0_sv        += fabs(m_secVtx_trk_d0_sv ->at(i)[itrk]);
	secVtx_sumz0_sv        += fabs(m_secVtx_trk_z0_sv ->at(i)[itrk]);
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
	
	// find min/max track parameters
	float fabsz0    = fabs( m_trk_z0           ->at(trkIx)   );
	float fabsP     = fabs( 1000*m_trk_qOverP  ->at(trkIx)   );
	float fabsd0_sv = fabs( m_secVtx_trk_d0_sv ->at(i)[itrk] );
	float fabsz0_sv = fabs( m_secVtx_trk_z0_sv ->at(i)[itrk] );
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
      }

      
      // set vector of DV types
      std::vector<int> DV;

      // --> base vertices (bare, clean, filtered, or trimmed)
      bool baseDV = false;
      if      ( base_dv.type == EJsHelper::BARE     ) { if ( m_secVtx_ntrk       ->at(i) > 1 ) baseDV = true; }
      else if ( base_dv.type == EJsHelper::CLEAN    ) { if ( m_secVtx_ntrk_clean ->at(i) > 1 ) baseDV = true; } // require final tracks ?
      else if ( base_dv.type == EJsHelper::FILTERED ) { if ( m_secVtx_ntrk_filt  ->at(i) > 1 ) baseDV = true; }
      // else if ( base_dv.type == EJsHelper::TRIMMED ) { ... }
      // --> will have to count trimmed tracks here (or above) and recalculate kinematic variables...
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_baseVerts ) {
	DV .push_back( baseDV );
      }
      
      // --> vertices near (leading) jets
      bool byJetDV     = false;
      bool byLeadJetDV = false;
      if ( m_secVtx_jetMatched ->at(i) ) byJetDV = true;
      if ( m_secVtx_jetMatched ->at(i) && m_secVtx_jetMatch_index ->at(i) < m_nJets ) byLeadJetDV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_byJetVerts ) {
	DV .push_back( baseDV && byJetDV     );
	DV .push_back( baseDV && byLeadJetDV ); 
      }
      // --> fiducial vertices --> cut on r, z, chi2
      bool fiducDV = false;
      if ( m_secVtx_r    ->at(i) < 300 && fabs( m_secVtx_z ->at(i) ) < 300 &&
	   m_secVtx_chi2 ->at(i) < 5 ) fiducDV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_fiducialVerts ) {
	DV .push_back( baseDV && fiducDV );
      }
      // --> k-short-mass-cut vertices --> cut on vertex mass
      bool ksmDV = false;
      if ( secVtx_mass > 0.7 ) ksmDV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_ksmVerts ) {
	DV .push_back( baseDV && ksmDV );
      }
      // --> low-pt cut
      bool ptDV = false;
      if ( secVtx_pt > 2.5 ) ptDV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_ptVerts ) {
	DV .push_back( baseDV && ptDV );
      }
      // --> min-d0 cuts
      bool mind0DV  = false;
      if ( secVtx_mind0 < 10 ) mind0DV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_d0Verts ) {
	DV .push_back( baseDV && mind0DV );
      }
      // --> min-z0 cuts
      bool minz0DV = false;
      if ( secVtx_minz0 < 100 ) minz0DV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_z0Verts ) {
	DV .push_back( baseDV && minz0DV );
      }
      // --> min sqrt-error d0/z0 cuts -- consider tightening (+ additional window cut b/w 0.5-1.0 for z0 (see double peak feature))
      bool minsqerrd0DV = false;
      bool minsqerrz0DV = false;
      if ( sqrt(sqrt(secVtx_minerrd0)) < 0.5 ) minsqerrd0DV = true;
      if ( sqrt(sqrt(secVtx_minerrz0)) < 1.5 ) minsqerrz0DV = true;
      if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_d0z0ErrVerts ) {
	DV .push_back( baseDV && minsqerrd0DV );
	DV .push_back( baseDV && minsqerrz0DV );
      }

      // combination cuts
      // --> by (leading) jets + fiducial cut
      bool byJetFidDV     = false;
      bool byLeadJetFidDV = false;
      if ( byJetDV     && fiducDV ) byJetFidDV     = true;
      if ( byLeadJetDV && fiducDV ) byLeadJetFidDV = true;
      if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts && m_histoInfoSwitch->m_fiducialVerts ) ) {
	DV .push_back( baseDV && byJetFidDV     );
	DV .push_back( baseDV && byLeadJetFidDV );
      }
      // --> by (leading) jets + k-short mass cut
      bool byJetKsmDV = false;
      bool byLeadJetKsmDV = false;
      if ( byJetDV     && ksmDV ) byJetKsmDV     = true;
      if ( byLeadJetDV && ksmDV ) byLeadJetKsmDV = true;
      if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts && m_histoInfoSwitch->m_ksmVerts ) ) {
	DV .push_back( baseDV && byJetKsmDV     );
	DV .push_back( baseDV && byLeadJetKsmDV );
      }
      // --> by (leading) jets + low-pt cut
      bool byJetPtDV     = false;
      bool byLeadJetPtDV = false;
      if ( byJetDV     && ptDV ) byJetPtDV     = true;
      if ( byLeadJetDV && ptDV ) byLeadJetPtDV = true;
      if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts && m_histoInfoSwitch->m_ptVerts ) ) {
	DV .push_back( baseDV && byJetPtDV     );
	DV .push_back( baseDV && byLeadJetPtDV );
      }
      // --> by (leading) jets + min-d0 cut
      bool byJetMind0DV     = false;
      bool byLeadJetMind0DV = false;
      if ( byJetDV     && mind0DV ) byJetMind0DV     = true;
      if ( byLeadJetDV && mind0DV ) byLeadJetMind0DV = true;
      if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts && m_histoInfoSwitch->m_d0Verts ) ) {
	DV .push_back( baseDV && byJetMind0DV     );
	DV .push_back( baseDV && byLeadJetMind0DV );
      }
      // --> by (leading) jets + min-z0 cut
      bool byJetMinz0DV     = false;
      bool byLeadJetMinz0DV = false;
      if ( byJetDV     && minz0DV  ) byJetMinz0DV     = true;
      if ( byLeadJetDV && minz0DV  ) byLeadJetMinz0DV = true;
      if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts && m_histoInfoSwitch->m_z0Verts ) ) {
	DV .push_back( baseDV && byJetMinz0DV     );
	DV .push_back( baseDV && byLeadJetMinz0DV );
      }
      // --> fiducial + k-short-mass cuts
      bool fidKsmDV = false;
      if ( fiducDV && ksmDV ) fidKsmDV = true;
      if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_fiducialVerts && m_histoInfoSwitch->m_ksmVerts ) ) {
	DV .push_back( baseDV && fidKsmDV );
      }
      // --> by (leading) jets + fiducial and k-short-mass cuts
      bool byJetFidKsmDV     = false;
      bool byLeadJetFidKsmDV = false;
      if ( byJetDV     && fiducDV && ksmDV ) byJetFidKsmDV     = true;
      if ( byLeadJetDV && fiducDV && ksmDV ) byLeadJetFidKsmDV = true;
      if ( m_histoInfoSwitch->m_vertices || ( m_histoInfoSwitch->m_byJetVerts    &&
					      m_histoInfoSwitch->m_fiducialVerts && m_histoInfoSwitch->m_ksmVerts ) ) {
	DV .push_back( baseDV && byJetFidKsmDV     );
	DV .push_back( baseDV && byLeadJetFidKsmDV );
      }
      // --> eventually add further above individual cuts to these combinations after seeing impact on variables of interest...
      // --> don't forget to add to truth dv's as well


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
      	    if ( m_secVtx_truth_llp ->at(i)[itruth] == "DarkPion" ) darkPionDV = true;
      	    if ( m_secVtx_truth_llp ->at(i)[itruth] == "Kshort"   ) kshortDV   = true;
      	  }
      	}
      	if ( !darkPionDV && !kshortDV ) nomatchDV = true;
	if ( m_histoInfoSwitch->m_vtxTruth ) {
	  //std::vector<int> mDV = { darkPionDV,  kshortDV, nomatchDV };
	  std::vector<int> mDV = { darkPionDV };
	  std::vector<int> miDV;
	  for ( size_t idv = 0; idv != DV.size(); ++idv )
	    miDV .push_back( DV[idv] );
	  for ( size_t ii = 0; ii != mDV.size(); ++ii )
	    for ( size_t jj = 0; jj != miDV.size(); ++jj )
	      DV .push_back( baseDV && mDV[ii] && miDV[jj] );
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
	
      	if ( !DV[idv] ) continue;
	++n_DV[idv];

	int ntrk = secVtx_ntrk;
	if ( m_numVtxTrks ) {
	  if ( ntrk >= m_numVtxTrks ) ntrk = m_numVtxTrks;
	  ++n_ntrkDV[idv][ntrk];
	}

	const TVector3 secVtx_pos( m_secVtx_x ->at(i), m_secVtx_y ->at(i), m_secVtx_z ->at(i) );

	if ( !doHists ) continue;

	// distance to nearby jets
	if ( m_secVtx_jetMatched ->at(i) ) {
	  h_DV_jetDR       [ireg][idv] ->Fill( m_secVtx_jetMatch_dR ->at(i), weight );
	  // distance to nearby leading jets
	  if ( m_secVtx_jetMatch_index ->at(i) < m_nJets )
	    h_DV_leadJetDR [ireg][idv] ->Fill( m_secVtx_jetMatch_dR ->at(i), weight );
	}
	
      	h_DV_x         [ireg][idv] ->Fill( m_secVtx_x    ->at(i), weight );
      	h_DV_y         [ireg][idv] ->Fill( m_secVtx_y    ->at(i), weight );
      	h_DV_z         [ireg][idv] ->Fill( m_secVtx_z    ->at(i), weight );
      	h_DV_r         [ireg][idv] ->Fill( m_secVtx_r    ->at(i), weight );
	h_DV_x_s       [ireg][idv] ->Fill( m_secVtx_x    ->at(i), weight );
	h_DV_y_s       [ireg][idv] ->Fill( m_secVtx_y    ->at(i), weight );
	h_DV_z_s       [ireg][idv] ->Fill( m_secVtx_z    ->at(i), weight );
	h_DV_r_s       [ireg][idv] ->Fill( m_secVtx_r    ->at(i), weight );
	h_DV_phipos    [ireg][idv] ->Fill( secVtx_pos     .Phi(), weight );
	h_DV_pt        [ireg][idv] ->Fill( secVtx_pt,             weight );
	h_DV_pt_s      [ireg][idv] ->Fill( secVtx_pt,             weight );
	h_DV_pt_xs     [ireg][idv] ->Fill( secVtx_pt,             weight );
	h_DV_eta       [ireg][idv] ->Fill( secVtx_eta,            weight );
	h_DV_phi       [ireg][idv] ->Fill( secVtx_phi,            weight );
	h_DV_mass      [ireg][idv] ->Fill( secVtx_mass,           weight );
	h_DV_mass_l    [ireg][idv] ->Fill( secVtx_mass,           weight );
	h_DV_mass_s    [ireg][idv] ->Fill( secVtx_mass,           weight );
	h_DV_mass_xs   [ireg][idv] ->Fill( secVtx_mass,           weight );
	h_DV_massNA    [ireg][idv] ->Fill( secVtx_massNA,         weight );
	h_DV_massNA_l  [ireg][idv] ->Fill( secVtx_massNA,         weight );
	h_DV_massNA_s  [ireg][idv] ->Fill( secVtx_massNA,         weight );
	h_DV_massNA_xs [ireg][idv] ->Fill( secVtx_massNA,         weight );
	h_DV_direction [ireg][idv] ->Fill( secVtx_dir,            weight ); // cos-phi, phi = ang. b/w vtx pos + track sum-p4 vectors
	h_DV_minOpAng  [ireg][idv] ->Fill( secVtx_minOpAng,       weight ); // wrt SV
	h_DV_maxOpAng  [ireg][idv] ->Fill( secVtx_maxOpAng,       weight );
	h_DV_chi2      [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), weight );
	h_DV_chi2_s    [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), weight );
	h_DV_ntrk      [ireg][idv] ->Fill( secVtx_ntrk,           weight );
	// --> look at mass_selected (is this the same as non-associated? check), mass_LRT
	// --> --> need to calculate sumP4 using only tracks of interest

	// 2d plots
	if ( m_histoInfoSwitch->m_vtx2D ) {
	  h_DV_z_r         [ireg][idv] ->Fill( m_secVtx_r    ->at(i), m_secVtx_z    ->at(i), weight );
	  h_DV_mass_r      [ireg][idv] ->Fill( m_secVtx_r    ->at(i), m_secVtx_mass ->at(i), weight );
	  h_DV_z_chi2      [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_z    ->at(i), weight );
	  h_DV_r_chi2      [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_r    ->at(i), weight );
	  h_DV_mass_chi2   [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_mass ->at(i), weight );
	  h_DV_z_r_s       [ireg][idv] ->Fill( m_secVtx_r    ->at(i), m_secVtx_z    ->at(i), weight );
	  h_DV_mass_r_s    [ireg][idv] ->Fill( m_secVtx_r    ->at(i), m_secVtx_mass ->at(i), weight );
	  h_DV_z_chi2_s    [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_z    ->at(i), weight );
	  h_DV_r_chi2_s    [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_r    ->at(i), weight );
	  h_DV_mass_chi2_s [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_mass ->at(i), weight );
	}

	// squared errors --> DOUBLE CHECK ERROR PROPAGATIONS FOR R, PHI...
	float secVtx_x2     = pow( m_secVtx_x ->at(i), 2 );
	float secVtx_y2     = pow( m_secVtx_y ->at(i), 2 );
	float secVtx_r2     = pow( m_secVtx_r ->at(i), 2 );
	float secVtx_xy     = m_secVtx_x ->at(i) * m_secVtx_y ->at(i);
	float secVtx_errx   = m_secVtx_covariance ->at(i)[0];
	float secVtx_errxy  = m_secVtx_covariance ->at(i)[1]; // xz=3, xz=4
	float secVtx_erry   = m_secVtx_covariance ->at(i)[2];
	float secVtx_errz   = m_secVtx_covariance ->at(i)[5];
	float secVtx_errr   = ( secVtx_x2 * secVtx_errx + secVtx_y2 * secVtx_erry + 2 * secVtx_xy * secVtx_errxy ) / secVtx_r2;
	float secVtx_errphi = ( secVtx_y2 * secVtx_errx + secVtx_x2 * secVtx_erry - 2 * secVtx_xy * secVtx_errxy ) / pow( secVtx_r2, 2 );
	if ( m_histoInfoSwitch->m_vtxErrors ) {
	  h_DV_errx             [ireg][idv] ->Fill( sqrt(secVtx_errx),                                    weight );
	  h_DV_erry             [ireg][idv] ->Fill( sqrt(secVtx_erry),                                    weight );
	  h_DV_errz             [ireg][idv] ->Fill( sqrt(secVtx_errz),                                    weight );
	  h_DV_errr             [ireg][idv] ->Fill( sqrt(secVtx_errr),                                    weight );
	  h_DV_errphi           [ireg][idv] ->Fill( sqrt(secVtx_errphi),                                  weight );
	  h_DV_sqrterrx         [ireg][idv] ->Fill( sqrt(sqrt(secVtx_errx)),                              weight );
	  h_DV_sqrterry         [ireg][idv] ->Fill( sqrt(sqrt(secVtx_erry)),                              weight );
	  h_DV_sqrterrz         [ireg][idv] ->Fill( sqrt(sqrt(secVtx_errz)),                              weight );
	  h_DV_sqrterrr         [ireg][idv] ->Fill( sqrt(sqrt(secVtx_errr)),                              weight );
	  h_DV_sqrterrphi       [ireg][idv] ->Fill( sqrt(sqrt(secVtx_errphi)),                            weight );
	  h_DV_fracerrx         [ireg][idv] ->Fill( sqrt(secVtx_errx)        / fabs(m_secVtx_x ->at(i)),  weight );
	  h_DV_fracerry         [ireg][idv] ->Fill( sqrt(secVtx_erry)        / fabs(m_secVtx_y ->at(i)),  weight );
	  h_DV_fracerrz         [ireg][idv] ->Fill( sqrt(secVtx_errz)        / fabs(m_secVtx_z ->at(i)),  weight );
	  h_DV_fracerrr         [ireg][idv] ->Fill( sqrt(secVtx_errr)        / fabs(m_secVtx_r ->at(i)),  weight );
	  h_DV_fracerrphi       [ireg][idv] ->Fill( sqrt(secVtx_errphi)      / fabs(secVtx_pos  .Phi()),  weight );
	  h_DV_signifx          [ireg][idv] ->Fill( fabs(m_secVtx_x ->at(i)) / sqrt(secVtx_errx),         weight );
	  h_DV_signify          [ireg][idv] ->Fill( fabs(m_secVtx_y ->at(i)) / sqrt(secVtx_erry),         weight );
	  h_DV_signifz          [ireg][idv] ->Fill( fabs(m_secVtx_z ->at(i)) / sqrt(secVtx_errz),         weight );
	  h_DV_signifr          [ireg][idv] ->Fill( fabs(m_secVtx_r ->at(i)) / sqrt(secVtx_errr),         weight );
	  h_DV_signifphi        [ireg][idv] ->Fill( fabs(secVtx_pos  .Phi()) / sqrt(secVtx_errphi),       weight );
	  // --> 2d
	  if ( m_histoInfoSwitch->m_vtx2D ) {
	    h_DV_errx_x         [ireg][idv] ->Fill( m_secVtx_x ->at(i),        sqrt(secVtx_errx),         weight );
	    h_DV_erry_y         [ireg][idv] ->Fill( m_secVtx_y ->at(i),        sqrt(secVtx_erry),         weight );
	    h_DV_errz_z         [ireg][idv] ->Fill( m_secVtx_z ->at(i),        sqrt(secVtx_errz),         weight );
	    h_DV_errr_r         [ireg][idv] ->Fill( m_secVtx_r ->at(i),        sqrt(secVtx_errr),         weight );
	    h_DV_errphi_phi     [ireg][idv] ->Fill( secVtx_pos  .Phi(),        sqrt(secVtx_errphi),       weight );
	    h_DV_sqrterrx_x     [ireg][idv] ->Fill( m_secVtx_x ->at(i),        sqrt(sqrt(secVtx_errx)),   weight );
	    h_DV_sqrterry_y     [ireg][idv] ->Fill( m_secVtx_y ->at(i),        sqrt(sqrt(secVtx_erry)),   weight );
	    h_DV_sqrterrz_z     [ireg][idv] ->Fill( m_secVtx_z ->at(i),        sqrt(sqrt(secVtx_errz)),   weight );
	    h_DV_sqrterrr_r     [ireg][idv] ->Fill( m_secVtx_r ->at(i),        sqrt(sqrt(secVtx_errr)),   weight );
	    h_DV_sqrterrphi_phi [ireg][idv] ->Fill( secVtx_pos  .Phi(),        sqrt(sqrt(secVtx_errphi)), weight );
	  }
	}

	// loop over vertex tracks
	for ( int j = 0; j != m_secVtx_ntrk ->at(i); ++j ) {
	  if ( base_dv.type == EJsHelper::CLEAN    && !m_secVtx_trk_isClean ->at(i)[j] ) continue;
	  if ( base_dv.type == EJsHelper::FILTERED && !m_secVtx_trk_isFilt  ->at(i)[j] ) continue;
	  // if ( base_dv.type == EJsHelper::TRIMMED && *track fails trimming cuts* ) continue;

	  int trkIx = m_secVtx_trk_index ->at(i)[j];

	  float trk_theta_sv  = 2 * atan( exp( -1 * m_secVtx_trk_eta_sv ->at(i)[j] ) ); // eta = -ln(tan(theta/2))
	  float trk_p_sv      = m_secVtx_trk_pt_sv ->at(i)[j] / sin( trk_theta_sv );    // pt  =  p*sin(theta)
	  float trk_qOverP_sv = m_trk_charge ->at(trkIx) / trk_p_sv;
	  float trk_chi2_sv   = m_secVtx_trk_chi2_sv ->at(i)[j] / m_trk_ndof ->at(trkIx);

	  // squared errors
	  float trk_errd0    = m_trk_errd0           ->at(trkIx);
	  float trk_errz0    = m_trk_errz0           ->at(trkIx);
	  float trk_errP     = m_trk_errP            ->at(trkIx) * 1e6;
	  float trk_errd0_sv = m_secVtx_trk_errd0_sv ->at(i)[j];
	  float trk_errz0_sv = m_secVtx_trk_errz0_sv ->at(i)[j];
	  float trk_errP_sv  = m_secVtx_trk_errP_sv  ->at(i)[j] * 1e6;
	  // squared fractional errors
	  float trk_fracerrd0    = trk_errd0    / pow(m_trk_d0           ->at(trkIx),        2);
	  float trk_fracerrz0    = trk_errz0    / pow(m_trk_z0           ->at(trkIx),        2);
	  float trk_fracerrP     = trk_errP     / pow(m_trk_qOverP       ->at(trkIx) * 1000, 2);
	  float trk_fracerrd0_sv = trk_errd0_sv / pow(m_secVtx_trk_d0_sv ->at(i)[j],         2);
	  float trk_fracerrz0_sv = trk_errz0_sv / pow(m_secVtx_trk_z0_sv ->at(i)[j],         2);
	  float trk_fracerrP_sv  = trk_errP_sv  / pow(trk_qOverP_sv,                         2);
	  
	  if ( m_histoInfoSwitch->m_vtxTrks ) {
	    h_DV_trk_qOverP        [ireg][idv] ->Fill( 1000 * m_trk_qOverP  ->at(trkIx), weight );
	    h_DV_trk_theta         [ireg][idv] ->Fill( m_trk_theta          ->at(trkIx), weight );
	    h_DV_trk_pt            [ireg][idv] ->Fill( m_trk_pt             ->at(trkIx), weight );
	    h_DV_trk_eta           [ireg][idv] ->Fill( m_trk_eta            ->at(trkIx), weight );
	    h_DV_trk_phi           [ireg][idv] ->Fill( m_trk_phi            ->at(trkIx), weight );
	    h_DV_trk_d0            [ireg][idv] ->Fill( m_trk_d0             ->at(trkIx), weight );
	    h_DV_trk_d0_xs         [ireg][idv] ->Fill( m_trk_d0             ->at(trkIx), weight );
	    h_DV_trk_z0            [ireg][idv] ->Fill( m_trk_z0             ->at(trkIx), weight );
	    h_DV_trk_errd0         [ireg][idv] ->Fill( sqrt(trk_errd0),                  weight );
	    h_DV_trk_errz0         [ireg][idv] ->Fill( sqrt(trk_errz0),                  weight );
	    h_DV_trk_sqrterrd0     [ireg][idv] ->Fill( sqrt(sqrt(trk_errd0)),            weight );
	    h_DV_trk_sqrterrz0     [ireg][idv] ->Fill( sqrt(sqrt(trk_errz0)),            weight );
	    h_DV_trk_fracerrd0     [ireg][idv] ->Fill( sqrt(trk_fracerrd0),              weight );
	    h_DV_trk_fracerrz0     [ireg][idv] ->Fill( sqrt(trk_fracerrz0),              weight );
	    h_DV_trk_signifd0      [ireg][idv] ->Fill( 1/sqrt(trk_fracerrd0),            weight );
	    h_DV_trk_signifz0      [ireg][idv] ->Fill( 1/sqrt(trk_fracerrz0),            weight );
	    h_DV_trk_errP          [ireg][idv] ->Fill( sqrt(trk_errP),                   weight );
	    h_DV_trk_sqrterrP      [ireg][idv] ->Fill( sqrt(sqrt(trk_errP)),             weight );
	    h_DV_trk_fracerrP      [ireg][idv] ->Fill( sqrt(trk_fracerrP),               weight );
	    h_DV_trk_signifP       [ireg][idv] ->Fill( 1/sqrt(trk_fracerrP),             weight );
	    h_DV_trk_chi2          [ireg][idv] ->Fill( m_trk_chi2           ->at(trkIx), weight );
	    h_DV_trk_chiSq         [ireg][idv] ->Fill( m_trk_chiSq          ->at(trkIx), weight );
	    h_DV_trk_qOverP_sv     [ireg][idv] ->Fill( trk_qOverP_sv,                    weight );
	    h_DV_trk_theta_sv      [ireg][idv] ->Fill( trk_theta_sv,                     weight );
	    h_DV_trk_pt_sv         [ireg][idv] ->Fill( m_secVtx_trk_pt_sv   ->at(i)[j],  weight );
	    h_DV_trk_eta_sv        [ireg][idv] ->Fill( m_secVtx_trk_eta_sv  ->at(i)[j],  weight );
	    h_DV_trk_phi_sv        [ireg][idv] ->Fill( m_secVtx_trk_phi_sv  ->at(i)[j],  weight );
	    h_DV_trk_d0_sv         [ireg][idv] ->Fill( m_secVtx_trk_d0_sv   ->at(i)[j],  weight );
	    h_DV_trk_z0_sv         [ireg][idv] ->Fill( m_secVtx_trk_z0_sv   ->at(i)[j],  weight );
	    h_DV_trk_errd0_sv      [ireg][idv] ->Fill( sqrt(trk_errd0_sv),               weight );
	    h_DV_trk_errz0_sv      [ireg][idv] ->Fill( sqrt(trk_errz0_sv),               weight );
	    h_DV_trk_sqrterrd0_sv  [ireg][idv] ->Fill( sqrt(sqrt(trk_errd0_sv)),         weight );
	    h_DV_trk_sqrterrz0_sv  [ireg][idv] ->Fill( sqrt(sqrt(trk_errz0_sv)),         weight );
	    h_DV_trk_fracerrd0_sv  [ireg][idv] ->Fill( sqrt(trk_fracerrd0_sv),           weight );
	    h_DV_trk_fracerrz0_sv  [ireg][idv] ->Fill( sqrt(trk_fracerrz0_sv),           weight );
	    h_DV_trk_signifd0_sv   [ireg][idv] ->Fill( 1/sqrt(trk_fracerrd0_sv),         weight );
	    h_DV_trk_signifz0_sv   [ireg][idv] ->Fill( 1/sqrt(trk_fracerrz0_sv),         weight );
	    h_DV_trk_errP_sv       [ireg][idv] ->Fill( sqrt(trk_errP_sv),                weight );
	    h_DV_trk_sqrterrP_sv   [ireg][idv] ->Fill( sqrt(sqrt(trk_errP_sv)),          weight );
	    h_DV_trk_fracerrP_sv   [ireg][idv] ->Fill( sqrt(trk_fracerrP_sv),            weight );
	    h_DV_trk_signifP_sv    [ireg][idv] ->Fill( 1/sqrt(trk_fracerrP_sv),          weight );
	    h_DV_trk_chi2_sv       [ireg][idv] ->Fill( trk_chi2_sv,                      weight );
	    h_DV_trk_chiSq_sv      [ireg][idv] ->Fill( m_secVtx_trk_chi2_sv ->at(i)[j],  weight );
	    // selected tracks
	    if ( m_secVtx_trk_isSel ->at(i)[j] ) {
	      h_DV_seltrk_d0       [ireg][idv] ->Fill( m_trk_d0             ->at(trkIx),   weight );
	      h_DV_seltrk_d0_xs    [ireg][idv] ->Fill( m_trk_d0             ->at(trkIx),   weight );
	    }
	  }

	  if ( m_histoInfoSwitch->m_vtx2D && m_histoInfoSwitch->m_vtxTrks ) {
	    h_DV_trkd0_r          [ireg][idv] ->Fill( m_secVtx_r ->at(i), m_trk_d0            ->at(trkIx), weight );
	    h_DV_trkz0_z          [ireg][idv] ->Fill( m_secVtx_z ->at(i), m_trk_z0            ->at(trkIx), weight );
	    h_DV_trkP_pt          [ireg][idv] ->Fill( secVtx_pt,          1000 * m_trk_qOverP ->at(trkIx), weight );
	    h_DV_trkErrd0_r       [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(trk_errd0),                 weight );
	    h_DV_trkErrz0_z       [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(trk_errz0),                 weight );
	    h_DV_trkErrP_pt       [ireg][idv] ->Fill( secVtx_pt,          sqrt(trk_errP),                  weight );
	    h_DV_trkSqrterrd0_r   [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(trk_errd0)),           weight );
	    h_DV_trkSqrterrz0_z   [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(trk_errz0)),           weight );
	    h_DV_trkSqrterrP_pt   [ireg][idv] ->Fill( secVtx_pt,          sqrt(sqrt(trk_errP)),            weight );
	    h_DV_trkd0sv_r        [ireg][idv] ->Fill( m_secVtx_r ->at(i), m_secVtx_trk_d0_sv ->at(i)[j],   weight );
	    h_DV_trkz0sv_z        [ireg][idv] ->Fill( m_secVtx_z ->at(i), m_secVtx_trk_z0_sv ->at(i)[j],   weight );
	    h_DV_trkPsv_pt        [ireg][idv] ->Fill( secVtx_pt,          trk_qOverP_sv,                   weight );
	    h_DV_trkErrd0sv_r     [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(trk_errd0_sv),              weight );
	    h_DV_trkErrz0sv_z     [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(trk_errz0_sv),              weight );
	    h_DV_trkErrPsv_pt     [ireg][idv] ->Fill( secVtx_pt,          sqrt(trk_errP_sv),               weight );
	    h_DV_trkSqrterrd0sv_r [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(trk_errd0_sv)),        weight );
	    h_DV_trkSqrterrz0sv_z [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(trk_errz0_sv)),        weight );
	    h_DV_trkSqrterrPsv_pt [ireg][idv] ->Fill( secVtx_pt,          sqrt(sqrt(trk_errP_sv)),         weight );

	    h_DV_trkErrd0_trkd0         [ireg][idv] ->Fill( m_trk_d0            ->at(trkIx), sqrt(trk_errd0),          weight );
	    h_DV_trkErrz0_trkz0         [ireg][idv] ->Fill( m_trk_z0            ->at(trkIx), sqrt(trk_errz0),          weight );
	    h_DV_trkErrP_trkP           [ireg][idv] ->Fill( 1000 * m_trk_qOverP ->at(trkIx), sqrt(trk_errP),           weight );
	    h_DV_trkSqrterrd0_trkd0     [ireg][idv] ->Fill( m_trk_d0            ->at(trkIx), sqrt(sqrt(trk_errd0)),    weight );
	    h_DV_trkSqrterrz0_trkz0     [ireg][idv] ->Fill( m_trk_z0            ->at(trkIx), sqrt(sqrt(trk_errz0)),    weight );
	    h_DV_trkSqrterrP_trkP       [ireg][idv] ->Fill( 1000 * m_trk_qOverP ->at(trkIx), sqrt(sqrt(trk_errP)),     weight );
	    h_DV_trkErrd0sv_trkd0sv     [ireg][idv] ->Fill( m_secVtx_trk_d0_sv  ->at(i)[j],  sqrt(trk_errd0_sv),       weight );
	    h_DV_trkErrz0sv_trkz0sv     [ireg][idv] ->Fill( m_secVtx_trk_z0_sv  ->at(i)[j],  sqrt(trk_errz0_sv),       weight );
	    h_DV_trkErrPsv_trkPsv       [ireg][idv] ->Fill( trk_qOverP_sv,                   sqrt(trk_errP),           weight );
	    h_DV_trkSqrterrd0sv_trkd0sv [ireg][idv] ->Fill( m_secVtx_trk_d0_sv  ->at(i)[j],  sqrt(sqrt(trk_errd0_sv)), weight );
	    h_DV_trkSqrterrz0sv_trkz0sv [ireg][idv] ->Fill( m_secVtx_trk_z0_sv  ->at(i)[j],  sqrt(sqrt(trk_errz0_sv)), weight );
	    h_DV_trkSqrterrPsv_trkPsv   [ireg][idv] ->Fill( trk_qOverP_sv,                   sqrt(sqrt(trk_errP)),     weight );
	  }
	  
	} // end loop over tracks

	h_DV_ntrk_final [ireg][idv] ->Fill( secVtx_ntrk_final, weight );
	h_DV_ntrk_sel   [ireg][idv] ->Fill( secVtx_ntrk_sel,   weight );
	h_DV_ntrk_assoc [ireg][idv] ->Fill( secVtx_ntrk_assoc, weight );
	h_DV_ntrk_lrt   [ireg][idv] ->Fill( secVtx_ntrk_lrt,   weight );
	h_DV_ntrk_d0    [ireg][idv] ->Fill( secVtx_ntrk_d0,    weight );
	h_DV_ntrk_seld0 [ireg][idv] ->Fill( secVtx_ntrk_seld0, weight );
	
	h_DV_sumd0             [ireg][idv] ->Fill( secVtx_sumd0,                   weight );
	h_DV_sumz0             [ireg][idv] ->Fill( secVtx_sumz0,                   weight );
	h_DV_sumP              [ireg][idv] ->Fill( secVtx_sumP,                    weight );
	h_DV_sumd0_sv          [ireg][idv] ->Fill( secVtx_sumd0_sv,                weight );
	h_DV_sumz0_sv          [ireg][idv] ->Fill( secVtx_sumz0_sv,                weight );
	h_DV_sumP_sv           [ireg][idv] ->Fill( secVtx_sumP_sv,                 weight );
	h_DV_sumsqrtd0         [ireg][idv] ->Fill( sqrt(secVtx_sumd0),             weight );
	h_DV_sumsqrtz0         [ireg][idv] ->Fill( sqrt(secVtx_sumz0),             weight );
	h_DV_sumsqrtP          [ireg][idv] ->Fill( sqrt(secVtx_sumP),              weight );
	h_DV_sumsqrtd0_sv      [ireg][idv] ->Fill( sqrt(secVtx_sumd0_sv),          weight );
	h_DV_sumsqrtz0_sv      [ireg][idv] ->Fill( sqrt(secVtx_sumz0_sv),          weight );
	h_DV_sumsqrtP_sv       [ireg][idv] ->Fill( sqrt(secVtx_sumP_sv),           weight );
	h_DV_mind0             [ireg][idv] ->Fill( secVtx_mind0,                   weight );
	h_DV_minz0             [ireg][idv] ->Fill( secVtx_minz0,                   weight );
	h_DV_minP              [ireg][idv] ->Fill( secVtx_minP,                    weight );
	h_DV_mind0_sv          [ireg][idv] ->Fill( secVtx_mind0_sv,                weight );
	h_DV_minz0_sv          [ireg][idv] ->Fill( secVtx_minz0_sv,                weight );
	h_DV_minP_sv           [ireg][idv] ->Fill( secVtx_minP_sv,                 weight );
	h_DV_minsqrtd0         [ireg][idv] ->Fill( sqrt(secVtx_mind0),             weight );
	h_DV_minsqrtz0         [ireg][idv] ->Fill( sqrt(secVtx_minz0),             weight );
	h_DV_minsqrtP          [ireg][idv] ->Fill( sqrt(secVtx_minP),              weight );
	h_DV_minsqrtd0_sv      [ireg][idv] ->Fill( sqrt(secVtx_mind0_sv),          weight );
	h_DV_minsqrtz0_sv      [ireg][idv] ->Fill( sqrt(secVtx_minz0_sv),          weight );
	h_DV_minsqrtP_sv       [ireg][idv] ->Fill( sqrt(secVtx_minP_sv),           weight );
	h_DV_maxd0             [ireg][idv] ->Fill( secVtx_maxd0,                   weight );
	h_DV_maxz0             [ireg][idv] ->Fill( secVtx_maxz0,                   weight );
	h_DV_maxP              [ireg][idv] ->Fill( secVtx_maxP,                    weight );
	h_DV_maxd0_sv          [ireg][idv] ->Fill( secVtx_maxd0_sv,                weight );
	h_DV_maxz0_sv          [ireg][idv] ->Fill( secVtx_maxz0_sv,                weight );
	h_DV_maxP_sv           [ireg][idv] ->Fill( secVtx_maxP_sv,                 weight );
	h_DV_maxsqrtd0         [ireg][idv] ->Fill( sqrt(secVtx_maxd0),             weight );
	h_DV_maxsqrtz0         [ireg][idv] ->Fill( sqrt(secVtx_maxz0),             weight );
	h_DV_maxsqrtP          [ireg][idv] ->Fill( sqrt(secVtx_maxP),              weight );
	h_DV_maxsqrtd0_sv      [ireg][idv] ->Fill( sqrt(secVtx_maxd0_sv),          weight );
	h_DV_maxsqrtz0_sv      [ireg][idv] ->Fill( sqrt(secVtx_maxz0_sv),          weight );
	h_DV_maxsqrtP_sv       [ireg][idv] ->Fill( sqrt(secVtx_maxP_sv),           weight );
	if ( m_histoInfoSwitch->m_vtxErrors ) {
	  h_DV_sumErrd0        [ireg][idv] ->Fill( sqrt(secVtx_sumerrd0),          weight );
	  h_DV_sumErrz0        [ireg][idv] ->Fill( sqrt(secVtx_sumerrz0),          weight );
	  h_DV_sumErrP         [ireg][idv] ->Fill( sqrt(secVtx_sumerrP),           weight );
	  h_DV_sumSqrterrd0    [ireg][idv] ->Fill( sqrt(sqrt(secVtx_sumerrd0)),    weight );
	  h_DV_sumSqrterrz0    [ireg][idv] ->Fill( sqrt(sqrt(secVtx_sumerrz0)),    weight );
	  h_DV_sumSqrterrP     [ireg][idv] ->Fill( sqrt(sqrt(secVtx_sumerrP)),     weight );
	  h_DV_sumFracerrd0    [ireg][idv] ->Fill( sqrt(secVtx_sumfracerrd0),      weight );
	  h_DV_sumFracerrz0    [ireg][idv] ->Fill( sqrt(secVtx_sumfracerrz0),      weight );
	  h_DV_sumFracerrP     [ireg][idv] ->Fill( sqrt(secVtx_sumfracerrP),       weight );
	  h_DV_sumSignifd0     [ireg][idv] ->Fill( sqrt(secVtx_sumsignifd0),       weight );
	  h_DV_sumSignifz0     [ireg][idv] ->Fill( sqrt(secVtx_sumsignifz0),       weight );
	  h_DV_sumSignifP      [ireg][idv] ->Fill( sqrt(secVtx_sumsignifP),        weight );
	  h_DV_sumErrd0_sv     [ireg][idv] ->Fill( sqrt(secVtx_sumerrd0_sv),       weight );
	  h_DV_sumErrz0_sv     [ireg][idv] ->Fill( sqrt(secVtx_sumerrz0_sv),       weight );
	  h_DV_sumErrP_sv      [ireg][idv] ->Fill( sqrt(secVtx_sumerrP_sv),        weight );
	  h_DV_sumSqrterrd0_sv [ireg][idv] ->Fill( sqrt(sqrt(secVtx_sumerrd0_sv)), weight );
	  h_DV_sumSqrterrz0_sv [ireg][idv] ->Fill( sqrt(sqrt(secVtx_sumerrz0_sv)), weight );
	  h_DV_sumSqrterrP_sv  [ireg][idv] ->Fill( sqrt(sqrt(secVtx_sumerrP_sv)),  weight );
	  h_DV_sumFracerrd0_sv [ireg][idv] ->Fill( sqrt(secVtx_sumfracerrd0_sv),   weight );
	  h_DV_sumFracerrz0_sv [ireg][idv] ->Fill( sqrt(secVtx_sumfracerrz0_sv),   weight );
	  h_DV_sumFracerrP_sv  [ireg][idv] ->Fill( sqrt(secVtx_sumfracerrP_sv),    weight );
	  h_DV_sumSignifd0_sv  [ireg][idv] ->Fill( sqrt(secVtx_sumsignifd0_sv),    weight );
	  h_DV_sumSignifz0_sv  [ireg][idv] ->Fill( sqrt(secVtx_sumsignifz0_sv),    weight );
	  h_DV_sumSignifP_sv   [ireg][idv] ->Fill( sqrt(secVtx_sumsignifP_sv),     weight );

	  h_DV_minErrd0        [ireg][idv] ->Fill( sqrt(secVtx_minerrd0),          weight );
	  h_DV_minErrz0        [ireg][idv] ->Fill( sqrt(secVtx_minerrz0),          weight );
	  h_DV_minErrP         [ireg][idv] ->Fill( sqrt(secVtx_minerrP),           weight );
	  h_DV_minSqrterrd0    [ireg][idv] ->Fill( sqrt(sqrt(secVtx_minerrd0)),    weight );
	  h_DV_minSqrterrz0    [ireg][idv] ->Fill( sqrt(sqrt(secVtx_minerrz0)),    weight );
	  h_DV_minSqrterrP     [ireg][idv] ->Fill( sqrt(sqrt(secVtx_minerrP)),     weight );
	  h_DV_minFracerrd0    [ireg][idv] ->Fill( sqrt(secVtx_minfracerrd0),      weight );
	  h_DV_minFracerrz0    [ireg][idv] ->Fill( sqrt(secVtx_minfracerrz0),      weight );
	  h_DV_minFracerrP     [ireg][idv] ->Fill( sqrt(secVtx_minfracerrP),       weight );
	  h_DV_minSignifd0     [ireg][idv] ->Fill( sqrt(secVtx_minsignifd0),       weight );
	  h_DV_minSignifz0     [ireg][idv] ->Fill( sqrt(secVtx_minsignifz0),       weight );
	  h_DV_minSignifP      [ireg][idv] ->Fill( sqrt(secVtx_minsignifP),        weight );
	  h_DV_minErrd0_sv     [ireg][idv] ->Fill( sqrt(secVtx_minerrd0_sv),       weight );
	  h_DV_minErrz0_sv     [ireg][idv] ->Fill( sqrt(secVtx_minerrz0_sv),       weight );
	  h_DV_minErrP_sv      [ireg][idv] ->Fill( sqrt(secVtx_minerrP_sv),        weight );
	  h_DV_minSqrterrd0_sv [ireg][idv] ->Fill( sqrt(sqrt(secVtx_minerrd0_sv)), weight );
	  h_DV_minSqrterrz0_sv [ireg][idv] ->Fill( sqrt(sqrt(secVtx_minerrz0_sv)), weight );
	  h_DV_minSqrterrP_sv  [ireg][idv] ->Fill( sqrt(sqrt(secVtx_minerrP_sv)),  weight );
	  h_DV_minFracerrd0_sv [ireg][idv] ->Fill( sqrt(secVtx_minfracerrd0_sv),   weight );
	  h_DV_minFracerrz0_sv [ireg][idv] ->Fill( sqrt(secVtx_minfracerrz0_sv),   weight );
	  h_DV_minFracerrP_sv  [ireg][idv] ->Fill( sqrt(secVtx_minfracerrP_sv),    weight );
	  h_DV_minSignifd0_sv  [ireg][idv] ->Fill( sqrt(secVtx_minsignifd0_sv),    weight );
	  h_DV_minSignifz0_sv  [ireg][idv] ->Fill( sqrt(secVtx_minsignifz0_sv),    weight );
	  h_DV_minSignifP_sv   [ireg][idv] ->Fill( sqrt(secVtx_minsignifP_sv),     weight );

	  h_DV_maxErrd0        [ireg][idv] ->Fill( sqrt(secVtx_maxerrd0),          weight );
	  h_DV_maxErrz0        [ireg][idv] ->Fill( sqrt(secVtx_maxerrz0),          weight );
	  h_DV_maxErrP         [ireg][idv] ->Fill( sqrt(secVtx_maxerrP),           weight );
	  h_DV_maxSqrterrd0    [ireg][idv] ->Fill( sqrt(sqrt(secVtx_maxerrd0)),    weight );
	  h_DV_maxSqrterrz0    [ireg][idv] ->Fill( sqrt(sqrt(secVtx_maxerrz0)),    weight );
	  h_DV_maxSqrterrP     [ireg][idv] ->Fill( sqrt(sqrt(secVtx_maxerrP)),     weight );
	  h_DV_maxFracerrd0    [ireg][idv] ->Fill( sqrt(secVtx_maxfracerrd0),      weight );
	  h_DV_maxFracerrz0    [ireg][idv] ->Fill( sqrt(secVtx_maxfracerrz0),      weight );
	  h_DV_maxFracerrP     [ireg][idv] ->Fill( sqrt(secVtx_maxfracerrP),       weight );
	  h_DV_maxSignifd0     [ireg][idv] ->Fill( sqrt(secVtx_maxsignifd0),       weight );
	  h_DV_maxSignifz0     [ireg][idv] ->Fill( sqrt(secVtx_maxsignifz0),       weight );
	  h_DV_maxSignifP      [ireg][idv] ->Fill( sqrt(secVtx_maxsignifP),        weight );
	  h_DV_maxErrd0_sv     [ireg][idv] ->Fill( sqrt(secVtx_maxerrd0_sv),       weight );
	  h_DV_maxErrz0_sv     [ireg][idv] ->Fill( sqrt(secVtx_maxerrz0_sv),       weight );
	  h_DV_maxErrP_sv      [ireg][idv] ->Fill( sqrt(secVtx_maxerrP_sv),        weight );
	  h_DV_maxSqrterrd0_sv [ireg][idv] ->Fill( sqrt(sqrt(secVtx_maxerrd0_sv)), weight );
	  h_DV_maxSqrterrz0_sv [ireg][idv] ->Fill( sqrt(sqrt(secVtx_maxerrz0_sv)), weight );
	  h_DV_maxSqrterrP_sv  [ireg][idv] ->Fill( sqrt(sqrt(secVtx_maxerrP_sv)),  weight );
	  h_DV_maxFracerrd0_sv [ireg][idv] ->Fill( sqrt(secVtx_maxfracerrd0_sv),   weight );
	  h_DV_maxFracerrz0_sv [ireg][idv] ->Fill( sqrt(secVtx_maxfracerrz0_sv),   weight );
	  h_DV_maxFracerrP_sv  [ireg][idv] ->Fill( sqrt(secVtx_maxfracerrP_sv),    weight );
	  h_DV_maxSignifd0_sv  [ireg][idv] ->Fill( sqrt(secVtx_maxsignifd0_sv),    weight );
	  h_DV_maxSignifz0_sv  [ireg][idv] ->Fill( sqrt(secVtx_maxsignifz0_sv),    weight );
	  h_DV_maxSignifP_sv   [ireg][idv] ->Fill( sqrt(secVtx_maxsignifP_sv),     weight );
	}

	// 2d plots
	if ( m_histoInfoSwitch->m_vtx2D && m_histoInfoSwitch->m_vtxErrors ) {
	  h_DV_sumErrd0_r       [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_sumerrd0),          weight );
	  h_DV_sumErrz0_z       [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_sumerrz0),          weight );
	  h_DV_sumErrP_pt       [ireg][idv] ->Fill( secVtx_pt,          sqrt(secVtx_sumerrP),           weight );
	  h_DV_sumSqrterrd0_r   [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_sumerrd0)),    weight );
	  h_DV_sumSqrterrz0_z   [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_sumerrz0)),    weight );
	  h_DV_sumSqrterrP_pt   [ireg][idv] ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_sumerrP)),     weight );
	  h_DV_sumErrd0sv_r     [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_sumerrd0_sv),       weight );
	  h_DV_sumErrz0sv_z     [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_sumerrz0_sv),       weight );
	  h_DV_sumErrPsv_pt     [ireg][idv] ->Fill( secVtx_pt,          sqrt(secVtx_sumerrP_sv),        weight );
	  h_DV_sumSqrterrd0sv_r [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_sumerrd0_sv)), weight );
	  h_DV_sumSqrterrz0sv_z [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_sumerrz0_sv)), weight );
	  h_DV_sumSqrterrPsv_pt [ireg][idv] ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_sumerrP_sv)),  weight );

	  h_DV_minErrd0_r       [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_minerrd0),          weight );
	  h_DV_minErrz0_z       [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_minerrz0),          weight );
	  h_DV_minErrP_pt       [ireg][idv] ->Fill( secVtx_pt,          sqrt(secVtx_minerrP),           weight );
	  h_DV_minSqrterrd0_r   [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_minerrd0)),    weight );
	  h_DV_minSqrterrz0_z   [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_minerrz0)),    weight );
	  h_DV_minSqrterrP_pt   [ireg][idv] ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_minerrP)),     weight );
	  h_DV_minErrd0sv_r     [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_minerrd0_sv),       weight );
	  h_DV_minErrz0sv_z     [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_minerrz0_sv),       weight );
	  h_DV_minErrPsv_pt     [ireg][idv] ->Fill( secVtx_pt,          sqrt(secVtx_minerrP_sv),        weight );
	  h_DV_minSqrterrd0sv_r [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_minerrd0_sv)), weight );
	  h_DV_minSqrterrz0sv_z [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_minerrz0_sv)), weight );
	  h_DV_minSqrterrPsv_pt [ireg][idv] ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_minerrP_sv)),  weight );

	  h_DV_maxErrd0_r       [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_maxerrd0),          weight );
	  h_DV_maxErrz0_z       [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_maxerrz0),          weight );
	  h_DV_maxErrP_pt       [ireg][idv] ->Fill( secVtx_pt,          sqrt(secVtx_maxerrP),           weight );
	  h_DV_maxSqrterrd0_r   [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_maxerrd0)),    weight );
	  h_DV_maxSqrterrz0_z   [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_maxerrz0)),    weight );
	  h_DV_maxSqrterrP_pt   [ireg][idv] ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_maxerrP)),     weight );
	  h_DV_maxErrd0sv_r     [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(secVtx_maxerrd0_sv),       weight );
	  h_DV_maxErrz0sv_z     [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(secVtx_maxerrz0_sv),       weight );
	  h_DV_maxErrPsv_pt     [ireg][idv] ->Fill( secVtx_pt,          sqrt(secVtx_maxerrP_sv),        weight );
	  h_DV_maxSqrterrd0sv_r [ireg][idv] ->Fill( m_secVtx_r ->at(i), sqrt(sqrt(secVtx_maxerrd0_sv)), weight );
	  h_DV_maxSqrterrz0sv_z [ireg][idv] ->Fill( m_secVtx_z ->at(i), sqrt(sqrt(secVtx_maxerrz0_sv)), weight );
	  h_DV_maxSqrterrPsv_pt [ireg][idv] ->Fill( secVtx_pt,          sqrt(sqrt(secVtx_maxerrP_sv)),  weight );
	}

	// n-track vertices
	if ( m_numVtxTrks ) {
	  h_ntrkDV_z                 [ireg][idv][ntrk-2]->Fill( m_secVtx_z ->at(i),             weight );
	  h_ntrkDV_z_s               [ireg][idv][ntrk-2]->Fill( m_secVtx_z ->at(i),             weight );
	  h_ntrkDV_r                 [ireg][idv][ntrk-2]->Fill( m_secVtx_r ->at(i),             weight );
	  h_ntrkDV_r_s               [ireg][idv][ntrk-2]->Fill( m_secVtx_r ->at(i),             weight );
	  h_ntrkDV_mass              [ireg][idv][ntrk-2]->Fill( secVtx_mass,                    weight );
	  h_ntrkDV_mass_s            [ireg][idv][ntrk-2]->Fill( secVtx_mass,                    weight );
	  h_ntrkDV_mass_xs           [ireg][idv][ntrk-2]->Fill( secVtx_mass,                    weight );
	  h_ntrkDV_direction         [ireg][idv][ntrk-2]->Fill( secVtx_dir,                     weight );
	  h_ntrkDV_minOpAng          [ireg][idv][ntrk-2]->Fill( secVtx_minOpAng,                weight );
	  h_ntrkDV_maxOpAng          [ireg][idv][ntrk-2]->Fill( secVtx_maxOpAng,                weight );
	  h_ntrkDV_chi2              [ireg][idv][ntrk-2]->Fill( m_secVtx_chi2 ->at(i),          weight );
	  h_ntrkDV_chi2_s            [ireg][idv][ntrk-2]->Fill( m_secVtx_chi2 ->at(i),          weight );
	  h_ntrkDV_sumd0             [ireg][idv][ntrk-2]->Fill( secVtx_sumd0,                   weight );
	  h_ntrkDV_sumz0             [ireg][idv][ntrk-2]->Fill( secVtx_sumz0,                   weight );
	  h_ntrkDV_sumP              [ireg][idv][ntrk-2]->Fill( secVtx_sumP,                    weight );
	  h_ntrkDV_sumd0_sv          [ireg][idv][ntrk-2]->Fill( secVtx_sumd0_sv,                weight );
	  h_ntrkDV_sumd0_sv          [ireg][idv][ntrk-2]->Fill( secVtx_sumz0_sv,                weight );
	  h_ntrkDV_sumP_sv           [ireg][idv][ntrk-2]->Fill( secVtx_sumP_sv,                 weight );
	  h_ntrkDV_sumsqrtd0         [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumd0),             weight );
	  h_ntrkDV_sumsqrtz0         [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumz0),             weight );
	  h_ntrkDV_sumsqrtP          [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumP),              weight );
	  h_ntrkDV_sumsqrtd0_sv      [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumd0_sv),          weight );
	  h_ntrkDV_sumsqrtd0_sv      [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumz0_sv),          weight );
	  h_ntrkDV_sumsqrtP_sv       [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumP_sv),           weight );
	  h_ntrkDV_mind0             [ireg][idv][ntrk-2]->Fill( secVtx_mind0,                   weight );
	  h_ntrkDV_minz0             [ireg][idv][ntrk-2]->Fill( secVtx_minz0,                   weight );
	  h_ntrkDV_minP              [ireg][idv][ntrk-2]->Fill( secVtx_minP,                    weight );
	  h_ntrkDV_mind0_sv          [ireg][idv][ntrk-2]->Fill( secVtx_mind0_sv,                weight );
	  h_ntrkDV_minz0_sv          [ireg][idv][ntrk-2]->Fill( secVtx_minz0_sv,                weight );
	  h_ntrkDV_minP_sv           [ireg][idv][ntrk-2]->Fill( secVtx_minP_sv,                 weight );
	  h_ntrkDV_minsqrtd0         [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_mind0),             weight );
	  h_ntrkDV_minsqrtz0         [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_minz0),             weight );
	  h_ntrkDV_minsqrtP          [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_minP),              weight );
	  h_ntrkDV_minsqrtd0_sv      [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_mind0_sv),          weight );
	  h_ntrkDV_minsqrtd0_sv      [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_minz0_sv),          weight );
	  h_ntrkDV_minsqrtP_sv       [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_minP_sv),           weight );
	  h_ntrkDV_maxd0             [ireg][idv][ntrk-2]->Fill( secVtx_maxd0,                   weight );
	  h_ntrkDV_maxz0             [ireg][idv][ntrk-2]->Fill( secVtx_maxz0,                   weight );
	  h_ntrkDV_maxP              [ireg][idv][ntrk-2]->Fill( secVtx_maxP,                    weight );
	  h_ntrkDV_maxd0_sv          [ireg][idv][ntrk-2]->Fill( secVtx_maxd0_sv,                weight );
	  h_ntrkDV_maxz0_sv          [ireg][idv][ntrk-2]->Fill( secVtx_maxz0_sv,                weight );
	  h_ntrkDV_maxP_sv           [ireg][idv][ntrk-2]->Fill( secVtx_maxP_sv,                 weight );
	  h_ntrkDV_maxsqrtd0         [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxd0),             weight );
	  h_ntrkDV_maxsqrtz0         [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxz0),             weight );
	  h_ntrkDV_maxsqrtP          [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxP),              weight );
	  h_ntrkDV_maxsqrtd0_sv      [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxd0_sv),          weight );
	  h_ntrkDV_maxsqrtd0_sv      [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxz0_sv),          weight );
	  h_ntrkDV_maxsqrtP_sv       [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxP_sv),           weight );
	  if ( m_histoInfoSwitch->m_vtxErrors ) {
	    h_ntrkDV_sqrterrx        [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_errx)),        weight );
	    h_ntrkDV_sqrterry        [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_erry)),        weight );
	    h_ntrkDV_sqrterrz        [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_errz)),        weight );
	    h_ntrkDV_sqrterrr        [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_errr)),        weight );
	    h_ntrkDV_sqrterrphi      [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_errphi)),      weight );
	    h_ntrkDV_sumSqrterrd0    [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_sumerrd0)),    weight );
	    h_ntrkDV_sumSqrterrz0    [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_sumerrz0)),    weight );
	    h_ntrkDV_sumSqrterrP     [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_sumerrP)),     weight );
	    h_ntrkDV_sumSqrterrd0_sv [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_sumerrd0_sv)), weight );
	    h_ntrkDV_sumSqrterrz0_sv [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_sumerrz0_sv)), weight );
	    h_ntrkDV_sumSqrterrP_sv  [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_sumerrP_sv)),  weight );
	    h_ntrkDV_minSqrterrd0    [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_minerrd0)),    weight );
	    h_ntrkDV_minSqrterrz0    [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_minerrz0)),    weight );
	    h_ntrkDV_minSqrterrP     [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_minerrP)),     weight );
	    h_ntrkDV_minSqrterrd0_sv [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_minerrd0_sv)), weight );
	    h_ntrkDV_minSqrterrz0_sv [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_minerrz0_sv)), weight );
	    h_ntrkDV_minSqrterrP_sv  [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_minerrP_sv)),  weight );
	    h_ntrkDV_maxSqrterrd0    [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_maxerrd0)),    weight );
	    h_ntrkDV_maxSqrterrz0    [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_maxerrz0)),    weight );
	    h_ntrkDV_maxSqrterrP     [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_maxerrP)),     weight );
	    h_ntrkDV_maxSqrterrd0_sv [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_maxerrd0_sv)), weight );
	    h_ntrkDV_maxSqrterrz0_sv [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_maxerrz0_sv)), weight );
	    h_ntrkDV_maxSqrterrP_sv  [ireg][idv][ntrk-2]->Fill( sqrt(sqrt(secVtx_maxerrP_sv)),  weight );
	  }
	}
	
      } // end loop over DV types

    } // end loop over vertices

    // fill DV count histograms
    if ( doHists ) {
      for ( size_t idv = 0; idv != n_DV.size(); ++idv ) {
	h_DV_n [ireg][idv] ->Fill( n_DV[idv], weight );
	if ( m_numVtxTrks ) {
	  for ( const auto& ntrkDV : n_ntrkDV[idv] )
	    h_ntrkDV_n [ireg][idv][ntrkDV.first-2] ->Fill( ntrkDV.second, weight );
	}
      }
    }



    // --- ABCD PLANE TESTS --- //
    // -- tentative ABCD variables
    if ( m_histoInfoSwitch->m_abcd ) {
      for ( size_t idv = 0; idv != n_DV.size(); ++idv ) {
	h_abcd_nDV_njetHt          [ireg][idv] ->Fill( m_njetHt,                    n_DV[idv], weight );
	h_abcd_nDV_njetHt_vrsh     [ireg][idv] ->Fill( m_njetHt * m_VRShift_njetHt, n_DV[idv], weight );
	h_abcd_raw_nDV_njetHt      [ireg][idv] ->Fill( m_njetHt,                    n_DV[idv], 1.0    );
	h_abcd_raw_nDV_njetHt_vrsh [ireg][idv] ->Fill( m_njetHt * m_VRShift_njetHt, n_DV[idv], 1.0    );
      }
    }



    // --- TRIGGER STUDY --- //
    // do trigger efficiency studies
    if ( m_histoInfoSwitch->m_trigTest ) {
      // count number of four-jet events
      bool fourJetEvent = false;
      if ( m_jet_n >= m_nJets ) {
	fourJetEvent  = true;
	++m_nFourJets [ireg];
      }
      bool fourJetOthEvent = false;
      if ( m_jetOth_n >= m_nJets )
	fourJetOthEvent     = true;
      // count number of search-region events (excluding trigger requirement)
      bool searchRegionEvent = false;
      if ( m_signal_njet && m_signal_jetPt && m_signal_jetEta && m_signal_njetHt ) {
      	searchRegionEvent = true;
      	++m_nSearch [ireg];
      }
      // count number of events passing trigger
      bool passTrig_4j120 = false;
      for ( size_t i = 0; i != m_passedTriggers ->size(); ++i ) {
	if ( m_passedTriggers ->at(i) == "HLT_4j120" ) {
	  passTrig_4j120  = true;
	  ++m_nTrig_4j120 [ireg];
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
	  ++m_nOffTrig_4j120 [ireg];
	  if ( passJVT ) {
	    passOffTrigJVT_4j120  = true;
	    ++m_nOffTrigJVT_4j120 [ireg];
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
	  ++m_nOffTrig_4j120_other [ireg];
	  if ( passJVT ) {
	    passOffTrigJVT_4j120_other  = true;
	    ++m_nOffTrigJVT_4j120_other [ireg];
	  }
	}
      }
      // --> TEST JVT
      // count number of four-jet events passing trigger and fill pt distributions
      if ( fourJetEvent ) {
      	double nth_jet_pt = m_jet_pt ->at(m_nJets-1);
      	h_nthJetPt                   [ireg] ->Fill( nth_jet_pt, weight );
      	if ( passTrig_4j120             ) {
      	  h_nthJetPt_trig            [ireg] ->Fill( nth_jet_pt, weight );
      	  ++m_nTrig_fourJet          [ireg];
      	}
      	if ( passOffTrig_4j120          ) {
      	  h_nthJetPt_offTrig         [ireg] ->Fill( nth_jet_pt, weight );
      	  ++m_nOffTrig_fourJet       [ireg];
      	}
      	if ( passOffTrig_4j120_other    ) {
      	  h_nthJetPt_othOffTrig      [ireg] ->Fill( nth_jet_pt, weight );
      	  ++m_nOthOffTrig_fourJet    [ireg];
      	}
      	if ( passOffTrigJVT_4j120       ) {
      	  h_nthJetPt_offTrigJVT      [ireg] ->Fill( nth_jet_pt, weight );
      	  ++m_nOffTrigJVT_fourJet    [ireg];
      	}
      	if ( passOffTrigJVT_4j120_other ) {
      	  h_nthJetPt_othOffTrigJVT   [ireg] ->Fill( nth_jet_pt, weight );
      	  ++m_nOthOffTrigJVT_fourJet [ireg];
      	}
      }
      // count number of search-region events passing trigger
      if ( searchRegionEvent ) {
      	if ( passTrig_4j120             ) ++m_nTrig_search          [ireg];
      	if ( passOffTrig_4j120          ) ++m_nOffTrig_search       [ireg];
      	if ( passOffTrig_4j120_other    ) ++m_nOthOffTrig_search    [ireg];
      	if ( passOffTrigJVT_4j120       ) ++m_nOffTrigJVT_search    [ireg];
      	if ( passOffTrigJVT_4j120_other ) ++m_nOthOffTrigJVT_search [ireg];
      }  
    } // end trigger test

    ++m_nEntries [ireg];
    
  } // end loop over regions

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: finalize ( const std::vector<EJsHelper::Region>& regions )
{
  
  for ( int ireg = 0; ireg != regions.size(); ++ireg ) {

    // fill metadata histograms
    h_MetaData_EventCount [ireg] ->Fill( 1, m_nEvents_init );
    h_MetaData_EventCount [ireg] ->Fill( 2, m_nEvents_sel  );
    h_MetaData_EventCount [ireg] ->Fill( 3, m_sumw_init    );
    h_MetaData_EventCount [ireg] ->Fill( 4, m_sumw_sel     );
    h_MetaData_EventCount [ireg] ->Fill( 5, m_sumw2_init   );
    h_MetaData_EventCount [ireg] ->Fill( 6, m_sumw2_sel    );
    h_MetaData_Weights    [ireg] ->Fill( 1, m_xsec * 1e6   ); // [fb]
    h_MetaData_Weights    [ireg] ->Fill( 2, m_kfactor      );
    h_MetaData_Weights    [ireg] ->Fill( 3, m_filteff      );
    h_MetaData_Weights    [ireg] ->Fill( 4, m_lumi         ); // [ifb]
    
    if ( m_histoInfoSwitch->m_trigTest ) {
      // trigger efficiency as function of nth leading jet pt
      h_trigEff_nthJetPt             [ireg] ->Divide( h_nthJetPt_trig          [ireg], h_nthJetPt [ireg] );
      h_offTrigEff_nthJetPt          [ireg] ->Divide( h_nthJetPt_offTrig       [ireg], h_nthJetPt [ireg] );
      h_othOffTrigEff_nthJetPt       [ireg] ->Divide( h_nthJetPt_othOffTrig    [ireg], h_nthJetPt [ireg] );
      h_offTrigJVTEff_nthJetPt       [ireg] ->Divide( h_nthJetPt_offTrigJVT    [ireg], h_nthJetPt [ireg] );
      h_othOffTrigJVTEff_nthJetPt    [ireg] ->Divide( h_nthJetPt_othOffTrigJVT [ireg], h_nthJetPt [ireg] );
      
      // overall trigger efficiency (kA / nA = n trig events / n initial events)
      // --> nA = initial number of events in sample A
      // --> --> sample A = total events, four-jet events, ...
      // ... search region events (excluding trigger requirement), signal region events (region A, excluding trigger)
      // --> kA = final number of events in sample A after requiring trigger
      std::vector<int> nTrigEvents
      	= { m_nTrig_4j120            [ireg],
      	    m_nOffTrig_4j120         [ireg], m_nOffTrig_4j120_other     [ireg],
      	    m_nOffTrigJVT_4j120      [ireg], m_nOffTrigJVT_4j120_other  [ireg] };
      std::vector<int> nFourJetTrigEvents
      	= { m_nTrig_fourJet          [ireg], // four-jet region
	    m_nOffTrig_fourJet       [ireg], m_nOthOffTrig_fourJet      [ireg],
	    m_nOffTrigJVT_fourJet    [ireg], m_nOthOffTrigJVT_fourJet   [ireg] };
      std::vector<int> nSearchTrigEvents
      	= { m_nTrig_search           [ireg], // jet search region
	    m_nOffTrig_search        [ireg], m_nOthOffTrig_search       [ireg],
	    m_nOffTrigJVT_search     [ireg], m_nOthOffTrigJVT_search    [ireg] };
      for ( size_t i = 0; i != nTrigEvents.size(); ++i ) {
      	h_triggerEfficiency          [ireg] // trigger efficiency for all events
      	  ->Fill( i+1,   nTrigEvents        [i] / float( m_nEntries  [ireg] ) );
	h_triggerEfficiency_fourJet  [ireg] // trigger efficiency for four-jet events
      	  ->Fill( i+1,   nFourJetTrigEvents [i] / float( m_nFourJets [ireg] ) );
      	h_triggerEfficiency_search   [ireg] // trigger efficiency for search-region events
      	  ->Fill( i+1,   nSearchTrigEvents  [i] / float( m_nSearch   [ireg] ) );
      	h_searchTriggerEfficiency    [ireg] // search region efficiency
      	  ->Fill( i+1,   nSearchTrigEvents  [i] / float( m_nEntries  [ireg] ) );
      }
    } // end trigger study
    
  } // end loop over regions
  
  return StatusCode::SUCCESS;
}



void EJsHistogramManager :: getTrkTypes ( int trk_index, std::vector<int>& trk ) {
  
  bool lrtTrk   = false;
  bool selTrk   = false;
  bool assocTrk = false;
  bool svTrk    = false;
  bool cleanTrk = false;
  bool filtTrk  = false;
  bool finalTrk = false;
  if ( m_trk_isLRT     ->at(trk_index) ) lrtTrk   = true;
  if ( m_trk_isSel     ->at(trk_index) ) selTrk   = true;
  if ( m_trk_isAssoc   ->at(trk_index) ) assocTrk = true;
  if ( m_trk_isSV      ->at(trk_index) ) svTrk    = true;
  if ( m_trk_isCleanSV ->at(trk_index) ) cleanTrk = true;
  if ( m_trk_isFiltSV  ->at(trk_index) ) filtTrk  = true;
  if ( m_trk_isFinalSV ->at(trk_index) ) finalTrk = true;
  trk .push_back( true     ); // all tracks
  trk .push_back( lrtTrk   );
  trk .push_back( selTrk   );
  trk .push_back( assocTrk );
  trk .push_back( svTrk    );
  trk .push_back( cleanTrk );
  trk .push_back( filtTrk  );
  trk .push_back( finalTrk );
  
}
