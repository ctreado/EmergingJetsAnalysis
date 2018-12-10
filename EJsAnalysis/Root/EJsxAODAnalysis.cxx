#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <xAODEventInfo/EventInfo.h>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/EJsxAODAnalysis.h"

// needed to distribute algorithm to workers
ClassImp ( EJsxAODAnalysis )



EJsxAODAnalysis :: EJsxAODAnalysis () : Algorithm ( "EJsxAODAnalysis" )
{
  // code for base initialization of variables, e.g. initialize
  // all pointers to zero; note this method called on submission +
  // worker node, so only put most basic initialization here;
  // most initialization will go in histInitialize() and initialize()
}



EL::StatusCode EJsxAODAnalysis :: setupJob ( EL::Job& job )
{
  // code to set up job on submission object so it's ready to work
  // w/ alg, e.g. request D3PDReader service or add output files;
  // code here automatically activated/deactivated when alg
  // added/removed from job
  
  // initialize alg to use xAODRootAccess package
  job.useXAOD();
  xAOD::Init( "EJsxAODAnalysis" ).ignore(); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: histInitialize ()
{
  // everything that needs to be done at the beginning on each
  // worker node, e.g. create histos + output trees;
  // this method called before any input files connected
  
  ANA_CHECK( xAH::Algorithm::algInitialize() );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: fileExecute ()
{
  // everything that needs to be done exactly once for every
  // single file, e.g. collect list of all lumi-blocks processed

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: changeInput ( bool /*firstFile*/ )
{
  // everything that needs to be done when input files change,
  // e.g. resetting branch addresses on trees; not needed if
  // using D3PDReader or similar service...

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: initialize ()
{
  // everything that needs to be done after first input file
  // connected and before first event processed, e.g. create
  // additional histograms based on variables available in input files;
  // can also create all histograms + trees here, but note this method
  // doesn't get called if no events processed, so objects created
  // here won't be available in output if no input events

  ANA_MSG_INFO( "Initializing EJsxAODAnalysis..." );

  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: execute ()
{
  // everything that needs to be done on every single event,
  // e.g. read input variables, apply cuts, fill histos + trees;
  // here is where most of actual analysis will go...

  // if input comes from xAOD, or not running systematics...
  if ( m_inputAlgo.empty() ) {
    ANA_CHECK( executeSyst ( "" ) ); 
  }
  // otherwise, get list of systematics to run over
  else { 
    // get vector of string giving syst names
    std::vector<std::string>* systNames = 0;
    ANA_CHECK( HelperFunctions::retrieve( systNames, m_inputAlgo, 0, m_store, msg() ) );

    // loop over systematics	       
    std::vector<std::string>* vecOutContainerNames = new std::vector<std::string>;
    for ( const auto& systName : *systNames ) {
      ANA_CHECK( executeSyst ( "" ) );
      // will eventually want to make sure syst passes any cuts we may apply...
      vecOutContainerNames->push_back( systName );
    }

    // save list of systs to be considered downstream
    ANA_CHECK( m_store->record( vecOutContainerNames, m_outputAlgo ) );   
  }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: executeSyst ( std::string syst )
{
  // everything that needs to be on every individual systematic

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: postExecute ()
{
  // everything that need to be done after main event processing;
  // mainly used in implementing NTupleSvc

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: finalize ()
{
  // mirror image of initialize(); gets called after last event
  // processed on worker node; allows finishing up objects created
  // in initialize() before they're written to disk; only gets
  // called on worker nodes that processed input events

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsxAODAnalysis :: histFinalize ()
{
  // mirror image of histInitialize(); gets called after last event
  // processed on worker node; allows finishing up objects created in
  // histInitialize() before they're written to disk; gets called on
  // all worker nodes regardless of whether they processed input events

  return EL::StatusCode::SUCCESS;
}
