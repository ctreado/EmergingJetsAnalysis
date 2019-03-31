#ifndef EJsAnalysis_EJsHistogramManager_H
#define EJsAnalysis_EJsHistogramManager_H

/* EJsHistogramManager is a class derived from xAODAnaHelpers's HistogramManager class
   that books and fills EJs-specific histograms; 
   EJsHistogramManager is designed to run after the ntuple-making step
   and therefore contains connect-branch functions to read from an input TTree
   (may want to eventually add functionality to run directly over xAODs as well...) */

#include <string>
#include <vector>
#include <map>

#include <xAODAnaHelpers/HistogramManager.h>
#include <xAODAnaHelpers/HelperClasses.h>

#include "EJsAnalysis/EJsHelperFunctions.h"
#include "EJsAnalysis/EJsHelperClasses.h"


class EJsHistogramManager : public HistogramManager
{
 public:
  EJsHistogramManager ( std::string name, std::string detailStr, bool debug = false, bool emtopo = true, bool pflow = false, bool truth = false );
  virtual ~EJsHistogramManager ();

  StatusCode connectEvents         ( TTree* tree, bool mc = false );
  StatusCode connectTriggers       ( TTree* tree, bool mc = false );
  StatusCode connectJets           ( TTree* tree, const std::string jetName      = "jet",     bool mc = false );
  StatusCode connectTrigJets       ( TTree* tree, const std::string trigJetName  = "trigJet", bool mc = false );
  StatusCode connectTracks         ( TTree* tree, const std::string trackName    = "track",   bool mc = false ); 
  StatusCode connectSecondaryVerts ( TTree* tree, const std::string secVtxName   = "secVtx",  bool mc = false );
  StatusCode connectTruthJets      ( TTree* tree, const std::string truthJetName = "truthJet"  );
  StatusCode connectTruthDarkJets  ( TTree* tree, const std::string darkJetName  = "darkJet"   );
  StatusCode connectTruthParts     ( TTree* tree, const std::string truthName    = "truthPart" );
  StatusCode connectTruthVerts     ( TTree* tree, const std::string truthVtxName = "truthVtx"  ); 
  // --> need to handle all jet containers separately (write separate variables + connect functions for each collection)
  // or histograms will be overwritten with info from latest collection --> can dictate which collections to run w/ info switch -->
  // --> may be easiest to set up to handle one reco jet collection at a time (plus truth and dark jets)
  // and then just run job twice with different collections -->
  // --> can use info switches to turn off other histograms that already exist and don't depend on jets ...

  StatusCode initialize ( const std::string jetName, const std::string outFileName, const std::vector<std::string>& regions, bool mc = false );
  StatusCode execute    ( TTree* tree, Long64_t treeEntry, const std::vector<EJsHelper::Region>& regions, bool mc = false );
  // --> pass structures (not strings) to execute...

  using HistogramManager::book;    // overload
  using HistogramManager::initialize; // overload
  using HistogramManager::execute; // overload


 protected:
  // holds bools to control which histograms to be filled
  EJsHelperClasses::HistogramInfoSwitch* m_histoInfoSwitch;

  
 private:
  bool m_debug;
  bool m_doEMTopoJets;
  bool m_doPFlowJets;
  bool m_truthLevelOnly;
  
  std::string m_jetStr;

  int m_numLead;
  int m_numVtxTrk;


  // --- BRANCHES --- //
  
  // branches -- events
  int      m_runNumber;       //!
  Long64_t m_eventNumber;     //!
  int      m_lumiBlock;       //!
  int      m_bcid;            //!
  int      m_mcEventNumber;   //!
  int      m_mcChannelNumber; //!
  float    m_mcEventWeight;   //!
  int      m_npv;             //!
  float    m_actualMu;        //!
  float    m_averageMu;       //!
  float    m_weight_pileup;   //!
  uint8_t  m_isMC;            //!
  uint8_t  m_signal;          //!
  uint8_t  m_valid;           //!
  uint8_t  m_ctrl;            //!
  float    m_njetHt;          //!
  
  float    m_pv_x;            //!
  float    m_pv_y;            //!
  float    m_pv_z;            //!
  float    m_pv_r;            //!
  float    m_pv_phi;          //!
  uint32_t m_pv_nTrk;         //!
  int      m_pv_location;     //!

  
  // branches -- triggers
  int m_passL1;                                 //!
  int m_passHLT;                                //!
  std::vector<std::string>* m_passedTriggers;   //!
  std::vector<std::string>* m_disabledTriggers; //!

  
  // branches -- jets
  int                 m_jet_n;          //!
  std::vector<float>* m_jet_pt;         //!
  std::vector<float>* m_jet_eta;        //!
  std::vector<float>* m_jet_phi;        //!
  std::vector<float>* m_jet_E;          //!
  std::vector<float>* m_jet_M;          //!
  std::vector<float>* m_jet_rapid;      //!
  
  std::vector<float>* m_jet_hecFrac;      //!
  std::vector<float>* m_jet_emFrac;       //!
  std::vector<float>* m_jet_centroidR;    //!
  std::vector<float>* m_jet_width;        //!
  std::vector<int>*   m_jet_numConstit;   //!
  
  std::vector<std::vector<int>>*   m_jet_numTrkPt10;   //!
  std::vector<std::vector<float>>* m_jet_sumPtTrkPt10; //!
  std::vector<std::vector<float>>* m_jet_trkWidthPt10; //!
  std::vector<std::vector<int>>*   m_jet_numTrkPt5;    //!
  std::vector<std::vector<float>>* m_jet_sumPtTrkPt5;  //!
  std::vector<std::vector<float>>* m_jet_trkWidthPt5;  //!
  std::vector<std::vector<float>>* m_jet_jvf;          //!
  
  std::vector<int>*   m_jet_GhostTrackCount; //!
  std::vector<float>* m_jet_GhostTrackPt;    //! 
  std::vector<int>*   m_jet_GhostTruthCount; //!
  std::vector<float>* m_jet_GhostTruthPt;    //!
  
  std::vector<int>*                m_jet_trkCount;        //!
  std::vector<float>*              m_jet_trkPt;           //!
  std::vector<std::vector<float>>* m_jet_trk_dR;          //!
  std::vector<int>*                m_jet_tpCount;         //!
  std::vector<float>*              m_jet_tpPt;            //!
  std::vector<std::vector<float>>* m_jet_tp_dR;           //!

  std::vector<int>*                m_jet_secVtxCount;   //!
  std::vector<float>*              m_jet_secVtxPt;      //!
  std::vector<std::vector<float>>* m_jet_secVtx_dR;     //!
  std::vector<int>*                m_jet_truthVtxCount; //!
  std::vector<float>*              m_jet_truthVtxPt;    //!
  std::vector<std::vector<float>>* m_jet_truthVtx_dR;   //!

  std::vector<uint8_t>* m_jet_isTruthMatched; //!
  std::vector<float>*   m_jet_truthMatch_dR;  //!
  std::vector<uint8_t>* m_jet_isDarkMatched;  //!
  std::vector<float>*   m_jet_darkMatch_dR;   //!
  

  // branches -- truth jets
  int                 m_truthJet_n;          //!
  std::vector<float>* m_truthJet_pt;         //!
  std::vector<float>* m_truthJet_eta;        //!
  std::vector<float>* m_truthJet_phi;        //!
  std::vector<float>* m_truthJet_E;          //!
  std::vector<float>* m_truthJet_M;          //!
  std::vector<float>* m_truthJet_rapid;      //!
  
  std::vector<float>*              m_truthJet_width;      //!
  std::vector<float>*              m_truthJet_girth;      //!
  std::vector<int>*                m_truthJet_numConstit; //!
  std::vector<float>*              m_truthJet_constitPt;  //!
  std::vector<std::vector<float>>* m_truthJet_constit_dR; //!

  std::vector<int>*                m_truthJet_trkCount; //!
  std::vector<float>*              m_truthJet_trkPt;    //!
  std::vector<std::vector<float>>* m_truthJet_trk_dR;   //!
  std::vector<int>*                m_truthJet_tpCount;  //!
  std::vector<float>*              m_truthJet_tpPt;     //!
  std::vector<std::vector<float>>* m_truthJet_tp_dR;    //!

  std::vector<int>*                m_truthJet_secVtxCount;   //!
  std::vector<float>*              m_truthJet_secVtxPt;      //!
  std::vector<std::vector<float>>* m_truthJet_secVtx_dR;     //!
  std::vector<int>*                m_truthJet_truthVtxCount; //!
  std::vector<float>*              m_truthJet_truthVtxPt;    //!
  std::vector<std::vector<float>>* m_truthJet_truthVtx_dR;   //!

  std::vector<uint8_t>* m_truthJet_isDarkMatched;  //!
  std::vector<float>*   m_truthJet_darkMatch_dR;   //!
  

  // branches -- truth dark jets
  int                 m_darkJet_n;          //!
  std::vector<float>* m_darkJet_pt;         //!
  std::vector<float>* m_darkJet_eta;        //!
  std::vector<float>* m_darkJet_phi;        //!
  std::vector<float>* m_darkJet_E;          //!
  std::vector<float>* m_darkJet_M;          //!
  std::vector<float>* m_darkJet_rapid;      //!

  std::vector<float>*              m_darkJet_girth;      //!
  std::vector<int>*                m_darkJet_numConstit; //!
  std::vector<float>*              m_darkJet_constitPt;  //!
  std::vector<std::vector<float>>* m_darkJet_constit_dR; //!

  std::vector<int>*                m_darkJet_trkCount; //!
  std::vector<float>*              m_darkJet_trkPt;    //!
  std::vector<std::vector<float>>* m_darkJet_trk_dR;   //!
  std::vector<int>*                m_darkJet_tpCount;  //!
  std::vector<float>*              m_darkJet_tpPt;     //!
  std::vector<std::vector<float>>* m_darkJet_tp_dR;    //!
  
  std::vector<int>*                m_darkJet_secVtxCount;   //!
  std::vector<float>*              m_darkJet_secVtxPt;      //!
  std::vector<std::vector<float>>* m_darkJet_secVtx_dR;     //!
  std::vector<int>*                m_darkJet_truthVtxCount; //!
  std::vector<float>*              m_darkJet_truthVtxPt;    //!
  std::vector<std::vector<float>>* m_darkJet_truthVtx_dR;   //!


  // branches -- truth particles
  int                                m_tp_n;             //!
  std::vector<float>*                m_tp_pt;            //!
  std::vector<float>*                m_tp_eta;           //!
  std::vector<float>*                m_tp_phi;           //!
  std::vector<float>*                m_tp_E;             //!
  std::vector<float>*                m_tp_M;             //!
  std::vector<float>*                m_tp_charge;        //!
  std::vector<int>*                  m_tp_pdgId;         //!
  std::vector<int>*                  m_tp_status;        //!
  std::vector<uint8_t>*              m_tp_isDark;        //!
  std::vector<int>*                  m_tp_nParents;      //!
  std::vector<std::vector<int>>*     m_tp_parent_pdgId;  //!
  std::vector<std::vector<int>>*     m_tp_parent_status; //!
  std::vector<int>*                  m_tp_nChildren;     //!
  std::vector<std::vector<int>>*     m_tp_child_pdgId;   //!
  std::vector<std::vector<int>>*     m_tp_child_status;  //!
  std::vector<uint8_t>*              m_tp_hasPVtx;       //!
  std::vector<float>*                m_tp_pVtx_r;        //!
  std::vector<uint8_t>*              m_tp_hasDVtx;       //!
  std::vector<float>*                m_tp_dVtx_r;        //!

   
  // branches -- secondary vertex
  int                 m_secVtx_n;             //!
  std::vector<float>* m_secVtx_x;             //!
  std::vector<float>* m_secVtx_y;             //!
  std::vector<float>* m_secVtx_z;             //!
  std::vector<float>* m_secVtx_r;             //!
  std::vector<float>* m_secVtx_pt;            //!
  // pt_l, pt_m, pt_s ??
  std::vector<float>* m_secVtx_eta;           //!
  std::vector<float>* m_secVtx_phi;           //!
  std::vector<float>* m_secVtx_mass;          //!
  std::vector<float>* m_secVtx_mass_nonAssoc; //!
  std::vector<float>* m_secVtx_chi2;          //!
  std::vector<float>* m_secVtx_direction;     //!
  std::vector<int>*   m_secVtx_charge;        //!
  std::vector<float>* m_secVtx_Ht;            //!
  std::vector<float>* m_secVtx_minOpAng;      //!
  std::vector<float>* m_secVtx_maxOpAng;      //!
  std::vector<float>* m_secVtx_mind0;         //!
  std::vector<float>* m_secVtx_maxd0;         //!
  
  // kinematics (px,py,pz,Et) ??
  std::vector<float>*              m_secVtx_minOneTrkRmvMass; //!
  std::vector<std::vector<float>>* m_secVtx_twoTrkMass;       //!
  std::vector<std::vector<float>>* m_secVtx_twoTrkMassRest;   //!
  std::vector<std::vector<int>>*   m_secVtx_twoTrkCharge;     //!

  std::vector<uint32_t>* m_secVtx_ntrk;       //!
  std::vector<uint32_t>* m_secVtx_ntrk_sel;   //!
  std::vector<uint32_t>* m_secVtx_ntrk_assoc; //!

  

  // --- HISTOGRAMS --- //
  
  // histograms -- events
  // basics
  std::vector<TH1F*> h_npv;       //!
  std::vector<TH1F*> h_actualMu;  //!
  std::vector<TH1F*> h_averageMu; //!
  std::vector<TH1F*> h_njetHt;    //!
  // PV
  std::vector<TH1F*> h_pv_x;    //!
  std::vector<TH1F*> h_pv_y;    //!
  std::vector<TH1F*> h_pv_z;    //!
  std::vector<TH1F*> h_pv_r;    //!
  std::vector<TH1F*> h_pv_phi;  //!
  std::vector<TH1F*> h_pv_nTrk; //!


  // histograms -- jets
  // jet basics
  std::vector<TH1F*> h_jet_n;     //!
  std::vector<TH1F*> h_jet_pt;    //!
  std::vector<TH1F*> h_jet_pt_l;  //!
  std::vector<TH1F*> h_jet_pt_m;  //!
  std::vector<TH1F*> h_jet_pt_s;  //!
  std::vector<TH1F*> h_jet_eta;   //!
  std::vector<TH1F*> h_jet_phi;   //!
  std::vector<TH1F*> h_jet_E;     //!
  std::vector<TH1F*> h_jet_M;     //!
  std::vector<TH1F*> h_jet_rapid; //!
  // jet kinematics
  std::vector<TH1F*> h_jet_px;    //!
  std::vector<TH1F*> h_jet_py;    //!
  std::vector<TH1F*> h_jet_pz;    //!
  std::vector<TH1F*> h_jet_Et;    //!
  std::vector<TH1F*> h_jet_Et_l;  //!
  std::vector<TH1F*> h_jet_Et_m;  //!
  std::vector<TH1F*> h_jet_Et_s;  //!
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
  // leading jet kinematics
  std::vector<std::vector<TH1F*>> h_jetN_Et;    //!
  std::vector<std::vector<TH1F*>> h_jetN_Et_l;  //!
  std::vector<std::vector<TH1F*>> h_jetN_Et_m;  //!
  std::vector<std::vector<TH1F*>> h_jetN_Et_s;  //!

  // jet energy, width, constituents
  std::vector<TH1F*> h_jet_hecFrac;         //!
  std::vector<TH1F*> h_jet_emFrac;          //!
  std::vector<TH1F*> h_jet_centroidR;       //!
  std::vector<TH1F*> h_jet_width;           //!
  std::vector<TH1F*> h_jet_numConstit;      //!
  
  // track moments (PV)
  std::vector<TH1F*> h_jet_numTrkPt10;      //!
  std::vector<TH1F*> h_jet_sumPtTrkPt10;    //!
  std::vector<TH1F*> h_jet_sumPtTrkPt10_l;  //!
  std::vector<TH1F*> h_jet_sumPtTrkPt10_m;  //!
  std::vector<TH1F*> h_jet_sumPtTrkPt10_s;  //!
  std::vector<TH1F*> h_jet_trkWidthPt10;    //!
  std::vector<TH1F*> h_jet_numTrkPt5;       //!
  std::vector<TH1F*> h_jet_sumPtTrkPt5;     //!
  std::vector<TH1F*> h_jet_sumPtTrkPt5_l;   //!
  std::vector<TH1F*> h_jet_sumPtTrkPt5_m;   //!
  std::vector<TH1F*> h_jet_sumPtTrkPt5_s;   //!
  std::vector<TH1F*> h_jet_trkWidthPt5;     //!
  std::vector<TH1F*> h_jet_jvf;             //!
  
  // ghost-associated jet tracks / truth particles
  std::vector<TH1F*> h_jet_GhostTrackCount; //!
  std::vector<TH1F*> h_jet_GhostTrackPt;    //!
  std::vector<TH1F*> h_jet_GhostTrackPt_l;  //!
  std::vector<TH1F*> h_jet_GhostTrackPt_m;  //!
  std::vector<TH1F*> h_jet_GhostTrackPt_s;  //!
  std::vector<TH1F*> h_jet_GhostTruthCount; //!
  std::vector<TH1F*> h_jet_GhostTruthPt;    //!
  std::vector<TH1F*> h_jet_GhostTruthPt_l;  //!
  std::vector<TH1F*> h_jet_GhostTruthPt_m;  //!
  std::vector<TH1F*> h_jet_GhostTruthPt_s;  //!

  // jet associated tracks / truth particles
  std::vector<TH1F*> h_jet_trkCount; //!
  std::vector<TH1F*> h_jet_trkPt;    //!
  std::vector<TH1F*> h_jet_trkPt_l;  //!
  std::vector<TH1F*> h_jet_trkPt_m;  //!
  std::vector<TH1F*> h_jet_trkPt_s;  //!
  std::vector<TH1F*> h_jet_trk_dR;   //!
  std::vector<TH1F*> h_jet_tpCount;  //!
  std::vector<TH1F*> h_jet_tpPt;     //!
  std::vector<TH1F*> h_jet_tpPt_l;   //!
  std::vector<TH1F*> h_jet_tpPt_m;   //!
  std::vector<TH1F*> h_jet_tpPt_s;   //!
  std::vector<TH1F*> h_jet_tp_dR;    //!

  // jet associated vertices
  std::vector<TH1F*> h_jet_secVtxCount;   //!
  std::vector<TH1F*> h_jet_secVtxPt;      //!
  std::vector<TH1F*> h_jet_secVtx_dR;     //!
  std::vector<TH1F*> h_jet_truthVtxCount; //!
  std::vector<TH1F*> h_jet_truthVtxPt;    //!
  std::vector<TH1F*> h_jet_truthVtx_dR;   //!

  // jets vs pileup (average mu)
  std::vector<TH2F*> h_jet_n_vs_avgMu;           //!
  std::vector<TH2F*> h_jet_pt_vs_avgMu;          //!
  std::vector<TH2F*> h_jet_trkCount_vs_avgMu;    //!
  std::vector<TH2F*> h_jet_trkPt_vs_avgMu;       //!
  std::vector<TH2F*> h_jet_trk_dR_vs_avgMu;      //!
  std::vector<TH2F*> h_jet_secVtxCount_vs_avgMu; //!
  std::vector<TH2F*> h_jet_secVtxPt_vs_avgMu;    //!
  std::vector<TH2F*> h_jet_secVtx_dR_vs_avgMu;   //!
  // jets vs pileup (actual mu)
  std::vector<TH2F*> h_jet_n_vs_actMu;           //!
  std::vector<TH2F*> h_jet_pt_vs_actMu;          //!
  std::vector<TH2F*> h_jet_trkCount_vs_actMu;    //!
  std::vector<TH2F*> h_jet_trkPt_vs_actMu;       //!
  std::vector<TH2F*> h_jet_trk_dR_vs_actMu;      //!
  std::vector<TH2F*> h_jet_secVtxCount_vs_actMu; //!
  std::vector<TH2F*> h_jet_secVtxPt_vs_actMu;    //!
  std::vector<TH2F*> h_jet_secVtx_dR_vs_actMu;   //!
 

  // histograms -- truth jets
  // truth jet basics
  std::vector<TH1F*> h_truthJet_n;     //!
  std::vector<TH1F*> h_truthJet_pt;    //!
  std::vector<TH1F*> h_truthJet_pt_l;  //!
  std::vector<TH1F*> h_truthJet_pt_m;  //!
  std::vector<TH1F*> h_truthJet_pt_s;  //!
  std::vector<TH1F*> h_truthJet_eta;   //!
  std::vector<TH1F*> h_truthJet_phi;   //!
  std::vector<TH1F*> h_truthJet_E;     //!
  std::vector<TH1F*> h_truthJet_M;     //!
  std::vector<TH1F*> h_truthJet_rapid; //!
  // truth jet kinematics
  std::vector<TH1F*> h_truthJet_px;    //!
  std::vector<TH1F*> h_truthJet_py;    //!
  std::vector<TH1F*> h_truthJet_pz;    //!
  std::vector<TH1F*> h_truthJet_Et;    //!
  std::vector<TH1F*> h_truthJet_Et_l;  //!
  std::vector<TH1F*> h_truthJet_Et_m;  //!
  std::vector<TH1F*> h_truthJet_Et_s;  //!
  // leading truth jets
  std::vector<std::vector<TH1F*>> h_truthJetN_pt;    //!
  std::vector<std::vector<TH1F*>> h_truthJetN_pt_l;  //!
  std::vector<std::vector<TH1F*>> h_truthJetN_pt_m;  //!
  std::vector<std::vector<TH1F*>> h_truthJetN_pt_s;  //!
  std::vector<std::vector<TH1F*>> h_truthJetN_eta;   //!
  std::vector<std::vector<TH1F*>> h_truthJetN_phi;   //!
  std::vector<std::vector<TH1F*>> h_truthJetN_E;     //!
  std::vector<std::vector<TH1F*>> h_truthJetN_M;     //!
  std::vector<std::vector<TH1F*>> h_truthJetN_rapid; //!
  // leading truth jet kinematics
  std::vector<std::vector<TH1F*>> h_truthJetN_Et;    //!
  std::vector<std::vector<TH1F*>> h_truthJetN_Et_l;  //!
  std::vector<std::vector<TH1F*>> h_truthJetN_Et_m;  //!
  std::vector<std::vector<TH1F*>> h_truthJetN_Et_s;  //!

  // truth jet width, constituents
  std::vector<TH1F*> h_truthJet_width;      //!
  std::vector<TH1F*> h_truthJet_girth;      //!
  std::vector<TH1F*> h_truthJet_numConstit; //!
  std::vector<TH1F*> h_truthJet_constitPt;  //!
  std::vector<TH1F*> h_truthJet_constit_dR; //!

  // truth jet associated tracks / truth particles
  std::vector<TH1F*> h_truthJet_trkCount; //!
  std::vector<TH1F*> h_truthJet_trkPt;    //!
  std::vector<TH1F*> h_truthJet_trkPt_l;  //!
  std::vector<TH1F*> h_truthJet_trkPt_m;  //!
  std::vector<TH1F*> h_truthJet_trkPt_s;  //!
  std::vector<TH1F*> h_truthJet_trk_dR;   //!
  std::vector<TH1F*> h_truthJet_tpCount;  //!
  std::vector<TH1F*> h_truthJet_tpPt;     //!
  std::vector<TH1F*> h_truthJet_tpPt_l;   //!
  std::vector<TH1F*> h_truthJet_tpPt_m;   //!
  std::vector<TH1F*> h_truthJet_tpPt_s;   //!
  std::vector<TH1F*> h_truthJet_tp_dR;    //!

  // truth jet associated vertices
  std::vector<TH1F*> h_truthJet_secVtxCount;   //!
  std::vector<TH1F*> h_truthJet_secVtxPt;      //!
  std::vector<TH1F*> h_truthJet_secVtx_dR;     //!
  std::vector<TH1F*> h_truthJet_truthVtxCount; //!
  std::vector<TH1F*> h_truthJet_truthVtxPt;    //!
  std::vector<TH1F*> h_truthJet_truthVtx_dR;   //!

  // truth jets vs pileup (average mu)
  std::vector<TH2F*> h_truthJet_n_vs_avgMu;  //!
  std::vector<TH2F*> h_truthJet_pt_vs_avgMu; //!
  // truth jets vs pileup (actual mu)
  std::vector<TH2F*> h_truthJet_n_vs_actMu;  //!
  std::vector<TH2F*> h_truthJet_pt_vs_actMu; //!
  


  // histograms -- truth dark jets
  // dark jet basics
  std::vector<TH1F*> h_darkJet_n;     //!
  std::vector<TH1F*> h_darkJet_pt;    //!
  std::vector<TH1F*> h_darkJet_pt_l;  //!
  std::vector<TH1F*> h_darkJet_pt_m;  //!
  std::vector<TH1F*> h_darkJet_pt_s;  //!
  std::vector<TH1F*> h_darkJet_eta;   //!
  std::vector<TH1F*> h_darkJet_phi;   //!
  std::vector<TH1F*> h_darkJet_E;     //!
  std::vector<TH1F*> h_darkJet_M;     //!
  std::vector<TH1F*> h_darkJet_rapid; //!
   // dark jet kinematics
  std::vector<TH1F*> h_darkJet_px;    //!
  std::vector<TH1F*> h_darkJet_py;    //!
  std::vector<TH1F*> h_darkJet_pz;    //!
  std::vector<TH1F*> h_darkJet_Et;    //!
  std::vector<TH1F*> h_darkJet_Et_l;  //!
  std::vector<TH1F*> h_darkJet_Et_m;  //!
  std::vector<TH1F*> h_darkJet_Et_s;  //!
  // leading dark jets
  std::vector<std::vector<TH1F*>> h_darkJetN_pt;    //!
  std::vector<std::vector<TH1F*>> h_darkJetN_pt_l;  //!
  std::vector<std::vector<TH1F*>> h_darkJetN_pt_m;  //!
  std::vector<std::vector<TH1F*>> h_darkJetN_pt_s;  //!
  std::vector<std::vector<TH1F*>> h_darkJetN_eta;   //!
  std::vector<std::vector<TH1F*>> h_darkJetN_phi;   //!
  std::vector<std::vector<TH1F*>> h_darkJetN_E;     //!
  std::vector<std::vector<TH1F*>> h_darkJetN_M;     //!
  std::vector<std::vector<TH1F*>> h_darkJetN_rapid; //!
  // leading dark jet kinematics
  std::vector<std::vector<TH1F*>> h_darkJetN_Et;    //!
  std::vector<std::vector<TH1F*>> h_darkJetN_Et_l;  //!
  std::vector<std::vector<TH1F*>> h_darkJetN_Et_m;  //!
  std::vector<std::vector<TH1F*>> h_darkJetN_Et_s;  //!

  // dark jet constituents
  std::vector<TH1F*> h_darkJet_girth;      //!
  std::vector<TH1F*> h_darkJet_numConstit; //!
  std::vector<TH1F*> h_darkJet_constitPt;  //!
  std::vector<TH1F*> h_darkJet_constit_dR; //!

  // dark jet associated tracks / truth particles
  std::vector<TH1F*> h_darkJet_trkCount; //!
  std::vector<TH1F*> h_darkJet_trkPt;    //!
  std::vector<TH1F*> h_darkJet_trkPt_l;  //!
  std::vector<TH1F*> h_darkJet_trkPt_m;  //!
  std::vector<TH1F*> h_darkJet_trkPt_s;  //!
  std::vector<TH1F*> h_darkJet_trk_dR;   //!
  std::vector<TH1F*> h_darkJet_tpCount;  //!
  std::vector<TH1F*> h_darkJet_tpPt;     //!
  std::vector<TH1F*> h_darkJet_tpPt_l;   //!
  std::vector<TH1F*> h_darkJet_tpPt_m;   //!
  std::vector<TH1F*> h_darkJet_tpPt_s;   //!
  std::vector<TH1F*> h_darkJet_tp_dR;    //!

  // dark jet associated vertices
  std::vector<TH1F*> h_darkJet_secVtxCount;   //!
  std::vector<TH1F*> h_darkJet_secVtxPt;      //!
  std::vector<TH1F*> h_darkJet_secVtx_dR;     //!
  std::vector<TH1F*> h_darkJet_truthVtxCount; //!
  std::vector<TH1F*> h_darkJet_truthVtxPt;    //!
  std::vector<TH1F*> h_darkJet_truthVtx_dR;   //!

  // dark jets vs pileup (average mu)
  std::vector<TH2F*> h_darkJet_n_vs_avgMu;  //!
  std::vector<TH2F*> h_darkJet_pt_vs_avgMu; //!
  // dark jets vs pileup (actual mu)
  std::vector<TH2F*> h_darkJet_n_vs_actMu;  //!
  std::vector<TH2F*> h_darkJet_pt_vs_actMu; //!


  // histograms -- truth particles
  // heavy scalar mediator (Xd) basics
  std::vector<TH1F*> h_Xd_n;            //!
  std::vector<TH1F*> h_Xd_pt;           //!
  std::vector<TH1F*> h_Xd_eta;          //!
  std::vector<TH1F*> h_Xd_phi;          //!
  std::vector<TH1F*> h_Xd_E;            //!
  std::vector<TH1F*> h_Xd_M;            //!
  std::vector<TH1F*> h_Xd_charge;       //!
  std::vector<TH1F*> h_Xd_nParents;     //!
  std::vector<TH1F*> h_Xd_parentPdgId;  //!
  std::vector<TH1F*> h_Xd_parentStatus; //!
  std::vector<TH1F*> h_Xd_nChildren;    //!
  std::vector<TH1F*> h_Xd_childPdgId;   //!
  std::vector<TH1F*> h_Xd_childStatus;  //!
  std::vector<TH1F*> h_Xd_prodVtx_r;    //!
  std::vector<TH1F*> h_Xd_decayVtx_r;   //!
  // dark quark (qd) basics
  std::vector<TH1F*> h_qd_n;            //!
  std::vector<TH1F*> h_qd_pt;           //!
  std::vector<TH1F*> h_qd_eta;          //!
  std::vector<TH1F*> h_qd_phi;          //!
  std::vector<TH1F*> h_qd_E;            //!
  std::vector<TH1F*> h_qd_M;            //!
  std::vector<TH1F*> h_qd_charge;       //!
  std::vector<TH1F*> h_qd_nParents;     //!
  std::vector<TH1F*> h_qd_parentPdgId;  //!
  std::vector<TH1F*> h_qd_parentStatus; //!
  std::vector<TH1F*> h_qd_nChildren;    //!
  std::vector<TH1F*> h_qd_childPdgId;   //!
  std::vector<TH1F*> h_qd_childStatus;  //!
  std::vector<TH1F*> h_qd_prodVtx_r;    //!
  std::vector<TH1F*> h_qd_decayVtx_r;   //!
  // dark pion (pid) basics
  std::vector<TH1F*> h_pid_n;            //!
  std::vector<TH1F*> h_pid_pt;           //!
  std::vector<TH1F*> h_pid_eta;          //!
  std::vector<TH1F*> h_pid_phi;          //!
  std::vector<TH1F*> h_pid_E;            //!
  std::vector<TH1F*> h_pid_M;            //!
  std::vector<TH1F*> h_pid_charge;       //!
  std::vector<TH1F*> h_pid_nParents;     //!
  std::vector<TH1F*> h_pid_parentPdgId;  //!
  std::vector<TH1F*> h_pid_parentStatus; //!
  std::vector<TH1F*> h_pid_nChildren;    //!
  std::vector<TH1F*> h_pid_childPdgId;   //!
  std::vector<TH1F*> h_pid_childStatus;  //!
  std::vector<TH1F*> h_pid_prodVtx_r;    //!
  std::vector<TH1F*> h_pid_decayVtx_r;   //!
  // dark rho (rhod) basics
  std::vector<TH1F*> h_rhod_n;            //!
  std::vector<TH1F*> h_rhod_pt;           //!
  std::vector<TH1F*> h_rhod_eta;          //!
  std::vector<TH1F*> h_rhod_phi;          //!
  std::vector<TH1F*> h_rhod_E;            //!
  std::vector<TH1F*> h_rhod_M;            //!
  std::vector<TH1F*> h_rhod_charge;       //!
  std::vector<TH1F*> h_rhod_nParents;     //!
  std::vector<TH1F*> h_rhod_parentPdgId;  //!
  std::vector<TH1F*> h_rhod_parentStatus; //!
  std::vector<TH1F*> h_rhod_nChildren;    //!
  std::vector<TH1F*> h_rhod_childPdgId;   //!
  std::vector<TH1F*> h_rhod_childStatus;  //!
  std::vector<TH1F*> h_rhod_prodVtx_r;    //!
  std::vector<TH1F*> h_rhod_decayVtx_r;   //!
  // off-diagonal dark pion (offpid) basics
  std::vector<TH1F*> h_offpid_n;            //!
  std::vector<TH1F*> h_offpid_pt;           //!
  std::vector<TH1F*> h_offpid_eta;          //!
  std::vector<TH1F*> h_offpid_phi;          //!
  std::vector<TH1F*> h_offpid_E;            //!
  std::vector<TH1F*> h_offpid_M;            //!
  std::vector<TH1F*> h_offpid_charge;       //!
  std::vector<TH1F*> h_offpid_nParents;     //!
  std::vector<TH1F*> h_offpid_parentPdgId;  //!
  std::vector<TH1F*> h_offpid_parentStatus; //!
  std::vector<TH1F*> h_offpid_nChildren;    //!
  std::vector<TH1F*> h_offpid_childPdgId;   //!
  std::vector<TH1F*> h_offpid_childStatus;  //!
  std::vector<TH1F*> h_offpid_prodVtx_r;    //!
  std::vector<TH1F*> h_offpid_decayVtx_r;   //!
  // off-diagonal dark rho (offrhod) basics
  std::vector<TH1F*> h_offrhod_n;            //!
  std::vector<TH1F*> h_offrhod_pt;           //!
  std::vector<TH1F*> h_offrhod_eta;          //!
  std::vector<TH1F*> h_offrhod_phi;          //!
  std::vector<TH1F*> h_offrhod_E;            //!
  std::vector<TH1F*> h_offrhod_M;            //!
  std::vector<TH1F*> h_offrhod_charge;       //!
  std::vector<TH1F*> h_offrhod_nParents;     //!
  std::vector<TH1F*> h_offrhod_parentPdgId;  //!
  std::vector<TH1F*> h_offrhod_parentStatus; //!
  std::vector<TH1F*> h_offrhod_nChildren;    //!
  std::vector<TH1F*> h_offrhod_childPdgId;   //!
  std::vector<TH1F*> h_offrhod_childStatus;  //!
  std::vector<TH1F*> h_offrhod_prodVtx_r;    //!
  std::vector<TH1F*> h_offrhod_decayVtx_r;   //!
  // dark pion + off-diagonal dark pion (allpid) basics
  std::vector<TH1F*> h_allpid_n;            //!
  std::vector<TH1F*> h_allpid_pt;           //!
  std::vector<TH1F*> h_allpid_eta;          //!
  std::vector<TH1F*> h_allpid_phi;          //!
  std::vector<TH1F*> h_allpid_E;            //!
  std::vector<TH1F*> h_allpid_M;            //!
  std::vector<TH1F*> h_allpid_charge;       //!
  std::vector<TH1F*> h_allpid_nParents;     //!
  std::vector<TH1F*> h_allpid_parentPdgId;  //!
  std::vector<TH1F*> h_allpid_parentStatus; //!
  std::vector<TH1F*> h_allpid_nChildren;    //!
  std::vector<TH1F*> h_allpid_childPdgId;   //!
  std::vector<TH1F*> h_allpid_childStatus;  //!
  std::vector<TH1F*> h_allpid_prodVtx_r;    //!
  std::vector<TH1F*> h_allpid_decayVtx_r;   //!
  // dark rho + off-diagonal dark rho (allrhod) basics
  std::vector<TH1F*> h_allrhod_n;            //!
  std::vector<TH1F*> h_allrhod_pt;           //!
  std::vector<TH1F*> h_allrhod_eta;          //!
  std::vector<TH1F*> h_allrhod_phi;          //!
  std::vector<TH1F*> h_allrhod_E;            //!
  std::vector<TH1F*> h_allrhod_M;            //!
  std::vector<TH1F*> h_allrhod_charge;       //!
  std::vector<TH1F*> h_allrhod_nParents;     //!
  std::vector<TH1F*> h_allrhod_parentPdgId;  //!
  std::vector<TH1F*> h_allrhod_parentStatus; //!
  std::vector<TH1F*> h_allrhod_nChildren;    //!
  std::vector<TH1F*> h_allrhod_childPdgId;   //!
  std::vector<TH1F*> h_allrhod_childStatus;  //!
  std::vector<TH1F*> h_allrhod_prodVtx_r;    //!
  std::vector<TH1F*> h_allrhod_decayVtx_r;   //!
  
  
  // histograms -- secondary vertex
  // secondary vertex basics
  std::vector<TH1F*> h_secVtx_n;                //!
  std::vector<TH1F*> h_secVtx_x;                //!
  std::vector<TH1F*> h_secVtx_y;                //!
  std::vector<TH1F*> h_secVtx_z;                //!
  std::vector<TH1F*> h_secVtx_r;                //!
  std::vector<TH1F*> h_secVtx_r_l;              //!
  std::vector<TH1F*> h_secVtx_r_s;              //!
  std::vector<TH1F*> h_secVtx_pt;               //!
  std::vector<TH1F*> h_secVtx_eta;              //!
  std::vector<TH1F*> h_secVtx_phi;              //!
  std::vector<TH1F*> h_secVtx_mass;             //!
  std::vector<TH1F*> h_secVtx_mass_l;           //!
  std::vector<TH1F*> h_secVtx_mass_s;           //!
  std::vector<TH1F*> h_secVtx_mass_nonAssoc;    //!
  std::vector<TH1F*> h_secVtx_mass_nonAssoc_l;  //!
  std::vector<TH1F*> h_secVtx_mass_nonAssoc_s;  //!
  std::vector<TH1F*> h_secVtx_chi2;             //!
  std::vector<TH1F*> h_secVtx_direction;        //!
  std::vector<TH1F*> h_secVtx_charge;           //!
  std::vector<TH1F*> h_secVtx_Ht;               //!
  std::vector<TH1F*> h_secVtx_minOpAng;         //!
  std::vector<TH1F*> h_secVtx_maxOpAng;         //!
  std::vector<TH1F*> h_secVtx_mind0;            //!
  std::vector<TH1F*> h_secVtx_maxd0;            //!
  std::vector<TH1F*> h_secVtx_minOneTrkRmvMass; //!
  std::vector<TH1F*> h_secVtx_twoTrkMass;       //!
  std::vector<TH1F*> h_secVtx_twoTrkMassRest;   //!
  std::vector<TH1F*> h_secVtx_twoTrkCharge;     //!
  std::vector<TH1F*> h_secVtx_ntrk;             //!
  std::vector<TH1F*> h_secVtx_ntrk_sel;         //!
  std::vector<TH1F*> h_secVtx_ntrk_assoc;       //!

  // secondary vertex parameters vs ntrks
  std::vector<TH2F*> h_secVtx_r_vs_ntrk;                 //!
  std::vector<TH2F*> h_secVtx_pt_vs_ntrk;                //!
  std::vector<TH2F*> h_secVtx_mass_vs_ntrk;              //!
  std::vector<TH2F*> h_secVtx_massNonAssoc_vs_ntrk;      //!
  std::vector<TH2F*> h_secVtx_r_vs_ntrkSel;              //!
  std::vector<TH2F*> h_secVtx_pt_vs_ntrkSel;             //!
  std::vector<TH2F*> h_secVtx_mass_vs_ntrkSel;           //!
  std::vector<TH2F*> h_secVtx_massNonAssoc_vs_ntrkSel;   //!
  std::vector<TH2F*> h_secVtx_r_vs_ntrkAssoc;            //!
  std::vector<TH2F*> h_secVtx_pt_vs_ntrkAssoc;           //!
  std::vector<TH2F*> h_secVtx_mass_vs_ntrkAssoc;         //!
  std::vector<TH2F*> h_secVtx_massNonAssoc_vs_ntrkAssoc; //!
  // ntrk secondary vertices
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_n;               //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_x;               //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_y;               //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_z;               //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_r;               //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_r_l;             //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_r_s;             //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_pt;              //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_eta;             //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_phi;             //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_mass;            //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_mass_l;          //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_mass_s;          //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_mass_nonAssoc;   //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_mass_nonAssoc_l; //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_mass_nonAssoc_s; //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_chi2;            //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_direction;       //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_charge;          //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_Ht;              //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_minOpAng;        //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_maxOpAng;        //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_mind0;           //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_maxd0;           //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_ntrk_sel;        //!
  std::vector<std::vector<TH1F*>> h_secVtxNtrk_ntrk_assoc;      //!

  // secondary vertices vs pileup (average / actual mu)
  std::vector<TH2F*> h_secVtx_n_vs_avgMu;
  std::vector<TH2F*> h_secVtx_r_vs_avgMu;
  std::vector<TH2F*> h_secVtx_pt_vs_avgMu;
  std::vector<TH2F*> h_secVtx_eta_vs_avgMu;
  std::vector<TH2F*> h_secVtx_phi_vs_avgMu;
  std::vector<TH2F*> h_secVtx_mass_vs_avgMu;
  std::vector<TH2F*> h_secVtx_ntrk_vs_avgMu;
  std::vector<TH2F*> h_secVtx_ntrk_sel_vs_avgMu;
  std::vector<TH2F*> h_secVtx_ntrk_assoc_vs_avgMu;
  std::vector<TH2F*> h_secVtx_n_vs_actMu;
  std::vector<TH2F*> h_secVtx_r_vs_actMu;
  std::vector<TH2F*> h_secVtx_pt_vs_actMu;
  std::vector<TH2F*> h_secVtx_eta_vs_actMu;
  std::vector<TH2F*> h_secVtx_phi_vs_actMu;
  std::vector<TH2F*> h_secVtx_mass_vs_actMu;
  std::vector<TH2F*> h_secVtx_ntrk_vs_actMu;
  std::vector<TH2F*> h_secVtx_ntrk_sel_vs_actMu;
  std::vector<TH2F*> h_secVtx_ntrk_assoc_vs_actMu;
  // ntrk secondary vertices vs pileup (average / actual mu)
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_n_vs_avgMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_r_vs_avgMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_pt_vs_avgMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_eta_vs_avgMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_phi_vs_avgMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_mass_vs_avgMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_ntrk_sel_vs_avgMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_ntrk_assoc_vs_avgMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_n_vs_actMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_r_vs_actMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_pt_vs_actMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_eta_vs_actMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_phi_vs_actMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_mass_vs_actMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_ntrk_sel_vs_actMu;
  std::vector<std::vector<TH2F*>> h_secVtxNtrk_ntrk_assoc_vs_actMu;
  // --> FILL IN...
  
  // --> vertex track parameters
  // --> close / linked truth vertices
  

  
  
};

#endif // EJsAnalysis_EJsHistogramManager_H
