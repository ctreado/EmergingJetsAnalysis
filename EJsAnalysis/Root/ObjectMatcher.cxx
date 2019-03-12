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
    track->auxdecor<int>("ID") = track->index();
    track->auxdecor<char>("isMatchedToTruthJet") = false;
    track->auxdecor<int>("truthJetMatchID")      = AlgConsts::invalidInt;
    track->auxdecor<double>("truthJetMatchDR")   = AlgConsts::invalidFloat;
    track->auxdecor<char>("isMatchedToDarkJet")  = false;
    track->auxdecor<int>("darkJetMatchID")       = AlgConsts::invalidInt;
    track->auxdecor<double>("darkJetMatchDR")    = AlgConsts::invalidFloat;
  }
  for ( const auto& secVtx : *inSecVerts ) {
    secVtx->auxdecor<int>("ID") = secVtx->index();
    secVtx->auxdecor<char>("isMatchedToTruthJet") = false;
    secVtx->auxdecor<int>("truthJetMatchID")      = AlgConsts::invalidInt;
    secVtx->auxdecor<double>("truthJetMatchDR")   = AlgConsts::invalidFloat;
    secVtx->auxdecor<char>("isMatchedToDarkJet")  = false;
    secVtx->auxdecor<int>("darkJetMatchID")       = AlgConsts::invalidInt;
    secVtx->auxdecor<double>("darkJetMatchDR")    = AlgConsts::invalidFloat;
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
      truthPart->auxdecor<int>("ID") = truthPart->index();
      truthPart->auxdecor<char>("isMatchedToTruthJet") = false;
      truthPart->auxdecor<int>("truthJetMatchID")      = AlgConsts::invalidInt;
      truthPart->auxdecor<double>("truthJetMatchDR")   = AlgConsts::invalidFloat;
      truthPart->auxdecor<char>("isMatchedToDarkJet")  = false;
      truthPart->auxdecor<int>("darkJetMatchID")       = AlgConsts::invalidInt;
      truthPart->auxdecor<double>("darkJetMatchDR")    = AlgConsts::invalidFloat;
    }
    for ( const auto& truthVtx : *inTruthVerts ) {
      truthVtx->auxdecor<int>("ID")                                     = truthVtx->index();
      truthVtx->auxdecor<char>("isMatchedToTruthJet")                   = false;
      truthVtx->auxdecor<int>("truthJetMatchID")                        = AlgConsts::invalidInt;
      truthVtx->auxdecor<double>("truthJetMatchDR")                     = AlgConsts::invalidFloat;
      truthVtx->auxdecor<char>("isMatchedToDarkJet")                    = false;
      truthVtx->auxdecor<int>("darkJetMatchID")                         = AlgConsts::invalidInt;
      truthVtx->auxdecor<double>("darkJetMatchDR")                      = AlgConsts::invalidFloat;
      truthVtx->auxdecor<char>("isCloseToSecondaryVertex")              = false;
      truthVtx->auxdecor<int>("closeSecondaryVertexID")                 = AlgConsts::invalidInt;
      truthVtx->auxdecor<double>("closeSecondaryVertexDistance")        = AlgConsts::invalidFloat;
      truthVtx->auxdecor<char>("isClosestToSecondaryVertex")            = false;
      truthVtx->auxdecor<int>("closestSecondaryVertexID")               = AlgConsts::invalidInt;
      truthVtx->auxdecor<double>("closestSecondaryVertexDistance")      = AlgConsts::invalidFloat;
      truthVtx->auxdecor<char>("isLinkedToSecondaryVertex")             = false;
      truthVtx->auxdecor<int>("linkedSecondaryVertexID")                = AlgConsts::invalidInt;
      truthVtx->auxdecor<double>("linkedSecondaryVertexScore")          = AlgConsts::invalidFloat;
      truthVtx->auxdecor<char>("isMaxlinkedToSecondaryVertex")          = false;
      truthVtx->auxdecor<int>("maxlinkedSecondaryVertexID")             = AlgConsts::invalidInt;
      truthVtx->auxdecor<double>("maxlinkedSecondaryVertexScore")       = AlgConsts::invalidFloat;
      truthVtx->auxdecor<char>("isLinkedParentToSecondaryVertex")       = false; // prodTV of parent of tp linked to DV track
      truthVtx->auxdecor<int>("linkedParentSecondaryVertexID")          = AlgConsts::invalidInt;
      truthVtx->auxdecor<double>("linkedParentSecondaryVertexScore")    = AlgConsts::invalidFloat;
      truthVtx->auxdecor<char>("isMaxlinkedParentToSecondaryVertex")    = false;
      truthVtx->auxdecor<int>("maxlinkedParentSecondaryVertexID")       = AlgConsts::invalidInt;
      truthVtx->auxdecor<double>("maxlinkedParentSecondaryVertexScore") = AlgConsts::invalidFloat;
    }
  }


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

  // set decorator variable names
  std::string decor_tvIsMatched;
  std::string decor_tvMatchID;
  std::string decor_tvMatchDR;
  if      ( jet_type == TRUTH ) {
    decor_tvIsMatched = "isMatchedToTruthJet";
    decor_tvMatchID   = "truthJetMatchID";
    decor_tvMatchDR   = "truthJetMatchDR";
  }
  else if ( jet_type == DARK  ) {
    decor_tvIsMatched = "isMatchedToDarkJet";
    decor_tvMatchID   = "darkJetMatchID";
    decor_tvMatchDR   = "darkJetMatchDR";
  }
  else if ( jet_type == RECO  ) {
    decor_tvIsMatched = "isMatchedToRecoJet";
    decor_tvMatchID   = "recoJetMatchID";
    decor_tvMatchDR   = "recoJetMatchDR";
    if ( !jet_string.empty() ) {
      decor_tvIsMatched += "_" + jet_string;
      decor_tvMatchID   += "_" + jet_string;
      decor_tvMatchDR   += "_" + jet_string;
    }
    // loop over truthVerts + initialize decorators for all in container
    for ( const auto& truthVtx : *truthVerts ) {
      truthVtx->auxdecor<char>(decor_tvIsMatched) = false;
      truthVtx->auxdecor<int>(decor_tvMatchID)    = AlgConsts::invalidInt;
      truthVtx->auxdecor<double>(decor_tvMatchDR) = AlgConsts::invalidFloat;
    }
  }

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
	vtx->auxdecor<char>(decor_tvIsMatched) = true;
	vtx->auxdecor<int>(decor_tvMatchID)    = jet->auxdataConst<int>("ID");
	vtx->auxdecor<double>(decor_tvMatchDR) = dR;
	EJsHelper::TruthVertexLink_t link( m_inTruthVertexContainerName, v );
	matchedTVLinks .push_back( link );
	matched_dR     .push_back( dR );
      }
    } // end loop over truth vertices

    // decorate jets w/ matched truth vertices + dRs b/w them
    jet->auxdecor<EJsHelper::TruthVertexLinkVector_t>("matchedTruthVertexLinks") = matchedTVLinks;
    jet->auxdecor<std::vector<float>>("matchedTruthVertex_dR")                   = matched_dR;
    
  } // end loop over jets
  
} // end matchTruthVertsToJets



void ObjectMatcher :: matchSecVertsToJets ( const xAOD::JetContainer* jets,
					    const xAOD::VertexContainer* secVerts,
					    const enum jetType& jet_type, 
					    const std::string jet_string )
{
  // delta-R match reco secondary vertices to jets

  // set decorator variable names
  std::string decor_dvIsMatched;
  std::string decor_dvMatchID;
  std::string decor_dvMatchDR;
  if      ( jet_type == TRUTH ) {
    decor_dvIsMatched = "isMatchedToTruthJet";
    decor_dvMatchID   = "truthJetMatchID";
    decor_dvMatchDR   = "truthJetMatchDR";
  }
  else if ( jet_type == DARK  ) {
    decor_dvIsMatched = "isMatchedToDarkJet";
    decor_dvMatchID   = "darkJetMatchID";
    decor_dvMatchDR   = "darkJetMatchDR";
  }
  else if ( jet_type == RECO  ) {
    decor_dvIsMatched = "isMatchedToRecoJet";
    decor_dvMatchID   = "recoJetMatchID";
    decor_dvMatchDR   = "recoJetMatchDR";
    if ( !jet_string.empty() ) {
      decor_dvIsMatched += "_" + jet_string;
      decor_dvMatchID   += "_" + jet_string;
      decor_dvMatchDR   += "_" + jet_string;
    }
    // loop over secVerts + initialize decorators for all in container
    for ( const auto& secVtx : *secVerts ) {
      secVtx->auxdecor<char>(decor_dvIsMatched) = false;
      secVtx->auxdecor<int>(decor_dvMatchID)    = AlgConsts::invalidInt;
      secVtx->auxdecor<double>(decor_dvMatchDR) = AlgConsts::invalidFloat;
    }
  }

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
	vtx->auxdecor<char>(decor_dvIsMatched) = true;
	vtx->auxdecor<int>(decor_dvMatchID)    = jet->auxdataConst<int>("ID");
	vtx->auxdecor<double>(decor_dvMatchDR) = dR;
    	EJsHelper::VertexLink_t link( m_inSecondaryVertexContainerName, v );
    	matchedDVLinks .push_back( link );
    	matched_dR     .push_back( dR );
      }
      
    } // end loop over secondary vertices

    // decorate jets w/ matched secondary vertices + dRs b/w them
    jet->auxdecor<EJsHelper::VertexLinkVector_t>("matchedSecondaryVertexLinks") = matchedDVLinks;
    jet->auxdecor<std::vector<float>>("matchedSecondaryVertex_dR")              = matched_dR;
    
  } // end loop over jets

} // end matchSecVertsToJets



void ObjectMatcher :: matchTruthPartsToJets ( const xAOD::JetContainer* jets,
					      const xAOD::TruthParticleContainer* truthParts,
					      const enum jetType& jet_type,
					      const std::string jet_string )
{
  // delta-R match truth particles to jets

  // set decorator variable names
  std::string decor_tpIsMatched;
  std::string decor_tpMatchID;
  std::string decor_tpMatchDR;
  if      ( jet_type == TRUTH ) {
    decor_tpIsMatched = "isMatchedToTruthJet";
    decor_tpMatchID   = "truthJetMatchID";
    decor_tpMatchDR   = "truthJetMatchDR";
  }
  else if ( jet_type == DARK  ) {
    decor_tpIsMatched = "isMatchedToDarkJet";
    decor_tpMatchID   = "darkJetMatchID";
    decor_tpMatchDR   = "darkJetMatchDR";
  }
  else if ( jet_type == RECO  ) {
    decor_tpIsMatched = "isMatchedToRecoJet";
    decor_tpMatchID   = "recoJetMatchID";
    decor_tpMatchDR   = "recoJetMatchDR";
    if ( !jet_string.empty() ) {
      decor_tpIsMatched += "_" + jet_string;
      decor_tpMatchID   += "_" + jet_string;
      decor_tpMatchDR   += "_" + jet_string;
    }
    // loop over truthParts + initialize decorators for all in container
    for ( const auto& truthPart : *truthParts ) {
      truthPart->auxdecor<char>(decor_tpIsMatched) = false;
      truthPart->auxdecor<int>(decor_tpMatchID)    = AlgConsts::invalidInt;
      truthPart->auxdecor<double>(decor_tpMatchDR) = AlgConsts::invalidFloat;
    }
  }

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
	tp->auxdecor<char>(decor_tpIsMatched) = true;
	tp->auxdecor<int>(decor_tpMatchID)    = jet->auxdataConst<int>("ID");
	tp->auxdecor<double>(decor_tpMatchDR) = dR;
	EJsHelper::TruthParticleLink_t link( m_inTruthPartContainerName, t );
	matchedTruthPartLinks .push_back( link );
	matched_dR            .push_back( dR );
      }
    } // end loop over truth particles

    // decorate jets w/ matched truth particles + dRs b/w them
    jet->auxdecor<EJsHelper::TruthParticleLinkVector_t>("matchedTruthParticleLinks") = matchedTruthPartLinks;
    jet->auxdecor<std::vector<float>>("matchedTruthParticle_dR")                     = matched_dR;
    
  } // end loop over jets
  
} // end matchTruthPartsToJets



void ObjectMatcher :: matchTracksToJets ( const xAOD::JetContainer* jets,
					  const xAOD::TrackParticleContainer* tracks,
					  const enum jetType& jet_type,
					  const std::string jet_string )
{
  // delta-R match tracks to jets

  // set decorator variable names
  std::string decor_trkIsMatched;
  std::string decor_trkMatchID;
  std::string decor_trkMatchDR;
  if      ( jet_type == TRUTH ) {
    decor_trkIsMatched = "isMatchedToTruthJet";
    decor_trkMatchID   = "truthJetMatchID";
    decor_trkMatchDR   = "truthJetMatchDR";
  }
  else if ( jet_type == DARK  ) {
    decor_trkIsMatched = "isMatchedToDarkJet";
    decor_trkMatchID   = "darkJetMatchID";
    decor_trkMatchDR   = "darkJetMatchDR";
  }
  else if ( jet_type == RECO  ) {
    decor_trkIsMatched = "isMatchedToRecoJet";
    decor_trkMatchID   = "recoJetMatchID";
    decor_trkMatchDR   = "recoJetMatchDR";
    if ( !jet_string.empty() ) {
      decor_trkIsMatched += "_" + jet_string;
      decor_trkMatchID   += "_" + jet_string;
      decor_trkMatchDR   += "_" + jet_string;
    }
    // loop over tracks + initialize decorators for all in container
    for ( const auto& track : *tracks ) {
      track->auxdecor<char>(decor_trkIsMatched) = false;
      track->auxdecor<int>(decor_trkMatchID)    = AlgConsts::invalidInt;
      track->auxdecor<double>(decor_trkMatchDR) = AlgConsts::invalidFloat;
    }
  }

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
	trk->auxdecor<char>(decor_trkIsMatched) = true;
	trk->auxdecor<int>(decor_trkMatchID)    = jet->auxdataConst<int>("ID");
	trk->auxdecor<double>(decor_trkMatchDR) = dR;
	EJsHelper::TrackLink_t link( m_inTrackPartContainerName, t );
	matchedTrkLinks .push_back( link );
	matched_dR      .push_back( dR );
      }
    } // end loop over tracks

    // decorate jets w/ matched tracks + dRs b/w them
    jet->auxdecor<EJsHelper::TrackLinkVector_t>("matchedTrackLinks") = matchedTrkLinks;
    jet->auxdecor<std::vector<float>>("matchedTrack_dR")             = matched_dR;
    
  } // end loop over jets

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
  // reverse match tracks to the secondary vertices they correspond to

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
	truthVtx->auxdecor<char>("isCloseToSecondaryVertex")       = true;
	truthVtx->auxdecor<int>("closeSecondaryVertexID")          = secVtx->auxdataConst<int>("ID");
	truthVtx->auxdecor<double>("closeSecondaryVertexDistance") = dist;
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

    // decorate secondary vertices w/ close-matched and closest truth vertices + distances b/w them
    secVtx->auxdecor<EJsHelper::TruthVertexLinkVector_t>("closeMatchedTruthVertexLinks") = matchedTVLinks;
    secVtx->auxdecor<std::vector<float>>("closeMatchedTruthVertex_dist")                 = matchedTV_dist;

    if ( closestTruthVertex ) {
      closestTruthVertex->auxdecor<char>("isClosestToSecondaryVertex") = true;
      closestTruthVertex->auxdecor<int>("closestSecondaryVertexID") = secVtx->auxdataConst<int>("ID");
      closestTruthVertex->auxdecor<double>("closestSecondaryVertexDistance") = closestTVDist;
      EJsHelper::TruthVertexLink_t closestTVLink( closestTruthVertex, *truthVerts );
      secVtx->auxdecor<EJsHelper::TruthVertexLink_t>("closestTruthVertexLink") = closestTVLink;
    }
    secVtx->auxdecor<double>("closestTruthVertex_dist") = closestTVDist;
    
  } // end loop over secondary vertices
  
} // end matchCloseVerts



void ObjectMatcher :: matchLinkedTruthToSecVerts ( const xAOD::VertexContainer* secVerts,
						   const xAOD::TruthVertexContainer* truthVerts )
{
  // match linked truth vertices to reco secondary vertices (track-truth-link-based matching)
  // --> tentative strategy; may evolve (see VsiPerf efficiency processor) ...

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
      tv->auxdecor<char>("isLinkedToSecondaryVertex")    = true;
      tv->auxdecor<int>("linkedSecondaryVertexID")       = secVtx->auxdataConst<int>("ID");
      tv->auxdecor<double>("linkedSecondaryVertexScore") = linkedTV.second;
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
    }

    // loop over linked parent truth vertices + save element links + score
    EJsHelper::TruthVertexLinkVector_t linkedPTVLinks;
    std::vector<float>                 linkedPTV_score;
    for ( const auto& linkedPTV : linkedParentTruthVerts ) {
      const auto* ptv = linkedPTV.first;
      ptv->auxdecor<char>("isLinkedParentToSecondaryVertex")    = true;
      ptv->auxdecor<int>("linkedParentSecondaryVertexID")       = secVtx->auxdataConst<int>("ID");
      ptv->auxdecor<double>("linkedParentSecondaryVertexScore") = linkedPTV.second;
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
    }
    
    // decorate secondary vertices w/ (max) linked (parent) truth vertices + their pt-weighted scores
    secVtx->auxdecor<EJsHelper::TruthVertexLinkVector_t>("trackLinkedTruthVertexLinks") = linkedTVLinks;
    secVtx->auxdecor<std::vector<float>>("trackLinkedTruthVertex_score")                = linkedTV_score;

    if ( maxlinkedTruthVertex ) {
      maxlinkedTruthVertex->auxdecor<char>("isMaxlinkedToSecondaryVertex")    = true;
      maxlinkedTruthVertex->auxdecor<int>("maxlinkedSecondaryVertexID")       = secVtx->auxdataConst<int>("ID");
      maxlinkedTruthVertex->auxdecor<double>("maxlinkedSecondaryVertexScore") = maxlinkedTVScore;
      EJsHelper::TruthVertexLink_t maxlinkedTVLink( maxlinkedTruthVertex, *truthVerts );
      secVtx->auxdecor<EJsHelper::TruthVertexLink_t>("maxlinkedTruthVertexLink") = maxlinkedTVLink;
    }
    secVtx->auxdecor<double>("maxlinkedTruthVertex_score") = maxlinkedTVScore;

    secVtx->auxdecor<EJsHelper::TruthVertexLinkVector_t>("trackLinkedParentTruthVertexLinks") = linkedPTVLinks;
    secVtx->auxdecor<std::vector<float>>("trackLinkedParentTruthVertex_score")                = linkedPTV_score;

    if ( maxlinkedParentTruthVertex ) {
      maxlinkedTruthVertex->auxdecor<char>("isMaxlinkedParentToSecondaryVertex")    = true;
      maxlinkedTruthVertex->auxdecor<int>("maxlinkedParentSecondaryVertexID")       = secVtx->auxdataConst<int>("ID");
      maxlinkedTruthVertex->auxdecor<double>("maxlinkedParentSecondaryVertexScore") = maxlinkedPTVScore;
      EJsHelper::TruthVertexLink_t maxlinkedPTVLink( maxlinkedParentTruthVertex, *truthVerts );
      secVtx->auxdecor<EJsHelper::TruthVertexLink_t>("maxlinkedParentTruthVertexLink") = maxlinkedPTVLink;
    }
    secVtx->auxdecor<double>("maxlinkedParentTruthVertex_score") = maxlinkedPTVScore;

  } // end loop over secondary vertices
  
} // end matchLinkedVerts
