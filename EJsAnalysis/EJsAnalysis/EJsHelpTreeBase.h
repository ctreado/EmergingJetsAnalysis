#ifndef EJsAnalysis_EJsHelpTreeBase_H
#define EJsAnalysis_EJsHelpTreeBase_H

#include "xAODAnaHelpers/HelpTreeBase.h"

class EJsHelpTreeBase : public HelpTreeBase
{

 private:
  std::vector<int>* b_jet_exists;

  
 public:

  // create HelpTreeBase instance
  EJsHelpTreeBase ( xAOD::TEvent* event, TTree* tree, TFile* file,
		    const float units = 1e3, bool debug = false, xAOD::TStore* store = 0 );
  EJsHelpTreeBase ( TTree* tree, TFile* file, xAOD::TEvent* event = 0,
		    xAOD::TStore* store = 0, const float units = 1e3, bool debug = false );
  // standard destructor
  virtual ~EJsHelpTreeBase ();

  // connect branches for jet-level variables
  void AddJetsUser   ( const std::string detailStr = "", const std::string jetName = "jet" );
  // fill TTree with jet-level variables
  void FillJetsUser  ( const xAOD::Jet*, const std::string jetName = "jet" );
  // clear vectors used by jet-level variables
  void ClearJetsUser ( const std::string jetName = "jet" );

};

#endif // EJsAnalysis_EJsHelpTreeBase_H
