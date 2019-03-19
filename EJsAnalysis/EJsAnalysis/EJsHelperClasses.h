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
    bool m_emtopo;
    bool m_pflow;
    
    SecondaryVertexInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };
    
  protected:
    void initialize();
  };

  
  class TruthVertexInfoSwitch : public HelperClasses::InfoSwitch
  {
  public:
    bool m_isMatched;
    bool m_recoVerts;
    bool m_jets;
    bool m_emtopo;
    bool m_pflow;
    
    TruthVertexInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };

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
    bool m_emtopo;
    bool m_pflow;
    bool m_vertices;
    bool m_trackParts;
    
    JetInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };

  protected:
    void initialize();
  };


  class HistogramInfoSwitch : public HelperClasses::InfoSwitch
  {
  public:
    bool m_basics;
    bool m_jet_basics;
    bool m_secVtx_basics;
    bool m_truthVtx_basics;
    bool m_trk_basics;
    bool m_truthPart_basics;
    
    HistogramInfoSwitch ( const std::string configStr ) : HelperClasses::InfoSwitch( configStr ) { initialize(); };

  protected:
    void initialize();
  };
  
} // EJsHelperClasses

#endif // EJsAnalysis_EJsHelperClasses_H
