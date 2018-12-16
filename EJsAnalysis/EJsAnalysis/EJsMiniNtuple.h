#ifndef EJsAnalysis_EJsMiniNtuple_H
#define EJsAnalysis_EJsMiniNtuple_H

#include <vector>
#include <string>

#include <EventLoop/StatusCode.h>
#include <EventLoop/Algorithm.h>

#include <xAODAnaHelpers/Algorithm.h>

#include <xAODRootAccess/Init.h>
#include <xAODRootAccess/TEvent.h>
#include <xAODRootAccess/TStore.h>

#include "EJsAnalysis/EJsHelpTreeBase.h"


class EJsMiniNtuple : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  bool m_outHistDir = false; // choose whether to save tree to same dir as output hists

  // parsed to bools to control which branches are filled -->
  // --> see *InfoSwitch classes in xAH::HelperClasses for details...
  std::string m_evtDetailStr             = "";
  std::string m_trigDetailStr            = "";
  std::string m_jetDetailStr             = "";
  std::string m_trigJetDetailStr         = "";
  std::string m_truthJetDetailStr        = "";
  std::string m_truthPartDetailStr       = "";
  std::string m_trackPartDetailStr       = "";
  std::string m_truthVertexDetailStr     = "";
  std::string m_secondaryVertexDetailStr = "";

  // input containers
  std::string m_jetContainerName             = "";
  std::string m_trigJetContainerName         = "";
  std::string m_truthJetContainerName        = "";
  std::string m_truthPartContainerName       = "";
  std::string m_trackPartContainerName       = "";
  std::string m_truthVertexContainerName     = "";
  std::string m_secondaryVertexContainerName = "";

  // input branch names
  std::string m_jetBranchName             = "";
  std::string m_trigJetBranchName         = "";
  std::string m_truthJetBranchName        = "";
  std::string m_truthPartBranchName       = "";
  std::string m_trackPartBranchName       = "";
  std::string m_truthVertexBranchName     = "";
  std::string m_secondaryVertexBranchName = "";

  bool m_retrievePV = true;

  // systematics being processed over
  std::string m_systsVec = ""; // consider adding separate strings for separate objects

  // unit conversion from MeV; default is GeV
  float m_units = 1e3;
  

  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

  xAOD::TEvent* m_event; //!
  xAOD::TStore* m_store; //!


 protected:
  std::vector<std::string> m_jetDetails; //!
  std::vector<std::string> m_trigJetDetails; //!
  std::vector<std::string> m_truthJetDetails; //!
  
  std::vector<std::string> m_jetContainers; //!
  std::vector<std::string> m_trigJetContainers; //!
  std::vector<std::string> m_truthJetContainers; //!
  
  std::vector<std::string> m_jetBranches; //!
  std::vector<std::string> m_trigJetBranches; //!
  std::vector<std::string> m_truthJetBranches; //!

  std::map< std::string, EJsHelpTreeBase* > m_trees; //!


 public:

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

  virtual EL::StatusCode addTree ( std::string syst = "" );
  virtual EL::StatusCode executeSyst ( std::string syst = "" );

  // needed to distribute algorithm to workers
  ClassDef ( EJsMiniNtuple, 1 );
};

#endif // EJsAnalysis_EJsMiniNtuple_H
