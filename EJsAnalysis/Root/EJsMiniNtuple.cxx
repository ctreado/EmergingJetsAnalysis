#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <xAODEventInfo/EventInfo.h>
#include <xAODJet/JetContainer.h>
#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>
#include <xAODTruth/TruthParticleContainer.h>
#include <xAODTruth/TruthVertexContainer.h>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/EJsMiniNtuple.h"

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

  
  // to handle more than one jet collection (reco, trig, truth)
  std::string token;
  // reco jets
  std::istringstream ss_reco_containers( m_jetContainerName );
  while ( std::getline( ss_reco_containers, token, ' ' ) )
    m_jetContainers.push_back( token );
  std::istringstream ss_reco_names( m_jetBranchName );
  while ( std::getline( ss_reco_names, token, ' ' ) )
    m_jetBranches.push_back( token );
  if ( m_jetBranches.empty() )
    for ( size_t i = 0; i != m_jetContainers.size(); ++i )
      m_jetBranches.push_back( m_jetContainers.at(i) );
  if ( !m_jetContainerName.empty() &&
       m_jetContainers.size() != m_jetBranches.size() ) {
    ANA_MSG_ERROR( "Number of jet containers must be equal " <<
		   "to number of jet branch names. Exiting." );
    return EL::StatusCode::FAILURE;
  }
  // trig jets
  std::istringstream ss_trig_containers( m_trigJetContainerName );
  while ( std::getline( ss_trig_containers, token, ' ' ) )
    m_trigJetContainers.push_back( token );
  std::istringstream ss_trig_names( m_trigJetBranchName );
  while ( std::getline( ss_trig_names, token, ' ' ) )
    m_trigJetBranches.push_back( token );
  if ( m_trigJetBranches.empty() )
    for ( size_t i = 0; i != m_trigJetContainers.size(); ++i )
      m_trigJetBranches.push_back( m_trigJetContainers.at(i) );
  if ( !m_trigJetContainerName.empty() &&
       m_trigJetContainers.size() != m_trigJetBranches.size() ) {
    ANA_MSG_ERROR( "Number of trig jet containers must be equal " <<
		   "to number of trig jet branch names. Exiting." );
    return EL::StatusCode::FAILURE;
  }
  // truth jets
  std::istringstream ss_truth_containers( m_truthJetContainerName );
  while ( std::getline( ss_truth_containers, token, ' ' ) )
    m_truthJetContainers.push_back( token );
  std::istringstream ss_truth_names( m_truthJetBranchName );
  while ( std::getline( ss_truth_names, token, ' ' ) )
    m_truthJetBranches.push_back( token );
  if ( m_truthJetBranches.empty() )
    for ( size_t i = 0; i != m_truthJetContainers.size(); ++i )
      m_truthJetBranches.push_back( m_truthJetContainers.at(i) );
  if ( !m_truthJetContainerName.empty() &&
       m_truthJetContainers.size() != m_truthJetBranches.size() ) {
    ANA_MSG_ERROR( "Number of truth jet containers must be equal " <<
		   "to number of truth jet branch names. Exiting." );
    return EL::StatusCode::FAILURE;
  }
  
  // allow to store different variables for each jet collection (default: store the same)
  std::istringstream ss( m_jetDetailStr );
  while ( std::getline( ss, token, '|' ) )
    m_jetDetails.push_back( token );
  if ( m_jetDetails.size() != 1 &&
       m_jetContainers.size() != m_jetDetails.size() ) {
    ANA_MSG_ERROR( "Size of 'm_jetContainers' should be equal " <<
		   "to size of 'm_jetDetailStr'. Exiting." );
    return EL::StatusCode::FAILURE;
  }
  std::istringstream ss_trig( m_trigJetDetailStr );
  while ( std::getline( ss_trig, token, '|' ) )
    m_trigJetDetails.push_back( token );
  if ( m_trigJetDetails.size() != 1 &&
       m_trigJetContainers.size() != m_trigJetDetails.size() ) {
    ANA_MSG_ERROR( "Size of 'm_trigJetContainers' should be equal " <<
		   "to size of 'm_trigJetDetailStr'. Exiting." );
    return EL::StatusCode::FAILURE;
  }
  std::istringstream ss_truth( m_truthJetDetailStr );
  while ( std::getline( ss_truth, token, '|' ) )
    m_truthJetDetails.push_back( token );
  if ( m_truthJetDetails.size() != 1 &&
       m_truthJetContainers.size() != m_truthJetDetails.size() ) {
    ANA_MSG_ERROR( "Size of 'm_truthJetContainers' should be equal " <<
		   "to size of 'm_truthJetDetailStr'. Exiting." );
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

  m_trees[syst] = new EJsHelpTreeBase( m_event, outTree, treeFile, 1e3, msgLvl(MSG::DEBUG), m_store );
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

  helpTree->AddPV( );
  
  if ( !m_jetContainerName.empty() ) {
    for ( size_t i = 0; i != m_jetContainers.size(); ++i ) {
      if ( m_jetDetails.size() == 1 )
      	helpTree->AddJets( m_jetDetails.at(0), m_jetBranches.at(i).c_str() );
      else
      	helpTree->AddJets( m_jetDetails.at(i), m_jetBranches.at(i).c_str() );
    }
  }

  if ( !m_trigJetContainerName.empty() ) {
    for ( size_t i = 0; i != m_trigJetContainers.size(); ++i ) {
      if ( m_trigJetDetails.size() == 1 )
	helpTree->AddJets( m_trigJetDetails.at(0), m_trigJetBranches.at(i).c_str() );
      else
	helpTree->AddJets( m_trigJetDetails.at(i), m_trigJetBranches.at(i).c_str() );
    }
  }

  if ( !m_truthJetContainerName.empty() ) {
    for ( size_t i = 0; i != m_truthJetContainers.size(); ++i ) {
      if ( m_truthJetDetails.size() == 1 )
	helpTree->AddJets( m_truthJetDetails.at(0), m_truthJetBranches.at(i).c_str() );
      else
	helpTree->AddJets( m_truthJetDetails.at(i), m_truthJetBranches.at(i).c_str() );
    }
  }

  if ( !m_truthPartContainerName.empty() )
    helpTree->AddTruthParts( m_truthPartBranchName, m_truthPartDetailStr );

  if ( !m_trackPartContainerName.empty() )
    helpTree->AddTrackParts( m_trackPartBranchName, m_trackPartDetailStr );

  if ( !m_truthVertexContainerName.empty() )
    helpTree->AddTruthVerts( m_truthVertexDetailStr, m_truthVertexBranchName );

  if ( !m_secondaryVertexContainerName.empty() )
    helpTree->AddSecondaryVerts( m_secondaryVertexDetailStr, m_secondaryVertexBranchName );
  
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
  std::vector<std::string> jetSystNames;

  // temporary pointer for copying systematics
  std::vector<std::string>* systNames = 0;

  // add systematics to event-systematics vector
  if ( !m_jetSystsVec.empty() ) {
    ANA_CHECK( HelperFunctions::retrieve( systNames, m_jetSystsVec, 0, m_store, msg() ) );
    for ( const auto& systName : *systNames ) {
      jetSystNames.push_back( systName );
      if ( std::find( event_systNames.begin(), event_systNames.end(), systName )
  	   != event_systNames.end() ) continue;
      event_systNames.push_back( systName );
    }
  }

  
  // execute event for each individual systematic
  for ( const auto& systName : event_systNames ) {

    // add tree if it's not already created
    if ( m_trees.find( systName ) == m_trees.end() )
      ANA_CHECK( addTree( systName ) );

    const auto& helpTree = m_trees[systName];

    
    // assume nominal container by default
    std::string jetSuffix( "" );
    
    // find systematic in corresponding vector
    if ( std::find( jetSystNames.begin(), jetSystNames.end(), systName ) != jetSystNames.end() )
      jetSuffix = systName;

  
    // retrieve event info container
    ANA_MSG_DEBUG( "Retrieving '" << m_eventInfoContainerName << "' event info container" );
    const xAOD::EventInfo* eventInfo = 0;
    ANA_CHECK( HelperFunctions::retrieve( eventInfo, m_eventInfoContainerName,
					  m_event, m_store, msg() ) );

    // retrieve primary vertex + location
    ANA_MSG_DEBUG( "Retrieving '" << m_vertexContainerName << "' vertex container" );
    const xAOD::VertexContainer* vertices = 0;
    if ( m_retrievePV )
      ANA_CHECK( HelperFunctions::retrieve( vertices, m_vertexContainerName,
					    m_event, m_store, msg() ) );
    ANA_MSG_DEBUG( "Setting primary vertex" );
    const xAOD::Vertex* primaryVertex =
      m_retrievePV ? HelperFunctions::getPrimaryVertex( vertices, msg() ) : 0; 
    ANA_MSG_DEBUG( "Getting primary vertex location" );
    int pvLocation = HelperFunctions::getPrimaryVertexLocation( vertices, msg() );

  
    // fill event info
    ANA_MSG_DEBUG( "Filling event info branches" );
    helpTree->FillEvent( eventInfo, m_event, vertices );


    // fill primary vertex info
    ANA_MSG_DEBUG( "Filling primary vertex branches" );
    helpTree->FillPV( primaryVertex, pvLocation );

  
    // fill trigger info
    if ( !m_trigDetailStr.empty() ) {
      ANA_MSG_DEBUG( "Filling trigger branches" );
      helpTree->FillTrigger( eventInfo );
    }
  

    // fill jets
    if ( !m_jetContainerName.empty() ) {
      for ( unsigned i = 0; i != m_jetContainers.size(); ++i ) {
	// skip jet container if not available
	if ( !HelperFunctions::isAvailable<xAOD::JetContainer>( m_jetContainers.at(i) + jetSuffix,
								m_event, m_store, msg() ) )
	  { ANA_MSG_DEBUG( "Jet container, '" << m_jetContainers.at(i) + jetSuffix <<
			   "', is not available. Skipping..." ); continue; }
	// get container + fill branches
	ANA_MSG_DEBUG( "Retrieving '" << m_jetContainers.at(i) << "' jet container" );
	const xAOD::JetContainer* inJets = 0;
	ANA_CHECK( HelperFunctions::retrieve( inJets, m_jetContainers.at(i) + jetSuffix,
					      m_event, m_store, msg() ) );
	ANA_MSG_DEBUG( "Filling '" << m_jetBranches.at(i) << "' jet branches" );
	helpTree->FillJets( inJets, pvLocation, m_jetBranches.at(i) );
      }
    }


    // fill trig jets
    if ( !m_trigJetContainerName.empty() ) {
      for ( unsigned i = 0; i != m_trigJetContainers.size(); ++i ) {
	// skip trig jet container if not available
	if ( !HelperFunctions::isAvailable<xAOD::JetContainer>( m_trigJetContainers.at(i),
								m_event, m_store, msg() ) )
	  { ANA_MSG_DEBUG( "Trig jet container, '" << m_trigJetContainers.at(i) <<
			   "', is not available. Skipping..." ); continue; }
	// get container + fill branches
	ANA_MSG_DEBUG( "Retrieving '" << m_trigJetContainers.at(i) << "' trig jet container" );
	const xAOD::JetContainer* inTrigJets = 0;
	ANA_CHECK( HelperFunctions::retrieve( inTrigJets, m_trigJetContainers.at(i),
					      m_event, m_store, msg() ) );
	ANA_MSG_DEBUG( "Filling '" << m_trigJetBranches.at(i) << "' trig jet branches" );
	helpTree->FillJets( inTrigJets, pvLocation, m_trigJetBranches.at(i) );
      }
    }


    // fill truth jets
    if ( !m_truthJetContainerName.empty() ) {
      for ( unsigned i = 0; i != m_truthJetContainers.size(); ++i ) {
	// skip truth jet container if not available
	if ( !HelperFunctions::isAvailable<xAOD::JetContainer>( m_truthJetContainers.at(i),
								m_event, m_store, msg() ) )
	  { ANA_MSG_DEBUG( "Truth jet container, '" << m_truthJetContainers.at(i) <<
			   "', is not available. Skipping..." ); continue; }
	// get container + fill branches
	ANA_MSG_DEBUG( "Retrieving '" << m_truthJetContainers.at(i) << "' truth jet container" );
	const xAOD::JetContainer* inTruthJets = 0;
	ANA_CHECK( HelperFunctions::retrieve( inTruthJets, m_truthJetContainers.at(i),
					      m_event, m_store, msg() ) );
	ANA_MSG_DEBUG( "Filling '" << m_truthJetBranches.at(i) << "' truth jet branches" );
	helpTree->FillJets( inTruthJets, pvLocation, m_truthJetBranches.at(i) );
      }
    }


    // fill truth particles
    if ( !m_truthPartContainerName.empty() ) {
      // get container + fill branches if available
      if ( HelperFunctions::isAvailable<xAOD::TruthParticleContainer>( m_truthPartContainerName,
								       m_event, m_store, msg() ) ) {
	ANA_MSG_DEBUG( "Retrieving '" << m_truthPartContainerName << "' truth particle container" );
	const xAOD::TruthParticleContainer* inTruthParts = 0;
	ANA_CHECK( HelperFunctions::retrieve( inTruthParts, m_truthPartContainerName,
					      m_event, m_store, msg() ) );
	ANA_MSG_DEBUG( "Filling '" << m_truthPartBranchName << "' truth particle branches" );
	helpTree->FillTruth( m_truthPartBranchName, inTruthParts );
      }
      // otherwise, skip
      else ANA_MSG_DEBUG( "Truth particle container, '" << m_truthPartContainerName <<
			  ", is not available. Skipping..." );
    }


    // fill tracks
    if ( !m_trackPartContainerName.empty() ) { 
      // get container + fill branches if available
      if ( HelperFunctions::isAvailable<xAOD::TrackParticleContainer>( m_trackPartContainerName,
								       m_event, m_store, msg() ) ) {
	ANA_MSG_DEBUG( "Retrieving '" << m_trackPartContainerName << "' track particle container" );
	const xAOD::TrackParticleContainer* inTrackParts = 0;
	ANA_CHECK( HelperFunctions::retrieve( inTrackParts, m_trackPartContainerName,
					      m_event, m_store, msg() ) );
	ANA_MSG_DEBUG( "Filling '" << m_trackPartBranchName << "' track particle branches" );
	helpTree->FillTracks( m_trackPartBranchName, inTrackParts );
      }
      // otherwise, skip
      else ANA_MSG_DEBUG( "Track particle container, '" << m_trackPartContainerName <<
			  ", is not available. Skipping..." );
    }


    // fill truth vertices
    if ( !m_truthVertexContainerName.empty() ) {
      // get container + fill branches if available
      if ( HelperFunctions::isAvailable<xAOD::TruthVertexContainer>( m_truthVertexContainerName,
								     m_event, m_store, msg() ) ) {
	ANA_MSG_DEBUG( "Retrieving '" << m_truthVertexContainerName << "' truth vertex container" );
	const xAOD::TruthVertexContainer* inTruthVerts = 0;
	ANA_CHECK( HelperFunctions::retrieve( inTruthVerts, m_truthVertexContainerName,
					      m_event, m_store, msg() ) );
	ANA_MSG_DEBUG( "Filling '" << m_truthVertexBranchName << "' truth vertex branches" );
	helpTree->FillTruthVerts( inTruthVerts, m_truthVertexBranchName );
      }
      // otherwise, skip
      else ANA_MSG_DEBUG( "Truth vertex container, '" << m_truthVertexContainerName <<
			  ", is not available. Skipping..." );
    }


    // fill secondary vertices
    if ( !m_secondaryVertexContainerName.empty() ) {
      // get container + fill branches if available
      if ( HelperFunctions::isAvailable<xAOD::VertexContainer>( m_secondaryVertexContainerName,
								m_event, m_store, msg() ) ) {
	ANA_MSG_DEBUG( "Retrieving '" << m_secondaryVertexContainerName <<
		       "' secondary vertex container" );
	const xAOD::VertexContainer* inSecVerts = 0;
	ANA_CHECK( HelperFunctions::retrieve( inSecVerts, m_secondaryVertexContainerName,
					      m_event, m_store, msg() ) );
	ANA_MSG_DEBUG( "Filling '" << m_secondaryVertexBranchName << "' secondary vertex branches" );
	helpTree->FillSecondaryVerts( inSecVerts, m_secondaryVertexBranchName );
      }
      // otherwise, skip
      else ANA_MSG_DEBUG( "Secondary vertex container, '" << m_secondaryVertexContainerName <<
			  ", is not available. Skipping..." );
    }


    // fill the tree
    helpTree->Fill();
  }


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

  ANA_CHECK( xAH::Algorithm::algFinalize() );

  return EL::StatusCode::SUCCESS;
}
