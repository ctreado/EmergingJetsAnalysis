#ifndef EJsAnalysis_TruthVertexContainer_H
#define EJsAnalysis_TruthVertexContainer_H

/* TruthVertexContainer is the truth-vertex-specific derived class
   of the VertexContainer base class, responsible for handling truth vertex
   information (including LLP decay vertices of interest)
   to fill output ntuples; based partially on VSI performance code
   (https://gitlab.cern.ch/Atlas-Inner-Tracking/SecVtxPUBNote/tree/master/Code/VSIPerf) */

#include <vector>
#include <string>

#include <TTree.h>

#include <xAODTruth/TruthVertex.h>

#include "EJsAnalysis/VertexContainer.h"
#include "EJsAnalysis/EJsHelperClasses.h"

namespace EJs {

  class TruthVertexContainer : public VertexContainer < EJsHelperClasses::TruthVertexInfoSwitch >
  {
  public:
    TruthVertexContainer ( const std::string& name = "truthVtx", const std::string& detailStr = "", float units = 1e3 );
    virtual ~TruthVertexContainer ();

    virtual void setTree         ( TTree* tree );
    virtual void setBranches     ( TTree* tree );
    virtual void clear           ( );
    virtual void FillTruthVertex ( const xAOD::TruthVertex* truthVtx );

    
  private:
    // vector branches
    std::vector<uint8_t>* m_isDarkPionDecay;

    std::vector<int>*   m_ID;
    std::vector<int>*   m_barcode;
    std::vector<float>* m_x;
    std::vector<float>* m_y;
    std::vector<float>* m_z;
    std::vector<float>* m_r;
    std::vector<float>* m_eta;
    std::vector<float>* m_phi;

    std::vector<int>*   m_parent_ID;
    std::vector<int>*   m_parent_barcode;
    std::vector<float>* m_parent_pt;
    std::vector<float>* m_parent_eta;
    std::vector<float>* m_parent_phi;
    std::vector<float>* m_parent_charge;
    std::vector<int>*   m_parent_pid;

    std::vector<int>*   m_parent_prod_ID;
    std::vector<int>*   m_parent_prod_barcode;
    std::vector<float>* m_parent_prod_x;
    std::vector<float>* m_parent_prod_y;
    std::vector<float>* m_parent_prod_z;
    std::vector<float>* m_parent_prod_r;
    std::vector<float>* m_parent_prod_eta;
    std::vector<float>* m_parent_prod_phi;

    std::vector<std::vector<int>>*     m_outP_ID;
    std::vector<std::vector<int>>*     m_outP_barcode;
    std::vector<std::vector<float>>*   m_outP_pt;
    std::vector<std::vector<float>>*   m_outP_eta;
    std::vector<std::vector<float>>*   m_outP_phi;
    std::vector<std::vector<float>>*   m_outP_charge;
    std::vector<std::vector<int>>*     m_outP_pid;
    std::vector<std::vector<uint8_t>>* m_outP_isReco;
    std::vector<std::vector<float>>*   m_outP_recoProb;
    // --> add branches for corresponding isReco tracks (??) ...
    
  };
  
} // EJs

#endif // EJsAnalysis_TruthVertexContainer_H
