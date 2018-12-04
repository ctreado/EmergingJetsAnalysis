#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <xAODAnaHelpers/HelperFunctions.h>

#include <xAODEventInfo/EventInfo.h>

#include "EJsAnalysis/EJsMiniNtuple.h"
#include "EJsAnalysis/EJsHelpTreeBase.h"

// needed to distribute algorithm to workers
ClassImp ( EJsMiniNtuple )



EJsMiniNtuple :: EJsMiniNtuple () : Algorithm ( "EJsMiniNtuple" )
{
  // code for base initialization of variables, e.g. initialize
  // all pointers to zero; note this method called on submission +
  // worker node, so only put most basic initialization here;
  // most initialization will go in histInitialize() and initialize()
}



EL::StatusCode EJsMiniNtuple :: setupJob ( EL::Job& job )
{
  // code to set up job on submission object so it's ready to work
  // w/ alg, e.g. request D3PDReader service or add output files;
  // code here automatically activated/deactivated when alg
  // added/removed from job
  
  // initialize alg to use xAODRootAccess package
  job.useXAOD();
  xAOD::Init( "EJsMiniNtuple" ).ignore(); // call before opening first file

  EL::OutputStream outForTree( "tree" );
  job.outputAdd( outForTree );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: histInitialize ()
{
  // everything that needs to be done at the beginning on each
  // worker node, e.g. create histos + output trees;
  // this method called before any input files connected
  
  ANA_CHECK( xAH::Algorithm::algInitialize() );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: fileExecute ()
{
  // everything that needs to be done exactly once for every
  // single file, e.g. collect list of all lumi-blocks processed

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: changeInput ( bool /*firstFile*/ )
{
  // everything that needs to be done when input files change,
  // e.g. resetting branch addresses on trees; not needed if
  // using D3PDReader or similar service...

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: initialize ()
{
  // everything that needs to be done after first input file
  // connected and before first event processed, e.g. create
  // additional histograms based on variables available in input files;
  // can also create all histograms + trees here, but note this method
  // doesn't get called if no events processed, so objects created
  // here won't be available in output if no input events

  ANA_MSG_INFO( "Initializing EJsMiniNtuple..." );

  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();

  // get file already created + add directory for ntuple
  TFile* treeFile = wk()->getOutputFile( "tree" );
  treeFile->mkdir( m_name.c_str() );

  // to handle more than jet collection
  std::string token;
  std::istringstream ss_reco_containers( m_jetContainerName );
  while ( std::getline( ss_reco_containers, token, ' ' ) )
    m_jetContainers.push_back( token );
  std::istringstream ss_reco_names( m_jetBranchName );
  if ( !m_jetBranchName.empty() ) {
    while ( std::getline( ss_reco_names, token, ' ' ) )
      m_jetBranches.push_back( token );
    if ( !m_jetContainerName.empty() &&
	 m_jetContainers.size() != m_jetBranches.size() ) {
      ANA_MSG_ERROR( "Number of jet containers must be equal " <<
		     "to number of jet branch names. Exiting." );
      return EL::StatusCode::FAILURE;
    }
  }
  else // default to use jet container names as jet branch names
    for ( size_t i = 0; i != m_jetContainers.size(); ++i )
      m_jetBranches.push_back( m_jetContainers.at(i) );

  // allow to store different variables for each jet collection (default: store the same)
  std::istringstream ss( m_jetDetailStr );
  while ( std::getline( ss, token, '|' ) )
    m_jetDetails.push_back( token );
  if ( m_jetDetails.size() != 1 && m_jetContainers.size() != m_jetDetails.size() ) {
    ANA_MSG_ERROR( "Size of 'm_jetContainers' should be equal " <<
		   "to size of 'm_jetDetailStr'. Exiting" );
    return EL::StatusCode::FAILURE;
  }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: addTree ( std::string syst )
{
  ANA_MSG_DEBUG( "About to add tree for individual systematic" );

  // get file created above
  TFile* treeFile = wk()->getOutputFile( "tree" );

  std::string treeName = syst;
  if ( syst.empty() ) treeName = "nominal";

  ANA_MSG_INFO( "Making tree " << m_name << "/" << treeName );
  TTree* outTree = new TTree( treeName.c_str(), treeName.c_str() );
  if ( !outTree ) {
    ANA_MSG_ERROR( "Failed to instantiate output tree!" );
    return EL::StatusCode::FAILURE;
  }

  // this yields unchecked status code -->
  // --> probably from HelperFunctions::retrieve(eventInfo...) in class instantiation
  // --> is there a way to check this other than modifying HelpTreeBase code ???
  m_trees[syst] = new EJsHelpTreeBase( m_event, outTree, treeFile, 1e3, msgLvl(MSG::DEBUG), m_store );
  //new HelpTreeBase( m_event, outTree, treeFile, 1e3, msgLvl(MSG::DEBUG), m_store );
  const auto& helpTree = m_trees[syst];
  helpTree->m_vertexContainerName = m_vertexContainerName;

  // tell tree to go into file
  outTree->SetDirectory( treeFile->GetDirectory( m_name.c_str() ) );
  if ( m_outHistDir ) {
    if ( m_trees.size() > 1 )
      ANA_MSG_WARNING( "You're running systematics! " <<
		       "Set 'm_outHistDir = false' if you encounter issues " <<
		       "writing all output TTrees to output histogram file." );  
    wk()->addOutput( outTree );
  }

  
  // initialize all branches since we just added this tree
  helpTree->AddEvent( m_evtDetailStr );
  
  if ( !m_trigDetailStr.empty() )
    helpTree->AddTrigger( m_trigDetailStr );
  
  if ( !m_jetContainerName.empty() ) {
    for ( unsigned i = 0; i != m_jetContainers.size(); ++i ) {
      if ( m_jetDetails.size() == 1 )
	helpTree->AddJets( m_jetDetails.at(0), m_jetBranches.at(i).c_str() );
      else
	helpTree->AddJets( m_jetDetails.at(i), m_jetBranches.at(i).c_str() );
    }
  }
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: execute ()
{
  // everything that needs to be done on every single event,
  // e.g. read input variables, apply cuts, fill histos + trees;
  // here is where most of actual analysis will go...

  ANA_MSG_DEBUG( "Executing EJsMiniNtuple algorithm" );

  // systematics to process for the event
  // --> always handle nominal case ("") on every event
  std::vector<std::string> event_systNames({""});

  // temporary pointer for copying systematics
  std::vector<std::string>* systNames = 0;

  // add systematics to event-systematics vector
  if ( !m_systsVec.empty() ) {
    ANA_CHECK( HelperFunctions::retrieve( systNames, m_systsVec, 0, m_store, msg() ) );
    for ( const auto& systName : *systNames ) {
      if ( std::find( event_systNames.begin(), event_systNames.end(), systName )
  	   != event_systNames.end() ) continue;
      event_systNames.push_back( systName );
    }
  }

  // execute event for each individual systematic
  for ( const auto& systName : event_systNames ) {
    ANA_CHECK( executeSyst( systName ) );
  }


  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: executeSyst ( std::string syst )
{
  ANA_MSG_DEBUG( "Executing event for individual systematic" );

  // add tree if it's not already created
  if ( m_trees.find( syst ) == m_trees.end() )
    ANA_CHECK( addTree( syst ) );

  const auto& helpTree = m_trees[syst];

  
  // assume nominal container by default
  std::string jetSuffix( "" );

  
  // retrieve event info container
  ANA_MSG_DEBUG( "Retrieving '" << m_eventInfoContainerName << "' event info container" );
  const xAOD::EventInfo* eventInfo = 0;
  ANA_CHECK( HelperFunctions::retrieve( eventInfo, m_eventInfoContainerName,
					m_event, m_store, msg() ) );

  // retrieve primary vertex
  ANA_MSG_DEBUG( "Retrieving '" << m_vertexContainerName << "' vertex container" );
  const xAOD::VertexContainer* vertices = 0;
  if ( m_retrievePV )
    ANA_CHECK( HelperFunctions::retrieve( vertices, m_vertexContainerName,
					  m_event, m_store, msg() ) );
  ANA_MSG_DEBUG( "Setting primary vertex" );
  const xAOD::Vertex* primaryVertex =
    m_retrievePV ? HelperFunctions::getPrimaryVertex( vertices, msg() ) : 0;

  
  // fill event info
  ANA_MSG_DEBUG( "Filling event info branches" );
  helpTree->FillEvent( eventInfo );

  
  // fill trigger
  if ( !m_trigDetailStr.empty() ) {
    ANA_MSG_DEBUG( "Filling trigger branches" );
    helpTree->FillTrigger( eventInfo );
  }
  

  // fill jet
  if ( !m_jetContainerName.empty() ) {
    for ( unsigned i = 0; i != m_jetContainers.size(); ++i ) {
      ANA_MSG_DEBUG( "Retrieving '" << m_jetContainers.at(i) << "' jet container" );
      const xAOD::JetContainer* inJets = 0;
      ANA_CHECK( HelperFunctions::retrieve( inJets, m_jetContainers.at(i) + jetSuffix,
					    m_event, m_store, msg() ) );
      ANA_MSG_DEBUG( "Filling '" << m_jetBranches.at(i) << "' jet branch" );
      helpTree->FillJets( inJets, HelperFunctions::getPrimaryVertexLocation( vertices, msg() ),
			  m_jetBranches.at(i) );
    }
  }
  
  
  // fill the tree
  helpTree->Fill();
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: postExecute ()
{
  // everything that need to be done after main event processing;
  // mainly used in implementing NTupleSvc

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: finalize ()
{
  // mirror image of initialize(); gets called after last event
  // processed on worker node; allows finishing up objects created
  // in initialize() before they're written to disk; only gets
  // called on worker nodes that processed input events

  ANA_MSG_INFO( "Deleting tree instances..." );

  for ( auto& item : m_trees )
    if ( item.second ) { delete item.second; item.second = 0; }
  m_trees.clear();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: histFinalize ()
{
  // mirror image of histInitialize(); gets called after last event
  // processed on worker node; allows finishing up objects created in
  // histInitialize() before they're written to disk; gets called on
  // all worker nodes regardless of whether they processed input events

  return EL::StatusCode::SUCCESS;
}
