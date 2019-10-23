#ifndef EJsAnalysis_EJsHelpTreeBase_H
#define EJsAnalysis_EJsHelpTreeBase_H

/* EJsHelpTreeBase is a class derived from xAODAnaHelpers's HelpTreeBase class
   that creates and fills an EJs-specific TTree; 
   the *User functions override those defined in HelpTreeBase
   to add extra branches not already included from xAODAnaHelpers */

#include <vector>
#include <string>
#include <cstdint>
#include <map>

#include <TTree.h>
#include <TFile.h>

#include <xAODEventInfo/EventInfo.h>
#include <xAODJet/JetContainer.h>
#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>
#include <xAODTruth/TruthParticleContainer.h>
#include <xAODTruth/TruthVertexContainer.h>

#include <xAODAnaHelpers/HelpTreeBase.h>

#include "EJsAnalysis/TruthVertexContainer.h"
#include "EJsAnalysis/SecondaryVertexContainer.h"
#include "EJsAnalysis/JetContainer.h"

class EJsHelpTreeBase : public HelpTreeBase
{  
 public:
  // create HelpTreeBase instance
  EJsHelpTreeBase ( xAOD::TEvent* event, TTree* tree, TFile* file, const float units = 1e3, bool debug = false,
		    xAOD::TStore* store = 0, bool emtopo = true, bool pflow = false, bool truth = false,
		    const std::vector<std::string>& truthVtxLLPs = std::vector<std::string>() );
  // standard destructor
  virtual ~EJsHelpTreeBase ();

  // branches for new EJs container objects
  void AddPV   ( );
  void FillPV  ( const xAOD::Vertex* pv, int pvLocation = -1 );
  void ClearPV ( );
  
  void AddTruthVerts   ( const std::string detailStr = "",             const std::string truthVtxName = "truthVtx" );
  void FillTruthVerts  ( const xAOD::TruthVertexContainer* truthVerts, const std::string truthVtxName = "truthVtx" );
  void FillTruthVertex ( const xAOD::TruthVertex* truthVtx,            const std::string truthVtxName = "truthVtx" );
  void ClearTruthVerts ( const std::string truthVtxName = "truthVtx"  );

  void AddSecondaryVerts   ( const std::string detailStr = "",      const std::string secVtxName = "secVtx" );
  void FillSecondaryVerts  ( const xAOD::VertexContainer* secVerts, const std::string secVtxName = "secVtx",
			     const xAOD::Vertex* pv = 0 );
  void FillSecondaryVertex ( const xAOD::Vertex* secVtx,            const std::string secVtxName = "secVtx",
			     const xAOD::Vertex* pv = 0 );
  void ClearSecondaryVerts ( const std::string secVtxName = "secVtx" );

  // new branches for existing objects
  void AddEventUser    ( const std::string detailStr = "" );
  void FillEventUser   ( const xAOD::EventInfo*           );
  void ClearEventUser  ( );
  
  void AddJetsUser     ( const std::string detailStr = "", const std::string jetName = "jet" );
  void FillJetsUser    ( const xAOD::Jet*,                 const std::string jetName = "jet" );
  void ClearJetsUser   ( const std::string /*jetName = "jet"*/                               );

  void AddTruthUser    ( const std::string truthName,     const std::string detailStr = ""   );
  void FillTruthUser   ( const std::string /*truthName*/, const xAOD::TruthParticle*         );
  void ClearTruthUser  ( const std::string /*truthName*/                                     );
  
  void AddTracksUser   ( const std::string trackName,     const std::string detailStr = ""   );
  void FillTracksUser  ( const std::string /*trackName*/, const xAOD::TrackParticle*         );
  void ClearTracksUser ( const std::string /*trackName*/                                     );


 protected:
  std::map<std::string, EJs::TruthVertexContainer*>     m_truthVerts;
  std::map<std::string, EJs::SecondaryVertexContainer*> m_secVerts;
  std::map<std::string, EJs::JetContainer*>             m_jets;

 private:
  std::string m_treeName;
  
  bool m_doEMTopoJets;
  bool m_doPFlowJets;
  bool m_truthLevelOnly;
  std::vector<std::string> m_truthVtxLLPs;
  
  // --- extra (vector) branches --- //

  // primary vertex
  float    m_pv_x;
  float    m_pv_y;
  float    m_pv_z;
  float    m_pv_r;
  float    m_pv_phi;
  int      m_pv_nTracks;
  int      m_pv_location;

  
  // event info
  Long64_t m_nTotalEvents;
  uint8_t  m_eventIsMC;
  
  uint8_t  m_signal_emtopo;
  uint8_t  m_signal_pflow;
  uint8_t  m_signal_truth;
  uint8_t  m_valid_emtopo;
  uint8_t  m_valid_pflow;
  uint8_t  m_valid_truth;
  uint8_t  m_ctrl_emtopo;
  uint8_t  m_ctrl_pflow;
  uint8_t  m_ctrl_truth;

  uint8_t  m_signalTrig;
  uint8_t  m_signalNJet_emtopo;
  uint8_t  m_signalNJet_pflow;
  uint8_t  m_signalNJet_truth;
  uint8_t  m_signalJetPt_emtopo;
  uint8_t  m_signalJetPt_pflow;
  uint8_t  m_signalJetPt_truth;
  uint8_t  m_signalJetEta_emtopo;
  uint8_t  m_signalJetEta_pflow;
  uint8_t  m_signalJetEta_truth;
  uint8_t  m_signalNJetHt_emtopo;
  uint8_t  m_signalNJetHt_pflow;
  uint8_t  m_signalNJetHt_truth;
  //uint8_t  m_signalNEJ_emtopo;
  //uint8_t  m_signalNEJ_pflow;
  uint8_t  m_signalNEJ_truth;

  uint8_t  m_validTrig;
  uint8_t  m_validNJetMin_emtopo;
  uint8_t  m_validNJetMin_pflow;
  uint8_t  m_validNJetMin_truth;
  uint8_t  m_validNJetMax_emtopo;
  uint8_t  m_validNJetMax_pflow;
  uint8_t  m_validNJetMax_truth;
  uint8_t  m_validJetPt_emtopo;
  uint8_t  m_validJetPt_pflow;
  uint8_t  m_validJetPt_truth;
  uint8_t  m_validJetEta_emtopo;
  uint8_t  m_validJetEta_pflow;
  uint8_t  m_validJetEta_truth;

  float    m_njetHt_emtopo;
  float    m_njetHt_pflow;
  float    m_njetHt_truth;

  
  // truth particles
  std::vector<int>*                      m_tp_ID;
  std::vector<int>*                      m_tp_index;
  std::vector<float>*                    m_tp_M;
  std::vector<float>*                    m_tp_charge;
  std::vector<uint8_t>*                  m_tp_isReco;
  std::vector<uint8_t>*                  m_tp_isSelected;
  std::vector<uint8_t>*                  m_tp_isAssociated;
  std::vector<float>*                    m_tp_recoProb;
  std::vector<int>*                      m_tp_recoID;
  std::vector<int>*                      m_tp_recoIndex;
  std::vector<uint8_t>*                  m_tp_isStable;
  std::vector<uint8_t>*                  m_tp_isInteracting;
  std::vector<uint8_t>*                  m_tp_isDark;
  std::vector<uint8_t>*                  m_tp_isDescendant;
  std::vector<std::vector<std::string>>* m_tp_ancestor_llpDecay;
  std::vector<std::vector<int>>*         m_tp_ancestor_ID;
  std::vector<std::vector<int>>*         m_tp_ancestor_index;
  std::vector<std::vector<int>>*         m_tp_parent_ID;
  std::vector<std::vector<int>>*         m_tp_parent_index;
  std::vector<std::vector<int>>*         m_tp_child_ID;
  std::vector<std::vector<int>>*         m_tp_child_index;
  // production vertices
  std::vector<uint8_t>*                  m_tp_pVtx;
  std::vector<std::string>*              m_tp_pVtx_llpDecay;
  std::vector<int>*                      m_tp_pVtx_ID;
  std::vector<int>*                      m_tp_pVtx_index;
  std::vector<int>*                      m_tp_pVtx_barcode;
  std::vector<float>*                    m_tp_pVtx_r;
  // decay vertices
  std::vector<uint8_t>*                  m_tp_dVtx;
  std::vector<std::string>*              m_tp_dVtx_llpDecay;
  std::vector<int>*                      m_tp_dVtx_ID;
  std::vector<int>*                      m_tp_dVtx_index;
  std::vector<int>*                      m_tp_dVtx_barcode;
  std::vector<float>*                    m_tp_dVtx_r;
  // matching jets (jets to which truth particles are dR-matched)
  std::vector<uint8_t>*                  m_tp_truthJetMatch;
  std::vector<int>*                      m_tp_truthJetMatch_ID;
  std::vector<int>*                      m_tp_truthJetMatch_index;
  std::vector<float>*                    m_tp_truthJetMatch_dR;
  std::vector<uint8_t>*                  m_tp_darkJetMatch;
  std::vector<int>*                      m_tp_darkJetMatch_ID;
  std::vector<int>*                      m_tp_darkJetMatch_index;
  std::vector<float>*                    m_tp_darkJetMatch_dR;
  std::vector<uint8_t>*                  m_tp_emtopoJetMatch;
  std::vector<int>*                      m_tp_emtopoJetMatch_ID;
  std::vector<int>*                      m_tp_emtopoJetMatch_index;
  std::vector<float>*                    m_tp_emtopoJetMatch_dR;
  std::vector<uint8_t>*                  m_tp_pflowJetMatch;
  std::vector<int>*                      m_tp_pflowJetMatch_ID;
  std::vector<int>*                      m_tp_pflowJetMatch_index;
  std::vector<float>*                    m_tp_pflowJetMatch_dR;
        
  
  // tracks
  std::vector<int>*                      m_trk_ID;
  std::vector<int>*                      m_trk_index;
  std::vector<float>*                    m_trk_M;
  std::vector<float>*                    m_trk_d0;
  std::vector<float>*                    m_trk_errd0;
  std::vector<float>*                    m_trk_errz0;
  std::vector<float>*                    m_trk_chiSquared;
  std::vector<float>*                    m_trk_numberDoF;
  std::vector<float>*                    m_trk_chi2;
  std::vector<float>*                    m_trk_charge;
  // track summary information
  std::vector<uint8_t>*                  m_trk_nPixelHits;
  std::vector<uint8_t>*                  m_trk_nPixelHoles;
  std::vector<uint8_t>*                  m_trk_nPixelSharedHits;
  std::vector<uint8_t>*                  m_trk_nPixelDeadSensors;
  std::vector<uint8_t>*                  m_trk_expectInnerPixelLayerHit;
  std::vector<uint8_t>*                  m_trk_nInnerPixelLayerHits;
  std::vector<uint8_t>*                  m_trk_expectNextInnerPixelLayerHit;
  std::vector<uint8_t>*                  m_trk_nNextInnerPixelLayerHits;
  std::vector<uint8_t>*                  m_trk_nSCTHits;
  std::vector<uint8_t>*                  m_trk_nSCTHoles;
  std::vector<uint8_t>*                  m_trk_nSCTSharedHits;
  std::vector<uint8_t>*                  m_trk_nSCTDeadSensors;
  std::vector<uint8_t>*                  m_trk_nTRTHits;
  std::vector<uint8_t>*                  m_trk_nTRTOutliers;
  // track type
  std::vector<uint8_t>*                  m_trk_isLRT;
  std::vector<uint8_t>*                  m_trk_isSelected;
  std::vector<uint8_t>*                  m_trk_isAssociated;
  std::vector<uint8_t>*                  m_trk_isTruth;
  std::vector<float>*                    m_trk_truthProb;
  std::vector<int>*                      m_trk_truthID;
  std::vector<int>*                      m_trk_truthIndex;
  std::vector<int>*                      m_trk_truthBarcode;
  std::vector<int>*                      m_trk_truthPdgId;
  std::vector<uint8_t>*                  m_trk_truthIsDesc;
  std::vector<std::vector<std::string>>* m_trk_truthAncestorLLPDecay;
  std::vector<std::vector<int>>*         m_trk_truthAncestorID;
  std::vector<std::vector<int>>*         m_trk_truthAncestorIndex;
  // corresponding secondary vertices
  std::vector<uint8_t>*                  m_trk_isSecVtxTrk;
  std::vector<uint8_t>*                  m_trk_isSecVtxCleanTrk;
  std::vector<uint8_t>*                  m_trk_isSecVtxFiltTrk;
  std::vector<uint8_t>*                  m_trk_isSecVtxFinalTrk;
  std::vector<int>*                      m_trk_secVtxID;
  std::vector<int>*                      m_trk_secVtxIndex;
  // matching jets (jets to which tracks are dR-matched)
  std::vector<uint8_t>*                  m_trk_truthJetMatch;
  std::vector<int>*                      m_trk_truthJetMatch_ID;
  std::vector<int>*                      m_trk_truthJetMatch_index;
  std::vector<float>*                    m_trk_truthJetMatch_dR;
  std::vector<uint8_t>*                  m_trk_darkJetMatch;
  std::vector<int>*                      m_trk_darkJetMatch_ID;
  std::vector<int>*                      m_trk_darkJetMatch_index;
  std::vector<float>*                    m_trk_darkJetMatch_dR;
  std::vector<uint8_t>*                  m_trk_emtopoJetMatch;
  std::vector<int>*                      m_trk_emtopoJetMatch_ID;
  std::vector<int>*                      m_trk_emtopoJetMatch_index;
  std::vector<float>*                    m_trk_emtopoJetMatch_dR;
  std::vector<uint8_t>*                  m_trk_pflowJetMatch;
  std::vector<int>*                      m_trk_pflowJetMatch_ID;
  std::vector<int>*                      m_trk_pflowJetMatch_index;
  std::vector<float>*                    m_trk_pflowJetMatch_dR;

};

#endif // EJsAnalysis_EJsHelpTreeBase_H
