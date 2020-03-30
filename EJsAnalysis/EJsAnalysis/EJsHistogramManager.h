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
			  const std::string& jetHistName,  const EJsHelper::BaseDV& base_dv );
  StatusCode execute    ( TTree* tree, Long64_t treeEntry, const std::vector<EJsHelper::Region>& regions,
			  const EJsHelper::BaseDV& base_dv );
  StatusCode finalize   ( const std::vector<EJsHelper::Region>& regions );

  using HistogramManager::book;       // overload
  using HistogramManager::initialize; // overload
  using HistogramManager::execute;    // overload
  using HistogramManager::finalize;   // overload

  void getJetTypes ( int jet_index, std::vector<int>& jet );
  void getTrkTypes ( int trk_index, std::vector<int>& trk, const EJsHelper::BaseDV& base_dv );
  void getDVTypes  ( int dv_index,  std::vector<int>& dv,  const EJsHelper::BaseDV& base_dv,
		     bool jetDV = false, bool doCombos = true, bool doGood = true, bool doGoodCuts = false );


 protected:
  // holds bools that controls which histograms are filled
  EJsHelperClasses::HistogramInfoSwitch* m_histoInfoSwitch;

 private:
  std::string      m_jetStr;
  std::string      m_jetStrOth;
  float            m_nEvents_init;
  float            m_nEvents_sel;
  float            m_sumw_init;
  float            m_sumw_sel;
  float            m_sumw2_init;
  float            m_sumw2_sel;
  float            m_xsec;
  float            m_kfactor;
  float            m_filteff;
  float            m_lumi;
  bool             m_debug;
  bool             m_mc;
  bool             m_unblind; // un-blind analysis -- default = False to blind signal events in data
  int              m_numLeadJets;
  int              m_numVtxTrks;

  float weight = 1.0;
  float lumi   = 139.; // [fb-1]  

  // counters
  unsigned m_LJix       = 0;
  unsigned m_nTypeJs    = 0;
  unsigned m_nTypeBJs   = 0;
  unsigned m_nTypeTrks  = 0;
  unsigned m_nTypeDVs   = 0;
  unsigned m_nType1DVs  = 0;
  unsigned m_nTypeBDVs  = 0;
  unsigned m_nTypeJDVs  = 0;
  unsigned m_nType1JDVs = 0;
  unsigned m_nTypeBJDVs = 0;
  std::vector<int>   m_nEntries;
  std::vector<float> m_nWeightedEntries;
  std::vector<int>   m_nFourJets;
  std::vector<int>   m_nSearch;
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
  // ABCD VR shift values
  double m_VRshift_njetHt = 4./3;
  // nDV test cuts
  int m_ndv = 7;


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
  uint8_t  m_searchMinusOne;      //!
  uint8_t  m_search;              //!
  uint8_t  m_signal;              //!
  uint8_t  m_valid;               //!
  float    m_njetHt;              //!
  uint8_t  m_signal_njet;         //!
  uint8_t  m_signal_jetPt;        //!
  uint8_t  m_signal_jetEta;       //!
  uint8_t  m_signal_njetHt;       //!
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
  int m_jet_n;                         //!
  std::vector<int>*   m_jet_ID;        //!
  std::vector<int>*   m_jet_index;     //!
  std::vector<float>* m_jet_pt;        //!
  std::vector<float>* m_jet_eta;       //!
  std::vector<float>* m_jet_phi;       //!
  std::vector<float>* m_jet_E;         //!
  std::vector<float>* m_jet_M;         //!
  std::vector<float>* m_jet_rapid;     //!
  std::vector<int>*   m_jet_nConstits; //!
  std::vector<int>*   m_jet_passJVT;   //!
  // jets: calo / cluster (quality) info
  std::vector<float>* m_jet_timing;             //!
  std::vector<float>* m_jet_LArQual;            //!
  std::vector<float>* m_jet_HECQual;            //!
  std::vector<float>* m_jet_avgLArQF;           //!
  std::vector<float>* m_jet_n90Constits;        //!
  std::vector<float>* m_jet_centroidR;          //!
  std::vector<float>* m_jet_ootFracClust5;      //!
  std::vector<float>* m_jet_ootFracClust10;     //!
  std::vector<float>* m_jet_fracSampMax;        //!
  std::vector<float>* m_jet_fracSampMaxIx;      //!
  std::vector<float>* m_jet_leadClustPt;        //!
  std::vector<float>* m_jet_leadClustCtrLambda; //!
  std::vector<float>* m_jet_leadClust2ndLambda; //!
  std::vector<float>* m_jet_leadClust2ndR;      //!
  std::vector<float>* m_jet_EMFrac;             //!
  std::vector<float>* m_jet_HECFrac;            //!
  std::vector<float>* m_jet_width;              //!
  // jets: track moments (PV)
  std::vector<int>*   m_jet_ntrkPt10;     //!
  std::vector<float>* m_jet_sumPtTrkPt10; //!
  std::vector<float>* m_jet_trkWidthPt10; //!
  std::vector<int>*   m_jet_ntrkPt5;      //!
  std::vector<float>* m_jet_sumPtTrkPt5;  //!
  std::vector<float>* m_jet_trkWidthPt5;  //!
  std::vector<float>* m_jet_JVF;          //!
  // jets: truth / b-tagging info
  std::vector<int>*   m_jet_partonID; //!
  // jets: dR-matched (dark) truth
  std::vector<uint8_t>* m_jet_isDark;     //!
  std::vector<int>*     m_jet_darkID;     //!
  std::vector<int>*     m_jet_darkIndex;  //!
  std::vector<float>*   m_jet_darkDR;     //!
  std::vector<uint8_t>* m_jet_isTruth;    //!
  std::vector<int>*     m_jet_truthID;    //!
  std::vector<int>*     m_jet_truthIndex; //!
  std::vector<float>*   m_jet_truthDR;    //!
  // jets: ghost tracks
  std::vector<int>*   m_jet_ghostTrk_n;                //!
  std::vector<std::vector<int>>* m_jet_ghostTrk_ID;    //!
  std::vector<std::vector<int>>* m_jet_ghostTrk_index; //!
  // jets: dR-matched tracks
  std::vector<int>*                m_jet_trk_n;        //!
  std::vector<std::vector<int>>*   m_jet_trk_ID;       //!
  std::vector<std::vector<int>>*   m_jet_trk_index;    //!
  std::vector<std::vector<float>>* m_jet_trk_dR;       //! 
  // jets: dR-matched secondary vertices
  std::vector<int>*                m_jet_secVtx_n;     //!
  std::vector<std::vector<int>>*   m_jet_secVtx_ID;    //!
  std::vector<std::vector<int>>*   m_jet_secVtx_index; //!
  std::vector<std::vector<float>>* m_jet_secVtx_dR;    //!
  // other jets: for trigger study
  int m_jetOth_n;                       //!
  std::vector<float>* m_jetOth_pt;      //!
  std::vector<float>* m_jetOth_eta;     //!
  std::vector<int>*   m_jetOth_passJVT; //!

  // TRUTH JET BRANCHES
  // truth jets: basics / kinematics
  int m_truthJet_n;                   //!
  std::vector<int>* m_truthJet_ID;    //!
  std::vector<int>* m_truthJet_index; //!
  // truth jets: matched dark
  std::vector<uint8_t>* m_truthJet_isDark;    //!
  std::vector<int>*     m_truthJet_darkID;    //!
  std::vector<int>*     m_truthJet_darkIndex; //!
  std::vector<float>*   m_truthJet_darkDR;    //!

  // DARK JET BRANCHES
  // dark jets: basics / kinematics
  int m_darkJet_n;                      //!
  std::vector<int>* m_darkJet_ID;       //!
  std::vector<int>* m_darkJet_index;    //!
  std::vector<int>* m_darkJet_nConstit; //!

  // TRACK BRANCHES
  // tracks: basics / kinematics
  int m_trk_n;                                //!
  std::vector<int>*     m_trk_ID;             //!
  std::vector<int>*     m_trk_index;          //!
  std::vector<float>*   m_trk_qOverP;         //!
  std::vector<float>*   m_trk_theta;          //!
  std::vector<float>*   m_trk_pt;             //!
  std::vector<float>*   m_trk_eta;            //!
  std::vector<float>*   m_trk_phi;            //!
  std::vector<float>*   m_trk_E;              //!
  std::vector<float>*   m_trk_M;              //!
  std::vector<float>*   m_trk_d0;             //!
  std::vector<float>*   m_trk_z0;             //!
  std::vector<float>*   m_trk_errd0;          //!
  std::vector<float>*   m_trk_errz0;          //!
  std::vector<float>*   m_trk_errP;           //!
  std::vector<float>*   m_trk_chi2;           //!
  std::vector<float>*   m_trk_chiSq;          //!
  std::vector<int>*     m_trk_ndof;           //!
  std::vector<float>*   m_trk_charge;         //!
  std::vector<uint8_t>* m_trk_isLRT;          //!
  std::vector<uint8_t>* m_trk_isSel;          //!
  std::vector<uint8_t>* m_trk_isAssoc;        //!
  std::vector<uint8_t>* m_trk_isSV;           //!
  std::vector<uint8_t>* m_trk_isCleanSV;      //!
  std::vector<uint8_t>* m_trk_isFiltSV;       //!
  std::vector<uint8_t>* m_trk_isFinalSV;      //!
  std::vector<uint8_t>* m_trk_nSCT;           //!
  std::vector<uint8_t>* m_trk_nPixel;         //!
  std::vector<uint8_t>* m_trk_nTRT;           //!
  std::vector<uint8_t>* m_trk_jetMatch;       //!
  std::vector<int>*     m_trk_jetMatch_ID;    //!
  std::vector<int>*     m_trk_jetMatch_index; //!
  std::vector<float>*   m_trk_jetMatch_dR;    //!

  // TRUTH VERTEX BRANCHES
  // truth vertices: basics / kinematics
  int m_truthVtx_n;                           //!
  std::vector<std::string>* m_truthVtx_llp;   //!
  std::vector<int>*         m_truthVtx_ID;    //!
  std::vector<int>*         m_truthVtx_index; //!
  std::vector<float>*       m_truthVtx_x;     //!
  std::vector<float>*       m_truthVtx_y;     //!
  std::vector<float>*       m_truthVtx_z;     //!
  std::vector<float>*       m_truthVtx_r;     //!
  std::vector<float>*       m_truthVtx_pt;    //!
  std::vector<float>*       m_truthVtx_eta;   //!
  std::vector<float>*       m_truthVtx_phi;   //!
  std::vector<float>*       m_truthVtx_mass;  //!
  std::vector<int>*         m_truthVtx_nOutP; //!
  // truth vertices: parents
  std::vector<int>* m_truthVtx_parent_pdgId; //!
  // truth vertices: reconstructible descendants
  std::vector<int>* m_truthVtx_nDesc;     //!
  std::vector<int>* m_truthVtx_nRecoDesc; //!
  std::vector<int>* m_truthVtx_nSelDesc;  //!
  // truth vertices: physical positions
  std::vector<int>* m_truthVtx_nPos; //!
  // truth vertices: reco matching
  std::vector<int>*                m_truthVtx_reco_n;     //!
  std::vector<std::vector<int>>*   m_truthVtx_reco_ID;    //!
  std::vector<std::vector<int>>*   m_truthVtx_reco_index; //!
  std::vector<std::vector<float>>* m_truthVtx_reco_score; //!
  std::vector<std::vector<int>>*   m_truthVtx_reco_posID; //!
  std::vector<std::vector<float>>* m_truthVtx_reco_resid; //!

  // SECONDARY VERTEX BRANCHES
  // secondary vertices: basics / kinematics
  int                 m_secVtx_n;               //!
  std::vector<int>*   m_secVtx_ID;              //!
  std::vector<int>*   m_secVtx_index;           //!
  std::vector<float>* m_secVtx_x;               //!
  std::vector<float>* m_secVtx_y;               //!
  std::vector<float>* m_secVtx_z;               //!
  std::vector<float>* m_secVtx_r;               //!
  std::vector<float>* m_secVtx_pt;              //!
  std::vector<float>* m_secVtx_eta;             //!
  std::vector<float>* m_secVtx_phi;             //!
  std::vector<float>* m_secVtx_mass;            //!
  std::vector<float>* m_secVtx_massNA;          //!
  std::vector<float>* m_secVtx_direction;       //!
  std::vector<int>*   m_secVtx_charge;          //!
  std::vector<float>* m_secVtx_H;               //!
  std::vector<float>* m_secVtx_Ht;              //!
  std::vector<float>* m_secVtx_minOpAng;        //!
  std::vector<float>* m_secVtx_maxOpAng;        //!
  std::vector<float>* m_secVtx_mind0;           //!
  std::vector<float>* m_secVtx_maxd0;           //!
  std::vector<float>* m_secVtx_pt_clean;        //!
  std::vector<float>* m_secVtx_eta_clean;       //!
  std::vector<float>* m_secVtx_phi_clean;       //!
  std::vector<float>* m_secVtx_mass_clean;      //!
  std::vector<float>* m_secVtx_massNA_clean;    //!
  std::vector<float>* m_secVtx_direction_clean; //!
  std::vector<int>*   m_secVtx_charge_clean;    //!
  std::vector<float>* m_secVtx_H_clean;         //!
  std::vector<float>* m_secVtx_Ht_clean;        //!
  std::vector<float>* m_secVtx_minOpAng_clean;  //!
  std::vector<float>* m_secVtx_maxOpAng_clean;  //!
  std::vector<float>* m_secVtx_mind0_clean;     //!
  std::vector<float>* m_secVtx_maxd0_clean;     //!
  std::vector<float>* m_secVtx_pt_bare;         //!
  std::vector<float>* m_secVtx_eta_bare;        //!
  std::vector<float>* m_secVtx_phi_bare;        //!
  std::vector<float>* m_secVtx_mass_bare;       //!
  std::vector<float>* m_secVtx_massNA_bare;     //!
  std::vector<float>* m_secVtx_direction_bare;  //!
  std::vector<int>*   m_secVtx_charge_bare;     //!
  std::vector<float>* m_secVtx_H_bare;          //!
  std::vector<float>* m_secVtx_Ht_bare;         //!
  std::vector<float>* m_secVtx_minOpAng_bare;   //!
  std::vector<float>* m_secVtx_maxOpAng_bare;   //!
  std::vector<float>* m_secVtx_mind0_bare;      //!
  std::vector<float>* m_secVtx_maxd0_bare;      //!
  std::vector<float>* m_secVtx_chi2;            //!
  std::vector<int>*   m_secVtx_ntrk;            //!
  std::vector<int>*   m_secVtx_ntrk_clean;      //!
  std::vector<int>*   m_secVtx_ntrk_filt;       //!
  std::vector<std::vector<float>>* m_secVtx_covariance; //!
  // secondary vertex tracks
  std::vector<std::vector<int>>*     m_secVtx_trk_ID;       //!
  std::vector<std::vector<int>>*     m_secVtx_trk_index;    //!
  std::vector<std::vector<float>>*   m_secVtx_trk_pt_sv;    //!
  std::vector<std::vector<float>>*   m_secVtx_trk_eta_sv;   //!
  std::vector<std::vector<float>>*   m_secVtx_trk_phi_sv;   //!
  std::vector<std::vector<float>>*   m_secVtx_trk_d0_sv;    //!
  std::vector<std::vector<float>>*   m_secVtx_trk_z0_sv;    //!
  std::vector<std::vector<float>>*   m_secVtx_trk_errd0_sv; //!
  std::vector<std::vector<float>>*   m_secVtx_trk_errz0_sv; //!
  std::vector<std::vector<float>>*   m_secVtx_trk_errP_sv;  //!
  std::vector<std::vector<float>>*   m_secVtx_trk_chi2_sv;  //!
  std::vector<std::vector<uint8_t>>* m_secVtx_trk_isFinal;  //!
  std::vector<std::vector<uint8_t>>* m_secVtx_trk_isSel;    //!
  std::vector<std::vector<uint8_t>>* m_secVtx_trk_isAssoc;  //!
  std::vector<std::vector<uint8_t>>* m_secVtx_trk_isClean;  //!
  std::vector<std::vector<uint8_t>>* m_secVtx_trk_isFilt;   //!
  // secondary vertices: truth matching
  std::vector<int>*                      m_secVtx_truth_n;     //!
  std::vector<std::vector<std::string>>* m_secVtx_truth_llp;   //!
  std::vector<std::vector<int>>*         m_secVtx_truth_ID;    //!
  std::vector<std::vector<int>>*         m_secVtx_truth_index; //!
  std::vector<std::vector<float>>*       m_secVtx_truth_dist;  //!
  std::vector<std::vector<float>>*       m_secVtx_truth_score; //!
  std::vector<std::vector<int>>*         m_secVtx_truth_posID; //!
  std::vector<std::vector<float>>*       m_secVtx_truth_resid; //!
  // secondary vertices matched to jets
  std::vector<uint8_t>* m_secVtx_jetMatched;     //!
  std::vector<int>*     m_secVtx_jetMatch_ID;    //!
  std::vector<int>*     m_secVtx_jetMatch_index; //!
  std::vector<float>*   m_secVtx_jetMatch_dR;    //!
  


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
  std::vector<TH1F*> h_pv_x;    //!
  std::vector<TH1F*> h_pv_y;    //!
  std::vector<TH1F*> h_pv_z;    //!
  std::vector<TH1F*> h_pv_r;    //!
  std::vector<TH1F*> h_pv_phi;  //!
  std::vector<TH1F*> h_pv_ntrk; //!
  // leading N-jet Ht
  std::vector<TH1F*> h_NJetHt;      //!
  std::vector<TH1F*> h_NJetHt_vrsh; //!


  // JET HISTOS
  // basics
  std::vector<std::vector<TH1F*>> h_jet_n;     //!
  std::vector<std::vector<TH1F*>> h_jet_pt;    //!
  std::vector<std::vector<TH1F*>> h_jet_pt_s;  //!
  std::vector<std::vector<TH1F*>> h_jet_eta;   //!
  std::vector<std::vector<TH1F*>> h_jet_phi;   //!
  std::vector<std::vector<TH1F*>> h_jet_E;     //!
  std::vector<std::vector<TH1F*>> h_jet_M;     //!
  std::vector<std::vector<TH1F*>> h_jet_rapid; //!
  std::vector<std::vector<TH1F*>> h_jet_nConstits; //!
  // extra kinematics
  std::vector<std::vector<TH1F*>> h_jet_px;   //!
  std::vector<std::vector<TH1F*>> h_jet_py;   //!
  std::vector<std::vector<TH1F*>> h_jet_pz;   //!
  std::vector<std::vector<TH1F*>> h_jet_Et;   //!
  std::vector<std::vector<TH1F*>> h_jet_Et_s; //!
  // calo / cluster (quality) info
  std::vector<std::vector<TH1F*>> h_jet_timing;          //!
  std::vector<std::vector<TH1F*>> h_jet_timing_s;        //!
  std::vector<std::vector<TH1F*>> h_jet_sqrtTiming;      //!
  std::vector<std::vector<TH1F*>> h_jet_sqrtTiming_s;    //!
  std::vector<std::vector<TH1F*>> h_jet_LArQual;         //!
  std::vector<std::vector<TH1F*>> h_jet_LArQual_s;       //!
  std::vector<std::vector<TH1F*>> h_jet_sqrtLArQual;     //!
  std::vector<std::vector<TH1F*>> h_jet_sqrtLArQual_s;   //!
  std::vector<std::vector<TH1F*>> h_jet_HECQual;         //!
  std::vector<std::vector<TH1F*>> h_jet_HECQual_s;       //!
  std::vector<std::vector<TH1F*>> h_jet_sqrtHECQual;     //!
  std::vector<std::vector<TH1F*>> h_jet_sqrtHECQual_s;   //!
  std::vector<std::vector<TH1F*>> h_jet_LArQmean;        //!
  std::vector<std::vector<TH1F*>> h_jet_sqrtLArQmean;    //!
  std::vector<std::vector<TH1F*>> h_jet_n90Constits;     //!
  std::vector<std::vector<TH1F*>> h_jet_centroidR;       //!
  std::vector<std::vector<TH1F*>> h_jet_ootFrac5;        //!
  std::vector<std::vector<TH1F*>> h_jet_ootFrac5_s;      //!
  std::vector<std::vector<TH1F*>> h_jet_sqrtOotFrac5;    //!
  std::vector<std::vector<TH1F*>> h_jet_sqrtOotFrac5_s;  //!
  std::vector<std::vector<TH1F*>> h_jet_ootFrac10;       //!
  std::vector<std::vector<TH1F*>> h_jet_ootFrac10_s;     //!
  std::vector<std::vector<TH1F*>> h_jet_sqrtOotFrac10;   //!
  std::vector<std::vector<TH1F*>> h_jet_sqrtOotFrac10_s; //!
  std::vector<std::vector<TH1F*>> h_jet_fracSampMax;     //!
  std::vector<std::vector<TH1F*>> h_jet_leadClustPt;     //!
  std::vector<std::vector<TH1F*>> h_jet_leadClustCtrL;   //!
  std::vector<std::vector<TH1F*>> h_jet_leadClust2ndL;   //!
  std::vector<std::vector<TH1F*>> h_jet_leadClust2ndR;   //!
  std::vector<std::vector<TH1F*>> h_jet_EMFrac;          //!
  std::vector<std::vector<TH1F*>> h_jet_HECFrac;         //!
  std::vector<std::vector<TH1F*>> h_jet_nonzeroHECFrac;  //!
  std::vector<std::vector<TH1F*>> h_jet_width;           //!
  // PV track moments
  std::vector<std::vector<TH1F*>> h_jet_ntrkPt10;     //!
  std::vector<std::vector<TH1F*>> h_jet_sumPtTrkPt10; //!
  std::vector<std::vector<TH1F*>> h_jet_trkWidthPt10; //!
  std::vector<std::vector<TH1F*>> h_jet_ntrkPt5;      //!
  std::vector<std::vector<TH1F*>> h_jet_sumPtTrkPt5;  //!
  std::vector<std::vector<TH1F*>> h_jet_trkWidthPt5;  //!
  std::vector<std::vector<TH1F*>> h_jet_JVF;          //!
  // truth / b-tagging info
  std::vector<std::vector<TH1F*>> h_jet_partonID; //!
  // ghost tracks
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nghosttrk; //!
  
  // matched tracks
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_ntrk;             //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_dR;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_minDR;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_maxDR;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_pt;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_d0;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_mind0;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_maxd0;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sumd0;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_z0;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_minz0;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_maxz0;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sumz0;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_errd0;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_minErrd0;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_maxErrd0;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sumErrd0;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_errz0;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_minErrz0;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_maxErrz0;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sumErrz0;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtpt;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtd0;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtmind0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtmaxd0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtsumd0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtz0;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtminz0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtmaxz0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtsumz0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrterrd0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtminErrd0; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtmaxErrd0; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtsumErrd0; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrterrz0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtminErrz0; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtmaxErrz0; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_sqrtsumErrz0; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_nSCT;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_nPixel;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_nSi;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_trk_nTRT;         //!
  // --> system of matched tracks as single entity
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_ntrk_pt;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_ntrk_eta;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_ntrk_phi;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_ntrk_m;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_ntrk_sumPt;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_ntrk_sqrtsumPt;   //!
  
  // matched secondary vertices
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv;              //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_dR;            //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_minDR;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_maxDR;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_pt;            //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_Ht;            //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_H;             //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_sqrtpt;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_sqrtHt;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_sqrtH;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_mass;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_mass_s;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_ntrk;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_njtrk;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_z;             //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_minz;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_maxz;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_sumz;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_r;             //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_minr;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_maxr;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_sumr;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_sv_chi2;          //!
  // --> system of matched secondary vertices as single entity
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_pt;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_eta;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_phi;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_m;            //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_sumPt;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_sumHt;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_sumH;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_sqrtsumPt;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_sqrtsumHt;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_sqrtsumH;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_sumMass;      //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_sumMass_s;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_ntrk;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jet_nsv_njtrk;        //!
  // --> look at "good" vertices after vertex studies / finalized DV cuts...

  // --> calculate matched track, sv sum-p4 per N-jet dijet system (?)

  // --> count number of jets with some number of associated vertices, tracks w/ certain criteria
  // --> --> i.e. want to know per event how many jets have at least one associated DV...
  // --> --> LOOK AT PLOTS FIRST TO GET IDEA OF WHERE TO CUT

  // --> look at other jet variables (see tree, old code)

  // leading jets
  std::vector<std::vector<std::vector<TH1F*>> > h_jetN_pt;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jetN_pt_s;      //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jetN_eta;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jetN_phi;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jetN_E;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jetN_M;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jetN_rapid;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jetN_nConstits; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jetN_Et;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_jetN_Et_s;      //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_ntrk;             //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_minDR;        //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_maxDR;        //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_mind0;        //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_maxd0;        //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sumd0;        //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_minz0;        //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_maxz0;        //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sumz0;        //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_minErrd0;     //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_maxErrd0;     //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sumErrd0;     //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_minErrz0;     //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_maxErrz0;     //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sumErrz0;     //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtmind0;    //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtmaxd0;    //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtsumd0;    //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtminz0;    //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtmaxz0;    //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtsumz0;    //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtminErrd0; //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtmaxErrd0; //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtsumErrd0; //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtminErrz0; //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtmaxErrz0; //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_trk_sqrtsumErrz0; //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_ntrk_pt;          //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_ntrk_eta;         //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_ntrk_phi;         //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_ntrk_m;           //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_ntrk_sumPt;       //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_ntrk_sqrtsumPt;   //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv;              //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_sv_minDR;         //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_sv_maxDR;         //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_sv_minz;          //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_sv_maxz;          //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_sv_sumz;          //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_sv_minr;          //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_sv_maxr;          //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_sv_sumr;          //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_pt;           //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_eta;          //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_phi;          //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_m;            //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_sumPt;        //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_sumHt;        //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_sumH;         //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_sqrtsumPt;    //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_sqrtsumHt;    //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_sqrtsumH;     //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_sumMass;      //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_sumMass_s;    //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_ntrk;         //!
  std::vector<std::vector<std::vector<std::vector<TH1F*>> >> h_jetN_nsv_njtrk;        //!
  
  // dijets
  std::vector<std::vector<TH1F*>> h_dijet_n;           //!
  std::vector<std::vector<TH1F*>> h_dijet_pt;          //!
  std::vector<std::vector<TH1F*>> h_dijet_eta;         //!
  std::vector<std::vector<TH1F*>> h_dijet_phi;         //!
  std::vector<std::vector<TH1F*>> h_dijet_m;           //!
  std::vector<std::vector<TH1F*>> h_dijet_sumPt;       //!
  std::vector<std::vector<TH1F*>> h_dijet_dR;          //!
  std::vector<std::vector<TH1F*>> h_dijet_avgp4_pt;    //!
  std::vector<std::vector<TH1F*>> h_dijet_avgp4_eta;   //!
  std::vector<std::vector<TH1F*>> h_dijet_avgp4_phi;   //!
  std::vector<std::vector<TH1F*>> h_dijet_avgp4_m;     //!
  std::vector<std::vector<TH1F*>> h_dijet_avgp4_sumPt; //!
  std::vector<std::vector<TH1F*>> h_dijet_avgp4_dR;    //!
  std::vector<std::vector<TH1F*>> h_dijet_maxp4_pt;    //!
  std::vector<std::vector<TH1F*>> h_dijet_maxp4_eta;   //!
  std::vector<std::vector<TH1F*>> h_dijet_maxp4_phi;   //!
  std::vector<std::vector<TH1F*>> h_dijet_maxp4_m;     //!
  std::vector<std::vector<TH1F*>> h_dijet_maxp4_sumPt; //!
  std::vector<std::vector<TH1F*>> h_dijet_maxp4_dR;    //!
  std::vector<std::vector<TH1F*>> h_dijet_minp4_pt;    //!
  std::vector<std::vector<TH1F*>> h_dijet_minp4_eta;   //!
  std::vector<std::vector<TH1F*>> h_dijet_minp4_phi;   //!
  std::vector<std::vector<TH1F*>> h_dijet_minp4_m;     //!
  std::vector<std::vector<TH1F*>> h_dijet_minp4_sumPt; //!
  std::vector<std::vector<TH1F*>> h_dijet_minp4_dR;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_ntrk;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_ntrk_pt;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_ntrk_eta;   //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_ntrk_phi;   //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_ntrk_m;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_ntrk_sumPt; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_ntrk;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_ntrk_pt;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_ntrk_eta;   //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_ntrk_phi;   //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_ntrk_m;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_ntrk_sumPt; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_nsv;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_nsv_pt;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_nsv_eta;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_nsv_phi;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_nsv_m;      //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxp4_nsv_sumPt;  //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_nsv;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_nsv_pt;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_nsv_eta;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_nsv_phi;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_nsv_m;      //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minp4_nsv_sumPt;  //!
  std::vector<std::vector<TH1F*>> h_dijet_maxpt_pt;    //!
  std::vector<std::vector<TH1F*>> h_dijet_maxpt_eta;   //!
  std::vector<std::vector<TH1F*>> h_dijet_maxpt_phi;   //!
  std::vector<std::vector<TH1F*>> h_dijet_maxpt_m;     //!
  std::vector<std::vector<TH1F*>> h_dijet_maxpt_sumPt; //!
  std::vector<std::vector<TH1F*>> h_dijet_maxpt_dR;    //!
  std::vector<std::vector<TH1F*>> h_dijet_minpt_pt;    //!
  std::vector<std::vector<TH1F*>> h_dijet_minpt_eta;   //!
  std::vector<std::vector<TH1F*>> h_dijet_minpt_phi;   //!
  std::vector<std::vector<TH1F*>> h_dijet_minpt_m;     //!
  std::vector<std::vector<TH1F*>> h_dijet_minpt_sumPt; //!
  std::vector<std::vector<TH1F*>> h_dijet_minpt_dR;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_ntrk;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_ntrk_pt;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_ntrk_eta;   //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_ntrk_phi;   //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_ntrk_m;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_ntrk_sumPt; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_ntrk;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_ntrk_pt;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_ntrk_eta;   //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_ntrk_phi;   //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_ntrk_m;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_ntrk_sumPt; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_nsv;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_nsv_pt;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_nsv_eta;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_nsv_phi;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_nsv_m;      //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_maxpt_nsv_sumPt;  //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_nsv;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_nsv_pt;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_nsv_eta;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_nsv_phi;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_nsv_m;      //!
  std::vector<std::vector<std::vector<TH1F*>> > h_dijet_minpt_nsv_sumPt;  //!
  
  // N jets (all jets in event)
  std::vector<std::vector<TH1F*>> h_njet_pt;    //!
  std::vector<std::vector<TH1F*>> h_njet_eta;   //!
  std::vector<std::vector<TH1F*>> h_njet_phi;   //!
  std::vector<std::vector<TH1F*>> h_njet_m;     //!
  std::vector<std::vector<TH1F*>> h_njet_sumPt; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_ntrk;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_ntrk_pt;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_ntrk_eta;   //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_ntrk_phi;   //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_ntrk_m;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_ntrk_sumPt; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_nsv;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_nsv_pt;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_nsv_eta;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_nsv_phi;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_nsv_m;      //!
  std::vector<std::vector<std::vector<TH1F*>> > h_njet_nsv_sumPt;  //!

  // leading N-jet dijet invariant mass (avg of dijet pairs w/ min diff invM b/w them)
  std::vector<TH1F*> h_NJetMjj;            //!
  std::vector<TH1F*> h_NJetMjjDiff;        //!
  std::vector<TH1F*> h_NJetPtjj;           //!
  std::vector<TH1F*> h_NJetPtjjDiff;       //!
  std::vector<TH1F*> h_NJetEtajj;          //!
  std::vector<TH1F*> h_NJetEtajjDiff;      //!
  std::vector<TH1F*> h_NJetPhijj;          //!
  std::vector<TH1F*> h_NJetPhijjDiff;      //!
  std::vector<TH1F*> h_NJetSumPtjj;        //!
  std::vector<TH1F*> h_NJetDRjj;           //!
  std::vector<TH1F*> h_NJetMjj_0p5;        //!
  std::vector<TH1F*> h_NJetMjjDiff_0p5;    //!
  std::vector<TH1F*> h_NJetPtjj_0p5;       //!
  std::vector<TH1F*> h_NJetPtjjDiff_0p5;   //!
  std::vector<TH1F*> h_NJetEtajj_0p5;      //!
  std::vector<TH1F*> h_NJetEtajjDiff_0p5;  //!
  std::vector<TH1F*> h_NJetPhijj_0p5;      //!
  std::vector<TH1F*> h_NJetPhijjDiff_0p5;  //!
  std::vector<TH1F*> h_NJetSumPtjj_0p5;    //!
  std::vector<TH1F*> h_NJetDRjj_0p5;       //!
  std::vector<TH1F*> h_NJetMjj_0p25;       //!
  std::vector<TH1F*> h_NJetMjjDiff_0p25;   //!
  std::vector<TH1F*> h_NJetPtjj_0p25;      //!
  std::vector<TH1F*> h_NJetPtjjDiff_0p25;  //!
  std::vector<TH1F*> h_NJetEtajj_0p25;     //!
  std::vector<TH1F*> h_NJetEtajjDiff_0p25; //!
  std::vector<TH1F*> h_NJetPhijj_0p25;     //!
  std::vector<TH1F*> h_NJetPhijjDiff_0p25; //!
  std::vector<TH1F*> h_NJetSumPtjj_0p25;   //!
  std::vector<TH1F*> h_NJetDRjj_0p25;      //!
  std::vector<TH1F*> h_NJetMjj_0p2;        //!
  std::vector<TH1F*> h_NJetMjjDiff_0p2;    //!
  std::vector<TH1F*> h_NJetPtjj_0p2;       //!
  std::vector<TH1F*> h_NJetPtjjDiff_0p2;   //!
  std::vector<TH1F*> h_NJetEtajj_0p2;      //!
  std::vector<TH1F*> h_NJetEtajjDiff_0p2;  //!
  std::vector<TH1F*> h_NJetPhijj_0p2;      //!
  std::vector<TH1F*> h_NJetPhijjDiff_0p2;  //!
  std::vector<TH1F*> h_NJetSumPtjj_0p2;    //!
  std::vector<TH1F*> h_NJetDRjj_0p2;       //!

  
  // TRACK HISTOS
  // basics
  std::vector<std::vector<TH1F*>> h_trk_n; //!

  // --> DO TRACK CLEANING STUDIES
  // --> --> look at tracks matched to LLP descendants and compare to fakes (no matching truth)

  
  // TRUTH VERTEX HISTOS
  std::vector<TH1F*> h_truthVtx_n; //!
  // --> CHANGE TO VECTOR OF VECTOR FOR ANY LLP TRUTH VERTEX
  // dark pion decays
  std::vector<TH1F*> h_truthDarkPionDecay_n;         //!
  std::vector<TH1F*> h_truthDarkPionDecay_x;         //!
  std::vector<TH1F*> h_truthDarkPionDecay_y;         //!
  std::vector<TH1F*> h_truthDarkPionDecay_z;         //!
  std::vector<TH1F*> h_truthDarkPionDecay_r;         //!
  std::vector<TH1F*> h_truthDarkPionDecay_pt;        //!
  std::vector<TH1F*> h_truthDarkPionDecay_eta;       //!
  std::vector<TH1F*> h_truthDarkPionDecay_phi;       //!
  std::vector<TH1F*> h_truthDarkPionDecay_mass;      //!
  std::vector<TH1F*> h_truthDarkPionDecay_nOutP;     //!
  std::vector<TH1F*> h_truthDarkPionDecay_nDesc;     //!
  std::vector<TH1F*> h_truthDarkPionDecay_nRecoDesc; //!
  std::vector<TH1F*> h_truthDarkPionDecay_nSelDesc;  //!
  std::vector<TH1F*> h_truthDarkPionDecay_nPos;      //!
  // k-short decays
  std::vector<TH1F*> h_truthKshortDecay_n;         //!
  std::vector<TH1F*> h_truthKshortDecay_x;         //!
  std::vector<TH1F*> h_truthKshortDecay_y;         //!
  std::vector<TH1F*> h_truthKshortDecay_z;         //!
  std::vector<TH1F*> h_truthKshortDecay_r;         //!
  std::vector<TH1F*> h_truthKshortDecay_pt;        //!
  std::vector<TH1F*> h_truthKshortDecay_eta;       //!
  std::vector<TH1F*> h_truthKshortDecay_phi;       //!
  std::vector<TH1F*> h_truthKshortDecay_mass;      //!
  std::vector<TH1F*> h_truthKshortDecay_nOutP;     //!
  std::vector<TH1F*> h_truthKshortDecay_nDesc;     //!
  std::vector<TH1F*> h_truthKshortDecay_nRecoDesc; //!
  std::vector<TH1F*> h_truthKshortDecay_nSelDesc;  //!
  std::vector<TH1F*> h_truthKshortDecay_nPos;      //!

  
  // SECONDARY VERTEX HISTOS
  // basics --> add h/ht histos ??
  std::vector<std::vector<TH1F*>> h_DV_n;           //!
  std::vector<std::vector<TH1F*>> h_DV_x;           //!
  std::vector<std::vector<TH1F*>> h_DV_y;           //!
  std::vector<std::vector<TH1F*>> h_DV_z;           //!
  std::vector<std::vector<TH1F*>> h_DV_r;           //!
  std::vector<std::vector<TH1F*>> h_DV_x_s;         //!
  std::vector<std::vector<TH1F*>> h_DV_y_s;         //!
  std::vector<std::vector<TH1F*>> h_DV_z_s;         //!
  std::vector<std::vector<TH1F*>> h_DV_r_s;         //!
  std::vector<std::vector<TH1F*>> h_DV_phipos;      //!
  std::vector<std::vector<TH1F*>> h_DV_pt;          //!
  std::vector<std::vector<TH1F*>> h_DV_pt_s;        //!
  std::vector<std::vector<TH1F*>> h_DV_pt_xs;       //!
  std::vector<std::vector<TH1F*>> h_DV_eta;         //!
  std::vector<std::vector<TH1F*>> h_DV_phi;         //!
  std::vector<std::vector<TH1F*>> h_DV_mass;        //!
  std::vector<std::vector<TH1F*>> h_DV_mass_l;      //!
  std::vector<std::vector<TH1F*>> h_DV_mass_s;      //!
  std::vector<std::vector<TH1F*>> h_DV_mass_xs;     //!
  std::vector<std::vector<TH1F*>> h_DV_massNA;      //!
  std::vector<std::vector<TH1F*>> h_DV_massNA_l;    //!
  std::vector<std::vector<TH1F*>> h_DV_massNA_s;    //!
  std::vector<std::vector<TH1F*>> h_DV_massNA_xs;   //!
  std::vector<std::vector<TH1F*>> h_DV_direction;   //!
  std::vector<std::vector<TH1F*>> h_DV_minOpAng;    //!
  std::vector<std::vector<TH1F*>> h_DV_maxOpAng;    //!
  std::vector<std::vector<TH1F*>> h_DV_chi2;        //!
  std::vector<std::vector<TH1F*>> h_DV_chi2_s;      //!
  std::vector<std::vector<TH1F*>> h_DV_ntrk;        //!
  std::vector<std::vector<TH1F*>> h_DV_ntrk_final;  //!
  std::vector<std::vector<TH1F*>> h_DV_ntrk_sel;    //!
  std::vector<std::vector<TH1F*>> h_DV_ntrk_assoc;  //!
  std::vector<std::vector<TH1F*>> h_DV_ntrk_lrt;    //!
  std::vector<std::vector<TH1F*>> h_DV_errx;        //!
  std::vector<std::vector<TH1F*>> h_DV_erry;        //!
  std::vector<std::vector<TH1F*>> h_DV_errz;        //!
  std::vector<std::vector<TH1F*>> h_DV_errr;        //!
  std::vector<std::vector<TH1F*>> h_DV_errphi;      //!
  std::vector<std::vector<TH1F*>> h_DV_sqrterrx;    //!
  std::vector<std::vector<TH1F*>> h_DV_sqrterry;    //!
  std::vector<std::vector<TH1F*>> h_DV_sqrterrz;    //!
  std::vector<std::vector<TH1F*>> h_DV_sqrterrr;    //!
  std::vector<std::vector<TH1F*>> h_DV_sqrterrphi;  //!
  std::vector<std::vector<TH1F*>> h_DV_fracerrx;    //!
  std::vector<std::vector<TH1F*>> h_DV_fracerry;    //!
  std::vector<std::vector<TH1F*>> h_DV_fracerrz;    //!
  std::vector<std::vector<TH1F*>> h_DV_fracerrr;    //!
  std::vector<std::vector<TH1F*>> h_DV_fracerrphi;  //!
  std::vector<std::vector<TH1F*>> h_DV_signifx;     //!
  std::vector<std::vector<TH1F*>> h_DV_signify;     //!
  std::vector<std::vector<TH1F*>> h_DV_signifz;     //!
  std::vector<std::vector<TH1F*>> h_DV_signifr;     //!
  std::vector<std::vector<TH1F*>> h_DV_signifphi;   //!
  std::vector<std::vector<TH1F*>> h_DV_jetDR;       //!
  std::vector<std::vector<TH1F*>> h_DV_leadJetDR;   //!
  // --> for truth-matched DVs, look at match score, distance to truth, visible mass/mult fraction, etc; make 2d plots
  
  // tracks
  // --> track parameters wrt PV
  std::vector<std::vector<TH1F*>> h_DV_trk_qOverP;     //!
  std::vector<std::vector<TH1F*>> h_DV_trk_theta;      //!
  std::vector<std::vector<TH1F*>> h_DV_trk_pt;         //!
  std::vector<std::vector<TH1F*>> h_DV_trk_eta;        //!
  std::vector<std::vector<TH1F*>> h_DV_trk_phi;        //!
  std::vector<std::vector<TH1F*>> h_DV_trk_d0;         //!
  std::vector<std::vector<TH1F*>> h_DV_trk_d0_xs;      //!
  std::vector<std::vector<TH1F*>> h_DV_trk_z0;         //!
  std::vector<std::vector<TH1F*>> h_DV_trk_errd0;      //!
  std::vector<std::vector<TH1F*>> h_DV_trk_errz0;      //!
  std::vector<std::vector<TH1F*>> h_DV_trk_sqrterrd0;  //!
  std::vector<std::vector<TH1F*>> h_DV_trk_sqrterrz0;  //!
  std::vector<std::vector<TH1F*>> h_DV_trk_fracerrd0;  //!
  std::vector<std::vector<TH1F*>> h_DV_trk_fracerrz0;  //!
  std::vector<std::vector<TH1F*>> h_DV_trk_signifd0;   //!
  std::vector<std::vector<TH1F*>> h_DV_trk_signifz0;   //!
  std::vector<std::vector<TH1F*>> h_DV_trk_errP;       //!
  std::vector<std::vector<TH1F*>> h_DV_trk_sqrterrP;   //!
  std::vector<std::vector<TH1F*>> h_DV_trk_fracerrP;   //!
  std::vector<std::vector<TH1F*>> h_DV_trk_signifP;    //!
  std::vector<std::vector<TH1F*>> h_DV_trk_chi2;       //!
  std::vector<std::vector<TH1F*>> h_DV_trk_chiSq;      //!
  // --> track parameters wrt SV
  std::vector<std::vector<TH1F*>> h_DV_trk_qOverP_sv;     //!
  std::vector<std::vector<TH1F*>> h_DV_trk_theta_sv;      //!
  std::vector<std::vector<TH1F*>> h_DV_trk_pt_sv;         //!
  std::vector<std::vector<TH1F*>> h_DV_trk_eta_sv;        //!
  std::vector<std::vector<TH1F*>> h_DV_trk_phi_sv;        //!
  std::vector<std::vector<TH1F*>> h_DV_trk_d0_sv;         //!
  std::vector<std::vector<TH1F*>> h_DV_trk_z0_sv;         //!
  std::vector<std::vector<TH1F*>> h_DV_trk_errd0_sv;      //!
  std::vector<std::vector<TH1F*>> h_DV_trk_errz0_sv;      //!
  std::vector<std::vector<TH1F*>> h_DV_trk_sqrterrd0_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_trk_sqrterrz0_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_trk_fracerrd0_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_trk_fracerrz0_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_trk_signifd0_sv;   //!
  std::vector<std::vector<TH1F*>> h_DV_trk_signifz0_sv;   //!
  std::vector<std::vector<TH1F*>> h_DV_trk_errP_sv;       //!
  std::vector<std::vector<TH1F*>> h_DV_trk_sqrterrP_sv;   //!
  std::vector<std::vector<TH1F*>> h_DV_trk_fracerrP_sv;   //!
  std::vector<std::vector<TH1F*>> h_DV_trk_signifP_sv;    //!
  std::vector<std::vector<TH1F*>> h_DV_trk_chi2_sv;       //!
  std::vector<std::vector<TH1F*>> h_DV_trk_chiSq_sv;      //!
  // --> selected tracks
  std::vector<std::vector<TH1F*>> h_DV_seltrk_d0;    //!
  std::vector<std::vector<TH1F*>> h_DV_seltrk_d0_xs; //!
  // --> look at final, selected, associated (and combo) tracks, ...
  
  // --> combined track parameters
  std::vector<std::vector<TH1F*>> h_DV_sumd0;           //!
  std::vector<std::vector<TH1F*>> h_DV_sumz0;           //!
  std::vector<std::vector<TH1F*>> h_DV_sumP;            //!
  std::vector<std::vector<TH1F*>> h_DV_sumsqrtd0;       //!
  std::vector<std::vector<TH1F*>> h_DV_sumsqrtz0;       //!
  std::vector<std::vector<TH1F*>> h_DV_sumsqrtP;        //!
  std::vector<std::vector<TH1F*>> h_DV_sumErrd0;        //!
  std::vector<std::vector<TH1F*>> h_DV_sumErrz0;        //!
  std::vector<std::vector<TH1F*>> h_DV_sumErrP;         //!
  std::vector<std::vector<TH1F*>> h_DV_sumSqrterrd0;    //!
  std::vector<std::vector<TH1F*>> h_DV_sumSqrterrz0;    //!
  std::vector<std::vector<TH1F*>> h_DV_sumSqrterrP;     //!
  std::vector<std::vector<TH1F*>> h_DV_sumFracerrd0;    //!
  std::vector<std::vector<TH1F*>> h_DV_sumFracerrz0;    //!
  std::vector<std::vector<TH1F*>> h_DV_sumFracerrP;     //!
  std::vector<std::vector<TH1F*>> h_DV_sumSignifd0;     //!
  std::vector<std::vector<TH1F*>> h_DV_sumSignifz0;     //!
  std::vector<std::vector<TH1F*>> h_DV_sumSignifP;      //!
  std::vector<std::vector<TH1F*>> h_DV_sumd0_sv;        //!
  std::vector<std::vector<TH1F*>> h_DV_sumz0_sv;        //!
  std::vector<std::vector<TH1F*>> h_DV_sumP_sv;         //!
  std::vector<std::vector<TH1F*>> h_DV_sumsqrtd0_sv;    //!
  std::vector<std::vector<TH1F*>> h_DV_sumsqrtz0_sv;    //!
  std::vector<std::vector<TH1F*>> h_DV_sumsqrtP_sv;     //!
  std::vector<std::vector<TH1F*>> h_DV_sumErrd0_sv;     //!
  std::vector<std::vector<TH1F*>> h_DV_sumErrz0_sv;     //!
  std::vector<std::vector<TH1F*>> h_DV_sumErrP_sv;      //!
  std::vector<std::vector<TH1F*>> h_DV_sumSqrterrd0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_sumSqrterrz0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_sumSqrterrP_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_sumFracerrd0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_sumFracerrz0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_sumFracerrP_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_sumSignifd0_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_sumSignifz0_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_sumSignifP_sv;   //!
  // --> min track parameters
  std::vector<std::vector<TH1F*>> h_DV_mind0;           //!
  std::vector<std::vector<TH1F*>> h_DV_minz0;           //!
  std::vector<std::vector<TH1F*>> h_DV_minP;            //!
  std::vector<std::vector<TH1F*>> h_DV_minsqrtd0;       //!
  std::vector<std::vector<TH1F*>> h_DV_minsqrtz0;       //!
  std::vector<std::vector<TH1F*>> h_DV_minsqrtP;        //!
  std::vector<std::vector<TH1F*>> h_DV_minErrd0;        //!
  std::vector<std::vector<TH1F*>> h_DV_minErrz0;        //!
  std::vector<std::vector<TH1F*>> h_DV_minErrP;         //!
  std::vector<std::vector<TH1F*>> h_DV_minSqrterrd0;    //!
  std::vector<std::vector<TH1F*>> h_DV_minSqrterrz0;    //!
  std::vector<std::vector<TH1F*>> h_DV_minSqrterrP;     //!
  std::vector<std::vector<TH1F*>> h_DV_minFracerrd0;    //!
  std::vector<std::vector<TH1F*>> h_DV_minFracerrz0;    //!
  std::vector<std::vector<TH1F*>> h_DV_minFracerrP;     //!
  std::vector<std::vector<TH1F*>> h_DV_minSignifd0;     //!
  std::vector<std::vector<TH1F*>> h_DV_minSignifz0;     //!
  std::vector<std::vector<TH1F*>> h_DV_minSignifP;      //!
  std::vector<std::vector<TH1F*>> h_DV_mind0_sv;        //!
  std::vector<std::vector<TH1F*>> h_DV_minz0_sv;        //!
  std::vector<std::vector<TH1F*>> h_DV_minP_sv;         //!
  std::vector<std::vector<TH1F*>> h_DV_minsqrtd0_sv;    //!
  std::vector<std::vector<TH1F*>> h_DV_minsqrtz0_sv;    //!
  std::vector<std::vector<TH1F*>> h_DV_minsqrtP_sv;     //!
  std::vector<std::vector<TH1F*>> h_DV_minErrd0_sv;     //!
  std::vector<std::vector<TH1F*>> h_DV_minErrz0_sv;     //!
  std::vector<std::vector<TH1F*>> h_DV_minErrP_sv;      //!
  std::vector<std::vector<TH1F*>> h_DV_minSqrterrd0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_minSqrterrz0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_minSqrterrP_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_minFracerrd0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_minFracerrz0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_minFracerrP_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_minSignifd0_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_minSignifz0_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_minSignifP_sv;   //!
  // --> max track parameters
  std::vector<std::vector<TH1F*>> h_DV_maxd0;           //!
  std::vector<std::vector<TH1F*>> h_DV_maxz0;           //!
  std::vector<std::vector<TH1F*>> h_DV_maxP;            //!
  std::vector<std::vector<TH1F*>> h_DV_maxsqrtd0;       //!
  std::vector<std::vector<TH1F*>> h_DV_maxsqrtz0;       //!
  std::vector<std::vector<TH1F*>> h_DV_maxsqrtP;        //!
  std::vector<std::vector<TH1F*>> h_DV_maxErrd0;        //!
  std::vector<std::vector<TH1F*>> h_DV_maxErrz0;        //!
  std::vector<std::vector<TH1F*>> h_DV_maxErrP;         //!
  std::vector<std::vector<TH1F*>> h_DV_maxSqrterrd0;    //!
  std::vector<std::vector<TH1F*>> h_DV_maxSqrterrz0;    //!
  std::vector<std::vector<TH1F*>> h_DV_maxSqrterrP;     //!
  std::vector<std::vector<TH1F*>> h_DV_maxFracerrd0;    //!
  std::vector<std::vector<TH1F*>> h_DV_maxFracerrz0;    //!
  std::vector<std::vector<TH1F*>> h_DV_maxFracerrP;     //!
  std::vector<std::vector<TH1F*>> h_DV_maxSignifd0;     //!
  std::vector<std::vector<TH1F*>> h_DV_maxSignifz0;     //!
  std::vector<std::vector<TH1F*>> h_DV_maxSignifP;      //!
  std::vector<std::vector<TH1F*>> h_DV_maxd0_sv;        //!
  std::vector<std::vector<TH1F*>> h_DV_maxz0_sv;        //!
  std::vector<std::vector<TH1F*>> h_DV_maxP_sv;         //!
  std::vector<std::vector<TH1F*>> h_DV_maxsqrtd0_sv;    //!
  std::vector<std::vector<TH1F*>> h_DV_maxsqrtz0_sv;    //!
  std::vector<std::vector<TH1F*>> h_DV_maxsqrtP_sv;     //!
  std::vector<std::vector<TH1F*>> h_DV_maxErrd0_sv;     //!
  std::vector<std::vector<TH1F*>> h_DV_maxErrz0_sv;     //!
  std::vector<std::vector<TH1F*>> h_DV_maxErrP_sv;      //!
  std::vector<std::vector<TH1F*>> h_DV_maxSqrterrd0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_maxSqrterrz0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_maxSqrterrP_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_maxFracerrd0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_maxFracerrz0_sv; //!
  std::vector<std::vector<TH1F*>> h_DV_maxFracerrP_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_maxSignifd0_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_maxSignifz0_sv;  //!
  std::vector<std::vector<TH1F*>> h_DV_maxSignifP_sv;   //!
  
  // --> 2d histos: track/vertex vs track/vertex parameters
  std::vector<std::vector<TH2F*>> h_DV_z_r;                    //!
  std::vector<std::vector<TH2F*>> h_DV_mass_r;                 //!
  std::vector<std::vector<TH2F*>> h_DV_z_chi2;                 //!
  std::vector<std::vector<TH2F*>> h_DV_r_chi2;                 //!
  std::vector<std::vector<TH2F*>> h_DV_mass_chi2;              //!
  std::vector<std::vector<TH2F*>> h_DV_z_r_s;                  //!
  std::vector<std::vector<TH2F*>> h_DV_mass_r_s;               //!
  std::vector<std::vector<TH2F*>> h_DV_z_chi2_s;               //!
  std::vector<std::vector<TH2F*>> h_DV_r_chi2_s;               //!
  std::vector<std::vector<TH2F*>> h_DV_mass_chi2_s;            //!
  // --> errors vs mass, chi2 ??
  std::vector<std::vector<TH2F*>> h_DV_errx_x;                 //!
  std::vector<std::vector<TH2F*>> h_DV_erry_y;                 //!
  std::vector<std::vector<TH2F*>> h_DV_errz_z;                 //!
  std::vector<std::vector<TH2F*>> h_DV_errr_r;                 //!
  std::vector<std::vector<TH2F*>> h_DV_errphi_phi;             //!
  std::vector<std::vector<TH2F*>> h_DV_sqrterrx_x;             //!
  std::vector<std::vector<TH2F*>> h_DV_sqrterry_y;             //!
  std::vector<std::vector<TH2F*>> h_DV_sqrterrz_z;             //!
  std::vector<std::vector<TH2F*>> h_DV_sqrterrr_r;             //!
  std::vector<std::vector<TH2F*>> h_DV_sqrterrphi_phi;         //!
  std::vector<std::vector<TH2F*>> h_DV_sumErrd0_r;             //!
  std::vector<std::vector<TH2F*>> h_DV_sumErrz0_z;             //!
  std::vector<std::vector<TH2F*>> h_DV_sumErrP_pt;             //!
  std::vector<std::vector<TH2F*>> h_DV_sumSqrterrd0_r;         //!
  std::vector<std::vector<TH2F*>> h_DV_sumSqrterrz0_z;         //!
  std::vector<std::vector<TH2F*>> h_DV_sumSqrterrP_pt;         //!
  std::vector<std::vector<TH2F*>> h_DV_sumErrd0sv_r;           //!
  std::vector<std::vector<TH2F*>> h_DV_sumErrz0sv_z;           //!
  std::vector<std::vector<TH2F*>> h_DV_sumErrPsv_pt;           //!
  std::vector<std::vector<TH2F*>> h_DV_sumSqrterrd0sv_r;       //!
  std::vector<std::vector<TH2F*>> h_DV_sumSqrterrz0sv_z;       //!
  std::vector<std::vector<TH2F*>> h_DV_sumSqrterrPsv_pt;       //!
  std::vector<std::vector<TH2F*>> h_DV_minErrd0_r;             //!
  std::vector<std::vector<TH2F*>> h_DV_minErrz0_z;             //!
  std::vector<std::vector<TH2F*>> h_DV_minErrP_pt;             //!
  std::vector<std::vector<TH2F*>> h_DV_minSqrterrd0_r;         //!
  std::vector<std::vector<TH2F*>> h_DV_minSqrterrz0_z;         //!
  std::vector<std::vector<TH2F*>> h_DV_minSqrterrP_pt;         //!
  std::vector<std::vector<TH2F*>> h_DV_minErrd0sv_r;           //!
  std::vector<std::vector<TH2F*>> h_DV_minErrz0sv_z;           //!
  std::vector<std::vector<TH2F*>> h_DV_minErrPsv_pt;           //!
  std::vector<std::vector<TH2F*>> h_DV_minSqrterrd0sv_r;       //!
  std::vector<std::vector<TH2F*>> h_DV_minSqrterrz0sv_z;       //!
  std::vector<std::vector<TH2F*>> h_DV_minSqrterrPsv_pt;       //!
  std::vector<std::vector<TH2F*>> h_DV_maxErrd0_r;             //!
  std::vector<std::vector<TH2F*>> h_DV_maxErrz0_z;             //!
  std::vector<std::vector<TH2F*>> h_DV_maxErrP_pt;             //!
  std::vector<std::vector<TH2F*>> h_DV_maxSqrterrd0_r;         //!
  std::vector<std::vector<TH2F*>> h_DV_maxSqrterrz0_z;         //!
  std::vector<std::vector<TH2F*>> h_DV_maxSqrterrP_pt;         //!
  std::vector<std::vector<TH2F*>> h_DV_maxErrd0sv_r;           //!
  std::vector<std::vector<TH2F*>> h_DV_maxErrz0sv_z;           //!
  std::vector<std::vector<TH2F*>> h_DV_maxErrPsv_pt;           //!
  std::vector<std::vector<TH2F*>> h_DV_maxSqrterrd0sv_r;       //!
  std::vector<std::vector<TH2F*>> h_DV_maxSqrterrz0sv_z;       //!
  std::vector<std::vector<TH2F*>> h_DV_maxSqrterrPsv_pt;       //!
  std::vector<std::vector<TH2F*>> h_DV_trkd0_r;                //!
  std::vector<std::vector<TH2F*>> h_DV_trkz0_z;                //!
  std::vector<std::vector<TH2F*>> h_DV_trkP_pt;                //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrd0_r;             //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrz0_z;             //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrP_pt;             //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrd0_r;         //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrz0_z;         //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrP_pt;         //!
  std::vector<std::vector<TH2F*>> h_DV_trkd0sv_r;              //!
  std::vector<std::vector<TH2F*>> h_DV_trkz0sv_z;              //!
  std::vector<std::vector<TH2F*>> h_DV_trkPsv_pt;              //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrd0sv_r;           //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrz0sv_z;           //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrPsv_pt;           //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrd0sv_r;       //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrz0sv_z;       //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrPsv_pt;       //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrd0_trkd0;         //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrz0_trkz0;         //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrP_trkP;           //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrd0_trkd0;     //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrz0_trkz0;     //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrP_trkP;       //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrd0sv_trkd0sv;     //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrz0sv_trkz0sv;     //!
  std::vector<std::vector<TH2F*>> h_DV_trkErrPsv_trkPsv;       //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrd0sv_trkd0sv; //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrz0sv_trkz0sv; //!
  std::vector<std::vector<TH2F*>> h_DV_trkSqrterrPsv_trkPsv;   //!
  
  // n-track vertices
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_n;               //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_z;               //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_z_s;             //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_r;               //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_r_s;             //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_mass;            //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_mass_s;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_mass_xs;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_direction;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minOpAng;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxOpAng;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_chi2;            //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_chi2_s;          //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumd0;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumz0;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumP;            //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumd0_sv;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumz0_sv;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumP_sv;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumsqrtd0;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumsqrtz0;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumsqrtP;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumsqrtd0_sv;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumsqrtz0_sv;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumsqrtP_sv;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_mind0;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minz0;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minP;            //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_mind0_sv;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minz0_sv;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minP_sv;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minsqrtd0;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minsqrtz0;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minsqrtP;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minsqrtd0_sv;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minsqrtz0_sv;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minsqrtP_sv;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxd0;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxz0;           //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxP;            //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxd0_sv;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxz0_sv;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxP_sv;         //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxsqrtd0;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxsqrtz0;       //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxsqrtP;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxsqrtd0_sv;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxsqrtz0_sv;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxsqrtP_sv;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sqrterrx;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sqrterry;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sqrterrz;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sqrterrr;        //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sqrterrphi;      //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumSqrterrd0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumSqrterrz0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumSqrterrP;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumSqrterrd0_sv; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumSqrterrz0_sv; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_sumSqrterrP_sv;  //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minSqrterrd0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minSqrterrz0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minSqrterrP;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minSqrterrd0_sv; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minSqrterrz0_sv; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_minSqrterrP_sv;  //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxSqrterrd0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxSqrterrz0;    //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxSqrterrP;     //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxSqrterrd0_sv; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxSqrterrz0_sv; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_ntrkDV_maxSqrterrP_sv;  //!


  // CUTFLOWS
  std::vector<std::vector<TH1F*>> h_evt_testCutflow_DV;             //!
  std::vector<std::vector<TH1F*>> h_evt_testCutflowEfficiency_DV;   //!
  std::vector<std::vector<TH1F*>> h_evt_cutflow_DV;                 //!
  std::vector<std::vector<TH1F*>> h_evt_cutflowEfficiency_DV;       //!
  std::vector<std::vector<TH1F*>> h_evt_cutflow_NDV;                //!
  std::vector<std::vector<TH1F*>> h_evt_cutflowEfficiency_NDV;      //!
  std::vector<std::vector<TH1F*>> h_evt_cutflowTotalEfficiency_NDV; //!
  std::vector<std::vector<std::vector<TH1F*>> > h_evt_cutflow_ntrkNDV;                //!
  std::vector<std::vector<std::vector<TH1F*>> > h_evt_cutflowEfficiency_ntrkNDV;      //!
  std::vector<std::vector<std::vector<TH1F*>> > h_evt_cutflowTotalEfficiency_ntrkNDV; //!
  // *** run over individual DV cuts to identify promising ones to combine (also combine all, N-1)
  // *** --> run with all vertex, jet info switches and sift through plots to find potential discriminating variables / event-level jet/DV cuts
  // *** apply potential jet, DV-combo, event-level cuts
  // *** --> add jet cutflow, jet efficiency, full event cutflow (for various potential DV, jet cuts) histos ***
  
  // *** update plotting scripts to accomodate cutflow / efficiency plots (i.e. not normalize where necessary; divide efficiency combined histos by number of files added together) ***

  // --> add JET cutflow / efficiency histos for potential jet cuts (per event and overall)
  
  // ADD CUTFLOWS FOR EVENT-LEVEL CUTS AFTER NOMINAL SEARCH REGION SELECTION !!!!
  // --> test out number of potential cuts (i.e. nDV, nJet with some DV/track requirement, etc.)
  // --> will want different cutflow for each DV, jet type (excluding truth)
  // --> also want jet, dv cutflows (count all jet, dv in all events after each jet, dv cut)


  // OVERALL COUNTS / EFFICIENCIES
  std::vector<std::vector<TH1F*>> h_evt_count_DV;              //!
  std::vector<std::vector<TH1F*>> h_evt_cutEfficiency_DV;      //!
  std::vector<std::vector<TH1F*>> h_evt_matchcutEfficiency_DV; //!


  // 2D EVENT HISTOS -- ABCD PLANE TESTS
  // --> weighted standard
  std::vector<std::vector<TH2F*>> h_abcd_nDV_NJetHt;          //!
  //std::vector<std::vector<TH2F*>> h_abcd_nDV_NJetPt;          //!
  //std::vector<std::vector<TH2F*>> h_abcd_nDV_NJetMjj;         //!
  // --> weighted shifted
  std::vector<std::vector<TH2F*>> h_abcd_nDV_NJetHt_vrsh;     //!
  // --> raw standard
  std::vector<std::vector<TH2F*>> h_abcd_raw_nDV_NJetHt;      //!
  // --> raw shifteed
  std::vector<std::vector<TH2F*>> h_abcd_raw_nDV_NJetHt_vrsh; //!

  
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
