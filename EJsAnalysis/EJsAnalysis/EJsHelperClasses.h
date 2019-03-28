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
    bool m_jets;
    bool m_truth;
    bool m_close;
    bool m_linked;
    bool m_jetMatched;
    
    SecondaryVertexInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };
    virtual ~SecondaryVertexInfoSwitch() {}
    
  protected:
    void initialize();
  };

  
  class TruthVertexInfoSwitch : public HelperClasses::InfoSwitch
  {
  public:
    bool m_isMatched;
    bool m_recoVerts;
    bool m_jets;
    
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
    bool m_match;
    bool m_truthJets;
    bool m_vertices;
    bool m_trackParts;
    
    JetInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };
    virtual ~JetInfoSwitch() {}

  protected:
    void initialize();
  };


  class HistogramInfoSwitch : public HelperClasses::InfoSwitch
  {
  public:
    bool m_kinematic;
    bool m_kinematic_jet;
    bool m_match;
    bool m_match_jet;
    bool m_match_jetTrk;
    bool m_match_jetVtx;
    bool m_match_jetTruth;
    bool m_vsMu;
    bool m_vsMu_jet;
    bool m_vsMu_vtx;
    bool m_jetEConstit;
    bool m_jetTrkMom;
    bool m_jetGhost;
    bool m_vtxTracks;
    int  m_numLeading;
    int  m_numVtxTrk;
    
    
    HistogramInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };
    virtual ~HistogramInfoSwitch() {}

  protected:
    void initialize();
  };
  
} // EJsHelperClasses

#endif // EJsAnalysis_EJsHelperClasses_H
