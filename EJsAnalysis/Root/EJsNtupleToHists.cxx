#include <TFile.h>
#include <TTree.h>

#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include "EJsAnalysis/EJsNtupleToHists.h"


// needed to distribute algorithm to workers
ClassImp ( EJsNtupleToHists )



EJsNtupleToHists :: EJsNtupleToHists () : Algorithm ( "EJsNtupleToHists" )
{
  // code for base initialization of variables, e.g. initialize
  // all pointers to zero; note this method called on submission +
  // worker node, so only put most basic initialization here;
  // most initialization will go in histInitialize() and initialize()
}



EL::StatusCode EJsNtupleToHists :: setupJob ( EL::Job& job )
{
  // code to set up job on submission object so it's ready to work
  // w/ alg, e.g. request D3PDReader service or add output files;
  // code here automatically activated/deactivated when alg
  // added/removed from job

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsNtupleToHists :: histInitialize ()
{
  // everything that needs to be done at the beginning on each
  // worker node, e.g. create histos + output trees;
  // this method called before any input files connected
  
  ANA_CHECK( xAH::Algorithm::algInitialize() );

  // get tree name
  TTree* inTree = wk()->tree();
  std::string outFileName = inTree->GetName();

  // get list of regions to run over
  std::string token;
  std::istringstream ss_region_names( m_regionName );
  while ( std::getline( ss_region_names, token, ' ' ) )
    m_regionNames.push_back( token );
  // set singular region to ALL by default
  if ( m_regionNames.empty() )
    m_regionNames.push_back( "all" );
  // fill regions
  for ( size_t i = 0; i != m_regionNames.size(); ++i ) {
    EJsHelper::Region region;
    EJsHelper::fillRegion( region, m_regionNames.at(i) );
    m_regions.push_back( region );
  }

  // set emtopo / pflow booleans
  m_doEMTopo = false; m_doPFlow = false;
  if ( m_jetBranchName.find("EMTopo") != std::string::npos || m_jetBranchName.find("emtopo") != std::string::npos || m_jetEMTopo ) {
    m_doEMTopo = true;
    m_doPFlow  = false;
  }
  if ( m_jetBranchName.find("PFlow")  != std::string::npos || m_jetBranchName.find("pflow")  != std::string::npos || m_jetPFlow  ) {
    m_doEMTopo = false;
    m_doPFlow  = true;
  }

  // get input file name to set m_isMC
  TFile* inputFile = wk()->inputFile();
  std::string fileName = inputFile->GetName();
  m_isMC = true;
  if ( ( fileName.find("data1") != std::string::npos ) || ( fileName.find("Data1") != std::string::npos ) )
    m_isMC = false;


  // declare classes and add histograms to output
  m_plots = new EJsHistogramManager ( m_name, m_detailStr, false, m_doEMTopo, m_doPFlow );
  ANA_CHECK( m_plots ->initialize( m_jetBranchName, outFileName, m_regionNames, m_isMC ) );
  m_plots ->record( wk() );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsNtupleToHists :: fileExecute ()
{
  // everything that needs to be done exactly once for every
  // single file, e.g. collect list of all lumi-blocks processed

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsNtupleToHists :: changeInput ( bool /*firstFile*/ )
{
  // everything that needs to be done when input files change,
  // e.g. resetting branch addresses on trees; not needed if
  // using D3PDReader or similar service...

  // get input file name
  TFile* inputFile = wk()->inputFile();
  std::string fileName = inputFile->GetName();

  // set m_isMC
  m_isMC = true;
  if ( ( fileName.find("data1") != std::string::npos ) || ( fileName.find("Data1") != std::string::npos ) )
    m_isMC = false;
  
  // connect tree branches
  TTree* tree = wk()->tree();
  tree->SetBranchStatus( "*", 0 ); // disables all branches

  ANA_CHECK( m_plots ->connectEvents   ( tree, m_isMC ) );
  ANA_CHECK( m_plots ->connectTriggers ( tree, m_isMC ) );
  
  ANA_CHECK( m_plots ->connectJets           ( tree, m_jetBranchName,             m_isMC ) );
  ANA_CHECK( m_plots ->connectTrigJets       ( tree, m_trigJetBranchName,         m_isMC ) );
  ANA_CHECK( m_plots ->connectTracks         ( tree, m_trackPartBranchName,       m_isMC ) );
  ANA_CHECK( m_plots ->connectSecondaryVerts ( tree, m_secondaryVertexBranchName, m_isMC ) );

  if ( m_isMC ) {
    ANA_CHECK( m_plots ->connectTruthJets     ( tree, m_truthJetBranchName     ) );
    ANA_CHECK( m_plots ->connectTruthDarkJets ( tree, m_truthDarkJetBranchName ) );
    ANA_CHECK( m_plots ->connectTruthParts    ( tree, m_truthPartBranchName    ) );
    ANA_CHECK( m_plots ->connectTruthVerts    ( tree, m_truthVertexBranchName  ) );
  }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsNtupleToHists :: initialize ()
{
  // everything that needs to be done after first input file
  // connected and before first event processed, e.g. create
  // additional histograms based on variables available in input files;
  // can also create all histograms + trees here, but note this method
  // doesn't get called if no events processed, so objects created
  // here won't be available in output if no input events
  
  ANA_MSG_INFO( "Initializing EJsNtupleToHists..." );

  // initialize counter
  m_eventNumber = 0;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsNtupleToHists :: execute ()
{
  // everything that needs to be done on every single event,
  // e.g. read input variables, apply cuts, fill histos + trees;
  // here is where most of actual analysis will go...

  ANA_MSG_DEBUG( "Executing EJsNtupleToHists algorithm" );

  // do any more necessary analysis ???

  TTree* tree = wk()->tree();
  //ANA_CHECK( m_plots ->execute( tree, wk()->treeEntry(), m_regionNames, m_isMC ) );
  ANA_CHECK( m_plots ->execute( tree, wk()->treeEntry(), m_regions, m_isMC ) );
  

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsNtupleToHists :: postExecute ()
{
  // everything that need to be done after main event processing;
  // mainly used in implementing NTupleSvc

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsNtupleToHists :: finalize ()
{
  // mirror image of initialize(); gets called after last event
  // processed on worker node; allows finishing up objects created
  // in initialize() before they're written to disk; only gets
  // called on worker nodes that processed input events

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode EJsNtupleToHists :: histFinalize ()
{
  // mirror image of histInitialize(); gets called after last event
  // processed on worker node; allows finishing up objects created in
  // histInitialize() before they're written to disk; gets called on
  // all worker nodes regardless of whether they processed input events

  ANA_CHECK( xAH::Algorithm::algFinalize() );

  // clean up memory
  if ( m_plots ) delete m_plots;

  return EL::StatusCode::SUCCESS;
}
