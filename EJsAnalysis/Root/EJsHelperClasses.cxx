#include "EJsAnalysis/EJsHelperClasses.h"

namespace EJsHelperClasses {

  void SecondaryVertexInfoSwitch::initialize() {
    m_tracks     = has_exact( "tracks"     );
    m_jets       = has_exact( "jets"       );
    m_truth      = has_exact( "truth"      );
    m_close      = has_exact( "close"      );
    m_linked     = has_exact( "linked"     );
    m_jetMatched = has_exact( "jetMatched" );
    m_emtopo     = has_exact( "emtopo"     );
    m_pflow      = has_exact( "pflow"      );
  }

  void TruthVertexInfoSwitch::initialize() {
    m_isMatched = has_exact( "isMatched" );
    m_recoVerts = has_exact( "recoVerts" );
    m_jets      = has_exact( "jets"      );
    m_emtopo    = has_exact( "emtopo"    );
    m_pflow     = has_exact( "pflow"     );
  }

  void JetInfoSwitch::initialize() {
    m_constituentAll = has_exact( "constituentAll" );
    m_ghost          = has_exact( "ghost"          );
    m_match          = has_exact( "match"          );
    m_truthJets      = has_exact( "truthJets"      );
    m_emtopo         = has_exact( "emtopo"         );
    m_pflow          = has_exact( "pflow"          );
    m_vertices       = has_exact( "vertices"       );
    m_trackParts     = has_exact( "trackParts"     );
  }

  void HistogramInfoSwitch::initialize() {
    m_basics           = has_exact( "basics"           );
    m_jet_basics       = has_exact( "jet_basics"       );
    m_secVtx_basics    = has_exact( "secVtx_basics"    );
    m_truthVtx_basics  = has_exact( "truthVtx_basics"  );
    m_trk_basics       = has_exact( "trk_basics"       );
    m_truthPart_basics = has_exact( "truthPart_basics" );
  }
  
} // EJsHelperClasses
