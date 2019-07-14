#ifndef EJsAnalysis_TruthVertexSelector_H
#define EJsAnalysis_TruthVertexSelector_H

/* TruthVertexSelector is the algorithm responsible for selecting truth vertices */

#include <string>
#include <vector>

#include <TH1.h>

#include <xAODTruth/TruthVertex.h>

#include <xAODAnaHelpers/Algorithm.h>

#include "EJsAnalysis/AlgConsts.h"


class TruthVertexSelector : public xAH::Algorithm
{
  // configuration variables
  // public so they can be seen directly from CINT + python
 public:
  // float cutValue;

  bool m_useCutFlow = true;

  // input / output truth vertex containers
  std::string m_inContainerName  = "TruthVertices";
  std::string m_outContainerName = "FilteredTruthVertices";

  std::string m_decor = "passSel";

  bool m_decorateSelectedObjects = true;
  bool m_createSelectedContainer = false;

  // event-level cuts
  int m_nToProcess = -1;
  int m_pass_min   = -1;
  int m_pass_max   = -1;
  // truth vertex variable cuts
  float m_r_min         = AlgConsts::maxValue;
  float m_r_max         = AlgConsts::maxValue; //  563 ?? (VsiPerf rec)
  float m_z_min         = AlgConsts::maxValue;
  float m_z_max         = AlgConsts::maxValue; // 2720 ?? (VsiPerf rec)
  float m_mass_min      = AlgConsts::maxValue;
  float m_mass_max      = AlgConsts::maxValue;
  int   m_nVisOutP_min  = -1;
  int   m_nVisOutP_max  = -1;
  float m_outP_ptThresh = 1000;

  // LLP-decay selections
  std::string m_truthLLP = "DarkPion";


  // variables not filled at submission time
  // protected from being sent from submission to worker node
 public:
  // TTree *myTree; //!
  // TH1 *myHist; //!

 private:
  int m_eventNumber; //!
  int m_numPassEvents; //!
  int m_numPassWeightEvents; //!

  double m_mcEventWeight; //!

  // cutflow
  TH1D* m_cutflowHist  = 0; //!
  TH1D* m_cutflowHistW = 0; //!
  int   m_cutflow_bin  = 0; //!

  // object-level cutflow
  TH1D* m_truthVtx_cutflowHist = 0;     //!
  int   m_truthVtx_cutflow_all;         //!
  int   m_truthVtx_cutflow_rmin;        //!
  int   m_truthVtx_cutflow_rmax;        //!
  int   m_truthVtx_cutflow_zmin;        //!
  int   m_truthVtx_cutflow_zmax;        //!
  int   m_truthVtx_cutflow_nVisOutPmin; //!
  int   m_truthVtx_cutflow_nVisOutPmax; //!
  int   m_truthVtx_cutflow_massmin;     //!
  int   m_truthVtx_cutflow_massmax;     //!


 public:
  // standard constructor
  TruthVertexSelector ();

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

  virtual int PassCuts ( const xAOD::TruthVertex* );

  // needed to distribute algorithm to workers
  ClassDef ( TruthVertexSelector, 1 );
};

#endif // EJsAnalysis_TruthVertexSelector_H
