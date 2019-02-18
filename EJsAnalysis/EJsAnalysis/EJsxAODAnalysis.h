#ifndef EJsAnalysis_EJsxAODAnalysis_H
#define EJsAnalysis_EJsxAODAnalysis_H

/* EJsxAODAnalysis is the algorithm responsible for final EJs analysis selection
   and EJs observable, object, and signal/control/validation region definition/calculation */

#include <string>
#include <vector>

#include <TH1.h>

#include <xAODEventInfo/EventInfo.h>
#include <xAODJet/JetContainer.h>

#include <xAODAnaHelpers/Algorithm.h>


class EJsxAODAnalysis : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  bool m_useCutFlow = true;

  // input container names
  std::string m_inJetContainerName = "";

  // output histogram bin names
  std::string m_inJetBinName = "";

  // input type - from xAOD or xAODAnaHelper Algo output
  std::string m_inputAlgo = "";
  // output type - how vector<string> w/ syst names saved in TStore
  std::string m_outputAlgo = "";

  // decorate selected events? default "pass*Sel" + corresponding input jet container name
  bool m_decorateSelectedEvents = true;

  // index of jet container to run systematics over
  unsigned m_jetSystsContainerIndex = 0;

  // input trigger lists
  std::string m_signalTrigList;
  std::string m_validTrigList;
  std::string m_ctrlTrigList;

  // event selections
  unsigned m_nSignalJets  = 4;
  double   m_signalJetPt  = 120.; // GeV
  double   m_signalJetEta = 2.5;
  double   m_signalNJetHt = 1000; // GeV
  unsigned m_nSignalEJs   = 2;

  unsigned m_nValidJets  = 2;
  double   m_validJetPt  = 50.; // GeV
  double   m_validJetEta = 2.7; // --> do we even need this ??
  

  // units conversion from MeV; default is GeV
  float m_units = 1e3;
  

  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

 protected:
  std::vector<std::string> m_inJetContainers; //!
  std::vector<std::string> m_inJetBins; //!

  std::vector<std::string> m_signalTrigs; //!
  std::vector<std::string> m_validTrigs; //!
  std::vector<std::string> m_ctrlTrigs; //!

 private:
  int m_eventNumber; //!

  int m_numPassEvents; //!
  std::vector<int> m_numSignalEvents; //!
  std::vector<int> m_numValidEvents; //!
  std::vector<int> m_numCtrlEvents; //!
  std::vector<int> m_numSignalValidEvents; //!

  int m_numPassWeightEvents; //!
  std::vector<int> m_numSignalWeightEvents; //!
  std::vector<int> m_numValidWeightEvents; //!
  std::vector<int> m_numCtrlWeightEvents; //!
  std::vector<int> m_numSignalValidWeightEvents; //!

  int m_cutflow_bin; //!
  
  TH1D* m_cutflowHist        = 0; //!
  TH1D* m_cutflowHistW       = 0; //!
  TH1D* m_cutflowSignalHist  = 0; //!
  TH1D* m_cutflowSignalHistW = 0; //!
  TH1D* m_cutflowValidHist   = 0; //!
  TH1D* m_cutflowValidHistW  = 0; //!
  TH1D* m_cutflowCtrlHist    = 0; //!
  TH1D* m_cutflowCtrlHistW   = 0; //!
  // --> plot all jet containers on same histograms, but only count nominal case (no syst)

  double m_mcEventWeight; //!

  std::vector<std::string> m_passedTriggers; //!

  bool m_isNominalCase; //!
  bool m_isFirstJetContainer; //!

  
 public:
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

  // added functions not from Algorithm
  virtual EL::StatusCode executeSelection ( const xAOD::EventInfo*, const std::string&, bool& );

  virtual int PassSignalCuts     ( const xAOD::EventInfo*, const xAOD::JetContainer*, const std::string&, const std::string& );
  virtual int PassValidationCuts ( const xAOD::EventInfo*, const xAOD::JetContainer*, const std::string&, const std::string& );
  virtual int PassControlCuts    ( const xAOD::EventInfo*, const xAOD::JetContainer*, const std::string&, const std::string& );

  bool selectEmergingJet ( const xAOD::Jet* );
  
  // needed to distribute algorithm to workers
  ClassDef ( EJsxAODAnalysis, 1 );
};

#endif // EJsAnalysis_EJsxAODAnalysis_H
