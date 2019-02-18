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
  
  void AddTruthVerts   ( const std::string detailStr = "",
			 const std::string truthVtxName = "truthVtx" );
  void FillTruthVerts  ( const xAOD::TruthVertexContainer* truthVerts,
			 const std::string truthVtxName = "truthVtx" );
  void FillTruthVertex ( const xAOD::TruthVertex* truthVtx,
			 const std::string truthVtxName = "truthVtx" );
  void ClearTruthVerts ( const std::string truthVtxName = "truthVtx" );

  void AddSecondaryVerts   ( const std::string detailStr = "",
			     const std::string secVtxName = "secVtx" );
  void FillSecondaryVerts  ( const xAOD::VertexContainer* secVerts,
			     const std::string secVtxName = "secVtx" );
  void FillSecondaryVertex ( const xAOD::Vertex* secVtx,
			     const std::string secVtxName = "secVtx" );
  void ClearSecondaryVerts ( const std::string secVtxName = "secVtx" );

  // new branches for existing objects

  // event user ...
  
  void AddJetsUser   ( const std::string detailStr = "", const std::string jetName = "jet" );
  void FillJetsUser  ( const xAOD::Jet*,                 const std::string jetName = "jet" );
  void ClearJetsUser ( const std::string jetName = "jet"                                   );
  // --> add jet-constituents
  
  void AddTracksUser   ( const std::string trackName,     const std::string detailStr = "" );
  void FillTracksUser  ( const std::string /*trackName*/, const xAOD::TrackParticle*       );
  void ClearTracksUser ( const std::string /*trackName*/                                   );

  // truth user ...

 protected:
  std::map<std::string, EJs::TruthVertexContainer*>     m_truthVerts;
  std::map<std::string, EJs::SecondaryVertexContainer*> m_secVerts;

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
  
  // tracks
  std::vector<float>*   m_trk_d0;
  std::vector<float>*   m_trk_errd0;
  std::vector<float>*   m_trk_errz0;
  std::vector<float>*   m_trk_chi2;
  std::vector<uint8_t>* m_trk_isSelected;
  std::vector<uint8_t>* m_trk_isAssociated;
  uint32_t m_trk_nSelected;
  uint32_t m_trk_nAssociated;

};

#endif // EJsAnalysis_EJsHelpTreeBase_H
