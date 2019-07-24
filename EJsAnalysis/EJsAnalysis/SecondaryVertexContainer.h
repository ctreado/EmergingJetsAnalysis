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
    void processCloseTruth   ( const xAOD::Vertex*, const std::vector<const xAOD::TrackParticle*>& );
    void processLinkedTruth  ( const xAOD::Vertex*, const std::vector<const xAOD::TrackParticle*>& );

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
    
    std::vector<float>*              m_minOneTrackRemovedMass;
    std::vector<std::vector<float>>* m_twoTracksMass;
    std::vector<std::vector<float>>* m_twoTracksMassRest;
    std::vector<std::vector<int>>*   m_twoTracksCharge;
    
    std::vector<uint32_t>*           m_ntrk;
    std::vector<uint32_t>*           m_ntrk_sel;
    std::vector<uint32_t>*           m_ntrk_assoc;

    
    // tracks
    std::vector<std::vector<int>>*   m_trk_ID;
    std::vector<std::vector<int>>*   m_trk_index;
    std::vector<std::vector<float>>* m_trk_qOverP;
    std::vector<std::vector<float>>* m_trk_theta;
    std::vector<std::vector<float>>* m_trk_vz;
    std::vector<std::vector<float>>* m_trk_E;
    std::vector<std::vector<float>>* m_trk_M;
    std::vector<std::vector<float>>* m_trk_pt;
    std::vector<std::vector<float>>* m_trk_eta;
    std::vector<std::vector<float>>* m_trk_phi;
    std::vector<std::vector<float>>* m_trk_d0;
    std::vector<std::vector<float>>* m_trk_z0;
    std::vector<std::vector<float>>* m_trk_errd0;
    std::vector<std::vector<float>>* m_trk_errz0;
    std::vector<std::vector<float>>* m_trk_chi2;

    std::vector<std::vector<float>>* m_trk_pt_wrtSV;
    std::vector<std::vector<float>>* m_trk_eta_wrtSV;
    std::vector<std::vector<float>>* m_trk_phi_wrtSV;
    std::vector<std::vector<float>>* m_trk_d0_wrtSV;
    std::vector<std::vector<float>>* m_trk_z0_wrtSV;
    std::vector<std::vector<float>>* m_trk_errd0_wrtSV;
    std::vector<std::vector<float>>* m_trk_errz0_wrtSV;
    std::vector<std::vector<float>>* m_trk_errP_wrtSV;
    std::vector<std::vector<float>>* m_trk_chi2_toSV;

    std::vector<std::vector<int>>*      m_trk_charge;
    std::vector<std::vector<uint8_t>>*  m_trk_isFinal;
    std::vector<std::vector<uint8_t>>*  m_trk_isSelected;
    std::vector<std::vector<uint8_t>>*  m_trk_isAssociated;
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

    
    // jets
    // jets ... some alg that makes jets out of filtered tracks ?? probably don't need this...


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
