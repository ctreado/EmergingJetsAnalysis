#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <xAODAnaHelpers/HistogramManager.h>

#include "EJsAnalysis/HistogramEJsTree.h"

#include "TTree.h"

// needed to distribute algorithm to workers
ClassImp ( HistogramEJsTree )



HistogramEJsTree :: HistogramEJsTree () : Algorithm ( "HistogramEJsTree" ),
  m_jet_pt(0)
{
  // code for base initialization of variables, e.g. initialize
  // all pointers to zero; note this method called on submission +
  // worker node, so only put most basic initialization here;
  // most initialization will go in histInitialize() and initialize()
}



EL::StatusCode HistogramEJsTree :: setupJob ( EL::Job& job )
{
  // code to set up job on submission object so it's ready to work
  // w/ alg, e.g. request D3PDReader service or add output files;
  // code here automatically activated/deactivated when alg
  // added/removed from job

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HistogramEJsTree :: histInitialize ()
{
  // everything that needs to be done at the beginning on each
  // worker node, e.g. create histos + output trees;
  // this method called before any input files connected
  
  ANA_CHECK( xAH::Algorithm::algInitialize() );

  HistogramManager* HM = new HistogramManager ( "HistManager", "HistManager" );

  // book hists
  TTree* tree = wk()->tree();
  h_jet_pt = HM->book( m_name, "jet_pt", "jet p_{T} [GeV]", 100, 0, 3000 );

  // record hists to EventLoop output
  HM->record( wk() );

  ANA_MSG_INFO( "Histograms initialized!" );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HistogramEJsTree :: fileExecute ()
{
  // everything that needs to be done exactly once for every
  // single file, e.g. collect list of all lumi-blocks processed

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HistogramEJsTree :: changeInput ( bool /*firstFile*/ )
{
  // everything that needs to be done when input files change,
  // e.g. resetting branch addresses on trees; not needed if
  // using D3PDReader or similar service...

  // connect tree branches
  TTree* tree = wk()->tree();
  tree->SetBranchStatus( "*", 0 ); // disables all branches

  tree->SetBranchStatus  ( "jet_pt", 1 );
  tree->SetBranchAddress ( "jet_pt", &m_jet_pt );
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HistogramEJsTree :: initialize ()
{
  // everything that needs to be done after first input file
  // connected and before first event processed, e.g. create
  // additional histograms based on variables available in input files;
  // can also create all histograms + trees here, but note this method
  // doesn't get called if no events processed, so objects created
  // here won't be available in output if no input events

  ANA_MSG_INFO( "Initializing HistogramEJsTree..." );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HistogramEJsTree :: execute ()
{
  // everything that needs to be done on every single event,
  // e.g. read input variables, apply cuts, fill histos + trees;
  // here is where most of actual analysis will go...

  ANA_MSG_DEBUG( "Executing HistogramEJsTree algorithm" );

  wk()->tree()->GetEntry ( wk()->treeEntry() );

  for ( size_t i = 0; i != m_jet_pt->size(); ++i )
    h_jet_pt->Fill( m_jet_pt->at(i) );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HistogramEJsTree :: postExecute ()
{
  // everything that need to be done after main event processing;
  // mainly used in implementing NTupleSvc

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HistogramEJsTree :: finalize ()
{
  // mirror image of initialize(); gets called after last event
  // processed on worker node; allows finishing up objects created
  // in initialize() before they're written to disk; only gets
  // called on worker nodes that processed input events

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode HistogramEJsTree :: histFinalize ()
{
  // mirror image of histInitialize(); gets called after last event
  // processed on worker node; allows finishing up objects created in
  // histInitialize() before they're written to disk; gets called on
  // all worker nodes regardless of whether they processed input events

  ANA_CHECK( xAH::Algorithm::algFinalize() );

  return EL::StatusCode::SUCCESS;
}
