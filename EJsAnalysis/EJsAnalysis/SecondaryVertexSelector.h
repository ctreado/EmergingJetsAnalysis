#ifndef EJsAnalysis_SecondaryVertexSelector_H
#define EJsAnalysis_SecondaryVertexSelector_H

/* SecondaryVertexSelector is the algorithm responsible for
   selecting secondary vertices (primarily using the VsiBonsai toolkit);
   based on xAODAnaHelpers' *Selector algorithms */

// --> IMPLEMENT VSI-BONSAI TRACK FILTERING (add config variables)
// --> ADD SKELETON FOR MATERIAL MAP CUTS (w/ config variables)

#include <string>
#include <vector>

#include <TFile.h>
#include <TH1.h>
#include <TH3.h>
#include <TMatrixT.h>

#include <xAODTracking/Vertex.h>

#include <xAODAnaHelpers/Algorithm.h>

#include "EJsAnalysis/VsiBonsaiTool.h"
#include "EJsAnalysis/AlgConsts.h"


class SecondaryVertexSelector : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  bool m_useCutFlow = true;

  // input / output secondary vertex containers
  std::string m_inContainerName  = "VrtSecInclusive_SecondaryVertices";
  std::string m_outContainerName = "FilteredSecondaryVertices";

  std::string m_decor     = "passSel";
  std::string m_decorTrim = "passTrimSel";
  
  bool m_decorateSelectedObjects = true;
  bool m_createSelectedContainer = false;

  // event-level cuts
  int  m_nToProcess = -1;
  int  m_pass_min   = -1;
  int  m_pass_max   = -1;
  // vertex variable cuts
  float m_r_min    = AlgConsts::maxValue;
  float m_r_max    = AlgConsts::maxValue; // 300 ?? (DV rec)
  float m_z_min    = AlgConsts::maxValue;
  float m_z_max    = AlgConsts::maxValue; // 300 ?? (DV rec)
  float m_chi2_min = AlgConsts::maxValue;
  float m_chi2_max = AlgConsts::maxValue; //   5 ?? (DV rec)
  float m_dist_min = AlgConsts::maxValue;
  float m_dist_max = AlgConsts::maxValue;
  float m_mass_min = AlgConsts::maxValue;
  float m_mass_max = AlgConsts::maxValue; // 25000 ??
  int   m_ntrk_min = -1;
  int   m_ntrk_max = -1;

  // track trimming configurations
  bool   m_doTrackTrimming    = true;
  bool   m_doChi2Filter       = true;
  bool   m_doHitPatternFilter = true;
  bool   m_doIpWrtSVFilter    = true;
  bool   m_doDropAssociated   = false;
  bool   m_doDropNonSelected  = false;
  // default values based on VsiPerf note ... may want/need to change ... STUDY !!!
  double m_trkChi2Cut        = 5.0; // max (off) ??
  double m_d0_wrtSVCut       = 0.8;
  double m_z0_wrtSVCut       = 1.2;
  double m_errd0_wrtSVCut    = AlgConsts::invalidFloat;
  double m_errz0_wrtSVCut    = AlgConsts::invalidFloat;
  double m_d0signif_wrtSVCut = 5.0;
  double m_z0signif_wrtSVCut = 5.0;
  double m_chi2_toSVCut      = 5.0;
  VsiTool::HitPatternCondition m_hitPatternCond = VsiTool::HitPatternCondition::NONE;

  // material map veto
  bool m_doMatMapVeto = true;
  std::string m_matMapInnerFileName   = "";
  std::string m_matMapInnerHistName   = "";
  std::string m_matMapInnerMatrixName = "";
  std::string m_matMapOuterFileName   = "";
  std::string m_matMapOuterHistName   = "";
  
  
  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

 private:
  int m_eventNumber;         //!
  int m_numPassEvents;       //!
  int m_numPassWeightEvents; //!

  double m_mcEventWeight; //!

  VsiBonsai::Configurator m_bonsaiCfg = {}; //!

  TFile*            m_matMapInnerFile    = 0; //!
  TFile*            m_matMapOuterFile    = 0; //!
  TH3S*             m_materialMap_Inner  = 0; //!
  TH3S*             m_materialMap_Outer  = 0; //!
  TMatrixT<double>* m_materialMap_Matrix = 0; //!

  // cutflow
  TH1D* m_cutflowHist  = 0; //!
  TH1D* m_cutflowHistW = 0; //!
  int   m_cutflow_bin;      //!

  // object-level cutflow
  TH1D* m_secVtx_cutflowHist = 0; //!
  int   m_secVtx_cutflow_all;     //!
  int   m_secVtx_cutflow_filtTrk; //!
  int   m_secVtx_cutflow_matVeto; //!
  int   m_secVtx_cutflow_rmin;    //!
  int   m_secVtx_cutflow_rmax;    //!
  int   m_secVtx_cutflow_zmin;    //!
  int   m_secVtx_cutflow_zmax;    //!
  int   m_secVtx_cutflow_ntrkmin; //!
  int   m_secVtx_cutflow_ntrkmax; //!
  int   m_secVtx_cutflow_chi2min; //!
  int   m_secVtx_cutflow_chi2max; //!
  int   m_secVtx_cutflow_massmin; //!
  int   m_secVtx_cutflow_massmax; //!
  int   m_secVtx_cutflow_distmin; //!
  int   m_secVtx_cutflow_distmax; //!

  
 public:
  // standard constructor
  SecondaryVertexSelector ();

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

  virtual int PassCuts ( const xAOD::Vertex* vtx, const xAOD::Vertex* pv );

  //needed to distribute algorithm to workers
  ClassDef ( SecondaryVertexSelector, 1 );
};

#endif // EJsAnalysis_SecondaryVertexSelector_H
