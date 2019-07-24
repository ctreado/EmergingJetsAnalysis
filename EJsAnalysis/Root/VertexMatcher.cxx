#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/VertexMatcher.h"
#include "EJsAnalysis/EJsHelperFunctions.h"

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

  ANA_MSG_INFO( "Initializing ObjectMatcher..." );

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

  // retrieve truth + reco vertex containers
  const xAOD::TruthVertexContainer* inTruthVerts = 0;
  ANA_MSG_DEBUG( "Getting input truth vertex container: " << m_inTruthVertexContainerName );
  ANA_CHECK( HelperFunctions::retrieve( inTruthVerts, m_inTruthVertexContainerName, m_event, m_store, msg() ) );

  const xAOD::VertexContainer* inSecVerts   = 0;
  ANA_MSG_DEBUG( "Getting input secondary vertex container: " << m_inSecondaryVertexContainerName );
  ANA_CHECK( HelperFunctions::retrieve( inSecVerts, m_inSecondaryVertexContainerName, m_event, m_store, msg() ) );

  // do distance-based matching
  //matchClosestVerts ( inSecVerts, inTruthVerts );

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


// void VertexMatcher :: matchClosestVerts ( const xAOD::VertexContainer* secVerts, const xAOD::TruthVertexContainer* truthVerts )
// {
//   // distance-based matching b/w reco secondary + truth vertices --> find closest vertices

//   // find reco vertex closest to truth --> loop over truth vertices
//   for ( const auto& truthVtx : *truthVerts ) {

//     // loop over reco secondary vertices
//     for ( const auto& secVtx : *secVerts ) {

//       // calculate distance b/w truth + reco vertex positions
//       TVector3 reco_pos   (   secVtx->x(),   secVtx->y(),   secVtx->z() );
//       TVector3 truth_pos  ( truthVtx->x(), truthVtx->y(), truthVtx->z() );
//       double   distance = ( reco_pos - truth_pos ).Mag();
//       if ( distance < recoToTruthDistance ) {
// 	closestRecoVertex   = secVtx;
// 	recoToTruthDistance = distance;
//       }
      
//     } // end loop over reco vertices
    
//   } // end loop over truth vertices

  
//   // find truth vertex closest to reco --> loop over reco secondary vertices
//   for ( const auto& secVtx : *secVerts ) {

//     // loop over truth vertices
//     for ( const auto& truthVtx : *truthVerts ) {

//       // calculate distance b/w reco + truth vertex positions
//       TVector3 truth_pos  ( truthVtx->x(), truthVtx->y(), truthVtx->z() );
//       TVector3 reco_pos   (   secVtx->x(),   secVtx->y(),   secVtx->z() );
//       double   distance = ( truth_pos - reco_pos ).Mag();
//       if ( distance < truthToRecoDistance ) {
// 	closestTruthVertex  = truthVtx;
// 	truthToRecoDistance = distance;
//       }
//     }
//   }
  
// }



// void VertexMatcher :: matchClosestVerts ( const xAOD::VertexContainer* secVerts, const xAOD::TruthVertexContainer* truthVerts )
// {
//   // distance-based matching b/w reco secondary + truth vertices
//   // --> eventually will want to calculate reco distance from "representative truth vertex position 'TruthVertexPos'"...
//   // ... of "reconstructible LLP decays" (see VsiPerf::VsiEfficiencyProcessor alg)
//   // --> will also want separate function to match all close/representative (w/in certain matching distance) reco to truth...
//   // ...using 'TruthVertexPos' / VsiPerf::VsiEfficiencyProcessor methods

//   // find reco vertex closest to truth
//   // loop over truth vertices
//   for ( const auto& truthVtx : *truthVerts ) {

//     // // --> don't want to do filtering here, but keep for future reference for use in other matching function...
//     // // filter truth vertices for LLP decays
//     // std::string llpDecayType  = "";
//     // bool        passFilterLLP = false;
//     // for ( size_t i = 0; i != m_truthLLP_decays.size(); ++i ) {
//     //   if ( EJsHelper::pdgIdFuncs[m_truthLLP_decays.at(i)]( truthVtx ) ) {
//     // 	llpDecayType = m_truthLLP_decays.at(i);
//     // 	passFilterLLP = true;
//     //   }
//     // }
//     // if ( m_filterTruthVertex_llp && !passFilterLLP ) continue;

//     // loop over reco secondary vertices
//     for ( const auto& secVtx : *secVerts ) {

//       // calculate distance b/w truth + reco vertex positions
//       TVector3 reco_pos   (   secVtx->x(),   secVtx->y(),   secVtx->z() );
//       TVector3 truth_pos  ( truthVtx->x(), truthVtx->y(), truthVtx->z() );
//       double   distance = ( reco_pos - truth_pos ).Mag();
//       // // count as "close" if w/in matching distance
//       // if ( distance < m_vtx_matchDistance ) {
//       // 	++n_closeSecVerts;
//       // 	//closeSecVerts[secVtx] .push_back( std::make_pair( truthVtx, distance ) );
//       // }
//       std::cout << distance << std::endl;
      
//     }
    
//   } // end loop over truth vertices
  

  
// }


// --> FIGURE OUT... NOT SURE HOW WE WANT TO DO THIS YET...
