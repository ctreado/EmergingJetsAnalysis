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
  m_jetStr             = jetStr;
  m_jetStrOth          = ( jetStr == "EMTopo" ) ? "PFlow" : "EMTopo";
  m_nEvents_init       = metadata.find( "eventCount_init" )->second;
  m_nEvents_sel        = metadata.find( "eventCount_sel"  )->second;
  m_sumw_init          = metadata.find( "sumw_init"       )->second;
  m_sumw_sel           = metadata.find( "sumw_sel"        )->second;
  m_sumw2_init         = metadata.find( "sumw2_init"      )->second;
  m_sumw2_sel          = metadata.find( "sumw2_sel"       )->second;
  m_xsec               = metadata.find( "crossSection"    )->second;
  m_kfactor            = metadata.find( "kFactor"         )->second;
  m_filteff            = metadata.find( "genFilterEff"    )->second;
  m_lumi               = lumi;
  m_debug              = debug;
  m_mc                 = mc;
  m_unblind            = unblind;
  m_numLeadJets        = m_histoInfoSwitch->m_numLeadingJets;
  m_numVtxTrks         = m_histoInfoSwitch->m_numVtxTrks;

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
  
  // other jet branches
  m_jetOth_n       = 0;
  m_jetOth_pt      = new std::vector<float>;
  m_jetOth_eta     = new std::vector<float>;
  m_jetOth_passJVT = new std::vector<int>;

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
  m_secVtx_H               = new std::vector<float>;
  m_secVtx_Ht              = new std::vector<float>;
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
  delete m_secVtx_H;
  delete m_secVtx_Ht;
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

  connectBranch<int>     ( name, tree, "ID",              &m_truthJet_ID        );
  connectBranch<int>     ( name, tree, "index",           &m_truthJet_index     );
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

  connectBranch<int> ( name, tree, "ID",              &m_darkJet_ID       );
  connectBranch<int> ( name, tree, "index",           &m_darkJet_index    );
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
  connectBranch<float> ( name, tree, "H",                   &m_secVtx_H               );
  connectBranch<float> ( name, tree, "Ht",                  &m_secVtx_Ht              );
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
  connectBranch<float> ( name, tree, "H_clean",             &m_secVtx_H_clean         );
  connectBranch<float> ( name, tree, "Ht_clean",            &m_secVtx_Ht_clean        );
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
  connectBranch<float> ( name, tree, "H_bare",              &m_secVtx_H_bare          );
  connectBranch<float> ( name, tree, "Ht_bare",             &m_secVtx_Ht_bare         );
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
  std::string tightptJ       = "TightPt";
  std::string tightetaJ      = "TightEta";
  std::string tightmJ        = "TightMass";
  std::string tightptJstr    = "tight-pt";
  std::string tightetaJstr   = "tight-eta";
  std::string tightmJstr     = "tight-mass";
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
  std::vector<std::string> gJSV = { "loose", "mid", "tight" };
  std::vector<std::string> JSV;
  std::vector<std::string> JSVstr;
  JSV    .push_back( baseJSVup    +  "SV" );
  JSVstr .push_back( base_dv.name + "-SV" );
  for ( size_t ijsv = 0; ijsv != gJSV.size(); ++ijsv ) {
    std::string gJSVup = gJSV[ijsv]; gJSVup[0] = toupper(gJSVup[0]);
    JSV    .push_back( gJSVup     + "GoodSV"   );
    JSVstr .push_back( gJSV[ijsv] + "-good-SV" );
  }

  int n_svj_ix = 0;
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
    ++n_svj_ix;
    //m_svNtrkJ_ix  = n_svj_ix;
  }
  // --> n-sv njtrk jet cuts
  m_svNjtrkJ_ix = m_nType1SVJs;
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNjtrkJets ) {
    for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
      for ( const auto& injsvt : m_nJSVtrk ) {
	std::string snjsvt     = std::to_string(injsvt);
	std::string hnJSVnJT    = JSV[ijsv] + "Njtrk" + snjsvt;
	std::string hnJSVnJTstr = snjsvt + "-" + JSVstr[ijsv] + "-Njtrk";
	hJ    .push_back( hnJSVnJT    );
	hJstr .push_back( hnJSVnJTstr );
	hJ    .push_back( leadJ    +       hnJSVnJT    );
	hJstr .push_back( leadJstr + " " + hnJSVnJTstr );
      }
    }
    m_nType1SVJs += JSV.size() * m_nJSVtrk.size() * m_LJix;
    ++n_svj_ix;
    //m_svNjtrkJ_ix = n_svj_ix;
  }
  // --> n-sv-trk jet cuts
  m_svTrkJ_ix = m_nType1SVJs;
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvTrkJets ) {
    for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
      for ( const auto& injsvt : m_nJSVtrk ) {
	std::string snjsvt     = std::to_string(injsvt);
	std::string hnJSVT    = JSV[ijsv] + "trk" + snjsvt;
	std::string hnJSVTstr = snjsvt + "-" + JSVstr[ijsv] + "-trk";
	hJ    .push_back( hnJSVT    );
	hJstr .push_back( hnJSVTstr );
	hJ    .push_back( leadJ    +       hnJSVT    );
	hJstr .push_back( leadJstr + " " + hnJSVTstr );
      }
    }
    m_nType1SVJs += JSV.size() * m_nJSVtrk.size() * m_LJix;
    ++n_svj_ix;
    //m_svTrkJ_ix   = n_svj_ix;
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
    ++n_svj_ix;
    //m_svNJ_ix     = n_svj_ix;
  }

  // number of individual jet cuts
  m_nType1Js  = hJ .size();

  // --> combination jet cuts
  std::string tightJ    = "Tight";
  std::string tightJstr = "tight";
  if ( m_histoInfoSwitch->m_comboJets )
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_tightJets ) {
      // tight jets
      hJ    .push_back( tightJ    );
      hJstr .push_back( tightJstr );
      // --> lead tight jets (N top-pt tight)
      hJ    .push_back( leadJ    +       tightJ    );
      hJstr .push_back( leadJstr + " " + tightJstr );
    }

  // // --> "EJ" jets -- tentative set of cuts to define emerging-like jet
  // std::vector<std::string> hEJstr;
  // hEJstr .push_back( baseJstr      );
  // hEJstr .push_back( tightptJstr   );
  // hEJstr .push_back( tightetaJstr  );
  // hEJstr .push_back( tightmJstr    );
  // hEJstr .push_back( ngoodsv1Jstr  );
  // hEJstr .push_back( ngoodsv2Jstr  );
  // std::string EJ    = "Emerging";
  // std::string EJstr = "emerging";
  // hJ    .push_back(                  EJ    );
  // hJ    .push_back( leadJ    +       EJ    );
  // hJstr .push_back(                  EJstr );
  // hJstr .push_back( leadJstr + " " + EJstr );
  
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
  

  // --> secondary vertices
  std::vector<std::string> hDV,  hDVstr;
  std::vector<std::string> hJDV, hJDVstr;
  // base vertices (bare or clean or filtered or custom-trimmed --> starting point for all further cuts)
  std::string baseDV    = "";
  std::string baseDVstr = base_dv.name + ",";
  if      ( base_dv.type == EJsHelper::BARE     ) baseDV = "Bare";
  else if ( base_dv.type == EJsHelper::CLEAN    ) baseDV = "Clean";
  else if ( base_dv.type == EJsHelper::FILTERED ) baseDV = "Filt";
  else if ( base_dv.type == EJsHelper::TRIMMED  ) baseDV = "Trim";
  if ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_baseVerts    ) {
    hDV     .push_back( baseDV    );
    hDVstr  .push_back( baseDVstr );
  }
  if ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_baseJetVerts ) {
    hJDV    .push_back( baseDV    );
    hJDVstr .push_back( baseDVstr );
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
  // vertices passing fiducial cuts (fiducial volume, chi2)
  std::string fidDV    = "Fiduc";
  std::string fidDVstr = "fiduc,";
  if ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_fiducVerts    ) {
    hDV     .push_back( fidDV    );
    hDVstr  .push_back( fidDVstr );
  }
  if ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_fiducJetVerts ) {
    hJDV    .push_back( fidDV    );
    hJDVstr .push_back( fidDVstr );
  }
  // vertices w/ k-short mass window removed
  std::string ksmDV    = "Ksm";
  std::string ksmDVstr = "ksm,";
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
  std::string mind0DVstr = "mind0,";
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
  std::string minz0DVstr = "minz0,";
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
  std::string minsqerrd0DVstr = "minsqerrd0,";
  std::string minsqerrz0DVstr = "minsqerrz0,";
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

  // number of individual (jet) DV cuts
  m_nType1DVs  = hDV .size();
  m_nType1JDVs = hJDV.size();
  
  // --> do combinations
  
  // --> "good" DVs -- tentatively = combo of all above cuts
  std::vector<std::string> hGDVstr;
  hGDVstr .push_back( baseDVstr       );
  hGDVstr .push_back( jDVstr          );
  hGDVstr .push_back( ljDVstr         );
  hGDVstr .push_back( fidDVstr        );
  hGDVstr .push_back( ksmDVstr        );
  hGDVstr .push_back( ptDVstr         );
  hGDVstr .push_back( mind0DVstr      );
  hGDVstr .push_back( minz0DVstr      );
  hGDVstr .push_back( minsqerrd0DVstr );
  hGDVstr .push_back( minsqerrz0DVstr );
  std::string goodDV    = "Good";
  std::string goodDVstr = "good,";
  hDV     .push_back( "Loose"  + goodDV    );
  hJDV    .push_back( "Loose"  + goodDV    );
  hDVstr  .push_back( "loose-" + goodDVstr );
  hJDVstr .push_back( "loose-" + goodDVstr );
  hDV     .push_back( "Mid"    + goodDV    );
  hJDV    .push_back( "Mid"    + goodDV    );
  hDVstr  .push_back( "mid-"   + goodDVstr );
  hJDVstr .push_back( "mid-"   + goodDVstr );
  hDV     .push_back( "Tight"  + goodDV    );
  hJDV    .push_back( "Tight"  + goodDV    );
  hDVstr  .push_back( "tight-" + goodDVstr );
  hJDVstr .push_back( "tight-" + goodDVstr );

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
  

  // loop over regions + book histograms
  for ( size_t ireg = 0; ireg != regions.size(); ++ireg ) {
    const EJsHelper::Region region = regions[ireg];
    const std::string       name   = m_name + outFileName + "/" + region.name + "/";

    // initialize count vectors
    m_nEntries                  .push_back( 0 );
    m_nWeightedEntries          .push_back( 0 );
    if ( m_histoInfoSwitch->m_trigTest ) {
      m_nFourJets               .push_back( 0 );
      m_nSearch                 .push_back( 0 );
      m_nTrig_4j120             .push_back( 0 );
      m_nOffTrig_4j120          .push_back( 0 );
      m_nOffTrig_4j120_other    .push_back( 0 );
      m_nOffTrigJVT_4j120       .push_back( 0 );
      m_nOffTrigJVT_4j120_other .push_back( 0 );
      m_nTrig_fourJet           .push_back( 0 );
      m_nOffTrig_fourJet        .push_back( 0 );
      m_nOthOffTrig_fourJet     .push_back( 0 );
      m_nOffTrigJVT_fourJet     .push_back( 0 );
      m_nOthOffTrigJVT_fourJet  .push_back( 0 );
      m_nTrig_search            .push_back( 0 );
      m_nOffTrig_search         .push_back( 0 );
      m_nOthOffTrig_search      .push_back( 0 );
      m_nOffTrigJVT_search      .push_back( 0 );
      m_nOthOffTrigJVT_search   .push_back( 0 );
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
    h_NJetHt      .push_back( book( name, "NJetHt",      "leading N " + m_jetStr + " Jet H_{T} [GeV]",            100, njetht_xmin, 4000 ) );
    h_NJetHt_vrsh .push_back( book( name, "NJetHt_vrsh", "leading N " + m_jetStr + " Jet H_{T} [GeV] (VR-shift)", 100, njetht_xmin, 4000 ) );

    
    // --- RECO JETS --- //
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
    std::vector<TH1F*> h_jj_dR;
    std::vector<TH1F*> h_jj_avg_pt;
    std::vector<TH1F*> h_jj_avg_eta;
    std::vector<TH1F*> h_jj_avg_phi;
    std::vector<TH1F*> h_jj_avg_m;
    std::vector<TH1F*> h_jj_avg_sumPt;
    std::vector<TH1F*> h_jj_avg_dR;
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
    std::vector<std::vector<TH1F*>> h_jj_max_ntrk;
    std::vector<std::vector<TH1F*>> h_jj_max_ntrk_pt;
    std::vector<std::vector<TH1F*>> h_jj_max_ntrk_eta;
    std::vector<std::vector<TH1F*>> h_jj_max_ntrk_phi;
    std::vector<std::vector<TH1F*>> h_jj_max_ntrk_m;
    std::vector<std::vector<TH1F*>> h_jj_max_ntrk_sumPt;
    std::vector<std::vector<TH1F*>> h_jj_min_ntrk;
    std::vector<std::vector<TH1F*>> h_jj_min_ntrk_pt;
    std::vector<std::vector<TH1F*>> h_jj_min_ntrk_eta;
    std::vector<std::vector<TH1F*>> h_jj_min_ntrk_phi;
    std::vector<std::vector<TH1F*>> h_jj_min_ntrk_m;
    std::vector<std::vector<TH1F*>> h_jj_min_ntrk_sumPt;
    std::vector<std::vector<TH1F*>> h_jj_max_nsv;
    std::vector<std::vector<TH1F*>> h_jj_max_nsv_pt;
    std::vector<std::vector<TH1F*>> h_jj_max_nsv_eta;
    std::vector<std::vector<TH1F*>> h_jj_max_nsv_phi;
    std::vector<std::vector<TH1F*>> h_jj_max_nsv_m;
    std::vector<std::vector<TH1F*>> h_jj_max_nsv_sumPt;
    std::vector<std::vector<TH1F*>> h_jj_min_nsv;
    std::vector<std::vector<TH1F*>> h_jj_min_nsv_pt;
    std::vector<std::vector<TH1F*>> h_jj_min_nsv_eta;
    std::vector<std::vector<TH1F*>> h_jj_min_nsv_phi;
    std::vector<std::vector<TH1F*>> h_jj_min_nsv_m;
    std::vector<std::vector<TH1F*>> h_jj_min_nsv_sumPt;
    std::vector<TH1F*> h_jj_maxpt_pt;
    std::vector<TH1F*> h_jj_maxpt_eta;
    std::vector<TH1F*> h_jj_maxpt_phi;
    std::vector<TH1F*> h_jj_maxpt_m;
    std::vector<TH1F*> h_jj_maxpt_sumPt;
    std::vector<TH1F*> h_jj_maxpt_dR;
    std::vector<TH1F*> h_jj_minpt_pt;
    std::vector<TH1F*> h_jj_minpt_eta;
    std::vector<TH1F*> h_jj_minpt_phi;
    std::vector<TH1F*> h_jj_minpt_m;
    std::vector<TH1F*> h_jj_minpt_sumPt;
    std::vector<TH1F*> h_jj_minpt_dR;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk_pt;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk_eta;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk_phi;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk_m;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_ntrk_sumPt;
    std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk;
    std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk_pt;
    std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk_eta;
    std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk_phi;
    std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk_m;
    std::vector<std::vector<TH1F*>> h_jj_minpt_ntrk_sumPt;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv_pt;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv_eta;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv_phi;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv_m;
    std::vector<std::vector<TH1F*>> h_jj_maxpt_nsv_sumPt;
    std::vector<std::vector<TH1F*>> h_jj_minpt_nsv;
    std::vector<std::vector<TH1F*>> h_jj_minpt_nsv_pt;
    std::vector<std::vector<TH1F*>> h_jj_minpt_nsv_eta;
    std::vector<std::vector<TH1F*>> h_jj_minpt_nsv_phi;
    std::vector<std::vector<TH1F*>> h_jj_minpt_nsv_m;
    std::vector<std::vector<TH1F*>> h_jj_minpt_nsv_sumPt;
    std::vector<TH1F*> h_nj_pt;
    std::vector<TH1F*> h_nj_eta;
    std::vector<TH1F*> h_nj_phi;
    std::vector<TH1F*> h_nj_m;
    std::vector<TH1F*> h_nj_sumPt;
    std::vector<std::vector<TH1F*>> h_nj_ntrk;
    std::vector<std::vector<TH1F*>> h_nj_ntrk_pt;
    std::vector<std::vector<TH1F*>> h_nj_ntrk_eta;
    std::vector<std::vector<TH1F*>> h_nj_ntrk_phi;
    std::vector<std::vector<TH1F*>> h_nj_ntrk_m;
    std::vector<std::vector<TH1F*>> h_nj_ntrk_sumPt;
    std::vector<std::vector<TH1F*>> h_nj_nsv;
    std::vector<std::vector<TH1F*>> h_nj_nsv_pt;
    std::vector<std::vector<TH1F*>> h_nj_nsv_eta;
    std::vector<std::vector<TH1F*>> h_nj_nsv_phi;
    std::vector<std::vector<TH1F*>> h_nj_nsv_m;
    std::vector<std::vector<TH1F*>> h_nj_nsv_sumPt;
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
      
      h_j_n         .push_back( book( name, hj + "_n",         "n " + hjstr + "s",       njet,     0, njet ) );
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
	h_j_px   .push_back( book( name, hj + "_px",    hjstr + " p_{x} [GeV]",  100, -1500, 1500 ) );
	h_j_py   .push_back( book( name, hj + "_py",    hjstr + " p_{y} [GeV]",  100, -1500, 1500 ) );
	h_j_pz   .push_back( book( name, hj + "_pz",    hjstr + " p_{z} [GeV]",  100, -2500, 2500 ) );
	h_j_Et   .push_back( book( name, hj + "_Et",    hjstr + " E_{T} [GeV]",  100,     0, 1500 ) );
	h_j_Et_s .push_back( book( name, hj + "_Et_s",  hjstr + " E_{T} [GeV]",  100,     0,  500 ) );
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
      m_nTypeJDVs = h_j_nsecvtx.size();

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
      
      // dijets
      if ( m_histoInfoSwitch->m_dijets ) {
	std::string hjjavg    = hjj    + "_avgP4";
	std::string hjjavgstr = hjjstr + " avg-p4";
	std::string hjjmax    = hjj    + "_maxP4";
	std::string hjjmaxstr = hjjstr + " max-p4";
	std::string hjjmin    = hjj    + "_minP4";
	std::string hjjminstr = hjjstr + " min-p4";
	h_jj_n         .push_back( book( name, hjj + "_n",        "n " + hjjstr + "s",                 100,    0,   60 ) );
	h_jj_pt        .push_back( book( name, hjj + "_pt",       hjjstr + " p_{T} [GeV]",             100,    0, 2500 ) );
	h_jj_eta       .push_back( book( name, hjj + "_eta",      hjjstr + " eta",                     100,   -5,    5 ) );
	h_jj_phi       .push_back( book( name, hjj + "_phi",      hjjstr + " phi",                     100, -3.5,  3.5 ) );
	h_jj_m         .push_back( book( name, hjj + "_m",        hjjstr + " invariant mass [GeV]",    100,    0, 3500 ) );
	h_jj_sumPt     .push_back( book( name, hjj + "_sumPt",    hjjstr + " sum-p_{T} [GeV]",         100,    0, 3500 ) );
	h_jj_dR        .push_back( book( name, hjj + "_dR",       hjjstr + " dR",                      100,    0,    6 ) );
	// avg dijet system
	h_jj_avg_pt    .push_back( book( name, hjjavg + "_pt",    hjjavgstr + " p_{T} [GeV]",          100,    0, 1500 ) );
	h_jj_avg_eta   .push_back( book( name, hjjavg + "_eta",   hjjavgstr + " eta",                  100,   -5,    5 ) );
	h_jj_avg_phi   .push_back( book( name, hjjavg + "_phi",   hjjavgstr + " phi",                  100, -3.5,  3.5 ) );
	h_jj_avg_m     .push_back( book( name, hjjavg + "_m",     hjjavgstr + " invariant mass [GeV]", 100,    0, 2000 ) );
	h_jj_avg_sumPt .push_back( book( name, hjjavg + "_sumPt", hjjavgstr + " sum-p_{T} [GeV]",      100,    0, 2000 ) );
	h_jj_avg_dR    .push_back( book( name, hjjavg + "_dR",    hjjavgstr + " dR",                   100,    0,    6 ) );
	// max dijet system
	h_jj_max_pt    .push_back( book( name, hjjmax + "_pt",    hjjmaxstr + " p_{T} [GeV]",          100,    0, 1750 ) );
	h_jj_max_eta   .push_back( book( name, hjjmax + "_eta",   hjjmaxstr + " eta",                  100,   -5,    5 ) );
	h_jj_max_phi   .push_back( book( name, hjjmax + "_phi",   hjjmaxstr + " phi",                  100, -3.5,  3.5 ) );
	h_jj_max_m     .push_back( book( name, hjjmax + "_m",     hjjmaxstr + " invariant mass [GeV]", 100,    0, 4500 ) );
	h_jj_max_sumPt .push_back( book( name, hjjmax + "_sumPt", hjjmaxstr + " sum-p_{T} [GeV]",      100,    0, 4500 ) );
	h_jj_max_dR    .push_back( book( name, hjjmax + "_dR",    hjjmaxstr + " dR",                   100,    0,    6 ) );
	// min dijet system
	h_jj_min_pt    .push_back( book( name, hjjmin + "_pt",    hjjminstr + " p_{T} [GeV]",          100,    0, 2000 ) );
	h_jj_min_eta   .push_back( book( name, hjjmin + "_eta",   hjjminstr + " eta",                  100,   -5,    5 ) );
	h_jj_min_phi   .push_back( book( name, hjjmin + "_phi",   hjjminstr + " phi",                  100, -3.5,  3.5 ) );
	h_jj_min_m     .push_back( book( name, hjjmin + "_m",     hjjminstr + " invariant mass [GeV]", 100,    0, 1500 ) );
	h_jj_min_sumPt .push_back( book( name, hjjmin + "_sumPt", hjjminstr + " sum-p_{T} [GeV]",      100,    0, 2000 ) );
	h_jj_min_dR    .push_back( book( name, hjjmin + "_dR",    hjjminstr + " dR",                   100,    0,    6 ) );
	// min/max dijet ntrk system
	std::vector<int>   djnt_nbin    = {   100,  125,   75,  10,  20,  20,  20,  20 };
	std::vector<int>   djnt_x2      = {   500,  250,   75,  10,  20,  20,  20,  20 };
	std::vector<float> djntpt_x2    = {  5000, 2500, 1250,  25, 100, 100, 100, 100 };
	std::vector<float> djntmu_x2    = { 10000, 5000, 2500,  50, 200, 200, 200, 200 };
	std::vector<float> djntml_x2    = {  5000, 2500, 1250,  25, 100, 200, 200, 200 };
	std::vector<float> djntsumpt_x2 = { 10000, 5000, 2500,  50, 200, 200, 200, 200 };
	std::vector<TH1F*> h_jj_max_ntrack;
	std::vector<TH1F*> h_jj_max_ntrack_pt;
	std::vector<TH1F*> h_jj_max_ntrack_eta;
	std::vector<TH1F*> h_jj_max_ntrack_phi;
	std::vector<TH1F*> h_jj_max_ntrack_m;
	std::vector<TH1F*> h_jj_max_ntrack_sumPt;
	std::vector<TH1F*> h_jj_min_ntrack;
	std::vector<TH1F*> h_jj_min_ntrack_pt;
	std::vector<TH1F*> h_jj_min_ntrack_eta;
	std::vector<TH1F*> h_jj_min_ntrack_phi;
	std::vector<TH1F*> h_jj_min_ntrack_m;
	std::vector<TH1F*> h_jj_min_ntrack_sumPt;
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
	  if ( m_histoInfoSwitch->m_jetTrks ) {
	    h_jj_max_ntrack_pt   .push_back( book( name, hjjmaxnt + "_pt",   hjjmaxntstr + " p_{T} [GeV]",         100, 0, djntpt_x2   [j] ) );
	    h_jj_max_ntrack_eta  .push_back( book( name, hjjmaxnt + "_eta",  hjjmaxntstr + " eta",                 100,-5,               5 ) );
	    h_jj_max_ntrack_phi  .push_back( book( name, hjjmaxnt + "_phi",  hjjmaxntstr + " phi",                 100,-3.5,           3.5 ) );
	    h_jj_max_ntrack_m    .push_back( book( name, hjjmaxnt + "_m",    hjjmaxntstr + " invariant mass [GeV]",100, 0, djntmu_x2   [j] ) );
	    h_jj_max_ntrack_sumPt.push_back( book( name, hjjmaxnt + "_sumPt",hjjmaxntstr + " sum-p_{T} [GeV]",     100, 0, djntsumpt_x2[j] ) );
	    h_jj_min_ntrack_pt   .push_back( book( name, hjjminnt + "_pt",   hjjminntstr + " p_{T} [GeV]",         100, 0, djntpt_x2   [j] ) );
	    h_jj_min_ntrack_eta  .push_back( book( name, hjjminnt + "_eta",  hjjminntstr + " eta",                 100,-5,               5 ) );
	    h_jj_min_ntrack_phi  .push_back( book( name, hjjminnt + "_phi",  hjjminntstr + " phi",                 100,-3.5,           3.5 ) );
	    h_jj_min_ntrack_m    .push_back( book( name, hjjminnt + "_m",    hjjminntstr + " invariant mass [GeV]",100, 0, djntml_x2   [j] ) );
	    h_jj_min_ntrack_sumPt.push_back( book( name, hjjminnt + "_sumPt",hjjminntstr + " sum-p_{T} [GeV]",     100, 0, djntsumpt_x2[j] ) );
	  }
	}
	h_jj_max_ntrk         .push_back( h_jj_max_ntrack       );
	h_jj_min_ntrk         .push_back( h_jj_min_ntrack       );
	if ( m_histoInfoSwitch->m_jetTrks ) {
	  h_jj_max_ntrk_pt    .push_back( h_jj_max_ntrack_pt    );
	  h_jj_max_ntrk_eta   .push_back( h_jj_max_ntrack_eta   );
	  h_jj_max_ntrk_phi   .push_back( h_jj_max_ntrack_phi   );
	  h_jj_max_ntrk_m     .push_back( h_jj_max_ntrack_m     );
	  h_jj_max_ntrk_sumPt .push_back( h_jj_max_ntrack_sumPt );
	  h_jj_min_ntrk_pt    .push_back( h_jj_min_ntrack_pt    );
	  h_jj_min_ntrk_eta   .push_back( h_jj_min_ntrack_eta   );
	  h_jj_min_ntrk_phi   .push_back( h_jj_min_ntrack_phi   );
	  h_jj_min_ntrk_m     .push_back( h_jj_min_ntrack_m     );
	  h_jj_min_ntrk_sumPt .push_back( h_jj_min_ntrack_sumPt );
	}
	// min/max dijet nsv system
	std::vector<TH1F*> h_jj_max_nsecvtx;
	std::vector<TH1F*> h_jj_max_nsecvtx_pt;
	std::vector<TH1F*> h_jj_max_nsecvtx_eta;
	std::vector<TH1F*> h_jj_max_nsecvtx_phi;
	std::vector<TH1F*> h_jj_max_nsecvtx_m;
	std::vector<TH1F*> h_jj_max_nsecvtx_sumPt;
	std::vector<TH1F*> h_jj_min_nsecvtx;
	std::vector<TH1F*> h_jj_min_nsecvtx_pt;
	std::vector<TH1F*> h_jj_min_nsecvtx_eta;
	std::vector<TH1F*> h_jj_min_nsecvtx_phi;
	std::vector<TH1F*> h_jj_min_nsecvtx_m;
	std::vector<TH1F*> h_jj_min_nsecvtx_sumPt;
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
	  if ( m_histoInfoSwitch->m_jetVerts ) {
	    h_jj_max_nsecvtx_pt    .push_back( book( name, hjjmaxnv + "_pt",    hjjmaxnvstr + " p_{T} [GeV]",          100,    0,  175 ) );
	    h_jj_max_nsecvtx_eta   .push_back( book( name, hjjmaxnv + "_eta",   hjjmaxnvstr + " eta",                  100,   -5,    5 ) );
	    h_jj_max_nsecvtx_phi   .push_back( book( name, hjjmaxnv + "_phi",   hjjmaxnvstr + " phi",                  100, -3.5,  3.5 ) );
	    h_jj_max_nsecvtx_m     .push_back( book( name, hjjmaxnv + "_m",     hjjmaxnvstr + " invariant mass [GeV]", 100,    0,  150 ) );
	    h_jj_max_nsecvtx_sumPt .push_back( book( name, hjjmaxnv + "_sumPt", hjjmaxnvstr + " sum-p_{T} [GeV]",      100,    0,  200 ) );
	    h_jj_min_nsecvtx_pt    .push_back( book( name, hjjminnv + "_pt",    hjjminnvstr + " p_{T} [GeV]",          100,    0,  175 ) );
	    h_jj_min_nsecvtx_eta   .push_back( book( name, hjjminnv + "_eta",   hjjminnvstr + " eta",                  100,   -5,    5 ) );
	    h_jj_min_nsecvtx_phi   .push_back( book( name, hjjminnv + "_phi",   hjjminnvstr + " phi",                  100, -3.5,  3.5 ) );
	    h_jj_min_nsecvtx_m     .push_back( book( name, hjjminnv + "_m",     hjjminnvstr + " invariant mass [GeV]", 100,    0,   75 ) );
	    h_jj_min_nsecvtx_sumPt .push_back( book( name, hjjminnv + "_sumPt", hjjminnvstr + " sum-p_{T} [GeV]",      100,    0,  200 ) );
	  }
	}
	h_jj_max_nsv         .push_back( h_jj_max_nsecvtx       );
	h_jj_min_nsv         .push_back( h_jj_min_nsecvtx       );
	if ( m_histoInfoSwitch->m_jetVerts ) {
	  h_jj_max_nsv_pt    .push_back( h_jj_max_nsecvtx_pt    );
	  h_jj_max_nsv_eta   .push_back( h_jj_max_nsecvtx_eta   );
	  h_jj_max_nsv_phi   .push_back( h_jj_max_nsecvtx_phi   );
	  h_jj_max_nsv_m     .push_back( h_jj_max_nsecvtx_m     );
	  h_jj_max_nsv_sumPt .push_back( h_jj_max_nsecvtx_sumPt );
	  h_jj_min_nsv_pt    .push_back( h_jj_min_nsecvtx_pt    );
	  h_jj_min_nsv_eta   .push_back( h_jj_min_nsecvtx_eta   );
	  h_jj_min_nsv_phi   .push_back( h_jj_min_nsecvtx_phi   );
	  h_jj_min_nsv_m     .push_back( h_jj_min_nsecvtx_m     );
	  h_jj_min_nsv_sumPt .push_back( h_jj_min_nsecvtx_sumPt );
	}

	std::string hjjmaxpt    = hjj    + "_maxPt";
	std::string hjjmaxptstr = hjjstr + " max-pt";
	std::string hjjminpt    = hjj    + "_minPt";
	std::string hjjminptstr = hjjstr + " min-pt";
	// max-pt dijet system
	h_jj_maxpt_pt    .push_back( book( name, hjjmaxpt + "_pt",    hjjmaxptstr + " p_{T} [GeV]",          100,    0, 3000 ) );
	h_jj_maxpt_eta   .push_back( book( name, hjjmaxpt + "_eta",   hjjmaxptstr + " eta",                  100,   -5,    5 ) );
	h_jj_maxpt_phi   .push_back( book( name, hjjmaxpt + "_phi",   hjjmaxptstr + " phi",                  100, -3.5,  3.5 ) );
	h_jj_maxpt_m     .push_back( book( name, hjjmaxpt + "_m",     hjjmaxptstr + " invariant mass [GeV]", 100,    0, 3500 ) );
	h_jj_maxpt_sumPt .push_back( book( name, hjjmaxpt + "_sumPt", hjjmaxptstr + " sum-p_{T} [GeV]",      100,    0, 3500 ) );
	h_jj_maxpt_dR    .push_back( book( name, hjjmaxpt + "_dR",    hjjmaxptstr + " dR",                   100,    0,    6 ) );
	// min-pt dijet system
	h_jj_minpt_pt    .push_back( book( name, hjjminpt + "_pt",    hjjminptstr + " p_{T} [GeV]",          100,    0, 1250 ) );
	h_jj_minpt_eta   .push_back( book( name, hjjminpt + "_eta",   hjjminptstr + " eta",                  100,   -5,    5 ) );
	h_jj_minpt_phi   .push_back( book( name, hjjminpt + "_phi",   hjjminptstr + " phi",                  100, -3.5,  3.5 ) );
	h_jj_minpt_m     .push_back( book( name, hjjminpt + "_m",     hjjminptstr + " invariant mass [GeV]", 100,    0, 3500 ) );
	h_jj_minpt_sumPt .push_back( book( name, hjjminpt + "_sumPt", hjjminptstr + " sum-p_{T} [GeV]",      100,    0, 3000 ) );
	h_jj_minpt_dR    .push_back( book( name, hjjminpt + "_dR",    hjjminptstr + " dR",                   100,    0,    6 ) );
	// min/max-pt dijet ntrk system
	std::vector<TH1F*> h_jj_maxpt_ntrack;
	std::vector<TH1F*> h_jj_maxpt_ntrack_pt;
	std::vector<TH1F*> h_jj_maxpt_ntrack_eta;
	std::vector<TH1F*> h_jj_maxpt_ntrack_phi;
	std::vector<TH1F*> h_jj_maxpt_ntrack_m;
	std::vector<TH1F*> h_jj_maxpt_ntrack_sumPt;
	std::vector<TH1F*> h_jj_minpt_ntrack;
	std::vector<TH1F*> h_jj_minpt_ntrack_pt;
	std::vector<TH1F*> h_jj_minpt_ntrack_eta;
	std::vector<TH1F*> h_jj_minpt_ntrack_phi;
	std::vector<TH1F*> h_jj_minpt_ntrack_m;
	std::vector<TH1F*> h_jj_minpt_ntrack_sumPt;
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
	  if ( m_histoInfoSwitch->m_jetTrks ) {
	    h_jj_maxpt_ntrack_pt   .push_back( book( name, hjjmaxnt + "_pt",   hjjmaxntstr + " p_{T} [GeV]",         100, 0, djntpt_x2   [j] ) );
	    h_jj_maxpt_ntrack_eta  .push_back( book( name, hjjmaxnt + "_eta",  hjjmaxntstr + " eta",                 100,-5,               5 ) );
	    h_jj_maxpt_ntrack_phi  .push_back( book( name, hjjmaxnt + "_phi",  hjjmaxntstr + " phi",                 100,-3.5,           3.5 ) );
	    h_jj_maxpt_ntrack_m    .push_back( book( name, hjjmaxnt + "_m",    hjjmaxntstr + " invariant mass [GeV]",100, 0, djntmu_x2   [j] ) );
	    h_jj_maxpt_ntrack_sumPt.push_back( book( name, hjjmaxnt + "_sumPt",hjjmaxntstr + " sum-p_{T} [GeV]",     100, 0, djntsumpt_x2[j] ) );
	    h_jj_minpt_ntrack_pt   .push_back( book( name, hjjminnt + "_pt",   hjjminntstr + " p_{T} [GeV]",         100, 0, djntpt_x2   [j] ) );
	    h_jj_minpt_ntrack_eta  .push_back( book( name, hjjminnt + "_eta",  hjjminntstr + " eta",                 100,-5,               5 ) );
	    h_jj_minpt_ntrack_phi  .push_back( book( name, hjjminnt + "_phi",  hjjminntstr + " phi",                 100,-3.5,           3.5 ) );
	    h_jj_minpt_ntrack_m    .push_back( book( name, hjjminnt + "_m",    hjjminntstr + " invariant mass [GeV]",100, 0, djntml_x2   [j] ) );
	    h_jj_minpt_ntrack_sumPt.push_back( book( name, hjjminnt + "_sumPt",hjjminntstr + " sum-p_{T} [GeV]",     100, 0, djntsumpt_x2[j] ) );
	  }
	}
	h_jj_maxpt_ntrk         .push_back( h_jj_maxpt_ntrack       );
	h_jj_minpt_ntrk         .push_back( h_jj_minpt_ntrack       );
	if ( m_histoInfoSwitch->m_jetTrks ) {
	  h_jj_maxpt_ntrk_pt    .push_back( h_jj_maxpt_ntrack_pt    );
	  h_jj_maxpt_ntrk_eta   .push_back( h_jj_maxpt_ntrack_eta   );
	  h_jj_maxpt_ntrk_phi   .push_back( h_jj_maxpt_ntrack_phi   );
	  h_jj_maxpt_ntrk_m     .push_back( h_jj_maxpt_ntrack_m     );
	  h_jj_maxpt_ntrk_sumPt .push_back( h_jj_maxpt_ntrack_sumPt );
	  h_jj_minpt_ntrk_pt    .push_back( h_jj_minpt_ntrack_pt    );
	  h_jj_minpt_ntrk_eta   .push_back( h_jj_minpt_ntrack_eta   );
	  h_jj_minpt_ntrk_phi   .push_back( h_jj_minpt_ntrack_phi   );
	  h_jj_minpt_ntrk_m     .push_back( h_jj_minpt_ntrack_m     );
	  h_jj_minpt_ntrk_sumPt .push_back( h_jj_minpt_ntrack_sumPt );
	}
	// min/max-pt dijet nsv system
	std::vector<TH1F*> h_jj_maxpt_nsecvtx;
	std::vector<TH1F*> h_jj_maxpt_nsecvtx_pt;
	std::vector<TH1F*> h_jj_maxpt_nsecvtx_eta;
	std::vector<TH1F*> h_jj_maxpt_nsecvtx_phi;
	std::vector<TH1F*> h_jj_maxpt_nsecvtx_m;
	std::vector<TH1F*> h_jj_maxpt_nsecvtx_sumPt;
	std::vector<TH1F*> h_jj_minpt_nsecvtx;
	std::vector<TH1F*> h_jj_minpt_nsecvtx_pt;
	std::vector<TH1F*> h_jj_minpt_nsecvtx_eta;
	std::vector<TH1F*> h_jj_minpt_nsecvtx_phi;
	std::vector<TH1F*> h_jj_minpt_nsecvtx_m;
	std::vector<TH1F*> h_jj_minpt_nsecvtx_sumPt;
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
	  if ( m_histoInfoSwitch->m_jetVerts ) {
	    h_jj_maxpt_nsecvtx_pt    .push_back( book( name, hjjmaxnv + "_pt",    hjjmaxnvstr + " p_{T} [GeV]",          100,    0,  175 ) );
	    h_jj_maxpt_nsecvtx_eta   .push_back( book( name, hjjmaxnv + "_eta",   hjjmaxnvstr + " eta",                  100,   -5,    5 ) );
	    h_jj_maxpt_nsecvtx_phi   .push_back( book( name, hjjmaxnv + "_phi",   hjjmaxnvstr + " phi",                  100, -3.5,  3.5 ) );
	    h_jj_maxpt_nsecvtx_m     .push_back( book( name, hjjmaxnv + "_m",     hjjmaxnvstr + " invariant mass [GeV]", 100,    0,  150 ) );
	    h_jj_maxpt_nsecvtx_sumPt .push_back( book( name, hjjmaxnv + "_sumPt", hjjmaxnvstr + " sum-p_{T} [GeV]",      100,    0,  200 ) );
	    h_jj_minpt_nsecvtx_pt    .push_back( book( name, hjjminnv + "_pt",    hjjminnvstr + " p_{T} [GeV]",          100,    0,  175 ) );
	    h_jj_minpt_nsecvtx_eta   .push_back( book( name, hjjminnv + "_eta",   hjjminnvstr + " eta",                  100,   -5,    5 ) );
	    h_jj_minpt_nsecvtx_phi   .push_back( book( name, hjjminnv + "_phi",   hjjminnvstr + " phi",                  100, -3.5,  3.5 ) );
	    h_jj_minpt_nsecvtx_m     .push_back( book( name, hjjminnv + "_m",     hjjminnvstr + " invariant mass [GeV]", 100,    0,   75 ) );
	    h_jj_minpt_nsecvtx_sumPt .push_back( book( name, hjjminnv + "_sumPt", hjjminnvstr + " sum-p_{T} [GeV]",      100,    0,  200 ) );
	  }
	}
	h_jj_maxpt_nsv         .push_back( h_jj_maxpt_nsecvtx       );
	h_jj_minpt_nsv         .push_back( h_jj_minpt_nsecvtx       );
	if ( m_histoInfoSwitch->m_jetVerts ) {
	  h_jj_maxpt_nsv_pt    .push_back( h_jj_maxpt_nsecvtx_pt    );
	  h_jj_maxpt_nsv_eta   .push_back( h_jj_maxpt_nsecvtx_eta   );
	  h_jj_maxpt_nsv_phi   .push_back( h_jj_maxpt_nsecvtx_phi   );
	  h_jj_maxpt_nsv_m     .push_back( h_jj_maxpt_nsecvtx_m     );
	  h_jj_maxpt_nsv_sumPt .push_back( h_jj_maxpt_nsecvtx_sumPt );
	  h_jj_minpt_nsv_pt    .push_back( h_jj_minpt_nsecvtx_pt    );
	  h_jj_minpt_nsv_eta   .push_back( h_jj_minpt_nsecvtx_eta   );
	  h_jj_minpt_nsv_phi   .push_back( h_jj_minpt_nsecvtx_phi   );
	  h_jj_minpt_nsv_m     .push_back( h_jj_minpt_nsecvtx_m     );
	  h_jj_minpt_nsv_sumPt .push_back( h_jj_minpt_nsecvtx_sumPt );
	}
      } // end dijet info switch
      
      // event-level jets (all jets in event)
      if ( m_histoInfoSwitch->m_njets ) {
	h_nj_pt    .push_back( book( name, hnj + "_pt",    hnjstr + " p_{T} [GeV]",          100,           0,  750 ) );
	h_nj_eta   .push_back( book( name, hnj + "_eta",   hnjstr + " eta",                  100,          -7,    7 ) );
	h_nj_phi   .push_back( book( name, hnj + "_phi",   hnjstr + " phi",                  100,        -3.5,  3.5 ) );
	h_nj_m     .push_back( book( name, hnj + "_m",     hnjstr + " invariant mass [GeV]", 100, njetht_xmin, 7500 ) );
	h_nj_sumPt .push_back( book( name, hnj + "_sumPt", hnjstr + " sum-p_{T} [GeV]",      100, njetht_xmin, 5500 ) );
	// --> event-level jet-matched tracks
	std::vector<TH1F*> h_nj_ntrack;
	std::vector<TH1F*> h_nj_ntrack_pt;
	std::vector<TH1F*> h_nj_ntrack_eta;
	std::vector<TH1F*> h_nj_ntrack_phi;
	std::vector<TH1F*> h_nj_ntrack_m;
	std::vector<TH1F*> h_nj_ntrack_sumPt;
	std::vector<int>   njnt_nbin    = {   100,   100,  125,  15,  30,  30,  30,  30 };
	std::vector<float> njnt_x2      = {  1500,   750,  250,  15,  30,  30,  30,  30 };
	std::vector<float> njntpt_x2    = {  7500,  3750, 1250,  50, 200, 200, 200, 200 };
	std::vector<float> njntm_x2     = { 15000, 10000, 2500,  25, 250, 250, 250, 250 };
	std::vector<float> njntsumpt_x2 = { 15000, 10000, 2500,  50, 250, 250, 250, 250 };
	for ( size_t j = 0; j != hTrk.size(); ++j ) {
	  std::string htsubstr = "matched";
	  if ( !hTrkstr[j].empty() ) htsubstr += " ";
	  std::string ht       = hTrk[j] + "trk";
	  std::string hnt      = "n" + ht;
	  std::string hntstr   = htsubstr + hTrkstr[j] + " n-track";
	  std::string hnjnt    = hnj + "_" + hnt;
	  std::string hnjntstr = hnjstr + " " + hntstr;
	  h_nj_ntrack         .push_back( book( name, hnjnt,            hntstr + "s per " + hnjstr, njnt_nbin[j], 0, njnt_x2  [j] ) );
	  if ( m_histoInfoSwitch->m_jetTrks ) {
	    h_nj_ntrack_pt    .push_back( book( name, hnjnt + "_pt",    hnjntstr+ " p_{T} [GeV]",     100,    0, njntpt_x2    [j] ) );
	    h_nj_ntrack_eta   .push_back( book( name, hnjnt + "_eta",   hnjntstr+ " eta",             100,   -5,                5 ) );
	    h_nj_ntrack_phi   .push_back( book( name, hnjnt + "_phi",   hnjntstr+ " phi",             100, -3.5,              3.5 ) );
	    h_nj_ntrack_m     .push_back( book( name, hnjnt + "_m",     hnjntstr+ " mass [GeV]",      100,    0, njntm_x2     [j] ) );
	    h_nj_ntrack_sumPt .push_back( book( name, hnjnt + "_sumPt", hnjntstr+ " sum-p_{T} [GeV]", 100,    0, njntsumpt_x2 [j] ) );
	  }
	}
	h_nj_ntrk         .push_back( h_nj_ntrack       );
	if ( m_histoInfoSwitch->m_jetTrks ) {
	  h_nj_ntrk_pt    .push_back( h_nj_ntrack_pt    );
	  h_nj_ntrk_eta   .push_back( h_nj_ntrack_eta   );
	  h_nj_ntrk_phi   .push_back( h_nj_ntrack_phi   );
	  h_nj_ntrk_m     .push_back( h_nj_ntrack_m     );
	  h_nj_ntrk_sumPt .push_back( h_nj_ntrack_sumPt );
	}
	// --> event-level jet-matched secondary vertices
	std::vector<TH1F*> h_nj_nsecvtx;
	std::vector<TH1F*> h_nj_nsecvtx_pt;
	std::vector<TH1F*> h_nj_nsecvtx_eta;
	std::vector<TH1F*> h_nj_nsecvtx_phi;
	std::vector<TH1F*> h_nj_nsecvtx_m;
	std::vector<TH1F*> h_nj_nsecvtx_sumPt;
	for ( size_t k = 0; k != hJDV.size(); ++k ) {
	  std::string hv       = hJDV[k] + "SV"; hv[0] = tolower(hv[0]);
	  std::string hdvstr   = hJDVstr[k];     hdvstr.pop_back();
	  std::string hnv      = "n" + hv;
	  std::string hnvstr   = "matched " + hdvstr + " n-SV";
	  std::string hnjnv    = hnj    + "_" + hnv;
	  std::string hnjnvstr = hnjstr + " " + hnvstr;
	  h_nj_nsecvtx         .push_back( book( name, hnjnv,            hnvstr + "s per " + hnjstr,         20,    0,   20 ) );
	  if ( m_histoInfoSwitch->m_jetVerts ) {
	    h_nj_nsecvtx_pt    .push_back( book( name, hnjnv + "_pt",    hnjnvstr+ " p_{T} [GeV]",          100,    0,  250 ) );
	    h_nj_nsecvtx_eta   .push_back( book( name, hnjnv + "_eta",   hnjnvstr+ " eta",                  100,   -5,    5 ) );
	    h_nj_nsecvtx_phi   .push_back( book( name, hnjnv + "_phi",   hnjnvstr+ " phi",                  100, -3.5,  3.5 ) );
	    h_nj_nsecvtx_m     .push_back( book( name, hnjnv + "_m",     hnjnvstr+ " invariant mass [GeV]", 100,    0,  250 ) );
	    h_nj_nsecvtx_sumPt .push_back( book( name, hnjnv + "_sumPt", hnjnvstr+ " sum-p_{T} [GeV]",      100,    0,  300 ) );
	  }
	}
	h_nj_nsv         .push_back( h_nj_nsecvtx       );
	if ( m_histoInfoSwitch->m_jetVerts ) {
	  h_nj_nsv_pt    .push_back( h_nj_nsecvtx_pt    );
	  h_nj_nsv_eta   .push_back( h_nj_nsecvtx_eta   );
	  h_nj_nsv_phi   .push_back( h_nj_nsecvtx_phi   );
	  h_nj_nsv_m     .push_back( h_nj_nsecvtx_m     );
	  h_nj_nsv_sumPt .push_back( h_nj_nsecvtx_sumPt );
	}
      } // end njet info switch
    } // end loop over jet types
    
    h_jet_n         .push_back( h_j_n         );
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
    
    if ( m_histoInfoSwitch->m_dijets ) {
      h_dijet_n                  .push_back( h_jj_n                );
      h_dijet_pt                 .push_back( h_jj_pt               );
      h_dijet_eta                .push_back( h_jj_eta              );
      h_dijet_phi                .push_back( h_jj_phi              );
      h_dijet_m                  .push_back( h_jj_m                );
      h_dijet_sumPt              .push_back( h_jj_sumPt            );
      h_dijet_dR                 .push_back( h_jj_dR               );
      h_dijet_avgp4_pt           .push_back( h_jj_avg_pt           );
      h_dijet_avgp4_eta          .push_back( h_jj_avg_eta          );
      h_dijet_avgp4_phi          .push_back( h_jj_avg_phi          );
      h_dijet_avgp4_m            .push_back( h_jj_avg_m            );
      h_dijet_avgp4_sumPt        .push_back( h_jj_avg_sumPt        );
      h_dijet_avgp4_dR           .push_back( h_jj_avg_dR           );
      h_dijet_maxp4_pt           .push_back( h_jj_max_pt           );
      h_dijet_maxp4_eta          .push_back( h_jj_max_eta          );
      h_dijet_maxp4_phi          .push_back( h_jj_max_phi          );
      h_dijet_maxp4_m            .push_back( h_jj_max_m            );
      h_dijet_maxp4_sumPt        .push_back( h_jj_max_sumPt        );
      h_dijet_maxp4_dR           .push_back( h_jj_max_dR           );
      h_dijet_minp4_pt           .push_back( h_jj_min_pt           );
      h_dijet_minp4_eta          .push_back( h_jj_min_eta          );
      h_dijet_minp4_phi          .push_back( h_jj_min_phi          );
      h_dijet_minp4_m            .push_back( h_jj_min_m            );
      h_dijet_minp4_sumPt        .push_back( h_jj_min_sumPt        );
      h_dijet_minp4_dR           .push_back( h_jj_min_dR           );
      h_dijet_maxp4_ntrk         .push_back( h_jj_max_ntrk         );
      h_dijet_minp4_ntrk         .push_back( h_jj_min_ntrk         );
      if ( m_histoInfoSwitch->m_jetTrks   ) {
      	h_dijet_maxp4_ntrk_pt    .push_back( h_jj_max_ntrk_pt      );
      	h_dijet_maxp4_ntrk_eta   .push_back( h_jj_max_ntrk_eta     );
      	h_dijet_maxp4_ntrk_phi   .push_back( h_jj_max_ntrk_phi     );
      	h_dijet_maxp4_ntrk_m     .push_back( h_jj_max_ntrk_m       );
      	h_dijet_maxp4_ntrk_sumPt .push_back( h_jj_max_ntrk_sumPt   );
      	h_dijet_minp4_ntrk_pt    .push_back( h_jj_min_ntrk_pt      );
      	h_dijet_minp4_ntrk_eta   .push_back( h_jj_min_ntrk_eta     );
      	h_dijet_minp4_ntrk_phi   .push_back( h_jj_min_ntrk_phi     );
      	h_dijet_minp4_ntrk_m     .push_back( h_jj_min_ntrk_m       );
      	h_dijet_minp4_ntrk_sumPt .push_back( h_jj_min_ntrk_sumPt   );
      }
      h_dijet_maxp4_nsv          .push_back( h_jj_max_nsv          );
      h_dijet_minp4_nsv          .push_back( h_jj_min_nsv          );
      if ( m_histoInfoSwitch->m_jetVerts ) {
      	h_dijet_maxp4_nsv_pt     .push_back( h_jj_max_nsv_pt       );
      	h_dijet_maxp4_nsv_eta    .push_back( h_jj_max_nsv_eta      );
      	h_dijet_maxp4_nsv_phi    .push_back( h_jj_max_nsv_phi      );
      	h_dijet_maxp4_nsv_m      .push_back( h_jj_max_nsv_m        );
      	h_dijet_maxp4_nsv_sumPt  .push_back( h_jj_max_nsv_sumPt    );
      	h_dijet_minp4_nsv_pt     .push_back( h_jj_min_nsv_pt       );
      	h_dijet_minp4_nsv_eta    .push_back( h_jj_min_nsv_eta      );
      	h_dijet_minp4_nsv_phi    .push_back( h_jj_min_nsv_phi      );
      	h_dijet_minp4_nsv_m      .push_back( h_jj_min_nsv_m        );
      	h_dijet_minp4_nsv_sumPt  .push_back( h_jj_min_nsv_sumPt    );
      }
      h_dijet_maxpt_pt           .push_back( h_jj_maxpt_pt         );
      h_dijet_maxpt_eta          .push_back( h_jj_maxpt_eta        );
      h_dijet_maxpt_phi          .push_back( h_jj_maxpt_phi        );
      h_dijet_maxpt_m            .push_back( h_jj_maxpt_m          );
      h_dijet_maxpt_sumPt        .push_back( h_jj_maxpt_sumPt      );
      h_dijet_maxpt_dR           .push_back( h_jj_maxpt_dR         );
      h_dijet_minpt_pt           .push_back( h_jj_minpt_pt         );
      h_dijet_minpt_eta          .push_back( h_jj_minpt_eta        );
      h_dijet_minpt_phi          .push_back( h_jj_minpt_phi        );
      h_dijet_minpt_m            .push_back( h_jj_minpt_m          );
      h_dijet_minpt_sumPt        .push_back( h_jj_minpt_sumPt      );
      h_dijet_minpt_dR           .push_back( h_jj_minpt_dR         );
      h_dijet_maxpt_ntrk         .push_back( h_jj_maxpt_ntrk       );
      h_dijet_minpt_ntrk         .push_back( h_jj_minpt_ntrk       );
      if ( m_histoInfoSwitch->m_jetTrks   ) {
      	h_dijet_maxpt_ntrk_pt    .push_back( h_jj_maxpt_ntrk_pt    );
      	h_dijet_maxpt_ntrk_eta   .push_back( h_jj_maxpt_ntrk_eta   );
      	h_dijet_maxpt_ntrk_phi   .push_back( h_jj_maxpt_ntrk_phi   );
      	h_dijet_maxpt_ntrk_m     .push_back( h_jj_maxpt_ntrk_m     );
      	h_dijet_maxpt_ntrk_sumPt .push_back( h_jj_maxpt_ntrk_sumPt );
      	h_dijet_minpt_ntrk_pt    .push_back( h_jj_minpt_ntrk_pt    );
      	h_dijet_minpt_ntrk_eta   .push_back( h_jj_minpt_ntrk_eta   );
      	h_dijet_minpt_ntrk_phi   .push_back( h_jj_minpt_ntrk_phi   );
      	h_dijet_minpt_ntrk_m     .push_back( h_jj_minpt_ntrk_m     );
      	h_dijet_minpt_ntrk_sumPt .push_back( h_jj_minpt_ntrk_sumPt );
      }
      h_dijet_maxpt_nsv          .push_back( h_jj_maxpt_nsv        );
      h_dijet_minpt_nsv          .push_back( h_jj_minpt_nsv        );
      if ( m_histoInfoSwitch->m_jetVerts ) {
      	h_dijet_maxpt_nsv_pt     .push_back( h_jj_maxpt_nsv_pt     );
      	h_dijet_maxpt_nsv_eta    .push_back( h_jj_maxpt_nsv_eta    );
      	h_dijet_maxpt_nsv_phi    .push_back( h_jj_maxpt_nsv_phi    );
      	h_dijet_maxpt_nsv_m      .push_back( h_jj_maxpt_nsv_m      );
      	h_dijet_maxpt_nsv_sumPt  .push_back( h_jj_maxpt_nsv_sumPt  );
      	h_dijet_minpt_nsv_pt     .push_back( h_jj_minpt_nsv_pt     );
      	h_dijet_minpt_nsv_eta    .push_back( h_jj_minpt_nsv_eta    );
      	h_dijet_minpt_nsv_phi    .push_back( h_jj_minpt_nsv_phi    );
      	h_dijet_minpt_nsv_m      .push_back( h_jj_minpt_nsv_m      );
      	h_dijet_minpt_nsv_sumPt  .push_back( h_jj_minpt_nsv_sumPt  );
      }
    }
    if ( m_histoInfoSwitch->m_njets ) {
      h_njet_pt           .push_back( h_nj_pt         );
      h_njet_eta          .push_back( h_nj_eta        );
      h_njet_phi          .push_back( h_nj_phi        );
      h_njet_m            .push_back( h_nj_m          );
      h_njet_sumPt        .push_back( h_nj_sumPt      );
      h_njet_ntrk         .push_back( h_nj_ntrk       );
      if ( m_histoInfoSwitch->m_jetTrks   ) {
	h_njet_ntrk_pt    .push_back( h_nj_ntrk_pt    );
	h_njet_ntrk_eta   .push_back( h_nj_ntrk_eta   );
	h_njet_ntrk_phi   .push_back( h_nj_ntrk_phi   );
	h_njet_ntrk_m     .push_back( h_nj_ntrk_m     );
	h_njet_ntrk_sumPt .push_back( h_nj_ntrk_sumPt );
      }
      h_njet_nsv          .push_back( h_nj_nsv        );
      if ( m_histoInfoSwitch->m_jetVerts ) {
	h_njet_nsv_pt     .push_back( h_nj_nsv_pt     );
	h_njet_nsv_eta    .push_back( h_nj_nsv_eta    );
	h_njet_nsv_phi    .push_back( h_nj_nsv_phi    );
	h_njet_nsv_m      .push_back( h_nj_nsv_m      );
	h_njet_nsv_sumPt  .push_back( h_nj_nsv_sumPt  );
      }
    }
      
    // average of dijet pair with minimum invariant mass difference
    h_NJetJJ_pt
      .push_back( book( name, "NJetJJ_pt",      "leading N " + m_jetStr + " dijet p_{T} [GeV]",                     100,    0, 3000 ) );
    h_NJetJJ_eta
      .push_back( book( name, "NJetJJ_eta",     "leading N " + m_jetStr + " dijet eta",                             100,   -5,    5 ) );
    h_NJetJJ_phi
      .push_back( book( name, "NJetJJ_phi",     "leading N " + m_jetStr + " dijet phi",                             100, -3.5,  3.5 ) );
    h_NJetJJ_m
      .push_back( book( name, "NJetJJ_m",       "leading N " + m_jetStr + " dijet invariant mass [GeV]",            100,    0, 3000 ) );
    h_NJetJJ_ptDiff
      .push_back( book( name, "NJetJJ_ptDiff",  "leading N " + m_jetStr + " dijet p_{T} difference [GeV]",          100,    0, 1000 ) );
    h_NJetJJ_etaDiff
      .push_back( book( name, "NJetJJ_etaDiff", "leading N " + m_jetStr + " dijet eta difference",                  100,    0,  7.5 ) );
    h_NJetJJ_phiDiff
      .push_back( book( name, "NJetJJ_phiDiff", "leading N " + m_jetStr + " dijet phi difference",                  100,    0,  6.5 ) );
    h_NJetJJ_mDiff
      .push_back( book( name, "NJetJJ_mDiff",   "leading N " + m_jetStr + " dijet invariant mass difference [GeV]", 100,    0, 1500 ) );
    h_NJetJJ_sumPt
      .push_back( book( name, "NJetJJ_sumPt",   "leading N " + m_jetStr + " dijet sum-p_{T} [GeV]",                 100,    0, 5500 ) );
    h_NJetJJ_dR
      .push_back( book( name, "NJetJJ_dR",      "leading N " + m_jetStr + " dijet dR",                              100,    0,    7 ) );
    

    // --- TRACKS --- //
    // tracks: basics / kinematics
    std::vector<int>   ntrk_x2 = { 5000, 4000, 500, 20, 50, 50, 50, 50 };
    std::vector<TH1F*> h_track_n;
    for ( size_t i = 0; i != hTrk.size(); ++i ) {
      std::string ht    = hTrk   [i] + "trk";
      std::string htstr = hTrkstr[i] + " track";
      int nbin = 100;
      if ( i > 2 ) nbin = ntrk_x2[i];
      h_track_n .push_back( book( name, ht + "_n", "n " + htstr + "s", nbin, 0, ntrk_x2[i] ) );
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
      } // end if dark-pions
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
      } // end if k-shorts
    } // end if mc


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
    // sum-pt (Ht), ntracks (in event, for various types of tracks), sum of vertex masses / invariant mass of vertices in system
    for ( size_t i = 0; i != hDV.size(); ++i ) {
      // vertex basics
      std::string hdv    = hDV   [i] + "DV"; hdv[0] = tolower(hdv[0]);
      std::string hdvstr = hDVstr[i];        hdvstr.pop_back(); hdvstr += " DV";
      h_dv_n            .push_back( book( name, hdv + "_n",           "n " + hdvstr + "s",                     15,    0,   15 ) );
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
      }	
    } // end loop over DV types
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
    }


    // --- CUTFLOWS --- //
    // --> jet cutflow
    std::vector<TH1F*>              h_evt_testcutflow_j,           h_evt_testcutflow_leadj;
    std::vector<TH1F*>              h_evt_testcutfloweff_j,        h_evt_testcutfloweff_leadj;
    std::vector<std::vector<TH1F*>> h_evt_testcutflow_svntrkj,     h_evt_testcutflow_leadsvntrkj;
    std::vector<std::vector<TH1F*>> h_evt_testcutflow_svnjtrkj,    h_evt_testcutflow_leadsvnjtrkj;
    std::vector<std::vector<TH1F*>> h_evt_testcutflow_svtrkj,      h_evt_testcutflow_leadsvtrkj;
    std::vector<std::vector<TH1F*>> h_evt_testcutflow_svnj,        h_evt_testcutflow_leadsvnj;
    std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svntrkj,  h_evt_testcutfloweff_leadsvntrkj;
    std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svnjtrkj, h_evt_testcutfloweff_leadsvnjtrkj;
    std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svtrkj,   h_evt_testcutfloweff_leadsvtrkj;
    std::vector<std::vector<TH1F*>> h_evt_testcutfloweff_svnj,     h_evt_testcutfloweff_leadsvnj;
    std::vector<TH1F*>              h_evt_cutflow_j,               h_evt_cutflow_leadj;
    std::vector<TH1F*>              h_evt_cutfloweff_j,            h_evt_cutfloweff_leadj;
    std::vector<std::string> cj,    clj;
    std::vector<std::string> cjstr, cljstr;
    cj     .push_back( "jet" );
    cjstr  .push_back( "jet" );
    clj    .push_back( "leadJet"  );
    cljstr .push_back( "lead jet" );
    if ( m_mc && m_histoInfoSwitch->m_jetTruth ) {
      std::vector<std::string> mJ    = { "darkMatch",    "nomatch"   };
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
	int nbin_cj    = m_nType1Js   / m_LJix;
	h_evt_testcutflow_j
	  .push_back( book( name, "evt_testCutflow_"           + cj [icj], cjstr [icj] + " test cutflow",            nbin_cj, 0, nbin_cj ) );
	h_evt_testcutflow_leadj
	  .push_back( book( name, "evt_testCutflow_"           + clj[icj], cljstr[icj] + " test cutflow",            nbin_cj, 0, nbin_cj ) );
	h_evt_testcutfloweff_j
	  .push_back( book( name, "evt_testCutflowEfficiency_" + cj [icj], cjstr [icj] + " test cutflow efficiency", nbin_cj, 0, nbin_cj ) );
	h_evt_testcutfloweff_leadj
	  .push_back( book( name, "evt_testCutflowEfficiency_" + clj[icj], cljstr[icj] + " test cutflow efficiency", nbin_cj, 0, nbin_cj ) );	
	for ( unsigned i1j = 0; i1j != m_nType1Js/m_LJix; ++i1j ) {
	  std::string tmpjstr = hJstr[i1j*m_LJix];
	  if ( tmpjstr.empty() ) tmpjstr = "all";
	  h_evt_testcutflow_j        [icj] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
	  h_evt_testcutflow_leadj    [icj] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
	  h_evt_testcutfloweff_j     [icj] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
	  h_evt_testcutfloweff_leadj [icj] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
	}

	int ncjt         = ( m_nType1Js - m_nType1SVJs ) / m_LJix;
	int ncjsvnt      = m_svNtrkJ_ix  / m_LJix + ncjt;
	int ncjsvnjt     = m_svNjtrkJ_ix / m_LJix + ncjt;
	int ncjsvt       = m_svTrkJ_ix   / m_LJix + ncjt;
	int ncjsvn       = m_svNJ_ix     / m_LJix + ncjt;
	int nbin_cjsvtrk = m_nJSVtrk.size()       + ncjt;
	int nbin_cjsv    = m_nJSV   .size()       + ncjt;
	std::vector<TH1F*> h_evt_testcut_svntrkj,     h_evt_testcut_leadsvntrkj;
	std::vector<TH1F*> h_evt_testcut_svnjtrkj,    h_evt_testcut_leadsvnjtrkj;
	std::vector<TH1F*> h_evt_testcut_svtrkj,      h_evt_testcut_leadsvtrkj;
	std::vector<TH1F*> h_evt_testcut_svnj,        h_evt_testcut_leadsvnj;
	std::vector<TH1F*> h_evt_testcuteff_svntrkj,  h_evt_testcuteff_leadsvntrkj;
	std::vector<TH1F*> h_evt_testcuteff_svnjtrkj, h_evt_testcuteff_leadsvnjtrkj;
	std::vector<TH1F*> h_evt_testcuteff_svtrkj,   h_evt_testcuteff_leadsvtrkj;
	std::vector<TH1F*> h_evt_testcuteff_svnj,     h_evt_testcuteff_leadsvnj;
	for ( size_t ijsv = 0; ijsv != JSV.size(); ++ijsv ) {
	  // nsv-ntrk
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNtrkJets ) {
	    h_evt_testcut_svntrkj
	      .push_back( book( name, "evt_testCutflow_"           + cj [icj] + JSV[ijsv] + "Ntrk",
				JSVstr[ijsv] + "-Ntrk "  + cjstr [icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    h_evt_testcut_leadsvntrkj
	      .push_back( book( name, "evt_testCutflow_"           + clj[icj] + JSV[ijsv] + "Ntrk",
				JSVstr[ijsv] + "-Ntrk "  + cljstr[icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    h_evt_testcuteff_svntrkj
	      .push_back( book( name, "evt_testCutflowEfficiency_" + cj [icj] + JSV[ijsv] + "Ntrk",
				JSVstr[ijsv] + "-Ntrk "  + cjstr [icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    h_evt_testcuteff_leadsvntrkj
	      .push_back( book( name, "evt_testCutflowEfficiency_" + clj[icj] + JSV[ijsv] + "Ntrk",
				JSVstr[ijsv] + "-Ntrk "  + cljstr[icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	  }
	  // nsv-njtrk
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvNjtrkJets ) {
	    h_evt_testcut_svnjtrkj
	      .push_back( book( name, "evt_testCutflow_"           + cj [icj] + JSV[ijsv] + "Njtrk",
				JSVstr[ijsv] + "-Njtrk " + cjstr [icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    h_evt_testcut_leadsvnjtrkj
	      .push_back( book( name, "evt_testCutflow_"           + clj[icj] + JSV[ijsv] + "Njtrk",
				JSVstr[ijsv] + "-Njtrk " + cljstr[icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    h_evt_testcuteff_svnjtrkj
	      .push_back( book( name, "evt_testCutflowEfficiency_" + cj [icj] + JSV[ijsv] + "Njtrk",
				JSVstr[ijsv] + "-Njtrk " + cjstr [icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    h_evt_testcuteff_leadsvnjtrkj
	      .push_back( book( name, "evt_testCutflowEfficiency_" + clj[icj] + JSV[ijsv] + "Njtrk",
				JSVstr[ijsv] + "-Njtrk " + cljstr[icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	  }
	  // nsv-trk
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvTrkJets   ) {
	    h_evt_testcut_svtrkj
	      .push_back( book( name, "evt_testCutflow_"           + cj[icj] + JSV[ijsv] + "Trk",
				JSVstr[ijsv] + "-trk "   + cjstr [icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    h_evt_testcut_leadsvtrkj
	      .push_back( book( name, "evt_testCutflow_"           + clj[icj] + JSV[ijsv] + "Trk",
				JSVstr[ijsv] + "-trk "   + cljstr[icj] + " test cutflow",            nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    h_evt_testcuteff_svtrkj
	      .push_back( book( name, "evt_testCutflowEfficiency_" + cj [icj] + JSV[ijsv] + "Trk",
				JSVstr[ijsv] + "-trk "   + cjstr [icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	    h_evt_testcuteff_leadsvtrkj
	      .push_back( book( name, "evt_testCutflowEfficiency_" + clj[icj] + JSV[ijsv] + "Trk",
				JSVstr[ijsv] + "-trk "   + cljstr[icj] + " test cutflow efficiency", nbin_cjsvtrk, 0, nbin_cjsvtrk ) );
	  }
	  // nsv
	  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvJets      ) {
	    h_evt_testcut_svnj
	      .push_back( book( name, "evt_testCutflow_"           + cj [icj] + JSV[ijsv],
				JSVstr[ijsv] + " "       + cjstr[icj] + " test cutflow",             nbin_cjsv,    0, nbin_cjsv    ) );
	    h_evt_testcut_leadsvnj
	      .push_back( book( name, "evt_testCutflow_"           + clj[icj] + JSV[ijsv],
				JSVstr[ijsv] + " "       + cljstr[icj] + " test cutflow",            nbin_cjsv,    0, nbin_cjsv    ) );
	    h_evt_testcuteff_svnj
	      .push_back( book( name, "evt_testCutflowEfficiency_" + cj [icj] + JSV[ijsv],
				JSVstr[ijsv] + " "       + cjstr [icj] + " test cutflow efficiency", nbin_cjsv,    0, nbin_cjsv    ) );
	    h_evt_testcuteff_leadsvnj
	      .push_back( book( name, "evt_testCutflowEfficiency_" + clj[icj] + JSV[ijsv],
				JSVstr[ijsv] + " "       + cljstr[icj] + " test cutflow efficiency", nbin_cjsv,    0, nbin_cjsv    ) );
	  }
	  // --> label bins
	  for ( unsigned i1j = 0; i1j != m_nType1Js/m_LJix; ++i1j ) {
	    std::string tmpjstr = hJstr[i1j*m_LJix];
	    if ( tmpjstr.empty() ) tmpjstr = "all";
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
	  h_evt_testcutfloweff_leadsvtrkj   .push_back( h_evt_testcuteff_leadsvntrkj  );
	}
	// nsv
	if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvJets      ) {
	  h_evt_testcutflow_svnj            .push_back( h_evt_testcut_svnj            );
	  h_evt_testcutflow_leadsvnj        .push_back( h_evt_testcut_leadsvnj        );
	  h_evt_testcutfloweff_svnj         .push_back( h_evt_testcuteff_svnj         );
	  h_evt_testcutfloweff_leadsvnj     .push_back( h_evt_testcuteff_leadsvnj     );
	}
	
      } // end if m_nType1Js
      
      // h_evt_cutflow_j
      // 	.push_back( book( name, "evt_cutflow_"           + cj [icj], cjstr [icj] + " cutflow",            hEJstr.size(), 0, hEJstr.size() ) );
      // h_evt_cutflow_leadj
      // 	.push_back( book( name, "evt_cutflow_"           + clj[icj], cljstr[icj] + " cutflow",            hEJstr.size(), 0, hEJstr.size() ) );
      // h_evt_cutfloweff_j
      // 	.push_back( book( name, "evt_cutflowEfficiency_" + cj [icj], cjstr [icj] + " cutflow efficiency", hEJstr.size(), 0, hEJstr.size() ) );
      // h_evt_cutfloweff_leadj
      // 	.push_back( book( name, "evt_cutflowEfficiency_" + clj[icj], cljstr[icj] + " cutflow efficiency", hEJstr.size(), 0, hEJstr.size() ) );
      // for ( const auto& ej : hEJstr ) {
      // 	std::string tmpjstr = ej;
      // 	if ( tmpjstr.empty() ) tmpjstr = "all";
      // 	h_evt_cutflow_j        [icj] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
      // 	h_evt_cutflow_leadj    [icj] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
      // 	h_evt_cutfloweff_j     [icj] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
      // 	h_evt_cutfloweff_leadj [icj] ->GetXaxis()->FindBin( ( tmpjstr ).c_str() );
      // }
    }
    if ( m_nType1Js ) {
      h_evt_testCutflow_jet               .push_back( h_evt_testcutflow_j        );
      h_evt_testCutflow_leadjet           .push_back( h_evt_testcutflow_leadj    );
      h_evt_testCutflowEfficiency_jet     .push_back( h_evt_testcutfloweff_j     );
      h_evt_testCutflowEfficiency_leadjet .push_back( h_evt_testcutfloweff_leadj );

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
    // h_evt_cutflow_jet                     .push_back( h_evt_cutflow_j            );
    // h_evt_cutflow_leadjet                 .push_back( h_evt_cutflow_leadj        );
    // h_evt_cutflowEfficiency_jet           .push_back( h_evt_cutfloweff_j         );
    // h_evt_cutflowEfficiency_leadjet       .push_back( h_evt_cutfloweff_leadj     );
    
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
	  for ( int jndv = 0; jndv != m_ndv; ++jndv ) {
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


    // --- OVERALL EFFICIENCIES --- //
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
      h_abcd_nDV_NJetHt          .push_back( h_abcd_ndv_njetHt          );
      h_abcd_nDV_NJetHt_vrsh     .push_back( h_abcd_ndv_njetHt_vrsh     );
      h_abcd_raw_nDV_NJetHt      .push_back( h_abcd_raw_ndv_njetHt      );
      h_abcd_raw_nDV_NJetHt_vrsh .push_back( h_abcd_raw_ndv_njetHt_vrsh );
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
      h_NJetHt      [ireg] ->Fill( m_njetHt,                    weight );
      h_NJetHt_vrsh [ireg] ->Fill( m_njetHt * m_VRshift_njetHt, weight );
    }


    
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
    std::vector<float> p4_dijet_sum_dr    ( m_nTypeJs, 0 );
    std::vector<int>   p4_dijet_sum_count ( m_nTypeJs, 0 );

    std::vector<int> firstDijet ( m_nTypeJs, 1 ); // test for first dijet of given type

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
	if ( m_histoInfoSwitch->m_dijets ) {
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
	    p4_dijet_sum_dr    [ij] += jj_dR;
	    p4_dijet_sum_count [ij] += 1;
	    
	  } // end loop over dijets
	} // end if m_dijets info switch
      } // end loop over jet types
    } // end double loop over jets


    // ---> (N)JETS
    // set vectors of n-jet sum-p4
    std::vector<int> n_jet ( m_nTypeJs, 0 );
    TLorentzVector jp4sum;
    jp4sum.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<TLorentzVector> jet_p4_sum   ( m_nTypeJs, jp4sum );
    std::vector<float>          jet_p4_sumPt ( m_nTypeJs, 0      );
    // --> tracks
    TLorentzVector jp4sum_trk;
    jp4sum_trk.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> jetTracks_p4_sum
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeTrks, jp4sum_trk ) );
    std::vector<std::vector<float>> jetTracks_p4_sumPt   ( m_nTypeJs, std::vector<float> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>>   jetTracks_n          ( m_nTypeJs, std::vector<int>   ( m_nTypeTrks, 0 ) );
    TLorentzVector jjp4max_trk;
    TLorentzVector jjp4min_trk;
    jjp4max_trk.SetPtEtaPhiM( 0, 0, 0, 0 );
    jjp4min_trk.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> dijetTracks_p4_max
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeTrks, jjp4max_trk ) );
    std::vector<std::vector<TLorentzVector>> dijetTracks_p4_min
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeTrks, jjp4min_trk ) );
    std::vector<std::vector<int>> dijetTracks_p4_max_sumPt ( m_nTypeJs, std::vector<int> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>> dijetTracks_p4_min_sumPt ( m_nTypeJs, std::vector<int> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>> dijetTracks_p4_max_n     ( m_nTypeJs, std::vector<int> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>> dijetTracks_p4_min_n     ( m_nTypeJs, std::vector<int> ( m_nTypeTrks, 0 ) );
    TLorentzVector jjp4maxpt_trk;
    TLorentzVector jjp4minpt_trk;
    jjp4maxpt_trk.SetPtEtaPhiM( 0, 0, 0, 0 );
    jjp4minpt_trk.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> dijetTracks_p4_maxpt
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeTrks, jjp4maxpt_trk ) );
    std::vector<std::vector<TLorentzVector>> dijetTracks_p4_minpt
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeTrks, jjp4minpt_trk ) );
    std::vector<std::vector<int>> dijetTracks_p4_maxpt_sumPt ( m_nTypeJs, std::vector<int> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>> dijetTracks_p4_minpt_sumPt ( m_nTypeJs, std::vector<int> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>> dijetTracks_p4_maxpt_n     ( m_nTypeJs, std::vector<int> ( m_nTypeTrks, 0 ) );
    std::vector<std::vector<int>> dijetTracks_p4_minpt_n     ( m_nTypeJs, std::vector<int> ( m_nTypeTrks, 0 ) );
    // --> secondary vertices
    TLorentzVector jp4sum_sv;
    jp4sum_sv.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> jetSecVerts_p4_sum
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeJDVs, jp4sum_sv  ) );
    std::vector<std::vector<float>> jetSecVerts_p4_sumPt ( m_nTypeJs, std::vector<float> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>>   jetSecVerts_n        ( m_nTypeJs, std::vector<int>   ( m_nTypeJDVs, 0 ) );
    TLorentzVector jjp4max_sv;
    TLorentzVector jjp4min_sv;
    jjp4max_sv.SetPtEtaPhiM( 0, 0, 0, 0 );
    jjp4min_sv.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> dijetSecVerts_p4_max
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeJDVs, jjp4max_sv ) );
    std::vector<std::vector<TLorentzVector>> dijetSecVerts_p4_min
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeJDVs, jjp4min_sv ) );
    std::vector<std::vector<int>> dijetSecVerts_p4_max_sumPt ( m_nTypeJs, std::vector<int> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>> dijetSecVerts_p4_min_sumPt ( m_nTypeJs, std::vector<int> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>> dijetSecVerts_p4_max_n     ( m_nTypeJs, std::vector<int> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>> dijetSecVerts_p4_min_n     ( m_nTypeJs, std::vector<int> ( m_nTypeJDVs, 0 ) );
    TLorentzVector jjp4maxpt_sv;
    TLorentzVector jjp4minpt_sv;
    jjp4maxpt_sv.SetPtEtaPhiM( 0, 0, 0, 0 );
    jjp4minpt_sv.SetPtEtaPhiM( 0, 0, 0, 0 );
    std::vector<std::vector<TLorentzVector>> dijetSecVerts_p4_maxpt
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeJDVs, jjp4maxpt_sv ) );
    std::vector<std::vector<TLorentzVector>> dijetSecVerts_p4_minpt
      ( m_nTypeJs, std::vector<TLorentzVector> ( m_nTypeJDVs, jjp4minpt_sv ) );
    std::vector<std::vector<int>> dijetSecVerts_p4_maxpt_sumPt ( m_nTypeJs, std::vector<int> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>> dijetSecVerts_p4_minpt_sumPt ( m_nTypeJs, std::vector<int> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>> dijetSecVerts_p4_maxpt_n     ( m_nTypeJs, std::vector<int> ( m_nTypeJDVs, 0 ) );
    std::vector<std::vector<int>> dijetSecVerts_p4_minpt_n     ( m_nTypeJs, std::vector<int> ( m_nTypeJDVs, 0 ) );
    
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
	int inj  = ij / m_LJix;                // index of lead jet type in jet type vector
	//int ilbj = n_jet[ij % m_nTypeBJs] - 1; // index of lead jet base jet container

	// sum p4 for all jets in event
	jet_p4_sum   [ij] += jet_p4;
	jet_p4_sumPt [ij] += jet_p4.Pt();
	  
	if ( !doHists ) continue;
	
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
	//if ( m_numLeadJets && ilbj < m_numLeadJets ) {
	if ( m_numLeadJets && i < m_numLeadJets ) {
	  //h_jetN_pt        [ireg][inj][ilbj] ->Fill( m_jet_pt        ->at(i), weight );
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

	    if ( doHists ) {
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
	    
	  } // end loop over matched track types
	} // end loop over matched tracks
      
	// fill matched track count, min/max/sum, n-track-p4 histograms
	for ( unsigned jt = 0; jt != m_nTypeTrks; ++jt ) {
	  if ( doHists ) {
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
	  // sum p4 for all matched tracks in min/max dijets
	  if ( m_histoInfoSwitch->m_dijets ) {
	    int maxix1 = p4_dijet_max_ix[ij].first; int maxix2 = p4_dijet_max_ix[ij].second;
	    int minix1 = p4_dijet_min_ix[ij].first; int minix2 = p4_dijet_min_ix[ij].second;
	    if ( m_jet_index ->at(i) == maxix1   || m_jet_index ->at(i) == maxix2   ) {
	      dijetTracks_p4_max         [ij][jt] += jettrk_p4_sum   [jt];
	      dijetTracks_p4_max_sumPt   [ij][jt] += jettrk_p4_sumPt [jt];
	      dijetTracks_p4_max_n       [ij][jt] += n_jettrk        [jt];
	    }
	    if ( m_jet_index ->at(i) == minix1   || m_jet_index ->at(i) == minix2   ) {
	      dijetTracks_p4_min         [ij][jt] += jettrk_p4_sum   [jt];
	      dijetTracks_p4_min_sumPt   [ij][jt] += jettrk_p4_sumPt [jt];
	      dijetTracks_p4_min_n       [ij][jt] += n_jettrk        [jt];
	    }
	    int maxptix1 = p4_dijet_maxpt_ix[ij].first; int maxptix2 = p4_dijet_maxpt_ix[ij].second;
	    int minptix1 = p4_dijet_minpt_ix[ij].first; int minptix2 = p4_dijet_minpt_ix[ij].second;
	    if ( m_jet_index ->at(i) == maxptix1 || m_jet_index ->at(i) == maxptix2 ) {
	      dijetTracks_p4_maxpt       [ij][jt] += jettrk_p4_sum   [jt];
	      dijetTracks_p4_maxpt_sumPt [ij][jt] += jettrk_p4_sumPt [jt];
	      dijetTracks_p4_maxpt_n     [ij][jt] += n_jettrk        [jt];
	    }
	    if ( m_jet_index ->at(i) == minptix1 || m_jet_index ->at(i) == minptix2 ) {
	      dijetTracks_p4_minpt       [ij][jt] += jettrk_p4_sum   [jt];
	      dijetTracks_p4_minpt_sumPt [ij][jt] += jettrk_p4_sumPt [jt];
	      dijetTracks_p4_minpt_n     [ij][jt] += n_jettrk        [jt];
	    }
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
	  getDVTypes( jetSvIx, jetsv, base_dv, true );
	  // loop over matched secondary vertex types
	  for ( size_t jv = 0; jv != jetsv.size(); ++jv ) {
	    if ( !jetsv[jv] ) continue;
	    ++n_jetsv[jv];

	    if ( doHists ) {
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
	  if ( doHists ) {
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
	  // sum p4 for all matched secondary vertices in min/max dijets
	  if ( m_histoInfoSwitch->m_dijets ) {
	    int maxix1 = p4_dijet_max_ix[ij].first; int maxix2 = p4_dijet_max_ix[ij].second;
	    int minix1 = p4_dijet_min_ix[ij].first; int minix2 = p4_dijet_min_ix[ij].second;
	    if ( m_jet_index ->at(i) == maxix1   || m_jet_index ->at(i) == maxix2   ) {
	      dijetSecVerts_p4_max         [ij][jv] += jetsv_p4_sum   [jv];
	      dijetSecVerts_p4_max_sumPt   [ij][jv] += jetsv_p4_sumPt [jv];
	      dijetSecVerts_p4_max_n       [ij][jv] += n_jetsv        [jv];
	    }
	    if ( m_jet_index ->at(i) == minix1   || m_jet_index ->at(i) == minix2   ) {
	      dijetSecVerts_p4_min         [ij][jv] += jetsv_p4_sum   [jv];
	      dijetSecVerts_p4_min_sumPt   [ij][jv] += jetsv_p4_sumPt [jv];
	      dijetSecVerts_p4_min_n       [ij][jv] += n_jetsv        [jv];
	    }
	    int maxptix1 = p4_dijet_maxpt_ix[ij].first; int maxptix2 = p4_dijet_maxpt_ix[ij].second;
	    int minptix1 = p4_dijet_minpt_ix[ij].first; int minptix2 = p4_dijet_minpt_ix[ij].second;
	    if ( m_jet_index ->at(i) == maxptix1 || m_jet_index ->at(i) == maxptix2 ) {
	      dijetSecVerts_p4_maxpt       [ij][jv] += jetsv_p4_sum   [jv];
	      dijetSecVerts_p4_maxpt_sumPt [ij][jv] += jetsv_p4_sumPt [jv];
	      dijetSecVerts_p4_maxpt_n     [ij][jv] += n_jetsv        [jv];
	    }
	    if ( m_jet_index ->at(i) == minptix1 || m_jet_index ->at(i) == minptix2 ) {
	      dijetSecVerts_p4_minpt       [ij][jv] += jetsv_p4_sum   [jv];
	      dijetSecVerts_p4_minpt_sumPt [ij][jv] += jetsv_p4_sumPt [jv];
	      dijetSecVerts_p4_minpt_n     [ij][jv] += n_jetsv        [jv];
	    }
	  } 
	} // end loop over jet vertex types
	
      } // end loop over jet types

      // do jet cutflow
      // --> test cuts
      if ( m_nType1Js ) {
	std::vector<int> jet_testCut;
	getJetTypes( i, jet_testCut, base_dv, false, false, false );
	std::vector<int>     jetTestCut ( jet_testCut.size() / m_nType1Js, 0 );
	std::vector<int> leadjetTestCut ( jet_testCut.size() / m_nType1Js, 0 );
	for ( size_t ijc = 0; ijc != jet_testCut.size() / m_LJix; ++ijc ) {
	  jetTestCut    [ijc*m_LJix / m_nType1Js] += jet_testCut[ijc*m_LJix  ];
	  leadjetTestCut[ijc*m_LJix / m_nType1Js] += jet_testCut[ijc*m_LJix+1];
	  h_evt_testCutflow_jet     [ireg][ijc*m_LJix / m_nType1Js]
	    ->Fill( ijc % (m_nType1Js/m_LJix), (     jetTestCut[ijc*m_LJix/m_nType1Js] / ( ijc % (m_nType1Js/m_LJix) + 1 ) ) * weight );
	  h_evt_testCutflow_leadjet [ireg][ijc*m_LJix / m_nType1Js]
	    ->Fill( ijc % (m_nType1Js/m_LJix), ( leadjetTestCut[ijc*m_LJix/m_nType1Js] / ( ijc % (m_nType1Js/m_LJix) + 1 ) ) * weight );
	}
      }
      // // --> "emerging" cuts
      // std::vector<int> jet_cut;
      // getJetTypes( i, jet_cut, base_dv, false, true, true );
      // int n_ejCuts = jet_cut.size() / h_evt_cutflow_jet [ireg].size();
      // std::vector<int>     jetCut ( h_evt_cutflow_jet [ireg].size(), 0 );
      // std::vector<int> leadjetCut ( h_evt_cutflow_jet [ireg].size(), 0 );
      // for ( size_t ijc = 0; ijc != jet_cut.size() / m_LJix; ++ijc ) {
      // 	jetCut     [ijc*m_LJix / n_ejCuts] += jet_cut[ijc*m_LJix  ];
      // 	leadjetCut [ijc*m_LJix / n_ejCuts] += jet_cut[ijc*m_LJix+1];
      // 	h_evt_cutflow_jet     [ireg][ijc*m_LJix / n_ejCuts]
      // 	  ->Fill( ijc % (n_ejCuts/m_LJix), (     jetCut[ijc*m_LJix/n_ejCuts] / ( ijc % (n_ejCuts/m_LJix) + 1 ) ) * weight );
      // 	h_evt_cutflow_leadjet [ireg][ijc*m_LJix / n_ejCuts]
      // 	  ->Fill( ijc % (n_ejCuts/m_LJix), ( leadjetCut[ijc*m_LJix/n_ejCuts] / ( ijc % (n_ejCuts/m_LJix) + 1 ) ) * weight );
      // }
		  
    } // end loop over jets

    // fill jet count, min/max/avg-dijet, njet histograms
    if ( doHists ) {
      for ( size_t ij = 0; ij != n_jet.size(); ++ij ) {
	h_jet_n [ireg][ij] ->Fill( n_jet[ij], weight );

	if ( m_histoInfoSwitch->m_dijets ) {
	  int sum_ct = p4_dijet_sum_count [ij];
	  h_dijet_n [ireg][ij] ->Fill( sum_ct, weight );

	  if ( sum_ct ) {
	    h_dijet_avgp4_pt    [ireg][ij] ->Fill( p4_dijet_sum_pt   [ij]/sum_ct, weight );
	    h_dijet_avgp4_eta   [ireg][ij] ->Fill( p4_dijet_sum_eta  [ij]/sum_ct, weight );
	    h_dijet_avgp4_phi   [ireg][ij] ->Fill( p4_dijet_sum_phi  [ij]/sum_ct, weight );
	    h_dijet_avgp4_m     [ireg][ij] ->Fill( p4_dijet_sum_m    [ij]/sum_ct, weight );
	    h_dijet_avgp4_sumPt [ireg][ij] ->Fill( p4_dijet_sum_sumpt[ij]/sum_ct, weight );
	    h_dijet_avgp4_dR    [ireg][ij] ->Fill( p4_dijet_sum_dr   [ij]/sum_ct, weight );
	    
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
	    h_dijet_maxp4_sumPt [ireg][ij] ->Fill( max_sumpt,              weight );
	    h_dijet_maxp4_dR    [ireg][ij] ->Fill( max_dr,                 weight );
	    for ( unsigned ijtrk = 0; ijtrk != m_nTypeTrks; ++ijtrk ) {
	      h_dijet_maxp4_ntrk         [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max_n       [ij][ijtrk],       weight );
	      if ( m_histoInfoSwitch->m_jetTrks  && dijetTracks_p4_max_n   [ij][ijtrk]  ) {
		h_dijet_maxp4_ntrk_pt    [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max         [ij][ijtrk].Pt(),  weight );
	    	h_dijet_maxp4_ntrk_eta   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max         [ij][ijtrk].Eta(), weight );
	    	h_dijet_maxp4_ntrk_phi   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max         [ij][ijtrk].Phi(), weight );
	    	h_dijet_maxp4_ntrk_m     [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max         [ij][ijtrk].M(),   weight );
	    	h_dijet_maxp4_ntrk_sumPt [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_max_sumPt   [ij][ijtrk],       weight );
	      }
	    }
	    for ( unsigned ijsv = 0;  ijsv != m_nTypeJDVs;  ++ijsv ) {
	      h_dijet_maxp4_nsv          [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max_n     [ij][ijsv],        weight );
	      if ( m_histoInfoSwitch->m_jetVerts && dijetSecVerts_p4_max_n [ij][ijsv] ) {
	    	h_dijet_maxp4_nsv_pt     [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max       [ij][ijsv].Pt(),   weight );
	    	h_dijet_maxp4_nsv_eta    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max       [ij][ijsv].Eta(),  weight );
	    	h_dijet_maxp4_nsv_phi    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max       [ij][ijsv].Phi(),  weight );
	    	h_dijet_maxp4_nsv_m      [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max       [ij][ijsv].M(),    weight );
	    	h_dijet_maxp4_nsv_sumPt  [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_max_sumPt [ij][ijsv],        weight );
	      }
	    }
	    
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
	    h_dijet_minp4_sumPt [ireg][ij] ->Fill( min_sumpt,              weight );
	    h_dijet_minp4_dR    [ireg][ij] ->Fill( min_dr,                 weight );
	    for ( unsigned ijtrk = 0; ijtrk != m_nTypeTrks; ++ijtrk ) {
	      h_dijet_minp4_ntrk         [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min_n       [ij][ijtrk],       weight );
	      if ( m_histoInfoSwitch->m_jetTrks  && dijetTracks_p4_min_n   [ij][ijtrk] ) {
	    	h_dijet_minp4_ntrk_pt    [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min         [ij][ijtrk].Pt(),  weight );
	    	h_dijet_minp4_ntrk_eta   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min         [ij][ijtrk].Eta(), weight );
	    	h_dijet_minp4_ntrk_phi   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min         [ij][ijtrk].Phi(), weight );
	    	h_dijet_minp4_ntrk_m     [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min         [ij][ijtrk].M(),   weight );
	    	h_dijet_minp4_ntrk_sumPt [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_min_sumPt   [ij][ijtrk],       weight );
	      }
	    }
	    for ( unsigned ijsv = 0;  ijsv != m_nTypeJDVs;  ++ijsv ) {
	      h_dijet_minp4_nsv          [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min_n     [ij][ijsv],        weight );
	      if ( m_histoInfoSwitch->m_jetVerts && dijetSecVerts_p4_min_n [ij][ijsv] ) {
	    	h_dijet_minp4_nsv_pt     [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min       [ij][ijsv].Pt(),   weight );
	    	h_dijet_minp4_nsv_eta    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min       [ij][ijsv].Eta(),  weight );
	    	h_dijet_minp4_nsv_phi    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min       [ij][ijsv].Phi(),  weight );
	    	h_dijet_minp4_nsv_m      [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min       [ij][ijsv].M(),    weight );
	    	h_dijet_minp4_nsv_sumPt  [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_min_sumPt [ij][ijsv],        weight );
	      }
	    }

	    int   maxpt_ix1   = p4_dijet_maxpt_ix[ij].first;
	    int   maxpt_ix2   = p4_dijet_maxpt_ix[ij].second;
	    float maxpt_sumpt = 0;
	    float maxpt_dr    = 0;
	    if ( maxpt_ix1 != -1 && maxpt_ix2 != -1 ) {
	      maxpt_sumpt = m_jet_pt->at(maxpt_ix1) + m_jet_pt->at(maxpt_ix2);
	      maxpt_dr    = EJsHelper::deltaR( m_jet_eta->at(maxpt_ix1), m_jet_eta->at(maxpt_ix2),
					       m_jet_phi->at(maxpt_ix1), m_jet_phi->at(maxpt_ix2) );
	    }
	    h_dijet_maxpt_pt    [ireg][ij] ->Fill( p4_dijet_maxpt[ij].Pt(),  weight );
	    h_dijet_maxpt_eta   [ireg][ij] ->Fill( p4_dijet_maxpt[ij].Eta(), weight );
	    h_dijet_maxpt_phi   [ireg][ij] ->Fill( p4_dijet_maxpt[ij].Phi(), weight );
	    h_dijet_maxpt_m     [ireg][ij] ->Fill( p4_dijet_maxpt[ij].M(),   weight );
	    h_dijet_maxpt_sumPt [ireg][ij] ->Fill( maxpt_sumpt,              weight );
	    h_dijet_maxpt_dR    [ireg][ij] ->Fill( maxpt_dr,                 weight );
	    for ( unsigned ijtrk = 0; ijtrk != m_nTypeTrks; ++ijtrk ) {
	      h_dijet_maxpt_ntrk         [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt_n       [ij][ijtrk],       weight );
	      if ( m_histoInfoSwitch->m_jetTrks  && dijetTracks_p4_maxpt_n   [ij][ijtrk] ) {
		h_dijet_maxpt_ntrk_pt    [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt         [ij][ijtrk].Pt(),  weight );
	    	h_dijet_maxpt_ntrk_eta   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt         [ij][ijtrk].Eta(), weight );
	    	h_dijet_maxpt_ntrk_phi   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt         [ij][ijtrk].Phi(), weight );
	    	h_dijet_maxpt_ntrk_m     [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt         [ij][ijtrk].M(),   weight );
	    	h_dijet_maxpt_ntrk_sumPt [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_maxpt_sumPt   [ij][ijtrk],       weight );
	      }
	    }
	    for ( unsigned ijsv = 0;  ijsv != m_nTypeJDVs;  ++ijsv  ) {
	      h_dijet_maxpt_nsv          [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt_n     [ij][ijsv],        weight );
	      if ( m_histoInfoSwitch->m_jetVerts && dijetSecVerts_p4_maxpt_n [ij][ijsv] ) {
	    	h_dijet_maxpt_nsv_pt     [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt       [ij][ijsv].Pt(),   weight );
	    	h_dijet_maxpt_nsv_eta    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt       [ij][ijsv].Eta(),  weight );
	    	h_dijet_maxpt_nsv_phi    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt       [ij][ijsv].Phi(),  weight );
	    	h_dijet_maxpt_nsv_m      [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt       [ij][ijsv].M(),    weight );
	    	h_dijet_maxpt_nsv_sumPt  [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_maxpt_sumPt [ij][ijsv],        weight );
	      }
	    }

	    int   minpt_ix1   = p4_dijet_minpt_ix[ij].first;
	    int   minpt_ix2   = p4_dijet_minpt_ix[ij].second;
	    float minpt_sumpt = 0;
	    float minpt_dr    = 0;
	    if ( minpt_ix1 != -1 && minpt_ix2 != -1 ) {
	      minpt_sumpt = m_jet_pt->at(minpt_ix1) + m_jet_pt->at(minpt_ix2);
	      minpt_dr    = EJsHelper::deltaR( m_jet_eta->at(minpt_ix1), m_jet_eta->at(minpt_ix2),
					       m_jet_phi->at(minpt_ix1), m_jet_phi->at(minpt_ix2) );
	    }
	    h_dijet_minpt_pt    [ireg][ij] ->Fill( p4_dijet_minpt[ij].Pt(),  weight );
	    h_dijet_minpt_eta   [ireg][ij] ->Fill( p4_dijet_minpt[ij].Eta(), weight );
	    h_dijet_minpt_phi   [ireg][ij] ->Fill( p4_dijet_minpt[ij].Phi(), weight );
	    h_dijet_minpt_m     [ireg][ij] ->Fill( p4_dijet_minpt[ij].M(),   weight );
	    h_dijet_minpt_sumPt [ireg][ij] ->Fill( minpt_sumpt,              weight );
	    h_dijet_minpt_dR    [ireg][ij] ->Fill( minpt_dr,                 weight );
	    for ( unsigned ijtrk = 0; ijtrk != m_nTypeTrks; ++ijtrk ) {
	      h_dijet_minpt_ntrk         [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt_n       [ij][ijtrk],       weight );
	      if ( m_histoInfoSwitch->m_jetTrks  && dijetTracks_p4_minpt_n   [ij][ijtrk] ) {
		h_dijet_minpt_ntrk_pt    [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt         [ij][ijtrk].Pt(),  weight );
	    	h_dijet_minpt_ntrk_eta   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt         [ij][ijtrk].Eta(), weight );
	    	h_dijet_minpt_ntrk_phi   [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt         [ij][ijtrk].Phi(), weight );
	    	h_dijet_minpt_ntrk_m     [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt         [ij][ijtrk].M(),   weight );
	    	h_dijet_minpt_ntrk_sumPt [ireg][ij][ijtrk] ->Fill( dijetTracks_p4_minpt_sumPt   [ij][ijtrk],       weight );
	      }
	    }
	    for ( unsigned ijsv = 0;  ijsv != m_nTypeJDVs;  ++ijsv  ) {
	      h_dijet_minpt_nsv          [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt_n     [ij][ijsv],        weight );
	      if ( m_histoInfoSwitch->m_jetVerts && dijetSecVerts_p4_minpt_n [ij][ijsv] ) {
	    	h_dijet_minpt_nsv_pt     [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt       [ij][ijsv].Pt(),   weight );
	    	h_dijet_minpt_nsv_eta    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt       [ij][ijsv].Eta(),  weight );
	    	h_dijet_minpt_nsv_phi    [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt       [ij][ijsv].Phi(),  weight );
	    	h_dijet_minpt_nsv_m      [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt       [ij][ijsv].M(),    weight );
	    	h_dijet_minpt_nsv_sumPt  [ireg][ij][ijsv]  ->Fill( dijetSecVerts_p4_minpt_sumPt [ij][ijsv],        weight );
	      }
	    }
	  } // end if sum_ct
	} // end if dijets

	// event level jet variables
	if ( m_histoInfoSwitch->m_njets && n_jet[ij] ) {
	  h_njet_pt    [ireg][ij] ->Fill( jet_p4_sum  [ij].Pt(),  weight );
	  h_njet_eta   [ireg][ij] ->Fill( jet_p4_sum  [ij].Eta(), weight );
	  h_njet_phi   [ireg][ij] ->Fill( jet_p4_sum  [ij].Phi(), weight );
	  h_njet_m     [ireg][ij] ->Fill( jet_p4_sum  [ij].M(),   weight );
	  h_njet_sumPt [ireg][ij] ->Fill( jet_p4_sumPt[ij],       weight ); 
	  for ( unsigned ijtrk = 0; ijtrk != m_nTypeTrks; ++ijtrk ) {
	    h_njet_ntrk         [ireg][ij][ijtrk] ->Fill( jetTracks_n          [ij][ijtrk],       weight );
	    if ( m_histoInfoSwitch->m_jetTrks  && jetTracks_n [ij][ijtrk] ) {
	      h_njet_ntrk_pt    [ireg][ij][ijtrk] ->Fill( jetTracks_p4_sum     [ij][ijtrk].Pt(),  weight );
	      h_njet_ntrk_eta   [ireg][ij][ijtrk] ->Fill( jetTracks_p4_sum     [ij][ijtrk].Eta(), weight );
	      h_njet_ntrk_phi   [ireg][ij][ijtrk] ->Fill( jetTracks_p4_sum     [ij][ijtrk].Phi(), weight );
	      h_njet_ntrk_m     [ireg][ij][ijtrk] ->Fill( jetTracks_p4_sum     [ij][ijtrk].M(),   weight );
	      h_njet_ntrk_sumPt [ireg][ij][ijtrk] ->Fill( jetTracks_p4_sumPt   [ij][ijtrk],       weight );
	    }
	  }
	  for ( unsigned ijsv = 0; ijsv != m_nTypeJDVs; ++ijsv ) {
	    h_njet_nsv          [ireg][ij][ijsv]  ->Fill( jetSecVerts_n        [ij][ijsv],        weight );
	    if ( m_histoInfoSwitch->m_jetVerts && jetSecVerts_n [ij][ijsv] ) {
	      h_njet_nsv_pt     [ireg][ij][ijsv]  ->Fill( jetSecVerts_p4_sum   [ij][ijsv] .Pt(),  weight );
	      h_njet_nsv_eta    [ireg][ij][ijsv]  ->Fill( jetSecVerts_p4_sum   [ij][ijsv] .Eta(), weight );
	      h_njet_nsv_phi    [ireg][ij][ijsv]  ->Fill( jetSecVerts_p4_sum   [ij][ijsv] .Phi(), weight );
	      h_njet_nsv_m      [ireg][ij][ijsv]  ->Fill( jetSecVerts_p4_sum   [ij][ijsv] .M(),   weight );
	      h_njet_nsv_sumPt  [ireg][ij][ijsv]  ->Fill( jetSecVerts_p4_sumPt [ij][ijsv],        weight );
	    }
	  }
	} // end if njets

	// NJet cutflow
	if ( ij >= m_nTypeBJs ) continue;
	for ( int inj = 0; inj != m_nJets+1; ++inj )
	if ( n_jet[ij] > inj-1 ) {
	    if ( ij % m_LJix == 0 )
	      h_evt_cutflow_NJet     [ireg][ij/m_LJix] ->Fill( inj, weight );
	    else if ( ij % m_LJix == 1 )
	      h_evt_cutflow_NLeadJet [ireg][ij/m_LJix] ->Fill( inj, weight );
	  }
	
      } // end loop over jet types
    } // end if doHists

    // find singular dijet invariant mass (average of dijet pairs of leading four jets with smallest difference between them)
    // --> note: this method only works for specific case of m_nJets = 4
    std::vector<std::pair<int,int>> dijet_indices;
    for ( int i = 0; i != m_jet_n; ++i ) {
      for ( int j = i+1; j != m_jet_n; ++j ) {
	if ( i >= m_nJets || j >= m_nJets ) continue;
	dijet_indices.push_back( std::make_pair( i, j ) );
      }
    }
    float mindiff         = AlgConsts::maxValue;
    float mindiff_invM    = 0;
    float mindiff_pt      = 0;
    float mindiff_ptdiff  = 0;
    float mindiff_eta     = 0;
    float mindiff_etadiff = 0;
    float mindiff_phi     = 0;
    float mindiff_phidiff = 0;
    float mindiff_sumpt   = 0;
    float mindiff_dR      = 0;
    for ( size_t i = 0; i != dijet_indices.size(); ++i ) {
      for ( size_t j = i+1; j != dijet_indices.size(); ++j ) {
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
	TLorentzVector p4_j12 = p4_j1 + p4_j2;
	TLorentzVector p4_j34 = p4_j3 + p4_j4;
	float avg_pt    =     ( p4_j12.Pt()  + p4_j34.Pt()  ) / 2;
	float avg_eta   =     ( p4_j12.Eta() + p4_j34.Eta() ) / 2;
	float avg_phi   =     ( p4_j12.Phi() + p4_j34.Phi() ) / 2;
	float avg_invM  =     ( p4_j12.M()   + p4_j34.M()   ) / 2;
	float diff_pt   = fabs( p4_j12.Pt()  - p4_j34.Pt()  );
	float diff_eta  = fabs( p4_j12.Eta() - p4_j34.Eta() );
	float diff_phi  = fabs( p4_j12.Phi() - p4_j34.Phi() );
	float diff_invM = fabs( p4_j12.M()   - p4_j34.M()   );
	float avg_sumPt =       p4_j12.Pt()  + p4_j34.Pt();
	float avg_dR    = EJsHelper::deltaR(   p4_j12.Eta(), p4_j34.Eta(), p4_j12.Phi(), p4_j34.Phi() );
	if ( diff_invM < mindiff ) {
	  mindiff         = diff_invM;
	  mindiff_invM    = avg_invM;
	  mindiff_pt      = avg_pt;
	  mindiff_ptdiff  = diff_pt;
	  mindiff_eta     = avg_eta;
	  mindiff_etadiff = diff_eta;
	  mindiff_phi     = avg_phi;
	  mindiff_phidiff = diff_phi;
	  mindiff_sumpt   = avg_sumPt;
	  mindiff_dR      = avg_dR;
	}
      }
    } // end double loop over dijet pairs
    h_NJetJJ_pt              [ireg] ->Fill( mindiff_pt,      weight );
    h_NJetJJ_eta             [ireg] ->Fill( mindiff_eta,     weight );
    h_NJetJJ_phi             [ireg] ->Fill( mindiff_phi,     weight );
    h_NJetJJ_m               [ireg] ->Fill( mindiff_invM,    weight );
    h_NJetJJ_ptDiff          [ireg] ->Fill( mindiff_ptdiff,  weight );
    h_NJetJJ_etaDiff         [ireg] ->Fill( mindiff_etadiff, weight );
    h_NJetJJ_phiDiff         [ireg] ->Fill( mindiff_phidiff, weight );
    h_NJetJJ_mDiff           [ireg] ->Fill( mindiff,         weight );
    h_NJetJJ_sumPt           [ireg] ->Fill( mindiff_sumpt,   weight );
    h_NJetJJ_dR              [ireg] ->Fill( mindiff_dR,      weight );
    // if ( mindiff < mindiff_invM * 0.50 ) {
    // }
    

    
    // -------------- //
    // --- TRACKS --- //
    // -------------- //
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

      // set vector of DV types
      std::vector<int> DV;
      getDVTypes( i, DV, base_dv );
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

	// total DV count
	h_evt_count_DV [ireg][idv] ->Fill( int(0), weight );

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
      // --> test cuts
      if ( m_nType1DVs ) {
      	std::vector<int> DV_testCut;
      	getDVTypes( i, DV_testCut, base_dv, false, false, false );
      	std::vector<int> dvTestCut ( DV_testCut.size() / m_nType1DVs, 0 );
      	for ( size_t idvc = 0; idvc != DV_testCut.size(); ++idvc ) {
      	  dvTestCut[idvc / m_nType1DVs] += DV_testCut[idvc];
      	  h_evt_testCutflow_DV [ireg][idvc / m_nType1DVs]
      	    ->Fill( idvc % m_nType1DVs, ( dvTestCut[idvc/m_nType1DVs] / ( idvc % m_nType1DVs + 1 ) ) * weight );
      	}
      }
      // --> "good" cuts
      std::vector<int> DV_cut;
      getDVTypes( i, DV_cut, base_dv, false, false, false, true );
      int n_goodCuts = DV_cut.size() / h_evt_cutflow_DV [ireg].size();
      std::vector<int> dvCut ( h_evt_cutflow_DV [ireg].size(), 0 );
      for ( size_t idvc = 0; idvc != DV_cut.size(); ++idvc ) {
      	dvCut[idvc / n_goodCuts] += DV_cut[idvc];
      	h_evt_cutflow_DV [ireg][idvc / n_goodCuts]
      	  ->Fill( idvc % n_goodCuts, ( dvCut[idvc/n_goodCuts] / ( idvc % n_goodCuts + 1 ) ) * weight );
      }

    } // end loop over vertices

    // fill DV count histograms
    if ( doHists ) {
      for ( size_t idv = 0; idv != n_DV.size(); ++idv ) {
	h_DV_n [ireg][idv] ->Fill( n_DV[idv], weight );
	if ( m_numVtxTrks ) {
	  for ( const auto& ntrkDV : n_ntrkDV[idv] )
	    h_ntrkDV_n [ireg][idv][ntrkDV.first-2] ->Fill( ntrkDV.second, weight );
	}
	// NDV cutflow
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
    }



    // --- ABCD PLANE TESTS --- //
    // -- tentative ABCD variables
    if ( m_histoInfoSwitch->m_abcd ) {
      for ( size_t idv = 0; idv != n_DV.size(); ++idv ) {
	h_abcd_nDV_NJetHt          [ireg][idv] ->Fill( m_njetHt,                    n_DV[idv], weight );
	h_abcd_nDV_NJetHt_vrsh     [ireg][idv] ->Fill( m_njetHt * m_VRshift_njetHt, n_DV[idv], weight );
	h_abcd_raw_nDV_NJetHt      [ireg][idv] ->Fill( m_njetHt,                    n_DV[idv], 1.0    );
	h_abcd_raw_nDV_NJetHt_vrsh [ireg][idv] ->Fill( m_njetHt * m_VRshift_njetHt, n_DV[idv], 1.0    );
	// --> ADD OTHER ABCD PLOTS WITH EVENT LEVEL VARIABLES
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
    m_nWeightedEntries [ireg] += weight;
    
  } // end loop over regions

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: finalize ( const std::vector<EJsHelper::Region>& regions )
{
  
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

    // cutflow efficiency histograms
    float reg_count  = m_nWeightedEntries [ireg];
    
    // --> JETS
    //for ( size_t icj = 0; icj != h_evt_cutflow_jet [ireg].size(); ++icj ) {
      //float  jcount = h_evt_cutflow_jet     [ireg][icj] ->GetBinContent(1);
      //float ljcount = h_evt_cutflow_leadjet [ireg][icj] ->GetBinContent(1);
    for ( size_t icj = 0; icj != h_evt_testCutflow_jet [ireg].size(); ++icj ) {
      float  jcount = h_evt_testCutflow_jet     [ireg][icj] ->GetBinContent(1);
      float ljcount = h_evt_testCutflow_leadjet [ireg][icj] ->GetBinContent(1);
      // --> test jet cuts
      if ( m_nType1Js ) {
	for ( int ibin = 0; ibin != h_evt_testCutflowEfficiency_jet [ireg][icj] ->GetNbinsX(); ++ibin ) {
	  float ibin_jcut  = h_evt_testCutflow_jet     [ireg][icj] ->GetBinContent(ibin+1);
	  float ibin_ljcut = h_evt_testCutflow_leadjet [ireg][icj] ->GetBinContent(ibin+1);
	  h_evt_testCutflowEfficiency_jet        [ireg][icj] ->Fill( ibin, ibin_jcut  /  jcount );
	  h_evt_testCutflowEfficiency_leadjet    [ireg][icj] ->Fill( ibin, ibin_ljcut / ljcount );
	}
      }
      // // --> emerging jet cuts
      // for ( int ibin = 0; ibin != h_evt_cutflowEfficiency_jet [ireg][icj] ->GetNbinsX(); ++ibin ) {
      // 	float ibin_jcut  = h_evt_cutflow_jet     [ireg][icj] ->GetBinContent(ibin+1);
      // 	float ibin_ljcut = h_evt_cutflow_leadjet [ireg][icj] ->GetBinContent(ibin+1);
      // 	h_evt_cutflowEfficiency_jet     [ireg][icj] ->Fill( ibin, ibin_jcut  /  jcount );
      // 	h_evt_cutflowEfficiency_leadjet [ireg][icj] ->Fill( ibin, ibin_ljcut / ljcount );
      // }
    }
    // --> N-Jet cuts
    for ( size_t icnj = 0; icnj != h_evt_cutflow_NJet [ireg].size(); ++icnj ) {
      for ( int ibin = 0; ibin != h_evt_cutflowEfficiency_NJet [ireg][icnj] ->GetNbinsX(); ++ibin ) {
	float ibin_cut     = h_evt_cutflow_NJet     [ireg][icnj] ->GetBinContent(ibin+1);
	float ileadbin_cut = h_evt_cutflow_NLeadJet [ireg][icnj] ->GetBinContent(ibin+1);
	h_evt_cutflowEfficiency_NJet          [ireg][icnj] ->Fill( ibin, ibin_cut     / reg_count   );
	h_evt_cutflowEfficiency_NLeadJet      [ireg][icnj] ->Fill( ibin, ileadbin_cut / reg_count   );
	h_evt_cutflowTotalEfficiency_NJet     [ireg][icnj] ->Fill( ibin, ibin_cut     / m_sumw_init );
	h_evt_cutflowTotalEfficiency_NLeadJet [ireg][icnj] ->Fill( ibin, ileadbin_cut / m_sumw_init );
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
    	h_evt_cutflowEfficiency_NDV      [ireg][icndv] ->Fill( ibin, ibin_cut / reg_count   );
    	h_evt_cutflowTotalEfficiency_NDV [ireg][icndv] ->Fill( ibin, ibin_cut / m_sumw_init );
      }
      // --> n-trk N-DV cuts
      if ( m_numVtxTrks ) {
      	for ( size_t itrk = 0; itrk != h_evt_cutflow_ntrkNDV [ireg][icndv].size(); ++itrk ) {
      	  for ( int itrkbin = 0; itrkbin != h_evt_cutflowEfficiency_ntrkNDV [ireg][icndv][itrk] ->GetNbinsX(); ++itrkbin ) {
      	    float itrkbin_cut = h_evt_cutflow_ntrkNDV [ireg][icndv][itrk] ->GetBinContent(itrkbin+1);
      	    h_evt_cutflowEfficiency_ntrkNDV      [ireg][icndv][itrk] ->Fill( itrkbin, itrkbin_cut / reg_count   );
      	    h_evt_cutflowTotalEfficiency_ntrkNDV [ireg][icndv][itrk] ->Fill( itrkbin, itrkbin_cut / m_sumw_init );
      	  }
      	}
      }
    }

    // overall count / efficiency histograms
    for ( size_t ihdv = 0; ihdv != h_evt_count_DV [ireg].size(); ++ihdv ) {
      h_evt_cutEfficiency_DV      [ireg][ihdv] ->Divide( h_evt_count_DV [ireg][ihdv], h_evt_count_DV [ireg][0]                            );
      h_evt_matchcutEfficiency_DV [ireg][ihdv] ->Divide( h_evt_count_DV [ireg][ihdv], h_evt_count_DV [ireg][ihdv/m_nTypeBDVs*m_nTypeBDVs] );
    }
    
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



void EJsHistogramManager :: getJetTypes ( int jet_index, std::vector<int>& jet, const EJsHelper::BaseDV& base_dv,
					  bool doCombos, bool doEJ, bool doEJCuts )
{

  if ( doEJCuts ) doCombos = false;

  // --- event-level variables to consider for signal-region cuts (i.e. in ABCD plane) --- //
  // plot on x-axis against nDV, nDVTrk, other DV event-level variables (like pt, ht?) in ABCD plane
  // implement test cuts in event-level cutflow
  // --> LEAD JETS
  // avg dijet    (jj_avgP4) dR, pt, sum-pt
  // max dijet    (jj_maxP4) dR, pt, sum-pt
  // max dijet n-sv        (jj_maxP4_nbareSV, jj_maxP4_n*GoodSV   ) [n SVs       per max-p4 dijet system]
  // max dijet n-sv-trk    (jj_maxP4_nSVtrk,  jj_maxP4_n*goodSVtrk) [n SV tracks per max-p4 dijet system]
  // max-pt dijet (jj_maxPt) dR, pt, sum-pt, m
  // max-pt dijet n-sv     (jj_maxPt_nbareSV, jj_maxPt_n*GoodSV   ) [n SVs       per max-pt dijet system]
  // max-pt dijet n-sv-trk (jj_maxPt_nSVtrk,  jj_maxPt_n*goodSVtrk) [n SV tracks per max-pt dijet system]
  // min    dijet (jj_minP4) m, pt, sum-pt
  // min dijet n-sv        (jj_minP4_nbareSV, jj_minP4_n*GoodSV   ) [n SVs       per min-p4 dijet system]
  // min dijet n-sv-trk    (jj_minP4_nSVtrk,  jj_minP4_n*goodSVtrk) [n SV tracks per min-p4 dijet system]
  // min-pt dijet (jj_minPt)        sum-pt
  // min-pt dijet n-sv     (jj_minPt_nbareSV, jj_minPt_n*GoodSV   ) [n SVs       per min-pt dijet system]
  // min-pt dijet n-sv-trk (jj_minPt_nSVtrk,  jj_minPt_n*goodSVtrk) [n SV tracks per min-pt dijet system]
  // N-jet (Nj) pt, sum-pt, eta
  // N-jet n-sv (Nj_nbareSV, Nj_n*GoodSV), n-sv-trk (Nj_nSVtrk, Nj_n*goodSVtrk) [n SVs, SV tracks per N-jet system]
  // min-invM dijet (NJetJJ) dR, invM, invM-diff --> look at invM after cutting on dR, invM-diff
  // --> LEAD "EMERGING" JETS
  // n EJs
  // avg    dijet dR, pt
  // max-pt dijet dR, pt
  // min    dijet dR, pt
  // N-jet sum-pt

  // --- jet-level variables to consider for emerging-jet cuts (to add to "tight" jet cuts) --- //
  // (min/max) dR b/w jets + matched tracks, SVs
  // n-sv [n SVs / n-SV kinematics per jet] --> n, n(j)trk, pt, sum-(sqrt)pt, sum-(sqrt)H, sum-(sqrt)Ht
  // --> if cutting on n SVs seems too tight, try cutting on n-sv kinematic variables instead
  // n-svtrk [n SV tracks per jet]
  // n (basic tracks) w/ dR and min-d0 above some threshold


  // IMPLEMENT SV, SV-TRK JET TEST CUTS (INDIVIDUALLY + ON TOP OF TIGHT CUTS; CHECK CUTFLOWS TO COMBINE) -->
  // --> IMPLEMENT TENTATIVE (LOOSE, MID, TIGHT) EMERGING JET CUTS -->
  // --> ADD ABCD PLOTS + CUTFLOWS FOR NJET/EJ EVENT-LEVEL VARIABLES + TEST-CUTS (CHECK EJ PLOTS)
  // --> --> TEST FOR DIFFERENT N-JET, SIGNAL-REGION REQUIREMENTS (I.E. IF N-EJ >= 2)
  
  
  // set vector of jet types (before truth matching)
  int allJet           = 1;
  int leadJet          = 0;
  // --> tight cuts
  int tightPtJet       = 0;
  int tightEtaJet      = 0;
  int tightMassJet     = 0;
  // --> n-sv ntrk cuts
  int nJSV_types = 4; // base, loose-good, mid-good, tight-good
  std::vector<int> svNtrkJet  ( nJSV_types * m_nJSVtrk.size(), 0 );
  // --> n-sv njtrk cuts
  std::vector<int> svNjtrkJet ( nJSV_types * m_nJSVtrk.size(), 0 );
  // --> n-sv-trk cuts
  std::vector<int> svTrkJet   ( nJSV_types * m_nJSVtrk.size(), 0 );
  // --> n-sv cuts
  std::vector<int> svJet      ( nJSV_types * m_nJSV   .size(), 0 ); 
  // --> combo cuts --> ADD N-SV (TRK) COMBOS
  int tightJet         = 0;

  // test if jet passes cuts
  // --> tight cuts
  if ( jet_index < m_nJets )
    leadJet       = 1;
  if ( m_jet_pt ->at(jet_index) > 200 )
    tightPtJet    = 1;
  if ( fabs( m_jet_eta ->at(jet_index) ) < 2.0 )
    tightEtaJet   = 1;
  if ( m_jet_M  ->at(jet_index) > 25 )
    tightMassJet  = 1;
  
  // --> n-sv ntrk cuts
  std::vector<int> n_svNtrk  ( nJSV_types, 0 );
  // --> n-sv njtrk cuts
  std::vector<int> n_svNjtrk ( nJSV_types, 0 );
  // --> n-sv-trk cuts
  std::vector<int> n_svTrk   ( nJSV_types, 0 );
  // --> n-sv cuts
  std::vector<int> n_sv      ( nJSV_types, 0 );
  // loop over matched secondary vertices
  for ( int jsv = 0; jsv != m_jet_secVtx_n ->at(jet_index); ++jsv ) {
    int jetSvIx   = m_jet_secVtx_index ->at(jet_index)[jsv];

    int jetSvNtrk = 0;
    if      ( base_dv.type == EJsHelper::BARE     )
      jetSvNtrk = m_secVtx_ntrk       ->at(jetSvIx);
    else if ( base_dv.type == EJsHelper::CLEAN    )
      jetSvNtrk = m_secVtx_ntrk_clean ->at(jetSvIx);
    else if ( base_dv.type == EJsHelper::FILTERED )
      jetSvNtrk = m_secVtx_ntrk_filt  ->at(jetSvIx);
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
    
    std::vector<int> jetsv;
    getDVTypes( jetSvIx, jetsv, base_dv, true );
    // base sv
    if ( jetSvNtrk > 1 ) {
      n_svNtrk [0] += jetSvNtrk;
      n_svNjtrk[0] += jetSvNjtrk;
      ++n_sv   [0];
    }
    // loose-good sv
    if ( jetsv[jetsv.size()-3] ) {
      n_svNtrk [1] += jetSvNtrk;
      n_svNjtrk[1] += jetSvNjtrk;
      ++n_sv   [1];
    }
    // mid-good sv
    if ( jetsv[jetsv.size()-2] ) {
      n_svNtrk [2] += jetSvNtrk;
      n_svNjtrk[2] += jetSvNjtrk;
      ++n_sv   [2];
    }
    // tight-good sv
    if ( jetsv[jetsv.size()-1] ) {
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

  
  // --> combo cuts
  if ( tightPtJet && tightEtaJet && tightMassJet )
    tightJet      = 1;
  
  // fill jet pass/fail cut vector
  jet   .push_back( allJet   );
  jet   .push_back( leadJet  );
  // --> tight cuts
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_tightJets || doEJCuts ) {
    jet   .push_back( tightPtJet               );
    jet   .push_back( tightPtJet    && leadJet );
    jet   .push_back( tightEtaJet              );
    jet   .push_back( tightEtaJet   && leadJet );
    jet   .push_back( tightMassJet             );
    jet   .push_back( tightMassJet  && leadJet );
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
  if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_nsvJets ) { // || doEJCuts ?? --> wait for EJ cut decisions...
    for ( const auto& svj : svJet ) {
      jet .push_back( svj            );
      jet .push_back( svj && leadJet );
    }
  }
  
  
  
  // --> combo cuts
  if ( m_histoInfoSwitch->m_comboJets && doCombos && !doEJCuts ) {
    if ( m_histoInfoSwitch->m_typeJets || m_histoInfoSwitch->m_tightJets ) {
      jet .push_back( tightJet                );
      jet .push_back( tightJet     && leadJet );
    }
  }

  // // --> "emerging" jets (update)
  // bool emergingJet     =  allJet && tightJet && ngoodsv2Jet; // --> 1 good SV ??
  // bool leadEmergingJet = leadJet && emergingJet;
  // if ( doEJ ) {
  //   jet .push_back(     emergingJet );
  //   jet .push_back( leadEmergingJet );
  // }

  // truth matching (to dark jets)
  bool darkJet    = false;
  bool nomatchJet = false;
  if ( m_mc ) {
    // require dark + truth jet match
    if ( m_jet_isDark ->at(jet_index) && m_jet_isTruth ->at(jet_index) ) {
      int truthIx = m_jet_truthIndex ->at(jet_index);
      // require matched dark + truth jet also matched to one another
      if ( m_jet_darkID ->at(jet_index) == m_truthJet_darkID ->at(truthIx) )
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
    getDVTypes ( trkSVix, trkSV, base_dv, true, false, true, false );
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
					 bool jetDV, bool doCombos, bool doGood, bool doGoodCuts )
{
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
  // --> vertices near (leading) jets
  bool byJetDV  = false;
  bool byNJetDV = false;
  if ( m_secVtx_jetMatched ->at(dv_index) ) byJetDV = true;
  if ( m_secVtx_jetMatched ->at(dv_index) && m_secVtx_jetMatch_index ->at(dv_index) < m_nJets ) byNJetDV = true;
  // --> fiducial vertices --> cut on r, z, chi2
  bool fiducDV = false;
  if ( m_secVtx_r    ->at(dv_index) < 300 && fabs( m_secVtx_z ->at(dv_index) ) < 300 &&
       m_secVtx_chi2 ->at(dv_index) < 5 ) fiducDV = true;
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

  // fill (jet) DV pass/fail cut vector
  if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_baseVerts     ) ) ||
       (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_baseJetVerts  ) ) ||
       (  doGoodCuts ) )
    dv .push_back( baseDV );
  if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_byJetVerts    ) ) ||
       (  doGoodCuts ) ) {
    dv .push_back( baseDV && byJetDV  );
    dv .push_back( baseDV && byNJetDV );
  }
  if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_fiducVerts      ) ) ||
       (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_fiducJetVerts   ) ) ||
       (  doGoodCuts ) )
    dv .push_back( baseDV && fiducDV );
  if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_ksmVerts        ) ) ||
       (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_ksmJetVerts     ) ) ||
       (  doGoodCuts ) )
    dv .push_back( baseDV && ksmDV   );
  if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_ptVerts         ) ) ||
       (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_ptJetVerts      ) ) ||
       (  doGoodCuts ) )
    dv .push_back( baseDV && ptDV    );
  if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_d0Verts         ) ) ||
       (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_d0JetVerts      ) ) ||
       (  doGoodCuts ) )
    dv .push_back( baseDV && mind0DV );
  if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_z0Verts         ) ) ||
       (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_z0JetVerts      ) ) ||
       (  doGoodCuts ) )
    dv .push_back( baseDV && minz0DV );
  if ( ( !jetDV && ( m_histoInfoSwitch->m_vertices    || m_histoInfoSwitch->m_d0z0ErrVerts    ) ) ||
       (  jetDV && ( m_histoInfoSwitch->m_jetVertices || m_histoInfoSwitch->m_d0z0ErrJetVerts ) ) ||
       (  doGoodCuts ) ) {
    dv .push_back( baseDV && minsqerrd0DV );
    dv .push_back( baseDV && minsqerrz0DV );
  }
  
  // --> combination cuts

  // --> "good" DVs
  bool looseGoodDV = baseDV && fiducDV && ksmDV;
  bool   midGoodDV = baseDV && fiducDV && ksmDV && ptDV;
  bool tightGoodDV = baseDV && fiducDV && ksmDV && ptDV && mind0DV && minz0DV && minsqerrd0DV && minsqerrz0DV;
  if ( doGood ) {
    if      ( !jetDV ) {
      dv .push_back( looseGoodDV && byNJetDV );
      dv .push_back(   midGoodDV && byNJetDV );
      dv .push_back( tightGoodDV && byNJetDV );
    }
    else if (  jetDV ) {
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

