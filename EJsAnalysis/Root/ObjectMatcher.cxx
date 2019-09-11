#include <map>

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
  while ( std::getline( ss_jet_containers, token, ' ' ) )
    m_inJetContainers.push_back( token );
  
  // check for input containers
  if ( !m_truthLevelOnly ) {
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

  // get truth containers
  if ( isMC() ) {
    if ( m_haveTruthJets ) {
      ANA_MSG_DEBUG( "Getting input truth jet container: " << m_inTruthJetContainerName );
      ANA_CHECK( HelperFunctions::retrieve( inTruthJets, m_inTruthJetContainerName, m_event, m_store, msg() ) );
    }
    
    if ( m_haveDarkJets ) {
      ANA_MSG_DEBUG( "Getting input truth dark jet container: " << m_inTruthDarkJetContainerName );
      ANA_CHECK( HelperFunctions::retrieve( inTruthDarkJets, m_inTruthDarkJetContainerName, m_event, m_store, msg() ) );
    }
    
    ANA_MSG_DEBUG( "Getting input truth particle container: " << m_inTruthPartContainerName );
    ANA_CHECK( HelperFunctions::retrieve( inTruthParts, m_inTruthPartContainerName, m_event, m_store, msg() ) );

    ANA_MSG_DEBUG( "Getting input truth vertex container: " << m_inTruthVertexContainerName );
    ANA_CHECK( HelperFunctions::retrieve( inTruthVerts, m_inTruthVertexContainerName, m_event, m_store, msg() ) );
  }

  // get reco containers
  if ( !m_truthLevelOnly ) {
    ANA_MSG_DEBUG( "Getting input track particle container: " << m_inTrackPartContainerName );
    ANA_CHECK( HelperFunctions::retrieve( inTrackParts, m_inTrackPartContainerName, m_event, m_store, msg() ) );

    ANA_MSG_DEBUG( "Getting input secondary vertex container: " << m_inSecondaryVertexContainerName );
    ANA_CHECK( HelperFunctions::retrieve( inSecVerts, m_inSecondaryVertexContainerName, m_event, m_store, msg() ) );
  }


  // initialize decorators
  // --> "ID" = index of original, unselected xAOD container; "index" = index of new, selected container -->
  // --> "ID" = "index" if not using selected container as input
  if ( isMC() ) {
    int truthJet_index = 0;
    for ( const auto& truthJet : *inTruthJets ) {
      truthJet->auxdecor<int>("ID")    = truthJet->index();
      truthJet->auxdecor<int>("index") = truthJet_index;
      ++truthJet_index;
    }

    int truthDarkJet_index = 0;
    for ( const auto& truthDarkJet : *inTruthDarkJets ) {
      truthDarkJet->auxdecor<int>  ("ID")              = truthDarkJet->index();
      truthDarkJet->auxdecor<int>  ("index")           = truthDarkJet_index;
      truthDarkJet->auxdecor<char> ("isTruthMatched")  = false;
      truthDarkJet->auxdecor<int>  ("truthMatchID")    = AlgConsts::invalidInt;
      truthDarkJet->auxdecor<int>  ("truthMatchIndex") = AlgConsts::invalidInt;
      truthDarkJet->auxdecor<float>("truthMatchDR")    = AlgConsts::invalidFloat;
      ++truthDarkJet_index;
    }
    
    int truthPart_index = 0;
    for ( const auto& truthPart : *inTruthParts ) {
      truthPart->auxdecor<int>  ("ID")                         = truthPart->index();
      truthPart->auxdecor<int>  ("index")                      = truthPart_index;
      truthPart->auxdecor<EJsHelper::TrackLink_t>("trackLink") = EJsHelper::TrackLink_t();
      truthPart->auxdecor<char> ("isTrackMatch")               = false;
      truthPart->auxdecor<float>("trackMatchProbability")      = AlgConsts::invalidFloat;
      ++truthPart_index;
    }

    int truthVtx_index = 0;
    for ( const auto& truthVtx : *inTruthVerts ) {
      truthVtx->auxdecor<int>("ID")    = truthVtx->index();
      truthVtx->auxdecor<int>("index") = truthVtx_index;
      ++truthVtx_index;
    }
  }

  if ( !m_truthLevelOnly ) {
    int track_index = 0;
    for ( const auto& track : *inTrackParts ) {
      track->auxdecor<int>("ID")                                      = track->index();
      track->auxdecor<int>("index")                                   = track_index;
      track->auxdecor<EJsHelper::VertexLink_t>("secondaryVertexLink") = EJsHelper::VertexLink_t();
      track->auxdecor<char>("isSecondaryVertexTrack")                 = false;
      ++track_index;
    }

    int secVtx_index = 0;
    for ( const auto& secVtx : *inSecVerts ) {
      secVtx->auxdecor<int>("ID")    = secVtx->index();
      secVtx->auxdecor<int>("index") = secVtx_index;
      ++secVtx_index;
    }
  }


  if ( isMC() ) {
    if ( !m_truthLevelOnly ) {
      // match tracks to truth particles
      if ( m_doTruthTrackMatching )
	matchTracksToTruthParts( inTruthParts, inTrackParts );
      // match truth vertices to truth (dark) jets
      if ( inTruthJets     ) matchTruthVertsToJets( inTruthJets,     inTruthVerts, TRUTH, "" );
      if ( inTruthDarkJets ) matchTruthVertsToJets( inTruthDarkJets, inTruthVerts, DARK,  "" );
      // match reco secondary vertices to truth (dark) jets
      if ( inTruthJets     ) matchSecVertsToJets(  inTruthJets,      inSecVerts,   TRUTH, "" );
      if ( inTruthDarkJets ) matchSecVertsToJets(  inTruthDarkJets,  inSecVerts,   DARK,  "" );
      // match truth particles to truth (dark) jets
      if ( inTruthJets     ) matchTruthPartsToJets( inTruthJets,     inTruthParts, TRUTH, "" );
      if ( inTruthDarkJets ) matchTruthPartsToJets( inTruthDarkJets, inTruthParts, DARK,  "" );
      // match tracks to truth (dark) jets
      if ( inTruthJets     ) matchTracksToJets(    inTruthJets,      inTrackParts, TRUTH, "" );
      if ( inTruthDarkJets ) matchTracksToJets(    inTruthDarkJets,  inTrackParts, DARK,  "" );
    }
    // match truth dark jets to truth jets
    if ( inTruthJets && inTruthDarkJets )
      matchTruthJets( inTruthJets, inTruthDarkJets, TRUTH, DARK, "" );
  }


  if ( !m_truthLevelOnly ) {
    // match secondary vertices to tracks
    matchSecVertsToTracks( inTrackParts, inSecVerts );
    
    // if input comes from xAOD, or not running systematics...
    if ( m_inputAlgo.empty() ) {
    
      // get jet container(s)
      for ( size_t i = 0; i != m_inJetContainers.size(); ++i ) {
	  
	// skip jet container if not available
	if ( !HelperFunctions::isAvailable<xAOD::JetContainer>( m_inJetContainers.at(i), m_event, m_store, msg() ) ) {
	  ANA_MSG_DEBUG( "Input jet container, '" << m_inJetContainers.at(i) << "', is not available. Skipping..." );
	  continue;
	}
	const xAOD::JetContainer* inJets = 0;  
	ANA_MSG_DEBUG( "Getting input jet container: " << m_inJetContainers.at(i) );
	ANA_CHECK( HelperFunctions::retrieve( inJets, m_inJetContainers.at(i), m_event, m_store, msg() ) );

	// initialize decorators
	int jet_index = 0;
	for ( const auto& jet : *inJets ) {
	  jet->auxdecor<int>("ID")    = jet->index();
	  jet->auxdecor<int>("index") = jet_index;
	  ++jet_index;
	}

	// set jet-string
	std::string jetStr = "";
	if      ( m_inJetContainers.at(i).find("EMTopo") != std::string::npos ) jetStr = "EMTopo";
	else if ( m_inJetContainers.at(i).find("PFlow")  != std::string::npos ) jetStr = "PFlow";

	// do matching
	if ( isMC() ) {
	  // match truth (dark) jets to reco jets
	  if ( inTruthJets )
	    matchTruthJets( inJets, inTruthJets,     RECO, TRUTH, jetStr );
	  if (inTruthDarkJets )
	    matchTruthJets( inJets, inTruthDarkJets, RECO, DARK,  jetStr );
	  
	  // match truth vertices to reco jets
	  matchTruthVertsToJets( inJets, inTruthVerts, RECO, jetStr );
	  // match truth particles to reco jets
	  matchTruthPartsToJets( inJets, inTruthParts, RECO, jetStr );
	}

	// match reco secondary vertices to reco jets
	matchSecVertsToJets(   inJets, inSecVerts,   RECO, jetStr );
	// match tracks to reco jets
	matchTracksToJets(     inJets, inTrackParts, RECO, jetStr );
      
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
	    int jet_index = 0;
	    for ( const auto& jet : *inJets ) {
	      jet->auxdecor<int>("ID")    = jet->index();
	      jet->auxdecor<int>("index") = jet_index;
	      ++jet_index;
	    }

	    // set jet-string
	    std::string jetStr = "";
	    if      ( m_inJetContainers.at(i).find("EMTopo") != std::string::npos ) jetStr = "EMTopo";
	    else if ( m_inJetContainers.at(i).find("PFlow")  != std::string::npos ) jetStr = "PFlow";
      
	    // do matching
	    if ( isMC() ) {
	      // match truth (dark) jets to reco jets
	      if ( inTruthJets )
		matchTruthJets( inJets, inTruthJets,     RECO, TRUTH, jetStr + systName );
	      if ( inTruthDarkJets )
		matchTruthJets( inJets, inTruthDarkJets, RECO, DARK,  jetStr + systName );

	      // match truth vertices to reco jets
	      matchTruthVertsToJets( inJets, inTruthVerts, RECO, jetStr + systName );
	      // match truth particles to reco jets
	      matchTruthPartsToJets( inJets, inTruthParts, RECO, jetStr + systName );
	    }

	    // match reco secondary vertices to reco jets
	    matchSecVertsToJets(   inJets, inSecVerts,   RECO, jetStr + systName );
	    // match tracks to reco jets
	    matchTracksToJets(     inJets, inTrackParts, RECO, jetStr + systName );

	  }
	} // end loop over input jet containers
      } // end loop over systematics
    }
    
  } // end reco jet matching
  

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



void ObjectMatcher :: matchTracksToTruthParts ( const xAOD::TruthParticleContainer* parts,
						const xAOD::TrackParticleContainer* tracks )
{
  // reverse match tracks to truth particles using track-truth links

  // loop over tracks
  for ( const auto& trk : *tracks ) {
    const auto* tp = EJsHelper::getTruthPart( trk ); // get linked truth particle
    if ( !tp ) continue;
    EJsHelper::TrackLink_t trkLink( m_inTrackPartContainerName, trk->auxdataConst<int>("index") );
    tp->auxdecor<EJsHelper::TrackLink_t>("trackLink") = trkLink;
    tp->auxdecor<char> ("isTrackMatch")               = true;
    tp->auxdecor<float>("trackMatchProbability")      = trk->auxdataConst<float>("truthMatchProbability");
  } // end loop over tracks
  
} // end matchTracksToTruthParts



void ObjectMatcher :: matchSecVertsToTracks ( const xAOD::TrackParticleContainer* tracks,
					      const xAOD::VertexContainer* secVerts )
{
  // match tracks to corresponding secondary vertices

  // loop over secondary vertices
  for ( const auto& vtx : *secVerts ) {
    // loop over vertex tracks + decorate
    for ( size_t i = 0; i != vtx->nTrackParticles(); ++i ) {
      const auto* trk = vtx->trackParticle(i);
      if ( !trk ) continue;
      EJsHelper::VertexLink_t vtxLink( m_inSecondaryVertexContainerName, vtx->auxdataConst<int>("index") );
      trk->auxdecor<EJsHelper::VertexLink_t>("secondaryVertexLink") = vtxLink;
      trk->auxdecor<char>("isSecondaryVertexTrack")                 = true;
    }
  }
  
} // end matchSecVertsToTracks



void ObjectMatcher :: matchTruthJets ( const xAOD::JetContainer* jets, const xAOD::JetContainer* matchJets,
				       const enum jetType& jet_type,   const enum jetType& matchJet_type,
				       const std::string jet_string )
{
  // delta-R match truth (dark) jets to (truth) jets

  // set decorator variable names
  std::string decor_isMatched;
  std::string decor_isMatchedID;
  std::string decor_isMatchedIndex;
  std::string decor_isMatchedDR;
  std::string decor_hasMatch;
  std::string decor_matchID;
  std::string decor_matchIndex;
  std::string decor_matchDR;
  std::string decor_matchLink;

  if ( jet_type == TRUTH ) {
    decor_isMatched      = "isTruthMatched";
    decor_isMatchedID    = "truthMatchID";
    decor_isMatchedIndex = "truthMatchIndex";
    decor_isMatchedDR    = "truthMatchDR";
  }
  else if ( jet_type == RECO ) {
    decor_isMatched      = "isRecoMatched";
    decor_isMatchedID    = "recoMatchID";
    decor_isMatchedIndex = "recoMatchIndex";
    decor_isMatchedDR    = "recoMatchDR";
    if ( !jet_string.empty() ) {
      decor_isMatched      += "_" + jet_string;
      decor_isMatchedID    += "_" + jet_string;
      decor_isMatchedIndex += "_" + jet_string;
      decor_isMatchedDR    += "_" + jet_string;
    }
    // loop over matchJets + initialize decorators for all in container
    for ( const auto& matchJet : *matchJets ) {
      matchJet->auxdecor<char> (decor_isMatched)      = false;
      matchJet->auxdecor<int>  (decor_isMatchedID)    = AlgConsts::invalidInt;
      matchJet->auxdecor<int>  (decor_isMatchedIndex) = AlgConsts::invalidInt;
      matchJet->auxdecor<float>(decor_isMatchedDR)    = AlgConsts::invalidFloat;
    }
  }
  
  if ( matchJet_type == TRUTH ) {
    decor_hasMatch   = "hasTruthJetMatch";
    decor_matchID    = "truthJetMatchID";
    decor_matchIndex = "truthJetMatchIndex";
    decor_matchDR    = "truthJetMatchDR";
    decor_matchLink  = "truthJetMatchLink";
  }
  else if ( matchJet_type == DARK ) {
    decor_hasMatch   = "hasDarkJetMatch";
    decor_matchID    = "darkJetMatchID";
    decor_matchIndex = "darkJetMatchIndex";
    decor_matchDR    = "darkJetMatchDR";
    decor_matchLink  = "darkJetMatchLink";
  }
  
  // loop over jets
  for ( const auto& jet : *jets ) {

    bool   jetHasMatch   = false;
    int    jetMatchID    = AlgConsts::invalidInt;
    int    jetMatchIndex = AlgConsts::invalidInt;
    double jetMatchDR    = AlgConsts::invalidFloat;
    
    // loop over matchJets to match to jets
    for ( const auto& matchJet : *matchJets ) {
      
      // skip matchJet if already matched to jet...
      if ( matchJet->auxdecor<char>(decor_isMatched) ) continue;

      // calculate dR b/w jet + matchJet and look for match
      double dR = EJsHelper::deltaR( jet->eta(), matchJet->eta(), jet->phi(), matchJet->phi() );
      if ( dR < m_jet_matchRadius ) { // first match in high-pt order
	matchJet->auxdecor<char> (decor_isMatched)      = true;
	matchJet->auxdecor<int>  (decor_isMatchedID)    = jet->auxdataConst<int>("ID");
	matchJet->auxdecor<int>  (decor_isMatchedIndex) = jet->auxdataConst<int>("index");
	matchJet->auxdecor<float>(decor_isMatchedDR)    = dR;
	jetHasMatch   = true;
	jetMatchID    = matchJet->auxdataConst<int>("ID");
	jetMatchIndex = matchJet->auxdataConst<int>("index");
	jetMatchDR    = dR;
	break; // match found --> leave matchJet loop + go to next jet
      }
      
    } // end loop over matchJets

    jet->auxdecor<char> (decor_hasMatch)   = jetHasMatch;
    jet->auxdecor<int>  (decor_matchID)    = jetMatchID;
    jet->auxdecor<int>  (decor_matchIndex) = jetMatchIndex;
    jet->auxdecor<float>(decor_matchDR)    = jetMatchDR;

    std::string matchJetContainerName = "";
    if      ( matchJet_type == TRUTH ) matchJetContainerName = m_inTruthJetContainerName;
    else if ( matchJet_type == DARK  ) matchJetContainerName = m_inTruthDarkJetContainerName;
    EJsHelper::JetLink_t jetLink( matchJetContainerName, jetMatchIndex );
    jet->auxdecor<EJsHelper::JetLink_t>(decor_matchLink) = jetLink;
    
  } // end loop over jets
} // end matchTruthJets



void ObjectMatcher :: matchTruthVertsToJets ( const xAOD::JetContainer* jets, const xAOD::TruthVertexContainer* truthVerts,
					      const enum jetType& jet_type,   const std::string jet_string )
{
  // delta-R match truth vertices to jets

  // set decorator variable names
  std::string decor_tvIsJetMatched;
  std::string decor_tvJetMatchID;
  std::string decor_tvJetMatchIndex;
  std::string decor_tvJetMatchDR;
  if      ( jet_type == TRUTH ) {
    decor_tvIsJetMatched  = "isMatchedToTruthJet";
    decor_tvJetMatchID    = "truthJetMatchID";
    decor_tvJetMatchIndex = "truthJetMatchIndex";
    decor_tvJetMatchDR    = "truthJetMatchDR";
  }
  else if ( jet_type == DARK  ) {
    decor_tvIsJetMatched  = "isMatchedToDarkJet";
    decor_tvJetMatchID    = "darkJetMatchID";
    decor_tvJetMatchIndex = "darkJetMatchIndex";
    decor_tvJetMatchDR    = "darkJetMatchDR"; 
  }
  else if ( jet_type == RECO  ) {
    decor_tvIsJetMatched  = "isMatchedToRecoJet";
    decor_tvJetMatchID    = "recoJetMatchID";
    decor_tvJetMatchIndex = "recoJetMatchIndex";
    decor_tvJetMatchDR    = "recoJetMatchDR";
    if ( !jet_string.empty() ) {
      decor_tvIsJetMatched  += "_" + jet_string;
      decor_tvJetMatchID    += "_" + jet_string;
      decor_tvJetMatchIndex += "_" + jet_string;
      decor_tvJetMatchDR    += "_" + jet_string;
    }
  }

  // map matched truth vertices to ALL matching jets
  std::map<const xAOD::TruthVertex*, std::vector<std::pair<const xAOD::Jet*, float>> > matchedTruthVerts_tmp;

  // loop over jets
  for ( const auto& jet : *jets ) {

    // initialize jet decorators
    jet->auxdecor<EJsHelper::TruthVertexLinkVector_t>("matchedTruthVertexLinks") = EJsHelper::TruthVertexLinkVector_t();
    jet->auxdecor<std::vector<float>>("matchedTruthVertex_dR")                   = std::vector<float>();

    // loop over truth vertices
    for ( const auto& vtx : *truthVerts ) {

      // initialize vertex decorators
      vtx->auxdecor<char> (decor_tvIsJetMatched)  = false;
      vtx->auxdecor<int>  (decor_tvJetMatchID)    = AlgConsts::invalidInt;
      vtx->auxdecor<int>  (decor_tvJetMatchIndex) = AlgConsts::invalidInt;
      vtx->auxdecor<float>(decor_tvJetMatchDR)    = AlgConsts::invalidFloat;

      double dR = EJsHelper::deltaR( jet->eta(), vtx->eta(), jet->phi(), vtx->phi() );
      if ( dR < m_jet_vtx_matchRadius )
	matchedTruthVerts_tmp[vtx] .push_back( std::make_pair( jet, dR ) );
      
    } // end loop over truth vertices
    
  } // end loop over jets

  // map matched truth vertex to SINGLE closest matching jet + dR b/w them
  std::map<const xAOD::TruthVertex*, std::pair<const xAOD::Jet*, float>> matchedTruthVerts;
  for ( const auto& matchedTV : matchedTruthVerts_tmp ) {
    auto minDR_match = *std::min_element( matchedTV.second.begin(), matchedTV.second.end(), []
					  ( const auto& lhs, const auto& rhs ) { return lhs.second < rhs.second; } );
    matchedTruthVerts[matchedTV.first] = minDR_match;
  }

  // map jets to all matched truth vertices + dRs b/w them
  std::map<const xAOD::Jet*, EJsHelper::TruthVertexLinkVector_t> jets_matchedTruthVerts_link;
  std::map<const xAOD::Jet*, std::vector<float>> jets_matchedTruthVerts_dR;
  for ( const auto& matchedTV : matchedTruthVerts ) {
    EJsHelper::TruthVertexLink_t link( m_inTruthVertexContainerName, matchedTV.first->auxdataConst<int>("index") );
    jets_matchedTruthVerts_link[ matchedTV.second.first ] .push_back( link                    );
    jets_matchedTruthVerts_dR  [ matchedTV.second.first ] .push_back( matchedTV.second.second );

    // decorate TVs w/ jet-match map info
    matchedTV.first->auxdecor<char> (decor_tvIsJetMatched ) = true;
    matchedTV.first->auxdecor<int>  (decor_tvJetMatchID)    = matchedTV.second.first->auxdataConst<int>("ID");
    matchedTV.first->auxdecor<int>  (decor_tvJetMatchIndex) = matchedTV.second.first->auxdataConst<int>("index");
    matchedTV.first->auxdecor<float>(decor_tvJetMatchDR)    = matchedTV.second.second;
  }

  // decorate jets w/ matched-TVs map info
  for ( const auto& matchJet : jets_matchedTruthVerts_link )
    matchJet.first->auxdecor<EJsHelper::TruthVertexLinkVector_t>("matchedTruthVertexLinks") = matchJet.second;
  for ( const auto& matchJet : jets_matchedTruthVerts_dR   )
    matchJet.first->auxdecor<std::vector<float>>("matchedTruthVertex_dR")                   = matchJet.second;

} // end matchTruthVertsToJets



void ObjectMatcher :: matchSecVertsToJets ( const xAOD::JetContainer* jets, const xAOD::VertexContainer* secVerts,
					    const enum jetType& jet_type,   const std::string jet_string )
{
  // delta-R match reco secondary vertices to jets

  // set decorator variable names
  std::string decor_dvIsJetMatched;
  std::string decor_dvJetMatchID;
  std::string decor_dvJetMatchIndex;
  std::string decor_dvJetMatchDR;
  if      ( jet_type == TRUTH ) {
    decor_dvIsJetMatched  = "isMatchedToTruthJet";
    decor_dvJetMatchID    = "truthJetMatchID";
    decor_dvJetMatchIndex = "truthJetMatchIndex";
    decor_dvJetMatchDR    = "truthJetMatchDR";
  }
  else if ( jet_type == DARK  ) {
    decor_dvIsJetMatched = "isMatchedToDarkJet";
    decor_dvJetMatchID    = "darkJetMatchID";
    decor_dvJetMatchIndex = "darkJetMatchIndex";
    decor_dvJetMatchDR    = "darkJetMatchDR";
  }
  else if ( jet_type == RECO  ) {
    decor_dvIsJetMatched = "isMatchedToRecoJet";
    decor_dvJetMatchID    = "recoJetMatchID";
    decor_dvJetMatchIndex = "recoJetMatchIndex";
    decor_dvJetMatchDR    = "recoJetMatchDR";
    if ( !jet_string.empty() ) {
      decor_dvIsJetMatched  += "_" + jet_string;
      decor_dvJetMatchID    += "_" + jet_string;
      decor_dvJetMatchIndex += "_" + jet_string;
      decor_dvJetMatchDR    += "_" + jet_string;
    }
  }

  // map matched secondary vertices to ALL matching jets
  std::map<const xAOD::Vertex*, std::vector<std::pair<const xAOD::Jet*, float>> > matchedSecVerts_tmp;
  
  // loop over jets
  for ( const auto& jet : *jets ) {

    // initialize jet decorators
    jet->auxdecor<EJsHelper::VertexLinkVector_t>("matchedSecondaryVertexLinks") = EJsHelper::VertexLinkVector_t();
    jet->auxdecor<std::vector<float>>("matchedSecondaryVertex_dR")              = std::vector<float>();

    // loop over secondary vertices
    for ( const auto& vtx : *secVerts ) {

      // initialize vertex decorators
      vtx->auxdecor<char> (decor_dvIsJetMatched)  = false;
      vtx->auxdecor<int>  (decor_dvJetMatchID)    = AlgConsts::invalidInt;
      vtx->auxdecor<int>  (decor_dvJetMatchIndex) = AlgConsts::invalidInt;
      vtx->auxdecor<float>(decor_dvJetMatchDR)    = AlgConsts::invalidFloat;
      
      // get vertex eta, phi from four-momentum + calculate dR to jet
      std::vector<const xAOD::TrackParticle*> filteredTracks;
      std::vector<const xAOD::TrackParticle*> allTracks;
      EJsHelper::getFilteredTracks( vtx, filteredTracks );
      for ( size_t i = 0; i != vtx->nTrackParticles(); ++i ) {
	const auto* trk = vtx->trackParticle(i);
	allTracks.push_back( trk );
      }
      TLorentzVector vtxP4      = VsiBonsai::sumP4 ( filteredTracks );
      TLorentzVector vtxP4_bare = VsiBonsai::sumP4 ( allTracks      );
      
      double dR      = EJsHelper::deltaR( jet->eta(), vtxP4.Eta(),      jet->phi(), vtxP4.Phi()      );
      double dR_bare = EJsHelper::deltaR( jet->eta(), vtxP4_bare.Eta(), jet->phi(), vtxP4_bare.Phi() );
      if ( dR < m_jet_vtx_matchRadius || dR_bare < m_jet_vtx_matchRadius )
	matchedSecVerts_tmp[vtx] .push_back( std::make_pair( jet, std::min(dR, dR_bare) ) );
      
    } // end loop over secondary vertices
    
  } // end loop over jets

  // map matched secondary vertex to SINGLE closest matching jet + dR b/w them
  std::map<const xAOD::Vertex*, std::pair<const xAOD::Jet*, float>> matchedSecVerts;
  for ( const auto& matchedDV : matchedSecVerts_tmp ) {
    auto minDR_match = *std::min_element( matchedDV.second.begin(), matchedDV.second.end(), []
					  ( const auto& lhs, const auto& rhs ) { return lhs.second < rhs.second; } );
    matchedSecVerts[matchedDV.first] = minDR_match;
  }

  // map jets to all matched secondary vertices + dRs b/w them
  std::map<const xAOD::Jet*, EJsHelper::VertexLinkVector_t> jets_matchedSecVerts_link;
  std::map<const xAOD::Jet*, std::vector<float>> jets_matchedSecVerts_dR;
  for ( const auto& matchedDV : matchedSecVerts ) {
    EJsHelper::VertexLink_t link( m_inSecondaryVertexContainerName, matchedDV.first->auxdataConst<int>("index") );
    jets_matchedSecVerts_link[ matchedDV.second.first ] .push_back( link                    );
    jets_matchedSecVerts_dR  [ matchedDV.second.first ] .push_back( matchedDV.second.second );

    // decorate DVs w/ jet-match map info
    matchedDV.first->auxdecor<char> (decor_dvIsJetMatched)  = true;
    matchedDV.first->auxdecor<int>  (decor_dvJetMatchID)    = matchedDV.second.first->auxdataConst<int>("ID");
    matchedDV.first->auxdecor<int>  (decor_dvJetMatchIndex) = matchedDV.second.first->auxdataConst<int>("index");
    matchedDV.first->auxdecor<float>(decor_dvJetMatchDR)    = matchedDV.second.second;
  }

  // decorate jets w/ matched-DVs map info
  for ( const auto& matchJet : jets_matchedSecVerts_link )
    matchJet.first->auxdecor<EJsHelper::VertexLinkVector_t>("matchedSecondaryVertexLinks") = matchJet.second;
  for ( const auto& matchJet : jets_matchedSecVerts_dR   )
    matchJet.first->auxdecor<std::vector<float>>("matchedSecondaryVertex_dR")              = matchJet.second;
  
} // end matchSecVertsToJets



void ObjectMatcher :: matchTruthPartsToJets ( const xAOD::JetContainer* jets, const xAOD::TruthParticleContainer* truthParts,
					      const enum jetType& jet_type,   const std::string jet_string )
{
  // delta-R match truth particles to jets

  // set decorator variable names
  std::string decor_tpIsJetMatched;
  std::string decor_tpJetMatchID;
  std::string decor_tpJetMatchIndex;
  std::string decor_tpJetMatchDR;
  if      ( jet_type == TRUTH ) {
    decor_tpIsJetMatched  = "isMatchedToTruthJet";
    decor_tpJetMatchID    = "truthJetMatchID";
    decor_tpJetMatchIndex = "truthJetMatchIndex";
    decor_tpJetMatchDR    = "truthJetMatchDR";
  }
  else if ( jet_type == DARK  ) {
    decor_tpIsJetMatched = "isMatchedToDarkJet";
    decor_tpJetMatchID    = "darkJetMatchID";
    decor_tpJetMatchIndex = "darkJetMatchIndex";
    decor_tpJetMatchDR    = "darkJetMatchDR";
  }
  else if ( jet_type == RECO  ) {
    decor_tpIsJetMatched = "isMatchedToRecoJet";
    decor_tpJetMatchID    = "recoJetMatchID";
    decor_tpJetMatchIndex = "recoJetMatchIndex";
    decor_tpJetMatchDR    = "recoJetMatchDR";
    if ( !jet_string.empty() ) {
      decor_tpIsJetMatched  += "_" + jet_string;
      decor_tpJetMatchID    += "_" + jet_string;
      decor_tpJetMatchIndex += "_" + jet_string;
      decor_tpJetMatchDR    += "_" + jet_string;
    }
  }

  // map matched truth particles to ALL matching jets
  std::map<const xAOD::TruthParticle*, std::vector<std::pair<const xAOD::Jet*, float>> > matchedTruthParts_tmp;

  // loop over jets
  for ( const auto& jet : *jets ) {

    // initialize jet decorators
    jet->auxdecor<EJsHelper::TruthParticleLinkVector_t>("matchedTruthParticleLinks") = EJsHelper::TruthParticleLinkVector_t();
    jet->auxdecor<std::vector<float>>("matchedTruthParticle_dR")                     = std::vector<float>();

    // loop over truth particles
    for ( const auto& tp : *truthParts ) {

      // initialize truth particle decorators
      tp->auxdecor<char> (decor_tpIsJetMatched)  = false;
      tp->auxdecor<int>  (decor_tpJetMatchID)    = AlgConsts::invalidInt;
      tp->auxdecor<int>  (decor_tpJetMatchIndex) = AlgConsts::invalidInt;
      tp->auxdecor<float>(decor_tpJetMatchDR)    = AlgConsts::invalidFloat;

      double dR = EJsHelper::deltaR( jet->eta(), tp->eta(), jet->phi(), tp->phi() );
      if ( dR < m_jet_trk_matchRadius )
	matchedTruthParts_tmp[tp] .push_back( std::make_pair( jet, dR ) );
      
    } // end loop over truth particles
    
  } // end loop over jets

  // map matched truth particle to SINGLE closest matching jet + dR b/w them
  std::map<const xAOD::TruthParticle*, std::pair<const xAOD::Jet*, float>> matchedTruthParts;
  for ( const auto& matchedTP : matchedTruthParts_tmp ) {
    auto minDR_match = *std::min_element( matchedTP.second.begin(), matchedTP.second.end(), []
					  ( const auto& lhs, const auto& rhs ) { return lhs.second < rhs.second; } );
    matchedTruthParts[matchedTP.first] = minDR_match;
  }

  // map jets to all matched truth particles + dRs b/w them
  std::map<const xAOD::Jet*, EJsHelper::TruthParticleLinkVector_t> jets_matchedTruthParts_link;
  std::map<const xAOD::Jet*, std::vector<float>> jets_matchedTruthParts_dR;
  for ( const auto& matchedTP : matchedTruthParts ) {
    EJsHelper::TruthParticleLink_t link( m_inTruthPartContainerName, matchedTP.first->auxdataConst<int>("index") );
    jets_matchedTruthParts_link[ matchedTP.second.first ] .push_back( link                    );
    jets_matchedTruthParts_dR  [ matchedTP.second.first ] .push_back( matchedTP.second.second );

    // decorate truth particles w/ jet-match map info
    matchedTP.first->auxdecor<char> (decor_tpIsJetMatched)  = true;
    matchedTP.first->auxdecor<int>  (decor_tpJetMatchID)    = matchedTP.second.first->auxdataConst<int>("ID");
    matchedTP.first->auxdecor<int>  (decor_tpJetMatchIndex) = matchedTP.second.first->auxdataConst<int>("index");
    matchedTP.first->auxdecor<float>(decor_tpJetMatchDR)    = matchedTP.second.second;
  }

  // decorate jets w/ matched-truth-particles map info
  for ( const auto& matchJet : jets_matchedTruthParts_link )
    matchJet.first->auxdecor<EJsHelper::TruthParticleLinkVector_t>("matchedTruthParticleLinks") = matchJet.second;
  for ( const auto& matchJet : jets_matchedTruthParts_dR   )
    matchJet.first->auxdecor<std::vector<float>>("matchedTruthParticle_dR")                     = matchJet.second;

} // end matchTruthPartsToJets



void ObjectMatcher :: matchTracksToJets ( const xAOD::JetContainer* jets, const xAOD::TrackParticleContainer* tracks,
					  const enum jetType& jet_type,   const std::string jet_string )
{
  // delta-R match tracks to jets

  // set decorator variable names
  std::string decor_trkIsJetMatched;
  std::string decor_trkJetMatchID;
  std::string decor_trkJetMatchIndex;
  std::string decor_trkJetMatchDR;
  if      ( jet_type == TRUTH ) {
    decor_trkIsJetMatched  = "isMatchedToTruthJet";
    decor_trkJetMatchID    = "truthJetMatchID";
    decor_trkJetMatchIndex = "truthJetMatchIndex";
    decor_trkJetMatchDR    = "truthJetMatchDR";
  }
  else if ( jet_type == DARK  ) {
    decor_trkIsJetMatched = "isMatchedToDarkJet";
    decor_trkJetMatchID    = "darkJetMatchID";
    decor_trkJetMatchIndex = "darkJetMatchIndex";
    decor_trkJetMatchDR    = "darkJetMatchDR";
  }
  else if ( jet_type == RECO  ) {
    decor_trkIsJetMatched = "isMatchedToRecoJet";
    decor_trkJetMatchID    = "recoJetMatchID";
    decor_trkJetMatchIndex = "recoJetMatchIndex";
    decor_trkJetMatchDR    = "recoJetMatchDR";
    if ( !jet_string.empty() ) {
      decor_trkIsJetMatched  += "_" + jet_string;
      decor_trkJetMatchID    += "_" + jet_string;
      decor_trkJetMatchIndex += "_" + jet_string;
      decor_trkJetMatchDR    += "_" + jet_string;
    }
  }

  // map matched tracks to ALL matching jets
  std::map<const xAOD::TrackParticle*, std::vector<std::pair<const xAOD::Jet*, float>> > matchedTracks_tmp;

  // loop over jets
  for ( const auto& jet : *jets ) {

    // initialize jet decorators
    jet->auxdecor<EJsHelper::TrackLinkVector_t>("matchedTrackLinks") = EJsHelper::TrackLinkVector_t();
    jet->auxdecor<std::vector<float>>("matchedTrack_dR")             = std::vector<float>();

    // loop over tracks
    for ( const auto& trk : *tracks ) {

      // initialize vertex decorators
      trk->auxdecor<char> (decor_trkIsJetMatched)  = false;
      trk->auxdecor<int>  (decor_trkJetMatchID)    = AlgConsts::invalidInt;
      trk->auxdecor<int>  (decor_trkJetMatchIndex) = AlgConsts::invalidInt;
      trk->auxdecor<float>(decor_trkJetMatchDR)    = AlgConsts::invalidFloat;
      
      double dR = EJsHelper::deltaR( jet->eta(), trk->eta(), jet->phi(), trk->phi() );
      if ( dR < m_jet_trk_matchRadius )
	matchedTracks_tmp[trk] .push_back( std::make_pair( jet, dR ) );
      
    } // end loop over tracks
    
  } // end loop over jets

  // map matched track to SINGLE closest matching jet + dR b/w them
  std::map<const xAOD::TrackParticle*, std::pair<const xAOD::Jet*, float>> matchedTracks;
  for ( const auto& matchedTrk : matchedTracks_tmp ) {
    auto minDR_match = *std::min_element( matchedTrk.second.begin(), matchedTrk.second.end(), []
					  ( const auto& lhs, const auto& rhs ) { return lhs.second < rhs.second; } );
    matchedTracks[matchedTrk.first] = minDR_match;
  }

  // map jets to all matched tracks + dRs b/w them
  std::map<const xAOD::Jet*, EJsHelper::TrackLinkVector_t> jets_matchedTracks_link;
  std::map<const xAOD::Jet*, std::vector<float>> jets_matchedTracks_dR;
  for ( const auto& matchedTrk : matchedTracks ) {
    EJsHelper::TrackLink_t link( m_inTrackPartContainerName, matchedTrk.first->auxdataConst<int>("index") );
    jets_matchedTracks_link[ matchedTrk.second.first ] .push_back( link                     );
    jets_matchedTracks_dR  [ matchedTrk.second.first ] .push_back( matchedTrk.second.second );

    // decorate tracks w/ jet-match map info
    matchedTrk.first->auxdecor<char> (decor_trkIsJetMatched)  = true;
    matchedTrk.first->auxdecor<int>  (decor_trkJetMatchID)    = matchedTrk.second.first->auxdataConst<int>("ID");
    matchedTrk.first->auxdecor<int>  (decor_trkJetMatchIndex) = matchedTrk.second.first->auxdataConst<int>("index");
    matchedTrk.first->auxdecor<float>(decor_trkJetMatchDR)    = matchedTrk.second.second;
  }

  // decorate jets w/ matched-tracks map info
  for ( const auto& matchJet : jets_matchedTracks_link )
    matchJet.first->auxdecor<EJsHelper::TrackLinkVector_t>("matchedTrackLinks") = matchJet.second;
  for ( const auto& matchJet : jets_matchedTracks_dR   )
    matchJet.first->auxdecor<std::vector<float>>("matchedTrack_dR")             = matchJet.second;
  
} // end matchTracksToJets

