#ifndef EJsAnalysis_VertexMatcher_H
#define EJsAnalysis_VertexMatcher_H

/* VertexMatcher is the algorithm responsible for matching between 
   truth and reco secondary vertices */

#include <string>
#include <vector>
#include <set>
#include <unordered_map>

#include <xAODTruth/TruthVertexContainer.h>
#include <xAODTracking/VertexContainer.h>

#include <xAODAnaHelpers/Algorithm.h>

#include "EJsAnalysis/AlgConsts.h"


class VertexMatcher : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  // input container names
  std::string m_inTruthPartContainerName       = "TruthParticles";
  std::string m_inTrackPartContainerName       = "";
  std::string m_inTruthVertexContainerName     = "TruthVertices";
  std::string m_inSecondaryVertexContainerName = "";

  // truth vertex llp decay types to process
  std::string m_truthLLP = "DarkPion";

  // do llp-decay truth vertex filtering?
  bool m_filterTruthVertex_llp  = true;
  // apply cut on truth vertex outside fiducial volume?
  bool m_applyFiducialVolumeCut = true;
  
  // recursively trace LLP decay chain?
  bool  m_doRecursive    = true;
  // max particle production-decay distance for recursive trace
  float m_distanceCutoff = 10.0;
  // min reconstructible particle pt
  float m_ptThreshold    = 1e3;

  // reco-truth vertex match score
  float m_vtx_matchScore = 0.5;
  float m_vtx_residual   = AlgConsts::maxValue; // 10.0 ??

  // do truth-track matching
  bool m_doTruthTrackMatching = true;

  // set object identifiers
  bool m_setObjectIdentifiers = true;
  


  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

 private:
  std::vector<std::string> m_truthLLP_decays; //!
  
  int m_eventNumber; //!
  std::unordered_map<const xAOD::TruthParticle*, const xAOD::TrackParticle*> m_truthTrackHash; //!


 public:
  // standard constructor
  VertexMatcher ();

  // functions inherited from Algorithm
  virtual EL::StatusCode setupJob ( EL::Job& job );
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput ( bool firstFile );
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // added functions not from Algorithm
  void collectReconstructibleDescendants ( const xAOD::TruthVertex*,            std::set<const xAOD::TruthParticle*>& );
  void matchTracksToTruthParts           ( const xAOD::TruthParticleContainer*, const xAOD::TrackParticleContainer*   );

  // needed to distribute algorithm to workers
  ClassDef ( VertexMatcher, 1 );
};

#endif // EJsAnalysis_VertexMatcher
