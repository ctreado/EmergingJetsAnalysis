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
			bool debug = false, bool mc = false, bool truth = false );
  virtual ~EJsHistogramManager ();

  StatusCode connectEvents         ( TTree* tree );
  StatusCode connectTriggers       ( TTree* tree );
  StatusCode connectJets           ( TTree* tree, const std::string& jetName       = "jet"       );
  StatusCode connectTrigJets       ( TTree* tree, const std::string& trigJetName   = "trigJet"   );
  StatusCode connectTracks         ( TTree* tree, const std::string& trackName     = "track"     );
  StatusCode connectSecondaryVerts ( TTree* tree, const std::string& secVtxName    = "secVtx"    );
  StatusCode connectTruthJets      ( TTree* tree, const std::string& truthJetName  = "truthJet"  );
  StatusCode connectTruthDarkJets  ( TTree* tree, const std::string& darkJetName   = "darkJet"   );
  StatusCode connectTruthParts     ( TTree* tree, const std::string& truthPartName = "truthPart" );
  StatusCode connectTruthVerts     ( TTree* tree, const std::string& truthVtxName  = "truthVtx"  );

  StatusCode initialize ( const std::string& outFileName,  const std::vector<std::string>& regions,
			  const std::string& jetHistName );
  StatusCode execute    ( TTree* tree, Long64_t treeEntry, const std::vector<EJsHelper::Region>& regions );

  using HistogramManager::book;       // overload
  using HistogramManager::initialize; // overload
  using HistogramManager::execute;    // overload


 protected:
  // holds bools that controls which histograms are filled
  EJsHelperClasses::HistogramInfoSwitch* m_histoInfoSwitch;

 private:
  std::string m_jetStr;
  bool        m_debug;
  bool        m_mc;
  bool        m_truth;
  int         m_numLeadJets;
  int         m_numLeadTJets;
  int         m_numLeadDJets;
  int         m_numVtxTrks;
  int         m_numTVtxTrks;

  
  double m_tpPtThr = 0.5; //!
  double m_tvRThr  = 0.5; //!

  
  // --- BRANCHES --- //

  // EVENTS
  // branches -- event info
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
  // branches -- primary vertex
  float    m_pv_x;            //!
  float    m_pv_y;            //!
  float    m_pv_z;            //!
  float    m_pv_r;            //!
  float    m_pv_phi;          //!
  int      m_pv_ntrk;         //!
  int      m_pv_location;     //!

  // TRIGGERS
  // branches -- triggers
  int m_passL1;                                 //!
  int m_passHLT;                                //!
  std::vector<std::string>* m_passedTriggers;   //!
  std::vector<std::string>* m_disabledTriggers; //!

  // JETS
  // branches -- jet basics
  int                 m_jet_n;            //!
  std::vector<float>* m_jet_pt;           //!
  std::vector<float>* m_jet_eta;          //!
  std::vector<float>* m_jet_phi;          //!
  std::vector<float>* m_jet_E;            //!
  std::vector<float>* m_jet_M;            //!
  std::vector<float>* m_jet_rapid;        //!
  std::vector<int>*   m_jet_ID;           //!
  std::vector<int>*   m_jet_index;        //!
  // branches -- jet energy
  std::vector<float>* m_jet_hecFrac;      //!
  std::vector<float>* m_jet_emFrac;       //!
  std::vector<float>* m_jet_centroidR;    //!
  std::vector<float>* m_jet_width;        //!
  // branches -- jet constituents
  std::vector<int>*   m_jet_numConstit;   //!
  // branches -- jet track moments (pv)
  std::vector<int>*   m_jet_numTrkPt10;   //!
  std::vector<float>* m_jet_sumPtTrkPt10; //!
  std::vector<float>* m_jet_trkWidthPt10; //!
  std::vector<int>*   m_jet_numTrkPt5;    //!
  std::vector<float>* m_jet_sumPtTrkPt5;  //!
  std::vector<float>* m_jet_trkWidthPt5;  //!
  std::vector<float>* m_jet_jvf;          //!
  std::vector<float>* m_jet_jvt;          //!
  // branches -- ghost tracks / truth particles
  std::vector<int>*                m_jet_ghostTrkCount;    //!
  std::vector<float>*              m_jet_ghostTrkPt;       //!
  std::vector<std::vector<int>>*   m_jet_ghostTrk_ID;      //!
  std::vector<std::vector<int>>*   m_jet_ghostTrk_index;   //!
  std::vector<std::vector<float>>* m_jet_ghostTrk_eta;     //!
  std::vector<std::vector<float>>* m_jet_ghostTrk_phi;     //!
  std::vector<int>*                m_jet_ghostTruthCount;  //!
  std::vector<float>*              m_jet_ghostTruthPt;     //!
  std::vector<std::vector<int>>*   m_jet_ghostTruth_ID;    //!
  std::vector<std::vector<int>>*   m_jet_ghostTruth_index; //!
  std::vector<std::vector<int>>*   m_jet_ghostTruth_pdgId; //!
  std::vector<std::vector<float>>* m_jet_ghostTruth_eta;   //!
  std::vector<std::vector<float>>* m_jet_ghostTruth_phi;   //!
  // branches -- jet matched tracks / truth particles
  std::vector<int>*                m_jet_trkCount;  //!
  std::vector<float>*              m_jet_trkPt;     //!
  std::vector<std::vector<int>>*   m_jet_trk_ID;    //!
  std::vector<std::vector<int>>*   m_jet_trk_index; //!
  std::vector<std::vector<float>>* m_jet_trk_dR;    //!
  std::vector<int>*                m_jet_tpCount;   //!
  std::vector<float>*              m_jet_tpPt;      //!
  std::vector<std::vector<int>>*   m_jet_tp_ID;     //!
  std::vector<std::vector<int>>*   m_jet_tp_index;  //!
  std::vector<std::vector<int>>*   m_jet_tp_pdgId;  //!
  std::vector<std::vector<float>>* m_jet_tp_dR;     //!
  // branches -- jet matched secondary / truth vertices
  std::vector<int>*                      m_jet_secVtxCount;    //!
  std::vector<float>*                    m_jet_secVtxPt;       //!
  std::vector<std::vector<int>>*         m_jet_secVtx_ID;      //!
  std::vector<std::vector<int>>*         m_jet_secVtx_index;   //!
  std::vector<std::vector<float>>*       m_jet_secVtx_dR;      //!
  std::vector<int>*                      m_jet_truthVtxCount;  //!
  std::vector<float>*                    m_jet_truthVtxPt;     //!
  std::vector<std::vector<int>>*         m_jet_truthVtx_ID;    //!
  std::vector<std::vector<int>>*         m_jet_truthVtx_index; //!
  std::vector<std::vector<std::string>>* m_jet_truthVtx_llp;   //!
  std::vector<std::vector<float>>*       m_jet_truthVtx_dR;    //!
   // branches -- truth jet matching
  std::vector<uint8_t>* m_jet_isTruthMatched;   //!
  std::vector<int>*     m_jet_truthMatch_ID;    //!
  std::vector<int>*     m_jet_truthMatch_index; //!
  std::vector<float>*   m_jet_truthMatch_dR;    //!
  std::vector<uint8_t>* m_jet_isDarkMatched;    //!
  std::vector<int>*     m_jet_darkMatch_ID;     //!
  std::vector<int>*     m_jet_darkMatch_index;  //!
  std::vector<float>*   m_jet_darkMatch_dR;     //!

  // TRUTH JETS
  // branches -- truth jet basics
  int                 m_truthJet_n;     //!
  std::vector<float>* m_truthJet_pt;    //!
  std::vector<float>* m_truthJet_eta;   //!
  std::vector<float>* m_truthJet_phi;   //!
  std::vector<float>* m_truthJet_E;     //!
  std::vector<float>* m_truthJet_M;     //!
  std::vector<float>* m_truthJet_rapid; //!
  std::vector<int>*   m_truthJet_ID;    //!
  std::vector<int>*   m_truthJet_index; //!
  // branches -- truth jet energy (width)
  std::vector<float>* m_truthJet_width; //!
  // branches -- truth jet constituents
  std::vector<float>*              m_truthJet_girth;          //!
  std::vector<int>*                m_truthJet_numConstit;     //!
  std::vector<float>*              m_truthJet_constitPt;      //!
  std::vector<std::vector<int>>*   m_truthJet_constit_ID;     //!
  std::vector<std::vector<int>>*   m_truthJet_constit_index;  //!
  std::vector<std::vector<float>>* m_truthJet_constit_pt;     //!
  std::vector<std::vector<float>>* m_truthJet_constit_charge; //!
  std::vector<std::vector<float>>* m_truthJet_constit_dR;     //!
  std::vector<std::vector<float>>* m_truthJet_constit_pVtx_r; //!
  // branches -- truth jet matched tracks / truth particles
  std::vector<int>*                      m_truthJet_trkCount;       //!
  std::vector<float>*                    m_truthJet_trkPt;          //!
  std::vector<std::vector<int>>*         m_truthJet_trk_ID;         //!
  std::vector<std::vector<int>>*         m_truthJet_trk_index;      //!
  std::vector<std::vector<float>>*       m_truthJet_trk_dR;         //!
  std::vector<int>*                      m_truthJet_tpCount;        //!
  std::vector<float>*                    m_truthJet_tpPt;           //!
  std::vector<std::vector<int>>*         m_truthJet_tp_ID;          //!
  std::vector<std::vector<int>>*         m_truthJet_tp_index;       //!
  std::vector<std::vector<float>>*       m_truthJet_tp_pt;          //!
  std::vector<std::vector<float>>*       m_truthJet_tp_charge;      //!
  std::vector<std::vector<int>>*         m_truthJet_tp_pdgId;       //!
  std::vector<std::vector<float>>*       m_truthJet_tp_dR;          //!
  std::vector<std::vector<uint8_t>>*     m_truthJet_tp_isStable;    //!
  std::vector<std::vector<uint8_t>>*     m_truthJet_tp_isDark;      //!
  // branches -- truth jet matched secondary / truth vertices
  std::vector<int>*                      m_truthJet_secVtxCount;    //!
  std::vector<float>*                    m_truthJet_secVtxPt;       //!
  std::vector<std::vector<int>>*         m_truthJet_secVtx_ID;      //!
  std::vector<std::vector<int>>*         m_truthJet_secVtx_index;   //!
  std::vector<std::vector<float>>*       m_truthJet_secVtx_dR;      //!
  std::vector<int>*                      m_truthJet_truthVtxCount;  //!
  std::vector<float>*                    m_truthJet_truthVtxPt;     //!
  std::vector<std::vector<int>>*         m_truthJet_truthVtx_ID;    //!
  std::vector<std::vector<int>>*         m_truthJet_truthVtx_index; //!
  std::vector<std::vector<std::string>>* m_truthJet_truthVtx_llp;   //!
  std::vector<std::vector<float>>*       m_truthJet_truthVtx_r;     //!
  std::vector<std::vector<float>>*       m_truthJet_truthVtx_mass;  //!
  std::vector<std::vector<float>>*       m_truthJet_truthVtx_dR;    //!
  // branches -- truth dark / reco jet matching
  std::vector<uint8_t>* m_truthJet_isDarkMatched;   //!
  std::vector<int>*     m_truthJet_darkMatch_ID;    //!
  std::vector<int>*     m_truthJet_darkMatch_index; //!
  std::vector<float>*   m_truthJet_darkMatch_dR;    //!
  std::vector<uint8_t>* m_truthJet_isRecoMatch;     //!
  std::vector<int>*     m_truthJet_recoMatch_ID;    //!
  std::vector<int>*     m_truthJet_recoMatch_index; //!
  std::vector<float>*   m_truthJet_recoMatch_dR;    //!

  // DARK JETS
  // branches -- dark jet basics
  int                 m_darkJet_n;     //!
  std::vector<float>* m_darkJet_pt;    //!
  std::vector<float>* m_darkJet_eta;   //!
  std::vector<float>* m_darkJet_phi;   //!
  std::vector<float>* m_darkJet_E;     //!
  std::vector<float>* m_darkJet_M;     //!
  std::vector<float>* m_darkJet_rapid; //!
  std::vector<int>*   m_darkJet_ID;    //!
  std::vector<int>*   m_darkJet_index; //!
  // branches -- dark jet energy (width)
  std::vector<float>* m_darkJet_width; //!
  // branches -- dark jet constituents
  std::vector<float>*              m_darkJet_girth;          //!
  std::vector<int>*                m_darkJet_numConstit;     //!
  std::vector<float>*              m_darkJet_constitPt;      //!
  std::vector<std::vector<int>>*   m_darkJet_constit_ID;     //!
  std::vector<std::vector<int>>*   m_darkJet_constit_index;  //!
  std::vector<std::vector<float>>* m_darkJet_constit_pt;     //!
  std::vector<std::vector<float>>* m_darkJet_constit_charge; //!
  std::vector<std::vector<float>>* m_darkJet_constit_dR;     //!
  std::vector<std::vector<float>>* m_darkJet_constit_dVtx_r; //!
  // branches -- dark jet matched tracks / truth particles
  std::vector<int>*                      m_darkJet_trkCount;       //!
  std::vector<float>*                    m_darkJet_trkPt;          //!
  std::vector<std::vector<int>>*         m_darkJet_trk_ID;         //!
  std::vector<std::vector<int>>*         m_darkJet_trk_index;      //!
  std::vector<std::vector<float>>*       m_darkJet_trk_dR;         //!
  std::vector<int>*                      m_darkJet_tpCount;        //!
  std::vector<float>*                    m_darkJet_tpPt;           //!
  std::vector<std::vector<int>>*         m_darkJet_tp_ID;          //!
  std::vector<std::vector<int>>*         m_darkJet_tp_index;       //!
  std::vector<std::vector<float>>*       m_darkJet_tp_pt;          //!
  std::vector<std::vector<float>>*       m_darkJet_tp_charge;      //!
  std::vector<std::vector<int>>*         m_darkJet_tp_pdgId;       //!
  std::vector<std::vector<float>>*       m_darkJet_tp_dR;          //!
  std::vector<std::vector<uint8_t>>*     m_darkJet_tp_isStable;    //!
  std::vector<std::vector<uint8_t>>*     m_darkJet_tp_isDark;      //!
  // branches -- dark jet matched secondary / truth vertices
  std::vector<int>*                      m_darkJet_secVtxCount;    //!
  std::vector<float>*                    m_darkJet_secVtxPt;       //!
  std::vector<std::vector<int>>*         m_darkJet_secVtx_ID;      //!
  std::vector<std::vector<int>>*         m_darkJet_secVtx_index;   //!
  std::vector<std::vector<float>>*       m_darkJet_secVtx_dR;      //!
  std::vector<int>*                      m_darkJet_truthVtxCount;  //!
  std::vector<float>*                    m_darkJet_truthVtxPt;     //!
  std::vector<std::vector<int>>*         m_darkJet_truthVtx_ID;    //!
  std::vector<std::vector<int>>*         m_darkJet_truthVtx_index; //!
  std::vector<std::vector<std::string>>* m_darkJet_truthVtx_llp;   //!
  std::vector<std::vector<float>>*       m_darkJet_truthVtx_r;     //!
  std::vector<std::vector<float>>*       m_darkJet_truthVtx_mass;  //!
  std::vector<std::vector<float>>*       m_darkJet_truthVtx_dR;    //!
  // branches -- dark dark / reco jet matching
  std::vector<uint8_t>* m_darkJet_isTruthMatch;     //!
  std::vector<int>*     m_darkJet_truthMatch_ID;    //!
  std::vector<int>*     m_darkJet_truthMatch_index; //!
  std::vector<float>*   m_darkJet_truthMatch_dR;    //!
  std::vector<uint8_t>* m_darkJet_isRecoMatch;      //!
  std::vector<int>*     m_darkJet_recoMatch_ID;     //!
  std::vector<int>*     m_darkJet_recoMatch_index;  //!
  std::vector<float>*   m_darkJet_recoMatch_dR;     //!

  // TRUTH PARTICLES
  // branches -- truth particle basics
  int                            m_tp_n;             //!
  std::vector<int>*              m_tp_ID;            //!
  std::vector<int>*              m_tp_index;         //!
  std::vector<float>*            m_tp_pt;            //!
  std::vector<float>*            m_tp_eta;           //!
  std::vector<float>*            m_tp_phi;           //!
  std::vector<float>*            m_tp_E;             //!
  std::vector<float>*            m_tp_M;             //!
  std::vector<float>*            m_tp_charge;        //!
  std::vector<int>*              m_tp_pdgId;         //!
  std::vector<int>*              m_tp_status;        //!
  std::vector<uint8_t>*          m_tp_isStable;      //!
  std::vector<uint8_t>*          m_tp_isDark;        //!
  std::vector<int>*              m_tp_nParents;      //!
  std::vector<std::vector<int>>* m_tp_parent_pdgId;  //!
  std::vector<std::vector<int>>* m_tp_parent_status; //!
  std::vector<int>*              m_tp_nChildren;     //!
  std::vector<std::vector<int>>* m_tp_child_pdgId;   //!
  std::vector<std::vector<int>>* m_tp_child_status;  //!
  std::vector<uint8_t>*          m_tp_hasPVtx;       //!
  std::vector<float>*            m_tp_pVtx_r;        //!
  std::vector<uint8_t>*          m_tp_hasDVtx;       //!
  std::vector<float>*            m_tp_dVtx_r;        //!

  // SECONDARY VERTICES
  // branches -- secondary vertex basics
  int                              m_secVtx_n;             //!
  std::vector<int>*                m_secVtx_ID;            //!
  std::vector<int>*                m_secVtx_index;         //!
  std::vector<float>*              m_secVtx_x;             //!
  std::vector<float>*              m_secVtx_y;             //!
  std::vector<float>*              m_secVtx_z;             //!
  std::vector<float>*              m_secVtx_r;             //!
  std::vector<float>*              m_secVtx_pt;            //!
  std::vector<float>*              m_secVtx_eta;           //!
  std::vector<float>*              m_secVtx_phi;           //!
  std::vector<float>*              m_secVtx_mass;          //!
  std::vector<float>*              m_secVtx_mass_nonAssoc; //!
  std::vector<float>*              m_secVtx_chi2;          //!
  std::vector<float>*              m_secVtx_direction;     //!
  std::vector<int>*                m_secVtx_charge;        //!
  std::vector<float>*              m_secVtx_Ht;            //!
  std::vector<float>*              m_secVtx_minOpAng;      //!
  std::vector<float>*              m_secVtx_maxOpAng;      //!
  std::vector<float>*              m_secVtx_mind0;         //!
  std::vector<float>*              m_secVtx_maxd0;         //!
  std::vector<std::vector<float>>* m_secVtx_twoTrkMass;    //!
  std::vector<uint32_t>*           m_secVtx_ntrk;          //!
  std::vector<uint32_t>*           m_secVtx_ntrk_sel;      //!
  std::vector<uint32_t>*           m_secVtx_ntrk_assoc;    //!

  // TRUTH VERTICES
  // branches -- truth vertex basics
  int                       m_truthVtx_n;     //!
  std::vector<int>*         m_truthVtx_ID;    //!
  std::vector<int>*         m_truthVtx_index; //!
  std::vector<std::string>* m_truthVtx_llp;   //!
  std::vector<float>*       m_truthVtx_x;     //!
  std::vector<float>*       m_truthVtx_y;     //!
  std::vector<float>*       m_truthVtx_z;     //!
  std::vector<float>*       m_truthVtx_r;     //!
  std::vector<float>*       m_truthVtx_pt;    //!
  std::vector<float>*       m_truthVtx_eta;   //!
  std::vector<float>*       m_truthVtx_phi;   //!
  std::vector<float>*       m_truthVtx_mass;  //!
  std::vector<int>*         m_truthVtx_nOutP; //!
  
  

  // --- HISTOGRAMS --- //

  // EVENTS
  // histograms -- event info
  std::vector<TH1F*> h_npv;       //!
  std::vector<TH1F*> h_actualMu;  //!
  std::vector<TH1F*> h_averageMu; //!
  std::vector<TH1F*> h_njetHt;    //!
  // histograms -- primary vertex
  std::vector<TH1F*> h_pv_x;      //!
  std::vector<TH1F*> h_pv_y;      //!
  std::vector<TH1F*> h_pv_z;      //!
  std::vector<TH1F*> h_pv_r;      //!
  std::vector<TH1F*> h_pv_phi;    //!
  std::vector<TH1F*> h_pv_ntrk;   //!

  // JETS
  // histograms -- jet basics
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
  // histograms -- jet kinematics
  std::vector<TH1F*> h_jet_px;    //!
  std::vector<TH1F*> h_jet_py;    //!
  std::vector<TH1F*> h_jet_pz;    //!
  std::vector<TH1F*> h_jet_Et;    //!
  std::vector<TH1F*> h_jet_Et_l;  //!
  std::vector<TH1F*> h_jet_Et_m;  //!
  std::vector<TH1F*> h_jet_Et_s;  //!
  // histograms -- leading jets
  std::vector<std::vector<TH1F*>> h_jetN_pt;    //!
  std::vector<std::vector<TH1F*>> h_jetN_pt_l;  //!
  std::vector<std::vector<TH1F*>> h_jetN_pt_m;  //!
  std::vector<std::vector<TH1F*>> h_jetN_pt_s;  //!
  std::vector<std::vector<TH1F*>> h_jetN_eta;   //!
  std::vector<std::vector<TH1F*>> h_jetN_phi;   //!
  std::vector<std::vector<TH1F*>> h_jetN_E;     //!
  std::vector<std::vector<TH1F*>> h_jetN_M;     //!
  std::vector<std::vector<TH1F*>> h_jetN_rapid; //!
  // histograms -- leading jet kinematics
  std::vector<std::vector<TH1F*>> h_jetN_Et;    //!
  std::vector<std::vector<TH1F*>> h_jetN_Et_l;  //!
  std::vector<std::vector<TH1F*>> h_jetN_Et_m;  //!
  std::vector<std::vector<TH1F*>> h_jetN_Et_s;  //!
  // histograms -- jet energy
  std::vector<TH1F*> h_jet_hecFrac;    //!
  std::vector<TH1F*> h_jet_emFrac;     //!
  std::vector<TH1F*> h_jet_centroidR;  //!
  std::vector<TH1F*> h_jet_width;      //!
  // histograms -- jet constituents
  std::vector<TH1F*> h_jet_numConstit; //!
  // histograms -- track moments (PV)
  std::vector<TH1F*> h_jet_numTrkPt10;   //!
  std::vector<TH1F*> h_jet_sumPtTrkPt10; //!
  std::vector<TH1F*> h_jet_trkWidthPt10; //!
  std::vector<TH1F*> h_jet_numTrkPt5;    //!
  std::vector<TH1F*> h_jet_sumPtTrkPt5;  //!
  std::vector<TH1F*> h_jet_trkWidthPt5;  //!
  std::vector<TH1F*> h_jet_jvf;          //!
  std::vector<TH1F*> h_jet_jvt;          //!
  // histograms -- ghost tracks / truth particles
  std::vector<TH1F*> h_jet_ghostTrkCount;   //!
  std::vector<TH1F*> h_jet_ghostTrkPt;      //!
  std::vector<TH1F*> h_jet_ghostTrk_dR;     //!
  std::vector<TH1F*> h_jet_ghostTruthCount; //!
  std::vector<TH1F*> h_jet_ghostTruthPt;    //!
  std::vector<TH1F*> h_jet_ghostTruth_dR;   //!
  // histograms -- jet matched tracks / truth particles
  std::vector<TH1F*> h_jet_trkCount;        //!
  std::vector<TH1F*> h_jet_trkPt;           //!
  std::vector<TH1F*> h_jet_trk_dR;          //!
  std::vector<TH1F*> h_jet_tpCount;         //!
  std::vector<TH1F*> h_jet_tpPt;            //!
  std::vector<TH1F*> h_jet_tp_dR;           //!
  // histograms -- jet matched vertices
  std::vector<TH1F*> h_jet_secVtxCount;     //!
  std::vector<TH1F*> h_jet_secVtxPt;        //!
  std::vector<TH1F*> h_jet_secVtx_dR;       //!
  std::vector<TH1F*> h_jet_truthVtxCount;   //!
  std::vector<TH1F*> h_jet_truthVtxPt;      //!
  std::vector<TH1F*> h_jet_truthVtx_dR;     //!
  // histograms -- jets vs pileup --> ADD THE REST (pt, matched track/vertices, etc.)
  std::vector<TH2F*> h_jet_n_vs_avgMu; //!
  std::vector<TH2F*> h_jet_n_vs_actMu; //!

  // n matched trks, vertices w/in different dRs
  // matched trk, vtx basics (including corresponding truth) ??
  // n / fraction matched specific tps, truth vertices (i.e. dark pion (decays) ??)

  // dark-matched vs not-dark-matched jets
  // --> also look at jets that are both matched to dark jets and matched to truth jets that are matched to dark jets...

  // TRUTH JETS
  // histograms -- truth jet basics
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
  // histograms -- truth truthJet kinematics
  std::vector<TH1F*> h_truthJet_px;    //!
  std::vector<TH1F*> h_truthJet_py;    //!
  std::vector<TH1F*> h_truthJet_pz;    //!
  std::vector<TH1F*> h_truthJet_Et;    //!
  std::vector<TH1F*> h_truthJet_Et_l;  //!
  std::vector<TH1F*> h_truthJet_Et_m;  //!
  std::vector<TH1F*> h_truthJet_Et_s;  //!
  // histograms -- leading truth jets
  std::vector<std::vector<TH1F*>> h_truthJetN_pt;    //!
  std::vector<std::vector<TH1F*>> h_truthJetN_pt_l;  //!
  std::vector<std::vector<TH1F*>> h_truthJetN_pt_m;  //!
  std::vector<std::vector<TH1F*>> h_truthJetN_pt_s;  //!
  std::vector<std::vector<TH1F*>> h_truthJetN_eta;   //!
  std::vector<std::vector<TH1F*>> h_truthJetN_phi;   //!
  std::vector<std::vector<TH1F*>> h_truthJetN_E;     //!
  std::vector<std::vector<TH1F*>> h_truthJetN_M;     //!
  std::vector<std::vector<TH1F*>> h_truthJetN_rapid; //!
  // histograms -- leading truth jet kinematics
  std::vector<std::vector<TH1F*>> h_truthJetN_Et;    //!
  std::vector<std::vector<TH1F*>> h_truthJetN_Et_l;  //!
  std::vector<std::vector<TH1F*>> h_truthJetN_Et_m;  //!
  std::vector<std::vector<TH1F*>> h_truthJetN_Et_s;  //!
  // histograms -- truth jet energy (width)
  std::vector<TH1F*> h_truthJet_width; //!
  // histograms -- truth jet constituents
  std::vector<TH1F*> h_truthJet_girth;             //!
  std::vector<TH1F*> h_truthJet_nConstit;          //!
  std::vector<TH1F*> h_truthJet_constitPt;         //!
  std::vector<TH1F*> h_truthJet_constit_dR;        //!
  std::vector<TH1F*> h_truthJet_constit_pVtx_r;    //!
  std::vector<TH1F*> h_truthJet_nChrgConstit;      //!
  std::vector<TH1F*> h_truthJet_nVisConstit;       //!
  // histograms -- truth jet matched tracks / truth particles
  std::vector<TH1F*> h_truthJet_trkCount;          //!
  std::vector<TH1F*> h_truthJet_trkPt;             //!
  std::vector<TH1F*> h_truthJet_trk_dR;            //!
  std::vector<TH1F*> h_truthJet_tpCount;           //!
  std::vector<TH1F*> h_truthJet_tpPt;              //!
  std::vector<TH1F*> h_truthJet_tp_dR;             //!
  std::vector<TH1F*> h_truthJet_chrgTpCount;       //!
  std::vector<TH1F*> h_truthJet_visTpCount;        //!
  std::vector<TH1F*> h_truthJet_darkTpCount;       //!
  std::vector<TH1F*> h_truthJet_pidTpCount;        //!
  // histograms -- truth jet matched secondary / truth vertices
  std::vector<TH1F*> h_truthJet_secVtxCount;       //!
  std::vector<TH1F*> h_truthJet_secVtxPt;          //!
  std::vector<TH1F*> h_truthJet_secVtx_dR;         //!
  std::vector<TH1F*> h_truthJet_truthVtxCount;     //!
  std::vector<TH1F*> h_truthJet_truthVtxPt;        //!
  std::vector<TH1F*> h_truthJet_truthVtx_dR;       //!
  std::vector<TH1F*> h_truthJet_truthVtx_r;        //!
  std::vector<TH1F*> h_truthJet_truthVtx_mass;     //!
  std::vector<TH1F*> h_truthJet_pidTruthVtxCount;  //!
  std::vector<TH1F*> h_truthJet_dispTruthVtxCount; //!

  // dark-matched vs not-dark-matched truth jets

  // DARK JETS
  // histograms -- dark jet basics
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
  // histograms -- dark jet kinematics
  std::vector<TH1F*> h_darkJet_px;    //!
  std::vector<TH1F*> h_darkJet_py;    //!
  std::vector<TH1F*> h_darkJet_pz;    //!
  std::vector<TH1F*> h_darkJet_Et;    //!
  std::vector<TH1F*> h_darkJet_Et_l;  //!
  std::vector<TH1F*> h_darkJet_Et_m;  //!
  std::vector<TH1F*> h_darkJet_Et_s;  //!
  // histograms -- leading dark jets
  std::vector<std::vector<TH1F*>> h_darkJetN_pt;    //!
  std::vector<std::vector<TH1F*>> h_darkJetN_pt_l;  //!
  std::vector<std::vector<TH1F*>> h_darkJetN_pt_m;  //!
  std::vector<std::vector<TH1F*>> h_darkJetN_pt_s;  //!
  std::vector<std::vector<TH1F*>> h_darkJetN_eta;   //!
  std::vector<std::vector<TH1F*>> h_darkJetN_phi;   //!
  std::vector<std::vector<TH1F*>> h_darkJetN_E;     //!
  std::vector<std::vector<TH1F*>> h_darkJetN_M;     //!
  std::vector<std::vector<TH1F*>> h_darkJetN_rapid; //!
  // histograms -- leading dark jet kinematics
  std::vector<std::vector<TH1F*>> h_darkJetN_Et;    //!
  std::vector<std::vector<TH1F*>> h_darkJetN_Et_l;  //!
  std::vector<std::vector<TH1F*>> h_darkJetN_Et_m;  //!
  std::vector<std::vector<TH1F*>> h_darkJetN_Et_s;  //!
  // histograms -- dark jet energy (width)
  std::vector<TH1F*> h_darkJet_width; //!
  // histograms -- dark jet constituents
  std::vector<TH1F*> h_darkJet_girth;          //!
  std::vector<TH1F*> h_darkJet_nConstit;       //!
  std::vector<TH1F*> h_darkJet_constitPt;      //!
  std::vector<TH1F*> h_darkJet_constit_dR;     //!
  std::vector<TH1F*> h_darkJet_constit_dVtx_r; //!
  std::vector<TH1F*> h_darkJet_nChrgConstit;   //!
  std::vector<TH1F*> h_darkJet_nVisConstit;    //!
  // histograms -- dark jet matched tracks / truth particles
  std::vector<TH1F*> h_darkJet_trkCount;          //!
  std::vector<TH1F*> h_darkJet_trkPt;             //!
  std::vector<TH1F*> h_darkJet_trk_dR;            //!
  std::vector<TH1F*> h_darkJet_tpCount;           //!
  std::vector<TH1F*> h_darkJet_tpPt;              //!
  std::vector<TH1F*> h_darkJet_tp_dR;             //!
  std::vector<TH1F*> h_darkJet_chrgTpCount;       //!
  std::vector<TH1F*> h_darkJet_visTpCount;        //!
  std::vector<TH1F*> h_darkJet_darkTpCount;       //!
  std::vector<TH1F*> h_darkJet_pidTpCount;        //!
  // histograms -- dark jet matched secondary / truth vertices
  std::vector<TH1F*> h_darkJet_secVtxCount;       //!
  std::vector<TH1F*> h_darkJet_secVtxPt;          //!
  std::vector<TH1F*> h_darkJet_secVtx_dR;         //!
  std::vector<TH1F*> h_darkJet_truthVtxCount;     //!
  std::vector<TH1F*> h_darkJet_truthVtxPt;        //!
  std::vector<TH1F*> h_darkJet_truthVtx_dR;       //!
  std::vector<TH1F*> h_darkJet_truthVtx_r;        //!
  std::vector<TH1F*> h_darkJet_truthVtx_mass;     //!
  std::vector<TH1F*> h_darkJet_pidTruthVtxCount;  //!
  std::vector<TH1F*> h_darkJet_dispTruthVtxCount; //!

  // TRACKS
  // histograms -- track basics

  // TRUTH PARTICLES
  // histograms -- truth particle basics
  std::vector<TH1F*> h_tp_n;            //!
  std::vector<TH1F*> h_tp_pt;           //!
  std::vector<TH1F*> h_tp_eta;          //!
  std::vector<TH1F*> h_tp_phi;          //!
  std::vector<TH1F*> h_tp_E;            //!
  std::vector<TH1F*> h_tp_M;            //!
  std::vector<TH1F*> h_tp_sumPt;        //!
  std::vector<TH1F*> h_tp_nCharged;     //!
  std::vector<TH1F*> h_tp_chargedSumPt; //!
  std::vector<TH1F*> h_tp_nVisible;     //!
  std::vector<TH1F*> h_tp_visibleSumPt; //!
  std::vector<TH1F*> h_tp_nDark;        //!
  std::vector<TH1F*> h_tp_darkSumPt;    //!
  // histograms -- truth particle kinematics --> ADD !!!
  std::vector<TH1F*> h_tp_px;           //!
  std::vector<TH1F*> h_tp_py;           //!
  std::vector<TH1F*> h_tp_pz;           //!
  std::vector<TH1F*> h_tp_Et;           //!
  std::vector<TH1F*> h_tp_Et_l;         //!
  std::vector<TH1F*> h_tp_Et_m;         //!
  std::vector<TH1F*> h_tp_Et_s;         //!
  // histograms -- heavy scalar mediator (Xd) truth particles
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
  std::vector<TH1F*> h_Xd_sumPt;        //!
  // histograms -- dark quark (qd) truth particles
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
  std::vector<TH1F*> h_qd_sumPt;        //!
  // histograms -- dark pion (pid) truth particles
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
  std::vector<TH1F*> h_pid_sumPt;        //!
  // histograms -- dark rho (rhod) truth particles
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
  std::vector<TH1F*> h_rhod_sumPt;        //!

  // SECONDARY VERTICES
  // histograms -- secondary vertex basics
  std::vector<TH1F*> h_secVtx_n;               //!
  std::vector<TH1F*> h_secVtx_x;               //!
  std::vector<TH1F*> h_secVtx_y;               //!
  std::vector<TH1F*> h_secVtx_z;               //!
  std::vector<TH1F*> h_secVtx_r;               //!
  std::vector<TH1F*> h_secVtx_r_l;             //!
  std::vector<TH1F*> h_secVtx_r_s;             //!
  std::vector<TH1F*> h_secVtx_pt;              //!
  std::vector<TH1F*> h_secVtx_eta;             //!
  std::vector<TH1F*> h_secVtx_phi;             //!
  std::vector<TH1F*> h_secVtx_mass;            //!
  std::vector<TH1F*> h_secVtx_mass_l;          //!
  std::vector<TH1F*> h_secVtx_mass_s;          //!
  std::vector<TH1F*> h_secVtx_mass_nonAssoc;   //!
  std::vector<TH1F*> h_secVtx_mass_nonAssoc_l; //!
  std::vector<TH1F*> h_secVtx_mass_nonAssoc_s; //!
  std::vector<TH1F*> h_secVtx_chi2;            //!
  std::vector<TH1F*> h_secVtx_direction;       //!
  std::vector<TH1F*> h_secVtx_charge;          //!
  std::vector<TH1F*> h_secVtx_Ht;              //!
  std::vector<TH1F*> h_secVtx_minOpAng;        //!
  std::vector<TH1F*> h_secVtx_maxOpAng;        //!
  std::vector<TH1F*> h_secVtx_mind0;           //!
  std::vector<TH1F*> h_secVtx_maxd0;           //!
  std::vector<TH1F*> h_secVtx_twoTrkMass;      //!
  std::vector<TH1F*> h_secVtx_twoTrkMass_l;    //!
  std::vector<TH1F*> h_secVtx_twoTrkMass_s;    //!
  std::vector<TH1F*> h_secVtx_ntrk;            //!
  std::vector<TH1F*> h_secVtx_ntrk_sel;        //!
  std::vector<TH1F*> h_secVtx_ntrk_assoc;      //!
  // histograms -- n-trk secondary vertices
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
  // histograms -- n-sel/non-assoc secondary vertices --> ADD
  // associated tracks
  // close to / matched to truth dark pion decays
  
  // TRUTH VERTICES
  // histograms -- truth vertex basics
  std::vector<TH1F*> h_truthVtx_n;     //!
  std::vector<TH1F*> h_truthVtx_x;     //!
  std::vector<TH1F*> h_truthVtx_y;     //!
  std::vector<TH1F*> h_truthVtx_z;     //!
  std::vector<TH1F*> h_truthVtx_r;     //!
  std::vector<TH1F*> h_truthVtx_pt;    //!
  std::vector<TH1F*> h_truthVtx_eta;   //!
  std::vector<TH1F*> h_truthVtx_phi;   //!
  std::vector<TH1F*> h_truthVtx_mass;  //!
  std::vector<TH1F*> h_truthVtx_nOutP; //!
  // dark pion decay vertex basics
  std::vector<TH1F*> h_truthVtxPid_n;     //!
  std::vector<TH1F*> h_truthVtxPid_x;     //!
  std::vector<TH1F*> h_truthVtxPid_y;     //!
  std::vector<TH1F*> h_truthVtxPid_z;     //!
  std::vector<TH1F*> h_truthVtxPid_r;     //!
  std::vector<TH1F*> h_truthVtxPid_pt;    //!
  std::vector<TH1F*> h_truthVtxPid_eta;   //!
  std::vector<TH1F*> h_truthVtxPid_phi;   //!
  std::vector<TH1F*> h_truthVtxPid_mass;  //!
  std::vector<TH1F*> h_truthVtxPid_nOutP; //!
  // descendants, physical positions, close / matched reco vertices (see VsiPerf efficiency processor)


  // objects vs pileup
  
};

#endif // EJsAnalysis_EJsHistogramManager_H
