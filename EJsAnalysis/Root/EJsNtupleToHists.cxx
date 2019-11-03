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

  // get input file name
  TFile* inFile = wk()->inputFile();
  std::string inFileName = inFile->GetName();

  // get total number of initial events
  TH1F* metadata_cutflow = (TH1F*) inFile->Get( "MetaData_EventCount" );
  //m_nTotalEvents = metadata_cutflow->GetBinContent(3); // sumOfWeights (numberOfEvents = bin-1)
  m_nTotalEvents = 6000; // SWAP W/ ABOVE AFTER RE-RUNNING SAMPLES W/ METADATA SAVED TO DATA-TREE
  ANA_MSG_INFO( "Found initial number of events: " << m_nTotalEvents );
  
  // set m_isMC
  m_isMC = false;
  if ( ( inFileName.find("mc16") != std::string::npos ) || ( inFileName.find("data1") == std::string::npos ) )
    m_isMC = true;

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

  if ( m_jetHistoName      .empty() ) m_jetHistoName      = m_jetBranchName;
  if ( m_otherJetHistoName .empty() ) m_otherJetHistoName = m_otherJetBranchName;
  
  if ( m_truthLevelOnly )
    m_jetStr = "Truth";
  if ( m_jetBranchName.find("PFlow")  != std::string::npos || m_jetBranchName.find("pflow")  != std::string::npos )
    m_jetStr = "PFlow";
  if ( m_jetBranchName.find("EMTopo") != std::string::npos || m_jetBranchName.find("emtopo") != std::string::npos )
    m_jetStr = "EMTopo";
  
  // declare histogram manager class + add histograms to ouput
  m_plots = new EJsHistogramManager ( m_name, m_detailStr, m_jetStr, m_nTotalEvents, m_debug, m_isMC, m_unblind );
  ANA_CHECK( m_plots ->initialize( outFileName, m_regionNames, m_jetHistoName ) );
  m_plots->record( wk() );

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
  TFile* inFile = wk()->inputFile();
  std::string inFileName = inFile->GetName();

  // set m_isMC
  m_isMC = false;
  if ( ( inFileName.find("mc16") != std::string::npos ) || ( inFileName.find("data1") == std::string::npos ) )
    m_isMC = true;

  // connect tree branches
  TTree* tree = wk()->tree();
  tree->SetBranchStatus( "*", 0 ); // disable all branches

  if ( m_doEventInfo )
    ANA_CHECK   ( m_plots ->connectEvents         ( tree                              ) );
  if ( !m_truthLevelOnly ) {
    if ( m_doTriggers )
      ANA_CHECK ( m_plots ->connectTriggers       ( tree                              ) );
    if ( m_doJets )
      ANA_CHECK ( m_plots ->connectJets           ( tree, m_jetBranchName             ) );
    if ( m_doOtherJets )
      ANA_CHECK ( m_plots ->connectOtherJets      ( tree, m_otherJetBranchName        ) );
    if ( m_doTrigJets )
      ANA_CHECK ( m_plots ->connectTrigJets       ( tree, m_trigJetBranchName         ) );
    if ( m_doTracks )
      ANA_CHECK ( m_plots ->connectTracks         ( tree, m_trackPartBranchName       ) );
    if ( m_doSecondaryVertices )
      ANA_CHECK ( m_plots ->connectSecondaryVerts ( tree, m_secondaryVertexBranchName ) );
  }
  if ( m_isMC ) {
    if ( m_doTruthJets )
      ANA_CHECK ( m_plots ->connectTruthJets      ( tree, m_truthJetBranchName        ) );
    if ( m_doTruthDarkJets )
      ANA_CHECK ( m_plots ->connectTruthDarkJets  ( tree, m_truthDarkJetBranchName    ) );
    if ( m_doTruthParts )
      ANA_CHECK ( m_plots ->connectTruthParts     ( tree, m_truthPartBranchName       ) );
    if ( m_doTruthVertices )
      ANA_CHECK ( m_plots ->connectTruthVerts     ( tree, m_truthVertexBranchName     ) );
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

  TTree* tree = wk()->tree();
  ANA_CHECK( m_plots ->execute( tree, wk()->treeEntry(), m_regions ) );

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

  ANA_CHECK( m_plots ->finalize() );

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
