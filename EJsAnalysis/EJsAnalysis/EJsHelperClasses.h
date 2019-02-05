#ifndef EJsAnalysis_EJsHelperClasses_H
#define EJsAnalysis_EJsHelperClasses_H

/* EJsHelperClasses is a helper class derived from xAODAnaHelpers's HelperClasses class
   that defines EJs-specific info switches (namely for our new vertex container classes) */

#include <xAODAnaHelpers/HelperClasses.h>

namespace EJsHelperClasses {

  
  class SecondaryVertexInfoSwitch : public HelperClasses::InfoSwitch {
  public:
    bool m_tracks;
    bool m_jets;
    bool m_truth;
    bool m_close;
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
