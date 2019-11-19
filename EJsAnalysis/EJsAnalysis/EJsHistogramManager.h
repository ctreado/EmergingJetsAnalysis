#ifndef EJsAnalysis_EJsHistogramManager_H
#define EJsAnalysis_EJsHistogramManager_H

/* EJsHistogramManager is a class derived from xAODAnaHelpers's HistogramManager class
   that books and fills EJs-specific histograms; 
   EJsHistogramManager is designed to run after the ntuple-making step
   and therefore contains connect-branch functions to read from an input TTree
   (may want to eventually add functionality to run directly over xAODs as well...) */

#include <TTree.h>

#include <string>
#include <vector>

#include <xAODAnaHelpers/HistogramManager.h>
#include <xAODAnaHelpers/HelperClasses.h>

#include "EJsAnalysis/EJsHelperFunctions.h"
#include "EJsAnalysis/EJsHelperClasses.h"


class EJsHistogramManager : public HistogramManager
{
 public:
  EJsHistogramManager ( const std::string& name, const std::string& detailStr, const std::string& jetStr,
			const std::map<std::string, float>& metadata, float lumi = 139.,
			bool debug = false, bool mc = false, bool unblind = false );
  virtual ~EJsHistogramManager ();

  StatusCode connectEvents         ( TTree* tree );
  StatusCode connectTriggers       ( TTree* tree );
  StatusCode connectJets           ( TTree* tree, const std::string& jetName       = "jet"       );
  StatusCode connectOtherJets      ( TTree* tree, const std::string& jetOthName    = "pflowJet"  );
  StatusCode connectTrigJets       ( TTree* tree, const std::string& trigJetName   = "trigJet"   );
  StatusCode connectTracks         ( TTree* tree, const std::string& trackName     = "track"     );
  StatusCode connectSecondaryVerts ( TTree* tree, const std::string& secVtxName    = "secVtx"    );
  StatusCode connectTruthJets      ( TTree* tree, const std::string& truthJetName  = "truthJet"  );
  StatusCode connectTruthDarkJets  ( TTree* tree, const std::string& darkJetName   = "darkJet"   );
  StatusCode connectTruthParts     ( TTree* tree, const std::string& truthPartName = "truthPart" );
  StatusCode connectTruthVerts     ( TTree* tree, const std::string& truthVtxName  = "truthVtx"  );

  StatusCode initialize ( const std::string& outFileName,  const std::vector<EJsHelper::Region>& regions,
			  const std::string& jetHistName );
  StatusCode execute    ( TTree* tree, Long64_t treeEntry, const std::vector<EJsHelper::Region>& regions );
  StatusCode finalize   ( const std::vector<EJsHelper::Region>& regions );

  using HistogramManager::book;       // overload
  using HistogramManager::initialize; // overload
  using HistogramManager::execute;    // overload
  using HistogramManager::finalize;   // overload


 protected:
  // holds bools that controls which histograms are filled
  EJsHelperClasses::HistogramInfoSwitch* m_histoInfoSwitch;

 private:
  std::string m_jetStr;
  std::string m_jetStrOth;
  float       m_nEvents_init;
  float       m_nEvents_sel;
  float       m_sumw_init;
  float       m_sumw_sel;
  float       m_sumw2_init;
  float       m_sumw2_sel;
  float       m_xsec;
  float       m_kfactor;
  float       m_filteff;
  float       m_lumi;
  bool        m_debug;
  bool        m_mc;
  bool        m_unblind; // un-blind analysis -- default = False to blind signal events in data
  int         m_numLeadJets;

  float weight = 1.0;
  float lumi   = 139.; // [fb-1]  

  // counters
  std::vector<int>   m_nEntries;
  std::vector<float> m_nWeightedEntries;
  std::vector<int>   m_nFourJets;
  std::vector<int>   m_nFourJets_other;
  std::vector<int>   m_nSearch;
  std::vector<int>   m_nSearch_other;
  std::vector<int>   m_nTrig_4j120;
  std::vector<int>   m_nOffTrig_4j120;
  std::vector<int>   m_nOffTrig_4j120_other;
  std::vector<int>   m_nOffTrigJVT_4j120;
  std::vector<int>   m_nOffTrigJVT_4j120_other;
  std::vector<int>   m_nTrig_fourJet;
  std::vector<int>   m_nOffTrig_fourJet;
  std::vector<int>   m_nOthOffTrig_fourJet;
  std::vector<int>   m_nOffTrigJVT_fourJet;
  std::vector<int>   m_nOthOffTrigJVT_fourJet;
  std::vector<int>   m_nTrig_search;
  std::vector<int>   m_nOffTrig_search;
  std::vector<int>   m_nOthOffTrig_search;
  std::vector<int>   m_nOffTrigJVT_search;
  std::vector<int>   m_nOthOffTrigJVT_search;

  // analysis selections
  int    m_nJets      = 4;
  double m_jetPt      = 120.;
  double m_jetEta     = 2.5;
  // trigger selections
  int    m_nTrigJets  = 4;
  double m_trigJetPt  = 120.;
  double m_trigJetEta = 3.1;
  // ABCD region discriminating variables (temp)
  // --> A = > njetHt, > nDV
  double m_ABCD_njetHt = 1375.;
  int    m_ABCD_nDV    = 2;
  


  // --- BRANCHES --- //
  // EVENT BRANCHES
  // event info: basics
  int      m_runNumber;           //!
  Long64_t m_eventNumber;         //!
  int      m_lumiBlock;           //!
  int      m_bcid;                //!
  int      m_mcEventNumber;       //!
  int      m_mcChannelNumber;     //!
  // event info: weights
  float    m_mcEventWeight;       //!
  float    m_weight_pileup;       //!
  // --> get other weights...
  // event info: pileup
  int      m_npv;                 //!
  float    m_actualMu;            //!
  float    m_averageMu;           //!
  float    m_corrActualMu;        //!
  float    m_corrAverageMu;       //!
  float    m_corrScaleActualMu;   //!
  float    m_corrScaleAverageMu;  //!
  int      m_randRunNr;           //!
  int      m_randLumiBlockNr;     //!
  // event info: region / analysis selections
  uint8_t  m_search;              //!
  uint8_t  m_valid;               //!
  float    m_njetHt;              //!
  uint8_t  m_search_njet;         //!
  uint8_t  m_search_jetPt;        //!
  uint8_t  m_search_jetEta;       //!
  uint8_t  m_search_njetHt;       //!
  // event info: region / analysis selections for other jet type
  uint8_t  m_search_other;        //!
  uint8_t  m_valid_other;         //!
  float    m_njetHt_other;        //!
  uint8_t  m_search_njet_other;   //!
  uint8_t  m_search_jetPt_other;  //!
  uint8_t  m_search_jetEta_other; //!
  uint8_t  m_search_njetHt_other; //!
  // PV info
  float    m_pv_x;                //!
  float    m_pv_y;                //!
  float    m_pv_z;                //!
  float    m_pv_r;                //!
  float    m_pv_phi;              //!
  int      m_pv_ntrk;             //!
  int      m_pv_location;         //!

  // TRIGGER BRANCHES
  // trigger info
  std::vector<std::string>* m_passedTriggers;   //!
  std::vector<std::string>* m_disabledTriggers; //!
  std::vector<float>*       m_triggerPrescales; //!

  // JET BRANCHES
  // jets: basics / kinematics
  int m_jet_n;                       //!
  std::vector<int>*   m_jet_ID;      //!
  std::vector<int>*   m_jet_index;   //!
  std::vector<float>* m_jet_pt;      //!
  std::vector<float>* m_jet_eta;     //!
  std::vector<float>* m_jet_phi;     //!
  std::vector<float>* m_jet_E;       //!
  std::vector<float>* m_jet_M;       //!
  std::vector<float>* m_jet_rapid;   //!
  std::vector<int>*   m_jet_passJVT; //!
  // jets: matched tracks
  std::vector<int>*                m_jet_trk_n;        //!
  std::vector<std::vector<int>>*   m_jet_trk_ID;       //!
  std::vector<std::vector<int>>*   m_jet_trk_index;    //!
  std::vector<std::vector<float>>* m_jet_trk_dR;       //! 
  // jets: matched secondary vertices
  std::vector<int>*                m_jet_secVtx_n;     //!
  std::vector<std::vector<int>>*   m_jet_secVtx_ID;    //!
  std::vector<std::vector<int>>*   m_jet_secVtx_index; //!
  std::vector<std::vector<float>>* m_jet_secVtx_dR;    //!
  // other jets: for trigger study
  int m_jetOth_n;                       //!
  std::vector<float>* m_jetOth_pt;      //!
  std::vector<float>* m_jetOth_eta;     //!
  std::vector<int>*   m_jetOth_passJVT; //!

  // TRACK BRANCHES
  // tracks: basics / kinematics
  int m_trk_n; //!

  // SECONDARY VERTEX BRANCHES
  // secondary vertices: basics / kinematics
  int m_secVtx_n; //!
  // secondary vertices matched to jets
  std::vector<uint8_t>* m_secVtx_jetMatched;        //!
  std::vector<int>*     m_secVtx_jetMatch_ID;       //!
  std::vector<int>*     m_secVtx_jetMatch_index;    //!
  std::vector<float>*   m_secVtx_jetMatch_dR;       //!
  std::vector<uint8_t>* m_secVtx_jetOthMatched;     //!
  std::vector<int>*     m_secVtx_jetOthMatch_ID;    //!
  std::vector<int>*     m_secVtx_jetOthMatch_index; //!
  std::vector<float>*   m_secVtx_jetOthMatch_dR;    //!
  


  // --- HISTOGRAMS --- //

  // METADATA HISTOS
  std::vector<TH1F*> h_MetaData_EventCount; //!
  std::vector<TH1F*> h_MetaData_Weights;    //!
  // --> not region-dependent, but save one for each region for ease of access downstream...

  // EVENT HISTOS
  // pileup
  std::vector<TH1F*> h_npv;                //!
  std::vector<TH1F*> h_actualMu;           //!
  std::vector<TH1F*> h_averageMu;          //!
  std::vector<TH1F*> h_corrActualMu;       //!
  std::vector<TH1F*> h_corrAverageMu;      //!
  std::vector<TH1F*> h_corrScaleActualMu;  //!
  std::vector<TH1F*> h_corrScaleAverageMu; //!
  // primary vertex
  std::vector<TH1F*> h_pv_x;      //!
  std::vector<TH1F*> h_pv_y;      //!
  std::vector<TH1F*> h_pv_z;      //!
  std::vector<TH1F*> h_pv_r;      //!
  std::vector<TH1F*> h_pv_phi;    //!
  std::vector<TH1F*> h_pv_ntrk;   //!
  // leading N-jet Ht
  std::vector<TH1F*> h_njetHt;    //!
  std::vector<TH1F*> h_njetOthHt; //!

  // 2D EVENT HISTOS -- ABCD PLANE TESTS
  std::vector<TH2F*> h_abcd_nDV_njetHt;              //!
  std::vector<TH2F*> h_abcd_nJetDV_njetHt;           //!
  std::vector<TH2F*> h_abcd_nLeadJetDV_njetHt;       //!
  std::vector<TH2F*> h_abcd_nDV_njetOthHt;           //!
  std::vector<TH2F*> h_abcd_nJetOthDV_njetOthHt;     //!
  std::vector<TH2F*> h_abcd_nLeadJetOthDV_njetOthHt; //!

  // JET HISTOS
  // basics
  std::vector<TH1F*> h_jet_n;      //!
  std::vector<TH1F*> h_jet_pt;     //!
  std::vector<TH1F*> h_jet_pt_l;   //!
  std::vector<TH1F*> h_jet_pt_m;   //!
  std::vector<TH1F*> h_jet_pt_s;   //!
  std::vector<TH1F*> h_jet_eta;    //!
  std::vector<TH1F*> h_jet_phi;    //!
  std::vector<TH1F*> h_jet_E;      //!
  std::vector<TH1F*> h_jet_M;      //!
  std::vector<TH1F*> h_jet_rapid;  //!
  // extra kinematics
  std::vector<TH1F*> h_jet_px;     //!
  std::vector<TH1F*> h_jet_py;     //!
  std::vector<TH1F*> h_jet_pz;     //!
  std::vector<TH1F*> h_jet_Et;     //!
  std::vector<TH1F*> h_jet_Et_m;   //!
  std::vector<TH1F*> h_jet_Et_s;   //!
  // matched tracks
  std::vector<TH1F*> h_jet_nTrk;       //!
  std::vector<TH1F*> h_jet_trk_dR;     //!
  std::vector<TH2F*> h_jet_nTrk_vs_dR; //!
  // --> look at number of LRT, selected, vertex tracks, etc.
  // matched vertices
  std::vector<TH1F*> h_jet_nDV;       //!
  std::vector<TH1F*> h_jet_DV_dR;     //!
  std::vector<TH2F*> h_jet_nDV_vs_dR; //!
  // --> investigate further (like number of "good" vertices) after vertex studies...
  
  // leading jets
  std::vector<std::vector<TH1F*>> h_jetN_pt;    //!
  std::vector<std::vector<TH1F*>> h_jetN_pt_l;  //!
  std::vector<std::vector<TH1F*>> h_jetN_pt_m;  //!
  std::vector<std::vector<TH1F*>> h_jetN_pt_s;  //!
  std::vector<std::vector<TH1F*>> h_jetN_eta;   //!
  std::vector<std::vector<TH1F*>> h_jetN_phi;   //!
  std::vector<std::vector<TH1F*>> h_jetN_E;     //!
  std::vector<std::vector<TH1F*>> h_jetN_M;     //!
  std::vector<std::vector<TH1F*>> h_jetN_rapid; //!
  // leading jet extra kinematics
  std::vector<std::vector<TH1F*>> h_jetN_Et;    //!
  std::vector<std::vector<TH1F*>> h_jetN_Et_m;  //!
  std::vector<std::vector<TH1F*>> h_jetN_Et_s;  //!
  // --> add matched tracks / vertices (at least counts)

  // TRACK HISTOS
  // basics
  std::vector<TH1F*> h_trk_n; //!

  // SECONDARY VERTEX HISTOS
  // basics
  std::vector<TH1F*> h_DV_n;           //!
  // DVs nearby to (lead) jets
  std::vector<TH1F*> h_byJetDV_n;        //!
  std::vector<TH1F*> h_byJetOthDV_n;     //!
  std::vector<TH1F*> h_byLeadJetDV_n;    //!
  std::vector<TH1F*> h_byLeadJetOthDV_n; //!

  
  // TRIGGER STUDY HISTOS
  std::vector<TH1F*> h_nthJetPt;                     //!
  std::vector<TH1F*> h_nthJetPt_trig;                //!
  std::vector<TH1F*> h_nthJetPt_offTrig;             //!
  std::vector<TH1F*> h_nthJetPt_othOffTrig;          //!
  std::vector<TH1F*> h_nthJetPt_offTrigJVT;          //!
  std::vector<TH1F*> h_nthJetPt_othOffTrigJVT;       //!
  std::vector<TH1F*> h_trigEff_nthJetPt;             //!
  std::vector<TH1F*> h_offTrigEff_nthJetPt;          //!
  std::vector<TH1F*> h_othOffTrigEff_nthJetPt;       //!
  std::vector<TH1F*> h_offTrigJVTEff_nthJetPt;       //!
  std::vector<TH1F*> h_othOffTrigJVTEff_nthJetPt;    //!
  std::vector<TH1F*> h_triggerEfficiency;            //!
  std::vector<TH1F*> h_triggerEfficiency_fourJet;    //!
  std::vector<TH1F*> h_triggerEfficiency_search;     //!
  std::vector<TH1F*> h_searchTriggerEfficiency;      //!
  
};

#endif // EJsAnalysis_EJsHistogramManager_H
