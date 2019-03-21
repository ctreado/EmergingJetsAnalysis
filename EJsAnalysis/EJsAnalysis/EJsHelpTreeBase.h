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
  EJsHelpTreeBase ( xAOD::TEvent* event, TTree* tree, TFile* file, const float units = 1e3,
		    bool debug = false, xAOD::TStore* store = 0, bool emtopo = true, bool pflow = false );
  // standard destructor
  virtual ~EJsHelpTreeBase ();

  // branches for new EJs container objects
  void AddPV   ( );
  void FillPV  ( const xAOD::Vertex* pv, int pvLocation = -1 );
  void ClearPV ( );
  
  void AddTruthVerts   ( const std::string detailStr = "",             const std::string truthVtxName = "truthVtx" );
  void FillTruthVerts  ( const xAOD::TruthVertexContainer* truthVerts, const std::string truthVtxName = "truthVtx" );
  void FillTruthVertex ( const xAOD::TruthVertex* truthVtx,            const std::string truthVtxName = "truthVtx" );
  void ClearTruthVerts ( const std::string truthVtxName = "truthVtx"                                               );

  void AddSecondaryVerts   ( const std::string detailStr = "",      const std::string secVtxName = "secVtx" );
  void FillSecondaryVerts  ( const xAOD::VertexContainer* secVerts, const std::string secVtxName = "secVtx" );
  void FillSecondaryVertex ( const xAOD::Vertex* secVtx,            const std::string secVtxName = "secVtx" );
  void ClearSecondaryVerts ( const std::string secVtxName = "secVtx"                                        );

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
  
  // --- extra (vector) branches --- //

  // primary vertex
  float    m_pv_x;
  float    m_pv_y;
  float    m_pv_z;
  float    m_pv_r;
  float    m_pv_phi;
  uint32_t m_pv_nTracks;
  int      m_pv_location;

  
  // event info
  uint8_t m_eventIsMC;
  
  uint8_t m_signal_emtopo;
  uint8_t m_signal_pflow;
  uint8_t m_valid_emtopo;
  uint8_t m_valid_pflow;
  uint8_t m_ctrl_emtopo;
  uint8_t m_ctrl_pflow;

  uint8_t m_signalTrig;
  uint8_t m_signalNJet_emtopo;
  uint8_t m_signalNJet_pflow;
  uint8_t m_signalJetPt_emtopo;
  uint8_t m_signalJetPt_pflow;
  uint8_t m_signalJetEta_emtopo;
  uint8_t m_signalJetEta_pflow;
  uint8_t m_signalNJetHt_emtopo;
  uint8_t m_signalNJetHt_pflow;

  uint8_t m_validTrig;
  uint8_t m_validNJetMin_emtopo;
  uint8_t m_validNJetMin_pflow;
  uint8_t m_validNJetMax_emtopo;
  uint8_t m_validNJetMax_pflow;
  uint8_t m_validJetPt_emtopo;
  uint8_t m_validJetPt_pflow;
  uint8_t m_validJetEta_emtopo;
  uint8_t m_validJetEta_pflow;

  float m_njetHt_emtopo;
  float m_njetHt_pflow;

  uint8_t m_cleanJets_emtopo;
  uint8_t m_cleanJets_pflow;

  
  // truth particles
  std::vector<int>*     m_tp_ID;
  std::vector<float>*   m_tp_M;
  std::vector<float>*   m_tp_charge;
  std::vector<uint8_t>* m_tp_isReco;
  std::vector<float>*   m_tp_recoProb;
  std::vector<int>*     m_tp_recoID;
  std::vector<uint8_t>* m_tp_recoIsSelected;
  std::vector<uint8_t>* m_tp_recoIsAssociated;
  std::vector<uint8_t>* m_tp_isStable;
  std::vector<uint8_t>* m_tp_isInteracting;
  std::vector<uint8_t>* m_tp_isReconstructible;
  std::vector<uint8_t>* m_tp_isDark;
  
  std::vector<std::vector<int>>*     m_tp_parent_ID;
  std::vector<std::vector<uint8_t>>* m_tp_parent_isReco;
  std::vector<std::vector<float>>*   m_tp_parent_recoProb;
  std::vector<std::vector<int>>*     m_tp_parent_recoID;
  std::vector<std::vector<uint8_t>>* m_tp_parent_isStable;
  std::vector<std::vector<uint8_t>>* m_tp_parent_isInteracting;
  std::vector<std::vector<uint8_t>>* m_tp_parent_isReconstructible;
  std::vector<std::vector<uint8_t>>* m_tp_parent_isDark;

  std::vector<std::vector<int>>*     m_tp_child_ID;
  std::vector<std::vector<uint8_t>>* m_tp_child_isReco;
  std::vector<std::vector<float>>*   m_tp_child_recoProb;
  std::vector<std::vector<int>>*     m_tp_child_recoID;
  std::vector<std::vector<uint8_t>>* m_tp_child_isStable;
  std::vector<std::vector<uint8_t>>* m_tp_child_isInteracting;
  std::vector<std::vector<uint8_t>>* m_tp_child_isReconstructible;
  std::vector<std::vector<uint8_t>>* m_tp_child_isDark;
  
  // --> eventually, "isDarkPionDescendant" + "darkPionDescGeneration" (or something like that) for tp, parent, child ...

  std::vector<uint8_t>* m_tp_pVtx;
  std::vector<uint8_t>* m_tp_pVtx_isDarkPionDecay;
  std::vector<int>*     m_tp_pVtx_ID;
  std::vector<int>*     m_tp_pVtx_barcode;
  std::vector<float>*   m_tp_pVtx_r;
   
  std::vector<uint8_t>* m_tp_dVtx;
  std::vector<uint8_t>* m_tp_dVtx_isDarkPionDecay;
  std::vector<int>*     m_tp_dVtx_ID;
  std::vector<int>*     m_tp_dVtx_barcode;
  std::vector<float>*   m_tp_dVtx_r;

  std::vector<uint8_t>*            m_tp_truthJetMatch;
  std::vector<std::vector<int>>*   m_tp_truthJetMatch_ID;
  std::vector<std::vector<float>>* m_tp_truthJetMatch_dR;
  std::vector<uint8_t>*            m_tp_darkJetMatch;
  std::vector<std::vector<int>>*   m_tp_darkJetMatch_ID;
  std::vector<std::vector<float>>* m_tp_darkJetMatch_dR;
  std::vector<uint8_t>*            m_tp_emtopoJetMatch;
  std::vector<std::vector<int>>*   m_tp_emtopoJetMatch_ID;
  std::vector<std::vector<float>>* m_tp_emtopoJetMatch_dR;
  std::vector<uint8_t>*            m_tp_pflowJetMatch;
  std::vector<std::vector<int>>*   m_tp_pflowJetMatch_ID;
  std::vector<std::vector<float>>* m_tp_pflowJetMatch_dR;

  
  // tracks
  std::vector<int>*     m_trk_ID;
  std::vector<float>*   m_trk_d0;
  std::vector<float>*   m_trk_errd0;
  std::vector<float>*   m_trk_errz0;
  std::vector<float>*   m_trk_chi2;
  std::vector<uint8_t>* m_trk_isSelected;
  std::vector<uint8_t>* m_trk_isAssociated;
  uint32_t m_trk_nSelected;
  uint32_t m_trk_nAssociated;
  // --> definitely at least add info from jet class (i.e. charge, truth match, etc.)
  // --> do we want to add more info here (i.e. VSI track info) ???

};

#endif // EJsAnalysis_EJsHelpTreeBase_H
