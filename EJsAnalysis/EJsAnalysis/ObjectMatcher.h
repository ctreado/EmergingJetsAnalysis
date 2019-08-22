#ifndef EJsAnalysis_ObjectMatcher_H
#define EJsAnalysis_ObjectMatcher_H

/* ObjectMatcher is the algorithm responsible for matching between 
   physics objects, including truth-matching; note: truth-reco vertex
   matching is done in a separate algorithm */

#include <string>
#include <vector>

#include <xAODJet/JetContainer.h>
#include <xAODTruth/TruthParticleContainer.h>
#include <xAODTracking/TrackParticleContainer.h>

#include <xAODAnaHelpers/Algorithm.h>


class ObjectMatcher : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  // input container names
  
  std::string m_inTruthJetContainerName        = "AntiKt4TruthJets";
  std::string m_inTruthDarkJetContainerName    = "AntiKt4TruthDarkJets";
  std::string m_inJetContainerName             = "";
  std::string m_inTruthPartContainerName       = "TruthParticles";
  std::string m_inTrackPartContainerName       = "";
  std::string m_inTruthVertexContainerName     = "TruthVertices";
  std::string m_inSecondaryVertexContainerName = "";

  // input type (from xAOD or xAH/EJs alg output) -- vector of syst names to run over
  std::string m_inputAlgo = "";

  // index of jet container to run systematics over
  unsigned m_jetSystsContainerIndex = 0;

  // object matching criteria
  double m_jet_matchRadius     = 0.1; // truth-jet matching dR
  double m_jet_vtx_matchRadius = 0.4; // jet-vertex matching dR --> 0.6 ?? 1.0 ??
  double m_jet_trk_matchRadius = 0.4; // jet-track matching dR  --> 0.6 ?? 1.0 ??

  // do truth-track matching
  bool m_doTruthTrackMatching = true;

  // protection when running on truth derivation
  bool m_truthLevelOnly = false;

  // protection when running on samples w/o truth (dark) jets
  bool m_haveTruthJets = true;
  bool m_haveDarkJets  = true;


  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

 protected:
  std::vector<std::string> m_inJetContainers; //!

  private:
  int m_eventNumber; //!
  enum jetType { RECO, TRUTH, DARK }; //!

  
 public:
  // standard constructor
  ObjectMatcher ();

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
  void matchTracksToTruthParts ( const xAOD::TruthParticleContainer*, const xAOD::TrackParticleContainer* );
  void matchSecVertsToTracks   ( const xAOD::TrackParticleContainer*, const xAOD::VertexContainer*        );

  void matchTruthJets          ( const xAOD::JetContainer*, const xAOD::JetContainer*,
				 const enum jetType&,       const enum jetType&,
				 std::string );

  void matchTruthVertsToJets   ( const xAOD::JetContainer*, const xAOD::TruthVertexContainer*,
				 const enum jetType&,       const std::string );
  void matchSecVertsToJets     ( const xAOD::JetContainer*, const xAOD::VertexContainer*,
				 const enum jetType&,       const std::string );
  void matchTruthPartsToJets   ( const xAOD::JetContainer*, const xAOD::TruthParticleContainer*,
				 const enum jetType&,       const std::string );
  void matchTracksToJets       ( const xAOD::JetContainer*, const xAOD::TrackParticleContainer*,
				 const enum jetType&,       const std::string );

  // needed to distribute algorithm to workers
  ClassDef ( ObjectMatcher, 1 );
};

#endif // EJsAnalysis_ObjectMatcher_H
