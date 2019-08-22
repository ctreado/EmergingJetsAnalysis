#include "EJsAnalysis/EJsHelperClasses.h"

namespace EJsHelperClasses {

  void SecondaryVertexInfoSwitch::initialize() {
    m_tracks          = has_exact( "tracks"          );
    m_truthMatching   = has_exact( "truthMatching"   );
    m_jetMatched      = has_exact( "jetMatched"      );
    m_recoJetMatched  = has_exact( "recoJetMatched"  );
    m_truthJetMatched = has_exact( "truthJetMatched" );
  }

  void TruthVertexInfoSwitch::initialize() {
    m_recoMatching    = has_exact( "recoMatching"    );
    m_jetMatched      = has_exact( "jetMatched"      );
    m_recoJetMatched  = has_exact( "recoJetMatched"  );
    m_truthJetMatched = has_exact( "truthJetMatched" );
  }

  void JetInfoSwitch::initialize() {
    m_constituentAll = has_exact( "constituentAll" );
    m_ghost          = has_exact( "ghost"          );
    m_ghostTracks    = has_exact( "ghostTracks"    );
    m_ghostTruth     = has_exact( "ghostTruth"     );
    m_match          = has_exact( "match"          );
    m_truthJets      = has_exact( "truthJets"      );
    m_vertices       = has_exact( "vertices"       );
    m_recoVerts      = has_exact( "recoVerts"      );
    m_truthVerts     = has_exact( "truthVerts"     );
    m_trackParts     = has_exact( "trackParts"     );
    m_truthParts     = has_exact( "truthParts"     );
  }

  void HistogramInfoSwitch::initialize() {
    m_kinematic      = has_exact( "kinematic"      );
    m_kinematic_jet  = has_exact( "kinematic_jet"  );
    m_match          = has_exact( "match"          );
    m_match_jet      = has_exact( "match_jet"      );
    m_match_jetTrk   = has_exact( "match_jetTrk"   );
    m_match_jetVtx   = has_exact( "match_jetVtx"   );
    m_match_jetTruth = has_exact( "match_jetTruth" );
    m_vsMu           = has_exact( "vsMu"           );
    m_vsMu_jet       = has_exact( "vsMu_jet"       );
    m_vsMu_vtx       = has_exact( "vsMu_vtx"       );
    m_jetEConstit    = has_exact( "jetEConstit"    );
    m_jetTrkMom      = has_exact( "jetTrkMom"      );
    m_jetGhost       = has_exact( "jetGhost"       );
    m_vtxTracks      = has_exact( "vtxTracks"      );
    
    m_numLeading = 0;
    m_numVtxTrk  = 0;
    for ( auto configDetail : m_configDetails ) {
      if ( configDetail.compare( 0, 8, "NLeading" ) == 0 )
    	m_numLeading = std::atoi( configDetail.substr( 8, std::string::npos ).c_str() );
      if ( configDetail.compare( 0, 7, "NVtxTrk"  ) == 0 )
	m_numVtxTrk  = std::atoi( configDetail.substr( 7, std::string::npos ).c_str() );
    }
  }
  
} // EJsHelperClasses
