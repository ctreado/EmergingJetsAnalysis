#include <map>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/EJsHistogramManager.h"


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

  if ( m_debug ) Info( "EJsHistogramManager()", "setting up" );

  // event branches
  m_runNumber           = 0;
  m_eventNumber         = 0;
  m_lumiBlock           = 0;
  m_bcid                = 0;
  m_mcEventNumber       = 0;
  m_mcChannelNumber     = 0;
  m_mcEventWeight       = 0;
  m_weight_pileup       = 0;
  m_npv                 = 0;
  m_actualMu            = 0;
  m_averageMu           = 0;
  m_corrActualMu        = 0;
  m_corrAverageMu       = 0;
  m_corrScaleActualMu   = 0;
  m_corrScaleAverageMu  = 0;
  m_randRunNr           = 0;
  m_randLumiBlockNr     = 0;
  m_search              = 0;
  m_valid               = 0;
  m_njetHt              = 0;
  m_search_njet         = 0;
  m_search_jetPt        = 0;
  m_search_jetEta       = 0;
  m_search_njetHt       = 0;
  m_search_other        = 0;
  m_valid_other         = 0;
  m_njetHt_other        = 0;
  m_search_njet_other   = 0;
  m_search_jetPt_other  = 0;
  m_search_jetEta_other = 0;
  m_search_njetHt_other = 0;
  m_pv_x                = 0;
  m_pv_y                = 0;
  m_pv_z                = 0;
  m_pv_r                = 0;
  m_pv_phi              = 0;
  m_pv_ntrk             = 0;
  m_pv_location         = 0;

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
  m_trk_n = 0;

  // secondary vertex branches
  m_secVtx_n = 0;
  m_secVtx_jetMatched        = new std::vector<uint8_t>;
  m_secVtx_jetMatch_ID       = new std::vector<int>;
  m_secVtx_jetMatch_index    = new std::vector<int>;
  m_secVtx_jetMatch_dR       = new std::vector<float>;
  m_secVtx_jetOthMatched     = new std::vector<uint8_t>;
  m_secVtx_jetOthMatch_ID    = new std::vector<int>;
  m_secVtx_jetOthMatch_index = new std::vector<int>;
  m_secVtx_jetOthMatch_dR    = new std::vector<float>;
  
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

  // secondary vertex branches
  delete m_secVtx_jetMatched;
  delete m_secVtx_jetMatch_ID;
  delete m_secVtx_jetMatch_index;
  delete m_secVtx_jetMatch_dR;
  delete m_secVtx_jetOthMatched;
  delete m_secVtx_jetOthMatch_ID;
  delete m_secVtx_jetOthMatch_index;
  delete m_secVtx_jetOthMatch_dR;
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

  // search / validation region selections
  connectBranch<uint8_t>  ( tree, "isSignal_"           + m_jetStr,    &m_search              );
  connectBranch<uint8_t>  ( tree, "isValid_"            + m_jetStr,    &m_valid               );
  connectBranch<float>    ( tree, "NJetHt_"             + m_jetStr,    &m_njetHt              );
  connectBranch<uint8_t>  ( tree, "passesSignalNJet_"   + m_jetStr,    &m_search_njet         );
  connectBranch<uint8_t>  ( tree, "passesSignalJetPt_"  + m_jetStr,    &m_search_jetPt        );
  connectBranch<uint8_t>  ( tree, "passesSignalJetEta_" + m_jetStr,    &m_search_jetEta       );
  connectBranch<uint8_t>  ( tree, "passesSignalNJetHt_" + m_jetStr,    &m_search_njetHt       );
  // signal validation region selections using other jet type
  connectBranch<uint8_t>  ( tree, "isSignal_"           + m_jetStrOth, &m_search_other        );
  connectBranch<uint8_t>  ( tree, "isValid_"            + m_jetStrOth, &m_valid_other         );
  connectBranch<float>    ( tree, "NJetHt_"             + m_jetStrOth, &m_njetHt_other        );
  connectBranch<uint8_t>  ( tree, "passesSignalNJet_"   + m_jetStrOth, &m_search_njet_other   );
  connectBranch<uint8_t>  ( tree, "passesSignalJetPt_"  + m_jetStrOth, &m_search_jetPt_other  );
  connectBranch<uint8_t>  ( tree, "passesSignalJetEta_" + m_jetStrOth, &m_search_jetEta_other );
  connectBranch<uint8_t>  ( tree, "passesSignalNJetHt_" + m_jetStrOth, &m_search_njetHt_other );

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

  connectBranch<uint8_t> ( name, tree, "is" + m_jetStr    + "JetMatched", &m_secVtx_jetMatched        );
  connectBranch<int>     ( name, tree, m_jetStr + "JetMatch_ID",          &m_secVtx_jetMatch_ID       );
  connectBranch<int>     ( name, tree, m_jetStr + "JetMatch_index",       &m_secVtx_jetMatch_index    );
  connectBranch<float>   ( name, tree, m_jetStr + "JetMatch_dR",          &m_secVtx_jetMatch_dR       );
  connectBranch<uint8_t> ( name, tree, "is" + m_jetStrOth + "JetMatched", &m_secVtx_jetOthMatched     );
  connectBranch<int>     ( name, tree, m_jetStrOth + "JetMatch_ID",       &m_secVtx_jetOthMatch_ID    );
  connectBranch<int>     ( name, tree, m_jetStrOth + "JetMatch_index",    &m_secVtx_jetOthMatch_index );
  connectBranch<float>   ( name, tree, m_jetStrOth + "JetMatch_dR",       &m_secVtx_jetOthMatch_dR    );

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: connectTruthVerts ( TTree* tree, const std::string& truthVtxName )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectTruthVerts()", "connecting truth vertex branches" );
  
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
    h_njetHt    .push_back( book( name, "NJetHt",    "Leading N-" + m_jetStr    + "-jet scalar sum-p_{T} [GeV]", 100, njetht_xmin, 3500 ) );
    h_njetOthHt .push_back( book( name, "NJetOthHt", "Leading N-" + m_jetStrOth + "-jet scalar sum-p_{T} [GeV]", 100, njetht_xmin, 3500 ) );

    
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


    // --- SECONDARY VERTICES -- //
    // vertices: basics / kinematics
    h_DV_n .push_back( book( name, "DV_n", "n secondary vertices", 15, 0, 15 ) );
    // vertices nearby to (lead) jets
    h_byJetDV_n        .push_back( book( name, "byJetDV_n",        "n DVs by "        + m_jetStr    + " jets", 12, 0, 12 ) );
    h_byLeadJetDV_n    .push_back( book( name, "byLeadJetDV_n",    "n DVs by N-lead " + m_jetStr    + " jets", 10, 0, 10 ) );


    // --- ABCD HISTOS --- //
    if ( m_histoInfoSwitch->m_abcd ) {
      h_abcd_nDV_njetHt
	.push_back( book( name, "ABCD_nDV_NJetHt", "Leading N " + m_jetStr + " jet H_{T} [GeV]", 100, njetht_xmin, 3000,
			  "n DVs", 16, -1, 15 ) );
       h_abcd_nJetDV_njetHt
	.push_back( book( name, "ABCD_nByJetDV_NJetHt", "Leading N " + m_jetStr + " jet H_{T} [GeV]", 100, njetht_xmin, 3000,
			  "n DVs by " + m_jetStr + " jets", 13, -1, 12 ) );
       h_abcd_nLeadJetDV_njetHt
	.push_back( book( name, "ABCD_nByLeadJetDV_NJetHt", "Leading N " + m_jetStr + " jet H_{T} [GeV]", 100, njetht_xmin, 3000,
			  "n DVs by leading N " + m_jetStr + " jets", 11, -1, 10 ) );
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

  // check for abcd region event
  bool m_abcd_a = false;
  bool m_abcd_b = false;
  bool m_abcd_c = false;
  bool m_abcd_d = false;
  int m_nDV_nearJets     = 0; // for testing purposes...
  int m_nDV_nearLeadJets = 0; // --> this is what we really want (for now)
  for ( int i = 0; i != m_secVtx_n; ++i ) {
    // n DVs near jets
    if ( m_secVtx_jetMatched    ->at(i) )
      ++m_nDV_nearJets;
    // n DVs near lead jets
    if ( m_secVtx_jetMatched    ->at(i) && m_secVtx_jetMatch_index    ->at(i) < m_nJets )
      ++m_nDV_nearLeadJets;
  }
  if      ( ( m_njetHt >= m_ABCD_njetHt ) && ( m_nDV_nearLeadJets >= m_ABCD_nDV ) ) m_abcd_a = true;
  else if ( ( m_njetHt >= m_ABCD_njetHt ) && ( m_nDV_nearLeadJets <  m_ABCD_nDV ) ) m_abcd_b = true;
  else if ( ( m_njetHt <  m_ABCD_njetHt ) && ( m_nDV_nearLeadJets >= m_ABCD_nDV ) ) m_abcd_c = true;
  else if ( ( m_njetHt <  m_ABCD_njetHt ) && ( m_nDV_nearLeadJets <  m_ABCD_nDV ) ) m_abcd_d = true;

  // check for signal region event
  bool m_signal = false;
  if ( m_search && m_abcd_a ) m_signal = true;
    
  // loop over regions + fill histograms
  for ( size_t ireg = 0; ireg != regions.size(); ++ireg ) {
    const EJsHelper::Region region = regions.at(ireg);

    // skip events outside specified region
    if      ( region.type == EJsHelper::SEARCH     ) { if ( !m_search ) continue; }
    else if ( region.type == EJsHelper::VALIDATION ) { if ( !m_valid  ) continue; }
    else if ( region.type == EJsHelper::SIGNAL     ) { if ( !m_signal || ( !m_mc && !m_unblind ) ) continue; }
    // --> skip signal events in data until we unblind

    // --- ABCD PLANE TESTS --- //
    if ( m_histoInfoSwitch->m_abcd ) {
      h_abcd_nDV_njetHt              .at(ireg) ->Fill( m_njetHt,       m_secVtx_n,               weight );
      h_abcd_nJetDV_njetHt           .at(ireg) ->Fill( m_njetHt,       m_nDV_nearJets,           weight );
      h_abcd_nLeadJetDV_njetHt       .at(ireg) ->Fill( m_njetHt,       m_nDV_nearLeadJets,       weight );
    }

    if ( region.type == EJsHelper::SEARCH ) { if ( !m_mc && !m_unblind ) continue; }
    // --> skip remaining search events in data for now --> ...
    // ... maybe okay to look at search_minus_signal region, but not until signal region wholly finalized

    // ------------------ //
    // --- EVENT INFO --- //
    // ------------------ // 
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
    h_njetHt    .at(ireg) ->Fill( m_njetHt,       weight );
    h_njetOthHt .at(ireg) ->Fill( m_njetHt_other, weight );



    // ----------------- //
    // --- RECO JETS --- //
    // ----------------- //
    h_jet_n .at(ireg) ->Fill( m_jet_n );
    
    // loop over jets
    for ( int i = 0; i != m_jet_n; ++i ) {
      
      // get jet four-momentum
      TLorentzVector jet_p4;
      jet_p4.SetPtEtaPhiM( m_jet_pt->at(i), m_jet_eta->at(i), m_jet_phi->at(i), m_jet_M->at(i) );
      
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
      for ( int j = 0; j != nJetTrk; ++j ) {
	double dR = m_jet_trk_dR ->at(i).at(j);
	h_jet_trk_dR .at(ireg) ->Fill( dR, weight );
	h_jet_nTrk_vs_dR .at(ireg) ->Fill( dR, nJetTrk, weight );
      }
      
      // matched secondary vertices
      int nJetDV = m_jet_secVtx_n->at(i);
      h_jet_nDV .at(ireg) ->Fill( nJetDV, weight );
      // loop over matched secondary vertices
      for ( int j = 0; j != nJetDV; ++j ) {
	double dR = m_jet_secVtx_dR ->at(i).at(j);
	h_jet_DV_dR .at(ireg) ->Fill( dR, weight );
	h_jet_nDV_vs_dR .at(ireg) ->Fill( dR, nJetDV, weight );
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
    h_trk_n .at(ireg) ->Fill( m_trk_n );



    // -------------------------- //
    // --- SECONDARY VERTICES --- //
    // -------------------------- //
    h_DV_n             .at(ireg) ->Fill( m_secVtx_n,               weight );
    h_byJetDV_n        .at(ireg) ->Fill( m_nDV_nearJets,           weight );
    h_byLeadJetDV_n    .at(ireg) ->Fill( m_nDV_nearLeadJets,       weight );



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
      bool searchRegionEvent    = false;
      if ( m_search_njet       && m_search_jetPt       && m_search_jetEta       && m_search_njetHt       ) {
      	searchRegionEvent = true;
      	++m_nSearch       .at(ireg);
      }
      bool otherSearchRegionEvent = false;
      if ( m_search_njet_other && m_search_jetPt_other && m_search_jetEta_other && m_search_njetHt_other )
      	otherSearchRegionEvent = true;

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
      // TEST JVT

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


  // loop over regions (for ireg in regions)
    // // ----------------- //
    // // --- RECO JETS --- //
    // // ----------------- //
    // if ( m_histoInfoSwitch->m_jets && !m_truth ) {
    //   h_jet_n .at(ireg)->Fill( m_jet_n );

    //   // loop over jets
    //   for ( int i = 0; i != m_jet_n; ++i ) {

    // 	// ghost tracks
    // 	if ( m_histoInfoSwitch->m_jet_ghost || m_histoInfoSwitch->m_jet_ghostTrk ) {
    // 	  h_jet_ghostTrkCount .at(ireg)->Fill( m_jet_ghostTrkCount ->at(i) );
    // 	  h_jet_ghostTrkPt    .at(ireg)->Fill( m_jet_ghostTrkPt    ->at(i) );
    // 	  for ( int j = 0; j != m_jet_ghostTrkCount->at(i); ++ j ) {
    // 	    // calculate dR b/w ghost tracks + jet
    // 	    double eta = m_jet_ghostTrk_eta ->at(i).at(j);
    // 	    double phi = m_jet_ghostTrk_phi ->at(i).at(j);
    // 	    double dR  = EJsHelper::deltaR( m_jet_eta->at(i), eta, m_jet_phi->at(i), phi );
    // 	    h_jet_ghostTrk_dR .at(ireg)->Fill( dR );

    // 	    // // --> HOW TO ACCESS EXTRA MATCHED OBJECT INFO NOT EXPLICITLY SAVED AS ITS OWN BRANCH -->
    // 	    // int ghosttrack_id = m_jet_ghostTrk_ID ->at(i).at(j);
    // 	    // int ghosttrack_index = m_jet_ghostTrk_index ->at(i).at(j);
    // 	    // if ( ghosttrack_id != 0 ) // have to check ID is not zero -- ID=0 means ID is not set / corresponding object not saved to tree
    // 	    //   std::cout << m_jet_ghostTrk_eta ->at(i).at(j) << " " << m_trk_eta ->at(ghosttrack_index) << std::endl;
    // 	  }
    // 	}	
    //   } // end loop over jets
    // } // end jet switch

  
  

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
	int j = nTrigEvents.size() + i;
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
