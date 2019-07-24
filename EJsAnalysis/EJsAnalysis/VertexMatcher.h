#ifndef EJsAnalysis_VertexMatcher_H
#define EJsAnalysis_VertexMatcher_H

/* VertexMatcher is the algorithm responsible for matching between 
   truth and reco secondary vertices */

#include <string>
#include <vector>

#include <xAODTruth/TruthVertexContainer.h>
#include <xAODTracking/VertexContainer.h>

#include <xAODAnaHelpers/Algorithm.h>


class VertexMatcher : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  // input container names
  std::string m_inTruthVertexContainerName     = "TruthVertices";
  std::string m_inSecondaryVertexContainerName = "";

  // truth vertex llp decay types to process
  std::string m_truthLLP = "DarkPion";

  // reco-truth vertex "close-matching" distance
  double m_vtx_matchDistance = 5.0;

  // do llp-decay truth vertex filtering?
  bool m_filterTruthVertex_llp = true;


  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

 private:
  std::vector<std::string> m_truthLLP_decays; //!
  
  int m_eventNumber; //!


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
  void matchClosestVerts ( const xAOD::VertexContainer*, const xAOD::TruthVertexContainer* );

  // needed to distribute algorithm to workers
  ClassDef ( VertexMatcher, 1 );
};

#endif // EJsAnalysis_VertexMatcher
