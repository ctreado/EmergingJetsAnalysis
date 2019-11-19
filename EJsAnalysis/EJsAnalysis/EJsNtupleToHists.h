#ifndef EJsAnalysis_EJsNtupleToHists_H
#define EJsAnalysis_EJsNtupleToHists_H

/* EJsMiniNtuple is the algorithm responsible for histogram-making;
   the algorithm runs over a tree (the output EJsMiniNtuple from the ntuple-making alg)
   and books, fills, and outputs histograms using the EJsHistogramManager class;
   NOTE: unlike the tree-making alg, this alg can only handle one reco jet collection at a time;
   to histogram multiple reco jet collections, re-run the job with a different input jet branch name */

#include <vector>
#include <string>
#include <map>

#include <xAODAnaHelpers/Algorithm.h>

#include "EJsAnalysis/EJsHistogramManager.h"
#include "EJsAnalysis/EJsHelperFunctions.h"
#include "EJsAnalysis/AlgConsts.h"


class EJsNtupleToHists : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  // histogram info switches
  std::string m_detailStr = "";

  // regions to num over
  std::string m_regionName = "";

  // input branch names
  std::string m_jetBranchName             = "";
  std::string m_otherJetBranchName        = "";
  std::string m_trigJetBranchName         = "";
  std::string m_truthJetBranchName        = "";
  std::string m_truthDarkJetBranchName    = "";
  std::string m_truthPartBranchName       = "";
  std::string m_trackPartBranchName       = "";
  std::string m_truthVertexBranchName     = "";
  std::string m_secondaryVertexBranchName = "";

  // jet-type string (used in event-info branch labels)
  std::string m_jetStr = "EMTopo";

  // output histogram names
  std::string m_jetHistoName             = "";
  std::string m_otherJetHistoName        = "";
  std::string m_trigJetHistoName         = "";
  std::string m_truthJetHistoName        = "";
  std::string m_truthDarkJetHistoName    = "";
  std::string m_truthPartHistoName       = "";
  std::string m_trackPartHistoName       = "";
  std::string m_truthVertexHistoName     = "";
  std::string m_secondaryVertexHistoName = "";

  bool  m_truthLevelOnly = false;
  bool  m_unblind        = false;
  float m_lumi           = 139.; // integrated luminosity to scale to (i.e. full Run2 delivered = 139) [ifb]

  // protect against nonexistent branches
  bool m_doEventInfo         = true;
  bool m_doTriggers          = true;
  bool m_doJets              = true;
  bool m_doOtherJets         = true;
  bool m_doTrigJets          = true;
  bool m_doTruthJets         = true;
  bool m_doTruthDarkJets     = true;
  bool m_doTracks            = true;
  bool m_doTruthParts        = true;
  bool m_doSecondaryVertices = true;
  bool m_doTruthVertices     = true;


  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

 protected:
  std::vector<std::string>       m_regionNames; //!
  std::vector<EJsHelper::Region> m_regions;     //!
  
  EJsHistogramManager* m_plots = 0; //!
  
  int   m_eventNumber;                            //!
  bool  m_isMC;                                   //!
  float m_nEvents_init = AlgConsts::invalidFloat; //! // initial number of events before daod skimming
  float m_nEvents_sel  = AlgConsts::invalidFloat; //! // initial number of events after daod skimming
  float m_sumw_init    = AlgConsts::invalidFloat; //! // sum of weights before skimming
  float m_sumw_sel     = AlgConsts::invalidFloat; //! // sum of weights after skimming
  float m_sumw2_init   = AlgConsts::invalidFloat; //! // sum of weights squared before skimming
  float m_sumw2_sel    = AlgConsts::invalidFloat; //! // sum o weights squared after skimming
  float m_crossSection = AlgConsts::invalidFloat; //! // [nb]
  float m_kFactor      = AlgConsts::invalidFloat; //!
  float m_genFilterEff = AlgConsts::invalidFloat; //!
  std::map<std::string, float> m_metadata;        //!
  
  
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
