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
  EJsHelpTreeBase ( xAOD::TEvent* event, TTree* tree, TFile* file,
		    const float units = 1e3, bool debug = false, xAOD::TStore* store = 0 );
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
  // extra (vector) branches

  // primary vertex
  float    m_pv_x;
  float    m_pv_y;
  float    m_pv_z;
  float    m_pv_r;
  float    m_pv_phi;
  uint32_t m_pv_nTracks;
  int      m_pv_location;

  // event info
  char m_signal_emtopo;
  char m_signal_pflow;
  char m_valid_emtopo;
  char m_valid_pflow;
  char m_ctrl_emtopo;
  char m_ctrl_pflow;

  char m_signalTrig;
  char m_signalNJet_emtopo;
  char m_signalNJet_pflow;
  char m_signalJetPt_emtopo;
  char m_signalJetPt_pflow;
  char m_signalJetEta_emtopo;
  char m_signalJetEta_pflow;
  char m_signalNJetHt_emtopo;
  char m_signalNJetHt_pflow;

  char m_validTrig;
  char m_validNJetMin_emtopo;
  char m_validNJetMin_pflow;
  char m_validNJetMax_emtopo;
  char m_validNJetMax_pflow;
  char m_validJetPt_emtopo;
  char m_validJetPt_pflow;
  char m_validJetEta_emtopo;
  char m_validJetEta_pflow;

  // truth particles
  std::vector<int>*   m_tp_ID;
  std::vector<float>* m_tp_M;
  // charge, isReco, recoProb, recoID, recoIsSelected, recoIsAssociated
  // isDarkPion, isStable, isInteracting (?)
  // charge, pt, eta, phi, E, M, ID, isReco, recoProb, recoID, recoIsSelected, recoIsAssociated of parents / children
  // --> eventually, "isDarkPionDescendant" + "darkPionDescGeneration" (or something like that)
  // production, decay vertices (basics - ID, barcode, isDarkPionDecay, x, y, z, r
  
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
