#ifndef EJsAnalysis_EJsHistogramManager_H
#define EJsAnalysis_EJsHistogramManager_H

#include <string>
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

  StatusCode connectSecVerts ( TTree* tree, const std::string secVtxName = "secVtx",
			       const std::string secVtxDetailStr = "" );
  // add other connect functions for all types of objects ...
  StatusCode initialize      ( const std::string secVtxDetailStr = "" ); 
  StatusCode execute         ( TTree* tree, Long64_t treeEntry,
			       const std::string secVtxDetailStr = "" );
  // add other detail strings as input parameters to intialize + execute
  // to account for all types of objects ...

  using HistogramManager::book;    // overload
  using HistogramManager::execute; // overload


 protected:
  
  // holds bools to control which histograms to be filled
  EJsHelperClasses::SecondaryVertexInfoSwitch* m_secVtxInfoSwitch;

  
 private:

  // branches -- secondary vertex
  uint32_t                         m_secVtx_n;               //!
  std::vector<float>*              m_secVtx_x;               //!
  std::vector<float>*              m_secVtx_y;               //!
  std::vector<float>*              m_secVtx_z;               //!
  std::vector<float>*              m_secVtx_r;               //!
  std::vector<float>*              m_secVtx_pt;              //!
  std::vector<float>*              m_secVtx_eta;             //!
  std::vector<float>*              m_secVtx_phi;             //!
  std::vector<float>*              m_secVtx_mass;            //!

  std::vector<uint32_t>*           m_secVtx_ntrk;            //!
  std::vector<uint32_t>*           m_secVtx_ntrk_sel;        //!
  std::vector<uint32_t>*           m_secVtx_ntrk_assoc;      //!

  
  // histograms -- secondary vertex
  TH1F* h_secVtx_n;             //!
  TH1F* h_secVtx_x;             //!
  TH1F* h_secVtx_y;             //!
  TH1F* h_secVtx_z;             //!
  TH1F* h_secVtx_r;             //!
  TH1F* h_secVtx_pt;            //!
  TH1F* h_secVtx_eta;           //!
  TH1F* h_secVtx_phi;           //!
  TH1F* h_secVtx_mass;          //!

  TH1F* h_secVtx_ntrk;          //!
  TH1F* h_secVtx_ntrk_sel;      //!
  TH1F* h_secVtx_ntrk_assoc;    //!
  
};

#endif // EJsAnalysis_EJsHistogramManager_H
