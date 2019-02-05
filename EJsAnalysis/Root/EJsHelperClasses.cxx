#include "EJsAnalysis/EJsHelperClasses.h"

namespace EJsHelperClasses {

  void SecondaryVertexInfoSwitch::initialize() {
    m_tracks = has_exact( "tracks" );
    m_jets   = has_exact( "jets"   );
    m_truth  = has_exact( "truth"  );
    m_close  = has_exact( "close"  );
    m_linked = has_exact( "linked" );
  }

  void TruthVertexInfoSwitch::initialize() {
    // nothing here yet...
  }
  
} // EJsHelperClasses
