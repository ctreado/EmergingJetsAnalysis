#include <map>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/EJsHistogramManager.h"
#include "EJsAnalysis/AlgConsts.h"


EJsHistogramManager :: EJsHistogramManager ( const std::string& name, const std::string& detailStr, const std::string& jetStr,
					     const std::map<std::string, float>& metadata, const std::vector<TH1F*>& ntupCutHists,
					     float lumi, bool debug, bool mc, bool unblind )
  : HistogramManager ( name, detailStr )
{
  m_histoInfoSwitch = new EJsHelperClasses::HistogramInfoSwitch( detailStr );
  m_jetStr             = jetStr;
  m_nEvents_init       = metadata.find( "eventCount_init" )->second;
  m_nEvents_sel        = metadata.find( "eventCount_sel"  )->second;
  m_sumw_init          = metadata.find( "sumw_init"       )->second;
  m_sumw_sel           = metadata.find( "sumw_sel"        )->second;
  m_sumw2_init         = metadata.find( "sumw2_init"      )->second;
  m_sumw2_sel          = metadata.find( "sumw2_sel"       )->second;
  m_xsec               = metadata.find( "crossSection"    )->second;
  m_kfactor            = metadata.find( "kFactor"         )->second;
  m_filteff            = metadata.find( "genFilterEff"    )->second;
  m_ntupCutHists       = ntupCutHists;
  m_lumi               = lumi;
  m_debug              = debug;
  m_mc                 = mc;
  m_unblind            = unblind;
  m_numLeadJets        = m_histoInfoSwitch->m_numLeadingJets;
  m_numVtxTrks         = m_histoInfoSwitch->m_numVtxTrks;
  m_doComboDVs         = m_histoInfoSwitch->m_comboVerts;

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
  m_truthPartPtSum     = 0;
  m_truthPartDarkPtSum = 0;
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
  m_jet_n                  = 0;
  m_jet_ID                 = new std::vector<int>;
  m_jet_index              = new std::vector<int>;
  m_jet_pt                 = new std::vector<float>;
  m_jet_eta                = new std::vector<float>;
  m_jet_phi                = new std::vector<float>;
  m_jet_E                  = new std::vector<float>;
  m_jet_M                  = new std::vector<float>;
  m_jet_rapid              = new std::vector<float>;
  m_jet_nConstits          = new std::vector<int>;
  m_jet_passJVT            = new std::vector<int>;
  m_jet_timing             = new std::vector<float>;
  m_jet_LArQual            = new std::vector<float>;
  m_jet_HECQual            = new std::vector<float>;
  m_jet_avgLArQF           = new std::vector<float>;
  m_jet_n90Constits        = new std::vector<float>;
  m_jet_centroidR          = new std::vector<float>;
  m_jet_ootFracClust5      = new std::vector<float>;
  m_jet_ootFracClust10     = new std::vector<float>;
  m_jet_fracSampMax        = new std::vector<float>;
  m_jet_fracSampMaxIx      = new std::vector<float>;
  m_jet_leadClustPt        = new std::vector<float>;
  m_jet_leadClustCtrLambda = new std::vector<float>;
  m_jet_leadClust2ndLambda = new std::vector<float>;
  m_jet_leadClust2ndR      = new std::vector<float>;
  m_jet_EMFrac             = new std::vector<float>;
  m_jet_HECFrac            = new std::vector<float>;
  m_jet_width              = new std::vector<float>;
  m_jet_ntrkPt10           = new std::vector<int>;
  m_jet_sumPtTrkPt10       = new std::vector<float>;
  m_jet_trkWidthPt10       = new std::vector<float>;
  m_jet_ntrkPt5            = new std::vector<int>;
  m_jet_sumPtTrkPt5        = new std::vector<float>;
  m_jet_trkWidthPt5        = new std::vector<float>;
  m_jet_JVF                = new std::vector<float>;
  m_jet_partonID           = new std::vector<int>;
  m_jet_isDark             = new std::vector<uint8_t>;
  m_jet_darkID             = new std::vector<int>;
  m_jet_darkIndex          = new std::vector<int>;
  m_jet_darkDR             = new std::vector<float>;
  m_jet_isTruth            = new std::vector<uint8_t>;
  m_jet_truthID            = new std::vector<int>;
  m_jet_truthIndex         = new std::vector<int>;
  m_jet_truthDR            = new std::vector<float>;
  m_jet_ghostTrk_n         = new std::vector<int>;
  m_jet_ghostTrk_ID        = new std::vector<std::vector<int>>;
  m_jet_ghostTrk_index     = new std::vector<std::vector<int>>;
  m_jet_trk_n              = new std::vector<int>;
  m_jet_trk_ID             = new std::vector<std::vector<int>>;
  m_jet_trk_index          = new std::vector<std::vector<int>>;
  m_jet_trk_dR             = new std::vector<std::vector<float>>;
  m_jet_secVtx_n           = new std::vector<int>;
  m_jet_secVtx_ID          = new std::vector<std::vector<int>>;
  m_jet_secVtx_index       = new std::vector<std::vector<int>>;
  m_jet_secVtx_dR          = new std::vector<std::vector<float>>;

  // truth jet branches
  m_truthJet_n           = 0;
  m_truthJet_ID          = new std::vector<int>;
  m_truthJet_index       = new std::vector<int>;
  m_truthJet_pt          = new std::vector<float>;
  m_truthJet_eta         = new std::vector<float>;
  m_truthJet_phi         = new std::vector<float>;
  m_truthJet_E           = new std::vector<float>;
  m_truthJet_M           = new std::vector<float>;
  m_truthJet_rapid       = new std::vector<float>;
  m_truthJet_girth       = new std::vector<float>;
  m_truthJet_nConstit    = new std::vector<int>;
  m_truthJet_constitPt   = new std::vector<float>;
  m_truthJet_constit_pt  = new std::vector<std::vector<float>>;
  m_truthJet_constit_eta = new std::vector<std::vector<float>>;
  m_truthJet_isDark      = new std::vector<uint8_t>;
  m_truthJet_darkID      = new std::vector<int>;
  m_truthJet_darkIndex   = new std::vector<int>;
  m_truthJet_darkDR      = new std::vector<float>;
  m_truthJet_darkPt      = new std::vector<float>;
  m_truthJet_nTV         = new std::vector<int>;
  m_truthJet_TV_llp      = new std::vector<std::vector<std::string>>;
  m_truthJet_TV_ID       = new std::vector<std::vector<int>>;
  m_truthJet_TV_index    = new std::vector<std::vector<int>>;
  m_truthJet_TV_r        = new std::vector<std::vector<float>>;
  m_truthJet_TV_z        = new std::vector<std::vector<float>>;
  m_truthJet_TV_dR       = new std::vector<std::vector<float>>;
  m_truthJet_ntp         = new std::vector<int>;
  m_truthJet_tp_ID       = new std::vector<std::vector<int>>;
  m_truthJet_tp_index    = new std::vector<std::vector<int>>;
  m_truthJet_tp_dR       = new std::vector<std::vector<float>>;
  m_truthJet_tp_phi      = new std::vector<std::vector<float>>;

  // dark jet branches
  m_darkJet_n            = 0;
  m_darkJet_ID           = new std::vector<int>;
  m_darkJet_index        = new std::vector<int>;
  m_darkJet_pt           = new std::vector<float>;
  m_darkJet_eta          = new std::vector<float>;
  m_darkJet_phi          = new std::vector<float>;
  m_darkJet_E            = new std::vector<float>;
  m_darkJet_M            = new std::vector<float>;
  m_darkJet_rapid        = new std::vector<float>;
  m_darkJet_girth        = new std::vector<float>;
  m_darkJet_nConstit     = new std::vector<int>;
  m_darkJet_constitPt    = new std::vector<float>;
  m_darkJet_constit_pt   = new std::vector<std::vector<float>>;
  m_darkJet_constit_eta  = new std::vector<std::vector<float>>;
  m_darkJet_truthMatch   = new std::vector<uint8_t>;
  m_darkJet_nTV          = new std::vector<int>;
  m_darkJet_TV_llp       = new std::vector<std::vector<std::string>>;
  m_darkJet_TV_ID        = new std::vector<std::vector<int>>;
  m_darkJet_TV_index     = new std::vector<std::vector<int>>;
  m_darkJet_TV_r         = new std::vector<std::vector<float>>;
  m_darkJet_TV_z         = new std::vector<std::vector<float>>;
  m_darkJet_TV_dR        = new std::vector<std::vector<float>>;
  m_darkJet_ntp          = new std::vector<int>;
  m_darkJet_tp_ID        = new std::vector<std::vector<int>>;
  m_darkJet_tp_index     = new std::vector<std::vector<int>>;
  m_darkJet_tp_dR        = new std::vector<std::vector<float>>;
  m_darkJet_tp_phi       = new std::vector<std::vector<float>>;
  

  // truth part branches
  m_tp_n                   = 0;
  m_tp_ID                  = new std::vector<int>;
  m_tp_index               = new std::vector<int>;
  m_tp_pt                  = new std::vector<float>;
  m_tp_eta                 = new std::vector<float>;
  m_tp_phi                 = new std::vector<float>;
  m_tp_E                   = new std::vector<float>;
  m_tp_M                   = new std::vector<float>;
  m_tp_charge              = new std::vector<float>;
  m_tp_pdgId               = new std::vector<int>;
  m_tp_status              = new std::vector<int>;
  m_tp_isReco              = new std::vector<uint8_t>;
  m_tp_recoProb            = new std::vector<float>;
  m_tp_recoID              = new std::vector<int>;
  m_tp_recoIndex           = new std::vector<int>;
  m_tp_isStable            = new std::vector<uint8_t>;
  m_tp_isDark              = new std::vector<uint8_t>;
  m_tp_isDesc              = new std::vector<uint8_t>;
  m_tp_ancest_llp          = new std::vector<std::vector<std::string>>;
  m_tp_ancest_ID           = new std::vector<std::vector<int>>;
  m_tp_ancest_index        = new std::vector<std::vector<int>>;
  m_tp_nParents            = new std::vector<int>;
  m_tp_parent_pdgId        = new std::vector<std::vector<int>>;
  m_tp_parent_status       = new std::vector<std::vector<int>>;
  m_tp_nChildren           = new std::vector<int>;
  m_tp_child_pdgId         = new std::vector<std::vector<int>>;
  m_tp_child_status        = new std::vector<std::vector<int>>;
  m_tp_pvtx                = new std::vector<uint8_t>;
  m_tp_pvtx_ID             = new std::vector<int>;
  m_tp_pvtx_index          = new std::vector<int>;
  m_tp_pvtx_r              = new std::vector<float>;
  m_tp_truthJetMatch       = new std::vector<uint8_t>;
  m_tp_truthJetMatch_ID    = new std::vector<int>;
  m_tp_truthJetMatch_index = new std::vector<int>;
  m_tp_truthJetMatch_dR    = new std::vector<float>;
  m_tp_darkJetMatch        = new std::vector<uint8_t>;
  m_tp_darkJetMatch_ID     = new std::vector<int>;
  m_tp_darkJetMatch_index  = new std::vector<int>;
  m_tp_darkJetMatch_dR     = new std::vector<float>;

  // track branches
  m_trk_n              = 0;
  m_trk_ID             = new std::vector<int>;
  m_trk_index          = new std::vector<int>;
  m_trk_qOverP         = new std::vector<float>;
  m_trk_theta          = new std::vector<float>;
  m_trk_pt             = new std::vector<float>;
  m_trk_eta            = new std::vector<float>;
  m_trk_phi            = new std::vector<float>;
  m_trk_E              = new std::vector<float>;
  m_trk_M              = new std::vector<float>;
  m_trk_d0             = new std::vector<float>;
  m_trk_z0             = new std::vector<float>;
  m_trk_errd0          = new std::vector<float>;
  m_trk_errz0          = new std::vector<float>;
  m_trk_errP           = new std::vector<float>;
  m_trk_chi2           = new std::vector<float>;
  m_trk_chiSq          = new std::vector<float>;
  m_trk_ndof           = new std::vector<int>;
  m_trk_charge         = new std::vector<float>;
  m_trk_isLRT          = new std::vector<uint8_t>;
  m_trk_isSel          = new std::vector<uint8_t>;
  m_trk_isAssoc        = new std::vector<uint8_t>;
  m_trk_isSV           = new std::vector<uint8_t>;
  m_trk_isCleanSV      = new std::vector<uint8_t>;
  m_trk_isFiltSV       = new std::vector<uint8_t>;
  m_trk_isFinalSV      = new std::vector<uint8_t>;
  m_trk_SV_ID          = new std::vector<int>;
  m_trk_SV_index       = new std::vector<int>;
  m_trk_nSCT           = new std::vector<uint8_t>;
  m_trk_nPixel         = new std::vector<uint8_t>;
  m_trk_nTRT           = new std::vector<uint8_t>;
  m_trk_jetMatch       = new std::vector<uint8_t>;
  m_trk_jetMatch_ID    = new std::vector<int>;
  m_trk_jetMatch_index = new std::vector<int>;
  m_trk_jetMatch_dR    = new std::vector<float>;

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
  m_truthVtx_childOpAng   = new std::vector<float>;
  m_truthVtx_nOutP        = new std::vector<int>;
  m_truthVtx_isRecoble    = new std::vector<uint8_t>;
  m_truthVtx_nDesc        = new std::vector<int>;
  m_truthVtx_nRecoDesc    = new std::vector<int>;
  m_truthVtx_nSelDesc     = new std::vector<int>;
  m_truthVtx_descPt       = new std::vector<float>;
  m_truthVtx_descEta      = new std::vector<float>;
  m_truthVtx_descPhi      = new std::vector<float>;
  m_truthVtx_descE        = new std::vector<float>;
  m_truthVtx_descM        = new std::vector<float>;
  m_truthVtx_desc_ID      = new std::vector<std::vector<int>>;
  m_truthVtx_desc_index   = new std::vector<std::vector<int>>;
  m_truthVtx_desc_pt      = new std::vector<std::vector<float>>;
  m_truthVtx_desc_eta     = new std::vector<std::vector<float>>;
  m_truthVtx_desc_phi     = new std::vector<std::vector<float>>;
  m_truthVtx_desc_E       = new std::vector<std::vector<float>>;
  m_truthVtx_desc_M       = new std::vector<std::vector<float>>;
  m_truthVtx_desc_isReco  = new std::vector<std::vector<uint8_t>>;
  m_truthVtx_desc_recoID  = new std::vector<std::vector<int>>;
  m_truthVtx_nPos         = new std::vector<int>;
  m_truthVtx_reco_n       = new std::vector<int>;
  m_truthVtx_reco_ID      = new std::vector<std::vector<int>>;
  m_truthVtx_reco_index   = new std::vector<std::vector<int>>;
  m_truthVtx_reco_score   = new std::vector<std::vector<float>>;
  m_truthVtx_reco_posID   = new std::vector<std::vector<int>>;
  m_truthVtx_reco_resid   = new std::vector<std::vector<float>>;
  m_truthVtx_reco_x       = new std::vector<std::vector<float>>;
  m_truthVtx_reco_y       = new std::vector<std::vector<float>>;
  m_truthVtx_reco_z       = new std::vector<std::vector<float>>;
  m_truthVtx_reco_r       = new std::vector<std::vector<float>>;
  m_truthVtx_reco_phi     = new std::vector<std::vector<float>>;
  m_truthVtx_reco_ntrk    = new std::vector<std::vector<int>>;
  m_truthVtx_reco_nseltrk = new std::vector<std::vector<int>>;

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
  m_secVtx_H               = new std::vector<float>;
  m_secVtx_Ht              = new std::vector<float>;
  m_secVtx_minOpAng        = new std::vector<float>;
  m_secVtx_maxOpAng        = new std::vector<float>;
  m_secVtx_mind0           = new std::vector<float>;
  m_secVtx_maxd0           = new std::vector<float>;
  m_secVtx_passMatVeto     = new std::vector<uint8_t>;
  m_secVtx_pt_clean        = new std::vector<float>;
  m_secVtx_eta_clean       = new std::vector<float>;
  m_secVtx_phi_clean       = new std::vector<float>;
  m_secVtx_mass_clean      = new std::vector<float>;
  m_secVtx_massNA_clean    = new std::vector<float>;
  m_secVtx_direction_clean = new std::vector<float>;
  m_secVtx_H_clean         = new std::vector<float>;
  m_secVtx_Ht_clean        = new std::vector<float>;
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
  m_secVtx_H_bare          = new std::vector<float>;
  m_secVtx_Ht_bare         = new std::vector<float>;
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
  delete m_jet_nConstits;
  delete m_jet_passJVT;
  delete m_jet_timing;
  delete m_jet_LArQual;
  delete m_jet_HECQual;
  delete m_jet_avgLArQF;
  delete m_jet_n90Constits;
  delete m_jet_centroidR;
  delete m_jet_ootFracClust5;
  delete m_jet_ootFracClust10;
  delete m_jet_fracSampMax;
  delete m_jet_fracSampMaxIx;
  delete m_jet_leadClustPt;
  delete m_jet_leadClustCtrLambda;
  delete m_jet_leadClust2ndLambda;
  delete m_jet_leadClust2ndR;
  delete m_jet_EMFrac;
  delete m_jet_HECFrac;
  delete m_jet_width;
  delete m_jet_ntrkPt10;
  delete m_jet_sumPtTrkPt10;
  delete m_jet_trkWidthPt10;
  delete m_jet_ntrkPt5;
  delete m_jet_sumPtTrkPt5;
  delete m_jet_trkWidthPt5;
  delete m_jet_JVF;
  delete m_jet_partonID;
  delete m_jet_isDark;
  delete m_jet_darkID;
  delete m_jet_darkIndex;
  delete m_jet_darkDR;
  delete m_jet_isTruth;
  delete m_jet_truthID;
  delete m_jet_truthIndex;
  delete m_jet_truthDR;
  delete m_jet_ghostTrk_n;
  delete m_jet_ghostTrk_ID;
  delete m_jet_ghostTrk_index;
  delete m_jet_trk_n;
  delete m_jet_trk_ID;
  delete m_jet_trk_index;
  delete m_jet_trk_dR;
  delete m_jet_secVtx_n;
  delete m_jet_secVtx_ID;
  delete m_jet_secVtx_index;
  delete m_jet_secVtx_dR;

  // truth jet branches
  delete m_truthJet_ID;
  delete m_truthJet_index;
  delete m_truthJet_pt;
  delete m_truthJet_eta;
  delete m_truthJet_phi;
  delete m_truthJet_E;
  delete m_truthJet_M;
  delete m_truthJet_rapid;
  delete m_truthJet_girth;
  delete m_truthJet_nConstit;
  delete m_truthJet_constitPt;
  delete m_truthJet_constit_pt;
  delete m_truthJet_constit_eta;
  delete m_truthJet_isDark;
  delete m_truthJet_darkID;
  delete m_truthJet_darkIndex;
  delete m_truthJet_darkDR;
  delete m_truthJet_darkPt;
  delete m_truthJet_nTV;
  delete m_truthJet_TV_llp;
  delete m_truthJet_TV_ID;
  delete m_truthJet_TV_index;
  delete m_truthJet_TV_r;
  delete m_truthJet_TV_z;
  delete m_truthJet_TV_dR;
  delete m_truthJet_ntp;
  delete m_truthJet_tp_ID;
  delete m_truthJet_tp_index;
  delete m_truthJet_tp_dR;
  delete m_truthJet_tp_phi;

  // dark jet branches
  delete m_darkJet_ID;
  delete m_darkJet_index;
  delete m_darkJet_pt;
  delete m_darkJet_eta;
  delete m_darkJet_phi;
  delete m_darkJet_E;
  delete m_darkJet_M;
  delete m_darkJet_rapid;
  delete m_darkJet_girth;
  delete m_darkJet_nConstit;
  delete m_darkJet_constitPt;
  delete m_darkJet_constit_pt;
  delete m_darkJet_constit_eta;
  delete m_darkJet_truthMatch;
  delete m_darkJet_nTV;
  delete m_darkJet_TV_llp;
  delete m_darkJet_TV_ID;
  delete m_darkJet_TV_index;
  delete m_darkJet_TV_r;
  delete m_darkJet_TV_z;
  delete m_darkJet_TV_dR;
  delete m_darkJet_ntp;
  delete m_darkJet_tp_ID;
  delete m_darkJet_tp_index;
  delete m_darkJet_tp_dR;
  delete m_darkJet_tp_phi;

  // truth particle branches
  delete m_tp_ID;
  delete m_tp_index;
  delete m_tp_pt;
  delete m_tp_eta;
  delete m_tp_phi;
  delete m_tp_E;
  delete m_tp_M;
  delete m_tp_charge;
  delete m_tp_pdgId;
  delete m_tp_status;
  delete m_tp_isReco;
  delete m_tp_recoProb;
  delete m_tp_recoID;
  delete m_tp_recoIndex;
  delete m_tp_isStable;
  delete m_tp_isDark;
  delete m_tp_isDesc;
  delete m_tp_ancest_llp;
  delete m_tp_ancest_ID;
  delete m_tp_ancest_index;
  delete m_tp_nParents;
  delete m_tp_parent_pdgId;
  delete m_tp_parent_status;
  delete m_tp_nChildren;
  delete m_tp_child_pdgId;
  delete m_tp_child_status;
  delete m_tp_pvtx;
  delete m_tp_pvtx_ID;
  delete m_tp_pvtx_index;
  delete m_tp_pvtx_r;
  delete m_tp_truthJetMatch;
  delete m_tp_truthJetMatch_ID;
  delete m_tp_truthJetMatch_index;
  delete m_tp_truthJetMatch_dR;
  delete m_tp_darkJetMatch;
  delete m_tp_darkJetMatch_ID;
  delete m_tp_darkJetMatch_index;
  delete m_tp_darkJetMatch_dR;

  // track branches
  delete m_trk_ID;
  delete m_trk_index;
  delete m_trk_qOverP;
  delete m_trk_theta;
  delete m_trk_pt;
  delete m_trk_eta;
  delete m_trk_phi;
  delete m_trk_E;
  delete m_trk_M;
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
  delete m_trk_SV_ID;
  delete m_trk_SV_index;
  delete m_trk_nSCT;
  delete m_trk_nPixel;
  delete m_trk_nTRT;
  delete m_trk_jetMatch;
  delete m_trk_jetMatch_ID;
  delete m_trk_jetMatch_index;
  delete m_trk_jetMatch_dR;

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
  delete m_truthVtx_childOpAng;
  delete m_truthVtx_nOutP;
  delete m_truthVtx_isRecoble;
  delete m_truthVtx_nDesc;
  delete m_truthVtx_nRecoDesc;
  delete m_truthVtx_nSelDesc;
  delete m_truthVtx_descPt;
  delete m_truthVtx_descEta;
  delete m_truthVtx_descPhi;
  delete m_truthVtx_descE;
  delete m_truthVtx_descM;
  delete m_truthVtx_desc_ID;
  delete m_truthVtx_desc_index;
  delete m_truthVtx_desc_pt;
  delete m_truthVtx_desc_eta;
  delete m_truthVtx_desc_phi;
  delete m_truthVtx_desc_E;
  delete m_truthVtx_desc_M;
  delete m_truthVtx_desc_isReco;
  delete m_truthVtx_desc_recoID;
  delete m_truthVtx_nPos;
  delete m_truthVtx_reco_n;
  delete m_truthVtx_reco_ID;
  delete m_truthVtx_reco_index;
  delete m_truthVtx_reco_score;
  delete m_truthVtx_reco_posID;
  delete m_truthVtx_reco_resid;
  delete m_truthVtx_reco_x;
  delete m_truthVtx_reco_y;
  delete m_truthVtx_reco_z;
  delete m_truthVtx_reco_r;
  delete m_truthVtx_reco_phi;
  delete m_truthVtx_reco_ntrk;
  delete m_truthVtx_reco_nseltrk;

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
  delete m_secVtx_H;
  delete m_secVtx_Ht;
  delete m_secVtx_minOpAng;
  delete m_secVtx_maxOpAng;
  delete m_secVtx_mind0;
  delete m_secVtx_maxd0;
  delete m_secVtx_passMatVeto;
  delete m_secVtx_pt_clean;
  delete m_secVtx_eta_clean;
  delete m_secVtx_phi_clean;
  delete m_secVtx_mass_clean;
  delete m_secVtx_massNA_clean;
  delete m_secVtx_direction_clean;
  delete m_secVtx_H_clean;
  delete m_secVtx_Ht_clean;
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
  delete m_secVtx_H_bare;
  delete m_secVtx_Ht_bare;
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

  connectBranch<float>    ( tree, "truthPartPtSum",     &m_truthPartPtSum     );
  connectBranch<float>    ( tree, "truthPartDarkPtSum", &m_truthPartDarkPtSum );

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

  connectBranch<int>   ( name, tree, "ID",                         &m_jet_ID                 );
  connectBranch<int>   ( name, tree, "index",                      &m_jet_index              );
  connectBranch<float> ( name, tree, "pt",                         &m_jet_pt                 );
  connectBranch<float> ( name, tree, "eta",                        &m_jet_eta                );
  connectBranch<float> ( name, tree, "phi",                        &m_jet_phi                );
  connectBranch<float> ( name, tree, "E",                          &m_jet_E                  );
  connectBranch<float> ( name, tree, "M",                          &m_jet_M                  );
  connectBranch<float> ( name, tree, "rapidity",                   &m_jet_rapid              );
  connectBranch<int>   ( name, tree, "numConstituents",            &m_jet_nConstits          );
  connectBranch<int>   ( name, tree, "JvtPass_Medium",             &m_jet_passJVT            );
  connectBranch<float> ( name, tree, "Timing",                     &m_jet_timing             );
  connectBranch<float> ( name, tree, "LArQuality",                 &m_jet_LArQual            );
  connectBranch<float> ( name, tree, "HECQuality",                 &m_jet_HECQual            );
  connectBranch<float> ( name, tree, "AverageLArQF",               &m_jet_avgLArQF           );
  connectBranch<float> ( name, tree, "N90Constituents",            &m_jet_n90Constits        );
  connectBranch<float> ( name, tree, "CentroidR",                  &m_jet_centroidR          );
  connectBranch<float> ( name, tree, "OotFracClusters5",           &m_jet_ootFracClust5      );
  connectBranch<float> ( name, tree, "OotFracClusters10",          &m_jet_ootFracClust10     );
  connectBranch<float> ( name, tree, "FracSamplingMax",            &m_jet_fracSampMax        );
  connectBranch<float> ( name, tree, "FracSamplingMaxIndex",       &m_jet_fracSampMaxIx      );
  connectBranch<float> ( name, tree, "LeadingClusterPt",           &m_jet_leadClustPt        );
  connectBranch<float> ( name, tree, "LeadingClusterCenterLambda", &m_jet_leadClustCtrLambda );
  connectBranch<float> ( name, tree, "LeadingClusterSecondLambda", &m_jet_leadClust2ndLambda );
  connectBranch<float> ( name, tree, "LeadingClusterSecondR",      &m_jet_leadClust2ndR      );
  connectBranch<float> ( name, tree, "EMFrac",                     &m_jet_EMFrac             );
  connectBranch<float> ( name, tree, "HECFrac",                    &m_jet_HECFrac            );
  connectBranch<float> ( name, tree, "Width",                      &m_jet_width              );
  connectBranch<int>   ( name, tree, "NumTrkPt1000PV",             &m_jet_ntrkPt10           );
  connectBranch<float> ( name, tree, "SumPtTrkPt1000PV",           &m_jet_sumPtTrkPt10       );
  connectBranch<float> ( name, tree, "TrackWidthPt1000PV",         &m_jet_trkWidthPt10       );
  connectBranch<int>   ( name, tree, "NumTrkPt500PV",              &m_jet_ntrkPt5            );
  connectBranch<float> ( name, tree, "SumPtTrkPt500PV",            &m_jet_sumPtTrkPt5        );
  connectBranch<float> ( name, tree, "TrackWidthPt500PV",          &m_jet_trkWidthPt5        );
  connectBranch<float> ( name, tree, "JVFPV",                      &m_jet_JVF                );

  if ( m_mc ) {
    connectBranch<int>     ( name, tree, "PartonTruthLabelID", &m_jet_partonID   );
    connectBranch<uint8_t> ( name, tree, "isDarkMatched",      &m_jet_isDark     );
    connectBranch<int>     ( name, tree, "darkMatch_ID",       &m_jet_darkID     );
    connectBranch<int>     ( name, tree, "darkMatch_index",    &m_jet_darkIndex  );
    connectBranch<float>   ( name, tree, "darkMatch_dR",       &m_jet_darkDR     );
    connectBranch<uint8_t> ( name, tree, "isTruthMatched",     &m_jet_isTruth    );
    connectBranch<int>     ( name, tree, "truthMatch_ID",      &m_jet_truthID    );
    connectBranch<int>     ( name, tree, "truthMatch_index",   &m_jet_truthIndex );
    connectBranch<float>   ( name, tree, "truthMatch_dR",      &m_jet_truthDR    );
  }

  connectBranch<int>                ( name, tree, "GhostTrackCount",  &m_jet_ghostTrk_n     );
  connectBranch<std::vector<int>>   ( name, tree, "GhostTrack_ID",    &m_jet_ghostTrk_ID    );
  connectBranch<std::vector<int>>   ( name, tree, "GhostTrack_index", &m_jet_ghostTrk_index );
  connectBranch<int>                ( name, tree, "trkCount",         &m_jet_trk_n          );
  connectBranch<std::vector<int>>   ( name, tree, "trk_ID",           &m_jet_trk_ID         );
  connectBranch<std::vector<int>>   ( name, tree, "trk_index",        &m_jet_trk_index      );
  connectBranch<std::vector<float>> ( name, tree, "trk_dR",           &m_jet_trk_dR         );
  connectBranch<int>                ( name, tree, "secVtxCount",      &m_jet_secVtx_n       );
  connectBranch<std::vector<int>>   ( name, tree, "secVtx_ID",        &m_jet_secVtx_ID      );
  connectBranch<std::vector<int>>   ( name, tree, "secVtx_index",     &m_jet_secVtx_index   );
  connectBranch<std::vector<float>> ( name, tree, "secVtx_dR",        &m_jet_secVtx_dR      );
  
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

  connectBranch<int>                      ( name, tree, "ID",                &m_truthJet_ID          );
  connectBranch<int>                      ( name, tree, "index",             &m_truthJet_index       );
  connectBranch<float>                    ( name, tree, "pt",                &m_truthJet_pt          );
  connectBranch<float>                    ( name, tree, "eta",               &m_truthJet_eta         );
  connectBranch<float>                    ( name, tree, "phi",               &m_truthJet_phi         );
  connectBranch<float>                    ( name, tree, "E",                 &m_truthJet_E           );
  connectBranch<float>                    ( name, tree, "M",                 &m_truthJet_M           );
  connectBranch<float>                    ( name, tree, "rapidity",          &m_truthJet_rapid       );
  connectBranch<float>                    ( name, tree, "girth",             &m_truthJet_girth       );
  connectBranch<int>                      ( name, tree, "numConstituents",   &m_truthJet_nConstit    );
  connectBranch<float>                    ( name, tree, "constituentPt",     &m_truthJet_constitPt   );
  connectBranch<std::vector<float>>       ( name, tree, "constituent_pt",    &m_truthJet_constit_pt  );
  connectBranch<std::vector<float>>       ( name, tree, "constituent_eta",   &m_truthJet_constit_eta );
  connectBranch<uint8_t>                  ( name, tree, "isDarkMatched",     &m_truthJet_isDark      );
  connectBranch<int>                      ( name, tree, "darkMatch_ID",      &m_truthJet_darkID      );
  connectBranch<int>                      ( name, tree, "darkMatch_index",   &m_truthJet_darkIndex   );
  connectBranch<float>                    ( name, tree, "darkMatch_dR",      &m_truthJet_darkDR      );
  connectBranch<float>                    ( name, tree, "darkMatch_pt",      &m_truthJet_darkPt      );
  connectBranch<int>                      ( name, tree, "truthVtxCount",     &m_truthJet_nTV         );
  connectBranch<std::vector<std::string>> ( name, tree, "truthVtx_llpDecay", &m_truthJet_TV_llp      );
  connectBranch<std::vector<int>>         ( name, tree, "truthVtx_ID",       &m_truthJet_TV_ID       );
  connectBranch<std::vector<int>>         ( name, tree, "truthVtx_index",    &m_truthJet_TV_index    );
  connectBranch<std::vector<float>>       ( name, tree, "truthVtx_r",        &m_truthJet_TV_r        );
  connectBranch<std::vector<float>>       ( name, tree, "truthVtx_z",        &m_truthJet_TV_z        );
  connectBranch<std::vector<float>>       ( name, tree, "truthVtx_dR",       &m_truthJet_TV_dR       );
  connectBranch<int>                      ( name, tree, "tpCount",           &m_truthJet_ntp         );
  connectBranch<std::vector<int>>         ( name, tree, "tp_ID",             &m_truthJet_tp_ID       );
  connectBranch<std::vector<int>>         ( name, tree, "tp_index",          &m_truthJet_tp_index    );
  connectBranch<std::vector<float>>       ( name, tree, "tp_dR",             &m_truthJet_tp_dR       );
  connectBranch<std::vector<float>>       ( name, tree, "tp_phi",            &m_truthJet_tp_phi      );
  
  return StatusCode::SUCCESS;
}


StatusCode EJsHistogramManager :: connectTruthDarkJets ( TTree* tree, const std::string& darkJetName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthDarkJets()", "connecting truth dark jet branches" );

  std::string name = darkJetName;

  using namespace EJsHelper;

  connectBranch<int> ( tree, "n" + name, &m_darkJet_n );

  using namespace HelperFunctions;

  connectBranch<int>                      ( name, tree, "ID",                &m_darkJet_ID          );
  connectBranch<int>                      ( name, tree, "index",             &m_darkJet_index       );
  connectBranch<float>                    ( name, tree, "pt",                &m_darkJet_pt          );
  connectBranch<float>                    ( name, tree, "eta",               &m_darkJet_eta         );
  connectBranch<float>                    ( name, tree, "phi",               &m_darkJet_phi         );
  connectBranch<float>                    ( name, tree, "E",                 &m_darkJet_E           );
  connectBranch<float>                    ( name, tree, "M",                 &m_darkJet_M           );
  connectBranch<float>                    ( name, tree, "rapidity",          &m_darkJet_rapid       );
  connectBranch<float>                    ( name, tree, "girth",             &m_darkJet_girth       );
  connectBranch<int>                      ( name, tree, "numConstituents",   &m_darkJet_nConstit    );
  connectBranch<float>                    ( name, tree, "constituentPt",     &m_darkJet_constitPt   );
  connectBranch<std::vector<float>>       ( name, tree, "constituent_pt",    &m_darkJet_constit_pt  );
  connectBranch<std::vector<float>>       ( name, tree, "constituent_eta",   &m_darkJet_constit_eta );
  connectBranch<uint8_t>                  ( name, tree, "isMatchedToTruth",  &m_darkJet_truthMatch  );
  connectBranch<int>                      ( name, tree, "truthVtxCount",     &m_darkJet_nTV         );
  connectBranch<std::vector<std::string>> ( name, tree, "truthVtx_llpDecay", &m_darkJet_TV_llp      );
  connectBranch<std::vector<int>>         ( name, tree, "truthVtx_ID",       &m_darkJet_TV_ID       );
  connectBranch<std::vector<int>>         ( name, tree, "truthVtx_index",    &m_darkJet_TV_index    );
  connectBranch<std::vector<float>>       ( name, tree, "truthVtx_r",        &m_darkJet_TV_r        );
  connectBranch<std::vector<float>>       ( name, tree, "truthVtx_z",        &m_darkJet_TV_z        );
  connectBranch<std::vector<float>>       ( name, tree, "truthVtx_dR",       &m_darkJet_TV_dR       );
  connectBranch<int>                      ( name, tree, "tpCount",           &m_darkJet_ntp         );
  connectBranch<std::vector<int>>         ( name, tree, "tp_ID",             &m_darkJet_tp_ID       );
  connectBranch<std::vector<int>>         ( name, tree, "tp_index",          &m_darkJet_tp_index    );
  connectBranch<std::vector<float>>       ( name, tree, "tp_dR",             &m_darkJet_tp_dR       );
  connectBranch<std::vector<float>>       ( name, tree, "tp_phi",            &m_darkJet_tp_phi      );
  
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
  connectBranch<float>   ( name, tree, "E",                 &m_trk_E         );
  connectBranch<float>   ( name, tree, "M",                 &m_trk_M         );
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
  connectBranch<int>     ( name, tree, "secVtxID",          &m_trk_SV_ID     );
  connectBranch<int>     ( name, tree, "secVtxIndex",       &m_trk_SV_index  );
  connectBranch<uint8_t> ( name, tree, "nSCTHits",          &m_trk_nSCT      );
  connectBranch<uint8_t> ( name, tree, "nPixelHits",        &m_trk_nPixel    );
  connectBranch<uint8_t> ( name, tree, "nTRTHits",          &m_trk_nTRT      );

  std::string trk_jetStr = m_jetStr;
  for ( size_t i = 0; i != trk_jetStr.length(); ++i ) trk_jetStr[i] = std::tolower( trk_jetStr[i] );
  connectBranch<uint8_t> ( name, tree, trk_jetStr + "JetMatch",       &m_trk_jetMatch       );
  connectBranch<int>     ( name, tree, trk_jetStr + "JetMatch_ID",    &m_trk_jetMatch_ID    );
  connectBranch<int>     ( name, tree, trk_jetStr + "JetMatch_index", &m_trk_jetMatch_index );
  connectBranch<float>   ( name, tree, trk_jetStr + "JetMatch_dR",    &m_trk_jetMatch_dR    );
  
  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthParts ( TTree* tree, const std::string& truthPartName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthParts()", "connecting truth particle branches" );

  std::string name = truthPartName;

  using namespace EJsHelper;

  connectBranch<int> ( tree, "n" + name, &m_tp_n );

  using namespace HelperFunctions;

  connectBranch<int>                      ( name, tree, "ID",                  &m_tp_ID                  );
  connectBranch<int>                      ( name, tree, "index",               &m_tp_index               );
  connectBranch<float>                    ( name, tree, "pt",                  &m_tp_pt                  );
  connectBranch<float>                    ( name, tree, "eta",                 &m_tp_eta                 );
  connectBranch<float>                    ( name, tree, "phi",                 &m_tp_phi                 );
  connectBranch<float>                    ( name, tree, "E",                   &m_tp_E                   );
  connectBranch<float>                    ( name, tree, "M",                   &m_tp_M                   );
  connectBranch<float>                    ( name, tree, "charge",              &m_tp_charge              );
  connectBranch<int>                      ( name, tree, "status",              &m_tp_status              );
  connectBranch<uint8_t>                  ( name, tree, "isReco",              &m_tp_isReco              );
  connectBranch<float>                    ( name, tree, "recoProb",            &m_tp_recoProb            );
  connectBranch<int>                      ( name, tree, "recoID",              &m_tp_recoID              );
  connectBranch<int>                      ( name, tree, "recoIndex",           &m_tp_recoIndex           );
  connectBranch<uint8_t>                  ( name, tree, "isStable",            &m_tp_isStable            );
  connectBranch<uint8_t>                  ( name, tree, "isDark",              &m_tp_isDark              );
  connectBranch<uint8_t>                  ( name, tree, "isDescendant",        &m_tp_isDesc              );
  connectBranch<std::vector<std::string>> ( name, tree, "ancestor_llpDecay",   &m_tp_ancest_llp          );
  connectBranch<std::vector<int>>         ( name, tree, "ancestor_ID",         &m_tp_ancest_ID           );
  connectBranch<std::vector<int>>         ( name, tree, "ancestor_index",      &m_tp_ancest_index        );
  connectBranch<int>                      ( name, tree, "pdgId",               &m_tp_pdgId               );
  connectBranch<int>                      ( name, tree, "nParents",            &m_tp_nParents            );
  connectBranch<std::vector<int>>         ( name, tree, "parent_pdgId",        &m_tp_parent_pdgId        );
  connectBranch<std::vector<int>>         ( name, tree, "parent_status",       &m_tp_parent_status       );
  connectBranch<int>                      ( name, tree, "nChildren",           &m_tp_nChildren           );
  connectBranch<std::vector<int>>         ( name, tree, "child_pdgId",         &m_tp_child_pdgId         );
  connectBranch<std::vector<int>>         ( name, tree, "child_status",        &m_tp_child_status        );
  connectBranch<uint8_t>                  ( name, tree, "hasProdVtx",          &m_tp_pvtx                );
  connectBranch<int>                      ( name, tree, "prodVtx_ID",          &m_tp_pvtx_ID             );
  connectBranch<int>                      ( name, tree, "prodVtx_index",       &m_tp_pvtx_index          );
  connectBranch<float>                    ( name, tree, "prodVtx_r",           &m_tp_pvtx_r              );
  connectBranch<uint8_t>                  ( name, tree, "truthJetMatch",       &m_tp_truthJetMatch       );
  connectBranch<int>                      ( name, tree, "truthJetMatch_ID",    &m_tp_truthJetMatch_ID    );
  connectBranch<int>                      ( name, tree, "truthJetMatch_index", &m_tp_truthJetMatch_index );
  connectBranch<float>                    ( name, tree, "truthJetMatch_dR",    &m_tp_truthJetMatch_dR    );
  connectBranch<uint8_t>                  ( name, tree, "darkJetMatch",        &m_tp_darkJetMatch        );
  connectBranch<int>                      ( name, tree, "darkJetMatch_ID",     &m_tp_darkJetMatch_ID     );
  connectBranch<int>                      ( name, tree, "darkJetMatch_index",  &m_tp_darkJetMatch_index  );
  connectBranch<float>                    ( name, tree, "darkJetMatch_dR",     &m_tp_darkJetMatch_dR     );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectSecondaryVerts ( TTree* tree, const std::string& secVtxName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectSecondaryVerts()", "connecting secondary vertex branches" );

  std::string name = secVtxName;

  using namespace EJsHelper;

  connectBranch<int> ( tree, "n" + name, &m_secVtx_n );
  
  using namespace HelperFunctions;

  connectBranch<int>     ( name, tree, "ID",                  &m_secVtx_ID              );
  connectBranch<int>     ( name, tree, "index",               &m_secVtx_index           );
  connectBranch<float>   ( name, tree, "x",                   &m_secVtx_x               );
  connectBranch<float>   ( name, tree, "y",                   &m_secVtx_y               );
  connectBranch<float>   ( name, tree, "z",                   &m_secVtx_z               );
  connectBranch<float>   ( name, tree, "r",                   &m_secVtx_r               );
  connectBranch<float>   ( name, tree, "pt",                  &m_secVtx_pt              );
  connectBranch<float>   ( name, tree, "eta",                 &m_secVtx_eta             );
  connectBranch<float>   ( name, tree, "phi",                 &m_secVtx_phi             );
  connectBranch<float>   ( name, tree, "mass",                &m_secVtx_mass            );
  connectBranch<float>   ( name, tree, "mass_nonAssoc",       &m_secVtx_massNA          );
  connectBranch<float>   ( name, tree, "direction",           &m_secVtx_direction       );
  connectBranch<float>   ( name, tree, "H",                   &m_secVtx_H               );
  connectBranch<float>   ( name, tree, "Ht",                  &m_secVtx_Ht              );
  connectBranch<float>   ( name, tree, "minOpAng",            &m_secVtx_minOpAng        );
  connectBranch<float>   ( name, tree, "maxOpAng",            &m_secVtx_maxOpAng        );
  connectBranch<float>   ( name, tree, "mind0",               &m_secVtx_mind0           );
  connectBranch<float>   ( name, tree, "maxd0",               &m_secVtx_maxd0           );
  connectBranch<uint8_t> ( name, tree, "passMaterialVeto",    &m_secVtx_passMatVeto     );
  connectBranch<float>   ( name, tree, "pt_clean",            &m_secVtx_pt_clean        );
  connectBranch<float>   ( name, tree, "eta_clean",           &m_secVtx_eta_clean       );
  connectBranch<float>   ( name, tree, "phi_clean",           &m_secVtx_phi_clean       );
  connectBranch<float>   ( name, tree, "mass_clean",          &m_secVtx_mass_clean      );
  connectBranch<float>   ( name, tree, "mass_nonAssoc_clean", &m_secVtx_massNA_clean    );
  connectBranch<float>   ( name, tree, "direction_clean",     &m_secVtx_direction_clean );
  connectBranch<float>   ( name, tree, "H_clean",             &m_secVtx_H_clean         );
  connectBranch<float>   ( name, tree, "Ht_clean",            &m_secVtx_Ht_clean        );
  connectBranch<float>   ( name, tree, "minOpAng_clean",      &m_secVtx_minOpAng_clean  );
  connectBranch<float>   ( name, tree, "maxOpAng_clean",      &m_secVtx_maxOpAng_clean  );
  connectBranch<float>   ( name, tree, "mind0_clean",         &m_secVtx_mind0_clean     );
  connectBranch<float>   ( name, tree, "maxd0_clean",         &m_secVtx_maxd0_clean     );
  connectBranch<float>   ( name, tree, "pt_bare",             &m_secVtx_pt_bare         );
  connectBranch<float>   ( name, tree, "eta_bare",            &m_secVtx_eta_bare        );
  connectBranch<float>   ( name, tree, "phi_bare",            &m_secVtx_phi_bare        );
  connectBranch<float>   ( name, tree, "mass_bare",           &m_secVtx_mass_bare       );
  connectBranch<float>   ( name, tree, "mass_nonAssoc_bare",  &m_secVtx_massNA_bare     );
  connectBranch<float>   ( name, tree, "direction_bare",      &m_secVtx_direction_bare  );
  connectBranch<float>   ( name, tree, "H_bare",              &m_secVtx_H_bare          );
  connectBranch<float>   ( name, tree, "Ht_bare",             &m_secVtx_Ht_bare         );
  connectBranch<float>   ( name, tree, "minOpAng_bare",       &m_secVtx_minOpAng_bare   );
  connectBranch<float>   ( name, tree, "maxOpAng_bare",       &m_secVtx_maxOpAng_bare   );
  connectBranch<float>   ( name, tree, "mind0_bare",          &m_secVtx_mind0_bare      );
  connectBranch<float>   ( name, tree, "maxd0_bare",          &m_secVtx_maxd0_bare      );
  connectBranch<float>   ( name, tree, "chi2",                &m_secVtx_chi2            );

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

  connectBranch<std::string> ( name, tree, "llpDecay",             &m_truthVtx_llp        );
  connectBranch<int>         ( name, tree, "ID",                   &m_truthVtx_ID         );
  connectBranch<int>         ( name, tree, "index",                &m_truthVtx_index      );
  connectBranch<float>       ( name, tree, "x",                    &m_truthVtx_x          );
  connectBranch<float>       ( name, tree, "y",                    &m_truthVtx_y          );
  connectBranch<float>       ( name, tree, "z",                    &m_truthVtx_z          );
  connectBranch<float>       ( name, tree, "r",                    &m_truthVtx_r          );
  connectBranch<float>       ( name, tree, "pt",                   &m_truthVtx_pt         );
  connectBranch<float>       ( name, tree, "eta",                  &m_truthVtx_eta        );
  connectBranch<float>       ( name, tree, "phi",                  &m_truthVtx_phi        );
  connectBranch<float>       ( name, tree, "mass",                 &m_truthVtx_mass       );
  connectBranch<float>       ( name, tree, "childOpenAngle",       &m_truthVtx_childOpAng );
  connectBranch<int>         ( name, tree, "nOutP",                &m_truthVtx_nOutP      );
  connectBranch<uint8_t>     ( name, tree, "isReconstructible",    &m_truthVtx_isRecoble  );
  
  connectBranch<int>         ( name, tree, "descendant_n",         &m_truthVtx_nDesc      );
  connectBranch<int>         ( name, tree, "descendant_nReco",     &m_truthVtx_nRecoDesc  );
  connectBranch<int>         ( name, tree, "descendant_nSelected", &m_truthVtx_nSelDesc   );
  connectBranch<float>       ( name, tree, "descendant_sumPt",     &m_truthVtx_descPt     );
  connectBranch<float>       ( name, tree, "descendant_sumEta",    &m_truthVtx_descEta    );
  connectBranch<float>       ( name, tree, "descendant_sumPhi",    &m_truthVtx_descPhi    );
  connectBranch<float>       ( name, tree, "descendant_sumE",      &m_truthVtx_descE      );
  connectBranch<float>       ( name, tree, "descendant_sumM",      &m_truthVtx_descM      );

  connectBranch<std::vector<int>>     ( name, tree, "descendant_ID",     &m_truthVtx_desc_ID     );
  connectBranch<std::vector<int>>     ( name, tree, "descendant_index",  &m_truthVtx_desc_index  );
  connectBranch<std::vector<float>>   ( name, tree, "descendant_pt",     &m_truthVtx_desc_pt     );
  connectBranch<std::vector<float>>   ( name, tree, "descendant_eta",    &m_truthVtx_desc_eta    );
  connectBranch<std::vector<float>>   ( name, tree, "descendant_phi",    &m_truthVtx_desc_phi    );
  connectBranch<std::vector<float>>   ( name, tree, "descendant_E",      &m_truthVtx_desc_E      );
  connectBranch<std::vector<float>>   ( name, tree, "descendant_M",      &m_truthVtx_desc_M      );
  connectBranch<std::vector<uint8_t>> ( name, tree, "descendant_isReco", &m_truthVtx_desc_isReco );
  connectBranch<std::vector<int>>     ( name, tree, "descendant_recoID", &m_truthVtx_desc_recoID );

  connectBranch<int> ( name, tree, "physPos_n", &m_truthVtx_nPos );

  connectBranch<int>                ( name, tree, "matchedRecoVtx_n",                 &m_truthVtx_reco_n       );
  connectBranch<std::vector<int>>   ( name, tree, "matchedRecoVtx_ID",                &m_truthVtx_reco_ID      );
  connectBranch<std::vector<int>>   ( name, tree, "matchedRecoVtx_index",             &m_truthVtx_reco_index   );
  connectBranch<std::vector<float>> ( name, tree, "matchedRecoVtx_matchScore",        &m_truthVtx_reco_score   );
  connectBranch<std::vector<int>>   ( name, tree, "matchedRecoVtx_reprTruthPosID",    &m_truthVtx_reco_posID   );
  connectBranch<std::vector<float>> ( name, tree, "matchedRecoVtx_residual_distance", &m_truthVtx_reco_resid   );
  connectBranch<std::vector<float>> ( name, tree, "matchedRecoVtx_x",                 &m_truthVtx_reco_x       );
  connectBranch<std::vector<float>> ( name, tree, "matchedRecoVtx_y",                 &m_truthVtx_reco_y       );
  connectBranch<std::vector<float>> ( name, tree, "matchedRecoVtx_z",                 &m_truthVtx_reco_z       );
  connectBranch<std::vector<float>> ( name, tree, "matchedRecoVtx_r",                 &m_truthVtx_reco_r       );
  connectBranch<std::vector<float>> ( name, tree, "matchedRecoVtx_phi",               &m_truthVtx_reco_phi     );
  connectBranch<std::vector<int>>   ( name, tree, "matchedRecoVtx_ntrk",              &m_truthVtx_reco_ntrk    );
  connectBranch<std::vector<int>>   ( name, tree, "matchedRecoVtx_ntrk_sel",          &m_truthVtx_reco_nseltrk );
  
  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: initialize ( const std::string& outFileName, const std::vector<EJsHelper::Region>& regions,
					       const std::string& jetHistName, const EJsHelper::BaseDV& base_dv )
{
  if ( m_debug ) Info( "EJsHistogramManager::initialize()", "booking histograms" );

  // initialize object types

  // --> signal vertex types
  std::vector<std::string> hSgnlDV    = { "Loose",  "Mid",     "Tight"  };
  std::vector<std::string> hSgnlDVstr = { "Loose,", "Medium,", "Tight," };
  m_nTypeSgnlDVs = hSgnlDV.size();

  // --> truth jets
  std::vector<std::string> hTJ, hTJstr;
  hTJ    .push_back( ""                ); // all truth jets
  hTJstr .push_back( ""                );
  hTJ    .push_back( "Lead"            );
  hTJstr .push_back( "lead N"          );
  hTJ    .push_back( "Emerging"        ); // truth emerging jets (dark-matched)
  hTJstr .push_back( "emerging"        );
  hTJ    .push_back( "LeadEmerging"    );
  hTJstr .push_back( "lead N emerging" );
  hTJ    .push_back( "Qcd"             ); // truth qcd jets (not dark-matched)
  hTJstr .push_back( "QCD"             );
  hTJ    .push_back( "LeadQcd"         );
  hTJstr .push_back( "lead N QCD"      );
  m_nTypeTJs = hTJ.size();

  // --> truth dark jets --> for truth match (here and in declaring "emerging" jets), add cut on pt (>25GeV?)
  std::vector<std::string> hDJ, hDJstr;
  hDJ    .push_back( ""     ); // all truth dark jets
  hDJstr .push_back( ""     );
  hDJ    .push_back( "Good" );
  hDJstr .push_back( "good" ); // truth matchd and pt > 30 GeV
  m_nTypeDJs = hDJ.size();

  
  // --> jets
  std::vector<std::string> hJ, hJstr;
  // base jets (EMTopo or PFlow; no cuts beyond search/validation region pt, eta cuts)
  std::string baseJ    = "";
  std::string baseJstr = "";
  hJ    .push_back( baseJ    );
  hJstr .push_back( baseJstr );
  // --> lead jets (N top-pt)
  std::string leadJ    = "Lead";
  std::string leadJstr = "lead";
  hJ    .push_back( leadJ    );
  hJstr .push_back( leadJstr );

  m_LJix = hJ.size();

  // --> "tight" jet cuts
  std::string tightptJ       = "HardPt";
  std::string tightetaJ      = "HardEta";
  std::string tightmJ        = "HardMass";
  std::string tightptJstr    = "hard-pt";
  std::string tightetaJstr   = "hard-eta";
  std::string tightmJstr     = "hard-mass";
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_tightJets ) {
    // tight-pt jets
    hJ      .push_back( tightptJ    );
    hJstr   .push_back( tightptJstr );
    // --> lead tight-pt jets (N top-pt tight-pt)
    hJ      .push_back( leadJ    +       tightptJ    );
    hJstr   .push_back( leadJstr + " " + tightptJstr );
    // tight-eta jets
    hJ      .push_back( tightetaJ    );
    hJstr   .push_back( tightetaJstr );
    // --> lead tight-eta jets (N top-pt tight-eta)
    hJ      .push_back( leadJ    +       tightetaJ    );
    hJstr   .push_back( leadJstr + " " + tightetaJstr );
    // tight-mass jets
    hJ      .push_back( tightmJ    );
    hJstr   .push_back( tightmJstr );
    // --> lead tight-mass jets (N top-pt tight-mass)
    hJ      .push_back( leadJ    +       tightmJ    );
    hJstr   .push_back( leadJstr + " " + tightmJstr );
  }

  std::string baseJSVup = base_dv.name; baseJSVup[0] = toupper(baseJSVup[0]);
  std::vector<std::string> JSV;
  std::vector<std::string> JSVstr;
  JSV    .push_back( baseJSVup    +  "SV" );
  JSVstr .push_back( base_dv.name + "-SV" );
  for ( size_t ijsv = 0; ijsv != hSgnlDV.size(); ++ijsv ) {
    std::string sgnlJSVstr = hSgnlDVstr[ijsv]; sgnlJSVstr.pop_back();
    JSV    .push_back( hSgnlDV[ijsv] + "SV"  );
    JSVstr .push_back( sgnlJSVstr    + "-SV" );
  }
  m_nTypeJSVs = JSV.size();

  // --> n-sv pt jet cuts
  m_svP4J_ix = m_nType1SVJs;
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvP4Jets ) {
    for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
      for ( const auto& injsvk : m_nJSVkin ) {
	std::string snjsvk     = injsvk; snjsvk[0] = toupper(snjsvk[0]);
	std::string hnJSVp4    = JSV   [ijsv] + snjsvk + "P4";
	std::string hnJSVp4str = JSVstr[ijsv] + "-" + injsvk + "-pt";
	hJ    .push_back( hnJSVp4    );
	hJstr .push_back( hnJSVp4str );
	hJ    .push_back( leadJ    +       hnJSVp4    );
	hJstr .push_back( leadJstr + " " + hnJSVp4str );
      }
    }
    m_nType1SVJs += JSV.size() * m_nJSVpt.size() * m_LJix;
  }
  // --> n-sv sum-pt jet cuts
  m_svPtJ_ix = m_nType1SVJs;
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvPtJets ) {
    for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
      for ( const auto& injsvk : m_nJSVkin ) {
	std::string snjsvk     = injsvk; snjsvk[0] = toupper(snjsvk[0]);
	std::string hnJSVpt    = JSV   [ijsv] + snjsvk + "Pt";
	std::string hnJSVptstr = JSVstr[ijsv] + "-" + injsvk + "-sum-pt";
	hJ    .push_back( hnJSVpt    );
	hJstr .push_back( hnJSVptstr );
	hJ    .push_back( leadJ    +       hnJSVpt    );
	hJstr .push_back( leadJstr + " " + hnJSVptstr );
      }
    }
    m_nType1SVJs += JSV.size() * m_nJSVpt.size() * m_LJix;
  }
  // --> n-sv sum-Ht jet cuts
  m_svHtJ_ix = m_nType1SVJs;
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHtJets ) {
    for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
      for ( const auto& injsvk : m_nJSVkin ) {
	std::string snjsvk     = injsvk; snjsvk[0] = toupper(snjsvk[0]);
	std::string hnJSVht    = JSV   [ijsv] + snjsvk + "Ht";
	std::string hnJSVhtstr = JSVstr[ijsv] + "-" + injsvk + "-sum-Ht";
	hJ    .push_back( hnJSVht    );
	hJstr .push_back( hnJSVhtstr );
	hJ    .push_back( leadJ    +       hnJSVht    );
	hJstr .push_back( leadJstr + " " + hnJSVhtstr );
      }
    }
    m_nType1SVJs += JSV.size() * m_nJSVpt.size() * m_LJix;
  }
  // --> n-sv sum-H jet cuts
  m_svHJ_ix = m_nType1SVJs;
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHJets ) {
    for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
      for ( const auto& injsvk : m_nJSVkin ) {
	std::string snjsvk    = injsvk; snjsvk[0] = toupper(snjsvk[0]);
	std::string hnJSVh    = JSV   [ijsv] + snjsvk + "H";
	std::string hnJSVhstr = JSVstr[ijsv] + "-" + injsvk + "-sum-H";
	hJ    .push_back( hnJSVh    );
	hJstr .push_back( hnJSVhstr );
	hJ    .push_back( leadJ    +       hnJSVh    );
	hJstr .push_back( leadJstr + " " + hnJSVhstr );
      }
    }
    m_nType1SVJs += JSV.size() * m_nJSVh.size() * m_LJix;
  }

  // --> n-sv ntrk jet cuts
  m_svNtrkJ_ix = m_nType1SVJs;
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNtrkJets ) {
    for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
      for ( const auto& injsvt : m_nJSVtrk ) {
	std::string snjsvt     = std::to_string(injsvt);
	std::string hnJSVnT    = JSV[ijsv] + "Ntrk" + snjsvt;
	std::string hnJSVnTstr = snjsvt + "-" + JSVstr[ijsv] + "-Ntrk";
	hJ    .push_back( hnJSVnT    );
	hJstr .push_back( hnJSVnTstr );
	hJ    .push_back( leadJ    +       hnJSVnT    );
	hJstr .push_back( leadJstr + " " + hnJSVnTstr );
      }
    }
    m_nType1SVJs += JSV.size() * m_nJSVtrk.size() * m_LJix;
  }
  // --> n-sv njtrk jet cuts
  m_svNjtrkJ_ix = m_nType1SVJs;
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNjtrkJets ) {
    for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
      for ( const auto& injsvt : m_nJSVtrk ) {
	std::string snjsvt      = std::to_string(injsvt);
	std::string hnJSVnJT    = JSV[ijsv] + "Njtrk" + snjsvt;
	std::string hnJSVnJTstr = snjsvt + "-" + JSVstr[ijsv] + "-Njtrk";
	hJ    .push_back( hnJSVnJT    );
	hJstr .push_back( hnJSVnJTstr );
	hJ    .push_back( leadJ    +       hnJSVnJT    );
	hJstr .push_back( leadJstr + " " + hnJSVnJTstr );
      }
    }
    m_nType1SVJs += JSV.size() * m_nJSVtrk.size() * m_LJix;
  }
  // --> n-sv-trk jet cuts
  m_svTrkJ_ix = m_nType1SVJs;
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvTrkJets ) {
    for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
      for ( const auto& injsvt : m_nJSVtrk ) {
	std::string snjsvt    = std::to_string(injsvt);
	std::string hnJSVT    = JSV[ijsv] + "trk" + snjsvt;
	std::string hnJSVTstr = snjsvt + "-" + JSVstr[ijsv] + "-trk";
	hJ    .push_back( hnJSVT    );
	hJstr .push_back( hnJSVTstr );
	hJ    .push_back( leadJ    +       hnJSVT    );
	hJstr .push_back( leadJstr + " " + hnJSVTstr );
      }
    }
    m_nType1SVJs += JSV.size() * m_nJSVtrk.size() * m_LJix;
  }
  // --> n-sv jet cuts
  m_svNJ_ix = m_nType1SVJs;
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvJets ) {
    for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
      for ( const auto& injsv : m_nJSV ) {
	std::string snjsv    = std::to_string(injsv);
	std::string hnJSV    = JSV[ijsv] + snjsv;
	std::string hnJSVstr = snjsv + "-" + JSVstr[ijsv];
	hJ    .push_back( hnJSV    );
	hJstr .push_back( hnJSVstr );
	hJ    .push_back( leadJ    +       hnJSV    );
	hJstr .push_back( leadJstr + " " + hnJSVstr );
      }
    }
    m_nType1SVJs += JSV.size() * m_nJSV   .size() * m_LJix;
  }

  // number of individual jet cuts
  m_nType1Js  = hJ .size();

  // --> combination jet cuts
  std::string tightJ    = "Hard";
  std::string tightJstr = "hard";
  if ( m_histoInfoSwitch->m_comboJets ) {
    // --> tight jets
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_tightJets ) {
      hJ    .push_back( tightJ    );
      hJstr .push_back( tightJstr );
      hJ    .push_back( leadJ    +       tightJ    );
      hJstr .push_back( leadJstr + " " + tightJstr );
    }
    // --> n-sv pt tight jets
    if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvP4Jets ) )
      for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv )
  	for ( const auto& injsvk : m_nJSVkin ) {
  	  std::string snjsvk     = injsvk; snjsvk[0] = toupper(snjsvk[0]);
  	  std::string hnJSVp4    = JSV   [ijsv] + snjsvk + "P4";
  	  std::string hnJSVp4str = JSVstr[ijsv] + "-" + injsvk + "-pt";
  	  hJ    .push_back( hnJSVp4                     +       tightJ    );
  	  hJstr .push_back( hnJSVp4str                  + " " + tightJstr );
  	  hJ    .push_back( leadJ    +       hnJSVp4    +       tightJ    );
  	  hJstr .push_back( leadJstr + " " + hnJSVp4str + " " + tightJstr );
      }
    // --> n-sv sum-pt tight jets
    if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvPtJets ) )
      for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv )
  	for ( const auto& injsvk : m_nJSVkin ) {
  	  std::string snjsvk     = injsvk; snjsvk[0] = toupper(snjsvk[0]);
  	  std::string hnJSVpt    = JSV   [ijsv] + snjsvk + "Pt";
  	  std::string hnJSVptstr = JSVstr[ijsv] + "-" + injsvk + "-sum-pt";
  	  hJ    .push_back( hnJSVpt                     +       tightJ    );
  	  hJstr .push_back( hnJSVptstr                  + " " + tightJstr );
  	  hJ    .push_back( leadJ    +       hnJSVpt    +       tightJ    );
  	  hJstr .push_back( leadJstr + " " + hnJSVptstr + " " + tightJstr );
  	}
    // --> n-sv sum-Ht tight jets
    if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvHtJets ) )
      for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv )
  	for ( const auto& injsvk : m_nJSVkin ) {
  	  std::string snjsvk     = injsvk; snjsvk[0] = toupper(snjsvk[0]);
  	  std::string hnJSVht    = JSV   [ijsv] + snjsvk + "Ht";
  	  std::string hnJSVhtstr = JSVstr[ijsv] + "-" + injsvk + "-sum-Ht";
  	  hJ    .push_back( hnJSVht                     +       tightJ    );
  	  hJstr .push_back( hnJSVhtstr                  + " " + tightJstr );
  	  hJ    .push_back( leadJ    +       hnJSVht    +       tightJ    );
  	  hJstr .push_back( leadJstr + " " + hnJSVhtstr + " " + tightJstr );
  	}
    // --> n-sv sum-H tight jets
    if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvHJets ) )
      for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv )
  	for ( const auto& injsvk : m_nJSVkin ) {
  	  std::string snjsvk    = injsvk; snjsvk[0] = toupper(snjsvk[0]);
  	  std::string hnJSVh    = JSV   [ijsv] + snjsvk + "H";
  	  std::string hnJSVhstr = JSVstr[ijsv] + "-" + injsvk + "-sum-H";
  	  hJ    .push_back( hnJSVh                     +       tightJ    );
  	  hJstr .push_back( hnJSVhstr                  + " " + tightJstr );
  	  hJ    .push_back( leadJ    +       hnJSVh    +       tightJ    );
  	  hJstr .push_back( leadJstr + " " + hnJSVhstr + " " + tightJstr );
  	}
    if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvNtrkJets ) )
      for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv )
  	for ( const auto& injsvt : m_nJSVtrk ) {
  	  std::string snjsvt      = std::to_string(injsvt);
  	  std::string hnJSVnT     = JSV[ijsv] + "Ntrk"  + snjsvt;
  	  std::string hnJSVnTstr  = snjsvt + "-" + JSVstr[ijsv] + "-Ntrk";
  	  hJ    .push_back( hnJSVnT                      +       tightJ    );
  	  hJstr .push_back( hnJSVnTstr                   + " " + tightJstr );
  	  hJ    .push_back( leadJ    +       hnJSVnT     +       tightJ    );
  	  hJstr .push_back( leadJstr + " " + hnJSVnTstr  + " " + tightJstr );
  	}
    if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvNjtrkJets ) )
      for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv )
  	for ( const auto& injsvt : m_nJSVtrk ) {
  	  std::string snjsvt      = std::to_string(injsvt);
  	  std::string hnJSVnJT    = JSV[ijsv] + "Njtrk" + snjsvt;
  	  std::string hnJSVnJTstr = snjsvt + "-" + JSVstr[ijsv] + "-Njtrk";
  	  hJ    .push_back( hnJSVnJT                     +       tightJ    );
  	  hJstr .push_back( hnJSVnJTstr                  + " " + tightJstr );
  	  hJ    .push_back( leadJ    +       hnJSVnJT    +       tightJ    );
  	  hJstr .push_back( leadJstr + " " + hnJSVnJTstr + " " + tightJstr );
  	}
    if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvTrkJets ) )
      for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv )
  	for ( const auto& injsvt : m_nJSVtrk ) {
  	  std::string snjsvt      = std::to_string(injsvt);
  	  std::string hnJSVT      = JSV[ijsv] + "trk"   + snjsvt;
  	  std::string hnJSVTstr   = snjsvt + "-" + JSVstr[ijsv] + "-trk";
  	  hJ    .push_back( hnJSVT                       +       tightJ    );
  	  hJstr .push_back( hnJSVTstr                    + " " + tightJstr );
  	  hJ    .push_back( leadJ    +       hnJSVT      +       tightJ    );
  	  hJstr .push_back( leadJstr + " " + hnJSVTstr   + " " + tightJstr );
  	}
    if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvJets ) )
      for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv )
  	for ( const auto& injsv : m_nJSV ) {
  	  std::string snjsv    = std::to_string(injsv);
  	  std::string hnJSV    = JSV[ijsv] + snjsv;
  	  std::string hnJSVstr = snjsv + "-" + JSVstr[ijsv];
  	  hJ    .push_back( hnJSV                     +       tightJ    );
  	  hJstr .push_back( hnJSVstr                  + " " + tightJstr );
  	  hJ    .push_back( leadJ    +       hnJSV    +       tightJ    );
  	  hJstr .push_back( leadJstr + " " + hnJSVstr + " " + tightJstr );
  	}
  }

  // --> "EJ" jets -- tentative set of cuts to define emerging-like jet
  std::vector<std::string> hEJstr;
  for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
    std::string svptlJstr  = JSVstr[ijsv] + "-" + m_nJSVkin[0] + "-pt";
    std::string svtrkl     = std::to_string( m_nJSVtrk[0] );
    std::string svtrklJstr = svtrkl + "-" + JSVstr[ijsv] + "-Njtrk";
    std::string svpttJstr  = JSVstr[ijsv] + "-" + m_nJSVkin[1] + "-pt";
    std::string svtrkt     = std::to_string( m_nJSVtrk[1] );
    std::string svtrktJstr = svtrkt + "-" + JSVstr[ijsv] + "-Njtrk";
    hEJstr   .push_back( baseJstr                      );
    hEJstr   .push_back( leadJstr                      );
    hEJstr   .push_back( tightptJstr                   );
    hEJstr   .push_back( leadJstr + " " + tightptJstr  );
    hEJstr   .push_back( tightetaJstr                  );
    hEJstr   .push_back( leadJstr + " " + tightetaJstr );
    hEJstr   .push_back( tightmJstr                    );
    hEJstr   .push_back( leadJstr + " " + tightmJstr   );
    hEJstr   .push_back( svptlJstr                     );
    hEJstr   .push_back( leadJstr + " " + svptlJstr    );
    hEJstr   .push_back( svtrklJstr                    );
    hEJstr   .push_back( leadJstr + " " + svtrklJstr   );
    hEJstr   .push_back( svpttJstr                     );
    hEJstr   .push_back( leadJstr + " " + svpttJstr    );
    hEJstr   .push_back( svtrktJstr                    );
    hEJstr   .push_back( leadJstr + " " + svtrktJstr   );
    if ( m_histoInfoSwitch->m_emergingJets || m_histoInfoSwitch->m_cutflow || m_histoInfoSwitch->m_abcdcutOnly ) {
      hJ    .push_back(              "LooseEmerging"   + JSV   [ijsv]       );
      hJ    .push_back( leadJ    +   "LooseEmerging"   + JSV   [ijsv]       );
      hJ    .push_back(              "TightEmerging"   + JSV   [ijsv]       );
      hJ    .push_back( leadJ    +   "TightEmerging"   + JSV   [ijsv]       );
      hJstr .push_back(            " Loose Emerging (" + JSVstr[ijsv] + ")" );
      hJstr .push_back( leadJstr + " Loose Emerging (" + JSVstr[ijsv] + ")" );
      hJstr .push_back(            " Tight Emerging (" + JSVstr[ijsv] + ")" );
      hJstr .push_back( leadJstr + " Tight Emerging (" + JSVstr[ijsv] + ")" );
    }
  }
  
  // number of jet types excluding truth matching
  m_nTypeBJs = hJ.size();
  
  // truth-(dark-)matched jets
  // --> dark = has truth match + dark match (highest pT w/in dR = 0.3), with dark also matched to truth match
  // --> need additional cut on dark matching; averaging 3/4 dark-matched lead jets (should be 2/4)
  if ( m_mc && m_histoInfoSwitch->m_jetTruth ) {
    std::vector<std::string> mJ    = { "DarkMatch",    "Nomatch"   };
    std::vector<std::string> mJstr = { "dark-matched", "unmatched" };
    std::vector<std::string> miJ, miJstr;
    for ( size_t ihj = 0; ihj != hJ.size(); ++ihj ) {
      miJ    .push_back( hJ    [ihj] );
      miJstr .push_back( hJstr [ihj] );
    }
    for ( size_t i = 0; i != mJ.size(); ++i ) {
      for ( size_t j = 0; j != miJ.size(); ++j ) {
	std::string mJs  = mJ  [i];
	std::string tmpj = miJ [j] + mJs; tmpj[0] = tolower(tmpj[0]);
	std::string tmpjstr = miJstr [j];
	if ( !tmpjstr.empty() ) tmpjstr += " ";
	tmpjstr += mJstr[i];
	hJ    .push_back( tmpj    );
	hJstr .push_back( tmpjstr );
      }
    }
  }

  // number of jet types including truth matching
  m_nTypeJs = hJ.size();


  // --> truth particles
  std::vector<std::string> hTP, hTPstr;
  hTP    .push_back( "Xd"              );
  hTPstr .push_back( "scalar mediator" );
  hTP    .push_back( "qd"              );
  hTPstr .push_back( "dark quark"      );
  hTP    .push_back( "pid"             );
  hTPstr .push_back( "dark pion"       );
  hTP    .push_back( "rhod"            );
  hTPstr .push_back( "dark rho"        );
  m_nTypeTPs = hTP.size();


  // --> tracks
  std::vector<std::string> hTrk, hTrkstr;
  hTrk    .push_back( ""                            );
  hTrkstr .push_back( ""                            );
  hTrk    .push_back( "LRT"                         );
  hTrkstr .push_back( "LRT"                         );
  hTrk    .push_back( "sel"                         );
  hTrkstr .push_back( "selected"                    );
  hTrk    .push_back( "assoc"                       );
  hTrkstr .push_back( "associated"                  );
  hTrk    .push_back( "SV"                          );
  hTrkstr .push_back( "secondary vertex"            );
  hTrk    .push_back( "lgoodSV"                     );
  hTrkstr .push_back( "loose good secondary vertex" );
  hTrk    .push_back( "mgoodSV"                     );
  hTrkstr .push_back( "mid good secondary vertex"   );
  hTrk    .push_back( "tgoodSV"                     );
  hTrkstr .push_back( "tight good secondary vertex" );
  m_nTypeTrks = hTrk.size();


  // --> truth vertices
  std::vector<std::string> hLLP, hLLPstr;
  // dark pion decay
  std::string pidLLP    = "DarkPion";
  std::string pidLLPstr = "dark pion,";
  // k-short decay
  std::string ksLLP     = "Kshort";
  std::string ksLLPstr  = "k-short,";
  if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_darkPions ) {
    hLLP    .push_back( pidLLP    );
    hLLPstr .push_back( pidLLPstr );
  }
  if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_kshorts   ) {
    hLLP    .push_back( ksLLP     );
    hLLPstr .push_back( ksLLPstr  );
  }
  m_nTypeLLPs = hLLP.size();
  

  // --> secondary vertices
  std::vector<std::string> hDV,  hDVstr;
  std::vector<std::string> hJDV, hJDVstr;
  // base vertices (bare or clean or filtered or custom-trimmed --> starting point for all further cuts)
  // --> no material map veto applied here, but applied for every other type of DV...
  std::string baseDV    = "";
  std::string baseDVstr = base_dv.name + ",";
  if      ( base_dv.type == EJsHelper::BARE     ) baseDV = "Bare";
  else if ( base_dv.type == EJsHelper::CLEAN    ) baseDV = "Clean";
  else if ( base_dv.type == EJsHelper::FILTERED ) baseDV = "Filtered";
  else if ( base_dv.type == EJsHelper::TRIMMED  ) baseDV = "Trimmed";
  if ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_baseVerts    ) {
    hDV     .push_back( baseDV    );
    hDVstr  .push_back( baseDVstr );
  }
  if ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_baseJetVerts ) {
    hJDV    .push_back( baseDV    );
    hJDVstr .push_back( baseDVstr );
  }
  // vertices passing material map veto
  std::string matmapDV    = "MatMap";
  std::string matmapDVstr = "material-veto,";
  if ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_matmapVerts    ) {
    hDV     .push_back( matmapDV    );
    hDVstr  .push_back( matmapDVstr );
  }
  if ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_matmapJetVerts ) {
    hJDV    .push_back( matmapDV    );
    hJDVstr .push_back( matmapDVstr );
  }
  // vertices passing fiducial volume cuts
  std::string fidDV    = "Fiduc";
  std::string fidDVstr = "fiducial-volume,";
  if ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_fiducVerts    ) {
    hDV     .push_back( fidDV    );
    hDVstr  .push_back( fidDVstr );
  }
  if ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_fiducJetVerts ) {
    hJDV    .push_back( fidDV    );
    hJDVstr .push_back( fidDVstr );
  }
  // vertices passing quality of fit cut
  std::string chi2DV    = "Chi2";
  std::string chi2DVstr = "chi2/ndof,";
  if ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_chi2Verts    ) {
    hDV     .push_back( chi2DV    );
    hDVstr  .push_back( chi2DVstr );
  }
  if ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_chi2JetVerts ) {
    hJDV    .push_back( chi2DV    );
    hJDVstr .push_back( chi2DVstr );
  }
  // vertices w/ k-short mass window removed
  std::string ksmDV    = "Ksm";
  std::string ksmDVstr = "k-short-mass,";
  if ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_ksmVerts    ) {
    hDV    .push_back( ksmDV    );
    hDVstr .push_back( ksmDVstr );
  }
  if ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_ksmJetVerts ) {
    hJDV    .push_back( ksmDV    );
    hJDVstr .push_back( ksmDVstr );
  }
  // vertices passing low-pt cut
  std::string ptDV    = "Pt";
  std::string ptDVstr = "pt,";
  if ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_ptVerts    ) {
    hDV     .push_back( ptDV    );
    hDVstr  .push_back( ptDVstr );
  }
  if ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_ptJetVerts ) {
    hJDV    .push_back( ptDV    );
    hJDVstr .push_back( ptDVstr );
  }
  // vertices pass min-d0 cut
  // --> add max/sum-d0 (wrt SV) cuts if necessary...
  std::string mind0DV    = "Mind0";
  std::string mind0DVstr = "min-d0,";
  if ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_d0Verts    ) {
    hDV     .push_back( mind0DV    );
    hDVstr  .push_back( mind0DVstr );
  }
  if ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_d0JetVerts ) {
    hJDV    .push_back( mind0DV    );
    hJDVstr .push_back( mind0DVstr );
  }
  // vertices passing min-z0 cut
  // --> add max/sum-z0 (wrt SV) cuts if necessary...
  std::string minz0DV    = "Minz0";
  std::string minz0DVstr = "min-z0,";
  if ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_z0Verts    ) {
    hDV     .push_back( minz0DV    );
    hDVstr  .push_back( minz0DVstr );
  }
  if ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_z0JetVerts ) {
    hJDV    .push_back( minz0DV    );
    hJDVstr .push_back( minz0DVstr );
  }
  // vertices passing min-sqrterr-d0/z0 cut
  // --> add max/sum-sqrterr-d0/z0 (wrt SV) cuts if necessary...
  std::string minsqerrd0DV    = "Minsqerrd0";
  std::string minsqerrz0DV    = "Minsqerrz0";
  std::string minsqerrd0DVstr = "min-sqrt-d0-error,";
  std::string minsqerrz0DVstr = "min-sqrt-z0-error,";
  if ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_d0z0ErrVerts    ) {
    hDV     .push_back( minsqerrd0DV    );
    hDV     .push_back( minsqerrz0DV    );
    hDVstr  .push_back( minsqerrd0DVstr );
    hDVstr  .push_back( minsqerrz0DVstr );
  }
  if ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_d0z0ErrJetVerts ) {
    hJDV    .push_back( minsqerrd0DV    );
    hJDV    .push_back( minsqerrz0DV    );
    hJDVstr .push_back( minsqerrd0DVstr );
    hJDVstr .push_back( minsqerrz0DVstr );
  }
  // vertices by (leading) jets -- skip for jet DVs
  std::string jDV     = "ByJet";
  std::string ljDV    = "ByNJet";
  std::string jDVstr  = "by-jet,";
  std::string ljDVstr = "by-N-lead-jet,";
  if ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_byJetVerts ) {
    hDV    .push_back( jDV     );
    hDV    .push_back( ljDV    );
    hDVstr .push_back( jDVstr  );
    hDVstr .push_back( ljDVstr );
  }

  // number of individual (jet) DV cuts
  m_nType1DVs  = hDV .size();
  m_nType1JDVs = hJDV.size();
  
  // --> "good" DVs -- tentatively = combo of all above cuts
  std::vector<std::string> hGDVstr;
  hGDVstr .push_back( baseDVstr       );
  hGDVstr .push_back( matmapDVstr     );
  hGDVstr .push_back( fidDVstr        );
  hGDVstr .push_back( chi2DVstr       );
  hGDVstr .push_back( ksmDVstr        );
  hGDVstr .push_back( ptDVstr         );
  hGDVstr .push_back( mind0DVstr      );
  hGDVstr .push_back( minz0DVstr      );
  hGDVstr .push_back( minsqerrd0DVstr );
  hGDVstr .push_back( minsqerrz0DVstr );
  hGDVstr .push_back( jDVstr          );
  hGDVstr .push_back( ljDVstr         );
  for ( size_t isdv = 0; isdv != hSgnlDV.size(); ++isdv ) {
    hDV     .push_back( "ByNJet"         + hSgnlDV    [isdv] ); // test ByJet
    hJDV    .push_back(                    hSgnlDV    [isdv] );
    hDVstr  .push_back( "by-N-lead-jet " + hSgnlDVstr [isdv] ); // test by-jet
    hJDVstr .push_back(                    hSgnlDVstr [isdv] );
  }

  // number of (jet) DV types excluding truth matching
  m_nTypeBDVs  = hDV .size();
  m_nTypeBJDVs = hJDV.size();

  // truth-matched vertices (testing matching criteria)  
  // --> initial matching criteria (v0): match score > 0; no requirement on no. / type of matches (may be matched to multiple llps)
  // --> --> test other criteria: additional distance-based requirement; require single match or llp type
  if ( m_mc ) {
    //std::vector<std::string> mDV     = { "DarkPion",   "Kshort",   "Nomatch"    };
    //std::vector<std::string> mDVstr  = { "dark pion,", "k-short,", "unmatched," };
    std::vector<std::string> mDV     = { "DarkPion"   };
    std::vector<std::string> mDVstr  = { "dark pion," };
    if ( m_histoInfoSwitch->m_vtxTruth ) {
      std::vector<std::string> miDV, miDVstr;
      for ( size_t ihdv = 0; ihdv != hDV.size(); ++ihdv ) {
	miDV    .push_back( hDV    [ihdv] );
	miDVstr .push_back( hDVstr [ihdv] );
      }
      for ( size_t i = 0; i != mDV.size(); ++i ) {
	for ( size_t j = 0; j != miDV.size(); ++j ) {
	  std::string mDVs  = mDV  [i];
	  std::string tmpdv = miDV [j];
	  if ( tmpdv == baseDV ) tmpdv = "";
	  tmpdv += mDVs; tmpdv[0] = tolower(tmpdv[0]);
	  std::string tmpdvstr = miDVstr [j];
	  if ( tmpdvstr == baseDVstr ) tmpdvstr  = ",";
	  tmpdvstr.pop_back();
	  if ( !tmpdvstr.empty()     ) tmpdvstr += " ";
	  tmpdvstr += mDVstr[i];
	  hDV    .push_back( tmpdv    );
	  hDVstr .push_back( tmpdvstr );
	}
      }
    }
    if ( m_histoInfoSwitch->m_jetVtxTruth ) {
      std::vector<std::string> miJDV, miJDVstr;
      for ( size_t ihjdv = 0; ihjdv != hJDV.size(); ++ihjdv ) {
	miJDV    .push_back( hJDV    [ihjdv] );
	miJDVstr .push_back( hJDVstr [ihjdv] );
      }
      for ( size_t i = 0; i != mDV.size(); ++i ) {
	for ( size_t j = 0; j != miJDV.size(); ++j ) {
	  std::string mDVs  = mDV   [i];
	  std::string tmpdv = miJDV [j];
	  if ( tmpdv == baseDV ) tmpdv = "";
	  tmpdv += mDVs; tmpdv[0] = tolower(tmpdv[0]);
	  std::string tmpdvstr = miJDVstr [j];
	  if ( tmpdvstr == baseDVstr ) tmpdvstr  = ",";
	  tmpdvstr.pop_back();
	  if ( !tmpdvstr.empty()     ) tmpdvstr += " ";
	  tmpdvstr += mDVstr[i];
	  hJDV    .push_back( tmpdv    );
	  hJDVstr .push_back( tmpdvstr );
	}
      }
    }
  }

  // number of (jet) DV types including truth matching
  m_nTypeDVs  = hDV .size();
  m_nTypeJDVs = hJDV.size();


  // ntuple cutflows
  for ( size_t inchist = 0; inchist != m_ntupCutHists.size(); ++inchist ) {
    TH1F* cuthist = m_ntupCutHists[inchist];
    std::string cutname = cuthist->GetName();
    if ( cutname == "cutflow" ) {
      int    cutbin         = cuthist->GetXaxis()->FindBin( "EJsAna" );
      double cutbin_content = cuthist->GetBinContent( cutbin );
      m_ntupcut_signal_full   .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( "all"                          ) ) );
      m_ntupcut_signal_full   .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( "init"                         ) ) );
      if ( !m_mc ) {
	m_ntupcut_signal_full .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( "GRL"                          ) ) );
	m_ntupcut_signal_full .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( "LAr"                          ) ) );
	m_ntupcut_signal_full .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( "tile"                         ) ) );
	m_ntupcut_signal_full .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( "SCT"                          ) ) );
	m_ntupcut_signal_full .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( "core"                         ) ) );
      }
      m_ntupcut_signal_full   .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( "JetCleaning"                  ) ) );
      m_ntupcut_signal_full   .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( "NPV"                          ) ) );
      m_ntupcut_signal_full   .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( "Trigger"                      ) ) );
      m_ntupcut_signal_full   .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( ( "JetSelect_AntiKt4" + m_jetStr ).c_str() ) ) );
      m_ntupcut_signal_full   .push_back( cuthist->GetBinContent( cuthist->GetXaxis()->FindBin( "EJsAna"                       ) ) );
    }
    if ( cutname == "cutflow_ejs_signal" ) {
      for ( size_t icutsig = 0; icutsig != cuthist->GetNbinsX(); ++icutsig )
	m_ntupcut_signal .push_back( cuthist->GetBinContent( icutsig+1 ) );
    }
  }
  

  // loop over regions + book histograms
  for ( size_t ireg = 0; ireg != regions.size(); ++ireg ) {
    const EJsHelper::Region region = regions[ireg];
    const std::string       name   = m_name + outFileName + "/" + region.name + "/";

    // initialize count vectors
    m_nEntries                  .push_back( 0 );
    m_nWeightedEntries          .push_back( 0 );

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
    if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
      // event info: pileup
      if ( m_histoInfoSwitch->m_pileup ) {
	h_npv       .push_back( book( name, "nPV",       "n primary vertices",              50, 0, 50 ) );
	h_actualMu  .push_back( book( name, "actualMu",  "actual interactions / crossing",  90, 0, 90 ) );
	h_averageMu .push_back( book( name, "averageMu", "average interactions / crossing", 90, 0, 90 ) );
	
	h_corrActualMu
	  .push_back( book( name, "corrActualMu",       "corrected actual interactions / crossing",           90, 0, 90 ) );
	h_corrAverageMu
	  .push_back( book( name, "corrAverageMu",      "corrected average interactions / crossing",          90, 0, 90 ) );
	h_corrScaleActualMu
	  .push_back( book( name, "corrScaleActualMu",  "corrected + scaled actual interactions / crossing",  90, 0, 90 ) );
	h_corrScaleAverageMu
	  .push_back( book( name, "corrScaleAverageMu", "corrected + scaled average interactions / crossing", 90, 0, 90 ) );
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
    } // end if not abcdcutOnly 
    // // event info: orphan pt
    // h_evt_truthPartPtSum
    //   .push_back( book( name, "evt_truthPartPtSum",            "truth particle sum-p{T} [GeV]",              100, 0, 7500 ) );
    // h_evt_truthPartDarkPtSum
    //   .push_back( book( name, "evt_truthPartDarkPtSum",        "dark particle sum-p{T} [GeV]",               100, 0, 7500 ) );
    // h_evt_truthJetConstitPtSum
    //   .push_back( book( name, "evt_truthJetConstitPtSum",      "truth jet constituent sum-p{T} [GeV]",       100, 0, 7500 ) );
    // h_evt_tightTruthJetConstitPtSum
    //   .push_back( book( name, "evt_tightTruthJetConstitPtSum", "tight truth jet constituent sum-p{T} [GeV]", 100, 0, 7500 ) );
    // h_evt_darkJetConstitPtSum
    //   .push_back( book( name, "evt_darkJetConstitPtSum",       "dark jet constituent sum-p{T} [GeV]",        100, 0, 3750 ) );
    // h_evt_tightDarkJetConstitPtSum
    //   .push_back( book( name, "evt_tightDarkJetConstitPtSum",  "tight dark jet constituent sum-p{T} [GeV]",  100, 0, 3750 ) );
    // h_orphanPt
    //   .push_back( book( name, "orphanPt",                      "orphan p_{T} [GeV]",                         100, 0, 3000 ) );
    // h_tightOrphanPt
    //   .push_back( book( name, "tightOrphanPt",                 "tight orphan p_{T} [GeV]",                   100, 0, 3000 ) );
    // h_darkOrphanPt
    //   .push_back( book( name, "darkOrphanPt",                  "dark orphan p_{T} [GeV]",                    100, 0, 6000 ) );
    // h_tightDarkOrphanPt
    //   .push_back( book( name, "tightDarkOrphanPt",             "tight dark orphan p_{T} [GeV]",              100, 0, 6000 ) );


    if ( m_mc ) {
      // --- TRUTH JETS --- //
      std::vector<TH1F*> h_tj_n;
      std::vector<TH1F*> h_tj_pt;
      std::vector<TH1F*> h_tj_pt_s;
      std::vector<TH1F*> h_tj_eta;
      std::vector<TH1F*> h_tj_phi;
      std::vector<TH1F*> h_tj_E;
      std::vector<TH1F*> h_tj_M;
      std::vector<TH1F*> h_tj_rapid;
      std::vector<TH1F*> h_tj_girth;
      std::vector<TH1F*> h_tj_nConstit;
      std::vector<TH1F*> h_tj_px;
      std::vector<TH1F*> h_tj_py;
      std::vector<TH1F*> h_tj_pz;
      std::vector<TH1F*> h_tj_Et;
      std::vector<TH1F*> h_tj_Et_s;
      std::vector<std::vector<TH1F*>> h_tj_nllpdv;
      std::vector<std::vector<TH1F*>> h_tj_llpdv_dR;
      std::vector<std::vector<TH1F*>> h_tj_llpdv_ndesc;
      std::vector<std::vector<TH1F*>> h_tj_llpdv_z;
      std::vector<std::vector<TH1F*>> h_tj_llpdv_r;
      std::vector<std::vector<TH1F*>> h_tj_nllptrk;
      std::vector<std::vector<TH1F*>> h_tj_llptrk_dR;
      std::vector<std::vector<TH1F*>> h_tj_llptrk_z0;
      std::vector<std::vector<TH1F*>> h_tj_llptrk_d0;
      for ( size_t i = 0; i != hTJ.size(); ++i ) {
	std::string htj     = hTJ    [i] + "TruthJet"; htj[0] = tolower(htj[0]);
	std::string htjstr  = hTJstr [i]; if ( !htjstr.empty() ) htjstr += " ";
	htjstr += "truth jet";
	int ntj = 25;
	if ( i % 2 ) ntj = 10;
	h_tj_n          .push_back( book( name, htj + "_n",        "n " + htjstr,              ntj,     0,  ntj ) );
	if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
	  h_tj_pt       .push_back( book( name, htj + "_pt",       htjstr + " p_{T} [GeV]",    100,     0, 1500 ) );
	  h_tj_pt_s     .push_back( book( name, htj + "_pt_s",     htjstr + " p_{T} [GeV]",    100,     0,  500 ) );
	  h_tj_eta      .push_back( book( name, htj + "_eta",      htjstr + " eta",            100,    -3,    3 ) );
	  h_tj_phi      .push_back( book( name, htj + "_phi",      htjstr + " phi",            100,  -3.5,  3.5 ) );
	  h_tj_E        .push_back( book( name, htj + "_E",        htjstr + " energy [GeV]",   100,     0, 2500 ) );
	  h_tj_M        .push_back( book( name, htj + "_M",        htjstr + " mass [GeV]",     100,     0,  300 ) );
	  h_tj_rapid    .push_back( book( name, htj + "_rapid",    htjstr + " rapidity",       100,    -3,    3 ) );
	  h_tj_girth    .push_back( book( name, htj + "_girth",    htjstr + " girth",          100,     0, 0.35 ) );
	  h_tj_nConstit .push_back( book( name, htj + "_nConstit", "n "+htjstr+" constituents",100,     0,  200 ) );
	  // truth jets: extra kinematics
	  if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_tjet ) {
	    h_tj_px     .push_back( book( name, htj + "_px",       htjstr + " p_{x} [GeV]",    100, -1500, 1500 ) );
	    h_tj_py     .push_back( book( name, htj + "_py",       htjstr + " p_{y} [GeV]",    100, -1500, 1500 ) );
	    h_tj_pz     .push_back( book( name, htj + "_pz",       htjstr + " p_{z} [GeV]",    100, -2500, 2500 ) );
	    h_tj_Et     .push_back( book( name, htj + "_Et",       htjstr + " E_{T} [GeV]",    100,     0, 1500 ) );
	    h_tj_Et_s   .push_back( book( name, htj + "_Et_s",     htjstr + " E_{T} [GeV]",    100,     0,  500 ) );
	  }
	  // loop over matched LLP types
	  std::vector<TH1F*> h_tj_nllp;
	  std::vector<TH1F*> h_tj_llp_dR;
	  std::vector<TH1F*> h_tj_llp_ndesc;
	  std::vector<TH1F*> h_tj_llp_z;
	  std::vector<TH1F*> h_tj_llp_r;
	  std::vector<TH1F*> h_tj_nllpt;
	  std::vector<TH1F*> h_tj_llpt_dR;
	  std::vector<TH1F*> h_tj_llpt_z0;
	  std::vector<TH1F*> h_tj_llpt_d0;
	  for ( size_t j = 0; j != hLLP.size(); ++j ) {
	    std::string htv      = hLLP[j] + "TV";  htv[0] = tolower(htv[0]);
	    std::string htjtv    = htj + "_" + htv;
	    std::string hvstr    = hLLPstr[j]; hvstr.pop_back();
	    std::string htvstr   = "matched " + hvstr + " decay vertex";
	    std::string htvstrpl = "matched " + hvstr + " decay vertices";
	    std::string htjtvstr = htjstr + " " + htvstr;
	    std::string htp      = hLLP[j] + "Trk"; htp[0] = tolower(htv[0]);
	    std::string htjtp    = htj + "_" + htp;
	    std::string htpstr   = "matched " + hvstr + " truth track";
	    std::string htjtpstr = htjstr + " " + htpstr;
	    h_tj_nllp      .push_back( book( name, htj   + "_n" + htv, "n " +htvstrpl+ " per " + htjstr,  15,     0,   15 ) );
	    h_tj_llp_dR    .push_back( book( name, htjtv + "_dR",      htjstr + " - " + htvstr + " dR",  100,     0,  0.6 ) );
	    h_tj_llp_ndesc .push_back( book( name, htjtv + "_nDesc",   htjtvstr + " n descendants",       20,     0,   20 ) );
	    if ( m_histoInfoSwitch->m_tjetVerts ) {
	      h_tj_llp_z   .push_back( book( name, htjtv + "_z",       htjtvstr + " z-pos [mm]",         100, -3000, 3000 ) );
	      h_tj_llp_r   .push_back( book( name, htjtv + "_r",       htjtvstr + " r-pos [mm]",         100,     0,  600 ) ); 
	    }
	    h_tj_nllpt     .push_back( book( name, htj   + "_n" + htp, "n " + htpstr + "s per " + htjstr, 40,     0,   40 ) );
	    h_tj_llpt_dR   .push_back( book( name, htjtp + "_dR",      htjstr + " - " + htpstr + " dR",  100,     0,  0.6 ) );
	    if ( m_histoInfoSwitch->m_tjetTrks ) {
	      h_tj_llpt_z0 .push_back( book( name, htjtp + "_z0",      htjtpstr + " z0 [mm]",            100, -1500, 1500 ) );
	      h_tj_llpt_d0 .push_back( book( name, htjtp + "_d0",      htjtpstr + " d0 [mm]",            100,  -300,  300 ) ); 
	    }
	  }
	  h_tj_nllpdv      .push_back( h_tj_nllp      );
	  h_tj_llpdv_dR    .push_back( h_tj_llp_dR    );
	  h_tj_llpdv_ndesc .push_back( h_tj_llp_ndesc );
	  if ( m_histoInfoSwitch->m_tjetVerts ) {
	    h_tj_llpdv_z   .push_back( h_tj_llp_z     );
	    h_tj_llpdv_r   .push_back( h_tj_llp_r     ); 
	  }
	  h_tj_nllptrk     .push_back( h_tj_nllpt     );
	  h_tj_llptrk_dR   .push_back( h_tj_llpt_dR   );
	  if ( m_histoInfoSwitch->m_tjetTrks ) {
	    h_tj_llptrk_z0 .push_back( h_tj_llpt_z0   );
	    h_tj_llptrk_d0 .push_back( h_tj_llpt_d0   );
	  }
	  
	} // end if not abcdcutOnly
      } // end loop over truth jet types
      
      h_truthJet_n .push_back( h_tj_n );
      if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
	h_truthJet_pt          .push_back( h_tj_pt          );
	h_truthJet_pt_s        .push_back( h_tj_pt_s        );
	h_truthJet_eta         .push_back( h_tj_eta         );
	h_truthJet_phi         .push_back( h_tj_phi         );
	h_truthJet_E           .push_back( h_tj_E           );
	h_truthJet_M           .push_back( h_tj_M           );
	h_truthJet_rapid       .push_back( h_tj_rapid       );
	h_truthJet_girth       .push_back( h_tj_girth       );
	h_truthJet_nConstit    .push_back( h_tj_nConstit    );
	if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_tjet ) {
	  h_truthJet_px        .push_back( h_tj_px          );
	  h_truthJet_py        .push_back( h_tj_py          );
	  h_truthJet_pz        .push_back( h_tj_pz          );
	  h_truthJet_Et        .push_back( h_tj_Et          );
	  h_truthJet_Et_s      .push_back( h_tj_Et_s        );
	}
	h_truthJet_nllpdv      .push_back( h_tj_nllpdv      );
	h_truthJet_llpdv_dR    .push_back( h_tj_llpdv_dR    );
	h_truthJet_llpdv_ndesc .push_back( h_tj_llpdv_ndesc );
	if ( m_histoInfoSwitch->m_tjetVerts ) {
	  h_truthJet_llpdv_z   .push_back( h_tj_llpdv_z     );
	  h_truthJet_llpdv_r   .push_back( h_tj_llpdv_r     );
	}
	h_truthJet_nllptrk     .push_back( h_tj_nllptrk     );
	h_truthJet_llptrk_dR   .push_back( h_tj_llptrk_dR   );
	if ( m_histoInfoSwitch->m_tjetTrks ) {
	  h_truthJet_llptrk_z0 .push_back( h_tj_llptrk_z0   );
	  h_truthJet_llptrk_d0 .push_back( h_tj_llptrk_d0   );
	}					   
      }

      
      // --- TRUTH DARK JETS --- //
      // --> look at dark jets that are matched to truth jets
      std::vector<TH1F*> h_dj_n;
      std::vector<TH1F*> h_dj_pt;
      std::vector<TH1F*> h_dj_pt_s;
      std::vector<TH1F*> h_dj_eta;
      std::vector<TH1F*> h_dj_phi;
      std::vector<TH1F*> h_dj_E;
      std::vector<TH1F*> h_dj_M;
      std::vector<TH1F*> h_dj_rapid;
      std::vector<TH1F*> h_dj_girth;
      std::vector<TH1F*> h_dj_nConstit;
      std::vector<TH1F*> h_dj_px;
      std::vector<TH1F*> h_dj_py;
      std::vector<TH1F*> h_dj_pz;
      std::vector<TH1F*> h_dj_Et;
      std::vector<TH1F*> h_dj_Et_s;
      std::vector<std::vector<TH1F*>> h_dj_nllpdv;
      std::vector<std::vector<TH1F*>> h_dj_llpdv_dR;
      std::vector<std::vector<TH1F*>> h_dj_llpdv_ndesc;
      std::vector<std::vector<TH1F*>> h_dj_llpdv_z;
      std::vector<std::vector<TH1F*>> h_dj_llpdv_r;
      std::vector<std::vector<TH1F*>> h_dj_nllptrk;
      std::vector<std::vector<TH1F*>> h_dj_llptrk_dR;
      std::vector<std::vector<TH1F*>> h_dj_llptrk_z0;
      std::vector<std::vector<TH1F*>> h_dj_llptrk_d0;
      std::vector<int>   ndj   = { 50, 25 };
      std::vector<float> djeta = {  5,  3 };
      for ( size_t i = 0; i != hDJ.size(); ++i ) {
	std::string hdj     = hDJ    [i] + "DarkJet"; hdj[0] = tolower(hdj[0]);
	std::string hdjstr  = hDJstr [i]; if ( !hdjstr.empty() ) hdjstr += " ";
	hdjstr += "dark jet";
	h_dj_n          .push_back( book( name, hdj + "_n",        "n " + hdjstr,           ndj[i],       0,   ndj[i] ) );
	if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
	  h_dj_pt       .push_back( book( name, hdj + "_pt",       hdjstr + " p_{T} [GeV]",    100,        0,    1500 ) );
	  h_dj_pt_s     .push_back( book( name, hdj + "_pt_s",     hdjstr + " p_{T} [GeV]",    100,        0,     500 ) );
	  h_dj_eta      .push_back( book( name, hdj + "_eta",      hdjstr + " eta",            100,-djeta[i],djeta[i] ) );
	  h_dj_phi      .push_back( book( name, hdj + "_phi",      hdjstr + " phi",            100,     -3.5,     3.5 ) );
	  h_dj_E        .push_back( book( name, hdj + "_E",        hdjstr + " energy [GeV]",   100,        0,    2500 ) );
	  h_dj_M        .push_back( book( name, hdj + "_M",        hdjstr + " mass [GeV]",     100,        0,     300 ) );
	  h_dj_rapid    .push_back( book( name, hdj + "_rapid",    hdjstr + " rapidity",       100,-djeta[i],djeta[i] ) );
	  h_dj_girth    .push_back( book( name, hdj + "_girth",    hdjstr + " girth",          100,        0,    0.35 ) );
	  h_dj_nConstit .push_back( book( name, hdj + "_nConstit", "n "+hdjstr+" constituents", 35,        0,      35 ) );
	  // dark jets: extra kinematics
	  if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_djet ) {
	    h_dj_px     .push_back( book( name, hdj + "_px",       hdjstr + " p_{x} [GeV]",    100,    -1500,    1500 ) );
	    h_dj_py     .push_back( book( name, hdj + "_py",       hdjstr + " p_{y} [GeV]",    100,    -1500,    1500 ) );
	    h_dj_pz     .push_back( book( name, hdj + "_pz",       hdjstr + " p_{z} [GeV]",    100,    -2500,    2500 ) );
	    h_dj_Et     .push_back( book( name, hdj + "_Et",       hdjstr + " E_{T} [GeV]",    100,        0,    1500 ) );
	    h_dj_Et_s   .push_back( book( name, hdj + "_Et_s",     hdjstr + " E_{T} [GeV]",    100,        0,     500 ) );
	  }
	  // loop over matched LLP types
	  std::vector<TH1F*> h_dj_nllp;
	  std::vector<TH1F*> h_dj_llp_dR;
	  std::vector<TH1F*> h_dj_llp_ndesc;
	  std::vector<TH1F*> h_dj_llp_z;
	  std::vector<TH1F*> h_dj_llp_r;
	  std::vector<TH1F*> h_dj_nllpt;
	  std::vector<TH1F*> h_dj_llpt_dR;
	  std::vector<TH1F*> h_dj_llpt_z0;
	  std::vector<TH1F*> h_dj_llpt_d0;
	  for ( size_t j = 0; j != hLLP.size(); ++j ) {
	    std::string htv      = hLLP[j] + "TV"; htv[0] = tolower(htv[0]);
	    std::string hdjtv    = hdj + "_" + htv;
	    std::string hvstr    = hLLPstr[j]; hvstr.pop_back();
	    std::string htvstr   = "matched " + hvstr + " decay vertex";
	    std::string htvstrpl = "matched " + hvstr + " decay vertices";
	    std::string hdjtvstr = hdjstr + " " + htvstr;
	    std::string htp      = hLLP[j] + "Trk"; htp[0] = tolower(htv[0]);
	    std::string hdjtp    = hdj + "_" + htp;
	    std::string htpstr   = "matched " + hvstr + " truth track";
	    std::string hdjtpstr = hdjstr + " " + htpstr;
	    h_dj_nllp      .push_back( book( name, hdj   + "_n" + htv, "n " +htvstrpl+ " per " + hdjstr,  15,     0,   15 ) );
	    h_dj_llp_dR    .push_back( book( name, hdjtv + "_dR",      hdjstr + " - " + htvstr + " dR",  100,     0,  0.6 ) );
	    h_dj_llp_ndesc .push_back( book( name, hdjtv + "_nDesc",   hdjtvstr + " n descendants",       20,     0,   20 ) );
	    if ( m_histoInfoSwitch->m_djetVerts ) {
	      h_dj_llp_z   .push_back( book( name, hdjtv + "_z",       hdjtvstr + " z-pos [mm]",         100, -3000, 3000 ) );
	      h_dj_llp_r   .push_back( book( name, hdjtv + "_r",       hdjtvstr + " r-pos [mm]",         100,     0,  600 ) );
	    }
	    h_dj_nllpt     .push_back( book( name, hdj   + "_n" + htp, "n " + htpstr + "s per " + hdjstr, 40,     0,   40 ) );
	    h_dj_llpt_dR   .push_back( book( name, hdjtp + "_dR",      hdjstr + " - " + htpstr + " dR",  100,     0,  0.6 ) );
	    if ( m_histoInfoSwitch->m_djetTrks ) {
	      h_dj_llpt_z0 .push_back( book( name, hdjtp + "_z0",      hdjtpstr + " z0 [mm]",            100, -1500, 1500 ) );
	      h_dj_llpt_d0 .push_back( book( name, hdjtp + "_d0",      hdjtpstr + " d0 [mm]",            100,  -300,  300 ) ); 
	    }
	  }
	  h_dj_nllpdv      .push_back( h_dj_nllp      );
	  h_dj_llpdv_dR    .push_back( h_dj_llp_dR    );
	  h_dj_llpdv_ndesc .push_back( h_dj_llp_ndesc );
	  if ( m_histoInfoSwitch->m_djetVerts ) {
	    h_dj_llpdv_z   .push_back( h_dj_llp_z     );
	    h_dj_llpdv_r   .push_back( h_dj_llp_r     ); 
	  }
	  h_dj_nllptrk     .push_back( h_dj_nllpt     );
	  h_dj_llptrk_dR   .push_back( h_dj_llpt_dR   );
	  if ( m_histoInfoSwitch->m_djetTrks ) {
	    h_dj_llptrk_z0 .push_back( h_dj_llpt_z0   );
	    h_dj_llptrk_d0 .push_back( h_dj_llpt_d0   );
	  }

	} // end if not abcdcutOnly
      } // end loop over dark jet types
      
      h_darkJet_n .push_back( h_dj_n );
      if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
	h_darkJet_pt          .push_back( h_dj_pt          );
	h_darkJet_pt_s        .push_back( h_dj_pt_s        );
	h_darkJet_eta         .push_back( h_dj_eta         );
	h_darkJet_phi         .push_back( h_dj_phi         );
	h_darkJet_E           .push_back( h_dj_E           );
	h_darkJet_M           .push_back( h_dj_M           );
	h_darkJet_rapid       .push_back( h_dj_rapid       );
	h_darkJet_girth       .push_back( h_dj_girth       );
	h_darkJet_nConstit    .push_back( h_dj_nConstit    );
	if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_djet ) {
	  h_darkJet_px        .push_back( h_dj_px          );
	  h_darkJet_py        .push_back( h_dj_py          );
	  h_darkJet_pz        .push_back( h_dj_pz          );
	  h_darkJet_Et        .push_back( h_dj_Et          );
	  h_darkJet_Et_s      .push_back( h_dj_Et_s        );
	}
	h_darkJet_nllpdv      .push_back( h_dj_nllpdv      );
	h_darkJet_llpdv_dR    .push_back( h_dj_llpdv_dR    );
	h_darkJet_llpdv_ndesc .push_back( h_dj_llpdv_ndesc );
	if ( m_histoInfoSwitch->m_djetVerts ) {
	  h_darkJet_llpdv_z   .push_back( h_dj_llpdv_z     );
	  h_darkJet_llpdv_r   .push_back( h_dj_llpdv_r     );
	}
	h_darkJet_nllptrk     .push_back( h_dj_nllptrk     );
	h_darkJet_llptrk_dR   .push_back( h_dj_llptrk_dR   );
	if ( m_histoInfoSwitch->m_djetTrks ) {
	  h_darkJet_llptrk_z0 .push_back( h_dj_llptrk_z0   );
	  h_darkJet_llptrk_d0 .push_back( h_dj_llptrk_d0   );
	}
      }

    } // end if mc

      
      
    // --- RECO JETS --- //
    if ( !m_histoInfoSwitch->m_truthOnly ) {
      std::vector<TH1F*> h_j_n;
      std::vector<TH1F*> h_j_pt;
      std::vector<TH1F*> h_j_pt_s;
      std::vector<TH1F*> h_j_eta;
      std::vector<TH1F*> h_j_phi;
      std::vector<TH1F*> h_j_E;
      std::vector<TH1F*> h_j_M;
      std::vector<TH1F*> h_j_rapid;
      std::vector<TH1F*> h_j_nConstits;
      std::vector<TH1F*> h_j_px;
      std::vector<TH1F*> h_j_py;
      std::vector<TH1F*> h_j_pz;
      std::vector<TH1F*> h_j_Et;
      std::vector<TH1F*> h_j_Et_s;
      std::vector<TH1F*> h_j_timing;
      std::vector<TH1F*> h_j_timing_s;
      std::vector<TH1F*> h_j_sqrtTiming;
      std::vector<TH1F*> h_j_sqrtTiming_s;
      std::vector<TH1F*> h_j_LArQual;
      std::vector<TH1F*> h_j_LArQual_s;
      std::vector<TH1F*> h_j_sqrtLArQual;
      std::vector<TH1F*> h_j_sqrtLArQual_s;
      std::vector<TH1F*> h_j_HECQual;
      std::vector<TH1F*> h_j_HECQual_s;
      std::vector<TH1F*> h_j_sqrtHECQual;
      std::vector<TH1F*> h_j_sqrtHECQual_s;
      std::vector<TH1F*> h_j_LArQmean;
      std::vector<TH1F*> h_j_sqrtLArQmean;
      std::vector<TH1F*> h_j_n90Constits;
      std::vector<TH1F*> h_j_centroidR;
      std::vector<TH1F*> h_j_ootFrac5;
      std::vector<TH1F*> h_j_ootFrac5_s;
      std::vector<TH1F*> h_j_sqrtOotFrac5;
      std::vector<TH1F*> h_j_sqrtOotFrac5_s;
      std::vector<TH1F*> h_j_ootFrac10;
      std::vector<TH1F*> h_j_ootFrac10_s;
      std::vector<TH1F*> h_j_sqrtOotFrac10;
      std::vector<TH1F*> h_j_sqrtOotFrac10_s;
      std::vector<TH1F*> h_j_fracSampMax;
      std::vector<TH1F*> h_j_leadClustPt;
      std::vector<TH1F*> h_j_leadClustCtrL;
      std::vector<TH1F*> h_j_leadClust2ndL;
      std::vector<TH1F*> h_j_leadClust2ndR;
      std::vector<TH1F*> h_j_EMFrac;
      std::vector<TH1F*> h_j_HECFrac;
      std::vector<TH1F*> h_j_nonzeroHECFrac;
      std::vector<TH1F*> h_j_width;
      std::vector<TH1F*> h_j_ntrkPt10;
      std::vector<TH1F*> h_j_sumPtTrkPt10;
      std::vector<TH1F*> h_j_trkWidthPt10;
      std::vector<TH1F*> h_j_ntrkPt5;
      std::vector<TH1F*> h_j_sumPtTrkPt5;
      std::vector<TH1F*> h_j_trkWidthPt5;
      std::vector<TH1F*> h_j_JVF;
      std::vector<TH1F*> h_j_partonID;
      std::vector<std::vector<TH1F*>> h_j_nghosttrk;
      std::vector<std::vector<TH1F*>> h_j_ntrk;
      std::vector<std::vector<TH1F*>> h_j_trk_dR;
      std::vector<std::vector<TH1F*>> h_j_trk_minDR;
      std::vector<std::vector<TH1F*>> h_j_trk_maxDR;
      std::vector<std::vector<TH1F*>> h_j_trk_pt;
      std::vector<std::vector<TH1F*>> h_j_trk_d0;
      std::vector<std::vector<TH1F*>> h_j_trk_mind0;
      std::vector<std::vector<TH1F*>> h_j_trk_maxd0;
      std::vector<std::vector<TH1F*>> h_j_trk_sumd0;
      std::vector<std::vector<TH1F*>> h_j_trk_z0;
      std::vector<std::vector<TH1F*>> h_j_trk_minz0;
      std::vector<std::vector<TH1F*>> h_j_trk_maxz0;
      std::vector<std::vector<TH1F*>> h_j_trk_sumz0;
      std::vector<std::vector<TH1F*>> h_j_trk_errd0;
      std::vector<std::vector<TH1F*>> h_j_trk_minErrd0;
      std::vector<std::vector<TH1F*>> h_j_trk_maxErrd0;
      std::vector<std::vector<TH1F*>> h_j_trk_sumErrd0;
      std::vector<std::vector<TH1F*>> h_j_trk_errz0;
      std::vector<std::vector<TH1F*>> h_j_trk_minErrz0;
      std::vector<std::vector<TH1F*>> h_j_trk_maxErrz0;
      std::vector<std::vector<TH1F*>> h_j_trk_sumErrz0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtpt;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtd0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtmind0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtmaxd0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtsumd0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtz0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtminz0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtmaxz0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtsumz0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrterrd0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtminErrd0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtmaxErrd0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtsumErrd0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrterrz0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtminErrz0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtmaxErrz0;
      std::vector<std::vector<TH1F*>> h_j_trk_sqrtsumErrz0;
      std::vector<std::vector<TH1F*>> h_j_trk_nSCT;
      std::vector<std::vector<TH1F*>> h_j_trk_nPixel;
      std::vector<std::vector<TH1F*>> h_j_trk_nSi;
      std::vector<std::vector<TH1F*>> h_j_trk_nTRT;
      std::vector<std::vector<TH1F*>> h_j_ntrk_pt;
      std::vector<std::vector<TH1F*>> h_j_ntrk_eta;
      std::vector<std::vector<TH1F*>> h_j_ntrk_phi;
      std::vector<std::vector<TH1F*>> h_j_ntrk_m;
      std::vector<std::vector<TH1F*>> h_j_ntrk_sumPt;
      std::vector<std::vector<TH1F*>> h_j_ntrk_sqrtsumPt;
      std::vector<std::vector<TH1F*>> h_j_nsv;
      std::vector<std::vector<TH1F*>> h_j_sv_dR;
      std::vector<std::vector<TH1F*>> h_j_sv_minDR;
      std::vector<std::vector<TH1F*>> h_j_sv_maxDR;
      std::vector<std::vector<TH1F*>> h_j_sv_pt;
      std::vector<std::vector<TH1F*>> h_j_sv_Ht;
      std::vector<std::vector<TH1F*>> h_j_sv_H;
      std::vector<std::vector<TH1F*>> h_j_sv_sqrtpt;
      std::vector<std::vector<TH1F*>> h_j_sv_sqrtHt;
      std::vector<std::vector<TH1F*>> h_j_sv_sqrtH;
      std::vector<std::vector<TH1F*>> h_j_sv_mass;
      std::vector<std::vector<TH1F*>> h_j_sv_mass_s;
      std::vector<std::vector<TH1F*>> h_j_sv_ntrk;
      std::vector<std::vector<TH1F*>> h_j_sv_njtrk;
      std::vector<std::vector<TH1F*>> h_j_sv_z;
      std::vector<std::vector<TH1F*>> h_j_sv_minz;
      std::vector<std::vector<TH1F*>> h_j_sv_maxz;
      std::vector<std::vector<TH1F*>> h_j_sv_sumz;
      std::vector<std::vector<TH1F*>> h_j_sv_r;
      std::vector<std::vector<TH1F*>> h_j_sv_minr;
      std::vector<std::vector<TH1F*>> h_j_sv_maxr;
      std::vector<std::vector<TH1F*>> h_j_sv_sumr;
      std::vector<std::vector<TH1F*>> h_j_sv_chi2;
      std::vector<std::vector<TH1F*>> h_j_nsv_pt;
      std::vector<std::vector<TH1F*>> h_j_nsv_eta;
      std::vector<std::vector<TH1F*>> h_j_nsv_phi;
      std::vector<std::vector<TH1F*>> h_j_nsv_m;
      std::vector<std::vector<TH1F*>> h_j_nsv_sumPt;
      std::vector<std::vector<TH1F*>> h_j_nsv_sumHt;
      std::vector<std::vector<TH1F*>> h_j_nsv_sumH;
      std::vector<std::vector<TH1F*>> h_j_nsv_sqrtsumPt;
      std::vector<std::vector<TH1F*>> h_j_nsv_sqrtsumHt;
      std::vector<std::vector<TH1F*>> h_j_nsv_sqrtsumH;
      std::vector<std::vector<TH1F*>> h_j_nsv_sumMass;
      std::vector<std::vector<TH1F*>> h_j_nsv_sumMass_s;
      std::vector<std::vector<TH1F*>> h_j_nsv_ntrk;
      std::vector<std::vector<TH1F*>> h_j_nsv_njtrk;
      std::vector<std::vector<TH1F*>> h_nlj_pt;
      std::vector<std::vector<TH1F*>> h_nlj_pt_s;
      std::vector<std::vector<TH1F*>> h_nlj_eta;
      std::vector<std::vector<TH1F*>> h_nlj_phi;
      std::vector<std::vector<TH1F*>> h_nlj_E;
      std::vector<std::vector<TH1F*>> h_nlj_M;
      std::vector<std::vector<TH1F*>> h_nlj_rapid;
      std::vector<std::vector<TH1F*>> h_nlj_nConstits;
      std::vector<std::vector<TH1F*>> h_nlj_Et;
      std::vector<std::vector<TH1F*>> h_nlj_Et_s;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_ntrk;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_minDR;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_maxDR;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_mind0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_maxd0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sumd0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_minz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_maxz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sumz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_minErrd0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_maxErrd0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sumErrd0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_minErrz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_maxErrz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sumErrz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtmind0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtmaxd0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtsumd0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtminz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtmaxz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtsumz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtminErrd0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtmaxErrd0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtsumErrd0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtminErrz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtmaxErrz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_trk_sqrtsumErrz0;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_ntrk_pt;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_ntrk_eta;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_ntrk_phi;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_ntrk_m;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_ntrk_sumPt;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_ntrk_sqrtsumPt;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_sv_minDR;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_sv_maxDR;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_sv_minz;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_sv_maxz;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_sv_sumz;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_sv_minr;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_sv_maxr;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_sv_sumr;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_pt;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_eta;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_phi;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_m;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_sumPt;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_sumHt;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_sumH;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_sqrtsumPt;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_sqrtsumHt;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_sqrtsumH;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_sumMass;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_sumMass_s;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_ntrk;
      std::vector<std::vector<std::vector<TH1F*>> > h_nlj_nsv_njtrk;
      std::vector<TH1F*> h_jj_n;
      std::vector<TH1F*> h_jj_pt;
      std::vector<TH1F*> h_jj_eta;
      std::vector<TH1F*> h_jj_phi;
      std::vector<TH1F*> h_jj_m;
      std::vector<TH1F*> h_jj_sumPt;
      std::vector<TH1F*> h_jj_sumM;
      std::vector<TH1F*> h_jj_dR;
      std::vector<TH1F*> h_jj_avg_pt;
      std::vector<TH1F*> h_jj_avg_eta;
      std::vector<TH1F*> h_jj_avg_phi;
      std::vector<TH1F*> h_jj_avg_m;
      std::vector<TH1F*> h_jj_avg_sumPt;
      std::vector<TH1F*> h_jj_avg_sumM;
      std::vector<TH1F*> h_jj_avg_dR;
      std::vector<TH1F*> h_jj_max_pt;
      std::vector<TH1F*> h_jj_max_eta;
      std::vector<TH1F*> h_jj_max_phi;
      std::vector<TH1F*> h_jj_max_m;
      std::vector<TH1F*> h_jj_max_sumPt;
      std::vector<TH1F*> h_jj_max_sumM;
      std::vector<TH1F*> h_jj_max_dR;
      std::vector<TH1F*> h_jj_min_pt;
      std::vector<TH1F*> h_jj_min_eta;
      std::vector<TH1F*> h_jj_min_phi;
      std::vector<TH1F*> h_jj_min_m;
      std::vector<TH1F*> h_jj_min_sumPt;
      std::vector<TH1F*> h_jj_min_sumM;
      std::vector<TH1F*> h_jj_min_dR;
      std::vector<std::vector<TH1F*>> h_jj_max_ntrk;
      std::vector<std::vector<TH1F*>> h_jj_max_ntrk_pt;
      std::vector<std::vector<TH1F*>> h_jj_max_ntrk_eta;
      std::vector<std::vector<TH1F*>> h_jj_max_ntrk_phi;
      std::vector<std::vector<TH1F*>> h_jj_max_ntrk_m;
      std::vector<std::vector<TH1F*>> h_jj_max_ntrk_sumPt;
      std::vector<std::vector<TH1F*>> h_jj_max_ntrk_sumM;
      std::vector<std::vector<TH1F*>> h_jj_min_ntrk;
      std::vector<std::vector<TH1F*>> h_jj_min_ntrk_pt;
      std::vector<std::vector<TH1F*>> h_jj_min_ntrk_eta;
      std::vector<std::vector<TH1F*>> h_jj_min_ntrk_phi;
      std::vector<std::vector<TH1F*>> h_jj_min_ntrk_m;
      std::vector<std::vector<TH1F*>> h_jj_min_ntrk_sumPt;
      std::vector<std::vector<TH1F*>> h_jj_min_ntrk_sumM;
      std::vector<std::vector<TH1F*>> h_jj_max_nsv;
      std::vector<std::vector<TH1F*>> h_jj_max_nsv_pt;
      std::vector<std::vector<TH1F*>> h_jj_max_nsv_eta;
      std::vector<std::vector<TH1F*>> h_jj_max_nsv_phi;
      std::vector<std::vector<TH1F*>> h_jj_max_nsv_m;
      std::vector<std::vector<TH1F*>> h_jj_max_nsv_sumPt;
      std::vector<std::vector<TH1F*>> h_jj_max_nsv_sumM;
      std::vector<std::vector<TH1F*>> h_jj_min_nsv;
      std::vector<std::vector<TH1F*>> h_jj_min_nsv_pt;
      std::vector<std::vector<TH1F*>> h_jj_min_nsv_eta;
      std::vector<std::vector<TH1F*>> h_jj_min_nsv_phi;
      std::vector<std::vector<TH1F*>> h_jj_min_nsv_m;
      std::vector<std::vector<TH1F*>> h_jj_min_nsv_sumPt;
      std::vector<std::vector<TH1F*>> h_jj_min_nsv_sumM;
      std::vector<TH1F*> h_jj_maxpt_pt;
      std::vector<TH1F*> h_jj_maxpt_eta;
      std::vector<TH1F*> h_jj_maxpt_phi;
      std::vector<TH1F*> h_jj_maxpt_m;
      std::vector<TH1F*> h_jj_maxpt_sumPt;
      std::vector<TH1F*> h_jj_maxpt_sumM;
      std::vector<TH1F*> h_jj_maxpt_dR;
      std::vector<TH1F*> h_jj_minpt_pt;
      std::vector<TH1F*> h_jj_minpt_eta;
      std::vector<TH1F*> h_jj_minpt_phi;
      std::vector<TH1F*> h_jj_minpt_m;
      std::vector<TH1F*> h_jj_minpt_sumPt;
      std::vector<TH1F*> h_jj_minpt_sumM;
      std::vector<TH1F*> h_jj_minpt_dR;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk_pt;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk_eta;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk_phi;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk_m;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk_sumPt;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk_sumM;
      std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk;
      std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk_pt;
      std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk_eta;
      std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk_phi;
      std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk_m;
      std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk_sumPt;
      std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk_sumM;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv_pt;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv_eta;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv_phi;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv_m;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv_sumPt;
      std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv_sumM;
      std::vector<std::vector<TH1F*>> h_jj_minpt_nsv;
      std::vector<std::vector<TH1F*>> h_jj_minpt_nsv_pt;
      std::vector<std::vector<TH1F*>> h_jj_minpt_nsv_eta;
      std::vector<std::vector<TH1F*>> h_jj_minpt_nsv_phi;
      std::vector<std::vector<TH1F*>> h_jj_minpt_nsv_m;
      std::vector<std::vector<TH1F*>> h_jj_minpt_nsv_sumPt;
      std::vector<std::vector<TH1F*>> h_jj_minpt_nsv_sumM;
      std::vector<TH1F*> h_nj_pt;
      std::vector<TH1F*> h_nj_eta;
      std::vector<TH1F*> h_nj_phi;
      std::vector<TH1F*> h_nj_m;
      std::vector<TH1F*> h_nj_sumPt;
      std::vector<TH1F*> h_nj_sumM;
      std::vector<std::vector<TH1F*>> h_nj_ntrk;
      std::vector<std::vector<TH1F*>> h_nj_ntrk_pt;
      std::vector<std::vector<TH1F*>> h_nj_ntrk_eta;
      std::vector<std::vector<TH1F*>> h_nj_ntrk_phi;
      std::vector<std::vector<TH1F*>> h_nj_ntrk_m;
      std::vector<std::vector<TH1F*>> h_nj_ntrk_sumPt;
      std::vector<std::vector<TH1F*>> h_nj_ntrk_sumM;
      std::vector<std::vector<TH1F*>> h_nj_nsv;
      std::vector<std::vector<TH1F*>> h_nj_nsv_pt;
      std::vector<std::vector<TH1F*>> h_nj_nsv_eta;
      std::vector<std::vector<TH1F*>> h_nj_nsv_phi;
      std::vector<std::vector<TH1F*>> h_nj_nsv_m;
      std::vector<std::vector<TH1F*>> h_nj_nsv_sumPt;
      std::vector<std::vector<TH1F*>> h_nj_nsv_sumM;
      for ( size_t i = 0; i != hJ.size(); ++i ) {
	std::string jetHistNameUp = jetHistName; jetHistNameUp[0] = toupper(jetHistNameUp[0]);
	std::string hjName   = "";
	std::string hjString = "";
	if ( hJ [i].empty() )
	  hjName  = hJ[i] + jetHistName;
	else
	  hjName  = hJ[i] + jetHistNameUp;
	hjName[0] = tolower(hjName[0]);
	if ( hJstr[i].empty() ) hjString = hJstr[i];
	else                    hjString = hJstr[i] + " ";
	std::string hj     = hjName;
	std::string hjstr  = hjString + m_jetStr + " jet";
	std::string hjj    = hjName   + "_jj";
	std::string hjjstr = hjString + m_jetStr + " dijet";
	std::string hnj    = hjName   + "_Nj";
	std::string hnjstr = hjString + m_jetStr + " N-jet";

	int njet = 20;
	if ( hj.find("lead") != std::string::npos ) njet = 5;

	h_j_n           .push_back( book( name, hj + "_n",         "n " + hjstr + "s",       njet,     0, njet ) );
	if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
	  h_j_pt        .push_back( book( name, hj + "_pt",        hjstr + " p_{T} [GeV]",    100,     0, 1500 ) );
	  h_j_pt_s      .push_back( book( name, hj + "_pt_s",      hjstr + " p_{T} [GeV]",    100,     0,  500 ) );
	  h_j_eta       .push_back( book( name, hj + "_eta",       hjstr + " eta",            100,    -3,    3 ) );
	  h_j_phi       .push_back( book( name, hj + "_phi",       hjstr + " phi",            100,  -3.5,  3.5 ) );
	  h_j_E         .push_back( book( name, hj + "_E",         hjstr + " energy [GeV]",   100,     0, 2500 ) );
	  h_j_M         .push_back( book( name, hj + "_M",         hjstr + " mass [GeV]",     100,     0,  250 ) );
	  h_j_rapid     .push_back( book( name, hj + "_rapid",     hjstr + " rapidity",       100,    -3,    3 ) );
	  h_j_nConstits .push_back( book( name, hj + "_nConstits", hjstr + " n constituents", 100,     0,   60 ) );
	  // jets: extra kinematics
	  if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	    h_j_px      .push_back( book( name, hj + "_px",        hjstr + " p_{x} [GeV]",    100, -1500, 1500 ) );
	    h_j_py      .push_back( book( name, hj + "_py",        hjstr + " p_{y} [GeV]",    100, -1500, 1500 ) );
	    h_j_pz      .push_back( book( name, hj + "_pz",        hjstr + " p_{z} [GeV]",    100, -2500, 2500 ) );
	    h_j_Et      .push_back( book( name, hj + "_Et",        hjstr + " E_{T} [GeV]",    100,     0, 1500 ) );
	    h_j_Et_s    .push_back( book( name, hj + "_Et_s",      hjstr + " E_{T} [GeV]",    100,     0,  500 ) );
	  }
	  // jets: calo / cluster (quality) info
	  if ( m_histoInfoSwitch->m_jetCalo ) {
	    h_j_timing         .push_back( book( name, hj + "_timing",         hjstr + " abs timing [ns]",                100,   0,   25 ) );
	    h_j_timing_s       .push_back( book( name, hj + "_timing_s",       hjstr + " abs timing [ns]",                100,   0,    5 ) );
	    h_j_sqrtTiming     .push_back( book( name, hj + "_sqrtTiming",     hjstr + " sqrt timing [ns]",               100,   0,    5 ) );
	    h_j_sqrtTiming_s   .push_back( book( name, hj + "_sqrtTiming_s",   hjstr + " sqrt timing [ns]",               100,   0,  2.5 ) );
	    h_j_LArQual        .push_back( book( name, hj + "_LArQual",        hjstr + " LAr quality",                    100,   0,    1 ) );
	    h_j_LArQual_s      .push_back( book( name, hj + "_LArQual_s",      hjstr + " LAr quality",                    100,   0,  0.2 ) );
	    h_j_sqrtLArQual    .push_back( book( name, hj + "_sqrtLArQual",    hjstr + " sqrt LAr quality",               100,   0,    1 ) );
	    h_j_sqrtLArQual_s  .push_back( book( name, hj + "_sqrtLArQual_s",  hjstr + " sqrt LAr quality",               100,   0, 0.45 ) );
	    h_j_HECQual        .push_back( book( name, hj + "_HECQual",        hjstr + " HEC quality",                    100,   0,    1 ) );
	    h_j_HECQual_s      .push_back( book( name, hj + "_HECQual_s",      hjstr + " HEC quality",                    100,   0,  0.1 ) );
	    h_j_sqrtHECQual    .push_back( book( name, hj + "_sqrtHECQual",    hjstr + " sqrt HEC quality",               100,   0,    1 ) );
	    h_j_sqrtHECQual_s  .push_back( book( name, hj + "_sqrtHECQual_s",  hjstr + " sqrt HEC quality",               100,   0,  0.3 ) );
	    h_j_LArQmean       .push_back( book( name, hj + "_LArQmean",       hjstr + " norm avg LAr quality",           100,   0, 0.06 ) );
	    h_j_sqrtLArQmean   .push_back( book( name, hj + "_sqrtLArQmean",   hjstr + " sqrt norm avg LAr quality",      100,   0, 0.25 ) );
	    h_j_n90Constits    .push_back( book( name, hj + "_n90Constits",    hjstr + " n clusters w/ >90% energy",       30,   0,   30 ) );
	    h_j_centroidR      .push_back( book( name, hj + "_centroidR",      hjstr + " weighted barycenter",            100,1500, 6500 ) );
	    h_j_ootFrac5       .push_back( book( name, hj + "_ootFrac5",       hjstr + " out-of-time >5ns fraction",      100,   0,    1 ) );
	    h_j_ootFrac5_s     .push_back( book( name, hj + "_ootFrac5_s",     hjstr + " out-of-time >5ns fraction",      100,   0,  0.5 ) );
	    h_j_sqrtOotFrac5   .push_back( book( name, hj + "_sqrtOotFrac5",   hjstr + " sqrt out-of-time >5ns fraction", 100,   0,    1 ) );
	    h_j_sqrtOotFrac5_s .push_back( book( name, hj + "_sqrtOotFrac5_s", hjstr + " sqrt out-of-time >5ns fraction", 100,   0,  0.7 ) );
	    h_j_ootFrac10      .push_back( book( name, hj + "_ootFrac10",      hjstr + " out-of-time >10ns fraction",     100,   0,    1 ) );
	    h_j_ootFrac10_s    .push_back( book( name, hj + "_ootFrac10_s",    hjstr + " out-of-time >10ns fraction",     100,   0, 0.35 ) );
	    h_j_sqrtOotFrac10  .push_back( book( name, hj + "_sqrtOotFrac10",  hjstr + " sqrt out-of-time >10ns fraction",100,   0,    1 ) );
	    h_j_sqrtOotFrac10_s.push_back( book( name, hj + "_sqrtOotFrac10_s",hjstr + " sqrt out-of-time >10ns fraction",100,   0,  0.6 ) );
	    h_j_fracSampMax    .push_back( book( name, hj + "_fracSampMax",    hjstr + " max energy frac per calo layer", 100,   0,    1 ) );
	    // --> look at fracSampMax in specific sampling layers...
	    h_j_leadClustPt    .push_back( book( name, hj + "_leadClustPt",   hjstr + " lead cluster p_{T} [GeV]",       100,   0,  750 ) );
	    h_j_leadClustCtrL  .push_back( book( name, hj + "_leadClustCtrL", hjstr + " lead cluster center lambda",     100,   0, 5000 ) );
	    h_j_leadClust2ndL  .push_back( book( name, hj + "_leadClust2ndL", hjstr + " lead cluster second lambda",     100,   0, 75e4 ) );
	    h_j_leadClust2ndR  .push_back( book( name, hj + "_leadClust2ndR", hjstr + " lead cluster second R",          100,   0,  5e4 ) );
	    h_j_EMFrac         .push_back( book( name, hj + "_EMFrac",        hjstr + " energy fraction in EM cal",      100,   0,  1.1 ) );
	    h_j_HECFrac        .push_back( book( name, hj + "_HECFrac",       hjstr + " energy fraction in HEC cal",     100,   0,    1 ) );
	    h_j_nonzeroHECFrac .push_back( book( name, hj + "_nonzeroHECFrac",hjstr + " nonzero energy fraction in HEC cal",100,0,    1 ) );
	    h_j_width          .push_back( book( name, hj + "_width",         hjstr + " width",                          100,   0,  0.3 ) );
	  }
	  // jets: PV track moments
	  if ( m_histoInfoSwitch->m_jetTrkMom ) {
	    h_j_ntrkPt10     .push_back( book( name, hj + "_ntrkPt10",     hjstr + " n p_{T}>1GeV ghost tracks",          50,  0,    50 ) );
	    h_j_sumPtTrkPt10 .push_back( book( name, hj + "_sumPtTrkPt10", hjstr + " p_{T}>1GeV ghost track sum-p_{T}",  100,  0,  1000 ) );
	    h_j_trkWidthPt10 .push_back( book( name, hj + "_trkWidthPt10", hjstr + " p_{T}>1GeV ghost track width",      100,  0,   0.5 ) );
	    h_j_ntrkPt5      .push_back( book( name, hj + "_ntrkPt5",      hjstr + " n p_{T}>.5GeV ghost tracks",         60,  0,    60 ) );
	    h_j_sumPtTrkPt5  .push_back( book( name, hj + "_sumPtTrkPt5",  hjstr + " p_{T}>.5GeV ghost track sum-p_{T}", 100,  0,  1000 ) );
	    h_j_trkWidthPt5  .push_back( book( name, hj + "_trkWidthPt5",  hjstr + " p_{T}>.5GeV ghost track width",     100,  0,   0.5 ) );
	    h_j_JVF          .push_back( book( name, hj + "_JVF",          hjstr + " jet vertex fraction (JVF)",         100,-0.1,  1.1 ) );
	  }
	  if ( m_mc )
	    h_j_partonID     .push_back( book( name, hj + "_partonID",     hjstr + " lead ghost parton pdgID",            22,  -1,    21 ) );
      
	  // jets: matched tracks
	  std::vector<TH1F*> h_j_ntrack;
	  std::vector<TH1F*> h_j_track_dR;
	  std::vector<TH1F*> h_j_track_minDR;
	  std::vector<TH1F*> h_j_track_maxDR;
	  std::vector<TH1F*> h_j_track_pt;
	  std::vector<TH1F*> h_j_track_d0;
	  std::vector<TH1F*> h_j_track_mind0;
	  std::vector<TH1F*> h_j_track_maxd0;
	  std::vector<TH1F*> h_j_track_sumd0;
	  std::vector<TH1F*> h_j_track_z0;
	  std::vector<TH1F*> h_j_track_minz0;
	  std::vector<TH1F*> h_j_track_maxz0;
	  std::vector<TH1F*> h_j_track_sumz0;
	  std::vector<TH1F*> h_j_track_errd0;
	  std::vector<TH1F*> h_j_track_minErrd0;
	  std::vector<TH1F*> h_j_track_maxErrd0;
	  std::vector<TH1F*> h_j_track_sumErrd0;
	  std::vector<TH1F*> h_j_track_errz0;
	  std::vector<TH1F*> h_j_track_minErrz0;
	  std::vector<TH1F*> h_j_track_maxErrz0;
	  std::vector<TH1F*> h_j_track_sumErrz0;
	  std::vector<TH1F*> h_j_track_sqrtpt;
	  std::vector<TH1F*> h_j_track_sqrtd0;
	  std::vector<TH1F*> h_j_track_sqrtmind0;
	  std::vector<TH1F*> h_j_track_sqrtmaxd0;
	  std::vector<TH1F*> h_j_track_sqrtsumd0;
	  std::vector<TH1F*> h_j_track_sqrtz0;
	  std::vector<TH1F*> h_j_track_sqrtminz0;
	  std::vector<TH1F*> h_j_track_sqrtmaxz0;
	  std::vector<TH1F*> h_j_track_sqrtsumz0;
	  std::vector<TH1F*> h_j_track_sqrterrd0;
	  std::vector<TH1F*> h_j_track_sqrtminErrd0;
	  std::vector<TH1F*> h_j_track_sqrtmaxErrd0;
	  std::vector<TH1F*> h_j_track_sqrtsumErrd0;
	  std::vector<TH1F*> h_j_track_sqrterrz0;
	  std::vector<TH1F*> h_j_track_sqrtminErrz0;
	  std::vector<TH1F*> h_j_track_sqrtmaxErrz0;
	  std::vector<TH1F*> h_j_track_sqrtsumErrz0;
	  std::vector<TH1F*> h_j_track_nSCT;
	  std::vector<TH1F*> h_j_track_nPixel;
	  std::vector<TH1F*> h_j_track_nSi;
	  std::vector<TH1F*> h_j_track_nTRT;
	  std::vector<TH1F*> h_j_ntrack_pt;
	  std::vector<TH1F*> h_j_ntrack_eta;
	  std::vector<TH1F*> h_j_ntrack_phi;
	  std::vector<TH1F*> h_j_ntrack_m;
	  std::vector<TH1F*> h_j_ntrack_sumPt;
	  std::vector<TH1F*> h_j_ntrack_sqrtsumPt;
	  std::vector<int>   nt_x2        = {   250,   200,    50,    10,    15,   15,   15,   15 };
	  std::vector<float> tpt_x2       = {  1250,   750,   250,    25,    75,   75,   75,   75 }; 
	  std::vector<float> td0_x2       = {   300,   300,   300,   300,   300,  300,  300,  300 };
	  std::vector<float> tmind0_x2    = {   0.1,   100,   100,   100,   100,  100,  100,  100 };
	  std::vector<float> tmaxd0_x2    = {   300,   300,   300,   300,   300,  300,  300,  300 };
	  std::vector<float> tsumd0_x2    = { 10000, 10000,  2500,   250,   500,  500,  500,  500 };
	  std::vector<float> tz0_x2       = {  1500,  1500,  1500,  1500,  1500, 1500, 1500, 1500 };
	  std::vector<float> tminz0_x2    = {    50,   250,   250,   250,   500,  500,  500,  500 };
	  std::vector<float> tmaxz0_x2    = {  1500,  1500,  1500,  1500,  1500, 1500, 1500, 1500 };
	  std::vector<float> tsumz0_x2    = { 75000, 75000, 10000,  1000,  2000, 2000, 2000, 2000 };
	  std::vector<float> terrd0_x2    = {    25,    10,     5,     5,     5,    5,    5,    5 };
	  std::vector<float> tminerrd0_x2 = {  0.05,   0.5,  0.75,     1,     1,    1,    5,    5 };
	  std::vector<float> tmaxerrd0_x2 = {    25,    15,     5,     3,     3,    3,    3,    3 };
	  std::vector<float> tsumerrd0_x2 = {    50,    25,    10,     5,     5,    5,    5,    5 };
	  std::vector<float> terrz0_x2    = {   500,    50,    25,    10,    10,   10,   10,   10 };
	  std::vector<float> tminerrz0_x2 = {  0.25,     5,   7.5,    10,    10,   10,   10,   10 };
	  std::vector<float> tmaxerrz0_x2 = {   500,    75,    30,    15,    15,   15,   15,   15 };
	  std::vector<float> tsumerrz0_x2 = {  1000,   150,    50,    20,    20,   20,   20,   20 };
	  std::vector<float> ntpt_x2      = {  3500,  1750,   500,    50,   150,  150,  150,  150 };
	  std::vector<float> ntm_x2       = {  1000,   500,   150,   7.5,    25,   25,   25,   25 };
	  std::vector<float> ntsumpt_x2   = {  3500,  1750,   500,    50,   150,  150,  150,  150 };
	  // loop over jet-matched track types
	  for ( size_t j = 0; j != hTrk.size(); ++j ) {
	    std::string htsubstr = "matched";
	    if ( !hTrkstr[j].empty() ) htsubstr += " ";
	    std::string ht       = hTrk[j] + "trk";
	    std::string hjt      = hj + "_" + ht;
	    std::string htstr    = htsubstr + hTrkstr[j] + " track";
	    std::string hjtstr   = hjstr + " " + htstr;
	    std::string hnt      = "n" + ht;
	    std::string hjnt     = hj + "_" + hnt;
	    std::string hntstr   = htsubstr + hTrkstr[j] + " n-track";
	    std::string hjntstr  = hjstr + " " + hntstr;
	    int nbin = nt_x2[j];
	    if ( j < 2 ) nbin = nt_x2[j] / 2;
	    h_j_ntrack              .push_back( book( name, hj + "_n" + ht,       "n " + htstr + "s per " + hjstr,  nbin, 0, nt_x2            [j] ) );
	    h_j_track_dR            .push_back( book( name, hjt  + "_dR",          hjstr   +" - "+ htstr + " dR",    100, 0,                  0.6 ) );
	    h_j_track_minDR         .push_back( book( name, hjt  + "_minDR",       hjstr   +" - "+ htstr + " min dR",100, 0,                  0.6 ) );
	    h_j_track_maxDR         .push_back( book( name, hjt  + "_maxDR",       hjstr   +" - "+ htstr + " max dR",100, 0,                  0.6 ) );
	    if ( m_histoInfoSwitch->m_jetTrks ) {
	      h_j_track_pt          .push_back( book( name, hjt  + "_pt",          hjtstr  + " p_{T} [GeV]",         100, 1, tpt_x2           [j] ) );
	      h_j_track_d0          .push_back( book( name, hjt  + "_d0",          hjtstr  + " abs. d0 [mm]",        100, 0, td0_x2           [j] ) );
	      h_j_track_mind0       .push_back( book( name, hjt  + "_mind0",       hjtstr  + " min d0 [mm]",         100, 0, tmind0_x2        [j] ) );
	      h_j_track_maxd0       .push_back( book( name, hjt  + "_maxd0",       hjtstr  + " max d0 [mm]",         100, 0, tmaxd0_x2        [j] ) );
	      h_j_track_sumd0       .push_back( book( name, hjt  + "_sumd0",       hjtstr  + " sum-d0 [mm]",         100, 0, tsumd0_x2        [j] ) );
	      h_j_track_z0          .push_back( book( name, hjt  + "_z0",          hjtstr  + " abs. z0 [mm]",        100, 0, tz0_x2           [j] ) );
	      h_j_track_minz0       .push_back( book( name, hjt  + "_minz0",       hjtstr  + " min z0 [mm]",         100, 0, tminz0_x2        [j] ) );
	      h_j_track_maxz0       .push_back( book( name, hjt  + "_maxz0",       hjtstr  + " max z0 [mm]",         100, 0, tmaxz0_x2        [j] ) );
	      h_j_track_sumz0       .push_back( book( name, hjt  + "_sumz0",       hjtstr  + " sum-z0 [mm]",         100, 0, tsumz0_x2        [j] ) );
	      h_j_track_errd0       .push_back( book( name, hjt  + "_errd0",       hjtstr  + " d0 uncert.",          100, 0, terrd0_x2        [j] ) );
	      h_j_track_minErrd0    .push_back( book( name, hjt  + "_minErrd0",    hjtstr  + " min d0 uncert.",      100, 0, tminerrd0_x2     [j] ) );
	      h_j_track_maxErrd0    .push_back( book( name, hjt  + "_maxErrd0",    hjtstr  + " max d0 uncert.",      100, 0, tmaxerrd0_x2     [j] ) );
	      h_j_track_sumErrd0    .push_back( book( name, hjt  + "_sumErrd0",    hjtstr  + " sum d0 uncert.",      100, 0, tsumerrd0_x2     [j] ) );
	      h_j_track_errz0       .push_back( book( name, hjt  + "_errz0",       hjtstr  + " z0 uncert.",          100, 0, terrz0_x2        [j] ) );
	      h_j_track_minErrz0    .push_back( book( name, hjt  + "_minErrz0",    hjtstr  + " min z0 uncert.",      100, 0, tminerrz0_x2     [j] ) );
	      h_j_track_maxErrz0    .push_back( book( name, hjt  + "_maxErrz0",    hjtstr  + " max z0 uncert.",      100, 0, tmaxerrz0_x2     [j] ) );
	      h_j_track_sumErrz0    .push_back( book( name, hjt  + "_sumErrz0",    hjtstr  + " sum z0 uncert.",      100, 0, tsumerrz0_x2     [j] ) );
	      h_j_track_sqrtpt      .push_back( book( name, hjt  + "_sqrtpt",      hjtstr  + " sqrt p_{T} [GeV]",    100, 1, sqrt(tpt_x2      [j])) );
	      h_j_track_sqrtd0      .push_back( book( name, hjt  + "_sqrtd0",      hjtstr  + " sqrt d0 [mm]",        100, 0, sqrt(td0_x2      [j])) );
	      h_j_track_sqrtmind0   .push_back( book( name, hjt  + "_sqrtmind0",   hjtstr  + " sqrt min d0 [mm]",    100, 0, sqrt(tmind0_x2   [j])) );
	      h_j_track_sqrtmaxd0   .push_back( book( name, hjt  + "_sqrtmaxd0",   hjtstr  + " sqrt max d0 [mm]",    100, 0, sqrt(tmaxd0_x2   [j])) );
	      h_j_track_sqrtsumd0   .push_back( book( name, hjt  + "_sqrtsumd0",   hjtstr  + " sqrt sum-d0 [mm]",    100, 0, sqrt(tsumd0_x2   [j])) );
	      h_j_track_sqrtz0      .push_back( book( name, hjt  + "_sqrtz0",      hjtstr  + " sqrt z0 [mm]",        100, 0, sqrt(tz0_x2      [j])) );
	      h_j_track_sqrtminz0   .push_back( book( name, hjt  + "_sqrtminz0",   hjtstr  + " sqrt min z0 [mm]",    100, 0, sqrt(tminz0_x2   [j])) );
	      h_j_track_sqrtmaxz0   .push_back( book( name, hjt  + "_sqrtmaxz0",   hjtstr  + " sqrt max z0 [mm]",    100, 0, sqrt(tmaxz0_x2   [j])) );
	      h_j_track_sqrtsumz0   .push_back( book( name, hjt  + "_sumsqrtz0",   hjtstr  + " sqrt sum-z0 [mm]",    100, 0, sqrt(tsumz0_x2   [j])) );
	      h_j_track_sqrterrd0   .push_back( book( name, hjt  + "_sqrterrd0",   hjtstr  + " sqrt d0 uncert.",     100, 0, sqrt(terrd0_x2   [j])) );
	      h_j_track_sqrtminErrd0.push_back( book( name, hjt  + "_sqrtminErrd0",hjtstr  + " sqrt min d0 uncert.", 100, 0, sqrt(tminerrd0_x2[j])) );
	      h_j_track_sqrtmaxErrd0.push_back( book( name, hjt  + "_sqrtmaxErrd0",hjtstr  + " sqrt max d0 uncert.", 100, 0, sqrt(tmaxerrd0_x2[j])) );
	      h_j_track_sqrtsumErrd0.push_back( book( name, hjt  + "_sqrtsumErrd0",hjtstr  + " sqrt sum d0 uncert.", 100, 0, sqrt(tsumerrd0_x2[j])) );
	      h_j_track_sqrterrz0   .push_back( book( name, hjt  + "_sqrterrz0",   hjtstr  + " sqrt z0 uncert.",     100, 0, sqrt(terrz0_x2   [j])) );
	      h_j_track_sqrtminErrz0.push_back( book( name, hjt  + "_sqrtminErrz0",hjtstr  + " sqrt min z0 uncert.", 100, 0, sqrt(tminerrz0_x2[j])) );
	      h_j_track_sqrtmaxErrz0.push_back( book( name, hjt  + "_sqrtmaxErrz0",hjtstr  + " sqrt max z0 uncert.", 100, 0, sqrt(tmaxerrz0_x2[j])) );
	      h_j_track_sqrtsumErrz0.push_back( book( name, hjt  + "_sqrtsumErrz0",hjtstr  + " sqrt sum z0 uncert.", 100, 0, sqrt(tsumerrz0_x2[j])) );
	      h_j_track_nSCT        .push_back( book( name, hjt  + "_nSCT",        hjtstr  + " n SCT hits",          100, 0,                    5 ) );
	      h_j_track_nPixel      .push_back( book( name, hjt  + "_nPixel",      hjtstr  + " n Pixel hits",        100, 0,                   10 ) );
	      h_j_track_nSi         .push_back( book( name, hjt  + "_nSi",         hjtstr  + " n Silicon hits",      100, 0,                   30 ) );
	      h_j_track_nTRT        .push_back( book( name, hjt  + "_nTRT",        hjtstr  + " n TRT hits",          100, 0,                   75 ) );
	      h_j_ntrack_pt         .push_back( book( name, hjnt + "_pt",          hjntstr + " p_{T} [GeV]",         100, 1, ntpt_x2          [j] ) );
	      h_j_ntrack_eta        .push_back( book( name, hjnt + "_eta",         hjntstr + " eta",                 100, -3,                   3 ) );
	      h_j_ntrack_phi        .push_back( book( name, hjnt + "_phi",         hjntstr + " phi",                 100, -3.5,               3.5 ) );
	      h_j_ntrack_m          .push_back( book( name, hjnt + "_m",           hjntstr + " mass [GeV]",          100, 0, ntm_x2           [j] ) );
	      h_j_ntrack_sumPt      .push_back( book( name, hjnt + "_sumPt",       hjntstr + " sum-p_{T} [GeV]",     100, 1, ntsumpt_x2       [j] ) );
	      h_j_ntrack_sqrtsumPt  .push_back( book( name, hjnt + "_sqrtsumPt",   hjntstr + " sqrt sum-p_{T} [GeV]",100, 1, sqrt(ntsumpt_x2  [j])) );
	    } // end if jetTrks info switch
	  } // end loop over track types
	  h_j_ntrk               .push_back( h_j_ntrack             );
	  h_j_trk_dR             .push_back( h_j_track_dR           );
	  h_j_trk_minDR          .push_back( h_j_track_minDR        );
	  h_j_trk_maxDR          .push_back( h_j_track_maxDR        );
	  if ( m_histoInfoSwitch->m_jetTrks ) {
	    h_j_trk_pt           .push_back( h_j_track_pt           );
	    h_j_trk_d0           .push_back( h_j_track_d0           );
	    h_j_trk_mind0        .push_back( h_j_track_mind0        );
	    h_j_trk_maxd0        .push_back( h_j_track_maxd0        );
	    h_j_trk_sumd0        .push_back( h_j_track_sumd0        );
	    h_j_trk_z0           .push_back( h_j_track_z0           );
	    h_j_trk_minz0        .push_back( h_j_track_minz0        );
	    h_j_trk_maxz0        .push_back( h_j_track_maxz0        );
	    h_j_trk_sumz0        .push_back( h_j_track_sumz0        );
	    h_j_trk_errd0        .push_back( h_j_track_errd0        );
	    h_j_trk_minErrd0     .push_back( h_j_track_minErrd0     );
	    h_j_trk_maxErrd0     .push_back( h_j_track_maxErrd0     );
	    h_j_trk_sumErrd0     .push_back( h_j_track_sumErrd0     );
	    h_j_trk_errz0        .push_back( h_j_track_errz0        );
	    h_j_trk_minErrz0     .push_back( h_j_track_minErrz0     );
	    h_j_trk_maxErrz0     .push_back( h_j_track_maxErrz0     );
	    h_j_trk_sumErrz0     .push_back( h_j_track_sumErrz0     );
	    h_j_trk_sqrtpt       .push_back( h_j_track_sqrtpt       );
	    h_j_trk_sqrtd0       .push_back( h_j_track_sqrtd0       );
	    h_j_trk_sqrtmind0    .push_back( h_j_track_sqrtmind0    );
	    h_j_trk_sqrtmaxd0    .push_back( h_j_track_sqrtmaxd0    );
	    h_j_trk_sqrtsumd0    .push_back( h_j_track_sqrtsumd0    );
	    h_j_trk_sqrtz0       .push_back( h_j_track_sqrtz0       );
	    h_j_trk_sqrtminz0    .push_back( h_j_track_sqrtminz0    );
	    h_j_trk_sqrtmaxz0    .push_back( h_j_track_sqrtmaxz0    );
	    h_j_trk_sqrtsumz0    .push_back( h_j_track_sqrtsumz0    );
	    h_j_trk_sqrterrd0    .push_back( h_j_track_sqrterrd0    );
	    h_j_trk_sqrtminErrd0 .push_back( h_j_track_sqrtminErrd0 );
	    h_j_trk_sqrtmaxErrd0 .push_back( h_j_track_sqrtmaxErrd0 );
	    h_j_trk_sqrtsumErrd0 .push_back( h_j_track_sqrtsumErrd0 );
	    h_j_trk_sqrterrz0    .push_back( h_j_track_sqrterrz0    );
	    h_j_trk_sqrtminErrz0 .push_back( h_j_track_sqrtminErrz0 );
	    h_j_trk_sqrtmaxErrz0 .push_back( h_j_track_sqrtmaxErrz0 );
	    h_j_trk_sqrtsumErrz0 .push_back( h_j_track_sqrtsumErrz0 );
	    h_j_trk_nSCT         .push_back( h_j_track_nSCT         );
	    h_j_trk_nPixel       .push_back( h_j_track_nPixel       );
	    h_j_trk_nSi          .push_back( h_j_track_nSi          );
	    h_j_trk_nTRT         .push_back( h_j_track_nTRT         );
	    h_j_ntrk_pt          .push_back( h_j_ntrack_pt          );
	    h_j_ntrk_eta         .push_back( h_j_ntrack_eta         );
	    h_j_ntrk_phi         .push_back( h_j_ntrack_phi         );
	    h_j_ntrk_m           .push_back( h_j_ntrack_m           );
	    h_j_ntrk_sumPt       .push_back( h_j_ntrack_sumPt       );
	    h_j_ntrk_sqrtsumPt   .push_back( h_j_ntrack_sqrtsumPt   );
	  } // end if jetTrks info switch

	  // jets: matched secondary vertices
	  std::vector<TH1F*> h_j_nsecvtx;
	  std::vector<TH1F*> h_j_secvtx_dR;
	  std::vector<TH1F*> h_j_secvtx_minDR;
	  std::vector<TH1F*> h_j_secvtx_maxDR;
	  std::vector<TH1F*> h_j_secvtx_pt;
	  std::vector<TH1F*> h_j_secvtx_Ht;
	  std::vector<TH1F*> h_j_secvtx_H;
	  std::vector<TH1F*> h_j_secvtx_sqrtpt;
	  std::vector<TH1F*> h_j_secvtx_sqrtHt;
	  std::vector<TH1F*> h_j_secvtx_sqrtH;
	  std::vector<TH1F*> h_j_secvtx_mass;
	  std::vector<TH1F*> h_j_secvtx_mass_s;
	  std::vector<TH1F*> h_j_secvtx_ntrk;
	  std::vector<TH1F*> h_j_secvtx_njtrk;
	  std::vector<TH1F*> h_j_secvtx_z;
	  std::vector<TH1F*> h_j_secvtx_minz;
	  std::vector<TH1F*> h_j_secvtx_maxz;
	  std::vector<TH1F*> h_j_secvtx_sumz;
	  std::vector<TH1F*> h_j_secvtx_r;
	  std::vector<TH1F*> h_j_secvtx_minr;
	  std::vector<TH1F*> h_j_secvtx_maxr;
	  std::vector<TH1F*> h_j_secvtx_sumr;
	  std::vector<TH1F*> h_j_secvtx_chi2;
	  std::vector<TH1F*> h_j_nsecvtx_pt;
	  std::vector<TH1F*> h_j_nsecvtx_eta;
	  std::vector<TH1F*> h_j_nsecvtx_phi;
	  std::vector<TH1F*> h_j_nsecvtx_m;
	  std::vector<TH1F*> h_j_nsecvtx_sumPt;
	  std::vector<TH1F*> h_j_nsecvtx_sumHt;
	  std::vector<TH1F*> h_j_nsecvtx_sumH;
	  std::vector<TH1F*> h_j_nsecvtx_sqrtsumPt;
	  std::vector<TH1F*> h_j_nsecvtx_sqrtsumHt;
	  std::vector<TH1F*> h_j_nsecvtx_sqrtsumH;
	  std::vector<TH1F*> h_j_nsecvtx_sumMass;
	  std::vector<TH1F*> h_j_nsecvtx_sumMass_s;
	  std::vector<TH1F*> h_j_nsecvtx_ntrk;
	  std::vector<TH1F*> h_j_nsecvtx_njtrk;
	  // loop over jet-matched secondary vertices
	  for ( size_t k = 0; k != hJDV.size(); ++k ) {
	    std::string hv       = hJDV[k] + "SV"; hv[0] = tolower(hv[0]);
	    std::string hjv      = hj + "_" + hv;
	    std::string hdvstr   = hJDVstr[k]; hdvstr.pop_back();
	    std::string hvstr    = "matched " + hdvstr + " SV";
	    std::string hjvstr   = hjstr + " " + hvstr;
	    std::string hnv      = "n" + hv;
	    std::string hjnv     = hj + "_" + hnv;
	    std::string hnvstr   = "matched " + hdvstr + " n-SV";
	    std::string hjnvstr  = hjstr + " " + hnvstr;
	    std::string hnjnv    = hnj + "_" + hnv;
	    std::string hnjnvstr = hnjstr + " " + hnvstr;
	    h_j_nsecvtx             .push_back( book( name, hj    + "_n" + hv,    "n " + hvstr + "s per " + hjstr,    10, 0,   10 ) );
	    h_j_secvtx_dR           .push_back( book( name, hjv   + "_dR",        hjstr   +" - "+ hvstr + " dR",     100, 0,  0.6 ) );
	    h_j_secvtx_minDR        .push_back( book( name, hjv   + "_minDR",     hjstr   +" - "+ hvstr + " min dR", 100, 0,  0.6 ) );
	    h_j_secvtx_maxDR        .push_back( book( name, hjv   + "_maxDR",     hjstr   +" - "+ hvstr + " max dR", 100, 0,  0.6 ) );
	    if ( m_histoInfoSwitch->m_jetVerts ) {
	      h_j_secvtx_pt         .push_back( book( name, hjv   + "_pt",        hjvstr  + " p_{T} [GeV]",          100, 0,  100 ) );
	      h_j_secvtx_Ht         .push_back( book( name, hjv   + "_Ht",        hjvstr  + " H_{T} [GeV]",          100, 0,  100 ) );
	      h_j_secvtx_H          .push_back( book( name, hjv   + "_H",         hjvstr  + " H [GeV]",              100, 0,  125 ) );
	      h_j_secvtx_sqrtpt     .push_back( book( name, hjv   + "_sqrtpt",    hjvstr  + " sqrt p_{T} [GeV]",     100, 0,   10 ) );
	      h_j_secvtx_sqrtHt     .push_back( book( name, hjv   + "_sqrtHt",    hjvstr  + " sqrt H_{T} [GeV]",     100, 0,   10 ) );
	      h_j_secvtx_sqrtH      .push_back( book( name, hjv   + "_sqrtH",     hjvstr  + " sqrt H [GeV]",         100, 0,   11 ) );
	      h_j_secvtx_mass_s     .push_back( book( name, hjv   + "_mass",      hjvstr  + " mass [GeV]",           100, 0,   50 ) );
	      h_j_secvtx_mass       .push_back( book( name, hjv   + "_mass_s",    hjvstr  + " mass [GeV]",           100, 0,   25 ) );
	      h_j_secvtx_ntrk       .push_back( book( name, hjv   + "_ntrk",      hjvstr  + " n tracks",              10, 2,   12 ) );
	      h_j_secvtx_njtrk      .push_back( book( name, hjv   + "_njtrk",     hjvstr  + " n jet-matched tracks",  12, 0,   12 ) );
	      h_j_secvtx_z          .push_back( book( name, hjv   + "_z",         hjvstr  + " abs z-pos [mm]",       100, 0,  300 ) );
	      h_j_secvtx_minz       .push_back( book( name, hjv   + "_minz",      hjvstr  + " min abs z-pos [mm]",   100, 0,  300 ) );
	      h_j_secvtx_maxz       .push_back( book( name, hjv   + "_maxz",      hjvstr  + " max abs z-pos [mm]",   100, 0,  300 ) );
	      h_j_secvtx_sumz       .push_back( book( name, hjv   + "_sumz",      hjvstr  + " sum abs z-pos [mm]",   100, 0,  600 ) );
	      h_j_secvtx_r          .push_back( book( name, hjv   + "_r",         hjvstr  + " r-pos [mm]",           100, 0,  300 ) );
	      h_j_secvtx_minr       .push_back( book( name, hjv   + "_minr",      hjvstr  + " min r-pos [mm]",       100, 0,  300 ) );
	      h_j_secvtx_maxr       .push_back( book( name, hjv   + "_maxr",      hjvstr  + " max r-pos [mm]",       100, 0,  300 ) );
	      h_j_secvtx_sumr       .push_back( book( name, hjv   + "_sumr",      hjvstr  + " sum r-pos [mm]",       100, 0,  600 ) );
	      h_j_secvtx_chi2       .push_back( book( name, hjv   + "_chi2",      hjvstr  + " chi2 / nDoF",          100, 0,    5 ) );
	      h_j_nsecvtx_pt        .push_back( book( name, hjnv  + "_pt",        hjnvstr + " p_{T} [GeV]",          100, 0,  100 ) );
	      h_j_nsecvtx_eta       .push_back( book( name, hjnv  + "_eta",       hjnvstr + " eta",                  100, -3,   3 ) );
	      h_j_nsecvtx_phi       .push_back( book( name, hjnv  + "_phi",       hjnvstr + " phi",                  100,-3.5,3.5 ) );
	      h_j_nsecvtx_m         .push_back( book( name, hjnv  + "_m",         hjnvstr + " invariant mass [GeV]", 100, 0,  100 ) );
	      h_j_nsecvtx_sumPt     .push_back( book( name, hjnv  + "_sumPt",     hjnvstr + " sum-p_{T} [GeV]",      100, 0,  150 ) );
	      h_j_nsecvtx_sumHt     .push_back( book( name, hjnv  + "_sumHt",     hjnvstr + " sum-H_{T} [GeV]",      100, 0,  150 ) );
	      h_j_nsecvtx_sumH      .push_back( book( name, hjnv  + "_sumH",      hjnvstr + " sum-H [GeV]",          100, 0,  200 ) );
	      h_j_nsecvtx_sqrtsumPt .push_back( book( name, hjnv  + "_sumSqrtpt", hjnvstr + " sqrt sum-p_{T} [GeV]", 100, 0, 12.5 ) );
	      h_j_nsecvtx_sqrtsumHt .push_back( book( name, hjnv  + "_sumSqrtHt", hjnvstr + " sqrt sum-H_{T} [GeV]", 100, 0, 12.5 ) );
	      h_j_nsecvtx_sqrtsumH  .push_back( book( name, hjnv  + "_sumSqrtH",  hjnvstr + " sqrt sum-H [GeV]",     100, 0,   15 ) );
	      h_j_nsecvtx_sumMass   .push_back( book( name, hjnv  + "_sumMass",   hjnvstr + " sum-mass [GeV]",       100, 0,   75 ) );
	      h_j_nsecvtx_sumMass_s .push_back( book( name, hjnv  + "_sumMass_s", hjnvstr + " sum-mass [GeV]",       100, 0,   35 ) );
	      h_j_nsecvtx_ntrk      .push_back( book( name, hjnv  + "_ntrk",      hjnvstr + " sum n tracks",          18, 2,   20 ) );
	      h_j_nsecvtx_njtrk     .push_back( book( name, hjnv  + "_njtrk",     hjnvstr + " sum n jet-matched tracks",20,0,  20 ) );
	    }
	  } // end loop over SV types
	  h_j_nsv             .push_back( h_j_nsecvtx );
	  h_j_sv_dR           .push_back( h_j_secvtx_dR         );
	  h_j_sv_minDR        .push_back( h_j_secvtx_minDR      );
	  h_j_sv_maxDR        .push_back( h_j_secvtx_maxDR      );
	  if ( m_histoInfoSwitch->m_jetVerts ) {
	    h_j_sv_pt         .push_back( h_j_secvtx_pt         );
	    h_j_sv_Ht         .push_back( h_j_secvtx_Ht         );
	    h_j_sv_H          .push_back( h_j_secvtx_H          );
	    h_j_sv_sqrtpt     .push_back( h_j_secvtx_sqrtpt     );
	    h_j_sv_sqrtHt     .push_back( h_j_secvtx_sqrtHt     );	
	    h_j_sv_sqrtH      .push_back( h_j_secvtx_sqrtH      );	
	    h_j_sv_mass       .push_back( h_j_secvtx_mass       );
	    h_j_sv_mass_s     .push_back( h_j_secvtx_mass_s     );
	    h_j_sv_ntrk       .push_back( h_j_secvtx_ntrk       );
	    h_j_sv_njtrk      .push_back( h_j_secvtx_njtrk      );
	    h_j_sv_z          .push_back( h_j_secvtx_z          );
	    h_j_sv_minz       .push_back( h_j_secvtx_minz       );
	    h_j_sv_maxz       .push_back( h_j_secvtx_maxz       );
	    h_j_sv_sumz       .push_back( h_j_secvtx_sumz       );
	    h_j_sv_r          .push_back( h_j_secvtx_r          );
	    h_j_sv_minr       .push_back( h_j_secvtx_minr       );
	    h_j_sv_maxr       .push_back( h_j_secvtx_maxr       );
	    h_j_sv_sumr       .push_back( h_j_secvtx_sumr       );
	    h_j_sv_chi2       .push_back( h_j_secvtx_chi2       );
	    h_j_nsv_pt        .push_back( h_j_nsecvtx_pt        );
	    h_j_nsv_eta       .push_back( h_j_nsecvtx_eta       );
	    h_j_nsv_phi       .push_back( h_j_nsecvtx_phi       );
	    h_j_nsv_m         .push_back( h_j_nsecvtx_m         );
	    h_j_nsv_sumPt     .push_back( h_j_nsecvtx_sumPt     );
	    h_j_nsv_sumHt     .push_back( h_j_nsecvtx_sumHt     );
	    h_j_nsv_sumH      .push_back( h_j_nsecvtx_sumH      );
	    h_j_nsv_sqrtsumPt .push_back( h_j_nsecvtx_sqrtsumPt );
	    h_j_nsv_sqrtsumHt .push_back( h_j_nsecvtx_sqrtsumHt );
	    h_j_nsv_sqrtsumH  .push_back( h_j_nsecvtx_sqrtsumH  );
	    h_j_nsv_sumMass   .push_back( h_j_nsecvtx_sumMass   );
	    h_j_nsv_sumMass_s .push_back( h_j_nsecvtx_sumMass_s );
	    h_j_nsv_ntrk      .push_back( h_j_nsecvtx_ntrk      );
	    h_j_nsv_njtrk     .push_back( h_j_nsecvtx_njtrk     );
	  }
	  //m_nTypeJDVs = h_j_nsecvtx.size();

	  // N leading jets
	  if ( m_numLeadJets && i % m_LJix ) {
	    std::vector<TH1F*> h_nleadj_pt;
	    std::vector<TH1F*> h_nleadj_pt_s;
	    std::vector<TH1F*> h_nleadj_eta;
	    std::vector<TH1F*> h_nleadj_phi;
	    std::vector<TH1F*> h_nleadj_E;
	    std::vector<TH1F*> h_nleadj_M;
	    std::vector<TH1F*> h_nleadj_rapid;
	    std::vector<TH1F*> h_nleadj_nConstits;
	    std::vector<TH1F*> h_nleadj_Et;
	    std::vector<TH1F*> h_nleadj_Et_s;
	    std::vector<std::vector<TH1F*>> h_nleadj_ntrk;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_minDR;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_maxDR;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_mind0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_maxd0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sumd0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_minz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_maxz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sumz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_minErrd0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_maxErrd0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sumErrd0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_minErrz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_maxErrz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sumErrz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtmind0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtmaxd0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtsumd0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtminz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtmaxz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtsumz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtminErrd0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtmaxErrd0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtsumErrd0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtminErrz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtmaxErrz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_trk_sqrtsumErrz0;
	    std::vector<std::vector<TH1F*>> h_nleadj_ntrk_pt;
	    std::vector<std::vector<TH1F*>> h_nleadj_ntrk_eta;
	    std::vector<std::vector<TH1F*>> h_nleadj_ntrk_phi;
	    std::vector<std::vector<TH1F*>> h_nleadj_ntrk_m;
	    std::vector<std::vector<TH1F*>> h_nleadj_ntrk_sumPt;
	    std::vector<std::vector<TH1F*>> h_nleadj_ntrk_sqrtsumPt;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv;
	    std::vector<std::vector<TH1F*>> h_nleadj_sv_minDR;
	    std::vector<std::vector<TH1F*>> h_nleadj_sv_maxDR;
	    std::vector<std::vector<TH1F*>> h_nleadj_sv_minz;
	    std::vector<std::vector<TH1F*>> h_nleadj_sv_maxz;
	    std::vector<std::vector<TH1F*>> h_nleadj_sv_sumz;
	    std::vector<std::vector<TH1F*>> h_nleadj_sv_minr;
	    std::vector<std::vector<TH1F*>> h_nleadj_sv_maxr;
	    std::vector<std::vector<TH1F*>> h_nleadj_sv_sumr;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_pt;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_eta;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_phi;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_m;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_sumPt;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_sumHt;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_sumH;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_sqrtsumPt;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_sqrtsumHt;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_sqrtsumH;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_sumMass;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_sumMass_s;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_ntrk;
	    std::vector<std::vector<TH1F*>> h_nleadj_nsv_njtrk;
	    for ( int j = 0; j != m_numLeadJets; ++j ) {
	      std::string njet     = std::to_string(j);
	      std::string hnjet    = hj + njet;
	      std::string hnjetstr = hjstr + "-" + njet;
	      h_nleadj_pt        .push_back( book( name, hnjet + "_pt",        hnjetstr + " p_{T} [GeV]",    100,    0, 1500 ) );
	      h_nleadj_pt_s      .push_back( book( name, hnjet + "_pt_s",      hnjetstr + " p_{T} [GeV]",    100,    0,  500 ) );
	      h_nleadj_eta       .push_back( book( name, hnjet + "_eta",       hnjetstr + " eta",            100,   -5,    5 ) );
	      h_nleadj_phi       .push_back( book( name, hnjet + "_phi",       hnjetstr + " phi",            100, -3.5,  3.5 ) );
	      h_nleadj_E         .push_back( book( name, hnjet + "_E",         hnjetstr + " energy [GeV]",   100,    0, 2500 ) );
	      h_nleadj_M         .push_back( book( name, hnjet + "_M",         hnjetstr + " mass [GeV]",     100,    0,  250 ) );
	      h_nleadj_rapid     .push_back( book( name, hnjet + "_rapid",     hnjetstr + " rapidity",       100,   -5,    5 ) );
	      h_nleadj_nConstits .push_back( book( name, hnjet + "_nConstits", hnjetstr + " n constituents", 100,    0,   60 ) );
	      if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
		h_nleadj_Et      .push_back( book( name, hnjet + "_Et",        hnjetstr + " E_{T} [GeV]",    100,    0, 1500 ) );
		h_nleadj_Et_s    .push_back( book( name, hnjet + "_Et_s",      hnjetstr + " E_{T} [GeV]",    100,    0,  500 ) );
	      }
	  
	      std::vector<TH1F*> h_nleadj_ntrack;
	      std::vector<TH1F*> h_nleadj_track_minDR;
	      std::vector<TH1F*> h_nleadj_track_maxDR;
	      std::vector<TH1F*> h_nleadj_track_mind0;
	      std::vector<TH1F*> h_nleadj_track_maxd0;
	      std::vector<TH1F*> h_nleadj_track_sumd0;
	      std::vector<TH1F*> h_nleadj_track_minz0;
	      std::vector<TH1F*> h_nleadj_track_maxz0;
	      std::vector<TH1F*> h_nleadj_track_sumz0;
	      std::vector<TH1F*> h_nleadj_track_minErrd0;
	      std::vector<TH1F*> h_nleadj_track_maxErrd0;
	      std::vector<TH1F*> h_nleadj_track_sumErrd0;
	      std::vector<TH1F*> h_nleadj_track_minErrz0;
	      std::vector<TH1F*> h_nleadj_track_maxErrz0;
	      std::vector<TH1F*> h_nleadj_track_sumErrz0;
	      std::vector<TH1F*> h_nleadj_track_sqrtmind0;
	      std::vector<TH1F*> h_nleadj_track_sqrtmaxd0;
	      std::vector<TH1F*> h_nleadj_track_sqrtsumd0;
	      std::vector<TH1F*> h_nleadj_track_sqrtminz0;
	      std::vector<TH1F*> h_nleadj_track_sqrtmaxz0;
	      std::vector<TH1F*> h_nleadj_track_sqrtsumz0;
	      std::vector<TH1F*> h_nleadj_track_sqrtminErrd0;
	      std::vector<TH1F*> h_nleadj_track_sqrtmaxErrd0;
	      std::vector<TH1F*> h_nleadj_track_sqrtsumErrd0;
	      std::vector<TH1F*> h_nleadj_track_sqrtminErrz0;
	      std::vector<TH1F*> h_nleadj_track_sqrtmaxErrz0;
	      std::vector<TH1F*> h_nleadj_track_sqrtsumErrz0;
	      std::vector<TH1F*> h_nleadj_ntrack_pt;
	      std::vector<TH1F*> h_nleadj_ntrack_eta;
	      std::vector<TH1F*> h_nleadj_ntrack_phi;
	      std::vector<TH1F*> h_nleadj_ntrack_m;
	      std::vector<TH1F*> h_nleadj_ntrack_sumPt;
	      std::vector<TH1F*> h_nleadj_ntrack_sqrtsumPt;
	      for ( size_t k = 0; k != hTrk.size(); ++k ) {
		std::string htsubstr   = "matched";
		if ( !hTrkstr[k].empty() ) htsubstr += " ";
		std::string ht         = hTrk[k]  + "trk";
		std::string htstr      = htsubstr + hTrkstr[k] + " track";
		std::string hnjett     = hnjet + "_" + ht;
		std::string hnjettstr  = hnjetstr + " " + htstr;
		std::string hnt        = "n" + ht;
		std::string hntstr     = htsubstr + hTrkstr[k] + " n-track";
		std::string hnjetnt    = hnjet + "_" + hnt;
		std::string hnjetntstr = hnjetstr + " " + hntstr;
		int nbin = nt_x2[k];
		if ( k < 2 ) nbin = nt_x2[k] / 2;
		h_nleadj_ntrack
		  .push_back(   book( name, hnjet + "_n" + ht,        "n " + htstr + "s per " + hnjetstr, nbin, 0, nt_x2            [k] ) );
		h_nleadj_track_minDR
		  .push_back(   book( name, hnjett  + "_minDR",       hnjetstr   +" - "+ htstr + " min dR",100, 0,                  0.6 ) );
		h_nleadj_track_maxDR
		  .push_back(   book( name, hnjett  + "_maxDR",       hnjetstr   +" - "+ htstr + " max dR",100, 0,                  0.6 ) );
		if ( m_histoInfoSwitch->m_jetTrks ) {
		  h_nleadj_track_mind0
		    .push_back( book( name, hnjett  + "_mind0",       hnjettstr  + " min d0 [mm]",         100, 0, tmind0_x2        [k] ) );
		  h_nleadj_track_maxd0
		    .push_back( book( name, hnjett  + "_maxd0",       hnjettstr  + " max d0 [mm]",         100, 0, tmaxd0_x2        [k] ) );
		  h_nleadj_track_sumd0
		    .push_back( book( name, hnjett  + "_sumd0",       hnjettstr  + " sum-d0 [mm]",         100, 0, tsumd0_x2        [k] ) );
		  h_nleadj_track_minz0
		    .push_back( book( name, hnjett  + "_minz0",       hnjettstr  + " min z0 [mm]",         100, 0, tminz0_x2        [k] ) );
		  h_nleadj_track_maxz0
		    .push_back( book( name, hnjett  + "_maxz0",       hnjettstr  + " max z0 [mm]",         100, 0, tmaxz0_x2        [k] ) );
		  h_nleadj_track_sumz0
		    .push_back( book( name, hnjett  + "_sumz0",       hnjettstr  + " sum-z0 [mm]",         100, 0, tsumz0_x2        [k] ) );
		  h_nleadj_track_minErrd0
		    .push_back( book( name, hnjett  + "_minErrd0",    hnjettstr  + " min d0 uncert.",      100, 0, tminerrd0_x2     [k] ) );
		  h_nleadj_track_maxErrd0
		    .push_back( book( name, hnjett  + "_maxErrd0",    hnjettstr  + " max d0 uncert.",      100, 0, tmaxerrd0_x2     [k] ) );
		  h_nleadj_track_sumErrd0
		    .push_back( book( name, hnjett  + "_sumErrd0",    hnjettstr  + " sum d0 uncert.",      100, 0, tsumerrd0_x2     [k] ) );
		  h_nleadj_track_minErrz0
		    .push_back( book( name, hnjett  + "_minErrz0",    hnjettstr  + " min z0 uncert.",      100, 0, tminerrz0_x2     [k] ) );
		  h_nleadj_track_maxErrz0
		    .push_back( book( name, hnjett  + "_maxErrz0",    hnjettstr  + " max z0 uncert.",      100, 0, tmaxerrz0_x2     [k] ) );
		  h_nleadj_track_sumErrz0
		    .push_back( book( name, hnjett  + "_sumErrz0",    hnjettstr  + " sum z0 uncert.",      100, 0, tsumerrz0_x2     [k] ) );
		  h_nleadj_track_sqrtmind0
		    .push_back( book( name, hnjett  + "_sqrtmind0",   hnjettstr  + " sqrt min d0 [mm]",    100, 0, sqrt(tmind0_x2   [k])) );
		  h_nleadj_track_sqrtmaxd0
		    .push_back( book( name, hnjett  + "_sqrtmaxd0",   hnjettstr  + " sqrt max d0 [mm]",    100, 0, sqrt(tmaxd0_x2   [k])) );
		  h_nleadj_track_sqrtsumd0
		    .push_back( book( name, hnjett  + "_sqrtsumd0",   hnjettstr  + " sqrt sum-d0 [mm]",    100, 0, sqrt(tsumd0_x2   [k])) );
		  h_nleadj_track_sqrtminz0
		    .push_back( book( name, hnjett  + "_sqrtminz0",   hnjettstr  + " sqrt min z0 [mm]",    100, 0, sqrt(tminz0_x2   [k])) );
		  h_nleadj_track_sqrtmaxz0
		    .push_back( book( name, hnjett  + "_sqrtmaxz0",   hnjettstr  + " sqrt max z0 [mm]",    100, 0, sqrt(tmaxz0_x2   [k])) );
		  h_nleadj_track_sqrtsumz0
		    .push_back( book( name, hnjett  + "_sumsqrtz0",   hnjettstr  + " sqrt sum-z0 [mm]",    100, 0, sqrt(tsumz0_x2   [k])) );
		  h_nleadj_track_sqrtminErrd0
		    .push_back( book( name, hnjett  + "_sqrtminErrd0",hnjettstr  + " sqrt min d0 uncert.", 100, 0, sqrt(tminerrd0_x2[k])) );
		  h_nleadj_track_sqrtmaxErrd0
		    .push_back( book( name, hnjett  + "_sqrtmaxErrd0",hnjettstr  + " sqrt max d0 uncert.", 100, 0, sqrt(tmaxerrd0_x2[k])) );
		  h_nleadj_track_sqrtsumErrd0
		    .push_back( book( name, hnjett  + "_sqrtsumErrd0",hnjettstr  + " sqrt sum d0 uncert.", 100, 0, sqrt(tsumerrd0_x2[k])) );
		  h_nleadj_track_sqrtminErrz0
		    .push_back( book( name, hnjett  + "_sqrtminErrz0",hnjettstr  + " sqrt min z0 uncert.", 100, 0, sqrt(tminerrz0_x2[k])) );
		  h_nleadj_track_sqrtmaxErrz0
		    .push_back( book( name, hnjett  + "_sqrtmaxErrz0",hnjettstr  + " sqrt max z0 uncert.", 100, 0, sqrt(tmaxerrz0_x2[k])) );
		  h_nleadj_track_sqrtsumErrz0
		    .push_back( book( name, hnjett  + "_sqrtsumErrz0",hnjettstr  + " sqrt sum z0 uncert.", 100, 0, sqrt(tsumerrz0_x2[k])) );
		  h_nleadj_ntrack_pt
		    .push_back( book( name, hnjetnt + "_pt",          hnjetntstr + " p_{T} [GeV]",         100, 1, ntpt_x2          [k] ) );
		  h_nleadj_ntrack_eta
		    .push_back( book( name, hnjetnt + "_eta",         hnjetntstr + " eta",                 100, -3,                   3 ) );
		  h_nleadj_ntrack_phi
		    .push_back( book( name, hnjetnt + "_phi",         hnjetntstr + " phi",                 100, -3.5,               3.5 ) );
		  h_nleadj_ntrack_m
		    .push_back( book( name, hnjetnt + "_m",           hnjetntstr + " mass [GeV]",          100, 0, ntm_x2           [k] ) );
		  h_nleadj_ntrack_sumPt
		    .push_back( book( name, hnjetnt + "_sumPt",       hnjetntstr + " sum-p_{T} [GeV]",     100, 1, ntsumpt_x2       [k] ) );
		  h_nleadj_ntrack_sqrtsumPt
		    .push_back( book( name, hnjetnt + "_sqrtsumPt",   hnjetntstr + " sqrt sum-p_{T} [GeV]",100, 1, sqrt(ntsumpt_x2  [k])) );
		}
	      }
	      h_nleadj_ntrk               .push_back( h_nleadj_ntrack             );
	      h_nleadj_trk_minDR          .push_back( h_nleadj_track_minDR        );
	      h_nleadj_trk_maxDR          .push_back( h_nleadj_track_maxDR        );
	      if ( m_histoInfoSwitch->m_jetTrks ) {
		h_nleadj_trk_mind0        .push_back( h_nleadj_track_mind0        );
		h_nleadj_trk_maxd0        .push_back( h_nleadj_track_maxd0        );
		h_nleadj_trk_sumd0        .push_back( h_nleadj_track_sumd0        );
		h_nleadj_trk_minz0        .push_back( h_nleadj_track_minz0        );
		h_nleadj_trk_maxz0        .push_back( h_nleadj_track_maxz0        );
		h_nleadj_trk_sumz0        .push_back( h_nleadj_track_sumz0        );
		h_nleadj_trk_minErrd0     .push_back( h_nleadj_track_minErrd0     );
		h_nleadj_trk_maxErrd0     .push_back( h_nleadj_track_maxErrd0     );
		h_nleadj_trk_sumErrd0     .push_back( h_nleadj_track_sumErrd0     );
		h_nleadj_trk_minErrz0     .push_back( h_nleadj_track_minErrz0     );
		h_nleadj_trk_maxErrz0     .push_back( h_nleadj_track_maxErrz0     );
		h_nleadj_trk_sumErrz0     .push_back( h_nleadj_track_sumErrz0     );
		h_nleadj_trk_sqrtmind0    .push_back( h_nleadj_track_sqrtmind0    );
		h_nleadj_trk_sqrtmaxd0    .push_back( h_nleadj_track_sqrtmaxd0    );
		h_nleadj_trk_sqrtsumd0    .push_back( h_nleadj_track_sqrtsumd0    );
		h_nleadj_trk_sqrtminz0    .push_back( h_nleadj_track_sqrtminz0    );
		h_nleadj_trk_sqrtmaxz0    .push_back( h_nleadj_track_sqrtmaxz0    );
		h_nleadj_trk_sqrtsumz0    .push_back( h_nleadj_track_sqrtsumz0    );
		h_nleadj_trk_sqrtminErrd0 .push_back( h_nleadj_track_sqrtminErrd0 );
		h_nleadj_trk_sqrtmaxErrd0 .push_back( h_nleadj_track_sqrtmaxErrd0 );
		h_nleadj_trk_sqrtsumErrd0 .push_back( h_nleadj_track_sqrtsumErrd0 );
		h_nleadj_trk_sqrtminErrz0 .push_back( h_nleadj_track_sqrtminErrz0 );
		h_nleadj_trk_sqrtmaxErrz0 .push_back( h_nleadj_track_sqrtmaxErrz0 );
		h_nleadj_trk_sqrtsumErrz0 .push_back( h_nleadj_track_sqrtsumErrz0 );
		h_nleadj_ntrk_pt          .push_back( h_nleadj_ntrack_pt          );
		h_nleadj_ntrk_eta         .push_back( h_nleadj_ntrack_eta         );
		h_nleadj_ntrk_phi         .push_back( h_nleadj_ntrack_phi         );
		h_nleadj_ntrk_m           .push_back( h_nleadj_ntrack_m           );
		h_nleadj_ntrk_sumPt       .push_back( h_nleadj_ntrack_sumPt       );
		h_nleadj_ntrk_sqrtsumPt   .push_back( h_nleadj_ntrack_sqrtsumPt   );
	      }

	      std::vector<TH1F*> h_nleadj_nsecvtx;
	      std::vector<TH1F*> h_nleadj_secvtx_minDR;
	      std::vector<TH1F*> h_nleadj_secvtx_maxDR;
	      std::vector<TH1F*> h_nleadj_secvtx_minz;
	      std::vector<TH1F*> h_nleadj_secvtx_maxz;
	      std::vector<TH1F*> h_nleadj_secvtx_sumz;
	      std::vector<TH1F*> h_nleadj_secvtx_minr;
	      std::vector<TH1F*> h_nleadj_secvtx_maxr;
	      std::vector<TH1F*> h_nleadj_secvtx_sumr;
	      std::vector<TH1F*> h_nleadj_nsecvtx_pt;
	      std::vector<TH1F*> h_nleadj_nsecvtx_eta;
	      std::vector<TH1F*> h_nleadj_nsecvtx_phi;
	      std::vector<TH1F*> h_nleadj_nsecvtx_m;
	      std::vector<TH1F*> h_nleadj_nsecvtx_sumPt;
	      std::vector<TH1F*> h_nleadj_nsecvtx_sumHt;
	      std::vector<TH1F*> h_nleadj_nsecvtx_sumH;
	      std::vector<TH1F*> h_nleadj_nsecvtx_sqrtsumPt;
	      std::vector<TH1F*> h_nleadj_nsecvtx_sqrtsumHt;
	      std::vector<TH1F*> h_nleadj_nsecvtx_sqrtsumH;
	      std::vector<TH1F*> h_nleadj_nsecvtx_sumMass;
	      std::vector<TH1F*> h_nleadj_nsecvtx_sumMass_s;
	      std::vector<TH1F*> h_nleadj_nsecvtx_ntrk;
	      std::vector<TH1F*> h_nleadj_nsecvtx_njtrk;
	      for ( size_t k = 0; k != hJDV.size(); ++k ) {
		std::string hv         = hJDV[k] + "SV"; hv[0] = tolower(hv[0]);
		std::string hdvstr     = hJDVstr[k]; hdvstr.pop_back();
		std::string hvstr      = "matched " + hdvstr + " SV";
		std::string hnjetv     = hnjet + "_" + hv;
		std::string hnjetvstr  = hnjetstr + " " + hvstr;
		std::string hnv        = "n" + hv;
		std::string hnjetnv    = hnjet + "_" + hnv;
		std::string hnvstr     = "matched " + hdvstr + " n-SV";
		std::string hnjetnvstr = hnjetstr + " " + hnvstr;
		h_nleadj_nsecvtx             .push_back( book( name, hnjet    + "_n" + hv,    "n " + hvstr + "s per " + hnjetstr,    10, 0,   10 ) );
		h_nleadj_secvtx_minDR        .push_back( book( name, hnjetv   + "_minDR",     hnjetstr   +" - "+ hvstr + " min dR", 100, 0,  0.6 ) );
		h_nleadj_secvtx_maxDR        .push_back( book( name, hnjetv   + "_maxDR",     hnjetstr   +" - "+ hvstr + " max dR", 100, 0,  0.6 ) );
		if ( m_histoInfoSwitch->m_jetVerts ) {
		  h_nleadj_secvtx_minz       .push_back( book( name, hnjetv   + "_minz",      hnjetvstr  + " min abs z-pos [mm]",   100, 0,  300 ) );
		  h_nleadj_secvtx_maxz       .push_back( book( name, hnjetv   + "_maxz",      hnjetvstr  + " max abs z-pos [mm]",   100, 0,  300 ) );
		  h_nleadj_secvtx_sumz       .push_back( book( name, hnjetv   + "_sumz",      hnjetvstr  + " sum abs z-pos [mm]",   100, 0,  600 ) );
		  h_nleadj_secvtx_minr       .push_back( book( name, hnjetv   + "_minr",      hnjetvstr  + " min r-pos [mm]",       100, 0,  300 ) );
		  h_nleadj_secvtx_maxr       .push_back( book( name, hnjetv   + "_maxr",      hnjetvstr  + " max r-pos [mm]",       100, 0,  300 ) );
		  h_nleadj_secvtx_sumr       .push_back( book( name, hnjetv   + "_sumr",      hnjetvstr  + " sum r-pos [mm]",       100, 0,  600 ) );
		  h_nleadj_nsecvtx_pt        .push_back( book( name, hnjetnv  + "_pt",        hnjetnvstr + " p_{T} [GeV]",          100, 0,  100 ) );
		  h_nleadj_nsecvtx_eta       .push_back( book( name, hnjetnv  + "_eta",       hnjetnvstr + " eta",                  100, -3,   3 ) );
		  h_nleadj_nsecvtx_phi       .push_back( book( name, hnjetnv  + "_phi",       hnjetnvstr + " phi",                  100,-3.5,3.5 ) );
		  h_nleadj_nsecvtx_m         .push_back( book( name, hnjetnv  + "_m",         hnjetnvstr + " invariant mass [GeV]", 100, 0,  100 ) );
		  h_nleadj_nsecvtx_sumPt     .push_back( book( name, hnjetnv  + "_sumPt",     hnjetnvstr + " sum-p_{T} [GeV]",      100, 0,  150 ) );
		  h_nleadj_nsecvtx_sumHt     .push_back( book( name, hnjetnv  + "_sumHt",     hnjetnvstr + " sum-H_{T} [GeV]",      100, 0,  150 ) );
		  h_nleadj_nsecvtx_sumH      .push_back( book( name, hnjetnv  + "_sumH",      hnjetnvstr + " sum-H [GeV]",          100, 0,  200 ) );
		  h_nleadj_nsecvtx_sqrtsumPt .push_back( book( name, hnjetnv  + "_sumSqrtpt", hnjetnvstr + " sqrt sum-p_{T} [GeV]", 100, 0, 12.5 ) );
		  h_nleadj_nsecvtx_sqrtsumHt .push_back( book( name, hnjetnv  + "_sumSqrtHt", hnjetnvstr + " sqrt sum-H_{T} [GeV]", 100, 0, 12.5 ) );
		  h_nleadj_nsecvtx_sqrtsumH  .push_back( book( name, hnjetnv  + "_sumSqrtH",  hnjetnvstr + " sqrt sum-H [GeV]",     100, 0,   15 ) );
		  h_nleadj_nsecvtx_sumMass   .push_back( book( name, hnjetnv  + "_sumMass",   hnjetnvstr + " sum-mass [GeV]",       100, 0,   75 ) );
		  h_nleadj_nsecvtx_sumMass_s .push_back( book( name, hnjetnv  + "_sumMass_s", hnjetnvstr + " sum-mass [GeV]",       100, 0,   35 ) );
		  h_nleadj_nsecvtx_ntrk      .push_back( book( name, hnjetnv  + "_ntrk",      hnjetnvstr + " sum n tracks",          18, 2,   20 ) );
		  h_nleadj_nsecvtx_njtrk     .push_back( book( name, hnjetnv  + "_njtrk",     hnjetnvstr + " sum n jet-matched tracks",20,0,  20 ) );
		}
	      }
	      h_nleadj_nsv             .push_back( h_nleadj_nsecvtx           );
	      h_nleadj_sv_minDR        .push_back( h_nleadj_secvtx_minDR      );
	      h_nleadj_sv_maxDR        .push_back( h_nleadj_secvtx_maxDR      );
	      if ( m_histoInfoSwitch->m_jetVerts ) {
		h_nleadj_sv_minz       .push_back( h_nleadj_secvtx_minz       );
		h_nleadj_sv_maxz       .push_back( h_nleadj_secvtx_maxz       );
		h_nleadj_sv_sumz       .push_back( h_nleadj_secvtx_sumz       );
		h_nleadj_sv_minr       .push_back( h_nleadj_secvtx_minr       );
		h_nleadj_sv_maxr       .push_back( h_nleadj_secvtx_maxr       );
		h_nleadj_sv_sumr       .push_back( h_nleadj_secvtx_sumr       );
		h_nleadj_nsv_pt        .push_back( h_nleadj_nsecvtx_pt        );
		h_nleadj_nsv_eta       .push_back( h_nleadj_nsecvtx_eta       );
		h_nleadj_nsv_phi       .push_back( h_nleadj_nsecvtx_phi       );
		h_nleadj_nsv_m         .push_back( h_nleadj_nsecvtx_m         );
		h_nleadj_nsv_sumPt     .push_back( h_nleadj_nsecvtx_sumPt     );
		h_nleadj_nsv_sumHt     .push_back( h_nleadj_nsecvtx_sumHt     );
		h_nleadj_nsv_sumH      .push_back( h_nleadj_nsecvtx_sumH      );
		h_nleadj_nsv_sqrtsumPt .push_back( h_nleadj_nsecvtx_sqrtsumPt );
		h_nleadj_nsv_sqrtsumHt .push_back( h_nleadj_nsecvtx_sqrtsumHt );
		h_nleadj_nsv_sqrtsumH  .push_back( h_nleadj_nsecvtx_sqrtsumH  );
		h_nleadj_nsv_sumMass   .push_back( h_nleadj_nsecvtx_sumMass   );
		h_nleadj_nsv_sumMass_s .push_back( h_nleadj_nsecvtx_sumMass_s );
		h_nleadj_nsv_ntrk      .push_back( h_nleadj_nsecvtx_ntrk      );
		h_nleadj_nsv_njtrk     .push_back( h_nleadj_nsecvtx_njtrk     );
	      }
	    }
	
	    h_nlj_pt        .push_back( h_nleadj_pt        );
	    h_nlj_pt_s      .push_back( h_nleadj_pt_s      );
	    h_nlj_eta       .push_back( h_nleadj_eta       );
	    h_nlj_phi       .push_back( h_nleadj_phi       );
	    h_nlj_E         .push_back( h_nleadj_E         );
	    h_nlj_M         .push_back( h_nleadj_M         );
	    h_nlj_rapid     .push_back( h_nleadj_rapid     );
	    h_nlj_nConstits .push_back( h_nleadj_nConstits );
	    if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	      h_nlj_Et      .push_back( h_nleadj_Et        );
	      h_nlj_Et_s    .push_back( h_nleadj_Et_s      );
	    }
	    h_nlj_ntrk               .push_back( h_nleadj_ntrk             );
	    h_nlj_trk_minDR          .push_back( h_nleadj_trk_minDR        );
	    h_nlj_trk_maxDR          .push_back( h_nleadj_trk_maxDR        );
	    if ( m_histoInfoSwitch->m_jetTrks ) {
	      h_nlj_trk_mind0        .push_back( h_nleadj_trk_mind0        );
	      h_nlj_trk_maxd0        .push_back( h_nleadj_trk_maxd0        );
	      h_nlj_trk_sumd0        .push_back( h_nleadj_trk_sumd0        );
	      h_nlj_trk_minz0        .push_back( h_nleadj_trk_minz0        );
	      h_nlj_trk_maxz0        .push_back( h_nleadj_trk_maxz0        );
	      h_nlj_trk_sumz0        .push_back( h_nleadj_trk_sumz0        );
	      h_nlj_trk_minErrd0     .push_back( h_nleadj_trk_minErrd0     );
	      h_nlj_trk_maxErrd0     .push_back( h_nleadj_trk_maxErrd0     );
	      h_nlj_trk_sumErrd0     .push_back( h_nleadj_trk_sumErrd0     );
	      h_nlj_trk_minErrz0     .push_back( h_nleadj_trk_minErrz0     );
	      h_nlj_trk_maxErrz0     .push_back( h_nleadj_trk_maxErrz0     );
	      h_nlj_trk_sumErrz0     .push_back( h_nleadj_trk_sumErrz0     );
	      h_nlj_trk_sqrtmind0    .push_back( h_nleadj_trk_sqrtmind0    );
	      h_nlj_trk_sqrtmaxd0    .push_back( h_nleadj_trk_sqrtmaxd0    );
	      h_nlj_trk_sqrtsumd0    .push_back( h_nleadj_trk_sqrtsumd0    );
	      h_nlj_trk_sqrtminz0    .push_back( h_nleadj_trk_sqrtminz0    );
	      h_nlj_trk_sqrtmaxz0    .push_back( h_nleadj_trk_sqrtmaxz0    );
	      h_nlj_trk_sqrtsumz0    .push_back( h_nleadj_trk_sqrtsumz0    );
	      h_nlj_trk_sqrtminErrd0 .push_back( h_nleadj_trk_sqrtminErrd0 );
	      h_nlj_trk_sqrtmaxErrd0 .push_back( h_nleadj_trk_sqrtmaxErrd0 );
	      h_nlj_trk_sqrtsumErrd0 .push_back( h_nleadj_trk_sqrtsumErrd0 );
	      h_nlj_trk_sqrtminErrz0 .push_back( h_nleadj_trk_sqrtminErrz0 );
	      h_nlj_trk_sqrtmaxErrz0 .push_back( h_nleadj_trk_sqrtmaxErrz0 );
	      h_nlj_trk_sqrtsumErrz0 .push_back( h_nleadj_trk_sqrtsumErrz0 );
	      h_nlj_ntrk_pt          .push_back( h_nleadj_ntrk_pt          );
	      h_nlj_ntrk_eta         .push_back( h_nleadj_ntrk_eta         );
	      h_nlj_ntrk_phi         .push_back( h_nleadj_ntrk_phi         );
	      h_nlj_ntrk_m           .push_back( h_nleadj_ntrk_m           );
	      h_nlj_ntrk_sumPt       .push_back( h_nleadj_ntrk_sumPt       );
	      h_nlj_ntrk_sqrtsumPt   .push_back( h_nleadj_ntrk_sqrtsumPt   );
	    }
	    h_nlj_nsv             .push_back( h_nleadj_nsv           );
	    h_nlj_sv_minDR        .push_back( h_nleadj_sv_minDR      );
	    h_nlj_sv_maxDR        .push_back( h_nleadj_sv_maxDR      );
	    if ( m_histoInfoSwitch->m_jetVerts ) {
	      h_nlj_sv_minz       .push_back( h_nleadj_sv_minz       );
	      h_nlj_sv_maxz       .push_back( h_nleadj_sv_maxz       );
	      h_nlj_sv_sumz       .push_back( h_nleadj_sv_sumz       );
	      h_nlj_sv_minr       .push_back( h_nleadj_sv_minr       );
	      h_nlj_sv_maxr       .push_back( h_nleadj_sv_maxr       );
	      h_nlj_sv_sumr       .push_back( h_nleadj_sv_sumr       );
	      h_nlj_nsv_pt        .push_back( h_nleadj_nsv_pt        );
	      h_nlj_nsv_eta       .push_back( h_nleadj_nsv_eta       );
	      h_nlj_nsv_phi       .push_back( h_nleadj_nsv_phi       );
	      h_nlj_nsv_m         .push_back( h_nleadj_nsv_m         );
	      h_nlj_nsv_sumPt     .push_back( h_nleadj_nsv_sumPt     );
	      h_nlj_nsv_sumHt     .push_back( h_nleadj_nsv_sumHt     );
	      h_nlj_nsv_sumH      .push_back( h_nleadj_nsv_sumH      );
	      h_nlj_nsv_sqrtsumPt .push_back( h_nleadj_nsv_sqrtsumPt );
	      h_nlj_nsv_sqrtsumHt .push_back( h_nleadj_nsv_sqrtsumHt );
	      h_nlj_nsv_sqrtsumH  .push_back( h_nleadj_nsv_sqrtsumH  );
	      h_nlj_nsv_sumMass   .push_back( h_nleadj_nsv_sumMass   );
	      h_nlj_nsv_sumMass_s .push_back( h_nleadj_nsv_sumMass_s );
	      h_nlj_nsv_ntrk      .push_back( h_nleadj_nsv_ntrk      );
	      h_nlj_nsv_njtrk     .push_back( h_nleadj_nsv_njtrk     );
	    }
	  }
	} // end if not abcdcutOnly
      
	// dijets
	if ( m_histoInfoSwitch->m_dijets ) {
	  // float jj_sumpt  = 3000;
	  // if ( region.type == EJsHelper::JZ4W_SLICE_SEARCH ) jj_sumpt  = 2000;
	  std::string hjjavg    = hjj    + "_avgP4";
	  std::string hjjavgstr = hjjstr + " avg-p4";
	  std::string hjjmax    = hjj    + "_maxP4";
	  std::string hjjmaxstr = hjjstr + " max-p4";
	  std::string hjjmin    = hjj    + "_minP4";
	  std::string hjjminstr = hjjstr + " min-p4";
	  if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
	    h_jj_n       .push_back( book( name, hjj + "_n",        "n " + hjjstr + "s",                 100,    0,   60 ) );
	    h_jj_pt      .push_back( book( name, hjj + "_pt",       hjjstr + " p_{T} [GeV]",             100,    0, 2000 ) );
	    h_jj_eta     .push_back( book( name, hjj + "_eta",      hjjstr + " eta",                     100,   -5,    5 ) );
	    h_jj_phi     .push_back( book( name, hjj + "_phi",      hjjstr + " phi",                     100, -3.5,  3.5 ) );
	    h_jj_m       .push_back( book( name, hjj + "_m",        hjjstr + " invariant mass [GeV]",    100,    0, 3000 ) );
	    h_jj_sumPt   .push_back( book( name, hjj + "_sumPt",    hjjstr + " sum-p_{T} [GeV]",         100,    0, 3000 ) ); // jz4w 2000
	    h_jj_sumM    .push_back( book( name, hjj + "_sumM",     hjjstr + " sum-mass [GeV]",          100,    0,  400 ) );
	    h_jj_dR      .push_back( book( name, hjj + "_dR",       hjjstr + " dR",                      100,    0,    6 ) );
	  }
	  // avg dijet system
	  h_jj_avg_pt    .push_back( book( name, hjjavg + "_pt",    hjjavgstr + " p_{T} [GeV]",          100,    0, 1200 ) );
	  h_jj_avg_eta   .push_back( book( name, hjjavg + "_eta",   hjjavgstr + " eta",                  100,   -5,    5 ) );
	  h_jj_avg_phi   .push_back( book( name, hjjavg + "_phi",   hjjavgstr + " phi",                  100, -3.5,  3.5 ) );
	  h_jj_avg_m     .push_back( book( name, hjjavg + "_m",     hjjavgstr + " invariant mass [GeV]", 100,    0, 2000 ) );
	  h_jj_avg_sumPt .push_back( book( name, hjjavg + "_sumPt", hjjavgstr + " sum-p_{T} [GeV]",      100,    0, 2000 ) );
	  h_jj_avg_sumM  .push_back( book( name, hjjavg + "_sumM",  hjjavgstr + " sum-mass [GeV]",       100,    0,  300 ) );
	  h_jj_avg_dR    .push_back( book( name, hjjavg + "_dR",    hjjavgstr + " dR",                   100,    0,    6 ) );
	  // max dijet system
	  h_jj_max_pt    .push_back( book( name, hjjmax + "_pt",    hjjmaxstr + " p_{T} [GeV]",          100,    0, 1500 ) );
	  h_jj_max_eta   .push_back( book( name, hjjmax + "_eta",   hjjmaxstr + " eta",                  100,   -5,    5 ) );
	  h_jj_max_phi   .push_back( book( name, hjjmax + "_phi",   hjjmaxstr + " phi",                  100, -3.5,  3.5 ) );
	  h_jj_max_m     .push_back( book( name, hjjmax + "_m",     hjjmaxstr + " invariant mass [GeV]", 100,    0, 4000 ) );
	  h_jj_max_sumPt .push_back( book( name, hjjmax + "_sumPt", hjjmaxstr + " sum-p_{T} [GeV]",      100,    0, 3500 ) ); // jz4w 2000
	  h_jj_max_sumM  .push_back( book( name, hjjmax + "_sumM",  hjjmaxstr + " sum-mass [GeV]",       100,    0,  400 ) );
	  h_jj_max_dR    .push_back( book( name, hjjmax + "_dR",    hjjmaxstr + " dR",                   100,    0,    6 ) );
	  // min dijet system
	  h_jj_min_pt    .push_back( book( name, hjjmin + "_pt",    hjjminstr + " p_{T} [GeV]",          100,    0, 2000 ) );
	  h_jj_min_eta   .push_back( book( name, hjjmin + "_eta",   hjjminstr + " eta",                  100,   -5,    5 ) );
	  h_jj_min_phi   .push_back( book( name, hjjmin + "_phi",   hjjminstr + " phi",                  100, -3.5,  3.5 ) );
	  h_jj_min_m     .push_back( book( name, hjjmin + "_m",     hjjminstr + " invariant mass [GeV]", 100,    0, 1500 ) );
	  h_jj_min_sumPt .push_back( book( name, hjjmin + "_sumPt", hjjminstr + " sum-p_{T} [GeV]",      100,    0, 2000 ) );
	  h_jj_min_sumM  .push_back( book( name, hjjmin + "_sumM",  hjjminstr + " sum-mass [GeV]",       100,    0,  300 ) );
	  h_jj_min_dR    .push_back( book( name, hjjmin + "_dR",    hjjminstr + " dR",                   100,    0,    6 ) );
	  // min/max dijet ntrk system
	  std::vector<int>   djnt_nbin    = {   100,  125,   75,  10,  20,  20,  20,  20 };
	  std::vector<int>   djnt_x2      = {   400,  250,   75,  10,  20,  20,  20,  20 };
	  std::vector<float> djntpt_x2    = {  5000, 2000,  800,  25, 100, 100, 100, 100 };
	  std::vector<float> djntmu_x2    = { 10000, 4000, 1600,  30, 120, 120, 120, 120 };
	  std::vector<float> djntml_x2    = {  5000, 2000,  800,  15,  60,  60,  60,  60 };
	  std::vector<float> djntsumpt_x2 = { 10000, 4000, 1600,  50, 200, 200, 200, 200 };
	  std::vector<float> djntsumm_x2  = {    75,   50,   15,   5,  10,  10,  10,  10 };
	  std::vector<TH1F*> h_jj_max_ntrack;
	  std::vector<TH1F*> h_jj_max_ntrack_pt;
	  std::vector<TH1F*> h_jj_max_ntrack_eta;
	  std::vector<TH1F*> h_jj_max_ntrack_phi;
	  std::vector<TH1F*> h_jj_max_ntrack_m;
	  std::vector<TH1F*> h_jj_max_ntrack_sumPt;
	  std::vector<TH1F*> h_jj_max_ntrack_sumM;
	  std::vector<TH1F*> h_jj_min_ntrack;
	  std::vector<TH1F*> h_jj_min_ntrack_pt;
	  std::vector<TH1F*> h_jj_min_ntrack_eta;
	  std::vector<TH1F*> h_jj_min_ntrack_phi;
	  std::vector<TH1F*> h_jj_min_ntrack_m;
	  std::vector<TH1F*> h_jj_min_ntrack_sumPt;
	  std::vector<TH1F*> h_jj_min_ntrack_sumM;
	  for ( size_t j = 0; j != hTrk.size(); ++j ) {
	    std::string htsubstr = "matched";
	    if ( !hTrkstr[j].empty() ) htsubstr += " ";
	    std::string ht          = hTrk[j] + "trk";
	    std::string hnt         = "n" + ht;
	    std::string hntstr      = htsubstr + hTrkstr[j] + " n-track";
	    std::string hjjmaxnt    = hjjmax    + "_" + hnt;
	    std::string hjjmaxntstr = hjjmaxstr + " " + hntstr;
	    std::string hjjminnt    = hjjmin    + "_" + hnt;
	    std::string hjjminntstr = hjjminstr + " " + hntstr;
	    h_jj_max_ntrack        .push_back( book( name, hjjmaxnt,           hntstr + "s per " + hjjmaxstr, djnt_nbin[j], 0, djnt_x2   [j] ) );
	    h_jj_min_ntrack        .push_back( book( name, hjjminnt,           hntstr + "s per " + hjjminstr, djnt_nbin[j], 0, djnt_x2   [j] ) );
	    if ( m_histoInfoSwitch->m_dijetTrks ) {
	      h_jj_max_ntrack_pt   .push_back( book( name, hjjmaxnt + "_pt",   hjjmaxntstr + " p_{T} [GeV]",         100, 0, djntpt_x2   [j] ) );
	      h_jj_max_ntrack_eta  .push_back( book( name, hjjmaxnt + "_eta",  hjjmaxntstr + " eta",                 100,-5,               5 ) );
	      h_jj_max_ntrack_phi  .push_back( book( name, hjjmaxnt + "_phi",  hjjmaxntstr + " phi",                 100,-3.5,           3.5 ) );
	      h_jj_max_ntrack_m    .push_back( book( name, hjjmaxnt + "_m",    hjjmaxntstr + " invariant mass [GeV]",100, 0, djntmu_x2   [j] ) );
	      h_jj_max_ntrack_sumPt.push_back( book( name, hjjmaxnt + "_sumPt",hjjmaxntstr + " sum-p_{T} [GeV]",     100, 0, djntsumpt_x2[j] ) );
	      h_jj_max_ntrack_sumM .push_back( book( name, hjjmaxnt + "_sumM", hjjmaxntstr + " sum-mass [GeV]",      100, 0, djntsumm_x2 [j] ) );
	      h_jj_min_ntrack_pt   .push_back( book( name, hjjminnt + "_pt",   hjjminntstr + " p_{T} [GeV]",         100, 0, djntpt_x2   [j] ) );
	      h_jj_min_ntrack_eta  .push_back( book( name, hjjminnt + "_eta",  hjjminntstr + " eta",                 100,-5,               5 ) );
	      h_jj_min_ntrack_phi  .push_back( book( name, hjjminnt + "_phi",  hjjminntstr + " phi",                 100,-3.5,           3.5 ) );
	      h_jj_min_ntrack_m    .push_back( book( name, hjjminnt + "_m",    hjjminntstr + " invariant mass [GeV]",100, 0, djntml_x2   [j] ) );
	      h_jj_min_ntrack_sumPt.push_back( book( name, hjjminnt + "_sumPt",hjjminntstr + " sum-p_{T} [GeV]",     100, 0, djntsumpt_x2[j] ) );
	      h_jj_min_ntrack_sumM .push_back( book( name, hjjminnt + "_sumM", hjjminntstr + " sum-mass [GeV]",      100, 0, djntsumm_x2 [j] ) );
	    }
	  }
	  h_jj_max_ntrk         .push_back( h_jj_max_ntrack       );
	  h_jj_min_ntrk         .push_back( h_jj_min_ntrack       );
	  if ( m_histoInfoSwitch->m_dijetTrks ) {
	    h_jj_max_ntrk_pt    .push_back( h_jj_max_ntrack_pt    );
	    h_jj_max_ntrk_eta   .push_back( h_jj_max_ntrack_eta   );
	    h_jj_max_ntrk_phi   .push_back( h_jj_max_ntrack_phi   );
	    h_jj_max_ntrk_m     .push_back( h_jj_max_ntrack_m     );
	    h_jj_max_ntrk_sumPt .push_back( h_jj_max_ntrack_sumPt );
	    h_jj_max_ntrk_sumM  .push_back( h_jj_max_ntrack_sumM  );
	    h_jj_min_ntrk_pt    .push_back( h_jj_min_ntrack_pt    );
	    h_jj_min_ntrk_eta   .push_back( h_jj_min_ntrack_eta   );
	    h_jj_min_ntrk_phi   .push_back( h_jj_min_ntrack_phi   );
	    h_jj_min_ntrk_m     .push_back( h_jj_min_ntrack_m     );
	    h_jj_min_ntrk_sumPt .push_back( h_jj_min_ntrack_sumPt );
	    h_jj_min_ntrk_sumM  .push_back( h_jj_min_ntrack_sumM  );
	  }
	  // min/max dijet nsv system
	  std::vector<TH1F*> h_jj_max_nsecvtx;
	  std::vector<TH1F*> h_jj_max_nsecvtx_pt;
	  std::vector<TH1F*> h_jj_max_nsecvtx_eta;
	  std::vector<TH1F*> h_jj_max_nsecvtx_phi;
	  std::vector<TH1F*> h_jj_max_nsecvtx_m;
	  std::vector<TH1F*> h_jj_max_nsecvtx_sumPt;
	  std::vector<TH1F*> h_jj_max_nsecvtx_sumM;
	  std::vector<TH1F*> h_jj_min_nsecvtx;
	  std::vector<TH1F*> h_jj_min_nsecvtx_pt;
	  std::vector<TH1F*> h_jj_min_nsecvtx_eta;
	  std::vector<TH1F*> h_jj_min_nsecvtx_phi;
	  std::vector<TH1F*> h_jj_min_nsecvtx_m;
	  std::vector<TH1F*> h_jj_min_nsecvtx_sumPt;
	  std::vector<TH1F*> h_jj_min_nsecvtx_sumM;
	  for ( size_t k = 0; k != hJDV.size(); ++k ) {
	    std::string hv          = hJDV[k] + "SV"; hv[0] = tolower(hv[0]);
	    std::string hdvstr      = hJDVstr[k];     hdvstr.pop_back();
	    std::string hnv         = "n" + hv;
	    std::string hnvstr      = "matched " + hdvstr + " n-SV";
	    std::string hjjmaxnv    = hjjmax     + "_" + hnv;
	    std::string hjjminnv    = hjjmin     + "_" + hnv;
	    std::string hjjmaxnvstr = hjjmaxstr  + " " + hnvstr;
	    std::string hjjminnvstr = hjjminstr  + " " + hnvstr;
	    h_jj_max_nsecvtx         .push_back( book( name, hjjmaxnv,            hnvstr + "s per " + hjjmaxstr,          10,    0,   10 ) );
	    h_jj_min_nsecvtx         .push_back( book( name, hjjminnv,            hnvstr + "s per " + hjjminstr,          10,    0,   10 ) );
	    if ( m_histoInfoSwitch->m_dijetVerts ) {
	      h_jj_max_nsecvtx_pt    .push_back( book( name, hjjmaxnv + "_pt",    hjjmaxnvstr + " p_{T} [GeV]",          100,    0,  150 ) );
	      h_jj_max_nsecvtx_eta   .push_back( book( name, hjjmaxnv + "_eta",   hjjmaxnvstr + " eta",                  100,   -5,    5 ) );
	      h_jj_max_nsecvtx_phi   .push_back( book( name, hjjmaxnv + "_phi",   hjjmaxnvstr + " phi",                  100, -3.5,  3.5 ) );
	      h_jj_max_nsecvtx_m     .push_back( book( name, hjjmaxnv + "_m",     hjjmaxnvstr + " invariant mass [GeV]", 100,    0,  100 ) );
	      h_jj_max_nsecvtx_sumPt .push_back( book( name, hjjmaxnv + "_sumPt", hjjmaxnvstr + " sum-p_{T} [GeV]",      100,    0,  200 ) );
	      h_jj_max_nsecvtx_sumM  .push_back( book( name, hjjmaxnv + "_sumM",  hjjmaxnvstr + " sum-mass [GeV]",       100,    0,   25 ) );
	      h_jj_min_nsecvtx_pt    .push_back( book( name, hjjminnv + "_pt",    hjjminnvstr + " p_{T} [GeV]",          100,    0,  150 ) );
	      h_jj_min_nsecvtx_eta   .push_back( book( name, hjjminnv + "_eta",   hjjminnvstr + " eta",                  100,   -5,    5 ) );
	      h_jj_min_nsecvtx_phi   .push_back( book( name, hjjminnv + "_phi",   hjjminnvstr + " phi",                  100, -3.5,  3.5 ) );
	      h_jj_min_nsecvtx_m     .push_back( book( name, hjjminnv + "_m",     hjjminnvstr + " invariant mass [GeV]", 100,    0,   50 ) );
	      h_jj_min_nsecvtx_sumPt .push_back( book( name, hjjminnv + "_sumPt", hjjminnvstr + " sum-p_{T} [GeV]",      100,    0,  200 ) );
	      h_jj_min_nsecvtx_sumM  .push_back( book( name, hjjminnv + "_sumM",  hjjminnvstr + " sum-mass [GeV]",       100,    0,   25 ) );
	    }
	  }
	  h_jj_max_nsv         .push_back( h_jj_max_nsecvtx       );
	  h_jj_min_nsv         .push_back( h_jj_min_nsecvtx       );
	  if ( m_histoInfoSwitch->m_dijetVerts ) {
	    h_jj_max_nsv_pt    .push_back( h_jj_max_nsecvtx_pt    );
	    h_jj_max_nsv_eta   .push_back( h_jj_max_nsecvtx_eta   );
	    h_jj_max_nsv_phi   .push_back( h_jj_max_nsecvtx_phi   );
	    h_jj_max_nsv_m     .push_back( h_jj_max_nsecvtx_m     );
	    h_jj_max_nsv_sumPt .push_back( h_jj_max_nsecvtx_sumPt );
	    h_jj_max_nsv_sumM  .push_back( h_jj_max_nsecvtx_sumM  );
	    h_jj_min_nsv_pt    .push_back( h_jj_min_nsecvtx_pt    );
	    h_jj_min_nsv_eta   .push_back( h_jj_min_nsecvtx_eta   );
	    h_jj_min_nsv_phi   .push_back( h_jj_min_nsecvtx_phi   );
	    h_jj_min_nsv_m     .push_back( h_jj_min_nsecvtx_m     );
	    h_jj_min_nsv_sumPt .push_back( h_jj_min_nsecvtx_sumPt );
	    h_jj_min_nsv_sumM  .push_back( h_jj_min_nsecvtx_sumM  );
	  }

	  std::string hjjmaxpt    = hjj    + "_maxPt";
	  std::string hjjmaxptstr = hjjstr + " max-pt";
	  std::string hjjminpt    = hjj    + "_minPt";
	  std::string hjjminptstr = hjjstr + " min-pt";
	  // max-pt dijet system
	  h_jj_maxpt_pt    .push_back( book( name, hjjmaxpt + "_pt",    hjjmaxptstr + " p_{T} [GeV]",          100,    0, 2500 ) ); // jz4w 2000
	  h_jj_maxpt_eta   .push_back( book( name, hjjmaxpt + "_eta",   hjjmaxptstr + " eta",                  100,   -5,    5 ) );
	  h_jj_maxpt_phi   .push_back( book( name, hjjmaxpt + "_phi",   hjjmaxptstr + " phi",                  100, -3.5,  3.5 ) );
	  h_jj_maxpt_m     .push_back( book( name, hjjmaxpt + "_m",     hjjmaxptstr + " invariant mass [GeV]", 100,    0, 3000 ) );
	  h_jj_maxpt_sumPt .push_back( book( name, hjjmaxpt + "_sumPt", hjjmaxptstr + " sum-p_{T} [GeV]",      100,    0, 3000 ) ); // jz4w 2000
	  h_jj_maxpt_sumM  .push_back( book( name, hjjmaxpt + "_sumM",  hjjmaxptstr + " sum-mass [GeV]",       100,    0,  400 ) );
	  h_jj_maxpt_dR    .push_back( book( name, hjjmaxpt + "_dR",    hjjmaxptstr + " dR",                   100,    0,    6 ) );
	  // min-pt dijet system
	  h_jj_minpt_pt    .push_back( book( name, hjjminpt + "_pt",    hjjminptstr + " p_{T} [GeV]",          100,    0, 1250 ) );
	  h_jj_minpt_eta   .push_back( book( name, hjjminpt + "_eta",   hjjminptstr + " eta",                  100,   -5,    5 ) );
	  h_jj_minpt_phi   .push_back( book( name, hjjminpt + "_phi",   hjjminptstr + " phi",                  100, -3.5,  3.5 ) );
	  h_jj_minpt_m     .push_back( book( name, hjjminpt + "_m",     hjjminptstr + " invariant mass [GeV]", 100,    0, 3000 ) );
	  h_jj_minpt_sumPt .push_back( book( name, hjjminpt + "_sumPt", hjjminptstr + " sum-p_{T} [GeV]",      100,    0, 3000 ) ); // jz4w 2000
	  h_jj_minpt_sumM  .push_back( book( name, hjjminpt + "_sumM",  hjjminptstr + " sum-mass [GeV]",       100,    0,  400 ) );
	  h_jj_minpt_dR    .push_back( book( name, hjjminpt + "_dR",    hjjminptstr + " dR",                   100,    0,    6 ) );
	  // min/max-pt dijet ntrk system
	  std::vector<TH1F*> h_jj_maxpt_ntrack;
	  std::vector<TH1F*> h_jj_maxpt_ntrack_pt;
	  std::vector<TH1F*> h_jj_maxpt_ntrack_eta;
	  std::vector<TH1F*> h_jj_maxpt_ntrack_phi;
	  std::vector<TH1F*> h_jj_maxpt_ntrack_m;
	  std::vector<TH1F*> h_jj_maxpt_ntrack_sumPt;
	  std::vector<TH1F*> h_jj_maxpt_ntrack_sumM;
	  std::vector<TH1F*> h_jj_minpt_ntrack;
	  std::vector<TH1F*> h_jj_minpt_ntrack_pt;
	  std::vector<TH1F*> h_jj_minpt_ntrack_eta;
	  std::vector<TH1F*> h_jj_minpt_ntrack_phi;
	  std::vector<TH1F*> h_jj_minpt_ntrack_m;
	  std::vector<TH1F*> h_jj_minpt_ntrack_sumPt;
	  std::vector<TH1F*> h_jj_minpt_ntrack_sumM;
	  for ( size_t j = 0; j != hTrk.size(); ++j ) {
	    std::string htsubstr = "matched";
	    if ( !hTrkstr[j].empty() ) htsubstr += " ";
	    std::string ht          = hTrk[j]  + "trk";
	    std::string hnt         = "n"      + ht;
	    std::string hntstr      = htsubstr + hTrkstr[j] + " n-track";
	    std::string hjjmaxnt    = hjjmaxpt    + "_" + hnt;
	    std::string hjjmaxntstr = hjjmaxptstr + " " + hntstr;
	    std::string hjjminnt    = hjjminpt    + "_" + hnt;
	    std::string hjjminntstr = hjjminptstr + " " + hntstr;
	    h_jj_maxpt_ntrack        .push_back( book( name, hjjmaxnt,           hntstr +"s per "+ hjjmaxptstr, djnt_nbin[j], 0, djnt_x2   [j] ) );
	    h_jj_minpt_ntrack        .push_back( book( name, hjjminnt,           hntstr +"s per "+ hjjminptstr, djnt_nbin[j], 0, djnt_x2   [j] ) );
	    if ( m_histoInfoSwitch->m_dijetTrks ) {
	      h_jj_maxpt_ntrack_pt   .push_back( book( name, hjjmaxnt + "_pt",   hjjmaxntstr + " p_{T} [GeV]",         100, 0, djntpt_x2   [j] ) );
	      h_jj_maxpt_ntrack_eta  .push_back( book( name, hjjmaxnt + "_eta",  hjjmaxntstr + " eta",                 100,-5,               5 ) );
	      h_jj_maxpt_ntrack_phi  .push_back( book( name, hjjmaxnt + "_phi",  hjjmaxntstr + " phi",                 100,-3.5,           3.5 ) );
	      h_jj_maxpt_ntrack_m    .push_back( book( name, hjjmaxnt + "_m",    hjjmaxntstr + " invariant mass [GeV]",100, 0, djntmu_x2   [j] ) );
	      h_jj_maxpt_ntrack_sumPt.push_back( book( name, hjjmaxnt + "_sumPt",hjjmaxntstr + " sum-p_{T} [GeV]",     100, 0, djntsumpt_x2[j] ) );
	      h_jj_maxpt_ntrack_sumM .push_back( book( name, hjjmaxnt + "_sumM", hjjmaxntstr + " sum-mass [GeV]",      100, 0, djntsumm_x2 [j] ) );
	      h_jj_minpt_ntrack_pt   .push_back( book( name, hjjminnt + "_pt",   hjjminntstr + " p_{T} [GeV]",         100, 0, djntpt_x2   [j] ) );
	      h_jj_minpt_ntrack_eta  .push_back( book( name, hjjminnt + "_eta",  hjjminntstr + " eta",                 100,-5,               5 ) );
	      h_jj_minpt_ntrack_phi  .push_back( book( name, hjjminnt + "_phi",  hjjminntstr + " phi",                 100,-3.5,           3.5 ) );
	      h_jj_minpt_ntrack_m    .push_back( book( name, hjjminnt + "_m",    hjjminntstr + " invariant mass [GeV]",100, 0, djntml_x2   [j] ) );
	      h_jj_minpt_ntrack_sumPt.push_back( book( name, hjjminnt + "_sumPt",hjjminntstr + " sum-p_{T} [GeV]",     100, 0, djntsumpt_x2[j] ) );
	      h_jj_minpt_ntrack_sumM .push_back( book( name, hjjminnt + "_sumM", hjjminntstr + " sum-mass [GeV]",      100, 0, djntsumm_x2 [j] ) );
	    }
	  }
	  h_jj_maxpt_ntrk         .push_back( h_jj_maxpt_ntrack       );
	  h_jj_minpt_ntrk         .push_back( h_jj_minpt_ntrack       );
	  if ( m_histoInfoSwitch->m_dijetTrks ) {
	    h_jj_maxpt_ntrk_pt    .push_back( h_jj_maxpt_ntrack_pt    );
	    h_jj_maxpt_ntrk_eta   .push_back( h_jj_maxpt_ntrack_eta   );
	    h_jj_maxpt_ntrk_phi   .push_back( h_jj_maxpt_ntrack_phi   );
	    h_jj_maxpt_ntrk_m     .push_back( h_jj_maxpt_ntrack_m     );
	    h_jj_maxpt_ntrk_sumPt .push_back( h_jj_maxpt_ntrack_sumPt );
	    h_jj_maxpt_ntrk_sumM  .push_back( h_jj_maxpt_ntrack_sumM  );
	    h_jj_minpt_ntrk_pt    .push_back( h_jj_minpt_ntrack_pt    );
	    h_jj_minpt_ntrk_eta   .push_back( h_jj_minpt_ntrack_eta   );
	    h_jj_minpt_ntrk_phi   .push_back( h_jj_minpt_ntrack_phi   );
	    h_jj_minpt_ntrk_m     .push_back( h_jj_minpt_ntrack_m     );
	    h_jj_minpt_ntrk_sumPt .push_back( h_jj_minpt_ntrack_sumPt );
	    h_jj_minpt_ntrk_sumM  .push_back( h_jj_minpt_ntrack_sumM  );
	  }
	  // min/max-pt dijet nsv system
	  std::vector<TH1F*> h_jj_maxpt_nsecvtx;
	  std::vector<TH1F*> h_jj_maxpt_nsecvtx_pt;
	  std::vector<TH1F*> h_jj_maxpt_nsecvtx_eta;
	  std::vector<TH1F*> h_jj_maxpt_nsecvtx_phi;
	  std::vector<TH1F*> h_jj_maxpt_nsecvtx_m;
	  std::vector<TH1F*> h_jj_maxpt_nsecvtx_sumPt;
	  std::vector<TH1F*> h_jj_maxpt_nsecvtx_sumM;
	  std::vector<TH1F*> h_jj_minpt_nsecvtx;
	  std::vector<TH1F*> h_jj_minpt_nsecvtx_pt;
	  std::vector<TH1F*> h_jj_minpt_nsecvtx_eta;
	  std::vector<TH1F*> h_jj_minpt_nsecvtx_phi;
	  std::vector<TH1F*> h_jj_minpt_nsecvtx_m;
	  std::vector<TH1F*> h_jj_minpt_nsecvtx_sumPt;
	  std::vector<TH1F*> h_jj_minpt_nsecvtx_sumM;
	  for ( size_t k = 0; k != hJDV.size(); ++k ) {
	    std::string hv          = hJDV[k] + "SV"; hv[0] = tolower(hv[0]);
	    std::string hdvstr      = hJDVstr[k];     hdvstr.pop_back();
	    std::string hnv         = "n" + hv;
	    std::string hnvstr      = "matched " + hdvstr + " n-SV";
	    std::string hjjmaxnv    = hjjmaxpt     + "_" + hnv;
	    std::string hjjminnv    = hjjminpt     + "_" + hnv;
	    std::string hjjmaxnvstr = hjjmaxptstr  + " " + hnvstr;
	    std::string hjjminnvstr = hjjminptstr  + " " + hnvstr;
	    h_jj_maxpt_nsecvtx         .push_back( book( name, hjjmaxnv,            hnvstr + "s per " + hjjmaxptstr,        10,    0,   10 ) );
	    h_jj_minpt_nsecvtx         .push_back( book( name, hjjminnv,            hnvstr + "s per " + hjjminptstr,        10,    0,   10 ) );
	    if ( m_histoInfoSwitch->m_dijetVerts ) {
	      h_jj_maxpt_nsecvtx_pt    .push_back( book( name, hjjmaxnv + "_pt",    hjjmaxnvstr + " p_{T} [GeV]",          100,    0,  150 ) );
	      h_jj_maxpt_nsecvtx_eta   .push_back( book( name, hjjmaxnv + "_eta",   hjjmaxnvstr + " eta",                  100,   -5,    5 ) );
	      h_jj_maxpt_nsecvtx_phi   .push_back( book( name, hjjmaxnv + "_phi",   hjjmaxnvstr + " phi",                  100, -3.5,  3.5 ) );
	      h_jj_maxpt_nsecvtx_m     .push_back( book( name, hjjmaxnv + "_m",     hjjmaxnvstr + " invariant mass [GeV]", 100,    0,  100 ) );
	      h_jj_maxpt_nsecvtx_sumPt .push_back( book( name, hjjmaxnv + "_sumPt", hjjmaxnvstr + " sum-p_{T} [GeV]",      100,    0,  200 ) );
	      h_jj_maxpt_nsecvtx_sumM  .push_back( book( name, hjjmaxnv + "_sumM",  hjjmaxnvstr + " sum-mass [GeV]",       100,    0,   25 ) );
	      h_jj_minpt_nsecvtx_pt    .push_back( book( name, hjjminnv + "_pt",    hjjminnvstr + " p_{T} [GeV]",          100,    0,  150 ) );
	      h_jj_minpt_nsecvtx_eta   .push_back( book( name, hjjminnv + "_eta",   hjjminnvstr + " eta",                  100,   -5,    5 ) );
	      h_jj_minpt_nsecvtx_phi   .push_back( book( name, hjjminnv + "_phi",   hjjminnvstr + " phi",                  100, -3.5,  3.5 ) );
	      h_jj_minpt_nsecvtx_m     .push_back( book( name, hjjminnv + "_m",     hjjminnvstr + " invariant mass [GeV]", 100,    0,   50 ) );
	      h_jj_minpt_nsecvtx_sumPt .push_back( book( name, hjjminnv + "_sumPt", hjjminnvstr + " sum-p_{T} [GeV]",      100,    0,  200 ) );
	      h_jj_minpt_nsecvtx_sumM  .push_back( book( name, hjjminnv + "_sumM",  hjjminnvstr + " sum-mass [GeV]",       100,    0,   25 ) );
	    }
	  }
	  h_jj_maxpt_nsv         .push_back( h_jj_maxpt_nsecvtx       );
	  h_jj_minpt_nsv         .push_back( h_jj_minpt_nsecvtx       );
	  if ( m_histoInfoSwitch->m_dijetVerts ) {
	    h_jj_maxpt_nsv_pt    .push_back( h_jj_maxpt_nsecvtx_pt    );
	    h_jj_maxpt_nsv_eta   .push_back( h_jj_maxpt_nsecvtx_eta   );
	    h_jj_maxpt_nsv_phi   .push_back( h_jj_maxpt_nsecvtx_phi   );
	    h_jj_maxpt_nsv_m     .push_back( h_jj_maxpt_nsecvtx_m     );
	    h_jj_maxpt_nsv_sumPt .push_back( h_jj_maxpt_nsecvtx_sumPt );
	    h_jj_maxpt_nsv_sumM  .push_back( h_jj_maxpt_nsecvtx_sumM  );
	    h_jj_minpt_nsv_pt    .push_back( h_jj_minpt_nsecvtx_pt    );
	    h_jj_minpt_nsv_eta   .push_back( h_jj_minpt_nsecvtx_eta   );
	    h_jj_minpt_nsv_phi   .push_back( h_jj_minpt_nsecvtx_phi   );
	    h_jj_minpt_nsv_m     .push_back( h_jj_minpt_nsecvtx_m     );
	    h_jj_minpt_nsv_sumPt .push_back( h_jj_minpt_nsecvtx_sumPt );
	    h_jj_minpt_nsv_sumM  .push_back( h_jj_minpt_nsecvtx_sumM  );
	  }
	} // end dijet info switch
      
	// event-level jets (all jets in event)
	if ( m_histoInfoSwitch->m_njets ) {
	  h_nj_pt    .push_back( book( name, hnj + "_pt",    hnjstr + " p_{T} [GeV]",          100,    0,  1000 ) );
	  h_nj_eta   .push_back( book( name, hnj + "_eta",   hnjstr + " eta",                  100,   -7,     7 ) );
	  h_nj_phi   .push_back( book( name, hnj + "_phi",   hnjstr + " phi",                  100, -3.5,   3.5 ) );
	  h_nj_m     .push_back( book( name, hnj + "_m",     hnjstr + " invariant mass [GeV]", 100,    0,  6000 ) );
	  h_nj_sumPt .push_back( book( name, hnj + "_sumPt", hnjstr + " sum-p_{T} [GeV]",      100,    0,  5000 ) );
	  h_nj_sumM  .push_back( book( name, hnj + "_sumM",  hnjstr + " sum-mass [GeV]",       100,    0,   600 ) );
	  // --> event-level jet-matched tracks
	  std::vector<TH1F*> h_nj_ntrack;
	  std::vector<TH1F*> h_nj_ntrack_pt;
	  std::vector<TH1F*> h_nj_ntrack_eta;
	  std::vector<TH1F*> h_nj_ntrack_phi;
	  std::vector<TH1F*> h_nj_ntrack_m;
	  std::vector<TH1F*> h_nj_ntrack_sumPt;
	  std::vector<TH1F*> h_nj_ntrack_sumM;
	  std::vector<int>   njnt_nbin    = {   100,   100,  125,  15,  30,  30,  30,  30 };
	  std::vector<float> njnt_x2      = {  1000,   500,  125,  15,  30,  30,  30,  30 };
	  std::vector<float> njntpt_x2    = {  6000,  3000, 1000,  50, 200, 200, 200, 200 };
	  std::vector<float> njntm_x2     = { 12000,  6000, 2000,  25, 250, 250, 250, 250 };
	  std::vector<float> njntsumpt_x2 = { 12000,  6000, 2000,  50, 250, 250, 250, 250 };
	  std::vector<float> njntsumm_x2  = {   150,   100,   25,   5,  10,  10,  10,  10 };
	  for ( size_t j = 0; j != hTrk.size(); ++j ) {
	    std::string htsubstr = "matched";
	    if ( !hTrkstr[j].empty() ) htsubstr += " ";
	    std::string ht       = hTrk[j] + "trk";
	    std::string hnt      = "n" + ht;
	    std::string hntstr   = htsubstr + hTrkstr[j] + " n-track";
	    std::string hnjnt    = hnj + "_" + hnt;
	    std::string hnjntstr = hnjstr + " " + hntstr;
	    h_nj_ntrack         .push_back( book( name, hnjnt,            hntstr + "s per " + hnjstr, njnt_nbin[j], 0, njnt_x2  [j] ) );
	    if ( m_histoInfoSwitch->m_njetTrks ) {
	      h_nj_ntrack_pt    .push_back( book( name, hnjnt + "_pt",    hnjntstr+ " p_{T} [GeV]",     100,    0, njntpt_x2    [j] ) );
	      h_nj_ntrack_eta   .push_back( book( name, hnjnt + "_eta",   hnjntstr+ " eta",             100,   -5,                5 ) );
	      h_nj_ntrack_phi   .push_back( book( name, hnjnt + "_phi",   hnjntstr+ " phi",             100, -3.5,              3.5 ) );
	      h_nj_ntrack_m     .push_back( book( name, hnjnt + "_m",     hnjntstr+ " mass [GeV]",      100,    0, njntm_x2     [j] ) );
	      h_nj_ntrack_sumPt .push_back( book( name, hnjnt + "_sumPt", hnjntstr+ " sum-p_{T} [GeV]", 100,    0, njntsumpt_x2 [j] ) );
	      h_nj_ntrack_sumM  .push_back( book( name, hnjnt + "_sumM",  hnjntstr+ " sum-mass [GeV]",  100,    0, njntsumm_x2  [j] ) );
	    }
	  }
	  h_nj_ntrk         .push_back( h_nj_ntrack       );
	  if ( m_histoInfoSwitch->m_njetTrks ) {
	    h_nj_ntrk_pt    .push_back( h_nj_ntrack_pt    );
	    h_nj_ntrk_eta   .push_back( h_nj_ntrack_eta   );
	    h_nj_ntrk_phi   .push_back( h_nj_ntrack_phi   );
	    h_nj_ntrk_m     .push_back( h_nj_ntrack_m     );
	    h_nj_ntrk_sumPt .push_back( h_nj_ntrack_sumPt );
	    h_nj_ntrk_sumM  .push_back( h_nj_ntrack_sumM  );
	  }
	  // --> event-level jet-matched secondary vertices
	  std::vector<TH1F*> h_nj_nsecvtx;
	  std::vector<TH1F*> h_nj_nsecvtx_pt;
	  std::vector<TH1F*> h_nj_nsecvtx_eta;
	  std::vector<TH1F*> h_nj_nsecvtx_phi;
	  std::vector<TH1F*> h_nj_nsecvtx_m;
	  std::vector<TH1F*> h_nj_nsecvtx_sumPt;
	  std::vector<TH1F*> h_nj_nsecvtx_sumM;
	  for ( size_t k = 0; k != hJDV.size(); ++k ) {
	    std::string hv       = hJDV[k] + "SV"; hv[0] = tolower(hv[0]);
	    std::string hdvstr   = hJDVstr[k];     hdvstr.pop_back();
	    std::string hnv      = "n" + hv;
	    std::string hnvstr   = "matched " + hdvstr + " n-SV";
	    std::string hnjnv    = hnj    + "_" + hnv;
	    std::string hnjnvstr = hnjstr + " " + hnvstr;
	    h_nj_nsecvtx         .push_back( book( name, hnjnv,            hnvstr + "s per " + hnjstr,         20,    0,   20 ) );
	    if ( m_histoInfoSwitch->m_njetVerts ) {
	      h_nj_nsecvtx_pt    .push_back( book( name, hnjnv + "_pt",    hnjnvstr+ " p_{T} [GeV]",          100,    0,  200 ) );
	      h_nj_nsecvtx_eta   .push_back( book( name, hnjnv + "_eta",   hnjnvstr+ " eta",                  100,   -5,    5 ) );
	      h_nj_nsecvtx_phi   .push_back( book( name, hnjnv + "_phi",   hnjnvstr+ " phi",                  100, -3.5,  3.5 ) );
	      h_nj_nsecvtx_m     .push_back( book( name, hnjnv + "_m",     hnjnvstr+ " invariant mass [GeV]", 100,    0,  200 ) );
	      h_nj_nsecvtx_sumPt .push_back( book( name, hnjnv + "_sumPt", hnjnvstr+ " sum-p_{T} [GeV]",      100,    0,  200 ) );
	      h_nj_nsecvtx_sumM  .push_back( book( name, hnjnv + "_sumM",  hnjnvstr+ " sum-mass [GeV]",       100,    0,  100 ) );
	    }
	  }
	  h_nj_nsv         .push_back( h_nj_nsecvtx       );
	  if ( m_histoInfoSwitch->m_njetVerts ) {
	    h_nj_nsv_pt    .push_back( h_nj_nsecvtx_pt    );
	    h_nj_nsv_eta   .push_back( h_nj_nsecvtx_eta   );
	    h_nj_nsv_phi   .push_back( h_nj_nsecvtx_phi   );
	    h_nj_nsv_m     .push_back( h_nj_nsecvtx_m     );
	    h_nj_nsv_sumPt .push_back( h_nj_nsecvtx_sumPt );
	    h_nj_nsv_sumM  .push_back( h_nj_nsecvtx_sumM  );
	  }
	} // end njet info switch
      } // end loop over jet types
    
      h_jet_n         .push_back( h_j_n         );
      if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
	h_jet_pt        .push_back( h_j_pt        );
	h_jet_pt_s      .push_back( h_j_pt_s      );
	h_jet_eta       .push_back( h_j_eta       );
	h_jet_phi       .push_back( h_j_phi       );
	h_jet_E         .push_back( h_j_E         );
	h_jet_M         .push_back( h_j_M         );
	h_jet_rapid     .push_back( h_j_rapid     );
	h_jet_nConstits .push_back( h_j_nConstits );
	if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	  h_jet_px   .push_back( h_j_px    );
	  h_jet_py   .push_back( h_j_py    );
	  h_jet_pz   .push_back( h_j_pz    );
	  h_jet_Et   .push_back( h_j_Et    );
	  h_jet_Et_s .push_back( h_j_Et_s  );
	}
	if ( m_histoInfoSwitch->m_jetCalo ) {
	  h_jet_timing          .push_back( h_j_timing          );
	  h_jet_timing_s        .push_back( h_j_timing_s        );
	  h_jet_sqrtTiming      .push_back( h_j_sqrtTiming      );
	  h_jet_sqrtTiming_s    .push_back( h_j_sqrtTiming_s    );
	  h_jet_LArQual         .push_back( h_j_LArQual         );
	  h_jet_LArQual_s       .push_back( h_j_LArQual_s       );
	  h_jet_sqrtLArQual     .push_back( h_j_sqrtLArQual     );
	  h_jet_sqrtLArQual_s   .push_back( h_j_sqrtLArQual_s   );
	  h_jet_HECQual         .push_back( h_j_HECQual         );
	  h_jet_HECQual_s       .push_back( h_j_HECQual_s       );
	  h_jet_sqrtHECQual     .push_back( h_j_sqrtHECQual     );
	  h_jet_sqrtHECQual_s   .push_back( h_j_sqrtHECQual_s   );
	  h_jet_LArQmean        .push_back( h_j_LArQmean        );
	  h_jet_sqrtLArQmean    .push_back( h_j_sqrtLArQmean    );
	  h_jet_n90Constits     .push_back( h_j_n90Constits     );
	  h_jet_centroidR       .push_back( h_j_centroidR       );
	  h_jet_ootFrac5        .push_back( h_j_ootFrac5        );
	  h_jet_sqrtOotFrac5    .push_back( h_j_sqrtOotFrac5    );
	  h_jet_ootFrac10       .push_back( h_j_ootFrac10       );
	  h_jet_sqrtOotFrac10   .push_back( h_j_sqrtOotFrac10   );
	  h_jet_ootFrac5_s      .push_back( h_j_ootFrac5_s      );
	  h_jet_sqrtOotFrac5_s  .push_back( h_j_sqrtOotFrac5_s  );
	  h_jet_ootFrac10_s     .push_back( h_j_ootFrac10_s     );
	  h_jet_sqrtOotFrac10_s .push_back( h_j_sqrtOotFrac10_s );
	  h_jet_fracSampMax     .push_back( h_j_fracSampMax     );
	  h_jet_leadClustPt     .push_back( h_j_leadClustPt     );
	  h_jet_leadClustCtrL   .push_back( h_j_leadClustCtrL   );
	  h_jet_leadClust2ndL   .push_back( h_j_leadClust2ndL   );
	  h_jet_leadClust2ndR   .push_back( h_j_leadClust2ndR   );
	  h_jet_EMFrac          .push_back( h_j_EMFrac          );
	  h_jet_HECFrac         .push_back( h_j_HECFrac         );
	  h_jet_nonzeroHECFrac  .push_back( h_j_nonzeroHECFrac  );
	  h_jet_width           .push_back( h_j_width           );
	}
	if ( m_histoInfoSwitch->m_jetTrkMom ) {
	  h_jet_ntrkPt10      .push_back( h_j_ntrkPt10      );
	  h_jet_sumPtTrkPt10  .push_back( h_j_sumPtTrkPt10  );
	  h_jet_trkWidthPt10  .push_back( h_j_trkWidthPt10  );
	  h_jet_ntrkPt5       .push_back( h_j_ntrkPt5       );
	  h_jet_sumPtTrkPt5   .push_back( h_j_sumPtTrkPt5   );
	  h_jet_trkWidthPt5   .push_back( h_j_trkWidthPt5   );
	  h_jet_JVF           .push_back( h_j_JVF           );
	}
	if ( m_mc )
	  h_jet_partonID      .push_back( h_j_partonID      );
    
	h_jet_ntrk               .push_back( h_j_ntrk             );
	h_jet_trk_dR             .push_back( h_j_trk_dR           );
	h_jet_trk_minDR          .push_back( h_j_trk_minDR        );
	h_jet_trk_maxDR          .push_back( h_j_trk_maxDR        );
	if ( m_histoInfoSwitch->m_jetTrks ) {
	  h_jet_trk_pt           .push_back( h_j_trk_pt           );
	  h_jet_trk_d0           .push_back( h_j_trk_d0           );
	  h_jet_trk_mind0        .push_back( h_j_trk_mind0        );
	  h_jet_trk_maxd0        .push_back( h_j_trk_maxd0        );
	  h_jet_trk_sumd0        .push_back( h_j_trk_sumd0        );
	  h_jet_trk_z0           .push_back( h_j_trk_z0           );
	  h_jet_trk_minz0        .push_back( h_j_trk_minz0        );
	  h_jet_trk_maxz0        .push_back( h_j_trk_maxz0        );
	  h_jet_trk_sumz0        .push_back( h_j_trk_sumz0        );
	  h_jet_trk_errd0        .push_back( h_j_trk_errd0        );
	  h_jet_trk_minErrd0     .push_back( h_j_trk_minErrd0     );
	  h_jet_trk_maxErrd0     .push_back( h_j_trk_maxErrd0     );
	  h_jet_trk_sumErrd0     .push_back( h_j_trk_sumErrd0     );
	  h_jet_trk_errz0        .push_back( h_j_trk_errz0        );
	  h_jet_trk_minErrz0     .push_back( h_j_trk_minErrz0     );
	  h_jet_trk_maxErrz0     .push_back( h_j_trk_maxErrz0     );
	  h_jet_trk_sumErrz0     .push_back( h_j_trk_sumErrz0     );
	  h_jet_trk_sqrtpt       .push_back( h_j_trk_sqrtpt       );
	  h_jet_trk_sqrtd0       .push_back( h_j_trk_sqrtd0       );
	  h_jet_trk_sqrtmind0    .push_back( h_j_trk_sqrtmind0    );
	  h_jet_trk_sqrtmaxd0    .push_back( h_j_trk_sqrtmaxd0    );
	  h_jet_trk_sqrtsumd0    .push_back( h_j_trk_sqrtsumd0    );
	  h_jet_trk_sqrtz0       .push_back( h_j_trk_sqrtz0       );
	  h_jet_trk_sqrtminz0    .push_back( h_j_trk_sqrtminz0    );
	  h_jet_trk_sqrtmaxz0    .push_back( h_j_trk_sqrtmaxz0    );
	  h_jet_trk_sqrtsumz0    .push_back( h_j_trk_sqrtsumz0    );
	  h_jet_trk_sqrterrd0    .push_back( h_j_trk_sqrterrd0    );
	  h_jet_trk_sqrtminErrd0 .push_back( h_j_trk_sqrtminErrd0 );
	  h_jet_trk_sqrtmaxErrd0 .push_back( h_j_trk_sqrtmaxErrd0 );
	  h_jet_trk_sqrtsumErrd0 .push_back( h_j_trk_sqrtsumErrd0 );
	  h_jet_trk_sqrterrz0    .push_back( h_j_trk_sqrterrz0    );
	  h_jet_trk_sqrtminErrz0 .push_back( h_j_trk_sqrtminErrz0 );
	  h_jet_trk_sqrtmaxErrz0 .push_back( h_j_trk_sqrtmaxErrz0 );
	  h_jet_trk_sqrtsumErrz0 .push_back( h_j_trk_sqrtsumErrz0 );
	  h_jet_trk_nSCT         .push_back( h_j_trk_nSCT         );
	  h_jet_trk_nPixel       .push_back( h_j_trk_nPixel       );
	  h_jet_trk_nSi          .push_back( h_j_trk_nSi          );
	  h_jet_trk_nTRT         .push_back( h_j_trk_nTRT         );
	  h_jet_ntrk_pt          .push_back( h_j_ntrk_pt          );
	  h_jet_ntrk_eta         .push_back( h_j_ntrk_eta         );
	  h_jet_ntrk_phi         .push_back( h_j_ntrk_phi         );
	  h_jet_ntrk_m           .push_back( h_j_ntrk_m           );
	  h_jet_ntrk_sumPt       .push_back( h_j_ntrk_sumPt       );
	  h_jet_ntrk_sqrtsumPt   .push_back( h_j_ntrk_sqrtsumPt   );
	}
    
	h_jet_nsv             .push_back( h_j_nsv           );
	h_jet_sv_dR           .push_back( h_j_sv_dR         );
	h_jet_sv_minDR        .push_back( h_j_sv_minDR      );
	h_jet_sv_maxDR        .push_back( h_j_sv_maxDR      );
	if ( m_histoInfoSwitch->m_jetVerts ) {
	  h_jet_sv_pt         .push_back( h_j_sv_pt         );
	  h_jet_sv_Ht         .push_back( h_j_sv_Ht         );
	  h_jet_sv_H          .push_back( h_j_sv_H          );
	  h_jet_sv_sqrtpt     .push_back( h_j_sv_sqrtpt     );
	  h_jet_sv_sqrtHt     .push_back( h_j_sv_sqrtHt     );
	  h_jet_sv_sqrtH      .push_back( h_j_sv_sqrtH      );
	  h_jet_sv_mass       .push_back( h_j_sv_mass       );
	  h_jet_sv_mass_s     .push_back( h_j_sv_mass_s     );
	  h_jet_sv_ntrk       .push_back( h_j_sv_ntrk       );
	  h_jet_sv_njtrk      .push_back( h_j_sv_njtrk      );
	  h_jet_sv_z          .push_back( h_j_sv_z          );
	  h_jet_sv_minz       .push_back( h_j_sv_minz       );
	  h_jet_sv_maxz       .push_back( h_j_sv_maxz       );
	  h_jet_sv_sumz       .push_back( h_j_sv_sumz       );
	  h_jet_sv_r          .push_back( h_j_sv_r          );
	  h_jet_sv_minr       .push_back( h_j_sv_minr       );
	  h_jet_sv_maxr       .push_back( h_j_sv_maxr       );
	  h_jet_sv_sumr       .push_back( h_j_sv_sumr       );
	  h_jet_sv_chi2       .push_back( h_j_sv_chi2       );
	  h_jet_nsv_pt        .push_back( h_j_nsv_pt        );
	  h_jet_nsv_eta       .push_back( h_j_nsv_eta       );
	  h_jet_nsv_phi       .push_back( h_j_nsv_phi       );
	  h_jet_nsv_m         .push_back( h_j_nsv_m         );
	  h_jet_nsv_sumPt     .push_back( h_j_nsv_sumPt     );
	  h_jet_nsv_sumHt     .push_back( h_j_nsv_sumHt     );
	  h_jet_nsv_sumH      .push_back( h_j_nsv_sumH      );
	  h_jet_nsv_sqrtsumPt .push_back( h_j_nsv_sqrtsumPt );
	  h_jet_nsv_sqrtsumHt .push_back( h_j_nsv_sqrtsumHt );
	  h_jet_nsv_sqrtsumH  .push_back( h_j_nsv_sqrtsumH  );
	  h_jet_nsv_sumMass   .push_back( h_j_nsv_sumMass   );
	  h_jet_nsv_sumMass_s .push_back( h_j_nsv_sumMass_s );
	  h_jet_nsv_ntrk      .push_back( h_j_nsv_ntrk      );
	  h_jet_nsv_njtrk     .push_back( h_j_nsv_njtrk     );
	}

	if ( m_numLeadJets ) {
	  h_jetN_pt        .push_back( h_nlj_pt        );
	  h_jetN_pt_s      .push_back( h_nlj_pt_s      );
	  h_jetN_eta       .push_back( h_nlj_eta       );
	  h_jetN_phi       .push_back( h_nlj_phi       );
	  h_jetN_E         .push_back( h_nlj_E         );
	  h_jetN_M         .push_back( h_nlj_M         );
	  h_jetN_rapid     .push_back( h_nlj_rapid     );
	  h_jetN_nConstits .push_back( h_nlj_nConstits );
	  if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	    h_jetN_Et      .push_back( h_nlj_Et        );
	    h_jetN_Et_s    .push_back( h_nlj_Et_s      );
	  }
	  h_jetN_ntrk               .push_back( h_nlj_ntrk             );
	  h_jetN_trk_minDR          .push_back( h_nlj_trk_minDR        );
	  h_jetN_trk_maxDR          .push_back( h_nlj_trk_maxDR        );
	  if ( m_histoInfoSwitch->m_jetTrks ) {
	    h_jetN_trk_mind0        .push_back( h_nlj_trk_mind0        );
	    h_jetN_trk_maxd0        .push_back( h_nlj_trk_maxd0        );
	    h_jetN_trk_sumd0        .push_back( h_nlj_trk_sumd0        );
	    h_jetN_trk_minz0        .push_back( h_nlj_trk_minz0        );
	    h_jetN_trk_maxz0        .push_back( h_nlj_trk_maxz0        );
	    h_jetN_trk_sumz0        .push_back( h_nlj_trk_sumz0        );
	    h_jetN_trk_minErrd0     .push_back( h_nlj_trk_minErrd0     );
	    h_jetN_trk_maxErrd0     .push_back( h_nlj_trk_maxErrd0     );
	    h_jetN_trk_sumErrd0     .push_back( h_nlj_trk_sumErrd0     );
	    h_jetN_trk_minErrz0     .push_back( h_nlj_trk_minErrz0     );
	    h_jetN_trk_maxErrz0     .push_back( h_nlj_trk_maxErrz0     );
	    h_jetN_trk_sumErrz0     .push_back( h_nlj_trk_sumErrz0     );
	    h_jetN_trk_sqrtmind0    .push_back( h_nlj_trk_sqrtmind0    );
	    h_jetN_trk_sqrtmaxd0    .push_back( h_nlj_trk_sqrtmaxd0    );
	    h_jetN_trk_sqrtsumd0    .push_back( h_nlj_trk_sqrtsumd0    );
	    h_jetN_trk_sqrtminz0    .push_back( h_nlj_trk_sqrtminz0    );
	    h_jetN_trk_sqrtmaxz0    .push_back( h_nlj_trk_sqrtmaxz0    );
	    h_jetN_trk_sqrtsumz0    .push_back( h_nlj_trk_sqrtsumz0    );
	    h_jetN_trk_sqrtminErrd0 .push_back( h_nlj_trk_sqrtminErrd0 );
	    h_jetN_trk_sqrtmaxErrd0 .push_back( h_nlj_trk_sqrtmaxErrd0 );
	    h_jetN_trk_sqrtsumErrd0 .push_back( h_nlj_trk_sqrtsumErrd0 );
	    h_jetN_trk_sqrtminErrz0 .push_back( h_nlj_trk_sqrtminErrz0 );
	    h_jetN_trk_sqrtmaxErrz0 .push_back( h_nlj_trk_sqrtmaxErrz0 );
	    h_jetN_trk_sqrtsumErrz0 .push_back( h_nlj_trk_sqrtsumErrz0 );
	    h_jetN_ntrk_pt          .push_back( h_nlj_ntrk_pt          );
	    h_jetN_ntrk_eta         .push_back( h_nlj_ntrk_eta         );
	    h_jetN_ntrk_phi         .push_back( h_nlj_ntrk_phi         );
	    h_jetN_ntrk_m           .push_back( h_nlj_ntrk_m           );
	    h_jetN_ntrk_sumPt       .push_back( h_nlj_ntrk_sumPt       );
	    h_jetN_ntrk_sqrtsumPt   .push_back( h_nlj_ntrk_sqrtsumPt   );
	  }
	  h_jetN_nsv             .push_back( h_nlj_nsv           );
	  h_jetN_sv_minDR        .push_back( h_nlj_sv_minDR      );
	  h_jetN_sv_maxDR        .push_back( h_nlj_sv_maxDR      );
	  if ( m_histoInfoSwitch->m_jetVerts ) {
	    h_jetN_sv_minz       .push_back( h_nlj_sv_minz       );
	    h_jetN_sv_maxz       .push_back( h_nlj_sv_maxz       );
	    h_jetN_sv_sumz       .push_back( h_nlj_sv_sumz       );
	    h_jetN_sv_minr       .push_back( h_nlj_sv_minr       );
	    h_jetN_sv_maxr       .push_back( h_nlj_sv_maxr       );
	    h_jetN_sv_sumr       .push_back( h_nlj_sv_sumr       );
	    h_jetN_nsv_pt        .push_back( h_nlj_nsv_pt        );
	    h_jetN_nsv_eta       .push_back( h_nlj_nsv_eta       );
	    h_jetN_nsv_phi       .push_back( h_nlj_nsv_phi       );
	    h_jetN_nsv_m         .push_back( h_nlj_nsv_m         );
	    h_jetN_nsv_sumPt     .push_back( h_nlj_nsv_sumPt     );
	    h_jetN_nsv_sumHt     .push_back( h_nlj_nsv_sumHt     );
	    h_jetN_nsv_sumH      .push_back( h_nlj_nsv_sumH      );
	    h_jetN_nsv_sqrtsumPt .push_back( h_nlj_nsv_sqrtsumPt );
	    h_jetN_nsv_sqrtsumHt .push_back( h_nlj_nsv_sqrtsumHt );
	    h_jetN_nsv_sqrtsumH  .push_back( h_nlj_nsv_sqrtsumH  );
	    h_jetN_nsv_sumMass   .push_back( h_nlj_nsv_sumMass   );
	    h_jetN_nsv_sumMass_s .push_back( h_nlj_nsv_sumMass_s );
	    h_jetN_nsv_ntrk      .push_back( h_nlj_nsv_ntrk      );
	    h_jetN_nsv_njtrk     .push_back( h_nlj_nsv_njtrk     );
	  }
	}
      } // end if not abcdcutOnly
    
      if ( m_histoInfoSwitch->m_dijets ) {
	if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
	  h_dijet_n                .push_back( h_jj_n                );
	  h_dijet_pt               .push_back( h_jj_pt               );
	  h_dijet_eta              .push_back( h_jj_eta              );
	  h_dijet_phi              .push_back( h_jj_phi              );
	  h_dijet_m                .push_back( h_jj_m                );
	  h_dijet_sumPt            .push_back( h_jj_sumPt            );
	  h_dijet_sumM             .push_back( h_jj_sumM             );
	  h_dijet_dR               .push_back( h_jj_dR               );
	}
	h_dijet_avgp4_pt           .push_back( h_jj_avg_pt           );
	h_dijet_avgp4_eta          .push_back( h_jj_avg_eta          );
	h_dijet_avgp4_phi          .push_back( h_jj_avg_phi          );
	h_dijet_avgp4_m            .push_back( h_jj_avg_m            );
	h_dijet_avgp4_sumPt        .push_back( h_jj_avg_sumPt        );
	h_dijet_avgp4_sumM         .push_back( h_jj_avg_sumM         );
	h_dijet_avgp4_dR           .push_back( h_jj_avg_dR           );
	h_dijet_maxp4_pt           .push_back( h_jj_max_pt           );
	h_dijet_maxp4_eta          .push_back( h_jj_max_eta          );
	h_dijet_maxp4_phi          .push_back( h_jj_max_phi          );
	h_dijet_maxp4_m            .push_back( h_jj_max_m            );
	h_dijet_maxp4_sumPt        .push_back( h_jj_max_sumPt        );
	h_dijet_maxp4_sumM         .push_back( h_jj_max_sumM         );
	h_dijet_maxp4_dR           .push_back( h_jj_max_dR           );
	h_dijet_minp4_pt           .push_back( h_jj_min_pt           );
	h_dijet_minp4_eta          .push_back( h_jj_min_eta          );
	h_dijet_minp4_phi          .push_back( h_jj_min_phi          );
	h_dijet_minp4_m            .push_back( h_jj_min_m            );
	h_dijet_minp4_sumPt        .push_back( h_jj_min_sumPt        );
	h_dijet_minp4_sumM         .push_back( h_jj_min_sumM         );
	h_dijet_minp4_dR           .push_back( h_jj_min_dR           );
	h_dijet_maxp4_ntrk         .push_back( h_jj_max_ntrk         );
	h_dijet_minp4_ntrk         .push_back( h_jj_min_ntrk         );
	if ( m_histoInfoSwitch->m_dijetTrks   ) {
	  h_dijet_maxp4_ntrk_pt    .push_back( h_jj_max_ntrk_pt      );
	  h_dijet_maxp4_ntrk_eta   .push_back( h_jj_max_ntrk_eta     );
	  h_dijet_maxp4_ntrk_phi   .push_back( h_jj_max_ntrk_phi     );
	  h_dijet_maxp4_ntrk_m     .push_back( h_jj_max_ntrk_m       );
	  h_dijet_maxp4_ntrk_sumPt .push_back( h_jj_max_ntrk_sumPt   );
	  h_dijet_maxp4_ntrk_sumM  .push_back( h_jj_max_ntrk_sumM    );
	  h_dijet_minp4_ntrk_pt    .push_back( h_jj_min_ntrk_pt      );
	  h_dijet_minp4_ntrk_eta   .push_back( h_jj_min_ntrk_eta     );
	  h_dijet_minp4_ntrk_phi   .push_back( h_jj_min_ntrk_phi     );
	  h_dijet_minp4_ntrk_m     .push_back( h_jj_min_ntrk_m       );
	  h_dijet_minp4_ntrk_sumPt .push_back( h_jj_min_ntrk_sumPt   );
	  h_dijet_minp4_ntrk_sumM  .push_back( h_jj_min_ntrk_sumM    );
	}
	h_dijet_maxp4_nsv          .push_back( h_jj_max_nsv          );
	h_dijet_minp4_nsv          .push_back( h_jj_min_nsv          );
	if ( m_histoInfoSwitch->m_dijetVerts ) {
	  h_dijet_maxp4_nsv_pt     .push_back( h_jj_max_nsv_pt       );
	  h_dijet_maxp4_nsv_eta    .push_back( h_jj_max_nsv_eta      );
	  h_dijet_maxp4_nsv_phi    .push_back( h_jj_max_nsv_phi      );
	  h_dijet_maxp4_nsv_m      .push_back( h_jj_max_nsv_m        );
	  h_dijet_maxp4_nsv_sumPt  .push_back( h_jj_max_nsv_sumPt    );
	  h_dijet_maxp4_nsv_sumM   .push_back( h_jj_max_nsv_sumM     );
	  h_dijet_minp4_nsv_pt     .push_back( h_jj_min_nsv_pt       );
	  h_dijet_minp4_nsv_eta    .push_back( h_jj_min_nsv_eta      );
	  h_dijet_minp4_nsv_phi    .push_back( h_jj_min_nsv_phi      );
	  h_dijet_minp4_nsv_m      .push_back( h_jj_min_nsv_m        );
	  h_dijet_minp4_nsv_sumPt  .push_back( h_jj_min_nsv_sumPt    );
	  h_dijet_minp4_nsv_sumM   .push_back( h_jj_min_nsv_sumM     );
	}
	h_dijet_maxpt_pt           .push_back( h_jj_maxpt_pt         );
	h_dijet_maxpt_eta          .push_back( h_jj_maxpt_eta        );
	h_dijet_maxpt_phi          .push_back( h_jj_maxpt_phi        );
	h_dijet_maxpt_m            .push_back( h_jj_maxpt_m          );
	h_dijet_maxpt_sumPt        .push_back( h_jj_maxpt_sumPt      );
	h_dijet_maxpt_sumM         .push_back( h_jj_maxpt_sumM       );
	h_dijet_maxpt_dR           .push_back( h_jj_maxpt_dR         );
	h_dijet_minpt_pt           .push_back( h_jj_minpt_pt         );
	h_dijet_minpt_eta          .push_back( h_jj_minpt_eta        );
	h_dijet_minpt_phi          .push_back( h_jj_minpt_phi        );
	h_dijet_minpt_m            .push_back( h_jj_minpt_m          );
	h_dijet_minpt_sumPt        .push_back( h_jj_minpt_sumPt      );
	h_dijet_minpt_sumM         .push_back( h_jj_minpt_sumM       );
	h_dijet_minpt_dR           .push_back( h_jj_minpt_dR         );
	h_dijet_maxpt_ntrk         .push_back( h_jj_maxpt_ntrk       );
	h_dijet_minpt_ntrk         .push_back( h_jj_minpt_ntrk       );
	if ( m_histoInfoSwitch->m_dijetTrks   ) {
	  h_dijet_maxpt_ntrk_pt    .push_back( h_jj_maxpt_ntrk_pt    );
	  h_dijet_maxpt_ntrk_eta   .push_back( h_jj_maxpt_ntrk_eta   );
	  h_dijet_maxpt_ntrk_phi   .push_back( h_jj_maxpt_ntrk_phi   );
	  h_dijet_maxpt_ntrk_m     .push_back( h_jj_maxpt_ntrk_m     );
	  h_dijet_maxpt_ntrk_sumPt .push_back( h_jj_maxpt_ntrk_sumPt );
	  h_dijet_maxpt_ntrk_sumM  .push_back( h_jj_maxpt_ntrk_sumM  );
	  h_dijet_minpt_ntrk_pt    .push_back( h_jj_minpt_ntrk_pt    );
	  h_dijet_minpt_ntrk_eta   .push_back( h_jj_minpt_ntrk_eta   );
	  h_dijet_minpt_ntrk_phi   .push_back( h_jj_minpt_ntrk_phi   );
	  h_dijet_minpt_ntrk_m     .push_back( h_jj_minpt_ntrk_m     );
	  h_dijet_minpt_ntrk_sumPt .push_back( h_jj_minpt_ntrk_sumPt );
	  h_dijet_minpt_ntrk_sumM  .push_back( h_jj_minpt_ntrk_sumM  );
	}
	h_dijet_maxpt_nsv          .push_back( h_jj_maxpt_nsv        );
	h_dijet_minpt_nsv          .push_back( h_jj_minpt_nsv        );
	if ( m_histoInfoSwitch->m_dijetVerts ) {
	  h_dijet_maxpt_nsv_pt     .push_back( h_jj_maxpt_nsv_pt     );
	  h_dijet_maxpt_nsv_eta    .push_back( h_jj_maxpt_nsv_eta    );
	  h_dijet_maxpt_nsv_phi    .push_back( h_jj_maxpt_nsv_phi    );
	  h_dijet_maxpt_nsv_m      .push_back( h_jj_maxpt_nsv_m      );
	  h_dijet_maxpt_nsv_sumPt  .push_back( h_jj_maxpt_nsv_sumPt  );
	  h_dijet_maxpt_nsv_sumM   .push_back( h_jj_maxpt_nsv_sumM   );
	  h_dijet_minpt_nsv_pt     .push_back( h_jj_minpt_nsv_pt     );
	  h_dijet_minpt_nsv_eta    .push_back( h_jj_minpt_nsv_eta    );
	  h_dijet_minpt_nsv_phi    .push_back( h_jj_minpt_nsv_phi    );
	  h_dijet_minpt_nsv_m      .push_back( h_jj_minpt_nsv_m      );
	  h_dijet_minpt_nsv_sumPt  .push_back( h_jj_minpt_nsv_sumPt  );
	  h_dijet_minpt_nsv_sumM   .push_back( h_jj_minpt_nsv_sumM   );
	}
      }
      if ( m_histoInfoSwitch->m_njets ) {
	h_njet_pt           .push_back( h_nj_pt         );
	h_njet_eta          .push_back( h_nj_eta        );
	h_njet_phi          .push_back( h_nj_phi        );
	h_njet_m            .push_back( h_nj_m          );
	h_njet_sumPt        .push_back( h_nj_sumPt      );
	h_njet_sumM         .push_back( h_nj_sumM       );
	h_njet_ntrk         .push_back( h_nj_ntrk       );
	if ( m_histoInfoSwitch->m_njetTrks   ) {
	  h_njet_ntrk_pt    .push_back( h_nj_ntrk_pt    );
	  h_njet_ntrk_eta   .push_back( h_nj_ntrk_eta   );
	  h_njet_ntrk_phi   .push_back( h_nj_ntrk_phi   );
	  h_njet_ntrk_m     .push_back( h_nj_ntrk_m     );
	  h_njet_ntrk_sumPt .push_back( h_nj_ntrk_sumPt );
	  h_njet_ntrk_sumM  .push_back( h_nj_ntrk_sumM  );
	}
	h_njet_nsv          .push_back( h_nj_nsv        );
	if ( m_histoInfoSwitch->m_njetVerts ) {
	  h_njet_nsv_pt     .push_back( h_nj_nsv_pt     );
	  h_njet_nsv_eta    .push_back( h_nj_nsv_eta    );
	  h_njet_nsv_phi    .push_back( h_nj_nsv_phi    );
	  h_njet_nsv_m      .push_back( h_nj_nsv_m      );
	  h_njet_nsv_sumPt  .push_back( h_nj_nsv_sumPt  );
	  h_njet_nsv_sumM   .push_back( h_nj_nsv_sumM   );
	}
      }
    } // end if not truthOnly

    // leading N-jets
    // --> set NJetX histo x-min --> add others accordingly (see ABCD plots)
    float njetht_xmin = 0;
    if      ( region.type == EJsHelper::SEARCH     || region.type == EJsHelper::JZ4W_SLICE_SEARCH     ) njetht_xmin = 950;
    else if ( region.type == EJsHelper::VALIDATION || region.type == EJsHelper::JZ4W_SLICE_VALIDATION ) njetht_xmin = 200;
    // --> set validation region shift
    std::string vrsh    = "_vrsh";
    std::string vrshift = " (VR-shift)";
    h_NJetHt
      .push_back(     book( name, "NJetHt",          "leading N " + m_jetStr + " Jet H_{T} [GeV]",              100, njetht_xmin, 5000 ) );
    if ( m_histoInfoSwitch->m_vrshift )
      h_NJetHt_vrsh
	.push_back(   book( name, "NJetHt"   + vrsh, "leading N " + m_jetStr + " Jet H_{T} [GeV]"    + vrshift, 100,           0, 5000 ) );

    if ( !m_histoInfoSwitch->m_truthOnly ) {
      // leading N-jets
      h_NJetPt
      	.push_back(   book( name, "NJetPt",          "leading N " + m_jetStr + " Jet p_{T} [GeV]",              100,    0, 1000 ) );
      h_NJetEta
      	.push_back(   book( name, "NJetEta",         "leading N " + m_jetStr + " Jet eta",                      100,   -7,    7 ) );
      h_NJetPhi
      	.push_back(   book( name, "NJetPhi",         "leading N " + m_jetStr + " Jet phi",                      100, -3.5,  3.5 ) );
      h_NJetM
      	.push_back(   book( name, "NJetM",           "leading N " + m_jetStr + " Jet mass [GeV]",               100,    0, 6000 ) );
      h_NJetSumM
      	.push_back(   book( name, "NJetSumM",        "leading N " + m_jetStr + " Jet sum-mass [GeV]",           100,    0,  600 ) );
      if ( m_histoInfoSwitch->m_vrshift ) {
	h_NJetPt_vrsh
	  .push_back( book( name, "NJetPt"   + vrsh, "leading N " + m_jetStr + " Jet p_{T} [GeV]"    + vrshift, 100,    0, 1000 ) );
	h_NJetSumM_vrsh
	  .push_back( book( name, "NJetSumM" + vrsh, "leading N " + m_jetStr + " Jet sum-mass [GeV]" + vrshift, 100,    0,  600 ) );
      }
      
      // average of dijet pair with minimum invariant mass difference 
      std::string mindmstr  = m_jetStr  + " min-diff-invM dijet";
      std::string mindptstr = m_jetStr  + " min-diff-pt dijet";
      std::string maxdrstr  = m_jetStr  + " max-dR dijet";
      std::string avgstr    = m_jetStr  + " average dijet";
      std::string maxstr    = m_jetStr  + " max-invM dijet";
      std::string minstr    = m_jetStr  + " min-invM dijet";
      std::string maxptstr  = m_jetStr  + " max-pt dijet";
      std::string minptstr  = m_jetStr  + " min-pt dijet";
      h_NJetJJ_pt
	.push_back(   book( name, "NJetJJ_pt",                  "leading N " + mindmstr  + " p_{T} [GeV]",                      100,    0, 2500 ) );
      h_NJetJJ_eta
	.push_back(   book( name, "NJetJJ_eta",                 "leading N " + mindmstr  + " eta",                              100,   -5,    5 ) );
      h_NJetJJ_phi
	.push_back(   book( name, "NJetJJ_phi",                 "leading N " + mindmstr  + " phi",                              100, -3.5,  3.5 ) );
      h_NJetJJ_m
	.push_back(   book( name, "NJetJJ_m",                   "leading N " + mindmstr  + " invariant mass [GeV]",             100,    0, 2500 ) );
      h_NJetJJ_ptDiff
	.push_back(   book( name, "NJetJJ_ptDiff",              "leading N " + mindmstr  + " p_{T} difference [GeV]",           100,    0,  750 ) );
      h_NJetJJ_etaDiff
	.push_back(   book( name, "NJetJJ_etaDiff",             "leading N " + mindmstr  + " eta difference",                   100,    0,    6 ) );
      h_NJetJJ_phiDiff
	.push_back(   book( name, "NJetJJ_phiDiff",             "leading N " + mindmstr  + " phi difference",                   100,    0,    6 ) );
      h_NJetJJ_mDiff
	.push_back(   book( name, "NJetJJ_mDiff",               "leading N " + mindmstr  + " invariant mass difference [GeV]",  100,    0, 1000 ) );
      h_NJetJJ_sumPt
	.push_back(   book( name, "NJetJJ_sumPt",               "leading N " + mindmstr  + " sum-p_{T} [GeV]",                  100,    0, 2500 ) );
      h_NJetJJ_sumM
	.push_back(   book( name, "NJetJJ_sumM",                "leading N " + mindmstr  + " sum-mass [GeV]",                   100,    0,  400 ) );
      h_NJetJJ_dR
	.push_back(   book( name, "NJetJJ_dR",                  "leading N " + mindmstr  + " dR",                               100,    0,    6 ) );
      h_NJetJJ_dRjj
	.push_back(   book( name, "NJetJJ_dRjj",                "leading N " + mindmstr  + " jet-jet dR",                       100,    0,    6 ) );
      h_NJetJJmindpt_pt
	.push_back(   book( name, "NJetJJmindpt_pt",            "leading N " + mindptstr + " p_{T} [GeV]",                      100,    0, 2500 ) );
      h_NJetJJmindpt_eta
	.push_back(   book( name, "NJetJJmindpt_eta",           "leading N " + mindptstr + " eta",                              100,   -5,    5 ) );
      h_NJetJJmindpt_phi
	.push_back(   book( name, "NJetJJmindpt_phi",           "leading N " + mindptstr + " phi",                              100, -3.5,  3.5 ) );
      h_NJetJJmindpt_m
	.push_back(   book( name, "NJetJJmindpt_m",             "leading N " + mindptstr + " invariant mass [GeV]",             100,    0, 2500 ) );
      h_NJetJJmindpt_ptDiff
	.push_back(   book( name, "NJetJJmindpt_ptDiff",        "leading N " + mindptstr + " p_{T} difference [GeV]",           100,    0,  500 ) );
      h_NJetJJmindpt_etaDiff
	.push_back(   book( name, "NJetJJmindpt_etaDiff",       "leading N " + mindptstr + " eta difference",                   100,    0,    6 ) );
      h_NJetJJmindpt_phiDiff
	.push_back(   book( name, "NJetJJmindpt_phiDiff",       "leading N " + mindptstr + " phi difference",                   100,    0,    6 ) );
      h_NJetJJmindpt_mDiff
	.push_back(   book( name, "NJetJJmindpt_mDiff",         "leading N " + mindptstr + " invariant mass difference [GeV]",  100,    0, 2000 ) );
      h_NJetJJmindpt_sumPt
	.push_back(   book( name, "NJetJJmindpt_sumPt",         "leading N " + mindptstr + " sum-p_{T} [GeV]",                  100,    0, 2500 ) );
      h_NJetJJmindpt_sumM
	.push_back(   book( name, "NJetJJmindpt_sumM",          "leading N " + mindptstr + " sum-mass [GeV]",                   100,    0,  400 ) );
      h_NJetJJmindpt_dR
	.push_back(   book( name, "NJetJJmindpt_dR",            "leading N " + mindptstr + " dR",                               100,    0,    6 ) );
      h_NJetJJmindpt_dRjj
	.push_back(   book( name, "NJetJJmindpt_dRjj",          "leading N " + mindptstr + " jet-jet dR",                       100,    0,    6 ) );
      h_NJetJJmaxdr_pt
	.push_back(   book( name, "NJetJJmaxdr_pt",             "leading N " + maxdrstr  + " p_{T} [GeV]",                      100,    0, 2500 ) );
      h_NJetJJmaxdr_eta
	.push_back(   book( name, "NJetJJmaxdr_eta",            "leading N " + maxdrstr  + " eta",                              100,   -5,    5 ) );
      h_NJetJJmaxdr_phi
	.push_back(   book( name, "NJetJJmaxdr_phi",            "leading N " + maxdrstr  + " phi",                              100, -3.5,  3.5 ) );
      h_NJetJJmaxdr_m
	.push_back(   book( name, "NJetJJmaxdr_m",              "leading N " + maxdrstr  + " invariant mass [GeV]",             100,    0, 2500 ) );
      h_NJetJJmaxdr_ptDiff
	.push_back(   book( name, "NJetJJmaxdr_ptDiff",         "leading N " + maxdrstr  + " p_{T} difference [GeV]",           100,    0,  750 ) );
      h_NJetJJmaxdr_etaDiff
	.push_back(   book( name, "NJetJJmaxdr_etaDiff",        "leading N " + maxdrstr  + " eta difference",                   100,    0,    6 ) );
      h_NJetJJmaxdr_phiDiff
	.push_back(   book( name, "NJetJJmaxdr_phiDiff",        "leading N " + maxdrstr  + " phi difference",                   100,    0,    6 ) );
      h_NJetJJmaxdr_mDiff
	.push_back(   book( name, "NJetJJmaxdr_mDiff",          "leading N " + maxdrstr  + " invariant mass difference [GeV]",  100,    0, 2000 ) );
      h_NJetJJmaxdr_sumPt
	.push_back(   book( name, "NJetJJmaxdr_sumPt",          "leading N " + maxdrstr  + " sum-p_{T} [GeV]",                  100,    0, 2500 ) );
      h_NJetJJmaxdr_sumM
	.push_back(   book( name, "NJetJJmaxdr_sumM",           "leading N " + maxdrstr  + " sum-mass [GeV]",                   100,    0,  400 ) );
      h_NJetJJmaxdr_dR
	.push_back(   book( name, "NJetJJmaxdr_dR",             "leading N " + maxdrstr  + " dR",                               100,    0,    6 ) );
      h_NJetJJmaxdr_dRjj
	.push_back(   book( name, "NJetJJmaxdr_dRjj",           "leading N " + maxdrstr  + " jet-jet dR",                       100,    0,    6 ) );
      h_avgNJetJJ_pt
	.push_back(   book( name, "avgNJetJJ_pt",               "leading N " + avgstr    + " p_{T} [GeV]",                      100,    0, 1200 ) );
      h_avgNJetJJ_eta
	.push_back(   book( name, "avgNJetJJ_eta",              "leading N " + avgstr    + " eta",                              100,   -5,    5 ) );
      h_avgNJetJJ_phi
	.push_back(   book( name, "avgNJetJJ_phi",              "leading N " + avgstr    + " phi",                              100, -3.5,  3.5 ) );
      h_avgNJetJJ_m
	.push_back(   book( name, "avgNJetJJ_m",                "leading N " + avgstr    + " mass [GeV]",                       100,    0, 2000 ) );
      h_avgNJetJJ_dR
	.push_back(   book( name, "avgNJetJJ_dR",               "leading N " + avgstr    + " dR",                               100,    0,    6 ) );
      h_maxNJetJJ_pt
	.push_back(   book( name, "maxNJetJJ_pt",               "leading N " + maxstr    + " p_{T} [GeV]",                      100,    0, 1500 ) );
      h_maxNJetJJ_eta
	.push_back(   book( name, "maxNJetJJ_eta",              "leading N " + maxstr    + " eta",                              100,   -5,    5 ) );
      h_maxNJetJJ_phi
	.push_back(   book( name, "maxNJetJJ_phi",              "leading N " + maxstr    + " phi",                              100, -3.5,  3.5 ) );
      h_maxNJetJJ_m
	.push_back(   book( name, "maxNJetJJ_m",                "leading N " + maxstr    + " mass [GeV]",                       100,    0, 4000 ) );
      h_maxNJetJJ_sumPt
	.push_back(   book( name, "maxNJetJJ_sumPt",            "leading N " + maxstr    + " sum-p_{T} [GeV]",                  100,    0, 3500 ) );
      h_maxNJetJJ_sumM
	.push_back(   book( name, "maxNJetJJ_sumM",             "leading N " + maxstr    + " sum-mass [GeV]",                   100,    0,  400 ) );
      h_maxNJetJJ_dR
	.push_back(   book( name, "maxNJetJJ_dR",               "leading N " + maxstr    + " dR",                               100,    0,    6 ) );
      h_minNJetJJ_pt
	.push_back(   book( name, "minNJetJJ_pt",               "leading N " + minstr    + " p_{T} [GeV]",                      100,    0, 2000 ) );
      h_minNJetJJ_eta
	.push_back(   book( name, "minNJetJJ_eta",              "leading N " + minstr    + " eta",                              100,   -5,    5 ) );
      h_minNJetJJ_phi
	.push_back(   book( name, "minNJetJJ_phi",              "leading N " + minstr    + " phi",                              100, -3.5,  3.5 ) );
      h_minNJetJJ_m
	.push_back(   book( name, "minNJetJJ_m",                "leading N " + minstr    + " mass [GeV]",                       100,    0, 1500 ) );
      h_minNJetJJ_sumPt
	.push_back(   book( name, "minNJetJJ_sumPt",            "leading N " + minstr    + " sum-p_{T} [GeV]",                  100,    0, 2000 ) );
      h_minNJetJJ_sumM
	.push_back(   book( name, "minNJetJJ_sumM",             "leading N " + minstr    + " sum-mass [GeV]",                   100,    0,  300 ) );
      h_minNJetJJ_dR
	.push_back(   book( name, "minNJetJJ_dR",               "leading N " + minstr    + " dR",                               100,    0,    6 ) );
      h_maxptNJetJJ_pt
	.push_back(   book( name, "maxptNJetJJ_pt",             "leading N " + maxptstr  + " p_{T} [GeV]",                      100,    0, 2500 ) );
      h_maxptNJetJJ_eta
	.push_back(   book( name, "maxptNJetJJ_eta",            "leading N " + maxptstr  + " eta",                              100,   -5,    5 ) );
      h_maxptNJetJJ_phi
	.push_back(   book( name, "maxptNJetJJ_phi",            "leading N " + maxptstr  + " phi",                              100, -3.5,  3.5 ) );
      h_maxptNJetJJ_m
	.push_back(   book( name, "maxptNJetJJ_m",              "leading N " + maxptstr  + " mass [GeV]",                       100,    0, 3000 ) );
      h_maxptNJetJJ_sumPt
	.push_back(   book( name, "maxptNJetJJ_sumPt",          "leading N " + maxptstr  + " sum-p_{T} [GeV]",                  100,    0, 3000 ) );
      h_maxptNJetJJ_sumM
	.push_back(   book( name, "maxptNJetJJ_sumM",           "leading N " + maxptstr  + " sum-mass [GeV]",                   100,    0,  400 ) );
      h_maxptNJetJJ_dR
	.push_back(   book( name, "maxptNJetJJ_dR",             "leading N " + maxptstr  + " dR",                               100,    0,    6 ) );
      h_minptNJetJJ_pt
	.push_back(   book( name, "minptNJetJJ_pt",             "leading N " + minptstr  + " p_{T} [GeV]",                      100,    0, 1250 ) );
      h_minptNJetJJ_eta
	.push_back(   book( name, "minptNJetJJ_eta",            "leading N " + minptstr  + " eta",                              100,   -5,    5 ) );
      h_minptNJetJJ_phi
	.push_back(   book( name, "minptNJetJJ_phi",            "leading N " + minptstr  + " phi",                              100, -3.5,  3.5 ) );
      h_minptNJetJJ_m
	.push_back(   book( name, "minptNJetJJ_m",              "leading N " + minptstr  + " mass [GeV]",                       100,    0, 3000 ) );
      h_minptNJetJJ_sumPt
	.push_back(   book( name, "minptNJetJJ_sumPt",          "leading N " + minptstr  + " sum-p_{T} [GeV]",                  100,    0, 3000 ) );
      h_minptNJetJJ_sumM
	.push_back(   book( name, "minptNJetJJ_sumM",           "leading N " + minptstr  + " sum-mass [GeV]",                   100,    0,  400 ) );
      h_minptNJetJJ_dR
	.push_back(   book( name, "minptNJetJJ_dR",             "leading N " + minptstr  + " dR",                               100,    0,    6 ) );
      if ( m_histoInfoSwitch->m_vrshift ) {
	h_NJetJJ_pt_vrsh
	  .push_back( book( name, "NJetJJ_pt"           + vrsh, "leading N " + mindmstr  + " p_{T} [GeV]"          + vrshift,   100,    0, 2500 ) );
	h_NJetJJ_m_vrsh
	  .push_back( book( name, "NJetJJ_m"            + vrsh, "leading N " + mindmstr  + " invariant mass [GeV]" + vrshift,   100,    0, 2500 ) );
	h_NJetJJmindpt_pt_vrsh
	  .push_back( book( name, "NJetJJmindpt_pt"     + vrsh, "leading N " + mindptstr + " p_{T} [GeV]"          + vrshift,   100,    0, 2500 ) );
	h_NJetJJmindpt_m_vrsh
	  .push_back( book( name, "NJetJJmindpt_m"      + vrsh, "leading N " + mindptstr + " invariant mass [GeV]" + vrshift,   100,    0, 2500 ) );
	h_NJetJJmaxdr_pt_vrsh
	  .push_back( book( name, "NJetJJmaxdr_pt"      + vrsh, "leading N " + maxdrstr  + " p_{T} [GeV]"          + vrshift,   100,    0, 2500 ) );
	h_NJetJJmaxdr_m_vrsh
	  .push_back( book( name, "NJetJJmaxdr_m"       + vrsh, "leading N " + maxdrstr  + " invariant mass [GeV]" + vrshift,   100,    0, 2500 ) );
	h_avgNJetJJ_pt_vrsh
	  .push_back( book( name, "avgNJetJJ_pt"        + vrsh, "leading N " + avgstr    + " p_{T} [GeV]"          + vrshift,   100,    0, 1200 ) );
	h_avgNJetJJ_m_vrsh
	  .push_back( book( name, "avgNJetJJ_m"         + vrsh, "leading N " + avgstr    + " mass [GeV]"           + vrshift,   100,    0, 2000 ) );
	h_maxNJetJJ_pt_vrsh
	  .push_back( book( name, "maxNJetJJ_pt"        + vrsh, "leading N " + maxstr    + " p_{T} [GeV]"          + vrshift,   100,    0, 1500 ) );
	h_maxNJetJJ_m_vrsh
	  .push_back( book( name, "maxNJetJJ_m"         + vrsh, "leading N " + maxstr    + " mass [GeV]"           + vrshift,   100,    0, 4000 ) );
	h_maxNJetJJ_sumPt_vrsh
	  .push_back( book( name, "maxNJetJJ_sumPt"     + vrsh, "leading N " + maxstr    + " sum-p_{T} [GeV]"      + vrshift,   100,    0, 3500 ) );
	h_maxNJetJJ_sumM_vrsh
	  .push_back( book( name, "maxNJetJJ_sumM"      + vrsh, "leading N " + maxstr    + " sum-mass [GeV]"       + vrshift,   100,    0,  400 ) );
	h_minNJetJJ_pt_vrsh
	  .push_back( book( name, "minNJetJJ_pt"        + vrsh, "leading N " + minstr    + " p_{T} [GeV]"          + vrshift,   100,    0, 2000 ) );
	h_minNJetJJ_m_vrsh
	  .push_back( book( name, "minNJetJJ_m"         + vrsh, "leading N " + minstr    + " mass [GeV]"           + vrshift,   100,    0, 1500 ) );
	h_minNJetJJ_sumPt_vrsh
	  .push_back( book( name, "minNJetJJ_sumPt"     + vrsh, "leading N " + minstr    + " sum-p_{T} [GeV]"      + vrshift,   100,    0, 2000 ) );
	h_minNJetJJ_sumM_vrsh
	  .push_back( book( name, "minNJetJJ_sumM"      + vrsh, "leading N " + minstr    + " sum-mass [GeV]"       + vrshift,   100,    0,  300 ) );
	h_maxptNJetJJ_pt_vrsh
	  .push_back( book( name, "maxptNJetJJ_pt"      + vrsh, "leading N " + maxptstr  + " p_{T} [GeV]"          + vrshift,   100,    0, 2500 ) );
	h_maxptNJetJJ_m_vrsh
	  .push_back( book( name, "maxptNJetJJ_m"       + vrsh, "leading N " + maxptstr  + " mass [GeV]"           + vrshift,   100,    0, 3000 ) );
	h_maxptNJetJJ_sumPt_vrsh
	  .push_back( book( name, "maxptNJetJJ_sumPt"   + vrsh, "leading N " + maxptstr  + " sum-p_{T} [GeV]"      + vrshift,   100,    0, 3000 ) );
	h_maxptNJetJJ_sumM_vrsh
	  .push_back( book( name, "maxptNJetJJ_sumM"    + vrsh, "leading N " + maxptstr  + " sum-mass [GeV]"       + vrshift,   100,    0,  400 ) );
	h_minptNJetJJ_pt_vrsh
	  .push_back( book( name, "minptNJetJJ_pt"      + vrsh, "leading N " + minptstr  + " p_{T} [GeV]"          + vrshift,   100,    0, 1250 ) );
	h_minptNJetJJ_m_vrsh
	  .push_back( book( name, "minptNJetJJ_m"       + vrsh, "leading N " + minptstr  + " mass [GeV]"           + vrshift,   100,    0, 3000 ) );
	h_minptNJetJJ_sumPt_vrsh
	  .push_back( book( name, "minptNJetJJ_sumPt"   + vrsh, "leading N " + minptstr  + " sum-p_{T} [GeV]"      + vrshift,   100,    0, 3000 ) );
	h_minptNJetJJ_sumM_vrsh
	  .push_back( book( name, "minptNJetJJ_sumM"    + vrsh, "leading N " + minptstr  + " sum-mass [GeV]"       + vrshift,   100,    0,  400 ) );
      }
    } // end if not truthOnly


    // --- TRUTH PARTICLES --- //
    // truth particles: basics / kinematics
    if ( m_mc ) {
      std::vector<int>   ntp    = {       5,       5,     150,      75 };
      std::vector<float> tppt   = {    2500,    1500,     500,    1000 };
      std::vector<float> tpm    = {    2500,      60,      30,     120 };
      std::vector<float> tpbg   = {       5,     200,     100,      50 };
      std::vector<int>   ptp_n  = {       5,       5,     225,     225 };
      std::vector<int>   ptp_l  = { 4900000, 4900100, 4900000, 4900000 };
      std::vector<int>   ptp_h  = { 4900005, 4900105, 4900225, 4900225 };
      std::vector<int>   ntpch  = {       5,     100,      15,      15 };
      std::vector<int>   ptch_n = {     105,     125,     100,     100 };
      std::vector<int>   ptch_l = {       0, 4900100,       0,       0 };
      std::vector<int>   ptch_h = { 4900105, 4900225,    3500, 4900225 };
      std::vector<TH1F*> h_tpart_n;
      std::vector<TH1F*> h_tpart_pt;
      std::vector<TH1F*> h_tpart_eta;
      std::vector<TH1F*> h_tpart_phi;
      std::vector<TH1F*> h_tpart_E;
      std::vector<TH1F*> h_tpart_M;
      std::vector<TH1F*> h_tpart_betagamma;
      std::vector<TH1F*> h_tpart_charge;
      std::vector<TH1F*> h_tpart_nParents;
      std::vector<TH1F*> h_tpart_parentPdgId;
      std::vector<TH1F*> h_tpart_nChildren;
      std::vector<TH1F*> h_tpart_childPdgId;
      for ( size_t i = 0; i != hTP.size(); ++i ) {
	std::string htp    = hTP    [i];
	std::string htpstr = hTPstr [i];
	h_tpart_n           .push_back( book( name, htp + "_n",           "n " + htpstr + "s",           ntp[i],         0,    ntp[i] ) );
	if ( m_histoInfoSwitch->m_abcdcutOnly ) continue;
	h_tpart_pt          .push_back( book( name, htp + "_pt",          htpstr + " p_{T} [GeV]",          100,         0,   tppt[i] ) );
	h_tpart_eta         .push_back( book( name, htp + "_eta",         htpstr + " eta",                  100,        -5,         5 ) );
	h_tpart_phi         .push_back( book( name, htp + "_phi",         htpstr + " phi",                  100,      -3.5,       3.5 ) );
	h_tpart_E           .push_back( book( name, htp + "_E",           htpstr + " energy [GeV]",         100,         0, 2*tppt[i] ) );
	h_tpart_M           .push_back( book( name, htp + "_M",           htpstr + " mass [GeV]",           100,         0,    tpm[i] ) );
	h_tpart_betagamma   .push_back( book( name, htp + "_betagamma",   htpstr + " #beta #gamma",         100,         0,   tpbg[i] ) );
	h_tpart_charge      .push_back( book( name, htp + "_charge",      htpstr + " charge",               100,        -2,         2 ) );
	h_tpart_nParents    .push_back( book( name, htp + "_nParents",    "n " + htpstr + " parents",        10,         0,        10 ) );
	h_tpart_parentPdgId .push_back( book( name, htp + "_parentPdgId", htpstr + " parent pdgId",    ptp_n[i],  ptp_l[i],  ptp_h[i] ) );
	h_tpart_nChildren   .push_back( book( name, htp + "_nChildren",   "n " + htpstr + " children", ntpch[i],         0,  ntpch[i] ) );
	h_tpart_childPdgId  .push_back( book( name, htp + "_childPdgId",  htpstr + " child pdgId",    ptch_n[i], ptch_l[i], ptch_h[i] ) );
      } // end loop over truth particle types
      h_tp_n           .push_back( h_tpart_n           );
      if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
	h_tp_pt          .push_back( h_tpart_pt          );
	h_tp_eta         .push_back( h_tpart_eta         );
	h_tp_phi         .push_back( h_tpart_phi         );
	h_tp_E           .push_back( h_tpart_E           );
	h_tp_M           .push_back( h_tpart_M           );
	h_tp_betagamma   .push_back( h_tpart_betagamma   );
	h_tp_charge      .push_back( h_tpart_charge      );
	h_tp_nParents    .push_back( h_tpart_nParents    );
	h_tp_parentPdgId .push_back( h_tpart_parentPdgId );
	h_tp_nChildren   .push_back( h_tpart_nChildren   );
	h_tp_childPdgId  .push_back( h_tpart_childPdgId  );
	if ( m_histoInfoSwitch->m_llpRecoEff || m_histoInfoSwitch->m_llptrkRecoEff ) {
	  std::vector<TH1F*> h_llptrk_x;
	  std::vector<TH1F*> h_llptrk_y;
	  std::vector<TH1F*> h_llptrk_z;
	  std::vector<TH1F*> h_llptrk_r;
	  std::vector<TH1F*> h_llptrk_pt;
	  std::vector<TH1F*> h_llptrk_eta;
	  std::vector<TH1F*> h_llptrk_phi;
	  std::vector<TH1F*> h_llptrk_d0;
	  std::vector<TH1F*> h_llptrk_z0;
	  std::vector<TH1F*> h_llptrk_avgMu;
	  std::vector<TH1F*> h_llptrk_minDR;
	  std::vector<TH1F*> h_rllptrk_x;
	  std::vector<TH1F*> h_rllptrk_y;
	  std::vector<TH1F*> h_rllptrk_z;
	  std::vector<TH1F*> h_rllptrk_r;
	  std::vector<TH1F*> h_rllptrk_pt;
	  std::vector<TH1F*> h_rllptrk_eta;
	  std::vector<TH1F*> h_rllptrk_phi;
	  std::vector<TH1F*> h_rllptrk_d0;
	  std::vector<TH1F*> h_rllptrk_z0;
	  std::vector<TH1F*> h_rllptrk_avgMu;
	  std::vector<TH1F*> h_rllptrk_minDR;
	  std::vector<TH1F*> h_rllptrk_resid_d0;
	  std::vector<TH1F*> h_rllptrk_resid_z0;
	  std::vector<TH1F*> h_rllptrk_resid_qOverP;
	  std::vector<TH2F*> h_rllptrk_resid_d0_r;
	  std::vector<TH2F*> h_rllptrk_resid_d0_pt;
	  std::vector<TH2F*> h_rllptrk_resid_z0_r;
	  std::vector<TH2F*> h_rllptrk_resid_z0_pt;
	  std::vector<TH2F*> h_rllptrk_resid_qOverP_r;
	  std::vector<TH2F*> h_rllptrk_resid_qOverP_pt;
	  std::vector<TH1F*> h_sllptrk_x;
	  std::vector<TH1F*> h_sllptrk_y;
	  std::vector<TH1F*> h_sllptrk_z;
	  std::vector<TH1F*> h_sllptrk_r;
	  std::vector<TH1F*> h_sllptrk_pt;
	  std::vector<TH1F*> h_sllptrk_eta;
	  std::vector<TH1F*> h_sllptrk_phi;
	  std::vector<TH1F*> h_sllptrk_d0;
	  std::vector<TH1F*> h_sllptrk_z0;
	  std::vector<TH1F*> h_sllptrk_avgMu;
	  std::vector<TH1F*> h_sllptrk_minDR;
	  std::vector<TH1F*> h_sllptrk_resid_d0;
	  std::vector<TH1F*> h_sllptrk_resid_z0;
	  std::vector<TH1F*> h_sllptrk_resid_qOverP;
	  std::vector<TH2F*> h_sllptrk_resid_d0_r;
	  std::vector<TH2F*> h_sllptrk_resid_d0_pt;
	  std::vector<TH2F*> h_sllptrk_resid_z0_r;
	  std::vector<TH2F*> h_sllptrk_resid_z0_pt;
	  std::vector<TH2F*> h_sllptrk_resid_qOverP_r;
	  std::vector<TH2F*> h_sllptrk_resid_qOverP_pt;
	  std::vector<TH1F*> h_lllptrk_x;
	  std::vector<TH1F*> h_lllptrk_y;
	  std::vector<TH1F*> h_lllptrk_z;
	  std::vector<TH1F*> h_lllptrk_r;
	  std::vector<TH1F*> h_lllptrk_pt;
	  std::vector<TH1F*> h_lllptrk_eta;
	  std::vector<TH1F*> h_lllptrk_phi;
	  std::vector<TH1F*> h_lllptrk_d0;
	  std::vector<TH1F*> h_lllptrk_z0;
	  std::vector<TH1F*> h_lllptrk_avgMu;
	  std::vector<TH1F*> h_lllptrk_minDR;
	  std::vector<TH1F*> h_lllptrk_resid_d0;
	  std::vector<TH1F*> h_lllptrk_resid_z0;
	  std::vector<TH1F*> h_lllptrk_resid_qOverP;
	  std::vector<TH2F*> h_lllptrk_resid_d0_r;
	  std::vector<TH2F*> h_lllptrk_resid_d0_pt;
	  std::vector<TH2F*> h_lllptrk_resid_z0_r;
	  std::vector<TH2F*> h_lllptrk_resid_z0_pt;
	  std::vector<TH2F*> h_lllptrk_resid_qOverP_r;
	  std::vector<TH2F*> h_lllptrk_resid_qOverP_pt;
	  std::vector<TH1F*> h_llptrk_reff_x;
	  std::vector<TH1F*> h_llptrk_reff_y;
	  std::vector<TH1F*> h_llptrk_reff_z;
	  std::vector<TH1F*> h_llptrk_reff_r;
	  std::vector<TH1F*> h_llptrk_reff_pt;
	  std::vector<TH1F*> h_llptrk_reff_eta;
	  std::vector<TH1F*> h_llptrk_reff_phi;
	  std::vector<TH1F*> h_llptrk_reff_d0;
	  std::vector<TH1F*> h_llptrk_reff_z0;
	  std::vector<TH1F*> h_llptrk_reff_avgMu;
	  std::vector<TH1F*> h_llptrk_reff_minDR;
	  std::vector<TH1F*> h_llptrk_seff_x;
	  std::vector<TH1F*> h_llptrk_seff_y;
	  std::vector<TH1F*> h_llptrk_seff_z;
	  std::vector<TH1F*> h_llptrk_seff_r;
	  std::vector<TH1F*> h_llptrk_seff_pt;
	  std::vector<TH1F*> h_llptrk_seff_eta;
	  std::vector<TH1F*> h_llptrk_seff_phi;
	  std::vector<TH1F*> h_llptrk_seff_d0;
	  std::vector<TH1F*> h_llptrk_seff_z0;
	  std::vector<TH1F*> h_llptrk_seff_avgMu;
	  std::vector<TH1F*> h_llptrk_seff_minDR;
	  std::vector<TH1F*> h_llptrk_leff_x;
	  std::vector<TH1F*> h_llptrk_leff_y;
	  std::vector<TH1F*> h_llptrk_leff_z;
	  std::vector<TH1F*> h_llptrk_leff_r;
	  std::vector<TH1F*> h_llptrk_leff_pt;
	  std::vector<TH1F*> h_llptrk_leff_eta;
	  std::vector<TH1F*> h_llptrk_leff_phi;
	  std::vector<TH1F*> h_llptrk_leff_d0;
	  std::vector<TH1F*> h_llptrk_leff_z0;
	  std::vector<TH1F*> h_llptrk_leff_avgMu;
	  std::vector<TH1F*> h_llptrk_leff_minDR;
	  // loop over descendant types
	  for ( size_t i = 0; i != hLLP.size(); ++i ) {
	    std::string hllpstr = hLLPstr[i]; hllpstr.pop_back();
	    std::string htp     = hLLP[i] + "Trk"; htp[0] = tolower(htp[0]);
	    std::string htpstr  = hllpstr + " truth track";
	    std::string hrtp    = "reco"  + hLLP[i] + "Trk";
	    std::string hrtpstr = "reconstructed "              + htpstr;
	    std::string hstp    = "std"   + hLLP[i] + "Trk";
	    std::string hstpstr = "standard reconstructed "     + htpstr;
	    std::string hltp    = "lrt"   + hLLP[i] + "Trk";
	    std::string hltpstr = "large-radius reconstructed " + htpstr;
	    h_llptrk_x          .push_back( book( name, htp  + "_x",             htpstr  + " production x-pos [mm]", 100,  -450,  450 ) );
	    h_llptrk_y          .push_back( book( name, htp  + "_y",             htpstr  + " production y-pos [mm]", 100,  -450,  450 ) );
	    h_llptrk_z          .push_back( book( name, htp  + "_z",             htpstr  + " production z-pos [mm]", 100, -2000, 2000 ) );
	    h_llptrk_r          .push_back( book( name, htp  + "_r",             htpstr  + " production r-pos [mm]", 100,     0,  450 ) );
	    h_llptrk_pt         .push_back( book( name, htp  + "_pt",            htpstr  + " p_{T} [GeV]",           100,     0,  300 ) );
	    h_llptrk_eta        .push_back( book( name, htp  + "_eta",           htpstr  + " eta",                   100,    -3,    3 ) );
	    h_llptrk_phi        .push_back( book( name, htp  + "_phi",           htpstr  + " phi",                   100,  -3.5,  3.5 ) );
	    h_llptrk_d0         .push_back( book( name, htp  + "_d0",            htpstr  + " d0 [mm]",               100,  -300,  300 ) );
	    h_llptrk_z0         .push_back( book( name, htp  + "_z0",            htpstr  + " z0 [mm]",               100, -1500, 1500 ) );
	    h_llptrk_avgMu      .push_back( book( name, htp  + "_avgMu",         htpstr  + " average pp interactions",90,     0,   90 ) );
	    h_llptrk_minDR      .push_back( book( name, htp  + "_minDR",         htpstr  + " nearest truth track dR",100,     0,  1.0 ) );
	    h_rllptrk_x         .push_back( book( name, hrtp + "_x",             hrtpstr + " production x-pos [mm]", 100,  -450,  450 ) );
	    h_rllptrk_y         .push_back( book( name, hrtp + "_y",             hrtpstr + " production y-pos [mm]", 100,  -450,  450 ) );
	    h_rllptrk_z         .push_back( book( name, hrtp + "_z",             hrtpstr + " production z-pos [mm]", 100, -2000, 2000 ) );
	    h_rllptrk_r         .push_back( book( name, hrtp + "_r",             hrtpstr + " production r-pos [mm]", 100,     0,  450 ) );
	    h_rllptrk_pt        .push_back( book( name, hrtp + "_pt",            hrtpstr + " p_{T} [GeV]",           100,     0,  300 ) ); // 100
	    h_rllptrk_eta       .push_back( book( name, hrtp + "_eta",           hrtpstr + " eta",                   100,    -3,    3 ) );
	    h_rllptrk_phi       .push_back( book( name, hrtp + "_phi",           hrtpstr + " phi",                   100,  -3.5,  3.5 ) );
	    h_rllptrk_d0        .push_back( book( name, hrtp + "_d0",            hrtpstr + " d0 [mm]",               100,  -300,  300 ) );
	    h_rllptrk_z0        .push_back( book( name, hrtp + "_z0",            hrtpstr + " z0 [mm]",               100, -1500, 1500 ) );
	    h_rllptrk_avgMu     .push_back( book( name, hrtp + "_avgMu",         hrtpstr + " average pp interactions",90,     0,   90 ) );
	    h_rllptrk_minDR     .push_back( book( name, hrtp + "_minDR",         hrtpstr + " nearest truth track dR",100,     0,  1.0 ) );
	    h_rllptrk_resid_d0
	      .push_back( book( name, hrtp + "_resid_d0",         hrtpstr + " residual d0 [mm]",      100,  -30,   30 ) ); // 10
	    h_rllptrk_resid_z0
	      .push_back( book( name, hrtp + "_resid_z0",         hrtpstr + " residual z0 [mm]",      100, -100,  100 ) ); // 10
	    h_rllptrk_resid_qOverP
	      .push_back( book( name, hrtp + "_resid_qOverP",     hrtpstr + " residual q/p [e/GeV]",  100, -0.5,  0.5 ) ); // 1
	    h_rllptrk_resid_d0_r
	      .push_back( book( name, hrtp + "_resid_d0_r",       hrtpstr + " production r-pos [mm]", 100,    0,  450,
				hrtpstr + " residual d0 [mm]",     100,  -30,  30 ) );
	    h_rllptrk_resid_d0_pt
	      .push_back( book( name, hrtp + "_resid_d0_pt",      hrtpstr + " p_{T} [GeV]",           100,    0,  300,
				hrtpstr + " residual d0 [mm]",     100,  -30,  30 ) );
	    h_rllptrk_resid_z0_r
	      .push_back( book( name, hrtp + "_resid_z0_r",       hrtpstr + " production r-pos [mm]", 100,    0,  450,
				hrtpstr + " residual z0 [mm]",     100, -100, 100 ) );
	    h_rllptrk_resid_z0_pt
	      .push_back( book( name, hrtp + "_resid_z0_pt",      hrtpstr + " p_{T} [GeV]",           100,    0,  300,
				hrtpstr + " residual z0 [mm]",     100, -100, 100 ) );
	    h_rllptrk_resid_qOverP_r
	      .push_back( book( name, hrtp + "_resid_qOverP_r",   hrtpstr + " production r-pos [mm]", 100,    0,  450,
				hrtpstr + " residual q/p [e/GeV]", 100, -0.5, 0.5 ) );
	    h_rllptrk_resid_qOverP_pt
	      .push_back( book( name, hrtp + "_resid_qOverP_pt",  hrtpstr + " p_{T} [GeV]",           100,    0,  300,
				hrtpstr + " residual q/p [e/GeV]", 100, -0.5, 0.5 ) );
	    h_sllptrk_x         .push_back( book( name, hstp + "_x",             hstpstr + " production x-pos [mm]", 100,  -450,  450 ) );
	    h_sllptrk_y         .push_back( book( name, hstp + "_y",             hstpstr + " production y-pos [mm]", 100,  -450,  450 ) );
	    h_sllptrk_z         .push_back( book( name, hstp + "_z",             hstpstr + " production z-pos [mm]", 100, -2000, 2000 ) );
	    h_sllptrk_r         .push_back( book( name, hstp + "_r",             hstpstr + " production r-pos [mm]", 100,     0,  450 ) );
	    h_sllptrk_pt        .push_back( book( name, hstp + "_pt",            hstpstr + " p_{T} [GeV]",           100,     0,  300 ) );
	    h_sllptrk_eta       .push_back( book( name, hstp + "_eta",           hstpstr + " eta",                   100,    -3,    3 ) );
	    h_sllptrk_phi       .push_back( book( name, hstp + "_phi",           hstpstr + " phi",                   100,  -3.5,  3.5 ) );
	    h_sllptrk_d0        .push_back( book( name, hstp + "_d0",            hstpstr + " d0 [mm]",               100,  -300,  300 ) );
	    h_sllptrk_z0        .push_back( book( name, hstp + "_z0",            hstpstr + " z0 [mm]",               100, -1500, 1500 ) );
	    h_sllptrk_avgMu     .push_back( book( name, hstp + "_avgMu",         hstpstr + " average pp interactions",90,     0,   90 ) );
	    h_sllptrk_minDR     .push_back( book( name, hstp + "_minDR",         hstpstr + " nearest truth track dR",100,     0,  1.0 ) );
	    h_sllptrk_resid_d0
	      .push_back( book( name, hstp + "_resid_d0",         hstpstr + " residual d0 [mm]",      100,  -30,  30 ) );
	    h_sllptrk_resid_z0
	      .push_back( book( name, hstp + "_resid_z0",         hstpstr + " residual z0 [mm]",      100, -100, 100 ) );
	    h_sllptrk_resid_qOverP
	      .push_back( book( name, hstp + "_resid_qOverP",     hstpstr + " residual q/p [e/GeV]",  100, -0.5, 0.5 ) );
	    h_sllptrk_resid_d0_r
	      .push_back( book( name, hstp + "_resid_d0_r",       hstpstr + " production r-pos [mm]", 100,    0, 450,
				hstpstr + " residual d0 [mm]",     100,  -30,  30 ) );
	    h_sllptrk_resid_d0_pt
	      .push_back( book( name, hstp + "_resid_d0_pt",       hstpstr + " p_{T} [GeV]",          100,    0, 300,
				hstpstr + " residual d0 [mm]",     100,  -30,  30 ) );
	    h_sllptrk_resid_z0_r
	      .push_back( book( name, hstp + "_resid_z0_r",       hstpstr + " production r-pos [mm]", 100,    0, 450,
				hstpstr + " residual z0 [mm]",     100, -100, 100 ) );
	    h_sllptrk_resid_z0_pt
	      .push_back( book( name, hstp + "_resid_z0_pt",      hstpstr + " p_{T} [GeV]",           100,    0, 300,
				hstpstr + " residual z0 [mm]",     100, -100, 100 ) );
	    h_sllptrk_resid_qOverP_r
	      .push_back( book( name, hstp + "_resid_qOverP_r",   hstpstr + " production r-pos [mm]", 100,    0, 450,
				hstpstr + " residual q/p [e/GeV]", 100, -0.5, 0.5 ) );
	    h_sllptrk_resid_qOverP_pt
	      .push_back( book( name, hstp + "_resid_qOverP_pt",  hstpstr + " p_{T} [GeV]",           100,    0, 300,
				hstpstr + " residual q/p [e/GeV]", 100, -0.5, 0.5 ) );
	    h_lllptrk_x         .push_back( book( name, hltp + "_x",             hltpstr + " production x-pos [mm]", 100,  -450,  450 ) );
	    h_lllptrk_y         .push_back( book( name, hltp + "_y",             hltpstr + " production y-pos [mm]", 100,  -450,  450 ) );
	    h_lllptrk_z         .push_back( book( name, hltp + "_z",             hltpstr + " production z-pos [mm]", 100, -2000, 2000 ) );
	    h_lllptrk_r         .push_back( book( name, hltp + "_r",             hltpstr + " production r-pos [mm]", 100,     0,  450 ) );
	    h_lllptrk_pt        .push_back( book( name, hltp + "_pt",            hltpstr + " p_{T} [GeV]",           100,     0,  300 ) );
	    h_lllptrk_eta       .push_back( book( name, hltp + "_eta",           hltpstr + " eta",                   100,    -3,    3 ) );
	    h_lllptrk_phi       .push_back( book( name, hltp + "_phi",           hltpstr + " phi",                   100,  -3.5,  3.5 ) );
	    h_lllptrk_d0        .push_back( book( name, hltp + "_d0",            hltpstr + " d0 [mm]",               100,  -300,  300 ) );
	    h_lllptrk_z0        .push_back( book( name, hltp + "_z0",            hltpstr + " z0 [mm]",               100, -1500, 1500 ) );
	    h_lllptrk_avgMu     .push_back( book( name, hltp + "_avgMu",         hltpstr + " average pp interactions",90,     0,   90 ) );
	    h_lllptrk_minDR     .push_back( book( name, hltp  + "_minDR",        hltpstr + " nearest truth track dR",100,     0,  1.0 ) );
	    h_lllptrk_resid_d0
	      .push_back( book( name, hltp + "_resid_d0",         hltpstr + " residual d0 [mm]",      100,  -30,  30 ) );
	    h_lllptrk_resid_z0
	      .push_back( book( name, hltp + "_resid_z0",         hltpstr + " residual z0 [mm]",      100, -100, 100 ) );
	    h_lllptrk_resid_qOverP
	      .push_back( book( name, hltp + "_resid_qOverP",     hltpstr + " residual q/p [e/GeV]",  100, -0.5, 0.5 ) );
	    h_lllptrk_resid_d0_r
	      .push_back( book( name, hltp + "_resid_d0_r",       hltpstr + " production r-pos [mm]", 100,    0, 450,
				hltpstr + " residual d0 [mm]",     100,  -30,  30 ) );
	    h_lllptrk_resid_d0_pt
	      .push_back( book( name, hltp + "_resid_d0_pt",      hltpstr + " p_{T} [GeV]",           100,    0, 300,
				hltpstr + " residual d0 [mm]",     100,  -30,  30 ) );
	    h_lllptrk_resid_z0_r
	      .push_back( book( name, hltp + "_resid_z0_r",       hltpstr + " production r-pos [mm]", 100,    0, 450,
				hltpstr + " residual z0 [mm]",     100, -100, 100 ) );
	    h_lllptrk_resid_z0_pt
	      .push_back( book( name, hltp + "_resid_z0_pt",      hltpstr + " p_{T} [GeV]",           100,    0, 300,
				hltpstr + " residual z0 [mm]",     100, -100, 100 ) );
	    h_lllptrk_resid_qOverP_r
	      .push_back( book( name, hltp + "_resid_qOverP_r",   hltpstr + " production r-pos [mm]", 100,    0, 450,
				hltpstr + " residual q/p [e/GeV]", 100, -0.5, 0.5 ) );
	    h_lllptrk_resid_qOverP_pt
	      .push_back( book( name, hltp + "_resid_qOverP_pt",  hltpstr + " p_{T} [GeV]",           100,    0, 300,
				hltpstr + " residual q/p [e/GeV]", 100, -0.5, 0.5 ) );
	    h_llptrk_reff_x     .push_back( book( name, htp  + "_recoEff_x",     htpstr  + " production x-pos [mm]", 100,  -450,  450 ) );
	    h_llptrk_reff_y     .push_back( book( name, htp  + "_recoEff_y",     htpstr  + " production y-pos [mm]", 100,  -450,  450 ) );
	    h_llptrk_reff_z     .push_back( book( name, htp  + "_recoEff_z",     htpstr  + " production z-pos [mm]", 100, -2000, 2000 ) );
	    h_llptrk_reff_r     .push_back( book( name, htp  + "_recoEff_r",     htpstr  + " production r-pos [mm]", 100,     0,  450 ) );
	    h_llptrk_reff_pt    .push_back( book( name, htp  + "_recoEff_pt",    htpstr  + " p_{T} [GeV]",           100,     0,  300 ) );
	    h_llptrk_reff_eta   .push_back( book( name, htp  + "_recoEff_eta",   htpstr  + " eta",                   100,    -3,    3 ) );
	    h_llptrk_reff_phi   .push_back( book( name, htp  + "_recoEff_phi",   htpstr  + " phi",                   100,  -3.5,  3.5 ) );
	    h_llptrk_reff_d0    .push_back( book( name, htp  + "_recoEff_d0",    htpstr  + " d0 [mm]",               100,  -300,  300 ) );
	    h_llptrk_reff_z0    .push_back( book( name, htp  + "_recoEff_z0",    htpstr  + " z0 [mm]",               100, -1500, 1500 ) );
	    h_llptrk_reff_avgMu .push_back( book( name, htp  + "_recoEff_avgMu", htpstr  + " average pp interactions",90,     0,   90 ) );
	    h_llptrk_reff_minDR .push_back( book( name, htp  + "_recoEff_minDR", htpstr  + " nearest truth track dR",100,     0,  1.0 ) );
	    h_llptrk_seff_x     .push_back( book( name, htp  + "_stdEff_x",      htpstr  + " production x-pos [mm]", 100,  -450,  450 ) );
	    h_llptrk_seff_y     .push_back( book( name, htp  + "_stdEff_y",      htpstr  + " production y-pos [mm]", 100,  -450,  450 ) );
	    h_llptrk_seff_z     .push_back( book( name, htp  + "_stdEff_z",      htpstr  + " production z-pos [mm]", 100, -2000, 2000 ) );
	    h_llptrk_seff_r     .push_back( book( name, htp  + "_stdEff_r",      htpstr  + " production r-pos [mm]", 100,     0,  450 ) );
	    h_llptrk_seff_pt    .push_back( book( name, htp  + "_stdEff_pt",     htpstr  + " p_{T} [GeV]",           100,     0,  300 ) );
	    h_llptrk_seff_eta   .push_back( book( name, htp  + "_stdEff_eta",    htpstr  + " eta",                   100,    -3,    3 ) );
	    h_llptrk_seff_phi   .push_back( book( name, htp  + "_stdEff_phi",    htpstr  + " phi",                   100,  -3.5,  3.5 ) );
	    h_llptrk_seff_d0    .push_back( book( name, htp  + "_stdEff_d0",     htpstr  + " d0 [mm]",               100,  -300,  300 ) );
	    h_llptrk_seff_z0    .push_back( book( name, htp  + "_stdEff_z0",     htpstr  + " z0 [mm]",               100, -1500, 1500 ) );
	    h_llptrk_seff_avgMu .push_back( book( name, htp  + "_stdEff_avgMu",  htpstr  + " average pp interactions",90,     0,   90 ) );
	    h_llptrk_seff_minDR .push_back( book( name, htp  + "_stdEff_minDR",  htpstr  + " nearest truth track dR",100,     0,  1.0 ) );
	    h_llptrk_leff_x     .push_back( book( name, htp  + "_lrtEff_x",      htpstr  + " production x-pos [mm]", 100,  -450,  450 ) );
	    h_llptrk_leff_y     .push_back( book( name, htp  + "_lrtEff_y",      htpstr  + " production y-pos [mm]", 100,  -450,  450 ) );
	    h_llptrk_leff_z     .push_back( book( name, htp  + "_lrtEff_z",      htpstr  + " production z-pos [mm]", 100, -2000, 2000 ) );
	    h_llptrk_leff_r     .push_back( book( name, htp  + "_lrtEff_r",      htpstr  + " production r-pos [mm]", 100,     0,  450 ) );
	    h_llptrk_leff_pt    .push_back( book( name, htp  + "_lrtEff_pt",     htpstr  + " p_{T} [GeV]",           100,     0,  300 ) );
	    h_llptrk_leff_eta   .push_back( book( name, htp  + "_lrtEff_eta",    htpstr  + " eta",                   100,    -3,    3 ) );
	    h_llptrk_leff_phi   .push_back( book( name, htp  + "_lrtEff_phi",    htpstr  + " phi",                   100,  -3.5,  3.5 ) );
	    h_llptrk_leff_d0    .push_back( book( name, htp  + "_lrtEff_d0",     htpstr  + " d0 [mm]",               100,  -300,  300 ) );
	    h_llptrk_leff_z0    .push_back( book( name, htp  + "_lrtEff_z0",     htpstr  + " z0 [mm]",               100, -1500, 1500 ) );
	    h_llptrk_leff_avgMu .push_back( book( name, htp  + "_lrtEff_avgMu",  htpstr  + " average pp interactions",90,     0,   90 ) );
	    h_llptrk_leff_minDR .push_back( book( name, htp  + "_lrtEff_minDR",  htpstr  + " nearest truth track dR",100,     0,  1.0 ) );
	  }
	  h_LLPtrk_x             .push_back( h_llptrk_x          );
	  h_LLPtrk_y             .push_back( h_llptrk_y          );
	  h_LLPtrk_z             .push_back( h_llptrk_z          );
	  h_LLPtrk_r             .push_back( h_llptrk_r          );
	  h_LLPtrk_pt            .push_back( h_llptrk_pt         );
	  h_LLPtrk_eta           .push_back( h_llptrk_eta        );
	  h_LLPtrk_phi           .push_back( h_llptrk_phi        );
	  h_LLPtrk_d0            .push_back( h_llptrk_d0         );
	  h_LLPtrk_z0            .push_back( h_llptrk_z0         );
	  h_LLPtrk_avgMu         .push_back( h_llptrk_avgMu      );
	  h_LLPtrk_minDR         .push_back( h_llptrk_minDR      );
	  h_recoLLPtrk_x         .push_back( h_rllptrk_x         );
	  h_recoLLPtrk_y         .push_back( h_rllptrk_y         );
	  h_recoLLPtrk_z         .push_back( h_rllptrk_z         );
	  h_recoLLPtrk_r         .push_back( h_rllptrk_r         );
	  h_recoLLPtrk_pt        .push_back( h_rllptrk_pt        );
	  h_recoLLPtrk_eta       .push_back( h_rllptrk_eta       );
	  h_recoLLPtrk_phi       .push_back( h_rllptrk_phi       );
	  h_recoLLPtrk_d0        .push_back( h_rllptrk_d0        );
	  h_recoLLPtrk_z0        .push_back( h_rllptrk_z0        );
	  h_recoLLPtrk_avgMu     .push_back( h_rllptrk_avgMu     );
	  h_recoLLPtrk_minDR     .push_back( h_rllptrk_minDR     );
	  h_recoLLPtrk_resid_d0        .push_back( h_rllptrk_resid_d0        );
	  h_recoLLPtrk_resid_z0        .push_back( h_rllptrk_resid_z0        );
	  h_recoLLPtrk_resid_qOverP    .push_back( h_rllptrk_resid_qOverP    );
	  h_recoLLPtrk_resid_d0_r      .push_back( h_rllptrk_resid_d0_r      );
	  h_recoLLPtrk_resid_d0_pt     .push_back( h_rllptrk_resid_d0_pt     );
	  h_recoLLPtrk_resid_z0_r      .push_back( h_rllptrk_resid_z0_r      );
	  h_recoLLPtrk_resid_z0_pt     .push_back( h_rllptrk_resid_z0_pt     );
	  h_recoLLPtrk_resid_qOverP_r  .push_back( h_rllptrk_resid_qOverP_r  );
	  h_recoLLPtrk_resid_qOverP_pt .push_back( h_rllptrk_resid_qOverP_pt );
	  h_stdLLPtrk_x          .push_back( h_sllptrk_x         );
	  h_stdLLPtrk_y          .push_back( h_sllptrk_y         );
	  h_stdLLPtrk_z          .push_back( h_sllptrk_z         );
	  h_stdLLPtrk_r          .push_back( h_sllptrk_r         );
	  h_stdLLPtrk_pt         .push_back( h_sllptrk_pt        );
	  h_stdLLPtrk_eta        .push_back( h_sllptrk_eta       );
	  h_stdLLPtrk_phi        .push_back( h_sllptrk_phi       );
	  h_stdLLPtrk_d0         .push_back( h_sllptrk_d0        );
	  h_stdLLPtrk_z0         .push_back( h_sllptrk_z0        );
	  h_stdLLPtrk_avgMu      .push_back( h_sllptrk_avgMu     );
	  h_stdLLPtrk_minDR      .push_back( h_sllptrk_minDR     );
	  h_stdLLPtrk_resid_d0         .push_back( h_sllptrk_resid_d0        );
	  h_stdLLPtrk_resid_z0         .push_back( h_sllptrk_resid_z0        );
	  h_stdLLPtrk_resid_qOverP     .push_back( h_sllptrk_resid_qOverP    );
	  h_stdLLPtrk_resid_d0_r       .push_back( h_sllptrk_resid_d0_r      );
	  h_stdLLPtrk_resid_d0_pt      .push_back( h_sllptrk_resid_d0_pt     );
	  h_stdLLPtrk_resid_z0_r       .push_back( h_sllptrk_resid_z0_r      );
	  h_stdLLPtrk_resid_z0_pt      .push_back( h_sllptrk_resid_z0_pt     );
	  h_stdLLPtrk_resid_qOverP_r   .push_back( h_sllptrk_resid_qOverP_r  );
	  h_stdLLPtrk_resid_qOverP_pt  .push_back( h_sllptrk_resid_qOverP_pt );
	  h_lrtLLPtrk_x          .push_back( h_lllptrk_x         );
	  h_lrtLLPtrk_y          .push_back( h_lllptrk_y         );
	  h_lrtLLPtrk_z          .push_back( h_lllptrk_z         );
	  h_lrtLLPtrk_r          .push_back( h_lllptrk_r         );
	  h_lrtLLPtrk_pt         .push_back( h_lllptrk_pt        );
	  h_lrtLLPtrk_eta        .push_back( h_lllptrk_eta       );
	  h_lrtLLPtrk_phi        .push_back( h_lllptrk_phi       );
	  h_lrtLLPtrk_d0         .push_back( h_lllptrk_d0        );
	  h_lrtLLPtrk_z0         .push_back( h_lllptrk_z0        );
	  h_lrtLLPtrk_avgMu      .push_back( h_lllptrk_avgMu     );
	  h_lrtLLPtrk_minDR      .push_back( h_lllptrk_minDR     );
	  h_lrtLLPtrk_resid_d0         .push_back( h_lllptrk_resid_d0        );
	  h_lrtLLPtrk_resid_z0         .push_back( h_lllptrk_resid_z0        );
	  h_lrtLLPtrk_resid_qOverP     .push_back( h_lllptrk_resid_qOverP    );
	  h_lrtLLPtrk_resid_d0_r       .push_back( h_lllptrk_resid_d0_r      );
	  h_lrtLLPtrk_resid_d0_pt      .push_back( h_lllptrk_resid_d0_pt     );
	  h_lrtLLPtrk_resid_z0_r       .push_back( h_lllptrk_resid_z0_r      );
	  h_lrtLLPtrk_resid_z0_pt      .push_back( h_lllptrk_resid_z0_pt     );
	  h_lrtLLPtrk_resid_qOverP_r   .push_back( h_lllptrk_resid_qOverP_r  );
	  h_lrtLLPtrk_resid_qOverP_pt  .push_back( h_lllptrk_resid_qOverP_pt );
	  h_LLPtrk_recoEff_x     .push_back( h_llptrk_reff_x     );
	  h_LLPtrk_recoEff_y     .push_back( h_llptrk_reff_y     );
	  h_LLPtrk_recoEff_z     .push_back( h_llptrk_reff_z     );
	  h_LLPtrk_recoEff_r     .push_back( h_llptrk_reff_r     );
	  h_LLPtrk_recoEff_pt    .push_back( h_llptrk_reff_pt    );
	  h_LLPtrk_recoEff_eta   .push_back( h_llptrk_reff_eta   );
	  h_LLPtrk_recoEff_phi   .push_back( h_llptrk_reff_phi   );
	  h_LLPtrk_recoEff_d0    .push_back( h_llptrk_reff_d0    );
	  h_LLPtrk_recoEff_z0    .push_back( h_llptrk_reff_z0    );
	  h_LLPtrk_recoEff_avgMu .push_back( h_llptrk_reff_avgMu );
	  h_LLPtrk_recoEff_minDR .push_back( h_llptrk_reff_minDR );
	  h_LLPtrk_stdEff_x      .push_back( h_llptrk_seff_x     );
	  h_LLPtrk_stdEff_y      .push_back( h_llptrk_seff_y     );
	  h_LLPtrk_stdEff_z      .push_back( h_llptrk_seff_z     );
	  h_LLPtrk_stdEff_r      .push_back( h_llptrk_seff_r     );
	  h_LLPtrk_stdEff_pt     .push_back( h_llptrk_seff_pt    );
	  h_LLPtrk_stdEff_eta    .push_back( h_llptrk_seff_eta   );
	  h_LLPtrk_stdEff_phi    .push_back( h_llptrk_seff_phi   );
	  h_LLPtrk_stdEff_d0     .push_back( h_llptrk_seff_d0    );
	  h_LLPtrk_stdEff_z0     .push_back( h_llptrk_seff_z0    );
	  h_LLPtrk_stdEff_avgMu  .push_back( h_llptrk_seff_avgMu );
	  h_LLPtrk_stdEff_minDR  .push_back( h_llptrk_seff_minDR );
	  h_LLPtrk_lrtEff_x      .push_back( h_llptrk_leff_x     );
	  h_LLPtrk_lrtEff_y      .push_back( h_llptrk_leff_y     );
	  h_LLPtrk_lrtEff_z      .push_back( h_llptrk_leff_z     );
	  h_LLPtrk_lrtEff_r      .push_back( h_llptrk_leff_r     );
	  h_LLPtrk_lrtEff_pt     .push_back( h_llptrk_leff_pt    );
	  h_LLPtrk_lrtEff_eta    .push_back( h_llptrk_leff_eta   );
	  h_LLPtrk_lrtEff_phi    .push_back( h_llptrk_leff_phi   );
	  h_LLPtrk_lrtEff_d0     .push_back( h_llptrk_leff_d0    );
	  h_LLPtrk_lrtEff_z0     .push_back( h_llptrk_leff_z0    );
	  h_LLPtrk_lrtEff_avgMu  .push_back( h_llptrk_leff_avgMu );
	  h_LLPtrk_lrtEff_minDR  .push_back( h_llptrk_leff_minDR );
	} // end reconstruction efficiency
      } // end if not abcdcutOnly
    }
    

    // --- TRACKS --- //
    // tracks: basics / kinematics
    if ( !m_histoInfoSwitch->m_truthOnly ) {
      std::vector<int>   ntrk_x2 = { 5000, 4000, 500, 20, 50, 50, 50, 50 };
      std::vector<TH1F*> h_track_n;
      for ( size_t i = 0; i != hTrk.size(); ++i ) {
	std::string ht    = hTrk   [i] + "trk";
	std::string htstr = hTrkstr[i] + " track";
	int nbin = 100;
	if ( i > 2 ) nbin = ntrk_x2[i];
	h_track_n .push_back( book( name, ht + "_n", "n " + htstr + "s", nbin, 0, ntrk_x2[i] ) );
      } // end loop over track types
      h_trk_n .push_back( h_track_n );
    }
    
    
    // --- TRUTH VERTICES --- //
    if ( m_mc ) {
      std::vector<TH1F*> h_llpdvtx_n;
      std::vector<TH1F*> h_llpdvtx_z;
      std::vector<TH1F*> h_llpdvtx_r;
      std::vector<TH1F*> h_llpdvtx_pt;
      std::vector<TH1F*> h_llpdvtx_eta;
      std::vector<TH1F*> h_llpdvtx_phi;
      std::vector<TH1F*> h_llpdvtx_mass;
      std::vector<TH1F*> h_llpdvtx_childOpAng;
      std::vector<TH1F*> h_llpdvtx_nOutP;
      std::vector<TH1F*> h_llpdvtx_ndesc;
      std::vector<TH1F*> h_llpdvtx_descPt;
      std::vector<TH1F*> h_llpdvtx_descEta;
      std::vector<TH1F*> h_llpdvtx_descPhi;
      std::vector<TH1F*> h_llpdvtx_descE;
      std::vector<TH1F*> h_llpdvtx_descM;
      std::vector<TH1F*> h_llpdvtx_desc_pt;
      std::vector<TH1F*> h_llpdvtx_desc_eta;
      std::vector<TH1F*> h_llpdvtx_desc_phi;
      std::vector<TH1F*> h_llpdvtx_desc_d0;
      std::vector<TH1F*> h_llpdvtx_desc_z0;
      std::vector<TH1F*> h_recollpdvtx_x;
      std::vector<TH1F*> h_recollpdvtx_y;
      std::vector<TH1F*> h_recollpdvtx_z;
      std::vector<TH1F*> h_recollpdvtx_r;
      std::vector<TH1F*> h_recollpdvtx_pt;
      std::vector<TH1F*> h_recollpdvtx_eta;
      std::vector<TH1F*> h_recollpdvtx_phi;
      std::vector<TH1F*> h_recollpdvtx_avgMu;
      std::vector<TH1F*> h_recollpdvtx_descM;
      std::vector<TH1F*> h_recollpdvtx_nDesc;
      std::vector<TH1F*> h_recollpdvtx_nRecoDesc;
      std::vector<TH1F*> h_recollpdvtx_nSelDesc;
      std::vector<TH2F*> h_recollpdvtx_nDesc_r;
      std::vector<TH2F*> h_recollpdvtx_nDesc_z;
      std::vector<TH2F*> h_recollpdvtx_descM_r;
      std::vector<TH2F*> h_recollpdvtx_descM_z;
      std::vector<TH2F*> h_recollpdvtx_nRecoDesc_r;
      std::vector<TH2F*> h_recollpdvtx_nRecoDesc_z;
      std::vector<TH2F*> h_recollpdvtx_recoDescM_r;
      std::vector<TH2F*> h_recollpdvtx_recoDescM_z;
      std::vector<TH2F*> h_recollpdvtx_nVtxDesc_r;
      std::vector<TH2F*> h_recollpdvtx_nVtxDesc_z;
      std::vector<TH2F*> h_recollpdvtx_vtxDescM_r;
      std::vector<TH2F*> h_recollpdvtx_vtxDescM_z;
      std::vector<TH2F*> h_recollpdvtx_fracRecoDesc_r;
      std::vector<TH2F*> h_recollpdvtx_fracRecoDesc_z;
      std::vector<TH2F*> h_recollpdvtx_fracRecoDescM_r;
      std::vector<TH2F*> h_recollpdvtx_fracRecoDescM_z;
      std::vector<TH2F*> h_recollpdvtx_fracVtxDesc_r;
      std::vector<TH2F*> h_recollpdvtx_fracVtxDesc_z;
      std::vector<TH2F*> h_recollpdvtx_fracVtxDescM_r;
      std::vector<TH2F*> h_recollpdvtx_fracVtxDescM_z;
      std::vector<TH1F*> h_reco2llpdvtx_x;
      std::vector<TH1F*> h_reco2llpdvtx_y;
      std::vector<TH1F*> h_reco2llpdvtx_z;
      std::vector<TH1F*> h_reco2llpdvtx_r;
      std::vector<TH1F*> h_reco2llpdvtx_pt;
      std::vector<TH1F*> h_reco2llpdvtx_eta;
      std::vector<TH1F*> h_reco2llpdvtx_phi;
      std::vector<TH1F*> h_reco2llpdvtx_avgMu;
      std::vector<TH1F*> h_reco2llpdvtx_descM;
      std::vector<TH1F*> h_reco2llpdvtx_nDesc;
      std::vector<TH1F*> h_reco2llpdvtx_nRecoDesc;
      std::vector<TH1F*> h_reco2llpdvtx_nSelDesc;
      std::vector<TH1F*> h_slctllpdvtx_x;
      std::vector<TH1F*> h_slctllpdvtx_y;
      std::vector<TH1F*> h_slctllpdvtx_z;
      std::vector<TH1F*> h_slctllpdvtx_r;
      std::vector<TH1F*> h_slctllpdvtx_pt;
      std::vector<TH1F*> h_slctllpdvtx_eta;
      std::vector<TH1F*> h_slctllpdvtx_phi;
      std::vector<TH1F*> h_slctllpdvtx_avgMu;
      std::vector<TH1F*> h_slctllpdvtx_descM;
      std::vector<TH1F*> h_slctllpdvtx_nDesc;
      std::vector<TH1F*> h_slctllpdvtx_nRecoDesc;
      std::vector<TH1F*> h_slctllpdvtx_nSelDesc;
      std::vector<TH1F*> h_matchllpdvtx_score;
      std::vector<TH1F*> h_matchllpdvtx_x;
      std::vector<TH1F*> h_matchllpdvtx_y;
      std::vector<TH1F*> h_matchllpdvtx_z;
      std::vector<TH1F*> h_matchllpdvtx_r;
      std::vector<TH1F*> h_matchllpdvtx_pt;
      std::vector<TH1F*> h_matchllpdvtx_eta;
      std::vector<TH1F*> h_matchllpdvtx_phi;
      std::vector<TH1F*> h_matchllpdvtx_avgMu;
      std::vector<TH1F*> h_matchllpdvtx_descM;
      std::vector<TH1F*> h_matchllpdvtx_nDesc;
      std::vector<TH1F*> h_matchllpdvtx_nRecoDesc;
      std::vector<TH1F*> h_matchllpdvtx_nSelDesc;
      std::vector<TH1F*> h_matchllpdvtx_resid_x;
      std::vector<TH1F*> h_matchllpdvtx_resid_y;
      std::vector<TH1F*> h_matchllpdvtx_resid_z;
      std::vector<TH1F*> h_matchllpdvtx_resid_r;
      std::vector<TH1F*> h_matchllpdvtx_resid_rphi;
      std::vector<TH2F*> h_matchllpdvtx_resid_z_r;
      std::vector<TH2F*> h_matchllpdvtx_resid_z_z;
      std::vector<TH2F*> h_matchllpdvtx_resid_z_ntrk;
      std::vector<TH2F*> h_matchllpdvtx_resid_z_nseltrk;
      std::vector<TH2F*> h_matchllpdvtx_resid_r_r;
      std::vector<TH2F*> h_matchllpdvtx_resid_r_z;
      std::vector<TH2F*> h_matchllpdvtx_resid_r_ntrk;
      std::vector<TH2F*> h_matchllpdvtx_resid_r_nseltrk;
      std::vector<TH2F*> h_matchllpdvtx_resid_rphi_r;
      std::vector<TH2F*> h_matchllpdvtx_resid_rphi_z;
      std::vector<TH2F*> h_matchllpdvtx_resid_rphi_ntrk;
      std::vector<TH2F*> h_matchllpdvtx_resid_rphi_nseltrk;
      std::vector<TH1F*> h_recofllpdvtx_x;
      std::vector<TH1F*> h_recofllpdvtx_y;
      std::vector<TH1F*> h_recofllpdvtx_z;
      std::vector<TH1F*> h_recofllpdvtx_r;
      std::vector<TH1F*> h_recofllpdvtx_pt;
      std::vector<TH1F*> h_recofllpdvtx_eta;
      std::vector<TH1F*> h_recofllpdvtx_phi;
      std::vector<TH1F*> h_recofllpdvtx_avgMu;
      std::vector<TH1F*> h_recofllpdvtx_descM;
      std::vector<TH1F*> h_recofllpdvtx_nDesc;
      std::vector<TH1F*> h_recofllpdvtx_nRecoDesc;
      std::vector<TH1F*> h_recofllpdvtx_nSelDesc;
      std::vector<TH2F*> h_recofllpdvtx_nDesc_r;
      std::vector<TH2F*> h_recofllpdvtx_nDesc_z;
      std::vector<TH2F*> h_recofllpdvtx_descM_r;
      std::vector<TH2F*> h_recofllpdvtx_descM_z;
      std::vector<TH2F*> h_recofllpdvtx_nRecoDesc_r;
      std::vector<TH2F*> h_recofllpdvtx_nRecoDesc_z;
      std::vector<TH2F*> h_recofllpdvtx_recoDescM_r;
      std::vector<TH2F*> h_recofllpdvtx_recoDescM_z;
      std::vector<std::vector<TH2F*>> h_recofllpdvtx_nVtxDesc_r;
      std::vector<std::vector<TH2F*>> h_recofllpdvtx_nVtxDesc_z;
      std::vector<std::vector<TH2F*>> h_recofllpdvtx_vtxDescM_r;
      std::vector<std::vector<TH2F*>> h_recofllpdvtx_vtxDescM_z;
      std::vector<TH2F*> h_recofllpdvtx_fracRecoDesc_r;
      std::vector<TH2F*> h_recofllpdvtx_fracRecoDesc_z;
      std::vector<TH2F*> h_recofllpdvtx_fracRecoDescM_r;
      std::vector<TH2F*> h_recofllpdvtx_fracRecoDescM_z;
      std::vector<std::vector<TH2F*>> h_recofllpdvtx_fracVtxDesc_r;
      std::vector<std::vector<TH2F*>> h_recofllpdvtx_fracVtxDesc_z;
      std::vector<std::vector<TH2F*>> h_recofllpdvtx_fracVtxDescM_r;
      std::vector<std::vector<TH2F*>> h_recofllpdvtx_fracVtxDescM_z;
      std::vector<TH1F*> h_reco2fllpdvtx_x;
      std::vector<TH1F*> h_reco2fllpdvtx_y;
      std::vector<TH1F*> h_reco2fllpdvtx_z;
      std::vector<TH1F*> h_reco2fllpdvtx_r;
      std::vector<TH1F*> h_reco2fllpdvtx_pt;
      std::vector<TH1F*> h_reco2fllpdvtx_eta;
      std::vector<TH1F*> h_reco2fllpdvtx_phi;
      std::vector<TH1F*> h_reco2fllpdvtx_avgMu;
      std::vector<TH1F*> h_reco2fllpdvtx_descM;
      std::vector<TH1F*> h_reco2fllpdvtx_nDesc;
      std::vector<TH1F*> h_reco2fllpdvtx_nRecoDesc;
      std::vector<TH1F*> h_reco2fllpdvtx_nSelDesc;
      std::vector<TH1F*> h_slctfllpdvtx_x;
      std::vector<TH1F*> h_slctfllpdvtx_y;
      std::vector<TH1F*> h_slctfllpdvtx_z;
      std::vector<TH1F*> h_slctfllpdvtx_r;
      std::vector<TH1F*> h_slctfllpdvtx_pt;
      std::vector<TH1F*> h_slctfllpdvtx_eta;
      std::vector<TH1F*> h_slctfllpdvtx_phi;
      std::vector<TH1F*> h_slctfllpdvtx_avgMu;
      std::vector<TH1F*> h_slctfllpdvtx_descM;
      std::vector<TH1F*> h_slctfllpdvtx_nDesc;
      std::vector<TH1F*> h_slctfllpdvtx_nRecoDesc;
      std::vector<TH1F*> h_slctfllpdvtx_nSelDesc;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_score;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_x;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_y;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_z;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_r;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_pt;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_eta;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_phi;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_avgMu;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_descM;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_nDesc;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_nRecoDesc;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_nSelDesc;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_resid_x;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_resid_y;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_resid_z;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_resid_r;
      std::vector<std::vector<TH1F*>> h_smatchllpdvtx_resid_rphi;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_z_r;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_z_z;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_z_ntrk;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_z_nseltrk;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_r_r;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_r_z;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_r_ntrk;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_r_nseltrk;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_rphi_r;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_rphi_z;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_rphi_ntrk;
      std::vector<std::vector<TH2F*>> h_smatchllpdvtx_resid_rphi_nseltrk;
      std::vector<TH1F*> h_llpdvtx_accept_x;
      std::vector<TH1F*> h_llpdvtx_accept_y;
      std::vector<TH1F*> h_llpdvtx_accept_z;
      std::vector<TH1F*> h_llpdvtx_accept_r;
      std::vector<TH1F*> h_llpdvtx_accept_pt;
      std::vector<TH1F*> h_llpdvtx_accept_eta;
      std::vector<TH1F*> h_llpdvtx_accept_phi;
      std::vector<TH1F*> h_llpdvtx_accept_avgMu;
      std::vector<TH1F*> h_llpdvtx_accept_descM;
      std::vector<TH1F*> h_llpdvtx_accept_nDesc;
      std::vector<TH1F*> h_llpdvtx_accept_nRecoDesc;
      std::vector<TH1F*> h_llpdvtx_accept_nSelDesc;
      std::vector<TH1F*> h_llpdvtx_recoEff_x;
      std::vector<TH1F*> h_llpdvtx_recoEff_y;
      std::vector<TH1F*> h_llpdvtx_recoEff_z;
      std::vector<TH1F*> h_llpdvtx_recoEff_r;
      std::vector<TH1F*> h_llpdvtx_recoEff_pt;
      std::vector<TH1F*> h_llpdvtx_recoEff_eta;
      std::vector<TH1F*> h_llpdvtx_recoEff_phi;
      std::vector<TH1F*> h_llpdvtx_recoEff_avgMu;
      std::vector<TH1F*> h_llpdvtx_recoEff_descM;
      std::vector<TH1F*> h_llpdvtx_recoEff_nDesc;
      std::vector<TH1F*> h_llpdvtx_recoEff_nRecoDesc;
      std::vector<TH1F*> h_llpdvtx_recoEff_nSelDesc;
      std::vector<TH1F*> h_llpdvtx_algEff_x;
      std::vector<TH1F*> h_llpdvtx_algEff_y;
      std::vector<TH1F*> h_llpdvtx_algEff_z;
      std::vector<TH1F*> h_llpdvtx_algEff_r;
      std::vector<TH1F*> h_llpdvtx_algEff_pt;
      std::vector<TH1F*> h_llpdvtx_algEff_eta;
      std::vector<TH1F*> h_llpdvtx_algEff_phi;
      std::vector<TH1F*> h_llpdvtx_algEff_avgMu;
      std::vector<TH1F*> h_llpdvtx_algEff_descM;
      std::vector<TH1F*> h_llpdvtx_algEff_nDesc;
      std::vector<TH1F*> h_llpdvtx_algEff_nRecoDesc;
      std::vector<TH1F*> h_llpdvtx_algEff_nSelDesc;
      std::vector<TH1F*> h_llpdvtx_coreEff_x;
      std::vector<TH1F*> h_llpdvtx_coreEff_y;
      std::vector<TH1F*> h_llpdvtx_coreEff_z;
      std::vector<TH1F*> h_llpdvtx_coreEff_r;
      std::vector<TH1F*> h_llpdvtx_coreEff_pt;
      std::vector<TH1F*> h_llpdvtx_coreEff_eta;
      std::vector<TH1F*> h_llpdvtx_coreEff_phi;
      std::vector<TH1F*> h_llpdvtx_coreEff_avgMu;
      std::vector<TH1F*> h_llpdvtx_coreEff_descM;
      std::vector<TH1F*> h_llpdvtx_coreEff_nDesc;
      std::vector<TH1F*> h_llpdvtx_coreEff_nRecoDesc;
      std::vector<TH1F*> h_llpdvtx_coreEff_nSelDesc;
      std::vector<TH1F*> h_llpdvtx_seedEff_x;
      std::vector<TH1F*> h_llpdvtx_seedEff_y;
      std::vector<TH1F*> h_llpdvtx_seedEff_z;
      std::vector<TH1F*> h_llpdvtx_seedEff_r;
      std::vector<TH1F*> h_llpdvtx_seedEff_pt;
      std::vector<TH1F*> h_llpdvtx_seedEff_eta;
      std::vector<TH1F*> h_llpdvtx_seedEff_phi;
      std::vector<TH1F*> h_llpdvtx_seedEff_avgMu;
      std::vector<TH1F*> h_llpdvtx_seedEff_descM;
      std::vector<TH1F*> h_llpdvtx_seedEff_nDesc;
      std::vector<TH1F*> h_llpdvtx_seedEff_nRecoDesc;
      std::vector<TH1F*> h_llpdvtx_seedEff_nSelDesc;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_x;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_y;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_z;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_r;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_pt;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_eta;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_phi;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_avgMu;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_descM;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_nDesc;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_nRecoDesc;
      std::vector<TH1F*> h_llpdvtx_sgnlaccept_nSelDesc;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_x;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_y;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_z;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_r;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_pt;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_eta;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_phi;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_avgMu;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_descM;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_nDesc;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_nRecoDesc;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlrecoEff_nSelDesc;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_x;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_y;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_z;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_r;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_pt;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_eta;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_phi;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_avgMu;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_descM;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_nDesc;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_nRecoDesc;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlalgEff_nSelDesc;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_x;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_y;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_z;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_r;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_pt;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_eta;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_phi;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_avgMu;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_descM;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_nDesc;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_nRecoDesc;
      std::vector<std::vector<TH1F*>> h_llpdvtx_sgnlcoreEff_nSelDesc;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_x;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_y;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_z;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_r;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_pt;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_eta;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_phi;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_avgMu;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_descM;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_nDesc;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_nRecoDesc;
      std::vector<TH1F*> h_llpdvtx_sgnlseedEff_nSelDesc;
      for ( size_t i = 0; i != hLLP.size(); ++i ) {
	// llp decay truth vertex basics
	std::string hllp       = hLLP    [i] + "DecayVtx"; hllp[0] = tolower(hllp[0]);
	std::string hllpstr    = hLLPstr [i]; hllpstr.pop_back();
	std::string hllpstrpl  = hllpstr; hllpstr += " decay vertex"; hllpstrpl += " decay vertices";
	std::string hllpdstr   = hllpstr +   " descendant";
	std::string hllpndstr  = hllpstr + " n-descendant";
	std::string hrllp      = "recoble"   + hLLP[i] + "DecayVtx";
	std::string hrllpstr   = "reconstructible "          + hllpstr;
	std::string hr2llp     = "reco"      + hLLP[i] + "DecayVtx";
	std::string hr2llpstr  = "reconstructed "            + hllpstr;
	std::string hsllp      = "sel"       + hLLP[i] + "DecayVtx";
	std::string hsllpstr   = "selected "                 + hllpstr;
	std::string hmllp      = "recoMatch" + hLLP[i] + "DecayVtx";
	std::string hmllpstr   = "reco-matched "             + hllpstr;
	std::string hrfllp     = "fiduc"     + hLLP[i] + "DecayVtx";
	std::string hrfllpstr  = "reconstructible fiducial " + hllpstr;
	std::string hr2fllp    = "recoFiduc" + hLLP[i] + "DecayVtx";
	std::string hr2fllpstr = "reconstructed fiducial "   + hllpstr;
	std::string hsfllp     = "selFiduc"  + hLLP[i] + "DecayVtx";
	std::string hsfllpstr  = "selected fiducial "        + hllpstr;
	h_llpdvtx_n          .push_back( book( name, hllp + "_n",          "n " + hllpstrpl,                  100,     0,  100 ) );
	if ( m_histoInfoSwitch->m_abcdcutOnly ) continue;
	h_llpdvtx_z          .push_back( book( name, hllp + "_z",          hllpstr + " z-pos [mm]",           100, -2500, 2500 ) );
	h_llpdvtx_r          .push_back( book( name, hllp + "_r",          hllpstr + " r-pos [mm]",           100,     0,  600 ) );
	h_llpdvtx_pt         .push_back( book( name, hllp + "_pt",         hllpstr + " p_{T} [GeV]",          100,     0,  500 ) );
	h_llpdvtx_eta        .push_back( book( name, hllp + "_eta",        hllpstr + " eta",                  100,    -5,    5 ) );
	h_llpdvtx_phi        .push_back( book( name, hllp + "_phi",        hllpstr + " phi",                  100,  -3.5,  3.5 ) );
	h_llpdvtx_mass       .push_back( book( name, hllp + "_mass",       hllpstr + " mass [GeV]",           100,     0,   30 ) );
	h_llpdvtx_childOpAng .push_back( book( name, hllp + "_childOpAng", hllpstr + " opening angle",        100,     0,    6 ) );
	h_llpdvtx_nOutP      .push_back( book( name, hllp + "_nOutP",      hllpstr + " n outgoing particles",   5,     0,    5 ) );
	h_llpdvtx_ndesc      .push_back( book( name, hllp + "_nDesc",      "n " + hllpdstr + "s",              20,     0,   20 ) );
	if ( m_histoInfoSwitch->m_llpDesc ) {
	  h_llpdvtx_descPt   .push_back( book( name, hllp + "_descPt",     hllpndstr + " p_{T} [GeV]",        100,     0,  250 ) );
	  h_llpdvtx_descEta  .push_back( book( name, hllp + "_descEta",    hllpndstr + " eta",                100,    -5,    5 ) );
	  h_llpdvtx_descPhi  .push_back( book( name, hllp + "_descPhi",    hllpndstr + " phi",                100,  -3.5,  3.5 ) );
	  h_llpdvtx_descE    .push_back( book( name, hllp + "_descE",      hllpndstr + " energy [GeV]",       100,     0,  350 ) );
	  h_llpdvtx_descM    .push_back( book( name, hllp + "_descM",      hllpndstr + " mass [GeV]",         100,     0,   30 ) );
	  h_llpdvtx_desc_pt  .push_back( book( name, hllp + "_desc_pt",    hllpdstr  + " p_{T} [GeV]",        100,     0,   50 ) );
	  h_llpdvtx_desc_eta .push_back( book( name, hllp + "_desc_eta",   hllpdstr  + " eta",                100,    -5,    5 ) );
	  h_llpdvtx_desc_phi .push_back( book( name, hllp + "_desc_phi",   hllpdstr  + " phi",                100,  -3.5,  3.5 ) );
	  h_llpdvtx_desc_d0  .push_back( book( name, hllp + "_desc_d0",    hllpdstr  + " d0 [mm]",            100,  -300,  300 ) );
	  h_llpdvtx_desc_z0  .push_back( book( name, hllp + "_desc_z0",    hllpdstr  + " z0 [mm]",            100, -1500, 1500 ) );
	}
	if ( m_histoInfoSwitch->m_llpRecoEff || m_histoInfoSwitch->m_llpvtxRecoEff ) {
	  h_recollpdvtx_x              .push_back( book( name, hrllp   + "_x",         hrllpstr   + " x-pos [mm]",             100,  -600,  600 ) );
	  h_recollpdvtx_y              .push_back( book( name, hrllp   + "_y",         hrllpstr   + " y-pos [mm]",             100,  -600,  600 ) );
	  h_recollpdvtx_z              .push_back( book( name, hrllp   + "_z",         hrllpstr   + " z-pos [mm]",             100, -2500, 2500 ) );
	  h_recollpdvtx_r              .push_back( book( name, hrllp   + "_r",         hrllpstr   + " r-pos [mm]",             100,     0,  600 ) );
	  h_recollpdvtx_pt             .push_back( book( name, hrllp   + "_pt",        hrllpstr   + " p_{T} [GeV]",            100,     0,  500 ) );
	  h_recollpdvtx_eta            .push_back( book( name, hrllp   + "_eta",       hrllpstr   + " eta",                    100,    -5,    5 ) );
	  h_recollpdvtx_phi            .push_back( book( name, hrllp   + "_phi",       hrllpstr   + " phi",                    100,  -3.5,  3.5 ) );
	  h_recollpdvtx_avgMu          .push_back( book( name, hrllp   + "_avgMu",     hrllpstr   + " average pp interactions", 90,     0,   90 ) );
	  h_recollpdvtx_descM          .push_back( book( name, hrllp   + "_descM",     hrllpstr   + " descendant mass [GeV]",  100,     0,   21 ) );
	  h_recollpdvtx_nDesc          .push_back( book( name, hrllp   + "_nDesc",     "n "+hrllpstr+" descendants",                20, 0,   20 ) );
	  h_recollpdvtx_nRecoDesc      .push_back( book( name, hrllp   + "_nRecoDesc", "n "+hrllpstr+" reconstructed descendants",  20, 0,   20 ) );
	  h_recollpdvtx_nSelDesc       .push_back( book( name, hrllp   + "_nSelDesc",  "n "+hrllpstr+" selected descendants",       20, 0,   20 ) );
	  h_recollpdvtx_nDesc_r        .push_back( book( name, hrllp   + "_nDesc_r",         hrllpstr       + " r-pos [mm]",   100,     0,  600,
							 "n " + hrllpstr + " descendants",                     20, 0, 20 ) );
	  h_recollpdvtx_nDesc_z        .push_back( book( name, hrllp   + "_nDesc_z",         hrllpstr       + " z-pos [mm]",   100, -2500, 2500,
							 "n " + hrllpstr + " descendants",                     20, 0, 20 ) );
	  h_recollpdvtx_descM_r        .push_back( book( name, hrllp   + "_descM_r",         hrllpstr       + " r-pos [mm]",   100,     0,  600,
							 hrllpstr + " descendant mass [GeV]",                 100, 0, 21 ) );
	  h_recollpdvtx_descM_z        .push_back( book( name, hrllp   + "_descM_z",         hrllpstr       + " z-pos [mm]",   100, -2500, 2500,
							 hrllpstr + " descendant mass [GeV]",                 100, 0, 21 ) );
	  h_recollpdvtx_nRecoDesc_r    .push_back( book( name, hrllp   + "_nRecoDesc_r",     hrllpstr   + " r-pos [mm]",       100,     0,  600,
							 "n " + hrllpstr + " reconstructed descendants",       20, 0, 20 ) );
	  h_recollpdvtx_nRecoDesc_z    .push_back( book( name, hrllp   + "_nRecoDesc_z",     hrllpstr   + " z-pos [mm]",       100, -2500, 2500,
							 "n " + hrllpstr + " reconstructed descendants",       20, 0, 20 ) );
	  h_recollpdvtx_recoDescM_r    .push_back( book( name, hrllp   + "_recoDescM_r",     hrllpstr   + " r-pos [mm]",       100,     0,  600,
							 hrllpstr + " reconstructed descendant mass [GeV]",   100, 0, 21 ) );
	  h_recollpdvtx_recoDescM_z    .push_back( book( name, hrllp   + "_recoDescM_z",     hrllpstr   + " z-pos [mm]",       100, -2500, 2500,
							 hrllpstr + " reconstructed descendant mass [GeV]",   100, 0, 21 ) );
	  h_recollpdvtx_nVtxDesc_r     .push_back( book( name, hrllp   + "_nVtxDesc_r",      hrllpstr    + " r-pos [mm]",      100,     0,  600,
							 "n " + hrllpstr + " vertexed descendants",            20, 0, 20 ) );
	  h_recollpdvtx_nVtxDesc_z     .push_back( book( name, hrllp   + "_nVtxDesc_z",      hrllpstr    + " z-pos [mm]",      100, -2500, 2500,
							 "n " + hrllpstr + " vertexed descendants",            20, 0, 20 ) );
	  h_recollpdvtx_vtxDescM_r     .push_back( book( name, hrllp   + "_vtxDescM_r",      hrllpstr    + " r-pos [mm]",      100,     0,  600,
							 hrllpstr + " vertexed descendant mass [GeV]",        100, 0, 21 ) );
	  h_recollpdvtx_vtxDescM_z     .push_back( book( name, hrllp   + "_vtxDescM_z",      hrllpstr    + " z-pos [mm]",      100, -2500, 2500,
							 hrllpstr + " vertexed descendant mass [GeV]",        100, 0, 21 ) );
	  h_recollpdvtx_fracRecoDesc_r .push_back( book( name, hrllp   + "_fracRecoDesc_r",  hrllpstr   + " r-pos [mm]",       100,     0,  600,
							 "fraction " + hrllpstr + " reconstructed descendants",100,0,  1 ) );
	  h_recollpdvtx_fracRecoDesc_z .push_back( book( name, hrllp   + "_fracRecoDesc_z",  hrllpstr   + " z-pos [mm]",       100, -2500, 2500,
							 "fraction " + hrllpstr + " reconstructed descendants",100,0,  1 ) );
	  h_recollpdvtx_fracRecoDescM_r.push_back( book( name, hrllp   + "_fracRecoDescM_r", hrllpstr   + " r-pos [mm]",       100,     0,  600,
							 hrllpstr + " reconstructed descendant mass fraction", 100,0,  1 ) );
	  h_recollpdvtx_fracRecoDescM_z.push_back( book( name, hrllp   + "_fracRecoDescM_z", hrllpstr   + " z-pos [mm]",       100, -2500, 2500,
							 hrllpstr + " reconstructed descendant mass fraction", 100,0,  1 ) );
	  h_recollpdvtx_fracVtxDesc_r  .push_back( book( name, hrllp   + "_fracVtxDesc_r",   hrllpstr    + " r-pos [mm]",      100,     0,  600,
							 "fraction " + hrllpstr + " vertexed descendants",     100,0,  1 ) );
	  h_recollpdvtx_fracVtxDesc_z  .push_back( book( name, hrllp   + "_fracVtxDesc_z",   hrllpstr    + " z-pos [mm]",      100, -2500, 2500,
							 "fraction " + hrllpstr + " vertexed descendants",     100,0,  1 ) );
	  h_recollpdvtx_fracVtxDescM_r .push_back( book( name, hrllp   + "_fracVtxDescM_r",  hrllpstr    + " r-pos [mm]",      100,     0,  600,
							 hrllpstr + " vertexed descendant mass fraction",      100,0,  1 ) );
	  h_recollpdvtx_fracVtxDescM_z .push_back( book( name, hrllp   + "_fracVtxDescM_z",  hrllpstr    + " z-pos [mm]",      100, -2500, 2500,
							 hrllpstr + " vertexed descendant mass fraction",      100,0,  1 ) );
	  h_reco2llpdvtx_x          .push_back( book( name, hr2llp  + "_x",         hr2llpstr  + " x-pos [mm]",             100,  -600,  600 ) );
	  h_reco2llpdvtx_y          .push_back( book( name, hr2llp  + "_y",         hr2llpstr  + " y-pos [mm]",             100,  -600,  600 ) );
	  h_reco2llpdvtx_z          .push_back( book( name, hr2llp  + "_z",         hr2llpstr  + " z-pos [mm]",             100, -2500, 2500 ) );
	  h_reco2llpdvtx_r          .push_back( book( name, hr2llp  + "_r",         hr2llpstr  + " r-pos [mm]",             100,     0,  600 ) );
	  h_reco2llpdvtx_pt         .push_back( book( name, hr2llp  + "_pt",        hr2llpstr  + " p_{T} [GeV]",            100,     0,  500 ) );
	  h_reco2llpdvtx_eta        .push_back( book( name, hr2llp  + "_eta",       hr2llpstr  + " eta",                    100,    -5,    5 ) );
	  h_reco2llpdvtx_phi        .push_back( book( name, hr2llp  + "_phi",       hr2llpstr  + " phi",                    100,  -3.5,  3.5 ) );
	  h_reco2llpdvtx_avgMu      .push_back( book( name, hr2llp  + "_avgMu",     hr2llpstr  + " average pp interactions", 90,     0,   90 ) );
	  h_reco2llpdvtx_descM      .push_back( book( name, hr2llp  + "_descM",     hr2llpstr  + " descendant mass [GeV]",  100,     0,   21 ) );
	  h_reco2llpdvtx_nDesc      .push_back( book( name, hr2llp  + "_nDesc",     "n "+hr2llpstr+" descendants",               20, 0,   20 ) );
	  h_reco2llpdvtx_nRecoDesc  .push_back( book( name, hr2llp  + "_nRecoDesc", "n "+hr2llpstr+" reconstructed descendants", 20, 0,   20 ) );
	  h_reco2llpdvtx_nSelDesc   .push_back( book( name, hr2llp  + "_nSelDesc",  "n "+hr2llpstr+" selected descendants",      20, 0,   20 ) );
	  h_slctllpdvtx_x           .push_back( book( name, hsllp   + "_x",         hsllpstr   + " x-pos [mm]",             100,  -600,  600 ) );
	  h_slctllpdvtx_y           .push_back( book( name, hsllp   + "_y",         hsllpstr   + " y-pos [mm]",             100,  -600,  600 ) );
	  h_slctllpdvtx_z           .push_back( book( name, hsllp   + "_z",         hsllpstr   + " z-pos [mm]",             100, -2500, 2500 ) );
	  h_slctllpdvtx_r           .push_back( book( name, hsllp   + "_r",         hsllpstr   + " r-pos [mm]",             100,     0,  600 ) );
	  h_slctllpdvtx_pt          .push_back( book( name, hsllp   + "_pt",        hsllpstr   + " p_{T} [GeV]",            100,     0,  500 ) );
	  h_slctllpdvtx_eta         .push_back( book( name, hsllp   + "_eta",       hsllpstr   + " eta",                    100,    -5,    5 ) );
	  h_slctllpdvtx_phi         .push_back( book( name, hsllp   + "_phi",       hsllpstr   + " phi",                    100,  -3.5,  3.5 ) );
	  h_slctllpdvtx_avgMu       .push_back( book( name, hsllp   + "_avgMu",     hsllpstr   + " average pp interactions", 90,     0,   90 ) );
	  h_slctllpdvtx_descM       .push_back( book( name, hsllp   + "_descM",     hsllpstr   + " descendant mass [GeV]",  100,     0,   21 ) );
	  h_slctllpdvtx_nDesc       .push_back( book( name, hsllp   + "_nDesc",     "n "+hsllpstr+" descendants",                20, 0,   20 ) );
	  h_slctllpdvtx_nRecoDesc   .push_back( book( name, hsllp   + "_nRecoDesc", "n "+hsllpstr+" reconstructed descendants",  20, 0,   20 ) );
	  h_slctllpdvtx_nSelDesc    .push_back( book( name, hsllp   + "_nSelDesc",  "n "+hsllpstr+" selected descendants",       20, 0,   20 ) );
	  h_matchllpdvtx_score      .push_back( book( name, hmllp   + "_score",     hmllpstr   + " match score",            100,     0,    1 ) );
	  h_matchllpdvtx_x          .push_back( book( name, hmllp   + "_x",         hmllpstr   + " x-pos [mm]",             100,  -600,  600 ) );
	  h_matchllpdvtx_y          .push_back( book( name, hmllp   + "_y",         hmllpstr   + " y-pos [mm]",             100,  -600,  600 ) );
	  h_matchllpdvtx_z          .push_back( book( name, hmllp   + "_z",         hmllpstr   + " z-pos [mm]",             100, -2500, 2500 ) );
	  h_matchllpdvtx_r          .push_back( book( name, hmllp   + "_r",         hmllpstr   + " r-pos [mm]",             100,     0,  600 ) );
	  h_matchllpdvtx_pt         .push_back( book( name, hmllp   + "_pt",        hmllpstr   + " p_{T} [GeV]",            100,     0,  500 ) );
	  h_matchllpdvtx_eta        .push_back( book( name, hmllp   + "_eta",       hmllpstr   + " eta",                    100,    -5,    5 ) );
	  h_matchllpdvtx_phi        .push_back( book( name, hmllp   + "_phi",       hmllpstr   + " phi",                    100,  -3.5,  3.5 ) );
	  h_matchllpdvtx_avgMu      .push_back( book( name, hmllp   + "_avgMu",     hmllpstr   + " average pp interaction",  90,     0,   90 ) );
	  h_matchllpdvtx_descM      .push_back( book( name, hmllp   + "_descM",     hmllpstr   + " descendant mass [GeV]",  100,     0,   21 ) );
	  h_matchllpdvtx_nDesc      .push_back( book( name, hmllp   + "_nDesc",     "n "+hsllpstr+" descendants",                20, 0,   20 ) );
	  h_matchllpdvtx_nRecoDesc  .push_back( book( name, hmllp   + "_nRecoDesc", "n "+hsllpstr+" reconstructed descendants",  20, 0,   20 ) );
	  h_matchllpdvtx_nSelDesc   .push_back( book( name, hmllp   + "_nSelDesc",  "n "+hsllpstr+" selected descendants",       20, 0,   20 ) );
	  h_matchllpdvtx_resid_x    .push_back( book( name, hmllp   + "_resid_x",   hmllpstr   + " residual x-pos [mm]",    100,   -10,   10 ) );
	  h_matchllpdvtx_resid_y    .push_back( book( name, hmllp   + "_resid_y",   hmllpstr   + " residual y-pos [mm]",    100,   -10,   10 ) );
	  h_matchllpdvtx_resid_z    .push_back( book( name, hmllp   + "_resid_z",   hmllpstr   + " residual z-pos [mm]",    100,   -10,   10 ) );
	  h_matchllpdvtx_resid_r    .push_back( book( name, hmllp   + "_resid_r",   hmllpstr   + " residual r-pos [mm]",    100,   -10,   10 ) );
	  h_matchllpdvtx_resid_rphi .push_back( book( name, hmllp   + "_resid_rphi",hmllpstr   + " r times residual phi-pos [mm]",100,-10,10 ) );
	  h_matchllpdvtx_resid_z_r
	    .push_back( book( name, hmllp + "_resid_z_r",          hmllpstr + " r-pos [mm]",      100,     0,  600,
			      hmllpstr + " residual z-pos [mm]",           100, -10, 10 ) );
	  h_matchllpdvtx_resid_z_z
	    .push_back( book( name, hmllp + "_resid_z_z",          hmllpstr + " z-pos [mm]",      100, -2500, 2500,
			      hmllpstr + " residual z-pos [mm]",           100, -10, 10 ) );
	  h_matchllpdvtx_resid_z_ntrk
	    .push_back( book( name, hmllp + "_resid_z_ntrk",       hmllpstr + " n tracks",         20,     0,   20,
			      hmllpstr + " residual z-pos [mm]",           100, -10, 10 ) );
	  h_matchllpdvtx_resid_z_nseltrk
	    .push_back( book( name, hmllp + "_resid_z_nseltrk",    hmllpstr + " n selected tracks",20,     0,   20,
			      hmllpstr + " residual z-pos [mm]",           100, -10, 10 ) );
	  h_matchllpdvtx_resid_r_r
	    .push_back( book( name, hmllp + "_resid_r_r",          hmllpstr + " r-pos [mm]",      100,     0,  600,
			      hmllpstr + " residual r-pos [mm]",           100, -10, 10 ) );
	  h_matchllpdvtx_resid_r_z
	    .push_back( book( name, hmllp + "_resid_r_z",          hmllpstr + " z-pos [mm]",      100, -2500, 2500,
			      hmllpstr + " residual r-pos [mm]",           100, -10, 10 ) );
	  h_matchllpdvtx_resid_r_ntrk
	    .push_back( book( name, hmllp + "_resid_r_ntrk",       hmllpstr + " n tracks",         20,     0,   20,
			      hmllpstr + " residual r-pos [mm]",           100, -10, 10 ) );
	  h_matchllpdvtx_resid_r_nseltrk
	    .push_back( book( name, hmllp + "_resid_r_nseltrk",    hmllpstr + " n selected tracks",20,     0,   20,
			      hmllpstr + " residual r-pos [mm]",           100, -10, 10 ) );
	  h_matchllpdvtx_resid_rphi_r
	    .push_back( book( name, hmllp + "_resid_rphi_r",       hmllpstr + " r-pos [mm]",      100,     0,  600,
			      hmllpstr + " r times residual phi-pos [mm]", 100, -10, 10 ) );
	  h_matchllpdvtx_resid_rphi_z
	    .push_back( book( name, hmllp + "_resid_rphi_z",       hmllpstr + " z-pos [mm]",      100, -2500, 2500,
			      hmllpstr + " r times residual phi-pos [mm]", 100, -10, 10 ) );
	  h_matchllpdvtx_resid_rphi_ntrk
	    .push_back( book( name, hmllp + "_resid_rphi_ntrk",    hmllpstr + " n tracks",         20,     0,   20,
			      hmllpstr + " r times residual phi-pos [mm]", 100, -10, 10 ) );
	  h_matchllpdvtx_resid_rphi_nseltrk
	    .push_back( book( name, hmllp + "_resid_rphi_nseltrk", hmllpstr + " n selected tracks",20,     0,   20,
			      hmllpstr + " r times residual phi-pos [mm]", 100, -10, 10 ) );
	  h_recofllpdvtx_x          .push_back( book( name, hrfllp  + "_x",         hrfllpstr  + " x-pos [mm]",             100,  -300,  300 ) );
	  h_recofllpdvtx_y          .push_back( book( name, hrfllp  + "_y",         hrfllpstr  + " y-pos [mm]",             100,  -300,  300 ) );
	  h_recofllpdvtx_z          .push_back( book( name, hrfllp  + "_z",         hrfllpstr  + " z-pos [mm]",             100,  -300,  300 ) );
	  h_recofllpdvtx_r          .push_back( book( name, hrfllp  + "_r",         hrfllpstr  + " r-pos [mm]",             100,     0,  300 ) );
	  h_recofllpdvtx_pt         .push_back( book( name, hrfllp  + "_pt",        hrfllpstr  + " p_{T} [GeV]",            100,     0,  500 ) );
	  h_recofllpdvtx_eta        .push_back( book( name, hrfllp  + "_eta",       hrfllpstr  + " eta",                    100,    -5,    5 ) );
	  h_recofllpdvtx_phi        .push_back( book( name, hrfllp  + "_phi",       hrfllpstr  + " phi",                    100,  -3.5,  3.5 ) );
	  h_recofllpdvtx_avgMu      .push_back( book( name, hrfllp  + "_avgMu",     hrfllpstr  + " average pp interactions", 90,     0,   90 ) );
	  h_recofllpdvtx_descM      .push_back( book( name, hrfllp  + "_descM",     hrfllpstr  + " descendant mass [GeV]",  100,     0,   21 ) );
	  h_recofllpdvtx_nDesc      .push_back( book( name, hrfllp  + "_nDesc",     "n "+hrfllpstr+" descendants",               20, 0,   20 ) );
	  h_recofllpdvtx_nRecoDesc  .push_back( book( name, hrfllp  + "_nRecoDesc", "n "+hrfllpstr+" reconstructed descendants", 20, 0,   20 ) );
	  h_recofllpdvtx_nSelDesc   .push_back( book( name, hrfllp  + "_nSelDesc",  "n "+hrfllpstr+" selected descendants",      20, 0,   20 ) );
	  h_recofllpdvtx_nDesc_r        .push_back( book( name, hrfllp   + "_nDesc_r",   hrfllpstr       + " r-pos [mm]",   100,   0,  300,
							  "n " + hrfllpstr + " descendants",                      20, 0, 20 ) );
	  h_recofllpdvtx_nDesc_z        .push_back( book( name, hrfllp   + "_nDesc_z",   hrfllpstr       + " z-pos [mm]",   100, -300, 300,
							  "n " + hrfllpstr + " descendants",                      20, 0, 20 ) );
	  h_recofllpdvtx_descM_r        .push_back( book( name, hrfllp   + "_descM_r",   hrfllpstr       + " r-pos [mm]",   100,   0,  300,
							  hrfllpstr + " descendant mass [GeV]",                  100, 0, 21 ) );
	  h_recofllpdvtx_descM_z        .push_back( book( name, hrfllp   + "_descM_z",   hrfllpstr       + " z-pos [mm]",   100, -300, 300,
							  hrfllpstr + " descendant mass [GeV]",                  100, 0, 21 ) );
	  h_recofllpdvtx_nRecoDesc_r    .push_back( book( name, hrfllp   + "_nRecoDesc_r",   hrfllpstr   + " r-pos [mm]",   100,   0,  300,
							  "n " + hrfllpstr + " reconstructed descendants",        20, 0, 20 ) );
	  h_recofllpdvtx_nRecoDesc_z    .push_back( book( name, hrfllp   + "_nRecoDesc_z",   hrfllpstr   + " z-pos [mm]",   100, -300, 300,
							  "n " + hrfllpstr + " reconstructed descendants",        20, 0, 20 ) );
	  h_recofllpdvtx_recoDescM_r    .push_back( book( name, hrfllp   + "_recoDescM_r",   hrfllpstr   + " r-pos [mm]",   100,    0, 300,
							  hrfllpstr + " reconstructed descendant mass [GeV]",    100, 0, 21 ) );
	  h_recofllpdvtx_recoDescM_z    .push_back( book( name, hrfllp   + "_recoDescM_z",   hrfllpstr   + " z-pos [mm]",   100, -300, 300,
							  hrfllpstr + " reconstructed descendant mass [GeV]",    100, 0, 21 ) );
	  h_recofllpdvtx_fracRecoDesc_r .push_back( book( name, hrfllp   + "_fracRecoDesc_r",  hrfllpstr   + " r-pos [mm]", 100,    0, 300,
							  "fraction " + hrfllpstr + " reconstructed descendants",100, 0,  1 ) );
	  h_recofllpdvtx_fracRecoDesc_z .push_back( book( name, hrfllp   + "_fracRecoDesc_z",  hrfllpstr   + " z-pos [mm]", 100, -300, 300,
							  "fraction " + hrfllpstr + " reconstructed descendants",100, 0,  1 ) );
	  h_recofllpdvtx_fracRecoDescM_r.push_back( book( name, hrfllp   + "_fracRecoDescM_r", hrfllpstr   + " r-pos [mm]", 100,    0, 300,
							  hrfllpstr + " reconstructed descendant mass fraction", 100, 0,  1 ) );
	  h_recofllpdvtx_fracRecoDescM_z.push_back( book( name, hrfllp   + "_fracRecoDescM_z", hrfllpstr   + " z-pos [mm]", 100, -300, 300,
							  hrfllpstr + " reconstructed descendant mass fraction", 100, 0,  1 ) );
	  // loop over truth-matched signal reco vertex types
	  std::vector<TH2F*> h_recofllpdv_nVtxDesc_r;
	  std::vector<TH2F*> h_recofllpdv_nVtxDesc_z;
	  std::vector<TH2F*> h_recofllpdv_vtxDescM_r;
	  std::vector<TH2F*> h_recofllpdv_vtxDescM_z;
	  std::vector<TH2F*> h_recofllpdv_fracVtxDesc_r;
	  std::vector<TH2F*> h_recofllpdv_fracVtxDesc_z;
	  std::vector<TH2F*> h_recofllpdv_fracVtxDescM_r;
	  std::vector<TH2F*> h_recofllpdv_fracVtxDescM_z;
	  for ( size_t k = 0; k != hSgnlDV.size() + 1; ++k ) {
	    std::string hsvtmp     = "";
	    std::string hsvtmp_low = "";
	    std::string hsvtmp_str = "";
	    if ( k != 0 ) {
	      hsvtmp     = hSgnlDVstr[k-1]; hsvtmp.pop_back();
	      hsvtmp_low = hsvtmp; hsvtmp_low[0] = tolower(hsvtmp_low[0]);
	      hsvtmp_str = " " + hsvtmp_low;
	    }
	    std::string hsv_desc = "";
	    if ( hsvtmp.empty() ) hsv_desc = "vtxDesc";
	    else                  hsv_desc = "VtxDesc";
	    h_recofllpdv_nVtxDesc_r    .push_back( book( name, hrfllp + "_n" + hsvtmp + hsv_desc + "_r", hrfllpstr + " r-pos [mm]",     100,   0, 300,
							 "n " + hrfllpstr + hsvtmp_str + " vertexed descendants",        20, 0, 20 ) );
	    h_recofllpdv_nVtxDesc_z    .push_back( book( name, hrfllp + "_n" + hsvtmp + hsv_desc + "_z", hrfllpstr + " z-pos [mm]",     100,-300, 300,
							 "n " + hrfllpstr + hsvtmp_str + " vertexed descendants",        20, 0, 20 ) );
	    h_recofllpdv_vtxDescM_r    .push_back( book( name, hrfllp + "_" + hsvtmp_low + hsv_desc + "M_r", hrfllpstr + " r-pos [mm]", 100,   0, 300,
							 hrfllpstr + hsvtmp_str + " vertexed descendant mass [GeV]",    100, 0, 21 ) );
	    h_recofllpdv_vtxDescM_z    .push_back( book( name, hrfllp + "_" + hsvtmp_low + hsv_desc + "M_z", hrfllpstr + " z-pos [mm]", 100,-300, 300,
							 hrfllpstr + hsvtmp_str + " vertexed descendant mass [GeV]",    100, 0, 21 ) );
	    h_recofllpdv_fracVtxDesc_r .push_back( book( name, hrfllp + "_frac" + hsvtmp + hsv_desc + "_r",  hrfllpstr + " r-pos [mm]", 100,   0, 300,
							 "fraction " + hrfllpstr + hsvtmp_str + " vertexed descendants",100, 0,  1 ) );
	    h_recofllpdv_fracVtxDesc_z .push_back( book( name, hrfllp + "_frac" + hsvtmp + hsv_desc + "_z",  hrfllpstr + " z-pos [mm]", 100,-300, 300,
							 "fraction " + hrfllpstr + hsvtmp_str + " vertexed descendants",100, 0,  1 ) );
	    h_recofllpdv_fracVtxDescM_r.push_back( book( name, hrfllp + "_frac" + hsvtmp + hsv_desc + "M_r", hrfllpstr + " r-pos [mm]", 100,   0, 300,
							 hrfllpstr + hsvtmp_str + " vertexed descendant mass fraction", 100, 0,  1 ) );
	    h_recofllpdv_fracVtxDescM_z.push_back( book( name, hrfllp + "_frac" + hsvtmp + hsv_desc + "M_z", hrfllpstr + " z-pos [mm]", 100,-300, 300,
							 hrfllpstr + hsvtmp_str + " vertexed descendant mass fraction", 100, 0,  1 ) );
	  }
	  h_recofllpdvtx_nVtxDesc_r    .push_back( h_recofllpdv_nVtxDesc_r     );
	  h_recofllpdvtx_nVtxDesc_z    .push_back( h_recofllpdv_nVtxDesc_z     );
	  h_recofllpdvtx_vtxDescM_r    .push_back( h_recofllpdv_vtxDescM_r     );
	  h_recofllpdvtx_vtxDescM_z    .push_back( h_recofllpdv_vtxDescM_z     );
	  h_recofllpdvtx_fracVtxDesc_r .push_back( h_recofllpdv_fracVtxDesc_r  );
	  h_recofllpdvtx_fracVtxDesc_z .push_back( h_recofllpdv_fracVtxDesc_z  );
	  h_recofllpdvtx_fracVtxDescM_r.push_back( h_recofllpdv_fracVtxDescM_r );
	  h_recofllpdvtx_fracVtxDescM_z.push_back( h_recofllpdv_fracVtxDescM_z );
	  
	  h_reco2fllpdvtx_x         .push_back( book( name, hr2fllp + "_x",         hr2fllpstr + " x-pos [mm]",             100,  -300,  300 ) );
	  h_reco2fllpdvtx_y         .push_back( book( name, hr2fllp + "_y",         hr2fllpstr + " y-pos [mm]",             100,  -300,  300 ) );
	  h_reco2fllpdvtx_z         .push_back( book( name, hr2fllp + "_z",         hr2fllpstr + " z-pos [mm]",             100,  -300,  300 ) );
	  h_reco2fllpdvtx_r         .push_back( book( name, hr2fllp + "_r",         hr2fllpstr + " r-pos [mm]",             100,     0,  300 ) );
	  h_reco2fllpdvtx_pt        .push_back( book( name, hr2fllp + "_pt",        hr2fllpstr + " p_{T} [GeV]",            100,     0,  500 ) );
	  h_reco2fllpdvtx_eta       .push_back( book( name, hr2fllp + "_eta",       hr2fllpstr + " eta",                    100,    -5,    5 ) );
	  h_reco2fllpdvtx_phi       .push_back( book( name, hr2fllp + "_phi",       hr2fllpstr + " phi",                    100,  -3.5,  3.5 ) );
	  h_reco2fllpdvtx_avgMu     .push_back( book( name, hr2fllp + "_avgMu",     hr2fllpstr + " average pp interactions", 90,     0,   90 ) );
	  h_reco2fllpdvtx_descM     .push_back( book( name, hr2fllp + "_descM",     hr2fllpstr + " descendant mass [GeV]",  100,     0,   21 ) );
	  h_reco2fllpdvtx_nDesc     .push_back( book( name, hr2fllp + "_nDesc",     "n "+hr2fllpstr+" descendants",              20, 0,   20 ) );
	  h_reco2fllpdvtx_nRecoDesc .push_back( book( name, hr2fllp + "_nRecoDesc", "n "+hr2fllpstr+" reconstructed descendants",20, 0,   20 ) );
	  h_reco2fllpdvtx_nSelDesc  .push_back( book( name, hr2fllp + "_nSelDesc",  "n "+hr2fllpstr+" selected descendants",     20, 0,   20 ) );
	  h_slctfllpdvtx_x          .push_back( book( name, hsfllp  + "_x",         hsfllpstr  + " x-pos [mm]",             100,  -300,  300 ) );
	  h_slctfllpdvtx_y          .push_back( book( name, hsfllp  + "_y",         hsfllpstr  + " y-pos [mm]",             100,  -300,  300 ) );
	  h_slctfllpdvtx_z          .push_back( book( name, hsfllp  + "_z",         hsfllpstr  + " z-pos [mm]",             100,  -300,  300 ) );
	  h_slctfllpdvtx_r          .push_back( book( name, hsfllp  + "_r",         hsfllpstr  + " r-pos [mm]",             100,     0,  300 ) );
	  h_slctfllpdvtx_pt         .push_back( book( name, hsfllp  + "_pt",        hsfllpstr  + " p_{T} [GeV]",            100,     0,  500 ) );
	  h_slctfllpdvtx_eta        .push_back( book( name, hsfllp  + "_eta",       hsfllpstr  + " eta",                    100,    -5,    5 ) );
	  h_slctfllpdvtx_phi        .push_back( book( name, hsfllp  + "_phi",       hsfllpstr  + " phi",                    100,  -3.5,  3.5 ) );
	  h_slctfllpdvtx_avgMu      .push_back( book( name, hsfllp  + "_avgMu",     hsfllpstr  + " average pp interactions", 90,     0,   90 ) );
	  h_slctfllpdvtx_descM      .push_back( book( name, hsfllp  + "_descM",     hsfllpstr  + " descendant mass [GeV]",  100,     0,   21 ) );
	  h_slctfllpdvtx_nDesc      .push_back( book( name, hsfllp  + "_nDesc",     "n "+hsfllpstr+" descendants",               20, 0,   20 ) );
	  h_slctfllpdvtx_nRecoDesc  .push_back( book( name, hsfllp  + "_nRecoDesc", "n "+hsfllpstr+" reconstructed descendants", 20, 0,   20 ) );
	  h_slctfllpdvtx_nSelDesc   .push_back( book( name, hsfllp  + "_nSelDesc",  "n "+hsfllpstr+" selected descendants",      20, 0,   20 ) );

	  // loop over truth-matched signal reco vertex types
	  std::vector<TH1F*> h_smatchllpdv_score;
	  std::vector<TH1F*> h_smatchllpdv_x;
	  std::vector<TH1F*> h_smatchllpdv_y;
	  std::vector<TH1F*> h_smatchllpdv_z;
	  std::vector<TH1F*> h_smatchllpdv_r;
	  std::vector<TH1F*> h_smatchllpdv_pt;
	  std::vector<TH1F*> h_smatchllpdv_eta;
	  std::vector<TH1F*> h_smatchllpdv_phi;
	  std::vector<TH1F*> h_smatchllpdv_avgMu;
	  std::vector<TH1F*> h_smatchllpdv_descM;
	  std::vector<TH1F*> h_smatchllpdv_nDesc;
	  std::vector<TH1F*> h_smatchllpdv_nRecoDesc;
	  std::vector<TH1F*> h_smatchllpdv_nSelDesc;
	  std::vector<TH1F*> h_smatchllpdv_resid_x;
	  std::vector<TH1F*> h_smatchllpdv_resid_y;
	  std::vector<TH1F*> h_smatchllpdv_resid_z;
	  std::vector<TH1F*> h_smatchllpdv_resid_r;
	  std::vector<TH1F*> h_smatchllpdv_resid_rphi;
	  std::vector<TH2F*> h_smatchllpdv_resid_z_r;
	  std::vector<TH2F*> h_smatchllpdv_resid_z_z;
	  std::vector<TH2F*> h_smatchllpdv_resid_z_ntrk;
	  std::vector<TH2F*> h_smatchllpdv_resid_z_nseltrk;
	  std::vector<TH2F*> h_smatchllpdv_resid_r_r;
	  std::vector<TH2F*> h_smatchllpdv_resid_r_z;
	  std::vector<TH2F*> h_smatchllpdv_resid_r_ntrk;
	  std::vector<TH2F*> h_smatchllpdv_resid_r_nseltrk;
	  std::vector<TH2F*> h_smatchllpdv_resid_rphi_r;
	  std::vector<TH2F*> h_smatchllpdv_resid_rphi_z;
	  std::vector<TH2F*> h_smatchllpdv_resid_rphi_ntrk;
	  std::vector<TH2F*> h_smatchllpdv_resid_rphi_nseltrk;
	  for ( size_t k = 0; k != hSgnlDV.size(); ++k ) {
	    std::string hsmtmp    = hSgnlDVstr [k]; hsmtmp.pop_back(); hsmtmp[0] = tolower(hsmtmp[0]); // keep capitalized?
	    std::string hsmllp    = hSgnlDV    [k] + "RecoMatch" + hLLP[i] + "DecayVtx"; hsmllp[0] = tolower(hsmllp[0]);
	    std::string hsmllpstr = hsmtmp + "-reco-matched " + hllpstr;
	    h_smatchllpdv_score     .push_back( book( name, hsmllp  + "_score",     hsmllpstr  + " match score",            100,     0,    1 ) );
	    h_smatchllpdv_x         .push_back( book( name, hsmllp  + "_x",         hsmllpstr  + " x-pos [mm]",             100,  -300,  300 ) );
	    h_smatchllpdv_y         .push_back( book( name, hsmllp  + "_y",         hsmllpstr  + " y-pos [mm]",             100,  -300,  300 ) );
	    h_smatchllpdv_z         .push_back( book( name, hsmllp  + "_z",         hsmllpstr  + " z-pos [mm]",             100,  -300,  300 ) );
	    h_smatchllpdv_r         .push_back( book( name, hsmllp  + "_r",         hsmllpstr  + " r-pos [mm]",             100,     0,  300 ) );
	    h_smatchllpdv_pt        .push_back( book( name, hsmllp  + "_pt",        hsmllpstr  + " p_{T} [GeV]",            100,     0,  500 ) );
	    h_smatchllpdv_eta       .push_back( book( name, hsmllp  + "_eta",       hsmllpstr  + " eta",                    100,    -5,    5 ) );
	    h_smatchllpdv_phi       .push_back( book( name, hsmllp  + "_phi",       hsmllpstr  + " phi",                    100,  -3.5,  3.5 ) );
	    h_smatchllpdv_avgMu     .push_back( book( name, hsmllp  + "_avgMu",     hsmllpstr  + " average pp interactions", 90,     0,   90 ) );
	    h_smatchllpdv_descM     .push_back( book( name, hsmllp  + "_descM",     hsmllpstr  + " descendant mass [GeV]",  100,     0,   21 ) );
	    h_smatchllpdv_nDesc     .push_back( book( name, hsmllp  + "_nDesc",     "n "+hsfllpstr+" descendants",               20, 0,   20 ) );
	    h_smatchllpdv_nRecoDesc .push_back( book( name, hsmllp  + "_nRecoDesc", "n "+hsfllpstr+" reconstructed descendants", 20, 0,   20 ) );
	    h_smatchllpdv_nSelDesc  .push_back( book( name, hsmllp  + "_nSelDesc",  "n "+hsfllpstr+" selected descendants",      20, 0,   20 ) );
	    h_smatchllpdv_resid_x   .push_back( book( name, hsmllp  + "_resid_x",   hsmllpstr  + " residual x-pos [mm]",    100,   -10,   10 ) );
	    h_smatchllpdv_resid_y   .push_back( book( name, hsmllp  + "_resid_y",   hsmllpstr  + " residual y-pos [mm]",    100,   -10,   10 ) );
	    h_smatchllpdv_resid_z   .push_back( book( name, hsmllp  + "_resid_z",   hsmllpstr  + " residual z-pos [mm]",    100,   -10,   10 ) );
	    h_smatchllpdv_resid_r   .push_back( book( name, hsmllp  + "_resid_r",   hsmllpstr  + " residual r-pos [mm]",    100,   -10,   10 ) );
	    h_smatchllpdv_resid_rphi.push_back( book( name, hsmllp  + "_resid_rphi",hsmllpstr  + " r times residual phi-pos [mm]",100,-10,10 ) );
	    h_smatchllpdv_resid_z_r
	      .push_back( book( name, hsmllp + "_resid_z_r",          hsmllpstr + " r-pos [mm]",       100,    0, 300,
				hsmllpstr + " residual z-pos [mm]",            100, -10, 10 ) );
	    h_smatchllpdv_resid_z_z
	      .push_back( book( name, hsmllp + "_resid_z_z",          hsmllpstr + " z-pos [mm]",       100, -300, 300,
				hsmllpstr + " residual z-pos [mm]",           100, -10, 10 ) );
	    h_smatchllpdv_resid_z_ntrk
	      .push_back( book( name, hsmllp + "_resid_z_ntrk",       hsmllpstr + " n tracks",          20,    0,  20,
				hsmllpstr + " residual z-pos [mm]",           100, -10, 10 ) );
	    h_smatchllpdv_resid_z_nseltrk
	      .push_back( book( name, hsmllp + "_resid_z_nseltrk",    hsmllpstr + " n selected tracks", 20,    0,  20,
				hsmllpstr + " residual z-pos [mm]",           100, -10, 10 ) );
	    h_smatchllpdv_resid_r_r
	      .push_back( book( name, hsmllp + "_resid_r_r",          hsmllpstr + " r-pos [mm]",       100,    0, 300,
				hsmllpstr + " residual r-pos [mm]",           100, -10, 10 ) );
	    h_smatchllpdv_resid_r_z
	      .push_back( book( name, hsmllp + "_resid_r_z",          hsmllpstr + " z-pos [mm]",       100, -300, 300,
				hsmllpstr + " residual r-pos [mm]",           100, -10, 10 ) );
	    h_smatchllpdv_resid_r_ntrk
	      .push_back( book( name, hsmllp + "_resid_r_ntrk",       hsmllpstr + " n tracks",          20,    0,  20,
				hsmllpstr + " residual r-pos [mm]",           100, -10, 10 ) );
	    h_smatchllpdv_resid_r_nseltrk
	      .push_back( book( name, hsmllp + "_resid_r_nseltrk",    hsmllpstr + " n selected tracks", 20,    0,  20,
				hsmllpstr + " residual r-pos [mm]",           100, -10, 10 ) );
	    h_smatchllpdv_resid_rphi_r
	      .push_back( book( name, hsmllp + "_resid_rphi_r",       hsmllpstr + " r-pos [mm]",       100,    0, 300,
				hsmllpstr + " r times residual phi-pos [mm]", 100, -10, 10 ) );
	    h_smatchllpdv_resid_rphi_z
	      .push_back( book( name, hsmllp + "_resid_rphi_z",       hsmllpstr + " z-pos [mm]",       100, -300, 300,
				hsmllpstr + " r times residual phi-pos [mm]", 100, -10, 10 ) );
	    h_smatchllpdv_resid_rphi_ntrk
	      .push_back( book( name, hsmllp + "_resid_rphi_ntrk",    hsmllpstr + " n tracks",          20,    0,  20,
				hsmllpstr + " r times residual phi-pos [mm]", 100, -10, 10 ) );
	    h_smatchllpdv_resid_rphi_nseltrk
	      .push_back( book( name, hsmllp + "_resid_rphi_nseltrk", hsmllpstr + " n selected tracks", 20,    0,  20,
				hsmllpstr + " r times residual phi-pos [mm]", 100, -10, 10 ) );
	  }
	  h_smatchllpdvtx_score              .push_back( h_smatchllpdv_score              );
	  h_smatchllpdvtx_x                  .push_back( h_smatchllpdv_x                  );
	  h_smatchllpdvtx_y                  .push_back( h_smatchllpdv_y                  );
	  h_smatchllpdvtx_z                  .push_back( h_smatchllpdv_z                  );
	  h_smatchllpdvtx_r                  .push_back( h_smatchllpdv_r                  );
	  h_smatchllpdvtx_pt                 .push_back( h_smatchllpdv_pt                 );
	  h_smatchllpdvtx_eta                .push_back( h_smatchllpdv_eta                );
	  h_smatchllpdvtx_phi                .push_back( h_smatchllpdv_phi                );
	  h_smatchllpdvtx_avgMu              .push_back( h_smatchllpdv_avgMu              );
	  h_smatchllpdvtx_descM              .push_back( h_smatchllpdv_descM              );
	  h_smatchllpdvtx_nDesc              .push_back( h_smatchllpdv_nDesc              );
	  h_smatchllpdvtx_nRecoDesc          .push_back( h_smatchllpdv_nRecoDesc          );
	  h_smatchllpdvtx_nSelDesc           .push_back( h_smatchllpdv_nSelDesc           );
	  h_smatchllpdvtx_resid_x            .push_back( h_smatchllpdv_resid_x            );
	  h_smatchllpdvtx_resid_y            .push_back( h_smatchllpdv_resid_y            );
	  h_smatchllpdvtx_resid_z            .push_back( h_smatchllpdv_resid_z            );
	  h_smatchllpdvtx_resid_r            .push_back( h_smatchllpdv_resid_r            );
	  h_smatchllpdvtx_resid_rphi         .push_back( h_smatchllpdv_resid_rphi         );
	  h_smatchllpdvtx_resid_z_r          .push_back( h_smatchllpdv_resid_z_r          );
	  h_smatchllpdvtx_resid_z_z          .push_back( h_smatchllpdv_resid_z_z          );
	  h_smatchllpdvtx_resid_z_ntrk       .push_back( h_smatchllpdv_resid_z_ntrk       );
	  h_smatchllpdvtx_resid_z_nseltrk    .push_back( h_smatchllpdv_resid_z_nseltrk    );
	  h_smatchllpdvtx_resid_r_r          .push_back( h_smatchllpdv_resid_r_r          );
	  h_smatchllpdvtx_resid_r_z          .push_back( h_smatchllpdv_resid_r_z          );
	  h_smatchllpdvtx_resid_r_ntrk       .push_back( h_smatchllpdv_resid_r_ntrk       );
	  h_smatchllpdvtx_resid_r_nseltrk    .push_back( h_smatchllpdv_resid_r_nseltrk    );
	  h_smatchllpdvtx_resid_rphi_r       .push_back( h_smatchllpdv_resid_rphi_r       );
	  h_smatchllpdvtx_resid_rphi_z       .push_back( h_smatchllpdv_resid_rphi_z       );
	  h_smatchllpdvtx_resid_rphi_ntrk    .push_back( h_smatchllpdv_resid_rphi_ntrk    );
	  h_smatchllpdvtx_resid_rphi_nseltrk .push_back( h_smatchllpdv_resid_rphi_nseltrk );
	  
	  h_llpdvtx_accept_x
	    .push_back( book( name, hllp + "_accept_x",             hllpstr    + " x-pos [mm]",                 100,  -600,  600 ) );
	  h_llpdvtx_accept_y
	    .push_back( book( name, hllp + "_accept_y",             hllpstr    + " y-pos [mm]",                 100,  -600,  600 ) );
	  h_llpdvtx_accept_z
	    .push_back( book( name, hllp + "_accept_z",             hllpstr    + " z-pos [mm]",                 100, -2500, 2500 ) );
	  h_llpdvtx_accept_r
	    .push_back( book( name, hllp + "_accept_r",             hllpstr    + " r-pos [mm]",                 100,     0,  600 ) );
	  h_llpdvtx_accept_pt
	    .push_back( book( name, hllp + "_accept_pt",            hllpstr    + " p_{T} [GeV]",                100,     0,  500 ) );
	  h_llpdvtx_accept_eta
	    .push_back( book( name, hllp + "_accept_eta",           hllpstr    + " eta",                        100,    -5,    5 ) );
	  h_llpdvtx_accept_phi
	    .push_back( book( name, hllp + "_accept_phi",           hllpstr    + " phi",                        100,  -3.5,  3.5 ) );
	  h_llpdvtx_accept_avgMu
	    .push_back( book( name, hllp + "_accept_avgMu",         hllpstr    + " average pp interactions",     90,     0,   90 ) );
	  h_llpdvtx_accept_descM
	    .push_back( book( name, hllp + "_accept_descM",         hllpstr    + " descendant mass [GeV]",      100,     0,   21 ) );
	  h_llpdvtx_accept_nDesc
	    .push_back( book( name, hllp + "_accept_nDesc",         "n " +hllpstr+ " descendants",               20,     0,   20 ) );
	  h_llpdvtx_accept_nRecoDesc
	    .push_back( book( name, hllp + "_accept_nRecoDesc",     "n " +hllpstr+ " reconstructed descendants", 20,     0,   20 ) );
	  h_llpdvtx_accept_nSelDesc
	    .push_back( book( name, hllp + "_accept_nSelDesc",      "n " +hllpstr+ " selected descendants",      20,     0,   20 ) );
	  h_llpdvtx_recoEff_x
	    .push_back( book( name, hllp + "_recoEff_x",            hllpstr + " x-pos [mm]",                    100,  -600,  600 ) );
	  h_llpdvtx_recoEff_y
	    .push_back( book( name, hllp + "_recoEff_y",            hllpstr + " y-pos [mm]",                    100,  -600,  600 ) );
	  h_llpdvtx_recoEff_z
	    .push_back( book( name, hllp + "_recoEff_z",            hllpstr + " z-pos [mm]",                    100, -2500, 2500 ) );
	  h_llpdvtx_recoEff_r
	    .push_back( book( name, hllp + "_recoEff_r",            hllpstr + " r-pos [mm]",                    100,     0,  600 ) );
	  h_llpdvtx_recoEff_pt
	    .push_back( book( name, hllp + "_recoEff_pt",           hllpstr + " p_{T} [GeV]",                   100,     0,  500 ) );
	  h_llpdvtx_recoEff_eta
	    .push_back( book( name, hllp + "_recoEff_eta",          hllpstr + " eta",                           100,    -5,    5 ) );
	  h_llpdvtx_recoEff_phi
	    .push_back( book( name, hllp + "_recoEff_phi",          hllpstr + " phi",                           100,  -3.5,  3.5 ) );
	  h_llpdvtx_recoEff_avgMu
	    .push_back( book( name, hllp + "_recoEff_avgMu",        hllpstr + " average pp interactions",        90,     0,   90 ) );
	  h_llpdvtx_recoEff_descM
	    .push_back( book( name, hllp + "_recoEff_descM",        hllpstr + " descendant mass [GeV]",         100,     0,   21 ) );
	  h_llpdvtx_recoEff_nDesc
	    .push_back( book( name, hllp + "_recoEff_nDesc",        "n " +hllpstr+ " descendants",               20,     0,   20 ) );
	  h_llpdvtx_recoEff_nRecoDesc
	    .push_back( book( name, hllp + "_recoEff_nRecoDesc",    "n " +hllpstr+ " reconstructed descendants", 20,     0,   20 ) );
	  h_llpdvtx_recoEff_nSelDesc
	    .push_back( book( name, hllp + "_recoEff_nSelDesc",     "n " +hllpstr+ " selected descendants",      20,     0,   20 ) );
	  h_llpdvtx_algEff_x
	    .push_back( book( name, hllp + "_algEff_x",             hllpstr + " x-pos [mm]",                    100,  -600,  600 ) );
	  h_llpdvtx_algEff_y
	    .push_back( book( name, hllp + "_algEff_y",             hllpstr + " y-pos [mm]",                    100,  -600,  600 ) );
	  h_llpdvtx_algEff_z
	    .push_back( book( name, hllp + "_algEff_z",             hllpstr + " z-pos [mm]",                    100, -2500, 2500 ) );
	  h_llpdvtx_algEff_r
	    .push_back( book( name, hllp + "_algEff_r",             hllpstr + " r-pos [mm]",                    100,     0,  600 ) );
	  h_llpdvtx_algEff_pt
	    .push_back( book( name, hllp + "_algEff_pt",            hllpstr + " p_{T} [GeV]",                   100,     0,  500 ) );
	  h_llpdvtx_algEff_eta
	    .push_back( book( name, hllp + "_algEff_eta",           hllpstr + " eta",                           100,    -5,    5 ) );
	  h_llpdvtx_algEff_phi
	    .push_back( book( name, hllp + "_algEff_phi",           hllpstr + " phi",                           100,  -3.5,  3.5 ) );
	  h_llpdvtx_algEff_avgMu
	    .push_back( book( name, hllp + "_algEff_avgMu",         hllpstr + " average pp interactions",        90,     0,   90 ) );
	  h_llpdvtx_algEff_descM
	    .push_back( book( name, hllp + "_algEff_descM",         hllpstr + " descendant mass [GeV]",         100,     0,   21 ) );
	  h_llpdvtx_algEff_nDesc
	    .push_back( book( name, hllp + "_algEff_nDesc",         "n " +hllpstr+ " descendants",               20,     0,   20 ) );
	  h_llpdvtx_algEff_nRecoDesc
	    .push_back( book( name, hllp + "_algEff_nRecoDesc",     "n " +hllpstr+ " reconstructed descendants", 20,     0,   20 ) );
	  h_llpdvtx_algEff_nSelDesc
	    .push_back( book( name, hllp + "_algEff_nSelDesc",      "n " +hllpstr+ " selected descendants",      20,     0,   20 ) );
	  h_llpdvtx_coreEff_x
	    .push_back( book( name, hllp + "_coreEff_x",            hllpstr + " x-pos [mm]",                    100,  -600,  600 ) );
	  h_llpdvtx_coreEff_y
	    .push_back( book( name, hllp + "_coreEff_y",            hllpstr + " y-pos [mm]",                    100,  -600,  600 ) );
	  h_llpdvtx_coreEff_z
	    .push_back( book( name, hllp + "_coreEff_z",            hllpstr + " z-pos [mm]",                    100, -2500, 2500 ) );
	  h_llpdvtx_coreEff_r
	    .push_back( book( name, hllp + "_coreEff_r",            hllpstr + " r-pos [mm]",                    100,     0,  600 ) );
	  h_llpdvtx_coreEff_pt
	    .push_back( book( name, hllp + "_coreEff_pt",           hllpstr + " p_{T} [GeV]",                   100,     0,  500 ) );
	  h_llpdvtx_coreEff_eta
	    .push_back( book( name, hllp + "_coreEff_eta",          hllpstr + " eta",                           100,    -5,    5 ) );
	  h_llpdvtx_coreEff_phi
	    .push_back( book( name, hllp + "_coreEff_phi",          hllpstr + " phi",                           100,  -3.5,  3.5 ) );
	  h_llpdvtx_coreEff_avgMu
	    .push_back( book( name, hllp + "_coreEff_avgMu",        hllpstr + " average pp interactions",        90,     0,   90 ) );
	  h_llpdvtx_coreEff_descM
	    .push_back( book( name, hllp + "_coreEff_descM",        hllpstr + " descendant mass [GeV]",         100,     0,   21 ) );
	  h_llpdvtx_coreEff_nDesc
	    .push_back( book( name, hllp + "_coreEff_nDesc",        "n " +hllpstr+ " descendants",               20,     0,   20 ) );
	  h_llpdvtx_coreEff_nRecoDesc
	    .push_back( book( name, hllp + "_coreEff_nRecoDesc",    "n " +hllpstr+ " reconstructed descendants", 20,     0,   20 ) );
	  h_llpdvtx_coreEff_nSelDesc
	    .push_back( book( name, hllp + "_coreEff_nSelDesc",     "n " +hllpstr+ " selected descendants",      20,     0,   20 ) );
	  h_llpdvtx_seedEff_x
	    .push_back( book( name, hllp + "_seedEff_x",            hllpstr + " x-pos [mm]",                    100,  -600,  600 ) );
	  h_llpdvtx_seedEff_y
	    .push_back( book( name, hllp + "_seedEff_y",            hllpstr + " y-pos [mm]",                    100,  -600,  600 ) );
	  h_llpdvtx_seedEff_z
	    .push_back( book( name, hllp + "_seedEff_z",            hllpstr + " z-pos [mm]",                    100, -2500, 2500 ) );
	  h_llpdvtx_seedEff_r
	    .push_back( book( name, hllp + "_seedEff_r",            hllpstr + " r-pos [mm]",                    100,     0,  600 ) );
	  h_llpdvtx_seedEff_pt
	    .push_back( book( name, hllp + "_seedEff_pt",           hllpstr + " p_{T} [GeV]",                   100,     0,  500 ) );
	  h_llpdvtx_seedEff_eta
	    .push_back( book( name, hllp + "_seedEff_eta",          hllpstr + " eta",                           100,    -5,    5 ) );
	  h_llpdvtx_seedEff_phi
	    .push_back( book( name, hllp + "_seedEff_phi",          hllpstr + " phi",                           100,  -3.5,  3.5 ) );
	  h_llpdvtx_seedEff_avgMu
	    .push_back( book( name, hllp + "_seedEff_avgMu",        hllpstr + " average pp interactions",        90,     0,   90 ) );
	  h_llpdvtx_seedEff_descM
	    .push_back( book( name, hllp + "_seedEff_descM",        hllpstr + " descendant mass [GeV]",         100,     0,   21 ) );
	  h_llpdvtx_seedEff_nDesc
	    .push_back( book( name, hllp + "_seedEff_nDesc",        "n " +hllpstr+ " descendants",               20,     0,   20 ) );
	  h_llpdvtx_seedEff_nRecoDesc
	    .push_back( book( name, hllp + "_seedEff_nRecoDesc",    "n " +hllpstr+ " reconstructed descendants", 20,     0,   20 ) );
	  h_llpdvtx_seedEff_nSelDesc
	    .push_back( book( name, hllp + "_seedEff_nSelDesc",     "n " +hllpstr+ " selected descendants",      20,     0,   20 ) );
	  
	  h_llpdvtx_sgnlaccept_x
	    .push_back( book( name, hllp + "_sgnlAccept_x",         hllpstr    + " x-pos [mm]",                 100,  -300,  300 ) );
	  h_llpdvtx_sgnlaccept_y
	    .push_back( book( name, hllp + "_sgnlAccept_y",         hllpstr    + " y-pos [mm]",                 100,  -300,  300 ) );
	  h_llpdvtx_sgnlaccept_z
	    .push_back( book( name, hllp + "_sgnlAccept_z",         hllpstr    + " z-pos [mm]",                 100,  -300,  300 ) );
	  h_llpdvtx_sgnlaccept_r
	    .push_back( book( name, hllp + "_sgnlAccept_r",         hllpstr    + " r-pos [mm]",                 100,     0,  300 ) );
	  h_llpdvtx_sgnlaccept_pt
	    .push_back( book( name, hllp + "_sgnlAccept_pt",        hllpstr    + " p_{T} [GeV]",                100,     0,  500 ) );
	  h_llpdvtx_sgnlaccept_eta
	    .push_back( book( name, hllp + "_sgnlAccept_eta",       hllpstr    + " eta",                        100,    -5,    5 ) );
	  h_llpdvtx_sgnlaccept_phi
	    .push_back( book( name, hllp + "_sgnlAccept_phi",       hllpstr    + " phi",                        100,  -3.5,  3.5 ) );
	  h_llpdvtx_sgnlaccept_avgMu
	    .push_back( book( name, hllp + "_sgnlAccept_avgMu",     hllpstr    + " average pp interactions",     90,     0,   90 ) );
	  h_llpdvtx_sgnlaccept_descM
	    .push_back( book( name, hllp + "_sgnlAccept_descM",     hllpstr    + " descendant mass [GeV]",      100,     0,   21 ) );
	  h_llpdvtx_sgnlaccept_nDesc
	    .push_back( book( name, hllp + "_sgnlAccept_nDesc",     "n " +hllpstr+ " descendants",               20,     0,   20 ) );
	  h_llpdvtx_sgnlaccept_nRecoDesc
	    .push_back( book( name, hllp + "_sgnlAccept_nRecoDesc", "n " +hllpstr+ " reconstructed descendants", 20,     0,   20 ) );
	  h_llpdvtx_sgnlaccept_nSelDesc
	    .push_back( book( name, hllp + "_sgnlAccept_nSelDesc",  "n " +hllpstr+ " selected descendants",      20,     0,   20 ) );

	  // loop over truth-matched signal reco vertex types
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_x;
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_y;
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_z;
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_r;
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_pt;
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_eta;
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_phi;
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_avgMu;
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_descM;
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_nDesc;
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_nRecoDesc;
	  std::vector<TH1F*> h_llpdv_sgnlrecoEff_nSelDesc;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_x;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_y;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_z;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_r;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_pt;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_eta;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_phi;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_avgMu;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_descM;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_nDesc;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_nRecoDesc;
	  std::vector<TH1F*> h_llpdv_sgnlalgEff_nSelDesc;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_x;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_y;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_z;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_r;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_pt;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_eta;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_phi;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_avgMu;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_descM;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_nDesc;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_nRecoDesc;
	  std::vector<TH1F*> h_llpdv_sgnlcoreEff_nSelDesc;
	  for ( size_t k = 0; k != hSgnlDV.size(); ++k ) {
	    std::string hsdv = hSgnlDV[k]; hsdv[0] = tolower(hsdv[0]);
	    h_llpdv_sgnlrecoEff_x
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_x",         hllpstr + " x-pos [mm]",                100, -300, 300 ) );
	    h_llpdv_sgnlrecoEff_y
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_y",         hllpstr + " y-pos [mm]",                100, -300, 300 ) );
	    h_llpdv_sgnlrecoEff_z
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_z",         hllpstr + " z-pos [mm]",                100, -300, 300 ) );
	    h_llpdv_sgnlrecoEff_r
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_r",         hllpstr + " r-pos [mm]",                100,    0, 300 ) );
	    h_llpdv_sgnlrecoEff_pt
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_pt",        hllpstr + " p_{T} [GeV]",               100,    0, 500 ) );
	    h_llpdv_sgnlrecoEff_eta
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_eta",       hllpstr + " eta",                       100,   -5,   5 ) );
	    h_llpdv_sgnlrecoEff_phi
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_phi",       hllpstr + " phi",                       100, -3.5, 3.5 ) );
	    h_llpdv_sgnlrecoEff_avgMu
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_avgMu",     hllpstr + " average pp interactions",    90,    0,  90 ) );
	    h_llpdv_sgnlrecoEff_descM
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_descM",     hllpstr + " descendant mass [GeV]",     100,    0,  21 ) );
	    h_llpdv_sgnlrecoEff_nDesc
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_nDesc",     "n " +hllpstr+ " descendants",              20, 0,  20 ) );
	    h_llpdv_sgnlrecoEff_nRecoDesc
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_nRecoDesc", "n " +hllpstr+ " reconstructed descendants",20, 0,  20 ) );
	    h_llpdv_sgnlrecoEff_nSelDesc
	      .push_back( book( name, hllp + "_" + hsdv + "RecoEff_nSelDesc",  "n " +hllpstr+ " selected descendants",     20, 0,  20 ) );
	    h_llpdv_sgnlalgEff_x
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_x",          hllpstr + " x-pos [mm]",                100, -300, 300 ) );
	    h_llpdv_sgnlalgEff_y
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_y",          hllpstr + " y-pos [mm]",                100, -300, 300 ) );
	    h_llpdv_sgnlalgEff_z
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_z",          hllpstr + " z-pos [mm]",                100, -300, 300 ) );
	    h_llpdv_sgnlalgEff_r
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_r",          hllpstr + " r-pos [mm]",                100,    0, 300 ) );
	    h_llpdv_sgnlalgEff_pt
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_pt",         hllpstr + " p_{T} [GeV]",               100,    0, 500 ) );
	    h_llpdv_sgnlalgEff_eta
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_eta",        hllpstr + " eta",                       100,   -5,   5 ) );
	    h_llpdv_sgnlalgEff_phi
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_phi",        hllpstr + " phi",                       100, -3.5, 3.5 ) );
	    h_llpdv_sgnlalgEff_avgMu
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_avgMu",      hllpstr + " average pp interactions",    90,    0,  90 ) );
	    h_llpdv_sgnlalgEff_descM
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_descM",      hllpstr + " descendant mass [GeV]",     100,    0,  21 ) );
	    h_llpdv_sgnlalgEff_nDesc
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_nDesc",      "n " +hllpstr+ " descendants",              20, 0,  20 ) );
	    h_llpdv_sgnlalgEff_nRecoDesc
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_nRecoDesc",  "n " +hllpstr+ " reconstructed descendants",20, 0,  20 ) );
	    h_llpdv_sgnlalgEff_nSelDesc
	      .push_back( book( name, hllp + "_" + hsdv + "AlgEff_nSelDesc",   "n " +hllpstr+ " selected descendants",     20, 0,  20 ) );
	    h_llpdv_sgnlcoreEff_x
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_x",         hllpstr + " x-pos [mm]",                100, -300, 300 ) );
	    h_llpdv_sgnlcoreEff_y
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_y",         hllpstr + " y-pos [mm]",                100, -300, 300 ) );
	    h_llpdv_sgnlcoreEff_z
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_z",         hllpstr + " z-pos [mm]",                100, -300, 300 ) );
	    h_llpdv_sgnlcoreEff_r
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_r",         hllpstr + " r-pos [mm]",                100,    0, 300 ) );
	    h_llpdv_sgnlcoreEff_pt
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_pt",        hllpstr + " p_{T} [GeV]",               100,    0, 500 ) );
	    h_llpdv_sgnlcoreEff_eta
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_eta",       hllpstr + " eta",                       100,   -5,   5 ) );
	    h_llpdv_sgnlcoreEff_phi
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_phi",       hllpstr + " phi",                       100, -3.5, 3.5 ) );
	    h_llpdv_sgnlcoreEff_avgMu
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_avgMu",     hllpstr + " average pp interactions",    90,    0,  90 ) );
	    h_llpdv_sgnlcoreEff_descM
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_descM",     hllpstr + " descendant mass [GeV]",     100,    0,  21 ) );
	    h_llpdv_sgnlcoreEff_nDesc
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_nDesc",     "n " +hllpstr+ " descendants",              20, 0,  20 ) );
	    h_llpdv_sgnlcoreEff_nRecoDesc
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_nRecoDesc", "n " +hllpstr+ " reconstructed descendants",20, 0,  20 ) );
	    h_llpdv_sgnlcoreEff_nSelDesc
	      .push_back( book( name, hllp + "_" + hsdv + "CoreEff_nSelDesc",  "n " +hllpstr+ " selected descendants",     20, 0,  20 ) );
	  }
	  h_llpdvtx_sgnlrecoEff_x         .push_back( h_llpdv_sgnlrecoEff_x         );
	  h_llpdvtx_sgnlrecoEff_y         .push_back( h_llpdv_sgnlrecoEff_y         );
	  h_llpdvtx_sgnlrecoEff_z         .push_back( h_llpdv_sgnlrecoEff_z         );
	  h_llpdvtx_sgnlrecoEff_r         .push_back( h_llpdv_sgnlrecoEff_r         );
	  h_llpdvtx_sgnlrecoEff_pt        .push_back( h_llpdv_sgnlrecoEff_pt        );
	  h_llpdvtx_sgnlrecoEff_eta       .push_back( h_llpdv_sgnlrecoEff_eta       );
	  h_llpdvtx_sgnlrecoEff_phi       .push_back( h_llpdv_sgnlrecoEff_phi       );
	  h_llpdvtx_sgnlrecoEff_avgMu     .push_back( h_llpdv_sgnlrecoEff_avgMu     );
	  h_llpdvtx_sgnlrecoEff_descM     .push_back( h_llpdv_sgnlrecoEff_descM     );
	  h_llpdvtx_sgnlrecoEff_nDesc     .push_back( h_llpdv_sgnlrecoEff_nDesc     );
	  h_llpdvtx_sgnlrecoEff_nRecoDesc .push_back( h_llpdv_sgnlrecoEff_nRecoDesc );
	  h_llpdvtx_sgnlrecoEff_nSelDesc  .push_back( h_llpdv_sgnlrecoEff_nSelDesc  );
	  h_llpdvtx_sgnlalgEff_x          .push_back( h_llpdv_sgnlalgEff_x          );
	  h_llpdvtx_sgnlalgEff_y          .push_back( h_llpdv_sgnlalgEff_y          );
	  h_llpdvtx_sgnlalgEff_z          .push_back( h_llpdv_sgnlalgEff_z          );
	  h_llpdvtx_sgnlalgEff_r          .push_back( h_llpdv_sgnlalgEff_r          );
	  h_llpdvtx_sgnlalgEff_pt         .push_back( h_llpdv_sgnlalgEff_pt         );
	  h_llpdvtx_sgnlalgEff_eta        .push_back( h_llpdv_sgnlalgEff_eta        );
	  h_llpdvtx_sgnlalgEff_phi        .push_back( h_llpdv_sgnlalgEff_phi        );
	  h_llpdvtx_sgnlalgEff_avgMu      .push_back( h_llpdv_sgnlalgEff_avgMu      );
	  h_llpdvtx_sgnlalgEff_descM      .push_back( h_llpdv_sgnlalgEff_descM      );
	  h_llpdvtx_sgnlalgEff_nDesc      .push_back( h_llpdv_sgnlalgEff_nDesc      );
	  h_llpdvtx_sgnlalgEff_nRecoDesc  .push_back( h_llpdv_sgnlalgEff_nRecoDesc  );
	  h_llpdvtx_sgnlalgEff_nSelDesc   .push_back( h_llpdv_sgnlalgEff_nSelDesc   );
	  h_llpdvtx_sgnlcoreEff_x         .push_back( h_llpdv_sgnlcoreEff_x         );
	  h_llpdvtx_sgnlcoreEff_y         .push_back( h_llpdv_sgnlcoreEff_y         );
	  h_llpdvtx_sgnlcoreEff_z         .push_back( h_llpdv_sgnlcoreEff_z         );
	  h_llpdvtx_sgnlcoreEff_r         .push_back( h_llpdv_sgnlcoreEff_r         );
	  h_llpdvtx_sgnlcoreEff_pt        .push_back( h_llpdv_sgnlcoreEff_pt        );
	  h_llpdvtx_sgnlcoreEff_eta       .push_back( h_llpdv_sgnlcoreEff_eta       );
	  h_llpdvtx_sgnlcoreEff_phi       .push_back( h_llpdv_sgnlcoreEff_phi       );
	  h_llpdvtx_sgnlcoreEff_avgMu     .push_back( h_llpdv_sgnlcoreEff_avgMu     );
	  h_llpdvtx_sgnlcoreEff_descM     .push_back( h_llpdv_sgnlcoreEff_descM     );
	  h_llpdvtx_sgnlcoreEff_nDesc     .push_back( h_llpdv_sgnlcoreEff_nDesc     );
	  h_llpdvtx_sgnlcoreEff_nRecoDesc .push_back( h_llpdv_sgnlcoreEff_nRecoDesc );
	  h_llpdvtx_sgnlcoreEff_nSelDesc  .push_back( h_llpdv_sgnlcoreEff_nSelDesc  );
	  h_llpdvtx_sgnlseedEff_x
	    .push_back( book( name, hllp + "_sgnlSeedEff_x",         hllpstr + " x-pos [mm]",                100, -300, 300 ) );
	  h_llpdvtx_sgnlseedEff_y
	    .push_back( book( name, hllp + "_sgnlSeedEff_y",         hllpstr + " y-pos [mm]",                100, -300, 300 ) );
	  h_llpdvtx_sgnlseedEff_z
	    .push_back( book( name, hllp + "_sgnlSeedEff_z",         hllpstr + " z-pos [mm]",                100, -300, 300 ) );
	  h_llpdvtx_sgnlseedEff_r
	    .push_back( book( name, hllp + "_sgnlSeedEff_r",         hllpstr + " r-pos [mm]",                100,    0, 300 ) );
	  h_llpdvtx_sgnlseedEff_pt
	    .push_back( book( name, hllp + "_sgnlSeedEff_pt",        hllpstr + " p_{T} [GeV]",               100,    0, 500 ) );
	  h_llpdvtx_sgnlseedEff_eta
	    .push_back( book( name, hllp + "_sgnlSeedEff_eta",       hllpstr + " eta",                       100,   -5,   5 ) );
	  h_llpdvtx_sgnlseedEff_phi
	    .push_back( book( name, hllp + "_sgnlSeedEff_phi",       hllpstr + " phi",                       100, -3.5, 3.5 ) );
	  h_llpdvtx_sgnlseedEff_avgMu
	    .push_back( book( name, hllp + "_sgnlSeedEff_avgMu",     hllpstr + " average pp interactions",    90,    0,  90 ) );
	  h_llpdvtx_sgnlseedEff_descM
	    .push_back( book( name, hllp + "_sgnlSeedEff_descM",     hllpstr + " descendant mass [GeV]",     100,    0,  21 ) );
	  h_llpdvtx_sgnlseedEff_nDesc
	    .push_back( book( name, hllp + "_sgnlSeedEff_nDesc",     "n " +hllpstr+ " descendants",              20, 0,  20 ) );
	  h_llpdvtx_sgnlseedEff_nRecoDesc
	    .push_back( book( name, hllp + "_sgnlSeedEff_nRecoDesc", "n " +hllpstr+ " reconstructed descendants",20, 0,  20 ) );
	  h_llpdvtx_sgnlseedEff_nSelDesc
	    .push_back( book( name, hllp + "_sgnlSeedEff_nSelDesc",  "n " +hllpstr+ " selected descendants",     20, 0,  20 ) );
	} // end reco efficiency
      } // end loop over llp decay types
      
      h_LLPdVtx_n          .push_back( h_llpdvtx_n          );
      if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
	h_LLPdVtx_z          .push_back( h_llpdvtx_z          );
	h_LLPdVtx_r          .push_back( h_llpdvtx_r          );
	h_LLPdVtx_pt         .push_back( h_llpdvtx_pt         );
	h_LLPdVtx_eta        .push_back( h_llpdvtx_eta        );
	h_LLPdVtx_phi        .push_back( h_llpdvtx_phi        );
	h_LLPdVtx_mass       .push_back( h_llpdvtx_mass       );
	h_LLPdVtx_childOpAng .push_back( h_llpdvtx_childOpAng );
	h_LLPdVtx_nOutP      .push_back( h_llpdvtx_nOutP      );
	h_LLPdVtx_ndesc      .push_back( h_llpdvtx_ndesc      );
	if ( m_histoInfoSwitch->m_llpDesc ) {
	  h_LLPdVtx_descPt   .push_back( h_llpdvtx_descPt     );
	  h_LLPdVtx_descEta  .push_back( h_llpdvtx_descEta    );
	  h_LLPdVtx_descPhi  .push_back( h_llpdvtx_descPhi    );
	  h_LLPdVtx_descE    .push_back( h_llpdvtx_descE      );
	  h_LLPdVtx_descM    .push_back( h_llpdvtx_descM      );
	  h_LLPdVtx_desc_pt  .push_back( h_llpdvtx_desc_pt    );
	  h_LLPdVtx_desc_eta .push_back( h_llpdvtx_desc_eta   );
	  h_LLPdVtx_desc_phi .push_back( h_llpdvtx_desc_phi   );
	  h_LLPdVtx_desc_d0  .push_back( h_llpdvtx_desc_d0    );
	  h_LLPdVtx_desc_z0  .push_back( h_llpdvtx_desc_z0    );
	}
	if ( m_histoInfoSwitch->m_llpRecoEff || m_histoInfoSwitch->m_llpvtxRecoEff ) {
	  h_recobleLLPdVtx_x               .push_back( h_recollpdvtx_x                 );
	  h_recobleLLPdVtx_y               .push_back( h_recollpdvtx_y                 );
	  h_recobleLLPdVtx_z               .push_back( h_recollpdvtx_z                 );
	  h_recobleLLPdVtx_r               .push_back( h_recollpdvtx_r                 );
	  h_recobleLLPdVtx_pt              .push_back( h_recollpdvtx_pt                );
	  h_recobleLLPdVtx_eta             .push_back( h_recollpdvtx_eta               );
	  h_recobleLLPdVtx_phi             .push_back( h_recollpdvtx_phi               );
	  h_recobleLLPdVtx_avgMu           .push_back( h_recollpdvtx_avgMu             );
	  h_recobleLLPdVtx_descM           .push_back( h_recollpdvtx_descM             );
	  h_recobleLLPdVtx_nDesc           .push_back( h_recollpdvtx_nDesc             );
	  h_recobleLLPdVtx_nRecoDesc       .push_back( h_recollpdvtx_nRecoDesc         );
	  h_recobleLLPdVtx_nSelDesc        .push_back( h_recollpdvtx_nSelDesc          );
	  h_recobleLLPdVtx_nDesc_r         .push_back( h_recollpdvtx_nDesc_r           );
	  h_recobleLLPdVtx_nDesc_z         .push_back( h_recollpdvtx_nDesc_z           );
	  h_recobleLLPdVtx_descM_r         .push_back( h_recollpdvtx_descM_r           );
	  h_recobleLLPdVtx_descM_z         .push_back( h_recollpdvtx_descM_z           );
	  h_recobleLLPdVtx_nRecoDesc_r     .push_back( h_recollpdvtx_nRecoDesc_r       );
	  h_recobleLLPdVtx_nRecoDesc_z     .push_back( h_recollpdvtx_nRecoDesc_z       );
	  h_recobleLLPdVtx_recoDescM_r     .push_back( h_recollpdvtx_recoDescM_r       );
	  h_recobleLLPdVtx_recoDescM_z     .push_back( h_recollpdvtx_recoDescM_z       );
	  h_recobleLLPdVtx_nVtxDesc_r      .push_back( h_recollpdvtx_nVtxDesc_r        );
	  h_recobleLLPdVtx_nVtxDesc_z      .push_back( h_recollpdvtx_nVtxDesc_z        );
	  h_recobleLLPdVtx_vtxDescM_r      .push_back( h_recollpdvtx_vtxDescM_r        );
	  h_recobleLLPdVtx_vtxDescM_z      .push_back( h_recollpdvtx_vtxDescM_z        );
	  h_recobleLLPdVtx_fracRecoDesc_r  .push_back( h_recollpdvtx_fracRecoDesc_r    );
	  h_recobleLLPdVtx_fracRecoDesc_z  .push_back( h_recollpdvtx_fracRecoDesc_z    );
	  h_recobleLLPdVtx_fracRecoDescM_r .push_back( h_recollpdvtx_fracRecoDescM_r   );
	  h_recobleLLPdVtx_fracRecoDescM_z .push_back( h_recollpdvtx_fracRecoDescM_z   );
	  h_recobleLLPdVtx_fracVtxDesc_r   .push_back( h_recollpdvtx_fracVtxDesc_r     );
	  h_recobleLLPdVtx_fracVtxDesc_z   .push_back( h_recollpdvtx_fracVtxDesc_z     );
	  h_recobleLLPdVtx_fracVtxDescM_r  .push_back( h_recollpdvtx_fracVtxDescM_r    );
	  h_recobleLLPdVtx_fracVtxDescM_z  .push_back( h_recollpdvtx_fracVtxDescM_z    );
	  h_recoLLPdVtx_x                  .push_back( h_reco2llpdvtx_x                );
	  h_recoLLPdVtx_y                  .push_back( h_reco2llpdvtx_y                );
	  h_recoLLPdVtx_z                  .push_back( h_reco2llpdvtx_z                );
	  h_recoLLPdVtx_r                  .push_back( h_reco2llpdvtx_r                );
	  h_recoLLPdVtx_pt                 .push_back( h_reco2llpdvtx_pt               );
	  h_recoLLPdVtx_eta                .push_back( h_reco2llpdvtx_eta              );
	  h_recoLLPdVtx_phi                .push_back( h_reco2llpdvtx_phi              );
	  h_recoLLPdVtx_avgMu              .push_back( h_reco2llpdvtx_avgMu            );
	  h_recoLLPdVtx_descM              .push_back( h_reco2llpdvtx_descM            );
	  h_recoLLPdVtx_nDesc              .push_back( h_reco2llpdvtx_nDesc            );
	  h_recoLLPdVtx_nRecoDesc          .push_back( h_reco2llpdvtx_nRecoDesc        );
	  h_recoLLPdVtx_nSelDesc           .push_back( h_reco2llpdvtx_nSelDesc         );
	  h_selLLPdVtx_x                   .push_back( h_slctllpdvtx_x                 );
	  h_selLLPdVtx_y                   .push_back( h_slctllpdvtx_y                 );
	  h_selLLPdVtx_z                   .push_back( h_slctllpdvtx_z                 );
	  h_selLLPdVtx_r                   .push_back( h_slctllpdvtx_r                 );
	  h_selLLPdVtx_pt                  .push_back( h_slctllpdvtx_pt                ); 
	  h_selLLPdVtx_eta                 .push_back( h_slctllpdvtx_eta               );
	  h_selLLPdVtx_phi                 .push_back( h_slctllpdvtx_phi               );
	  h_selLLPdVtx_avgMu               .push_back( h_slctllpdvtx_avgMu             );
	  h_selLLPdVtx_descM               .push_back( h_slctllpdvtx_descM             );
	  h_selLLPdVtx_nDesc               .push_back( h_slctllpdvtx_nDesc             );
	  h_selLLPdVtx_nRecoDesc           .push_back( h_slctllpdvtx_nRecoDesc         );
	  h_selLLPdVtx_nSelDesc            .push_back( h_slctllpdvtx_nSelDesc          );
	  h_recoMatchLLPdVtx_score         .push_back( h_matchllpdvtx_score            );
	  h_recoMatchLLPdVtx_x             .push_back( h_matchllpdvtx_x                );
	  h_recoMatchLLPdVtx_y             .push_back( h_matchllpdvtx_y                );
	  h_recoMatchLLPdVtx_z             .push_back( h_matchllpdvtx_z                );
	  h_recoMatchLLPdVtx_r             .push_back( h_matchllpdvtx_r                );
	  h_recoMatchLLPdVtx_pt            .push_back( h_matchllpdvtx_pt               );
	  h_recoMatchLLPdVtx_eta           .push_back( h_matchllpdvtx_eta              );
	  h_recoMatchLLPdVtx_phi           .push_back( h_matchllpdvtx_phi              );
	  h_recoMatchLLPdVtx_avgMu         .push_back( h_matchllpdvtx_avgMu            );
	  h_recoMatchLLPdVtx_descM         .push_back( h_matchllpdvtx_descM            );
	  h_recoMatchLLPdVtx_nDesc         .push_back( h_matchllpdvtx_nDesc            );
	  h_recoMatchLLPdVtx_nRecoDesc     .push_back( h_matchllpdvtx_nRecoDesc        );
	  h_recoMatchLLPdVtx_nSelDesc      .push_back( h_matchllpdvtx_nSelDesc         );
	  h_recoMatchLLPdVtx_resid_x       .push_back( h_matchllpdvtx_resid_x          );
	  h_recoMatchLLPdVtx_resid_y       .push_back( h_matchllpdvtx_resid_y          );
	  h_recoMatchLLPdVtx_resid_z       .push_back( h_matchllpdvtx_resid_z          );
	  h_recoMatchLLPdVtx_resid_r       .push_back( h_matchllpdvtx_resid_r          );
	  h_recoMatchLLPdVtx_resid_rphi    .push_back( h_matchllpdvtx_resid_rphi       );
	  h_recoMatchLLPdVtx_resid_z_r          .push_back( h_matchllpdvtx_resid_z_r          );
	  h_recoMatchLLPdVtx_resid_z_z          .push_back( h_matchllpdvtx_resid_z_z          );
	  h_recoMatchLLPdVtx_resid_z_ntrk       .push_back( h_matchllpdvtx_resid_z_ntrk       );
	  h_recoMatchLLPdVtx_resid_z_nseltrk    .push_back( h_matchllpdvtx_resid_z_nseltrk    );
	  h_recoMatchLLPdVtx_resid_r_r          .push_back( h_matchllpdvtx_resid_r_r          );
	  h_recoMatchLLPdVtx_resid_r_z          .push_back( h_matchllpdvtx_resid_r_z          );
	  h_recoMatchLLPdVtx_resid_r_ntrk       .push_back( h_matchllpdvtx_resid_r_ntrk       );
	  h_recoMatchLLPdVtx_resid_r_nseltrk    .push_back( h_matchllpdvtx_resid_r_nseltrk    );
	  h_recoMatchLLPdVtx_resid_rphi_r       .push_back( h_matchllpdvtx_resid_rphi_r       );
	  h_recoMatchLLPdVtx_resid_rphi_z       .push_back( h_matchllpdvtx_resid_rphi_z       );
	  h_recoMatchLLPdVtx_resid_rphi_ntrk    .push_back( h_matchllpdvtx_resid_rphi_ntrk    );
	  h_recoMatchLLPdVtx_resid_rphi_nseltrk .push_back( h_matchllpdvtx_resid_rphi_nseltrk );
	  h_fiducLLPdVtx_x                 .push_back( h_recofllpdvtx_x                );
	  h_fiducLLPdVtx_y                 .push_back( h_recofllpdvtx_y                );
	  h_fiducLLPdVtx_z                 .push_back( h_recofllpdvtx_z                );
	  h_fiducLLPdVtx_r                 .push_back( h_recofllpdvtx_r                );
	  h_fiducLLPdVtx_pt                .push_back( h_recofllpdvtx_pt               );
	  h_fiducLLPdVtx_eta               .push_back( h_recofllpdvtx_eta              );
	  h_fiducLLPdVtx_phi               .push_back( h_recofllpdvtx_phi              );
	  h_fiducLLPdVtx_avgMu             .push_back( h_recofllpdvtx_avgMu            );
	  h_fiducLLPdVtx_descM             .push_back( h_recofllpdvtx_descM            );
	  h_fiducLLPdVtx_nDesc             .push_back( h_recofllpdvtx_nDesc            );
	  h_fiducLLPdVtx_nRecoDesc         .push_back( h_recofllpdvtx_nRecoDesc        );
	  h_fiducLLPdVtx_nSelDesc          .push_back( h_recofllpdvtx_nSelDesc         );
	  h_fiducLLPdVtx_nDesc_r           .push_back( h_recofllpdvtx_nDesc_r          );
	  h_fiducLLPdVtx_nDesc_z           .push_back( h_recofllpdvtx_nDesc_z          );
	  h_fiducLLPdVtx_descM_r           .push_back( h_recofllpdvtx_descM_r          );
	  h_fiducLLPdVtx_descM_z           .push_back( h_recofllpdvtx_descM_z          );
	  h_fiducLLPdVtx_nRecoDesc_r       .push_back( h_recofllpdvtx_nRecoDesc_r      );
	  h_fiducLLPdVtx_nRecoDesc_z       .push_back( h_recofllpdvtx_nRecoDesc_z      );
	  h_fiducLLPdVtx_recoDescM_r       .push_back( h_recofllpdvtx_recoDescM_r      );
	  h_fiducLLPdVtx_recoDescM_z       .push_back( h_recofllpdvtx_recoDescM_z      );
	  h_fiducLLPdVtx_nVtxDesc_r        .push_back( h_recofllpdvtx_nVtxDesc_r       );
	  h_fiducLLPdVtx_nVtxDesc_z        .push_back( h_recofllpdvtx_nVtxDesc_z       );
	  h_fiducLLPdVtx_vtxDescM_r        .push_back( h_recofllpdvtx_vtxDescM_r       );
	  h_fiducLLPdVtx_vtxDescM_z        .push_back( h_recofllpdvtx_vtxDescM_z       );
	  h_fiducLLPdVtx_fracRecoDesc_r    .push_back( h_recofllpdvtx_fracRecoDesc_r   );
	  h_fiducLLPdVtx_fracRecoDesc_z    .push_back( h_recofllpdvtx_fracRecoDesc_z   );
	  h_fiducLLPdVtx_fracRecoDescM_r   .push_back( h_recofllpdvtx_fracRecoDescM_r  );
	  h_fiducLLPdVtx_fracRecoDescM_z   .push_back( h_recofllpdvtx_fracRecoDescM_z  );
	  h_fiducLLPdVtx_fracVtxDesc_r     .push_back( h_recofllpdvtx_fracVtxDesc_r    );
	  h_fiducLLPdVtx_fracVtxDesc_z     .push_back( h_recofllpdvtx_fracVtxDesc_z    );
	  h_fiducLLPdVtx_fracVtxDescM_r    .push_back( h_recofllpdvtx_fracVtxDescM_r   );
	  h_fiducLLPdVtx_fracVtxDescM_z    .push_back( h_recofllpdvtx_fracVtxDescM_z   );
	  h_recoFiducLLPdVtx_x             .push_back( h_reco2fllpdvtx_x               );
	  h_recoFiducLLPdVtx_y             .push_back( h_reco2fllpdvtx_y               );
	  h_recoFiducLLPdVtx_z             .push_back( h_reco2fllpdvtx_z               );
	  h_recoFiducLLPdVtx_r             .push_back( h_reco2fllpdvtx_r               );
	  h_recoFiducLLPdVtx_pt            .push_back( h_reco2fllpdvtx_pt              );
	  h_recoFiducLLPdVtx_eta           .push_back( h_reco2fllpdvtx_eta             );
	  h_recoFiducLLPdVtx_phi           .push_back( h_reco2fllpdvtx_phi             );
	  h_recoFiducLLPdVtx_avgMu         .push_back( h_reco2fllpdvtx_avgMu           );
	  h_recoFiducLLPdVtx_descM         .push_back( h_reco2fllpdvtx_descM           );
	  h_recoFiducLLPdVtx_nDesc         .push_back( h_reco2fllpdvtx_nDesc           );
	  h_recoFiducLLPdVtx_nRecoDesc     .push_back( h_reco2fllpdvtx_nRecoDesc       );
	  h_recoFiducLLPdVtx_nSelDesc      .push_back( h_reco2fllpdvtx_nSelDesc        );
	  h_selFiducLLPdVtx_x              .push_back( h_slctfllpdvtx_x                );
	  h_selFiducLLPdVtx_y              .push_back( h_slctfllpdvtx_y                );
	  h_selFiducLLPdVtx_z              .push_back( h_slctfllpdvtx_z                );
	  h_selFiducLLPdVtx_r              .push_back( h_slctfllpdvtx_r                );
	  h_selFiducLLPdVtx_pt             .push_back( h_slctfllpdvtx_pt               );
	  h_selFiducLLPdVtx_eta            .push_back( h_slctfllpdvtx_eta              );
	  h_selFiducLLPdVtx_phi            .push_back( h_slctfllpdvtx_phi              );
	  h_selFiducLLPdVtx_avgMu          .push_back( h_slctfllpdvtx_avgMu            );
	  h_selFiducLLPdVtx_descM          .push_back( h_slctfllpdvtx_descM            );
	  h_selFiducLLPdVtx_nDesc          .push_back( h_slctfllpdvtx_nDesc            );
	  h_selFiducLLPdVtx_nRecoDesc      .push_back( h_slctfllpdvtx_nRecoDesc        );
	  h_selFiducLLPdVtx_nSelDesc       .push_back( h_slctfllpdvtx_nSelDesc         );
	  h_sgnlRecoMatchLLPdVtx_score     .push_back( h_smatchllpdvtx_score           );
	  h_sgnlRecoMatchLLPdVtx_x         .push_back( h_smatchllpdvtx_x               );
	  h_sgnlRecoMatchLLPdVtx_y         .push_back( h_smatchllpdvtx_y               );
	  h_sgnlRecoMatchLLPdVtx_z         .push_back( h_smatchllpdvtx_z               );
	  h_sgnlRecoMatchLLPdVtx_r         .push_back( h_smatchllpdvtx_r               );
	  h_sgnlRecoMatchLLPdVtx_pt        .push_back( h_smatchllpdvtx_pt              );
	  h_sgnlRecoMatchLLPdVtx_eta       .push_back( h_smatchllpdvtx_eta             );
	  h_sgnlRecoMatchLLPdVtx_phi       .push_back( h_smatchllpdvtx_phi             );
	  h_sgnlRecoMatchLLPdVtx_avgMu     .push_back( h_smatchllpdvtx_avgMu           );
	  h_sgnlRecoMatchLLPdVtx_descM     .push_back( h_smatchllpdvtx_descM           );
	  h_sgnlRecoMatchLLPdVtx_nDesc     .push_back( h_smatchllpdvtx_nDesc           );
	  h_sgnlRecoMatchLLPdVtx_nRecoDesc .push_back( h_smatchllpdvtx_nRecoDesc       );
	  h_sgnlRecoMatchLLPdVtx_nSelDesc  .push_back( h_smatchllpdvtx_nSelDesc        );
	  h_sgnlRecoMatchLLPdVtx_resid_x   .push_back( h_smatchllpdvtx_resid_x         );
	  h_sgnlRecoMatchLLPdVtx_resid_y   .push_back( h_smatchllpdvtx_resid_y         );
	  h_sgnlRecoMatchLLPdVtx_resid_z   .push_back( h_smatchllpdvtx_resid_z         );
	  h_sgnlRecoMatchLLPdVtx_resid_r   .push_back( h_smatchllpdvtx_resid_r         );
	  h_sgnlRecoMatchLLPdVtx_resid_rphi.push_back( h_smatchllpdvtx_resid_rphi      );
	  h_sgnlRecoMatchLLPdVtx_resid_z_r          .push_back( h_smatchllpdvtx_resid_z_r          );
	  h_sgnlRecoMatchLLPdVtx_resid_z_z          .push_back( h_smatchllpdvtx_resid_z_z          );
	  h_sgnlRecoMatchLLPdVtx_resid_z_ntrk       .push_back( h_smatchllpdvtx_resid_z_ntrk       );
	  h_sgnlRecoMatchLLPdVtx_resid_z_nseltrk    .push_back( h_smatchllpdvtx_resid_z_nseltrk    );
	  h_sgnlRecoMatchLLPdVtx_resid_r_r          .push_back( h_smatchllpdvtx_resid_r_r          );
	  h_sgnlRecoMatchLLPdVtx_resid_r_z          .push_back( h_smatchllpdvtx_resid_r_z          );
	  h_sgnlRecoMatchLLPdVtx_resid_r_ntrk       .push_back( h_smatchllpdvtx_resid_r_ntrk       );
	  h_sgnlRecoMatchLLPdVtx_resid_r_nseltrk    .push_back( h_smatchllpdvtx_resid_r_nseltrk    );
	  h_sgnlRecoMatchLLPdVtx_resid_rphi_r       .push_back( h_smatchllpdvtx_resid_rphi_r       );
	  h_sgnlRecoMatchLLPdVtx_resid_rphi_z       .push_back( h_smatchllpdvtx_resid_rphi_z       );
	  h_sgnlRecoMatchLLPdVtx_resid_rphi_ntrk    .push_back( h_smatchllpdvtx_resid_rphi_ntrk    );
	  h_sgnlRecoMatchLLPdVtx_resid_rphi_nseltrk .push_back( h_smatchllpdvtx_resid_rphi_nseltrk );
	  h_LLPdVtx_accept_x               .push_back( h_llpdvtx_accept_x              );
	  h_LLPdVtx_accept_y               .push_back( h_llpdvtx_accept_y              );
	  h_LLPdVtx_accept_z               .push_back( h_llpdvtx_accept_z              );
	  h_LLPdVtx_accept_r               .push_back( h_llpdvtx_accept_r              );
	  h_LLPdVtx_accept_pt              .push_back( h_llpdvtx_accept_pt             );
	  h_LLPdVtx_accept_eta             .push_back( h_llpdvtx_accept_eta            );
	  h_LLPdVtx_accept_phi             .push_back( h_llpdvtx_accept_phi            );
	  h_LLPdVtx_accept_avgMu           .push_back( h_llpdvtx_accept_avgMu          );
	  h_LLPdVtx_accept_descM           .push_back( h_llpdvtx_accept_descM          );
	  h_LLPdVtx_accept_nDesc           .push_back( h_llpdvtx_accept_nDesc          );
	  h_LLPdVtx_accept_nRecoDesc       .push_back( h_llpdvtx_accept_nRecoDesc      );
	  h_LLPdVtx_accept_nSelDesc        .push_back( h_llpdvtx_accept_nSelDesc       );
	  h_LLPdVtx_recoEff_x              .push_back( h_llpdvtx_recoEff_x             );
	  h_LLPdVtx_recoEff_y              .push_back( h_llpdvtx_recoEff_y             );
	  h_LLPdVtx_recoEff_z              .push_back( h_llpdvtx_recoEff_z             );
	  h_LLPdVtx_recoEff_r              .push_back( h_llpdvtx_recoEff_r             );
	  h_LLPdVtx_recoEff_pt             .push_back( h_llpdvtx_recoEff_pt            );
	  h_LLPdVtx_recoEff_eta            .push_back( h_llpdvtx_recoEff_eta           );
	  h_LLPdVtx_recoEff_phi            .push_back( h_llpdvtx_recoEff_phi           );
	  h_LLPdVtx_recoEff_avgMu          .push_back( h_llpdvtx_recoEff_avgMu         );
	  h_LLPdVtx_recoEff_descM          .push_back( h_llpdvtx_recoEff_descM         );
	  h_LLPdVtx_recoEff_nDesc          .push_back( h_llpdvtx_recoEff_nDesc         );
	  h_LLPdVtx_recoEff_nRecoDesc      .push_back( h_llpdvtx_recoEff_nRecoDesc     );
	  h_LLPdVtx_recoEff_nSelDesc       .push_back( h_llpdvtx_recoEff_nSelDesc      );
	  h_LLPdVtx_algEff_x               .push_back( h_llpdvtx_algEff_x              );
	  h_LLPdVtx_algEff_y               .push_back( h_llpdvtx_algEff_y              );
	  h_LLPdVtx_algEff_z               .push_back( h_llpdvtx_algEff_z              );
	  h_LLPdVtx_algEff_r               .push_back( h_llpdvtx_algEff_r              );
	  h_LLPdVtx_algEff_pt              .push_back( h_llpdvtx_algEff_pt             );
	  h_LLPdVtx_algEff_eta             .push_back( h_llpdvtx_algEff_eta            );
	  h_LLPdVtx_algEff_phi             .push_back( h_llpdvtx_algEff_phi            );
	  h_LLPdVtx_algEff_avgMu           .push_back( h_llpdvtx_algEff_avgMu          );
	  h_LLPdVtx_algEff_descM           .push_back( h_llpdvtx_algEff_descM          );
	  h_LLPdVtx_algEff_nDesc           .push_back( h_llpdvtx_algEff_nDesc          );
	  h_LLPdVtx_algEff_nRecoDesc       .push_back( h_llpdvtx_algEff_nRecoDesc      );
	  h_LLPdVtx_algEff_nSelDesc        .push_back( h_llpdvtx_algEff_nSelDesc       );
	  h_LLPdVtx_coreEff_x              .push_back( h_llpdvtx_coreEff_x             );
	  h_LLPdVtx_coreEff_y              .push_back( h_llpdvtx_coreEff_y             );
	  h_LLPdVtx_coreEff_z              .push_back( h_llpdvtx_coreEff_z             );
	  h_LLPdVtx_coreEff_r              .push_back( h_llpdvtx_coreEff_r             );
	  h_LLPdVtx_coreEff_pt             .push_back( h_llpdvtx_coreEff_pt            );
	  h_LLPdVtx_coreEff_eta            .push_back( h_llpdvtx_coreEff_eta           );
	  h_LLPdVtx_coreEff_phi            .push_back( h_llpdvtx_coreEff_phi           );
	  h_LLPdVtx_coreEff_avgMu          .push_back( h_llpdvtx_coreEff_avgMu         );
	  h_LLPdVtx_coreEff_descM          .push_back( h_llpdvtx_coreEff_descM         );
	  h_LLPdVtx_coreEff_nDesc          .push_back( h_llpdvtx_coreEff_nDesc         );
	  h_LLPdVtx_coreEff_nRecoDesc      .push_back( h_llpdvtx_coreEff_nRecoDesc     );
	  h_LLPdVtx_coreEff_nSelDesc       .push_back( h_llpdvtx_coreEff_nSelDesc      );
	  h_LLPdVtx_seedEff_x              .push_back( h_llpdvtx_seedEff_x             );
	  h_LLPdVtx_seedEff_y              .push_back( h_llpdvtx_seedEff_y             );
	  h_LLPdVtx_seedEff_z              .push_back( h_llpdvtx_seedEff_z             );
	  h_LLPdVtx_seedEff_r              .push_back( h_llpdvtx_seedEff_r             );
	  h_LLPdVtx_seedEff_pt             .push_back( h_llpdvtx_seedEff_pt            );
	  h_LLPdVtx_seedEff_eta            .push_back( h_llpdvtx_seedEff_eta           );
	  h_LLPdVtx_seedEff_phi            .push_back( h_llpdvtx_seedEff_phi           );
	  h_LLPdVtx_seedEff_avgMu          .push_back( h_llpdvtx_seedEff_avgMu         );
	  h_LLPdVtx_seedEff_descM          .push_back( h_llpdvtx_seedEff_descM         );
	  h_LLPdVtx_seedEff_nDesc          .push_back( h_llpdvtx_seedEff_nDesc         );
	  h_LLPdVtx_seedEff_nRecoDesc      .push_back( h_llpdvtx_seedEff_nRecoDesc     );
	  h_LLPdVtx_seedEff_nSelDesc       .push_back( h_llpdvtx_seedEff_nSelDesc      );
	  h_LLPdVtx_sgnlAccept_x           .push_back( h_llpdvtx_sgnlaccept_x          );
	  h_LLPdVtx_sgnlAccept_y           .push_back( h_llpdvtx_sgnlaccept_y          );
	  h_LLPdVtx_sgnlAccept_z           .push_back( h_llpdvtx_sgnlaccept_z          );
	  h_LLPdVtx_sgnlAccept_r           .push_back( h_llpdvtx_sgnlaccept_r          );
	  h_LLPdVtx_sgnlAccept_pt          .push_back( h_llpdvtx_sgnlaccept_pt         );
	  h_LLPdVtx_sgnlAccept_eta         .push_back( h_llpdvtx_sgnlaccept_eta        );
	  h_LLPdVtx_sgnlAccept_phi         .push_back( h_llpdvtx_sgnlaccept_phi        );
	  h_LLPdVtx_sgnlAccept_avgMu       .push_back( h_llpdvtx_sgnlaccept_avgMu      );
	  h_LLPdVtx_sgnlAccept_descM       .push_back( h_llpdvtx_sgnlaccept_descM      );
	  h_LLPdVtx_sgnlAccept_nDesc       .push_back( h_llpdvtx_sgnlaccept_nDesc      );
	  h_LLPdVtx_sgnlAccept_nRecoDesc   .push_back( h_llpdvtx_sgnlaccept_nRecoDesc  );
	  h_LLPdVtx_sgnlAccept_nSelDesc    .push_back( h_llpdvtx_sgnlaccept_nSelDesc   );	
	  h_LLPdVtx_sgnlRecoEff_x          .push_back( h_llpdvtx_sgnlrecoEff_x         );
	  h_LLPdVtx_sgnlRecoEff_y          .push_back( h_llpdvtx_sgnlrecoEff_y         );
	  h_LLPdVtx_sgnlRecoEff_z          .push_back( h_llpdvtx_sgnlrecoEff_z         );
	  h_LLPdVtx_sgnlRecoEff_r          .push_back( h_llpdvtx_sgnlrecoEff_r         );
	  h_LLPdVtx_sgnlRecoEff_pt         .push_back( h_llpdvtx_sgnlrecoEff_pt        );
	  h_LLPdVtx_sgnlRecoEff_eta        .push_back( h_llpdvtx_sgnlrecoEff_eta       );
	  h_LLPdVtx_sgnlRecoEff_phi        .push_back( h_llpdvtx_sgnlrecoEff_phi       );
	  h_LLPdVtx_sgnlRecoEff_avgMu      .push_back( h_llpdvtx_sgnlrecoEff_avgMu     );
	  h_LLPdVtx_sgnlRecoEff_descM      .push_back( h_llpdvtx_sgnlrecoEff_descM     );
	  h_LLPdVtx_sgnlRecoEff_nDesc      .push_back( h_llpdvtx_sgnlrecoEff_nDesc     );
	  h_LLPdVtx_sgnlRecoEff_nRecoDesc  .push_back( h_llpdvtx_sgnlrecoEff_nRecoDesc );
	  h_LLPdVtx_sgnlRecoEff_nSelDesc   .push_back( h_llpdvtx_sgnlrecoEff_nSelDesc  );
	  h_LLPdVtx_sgnlAlgEff_x           .push_back( h_llpdvtx_sgnlalgEff_x          );
	  h_LLPdVtx_sgnlAlgEff_y           .push_back( h_llpdvtx_sgnlalgEff_y          );
	  h_LLPdVtx_sgnlAlgEff_z           .push_back( h_llpdvtx_sgnlalgEff_z          );
	  h_LLPdVtx_sgnlAlgEff_r           .push_back( h_llpdvtx_sgnlalgEff_r          );
	  h_LLPdVtx_sgnlAlgEff_pt          .push_back( h_llpdvtx_sgnlalgEff_pt         );
	  h_LLPdVtx_sgnlAlgEff_eta         .push_back( h_llpdvtx_sgnlalgEff_eta        );
	  h_LLPdVtx_sgnlAlgEff_phi         .push_back( h_llpdvtx_sgnlalgEff_phi        );
	  h_LLPdVtx_sgnlAlgEff_avgMu       .push_back( h_llpdvtx_sgnlalgEff_avgMu      );
	  h_LLPdVtx_sgnlAlgEff_descM       .push_back( h_llpdvtx_sgnlalgEff_descM      );
	  h_LLPdVtx_sgnlAlgEff_nDesc       .push_back( h_llpdvtx_sgnlalgEff_nDesc      );
	  h_LLPdVtx_sgnlAlgEff_nRecoDesc   .push_back( h_llpdvtx_sgnlalgEff_nRecoDesc  );
	  h_LLPdVtx_sgnlAlgEff_nSelDesc    .push_back( h_llpdvtx_sgnlalgEff_nSelDesc   );
	  h_LLPdVtx_sgnlCoreEff_x          .push_back( h_llpdvtx_sgnlcoreEff_x         );
	  h_LLPdVtx_sgnlCoreEff_y          .push_back( h_llpdvtx_sgnlcoreEff_y         );
	  h_LLPdVtx_sgnlCoreEff_z          .push_back( h_llpdvtx_sgnlcoreEff_z         );
	  h_LLPdVtx_sgnlCoreEff_r          .push_back( h_llpdvtx_sgnlcoreEff_r         );
	  h_LLPdVtx_sgnlCoreEff_pt         .push_back( h_llpdvtx_sgnlcoreEff_pt        );
	  h_LLPdVtx_sgnlCoreEff_eta        .push_back( h_llpdvtx_sgnlcoreEff_eta       );
	  h_LLPdVtx_sgnlCoreEff_phi        .push_back( h_llpdvtx_sgnlcoreEff_phi       );
	  h_LLPdVtx_sgnlCoreEff_avgMu      .push_back( h_llpdvtx_sgnlcoreEff_avgMu     );
	  h_LLPdVtx_sgnlCoreEff_descM      .push_back( h_llpdvtx_sgnlcoreEff_descM     );
	  h_LLPdVtx_sgnlCoreEff_nDesc      .push_back( h_llpdvtx_sgnlcoreEff_nDesc     );
	  h_LLPdVtx_sgnlCoreEff_nRecoDesc  .push_back( h_llpdvtx_sgnlcoreEff_nRecoDesc );
	  h_LLPdVtx_sgnlCoreEff_nSelDesc   .push_back( h_llpdvtx_sgnlcoreEff_nSelDesc  );
	  h_LLPdVtx_sgnlSeedEff_x          .push_back( h_llpdvtx_sgnlseedEff_x         );
	  h_LLPdVtx_sgnlSeedEff_y          .push_back( h_llpdvtx_sgnlseedEff_y         );
	  h_LLPdVtx_sgnlSeedEff_z          .push_back( h_llpdvtx_sgnlseedEff_z         );
	  h_LLPdVtx_sgnlSeedEff_r          .push_back( h_llpdvtx_sgnlseedEff_r         );
	  h_LLPdVtx_sgnlSeedEff_pt         .push_back( h_llpdvtx_sgnlseedEff_pt        );
	  h_LLPdVtx_sgnlSeedEff_eta        .push_back( h_llpdvtx_sgnlseedEff_eta       );
	  h_LLPdVtx_sgnlSeedEff_phi        .push_back( h_llpdvtx_sgnlseedEff_phi       );
	  h_LLPdVtx_sgnlSeedEff_avgMu      .push_back( h_llpdvtx_sgnlseedEff_avgMu     );
	  h_LLPdVtx_sgnlSeedEff_descM      .push_back( h_llpdvtx_sgnlseedEff_descM     );
	  h_LLPdVtx_sgnlSeedEff_nDesc      .push_back( h_llpdvtx_sgnlseedEff_nDesc     );
	  h_LLPdVtx_sgnlSeedEff_nRecoDesc  .push_back( h_llpdvtx_sgnlseedEff_nRecoDesc );
	  h_LLPdVtx_sgnlSeedEff_nSelDesc   .push_back( h_llpdvtx_sgnlseedEff_nSelDesc  );
	}
      } // end if not abcdcutOnly
    }


    // --- SECONDARY VERTICES -- //
    if ( !m_histoInfoSwitch->m_truthOnly ) {
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
      std::vector<TH1F*> h_dv_H;
      std::vector<TH1F*> h_dv_H_s;
      std::vector<TH1F*> h_dv_H_xs;
      std::vector<TH1F*> h_dv_Ht;
      std::vector<TH1F*> h_dv_Ht_s;
      std::vector<TH1F*> h_dv_Ht_xs;
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
      std::vector<TH1F*> h_dv_assoctrk_d0;
      std::vector<TH1F*> h_dv_assoctrk_eta;
      std::vector<TH1F*> h_dv_assoctrk_phi;
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
      std::vector<TH1F*> h_dv_mind0_s;
      std::vector<TH1F*> h_dv_minz0_s;
      std::vector<TH1F*> h_dv_minP;
      std::vector<TH1F*> h_dv_minsqrtd0;
      std::vector<TH1F*> h_dv_minsqrtz0;
      std::vector<TH1F*> h_dv_minsqrtP;
      std::vector<TH1F*> h_dv_minErrd0;
      std::vector<TH1F*> h_dv_minErrz0;
      std::vector<TH1F*> h_dv_minErrP;
      std::vector<TH1F*> h_dv_minSqrterrd0;
      std::vector<TH1F*> h_dv_minSqrterrz0;
      std::vector<TH1F*> h_dv_minSqrterrd0_s;
      std::vector<TH1F*> h_dv_minSqrterrz0_s;
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
      std::vector<TH2F*> h_dv_y_x;
      std::vector<TH2F*> h_dv_z_r;
      std::vector<TH2F*> h_dv_r_z;
      std::vector<TH2F*> h_dv_r_phi;
      std::vector<TH3F*> h_dv_rzphi;
      std::vector<TH2F*> h_dv_mass_r;
      std::vector<TH2F*> h_dv_z_chi2;
      std::vector<TH2F*> h_dv_r_chi2;
      std::vector<TH2F*> h_dv_mass_chi2;
      std::vector<TH2F*> h_dv_y_x_s;
      std::vector<TH2F*> h_dv_z_r_s;
      std::vector<TH2F*> h_dv_r_z_s;
      std::vector<TH2F*> h_dv_r_phi_s;
      std::vector<TH3F*> h_dv_rzphi_s;
      std::vector<TH2F*> h_dv_mass_r_s;
      std::vector<TH2F*> h_dv_z_chi2_s;
      std::vector<TH2F*> h_dv_r_chi2_s;
      std::vector<TH2F*> h_dv_mass_chi2_s;
      std::vector<TH2F*> h_dv_mind0_r;
      std::vector<TH2F*> h_dv_minz0_z;
      std::vector<TH2F*> h_dv_mind0z0;
      std::vector<TH2F*> h_dv_mind0_r_s;
      std::vector<TH2F*> h_dv_minz0_z_s;
      std::vector<TH2F*> h_dv_mind0z0_s;
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
      std::vector<TH2F*> h_dv_minSqrterrd0_mind0;
      std::vector<TH2F*> h_dv_minSqrterrz0_minz0;
      std::vector<TH2F*> h_dv_minSqrterrd0z0;
      std::vector<TH2F*> h_dv_minSqrterrd0_mind0_s;
      std::vector<TH2F*> h_dv_minSqrterrz0_minz0_s;
      std::vector<TH2F*> h_dv_minSqrterrd0z0_s;
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
      std::vector<TH2F*> h_dv_assoctrk_d0_phi;
      std::vector<TH2F*> h_dv_assoctrk_eta_phi;
      std::vector<TH2F*> h_dv_assoctrk_phi_eta;
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
      // sum-pt (Ht), ntracks (in event, for various types of tracks), sum of vertex masses / invariant mass of vertices in system
      for ( size_t i = 0; i != hDV.size(); ++i ) {
	// vertex basics
	std::string hdv    = hDV   [i] + "DV"; hdv[0] = tolower(hdv[0]);
	std::string hdvstr = hDVstr[i];        hdvstr.pop_back(); hdvstr += " DV";
	h_dv_n              .push_back( book( name, hdv + "_n",           "n " + hdvstr + "s",                     15,    0,   15 ) );
	if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
	  h_dv_x            .push_back( book( name, hdv + "_x",           hdvstr + " x-pos [mm]",                 100, -400,  400 ) );
	  h_dv_y            .push_back( book( name, hdv + "_y",           hdvstr + " y-pos [mm]",                 100, -400,  400 ) );
	  h_dv_z            .push_back( book( name, hdv + "_z",           hdvstr + " z-pos [mm]",                 100, -800,  800 ) );
	  h_dv_r            .push_back( book( name, hdv + "_r",           hdvstr + " r-pos [mm]",                 100,    0,  400 ) );
	  h_dv_x_s          .push_back( book( name, hdv + "_x_s",         hdvstr + " x-pos [mm]",                 100, -300,  300 ) );
	  h_dv_y_s          .push_back( book( name, hdv + "_y_s",         hdvstr + " y-pos [mm]",                 100, -300,  300 ) );
	  h_dv_z_s          .push_back( book( name, hdv + "_z_s",         hdvstr + " z-pos [mm]",                 100, -300,  300 ) );
	  h_dv_r_s          .push_back( book( name, hdv + "_r_s",         hdvstr + " r-pos [mm]",                 100,    0,  300 ) );
	  h_dv_phipos       .push_back( book( name, hdv + "_phipos",      hdvstr + " phi-pos",                    100, -3.5,  3.5 ) );
	  h_dv_pt           .push_back( book( name, hdv + "_pt",          hdvstr + " p_{T} [GeV]",                100,    0,  100 ) );
	  h_dv_pt_s         .push_back( book( name, hdv + "_pt_s",        hdvstr + " p_{T} [GeV]",                100,    0,   50 ) );
	  h_dv_pt_xs        .push_back( book( name, hdv + "_pt_xs",       hdvstr + " p_{T} [GeV]",                100,    0,   10 ) );
	  h_dv_eta          .push_back( book( name, hdv + "_eta",         hdvstr + " eta",                        100,   -5,    5 ) );
	  h_dv_phi          .push_back( book( name, hdv + "_phi",         hdvstr + " phi",                        100, -3.5,  3.5 ) );
	  h_dv_mass         .push_back( book( name, hdv + "_mass",        hdvstr + " mass [GeV]",                 100,    0,   50 ) );
	  h_dv_mass_l       .push_back( book( name, hdv + "_mass_l",      hdvstr + " mass [GeV]",                 100,    0,  100 ) );
	  h_dv_mass_s       .push_back( book( name, hdv + "_mass_s",      hdvstr + " mass [GeV]",                 100,    0,   25 ) );
	  h_dv_mass_xs      .push_back( book( name, hdv + "_mass_xs",     hdvstr + " mass [GeV]",                 100,    0,    5 ) );
	  h_dv_massNA       .push_back( book( name, hdv + "_massNA",      hdvstr + " non-assoc. mass [GeV]",      100,    0,   50 ) );
	  h_dv_massNA_l     .push_back( book( name, hdv + "_massNA_l",    hdvstr + " non-assoc. mass [GeV]",      100,    0,  100 ) );
	  h_dv_massNA_s     .push_back( book( name, hdv + "_massNA_s",    hdvstr + " non-assoc. mass [GeV]",      100,    0,   25 ) );
	  h_dv_massNA_xs    .push_back( book( name, hdv + "_massNA_xs",   hdvstr + " non-assoc. mass [GeV]",      100,    0,    5 ) );
	  h_dv_direction    .push_back( book( name, hdv + "_direction",   hdvstr + " direction",                  100, -1.1,  1.1 ) );
	  h_dv_H            .push_back( book( name, hdv + "_H",           hdvstr + " H [GeV]",                    100,    0,  200 ) );
	  h_dv_H_s          .push_back( book( name, hdv + "_H_s",         hdvstr + " H [GeV]",                    100,    0,  100 ) );
	  h_dv_H_xs         .push_back( book( name, hdv + "_H_xs",        hdvstr + " H [GeV]",                    100,    0,   20 ) );
	  h_dv_Ht           .push_back( book( name, hdv + "_Ht",          hdvstr + " H_{T} [GeV]",                100,    0,  100 ) );
	  h_dv_Ht_s         .push_back( book( name, hdv + "_Ht_s",        hdvstr + " H_{T} [GeV]",                100,    0,   50 ) );
	  h_dv_Ht_xs        .push_back( book( name, hdv + "_Ht_xs",       hdvstr + " H_{T} [GeV]",                100,    0,   10 ) );
	  h_dv_minOpAng     .push_back( book( name, hdv + "_minOpAng",    hdvstr + " cos min opening angle",      100, -1.1,  1.1 ) );
	  h_dv_maxOpAng     .push_back( book( name, hdv + "_maxOpAng",    hdvstr + " cos max opening angle",      100, -1.1,  1.1 ) );
	  h_dv_chi2         .push_back( book( name, hdv + "_chi2",        hdvstr + " chi2 / nDoF",                100,    0,   10 ) );
	  h_dv_chi2_s       .push_back( book( name, hdv + "_chi2_s",      hdvstr + " chi2 / nDoF",                100,    0,    5 ) );
	  h_dv_ntrk         .push_back( book( name, hdv + "_ntrk",        "n " + hdvstr + " tracks",               10,    2,   12 ) );
	  h_dv_ntrk_final   .push_back( book( name, hdv + "_ntrk_final",  "n " + hdvstr + " final tracks",         10,    2,   12 ) );
	  h_dv_ntrk_sel     .push_back( book( name, hdv + "_ntrk_sel",    "n " + hdvstr + " selected tracks",      10,    2,   12 ) );
	  h_dv_ntrk_assoc   .push_back( book( name, hdv + "_ntrk_assoc",  "n " + hdvstr + " associated tracks",    10,    2,   12 ) );
	  h_dv_ntrk_lrt     .push_back( book( name, hdv + "_ntrk_lrt",    "n " + hdvstr + " large-radius tracks",  10,    2,   12 ) );
	  if ( m_histoInfoSwitch->m_vtxErrors ) {
	    h_dv_errx       .push_back( book( name, hdv + "_errx",        hdvstr + " x-pos uncert.",              100,    0,   25 ) );
	    h_dv_erry       .push_back( book( name, hdv + "_erry",        hdvstr + " y-pos uncert.",              100,    0,   25 ) );
	    h_dv_errz       .push_back( book( name, hdv + "_errz",        hdvstr + " z-pos uncert.",              100,    0,   25 ) );
	    h_dv_errr       .push_back( book( name, hdv + "_errr",        hdvstr + " r-pos uncert.",              100,    0,   25 ) );
	    h_dv_errphi     .push_back( book( name, hdv + "_errphi",      hdvstr + " phi uncert.",                100,    0, 0.15 ) );
	    h_dv_sqrterrx   .push_back( book( name, hdv + "_sqrterrx",    hdvstr + " x-pos sqrt-uncert.",         100,    0,    5 ) );
	    h_dv_sqrterry   .push_back( book( name, hdv + "_sqrterry",    hdvstr + " y-pos sqrt-uncert.",         100,    0,    5 ) );
	    h_dv_sqrterrz   .push_back( book( name, hdv + "_sqrterrz",    hdvstr + " z-pos sqrt-uncert.",         100,    0,    5 ) );
	    h_dv_sqrterrr   .push_back( book( name, hdv + "_sqrterrr",    hdvstr + " r-pos sqrt-uncert.",         100,    0,    5 ) );
	    h_dv_sqrterrphi .push_back( book( name, hdv + "_sqrterrphi",  hdvstr + " phi sqrt-uncert.",           100,    0,  0.4 ) );
	    h_dv_fracerrx   .push_back( book( name, hdv + "_fracerrx",    hdvstr + " x-pos fractional uncert.",   100,    0,  0.1 ) );
	    h_dv_fracerry   .push_back( book( name, hdv + "_fracerry",    hdvstr + " y-pos fractional uncert.",   100,    0,  0.1 ) );
	    h_dv_fracerrz   .push_back( book( name, hdv + "_fracerrz",    hdvstr + " z-pos fractional uncert.",   100,    0,  0.1 ) );
	    h_dv_fracerrr   .push_back( book( name, hdv + "_fracerrr",    hdvstr + " r-pos fractional uncert.",   100,    0,  0.1 ) );
	    h_dv_fracerrphi .push_back( book( name, hdv + "_fracerrphi",  hdvstr + " phi fractional uncert.",     100,    0,  0.1 ) );
	    h_dv_signifx    .push_back( book( name, hdv + "_signifx",     hdvstr + " x-pos significance",         100,    0, 1000 ) );
	    h_dv_signify    .push_back( book( name, hdv + "_signify",     hdvstr + " y-pos significance",         100,    0, 1000 ) );
	    h_dv_signifz    .push_back( book( name, hdv + "_signifz",     hdvstr + " z-pos significance",         100,    0, 1000 ) );
	    h_dv_signifr    .push_back( book( name, hdv + "_signifr",     hdvstr + " r-pos significance",         100,    0, 1000 ) );
	    h_dv_signifphi  .push_back( book( name, hdv + "_signifphi",   hdvstr + " phi-pos significance",       100,    0, 1000 ) );
	  }
	  // vertex nearby jets
	  h_dv_jetDR        .push_back( book( name, hdv + "_jetDR",       hdvstr + " - jet dR",                   100,    0,  0.6 ) );
	  h_dv_leadJetDR    .push_back( book( name, hdv + "_leadJetDR",   hdvstr + " - lead jet dR",              100,    0,  0.6 ) );

	  // vertex tracks
	  std::string hDVtrk         = hdv    + "_trk";
	  std::string hDVtrkstr      = hdvstr + " track";
	  std::string hDVseltrk      = hdv    + "_seltrk";
	  std::string hDVseltrkstr   = hdvstr + " selected track";
	  std::string hDVassoctrk    = hdv    + "_assoctrk";
	  std::string hDVassoctrkstr = hdvstr + " associated track";
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
	    h_dv_assoctrk_d0      .push_back( book( name, hDVassoctrk + "_d0",      hDVassoctrkstr + " d0 [mm]",            100,  -300,   300 ) );
	    h_dv_assoctrk_eta     .push_back( book( name, hDVassoctrk + "_eta",     hDVassoctrkstr + " eta",                100,  -3.5,   3.5 ) );
	    h_dv_assoctrk_phi     .push_back( book( name, hDVassoctrk + "_phi",     hDVassoctrkstr + " phi",                100,  -3.5,   3.5 ) );
	  }
      
	  // sum, min, max vertex track errors
	  std::string hDVsum    = hdv    + "_sum";
	  std::string hDVsumstr = hdvstr + " sum track";
	  std::string hDVmin    = hdv    + "_min";
	  std::string hDVminstr = hdvstr + " min track";
	  std::string hDVmax    = hdv    + "_max";
	  std::string hDVmaxstr = hdvstr + " max track";
	  if ( m_histoInfoSwitch->m_vtxOverallTrk ) {
	    h_dv_sumd0           .push_back( book( name, hDVsum + "d0",           hDVsumstr + " |d0| [mm]",               100, 0,  500 ) );
	    h_dv_sumz0           .push_back( book( name, hDVsum + "z0",           hDVsumstr + " |z0| [mm]",               100, 0, 2000 ) );
	    h_dv_sumP            .push_back( book( name, hDVsum + "P",            hDVsumstr + " |q/p| [e/GeV]",           100, 0,    5 ) );
	    h_dv_sumd0_sv        .push_back( book( name, hDVsum + "d0_sv",        hDVsumstr + " |d0| wrt SV [mm]",        100, 0,   50 ) );
	    h_dv_sumz0_sv        .push_back( book( name, hDVsum + "z0_sv",        hDVsumstr + " |z0| wrt SV [mm]",        100, 0,  150 ) );
	    h_dv_sumP_sv         .push_back( book( name, hDVsum + "P_sv",         hDVsumstr + " |q/p| wrt SV [e/GeV]",    100, 0,    5 ) );
	    h_dv_sumsqrtd0       .push_back( book( name, hDVsum + "sqrtd0",       hDVsumstr + " sqrt |d0| [mm]",          100, 0, 22.5 ) );
	    h_dv_sumsqrtz0       .push_back( book( name, hDVsum + "sqrtz0",       hDVsumstr + " sqrt |z0| [mm]",          100, 0,   45 ) );
	    h_dv_sumsqrtP        .push_back( book( name, hDVsum + "sqrtP",        hDVsumstr + " sqrt |q/p| [e/GeV]",      100, 0, 2.25 ) );
	    h_dv_sumsqrtd0_sv    .push_back( book( name, hDVsum + "sqrtd0_sv",    hDVsumstr + " sqrt |d0| wrt SV [mm]",   100, 0,    7 ) );
	    h_dv_sumsqrtz0_sv    .push_back( book( name, hDVsum + "sqrtz0_sv",    hDVsumstr + " sqrt |z0| wrt SV [mm]",   100, 0,12.25 ) );
	    h_dv_sumsqrtP_sv     .push_back( book( name, hDVsum + "sqrtP_sv",     hDVsumstr + " sqrt |q/p| wrt SV [e/GeV]",100,0, 2.25 ) );
	    h_dv_mind0           .push_back( book( name, hDVmin + "d0",           hDVminstr + " |d0| [mm]",               100, 0,  200 ) );
	    h_dv_minz0           .push_back( book( name, hDVmin + "z0",           hDVminstr + " |z0| [mm]",               100, 0, 1000 ) );
	    h_dv_mind0_s         .push_back( book( name, hDVmin + "d0_s",         hDVminstr + " |d0| [mm]",               100, 0,   10 ) );
	    h_dv_minz0_s         .push_back( book( name, hDVmin + "z0_s",         hDVminstr + " |z0| [mm]",               100, 0,  100 ) );
	    h_dv_minP            .push_back( book( name, hDVmin + "P",            hDVminstr + " |q/p| [e/GeV]",           100, 0,    1 ) );
	    h_dv_mind0_sv        .push_back( book( name, hDVmin + "d0_sv",        hDVminstr + " |d0| wrt SV [mm]",        100, 0,   15 ) );
	    h_dv_minz0_sv        .push_back( book( name, hDVmin + "z0_sv",        hDVminstr + " |z0| wrt SV [mm]",        100, 0,   50 ) );
	    h_dv_minP_sv         .push_back( book( name, hDVmin + "P_sv",         hDVminstr + " |q/p| wrt SV [e/GeV]",    100, 0,    1 ) );
	    h_dv_minsqrtd0       .push_back( book( name, hDVmin + "sqrtd0",       hDVminstr + " sqrt |d0| [mm]",          100, 0,   14 ) );
	    h_dv_minsqrtz0       .push_back( book( name, hDVmin + "sqrtz0",       hDVminstr + " sqrt |z0| [mm]",          100, 0,   32 ) );
	    h_dv_minsqrtP        .push_back( book( name, hDVmin + "sqrtP",        hDVminstr + " sqrt |q/p| [e/GeV]",      100, 0,    1 ) );
	    h_dv_minsqrtd0_sv    .push_back( book( name, hDVmin + "sqrtd0_sv",    hDVminstr + " sqrt |d0| wrt SV [mm]",   100, 0,    4 ) );
	    h_dv_minsqrtz0_sv    .push_back( book( name, hDVmin + "sqrtz0_sv",    hDVminstr + " sqrt |z0| wrt SV [mm]",   100, 0,    7 ) );
	    h_dv_minsqrtP_sv     .push_back( book( name, hDVmin + "sqrtP_sv",     hDVminstr + " sqrt |q/p| wrt SV [e/GeV]",100,0,    1 ) );
	    h_dv_maxd0           .push_back( book( name, hDVmax + "d0",           hDVmaxstr + " |d0| [mm]",               100, 0,  300 ) );
	    h_dv_maxz0           .push_back( book( name, hDVmax + "z0",           hDVmaxstr + " |z0| [mm]",               100, 0, 1500 ) );
	    h_dv_maxP            .push_back( book( name, hDVmax + "P",            hDVmaxstr + " |q/p| [e/GeV]",           100, 0,  1.1 ) );
	    h_dv_maxd0_sv        .push_back( book( name, hDVmax + "d0_sv",        hDVmaxstr + " |d0| wrt SV [mm]",        100, 0,   30 ) );
	    h_dv_maxz0_sv        .push_back( book( name, hDVmax + "z0_sv",        hDVmaxstr + " |z0| wrt SV [mm]",        100, 0,  100 ) );
	    h_dv_maxP_sv         .push_back( book( name, hDVmax + "P_sv",         hDVmaxstr + " |q/p| wrt SV [e/GeV]",    100, 0,  1.1 ) );
	    h_dv_maxsqrtd0       .push_back( book( name, hDVmax + "sqrtd0",       hDVmaxstr + " sqrt |d0| [mm]",          100, 0, 17.5 ) );
	    h_dv_maxsqrtz0       .push_back( book( name, hDVmax + "sqrtz0",       hDVmaxstr + " sqrt |z0| [mm]",          100, 0,   40 ) );
	    h_dv_maxsqrtP        .push_back( book( name, hDVmax + "sqrtP",        hDVmaxstr + " sqrt |q/p| [e/GeV]",      100, 0,    1 ) );
	    h_dv_maxsqrtd0_sv    .push_back( book( name, hDVmax + "sqrtd0_sv",    hDVmaxstr + " sqrt |d0| wrt SV [mm]",   100, 0,  5.5 ) );
	    h_dv_maxsqrtz0_sv    .push_back( book( name, hDVmax + "sqrtz0_sv",    hDVmaxstr + " sqrt |z0| wrt SV [mm]",   100, 0,   10 ) );
	    h_dv_maxsqrtP_sv     .push_back( book( name, hDVmax + "sqrtP_sv",     hDVmaxstr + " sqrt |q/p| wrt SV [e/GeV]",100,0,    1 ) );
	  }
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
	    h_dv_minSqrterrd0_s  .push_back( book( name, hDVmin + "Sqrterrd0_s",  hDVminstr + " d0 sqrt-uncert.",         100, 0,  0.5 ) );
	    h_dv_minSqrterrz0_s  .push_back( book( name, hDVmin + "Sqrterrz0_s",  hDVminstr + " z0 sqrt-uncert.",         100, 0,  1.5 ) );
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
	    h_dv_y_x                    .push_back( book( name, hdv + "_y_x",             hdvstr + " x-pos [mm]",      100,  -800,  800,
							  hdvstr + " y-pos [mm]",           100,  -800,  800 ) );
	    h_dv_z_r                    .push_back( book( name, hdv + "_z_r",             hdvstr + " r-pos [mm]",      100,     0,  400,
							  hdvstr + " z-pos [mm]",           100,  -800,  800 ) );
	    h_dv_r_z                    .push_back( book( name, hdv + "_r_z",             hdvstr + " z-pos [mm]",      100,  -800,  800,
							  hdvstr + " r-pos [mm]",           100,     0,  400 ) );
	    h_dv_r_phi                  .push_back( book( name, hdv + "_r_phi",           hdvstr + " phi-pos [mm]",    100,  -3.5,  3.5,
							  hdvstr + " r-pos [mm]",           100,     0,  400 ) );
	    h_dv_rzphi                  .push_back( book( name, hdv + "_rzphi",           hdvstr + " r-pos [mm]",      100,     0,  400,
							  hdvstr + " z-pos [mm]",           100,  -800, 800,
							  hdvstr + " phi-pos [mm]",         100,  -3.5, 3.5 ) );
	    h_dv_mass_r                 .push_back( book( name, hdv + "_mass_r",          hdvstr + " r-pos [mm]",      100,     0,  400,
							  hdvstr + " mass [GeV]",           100,     0,   50 ) );
	    h_dv_z_chi2                 .push_back( book( name, hdv + "_z_chi2",          hdvstr + " chi2 / nDoF",     100,     0,   10,
							  hdvstr + " z-pos [mm]",           100,  -800,  800 ) );
	    h_dv_r_chi2                 .push_back( book( name, hdv + "_r_chi2",          hdvstr + " chi2 / nDoF",     100,     0,   10,
							  hdvstr + " r-pos [mm]",           100,     0,  400 ) );
	    h_dv_mass_chi2              .push_back( book( name, hdv + "_mass_chi2",       hdvstr + " chi2 / nDoF",     100,     0,   10,
							  hdvstr + " mass [GeV]",           100,     0,   50 ) );
	    h_dv_y_x_s                  .push_back( book( name, hdv + "_y_x_s",           hdvstr + " x-pos [mm]",      100,  -300,  300,
							  hdvstr + " y-pos [mm]",           100,  -300,  300 ) );
	    h_dv_z_r_s                  .push_back( book( name, hdv + "_z_r_s",           hdvstr + " r-pos [mm]",      100,     0,  300,
							  hdvstr + " z-pos [mm]",           100,  -300,  300 ) );
	    h_dv_r_z_s                  .push_back( book( name, hdv + "_r_z_s",           hdvstr + " z-pos [mm]",      100,  -300,  300,
							  hdvstr + " r-pos [mm]",           100,     0,  300 ) );
	    h_dv_r_phi_s                .push_back( book( name, hdv + "_r_phi_s",         hdvstr + " phi-pos [mm]",    100,  -3.5,  3.5,
							  hdvstr + " r-pos [mm]",           100,     0,  300 ) );
	    h_dv_rzphi_s                .push_back( book( name, hdv + "_rzphi_s",         hdvstr + " r-pos [mm]",      100,     0,  300,
							  hdvstr + " z-pos [mm]",           100,  -300, 300,
							  hdvstr + " phi-pos [mm]",         100,  -3.5, 3.5 ) );
	    h_dv_mass_r_s               .push_back( book( name, hdv + "_mass_r_s",        hdvstr + " r-pos [mm]",      100,     0,  300,
							  hdvstr + " mass [GeV]",           100,     0,   25 ) );
	    h_dv_z_chi2_s               .push_back( book( name, hdv + "_z_chi2_s",        hdvstr + " chi2 / nDoF",     100,     0,    5,
							  hdvstr + " z-pos [mm]",           100,  -300,  300 ) );
	    h_dv_r_chi2_s               .push_back( book( name, hdv + "_r_chi2_s",        hdvstr + " chi2 / nDoF",     100,     0,    5,
							  hdvstr + " r-pos [mm]",           100,     0,  300 ) );
	    h_dv_mass_chi2_s            .push_back( book( name, hdv + "_mass_chi2_s",     hdvstr + " chi2 / nDoF",     100,     0,    5,
							  hdvstr + " mass [GeV]",           100,     0,   25 ) );
	    if ( m_histoInfoSwitch->m_vtxOverallTrk ) {
	      h_dv_mind0_r              .push_back( book( name, hdv + "_mind0_r",         hdvstr + " r-pos [mm]",      100,     0,  400,
							  hdvstr + " min-d0 [mm]",          100,     0,  200 ) );
	      h_dv_minz0_z              .push_back( book( name, hdv + "_minz0_z",         hdvstr + " z-pos [mm]",      100,  -800,  800,
							  hdvstr + " min-z0 [mm]",          100,     0, 1000 ) );
	      h_dv_mind0z0              .push_back( book( name, hdv + "_mind0z0",         hdvstr + " min-z0 [mm]",     100,     0, 1000,
							  hdvstr + " min-d0 [mm]",          100,     0,  200 ) );
	      h_dv_mind0_r_s            .push_back( book( name, hdv + "_mind0_r_s",       hdvstr + " r-pos [mm]",      100,     0,  300,
							  hdvstr + " min-d0 [mm]",          100,     0,   10 ) );
	      h_dv_minz0_z_s            .push_back( book( name, hdv + "_minz0_z_s",       hdvstr + " z-pos [mm]",      100,  -300,  300,
							  hdvstr + " min-z0 [mm]",          100,     0,  100 ) );
	      h_dv_mind0z0_s            .push_back( book( name, hdv + "_mind0z0_s",       hdvstr + " min-z0 [mm]",     100,     0,  100,
							  hdvstr + " min-d0 [mm]",          100,     0,   10 ) );
	    }
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
	    h_dv_minSqrterrd0_mind0     .push_back( book( name, hDVmin + "Sqrterrd0_mind0",     hdvstr + " min-d0 [mm]",     100,     0,  200,
							  hDVminstr + " d0 sqrt-uncert.",         100,     0,  1.5 ) );
	    h_dv_minSqrterrz0_minz0     .push_back( book( name, hDVmin + "Sqrterrz0_minz0",     hdvstr + " min-z0 [mm]",     100,     0, 1000,
							  hDVminstr + " z0 sqrt-uncert.",         100,     0,  3.5 ) );
	    h_dv_minSqrterrd0z0         .push_back( book( name, hDVmin + "Sqrterrd0z0",         hDVminstr+" z0 sqrt-uncert.",100,     0,  3.5,
							  hDVminstr + " d0 sqrt-uncert.",         100,     0,  1.5 ) );
	    h_dv_minSqrterrd0_mind0_s   .push_back( book( name, hDVmin + "Sqrterrd0_mind0_s",   hdvstr + " min-d0 [mm]",     100,     0,   10,
							  hDVminstr + " d0 sqrt-uncert.",         100,     0,  0.5 ) );
	    h_dv_minSqrterrz0_minz0_s   .push_back( book( name, hDVmin + "Sqrterrz0_minz0_s",   hdvstr + " min-z0 [mm]",     100,     0,  100,
							  hDVminstr + " z0 sqrt-uncert.",         100,     0,  1.5 ) );
	    h_dv_minSqrterrd0z0_s       .push_back( book( name, hDVmin + "Sqrterrd0z0_s",       hDVminstr+" z0 sqrt-uncert.",100,     0,  1.5,
							  hDVminstr + " d0 sqrt-uncert.",         100,     0,  0.5 ) );
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
	    h_dv_assoctrk_d0_phi        .push_back( book( name, hDVassoctrk + "_d0_phi",        hDVassoctrkstr + " phi",           100,  -3.5,  3.5,
							  hDVassoctrkstr + " d0 [mm]",            100,  -300,  300 ) );
	    h_dv_assoctrk_eta_phi       .push_back( book( name, hDVassoctrk + "_eta_phi",       hDVassoctrkstr + " phi",           100,  -3.5,  3.5,
							  hDVassoctrkstr + " eta",                100,  -3.5,  3.5 ) );
	    h_dv_assoctrk_phi_eta       .push_back( book( name, hDVassoctrk + "_phi_eta",       hDVassoctrkstr + " eta",           100,  -3.5,  3.5,
							  hDVassoctrkstr + " phi",                100,  -3.5,  3.5 ) );
	  }
	} // end if abcdcutOnly
	
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
	    h_njtrkdv_n                   .push_back( book( name, ntrkDV    + "_n",           "n " + ntrkDVstr + "s",                    15, 0,   15 ) );
	    if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
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
	      if ( m_histoInfoSwitch->m_vtxOverallTrk ) {
		h_njtrkdv_sumd0           .push_back( book( name, ntrkDVsum + "d0",           ntrkDVsumstr + " |d0| [mm]",              100, 0,  500 ) );
		h_njtrkdv_sumz0           .push_back( book( name, ntrkDVsum + "z0",           ntrkDVsumstr + " |z0| [mm]",              100, 0, 2000 ) );
		h_njtrkdv_sumP            .push_back( book( name, ntrkDVsum + "P",            ntrkDVsumstr + " |q/p| [e/GeV]",          100, 0,    5 ) );
		h_njtrkdv_sumd0_sv        .push_back( book( name, ntrkDVsum + "d0_sv",        ntrkDVsumstr + " |d0| wrt SV [mm]",       100, 0,   50 ) );
		h_njtrkdv_sumz0_sv        .push_back( book( name, ntrkDVsum + "z0_sv",        ntrkDVsumstr + " |z0| wrt SV [mm]",       100, 0,  150 ) );
		h_njtrkdv_sumP_sv         .push_back( book( name, ntrkDVsum + "P_sv",         ntrkDVsumstr + " |q/p| wrt SV [e/GeV]",   100, 0,    5 ) );
		h_njtrkdv_sumsqrtd0       .push_back( book( name, ntrkDVsum + "sqrtd0",       ntrkDVsumstr + " sqrt |d0| [mm]",         100, 0, 22.5 ) );
		h_njtrkdv_sumsqrtz0       .push_back( book( name, ntrkDVsum + "sqrtz0",       ntrkDVsumstr + " sqrt |z0| [mm]",         100, 0,   45 ) );
		h_njtrkdv_sumsqrtP        .push_back( book( name, ntrkDVsum + "sqrtP",        ntrkDVsumstr + " sqrt |q/p| [e/GeV]",     100, 0, 2.25 ) );
		h_njtrkdv_sumsqrtd0_sv    .push_back( book( name, ntrkDVsum + "sqrtd0_sv",    ntrkDVsumstr + " sqrt |d0| wrt SV [mm]",  100, 0,    7 ) );
		h_njtrkdv_sumsqrtz0_sv    .push_back( book( name, ntrkDVsum + "sqrtz0_sv",    ntrkDVsumstr + " sqrt |z0| wrt SV [mm]",  100, 0,12.25 ) );
		h_njtrkdv_sumsqrtP_sv     .push_back( book( name, ntrkDVsum + "sqrtP_sv",     ntrkDVsumstr + " sqrt |q/p| wrt SV [e/GeV]",100,0,2.25 ) );
		h_njtrkdv_mind0           .push_back( book( name, ntrkDVmin + "d0",           ntrkDVminstr + " |d0| [mm]",              100, 0,  200 ) );
		h_njtrkdv_minz0           .push_back( book( name, ntrkDVmin + "z0",           ntrkDVminstr + " |z0| [mm]",              100, 0, 1000 ) );
		h_njtrkdv_minP            .push_back( book( name, ntrkDVmin + "P",            ntrkDVminstr + " |q/p| [e/GeV]",          100, 0,    1 ) );
		h_njtrkdv_mind0_sv        .push_back( book( name, ntrkDVmin + "d0_sv",        ntrkDVminstr + " |d0| wrt SV [mm]",       100, 0,   15 ) );
		h_njtrkdv_minz0_sv        .push_back( book( name, ntrkDVmin + "z0_sv",        ntrkDVminstr + " |z0| wrt SV [mm]",       100, 0,   50 ) );
		h_njtrkdv_minP_sv         .push_back( book( name, ntrkDVmin + "P_sv",         ntrkDVminstr + " |q/p| wrt SV [e/GeV]",   100, 0,    1 ) );
		h_njtrkdv_minsqrtd0       .push_back( book( name, ntrkDVmin + "sqrtd0",       ntrkDVminstr + " sqrt |d0| [mm]",         100, 0,   14 ) );
		h_njtrkdv_minsqrtz0       .push_back( book( name, ntrkDVmin + "sqrtz0",       ntrkDVminstr + " sqrt |z0| [mm]",         100, 0,   32 ) );
		h_njtrkdv_minsqrtP        .push_back( book( name, ntrkDVmin + "sqrtP",        ntrkDVminstr + " sqrt |q/p| [e/GeV]",     100, 0,    1 ) );
		h_njtrkdv_minsqrtd0_sv    .push_back( book( name, ntrkDVmin + "sqrtd0_sv",    ntrkDVminstr + " sqrt |d0| wrt SV [mm]",  100, 0,    4 ) );
		h_njtrkdv_minsqrtz0_sv    .push_back( book( name, ntrkDVmin + "sqrtz0_sv",    ntrkDVminstr + " sqrt |z0| wrt SV [mm]",  100, 0,    7 ) );
		h_njtrkdv_minsqrtP_sv     .push_back( book( name, ntrkDVmin + "sqrtP_sv",     ntrkDVminstr + " sqrt |q/p| wrt SV [e/GeV]",100,0,   1 ) );
		h_njtrkdv_maxd0           .push_back( book( name, ntrkDVmax + "d0",           ntrkDVmaxstr + " |d0| [mm]",              100, 0,  300 ) );
		h_njtrkdv_maxz0           .push_back( book( name, ntrkDVmax + "z0",           ntrkDVmaxstr + " |z0| [mm]",              100, 0, 1500 ) );
		h_njtrkdv_maxP            .push_back( book( name, ntrkDVmax + "P",            ntrkDVmaxstr + " |q/p| [e/GeV]",          100, 0,  1.1 ) );
		h_njtrkdv_maxd0_sv        .push_back( book( name, ntrkDVmax + "d0_sv",        ntrkDVmaxstr + " |d0| wrt SV [mm]",       100, 0,   30 ) );
		h_njtrkdv_maxz0_sv        .push_back( book( name, ntrkDVmax + "z0_sv",        ntrkDVmaxstr + " |z0| wrt SV [mm]",       100, 0,  100 ) );
		h_njtrkdv_maxP_sv         .push_back( book( name, ntrkDVmax + "P_sv",         ntrkDVmaxstr + " |q/p| wrt SV [e/GeV]",   100, 0,  1.1 ) );
		h_njtrkdv_maxsqrtd0       .push_back( book( name, ntrkDVmax + "sqrtd0",       ntrkDVmaxstr + " sqrt |d0| [mm]",         100, 0, 17.5 ) );
		h_njtrkdv_maxsqrtz0       .push_back( book( name, ntrkDVmax + "sqrtz0",       ntrkDVmaxstr + " sqrt |z0| [mm]",         100, 0,   40 ) );
		h_njtrkdv_maxsqrtP        .push_back( book( name, ntrkDVmax + "sqrtP",        ntrkDVmaxstr + " sqrt |q/p| [e/GeV]",     100, 0,    1 ) );
		h_njtrkdv_maxsqrtd0_sv    .push_back( book( name, ntrkDVmax + "sqrtd0_sv",    ntrkDVmaxstr + " sqrt |d0| wrt SV [mm]",  100, 0,  5.5 ) );
		h_njtrkdv_maxsqrtz0_sv    .push_back( book( name, ntrkDVmax + "sqrtz0_sv",    ntrkDVmaxstr + " sqrt |z0| wrt SV [mm]",  100, 0,   10 ) );
		h_njtrkdv_maxsqrtP_sv     .push_back( book( name, ntrkDVmax + "sqrtP_sv",     ntrkDVmaxstr + " sqrt |q/p| wrt SV [e/GeV]",100,0,   1 ) );
	      }
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
	    } // end if not abcdcutOnly
	  } // end loop over numVtxTrks
	  h_ntrkdv_n                 .push_back( h_njtrkdv_n               );
	  if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
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
	    if ( m_histoInfoSwitch->m_vtxOverallTrk ) {
	      h_ntrkdv_sumd0         .push_back( h_njtrkdv_sumd0           );
	      h_ntrkdv_sumz0         .push_back( h_njtrkdv_sumz0           );
	      h_ntrkdv_sumP          .push_back( h_njtrkdv_sumP            );
	      h_ntrkdv_sumd0_sv      .push_back( h_njtrkdv_sumd0_sv        );
	      h_ntrkdv_sumz0_sv      .push_back( h_njtrkdv_sumz0_sv        );
	      h_ntrkdv_sumP_sv       .push_back( h_njtrkdv_sumP_sv         );
	      h_ntrkdv_sumsqrtd0     .push_back( h_njtrkdv_sumsqrtd0       );
	      h_ntrkdv_sumsqrtz0     .push_back( h_njtrkdv_sumsqrtz0       );
	      h_ntrkdv_sumsqrtP      .push_back( h_njtrkdv_sumsqrtP        );
	      h_ntrkdv_sumsqrtd0_sv  .push_back( h_njtrkdv_sumsqrtd0_sv    );
	      h_ntrkdv_sumsqrtz0_sv  .push_back( h_njtrkdv_sumsqrtz0_sv    );
	      h_ntrkdv_sumsqrtP_sv   .push_back( h_njtrkdv_sumsqrtP_sv     );
	      h_ntrkdv_mind0         .push_back( h_njtrkdv_mind0           );
	      h_ntrkdv_minz0         .push_back( h_njtrkdv_minz0           );
	      h_ntrkdv_minP          .push_back( h_njtrkdv_minP            );
	      h_ntrkdv_mind0_sv      .push_back( h_njtrkdv_mind0_sv        );
	      h_ntrkdv_minz0_sv      .push_back( h_njtrkdv_minz0_sv        );
	      h_ntrkdv_minP_sv       .push_back( h_njtrkdv_minP_sv         );
	      h_ntrkdv_minsqrtd0     .push_back( h_njtrkdv_minsqrtd0       );
	      h_ntrkdv_minsqrtz0     .push_back( h_njtrkdv_minsqrtz0       );
	      h_ntrkdv_minsqrtP      .push_back( h_njtrkdv_minsqrtP        );
	      h_ntrkdv_minsqrtd0_sv  .push_back( h_njtrkdv_minsqrtd0_sv    );
	      h_ntrkdv_minsqrtz0_sv  .push_back( h_njtrkdv_minsqrtz0_sv    );
	      h_ntrkdv_minsqrtP_sv   .push_back( h_njtrkdv_minsqrtP_sv     );
	      h_ntrkdv_maxd0         .push_back( h_njtrkdv_maxd0           );
	      h_ntrkdv_maxz0         .push_back( h_njtrkdv_maxz0           );
	      h_ntrkdv_maxP          .push_back( h_njtrkdv_maxP            );
	      h_ntrkdv_maxd0_sv      .push_back( h_njtrkdv_maxd0_sv        );
	      h_ntrkdv_maxz0_sv      .push_back( h_njtrkdv_maxz0_sv        );
	      h_ntrkdv_maxP_sv       .push_back( h_njtrkdv_maxP_sv         );
	      h_ntrkdv_maxsqrtd0     .push_back( h_njtrkdv_maxsqrtd0       );
	      h_ntrkdv_maxsqrtz0     .push_back( h_njtrkdv_maxsqrtz0       );
	      h_ntrkdv_maxsqrtP      .push_back( h_njtrkdv_maxsqrtP        );
	      h_ntrkdv_maxsqrtd0_sv  .push_back( h_njtrkdv_maxsqrtd0_sv    );
	      h_ntrkdv_maxsqrtz0_sv  .push_back( h_njtrkdv_maxsqrtz0_sv    );
	      h_ntrkdv_maxsqrtP_sv   .push_back( h_njtrkdv_maxsqrtP_sv     );
	    }
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
	  } // end if not abcdcutOnly
	} // end if m_numVtxTrks
      } // end loop over DV types
      h_DV_n                          .push_back( h_dv_n                      );
      if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
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
	h_DV_H                        .push_back( h_dv_H                      );
	h_DV_H_s                      .push_back( h_dv_H_s                    );
	h_DV_H_xs                     .push_back( h_dv_H_xs                   );
	h_DV_Ht                       .push_back( h_dv_Ht                     );
	h_DV_Ht_s                     .push_back( h_dv_Ht_s                   );
	h_DV_Ht_xs                    .push_back( h_dv_Ht_xs                  );
	h_DV_minOpAng                 .push_back( h_dv_minOpAng               );
	h_DV_maxOpAng                 .push_back( h_dv_maxOpAng               );
	h_DV_chi2                     .push_back( h_dv_chi2                   );
	h_DV_chi2_s                   .push_back( h_dv_chi2_s                 );
	h_DV_ntrk                     .push_back( h_dv_ntrk                   );
	h_DV_ntrk_final               .push_back( h_dv_ntrk_final             );
	h_DV_ntrk_sel                 .push_back( h_dv_ntrk_sel               );
	h_DV_ntrk_assoc               .push_back( h_dv_ntrk_assoc             );
	h_DV_ntrk_lrt                 .push_back( h_dv_ntrk_lrt               );
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
	  h_DV_assoctrk_d0            .push_back( h_dv_assoctrk_d0            );
	  h_DV_assoctrk_eta           .push_back( h_dv_assoctrk_eta           );
	  h_DV_assoctrk_phi           .push_back( h_dv_assoctrk_phi           );
	}
	if ( m_histoInfoSwitch->m_vtxOverallTrk ) {
	  h_DV_sumd0                  .push_back( h_dv_sumd0                  );
	  h_DV_sumz0                  .push_back( h_dv_sumz0                  );
	  h_DV_sumP                   .push_back( h_dv_sumP                   );
	  h_DV_sumd0_sv               .push_back( h_dv_sumd0_sv               );
	  h_DV_sumz0_sv               .push_back( h_dv_sumz0_sv               );
	  h_DV_sumP_sv                .push_back( h_dv_sumP_sv                );
	  h_DV_sumsqrtd0              .push_back( h_dv_sumsqrtd0              );
	  h_DV_sumsqrtz0              .push_back( h_dv_sumsqrtz0              );
	  h_DV_sumsqrtP               .push_back( h_dv_sumsqrtP               );
	  h_DV_sumsqrtd0_sv           .push_back( h_dv_sumsqrtd0_sv           );
	  h_DV_sumsqrtz0_sv           .push_back( h_dv_sumsqrtz0_sv           );
	  h_DV_sumsqrtP_sv            .push_back( h_dv_sumsqrtP_sv            );
	  h_DV_mind0                  .push_back( h_dv_mind0                  );
	  h_DV_minz0                  .push_back( h_dv_minz0                  );
	  h_DV_mind0_s                .push_back( h_dv_mind0_s                );
	  h_DV_minz0_s                .push_back( h_dv_minz0_s                );
	  h_DV_minP                   .push_back( h_dv_minP                   );
	  h_DV_mind0_sv               .push_back( h_dv_mind0_sv               );
	  h_DV_minz0_sv               .push_back( h_dv_minz0_sv               );
	  h_DV_minP_sv                .push_back( h_dv_minP_sv                );
	  h_DV_minsqrtd0              .push_back( h_dv_minsqrtd0              );
	  h_DV_minsqrtz0              .push_back( h_dv_minsqrtz0              );
	  h_DV_minsqrtP               .push_back( h_dv_minsqrtP               );
	  h_DV_minsqrtd0_sv           .push_back( h_dv_minsqrtd0_sv           );
	  h_DV_minsqrtz0_sv           .push_back( h_dv_minsqrtz0_sv           );
	  h_DV_minsqrtP_sv            .push_back( h_dv_minsqrtP_sv            );
	  h_DV_maxd0                  .push_back( h_dv_maxd0                  );
	  h_DV_maxz0                  .push_back( h_dv_maxz0                  );
	  h_DV_maxP                   .push_back( h_dv_maxP                   );
	  h_DV_maxd0_sv               .push_back( h_dv_maxd0_sv               );
	  h_DV_maxz0_sv               .push_back( h_dv_maxz0_sv               );
	  h_DV_maxP_sv                .push_back( h_dv_maxP_sv                );
	  h_DV_maxsqrtd0              .push_back( h_dv_maxsqrtd0              );
	  h_DV_maxsqrtz0              .push_back( h_dv_maxsqrtz0              );
	  h_DV_maxsqrtP               .push_back( h_dv_maxsqrtP               );
	  h_DV_maxsqrtd0_sv           .push_back( h_dv_maxsqrtd0_sv           );
	  h_DV_maxsqrtz0_sv           .push_back( h_dv_maxsqrtz0_sv           );
	  h_DV_maxsqrtP_sv            .push_back( h_dv_maxsqrtP_sv            );
	}
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
	  h_DV_minSqrterrd0_s         .push_back( h_dv_minSqrterrd0_s         );
	  h_DV_minSqrterrz0_s         .push_back( h_dv_minSqrterrz0_s         );
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
	  h_DV_y_x                    .push_back( h_dv_y_x                    );
	  h_DV_z_r                    .push_back( h_dv_z_r                    );
	  h_DV_r_z                    .push_back( h_dv_r_z                    );
	  h_DV_r_phi                  .push_back( h_dv_r_phi                  );
	  h_DV_rzphi                  .push_back( h_dv_rzphi                  );
	  h_DV_mass_r                 .push_back( h_dv_mass_r                 );
	  h_DV_z_chi2                 .push_back( h_dv_z_chi2                 );
	  h_DV_r_chi2                 .push_back( h_dv_r_chi2                 );
	  h_DV_mass_chi2              .push_back( h_dv_mass_chi2              );
	  h_DV_y_x_s                  .push_back( h_dv_y_x_s                  );
	  h_DV_z_r_s                  .push_back( h_dv_z_r_s                  );
	  h_DV_r_z_s                  .push_back( h_dv_r_z_s                  );
	  h_DV_r_phi_s                .push_back( h_dv_r_phi_s                );
	  h_DV_rzphi_s                .push_back( h_dv_rzphi_s                );
	  h_DV_mass_r_s               .push_back( h_dv_mass_r_s               );
	  h_DV_z_chi2_s               .push_back( h_dv_z_chi2_s               );
	  h_DV_r_chi2_s               .push_back( h_dv_r_chi2_s               );
	  h_DV_mass_chi2_s            .push_back( h_dv_mass_chi2_s            );
	  if ( m_histoInfoSwitch->m_vtxOverallTrk ) {
	    h_DV_mind0_r              .push_back( h_dv_mind0_r                );
	    h_DV_minz0_z              .push_back( h_dv_minz0_z                );
	    h_DV_mind0z0              .push_back( h_dv_mind0z0                );
	    h_DV_mind0_r_s            .push_back( h_dv_mind0_r_s              );
	    h_DV_minz0_z_s            .push_back( h_dv_minz0_z_s              );
	    h_DV_mind0z0_s            .push_back( h_dv_mind0z0_s              );
	  }
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
	  h_DV_minSqrterrd0_mind0     .push_back( h_dv_minSqrterrd0_mind0     );
	  h_DV_minSqrterrz0_minz0     .push_back( h_dv_minSqrterrz0_minz0     );
	  h_DV_minSqrterrd0z0         .push_back( h_dv_minSqrterrd0z0         );
	  h_DV_minSqrterrd0_mind0_s   .push_back( h_dv_minSqrterrd0_mind0_s   );
	  h_DV_minSqrterrz0_minz0_s   .push_back( h_dv_minSqrterrz0_minz0_s   );
	  h_DV_minSqrterrd0z0_s       .push_back( h_dv_minSqrterrd0z0_s       );
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
	  h_DV_assoctrk_d0_phi        .push_back( h_dv_assoctrk_d0_phi        );
	  h_DV_assoctrk_eta_phi       .push_back( h_dv_assoctrk_eta_phi       );
	  h_DV_assoctrk_phi_eta       .push_back( h_dv_assoctrk_phi_eta       );
	}
      } // end if not abcdcutOnly
      if ( m_numVtxTrks ) {
	h_ntrkDV_n                    .push_back( h_ntrkdv_n                  );
	if ( !m_histoInfoSwitch->m_abcdcutOnly ) {
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
	  if ( m_histoInfoSwitch->m_vtxOverallTrk ) {
	    h_ntrkDV_sumd0            .push_back( h_ntrkdv_sumd0              );
	    h_ntrkDV_sumz0            .push_back( h_ntrkdv_sumz0              );
	    h_ntrkDV_sumP             .push_back( h_ntrkdv_sumP               );
	    h_ntrkDV_sumd0_sv         .push_back( h_ntrkdv_sumd0_sv           );
	    h_ntrkDV_sumz0_sv         .push_back( h_ntrkdv_sumz0_sv           );
	    h_ntrkDV_sumP_sv          .push_back( h_ntrkdv_sumP_sv            );
	    h_ntrkDV_sumsqrtd0        .push_back( h_ntrkdv_sumsqrtd0          );
	    h_ntrkDV_sumsqrtz0        .push_back( h_ntrkdv_sumsqrtz0          );
	    h_ntrkDV_sumsqrtP         .push_back( h_ntrkdv_sumsqrtP           );
	    h_ntrkDV_sumsqrtd0_sv     .push_back( h_ntrkdv_sumsqrtd0_sv       );
	    h_ntrkDV_sumsqrtz0_sv     .push_back( h_ntrkdv_sumsqrtz0_sv       );
	    h_ntrkDV_sumsqrtP_sv      .push_back( h_ntrkdv_sumsqrtP_sv        );
	    h_ntrkDV_mind0            .push_back( h_ntrkdv_mind0              );
	    h_ntrkDV_minz0            .push_back( h_ntrkdv_minz0              );
	    h_ntrkDV_minP             .push_back( h_ntrkdv_minP               );
	    h_ntrkDV_mind0_sv         .push_back( h_ntrkdv_mind0_sv           );
	    h_ntrkDV_minz0_sv         .push_back( h_ntrkdv_minz0_sv           );
	    h_ntrkDV_minP_sv          .push_back( h_ntrkdv_minP_sv            );
	    h_ntrkDV_minsqrtd0        .push_back( h_ntrkdv_minsqrtd0          );
	    h_ntrkDV_minsqrtz0        .push_back( h_ntrkdv_minsqrtz0          );
	    h_ntrkDV_minsqrtP         .push_back( h_ntrkdv_minsqrtP           );
	    h_ntrkDV_minsqrtd0_sv     .push_back( h_ntrkdv_minsqrtd0_sv       );
	    h_ntrkDV_minsqrtz0_sv     .push_back( h_ntrkdv_minsqrtz0_sv       );
	    h_ntrkDV_minsqrtP_sv      .push_back( h_ntrkdv_minsqrtP_sv        );
	    h_ntrkDV_maxd0            .push_back( h_ntrkdv_maxd0              );
	    h_ntrkDV_maxz0            .push_back( h_ntrkdv_maxz0              );
	    h_ntrkDV_maxP             .push_back( h_ntrkdv_maxP               );
	    h_ntrkDV_maxd0_sv         .push_back( h_ntrkdv_maxd0_sv           );
	    h_ntrkDV_maxz0_sv         .push_back( h_ntrkdv_maxz0_sv           );
	    h_ntrkDV_maxP_sv          .push_back( h_ntrkdv_maxP_sv            );
	    h_ntrkDV_maxsqrtd0        .push_back( h_ntrkdv_maxsqrtd0          );
	    h_ntrkDV_maxsqrtz0        .push_back( h_ntrkdv_maxsqrtz0          );
	    h_ntrkDV_maxsqrtP         .push_back( h_ntrkdv_maxsqrtP           );
	    h_ntrkDV_maxsqrtd0_sv     .push_back( h_ntrkdv_maxsqrtd0_sv       );
	    h_ntrkDV_maxsqrtz0_sv     .push_back( h_ntrkdv_maxsqrtz0_sv       );
	    h_ntrkDV_maxsqrtP_sv      .push_back( h_ntrkdv_maxsqrtP_sv        );
	  }
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
	} // end if not abcdcutOnly
      } // end if m_numVtxTrks
    } // end if not truthOnly


    // --- CUTFLOWS --- //
    if ( m_histoInfoSwitch->m_cutflow || m_histoInfoSwitch->m_abcdcutOnly ) {
      // --> jet cutflow
      std::vector<std::vector<TH1F*>> h_evt_testcutflow_j,           h_evt_testcutflow_leadj;
      std::vector<std::vector<TH1F*>> h_evt_testcutflow_svp4j,       h_evt_testcutflow_leadsvp4j;
      std::vector<std::vector<TH1F*>> h_evt_testcutflow_svptj,       h_evt_testcutflow_leadsvptj;
      std::vector<std::vector<TH1F*>> h_evt_testcutflow_svhtj,       h_evt_testcutflow_leadsvhtj;
      std::vector<std::vector<TH1F*>> h_evt_testcutflow_svhj,        h_evt_testcutflow_leadsvhj;
      std::vector<std::vector<TH1F*>> h_evt_testcutflow_svntrkj,     h_evt_testcutflow_leadsvntrkj;
      std::vector<std::vector<TH1F*>> h_evt_testcutflow_svnjtrkj,    h_evt_testcutflow_leadsvnjtrkj;
      std::vector<std::vector<TH1F*>> h_evt_testcutflow_svtrkj,      h_evt_testcutflow_leadsvtrkj;
      std::vector<std::vector<TH1F*>> h_evt_testcutflow_svnj,        h_evt_testcutflow_leadsvnj;
      std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_j,        h_evt_testcutfloweff_leadj;
      std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svp4j,    h_evt_testcutfloweff_leadsvp4j;
      std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svptj,    h_evt_testcutfloweff_leadsvptj;
      std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svhtj,    h_evt_testcutfloweff_leadsvhtj;
      std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svhj,     h_evt_testcutfloweff_leadsvhj;
      std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svntrkj,  h_evt_testcutfloweff_leadsvntrkj;
      std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svnjtrkj, h_evt_testcutfloweff_leadsvnjtrkj;
      std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svtrkj,   h_evt_testcutfloweff_leadsvtrkj;
      std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svnj,     h_evt_testcutfloweff_leadsvnj;
      std::vector<std::vector<TH1F*>> h_evt_cutflow_ej,              h_evt_cutflow_leadej;
      std::vector<std::vector<TH1F*>> h_evt_cutfloweff_ej,           h_evt_cutfloweff_leadej;
      std::vector<std::string> cj,    clj;
      std::vector<std::string> cjstr, cljstr;
      cj     .push_back(  "Jet" );
      cjstr  .push_back( " jet" );
      clj    .push_back(  "LeadJet"  );
      cljstr .push_back( " lead jet" );
      if ( m_mc && m_histoInfoSwitch->m_jetTruth ) {
	std::vector<std::string> mJ    = { "DarkMatch",    "Nomatch"   };
	std::vector<std::string> mJstr = { "dark-matched", "unmatched" };
	for ( size_t imj = 0; imj != mJ.size(); ++imj ) {
	  cj     .push_back( mJ    [imj] +       "Jet" );
	  cjstr  .push_back( mJstr [imj] +      " jet" );
	  clj    .push_back( mJ    [imj] +   "LeadJet" );
	  cljstr .push_back( mJstr [imj] + " lead jet" );
	}
      }
      for ( size_t icj = 0; icj != cj.size(); ++icj ) {
	if ( m_nType1Js ) {
	  unsigned ncjt         = ( m_nType1Js - m_nType1SVJs ) / m_LJix;
	  unsigned ncjv         = m_nType1SVJs / m_nTypeJSVs    / m_LJix;
	  unsigned ncjsvp4      = m_svP4J_ix    / m_LJix + ncjt;
	  unsigned ncjsvpt      = m_svPtJ_ix    / m_LJix + ncjt;
	  unsigned ncjsvht      = m_svHtJ_ix    / m_LJix + ncjt;
	  unsigned ncjsvh       = m_svHJ_ix     / m_LJix + ncjt;
	  unsigned ncjsvnt      = m_svNtrkJ_ix  / m_LJix + ncjt;
	  unsigned ncjsvnjt     = m_svNjtrkJ_ix / m_LJix + ncjt;
	  unsigned ncjsvt       = m_svTrkJ_ix   / m_LJix + ncjt;
	  unsigned ncjsvn       = m_svNJ_ix     / m_LJix + ncjt;
	  unsigned nbin_cj      = ncjv                   + ncjt;
	  unsigned nbin_cjpt    = m_nJSVpt .size()       + ncjt;
	  unsigned nbin_cjh     = m_nJSVh  .size()       + ncjt;
	  unsigned nbin_cjsvtrk = m_nJSVtrk.size()       + ncjt;
	  unsigned nbin_cjsv    = m_nJSV   .size()       + ncjt;
	  std::vector<TH1F*> h_evt_testcut_j,           h_evt_testcut_leadj;
	  std::vector<TH1F*> h_evt_testcut_svp4j,       h_evt_testcut_leadsvp4j;
	  std::vector<TH1F*> h_evt_testcut_svptj,       h_evt_testcut_leadsvptj;
	  std::vector<TH1F*> h_evt_testcut_svhtj,       h_evt_testcut_leadsvhtj;
	  std::vector<TH1F*> h_evt_testcut_svhj,        h_evt_testcut_leadsvhj;
	  std::vector<TH1F*> h_evt_testcut_svntrkj,     h_evt_testcut_leadsvntrkj;
	  std::vector<TH1F*> h_evt_testcut_svnjtrkj,    h_evt_testcut_leadsvnjtrkj;
	  std::vector<TH1F*> h_evt_testcut_svtrkj,      h_evt_testcut_leadsvtrkj;
	  std::vector<TH1F*> h_evt_testcut_svnj,        h_evt_testcut_leadsvnj;
	  std::vector<TH1F*> h_evt_testcuteff_j,        h_evt_testcuteff_leadj;
	  std::vector<TH1F*> h_evt_testcuteff_svp4j,    h_evt_testcuteff_leadsvp4j;
	  std::vector<TH1F*> h_evt_testcuteff_svptj,    h_evt_testcuteff_leadsvptj;
	  std::vector<TH1F*> h_evt_testcuteff_svhtj,    h_evt_testcuteff_leadsvhtj;
	  std::vector<TH1F*> h_evt_testcuteff_svhj,     h_evt_testcuteff_leadsvhj;
	  std::vector<TH1F*> h_evt_testcuteff_svntrkj,  h_evt_testcuteff_leadsvntrkj;
	  std::vector<TH1F*> h_evt_testcuteff_svnjtrkj, h_evt_testcuteff_leadsvnjtrkj;
	  std::vector<TH1F*> h_evt_testcuteff_svtrkj,   h_evt_testcuteff_leadsvtrkj;
	  std::vector<TH1F*> h_evt_testcuteff_svnj,     h_evt_testcuteff_leadsvnj;
	  for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
	    std::string jsvlow = JSV[ijsv]; jsvlow[0] = tolower(jsvlow[0]);
	    // all test cuts
	    h_evt_testcut_j
	      .push_back(   book( name, "evt_testCutflow_"           + jsvlow + cj [icj],
	    			  JSVstr[ijsv]              + cjstr [icj] + " test cutflow",             nbin_cj,      0, nbin_cj      ) );
	    h_evt_testcut_leadj
	      .push_back(   book( name, "evt_testCutflow_"           + jsvlow + clj[icj],
	    			  JSVstr[ijsv]              + cljstr[icj] + " test cutflow",             nbin_cj,      0, nbin_cj      ) );
	    h_evt_testcuteff_j
	      .push_back(   book( name, "evt_testCutflowEfficiency_" + jsvlow + cj [icj],
	    			  JSVstr[ijsv]              + cjstr [icj] + " test cutflow efficiency",  nbin_cj,      0, nbin_cj      ) );
	    h_evt_testcuteff_leadj
	      .push_back(   book( name, "evt_testCutflowEfficiency_" + jsvlow + clj[icj],
	    			  JSVstr[ijsv]              + cljstr[icj] + " test cutflow efficiency",  nbin_cj,      0, nbin_cj      ) );
	    // nsv-pt
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvP4Jets ) {
	      h_evt_testcut_svp4j
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "P4" + cj [icj],
				  JSVstr[ijsv] + "-pt "     + cjstr [icj] + " test cutflow",            nbin_cjpt,    0, nbin_cjpt    ) );
	      h_evt_testcut_leadsvp4j
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "P4" + clj[icj],
				  JSVstr[ijsv] + "-pt "     + cljstr[icj] + " test cutflow",            nbin_cjpt,    0, nbin_cjpt    ) );
	      h_evt_testcuteff_svp4j
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "P4" + cj [icj],
				  JSVstr[ijsv] + "-pt "     + cjstr [icj] + " test cutflow efficiency", nbin_cjpt,    0, nbin_cjpt    ) );
	      h_evt_testcuteff_leadsvp4j
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "P4" + clj[icj],
				  JSVstr[ijsv] + "-pt "     + cljstr[icj] + " test cutflow efficiency", nbin_cjpt,    0, nbin_cjpt    ) );
	    }
	    // nsv-sum-pt
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvPtJets ) {
	      h_evt_testcut_svptj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "Pt" + cj [icj],
				  JSVstr[ijsv] + "-sum-pt " + cjstr [icj] + " test cutflow",            nbin_cjpt,    0, nbin_cjpt    ) );
	      h_evt_testcut_leadsvptj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "Pt" + clj[icj],
				  JSVstr[ijsv] + "-sum-pt " + cljstr[icj] + " test cutflow",            nbin_cjpt,    0, nbin_cjpt    ) );
	      h_evt_testcuteff_svptj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "Pt" + cj [icj],
				  JSVstr[ijsv] + "-sum-pt " + cjstr [icj] + " test cutflow efficiency", nbin_cjpt,    0, nbin_cjpt    ) );
	      h_evt_testcuteff_leadsvptj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "Pt" + clj[icj],
				  JSVstr[ijsv] + "-sum-pt " + cljstr[icj] + " test cutflow efficiency", nbin_cjpt,    0, nbin_cjpt    ) );
	    }
	    // nsv-sum-Ht
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHtJets ) {
	      h_evt_testcut_svhtj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "Ht" + cj [icj],
				  JSVstr[ijsv] + "-sum-Ht " + cjstr [icj] + " test cutflow",            nbin_cjpt,    0, nbin_cjpt    ) );
	      h_evt_testcut_leadsvhtj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "Ht" + clj[icj],
				  JSVstr[ijsv] + "-sum-Ht " + cljstr[icj] + " test cutflow",            nbin_cjpt,    0, nbin_cjpt    ) );
	      h_evt_testcuteff_svhtj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "Ht" + cj [icj],
				  JSVstr[ijsv] + "-sum-Ht " + cjstr [icj] + " test cutflow efficiency", nbin_cjpt,    0, nbin_cjpt    ) );
	      h_evt_testcuteff_leadsvhtj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "Ht" + clj[icj],
				  JSVstr[ijsv] + "-sum-Ht " + cljstr[icj] + " test cutflow efficiency", nbin_cjpt,    0, nbin_cjpt    ) );
	    }
	    // nsv-sum-H
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHJets ) {
	      h_evt_testcut_svhj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "H" + cj [icj],
				  JSVstr[ijsv] + "-sum-H "  + cjstr [icj] + " test cutflow",            nbin_cjh,     0, nbin_cjh     ) );
	      h_evt_testcut_leadsvhj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "H" + clj[icj],
				  JSVstr[ijsv] + "-sum-H "  + cljstr[icj] + " test cutflow",            nbin_cjh,     0, nbin_cjh     ) );
	      h_evt_testcuteff_svhj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "H" + cj [icj],
				  JSVstr[ijsv] + "-sum-H "  + cjstr [icj] + " test cutflow efficiency", nbin_cjh,     0, nbin_cjh     ) );
	      h_evt_testcuteff_leadsvhj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "H" + clj[icj],
				  JSVstr[ijsv] + "-sum-H "  + cljstr[icj] + " test cutflow efficiency", nbin_cjh,     0, nbin_cjh     ) );
	    }
	    // nsv-ntrk
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNtrkJets ) {
	      h_evt_testcut_svntrkj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "Ntrk" + cj [icj],
				  JSVstr[ijsv] + "-Ntrk "   + cjstr [icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	      h_evt_testcut_leadsvntrkj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "Ntrk" + clj[icj],
				  JSVstr[ijsv] + "-Ntrk "   + cljstr[icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	      h_evt_testcuteff_svntrkj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "Ntrk" + cj [icj],
				  JSVstr[ijsv] + "-Ntrk "   + cjstr [icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	      h_evt_testcuteff_leadsvntrkj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "Ntrk" + clj[icj],
				  JSVstr[ijsv] + "-Ntrk "   + cljstr[icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    }
	    // nsv-njtrk
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNjtrkJets ) {
	      h_evt_testcut_svnjtrkj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "Njtrk" + cj [icj],
				  JSVstr[ijsv] + "-Njtrk "  + cjstr [icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	      h_evt_testcut_leadsvnjtrkj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "Njtrk" + clj[icj],
				  JSVstr[ijsv] + "-Njtrk "  + cljstr[icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	      h_evt_testcuteff_svnjtrkj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "Njtrk" + cj [icj],
				  JSVstr[ijsv] + "-Njtrk "  + cjstr [icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	      h_evt_testcuteff_leadsvnjtrkj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "Njtrk" + clj[icj],
				  JSVstr[ijsv] + "-Njtrk "  + cljstr[icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    }
	    // nsv-trk
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvTrkJets   ) {
	      h_evt_testcut_svtrkj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "Trk" + cj[icj],
				  JSVstr[ijsv] + "-trk "    + cjstr [icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	      h_evt_testcut_leadsvtrkj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "Trk" + clj[icj],
				  JSVstr[ijsv] + "-trk "    + cljstr[icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	      h_evt_testcuteff_svtrkj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "Trk" + cj [icj],
				  JSVstr[ijsv] + "-trk "    + cjstr [icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	      h_evt_testcuteff_leadsvtrkj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "Trk" + clj[icj],
				  JSVstr[ijsv] + "-trk "    + cljstr[icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    }
	    // nsv
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvJets      ) {
	      h_evt_testcut_svnj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "N" + cj [icj],
				  JSVstr[ijsv] + " "        + cjstr[icj] + " test cutflow",             nbin_cjsv,    0, nbin_cjsv    ) );
	      h_evt_testcut_leadsvnj
		.push_back( book( name, "evt_testCutflow_"           + jsvlow + "N" + clj[icj],
				  JSVstr[ijsv] + " "        + cljstr[icj] + " test cutflow",            nbin_cjsv,    0, nbin_cjsv    ) );
	      h_evt_testcuteff_svnj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "N" + cj [icj],
				  JSVstr[ijsv] + " "        + cjstr [icj] + " test cutflow efficiency", nbin_cjsv,    0, nbin_cjsv    ) );
	      h_evt_testcuteff_leadsvnj
		.push_back( book( name, "evt_testCutflowEfficiency_" + jsvlow + "N" + clj[icj],
				  JSVstr[ijsv] + " "        + cljstr[icj] + " test cutflow efficiency", nbin_cjsv,    0, nbin_cjsv    ) );
	    }
	    // --> label bins
	    for ( unsigned i1j = 0; i1j != m_nType1Js/m_LJix; ++i1j ) {
	      std::string tmpjstr = hJstr[i1j*m_LJix];
	      if ( tmpjstr.empty() ) tmpjstr = "all";
	      // all test cuts
	      if ( ( i1j < ncjt ) ||
		   ( i1j >=  ncjsvp4 + m_nJSVpt .size()*ijsv && i1j <  ncjsvp4 + m_nJSVpt .size() * (ijsv+1) ) ||
		   ( i1j >=  ncjsvpt + m_nJSVpt .size()*ijsv && i1j <  ncjsvpt + m_nJSVpt .size() * (ijsv+1) ) ||
		   ( i1j >=  ncjsvht + m_nJSVpt .size()*ijsv && i1j <  ncjsvht + m_nJSVpt .size() * (ijsv+1) ) ||
		   ( i1j >=   ncjsvh + m_nJSVh  .size()*ijsv && i1j <   ncjsvh + m_nJSVh  .size() * (ijsv+1) ) ||
		   ( i1j >=  ncjsvnt + m_nJSVtrk.size()*ijsv && i1j <  ncjsvnt + m_nJSVtrk.size() * (ijsv+1) ) ||
		   ( i1j >= ncjsvnjt + m_nJSVtrk.size()*ijsv && i1j < ncjsvnjt + m_nJSVtrk.size() * (ijsv+1) ) ||
		   ( i1j >=   ncjsvt + m_nJSVtrk.size()*ijsv && i1j <   ncjsvt + m_nJSVtrk.size() * (ijsv+1) ) ||
		   ( i1j >=   ncjsvn + m_nJSV   .size()*ijsv && i1j <   ncjsvn + m_nJSV   .size() * (ijsv+1) ) ) {
		h_evt_testcut_j              [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		h_evt_testcut_leadj          [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		h_evt_testcuteff_j           [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		h_evt_testcuteff_leadj       [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
	      }
	      // nsv-pt
	      if ( ( i1j < ncjt ) || ( i1j >=  ncjsvp4+m_nJSVpt .size()*ijsv && i1j <  ncjsvp4+m_nJSVpt .size()*(ijsv+1) ) )
		if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvP4Jets    ) {
		  h_evt_testcut_svp4j        [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcut_leadsvp4j    [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_svp4j     [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_leadsvp4j [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		}
	      // nsv-sum-pt
	      if ( ( i1j < ncjt ) || ( i1j >=  ncjsvpt+m_nJSVpt .size()*ijsv && i1j <  ncjsvpt+m_nJSVpt .size()*(ijsv+1) ) )
		if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvPtJets    ) {
		  h_evt_testcut_svptj        [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcut_leadsvptj    [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_svptj     [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_leadsvptj [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		}
	      // nsv-sum-Ht
	      if ( ( i1j < ncjt ) || ( i1j >=  ncjsvht+m_nJSVpt .size()*ijsv && i1j <  ncjsvht+m_nJSVpt .size()*(ijsv+1) ) )
		if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHtJets    ) {
		  h_evt_testcut_svhtj        [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcut_leadsvhtj    [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_svhtj     [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_leadsvhtj [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		}
	      // nsv-sum-H
	      if ( ( i1j < ncjt ) || ( i1j >=   ncjsvh+m_nJSVh  .size()*ijsv && i1j <   ncjsvh+m_nJSVh  .size()*(ijsv+1) ) )
		if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHJets    ) {
		  h_evt_testcut_svhj         [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcut_leadsvhj     [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_svhj      [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_leadsvhj  [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		}
	      // nsv-ntrk
	      if ( ( i1j < ncjt ) || ( i1j >=  ncjsvnt+m_nJSVtrk.size()*ijsv && i1j <  ncjsvnt+m_nJSVtrk.size()*(ijsv+1) ) )
		if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNtrkJets  ) {
		  h_evt_testcut_svntrkj         [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcut_leadsvntrkj     [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_svntrkj      [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_leadsvntrkj  [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		}
	      // nsv-njtrk
	      if ( ( i1j < ncjt ) || ( i1j >= ncjsvnjt+m_nJSVtrk.size()*ijsv && i1j < ncjsvnjt+m_nJSVtrk.size()*(ijsv+1) ) )
		if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNjtrkJets ) {
		  h_evt_testcut_svnjtrkj        [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcut_leadsvnjtrkj    [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_svnjtrkj     [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_leadsvnjtrkj [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		}
	      // nsv-trk
	      if ( ( i1j < ncjt ) || ( i1j >=   ncjsvt+m_nJSVtrk.size()*ijsv && i1j <   ncjsvt+m_nJSVtrk.size()*(ijsv+1) ) )
		if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvTrkJets   ) {
		  h_evt_testcut_svtrkj          [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcut_leadsvtrkj      [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_svtrkj       [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_leadsvtrkj   [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		}
	      // nsv
	      if ( ( i1j < ncjt ) || ( i1j >=   ncjsvn+m_nJSV   .size()*ijsv && i1j <   ncjsvn+m_nJSV   .size()*(ijsv+1) ) )
		if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvJets      ) {
		  h_evt_testcut_svnj            [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcut_leadsvnj        [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_svnj         [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		  h_evt_testcuteff_leadsvnj     [ijsv] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
		}
	    }
	  } // end loop over JSVs
	  // all test cuts
	  h_evt_testcutflow_j                 .push_back( h_evt_testcut_j               );
	  h_evt_testcutflow_leadj             .push_back( h_evt_testcut_leadj           );
	  h_evt_testcutfloweff_j              .push_back( h_evt_testcuteff_j            );
	  h_evt_testcutfloweff_leadj          .push_back( h_evt_testcuteff_leadj        );
	  // nsv-pt
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvP4Jets    ) {
	    h_evt_testcutflow_svp4j           .push_back( h_evt_testcut_svp4j           );
	    h_evt_testcutflow_leadsvp4j       .push_back( h_evt_testcut_leadsvp4j       );
	    h_evt_testcutfloweff_svp4j        .push_back( h_evt_testcuteff_svp4j        );
	    h_evt_testcutfloweff_leadsvp4j    .push_back( h_evt_testcuteff_leadsvp4j    );
	  }
	  // nsv-sum-pt
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvPtJets    ) {
	    h_evt_testcutflow_svptj           .push_back( h_evt_testcut_svptj           );
	    h_evt_testcutflow_leadsvptj       .push_back( h_evt_testcut_leadsvptj       );
	    h_evt_testcutfloweff_svptj        .push_back( h_evt_testcuteff_svptj        );
	    h_evt_testcutfloweff_leadsvptj    .push_back( h_evt_testcuteff_leadsvptj    );
	  }
	  // nsv-sum-Ht
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHtJets    ) {
	    h_evt_testcutflow_svhtj           .push_back( h_evt_testcut_svhtj           );
	    h_evt_testcutflow_leadsvhtj       .push_back( h_evt_testcut_leadsvhtj       );
	    h_evt_testcutfloweff_svhtj        .push_back( h_evt_testcuteff_svhtj        );
	    h_evt_testcutfloweff_leadsvhtj    .push_back( h_evt_testcuteff_leadsvhtj    );
	  }
	  // nsv-sum-H
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHJets     ) {
	    h_evt_testcutflow_svhj            .push_back( h_evt_testcut_svhj            );
	    h_evt_testcutflow_leadsvhj        .push_back( h_evt_testcut_leadsvhj        );
	    h_evt_testcutfloweff_svhj         .push_back( h_evt_testcuteff_svhj         );
	    h_evt_testcutfloweff_leadsvhj     .push_back( h_evt_testcuteff_leadsvhj     );
	  }
	  // nsv-ntrk
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNtrkJets  ) {
	    h_evt_testcutflow_svntrkj         .push_back( h_evt_testcut_svntrkj         );
	    h_evt_testcutflow_leadsvntrkj     .push_back( h_evt_testcut_leadsvntrkj     );
	    h_evt_testcutfloweff_svntrkj      .push_back( h_evt_testcuteff_svntrkj      );
	    h_evt_testcutfloweff_leadsvntrkj  .push_back( h_evt_testcuteff_leadsvntrkj  );
	  }
	  // nsv-njtrk
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNjtrkJets ) {
	    h_evt_testcutflow_svnjtrkj        .push_back( h_evt_testcut_svnjtrkj        );
	    h_evt_testcutflow_leadsvnjtrkj    .push_back( h_evt_testcut_leadsvnjtrkj    );
	    h_evt_testcutfloweff_svnjtrkj     .push_back( h_evt_testcuteff_svnjtrkj     );
	    h_evt_testcutfloweff_leadsvnjtrkj .push_back( h_evt_testcuteff_leadsvnjtrkj );
	  }
	  // nsv-trk
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvTrkJets   ) {
	    h_evt_testcutflow_svtrkj          .push_back( h_evt_testcut_svtrkj          );
	    h_evt_testcutflow_leadsvtrkj      .push_back( h_evt_testcut_leadsvtrkj      );
	    h_evt_testcutfloweff_svtrkj       .push_back( h_evt_testcuteff_svtrkj       );
	    h_evt_testcutfloweff_leadsvtrkj   .push_back( h_evt_testcuteff_leadsvtrkj   );
	  }
	  // nsv
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvJets      ) {
	    h_evt_testcutflow_svnj            .push_back( h_evt_testcut_svnj            );
	    h_evt_testcutflow_leadsvnj        .push_back( h_evt_testcut_leadsvnj        );
	    h_evt_testcutfloweff_svnj         .push_back( h_evt_testcuteff_svnj         );
	    h_evt_testcutfloweff_leadsvnj     .push_back( h_evt_testcuteff_leadsvnj     );
	  }
	} // end if m_nType1Js

	// --> emerging jet cuts
	unsigned nbin_ej = hEJstr.size() / m_LJix / JSV.size();
	std::vector<TH1F*> h_evt_cut_ej,    h_evt_cut_leadej;
	std::vector<TH1F*> h_evt_cuteff_ej, h_evt_cuteff_leadej;
	for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
	  h_evt_cut_ej
	    .push_back( book( name, "evt_cutflow_emerging" + JSV[ijsv] + cj [icj],
			      "Emerging (" + JSV[ijsv] + ") " + cjstr [icj] + " cutflow",            nbin_ej, 0, nbin_ej ) );
	  h_evt_cut_leadej
	    .push_back( book( name, "evt_cutflow_emerging" + JSV[ijsv] + clj[icj],
			      "Emerging (" + JSV[ijsv] + ") " + cljstr[icj] + " cutflow",            nbin_ej, 0, nbin_ej ) );
	  h_evt_cuteff_ej
	    .push_back( book( name, "evt_cutflowEfficiency_emerging" + JSV[ijsv] + cj [icj],
			      "Emerging (" + JSV[ijsv] + ") " + cjstr [icj] + " cutflow efficiency", nbin_ej, 0, nbin_ej ) );
	  h_evt_cuteff_leadej
	    .push_back( book( name, "evt_cutflowEfficiency_emerging" + JSV[ijsv] + clj[icj],
			      "Emerging (" + JSV[ijsv] + ") " + cljstr[icj] + " cutflow efficiency", nbin_ej, 0, nbin_ej ) );
	  // --> label bins
	  for ( unsigned iej = 0; iej != nbin_ej; ++iej ) {
	    std::string tmpjstr = hEJstr[iej*m_LJix];
	    if ( tmpjstr.empty() ) tmpjstr = "all";
	    h_evt_cut_ej        [ijsv] ->GetXaxis()->FindBin( (tmpjstr ).c_str() );
	    h_evt_cut_leadej    [ijsv] ->GetXaxis()->FindBin( (tmpjstr ).c_str() );
	    h_evt_cuteff_ej     [ijsv] ->GetXaxis()->FindBin( (tmpjstr ).c_str() );
	    h_evt_cuteff_leadej [ijsv] ->GetXaxis()->FindBin( (tmpjstr ).c_str() );
	  }
	}
	h_evt_cutflow_ej        .push_back( h_evt_cut_ej        );
	h_evt_cutflow_leadej    .push_back( h_evt_cut_leadej    );
	h_evt_cutfloweff_ej     .push_back( h_evt_cuteff_ej     );
	h_evt_cutfloweff_leadej .push_back( h_evt_cuteff_leadej );
	
      } // end loop over cutflow types
      
      if ( m_nType1Js ) {
	h_evt_testCutflow_jet                        .push_back( h_evt_testcutflow_j               );
	h_evt_testCutflow_leadJet                    .push_back( h_evt_testcutflow_leadj           );
	h_evt_testCutflowEfficiency_jet              .push_back( h_evt_testcutfloweff_j            );
	h_evt_testCutflowEfficiency_leadJet          .push_back( h_evt_testcutfloweff_leadj        );
	if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvP4Jets    ) {
	  h_evt_testCutflow_svP4Jet                  .push_back( h_evt_testcutflow_svp4j           );
	  h_evt_testCutflow_leadSvP4Jet              .push_back( h_evt_testcutflow_leadsvp4j       );
	  h_evt_testCutflowEfficiency_svP4Jet        .push_back( h_evt_testcutfloweff_svp4j        );
	  h_evt_testCutflowEfficiency_leadSvP4Jet    .push_back( h_evt_testcutfloweff_leadsvp4j    );
	}
	if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvPtJets    ) {
	  h_evt_testCutflow_svPtJet                  .push_back( h_evt_testcutflow_svptj           );
	  h_evt_testCutflow_leadSvPtJet              .push_back( h_evt_testcutflow_leadsvptj       );
	  h_evt_testCutflowEfficiency_svPtJet        .push_back( h_evt_testcutfloweff_svptj        );
	  h_evt_testCutflowEfficiency_leadSvPtJet    .push_back( h_evt_testcutfloweff_leadsvptj    );
	}
	if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHtJets    ) {
	  h_evt_testCutflow_svHtJet                  .push_back( h_evt_testcutflow_svhtj           );
	  h_evt_testCutflow_leadSvHtJet              .push_back( h_evt_testcutflow_leadsvhtj       );
	  h_evt_testCutflowEfficiency_svHtJet        .push_back( h_evt_testcutfloweff_svhtj        );
	  h_evt_testCutflowEfficiency_leadSvHtJet    .push_back( h_evt_testcutfloweff_leadsvhtj    );
	}
	if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHJets     ) {
	  h_evt_testCutflow_svHJet                   .push_back( h_evt_testcutflow_svhj            );
	  h_evt_testCutflow_leadSvHJet               .push_back( h_evt_testcutflow_leadsvhj        );
	  h_evt_testCutflowEfficiency_svHJet         .push_back( h_evt_testcutfloweff_svhj         );
	  h_evt_testCutflowEfficiency_leadSvHJet     .push_back( h_evt_testcutfloweff_leadsvhj     );
	}
	if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNtrkJets  ) {
	  h_evt_testCutflow_svNtrkJet                .push_back( h_evt_testcutflow_svntrkj         );
	  h_evt_testCutflow_leadSvNtrkJet            .push_back( h_evt_testcutflow_leadsvntrkj     );
	  h_evt_testCutflowEfficiency_svNtrkJet      .push_back( h_evt_testcutfloweff_svntrkj      );
	  h_evt_testCutflowEfficiency_leadSvNtrkJet  .push_back( h_evt_testcutfloweff_leadsvntrkj  ); 
	}
	if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNjtrkJets ) {
	  h_evt_testCutflow_svNjtrkJet               .push_back( h_evt_testcutflow_svnjtrkj        );
	  h_evt_testCutflow_leadSvNjtrkJet           .push_back( h_evt_testcutflow_leadsvnjtrkj    );
	  h_evt_testCutflowEfficiency_svNjtrkJet     .push_back( h_evt_testcutfloweff_svnjtrkj     );
	  h_evt_testCutflowEfficiency_leadSvNjtrkJet .push_back( h_evt_testcutfloweff_leadsvnjtrkj );
	}
	if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvTrkJets   ) {
	  h_evt_testCutflow_svTrkJet                 .push_back( h_evt_testcutflow_svtrkj          );
	  h_evt_testCutflow_leadSvTrkJet             .push_back( h_evt_testcutflow_leadsvtrkj      );
	  h_evt_testCutflowEfficiency_svTrkJet       .push_back( h_evt_testcutfloweff_svtrkj       );
	  h_evt_testCutflowEfficiency_leadSvTrkJet   .push_back( h_evt_testcutfloweff_leadsvtrkj   );
	}
	if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvJets      ) {
	  h_evt_testCutflow_svNJet                   .push_back( h_evt_testcutflow_svnj            );
	  h_evt_testCutflow_leadSvNJet               .push_back( h_evt_testcutflow_leadsvnj        );
	  h_evt_testCutflowEfficiency_svNJet         .push_back( h_evt_testcutfloweff_svnj         );
	  h_evt_testCutflowEfficiency_leadSvNJet     .push_back( h_evt_testcutfloweff_leadsvnj     );
	}
      }
      h_evt_cutflow_emergingJet                      .push_back( h_evt_cutflow_ej                  );
      h_evt_cutflow_leadEmergingJet                  .push_back( h_evt_cutflow_leadej              );
      h_evt_cutflowEfficiency_emergingJet            .push_back( h_evt_cutfloweff_ej               );
      h_evt_cutflowEfficiency_leadEmergingJet        .push_back( h_evt_cutfloweff_leadej           );
      
      // --> DV cutflow
      // --> ADD "ALL" BIN (so we can see how initial cleaning cuts affect cutflow)
      std::vector<TH1F*> h_evt_testcutflow_dv;
      std::vector<TH1F*> h_evt_testcutfloweff_dv;
      std::vector<TH1F*> h_evt_cutflow_dv;
      std::vector<TH1F*> h_evt_cutfloweff_dv;
      std::vector<std::string> cdv;
      std::vector<std::string> cdvstr;
      std::string bdv    = baseDV;    bdv[0] = std::tolower(bdv[0]);
      std::string bdvstr = baseDVstr; bdvstr.pop_back();
      cdv    .push_back( bdv    +  "DV" );
      cdvstr .push_back( bdvstr + " DV" );
      if ( m_mc && m_histoInfoSwitch->m_vtxTruth ) {
	//std::vector<std::string> mDV     = { "darkPion",  "kshort",  "nomatch"   };
	//std::vector<std::string> mDVstr  = { "dark pion", "k-short", "unmatched" };
	std::vector<std::string> mDV     = { "darkPion"  };
	std::vector<std::string> mDVstr  = { "dark pion" };
	for ( size_t imdv = 0; imdv != mDV.size(); ++imdv ) {
	  cdv    .push_back( mDV    [imdv] +  "DV" );
	  cdvstr .push_back( mDVstr [imdv] + " DV" );
	}
      }
      for ( size_t icdv = 0; icdv != cdv.size(); ++icdv ) {
	if ( m_nType1DVs ) {
	  h_evt_testcutflow_dv
	    .push_back( book( name, "evt_testCutflow_"          +cdv[icdv], cdvstr[icdv]+" test cutflow",            m_nType1DVs, 0, m_nType1DVs ) );
	  h_evt_testcutfloweff_dv
	    .push_back( book( name, "evt_testCutflowEfficiency_"+cdv[icdv], cdvstr[icdv]+" test cutflow efficiency", m_nType1DVs, 0, m_nType1DVs ) );
	  for ( unsigned i1dv = 0; i1dv != m_nType1DVs; ++i1dv ) {
	    std::string tmpdvstr = hDVstr[ i1dv ]; tmpdvstr.pop_back();
	    h_evt_testcutflow_dv    [icdv] ->GetXaxis()->FindBin( ( tmpdvstr ).c_str() );
	    h_evt_testcutfloweff_dv [icdv] ->GetXaxis()->FindBin( ( tmpdvstr ).c_str() );
	  }
	}
	h_evt_cutflow_dv
	  .push_back( book( name, "evt_cutflow_"          +cdv[icdv], cdvstr[icdv]+" cutflow",            hGDVstr.size(), 0, hGDVstr.size() ) );
	h_evt_cutfloweff_dv
	  .push_back( book( name, "evt_cutflowEfficiency_"+cdv[icdv], cdvstr[icdv]+" cutflow efficiency", hGDVstr.size(), 0, hGDVstr.size() ) );
	for ( const auto& gdv : hGDVstr ) {
	  std::string tmpdvstr = gdv; tmpdvstr.pop_back();
	  h_evt_cutflow_dv        [icdv] ->GetXaxis()->FindBin( ( tmpdvstr ).c_str() );
	  h_evt_cutfloweff_dv     [icdv] ->GetXaxis()->FindBin( ( tmpdvstr ).c_str() );
	}
      }
      if ( m_nType1DVs ) {
	h_evt_testCutflow_DV           .push_back( h_evt_testcutflow_dv    );
	h_evt_testCutflowEfficiency_DV .push_back( h_evt_testcutfloweff_dv );
      }
      h_evt_cutflow_DV                 .push_back( h_evt_cutflow_dv        );
      h_evt_cutflowEfficiency_DV       .push_back( h_evt_cutfloweff_dv     );
      
      // --> event-level cutflows
      // --> --> n-jets
      std::vector<TH1F*> h_evt_cutflow_nj;
      std::vector<TH1F*> h_evt_cutflow_nleadj;
      std::vector<TH1F*> h_evt_cutfloweff_nj;
      std::vector<TH1F*> h_evt_cutfloweff_nleadj;
      std::vector<TH1F*> h_evt_cutflowtoteff_nj;
      std::vector<TH1F*> h_evt_cutflowtoteff_nleadj;
      for ( size_t ibj = 0; ibj != m_nTypeBJs/m_LJix; ++ibj ) {
	std::string hj     = hJ   [ibj*m_LJix  ] + "Jet";
	std::string hlj    = hJ   [ibj*m_LJix+1] + "Jet";
	std::string hjstr  = hJstr[ibj*m_LJix  ];
	std::string hljstr = hJstr[ibj*m_LJix+1];
	if ( !hjstr.empty()  ) hjstr  += " ";
	if ( !hljstr.empty() ) hljstr += " ";
	h_evt_cutflow_nj
	  .push_back( book( name, "evt_cutflow_N"                + hj,  "N " + hjstr  + "jet cutflow",                  m_nJets+1, 0, m_nJets+1 ) );
	h_evt_cutflow_nleadj
	  .push_back( book( name, "evt_cutflow_N"                + hlj, "N " + hljstr + "jet cutflow",                  m_nJets+1, 0, m_nJets+1 ) );
	h_evt_cutfloweff_nj
	  .push_back( book( name, "evt_cutflowEfficiency_N"      + hj,  "N " + hjstr  + "jet cutflow efficiency",       m_nJets+1, 0, m_nJets+1 ) );
	h_evt_cutfloweff_nleadj
	  .push_back( book( name, "evt_cutflowEfficiency_N"      + hlj, "N " + hljstr + "jet cutflow efficiency",       m_nJets+1, 0, m_nJets+1 ) );
	h_evt_cutflowtoteff_nj
	  .push_back( book( name, "evt_cutflowTotalEfficiency_N" + hj,  "N " + hjstr  + "jet cutflow total efficiency", m_nJets+1, 0, m_nJets+1 ) );
	h_evt_cutflowtoteff_nleadj
	  .push_back( book( name, "evt_cutflowTotalEfficiency_N" + hlj, "N " + hljstr + "jet cutflow total efficiency", m_nJets+1, 0, m_nJets+1 ) );
	for ( int inj = 0; inj != m_nJets+1; ++inj ) {
	  h_evt_cutflow_nj           [ibj] ->GetXaxis()->FindBin( ( "NJet = "     + std::to_string(inj) ).c_str() );
	  h_evt_cutflow_nleadj       [ibj] ->GetXaxis()->FindBin( ( "NLeadJet = " + std::to_string(inj) ).c_str() );
	  h_evt_cutfloweff_nj        [ibj] ->GetXaxis()->FindBin( ( "NJet = "     + std::to_string(inj) ).c_str() );
	  h_evt_cutfloweff_nleadj    [ibj] ->GetXaxis()->FindBin( ( "NLeadJet = " + std::to_string(inj) ).c_str() );
	  h_evt_cutflowtoteff_nj     [ibj] ->GetXaxis()->FindBin( ( "NJet = "     + std::to_string(inj) ).c_str() );
	  h_evt_cutflowtoteff_nleadj [ibj] ->GetXaxis()->FindBin( ( "NLeadJet = " + std::to_string(inj) ).c_str() );
	}
      }
      h_evt_cutflow_NJet                    .push_back( h_evt_cutflow_nj           );
      h_evt_cutflow_NLeadJet                .push_back( h_evt_cutflow_nleadj       );
      h_evt_cutflowEfficiency_NJet          .push_back( h_evt_cutfloweff_nj        );
      h_evt_cutflowEfficiency_NLeadJet      .push_back( h_evt_cutfloweff_nleadj    );
      h_evt_cutflowTotalEfficiency_NJet     .push_back( h_evt_cutflowtoteff_nj     );
      h_evt_cutflowTotalEfficiency_NLeadJet .push_back( h_evt_cutflowtoteff_nleadj );
      
      // --> --> n-dvs
      std::vector<TH1F*> h_evt_cutflow_ndv;
      std::vector<TH1F*> h_evt_cutfloweff_ndv;
      std::vector<TH1F*> h_evt_cutflowtoteff_ndv;
      std::vector<std::vector<TH1F*>> h_evt_cutflow_ntrkndv;
      std::vector<std::vector<TH1F*>> h_evt_cutfloweff_ntrkndv;
      std::vector<std::vector<TH1F*>> h_evt_cutflowtoteff_ntrkndv;
      for ( size_t ibdv = 0; ibdv != m_nTypeBDVs; ++ibdv ) { // skip truth-matched DVs
	std::string hdv    = hDV   [ibdv] + "DV";
	std::string hdvstr = hDVstr[ibdv]; hdvstr.pop_back(); hdvstr += " DV";
	h_evt_cutflow_ndv
	  .push_back( book( name, "evt_cutflow_N"                + hdv, "N " + hdvstr + " cutflow",                  m_ndv+1, 0, m_ndv+1 ) );
	h_evt_cutfloweff_ndv
	  .push_back( book( name, "evt_cutflowEfficiency_N"      + hdv, "N " + hdvstr + " cutflow efficiency",       m_ndv+1, 0, m_ndv+1 ) );
	h_evt_cutflowtoteff_ndv
	  .push_back( book( name, "evt_cutflowTotalEfficiency_N" + hdv, "N " + hdvstr + " cutflow total efficiency", m_ndv+1, 0, m_ndv+1 ) );
	for ( int indv = 0; indv != m_ndv+1; ++indv ) {
	  h_evt_cutflow_ndv       [ibdv] ->GetXaxis()->FindBin( ( "NDV = " + std::to_string(indv) ).c_str() );
	  h_evt_cutfloweff_ndv    [ibdv] ->GetXaxis()->FindBin( ( "NDV = " + std::to_string(indv) ).c_str() );
	  h_evt_cutflowtoteff_ndv [ibdv] ->GetXaxis()->FindBin( ( "NDV = " + std::to_string(indv) ).c_str() );
	}
	if ( m_numVtxTrks ) {
	  std::vector<TH1F*> h_evt_cutflow_njtrkndv;
	  std::vector<TH1F*> h_evt_cutfloweff_njtrkndv;
	  std::vector<TH1F*> h_evt_cutflowtoteff_njtrkndv;
	  for ( int j = 1; j != m_numVtxTrks; ++j ) {
	    std::string ntrk      = std::to_string(j+1);
	    std::string jdv       = hdv; jdv[0] = std::toupper(jdv[0]);
	    std::string ntrkndv    = ntrk + "trkN" + jdv;
	    std::string ntrkndvstr = ntrk + "-track N-" + hdvstr;
	    h_evt_cutflow_njtrkndv
	      .push_back( book( name, "evt_cutflow_"                + ntrkndv, ntrkndvstr + " cutflow",                  m_ndv+1, 0, m_ndv+1 ) );
	    h_evt_cutfloweff_njtrkndv
	      .push_back( book( name, "evt_cutflowEfficiency_"      + ntrkndv, ntrkndvstr + " cutflow efficiency",       m_ndv+1, 0, m_ndv+1 ) );
	    h_evt_cutflowtoteff_njtrkndv
	      .push_back( book( name, "evt_cutflowTotalEfficiency_" + ntrkndv, ntrkndvstr + " cutflow total efficiency", m_ndv+1, 0, m_ndv+1 ) );
	    for ( int jndv = 0; jndv != m_ndv+1; ++jndv ) {
	      h_evt_cutflow_njtrkndv       [j-1] ->GetXaxis()->FindBin( ( "NDV = " + std::to_string(jndv) ).c_str() );
	      h_evt_cutfloweff_njtrkndv    [j-1] ->GetXaxis()->FindBin( ( "NDV = " + std::to_string(jndv) ).c_str() );
	      h_evt_cutflowtoteff_njtrkndv [j-1] ->GetXaxis()->FindBin( ( "NDV = " + std::to_string(jndv) ).c_str() );
	    }
	  }
	  h_evt_cutflow_ntrkndv       .push_back( h_evt_cutflow_njtrkndv       );
	  h_evt_cutfloweff_ntrkndv    .push_back( h_evt_cutfloweff_njtrkndv    );
	  h_evt_cutflowtoteff_ntrkndv .push_back( h_evt_cutflowtoteff_njtrkndv );
	}
      }
      h_evt_cutflow_NDV                    .push_back( h_evt_cutflow_ndv           );
      h_evt_cutflowEfficiency_NDV          .push_back( h_evt_cutfloweff_ndv        );
      h_evt_cutflowTotalEfficiency_NDV     .push_back( h_evt_cutflowtoteff_ndv     );
      if ( m_numVtxTrks ) {
	h_evt_cutflow_ntrkNDV                .push_back( h_evt_cutflow_ntrkndv       );
	h_evt_cutflowEfficiency_ntrkNDV      .push_back( h_evt_cutfloweff_ntrkndv    );
	h_evt_cutflowTotalEfficiency_ntrkNDV .push_back( h_evt_cutflowtoteff_ntrkndv );
      }

      // --> --> n-jet-x
      std::string ljstr  = "N-leading jet";
      std::string cstr   = " cutflow";
      std::string cestr  = " cutflow efficiency";
      std::string ctestr = " cutflow total efficiency";
      int nbin_njet = m_njetht_cut.size();
      h_evt_cutflow_NJetHt                            .push_back( book( name, "evt_cutflow_NJetHt",
									ljstr + " H_{T} [GeV]"                     + cstr,   nbin_njet, 0, nbin_njet ) );
      h_evt_cutflowEfficiency_NJetHt                  .push_back( book( name, "evt_cutflowEfficiency_NJetHt",
									ljstr + " H_{T} [GeV]"                     + cestr,  nbin_njet, 0, nbin_njet ) );
      h_evt_cutflowTotalEfficiency_NJetHt             .push_back( book( name, "evt_cutflowTotalEfficiency_NJetHt",
									ljstr + " H_{T} [GeV]"                     + ctestr, nbin_njet, 0, nbin_njet ) );
      if ( !m_histoInfoSwitch->m_truthOnly ) {
	h_evt_cutflow_NJetPt                          .push_back( book( name, "evt_cutflow_NJetPt",
									ljstr + " p_{T} [GeV]"                     + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_NJetSumM                        .push_back( book( name, "evt_cutflow_NJetSumM",
									ljstr + " sum-mass [GeV]"                  + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_NJetJJ_pt                       .push_back( book( name, "evt_cutflow_NJetJJ_pt",
									ljstr + " min-diff-invM dijet p_{T} [GeV]" + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_NJetJJ_m                        .push_back( book( name, "evt_cutflow_NJetJJ_m",
									ljstr + " min-diff-invM dijet mass [GeV]"  + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_NJetJJmindpt_pt                 .push_back( book( name, "evt_cutflow_NJetJJmindpt_pt",
									ljstr + " min-diff-pt dijet p_{T} [GeV]"   + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_NJetJJmindpt_m                  .push_back( book( name, "evt_cutflow_NJetJJmindpt_m",
									ljstr + " min-diff-pt dijet mass [GeV]"    + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_NJetJJmaxdr_pt                  .push_back( book( name, "evt_cutflow_NJetJJmaxdr_pt",
									ljstr + " max-dR dijet p_{T} [GeV]"        + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_NJetJJmaxdr_m                   .push_back( book( name, "evt_cutflow_NJetJJmaxdr_m",
									ljstr + " max-dR dijet mass [GeV]"         + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_avgNJetJJ_pt                    .push_back( book( name, "evt_cutflow_avgNJetJJ_pt",
									ljstr + " average dijet p_{T} [GeV]"       + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_avgNJetJJ_m                     .push_back( book( name, "evt_cutflow_avgNJetJJ_m",
									ljstr + " average dijet mass [GeV]"        + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_maxNJetJJ_pt                    .push_back( book( name, "evt_cutflow_maxNJetJJ_pt",
									ljstr + " max-invM dijet p_{T} [GeV]"      + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_maxNJetJJ_m                     .push_back( book( name, "evt_cutflow_maxNJetJJ_m",
									ljstr + " max-invM dijet mass [GeV]"       + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_maxNJetJJ_sumPt                 .push_back( book( name, "evt_cutflow_maxNJetJJ_sumPt",
									ljstr + " max-invM dijet sum-p_{T} [GeV]"  + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_maxNJetJJ_sumM                  .push_back( book( name, "evt_cutflow_maxNJetJJ_sumM",
									ljstr + " max-invM dijet sum-mass [GeV]"   + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_minNJetJJ_pt                    .push_back( book( name, "evt_cutflow_minNJetJJ_pt",
									ljstr + " min-invM dijet p_{T} [GeV]"      + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_minNJetJJ_m                     .push_back( book( name, "evt_cutflow_minNJetJJ_m",
									ljstr + " min-invM dijet mass [GeV]"       + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_minNJetJJ_sumPt                 .push_back( book( name, "evt_cutflow_minNJetJJ_sumPt",
									ljstr + " min-invM dijet sum-p_{T} [GeV]"  + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_minNJetJJ_sumM                  .push_back( book( name, "evt_cutflow_minNJetJJ_sumM",
									ljstr + " min-invM dijet sum-mass [GeV]"   + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_maxptNJetJJ_pt                  .push_back( book( name, "evt_cutflow_maxptNJetJJ_pt",
									ljstr + " max-pt dijet p_{T} [GeV]"        + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_maxptNJetJJ_m                   .push_back( book( name, "evt_cutflow_maxptNJetJJ_m",
									ljstr + " max-pt dijet mass [GeV]"         + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_maxptNJetJJ_sumPt               .push_back( book( name, "evt_cutflow_maxptNJetJJ_sumPt",
									ljstr + " max-pt dijet sum-p_{T} [GeV]"    + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_maxptNJetJJ_sumM                .push_back( book( name, "evt_cutflow_maxptNJetJJ_sumM",
									ljstr + " max-pt dijet sum-mass [GeV]"     + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_minptNJetJJ_pt                  .push_back( book( name, "evt_cutflow_minptNJetJJ_pt",
									ljstr + " min-pt dijet p_{T} [GeV]"        + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_minptNJetJJ_m                   .push_back( book( name, "evt_cutflow_minptNJetJJ_m",
									ljstr + " min-pt dijet mass [GeV]"         + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_minptNJetJJ_sumPt               .push_back( book( name, "evt_cutflow_minptNJetJJ_sumPt",
									ljstr + " min-pt dijet sum-p_{T} [GeV]"    + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflow_minptNJetJJ_sumM                .push_back( book( name, "evt_cutflow_minptNJetJJ_sumM",
									ljstr + " min-pt dijet sum-mass [GeV]"     + cstr,   nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_NJetPt                .push_back( book( name, "evt_cutflowEfficiency_NJetPt",
									ljstr + " p_{T} [GeV]"                     + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_NJetSumM              .push_back( book( name, "evt_cutflowEfficiency_NJetSumM",
									ljstr + " sum-mass [GeV]"                  + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_NJetJJ_pt             .push_back( book( name, "evt_cutflowEfficiency_NJetJJ_pt",
									ljstr + " min-diff-invM dijet p_{T} [GeV]" + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_NJetJJ_m              .push_back( book( name, "evt_cutflowEfficiency_NJetJJ_m",
									ljstr + " min-diff-invM dijet mass [GeV]"  + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_NJetJJmindpt_pt       .push_back( book( name, "evt_cutflowEfficiency_NJetJJmindpt_pt",
									ljstr + " min-diff-pt dijet p_{T} [GeV]"   + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_NJetJJmindpt_m        .push_back( book( name, "evt_cutflowEfficiency_NJetJJmindpt_m",
									ljstr + " min-diff-pt dijet mass [GeV]"    + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_NJetJJmaxdr_pt        .push_back( book( name, "evt_cutflowEfficiency_NJetJJmaxdr_pt",
									ljstr + " max-dR dijet p_{T} [GeV]"        + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_NJetJJmaxdr_m         .push_back( book( name, "evt_cutflowEfficiency_NJetJJmaxdr_m",
									ljstr + " max-dR dijet mass [GeV]"         + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_avgNJetJJ_pt          .push_back( book( name, "evt_cutflowEfficiency_avgNJetJJ_pt",
									ljstr + " average dijet p_{T} [GeV]"       + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_avgNJetJJ_m           .push_back( book( name, "evt_cutflowEfficiency_avgNJetJJ_m",
									ljstr + " average dijet mass [GeV]"        + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_maxNJetJJ_pt          .push_back( book( name, "evt_cutflowEfficiency_maxNJetJJ_pt",
									ljstr + " max-invM dijet p_{T} [GeV]"      + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_maxNJetJJ_m           .push_back( book( name, "evt_cutflowEfficiency_maxNJetJJ_m",
									ljstr + " max-invM dijet mass [GeV]"       + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_maxNJetJJ_sumPt       .push_back( book( name, "evt_cutflowEfficiency_maxNJetJJ_sumPt",
									ljstr + " max-invM dijet sum-p_{T} [GeV]"  + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_maxNJetJJ_sumM        .push_back( book( name, "evt_cutflowEfficiency_maxNJetJJ_sumM",
									ljstr + " max-invM dijet sum-mass [GeV]"   + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_minNJetJJ_pt          .push_back( book( name, "evt_cutflowEfficiency_minNJetJJ_pt",
									ljstr + " min-invM dijet p_{T} [GeV]"      + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_minNJetJJ_m           .push_back( book( name, "evt_cutflowEfficiency_minNJetJJ_m",
									ljstr + " min-invM dijet mass [GeV]"       + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_minNJetJJ_sumPt       .push_back( book( name, "evt_cutflowEfficiency_minNJetJJ_sumPt",
									ljstr + " min-invM dijet sum-p_{T} [GeV]"  + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_minNJetJJ_sumM        .push_back( book( name, "evt_cutflowEfficiency_minNJetJJ_sumM",
									ljstr + " min-invM dijet sum-mass [GeV]"   + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_maxptNJetJJ_pt        .push_back( book( name, "evt_cutflowEfficiency_maxptNJetJJ_pt",
									ljstr + " max-pt dijet p_{T} [GeV]"        + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_maxptNJetJJ_m         .push_back( book( name, "evt_cutflowEfficiency_maxptNJetJJ_m",
									ljstr + " max-pt dijet mass [GeV]"         + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_maxptNJetJJ_sumPt     .push_back( book( name, "evt_cutflowEfficiency_maxptNJetJJ_sumPt",
									ljstr + " max-pt dijet sum-p_{T} [GeV]"    + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_maxptNJetJJ_sumM      .push_back( book( name, "evt_cutflowEfficiency_maxptNJetJJ_sumM",
									ljstr + " max-pt dijet sum-mass [GeV]"     + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_minptNJetJJ_pt        .push_back( book( name, "evt_cutflowEfficiency_minptNJetJJ_pt",
									ljstr + " min-pt dijet p_{T} [GeV]"        + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_minptNJetJJ_m         .push_back( book( name, "evt_cutflowEfficiency_minptNJetJJ_m",
									ljstr + " min-pt dijet mass [GeV]"         + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_minptNJetJJ_sumPt     .push_back( book( name, "evt_cutflowEfficiency_minptNJetJJ_sumPt",
									ljstr + " min-pt dijet sum-p_{T} [GeV]"    + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowEfficiency_minptNJetJJ_sumM      .push_back( book( name, "evt_cutflowEfficiency_minptNJetJJ_sumM",
									ljstr + " min-pt dijet sum-mass [GeV]"     + cestr,  nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_NJetPt           .push_back( book( name, "evt_cutflowTotalEfficiency_NJetPt",
									ljstr + " p_{T} [GeV]"                     + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_NJetSumM         .push_back( book( name, "evt_cutflowTotalEfficiency_NJetSumM",
									ljstr + " sum-mass [GeV]"                  + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_NJetJJ_pt        .push_back( book( name, "evt_cutflowTotalEfficiency_NJetJJ_pt",
									ljstr + " min-diff-invM dijet p_{T} [GeV]" + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_NJetJJ_m         .push_back( book( name, "evt_cutflowTotalEfficiency_NJetJJ_m",
									ljstr + " min-diff-invM dijet mass [GeV]"  + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_NJetJJmindpt_pt  .push_back( book( name, "evt_cutflowTotalEfficiency_NJetJJmindpt_pt",
									ljstr + " min-diff-pt dijet p_{T} [GeV]"   + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_NJetJJmindpt_m   .push_back( book( name, "evt_cutflowTotalEfficiency_NJetJJmindpt_m",
									ljstr + " min-diff-pt dijet mass [GeV]"    + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_NJetJJmaxdr_pt   .push_back( book( name, "evt_cutflowTotalEfficiency_NJetJJmaxdr_pt",
									ljstr + " max-dR dijet p_{T} [GeV]"        + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_NJetJJmaxdr_m    .push_back( book( name, "evt_cutflowTotalEfficiency_NJetJJmaxdr_m",
									ljstr + " max-dR dijet mass [GeV]"         + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_avgNJetJJ_pt     .push_back( book( name, "evt_cutflowTotalEfficiency_avgNJetJJ_pt",
									ljstr + " average dijet p_{T} [GeV]"       + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_avgNJetJJ_m      .push_back( book( name, "evt_cutflowTotalEfficiency_avgNJetJJ_m",
									ljstr + " average dijet mass [GeV]"        + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_maxNJetJJ_pt     .push_back( book( name, "evt_cutflowTotalEfficiency_maxNJetJJ_pt",
									ljstr + " max-invM dijet p_{T} [GeV]"      + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_maxNJetJJ_m      .push_back( book( name, "evt_cutflowTotalEfficiency_maxNJetJJ_m",
									ljstr + " max-invM dijet mass [GeV]"       + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_maxNJetJJ_sumPt  .push_back( book( name, "evt_cutflowTotalEfficiency_maxNJetJJ_sumPt",
									ljstr + " max-invM dijet sum-p_{T} [GeV]"  + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_maxNJetJJ_sumM   .push_back( book( name, "evt_cutflowTotalEfficiency_maxNJetJJ_sumM",
									ljstr + " max-invM dijet sum-mass [GeV]"   + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_minNJetJJ_pt     .push_back( book( name, "evt_cutflowTotalEfficiency_minNJetJJ_pt",
									ljstr + " min-invM dijet p_{T} [GeV]"      + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_minNJetJJ_m      .push_back( book( name, "evt_cutflowTotalEfficiency_minNJetJJ_m",
									ljstr + " min-invM dijet mass [GeV]"       + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_minNJetJJ_sumPt  .push_back( book( name, "evt_cutflowTotalEfficiency_minNJetJJ_sumPt",
									ljstr + " min-invM dijet sum-p_{T} [GeV]"  + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_minNJetJJ_sumM   .push_back( book( name, "evt_cutflowTotalEfficiency_minNJetJJ_sumM",
									ljstr + " min-invM dijet sum-mass [GeV]"   + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_maxptNJetJJ_pt   .push_back( book( name, "evt_cutflowTotalEfficiency_maxptNJetJJ_pt",
									ljstr + " max-pt dijet p_{T} [GeV]"        + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_maxptNJetJJ_m    .push_back( book( name, "evt_cutflowTotalEfficiency_maxptNJetJJ_m",
									ljstr + " max-pt dijet mass [GeV]"         + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_maxptNJetJJ_sumPt.push_back( book( name, "evt_cutflowTotalEfficiency_maxptNJetJJ_sumPt",
									ljstr + " max-pt dijet sum-p_{T} [GeV]"    + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_maxptNJetJJ_sumM .push_back( book( name, "evt_cutflowTotalEfficiency_maxptNJetJJ_sumM",
									ljstr + " max-pt dijet sum-mass [GeV]"     + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_minptNJetJJ_pt   .push_back( book( name, "evt_cutflowTotalEfficiency_minptNJetJJ_pt",
									ljstr + " min-pt dijet p_{T} [GeV]"        + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_minptNJetJJ_m    .push_back( book( name, "evt_cutflowTotalEfficiency_minptNJetJJ_m",
									ljstr + " min-pt dijet mass [GeV]"         + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_minptNJetJJ_sumPt.push_back( book( name, "evt_cutflowTotalEfficiency_minptNJetJJ_sumPt",
									ljstr + " min-pt dijet sum-p_{T} [GeV]"    + ctestr, nbin_njet, 0, nbin_njet ) );
	h_evt_cutflowTotalEfficiency_minptNJetJJ_sumM .push_back( book( name, "evt_cutflowTotalEfficiency_minptNJetJJ_sumM",
									ljstr + " min-pt dijet sum-mass [GeV]"     + ctestr, nbin_njet, 0, nbin_njet ) );
      }
      for ( int injb = 0; injb != nbin_njet; ++injb ) {
	std::string njetht_cut         = std::to_string(m_njetht_cut        [injb]);
	std::string njetpt_cut         = std::to_string(m_njetpt_cut        [injb]);
	std::string njetsm_cut         = std::to_string(m_njetsm_cut        [injb]);
	std::string njetjj_pt_cut      = std::to_string(m_njetjj_pt_cut     [injb]);
	std::string njetjj_m_cut       = std::to_string(m_njetjj_m_cut      [injb]);
	std::string njetjjpt_pt_cut    = std::to_string(m_njetjjpt_pt_cut   [injb]);
	std::string njetjjpt_m_cut     = std::to_string(m_njetjjpt_m_cut    [injb]);
	std::string njetjjdr_pt_cut    = std::to_string(m_njetjjdr_pt_cut   [injb]);
	std::string njetjjdr_m_cut     = std::to_string(m_njetjjdr_m_cut    [injb]);
	std::string avgnjetjj_pt_cut   = std::to_string(m_avgnjetjj_pt_cut  [injb]);
	std::string avgnjetjj_m_cut    = std::to_string(m_avgnjetjj_m_cut   [injb]);
	std::string maxnjetjj_pt_cut   = std::to_string(m_maxnjetjj_pt_cut  [injb]);
	std::string maxnjetjj_m_cut    = std::to_string(m_maxnjetjj_m_cut   [injb]);
	std::string maxnjetjj_ht_cut   = std::to_string(m_maxnjetjj_ht_cut  [injb]);
	std::string maxnjetjj_sm_cut   = std::to_string(m_maxnjetjj_sm_cut  [injb]);
	std::string minnjetjj_pt_cut   = std::to_string(m_minnjetjj_pt_cut  [injb]);
	std::string minnjetjj_m_cut    = std::to_string(m_minnjetjj_m_cut   [injb]);
	std::string minnjetjj_ht_cut   = std::to_string(m_minnjetjj_ht_cut  [injb]);
	std::string minnjetjj_sm_cut   = std::to_string(m_minnjetjj_sm_cut  [injb]);
	std::string maxptnjetjj_pt_cut = std::to_string(m_maxptnjetjj_pt_cut[injb]);
	std::string maxptnjetjj_m_cut  = std::to_string(m_maxptnjetjj_m_cut [injb]);
	std::string maxptnjetjj_ht_cut = std::to_string(m_maxptnjetjj_ht_cut[injb]);
	std::string maxptnjetjj_sm_cut = std::to_string(m_maxptnjetjj_sm_cut[injb]);
	std::string minptnjetjj_pt_cut = std::to_string(m_minptnjetjj_pt_cut[injb]);
	std::string minptnjetjj_m_cut  = std::to_string(m_minptnjetjj_m_cut [injb]);
	std::string minptnjetjj_ht_cut = std::to_string(m_minptnjetjj_ht_cut[injb]);
	std::string minptnjetjj_sm_cut = std::to_string(m_minptnjetjj_sm_cut[injb]);
	njetht_cut         = njetht_cut        .substr( 0, njetht_cut        .find(".") + 3 );
	njetpt_cut         = njetpt_cut        .substr( 0, njetpt_cut        .find(".") + 3 );
	njetsm_cut         = njetsm_cut        .substr( 0, njetsm_cut        .find(".") + 3 );
	njetjj_pt_cut      = njetjj_pt_cut     .substr( 0, njetjj_pt_cut     .find(".") + 3 );
	njetjj_m_cut       = njetjj_m_cut      .substr( 0, njetjj_m_cut      .find(".") + 3 );
	njetjjpt_pt_cut    = njetjjpt_pt_cut   .substr( 0, njetjjpt_pt_cut   .find(".") + 3 );
	njetjjpt_m_cut     = njetjjpt_m_cut    .substr( 0, njetjjpt_m_cut    .find(".") + 3 );
	njetjjdr_pt_cut    = njetjjdr_pt_cut   .substr( 0, njetjjdr_pt_cut   .find(".") + 3 );
	njetjjdr_m_cut     = njetjjdr_m_cut    .substr( 0, njetjjdr_m_cut    .find(".") + 3 );
	avgnjetjj_pt_cut   = avgnjetjj_pt_cut  .substr( 0, avgnjetjj_pt_cut  .find(".") + 3 );
	avgnjetjj_m_cut    = avgnjetjj_m_cut   .substr( 0, avgnjetjj_m_cut   .find(".") + 3 );
	maxnjetjj_pt_cut   = maxnjetjj_pt_cut  .substr( 0, maxnjetjj_pt_cut  .find(".") + 3 );
	maxnjetjj_m_cut    = maxnjetjj_m_cut   .substr( 0, maxnjetjj_m_cut   .find(".") + 3 );
	maxnjetjj_ht_cut   = maxnjetjj_ht_cut  .substr( 0, maxnjetjj_ht_cut  .find(".") + 3 );
	maxnjetjj_sm_cut   = maxnjetjj_sm_cut  .substr( 0, maxnjetjj_sm_cut  .find(".") + 3 );
	minnjetjj_pt_cut   = minnjetjj_pt_cut  .substr( 0, minnjetjj_pt_cut  .find(".") + 3 );
	minnjetjj_m_cut    = minnjetjj_m_cut   .substr( 0, minnjetjj_m_cut   .find(".") + 3 );
	minnjetjj_ht_cut   = minnjetjj_ht_cut  .substr( 0, minnjetjj_ht_cut  .find(".") + 3 );
	minnjetjj_sm_cut   = minnjetjj_sm_cut  .substr( 0, minnjetjj_sm_cut  .find(".") + 3 );
	maxptnjetjj_pt_cut = maxptnjetjj_pt_cut.substr( 0, maxptnjetjj_pt_cut.find(".") + 3 );
	maxptnjetjj_m_cut  = maxptnjetjj_m_cut .substr( 0, maxptnjetjj_m_cut .find(".") + 3 );
	maxptnjetjj_ht_cut = maxptnjetjj_ht_cut.substr( 0, maxptnjetjj_ht_cut.find(".") + 3 );
	maxptnjetjj_sm_cut = maxptnjetjj_sm_cut.substr( 0, maxptnjetjj_sm_cut.find(".") + 3 );
	minptnjetjj_pt_cut = minptnjetjj_pt_cut.substr( 0, minptnjetjj_pt_cut.find(".") + 3 );
	minptnjetjj_m_cut  = minptnjetjj_m_cut .substr( 0, minptnjetjj_m_cut .find(".") + 3 );
	minptnjetjj_ht_cut = minptnjetjj_ht_cut.substr( 0, minptnjetjj_ht_cut.find(".") + 3 );
	minptnjetjj_sm_cut = minptnjetjj_sm_cut.substr( 0, minptnjetjj_sm_cut.find(".") + 3 );
	if ( injb == 0 && ( region.type == EJsHelper::SEARCH || region.type == EJsHelper::JZ4W_SLICE_SEARCH ) ) njetht_cut = "1000.00";
	h_evt_cutflow_NJetHt                             [ireg] ->GetXaxis()->FindBin( ( "> " + njetht_cut         + " GeV" ).c_str() );
	h_evt_cutflowEfficiency_NJetHt                   [ireg] ->GetXaxis()->FindBin( ( "> " + njetht_cut         + " GeV" ).c_str() );
	h_evt_cutflowTotalEfficiency_NJetHt              [ireg] ->GetXaxis()->FindBin( ( "> " + njetht_cut         + " GeV" ).c_str() );
	if ( !m_histoInfoSwitch->m_truthOnly ) {
	  h_evt_cutflow_NJetPt                           [ireg] ->GetXaxis()->FindBin( ( "> " + njetpt_cut         + " GeV" ).c_str() );
	  h_evt_cutflow_NJetSumM                         [ireg] ->GetXaxis()->FindBin( ( "> " + njetsm_cut         + " GeV" ).c_str() );
	  h_evt_cutflow_NJetJJ_pt                        [ireg] ->GetXaxis()->FindBin( ( "> " + njetjj_pt_cut      + " GeV" ).c_str() );
	  h_evt_cutflow_NJetJJ_m                         [ireg] ->GetXaxis()->FindBin( ( "> " + njetjj_m_cut       + " GeV" ).c_str() );
	  h_evt_cutflow_NJetJJmindpt_pt                  [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjpt_pt_cut    + " GeV" ).c_str() );
	  h_evt_cutflow_NJetJJmindpt_m                   [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjpt_m_cut     + " GeV" ).c_str() );
	  h_evt_cutflow_NJetJJmaxdr_pt                   [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjdr_pt_cut    + " GeV" ).c_str() );
	  h_evt_cutflow_NJetJJmaxdr_m                    [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjdr_m_cut     + " GeV" ).c_str() );
	  h_evt_cutflow_avgNJetJJ_pt                     [ireg] ->GetXaxis()->FindBin( ( "> " + avgnjetjj_pt_cut   + " GeV" ).c_str() );
	  h_evt_cutflow_avgNJetJJ_m                      [ireg] ->GetXaxis()->FindBin( ( "> " + avgnjetjj_m_cut    + " GeV" ).c_str() );
	  h_evt_cutflow_maxNJetJJ_pt                     [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_pt_cut   + " GeV" ).c_str() );
	  h_evt_cutflow_maxNJetJJ_m                      [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_m_cut    + " GeV" ).c_str() );
	  h_evt_cutflow_maxNJetJJ_sumPt                  [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_ht_cut   + " GeV" ).c_str() );
	  h_evt_cutflow_maxNJetJJ_sumM                   [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_sm_cut   + " GeV" ).c_str() );
	  h_evt_cutflow_minNJetJJ_pt                     [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_pt_cut   + " GeV" ).c_str() );
	  h_evt_cutflow_minNJetJJ_m                      [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_m_cut    + " GeV" ).c_str() );
	  h_evt_cutflow_minNJetJJ_sumPt                  [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_ht_cut   + " GeV" ).c_str() );
	  h_evt_cutflow_minNJetJJ_sumM                   [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_sm_cut   + " GeV" ).c_str() );
	  h_evt_cutflow_maxptNJetJJ_pt                   [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_pt_cut + " GeV" ).c_str() );
	  h_evt_cutflow_maxptNJetJJ_m                    [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_m_cut  + " GeV" ).c_str() );
	  h_evt_cutflow_maxptNJetJJ_sumPt                [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_ht_cut + " GeV" ).c_str() );
	  h_evt_cutflow_maxptNJetJJ_sumM                 [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_sm_cut + " GeV" ).c_str() );
	  h_evt_cutflow_minptNJetJJ_pt                   [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_pt_cut + " GeV" ).c_str() );
	  h_evt_cutflow_minptNJetJJ_m                    [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_m_cut  + " GeV" ).c_str() );
	  h_evt_cutflow_minptNJetJJ_sumPt                [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_ht_cut + " GeV" ).c_str() );
	  h_evt_cutflow_minptNJetJJ_sumM                 [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_sm_cut + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_NJetPt                 [ireg] ->GetXaxis()->FindBin( ( "> " + njetpt_cut         + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_NJetSumM               [ireg] ->GetXaxis()->FindBin( ( "> " + njetsm_cut         + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_NJetJJ_pt              [ireg] ->GetXaxis()->FindBin( ( "> " + njetjj_pt_cut      + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_NJetJJ_m               [ireg] ->GetXaxis()->FindBin( ( "> " + njetjj_m_cut       + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_NJetJJmindpt_pt        [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjpt_pt_cut    + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_NJetJJmindpt_m         [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjpt_m_cut     + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_NJetJJmaxdr_pt         [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjdr_pt_cut    + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_NJetJJmaxdr_m          [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjdr_m_cut     + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_avgNJetJJ_pt           [ireg] ->GetXaxis()->FindBin( ( "> " + avgnjetjj_pt_cut   + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_avgNJetJJ_m            [ireg] ->GetXaxis()->FindBin( ( "> " + avgnjetjj_m_cut    + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_maxNJetJJ_pt           [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_pt_cut   + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_maxNJetJJ_m            [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_m_cut    + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_maxNJetJJ_sumPt        [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_ht_cut   + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_maxNJetJJ_sumM         [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_sm_cut   + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_minNJetJJ_pt           [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_pt_cut   + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_minNJetJJ_m            [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_m_cut    + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_minNJetJJ_sumPt        [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_ht_cut   + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_minNJetJJ_sumM         [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_sm_cut   + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_maxptNJetJJ_pt         [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_pt_cut + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_maxptNJetJJ_m          [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_m_cut  + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_maxptNJetJJ_sumPt      [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_ht_cut + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_maxptNJetJJ_sumM       [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_sm_cut + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_minptNJetJJ_pt         [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_pt_cut + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_minptNJetJJ_m          [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_m_cut  + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_minptNJetJJ_sumPt      [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_ht_cut + " GeV" ).c_str() );
	  h_evt_cutflowEfficiency_minptNJetJJ_sumM       [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_sm_cut + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_NJetPt            [ireg] ->GetXaxis()->FindBin( ( "> " + njetpt_cut         + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_NJetSumM          [ireg] ->GetXaxis()->FindBin( ( "> " + njetsm_cut         + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_NJetJJ_pt         [ireg] ->GetXaxis()->FindBin( ( "> " + njetjj_pt_cut      + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_NJetJJ_m          [ireg] ->GetXaxis()->FindBin( ( "> " + njetjj_m_cut       + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_NJetJJmindpt_pt   [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjpt_pt_cut    + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_NJetJJmindpt_m    [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjpt_m_cut     + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_NJetJJmaxdr_pt    [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjdr_pt_cut    + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_NJetJJmaxdr_m     [ireg] ->GetXaxis()->FindBin( ( "> " + njetjjdr_m_cut     + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_avgNJetJJ_pt      [ireg] ->GetXaxis()->FindBin( ( "> " + avgnjetjj_pt_cut   + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_avgNJetJJ_m       [ireg] ->GetXaxis()->FindBin( ( "> " + avgnjetjj_m_cut    + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_maxNJetJJ_pt      [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_pt_cut   + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_maxNJetJJ_m       [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_m_cut    + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_maxNJetJJ_sumPt   [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_ht_cut   + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_maxNJetJJ_sumM    [ireg] ->GetXaxis()->FindBin( ( "> " + maxnjetjj_sm_cut   + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_minNJetJJ_pt      [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_pt_cut   + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_minNJetJJ_m       [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_m_cut    + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_minNJetJJ_sumPt   [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_ht_cut   + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_minNJetJJ_sumM    [ireg] ->GetXaxis()->FindBin( ( "> " + minnjetjj_sm_cut   + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_maxptNJetJJ_pt    [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_pt_cut + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_maxptNJetJJ_m     [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_m_cut  + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_maxptNJetJJ_sumPt [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_ht_cut + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_maxptNJetJJ_sumM  [ireg] ->GetXaxis()->FindBin( ( "> " + maxptnjetjj_sm_cut + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_minptNJetJJ_pt    [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_pt_cut + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_minptNJetJJ_m     [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_m_cut  + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_minptNJetJJ_sumPt [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_ht_cut + " GeV" ).c_str() );
	  h_evt_cutflowTotalEfficiency_minptNJetJJ_sumM  [ireg] ->GetXaxis()->FindBin( ( "> " + minptnjetjj_sm_cut + " GeV" ).c_str() );
	}
      }

      // overall dv counts / efficiencies
      std::vector<TH1F*> h_evt_count_dv;
      std::vector<TH1F*> h_evt_cuteff_dv;
      std::vector<TH1F*> h_evt_matchcuteff_dv;
      for ( size_t i = 0; i != hDV.size(); ++i ) {
	std::string hdv    = hDV   [i] + "DV"; hdv[0] = tolower(hdv[0]);
	std::string hdvstr = hDVstr[i];        hdvstr.pop_back(); hdvstr += " DV";
	h_evt_count_dv
	  .push_back( book( name, "evt_count_"              + hdv, "overall " + hdvstr + " count",                      1, 0, 1 ) );
	h_evt_cuteff_dv
	  .push_back( book( name, "evt_cutEfficiency_"      + hdv, "overall " + hdvstr + " cut efficiency",             1, 0, 1 ) );
	h_evt_matchcuteff_dv
	  .push_back( book( name, "evt_matchcutEfficiency_" + hdv, "overall " + hdvstr + " truth-match cut efficiency", 1, 0, 1 ) );
      }
      h_evt_count_DV              .push_back( h_evt_count_dv       );
      h_evt_cutEfficiency_DV      .push_back( h_evt_cuteff_dv      );
      h_evt_matchcutEfficiency_DV .push_back( h_evt_matchcuteff_dv );
      

      // OVERALL SIGNAL CUTFLOWS
      int icuthist = 0;
      std::vector<TH1F*> h_evt_cutflow_sgnl_nej_ndv_njx;
      std::vector<TH1F*> h_evt_cutflow_sgnlreg_nej_ndv_njx;
      std::vector<TH1F*> h_evt_cutflow_sgnlregfull_nej_ndv_njx;
      std::vector<TH1F*> h_evt_cutfloweff_sgnl_nej_ndv_njx;
      std::vector<TH1F*> h_evt_cutfloweff_sgnlreg_nej_ndv_njx;
      std::vector<TH1F*> h_evt_cutfloweff_sgnlregfull_nej_ndv_njx;
      std::vector<TH1F*> h_evt_cutflowtoteff_sgnl_nej_ndv_njx;
      std::vector<TH1F*> h_evt_cutflowtoteff_sgnlreg_nej_ndv_njx;
      std::vector<TH1F*> h_evt_cutflowtoteff_sgnlregfull_nej_ndv_njx;
      for ( const auto& cutej : m_cutEJ )
	for ( const auto& icutnej : m_ncutEJ )
	  for ( const auto& cutdv : m_cutDV )
	    for ( const auto& icutndv : m_ncutDV )
	      for ( size_t icnjx = 0; icnjx != m_cutNJetX.size(); ++icnjx ) {
		std::string              cutnej    = std::to_string( icutnej );
		std::string              cutndv    = std::to_string( icutndv );
		std::string              cutnjx    = m_cutNJetX [icnjx];
		std::vector<std::string> blabel    = { "all", cutej + " #geq " + cutnej, cutdv + " #geq " + cutndv };
		std::vector<std::string> rblabel   = { "all", "init", "four-jet trigger", "NJets #geq 4", "jet p_{T} > 120",
						       "jet |#eta| < 2.5", "NJetHt > 1000", cutej + " #geq " + cutnej, cutdv + " #geq " + cutndv };
		std::vector<std::string> rfblabel;
		if ( m_mc ) rfblabel = { "all", "init",                                      "jet cleaning", "NPV", "trigger", "jet select",
					 "four-jet trigger", "NJets #geq 4", "jet p_{T} > 120", "jet |#eta| < 2.5", "NJetHt > 1000",
					 cutej + " #geq " + cutnej, cutdv + " #geq " + cutndv};
		else        rfblabel = { "all", "init", "GRL", "LAr", "tile", "SCT", "core", "jet cleaning", "NPV", "trigger", "jet select",
					 "four-jet trigger", "NJets #geq 4", "jet p_{T} > 120", "jet |#eta| < 2.5", "NJetHt > 1000",
					 cutej + " #geq " + cutnej, cutdv + " #geq " + cutndv};
		std::vector<double>      cutnjxval_tmp;
		if      ( cutnjx == "NJetHt"            ) cutnjxval_tmp = m_njetht_cut;
		else if ( cutnjx == "NJetPt"            ) cutnjxval_tmp = m_njetpt_cut;
		else if ( cutnjx == "NJetSumM"          ) cutnjxval_tmp = m_njetsm_cut;
		else if ( cutnjx == "NJetJJ_pt"         ) cutnjxval_tmp = m_njetjj_pt_cut;
		else if ( cutnjx == "NJetJJmaxdr_pt"    ) cutnjxval_tmp = m_njetjjdr_pt_cut;
		else if ( cutnjx == "avgNJetJJ_pt"      ) cutnjxval_tmp = m_avgnjetjj_pt_cut;
		else if ( cutnjx == "maxNJetJJ_sumPt"   ) cutnjxval_tmp = m_maxnjetjj_ht_cut;
		else if ( cutnjx == "maxNJetJJ_sumM"    ) cutnjxval_tmp = m_maxnjetjj_sm_cut;
		else if ( cutnjx == "minNJetJJ_sumPt"   ) cutnjxval_tmp = m_minnjetjj_ht_cut;
		else if ( cutnjx == "minNJetJJ_sumM"    ) cutnjxval_tmp = m_minnjetjj_sm_cut;
		else if ( cutnjx == "maxptNJetJJ_pt"    ) cutnjxval_tmp = m_maxptnjetjj_pt_cut;
		else if ( cutnjx == "maxptNJetJJ_sumPt" ) cutnjxval_tmp = m_maxptnjetjj_ht_cut;
		else if ( cutnjx == "maxptNJetJJ_sumM"  ) cutnjxval_tmp = m_maxptnjetjj_sm_cut;
		for ( size_t injx = 0; injx != m_vcutNJetX.size(); ++injx ) {
		  std::string cutnjxval = std::to_string( cutnjxval_tmp[m_vcutNJetX[injx]] ); cutnjxval = cutnjxval.substr( 0, cutnjxval.find(".")+3 );
		  blabel   .push_back( cutnjx + " > " + cutnjxval );
		  rblabel  .push_back( cutnjx + " > " + cutnjxval );
		  rfblabel .push_back( cutnjx + " > " + cutnjxval );
		}
		size_t                   ncbin     =   blabel.size();
		size_t                   ncrbin    =  rblabel.size();
		size_t                  ncrfbin    = rfblabel.size();
		h_evt_cutflow_sgnl_nej_ndv_njx
		  .push_back( book( name, "evt_cutflow_signal_"                          +
				    cutnej + cutej + "_" + cutndv + cutdv + "_" + cutnjx,
				    cutnej + cutej + " " + cutndv + cutdv + " " + cutnjx + " signal cutflow",
				    ncbin, 0,   ncbin ) );
		h_evt_cutflow_sgnlreg_nej_ndv_njx
		  .push_back( book( name, "evt_cutflow_signalRegion_"                    +
				    cutnej + cutej + "_" + cutndv + cutdv + "_" + cutnjx,
		  		    cutnej + cutej + " " + cutndv + cutdv + " " + cutnjx + " signal region cutflow",
				    ncrbin, 0,  ncrbin ) );
		h_evt_cutflow_sgnlregfull_nej_ndv_njx
		  .push_back( book( name, "evt_cutflow_signalRegionFull_"                +
				    cutnej + cutej + "_" + cutndv + cutdv + "_" + cutnjx,
		  		    cutnej + cutej + " " + cutndv + cutdv + " " + cutnjx + " signal region full cutflow",
				    ncrfbin, 0, ncrfbin ) );
		h_evt_cutfloweff_sgnl_nej_ndv_njx
		  .push_back( book( name, "evt_cutflowEfficiency_signal_"                +
				    cutnej + cutej + "_" + cutndv + cutdv + "_" + cutnjx,
				    cutnej + cutej + " " + cutndv + cutdv + " " + cutnjx + " signal cutflow efficiency",
				    ncbin, 0,   ncbin ) );
		h_evt_cutfloweff_sgnlreg_nej_ndv_njx
		  .push_back( book( name, "evt_cutflowEfficiency_signalRegion_"          +
				    cutnej + cutej + "_" + cutndv + cutdv + "_" + cutnjx,
		  		    cutnej + cutej + " " + cutndv + cutdv + " " + cutnjx + " signal region cutflow efficiency",
				    ncrbin, 0,  ncrbin ) );
		h_evt_cutfloweff_sgnlregfull_nej_ndv_njx
		  .push_back( book( name, "evt_cutflowEfficiency_signalRegionFull_"      +
				    cutnej + cutej + "_" + cutndv + cutdv + "_" + cutnjx,
		  		    cutnej + cutej + " " + cutndv + cutdv + " " + cutnjx + " signal region full cutflow efficiency",
				    ncrfbin, 0, ncrfbin ) );
		h_evt_cutflowtoteff_sgnl_nej_ndv_njx
		  .push_back( book( name, "evt_cutflowTotalEfficiency_signal_"           +
				    cutnej + cutej + "_" + cutndv + cutdv + "_" + cutnjx,
				    cutnej + cutej + " " + cutndv + cutdv + " " + cutnjx + " signal cutflow total efficiency",
				    ncbin, 0,   ncbin ) );
		h_evt_cutflowtoteff_sgnlreg_nej_ndv_njx
		  .push_back( book( name, "evt_cutflowTotalEfficiency_signalRegion_"     +
				    cutnej + cutej + "_" + cutndv + cutdv + "_" + cutnjx,
		  		    cutnej + cutej + " " + cutndv + cutdv + " " + cutnjx + " signal region cutflow total efficiency",
				    ncrbin, 0,  ncrbin ) );
		h_evt_cutflowtoteff_sgnlregfull_nej_ndv_njx
		  .push_back( book( name, "evt_cutflowTotalEfficiency_signalRegionFull_"+
				    cutnej + cutej + "_" + cutndv + cutdv + "_" + cutnjx,
		  		    cutnej + cutej + " " + cutndv + cutdv + " " + cutnjx + " signal region full cutflow total efficiency",
				    ncrfbin, 0, ncrfbin ) );
		for ( size_t   icbin = 0; icbin   != ncbin;     ++icbin ) {
		  h_evt_cutflow_sgnl_nej_ndv_njx              [icuthist] ->GetXaxis()->FindBin( (   blabel[  icbin] ).c_str() );
		  h_evt_cutfloweff_sgnl_nej_ndv_njx           [icuthist] ->GetXaxis()->FindBin( (   blabel[  icbin] ).c_str() );
		  h_evt_cutflowtoteff_sgnl_nej_ndv_njx        [icuthist] ->GetXaxis()->FindBin( (   blabel[  icbin] ).c_str() );
		}
		for ( size_t  icrbin = 0; icrbin  != ncrbin;   ++icrbin ) {
		  h_evt_cutflow_sgnlreg_nej_ndv_njx           [icuthist] ->GetXaxis()->FindBin( (  rblabel[ icrbin] ).c_str() );
		  h_evt_cutfloweff_sgnlreg_nej_ndv_njx        [icuthist] ->GetXaxis()->FindBin( (  rblabel[ icrbin] ).c_str() );
		  h_evt_cutflowtoteff_sgnlreg_nej_ndv_njx     [icuthist] ->GetXaxis()->FindBin( (  rblabel[ icrbin] ).c_str() );
		}
		for ( size_t icrfbin = 0; icrfbin != ncrfbin; ++icrfbin ) {
		  h_evt_cutflow_sgnlregfull_nej_ndv_njx       [icuthist] ->GetXaxis()->FindBin( ( rfblabel[icrfbin] ).c_str() );
		  h_evt_cutfloweff_sgnlregfull_nej_ndv_njx    [icuthist] ->GetXaxis()->FindBin( ( rfblabel[icrfbin] ).c_str() );
		  h_evt_cutflowtoteff_sgnlregfull_nej_ndv_njx [icuthist] ->GetXaxis()->FindBin( ( rfblabel[icrfbin] ).c_str() );
		}
		++icuthist;
	      }
      h_evt_cutflow_signal_NEJ_NDV_NJetX                          .push_back( h_evt_cutflow_sgnl_nej_ndv_njx              );
      h_evt_cutflow_signalRegion_NEJ_NDV_NJetX                    .push_back( h_evt_cutflow_sgnlreg_nej_ndv_njx           );
      h_evt_cutflow_signalRegionFull_NEJ_NDV_NJetX                .push_back( h_evt_cutflow_sgnlregfull_nej_ndv_njx       );
      h_evt_cutflowEfficiency_signal_NEJ_NDV_NJetX                .push_back( h_evt_cutfloweff_sgnl_nej_ndv_njx           );
      h_evt_cutflowEfficiency_signalRegion_NEJ_NDV_NJetX          .push_back( h_evt_cutfloweff_sgnlreg_nej_ndv_njx        );
      h_evt_cutflowEfficiency_signalRegionFull_NEJ_NDV_NJetX      .push_back( h_evt_cutfloweff_sgnlregfull_nej_ndv_njx    );
      h_evt_cutflowTotalEfficiency_signal_NEJ_NDV_NJetX           .push_back( h_evt_cutflowtoteff_sgnl_nej_ndv_njx        );
      h_evt_cutflowTotalEfficiency_signalRegion_NEJ_NDV_NJetX     .push_back( h_evt_cutflowtoteff_sgnlreg_nej_ndv_njx     );
      h_evt_cutflowTotalEfficiency_signalRegionFull_NEJ_NDV_NJetX .push_back( h_evt_cutflowtoteff_sgnlregfull_nej_ndv_njx );
      
    } // end if cutflow info switch
      

    // --- ABCD HISTOS --- //
    if ( m_histoInfoSwitch->m_abcd || m_histoInfoSwitch->m_abcdcutOnly ) {
      std::vector<TH2F*> h_abcd_ndv_njetHt;
      std::vector<TH2F*> h_abcd_ndv_njetPt;
      std::vector<TH2F*> h_abcd_ndv_njetSumM;
      std::vector<TH2F*> h_abcd_ndv_njetjj_pt;
      std::vector<TH2F*> h_abcd_ndv_njetjj_m;
      std::vector<TH2F*> h_abcd_ndv_njetjjpt_pt;
      std::vector<TH2F*> h_abcd_ndv_njetjjpt_m;
      std::vector<TH2F*> h_abcd_ndv_njetjjdr_pt;
      std::vector<TH2F*> h_abcd_ndv_njetjjdr_m;
      std::vector<TH2F*> h_abcd_ndv_avgnjetjj_pt;
      std::vector<TH2F*> h_abcd_ndv_avgnjetjj_m;
      std::vector<TH2F*> h_abcd_ndv_maxnjetjj_pt;
      std::vector<TH2F*> h_abcd_ndv_maxnjetjj_m;
      std::vector<TH2F*> h_abcd_ndv_maxnjetjj_sumPt;
      std::vector<TH2F*> h_abcd_ndv_maxnjetjj_sumM;
      std::vector<TH2F*> h_abcd_ndv_minnjetjj_pt;
      std::vector<TH2F*> h_abcd_ndv_minnjetjj_m;
      std::vector<TH2F*> h_abcd_ndv_minnjetjj_sumPt;
      std::vector<TH2F*> h_abcd_ndv_minnjetjj_sumM;
      std::vector<TH2F*> h_abcd_ndv_maxptnjetjj_pt;
      std::vector<TH2F*> h_abcd_ndv_maxptnjetjj_m;
      std::vector<TH2F*> h_abcd_ndv_maxptnjetjj_sumPt;
      std::vector<TH2F*> h_abcd_ndv_maxptnjetjj_sumM;
      std::vector<TH2F*> h_abcd_ndv_minptnjetjj_pt;
      std::vector<TH2F*> h_abcd_ndv_minptnjetjj_m;
      std::vector<TH2F*> h_abcd_ndv_minptnjetjj_sumPt;
      std::vector<TH2F*> h_abcd_ndv_minptnjetjj_sumM;
      std::vector<TH2F*> h_abcd_ndv_njetHt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_njetPt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_njetSumM_vrsh;
      std::vector<TH2F*> h_abcd_ndv_njetjj_pt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_njetjj_m_vrsh;
      std::vector<TH2F*> h_abcd_ndv_njetjjpt_pt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_njetjjpt_m_vrsh;
      std::vector<TH2F*> h_abcd_ndv_njetjjdr_pt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_njetjjdr_m_vrsh;
      std::vector<TH2F*> h_abcd_ndv_avgnjetjj_pt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_avgnjetjj_m_vrsh;
      std::vector<TH2F*> h_abcd_ndv_maxnjetjj_pt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_maxnjetjj_m_vrsh;
      std::vector<TH2F*> h_abcd_ndv_maxnjetjj_sumPt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_maxnjetjj_sumM_vrsh;
      std::vector<TH2F*> h_abcd_ndv_minnjetjj_pt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_minnjetjj_m_vrsh;
      std::vector<TH2F*> h_abcd_ndv_minnjetjj_sumPt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_minnjetjj_sumM_vrsh;
      std::vector<TH2F*> h_abcd_ndv_maxptnjetjj_pt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_maxptnjetjj_m_vrsh;
      std::vector<TH2F*> h_abcd_ndv_maxptnjetjj_sumPt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_maxptnjetjj_sumM_vrsh;
      std::vector<TH2F*> h_abcd_ndv_minptnjetjj_pt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_minptnjetjj_m_vrsh;
      std::vector<TH2F*> h_abcd_ndv_minptnjetjj_sumPt_vrsh;
      std::vector<TH2F*> h_abcd_ndv_minptnjetjj_sumM_vrsh;
      int    ndv     = 0;
      double njetht  = 0;
      size_t dv_size = 0;
      if ( m_histoInfoSwitch->m_truthOnly ) {
	ndv     = 50;
	njetht  = 4000;
	dv_size = hLLP.size();
      }
      else {
	ndv     = 12;
	njetht  = 3500;
	dv_size = hDV .size();
      }
      for ( size_t i = 0; i != dv_size; ++i ) {
	std::string hdv      = "";
	std::string hdvstr   = "";
	std::string hdvstrpl = "";
	if ( m_histoInfoSwitch->m_truthOnly ) {
	  hdv      = hLLP   [i] +  "DecayVtx";
	  hdvstr   = hLLPstr[i]; hdvstr.pop_back();
	  hdvstrpl = hdvstr + " decay vertices";
	  hdvstr  += " decay vertex";
	}
	else {
	  hdv      = hDV   [i] +  "DV";
	  hdvstr   = hDVstr[i]; hdvstr.pop_back(); hdvstr += " DV";
	  hdvstrpl = hdvstr + "s";
	}
	std::string m_ljstr       = "Leading N " + m_jetStr + " Jet";
	std::string m_ljjstr      = m_ljstr + " min-diff-invM dijet";
	std::string m_ljjptstr    = m_ljstr + " min-diff-pt dijet";
	std::string m_ljjdrstr    = m_ljstr + " max-dR dijet";
	std::string m_avgljjstr   = m_ljstr + " average dijet";
	std::string m_maxljjstr   = m_ljstr + " max-invM dijet";
	std::string m_minljjstr   = m_ljstr + " min-invM dijet";
	std::string m_maxptljjstr = m_ljstr + " max-pt dijet";
	std::string m_minptljjstr = m_ljstr + " min-pt dijet";
	h_abcd_ndv_njetHt
	  .push_back(   book( name, "ABCD_n" + hdv + "_NJetHt",                   m_ljstr    + " H_{T} [GeV]",
			      100, njetht_xmin, njetht, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	h_abcd_ndv_njetHt_vrsh
	  .push_back(   book( name, "ABCD_n" + hdv + "_NJetHt"            + vrsh, m_ljstr    + " H_{T} [GeV]"        + vrshift,
			      100, njetht_xmin, njetht, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	if ( !m_histoInfoSwitch->m_truthOnly ) {
	  h_abcd_ndv_njetPt
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetPt",                   m_ljstr    + " p_{T} [GeV]",
			      100, 0,             1000, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetSumM
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetSumM",                 m_ljstr    + " sum-mass [GeV]",
			      100, 0,              550, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjj_pt
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJ_pt",                m_ljjstr   + " p_{T} [GeV]",
			      100, 0,             1700, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjj_m
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJ_m",                 m_ljjstr   + " mass [GeV]",
			      100, 0,             1800, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjjpt_pt
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJmindpt_pt",          m_ljjptstr + " p_{T} [GeV]",
			      100, 0,             1500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjjpt_m
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJmindpt_m",           m_ljjptstr + " mass [GeV]",
			      100, 0,             2000, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjjdr_pt
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJmaxdr_pt",           m_ljjdrstr + " p_{T} [GeV]",
			      100, 0,             1500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjjdr_m
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJmaxdr_m",            m_ljjdrstr + " mass [GeV]",
			      100, 0,             2000, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_avgnjetjj_pt
	    .push_back( book( name, "ABCD_n" + hdv + "_avgNJetJJ_pt",             m_avgljjstr   + " p_{T} [GeV]",
			      100, 0,             1400, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_avgnjetjj_m
	    .push_back( book( name, "ABCD_n" + hdv + "_avgNJetJJ_m",              m_avgljjstr   + " mass [GeV]",
			      100, 0,             2000, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxnjetjj_pt
	    .push_back( book( name, "ABCD_n" + hdv + "_maxNJetJJ_pt",             m_maxljjstr   + " p_{T} [GeV]",
			      100, 0,             1250, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxnjetjj_m
	    .push_back( book( name, "ABCD_n" + hdv + "_maxNJetJJ_m",              m_maxljjstr   + " mass [GeV]",
			      100, 0,             3500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxnjetjj_sumPt
	    .push_back( book( name, "ABCD_n" + hdv + "_maxNJetJJ_sumPt",          m_maxljjstr   + " sum-p_{T} [GeV]",
			      100, 0,             3200, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxnjetjj_sumM
	    .push_back( book( name, "ABCD_n" + hdv + "_maxNJetJJ_sumM",           m_maxljjstr   + " sum-mass [GeV]",
			      100, 0,              400, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minnjetjj_pt
	    .push_back( book( name, "ABCD_n" + hdv + "_minNJetJJ_pt",             m_minljjstr   + " p_{T} [GeV]",
			      100, 0,             1600, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minnjetjj_m
	    .push_back( book( name, "ABCD_n" + hdv + "_minNJetJJ_m",              m_minljjstr   + " mass [GeV]",
			      100, 0,             1200, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minnjetjj_sumPt
	    .push_back( book( name, "ABCD_n" + hdv + "_minNJetJJ_sumPt",          m_minljjstr   + " sum-p_{T} [GeV]",
			      100, 0,             1800, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minnjetjj_sumM
	    .push_back( book( name, "ABCD_n" + hdv + "_minNJetJJ_sumM",           m_minljjstr   + " sum-mass [GeV]",
			      100, 0,              250, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxptnjetjj_pt
	    .push_back( book( name, "ABCD_n" + hdv + "_maxptNJetJJ_pt",           m_maxptljjstr + " p_{T} [GeV]",
			      100, 0,             2000, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxptnjetjj_m
	    .push_back( book( name, "ABCD_n" + hdv + "_maxptNJetJJ_m",            m_maxptljjstr + " mass [GeV]",
			      100, 0,             2200, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxptnjetjj_sumPt
	    .push_back( book( name, "ABCD_n" + hdv + "_maxptNJetJJ_sumPt",        m_maxptljjstr + " sum-p_{T} [GeV]",
			      100, 0,             2500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxptnjetjj_sumM
	    .push_back( book( name, "ABCD_n" + hdv + "_maxptNJetJJ_sumM",         m_maxptljjstr + " sum-mass [GeV]",
			      100, 0,              320, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minptnjetjj_pt
	    .push_back( book( name, "ABCD_n" + hdv + "_minptNJetJJ_pt",           m_minptljjstr + " p_{T} [GeV]",
			      100, 0,              900, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minptnjetjj_m
	    .push_back( book( name, "ABCD_n" + hdv + "_minptNJetJJ_m",            m_minptljjstr + " mass [GeV]",
			      100, 0,             2500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minptnjetjj_sumPt
	    .push_back( book( name, "ABCD_n" + hdv + "_minptNJetJJ_sumPt",        m_minptljjstr + " sum-p_{T} [GeV]",
			      100, 0,             2500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minptnjetjj_sumM
	    .push_back( book( name, "ABCD_n" + hdv + "_minptNJetJJ_sumM",         m_minptljjstr + " sum-mass [GeV]",
			      100, 0,              320, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetPt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetPt"            + vrsh, m_ljstr       + " p_{T} [GeV]"     + vrshift,
			      100, 0,             1000, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetSumM_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetSumM"          + vrsh, m_ljstr       + " sum-mass [GeV]"  + vrshift,
			      100, 0,              550, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjj_pt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJ_pt"         + vrsh, m_ljjstr      + " p_{T} [GeV]"     + vrshift,
			      100, 0,             1700, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjj_m_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJ_m"          + vrsh, m_ljjstr      + " mass [GeV]"      + vrshift,
			      100, 0,             1800, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjjpt_pt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJmindpt_pt"   + vrsh, m_ljjptstr    + " p_{T} [GeV]"     + vrshift,
			      100, 0,             1500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjjpt_m_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJmindpt_m"    + vrsh, m_ljjptstr    + " mass [GeV]"      + vrshift,
			      100, 0,             2000, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjjdr_pt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJmaxdr_pt"    + vrsh, m_ljjdrstr    + " p_{T} [GeV]"     + vrshift,
			      100, 0,             1500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_njetjjdr_m_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_NJetJJmaxdr_m"     + vrsh, m_ljjdrstr    + " mass [GeV]"      + vrshift,
			      100, 0,             2000, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_avgnjetjj_pt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_avgNJetJJ_pt"      + vrsh, m_avgljjstr   + " p_{T} [GeV]"     + vrshift,
			      100, 0,             1400, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_avgnjetjj_m_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_avgNJetJJ_m"       + vrsh, m_avgljjstr   + " mass [GeV]"      + vrshift,
			      100, 0,             2000, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxnjetjj_pt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_maxNJetJJ_pt"      + vrsh, m_maxljjstr   + " p_{T} [GeV]"     + vrshift,
			      100, 0,             1250, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxnjetjj_m_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_maxNJetJJ_m"       + vrsh, m_maxljjstr   + " mass [GeV]"      + vrshift,
			      100, 0,             3500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxnjetjj_sumPt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_maxNJetJJ_sumPt"   + vrsh, m_maxljjstr   + " sum-p_{T} [GeV]" + vrshift,
			      100, 0,             3200, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxnjetjj_sumM_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_maxNJetJJ_sumM"    + vrsh, m_maxljjstr   + " sum-mass [GeV]"  + vrshift,
			      100, 0,              400, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minnjetjj_pt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_minNJetJJ_pt"      + vrsh, m_minljjstr   + " p_{T} [GeV]"     + vrshift,
			      100, 0,             1600, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minnjetjj_m_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_minNJetJJ_m"       + vrsh, m_minljjstr   + " mass [GeV]"      + vrshift,
			      100, 0,             1200, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minnjetjj_sumPt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_minNJetJJ_sumPt"   + vrsh, m_minljjstr   + " sum-p_{T} [GeV]" + vrshift,
			      100, 0,             1800, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minnjetjj_sumM_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_minNJetJJ_sumM"    + vrsh, m_minljjstr   + " sum-mass [GeV]"  + vrshift,
			      100, 0,              250, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxptnjetjj_pt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_maxptNJetJJ_pt"    + vrsh, m_maxptljjstr + " p_{T} [GeV]"     + vrshift,
			      100, 0,             2000, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxptnjetjj_m_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_maxptNJetJJ_m"     + vrsh, m_maxptljjstr + " mass [GeV]"      + vrshift,
			      100, 0,             2200, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxptnjetjj_sumPt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_maxptNJetJJ_sumPt" + vrsh, m_maxptljjstr + " sum-p_{T} [GeV]" + vrshift,
			      100, 0,             2500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_maxptnjetjj_sumM_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_maxptNJetJJ_sumM"  + vrsh, m_maxptljjstr + " sum-mass [GeV]"  + vrshift,
			      100, 0,              320, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minptnjetjj_pt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_minptNJetJJ_pt"    + vrsh, m_minptljjstr + " p_{T} [GeV]"     + vrshift,
			      100, 0,              900, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minptnjetjj_m_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_minptNJetJJ_m"     + vrsh, m_minptljjstr + " mass [GeV]"      + vrshift,
			      100, 0,             2500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minptnjetjj_sumPt_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_minptNJetJJ_sumPt" + vrsh, m_minptljjstr + " sum-p_{T} [GeV]" + vrshift,
			      100, 0,             2500, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	  h_abcd_ndv_minptnjetjj_sumM_vrsh
	    .push_back( book( name, "ABCD_n" + hdv + "_minptNJetJJ_sumM"  + vrsh, m_minptljjstr + " sum-mass [GeV]"  + vrshift,
			      100, 0,              320, "n " + hdvstrpl, ndv+1, -1, ndv ) );
	}	
      }
      h_abcd_nDV_NJetHt                 .push_back( h_abcd_ndv_njetHt                 );
      h_abcd_nDV_NJetPt                 .push_back( h_abcd_ndv_njetPt                 );
      h_abcd_nDV_NJetSumM               .push_back( h_abcd_ndv_njetSumM               );
      h_abcd_nDV_NJetJJ_pt              .push_back( h_abcd_ndv_njetjj_pt              );
      h_abcd_nDV_NJetJJ_m               .push_back( h_abcd_ndv_njetjj_m               );
      h_abcd_nDV_NJetJJmindpt_pt        .push_back( h_abcd_ndv_njetjjpt_pt            );
      h_abcd_nDV_NJetJJmindpt_m         .push_back( h_abcd_ndv_njetjjpt_m             );
      h_abcd_nDV_NJetJJmaxdr_pt         .push_back( h_abcd_ndv_njetjjdr_pt            );
      h_abcd_nDV_NJetJJmaxdr_m          .push_back( h_abcd_ndv_njetjjdr_m             );
      h_abcd_nDV_avgNJetJJ_pt           .push_back( h_abcd_ndv_avgnjetjj_pt           );
      h_abcd_nDV_avgNJetJJ_m            .push_back( h_abcd_ndv_avgnjetjj_m            );
      h_abcd_nDV_maxNJetJJ_pt           .push_back( h_abcd_ndv_maxnjetjj_pt           );
      h_abcd_nDV_maxNJetJJ_m            .push_back( h_abcd_ndv_maxnjetjj_m            );
      h_abcd_nDV_maxNJetJJ_sumPt        .push_back( h_abcd_ndv_maxnjetjj_sumPt        );
      h_abcd_nDV_maxNJetJJ_sumM         .push_back( h_abcd_ndv_maxnjetjj_sumM         );
      h_abcd_nDV_minNJetJJ_pt           .push_back( h_abcd_ndv_minnjetjj_pt           );
      h_abcd_nDV_minNJetJJ_m            .push_back( h_abcd_ndv_minnjetjj_m            );
      h_abcd_nDV_minNJetJJ_sumPt        .push_back( h_abcd_ndv_minnjetjj_sumPt        );
      h_abcd_nDV_minNJetJJ_sumM         .push_back( h_abcd_ndv_minnjetjj_sumM         );
      h_abcd_nDV_maxptNJetJJ_pt         .push_back( h_abcd_ndv_maxptnjetjj_pt         );
      h_abcd_nDV_maxptNJetJJ_m          .push_back( h_abcd_ndv_maxptnjetjj_m          );
      h_abcd_nDV_maxptNJetJJ_sumPt      .push_back( h_abcd_ndv_maxptnjetjj_sumPt      );
      h_abcd_nDV_maxptNJetJJ_sumM       .push_back( h_abcd_ndv_maxptnjetjj_sumM       );
      h_abcd_nDV_minptNJetJJ_pt         .push_back( h_abcd_ndv_minptnjetjj_pt         );
      h_abcd_nDV_minptNJetJJ_m          .push_back( h_abcd_ndv_minptnjetjj_m          );
      h_abcd_nDV_minptNJetJJ_sumPt      .push_back( h_abcd_ndv_minptnjetjj_sumPt      );
      h_abcd_nDV_minptNJetJJ_sumM       .push_back( h_abcd_ndv_minptnjetjj_sumM       );
      h_abcd_nDV_NJetHt_vrsh            .push_back( h_abcd_ndv_njetHt_vrsh            );
      h_abcd_nDV_NJetPt_vrsh            .push_back( h_abcd_ndv_njetPt_vrsh            );
      h_abcd_nDV_NJetSumM_vrsh          .push_back( h_abcd_ndv_njetSumM_vrsh          );
      h_abcd_nDV_NJetJJ_pt_vrsh         .push_back( h_abcd_ndv_njetjj_pt_vrsh         );
      h_abcd_nDV_NJetJJ_m_vrsh          .push_back( h_abcd_ndv_njetjj_m_vrsh          );
      h_abcd_nDV_NJetJJmindpt_pt_vrsh   .push_back( h_abcd_ndv_njetjjpt_pt_vrsh       );
      h_abcd_nDV_NJetJJmindpt_m_vrsh    .push_back( h_abcd_ndv_njetjjpt_m_vrsh        );
      h_abcd_nDV_NJetJJmaxdr_pt_vrsh    .push_back( h_abcd_ndv_njetjjdr_pt_vrsh       );
      h_abcd_nDV_NJetJJmaxdr_m_vrsh     .push_back( h_abcd_ndv_njetjjdr_m_vrsh        );
      h_abcd_nDV_avgNJetJJ_pt_vrsh      .push_back( h_abcd_ndv_avgnjetjj_pt_vrsh      );
      h_abcd_nDV_avgNJetJJ_m_vrsh       .push_back( h_abcd_ndv_avgnjetjj_m_vrsh       );
      h_abcd_nDV_maxNJetJJ_pt_vrsh      .push_back( h_abcd_ndv_maxnjetjj_pt_vrsh      );
      h_abcd_nDV_maxNJetJJ_m_vrsh       .push_back( h_abcd_ndv_maxnjetjj_m_vrsh       );
      h_abcd_nDV_maxNJetJJ_sumPt_vrsh   .push_back( h_abcd_ndv_maxnjetjj_sumPt_vrsh   );
      h_abcd_nDV_maxNJetJJ_sumM_vrsh    .push_back( h_abcd_ndv_maxnjetjj_sumM_vrsh    );
      h_abcd_nDV_minNJetJJ_pt_vrsh      .push_back( h_abcd_ndv_minnjetjj_pt_vrsh      );
      h_abcd_nDV_minNJetJJ_m_vrsh       .push_back( h_abcd_ndv_minnjetjj_m_vrsh       );
      h_abcd_nDV_minNJetJJ_sumPt_vrsh   .push_back( h_abcd_ndv_minnjetjj_sumPt_vrsh   );
      h_abcd_nDV_minNJetJJ_sumM_vrsh    .push_back( h_abcd_ndv_minnjetjj_sumM_vrsh    );
      h_abcd_nDV_maxptNJetJJ_pt_vrsh    .push_back( h_abcd_ndv_maxptnjetjj_pt_vrsh    );
      h_abcd_nDV_maxptNJetJJ_m_vrsh     .push_back( h_abcd_ndv_maxptnjetjj_m_vrsh     );
      h_abcd_nDV_maxptNJetJJ_sumPt_vrsh .push_back( h_abcd_ndv_maxptnjetjj_sumPt_vrsh );
      h_abcd_nDV_maxptNJetJJ_sumM_vrsh  .push_back( h_abcd_ndv_maxptnjetjj_sumM_vrsh  );
      h_abcd_nDV_minptNJetJJ_pt_vrsh    .push_back( h_abcd_ndv_minptnjetjj_pt_vrsh    );
      h_abcd_nDV_minptNJetJJ_m_vrsh     .push_back( h_abcd_ndv_minptnjetjj_m_vrsh     );
      h_abcd_nDV_minptNJetJJ_sumPt_vrsh .push_back( h_abcd_ndv_minptnjetjj_sumPt_vrsh );
      h_abcd_nDV_minptNJetJJ_sumM_vrsh  .push_back( h_abcd_ndv_minptnjetjj_sumM_vrsh  );
    } // end abcd switch
  
  } // end loop over regions

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: execute ( TTree* tree, Long64_t treeEntry, const std::vector<EJsHelper::Region>& regions,
					    const EJsHelper::BaseDV& base_dv )
{
  if ( m_debug ) Info( "EJsHistogramManager::execute()", "filling histograms" );

  tree->GetEntry( treeEntry );

  if ( treeEntry % 5000 == 0 ) Info( "EJsHistogramManager::execute()", "tree entry: %llu", treeEntry );

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
    // --> skip signal events in data until we unblind
    else if ( region.type == EJsHelper::SIGNAL           ) { if ( !m_signal || ( !m_mc && !m_unblind ) ) continue; }
    // --> isolate region of available mc dijet background pt-slice (lead jet b/w 400-800 GeV)
    else if ( region.type == EJsHelper::JZ4W_SLICE_SEARCH_MINUS_ONE ) {
      if ( !m_searchMinusOne ) continue; 
      if ( m_jet_pt->at(0) < 400 || m_jet_pt ->at(0) > 800 ) continue;
    }
    else if ( region.type == EJsHelper::JZ4W_SLICE_SEARCH           ) {
      if ( !m_search         ) continue; 
      if ( m_jet_pt->at(0) < 400 || m_jet_pt ->at(0) > 800 ) continue;
    }
    else if ( region.type == EJsHelper::JZ4W_SLICE_VALIDATION       ) {
      if ( !m_valid          ) continue; 
      if ( m_jet_pt->at(0) < 400 || m_jet_pt ->at(0) > 800 ) continue;
    }

    bool doHists = true;
    if ( region.type == EJsHelper::SEARCH || region.type == EJsHelper::SEARCH_MINUS_ONE )
      { if ( !m_mc && !m_unblind ) doHists = false; }
    // --> skip search (and search-minus-one) histos (except ABCD) in data for now

    
    // ------------------ //
    // --- EVENT INFO --- //
    // ------------------ //
    if ( doHists && !m_histoInfoSwitch->m_abcdcutOnly ) {
      if ( m_debug ) Info( "EJsHistogramManager::execute()", "doing event info histos" );
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
    }
    // NDVs per event --> fill below
    std::vector<int> NDV;


    
    // ------------------------- //
    // --- TRUTH (DARK) JETS --- //
    // ------------------------- //

    double truthJetConstit_sumPt      = 0;
    double tightTruthJetConstit_sumPt = 0;
    double darkJetConstit_sumPt       = 0;
    double tightDarkJetConstit_sumPt  = 0;
    
    if ( m_mc ) {

      // --- TRUTH JETS --- //
      if ( m_debug ) Info( "EJsHistogramManager::execute()", "doing truth jet histos" );
      
      // set vector of nTJ counters
      std::vector<int> n_truthJet ( m_nTypeTJs, 0 );

      // loop over truth jets
      for ( int i = 0; i != m_truthJet_n; ++i ) {

	// // sum truth jet constituent sum-pt for calculating truth orphan pt
	// if ( m_truthJet_pt ->at(i) > m_jetPt      )
	//   truthJetConstit_sumPt      += m_truthJet_constitPt ->at(i);
	// if ( m_truthJet_pt ->at(i) > m_tightJetPt )
	//   tightTruthJetConstit_sumPt += m_truthJet_constitPt ->at(i);

	// get truth jet four-momentum
	TLorentzVector truthJet_p4;
	truthJet_p4.SetPtEtaPhiM( m_truthJet_pt ->at(i), m_truthJet_eta ->at(i), m_truthJet_phi ->at(i), m_truthJet_M ->at(i) );

	// get vector of truth jet types
	std::vector<int> truthJet;
	getTruthJetTypes( i, truthJet );

	// loop over truth jet types and fill histograms
	for ( size_t itj = 0; itj != truthJet.size(); ++itj ) {
	  if ( !truthJet[itj] ) continue;
	  ++n_truthJet[itj];

	  if ( !doHists || m_histoInfoSwitch->m_abcdcutOnly ) continue;
	  h_truthJet_pt       [ireg][itj] ->Fill( m_truthJet_pt       ->at(i), weight );
	  h_truthJet_pt_s     [ireg][itj] ->Fill( m_truthJet_pt       ->at(i), weight );
	  h_truthJet_eta      [ireg][itj] ->Fill( m_truthJet_eta      ->at(i), weight );
	  h_truthJet_phi      [ireg][itj] ->Fill( m_truthJet_phi      ->at(i), weight );
	  h_truthJet_E        [ireg][itj] ->Fill( m_truthJet_E        ->at(i), weight );
	  h_truthJet_M        [ireg][itj] ->Fill( m_truthJet_M        ->at(i), weight );
	  h_truthJet_rapid    [ireg][itj] ->Fill( m_truthJet_rapid    ->at(i), weight );
	  h_truthJet_girth    [ireg][itj] ->Fill( m_truthJet_girth    ->at(i), weight );
	  h_truthJet_nConstit [ireg][itj] ->Fill( m_truthJet_nConstit ->at(i), weight );
	  // kinematics
	  if ( m_histoInfoSwitch ->m_kinematics || m_histoInfoSwitch ->m_kinematics_tjet ) {
	    h_truthJet_px     [ireg][itj] ->Fill( truthJet_p4.Px(),            weight );
	    h_truthJet_py     [ireg][itj] ->Fill( truthJet_p4.Py(),            weight );
	    h_truthJet_pz     [ireg][itj] ->Fill( truthJet_p4.Pz(),            weight );
	    h_truthJet_Et     [ireg][itj] ->Fill( truthJet_p4.Et(),            weight );
	    h_truthJet_Et_s   [ireg][itj] ->Fill( truthJet_p4.Et(),            weight );
	  }

	  // matched LLP decay vertices
	  std::vector<int> n_tjet_llpdv ( m_nTypeLLPs, 0 );
	  // loop over matched truth vertices
	  for ( int tjv = 0; tjv != m_truthJet_nTV ->at(i); ++tjv ) {
	    int tjetTvIx  = m_truthJet_TV_index ->at(i)[tjv];
	    int n_tv_desc = m_truthVtx_nDesc    ->at(tjetTvIx);

	    // set vector of matched LLP decay vertex types
	    std::vector<int> tjet_llpdv;
	    getLLPTypes( tjetTvIx, tjet_llpdv );
	    // loop over matched LLP decay vertex types
	    for ( size_t tjtv = 0; tjtv != tjet_llpdv.size(); ++tjtv ) {
	      if ( !tjet_llpdv[tjtv] ) continue;
	      ++n_tjet_llpdv[tjtv];

	      h_truthJet_llpdv_dR    [ireg][itj][tjtv] ->Fill( m_truthJet_TV_dR ->at(i)[tjv], weight );
	      h_truthJet_llpdv_ndesc [ireg][itj][tjtv] ->Fill( n_tv_desc,                     weight );
	      if ( m_histoInfoSwitch->m_tjetVerts ) {
		h_truthJet_llpdv_z   [ireg][itj][tjtv] ->Fill( m_truthJet_TV_z  ->at(i)[tjv], weight );
		h_truthJet_llpdv_r   [ireg][itj][tjtv] ->Fill( m_truthJet_TV_r  ->at(i)[tjv], weight );
	      }
	    } // end loop over matched LLP decay types
	    
	  } // end loop over matched truth vertices

	  for ( size_t tjtv = 0; tjtv != n_tjet_llpdv.size(); ++tjtv )
	    h_truthJet_nllpdv [ireg][itj][tjtv] ->Fill( n_tjet_llpdv[tjtv], weight );

	  // matched LLP truth tracks
	  std::vector<int> n_tjet_llptrk ( m_nTypeLLPs, 0 );
	  // loop over matched truth particles
	  for ( int tjp = 0; tjp != m_truthJet_ntp ->at(i); ++tjp ) {
	    int tjetTpID = m_truthJet_tp_ID    ->at(i)[tjp];
	    int tjetTpIx = m_truthJet_tp_index ->at(i)[tjp];
	    
	    // set vector matched LLP descendant types
	    std::vector<int> tjet_llptrk;
	    int ancestIx = getLLPDescTypes( tjetTpID, tjet_llptrk );

	    // loop over matched LLP descendant types
	    for ( size_t tjtp = 0; tjtp != tjet_llptrk.size(); ++tjtp ) {
	      if ( !tjet_llptrk[tjtp] ) continue;
	      ++n_tjet_llptrk[tjtp];

	      double d0 = 0;
	      double z0 = 0;
	      if ( ancestIx >= 0 ) {
	      	TVector3 pointvec
		( m_truthVtx_x ->at(ancestIx) - m_pv_x, m_truthVtx_y ->at(ancestIx) - m_pv_y, m_truthVtx_z ->at(ancestIx) - m_pv_z );
	      	double dphi_tp_pointvec = EJsHelper::deltaPhi( m_truthJet_tp_phi ->at(i)[tjp], pointvec.Phi() );
	      	d0 = m_truthVtx_r ->at(ancestIx) * TMath::Sin( dphi_tp_pointvec );
	      	z0 = m_truthVtx_r ->at(ancestIx) / TMath::Tan( pointvec.Theta() );
	      }
	      h_truthJet_llptrk_dR   [ireg][itj][tjtp] ->Fill( m_truthJet_tp_dR ->at(i)[tjp], weight );
	      if ( m_histoInfoSwitch->m_tjetTrks ) {
		h_truthJet_llptrk_d0 [ireg][itj][tjtp] ->Fill( d0,                            weight );
		h_truthJet_llptrk_z0 [ireg][itj][tjtp] ->Fill( z0,                            weight );
	      }
	    } // end loop over LLP desc types

	  } // end loop over matched truth particles

	  for ( size_t tjtp = 0; tjtp != n_tjet_llptrk.size(); ++tjtp )
	    h_truthJet_nllptrk [ireg][itj][tjtp] ->Fill( n_tjet_llptrk[tjtp], weight );

	} // end loop over truth jet types
	
      } // end loop over truth jets

      // fill truth jet count histograms
      for ( size_t itj = 0; itj != n_truthJet.size(); ++itj ) {
	h_truthJet_n [ireg][itj] ->Fill( n_truthJet[itj], weight );
      }


      // --- TRUTH DARK JETS --- //
      if ( m_debug ) Info( "EJsHistogramManager::execute()", "doing dark jet histos" );
      
      // set vector of nDJ counters
      std::vector<int> n_darkJet ( m_nTypeDJs, 0 );

      // loop over truth dark jets
      for ( int i = 0; i != m_darkJet_n; ++i ) {

	// // sum truth dark jet constituent sum-pt for calculating truth dark orphan pt
	// if ( m_darkJet_pt ->at(i) > m_jetPt      )
	//   darkJetConstit_sumPt      += m_darkJet_constitPt ->at(i);
	// if ( m_darkJet_pt ->at(i) > m_tightJetPt )
	//   tightDarkJetConstit_sumPt += m_darkJet_constitPt ->at(i);

	// get truth dark jet four-momentum
	TLorentzVector darkJet_p4;
	darkJet_p4.SetPtEtaPhiM( m_darkJet_pt ->at(i), m_darkJet_eta ->at(i), m_darkJet_phi ->at(i), m_darkJet_M ->at(i) );

	// get vector of truth dark jet types
	std::vector<int> darkJet;
	bool allDJ   = 1;
	bool matchDJ = 0;
	if ( m_darkJet_truthMatch ->at(i) && m_darkJet_pt ->at(i) > 30 ) matchDJ = 1;
	darkJet .push_back( allDJ   );
	darkJet .push_back( matchDJ );

	// loop over truth dark jet types and fill histograms
	for ( size_t idj = 0; idj != darkJet.size(); ++idj ) {
	  if ( !darkJet[idj] ) continue;
	  ++n_darkJet[idj];

	  if ( !doHists || m_histoInfoSwitch->m_abcdcutOnly ) continue;
	  h_darkJet_pt       [ireg][idj] ->Fill( m_darkJet_pt       ->at(i), weight );
	  h_darkJet_pt_s     [ireg][idj] ->Fill( m_darkJet_pt       ->at(i), weight );
	  h_darkJet_eta      [ireg][idj] ->Fill( m_darkJet_eta      ->at(i), weight );
	  h_darkJet_phi      [ireg][idj] ->Fill( m_darkJet_phi      ->at(i), weight );
	  h_darkJet_E        [ireg][idj] ->Fill( m_darkJet_E        ->at(i), weight );
	  h_darkJet_M        [ireg][idj] ->Fill( m_darkJet_M        ->at(i), weight );
	  h_darkJet_rapid    [ireg][idj] ->Fill( m_darkJet_rapid    ->at(i), weight );
	  h_darkJet_girth    [ireg][idj] ->Fill( m_darkJet_girth    ->at(i), weight );
	  h_darkJet_nConstit [ireg][idj] ->Fill( m_darkJet_nConstit ->at(i), weight );
	  // kinematics
	  if ( m_histoInfoSwitch ->m_kinematics || m_histoInfoSwitch ->m_kinematics_djet ) {
	    h_darkJet_px     [ireg][idj] ->Fill( darkJet_p4.Px(),            weight );
	    h_darkJet_py     [ireg][idj] ->Fill( darkJet_p4.Py(),            weight );
	    h_darkJet_pz     [ireg][idj] ->Fill( darkJet_p4.Pz(),            weight );
	    h_darkJet_Et     [ireg][idj] ->Fill( darkJet_p4.Et(),            weight );
	    h_darkJet_Et_s   [ireg][idj] ->Fill( darkJet_p4.Et(),            weight );
	  }

	  // matched LLP decay vertices
	  std::vector<int> n_djet_llpdv ( m_nTypeLLPs, 0 );
	  // loop over matched truth vertices
	  for ( int djv = 0; djv != m_darkJet_nTV ->at(i); ++djv ) {
	    int djetTvIx  = m_darkJet_TV_index ->at(i)[djv];
	    int n_tv_desc = m_truthVtx_nDesc    ->at(djetTvIx);

	    // set vector of matched LLP decay vertex types
	    std::vector<int> djet_llpdv;
	    getLLPTypes( djetTvIx, djet_llpdv );
	    // loop over matched LLP decay vertex types
	    for ( size_t djtv = 0; djtv != djet_llpdv.size(); ++djtv ) {
	      if ( !djet_llpdv[djtv] ) continue;
	      ++n_djet_llpdv[djtv];

	      h_darkJet_llpdv_dR    [ireg][idj][djtv] ->Fill( m_darkJet_TV_dR ->at(i)[djv], weight );
	      h_darkJet_llpdv_ndesc [ireg][idj][djtv] ->Fill( n_tv_desc,                    weight );
	      if ( m_histoInfoSwitch->m_djetVerts ) {
		h_darkJet_llpdv_z   [ireg][idj][djtv] ->Fill( m_darkJet_TV_z  ->at(i)[djv], weight );
		h_darkJet_llpdv_r   [ireg][idj][djtv] ->Fill( m_darkJet_TV_r  ->at(i)[djv], weight );
	      }
	    } // end loop over matched LLP decay types
	    
	  } // end loop over matched truth vertices

	  for ( size_t djtv = 0; djtv != n_djet_llpdv.size(); ++djtv )
	    h_darkJet_nllpdv [ireg][idj][djtv] ->Fill( n_djet_llpdv[djtv], weight );

	  // matched LLP truth tracks
	  std::vector<int> n_djet_llptrk ( m_nTypeLLPs, 0 );
	  // loop over matched truth particles
	  for ( int djp = 0; djp != m_darkJet_ntp ->at(i); ++djp ) {
	    int djetTpID = m_darkJet_tp_ID    ->at(i)[djp];
	    int djetTpIx = m_darkJet_tp_index ->at(i)[djp];
	    
	    // set vector matched LLP descendant types
	    std::vector<int> djet_llptrk;
	    int ancestIx = getLLPDescTypes( djetTpID, djet_llptrk );

	    // loop over matched LLP descendant types
	    for ( size_t djtp = 0; djtp != djet_llptrk.size(); ++djtp ) {
	      if ( !djet_llptrk[djtp] ) continue;
	      ++n_djet_llptrk[djtp];

	      double d0 = 0;
	      double z0 = 0;
	      if ( ancestIx >= 0 ) {
	      	TVector3 pointvec
		( m_truthVtx_x ->at(ancestIx) - m_pv_x, m_truthVtx_y ->at(ancestIx) - m_pv_y, m_truthVtx_z ->at(ancestIx) - m_pv_z );
	      	double dphi_tp_pointvec = EJsHelper::deltaPhi( m_darkJet_tp_phi ->at(i)[djp], pointvec.Phi() );
	      	d0 = m_truthVtx_r ->at(ancestIx) * TMath::Sin( dphi_tp_pointvec );
	      	z0 = m_truthVtx_r ->at(ancestIx) / TMath::Tan( pointvec.Theta() );
	      }
	      h_darkJet_llptrk_dR   [ireg][idj][djtp] ->Fill( m_darkJet_tp_dR ->at(i)[djp], weight );
	      if ( m_histoInfoSwitch->m_djetTrks ) {
		h_darkJet_llptrk_d0 [ireg][idj][djtp] ->Fill( d0,                           weight );
		h_darkJet_llptrk_z0 [ireg][idj][djtp] ->Fill( z0,                           weight );
	      }
	    } // end loop over LLP desc types

	  } // end loop over matched truth particles

	  for ( size_t djtp = 0; djtp != n_djet_llptrk.size(); ++djtp )
	    h_darkJet_nllptrk [ireg][idj][djtp] ->Fill( n_djet_llptrk[djtp], weight );

	} // end loop over truth jet types
	
      } // end loop over truth jets

      // fill truth jet count histograms
      for ( size_t idj = 0; idj != n_darkJet.size(); ++idj ) {
	h_darkJet_n [ireg][idj] ->Fill( n_darkJet[idj], weight );
      }
      
    } // end if mc
    

    
    // ----------------- //
    // --- RECO JETS --- //
    // ----------------- //
    
    // --> DIJETS
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

    TLorentzVector p4jj_maxpt;
    TLorentzVector p4jj_minpt;
    p4jj_maxpt.SetPtEtaPhiM( 0, 0, 0, 0 );
    p4jj_minpt.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<TLorentzVector> p4_dijet_maxpt ( m_nTypeJs, p4jj_maxpt );
    std::vector<TLorentzVector> p4_dijet_minpt ( m_nTypeJs, p4jj_minpt );
    
    std::pair<int, int> p4jj_maxpt_ix = std::make_pair( -1, -1 );
    std::pair<int, int> p4jj_minpt_ix = std::make_pair( -1, -1 );
    std::vector<std::pair<int,int>> p4_dijet_maxpt_ix ( m_nTypeJs, p4jj_maxpt_ix );
    std::vector<std::pair<int,int>> p4_dijet_minpt_ix ( m_nTypeJs, p4jj_minpt_ix );

    std::vector<float> p4_dijet_sum_pt    ( m_nTypeJs, 0 );
    std::vector<float> p4_dijet_sum_eta   ( m_nTypeJs, 0 );
    std::vector<float> p4_dijet_sum_phi   ( m_nTypeJs, 0 );
    std::vector<float> p4_dijet_sum_m     ( m_nTypeJs, 0 );
    std::vector<float> p4_dijet_sum_sumpt ( m_nTypeJs, 0 );
    std::vector<float> p4_dijet_sum_summ  ( m_nTypeJs, 0 );
    std::vector<float> p4_dijet_sum_dr    ( m_nTypeJs, 0 );
    std::vector<int>   p4_dijet_sum_count ( m_nTypeJs, 0 );

    std::vector<int> firstDijet ( m_nTypeJs, 1 ); // test for first dijet of given type

    // ---> (N)JETS
    // set vectors of n-jet sum-p4
    std::vector<int> n_jet ( m_nTypeJs, 0 );
    TLorentzVector jp4sum;
    jp4sum.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<TLorentzVector> jet_p4_sum   ( m_nTypeJs, jp4sum );
    std::vector<float>          jet_p4_sumPt ( m_nTypeJs, 0      );
    std::vector<float>          jet_p4_sumM  ( m_nTypeJs, 0      );
    // --> tracks
    TLorentzVector jp4sum_trk;
    jp4sum_trk.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> jetTracks_p4_sum
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeTrks, jp4sum_trk ) );
    std::vector<std::vector<float>> jetTracks_p4_sumPt   ( m_nTypeJs, std::vector<float> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<float>> jetTracks_p4_sumM    ( m_nTypeJs, std::vector<float> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>>   jetTracks_n          ( m_nTypeJs, std::vector<int>   ( m_nTypeTrks, 0 ) );
    TLorentzVector jjp4max_trk;
    TLorentzVector jjp4min_trk;
    jjp4max_trk.SetPtEtaPhiM( 0, 0, 0, 0 );
    jjp4min_trk.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> dijetTracks_p4_max
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeTrks, jjp4max_trk ) );
    std::vector<std::vector<TLorentzVector>> dijetTracks_p4_min
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeTrks, jjp4min_trk ) );
    std::vector<std::vector<float>> dijetTracks_p4_max_sumPt ( m_nTypeJs, std::vector<float> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<float>> dijetTracks_p4_min_sumPt ( m_nTypeJs, std::vector<float> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<float>> dijetTracks_p4_max_sumM  ( m_nTypeJs, std::vector<float> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<float>> dijetTracks_p4_min_sumM  ( m_nTypeJs, std::vector<float> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>>   dijetTracks_p4_max_n     ( m_nTypeJs, std::vector<int>   ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>>   dijetTracks_p4_min_n     ( m_nTypeJs, std::vector<int>   ( m_nTypeTrks, 0 ) );
    TLorentzVector jjp4maxpt_trk;
    TLorentzVector jjp4minpt_trk;
    jjp4maxpt_trk.SetPtEtaPhiM( 0, 0, 0, 0 );
    jjp4minpt_trk.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> dijetTracks_p4_maxpt
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeTrks, jjp4maxpt_trk ) );
    std::vector<std::vector<TLorentzVector>> dijetTracks_p4_minpt
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeTrks, jjp4minpt_trk ) );
    std::vector<std::vector<float>> dijetTracks_p4_maxpt_sumPt ( m_nTypeJs, std::vector<float> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<float>> dijetTracks_p4_minpt_sumPt ( m_nTypeJs, std::vector<float> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<float>> dijetTracks_p4_maxpt_sumM  ( m_nTypeJs, std::vector<float> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<float>> dijetTracks_p4_minpt_sumM  ( m_nTypeJs, std::vector<float> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>>   dijetTracks_p4_maxpt_n     ( m_nTypeJs, std::vector<int>   ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>>   dijetTracks_p4_minpt_n     ( m_nTypeJs, std::vector<int>   ( m_nTypeTrks, 0 ) );
    // --> secondary vertices
    TLorentzVector jp4sum_sv;
    jp4sum_sv.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> jetSecVerts_p4_sum
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeJDVs, jp4sum_sv  ) );
    std::vector<std::vector<float>> jetSecVerts_p4_sumPt ( m_nTypeJs, std::vector<float> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<float>> jetSecVerts_p4_sumM  ( m_nTypeJs, std::vector<float> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>>   jetSecVerts_n        ( m_nTypeJs, std::vector<int>   ( m_nTypeJDVs, 0 ) );
    TLorentzVector jjp4max_sv;
    TLorentzVector jjp4min_sv;
    jjp4max_sv.SetPtEtaPhiM( 0, 0, 0, 0 );
    jjp4min_sv.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> dijetSecVerts_p4_max
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeJDVs, jjp4max_sv ) );
    std::vector<std::vector<TLorentzVector>> dijetSecVerts_p4_min
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeJDVs, jjp4min_sv ) );
    std::vector<std::vector<float>> dijetSecVerts_p4_max_sumPt ( m_nTypeJs, std::vector<float> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<float>> dijetSecVerts_p4_min_sumPt ( m_nTypeJs, std::vector<float> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<float>> dijetSecVerts_p4_max_sumM  ( m_nTypeJs, std::vector<float> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<float>> dijetSecVerts_p4_min_sumM  ( m_nTypeJs, std::vector<float> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>>   dijetSecVerts_p4_max_n     ( m_nTypeJs, std::vector<int>   ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>>   dijetSecVerts_p4_min_n     ( m_nTypeJs, std::vector<int>   ( m_nTypeJDVs, 0 ) );
    TLorentzVector jjp4maxpt_sv;
    TLorentzVector jjp4minpt_sv;
    jjp4maxpt_sv.SetPtEtaPhiM( 0, 0, 0, 0 );
    jjp4minpt_sv.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> dijetSecVerts_p4_maxpt
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeJDVs, jjp4maxpt_sv ) );
    std::vector<std::vector<TLorentzVector>> dijetSecVerts_p4_minpt
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeJDVs, jjp4minpt_sv ) );
    std::vector<std::vector<float>> dijetSecVerts_p4_maxpt_sumPt ( m_nTypeJs, std::vector<float> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<float>> dijetSecVerts_p4_minpt_sumPt ( m_nTypeJs, std::vector<float> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<float>> dijetSecVerts_p4_maxpt_sumM  ( m_nTypeJs, std::vector<float> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<float>> dijetSecVerts_p4_minpt_sumM  ( m_nTypeJs, std::vector<float> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>>   dijetSecVerts_p4_maxpt_n     ( m_nTypeJs, std::vector<int>   ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>>   dijetSecVerts_p4_minpt_n     ( m_nTypeJs, std::vector<int>   ( m_nTypeJDVs, 0 ) );

    if ( !m_histoInfoSwitch->m_truthOnly ) {
      if ( m_debug ) Info( "EJsHistogramManager::execute()", "doing jet histos" );

      // double loop over jets to calculate di-jet systems
      for ( int i = 0; i != m_jet_n; ++i ) {

	// get jet four-momentum
	TLorentzVector jet_p4;
	jet_p4.SetPtEtaPhiM( m_jet_pt->at(i), m_jet_eta->at(i), m_jet_phi->at(i), m_jet_M->at(i) );
      
	// set vector of jet types
	std::vector<int> jet;
	getJetTypes( i, jet, base_dv );
      
	// loop over jet types and fill histograms
	for ( size_t ij = 0; ij != jet.size(); ++ij ) {
	  if ( !jet[ij] ) continue; // --> skip jet failing ijth jet type selection

	  // double loop
	  for ( int i2 = i+1; i2 != m_jet_n; ++i2 ) {
	    
	    // set vector of jet2 types
	    std::vector<int> jet2;
	    getJetTypes( i2, jet2, base_dv ); 
	    if ( !jet2[ij] ) continue; // --> skip jet2 if not passing ijth jet type cut from above
	    
	    // get jet2 four-momentum
	    TLorentzVector jet2_p4;
	    jet2_p4.SetPtEtaPhiM( m_jet_pt->at(i2), m_jet_eta->at(i2), m_jet_phi->at(i2), m_jet_M->at(i2) );
	    
	    // calculate dijet four-momentum
	    TLorentzVector jj_p4 = jet_p4 + jet2_p4;
	    
	    // sum pt, calculate dR for jet pairs
	    float jj_sumPt = jet_p4.Pt() + jet2_p4.Pt();
	    float jj_sumM  = jet_p4.M()  + jet2_p4.M();
	    float jj_dR    = EJsHelper::deltaR( jet_p4.Eta(), jet2_p4.Eta(), jet_p4.Phi(), jet2_p4.Phi() );
	    
	    if ( doHists && !m_histoInfoSwitch->m_abcdcutOnly && m_histoInfoSwitch->m_dijets ) {
	      h_dijet_pt    [ireg][ij] ->Fill( jj_p4.Pt(),  weight );
	      h_dijet_eta   [ireg][ij] ->Fill( jj_p4.Eta(), weight );
	      h_dijet_phi   [ireg][ij] ->Fill( jj_p4.Phi(), weight );
	      h_dijet_m     [ireg][ij] ->Fill( jj_p4.M(),   weight );
	      h_dijet_sumPt [ireg][ij] ->Fill( jj_sumPt,    weight );
	      h_dijet_sumM  [ireg][ij] ->Fill( jj_sumM,     weight );
	      h_dijet_dR    [ireg][ij] ->Fill( jj_dR,       weight );
	    }
	    
	    // get max/min dijet four-momentum
	    if ( jj_p4.M()  > p4_dijet_max[ij].M()    ) {
	      p4_dijet_max      [ij] = jj_p4;
	      p4_dijet_max_ix   [ij] = std::make_pair( i, i2 );
	    }
	    if ( jj_p4.M()  < p4_dijet_min[ij].M()    || firstDijet[ij] ) { // save first pair as initial min
	      p4_dijet_min      [ij] = jj_p4;
	      p4_dijet_min_ix   [ij] = std::make_pair( i, i2 );
	    }
	    // get max/min-pt dijet four-momentum
	    if ( jj_p4.Pt() > p4_dijet_maxpt[ij].Pt() ) {
	      p4_dijet_maxpt    [ij] = jj_p4;
	      p4_dijet_maxpt_ix [ij] = std::make_pair( i, i2 );
	    }
	    if ( jj_p4.Pt() < p4_dijet_minpt[ij].Pt() || firstDijet[ij] ) { // save first pair as initial min
	      p4_dijet_minpt    [ij] = jj_p4;
	      p4_dijet_minpt_ix [ij] = std::make_pair( i, i2 );
	    }
	    firstDijet[ij] = false;
	    
	    // sum dijet system variables
	    p4_dijet_sum_pt    [ij] += jj_p4.Pt();
	    p4_dijet_sum_eta   [ij] += jj_p4.Eta();
	    p4_dijet_sum_phi   [ij] += jj_p4.Phi();
	    p4_dijet_sum_m     [ij] += jj_p4.M();
	    p4_dijet_sum_sumpt [ij] += jj_sumPt;
	    p4_dijet_sum_summ  [ij] += jj_sumM;
	    p4_dijet_sum_dr    [ij] += jj_dR;
	    p4_dijet_sum_count [ij] += 1;
	    
	  } // end loop over dijets
	} // end loop over jet types
      } // end double loop over jets


      // loop over jets
      for ( int i = 0; i != m_jet_n; ++i ) {

	// get jet four-momentum
	TLorentzVector jet_p4;
	jet_p4.SetPtEtaPhiM( m_jet_pt->at(i), m_jet_eta->at(i), m_jet_phi->at(i), m_jet_M->at(i) );
      
	// set vector of jet types
	std::vector<int> jet;
	getJetTypes( i, jet, base_dv );
      
	// loop over jet types and fill histograms
	for ( size_t ij = 0; ij != jet.size(); ++ij ) {
	  if ( !jet[ij] ) continue; // --> skip jet failing ijth jet type selection
	  ++n_jet[ij];

	  // keep track of lead jet types
	  int inj  = ij / m_LJix; // index of lead jet type in jet type vector

	  // total jet count

	  // sum p4 for all jets in event
	  jet_p4_sum   [ij] += jet_p4;
	  jet_p4_sumPt [ij] += jet_p4.Pt();
	  jet_p4_sumM  [ij] += jet_p4.M();
	  
	  if ( doHists && !m_histoInfoSwitch->m_abcdcutOnly ) {
	    h_jet_pt        [ireg][ij] ->Fill( m_jet_pt        ->at(i), weight );
	    h_jet_pt_s      [ireg][ij] ->Fill( m_jet_pt        ->at(i), weight );
	    h_jet_eta       [ireg][ij] ->Fill( m_jet_eta       ->at(i), weight );
	    h_jet_phi       [ireg][ij] ->Fill( m_jet_phi       ->at(i), weight );
	    h_jet_E         [ireg][ij] ->Fill( m_jet_E         ->at(i), weight );
	    h_jet_M         [ireg][ij] ->Fill( m_jet_M         ->at(i), weight );
	    h_jet_rapid     [ireg][ij] ->Fill( m_jet_rapid     ->at(i), weight );
	    h_jet_nConstits [ireg][ij] ->Fill( m_jet_nConstits ->at(i), weight );
	    // extra jet kinematics
	    if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	      h_jet_px   [ireg][ij] ->Fill( jet_p4.Px(), weight );
	      h_jet_py   [ireg][ij] ->Fill( jet_p4.Py(), weight );
	      h_jet_pz   [ireg][ij] ->Fill( jet_p4.Pz(), weight );
	      h_jet_Et   [ireg][ij] ->Fill( jet_p4.Et(), weight );
	      h_jet_Et_s [ireg][ij] ->Fill( jet_p4.Et(), weight );
	    }

	    // leading jets
	    if ( m_numLeadJets && i < m_numLeadJets ) {
	      h_jetN_pt        [ireg][inj][i] ->Fill( m_jet_pt        ->at(i), weight );
	      h_jetN_pt_s      [ireg][inj][i] ->Fill( m_jet_pt        ->at(i), weight );
	      h_jetN_eta       [ireg][inj][i] ->Fill( m_jet_eta       ->at(i), weight );
	      h_jetN_phi       [ireg][inj][i] ->Fill( m_jet_phi       ->at(i), weight );
	      h_jetN_E         [ireg][inj][i] ->Fill( m_jet_E         ->at(i), weight );
	      h_jetN_M         [ireg][inj][i] ->Fill( m_jet_M         ->at(i), weight );
	      h_jetN_rapid     [ireg][inj][i] ->Fill( m_jet_rapid     ->at(i), weight );
	      h_jetN_nConstits [ireg][inj][i] ->Fill( m_jet_nConstits ->at(i), weight );
	      if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
		h_jetN_Et      [ireg][inj][i] ->Fill( jet_p4.Et(),             weight );
		h_jetN_Et_s    [ireg][inj][i] ->Fill( jet_p4.Et(),             weight );
	      }
	    }
	  
	    // jet calo / cluster (quality) info
	    if ( m_histoInfoSwitch->m_jetCalo ) {
	      // timing = energy-squared weighted average cell time (signal peaking time wrt BC)
	      float absTiming = fabs( m_jet_timing ->at(i) );
	      h_jet_timing          [ireg][ij] ->Fill( absTiming,         weight );
	      h_jet_timing_s        [ireg][ij] ->Fill( absTiming,         weight );
	      h_jet_sqrtTiming      [ireg][ij] ->Fill( sqrt( absTiming ), weight );
	      h_jet_sqrtTiming_s    [ireg][ij] ->Fill( sqrt( absTiming ), weight );
	      // LAr/HEC quality = energy fraction of quality LAr/HEC clusters
	      h_jet_LArQual         [ireg][ij] ->Fill( m_jet_LArQual       ->at(i),  weight );
	      h_jet_HECQual         [ireg][ij] ->Fill( m_jet_HECQual       ->at(i),  weight );
	      h_jet_LArQual_s       [ireg][ij] ->Fill( m_jet_LArQual       ->at(i),  weight );
	      h_jet_HECQual_s       [ireg][ij] ->Fill( m_jet_HECQual       ->at(i),  weight );
	      h_jet_sqrtLArQual     [ireg][ij] ->Fill( sqrt( m_jet_LArQual ->at(i) ),weight );
	      h_jet_sqrtHECQual     [ireg][ij] ->Fill( sqrt( m_jet_HECQual ->at(i) ),weight );
	      h_jet_sqrtLArQual_s   [ireg][ij] ->Fill( sqrt( m_jet_LArQual ->at(i) ),weight );
	      h_jet_sqrtHECQual_s   [ireg][ij] ->Fill( sqrt( m_jet_HECQual ->at(i) ),weight );
	      // normalized energy-squared weighted average LAr quality = avgLArQF/65535
	      float norm_avg = m_jet_avgLArQF ->at(i) / 655335;
	      h_jet_LArQmean        [ireg][ij] ->Fill( norm_avg,         weight );
	      h_jet_sqrtLArQmean    [ireg][ij] ->Fill( sqrt( norm_avg ), weight );
	      // number of clusters holding >90% energy
	      h_jet_n90Constits     [ireg][ij] ->Fill( m_jet_n90Constits ->at(i), weight );
	      // energy-weighted barycenter (in eta, phi) from center (in x,y,z)
	      h_jet_centroidR       [ireg][ij] ->Fill( m_jet_centroidR   ->at(i), weight );
	      // out-of-time-X fraction = energy-weighted fraction of clusters with |time| > X ns
	      h_jet_ootFrac5        [ireg][ij] ->Fill( m_jet_ootFracClust5        ->at(i),   weight );
	      h_jet_ootFrac10       [ireg][ij] ->Fill( m_jet_ootFracClust10       ->at(i),   weight );
	      h_jet_ootFrac5_s      [ireg][ij] ->Fill( m_jet_ootFracClust5        ->at(i),   weight );
	      h_jet_ootFrac10_s     [ireg][ij] ->Fill( m_jet_ootFracClust10       ->at(i),   weight );
	      h_jet_sqrtOotFrac5    [ireg][ij] ->Fill( sqrt( m_jet_ootFracClust5  ->at(i) ), weight );
	      h_jet_sqrtOotFrac10   [ireg][ij] ->Fill( sqrt( m_jet_ootFracClust10 ->at(i) ), weight );
	      h_jet_sqrtOotFrac5_s  [ireg][ij] ->Fill( sqrt( m_jet_ootFracClust5  ->at(i) ), weight );
	      h_jet_sqrtOotFrac10_s [ireg][ij] ->Fill( sqrt( m_jet_ootFracClust10 ->at(i) ), weight );
	      // maximum energy fraction in single calo sampling layer
	      h_jet_fracSampMax     [ireg][ij] ->Fill( m_jet_fracSampMax ->at(i), weight );
	      // leading cluster moments --> CtrL = center lambda (?); 2ndR,L = second moments of r,lambda
	      // --> r = radial distance to shower axis, lambda = longitudinal distance from shower center of gravity
	      h_jet_leadClustPt     [ireg][ij] ->Fill( 0.001 * m_jet_leadClustPt ->at(i), weight );
	      h_jet_leadClustCtrL   [ireg][ij] ->Fill( m_jet_leadClustCtrLambda  ->at(i), weight );
	      h_jet_leadClust2ndL   [ireg][ij] ->Fill( m_jet_leadClust2ndLambda  ->at(i), weight );
	      h_jet_leadClust2ndR   [ireg][ij] ->Fill( m_jet_leadClust2ndR       ->at(i), weight );
	      // energy fraction in EM/HEC calos
	      h_jet_EMFrac          [ireg][ij] ->Fill( m_jet_EMFrac  ->at(i), weight );
	      h_jet_HECFrac         [ireg][ij] ->Fill( m_jet_HECFrac ->at(i), weight );
	      if ( m_jet_HECFrac ->at(i) )
		h_jet_nonzeroHECFrac[ireg][ij] ->Fill( m_jet_HECFrac ->at(i), weight );
	      // width = pt-weighted dR b/w constituents and jet center
	      h_jet_width           [ireg][ij] ->Fill( m_jet_width   ->at(i), weight );
	    }
	    // jets: PV track moments
	    if ( m_histoInfoSwitch->m_jetTrkMom ) {
	      h_jet_ntrkPt10        [ireg][ij] ->Fill( m_jet_ntrkPt10     ->at(i), weight );
	      h_jet_sumPtTrkPt10    [ireg][ij] ->Fill( m_jet_sumPtTrkPt10 ->at(i), weight );
	      h_jet_trkWidthPt10    [ireg][ij] ->Fill( m_jet_trkWidthPt10 ->at(i), weight );
	      h_jet_ntrkPt5         [ireg][ij] ->Fill( m_jet_ntrkPt5      ->at(i), weight );
	      h_jet_sumPtTrkPt5     [ireg][ij] ->Fill( m_jet_sumPtTrkPt5  ->at(i), weight );
	      h_jet_trkWidthPt5     [ireg][ij] ->Fill( m_jet_trkWidthPt5  ->at(i), weight );
	      h_jet_JVF             [ireg][ij] ->Fill( m_jet_JVF          ->at(i), weight );
	    }
	    if ( m_mc )
	      h_jet_partonID        [ireg][ij] ->Fill( m_jet_partonID     ->at(i), weight );
	  } // end if not abcdcutOnly

	  // ghost tracks
	
	  // matched tracks
	  std::vector<int>    n_jettrk        ( m_nTypeTrks, 0                   );
	  std::vector<double> jettrk_minDR    ( m_nTypeTrks, AlgConsts::maxValue );
	  std::vector<double> jettrk_maxDR    ( m_nTypeTrks, 0                   );
	  std::vector<double> jettrk_mind0    ( m_nTypeTrks, AlgConsts::maxValue );
	  std::vector<double> jettrk_maxd0    ( m_nTypeTrks, 0                   );
	  std::vector<double> jettrk_sumd0    ( m_nTypeTrks, 0                   );
	  std::vector<double> jettrk_minz0    ( m_nTypeTrks, AlgConsts::maxValue );
	  std::vector<double> jettrk_maxz0    ( m_nTypeTrks, 0                   );
	  std::vector<double> jettrk_sumz0    ( m_nTypeTrks, 0                   );
	  std::vector<double> jettrk_minerrd0 ( m_nTypeTrks, AlgConsts::maxValue );
	  std::vector<double> jettrk_maxerrd0 ( m_nTypeTrks, 0                   );
	  std::vector<double> jettrk_sumerrd0 ( m_nTypeTrks, 0                   );
	  std::vector<double> jettrk_minerrz0 ( m_nTypeTrks, AlgConsts::maxValue );
	  std::vector<double> jettrk_maxerrz0 ( m_nTypeTrks, 0                   );
	  std::vector<double> jettrk_sumerrz0 ( m_nTypeTrks, 0                   );
	  TLorentzVector jtp4sum;
	  jtp4sum.SetPtEtaPhiM( 0, 0, 0, 0 );
	  std::vector<TLorentzVector> jettrk_p4_sum   ( m_nTypeTrks, jtp4sum );
	  std::vector<double>         jettrk_p4_sumPt ( m_nTypeTrks, 0       );
	  std::vector<double>         jettrk_p4_sumM  ( m_nTypeTrks, 0       );
	  // loop over matched tracks
	  for ( int jtrk = 0; jtrk != m_jet_trk_n ->at(i); ++jtrk ) {
	    int    jetTrkIx = m_jet_trk_index ->at(i)[jtrk];
	    double dR       = m_jet_trk_dR    ->at(i)[jtrk];
	    double pt       = m_trk_pt        ->at(jetTrkIx);
	    double eta      = m_trk_eta       ->at(jetTrkIx);
	    double phi      = m_trk_phi       ->at(jetTrkIx);
	    double M        = m_trk_M         ->at(jetTrkIx);
	    double d0       = fabs( m_trk_d0  ->at(jetTrkIx) );
	    double z0       = fabs( m_trk_z0  ->at(jetTrkIx) );
	    double errd0    = m_trk_errd0     ->at(jetTrkIx);
	    double errz0    = m_trk_errz0     ->at(jetTrkIx);
	    int    nSCT     = m_trk_nSCT      ->at(jetTrkIx);
	    int    nPixel   = m_trk_nPixel    ->at(jetTrkIx);
	    int    nTRT     = m_trk_nTRT      ->at(jetTrkIx);

	    // get matched track four-momentum
	    TLorentzVector jettrk_p4;
	    jettrk_p4.SetPtEtaPhiM( pt, eta, phi, M );
	  
	    // set vector of matched track types
	    std::vector<int> jettrk;
	    getTrkTypes( jetTrkIx, jettrk, base_dv );
	    // loop over matched track types
	    for ( unsigned jt = 0; jt != m_nTypeTrks; ++jt ) {
	      if ( !jettrk[jt] ) continue;
	      ++n_jettrk[jt]; 

	      if ( doHists && !m_histoInfoSwitch->m_abcdcutOnly ) {
		// dR b/w jet + matched track
		h_jet_trk_dR          [ireg][ij][jt] ->Fill( dR,                weight );
		if ( m_histoInfoSwitch->m_jetTrks ) {
		  // pt
		  h_jet_trk_pt        [ireg][ij][jt] ->Fill( pt,                weight );
		  h_jet_trk_sqrtpt    [ireg][ij][jt] ->Fill( sqrt(pt),          weight );
		  // d0
		  h_jet_trk_d0        [ireg][ij][jt] ->Fill( d0,                weight );
		  h_jet_trk_sqrtd0    [ireg][ij][jt] ->Fill( sqrt(d0),          weight );
		  // z0
		  h_jet_trk_z0        [ireg][ij][jt] ->Fill( z0,                weight );
		  h_jet_trk_sqrtz0    [ireg][ij][jt] ->Fill( sqrt(z0),          weight );
		  // d0 uncertainty
		  h_jet_trk_errd0     [ireg][ij][jt] ->Fill( sqrt(errd0),       weight );
		  h_jet_trk_sqrterrd0 [ireg][ij][jt] ->Fill( sqrt(sqrt(errd0)), weight );
		  // z0 uncertainty
		  h_jet_trk_errz0     [ireg][ij][jt] ->Fill( sqrt(errz0),       weight );
		  h_jet_trk_sqrterrz0 [ireg][ij][jt] ->Fill( sqrt(sqrt(errz0)), weight );
		  // hits
		  h_jet_trk_nSCT      [ireg][ij][jt] ->Fill( nSCT,              weight );
		  h_jet_trk_nPixel    [ireg][ij][jt] ->Fill( nPixel,            weight );
		  h_jet_trk_nSi       [ireg][ij][jt] ->Fill( nSCT + nPixel,     weight );
		  h_jet_trk_nTRT      [ireg][ij][jt] ->Fill( nTRT,              weight );
		}
	      }

	      // dR b/w jet + matched track
	      if ( dR    < jettrk_minDR   [jt] ) jettrk_minDR   [jt] = dR;
	      if ( dR    > jettrk_maxDR   [jt] ) jettrk_maxDR   [jt] = dR;
	      // d0
	      if ( d0    < jettrk_mind0   [jt] ) jettrk_mind0   [jt] = d0;
	      if ( d0    > jettrk_maxd0   [jt] ) jettrk_maxd0   [jt] = d0;
	      jettrk_sumd0    [jt] += d0;
	      // z0
	      if ( z0    < jettrk_minz0   [jt] ) jettrk_minz0   [jt] = z0;
	      if ( z0    > jettrk_maxz0   [jt] ) jettrk_maxz0   [jt] = z0;
	      jettrk_sumz0    [jt] += z0;
	      // d0 uncertainty
	      if ( errd0 < jettrk_minerrd0[jt] ) jettrk_minerrd0[jt] = errd0;
	      if ( errd0 > jettrk_maxerrd0[jt] ) jettrk_maxerrd0[jt] = errd0;
	      jettrk_sumerrd0 [jt] += errd0;
	      // z0 uncertainty
	      if ( errz0 < jettrk_minerrz0[jt] ) jettrk_minerrz0[jt] = errz0;
	      if ( errz0 > jettrk_maxerrz0[jt] ) jettrk_maxerrz0[jt] = errz0;
	      jettrk_sumerrz0 [jt] += errz0;
	      // sum p4 for all matched tracks in jet
	      jettrk_p4_sum   [jt] += jettrk_p4;
	      jettrk_p4_sumPt [jt] += pt;
	      jettrk_p4_sumM  [jt] += M;
	    
	    } // end loop over matched track types
	  } // end loop over matched tracks
      
	  // fill matched track count, min/max/sum, n-track-p4 histograms
	  for ( unsigned jt = 0; jt != m_nTypeTrks; ++jt ) {
	    if ( doHists && !m_histoInfoSwitch->m_abcdcutOnly ) {
	      h_jet_ntrk    [ireg][ij][jt]    ->Fill( n_jettrk [jt], weight );
	      if ( m_numLeadJets && i < m_numLeadJets )
		h_jetN_ntrk [ireg][inj][i][jt] ->Fill( n_jettrk [jt], weight );

	      if ( n_jettrk[jt] ) {
		h_jet_trk_minDR          [ireg][ij][jt] ->Fill( jettrk_minDR[jt],                weight );
		h_jet_trk_maxDR          [ireg][ij][jt] ->Fill( jettrk_maxDR[jt],                weight );
		if ( m_histoInfoSwitch->m_jetTrks ) {
		  h_jet_trk_mind0        [ireg][ij][jt] ->Fill( jettrk_mind0[jt],                weight );
		  h_jet_trk_maxd0        [ireg][ij][jt] ->Fill( jettrk_maxd0[jt],                weight );
		  h_jet_trk_sumd0        [ireg][ij][jt] ->Fill( jettrk_sumd0[jt],                weight );
		  h_jet_trk_minz0        [ireg][ij][jt] ->Fill( jettrk_minz0[jt],                weight );
		  h_jet_trk_maxz0        [ireg][ij][jt] ->Fill( jettrk_maxz0[jt],                weight );
		  h_jet_trk_sumz0        [ireg][ij][jt] ->Fill( jettrk_sumz0[jt],                weight );
		  h_jet_trk_minErrd0     [ireg][ij][jt] ->Fill( sqrt(jettrk_minerrd0[jt]),       weight );
		  h_jet_trk_maxErrd0     [ireg][ij][jt] ->Fill( sqrt(jettrk_maxerrd0[jt]),       weight );
		  h_jet_trk_sumErrd0     [ireg][ij][jt] ->Fill( sqrt(jettrk_sumerrd0[jt]),       weight );
		  h_jet_trk_minErrz0     [ireg][ij][jt] ->Fill( sqrt(jettrk_minerrz0[jt]),       weight );
		  h_jet_trk_maxErrz0     [ireg][ij][jt] ->Fill( sqrt(jettrk_maxerrz0[jt]),       weight );
		  h_jet_trk_sumErrz0     [ireg][ij][jt] ->Fill( sqrt(jettrk_sumerrz0[jt]),       weight );
		  h_jet_trk_sqrtmind0    [ireg][ij][jt] ->Fill( sqrt(jettrk_mind0[jt]),          weight );
		  h_jet_trk_sqrtmaxd0    [ireg][ij][jt] ->Fill( sqrt(jettrk_maxd0[jt]),          weight );
		  h_jet_trk_sqrtsumd0    [ireg][ij][jt] ->Fill( sqrt(jettrk_sumd0[jt]),          weight );
		  h_jet_trk_sqrtminz0    [ireg][ij][jt] ->Fill( sqrt(jettrk_minz0[jt]),          weight );
		  h_jet_trk_sqrtmaxz0    [ireg][ij][jt] ->Fill( sqrt(jettrk_maxz0[jt]),          weight );
		  h_jet_trk_sqrtsumz0    [ireg][ij][jt] ->Fill( sqrt(jettrk_sumz0[jt]),          weight );
		  h_jet_trk_sqrtminErrd0 [ireg][ij][jt] ->Fill( sqrt(sqrt(jettrk_minerrd0[jt])), weight );
		  h_jet_trk_sqrtmaxErrd0 [ireg][ij][jt] ->Fill( sqrt(sqrt(jettrk_maxerrd0[jt])), weight );
		  h_jet_trk_sqrtsumErrd0 [ireg][ij][jt] ->Fill( sqrt(sqrt(jettrk_sumerrd0[jt])), weight );
		  h_jet_trk_sqrtminErrz0 [ireg][ij][jt] ->Fill( sqrt(sqrt(jettrk_minerrz0[jt])), weight );
		  h_jet_trk_sqrtmaxErrz0 [ireg][ij][jt] ->Fill( sqrt(sqrt(jettrk_maxerrz0[jt])), weight );
		  h_jet_trk_sqrtsumErrz0 [ireg][ij][jt] ->Fill( sqrt(sqrt(jettrk_sumerrz0[jt])), weight );
		  h_jet_ntrk_pt          [ireg][ij][jt] ->Fill( jettrk_p4_sum  [jt].Pt(),        weight );
		  h_jet_ntrk_eta         [ireg][ij][jt] ->Fill( jettrk_p4_sum  [jt].Eta(),       weight );
		  h_jet_ntrk_phi         [ireg][ij][jt] ->Fill( jettrk_p4_sum  [jt].Phi(),       weight );
		  h_jet_ntrk_m           [ireg][ij][jt] ->Fill( jettrk_p4_sum  [jt].M(),         weight ); 
		  h_jet_ntrk_sumPt       [ireg][ij][jt] ->Fill( jettrk_p4_sumPt[jt],             weight );
		  h_jet_ntrk_sqrtsumPt   [ireg][ij][jt] ->Fill( sqrt(jettrk_p4_sumPt[jt]),       weight );
		}
		if ( m_numLeadJets && i < m_numLeadJets ) {
		  h_jetN_trk_minDR          [ireg][inj][i][jt] ->Fill( jettrk_minDR[jt],                weight );
		  h_jetN_trk_maxDR          [ireg][inj][i][jt] ->Fill( jettrk_maxDR[jt],                weight );
		  if ( m_histoInfoSwitch->m_jetTrks ) {
		    h_jetN_trk_mind0        [ireg][inj][i][jt] ->Fill( jettrk_mind0[jt],                weight );
		    h_jetN_trk_maxd0        [ireg][inj][i][jt] ->Fill( jettrk_maxd0[jt],                weight );
		    h_jetN_trk_sumd0        [ireg][inj][i][jt] ->Fill( jettrk_sumd0[jt],                weight );
		    h_jetN_trk_minz0        [ireg][inj][i][jt] ->Fill( jettrk_minz0[jt],                weight );
		    h_jetN_trk_maxz0        [ireg][inj][i][jt] ->Fill( jettrk_maxz0[jt],                weight );
		    h_jetN_trk_sumz0        [ireg][inj][i][jt] ->Fill( jettrk_sumz0[jt],                weight );
		    h_jetN_trk_minErrd0     [ireg][inj][i][jt] ->Fill( sqrt(jettrk_minerrd0[jt]),       weight );
		    h_jetN_trk_maxErrd0     [ireg][inj][i][jt] ->Fill( sqrt(jettrk_maxerrd0[jt]),       weight );
		    h_jetN_trk_sumErrd0     [ireg][inj][i][jt] ->Fill( sqrt(jettrk_sumerrd0[jt]),       weight );
		    h_jetN_trk_minErrz0     [ireg][inj][i][jt] ->Fill( sqrt(jettrk_minerrz0[jt]),       weight );
		    h_jetN_trk_maxErrz0     [ireg][inj][i][jt] ->Fill( sqrt(jettrk_maxerrz0[jt]),       weight );
		    h_jetN_trk_sumErrz0     [ireg][inj][i][jt] ->Fill( sqrt(jettrk_sumerrz0[jt]),       weight );
		    h_jetN_trk_sqrtmind0    [ireg][inj][i][jt] ->Fill( sqrt(jettrk_mind0[jt]),          weight );
		    h_jetN_trk_sqrtmaxd0    [ireg][inj][i][jt] ->Fill( sqrt(jettrk_maxd0[jt]),          weight );
		    h_jetN_trk_sqrtsumd0    [ireg][inj][i][jt] ->Fill( sqrt(jettrk_sumd0[jt]),          weight );
		    h_jetN_trk_sqrtminz0    [ireg][inj][i][jt] ->Fill( sqrt(jettrk_minz0[jt]),          weight );
		    h_jetN_trk_sqrtmaxz0    [ireg][inj][i][jt] ->Fill( sqrt(jettrk_maxz0[jt]),          weight );
		    h_jetN_trk_sqrtsumz0    [ireg][inj][i][jt] ->Fill( sqrt(jettrk_sumz0[jt]),          weight );
		    h_jetN_trk_sqrtminErrd0 [ireg][inj][i][jt] ->Fill( sqrt(sqrt(jettrk_minerrd0[jt])), weight );
		    h_jetN_trk_sqrtmaxErrd0 [ireg][inj][i][jt] ->Fill( sqrt(sqrt(jettrk_maxerrd0[jt])), weight );
		    h_jetN_trk_sqrtsumErrd0 [ireg][inj][i][jt] ->Fill( sqrt(sqrt(jettrk_sumerrd0[jt])), weight );
		    h_jetN_trk_sqrtminErrz0 [ireg][inj][i][jt] ->Fill( sqrt(sqrt(jettrk_minerrz0[jt])), weight );
		    h_jetN_trk_sqrtmaxErrz0 [ireg][inj][i][jt] ->Fill( sqrt(sqrt(jettrk_maxerrz0[jt])), weight );
		    h_jetN_trk_sqrtsumErrz0 [ireg][inj][i][jt] ->Fill( sqrt(sqrt(jettrk_sumerrz0[jt])), weight );
		    h_jetN_ntrk_pt          [ireg][inj][i][jt] ->Fill ( jettrk_p4_sum  [jt].Pt(),       weight );
		    h_jetN_ntrk_eta         [ireg][inj][i][jt] ->Fill ( jettrk_p4_sum  [jt].Eta(),      weight );
		    h_jetN_ntrk_phi         [ireg][inj][i][jt] ->Fill ( jettrk_p4_sum  [jt].Phi(),      weight );
		    h_jetN_ntrk_m           [ireg][inj][i][jt] ->Fill ( jettrk_p4_sum  [jt].M(),        weight );
		    h_jetN_ntrk_sumPt       [ireg][inj][i][jt] ->Fill ( jettrk_p4_sumPt[jt],            weight );
		    h_jetN_ntrk_sqrtsumPt   [ireg][inj][i][jt] ->Fill ( sqrt(jettrk_p4_sumPt[jt]),      weight );
		  }
		}
	      } // end if n jet tracks
	    } // end if doHists
	  
	    // sum p4 for all matched tracks in all jets in event
	    jetTracks_n        [ij][jt] += n_jettrk        [jt];
	    jetTracks_p4_sum   [ij][jt] += jettrk_p4_sum   [jt];
	    jetTracks_p4_sumPt [ij][jt] += jettrk_p4_sumPt [jt];
	    jetTracks_p4_sumM  [ij][jt] += jettrk_p4_sumM  [jt];
	    // sum p4 for all matched tracks in min/max dijets
	    int maxix1 = p4_dijet_max_ix[ij].first; int maxix2 = p4_dijet_max_ix[ij].second;
	    int minix1 = p4_dijet_min_ix[ij].first; int minix2 = p4_dijet_min_ix[ij].second;
	    if ( m_jet_index ->at(i) == maxix1   || m_jet_index ->at(i) == maxix2   ) {
	      dijetTracks_p4_max         [ij][jt] += jettrk_p4_sum   [jt];
	      dijetTracks_p4_max_sumPt   [ij][jt] += jettrk_p4_sumPt [jt];
	      dijetTracks_p4_max_sumM    [ij][jt] += jettrk_p4_sumM  [jt];
	      dijetTracks_p4_max_n       [ij][jt] += n_jettrk        [jt];
	    }
	    if ( m_jet_index ->at(i) == minix1   || m_jet_index ->at(i) == minix2   ) {
	      dijetTracks_p4_min         [ij][jt] += jettrk_p4_sum   [jt];
	      dijetTracks_p4_min_sumPt   [ij][jt] += jettrk_p4_sumPt [jt];
	      dijetTracks_p4_min_sumM    [ij][jt] += jettrk_p4_sumM  [jt];
	      dijetTracks_p4_min_n       [ij][jt] += n_jettrk        [jt];
	    }
	    int maxptix1 = p4_dijet_maxpt_ix[ij].first; int maxptix2 = p4_dijet_maxpt_ix[ij].second;
	    int minptix1 = p4_dijet_minpt_ix[ij].first; int minptix2 = p4_dijet_minpt_ix[ij].second;
	    if ( m_jet_index ->at(i) == maxptix1 || m_jet_index ->at(i) == maxptix2 ) {
	      dijetTracks_p4_maxpt       [ij][jt] += jettrk_p4_sum   [jt];
	      dijetTracks_p4_maxpt_sumPt [ij][jt] += jettrk_p4_sumPt [jt];
	      dijetTracks_p4_maxpt_sumM  [ij][jt] += jettrk_p4_sumM  [jt];
	      dijetTracks_p4_maxpt_n     [ij][jt] += n_jettrk        [jt];
	    }
	    if ( m_jet_index ->at(i) == minptix1 || m_jet_index ->at(i) == minptix2 ) {
	      dijetTracks_p4_minpt       [ij][jt] += jettrk_p4_sum   [jt];
	      dijetTracks_p4_minpt_sumPt [ij][jt] += jettrk_p4_sumPt [jt];
	      dijetTracks_p4_minpt_sumM  [ij][jt] += jettrk_p4_sumM  [jt];
	      dijetTracks_p4_minpt_n     [ij][jt] += n_jettrk        [jt];
	    }
	  } // end loop over jet track types

	
	  // matched secondary vertices
	  std::vector<int>    n_jetsv       ( m_nTypeJDVs, 0                   );
	  std::vector<double> jetsv_minDR   ( m_nTypeJDVs, AlgConsts::maxValue );
	  std::vector<double> jetsv_maxDR   ( m_nTypeJDVs, 0                   );
	  std::vector<double> jetsv_minz    ( m_nTypeJDVs, AlgConsts::maxValue );
	  std::vector<double> jetsv_maxz    ( m_nTypeJDVs, 0                   );
	  std::vector<double> jetsv_sumz    ( m_nTypeJDVs, 0                   );
	  std::vector<double> jetsv_minr    ( m_nTypeJDVs, AlgConsts::maxValue );
	  std::vector<double> jetsv_maxr    ( m_nTypeJDVs, 0                   );
	  std::vector<double> jetsv_sumr    ( m_nTypeJDVs, 0                   );
	  TLorentzVector jvp4sum;
	  jvp4sum.SetPtEtaPhiM( 0, 0, 0, 0 );
	  std::vector<TLorentzVector> jetsv_p4_sum   ( m_nTypeJDVs, jvp4sum );
	  std::vector<double>         jetsv_p4_sumPt ( m_nTypeJDVs, 0       );
	  std::vector<double>         jetsv_p4_sumHt ( m_nTypeJDVs, 0       );
	  std::vector<double>         jetsv_p4_sumH  ( m_nTypeJDVs, 0       );
	  std::vector<double>         jetsv_p4_sumM  ( m_nTypeJDVs, 0       );
	  std::vector<double>         jetsv_p4_ntrk  ( m_nTypeJDVs, 0       );
	  std::vector<double>         jetsv_p4_njtrk ( m_nTypeJDVs, 0       );
	  // loop over matched secondary vertices
	  for ( int jsv = 0; jsv != m_jet_secVtx_n ->at(i); ++jsv ) {
	    int   jetSvIx = m_jet_secVtx_index ->at(i)[jsv];
	    float pt      = 0;
	    float ht      = 0; 
	    float h       = 0;
	    float eta     = 0;
	    float phi     = 0;
	    float mass    = 0;
	    int   ntrk    = 0;
	    if      ( base_dv.type == EJsHelper::BARE     ) {
	      pt    = m_secVtx_pt_bare    ->at(jetSvIx);
	      ht    = m_secVtx_Ht_bare    ->at(jetSvIx);
	      h     = m_secVtx_H_bare     ->at(jetSvIx);
	      eta   = m_secVtx_eta_bare   ->at(jetSvIx);
	      phi   = m_secVtx_phi_bare   ->at(jetSvIx);
	      mass  = m_secVtx_mass_bare  ->at(jetSvIx);
	      ntrk  = m_secVtx_ntrk       ->at(jetSvIx);
	    }
	    else if ( base_dv.type == EJsHelper::CLEAN    ) {
	      pt    = m_secVtx_pt_clean   ->at(jetSvIx);
	      ht    = m_secVtx_Ht_clean   ->at(jetSvIx);
	      h     = m_secVtx_H_clean    ->at(jetSvIx);
	      eta   = m_secVtx_eta_clean  ->at(jetSvIx);
	      phi   = m_secVtx_phi_clean  ->at(jetSvIx);
	      mass  = m_secVtx_mass_clean ->at(jetSvIx);
	      ntrk  = m_secVtx_ntrk_clean ->at(jetSvIx);
	    }
	    else if ( base_dv.type == EJsHelper::FILTERED ) {
	      pt    = m_secVtx_pt         ->at(jetSvIx);
	      ht    = m_secVtx_Ht         ->at(jetSvIx);
	      h     = m_secVtx_H          ->at(jetSvIx);
	      eta   = m_secVtx_eta        ->at(jetSvIx);
	      phi   = m_secVtx_phi        ->at(jetSvIx);
	      mass  = m_secVtx_mass       ->at(jetSvIx);
	      ntrk  = m_secVtx_ntrk_filt  ->at(jetSvIx);
	    }
	    float z       = fabs( m_secVtx_z   ->at(jetSvIx) );
	    float r       = m_secVtx_r         ->at(jetSvIx);
	    float chi2    = m_secVtx_chi2      ->at(jetSvIx);
	  
	    double dR     = m_jet_secVtx_dR    ->at(i)[jsv];
	    int    njtrk  = 0;
	    for ( int svtrk = 0; svtrk != m_secVtx_ntrk ->at(jetSvIx); ++svtrk ) {
	      if ( base_dv.type == EJsHelper::CLEAN    && !m_secVtx_trk_isClean ->at(jetSvIx)[svtrk] ) continue;
	      if ( base_dv.type == EJsHelper::FILTERED && !m_secVtx_trk_isFilt  ->at(jetSvIx)[svtrk] ) continue;
	      // if ( base_dv.type == EJsHelper::TRIMMED && *track fails trimming cuts* ) continue;
	      int svtrkIx = m_secVtx_trk_index ->at(jetSvIx)[svtrk];
	      if ( m_trk_jetMatch    ->at(svtrkIx) &&
		   m_trk_jetMatch_ID ->at(svtrkIx) == m_jet_ID ->at(i) ) ++njtrk;
	    }

	    // get matched secondary vertex four-momentum
	    TLorentzVector jetsv_p4;
	    jetsv_p4.SetPtEtaPhiM( pt, eta, phi, mass );

	    // set vector of matched secondary vertex types
	    std::vector<int> jetsv;
	    getDVTypes( jetSvIx, jetsv, base_dv, m_doComboDVs, true );
	    // loop over matched secondary vertex types
	    for ( size_t jv = 0; jv != jetsv.size(); ++jv ) {
	      if ( !jetsv[jv] ) continue;
	      ++n_jetsv[jv];

	      if ( doHists && !m_histoInfoSwitch->m_abcdcutOnly ) {
		// dR b/w jet and SV
		h_jet_sv_dR [ireg][ij][jv] ->Fill( dR, weight );
		if ( m_histoInfoSwitch->m_jetVerts ) {
		  // pt (system of dv tracks)
		  h_jet_sv_pt     [ireg][ij][jv] ->Fill( pt,       weight );
		  h_jet_sv_sqrtpt [ireg][ij][jv] ->Fill( sqrt(pt), weight );
		  // sum-pt (dv tracks)
		  h_jet_sv_Ht     [ireg][ij][jv] ->Fill( ht,       weight );
		  h_jet_sv_sqrtHt [ireg][ij][jv] ->Fill( sqrt(ht), weight );
		  // sum-p (sum-p4-mag dv tracks)
		  h_jet_sv_H      [ireg][ij][jv] ->Fill( h,        weight );
		  h_jet_sv_sqrtH  [ireg][ij][jv] ->Fill( sqrt(h),  weight );
		  // mass (mag-sum-p4 dv tracks)
		  h_jet_sv_mass   [ireg][ij][jv] ->Fill( mass,     weight );
		  h_jet_sv_mass_s [ireg][ij][jv] ->Fill( mass,     weight );
		  // n-trk
		  h_jet_sv_ntrk   [ireg][ij][jv] ->Fill( ntrk,     weight );
		  // n-jettrk
		  h_jet_sv_njtrk  [ireg][ij][jv] ->Fill( njtrk,    weight );
		  // z-position
		  h_jet_sv_z      [ireg][ij][jv] ->Fill( z,        weight );
		  // r-position
		  h_jet_sv_r      [ireg][ij][jv] ->Fill( r,        weight );
		  // chi-squared
		  h_jet_sv_chi2   [ireg][ij][jv] ->Fill( chi2,     weight );
		}
	      }
	    
	      // dR b/w jet and SV
	      if ( dR < jetsv_minDR[jv] ) jetsv_minDR[jv] = dR;
	      if ( dR > jetsv_maxDR[jv] ) jetsv_maxDR[jv] = dR;
	      // z-position
	      if ( z < jetsv_minz[jv] ) jetsv_minz[jv] = z;
	      if ( z > jetsv_maxz[jv] ) jetsv_maxz[jv] = z;
	      jetsv_sumz[jv] += z;
	      // r-position
	      if ( r < jetsv_minr[jv] ) jetsv_minr[jv] = r;
	      if ( r > jetsv_maxr[jv] ) jetsv_maxr[jv] = r;
	      jetsv_sumr[jv] += r;
	    
	      // sum p4 for all matched secondary vertices in jet
	      jetsv_p4_sum   [jv] += jetsv_p4; 
	      jetsv_p4_sumPt [jv] += pt;
	      jetsv_p4_sumHt [jv] += ht;
	      jetsv_p4_sumH  [jv] += h;
	      jetsv_p4_sumM  [jv] += mass;
	      jetsv_p4_ntrk  [jv] += ntrk;
	      jetsv_p4_njtrk [jv] += njtrk;
	    
	    } // end loop over matched secondary vertex types
	  } // end loop over matched secondary vertices

	  // fill matched secondary vertex count, min/max/sum/avg histograms
	  for ( size_t jv = 0; jv != n_jetsv.size(); ++jv ) {
	    if ( doHists && !m_histoInfoSwitch->m_abcdcutOnly ) {
	      h_jet_nsv    [ireg][ij][jv]    ->Fill( n_jetsv [jv], weight );
	      if ( m_numLeadJets && i < m_numLeadJets )
		h_jetN_nsv [ireg][inj][i][jv] ->Fill( n_jetsv [jv], weight );

	      if ( n_jetsv[jv] ) {
		h_jet_sv_minDR        [ireg][ij][jv] ->Fill( jetsv_minDR        [jv],       weight );
		h_jet_sv_maxDR        [ireg][ij][jv] ->Fill( jetsv_maxDR        [jv],       weight );
		if ( m_histoInfoSwitch->m_jetVerts && n_jetsv[jv] ) {
		  h_jet_sv_minz       [ireg][ij][jv] ->Fill( jetsv_minz         [jv],       weight );
		  h_jet_sv_maxz       [ireg][ij][jv] ->Fill( jetsv_maxz         [jv],       weight );
		  h_jet_sv_sumz       [ireg][ij][jv] ->Fill( jetsv_sumz         [jv],       weight );
		  h_jet_sv_minr       [ireg][ij][jv] ->Fill( jetsv_minr         [jv],       weight );
		  h_jet_sv_maxr       [ireg][ij][jv] ->Fill( jetsv_maxr         [jv],       weight );
		  h_jet_sv_sumr       [ireg][ij][jv] ->Fill( jetsv_sumr         [jv],       weight );
		  h_jet_nsv_pt        [ireg][ij][jv] ->Fill( jetsv_p4_sum       [jv].Pt(),  weight );
		  h_jet_nsv_eta       [ireg][ij][jv] ->Fill( jetsv_p4_sum       [jv].Eta(), weight );
		  h_jet_nsv_phi       [ireg][ij][jv] ->Fill( jetsv_p4_sum       [jv].Phi(), weight );
		  h_jet_nsv_m         [ireg][ij][jv] ->Fill( jetsv_p4_sum       [jv].M(),   weight );
		  h_jet_nsv_sumPt     [ireg][ij][jv] ->Fill( jetsv_p4_sumPt     [jv],       weight );
		  h_jet_nsv_sumHt     [ireg][ij][jv] ->Fill( jetsv_p4_sumHt     [jv],       weight );
		  h_jet_nsv_sumH      [ireg][ij][jv] ->Fill( jetsv_p4_sumH      [jv],       weight );
		  h_jet_nsv_sqrtsumPt [ireg][ij][jv] ->Fill( sqrt(jetsv_p4_sumPt[jv]),      weight );
		  h_jet_nsv_sqrtsumHt [ireg][ij][jv] ->Fill( sqrt(jetsv_p4_sumHt[jv]),      weight );
		  h_jet_nsv_sqrtsumH  [ireg][ij][jv] ->Fill( sqrt(jetsv_p4_sumH [jv]),      weight );
		  h_jet_nsv_sumMass   [ireg][ij][jv] ->Fill( jetsv_p4_sumM      [jv],       weight );
		  h_jet_nsv_sumMass_s [ireg][ij][jv] ->Fill( jetsv_p4_sumM      [jv],       weight );
		  h_jet_nsv_ntrk      [ireg][ij][jv] ->Fill( jetsv_p4_ntrk      [jv],       weight );
		  h_jet_nsv_njtrk     [ireg][ij][jv] ->Fill( jetsv_p4_njtrk     [jv],       weight );
		}
		if ( m_numLeadJets && i < m_numLeadJets ) {
		  h_jetN_sv_minDR        [ireg][inj][i][jv] ->Fill( jetsv_minDR        [jv],       weight );
		  h_jetN_sv_maxDR        [ireg][inj][i][jv] ->Fill( jetsv_maxDR        [jv],       weight );
		  if ( m_histoInfoSwitch->m_jetVerts ) {
		    h_jetN_sv_minz       [ireg][inj][i][jv] ->Fill( jetsv_minz         [jv],       weight );
		    h_jetN_sv_maxz       [ireg][inj][i][jv] ->Fill( jetsv_maxz         [jv],       weight );
		    h_jetN_sv_sumz       [ireg][inj][i][jv] ->Fill( jetsv_sumz         [jv],       weight );
		    h_jetN_sv_minr       [ireg][inj][i][jv] ->Fill( jetsv_minr         [jv],       weight );
		    h_jetN_sv_maxr       [ireg][inj][i][jv] ->Fill( jetsv_maxr         [jv],       weight );
		    h_jetN_sv_sumr       [ireg][inj][i][jv] ->Fill( jetsv_sumr         [jv],       weight );
		    h_jetN_nsv_pt        [ireg][inj][i][jv] ->Fill( jetsv_p4_sum       [jv].Pt(),  weight );
		    h_jetN_nsv_eta       [ireg][inj][i][jv] ->Fill( jetsv_p4_sum       [jv].Eta(), weight );
		    h_jetN_nsv_phi       [ireg][inj][i][jv] ->Fill( jetsv_p4_sum       [jv].Phi(), weight );
		    h_jetN_nsv_m         [ireg][inj][i][jv] ->Fill( jetsv_p4_sum       [jv].M(),   weight );
		    h_jetN_nsv_sumPt     [ireg][inj][i][jv] ->Fill( jetsv_p4_sumPt     [jv],       weight );
		    h_jetN_nsv_sumHt     [ireg][inj][i][jv] ->Fill( jetsv_p4_sumHt     [jv],       weight );
		    h_jetN_nsv_sumH      [ireg][inj][i][jv] ->Fill( jetsv_p4_sumH      [jv],       weight );
		    h_jetN_nsv_sqrtsumPt [ireg][inj][i][jv] ->Fill( sqrt(jetsv_p4_sumPt[jv]),      weight );
		    h_jetN_nsv_sqrtsumHt [ireg][inj][i][jv] ->Fill( sqrt(jetsv_p4_sumHt[jv]),      weight );
		    h_jetN_nsv_sqrtsumH  [ireg][inj][i][jv] ->Fill( sqrt(jetsv_p4_sumH [jv]),      weight );
		    h_jetN_nsv_sumMass   [ireg][inj][i][jv] ->Fill( jetsv_p4_sumM      [jv],       weight );
		    h_jetN_nsv_sumMass_s [ireg][inj][i][jv] ->Fill( jetsv_p4_sumM      [jv],       weight );
		    h_jetN_nsv_ntrk      [ireg][inj][i][jv] ->Fill( jetsv_p4_ntrk      [jv],       weight );
		    h_jetN_nsv_njtrk     [ireg][inj][i][jv] ->Fill( jetsv_p4_njtrk     [jv],       weight );
		  }
		}
	      } // end if n jet svs 
	    } // end if doHists

	    // sum p4 for all matched secondary vertices in all jets in event
	    jetSecVerts_n        [ij][jv] += n_jetsv        [jv];
	    jetSecVerts_p4_sum   [ij][jv] += jetsv_p4_sum   [jv];
	    jetSecVerts_p4_sumPt [ij][jv] += jetsv_p4_sumPt [jv];
	    jetSecVerts_p4_sumM  [ij][jv] += jetsv_p4_sumM  [jv];
	    // sum p4 for all matched secondary vertices in min/max dijets
	    if ( m_histoInfoSwitch->m_dijets ) {
	      int maxix1 = p4_dijet_max_ix[ij].first; int maxix2 = p4_dijet_max_ix[ij].second;
	      int minix1 = p4_dijet_min_ix[ij].first; int minix2 = p4_dijet_min_ix[ij].second;
	      if ( m_jet_index ->at(i) == maxix1   || m_jet_index ->at(i) == maxix2   ) {
		dijetSecVerts_p4_max         [ij][jv] += jetsv_p4_sum   [jv];
		dijetSecVerts_p4_max_sumPt   [ij][jv] += jetsv_p4_sumPt [jv];
		dijetSecVerts_p4_max_sumM    [ij][jv] += jetsv_p4_sumM  [jv];
		dijetSecVerts_p4_max_n       [ij][jv] += n_jetsv        [jv];
	      }
	      if ( m_jet_index ->at(i) == minix1   || m_jet_index ->at(i) == minix2   ) {
		dijetSecVerts_p4_min         [ij][jv] += jetsv_p4_sum   [jv];
		dijetSecVerts_p4_min_sumPt   [ij][jv] += jetsv_p4_sumPt [jv];
		dijetSecVerts_p4_min_sumM    [ij][jv] += jetsv_p4_sumM  [jv];
		dijetSecVerts_p4_min_n       [ij][jv] += n_jetsv        [jv];
	      }
	      int maxptix1 = p4_dijet_maxpt_ix[ij].first; int maxptix2 = p4_dijet_maxpt_ix[ij].second;
	      int minptix1 = p4_dijet_minpt_ix[ij].first; int minptix2 = p4_dijet_minpt_ix[ij].second;
	      if ( m_jet_index ->at(i) == maxptix1 || m_jet_index ->at(i) == maxptix2 ) {
		dijetSecVerts_p4_maxpt       [ij][jv] += jetsv_p4_sum   [jv];
		dijetSecVerts_p4_maxpt_sumPt [ij][jv] += jetsv_p4_sumPt [jv];
		dijetSecVerts_p4_maxpt_sumM  [ij][jv] += jetsv_p4_sumM  [jv];
		dijetSecVerts_p4_maxpt_n     [ij][jv] += n_jetsv        [jv];
	      }
	      if ( m_jet_index ->at(i) == minptix1 || m_jet_index ->at(i) == minptix2 ) {
		dijetSecVerts_p4_minpt       [ij][jv] += jetsv_p4_sum   [jv];
		dijetSecVerts_p4_minpt_sumPt [ij][jv] += jetsv_p4_sumPt [jv];
		dijetSecVerts_p4_minpt_sumM  [ij][jv] += jetsv_p4_sumM  [jv];
		dijetSecVerts_p4_minpt_n     [ij][jv] += n_jetsv        [jv];
	      }
	    } 
	  } // end loop over jet vertex types
	
	} // end loop over jet types

	// do jet cutflow
	if ( m_histoInfoSwitch->m_cutflow || m_histoInfoSwitch->m_abcdcutOnly ) {
	  // --> test cuts
	  if ( m_nType1Js ) {
	    std::vector<int> jet_testCut;
	    getJetTypes( i, jet_testCut, base_dv, false, false, false );
	    std::vector<std::vector<int>>            jetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>        leadJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>        svP4JetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>    leadSvP4JetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>        svPtJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>    leadSvPtJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>        svHtJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>    leadSvHtJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>         svHJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>     leadSvHJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>      svNtrkJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>  leadSvNtrkJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>     svNjtrkJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>> leadSvNjtrkJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>       svTrkJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>   leadSvTrkJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>         svNJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    std::vector<std::vector<int>>     leadSvNJetTestCut
	      ( m_nTypeJSVs, std::vector<int> ( jet_testCut.size() / m_nType1Js, 0 ) );
	    unsigned ncjt     = ( m_nType1Js - m_nType1SVJs ) / m_LJix;
	    unsigned ncjv     = m_nType1SVJs / m_nTypeJSVs    / m_LJix;
	    unsigned ncjsvp4  = m_svP4J_ix    / m_LJix + ncjt;
	    unsigned ncjsvpt  = m_svPtJ_ix    / m_LJix + ncjt;
	    unsigned ncjsvht  = m_svHtJ_ix    / m_LJix + ncjt;
	    unsigned ncjsvh   = m_svHJ_ix     / m_LJix + ncjt;
	    unsigned ncjsvnt  = m_svNtrkJ_ix  / m_LJix + ncjt;
	    unsigned ncjsvnjt = m_svNjtrkJ_ix / m_LJix + ncjt;
	    unsigned ncjsvt   = m_svTrkJ_ix   / m_LJix + ncjt;
	    unsigned ncjsvn   = m_svNJ_ix     / m_LJix + ncjt;
	    for ( unsigned ijsv = 0; ijsv != m_nTypeJSVs; ++ijsv ) {
	      unsigned ibin         = 0;
	      unsigned ibin_svp4    = 0;
	      unsigned ibin_svpt    = 0;
	      unsigned ibin_svht    = 0;
	      unsigned ibin_svh     = 0;
	      unsigned ibin_svntrk  = 0;
	      unsigned ibin_svnjtrk = 0;
	      unsigned ibin_svtrk   = 0;
	      unsigned ibin_svn     = 0;
	      for ( size_t ijc = 0; ijc != jet_testCut.size() / m_LJix; ++ijc ) {
		unsigned imodjc          = ijc          % ( m_nType1Js / m_LJix     );
		unsigned imodbin         = ibin         % ( ncjt + ncjv             );
		unsigned imodbin_svp4    = ibin_svp4    % ( ncjt + m_nJSVpt .size() );
		unsigned imodbin_svpt    = ibin_svpt    % ( ncjt + m_nJSVpt .size() );
		unsigned imodbin_svht    = ibin_svht    % ( ncjt + m_nJSVpt .size() );
	        unsigned imodbin_svh     = ibin_svh     % ( ncjt + m_nJSVh  .size() );
		unsigned imodbin_svntrk  = ibin_svntrk  % ( ncjt + m_nJSVtrk.size() );
		unsigned imodbin_svnjtrk = ibin_svnjtrk % ( ncjt + m_nJSVtrk.size() );
		unsigned imodbin_svtrk   = ibin_svtrk   % ( ncjt + m_nJSVtrk.size() );
		unsigned imodbin_svn     = ibin_svn     % ( ncjt + m_nJSV   .size() );
		// all test cuts
		if ( ( imodjc < ncjt ) ||
		     ( imodjc >= ncjsvp4+m_nJSVpt  .size()*ijsv && imodjc < ncjsvp4+m_nJSVpt  .size()*(ijsv+1) ) ||
		     ( imodjc >= ncjsvpt+m_nJSVpt  .size()*ijsv && imodjc < ncjsvpt+m_nJSVpt  .size()*(ijsv+1) ) ||
		     ( imodjc >= ncjsvht+m_nJSVpt  .size()*ijsv && imodjc < ncjsvht+m_nJSVpt  .size()*(ijsv+1) ) ||
		     ( imodjc >= ncjsvh+m_nJSVh    .size()*ijsv && imodjc < ncjsvh+m_nJSVh    .size()*(ijsv+1) ) ||
		     ( imodjc >= ncjsvnt+m_nJSVtrk .size()*ijsv && imodjc < ncjsvnt+m_nJSVtrk .size()*(ijsv+1) ) ||
		     ( imodjc >= ncjsvnjt+m_nJSVtrk.size()*ijsv && imodjc < ncjsvnjt+m_nJSVtrk.size()*(ijsv+1) ) ||
		     ( imodjc >= ncjsvt+m_nJSVtrk  .size()*ijsv && imodjc < ncjsvt+m_nJSVtrk  .size()*(ijsv+1) ) ||
		     ( imodjc >= ncjsvn+m_nJSV     .size()*ijsv && imodjc < ncjsvn+m_nJSV     .size()*(ijsv+1) ) ) {
		  jetTestCut     [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix  ];
		  leadJetTestCut [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix+1];
		  h_evt_testCutflow_jet     [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		    ->Fill( imodbin, (     jetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin + 1 ) ) * weight );
		  h_evt_testCutflow_leadJet [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		    ->Fill( imodbin, ( leadJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin + 1 ) ) * weight );
		  ++ibin;
		}
		// nsv-pt
		if ( ( imodjc < ncjt ) ||
		     ( imodjc >= ncjsvp4+m_nJSVpt.size()*ijsv && imodjc < ncjsvp4+m_nJSVpt.size()*(ijsv+1) ) ) {
		  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvP4Jets ) {
		    svP4JetTestCut     [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix  ];
		    leadSvP4JetTestCut [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix+1];
		    h_evt_testCutflow_svP4Jet     [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svp4, (     svP4JetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svp4 + 1 ) ) * weight );
		    h_evt_testCutflow_leadSvP4Jet [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svp4, ( leadSvP4JetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svp4 + 1 ) ) * weight );
		  }
		  ++ibin_svp4;
		}
		// nsv-sum-pt
		if ( ( imodjc < ncjt ) ||
		     ( imodjc >= ncjsvpt+m_nJSVpt.size()*ijsv && imodjc < ncjsvpt+m_nJSVpt.size()*(ijsv+1) ) ) {
		  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvPtJets ) {
		    svPtJetTestCut     [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix  ];
		    leadSvPtJetTestCut [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix+1];
		    h_evt_testCutflow_svPtJet     [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svpt, (     svPtJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svpt + 1 ) ) * weight );
		    h_evt_testCutflow_leadSvPtJet [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svpt, ( leadSvPtJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svpt + 1 ) ) * weight );
		  }
		  ++ibin_svpt;
		}
		// nsv-sum-Ht
		if ( ( imodjc < ncjt ) ||
		     ( imodjc >= ncjsvht+m_nJSVpt.size()*ijsv && imodjc < ncjsvht+m_nJSVpt.size()*(ijsv+1) ) ) {
		  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHtJets ) {
		    svHtJetTestCut     [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix  ];
		    leadSvHtJetTestCut [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix+1];
		    h_evt_testCutflow_svHtJet     [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svht, (     svHtJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svht + 1 ) ) * weight );
		    h_evt_testCutflow_leadSvHtJet [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svht, ( leadSvHtJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svht + 1 ) ) * weight );
		  }
		  ++ibin_svht;
		}
		// nsv-sum-H
		if ( ( imodjc < ncjt ) ||
		     ( imodjc >= ncjsvh+m_nJSVh.size()*ijsv && imodjc < ncjsvh+m_nJSVh.size()*(ijsv+1) ) ) {
		  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHJets ) {
		    svHJetTestCut     [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix  ];
		    leadSvHJetTestCut [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix+1];
		    h_evt_testCutflow_svHJet     [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svh, (     svHJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svh + 1 ) ) * weight );
		    h_evt_testCutflow_leadSvHJet [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svh, ( leadSvHJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svh + 1 ) ) * weight );
		  }
		  ++ibin_svh;
		}
		// nsv-ntrk
		if ( ( imodjc < ncjt ) ||
		     ( imodjc >= ncjsvnt+m_nJSVtrk.size()*ijsv && imodjc < ncjsvnt+m_nJSVtrk.size()*(ijsv+1) ) ) {
		  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNtrkJets  ) {
		    svNtrkJetTestCut     [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix  ];
		    leadSvNtrkJetTestCut [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix+1];
		    h_evt_testCutflow_svNtrkJet     [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svntrk, (     svNtrkJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svntrk + 1 ) ) * weight );
		    h_evt_testCutflow_leadSvNtrkJet [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svntrk, ( leadSvNtrkJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svntrk + 1 ) ) * weight );
		  }
		  ++ibin_svntrk;
		}
		// nsv-njtrk
		if ( ( imodjc < ncjt ) ||
		     ( imodjc >= ncjsvnjt+m_nJSVtrk.size()*ijsv && imodjc < ncjsvnjt+m_nJSVtrk.size()*(ijsv+1) ) ) {
		  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNjtrkJets ) {
		    svNjtrkJetTestCut     [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix  ];
		    leadSvNjtrkJetTestCut [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix+1];
		    h_evt_testCutflow_svNjtrkJet     [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svnjtrk, (     svNjtrkJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svnjtrk + 1 ) ) * weight );
		    h_evt_testCutflow_leadSvNjtrkJet [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svnjtrk, ( leadSvNjtrkJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svnjtrk + 1 ) ) * weight );
		  }
		  ++ibin_svnjtrk;
		}
		// nsv-trk
		if ( ( imodjc < ncjt ) ||
		     ( imodjc >= ncjsvt+m_nJSVtrk.size()*ijsv && imodjc < ncjsvt+m_nJSVtrk.size()*(ijsv+1) ) ) {
		  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvTrkJets ) {
		    svTrkJetTestCut     [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix  ];
		    leadSvTrkJetTestCut [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix+1];
		    h_evt_testCutflow_svTrkJet     [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svtrk, (     svTrkJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svtrk + 1 ) ) * weight );
		    h_evt_testCutflow_leadSvTrkJet [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svtrk, ( leadSvTrkJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svtrk + 1 ) ) * weight );
		  }
		  ++ibin_svtrk;
		}
		// nsv
		if ( ( imodjc < ncjt ) ||
		     ( imodjc >= ncjsvn+m_nJSV.size()*ijsv && imodjc < ncjsvn+m_nJSV.size()*(ijsv+1) ) ) {
		  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvJets ) {
		    svNJetTestCut     [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix  ];
		    leadSvNJetTestCut [ijsv][ijc*m_LJix/m_nType1Js] += jet_testCut[ijc*m_LJix+1];
		    h_evt_testCutflow_svNJet     [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svn, (     svNJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svn + 1 ) ) * weight );
		    h_evt_testCutflow_leadSvNJet [ireg][ijc*m_LJix/m_nType1Js][ijsv]
		      ->Fill( imodbin_svn, ( leadSvNJetTestCut[ijsv][ijc*m_LJix/m_nType1Js] / ( imodbin_svn + 1 ) ) * weight );
		  }
		  ++ibin_svn;
		}
	      } // end loop over test jet cuts
	    } // end loop over JSVs
	  } // end if m_nType1Js
	
	  // --> "emerging" cuts
	  std::vector<int> jet_cut;
	  getJetTypes( i, jet_cut, base_dv, false, false, true );
	  unsigned n_ejcuts = jet_cut.size() / h_evt_cutflow_emergingJet [ireg].size();
	  unsigned nbinej   = n_ejcuts / m_LJix / m_nTypeJSVs;
	  std::vector<std::vector<int>> jetCut     ( m_nTypeJSVs, std::vector<int> ( jet_cut.size() / n_ejcuts, 0 ) );
	  std::vector<std::vector<int>> leadJetCut ( m_nTypeJSVs, std::vector<int> ( jet_cut.size() / n_ejcuts, 0 ) );
	  for ( unsigned ijsv = 0; ijsv != m_nTypeJSVs; ++ijsv ) {
	    unsigned  ibin = 0;
	    for ( size_t ijc = 0; ijc != jet_cut.size() / m_LJix; ++ijc ) {
	      unsigned imodjc  = ijc % ( n_ejcuts / m_LJix );
	      unsigned imodbin = ibin % nbinej;
	      if ( imodjc >= nbinej*ijsv && imodjc < nbinej*(ijsv+1) ) {
		jetCut     [ijsv][ijc*m_LJix/n_ejcuts] += jet_cut[ijc*m_LJix  ];
		leadJetCut [ijsv][ijc*m_LJix/n_ejcuts] += jet_cut[ijc*m_LJix+1];
		h_evt_cutflow_emergingJet     [ireg][ijc*m_LJix/n_ejcuts][ijsv]
		  ->Fill( imodbin, (     jetCut[ijsv][ijc*m_LJix/n_ejcuts] / ( imodbin + 1 ) ) * weight );
		h_evt_cutflow_leadEmergingJet [ireg][ijc*m_LJix/n_ejcuts][ijsv]
		  ->Fill( imodbin, ( leadJetCut[ijsv][ijc*m_LJix/n_ejcuts] / ( imodbin + 1 ) ) * weight );
		++ibin;
	      }	
	    }
	  }
	
	} // end if cutflow info switch
		  
      } // end loop over jets

      // fill jet count, min/max/avg-dijet, njet histograms
      for ( size_t ij = 0; ij != n_jet.size(); ++ij ) {
	h_jet_n [ireg][ij] ->Fill( n_jet[ij], weight );

	if ( m_histoInfoSwitch->m_dijets ) {
	  int sum_ct = p4_dijet_sum_count [ij];
	  if ( doHists && !m_histoInfoSwitch->m_abcdcutOnly )
	    h_dijet_n [ireg][ij] ->Fill( sum_ct, weight );

	  if ( sum_ct ) {
	    h_dijet_avgp4_pt    [ireg][ij] ->Fill( p4_dijet_sum_pt   [ij]/sum_ct, weight );
	    h_dijet_avgp4_eta   [ireg][ij] ->Fill( p4_dijet_sum_eta  [ij]/sum_ct, weight );
	    h_dijet_avgp4_phi   [ireg][ij] ->Fill( p4_dijet_sum_phi  [ij]/sum_ct, weight );
	    h_dijet_avgp4_m     [ireg][ij] ->Fill( p4_dijet_sum_m    [ij]/sum_ct, weight );
	    h_dijet_avgp4_sumPt [ireg][ij] ->Fill( p4_dijet_sum_sumpt[ij]/sum_ct, weight );
	    h_dijet_avgp4_sumM  [ireg][ij] ->Fill( p4_dijet_sum_summ [ij]/sum_ct, weight );
	    h_dijet_avgp4_dR    [ireg][ij] ->Fill( p4_dijet_sum_dr   [ij]/sum_ct, weight );
	    
	    int   max_ix1   = p4_dijet_max_ix[ij].first;
	    int   max_ix2   = p4_dijet_max_ix[ij].second;
	    float max_sumpt = 0;
	    float max_summ  = 0;
	    float max_dr    = 0;
	    if ( max_ix1 != -1 && max_ix2 != -1 ) {
	      max_sumpt = m_jet_pt->at(max_ix1) + m_jet_pt->at(max_ix2);
	      max_summ  = m_jet_M ->at(max_ix1) + m_jet_M ->at(max_ix2);
	      max_dr    = EJsHelper::deltaR( m_jet_eta->at(max_ix1), m_jet_eta->at(max_ix2), m_jet_phi->at(max_ix1), m_jet_phi->at(max_ix2) );
	    }
	    h_dijet_maxp4_pt    [ireg][ij] ->Fill( p4_dijet_max[ij].Pt(),  weight );
	    h_dijet_maxp4_eta   [ireg][ij] ->Fill( p4_dijet_max[ij].Eta(), weight );
	    h_dijet_maxp4_phi   [ireg][ij] ->Fill( p4_dijet_max[ij].Phi(), weight );
	    h_dijet_maxp4_m     [ireg][ij] ->Fill( p4_dijet_max[ij].M(),   weight );
	    h_dijet_maxp4_sumPt [ireg][ij] ->Fill( max_sumpt,              weight );
	    h_dijet_maxp4_sumM  [ireg][ij] ->Fill( max_summ,               weight );
	    h_dijet_maxp4_dR    [ireg][ij] ->Fill( max_dr,                 weight );
	    for ( unsigned ijtrk = 0; ijtrk != m_nTypeTrks; ++ijtrk ) {
	      h_dijet_maxp4_ntrk         [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max_n       [ij][ijtrk],       weight );
	      if ( m_histoInfoSwitch->m_dijetTrks  && dijetTracks_p4_max_n   [ij][ijtrk]  ) {
		h_dijet_maxp4_ntrk_pt    [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max         [ij][ijtrk].Pt(),  weight );
		h_dijet_maxp4_ntrk_eta   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max         [ij][ijtrk].Eta(), weight );
		h_dijet_maxp4_ntrk_phi   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max         [ij][ijtrk].Phi(), weight );
		h_dijet_maxp4_ntrk_m     [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max         [ij][ijtrk].M(),   weight );
		h_dijet_maxp4_ntrk_sumPt [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max_sumPt   [ij][ijtrk],       weight );
		h_dijet_maxp4_ntrk_sumM  [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max_sumM    [ij][ijtrk],       weight );
	      }
	    }
	    for ( unsigned ijsv = 0;  ijsv != m_nTypeJDVs;  ++ijsv ) {
	      h_dijet_maxp4_nsv          [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max_n     [ij][ijsv],        weight );
	      if ( m_histoInfoSwitch->m_dijetVerts && dijetSecVerts_p4_max_n [ij][ijsv] ) {
		h_dijet_maxp4_nsv_pt     [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max       [ij][ijsv].Pt(),   weight );
		h_dijet_maxp4_nsv_eta    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max       [ij][ijsv].Eta(),  weight );
		h_dijet_maxp4_nsv_phi    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max       [ij][ijsv].Phi(),  weight );
		h_dijet_maxp4_nsv_m      [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max       [ij][ijsv].M(),    weight );
		h_dijet_maxp4_nsv_sumPt  [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max_sumPt [ij][ijsv],        weight );
		h_dijet_maxp4_nsv_sumM   [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max_sumM  [ij][ijsv],        weight );
	      }
	    }
	    
	    int   min_ix1   = p4_dijet_min_ix[ij].first;
	    int   min_ix2   = p4_dijet_min_ix[ij].second;
	    float min_sumpt = 0;
	    float min_summ  = 0;
	    float min_dr    = 0;
	    if ( min_ix1 != -1 && min_ix2 != -1 ) {
	      min_sumpt = m_jet_pt->at(min_ix1) + m_jet_pt->at(min_ix2);
	      min_summ  = m_jet_M ->at(min_ix1) + m_jet_M ->at(min_ix2);
	      min_dr    = EJsHelper::deltaR( m_jet_eta->at(min_ix1), m_jet_eta->at(min_ix2), m_jet_phi->at(min_ix1), m_jet_phi->at(min_ix2) );
	    }
	    h_dijet_minp4_pt    [ireg][ij] ->Fill( p4_dijet_min[ij].Pt(),  weight );
	    h_dijet_minp4_eta   [ireg][ij] ->Fill( p4_dijet_min[ij].Eta(), weight );
	    h_dijet_minp4_phi   [ireg][ij] ->Fill( p4_dijet_min[ij].Phi(), weight );
	    h_dijet_minp4_m     [ireg][ij] ->Fill( p4_dijet_min[ij].M(),   weight );
	    h_dijet_minp4_sumPt [ireg][ij] ->Fill( min_sumpt,              weight );
	    h_dijet_minp4_sumM  [ireg][ij] ->Fill( min_summ,               weight );
	    h_dijet_minp4_dR    [ireg][ij] ->Fill( min_dr,                 weight );
	    for ( unsigned ijtrk = 0; ijtrk != m_nTypeTrks; ++ijtrk ) {
	      h_dijet_minp4_ntrk         [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min_n       [ij][ijtrk],       weight );
	      if ( m_histoInfoSwitch->m_dijetTrks  && dijetTracks_p4_min_n   [ij][ijtrk] ) {
		h_dijet_minp4_ntrk_pt    [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min         [ij][ijtrk].Pt(),  weight );
		h_dijet_minp4_ntrk_eta   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min         [ij][ijtrk].Eta(), weight );
		h_dijet_minp4_ntrk_phi   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min         [ij][ijtrk].Phi(), weight );
		h_dijet_minp4_ntrk_m     [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min         [ij][ijtrk].M(),   weight );
		h_dijet_minp4_ntrk_sumPt [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min_sumPt   [ij][ijtrk],       weight );
		h_dijet_minp4_ntrk_sumM  [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min_sumM    [ij][ijtrk],       weight );
	      }
	    }
	    for ( unsigned ijsv = 0;  ijsv != m_nTypeJDVs;  ++ijsv ) {
	      h_dijet_minp4_nsv          [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min_n     [ij][ijsv],        weight );
	      if ( m_histoInfoSwitch->m_dijetVerts && dijetSecVerts_p4_min_n [ij][ijsv] ) {
		h_dijet_minp4_nsv_pt     [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min       [ij][ijsv].Pt(),   weight );
		h_dijet_minp4_nsv_eta    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min       [ij][ijsv].Eta(),  weight );
		h_dijet_minp4_nsv_phi    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min       [ij][ijsv].Phi(),  weight );
		h_dijet_minp4_nsv_m      [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min       [ij][ijsv].M(),    weight );
		h_dijet_minp4_nsv_sumPt  [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min_sumPt [ij][ijsv],        weight );
		h_dijet_minp4_nsv_sumM   [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min_sumM  [ij][ijsv],        weight );
	      }
	    }

	    int   maxpt_ix1   = p4_dijet_maxpt_ix[ij].first;
	    int   maxpt_ix2   = p4_dijet_maxpt_ix[ij].second;
	    float maxpt_sumpt = 0;
	    float maxpt_summ  = 0;
	    float maxpt_dr    = 0;
	    if ( maxpt_ix1 != -1 && maxpt_ix2 != -1 ) {
	      maxpt_sumpt = m_jet_pt->at(maxpt_ix1) + m_jet_pt->at(maxpt_ix2);
	      maxpt_summ  = m_jet_M ->at(maxpt_ix1) + m_jet_M ->at(maxpt_ix2);
	      maxpt_dr    = EJsHelper::deltaR( m_jet_eta->at(maxpt_ix1), m_jet_eta->at(maxpt_ix2),
					       m_jet_phi->at(maxpt_ix1), m_jet_phi->at(maxpt_ix2) );
	    }
	    h_dijet_maxpt_pt    [ireg][ij] ->Fill( p4_dijet_maxpt[ij].Pt(),  weight );
	    h_dijet_maxpt_eta   [ireg][ij] ->Fill( p4_dijet_maxpt[ij].Eta(), weight );
	    h_dijet_maxpt_phi   [ireg][ij] ->Fill( p4_dijet_maxpt[ij].Phi(), weight );
	    h_dijet_maxpt_m     [ireg][ij] ->Fill( p4_dijet_maxpt[ij].M(),   weight );
	    h_dijet_maxpt_sumPt [ireg][ij] ->Fill( maxpt_sumpt,              weight );
	    h_dijet_maxpt_sumM  [ireg][ij] ->Fill( maxpt_summ,               weight );
	    h_dijet_maxpt_dR    [ireg][ij] ->Fill( maxpt_dr,                 weight );
	    for ( unsigned ijtrk = 0; ijtrk != m_nTypeTrks; ++ijtrk ) {
	      h_dijet_maxpt_ntrk         [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt_n       [ij][ijtrk],       weight );
	      if ( m_histoInfoSwitch->m_dijetTrks  && dijetTracks_p4_maxpt_n   [ij][ijtrk] ) {
		h_dijet_maxpt_ntrk_pt    [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt         [ij][ijtrk].Pt(),  weight );
		h_dijet_maxpt_ntrk_eta   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt         [ij][ijtrk].Eta(), weight );
		h_dijet_maxpt_ntrk_phi   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt         [ij][ijtrk].Phi(), weight );
		h_dijet_maxpt_ntrk_m     [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt         [ij][ijtrk].M(),   weight );
		h_dijet_maxpt_ntrk_sumPt [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt_sumPt   [ij][ijtrk],       weight );
		h_dijet_maxpt_ntrk_sumM  [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt_sumM    [ij][ijtrk],       weight );
	      }
	    }
	    for ( unsigned ijsv = 0;  ijsv != m_nTypeJDVs;  ++ijsv  ) {
	      h_dijet_maxpt_nsv          [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt_n     [ij][ijsv],        weight );
	      if ( m_histoInfoSwitch->m_dijetVerts && dijetSecVerts_p4_maxpt_n [ij][ijsv] ) {
		h_dijet_maxpt_nsv_pt     [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt       [ij][ijsv].Pt(),   weight );
		h_dijet_maxpt_nsv_eta    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt       [ij][ijsv].Eta(),  weight );
		h_dijet_maxpt_nsv_phi    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt       [ij][ijsv].Phi(),  weight );
		h_dijet_maxpt_nsv_m      [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt       [ij][ijsv].M(),    weight );
		h_dijet_maxpt_nsv_sumPt  [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt_sumPt [ij][ijsv],        weight );
		h_dijet_maxpt_nsv_sumM   [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt_sumM  [ij][ijsv],        weight );
	      }
	    }

	    int   minpt_ix1   = p4_dijet_minpt_ix[ij].first;
	    int   minpt_ix2   = p4_dijet_minpt_ix[ij].second;
	    float minpt_sumpt = 0;
	    float minpt_summ  = 0;
	    float minpt_dr    = 0;
	    if ( minpt_ix1 != -1 && minpt_ix2 != -1 ) {
	      minpt_sumpt = m_jet_pt->at(minpt_ix1) + m_jet_pt->at(minpt_ix2);
	      minpt_summ  = m_jet_M ->at(minpt_ix1) + m_jet_M ->at(minpt_ix2);
	      minpt_dr    = EJsHelper::deltaR( m_jet_eta->at(minpt_ix1), m_jet_eta->at(minpt_ix2),
					       m_jet_phi->at(minpt_ix1), m_jet_phi->at(minpt_ix2) );
	    }
	    h_dijet_minpt_pt    [ireg][ij] ->Fill( p4_dijet_minpt[ij].Pt(),  weight );
	    h_dijet_minpt_eta   [ireg][ij] ->Fill( p4_dijet_minpt[ij].Eta(), weight );
	    h_dijet_minpt_phi   [ireg][ij] ->Fill( p4_dijet_minpt[ij].Phi(), weight );
	    h_dijet_minpt_m     [ireg][ij] ->Fill( p4_dijet_minpt[ij].M(),   weight );
	    h_dijet_minpt_sumPt [ireg][ij] ->Fill( minpt_sumpt,              weight );
	    h_dijet_minpt_sumM  [ireg][ij] ->Fill( minpt_summ,               weight );
	    h_dijet_minpt_dR    [ireg][ij] ->Fill( minpt_dr,                 weight );
	    for ( unsigned ijtrk = 0; ijtrk != m_nTypeTrks; ++ijtrk ) {
	      h_dijet_minpt_ntrk         [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt_n       [ij][ijtrk],       weight );
	      if ( m_histoInfoSwitch->m_dijetTrks  && dijetTracks_p4_minpt_n   [ij][ijtrk] ) {
		h_dijet_minpt_ntrk_pt    [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt         [ij][ijtrk].Pt(),  weight );
		h_dijet_minpt_ntrk_eta   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt         [ij][ijtrk].Eta(), weight );
		h_dijet_minpt_ntrk_phi   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt         [ij][ijtrk].Phi(), weight );
		h_dijet_minpt_ntrk_m     [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt         [ij][ijtrk].M(),   weight );
		h_dijet_minpt_ntrk_sumPt [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt_sumPt   [ij][ijtrk],       weight );
		h_dijet_minpt_ntrk_sumM  [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt_sumM    [ij][ijtrk],       weight );
	      }
	    }
	    for ( unsigned ijsv = 0;  ijsv != m_nTypeJDVs;  ++ijsv  ) {
	      h_dijet_minpt_nsv          [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt_n     [ij][ijsv],        weight );
	      if ( m_histoInfoSwitch->m_dijetVerts && dijetSecVerts_p4_minpt_n [ij][ijsv] ) {
		h_dijet_minpt_nsv_pt     [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt       [ij][ijsv].Pt(),   weight );
		h_dijet_minpt_nsv_eta    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt       [ij][ijsv].Eta(),  weight );
		h_dijet_minpt_nsv_phi    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt       [ij][ijsv].Phi(),  weight );
		h_dijet_minpt_nsv_m      [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt       [ij][ijsv].M(),    weight );
		h_dijet_minpt_nsv_sumPt  [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt_sumPt [ij][ijsv],        weight );
		h_dijet_minpt_nsv_sumM   [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt_sumM  [ij][ijsv],        weight );
	      }
	    }
	  } // end if sum_ct
	} // end if dijets

	if ( m_histoInfoSwitch->m_njets && n_jet[ij] ) {
	  h_njet_pt    [ireg][ij] ->Fill( jet_p4_sum  [ij].Pt(),  weight );
	  h_njet_eta   [ireg][ij] ->Fill( jet_p4_sum  [ij].Eta(), weight );
	  h_njet_phi   [ireg][ij] ->Fill( jet_p4_sum  [ij].Phi(), weight );
	  h_njet_m     [ireg][ij] ->Fill( jet_p4_sum  [ij].M(),   weight );
	  h_njet_sumPt [ireg][ij] ->Fill( jet_p4_sumPt[ij],       weight );
	  h_njet_sumM  [ireg][ij] ->Fill( jet_p4_sumM [ij],       weight );
	  for ( unsigned ijtrk = 0; ijtrk != m_nTypeTrks; ++ijtrk ) {
	    h_njet_ntrk         [ireg][ij][ijtrk] ->Fill( jetTracks_n          [ij][ijtrk],       weight );
	    if ( m_histoInfoSwitch->m_njetTrks  && jetTracks_n [ij][ijtrk] ) {
	      h_njet_ntrk_pt    [ireg][ij][ijtrk] ->Fill( jetTracks_p4_sum     [ij][ijtrk].Pt(),  weight );
	      h_njet_ntrk_eta   [ireg][ij][ijtrk] ->Fill( jetTracks_p4_sum     [ij][ijtrk].Eta(), weight );
	      h_njet_ntrk_phi   [ireg][ij][ijtrk] ->Fill( jetTracks_p4_sum     [ij][ijtrk].Phi(), weight );
	      h_njet_ntrk_m     [ireg][ij][ijtrk] ->Fill( jetTracks_p4_sum     [ij][ijtrk].M(),   weight );
	      h_njet_ntrk_sumPt [ireg][ij][ijtrk] ->Fill( jetTracks_p4_sumPt   [ij][ijtrk],       weight );
	      h_njet_ntrk_sumM  [ireg][ij][ijtrk] ->Fill( jetTracks_p4_sumM    [ij][ijtrk],       weight );
	    }
	  }
	  for ( unsigned ijsv = 0; ijsv != m_nTypeJDVs; ++ijsv ) {
	    h_njet_nsv          [ireg][ij][ijsv]  ->Fill( jetSecVerts_n        [ij][ijsv],        weight );
	    if ( m_histoInfoSwitch->m_njetVerts && jetSecVerts_n [ij][ijsv] ) {
	      h_njet_nsv_pt     [ireg][ij][ijsv]  ->Fill( jetSecVerts_p4_sum   [ij][ijsv] .Pt(),  weight );
	      h_njet_nsv_eta    [ireg][ij][ijsv]  ->Fill( jetSecVerts_p4_sum   [ij][ijsv] .Eta(), weight );
	      h_njet_nsv_phi    [ireg][ij][ijsv]  ->Fill( jetSecVerts_p4_sum   [ij][ijsv] .Phi(), weight );
	      h_njet_nsv_m      [ireg][ij][ijsv]  ->Fill( jetSecVerts_p4_sum   [ij][ijsv] .M(),   weight );
	      h_njet_nsv_sumPt  [ireg][ij][ijsv]  ->Fill( jetSecVerts_p4_sumPt [ij][ijsv],        weight );
	      h_njet_nsv_sumM   [ireg][ij][ijsv]  ->Fill( jetSecVerts_p4_sumM  [ij][ijsv],        weight );
	    }
	  }
	} // end if njets

	// NJet cutflow
	if ( m_histoInfoSwitch->m_cutflow || m_histoInfoSwitch->m_abcdcutOnly ) {
	  if ( ij >= m_nTypeBJs ) continue;
	  for ( int inj = 0; inj != m_nJets+1; ++inj )
	    if ( n_jet[ij] > inj-1 ) {
	      if ( ij % m_LJix == 0 )
		h_evt_cutflow_NJet     [ireg][ij/m_LJix] ->Fill( inj, weight );
	      else if ( ij % m_LJix == 1 )
		h_evt_cutflow_NLeadJet [ireg][ij/m_LJix] ->Fill( inj, weight );
	    }
	}
      
      } // end loop over jet types
    } // end if not truthOnly
    
    
    // N-leading jets
    double njht      = m_njetHt;
    double njht_vrsh = m_njetHt;
    if ( region.type == EJsHelper::VALIDATION || region.type == EJsHelper::JZ4W_SLICE_VALIDATION )
      njht_vrsh     *= m_vrshift_njetht;
    h_NJetHt        [ireg] ->Fill( njht,      weight );
    if ( m_histoInfoSwitch->m_vrshift )
      h_NJetHt_vrsh [ireg] ->Fill( njht_vrsh, weight );

    double njpt                = 0;
    double njeta               = 0;
    double njphi               = 0;
    double njm                 = 0;
    double njsumm              = 0;
    double mindiff             = AlgConsts::maxValue;
    double mindiff_invM        = 0;
    double mindiff_pt          = 0;
    double mindiff_ptdiff      = 0;
    double mindiff_eta         = 0;
    double mindiff_etadiff     = 0;
    double mindiff_phi         = 0;
    double mindiff_phidiff     = 0;
    double mindiff_sumpt       = 0;
    double mindiff_summ        = 0;
    double mindiff_dR          = 0;
    double mindiff_dRjj        = 0;
    double mindiffpt           = AlgConsts::maxValue;
    double mindiffpt_pt        = 0;
    double mindiffpt_eta       = 0;
    double mindiffpt_etadiff   = 0;
    double mindiffpt_phi       = 0;
    double mindiffpt_phidiff   = 0;
    double mindiffpt_invM      = 0;
    double mindiffpt_invMdiff  = 0;
    double mindiffpt_sumpt     = 0;
    double mindiffpt_summ      = 0;
    double mindiffpt_dR        = 0;
    double mindiffpt_dRjj      = 0;
    double maxdr               = 0;
    double maxdr_dRjj          = 0;
    double maxdr_pt            = 0;
    double maxdr_ptdiff        = 0;
    double maxdr_eta           = 0;
    double maxdr_etadiff       = 0;
    double maxdr_phi           = 0;
    double maxdr_phidiff       = 0;
    double maxdr_invM          = 0;
    double maxdr_invMdiff      = 0;
    double maxdr_sumpt         = 0;
    double maxdr_summ          = 0;
    double avgjj_pt            = 0;
    double avgjj_eta           = 0;
    double avgjj_phi           = 0;
    double avgjj_m             = 0;
    double avgjj_dR            = 0;
    double maxjj_pt            = 0;
    double maxjj_eta           = 0;
    double maxjj_phi           = 0;
    double maxjj_m             = 0;
    double maxjj_sumPt         = 0;
    double maxjj_sumM          = 0;
    double maxjj_dR            = 0;
    double minjj_pt            = 0;
    double minjj_eta           = 0;
    double minjj_phi           = 0;
    double minjj_m             = 0;
    double minjj_sumPt         = 0;
    double minjj_sumM          = 0;
    double minjj_dR            = 0;
    double maxptjj_pt          = 0;
    double maxptjj_eta         = 0;
    double maxptjj_phi         = 0;
    double maxptjj_m           = 0;
    double maxptjj_sumPt       = 0;
    double maxptjj_sumM        = 0;
    double maxptjj_dR          = 0;
    double minptjj_pt          = 0;
    double minptjj_eta         = 0;
    double minptjj_phi         = 0;
    double minptjj_m           = 0;
    double minptjj_sumPt       = 0;
    double minptjj_sumM        = 0;
    double minptjj_dR          = 0;
    double njpt_vrsh           = 0;
    double njsumm_vrsh         = 0;
    double mindiff_pt_vrsh     = 0;
    double mindiff_invM_vrsh   = 0;
    double mindiffpt_pt_vrsh   = 0;
    double mindiffpt_invM_vrsh = 0;
    double maxdr_pt_vrsh       = 0;
    double maxdr_invM_vrsh     = 0;
    double avgjj_pt_vrsh       = 0;
    double avgjj_m_vrsh        = 0;
    double maxjj_pt_vrsh       = 0;
    double maxjj_m_vrsh        = 0;
    double maxjj_sumPt_vrsh    = 0;
    double maxjj_sumM_vrsh     = 0;
    double minjj_pt_vrsh       = 0;
    double minjj_m_vrsh        = 0;
    double minjj_sumPt_vrsh    = 0;
    double minjj_sumM_vrsh     = 0;
    double maxptjj_pt_vrsh     = 0;
    double maxptjj_m_vrsh      = 0;
    double maxptjj_sumPt_vrsh  = 0;
    double maxptjj_sumM_vrsh   = 0;
    double minptjj_pt_vrsh     = 0;
    double minptjj_m_vrsh      = 0;
    double minptjj_sumPt_vrsh  = 0;
    double minptjj_sumM_vrsh   = 0;
    if ( !m_histoInfoSwitch->m_truthOnly ) {
      // N-leading jets
      njpt        = jet_p4_sum  [m_LJix-1].Pt();
      njeta       = jet_p4_sum  [m_LJix-1].Eta();
      njphi       = jet_p4_sum  [m_LJix-1].Phi();
      njm         = jet_p4_sum  [m_LJix-1].M();
      njsumm      = jet_p4_sumM [m_LJix-1];
      njpt_vrsh   = njpt;
      njsumm_vrsh = njsumm;
      if ( region.type == EJsHelper::VALIDATION || region.type == EJsHelper::JZ4W_SLICE_VALIDATION ) {
	njpt_vrsh   *= m_vrshift_njetpt;
	njsumm_vrsh *= m_vrshift_njetsm;
      }
      
      h_NJetPt          [ireg] ->Fill( njpt,        weight );
      h_NJetEta         [ireg] ->Fill( njeta,       weight );
      h_NJetPhi         [ireg] ->Fill( njphi,       weight );
      h_NJetM           [ireg] ->Fill( njm,         weight );
      h_NJetSumM        [ireg] ->Fill( njsumm,      weight );
      if ( m_histoInfoSwitch->m_vrshift ) {
	h_NJetPt_vrsh   [ireg] ->Fill( njpt_vrsh,   weight );
	h_NJetSumM_vrsh [ireg] ->Fill( njsumm_vrsh, weight );
      }	
      
      // find average of dijet pairs of N-leading jets
      // --> note: this method only works for specific case of m_nJets <= 4
      std::vector<std::pair<int,int>> dijet_indices;
      for ( int i = 0; i != m_jet_n; ++i ) {
	for ( int j = i+1; j != m_jet_n; ++j ) {
	  if ( i >= m_nJets || j >= m_nJets ) continue;
	  dijet_indices.push_back( std::make_pair( i, j ) );
	}
      }
      // --> special handling for 2 or 3 jets
      if ( m_jet_n < m_nJets ) dijet_indices.push_back( dijet_indices[dijet_indices.size()-1] );
      // loop over dijet pairs
      for ( size_t i = 0; i != dijet_indices.size(); ++i ) {
	for ( size_t j = i+1; j != dijet_indices.size(); ++j ) {
	  if ( m_jet_n >= m_nJets && ( dijet_indices[i].first  == dijet_indices[j].first  ||
				       dijet_indices[i].first  == dijet_indices[j].second ||
				       dijet_indices[i].second == dijet_indices[j].first  ||
				       dijet_indices[i].second == dijet_indices[j].second ) ) continue;
	  else if ( m_jet_n == 3 && j != i+1 ) continue;
	  TLorentzVector p4_j1, p4_j2, p4_j3, p4_j4;
	  int ix_j1 = dijet_indices[i].first;
	  int ix_j2 = dijet_indices[i].second;
	  int ix_j3 = dijet_indices[j].first;
	  int ix_j4 = dijet_indices[j].second;
	  // call third jet second dijet in case of 3 jets
	  if ( m_jet_n == 3 ) {
	    if      ( ix_j1 == 0 && ix_j2 == 1 ) ix_j3 = 2;
	    else if ( ix_j1 == 0 && ix_j2 == 2 ) ix_j3 = 1;
	    else if ( ix_j1 == 1 && ix_j2 == 2 ) ix_j3 = 0;
	    ix_j4 = ix_j3;
	  }
	  p4_j1.SetPtEtaPhiM( m_jet_pt->at(ix_j1), m_jet_eta->at(ix_j1), m_jet_phi->at(ix_j1), m_jet_M->at(ix_j1) );
	  p4_j2.SetPtEtaPhiM( m_jet_pt->at(ix_j2), m_jet_eta->at(ix_j2), m_jet_phi->at(ix_j2), m_jet_M->at(ix_j2) );
	  p4_j3.SetPtEtaPhiM( m_jet_pt->at(ix_j3), m_jet_eta->at(ix_j3), m_jet_phi->at(ix_j3), m_jet_M->at(ix_j3) );
	  p4_j4.SetPtEtaPhiM( m_jet_pt->at(ix_j4), m_jet_eta->at(ix_j4), m_jet_phi->at(ix_j4), m_jet_M->at(ix_j4) );
	  TLorentzVector p4_j12 = p4_j1 + p4_j2;
	  TLorentzVector p4_j34 = p4_j3 + p4_j4;
	  if ( m_jet_n == 3 ) p4_j34 = p4_j3;
	  float avg_pt    =     ( p4_j12.Pt()  + p4_j34.Pt()  ) / 2;
	  float avg_eta   =     ( p4_j12.Eta() + p4_j34.Eta() ) / 2;
	  float avg_phi   =     ( p4_j12.Phi() + p4_j34.Phi() ) / 2;
	  float avg_invM  =     ( p4_j12.M()   + p4_j34.M()   ) / 2;
	  float diff_pt   = fabs( p4_j12.Pt()  - p4_j34.Pt()  );
	  float diff_eta  = fabs( p4_j12.Eta() - p4_j34.Eta() );
	  float diff_phi  = fabs( p4_j12.Phi() - p4_j34.Phi() );
	  float diff_invM = fabs( p4_j12.M()   - p4_j34.M()   );
	  float avg_sumPt = ( p4_j1.Pt() + p4_j2.Pt() + p4_j3.Pt() + p4_j4.Pt() ) / 2;
	  float avg_sumM  = ( p4_j1.M () + p4_j2.M () + p4_j3.M () + p4_j4.M () ) / 2;
	  if ( m_jet_n == 3 ) {
	    avg_sumPt = ( p4_j1.Pt() + p4_j2.Pt() + p4_j3.Pt() ) / 2;
	    avg_sumM  = ( p4_j1.M () + p4_j2.M () + p4_j3.M () ) / 2;
	  }
	  float avg_dR    = EJsHelper::deltaR(   p4_j12.Eta(), p4_j34.Eta(), p4_j12.Phi(), p4_j34.Phi() );
	  float dR_j12    = EJsHelper::deltaR( m_jet_eta ->at(ix_j1), m_jet_eta ->at(ix_j2), m_jet_phi ->at(ix_j1), m_jet_phi ->at(ix_j2) );
	  float dR_j34    = EJsHelper::deltaR( m_jet_eta ->at(ix_j3), m_jet_eta ->at(ix_j4), m_jet_phi ->at(ix_j3), m_jet_phi ->at(ix_j4) );
	  float avg_dRjj  = ( dR_j12 + dR_j34 ) / 2;
	  if ( diff_invM < mindiff ) {
	    mindiff            = diff_invM;
	    mindiff_invM       = avg_invM;
	    mindiff_pt         = avg_pt;
	    mindiff_ptdiff     = diff_pt;
	    mindiff_eta        = avg_eta;
	    mindiff_etadiff    = diff_eta;
	    mindiff_phi        = avg_phi;
	    mindiff_phidiff    = diff_phi;
	    mindiff_sumpt      = avg_sumPt;
	    mindiff_summ       = avg_sumM;
	    mindiff_dR         = avg_dR;
	    mindiff_dRjj       = avg_dRjj;
	  }
	  // average of dijet pairs with smallest pt difference between them
	  if ( diff_pt < mindiffpt ) {
	    mindiffpt          = diff_pt;
	    mindiffpt_pt       = avg_pt;
	    mindiffpt_eta      = avg_eta;
	    mindiffpt_etadiff  = diff_eta;
	    mindiffpt_phi      = avg_phi;
	    mindiffpt_phidiff  = diff_phi;
	    mindiffpt_invM     = avg_invM;
	    mindiffpt_invMdiff = diff_invM;
	    mindiffpt_sumpt    = avg_sumPt;
	    mindiffpt_summ     = avg_sumM;
	    mindiffpt_dR       = avg_dR;
	    mindiffpt_dRjj     = avg_dRjj;
	  }
	  // average of dijet pairs with largest dR between them
	  if ( avg_dR > maxdr ) {
	    maxdr              = avg_dR;
	    maxdr_dRjj         = avg_dRjj;
	    maxdr_pt           = avg_pt;
	    maxdr_ptdiff       = diff_pt;
	    maxdr_eta          = avg_eta;
	    maxdr_etadiff      = diff_eta;
	    maxdr_phi          = avg_phi;
	    maxdr_phidiff      = diff_phi;
	    maxdr_invM         = avg_invM;
	    maxdr_invMdiff     = diff_invM;
	    maxdr_sumpt        = avg_sumPt;
	    maxdr_summ         = avg_sumM;
	  }
	}
      } // end double loop over dijet pairs
      // --> if vrshift, multiply variables filling histos by corresponding scale factors...
      mindiff_pt_vrsh     = mindiff_pt;
      mindiff_invM_vrsh   = mindiff_invM;
      mindiffpt_pt_vrsh   = mindiffpt_pt;
      mindiffpt_invM_vrsh = mindiffpt_invM;
      maxdr_pt_vrsh       = maxdr_pt;
      maxdr_invM_vrsh     = maxdr_invM;
      if ( region.type == EJsHelper::VALIDATION || region.type == EJsHelper::JZ4W_SLICE_VALIDATION ) {
	mindiff_pt_vrsh     *= m_vrshift_njetjj_pt;
	mindiff_invM_vrsh   *= m_vrshift_njetjj_m;
	mindiffpt_pt_vrsh   *= m_vrshift_njetjjpt_pt;
	mindiffpt_invM_vrsh *= m_vrshift_njetjjpt_m;
	maxdr_pt_vrsh       *= m_vrshift_njetjjdr_pt;
	maxdr_invM_vrsh     *= m_vrshift_njetjjdr_m;
      }
      h_NJetJJ_pt              [ireg] ->Fill( mindiff_pt,          weight );
      h_NJetJJ_eta             [ireg] ->Fill( mindiff_eta,         weight );
      h_NJetJJ_phi             [ireg] ->Fill( mindiff_phi,         weight );
      h_NJetJJ_m               [ireg] ->Fill( mindiff_invM,        weight );
      h_NJetJJ_ptDiff          [ireg] ->Fill( mindiff_ptdiff,      weight );
      h_NJetJJ_etaDiff         [ireg] ->Fill( mindiff_etadiff,     weight );
      h_NJetJJ_phiDiff         [ireg] ->Fill( mindiff_phidiff,     weight );
      h_NJetJJ_mDiff           [ireg] ->Fill( mindiff,             weight );
      h_NJetJJ_sumPt           [ireg] ->Fill( mindiff_sumpt,       weight );
      h_NJetJJ_sumM            [ireg] ->Fill( mindiff_summ,        weight );
      h_NJetJJ_dR              [ireg] ->Fill( mindiff_dR,          weight );
      h_NJetJJ_dRjj            [ireg] ->Fill( mindiff_dRjj,        weight );
      h_NJetJJmindpt_pt        [ireg] ->Fill( mindiffpt_pt,        weight );
      h_NJetJJmindpt_eta       [ireg] ->Fill( mindiffpt_eta,       weight );
      h_NJetJJmindpt_phi       [ireg] ->Fill( mindiffpt_phi,       weight );
      h_NJetJJmindpt_m         [ireg] ->Fill( mindiffpt_invM,      weight );
      h_NJetJJmindpt_ptDiff    [ireg] ->Fill( mindiffpt,           weight );
      h_NJetJJmindpt_etaDiff   [ireg] ->Fill( mindiffpt_etadiff,   weight );
      h_NJetJJmindpt_phiDiff   [ireg] ->Fill( mindiffpt_phidiff,   weight );
      h_NJetJJmindpt_mDiff     [ireg] ->Fill( mindiffpt_invMdiff,  weight );
      h_NJetJJmindpt_sumPt     [ireg] ->Fill( mindiffpt_sumpt,     weight );
      h_NJetJJmindpt_sumM      [ireg] ->Fill( mindiffpt_summ,      weight );
      h_NJetJJmindpt_dR        [ireg] ->Fill( mindiffpt_dR,        weight );
      h_NJetJJmindpt_dRjj      [ireg] ->Fill( mindiffpt_dRjj,      weight );
      h_NJetJJmaxdr_pt         [ireg] ->Fill( maxdr_pt,            weight );
      h_NJetJJmaxdr_eta        [ireg] ->Fill( maxdr_eta,           weight );
      h_NJetJJmaxdr_phi        [ireg] ->Fill( maxdr_phi,           weight );
      h_NJetJJmaxdr_m          [ireg] ->Fill( maxdr_invM,          weight );
      h_NJetJJmaxdr_ptDiff     [ireg] ->Fill( maxdr_ptdiff,        weight );
      h_NJetJJmaxdr_etaDiff    [ireg] ->Fill( maxdr_etadiff,       weight );
      h_NJetJJmaxdr_phiDiff    [ireg] ->Fill( maxdr_phidiff,       weight );
      h_NJetJJmaxdr_mDiff      [ireg] ->Fill( maxdr_invMdiff,      weight );
      h_NJetJJmaxdr_sumPt      [ireg] ->Fill( maxdr_sumpt,         weight );
      h_NJetJJmaxdr_sumM       [ireg] ->Fill( maxdr_summ,          weight );
      h_NJetJJmaxdr_dR         [ireg] ->Fill( maxdr,               weight );
      h_NJetJJmaxdr_dRjj       [ireg] ->Fill( maxdr_dRjj,          weight );
      if ( m_histoInfoSwitch->m_vrshift ) {
	h_NJetJJ_pt_vrsh       [ireg] ->Fill( mindiff_pt_vrsh,     weight );
	h_NJetJJ_m_vrsh        [ireg] ->Fill( mindiff_invM_vrsh,   weight );
	h_NJetJJmindpt_pt_vrsh [ireg] ->Fill( mindiffpt_pt_vrsh,   weight );
	h_NJetJJmindpt_m_vrsh  [ireg] ->Fill( mindiffpt_invM_vrsh, weight );
	h_NJetJJmaxdr_pt_vrsh  [ireg] ->Fill( maxdr_pt_vrsh,       weight );
	h_NJetJJmaxdr_m_vrsh   [ireg] ->Fill( maxdr_invM_vrsh,     weight );
      }

      // grab average, min/max(pt) dijets of N-leading jets
      int sum_ct = p4_dijet_sum_count [m_LJix-1];
      if ( sum_ct ) {
	int max_ix1   = p4_dijet_max_ix  [m_LJix-1].first;
	int max_ix2   = p4_dijet_max_ix  [m_LJix-1].second;
	if ( max_ix1 != -1 && max_ix2 != -1 ) {
	  maxjj_sumPt   = m_jet_pt->at(max_ix1  ) + m_jet_pt->at(max_ix2  );
	  maxjj_sumM    = m_jet_M ->at(max_ix1  ) + m_jet_M ->at(max_ix2  );
	  maxjj_dR      = EJsHelper::deltaR( m_jet_eta->at(max_ix1  ), m_jet_eta->at(max_ix2  ),
					     m_jet_phi->at(max_ix1  ), m_jet_phi->at(max_ix2  ) );
	}
	int min_ix1   = p4_dijet_min_ix  [m_LJix-1].first;
	int min_ix2   = p4_dijet_min_ix  [m_LJix-1].second;
	if ( min_ix1 != -1 && min_ix2 != -1 ) {
	  minjj_sumPt   = m_jet_pt->at(min_ix1  ) + m_jet_pt->at(min_ix2  );
	  minjj_sumM    = m_jet_M ->at(min_ix1  ) + m_jet_M ->at(min_ix2  );
	  minjj_dR      = EJsHelper::deltaR( m_jet_eta->at(min_ix1  ), m_jet_eta->at(min_ix2  ),
					     m_jet_phi->at(min_ix1  ), m_jet_phi->at(min_ix2  ) );
	}
	int maxpt_ix1 = p4_dijet_maxpt_ix[m_LJix-1].first;
	int maxpt_ix2 = p4_dijet_maxpt_ix[m_LJix-1].second;
	if ( maxpt_ix1 != -1 && maxpt_ix2 != -1 ) {
	  maxptjj_sumPt = m_jet_pt->at(maxpt_ix1) + m_jet_pt->at(maxpt_ix2);
	  maxptjj_sumM  = m_jet_M ->at(maxpt_ix1) + m_jet_M ->at(maxpt_ix2);
	  maxptjj_dR    = EJsHelper::deltaR( m_jet_eta->at(maxpt_ix1), m_jet_eta->at(maxpt_ix2),
					     m_jet_phi->at(maxpt_ix1), m_jet_phi->at(maxpt_ix2) );
	}
	int minpt_ix1 = p4_dijet_minpt_ix[m_LJix-1].first;
	int minpt_ix2 = p4_dijet_minpt_ix[m_LJix-1].second;
	if ( minpt_ix1 != -1 && minpt_ix2 != -1 ) {
	  minptjj_sumPt = m_jet_pt->at(minpt_ix1) + m_jet_pt->at(minpt_ix2);
	  minptjj_sumM  = m_jet_M ->at(minpt_ix1) + m_jet_M ->at(minpt_ix2);
	  minptjj_dR    = EJsHelper::deltaR( m_jet_eta->at(minpt_ix1), m_jet_eta->at(minpt_ix2),
					     m_jet_phi->at(minpt_ix1), m_jet_phi->at(minpt_ix2) );
	}

	avgjj_pt    = p4_dijet_sum_pt  [m_LJix-1]/sum_ct;
	avgjj_eta   = p4_dijet_sum_eta [m_LJix-1]/sum_ct;
	avgjj_phi   = p4_dijet_sum_phi [m_LJix-1]/sum_ct;
	avgjj_m     = p4_dijet_sum_m   [m_LJix-1]/sum_ct;
	avgjj_dR    = p4_dijet_sum_dr  [m_LJix-1]/sum_ct;
	maxjj_pt    = p4_dijet_max     [m_LJix-1].Pt ();
	maxjj_eta   = p4_dijet_max     [m_LJix-1].Eta();
	maxjj_phi   = p4_dijet_max     [m_LJix-1].Phi();
	maxjj_m     = p4_dijet_max     [m_LJix-1].M  ();
	minjj_pt    = p4_dijet_min     [m_LJix-1].Pt ();
	minjj_eta   = p4_dijet_min     [m_LJix-1].Eta();
	minjj_phi   = p4_dijet_min     [m_LJix-1].Phi();
	minjj_m     = p4_dijet_min     [m_LJix-1].M  ();
	maxptjj_pt  = p4_dijet_maxpt   [m_LJix-1].Pt ();
	maxptjj_eta = p4_dijet_maxpt   [m_LJix-1].Eta();
	maxptjj_phi = p4_dijet_maxpt   [m_LJix-1].Phi();
	maxptjj_m   = p4_dijet_maxpt   [m_LJix-1].M  ();
	minptjj_pt  = p4_dijet_minpt   [m_LJix-1].Pt ();
	minptjj_eta = p4_dijet_minpt   [m_LJix-1].Eta();
	minptjj_phi = p4_dijet_minpt   [m_LJix-1].Phi();
	minptjj_m   = p4_dijet_minpt   [m_LJix-1].M  ();
      } // end if sum_ct

      avgjj_pt_vrsh         = avgjj_pt;
      avgjj_m_vrsh          = avgjj_m;
      maxjj_pt_vrsh         = maxjj_pt;
      maxjj_m_vrsh          = maxjj_m;
      maxjj_sumPt_vrsh      = maxjj_sumPt;
      maxjj_sumM_vrsh       = maxjj_sumM;
      minjj_pt_vrsh         = minjj_pt;
      minjj_m_vrsh          = minjj_m;
      minjj_sumPt_vrsh      = minjj_sumPt;
      minjj_sumM_vrsh       = minjj_sumM;
      maxptjj_pt_vrsh       = maxptjj_pt;
      maxptjj_m_vrsh        = maxptjj_m;
      maxptjj_sumPt_vrsh    = maxptjj_sumPt;
      maxptjj_sumM_vrsh     = maxptjj_sumM;
      minptjj_pt_vrsh       = minptjj_pt;
      minptjj_m_vrsh        = minptjj_m;
      minptjj_sumPt_vrsh    = minptjj_sumPt;
      minptjj_sumM_vrsh     = minptjj_sumM;
      if ( region.type == EJsHelper::VALIDATION || region.type == EJsHelper::JZ4W_SLICE_VALIDATION ) {
	avgjj_pt_vrsh      *= m_vrshift_avgnjetjj_pt;
	avgjj_m_vrsh       *= m_vrshift_avgnjetjj_m;
	maxjj_pt_vrsh      *= m_vrshift_maxnjetjj_pt;
	maxjj_m_vrsh       *= m_vrshift_maxnjetjj_m;
	maxjj_sumPt_vrsh   *= m_vrshift_maxnjetjj_ht;
	maxjj_sumM_vrsh    *= m_vrshift_maxnjetjj_sm;
	minjj_pt_vrsh      *= m_vrshift_minnjetjj_pt;
	minjj_m_vrsh       *= m_vrshift_minnjetjj_m;
	minjj_sumPt_vrsh   *= m_vrshift_minnjetjj_ht;
	minjj_sumM_vrsh    *= m_vrshift_minnjetjj_sm;
	maxptjj_pt_vrsh    *= m_vrshift_maxptnjetjj_pt;
	maxptjj_m_vrsh     *= m_vrshift_maxptnjetjj_m;
	maxptjj_sumPt_vrsh *= m_vrshift_maxptnjetjj_ht;
	maxptjj_sumM_vrsh  *= m_vrshift_maxptnjetjj_sm;
	minptjj_pt_vrsh    *= m_vrshift_minptnjetjj_pt;
	minptjj_m_vrsh     *= m_vrshift_minptnjetjj_m;
	minptjj_sumPt_vrsh *= m_vrshift_minptnjetjj_ht;
	minptjj_sumM_vrsh  *= m_vrshift_minptnjetjj_sm;
      }
      h_avgNJetJJ_pt             [ireg] ->Fill( avgjj_pt,           weight );
      h_avgNJetJJ_eta            [ireg] ->Fill( avgjj_eta,          weight );
      h_avgNJetJJ_phi            [ireg] ->Fill( avgjj_phi,          weight );
      h_avgNJetJJ_m              [ireg] ->Fill( avgjj_m,            weight );
      h_avgNJetJJ_dR             [ireg] ->Fill( avgjj_dR,           weight );
      h_maxNJetJJ_pt             [ireg] ->Fill( maxjj_pt,           weight );
      h_maxNJetJJ_eta            [ireg] ->Fill( maxjj_eta,          weight );
      h_maxNJetJJ_phi            [ireg] ->Fill( maxjj_phi,          weight );
      h_maxNJetJJ_m              [ireg] ->Fill( maxjj_m,            weight );
      h_maxNJetJJ_sumPt          [ireg] ->Fill( maxjj_sumPt,        weight );
      h_maxNJetJJ_sumM           [ireg] ->Fill( maxjj_sumM,         weight );
      h_maxNJetJJ_dR             [ireg] ->Fill( maxjj_dR,           weight );
      h_minNJetJJ_pt             [ireg] ->Fill( minjj_pt,           weight );
      h_minNJetJJ_eta            [ireg] ->Fill( minjj_eta,          weight );
      h_minNJetJJ_phi            [ireg] ->Fill( minjj_phi,          weight );
      h_minNJetJJ_m              [ireg] ->Fill( minjj_m,            weight );
      h_minNJetJJ_sumPt          [ireg] ->Fill( minjj_sumPt,        weight );
      h_minNJetJJ_sumM           [ireg] ->Fill( minjj_sumM,         weight );
      h_minNJetJJ_dR             [ireg] ->Fill( minjj_dR,           weight );
      h_maxptNJetJJ_pt           [ireg] ->Fill( maxptjj_pt,         weight );
      h_maxptNJetJJ_eta          [ireg] ->Fill( maxptjj_eta,        weight );
      h_maxptNJetJJ_phi          [ireg] ->Fill( maxptjj_phi,        weight );
      h_maxptNJetJJ_m            [ireg] ->Fill( maxptjj_m,          weight );
      h_maxptNJetJJ_sumPt        [ireg] ->Fill( maxptjj_sumPt,      weight );
      h_maxptNJetJJ_sumM         [ireg] ->Fill( maxptjj_sumM,       weight );
      h_maxptNJetJJ_dR           [ireg] ->Fill( maxptjj_dR,         weight );
      h_minptNJetJJ_pt           [ireg] ->Fill( minptjj_pt,         weight );
      h_minptNJetJJ_eta          [ireg] ->Fill( minptjj_eta,        weight );
      h_minptNJetJJ_phi          [ireg] ->Fill( minptjj_phi,        weight );
      h_minptNJetJJ_m            [ireg] ->Fill( minptjj_m,          weight );
      h_minptNJetJJ_sumPt        [ireg] ->Fill( minptjj_sumPt,      weight );
      h_minptNJetJJ_sumM         [ireg] ->Fill( minptjj_sumM,       weight );
      h_minptNJetJJ_dR           [ireg] ->Fill( minptjj_dR,         weight );
      if ( m_histoInfoSwitch->m_vrshift ) {
	h_avgNJetJJ_pt_vrsh      [ireg] ->Fill( avgjj_pt_vrsh,      weight );
	h_avgNJetJJ_m_vrsh       [ireg] ->Fill( avgjj_m_vrsh,       weight );
	h_maxNJetJJ_pt_vrsh      [ireg] ->Fill( maxjj_pt_vrsh,      weight );
	h_maxNJetJJ_m_vrsh       [ireg] ->Fill( maxjj_m_vrsh,       weight );
	h_maxNJetJJ_sumPt_vrsh   [ireg] ->Fill( maxjj_sumPt_vrsh,   weight );
	h_maxNJetJJ_sumM_vrsh    [ireg] ->Fill( maxjj_sumM_vrsh,    weight );
	h_minNJetJJ_pt_vrsh      [ireg] ->Fill( minjj_pt_vrsh,      weight );
	h_minNJetJJ_m_vrsh       [ireg] ->Fill( minjj_m_vrsh,       weight );
	h_minNJetJJ_sumPt_vrsh   [ireg] ->Fill( minjj_sumPt_vrsh,   weight );
	h_minNJetJJ_sumM_vrsh    [ireg] ->Fill( minjj_sumM_vrsh,    weight );
	h_maxptNJetJJ_pt_vrsh    [ireg] ->Fill( maxptjj_pt_vrsh,    weight );
	h_maxptNJetJJ_m_vrsh     [ireg] ->Fill( maxptjj_m_vrsh,     weight );
	h_maxptNJetJJ_sumPt_vrsh [ireg] ->Fill( maxptjj_sumPt_vrsh, weight );
	h_maxptNJetJJ_sumM_vrsh  [ireg] ->Fill( maxptjj_sumM_vrsh,  weight );
	h_minptNJetJJ_pt_vrsh    [ireg] ->Fill( minptjj_pt_vrsh,    weight );
	h_minptNJetJJ_m_vrsh     [ireg] ->Fill( minptjj_m_vrsh,     weight );
	h_minptNJetJJ_sumPt_vrsh [ireg] ->Fill( minptjj_sumPt_vrsh, weight );
	h_minptNJetJJ_sumM_vrsh  [ireg] ->Fill( minptjj_sumM_vrsh,  weight );
      }
    } // end if truthOnly

    // do NJetX cutflow
    if ( m_histoInfoSwitch->m_cutflow || m_histoInfoSwitch->m_abcdcutOnly ) {
      for ( size_t icut = 0; icut != m_njetht_cut.size(); ++icut ) {
	if ( njht             > m_njetht_cut         [icut] ) h_evt_cutflow_NJetHt            [ireg] ->Fill( icut, weight );
	if ( !m_histoInfoSwitch->m_truthOnly ) {
	  if ( njpt           > m_njetpt_cut         [icut] ) h_evt_cutflow_NJetPt            [ireg] ->Fill( icut, weight );
	  if ( njsumm         > m_njetsm_cut         [icut] ) h_evt_cutflow_NJetSumM          [ireg] ->Fill( icut, weight );
	  if ( mindiff_pt     > m_njetjj_pt_cut      [icut] ) h_evt_cutflow_NJetJJ_pt         [ireg] ->Fill( icut, weight );
	  if ( mindiff_invM   > m_njetjj_m_cut       [icut] ) h_evt_cutflow_NJetJJ_m          [ireg] ->Fill( icut, weight );
	  if ( mindiffpt_pt   > m_njetjjpt_pt_cut    [icut] ) h_evt_cutflow_NJetJJmindpt_pt   [ireg] ->Fill( icut, weight );
	  if ( mindiffpt_invM > m_njetjjpt_m_cut     [icut] ) h_evt_cutflow_NJetJJmindpt_m    [ireg] ->Fill( icut, weight );
	  if ( maxdr_pt       > m_njetjjdr_pt_cut    [icut] ) h_evt_cutflow_NJetJJmaxdr_pt    [ireg] ->Fill( icut, weight );
	  if ( maxdr_invM     > m_njetjjdr_m_cut     [icut] ) h_evt_cutflow_NJetJJmaxdr_m     [ireg] ->Fill( icut, weight );
	  if ( avgjj_pt       > m_avgnjetjj_pt_cut   [icut] ) h_evt_cutflow_avgNJetJJ_pt      [ireg] ->Fill( icut, weight );
	  if ( avgjj_m        > m_avgnjetjj_m_cut    [icut] ) h_evt_cutflow_avgNJetJJ_m       [ireg] ->Fill( icut, weight );
	  if ( maxjj_pt       > m_maxnjetjj_pt_cut   [icut] ) h_evt_cutflow_maxNJetJJ_pt      [ireg] ->Fill( icut, weight );
	  if ( maxjj_m        > m_maxnjetjj_m_cut    [icut] ) h_evt_cutflow_maxNJetJJ_m       [ireg] ->Fill( icut, weight );
	  if ( maxjj_sumPt    > m_maxnjetjj_ht_cut   [icut] ) h_evt_cutflow_maxNJetJJ_sumPt   [ireg] ->Fill( icut, weight );
	  if ( maxjj_sumM     > m_maxnjetjj_sm_cut   [icut] ) h_evt_cutflow_maxNJetJJ_sumM    [ireg] ->Fill( icut, weight );
	  if ( minjj_pt       > m_minnjetjj_pt_cut   [icut] ) h_evt_cutflow_minNJetJJ_pt      [ireg] ->Fill( icut, weight );
	  if ( minjj_m        > m_minnjetjj_m_cut    [icut] ) h_evt_cutflow_minNJetJJ_m       [ireg] ->Fill( icut, weight );
	  if ( minjj_sumPt    > m_minnjetjj_ht_cut   [icut] ) h_evt_cutflow_minNJetJJ_sumPt   [ireg] ->Fill( icut, weight );
	  if ( minjj_sumM     > m_minnjetjj_sm_cut   [icut] ) h_evt_cutflow_minNJetJJ_sumM    [ireg] ->Fill( icut, weight );
	  if ( maxptjj_pt     > m_maxptnjetjj_pt_cut [icut] ) h_evt_cutflow_maxptNJetJJ_pt    [ireg] ->Fill( icut, weight );
	  if ( maxptjj_m      > m_maxptnjetjj_m_cut  [icut] ) h_evt_cutflow_maxptNJetJJ_m     [ireg] ->Fill( icut, weight );
	  if ( maxptjj_sumPt  > m_maxptnjetjj_ht_cut [icut] ) h_evt_cutflow_maxptNJetJJ_sumPt [ireg] ->Fill( icut, weight );
	  if ( maxptjj_sumM   > m_maxptnjetjj_sm_cut [icut] ) h_evt_cutflow_maxptNJetJJ_sumM  [ireg] ->Fill( icut, weight );
	  if ( minptjj_pt     > m_minptnjetjj_pt_cut [icut] ) h_evt_cutflow_minptNJetJJ_pt    [ireg] ->Fill( icut, weight );
	  if ( minptjj_m      > m_minptnjetjj_m_cut  [icut] ) h_evt_cutflow_minptNJetJJ_m     [ireg] ->Fill( icut, weight );
	  if ( minptjj_sumPt  > m_minptnjetjj_ht_cut [icut] ) h_evt_cutflow_minptNJetJJ_sumPt [ireg] ->Fill( icut, weight );
	  if ( minptjj_sumM   > m_minptnjetjj_sm_cut [icut] ) h_evt_cutflow_minptNJetJJ_sumM  [ireg] ->Fill( icut, weight );
	}
      }
    }



    
    // ----------------------- //
    // --- TRUTH PARTICLES --- //
    // ----------------------- //

    // --> ADD IF NOT ABCD-ONLY (FOR TRUTH VERTS TOO)
    
    double truthPart_sumPt     = 0;
    double truthPartDark_sumPt = 0;
    
    if ( m_mc ) {
      if ( m_debug ) Info( "EJsHistogramManager::execute()", "doing truth particle histos" );
      // set vector of ntp counters
      std::vector<int> n_tp ( m_nTypeTPs, 0 );

      // loop over truth particles
      for ( int i = 0; i != m_tp_n; ++i ) {

      	// sum truth (dark) particle pt for calculating truth (dark) orphan pt
      	if ( m_tp_isStable ->at(i) )
      	  truthPart_sumPt += m_tp_pt ->at(i);
      	// --> dark particle sum-pt
      	if ( m_tp_isDark ->at(i) )
	  // only count "stable" dark particles decaying to SM
	  if ( ( m_tp_nChildren->at(i) && fabs( m_tp_child_pdgId ->at(i).at(0) ) < 4.9e6 ) || !m_tp_nChildren->at(i) ) 
	    truthPartDark_sumPt += m_tp_pt ->at(i);

      	// get truth particle four-momentum
      	TLorentzVector tp_p4;
      	tp_p4.SetPtEtaPhiM( m_tp_pt->at(i), m_tp_eta->at(i), m_tp_phi->at(i), m_tp_M->at(i) );
	  
      	// set vector of truth particle types
      	std::vector<int> tp;
      	getTPTypes( i, tp );

      	// loop over truth particle types and fill histograms
      	for ( size_t itp = 0; itp != tp.size(); ++itp ) {
      	  if ( !tp[itp] ) continue;
      	  ++n_tp[itp];
	  
      	  if ( !doHists || m_histoInfoSwitch->m_abcdcutOnly ) continue;
      	  h_tp_pt        [ireg][itp] ->Fill( m_tp_pt            ->at(i), weight );
      	  h_tp_eta       [ireg][itp] ->Fill( m_tp_eta           ->at(i), weight );
      	  h_tp_phi       [ireg][itp] ->Fill( m_tp_phi           ->at(i), weight );
      	  h_tp_E         [ireg][itp] ->Fill( m_tp_E             ->at(i), weight );
      	  h_tp_M         [ireg][itp] ->Fill( m_tp_M             ->at(i), weight );
      	  h_tp_betagamma [ireg][itp] ->Fill( tp_p4.Beta()*tp_p4.Gamma(), weight );
      	  h_tp_charge    [ireg][itp] ->Fill( m_tp_charge        ->at(i), weight );
      	  h_tp_nParents  [ireg][itp] ->Fill( m_tp_nParents      ->at(i), weight );
      	  h_tp_nChildren [ireg][itp] ->Fill( m_tp_nChildren     ->at(i), weight );
	  for ( int j  = 0; j  != m_tp_nParents ->at(i); ++j  )
	    h_tp_parentPdgId [ireg][itp] ->Fill( fabs( m_tp_parent_pdgId ->at(i).at(j) ), weight );
	  for ( int j = 0; j != m_tp_nChildren->at(i); ++j )
	    h_tp_childPdgId  [ireg][itp] ->Fill( fabs( m_tp_child_pdgId  ->at(i).at(j) ), weight );
      	} // end loop over truth particle types

	if ( !doHists || m_histoInfoSwitch->m_abcdcutOnly ) continue;
	
	// do reconstruction efficiency studies
	if ( m_histoInfoSwitch->m_llpRecoEff || m_histoInfoSwitch->m_llptrkRecoEff ) {
	  // do fiducial selections: pt > 1 GeV, |eta| < 2.5, r-prod < 440 mm, charge = +-1, from llp decay
	  if ( m_tp_pt ->at(i) <  1 )           continue;
	  if ( fabs( m_tp_eta ->at(i) ) > 2.5 ) continue;
	  if ( !m_tp_pvtx   ->at(i) )           continue;
	  if (  m_tp_pvtx_r ->at(i) > 440 )     continue;
	  if ( !m_tp_charge ->at(i) )           continue;
	  if ( !m_tp_isDesc ->at(i) )           continue;

	  // look for (standard/lrt) reco track and get track parameters
	  bool   isRecoTrk      = false;
	  bool   isStdTrk       = false;
	  bool   isLrtTrk       = false;
	  double recoTrk_d0     = 0;
	  double recoTrk_z0     = 0;
	  double recoTrk_qOverP = 0;
	  if ( m_tp_isReco ->at(i) ) {
	    isRecoTrk = true;
	    int trkIx = -1;
	    for ( int itrk = 0; itrk != m_trk_n; ++itrk )
	      if ( m_trk_ID ->at(itrk) == m_tp_recoID ->at(i) ) trkIx = itrk;
	    if ( trkIx != -1 ) {
	      if ( m_trk_isLRT ->at(trkIx) ) isLrtTrk = true;
	      else                           isStdTrk = true;
	      recoTrk_d0     = m_trk_d0     ->at(trkIx);
	      recoTrk_z0     = m_trk_z0     ->at(trkIx);
	      recoTrk_qOverP = m_trk_qOverP ->at(trkIx);
	    }
	  }

	  // get production vertex if available in ntuple --> otherwise use ancestor vertex (close enough)
	  int prodVtx_index = -1;
	  for ( int itv = 0; itv != m_truthVtx_n; ++itv )
	    if ( m_tp_pvtx_ID ->at(i) == m_truthVtx_ID ->at(itv) ) prodVtx_index = itv;
	    
	  std::vector<int> llptrk;
	  int ancestor_index = getLLPDescTypes( m_tp_ID ->at(i), llptrk );

	  // get nearest track from same ancestor
	  double minTrkDR = AlgConsts::maxValue;
	  for ( int llpd = 0; llpd != m_truthVtx_nDesc ->at(ancestor_index); ++llpd ) {
	    if ( m_tp_ID ->at(i) == m_truthVtx_desc_ID ->at(ancestor_index)[llpd] ) continue;
	    double trkDR = EJsHelper::deltaR( m_tp_eta ->at(i), m_truthVtx_desc_eta ->at(ancestor_index)[llpd],
					      m_tp_phi ->at(i), m_truthVtx_desc_phi ->at(ancestor_index)[llpd] );
	    if ( trkDR < minTrkDR ) minTrkDR = trkDR;
	  }
	  
	  for ( size_t illp = 0; illp != llptrk.size(); ++illp ) {
	    
	    if ( !llptrk[illp] ) continue;
	    
	    h_LLPtrk_r           [ireg][illp] ->Fill( m_tp_pvtx_r  ->at(i), weight );
	    h_LLPtrk_pt          [ireg][illp] ->Fill( m_tp_pt      ->at(i), weight );
	    h_LLPtrk_eta         [ireg][illp] ->Fill( m_tp_eta     ->at(i), weight );
	    h_LLPtrk_phi         [ireg][illp] ->Fill( m_tp_phi     ->at(i), weight );
	    h_LLPtrk_avgMu       [ireg][illp] ->Fill( m_averageMu,          weight );
	    h_LLPtrk_minDR       [ireg][illp] ->Fill( minTrkDR,             weight );
	    if ( isRecoTrk ) {
	      h_recoLLPtrk_r     [ireg][illp] ->Fill( m_tp_pvtx_r  ->at(i), weight );
	      h_recoLLPtrk_pt    [ireg][illp] ->Fill( m_tp_pt      ->at(i), weight );
	      h_recoLLPtrk_eta   [ireg][illp] ->Fill( m_tp_eta     ->at(i), weight );
	      h_recoLLPtrk_phi   [ireg][illp] ->Fill( m_tp_phi     ->at(i), weight );
	      h_recoLLPtrk_avgMu [ireg][illp] ->Fill( m_averageMu,          weight );
	      h_recoLLPtrk_minDR [ireg][illp] ->Fill( minTrkDR,             weight );
	    }
	    if ( isStdTrk ) {
	      h_stdLLPtrk_r      [ireg][illp] ->Fill( m_tp_pvtx_r  ->at(i), weight );
	      h_stdLLPtrk_pt     [ireg][illp] ->Fill( m_tp_pt      ->at(i), weight );
	      h_stdLLPtrk_eta    [ireg][illp] ->Fill( m_tp_eta     ->at(i), weight );
	      h_stdLLPtrk_phi    [ireg][illp] ->Fill( m_tp_phi     ->at(i), weight );
	      h_stdLLPtrk_avgMu  [ireg][illp] ->Fill( m_averageMu,          weight );
	      h_stdLLPtrk_minDR  [ireg][illp] ->Fill( minTrkDR,             weight );
	    }
	    if ( isLrtTrk ) {
	      h_lrtLLPtrk_r      [ireg][illp] ->Fill( m_tp_pvtx_r  ->at(i), weight );
	      h_lrtLLPtrk_pt     [ireg][illp] ->Fill( m_tp_pt      ->at(i), weight );
	      h_lrtLLPtrk_eta    [ireg][illp] ->Fill( m_tp_eta     ->at(i), weight );
	      h_lrtLLPtrk_phi    [ireg][illp] ->Fill( m_tp_phi     ->at(i), weight );
	      h_lrtLLPtrk_avgMu  [ireg][illp] ->Fill( m_averageMu,          weight );
	      h_lrtLLPtrk_minDR  [ireg][illp] ->Fill( minTrkDR,             weight );
	    }

	    int pvtx_index = prodVtx_index;
	    if ( pvtx_index == -1 ) pvtx_index = ancestor_index;

	    double llptrk_d0 = 0;
	    double llptrk_z0 = 0;
	    TVector3 pointvec
	      ( m_truthVtx_x ->at(pvtx_index) - m_pv_x, m_truthVtx_y ->at(pvtx_index) - m_pv_y, m_truthVtx_z ->at(pvtx_index) - m_pv_z );
	    double dphi_llptrk_pointvec = EJsHelper::deltaPhi( m_tp_phi ->at(i), pointvec.Phi() );
	    llptrk_d0 = m_tp_pvtx_r ->at(i) * TMath::Sin( dphi_llptrk_pointvec );
	    llptrk_z0 = m_tp_pvtx_r ->at(i) / TMath::Tan( pointvec.Theta()     );

	    // residual d0, z0, q/p
	    double resid_d0     = recoTrk_d0 - llptrk_d0;
	    double resid_z0     = recoTrk_z0 - llptrk_z0;
	    double resid_qOverP = recoTrk_qOverP - ( m_tp_charge ->at(i) / tp_p4.Vect().Mag() );
	    
	    h_LLPtrk_x        [ireg][illp] ->Fill( m_truthVtx_x ->at(pvtx_index), weight );
	    h_LLPtrk_y        [ireg][illp] ->Fill( m_truthVtx_y ->at(pvtx_index), weight );
	    h_LLPtrk_z        [ireg][illp] ->Fill( m_truthVtx_z ->at(pvtx_index), weight );
	    h_LLPtrk_d0       [ireg][illp] ->Fill( llptrk_d0,                     weight );
	    h_LLPtrk_z0       [ireg][illp] ->Fill( llptrk_z0,                     weight );
	    if ( isRecoTrk ) {
	      h_recoLLPtrk_x  [ireg][illp] ->Fill( m_truthVtx_x ->at(pvtx_index), weight );
	      h_recoLLPtrk_y  [ireg][illp] ->Fill( m_truthVtx_y ->at(pvtx_index), weight );
	      h_recoLLPtrk_z  [ireg][illp] ->Fill( m_truthVtx_z ->at(pvtx_index), weight );
	      h_recoLLPtrk_d0 [ireg][illp] ->Fill( llptrk_d0,                     weight );
	      h_recoLLPtrk_z0 [ireg][illp] ->Fill( llptrk_z0,                     weight );
	      h_recoLLPtrk_resid_d0        [ireg][illp] ->Fill( resid_d0,     weight );
	      h_recoLLPtrk_resid_z0        [ireg][illp] ->Fill( resid_z0,     weight );
	      h_recoLLPtrk_resid_qOverP    [ireg][illp] ->Fill( resid_qOverP, weight );
	      h_recoLLPtrk_resid_d0_r      [ireg][illp] ->Fill( m_tp_pvtx_r ->at(i), resid_d0,     weight );
	      h_recoLLPtrk_resid_d0_pt     [ireg][illp] ->Fill( m_tp_pt     ->at(i), resid_d0,     weight );
	      h_recoLLPtrk_resid_z0_r      [ireg][illp] ->Fill( m_tp_pvtx_r ->at(i), resid_z0,     weight );
	      h_recoLLPtrk_resid_z0_pt     [ireg][illp] ->Fill( m_tp_pt     ->at(i), resid_z0,     weight );
	      h_recoLLPtrk_resid_qOverP_r  [ireg][illp] ->Fill( m_tp_pvtx_r ->at(i), resid_qOverP, weight );
	      h_recoLLPtrk_resid_qOverP_pt [ireg][illp] ->Fill( m_tp_pt     ->at(i), resid_qOverP, weight );
	    }
	    if ( isStdTrk ) {
	      h_stdLLPtrk_x   [ireg][illp] ->Fill( m_truthVtx_x ->at(pvtx_index), weight );
	      h_stdLLPtrk_y   [ireg][illp] ->Fill( m_truthVtx_y ->at(pvtx_index), weight );
	      h_stdLLPtrk_z   [ireg][illp] ->Fill( m_truthVtx_z ->at(pvtx_index), weight );
	      h_stdLLPtrk_d0  [ireg][illp] ->Fill( llptrk_d0,                     weight );
	      h_stdLLPtrk_z0  [ireg][illp] ->Fill( llptrk_z0,                     weight );
	      h_stdLLPtrk_resid_d0        [ireg][illp] ->Fill( resid_d0,     weight );
	      h_stdLLPtrk_resid_z0        [ireg][illp] ->Fill( resid_z0,     weight );
	      h_stdLLPtrk_resid_qOverP    [ireg][illp] ->Fill( resid_qOverP, weight );
	      h_stdLLPtrk_resid_d0_r      [ireg][illp] ->Fill( m_tp_pvtx_r ->at(i), resid_d0,     weight );
	      h_stdLLPtrk_resid_d0_pt     [ireg][illp] ->Fill( m_tp_pt     ->at(i), resid_d0,     weight );
	      h_stdLLPtrk_resid_z0_r      [ireg][illp] ->Fill( m_tp_pvtx_r ->at(i), resid_z0,     weight );
	      h_stdLLPtrk_resid_z0_pt     [ireg][illp] ->Fill( m_tp_pt     ->at(i), resid_z0,     weight );
	      h_stdLLPtrk_resid_qOverP_r  [ireg][illp] ->Fill( m_tp_pvtx_r ->at(i), resid_qOverP, weight );
	      h_stdLLPtrk_resid_qOverP_pt [ireg][illp] ->Fill( m_tp_pt     ->at(i), resid_qOverP, weight );
	    }
	    if ( isLrtTrk ) {
	      h_lrtLLPtrk_x   [ireg][illp] ->Fill( m_truthVtx_x ->at(pvtx_index), weight );
	      h_lrtLLPtrk_y   [ireg][illp] ->Fill( m_truthVtx_y ->at(pvtx_index), weight );
	      h_lrtLLPtrk_z   [ireg][illp] ->Fill( m_truthVtx_z ->at(pvtx_index), weight );
	      h_lrtLLPtrk_d0  [ireg][illp] ->Fill( llptrk_d0,                     weight );
	      h_lrtLLPtrk_z0  [ireg][illp] ->Fill( llptrk_z0,                     weight );
	      h_lrtLLPtrk_resid_d0        [ireg][illp] ->Fill( resid_d0,     weight );
	      h_lrtLLPtrk_resid_z0        [ireg][illp] ->Fill( resid_z0,     weight );
	      h_lrtLLPtrk_resid_qOverP    [ireg][illp] ->Fill( resid_qOverP, weight );
	      h_lrtLLPtrk_resid_d0_r      [ireg][illp] ->Fill( m_tp_pvtx_r ->at(i), resid_d0,     weight );
	      h_lrtLLPtrk_resid_d0_pt     [ireg][illp] ->Fill( m_tp_pt     ->at(i), resid_d0,     weight );
	      h_lrtLLPtrk_resid_z0_r      [ireg][illp] ->Fill( m_tp_pvtx_r ->at(i), resid_z0,     weight );
	      h_lrtLLPtrk_resid_z0_pt     [ireg][illp] ->Fill( m_tp_pt     ->at(i), resid_z0,     weight );
	      h_lrtLLPtrk_resid_qOverP_r  [ireg][illp] ->Fill( m_tp_pvtx_r ->at(i), resid_qOverP, weight );
	      h_lrtLLPtrk_resid_qOverP_pt [ireg][illp] ->Fill( m_tp_pt     ->at(i), resid_qOverP, weight );
	    }
	  } // end loop over llp descendant types
	  
	} // end reconstruction efficiency studies
	
      } // end loop over truth particles

      // fill truth particle count histoograms
      for ( size_t itp = 0; itp != n_tp.size(); ++itp )
       	h_tp_n [ireg][itp] ->Fill( n_tp[itp], weight );
    } // end if mc
    

    
    // -------------- //
    // --- TRACKS --- //
    // -------------- //
    if ( !m_histoInfoSwitch->m_truthOnly ) {
      if ( m_debug ) Info( "EJsHistogramManager::execute()", "doing track histos" );
      
      // set vector of ntrk counters
      std::vector<int> n_trk ( m_nTypeTrks, 0 );
    
      // loop over tracks
      for ( int i = 0; i != m_trk_n; ++i ) {
	// set vector of track types
	std::vector<int> trk;
	getTrkTypes( i, trk, base_dv );
	// loop over track types and fill histograms
	for ( size_t it = 0; it != trk.size(); ++it ) {
	  if ( !trk[it] ) continue;
	  ++n_trk[it];
	  //if ( !doHists || m_histoInfoSwitch->m_abcdcutOnly ) continue;
	} // end loop over track types
      } // end loop over tracks
      
      // fill track count histograms
      for ( size_t it = 0; it != n_trk.size(); ++it )
	h_trk_n [ireg][it] ->Fill( n_trk[it], weight );
    }



    // ---------------------- //
    // --- TRUTH VERTICES --- //
    // ---------------------- //
    if ( m_mc ) {
      if ( m_debug ) Info( "EJsHistogramManager::execute()", "doing truth vertex histos" );

      // set vector of nLLP counters
      std::vector<int> n_LLP ( m_nTypeLLPs, 0 );
      
      // loop over truth vertices
      for ( int i = 0; i != m_truthVtx_n; ++i ) {

	// get vector of LLP types
	std::vector<int> LLP;
	getLLPTypes( i, LLP );

	// loop over LLP types and fill histograms
	for ( size_t illp = 0; illp != LLP.size(); ++illp ) {
	  if ( !LLP[illp] ) continue;
	  ++n_LLP[illp];

	  if ( !doHists || m_histoInfoSwitch->m_abcdcutOnly ) continue;
	  h_LLPdVtx_z          [ireg][illp] ->Fill( m_truthVtx_z          ->at(i), weight );
	  h_LLPdVtx_r          [ireg][illp] ->Fill( m_truthVtx_r          ->at(i), weight );
	  h_LLPdVtx_pt         [ireg][illp] ->Fill( m_truthVtx_pt         ->at(i), weight );
	  h_LLPdVtx_eta        [ireg][illp] ->Fill( m_truthVtx_eta        ->at(i), weight );
	  h_LLPdVtx_phi        [ireg][illp] ->Fill( m_truthVtx_phi        ->at(i), weight );
	  h_LLPdVtx_mass       [ireg][illp] ->Fill( m_truthVtx_mass       ->at(i), weight );
	  h_LLPdVtx_childOpAng [ireg][illp] ->Fill( m_truthVtx_childOpAng ->at(i), weight );
	  h_LLPdVtx_nOutP      [ireg][illp] ->Fill( m_truthVtx_nOutP      ->at(i), weight );
	  h_LLPdVtx_ndesc      [ireg][illp] ->Fill( m_truthVtx_nDesc      ->at(i), weight );

	  if ( m_histoInfoSwitch->m_llpDesc ) {
	    h_LLPdVtx_descPt   [ireg][illp] ->Fill( m_truthVtx_descPt     ->at(i), weight );
	    h_LLPdVtx_descEta  [ireg][illp] ->Fill( m_truthVtx_descEta    ->at(i), weight );
	    h_LLPdVtx_descPhi  [ireg][illp] ->Fill( m_truthVtx_descPhi    ->at(i), weight );
	    h_LLPdVtx_descE    [ireg][illp] ->Fill( m_truthVtx_descE      ->at(i), weight );
	    h_LLPdVtx_descM    [ireg][illp] ->Fill( m_truthVtx_descM      ->at(i), weight );
	    
	    TVector3 pointvec ( m_truthVtx_x ->at(i) - m_pv_x, m_truthVtx_y ->at(i) - m_pv_y, m_truthVtx_z ->at(i) - m_pv_z );
	    // loop over descendants
	    for ( int llpd = 0; llpd != m_truthVtx_nDesc ->at(i); ++llpd ) {
	      double dphi_desc_pointvec = EJsHelper::deltaPhi( m_truthVtx_desc_phi ->at(i)[llpd], pointvec.Phi() );
	      double d0 = m_truthVtx_r ->at(i) * TMath::Sin( dphi_desc_pointvec );
	      double z0 = m_truthVtx_r ->at(i) / TMath::Tan( pointvec.Theta()   );
	      h_LLPdVtx_desc_pt  [ireg][illp] ->Fill( m_truthVtx_desc_pt  ->at(i)[llpd], weight );
	      h_LLPdVtx_desc_eta [ireg][illp] ->Fill( m_truthVtx_desc_eta ->at(i)[llpd], weight );
	      h_LLPdVtx_desc_phi [ireg][illp] ->Fill( m_truthVtx_desc_phi ->at(i)[llpd], weight );
	      h_LLPdVtx_desc_d0  [ireg][illp] ->Fill( d0,                                weight );
	      h_LLPdVtx_desc_z0  [ireg][illp] ->Fill( z0,                                weight );
	    } // end loop over descendants
	  } // end if llpDesc

	  if ( !doHists || m_histoInfoSwitch->m_abcdcutOnly ) continue;
	  
	  // do reconstruction efficiency studies
	  if ( m_histoInfoSwitch->m_llpRecoEff || m_histoInfoSwitch->m_llpvtxRecoEff ) {

	    // get matched vertices
	    bool hasRecoMatch_nonzero = false;
	    bool hasRecoMatch         = false;
	    std::vector<int> hasSgnlRecoMatch_nonzero ( m_nTypeSgnlDVs, 0 );
	    std::vector<int> hasSgnlRecoMatch         ( m_nTypeSgnlDVs, 0 );
	    if ( m_truthVtx_reco_n ->at(i) ) {
	      for ( size_t k = 0; k != m_truthVtx_reco_score ->at(i).size(); ++k ) {
		//if ( !m_secVtx_passMatVeto ->empty() )
		//  if ( !m_secVtx_passMatVeto ->at(m_truthVtx_reco_index ->at(i)[k]) ) continue;
		std::vector<int> reco_dv;
		getDVTypes( m_truthVtx_reco_index ->at(i)[k], reco_dv, base_dv, false, false, true, true, true );
		hasRecoMatch_nonzero = true;
		for ( size_t jj = 0; jj != reco_dv.size(); ++jj ) {
		  if ( !reco_dv[jj] ) continue;
		  hasSgnlRecoMatch_nonzero[jj] = 1;
		}
	    	if ( m_truthVtx_reco_score ->at(i)[k] < 0.5 ) continue;
	    	hasRecoMatch = true;
		for ( size_t kk = 0; kk != reco_dv.size(); ++kk ) {
		  if ( !reco_dv[kk] ) continue;
		  hasSgnlRecoMatch[kk] = 1;
		}  
	      }
	    }

	    // count reconstructed + vertexed descendants
	    int n_vtxDesc = 0;
	    std::vector<int> n_sgnlVtxDesc ( m_nTypeSgnlDVs, 0 );
	    TLorentzVector llp_recoDesc_sump4;
	    llp_recoDesc_sump4.SetPtEtaPhiM( 0, 0, 0, 0 );
	    TLorentzVector llp_vtxDesc_sump4;
	    llp_vtxDesc_sump4 .SetPtEtaPhiM( 0, 0, 0, 0 );
	    TLorentzVector llp_sgnlVtxDesc_p4;
	    llp_sgnlVtxDesc_p4.SetPtEtaPhiM( 0, 0, 0, 0 );
	    std::vector<TLorentzVector> llp_sgnlVtxDesc_sump4 ( m_nTypeSgnlDVs, llp_sgnlVtxDesc_p4 );
	    // loop over descendants
	    for ( int llpd = 0; llpd != m_truthVtx_nDesc ->at(i); ++llpd ) {
	      bool isVtxDesc  = false;
	      std::vector<int> isSgnlVtxDesc ( m_nTypeSgnlDVs, 0 );
	      // reco descendants
	      if ( m_truthVtx_desc_isReco ->at(i)[llpd] ) {
		TLorentzVector recoDesc_p4;
		recoDesc_p4.SetPtEtaPhiM( m_truthVtx_desc_pt  ->at(i)[llpd], m_truthVtx_desc_eta  ->at(i)[llpd],
					  m_truthVtx_desc_phi ->at(i)[llpd], m_truthVtx_desc_M    ->at(i)[llpd] );
		llp_recoDesc_sump4 += recoDesc_p4;
		// loop over matched vertices
		int  recoDescID = m_truthVtx_desc_recoID ->at(i)[llpd];
		for ( size_t k = 0; k != m_truthVtx_reco_index ->at(i).size(); ++k ) {
		  int dv_ix = m_truthVtx_reco_index ->at(i)[k];
		  //if ( !m_secVtx_passMatVeto ->empty() )
		  //  if ( !m_secVtx_passMatVeto ->at(dv_ix) ) continue;
		  std::vector<int> reco_dv;
		  getDVTypes( dv_ix, reco_dv, base_dv, false, false, true, true, true );
		  for ( size_t idvtrk = 0; idvtrk != m_secVtx_trk_ID ->at(dv_ix).size(); ++idvtrk )
		    if ( m_secVtx_trk_ID ->at(dv_ix)[idvtrk] == recoDescID ) {
		      isVtxDesc = true;
		      for ( size_t kk = 0; kk != reco_dv.size(); ++kk )
			if ( reco_dv[kk] ) isSgnlVtxDesc[kk] = true;
		    }
		}
		if ( isVtxDesc ) {
		  TLorentzVector vtxDesc_p4;
		  vtxDesc_p4.SetPtEtaPhiM( m_truthVtx_desc_pt  ->at(i)[llpd], m_truthVtx_desc_eta  ->at(i)[llpd],
					   m_truthVtx_desc_phi ->at(i)[llpd], m_truthVtx_desc_M    ->at(i)[llpd] );
		  llp_vtxDesc_sump4 += vtxDesc_p4;
		  ++n_vtxDesc;
		}
		for ( size_t isv = 0; isv != isSgnlVtxDesc.size(); ++isv ) {
		  if ( isSgnlVtxDesc[isv] ) {
		    TLorentzVector sgnlVtxDesc_p4;
		    sgnlVtxDesc_p4.SetPtEtaPhiM( m_truthVtx_desc_pt  ->at(i)[llpd], m_truthVtx_desc_eta  ->at(i)[llpd],
						 m_truthVtx_desc_phi ->at(i)[llpd], m_truthVtx_desc_M    ->at(i)[llpd] );
		    llp_sgnlVtxDesc_sump4 [isv] += sgnlVtxDesc_p4;
		    ++n_sgnlVtxDesc [isv];
		  }
		}
	      }
	    }
	    float fracRecoDesc  = m_truthVtx_nRecoDesc ->at(i) / float( m_truthVtx_nDesc ->at(i) );
	    float fracRecoDescM = llp_recoDesc_sump4.M()       / float( m_truthVtx_descM ->at(i) );
	    float fracVtxDesc   = n_vtxDesc                    / float( m_truthVtx_nDesc ->at(i) );
	    float fracVtxDescM  = llp_vtxDesc_sump4 .M()       / float( m_truthVtx_descM ->at(i) );
	    std::vector<float> fracSgnlVtxDesc  ( m_nTypeSgnlDVs, 0 );
	    std::vector<float> fracSgnlVtxDescM ( m_nTypeSgnlDVs, 0 );
	    for ( size_t isvd = 0; isvd != m_nTypeSgnlDVs; ++isvd ) {
	      fracSgnlVtxDesc [isvd] = n_sgnlVtxDesc[isvd]              / float( m_truthVtx_nDesc ->at(i) );
	      fracSgnlVtxDescM[isvd] = llp_sgnlVtxDesc_sump4[isvd] .M() / float( m_truthVtx_descM ->at(i) );
	    }

	    // do tracking efficiency studies
	    // run with and without material map veto on inclusive studies

	    TVector3 truthPos ( m_truthVtx_x ->at(i), m_truthVtx_y ->at(i), m_truthVtx_z ->at(i) );
	    
	    // reconstructible LLP decays
	    if ( m_truthVtx_isRecoble ->at(i) ) {
	      h_recobleLLPdVtx_x               [ireg][illp] ->Fill( m_truthVtx_x         ->at(i), weight );
	      h_recobleLLPdVtx_y               [ireg][illp] ->Fill( m_truthVtx_y         ->at(i), weight );
	      h_recobleLLPdVtx_z               [ireg][illp] ->Fill( m_truthVtx_z         ->at(i), weight );
	      h_recobleLLPdVtx_r               [ireg][illp] ->Fill( m_truthVtx_r         ->at(i), weight );
	      h_recobleLLPdVtx_pt              [ireg][illp] ->Fill( m_truthVtx_pt        ->at(i), weight );
	      h_recobleLLPdVtx_eta             [ireg][illp] ->Fill( m_truthVtx_eta       ->at(i), weight );
	      h_recobleLLPdVtx_phi             [ireg][illp] ->Fill( m_truthVtx_phi       ->at(i), weight );
	      h_recobleLLPdVtx_avgMu           [ireg][illp] ->Fill( m_averageMu,                  weight );
	      h_recobleLLPdVtx_descM           [ireg][illp] ->Fill( m_truthVtx_descM     ->at(i), weight );
	      h_recobleLLPdVtx_nDesc           [ireg][illp] ->Fill( m_truthVtx_nDesc     ->at(i), weight );
	      h_recobleLLPdVtx_nRecoDesc       [ireg][illp] ->Fill( m_truthVtx_nRecoDesc ->at(i), weight );
	      h_recobleLLPdVtx_nSelDesc        [ireg][illp] ->Fill( m_truthVtx_nSelDesc  ->at(i), weight );
	      h_recobleLLPdVtx_nDesc_r         [ireg][illp] ->Fill( m_truthVtx_r ->at(i), m_truthVtx_nDesc     ->at(i), weight );
	      h_recobleLLPdVtx_nDesc_z         [ireg][illp] ->Fill( m_truthVtx_z ->at(i), m_truthVtx_nDesc     ->at(i), weight );
	      h_recobleLLPdVtx_descM_r         [ireg][illp] ->Fill( m_truthVtx_r ->at(i), m_truthVtx_descM     ->at(i), weight );
	      h_recobleLLPdVtx_descM_z         [ireg][illp] ->Fill( m_truthVtx_z ->at(i), m_truthVtx_descM     ->at(i), weight );
	      h_recobleLLPdVtx_nRecoDesc_r     [ireg][illp] ->Fill( m_truthVtx_r ->at(i), m_truthVtx_nRecoDesc ->at(i), weight );
	      h_recobleLLPdVtx_nRecoDesc_z     [ireg][illp] ->Fill( m_truthVtx_z ->at(i), m_truthVtx_nRecoDesc ->at(i), weight );
	      h_recobleLLPdVtx_recoDescM_r     [ireg][illp] ->Fill( m_truthVtx_r ->at(i), llp_recoDesc_sump4.M(),       weight );
	      h_recobleLLPdVtx_recoDescM_z     [ireg][illp] ->Fill( m_truthVtx_z ->at(i), llp_recoDesc_sump4.M(),       weight );
	      h_recobleLLPdVtx_nVtxDesc_r      [ireg][illp] ->Fill( m_truthVtx_r ->at(i), n_vtxDesc,                    weight );
	      h_recobleLLPdVtx_nVtxDesc_z      [ireg][illp] ->Fill( m_truthVtx_z ->at(i), n_vtxDesc,                    weight );
	      h_recobleLLPdVtx_vtxDescM_r      [ireg][illp] ->Fill( m_truthVtx_r ->at(i), llp_vtxDesc_sump4 .M(),       weight );
	      h_recobleLLPdVtx_vtxDescM_z      [ireg][illp] ->Fill( m_truthVtx_z ->at(i), llp_vtxDesc_sump4 .M(),       weight );
	      h_recobleLLPdVtx_fracRecoDesc_r  [ireg][illp] ->Fill( m_truthVtx_r ->at(i), fracRecoDesc,                 weight );
	      h_recobleLLPdVtx_fracRecoDesc_z  [ireg][illp] ->Fill( m_truthVtx_z ->at(i), fracRecoDesc,                 weight );
	      h_recobleLLPdVtx_fracRecoDescM_r [ireg][illp] ->Fill( m_truthVtx_r ->at(i), fracRecoDescM,                weight );
	      h_recobleLLPdVtx_fracRecoDescM_z [ireg][illp] ->Fill( m_truthVtx_z ->at(i), fracRecoDescM,                weight );
	      h_recobleLLPdVtx_fracVtxDesc_r   [ireg][illp] ->Fill( m_truthVtx_r ->at(i), fracVtxDesc,                  weight );
	      h_recobleLLPdVtx_fracVtxDesc_z   [ireg][illp] ->Fill( m_truthVtx_z ->at(i), fracVtxDesc,                  weight );
	      h_recobleLLPdVtx_fracVtxDescM_r  [ireg][illp] ->Fill( m_truthVtx_r ->at(i), fracVtxDescM,                 weight );
	      h_recobleLLPdVtx_fracVtxDescM_z  [ireg][illp] ->Fill( m_truthVtx_z ->at(i), fracVtxDescM,                 weight );
	      // matched reconstructible LLP decays
	      if ( hasRecoMatch_nonzero )
		for ( size_t j = 0; j != m_truthVtx_reco_score ->at(i).size(); ++j )
		  h_recoMatchLLPdVtx_score   [ireg][illp] ->Fill( m_truthVtx_reco_score ->at(i)[j], weight );
	      if ( hasRecoMatch ) {
		h_recoMatchLLPdVtx_x         [ireg][illp] ->Fill( m_truthVtx_x              ->at(i), weight );
		h_recoMatchLLPdVtx_y         [ireg][illp] ->Fill( m_truthVtx_y              ->at(i), weight );
		h_recoMatchLLPdVtx_z         [ireg][illp] ->Fill( m_truthVtx_z              ->at(i), weight );
		h_recoMatchLLPdVtx_r         [ireg][illp] ->Fill( m_truthVtx_r              ->at(i), weight );
		h_recoMatchLLPdVtx_pt        [ireg][illp] ->Fill( m_truthVtx_pt             ->at(i), weight );
		h_recoMatchLLPdVtx_eta       [ireg][illp] ->Fill( m_truthVtx_eta            ->at(i), weight );
		h_recoMatchLLPdVtx_phi       [ireg][illp] ->Fill( m_truthVtx_phi            ->at(i), weight );
		h_recoMatchLLPdVtx_avgMu     [ireg][illp] ->Fill( m_averageMu,                       weight );
		h_recoMatchLLPdVtx_descM     [ireg][illp] ->Fill( m_truthVtx_descM          ->at(i), weight );
		h_recoMatchLLPdVtx_nDesc     [ireg][illp] ->Fill( m_truthVtx_nDesc          ->at(i), weight );
		h_recoMatchLLPdVtx_nRecoDesc [ireg][illp] ->Fill( m_truthVtx_nRecoDesc      ->at(i), weight );
		h_recoMatchLLPdVtx_nSelDesc  [ireg][illp] ->Fill( m_truthVtx_nSelDesc       ->at(i), weight );
		for ( size_t j = 0; j != m_truthVtx_reco_x ->at(i).size(); ++j ) {
		  TVector3 recoPos  ( m_truthVtx_reco_x ->at(i)[j], m_truthVtx_reco_y ->at(i)[j], m_truthVtx_reco_z ->at(i)[j] );
		  float resid_phi    = recoPos.Phi() - truthPos.Phi();
		  float resid_x      = m_truthVtx_reco_x       ->at(i)[j] - m_truthVtx_x ->at(i);
		  float resid_y      = m_truthVtx_reco_y       ->at(i)[j] - m_truthVtx_y ->at(i);
		  float resid_z      = m_truthVtx_reco_z       ->at(i)[j] - m_truthVtx_z ->at(i);
		  float resid_r      = m_truthVtx_reco_r       ->at(i)[j] - m_truthVtx_r ->at(i);
		  int   reco_ntrk    = m_truthVtx_reco_ntrk    ->at(i)[j];
		  int   reco_nseltrk = m_truthVtx_reco_nseltrk ->at(i)[j];
		  h_recoMatchLLPdVtx_resid_x            [ireg][illp] ->Fill( resid_x, weight );
		  h_recoMatchLLPdVtx_resid_y            [ireg][illp] ->Fill( resid_y, weight );
		  h_recoMatchLLPdVtx_resid_z            [ireg][illp] ->Fill( resid_z, weight );
		  h_recoMatchLLPdVtx_resid_r            [ireg][illp] ->Fill( resid_r, weight );
		  h_recoMatchLLPdVtx_resid_rphi         [ireg][illp] ->Fill( resid_phi * m_truthVtx_r ->at(i), weight );
		  h_recoMatchLLPdVtx_resid_z_r          [ireg][illp] ->Fill( m_truthVtx_r ->at(i), resid_z, weight );
		  h_recoMatchLLPdVtx_resid_z_z          [ireg][illp] ->Fill( m_truthVtx_z ->at(i), resid_z, weight );
		  h_recoMatchLLPdVtx_resid_z_ntrk       [ireg][illp] ->Fill( reco_ntrk,            resid_z, weight );
		  h_recoMatchLLPdVtx_resid_z_nseltrk    [ireg][illp] ->Fill( reco_nseltrk,         resid_z, weight );
		  h_recoMatchLLPdVtx_resid_r_r          [ireg][illp] ->Fill( m_truthVtx_r ->at(i), resid_r, weight );
		  h_recoMatchLLPdVtx_resid_r_z          [ireg][illp] ->Fill( m_truthVtx_z ->at(i), resid_r, weight );
		  h_recoMatchLLPdVtx_resid_r_ntrk       [ireg][illp] ->Fill( reco_ntrk,            resid_r, weight );
		  h_recoMatchLLPdVtx_resid_r_nseltrk    [ireg][illp] ->Fill( reco_nseltrk,         resid_r, weight );
		  h_recoMatchLLPdVtx_resid_rphi_r       [ireg][illp] ->Fill( m_truthVtx_r ->at(i), resid_phi * m_truthVtx_r ->at(i), weight );
		  h_recoMatchLLPdVtx_resid_rphi_z       [ireg][illp] ->Fill( m_truthVtx_z ->at(i), resid_phi * m_truthVtx_r ->at(i), weight );
		  h_recoMatchLLPdVtx_resid_rphi_ntrk    [ireg][illp] ->Fill( reco_ntrk,            resid_phi * m_truthVtx_r ->at(i), weight );
		  h_recoMatchLLPdVtx_resid_rphi_nseltrk [ireg][illp] ->Fill( reco_nseltrk,         resid_phi * m_truthVtx_r ->at(i), weight );
		}
	      }
	    }
	    // reconstructed LLP decays
	    if ( m_truthVtx_nRecoDesc ->at(i) > 1 ) {
	      h_recoLLPdVtx_x             [ireg][illp] ->Fill( m_truthVtx_x         ->at(i), weight );
	      h_recoLLPdVtx_y             [ireg][illp] ->Fill( m_truthVtx_y         ->at(i), weight );
	      h_recoLLPdVtx_z             [ireg][illp] ->Fill( m_truthVtx_z         ->at(i), weight );
	      h_recoLLPdVtx_r             [ireg][illp] ->Fill( m_truthVtx_r         ->at(i), weight );
	      h_recoLLPdVtx_pt            [ireg][illp] ->Fill( m_truthVtx_pt        ->at(i), weight );
	      h_recoLLPdVtx_eta           [ireg][illp] ->Fill( m_truthVtx_eta       ->at(i), weight );
	      h_recoLLPdVtx_phi           [ireg][illp] ->Fill( m_truthVtx_phi       ->at(i), weight );
	      h_recoLLPdVtx_avgMu         [ireg][illp] ->Fill( m_averageMu,                  weight );
	      h_recoLLPdVtx_descM         [ireg][illp] ->Fill( m_truthVtx_descM     ->at(i), weight );
	      h_recoLLPdVtx_nDesc         [ireg][illp] ->Fill( m_truthVtx_nDesc     ->at(i), weight );
	      h_recoLLPdVtx_nRecoDesc     [ireg][illp] ->Fill( m_truthVtx_nRecoDesc ->at(i), weight );
	      h_recoLLPdVtx_nSelDesc      [ireg][illp] ->Fill( m_truthVtx_nSelDesc  ->at(i), weight );
	    }
	    // selected LLP decays
	    if ( m_truthVtx_nSelDesc  ->at(i) > 1 ) {
	      h_selLLPdVtx_x              [ireg][illp] ->Fill( m_truthVtx_x         ->at(i), weight );
	      h_selLLPdVtx_y              [ireg][illp] ->Fill( m_truthVtx_y         ->at(i), weight );
	      h_selLLPdVtx_z              [ireg][illp] ->Fill( m_truthVtx_z         ->at(i), weight );
	      h_selLLPdVtx_r              [ireg][illp] ->Fill( m_truthVtx_r         ->at(i), weight );
	      h_selLLPdVtx_pt             [ireg][illp] ->Fill( m_truthVtx_pt        ->at(i), weight );
	      h_selLLPdVtx_eta            [ireg][illp] ->Fill( m_truthVtx_eta       ->at(i), weight );
	      h_selLLPdVtx_phi            [ireg][illp] ->Fill( m_truthVtx_phi       ->at(i), weight );
	      h_selLLPdVtx_avgMu          [ireg][illp] ->Fill( m_averageMu,                  weight );
	      h_selLLPdVtx_descM          [ireg][illp] ->Fill( m_truthVtx_descM     ->at(i), weight );
	      h_selLLPdVtx_nDesc          [ireg][illp] ->Fill( m_truthVtx_nDesc     ->at(i), weight );
	      h_selLLPdVtx_nRecoDesc      [ireg][illp] ->Fill( m_truthVtx_nRecoDesc ->at(i), weight );
	      h_selLLPdVtx_nSelDesc       [ireg][illp] ->Fill( m_truthVtx_nSelDesc  ->at(i), weight );
	    }

	    // cut on analysis fiducial volume for signal vertex efficiency
	    if ( m_truthVtx_r ->at(i) > 300 || fabs( m_truthVtx_z ->at(i) ) > 300 ) continue;

	    // reconstructible LLP decays in analysis fiducial volume
	    if ( m_truthVtx_isRecoble ->at(i) ) {
	      h_fiducLLPdVtx_x                   [ireg][illp]    ->Fill( m_truthVtx_x         ->at(i), weight );
	      h_fiducLLPdVtx_y                   [ireg][illp]    ->Fill( m_truthVtx_y         ->at(i), weight );
	      h_fiducLLPdVtx_z                   [ireg][illp]    ->Fill( m_truthVtx_z         ->at(i), weight );
	      h_fiducLLPdVtx_r                   [ireg][illp]    ->Fill( m_truthVtx_r         ->at(i), weight );
	      h_fiducLLPdVtx_pt                  [ireg][illp]    ->Fill( m_truthVtx_pt        ->at(i), weight );
	      h_fiducLLPdVtx_eta                 [ireg][illp]    ->Fill( m_truthVtx_eta       ->at(i), weight );
	      h_fiducLLPdVtx_phi                 [ireg][illp]    ->Fill( m_truthVtx_phi       ->at(i), weight );
	      h_fiducLLPdVtx_avgMu               [ireg][illp]    ->Fill( m_averageMu,                  weight );
	      h_fiducLLPdVtx_descM               [ireg][illp]    ->Fill( m_truthVtx_descM     ->at(i), weight );
	      h_fiducLLPdVtx_nDesc               [ireg][illp]    ->Fill( m_truthVtx_nDesc     ->at(i), weight );
	      h_fiducLLPdVtx_nRecoDesc           [ireg][illp]    ->Fill( m_truthVtx_nRecoDesc ->at(i), weight );
	      h_fiducLLPdVtx_nSelDesc            [ireg][illp]    ->Fill( m_truthVtx_nSelDesc  ->at(i), weight );
	      h_fiducLLPdVtx_nDesc_r             [ireg][illp]    ->Fill( m_truthVtx_r ->at(i), m_truthVtx_nDesc     ->at(i), weight );
	      h_fiducLLPdVtx_nDesc_z             [ireg][illp]    ->Fill( m_truthVtx_z ->at(i), m_truthVtx_nDesc     ->at(i), weight );
	      h_fiducLLPdVtx_descM_r             [ireg][illp]    ->Fill( m_truthVtx_r ->at(i), m_truthVtx_descM     ->at(i), weight );
	      h_fiducLLPdVtx_descM_z             [ireg][illp]    ->Fill( m_truthVtx_z ->at(i), m_truthVtx_descM     ->at(i), weight );
	      h_fiducLLPdVtx_nRecoDesc_r         [ireg][illp]    ->Fill( m_truthVtx_r ->at(i), m_truthVtx_nRecoDesc ->at(i), weight );
	      h_fiducLLPdVtx_nRecoDesc_z         [ireg][illp]    ->Fill( m_truthVtx_z ->at(i), m_truthVtx_nRecoDesc ->at(i), weight );
	      h_fiducLLPdVtx_recoDescM_r         [ireg][illp]    ->Fill( m_truthVtx_r ->at(i), llp_recoDesc_sump4.M(),       weight );
	      h_fiducLLPdVtx_recoDescM_z         [ireg][illp]    ->Fill( m_truthVtx_z ->at(i), llp_recoDesc_sump4.M(),       weight );
	      h_fiducLLPdVtx_fracRecoDesc_r      [ireg][illp]    ->Fill( m_truthVtx_r ->at(i), fracRecoDesc,                 weight );
	      h_fiducLLPdVtx_fracRecoDesc_z      [ireg][illp]    ->Fill( m_truthVtx_z ->at(i), fracRecoDesc,                 weight );
	      h_fiducLLPdVtx_fracRecoDescM_r     [ireg][illp]    ->Fill( m_truthVtx_r ->at(i), fracRecoDescM,                weight );
	      h_fiducLLPdVtx_fracRecoDescM_z     [ireg][illp]    ->Fill( m_truthVtx_z ->at(i), fracRecoDescM,                weight );
	      for ( size_t k = 0; k != n_sgnlVtxDesc.size() + 1; ++k ) {
		int    n_vdesc      = 0;
		double vdesc_m      = 0;
		double frac_vdesc   = 0;
		double frac_vdesc_m = 0;
		if ( k == 0 ) {
		  n_vdesc      = n_vtxDesc;
		  vdesc_m      = llp_vtxDesc_sump4.M();
		  frac_vdesc   = fracVtxDesc;
		  frac_vdesc_m = fracVtxDescM;
		}
		else {
		  n_vdesc      = n_sgnlVtxDesc        [k-1];
		  vdesc_m      = llp_sgnlVtxDesc_sump4[k-1].M();
		  frac_vdesc   = fracSgnlVtxDesc      [k-1];
		  frac_vdesc_m = fracSgnlVtxDescM     [k-1];
		}
		h_fiducLLPdVtx_nVtxDesc_r        [ireg][illp][k] ->Fill( m_truthVtx_r ->at(i), n_vdesc,                      weight );
		h_fiducLLPdVtx_nVtxDesc_z        [ireg][illp][k] ->Fill( m_truthVtx_z ->at(i), n_vdesc,                      weight );
		h_fiducLLPdVtx_vtxDescM_r        [ireg][illp][k] ->Fill( m_truthVtx_r ->at(i), vdesc_m,                      weight );
		h_fiducLLPdVtx_vtxDescM_z        [ireg][illp][k] ->Fill( m_truthVtx_z ->at(i), vdesc_m,                      weight );
		h_fiducLLPdVtx_fracVtxDesc_r     [ireg][illp][k] ->Fill( m_truthVtx_r ->at(i), frac_vdesc,                   weight );
		h_fiducLLPdVtx_fracVtxDesc_z     [ireg][illp][k] ->Fill( m_truthVtx_z ->at(i), frac_vdesc,                   weight );
		h_fiducLLPdVtx_fracVtxDescM_r    [ireg][illp][k] ->Fill( m_truthVtx_r ->at(i), frac_vdesc_m,                 weight );
		h_fiducLLPdVtx_fracVtxDescM_z    [ireg][illp][k] ->Fill( m_truthVtx_z ->at(i), frac_vdesc_m,                 weight );
	      }
	      for ( size_t k = 0; k != hasSgnlRecoMatch.size(); ++k ) {
		if ( !hasSgnlRecoMatch_nonzero[k] ) continue;
		for ( size_t j = 0; j != m_truthVtx_reco_score ->at(i).size(); ++j )
		  h_sgnlRecoMatchLLPdVtx_score   [ireg][illp][k] ->Fill( m_truthVtx_reco_score ->at(i)[j], weight );
		if ( !hasSgnlRecoMatch[k] ) continue;
		h_sgnlRecoMatchLLPdVtx_x         [ireg][illp][k] ->Fill( m_truthVtx_x         ->at(i), weight );
		h_sgnlRecoMatchLLPdVtx_y         [ireg][illp][k] ->Fill( m_truthVtx_y         ->at(i), weight );
		h_sgnlRecoMatchLLPdVtx_z         [ireg][illp][k] ->Fill( m_truthVtx_z         ->at(i), weight );
		h_sgnlRecoMatchLLPdVtx_r         [ireg][illp][k] ->Fill( m_truthVtx_r         ->at(i), weight );
		h_sgnlRecoMatchLLPdVtx_pt        [ireg][illp][k] ->Fill( m_truthVtx_pt        ->at(i), weight );
		h_sgnlRecoMatchLLPdVtx_eta       [ireg][illp][k] ->Fill( m_truthVtx_eta       ->at(i), weight );
		h_sgnlRecoMatchLLPdVtx_phi       [ireg][illp][k] ->Fill( m_truthVtx_phi       ->at(i), weight );
		h_sgnlRecoMatchLLPdVtx_avgMu     [ireg][illp][k] ->Fill( m_averageMu,                  weight );
		h_sgnlRecoMatchLLPdVtx_descM     [ireg][illp][k] ->Fill( m_truthVtx_descM     ->at(i), weight );
		h_sgnlRecoMatchLLPdVtx_nDesc     [ireg][illp][k] ->Fill( m_truthVtx_nDesc     ->at(i), weight );
		h_sgnlRecoMatchLLPdVtx_nRecoDesc [ireg][illp][k] ->Fill( m_truthVtx_nRecoDesc ->at(i), weight );
		h_sgnlRecoMatchLLPdVtx_nSelDesc  [ireg][illp][k] ->Fill( m_truthVtx_nSelDesc  ->at(i), weight );
		for ( size_t j = 0; j != m_truthVtx_reco_x ->at(i).size(); ++j ) {
		  TVector3 recoPos  ( m_truthVtx_reco_x ->at(i)[j], m_truthVtx_reco_y ->at(i)[j], m_truthVtx_reco_z ->at(i)[j] );
		  float resid_phi    = recoPos.Phi() - truthPos.Phi();
		  float resid_x      = m_truthVtx_reco_x       ->at(i)[j] - m_truthVtx_x ->at(i);
		  float resid_y      = m_truthVtx_reco_y       ->at(i)[j] - m_truthVtx_y ->at(i);
		  float resid_z      = m_truthVtx_reco_z       ->at(i)[j] - m_truthVtx_z ->at(i);
		  float resid_r      = m_truthVtx_reco_r       ->at(i)[j] - m_truthVtx_r ->at(i);
		  int   reco_ntrk    = m_truthVtx_reco_ntrk    ->at(i)[j];
		  int   reco_nseltrk = m_truthVtx_reco_nseltrk ->at(i)[j];
		  h_sgnlRecoMatchLLPdVtx_resid_x            [ireg][illp][k] ->Fill( resid_x, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_y            [ireg][illp][k] ->Fill( resid_y, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_z            [ireg][illp][k] ->Fill( resid_z, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_r            [ireg][illp][k] ->Fill( resid_r, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_rphi         [ireg][illp][k] ->Fill( resid_phi * m_truthVtx_r ->at(i), weight );
		  h_sgnlRecoMatchLLPdVtx_resid_z_r          [ireg][illp][k] ->Fill( m_truthVtx_r ->at(i), resid_z, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_z_z          [ireg][illp][k] ->Fill( m_truthVtx_z ->at(i), resid_z, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_z_ntrk       [ireg][illp][k] ->Fill( reco_ntrk,            resid_z, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_z_nseltrk    [ireg][illp][k] ->Fill( reco_nseltrk,         resid_z, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_r_r          [ireg][illp][k] ->Fill( m_truthVtx_r ->at(i), resid_r, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_r_z          [ireg][illp][k] ->Fill( m_truthVtx_z ->at(i), resid_r, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_r_ntrk       [ireg][illp][k] ->Fill( reco_ntrk,            resid_r, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_r_nseltrk    [ireg][illp][k] ->Fill( reco_nseltrk,         resid_r, weight );
		  h_sgnlRecoMatchLLPdVtx_resid_rphi_r       [ireg][illp][k] ->Fill( m_truthVtx_r ->at(i), resid_phi * m_truthVtx_r ->at(i), weight );
		  h_sgnlRecoMatchLLPdVtx_resid_rphi_z       [ireg][illp][k] ->Fill( m_truthVtx_z ->at(i), resid_phi * m_truthVtx_r ->at(i), weight );
		  h_sgnlRecoMatchLLPdVtx_resid_rphi_ntrk    [ireg][illp][k] ->Fill( reco_ntrk,            resid_phi * m_truthVtx_r ->at(i), weight );
		  h_sgnlRecoMatchLLPdVtx_resid_rphi_nseltrk [ireg][illp][k] ->Fill( reco_nseltrk,         resid_phi * m_truthVtx_r ->at(i), weight );
		}
	      }
	    }
	    // reconstructed LLP decays
	    if ( m_truthVtx_nRecoDesc ->at(i) > 1 ) {
	      h_recoFiducLLPdVtx_x        [ireg][illp] ->Fill( m_truthVtx_x         ->at(i), weight );
	      h_recoFiducLLPdVtx_y        [ireg][illp] ->Fill( m_truthVtx_y         ->at(i), weight );
	      h_recoFiducLLPdVtx_z        [ireg][illp] ->Fill( m_truthVtx_z         ->at(i), weight );
	      h_recoFiducLLPdVtx_r        [ireg][illp] ->Fill( m_truthVtx_r         ->at(i), weight );
	      h_recoFiducLLPdVtx_pt       [ireg][illp] ->Fill( m_truthVtx_pt        ->at(i), weight );
	      h_recoFiducLLPdVtx_eta      [ireg][illp] ->Fill( m_truthVtx_eta       ->at(i), weight );
	      h_recoFiducLLPdVtx_phi      [ireg][illp] ->Fill( m_truthVtx_phi       ->at(i), weight );
	      h_recoFiducLLPdVtx_avgMu    [ireg][illp] ->Fill( m_averageMu,                  weight );
	      h_recoFiducLLPdVtx_descM    [ireg][illp] ->Fill( m_truthVtx_descM     ->at(i), weight );
	      h_recoFiducLLPdVtx_nDesc    [ireg][illp] ->Fill( m_truthVtx_nDesc     ->at(i), weight );
	      h_recoFiducLLPdVtx_nRecoDesc[ireg][illp] ->Fill( m_truthVtx_nRecoDesc ->at(i), weight );
	      h_recoFiducLLPdVtx_nSelDesc [ireg][illp] ->Fill( m_truthVtx_nSelDesc  ->at(i), weight );
	    }
	    // selected LLP decays
	    if ( m_truthVtx_nSelDesc  ->at(i) > 1 ) {
	      h_selFiducLLPdVtx_x         [ireg][illp] ->Fill( m_truthVtx_x         ->at(i), weight );
	      h_selFiducLLPdVtx_y         [ireg][illp] ->Fill( m_truthVtx_y         ->at(i), weight );
	      h_selFiducLLPdVtx_z         [ireg][illp] ->Fill( m_truthVtx_z         ->at(i), weight );
	      h_selFiducLLPdVtx_r         [ireg][illp] ->Fill( m_truthVtx_r         ->at(i), weight );
	      h_selFiducLLPdVtx_pt        [ireg][illp] ->Fill( m_truthVtx_pt        ->at(i), weight );
	      h_selFiducLLPdVtx_eta       [ireg][illp] ->Fill( m_truthVtx_eta       ->at(i), weight );
	      h_selFiducLLPdVtx_phi       [ireg][illp] ->Fill( m_truthVtx_phi       ->at(i), weight );
	      h_selFiducLLPdVtx_avgMu     [ireg][illp] ->Fill( m_averageMu,                  weight );
	      h_selFiducLLPdVtx_descM     [ireg][illp] ->Fill( m_truthVtx_descM     ->at(i), weight );
	      h_selFiducLLPdVtx_nDesc     [ireg][illp] ->Fill( m_truthVtx_nDesc     ->at(i), weight );
	      h_selFiducLLPdVtx_nRecoDesc [ireg][illp] ->Fill( m_truthVtx_nRecoDesc ->at(i), weight );
	      h_selFiducLLPdVtx_nSelDesc  [ireg][illp] ->Fill( m_truthVtx_nSelDesc  ->at(i), weight );
	    }
	    
	  } // end efficiency studies
	  
	} // end loop over llp types

      } // end loop over truth vertices

      // fill LLP count histograms
      for ( size_t illp = 0; illp != n_LLP.size(); ++illp ) {
	h_LLPdVtx_n [ireg][illp] ->Fill( n_LLP[illp], weight );

	// fill NDV vector
	if ( m_histoInfoSwitch->m_truthOnly )
	  NDV .push_back( n_LLP[illp] );
      }
      
    } // end if mc



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
    // set vectors of n-dv sum-p4
    TLorentzVector dvp4sum;
    dvp4sum.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<TLorentzVector> dv_p4_sum     ( m_nTypeDVs, dvp4sum );
    std::vector<double>         dv_p4_sumPt   ( m_nTypeDVs, 0       );
    std::vector<double>         dv_p4_sumHt   ( m_nTypeDVs, 0       );
    std::vector<double>         dv_p4_sumH    ( m_nTypeDVs, 0       );
    std::vector<double>         dv_p4_sumMass ( m_nTypeDVs, 0       );
    std::vector<int>            dv_p4_sumNtrk ( m_nTypeDVs, 0       );

    if ( !m_histoInfoSwitch->m_truthOnly ) {
      if ( m_debug ) Info( "EJsHistogramManager::execute()", "doing DV histos" );
    
      // loop over vertices
      for ( int i = 0; i != m_secVtx_n; ++i ) {

	// set kinematic variables based on base DV type
	float secVtx_pt              = 0;
	float secVtx_eta             = 0;
	float secVtx_phi             = 0;
	float secVtx_mass            = 0;
	float secVtx_massNA          = 0;
	float secVtx_dir             = 0;
	float secVtx_h               = 0;
	float secVtx_ht              = 0;
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
	if      ( base_dv.type == EJsHelper::BARE     ) {
	  secVtx_pt       = m_secVtx_pt_bare         ->at(i);
	  secVtx_eta      = m_secVtx_eta_bare        ->at(i);
	  secVtx_phi      = m_secVtx_phi_bare        ->at(i);
	  secVtx_mass     = m_secVtx_mass_bare       ->at(i);
	  secVtx_massNA   = m_secVtx_massNA_bare     ->at(i);
	  secVtx_dir      = m_secVtx_direction_bare  ->at(i);
	  secVtx_h        = m_secVtx_H_bare          ->at(i);
	  secVtx_ht       = m_secVtx_Ht_bare         ->at(i);
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
	  secVtx_h        = m_secVtx_H_clean         ->at(i);
	  secVtx_ht       = m_secVtx_Ht_clean        ->at(i);
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
	  secVtx_h        = m_secVtx_H               ->at(i);
	  secVtx_ht       = m_secVtx_Ht              ->at(i);
	  secVtx_minOpAng = m_secVtx_minOpAng        ->at(i);
	  secVtx_maxOpAng = m_secVtx_maxOpAng        ->at(i);
	  secVtx_mind0    = m_secVtx_mind0           ->at(i);
	  secVtx_maxd0    = m_secVtx_maxd0           ->at(i);
	  secVtx_ntrk     = m_secVtx_ntrk_filt       ->at(i);
	}
	// else if ( base_dv.type == EJsHelper::TRIMMED ) {...}
	// --> will have to loop over tracks and re-calculate kinematic variables using only trimmed tracks...

	// get secondary vertex four-momentum + position
	TLorentzVector secVtx_p4;
	secVtx_p4.SetPtEtaPhiM( secVtx_pt, secVtx_eta, secVtx_phi, secVtx_mass );
	const TVector3 secVtx_pos( m_secVtx_x ->at(i), m_secVtx_y ->at(i), m_secVtx_z ->at(i) );
      
	// set vector of DV types
	std::vector<int> DV;
	getDVTypes( i, DV, base_dv, m_doComboDVs );
	// --> add "good" vertices --> this will eventually be our final version to use for analysis
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

	  // total DV count
	  if ( m_histoInfoSwitch->m_cutflow || m_histoInfoSwitch->m_abcdcutOnly )
	    h_evt_count_DV [ireg][idv] ->Fill( int(0), weight );

	  // sum p4 for all DVs in event
	  dv_p4_sum     [idv] += secVtx_p4;
	  dv_p4_sumPt   [idv] += secVtx_pt;
	  dv_p4_sumHt   [idv] += secVtx_ht;
	  dv_p4_sumH    [idv] += secVtx_h;
	  dv_p4_sumMass [idv] += secVtx_mass;
	  dv_p4_sumNtrk [idv] += secVtx_ntrk;

	  if ( !doHists || m_histoInfoSwitch->m_abcdcutOnly ) continue;

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
	  h_DV_H         [ireg][idv] ->Fill( secVtx_h,              weight );
	  h_DV_H_s       [ireg][idv] ->Fill( secVtx_h,              weight );
	  h_DV_H_xs      [ireg][idv] ->Fill( secVtx_h,              weight );
	  h_DV_Ht        [ireg][idv] ->Fill( secVtx_ht,             weight );
	  h_DV_Ht_s      [ireg][idv] ->Fill( secVtx_ht,             weight );
	  h_DV_Ht_xs     [ireg][idv] ->Fill( secVtx_ht,             weight );
	  h_DV_minOpAng  [ireg][idv] ->Fill( secVtx_minOpAng,       weight ); // wrt SV
	  h_DV_maxOpAng  [ireg][idv] ->Fill( secVtx_maxOpAng,       weight );
	  h_DV_chi2      [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), weight );
	  h_DV_chi2_s    [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), weight );
	  h_DV_ntrk      [ireg][idv] ->Fill( secVtx_ntrk,           weight );
	  // --> look at mass_selected (is this the same as non-associated? check), mass_LRT
	  // --> --> need to calculate sumP4 using only tracks of interest

	  // 2d plots
	  if ( m_histoInfoSwitch->m_vtx2D ) {
	    h_DV_y_x         [ireg][idv] ->Fill( m_secVtx_x    ->at(i), m_secVtx_y    ->at(i), weight );
	    h_DV_z_r         [ireg][idv] ->Fill( m_secVtx_r    ->at(i), m_secVtx_z    ->at(i), weight );
	    h_DV_r_z         [ireg][idv] ->Fill( m_secVtx_z    ->at(i), m_secVtx_r    ->at(i), weight );
	    h_DV_r_phi       [ireg][idv] ->Fill( secVtx_pos     .Phi(), m_secVtx_r    ->at(i), weight );
	    h_DV_rzphi       [ireg][idv] ->Fill( m_secVtx_r    ->at(i), m_secVtx_z    ->at(i), secVtx_pos .Phi(), weight );
	    h_DV_mass_r      [ireg][idv] ->Fill( m_secVtx_r    ->at(i), m_secVtx_mass ->at(i), weight );
	    h_DV_z_chi2      [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_z    ->at(i), weight );
	    h_DV_r_chi2      [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_r    ->at(i), weight );
	    h_DV_mass_chi2   [ireg][idv] ->Fill( m_secVtx_chi2 ->at(i), m_secVtx_mass ->at(i), weight );
	    h_DV_y_x_s       [ireg][idv] ->Fill( m_secVtx_x    ->at(i), m_secVtx_y    ->at(i), weight );
	    h_DV_z_r_s       [ireg][idv] ->Fill( m_secVtx_r    ->at(i), m_secVtx_z    ->at(i), weight );
	    h_DV_r_z_s       [ireg][idv] ->Fill( m_secVtx_z    ->at(i), m_secVtx_r    ->at(i), weight );
	    h_DV_r_phi_s     [ireg][idv] ->Fill( secVtx_pos     .Phi(), m_secVtx_r    ->at(i), weight );
	    h_DV_rzphi_s     [ireg][idv] ->Fill( m_secVtx_r    ->at(i), m_secVtx_z    ->at(i), secVtx_pos .Phi(), weight );
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

	  int secVtx_ntrk_final = 0;
	  int secVtx_ntrk_sel   = 0;
	  int secVtx_ntrk_assoc = 0;
	  int secVtx_ntrk_lrt   = 0;
	  // loop over vertex tracks
	  for ( int j = 0; j != m_secVtx_ntrk ->at(i); ++j ) {
	    if ( base_dv.type == EJsHelper::CLEAN    && !m_secVtx_trk_isClean ->at(i)[j] ) continue;
	    if ( base_dv.type == EJsHelper::FILTERED && !m_secVtx_trk_isFilt  ->at(i)[j] ) continue;
	    // if ( base_dv.type == EJsHelper::TRIMMED && *track fails trimming cuts* ) continue;

	    int trkIx = m_secVtx_trk_index ->at(i)[j];
	  
	    if ( m_secVtx_trk_isFinal ->at(i)[j]         ) ++secVtx_ntrk_final;
	    if ( m_secVtx_trk_isSel   ->at(i)[j]         ) ++secVtx_ntrk_sel;
	    if ( m_secVtx_trk_isAssoc ->at(i)[j]         ) ++secVtx_ntrk_assoc;
	    if ( m_trk_isLRT          ->at(trkIx)        ) ++secVtx_ntrk_lrt;

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

	    // sum vertex track parameters
	    secVtx_sumd0           += fabs(m_trk_d0           ->at(trkIx));
	    secVtx_sumz0           += fabs(m_trk_z0           ->at(trkIx));
	    secVtx_sumP            += fabs(m_trk_qOverP       ->at(trkIx) * 1000);
	    secVtx_sumd0_sv        += fabs(m_secVtx_trk_d0_sv ->at(i)[j]);
	    secVtx_sumz0_sv        += fabs(m_secVtx_trk_z0_sv ->at(i)[j]);
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
	    float fabsd0_sv = fabs( m_secVtx_trk_d0_sv ->at(i)[j] );
	    float fabsz0_sv = fabs( m_secVtx_trk_z0_sv ->at(i)[j] );
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
		h_DV_seltrk_d0       [ireg][idv] ->Fill( m_trk_d0             ->at(trkIx), weight );
		h_DV_seltrk_d0_xs    [ireg][idv] ->Fill( m_trk_d0             ->at(trkIx), weight );
	      }
	      // associated tracks
	      if ( m_secVtx_trk_isAssoc ->at(i)[j] ) {
		h_DV_assoctrk_d0      [ireg][idv] ->Fill( m_trk_d0            ->at(trkIx), weight );
		h_DV_assoctrk_eta     [ireg][idv] ->Fill( m_trk_eta           ->at(trkIx), weight );
		h_DV_assoctrk_phi     [ireg][idv] ->Fill( m_trk_phi           ->at(trkIx), weight );
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

	      h_DV_assoctrk_d0_phi        [ireg][idv] ->Fill( m_trk_phi           ->at(trkIx), m_trk_d0  ->at(trkIx),    weight );
	      h_DV_assoctrk_eta_phi       [ireg][idv] ->Fill( m_trk_phi           ->at(trkIx), m_trk_eta ->at(trkIx),    weight );
	      h_DV_assoctrk_phi_eta       [ireg][idv] ->Fill( m_trk_eta           ->at(trkIx), m_trk_phi ->at(trkIx),    weight );
	    }
	  
	  } // end loop over tracks

	  h_DV_ntrk_final [ireg][idv] ->Fill( secVtx_ntrk_final, weight );
	  h_DV_ntrk_sel   [ireg][idv] ->Fill( secVtx_ntrk_sel,   weight );
	  h_DV_ntrk_assoc [ireg][idv] ->Fill( secVtx_ntrk_assoc, weight );
	  h_DV_ntrk_lrt   [ireg][idv] ->Fill( secVtx_ntrk_lrt,   weight );

	  if ( m_histoInfoSwitch->m_vtxOverallTrk ) {
	    h_DV_sumd0           [ireg][idv] ->Fill( secVtx_sumd0,                   weight );
	    h_DV_sumz0           [ireg][idv] ->Fill( secVtx_sumz0,                   weight );
	    h_DV_sumP            [ireg][idv] ->Fill( secVtx_sumP,                    weight );
	    h_DV_sumd0_sv        [ireg][idv] ->Fill( secVtx_sumd0_sv,                weight );
	    h_DV_sumz0_sv        [ireg][idv] ->Fill( secVtx_sumz0_sv,                weight );
	    h_DV_sumP_sv         [ireg][idv] ->Fill( secVtx_sumP_sv,                 weight );
	    h_DV_sumsqrtd0       [ireg][idv] ->Fill( sqrt(secVtx_sumd0),             weight );
	    h_DV_sumsqrtz0       [ireg][idv] ->Fill( sqrt(secVtx_sumz0),             weight );
	    h_DV_sumsqrtP        [ireg][idv] ->Fill( sqrt(secVtx_sumP),              weight );
	    h_DV_sumsqrtd0_sv    [ireg][idv] ->Fill( sqrt(secVtx_sumd0_sv),          weight );
	    h_DV_sumsqrtz0_sv    [ireg][idv] ->Fill( sqrt(secVtx_sumz0_sv),          weight );
	    h_DV_sumsqrtP_sv     [ireg][idv] ->Fill( sqrt(secVtx_sumP_sv),           weight );
	    h_DV_mind0           [ireg][idv] ->Fill( secVtx_mind0,                   weight );
	    h_DV_minz0           [ireg][idv] ->Fill( secVtx_minz0,                   weight );
	    h_DV_mind0_s         [ireg][idv] ->Fill( secVtx_mind0,                   weight );
	    h_DV_minz0_s         [ireg][idv] ->Fill( secVtx_minz0,                   weight );
	    h_DV_minP            [ireg][idv] ->Fill( secVtx_minP,                    weight );
	    h_DV_mind0_sv        [ireg][idv] ->Fill( secVtx_mind0_sv,                weight );
	    h_DV_minz0_sv        [ireg][idv] ->Fill( secVtx_minz0_sv,                weight );
	    h_DV_minP_sv         [ireg][idv] ->Fill( secVtx_minP_sv,                 weight );
	    h_DV_minsqrtd0       [ireg][idv] ->Fill( sqrt(secVtx_mind0),             weight );
	    h_DV_minsqrtz0       [ireg][idv] ->Fill( sqrt(secVtx_minz0),             weight );
	    h_DV_minsqrtP        [ireg][idv] ->Fill( sqrt(secVtx_minP),              weight );
	    h_DV_minsqrtd0_sv    [ireg][idv] ->Fill( sqrt(secVtx_mind0_sv),          weight );
	    h_DV_minsqrtz0_sv    [ireg][idv] ->Fill( sqrt(secVtx_minz0_sv),          weight );
	    h_DV_minsqrtP_sv     [ireg][idv] ->Fill( sqrt(secVtx_minP_sv),           weight );
	    h_DV_maxd0           [ireg][idv] ->Fill( secVtx_maxd0,                   weight );
	    h_DV_maxz0           [ireg][idv] ->Fill( secVtx_maxz0,                   weight );
	    h_DV_maxP            [ireg][idv] ->Fill( secVtx_maxP,                    weight );
	    h_DV_maxd0_sv        [ireg][idv] ->Fill( secVtx_maxd0_sv,                weight );
	    h_DV_maxz0_sv        [ireg][idv] ->Fill( secVtx_maxz0_sv,                weight );
	    h_DV_maxP_sv         [ireg][idv] ->Fill( secVtx_maxP_sv,                 weight );
	    h_DV_maxsqrtd0       [ireg][idv] ->Fill( sqrt(secVtx_maxd0),             weight );
	    h_DV_maxsqrtz0       [ireg][idv] ->Fill( sqrt(secVtx_maxz0),             weight );
	    h_DV_maxsqrtP        [ireg][idv] ->Fill( sqrt(secVtx_maxP),              weight );
	    h_DV_maxsqrtd0_sv    [ireg][idv] ->Fill( sqrt(secVtx_maxd0_sv),          weight );
	    h_DV_maxsqrtz0_sv    [ireg][idv] ->Fill( sqrt(secVtx_maxz0_sv),          weight );
	    h_DV_maxsqrtP_sv     [ireg][idv] ->Fill( sqrt(secVtx_maxP_sv),           weight );
	    if ( m_histoInfoSwitch->m_vtx2D ) {
	      h_DV_mind0_r       [ireg][idv] ->Fill( m_secVtx_r ->at(i), secVtx_mind0, weight );
	      h_DV_minz0_z       [ireg][idv] ->Fill( m_secVtx_z ->at(i), secVtx_minz0, weight );
	      h_DV_mind0z0       [ireg][idv] ->Fill( secVtx_minz0,       secVtx_mind0, weight );
	      h_DV_mind0_r_s     [ireg][idv] ->Fill( m_secVtx_r ->at(i), secVtx_mind0, weight );
	      h_DV_minz0_z_s     [ireg][idv] ->Fill( m_secVtx_z ->at(i), secVtx_minz0, weight );
	      h_DV_mind0z0_s     [ireg][idv] ->Fill( secVtx_minz0,       secVtx_mind0, weight );
	    }
	  }
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
	    h_DV_minSqrterrd0_s  [ireg][idv] ->Fill( sqrt(sqrt(secVtx_minerrd0)),    weight );
	    h_DV_minSqrterrz0_s  [ireg][idv] ->Fill( sqrt(sqrt(secVtx_minerrz0)),    weight );
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

	    h_DV_minSqrterrd0_mind0   [ireg][idv] ->Fill( secVtx_mind0,                sqrt(sqrt(secVtx_minerrd0)), weight );
	    h_DV_minSqrterrz0_minz0   [ireg][idv] ->Fill( secVtx_minz0,                sqrt(sqrt(secVtx_minerrz0)), weight );
	    h_DV_minSqrterrd0z0       [ireg][idv] ->Fill( sqrt(sqrt(secVtx_minerrz0)), sqrt(sqrt(secVtx_minerrd0)), weight );
	    h_DV_minSqrterrd0_mind0_s [ireg][idv] ->Fill( secVtx_mind0,                sqrt(sqrt(secVtx_minerrd0)), weight );
	    h_DV_minSqrterrz0_minz0_s [ireg][idv] ->Fill( secVtx_minz0,                sqrt(sqrt(secVtx_minerrz0)), weight );
	    h_DV_minSqrterrd0z0_s     [ireg][idv] ->Fill( sqrt(sqrt(secVtx_minerrz0)), sqrt(sqrt(secVtx_minerrd0)), weight );

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
	    if ( m_histoInfoSwitch->m_vtxOverallTrk ) {
	      h_ntrkDV_sumd0           [ireg][idv][ntrk-2]->Fill( secVtx_sumd0,                   weight );
	      h_ntrkDV_sumz0           [ireg][idv][ntrk-2]->Fill( secVtx_sumz0,                   weight );
	      h_ntrkDV_sumP            [ireg][idv][ntrk-2]->Fill( secVtx_sumP,                    weight );
	      h_ntrkDV_sumd0_sv        [ireg][idv][ntrk-2]->Fill( secVtx_sumd0_sv,                weight );
	      h_ntrkDV_sumd0_sv        [ireg][idv][ntrk-2]->Fill( secVtx_sumz0_sv,                weight );
	      h_ntrkDV_sumP_sv         [ireg][idv][ntrk-2]->Fill( secVtx_sumP_sv,                 weight );
	      h_ntrkDV_sumsqrtd0       [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumd0),             weight );
	      h_ntrkDV_sumsqrtz0       [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumz0),             weight );
	      h_ntrkDV_sumsqrtP        [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumP),              weight );
	      h_ntrkDV_sumsqrtd0_sv    [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumd0_sv),          weight );
	      h_ntrkDV_sumsqrtd0_sv    [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumz0_sv),          weight );
	      h_ntrkDV_sumsqrtP_sv     [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_sumP_sv),           weight );
	      h_ntrkDV_mind0           [ireg][idv][ntrk-2]->Fill( secVtx_mind0,                   weight );
	      h_ntrkDV_minz0           [ireg][idv][ntrk-2]->Fill( secVtx_minz0,                   weight );
	      h_ntrkDV_minP            [ireg][idv][ntrk-2]->Fill( secVtx_minP,                    weight );
	      h_ntrkDV_mind0_sv        [ireg][idv][ntrk-2]->Fill( secVtx_mind0_sv,                weight );
	      h_ntrkDV_minz0_sv        [ireg][idv][ntrk-2]->Fill( secVtx_minz0_sv,                weight );
	      h_ntrkDV_minP_sv         [ireg][idv][ntrk-2]->Fill( secVtx_minP_sv,                 weight );
	      h_ntrkDV_minsqrtd0       [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_mind0),             weight );
	      h_ntrkDV_minsqrtz0       [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_minz0),             weight );
	      h_ntrkDV_minsqrtP        [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_minP),              weight );
	      h_ntrkDV_minsqrtd0_sv    [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_mind0_sv),          weight );
	      h_ntrkDV_minsqrtd0_sv    [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_minz0_sv),          weight );
	      h_ntrkDV_minsqrtP_sv     [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_minP_sv),           weight );
	      h_ntrkDV_maxd0           [ireg][idv][ntrk-2]->Fill( secVtx_maxd0,                   weight );
	      h_ntrkDV_maxz0           [ireg][idv][ntrk-2]->Fill( secVtx_maxz0,                   weight );
	      h_ntrkDV_maxP            [ireg][idv][ntrk-2]->Fill( secVtx_maxP,                    weight );
	      h_ntrkDV_maxd0_sv        [ireg][idv][ntrk-2]->Fill( secVtx_maxd0_sv,                weight );
	      h_ntrkDV_maxz0_sv        [ireg][idv][ntrk-2]->Fill( secVtx_maxz0_sv,                weight );
	      h_ntrkDV_maxP_sv         [ireg][idv][ntrk-2]->Fill( secVtx_maxP_sv,                 weight );
	      h_ntrkDV_maxsqrtd0       [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxd0),             weight );
	      h_ntrkDV_maxsqrtz0       [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxz0),             weight );
	      h_ntrkDV_maxsqrtP        [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxP),              weight );
	      h_ntrkDV_maxsqrtd0_sv    [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxd0_sv),          weight );
	      h_ntrkDV_maxsqrtd0_sv    [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxz0_sv),          weight );
	      h_ntrkDV_maxsqrtP_sv     [ireg][idv][ntrk-2]->Fill( sqrt(secVtx_maxP_sv),           weight );
	    }
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

	// do DV cutflows
	if ( m_histoInfoSwitch->m_cutflow || m_histoInfoSwitch->m_abcdcutOnly ) {
	  // --> test cuts
	  if ( m_nType1DVs ) {
	    std::vector<int> DV_testCut;
	    getDVTypes( i, DV_testCut, base_dv, false, false, false, false, false, false );
	    std::vector<int> dvTestCut ( DV_testCut.size() / m_nType1DVs, 0 );
	    for ( size_t idvc = 0; idvc != DV_testCut.size(); ++idvc ) {
	      dvTestCut[idvc / m_nType1DVs] += DV_testCut[idvc];
	      h_evt_testCutflow_DV [ireg][idvc / m_nType1DVs]
		->Fill( idvc % m_nType1DVs, ( dvTestCut[idvc/m_nType1DVs] / ( idvc % m_nType1DVs + 1 ) ) * weight );
	    }
	  }
	  // --> "good" cuts
	  std::vector<int> DV_cut;
	  getDVTypes( i, DV_cut, base_dv, false, false, false, false, false, true );
	  int n_goodCuts = DV_cut.size() / h_evt_cutflow_DV [ireg].size();
	  std::vector<int> dvCut ( h_evt_cutflow_DV [ireg].size(), 0 );
	  for ( size_t idvc = 0; idvc != DV_cut.size(); ++idvc ) {
	    dvCut[idvc / n_goodCuts] += DV_cut[idvc];
	    h_evt_cutflow_DV [ireg][idvc / n_goodCuts]
	      ->Fill( idvc % n_goodCuts, ( dvCut[idvc/n_goodCuts] / ( idvc % n_goodCuts + 1 ) ) * weight );
	  }
	}

      } // end loop over vertices

      // fill DV count, ndv histograms
      for ( size_t idv = 0; idv != n_DV.size(); ++idv ) {
	h_DV_n [ireg][idv] ->Fill( n_DV[idv], weight );
	if ( m_numVtxTrks )
	  for ( const auto& ntrkDV : n_ntrkDV[idv] )
	    h_ntrkDV_n [ireg][idv][ntrkDV.first-2] ->Fill( ntrkDV.second, weight );
      
	// NDV cutflow
	if ( m_histoInfoSwitch->m_cutflow || m_histoInfoSwitch->m_abcdcutOnly ) {
	  if ( idv >= m_nTypeBDVs ) continue;
	  for ( int indv = 0; indv != m_ndv+1; ++indv )
	    if ( n_DV[idv] > indv-1 )
	      h_evt_cutflow_NDV [ireg][idv] ->Fill( indv, weight );
	  // ntrk-NDV cutflow
	  if ( m_numVtxTrks ) {
	    for ( const auto& ntrkDV : n_ntrkDV[idv] )
	      for ( int intrkndv = 0; intrkndv != m_ndv+1; ++intrkndv )
		if ( ntrkDV.second > intrkndv-1 )
		  h_evt_cutflow_ntrkNDV [ireg][idv][ntrkDV.first-2] ->Fill( intrkndv, weight );
	  }
	}

	// fill NDV vector
	if ( !m_histoInfoSwitch->m_truthOnly )
	  NDV .push_back( n_DV[idv] );
      }

      
      // FILL SIGNAL CUTFLOWS
      int icuthist = 0;
      for ( size_t icej = 0; icej != m_cutEJ.size(); ++icej )
	for ( const auto& incej : m_ncutEJ )
	  for ( size_t icdv = 0; icdv != m_cutDV.size(); ++icdv )
	    for ( const auto& incdv : m_ncutDV ) {
	      int kcdv    = m_cutDV.size()      - icdv;
	      int kcej    = m_cutEJ.size()*kcdv - icej;
	      int iejhist = m_nTypeBJs          - kcej*2;
	      int idvhist = m_nTypeBDVs         - kcdv;
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist   ] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+1 ] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+2 ] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+3 ] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+4 ] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+5 ] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+6 ] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+7 ] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+8 ] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+9 ] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+10] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+11] ->Fill( int(0),      weight );
	      h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg][icuthist+12] ->Fill( int(0),      weight );
	      if ( n_jet[iejhist] >= incej ) {
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist   ] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+1 ] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+2 ] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+3 ] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+4 ] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+5 ] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+6 ] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+7 ] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+8 ] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+9 ] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+10] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+11] ->Fill(     1,       weight );
		h_evt_cutflow_signal_NEJ_NDV_NJetX     [ireg][icuthist+12] ->Fill(     1,       weight );
		if ( n_DV[idvhist] >= incdv ) {
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist   ] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+1 ] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+2 ] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+3 ] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+4 ] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+5 ] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+6 ] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+7 ] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+8 ] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+9 ] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+10] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+11] ->Fill(     2,       weight );
		  h_evt_cutflow_signal_NEJ_NDV_NJetX   [ireg][icuthist+12] ->Fill(     2,       weight );
		  for ( size_t injx = 0; injx != m_vcutNJetX.size(); ++injx ) {
		    //if ( njht          > m_vcutNJetX [0]  )
		    if ( njht          > m_njetht_cut        [m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist   ] ->Fill(   3+injx,  weight );
		    //if ( njpt          > m_vcutNJetX [1]  )
		    if ( njpt          > m_njetpt_cut        [m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+1 ] ->Fill(   3+injx,  weight );
		    //if ( njsumm        > m_vcutNJetX [2]  )
		    if ( njsumm        > m_njetsm_cut        [m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+2 ] ->Fill(   3+injx,  weight );
		    //if ( mindiff_pt    > m_vcutNJetX [3]  )
		    if ( mindiff_pt    > m_njetjj_pt_cut     [m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+3 ] ->Fill(   3+injx,  weight );
		    //if ( maxdr_pt      > m_vcutNJetX [4]  )
		    if ( maxdr_pt      > m_njetjjdr_pt_cut   [m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+4 ] ->Fill(   3+injx,  weight );
		    //if ( avgjj_pt      > m_vcutNJetX [5]  )
		    if ( avgjj_pt      > m_avgnjetjj_pt_cut  [m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+5 ] ->Fill(   3+injx,  weight );
		    //if ( maxjj_sumPt   > m_vcutNJetX [6]  )
		    if ( maxjj_sumPt   > m_maxnjetjj_ht_cut  [m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+6 ] ->Fill(   3+injx,  weight );
		    //if ( maxjj_sumM    > m_vcutNJetX [7]  )
		    if ( maxjj_sumM    > m_maxnjetjj_sm_cut  [m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+7 ] ->Fill(   3+injx,  weight );
		    //if ( minjj_sumPt   > m_vcutNJetX [8]  )
		    if ( minjj_sumPt   > m_minnjetjj_ht_cut  [m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+8 ] ->Fill(   3+injx,  weight );
		    //if ( minjj_sumM    > m_vcutNJetX [9]  )
		    if ( minjj_sumM    > m_minnjetjj_sm_cut  [m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+9 ] ->Fill(   3+injx,  weight );
		    //if ( maxptjj_pt    > m_vcutNJetX [10] )
		    if ( maxptjj_pt    > m_maxptnjetjj_pt_cut[m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+10] ->Fill(   3+injx,  weight );
		    //if ( maxptjj_sumPt > m_vcutNJetX [11] )
		    if ( maxptjj_sumPt > m_maxptnjetjj_ht_cut[m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+11] ->Fill(   3+injx,  weight );
		    //if ( maxptjj_sumM  > m_vcutNJetX [12] )
		    if ( maxptjj_sumM  > m_maxptnjetjj_sm_cut[m_vcutNJetX[injx]] )
		      h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][icuthist+12] ->Fill(   3+injx,  weight );
		  }
		}
	      }
	      icuthist += m_cutNJetX.size();
	    }

    } // end if not truthOnly


    


    // // --- ORPHAN PT --- //
    // if ( m_mc ) {
    //   if ( m_debug ) Info( "EJsHistogramManager::execute()", "doing orphan pt histos" );
    //   h_evt_truthPartPtSum            [ireg] ->Fill( m_truthPartPtSum,                                  weight );
    //   h_evt_truthPartDarkPtSum        [ireg] ->Fill( m_truthPartDarkPtSum,                              weight );
    //   h_evt_truthJetConstitPtSum      [ireg] ->Fill( truthJetConstit_sumPt,                             weight );
    //   h_evt_tightTruthJetConstitPtSum [ireg] ->Fill( tightTruthJetConstit_sumPt,                        weight );
    //   h_evt_darkJetConstitPtSum       [ireg] ->Fill( darkJetConstit_sumPt,                              weight );
    //   h_evt_tightDarkJetConstitPtSum  [ireg] ->Fill( tightDarkJetConstit_sumPt,                         weight );
    //   h_orphanPt                      [ireg] ->Fill( m_truthPartPtSum     - truthJetConstit_sumPt,      weight );
    //   h_tightOrphanPt                 [ireg] ->Fill( m_truthPartPtSum     - tightTruthJetConstit_sumPt, weight );
    //   h_darkOrphanPt                  [ireg] ->Fill( m_truthPartDarkPtSum - darkJetConstit_sumPt,       weight );
    //   h_tightDarkOrphanPt             [ireg] ->Fill( m_truthPartDarkPtSum - tightDarkJetConstit_sumPt,  weight );
    // }


    // --- ABCD PLANE TESTS --- //
    // -- tentative ABCD variables
    // --> --> excludes NEJ cuts (can add later, but shoouldn't really need for now...)
    // ADD VRSH ABCD PLOTS
    if ( m_histoInfoSwitch->m_abcd || m_histoInfoSwitch->m_abcdcutOnly ) {
      if ( m_debug ) Info( "EJsHistogramManager::execute()", "doing abcd histos" );
      for ( size_t idv = 0; idv != NDV.size(); ++idv ) {
	h_abcd_nDV_NJetHt                     [ireg][idv] ->Fill( njht,                NDV[idv], weight );
	if ( m_histoInfoSwitch->m_vrshift )
	  h_abcd_nDV_NJetHt                   [ireg][idv] ->Fill( njht_vrsh,           NDV[idv], weight );
	if ( !m_histoInfoSwitch->m_truthOnly ) {
	  h_abcd_nDV_NJetPt                   [ireg][idv] ->Fill( njpt,                NDV[idv], weight );
	  h_abcd_nDV_NJetSumM                 [ireg][idv] ->Fill( njsumm,              NDV[idv], weight );
	  h_abcd_nDV_NJetJJ_pt                [ireg][idv] ->Fill( mindiff_pt,          NDV[idv], weight );
	  h_abcd_nDV_NJetJJ_m                 [ireg][idv] ->Fill( mindiff_invM,        NDV[idv], weight );
	  h_abcd_nDV_NJetJJmindpt_pt          [ireg][idv] ->Fill( mindiffpt_pt,        NDV[idv], weight );
	  h_abcd_nDV_NJetJJmindpt_m           [ireg][idv] ->Fill( mindiffpt_invM,      NDV[idv], weight );
	  h_abcd_nDV_NJetJJmaxdr_pt           [ireg][idv] ->Fill( maxdr_pt,            NDV[idv], weight );
	  h_abcd_nDV_NJetJJmaxdr_m            [ireg][idv] ->Fill( maxdr_invM,          NDV[idv], weight );
	  h_abcd_nDV_avgNJetJJ_pt             [ireg][idv] ->Fill( avgjj_pt,            NDV[idv], weight );
	  h_abcd_nDV_avgNJetJJ_m              [ireg][idv] ->Fill( avgjj_m,             NDV[idv], weight );
	  h_abcd_nDV_maxNJetJJ_pt             [ireg][idv] ->Fill( maxjj_pt,            NDV[idv], weight );
	  h_abcd_nDV_maxNJetJJ_m              [ireg][idv] ->Fill( maxjj_m,             NDV[idv], weight );
	  h_abcd_nDV_maxNJetJJ_sumPt          [ireg][idv] ->Fill( maxjj_sumPt,         NDV[idv], weight );
	  h_abcd_nDV_maxNJetJJ_sumM           [ireg][idv] ->Fill( maxjj_sumM,          NDV[idv], weight );  
	  h_abcd_nDV_minNJetJJ_pt             [ireg][idv] ->Fill( minjj_pt,            NDV[idv], weight );
	  h_abcd_nDV_minNJetJJ_m              [ireg][idv] ->Fill( minjj_m,             NDV[idv], weight );
	  h_abcd_nDV_minNJetJJ_sumPt          [ireg][idv] ->Fill( minjj_sumPt,         NDV[idv], weight );
	  h_abcd_nDV_minNJetJJ_sumM           [ireg][idv] ->Fill( minjj_sumM,          NDV[idv], weight ); 
	  h_abcd_nDV_maxptNJetJJ_pt           [ireg][idv] ->Fill( maxptjj_pt,          NDV[idv], weight );
	  h_abcd_nDV_maxptNJetJJ_m            [ireg][idv] ->Fill( maxptjj_m,           NDV[idv], weight );
	  h_abcd_nDV_maxptNJetJJ_sumPt        [ireg][idv] ->Fill( maxptjj_sumPt,       NDV[idv], weight );
	  h_abcd_nDV_maxptNJetJJ_sumM         [ireg][idv] ->Fill( maxptjj_sumM,        NDV[idv], weight ); 
	  h_abcd_nDV_minptNJetJJ_pt           [ireg][idv] ->Fill( minptjj_pt,          NDV[idv], weight );
	  h_abcd_nDV_minptNJetJJ_m            [ireg][idv] ->Fill( minptjj_m,           NDV[idv], weight );
	  h_abcd_nDV_minptNJetJJ_sumPt        [ireg][idv] ->Fill( minptjj_sumPt,       NDV[idv], weight );
	  h_abcd_nDV_minptNJetJJ_sumM         [ireg][idv] ->Fill( minptjj_sumM,        NDV[idv], weight );
	  if ( m_histoInfoSwitch->m_vrshift ) {
	    h_abcd_nDV_NJetPt_vrsh            [ireg][idv] ->Fill( njpt_vrsh,           NDV[idv], weight );
	    h_abcd_nDV_NJetSumM_vrsh          [ireg][idv] ->Fill( njsumm_vrsh,         NDV[idv], weight );
	    h_abcd_nDV_NJetJJ_pt_vrsh         [ireg][idv] ->Fill( mindiff_pt_vrsh,     NDV[idv], weight );
	    h_abcd_nDV_NJetJJ_m_vrsh          [ireg][idv] ->Fill( mindiff_invM_vrsh,   NDV[idv], weight );
	    h_abcd_nDV_NJetJJmindpt_pt_vrsh   [ireg][idv] ->Fill( mindiffpt_pt_vrsh,   NDV[idv], weight );
	    h_abcd_nDV_NJetJJmindpt_m_vrsh    [ireg][idv] ->Fill( mindiffpt_invM_vrsh, NDV[idv], weight );
	    h_abcd_nDV_NJetJJmaxdr_pt_vrsh    [ireg][idv] ->Fill( maxdr_pt_vrsh,       NDV[idv], weight );
	    h_abcd_nDV_NJetJJmaxdr_m_vrsh     [ireg][idv] ->Fill( maxdr_invM_vrsh,     NDV[idv], weight );
	    h_abcd_nDV_avgNJetJJ_pt_vrsh      [ireg][idv] ->Fill( avgjj_pt_vrsh,       NDV[idv], weight );
	    h_abcd_nDV_avgNJetJJ_m_vrsh       [ireg][idv] ->Fill( avgjj_m_vrsh,        NDV[idv], weight );
	    h_abcd_nDV_maxNJetJJ_pt_vrsh      [ireg][idv] ->Fill( maxjj_pt_vrsh,       NDV[idv], weight );
	    h_abcd_nDV_maxNJetJJ_m_vrsh       [ireg][idv] ->Fill( maxjj_m_vrsh,        NDV[idv], weight );
	    h_abcd_nDV_maxNJetJJ_sumPt_vrsh   [ireg][idv] ->Fill( maxjj_sumPt_vrsh,    NDV[idv], weight );
	    h_abcd_nDV_maxNJetJJ_sumM_vrsh    [ireg][idv] ->Fill( maxjj_sumM_vrsh,     NDV[idv], weight );  
	    h_abcd_nDV_minNJetJJ_pt_vrsh      [ireg][idv] ->Fill( minjj_pt_vrsh,       NDV[idv], weight );
	    h_abcd_nDV_minNJetJJ_m_vrsh       [ireg][idv] ->Fill( minjj_m_vrsh,        NDV[idv], weight );
	    h_abcd_nDV_minNJetJJ_sumPt_vrsh   [ireg][idv] ->Fill( minjj_sumPt_vrsh,    NDV[idv], weight );
	    h_abcd_nDV_minNJetJJ_sumM_vrsh    [ireg][idv] ->Fill( minjj_sumM_vrsh,     NDV[idv], weight ); 
	    h_abcd_nDV_maxptNJetJJ_pt_vrsh    [ireg][idv] ->Fill( maxptjj_pt_vrsh,     NDV[idv], weight );
	    h_abcd_nDV_maxptNJetJJ_m_vrsh     [ireg][idv] ->Fill( maxptjj_m_vrsh,      NDV[idv], weight );
	    h_abcd_nDV_maxptNJetJJ_sumPt_vrsh [ireg][idv] ->Fill( maxptjj_sumPt_vrsh,  NDV[idv], weight );
	    h_abcd_nDV_maxptNJetJJ_sumM_vrsh  [ireg][idv] ->Fill( maxptjj_sumM_vrsh,   NDV[idv], weight ); 
	    h_abcd_nDV_minptNJetJJ_pt_vrsh    [ireg][idv] ->Fill( minptjj_pt_vrsh,     NDV[idv], weight );
	    h_abcd_nDV_minptNJetJJ_m_vrsh     [ireg][idv] ->Fill( minptjj_m_vrsh,      NDV[idv], weight );
	    h_abcd_nDV_minptNJetJJ_sumPt_vrsh [ireg][idv] ->Fill( minptjj_sumPt_vrsh,  NDV[idv], weight );
	    h_abcd_nDV_minptNJetJJ_sumM_vrsh  [ireg][idv] ->Fill( minptjj_sumM_vrsh,   NDV[idv], weight );
	  }
	}
      }
    }

    ++m_nEntries [ireg];
    m_nWeightedEntries [ireg] += weight;
    
  } // end loop over regions

  ++m_nEntries_all;
  m_nWeightedEntries_all += weight;

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: finalize ( const std::vector<EJsHelper::Region>& regions )
{

  double scale_factor = 1;
  double n_ejsana     = m_ntupcut_signal_full[m_ntupcut_signal_full.size()-1];
  if ( n_ejsana ) scale_factor = m_nWeightedEntries_all / n_ejsana;
  double sumw_init = m_sumw_init * scale_factor;
  
  for ( size_t ireg = 0; ireg != regions.size(); ++ireg ) {

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

    if ( m_histoInfoSwitch->m_cutflow || m_histoInfoSwitch->m_abcdcutOnly ) {
      // cutflow efficiency histograms
      double reg_count  = m_nWeightedEntries [ireg];
      
      // --> JETS
      //for ( size_t icj = 0; icj != h_evt_cutflow_jet [ireg].size(); ++icj ) {
      //float  jcount = h_evt_cutflow_jet     [ireg][icj] ->GetBinContent(1);
      //float ljcount = h_evt_cutflow_leadjet [ireg][icj] ->GetBinContent(1);
      for ( size_t icj = 0; icj != h_evt_testCutflow_jet [ireg].size(); ++icj ) {
      	float  jcount = h_evt_testCutflow_jet     [ireg][icj][0] ->GetBinContent(1);
      	float ljcount = h_evt_testCutflow_leadJet [ireg][icj][0] ->GetBinContent(1);
	// --> test jet cuts
	if ( m_nType1Js )
	  for ( unsigned ijsv = 0; ijsv != m_nTypeJSVs; ++ijsv ) {
	    for ( int ibin = 0; ibin != h_evt_testCutflowEfficiency_jet [ireg][icj][ijsv] ->GetNbinsX(); ++ibin ) {
	      float ibin_jcut  = h_evt_testCutflow_jet     [ireg][icj][ijsv] ->GetBinContent(ibin+1);
	      float ibin_ljcut = h_evt_testCutflow_leadJet [ireg][icj][ijsv] ->GetBinContent(ibin+1);
	      h_evt_testCutflowEfficiency_jet     [ireg][icj][ijsv] ->Fill( ibin, ibin_jcut  /  jcount );
	      h_evt_testCutflowEfficiency_leadJet [ireg][icj][ijsv] ->Fill( ibin, ibin_ljcut / ljcount );
	    }
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvP4Jets ) {
	      for ( int ibin = 0; ibin != h_evt_testCutflowEfficiency_svP4Jet [ireg][icj][ijsv] ->GetNbinsX(); ++ibin ) {
		float ibin_jcut  = h_evt_testCutflow_svP4Jet     [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		float ibin_ljcut = h_evt_testCutflow_leadSvP4Jet [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		h_evt_testCutflowEfficiency_svP4Jet     [ireg][icj][ijsv] ->Fill( ibin, ibin_jcut  / jcount  );
		h_evt_testCutflowEfficiency_leadSvP4Jet [ireg][icj][ijsv] ->Fill( ibin, ibin_ljcut / ljcount );
	      }
	    }
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvPtJets ) {
	      for ( int ibin = 0; ibin != h_evt_testCutflowEfficiency_svPtJet [ireg][icj][ijsv] ->GetNbinsX(); ++ibin ) {
		float ibin_jcut  = h_evt_testCutflow_svPtJet     [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		float ibin_ljcut = h_evt_testCutflow_leadSvPtJet [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		h_evt_testCutflowEfficiency_svPtJet     [ireg][icj][ijsv] ->Fill( ibin, ibin_jcut  / jcount  );
		h_evt_testCutflowEfficiency_leadSvPtJet [ireg][icj][ijsv] ->Fill( ibin, ibin_ljcut / ljcount );
	      }
	    }
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHtJets ) {
	      for ( int ibin = 0; ibin != h_evt_testCutflowEfficiency_svHtJet [ireg][icj][ijsv] ->GetNbinsX(); ++ibin ) {
		float ibin_jcut  = h_evt_testCutflow_svHtJet     [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		float ibin_ljcut = h_evt_testCutflow_leadSvHtJet [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		h_evt_testCutflowEfficiency_svHtJet     [ireg][icj][ijsv] ->Fill( ibin, ibin_jcut  / jcount  );
		h_evt_testCutflowEfficiency_leadSvHtJet [ireg][icj][ijsv] ->Fill( ibin, ibin_ljcut / ljcount );
	      }
	    }
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHJets ) {
	      for ( int ibin = 0; ibin != h_evt_testCutflowEfficiency_svHJet [ireg][icj][ijsv] ->GetNbinsX(); ++ibin ) {
		float ibin_jcut  = h_evt_testCutflow_svHJet     [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		float ibin_ljcut = h_evt_testCutflow_leadSvHJet [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		h_evt_testCutflowEfficiency_svHJet     [ireg][icj][ijsv] ->Fill( ibin, ibin_jcut  / jcount  );
		h_evt_testCutflowEfficiency_leadSvHJet [ireg][icj][ijsv] ->Fill( ibin, ibin_ljcut / ljcount );
	      }
	    }
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNtrkJets ) {
	      for ( int ibin = 0; ibin != h_evt_testCutflowEfficiency_svNtrkJet [ireg][icj][ijsv] ->GetNbinsX(); ++ibin ) {
		float ibin_jcut  = h_evt_testCutflow_svNtrkJet     [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		float ibin_ljcut = h_evt_testCutflow_leadSvNtrkJet [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		h_evt_testCutflowEfficiency_svNtrkJet     [ireg][icj][ijsv] ->Fill( ibin, ibin_jcut  / jcount  );
		h_evt_testCutflowEfficiency_leadSvNtrkJet [ireg][icj][ijsv] ->Fill( ibin, ibin_ljcut / ljcount );
	      }
	    }
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNjtrkJets ) {
	      for ( int ibin = 0; ibin != h_evt_testCutflowEfficiency_svNjtrkJet [ireg][icj][ijsv] ->GetNbinsX(); ++ibin ) {
		float ibin_jcut  = h_evt_testCutflow_svNjtrkJet     [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		float ibin_ljcut = h_evt_testCutflow_leadSvNjtrkJet [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		h_evt_testCutflowEfficiency_svNjtrkJet     [ireg][icj][ijsv] ->Fill( ibin, ibin_jcut  / jcount  );
		h_evt_testCutflowEfficiency_leadSvNjtrkJet [ireg][icj][ijsv] ->Fill( ibin, ibin_ljcut / ljcount );
	      }
	    }
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvTrkJets ) {
	      for ( int ibin = 0; ibin != h_evt_testCutflowEfficiency_svTrkJet [ireg][icj][ijsv] ->GetNbinsX(); ++ibin ) {
		float ibin_jcut  = h_evt_testCutflow_svTrkJet     [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		float ibin_ljcut = h_evt_testCutflow_leadSvTrkJet [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		h_evt_testCutflowEfficiency_svTrkJet     [ireg][icj][ijsv] ->Fill( ibin, ibin_jcut  / jcount  );
		h_evt_testCutflowEfficiency_leadSvTrkJet [ireg][icj][ijsv] ->Fill( ibin, ibin_ljcut / ljcount );
	      }
	    }
	    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvJets ) {
	      for ( int ibin = 0; ibin != h_evt_testCutflowEfficiency_svNJet [ireg][icj][ijsv] ->GetNbinsX(); ++ibin ) {
		float ibin_jcut  = h_evt_testCutflow_svNJet     [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		float ibin_ljcut = h_evt_testCutflow_leadSvNJet [ireg][icj][ijsv] ->GetBinContent(ibin+1);
		h_evt_testCutflowEfficiency_svNJet     [ireg][icj][ijsv] ->Fill( ibin, ibin_jcut  / jcount  );
		h_evt_testCutflowEfficiency_leadSvNJet [ireg][icj][ijsv] ->Fill( ibin, ibin_ljcut / ljcount );
	      }
	    }
	  }

	// --> emerging jet cuts
	for ( unsigned ijsv = 0; ijsv != m_nTypeJSVs; ++ijsv ) {
	  for ( int ibin = 0; ibin != h_evt_cutflowEfficiency_emergingJet [ireg][icj][ijsv] ->GetNbinsX(); ++ibin ) {
	    float ibin_jcut  = h_evt_cutflow_emergingJet     [ireg][icj][ijsv] ->GetBinContent(ibin+1);
	    float ibin_ljcut = h_evt_cutflow_leadEmergingJet [ireg][icj][ijsv] ->GetBinContent(ibin+1);
	    h_evt_cutflowEfficiency_emergingJet     [ireg][icj][ijsv] ->Fill( ibin, ibin_jcut  /  jcount );
	    h_evt_cutflowEfficiency_leadEmergingJet [ireg][icj][ijsv] ->Fill( ibin, ibin_ljcut / ljcount );
	  }
	}
      }
      // --> N-Jet cuts
      for ( size_t icnj = 0; icnj != h_evt_cutflow_NJet [ireg].size(); ++icnj ) {
      	for ( int ibin = 0; ibin != h_evt_cutflowEfficiency_NJet [ireg][icnj] ->GetNbinsX(); ++ibin ) {
      	  float ibin_cut     = h_evt_cutflow_NJet     [ireg][icnj] ->GetBinContent(ibin+1);
      	  float ileadbin_cut = h_evt_cutflow_NLeadJet [ireg][icnj] ->GetBinContent(ibin+1);
      	  h_evt_cutflowEfficiency_NJet          [ireg][icnj] ->Fill( ibin, ibin_cut     / reg_count );
      	  h_evt_cutflowEfficiency_NLeadJet      [ireg][icnj] ->Fill( ibin, ileadbin_cut / reg_count );
      	  h_evt_cutflowTotalEfficiency_NJet     [ireg][icnj] ->Fill( ibin, ibin_cut     / sumw_init );
      	  h_evt_cutflowTotalEfficiency_NLeadJet [ireg][icnj] ->Fill( ibin, ileadbin_cut / sumw_init );
      	}
      }
 
      // --> DVS
      for ( size_t icdv = 0; icdv != h_evt_cutflow_DV [ireg].size(); ++icdv ) {
	float count = h_evt_cutflow_DV [ireg][icdv] ->GetBinContent(1);
	// --> test DV cuts
	if ( m_nType1DVs ) {
	  for ( int ibin = 0; ibin != h_evt_testCutflowEfficiency_DV [ireg][icdv] ->GetNbinsX(); ++ibin ) {
	    float ibin_cut = h_evt_testCutflow_DV [ireg][icdv] ->GetBinContent(ibin+1);
	    h_evt_testCutflowEfficiency_DV        [ireg][icdv] ->Fill( ibin, ibin_cut / count );
	  }
	}
	// --> good DV cuts
	for ( int ibin = 0; ibin != h_evt_cutflowEfficiency_DV [ireg][icdv] ->GetNbinsX(); ++ibin ) {
	  float ibin_cut = h_evt_cutflow_DV       [ireg][icdv] ->GetBinContent(ibin+1);
	  h_evt_cutflowEfficiency_DV              [ireg][icdv] ->Fill( ibin, ibin_cut / count );
	}
      }
      // --> N-DV cuts
      for ( size_t icndv = 0; icndv != h_evt_cutflow_NDV        [ireg].size(); ++icndv ) {
	for ( int ibin = 0; ibin != h_evt_cutflowEfficiency_NDV [ireg][icndv] ->GetNbinsX(); ++ibin ) {
	  float ibin_cut   = h_evt_cutflow_NDV  [ireg][icndv] ->GetBinContent(ibin+1);
	  h_evt_cutflowEfficiency_NDV      [ireg][icndv] ->Fill( ibin, ibin_cut / reg_count );
	  h_evt_cutflowTotalEfficiency_NDV [ireg][icndv] ->Fill( ibin, ibin_cut / sumw_init );
	}
	// --> n-trk N-DV cuts
	if ( m_numVtxTrks ) {
	  for ( size_t itrk = 0; itrk != h_evt_cutflow_ntrkNDV [ireg][icndv].size(); ++itrk ) {
	    for ( int itrkbin = 0; itrkbin != h_evt_cutflowEfficiency_ntrkNDV [ireg][icndv][itrk] ->GetNbinsX(); ++itrkbin ) {
	      float itrkbin_cut = h_evt_cutflow_ntrkNDV [ireg][icndv][itrk] ->GetBinContent(itrkbin+1);
	      h_evt_cutflowEfficiency_ntrkNDV      [ireg][icndv][itrk] ->Fill( itrkbin, itrkbin_cut / reg_count );
	      h_evt_cutflowTotalEfficiency_ntrkNDV [ireg][icndv][itrk] ->Fill( itrkbin, itrkbin_cut / sumw_init );
	    }
	  }
	}
      }
      // --> overall DV count / efficiency histograms
      for ( size_t ihdv = 0; ihdv != h_evt_count_DV [ireg].size(); ++ihdv ) {
	h_evt_cutEfficiency_DV      [ireg][ihdv] ->Divide( h_evt_count_DV [ireg][ihdv], h_evt_count_DV [ireg][0]                            );
	h_evt_matchcutEfficiency_DV [ireg][ihdv] ->Divide( h_evt_count_DV [ireg][ihdv], h_evt_count_DV [ireg][ihdv/m_nTypeBDVs*m_nTypeBDVs] );
      }

      // --> NJetX
      for ( int ibin = 0; ibin != h_evt_cutflowEfficiency_NJetHt [ireg] ->GetNbinsX(); ++ibin ) {
	float ibin_njetht_cut = h_evt_cutflow_NJetHt [ireg] ->GetBinContent(ibin+1);
	h_evt_cutflowEfficiency_NJetHt      [ireg] ->Fill( ibin, ibin_njetht_cut / reg_count );
	h_evt_cutflowTotalEfficiency_NJetHt [ireg] ->Fill( ibin, ibin_njetht_cut / sumw_init );
	if ( !m_histoInfoSwitch->m_truthOnly ) {
	  float ibin_njetpt_cut         = h_evt_cutflow_NJetPt            [ireg] ->GetBinContent(ibin+1);
	  float ibin_njetsm_cut         = h_evt_cutflow_NJetSumM          [ireg] ->GetBinContent(ibin+1);
	  float ibin_njetjj_pt_cut      = h_evt_cutflow_NJetJJ_pt         [ireg] ->GetBinContent(ibin+1);
	  float ibin_njetjj_m_cut       = h_evt_cutflow_NJetJJ_m          [ireg] ->GetBinContent(ibin+1);
	  float ibin_njetjjpt_pt_cut    = h_evt_cutflow_NJetJJmindpt_pt   [ireg] ->GetBinContent(ibin+1);
	  float ibin_njetjjpt_m_cut     = h_evt_cutflow_NJetJJmindpt_m    [ireg] ->GetBinContent(ibin+1);
	  float ibin_njetjjdr_pt_cut    = h_evt_cutflow_NJetJJmaxdr_pt    [ireg] ->GetBinContent(ibin+1);
	  float ibin_njetjjdr_m_cut     = h_evt_cutflow_NJetJJmaxdr_m     [ireg] ->GetBinContent(ibin+1);
	  float ibin_avgnjetjj_pt_cut   = h_evt_cutflow_avgNJetJJ_pt      [ireg] ->GetBinContent(ibin+1);
	  float ibin_avgnjetjj_m_cut    = h_evt_cutflow_avgNJetJJ_m       [ireg] ->GetBinContent(ibin+1);
	  float ibin_maxnjetjj_pt_cut   = h_evt_cutflow_maxNJetJJ_pt      [ireg] ->GetBinContent(ibin+1);
	  float ibin_maxnjetjj_m_cut    = h_evt_cutflow_maxNJetJJ_m       [ireg] ->GetBinContent(ibin+1);
	  float ibin_maxnjetjj_ht_cut   = h_evt_cutflow_maxNJetJJ_sumPt   [ireg] ->GetBinContent(ibin+1);
	  float ibin_maxnjetjj_sm_cut   = h_evt_cutflow_maxNJetJJ_sumM    [ireg] ->GetBinContent(ibin+1);
	  float ibin_minnjetjj_pt_cut   = h_evt_cutflow_minNJetJJ_pt      [ireg] ->GetBinContent(ibin+1);
	  float ibin_minnjetjj_m_cut    = h_evt_cutflow_minNJetJJ_m       [ireg] ->GetBinContent(ibin+1);
	  float ibin_minnjetjj_ht_cut   = h_evt_cutflow_minNJetJJ_sumPt   [ireg] ->GetBinContent(ibin+1);
	  float ibin_minnjetjj_sm_cut   = h_evt_cutflow_minNJetJJ_sumM    [ireg] ->GetBinContent(ibin+1);
	  float ibin_maxptnjetjj_pt_cut = h_evt_cutflow_maxptNJetJJ_pt    [ireg] ->GetBinContent(ibin+1);
	  float ibin_maxptnjetjj_m_cut  = h_evt_cutflow_maxptNJetJJ_m     [ireg] ->GetBinContent(ibin+1);
	  float ibin_maxptnjetjj_ht_cut = h_evt_cutflow_maxptNJetJJ_sumPt [ireg] ->GetBinContent(ibin+1);
	  float ibin_maxptnjetjj_sm_cut = h_evt_cutflow_maxptNJetJJ_sumM  [ireg] ->GetBinContent(ibin+1);
	  float ibin_minptnjetjj_pt_cut = h_evt_cutflow_minptNJetJJ_pt    [ireg] ->GetBinContent(ibin+1);
	  float ibin_minptnjetjj_m_cut  = h_evt_cutflow_minptNJetJJ_m     [ireg] ->GetBinContent(ibin+1);
	  float ibin_minptnjetjj_ht_cut = h_evt_cutflow_minptNJetJJ_sumPt [ireg] ->GetBinContent(ibin+1);
	  float ibin_minptnjetjj_sm_cut = h_evt_cutflow_minptNJetJJ_sumM  [ireg] ->GetBinContent(ibin+1);
	  h_evt_cutflowEfficiency_NJetPt                 [ireg] ->Fill( ibin, ibin_njetpt_cut         / reg_count );
	  h_evt_cutflowEfficiency_NJetSumM               [ireg] ->Fill( ibin, ibin_njetsm_cut         / reg_count );
	  h_evt_cutflowEfficiency_NJetJJ_pt              [ireg] ->Fill( ibin, ibin_njetjj_pt_cut      / reg_count );
	  h_evt_cutflowEfficiency_NJetJJ_m               [ireg] ->Fill( ibin, ibin_njetjj_m_cut       / reg_count );
	  h_evt_cutflowEfficiency_NJetJJmindpt_pt        [ireg] ->Fill( ibin, ibin_njetjjpt_pt_cut    / reg_count );
	  h_evt_cutflowEfficiency_NJetJJmindpt_m         [ireg] ->Fill( ibin, ibin_njetjjpt_m_cut     / reg_count );
	  h_evt_cutflowEfficiency_NJetJJmaxdr_pt         [ireg] ->Fill( ibin, ibin_njetjjdr_pt_cut    / reg_count );
	  h_evt_cutflowEfficiency_NJetJJmaxdr_m          [ireg] ->Fill( ibin, ibin_njetjjdr_m_cut     / reg_count );
	  h_evt_cutflowEfficiency_avgNJetJJ_pt           [ireg] ->Fill( ibin, ibin_avgnjetjj_pt_cut   / reg_count );
	  h_evt_cutflowEfficiency_avgNJetJJ_m            [ireg] ->Fill( ibin, ibin_avgnjetjj_m_cut    / reg_count );
	  h_evt_cutflowEfficiency_maxNJetJJ_pt           [ireg] ->Fill( ibin, ibin_maxnjetjj_pt_cut   / reg_count );
	  h_evt_cutflowEfficiency_maxNJetJJ_m            [ireg] ->Fill( ibin, ibin_maxnjetjj_m_cut    / reg_count );
	  h_evt_cutflowEfficiency_maxNJetJJ_sumPt        [ireg] ->Fill( ibin, ibin_maxnjetjj_ht_cut   / reg_count );
	  h_evt_cutflowEfficiency_maxNJetJJ_sumM         [ireg] ->Fill( ibin, ibin_maxnjetjj_sm_cut   / reg_count );
	  h_evt_cutflowEfficiency_minNJetJJ_pt           [ireg] ->Fill( ibin, ibin_minnjetjj_pt_cut   / reg_count );
	  h_evt_cutflowEfficiency_minNJetJJ_m            [ireg] ->Fill( ibin, ibin_minnjetjj_m_cut    / reg_count );
	  h_evt_cutflowEfficiency_minNJetJJ_sumPt        [ireg] ->Fill( ibin, ibin_minnjetjj_ht_cut   / reg_count );
	  h_evt_cutflowEfficiency_minNJetJJ_sumM         [ireg] ->Fill( ibin, ibin_minnjetjj_sm_cut   / reg_count );
	  h_evt_cutflowEfficiency_maxptNJetJJ_pt         [ireg] ->Fill( ibin, ibin_maxptnjetjj_pt_cut / reg_count );
	  h_evt_cutflowEfficiency_maxptNJetJJ_m          [ireg] ->Fill( ibin, ibin_maxptnjetjj_m_cut  / reg_count );
	  h_evt_cutflowEfficiency_maxptNJetJJ_sumPt      [ireg] ->Fill( ibin, ibin_maxptnjetjj_ht_cut / reg_count );
	  h_evt_cutflowEfficiency_maxptNJetJJ_sumM       [ireg] ->Fill( ibin, ibin_maxptnjetjj_sm_cut / reg_count );
	  h_evt_cutflowEfficiency_minptNJetJJ_pt         [ireg] ->Fill( ibin, ibin_minptnjetjj_pt_cut / reg_count );
	  h_evt_cutflowEfficiency_minptNJetJJ_m          [ireg] ->Fill( ibin, ibin_minptnjetjj_m_cut  / reg_count );
	  h_evt_cutflowEfficiency_minptNJetJJ_sumPt      [ireg] ->Fill( ibin, ibin_minptnjetjj_ht_cut / reg_count );
	  h_evt_cutflowEfficiency_minptNJetJJ_sumM       [ireg] ->Fill( ibin, ibin_minptnjetjj_sm_cut / reg_count );
	  h_evt_cutflowTotalEfficiency_NJetPt            [ireg] ->Fill( ibin, ibin_njetpt_cut         / sumw_init );
	  h_evt_cutflowTotalEfficiency_NJetSumM          [ireg] ->Fill( ibin, ibin_njetsm_cut         / sumw_init );
	  h_evt_cutflowTotalEfficiency_NJetJJ_pt         [ireg] ->Fill( ibin, ibin_njetjj_pt_cut      / sumw_init );
	  h_evt_cutflowTotalEfficiency_NJetJJ_m          [ireg] ->Fill( ibin, ibin_njetjj_m_cut       / sumw_init );
	  h_evt_cutflowTotalEfficiency_NJetJJmindpt_pt   [ireg] ->Fill( ibin, ibin_njetjjpt_pt_cut    / sumw_init );
	  h_evt_cutflowTotalEfficiency_NJetJJmindpt_m    [ireg] ->Fill( ibin, ibin_njetjjpt_m_cut     / sumw_init );
	  h_evt_cutflowTotalEfficiency_NJetJJmaxdr_pt    [ireg] ->Fill( ibin, ibin_njetjjdr_pt_cut    / sumw_init );
	  h_evt_cutflowTotalEfficiency_NJetJJmaxdr_m     [ireg] ->Fill( ibin, ibin_njetjjdr_m_cut     / sumw_init );
	  h_evt_cutflowTotalEfficiency_avgNJetJJ_pt      [ireg] ->Fill( ibin, ibin_avgnjetjj_pt_cut   / sumw_init );
	  h_evt_cutflowTotalEfficiency_avgNJetJJ_m       [ireg] ->Fill( ibin, ibin_avgnjetjj_m_cut    / sumw_init );
	  h_evt_cutflowTotalEfficiency_maxNJetJJ_pt      [ireg] ->Fill( ibin, ibin_maxnjetjj_pt_cut   / sumw_init );
	  h_evt_cutflowTotalEfficiency_maxNJetJJ_m       [ireg] ->Fill( ibin, ibin_maxnjetjj_m_cut    / sumw_init );
	  h_evt_cutflowTotalEfficiency_maxNJetJJ_sumPt   [ireg] ->Fill( ibin, ibin_maxnjetjj_ht_cut   / sumw_init );
	  h_evt_cutflowTotalEfficiency_maxNJetJJ_sumM    [ireg] ->Fill( ibin, ibin_maxnjetjj_sm_cut   / sumw_init );
	  h_evt_cutflowTotalEfficiency_minNJetJJ_pt      [ireg] ->Fill( ibin, ibin_minnjetjj_pt_cut   / sumw_init );
	  h_evt_cutflowTotalEfficiency_minNJetJJ_m       [ireg] ->Fill( ibin, ibin_minnjetjj_m_cut    / sumw_init );
	  h_evt_cutflowTotalEfficiency_minNJetJJ_sumPt   [ireg] ->Fill( ibin, ibin_minnjetjj_ht_cut   / sumw_init );
	  h_evt_cutflowTotalEfficiency_minNJetJJ_sumM    [ireg] ->Fill( ibin, ibin_minnjetjj_sm_cut   / sumw_init );
	  h_evt_cutflowTotalEfficiency_maxptNJetJJ_pt    [ireg] ->Fill( ibin, ibin_maxptnjetjj_pt_cut / sumw_init );
	  h_evt_cutflowTotalEfficiency_maxptNJetJJ_m     [ireg] ->Fill( ibin, ibin_maxptnjetjj_m_cut  / sumw_init );
	  h_evt_cutflowTotalEfficiency_maxptNJetJJ_sumPt [ireg] ->Fill( ibin, ibin_maxptnjetjj_ht_cut / sumw_init );
	  h_evt_cutflowTotalEfficiency_maxptNJetJJ_sumM  [ireg] ->Fill( ibin, ibin_maxptnjetjj_sm_cut / sumw_init );
	  h_evt_cutflowTotalEfficiency_minptNJetJJ_pt    [ireg] ->Fill( ibin, ibin_minptnjetjj_pt_cut / sumw_init );
	  h_evt_cutflowTotalEfficiency_minptNJetJJ_m     [ireg] ->Fill( ibin, ibin_minptnjetjj_m_cut  / sumw_init );
	  h_evt_cutflowTotalEfficiency_minptNJetJJ_sumPt [ireg] ->Fill( ibin, ibin_minptnjetjj_ht_cut / sumw_init );
	  h_evt_cutflowTotalEfficiency_minptNJetJJ_sumM  [ireg] ->Fill( ibin, ibin_minptnjetjj_sm_cut / sumw_init );
	}
      }

      // --> signal cutflows
      for ( size_t ihist = 0; ihist != h_evt_cutflow_signalRegion_NEJ_NDV_NJetX [ireg].size(); ++ihist ) {
	for ( size_t isrbin = 0; isrbin != m_ntupcut_signal.size(); ++isrbin )
	  h_evt_cutflow_signalRegion_NEJ_NDV_NJetX [ireg][ihist]
	    ->SetBinContent( isrbin+1, m_ntupcut_signal[isrbin] * scale_factor );
	for ( size_t isbin  = 0; isbin  != h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][ihist]->GetNbinsX() - 1; ++isbin )
	  h_evt_cutflow_signalRegion_NEJ_NDV_NJetX [ireg][ihist]
	    ->SetBinContent( m_ntupcut_signal.size()+isbin+1, h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][ihist]->GetBinContent( 2+isbin ) );
      }
      for ( size_t ihist = 0; ihist != h_evt_cutflow_signalRegionFull_NEJ_NDV_NJetX [ireg].size(); ++ihist ) {
	for ( size_t isrfbin = 0; isrfbin != m_ntupcut_signal_full.size()-1; ++isrfbin )
	  h_evt_cutflow_signalRegionFull_NEJ_NDV_NJetX [ireg][ihist]
	    ->SetBinContent( isrfbin+1, m_ntupcut_signal_full[isrfbin] * scale_factor );
	for ( size_t isrbin  = 0; isrbin  != m_ntupcut_signal     .size()-2;  ++isrbin )
	  h_evt_cutflow_signalRegionFull_NEJ_NDV_NJetX [ireg][ihist]
	    ->SetBinContent( m_ntupcut_signal_full.size() + isrbin, m_ntupcut_signal[2+isrbin] * scale_factor );
	for ( size_t isbin   = 0; isbin   != h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][ihist]->GetNbinsX() - 1; ++isbin )
	  h_evt_cutflow_signalRegionFull_NEJ_NDV_NJetX [ireg][ihist]
	    ->SetBinContent( m_ntupcut_signal_full.size() + m_ntupcut_signal.size() - 2 + isbin,
			     h_evt_cutflow_signal_NEJ_NDV_NJetX [ireg][ihist]->GetBinContent( 2+isbin ) );
      }

      for ( size_t ics  = 0; ics  != h_evt_cutflow_signal_NEJ_NDV_NJetX       [ireg].size(); ++ics  ) {
	for ( int ibin = 0; ibin != h_evt_cutflowEfficiency_signal_NEJ_NDV_NJetX       [ireg][ics]  ->GetNbinsX(); ++ibin ) {
	  float ibin_cut = h_evt_cutflow_signal_NEJ_NDV_NJetX           [ireg][ics]   ->GetBinContent(ibin+1);
	  h_evt_cutflowEfficiency_signal_NEJ_NDV_NJetX                [ireg][ics]   ->Fill( ibin, ibin_cut / reg_count );
	  h_evt_cutflowTotalEfficiency_signal_NEJ_NDV_NJetX           [ireg][ics]   ->Fill( ibin, ibin_cut / sumw_init );
	}
      }
      for ( size_t icsr = 0; icsr != h_evt_cutflow_signalRegion_NEJ_NDV_NJetX [ireg].size(); ++icsr ) {
	for ( int ibin = 0; ibin != h_evt_cutflowEfficiency_signalRegion_NEJ_NDV_NJetX [ireg][icsr] ->GetNbinsX(); ++ibin ) {
	  float ibin_cut = h_evt_cutflow_signalRegion_NEJ_NDV_NJetX     [ireg][icsr]  ->GetBinContent(ibin+1);
	  h_evt_cutflowEfficiency_signalRegion_NEJ_NDV_NJetX          [ireg][icsr]  ->Fill( ibin, ibin_cut / reg_count );
	  h_evt_cutflowTotalEfficiency_signalRegion_NEJ_NDV_NJetX     [ireg][icsr]  ->Fill( ibin, ibin_cut / sumw_init );
	}
      }
      for ( size_t icsrf = 0; icsrf != h_evt_cutflow_signalRegionFull_NEJ_NDV_NJetX [ireg].size(); ++icsrf ) {
	for ( int ibin = 0; ibin != h_evt_cutflowEfficiency_signalRegionFull_NEJ_NDV_NJetX [ireg][icsrf] ->GetNbinsX(); ++ibin ) {
	  float ibin_cut = h_evt_cutflow_signalRegionFull_NEJ_NDV_NJetX [ireg][icsrf] ->GetBinContent(ibin+1);
	  h_evt_cutflowEfficiency_signalRegionFull_NEJ_NDV_NJetX      [ireg][icsrf] ->Fill( ibin, ibin_cut / reg_count );
	  h_evt_cutflowTotalEfficiency_signalRegionFull_NEJ_NDV_NJetX [ireg][icsrf] ->Fill( ibin, ibin_cut / sumw_init );
	}
      }
      
    } // end if cutflow / abcd


    // track reconstruction efficiency
    if ( m_histoInfoSwitch->m_llpRecoEff || m_histoInfoSwitch->m_llptrkRecoEff ) {
      for ( size_t illp = 0; illp != h_LLPtrk_r [ireg].size(); ++illp ) {
	// --> inclusive tracking efficiency
	h_LLPtrk_recoEff_x     [ireg][illp] ->Divide( h_recoLLPtrk_x     [ireg][illp],
						      h_LLPtrk_x         [ireg][illp] );
	h_LLPtrk_recoEff_y     [ireg][illp] ->Divide( h_recoLLPtrk_y     [ireg][illp],
						      h_LLPtrk_y         [ireg][illp] );
	h_LLPtrk_recoEff_z     [ireg][illp] ->Divide( h_recoLLPtrk_z     [ireg][illp],
						      h_LLPtrk_z         [ireg][illp] );
	h_LLPtrk_recoEff_r     [ireg][illp] ->Divide( h_recoLLPtrk_r     [ireg][illp],
						      h_LLPtrk_r         [ireg][illp] );
	h_LLPtrk_recoEff_pt    [ireg][illp] ->Divide( h_recoLLPtrk_pt    [ireg][illp],
						      h_LLPtrk_pt        [ireg][illp] );
	h_LLPtrk_recoEff_eta   [ireg][illp] ->Divide( h_recoLLPtrk_eta   [ireg][illp],
						      h_LLPtrk_eta       [ireg][illp] );
	h_LLPtrk_recoEff_phi   [ireg][illp] ->Divide( h_recoLLPtrk_phi   [ireg][illp],
						      h_LLPtrk_phi       [ireg][illp] );
	h_LLPtrk_recoEff_d0    [ireg][illp] ->Divide( h_recoLLPtrk_d0    [ireg][illp],
						      h_LLPtrk_d0        [ireg][illp] );
	h_LLPtrk_recoEff_z0    [ireg][illp] ->Divide( h_recoLLPtrk_z0    [ireg][illp],
						      h_LLPtrk_z0        [ireg][illp] );
	h_LLPtrk_recoEff_avgMu [ireg][illp] ->Divide( h_recoLLPtrk_avgMu [ireg][illp],
						      h_LLPtrk_avgMu     [ireg][illp] );
	h_LLPtrk_recoEff_minDR [ireg][illp] ->Divide( h_recoLLPtrk_minDR [ireg][illp],
						      h_LLPtrk_minDR     [ireg][illp] );
	// --> standard tracking efficiency
	h_LLPtrk_stdEff_x      [ireg][illp] ->Divide( h_stdLLPtrk_x      [ireg][illp],
						      h_LLPtrk_x         [ireg][illp] );
	h_LLPtrk_stdEff_y      [ireg][illp] ->Divide( h_stdLLPtrk_y      [ireg][illp],
						      h_LLPtrk_y         [ireg][illp] );
	h_LLPtrk_stdEff_z      [ireg][illp] ->Divide( h_stdLLPtrk_z      [ireg][illp],
						      h_LLPtrk_z         [ireg][illp] );
	h_LLPtrk_stdEff_r      [ireg][illp] ->Divide( h_stdLLPtrk_r      [ireg][illp],
						      h_LLPtrk_r         [ireg][illp] );
	h_LLPtrk_stdEff_pt     [ireg][illp] ->Divide( h_stdLLPtrk_pt     [ireg][illp],
						      h_LLPtrk_pt        [ireg][illp] );
	h_LLPtrk_stdEff_eta    [ireg][illp] ->Divide( h_stdLLPtrk_eta    [ireg][illp],
						      h_LLPtrk_eta       [ireg][illp] );
	h_LLPtrk_stdEff_phi    [ireg][illp] ->Divide( h_stdLLPtrk_phi    [ireg][illp],
						      h_LLPtrk_phi       [ireg][illp] );
	h_LLPtrk_stdEff_d0     [ireg][illp] ->Divide( h_stdLLPtrk_d0     [ireg][illp],
						      h_LLPtrk_d0        [ireg][illp] );
	h_LLPtrk_stdEff_z0     [ireg][illp] ->Divide( h_stdLLPtrk_z0     [ireg][illp],
						      h_LLPtrk_z0        [ireg][illp] );
	h_LLPtrk_stdEff_avgMu  [ireg][illp] ->Divide( h_stdLLPtrk_avgMu  [ireg][illp],
						      h_LLPtrk_avgMu     [ireg][illp] );
	h_LLPtrk_stdEff_minDR  [ireg][illp] ->Divide( h_stdLLPtrk_minDR  [ireg][illp],
						      h_LLPtrk_minDR     [ireg][illp] );
	// --> large-radius tracking efficiency
	h_LLPtrk_lrtEff_x      [ireg][illp] ->Divide( h_lrtLLPtrk_x      [ireg][illp],
						      h_LLPtrk_x         [ireg][illp] );
	h_LLPtrk_lrtEff_y      [ireg][illp] ->Divide( h_lrtLLPtrk_y      [ireg][illp],
						      h_LLPtrk_y         [ireg][illp] );
	h_LLPtrk_lrtEff_z      [ireg][illp] ->Divide( h_lrtLLPtrk_z      [ireg][illp],
						      h_LLPtrk_z         [ireg][illp] );
	h_LLPtrk_lrtEff_r      [ireg][illp] ->Divide( h_lrtLLPtrk_r      [ireg][illp],
						      h_LLPtrk_r         [ireg][illp] );
	h_LLPtrk_lrtEff_pt     [ireg][illp] ->Divide( h_lrtLLPtrk_pt     [ireg][illp],
						      h_LLPtrk_pt        [ireg][illp] );
	h_LLPtrk_lrtEff_eta    [ireg][illp] ->Divide( h_lrtLLPtrk_eta    [ireg][illp],
						      h_LLPtrk_eta       [ireg][illp] );
	h_LLPtrk_lrtEff_phi    [ireg][illp] ->Divide( h_lrtLLPtrk_phi    [ireg][illp],
						      h_LLPtrk_phi       [ireg][illp] );
	h_LLPtrk_lrtEff_d0     [ireg][illp] ->Divide( h_lrtLLPtrk_d0     [ireg][illp],
						      h_LLPtrk_d0        [ireg][illp] );
	h_LLPtrk_lrtEff_z0     [ireg][illp] ->Divide( h_lrtLLPtrk_z0     [ireg][illp],
						      h_LLPtrk_z0        [ireg][illp] );
	h_LLPtrk_lrtEff_avgMu  [ireg][illp] ->Divide( h_lrtLLPtrk_avgMu  [ireg][illp],
						      h_LLPtrk_avgMu     [ireg][illp] );
	h_LLPtrk_lrtEff_minDR  [ireg][illp] ->Divide( h_lrtLLPtrk_minDR  [ireg][illp],
						      h_LLPtrk_minDR     [ireg][illp] );
      }
    }
    
    // vertex reconstruction efficiency
    if ( m_histoInfoSwitch->m_llpRecoEff || m_histoInfoSwitch->m_llpvtxRecoEff ) {
      for ( size_t illp = 0; illp != h_recobleLLPdVtx_r [ireg].size(); ++illp ) {
	// --> inclusive acceptance
	h_LLPdVtx_accept_x                [ireg][illp]    ->Divide( h_recoLLPdVtx_x                  [ireg][illp],
								    h_recobleLLPdVtx_x               [ireg][illp] );
	h_LLPdVtx_accept_y                [ireg][illp]    ->Divide( h_recoLLPdVtx_y                  [ireg][illp],
								    h_recobleLLPdVtx_y               [ireg][illp] );
	h_LLPdVtx_accept_z                [ireg][illp]    ->Divide( h_recoLLPdVtx_z                  [ireg][illp],
								    h_recobleLLPdVtx_z               [ireg][illp] );
    	h_LLPdVtx_accept_r                [ireg][illp]    ->Divide( h_recoLLPdVtx_r                  [ireg][illp],
								    h_recobleLLPdVtx_r               [ireg][illp] );
	h_LLPdVtx_accept_pt               [ireg][illp]    ->Divide( h_recoLLPdVtx_pt                 [ireg][illp],
								    h_recobleLLPdVtx_pt              [ireg][illp] );
	h_LLPdVtx_accept_eta              [ireg][illp]    ->Divide( h_recoLLPdVtx_eta                [ireg][illp],
								    h_recobleLLPdVtx_eta             [ireg][illp] );
	h_LLPdVtx_accept_phi              [ireg][illp]    ->Divide( h_recoLLPdVtx_phi                [ireg][illp],
								    h_recobleLLPdVtx_phi             [ireg][illp] );
	h_LLPdVtx_accept_avgMu            [ireg][illp]    ->Divide( h_recoLLPdVtx_avgMu              [ireg][illp],
								    h_recobleLLPdVtx_avgMu           [ireg][illp] );
	h_LLPdVtx_accept_descM            [ireg][illp]    ->Divide( h_recoLLPdVtx_descM              [ireg][illp],
								    h_recobleLLPdVtx_descM           [ireg][illp] );
	h_LLPdVtx_accept_nDesc            [ireg][illp]    ->Divide( h_recoLLPdVtx_nDesc              [ireg][illp],
								    h_recobleLLPdVtx_nDesc           [ireg][illp] );
	h_LLPdVtx_accept_nRecoDesc        [ireg][illp]    ->Divide( h_recoLLPdVtx_nRecoDesc          [ireg][illp],
								    h_recobleLLPdVtx_nRecoDesc       [ireg][illp] );
	h_LLPdVtx_accept_nSelDesc         [ireg][illp]    ->Divide( h_recoLLPdVtx_nSelDesc           [ireg][illp],
								    h_recobleLLPdVtx_nSelDesc        [ireg][illp] );
	// --> inclusive total efficiency
	h_LLPdVtx_recoEff_x               [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_x             [ireg][illp],
								    h_recobleLLPdVtx_x               [ireg][illp] );
	h_LLPdVtx_recoEff_y               [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_y             [ireg][illp],
								    h_recobleLLPdVtx_y               [ireg][illp] );
	h_LLPdVtx_recoEff_z               [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_z             [ireg][illp],
								    h_recobleLLPdVtx_z               [ireg][illp] );
	h_LLPdVtx_recoEff_r               [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_r             [ireg][illp],
								    h_recobleLLPdVtx_r               [ireg][illp] );
	h_LLPdVtx_recoEff_pt              [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_pt            [ireg][illp],
								    h_recobleLLPdVtx_pt              [ireg][illp] );
	h_LLPdVtx_recoEff_eta             [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_eta           [ireg][illp],
								    h_recobleLLPdVtx_eta             [ireg][illp] );
	h_LLPdVtx_recoEff_phi             [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_phi           [ireg][illp],
								    h_recobleLLPdVtx_phi             [ireg][illp] );
	h_LLPdVtx_recoEff_avgMu           [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_avgMu         [ireg][illp],
								    h_recobleLLPdVtx_avgMu           [ireg][illp] );
	h_LLPdVtx_recoEff_descM           [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_descM         [ireg][illp],
								    h_recobleLLPdVtx_descM           [ireg][illp] );
	h_LLPdVtx_recoEff_nDesc           [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_nDesc         [ireg][illp],
								    h_recobleLLPdVtx_nDesc           [ireg][illp] );
	h_LLPdVtx_recoEff_nRecoDesc       [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_nRecoDesc     [ireg][illp],
								    h_recobleLLPdVtx_nRecoDesc       [ireg][illp] );
	h_LLPdVtx_recoEff_nSelDesc        [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_nSelDesc      [ireg][illp],
								    h_recobleLLPdVtx_nSelDesc        [ireg][illp] );
	// --> inclusive algorithmic efficiency
	h_LLPdVtx_algEff_x                [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_x             [ireg][illp],
								    h_recoLLPdVtx_x                  [ireg][illp] );
	h_LLPdVtx_algEff_y                [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_y             [ireg][illp],
								    h_recoLLPdVtx_y                  [ireg][illp] );
	h_LLPdVtx_algEff_z                [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_z             [ireg][illp],
								    h_recoLLPdVtx_z                  [ireg][illp] );
	h_LLPdVtx_algEff_r                [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_r             [ireg][illp],
								    h_recoLLPdVtx_r                  [ireg][illp] );
	h_LLPdVtx_algEff_pt               [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_pt            [ireg][illp],
								    h_recoLLPdVtx_pt                 [ireg][illp] );
	h_LLPdVtx_algEff_eta              [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_eta           [ireg][illp],
								    h_recoLLPdVtx_eta                [ireg][illp] );
	h_LLPdVtx_algEff_phi              [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_phi           [ireg][illp],
								    h_recoLLPdVtx_phi                [ireg][illp] );
	h_LLPdVtx_algEff_avgMu            [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_avgMu         [ireg][illp],
								    h_recoLLPdVtx_avgMu              [ireg][illp] );
	h_LLPdVtx_algEff_descM            [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_descM         [ireg][illp],
								    h_recoLLPdVtx_descM              [ireg][illp] );
	h_LLPdVtx_algEff_nDesc            [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_nDesc         [ireg][illp],
								    h_recoLLPdVtx_nDesc              [ireg][illp] );
	h_LLPdVtx_algEff_nRecoDesc        [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_nRecoDesc     [ireg][illp],
								    h_recoLLPdVtx_nRecoDesc          [ireg][illp] );
	h_LLPdVtx_algEff_nSelDesc         [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_nSelDesc      [ireg][illp],
								    h_recoLLPdVtx_nSelDesc           [ireg][illp] );
	// --> inclusive core efficiency
	h_LLPdVtx_coreEff_x               [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_x             [ireg][illp],
								    h_selLLPdVtx_x                   [ireg][illp] );
	h_LLPdVtx_coreEff_y               [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_y             [ireg][illp],
								    h_selLLPdVtx_y                   [ireg][illp] );
	h_LLPdVtx_coreEff_z               [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_z             [ireg][illp],
								    h_selLLPdVtx_z                   [ireg][illp] );
	h_LLPdVtx_coreEff_r               [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_r             [ireg][illp],
								    h_selLLPdVtx_r                   [ireg][illp] );
	h_LLPdVtx_coreEff_pt              [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_pt            [ireg][illp],
								    h_selLLPdVtx_pt                  [ireg][illp] );
	h_LLPdVtx_coreEff_eta             [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_eta           [ireg][illp],
								    h_selLLPdVtx_eta                 [ireg][illp] );
	h_LLPdVtx_coreEff_phi             [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_phi           [ireg][illp],
								    h_selLLPdVtx_phi                 [ireg][illp] );
	h_LLPdVtx_coreEff_avgMu           [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_avgMu         [ireg][illp],
								    h_selLLPdVtx_avgMu               [ireg][illp] );
	h_LLPdVtx_coreEff_descM           [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_descM         [ireg][illp],
								    h_selLLPdVtx_descM               [ireg][illp] );
	h_LLPdVtx_coreEff_nDesc           [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_nDesc         [ireg][illp],
								    h_selLLPdVtx_nDesc               [ireg][illp] );
	h_LLPdVtx_coreEff_nRecoDesc       [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_nRecoDesc     [ireg][illp],
								    h_selLLPdVtx_nRecoDesc           [ireg][illp] );
	h_LLPdVtx_coreEff_nSelDesc        [ireg][illp]    ->Divide( h_recoMatchLLPdVtx_nSelDesc      [ireg][illp],
								    h_selLLPdVtx_nSelDesc            [ireg][illp] );
	// --> inclusive seed efficiency
	h_LLPdVtx_seedEff_x               [ireg][illp]    ->Divide( h_selLLPdVtx_x                   [ireg][illp],
								    h_recoLLPdVtx_x                  [ireg][illp] );
	h_LLPdVtx_seedEff_y               [ireg][illp]    ->Divide( h_selLLPdVtx_y                   [ireg][illp],
								    h_recoLLPdVtx_y                  [ireg][illp] );
	h_LLPdVtx_seedEff_z               [ireg][illp]    ->Divide( h_selLLPdVtx_z                   [ireg][illp],
								    h_recoLLPdVtx_z                  [ireg][illp] );
	h_LLPdVtx_seedEff_r               [ireg][illp]    ->Divide( h_selLLPdVtx_r                   [ireg][illp],
								    h_recoLLPdVtx_r                  [ireg][illp] );
	h_LLPdVtx_seedEff_pt              [ireg][illp]    ->Divide( h_selLLPdVtx_pt                  [ireg][illp],
								    h_recoLLPdVtx_pt                 [ireg][illp] );
	h_LLPdVtx_seedEff_eta             [ireg][illp]    ->Divide( h_selLLPdVtx_eta                 [ireg][illp],
								    h_recoLLPdVtx_eta                [ireg][illp] );
	h_LLPdVtx_seedEff_phi             [ireg][illp]    ->Divide( h_selLLPdVtx_phi                 [ireg][illp],
								    h_recoLLPdVtx_phi                [ireg][illp] );
	h_LLPdVtx_seedEff_avgMu           [ireg][illp]    ->Divide( h_selLLPdVtx_avgMu               [ireg][illp],
								    h_recoLLPdVtx_avgMu              [ireg][illp] );
	h_LLPdVtx_seedEff_descM           [ireg][illp]    ->Divide( h_selLLPdVtx_descM               [ireg][illp],
								    h_recoLLPdVtx_descM              [ireg][illp] );
	h_LLPdVtx_seedEff_nDesc           [ireg][illp]    ->Divide( h_selLLPdVtx_nDesc               [ireg][illp],
								    h_recoLLPdVtx_nDesc              [ireg][illp] );
	h_LLPdVtx_seedEff_nRecoDesc       [ireg][illp]    ->Divide( h_selLLPdVtx_nRecoDesc           [ireg][illp],
								    h_recoLLPdVtx_nRecoDesc          [ireg][illp] );
	h_LLPdVtx_seedEff_nSelDesc        [ireg][illp]    ->Divide( h_selLLPdVtx_nSelDesc            [ireg][illp],
								    h_recoLLPdVtx_nSelDesc           [ireg][illp] );
	// --> signal acceptance
	h_LLPdVtx_sgnlAccept_x            [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_x             [ireg][illp],
								    h_fiducLLPdVtx_x                 [ireg][illp] );
	h_LLPdVtx_sgnlAccept_y            [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_y             [ireg][illp],
								    h_fiducLLPdVtx_y                 [ireg][illp] );
	h_LLPdVtx_sgnlAccept_z            [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_z             [ireg][illp],
								    h_fiducLLPdVtx_z                 [ireg][illp] );
    	h_LLPdVtx_sgnlAccept_r            [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_r             [ireg][illp],
								    h_fiducLLPdVtx_r                 [ireg][illp] );
	h_LLPdVtx_sgnlAccept_pt           [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_pt            [ireg][illp],
								    h_fiducLLPdVtx_pt                [ireg][illp] );
	h_LLPdVtx_sgnlAccept_eta          [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_eta           [ireg][illp],
								    h_fiducLLPdVtx_eta               [ireg][illp] );
	h_LLPdVtx_sgnlAccept_phi          [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_phi           [ireg][illp],
								    h_fiducLLPdVtx_phi               [ireg][illp] );
	h_LLPdVtx_sgnlAccept_avgMu        [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_avgMu         [ireg][illp],
								    h_fiducLLPdVtx_avgMu             [ireg][illp] );
	h_LLPdVtx_sgnlAccept_descM        [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_descM         [ireg][illp],
								    h_fiducLLPdVtx_descM             [ireg][illp] );
	h_LLPdVtx_sgnlAccept_nDesc        [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_nDesc         [ireg][illp],
								    h_fiducLLPdVtx_nDesc             [ireg][illp] );
	h_LLPdVtx_sgnlAccept_nRecoDesc    [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_nRecoDesc     [ireg][illp],
								    h_fiducLLPdVtx_nRecoDesc         [ireg][illp] );
	h_LLPdVtx_sgnlAccept_nSelDesc     [ireg][illp]    ->Divide( h_recoFiducLLPdVtx_nSelDesc      [ireg][illp],
								    h_fiducLLPdVtx_nSelDesc          [ireg][illp] );
	for ( size_t k = 0; k != m_nTypeSgnlDVs; ++k ) {
	  // --> total signal efficiency
	  h_LLPdVtx_sgnlRecoEff_x         [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_x         [ireg][illp][k],
								    h_fiducLLPdVtx_x                 [ireg][illp] );
	  h_LLPdVtx_sgnlRecoEff_y         [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_y         [ireg][illp][k],
								    h_fiducLLPdVtx_y                 [ireg][illp] );
	  h_LLPdVtx_sgnlRecoEff_z         [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_z         [ireg][illp][k],
								    h_fiducLLPdVtx_z                 [ireg][illp] );
	  h_LLPdVtx_sgnlRecoEff_r         [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_r         [ireg][illp][k],
								    h_fiducLLPdVtx_r                 [ireg][illp] );
	  h_LLPdVtx_sgnlRecoEff_pt        [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_pt        [ireg][illp][k],
								    h_fiducLLPdVtx_pt                [ireg][illp] );
	  h_LLPdVtx_sgnlRecoEff_eta       [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_eta       [ireg][illp][k],
								    h_fiducLLPdVtx_eta               [ireg][illp] );
	  h_LLPdVtx_sgnlRecoEff_phi       [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_phi       [ireg][illp][k],
								    h_fiducLLPdVtx_phi               [ireg][illp] );
	  h_LLPdVtx_sgnlRecoEff_avgMu     [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_avgMu     [ireg][illp][k],
								    h_fiducLLPdVtx_avgMu             [ireg][illp] );
	  h_LLPdVtx_sgnlRecoEff_descM     [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_descM     [ireg][illp][k],
								    h_fiducLLPdVtx_descM             [ireg][illp] );
	  h_LLPdVtx_sgnlRecoEff_nDesc     [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_nDesc     [ireg][illp][k],
								    h_fiducLLPdVtx_nDesc             [ireg][illp] );
	  h_LLPdVtx_sgnlRecoEff_nRecoDesc [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_nRecoDesc [ireg][illp][k],
								    h_fiducLLPdVtx_nRecoDesc         [ireg][illp] );
	  h_LLPdVtx_sgnlRecoEff_nSelDesc  [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_nSelDesc  [ireg][illp][k],
								    h_fiducLLPdVtx_nSelDesc          [ireg][illp] );
	  // --> algorithmic signal efficiency
	  h_LLPdVtx_sgnlAlgEff_x          [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_x         [ireg][illp][k],
								    h_recoFiducLLPdVtx_x             [ireg][illp] );
	  h_LLPdVtx_sgnlAlgEff_y          [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_y         [ireg][illp][k],
								    h_recoFiducLLPdVtx_y             [ireg][illp] );
	  h_LLPdVtx_sgnlAlgEff_z          [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_z         [ireg][illp][k],
								    h_recoFiducLLPdVtx_z             [ireg][illp] );
	  h_LLPdVtx_sgnlAlgEff_r          [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_r         [ireg][illp][k],
								    h_recoFiducLLPdVtx_r             [ireg][illp] );
	  h_LLPdVtx_sgnlAlgEff_pt         [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_pt        [ireg][illp][k],
								    h_recoFiducLLPdVtx_pt            [ireg][illp] );
	  h_LLPdVtx_sgnlAlgEff_eta        [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_eta       [ireg][illp][k],
								    h_recoFiducLLPdVtx_eta           [ireg][illp] );
	  h_LLPdVtx_sgnlAlgEff_phi        [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_phi       [ireg][illp][k],
								    h_recoFiducLLPdVtx_phi           [ireg][illp] );
	  h_LLPdVtx_sgnlAlgEff_avgMu      [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_avgMu     [ireg][illp][k],
								    h_recoFiducLLPdVtx_avgMu         [ireg][illp] );
	  h_LLPdVtx_sgnlAlgEff_descM      [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_descM     [ireg][illp][k],
								    h_recoFiducLLPdVtx_descM         [ireg][illp] );
	  h_LLPdVtx_sgnlAlgEff_nDesc      [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_nDesc     [ireg][illp][k],
								    h_recoFiducLLPdVtx_nDesc         [ireg][illp] );
	  h_LLPdVtx_sgnlAlgEff_nRecoDesc  [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_nRecoDesc [ireg][illp][k],
								    h_recoFiducLLPdVtx_nRecoDesc     [ireg][illp] );
	  h_LLPdVtx_sgnlAlgEff_nSelDesc   [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_nSelDesc  [ireg][illp][k],
								    h_recoFiducLLPdVtx_nSelDesc      [ireg][illp] );
	  // --> core signal efficiency
	  h_LLPdVtx_sgnlCoreEff_x         [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_x         [ireg][illp][k],
								    h_selFiducLLPdVtx_x              [ireg][illp] );
	  h_LLPdVtx_sgnlCoreEff_y         [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_y         [ireg][illp][k],
								    h_selFiducLLPdVtx_y              [ireg][illp] );
	  h_LLPdVtx_sgnlCoreEff_z         [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_z         [ireg][illp][k],
								    h_selFiducLLPdVtx_z              [ireg][illp] );
	  h_LLPdVtx_sgnlCoreEff_r         [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_r         [ireg][illp][k],
								    h_selFiducLLPdVtx_r              [ireg][illp] );
	  h_LLPdVtx_sgnlCoreEff_pt        [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_pt        [ireg][illp][k],
								    h_selFiducLLPdVtx_pt             [ireg][illp] );
	  h_LLPdVtx_sgnlCoreEff_eta       [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_eta       [ireg][illp][k],
								    h_selFiducLLPdVtx_eta            [ireg][illp] );
	  h_LLPdVtx_sgnlCoreEff_phi       [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_phi       [ireg][illp][k],
								    h_selFiducLLPdVtx_phi            [ireg][illp] );
	  h_LLPdVtx_sgnlCoreEff_avgMu     [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_avgMu     [ireg][illp][k],
								    h_selFiducLLPdVtx_avgMu          [ireg][illp] );
	  h_LLPdVtx_sgnlCoreEff_descM     [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_descM     [ireg][illp][k],
								    h_selFiducLLPdVtx_descM          [ireg][illp] );
	  h_LLPdVtx_sgnlCoreEff_nDesc     [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_nDesc     [ireg][illp][k],
								    h_selFiducLLPdVtx_nDesc          [ireg][illp] );
	  h_LLPdVtx_sgnlCoreEff_nRecoDesc [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_nRecoDesc [ireg][illp][k],
								    h_selFiducLLPdVtx_nRecoDesc      [ireg][illp] );
	  h_LLPdVtx_sgnlCoreEff_nSelDesc  [ireg][illp][k] ->Divide( h_sgnlRecoMatchLLPdVtx_nSelDesc  [ireg][illp][k],
								    h_selFiducLLPdVtx_nSelDesc       [ireg][illp] );
	}
	// --> seed signal efficiency
	h_LLPdVtx_sgnlSeedEff_x           [ireg][illp]    ->Divide( h_selFiducLLPdVtx_x              [ireg][illp],
								    h_recoFiducLLPdVtx_x             [ireg][illp] );
	h_LLPdVtx_sgnlSeedEff_y           [ireg][illp]    ->Divide( h_selFiducLLPdVtx_y              [ireg][illp],
								    h_recoFiducLLPdVtx_y             [ireg][illp] );
	h_LLPdVtx_sgnlSeedEff_z           [ireg][illp]    ->Divide( h_selFiducLLPdVtx_z              [ireg][illp],
								    h_recoFiducLLPdVtx_z             [ireg][illp] );
	h_LLPdVtx_sgnlSeedEff_r           [ireg][illp]    ->Divide( h_selFiducLLPdVtx_r              [ireg][illp],
								    h_recoFiducLLPdVtx_r             [ireg][illp] );
	h_LLPdVtx_sgnlSeedEff_pt          [ireg][illp]    ->Divide( h_selFiducLLPdVtx_pt             [ireg][illp],
								    h_recoFiducLLPdVtx_pt            [ireg][illp] );
	h_LLPdVtx_sgnlSeedEff_eta         [ireg][illp]    ->Divide( h_selFiducLLPdVtx_eta            [ireg][illp],
								    h_recoFiducLLPdVtx_eta           [ireg][illp] );
	h_LLPdVtx_sgnlSeedEff_phi         [ireg][illp]    ->Divide( h_selFiducLLPdVtx_phi            [ireg][illp],
								    h_recoFiducLLPdVtx_phi           [ireg][illp] );
	h_LLPdVtx_sgnlSeedEff_avgMu       [ireg][illp]    ->Divide( h_selFiducLLPdVtx_avgMu          [ireg][illp],
								    h_recoFiducLLPdVtx_avgMu         [ireg][illp] );
	h_LLPdVtx_sgnlSeedEff_descM       [ireg][illp]    ->Divide( h_selFiducLLPdVtx_descM          [ireg][illp],
								    h_recoFiducLLPdVtx_descM         [ireg][illp] );
	h_LLPdVtx_sgnlSeedEff_nDesc       [ireg][illp]    ->Divide( h_selFiducLLPdVtx_nDesc          [ireg][illp],
								    h_recoFiducLLPdVtx_nDesc         [ireg][illp] );
	h_LLPdVtx_sgnlSeedEff_nRecoDesc   [ireg][illp]    ->Divide( h_selFiducLLPdVtx_nRecoDesc      [ireg][illp],
								    h_recoFiducLLPdVtx_nRecoDesc     [ireg][illp] );
	h_LLPdVtx_sgnlSeedEff_nSelDesc    [ireg][illp]    ->Divide( h_selFiducLLPdVtx_nSelDesc       [ireg][illp],
								    h_recoFiducLLPdVtx_nSelDesc      [ireg][illp] );
      }
    }
    
    
  } // end loop over regions
  
  return StatusCode::SUCCESS;
}



void EJsHistogramManager :: getTruthJetTypes ( int truthJet_index, std::vector<int>& truthJet )
{
  // test if truth jet passes cuts
  int allTJ      = 1;
  int leadTJ     = 0;
  int emergingTJ = 0;
  int qcdTJ      = 0;
  if ( truthJet_index < m_nJets ) leadTJ = 1;
  if (  m_truthJet_isDark ->at(truthJet_index) /*&& m_truthJet_darkPt ->at(truthJet_index) > 30*/ ) emergingTJ = 1; // change -- this branch doesn't exists
  if ( !m_truthJet_isDark ->at(truthJet_index) ) qcdTJ = 1;
  // fill truth jet pass/fail cut vector
  truthJet .push_back( allTJ                );
  truthJet .push_back( allTJ      && leadTJ );
  truthJet .push_back( emergingTJ           );
  truthJet .push_back( emergingTJ && leadTJ );
  truthJet .push_back( qcdTJ                );
  truthJet .push_back( qcdTJ      && leadTJ );
}



void EJsHistogramManager :: getJetTypes ( int jet_index, std::vector<int>& jet, const EJsHelper::BaseDV& base_dv,
					  bool doCombos, bool doEJ, bool doEJCuts )
{  
  // set vector of jet types (before truth matching)
  int allJet           = 1;
  int leadJet          = 0;
  // --> tight cuts
  int tightPtJet       = 0;
  int tightEtaJet      = 0;
  int tightMassJet     = 0;
  // --> n-sv kinematic cuts
  std::vector<int> svPtJet     ( m_nTypeJSVs * m_nJSVpt .size(), 0 );
  std::vector<int> svSumPtJet  ( m_nTypeJSVs * m_nJSVpt .size(), 0 );
  std::vector<int> svSumHtJet  ( m_nTypeJSVs * m_nJSVpt .size(), 0 );
  std::vector<int> svSumHJet   ( m_nTypeJSVs * m_nJSVh  .size(), 0 );
  // --> n-sv (trk) cuts
  std::vector<int> svNtrkJet   ( m_nTypeJSVs * m_nJSVtrk.size(), 0 );
  std::vector<int> svNjtrkJet  ( m_nTypeJSVs * m_nJSVtrk.size(), 0 );
  std::vector<int> svTrkJet    ( m_nTypeJSVs * m_nJSVtrk.size(), 0 );
  std::vector<int> svJet       ( m_nTypeJSVs * m_nJSV   .size(), 0 ); 
  // --> combo cuts
  int tightJet         = 0;
  std::vector<int> svPtTightJet    ( m_nTypeJSVs * m_nJSVpt .size(), 0 );
  std::vector<int> svSumPtTightJet ( m_nTypeJSVs * m_nJSVpt .size(), 0 );
  std::vector<int> svSumHtTightJet ( m_nTypeJSVs * m_nJSVpt .size(), 0 );
  std::vector<int> svSumHTightJet  ( m_nTypeJSVs * m_nJSVh  .size(), 0 );
  std::vector<int> svNtrkTightJet  ( m_nTypeJSVs * m_nJSVtrk.size(), 0 );
  std::vector<int> svNjtrkTightJet ( m_nTypeJSVs * m_nJSVtrk.size(), 0 );
  std::vector<int> svTrkTightJet   ( m_nTypeJSVs * m_nJSVtrk.size(), 0 );
  std::vector<int> svTightJet      ( m_nTypeJSVs * m_nJSV   .size(), 0 );

  // test if jet passes cuts
  // --> tight cuts
  if ( jet_index < m_nJets )
    leadJet       = 1;
  if ( m_jet_pt ->at(jet_index) > m_tightJetPt )
    tightPtJet    = 1;
  if ( fabs( m_jet_eta ->at(jet_index) ) < m_tightJetEta )
    tightEtaJet   = 1;
  if ( m_jet_M  ->at(jet_index) > m_tightJetM )
    tightMassJet  = 1;
  // --> n-sv kinematic (sum-p4) cuts
  TLorentzVector svP4sum;
  svP4sum.SetPtEtaPhiM( 0, 0, 0, 0 );
  std::vector<TLorentzVector> svSumP4   ( m_nTypeJSVs, svP4sum );
  std::vector<double>         svSumPt   ( m_nTypeJSVs, 0       );
  std::vector<double>         svSumHt   ( m_nTypeJSVs, 0       );
  std::vector<double>         svSumH    ( m_nTypeJSVs, 0       );
  // --> n-sv (trk) cuts
  std::vector<int>            n_svNtrk  ( m_nTypeJSVs, 0       );
  std::vector<int>            n_svNjtrk ( m_nTypeJSVs, 0       );
  std::vector<int>            n_svTrk   ( m_nTypeJSVs, 0       );
  std::vector<int>            n_sv      ( m_nTypeJSVs, 0       );
  // loop over matched secondary vertices
  for ( int jsv = 0; jsv != m_jet_secVtx_n ->at(jet_index); ++jsv ) {
    int   jetSvIx   = m_jet_secVtx_index ->at(jet_index)[jsv];
    float jetSvPt   = 0;
    float jetSvHt   = 0;
    float jetSvH    = 0;
    float jetSvEta  = 0;
    float jetSvPhi  = 0;
    float jetSvMass = 0;
    int   jetSvNtrk = 0;
    if      ( base_dv.type == EJsHelper::BARE     ) {
      jetSvPt   = m_secVtx_pt_bare    ->at(jetSvIx);
      jetSvHt   = m_secVtx_Ht_bare    ->at(jetSvIx);
      jetSvH    = m_secVtx_H_bare     ->at(jetSvIx);
      jetSvEta  = m_secVtx_eta_bare   ->at(jetSvIx);
      jetSvPhi  = m_secVtx_phi_bare   ->at(jetSvIx);
      jetSvMass = m_secVtx_mass_bare  ->at(jetSvIx);
      jetSvNtrk = m_secVtx_ntrk       ->at(jetSvIx);
    }
    else if ( base_dv.type == EJsHelper::CLEAN    ) {
      jetSvPt   = m_secVtx_pt_clean   ->at(jetSvIx);
      jetSvHt   = m_secVtx_Ht_clean   ->at(jetSvIx);
      jetSvH    = m_secVtx_H_clean    ->at(jetSvIx);
      jetSvEta  = m_secVtx_eta_clean  ->at(jetSvIx);
      jetSvPhi  = m_secVtx_phi_clean  ->at(jetSvIx);
      jetSvMass = m_secVtx_mass_clean ->at(jetSvIx);
      jetSvNtrk = m_secVtx_ntrk_clean ->at(jetSvIx);
    }
    else if ( base_dv.type == EJsHelper::FILTERED ) {
      jetSvPt   = m_secVtx_pt         ->at(jetSvIx);
      jetSvHt   = m_secVtx_Ht         ->at(jetSvIx);
      jetSvH    = m_secVtx_H          ->at(jetSvIx);
      jetSvEta  = m_secVtx_eta        ->at(jetSvIx);
      jetSvPhi  = m_secVtx_phi        ->at(jetSvIx);
      jetSvMass = m_secVtx_mass       ->at(jetSvIx);
      jetSvNtrk = m_secVtx_ntrk_filt  ->at(jetSvIx);
    }
    // else if ( base_dv.type == EJsHelper::TRIMMED ) {...}

    int jetSvNjtrk = 0;
    for ( int jsvtrk = 0; jsvtrk != m_secVtx_ntrk ->at(jetSvIx); ++jsvtrk ) {
      if ( base_dv.type == EJsHelper::CLEAN    && !m_secVtx_trk_isClean ->at(jetSvIx)[jsvtrk] ) continue;
      if ( base_dv.type == EJsHelper::FILTERED && !m_secVtx_trk_isFilt  ->at(jetSvIx)[jsvtrk] ) continue;
      // if ( base_dv.type == EJsHelper::TRIMMED && *track fails trimming cuts* ) continue;
      int jsvtrkIx = m_secVtx_trk_index ->at(jetSvIx)[jsvtrk];
      if ( m_trk_jetMatch    ->at(jsvtrkIx) &&
    	   m_trk_jetMatch_ID ->at(jsvtrkIx) == m_jet_ID ->at(jet_index) ) ++jetSvNjtrk;
    }

    TLorentzVector jetSvP4;
    jetSvP4.SetPtEtaPhiM( jetSvPt, jetSvEta, jetSvPhi, jetSvMass );
    
    std::vector<int> jetsv;
    //getDVTypes( jetSvIx, jetsv, base_dv, false, true );
    getDVTypes( jetSvIx, jetsv, base_dv, false, true, true, true ); // only want goodDVs (w/o jet cuts)
    // base sv
    if ( jetSvNtrk > 1 ) {
      svSumP4  [0] += jetSvP4;
      svSumPt  [0] += jetSvPt;
      svSumHt  [0] += jetSvHt;
      svSumH   [0] += jetSvH;
      n_svNtrk [0] += jetSvNtrk;
      n_svNjtrk[0] += jetSvNjtrk;
      ++n_sv   [0];
    }
    // loose-good sv
    if ( jetsv[jetsv.size()-3] ) {
      svSumP4  [1] += jetSvP4;
      svSumPt  [1] += jetSvPt;
      svSumHt  [1] += jetSvHt;
      svSumH   [1] += jetSvH;
      n_svNtrk [1] += jetSvNtrk;
      n_svNjtrk[1] += jetSvNjtrk;
      ++n_sv   [1];
    }
    // mid-good sv
    if ( jetsv[jetsv.size()-2] ) {
      svSumP4  [2] += jetSvP4;
      svSumPt  [2] += jetSvPt;
      svSumHt  [2] += jetSvHt;
      svSumH   [2] += jetSvH;
      n_svNtrk [2] += jetSvNtrk;
      n_svNjtrk[2] += jetSvNjtrk;
      ++n_sv   [2];
    }
    // tight-good sv
    if ( jetsv[jetsv.size()-1] ) {
      svSumP4  [3] += jetSvP4;
      svSumPt  [3] += jetSvPt;
      svSumHt  [3] += jetSvHt;
      svSumH   [3] += jetSvH;
      n_svNtrk [3] += jetSvNtrk;
      n_svNjtrk[3] += jetSvNjtrk;
      ++n_sv   [3];
    }
  }
  // loop over matched tracks
  for ( int jtrk = 0; jtrk != m_jet_trk_n ->at(jet_index); ++jtrk ) {
    int jetTrkIx   = m_jet_trk_index ->at(jet_index)[jtrk];
    std::vector<int> jettrk;
    getTrkTypes( jetTrkIx, jettrk, base_dv );
    // base sv trk
    if ( jettrk[jettrk.size()-4] )
      ++n_svTrk[0];
    // loose-good sv trk
    if ( jettrk[jettrk.size()-3] )
      ++n_svTrk[1];
    // mid-good sv trk
    if ( jettrk[jettrk.size()-2] )
      ++n_svTrk[2];
    // tight-good sv trk
    if ( jettrk[jettrk.size()-1] )
      ++n_svTrk[3];
  }

  // --> n-sv pt cuts
  for ( size_t ijsvp4 = 0; ijsvp4 != svSumP4.size(); ++ijsvp4 )
    for ( size_t insvpt = 0; insvpt != m_nJSVpt.size(); ++insvpt )
      if ( svSumP4[ijsvp4].Pt() > m_nJSVpt[insvpt] ) svPtJet[ijsvp4*m_nJSVpt.size()+insvpt] = 1;
  // --> n-sv sum-pt cuts
  for ( size_t ijsvpt = 0; ijsvpt != svSumPt.size(); ++ijsvpt )
    for ( size_t insvpt = 0; insvpt != m_nJSVpt.size(); ++insvpt )
      if ( svSumPt[ijsvpt] > m_nJSVpt[insvpt] ) svSumPtJet[ijsvpt*m_nJSVpt.size()+insvpt] = 1;
  // --> n-sv sum-ht cuts
  for ( size_t ijsvht = 0; ijsvht != svSumHt.size(); ++ijsvht )
    for ( size_t insvpt = 0; insvpt != m_nJSVpt.size(); ++insvpt )
      if ( svSumHt[ijsvht] > m_nJSVpt[insvpt] ) svSumHtJet[ijsvht*m_nJSVpt.size()+insvpt] = 1;
  // --> n-sv sum-h cuts
  for ( size_t ijsvh = 0; ijsvh != svSumH.size(); ++ijsvh )
    for ( size_t insvh = 0; insvh != m_nJSVh.size(); ++insvh )
      if ( svSumH[ijsvh] > m_nJSVh[insvh] ) svSumHJet[ijsvh*m_nJSVh.size()+insvh] = 1;
  // --> n-sv ntrk cuts
  for ( size_t ijsvnt = 0; ijsvnt != n_svNtrk.size(); ++ijsvnt )
    for ( size_t insvt = 0; insvt != m_nJSVtrk.size(); ++insvt )
      if ( n_svNtrk[ijsvnt] > m_nJSVtrk[insvt]-1 ) svNtrkJet[ijsvnt*m_nJSVtrk.size()+insvt] = 1;
  // --> n-sv njtrk cuts
  for ( size_t ijsvnjt = 0; ijsvnjt != n_svNjtrk.size(); ++ijsvnjt )
    for ( size_t insvt = 0; insvt != m_nJSVtrk.size(); ++insvt )
      if ( n_svNjtrk[ijsvnjt] > m_nJSVtrk[insvt]-1 ) svNjtrkJet[ijsvnjt*m_nJSVtrk.size()+insvt] = 1;
  // --> n-sv-trk cuts
  for ( size_t ijsvt = 0; ijsvt != n_svTrk.size(); ++ijsvt )
    for ( size_t insvt = 0; insvt != m_nJSVtrk.size(); ++insvt )
      if ( n_svTrk[ijsvt] > m_nJSVtrk[insvt]-1 ) svTrkJet[ijsvt*m_nJSVtrk.size()+insvt] = 1;
  // --> n-sv cuts
  for ( size_t ijsv = 0; ijsv != n_sv.size(); ++ijsv )
    for ( size_t insv = 0; insv != m_nJSV.size(); ++insv )
      if ( n_sv[ijsv] > m_nJSV[insv]-1 ) svJet[ijsv*m_nJSV.size()+insv] = 1;
  
  // fill jet pass/fail cut vector
  // --> do cuts for EJ cutflows
  if ( doEJCuts ) {
    // loop over sv types -- easiest to just fill all jet types for each cutflow, rather than common ones for all and sv-specific ones for some
    for ( size_t isv = 0; isv != svSumP4.size(); ++isv ) {
      jet .push_back( allJet   );
      jet .push_back( leadJet  );
      jet .push_back( tightPtJet              );
      jet .push_back( tightPtJet   && leadJet );
      jet .push_back( tightEtaJet             );
      jet .push_back( tightEtaJet  && leadJet );
      jet .push_back( tightMassJet            );
      jet .push_back( tightMassJet && leadJet );
      jet .push_back( svPtJet    [isv*m_nJSVpt .size()  ]            );
      jet .push_back( svPtJet    [isv*m_nJSVpt .size()  ] && leadJet );
      jet .push_back( svNjtrkJet [isv*m_nJSVtrk.size()  ]            );
      jet .push_back( svNjtrkJet [isv*m_nJSVtrk.size()  ] && leadJet );
      jet .push_back( svPtJet    [isv*m_nJSVpt .size()+1]            );
      jet .push_back( svPtJet    [isv*m_nJSVpt .size()+1] && leadJet );
      jet .push_back( svNjtrkJet [isv*m_nJSVtrk.size()+1]            );
      jet .push_back( svNjtrkJet [isv*m_nJSVtrk.size()+1] && leadJet );
    } 
  }
  else {
    jet   .push_back( allJet   );
    jet   .push_back( leadJet  );
    // --> tight cuts
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_tightJets ) {
      jet   .push_back( tightPtJet               );
      jet   .push_back( tightPtJet    && leadJet );
      jet   .push_back( tightEtaJet              );
      jet   .push_back( tightEtaJet   && leadJet );
      jet   .push_back( tightMassJet             );
      jet   .push_back( tightMassJet  && leadJet );
    }
    // --> n-sv pt cuts
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvP4Jets ) {
      for ( const auto& svp4j : svPtJet ) {
	jet .push_back( svp4j            );
	jet .push_back( svp4j && leadJet );
      }
    }
    // --> n-sv sum-pt cuts
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvPtJets ) {
      for ( const auto& svptj : svSumPtJet ) {
	jet .push_back( svptj            );
	jet .push_back( svptj && leadJet );
      }
    }
    // --> n-sv sum-Ht cuts
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHtJets ) {
      for ( const auto& svhtj : svSumHtJet ) {
	jet .push_back( svhtj            );
	jet .push_back( svhtj && leadJet );
      }
    }
    // --> n-sv sum-H cuts
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvHJets ) {
      for ( const auto& svhj : svSumHJet ) {
	jet .push_back( svhj            );
	jet .push_back( svhj && leadJet );
      }
    }
    // --> n-sv ntrk cuts
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNtrkJets ) {
      for ( const auto& svntj : svNtrkJet ) {
	jet .push_back( svntj            );
	jet .push_back( svntj && leadJet );
      }
    }
    // --> n-sv njtrk cuts
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNjtrkJets ) {
      for ( const auto& svnjtj : svNjtrkJet ) {
	jet .push_back( svnjtj            );
	jet .push_back( svnjtj && leadJet );
      }
    }
    // --> n-sv-trk cuts
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvTrkJets ) {
      for ( const auto& svtj : svTrkJet ) {
	jet .push_back( svtj            );
	jet .push_back( svtj && leadJet );
      }
    }
    // --> n-sv cuts
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvJets ) { 
      for ( const auto& svj : svJet ) {
	jet .push_back( svj            );
	jet .push_back( svj && leadJet );
      }
    }
    // --> combo cuts
    if ( tightPtJet && tightEtaJet && tightMassJet ) tightJet = 1;
    if ( m_histoInfoSwitch->m_comboJets && doCombos ) {
      if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_tightJets ) {
	jet .push_back( tightJet                );
	jet .push_back( tightJet     && leadJet );
      }
      if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvP4Jets    ) )
	for ( const auto& svPtJ    : svPtJet    ) {
	  jet .push_back( svPtJ    && tightJet            );
	  jet .push_back( svPtJ    && tightJet && leadJet );
	}
      if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvPtJets    ) )
	for ( const auto& svSumPtJ : svSumPtJet ) {
	  jet .push_back( svSumPtJ && tightJet            );
	  jet .push_back( svSumPtJ && tightJet && leadJet );
	}
      if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvHtJets    ) )
	for ( const auto& svSumHtJ : svSumHtJet ) {
	  jet .push_back( svSumHtJ && tightJet            );
	  jet .push_back( svSumHtJ && tightJet && leadJet );
	}
      if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvHJets     ) )
	for ( const auto& svSumHJ  : svSumHJet  ) {
	  jet .push_back( svSumHJ  && tightJet            );
	  jet .push_back( svSumHJ  && tightJet && leadJet );
	}
      if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvNtrkJets  ) )
	for ( const auto& svNtrkJ  : svNtrkJet  ) {
	  jet .push_back( svNtrkJ  && tightJet            );
	  jet .push_back( svNtrkJ  && tightJet && leadJet );
	}
      if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvNjtrkJets ) )
	for ( const auto& svNjtrkJ : svNjtrkJet ) {
	  jet .push_back( svNjtrkJ && tightJet            );
	  jet .push_back( svNjtrkJ && tightJet && leadJet );
	}
      if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvTrkJets   ) )
	for ( const auto& svTrkJ   : svTrkJet   ) {
	  jet .push_back( svTrkJ   && tightJet            );
	  jet .push_back( svTrkJ   && tightJet && leadJet );
	}
      if ( m_histoInfoSwitch->m_typeJets || ( m_histoInfoSwitch->m_tightJets && m_histoInfoSwitch->m_nsvJets      ) )
	for ( const auto& svJ      : svJet      ) {
	  jet .push_back( svJ      && tightJet            );
	  jet .push_back( svJ      && tightJet && leadJet );
	}	
    }
  }

  // --> "emerging" jets
  if ( ( m_histoInfoSwitch->m_emergingJets || m_histoInfoSwitch->m_cutflow || m_histoInfoSwitch->m_abcdcutOnly ) && doEJ )
    for ( size_t isv = 0; isv != svSumP4.size(); ++isv ) {
      bool looseEmergingJet = allJet && tightPtJet && tightEtaJet && tightMassJet &&
	svPtJet [isv*m_nJSVpt.size()] && svNjtrkJet [isv*m_nJSVtrk.size()];
      bool tightEmergingJet = allJet && tightPtJet && tightEtaJet && tightMassJet &&
	svPtJet [isv*m_nJSVpt.size()  ] && svNjtrkJet [isv*m_nJSVtrk.size()  ] &&
	svPtJet [isv*m_nJSVpt.size()+1] && svNjtrkJet [isv*m_nJSVtrk.size()+1];
      jet .push_back( looseEmergingJet            );
      jet .push_back( looseEmergingJet && leadJet );
      jet .push_back( tightEmergingJet            );
      jet .push_back( tightEmergingJet && leadJet );
    }

  // truth matching (to dark jets) --> UPDATE: add dark-jet-pt cut
  bool darkJet    = false;
  bool nomatchJet = false;
  if ( m_mc ) {
    // require dark + truth jet match
    if ( m_jet_isDark ->at(jet_index) && m_jet_isTruth ->at(jet_index) ) {
      int truthIx = m_jet_truthIndex ->at(jet_index);
      int darkIx  = m_jet_darkIndex  ->at(jet_index);
      // require matched dark + truth jet also matched to one another
      if ( m_jet_darkID ->at(jet_index) == m_truthJet_darkID ->at(truthIx) )
	// require matched dark jet to pass pt quality cut
	if ( m_darkJet_pt ->at(darkIx) > 30 )
	  // require lead parton = down quark
	  if ( m_jet_partonID ->at(jet_index) == 1 )
	    darkJet = true;
    }
    if ( !darkJet ) nomatchJet = true;
    if ( m_histoInfoSwitch->m_jetTruth ) {
      std::vector<int> mJ = { darkJet, nomatchJet };
      std::vector<int> miJ;
      for ( size_t ij = 0; ij != jet.size(); ++ij )
	miJ .push_back( jet[ij] );
      for ( size_t ii = 0; ii != mJ.size(); ++ii )
	for ( size_t jj = 0; jj != miJ.size(); ++jj )
	  jet .push_back( mJ[ii] && miJ[jj] );
    }
  }
  
}



void EJsHistogramManager :: getTPTypes ( int tp_index, std::vector<int>& tp )
{
  bool xd   = false;
  bool qd   = false;
  bool pid  = false;
  bool rhod = false;
  if ( fabs( m_tp_pdgId ->at(tp_index) ) == 4900001 && m_tp_status      ->at(tp_index)   == 62      )
    xd = true;
  if ( fabs( m_tp_pdgId ->at(tp_index) ) == 4900101 && m_tp_status      ->at(tp_index)   == 71      )
    qd = true;
  if ( fabs( m_tp_pdgId ->at(tp_index) ) == 4900111 || fabs( m_tp_pdgId ->at(tp_index) ) == 4900211 )
    pid = true;
  if ( fabs( m_tp_pdgId ->at(tp_index) ) == 4900113 || fabs( m_tp_pdgId ->at(tp_index) ) == 4900213 )
    rhod = true;
  tp .push_back( xd   );
  tp .push_back( qd   );
  tp .push_back( pid  );
  tp .push_back( rhod );
}



void EJsHistogramManager :: getTrkTypes ( int trk_index, std::vector<int>& trk, const EJsHelper::BaseDV& base_dv )
{

  // eventually add info switch to turn loose,mid,tight-good SVs on/off (if we replace w/ singular "good" type)
  
  bool lrtTrk     = false;
  bool selTrk     = false;
  bool assocTrk   = false;
  bool svTrk      = false;
  bool lgoodsvTrk = false;
  bool mgoodsvTrk = false;
  bool tgoodsvTrk = false;
  if ( m_trk_isLRT     ->at(trk_index) ) lrtTrk   = true;
  if ( m_trk_isSel     ->at(trk_index) ) selTrk   = true;
  if ( m_trk_isAssoc   ->at(trk_index) ) assocTrk = true;
  if      ( base_dv.type == EJsHelper::BARE     ) {
    if ( m_trk_isSV      ->at(trk_index) ) svTrk = true;
  }
  else if ( base_dv.type == EJsHelper::CLEAN    ) {
    if ( m_trk_isCleanSV ->at(trk_index) ) svTrk = true;
  }
  else if ( base_dv.type == EJsHelper::FILTERED ) {
    if ( m_trk_isFiltSV  ->at(trk_index) ) svTrk = true;
  }
  // else if trimmed ...
  if ( svTrk ) {
    int trkSVix = m_trk_SV_index ->at(trk_index);
    std::vector<int> trkSV;
    getDVTypes ( trkSVix, trkSV, base_dv, false, false, true, true, true );
    lgoodsvTrk = trkSV[trkSV.size()-3];
    mgoodsvTrk = trkSV[trkSV.size()-2];
    tgoodsvTrk = trkSV[trkSV.size()-1];
  }
  trk .push_back( true       ); // all tracks
  trk .push_back( lrtTrk     );
  trk .push_back( selTrk     );
  trk .push_back( assocTrk   );
  trk .push_back( svTrk      );
  trk .push_back( lgoodsvTrk );
  trk .push_back( mgoodsvTrk );
  trk .push_back( tgoodsvTrk );
  
} // end getTrkTypes



void EJsHistogramManager :: getDVTypes ( int dv_index, std::vector<int>& dv, const EJsHelper::BaseDV& base_dv,
					 bool doCombos, bool jetDV, bool skipOneCuts, bool skipJetCuts, bool doGood, bool doGoodCuts )
{
  // separate chi2 cut from fiducial cut (for cutflow purposes); add material map cut
  
  // get kinematic variables
  float secVtx_pt    = 0;
  float secVtx_mass  = 0;
  float secVtx_mind0 = 0;
  int   secVtx_ntrk  = 0;
  if      ( base_dv.type == EJsHelper::BARE     ) {
    secVtx_pt    = m_secVtx_pt_bare     ->at(dv_index);
    secVtx_mass  = m_secVtx_mass_bare   ->at(dv_index);
    secVtx_mind0 = m_secVtx_mind0_bare  ->at(dv_index);
    secVtx_ntrk  = m_secVtx_ntrk        ->at(dv_index);
  }
  else if ( base_dv.type == EJsHelper::CLEAN    ) {
    secVtx_pt    = m_secVtx_pt_clean    ->at(dv_index);
    secVtx_mass  = m_secVtx_mass_clean  ->at(dv_index);
    secVtx_mind0 = m_secVtx_mind0_clean ->at(dv_index);
    secVtx_ntrk  = m_secVtx_ntrk_clean  ->at(dv_index);
  }
  else if ( base_dv.type == EJsHelper::FILTERED ) {
    secVtx_pt    = m_secVtx_pt          ->at(dv_index);
    secVtx_mass  = m_secVtx_mass        ->at(dv_index);
    secVtx_mind0 = m_secVtx_mind0       ->at(dv_index);
    secVtx_ntrk  = m_secVtx_ntrk_filt   ->at(dv_index);
  }
  // else if ( base_dv.type == EJsHelper::TRIMMED ) {...}
  // --> will have to loop over tracks and re-calculate kinematic variables using only trimmed tracks...
  // --> require final tracks in cleaning, filtering, trimming?

  float secVtx_minz0    = AlgConsts::maxValue;
  float secVtx_minerrd0 = AlgConsts::maxValue;
  float secVtx_minerrz0 = AlgConsts::maxValue;
  for ( int itrk = 0; itrk != m_secVtx_ntrk ->at(dv_index); ++itrk ) {
    if ( base_dv.type == EJsHelper::CLEAN    && !m_secVtx_trk_isClean ->at(dv_index)[itrk] ) continue;
    if ( base_dv.type == EJsHelper::FILTERED && !m_secVtx_trk_isFilt  ->at(dv_index)[itrk] ) continue;
    // if ( base_dv.type == EJsHelper::TRIMMED && *track fails trimming cuts* ) continue;
    int trkIx = m_secVtx_trk_index ->at(dv_index)[itrk];
    float fabsz0    = fabs( m_trk_z0 ->at(trkIx) );
    float trk_errd0 = m_trk_errd0    ->at(trkIx);
    float trk_errz0 = m_trk_errz0    ->at(trkIx);
    if ( fabsz0    < secVtx_minz0    ) secVtx_minz0    = fabsz0;
    if ( trk_errd0 < secVtx_minerrd0 ) secVtx_minerrd0 = trk_errd0;
    if ( trk_errz0 < secVtx_minerrz0 ) secVtx_minerrz0 = trk_errz0;
  }

  // test if DV passes cuts
  // --> base vertices (bare, clean, filtered, or trimmed)
  bool baseDV = false;
  if ( secVtx_ntrk > 1 ) baseDV = true;
  // --> material map veto
  bool matmapDV = true;
  if ( !m_secVtx_passMatVeto ->empty() )
    if ( !m_secVtx_passMatVeto ->at(dv_index) ) matmapDV = false;
  // --> fiducial volume vertices --> cut on r, z
  bool fiducDV = false;
  if ( m_secVtx_r ->at(dv_index) < 300 && fabs( m_secVtx_z ->at(dv_index) ) < 300 ) fiducDV = true;
  // --> good quality of fit vertices --> cut on chi2/ndof
  bool chi2DV = false;
  if ( m_secVtx_chi2 ->at(dv_index) < 5 ) chi2DV = true;
  // --> k-short-mass-cut vertices --> cut on vertex mass
  bool ksmDV = false;
  if ( secVtx_mass  > 0.7 ) ksmDV   = true;
  // --> low-pt cut
  bool ptDV = false;
  if ( secVtx_pt    > 2.5 ) ptDV    = true;
  // --> min-d0 cuts
  bool mind0DV  = false;
  if ( secVtx_mind0 <  10 ) mind0DV = true;
  // --> min-z0 cuts
  bool minz0DV = false;
  if ( secVtx_minz0 < 100 ) minz0DV = true;
  // --> min sqrt-error d0/z0 cuts
  // ... consider tightening (+ additional window cut b/w 0.5-1.0 for z0 (see double peak feature))
  bool minsqerrd0DV = false;
  bool minsqerrz0DV = false;
  if ( sqrt(sqrt(secVtx_minerrd0)) < 0.5 ) minsqerrd0DV = true;
  if ( sqrt(sqrt(secVtx_minerrz0)) < 1.5 ) minsqerrz0DV = true;
  // --> vertices near (leading) jets
  bool byJetDV  = false;
  bool byNJetDV = false;
  if ( m_secVtx_jetMatched ->at(dv_index) ) byJetDV = true;
  if ( m_secVtx_jetMatched ->at(dv_index) && m_secVtx_jetMatch_index ->at(dv_index) < m_nJets ) byNJetDV = true;

  // add explicit bare dv -- then only include in cutflow if baseDV != bare
  bool dv_base       = baseDV;
  bool dv_matmap     = baseDV && matmapDV;
  bool dv_fiduc      = baseDV && matmapDV && fiducDV;
  bool dv_chi2       = baseDV && matmapDV && chi2DV;
  bool dv_ksm        = baseDV && matmapDV && ksmDV;
  bool dv_pt         = baseDV && matmapDV && ptDV;
  bool dv_mind0      = baseDV && matmapDV && mind0DV;
  bool dv_minz0      = baseDV && matmapDV && minz0DV;
  bool dv_minsqerrd0 = baseDV && matmapDV && minsqerrd0DV;
  bool dv_minsqerrz0 = baseDV && matmapDV && minsqerrz0DV;
  bool dv_byjet      = baseDV && matmapDV && byJetDV;
  bool dv_bynjet     = baseDV && matmapDV && byNJetDV;
  if ( doCombos ) {
    dv_chi2       = dv_fiduc && chi2DV;
    dv_ksm        = dv_chi2  && ksmDV;
    dv_pt         = dv_ksm   && ptDV;
    dv_mind0      = dv_pt    && mind0DV;
    dv_minz0      = dv_pt    && minz0DV;
    dv_minsqerrd0 = dv_mind0 && dv_minz0 && minsqerrd0DV;
    dv_minsqerrz0 = dv_mind0 && dv_minz0 && minsqerrz0DV;
  }

  // fill (jet) DV pass/fail cut vector
  // --> may want to add cleaning / filtering bin for cutflow, but not necessary with baseline track cleaning ...
  // ... (doesn't remove any vertices from event)
  if ( !skipOneCuts ) {
    if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_baseVerts       ) ) ||
	 (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_baseJetVerts    ) ) ||
	 (  doGoodCuts ) )
      dv .push_back( dv_base   );
    if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_matmapVerts     ) ) ||
	 (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_matmapJetVerts  ) ) ||
	 (  doGoodCuts ) )
      dv .push_back( dv_matmap );
    if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_fiducVerts      ) ) ||
	 (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_fiducJetVerts   ) ) ||
	 (  doGoodCuts ) )
      dv .push_back( dv_fiduc  );
    if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_chi2Verts       ) ) ||
	 (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_chi2JetVerts    ) ) ||
	 (  doGoodCuts ) )
      dv .push_back( dv_chi2   );
    if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_ksmVerts        ) ) ||
	 (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_ksmJetVerts     ) ) ||
	 (  doGoodCuts ) )
      dv .push_back( dv_ksm    );
    if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_ptVerts         ) ) ||
	 (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_ptJetVerts      ) ) ||
	 (  doGoodCuts ) )
      dv .push_back( dv_pt     );
    if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_d0Verts         ) ) ||
	 (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_d0JetVerts      ) ) ||
	 (  doGoodCuts ) )
      dv .push_back( dv_mind0  );
    if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_z0Verts         ) ) ||
	 (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_z0JetVerts      ) ) ||
	 (  doGoodCuts ) )
      dv .push_back( dv_minz0  );
    if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_d0z0ErrVerts    ) ) ||
	 (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_d0z0ErrJetVerts ) ) ||
	 (  doGoodCuts ) ) {
      dv .push_back( dv_minsqerrd0 );
      dv .push_back( dv_minsqerrz0 );
    }
    if ( ( !skipJetCuts && !jetDV && ( m_histoInfoSwitch->m_vertices || m_histoInfoSwitch->m_byJetVerts ) ) ||
	 (  doGoodCuts ) ) {
      dv .push_back( dv_byjet  );
      dv .push_back( dv_bynjet );
    }
  }

  // --> "good" DVs
  bool looseGoodDV = baseDV && matmapDV && fiducDV && chi2DV && ksmDV;
  bool   midGoodDV = baseDV && matmapDV && fiducDV && chi2DV && ksmDV && ptDV;
  bool tightGoodDV = baseDV && matmapDV && fiducDV && chi2DV && ksmDV && ptDV && mind0DV && minz0DV && minsqerrd0DV && minsqerrz0DV;
  if ( doGood ) {
    if      ( !jetDV && !skipJetCuts ) {
      dv .push_back( looseGoodDV && byJetDV ); // byNJetDV
      dv .push_back(   midGoodDV && byJetDV );
      dv .push_back( tightGoodDV && byJetDV );
    }
    else if (  jetDV || skipJetCuts ) {
      dv .push_back( looseGoodDV );
      dv .push_back(   midGoodDV );
      dv .push_back( tightGoodDV );
    }
  }
  
  // --> truth matching --> test truth-matching criteria
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
    if ( m_secVtx_truth_n ->at(dv_index) ) {
      // get truth matches
      // --> for now, count every DV "DarkPion" llp decay truth match, regardless of match score, distance, other matches, etc.
      // --> will eventually want to choose singular best truth match if more than one ...
      // ... and cut on some combination of score, distance, corresponding truth vertex parameters ...
      // ... (like number of [reco/selected] descendants, "isReconstructible" flag), etc.
      // --> to choose single best match, look at match score first (choose highest), then (residual) distance (choose lowest)
      for ( int itruth = 0; itruth != m_secVtx_truth_n ->at(dv_index); ++itruth ) {
	// matching criteria:
	// --> v0 = match score > 0; no requirement on number / type of truth matches (may be matched to both multiple llps)
	if ( m_secVtx_truth_llp ->at(dv_index)[itruth] == "DarkPion" ) darkPionDV = true;
	if ( m_secVtx_truth_llp ->at(dv_index)[itruth] == "Kshort"   ) kshortDV   = true;
      }
    }
    if ( !darkPionDV && !kshortDV ) nomatchDV = true;
    if ( ( !jetDV && m_histoInfoSwitch->m_vtxTruth ) || ( jetDV && m_histoInfoSwitch->m_jetVtxTruth ) ) {
      //std::vector<int> mdv = { darkPionDV,  kshortDV, nomatchDV };
      std::vector<int> mdv = { darkPionDV };
      std::vector<int> midv;
      for ( size_t idv = 0; idv != dv.size(); ++idv )
	midv .push_back( dv[idv] );
      for ( size_t ii = 0; ii != mdv.size(); ++ii )
	for ( size_t jj = 0; jj != midv.size(); ++jj )
	  dv .push_back( baseDV && mdv[ii] && midv[jj] );
    }
  }
  
} // end getDVTypes



void EJsHistogramManager :: getLLPTypes ( int llp_index, std::vector<int>& llp )
{
  // test if llp decay passes cuts
  // --> dark pion / k-short decays
  int pidLLP = 0;
  int ksLLP  = 0;
  if ( m_truthVtx_llp ->at(llp_index) == "DarkPion" ) pidLLP = 1;
  if ( m_truthVtx_llp ->at(llp_index) == "Kshort"   ) ksLLP  = 1;

  // fill llp decay pass/fail cut vector
  if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_darkPions )
    llp .push_back( pidLLP );
  if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_kshorts   )
    llp .push_back( ksLLP  );
  
} // end getLLPTypes



int EJsHistogramManager :: getLLPDescTypes ( int llpDesc_ID, std::vector<int>& llpdesc )
{
  int ancestor_index = -1;
  
  // check if particle available in ntuples
  bool goodTP        = false;
  int  llpDesc_index = 0;
  for ( int i = 0; i != m_tp_n; ++i )
    if ( llpDesc_ID == m_tp_ID ->at(i) ) {
      goodTP = true;
      llpDesc_index = i;
    }
  if ( !goodTP ) return ancestor_index;

  // test if llp descendant passes cuts
  int pidLLPDesc     =  0;
  int ksLLPDesc      =  0;
  if ( m_tp_isDesc ->at(llpDesc_index) ) {
    for ( size_t i = 0; i != m_tp_ancest_llp ->at(llpDesc_index).size(); ++i ) {
      // --> dark pion descendant
      if ( m_tp_ancest_llp ->at(llpDesc_index)[i] == "DarkPion" ) pidLLPDesc = 1;
      // --> k-short descendant
      if ( m_tp_ancest_llp ->at(llpDesc_index)[i] == "Kshort"   ) ksLLPDesc  = 1;
    }
    ancestor_index = m_tp_ancest_index ->at(llpDesc_index)[0];
  }
  
  // fill llp descendant pass/fail cut vector
  if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_darkPions )
    llpdesc .push_back( pidLLPDesc );
  if ( m_histoInfoSwitch->m_llps || m_histoInfoSwitch->m_kshorts   )
    llpdesc .push_back( ksLLPDesc  );

  return ancestor_index;
  
} // end getLLPDescTypes
