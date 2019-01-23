#ifndef EJsAnalysis_EJsNtupleToHists_H
#define EJsAnalysis_EJsNtupleToHists_H

/* EJsMiniNtuple is the algorithm responsible for histogram-making;
   the algorithm runs over a tree (the output EJsMiniNtuple from the ntuple-making alg)
   and books, fills, and outputs histograms using the EJsHistogramManager class */

#include <string>

#include <xAODAnaHelpers/Algorithm.h>

#include "EJsAnalysis/EJsHistogramManager.h"


class EJsNtupleToHists : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  // in container name, detail string

  // info switches
  std::string m_detailStr = "";
  std::string m_secondaryVertexDetailStr = "";

  // input branch names
  std::string m_secondaryVertexBranchName = "";

  // unit conversion from MeV; default is GeV
  float m_units = 1e3;


  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!


 private:
  EJsHistogramManager* m_plots = 0; //!


 public:

  // standard constructor
  EJsNtupleToHists ();

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
  ClassDef ( EJsNtupleToHists, 1 );
};

#endif // EJsAnalysis_EJsNtupleToHists_H
