#include <map>
#include <tuple>

#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/VertexMatcher.h"
#include "EJsAnalysis/EJsHelperFunctions.h"
#include "EJsAnalysis/TruthVertexPosition.h"

// needed to distribute algorithm to workers
ClassImp ( VertexMatcher )



VertexMatcher :: VertexMatcher () : Algorithm ( "VertexMatcher" )
{
  // code for base initialization of variables, e.g. initialize
  // all pointers to zero; note this method called on submission +
  // worker node, so only put most basic initialization here;
  // most initialization will go in histInitialize() and initialize()
}



EL::StatusCode VertexMatcher :: setupJob ( EL::Job& job )
{
  // code to set up job on submission object so it's ready to work
  // w/ alg, e.g. request D3PDReader service or add output files;
  // code here automatically activated/deactivated when alg
  // added/removed from job
  
  // initialize alg to use xAODRootAccess package
  job.useXAOD();
  xAOD::Init( "VertexMatcher" ).ignore(); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode VertexMatcher :: histInitialize ()
{
  // everything that needs to be done at the beginning on each
  // worker node, e.g. create histos + output trees;
  // this method called before any input files connected
  
  ANA_CHECK( xAH::Algorithm::algInitialize() );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode VertexMatcher :: fileExecute ()
{
  // everything that needs to be done exactly once for every
  // single file, e.g. collect list of all lumi-blocks processed

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode VertexMatcher :: changeInput ( bool /*firstFile*/ )
{
  // everything that needs to be done when input files change,
  // e.g. resetting branch addresses on trees; not needed if
  // using D3PDReader or similar service...

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode VertexMatcher :: initialize ()
{
  // everything that needs to be done after first input file
  // connected and before first event processed, e.g. create
  // additional histograms based on variables available in input files;
  // can also create all histograms + trees here, but note this method
  // doesn't get called if no events processed, so objects created
  // here won't be available in output if no input events

  ANA_MSG_INFO( "Initializing VertexMatcher..." );

  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();

  // check for input containers
  if ( m_inSecondaryVertexContainerName.empty() ) {
    ANA_MSG_ERROR( "No input secondary vertex container provided! Exiting." );
    return EL::StatusCode::FAILURE;
  }

  // to handle more than one type of llp decay vertex
  std::string token;
  std::istringstream ss_llp_decays( m_truthLLP );
  while ( std::getline( ss_llp_decays, token, ' ' ) )
    m_truthLLP_decays.push_back( token );

  // initialize counters
  m_eventNumber = 0;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode VertexMatcher :: execute ()
{
  // everything that needs to be done on every single event,
  // e.g. read input variables, apply cuts, fill histos + trees;
  // here is where most of actual analysis will go...

  ANA_MSG_DEBUG( "Applying Truth-Reco Vertex Matching..." );

  // retrieve truth + track particle containers
  const xAOD::TruthParticleContainer* inTruthParts = 0;
  ANA_MSG_DEBUG( "Getting input truth particle container: " << m_inTruthPartContainerName );
  ANA_CHECK( HelperFunctions::retrieve( inTruthParts, m_inTruthPartContainerName, m_event, m_store, msg() ) );

  const xAOD::TrackParticleContainer* inTrackParts = 0;
  ANA_MSG_DEBUG( "Getting input track particle container: " << m_inTrackPartContainerName );
  ANA_CHECK( HelperFunctions::retrieve( inTrackParts, m_inTrackPartContainerName, m_event, m_store, msg() ) );

  // initialize truth particle decorators
  int truthPart_index = 0;
  for ( const auto& truthPart : *inTruthParts ) {
    truthPart->auxdecor<int>("ID")                           = truthPart->index();
    truthPart->auxdecor<int>("index")                        = truthPart_index;
    truthPart->auxdecor<char>("isReconstructibleDescendant") = false;
    truthPart->auxdecor<EJsHelper::TruthVertexLinkVector_t>("truthVertexAncestorLinks") =
      EJsHelper::TruthVertexLinkVector_t();
    ++truthPart_index;
  }
  
  // create truth - track hash table
  m_truthTrackHash.clear();
  for ( const auto& trk : *inTrackParts ) {
    const auto* truth = EJsHelper::getTruthPart( trk ); // get track-linked truth particle
    if ( !truth ) continue;
    m_truthTrackHash[truth] = trk;
  }
  if ( m_doTruthTrackMatching )
    matchTracksToTruthParts( inTruthParts, inTrackParts );
  
  // retrieve truth + reco vertex containers
  const xAOD::TruthVertexContainer* inTruthVerts = 0;
  ANA_MSG_DEBUG( "Getting input truth vertex container: " << m_inTruthVertexContainerName );
  ANA_CHECK( HelperFunctions::retrieve( inTruthVerts, m_inTruthVertexContainerName, m_event, m_store, msg() ) );

  const xAOD::VertexContainer* inSecVerts   = 0;
  ANA_MSG_DEBUG( "Getting input secondary vertex container: " << m_inSecondaryVertexContainerName );
  ANA_CHECK( HelperFunctions::retrieve( inSecVerts, m_inSecondaryVertexContainerName, m_event, m_store, msg() ) );

  // initialize reco vertex decorators
  int secVtx_index = 0;
  for ( const auto& secVtx : *inSecVerts ) {
    secVtx->auxdecor<int>("ID")    = secVtx->index();
    secVtx->auxdecor<int>("index") = secVtx_index;
    secVtx->auxdecor<EJsHelper::TruthVertexLink_t>("closestTruthVertexLink")      = EJsHelper::TruthVertexLink_t();
    secVtx->auxdecor<int>("closestTruthVertexPhysPosID")                          = AlgConsts::invalidInt;
    secVtx->auxdecor<TVector3>("closestTruthVertexPhysPosition")                  = TVector3();
    secVtx->auxdecor<float>("closestTruthVertexPhysPosDistance")                  = AlgConsts::invalidFloat;
    secVtx->auxdecor<EJsHelper::TruthVertexLinkVector_t>("truthVertexMatchLinks") = EJsHelper::TruthVertexLinkVector_t();
    secVtx->auxdecor<std::vector<float>>("truthVertexMatchScores")                = std::vector<float>();
    secVtx->auxdecor<std::vector<int>>("truthVertexMatchReprTruthPosIDs")         = std::vector<int>();
    secVtx->auxdecor<std::vector<TVector3>>("truthVertexMatchReprTruthPositions") = std::vector<TVector3>();
    secVtx->auxdecor<std::vector<TVector3>>("truthVertexMatchResiduals")          = std::vector<TVector3>();
    ++secVtx_index;
  }

  // initialize matched reco vertex map
  std::map<const xAOD::Vertex*, std::vector<std::pair<EJs::TruthVertexPosition, float>> > matchedRecoVerts;
  // initialize vector for ALL truth vertex physical positions
  std::vector<EJs::TruthVertexPosition> truthVtxPhysPositions_all;

  // initialize reconstructible descendant map
  std::map<const xAOD::TruthParticle*, std::vector<const xAOD::TruthVertex*>> recoDesc_truthVerts;
  
  // loop over truth vertices
  int  truthVtx_index = 0;
  for ( const auto& truthVtx : *inTruthVerts ) {

    // initialize truth vertex decorators
    truthVtx->auxdecor<int>("ID")                 = truthVtx->index();
    truthVtx->auxdecor<int>("index")              = truthVtx_index;
    truthVtx->auxdecor<char>("isReconstructible") = false;
    truthVtx->auxdecor<EJsHelper::TruthParticleLinkVector_t>("reconstructibleDescendantLinks") =
      EJsHelper::TruthParticleLinkVector_t();
    truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("closestRecoVertexLinks")      = EJsHelper::VertexLinkVector_t();
    truthVtx->auxdecor<std::vector<float>>("closestRecoVertexDistances")             = std::vector<float>();
    truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("matchedRecoVertexLinks")      = EJsHelper::VertexLinkVector_t();
    truthVtx->auxdecor<std::vector<float>>("matchedRecoVertexMatchScores")           = std::vector<float>();
    truthVtx->auxdecor<std::vector<int>>("matchedRecoVertexReprTruthPosIDs")         = std::vector<int>();
    truthVtx->auxdecor<std::vector<TVector3>>("matchedRecoVertexReprTruthPositions") = std::vector<TVector3>();
    truthVtx->auxdecor<std::vector<TVector3>>("matchedRecoVertexResiduals")          = std::vector<TVector3>();
    ++truthVtx_index;

    // filter truth vertices for LLP decays
    std::string llpDecayType  = "";
    bool        passFilterLLP = false;
    for ( size_t i = 0; i != m_truthLLP_decays.size(); ++i ) {
      if ( EJsHelper::pdgIdFuncs[m_truthLLP_decays.at(i)]( truthVtx ) ) {
    	llpDecayType = m_truthLLP_decays.at(i);
    	passFilterLLP = true;
      }
    }
    if ( m_filterTruthVertex_llp && !passFilterLLP ) continue;

    // cut on truth vertices outside fidual volume
    bool inFiducialVolume = true;
    if ( truthVtx->perp() > 563 || fabs( truthVtx->z() ) > 2720 ) inFiducialVolume = false; // outside SCT
    int nOut = 0;
    for ( size_t i = 0; i != truthVtx->nOutgoingParticles(); ++i ) {
      const auto* outPart = truthVtx->outgoingParticle( i );
      if ( !outPart ->charge()    ) continue;
      if (  outPart ->pt() < 1000 ) continue; // loosen to 500 ??
      ++nOut;
    }
    if ( nOut < 2 ) inFiducialVolume = false; // less than two charged, pT>1GeV outgoing particles
    if ( m_applyFiducialVolumeCut && !inFiducialVolume ) continue;

    // count reconstructible outgoing particles / descendants
    std::set<const xAOD::TruthParticle*> reconstructibleDescendants;
    collectReconstructibleDescendants ( truthVtx, reconstructibleDescendants );
    
    // create element link vector of reconstructible descendants + decorate truth vertex
    EJsHelper::TruthParticleLinkVector_t recoDescLinks;
    for ( const auto& truth : reconstructibleDescendants ) {
      EJsHelper::TruthParticleLink_t link( m_inTruthPartContainerName, truth->auxdataConst<int>("index") );
      recoDescLinks.push_back( link );
    }
    truthVtx->auxdecor<EJsHelper::TruthParticleLinkVector_t>("reconstructibleDescendantLinks") = recoDescLinks;

    // fill truth vertex position vector (TruthVertexPosition class -- physical position, associated truth + tracks)
    std::vector<EJs::TruthVertexPosition> truthVtxPhysPositions;
    int pos_index = 0;
    for ( const auto& truth : reconstructibleDescendants ) {
      
      // map descendants to all corresponding truth vertex ancestors
      recoDesc_truthVerts[truth] .push_back( truthVtx );
      
      if ( !truth->hasProdVtx() ) continue;
      if ( !truth->prodVtx()    ) continue;
      
      bool found_pos = false;
      for ( auto& pos : truthVtxPhysPositions ) {
      	// add truth particle descendant to set associated w/ this position (if compatible, i.e w/in certain 3d distance)
      	if ( pos.isCompatibleWith( truth ) ) {
      	  pos.emplace( truth );
      	  found_pos = true;
      	  break;
      	}
      }
      // otherwise, add new position for this truth particle
      if ( !found_pos ) {
      	truthVtxPhysPositions.emplace_back( EJs::TruthVertexPosition( truth, pos_index, truthVtx ) );
	++pos_index;
      }
    }
    
    // associate corresponding truth-linked tracks to truth vertex positions
    for ( auto& pos : truthVtxPhysPositions )
      pos.storeTracks( m_truthTrackHash );

    // save all truth vertex physical positions
    for ( const auto& pos : truthVtxPhysPositions )
      truthVtxPhysPositions_all.emplace_back( pos );

    // find closest reco vertex to each truth vertex physical position
    EJsHelper::VertexLinkVector_t closestRecoVtxLinks;
    std::vector<float> closestRecoVtxDistances;
    for ( const auto& pos : truthVtxPhysPositions ) {
      
      const xAOD::Vertex* closestRecoVertex = 0;
      double closestDistance = AlgConsts::maxValue;
      
      for ( const auto& secVtx : *inSecVerts ) {
	TVector3 secVtxPos  ( secVtx->x(), secVtx->y(), secVtx->z() );
	double   distance = ( pos.position() - secVtxPos ).Mag();

	if ( distance < closestDistance ) {
	  closestRecoVertex = secVtx;
	  closestDistance   = distance;
	}
      }
      if ( closestRecoVertex ) {
	EJsHelper::VertexLink_t link( m_inSecondaryVertexContainerName, closestRecoVertex->auxdataConst<int>("index") );
	closestRecoVtxLinks     .push_back( link            );
	closestRecoVtxDistances .push_back( closestDistance );
      }
    }
    truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("closestRecoVertexLinks") = closestRecoVtxLinks;
    truthVtx->auxdecor<std::vector<float>>("closestRecoVertexDistances")        = closestRecoVtxDistances;

    // count number of reconstructed (selected) descendants
    std::set<const xAOD::TruthParticle*> reconstructedDescendants;
    std::set<const xAOD::TruthParticle*> reconstructedDescendants_selected;
    for ( const auto& truth : reconstructibleDescendants ) {
      bool isReconstructed = m_truthTrackHash.find( truth ) != m_truthTrackHash.end();
      bool isSelected      = false;
      if ( isReconstructed ) {
	reconstructedDescendants .emplace( truth );
	const auto* track = m_truthTrackHash.at( truth );
	if ( track->isAvailable<char>("is_selected") )
	  if ( track->auxdataConst<char>("is_selected") ) isSelected = true;
      }
      if ( isSelected )
	reconstructedDescendants_selected .emplace( truth );
    }
    
    // require at least 2 reconstructed selected descendants for truth vertex to be "reconstructible"...
    if ( reconstructedDescendants_selected.size() < 2 ) continue;
    truthVtx->auxdecor<char>("isReconstructible") = true;

    // loop over reco vertices + search for matches to truth vertex (positions)
    EJsHelper::VertexLinkVector_t matchedRecoVtxLinks;
    std::vector<float>            matchedRecoVtxMatchScores;
    std::vector<int>              matchedRecoVtxReprTruthPosIDs;
    std::vector<TVector3>         matchedRecoVtxReprTruthPositions;
    std::vector<TVector3>         matchedRecoVtxResiduals;
    for ( const auto& secVtx : *inSecVerts ) {

      TVector3 secVtxPos ( secVtx->x(), secVtx->y(), secVtx->z() );
      
      // sum reco vertex track pt
      double secVtxTrkSumPt = 0.0;
      for ( size_t i = 0; i != secVtx->nTrackParticles(); ++i ) {
	const auto* track = secVtx->trackParticle(i);
	if ( !track ) continue;
	secVtxTrkSumPt += track->pt();
      }
      
      // loop over truth vertex positions + search for reco vertex tracks
      std::map<EJs::TruthVertexPosition, double> vtxCompositions;
      for ( const auto& pos : truthVtxPhysPositions ) {
      	for ( size_t i = 0; i != secVtx->nTrackParticles(); ++i ) {
      	  const auto* track = secVtx->trackParticle(i);
	  // weight truth-vertex-position reco-vertex composition by track-pt
      	  if ( pos.find( track ) ) vtxCompositions[pos] += track->pt();
      	}
      }

      // skip reco vertex if not at all associated w/ any truth position
      if ( vtxCompositions.empty() ) continue;

      // find representative truth position w/ maximal reco-vertex composition + calculate reco-truth match score
      auto representative = std::max_element( vtxCompositions.begin(), vtxCompositions.end(), []
      					      ( const auto& lhs, const auto& rhs ) { return lhs.second < rhs.second; } );
      double   matchScore = (*representative).second / secVtxTrkSumPt;
      TVector3 residual   = (*representative).first.position() - secVtxPos;
      
      if ( matchScore    < m_vtx_matchScore ) continue;
      if ( residual.Mag() > m_vtx_residual  ) continue;
   
      // if we made it this far, reco vertex is a match...
      EJsHelper::VertexLink_t recolink( m_inSecondaryVertexContainerName, secVtx->auxdataConst<int>("index") );
      matchedRecoVtxLinks              .push_back( recolink                           );
      matchedRecoVtxMatchScores        .push_back( matchScore                         );
      matchedRecoVtxReprTruthPosIDs    .push_back( (*representative).first.ID()       );
      matchedRecoVtxReprTruthPositions .push_back( (*representative).first.position() );
      matchedRecoVtxResiduals          .push_back( residual                           );

      // map matched reco vertices to all matching truth vertices --> can find single best match later...
      matchedRecoVerts[secVtx] .push_back( std::make_pair( (*representative).first, matchScore ) );
      
    } // end loop over secondary vertices
    
    truthVtx->auxdecor<EJsHelper::VertexLinkVector_t>("matchedRecoVertexLinks")      = matchedRecoVtxLinks;
    truthVtx->auxdecor<std::vector<float>>("matchedRecoVertexMatchScores")           = matchedRecoVtxMatchScores;
    truthVtx->auxdecor<std::vector<int>>("matchedRecoVertexReprTruthPosIDs")         = matchedRecoVtxReprTruthPosIDs;
    truthVtx->auxdecor<std::vector<TVector3>>("matchedRecoVertexReprTruthPositions") = matchedRecoVtxReprTruthPositions;
    truthVtx->auxdecor<std::vector<TVector3>>("matchedRecoVertexResiduals")          = matchedRecoVtxResiduals;

  } // end loop over truth vertices

  // decorate reconstructible descendants w/ corresponding truth-vertex-ancestor info
  for ( const auto& desc : recoDesc_truthVerts ) {
    EJsHelper::TruthVertexLinkVector_t truthVtxAncLinks;
    for ( size_t i = 0; i != desc.second.size(); ++i ) {
      EJsHelper::TruthVertexLink_t ancestorlink( m_inTruthVertexContainerName, desc.second.at(i)->auxdataConst<int>("index") );
      truthVtxAncLinks .push_back( ancestorlink );
    }
    desc.first->auxdecor<char>("isReconstructibleDescendant") = true;
    desc.first->auxdecor<EJsHelper::TruthVertexLinkVector_t>("truthVertexAncestorLinks") = truthVtxAncLinks;
  }

  // decorate matched reco vertices w/ corresponding truth-vertex info
  for ( const auto& match : matchedRecoVerts ) {
    EJsHelper::TruthVertexLinkVector_t truthVtxLinks;
    std::vector<float>    matchScores;
    std::vector<int>      reprTruthPosIDs;
    std::vector<TVector3> reprTruthPositions;
    std::vector<TVector3> residuals;
    for ( size_t i = 0; i != match.second.size(); ++i ) {
      
      TVector3 secVtxPos ( match.first->x(), match.first->y(), match.first->z() );
      
      EJsHelper::TruthVertexLink_t truthlink( m_inTruthVertexContainerName,
					      match.second.at(i).first.truth_vtx()->auxdataConst<int>("index") );
      truthVtxLinks      .push_back( truthlink                                       );
      matchScores        .push_back( match.second.at(i).second                       );
      reprTruthPosIDs    .push_back( match.second.at(i).first.ID()                   );
      reprTruthPositions .push_back( match.second.at(i).first.position()             );
      residuals          .push_back( match.second.at(i).first.position() - secVtxPos );
    }
    match.first->auxdecor<EJsHelper::TruthVertexLinkVector_t>("truthVertexMatchLinks") = truthVtxLinks;
    match.first->auxdecor<std::vector<float>>("truthVertexMatchScores")                = matchScores;
    match.first->auxdecor<std::vector<int>>("truthVertexMatchReprTruthPosIDs")         = reprTruthPosIDs;
    match.first->auxdecor<std::vector<TVector3>>("truthVertexMatchReprTruthPositions") = reprTruthPositions;
    match.first->auxdecor<std::vector<TVector3>>("truthVertexMatchResiduals")          = residuals;
  }

  // find closest truth vertex (physical position) to each reco vertex
  for ( const auto& secVtx : *inSecVerts ) {

    EJs::TruthVertexPosition closestTruthVtxPhysPos;
    double closestDistance    = AlgConsts::maxValue;
    bool   closestTruthVertex = false;
    
    TVector3 secVtxPos ( secVtx->x(), secVtx->y(), secVtx->z() );

    for ( const auto& pos : truthVtxPhysPositions_all ) {
      double distance = ( secVtxPos - pos.position() ).Mag();
      if ( distance < closestDistance ) {
    	closestTruthVtxPhysPos = pos;
    	closestDistance        = distance;
	closestTruthVertex     = true;
      }
    }
    if ( closestTruthVertex ) {
      EJsHelper::TruthVertexLink_t truthposlink( m_inTruthVertexContainerName,
    						 closestTruthVtxPhysPos.truth_vtx()->auxdataConst<int>("index") );
      secVtx->auxdecor<EJsHelper::TruthVertexLink_t>("closestTruthVertexLink") = truthposlink;
      secVtx->auxdecor<int>("closestTruthVertexPhysPosID")                     = closestTruthVtxPhysPos.ID();
      secVtx->auxdecor<TVector3>("closestTruthVertexPhysPosition")             = closestTruthVtxPhysPos.position();
      secVtx->auxdecor<float>("closestTruthVertexPhysPosDistance")             = closestDistance;
    }
  }
  
  // look what we have in store
  if ( msgLvl( MSG::VERBOSE ) ) m_store->print();

  ++m_eventNumber;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode VertexMatcher :: postExecute ()
{
  // everything that need to be done after main event processing;
  // mainly used in implementing NTupleSvc

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode VertexMatcher :: finalize ()
{
  // mirror image of initialize(); gets called after last event
  // processed on worker node; allows finishing up objects created
  // in initialize() before they're written to disk; only gets
  // called on worker nodes that processed input events

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode VertexMatcher :: histFinalize ()
{
  // mirror image of histInitialize(); gets called after last event
  // processed on worker node; allows finishing up objects created in
  // histInitialize() before they're written to disk; gets called on
  // all worker nodes regardless of whether they processed input events

  ANA_CHECK( xAH::Algorithm::algFinalize() );

  return EL::StatusCode::SUCCESS;
}



void VertexMatcher :: collectReconstructibleDescendants ( const xAOD::TruthVertex* truthVtx,
							  std::set<const xAOD::TruthParticle*>& truthPartSet )
{
  // collect set of all potentially reconstructible descendants of LLP decay

  // skip vertices outside fiducial volume (outside SCT)
  if ( truthVtx->perp() > 563.       ) return;
  if ( fabs( truthVtx->z() ) > 2720. ) return;

  // loop over truth vertex outgoing particles
  for ( size_t i = 0; i != truthVtx->nOutgoingParticles(); ++i ) {
    const auto* truthPart = truthVtx->outgoingParticle(i);
    if ( !truthPart ) continue;

    // recursively add descendants of LLP decay
    if ( truthPart->hasDecayVtx() ) {

      // get distance b/w particle production + decay
      TVector3 prodPos  ( truthPart->prodVtx()->x(),  truthPart->prodVtx()->y(),  truthPart->prodVtx()->z()  );
      TVector3 decayPos ( truthPart->decayVtx()->x(), truthPart->decayVtx()->y(), truthPart->decayVtx()->z() );

      const auto distance = ( decayPos - prodPos ).Mag();

      // for particle production r > 300mm, tracking efficiency degrades rapidly due to minimum seven hits requirement in LRT algs
      auto isInside  = []( TVector3& v ) { return ( v.Perp() < 300. && fabs( v.z() ) < 1500. ); };
      auto isOutside = []( TVector3& v ) { return ( v.Perp() > 563. || fabs( v.z() ) > 2720. ); };

      if ( distance < m_distanceCutoff ) {
	if ( m_doRecursive ) collectReconstructibleDescendants ( truthPart->decayVtx(), truthPartSet );
      }
      else if ( isInside( prodPos ) && isOutside( decayPos ) &&
		truthPart->charge() && truthPart->pt() > m_ptThreshold ) {
	truthPartSet.emplace( truthPart );
      }
      else if ( truthPart->isElectron() || truthPart->isMuon() ) {
	truthPartSet.emplace( truthPart );
      }
    }
    // we've reached stable particle...
    else {
      if ( !truthPart->charge() || truthPart->pt() < m_ptThreshold ) continue;
      truthPartSet.emplace( truthPart );
    }
  } // end loop over outgoing particles
} // end collectReconstructibleDescendants



void VertexMatcher :: matchTracksToTruthParts ( const xAOD::TruthParticleContainer* parts,
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
