#ifndef EJsAnalysis_EJsxAODAnalysis_H
#define EJsAnalysis_EJsxAODAnalysis_H

/* EJsxAODAnalysis is the algorithm responsible for final EJs analysis selection
   and EJs observable, object, and signal/control/validation region definition/calculation */

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <TSystem.h>
#include <TFile.h>
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
  std::string m_inJetContainerName      = "";
  std::string m_inTruthJetContainerName = "AntiKt4TruthJets";

  // output histogram bin names
  std::string m_inJetBinName = "";

  // input type - from xAOD or xAODAnaHelper Algo output
  std::string m_inputAlgo = "";
  // output type - how vector<string> w/ syst names saved in TStore
  std::string m_outputAlgo = "";

  // decorate selected events? default "pass*Sel" + corresponding input jet container name
  bool m_decorateSelectedEvents = true;

  // cut on events failing region cuts
  bool m_applyRegionCuts = true;

  // index of jet container to run systematics over
  unsigned m_jetSystsContainerIndex = 0;

  // jet container type to include in cutflow
  std::string m_cutflowJets = "EMTopo";

  // input trigger lists
  std::string m_signalTrigList;
  std::string m_validTrigList;

  // input metadata text file
  std::string m_metadataFileName = "";

  // event selections
  unsigned m_nSignalJets  = 4;
  double   m_signalJetPt  = 120.; // GeV
  double   m_signalJetEta = 2.5;
  double   m_signalNJetHt = 1000; // GeV
  unsigned m_nSignalEJs   = 2;

  unsigned m_nValidJets  = 2;
  double   m_validJetPt  = 120.; // GeV
  double   m_validJetEta = 2.5;

  // protection when running on truth derivation
  bool m_truthLevelOnly = false;
  
  // units conversion from MeV; default is GeV
  float m_units = 1e3;

  // cutflow / decorator labels
  std::string m_signalTrigLabel = "signalTrigger";
  std::string m_validTrigLabel  = "validTrigger";
  

  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

 protected:
  std::vector<std::string> m_inJetContainers; //!
  std::vector<std::string> m_inJetBins;       //!

  std::vector<std::string> m_signalTrigs; //!
  std::vector<std::string> m_validTrigs;  //!

 private:
  int m_eventNumber; //!

  int m_numPassEvents;                     //!
  std::vector<int> m_numSignalEvents;      //!
  std::vector<int> m_numValidEvents;       //!
  std::vector<int> m_numSignalValidEvents; //!

  int m_numPassWeightEvents;                     //!
  std::vector<int> m_numSignalWeightEvents;      //!
  std::vector<int> m_numValidWeightEvents;       //!
  std::vector<int> m_numSignalValidWeightEvents; //!

  Long64_t m_numTotalEvents; //!

  double m_mcEventWeight;   //!
  int    m_mcChannelNumber; //!
  double m_xsec       = 1.; //!
  double m_kfactor    = 1.; //!
  double m_filteff    = 1.; //!

  std::vector<std::string> m_passedTriggers; //!

  bool m_isNominalCase;       //!
  bool m_isFirstJetContainer; //!


  // event cutflow
  TH1D* m_cutflowHist        = 0; //!
  TH1D* m_cutflowHistW       = 0; //!
  int   m_cutflow_bin;            //!

  // signal- / validation- level cutflow
  TH1D* m_signal_cutflowHist = 0; //!
  int   m_signal_cutflow_all;     //!
  int   m_signal_cutflow_init;    //!
  int   m_signal_cutflow_trig;    //!
  int   m_signal_cutflow_njet;    //!
  int   m_signal_cutflow_jetpt;   //!
  int   m_signal_cutflow_jeteta;  //!
  int   m_signal_cutflow_njetHt;  //!
  int   m_signal_cutflow_nej;     //!
  TH1D* m_valid_cutflowHist  = 0; //!
  int   m_valid_cutflow_all;      //!
  int   m_valid_cutflow_init;     //!
  int   m_valid_cutflow_trig;     //!
  int   m_valid_cutflow_njetmin;  //!
  int   m_valid_cutflow_jetpt;    //!
  int   m_valid_cutflow_jeteta;   //!
  int   m_valid_cutflow_njetmax;  //!

  // metadata weights
  TH1D* m_meta_weightHist = 0; //!
  int m_meta_weight_xsec;      //!
  int m_meta_weight_kfactor;   //!
  int m_meta_weight_filteff;   //!

  
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

  virtual int PassSignalCuts     ( const xAOD::EventInfo*, const xAOD::JetContainer*, const std::string&, int&, int& );
  virtual int PassValidationCuts ( const xAOD::EventInfo*, const xAOD::JetContainer*, const std::string& );

  bool selectEmergingJet ( const xAOD::Jet* );
  
  // needed to distribute algorithm to workers
  ClassDef ( EJsxAODAnalysis, 1 );
};

#endif // EJsAnalysis_EJsxAODAnalysis_H
