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
  for ( const auto& track : *inTrackParts )
    track->auxdecor<int>("ID") = track->index();
  for ( const auto& secVtx : *inSecVerts )
    secVtx->auxdecor<int>("ID") = secVtx->index();
  if ( isMC() ) {
    for ( const auto& truthJet : *inTruthJets )
      truthJet->auxdecor<int>("ID") = truthJet->index();
    for ( const auto& truthDarkJet : *inTruthDarkJets ) {
      truthDarkJet->auxdecor<int>("ID") = truthDarkJet->index();
      truthDarkJet->auxdecor<char>("isTruthMatched") = false;
    }
    for ( const auto& truthPart : *inTruthParts )
      truthPart->auxdecor<int>("ID") = truthPart->index();
    for ( const auto& truthVtx : *inTruthVerts )
      truthVtx->auxdecor<int>("ID") = truthVtx->index();
  }


  // do matching to truth objects
  if ( isMC() ) {
    
    // match tracks to truth particles
    matchTracksToTruthParts( inTruthParts, inTrackParts );

    // match truth vertices to reco secondary vertices
    matchCloseTruthToSecVerts( inSecVerts, inTruthVerts );
    matchLinkedTruthToSecVerts( inSecVerts, inTruthVerts );

    // match truth dark jets to truth jets
    matchTruthJets( inTruthJets, inTruthDarkJets, "", true );

    // match truth vertices to truth (dark) jets
    matchTruthVertsToJets( inTruthJets,     inTruthVerts );
    matchTruthVertsToJets( inTruthDarkJets, inTruthVerts );

    // match reco secondary vertices to truth (dark) jets
    matchSecVertsToJets( inTruthJets,     inSecVerts );
    matchSecVertsToJets( inTruthDarkJets, inSecVerts );

    // match truth particles to truth (dark) jets
    matchTruthPartsToJets( inTruthJets,     inTruthParts );
    matchTruthPartsToJets( inTruthDarkJets, inTruthParts );
    
    // match tracks to truth (dark) jets
    matchTracksToJets( inTruthJets,     inTrackParts );
    matchTracksToJets( inTruthDarkJets, inTrackParts );

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

      if ( isMC() ) {
	// match truth (dark) jets to reco jets
	matchTruthJets( inJets, inTruthJets,     m_inJetContainers.at(i)       );
	matchTruthJets( inJets, inTruthDarkJets, m_inJetContainers.at(i), true );
	
	// match truth particles to reco jets
	matchTruthPartsToJets( inJets, inTruthParts );
	
	// match truth vertices to reco jets
	matchTruthVertsToJets( inJets, inTruthVerts );
      }
    
      // match reco secondary vertices to reco jets
      matchSecVertsToJets( inJets, inSecVerts );
      
      // match tracks to reco jets
      matchTracksToJets( inJets, inTrackParts );
      
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
      
	  if ( isMC() ) {
	    // match truth (dark) jets to reco jets
	    matchTruthJets( inJets, inTruthJets,     m_inJetContainers.at(i) + systName       );
	    matchTruthJets( inJets, inTruthDarkJets, m_inJetContainers.at(i) + systName, true );

	    // match truth particles to reco jets
	    matchTruthPartsToJets( inJets, inTruthParts );
	    
	    // match truth vertices to reco jets
	    matchTruthVertsToJets( inJets, inTruthVerts );	
	  }
	
	  // match reco secondary vertices to reco jets
	  matchSecVertsToJets( inJets, inSecVerts );
	  
	  // match tracks to reco jets
	  matchTracksToJets( inJets, inTrackParts );

	}
	
      } // end loop over input jet containers
      
    } // end loop over systematics
    
  }

  // look what we have in TStore
  if ( msgLvl( MSG::VERBOSE ) ) m_store->print();

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
				       const std::string         jet_string,
				       bool                      matchJetIsDark )
{
  // delta-R match truth (dark) jets to (truth) jets
  
  // set decorator variable names
  std::string decor_isMatched;
  std::string decor_hasMatch;
  std::string decor_matchID;
  std::string decor_matchDR;
  std::string decor_noMatchIDs;
  std::string decor_noMatchDRs;

  if ( jet_string.empty() )
    decor_isMatched = "isTruthMatched";
  else {
    decor_isMatched = "isRecoMatched_" + jet_string;
    // loop over matchJets + initialize decorators for all in container
    for ( const auto& matchJet : *matchJets )
      matchJet->auxdecor<char>(decor_isMatched) = false;
  }
  
  if ( !matchJetIsDark ) {
    decor_hasMatch   = "hasTruthJetMatch";
    decor_matchID    = "truthJetMatchID";
    decor_matchDR    = "truthJetMatchDR";
    decor_noMatchIDs = "truthJetNoMatchIDs";
    decor_noMatchDRs = "truthJetNoMatchDRs";
  }
  else {
    decor_hasMatch   = "hasDarkJetMatch";
    decor_matchID    = "darkJetMatchID";
    decor_matchDR    = "darkJetMatchDR";
    decor_noMatchIDs = "darkJetNoMatchIDs";
    decor_noMatchDRs = "darkJetNoMatchDRs";
  }
  
  // loop over jets
  for ( const auto& jet : *jets ) {

    bool   jetHasMatch = false;
    int    jetMatchID  = -1;
    double jetMatchDR  = AlgConsts::invalidFloat;

    std::vector<int>   jetNoMatchIDs;
    std::vector<float> jetNoMatchDRs;
    
    // loop over matchJets to match to jets
    for ( const auto& matchJet : *matchJets ) {
      
      // skip matchJet if already matched to jet...
      if ( matchJet->auxdecor<char>(decor_isMatched) ) continue;

      // calculate dR b/w jet + matchJet and look for match
      double dR = EJsHelper::deltaR( jet->eta(), matchJet->eta(), jet->phi(), matchJet->phi() );
      if ( dR < m_jet_matchRadius ) { // first match in high-pt order
	matchJet->auxdecor<char>(decor_isMatched) = true;
	jetHasMatch = true;
	jetMatchID  = matchJet->auxdataConst<int>("ID");
	jetMatchDR  = dR;
	break; // match found --> leave matchJet loop + go to next jet
      }
      else {
	jetNoMatchIDs .push_back( matchJet->auxdataConst<int>("ID") );
	jetNoMatchDRs .push_back( dR );
      }
      
    } // end loop over matchJets

    jet->auxdecor<char>(decor_hasMatch)  = jetHasMatch;
    jet->auxdecor<int>(decor_matchID)    = jetMatchID;
    jet->auxdecor<double>(decor_matchDR) = jetMatchDR;
    
    jet->auxdecor<std::vector<int>>(decor_noMatchIDs)   = jetNoMatchIDs;
    jet->auxdecor<std::vector<float>>(decor_noMatchDRs) = jetNoMatchDRs;
    
  } // end loop over jets
  
} // end matchTruthJets



void ObjectMatcher :: matchTruthVertsToJets ( const xAOD::JetContainer* jets,
					      const xAOD::TruthVertexContainer* truthVerts )
{
  // delta-R match truth vertices to jets

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
					    const xAOD::VertexContainer* secVerts )
{
  // delta-R match reco secondary vertices to jets

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
	for ( size_t itrk = 0; itrk != vtx->nTrackParticles(); ++itrk ) {
	  const auto* trk = vtx->trackParticle(itrk);
	  bool trk_isFilt = true;
	  if ( trk->isAvailable<char>("isFiltered") )
	    trk_isFilt = trk->auxdataConst<char>("isFiltered");
	  if ( trk_isFilt ) filteredTracks.push_back( trk );
	}
	vtxP4 = VsiBonsai::sumP4( filteredTracks );
      }

      double vtxEta = vtxP4.Eta();
      double vtxPhi = vtxP4.Phi();
      
      double dR = EJsHelper::deltaR( jet->eta(), vtxEta, jet->phi(), vtxPhi );
      
      if ( dR < jet_radius ) {
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
					      const xAOD::TruthParticleContainer* truthParts )
{
  // delta-R match truth particles to jets

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
					  const xAOD::TrackParticleContainer* tracks )
{
  // delta-R match tracks to jets

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
    for ( size_t itrk = 0; itrk != secVtx->nTrackParticles(); ++itrk ) {
      const auto* trk = secVtx->trackParticle(itrk);
      bool trk_isFilt = true;
      if ( trk->isAvailable<char>("isFiltered") )
	trk_isFilt = trk->auxdataConst<char>("isFiltered");
      if ( trk_isFilt ) filteredTracks.push_back( trk );
    }

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
  
} // end matchLinkedVerts
