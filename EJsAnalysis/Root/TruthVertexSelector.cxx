#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <AthContainers/ConstDataVector.h>

#include <xAODTruth/TruthVertexContainer.h>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/TruthVertexSelector.h"
#include "EJsAnalysis/EJsHelperFunctions.h"

// needed to distribute algorithm to workers
ClassImp ( TruthVertexSelector )



TruthVertexSelector :: TruthVertexSelector () : Algorithm ( "TruthVertexSelector" )
{
  // code for base initialization of variables, e.g. initialize
  // all pointers to zero; note this method called on submission +
  // worker node, so only put most basic initialization here;
  // most initialization will go in histInitialize() and initialize()
}



EL::StatusCode TruthVertexSelector :: setupJob ( EL::Job& job )
{
  // code to set up job on submission object so it's ready to work
  // w/ alg, e.g. request D3PDReader service or add output files;
  // code here automatically activated/deactivated when alg
  // added/removed from job
  
  // initialize alg to use xAODRootAccess package
  job.useXAOD();
  xAOD::Init( "TruthVertexSelector" ).ignore(); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthVertexSelector :: histInitialize ()
{
  // everything that needs to be done at the beginning on each
  // worker node, e.g. create histos + output trees;
  // this method called before any input files connected
  
  ANA_CHECK( xAH::Algorithm::algInitialize() );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthVertexSelector :: fileExecute ()
{
  // everything that needs to be done exactly once for every
  // single file, e.g. collect list of all lumi-blocks processed

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthVertexSelector :: changeInput ( bool /*firstFile*/ )
{
  // everything that needs to be done when input files change,
  // e.g. resetting branch addresses on trees; not needed if
  // using D3PDReader or similar service...

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthVertexSelector :: initialize ()
{
  // everything that needs to be done after first input file
  // connected and before first event processed, e.g. create
  // additional histograms based on variables available in input files;
  // can also create all histograms + trees here, but note this method
  // doesn't get called if no events processed, so objects created
  // here won't be available in output if no input events

  ANA_MSG_INFO( "Initializing TruthVertexSelector..." );

  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();

  // check for input truth vertex container
  if ( m_inContainerName.empty() ) {
    ANA_MSG_ERROR( "No input container provided! Exiting." );
    return EL::StatusCode::FAILURE;
  }

  // initialize cutflows
  if ( m_useCutFlow ) {

    // retrieve file in which cutflow hists are stored
    TFile *file = wk()->getOutputFile( "cutflow" );

    // retrieve event cutflows
    m_cutflowHist  = (TH1D*)file->Get( "cutflow"          );
    m_cutflowHistW = (TH1D*)file->Get( "cutflow_weighted" );

    m_cutflow_bin = m_cutflowHist->GetXaxis()->FindBin( ( m_name ).c_str() );

    m_cutflowHist  ->GetXaxis()->FindBin( ( m_name ).c_str() );
    m_cutflowHistW ->GetXaxis()->FindBin( ( m_name ).c_str() );

    // initialize object cutflow
    m_truthVtx_cutflowHist = new TH1D( "cutflow_truthVerts", "cutflow_truthVerts", 1, 1, 2 );
    m_truthVtx_cutflowHist ->SetCanExtend( TH1::kAllAxes );

    m_truthVtx_cutflow_all         = m_truthVtx_cutflowHist->GetXaxis()->FindBin( "all"              );
    m_truthVtx_cutflow_llp         = m_truthVtx_cutflowHist->GetXaxis()->FindBin( "llp_decay_cut"    );
    m_truthVtx_cutflow_rmin        = m_truthVtx_cutflowHist->GetXaxis()->FindBin( "r_min_cut"        );
    m_truthVtx_cutflow_rmax        = m_truthVtx_cutflowHist->GetXaxis()->FindBin( "r_max_cut"        );
    m_truthVtx_cutflow_zmin        = m_truthVtx_cutflowHist->GetXaxis()->FindBin( "z_min_cut"        );
    m_truthVtx_cutflow_zmax        = m_truthVtx_cutflowHist->GetXaxis()->FindBin( "z_max_cut"        );
    m_truthVtx_cutflow_nVisOutPmin = m_truthVtx_cutflowHist->GetXaxis()->FindBin( "nVisOutP_min_cut" );
    m_truthVtx_cutflow_nVisOutPmax = m_truthVtx_cutflowHist->GetXaxis()->FindBin( "nVisOutP_max_cut" );
    m_truthVtx_cutflow_massmin     = m_truthVtx_cutflowHist->GetXaxis()->FindBin( "mass_min_cut"     );
    m_truthVtx_cutflow_massmax     = m_truthVtx_cutflowHist->GetXaxis()->FindBin( "mass_max_cut"     );
  }

  // initialize counters
  m_eventNumber         = 0;
  m_numPassEvents       = 0;
  m_numPassWeightEvents = 0;

  // to handle more than one type of llp decay vertex
  std::string token;
  std::istringstream ss_llp_decays( m_truthLLP );
  while ( std::getline( ss_llp_decays, token, ' ' ) )
    m_truthLLP_decays.push_back( token );

  ANA_MSG_DEBUG( "TruthVertexSelector Interface successfully initialized!" );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthVertexSelector :: execute ()
{
  // everything that needs to be done on every single event,
  // e.g. read input variables, apply cuts, fill histos + trees;
  // here is where most of actual analysis will go...

  ANA_MSG_DEBUG( "Applying Truth Vertex Selection..." );

  // retrieve event info container
  const xAOD::EventInfo* eventInfo = 0;
  ANA_CHECK( HelperFunctions::retrieve( eventInfo, "EventInfo", m_event, m_store, msg() ) );

  // get MC event weight
  m_mcEventWeight = 1.0;
  if ( eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) )
    m_mcEventWeight = eventInfo->mcEventWeight();

  // get truth vertex collection from TEvent or TStore
  const xAOD::TruthVertexContainer* inTruthVerts = 0;
    ANA_CHECK( HelperFunctions::retrieve( inTruthVerts, m_inContainerName, m_event, m_store, msg() ) );

  // create output container (if requested)
  ConstDataVector<xAOD::TruthVertexContainer>* selectedTruthVerts = 0;
  if ( m_createSelectedContainer )
    selectedTruthVerts = new ConstDataVector<xAOD::TruthVertexContainer>(SG::VIEW_ELEMENTS);

  int nObj  = 0;
  int nPass = 0;

  // loop over truth vertices
  for ( const auto& tv : *inTruthVerts ) {

    // make sure all vertices decorated in case only processing subset
    if ( m_decorateSelectedObjects )
      tv->auxdecor<char>( m_decor ) = -1;
    if ( m_nToProcess > 0 && nObj >= m_nToProcess ) continue;

    ++nObj;

    // do truth vertex selections
    int passSel = this->PassCuts( tv );
    if ( m_decorateSelectedObjects ) tv->auxdecor<char>( m_decor ) = passSel;

    if ( !passSel ) continue;

    ++nPass;

    // copy selected truth vertex to output container (if requested)
    if ( m_createSelectedContainer ) selectedTruthVerts->push_back( tv );
  }

  ++m_eventNumber;

  // apply event selection based on min/max requirements on number of objects passing cuts per event
  if ( m_pass_min > 0 && nPass < m_pass_min ) {
    wk()->skipEvent();
    return EL::StatusCode::SUCCESS;
  }
  if ( m_pass_max > 0 && nPass > m_pass_max ) {
    wk()->skipEvent();
    return EL::StatusCode::SUCCESS;
  }

  // add output container to TStore
  if ( m_createSelectedContainer )
    ANA_CHECK( m_store->record( selectedTruthVerts, m_outContainerName ) );

  ++m_numPassEvents;
  m_numPassWeightEvents += m_mcEventWeight;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthVertexSelector :: postExecute ()
{
  // everything that need to be done after main event processing;
  // mainly used in implementing NTupleSvc

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthVertexSelector :: finalize ()
{
  // mirror image of initialize(); gets called after last event
  // processed on worker node; allows finishing up objects created
  // in initialize() before they're written to disk; only gets
  // called on worker nodes that processed input events

  if ( m_useCutFlow ) {
    ANA_MSG_DEBUG( "Filling cutflows + writing to output" );
    m_cutflowHist  ->SetBinContent( m_cutflow_bin, m_numPassEvents       );
    m_cutflowHistW ->SetBinContent( m_cutflow_bin, m_numPassWeightEvents );

    // write new object cutflow to output file
    TFile *file = wk()->getOutputFile( "cutflow" );
    file->cd();
    m_truthVtx_cutflowHist ->LabelsDeflate("X");
    m_truthVtx_cutflowHist ->Write();
  }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthVertexSelector :: histFinalize ()
{
  // mirror image of histInitialize(); gets called after last event
  // processed on worker node; allows finishing up objects created in
  // histInitialize() before they're written to disk; gets called on
  // all worker nodes regardless of whether they processed input events

  ANA_CHECK( xAH::Algorithm::algFinalize() );

  return EL::StatusCode::SUCCESS;
}



int TruthVertexSelector :: PassCuts ( const xAOD::TruthVertex* tv )
{
  // here's where we do the cuts --> if truth vertex fails cuts, return 0

  // fill cutflow bin 'all' before any cut
  if ( m_useCutFlow ) m_truthVtx_cutflowHist ->Fill( m_truthVtx_cutflow_all, 1 );

  // select LLP decay(s) of interest
  if ( !m_truthLLP_decays.empty() ) {
    bool isLLP = false;
    for ( size_t i = 0; i != m_truthLLP_decays.size(); ++i )
      if ( EJsHelper::pdgIdFuncs[m_truthLLP_decays.at(i)]( tv ) ) isLLP = true;
    if ( !isLLP ) return 0;
  }
  if ( m_useCutFlow ) m_truthVtx_cutflowHist ->Fill( m_truthVtx_cutflow_llp, 1 );

  // fiducial region cuts
  if ( m_r_min != AlgConsts::maxValue )
    if ( tv->perp() < m_r_min ) return 0;
  if ( m_useCutFlow ) m_truthVtx_cutflowHist ->Fill( m_truthVtx_cutflow_rmin, 1 );

  if ( m_r_max != AlgConsts::maxValue )
    if ( tv->perp() > m_r_max ) return 0;
  if ( m_useCutFlow ) m_truthVtx_cutflowHist ->Fill( m_truthVtx_cutflow_rmax, 1 );

  if ( m_z_min != AlgConsts::maxValue )
    if ( fabs( tv->z() ) < m_z_min ) return 0;
  if ( m_useCutFlow ) m_truthVtx_cutflowHist ->Fill( m_truthVtx_cutflow_zmin, 1 );

  if ( m_z_max != AlgConsts::maxValue )
    if ( fabs( tv->z() ) > m_z_max ) return 0;
  if ( m_useCutFlow ) m_truthVtx_cutflowHist ->Fill( m_truthVtx_cutflow_zmax, 1 );

  // n-visible-outgoing-particle cuts
  std::vector<const xAOD::TruthParticle*> outParts;
  int n_visOutParts = 0;
  for ( size_t i = 0; i != tv->nOutgoingParticles(); ++i ) {
    const auto* outP = tv->outgoingParticle(i);
    if ( !outP ) continue;
    outParts .push_back( outP );
    if ( !outP->charge() || outP->pt() < m_outP_ptThresh ) continue;
    ++n_visOutParts;
  }
  if ( m_nVisOutP_min > 0 )
    if ( n_visOutParts < m_nVisOutP_min ) return 0;
  if ( m_useCutFlow ) m_truthVtx_cutflowHist ->Fill( m_truthVtx_cutflow_nVisOutPmin, 1 );

  if ( m_nVisOutP_max > 0 )
    if ( n_visOutParts > m_nVisOutP_max ) return 0;
  if ( m_useCutFlow ) m_truthVtx_cutflowHist ->Fill( m_truthVtx_cutflow_nVisOutPmax, 1 );

  // mass cuts
  const TLorentzVector& sumP4 = EJsHelper::truthSumP4 ( outParts );
  if ( m_mass_min != AlgConsts::maxValue )
    if ( sumP4.M() < m_mass_min ) return 0;
  if ( m_useCutFlow ) m_truthVtx_cutflowHist ->Fill( m_truthVtx_cutflow_massmin, 1 );

  if ( m_mass_max != AlgConsts::maxValue )
    if ( sumP4.M() > m_mass_max ) return 0;
  if ( m_useCutFlow ) m_truthVtx_cutflowHist ->Fill( m_truthVtx_cutflow_massmax, 1 );
  

  return 1;
}
