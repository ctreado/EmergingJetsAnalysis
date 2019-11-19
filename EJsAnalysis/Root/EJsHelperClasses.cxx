#include "EJsAnalysis/EJsHelperClasses.h"

namespace EJsHelperClasses {

  void SecondaryVertexInfoSwitch::initialize() {
    m_detail            = has_exact( "detail"            );
    m_tracks            = has_exact( "tracks"            );
    m_trackDetail       = has_exact( "trackDetail"       );
    m_truthMatching     = has_exact( "truthMatching"     );
    m_truthMatchDetail  = has_exact( "truthMatchDetail"  );
    m_jetMatched        = has_exact( "jetMatched"        );
    m_recoJetMatched    = has_exact( "recoJetMatched"    );
    m_truthJetMatched   = has_exact( "truthJetMatched"   );
  }

  void TruthVertexInfoSwitch::initialize() {
    m_detail            = has_exact( "detail"            );
    m_outPartDetail     = has_exact( "outPartDetail"     );
    m_recoMatching      = has_exact( "recoMatching"      );
    m_recoMatchDetail   = has_exact( "reecoMatchDetail"  );
    m_jetMatched        = has_exact( "jetMatched"        );
    m_recoJetMatched    = has_exact( "recoJetMatched"    );
    m_truthJetMatched   = has_exact( "truthJetMatched"   );
  }

  void JetInfoSwitch::initialize() {
    m_constituentAll    = has_exact( "constituentAll"    );
    m_constituentDetail = has_exact( "constituentDetail" );
    m_ghost             = has_exact( "ghost"             );
    m_ghostTracks       = has_exact( "ghostTracks"       );
    m_ghostTruth        = has_exact( "ghostTruth"        );
    m_ghostDetail       = has_exact( "ghostDetail"       );
    m_ghostTrackDetail  = has_exact( "ghostTrackDetail"  );
    m_ghostTruthDetail  = has_exact( "ghostTruthDetail"  );
    m_match             = has_exact( "match"             );
    m_detail            = has_exact( "detail"            );
    m_truthJets         = has_exact( "truthJets"         );
    m_vertices          = has_exact( "vertices"          );
    m_recoVerts         = has_exact( "recoVerts"         );
    m_truthVerts        = has_exact( "truthVerts"        );
    m_trackParts        = has_exact( "trackParts"        );
    m_truthParts        = has_exact( "truthParts"        );
    m_truthJetDetail    = has_exact( "truthJetDetail"    );
    m_vertexDetail      = has_exact( "vertexDetail"      );
    m_recoVtxDetail     = has_exact( "recoVtxDetail"     );
    m_truthVtxDetail    = has_exact( "truthVtxDetail"    );
    m_trackPartDetail   = has_exact( "trackPartDetail"   );
    m_truthPartDetail   = has_exact( "truthPartDetail"   );
  }

  void HistogramInfoSwitch::initialize() {
    m_trigTest          = has_exact( "trigTest"          );
    m_abcd              = has_exact( "abcd"              );
    m_pileup            = has_exact( "pileup"            );
    m_pv                = has_exact( "pv"                );
    m_kinematics        = has_exact( "kinematics"        );
    m_kinematics_jet    = has_exact( "kinematics_jet"    );

    m_numLeadingJets = 0;
    for ( auto configDetail : m_configDetails ) {
      if ( configDetail.compare( 0, 9, "NLeadJets" ) == 0 )
	m_numLeadingJets = std::atoi( configDetail.substr( 9, std::string::npos ).c_str() );
    }
  }
  
} // EJsHelperClasses
