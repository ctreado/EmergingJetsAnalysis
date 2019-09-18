#ifndef EJsAnalysis_SecondaryVertexContainer_H
#define EJsAnalysis_SecondaryVertexContainer_H

/* SecondaryVertexContainer is the secondary-vertex-specific derived class
   of the VertexContainer base class, responsible for handling VrtSecInclusive DV
   information (including associated tracks, matched truth vertices, etc.)
   to fill output ntuples; based partially on VSI performance code
   (https://gitlab.cern.ch/Atlas-Inner-Tracking/SecVtxPUBNote/tree/master/Code/VSIPerf) */

#include <vector>
#include <string>

#include <TTree.h>

#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>

#include "EJsAnalysis/VertexContainer.h"
#include "EJsAnalysis/EJsHelperClasses.h"

namespace EJs {

  class SecondaryVertexContainer : public VertexContainer < EJsHelperClasses::SecondaryVertexInfoSwitch >
  {
  public:
    SecondaryVertexContainer ( const std::string& name = "secVtx", const std::string& detailStr = "", float units = 1e3,
			       bool mc = false, bool emtopo = true, bool pflow = false );
    virtual ~SecondaryVertexContainer ();

    virtual void setTree             ( TTree* tree );
    virtual void setBranches         ( TTree* tree );
    virtual void clear               ( );
    virtual void FillSecondaryVertex ( const xAOD::Vertex* secVtx,      const std::vector<std::string>& truthVtxLLPs,
				       const std::string treeName = "", const xAOD::Vertex* pv = 0 );


  private:   
    void recordTracks        ( const std::vector<const xAOD::TrackParticle*>& );
    //void processDVJets       ( const std::vector<const xAOD::TrackParticle*>& );

    bool m_doEMTopo;
    bool m_doPFlow;

    
    // vector branches
    std::vector<int>*                m_ID;
    std::vector<int>*                m_index;
    std::vector<float>*              m_x;
    std::vector<float>*              m_y;
    std::vector<float>*              m_z;
    std::vector<float>*              m_r;
    std::vector<float>*              m_pt;
    std::vector<float>*              m_eta;
    std::vector<float>*              m_phi;
    std::vector<float>*              m_mass;
    std::vector<float>*              m_mass_nonAssoc;
    std::vector<std::vector<float>>* m_covariance;
    std::vector<float>*              m_chi2;
    std::vector<float>*              m_direction;
    std::vector<int>*                m_charge;
    std::vector<float>*              m_H;
    std::vector<float>*              m_Ht;
    std::vector<float>*              m_minOpAng;
    std::vector<float>*              m_maxOpAng;
    std::vector<float>*              m_mind0;
    std::vector<float>*              m_maxd0;
    std::vector<float>*              m_distToPV;

    std::vector<float>*              m_pt_clean;
    std::vector<float>*              m_eta_clean;
    std::vector<float>*              m_phi_clean;
    std::vector<float>*              m_mass_clean;
    std::vector<float>*              m_mass_nonAssoc_clean;
    std::vector<float>*              m_direction_clean;
    std::vector<int>*                m_charge_clean;
    std::vector<float>*              m_H_clean;
    std::vector<float>*              m_Ht_clean;
    std::vector<float>*              m_minOpAng_clean;
    std::vector<float>*              m_maxOpAng_clean;
    std::vector<float>*              m_mind0_clean;
    std::vector<float>*              m_maxd0_clean;
    
    std::vector<float>*              m_pt_bare;
    std::vector<float>*              m_eta_bare;
    std::vector<float>*              m_phi_bare;
    std::vector<float>*              m_mass_bare;
    std::vector<float>*              m_mass_nonAssoc_bare;
    std::vector<float>*              m_direction_bare;
    std::vector<int>*                m_charge_bare;
    std::vector<float>*              m_H_bare;
    std::vector<float>*              m_Ht_bare;
    std::vector<float>*              m_minOpAng_bare;
    std::vector<float>*              m_maxOpAng_bare;
    std::vector<float>*              m_mind0_bare;
    std::vector<float>*              m_maxd0_bare;
    
    std::vector<float>*              m_minOneTrackRemovedMass;
    std::vector<std::vector<float>>* m_twoTracksMass;
    std::vector<std::vector<float>>* m_twoTracksMassRest;
    std::vector<std::vector<int>>*   m_twoTracksCharge;

    std::vector<float>*              m_minOneTrackRemovedMass_clean;
    std::vector<std::vector<float>>* m_twoTracksMass_clean;
    std::vector<std::vector<float>>* m_twoTracksMassRest_clean;
    std::vector<std::vector<int>>*   m_twoTracksCharge_clean;

    std::vector<float>*              m_minOneTrackRemovedMass_bare;
    std::vector<std::vector<float>>* m_twoTracksMass_bare;
    std::vector<std::vector<float>>* m_twoTracksMassRest_bare;
    std::vector<std::vector<int>>*   m_twoTracksCharge_bare;
    
    std::vector<int>*                m_ntrk;
    std::vector<int>*                m_ntrk_sel;
    std::vector<int>*                m_ntrk_assoc;
    std::vector<int>*                m_ntrk_clean;
    std::vector<int>*                m_ntrk_clean_sel;
    std::vector<int>*                m_ntrk_clean_assoc;
    std::vector<int>*                m_ntrk_filt;
    std::vector<int>*                m_ntrk_filt_sel;
    std::vector<int>*                m_ntrk_filt_assoc;

    
    // tracks
    std::vector<std::vector<int>>*      m_trk_ID;
    std::vector<std::vector<int>>*      m_trk_index;
    std::vector<std::vector<float>>*    m_trk_qOverP;
    std::vector<std::vector<float>>*    m_trk_theta;
    std::vector<std::vector<float>>*    m_trk_vz;
    std::vector<std::vector<float>>*    m_trk_E;
    std::vector<std::vector<float>>*    m_trk_M;
    std::vector<std::vector<float>>*    m_trk_pt;
    std::vector<std::vector<float>>*    m_trk_eta;
    std::vector<std::vector<float>>*    m_trk_phi;
    std::vector<std::vector<float>>*    m_trk_d0;
    std::vector<std::vector<float>>*    m_trk_z0;
    std::vector<std::vector<float>>*    m_trk_errd0;
    std::vector<std::vector<float>>*    m_trk_errz0;
    std::vector<std::vector<float>>*    m_trk_chi2;

    std::vector<std::vector<float>>*    m_trk_pt_wrtSV;
    std::vector<std::vector<float>>*    m_trk_eta_wrtSV;
    std::vector<std::vector<float>>*    m_trk_phi_wrtSV;
    std::vector<std::vector<float>>*    m_trk_d0_wrtSV;
    std::vector<std::vector<float>>*    m_trk_z0_wrtSV;
    std::vector<std::vector<float>>*    m_trk_errd0_wrtSV;
    std::vector<std::vector<float>>*    m_trk_errz0_wrtSV;
    std::vector<std::vector<float>>*    m_trk_errP_wrtSV;
    std::vector<std::vector<float>>*    m_trk_chi2_toSV;

    std::vector<std::vector<int>>*      m_trk_charge;
    std::vector<std::vector<uint8_t>>*  m_trk_isFinal;
    std::vector<std::vector<uint8_t>>*  m_trk_isSelected;
    std::vector<std::vector<uint8_t>>*  m_trk_isAssociated;
    std::vector<std::vector<uint8_t>>*  m_trk_isClean;
    std::vector<std::vector<uint8_t>>*  m_trk_isFiltered;
    std::vector<std::vector<uint8_t>>*  m_trk_nPixelHits;
    std::vector<std::vector<uint8_t>>*  m_trk_nSCTHits;
    std::vector<std::vector<uint8_t>>*  m_trk_nTRTHits;
    std::vector<std::vector<uint8_t>>*  m_trk_nPixelBarrelLayers;
    std::vector<std::vector<uint8_t>>*  m_trk_nPixelEndCapLayers;
    std::vector<std::vector<uint8_t>>*  m_trk_nSCTBarrelLayers;
    std::vector<std::vector<uint8_t>>*  m_trk_nSCTEndCapLayers;
    std::vector<std::vector<uint32_t>>* m_trk_hitPattern;
    std::vector<std::vector<float>>*    m_trk_dEdx;
    std::vector<std::vector<uint8_t>>*  m_trk_nUsedHitsdEdx;
    std::vector<std::vector<uint8_t>>*  m_trk_nIBLOverflowsdEdx;
    std::vector<std::vector<float>>*    m_trk_radiusOfFirstHit;

    std::vector<std::vector<float>>*    m_trk_truthProb;
    std::vector<std::vector<int>>*      m_trk_truthID;
    std::vector<std::vector<int>>*      m_trk_truthIndex;
    std::vector<std::vector<int>>*      m_trk_truthBarcode;
    std::vector<std::vector<int>>*      m_trk_truthPdgId;
    std::vector<std::vector<uint8_t>>*  m_trk_truthIsDesc;

    
    // jets
    // jets ... some alg that makes jets out of filtered tracks ?? probably don't need this...


    // truth vertex matching
    std::vector<std::string>*              m_closestTruthVtx_llpDecay;
    std::vector<uint8_t>*                  m_closestTruthVtx_isReconstructible;
    std::vector<int>*                      m_closestTruthVtx_ID;
    std::vector<int>*                      m_closestTruthVtx_index;
    std::vector<float>*                    m_closestTruthVtx_x;
    std::vector<float>*                    m_closestTruthVtx_y;
    std::vector<float>*                    m_closestTruthVtx_z;
    std::vector<float>*                    m_closestTruthVtx_r;
    std::vector<float>*                    m_closestTruthVtx_phi;
    std::vector<int>*                      m_closestTruthVtx_barcode;
    std::vector<float>*                    m_closestTruthVtx_distance;
    std::vector<int>*                      m_closestTruthVtxPhysPos_ID;
    std::vector<float>*                    m_closestTruthVtxPhysPos_x;
    std::vector<float>*                    m_closestTruthVtxPhysPos_y;
    std::vector<float>*                    m_closestTruthVtxPhysPos_z;
    std::vector<float>*                    m_closestTruthVtxPhysPos_r;
    std::vector<float>*                    m_closestTruthVtxPhysPos_phi;
    std::vector<float>*                    m_closestTruthVtxPhysPos_distance;

    std::vector<int>*                      m_matchedTruthVtx_n;
    std::vector<std::vector<std::string>>* m_matchedTruthVtx_llpDecay;
    std::vector<std::vector<int>>*         m_matchedTruthVtx_ID;
    std::vector<std::vector<int>>*         m_matchedTruthVtx_index;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_x;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_y;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_z;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_r;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_pt;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_eta;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_phi;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_mass;
    std::vector<std::vector<int>>*         m_matchedTruthVtx_barcode;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_distance;
    std::vector<std::vector<int>>*         m_matchedTruthVtx_nDesc;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_descSumPt;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_descSumEta;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_descSumPhi;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_descSumM;
    std::vector<std::vector<int>>*         m_matchedTruthVtx_nRecoDesc;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_recoDescSumPt;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_recoDescSumEta;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_recoDescSumPhi;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_recoDescSumM;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_massFraction;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_multFraction;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_cleanMassFraction;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_cleanMultFraction;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_bareMassFraction;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_bareMultFraction;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_matchScore;
    std::vector<std::vector<int>>*         m_matchedTruthVtxReprPhysPos_ID;
    std::vector<std::vector<float>>*       m_matchedTruthVtxReprPhysPos_x;
    std::vector<std::vector<float>>*       m_matchedTruthVtxReprPhysPos_y;
    std::vector<std::vector<float>>*       m_matchedTruthVtxReprPhysPos_z;
    std::vector<std::vector<float>>*       m_matchedTruthVtxReprPhysPos_r;
    std::vector<std::vector<float>>*       m_matchedTruthVtxReprPhysPos_phi;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_residual_x;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_residual_y;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_residual_z;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_residual_r;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_residual_phi;
    std::vector<std::vector<float>>*       m_matchedTruthVtx_residual_distance;




    // matching jets (jets to which DVs are dR-matched)
    std::vector<uint8_t>* m_truthJetMatch;
    std::vector<int>*     m_truthJetMatch_ID;
    std::vector<int>*     m_truthJetMatch_index;
    std::vector<float>*   m_truthJetMatch_dR;
    std::vector<uint8_t>* m_darkJetMatch;
    std::vector<int>*     m_darkJetMatch_ID;
    std::vector<int>*     m_darkJetMatch_index;
    std::vector<float>*   m_darkJetMatch_dR;
    std::vector<uint8_t>* m_emtopoJetMatch;
    std::vector<int>*     m_emtopoJetMatch_ID;
    std::vector<int>*     m_emtopoJetMatch_index;
    std::vector<float>*   m_emtopoJetMatch_dR;
    std::vector<uint8_t>* m_pflowJetMatch;
    std::vector<int>*     m_pflowJetMatch_ID;
    std::vector<int>*     m_pflowJetMatch_index;
    std::vector<float>*   m_pflowJetMatch_dR;

  };
  
} // EJs

#endif // EJsAnalysis_SecondaryVertexContainer_H
