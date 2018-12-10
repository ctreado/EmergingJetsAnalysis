#include <xAODTruth/TruthVertex.h>
#include <xAODTruth/TruthParticle.h>

#include "EJsAnalysis/TruthVertexContainer.h"
#include "EJsAnalysis/AlgConsts.h"

using namespace EJs;

TruthVertexContainer :: TruthVertexContainer ( const std::string& name, float units ) :
  VertexContainer ( name, units )
{
  m_x               = new std::vector<float>;
  m_y               = new std::vector<float>;
  m_z               = new std::vector<float>;
  m_r               = new std::vector<float>;
  m_eta             = new std::vector<float>;
  m_phi             = new std::vector<float>;
  m_parent_pt       = new std::vector<float>;
  m_parent_eta      = new std::vector<float>;
  m_parent_phi      = new std::vector<float>;
  m_parent_pid      = new std::vector<int>;
  m_parent_prod_x   = new std::vector<float>;
  m_parent_prod_y   = new std::vector<float>;
  m_parent_prod_z   = new std::vector<float>;
  m_parent_prod_r   = new std::vector<float>;
  m_parent_prod_eta = new std::vector<float>;
  m_parent_prod_phi = new std::vector<float>;
  m_outP_pt         = new std::vector<std::vector<float>>;
  m_outP_eta        = new std::vector<std::vector<float>>;
  m_outP_phi        = new std::vector<std::vector<float>>;
  m_outP_pid        = new std::vector<std::vector<int>>;
}

TruthVertexContainer :: ~TruthVertexContainer ()
{
  if ( m_debug ) std::cout << "Deleting TruthVertexContainer" << std::endl;

  delete m_x;
  delete m_y;
  delete m_z;
  delete m_r;
  delete m_eta;
  delete m_phi;
  delete m_parent_pt;
  delete m_parent_eta;
  delete m_parent_phi;
  delete m_parent_pid;
  delete m_parent_prod_x;
  delete m_parent_prod_y;
  delete m_parent_prod_z;
  delete m_parent_prod_r;
  delete m_parent_prod_eta;
  delete m_parent_prod_phi;
  delete m_outP_pt;
  delete m_outP_eta;
  delete m_outP_phi;
  delete m_outP_pid;
}

void TruthVertexContainer :: setTree ( TTree* tree )
{
  VertexContainer::setTree ( tree );

  connectBranch<float>              ( tree, "x",               &m_x );
  connectBranch<float>              ( tree, "y",               &m_y );
  connectBranch<float>              ( tree, "z",               &m_z );
  connectBranch<float>              ( tree, "r",               &m_r );
  connectBranch<float>              ( tree, "eta",             &m_eta );
  connectBranch<float>              ( tree, "phi",             &m_phi );
  connectBranch<float>              ( tree, "parent_pt",       &m_parent_pt );
  connectBranch<float>              ( tree, "parent_eta",      &m_parent_eta );
  connectBranch<float>              ( tree, "parent_phi",      &m_parent_phi );
  connectBranch<int>                ( tree, "parent_pid",      &m_parent_pid );
  connectBranch<float>              ( tree, "parent_prod_x",   &m_parent_prod_x );
  connectBranch<float>              ( tree, "parent_prod_y",   &m_parent_prod_y );
  connectBranch<float>              ( tree, "parent_prod_z",   &m_parent_prod_z );
  connectBranch<float>              ( tree, "parent_prod_r",   &m_parent_prod_r );
  connectBranch<float>              ( tree, "parent_prod_eta", &m_parent_prod_eta );
  connectBranch<float>              ( tree, "parent_prod_phi", &m_parent_prod_phi );
  connectBranch<std::vector<float>> ( tree, "outP_pt",         &m_outP_pt );
  connectBranch<std::vector<float>> ( tree, "outP_eta",        &m_outP_eta );
  connectBranch<std::vector<float>> ( tree, "outP_phi",        &m_outP_phi );
  connectBranch<std::vector<int>>   ( tree, "outP_pid",        &m_outP_pid );
}

// updateVertex

void TruthVertexContainer :: setBranches ( TTree* tree )
{
  VertexContainer::setBranches ( tree );

  setBranch<float>              ( tree, "x",               m_x );
  setBranch<float>              ( tree, "y",               m_y );
  setBranch<float>              ( tree, "z",               m_z );
  setBranch<float>              ( tree, "r",               m_r );
  setBranch<float>              ( tree, "eta",             m_eta );
  setBranch<float>              ( tree, "phi",             m_phi );
  setBranch<float>              ( tree, "parent_pt",       m_parent_pt );
  setBranch<float>              ( tree, "parent_eta",      m_parent_eta );
  setBranch<float>              ( tree, "parent_phi",      m_parent_phi );
  setBranch<int>                ( tree, "parent_pid",      m_parent_pid );
  setBranch<float>              ( tree, "parent_prod_x",   m_parent_prod_x );
  setBranch<float>              ( tree, "parent_prod_y",   m_parent_prod_y );
  setBranch<float>              ( tree, "parent_prod_z",   m_parent_prod_z );
  setBranch<float>              ( tree, "parent_prod_r",   m_parent_prod_r );
  setBranch<float>              ( tree, "parent_prod_eta", m_parent_prod_eta );
  setBranch<float>              ( tree, "parent_prod_phi", m_parent_prod_phi );
  setBranch<std::vector<float>> ( tree, "outP_pt",         m_outP_pt );
  setBranch<std::vector<float>> ( tree, "outP_eta",        m_outP_eta );
  setBranch<std::vector<float>> ( tree, "outP_phi",        m_outP_phi );
  setBranch<std::vector<int>>   ( tree, "outP_pid",        m_outP_pid );
}

void TruthVertexContainer :: clear ()
{
  VertexContainer::clear ();

  m_x               ->clear();
  m_y               ->clear();
  m_z               ->clear();
  m_r               ->clear();
  m_eta             ->clear();
  m_phi             ->clear();
  m_parent_pt       ->clear();
  m_parent_eta      ->clear();
  m_parent_phi      ->clear();
  m_parent_pid      ->clear();
  m_parent_prod_x   ->clear();
  m_parent_prod_y   ->clear();
  m_parent_prod_z   ->clear();
  m_parent_prod_r   ->clear();
  m_parent_prod_eta ->clear();
  m_parent_prod_phi ->clear();
  m_outP_pt         ->clear();
  m_outP_eta        ->clear();
  m_outP_phi        ->clear();
  m_outP_pid        ->clear();
}

void TruthVertexContainer :: FillTruthVertex ( const xAOD::TruthVertex* truthVtx )
{
  VertexContainer::FillVertex ();

  m_x   ->push_back( truthVtx->x() );
  m_y   ->push_back( truthVtx->y() );
  m_z   ->push_back( truthVtx->z() );
  m_r   ->push_back( truthVtx->perp() );
  m_eta ->push_back( truthVtx->eta() );
  m_phi ->push_back( truthVtx->phi() );

  const auto* parent = truthVtx->incomingParticle(0);
  if ( parent ) {
    m_parent_pt  ->push_back( parent->pt() / m_units );
    m_parent_eta ->push_back( parent->eta() );
    m_parent_phi ->push_back( parent->phi() );
    m_parent_pid ->push_back( parent->pdgId() );

    const auto* prodVtx = parent->prodVtx();
    m_parent_prod_x   ->push_back( prodVtx ? prodVtx->x()    : AlgConsts::invalidFloat );
    m_parent_prod_y   ->push_back( prodVtx ? prodVtx->y()    : AlgConsts::invalidFloat );
    m_parent_prod_z   ->push_back( prodVtx ? prodVtx->z()    : AlgConsts::invalidFloat );
    m_parent_prod_r   ->push_back( prodVtx ? prodVtx->perp() : AlgConsts::invalidFloat );
    m_parent_prod_eta ->push_back( prodVtx ? prodVtx->eta()  : AlgConsts::invalidFloat );
    m_parent_prod_phi ->push_back( prodVtx ? prodVtx->phi()  : AlgConsts::invalidFloat );
  }
  else {
    m_parent_pt       ->push_back( AlgConsts::invalidFloat );
    m_parent_eta      ->push_back( AlgConsts::invalidFloat );
    m_parent_phi      ->push_back( AlgConsts::invalidFloat );
    m_parent_pid      ->push_back( AlgConsts::invalidInt   );
    m_parent_prod_x   ->push_back( AlgConsts::invalidFloat );
    m_parent_prod_y   ->push_back( AlgConsts::invalidFloat );
    m_parent_prod_z   ->push_back( AlgConsts::invalidFloat );
    m_parent_prod_r   ->push_back( AlgConsts::invalidFloat );
    m_parent_prod_eta ->push_back( AlgConsts::invalidFloat );
    m_parent_prod_phi ->push_back( AlgConsts::invalidFloat );
  }

  std::vector<float> outP_pt;
  std::vector<float> outP_eta;
  std::vector<float> outP_phi;
  std::vector<int>   outP_pid;
  for ( size_t i = 0; i != truthVtx->nOutgoingParticles(); ++i ) {
    const auto* outP = truthVtx->outgoingParticle(i);
    if ( !outP )           continue;
    if ( !outP->charge() ) continue;
    outP_pt     .push_back( outP->pt() / m_units );
    outP_eta    .push_back( outP->eta() );
    outP_phi    .push_back( outP->phi() );
    outP_pid    .push_back( outP->pdgId() );
    if ( outP->charge() == 0 ) std::cout << "NEUTRAL PARTICLE PASSED" << std::endl;
  }
  m_outP_pt  ->push_back( outP_pt );
  m_outP_eta ->push_back( outP_eta );
  m_outP_phi ->push_back( outP_phi );
  m_outP_pid ->push_back( outP_pid );

}
