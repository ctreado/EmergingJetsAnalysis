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

#include "EJsAnalysis/EJsHelperClasses.h"


class EJsHistogramManager : public HistogramManager
{
 public:
  EJsHistogramManager ( std::string name, std::string detailStr );
  virtual ~EJsHistogramManager ();

  bool m_debug;

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

  StatusCode initialize ( const std::string outFileName,   const std::vector<std::string>& regions, bool mc = false );
  StatusCode execute    ( TTree* tree, Long64_t treeEntry, const std::vector<std::string>& regions, bool mc = false );
  // --> pass structures (not strings) to execute...

  using HistogramManager::book;    // overload
  using HistogramManager::execute; // overload


 protected:
  // holds bools to control which histograms to be filled
  EJsHelperClasses::HistogramInfoSwitch* m_histoInfoSwitch;

  
 private:
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
  
  float    m_pv_x;            //!
  float    m_pv_y;            //!
  float    m_pv_z;            //!
  float    m_pv_r;            //!
  float    m_pv_phi;          //!
  uint32_t m_pv_nTrk;         //!

  
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
  std::vector<float>* m_jet_width;      //!
  std::vector<int>*   m_jet_numConstit; //!

  std::vector<uint8_t>* m_jet_isTruthMatched; //!
  std::vector<float>*   m_jet_truthMatch_dR;  //!
  std::vector<uint8_t>* m_jet_isDarkMatched;  //!
  std::vector<float>*   m_jet_darkMatch_dR;   //!

  std::vector<int>*                m_jet_secVtxCount;   //!
  std::vector<float>*              m_jet_secVtxPt;      //!
  std::vector<std::vector<float>>* m_jet_secVtx_dR;     //!
  std::vector<int>*                m_jet_truthVtxCount; //!
  std::vector<float>*              m_jet_truthVtxPt;    //!
  std::vector<std::vector<float>>* m_jet_truthVtx_dR;   //!

  std::vector<int>*                m_jet_trkCount; //!
  std::vector<float>*              m_jet_trkPt;    //!
  std::vector<std::vector<float>>* m_jet_trk_dR;   //!
  std::vector<int>*                m_jet_tpCount;  //!
  std::vector<float>*              m_jet_tpPt;     //!
  std::vector<std::vector<float>>* m_jet_tp_dR;    //!
  
  std::vector<int>*   m_jet_GhostTrackCount; //!
  std::vector<float>* m_jet_GhostTrackPt;    //! 
  std::vector<int>*   m_jet_GhostTruthCount; //!
  std::vector<float>* m_jet_GhostTruthPt;    //!

  // branches -- truth jets
  int                 m_truthJet_n;          //!
  std::vector<float>* m_truthJet_pt;         //!
  std::vector<float>* m_truthJet_eta;        //!
  std::vector<float>* m_truthJet_phi;        //!
  std::vector<float>* m_truthJet_E;          //!
  std::vector<float>* m_truthJet_M;          //!
  std::vector<float>* m_truthJet_width;      //!
  std::vector<int>*   m_truthJet_numConstit; //!

  std::vector<uint8_t>* m_truthJet_isDarkMatched;  //!
  std::vector<float>*   m_truthJet_darkMatch_dR;   //!

  std::vector<int>*                m_truthJet_secVtxCount;   //!
  std::vector<float>*              m_truthJet_secVtxPt;      //!
  std::vector<std::vector<float>>* m_truthJet_secVtx_dR;     //!
  std::vector<int>*                m_truthJet_truthVtxCount; //!
  std::vector<float>*              m_truthJet_truthVtxPt;    //!
  std::vector<std::vector<float>>* m_truthJet_truthVtx_dR;   //!

  std::vector<int>*                m_truthJet_trkCount; //!
  std::vector<float>*              m_truthJet_trkPt;    //!
  std::vector<std::vector<float>>* m_truthJet_trk_dR;   //!
  std::vector<int>*                m_truthJet_tpCount;  //!
  std::vector<float>*              m_truthJet_tpPt;     //!
  std::vector<std::vector<float>>* m_truthJet_tp_dR;    //!

  std::vector<float>*              m_truthJet_girth;      //!
  std::vector<float>*              m_truthJet_constitPt;  //!
  std::vector<std::vector<float>>* m_truthJet_constit_dR; //!

  // branches -- truth dark jets
  int                 m_darkJet_n;          //!
  std::vector<float>* m_darkJet_pt;         //!
  std::vector<float>* m_darkJet_eta;        //!
  std::vector<float>* m_darkJet_phi;        //!
  std::vector<float>* m_darkJet_E;          //!
  std::vector<float>* m_darkJet_M;          //!
  std::vector<int>*   m_darkJet_numConstit; //!

  std::vector<int>*                m_darkJet_secVtxCount;   //!
  std::vector<float>*              m_darkJet_secVtxPt;      //!
  std::vector<std::vector<float>>* m_darkJet_secVtx_dR;     //!
  std::vector<int>*                m_darkJet_truthVtxCount; //!
  std::vector<float>*              m_darkJet_truthVtxPt;    //!
  std::vector<std::vector<float>>* m_darkJet_truthVtx_dR;   //!

  std::vector<int>*                m_darkJet_trkCount; //!
  std::vector<float>*              m_darkJet_trkPt;    //!
  std::vector<std::vector<float>>* m_darkJet_trk_dR;   //!
  std::vector<int>*                m_darkJet_tpCount;  //!
  std::vector<float>*              m_darkJet_tpPt;     //!
  std::vector<std::vector<float>>* m_darkJet_tp_dR;    //!

  std::vector<float>*              m_darkJet_girth;      //!
  std::vector<float>*              m_darkJet_constitPt;  //!
  std::vector<std::vector<float>>* m_darkJet_constit_dR; //!
  
   
  // branches -- secondary vertex
  int                 m_secVtx_n;             //!
  std::vector<float>* m_secVtx_x;             //!
  std::vector<float>* m_secVtx_y;             //!
  std::vector<float>* m_secVtx_z;             //!
  std::vector<float>* m_secVtx_r;             //!
  std::vector<float>* m_secVtx_pt;            //!
  std::vector<float>* m_secVtx_eta;           //!
  std::vector<float>* m_secVtx_phi;           //!
  std::vector<float>* m_secVtx_mass;          //!
  std::vector<float>* m_secVtx_mass_nonAssoc; //!
  std::vector<float>* m_secVtx_chi2;          //!
  std::vector<int>*   m_secVtx_charge;        //!
  std::vector<float>* m_secVtx_Ht;            //!
  std::vector<float>* m_secVtx_mind0;         //!
  std::vector<float>* m_secVtx_maxd0;         //!

  std::vector<std::vector<float>>* m_secVtx_twoTracksMass;     //!
  std::vector<std::vector<float>>* m_secVtx_twoTracksMassRest; //!
  std::vector<std::vector<int>>*   m_secVtx_twoTracksCharge;   //!

  std::vector<uint32_t>* m_secVtx_ntrk;       //!
  std::vector<uint32_t>* m_secVtx_ntrk_sel;   //!
  std::vector<uint32_t>* m_secVtx_ntrk_assoc; //!


  
  // histograms -- events
  std::vector<TH1F*> h_npv; //!
  std::vector<TH1F*> h_actualMu; //!
  std::vector<TH1F*> h_averageMu; //!
  
  std::vector<TH1F*> h_pv_x;    //!
  std::vector<TH1F*> h_pv_y;    //!
  std::vector<TH1F*> h_pv_z;    //!
  std::vector<TH1F*> h_pv_r;    //!
  std::vector<TH1F*> h_pv_phi;  //!
  std::vector<TH1F*> h_pv_nTrk; //!


  // histograms -- jets
  std::vector<TH1F*> h_jet_n;          //!
  std::vector<TH1F*> h_jet_pt;         //!
  std::vector<TH1F*> h_jet_eta;        //!
  std::vector<TH1F*> h_jet_phi;        //!
  std::vector<TH1F*> h_jet_E;          //!
  std::vector<TH1F*> h_jet_M;          //!
  std::vector<TH1F*> h_jet_width;      //!
  std::vector<TH1F*> h_jet_numConstit; //!

  std::vector<TH1F*> h_jet_secVtxCount;   //!
  std::vector<TH1F*> h_jet_secVtxPt;      //!
  std::vector<TH1F*> h_jet_secVtx_dR;     //!
  std::vector<TH1F*> h_jet_truthVtxCount; //!
  std::vector<TH1F*> h_jet_truthVtxPt;    //!
  std::vector<TH1F*> h_jet_truthVtx_dR;   //!

  std::vector<TH1F*> h_jet_trkCount; //!
  std::vector<TH1F*> h_jet_trkPt;    //!
  std::vector<TH1F*> h_jet_trk_dR;   //!
  std::vector<TH1F*> h_jet_tpCount;  //!
  std::vector<TH1F*> h_jet_tpPt;     //!
  std::vector<TH1F*> h_jet_tp_dR;    //!
  
  std::vector<TH1F*> h_jet_GhostTrackCount; //!
  std::vector<TH1F*> h_jet_GhostTrackPt;    //! 
  std::vector<TH1F*> h_jet_GhostTruthCount; //!
  std::vector<TH1F*> h_jet_GhostTruthPt;    //!

  // histograms -- truth jets
  std::vector<TH1F*> h_truthJet_n;          //!
  std::vector<TH1F*> h_truthJet_pt;         //!
  std::vector<TH1F*> h_truthJet_eta;        //!
  std::vector<TH1F*> h_truthJet_phi;        //!
  std::vector<TH1F*> h_truthJet_E;          //!
  std::vector<TH1F*> h_truthJet_M;          //!
  std::vector<TH1F*> h_truthJet_width;      //!
  std::vector<TH1F*> h_truthJet_numConstit; //!

  std::vector<TH1F*> h_truthJet_secVtxCount;   //!
  std::vector<TH1F*> h_truthJet_secVtxPt;      //!
  std::vector<TH1F*> h_truthJet_secVtx_dR;     //!
  std::vector<TH1F*> h_truthJet_truthVtxCount; //!
  std::vector<TH1F*> h_truthJet_truthVtxPt;    //!
  std::vector<TH1F*> h_truthJet_truthVtx_dR;   //!

  std::vector<TH1F*> h_truthJet_trkCount; //!
  std::vector<TH1F*> h_truthJet_trkPt;    //!
  std::vector<TH1F*> h_truthJet_trk_dR;   //!
  std::vector<TH1F*> h_truthJet_tpCount;  //!
  std::vector<TH1F*> h_truthJet_tpPt;     //!
  std::vector<TH1F*> h_truthJet_tp_dR;    //!

  std::vector<TH1F*> h_truthJet_girth;      //!
  std::vector<TH1F*> h_truthJet_constitPt;  //!
  std::vector<TH1F*> h_truthJet_constit_dR; //!

  // histograms -- truth dark jets
  std::vector<TH1F*> h_darkJet_n;          //!
  std::vector<TH1F*> h_darkJet_pt;         //!
  std::vector<TH1F*> h_darkJet_eta;        //!
  std::vector<TH1F*> h_darkJet_phi;        //!
  std::vector<TH1F*> h_darkJet_E;          //!
  std::vector<TH1F*> h_darkJet_M;          //!
  std::vector<TH1F*> h_darkJet_numConstit; //!

  std::vector<TH1F*> h_darkJet_secVtxCount;   //!
  std::vector<TH1F*> h_darkJet_secVtxPt;      //!
  std::vector<TH1F*> h_darkJet_secVtx_dR;     //!
  std::vector<TH1F*> h_darkJet_truthVtxCount; //!
  std::vector<TH1F*> h_darkJet_truthVtxPt;    //!
  std::vector<TH1F*> h_darkJet_truthVtx_dR;   //!

  std::vector<TH1F*> h_darkJet_trkCount; //!
  std::vector<TH1F*> h_darkJet_trkPt;    //!
  std::vector<TH1F*> h_darkJet_trk_dR;   //!
  std::vector<TH1F*> h_darkJet_tpCount;  //!
  std::vector<TH1F*> h_darkJet_tpPt;     //!
  std::vector<TH1F*> h_darkJet_tp_dR;    //!

  std::vector<TH1F*> h_darkJet_girth;      //!
  std::vector<TH1F*> h_darkJet_constitPt;  //!
  std::vector<TH1F*> h_darkJet_constit_dR; //!
  
  
  // histograms -- secondary vertex
  std::vector<TH1F*> h_secVtx_n;             //!
  std::vector<TH1F*> h_secVtx_x;             //!
  std::vector<TH1F*> h_secVtx_y;             //!
  std::vector<TH1F*> h_secVtx_z;             //!
  std::vector<TH1F*> h_secVtx_r;             //!
  std::vector<TH1F*> h_secVtx_pt;            //!
  std::vector<TH1F*> h_secVtx_eta;           //!
  std::vector<TH1F*> h_secVtx_phi;           //!
  std::vector<TH1F*> h_secVtx_mass;          //!
  std::vector<TH1F*> h_secVtx_mass_nonAssoc; //!
  std::vector<TH1F*> h_secVtx_chi2;          //!
  std::vector<TH1F*> h_secVtx_charge;        //!
  std::vector<TH1F*> h_secVtx_Ht;            //!
  std::vector<TH1F*> h_secVtx_mind0;         //!
  std::vector<TH1F*> h_secVtx_maxd0;         //!
  
  std::vector<TH1F*> h_secVtx_twoTracksMass;     //!
  std::vector<TH1F*> h_secVtx_twoTracksMassRest; //!
  std::vector<TH1F*> h_secVtx_twoTracksCharge;   //!

  std::vector<TH1F*> h_secVtx_ntrk;       //!
  std::vector<TH1F*> h_secVtx_ntrk_sel;   //!
  std::vector<TH1F*> h_secVtx_ntrk_assoc; //!

  std::vector<TH2F*> h_secVtx_r_vs_ntrk;    //!
  std::vector<TH2F*> h_secVtx_mass_vs_ntrk; //!
  
};

#endif // EJsAnalysis_EJsHistogramManager_H
