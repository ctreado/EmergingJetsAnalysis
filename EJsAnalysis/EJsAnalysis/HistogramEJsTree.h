#ifndef EJsAnalysis_HistogramEJsTree_H
#define EJsAnalysis_HistogramEJsTree_H

#include <EventLoop/StatusCode.h>
#include <EventLoop/Algorithm.h>

#include <xAODAnaHelpers/Algorithm.h>

#include "TH1.h"


class HistogramEJsTree : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;
  

  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!


 private:

  // branches
  std::vector<float>* m_jet_pt; //!

  // histograms
  TH1F* h_jet_pt; //!

  
 public:
  // standard constructor
  HistogramEJsTree ();

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
  ClassDef ( HistogramEJsTree, 1 );
};

#endif // EJsAnalysis_HistogramEJsTree_H
