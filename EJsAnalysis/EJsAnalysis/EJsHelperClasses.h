#ifndef EJsAnalysis_EJsHelperClasses_H
#define EJsAnalysis_EJsHelperClasses_H

#include <xAODAnaHelpers/HelperClasses.h>

namespace EJsHelperClasses {

  
  class SecondaryVertexInfoSwitch : public HelperClasses::InfoSwitch {
  public:
    bool m_tracks;
    bool m_jets;
    bool m_truth;
    bool m_closest;
    bool m_linked;
    
    SecondaryVertexInfoSwitch ( const std::string configStr ) :
    HelperClasses::InfoSwitch( configStr ) { initialize(); };
    
  protected:
    void initialize();
  };

  
  class TruthVertexInfoSwitch : public HelperClasses::InfoSwitch {
  public:
    // nothing here yet ...
    
    TruthVertexInfoSwitch ( const std::string configStr ) :
    HelperClasses::InfoSwitch( configStr ) { initialize(); };

  protected:
    void initialize();
  };
  
} // EJsHelperClasses

#endif // EJsAnalysis_EJsHelperClasses_H
