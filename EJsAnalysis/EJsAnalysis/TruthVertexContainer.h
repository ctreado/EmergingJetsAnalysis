#ifndef EJsAnalysis_TruthVertexContainer_H
#define EJsAnalysis_TruthVertexContainer_H

#include <vector>
#include <string>

#include <TTree.h>

#include <xAODTruth/TruthVertex.h>

#include "EJsAnalysis/VertexContainer.h"

namespace EJs {

  class TruthVertexContainer : public VertexContainer
  {
  public:
    TruthVertexContainer ( const std::string& name = "truthVtx", float units = 1e3 );
    virtual ~TruthVertexContainer ();

    virtual void setTree         ( TTree* tree );
    virtual void setBranches     ( TTree* tree );
    virtual void clear           ( );
    virtual void FillTruthVertex ( const xAOD::TruthVertex* truthVtx );

    // updateVertex ...

  private:
    // vector branches

    // check what kind of decay truth vertex is (i.e. dark pion decay, dark rho decay, etc.)
    // --> do we want to only save certain truth vertices?
    
    std::vector<float>* m_x;
    std::vector<float>* m_y;
    std::vector<float>* m_z;
    std::vector<float>* m_r;
    std::vector<float>* m_eta;
    std::vector<float>* m_phi;

    std::vector<float>*  m_parent_pt;
    std::vector<float>*  m_parent_eta;
    std::vector<float>*  m_parent_phi;
    std::vector<int>*    m_parent_pid;

    std::vector<float>* m_parent_prod_x;
    std::vector<float>* m_parent_prod_y;
    std::vector<float>* m_parent_prod_z;
    std::vector<float>* m_parent_prod_r;
    std::vector<float>* m_parent_prod_eta;
    std::vector<float>* m_parent_prod_phi;

    std::vector<std::vector<float>>*  m_outP_pt;
    std::vector<std::vector<float>>*  m_outP_eta;
    std::vector<std::vector<float>>*  m_outP_phi;
    std::vector<std::vector<int>>*    m_outP_pid;
    // --> right now, only saving charged outgoing particles...
    // outP_isReco
    
  };
  
} // EJs

#endif // EJsAnalysis_TruthVertexContainer_H
