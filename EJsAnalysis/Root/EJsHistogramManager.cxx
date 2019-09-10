#include <map>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/EJsHistogramManager.h"


EJsHistogramManager :: EJsHistogramManager ( const std::string& name, const std::string& detailStr, const std::string& jetStr,
					     bool debug, bool mc, bool truth ) : HistogramManager ( name, detailStr )
{
  m_histoInfoSwitch = new EJsHelperClasses::HistogramInfoSwitch( detailStr );
  m_jetStr          = jetStr;
  m_debug           = debug;
  m_mc              = mc;
  m_truth           = truth;
  m_numLeadJets     = m_histoInfoSwitch->m_numLeadingJets;
  m_numLeadTJets    = m_histoInfoSwitch->m_numLeadingTJets;
  m_numLeadDJets    = m_histoInfoSwitch->m_numLeadingDJets;
  m_numVtxTrks      = m_histoInfoSwitch->m_numVtxTrks;
  m_numTVtxTrks     = m_histoInfoSwitch->m_numTVtxTrks;

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
  m_pv_ntrk         = 0;
  m_pv_location     = 0;

  
  m_passL1           = 0;
  m_passHLT          = 0;
  m_passedTriggers   = new std::vector<std::string>;
  m_disabledTriggers = new std::vector<std::string>;

  
  m_jet_n                = 0;
  m_jet_pt               = new std::vector<float>;
  m_jet_eta              = new std::vector<float>;
  m_jet_phi              = new std::vector<float>;
  m_jet_E                = new std::vector<float>;
  m_jet_M                = new std::vector<float>;
  m_jet_rapid            = new std::vector<float>;
  m_jet_ID               = new std::vector<int>;
  m_jet_index            = new std::vector<int>;

  m_jet_hecFrac          = new std::vector<float>;
  m_jet_emFrac           = new std::vector<float>;
  m_jet_centroidR        = new std::vector<float>;
  m_jet_width            = new std::vector<float>;
  m_jet_numConstit       = new std::vector<int>;

  m_jet_numTrkPt10       = new std::vector<int>;
  m_jet_sumPtTrkPt10     = new std::vector<float>;
  m_jet_trkWidthPt10     = new std::vector<float>;
  m_jet_numTrkPt5        = new std::vector<int>;
  m_jet_sumPtTrkPt5      = new std::vector<float>;
  m_jet_trkWidthPt5      = new std::vector<float>;
  m_jet_jvf              = new std::vector<float>;
  m_jet_jvt              = new std::vector<float>;

  m_jet_ghostTrkCount    = new std::vector<int>;
  m_jet_ghostTrkPt       = new std::vector<float>;
  m_jet_ghostTrk_ID      = new std::vector<std::vector<int>>;
  m_jet_ghostTrk_index   = new std::vector<std::vector<int>>;
  m_jet_ghostTrk_eta     = new std::vector<std::vector<float>>;
  m_jet_ghostTrk_phi     = new std::vector<std::vector<float>>;
  m_jet_ghostTruthCount  = new std::vector<int>;
  m_jet_ghostTruthPt     = new std::vector<float>;
  m_jet_ghostTruth_ID    = new std::vector<std::vector<int>>;
  m_jet_ghostTruth_index = new std::vector<std::vector<int>>;
  m_jet_ghostTruth_pdgId = new std::vector<std::vector<int>>;
  m_jet_ghostTruth_eta   = new std::vector<std::vector<float>>;
  m_jet_ghostTruth_phi   = new std::vector<std::vector<float>>;

  m_jet_trkCount         = new std::vector<int>;
  m_jet_trkPt            = new std::vector<float>;
  m_jet_trk_ID           = new std::vector<std::vector<int>>;
  m_jet_trk_index        = new std::vector<std::vector<int>>;
  m_jet_trk_dR           = new std::vector<std::vector<float>>;
  m_jet_tpCount          = new std::vector<int>;
  m_jet_tpPt             = new std::vector<float>;
  m_jet_tp_ID            = new std::vector<std::vector<int>>;
  m_jet_tp_index         = new std::vector<std::vector<int>>;
  m_jet_tp_pdgId         = new std::vector<std::vector<int>>;
  m_jet_tp_dR            = new std::vector<std::vector<float>>;
  
  m_jet_secVtxCount      = new std::vector<int>;
  m_jet_secVtxPt         = new std::vector<float>;
  m_jet_secVtx_ID        = new std::vector<std::vector<int>>;
  m_jet_secVtx_index     = new std::vector<std::vector<int>>;
  m_jet_secVtx_dR        = new std::vector<std::vector<float>>;
  m_jet_truthVtxCount    = new std::vector<int>;
  m_jet_truthVtxPt       = new std::vector<float>;
  m_jet_truthVtx_ID      = new std::vector<std::vector<int>>;
  m_jet_truthVtx_index   = new std::vector<std::vector<int>>;
  m_jet_truthVtx_llp     = new std::vector<std::vector<std::string>>;
  m_jet_truthVtx_dR      = new std::vector<std::vector<float>>;

  m_jet_isTruthMatched   = new std::vector<uint8_t>;
  m_jet_truthMatch_ID    = new std::vector<int>;
  m_jet_truthMatch_index = new std::vector<int>;
  m_jet_truthMatch_dR    = new std::vector<float>;
  m_jet_isDarkMatched    = new std::vector<uint8_t>;
  m_jet_darkMatch_ID     = new std::vector<int>;
  m_jet_darkMatch_index  = new std::vector<int>;
  m_jet_darkMatch_dR     = new std::vector<float>;


  m_truthJet_n     = 0;
  m_truthJet_pt    = new std::vector<float>;
  m_truthJet_eta   = new std::vector<float>;
  m_truthJet_phi   = new std::vector<float>;
  m_truthJet_E     = new std::vector<float>;
  m_truthJet_M     = new std::vector<float>;  
  m_truthJet_rapid = new std::vector<float>;
  m_truthJet_ID    = new std::vector<int>;
  m_truthJet_index = new std::vector<int>;

  m_truthJet_width          = new std::vector<float>;
  m_truthJet_girth          = new std::vector<float>;
  m_truthJet_numConstit     = new std::vector<int>;
  m_truthJet_constitPt      = new std::vector<float>;
  m_truthJet_constit_ID     = new std::vector<std::vector<int>>;
  m_truthJet_constit_index  = new std::vector<std::vector<int>>;
  m_truthJet_constit_pt     = new std::vector<std::vector<float>>;
  m_truthJet_constit_charge = new std::vector<std::vector<float>>;
  m_truthJet_constit_dR     = new std::vector<std::vector<float>>;
  m_truthJet_constit_pVtx_r = new std::vector<std::vector<float>>;

  m_truthJet_trkCount    = new std::vector<int>;
  m_truthJet_trkPt       = new std::vector<float>;
  m_truthJet_trk_ID      = new std::vector<std::vector<int>>;
  m_truthJet_trk_index   = new std::vector<std::vector<int>>;
  m_truthJet_trk_dR      = new std::vector<std::vector<float>>;
  m_truthJet_tpCount     = new std::vector<int>;
  m_truthJet_tpPt        = new std::vector<float>;
  m_truthJet_tp_ID       = new std::vector<std::vector<int>>;
  m_truthJet_tp_index    = new std::vector<std::vector<int>>;
  m_truthJet_tp_pt       = new std::vector<std::vector<float>>;
  m_truthJet_tp_charge   = new std::vector<std::vector<float>>;
  m_truthJet_tp_pdgId    = new std::vector<std::vector<int>>;
  m_truthJet_tp_dR       = new std::vector<std::vector<float>>;
  m_truthJet_tp_isStable = new std::vector<std::vector<uint8_t>>;
  m_truthJet_tp_isDark   = new std::vector<std::vector<uint8_t>>;

  m_truthJet_secVtxCount    = new std::vector<int>;
  m_truthJet_secVtxPt       = new std::vector<float>;
  m_truthJet_secVtx_ID      = new std::vector<std::vector<int>>;
  m_truthJet_secVtx_index   = new std::vector<std::vector<int>>;
  m_truthJet_secVtx_dR      = new std::vector<std::vector<float>>;
  m_truthJet_truthVtxCount  = new std::vector<int>;
  m_truthJet_truthVtxPt     = new std::vector<float>;
  m_truthJet_truthVtx_ID    = new std::vector<std::vector<int>>;
  m_truthJet_truthVtx_index = new std::vector<std::vector<int>>;
  m_truthJet_truthVtx_llp   = new std::vector<std::vector<std::string>>;
  m_truthJet_truthVtx_r     = new std::vector<std::vector<float>>;
  m_truthJet_truthVtx_mass  = new std::vector<std::vector<float>>;
  m_truthJet_truthVtx_dR    = new std::vector<std::vector<float>>;

  m_truthJet_isDarkMatched   = new std::vector<uint8_t>;
  m_truthJet_darkMatch_ID    = new std::vector<int>;
  m_truthJet_darkMatch_index = new std::vector<int>;
  m_truthJet_darkMatch_dR    = new std::vector<float>;
  m_truthJet_isRecoMatch     = new std::vector<uint8_t>;
  m_truthJet_recoMatch_ID    = new std::vector<int>;
  m_truthJet_recoMatch_index = new std::vector<int>;
  m_truthJet_recoMatch_dR    = new std::vector<float>;


  m_darkJet_n     = 0;
  m_darkJet_pt    = new std::vector<float>;
  m_darkJet_eta   = new std::vector<float>;
  m_darkJet_phi   = new std::vector<float>;
  m_darkJet_E     = new std::vector<float>;
  m_darkJet_M     = new std::vector<float>;  
  m_darkJet_rapid = new std::vector<float>;
  m_darkJet_ID    = new std::vector<int>;
  m_darkJet_index = new std::vector<int>;

  m_darkJet_width          = new std::vector<float>;
  m_darkJet_girth          = new std::vector<float>;
  m_darkJet_numConstit     = new std::vector<int>;
  m_darkJet_constitPt      = new std::vector<float>;
  m_darkJet_constit_ID     = new std::vector<std::vector<int>>;
  m_darkJet_constit_index  = new std::vector<std::vector<int>>;
  m_darkJet_constit_pt     = new std::vector<std::vector<float>>;
  m_darkJet_constit_charge = new std::vector<std::vector<float>>;
  m_darkJet_constit_dR     = new std::vector<std::vector<float>>;
  m_darkJet_constit_dVtx_r = new std::vector<std::vector<float>>;

  m_darkJet_trkCount    = new std::vector<int>;
  m_darkJet_trkPt       = new std::vector<float>;
  m_darkJet_trk_ID      = new std::vector<std::vector<int>>;
  m_darkJet_trk_index   = new std::vector<std::vector<int>>;
  m_darkJet_trk_dR      = new std::vector<std::vector<float>>;
  m_darkJet_tpCount     = new std::vector<int>;
  m_darkJet_tpPt        = new std::vector<float>;
  m_darkJet_tp_ID       = new std::vector<std::vector<int>>;
  m_darkJet_tp_index    = new std::vector<std::vector<int>>;
  m_darkJet_tp_pt       = new std::vector<std::vector<float>>;
  m_darkJet_tp_charge   = new std::vector<std::vector<float>>;
  m_darkJet_tp_pdgId    = new std::vector<std::vector<int>>;
  m_darkJet_tp_dR       = new std::vector<std::vector<float>>;
  m_darkJet_tp_isStable = new std::vector<std::vector<uint8_t>>;
  m_darkJet_tp_isDark   = new std::vector<std::vector<uint8_t>>;

  m_darkJet_secVtxCount    = new std::vector<int>;
  m_darkJet_secVtxPt       = new std::vector<float>;
  m_darkJet_secVtx_ID      = new std::vector<std::vector<int>>;
  m_darkJet_secVtx_index   = new std::vector<std::vector<int>>;
  m_darkJet_secVtx_dR      = new std::vector<std::vector<float>>;
  m_darkJet_truthVtxCount  = new std::vector<int>;
  m_darkJet_truthVtxPt     = new std::vector<float>;
  m_darkJet_truthVtx_ID    = new std::vector<std::vector<int>>;
  m_darkJet_truthVtx_index = new std::vector<std::vector<int>>;
  m_darkJet_truthVtx_llp   = new std::vector<std::vector<std::string>>;
  m_darkJet_truthVtx_r     = new std::vector<std::vector<float>>;
  m_darkJet_truthVtx_mass  = new std::vector<std::vector<float>>;
  m_darkJet_truthVtx_dR    = new std::vector<std::vector<float>>;

  m_darkJet_isTruthMatch     = new std::vector<uint8_t>;
  m_darkJet_truthMatch_ID    = new std::vector<int>;
  m_darkJet_truthMatch_index = new std::vector<int>;
  m_darkJet_truthMatch_dR    = new std::vector<float>;
  m_darkJet_isRecoMatch      = new std::vector<uint8_t>;
  m_darkJet_recoMatch_ID     = new std::vector<int>;
  m_darkJet_recoMatch_index  = new std::vector<int>;
  m_darkJet_recoMatch_dR     = new std::vector<float>;


  m_tp_n             = 0;
  m_tp_ID            = new std::vector<int>;
  m_tp_index         = new std::vector<int>;
  m_tp_pt            = new std::vector<float>;
  m_tp_eta           = new std::vector<float>;
  m_tp_phi           = new std::vector<float>;
  m_tp_E             = new std::vector<float>;
  m_tp_M             = new std::vector<float>;
  m_tp_charge        = new std::vector<float>;
  m_tp_pdgId         = new std::vector<int>;
  m_tp_status        = new std::vector<int>;
  m_tp_isStable      = new std::vector<uint8_t>;
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
  m_secVtx_ID            = new std::vector<int>;
  m_secVtx_index         = new std::vector<int>;
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
  m_secVtx_twoTrkMass    = new std::vector<std::vector<float>>;
  m_secVtx_ntrk          = new std::vector<uint32_t>;
  m_secVtx_ntrk_sel      = new std::vector<uint32_t>;
  m_secVtx_ntrk_assoc    = new std::vector<uint32_t>;


  m_truthVtx_n        = 0;
  m_truthVtx_ID       = new std::vector<int>;
  m_truthVtx_index    = new std::vector<int>;
  m_truthVtx_llp      = new std::vector<std::string>;
  m_truthVtx_x        = new std::vector<float>;
  m_truthVtx_y        = new std::vector<float>;
  m_truthVtx_z        = new std::vector<float>;
  m_truthVtx_r        = new std::vector<float>;
  m_truthVtx_pt       = new std::vector<float>;
  m_truthVtx_eta      = new std::vector<float>;
  m_truthVtx_phi      = new std::vector<float>;
  m_truthVtx_mass     = new std::vector<float>;
  m_truthVtx_nOutP    = new std::vector<int>;
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
  delete m_jet_ID;
  delete m_jet_index;

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
  delete m_jet_jvf;
  delete m_jet_jvt;

  delete m_jet_ghostTrkCount;
  delete m_jet_ghostTrkPt;
  delete m_jet_ghostTrk_ID;
  delete m_jet_ghostTrk_index;
  delete m_jet_ghostTrk_eta;
  delete m_jet_ghostTrk_phi;
  delete m_jet_ghostTruthCount;
  delete m_jet_ghostTruthPt;
  delete m_jet_ghostTruth_ID;
  delete m_jet_ghostTruth_index;
  delete m_jet_ghostTruth_pdgId;
  delete m_jet_ghostTruth_eta;
  delete m_jet_ghostTruth_phi;

  delete m_jet_trkCount;
  delete m_jet_trkPt;
  delete m_jet_trk_ID;
  delete m_jet_trk_index;
  delete m_jet_trk_dR;
  delete m_jet_tpCount;
  delete m_jet_tpPt;
  delete m_jet_tp_ID;
  delete m_jet_tp_index;
  delete m_jet_tp_pdgId;
  delete m_jet_tp_dR;
  
  delete m_jet_secVtxCount;
  delete m_jet_secVtxPt;
  delete m_jet_secVtx_ID;
  delete m_jet_secVtx_index;
  delete m_jet_secVtx_dR;
  delete m_jet_truthVtxCount;
  delete m_jet_truthVtxPt;
  delete m_jet_truthVtx_ID;
  delete m_jet_truthVtx_index;
  delete m_jet_truthVtx_llp;
  delete m_jet_truthVtx_dR;

  delete m_jet_isTruthMatched;
  delete m_jet_truthMatch_ID;
  delete m_jet_truthMatch_index;
  delete m_jet_truthMatch_dR;
  delete m_jet_isDarkMatched;
  delete m_jet_darkMatch_ID;
  delete m_jet_darkMatch_index;
  delete m_jet_darkMatch_dR;


  delete m_truthJet_pt;
  delete m_truthJet_eta;
  delete m_truthJet_phi;
  delete m_truthJet_E;
  delete m_truthJet_M;
  delete m_truthJet_rapid;
  delete m_truthJet_ID;
  delete m_truthJet_index;
  
  delete m_truthJet_width;
  delete m_truthJet_girth;
  delete m_truthJet_numConstit;
  delete m_truthJet_constitPt;
  delete m_truthJet_constit_ID;
  delete m_truthJet_constit_index;
  delete m_truthJet_constit_pt;
  delete m_truthJet_constit_charge;
  delete m_truthJet_constit_dR;
  delete m_truthJet_constit_pVtx_r;

  delete m_truthJet_trkCount;
  delete m_truthJet_trkPt;
  delete m_truthJet_trk_ID;
  delete m_truthJet_trk_index;
  delete m_truthJet_trk_dR;
  delete m_truthJet_tpCount;
  delete m_truthJet_tpPt;
  delete m_truthJet_tp_ID;
  delete m_truthJet_tp_index;
  delete m_truthJet_tp_pt;
  delete m_truthJet_tp_charge;
  delete m_truthJet_tp_pdgId;
  delete m_truthJet_tp_dR;
  delete m_truthJet_tp_isStable;
  delete m_truthJet_tp_isDark;

  delete m_truthJet_secVtxCount;
  delete m_truthJet_secVtxPt;
  delete m_truthJet_secVtx_ID;
  delete m_truthJet_secVtx_index;
  delete m_truthJet_secVtx_dR;
  delete m_truthJet_truthVtxCount;
  delete m_truthJet_truthVtxPt;
  delete m_truthJet_truthVtx_ID;
  delete m_truthJet_truthVtx_index;
  delete m_truthJet_truthVtx_llp;
  delete m_truthJet_truthVtx_r;
  delete m_truthJet_truthVtx_mass;
  delete m_truthJet_truthVtx_dR;

  delete m_truthJet_isDarkMatched;
  delete m_truthJet_darkMatch_ID;
  delete m_truthJet_darkMatch_index;
  delete m_truthJet_darkMatch_dR;
  delete m_truthJet_isRecoMatch;
  delete m_truthJet_recoMatch_ID;
  delete m_truthJet_recoMatch_index;
  delete m_truthJet_recoMatch_dR;


  delete m_darkJet_pt;
  delete m_darkJet_eta;
  delete m_darkJet_phi;
  delete m_darkJet_E;
  delete m_darkJet_M;
  delete m_darkJet_rapid;
  delete m_darkJet_ID;
  delete m_darkJet_index;
  
  delete m_darkJet_width;
  delete m_darkJet_girth;
  delete m_darkJet_numConstit;
  delete m_darkJet_constitPt;
  delete m_darkJet_constit_ID;
  delete m_darkJet_constit_index;
  delete m_darkJet_constit_pt;
  delete m_darkJet_constit_charge;
  delete m_darkJet_constit_dR;
  delete m_darkJet_constit_dVtx_r;

  delete m_darkJet_trkCount;
  delete m_darkJet_trkPt;
  delete m_darkJet_trk_ID;
  delete m_darkJet_trk_index;
  delete m_darkJet_trk_dR;
  delete m_darkJet_tpCount;
  delete m_darkJet_tpPt;
  delete m_darkJet_tp_ID;
  delete m_darkJet_tp_index;
  delete m_darkJet_tp_pt;
  delete m_darkJet_tp_charge;
  delete m_darkJet_tp_pdgId;
  delete m_darkJet_tp_dR;
  delete m_darkJet_tp_isStable;
  delete m_darkJet_tp_isDark;

  delete m_darkJet_secVtxCount;
  delete m_darkJet_secVtxPt;
  delete m_darkJet_secVtx_ID;
  delete m_darkJet_secVtx_index;
  delete m_darkJet_secVtx_dR;
  delete m_darkJet_truthVtxCount;
  delete m_darkJet_truthVtxPt;
  delete m_darkJet_truthVtx_ID;
  delete m_darkJet_truthVtx_index;
  delete m_darkJet_truthVtx_llp;
  delete m_darkJet_truthVtx_r;
  delete m_darkJet_truthVtx_mass;
  delete m_darkJet_truthVtx_dR;

  delete m_darkJet_isTruthMatch;
  delete m_darkJet_truthMatch_ID;
  delete m_darkJet_truthMatch_index;
  delete m_darkJet_truthMatch_dR;
  delete m_darkJet_isRecoMatch;
  delete m_darkJet_recoMatch_ID;
  delete m_darkJet_recoMatch_index;
  delete m_darkJet_recoMatch_dR;


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
  delete m_tp_isStable;
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
  delete m_secVtx_mass_nonAssoc;
  delete m_secVtx_chi2;
  delete m_secVtx_direction;
  delete m_secVtx_charge;
  delete m_secVtx_Ht;
  delete m_secVtx_minOpAng;
  delete m_secVtx_maxOpAng;
  delete m_secVtx_mind0;
  delete m_secVtx_maxd0;
  delete m_secVtx_twoTrkMass;
  delete m_secVtx_ntrk;
  delete m_secVtx_ntrk_sel;
  delete m_secVtx_ntrk_assoc;


  delete m_truthVtx_ID;
  delete m_truthVtx_index;
  delete m_truthVtx_llp;
  delete m_truthVtx_x;
  delete m_truthVtx_y;
  delete m_truthVtx_z;
  delete m_truthVtx_r;
  delete m_truthVtx_pt;
  delete m_truthVtx_eta;
  delete m_truthVtx_phi;
  delete m_truthVtx_mass;
  delete m_truthVtx_nOutP;
}



StatusCode EJsHistogramManager :: connectEvents ( TTree* tree )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectEvents()", "connecting event branches" );

  using namespace EJsHelper;
  
  connectBranch<int>      ( tree, "runNumber",       &m_runNumber       );
  connectBranch<Long64_t> ( tree, "eventNumber",     &m_eventNumber     );
  connectBranch<int>      ( tree, "lumiBlock",       &m_lumiBlock       );
  connectBranch<int>      ( tree, "bcid",            &m_bcid            );
  connectBranch<uint8_t>  ( tree, "isMC",            &m_isMC            );
  if ( m_mc ) {
    connectBranch<int>    ( tree, "mcEventNumber",   &m_mcEventNumber   );
    connectBranch<int>    ( tree, "mcChannelNumber", &m_mcChannelNumber );
    connectBranch<float>  ( tree, "mcEventWeight",   &m_mcEventWeight   );
  }
  
  if ( m_histoInfoSwitch->m_pileup && !m_truth ) {
    connectBranch<int>   ( tree, "NPV",                            &m_npv           );
    connectBranch<float> ( tree, "actualInteractionsPerCrossing",  &m_actualMu      );
    connectBranch<float> ( tree, "averageInteractionsPerCrossing", &m_averageMu     );
    connectBranch<float> ( tree, "weight_pileup",                  &m_weight_pileup );
  }
  
  if ( m_histoInfoSwitch->m_pv && !m_truth ) {
    connectBranch<float> ( tree, "PV_x",       &m_pv_x    );
    connectBranch<float> ( tree, "PV_y",       &m_pv_y    );
    connectBranch<float> ( tree, "PV_z",       &m_pv_z    );
    connectBranch<float> ( tree, "PV_r",       &m_pv_r    );
    connectBranch<float> ( tree, "PV_phi",     &m_pv_phi  );
    //connectBranch<int>   ( tree, "PV_nTracks", &m_pv_ntrk );
  }

  connectBranch<uint8_t> ( tree, "isSignal_" + m_jetStr, &m_signal );
  connectBranch<uint8_t> ( tree, "isValid_"  + m_jetStr, &m_valid  );
  connectBranch<uint8_t> ( tree, "isCtrl_"   + m_jetStr, &m_ctrl   );
  connectBranch<float>   ( tree, "NJetHt_"   + m_jetStr, &m_njetHt );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTriggers ( TTree* tree )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTriggers()", "connecting trigger branches" );

  using namespace EJsHelper;
  
  connectBranch<int>            ( tree, "passL1",           &m_passL1           );
  connectBranch<int>            ( tree, "passHLT",          &m_passHLT          );
  connectBranchVec<std::string> ( tree, "passedTriggers",   &m_passedTriggers   );
  connectBranchVec<std::string> ( tree, "disabledTriggers", &m_disabledTriggers );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectJets ( TTree* tree, const std::string& jetName )
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
  connectBranch<int>   ( name, tree, "ID",       &m_jet_ID    );
  connectBranch<int>   ( name, tree, "index",    &m_jet_index );

  if ( m_histoInfoSwitch->m_jet_energy ) {
    connectBranch<float> ( name, tree, "HECFrac",            &m_jet_hecFrac      );
    connectBranch<float> ( name, tree, "EMFrac",             &m_jet_emFrac       );
    connectBranch<float> ( name, tree, "CentroidR",          &m_jet_centroidR    );
    connectBranch<float> ( name, tree, "Width",              &m_jet_width        );
  }
  if ( m_histoInfoSwitch->m_jet_constit )
    connectBranch<int>   ( name, tree, "numConstituents",    &m_jet_numConstit   );

  if ( m_histoInfoSwitch->m_jet_trkMoms ) {
    connectBranch<int>   ( name, tree, "NumTrkPt1000PV",     &m_jet_numTrkPt10   );
    connectBranch<float> ( name, tree, "SumPtTrkPt1000PV",   &m_jet_sumPtTrkPt10 );
    connectBranch<float> ( name, tree, "TrackWidthPt1000PV", &m_jet_trkWidthPt10 );
    connectBranch<int>   ( name, tree, "NumTrkPt500PV",      &m_jet_numTrkPt5    );
    connectBranch<float> ( name, tree, "SumPtTrkPt500PV",    &m_jet_sumPtTrkPt5  );
    connectBranch<float> ( name, tree, "TrackWidthPt500PV",  &m_jet_trkWidthPt5  );
    connectBranch<float> ( name, tree, "JVFPV",              &m_jet_jvf          );
    connectBranch<float> ( name, tree, "Jvt",                &m_jet_jvt          );
  }
  
  if ( m_histoInfoSwitch->m_jet_ghost || m_histoInfoSwitch->m_jet_ghostTrk ) {
    connectBranch<int>                ( name, tree, "GhostTrackCount",  &m_jet_ghostTrkCount    );
    connectBranch<float>              ( name, tree, "GhostTrackPt",     &m_jet_ghostTrkPt       );
    connectBranch<std::vector<int>>   ( name, tree, "GhostTrack_ID",    &m_jet_ghostTrk_ID      );
    connectBranch<std::vector<int>>   ( name, tree, "GhostTrack_index", &m_jet_ghostTrk_index   );
    connectBranch<std::vector<float>> ( name, tree, "GhostTrack_eta",   &m_jet_ghostTrk_eta     );
    connectBranch<std::vector<float>> ( name, tree, "GhostTrack_phi",   &m_jet_ghostTrk_phi     );
  }
  if ( ( m_histoInfoSwitch->m_jet_ghost || m_histoInfoSwitch->m_jet_ghostTruth ) && m_mc ) {
    connectBranch<int>                ( name, tree, "GhostTruthCount",  &m_jet_ghostTruthCount  );
    connectBranch<float>              ( name, tree, "GhostTruthPt",     &m_jet_ghostTruthPt     );
    connectBranch<std::vector<int>>   ( name, tree, "GhostTruth_ID",    &m_jet_ghostTruth_ID    );
    connectBranch<std::vector<int>>   ( name, tree, "GhostTruth_index", &m_jet_ghostTruth_index );
    connectBranch<std::vector<int>>   ( name, tree, "GhostTruth_pdgId", &m_jet_ghostTruth_pdgId );
    connectBranch<std::vector<float>> ( name, tree, "GhostTruth_eta",   &m_jet_ghostTruth_eta   );
    connectBranch<std::vector<float>> ( name, tree, "GhostTruth_phi",   &m_jet_ghostTruth_phi   );
  }

  if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_trk ) {
    connectBranch<int>                ( name, tree, "trkCount",  &m_jet_trkCount  );
    connectBranch<float>              ( name, tree, "trkPt",     &m_jet_trkPt     );
    connectBranch<std::vector<int>>   ( name, tree, "trk_ID",    &m_jet_trk_ID    );
    connectBranch<std::vector<int>>   ( name, tree, "trk_index", &m_jet_trk_index );
    connectBranch<std::vector<float>> ( name, tree, "trk_dR",    &m_jet_trk_dR    );
  }
  if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_tp ) && m_mc ) {
    connectBranch<int>                ( name, tree, "tpCount",   &m_jet_tpCount   );
    connectBranch<float>              ( name, tree, "tpPt",      &m_jet_tpPt      );
    connectBranch<std::vector<int>>   ( name, tree, "tp_ID",     &m_jet_tp_ID     );
    connectBranch<std::vector<int>>   ( name, tree, "tp_index",  &m_jet_tp_index  );
    connectBranch<std::vector<int>>   ( name, tree, "tp_pdgId",  &m_jet_tp_pdgId  );
    connectBranch<std::vector<float>> ( name, tree, "tp_dR",     &m_jet_tp_dR     );
  }
  
  if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_vtx ) {
    connectBranch<int>                      ( name, tree, "secVtxCount",       &m_jet_secVtxCount    );
    connectBranch<float>                    ( name, tree, "secVtxPt",          &m_jet_secVtxPt       );
    connectBranch<std::vector<int>>         ( name, tree, "secVtx_ID",         &m_jet_secVtx_ID      );
    connectBranch<std::vector<int>>         ( name, tree, "secVtx_index",      &m_jet_secVtx_index   );
    connectBranch<std::vector<float>>       ( name, tree, "secVtx_dR",         &m_jet_secVtx_dR      );
  }
  if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_tvtx ) && m_mc ) {
    connectBranch<int>                      ( name, tree, "truthVtxCount",     &m_jet_truthVtxCount  );
    connectBranch<float>                    ( name, tree, "truthVtxPt",        &m_jet_truthVtxPt     );
    connectBranch<std::vector<int>>         ( name, tree, "truthVtx_ID",       &m_jet_truthVtx_ID    );
    connectBranch<std::vector<int>>         ( name, tree, "truthVtx_index",    &m_jet_truthVtx_index );
    connectBranch<std::vector<std::string>> ( name, tree, "truthVtx_llpDecay", &m_jet_truthVtx_llp   );
    connectBranch<std::vector<float>>       ( name, tree, "truthVtx_dR",       &m_jet_truthVtx_dR    );
  }

  if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_truth ) && m_mc ) {
    connectBranch<uint8_t> ( name, tree, "isTruthMatched",   &m_jet_isTruthMatched   );
    connectBranch<int>     ( name, tree, "truthMatch_ID",    &m_jet_truthMatch_ID    );
    connectBranch<int>     ( name, tree, "truthMatch_index", &m_jet_truthMatch_index );
    connectBranch<float>   ( name, tree, "truthMatch_dR",    &m_jet_truthMatch_dR    );
    connectBranch<uint8_t> ( name, tree, "isDarkMatched",    &m_jet_isDarkMatched    );
    connectBranch<int>     ( name, tree, "darkMatch_ID",     &m_jet_darkMatch_ID     );
    connectBranch<int>     ( name, tree, "darkMatch_index",  &m_jet_darkMatch_index  );
    connectBranch<float>   ( name, tree, "darkMatch_dR",     &m_jet_darkMatch_dR     );
  }

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
  connectBranch<int> ( tree, "n"+name, &m_truthJet_n );

  using namespace HelperFunctions;
  connectBranch<float> ( name, tree, "pt",       &m_truthJet_pt    );
  connectBranch<float> ( name, tree, "eta",      &m_truthJet_eta   );
  connectBranch<float> ( name, tree, "phi",      &m_truthJet_phi   );
  connectBranch<float> ( name, tree, "E",        &m_truthJet_E     );
  connectBranch<float> ( name, tree, "M",        &m_truthJet_M     );
  connectBranch<float> ( name, tree, "rapidity", &m_truthJet_rapid );
  connectBranch<int>   ( name, tree, "ID",       &m_truthJet_ID    );
  connectBranch<int>   ( name, tree, "index",    &m_truthJet_index );

  if ( m_histoInfoSwitch->m_tjet_energy )
    connectBranch<float> ( name, tree, "Width", &m_truthJet_width );
  if ( m_histoInfoSwitch->m_tjet_constit ) {
    connectBranch<float>              ( name, tree, "girth",                 &m_truthJet_girth          );
    connectBranch<int>                ( name, tree, "numConstituents",       &m_truthJet_numConstit     );
    connectBranch<float>              ( name, tree, "constituentPt",         &m_truthJet_constitPt      );
    connectBranch<std::vector<int>>   ( name, tree, "constituent_ID",        &m_truthJet_constit_ID     );
    connectBranch<std::vector<int>>   ( name, tree, "constituent_index",     &m_truthJet_constit_index  );
    connectBranch<std::vector<float>> ( name, tree, "constituent_pt",        &m_truthJet_constit_pt     );
    connectBranch<std::vector<float>> ( name, tree, "constituent_charge",    &m_truthJet_constit_charge );
    connectBranch<std::vector<float>> ( name, tree, "constituent_dR",        &m_truthJet_constit_dR     );
    connectBranch<std::vector<float>> ( name, tree, "constituent_prodVtx_r", &m_truthJet_constit_pVtx_r );
  }

  if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_trk ) && !m_truth ) {
    connectBranch<int>                  ( name, tree, "trkCount",    &m_truthJet_trkCount    );
    connectBranch<float>                ( name, tree, "trkPt",       &m_truthJet_trkPt       );
    connectBranch<std::vector<int>>     ( name, tree, "trk_ID",      &m_truthJet_trk_ID      );
    connectBranch<std::vector<int>>     ( name, tree, "trk_index",   &m_truthJet_trk_index   );
    connectBranch<std::vector<float>>   ( name, tree, "trk_dR",      &m_truthJet_trk_dR      );
  }
  if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_tp ) {
    connectBranch<int>                  ( name, tree, "tpCount",     &m_truthJet_tpCount     );
    connectBranch<float>                ( name, tree, "tpPt",        &m_truthJet_tpPt        );
    connectBranch<std::vector<int>>     ( name, tree, "tp_ID",       &m_truthJet_tp_ID       );
    connectBranch<std::vector<int>>     ( name, tree, "tp_index",    &m_truthJet_tp_index    );
    connectBranch<std::vector<float>>   ( name, tree, "tp_pt",       &m_truthJet_tp_pt       );
    connectBranch<std::vector<float>>   ( name, tree, "tp_charge",   &m_truthJet_tp_charge   );
    connectBranch<std::vector<int>>     ( name, tree, "tp_pdgId",    &m_truthJet_tp_pdgId    );
    connectBranch<std::vector<float>>   ( name, tree, "tp_dR",       &m_truthJet_tp_dR       );
    connectBranch<std::vector<uint8_t>> ( name, tree, "tp_isStable", &m_truthJet_tp_isStable );
    connectBranch<std::vector<uint8_t>> ( name, tree, "tp_isDark",   &m_truthJet_tp_isDark   );
  }

  if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_vtx ) && !m_truth ) {
    connectBranch<int>                      ( name, tree, "secVtxCount",       &m_truthJet_secVtxCount    );
    connectBranch<float>                    ( name, tree, "secVtxPt",          &m_truthJet_secVtxPt       );
    connectBranch<std::vector<int>>         ( name, tree, "secVtx_ID",         &m_truthJet_secVtx_ID      );
    connectBranch<std::vector<int>>         ( name, tree, "secVtx_index",      &m_truthJet_secVtx_index   );
    connectBranch<std::vector<float>>       ( name, tree, "secVtx_dR",         &m_truthJet_secVtx_dR      );
  }
  if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_tvtx ) {
    connectBranch<int>                      ( name, tree, "truthVtxCount",     &m_truthJet_truthVtxCount  );
    connectBranch<float>                    ( name, tree, "truthVtxPt",        &m_truthJet_truthVtxPt     );
    connectBranch<std::vector<int>>         ( name, tree, "truthVtx_ID",       &m_truthJet_truthVtx_ID    );
    connectBranch<std::vector<int>>         ( name, tree, "truthVtx_index",    &m_truthJet_truthVtx_index );
    connectBranch<std::vector<std::string>> ( name, tree, "truthVtx_llpDecay", &m_truthJet_truthVtx_llp   );
    connectBranch<std::vector<float>>       ( name, tree, "truthVtx_r",        &m_truthJet_truthVtx_r     );
    connectBranch<std::vector<float>>       ( name, tree, "truthVtx_mass",     &m_truthJet_truthVtx_mass  );
    connectBranch<std::vector<float>>       ( name, tree, "truthVtx_dR",       &m_truthJet_truthVtx_dR    );
  }

  if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_truth ) {
    connectBranch<uint8_t>   ( name, tree, "isDarkMatched",                &m_truthJet_isDarkMatched   );
    connectBranch<int>       ( name, tree, "darkMatch_ID",                 &m_truthJet_darkMatch_ID    );
    connectBranch<int>       ( name, tree, "darkMatch_index",              &m_truthJet_darkMatch_index );
    connectBranch<float>     ( name, tree, "darkMatch_dR",                 &m_truthJet_darkMatch_dR    );
    if ( !m_truth ) {
      connectBranch<uint8_t> ( name, tree, "isMatchedTo" + m_jetStr,       &m_truthJet_isRecoMatch     );
      connectBranch<int>     ( name, tree, "matched" + m_jetStr + "ID",    &m_truthJet_recoMatch_ID    );
      connectBranch<int>     ( name, tree, "matched" + m_jetStr + "Index", &m_truthJet_recoMatch_index );
      connectBranch<float>   ( name, tree, "matched" + m_jetStr + "DR",    &m_truthJet_recoMatch_dR    );
    }
  }

  return StatusCode::SUCCESS;
}


StatusCode EJsHistogramManager :: connectTruthDarkJets ( TTree* tree, const std::string& darkJetName )
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
  connectBranch<int>   ( name, tree, "ID",       &m_darkJet_ID    );
  connectBranch<int>   ( name, tree, "index",    &m_darkJet_index );

  if ( m_histoInfoSwitch->m_djet_energy )
    connectBranch<float> ( name, tree, "Width", &m_darkJet_width );
  if ( m_histoInfoSwitch->m_djet_constit ) {
    connectBranch<float>              ( name, tree, "girth",                  &m_darkJet_girth          );
    connectBranch<int>                ( name, tree, "numConstituents",        &m_darkJet_numConstit     );
    connectBranch<float>              ( name, tree, "constituentPt",          &m_darkJet_constitPt      );
    connectBranch<std::vector<int>>   ( name, tree, "constituent_ID",         &m_darkJet_constit_ID     );
    connectBranch<std::vector<int>>   ( name, tree, "constituent_index",      &m_darkJet_constit_index  );
    connectBranch<std::vector<float>> ( name, tree, "constituent_pt",         &m_darkJet_constit_pt     );
    connectBranch<std::vector<float>> ( name, tree, "constituent_charge",     &m_darkJet_constit_charge );
    connectBranch<std::vector<float>> ( name, tree, "constituent_dR",         &m_darkJet_constit_dR     );
    connectBranch<std::vector<float>> ( name, tree, "constituent_decayVtx_r", &m_darkJet_constit_dVtx_r );
  }

  if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_trk ) && !m_truth ) {
    connectBranch<int>                  ( name, tree, "trkCount",    &m_darkJet_trkCount    );
    connectBranch<float>                ( name, tree, "trkPt",       &m_darkJet_trkPt       );
    connectBranch<std::vector<int>>     ( name, tree, "trk_ID",      &m_darkJet_trk_ID      );
    connectBranch<std::vector<int>>     ( name, tree, "trk_index",   &m_darkJet_trk_index   );
    connectBranch<std::vector<float>>   ( name, tree, "trk_dR",      &m_darkJet_trk_dR      );
  }
  if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_tp ) { 
    connectBranch<int>                  ( name, tree, "tpCount",     &m_darkJet_tpCount     );
    connectBranch<float>                ( name, tree, "tpPt",        &m_darkJet_tpPt        );
    connectBranch<std::vector<int>>     ( name, tree, "tp_ID",       &m_darkJet_tp_ID       );
    connectBranch<std::vector<int>>     ( name, tree, "tp_index",    &m_darkJet_tp_index    );
    connectBranch<std::vector<float>>   ( name, tree, "tp_pt",       &m_darkJet_tp_pt       );
    connectBranch<std::vector<float>>   ( name, tree, "tp_charge",   &m_darkJet_tp_charge   );
    connectBranch<std::vector<int>>     ( name, tree, "tp_pdgId",    &m_darkJet_tp_pdgId    );
    connectBranch<std::vector<float>>   ( name, tree, "tp_dR",       &m_darkJet_tp_dR       );
    connectBranch<std::vector<uint8_t>> ( name, tree, "tp_isStable", &m_darkJet_tp_isStable );
    connectBranch<std::vector<uint8_t>> ( name, tree, "tp_isDark",   &m_darkJet_tp_isDark   );
  }

  if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_vtx ) && !m_truth ) {
    connectBranch<int>                      ( name, tree, "secVtxCount",       &m_darkJet_secVtxCount    );
    connectBranch<float>                    ( name, tree, "secVtxPt",          &m_darkJet_secVtxPt       );
    connectBranch<std::vector<int>>         ( name, tree, "secVtx_ID",         &m_darkJet_secVtx_ID      );
    connectBranch<std::vector<int>>         ( name, tree, "secVtx_index",      &m_darkJet_secVtx_index   );
    connectBranch<std::vector<float>>       ( name, tree, "secVtx_dR",         &m_darkJet_secVtx_dR      );
  }
  if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_tvtx ) {
    connectBranch<int>                      ( name, tree, "truthVtxCount",     &m_darkJet_truthVtxCount  );
    connectBranch<float>                    ( name, tree, "truthVtxPt",        &m_darkJet_truthVtxPt     );
    connectBranch<std::vector<int>>         ( name, tree, "truthVtx_ID",       &m_darkJet_truthVtx_ID    );
    connectBranch<std::vector<int>>         ( name, tree, "truthVtx_index",    &m_darkJet_truthVtx_index );
    connectBranch<std::vector<std::string>> ( name, tree, "truthVtx_llpDecay", &m_darkJet_truthVtx_llp   );
    connectBranch<std::vector<float>>       ( name, tree, "truthVtx_r",        &m_darkJet_truthVtx_r     );
    connectBranch<std::vector<float>>       ( name, tree, "truthVtx_mass",     &m_darkJet_truthVtx_mass  );
    connectBranch<std::vector<float>>       ( name, tree, "truthVtx_dR",       &m_darkJet_truthVtx_dR    );
  }

  if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_truth ) {
    connectBranch<uint8_t>   ( name, tree, "isMatchedToTruth",             &m_darkJet_isTruthMatch     );
    connectBranch<int>       ( name, tree, "matchedTruthID",               &m_darkJet_truthMatch_ID    );
    connectBranch<int>       ( name, tree, "matchedTruthIndex",            &m_darkJet_truthMatch_index );
    connectBranch<float>     ( name, tree, "matchedTruthDR",               &m_darkJet_truthMatch_dR    );
    if ( !m_truth ) {
      connectBranch<uint8_t> ( name, tree, "isMatchedTo" + m_jetStr,       &m_darkJet_isRecoMatch      );
      connectBranch<int>     ( name, tree, "matched" + m_jetStr + "ID",    &m_darkJet_recoMatch_ID     );
      connectBranch<int>     ( name, tree, "matched" + m_jetStr + "Index", &m_darkJet_recoMatch_index  );
      connectBranch<float>   ( name, tree, "matched" + m_jetStr + "DR",    &m_darkJet_recoMatch_dR     );
    }
  }

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTracks ( TTree* tree, const std::string& trackName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTracks()", "connecting track branches" );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthParts ( TTree* tree, const std::string& truthPartName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthParts()", "connecting truth particle branches" );

  std::string name = truthPartName;
  
  using namespace EJsHelper;
  connectBranch<int> ( tree, "n"+name, &m_tp_n );

  using namespace HelperFunctions;
  connectBranch<int>              ( name, tree, "ID",            &m_tp_ID            );
  connectBranch<int>              ( name, tree, "index",         &m_tp_index         );
  connectBranch<float>            ( name, tree, "pt",            &m_tp_pt            );
  connectBranch<float>            ( name, tree, "eta",           &m_tp_eta           ); 
  connectBranch<float>            ( name, tree, "phi",           &m_tp_phi           );
  connectBranch<float>            ( name, tree, "E",             &m_tp_E             );
  connectBranch<float>            ( name, tree, "M",             &m_tp_M             );
  connectBranch<float>            ( name, tree, "charge",        &m_tp_charge        );
  connectBranch<int>              ( name, tree, "pdgId",         &m_tp_pdgId         );
  connectBranch<int>              ( name, tree, "status",        &m_tp_status        );
  connectBranch<uint8_t>          ( name, tree, "isStable",      &m_tp_isStable      );
  connectBranch<uint8_t>          ( name, tree, "isDark",        &m_tp_isDark        );
  connectBranch<int>              ( name, tree, "nParents",      &m_tp_nParents      );
  connectBranch<std::vector<int>> ( name, tree, "parent_pdgId",  &m_tp_parent_pdgId  );
  connectBranch<std::vector<int>> ( name, tree, "parent_status", &m_tp_parent_status );
  connectBranch<int>              ( name, tree, "nChildren",     &m_tp_nChildren     );
  connectBranch<std::vector<int>> ( name, tree, "child_pdgId",   &m_tp_child_pdgId   );
  connectBranch<std::vector<int>> ( name, tree, "child_status",  &m_tp_child_status  );
  connectBranch<uint8_t>          ( name, tree, "hasProdVtx",    &m_tp_hasPVtx       );
  connectBranch<float>            ( name, tree, "prodVtx_r",     &m_tp_pVtx_r        );
  connectBranch<uint8_t>          ( name, tree, "hasDecayVtx",   &m_tp_hasDVtx       );
  connectBranch<float>            ( name, tree, "decayVtx_r",    &m_tp_dVtx_r        );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectSecondaryVerts ( TTree* tree, const std::string& secVtxName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectSecondaryVerts()", "connecting secondary vertex branches" );

  std::string name = secVtxName;

  using namespace EJsHelper;
  connectBranch<int> ( tree, "n"+name, &m_secVtx_n );

  using namespace HelperFunctions;
  connectBranch<int>                ( name, tree, "ID",            &m_secVtx_ID            );
  connectBranch<int>                ( name, tree, "index",         &m_secVtx_index         );
  connectBranch<float>              ( name, tree, "x",             &m_secVtx_x             );
  connectBranch<float>              ( name, tree, "y",             &m_secVtx_y             );
  connectBranch<float>              ( name, tree, "z",             &m_secVtx_z             );
  connectBranch<float>              ( name, tree, "r",             &m_secVtx_r             );
  connectBranch<float>              ( name, tree, "pt",            &m_secVtx_pt            );
  connectBranch<float>              ( name, tree, "eta",           &m_secVtx_eta           );
  connectBranch<float>              ( name, tree, "phi",           &m_secVtx_phi           );
  connectBranch<float>              ( name, tree, "mass",          &m_secVtx_mass          );
  connectBranch<float>              ( name, tree, "mass_nonAssoc", &m_secVtx_mass_nonAssoc );
  connectBranch<float>              ( name, tree, "chi2",          &m_secVtx_chi2          );
  connectBranch<float>              ( name, tree, "direction",     &m_secVtx_direction     );
  connectBranch<int>                ( name, tree, "charge",        &m_secVtx_charge        );
  connectBranch<float>              ( name, tree, "Ht",            &m_secVtx_Ht            );
  connectBranch<float>              ( name, tree, "minOpAng",      &m_secVtx_minOpAng      );
  connectBranch<float>              ( name, tree, "maxOpAng",      &m_secVtx_maxOpAng      );
  connectBranch<float>              ( name, tree, "mind0",         &m_secVtx_mind0         );
  connectBranch<float>              ( name, tree, "maxd0",         &m_secVtx_maxd0         );
  connectBranch<std::vector<float>> ( name, tree, "twoTracksMass", &m_secVtx_twoTrkMass    );
  connectBranch<uint32_t>           ( name, tree, "ntrk",          &m_secVtx_ntrk          );
  connectBranch<uint32_t>           ( name, tree, "ntrk_sel",      &m_secVtx_ntrk_sel      );
  connectBranch<uint32_t>           ( name, tree, "ntrk_assoc",    &m_secVtx_ntrk_assoc    );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthVerts ( TTree* tree, const std::string& truthVtxName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthVerts()", "connecting truth vertex branches" );

  std::string name = truthVtxName;

  using namespace EJsHelper;
  connectBranch<int> ( tree, "n"+name, &m_truthVtx_n );

  using namespace HelperFunctions;
  connectBranch<int>         ( name, tree, "ID",       &m_truthVtx_ID    );
  connectBranch<int>         ( name, tree, "index",    &m_truthVtx_index );
  connectBranch<std::string> ( name, tree, "llpDecay", &m_truthVtx_llp   );
  connectBranch<float>       ( name, tree, "x",        &m_truthVtx_x     );
  connectBranch<float>       ( name, tree, "y",        &m_truthVtx_y     );
  connectBranch<float>       ( name, tree, "z",        &m_truthVtx_z     );
  connectBranch<float>       ( name, tree, "r",        &m_truthVtx_r     );
  connectBranch<float>       ( name, tree, "pt",       &m_truthVtx_pt    );
  connectBranch<float>       ( name, tree, "eta",      &m_truthVtx_eta   );
  connectBranch<float>       ( name, tree, "phi",      &m_truthVtx_phi   );
  connectBranch<float>       ( name, tree, "mass",     &m_truthVtx_mass  );
  connectBranch<int>         ( name, tree, "nOutP",    &m_truthVtx_nOutP );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: initialize ( const std::string& outFileName, const std::vector<std::string>& regions,
					       const std::string& jetHistName )
{
  if ( m_debug ) Info( "EJsHistogramManager::initialize()", "booking histograms" );

  std::string hjet  = jetHistName;
  std::string htjet = "truthJet";
  std::string hdjet = "darkJet";

  // loop over regions + book histograms
  for ( const auto& region : regions ) {
    const std::string name = m_name + outFileName + "/" + region + "/";

    // event info
    if ( m_histoInfoSwitch->m_eventInfo ) {
      h_njetHt .push_back( book( name, "N"+m_jetStr+"JetHt", "N-jet scalar sum-p_{T} [GeV]", 100, 0, 5000 ) ); // change name
      // pileup
      if ( m_histoInfoSwitch->m_pileup && !m_truth ) {
	h_npv       .push_back( book( name, "nPV",       "n primary vertices",               50, 0,  50 ) );
	h_actualMu  .push_back( book( name, "actualMu",  "actual interactions / crossing",  100, 0, 100 ) );
	h_averageMu .push_back( book( name, "averageMu", "average interactions / crossing", 100, 0, 100 ) );
      }
      // primary vertex
      if ( m_histoInfoSwitch->m_pv && !m_truth ) {
	h_pv_x    .push_back( book( name, "pv_x",    "PV x-pos [mm]", 100, -1.5, 1.5 ) );
	h_pv_y    .push_back( book( name, "pv_y",    "PV y-pos [mm]", 100, -1.5, 1.5 ) );
	h_pv_z    .push_back( book( name, "pv_z",    "PV z-pos [mm]", 100, -150, 150 ) );
	h_pv_r    .push_back( book( name, "pv_r",    "PV r-pos [mm]", 100,    0, 1.5 ) );
	h_pv_phi  .push_back( book( name, "pv_phi",  "PV phi",        100, -3.5, 3.5 ) );
	//h_pv_ntrk .push_back( book( name, "pv_nTrk", "n PV tracks",   100,    0, 350 ) );
      }
    } // end event-info switch

    
    // reco jets
    if ( m_histoInfoSwitch->m_jets && !m_truth ) {
      h_jet_n      .push_back( book( name, hjet + "_n",     "n jets",            20,    0,   20 ) );
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
      if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	h_jet_px   .push_back( book( name, hjet + "_px",    "jet p_{x} [GeV]",  100, -1500, 1500 ) );
	h_jet_py   .push_back( book( name, hjet + "_py",    "jet p_{y} [GeV]",  100, -1500, 1500 ) );
	h_jet_pz   .push_back( book( name, hjet + "_pz",    "jet p_{z} [GeV]",  100, -2500, 2500 ) );
	h_jet_Et   .push_back( book( name, hjet + "_Et",    "jet E_{T} [GeV]",  100,     0, 1500 ) );
	h_jet_Et_l .push_back( book( name, hjet + "_Et_l",  "jet E_{T} [GeV]",  100,     0, 2500 ) );
	h_jet_Et_m .push_back( book( name, hjet + "_Et_m",  "jet E_{T} [GeV]",  100,     0,  500 ) );
	h_jet_Et_s .push_back( book( name, hjet + "_Et_s",  "jet E_{T} [GeV]",  100,     0,  200 ) );
      }
      // leading jets
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
	std::vector<TH1F*> h_nlead_Et_l;
	std::vector<TH1F*> h_nlead_Et_m;
	std::vector<TH1F*> h_nlead_Et_s;
	for ( int i = 0; i != m_numLeadJets; ++i ) {
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
	if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	  h_jetN_Et   .push_back( h_nlead_Et    );
	  h_jetN_Et_l .push_back( h_nlead_Et_l  );
	  h_jetN_Et_m .push_back( h_nlead_Et_m  );
	  h_jetN_Et_s .push_back( h_nlead_Et_s  );
	}
      }

      // jet energy
      if ( m_histoInfoSwitch->m_jet_energy ) {
	h_jet_hecFrac   .push_back( book( name, hjet + "_hecFrac",   "HEC calo jet energy fraction", 100, -0.1,  1.1 ) );
	h_jet_emFrac    .push_back( book( name, hjet + "_emFrac",    "EM calo jet energy fraction",  100, -0.1,  1.1 ) );
	h_jet_centroidR .push_back( book( name, hjet + "_centroidR", "jet centroid R",               100,    0, 7500 ) );
	h_jet_width     .push_back( book( name, hjet + "_width",     "jet width",                    100,    0,  0.4 ) );
      }
      // jet constituents
      if ( m_histoInfoSwitch->m_jet_constit )
	h_jet_numConstit .push_back( book( name, hjet + "_numConstit", "n jet constituents", 75, 0, 75 ) );

      // jet track moments (PV)
      if ( m_histoInfoSwitch->m_jet_trkMoms ) {
	h_jet_numTrkPt10
	  .push_back( book( name, hjet + "_numTrkPt1000",   "n p_{T} > 1.0 GeV jet track moments",               75, 0,   75 ) );
	h_jet_sumPtTrkPt10
	  .push_back( book( name, hjet + "_sumPtTrkPt1000", "p_{T} > 1.0 GeV jet track moment sum-p_{T} [GeV]", 100, 0, 1000 ) );
	h_jet_trkWidthPt10
	  .push_back( book( name, hjet + "_trkWidthPt1000", "p_{T} > 1.0 GeV jet track moment width",           100, 0,  0.6 ) );
	h_jet_numTrkPt5
	  .push_back( book( name, hjet + "_numTrkPt500",    "n p_{T} > 0.5 GeV jet track moments",               75, 0,   75 ) );
	h_jet_sumPtTrkPt5
	  .push_back( book( name, hjet + "_sumPtTrkPt500",  "p_{T} > 0.5 GeV jet track moment sum-p_{T} [GeV]", 100, 0, 1000 ) );
	h_jet_trkWidthPt5
	  .push_back( book( name, hjet + "_trkWidthPt500",  "p_{T} > 0.5 GeV jet track moment width",           100, 0,  0.6 ) );
	h_jet_jvf
	  .push_back( book( name, hjet + "_JVF",            "jet vertex fraction",                              100, 0,    1 ) );
	h_jet_jvt
	  .push_back( book( name, hjet + "_JVT",            "jet vertex tagger",                                100, 0,    1 ) );
      }

      // jet ghost tracks
      if ( m_histoInfoSwitch->m_jet_ghost || m_histoInfoSwitch->m_jet_ghostTrk ) {
	h_jet_ghostTrkCount .push_back( book( name, hjet + "_GhostTrackCount",   "jet ghost track count",           125, 0,  250 ) );
	h_jet_ghostTrkPt    .push_back( book( name, hjet + "_GhostTrackPt",      "jet ghost track sum-p_{T} [GeV]", 100, 0, 2500 ) );
	h_jet_ghostTrk_dR   .push_back( book( name, hjet + "_GhostTrack_dR",     "jet - ghost-track dR",            100, 0,  0.6 ) );
      }
      // jet ghost truth particles
      if ( ( m_histoInfoSwitch->m_jet_ghost || m_histoInfoSwitch->m_jet_ghostTruth ) && m_mc ) {
	h_jet_ghostTruthCount .push_back( book( name, hjet + "_GhostTruthCount", "jet ghost truth count",           125, 0,  250 ) );
	h_jet_ghostTruthPt    .push_back( book( name, hjet + "_GhostTruthPt",    "jet ghost truth sum-p_{T} [GeV]", 100, 0, 2500 ) );
	h_jet_ghostTruth_dR   .push_back( book( name, hjet + "_GhostTruth_dR",   "jet - ghost-truth dR",            100, 0,  0.6 ) );
      }

      // jet dR-matched tracks
      if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_trk ) {
	h_jet_trkCount .push_back( book( name, hjet + "_trkCount", "jet-matched track count",                100, 0,   500 ) );
	h_jet_trkPt    .push_back( book( name, hjet + "_trkPt",    "jet-matched track sum-p_{T} [GeV]",      100, 0,  5000 ) );
	h_jet_trk_dR   .push_back( book( name, hjet + "_trk_dR",   "jet - matched-track dR",                 100, 0,     1 ) );
      }
      // jet dR-matched truth particles
      if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_tp ) && m_mc ) {
	h_jet_tpCount  .push_back( book( name, hjet + "_tpCount",  "jet-matched truth part count",           100, 0,   800 ) );
	h_jet_tpPt     .push_back( book( name, hjet + "_tpPt",     "jet-matched truth part sum-p_{T} [GeV]", 100, 0, 35000 ) );
	h_jet_tp_dR    .push_back( book( name, hjet + "_tp_dR",    "jet - matched-truth part dR",            100, 0,     1 ) );
      }

      // jet dR-matched secondary vertices
      if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_vtx ) {
	h_jet_secVtxCount   .push_back( book( name, hjet + "_secVtxCount",   "jet-matched sec vertex count",               7, 0,    7 ) );
	h_jet_secVtxPt      .push_back( book( name, hjet + "_secVtxPt",      "jet-matched sec vertex sum-p_{T} [GeV]",   100, 0,  200 ) );
	h_jet_secVtx_dR     .push_back( book( name, hjet + "_secVtx_dR",     "jet - matched-sec-vertex dR",              100, 0,    1 ) );
      }
      // jet dR-matched truth vertices
      if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_tvtx ) && m_mc ) {
	h_jet_truthVtxCount .push_back( book( name, hjet + "_truthVtxCount", "jet-matched truth vertex count",            35, 0,   35 ) );
	h_jet_truthVtxPt    .push_back( book( name, hjet + "_truthVtxPt",    "jet-matched truth vertex sum-p_{T} [GeV]", 100, 0, 1500 ) );
	h_jet_truthVtx_dR   .push_back( book( name, hjet + "_truthVtx_dR",   "jet - matched-truth-vertex dR",            100, 0,    1 ) );
      }

      // jets vs pileup
      if ( m_histoInfoSwitch->m_pileup ) {
	h_jet_n_vs_avgMu .push_back( book( name, hjet + "_n_vs_avgMu", "< #mu >", 100, 0, 100, "n jets", 20, 0, 20 ) );
	h_jet_n_vs_actMu .push_back( book( name, hjet + "_n_vs_actMu",   "#mu",   100, 0, 100, "n jets", 20, 0, 20 ) );
      }
    } // end jet switch


    // truth jets
    if ( m_histoInfoSwitch->m_tjets && m_mc ) {
      h_truthJet_n      .push_back( book( name, htjet + "_n",     "n truth jets",            75,    0,   75 ) );
      h_truthJet_pt     .push_back( book( name, htjet + "_pt",    "truth jet p_{T} [GeV]",  100,    0, 1500 ) );
      h_truthJet_pt_l   .push_back( book( name, htjet + "_pt_l",  "truth jet p_{T} [GeV]",  100,    0, 2500 ) );
      h_truthJet_pt_m   .push_back( book( name, htjet + "_pt_m",  "truth jet p_{T} [GeV]",  100,    0,  500 ) );
      h_truthJet_pt_s   .push_back( book( name, htjet + "_pt_s",  "truth jet p_{T} [GeV]",  100,    0,  200 ) );
      h_truthJet_eta    .push_back( book( name, htjet + "_eta",   "truth jet eta",          100,   -5,    5 ) );
      h_truthJet_phi    .push_back( book( name, htjet + "_phi",   "truth jet phi",          100, -3.5,  3.5 ) );
      h_truthJet_E      .push_back( book( name, htjet + "_E",     "truth jet energy [GeV]", 100,    0, 2500 ) );
      h_truthJet_M      .push_back( book( name, htjet + "_M",     "truth jet mass [GeV]",   100,    0,  300 ) );
      h_truthJet_rapid  .push_back( book( name, htjet + "_rapid", "truth jet rapidity",     100,   -5,    5 ) );
      // truth jet kinematics
      if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_tjet ) {
	h_truthJet_px   .push_back( book( name, htjet + "_px",    "truth jet p_{x} [GeV]",  100, -1500, 1500 ) );
	h_truthJet_py   .push_back( book( name, htjet + "_py",    "truth jet p_{y} [GeV]",  100, -1500, 1500 ) );
	h_truthJet_pz   .push_back( book( name, htjet + "_pz",    "truth jet p_{z} [GeV]",  100, -2500, 2500 ) );
	h_truthJet_Et   .push_back( book( name, htjet + "_Et",    "truth jet E_{T} [GeV]",  100,     0, 1500 ) );
	h_truthJet_Et_l .push_back( book( name, htjet + "_Et_l",  "truth jet E_{T} [GeV]",  100,     0, 2500 ) );
	h_truthJet_Et_m .push_back( book( name, htjet + "_Et_m",  "truth jet E_{T} [GeV]",  100,     0,  500 ) );
	h_truthJet_Et_s .push_back( book( name, htjet + "_Et_s",  "truth jet E_{T} [GeV]",  100,     0,  200 ) );
      }
      // leading truth jets
      if ( m_numLeadTJets ) {
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
	for ( int i = 0; i != m_numLeadTJets; ++i ) {
	  std::string njet = std::to_string(i);
	  h_nlead_pt    .push_back( book( name, ( htjet + njet + "_pt"    ), ( "truth-jet-" + njet + " p_{T} [GeV]"  ), 100,    0, 1500 ) );
	  h_nlead_pt_l  .push_back( book( name, ( htjet + njet + "_pt_l"  ), ( "truth-jet-" + njet + " p_{T} [GeV]"  ), 100,    0, 2500 ) );
	  h_nlead_pt_m  .push_back( book( name, ( htjet + njet + "_pt_m"  ), ( "truth-jet-" + njet + " p_{T} [GeV]"  ), 100,    0,  500 ) );
	  h_nlead_pt_s  .push_back( book( name, ( htjet + njet + "_pt_s"  ), ( "truth-jet-" + njet + " p_{T} [GeV]"  ), 100,    0,  200 ) );
	  h_nlead_eta   .push_back( book( name, ( htjet + njet + "_eta"   ), ( "truth-jet-" + njet + " eta"          ), 100,   -5,    5 ) );
	  h_nlead_phi   .push_back( book( name, ( htjet + njet + "_phi"   ), ( "truth-jet-" + njet + " phi"          ), 100, -3.5,  3.5 ) );
	  h_nlead_E     .push_back( book( name, ( htjet + njet + "_E"     ), ( "truth-jet-" + njet + " energy [GeV]" ), 100,    0, 2500 ) );
	  h_nlead_M     .push_back( book( name, ( htjet + njet + "_M"     ), ( "truth-jet-" + njet + " mass [GeV]"   ), 100,    0,  300 ) );
	  h_nlead_rapid .push_back( book( name, ( htjet + njet + "_rapid" ), ( "truth-jet-" + njet + " rapidity"     ), 100,   -5,    5 ) );
	  h_nlead_Et    .push_back( book( name, ( htjet + njet + "_Et"    ), ( "truth-jet-" + njet + " E_{T} [GeV]"  ), 100,    0, 1500 ) );
	  h_nlead_Et_l  .push_back( book( name, ( htjet + njet + "_Et_l"  ), ( "truth-jet-" + njet + " E_{T} [GeV]"  ), 100,    0, 2500 ) );
	  h_nlead_Et_m  .push_back( book( name, ( htjet + njet + "_Et_m"  ), ( "truth-jet-" + njet + " E_{T} [GeV]"  ), 100,    0,  500 ) );
	  h_nlead_Et_s  .push_back( book( name, ( htjet + njet + "_Et_s"  ), ( "truth-jet-" + njet + " E_{T} [GeV]"  ), 100,    0,  200 ) );
	}
	h_truthJetN_pt     .push_back( h_nlead_pt    );
	h_truthJetN_pt_l   .push_back( h_nlead_pt_l  );
	h_truthJetN_pt_m   .push_back( h_nlead_pt_m  );
	h_truthJetN_pt_s   .push_back( h_nlead_pt_s  );
	h_truthJetN_eta    .push_back( h_nlead_eta   );
	h_truthJetN_phi    .push_back( h_nlead_phi   );
	h_truthJetN_E      .push_back( h_nlead_E     );
	h_truthJetN_M      .push_back( h_nlead_M     );
	h_truthJetN_rapid  .push_back( h_nlead_rapid );
	// leading truth jet kinematics
	if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_tjet ) {
	  h_truthJetN_Et   .push_back( h_nlead_Et    );
	  h_truthJetN_Et_l .push_back( h_nlead_Et_l  );
	  h_truthJetN_Et_m .push_back( h_nlead_Et_m  );
	  h_truthJetN_Et_s .push_back( h_nlead_Et_s  );
	}
      }

      // truth jet energy (width)
      if ( m_histoInfoSwitch->m_tjet_energy )
    	h_truthJet_width .push_back( book( name, htjet + "_width", "truth jet width", 100, 0,  0.4 ) );
      // truth jet constituents
      if ( m_histoInfoSwitch->m_tjet_constit ) {
    	h_truthJet_girth          .push_back( book( name, htjet + "_girth",          "truth jet girth",                   100, 0,  0.5 ) );
    	h_truthJet_nConstit       .push_back( book( name, htjet + "_nConstit",       "n truth jet constits",              100, 0,  200 ) );
    	h_truthJet_constitPt      .push_back( book( name, htjet + "_constitPt",      "truth-jet constit sum-p_{T} [GeV]", 100, 0, 2000 ) );
    	h_truthJet_constit_dR     .push_back( book( name, htjet + "_constit_dR",     "truth-jet - constit dR",            100, 0,  4.5 ) );
	h_truthJet_constit_pVtx_r .push_back( book( name, htjet + "_constit_pVtx_r", "truth-jet constit pVtx r-pos [mm]", 100, 0, 2500 ) );
	h_truthJet_nChrgConstit   .push_back( book( name, htjet + "_nChrgConstit",   "n truth jet charged constits",      100, 0,  100 ) );
	h_truthJet_nVisConstit    .push_back( book( name, htjet + "_nVisConstit",    "n truth jet visible constits",      100, 0,  100 ) );
      }

      // truth jet dR-matched tracks
      if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_trk ) && !m_truth ) {
    	h_truthJet_trkCount .push_back( book( name, "truthJet_trkCount", "truth-jet-matched track count",           125, 0,  250 ) );
    	h_truthJet_trkPt    .push_back( book( name, "truthJet_trkPt",    "truth-jet-matched track sum-p_{T} [GeV]", 100, 0, 2500 ) );
    	h_truthJet_trk_dR   .push_back( book( name, "truthJet_trk_dR",   "truth-jet - matched-track dR",            100, 0,  0.4 ) );
      }
      // truth jet dR-matched truth particles
      if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_tp ) {
    	h_truthJet_tpCount
	  .push_back( book( name, "truthJet_tpCount",     "truth-jet-matched truth part count",           100, 0,   500 ) );
    	h_truthJet_tpPt
	  .push_back( book( name, "truthJet_tpPt",        "truth-jet-matched truth part sum-p_{T} [GeV]", 100, 0, 25000 ) );
    	h_truthJet_tp_dR
	  .push_back( book( name, "truthJet_tp_dR",       "truth-jet - matched-truth-part dR",            100, 0,     1 ) );
    	h_truthJet_chrgTpCount
	  .push_back( book( name, "truthJet_chrgTpCount", "truth-jet-matched charged truth part count",   125, 0,   250 ) );
    	h_truthJet_visTpCount
	  .push_back( book( name, "truthJet_visTpCount",  "truth-jet-matched visible truth part count",   100, 0,   100 ) );
    	h_truthJet_darkTpCount
	  .push_back( book( name, "truthJet_darkTpCount", "truth-jet-matched dark truth part count",      100, 0,   100 ) );
    	h_truthJet_pidTpCount
	  .push_back( book( name, "truthJet_pidTpCount",  "truth-jet-matched dark pion count",             50, 0,    50 ) );
      }
      
      // truth jet dR-matched secondary vertices
      if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_vtx ) && !m_truth ) {
    	h_truthJet_secVtxCount
	  .push_back( book( name, "truthJet_secVtxCount", "truth-jet-matched sec vertex count",             7, 0,   7 ) );
    	h_truthJet_secVtxPt
	  .push_back( book( name, "truthJet_secVtxPt",    "truth-jet-matched sec vertex sum-p_{T} [GeV]", 100, 0, 100 ) );
    	h_truthJet_secVtx_dR
	  .push_back( book( name, "truthJet_secVtx_dR",   "truth-jet - matched-sec-vertex dR",            100, 0,   1 ) );
      }
      // truth jet dR-matched truth vertices
      if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_tvtx ) {
    	h_truthJet_truthVtxCount
	  .push_back( book( name, "truthJet_truthVtxCount",     "truth-jet-matched truth vertex count",                25, 0,   25 ) );
    	h_truthJet_truthVtxPt
	  .push_back( book( name, "truthJet_truthVtxPt",        "truth-jet-matched truth vertex sum-p_{T} [GeV]",     100, 0, 1500 ) );
    	h_truthJet_truthVtx_dR
	  .push_back( book( name, "truthJet_truthVtx_dR",       "truth-jet - matched-truth-vertex dR",                100, 0,    1 ) );
	h_truthJet_truthVtx_r
	  .push_back( book( name, "truthJet_truthVtx_r",        "truth-jet-matched truth vertex r-pos [mm]",          100, 0, 2500 ) );
	h_truthJet_truthVtx_mass
	  .push_back( book( name, "truthJet_truthVtx_mass",     "truth-jet-matched truth vertex mass [GeV]",          100, 0,  200 ) );
	h_truthJet_pidTruthVtxCount
	  .push_back( book( name, "truthJet_pidTruthVtxCount",  "truth-jet-matched dark pion decay vtx count",         20, 0,   20 ) );
	h_truthJet_dispTruthVtxCount
	  .push_back( book( name, "truthJet_dispTruthVtxCount", "truth-jet-matched disp. (r > 0 mm) truth vtx count",  25, 0,   25 ) );
      }
    } // end truth jet switch


    // dark jets
    if ( m_histoInfoSwitch->m_djets && m_mc ) {
      h_darkJet_n      .push_back( book( name, hdjet + "_n",     "n dark jets",            50,    0,   50 ) );
      h_darkJet_pt     .push_back( book( name, hdjet + "_pt",    "dark jet p_{T} [GeV]",  100,    0, 1500 ) );
      h_darkJet_pt_l   .push_back( book( name, hdjet + "_pt_l",  "dark jet p_{T} [GeV]",  100,    0, 2500 ) );
      h_darkJet_pt_m   .push_back( book( name, hdjet + "_pt_m",  "dark jet p_{T} [GeV]",  100,    0,  500 ) );
      h_darkJet_pt_s   .push_back( book( name, hdjet + "_pt_s",  "dark jet p_{T} [GeV]",  100,    0,  200 ) );
      h_darkJet_eta    .push_back( book( name, hdjet + "_eta",   "dark jet eta",          100,   -5,    5 ) );
      h_darkJet_phi    .push_back( book( name, hdjet + "_phi",   "dark jet phi",          100, -3.5,  3.5 ) );
      h_darkJet_E      .push_back( book( name, hdjet + "_E",     "dark jet energy [GeV]", 100,    0, 2500 ) );
      h_darkJet_M      .push_back( book( name, hdjet + "_M",     "dark jet mass [GeV]",   100,    0,  300 ) );
      h_darkJet_rapid  .push_back( book( name, hdjet + "_rapid", "dark jet rapidity",     100,   -5,    5 ) );
      // dark jet kinematics
      if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_djet ) {
	h_darkJet_px   .push_back( book( name, hdjet + "_px",    "dark jet p_{x} [GeV]",  100, -1500, 1500 ) );
	h_darkJet_py   .push_back( book( name, hdjet + "_py",    "dark jet p_{y} [GeV]",  100, -1500, 1500 ) );
	h_darkJet_pz   .push_back( book( name, hdjet + "_pz",    "dark jet p_{z} [GeV]",  100, -2500, 2500 ) );
	h_darkJet_Et   .push_back( book( name, hdjet + "_Et",    "dark jet E_{T} [GeV]",  100,     0, 1500 ) );
	h_darkJet_Et_l .push_back( book( name, hdjet + "_Et_l",  "dark jet E_{T} [GeV]",  100,     0, 2500 ) );
	h_darkJet_Et_m .push_back( book( name, hdjet + "_Et_m",  "dark jet E_{T} [GeV]",  100,     0,  500 ) );
	h_darkJet_Et_s .push_back( book( name, hdjet + "_Et_s",  "dark jet E_{T} [GeV]",  100,     0,  200 ) );
      }
      // leading dark jets
      if ( m_numLeadDJets ) {
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
	for ( int i = 0; i != m_numLeadDJets; ++i ) {
	  std::string njet = std::to_string(i);
	  h_nlead_pt    .push_back( book( name, ( hdjet + njet + "_pt"    ), ( "dark-jet-" + njet + " p_{T} [GeV]"  ), 100,    0, 1500 ) );
	  h_nlead_pt_l  .push_back( book( name, ( hdjet + njet + "_pt_l"  ), ( "dark-jet-" + njet + " p_{T} [GeV]"  ), 100,    0, 2500 ) );
	  h_nlead_pt_m  .push_back( book( name, ( hdjet + njet + "_pt_m"  ), ( "dark-jet-" + njet + " p_{T} [GeV]"  ), 100,    0,  500 ) );
	  h_nlead_pt_s  .push_back( book( name, ( hdjet + njet + "_pt_s"  ), ( "dark-jet-" + njet + " p_{T} [GeV]"  ), 100,    0,  200 ) );
	  h_nlead_eta   .push_back( book( name, ( hdjet + njet + "_eta"   ), ( "dark-jet-" + njet + " eta"          ), 100,   -5,    5 ) );
	  h_nlead_phi   .push_back( book( name, ( hdjet + njet + "_phi"   ), ( "dark-jet-" + njet + " phi"          ), 100, -3.5,  3.5 ) );
	  h_nlead_E     .push_back( book( name, ( hdjet + njet + "_E"     ), ( "dark-jet-" + njet + " energy [GeV]" ), 100,    0, 2500 ) );
	  h_nlead_M     .push_back( book( name, ( hdjet + njet + "_M"     ), ( "dark-jet-" + njet + " mass [GeV]"   ), 100,    0,  300 ) );
	  h_nlead_rapid .push_back( book( name, ( hdjet + njet + "_rapid" ), ( "dark-jet-" + njet + " rapidity"     ), 100,   -5,    5 ) );
	  h_nlead_Et    .push_back( book( name, ( hdjet + njet + "_Et"    ), ( "dark-jet-" + njet + " E_{T} [GeV]"  ), 100,    0, 1500 ) );
	  h_nlead_Et_l  .push_back( book( name, ( hdjet + njet + "_Et_l"  ), ( "dark-jet-" + njet + " E_{T} [GeV]"  ), 100,    0, 2500 ) );
	  h_nlead_Et_m  .push_back( book( name, ( hdjet + njet + "_Et_m"  ), ( "dark-jet-" + njet + " E_{T} [GeV]"  ), 100,    0,  500 ) );
	  h_nlead_Et_s  .push_back( book( name, ( hdjet + njet + "_Et_s"  ), ( "dark-jet-" + njet + " E_{T} [GeV]"  ), 100,    0,  200 ) );
	}
	h_darkJetN_pt     .push_back( h_nlead_pt    );
	h_darkJetN_pt_l   .push_back( h_nlead_pt_l  );
	h_darkJetN_pt_m   .push_back( h_nlead_pt_m  );
	h_darkJetN_pt_s   .push_back( h_nlead_pt_s  );
	h_darkJetN_eta    .push_back( h_nlead_eta   );
	h_darkJetN_phi    .push_back( h_nlead_phi   );
	h_darkJetN_E      .push_back( h_nlead_E     );
	h_darkJetN_M      .push_back( h_nlead_M     );
	h_darkJetN_rapid  .push_back( h_nlead_rapid );
	// leading dark jet kinematics
	if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_djet ) {
	  h_darkJetN_Et   .push_back( h_nlead_Et    );
	  h_darkJetN_Et_l .push_back( h_nlead_Et_l  );
	  h_darkJetN_Et_m .push_back( h_nlead_Et_m  );
	  h_darkJetN_Et_s .push_back( h_nlead_Et_s  );
	}
      }

      // dark jet energy (width)
      if ( m_histoInfoSwitch->m_djet_energy )
    	h_darkJet_width .push_back( book( name, hdjet + "_width", "dark jet width", 100, 0,  0.4 ) );
      // dark jet constituents
      if ( m_histoInfoSwitch->m_djet_constit ) {
    	h_darkJet_girth          .push_back( book( name, hdjet + "_girth",          "dark jet girth",                   100, 0,  0.5 ) );
    	h_darkJet_nConstit       .push_back( book( name, hdjet + "_nConstit",       "n dark jet constits",               25, 0,   25 ) );
    	h_darkJet_constitPt      .push_back( book( name, hdjet + "_constitPt",      "dark-jet constit sum-p_{T} [GeV]", 100, 0, 2000 ) );
    	h_darkJet_constit_dR     .push_back( book( name, hdjet + "_constit_dR",     "dark-jet - constit dR",            100, 0,  0.4 ) );
	h_darkJet_constit_dVtx_r .push_back( book( name, hdjet + "_constit_dVtx_r", "dark-jet constit dVtx r-pos [mm]", 100, 0, 2500 ) );
	h_darkJet_nChrgConstit   .push_back( book( name, hdjet + "_nChrgConstit",   "n dark jet charged constits",      100, 0,  100 ) );
	h_darkJet_nVisConstit    .push_back( book( name, hdjet + "_nVisConstit",    "n dark jet visible constits",      100, 0,  100 ) );
      }

      // dark jet dR-matched tracks
      if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_trk ) && !m_truth ) {
    	h_darkJet_trkCount .push_back( book( name, "darkJet_trkCount", "dark-jet-matched track count",           125, 0,  250 ) );
    	h_darkJet_trkPt    .push_back( book( name, "darkJet_trkPt",    "dark-jet-matched track sum-p_{T} [GeV]", 100, 0, 2500 ) );
    	h_darkJet_trk_dR   .push_back( book( name, "darkJet_trk_dR",   "dark-jet - matched-track dR",            100, 0,    1 ) );
      }
      // dark jet dR-matched truth particles
      if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_tp ) {
    	h_darkJet_tpCount
	  .push_back( book( name, "darkJet_tpCount",     "dark-jet-matched truth part count",           100, 0,   500 ) );
    	h_darkJet_tpPt
	  .push_back( book( name, "darkJet_tpPt",        "dark-jet-matched truth part sum-p_{T} [GeV]", 100, 0, 25000 ) );
    	h_darkJet_tp_dR
	  .push_back( book( name, "darkJet_tp_dR",       "dark-jet - matched-truth-part dR",            100, 0,     1 ) );
    	h_darkJet_chrgTpCount
	  .push_back( book( name, "darkJet_chrgTpCount", "dark-jet-matched charged truth part count",   100, 0,   500 ) );
    	h_darkJet_visTpCount
	  .push_back( book( name, "darkJet_visTpCount",  "dark-jet-matched visible truth part count",   100, 0,   500 ) );
    	h_darkJet_darkTpCount
	  .push_back( book( name, "darkJet_darkTpCount", "dark-jet-matched dark truth part count",      100, 0,   500 ) );
    	h_darkJet_pidTpCount
	  .push_back( book( name, "darkJet_pidTpCount",  "dark-jet-matched dark pion count",             50, 0,   500 ) );
      }
      
      // dark jet dR-matched secondary vertices
      if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_vtx ) && !m_truth ) {
    	h_darkJet_secVtxCount
	  .push_back( book( name, "darkJet_secVtxCount", "dark-jet-matched sec vertex count",             7, 0,   7 ) );
    	h_darkJet_secVtxPt
	  .push_back( book( name, "darkJet_secVtxPt",    "dark-jet-matched sec vertex sum-p_{T} [GeV]", 100, 0, 100 ) );
    	h_darkJet_secVtx_dR
	  .push_back( book( name, "darkJet_secVtx_dR",   "dark-jet - matched-sec-vertex dR",            100, 0,   1 ) );
      }
      // dark jet dR-matched truth vertices
      if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_tvtx ) {
    	h_darkJet_truthVtxCount
	  .push_back( book( name, "darkJet_truthVtxCount",     "dark-jet-matched truth vertex count",                25, 0,   25 ) );
    	h_darkJet_truthVtxPt
	  .push_back( book( name, "darkJet_truthVtxPt",        "dark-jet-matched truth vertex sum-p_{T} [GeV]",     100, 0, 1500 ) );
    	h_darkJet_truthVtx_dR
	  .push_back( book( name, "darkJet_truthVtx_dR",       "dark-jet - matched-truth-vertex dR",                100, 0,    1 ) );
	h_darkJet_truthVtx_r
	  .push_back( book( name, "darkJet_truthVtx_r",        "dark-jet-matched truth vertex r-pos [mm]",          100, 0, 2500 ) );
	h_darkJet_truthVtx_mass
	  .push_back( book( name, "darkJet_truthVtx_mass",     "dark-jet-matched truth vertex mass [GeV]",          100, 0,  200 ) );
	h_darkJet_pidTruthVtxCount
	  .push_back( book( name, "darkJet_pidTruthVtxCount",  "dark-jet-matched dark pion decay vtx count",         20, 0,   20 ) );
	h_darkJet_dispTruthVtxCount
	  .push_back( book( name, "darkJet_dispTruthVtxCount", "dark-jet-matched disp. (r > 0 mm) truth vtx count",  25, 0,   25 ) );
      }   
    } // end dark jet switch


    // truth particles
    if ( m_histoInfoSwitch->m_tps && m_mc ) {
      h_tp_n            .push_back( book( name, "tp_n",                 "n truth particles",                      100,    0,    2000 ) );
      h_tp_pt           .push_back( book( name, "tp_pt",                "truth particle p_{T} [GeV]",             100,    0,    2500 ) );
      h_tp_eta          .push_back( book( name, "tp_eta",               "truth particle eta",                     100,  -10,      10 ) );
      h_tp_phi          .push_back( book( name, "tp_phi",               "truth particle phi",                     100, -3.5,     3.5 ) );
      h_tp_E            .push_back( book( name, "tp_E",                 "truth particle energy [GeV]",            100,    0,    5000 ) );
      h_tp_M            .push_back( book( name, "tp_M",                 "truth particle mass [GeV]",              100,    0,    2000 ) );
      h_tp_sumPt        .push_back( book( name, "tp_sumPt",             "truth particle sum-p_{T} [GeV]",         100,    0,  100000 ) );
      h_tp_nCharged     .push_back( book( name, "tp_nCharged",          "n charged truth particles",              100,    0,    1000 ) );
      h_tp_chargedSumPt .push_back( book( name, "tp_sumPtCharged",      "charged truth particle sum-p_{T} [GeV]", 100,    0,   75000 ) );
      h_tp_nVisible     .push_back( book( name, "tp_nVisible",          "n visible truth particles",               125,   0,     250 ) );
      h_tp_visibleSumPt .push_back( book( name, "tp_visibleSumPt",      "visible truth particle sum-p_{T} [GeV]",  100,   0,    3500 ) ); // fix name
      h_tp_nDark        .push_back( book( name, "tp_nDark",             "n dark truth particles",                  100,   0,     750 ) );
      h_tp_darkSumPt    .push_back( book( name, "tp_sumPtDark",         "dark truth particle sum-p_{T} [GeV]",     100,   0,   75000 ) );
      // heavy scalar mediator (Xd) truth particles
      if ( m_histoInfoSwitch->m_tps_xd ) {
	h_Xd_n            .push_back( book( name, "Xd_n",            "n scalar mediators",                        5,       0,       5 ) );
	h_Xd_pt           .push_back( book( name, "Xd_pt",           "scalar mediator p_{T} [GeV]",             100,       0,    2500 ) );
	h_Xd_eta          .push_back( book( name, "Xd_eta",          "scalar mediator eta",                     100,      -5,       5 ) );
	h_Xd_phi          .push_back( book( name, "Xd_phi",          "scalar mediator phi",                     100,    -3.5,     3.5 ) );
	h_Xd_E            .push_back( book( name, "Xd_E",            "scalar mediator energy [GeV]",            100,       0,    4000 ) );
	h_Xd_M            .push_back( book( name, "Xd_M",            "scalar mediator mass [GeV]",              100,       0,    2000 ) );
	h_Xd_charge       .push_back( book( name, "Xd_charge",       "scalar mediator charge",                  100,      -1,       1 ) );
	h_Xd_nParents     .push_back( book( name, "Xd_nParents",     "n scalar mediator parents",                 5,       0,       5 ) );
	h_Xd_parentPdgId  .push_back( book( name, "Xd_parentPdgId",  "scalar mediator parent pdgId",              5, 4900000, 4900005 ) );
	h_Xd_parentStatus .push_back( book( name, "Xd_parentStatus", "scalar mediator parent status",           100,       0,     100 ) );
	h_Xd_nChildren    .push_back( book( name, "Xd_nChildren",    "n scalar mediator children",                5,       0,       5 ) );
	h_Xd_childPdgId   .push_back( book( name, "Xd_childPdgId",   "scalar mediator child pdgId",             100,       0, 4900105 ) );
	h_Xd_childStatus  .push_back( book( name, "Xd_childStatus",  "scalar mediator child status",            100,       0,     100 ) );
	h_Xd_prodVtx_r    .push_back( book( name, "Xd_prodVtx_r",    "scalar mediator prod vertex r-pos [mm]",  100,       0,       1 ) );
	h_Xd_decayVtx_r   .push_back( book( name, "Xd_decayVtx_r",   "scalar mediator decay vertex r-pos [mm]", 100,       0,       1 ) );
	h_Xd_sumPt        .push_back( book( name, "Xd_sumPt",        "scalar mediator sum-p_{T} [GeV]",         100,       0,    6000 ) );
      }
      // dark quark (qd) truth particles
      if ( m_histoInfoSwitch->m_tps_qd ) {
	h_qd_n            .push_back( book( name, "qd_n",            "n dark quarks",                        5,       0,       5 ) );
	h_qd_pt           .push_back( book( name, "qd_pt",           "dark quark p_{T} [GeV]",             100,       0,    1500 ) );
	h_qd_eta          .push_back( book( name, "qd_eta",          "dark quark eta",                     100,      -5,       5 ) );
	h_qd_phi          .push_back( book( name, "qd_phi",          "dark quark phi",                     100,    -3.5,     3.5 ) );
	h_qd_E            .push_back( book( name, "qd_E",            "dark quark energy [GeV]",            100,       0,    2000 ) );
	h_qd_M            .push_back( book( name, "qd_M",            "dark quark mass [GeV]",              100,       0,      50 ) );
	h_qd_charge       .push_back( book( name, "qd_charge",       "dark quark charge",                  100,      -1,       1 ) );
	h_qd_nParents     .push_back( book( name, "qd_nParents",     "n dark quark parents",                 5,       0,       5 ) );
	h_qd_parentPdgId  .push_back( book( name, "qd_parentPdgId",  "dark quarks parent pdgId",             5, 4900100, 4900105 ) );
	h_qd_parentStatus .push_back( book( name, "qd_parentStatus", "dark quark parent status",           100,       0,     100 ) );
	h_qd_nChildren    .push_back( book( name, "qd_nChildren",    "n dark quark children",              100,       0,     100 ) );
	h_qd_childPdgId   .push_back( book( name, "qd_childPdgId",   "dark quark child pdgId",             125, 4900100, 4900225 ) );
	h_qd_childStatus  .push_back( book( name, "qd_childStatus",  "dark quark child status",            100,       0,     100 ) );
	h_qd_prodVtx_r    .push_back( book( name, "qd_prodVtx_r",    "dark quark prod vertex r-pos [mm]",  100,       0,       1 ) );
	h_qd_decayVtx_r   .push_back( book( name, "qd_decayVtx_r",   "dark quark decay vertex r-pos [mm]", 100,       0,       1 ) );
	h_qd_sumPt        .push_back( book( name, "qd_sumPt",        "dark quark sum-p_{T} [GeV]",         100,       0,    3000 ) );
      }
      // dark pion (pid) truth particles
      if ( m_histoInfoSwitch->m_tps_pid ) {
	h_pid_n            .push_back( book( name, "pid_n",            "n dark pions",                      150,       0,     150 ) );
	h_pid_pt           .push_back( book( name, "pid_pt",           "dark pion p_{T} [GeV]",             100,       0,     350 ) );
	h_pid_eta          .push_back( book( name, "pid_eta",          "dark pion eta",                     100,      -5,       5 ) );
	h_pid_phi          .push_back( book( name, "pid_phi",          "dark pion phi",                     100,    -3.5,     3.5 ) );
	h_pid_E            .push_back( book( name, "pid_E",            "dark pion energy [GeV]",            100,       0,     500 ) );
	h_pid_M            .push_back( book( name, "pid_M",            "dark pion mass [GeV]",              100,       0,      25 ) );
	h_pid_charge       .push_back( book( name, "pid_charge",       "dark pion charge",                  100,    -1.5,     1.5 ) );
	h_pid_nParents     .push_back( book( name, "pid_nParents",     "n dark pion parents",                 5,       0,     100 ) );
	h_pid_parentPdgId  .push_back( book( name, "pid_parentPdgId",  "dark pion parent pdgId",            225, 4900000, 4900225 ) );
	h_pid_parentStatus .push_back( book( name, "pid_parentStatus", "dark pion parent status",           100,       0,     100 ) );
	h_pid_nChildren    .push_back( book( name, "pid_nChildren",    "n dark pion children",               12,       0,      12 ) );
	h_pid_childPdgId   .push_back( book( name, "pid_childPdgId",   "dark pion child pdgId",             100,       0,    3500 ) );
	h_pid_childStatus  .push_back( book( name, "pid_childStatus",  "dark pion child status",            100,       0,     100 ) );
	h_pid_prodVtx_r    .push_back( book( name, "pid_prodVtx_r",    "dark pion prod vertex r-pos [mm]",  100,       0,       1 ) );
	h_pid_decayVtx_r   .push_back( book( name, "pid_decayVtx_r",   "dark pion decay vertex r-pos [mm]", 100,       0,    2500 ) );
	h_pid_sumPt        .push_back( book( name, "pid_sumPt",        "dark pion sum-p_{T} [GeV]",         100,       0,    3000 ) );
      }
      // dark rho (rhod) truth particles
      if ( m_histoInfoSwitch->m_tps_pid ) {
	h_rhod_n            .push_back( book( name, "rhod_n",            "n dark rhos",                       75,       0,      75 ) );
	h_rhod_pt           .push_back( book( name, "rhod_pt",           "dark rho p_{T} [GeV]",             100,       0,     500 ) );
	h_rhod_eta          .push_back( book( name, "rhod_eta",          "dark rho eta",                     100,      -5,       5 ) );
	h_rhod_phi          .push_back( book( name, "rhod_phi",          "dark rho phi",                     100,    -3.5,     3.5 ) );
	h_rhod_E            .push_back( book( name, "rhod_E",            "dark rho energy [GeV]",            100,       0,     750 ) );
	h_rhod_M            .push_back( book( name, "rhod_M",            "dark rho mass [GeV]",              100,       0,     100 ) );
	h_rhod_charge       .push_back( book( name, "rhod_charge",       "dark rho charge",                  100,    -1.5,     1.5 ) );
	h_rhod_nParents     .push_back( book( name, "rhod_nParents",     "n dark rho parents",                 5,       0,     100 ) );
	h_rhod_parentPdgId  .push_back( book( name, "rhod_parentPdgId",  "dark rho parent pdgId",            225, 4900000, 4900225 ) );
	h_rhod_parentStatus .push_back( book( name, "rhod_parentStatus", "dark rho parent status",           100,       0,     100 ) );
	h_rhod_nChildren    .push_back( book( name, "rhod_nChildren",    "n dark rho children",               12,       0,      12 ) );
	h_rhod_childPdgId   .push_back( book( name, "rhod_childPdgId",   "dark rho child pdgId",             100,       0, 4900225 ) );
	h_rhod_childStatus  .push_back( book( name, "rhod_childStatus",  "dark rho child status",            100,       0,     100 ) );
	h_rhod_prodVtx_r    .push_back( book( name, "rhod_prodVtx_r",    "dark rho prod vertex r-pos [mm]",  100,       0,       1 ) );
	h_rhod_decayVtx_r   .push_back( book( name, "rhod_decayVtx_r",   "dark rho decay vertex r-pos [mm]", 100,       0,       1 ) );
	h_rhod_sumPt        .push_back( book( name, "rhod_sumPt",        "dark rho sum-p_{T} [GeV]",         100,       0,    2500 ) );
      }
    } // end truth particle switch


    // secondary vertices
    if ( m_histoInfoSwitch->m_verts && !m_truth ) {
      h_secVtx_n               .push_back( book( name, "secVtx_n",               "n sec vertices",                       25,     0,   25 ) );
      h_secVtx_x               .push_back( book( name, "secVtx_x",               "sec vertex x-pos [mm]",               100,  -500,  500 ) );
      h_secVtx_y               .push_back( book( name, "secVtx_y",               "sec vertex y-pos [mm]",               100,  -500,  500 ) );
      h_secVtx_z               .push_back( book( name, "secVtx_z",               "sec vertex z-pos [mm]",               100, -1000, 1000 ) );
      h_secVtx_r               .push_back( book( name, "secVtx_r",               "sec vertex r-pos [mm]",               100,     0,  300 ) );
      h_secVtx_r_l             .push_back( book( name, "secVtx_r_l",             "sec vertex r-pos [mm]",               100,     0,  500 ) );
      h_secVtx_r_s             .push_back( book( name, "secVtx_r_s",             "sec vertex r-pos [mm]",               100,     0,  100 ) );
      h_secVtx_pt              .push_back( book( name, "secVtx_pt",              "sec vertex p_{T} [GeV]",              100,     0,  100 ) );
      h_secVtx_eta             .push_back( book( name, "secVtx_eta",             "sec vertex eta",                      100,    -5,    5 ) );
      h_secVtx_phi             .push_back( book( name, "secVtx_phi",             "sec vertex phi",                      100,  -3.5,  3.5 ) );
      h_secVtx_mass            .push_back( book( name, "secVtx_mass",            "sec vertex mass [GeV]",               100,     0,   50 ) );
      h_secVtx_mass_l          .push_back( book( name, "secVtx_mass_l",          "sec vertex mass [GeV]",               100,     0,  100 ) );
      h_secVtx_mass_s          .push_back( book( name, "secVtx_mass_s",          "sec vertex mass [GeV]",               100,     0,   25 ) );
      h_secVtx_mass_nonAssoc   .push_back( book( name, "secVtx_mass_nonAssoc",   "sec vertex non-assoc-trk mass [GeV]", 100,     0,   50 ) );
      h_secVtx_mass_nonAssoc_l .push_back( book( name, "secVtx_mass_nonAssoc_l", "sec vertex non-assoc-trk mass [GeV]", 100,     0,  100 ) );
      h_secVtx_mass_nonAssoc_s .push_back( book( name, "secVtx_mass_nonAssoc_s", "sec vertex non-assoc-trk mass [GeV]", 100,     0,   25 ) );
      h_secVtx_chi2            .push_back( book( name, "secVtx_chi2",            "sec vertex chi2 / DoF",               100,     0,   20 ) );
      h_secVtx_direction       .push_back( book( name, "secVtx_direction",       "sec vertex direction",                100,  -1.1,  1.1 ) );
      h_secVtx_charge          .push_back( book( name, "secVtx_charge",          "sec vertex charge",                    11,    -5,    5 ) );
      h_secVtx_Ht              .push_back( book( name, "secVtx_Ht",              "sec vertex scalar sum-p_{T} [GeV]",   100,     0,  100 ) );
      h_secVtx_minOpAng        .push_back( book( name, "secVtx_minOpAng",        "sec vertex minimum opening angle",    100,  -1.1,  1.1 ) );
      h_secVtx_maxOpAng        .push_back( book( name, "secVtx_maxOpAng",        "sec vertex maximum opening angle",    100,  -1.1,  1.1 ) );
      h_secVtx_mind0           .push_back( book( name, "secVtx_mind0",           "sec vertex minimum track d0",         100,     0,  250 ) );
      h_secVtx_maxd0           .push_back( book( name, "secVtx_maxd0",           "sec vertex maximum track d0",         100,     0,  250 ) );
      h_secVtx_twoTrkMass      .push_back( book( name, "secVtx_twoTrkMass",      "sec vertex 2-track mass [GeV]",       100,     0,   50 ) );
      h_secVtx_twoTrkMass_l    .push_back( book( name, "secVtx_twoTrkMass_l",    "sec vertex 2-track mass [GeV]",       100,     0,  100 ) );
      h_secVtx_twoTrkMass_s    .push_back( book( name, "secVtx_twoTrkMass_s",    "sec vertex 2-track mass [GeV]",       100,     0,   25 ) );
      h_secVtx_ntrk            .push_back( book( name, "secVtx_ntrk",            "sec vertex n tracks",                  10,     2,   12 ) );
      h_secVtx_ntrk_sel        .push_back( book( name, "secVtx_ntrk_sel",        "sec vertex n selected tracks",         10,     0,   10 ) );
      h_secVtx_ntrk_assoc      .push_back( book( name, "secVtx_ntrk_assoc",      "sec vertex n associated tracks",       10,     0,   10 ) );
      // n-track secondary vertices
      if ( m_numVtxTrks ) {
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
	for ( int i = 1; i != m_numVtxTrks; ++i ) {
	  std::string ntrk = std::to_string(i+1);
	  h_ntrk_n         .push_back( book( name, ntrk + "trkSecVtx_n",
					     "n " + ntrk + "-track sec vertices",                  20,     0,   20 ) );
	  h_ntrk_x         .push_back( book( name, ntrk + "trkSecVtx_x",
					     ntrk + "-track sec vertex x-pos [mm]",               100,  -500,  500 ) );
	  h_ntrk_y         .push_back( book( name, ntrk + "trkSecVtx_y",
					     ntrk + "-track sec vertex y-pos [mm]",               100,  -500,  500 ) );
	  h_ntrk_z         .push_back( book( name, ntrk + "trkSecVtx_z",
					     ntrk + "-track sec vertex z-pos [mm]",               100, -1000, 1000 ) );
	  h_ntrk_r         .push_back( book( name, ntrk + "trkSecVtx_r",
					     ntrk + "-track sec vertex r-pos [mm]",               100,     0,  300 ) );
	  h_ntrk_r_l       .push_back( book( name, ntrk + "trkSecVtx_r_l",
					     ntrk + "-track sec vertex r-pos [mm]",               100,     0,  500 ) );
	  h_ntrk_r_s       .push_back( book( name, ntrk + "trkSecVtx_r_s",
					     ntrk + "-track sec vertex r-pos [mm]",               100,     0,  100 ) );
	  h_ntrk_pt        .push_back( book( name, ntrk + "trkSecVtx_pt",
					     ntrk + "-track sec vertex p_{T} [GeV]",              100,     0,  100 ) );
	  h_ntrk_eta       .push_back( book( name, ntrk + "trkSecVtx_eta",
					     ntrk + "-track sec vertex eta",                      100,    -5,    5 ) );
	  h_ntrk_phi       .push_back( book( name, ntrk + "trkSecVtx_phi",
					     ntrk + "-track sec vertex phi",                      100,  -3.5,  3.5 ) );
	  h_ntrk_mass      .push_back( book( name, ntrk + "trkSecVtx_mass",
					     ntrk + "-track sec vertex mass [GeV]",               100,     0,   50 ) );
	  h_ntrk_mass_l    .push_back( book( name, ntrk + "trkSecVtx_mass_l",
					     ntrk + "-track sec vertex mass [GeV]",               100,     0,  100 ) );
	  h_ntrk_mass_s    .push_back( book( name, ntrk + "trkSecVtx_mass_s",
					     ntrk + "-track sec vertex mass [GeV]",               100,     0,   25 ) );
	  h_ntrk_massNon   .push_back( book( name, ntrk + "trkSecVtx_mass_nonAssoc",
					     ntrk + "-track sec vertex non-assoc-trk mass [GeV]", 100,     0,   50 ) );
	  h_ntrk_massNon_l .push_back( book( name, ntrk + "trkSecVtx_mass_nonAssoc_l",
					     ntrk + "-track sec vertex non-assoc-trk mass [GeV]", 100,     0,  100 ) );
	  h_ntrk_massNon_s .push_back( book( name, ntrk + "trkSecVtx_mass_nonAssoc_s",
					     ntrk + "-track sec vertex non-assoc-trk mass [GeV]", 100,     0,   25 ) );
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
      }
    } // end secondary vertex switch


    // truth vertices
    if ( m_histoInfoSwitch->m_tverts && m_mc ) {
      h_truthVtx_n        .push_back( book( name, "truthVtx_n",        "n truth vertices",                      150,    0,   150 ) );
      h_truthVtx_x        .push_back( book( name, "truthVtx_x",        "truth vertex x-pos [mm]",               100, -2500, 2500 ) );
      h_truthVtx_y        .push_back( book( name, "truthVtx_y",        "truth vertex y-pos [mm]",               100, -2500, 2500 ) );
      h_truthVtx_z        .push_back( book( name, "truthVtx_z",        "truth vertex z-pos [mm]",               100, -5000, 5000 ) );
      h_truthVtx_r        .push_back( book( name, "truthVtx_r",        "truth vertex r-pos [mm]",               100,     0, 2500 ) );
      h_truthVtx_pt       .push_back( book( name, "truthVtx_pt",       "truth vertex p_{T} [GeV]",              100,     0,  500 ) );
      h_truthVtx_eta      .push_back( book( name, "truthVtx_eta",      "truth vertex eta",                      100,    -5,    5 ) );
      h_truthVtx_phi      .push_back( book( name, "truthVtx_phi",      "truth vertex phi",                      100,  -3.5,  3.5 ) );
      h_truthVtx_mass     .push_back( book( name, "truthVtx_mass",     "truth vertex mass [GeV]",               100,     0,  200 ) );
      h_truthVtx_nOutP    .push_back( book( name, "truthVtx_nOutP",    "n truth vertex outgoing parts",          25,     0,   25 ) );
      // dark pion truth vertex decays
      h_truthVtxPid_n     .push_back( book( name, "truthVtxPid_n",     "n truth dark pion decays",              150,    0,   150 ) );
      h_truthVtxPid_x     .push_back( book( name, "truthVtxPid_x",     "truth dark pion decay x-pos [mm]",      100, -2500, 2500 ) );
      h_truthVtxPid_y     .push_back( book( name, "truthVtxPid_y",     "truth dark pion decay y-pos [mm]",      100, -2500, 2500 ) );
      h_truthVtxPid_z     .push_back( book( name, "truthVtxPid_z",     "truth dark pion decay z-pos [mm]",      100, -5000, 5000 ) );
      h_truthVtxPid_r     .push_back( book( name, "truthVtxPid_r",     "truth dark pion decay r-pos [mm]",      100,     0, 2500 ) );
      h_truthVtxPid_pt    .push_back( book( name, "truthVtxPid_pt",    "truth dark pion decay p_{T} [GeV]",     100,     0,  500 ) );
      h_truthVtxPid_eta   .push_back( book( name, "truthVtxPid_eta",   "truth dark pion decay eta",             100,    -5,    5 ) );
      h_truthVtxPid_phi   .push_back( book( name, "truthVtxPid_phi",   "truth dark pion decay phi",             100,  -3.5,  3.5 ) );
      h_truthVtxPid_mass  .push_back( book( name, "truthVtxPid_mass",  "truth dark pion decay mass [GeV]",      100,     0,   25 ) );
      h_truthVtxPid_nOutP .push_back( book( name, "truthVtxPid_nOutP", "n truth dark pion decay outgoing parts",  5,     0,    5 ) );
    }
    
  } // end loop over regions

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: execute ( TTree* tree, Long64_t treeEntry, const std::vector<EJsHelper::Region>& regions )
{
  if ( m_debug ) Info( "EJsHistogramManager::execute()", "filling histograms" );

  tree->GetEntry( treeEntry );

  // loop over regions + fill histograms
  for ( size_t ireg = 0; ireg != regions.size(); ++ireg ) {
    const EJsHelper::Region region = regions.at(ireg);

    if      ( region.type == EJsHelper::SIGNAL     ) { if ( !m_signal ) continue; }
    else if ( region.type == EJsHelper::VALIDATION ) { if ( !m_valid  ) continue; }
    else if ( region.type == EJsHelper::CONTROL    ) { if ( !m_ctrl   ) continue; }

    
    // ------------------ //
    // --- EVENT INFO --- //
    // ------------------ //
    if ( m_histoInfoSwitch->m_eventInfo ) {
      h_njetHt .at(ireg) ->Fill( m_njetHt );
      // pileup
      if ( m_histoInfoSwitch->m_pileup && !m_truth ) {
	h_npv       .at(ireg) ->Fill( m_npv       );
	h_actualMu  .at(ireg) ->Fill( m_actualMu  );
	h_averageMu .at(ireg) ->Fill( m_averageMu );
      }
      // primary vertex
      if ( m_histoInfoSwitch->m_pv && !m_truth ) {
	h_pv_x    .at(ireg) ->Fill( m_pv_x    );
	h_pv_y    .at(ireg) ->Fill( m_pv_y    );
	h_pv_z    .at(ireg) ->Fill( m_pv_z    );
	h_pv_r    .at(ireg) ->Fill( m_pv_r    );
	h_pv_phi  .at(ireg) ->Fill( m_pv_phi  );
	//h_pv_ntrk .at(ireg) ->Fill( m_pv_ntrk );
      }
    } // end event-info switch

    
    // ----------------- //
    // --- RECO JETS --- //
    // ----------------- //
    if ( m_histoInfoSwitch->m_jets && !m_truth ) {
      h_jet_n .at(ireg)->Fill( m_jet_n );

      // n jets vs pileup
      if ( m_histoInfoSwitch->m_pileup ) {
	h_jet_n_vs_avgMu .at(ireg)->Fill( m_averageMu, m_jet_n );
	h_jet_n_vs_actMu .at(ireg)->Fill( m_actualMu,  m_jet_n );
      }

      // loop over jets
      for ( int i = 0; i != m_jet_n; ++i ) {
	
	TLorentzVector jet_p4;
	jet_p4.SetPtEtaPhiM( m_jet_pt->at(i), m_jet_eta->at(i), m_jet_phi->at(i), m_jet_M->at(i) );
      
	h_jet_pt     .at(ireg)->Fill( m_jet_pt    ->at(i) );
	h_jet_pt_l   .at(ireg)->Fill( m_jet_pt    ->at(i) );
	h_jet_pt_m   .at(ireg)->Fill( m_jet_pt    ->at(i) );
	h_jet_pt_s   .at(ireg)->Fill( m_jet_pt    ->at(i) );
	h_jet_eta    .at(ireg)->Fill( m_jet_eta   ->at(i) );
	h_jet_phi    .at(ireg)->Fill( m_jet_phi   ->at(i) );
	h_jet_E      .at(ireg)->Fill( m_jet_E     ->at(i) );
	h_jet_M      .at(ireg)->Fill( m_jet_M     ->at(i) );
	h_jet_rapid  .at(ireg)->Fill( m_jet_rapid ->at(i) );
	// jet kinematics
	if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	  h_jet_px   .at(ireg)->Fill( jet_p4.Px() );
	  h_jet_py   .at(ireg)->Fill( jet_p4.Py() );
	  h_jet_pz   .at(ireg)->Fill( jet_p4.Pz() );
	  h_jet_Et   .at(ireg)->Fill( jet_p4.Et() );
	  h_jet_Et_l .at(ireg)->Fill( jet_p4.Et() );
	  h_jet_Et_m .at(ireg)->Fill( jet_p4.Et() );
	  h_jet_Et_s .at(ireg)->Fill( jet_p4.Et() );
	}
	// leading jets
	if ( m_numLeadJets ) {
	  if ( i < m_numLeadJets ) {
	    h_jetN_pt     .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i) );
	    h_jetN_pt_l   .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i) );
	    h_jetN_pt_m   .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i) );
	    h_jetN_pt_s   .at(ireg).at(i) ->Fill( m_jet_pt    ->at(i) );
	    h_jetN_eta    .at(ireg).at(i) ->Fill( m_jet_eta   ->at(i) );
	    h_jetN_phi    .at(ireg).at(i) ->Fill( m_jet_phi   ->at(i) );
	    h_jetN_E      .at(ireg).at(i) ->Fill( m_jet_E     ->at(i) );
	    h_jetN_M      .at(ireg).at(i) ->Fill( m_jet_M     ->at(i) );
	    h_jetN_rapid  .at(ireg).at(i) ->Fill( m_jet_rapid ->at(i) );
	    if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_jet ) {
	      h_jetN_Et   .at(ireg).at(i) ->Fill( jet_p4.Et() );
	      h_jetN_Et_l .at(ireg).at(i) ->Fill( jet_p4.Et() );
	      h_jetN_Et_m .at(ireg).at(i) ->Fill( jet_p4.Et() );
	      h_jetN_Et_s .at(ireg).at(i) ->Fill( jet_p4.Et() );
	    }
	  }
	}

	// jet energy
	if ( m_histoInfoSwitch->m_jet_energy ) {
	  h_jet_hecFrac      .at(ireg)->Fill( m_jet_hecFrac       ->at(i) );
	  h_jet_emFrac       .at(ireg)->Fill( m_jet_emFrac        ->at(i) );
	  h_jet_centroidR    .at(ireg)->Fill( m_jet_centroidR     ->at(i) );
	  h_jet_width        .at(ireg)->Fill( m_jet_width         ->at(i) );
	}
	// jet constituents
	if ( m_histoInfoSwitch->m_jet_constit )
	  h_jet_numConstit   .at(ireg)->Fill( m_jet_numConstit    ->at(i) );
	// jet track moments (PV)
	if ( m_histoInfoSwitch->m_jet_trkMoms ) {
	  h_jet_numTrkPt10   .at(ireg) ->Fill( m_jet_numTrkPt10   ->at(i) );
	  h_jet_sumPtTrkPt10 .at(ireg) ->Fill( m_jet_sumPtTrkPt10 ->at(i) );
	  h_jet_trkWidthPt10 .at(ireg) ->Fill( m_jet_trkWidthPt10 ->at(i) );
	  h_jet_numTrkPt5    .at(ireg) ->Fill( m_jet_numTrkPt5    ->at(i) );
	  h_jet_sumPtTrkPt5  .at(ireg) ->Fill( m_jet_sumPtTrkPt5  ->at(i) );
	  h_jet_trkWidthPt5  .at(ireg) ->Fill( m_jet_trkWidthPt5  ->at(i) );
	  h_jet_jvf          .at(ireg) ->Fill( m_jet_jvf          ->at(i) );
	  h_jet_jvt          .at(ireg) ->Fill( m_jet_jvt          ->at(i) );
	}

	// ghost tracks
	if ( m_histoInfoSwitch->m_jet_ghost || m_histoInfoSwitch->m_jet_ghostTrk ) {
	  h_jet_ghostTrkCount .at(ireg)->Fill( m_jet_ghostTrkCount ->at(i) );
	  h_jet_ghostTrkPt    .at(ireg)->Fill( m_jet_ghostTrkPt    ->at(i) );
	  for ( int j = 0; j != m_jet_ghostTrkCount->at(i); ++ j ) {
	    // calculate dR b/w ghost tracks + jet
	    double eta = m_jet_ghostTrk_eta ->at(i).at(j);
	    double phi = m_jet_ghostTrk_phi ->at(i).at(j);
	    double dR  = EJsHelper::deltaR( m_jet_eta->at(i), eta, m_jet_phi->at(i), phi );
	    h_jet_ghostTrk_dR .at(ireg)->Fill( dR );
	  }
	}
	// ghostTruth
	if ( ( m_histoInfoSwitch->m_jet_ghost || m_histoInfoSwitch->m_jet_ghostTruth ) && m_mc ) {
	  h_jet_ghostTruthCount .at(ireg)->Fill( m_jet_ghostTruthCount ->at(i) );
	  h_jet_ghostTruthPt    .at(ireg)->Fill( m_jet_ghostTruthPt    ->at(i) );
	  for ( int j = 0; j != m_jet_ghostTruthCount->at(i); ++ j ) {
	    // calculate dR b/w ghost truth + jet
	    double eta = m_jet_ghostTruth_eta ->at(i).at(j);
	    double phi = m_jet_ghostTruth_phi ->at(i).at(j);
	    double dR  = EJsHelper::deltaR( m_jet_eta->at(i), eta, m_jet_phi->at(i), phi );
	    h_jet_ghostTruth_dR .at(ireg)->Fill( dR );
	  }
	}

	// dR-matched tracks
	if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_trk ) {
	  h_jet_trkCount .at(ireg)->Fill( m_jet_trkCount ->at(i) );
	  h_jet_trkPt    .at(ireg)->Fill( m_jet_trkPt    ->at(i) );
	  for ( int j = 0; j != m_jet_trkCount->at(i); ++j )
	    h_jet_trk_dR .at(ireg)->Fill( m_jet_trk_dR ->at(i).at(j) );
	}
	// dR-matched truth particles
	if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_tp ) && m_mc ) {
	  h_jet_tpCount .at(ireg)->Fill( m_jet_tpCount ->at(i) );
	  h_jet_tpPt    .at(ireg)->Fill( m_jet_tpPt    ->at(i) );
	  for ( int j = 0; j != m_jet_tpCount->at(i); ++j )
	    h_jet_tp_dR .at(ireg)->Fill( m_jet_tp_dR ->at(i).at(j) );
	}

	// dR-matched secondary vertices
	if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_vtx ) {
	  h_jet_secVtxCount .at(ireg)->Fill( m_jet_secVtxCount ->at(i) );
	  h_jet_secVtxPt    .at(ireg)->Fill( m_jet_secVtxPt    ->at(i) );
	  for ( int j = 0; j != m_jet_secVtxCount->at(i); ++j )
	    h_jet_secVtx_dR .at(ireg)->Fill( m_jet_secVtx_dR ->at(i).at(j) );
	}
	// dR-matched truth vertices
	if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_jet || m_histoInfoSwitch->m_match_jet_tvtx ) && m_mc ) {
	  h_jet_truthVtxCount .at(ireg)->Fill( m_jet_truthVtxCount ->at(i) );
	  h_jet_truthVtxPt    .at(ireg)->Fill( m_jet_truthVtxPt    ->at(i) );
	  for ( int j = 0; j != m_jet_truthVtxCount->at(i); ++j )
	    h_jet_truthVtx_dR .at(ireg)->Fill( m_jet_truthVtx_dR ->at(i).at(j) );
	}
	
      } // end loop over jets
      
    } // end jet switch


    // ------------------ //
    // --- TRUTH JETS --- //
    // ------------------ //
    if ( m_histoInfoSwitch->m_tjets && m_mc ) {
      h_truthJet_n .at(ireg)->Fill( m_truthJet_n );

      // loop over truth jets
      for ( int i = 0; i != m_truthJet_n; ++i ) {

    	TLorentzVector truthJet_p4;
    	truthJet_p4.SetPtEtaPhiM( m_truthJet_pt->at(i), m_truthJet_eta->at(i), m_truthJet_phi->at(i), m_truthJet_M->at(i) );
	
    	h_truthJet_pt    .at(ireg)->Fill( m_truthJet_pt    ->at(i) );
    	h_truthJet_pt_l  .at(ireg)->Fill( m_truthJet_pt    ->at(i) );
    	h_truthJet_pt_m  .at(ireg)->Fill( m_truthJet_pt    ->at(i) );
    	h_truthJet_pt_s  .at(ireg)->Fill( m_truthJet_pt    ->at(i) );
    	h_truthJet_eta   .at(ireg)->Fill( m_truthJet_eta   ->at(i) );
    	h_truthJet_phi   .at(ireg)->Fill( m_truthJet_phi   ->at(i) );
    	h_truthJet_E     .at(ireg)->Fill( m_truthJet_E     ->at(i) );
    	h_truthJet_M     .at(ireg)->Fill( m_truthJet_M     ->at(i) );
    	h_truthJet_rapid .at(ireg)->Fill( m_truthJet_rapid ->at(i) );
    	// truth jet kinematics
    	if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_tjet ) {
    	  h_truthJet_px   .at(ireg)->Fill( truthJet_p4.Px() );
    	  h_truthJet_py   .at(ireg)->Fill( truthJet_p4.Py() );
    	  h_truthJet_pz   .at(ireg)->Fill( truthJet_p4.Pz() );
    	  h_truthJet_Et   .at(ireg)->Fill( truthJet_p4.Et() );
    	  h_truthJet_Et_l .at(ireg)->Fill( truthJet_p4.Et() );
    	  h_truthJet_Et_m .at(ireg)->Fill( truthJet_p4.Et() );
    	  h_truthJet_Et_s .at(ireg)->Fill( truthJet_p4.Et() );
    	}
    	// leading truth jets
    	if ( m_numLeadTJets ) {
    	  if ( i < m_numLeadTJets ) {
    	    h_truthJetN_pt    .at(ireg).at(i) ->Fill( m_truthJet_pt    ->at(i) );
    	    h_truthJetN_pt_l  .at(ireg).at(i) ->Fill( m_truthJet_pt    ->at(i) );
    	    h_truthJetN_pt_m  .at(ireg).at(i) ->Fill( m_truthJet_pt    ->at(i) );
    	    h_truthJetN_pt_s  .at(ireg).at(i) ->Fill( m_truthJet_pt    ->at(i) );
    	    h_truthJetN_eta   .at(ireg).at(i) ->Fill( m_truthJet_eta   ->at(i) );
    	    h_truthJetN_phi   .at(ireg).at(i) ->Fill( m_truthJet_phi   ->at(i) );
    	    h_truthJetN_E     .at(ireg).at(i) ->Fill( m_truthJet_E     ->at(i) );
    	    h_truthJetN_M     .at(ireg).at(i) ->Fill( m_truthJet_M     ->at(i) );
    	    h_truthJetN_rapid .at(ireg).at(i) ->Fill( m_truthJet_rapid ->at(i) );
    	    if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_tjet ) {
    	      h_truthJetN_Et   .at(ireg).at(i) ->Fill( truthJet_p4.Et() );
    	      h_truthJetN_Et_l .at(ireg).at(i) ->Fill( truthJet_p4.Et() );
    	      h_truthJetN_Et_m .at(ireg).at(i) ->Fill( truthJet_p4.Et() );
    	      h_truthJetN_Et_s .at(ireg).at(i) ->Fill( truthJet_p4.Et() );
    	    }
    	  }
    	}

    	// truth jet energy (width)
    	if ( m_histoInfoSwitch->m_tjet_energy )
    	  h_truthJet_width      .at(ireg)->Fill( m_truthJet_width      ->at(i) );
    	// truth jet constituents
    	if ( m_histoInfoSwitch->m_tjet_constit ) {
    	  h_truthJet_girth     .at(ireg)->Fill( m_truthJet_girth      ->at(i) );
    	  h_truthJet_nConstit  .at(ireg)->Fill( m_truthJet_numConstit ->at(i) );
    	  h_truthJet_constitPt .at(ireg)->Fill( m_truthJet_constitPt  ->at(i) );
    	  int n_chrgConstit = 0;
    	  int n_visConstit  = 0;
    	  for ( int j = 0; j != m_truthJet_numConstit->at(i); ++j ) {
    	    h_truthJet_constit_dR     .at(ireg)->Fill( m_truthJet_constit_dR     ->at(i).at(j) );
    	    h_truthJet_constit_pVtx_r .at(ireg)->Fill( m_truthJet_constit_pVtx_r ->at(i).at(j) );
	    if ( !m_truthJet_constit_charge->at(i).at(j)         ) continue;
	    ++n_chrgConstit;
	    if (  m_truthJet_constit_pt->at(i).at(j) < m_tpPtThr ) continue;
	    ++n_visConstit;
    	  }
	  h_truthJet_nChrgConstit .at(ireg)->Fill( n_chrgConstit );
	  h_truthJet_nVisConstit  .at(ireg)->Fill( n_visConstit  );
    	}

	// truth jet dR-matched tracks
	if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_trk ) && !m_truth ) {
	  h_truthJet_trkCount .at(ireg)->Fill( m_truthJet_trkCount ->at(i) );
	  h_truthJet_trkPt    .at(ireg)->Fill( m_truthJet_trkPt    ->at(i) );
	  for ( int j = 0; j != m_truthJet_trkCount->at(i); ++j )
	    h_truthJet_trk_dR .at(ireg)->Fill( m_truthJet_trk_dR   ->at(i).at(j) );
	}
	// truth jet dR-matched truth particles
	if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_tp ) {
	  h_truthJet_tpCount .at(ireg)->Fill( m_truthJet_tpCount ->at(i) );
	  h_truthJet_tpPt    .at(ireg)->Fill( m_truthJet_tpPt    ->at(i) );
	  int n_chrg_tp = 0;
	  int n_vis_tp  = 0;
	  int n_dark_tp = 0;
	  int n_pid_tp  = 0;
	  for ( int j = 0; j != m_truthJet_tpCount->at(i); ++j ) {
	    h_truthJet_tp_dR .at(ireg)->Fill( m_truthJet_tp_dR ->at(i).at(j) );
	    int absPdgId = fabs( m_truthJet_tp_pdgId ->at(i).at(j) );
	    if (  absPdgId == 4900111 || absPdgId == 4900211 ) ++n_pid_tp;
	    if (  m_truthJet_tp_isDark   ->at(i).at(j)       ) ++n_dark_tp;
	    if ( !m_truthJet_tp_charge   ->at(i).at(j)       ) continue;
	    ++n_chrg_tp;
	    if ( !m_truthJet_tp_isStable ->at(i).at(j)       ) continue;
	    if (  m_truthJet_tp_pt ->at(i).at(j) < m_tpPtThr ) continue;
	    ++n_vis_tp; 
	  }
	  h_truthJet_chrgTpCount .at(ireg)->Fill( n_chrg_tp );
	  h_truthJet_visTpCount  .at(ireg)->Fill( n_vis_tp  );
	  h_truthJet_darkTpCount .at(ireg)->Fill( n_dark_tp );
	  h_truthJet_pidTpCount  .at(ireg)->Fill( n_pid_tp  );
	}

	// truth jet dR-matched secondary vertices
    	if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_vtx ) && !m_truth ) {
    	  h_truthJet_secVtxCount .at(ireg)->Fill( m_truthJet_secVtxCount ->at(i) );
    	  h_truthJet_secVtxPt    .at(ireg)->Fill( m_truthJet_secVtxPt    ->at(i) );
    	  for ( int j = 0; j != m_truthJet_secVtxCount->at(i); ++j )
    	    h_truthJet_secVtx_dR .at(ireg)->Fill( m_truthJet_secVtx_dR   ->at(i).at(j) );
	}
	// truth jet dR-matched truth vertices
	if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_tjet || m_histoInfoSwitch->m_match_tjet_tvtx ) {
    	  h_truthJet_truthVtxCount .at(ireg)->Fill( m_truthJet_truthVtxCount ->at(i) );
    	  h_truthJet_truthVtxPt    .at(ireg)->Fill( m_truthJet_truthVtxPt    ->at(i) );
	  int n_pid_tv  = 0;
	  int n_disp_tv = 0;
    	  for ( int j = 0; j != m_truthJet_truthVtxCount->at(i); ++j ) {
    	    h_truthJet_truthVtx_dR   .at(ireg)->Fill( m_truthJet_truthVtx_dR   ->at(i).at(j) );
	    h_truthJet_truthVtx_r    .at(ireg)->Fill( m_truthJet_truthVtx_r    ->at(i).at(j) );
	    h_truthJet_truthVtx_mass .at(ireg)->Fill( m_truthJet_truthVtx_mass ->at(i).at(j) );
	    if ( m_truthJet_truthVtx_llp ->at(i).at(j) == "DarkPion" ) ++n_pid_tv;
	    if ( m_truthJet_truthVtx_r   ->at(i).at(j) > m_tvRThr    ) ++n_disp_tv;
	  }
	  h_truthJet_pidTruthVtxCount  .at(ireg)->Fill( n_pid_tv  );
	  h_truthJet_dispTruthVtxCount .at(ireg)->Fill( n_disp_tv );
    	}
	
      } // end loop over truth jets
      
    } // end truth jet switch


    // ----------------- //
    // --- DARK JETS --- //
    // ----------------- //
    if ( m_histoInfoSwitch->m_djets && m_mc ) {
      h_darkJet_n .at(ireg)->Fill( m_darkJet_n );

      // loop over dark jets
      for ( int i = 0; i != m_darkJet_n; ++i ) {

    	TLorentzVector darkJet_p4;
    	darkJet_p4.SetPtEtaPhiM( m_darkJet_pt->at(i), m_darkJet_eta->at(i), m_darkJet_phi->at(i), m_darkJet_M->at(i) );
	
    	h_darkJet_pt    .at(ireg)->Fill( m_darkJet_pt    ->at(i) );
    	h_darkJet_pt_l  .at(ireg)->Fill( m_darkJet_pt    ->at(i) );
    	h_darkJet_pt_m  .at(ireg)->Fill( m_darkJet_pt    ->at(i) );
    	h_darkJet_pt_s  .at(ireg)->Fill( m_darkJet_pt    ->at(i) );
    	h_darkJet_eta   .at(ireg)->Fill( m_darkJet_eta   ->at(i) );
    	h_darkJet_phi   .at(ireg)->Fill( m_darkJet_phi   ->at(i) );
    	h_darkJet_E     .at(ireg)->Fill( m_darkJet_E     ->at(i) );
    	h_darkJet_M     .at(ireg)->Fill( m_darkJet_M     ->at(i) );
    	h_darkJet_rapid .at(ireg)->Fill( m_darkJet_rapid ->at(i) );
    	// dark jet kinematics
    	if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_djet ) {
    	  h_darkJet_px   .at(ireg)->Fill( darkJet_p4.Px() );
    	  h_darkJet_py   .at(ireg)->Fill( darkJet_p4.Py() );
    	  h_darkJet_pz   .at(ireg)->Fill( darkJet_p4.Pz() );
    	  h_darkJet_Et   .at(ireg)->Fill( darkJet_p4.Et() );
    	  h_darkJet_Et_l .at(ireg)->Fill( darkJet_p4.Et() );
    	  h_darkJet_Et_m .at(ireg)->Fill( darkJet_p4.Et() );
    	  h_darkJet_Et_s .at(ireg)->Fill( darkJet_p4.Et() );
    	}
    	// leading dark jets
    	if ( m_numLeadDJets ) {
    	  if ( i < m_numLeadDJets ) {
    	    h_darkJetN_pt    .at(ireg).at(i) ->Fill( m_darkJet_pt    ->at(i) );
    	    h_darkJetN_pt_l  .at(ireg).at(i) ->Fill( m_darkJet_pt    ->at(i) );
    	    h_darkJetN_pt_m  .at(ireg).at(i) ->Fill( m_darkJet_pt    ->at(i) );
    	    h_darkJetN_pt_s  .at(ireg).at(i) ->Fill( m_darkJet_pt    ->at(i) );
    	    h_darkJetN_eta   .at(ireg).at(i) ->Fill( m_darkJet_eta   ->at(i) );
    	    h_darkJetN_phi   .at(ireg).at(i) ->Fill( m_darkJet_phi   ->at(i) );
    	    h_darkJetN_E     .at(ireg).at(i) ->Fill( m_darkJet_E     ->at(i) );
    	    h_darkJetN_M     .at(ireg).at(i) ->Fill( m_darkJet_M     ->at(i) );
    	    h_darkJetN_rapid .at(ireg).at(i) ->Fill( m_darkJet_rapid ->at(i) );
    	    if ( m_histoInfoSwitch->m_kinematics || m_histoInfoSwitch->m_kinematics_djet ) {
    	      h_darkJetN_Et   .at(ireg).at(i) ->Fill( darkJet_p4.Et() );
    	      h_darkJetN_Et_l .at(ireg).at(i) ->Fill( darkJet_p4.Et() );
    	      h_darkJetN_Et_m .at(ireg).at(i) ->Fill( darkJet_p4.Et() );
    	      h_darkJetN_Et_s .at(ireg).at(i) ->Fill( darkJet_p4.Et() );
    	    }
    	  }
    	}

    	// dark jet energy (width)
    	if ( m_histoInfoSwitch->m_djet_energy )
    	  h_darkJet_width      .at(ireg)->Fill( m_darkJet_width      ->at(i) );
    	// dark jet constituents
    	if ( m_histoInfoSwitch->m_djet_constit ) {
    	  h_darkJet_girth     .at(ireg)->Fill( m_darkJet_girth      ->at(i) );
    	  h_darkJet_nConstit  .at(ireg)->Fill( m_darkJet_numConstit ->at(i) );
    	  h_darkJet_constitPt .at(ireg)->Fill( m_darkJet_constitPt  ->at(i) );
    	  int n_chrgConstit = 0;
    	  int n_visConstit  = 0;
    	  for ( int j = 0; j != m_darkJet_numConstit->at(i); ++j ) {
    	    h_darkJet_constit_dR     .at(ireg)->Fill( m_darkJet_constit_dR     ->at(i).at(j) );
    	    h_darkJet_constit_dVtx_r .at(ireg)->Fill( m_darkJet_constit_dVtx_r ->at(i).at(j) );
	    if ( !m_darkJet_constit_charge->at(i).at(j) ) continue;
	    ++n_chrgConstit;
	    if (  m_darkJet_constit_pt->at(i).at(j) < m_tpPtThr ) continue;
	    ++n_visConstit;
    	  }
	  h_darkJet_nChrgConstit .at(ireg)->Fill( n_chrgConstit );
	  h_darkJet_nVisConstit  .at(ireg)->Fill( n_visConstit  );
    	}

	// dark jet dR-matched tracks
	if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_trk ) && !m_truth ) {
	  h_darkJet_trkCount .at(ireg)->Fill( m_darkJet_trkCount ->at(i) );
	  h_darkJet_trkPt    .at(ireg)->Fill( m_darkJet_trkPt    ->at(i) );
	  for ( int j = 0; j != m_darkJet_trkCount->at(i); ++j )
	    h_darkJet_trk_dR .at(ireg)->Fill( m_darkJet_trk_dR   ->at(i).at(j) );
	}
	// dark jet dR-matched truth particles
	if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_tp ) {
	  h_darkJet_tpCount .at(ireg)->Fill( m_darkJet_tpCount ->at(i) );
	  h_darkJet_tpPt    .at(ireg)->Fill( m_darkJet_tpPt    ->at(i) );
	  int n_chrg_tp = 0;
	  int n_vis_tp  = 0;
	  int n_dark_tp = 0;
	  int n_pid_tp  = 0;
	  for ( int j = 0; j != m_darkJet_tpCount->at(i); ++j ) {
	    h_darkJet_tp_dR .at(ireg)->Fill( m_darkJet_tp_dR ->at(i).at(j) );
	    int absPdgId = fabs( m_darkJet_tp_pdgId ->at(i).at(j) );
	    if (  absPdgId == 4900111 || absPdgId == 4900211 ) ++n_pid_tp;
	    if (  m_darkJet_tp_isDark   ->at(i).at(j)       ) ++n_dark_tp;
	    if ( !m_darkJet_tp_charge   ->at(i).at(j)       ) continue;
	    ++n_chrg_tp;
	    if ( !m_darkJet_tp_isStable ->at(i).at(j)       ) continue;
	    if (  m_darkJet_tp_pt ->at(i).at(j) < m_tpPtThr ) continue;
	    ++n_vis_tp; 
	  }
	  h_darkJet_chrgTpCount .at(ireg)->Fill( n_chrg_tp );
	  h_darkJet_visTpCount  .at(ireg)->Fill( n_vis_tp  );
	  h_darkJet_darkTpCount .at(ireg)->Fill( n_dark_tp );
	  h_darkJet_pidTpCount  .at(ireg)->Fill( n_pid_tp  );
	}

	// dark jet dR-matched secondary vertices
    	if ( ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_vtx ) && !m_truth ) {
    	  h_darkJet_secVtxCount .at(ireg)->Fill( m_darkJet_secVtxCount ->at(i) );
    	  h_darkJet_secVtxPt    .at(ireg)->Fill( m_darkJet_secVtxPt    ->at(i) );
    	  for ( int j = 0; j != m_darkJet_secVtxCount->at(i); ++j )
    	    h_darkJet_secVtx_dR .at(ireg)->Fill( m_darkJet_secVtx_dR   ->at(i).at(j) );
	}
	// dark jet dR-matched truth vertices
	if ( m_histoInfoSwitch->m_match || m_histoInfoSwitch->m_match_djet || m_histoInfoSwitch->m_match_djet_tvtx ) {
    	  h_darkJet_truthVtxCount .at(ireg)->Fill( m_darkJet_truthVtxCount ->at(i) );
    	  h_darkJet_truthVtxPt    .at(ireg)->Fill( m_darkJet_truthVtxPt    ->at(i) );
	  int n_pid_tv  = 0;
	  int n_disp_tv = 0;
    	  for ( int j = 0; j != m_darkJet_truthVtxCount->at(i); ++j ) {
    	    h_darkJet_truthVtx_dR   .at(ireg)->Fill( m_darkJet_truthVtx_dR   ->at(i).at(j) );
	    h_darkJet_truthVtx_r    .at(ireg)->Fill( m_darkJet_truthVtx_r    ->at(i).at(j) );
	    h_darkJet_truthVtx_mass .at(ireg)->Fill( m_darkJet_truthVtx_mass ->at(i).at(j) );
	    if ( m_darkJet_truthVtx_llp ->at(i).at(j) == "DarkPion" ) ++n_pid_tv;
	    if ( m_darkJet_truthVtx_r   ->at(i).at(j) > m_tvRThr    ) ++n_disp_tv;
	  }
	  h_darkJet_pidTruthVtxCount  .at(ireg)->Fill( n_pid_tv  );
	  h_darkJet_dispTruthVtxCount .at(ireg)->Fill( n_disp_tv );
    	}
	
      } // end loop over dark jets
      
    } // end dark jet switch


    // -------------- //
    // --- TRACKS --- //
    // -------------- //


    // ----------------------- //
    // --- TRUTH PARTICLES --- //
    // ----------------------- //
    if ( m_histoInfoSwitch->m_tps && m_mc ) {
      h_tp_n .at(ireg)->Fill( m_tp_n );

      int    n_charged    = 0;
      int    n_visible    = 0;
      int    n_dark       = 0;
      double sumPt        = 0;
      double sumPtCharged = 0;
      double sumPtVisible = 0;
      double sumPtDark    = 0;

      int    n_Xd      = 0;
      int    n_qd      = 0;
      int    n_pid     = 0;
      int    n_rhod    = 0;
      double sumPtXd   = 0;
      double sumPtQd   = 0;
      double sumPtPid  = 0;
      double sumPtRhod = 0;
      
      // loop over truth particles
      for ( int i = 0; i != m_tp_n; ++i ) {
	h_tp_pt  .at(ireg)->Fill( m_tp_pt  ->at(i) );
	h_tp_eta .at(ireg)->Fill( m_tp_eta ->at(i) );
	h_tp_phi .at(ireg)->Fill( m_tp_phi ->at(i) );
	h_tp_E   .at(ireg)->Fill( m_tp_E   ->at(i) );
	h_tp_M   .at(ireg)->Fill( m_tp_M   ->at(i) );

	sumPt += m_tp_pt ->at(i);
	if ( m_tp_charge ->at(i) ) {
	  ++n_charged; sumPtCharged += m_tp_pt ->at(i);
	  if ( m_tp_isStable ->at(i) && m_tp_pt ->at(i) > m_tpPtThr )
	    { ++n_visible; sumPtVisible += m_tp_pt ->at(i); }
	}

	// skip non-dark particles for now...
	if ( !m_tp_isDark ->at(i) ) continue;
	++n_dark; sumPtDark += m_tp_pt ->at(i);

	// dark truth particles
	if ( m_histoInfoSwitch->m_tps_xd  || m_histoInfoSwitch->m_tps_qd ||
	     m_histoInfoSwitch->m_tps_pid || m_histoInfoSwitch->m_tps_rhod ) {
	  // dark scalar mediator (Xd) truth particles
	  if ( fabs( m_tp_pdgId ->at(i) ) == 4900001 && m_tp_status ->at(i) == 62 ) {
	    if ( m_histoInfoSwitch->m_tps_xd ) {
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
	      //if ( m_tp_hasPVtx ) // --> CHECK W/ + W/O
	      h_Xd_prodVtx_r    .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	      //if ( m_tp_hasDVtx )
	      h_Xd_decayVtx_r   .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	      sumPtXd += m_tp_pt ->at(i);
	    }
	  }
	  // dark quark (qd) truth particles
	  else if ( fabs( m_tp_pdgId ->at(i) ) == 4900101 && m_tp_status ->at(i) == 71 ) {
	    if ( m_histoInfoSwitch->m_tps_qd ) {
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
	      //if ( m_tp_hasPVtx ) // --> CHECK W/ + W/O
	      h_qd_prodVtx_r    .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	      //if ( m_tp_hasDVtx )
	      h_qd_decayVtx_r   .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	      sumPtQd += m_tp_pt ->at(i);
	    }
	  }
	  // dark pion (pid) truth particles
	  else if ( fabs( m_tp_pdgId ->at(i) ) == 4900111 || fabs( m_tp_pdgId ->at(i) ) == 4900211 ) {
	    if ( m_histoInfoSwitch->m_tps_pid ) {
	      ++n_pid;
	      h_pid_pt             .at(ireg)->Fill( m_tp_pt                 ->at(i) );
	      h_pid_eta            .at(ireg)->Fill( m_tp_eta                ->at(i) );
	      h_pid_phi            .at(ireg)->Fill( m_tp_phi                ->at(i) );
	      h_pid_E              .at(ireg)->Fill( m_tp_E                  ->at(i) );
	      h_pid_M              .at(ireg)->Fill( m_tp_M                  ->at(i) );
	      h_pid_charge         .at(ireg)->Fill( m_tp_charge             ->at(i) );
	      h_pid_nParents       .at(ireg)->Fill( m_tp_nParents           ->at(i) );
	      h_pid_nChildren      .at(ireg)->Fill( m_tp_nChildren          ->at(i) );
	      for ( int j = 0; j != m_tp_nParents->at(i); ++j ) {
		h_pid_parentPdgId  .at(ireg)->Fill( fabs( m_tp_parent_pdgId ->at(i).at(j) ) );
		h_pid_parentStatus .at(ireg)->Fill( m_tp_parent_status      ->at(i).at(j) );
	      }
	      for ( int j = 0; j != m_tp_nChildren->at(i); ++j ) {
		h_pid_childPdgId   .at(ireg)->Fill( fabs( m_tp_child_pdgId  ->at(i).at(j) ) );
		h_pid_childStatus  .at(ireg)->Fill( m_tp_child_status       ->at(i).at(j) );
	      }
	      //if ( m_tp_hasPVtx ) // --> CHECK W/ + W/O
	      h_pid_prodVtx_r    .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	      //if ( m_tp_hasDVtx )
	      h_pid_decayVtx_r   .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	      sumPtPid += m_tp_pt ->at(i);
	    }
	  }
	  // dark rho (rhod) truth particles
	  else if ( fabs( m_tp_pdgId ->at(i) ) == 4900113 || fabs( m_tp_pdgId ->at(i) ) == 4900213 ) {
	    if ( m_histoInfoSwitch->m_tps_rhod ) {
	      ++n_rhod;
	      h_rhod_pt             .at(ireg)->Fill( m_tp_pt                 ->at(i) );
	      h_rhod_eta            .at(ireg)->Fill( m_tp_eta                ->at(i) );
	      h_rhod_phi            .at(ireg)->Fill( m_tp_phi                ->at(i) );
	      h_rhod_E              .at(ireg)->Fill( m_tp_E                  ->at(i) );
	      h_rhod_M              .at(ireg)->Fill( m_tp_M                  ->at(i) );
	      h_rhod_charge         .at(ireg)->Fill( m_tp_charge             ->at(i) );
	      h_rhod_nParents       .at(ireg)->Fill( m_tp_nParents           ->at(i) );
	      h_rhod_nChildren      .at(ireg)->Fill( m_tp_nChildren          ->at(i) );
	      for ( int j = 0; j != m_tp_nParents->at(i); ++j ) {
		h_rhod_parentPdgId  .at(ireg)->Fill( fabs( m_tp_parent_pdgId ->at(i).at(j) ) );
		h_rhod_parentStatus .at(ireg)->Fill( m_tp_parent_status      ->at(i).at(j) );
	      }
	      for ( int j = 0; j != m_tp_nChildren->at(i); ++j ) {
		h_rhod_childPdgId   .at(ireg)->Fill( fabs( m_tp_child_pdgId  ->at(i).at(j) ) );
		h_rhod_childStatus  .at(ireg)->Fill( m_tp_child_status       ->at(i).at(j) );
	      }
	      //if ( m_tp_hasPVtx ) // --> CHECK W/ + W/O
	      h_rhod_prodVtx_r    .at(ireg)->Fill( m_tp_pVtx_r             ->at(i) );
	      //if ( m_tp_hasDVtx )
	      h_rhod_decayVtx_r   .at(ireg)->Fill( m_tp_dVtx_r             ->at(i) );
	      sumPtRhod += m_tp_pt ->at(i);
	    }
	  }
	}	

      } // end loop over truth particles

      h_tp_nCharged     .at(ireg)->Fill( n_charged    );
      h_tp_nVisible     .at(ireg)->Fill( n_visible    );
      h_tp_nDark        .at(ireg)->Fill( n_dark       );
      h_tp_sumPt        .at(ireg)->Fill( sumPt        );
      h_tp_chargedSumPt .at(ireg)->Fill( sumPtCharged );
      h_tp_visibleSumPt .at(ireg)->Fill( sumPtVisible );
      h_tp_darkSumPt    .at(ireg)->Fill( sumPtDark    );
      h_Xd_n            .at(ireg)->Fill( n_Xd         );
      h_qd_n            .at(ireg)->Fill( n_qd         );
      h_pid_n           .at(ireg)->Fill( n_pid        );
      h_rhod_n          .at(ireg)->Fill( n_rhod       );
      h_Xd_sumPt        .at(ireg)->Fill( sumPtXd      );
      h_qd_sumPt        .at(ireg)->Fill( sumPtQd      );
      h_pid_sumPt       .at(ireg)->Fill( sumPtPid     );
      h_rhod_sumPt      .at(ireg)->Fill( sumPtRhod    );
      
    } // end truth particle switch


    // -------------------------- //
    // --- SECONDARY VERTICES --- //
    // -------------------------- //
    if ( m_histoInfoSwitch->m_verts && !m_truth ) {
      h_secVtx_n .at(ireg)->Fill( m_secVtx_n );

      // map of number of Ntrk vertices
      std::map<int, int> nNtrkVerts;
      if ( m_numVtxTrks ) {
	for ( int k = 1; k != m_numVtxTrks; ++k ) {
	  int ntrk = k + 1;
	  nNtrkVerts[ntrk] = 0;
	}
      }

      // loop over secondary vertices
      for ( int i = 0; i != m_secVtx_n; ++i ) {
	h_secVtx_x               .at(ireg)->Fill( m_secVtx_x             ->at(i) );
	h_secVtx_y               .at(ireg)->Fill( m_secVtx_y             ->at(i) );
	h_secVtx_z               .at(ireg)->Fill( m_secVtx_z             ->at(i) );
	h_secVtx_r               .at(ireg)->Fill( m_secVtx_r             ->at(i) );
	h_secVtx_r_l             .at(ireg)->Fill( m_secVtx_r             ->at(i) );
	h_secVtx_r_s             .at(ireg)->Fill( m_secVtx_r             ->at(i) );
	h_secVtx_pt              .at(ireg)->Fill( m_secVtx_pt            ->at(i) );
	h_secVtx_eta             .at(ireg)->Fill( m_secVtx_eta           ->at(i) );
	h_secVtx_phi             .at(ireg)->Fill( m_secVtx_phi           ->at(i) );
	h_secVtx_mass            .at(ireg)->Fill( m_secVtx_mass          ->at(i) );
	h_secVtx_mass_l          .at(ireg)->Fill( m_secVtx_mass          ->at(i) );
	h_secVtx_mass_s          .at(ireg)->Fill( m_secVtx_mass          ->at(i) );
	h_secVtx_mass_nonAssoc   .at(ireg)->Fill( m_secVtx_mass_nonAssoc ->at(i) );
	h_secVtx_mass_nonAssoc_l .at(ireg)->Fill( m_secVtx_mass_nonAssoc ->at(i) );
	h_secVtx_mass_nonAssoc_s .at(ireg)->Fill( m_secVtx_mass_nonAssoc ->at(i) );
	h_secVtx_chi2            .at(ireg)->Fill( m_secVtx_chi2          ->at(i) );
	h_secVtx_direction       .at(ireg)->Fill( m_secVtx_direction     ->at(i) );
	h_secVtx_charge          .at(ireg)->Fill( m_secVtx_charge        ->at(i) );
	h_secVtx_Ht              .at(ireg)->Fill( m_secVtx_Ht            ->at(i) );
	h_secVtx_minOpAng        .at(ireg)->Fill( m_secVtx_minOpAng      ->at(i) );
	h_secVtx_maxOpAng        .at(ireg)->Fill( m_secVtx_maxOpAng      ->at(i) );
	h_secVtx_mind0           .at(ireg)->Fill( m_secVtx_mind0         ->at(i) );
	h_secVtx_maxd0           .at(ireg)->Fill( m_secVtx_maxd0         ->at(i) );
	for ( size_t j = 0; j != m_secVtx_twoTrkMass->at(i).size(); ++j ) {
	  h_secVtx_twoTrkMass    .at(ireg)->Fill( m_secVtx_twoTrkMass    ->at(i).at(j) );
	  h_secVtx_twoTrkMass_l  .at(ireg)->Fill( m_secVtx_twoTrkMass    ->at(i).at(j) );
	  h_secVtx_twoTrkMass_s  .at(ireg)->Fill( m_secVtx_twoTrkMass    ->at(i).at(j) );
	}
	h_secVtx_ntrk            .at(ireg)->Fill( m_secVtx_ntrk          ->at(i) );
	h_secVtx_ntrk_sel        .at(ireg)->Fill( m_secVtx_ntrk_sel      ->at(i) );
	h_secVtx_ntrk_assoc      .at(ireg)->Fill( m_secVtx_ntrk_assoc    ->at(i) );

	// n-track vertices
	if ( m_numVtxTrks ) {
	  int ntrk = m_secVtx_ntrk ->at(i);
	  if ( ntrk <= m_numVtxTrks ) {
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
	  }
	}
	// n-sel/non-assoc-track vertices

      } // end loop over secondary vertices

      // loop over nNtrkVerts map
      for ( const auto& nNtrkVtx : nNtrkVerts ) {
	int ntrk = nNtrkVtx.first;
	int nvtx = nNtrkVtx.second;
	h_secVtxNtrk_n .at(ireg).at(ntrk-2)->Fill( nvtx );
      }
	
    } // end secondary vertex switch


    // ---------------------- //
    // --- TRUTH VERTICES --- //
    // ---------------------- //
    if ( m_histoInfoSwitch->m_tverts && m_mc ) {
      h_truthVtx_n .at(ireg)->Fill( m_truthVtx_n );

      int n_truthVtxPid = 0;
      
      // loop over truth vertices
      for ( int i = 0; i != m_truthVtx_n; ++i ) {
	h_truthVtx_x     .at(ireg)->Fill( m_truthVtx_x     ->at(i) );
	h_truthVtx_y     .at(ireg)->Fill( m_truthVtx_y     ->at(i) );
	h_truthVtx_z     .at(ireg)->Fill( m_truthVtx_z     ->at(i) );
	h_truthVtx_r     .at(ireg)->Fill( m_truthVtx_r     ->at(i) );
	h_truthVtx_pt    .at(ireg)->Fill( m_truthVtx_pt    ->at(i) );
	h_truthVtx_eta   .at(ireg)->Fill( m_truthVtx_eta   ->at(i) );
	h_truthVtx_phi   .at(ireg)->Fill( m_truthVtx_phi   ->at(i) );
	h_truthVtx_mass  .at(ireg)->Fill( m_truthVtx_mass  ->at(i) );
	h_truthVtx_nOutP .at(ireg)->Fill( m_truthVtx_nOutP ->at(i) );
	
	// dark pion decay truth vertices
	if ( m_truthVtx_llp ->at(i) == "DarkPion" ) {
	  ++n_truthVtxPid;
	  h_truthVtxPid_x     .at(ireg)->Fill( m_truthVtx_x     ->at(i) );
	  h_truthVtxPid_y     .at(ireg)->Fill( m_truthVtx_y     ->at(i) );
	  h_truthVtxPid_z     .at(ireg)->Fill( m_truthVtx_z     ->at(i) );
	  h_truthVtxPid_r     .at(ireg)->Fill( m_truthVtx_r     ->at(i) );
	  h_truthVtxPid_pt    .at(ireg)->Fill( m_truthVtx_pt    ->at(i) );
	  h_truthVtxPid_eta   .at(ireg)->Fill( m_truthVtx_eta   ->at(i) );
	  h_truthVtxPid_phi   .at(ireg)->Fill( m_truthVtx_phi   ->at(i) );
	  h_truthVtxPid_mass  .at(ireg)->Fill( m_truthVtx_mass  ->at(i) );
	  h_truthVtxPid_nOutP .at(ireg)->Fill( m_truthVtx_nOutP ->at(i) );
	}
	
      } // end loop over truth vertices
      
      h_truthVtxPid_n .at(ireg)->Fill( n_truthVtxPid );
      
    } // end truth vertex switch


  } // end loop over regions

  return StatusCode::SUCCESS;
}
