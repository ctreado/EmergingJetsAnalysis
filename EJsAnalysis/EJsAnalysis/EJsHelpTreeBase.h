#ifndef EJsAnalysis_EJsHelpTreeBase_H
#define EJsAnalysis_EJsHelpTreeBase_H

#include <string>

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


  // branches for new objects not covered in xAODAnaHelpers
  void AddTruthVerts     ( const std::string truthVtxName = "truthVtx" );
  void AddSecondaryVerts ( const std::string secVtxName   = "secVtx" );

  void FillTruthVerts  ( const xAOD::TruthVertexContainer* truthVerts,
			 const std::string truthVtxName = "truthVtx" );
  void FillTruthVertex ( const xAOD::TruthVertex* truthVtx,
			 const std::string truthVtxName = "truthVtx" );

  void FillSecondaryVerts  ( const xAOD::VertexContainer* secVerts,
			     const std::string secVtxName = "secVtx" );
  void FillSecondaryVertex ( const xAOD::Vertex* secVtx,
			     const std::string secVtxName = "secVtx" );

  void ClearTruthVerts     ( const std::string truthVtxName = "truthVtx" );
  void ClearSecondaryVerts ( const std::string secVtxName   = "secVtx" );

  
  // new branches for existing objects
  void AddJetsUser   ( const std::string detailStr = "", const std::string jetName = "jet" );
  //void AddTracksUser ( const std::string trackName,      const std::string detailStr = "" );

  void FillJetsUser   ( const xAOD::Jet*, const std::string jetName = "jet" );
  //void FillTracksUser ( const std::string /*trackName*/, const xAOD::TrackParticle* );
  
  void ClearJetsUser   ( const std::string jetName = "jet" );
  //void ClearTracksUser ( const std::string /*trackName*/ );


 protected:
  std::map<std::string, EJs::TruthVertexContainer*>     m_truthVerts;
  std::map<std::string, EJs::SecondaryVertexContainer*> m_secVerts;


 private:
  // vector branches
  std::vector<int>* m_jet_exists;

};

#endif // EJsAnalysis_EJsHelpTreeBase_H
