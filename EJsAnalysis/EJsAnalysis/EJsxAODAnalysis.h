#ifndef EJsAnalysis_EJsxAODAnalysis_H
#define EJsAnalysis_EJsxAODAnalysis_H

#include <EventLoop/StatusCode.h>
#include <EventLoop/Algorithm.h>

#include <xAODAnaHelpers/Algorithm.h>

#include <xAODRootAccess/Init.h>
#include <xAODRootAccess/TEvent.h>
#include <xAODRootAccess/TStore.h>


class EJsxAODAnalysis : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  // input type - from xAOD or xAODAnaHelper Algo output
  std::string m_inputAlgo = "";
  // output type - how vector<string> w/ syst names saved in TStore
  std::string m_outputAlgo = "";
  

  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

  xAOD::TEvent* m_event; //!
  xAOD::TStore* m_store; //!


  // standard constructor
  EJsxAODAnalysis ();

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

  virtual EL::StatusCode executeSyst ( std::string syst = "" );

  // needed to distribute algorithm to workers
  ClassDef ( EJsxAODAnalysis, 1 );
};

#endif // EJsAnalysis_EJsxAODAnalysis_H
