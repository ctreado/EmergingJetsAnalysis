#include "EJsAnalysis/SecondaryVertexContainer.h"

using namespace EJs;

SecondaryVertexContainer :: SecondaryVertexContainer ( const std::string& name, float units ) :
  VertexContainer ( name, units )
{

}

SecondaryVertexContainer :: ~SecondaryVertexContainer ()
{
  if ( m_debug ) std::cout << "Deleting SecondaryVertexContainer" << std::endl;
}

void SecondaryVertexContainer :: setTree ( TTree* tree )
{
  VertexContainer::setTree ( tree );
}

void SecondaryVertexContainer :: setBranches ( TTree* tree )
{
  VertexContainer::setBranches ( tree );
}

void SecondaryVertexContainer :: clear ()
{
  VertexContainer::clear ();
}

void SecondaryVertexContainer::FillSecondaryVertex ( const xAOD::Vertex* secVtx )
{
  VertexContainer::FillVertex ();
}
