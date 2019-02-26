#include "EJsAnalysis/JetContainer.h"

using namespace EJs;

JetContainer :: JetContainer ( const std::string& name, const std::string& detailStr, float units, bool mc ) :
  xAH::JetContainer ( name, detailStr, units, mc )
{
  if ( m_debug ) Info( "EJs::JetContainer()", "setting up" );

  m_ID     = new std::vector<int>;
  m_radius = new std::vector<float>;

  m_constit_E   = new std::vector<std::vector<float>>;
  m_constit_pt  = new std::vector<std::vector<float>>;
  m_constit_eta = new std::vector<std::vector<float>>;
  m_constit_phi = new std::vector<std::vector<float>>;
}


JetContainer :: ~JetContainer ()
{
  if ( m_debug ) Info( "EJs::JetContainer()", "deleting" );

  delete m_ID;
  delete m_radius;

  delete m_constit_E;
  delete m_constit_pt;
  delete m_constit_eta;
  delete m_constit_phi;
}


void JetContainer :: setTree ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::JetContainer::setTree()", "setting tree" );

  connectBranch<int>   ( tree, "ID",     &m_ID     );
  connectBranch<float> ( tree, "radius", &m_radius );

  connectBranch<std::vector<float>> ( tree, "constit_E",   &m_constit_E );
  connectBranch<std::vector<float>> ( tree, "constit_pt",  &m_constit_pt );
  connectBranch<std::vector<float>> ( tree, "constit_eta", &m_constit_eta );
  connectBranch<std::vector<float>> ( tree, "constit_phi", &m_constit_phi );
}


void JetContainer :: setBranches ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::JetContainer::setBranches()", "setting branches" );

  setBranch<int>   ( tree, "ID", m_ID );
  setBranch<float> ( tree, "radius", m_radius );

  setBranch<std::vector<float>> ( tree, "constit_E",   m_constit_E );
  setBranch<std::vector<float>> ( tree, "constit_pt",  m_constit_pt );
  setBranch<std::vector<float>> ( tree, "constit_eta", m_constit_eta );
  setBranch<std::vector<float>> ( tree, "constit_phi", m_constit_phi );
}


void JetContainer :: clear ( )
{
  if ( m_debug ) Info( "EJs::JetContainer::clear()", "clearing branches" );

  m_ID     ->clear();
  m_radius ->clear();

  m_constit_E   ->clear();
  m_constit_pt  ->clear();
  m_constit_eta ->clear();
  m_constit_phi ->clear();
}


void JetContainer :: FillJet ( const xAOD::Jet* jet )
{
  if ( m_debug ) Info( "EJs::JetContainer::FillJet()", "filling branches" );

  m_ID     ->push_back( AUXDYN( jet, int,   "ID"     ) );
  m_radius ->push_back( jet->getSizeParameter() );
    
  std::vector<float> constit_E;
  std::vector<float> constit_pt;
  std::vector<float> constit_eta;
  std::vector<float> constit_phi;
  
  // access constituents
  xAOD::JetConstituentVector jcv = jet->getConstituents();
  if ( jcv.isValid() ) {
    for ( const auto& jconstit : jcv ) {
      constit_E   .push_back( jconstit->e() / m_units );
      constit_pt  .push_back( jconstit->pt() / m_units );
      constit_eta .push_back( jconstit->eta() );
      constit_phi .push_back( jconstit->phi() );
    }
  }

  m_constit_E   ->push_back( constit_E );
  m_constit_pt  ->push_back( constit_pt );
  m_constit_eta ->push_back( constit_eta );
  m_constit_phi ->push_back( constit_phi );
}
