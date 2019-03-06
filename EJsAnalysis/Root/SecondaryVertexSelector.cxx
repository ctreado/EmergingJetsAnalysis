#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <AthContainers/ConstDataVector.h>

#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/SecondaryVertexSelector.h"

// needed to distribute algorithm to workers
ClassImp ( SecondaryVertexSelector )



SecondaryVertexSelector :: SecondaryVertexSelector () : Algorithm ( "SecondaryVertexSelector" )
{
  // code for base initialization of variables, e.g. initialize
  // all pointers to zero; note this method called on submission +
  // worker node, so only put most basic initialization here;
  // most initialization will go in histInitialize() and initialize()
}



EL::StatusCode SecondaryVertexSelector :: setupJob ( EL::Job& job )
{
  // code to set up job on submission object so it's ready to work
  // w/ alg, e.g. request D3PDReader service or add output files;
  // code here automatically activated/deactivated when alg
  // added/removed from job
  
  // initialize alg to use xAODRootAccess package
  job.useXAOD();
  xAOD::Init( "SecondaryVertexSelector" ).ignore(); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SecondaryVertexSelector :: histInitialize ()
{
  // everything that needs to be done at the beginning on each
  // worker node, e.g. create histos + output trees;
  // this method called before any input files connected
  
  ANA_CHECK( xAH::Algorithm::algInitialize() );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SecondaryVertexSelector :: fileExecute ()
{
  // everything that needs to be done exactly once for every
  // single file, e.g. collect list of all lumi-blocks processed

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SecondaryVertexSelector :: changeInput ( bool /*firstFile*/ )
{
  // everything that needs to be done when input files change,
  // e.g. resetting branch addresses on trees; not needed if
  // using D3PDReader or similar service...

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SecondaryVertexSelector :: initialize ()
{
  // everything that needs to be done after first input file
  // connected and before first event processed, e.g. create
  // additional histograms based on variables available in input files;
  // can also create all histograms + trees here, but note this method
  // doesn't get called if no events processed, so objects created
  // here won't be available in output if no input events

  ANA_MSG_INFO( "Initializing SecondaryVertexSelector..." );

  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();

  // cutflow

  if ( m_inContainerName.empty() ) {
    ANA_MSG_ERROR( "No input container provided! Exiting." );
    return EL::StatusCode::FAILURE;
  }

  ANA_MSG_DEBUG( "SecondaryVertexSelector Interface successfully initialized!" );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SecondaryVertexSelector :: execute ()
{
  // everything that needs to be done on every single event,
  // e.g. read input variables, apply cuts, fill histos + trees;
  // here is where most of actual analysis will go...

  ANA_MSG_DEBUG( "Applying Secondary Vertex Selection..." );

  // count number of events

  // get secondary vertex collection from TEvent or TStore
  const xAOD::VertexContainer* inSecVerts = 0;
  ANA_CHECK( HelperFunctions::retrieve( inSecVerts, m_inContainerName, m_event, m_store, msg() ) );

  // create output container (if requested) -- deep copy
  auto selectedSecVerts =
    std::make_unique<ConstDataVector<xAOD::VertexContainer>>(SG::VIEW_ELEMENTS);
  
  for ( const auto& vtx : *inSecVerts ) {
    int passSel = this->PassCuts( vtx );
    if ( m_decorateSelectedObjects ) vtx->auxdecor<char>( "passSel" ) = passSel;

    if ( !passSel ) continue;
    
    // copy selected vertex to ouput container (if requested)
    if ( m_createSelectedContainer ) selectedSecVerts->push_back( vtx );
  }

  // apply event selected based on min/max requirements on number of objects passing cuts per event

  // add output container to TStore
  if ( m_createSelectedContainer )
    ANA_CHECK( m_store->record( selectedSecVerts.release(), m_outContainerName ) );

  // cutflow

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SecondaryVertexSelector :: postExecute ()
{
  // everything that need to be done after main event processing;
  // mainly used in implementing NTupleSvc

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SecondaryVertexSelector :: finalize ()
{
  // mirror image of initialize(); gets called after last event
  // processed on worker node; allows finishing up objects created
  // in initialize() before they're written to disk; only gets
  // called on worker nodes that processed input events

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SecondaryVertexSelector :: histFinalize ()
{
  // mirror image of histInitialize(); gets called after last event
  // processed on worker node; allows finishing up objects created in
  // histInitialize() before they're written to disk; gets called on
  // all worker nodes regardless of whether they processed input events

  ANA_CHECK( xAH::Algorithm::algFinalize() );

  return EL::StatusCode::SUCCESS;
}



int SecondaryVertexSelector :: PassCuts ( const xAOD::Vertex* vtx )
{
  // here's where we do the cuts --> if vertex fails cuts, return 0

  // filter vertex tracks using VsiBonsai config
  std::vector<const xAOD::TrackParticle*> filteredTracks;
  
  for ( size_t i = 0; i != vtx->nTrackParticles(); ++i ) {
    bool failedTrimmers = false;
    const auto* trk = vtx->trackParticle(i);
    
    // do trimming... --> have config option, "do_trackTrimming" ...

    trk->auxdecor<char>( "isFiltered" ) = !failedTrimmers;

    if ( failedTrimmers ) continue;
    filteredTracks.push_back( trk ); // save filtered tracks
  }

  // material map veto... --> have config option, "do_matMapVeto" ...

  if ( filteredTracks.size() < 2 ) return 0;

  // other vertex cuts...
  
  return 1;
}
