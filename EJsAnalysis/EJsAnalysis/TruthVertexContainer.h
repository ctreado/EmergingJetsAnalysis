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
    TruthVertexContainer ( const std::string& name = "truthVtx", const std::string& detailStr = "", float units = 1e3,
			   bool mc = false, bool emtopo = true, bool pflow = false);
    virtual ~TruthVertexContainer ();

    virtual void setTree         ( TTree* tree );
    virtual void setBranches     ( TTree* tree );
    virtual void clear           ( );
    virtual void FillTruthVertex ( const xAOD::TruthVertex* truthVtx, const std::vector<std::string>& truthVtxLLPs,
				   const std::string treeName = "" );

    
  private:
    bool m_doEMTopo;
    bool m_doPFlow;
    
    // vector branches
    std::vector<uint8_t>*              m_passSel;
    std::vector<std::string>*          m_llpDecay;
    std::vector<int>*                  m_ID;
    std::vector<int>*                  m_index;
    std::vector<float>*                m_x;
    std::vector<float>*                m_y;
    std::vector<float>*                m_z;
    std::vector<float>*                m_r;
    std::vector<float>*                m_pt;
    std::vector<float>*                m_eta;
    std::vector<float>*                m_phi;
    std::vector<float>*                m_mass;
    std::vector<int>*                  m_nOutP;
    std::vector<int>*                  m_barcode;
    std::vector<float>*                m_childOpenAngle;
    
    std::vector<int>*                  m_parent_ID;
    std::vector<int>*                  m_parent_index;
    std::vector<float>*                m_parent_pt;
    std::vector<float>*                m_parent_eta;
    std::vector<float>*                m_parent_phi;
    std::vector<float>*                m_parent_E;
    std::vector<float>*                m_parent_M;
    std::vector<float>*                m_parent_charge;
    std::vector<int>*                  m_parent_pdgId;
    std::vector<int>*                  m_parent_status;
    std::vector<int>*                  m_parent_barcode;

    std::vector<int>*                  m_parent_prod_ID;
    std::vector<int>*                  m_parent_prod_index;
    std::vector<float>*                m_parent_prod_x;
    std::vector<float>*                m_parent_prod_y;
    std::vector<float>*                m_parent_prod_z;
    std::vector<float>*                m_parent_prod_r;
    std::vector<float>*                m_parent_prod_pt;
    std::vector<float>*                m_parent_prod_eta;
    std::vector<float>*                m_parent_prod_phi;
    std::vector<float>*                m_parent_prod_mass;
    std::vector<int>*                  m_parent_prod_nOutP;
    std::vector<int>*                  m_parent_prod_barcode;

    std::vector<std::vector<int>>*     m_outP_ID;
    std::vector<std::vector<int>>*     m_outP_index;
    std::vector<std::vector<float>>*   m_outP_pt;
    std::vector<std::vector<float>>*   m_outP_eta;
    std::vector<std::vector<float>>*   m_outP_phi;
    std::vector<std::vector<float>>*   m_outP_E;
    std::vector<std::vector<float>>*   m_outP_M;
    std::vector<std::vector<float>>*   m_outP_charge;
    std::vector<std::vector<int>>*     m_outP_pdgId;
    std::vector<std::vector<int>>*     m_outP_status;
    std::vector<std::vector<int>>*     m_outP_barcode;
    std::vector<std::vector<uint8_t>>* m_outP_isReco;
    std::vector<std::vector<uint8_t>>* m_outP_isSelected;
    std::vector<std::vector<uint8_t>>* m_outP_isAssociated;
    std::vector<std::vector<float>>*   m_outP_recoProb;
    std::vector<std::vector<int>>*     m_outP_recoID;
    std::vector<std::vector<int>>*     m_outP_recoIndex;
    std::vector<std::vector<uint8_t>>* m_outP_isStable;
    std::vector<std::vector<uint8_t>>* m_outP_isInteracting;
    std::vector<std::vector<uint8_t>>* m_outP_isDark;


    // reco vertex matching
    std::vector<uint8_t>*              m_isReconstructible;
    
    std::vector<int>*                  m_descendant_n;
    std::vector<int>*                  m_descendant_nReco;
    std::vector<int>*                  m_descendant_nSelected;
    std::vector<float>*                m_descendant_sumPt;
    std::vector<float>*                m_descendant_sumEta;
    std::vector<float>*                m_descendant_sumPhi;
    std::vector<float>*                m_descendant_sumE;
    std::vector<float>*                m_descendant_sumM;
    std::vector<float>*                m_descendant_recoSumPt;
    std::vector<float>*                m_descendant_recoSumEta;
    std::vector<float>*                m_descendant_recoSumPhi;
    std::vector<float>*                m_descendant_recoSumE;
    std::vector<float>*                m_descendant_recoSumM;
    std::vector<std::vector<int>>*     m_descendant_truthPosID;
    std::vector<std::vector<int>>*     m_descendant_ID;
    std::vector<std::vector<int>>*     m_descendant_index;
    std::vector<std::vector<float>>*   m_descendant_pt;
    std::vector<std::vector<float>>*   m_descendant_eta;
    std::vector<std::vector<float>>*   m_descendant_phi;
    std::vector<std::vector<float>>*   m_descendant_E;
    std::vector<std::vector<float>>*   m_descendant_M;
    std::vector<std::vector<float>>*   m_descendant_charge;
    std::vector<std::vector<int>>*     m_descendant_pdgId;
    std::vector<std::vector<int>>*     m_descendant_barcode;
    std::vector<std::vector<uint8_t>>* m_descendant_isReco;
    std::vector<std::vector<uint8_t>>* m_descendant_isSelected;
    std::vector<std::vector<uint8_t>>* m_descendant_isAssociated;
    std::vector<std::vector<float>>*   m_descendant_recoProb;
    std::vector<std::vector<int>>*     m_descendant_recoID;
    std::vector<std::vector<int>>*     m_descendant_recoIndex;
    std::vector<std::vector<float>>*   m_descendant_recoD0;
    std::vector<std::vector<float>>*   m_descendant_recoZ0;
    std::vector<std::vector<int>>*     m_descendant_prod_ID;
    std::vector<std::vector<int>>*     m_descendant_prod_index;
    std::vector<std::vector<float>>*   m_descendant_prod_x;
    std::vector<std::vector<float>>*   m_descendant_prod_y;
    std::vector<std::vector<float>>*   m_descendant_prod_z;
    std::vector<std::vector<float>>*   m_descendant_prod_r;
    std::vector<std::vector<float>>*   m_descendant_prod_phi;
    std::vector<std::vector<int>>*     m_descendant_prod_barcode;
    std::vector<std::vector<int>>*     m_descendant_decay_ID;
    std::vector<std::vector<int>>*     m_descendant_decay_index;
    std::vector<std::vector<float>>*   m_descendant_decay_x;
    std::vector<std::vector<float>>*   m_descendant_decay_y;
    std::vector<std::vector<float>>*   m_descendant_decay_z;
    std::vector<std::vector<float>>*   m_descendant_decay_r;
    std::vector<std::vector<float>>*   m_descendant_decay_phi;
    std::vector<std::vector<int>>*     m_descendant_decay_barcode;

    std::vector<int>*                  m_physPos_n;
    std::vector<float>*                m_physPos_maxSeparation;
    std::vector<std::vector<int>>*     m_physPos_ID;
    std::vector<std::vector<float>>*   m_physPos_x;
    std::vector<std::vector<float>>*   m_physPos_y;
    std::vector<std::vector<float>>*   m_physPos_z;
    std::vector<std::vector<float>>*   m_physPos_r;
    std::vector<std::vector<float>>*   m_physPos_phi;
    std::vector<std::vector<int>>*     m_physPos_nDesc;
    std::vector<std::vector<float>>*   m_physPos_sumPt;
    std::vector<std::vector<float>>*   m_physPos_sumEta;
    std::vector<std::vector<float>>*   m_physPos_sumPhi;
    std::vector<std::vector<float>>*   m_physPos_sumE;
    std::vector<std::vector<float>>*   m_physPos_sumM;

    std::vector<std::vector<int>>*     m_closestRecoVtx_ID;
    std::vector<std::vector<int>>*     m_closestRecoVtx_index;
    std::vector<std::vector<float>>*   m_closestRecoVtx_x;
    std::vector<std::vector<float>>*   m_closestRecoVtx_y;
    std::vector<std::vector<float>>*   m_closestRecoVtx_z;
    std::vector<std::vector<float>>*   m_closestRecoVtx_r;
    std::vector<std::vector<float>>*   m_closestRecoVtx_phi;
    std::vector<std::vector<float>>*   m_closestRecoVtx_distance;

    std::vector<int>*                  m_matchedRecoVtx_n;
    std::vector<std::vector<int>>*     m_matchedRecoVtx_ID;
    std::vector<std::vector<int>>*     m_matchedRecoVtx_index;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_x;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_y;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_z;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_r;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_pt;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_eta;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_phi;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_mass;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_pt_bare;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_eta_bare;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_phi_bare;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_mass_bare;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_chi2;
    std::vector<std::vector<int>>*     m_matchedRecoVtx_ntrk;
    std::vector<std::vector<int>>*     m_matchedRecoVtx_ntrk_sel;
    std::vector<std::vector<int>>*     m_matchedRecoVtx_ntrk_assoc;
    std::vector<std::vector<int>>*     m_matchedRecoVtx_ntrk_filt;
    std::vector<std::vector<int>>*     m_matchedRecoVtx_ntrk_filt_sel;
    std::vector<std::vector<int>>*     m_matchedRecoVtx_ntrk_filt_assoc;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_massFraction;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_multFraction;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_bareMassFraction;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_bareMultFraction;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_matchScore;
    std::vector<std::vector<int>>*     m_matchedRecoVtx_reprTruthPosID;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_reprTruthPosX;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_reprTruthPosY;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_reprTruthPosZ;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_reprTruthPosR;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_reprTruthPosPhi;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_residual_x;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_residual_y;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_residual_z;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_residual_r;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_residual_phi;
    std::vector<std::vector<float>>*   m_matchedRecoVtx_residual_distance;


    // matching jets (jets to which TVs are dR-matched)
    std::vector<uint8_t>*              m_truthJetMatch;
    std::vector<int>*                  m_truthJetMatch_ID;
    std::vector<int>*                  m_truthJetMatch_index;
    std::vector<float>*                m_truthJetMatch_dR;
    std::vector<uint8_t>*              m_darkJetMatch;
    std::vector<int>*                  m_darkJetMatch_ID;
    std::vector<int>*                  m_darkJetMatch_index;
    std::vector<float>*                m_darkJetMatch_dR;
    std::vector<uint8_t>*              m_emtopoJetMatch;
    std::vector<int>*                  m_emtopoJetMatch_ID;
    std::vector<int>*                  m_emtopoJetMatch_index;
    std::vector<float>*                m_emtopoJetMatch_dR;
    std::vector<uint8_t>*              m_pflowJetMatch;
    std::vector<int>*                  m_pflowJetMatch_ID;
    std::vector<int>*                  m_pflowJetMatch_index;
    std::vector<float>*                m_pflowJetMatch_dR;
    
  };
  
} // EJs

#endif // EJsAnalysis_TruthVertexContainer_H
