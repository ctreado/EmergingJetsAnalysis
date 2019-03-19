#ifndef EJsAnalysis_EJsNtupleToHists_H
#define EJsAnalysis_EJsNtupleToHists_H

/* EJsMiniNtuple is the algorithm responsible for histogram-making;
   the algorithm runs over a tree (the output EJsMiniNtuple from the ntuple-making alg)
   and books, fills, and outputs histograms using the EJsHistogramManager class;
   NOTE: unlike the tree-making alg, this alg can only handle one reco jet collection at a time;
   to histogram multiple reco jet collections, re-run the job with a different input jet branch name
   (can also turn off redundant histograms with 'do_jet_histos_only' info switch) */

#include <string>

#include <xAODAnaHelpers/Algorithm.h>

#include "EJsAnalysis/EJsHistogramManager.h"
#include "EJsAnalysis/EJsHelperFunctions.h"


class EJsNtupleToHists : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  // in container name, detail string

  // info switches
  std::string m_detailStr = "";

  // regions to run over
  std::string m_regionName = "";

  // input branch names
  std::string m_jetBranchName             = "";
  std::string m_trigJetBranchName         = "";
  std::string m_truthJetBranchName        = "";
  std::string m_truthDarkJetBranchName    = "";
  std::string m_truthPartBranchName       = "";
  std::string m_trackPartBranchName       = "";
  std::string m_truthVertexBranchName     = "";
  std::string m_secondaryVertexBranchName = "";

  // unit conversion from MeV; default is GeV
  float m_units = 1e3;


  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

 protected:
  std::vector<std::string>       m_regionNames; //!
  std::vector<EJsHelper::Region> m_regions;     //!
  
  EJsHistogramManager* m_plots = 0; //!

  int m_eventNumber; //!
  bool m_isMC;       //!

  
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
