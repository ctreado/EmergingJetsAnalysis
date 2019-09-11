#ifndef EJsAnalysis_JetContainer_H
#define EJsAnalysis_JetContainer_H

/* JetContainer is the EJs-specific jet container class, 
   derived from the VertexContainer class (to enable handling of EJs info switches)
   and responsible for handling extra jet information not included in the xAH jet class,
   like constituents and matched objects */

#include <vector>
#include <string>

#include <TTree.h>

#include <xAODJet/JetContainer.h>

#include "EJsAnalysis/VertexContainer.h"
#include "EJsAnalysis/EJsHelperClasses.h"

namespace EJs {

  class JetContainer : public VertexContainer < EJsHelperClasses::JetInfoSwitch >
  {
  public:
    JetContainer( const std::string& name = "jet", const std::string& detailStr = "", float units = 1e3,
		  bool mc = false, bool emtopo = true, bool pflow = false );
    virtual ~JetContainer();

    virtual void setTree     ( TTree* tree );
    virtual void setBranches ( TTree* tree );
    virtual void clear       ( );
    virtual void FillJet     ( const xAOD::Jet* jet, const std::vector<std::string>& truthVtxLLP,
			       const std::string treeName = "" );


  private:
    bool m_doEMTopo;
    bool m_doPFlow;
    
    enum jetType { RECO, TRUTH, DARK };
    jetType jet_type;
    
    // vector branches
    std::vector<int>*   m_ID;
    std::vector<int>*   m_index;
    std::vector<float>* m_M;
    std::vector<float>* m_radius;

    // ghost matched tracks
    std::vector<std::vector<int>>*         m_GhostTrack_ID;
    std::vector<std::vector<int>>*         m_GhostTrack_index;
    std::vector<std::vector<float>>*       m_GhostTrack_m;
    std::vector<std::vector<float>>*       m_GhostTrack_errd0;
    std::vector<std::vector<float>>*       m_GhostTrack_errz0;
    std::vector<std::vector<float>>*       m_GhostTrack_chi2;
    std::vector<std::vector<float>>*       m_GhostTrack_charge;
    std::vector<std::vector<uint8_t>>*     m_GhostTrack_isSelected;
    std::vector<std::vector<uint8_t>>*     m_GhostTrack_isAssociated;
    std::vector<std::vector<uint8_t>>*     m_GhostTrack_isTruth;
    std::vector<std::vector<float>>*       m_GhostTrack_truthProb;
    std::vector<std::vector<int>>*         m_GhostTrack_truthID;
    std::vector<std::vector<int>>*         m_GhostTrack_truthIndex;
    std::vector<std::vector<int>>*         m_GhostTrack_truthBarcode;
    std::vector<std::vector<int>>*         m_GhostTrack_truthPdgId;
    std::vector<std::vector<uint8_t>>*     m_GhostTrack_isSecVtxTrk;
    std::vector<std::vector<uint8_t>>*     m_GhostTrack_isSecVtxFiltTrk;
    std::vector<std::vector<int>>*         m_GhostTrack_secVtxID;
    std::vector<std::vector<int>>*         m_GhostTrack_secVtxIndex;
    // ghost matched truth particles
    std::vector<int>*                      m_GhostTruthCount;
    std::vector<float>*                    m_GhostTruthPt;
    std::vector<std::vector<int>>*         m_GhostTruth_ID;
    std::vector<std::vector<int>>*         m_GhostTruth_index;
    std::vector<std::vector<float>>*       m_GhostTruth_pt;
    std::vector<std::vector<float>>*       m_GhostTruth_eta;
    std::vector<std::vector<float>>*       m_GhostTruth_phi;
    std::vector<std::vector<float>>*       m_GhostTruth_e;
    std::vector<std::vector<float>>*       m_GhostTruth_m;
    std::vector<std::vector<float>>*       m_GhostTruth_charge;
    std::vector<std::vector<int>>*         m_GhostTruth_pdgId;
    std::vector<std::vector<int>>*         m_GhostTruth_status;
    std::vector<std::vector<int>>*         m_GhostTruth_barcode;
    std::vector<std::vector<uint8_t>>*     m_GhostTruth_isReco;
    std::vector<std::vector<uint8_t>>*     m_GhostTruth_isSelected;
    std::vector<std::vector<uint8_t>>*     m_GhostTruth_isAssociated;
    std::vector<std::vector<float>>*       m_GhostTruth_recoProb;
    std::vector<std::vector<int>>*         m_GhostTruth_recoID;
    std::vector<std::vector<int>>*         m_GhostTruth_recoIndex;
    std::vector<std::vector<uint8_t>>*     m_GhostTruth_isStable;
    std::vector<std::vector<uint8_t>>*     m_GhostTruth_isInteracting;
    std::vector<std::vector<uint8_t>>*     m_GhostTruth_isDark;
    std::vector<std::vector<std::string>>* m_GhostTruth_pVtx_llpDecay;
    std::vector<std::vector<int>>*         m_GhostTruth_pVtx_ID;
    std::vector<std::vector<int>>*         m_GhostTruth_pVtx_index;
    std::vector<std::vector<std::string>>* m_GhostTruth_dVtx_llpDecay;
    std::vector<std::vector<int>>*         m_GhostTruth_dVtx_ID;
    std::vector<std::vector<int>>*         m_GhostTruth_dVtx_index;
    // --> llp descendant (and generation?)

    // jet constituents --> check if we can get them for reco jets ...
    std::vector<float>*                m_girth;
    std::vector<float>*                m_constituentPt;
    std::vector<std::vector<float>>*   m_constituent_dR;
    std::vector<std::vector<int>>*     m_constituent_ID;
    std::vector<std::vector<int>>*     m_constituent_index;
    std::vector<std::vector<float>>*   m_constituent_m;
    std::vector<std::vector<float>>*   m_constituent_charge;
    std::vector<std::vector<int>>*     m_constituent_pdgId;
    std::vector<std::vector<int>>*     m_constituent_status;
    std::vector<std::vector<int>>*     m_constituent_barcode;
    std::vector<std::vector<uint8_t>>* m_constituent_isStable;
    std::vector<std::vector<uint8_t>>* m_constituent_isInteracting;
    std::vector<std::vector<uint8_t>>* m_constituent_isDark;
    std::vector<std::vector<uint8_t>>* m_constituent_pVtx;
    std::vector<std::vector<float>>*   m_constituent_pVtx_r;
    std::vector<std::vector<uint8_t>>* m_constituent_dVtx;
    std::vector<std::vector<float>>*   m_constituent_dVtx_r;

    // matched truth (dark) jets
    std::vector<uint8_t>* m_isTruthMatched;     // reco jet is truth-matched
    std::vector<int>*     m_truthMatch_ID;
    std::vector<int>*     m_truthMatch_index;
    std::vector<float>*   m_truthMatch_dR;
    std::vector<float>*   m_truthMatch_E;
    std::vector<float>*   m_truthMatch_M;
    std::vector<float>*   m_truthMatch_pt;
    std::vector<float>*   m_truthMatch_eta;
    std::vector<float>*   m_truthMatch_phi;
    std::vector<uint8_t>* m_isDarkMatched;      // reco / truth jet is dark-matched
    std::vector<int>*     m_darkMatch_ID;
    std::vector<int>*     m_darkMatch_index;
    std::vector<float>*   m_darkMatch_dR;
    std::vector<float>*   m_darkMatch_E;
    std::vector<float>*   m_darkMatch_M;
    std::vector<float>*   m_darkMatch_pt;
    std::vector<float>*   m_darkMatch_eta;
    std::vector<float>*   m_darkMatch_phi;
    std::vector<uint8_t>* m_isMatchedToTruth;   // dark jet is matched to truth
    std::vector<int>*     m_matchedTruthID;
    std::vector<int>*     m_matchedTruthIndex;
    std::vector<float>*   m_matchedTruthDR;
    std::vector<uint8_t>* m_isMatchedToEMTopo;  // dark / truth jet is matched to emtopo reco
    std::vector<int>*     m_matchedEMTopoID;
    std::vector<int>*     m_matchedEMTopoIndex;
    std::vector<float>*   m_matchedEMTopoDR;
    std::vector<uint8_t>* m_isMatchedToPFlow;   // dark / truth jet is matched to pflow reco
    std::vector<int>*     m_matchedPFlowID;
    std::vector<int>*     m_matchedPFlowIndex;
    std::vector<float>*   m_matchedPFlowDR;

    // matched secondary vertices
    std::vector<int>*                      m_secVtxCount;
    std::vector<float>*                    m_secVtxPt;
    std::vector<float>*                    m_secVtxBarePt;
    std::vector<std::vector<int>>*         m_secVtx_ID;
    std::vector<std::vector<int>>*         m_secVtx_index;
    std::vector<std::vector<float>>*       m_secVtx_x;
    std::vector<std::vector<float>>*       m_secVtx_y;
    std::vector<std::vector<float>>*       m_secVtx_z;
    std::vector<std::vector<float>>*       m_secVtx_r;
    std::vector<std::vector<float>>*       m_secVtx_pt;
    std::vector<std::vector<float>>*       m_secVtx_eta;
    std::vector<std::vector<float>>*       m_secVtx_phi;
    std::vector<std::vector<float>>*       m_secVtx_mass;
    std::vector<std::vector<float>>*       m_secVtx_pt_bare;
    std::vector<std::vector<float>>*       m_secVtx_eta_bare;
    std::vector<std::vector<float>>*       m_secVtx_phi_bare;
    std::vector<std::vector<float>>*       m_secVtx_mass_bare;
    std::vector<std::vector<float>>*       m_secVtx_chi2;
    std::vector<std::vector<float>>*       m_secVtx_distToPV;
    std::vector<std::vector<int>>*         m_secVtx_ntrk;
    std::vector<std::vector<int>>*         m_secVtx_ntrk_sel;
    std::vector<std::vector<int>>*         m_secVtx_ntrk_assoc;
    std::vector<std::vector<int>>*         m_secVtx_ntrk_filt;
    std::vector<std::vector<int>>*         m_secVtx_ntrk_filt_sel;
    std::vector<std::vector<int>>*         m_secVtx_ntrk_filt_assoc;
    std::vector<std::vector<float>>*       m_secVtx_dR;
    std::vector<std::vector<uint8_t>>*     m_secVtx_isTruthMatched;
    // matched truth vertices
    std::vector<int>*                      m_truthVtxCount;
    std::vector<float>*                    m_truthVtxPt;
    std::vector<std::vector<std::string>>* m_truthVtx_llpDecay;
    std::vector<std::vector<int>>*         m_truthVtx_ID;
    std::vector<std::vector<int>>*         m_truthVtx_index;
    std::vector<std::vector<float>>*       m_truthVtx_x;
    std::vector<std::vector<float>>*       m_truthVtx_y;
    std::vector<std::vector<float>>*       m_truthVtx_z;
    std::vector<std::vector<float>>*       m_truthVtx_r;
    std::vector<std::vector<float>>*       m_truthVtx_pt;
    std::vector<std::vector<float>>*       m_truthVtx_eta;
    std::vector<std::vector<float>>*       m_truthVtx_phi;
    std::vector<std::vector<float>>*       m_truthVtx_mass;
    std::vector<std::vector<int>>*         m_truthVtx_nOutP;
    std::vector<std::vector<int>>*         m_truthVtx_barcode;
    std::vector<std::vector<float>>*       m_truthVtx_dR;
    std::vector<std::vector<uint8_t>>*     m_truthVtx_isReconstructible;
    std::vector<std::vector<uint8_t>>*     m_truthVtx_isRecoMatched;

    // matched tracks
    std::vector<int>*                      m_trkCount;
    std::vector<float>*                    m_trkPt;
    std::vector<std::vector<int>>*         m_trk_ID;
    std::vector<std::vector<int>>*         m_trk_index;
    std::vector<std::vector<float>>*       m_trk_qOverP;
    std::vector<std::vector<float>>*       m_trk_E;
    std::vector<std::vector<float>>*       m_trk_M;
    std::vector<std::vector<float>>*       m_trk_pt;
    std::vector<std::vector<float>>*       m_trk_eta;
    std::vector<std::vector<float>>*       m_trk_phi;
    std::vector<std::vector<float>>*       m_trk_d0;
    std::vector<std::vector<float>>*       m_trk_z0;
    std::vector<std::vector<float>>*       m_trk_errd0;
    std::vector<std::vector<float>>*       m_trk_errz0;
    std::vector<std::vector<float>>*       m_trk_chi2;
    std::vector<std::vector<float>>*       m_trk_charge;
    std::vector<std::vector<uint8_t>>*     m_trk_isSelected;
    std::vector<std::vector<uint8_t>>*     m_trk_isAssociated;
    std::vector<std::vector<float>>*       m_trk_dR;
    std::vector<std::vector<uint8_t>>*     m_trk_isSecVtxTrk;
    std::vector<std::vector<uint8_t>>*     m_trk_isSecVtxFiltTrk;
    std::vector<std::vector<int>>*         m_trk_secVtxID;
    std::vector<std::vector<int>>*         m_trk_secVtxIndex;
    std::vector<std::vector<uint8_t>>*     m_trk_isTruth;
    std::vector<std::vector<float>>*       m_trk_truthProb;
    std::vector<std::vector<int>>*         m_trk_truthID;
    std::vector<std::vector<int>>*         m_trk_truthIndex;
    std::vector<std::vector<int>>*         m_trk_truthBarcode;
    std::vector<std::vector<int>>*         m_trk_truthPdgId;
    // matched truth particles
    std::vector<int>*                      m_tpCount;
    std::vector<float>*                    m_tpPt;
    std::vector<std::vector<int>>*         m_tp_ID;
    std::vector<std::vector<int>>*         m_tp_index;
    std::vector<std::vector<float>>*       m_tp_pt;
    std::vector<std::vector<float>>*       m_tp_eta;
    std::vector<std::vector<float>>*       m_tp_phi;
    std::vector<std::vector<float>>*       m_tp_E;
    std::vector<std::vector<float>>*       m_tp_M;
    std::vector<std::vector<float>>*       m_tp_charge;
    std::vector<std::vector<int>>*         m_tp_pdgId;
    std::vector<std::vector<int>>*         m_tp_status;
    std::vector<std::vector<int>>*         m_tp_barcode;
    std::vector<std::vector<float>>*       m_tp_dR;
    std::vector<std::vector<uint8_t>>*     m_tp_isReco;
    std::vector<std::vector<uint8_t>>*     m_tp_isSelected;
    std::vector<std::vector<uint8_t>>*     m_tp_isAssociated;
    std::vector<std::vector<float>>*       m_tp_recoProb;
    std::vector<std::vector<int>>*         m_tp_recoID;
    std::vector<std::vector<int>>*         m_tp_recoIndex;
    std::vector<std::vector<uint8_t>>*     m_tp_isStable;
    std::vector<std::vector<uint8_t>>*     m_tp_isInteracting;
    std::vector<std::vector<uint8_t>>*     m_tp_isDark;
    // --> llp descendant (and generation?)
    std::vector<std::vector<std::string>>* m_tp_pVtx_llpDecay;
    std::vector<std::vector<int>>*         m_tp_pVtx_ID;
    std::vector<std::vector<int>>*         m_tp_pVtx_index;
    std::vector<std::vector<std::string>>* m_tp_dVtx_llpDecay;
    std::vector<std::vector<int>>*         m_tp_dVtx_ID;
    std::vector<std::vector<int>>*         m_tp_dVtx_index;
    
  };

}

#endif // EJsAnalysis_JetContainer_H
