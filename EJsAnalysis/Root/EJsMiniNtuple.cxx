#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <xAODEventInfo/EventInfo.h>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/EJsMiniNtuple.h"

// needed to distribute algorithm to workers
ClassImp ( EJsMiniNtuple )



EJsMiniNtuple :: EJsMiniNtuple ()
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

  ANA_MSG_INFO( "setupJob(): calling setupJob" );
  
  // initialize alg to use xAODRootAccess package
  job.useXAOD();
  
  xAOD::Init( "EJsMiniNtuple" ).ignore(); // call before opening first file

  EL::OutputStream outforTree( m_filename.c_str() );
  job.outputAdd( outforTree );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: histInitialize ()
{
  // everything that needs to be done at the beginning on each
  // worker node, e.g. create histos + output trees;
  // this method called before any input files connected

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

  ANA_MSG_INFO( "initialize(): initializing EJsMiniNtuple algorithm" );

  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();

  // set isMC flag
  const xAOD::EventInfo* eventInfo = 0;
  ANA_CHECK( HelperFunctions::retrieve( eventInfo, "EventInfo", m_event, m_store ) );
  m_isMC = eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsMiniNtuple :: execute ()
{
  // everything that needs to be done on every single event,
  // e.g. read input variables, apply cuts, fill histos + trees;
  // here is where most of actual analysis will go...

  ANA_MSG_INFO( "execute(): executing EJsMiniNtuple algorithm" );

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
