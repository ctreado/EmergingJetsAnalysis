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
    m_recoMatchDetail   = has_exact( "recoMatchDetail"  );
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
    m_trigTest       = has_exact( "trigTest"       );
    m_abcd           = has_exact( "abcd"           );
    m_pileup         = has_exact( "pileup"         );
    m_pv             = has_exact( "pv"             );
    m_kinematics     = has_exact( "kinematics"     );
    m_kinematics_jet = has_exact( "kinematics_jet" );
    m_jetCalo        = has_exact( "jetCalo"        );
    m_jetTrkMom      = has_exact( "jetTrkMom"      );
    m_jetTruth       = has_exact( "jetTruth"       );
    m_jetTrks        = has_exact( "jetTrks"        );
    m_jetTrksDVTypes = has_exact( "jetTrksDVTypes" );
    m_jetVerts       = has_exact( "jetVerts"       );
    m_dijets         = has_exact( "dijets"         );
    m_vertices       = has_exact( "vertices"       );
    m_baseVerts      = has_exact( "baseVerts"      );
    m_byJetVerts     = has_exact( "byJetVerts"     );
    m_fiducVerts     = has_exact( "fiducVerts"     );
    m_ksmVerts       = has_exact( "ksmVerts"       );
    m_ptVerts        = has_exact( "ptVerts"        );
    m_d0Verts        = has_exact( "d0Verts"        );
    m_z0Verts        = has_exact( "z0Verts"        );
    m_d0z0ErrVerts   = has_exact( "d0z0ErrVerts"   );
    m_vtxCombos      = has_exact( "vtxCombos"      ); // do combos only, not individual cuts
    m_vtxTruth       = has_exact( "vtxTruth"       );
    m_vtxTrks        = has_exact( "vtxTrks"        );
    m_vtxOverallTrk  = has_exact( "vtxOverallTrk"  );
    m_vtxErrors      = has_exact( "vtxErrors"      );
    m_vtx2D          = has_exact( "vtx2D"          );
    m_llps           = has_exact( "llps"           );
    m_darkPions      = has_exact( "darkPions"      );
    m_kshorts        = has_exact( "kshorts"        );

    m_numLeadingJets  = 0;
    m_numVtxTrks      = 0;
    m_numVtxCutCombos = 0;
    for ( auto configDetail : m_configDetails ) {
      if ( configDetail.compare( 0,  9,      "NLeadJets" ) == 0 )
	m_numLeadingJets  = std::atoi( configDetail.substr(  9, std::string::npos ).c_str() );
      if ( configDetail.compare( 0,  8,       "NVtxTrks" ) == 0 )
	m_numVtxTrks      = std::atoi( configDetail.substr(  8, std::string::npos ).c_str() );
      if ( configDetail.compare( 0, 13,  "NVtxCutCombos" ) == 0 )
	m_numVtxCutCombos = std::atoi( configDetail.substr( 13, std::string::npos ).c_str() ); // -1 = all
      if ( configDetail.compare( 0, 14, "NVtxCutCombosV" ) == 0 ) {
	std::string token;
	std::istringstream vec_str ( configDetail.substr( 14, std::string::npos ) );
	while ( std::getline( vec_str, token, ',' ) )
	  m_numVtxCutCombosVec.push_back( std::atoi(token.c_str()) );
      }
    }
  }
  
} // EJsHelperClasses
