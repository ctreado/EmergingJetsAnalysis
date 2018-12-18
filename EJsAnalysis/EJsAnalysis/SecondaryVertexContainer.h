#ifndef EJsAnalysis_SecondaryVertexContainer_H
#define EJsAnalysis_SecondaryVertexContainer_H

#include <vector>
#include <string>

#include <TTree.h>

#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>

#include "EJsAnalysis/VertexContainer.h"
#include "EJsAnalysis/EJsHelperClasses.h"

namespace EJs {

  class SecondaryVertexContainer :
    public VertexContainer < EJsHelperClasses::SecondaryVertexInfoSwitch >
  {
  public:
    SecondaryVertexContainer ( const std::string& name = "secVtx",
			       const std::string& detailStr = "",
			       float units = 1e3 );
    virtual ~SecondaryVertexContainer ();

    virtual void setTree             ( TTree* tree );
    virtual void setBranches         ( TTree* tree );
    virtual void clear               ( );
    virtual void FillSecondaryVertex ( const xAOD::Vertex* secVtx );


  private:
    
    void recordTracks        ( std::vector< const xAOD::TrackParticle* >& );
    void processDVJets       ( std::vector< const xAOD::TrackParticle* >& );
    void processClosestTruth ( const xAOD::Vertex*, std::vector< const xAOD::TrackParticle* >&,
			       const xAOD::TrackParticleContainer*, const xAOD::VertexContainer* );
    void processLinkedTruth  ( const xAOD::Vertex*, std::vector< const xAOD::TrackParticle* >&,
			       const xAOD::TrackParticleContainer*, const xAOD::VertexContainer* );

    
    // vector branches

    // do we want to save trimming info?
    // --> i.e. whether trimming was applied and values of trimming cuts... 

    // save p4 ??
    
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
    
    std::vector<float>*              m_minOneTrackRemovedMass;
    std::vector<std::vector<float>>* m_twoTracksMass;
    std::vector<std::vector<float>>* m_twoTracksMassRest;
    std::vector<std::vector<int>>*   m_twoTracksCharge;
    
    std::vector<uint32_t>*           m_ntrk;
    std::vector<uint32_t>*           m_ntrk_sel;
    std::vector<uint32_t>*           m_ntrk_assoc;

    
    // tracks
    std::vector<std::vector<float>>* m_trk_qOverP;
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

    std::vector<std::vector<int>>*      m_trk_truthPid; // pdgId of truth link
    std::vector<std::vector<uint8_t>>*  m_trk_truthIsFromClosestTV;
    std::vector<std::vector<uint8_t>>*  m_trk_truthIsFromReprTV;
    
    // --> also want to check if track's truth-link is descended from LLP
    // --> will need to account for truth pointing directly to TV/LLP or descending from...
    // --> --> i.e. trk_truthPVtxIs*TV vs trk_truthAncestorPVtxIs*TV ...
    // --> --> ... or trk_truthIsLLP vs trk_truthAncestorIsLLP
    // --> --> --> can keep singular branch for both (i.e. trk_truthIsFrom*TV or trk_truthIsLLPDesc) ...
    // --> --> --> ... and add branch holding generation of descendant, ...
    // --> --> --> ... where 0 means truth is direct child of TV/LLP, 1 is grandchild, etc.


    // jets
    // jets ... some alg that makes jets out of filtered tracks ?? probably don't need this...


    // truth
    // closest truth -----------> do matching in separate matching alg, decorate vertices accordingly,
    // "representative" truth --> ... access closest/representative truth vertices here, and fill...
    // --> still not sure how exactly we want to define this...

  };
}

#endif // EJsAnalysis_SecondaryVertexContainer_H
