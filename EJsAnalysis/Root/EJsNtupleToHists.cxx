#include <TFile.h>
#include <TTree.h>
#include <TKey.h>

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

  // set m_isMC
  m_isMC = false;
  if ( ( inFileName.find("mc16") != std::string::npos ) || ( inFileName.find("data1") == std::string::npos ) )
    m_isMC = true;
  if ( m_truthLevelOnly )
    m_isMC = true;
  
  // get total number of initial events
  if ( inFile->GetListOfKeys()->Contains( "MetaData_EventCount" ) ) {
    TH1F* metadata_cutflow = (TH1F*) inFile->Get( "MetaData_EventCount" );
    m_nEvents_init = metadata_cutflow->GetBinContent(1);
    m_nEvents_sel  = metadata_cutflow->GetBinContent(2);
    m_sumw_init    = metadata_cutflow->GetBinContent(3); // initial number of weighted events
    m_sumw_sel     = metadata_cutflow->GetBinContent(4);
    m_sumw2_init   = metadata_cutflow->GetBinContent(5);
    m_sumw2_sel    = metadata_cutflow->GetBinContent(6);
    ANA_MSG_INFO( "Found initial number of events: " << m_sumw_init );
  }
  else
    ANA_MSG_INFO( "No MetaData_EventCount information available." );

  // get ntuple cutflows

  std::vector<TH1F*> m_ntupleCutflows;
  if ( inFile->GetListOfKeys()->Contains( "cutflow" ) ) {
    TIter nextkey ( inFile->GetListOfKeys() );
    TKey *key;
    while ( ( key = (TKey*) nextkey() ) )
      if ( strstr( key->GetName(), "cutflow" ) ) {
	TH1F* ntuple_cutflow = (TH1F*) inFile->Get( key->GetName() );
	m_ntupleCutflows .push_back( ntuple_cutflow );
      }
  }
  
  // get metadata weights from input text file for corresponding mc channel number
  if ( m_isMC ) {
    
    ANA_MSG_DEBUG( "Getting sample metadata." );
    
    // get channel number
    int mcChannelNumber = 0;
    inTree->SetBranchStatus( "*", 0 ); // disable all branches
    EJsHelper::connectBranch<int> ( inTree, "mcChannelNumber", &mcChannelNumber );
    inTree->GetEntry( wk()->treeEntry() );
    
    // get metadata file
    if ( !m_truthLevelOnly && !m_metadataFileName.empty() ) {
      const char* metadataPath = gSystem->ExpandPathName( PathResolverFindCalibFile( m_metadataFileName ).c_str() );
      std::ifstream m_metadataFile( metadataPath );
      delete [] metadataPath;

      std::string line;
      double word;
      std::vector<double> metadata;
      if ( m_metadataFile.is_open() ) {
	while ( std::getline( m_metadataFile, line ) ) {
	  std::istringstream iss( line );
	  int i = 0;
	  while ( iss >> word ) {
	    if ( i == 0 && word != mcChannelNumber ) continue;
	    metadata.push_back( word );
	    ++i;
	  }
	}
      }
      // metadata = { dataset_number, crossSection [nb], kFactor, genFiltEff }
      m_crossSection = metadata.at(1);
      m_kFactor      = metadata.at(2);
      m_genFilterEff = metadata.at(3);
    }
    else {
      m_crossSection = 1;
      m_kFactor      = 1;
      m_genFilterEff = 1;
    }
    
    ANA_MSG_INFO( "Found cross-section, k-factor, generator filter efficiency: "
		  << m_crossSection << " " << m_kFactor << " " << m_genFilterEff );
  }

  // set metadata map
  m_metadata[ "eventCount_init" ] = m_nEvents_init;
  m_metadata[ "eventCount_sel"  ] = m_nEvents_sel;
  m_metadata[ "sumw_init"       ] = m_sumw_init;
  m_metadata[ "sumw_sel"        ] = m_sumw_sel;
  m_metadata[ "sumw2_init"      ] = m_sumw2_init;
  m_metadata[ "sumw2_sel"       ] = m_sumw2_sel;
  m_metadata[ "crossSection"    ] = m_crossSection;
  m_metadata[ "kFactor"         ] = m_kFactor;
  m_metadata[ "genFilterEff"    ] = m_genFilterEff;
  
  // get list of regions to run over
  ANA_MSG_INFO( "Getting list of regions to run over." );
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

  // get base DV type
  ANA_MSG_INFO( "Setting base DV type." );
  EJsHelper::fillBaseDV( m_baseDV, m_baseDVName );

  // set jet branch and string to use for histograms
  ANA_MSG_INFO( "Setting jet branch name." );
  if ( m_jetHistoName .empty() ) m_jetHistoName = m_jetBranchName;
  if ( m_truthLevelOnly )
    m_jetStr = "Truth";
  if ( m_jetBranchName.find("PFlow")  != std::string::npos || m_jetBranchName.find("pflow")  != std::string::npos )
    m_jetStr = "PFlow";
  if ( m_jetBranchName.find("EMTopo") != std::string::npos || m_jetBranchName.find("emtopo") != std::string::npos )
    m_jetStr = "EMTopo";

  if ( m_truthLevelOnly ) m_detailStr += " truthOnly";
  // declare histogram manager class + add histograms to ouput
  m_plots = new EJsHistogramManager ( m_name, m_detailStr, m_jetStr, m_metadata, m_ntupleCutflows,
				      m_lumi, m_debug, m_isMC, m_unblind );
  ANA_CHECK( m_plots ->initialize( outFileName, m_regions, m_jetHistoName, m_baseDV ) );
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
  ANA_CHECK( m_plots ->execute( tree, wk()->treeEntry(), m_regions, m_baseDV ) );

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

  ANA_CHECK( m_plots ->finalize( m_regions ) );

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
