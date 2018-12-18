#ifndef EJsAnalysis_EJsHelpTreeBase_H
#define EJsAnalysis_EJsHelpTreeBase_H

#include <vector>
#include <string>
#include <cstdint>
#include <map>

#include <TTree.h>
#include <TFile.h>

#include <xAODAnaHelpers/HelpTreeBase.h>

#include <xAODEventInfo/EventInfo.h>
#include <xAODJet/JetContainer.h>
#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>
#include <xAODTruth/TruthParticleContainer.h>
#include <xAODTruth/TruthVertexContainer.h>

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
  void FillPV  ( const xAOD::Vertex* pv );
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
  void AddJetsUser   ( const std::string detailStr = "", const std::string jetName = "jet" );
  void FillJetsUser  ( const xAOD::Jet*,                 const std::string jetName = "jet" );
  void ClearJetsUser ( const std::string jetName = "jet"                                   );
  
  void AddTracksUser   ( const std::string trackName,     const std::string detailStr = "" );
  void FillTracksUser  ( const std::string /*trackName*/, const xAOD::TrackParticle*       );
  void ClearTracksUser ( const std::string /*trackName*/                                   );


 protected:
  std::map<std::string, EJs::TruthVertexContainer*>     m_truthVerts;
  std::map<std::string, EJs::SecondaryVertexContainer*> m_secVerts;


 private:
  // extra (vector) branches

  // primary vertex
  float    m_x;
  float    m_y;
  float    m_z;
  float    m_r;
  float    m_phi;
  uint32_t m_nTracks;
  

  // tracks
  std::vector<float>*   m_d0;
  std::vector<float>*   m_errd0;
  std::vector<float>*   m_errz0;
  std::vector<float>*   m_chi2;
  std::vector<uint8_t>* m_isSelected;
  std::vector<uint8_t>* m_isAssociated;
  uint32_t m_nSelected;
  uint32_t m_nAssociated;

};

#endif // EJsAnalysis_EJsHelpTreeBase_H
