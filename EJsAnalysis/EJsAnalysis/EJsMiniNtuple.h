#ifndef EJsAnalysis_EJsMiniNtuple_H
#define EJsAnalysis_EJsMiniNtuple_H

#include <EventLoop/StatusCode.h>
#include <EventLoop/Algorithm.h>

#include <xAODAnaHelpers/Algorithm.h>
#include <xAODAnaHelpers/HelpTreeBase.h>

#include <xAODRootAccess/Init.h>
#include <xAODRootAccess/TEvent.h>
#include <xAODRootAccess/TStore.h>

#include "TTree.h"


class EJsMiniNtuple : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  bool m_outHistDir = false; // choose whether to save tree to same dir as output hists

  // parsed to bools to control which branches are filled -->
  // --> see *InfoSwitch classes in xAH::HelperClasses for details...
  std::string m_evtDetailStr = "";
  std::string m_trigDetailStr = "";
  std::string m_jetDetailStr = "";

  // input containers
  std::string m_jetContainerName = "";
  std::string m_jetBranchName = "";

  bool m_retrievePV = true;

  // systematics being processed over (empty string 
  std::string m_systsVec = "";
  

  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

  xAOD::TEvent *m_event; //!
  xAOD::TStore *m_store; //!


 protected:
  std::map< std::string, HelpTreeBase* > m_trees; //!
  
  std::vector<std::string> m_jetDetails; //!
  std::vector<std::string> m_jetContainers; //!
  std::vector<std::string> m_jetBranches; //!


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
