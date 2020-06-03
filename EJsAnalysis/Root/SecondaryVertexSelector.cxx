#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

#include <AthContainers/ConstDataVector.h>

#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>

#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/SecondaryVertexSelector.h"
#include "EJsAnalysis/EJsHelperFunctions.h"

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

  // check for input secondary vertex container
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
    m_secVtx_cutflowHist = new TH1D( "cutflow_secVerts", "cutflow_secVerts", 1, 1, 2 );
    m_secVtx_cutflowHist ->SetCanExtend( TH1::kAllAxes);
    
    m_secVtx_cutflow_all      = m_secVtx_cutflowHist->GetXaxis()->FindBin( "all"              );
    m_secVtx_cutflow_cleanTrk = m_secVtx_cutflowHist->GetXaxis()->FindBin( "cleanTrk_cut"     );
    m_secVtx_cutflow_filtTrk  = m_secVtx_cutflowHist->GetXaxis()->FindBin( "filtTrk_cut"      );
    m_secVtx_cutflow_matVeto  = m_secVtx_cutflowHist->GetXaxis()->FindBin( "matMapVeto_cut"   );
    m_secVtx_cutflow_rmin     = m_secVtx_cutflowHist->GetXaxis()->FindBin( "r_min_cut"        );
    m_secVtx_cutflow_rmax     = m_secVtx_cutflowHist->GetXaxis()->FindBin( "r_max_cut"        );
    m_secVtx_cutflow_zmin     = m_secVtx_cutflowHist->GetXaxis()->FindBin( "z_min_cut"        );
    m_secVtx_cutflow_zmax     = m_secVtx_cutflowHist->GetXaxis()->FindBin( "z_max_cut"        );
    m_secVtx_cutflow_ntrkmin  = m_secVtx_cutflowHist->GetXaxis()->FindBin( "nTrk_min_cut"     );
    m_secVtx_cutflow_ntrkmax  = m_secVtx_cutflowHist->GetXaxis()->FindBin( "nTrk_max_cut"     );
    m_secVtx_cutflow_chi2min  = m_secVtx_cutflowHist->GetXaxis()->FindBin( "chi2_min_cut"     );
    m_secVtx_cutflow_chi2max  = m_secVtx_cutflowHist->GetXaxis()->FindBin( "chi2_max_cut"     );
    m_secVtx_cutflow_massmin  = m_secVtx_cutflowHist->GetXaxis()->FindBin( "mass_min_cut"     );
    m_secVtx_cutflow_massmax  = m_secVtx_cutflowHist->GetXaxis()->FindBin( "mass_max_cut"     );
    m_secVtx_cutflow_distmin  = m_secVtx_cutflowHist->GetXaxis()->FindBin( "distToPV_min_cut" );
    m_secVtx_cutflow_distmax  = m_secVtx_cutflowHist->GetXaxis()->FindBin( "distToPV_max_cut" );
  }

  // initialize counters
  m_eventNumber         = 0;
  m_numPassEvents       = 0;
  m_numPassWeightEvents = 0;

  // configure VsiBonsai tool
  if ( !m_doChi2Filter       )
    m_trkChi2Cut = AlgConsts::maxValue;
  if ( !m_doHitPatternFilter )
    m_hitPatternCond = VsiTool::HitPatternCondition::NONE;
  if ( !m_doIpWrtSVFilter    ) {
    m_d0_wrtSVCut       = AlgConsts::invalidFloat;
    m_z0_wrtSVCut       = AlgConsts::invalidFloat;
    m_errd0_wrtSVCut    = AlgConsts::invalidFloat;
    m_errz0_wrtSVCut    = AlgConsts::invalidFloat;
    m_d0signif_wrtSVCut = AlgConsts::invalidFloat;
    m_z0signif_wrtSVCut = AlgConsts::invalidFloat;
    m_chi2_toSVCut      = AlgConsts::invalidFloat;
  }
  VsiBonsai::setDefaultConfig( m_bonsaiCfg );				
  m_bonsaiCfg[ VsiBonsai::Config::trackChi2Cut        ] = m_trkChi2Cut;
  m_bonsaiCfg[ VsiBonsai::Config::hitPatternCondition ] = m_hitPatternCond;
  m_bonsaiCfg[ VsiBonsai::Config::d0_wrtSVCut         ] = m_d0_wrtSVCut;
  m_bonsaiCfg[ VsiBonsai::Config::z0_wrtSVCut         ] = m_z0_wrtSVCut;
  m_bonsaiCfg[ VsiBonsai::Config::errd0_wrtSVCut      ] = m_errd0_wrtSVCut;
  m_bonsaiCfg[ VsiBonsai::Config::errz0_wrtSVCut      ] = m_errz0_wrtSVCut;
  m_bonsaiCfg[ VsiBonsai::Config::d0signif_wrtSVCut   ] = m_d0signif_wrtSVCut;
  m_bonsaiCfg[ VsiBonsai::Config::z0signif_wrtSVCut   ] = m_z0signif_wrtSVCut;
  m_bonsaiCfg[ VsiBonsai::Config::chi2_toSVCut        ] = m_chi2_toSVCut;
  m_bonsaiCfg[ VsiBonsai::Config::dropAssociated      ] = m_doDropAssociated;
  m_bonsaiCfg[ VsiBonsai::Config::dropNonSelected     ] = m_doDropNonSelected;
  m_bonsaiCfg[ VsiBonsai::Config::cleanAssociatedD0   ] = m_doCleanAssociatedD0;

  // initialize material map(s)
  TFile* m_matMapInnerFile = new TFile( PathResolverFindCalibFile( m_matMapInnerFileName ).c_str(), "READ" );
  if ( m_matMapInnerFile->IsOpen() ) {
    m_matMapInnerFile->GetObject( m_matMapInnerHistName.c_str(),   m_materialMap_Inner  );
    m_matMapInnerFile->GetObject( m_matMapInnerMatrixName.c_str(), m_materialMap_Matrix );
    if ( m_materialMap_Inner ) {
      ANA_MSG_INFO( "Inner material map open!" );
      m_materialMap_Inner->SetDirectory(0);
    }
  }
  m_matMapInnerFile->Close();
  delete m_matMapInnerFile;

  TFile* m_matMapOuterFile = new TFile( PathResolverFindCalibFile( m_matMapOuterFileName ).c_str(), "READ" );
  if ( m_matMapOuterFile->IsOpen() ) {
    m_matMapOuterFile->GetObject( m_matMapOuterHistName.c_str(), m_materialMap_Outer );
    if ( m_materialMap_Outer ) {
      ANA_MSG_INFO( "Outer material map open!" );
      m_materialMap_Outer->SetDirectory(0);
    }
  }
  m_matMapOuterFile->Close();
  delete m_matMapOuterFile;

  ANA_MSG_DEBUG( "SecondaryVertexSelector Interface successfully initialized!" );

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SecondaryVertexSelector :: execute ()
{
  // everything that needs to be done on every single event,
  // e.g. read input variables, apply cuts, fill histos + trees;
  // here is where most of actual analysis will go...

  ANA_MSG_DEBUG( "Applying Secondary Vertex Selection..." );

  // retrieve event info container
  const xAOD::EventInfo* eventInfo = 0;
  ANA_CHECK( HelperFunctions::retrieve( eventInfo, "EventInfo", m_event, m_store, msg() ) );

  // get MC event weight
  m_mcEventWeight = 1.0;
  if ( eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) )
    m_mcEventWeight = eventInfo->mcEventWeight();

  // get primary vertex
  const xAOD::VertexContainer* vertices = 0;
  ANA_CHECK( HelperFunctions::retrieve( vertices, m_vertexContainerName, m_event, m_store, msg() ) );
  const xAOD::Vertex* primaryVertex = HelperFunctions::getPrimaryVertex( vertices, msg() );

  // get secondary vertex collection from TEvent or TStore
  const xAOD::VertexContainer* inSecVerts = 0;
  ANA_CHECK( HelperFunctions::retrieve( inSecVerts, m_inContainerName, m_event, m_store, msg() ) );

  // create output container (if requested)
  ConstDataVector<xAOD::VertexContainer>* selectedSecVerts = 0;
  if ( m_createSelectedContainer )
    selectedSecVerts = new ConstDataVector<xAOD::VertexContainer>(SG::VIEW_ELEMENTS);

  int nObj  = 0;
  int nPass = 0;
  
  // loop over secondary vertices
  for ( const auto& vtx : *inSecVerts ) {
    
    // make sure all vertices decorated in case only processing subset
    if ( m_decorateSelectedObjects ) {
      vtx->auxdecor<char>( m_decor ) = -1;
      for ( size_t i = 0; i != vtx->nTrackParticles(); ++i ) {
	const auto* trk = vtx->trackParticle(i);
	trk->auxdecor<char>( "isFiltered" ) = -1;
      }
      vtx->auxdecor<char>( "passMaterialVeto" ) = -1;
      vtx->auxdecor<float>( "distToPV" ) = AlgConsts::invalidFloat;
    }
    if ( m_nToProcess > 0 && nObj >= m_nToProcess ) continue;

    ++nObj;

    // do vertex selections
    int passSel = this->PassCuts( vtx, primaryVertex );
    if ( m_decorateSelectedObjects ) vtx->auxdecor<char>( m_decor ) = passSel;

    if ( !passSel ) continue;

    ++nPass;
    
    // copy selected vertex to ouput container (if requested)
    if ( m_createSelectedContainer ) selectedSecVerts->push_back( vtx );
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
    ANA_CHECK( m_store->record( selectedSecVerts, m_outContainerName ) );

  ++m_numPassEvents;
  m_numPassWeightEvents += m_mcEventWeight;

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

  if ( m_useCutFlow ) {
    ANA_MSG_DEBUG( "Filling cutflows + writing to output" );
    m_cutflowHist  ->SetBinContent( m_cutflow_bin, m_numPassEvents       );
    m_cutflowHistW ->SetBinContent( m_cutflow_bin, m_numPassWeightEvents );

    // write new object cutflow to output file
    TFile *file = wk()->getOutputFile( "cutflow" );
    file->cd();
    m_secVtx_cutflowHist ->LabelsDeflate("X");
    m_secVtx_cutflowHist ->Write();
  }

  delete m_secVtx_cutflowHist;
  
  delete m_materialMap_Inner;
  delete m_materialMap_Outer;
  delete m_materialMap_Matrix;

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



int SecondaryVertexSelector :: PassCuts ( const xAOD::Vertex* vtx, const xAOD::Vertex* pv )
{
  // here's where we do the cuts --> if vertex fails cuts, return 0

  // fill cutflow bin 'all' before any cut
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_all, 1 );

  // decorate vertices w/ distance to primary vertex
  auto dv_pos = vtx ->position();
  auto pv_pos = pv  ->position();
  float dv_pv_dist = ( pv_pos - dv_pos ).perp();
  if ( m_decorateSelectedObjects ) vtx->auxdecor<float>( "distToPV" ) = dv_pv_dist;
  
  // set vector of trimmers to apply
  std::vector<VsiBonsai::Trimmer> trimmers = {
    VsiBonsai::chi2Filter,
    VsiBonsai::hitPatternFilter,
    VsiBonsai::ipWrtSVFilter,
    VsiBonsai::dropAssociated,
    VsiBonsai::dropNonSelected,
    VsiBonsai::cleanAssociatedD0,
  };
  
  // filter vertex tracks using VsiBonsai config
  std::vector<const xAOD::TrackParticle*> filteredTracks;
  for ( size_t i = 0; i != vtx->nTrackParticles(); ++i ) {
    bool failedTrimmers = false;
    const auto* trk = vtx->trackParticle(i);
    // do track trimming
    if ( m_doTrackTrimming ) {
      for ( auto trimmer : trimmers ) {
    	if ( !trimmer( vtx, trk, pv, m_bonsaiCfg ) ) {
    	  failedTrimmers = true;
    	  break;
	}
      }
    }
    // decorate tracks w/ trimming results
    trk->auxdecor<char>( "isFiltered" ) = !failedTrimmers;
    // save filtered tracks
    if ( failedTrimmers ) continue;
    filteredTracks.push_back( trk );
  }

  // clean vertex tracks (remove bad-d0 associated tracks only, but apply no other trimming)
  std::vector<const xAOD::TrackParticle*> cleanTracks;
  for ( size_t j = 0; j != vtx->nTrackParticles(); ++j ) {
    bool failedCleaning = false;
    const auto* trk = vtx->trackParticle(j);
    // do track cleaning (independent of other trimmers)
    if ( m_doCleanAssociatedD0 )
      if ( !VsiBonsai::cleanAssociatedD0( vtx, trk, pv, m_bonsaiCfg ) )
	failedCleaning = true;
    // decorate tracks w/ cleaning results
    trk->auxdecor<char>( "isClean" ) = !failedCleaning;
    // save clean tracks
    if ( failedCleaning ) continue;
    cleanTracks.push_back( trk );
  }

  // apply clean / filtered track cuts
  if ( m_doCleanTrkCut && cleanTracks.size()    < 2 ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_cleanTrk, 1 );
  if ( m_doFiltTrkCut  && filteredTracks.size() < 2 ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_filtTrk,  1 );

  // material map veto
  if ( m_materialMap_Inner && m_materialMap_Outer && m_materialMap_Matrix ) {
    bool passMaterialVeto = false;
    
    // use inner / outer map based on vtx position
    auto pos = vtx->position();
    if ( pos.perp() > 150 )
      passMaterialVeto =
  	( m_materialMap_Outer->
	  GetBinContent( m_materialMap_Outer->
			 FindBin( pos.perp(), pos.phi(), pos.z() ) ) == 0 );
    else {
      for ( int i = 0; i != 5; ++i ) {
  	if ( pos.perp() < (*m_materialMap_Matrix)[i][0] ) {
	  float test_x = pos.x() + (*m_materialMap_Matrix)[i][1];
	  float test_y = pos.y() + (*m_materialMap_Matrix)[i][2];
	  double calc_phi = fmod( TMath::ATan2( test_y, test_x ),
				  TMath::Pi() / (*m_materialMap_Matrix)[i][3] );
	  if ( calc_phi < 0 ) calc_phi = calc_phi + TMath::Pi() / (*m_materialMap_Matrix)[i][3];
	  passMaterialVeto =
	    ( m_materialMap_Inner->
	      GetBinContent( m_materialMap_Inner->
			     FindBin( sqrt( test_x*test_x + test_y*test_y ), calc_phi, pos.z() ) ) == 0 );
	  break;
	}
      }
    }
    // decorate vertex with material veto decision
    if ( m_decorateSelectedObjects ) vtx->auxdecor<char>( "passMaterialVeto" ) = passMaterialVeto;
    // cut on material veto
    if ( m_doMatMapVeto && !passMaterialVeto ) return 0; 
  }
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_matVeto, 1 );

  // fiducial region cuts
  if ( m_r_min != AlgConsts::maxValue )
    if ( vtx->position().perp() < m_r_min ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_rmin, 1 );

  if ( m_r_max != AlgConsts::maxValue )
    if ( vtx->position().perp() > m_r_max ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_rmax, 1 );

  if ( m_z_min != AlgConsts::maxValue )
    if ( fabs( vtx->z() ) < m_z_min ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_zmin, 1 );

  if ( m_z_max != AlgConsts::maxValue )
    if ( fabs( vtx->z() ) > m_z_max ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_zmax, 1 );

  // n-track cuts
  if ( m_ntrk_min > 0 )
    if ( filteredTracks.size() < m_ntrk_min ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_ntrkmin, 1 );

  if ( m_ntrk_max > 0 )
    if ( filteredTracks.size() > m_ntrk_max ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_ntrkmax, 1 );

  // chi-squared cuts
  if ( m_chi2_min != AlgConsts::maxValue )
    if ( vtx->chiSquared() / vtx->numberDoF() < m_chi2_min ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_chi2min, 1 );

  if ( m_chi2_max != AlgConsts::maxValue )
    if ( vtx->chiSquared() / vtx->numberDoF() > m_chi2_max ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_chi2max, 1 );

  // mass cuts
  const TLorentzVector& sumP4 = VsiBonsai::sumP4( filteredTracks );
  if ( m_mass_min != AlgConsts::maxValue )
    if ( sumP4.M() < m_mass_min ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_massmin, 1 );

  if ( m_mass_max != AlgConsts::maxValue )
    if ( sumP4.M() > m_mass_max ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_massmax, 1 );

  // distance (to pv) cuts
  if ( m_dist_min != AlgConsts::maxValue )
    if ( dv_pv_dist < m_dist_min ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_distmin, 1 );

  if ( m_dist_max != AlgConsts::maxValue )
    if ( dv_pv_dist > m_dist_max ) return 0;
  if ( m_useCutFlow ) m_secVtx_cutflowHist ->Fill( m_secVtx_cutflow_distmax, 1 );

  
  return 1;
}
