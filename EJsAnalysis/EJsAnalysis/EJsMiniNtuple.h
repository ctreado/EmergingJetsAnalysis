#ifndef EJsAnalysis_EJsMiniNtuple_H
#define EJsAnalysis_EJsMiniNtuple_H

#include <EventLoop/StatusCode.h>
#include <EventLoop/Algorithm.h>
// algorithm wrapper
#include "xAODAnaHelpers/Algorithm.h"


class EJsMiniNtuple : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  float cutValue;

  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!


  // standard constructor
  EJsMiniNtuple ();

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

  // needed to distribute algorithm to workers
  ClassDef ( EJsMiniNtuple, 1 );
};

#endif // EJsAnalysis_EJsMiniNtuple_H
