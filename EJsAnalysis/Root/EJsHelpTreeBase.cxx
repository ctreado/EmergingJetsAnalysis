#include "EJsAnalysis/EJsHelpTreeBase.h"


using namespace asg::msgUserCode;


EJsHelpTreeBase :: EJsHelpTreeBase ( xAOD::TEvent* event, TTree* tree, TFile* file,
				     const float units, bool debug, xAOD::TStore* store ) :
  HelpTreeBase ( event, tree, file, units, debug, store )
{
  ANA_MSG_DEBUG( "Creating output EJs TTree" );

  m_jet_exists = new std::vector<int>;
}

EJsHelpTreeBase :: ~EJsHelpTreeBase()
{
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

void EJsHelpTreeBase::AddTruthVerts ( const std::string truthVtxName )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddTruthVerts()", "Adding truth vertex variables" );
  
  m_truthVerts[ truthVtxName ] = new EJs::TruthVertexContainer( truthVtxName, m_units );
  EJs::TruthVertexContainer* thisTruthVtx = m_truthVerts[ truthVtxName ];
  thisTruthVtx->setBranches( m_tree );
}

void EJsHelpTreeBase::FillTruthVerts ( const xAOD::TruthVertexContainer* truthVerts,
				       const std::string truthVtxName )
{
  this->ClearTruthVerts ( truthVtxName );

  for ( const auto& truthVtx : *truthVerts )
    this->FillTruthVertex( truthVtx, truthVtxName );
}

void EJsHelpTreeBase::FillTruthVertex ( const xAOD::TruthVertex* truthVtx,
					const std::string truthVtxName )
{
  EJs::TruthVertexContainer* thisTruthVtx = m_truthVerts[ truthVtxName ];
  thisTruthVtx->FillTruthVertex( truthVtx );
}

void EJsHelpTreeBase::ClearTruthVerts ( const std::string truthVtxName )
{
  EJs::TruthVertexContainer* thisTruthVtx = m_truthVerts[ truthVtxName ];
  thisTruthVtx->clear();
}



/**********************
 * SECONDARY VERTICES *
 **********************/

void EJsHelpTreeBase :: AddSecondaryVerts ( const std::string secVtxName )
{
  if ( m_debug ) Info( "EJsHelpTreeBase::AddSecondaryVerts()", "Adding secondary vertex variables" );

  m_secVerts[ secVtxName ] = new EJs::SecondaryVertexContainer( secVtxName, m_units );
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





/*************
 * USER JETS *
 *************/

void EJsHelpTreeBase::AddJetsUser ( const std::string detailStr, const std::string jetName )
{
  if ( m_debug ) Info( "EJsHelpTree::AddJetsUser()", "Adding EJs-user jet variables" );
  
  setBranch<int>( jetName, "jetExists", m_jet_exists);
}

void EJsHelpTreeBase::FillJetsUser ( const xAOD::Jet*, const std::string jetName )
{
  m_jet_exists->push_back(1);
}

void EJsHelpTreeBase::ClearJetsUser ( const std::string jetName )
{
  m_jet_exists->clear();
}



/************************
 * USER TRUTH PARTICLES *
 ************************/



/***************
 * USER TRACKS *
 ***************/



