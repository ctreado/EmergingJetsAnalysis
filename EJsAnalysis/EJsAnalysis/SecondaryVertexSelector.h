#ifndef EJsAnalysis_SecondaryVertexSelector_H
#define EJsAnalysis_SecondaryVertexSelector_H

/* SecondaryVertexSelector is the algorithm responsible for
   selecting secondary vertices (primarily using the VsiBonsai toolkit);
   based on xAODAnaHelpers' *Selector algorithms */

// --> IMPLEMENT VSI-BONSAI TRACK FILTERING (add config variables)
// --> ADD SKELETON FOR MATERIAL MAP CUTS (w/ config variables)

#include <string>

#include <xAODTracking/Vertex.h>

#include <xAODAnaHelpers/Algorithm.h>


class SecondaryVertexSelector : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  // do cutflow

  std::string m_inContainerName  = "VrtSecInclusive_SecondaryVertices";
  std::string m_outContainerName = "FilteredSecondaryVertices";

  bool m_decorateSelectedObjects = true;
  bool m_createSelectedContainer = true; // false

  // vertex cuts...


  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!
  

  // standard constructor
  SecondaryVertexSelector ();

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

  virtual int PassCuts ( const xAOD::Vertex* vtx ); // may need pv too

  //needed to distribute algorithm to workers
  ClassDef ( SecondaryVertexSelector, 1 );
};

#endif // EJsAnalysis_SecondaryVertexSelector_H
