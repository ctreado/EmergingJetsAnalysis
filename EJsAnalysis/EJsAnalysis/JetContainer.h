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
    JetContainer( const std::string& name = "jet", const std::string& detailStr = "", float units = 1e3, bool mc = false );
    virtual ~JetContainer();

    virtual void setTree     ( TTree* tree );
    virtual void setBranches ( TTree* tree );
    virtual void clear       ( );
    virtual void FillJet     ( const xAOD::Jet* jet, const std::string treeName = "" );


  private:
    enum jetType { RECO, TRUTH, DARK };
    jetType jet_type;
    
    // vector branches
    std::vector<int>*   m_ID;
    std::vector<float>* m_M;
    std::vector<float>* m_radius;

    // matched truth (dark) jets
    std::vector<uint8_t>*            m_isTruthMatched;        // reco jet is truth-matched
    std::vector<int>*                m_truthMatch_ID;
    std::vector<float>*              m_truthMatch_dR;
    std::vector<float>*              m_truthMatch_E;
    std::vector<float>*              m_truthMatch_M;
    std::vector<float>*              m_truthMatch_pt;
    std::vector<float>*              m_truthMatch_eta;
    std::vector<float>*              m_truthMatch_phi;
    std::vector<float>*              m_truthMatch_rapidity;
    std::vector<std::vector<int>>*   m_truthNonmatch_IDs;
    std::vector<std::vector<float>>* m_truthNonmatch_dRs;
    std::vector<uint8_t>*            m_isDarkMatched;         // reco / truth jet is dark-matched
    std::vector<int>*                m_darkMatch_ID;
    std::vector<float>*              m_darkMatch_dR;
    std::vector<float>*              m_darkMatch_E;
    std::vector<float>*              m_darkMatch_M;
    std::vector<float>*              m_darkMatch_pt;
    std::vector<float>*              m_darkMatch_eta;
    std::vector<float>*              m_darkMatch_phi;
    std::vector<float>*              m_darkMatch_rapidity;
    std::vector<std::vector<int>>*   m_darkNonmatch_IDs;
    std::vector<std::vector<float>>* m_darkNonmatch_dRs;
    std::vector<uint8_t>*            m_isMatchedToTruth;      // dark jet is matched to truth
    std::vector<int>*                m_matchedTruthID;
    std::vector<float>*              m_matchedTruthDR;
    std::vector<uint8_t>*            m_isMatchedToEMTopoReco; // dark / truth jet is matched to emtopo reco
    std::vector<int>*                m_matchedEMTopoRecoID;
    std::vector<float>*              m_matchedEMTopoRecoDR;
    std::vector<uint8_t>*            m_isMatchedToPFlowReco;  // dark / truth jet is matched to pflow reco
    std::vector<int>*                m_matchedPFlowRecoID;
    std::vector<float>*              m_matchedPFlowRecoDR;
    // matched vertices
    std::vector<int>*                  m_secVtxCount;
    std::vector<float>*                m_secVtxPt;
    std::vector<std::vector<int>>*     m_secVtx_ID;
    std::vector<std::vector<float>>*   m_secVtx_x;
    std::vector<std::vector<float>>*   m_secVtx_y;
    std::vector<std::vector<float>>*   m_secVtx_z;
    std::vector<std::vector<float>>*   m_secVtx_r;
    std::vector<std::vector<float>>*   m_secVtx_pt;
    std::vector<std::vector<float>>*   m_secVtx_eta;
    std::vector<std::vector<float>>*   m_secVtx_phi;
    std::vector<std::vector<float>>*   m_secVtx_mass;
    std::vector<std::vector<float>>*   m_secVtx_chi2;
    std::vector<std::vector<int>>*     m_secVtx_ntrk; // ntrk_sel/assoc ... ??
    std::vector<std::vector<float>>*   m_secVtx_dR;
    std::vector<std::vector<uint8_t>>* m_secVtx_closestTruth_isDarkPionDecay;
    std::vector<std::vector<int>>*     m_secVtx_closestTruth_ID;
    std::vector<std::vector<int>>*     m_secVtx_closestTruth_barcode;
    std::vector<std::vector<float>>*   m_secVtx_closestTruth_distance;
    std::vector<std::vector<uint8_t>>* m_secVtx_maxlinkTruth_isDarkPionDecay;
    std::vector<std::vector<int>>*     m_secVtx_maxlinkTruth_ID;
    std::vector<std::vector<int>>*     m_secVtx_maxlinkTruth_barcode;
    std::vector<std::vector<float>>*   m_secVtx_maxlinkTruth_score;
    std::vector<std::vector<uint8_t>>* m_secVtx_maxlinkParentTruth_isDarkPionDecay;
    std::vector<std::vector<int>>*     m_secVtx_maxlinkParentTruth_ID;
    std::vector<std::vector<int>>*     m_secVtx_maxlinkParentTruth_barcode;
    std::vector<std::vector<float>>*   m_secVtx_maxlinkParentTruth_score;
    std::vector<int>*                  m_truthVtxCount;
    std::vector<float>*                m_truthVtxPt;
    std::vector<std::vector<uint8_t>>* m_truthVtx_isDarkPionDecay;
    std::vector<std::vector<int>>*     m_truthVtx_ID;
    std::vector<std::vector<float>>*   m_truthVtx_x;
    std::vector<std::vector<float>>*   m_truthVtx_y;
    std::vector<std::vector<float>>*   m_truthVtx_z;
    std::vector<std::vector<float>>*   m_truthVtx_r;
    std::vector<std::vector<float>>*   m_truthVtx_pt;
    std::vector<std::vector<float>>*   m_truthVtx_eta;
    std::vector<std::vector<float>>*   m_truthVtx_phi;
    std::vector<std::vector<float>>*   m_truthVtx_mass;
    std::vector<std::vector<int>>*     m_truthVtx_nOutP; // n charged, reco, reconstructible out parts ... ??
    std::vector<std::vector<int>>*     m_truthVtx_barcode;
    std::vector<std::vector<float>>*   m_truthVtx_dR;
    // --> isReco (isClose(st) / is(Max)Linked) --> need to decorate truth vertices accordingly first (and do reco-to-truth matching)
    
    // matched tracks / truth particles
    std::vector<int>*                  m_trkCount;
    std::vector<float>*                m_trkPt;
    std::vector<std::vector<int>>*     m_trk_ID;
    std::vector<std::vector<float>>*   m_trk_qOverP;
    std::vector<std::vector<float>>*   m_trk_E;
    std::vector<std::vector<float>>*   m_trk_M;
    std::vector<std::vector<float>>*   m_trk_pt;
    std::vector<std::vector<float>>*   m_trk_eta;
    std::vector<std::vector<float>>*   m_trk_phi;
    std::vector<std::vector<float>>*   m_trk_d0;
    std::vector<std::vector<float>>*   m_trk_z0;
    std::vector<std::vector<float>>*   m_trk_errd0;
    std::vector<std::vector<float>>*   m_trk_errz0;
    std::vector<std::vector<float>>*   m_trk_chi2;
    std::vector<std::vector<float>>*   m_trk_charge;
    std::vector<std::vector<uint8_t>>* m_trk_isSelected;
    std::vector<std::vector<uint8_t>>* m_trk_isAssociated;
    std::vector<std::vector<float>>*   m_trk_dR;
    std::vector<std::vector<uint8_t>>* m_trk_isTruth;
    std::vector<std::vector<float>>*   m_trk_truthProb;
    std::vector<std::vector<int>>*     m_trk_truthID;
    std::vector<std::vector<int>>*     m_trk_truthBarcode;
    std::vector<std::vector<int>>*     m_trk_truthPid;
    std::vector<int>*                  m_tpCount;
    std::vector<float>*                m_tpPt;
    std::vector<std::vector<int>>*     m_tp_ID;
    std::vector<std::vector<float>>*   m_tp_pt;
    std::vector<std::vector<float>>*   m_tp_eta;
    std::vector<std::vector<float>>*   m_tp_phi;
    std::vector<std::vector<float>>*   m_tp_E;
    std::vector<std::vector<float>>*   m_tp_M;
    std::vector<std::vector<float>>*   m_tp_charge;
    std::vector<std::vector<int>>*     m_tp_pid;
    std::vector<std::vector<int>>*     m_tp_status;
    std::vector<std::vector<int>>*     m_tp_barcode;
    std::vector<std::vector<float>>*   m_tp_dR;
    std::vector<std::vector<uint8_t>>* m_tp_isReco;
    std::vector<std::vector<float>>*   m_tp_recoProb;
    std::vector<std::vector<int>>*     m_tp_recoID;
    std::vector<std::vector<uint8_t>>* m_tp_recoIsSelected;
    std::vector<std::vector<uint8_t>>* m_tp_recoIsAssociated;
    // --> want to add truth parents / ancestors ?? --> at least check if truth particle is dark pion descendant (and generation) 

    // ghost matched tracks / truth particles
    std::vector<std::vector<int>>*     m_GhostTrack_ID;
    std::vector<std::vector<float>>*   m_GhostTrack_m;
    std::vector<std::vector<float>>*   m_GhostTrack_errd0;
    std::vector<std::vector<float>>*   m_GhostTrack_errz0;
    std::vector<std::vector<float>>*   m_GhostTrack_chi2;
    std::vector<std::vector<float>>*   m_GhostTrack_charge;
    std::vector<std::vector<uint8_t>>* m_GhostTrack_isSelected;
    std::vector<std::vector<uint8_t>>* m_GhostTrack_isAssociated;
    std::vector<std::vector<uint8_t>>* m_GhostTrack_isTruth;
    std::vector<std::vector<float>>*   m_GhostTrack_truthProb;
    std::vector<std::vector<int>>*     m_GhostTrack_truthID;
    std::vector<std::vector<int>>*     m_GhostTrack_truthBarcode;
    std::vector<std::vector<int>>*     m_GhostTrack_truthPid;
    std::vector<int>*                  m_GhostTruthCount;
    std::vector<float>*                m_GhostTruthPt;
    std::vector<std::vector<int>>*     m_GhostTruth_ID;
    std::vector<std::vector<float>>*   m_GhostTruth_pt;
    std::vector<std::vector<float>>*   m_GhostTruth_eta;
    std::vector<std::vector<float>>*   m_GhostTruth_phi;
    std::vector<std::vector<float>>*   m_GhostTruth_e;
    std::vector<std::vector<float>>*   m_GhostTruth_m;
    std::vector<std::vector<float>>*   m_GhostTruth_charge;
    std::vector<std::vector<int>>*     m_GhostTruth_pid;
    std::vector<std::vector<int>>*     m_GhostTruth_status;
    std::vector<std::vector<int>>*     m_GhostTruth_barcode;
    std::vector<std::vector<uint8_t>>* m_GhostTruth_isReco;
    std::vector<std::vector<float>>*   m_GhostTruth_recoProb;
    std::vector<std::vector<int>>*     m_GhostTruth_recoID;
    std::vector<std::vector<uint8_t>>* m_GhostTruth_recoIsSelected;
    std::vector<std::vector<uint8_t>>* m_GhostTruth_recoIsAssociated;
    // --> want to add truth parents / ancestors ?? --> at least check if truth particle is dark pion descendant (and generation)

    // jet constituents
    std::vector<float>*              m_girth;
    std::vector<float>*              m_constituentPt;
    std::vector<std::vector<float>>* m_constituent_dR;
    std::vector<std::vector<float>>* m_constituent_m;
  };

}

#endif // EJsAnalysis_JetContainer_H
