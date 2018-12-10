#ifndef EJsAnalysis_SecondaryVertexContainer_H
#define EJsAnalysis_SecondaryVertexContainer_H

#include <vector>
#include <string>

#include <TTree.h>

#include <xAODTracking/Vertex.h>

#include "EJsAnalysis/VertexContainer.h"

namespace EJs {

  class SecondaryVertexContainer : public VertexContainer
  {
  public:
    SecondaryVertexContainer ( const std::string& name = "secVtx", float units = 1e3 );
    virtual ~SecondaryVertexContainer ();

    virtual void setTree             ( TTree* tree );
    virtual void setBranches         ( TTree* tree );
    virtual void clear               ( );
    virtual void FillSecondaryVertex ( const xAOD::Vertex* secVtx );


  private:
    // vector branches
  };
}

#endif // EJsAnalysis_SecondaryVertexContainer_H
