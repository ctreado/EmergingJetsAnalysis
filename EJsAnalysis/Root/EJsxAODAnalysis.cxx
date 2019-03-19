#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <xAODEventInfo/EventInfo.h>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/EJsxAODAnalysis.h"

// needed to distribute algorithm to workers
ClassImp ( EJsxAODAnalysis )



EJsxAODAnalysis :: EJsxAODAnalysis () : Algorithm ( "EJsxAODAnalysis" )
{
  // code for base initialization of variables, e.g. initialize
  // all pointers to zero; note this method called on submission +
  // worker node, so only put most basic initialization here;
  // most initialization will go in histInitialize() and initialize()
}



EL::StatusCode EJsxAODAnalysis :: setupJob ( EL::Job& job )
{
  // code to set up job on submission object so it's ready to work
  // w/ alg, e.g. request D3PDReader service or add output files;
  // code here automatically activated/deactivated when alg
  // added/removed from job
  
  // initialize alg to use xAODRootAccess package
  job.useXAOD();
  xAOD::Init( "EJsxAODAnalysis" ).ignore(); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: histInitialize ()
{
  // everything that needs to be done at the beginning on each
  // worker node, e.g. create histos + output trees;
  // this method called before any input files connected
  
  ANA_CHECK( xAH::Algorithm::algInitialize() );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: fileExecute ()
{
  // everything that needs to be done exactly once for every
  // single file, e.g. collect list of all lumi-blocks processed

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: changeInput ( bool /*firstFile*/ )
{
  // everything that needs to be done when input files change,
  // e.g. resetting branch addresses on trees; not needed if
  // using D3PDReader or similar service...

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: initialize ()
{
  // everything that needs to be done after first input file
  // connected and before first event processed, e.g. create
  // additional histograms based on variables available in input files;
  // can also create all histograms + trees here, but note this method
  // doesn't get called if no events processed, so objects created
  // here won't be available in output if no input events

  ANA_MSG_INFO( "Initializing EJsxAODAnalysis..." );

  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();

  // to handle more than one jet collection
  std::string token;
  std::istringstream ss_jet_containers( m_inJetContainerName );
  while ( std::getline( ss_jet_containers, token, ' ' ) )
    m_inJetContainers.push_back( token );

  // check for input containers
  if ( m_inJetContainers.empty() ) {
    ANA_MSG_ERROR( "No input jet container(s) provided! Exiting." );
    return EL::StatusCode::FAILURE;
  }

  // to handle histogram bin labels for more than one jet collection
  std::istringstream ss_jet_bins( m_inJetBinName );
  while ( std::getline( ss_jet_bins, token, ' ' ) )
    m_inJetBins.push_back( token );
  // default to jet container names if bin names not set
  if ( m_inJetBins.empty() || m_inJetContainers.size() != m_inJetBins.size() ) {
    for ( size_t i = 0; i != m_inJetContainers.size(); ++i )
      m_inJetBins.push_back( m_inJetContainers.at(i) );
  }

  // parse input trigger lists
  std::string trig_token;
  std::istringstream ss_signal_trigs( m_signalTrigList );
  while ( std::getline( ss_signal_trigs, trig_token, ',' ) )
    m_signalTrigs.push_back( trig_token );
  std::istringstream ss_valid_trigs( m_validTrigList );
  while ( std::getline( ss_valid_trigs, trig_token, ',' ) )
    m_validTrigs.push_back( trig_token );
  std::istringstream ss_ctrl_trigs( m_ctrlTrigList );
  while ( std::getline( ss_ctrl_trigs, trig_token, ',' ) )
    m_ctrlTrigs.push_back( trig_token );

  
  // initialize cutflows
  if ( m_useCutFlow ) {
    
    // retrieve file in which cutflow hists are store
    TFile *file = wk()->getOutputFile( "cutflow" );
    
    // retrieve event cutflows
    m_cutflowHist  = (TH1D*)file->Get( "cutflow" );
    m_cutflowHistW = (TH1D*)file->Get( "cutflow_weighted" );

    // initialize new EJs cutflows
    m_cutflowSignalHist  = (TH1D*)m_cutflowHist  ->Clone( "cutflow_signal"           );
    m_cutflowSignalHistW = (TH1D*)m_cutflowHistW ->Clone( "cutflow_signal_weighted"  );
    m_cutflowValidHist   = (TH1D*)m_cutflowHist  ->Clone( "cutflow_valid"            );
    m_cutflowValidHistW  = (TH1D*)m_cutflowHistW ->Clone( "cutflow_valid_weighted"   );
    m_cutflowCtrlHist    = (TH1D*)m_cutflowHist  ->Clone( "cutflow_control"          );
    m_cutflowCtrlHistW   = (TH1D*)m_cutflowHistW ->Clone( "cutflow_control_weighted" );
    m_cutflowSignalHist  ->SetTitle( "cutflow_signal"          );
    m_cutflowSignalHistW ->SetTitle( "cutflow_signal_weighted" );
    m_cutflowValidHist   ->SetTitle( "cutflow_valid"           );
    m_cutflowValidHistW  ->SetTitle( "cutflow_valid_weighted"  );
    m_cutflowCtrlHist    ->SetTitle( "cutflow_ctrl"            );
    m_cutflowCtrlHistW   ->SetTitle( "cutflow_ctrl_weighted"   );

    m_cutflow_bin = m_cutflowHist->GetXaxis()->FindBin( ( m_name ).c_str() );
    
    m_cutflowHist  ->GetXaxis()->FindBin( ( m_name ).c_str() );
    m_cutflowHistW ->GetXaxis()->FindBin( ( m_name ).c_str() );
    
    for ( size_t i = 0; i != m_inJetContainers.size(); ++i ) {
      m_cutflowHist  ->GetXaxis()->FindBin( ( m_name + "Signal_" + m_inJetBins.at(i) ).c_str() );
      m_cutflowHistW ->GetXaxis()->FindBin( ( m_name + "Signal_" + m_inJetBins.at(i) ).c_str() );
      m_cutflowHist  ->GetXaxis()->FindBin( ( m_name + "Valid_"  + m_inJetBins.at(i) ).c_str() );
      m_cutflowHistW ->GetXaxis()->FindBin( ( m_name + "Valid_"  + m_inJetBins.at(i) ).c_str() );
      // m_cutflowHist  ->GetXaxis()->FindBin( ( m_name + "Ctrl_"   + m_inJetBins.at(i) ).c_str() );
      // m_cutflowHistW ->GetXaxis()->FindBin( ( m_name + "Ctrl_"   + m_inJetBins.at(i) ).c_str() );
      m_cutflowHist  ->GetXaxis()->FindBin( ( m_name + "SignalValid_" + m_inJetBins.at(i) ).c_str() );
      m_cutflowHistW ->GetXaxis()->FindBin( ( m_name + "SignalValid_" + m_inJetBins.at(i) ).c_str() );
    }

  }

  if ( m_outputAlgo.empty() ) {
    m_outputAlgo = m_inputAlgo + "_EJsxAODAna";
  }

  // initialize counters
  m_eventNumber         = 0;
  m_numPassEvents       = 0;
  m_numPassWeightEvents = 0;
  for ( size_t i = 0; i != m_inJetContainers.size(); ++i ) {
    m_numSignalEvents            .push_back(0);
    m_numValidEvents             .push_back(0);
    m_numCtrlEvents              .push_back(0);
    m_numSignalValidEvents       .push_back(0);

    m_numSignalWeightEvents      .push_back(0);
    m_numValidWeightEvents       .push_back(0);
    m_numCtrlWeightEvents        .push_back(0);
    m_numSignalValidWeightEvents .push_back(0);
  }

  m_isNominalCase       = true;
  m_isFirstJetContainer = false;
  

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: execute ()
{
  // everything that needs to be done on every single event,
  // e.g. read input variables, apply cuts, fill histos + trees;
  // here is where most of actual analysis will go...

  ANA_MSG_DEBUG( "Applying EJs Analysis Selection..." );

  // retrieve event info container
  const xAOD::EventInfo* eventInfo = 0;
  ANA_CHECK( HelperFunctions::retrieve( eventInfo, "EventInfo", m_event, m_store, msg() ) );

  // get MC event weight
  m_mcEventWeight = 1.0;
  if ( eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) )
    m_mcEventWeight = eventInfo->mcEventWeight();

  // get list of passing triggers
  if ( eventInfo->isAvailable<std::vector<std::string>>("passedTriggers") )
    m_passedTriggers = eventInfo->auxdataConst<std::vector<std::string>>("passedTriggers");


  // did any collection pass the cuts?
  bool pass = false;
  
  // if input comes from xAOD, or not running systematics...
  if ( m_inputAlgo.empty() ) {
    
    ANA_CHECK( executeSelection( eventInfo, "", pass ) );
    
  }
  // otherwise, get list of systematics to run over
  else {
    
    // get vector of string giving syst names of upstream algo from TStore
    std::vector<std::string>* systNames = 0;
    ANA_CHECK( HelperFunctions::retrieve( systNames, m_inputAlgo, 0, m_store, msg() ) );

    // did any (systematic) collection pass the cuts?
    bool passOne = false;
    auto vecOutContainerNames = std::make_unique<std::vector<std::string>>();

    // loop over systematics
    for ( const auto& systName : *systNames ) {
      m_isNominalCase = ( systName.empty() ) ? true : false; // check for nominal case

      ANA_CHECK( executeSelection( eventInfo, systName, passOne ) );
      
      // save string if passing selection
      if ( passOne ) vecOutContainerNames->push_back( systName );

      // the final decision - if at least one passes, keep going!
      pass = pass || passOne;
    }

    // save list of systs that should be considered downstream
    ANA_CHECK( m_store->record( std::move( vecOutContainerNames ), m_outputAlgo ) );
    
  }

  // look what we have in TStore
  if ( msgLvl( MSG::VERBOSE ) ) m_store->print();

  ++m_eventNumber;

  // skip events failing all cuts
  if ( !pass ) wk()->skipEvent();

  ++m_numPassEvents;
  m_numPassWeightEvents += m_mcEventWeight;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: postExecute ()
{
  // everything that need to be done after main event processing;
  // mainly used in implementing NTupleSvc

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: finalize ()
{
  // mirror image of initialize(); gets called after last event
  // processed on worker node; allows finishing up objects created
  // in initialize() before they're written to disk; only gets
  // called on worker nodes that processed input events

  if ( m_useCutFlow ) {
    ANA_MSG_INFO( "filling cutflows + writing to output" );

    unsigned j = m_cutflow_bin;
    m_cutflowHist  ->SetBinContent( j, m_numPassEvents       );
    m_cutflowHistW ->SetBinContent( j, m_numPassWeightEvents );
    ++j;
    for ( size_t i = 0; i != m_inJetContainers.size(); ++i ) {
      m_cutflowHist  ->SetBinContent( j, m_numSignalEvents            .at(i) );
      m_cutflowHistW ->SetBinContent( j, m_numSignalWeightEvents      .at(i) );
      ++j;
      m_cutflowHist  ->SetBinContent( j, m_numValidEvents             .at(i) );
      m_cutflowHistW ->SetBinContent( j, m_numValidWeightEvents       .at(i) );
      ++j;
      // m_cutflowHist  ->SetBinContent( j, m_numCtrlEvents              .at(i) );
      // m_cutflowHistW ->SetBinContent( j, m_numCtrlWeightEvents        .at(i) );
      // ++j;
      m_cutflowHist  ->SetBinContent( j, m_numSignalValidEvents       .at(i) );
      m_cutflowHistW ->SetBinContent( j, m_numSignalValidWeightEvents .at(i) );
      ++j;
    }
    m_cutflowHist  ->LabelsDeflate("X");
    m_cutflowHistW ->LabelsDeflate("X");

    // fill new cutflows with original cutflow info from previous algs...
    for ( size_t ibin = 1; ibin != m_cutflow_bin; ++ibin ) {
      m_cutflowSignalHist  ->SetBinContent( ibin, m_cutflowHist  ->GetBinContent(ibin) );
      m_cutflowSignalHistW ->SetBinContent( ibin, m_cutflowHistW ->GetBinContent(ibin) );
      m_cutflowValidHist   ->SetBinContent( ibin, m_cutflowHist  ->GetBinContent(ibin) );
      m_cutflowValidHistW  ->SetBinContent( ibin, m_cutflowHistW ->GetBinContent(ibin) );
      m_cutflowCtrlHist    ->SetBinContent( ibin, m_cutflowHist  ->GetBinContent(ibin) );
      m_cutflowCtrlHistW   ->SetBinContent( ibin, m_cutflowHistW ->GetBinContent(ibin) );
    }

    // write new cutflows to output file
    TFile *file = wk()->getOutputFile( "cutflow" );
    file->cd();
    m_cutflowSignalHist  ->LabelsDeflate("X");
    m_cutflowSignalHistW ->LabelsDeflate("X");
    m_cutflowValidHist   ->LabelsDeflate("X");
    m_cutflowValidHistW  ->LabelsDeflate("X");
    // m_cutflowCtrlHist    ->LabelsDeflate("X");
    // m_cutflowCtrlHistW   ->LabelsDeflate("X");
    m_cutflowSignalHist  ->Write();
    m_cutflowSignalHistW ->Write();
    m_cutflowValidHist   ->Write();
    m_cutflowValidHistW  ->Write();
    // m_cutflowCtrlHist    ->Write();
    // m_cutflowCtrlHistW   ->Write();
  }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: histFinalize ()
{
  // mirror image of histInitialize(); gets called after last event
  // processed on worker node; allows finishing up objects created in
  // histInitialize() before they're written to disk; gets called on
  // all worker nodes regardless of whether they processed input events

  ANA_CHECK( xAH::Algorithm::algFinalize() );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: executeSelection ( const xAOD::EventInfo* eventInfo, const std::string& systName,
						     bool& passSelection )
{
  ANA_MSG_DEBUG( "in executeSelection..." );
  
  // did event pass any selections?
  int passAnySelection = 0;

  // retrieve jet container(s)
  for ( size_t i = 0; i != m_inJetContainers.size(); ++i ) {

    const xAOD::JetContainer* inJets = 0;

    m_isFirstJetContainer = ( i == 0 ) ? true : false; // check for first jet container

    if ( i == m_jetSystsContainerIndex || m_isNominalCase ) { // only run systs for specified container
    
      // skip jet container if not available
      if ( !HelperFunctions::isAvailable<xAOD::JetContainer>( m_inJetContainers.at(i) + systName, m_event, m_store, msg() ) ) {
	ANA_MSG_DEBUG( "Input jet container, '" << m_inJetContainers.at(i) + systName << "', is not available. Skipping..." );
	continue;
      }
    
      ANA_MSG_DEBUG( "Getting input jet container: " << m_inJetContainers.at(i) + systName );
      ANA_CHECK( HelperFunctions::retrieve( inJets, m_inJetContainers.at(i) + systName, m_event, m_store, msg() ) );

      // tag emerging jets --> ALWAYS FALSE FOR NOW...NEED TO FILL IN EJ-SELECTOR...
      for ( const auto& jet : *inJets )
	jet->auxdecor<char>("isEmerging") = selectEmergingJet( jet );

      // set decorator label
      std::string jetStr = "";
      if      ( m_inJetContainers.at(i).find("EMTopo") != std::string::npos ) jetStr = "EMTopo";
      else if ( m_inJetContainers.at(i).find("PFlow")  != std::string::npos ) jetStr = "PFlow";
      std::string decorLabel = jetStr + systName;

      // signal selections
      int passSignalSel = this->PassSignalCuts( eventInfo, inJets, m_inJetBins.at(i), decorLabel );

      // validation selections
      int passValidSel = this->PassValidationCuts( eventInfo, inJets, m_inJetBins.at(i), decorLabel );

      // control selections
      int passCtrlSel = this->PassControlCuts( eventInfo, inJets, m_inJetBins.at(i), decorLabel );

      passAnySelection += passSignalSel;
      passAnySelection += passValidSel;
      passAnySelection += passCtrlSel;
      // ANA_MSG_INFO( m_eventNumber << " " << decorLabel << " " << passAnySelection << " " <<
      // 		    passSignalSel << " " << passValidSel << " " << passCtrlSel );

      if ( m_decorateSelectedEvents ) {
	eventInfo->auxdecor<char>("passSignalSel_" + decorLabel) = passSignalSel;
	eventInfo->auxdecor<char>("passValidSel_"  + decorLabel) = passValidSel;
	eventInfo->auxdecor<char>("passCtrlSel_"   + decorLabel) = passCtrlSel;
      }

      if ( m_isNominalCase ) { // only count for nominal cases
      	m_numSignalEvents            .at(i) += passSignalSel;
      	m_numValidEvents             .at(i) += passValidSel;
      	m_numCtrlEvents              .at(i) += passCtrlSel;
	m_numSignalValidEvents       .at(i) += ( passSignalSel && passValidSel );

	m_numSignalWeightEvents      .at(i) += ( passSignalSel * m_mcEventWeight                     );
	m_numValidWeightEvents       .at(i) += ( passValidSel  * m_mcEventWeight                     );
	m_numCtrlWeightEvents        .at(i) += ( passCtrlSel   * m_mcEventWeight                     );
	m_numSignalValidWeightEvents .at(i) += ( ( passSignalSel && passValidSel ) * m_mcEventWeight );
      }

    }
    
  } // end loop over jet containers
  
  if ( !passAnySelection ) {
    passSelection = false;
    return EL::StatusCode::SUCCESS;
  }
  
  passSelection = true;
  return EL::StatusCode::SUCCESS;
}



int EJsxAODAnalysis :: PassSignalCuts ( const xAOD::EventInfo* eventInfo, const xAOD::JetContainer* jets,
					const std::string& bin_label,     const std::string& decor_label )
{
  // set bins
  int trig_bin     = m_cutflowSignalHist  ->GetXaxis()->FindBin( "multijetTrig"                    );
  int trig_bin_w   = m_cutflowSignalHistW ->GetXaxis()->FindBin( "multijetTrig"                    );
  // trig match bins ...
  int njet_bin     = m_cutflowSignalHist  ->GetXaxis()->FindBin( ( "NJets_"  + bin_label ).c_str() );
  int njet_bin_w   = m_cutflowSignalHistW ->GetXaxis()->FindBin( ( "NJets_"  + bin_label ).c_str() );
  int jetpt_bin    = m_cutflowSignalHist  ->GetXaxis()->FindBin( ( "jetPt_"  + bin_label ).c_str() );
  int jetpt_bin_w  = m_cutflowSignalHistW ->GetXaxis()->FindBin( ( "jetPt_"  + bin_label ).c_str() );
  int jeteta_bin   = m_cutflowSignalHist  ->GetXaxis()->FindBin( ( "jetEta_" + bin_label ).c_str() );
  int jeteta_bin_w = m_cutflowSignalHistW ->GetXaxis()->FindBin( ( "jetEta_" + bin_label ).c_str() );
  int njetHt_bin   = m_cutflowSignalHist  ->GetXaxis()->FindBin( ( "njetHt_" + bin_label ).c_str() );
  int njetHt_bin_w = m_cutflowSignalHistW ->GetXaxis()->FindBin( ( "njetHt_" + bin_label ).c_str() );
  // int nej_bin      = m_cutflowSignalHist  ->GetXaxis()->FindBin( ( "nEJs_"   + bin_label ).c_str() );
  // int nej_bin_w    = m_cutflowSignalHistW ->GetXaxis()->FindBin( ( "nEJs_"   + bin_label ).c_str() );

  // initialize decorators
  if ( m_isNominalCase && m_isFirstJetContainer )
    eventInfo->auxdecor<char>("passSignalTrigSel")                = false;
  eventInfo->auxdecor<char>("passSignalNJetSel_"   + decor_label) = false;
  eventInfo->auxdecor<char>("passSignalJetPtSel_"  + decor_label) = false;
  eventInfo->auxdecor<char>("passSignalJetEtaSel_" + decor_label) = false;
  eventInfo->auxdecor<char>("passSignalNJetHtSel_" + decor_label) = false;
  
  // trigger selection
  bool passTrigSel = false;
  for ( size_t i = 0; i != m_passedTriggers.size(); ++i ) {
    for ( size_t j = 0; j != m_signalTrigs.size(); ++j ) {
      if ( m_passedTriggers.at(i) == m_signalTrigs.at(j) ) {
	passTrigSel = true;
	break;
      }
    }
    if ( passTrigSel ) break;
  }
  if ( m_isNominalCase && m_isFirstJetContainer ) {
    if ( m_useCutFlow && passTrigSel ) {   
      m_cutflowSignalHist  ->Fill( trig_bin,   1               );
      m_cutflowSignalHistW ->Fill( trig_bin_w, m_mcEventWeight );
    }
    if ( m_decorateSelectedEvents )
      eventInfo->auxdecor<char>("passSignalTrigSel") = passTrigSel;
  }
  if ( !passTrigSel ) return 0;

  // trigger matching ???

  // n-jet selection
  bool passNJetSel = true;
  if ( jets->size() < m_nSignalJets ) passNJetSel = false;
  if ( m_isNominalCase && m_useCutFlow && passNJetSel ) {  
    m_cutflowSignalHist  ->Fill( njet_bin,   1               );
    m_cutflowSignalHistW ->Fill( njet_bin_w, m_mcEventWeight );
  }
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passSignalNJetSel_" + decor_label) = passNJetSel;
  if ( !passNJetSel ) return 0;

  // jet-pt, jet-eta, njet-Ht, nej selections
  bool passJetPtSel  = true;
  bool passJetEtaSel = true;
  bool passNJetHtSel = true;
  bool passNEJSel    = true;
  double   njet_ht = 0;
  unsigned n_ej    = 0;
  for ( const auto& jet : *jets ) {
    if ( jet->index() >= m_nSignalJets ) break;
    if ( jet->pt() < m_signalJetPt * m_units ) passJetPtSel  = false;
    if ( fabs( jet->eta() ) > m_signalJetEta ) passJetEtaSel = false;
    njet_ht += jet->pt();
    if ( jet->auxdataConst<char>("isEmerging") ) ++n_ej;
  }
  if ( njet_ht < m_signalNJetHt * m_units ) passNJetHtSel = false;
  if ( n_ej    < m_nSignalEJs             ) passNEJSel    = false;
  
  if ( m_isNominalCase && m_useCutFlow && passJetPtSel ) { // jet-pt
    m_cutflowSignalHist  ->Fill( jetpt_bin,   1               );
    m_cutflowSignalHistW ->Fill( jetpt_bin_w, m_mcEventWeight );
  }
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passSignalJetPtSel_" + decor_label) = passJetPtSel;
  if ( !passJetPtSel ) return 0;

  if ( m_isNominalCase && m_useCutFlow && passJetEtaSel ) { // jet-eta
    m_cutflowSignalHist  ->Fill( jeteta_bin,   1               );
    m_cutflowSignalHistW ->Fill( jeteta_bin_w, m_mcEventWeight );
  }
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passSignalJetEtaSel_" + decor_label) = passJetPtSel;
  if ( !passJetEtaSel ) return 0;

  if ( m_isNominalCase && m_useCutFlow && passNJetHtSel ) { // njet-ht
    m_cutflowSignalHist  ->Fill( njetHt_bin,   1               );
    m_cutflowSignalHistW ->Fill( njetHt_bin_w, m_mcEventWeight );
  }
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passSignalNJetHtSel_" + decor_label) = passNJetHtSel;
  if ( !passNJetHtSel ) return 0;

  // if ( m_isNominalCase && m_useCutFlow && passNEJSel ) { // nej
  //   m_cutflowSignalHist  ->Fill( nej_bin,   1               );
  //   m_cutflowSignalHistW ->Fill( nej_bin_w, m_mcEventWeight );
  // }
  // if ( m_decorateSelectedEvents )
  //   eventInfo->auxdecor<char>("passSignalNEJSel_" + decor_label ) = passNEJSel;
  // if ( !passNEJSel ) return 0;
  
  return 1;
}



int EJsxAODAnalysis :: PassValidationCuts ( const xAOD::EventInfo* eventInfo, const xAOD::JetContainer* jets,
					    const std::string& bin_label,     const std::string& decor_label )
{
  // set bins
  int trig_bin       = m_cutflowValidHist  ->GetXaxis()->FindBin( "singlejetTrig"                   );
  int trig_bin_w     = m_cutflowValidHistW ->GetXaxis()->FindBin( "singlejetTrig"                   );
  // trig match bins ...
  int njetmin_bin    = m_cutflowValidHist  ->GetXaxis()->FindBin( ( "NJetsMin_" + bin_label ).c_str() );
  int njetmin_bin_w  = m_cutflowValidHistW ->GetXaxis()->FindBin( ( "NJetsMin_" + bin_label ).c_str() );
  int njetmax_bin    = m_cutflowValidHist  ->GetXaxis()->FindBin( ( "NJetsMax_" + bin_label ).c_str() );
  int njetmax_bin_w  = m_cutflowValidHistW ->GetXaxis()->FindBin( ( "NJetsMax_" + bin_label ).c_str() );
  int jetpt_bin      = m_cutflowValidHist  ->GetXaxis()->FindBin( ( "jetPt_"    + bin_label ).c_str() );
  int jetpt_bin_w    = m_cutflowValidHistW ->GetXaxis()->FindBin( ( "jetPt_"    + bin_label ).c_str() );
  int jeteta_bin     = m_cutflowValidHist  ->GetXaxis()->FindBin( ( "jetEta_"   + bin_label ).c_str() );
  int jeteta_bin_w   = m_cutflowValidHistW ->GetXaxis()->FindBin( ( "jetEta_"   + bin_label ).c_str() );
  // --> require events to pass single-jet triggers and contain at least two but less than our jets w/ pt at least 50 GeV
  // --> --> do we want/need an eta requirement? maybe < 2.7?

  // initialize decorators
  if ( m_isNominalCase && m_isFirstJetContainer )
    eventInfo->auxdecor<char>("passValidTrigSel")                 = false;
  eventInfo->auxdecor<char>("passValidNJetMinSel_" + decor_label) = false;
  eventInfo->auxdecor<char>("passValidNJetMaxSel_" + decor_label) = false;
  eventInfo->auxdecor<char>("passValidJetPtSel_"   + decor_label) = false;
  eventInfo->auxdecor<char>("passValidJetEtaSel_"  + decor_label) = false;

  // trigger selection
  bool passTrigSel  = false;
  for ( size_t i = 0; i != m_passedTriggers.size(); ++i ) {
    for ( size_t j = 0; j != m_validTrigs.size(); ++j ) {
      if ( m_passedTriggers.at(i) == m_validTrigs.at(j) ) {
	passTrigSel = true;
	break;
      }
    }
    if ( passTrigSel ) break;
  }
  if ( m_isNominalCase && m_isFirstJetContainer ) {
    if ( m_useCutFlow && passTrigSel ) {
      m_cutflowValidHist  ->Fill( trig_bin,   1               );
      m_cutflowValidHistW ->Fill( trig_bin_w, m_mcEventWeight );
    }
    if ( m_decorateSelectedEvents )
      eventInfo->auxdecor<char>("passValidTrigSel") = passTrigSel;
  }
  if ( !passTrigSel ) return 0;

  // trigger matching ???

  // n-jet min selection
  bool passNJetMinSel = true;
  if ( jets->size() <  m_nValidJets  ) passNJetMinSel = false;
  if ( m_isNominalCase && m_useCutFlow && passNJetMinSel ) {
    m_cutflowValidHist  ->Fill( njetmin_bin,   1               );
    m_cutflowValidHistW ->Fill( njetmin_bin_w, m_mcEventWeight );
  }
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passValidNJetMinSel_" + decor_label) = passNJetMinSel;
  if ( !passNJetMinSel ) return 0;

  // n-jet max selection
  bool passNJetMaxSel = true;
  if ( jets->size() >= m_nSignalJets ) passNJetMaxSel = false;
  if ( m_isNominalCase && m_useCutFlow && passNJetMaxSel ) {
    m_cutflowValidHist  ->Fill( njetmax_bin,   1               );
    m_cutflowValidHistW ->Fill( njetmax_bin_w, m_mcEventWeight );
  }
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passValidNJetMaxSel_" + decor_label) = passNJetMaxSel;
  if ( !passNJetMaxSel ) return 0;

  // jet-pt, jet-eta selection
  bool passJetPtSel  = true;
  bool passJetEtaSel = true;
  for ( const auto& jet : *jets ) {
    if ( jet->index() >= m_nValidJets ) break;
    if ( jet->pt() < m_validJetPt * m_units ) passJetPtSel  = false;
    if ( fabs( jet->eta() ) > m_validJetEta ) passJetEtaSel = false;
  }
  
  if ( m_isNominalCase && m_useCutFlow && passJetPtSel ) { // jet-pt
    m_cutflowValidHist  ->Fill( jetpt_bin,   1               );
    m_cutflowValidHistW ->Fill( jetpt_bin_w, m_mcEventWeight );
  }
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passValidJetPtSel_" + decor_label) = passJetPtSel;
  if ( !passJetPtSel ) return 0;

  if ( m_isNominalCase && m_useCutFlow && passJetEtaSel ) { // jet-eta
    m_cutflowValidHist  ->Fill( jeteta_bin,   1               );
    m_cutflowValidHistW ->Fill( jeteta_bin_w, m_mcEventWeight );
  }
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passValidJetEtaSel_" + decor_label) = passJetEtaSel;
  if ( !passJetEtaSel ) return 0;
  
  return 1;
}



int EJsxAODAnalysis :: PassControlCuts ( const xAOD::EventInfo* eventInfo, const xAOD::JetContainer* jets,
					 const std::string& bin_label,     const std::string& decor_label )
{
  // until we fill in, fail all...
  return 0;
  
  return 1;
}



bool EJsxAODAnalysis :: selectEmergingJet ( const xAOD::Jet* )
{
  // until we fill in, fail all...
  return false;

  // if we made it this far, jet is emerging...
  return true;
}
