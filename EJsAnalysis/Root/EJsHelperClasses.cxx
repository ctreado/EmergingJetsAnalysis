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
    m_trigTest        = has_exact( "trigTest"        );
    m_abcd            = has_exact( "abcd"            );
    m_cutflow         = has_exact( "cutflow"         );
    m_abcdcutOnly     = has_exact( "abcdcutOnly"     );
    m_truthOnly       = has_exact( "truthOnly"       );
    m_pileup          = has_exact( "pileup"          );
    m_pv              = has_exact( "pv"              );
    m_kinematics      = has_exact( "kinematics"      );
    m_kinematics_jet  = has_exact( "kinematics_jet"  );
    m_kinematics_tjet = has_exact( "kinematics_tjet" );
    m_kinematics_djet = has_exact( "kinematics_djet" );
    m_jetCalo         = has_exact( "jetCalo"         );
    m_jetTrkMom       = has_exact( "jetTrkMom"       );
    m_jetTruth        = has_exact( "jetTruth"        );
    m_jetTrks         = has_exact( "jetTrks"         );
    m_tjetTrks        = has_exact( "tjetTrks"        );
    m_djetTrks        = has_exact( "djetTrks"        );
    m_jetTrksDVTypes  = has_exact( "jetTrksDVTypes"  );
    m_jetVerts        = has_exact( "jetVerts"        );
    m_tjetVerts       = has_exact( "tjetVerts"       );
    m_djetVerts       = has_exact( "djetVerts"       );
    m_jetVertices     = has_exact( "jetVertices"     );
    m_baseJetVerts    = has_exact( "baseJetVerts"    );
    m_matmapJetVerts  = has_exact( "matmapJetVerts"  );
    m_fiducJetVerts   = has_exact( "fiducJetVerts"   );
    m_chi2JetVerts    = has_exact( "chi2JetVerts"    );
    m_ksmJetVerts     = has_exact( "ksmJetVerts"     );
    m_ptJetVerts      = has_exact( "ptJetVerts"      );
    m_d0JetVerts      = has_exact( "d0JetVerts"      );
    m_z0JetVerts      = has_exact( "z0JetVerts"      );
    m_d0z0ErrJetVerts = has_exact( "d0z0ErrJetVerts" );
    m_jetVtxTruth     = has_exact( "jetVtxTruth"     );
    m_dijets          = has_exact( "dijets"          );
    m_njets           = has_exact( "njets"           );
    m_typeJets        = has_exact( "typeJets"        );
    m_tightJets       = has_exact( "tightJets"       );
    m_nsvP4Jets       = has_exact( "nsvP4Jets"       );
    m_nsvPtJets       = has_exact( "nsvPtJets"       );
    m_nsvHtJets       = has_exact( "nsvHtJets"       );
    m_nsvHJets        = has_exact( "nsvHJets"        );
    m_nsvNtrkJets     = has_exact( "nsvNtrkJets"     );
    m_nsvNjtrkJets    = has_exact( "nsvNjtrkJets"    );
    m_nsvTrkJets      = has_exact( "nsvTrkJets"      );
    m_nsvJets         = has_exact( "nsvJets"         );
    m_comboJets       = has_exact( "comboJets"       );
    m_vertices        = has_exact( "vertices"        );
    m_baseVerts       = has_exact( "baseVerts"       );
    m_matmapVerts     = has_exact( "matmapVerts"     );
    m_fiducVerts      = has_exact( "fiducVerts"      );
    m_chi2Verts       = has_exact( "chi2Verts"       );
    m_ksmVerts        = has_exact( "ksmVerts"        );
    m_ptVerts         = has_exact( "ptVerts"         );
    m_d0Verts         = has_exact( "d0Verts"         );
    m_z0Verts         = has_exact( "z0Verts"         );
    m_d0z0ErrVerts    = has_exact( "d0z0ErrVerts"    );
    m_byJetVerts      = has_exact( "byJetVerts"      );
    m_comboVerts      = has_exact( "comboVerts"      );
    m_vtxTruth        = has_exact( "vtxTruth"        );
    m_vtxTrks         = has_exact( "vtxTrks"         );
    m_vtxOverallTrk   = has_exact( "vtxOverallTrk"   );
    m_vtxErrors       = has_exact( "vtxErrors"       );
    m_vtx2D           = has_exact( "vtx2D"           );
    m_llps            = has_exact( "llps"            );
    m_darkPions       = has_exact( "darkPions"       );
    m_kshorts         = has_exact( "kshorts"         );
    m_llpDesc         = has_exact( "llpDesc"         );

    m_numLeadingJets  = 0;
    m_numVtxTrks      = 0;
    for ( auto configDetail : m_configDetails ) {
      if ( configDetail.compare( 0,  9,      "NLeadJets" ) == 0 )
	m_numLeadingJets  = std::atoi( configDetail.substr(  9, std::string::npos ).c_str() );
      if ( configDetail.compare( 0,  8,       "NVtxTrks" ) == 0 )
	m_numVtxTrks      = std::atoi( configDetail.substr(  8, std::string::npos ).c_str() );
    }
  }
  
} // EJsHelperClasses
