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
  if ( m_truthLevelOnly && m_inJetContainers.empty() )
    m_inJetContainers.push_back( m_inTruthJetContainerName );

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

  // set trigger-type cutflow/decorator label
  bool signalTrig_2j = false;
  bool signalTrig_3j = false;
  bool signalTrig_4j = false;
  bool signalTrig_5j = false;
  bool signalTrig_6j = false;
  bool signalTrig_7j = false;
  for ( size_t i = 0; i != m_signalTrigs.size(); ++i ) {
    if      ( m_signalTrigs.at(i).find("HLT_2j") != std::string::npos ) signalTrig_2j = true;
    else if ( m_signalTrigs.at(i).find("HLT_3j") != std::string::npos ) signalTrig_3j = true;
    else if ( m_signalTrigs.at(i).find("HLT_4j") != std::string::npos ) signalTrig_4j = true;
    else if ( m_signalTrigs.at(i).find("HLT_5j") != std::string::npos ) signalTrig_5j = true;
    else if ( m_signalTrigs.at(i).find("HLT_6j") != std::string::npos ) signalTrig_6j = true;
    else if ( m_signalTrigs.at(i).find("HLT_7j") != std::string::npos ) signalTrig_7j = true;
  }
  int njet_trig = signalTrig_2j + signalTrig_3j + signalTrig_4j + signalTrig_5j + signalTrig_6j + signalTrig_7j;
  if      ( njet_trig > 1 ) m_signalTrigLabel = "multiJetTrigger";
  else if ( signalTrig_2j ) m_signalTrigLabel = "twoJetTrigger";
  else if ( signalTrig_3j ) m_signalTrigLabel = "threeJetTrigger";
  else if ( signalTrig_4j ) m_signalTrigLabel = "fourJetTrigger";
  else if ( signalTrig_5j ) m_signalTrigLabel = "fiveJetTrigger";
  else if ( signalTrig_6j ) m_signalTrigLabel = "sixJetTrigger";
  else if ( signalTrig_7j ) m_signalTrigLabel = "sevenJetTrigger";

  bool validTrig_1j = false;
  for ( size_t i = 0; i != m_validTrigs.size(); ++i )
    if ( m_validTrigs.at(i).find("HLT_j") != std::string::npos ) validTrig_1j = true;
  if ( validTrig_1j ) m_validTrigLabel = "singleJetTrigger";
  
  
  // initialize cutflows
  if ( m_useCutFlow ) {
    
    // retrieve file in which cutflow hists are stored
    TFile *file = wk()->getOutputFile( "cutflow" );
    
    // retrieve event cutflows
    m_cutflowHist  = (TH1D*)file->Get( "cutflow"          );
    m_cutflowHistW = (TH1D*)file->Get( "cutflow_weighted" ); 
    m_cutflowHist  ->GetXaxis()->FindBin( ( m_name                             ).c_str() );
    m_cutflowHistW ->GetXaxis()->FindBin( ( m_name                             ).c_str() );
    m_cutflowHist  ->GetXaxis()->FindBin( ( m_name + "Signal_" + m_cutflowJets ).c_str() );
    m_cutflowHistW ->GetXaxis()->FindBin( ( m_name + "Signal_" + m_cutflowJets ).c_str() );
    m_cutflowHist  ->GetXaxis()->FindBin( ( m_name + "Valid_"  + m_cutflowJets ).c_str() );
    m_cutflowHistW ->GetXaxis()->FindBin( ( m_name + "Valid_"  + m_cutflowJets ).c_str() );
    // m_cutflowHist  ->GetXaxis()->FindBin( ( m_name + "Ctrl_"   + m_cutflowJets ).c_str() );
    // m_cutflowHistW ->GetXaxis()->FindBin( ( m_name + "Ctrl_"   + m_cutflowJets ).c_str() );  
    m_cutflow_bin  = m_cutflowHist->GetXaxis()->FindBin( ( m_name ).c_str() );

    // initialize EJs cutflows
    m_signal_cutflowHist    = new TH1D( "cutflow_ejs_signal", "cutflow_ejs_signal", 1, 1, 2 );
    m_signal_cutflowHist    ->SetCanExtend( TH1::kAllAxes );   
    m_signal_cutflow_all    = m_signal_cutflowHist->GetXaxis()->FindBin( "all"                                );
    m_signal_cutflow_init   = m_signal_cutflowHist->GetXaxis()->FindBin( "init"                               );
    m_signal_cutflow_trig   = m_signal_cutflowHist->GetXaxis()->FindBin( m_signalTrigLabel.c_str()            );
    m_signal_cutflow_njet   = m_signal_cutflowHist->GetXaxis()->FindBin( ("nJets_"  + m_cutflowJets).c_str()  );
    m_signal_cutflow_jetpt  = m_signal_cutflowHist->GetXaxis()->FindBin( ("jetPt_"  + m_cutflowJets).c_str()  );
    m_signal_cutflow_jeteta = m_signal_cutflowHist->GetXaxis()->FindBin( ("jetEta_" + m_cutflowJets).c_str()  );
    m_signal_cutflow_njetHt = m_signal_cutflowHist->GetXaxis()->FindBin( ("nJetHt_" + m_cutflowJets).c_str()  );
    if ( m_truthLevelOnly )
      m_signal_cutflow_nej  = m_signal_cutflowHist->GetXaxis()->FindBin( ("nEJs_"   + m_cutflowJets).c_str()  );

    m_valid_cutflowHist     = new TH1D( "cutflow_ejs_valid", "cutflow_ejs_valid", 1, 1, 2 );
    m_valid_cutflowHist     ->SetCanExtend( TH1::kAllAxes );
    m_valid_cutflow_all     = m_valid_cutflowHist->GetXaxis()->FindBin( "all"                                 );
    m_valid_cutflow_init    = m_valid_cutflowHist->GetXaxis()->FindBin( "init"                                );
    m_valid_cutflow_trig    = m_valid_cutflowHist->GetXaxis()->FindBin( m_validTrigLabel.c_str()              );
    m_valid_cutflow_njetmin = m_valid_cutflowHist->GetXaxis()->FindBin( ("nJetsMin_" + m_cutflowJets).c_str() );
    m_valid_cutflow_jetpt   = m_valid_cutflowHist->GetXaxis()->FindBin( ("jetPt_"    + m_cutflowJets).c_str() );
    m_valid_cutflow_jeteta  = m_valid_cutflowHist->GetXaxis()->FindBin( ("jetEta_"   + m_cutflowJets).c_str() );
    m_valid_cutflow_njetmax = m_valid_cutflowHist->GetXaxis()->FindBin( ("nJetsMax_" + m_cutflowJets).c_str() );
    
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
      
    m_numSignalWeightEvents      .push_back(0);
    m_numValidWeightEvents       .push_back(0);
    m_numCtrlWeightEvents        .push_back(0);
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
  if ( m_applyRegionCuts ) {
    if ( !pass ) {
      wk()->skipEvent();
      return EL::StatusCode::SUCCESS;
    }
  }

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
    ANA_MSG_DEBUG( "filling cutflows + writing to output" );

    int jet_index = 0;
    for ( size_t i = 0; i != m_inJetContainers.size(); ++i ) {
      if ( m_inJetBins.at(i).find(m_cutflowJets) != std::string::npos ) jet_index = i;
    }
    unsigned j = m_cutflow_bin;
    m_cutflowHist  ->SetBinContent( j, m_numPassEvents       );
    m_cutflowHistW ->SetBinContent( j, m_numPassWeightEvents );
    ++j;
    m_cutflowHist  ->SetBinContent( j, m_numSignalEvents       .at(jet_index) );
    m_cutflowHistW ->SetBinContent( j, m_numSignalWeightEvents .at(jet_index) );
    ++j;
    m_cutflowHist  ->SetBinContent( j, m_numValidEvents        .at(jet_index) );
    m_cutflowHistW ->SetBinContent( j, m_numValidWeightEvents  .at(jet_index) );
    ++j;
    //m_cutflowHist  ->SetBinContent( j, m_numCtrlEvents         .at(jet_index) );
    //m_cutflowHistW ->SetBinContent( j, m_numCtrlWeightEvents   .at(jet_index) );
    //++j;
    m_cutflowHist  ->LabelsDeflate("X");
    m_cutflowHistW ->LabelsDeflate("X");

    // write new ejs cutflows to output file
    TFile *file = wk()->getOutputFile( "cutflow" );
    file->cd();
    m_numTotalEvents     = m_cutflowHist ->GetBinContent( 1 );
    m_signal_cutflowHist ->SetBinContent( m_signal_cutflow_all, m_numTotalEvents );
    m_valid_cutflowHist  ->SetBinContent( m_valid_cutflow_all,  m_numTotalEvents );
    m_signal_cutflowHist ->LabelsDeflate("X");
    m_valid_cutflowHist  ->LabelsDeflate("X");
    m_signal_cutflowHist ->Write();
    m_valid_cutflowHist  ->Write();

    // get metadata histogram
    TFile *metaFile    = wk()  ->getOutputFile( "metadata"            );
    m_meta_cutflowHist = (TH1D*) metaFile->Get( "MetaData_EventCount" );
    m_meta_cutflowHist ->LabelsDeflate("X");
    m_meta_cutflowHist ->Write();
    // save metadata histogram to data-tree
    TFile *treeFile    = wk() ->getOutputFile( "tree" );
    m_meta_cloneHist   = (TH1D*) m_meta_cutflowHist->Clone();
    m_meta_cloneHist   ->SetDirectory( treeFile );
  }

  delete m_signal_cutflowHist;
  delete m_valid_cutflowHist;

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
      else if ( m_inJetContainers.at(i).find("Truth")  != std::string::npos ) jetStr = "Truth";
      std::string decorLabel = jetStr + systName;

      // calculate N-jet Ht
      unsigned njets = 0;
      double njet_ht = 0;
      for ( const auto& jet : *inJets ) {
	if ( njets >= m_nSignalJets ) break;
	njet_ht += jet->pt();
	++njets;
      }
      eventInfo->auxdecor<double>("NJetHt_" + decorLabel) = njet_ht / m_units;

      // signal selections
      int passSignalSel   = this->PassSignalCuts     ( eventInfo, inJets, decorLabel );

      // validation selections
      int passValidSel    = this->PassValidationCuts ( eventInfo, inJets, decorLabel );

      // control selections
      int passCtrlSel     = this->PassControlCuts    ( eventInfo, inJets, decorLabel );

      passAnySelection   += passSignalSel;
      passAnySelection   += passValidSel;
      passAnySelection   += passCtrlSel;

      if ( m_decorateSelectedEvents ) {
	eventInfo->auxdecor<char>("passSignalSel_" + decorLabel) = passSignalSel;
	eventInfo->auxdecor<char>("passValidSel_"  + decorLabel) = passValidSel;
	eventInfo->auxdecor<char>("passCtrlSel_"   + decorLabel) = passCtrlSel;
      }

      if ( m_isNominalCase ) { // only count for nominal cases
	m_numSignalEvents       .at(i) += passSignalSel;
	m_numValidEvents        .at(i) += passValidSel;
	m_numCtrlEvents         .at(i) += passCtrlSel;

	m_numSignalWeightEvents .at(i) += ( passSignalSel * m_mcEventWeight );
	m_numValidWeightEvents  .at(i) += ( passValidSel  * m_mcEventWeight );
	m_numCtrlWeightEvents   .at(i) += ( passCtrlSel   * m_mcEventWeight );
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
					const std::string& decor_label )
{
  // initialize decorators
  if ( m_isNominalCase && m_isFirstJetContainer )
    eventInfo ->auxdecor<char>("passSignalTrigSel"                 ) = false;
  eventInfo   ->auxdecor<char>("passSignalNJetSel_"   + decor_label) = false;
  eventInfo   ->auxdecor<char>("passSignalJetPtSel_"  + decor_label) = false;
  eventInfo   ->auxdecor<char>("passSignalJetEtaSel_" + decor_label) = false;
  eventInfo   ->auxdecor<char>("passSignalNJetHtSel_" + decor_label) = false;
  eventInfo   ->auxdecor<char>("passSignalNEJSel_"    + decor_label) = false;
 
  // test selections and decorate events with pass/fail result -->
  
  // trigger selection
  bool passTrigSel = true;
  if ( !m_truthLevelOnly ) {
    passTrigSel = false;
    for ( size_t i = 0; i != m_passedTriggers.size(); ++i ) {
      for ( size_t j = 0; j != m_signalTrigs.size(); ++j ) {
  	if ( m_passedTriggers.at(i) == m_signalTrigs.at(j) ) {
  	  passTrigSel = true;
  	  break;
  	}
      }
      if ( passTrigSel ) break;
    }
    if ( m_isNominalCase && m_isFirstJetContainer && m_decorateSelectedEvents )
      eventInfo->auxdecor<char>("passSignalTrigSel") = passTrigSel;
  }

  // n-jet selection
  bool passNJetSel = true;
  if ( jets->size() < m_nSignalJets ) passNJetSel = false;
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passSignalNJetSel_" + decor_label) = passNJetSel;

  // jet-pt, jet-eta, njet-Ht, nej selections
  bool passJetPtSel  = true;
  bool passJetEtaSel = true;
  bool passNJetHtSel = true;
  bool passNEJSel    = true;
  unsigned njets   = 0;
  double   njet_ht = 0;
  unsigned n_ej    = 0;
  for ( const auto& jet : *jets ) {
    if ( njets >= m_nSignalJets ) break;
    if ( jet->pt() < m_signalJetPt * m_units ) passJetPtSel  = false;
    if ( fabs( jet->eta() ) > m_signalJetEta ) passJetEtaSel = false;
    njet_ht += jet->pt();
    if ( jet->auxdataConst<char>("isEmerging") ) ++n_ej;
    ++njets;
  }
  if ( njet_ht < m_signalNJetHt * m_units ) passNJetHtSel = false;
  if ( n_ej    < m_nSignalEJs             ) passNEJSel    = false;
  
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passSignalJetPtSel_"  + decor_label) = passJetPtSel;

  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passSignalJetEtaSel_" + decor_label) = passJetPtSel;

  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passSignalNJetHtSel_" + decor_label) = passNJetHtSel;

  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passSignalNEJSel_"    + decor_label ) = passNEJSel;


  // do cutflow and apply selections
  bool doCutflowJets = false; // do cutflow for this jet container ??
  if ( decor_label.find(m_cutflowJets) != std::string::npos ) doCutflowJets = true;
  
  if ( m_isNominalCase && m_isFirstJetContainer && m_useCutFlow ) // initial events (after prior alg sels)
    m_signal_cutflowHist ->Fill( m_signal_cutflow_init, 1 );
  
  if ( m_isNominalCase && m_isFirstJetContainer && m_useCutFlow && passTrigSel ) // trigger
    m_signal_cutflowHist ->Fill( m_signal_cutflow_trig, 1 );
  if ( !passTrigSel   ) return 0;

  if ( m_isNominalCase && m_useCutFlow && passNJetSel   && doCutflowJets ) // n jets
    m_signal_cutflowHist ->Fill( m_signal_cutflow_njet, 1 );
  if ( !passNJetSel   ) return 0;

  if ( m_isNominalCase && m_useCutFlow && passJetPtSel  && doCutflowJets ) // jet-pt
    m_signal_cutflowHist ->Fill( m_signal_cutflow_jetpt, 1 );
  if ( !passJetPtSel  ) return 0;

  if ( m_isNominalCase && m_useCutFlow && passJetEtaSel && doCutflowJets ) // jet-eta
    m_signal_cutflowHist ->Fill( m_signal_cutflow_jeteta, 1 );
  if ( !passJetEtaSel ) return 0;
  
  if ( m_isNominalCase && m_useCutFlow && passNJetHtSel && doCutflowJets ) // njet-ht
    m_signal_cutflowHist ->Fill( m_signal_cutflow_njetHt, 1 );
  if ( !passNJetHtSel ) return 0;

  // only apply nEJs selection for truth derivations for now...
  if ( m_truthLevelOnly ) {
    if ( m_isNominalCase && m_useCutFlow && passNEJSel  && doCutflowJets ) // nej
      m_signal_cutflowHist ->Fill( m_signal_cutflow_nej, 1 );
    if ( !passNEJSel  ) return 0;
  }
  
  return 1;
}



int EJsxAODAnalysis :: PassValidationCuts ( const xAOD::EventInfo* eventInfo, const xAOD::JetContainer* jets,
					    const std::string& decor_label )
{
  // initialize decorators
  if ( m_isNominalCase && m_isFirstJetContainer )
    eventInfo ->auxdecor<char>("passValidTrigSel")                   = false;
  eventInfo   ->auxdecor<char>("passValidNJetMinSel_" + decor_label) = false;
  eventInfo   ->auxdecor<char>("passValidNJetMaxSel_" + decor_label) = false;
  eventInfo   ->auxdecor<char>("passValidJetPtSel_"   + decor_label) = false;
  eventInfo   ->auxdecor<char>("passValidJetEtaSel_"  + decor_label) = false;

  // test selections and decorate events with pass/fail result -->

  // trigger selection
  bool passTrigSel = true;
  if ( !m_truthLevelOnly ) {
    passTrigSel  = false;
    for ( size_t i = 0; i != m_passedTriggers.size(); ++i ) {
      for ( size_t j = 0; j != m_validTrigs.size(); ++j ) {
	if ( m_passedTriggers.at(i) == m_validTrigs.at(j) ) {
	  passTrigSel = true;
	  break;
	}
      }
      if ( passTrigSel ) break;
    }
    if ( m_isNominalCase && m_isFirstJetContainer && m_decorateSelectedEvents )    
      eventInfo->auxdecor<char>("passValidTrigSel") = passTrigSel;
  }

  // n-jet min selection
  bool passNJetMinSel = true;
  if ( jets->size() <  m_nValidJets  ) passNJetMinSel = false;
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passValidNJetMinSel_" + decor_label) = passNJetMinSel;

  // jet-pt, jet-eta selection
  bool passJetPtSel  = true;
  bool passJetEtaSel = true;
  unsigned njets     = 0;
  unsigned njets_pt  = 0;
  std::vector<float> validjet_pt;
  std::vector<float> validjet_eta;
  for ( const auto& jet : *jets ) {
    // count number of jets passing pt, eta cuts -- only need to look at leading four
    if ( njets >= m_nSignalJets ) break;
    if ( jet->pt() < m_validJetPt * m_units ) break;
    ++njets_pt;
    if ( fabs( jet->eta() ) > m_validJetEta ) break;
    ++njets;
    validjet_pt.push_back( jet->pt() );
    validjet_eta.push_back( fabs( jet->eta() ) );
  }
  if ( njets_pt < m_nValidJets ) passJetPtSel  = false;
  if ( njets    < m_nValidJets ) passJetEtaSel = false;

  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passValidJetPtSel_" + decor_label) = passJetPtSel;

  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passValidJetEtaSel_" + decor_label) = passJetEtaSel;
 
  // n-jet max selection
  bool passNJetMaxSel = true;
  if ( njets >= m_nSignalJets ) passNJetMaxSel = false;
  if ( m_decorateSelectedEvents )
    eventInfo->auxdecor<char>("passValidNJetMaxSel_" + decor_label) = passNJetMaxSel;

  
  // do cutflow and apply selections
  bool doCutflowJets = false; // do cutflow this jet container ??
  if ( decor_label.find(m_cutflowJets) != std::string::npos ) doCutflowJets = true;

  if ( m_isNominalCase && m_isFirstJetContainer && m_useCutFlow ) // initial events (after prior alg sels)
    m_valid_cutflowHist ->Fill( m_valid_cutflow_init, 1 );

  if ( m_isNominalCase && m_isFirstJetContainer && m_useCutFlow && passTrigSel ) // trigger
    m_valid_cutflowHist ->Fill( m_valid_cutflow_trig, 1 );
  if ( !passTrigSel    ) return 0;

  if ( m_isNominalCase && m_useCutFlow && passNJetMinSel && doCutflowJets ) // n min jets
    m_valid_cutflowHist ->Fill( m_valid_cutflow_njetmin, 1 );
  if ( !passNJetMinSel ) return 0;

  if ( m_isNominalCase && m_useCutFlow && passJetPtSel   && doCutflowJets ) // jet-pt
    m_valid_cutflowHist ->Fill( m_valid_cutflow_jetpt, 1 );
  if ( !passJetPtSel   ) return 0;
  
  if ( m_isNominalCase && m_useCutFlow && passJetEtaSel  && doCutflowJets ) // jet-eta
    m_valid_cutflowHist ->Fill( m_valid_cutflow_jeteta, 1 );
  if ( !passJetEtaSel  ) return 0;
  
  if ( m_isNominalCase && m_useCutFlow && passNJetMaxSel && doCutflowJets ) // n max jets
    m_valid_cutflowHist ->Fill( m_valid_cutflow_njetmax, 1 );
  if ( !passNJetMaxSel ) return 0;
  
  return 1;
}



int EJsxAODAnalysis :: PassControlCuts ( const xAOD::EventInfo* eventInfo, const xAOD::JetContainer* jets,
					 const std::string& decor_label )
{
  // until we fill in, fail all...
  return 0;
  
  return 1;
}



bool EJsxAODAnalysis :: selectEmergingJet ( const xAOD::Jet* jet )
{
  // until we fill in, fail all reco jets...
  if ( !m_truthLevelOnly )
    return false;

  // for truth jets, count as emerging if matched to dark jets
  if ( m_truthLevelOnly && jet->isAvailable<char>("hasDarkJetMatch") )
    if ( !jet->auxdataConst<char>("hasDarkJetMatch") )
      return false;

  // if we made it this far, jet is emerging...
  return true;
}
