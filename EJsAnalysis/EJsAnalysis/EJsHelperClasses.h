#ifndef EJsAnalysis_EJsHelperClasses_H
#define EJsAnalysis_EJsHelperClasses_H

/* EJsHelperClasses is a helper class derived from xAODAnaHelpers's HelperClasses class
   that defines EJs-specific info switches (namely for our new vertex container classes) */

#include <string>
#include <vector>

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
    bool m_cutflow;
    bool m_abcdcutOnly;
    bool m_truthOnly;
    bool m_pileup;
    bool m_pv;
    bool m_kinematics;
    bool m_kinematics_jet;
    bool m_kinematics_tjet;
    bool m_kinematics_djet;
    bool m_jetCalo;
    bool m_jetTrkMom;
    bool m_jetTruth;
    bool m_jetTrks;
    bool m_tjetTrks;
    bool m_djetTrks;
    bool m_jetTrksDVTypes;
    bool m_jetVerts;
    bool m_tjetVerts;
    bool m_djetVerts;
    bool m_jetVertices;
    bool m_baseJetVerts;
    bool m_matmapJetVerts;
    bool m_fiducJetVerts;
    bool m_chi2JetVerts;
    bool m_ksmJetVerts;
    bool m_ptJetVerts;
    bool m_d0JetVerts;
    bool m_z0JetVerts;
    bool m_d0z0ErrJetVerts;
    bool m_jetVtxTruth;
    bool m_dijets;
    bool m_dijetTrks;
    bool m_dijetVerts;
    bool m_njets;
    bool m_njetTrks;
    bool m_njetVerts;
    bool m_typeJets;
    bool m_tightJets;
    bool m_nsvP4Jets;
    bool m_nsvPtJets;
    bool m_nsvHtJets;
    bool m_nsvHJets;
    bool m_nsvNtrkJets;
    bool m_nsvNjtrkJets;
    bool m_nsvTrkJets;
    bool m_nsvJets;
    bool m_comboJets;
    bool m_emergingJets;
    bool m_vertices;
    bool m_baseVerts;
    bool m_matmapVerts;
    bool m_fiducVerts;
    bool m_chi2Verts;
    bool m_ksmVerts;
    bool m_ptVerts;
    bool m_d0Verts;
    bool m_z0Verts;
    bool m_d0z0ErrVerts;
    bool m_byJetVerts;
    bool m_comboVerts;
    bool m_vtxTruth;
    bool m_vtxTrks;
    bool m_vtxOverallTrk;
    bool m_vtxErrors;
    bool m_vtx2D;
    bool m_llps;
    bool m_darkPions;
    bool m_kshorts;
    bool m_llpDesc;
    bool m_llpRecoEff;
    bool m_llpvtxRecoEff;
    bool m_llptrkRecoEff;
    bool m_vrshift;

    int m_numLeadingJets; // n leading jets
    int m_numVtxTrks;     // n vertex tracks
    
    HistogramInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };
    virtual ~HistogramInfoSwitch() {}

  protected:
    void initialize();
  };
  
} // EJsHelperClasses

#endif // EJsAnalysis_EJsHelperClasses_H
