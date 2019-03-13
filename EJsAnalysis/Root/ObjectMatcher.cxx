#include <TVector3.h>
#include <TLorentzVector.h>

#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/ObjectMatcher.h"
#include "EJsAnalysis/EJsHelperFunctions.h"
#include "EJsAnalysis/AlgConsts.h"
#include "EJsAnalysis/VsiBonsaiTool.h"

// needed to distribute algorithm to workers
ClassImp ( ObjectMatcher )



ObjectMatcher :: ObjectMatcher () : Algorithm ( "ObjectMatcher" )
{
  // code for base initialization of variables, e.g. initialize
  // all pointers to zero; note this method called on submission +
  // worker node, so only put most basic initialization here;
  // most initialization will go in histInitialize() and initialize()
}



EL::StatusCode ObjectMatcher :: setupJob ( EL::Job& job )
{
  // code to set up job on submission object so it's ready to work
  // w/ alg, e.g. request D3PDReader service or add output files;
  // code here automatically activated/deactivated when alg
  // added/removed from job
  
  // initialize alg to use xAODRootAccess package
  job.useXAOD();
  xAOD::Init( "ObjectMatcher" ).ignore(); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode ObjectMatcher :: histInitialize ()
{
  // everything that needs to be done at the beginning on each
  // worker node, e.g. create histos + output trees;
  // this method called before any input files connected
  
  ANA_CHECK( xAH::Algorithm::algInitialize() );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode ObjectMatcher :: fileExecute ()
{
  // everything that needs to be done exactly once for every
  // single file, e.g. collect list of all lumi-blocks processed

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode ObjectMatcher :: changeInput ( bool /*firstFile*/ )
{
  // everything that needs to be done when input files change,
  // e.g. resetting branch addresses on trees; not needed if
  // using D3PDReader or similar service...

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode ObjectMatcher :: initialize ()
{
  // everything that needs to be done after first input file
  // connected and before first event processed, e.g. create
  // additional histograms based on variables available in input files;
  // can also create all histograms + trees here, but note this method
  // doesn't get called if no events processed, so objects created
  // here won't be available in output if no input events

  ANA_MSG_INFO( "Initializing ObjectMatcher..." );

  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();

  // to handle more than one jet collection
  std::string token;
  std::istringstream ss_jet_containers( m_inJetContainerName );
  while( std::getline( ss_jet_containers, token, ' ' ) )
    m_inJetContainers.push_back( token );
  
  // check for input containers
  if ( m_inJetContainers.empty() ) {
    ANA_MSG_ERROR( "No input jet container(s) provided! Exiting." );
    return EL::StatusCode::FAILURE;
  }
  if ( m_inTrackPartContainerName.empty() ) {
    ANA_MSG_ERROR( "No input track particle container provided! Exiting." );
    return EL::StatusCode::FAILURE;
  }
  if ( m_inSecondaryVertexContainerName.empty() ) {
    ANA_MSG_ERROR( "No input secondary vertex container provided! Exiting." );
    return EL::StatusCode::FAILURE;
  }

  // initialize counters
  m_eventNumber = 0;
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode ObjectMatcher :: execute ()
{
  // everything that needs to be done on every single event,
  // e.g. read input variables, apply cuts, fill histos + trees;
  // here is where most of actual analysis will go...

  ANA_MSG_DEBUG( "Applying Jet-Object Matching..." );

  // retrieve containers
  const xAOD::JetContainer*           inTruthJets     = 0;
  const xAOD::JetContainer*           inTruthDarkJets = 0;
  const xAOD::TruthParticleContainer* inTruthParts    = 0;
  const xAOD::TrackParticleContainer* inTrackParts    = 0;
  const xAOD::TruthVertexContainer*   inTruthVerts    = 0;
  const xAOD::VertexContainer*        inSecVerts      = 0;
  
  ANA_MSG_DEBUG( "Getting input track particle container: " << m_inTrackPartContainerName );
  ANA_CHECK( HelperFunctions::retrieve( inTrackParts, m_inTrackPartContainerName, m_event, m_store, msg() ) );

  ANA_MSG_DEBUG( "Getting input secondary vertex container: " << m_inSecondaryVertexContainerName );
  ANA_CHECK( HelperFunctions::retrieve( inSecVerts, m_inSecondaryVertexContainerName, m_event, m_store, msg() ) );
  
  if ( isMC() ) {
    ANA_MSG_DEBUG( "Getting input truth jet container: " << m_inTruthJetContainerName );
    ANA_CHECK( HelperFunctions::retrieve( inTruthJets, m_inTruthJetContainerName, m_event, m_store, msg() ) );
  
    ANA_MSG_DEBUG( "Getting input truth dark jet container: " << m_inTruthDarkJetContainerName );
    ANA_CHECK( HelperFunctions::retrieve( inTruthDarkJets, m_inTruthDarkJetContainerName, m_event, m_store, msg() ) );

    ANA_MSG_DEBUG( "Getting input truth particle container: " << m_inTruthPartContainerName );
    ANA_CHECK( HelperFunctions::retrieve( inTruthParts, m_inTruthPartContainerName, m_event, m_store, msg() ) );
  
    ANA_MSG_DEBUG( "Getting input truth vertex container: " << m_inTruthVertexContainerName );
    ANA_CHECK( HelperFunctions::retrieve( inTruthVerts, m_inTruthVertexContainerName, m_event, m_store, msg() ) );
  }

  
  // intialize decorators
  for ( const auto& track : *inTrackParts ) {
    track->auxdecor<int>("ID")                                        = track->index();
    track->auxdecor<char>("isMatchedToTruthJet")                      = false;
    track->auxdecor<EJsHelper::JetLinkVector_t>("truthJetMatchLinks") = EJsHelper::JetLinkVector_t();
    track->auxdecor<std::vector<float>>("truthJetMatchDRs")           = std::vector<float>();
    track->auxdecor<char>("isMatchedToDarkJet")                       = false;
    track->auxdecor<EJsHelper::JetLinkVector_t>("darkJetMatchLinks")  = EJsHelper::JetLinkVector_t();
    track->auxdecor<std::vector<float>>("darkJetMatchDRs")            = std::vector<float>();
  }
  for ( const auto& secVtx : *inSecVerts ) {
    secVtx->auxdecor<int>("ID")                                        = secVtx->index();
    secVtx->auxdecor<char>("isMatchedToTruthJet")                      = false;
    secVtx->auxdecor<EJsHelper::JetLinkVector_t>("truthJetMatchLinks") = EJsHelper::JetLinkVector_t();
    secVtx->auxdecor<std::vector<float>>("truthJetMatchDRs")           = std::vector<float>();
    secVtx->auxdecor<char>("isMatchedToDarkJet")                       = false;
    secVtx->auxdecor<EJsHelper::JetLinkVector_t>("darkJetMatchLinks")  = EJsHelper::JetLinkVector_t();
    secVtx->auxdecor<std::vector<float>>("darkJetMatchDRs")            = std::vector<float>();
  }
  if ( isMC() ) {
    for ( const auto& truthJet : *inTruthJets )
      truthJet->auxdecor<int>("ID") = truthJet->index();
    for ( const auto& truthDarkJet : *inTruthDarkJets ) {
      truthDarkJet->auxdecor<int>("ID")              = truthDarkJet->index();
      truthDarkJet->auxdecor<char>("isTruthMatched") = false;
      truthDarkJet->auxdecor<int>("truthMatchID")    = AlgConsts::invalidInt;
      truthDarkJet->auxdecor<double>("truthMatchDR") = AlgConsts::invalidFloat;
    }
    for ( const auto& truthPart : *inTruthParts ) {
      truthPart->auxdecor<int>("ID")                                        = truthPart->index();
      truthPart->auxdecor<char>("isMatchedToTruthJet")                      = false;
      truthPart->auxdecor<EJsHelper::JetLinkVector_t>("truthJetMatchLinks") = EJsHelper::JetLinkVector_t();
      truthPart->auxdecor<std::vector<float>>("truthJetMatchDRs")           = std::vector<float>();
      truthPart->auxdecor<char>("isMatchedToDarkJet")                       = false;
      truthPart->auxdecor<EJsHelper::JetLinkVector_t>("darkJetMatchLinks")  = EJsHelper::JetLinkVector_t();
      truthPart->auxdecor<std::vector<float>>("darkJetMatchDRs")            = std::vector<float>();
    }
    for ( const auto& truthVtx : *inTruthVerts ) {
      truthVtx->auxdecor<int>("ID")                                                              = truthVtx->index();
      truthVtx->auxdecor<char>("isMatchedToTruthJet")                                            = false;
      truthVtx->auxdecor<EJsHelper::JetLinkVector_t>("truthJetMatchLinks")                       = EJsHelper::JetLinkVector_t();
      truthVtx->auxdecor<std::vector<float>>("truthJetMatchDRs")                                 = std::vector<float>();
      truthVtx->auxdecor<char>("isMatchedToDarkJet")                                             = false;
      truthVtx->auxdecor<EJsHelper::JetLinkVector_t>("darkJetMatchLinks")                        = EJsHelper::JetLinkVector_t();
      truthVtx->auxdecor<std::vector<float>>("darkJetMatchDRs")                                  = std::vector<float>();
      truthVtx->auxdecor<char>("isCloseToSecondaryVertex")                                       = false;
      truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("closeSecondaryVertexLinks")             = EJsHelper::VertexLinkVector_t();
      truthVtx->auxdecor<std::vector<float>>("closeSecondaryVertexDists")                        = std::vector<float>();
      truthVtx->auxdecor<char>("isClosestToSecondaryVertex")                                     = false;
      truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("closestSecondaryVertexLinks")           = EJsHelper::VertexLinkVector_t();
      truthVtx->auxdecor<std::vector<float>>("closestSecondaryVertexDists")                      = std::vector<float>();
      truthVtx->auxdecor<char>("isLinkedToSecondaryVertex")                                      = false;
      truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("linkedSecondaryVertexLinks")            = EJsHelper::VertexLinkVector_t();
      truthVtx->auxdecor<std::vector<float>>("linkedSecondaryVertexScores")                      = std::vector<float>();
      truthVtx->auxdecor<char>("isMaxlinkedToSecondaryVertex")                                   = false;
      truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("maxlinkedSecondaryVertexLinks")         = EJsHelper::VertexLinkVector_t();
      truthVtx->auxdecor<std::vector<float>>("maxlinkedSecondaryVertexScores")                   = std::vector<float>();
      truthVtx->auxdecor<char>("isLinkedParentToSecondaryVertex")                                = false;
      truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("linkedParentSecondaryVertexLinks")      = EJsHelper::VertexLinkVector_t();
      truthVtx->auxdecor<std::vector<float>>("linkedParentSecondaryVertexScores")                = std::vector<float>();
      truthVtx->auxdecor<char>("isMaxlinkedParentToSecondaryVertex")                             = false;
      truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("maxlinkedParentSecondaryVertexLinks")   = EJsHelper::VertexLinkVector_t();
      truthVtx->auxdecor<std::vector<float>>("maxlinkedParentSecondaryVertexScores")             = std::vector<float>();
    }
  }


  // match tracks to reco secondary vertices
  matchTracksToSecVerts( inSecVerts, inTrackParts );


  // do matching to truth objects
  if ( isMC() ) {
    
    // match tracks to truth particles
    matchTracksToTruthParts( inTruthParts, inTrackParts );

    // match truth vertices to reco secondary vertices
    matchCloseTruthToSecVerts( inSecVerts, inTruthVerts );
    matchLinkedTruthToSecVerts( inSecVerts, inTruthVerts );

    // match truth dark jets to truth jets
    matchTruthJets( inTruthJets, inTruthDarkJets, TRUTH, DARK, "" );

    // match truth vertices to truth (dark) jets
    matchTruthVertsToJets( inTruthJets,     inTruthVerts, TRUTH, "" );
    matchTruthVertsToJets( inTruthDarkJets, inTruthVerts, DARK,  "" );

    // match reco secondary vertices to truth (dark) jets
    matchSecVertsToJets( inTruthJets,     inSecVerts, TRUTH, "" );
    matchSecVertsToJets( inTruthDarkJets, inSecVerts, DARK,  "" );

    // match truth particles to truth (dark) jets
    matchTruthPartsToJets( inTruthJets,     inTruthParts, TRUTH, "" );
    matchTruthPartsToJets( inTruthDarkJets, inTruthParts, DARK,  "" );
    
    // match tracks to truth (dark) jets
    matchTracksToJets( inTruthJets,     inTrackParts, TRUTH, "" );
    matchTracksToJets( inTruthDarkJets, inTrackParts, DARK,  "" );

  }
  

  // do matching for reco jets
  // if input comes from xAOD, or not running systematics...
  if ( m_inputAlgo.empty() ) {
    
    // get jet container(s)
    for ( size_t i = 0; i != m_inJetContainers.size(); ++i ) {

      const xAOD::JetContainer* inJets = 0;
      
      // skip jet container if not available
      if ( !HelperFunctions::isAvailable<xAOD::JetContainer>( m_inJetContainers.at(i), m_event, m_store, msg() ) ) {
	ANA_MSG_DEBUG( "Input jet container, '" << m_inJetContainers.at(i) << "', is not available. Skipping..." );
	continue;
      }	
      ANA_MSG_DEBUG( "Getting input jet container: " << m_inJetContainers.at(i) );
      ANA_CHECK( HelperFunctions::retrieve( inJets, m_inJetContainers.at(i), m_event, m_store, msg() ) );

      // initialize decorators
      for ( const auto& jet : *inJets )
	jet->auxdecor<int>("ID") = jet->index();

      // set jet-string
      std::string jetStr = "";
      if      ( m_inJetContainers.at(i).find("EMTopo") != std::string::npos ) jetStr = "EMTopo";
      else if ( m_inJetContainers.at(i).find("PFlow")  != std::string::npos ) jetStr = "PFlow";

      if ( isMC() ) {
	// match truth (dark) jets to reco jets
	matchTruthJets( inJets, inTruthJets,     RECO, TRUTH, jetStr );
	matchTruthJets( inJets, inTruthDarkJets, RECO, DARK,  jetStr );
	
	// match truth particles to reco jets
	matchTruthPartsToJets( inJets, inTruthParts, RECO, jetStr );
	
	// match truth vertices to reco jets
	matchTruthVertsToJets( inJets, inTruthVerts, RECO, jetStr );
      }
    
      // match reco secondary vertices to reco jets
      matchSecVertsToJets( inJets, inSecVerts, RECO, jetStr );
      
      // match tracks to reco jets
      matchTracksToJets( inJets, inTrackParts, RECO, jetStr );
      
    } // end loop over jet containers
    
  }
  // otherwise, get list of systematics to run over
  else {
    
    // get vector of string giving syst names of upstream algo from TStore
    std::vector<std::string>* systNames = 0;
    ANA_CHECK( HelperFunctions::retrieve( systNames, m_inputAlgo, 0, m_store, msg() ) );

    // loop over systematics
    for ( const auto& systName : *systNames ) {

      // get jet container(s)
      for ( size_t i = 0; i != m_inJetContainers.size(); ++i ) {

	const xAOD::JetContainer* inJets = 0;

	if ( i == m_jetSystsContainerIndex || systName.empty() ) { // only run systs for specified container
	  // skip jet container if not available
	  if ( !HelperFunctions::isAvailable<xAOD::JetContainer>( m_inJetContainers.at(i) + systName, m_event, m_store, msg() ) ) {
	    ANA_MSG_DEBUG( "Input jet container, '" << m_inJetContainers.at(i) + systName << "', is not available. Skipping..." );
	    continue;
	  }
	  ANA_MSG_DEBUG( "Getting input jet container: " << m_inJetContainers.at(i) + systName );
	  ANA_CHECK( HelperFunctions::retrieve( inJets, m_inJetContainers.at(i) + systName, m_event, m_store, msg() ) );

	  // initialize decorators
	  for ( const auto& jet : *inJets )
	    jet->auxdecor<int>("ID") = jet->index();

	  // set jet-string
	  std::string jetStr = "";
	  if      ( m_inJetContainers.at(i).find("EMTopo") != std::string::npos ) jetStr = "EMTopo";
	  else if ( m_inJetContainers.at(i).find("PFlow")  != std::string::npos ) jetStr = "PFlow";
      
	  if ( isMC() ) {
	    // match truth (dark) jets to reco jets
	    matchTruthJets( inJets, inTruthJets,     RECO, TRUTH, jetStr + systName );
	    matchTruthJets( inJets, inTruthDarkJets, RECO, DARK,  jetStr + systName );

	    // match truth particles to reco jets
	    matchTruthPartsToJets( inJets, inTruthParts, RECO, jetStr + systName );
	    
	    // match truth vertices to reco jets
	    matchTruthVertsToJets( inJets, inTruthVerts, RECO, jetStr + systName ); 	
	  }
	
	  // match reco secondary vertices to reco jets
	  matchSecVertsToJets( inJets, inSecVerts, RECO, jetStr + systName );
	  
	  // match tracks to reco jets
	  matchTracksToJets( inJets, inTrackParts, RECO, jetStr + systName );

	}
	
      } // end loop over input jet containers
      
    } // end loop over systematics
    
  }

  // look what we have in TStore
  if ( msgLvl( MSG::VERBOSE ) ) m_store->print();

  ++m_eventNumber;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode ObjectMatcher :: postExecute ()
{
  // everything that need to be done after main event processing;
  // mainly used in implementing NTupleSvc

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode ObjectMatcher :: finalize ()
{
  // mirror image of initialize(); gets called after last event
  // processed on worker node; allows finishing up objects created
  // in initialize() before they're written to disk; only gets
  // called on worker nodes that processed input events

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode ObjectMatcher :: histFinalize ()
{
  // mirror image of histInitialize(); gets called after last event
  // processed on worker node; allows finishing up objects created in
  // histInitialize() before they're written to disk; gets called on
  // all worker nodes regardless of whether they processed input events

  ANA_CHECK( xAH::Algorithm::algFinalize() );

  return EL::StatusCode::SUCCESS;
}



void ObjectMatcher :: matchTruthJets ( const xAOD::JetContainer* jets,
				       const xAOD::JetContainer* matchJets,
				       const enum jetType& jet_type,
				       const enum jetType& matchJet_type,
				       const std::string jet_string )
{
  // delta-R match truth (dark) jets to (truth) jets
  
  // set decorator variable names
  std::string decor_isMatched;
  std::string decor_isMatchedID;
  std::string decor_isMatchedDR;
  std::string decor_hasMatch;
  std::string decor_matchLink;
  std::string decor_matchID;
  std::string decor_matchDR;
  std::string decor_noMatchIDs;
  std::string decor_noMatchDRs;

  if ( jet_type == TRUTH ) {
    decor_isMatched   = "isTruthMatched";
    decor_isMatchedID = "truthMatchID";
    decor_isMatchedDR = "truthMatchDR";
  }
  else if ( jet_type == RECO ) {
    decor_isMatched   = "isRecoMatched";
    decor_isMatchedID = "recoMatchID";
    decor_isMatchedDR = "recoMatchDR";
    if ( !jet_string.empty() )
      decor_isMatched += jet_string;
    // loop over matchJets + initialize decorators for all in container
    for ( const auto& matchJet : *matchJets ) {
      matchJet->auxdecor<char>(decor_isMatched)     = false;
      matchJet->auxdecor<int>(decor_isMatchedID)    = AlgConsts::invalidInt;
      matchJet->auxdecor<double>(decor_isMatchedDR) = AlgConsts::invalidFloat;
    }
  }
  
  if ( matchJet_type == TRUTH ) {
    decor_hasMatch   = "hasTruthJetMatch";
    decor_matchLink  = "truthJetMatchLink";
    decor_matchID    = "truthJetMatchID";
    decor_matchDR    = "truthJetMatchDR";
    decor_noMatchIDs = "truthJetNoMatchIDs";
    decor_noMatchDRs = "truthJetNoMatchDRs";
  }
  else if ( matchJet_type == DARK ) {
    decor_hasMatch   = "hasDarkJetMatch";
    decor_matchLink  = "darkJetMatchLink";
    decor_matchID    = "darkJetMatchID";
    decor_matchDR    = "darkJetMatchDR";
    decor_noMatchIDs = "darkJetNoMatchIDs";
    decor_noMatchDRs = "darkJetNoMatchDRs";
  }
  
  // loop over jets
  for ( const auto& jet : *jets ) {

    bool               jetHasMatch = false;
    const xAOD::Jet*   jetMatch    = 0;
    int                jetMatchID  = -1;
    double             jetMatchDR  = AlgConsts::invalidFloat;
    std::vector<int>   jetNoMatchIDs;
    std::vector<float> jetNoMatchDRs;
    
    // loop over matchJets to match to jets
    for ( const auto& matchJet : *matchJets ) {
      
      // skip matchJet if already matched to jet...
      if ( matchJet->auxdecor<char>(decor_isMatched) ) continue;

      // calculate dR b/w jet + matchJet and look for match
      double dR = EJsHelper::deltaR( jet->eta(), matchJet->eta(), jet->phi(), matchJet->phi() );
      if ( dR < m_jet_matchRadius ) { // first match in high-pt order
	matchJet->auxdecor<char>(decor_isMatched)     = true;
	matchJet->auxdecor<int>(decor_isMatchedID)    = jet->auxdataConst<int>("ID");
	matchJet->auxdecor<double>(decor_isMatchedDR) = dR;
	jetHasMatch = true;
	jetMatch    = matchJet;
	jetMatchID  = matchJet->auxdataConst<int>("ID");
	jetMatchDR  = dR;
	break; // match found --> leave matchJet loop + go to next jet
      }
      else {
	jetNoMatchIDs .push_back( matchJet->auxdataConst<int>("ID") );
	jetNoMatchDRs .push_back( dR );
      }
      
    } // end loop over matchJets

    if ( jetMatch ) {
      EJsHelper::JetLink_t jetMatchLink( jetMatch, *matchJets );
      jet->auxdecor<EJsHelper::JetLink_t>(decor_matchLink) = jetMatchLink;
    }
    jet->auxdecor<char>(decor_hasMatch)  = jetHasMatch;
    jet->auxdecor<int>(decor_matchID)    = jetMatchID;
    jet->auxdecor<double>(decor_matchDR) = jetMatchDR;
    
    jet->auxdecor<std::vector<int>>(decor_noMatchIDs)   = jetNoMatchIDs;
    jet->auxdecor<std::vector<float>>(decor_noMatchDRs) = jetNoMatchDRs;
    
  } // end loop over jets
  
} // end matchTruthJets



void ObjectMatcher :: matchTruthVertsToJets ( const xAOD::JetContainer* jets,
					      const xAOD::TruthVertexContainer* truthVerts,
					      const enum jetType& jet_type,
					      const std::string jet_string )
{
  // delta-R match truth vertices to jets

  // set jet-container / decorator variable names
  std::string jetContainer;
  std::string decor_tvIsJetMatched;
  std::string decor_tvJetMatchLinks;
  std::string decor_tvJetMatchDRs;
  if      ( jet_type == TRUTH ) {
    jetContainer          = m_inTruthJetContainerName;
    decor_tvIsJetMatched  = "isMatchedToTruthJet";
    decor_tvJetMatchLinks = "truthJetMatchLinks";
    decor_tvJetMatchDRs   = "truthJetMatchDRs";
  }
  else if ( jet_type == DARK  ) {
    jetContainer          = m_inTruthDarkJetContainerName;
    decor_tvIsJetMatched  = "isMatchedToDarkJet";
    decor_tvJetMatchLinks = "darkJetMatchLinks";
    decor_tvJetMatchDRs   = "darkJetMatchDRs";
  }
  else if ( jet_type == RECO  ) {
    jetContainer          = m_inJetContainerName;
    decor_tvIsJetMatched  = "isMatchedToRecoJet";
    decor_tvJetMatchLinks = "recoJetMatchLinks";
    decor_tvJetMatchDRs   = "recoJetMatchDRs";
    if ( !jet_string.empty() ) {
      decor_tvIsJetMatched  += "_" + jet_string;
      decor_tvJetMatchLinks += "_" + jet_string;
      decor_tvJetMatchDRs   += "_" + jet_string;
    }
    // loop over truthVerts + initialize decorators for all in container
    for ( const auto& truthVtx : *truthVerts ) {
      truthVtx->auxdecor<char>(decor_tvIsJetMatched)                        = false;
      truthVtx->auxdecor<EJsHelper::JetLinkVector_t>(decor_tvJetMatchLinks) = EJsHelper::JetLinkVector_t();
      truthVtx->auxdecor<std::vector<float>>(decor_tvJetMatchDRs)           = std::vector<float>();
    }
  }

  // map matched truth vertices to jet indices and dRs b/w them
  std::map<const xAOD::TruthVertex*, std::vector<int>>   matchedTruthVerts_index;
  std::map<const xAOD::TruthVertex*, std::vector<float>> matchedTruthVerts_dR;
    
  // loop over jets
  for ( const auto& jet : *jets ) {

    EJsHelper::TruthVertexLinkVector_t matchedTVLinks;
    std::vector<float>                 matched_dR;
    double jet_radius = jet->getSizeParameter();
    
    // loop over truth vertices
    for ( size_t v = 0; v != truthVerts->size(); ++v ) {
      const auto* vtx = truthVerts->at(v);
      double dR = EJsHelper::deltaR( jet->eta(), vtx->eta(), jet->phi(), vtx->phi() );
      if ( dR < jet_radius ) {
	matchedTruthVerts_index[vtx] .push_back( jet->index() );
	matchedTruthVerts_dR[vtx]    .push_back( dR );
	EJsHelper::TruthVertexLink_t link( m_inTruthVertexContainerName, v );
	matchedTVLinks .push_back( link );
	matched_dR     .push_back( dR );
      }
    } // end loop over truth vertices

    // decorate jets w/ matched truth vertices + dRs b/w them
    jet->auxdecor<EJsHelper::TruthVertexLinkVector_t>("matchedTruthVertexLinks") = matchedTVLinks;
    jet->auxdecor<std::vector<float>>("matchedTruthVertex_dR")                   = matched_dR;
    
  } // end loop over jets

  // loop over matched truth vertices and save jet links + dRs
  for ( const auto& matchedTV_index : matchedTruthVerts_index ) {
    const auto* vtx = matchedTV_index.first;   
    std::vector<int> jetIndices = matchedTV_index.second;
    EJsHelper::JetLinkVector_t jetlinkvector;
    for ( size_t i = 0; i != jetIndices.size(); ++i ) {
      EJsHelper::JetLink_t jetlink( jetContainer, jetIndices.at(i) );
      jetlinkvector .push_back( jetlink );
    }
    vtx->auxdecor<char>(decor_tvIsJetMatched) = true;
    vtx->auxdecor<EJsHelper::JetLinkVector_t>(decor_tvJetMatchLinks) = jetlinkvector;
  }
  for ( const auto& matchedTV_dR : matchedTruthVerts_dR ) {
    const auto* vtx = matchedTV_dR.first;
    vtx->auxdecor<std::vector<float>>(decor_tvJetMatchDRs) = matchedTV_dR.second;
  }
  
} // end matchTruthVertsToJets



void ObjectMatcher :: matchSecVertsToJets ( const xAOD::JetContainer* jets,
					    const xAOD::VertexContainer* secVerts,
					    const enum jetType& jet_type, 
					    const std::string jet_string )
{
  // delta-R match reco secondary vertices to jets

  // set jet-container / decorator variable names
  std::string jetContainer;
  std::string decor_dvIsJetMatched;
  std::string decor_dvJetMatchLinks;
  std::string decor_dvJetMatchDRs;
  if      ( jet_type == TRUTH ) {
    jetContainer          = m_inTruthJetContainerName;
    decor_dvIsJetMatched  = "isMatchedToTruthJet";
    decor_dvJetMatchLinks = "truthJetMatchLinks";
    decor_dvJetMatchDRs   = "truthJetMatchDRs";
  }
  else if ( jet_type == DARK  ) {
    jetContainer          = m_inTruthDarkJetContainerName;
    decor_dvIsJetMatched  = "isMatchedToDarkJet";
    decor_dvJetMatchLinks = "darkJetMatchLinks";
    decor_dvJetMatchDRs   = "darkJetMatchDRs";
  }
  else if ( jet_type == RECO  ) {
    jetContainer          = m_inJetContainerName;
    decor_dvIsJetMatched  = "isMatchedToRecoJet";
    decor_dvJetMatchLinks = "recoJetMatchLinks";
    decor_dvJetMatchDRs   = "recoJetMatchDRs";
    if ( !jet_string.empty() ) {
      decor_dvIsJetMatched  += "_" + jet_string;
      decor_dvJetMatchLinks += "_" + jet_string;
      decor_dvJetMatchDRs   += "_" + jet_string;
    }
    // loop over truthVerts + initialize decorators for all in container
    for ( const auto& secVtx : *secVerts ) {
      secVtx->auxdecor<char>(decor_dvIsJetMatched)                        = false;
      secVtx->auxdecor<EJsHelper::JetLinkVector_t>(decor_dvJetMatchLinks) = EJsHelper::JetLinkVector_t();
      secVtx->auxdecor<std::vector<float>>(decor_dvJetMatchDRs)           = std::vector<float>();
    }
  }

  // map matched secondary vertices to jet indices and dRs b/w them
  std::map<const xAOD::Vertex*, std::vector<int>>   matchedSecVerts_index;
  std::map<const xAOD::Vertex*, std::vector<float>> matchedSecVerts_dR;

  // loop over jets
  for ( const auto& jet : *jets ) {
    
    EJsHelper::VertexLinkVector_t matchedDVLinks;
    std::vector<float>            matched_dR;
    double jet_radius = jet->getSizeParameter();

    // loop over secondary vertices
    for ( size_t v = 0; v != secVerts->size(); ++v ) {
      
      const auto* vtx = secVerts->at(v);

      // get vertex eta, phi from four-momentum
      TLorentzVector vtxP4;
      // grab 4-mom from decorator, if available
      if ( vtx->isAvailable<TLorentzVector>("sumP4") )
	vtxP4 = vtx->auxdataConst<TLorentzVector>("sumP4");
      // otherwise, calculate from filtered tracks
      else { 
	std::vector<const xAOD::TrackParticle*> filteredTracks;
	EJsHelper::getFilteredTracks( vtx, filteredTracks );
	vtxP4 = VsiBonsai::sumP4( filteredTracks );
      }

      double vtxEta = vtxP4.Eta();
      double vtxPhi = vtxP4.Phi();
      
      double dR = EJsHelper::deltaR( jet->eta(), vtxEta, jet->phi(), vtxPhi );
      
      if ( dR < jet_radius ) {
	matchedSecVerts_index[vtx] .push_back( jet->index() );
	matchedSecVerts_dR[vtx]    .push_back( dR );
    	EJsHelper::VertexLink_t link( m_inSecondaryVertexContainerName, v );
    	matchedDVLinks .push_back( link );
    	matched_dR     .push_back( dR );
      }
      
    } // end loop over secondary vertices

    // decorate jets w/ matched secondary vertices + dRs b/w them
    jet->auxdecor<EJsHelper::VertexLinkVector_t>("matchedSecondaryVertexLinks") = matchedDVLinks;
    jet->auxdecor<std::vector<float>>("matchedSecondaryVertex_dR")              = matched_dR;
    
  } // end loop over jets

  // loop over matched secondary vertices and save jet links + dRs
  for ( const auto& matchedDV_index : matchedSecVerts_index ) {
    const auto* vtx = matchedDV_index.first;
    std::vector<int> jetIndices = matchedDV_index.second;
    EJsHelper::JetLinkVector_t jetlinkvector;
    for ( size_t i = 0; i != jetIndices.size(); ++i ) {
      EJsHelper::JetLink_t jetlink( jetContainer, jetIndices.at(i) );
      jetlinkvector .push_back( jetlink );
    }
    vtx->auxdecor<char>(decor_dvIsJetMatched) = true;
    vtx->auxdecor<EJsHelper::JetLinkVector_t>(decor_dvJetMatchLinks) = jetlinkvector;
  }
  for ( const auto& matchedDV_dR : matchedSecVerts_dR ) {
    const auto* vtx = matchedDV_dR.first;
    vtx->auxdecor<std::vector<float>>(decor_dvJetMatchDRs) = matchedDV_dR.second;
  }

} // end matchSecVertsToJets



void ObjectMatcher :: matchTruthPartsToJets ( const xAOD::JetContainer* jets,
					      const xAOD::TruthParticleContainer* truthParts,
					      const enum jetType& jet_type,
					      const std::string jet_string )
{
  // delta-R match truth particles to jets

  // set jet-container / decorator variable names
  std::string jetContainer;
  std::string decor_tpIsJetMatched;
  std::string decor_tpJetMatchLinks;
  std::string decor_tpJetMatchDRs;
  if      ( jet_type == TRUTH ) {
    jetContainer          = m_inTruthJetContainerName;
    decor_tpIsJetMatched  = "isMatchedToTruthJet";
    decor_tpJetMatchLinks = "truthJetMatchLinks";
    decor_tpJetMatchDRs   = "truthJetMatchDRs";
  }
  else if ( jet_type == DARK  ) {
    jetContainer          = m_inTruthDarkJetContainerName;
    decor_tpIsJetMatched  = "isMatchedToDarkJet";
    decor_tpJetMatchLinks = "darkJetMatchLinks";
    decor_tpJetMatchDRs   = "darkJetMatchDRs";
  }
  else if ( jet_type == RECO  ) {
    jetContainer          = m_inJetContainerName;
    decor_tpIsJetMatched  = "isMatchedToRecoJet";
    decor_tpJetMatchLinks = "recoJetMatchLinks";
    decor_tpJetMatchDRs   = "recoJetMatchDRs";
    if ( !jet_string.empty() ) {
      decor_tpIsJetMatched  += "_" + jet_string;
      decor_tpJetMatchLinks += "_" + jet_string;
      decor_tpJetMatchDRs   += "_" + jet_string;
    }
    // loop over truthParts + initialize decorators for all in container
    for ( const auto& truthPart : *truthParts ) {
      truthPart->auxdecor<char>(decor_tpIsJetMatched)                        = false;
      truthPart->auxdecor<EJsHelper::JetLinkVector_t>(decor_tpJetMatchLinks) = EJsHelper::JetLinkVector_t();
      truthPart->auxdecor<std::vector<float>>(decor_tpJetMatchDRs)           = std::vector<float>();
    }
  }

  // map matched truth particles to jet indices and dRs b/w them
  std::map<const xAOD::TruthParticle*, std::vector<int>>   matchedTruthParts_index;
  std::map<const xAOD::TruthParticle*, std::vector<float>> matchedTruthParts_dR;

  // loop over jets
  for ( const auto& jet : *jets ) {

    EJsHelper::TruthParticleLinkVector_t matchedTruthPartLinks;
    std::vector<float>                   matched_dR;
    double jet_radius = jet->getSizeParameter();

    // loop over truth particles
    for ( size_t t = 0; t != truthParts->size(); ++t ) {
      const auto* tp = truthParts->at(t);
      double dR = EJsHelper::deltaR( jet->eta(), tp->eta(), jet->phi(), tp->phi() );
      if ( dR < jet_radius ) {
	matchedTruthParts_index[tp] .push_back( jet->index() );
	matchedTruthParts_dR[tp]    .push_back( dR );
	EJsHelper::TruthParticleLink_t link( m_inTruthPartContainerName, t );
	matchedTruthPartLinks .push_back( link );
	matched_dR            .push_back( dR );
      }
    } // end loop over truth particles

    // decorate jets w/ matched truth particles + dRs b/w them
    jet->auxdecor<EJsHelper::TruthParticleLinkVector_t>("matchedTruthParticleLinks") = matchedTruthPartLinks;
    jet->auxdecor<std::vector<float>>("matchedTruthParticle_dR")                     = matched_dR;
    
  } // end loop over jets

  // loop over matched truth particles and save jet links + dRs
  for ( const auto& matchedTP_index : matchedTruthParts_index ) {
    const auto* tp = matchedTP_index.first;   
    std::vector<int> jetIndices = matchedTP_index.second;
    EJsHelper::JetLinkVector_t jetlinkvector;
    for ( size_t i = 0; i != jetIndices.size(); ++i ) {
      EJsHelper::JetLink_t jetlink( jetContainer, jetIndices.at(i) );
      jetlinkvector .push_back( jetlink );
    }
    tp->auxdecor<char>(decor_tpIsJetMatched) = true;
    tp->auxdecor<EJsHelper::JetLinkVector_t>(decor_tpJetMatchLinks) = jetlinkvector;
  }
  for ( const auto& matchedTP_dR : matchedTruthParts_dR ) {
    const auto* tp = matchedTP_dR.first;
    tp->auxdecor<std::vector<float>>(decor_tpJetMatchDRs) = matchedTP_dR.second;
  }
  
} // end matchTruthPartsToJets



void ObjectMatcher :: matchTracksToJets ( const xAOD::JetContainer* jets,
					  const xAOD::TrackParticleContainer* tracks,
					  const enum jetType& jet_type,
					  const std::string jet_string )
{
  // delta-R match tracks to jets

  // set jet-container / decorator variable names
  std::string jetContainer;
  std::string decor_trkIsJetMatched;
  std::string decor_trkJetMatchLinks;
  std::string decor_trkJetMatchDRs;
  if      ( jet_type == TRUTH ) {
    jetContainer           = m_inTruthJetContainerName;
    decor_trkIsJetMatched  = "isMatchedToTruthJet";
    decor_trkJetMatchLinks = "truthJetMatchLinks";
    decor_trkJetMatchDRs   = "truthJetMatchDRs";
  }
  else if ( jet_type == DARK  ) {
    jetContainer           = m_inTruthDarkJetContainerName;
    decor_trkIsJetMatched  = "isMatchedToDarkJet";
    decor_trkJetMatchLinks = "darkJetMatchLinks";
    decor_trkJetMatchDRs   = "darkJetMatchDRs";
  }
  else if ( jet_type == RECO  ) {
    jetContainer           = m_inJetContainerName;
    decor_trkIsJetMatched  = "isMatchedToRecoJet";
    decor_trkJetMatchLinks = "recoJetMatchLinks";
    decor_trkJetMatchDRs   = "recoJetMatchDRs";
    if ( !jet_string.empty() ) {
      decor_trkIsJetMatched  += "_" + jet_string;
      decor_trkJetMatchLinks += "_" + jet_string;
      decor_trkJetMatchDRs   += "_" + jet_string;
    }
    // loop over tracks + initialize decorators for all in container
    for ( const auto& track : *tracks ) {
      track->auxdecor<char>(decor_trkIsJetMatched)                        = false;
      track->auxdecor<EJsHelper::JetLinkVector_t>(decor_trkJetMatchLinks) = EJsHelper::JetLinkVector_t();
      track->auxdecor<std::vector<float>>(decor_trkJetMatchDRs)           = std::vector<float>();
    }
  }

  // map matched tracks to jet indices and dRs b/w them
  std::map<const xAOD::TrackParticle*, std::vector<int>>   matchedTracks_index;
  std::map<const xAOD::TrackParticle*, std::vector<float>> matchedTracks_dR;

  // loop over jets
  for ( const auto& jet : *jets ) {

    EJsHelper::TrackLinkVector_t matchedTrkLinks;
    std::vector<float>           matched_dR;
    double jet_radius = jet->getSizeParameter();

    // loop over tracks
    for ( size_t t = 0; t != tracks->size(); ++t ) {
      const auto* trk = tracks->at(t);
      double dR = EJsHelper::deltaR( jet->eta(), trk->eta(), jet->phi(), trk->phi() );
      if ( dR < jet_radius ) {
	matchedTracks_index[trk] .push_back( jet->index() );
	matchedTracks_dR[trk]    .push_back( dR );
	EJsHelper::TrackLink_t link( m_inTrackPartContainerName, t );
	matchedTrkLinks .push_back( link );
	matched_dR      .push_back( dR );
      }
    } // end loop over tracks

    // decorate jets w/ matched tracks + dRs b/w them
    jet->auxdecor<EJsHelper::TrackLinkVector_t>("matchedTrackLinks") = matchedTrkLinks;
    jet->auxdecor<std::vector<float>>("matchedTrack_dR")             = matched_dR;
    
  } // end loop over jets

  // loop over matched tracks and save jet links + dRs
  for ( const auto& matchedTrk_index : matchedTracks_index ) {
    const auto* trk = matchedTrk_index.first;   
    std::vector<int> jetIndices = matchedTrk_index.second;
    EJsHelper::JetLinkVector_t jetlinkvector;
    for ( size_t i = 0; i != jetIndices.size(); ++i ) {
      EJsHelper::JetLink_t jetlink( jetContainer, jetIndices.at(i) );
      jetlinkvector .push_back( jetlink );
    }
    trk->auxdecor<char>(decor_trkIsJetMatched) = true;
    trk->auxdecor<EJsHelper::JetLinkVector_t>(decor_trkJetMatchLinks) = jetlinkvector;
  }
  for ( const auto& matchedTrk_dR : matchedTracks_dR ) {
    const auto* trk = matchedTrk_dR.first;
    trk->auxdecor<std::vector<float>>(decor_trkJetMatchDRs) = matchedTrk_dR.second;
  }

} // end matchTracksToJets



void ObjectMatcher :: matchTracksToTruthParts ( const xAOD::TruthParticleContainer* parts,
						const xAOD::TrackParticleContainer* tracks )
{
  // reverse match tracks to truth particles using track truth links

  // loop over truth particles + initialize decorators for all in container
  for ( const auto& part : *parts ) {
    part->auxdecor<char>("isTrackMatch")            = false;
    part->auxdecor<double>("trackMatchProbability") = AlgConsts::invalidFloat;
  }
  
  // loop over tracks
  for ( const auto& trk : *tracks ) {
    const auto* tp = EJsHelper::getTruthPart( trk ); // get linked truth particle
    if ( !tp ) continue;
    tp->auxdecor<char>("isTrackMatch")            = true;
    tp->auxdecor<double>("trackMatchProbability") = trk->auxdataConst<float>("truthMatchProbability");
    
    EJsHelper::TrackLink_t trkLink( m_inTrackPartContainerName, trk->index() );
    tp->auxdecor<EJsHelper::TrackLink_t>("trackLink") = trkLink;
  } // end loop over tracks
  
} // end matchTracksToTruthParts



void ObjectMatcher :: matchTracksToSecVerts ( const xAOD::VertexContainer* secVerts,
					      const xAOD::TrackParticleContainer* tracks )
{
  // reverse match tracks to corresponding secondary vertices

  // loop over tracks + initialize decorators for all in container
  for ( const auto& trk : *tracks ) {
    trk->auxdecor<char>("isSecondaryVertexTrack") = false;
    trk->auxdecor<int>("secondaryVertexID")       = AlgConsts::invalidInt;
  }

  // loop over secondary vertices
  for ( const auto& secVtx : *secVerts ) {
    // get vertex tracks
    for ( size_t itrk = 0; itrk != secVtx->nTrackParticles(); ++itrk ) {
      const auto* trk = secVtx->trackParticle(itrk);
      if ( !trk ) continue;
      trk->auxdecor<char>("isSecondaryVertexTrack") = true;
      trk->auxdecor<int>("secondaryVertexID")       = secVtx->auxdataConst<int>("ID");
      EJsHelper::VertexLink_t secVtxLink( m_inSecondaryVertexContainerName, secVtx->index() );
      trk->auxdecor<EJsHelper::VertexLink_t>("secondaryVertexLink") = secVtxLink;
    }
  } // end loop over secondary vertices
  
} // end matchTracksToSecVerts



void ObjectMatcher :: matchCloseTruthToSecVerts ( const xAOD::VertexContainer* secVerts,
						  const xAOD::TruthVertexContainer* truthVerts )
{
  // match close truth vertices to reco secondary vertices (distance-based matching)
  // --> tentative strategy; may evolve (see VsiPerf efficiency processor) ...

  // map close(st) truth vertices to secondary vertex indices and distances b/w them
  std::map<const xAOD::TruthVertex*, std::vector<int>>   closeTruthVerts_index;
  std::map<const xAOD::TruthVertex*, std::vector<float>> closeTruthVerts_dist;
  std::map<const xAOD::TruthVertex*, std::vector<int>>   closestTruthVerts_index;
  std::map<const xAOD::TruthVertex*, std::vector<float>> closestTruthVerts_dist;

  // loop over secondary vertices
  for ( const auto& secVtx : *secVerts ) {

    TVector3 reco_pos( secVtx->x(), secVtx->y(), secVtx->z() );
    EJsHelper::TruthVertexLinkVector_t matchedTVLinks;
    std::vector<float>                 matchedTV_dist;
    const xAOD::TruthVertex* closestTruthVertex = 0;
    double closestTVDist = AlgConsts::maxValue;

    // loop over truth vertices
    for ( size_t tv = 0; tv != truthVerts->size(); ++tv ) {

      const auto* truthVtx = truthVerts->at(tv);

      // find distance b/w truth + secondary vertices
      TVector3 truth_pos( truthVtx->x(), truthVtx->y(), truthVtx->z() );
      double dist = ( reco_pos - truth_pos ).Mag();

      // save truth vertex as "close match" if w/in match-distance
      if ( dist < m_vtx_matchDist ) {
	closeTruthVerts_index[truthVtx] .push_back( secVtx->index() );
	closeTruthVerts_dist[truthVtx]  .push_back( dist );
	EJsHelper::TruthVertexLink_t link( m_inTruthVertexContainerName, tv );
	matchedTVLinks .push_back( link );
	matchedTV_dist .push_back( dist );
      }

      // look for closest truth vertex
      if ( dist < closestTVDist ) {
	closestTruthVertex = truthVtx;
	closestTVDist      = dist;
      }
      
    } // end loop over truth vertices

    closestTruthVerts_index[closestTruthVertex] .push_back( secVtx->index() );
    closestTruthVerts_dist[closestTruthVertex]  .push_back( closestTVDist );

    // decorate secondary vertices w/ close-matched and closest truth vertices + distances b/w them
    secVtx->auxdecor<EJsHelper::TruthVertexLinkVector_t>("closeMatchedTruthVertexLinks") = matchedTVLinks;
    secVtx->auxdecor<std::vector<float>>("closeMatchedTruthVertex_dist")                 = matchedTV_dist;

    if ( closestTruthVertex ) {
      EJsHelper::TruthVertexLink_t closestTVLink( closestTruthVertex, *truthVerts );
      secVtx->auxdecor<EJsHelper::TruthVertexLink_t>("closestTruthVertexLink") = closestTVLink;
    }
    secVtx->auxdecor<double>("closestTruthVertex_dist") = closestTVDist;
    
  } // end loop over secondary vertices

  // loop over close(st) truth vertices and save secondary vertex links + distances
  for ( const auto& closeTV_index : closeTruthVerts_index ) {
    const auto* truthVtx = closeTV_index.first;
    std::vector<int> secVtxIndices = closeTV_index.second;
    EJsHelper::VertexLinkVector_t secvtxlinkvector;
    for ( size_t i = 0; i != secVtxIndices.size(); ++i ) {
      EJsHelper::VertexLink_t secvtxlink( m_inSecondaryVertexContainerName, secVtxIndices.at(i) );
      secvtxlinkvector .push_back( secvtxlink );
    }
    truthVtx->auxdecor<char>("isCloseToSecondaryVertex") = true;
    truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("closeSecondaryVertexLinks") = secvtxlinkvector;
  }
  for ( const auto& closeTV_dist : closeTruthVerts_dist ) {
    const auto* truthVtx = closeTV_dist.first;
    truthVtx->auxdecor<std::vector<float>>("closeSecondaryVertexDists") = closeTV_dist.second;
  }
  
  for ( const auto& closestTV_index : closestTruthVerts_index ) {
    const auto* truthVtx = closestTV_index.first;
    std::vector<int> secVtxIndices = closestTV_index.second;
    EJsHelper::VertexLinkVector_t secvtxlinkvector;
    for ( size_t i = 0; i != secVtxIndices.size(); ++i ) {
      EJsHelper::VertexLink_t secvtxlink( m_inSecondaryVertexContainerName, secVtxIndices.at(i) );
      secvtxlinkvector .push_back( secvtxlink );
    }
    truthVtx->auxdecor<char>("isClosestToSecondaryVertex") = true;
    truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("closestSecondaryVertexLinks") = secvtxlinkvector;
  }
  for ( const auto& closestTV_dist : closestTruthVerts_dist ) {
    const auto* truthVtx = closestTV_dist.first;
    truthVtx->auxdecor<std::vector<float>>("closestSecondaryVertexDists") = closestTV_dist.second;
  }
  
} // end matchCloseVerts



void ObjectMatcher :: matchLinkedTruthToSecVerts ( const xAOD::VertexContainer* secVerts,
						   const xAOD::TruthVertexContainer* truthVerts )
{
  // match linked truth vertices to reco secondary vertices (track-truth-link-based matching)
  // --> tentative strategy; may evolve (see VsiPerf efficiency processor) ...

  // map (max)linked (parent) truth vertices to secondary vertex indices and scores
  std::map<const xAOD::TruthVertex*, std::vector<int>>   linkTruthVerts_index;
  std::map<const xAOD::TruthVertex*, std::vector<float>> linkTruthVerts_score;
  std::map<const xAOD::TruthVertex*, std::vector<int>>   maxlinkTruthVerts_index;
  std::map<const xAOD::TruthVertex*, std::vector<float>> maxlinkTruthVerts_score;
  std::map<const xAOD::TruthVertex*, std::vector<int>>   linkParentTruthVerts_index;
  std::map<const xAOD::TruthVertex*, std::vector<float>> linkParentTruthVerts_score;
  std::map<const xAOD::TruthVertex*, std::vector<int>>   maxlinkParentTruthVerts_index;
  std::map<const xAOD::TruthVertex*, std::vector<float>> maxlinkParentTruthVerts_score;

  // loop over secondary vertices
  for ( const auto& secVtx : *secVerts ) {

    // fill vector of filtered tracks
    std::vector<const xAOD::TrackParticle*> filteredTracks;
    EJsHelper::getFilteredTracks( secVtx, filteredTracks );

    // map all (parent) truth vertices linked from secondary vertex tracks + their pt-weighted scores
    std::map<const xAOD::TruthVertex*, double> linkedTruthVerts;
    std::map<const xAOD::TruthVertex*, double> linkedParentTruthVerts;

    double secVtxSumPt = 0;
    // grab scalar sum-pt from decorator, if available
    if ( secVtx->isAvailable<double>("scalarSumPt") )
      secVtxSumPt = secVtx->auxdataConst<double>("scalarSumPt");
    // otherwise, calculate from filtered tracks
    else
      secVtxSumPt = VsiBonsai::scalarSumPt( filteredTracks );

    // loop over filtered tracks --> get corresponding (parent) truth vertices + pt-weight
    for ( const auto& trk : filteredTracks ) {
      const auto* truthProdVtx = EJsHelper::getProdVtx( trk );
      if ( truthProdVtx )
	linkedTruthVerts[truthProdVtx] += fabs( trk->pt() / secVtxSumPt );
      const auto* truthParentProdVtx = EJsHelper::getParentProdVtx( trk );
      if ( truthParentProdVtx )
	linkedParentTruthVerts[truthParentProdVtx] += fabs( trk->pt() / secVtxSumPt );
    }

    // loop over linked truth vertices and save element links + scores
    EJsHelper::TruthVertexLinkVector_t linkedTVLinks;
    std::vector<float>                 linkedTV_score;
    for ( const auto& linkedTV : linkedTruthVerts ) {
      const auto* tv = linkedTV.first;
      linkTruthVerts_index[tv] .push_back( secVtx->index() );
      linkTruthVerts_score[tv] .push_back( linkedTV.second );
      EJsHelper::TruthVertexLink_t tvlink( tv, *truthVerts );
      linkedTVLinks  .push_back( tvlink );
      linkedTV_score .push_back( linkedTV.second );
    }
    // find highest-score truth vertex
    const xAOD::TruthVertex* maxlinkedTruthVertex = 0;
    double maxlinkedTVScore = AlgConsts::invalidFloat;
    if ( !linkedTruthVerts.empty() ) {
      auto linkedTruthVertsMax =
	std::max_element( linkedTruthVerts.begin(), linkedTruthVerts.end(),
			  []( const std::pair<const xAOD::TruthVertex*, double>& p1,
			      const std::pair<const xAOD::TruthVertex*, double>& p2 )
			  { return ( p1.second < p2.second ); } );
      maxlinkedTruthVertex = (*linkedTruthVertsMax).first;
      maxlinkedTVScore     = (*linkedTruthVertsMax).second;
      maxlinkTruthVerts_index[maxlinkedTruthVertex] .push_back( secVtx->index() );
      maxlinkTruthVerts_score[maxlinkedTruthVertex] .push_back( maxlinkedTVScore );
    }

    // loop over linked parent truth vertices + save element links + score
    EJsHelper::TruthVertexLinkVector_t linkedPTVLinks;
    std::vector<float>                 linkedPTV_score;
    for ( const auto& linkedPTV : linkedParentTruthVerts ) {
      const auto* ptv = linkedPTV.first;
      linkParentTruthVerts_index[ptv] .push_back( secVtx->index() );
      linkParentTruthVerts_score[ptv] .push_back( linkedPTV.second );
      EJsHelper::TruthVertexLink_t ptvlink( ptv, *truthVerts );
      linkedPTVLinks  .push_back( ptvlink );
      linkedPTV_score .push_back( linkedPTV.second );
    }
    // find highest-score parent truth vertex
    const xAOD::TruthVertex* maxlinkedParentTruthVertex = 0;
    double maxlinkedPTVScore = AlgConsts::invalidFloat;
    if ( !linkedParentTruthVerts.empty() ) {
      auto linkedParentTruthVertsMax =
	std::max_element( linkedParentTruthVerts.begin(), linkedParentTruthVerts.end(),
			  []( const std::pair<const xAOD::TruthVertex*, double>& p1,
			      const std::pair<const xAOD::TruthVertex*, double>& p2 )
			  { return ( p1.second < p2.second ); } );
      maxlinkedParentTruthVertex = (*linkedParentTruthVertsMax).first;
      maxlinkedPTVScore          = (*linkedParentTruthVertsMax).second;
      maxlinkParentTruthVerts_index[maxlinkedParentTruthVertex] .push_back( secVtx->index() );
      maxlinkParentTruthVerts_score[maxlinkedParentTruthVertex] .push_back( maxlinkedPTVScore );
    }
    
    // decorate secondary vertices w/ (max) linked (parent) truth vertices + their pt-weighted scores
    secVtx->auxdecor<EJsHelper::TruthVertexLinkVector_t>("trackLinkedTruthVertexLinks") = linkedTVLinks;
    secVtx->auxdecor<std::vector<float>>("trackLinkedTruthVertex_score")                = linkedTV_score;

    if ( maxlinkedTruthVertex ) {
      EJsHelper::TruthVertexLink_t maxlinkedTVLink( maxlinkedTruthVertex, *truthVerts );
      secVtx->auxdecor<EJsHelper::TruthVertexLink_t>("maxlinkedTruthVertexLink") = maxlinkedTVLink;
    }
    secVtx->auxdecor<double>("maxlinkedTruthVertex_score") = maxlinkedTVScore;

    secVtx->auxdecor<EJsHelper::TruthVertexLinkVector_t>("trackLinkedParentTruthVertexLinks") = linkedPTVLinks;
    secVtx->auxdecor<std::vector<float>>("trackLinkedParentTruthVertex_score")                = linkedPTV_score;

    if ( maxlinkedParentTruthVertex ) {
      EJsHelper::TruthVertexLink_t maxlinkedPTVLink( maxlinkedParentTruthVertex, *truthVerts );
      secVtx->auxdecor<EJsHelper::TruthVertexLink_t>("maxlinkedParentTruthVertexLink") = maxlinkedPTVLink;
    }
    secVtx->auxdecor<double>("maxlinkedParentTruthVertex_score") = maxlinkedPTVScore;

  } // end loop over secondary vertices

  // loop over (max)linked (parent) truth vertices and save secondary vertex links + scores
  for ( const auto& linkTV_index : linkTruthVerts_index ) {
    const auto* truthVtx = linkTV_index.first;
    std::vector<int> secVtxIndices = linkTV_index.second;
    EJsHelper::VertexLinkVector_t secvtxlinkvector;
    for ( size_t i = 0; i != secVtxIndices.size(); ++i ) {
      EJsHelper::VertexLink_t secvtxlink( m_inSecondaryVertexContainerName, secVtxIndices.at(i) );
      secvtxlinkvector .push_back( secvtxlink );
    }
    truthVtx->auxdecor<char>("isLinkedToSecondaryVertex") = true;
    truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("linkedSecondaryVertexLinks") = secvtxlinkvector;
  }
  for ( const auto& linkTV_score : linkTruthVerts_score ) {
    const auto* truthVtx = linkTV_score.first;
    truthVtx->auxdecor<std::vector<float>>("linkedSecondaryVertexScores") = linkTV_score.second;
  }

  for ( const auto& maxlinkTV_index : maxlinkTruthVerts_index ) {
    const auto* truthVtx = maxlinkTV_index.first;
    std::vector<int> secVtxIndices = maxlinkTV_index.second;
    EJsHelper::VertexLinkVector_t secvtxlinkvector;
    for ( size_t i = 0; i != secVtxIndices.size(); ++i ) {
      EJsHelper::VertexLink_t secvtxlink( m_inSecondaryVertexContainerName, secVtxIndices.at(i) );
      secvtxlinkvector .push_back( secvtxlink );
    }
    truthVtx->auxdecor<char>("isMaxlinkedToSecondaryVertex") = true;
    truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("maxlinkedSecondaryVertexLinks") = secvtxlinkvector;
  }
  for ( const auto& maxlinkTV_score : maxlinkTruthVerts_score ) {
    const auto* truthVtx = maxlinkTV_score.first;
    truthVtx->auxdecor<std::vector<float>>("maxlinkedSecondaryVertexScores") = maxlinkTV_score.second;
  }

  for ( const auto& linkPTV_index : linkParentTruthVerts_index ) {
    const auto* truthVtx = linkPTV_index.first;
    std::vector<int> secVtxIndices = linkPTV_index.second;
    EJsHelper::VertexLinkVector_t secvtxlinkvector;
    for ( size_t i = 0; i != secVtxIndices.size(); ++i ) {
      EJsHelper::VertexLink_t secvtxlink( m_inSecondaryVertexContainerName, secVtxIndices.at(i) );
      secvtxlinkvector .push_back( secvtxlink );
    }
    truthVtx->auxdecor<char>("isLinkedParentToSecondaryVertex") = true;
    truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("linkedParentSecondaryVertexLinks") = secvtxlinkvector;
  }
  for ( const auto& linkPTV_score : linkParentTruthVerts_score ) {
    const auto* truthVtx = linkPTV_score.first;
    truthVtx->auxdecor<std::vector<float>>("linkedParentSecondaryVertexScores") = linkPTV_score.second;
  }

  for ( const auto& maxlinkPTV_index : maxlinkParentTruthVerts_index ) {
    const auto* truthVtx = maxlinkPTV_index.first;
    std::vector<int> secVtxIndices = maxlinkPTV_index.second;
    EJsHelper::VertexLinkVector_t secvtxlinkvector;
    for ( size_t i = 0; i != secVtxIndices.size(); ++i ) {
      EJsHelper::VertexLink_t secvtxlink( m_inSecondaryVertexContainerName, secVtxIndices.at(i) );
      secvtxlinkvector .push_back( secvtxlink );
    }
    truthVtx->auxdecor<char>("isMaxlinkedParentToSecondaryVertex") = true;
    truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("maxlinkedParentSecondaryVertexLinks") = secvtxlinkvector;
  }
  for ( const auto& maxlinkPTV_score : maxlinkParentTruthVerts_score ) {
    const auto* truthVtx = maxlinkPTV_score.first;
    truthVtx->auxdecor<std::vector<float>>("maxlinkedParentSecondaryVertexScores") = maxlinkPTV_score.second;
  }

  
} // end matchLinkedVerts
