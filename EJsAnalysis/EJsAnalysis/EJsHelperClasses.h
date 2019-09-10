#ifndef EJsAnalysis_EJsHelperClasses_H
#define EJsAnalysis_EJsHelperClasses_H

/* EJsHelperClasses is a helper class derived from xAODAnaHelpers's HelperClasses class
   that defines EJs-specific info switches (namely for our new vertex container classes) */

#include <string>

#include <xAODAnaHelpers/HelperClasses.h>

namespace EJsHelperClasses {

  class SecondaryVertexInfoSwitch : public HelperClasses::InfoSwitch
  {
  public:
    bool m_tracks;
    bool m_truthMatching;
    bool m_jetMatched;
    bool m_recoJetMatched;
    bool m_truthJetMatched;
    
    SecondaryVertexInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };
    virtual ~SecondaryVertexInfoSwitch() {}
    
  protected:
    void initialize();
  };

  
  class TruthVertexInfoSwitch : public HelperClasses::InfoSwitch
  {
  public:
    bool m_recoMatching;
    bool m_jetMatched;
    bool m_recoJetMatched;
    bool m_truthJetMatched;
    
    TruthVertexInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };
    virtual ~TruthVertexInfoSwitch() {}

  protected:
    void initialize();
  };


  class JetInfoSwitch : public HelperClasses::InfoSwitch
  {
  public:
    bool m_constituentAll;
    bool m_ghost;
    bool m_ghostTracks;
    bool m_ghostTruth;
    bool m_match;
    bool m_truthJets;
    bool m_vertices;
    bool m_recoVerts;
    bool m_truthVerts;
    bool m_trackParts;
    bool m_truthParts;
    
    JetInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };
    virtual ~JetInfoSwitch() {}

  protected:
    void initialize();
  };


  class HistogramInfoSwitch : public HelperClasses::InfoSwitch
  {
  public:
    bool m_eventInfo;        // event info
    bool m_pileup;
    bool m_pv;
    bool m_jets;             // reco jets
    bool m_jet_energy;
    bool m_jet_constit;
    bool m_jet_trkMoms;
    bool m_jet_ghost;
    bool m_jet_ghostTrk;
    bool m_jet_ghostTruth;
    bool m_tjets;            // truth jets
    bool m_tjet_energy;
    bool m_tjet_constit;
    bool m_djets;            // dark jets
    bool m_djet_energy;
    bool m_djet_constit;
    bool m_trks;             // tracks
    bool m_tps;              // truth particles
    bool m_tps_xd;
    bool m_tps_qd;
    bool m_tps_pid;
    bool m_tps_rhod;
    bool m_verts;            // secondary vertices
    bool m_tverts;           // truth vertices
    bool m_kinematics;       // object kinematics
    bool m_kinematics_jet;
    bool m_kinematics_tjet;
    bool m_kinematics_djet;
    bool m_kinematics_trk;
    bool m_kinematics_tp;
    bool m_match;            // matched objects
    bool m_match_jet;
    bool m_match_jet_truth;
    bool m_match_jet_trk;
    bool m_match_jet_tp;
    bool m_match_jet_vtx;
    bool m_match_jet_tvtx;
    bool m_match_tjet;
    bool m_match_tjet_truth;
    bool m_match_tjet_trk;
    bool m_match_tjet_tp;
    bool m_match_tjet_vtx;
    bool m_match_tjet_tvtx;
    bool m_match_djet;
    bool m_match_djet_truth;
    bool m_match_djet_trk;
    bool m_match_djet_tp;
    bool m_match_djet_vtx;
    bool m_match_djet_tvtx;
    
    int  m_numLeadingJets;   // leading jets
    int  m_numLeadingTJets;  // leading truth jets
    int  m_numLeadingDJets;  // leading dark jets
    int  m_numVtxTrks;       // n secondary vertex tracks
    int  m_numTVtxTrks;      // n truth vertex "tracks"    
    
    HistogramInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };
    virtual ~HistogramInfoSwitch() {}

  protected:
    void initialize();
  };
  
} // EJsHelperClasses

#endif // EJsAnalysis_EJsHelperClasses_H
