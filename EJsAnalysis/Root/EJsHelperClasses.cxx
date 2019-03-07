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

  void JetInfoSwitch::initialize() {
    m_constituentAll = has_exact( "constituentAll" );
    m_ghost          = has_exact( "ghost"          );
    m_match          = has_exact( "match"          );
    m_truthJets      = has_exact( "truthJets"      );
    m_vertices       = has_exact( "vertices"       );
    m_trackParts     = has_exact( "trackParts"     );
  }
  
} // EJsHelperClasses
