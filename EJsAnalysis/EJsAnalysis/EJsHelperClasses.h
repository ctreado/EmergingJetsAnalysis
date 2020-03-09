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
    bool m_detail;
    bool m_tracks;
    bool m_trackDetail;
    bool m_truthMatching;
    bool m_truthMatchDetail;
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
    bool m_detail;
    bool m_outPartDetail;
    bool m_recoMatching;
    bool m_recoMatchDetail;
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
    bool m_constituentDetail;
    bool m_ghost;
    bool m_ghostTracks;
    bool m_ghostTruth;
    bool m_ghostDetail;
    bool m_ghostTrackDetail;
    bool m_ghostTruthDetail;
    bool m_match;
    bool m_detail;
    bool m_truthJets;
    bool m_vertices;
    bool m_recoVerts;
    bool m_truthVerts;
    bool m_trackParts;
    bool m_truthParts;
    bool m_truthJetDetail;
    bool m_vertexDetail;
    bool m_recoVtxDetail;
    bool m_truthVtxDetail;
    bool m_trackPartDetail;
    bool m_truthPartDetail;
    
    JetInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };
    virtual ~JetInfoSwitch() {}

  protected:
    void initialize();
  };


  class HistogramInfoSwitch : public HelperClasses::InfoSwitch
  {
  public:
    bool m_trigTest;
    bool m_abcd;
    bool m_pileup;
    bool m_pv;
    bool m_kinematics;
    bool m_kinematics_jet;
    bool m_jetTruth;
    bool m_jetTrks;
    bool m_jetVerts;
    bool m_dijets;
    bool m_vertices;
    bool m_baseVerts;
    bool m_byJetVerts;
    bool m_fiducialVerts;
    bool m_ksmVerts;
    bool m_ptVerts;
    bool m_d0Verts;
    bool m_z0Verts;
    bool m_d0z0ErrVerts;
    bool m_vtxTruth;
    bool m_vtxTrks;
    bool m_vtxErrors;
    bool m_vtx2D;
    bool m_llps;
    bool m_darkPions;
    bool m_kshorts;

    int  m_numLeadingJets; // n leading jets
    int  m_numVtxTrks;     // n vertex tracks
    
    HistogramInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };
    virtual ~HistogramInfoSwitch() {}

  protected:
    void initialize();
  };
  
} // EJsHelperClasses

#endif // EJsAnalysis_EJsHelperClasses_H
