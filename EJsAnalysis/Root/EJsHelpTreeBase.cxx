#include "EJsAnalysis/EJsHelpTreeBase.h"
#include "EJsAnalysis/AlgConsts.h"


EJsHelpTreeBase :: EJsHelpTreeBase ( xAOD::TEvent* event, TTree* tree, TFile* file,
				     const float units, bool debug, xAOD::TStore* store ) :
  HelpTreeBase ( event, tree, file, units, debug, store )
{
  if ( m_debug ) Info( "EJsHelpTreeBase()", "creating output EJs TTree" );

  m_x       = 0;
  m_y       = 0;
  m_z       = 0;
  m_r       = 0;
  m_phi     = 0;
  m_nTracks = 0;
  
  m_nSelected   = 0;
  m_nAssociated = 0;
  
  m_d0           = new std::vector<float>;
  m_errd0        = new std::vector<float>;
  m_errz0        = new std::vector<float>;
  m_chi2         = new std::vector<float>;
  m_isSelected   = new std::vector<uint8_t>;
  m_isAssociated = new std::vector<uint8_t>;
}

EJsHelpTreeBase :: ~EJsHelpTreeBase()
{
  if ( m_debug ) Info( "EJsHelpTreeBase()", "deleting" );
  
  // truth vertices
  for ( auto truthVtx : m_truthVerts )
    delete truthVtx.second;

  // secondary vertices
  for ( auto secVtx : m_secVerts )
    delete secVtx.second;
}



/******************
 * TRUTH VERTICES *
 ******************/

void EJsHelpTreeBase :: AddTruthVerts ( const std::string detailStr, const std::string truthVtxName )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddTruthVerts()", "adding truth vertex variables" );
  
  m_truthVerts[ truthVtxName ] = new EJs::TruthVertexContainer( truthVtxName, detailStr, m_units );
  EJs::TruthVertexContainer* thisTruthVtx = m_truthVerts[ truthVtxName ];
  thisTruthVtx->setBranches( m_tree );
}

void EJsHelpTreeBase :: FillTruthVerts ( const xAOD::TruthVertexContainer* truthVerts,
					 const std::string truthVtxName )
{
  this->ClearTruthVerts ( truthVtxName );

  for ( const auto& truthVtx : *truthVerts )
    this->FillTruthVertex( truthVtx, truthVtxName );
}

void EJsHelpTreeBase :: FillTruthVertex ( const xAOD::TruthVertex* truthVtx,
					  const std::string truthVtxName )
{
  EJs::TruthVertexContainer* thisTruthVtx = m_truthVerts[ truthVtxName ];
  thisTruthVtx->FillTruthVertex( truthVtx );
}

void EJsHelpTreeBase :: ClearTruthVerts ( const std::string truthVtxName )
{
  EJs::TruthVertexContainer* thisTruthVtx = m_truthVerts[ truthVtxName ];
  thisTruthVtx->clear();
}



/**********************
 * SECONDARY VERTICES *
 **********************/

void EJsHelpTreeBase :: AddSecondaryVerts ( const std::string detailStr, const std::string secVtxName )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddSecondaryVerts()", "adding secondary vertex variables" );

  m_secVerts[ secVtxName ] = new EJs::SecondaryVertexContainer( secVtxName, detailStr, m_units );
  EJs::SecondaryVertexContainer* thisSecVtx = m_secVerts[ secVtxName ];
  thisSecVtx->setBranches( m_tree );
}

void EJsHelpTreeBase :: FillSecondaryVerts ( const xAOD::VertexContainer* secVerts,
					     const std::string secVtxName )
{
  this->ClearSecondaryVerts ( secVtxName );

  for ( const auto& secVtx : *secVerts )
    this->FillSecondaryVertex( secVtx, secVtxName );
}

void EJsHelpTreeBase :: FillSecondaryVertex ( const xAOD::Vertex* secVtx,
					      const std::string secVtxName )
{
  EJs::SecondaryVertexContainer* thisSecVtx = m_secVerts[ secVtxName ];
  thisSecVtx->FillSecondaryVertex( secVtx );
}

void EJsHelpTreeBase :: ClearSecondaryVerts ( const std::string secVtxName )
{
  EJs::SecondaryVertexContainer* thisSecVtx = m_secVerts[ secVtxName ];
  thisSecVtx->clear();
}



/******************
 * PRIMARY VERTEX *
 ******************/

void EJsHelpTreeBase :: AddPV ( )
{

  if ( m_debug ) Info( "EJsHelpTreeBase::AddPV()", "adding primary vertex variables" );

  m_tree->Branch( "PV_x",       &m_x,       "PV_x/F"       );
  m_tree->Branch( "PV_y",       &m_y,       "PV_y/F"       );
  m_tree->Branch( "PV_z",       &m_z,       "PV_z/F"       );
  m_tree->Branch( "PV_r",       &m_r,       "PV_r/F"       );
  m_tree->Branch( "PV_phi",     &m_phi,     "PV_phi"       );
  m_tree->Branch( "PV_nTracks", &m_nTracks, "PV_nTracks/i" );
}

void EJsHelpTreeBase :: FillPV ( const xAOD::Vertex* pv )
{
  m_x       = pv->x();
  m_y       = pv->y();
  m_z       = pv->z();
  m_r       = pv->position().perp();
  m_phi     = pv->position().phi();
  m_nTracks = pv->nTrackParticles(); 
}

void EJsHelpTreeBase :: ClearPV ( )
{
  m_x       = 0;
  m_y       = 0;
  m_z       = 0;
  m_r       = 0;
  m_phi     = 0;
  m_nTracks = 0;
}



/*************
 * USER JETS *
 *************/

void EJsHelpTreeBase :: AddJetsUser ( const std::string detailStr, const std::string jetName )
{

}

void EJsHelpTreeBase :: FillJetsUser ( const xAOD::Jet* jet, const std::string jetName )
{

}

void EJsHelpTreeBase :: ClearJetsUser ( const std::string jetName )
{

}



/************************
 * USER TRUTH PARTICLES *
 ************************/



/***************
 * USER TRACKS *
 ***************/
void EJsHelpTreeBase :: AddTracksUser ( const std::string trackName, const std::string detailStr )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddTracksUser()", "adding EJs-user track variables" );

  setBranch<float>    ( trackName, "d0",           m_d0 );
  setBranch<float>    ( trackName, "errd0",        m_errd0 );
  setBranch<float>    ( trackName, "errz0",        m_errz0 );
  setBranch<float>    ( trackName, "chi2",         m_chi2 );
  setBranch<uint8_t>  ( trackName, "isSelected",   m_isSelected );
  setBranch<uint8_t>  ( trackName, "isAssociated", m_isAssociated );

  std::string selCounterName   = "n" + trackName + "Selected";
  std::string assocCounterName = "n" + trackName + "Associated";
  m_tree->Branch( selCounterName  .c_str(), &m_nSelected,   (selCounterName  +"/i").c_str() );
  m_tree->Branch( assocCounterName.c_str(), &m_nAssociated, (assocCounterName+"/i").c_str() );

}

void EJsHelpTreeBase :: FillTracksUser ( const std::string trackName,
					 const xAOD::TrackParticle* track )
{
  bool is_selected = false;
  if ( track->isAvailable<char>("is_selected") ) {
    if ( track->auxdataConst<char>("is_selected") ) {
      is_selected = true;
      m_nSelected++;
    }
  }
  bool is_associated = false;
  if ( track->isAvailable<char>("is_associated") ) {
    if ( track->auxdataConst<char>("is_associated") ) {
      is_associated = true;
      m_nAssociated++;
    }
  }

  m_d0           ->push_back( track->d0() );
  m_errd0        ->push_back( track->definingParametersCovMatrix()(0,0) );
  m_errz0        ->push_back( track->definingParametersCovMatrix()(1,1) );
  m_chi2         ->push_back( track->chiSquared() / (track->numberDoF() + AlgConsts::infinitesimal) );
  m_isSelected   ->push_back( is_selected );
  m_isAssociated ->push_back( is_associated );
}

void EJsHelpTreeBase :: ClearTracksUser ( const std::string trackName )
{
  m_nSelected   = 0;
  m_nAssociated = 0;
  
  m_d0           ->clear();
  m_errd0        ->clear();
  m_errz0        ->clear();
  m_chi2         ->clear();
  m_isSelected   ->clear();
  m_isAssociated ->clear();
}


