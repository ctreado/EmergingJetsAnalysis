#ifndef EJsAnalysis_ObjectMatcher_H
#define EJsAnalysis_ObjectMatcher_H

/* ObjectMatcher is the algorithm responsible for matching between 
   physics objects, including truth-matching */

#include <string>
#include <vector>

#include <xAODJet/JetContainer.h>
#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>
#include <xAODTruth/TruthParticleContainer.h>
#include <xAODTruth/TruthVertexContainer.h>

#include <xAODAnaHelpers/Algorithm.h>


class ObjectMatcher : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  // input container names
  std::string m_inJetContainerName             = "";
  std::string m_inTruthJetContainerName        = "AntiKt4TruthJets";
  std::string m_inTruthDarkJetContainerName    = "AntiKt4TruthDarkJets";
  std::string m_inTruthPartContainerName       = "TruthParticles";
  std::string m_inTrackPartContainerName       = "";
  std::string m_inTruthVertexContainerName     = "TruthVertices";
  std::string m_inSecondaryVertexContainerName = "";

  // input type (from xAOD or xAH/EJs alg output) -- vector of syst names to run over
  std::string m_inputAlgo = "";

  // index of jet container to run systematics over
  unsigned m_jetSystsContainerIndex = 0;

  // truth - jet dR-matching radius
  double m_jet_matchRadius = 0.1;
  // truth - vertex matching distance
  double m_vtx_matchDist   = 5.0;


  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!
 
 protected:
  std::vector<std::string> m_inJetContainers; //!

  
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
  void matchTruthJets        ( const xAOD::JetContainer*, const xAOD::JetContainer*,
			       const std::string,         bool matchJetIsDark = false );

  void matchTruthVertsToJets ( const xAOD::JetContainer*, const xAOD::TruthVertexContainer* );
  void matchSecVertsToJets   ( const xAOD::JetContainer*, const xAOD::VertexContainer* );

  void matchTruthPartsToJets ( const xAOD::JetContainer*, const xAOD::TruthParticleContainer* );
  void matchTracksToJets     ( const xAOD::JetContainer*, const xAOD::TrackParticleContainer* );

  void matchTracksToTruthParts ( const xAOD::TruthParticleContainer*, const xAOD::TrackParticleContainer* );

  void matchCloseTruthToSecVerts  ( const xAOD::VertexContainer*, const xAOD::TruthVertexContainer* );
  void matchLinkedTruthToSecVerts ( const xAOD::VertexContainer*, const xAOD::TruthVertexContainer* );

  // reco to truth vertex matching (see VsiPerf efficiency processor) ...

  // needed to distribute algorithm to workers
  ClassDef ( ObjectMatcher, 1 );
};

#endif // EJsAnalysis_ObjectMatcher_H