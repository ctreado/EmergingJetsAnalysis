#ifndef EJsAnalysis_JetContainer_H
#define EJsAnalysis_JetContainer_H

#include <xAODAnaHelpers/JetContainer.h>

namespace EJs {

  class JetContainer : public xAH::JetContainer
  {
  public:
    JetContainer( const std::string& name = "jet", const std::string& detailStr = "", float units = 1e3, bool mc = false );
    virtual ~JetContainer();

    virtual void setTree     ( TTree* tree );
    virtual void setBranches ( TTree* tree );
    virtual void clear       ( );
    virtual void FillJet     ( const xAOD::Jet* jet );


  private:
    // vector branches
    std::vector<int>*   m_ID;
    std::vector<float>* m_radius;

    // matched truth (dark) jets
    std::vector<uint8_t>*            m_isTruthMatched;
    std::vector<int>*                m_truthMatchID;
    std::vector<float>*              m_truthMatchDR;
    std::vector<std::vector<int>>*   m_truthNonmatchIDs;
    std::vector<std::vector<float>>* m_truthNonmatchDRs;
    std::vector<uint8_t>*            m_isDarkMatched;
    std::vector<int>*                m_darkMatchID;
    std::vector<float>*              m_darkMatchDR;
    std::vector<std::vector<int>>*   m_darkNonmatchIDs;
    std::vector<std::vector<float>>* m_darkNonmatchDRs;
    // matched vertices
    std::vector<std::vector<uint8_t>>* m_truthVtx_isDarkPionDecay;
    std::vector<std::vector<int>>*     m_truthVtx_ID;
    std::vector<std::vector<int>>*     m_truthVtx_barcode;
    std::vector<std::vector<float>>*   m_truthVtx_dR;
    // --> isReco (isClose(st) / is(Max)Linked) --> need to decorate truth vertices accordingly first (and do reco-to-truth matching)
    std::vector<std::vector<int>>*     m_secVtx_ID;
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
    // matched truth particles / tracks
    std::vector<std::vector<int>>*     m_tp_ID;
    std::vector<std::vector<int>>*     m_tp_barcode;
    std::vector<std::vector<int>>*     m_tp_pid;
    std::vector<std::vector<uint8_t>>* m_tp_isReco;
    std::vector<std::vector<float>>*   m_tp_recoProb;
    std::vector<std::vector<int>>*     m_tp_recoID;
    std::vector<std::vector<float>>*   m_tp_dR;
    std::vector<std::vector<int>>*     m_trk_ID;
    std::vector<std::vector<uint8_t>>* m_trk_isTruth;
    std::vector<std::vector<float>>*   m_trk_truthProb;
    std::vector<std::vector<int>>*     m_trk_truthID;
    std::vector<std::vector<int>>*     m_trk_truthBarcode;
    std::vector<std::vector<int>>*     m_trk_truthPid;
    std::vector<std::vector<float>>*   m_trk_dR;

    // jet constituents
    std::vector<std::vector<float>>* m_constit_E;
    std::vector<std::vector<float>>* m_constit_pt;
    std::vector<std::vector<float>>* m_constit_eta;
    std::vector<std::vector<float>>* m_constit_phi;
  };

  #define AUXDYN( obj, type, varname ) \
  ( obj->isAvailable<type>(varname) ? obj->auxdataConst<type>(varname) : std::numeric_limits<type>::quiet_NaN() )

  #define AUXDYNVEC( obj, type, varname ) \
    ( obj->isAvailable<std::vector<type>>(varname) ? obj->auxdataConst<std::vector<type>>(varname) : std::vector<type>() )

}

#endif // EJsAnalysis_JetContainer_H
