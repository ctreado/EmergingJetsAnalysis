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
    m_eventInfo         = has_exact( "eventInfo"         );
    m_pileup            = has_exact( "pileup"            );
    m_pv                = has_exact( "pv"                );
    m_jets              = has_exact( "jets"              );
    m_jet_energy        = has_exact( "jet_energy"        );
    m_jet_constit       = has_exact( "jet_constit"       );
    m_jet_trkMoms       = has_exact( "jet_trkMoms"       );
    m_jet_ghost         = has_exact( "jet_ghost"         );
    m_jet_ghostTrk      = has_exact( "jet_ghostTrk"      );
    m_jet_ghostTruth    = has_exact( "jet_ghostTruth"    );
    m_tjets             = has_exact( "tjets"             );
    m_tjet_energy       = has_exact( "tjet_energy"       );
    m_tjet_constit      = has_exact( "tjet_constit"      );
    m_djets             = has_exact( "djets"             );
    m_djet_energy       = has_exact( "djet_energy"       );
    m_djet_constit      = has_exact( "djet_constit"      );
    m_trks              = has_exact( "trks"              );
    m_tps               = has_exact( "tps"               );
    m_tps_xd            = has_exact( "tps_xd"            );
    m_tps_qd            = has_exact( "tps_qd"            );
    m_tps_pid           = has_exact( "tps_pid"           );
    m_tps_rhod          = has_exact( "tps_rhod"          );
    m_verts             = has_exact( "verts"             );
    m_tverts            = has_exact( "tverts"            );
    m_kinematics        = has_exact( "kinematics"        );
    m_kinematics_jet    = has_exact( "kinematics_jet"    );
    m_kinematics_tjet   = has_exact( "kinematics_tjet"   );
    m_kinematics_djet   = has_exact( "kinematics_djet"   );
    m_kinematics_trk    = has_exact( "kinematics_trk"    );
    m_kinematics_tp     = has_exact( "kinematics_tp"     );
    m_match             = has_exact( "match"             );
    m_match_jet         = has_exact( "match_jet"         );
    m_match_jet_truth   = has_exact( "match_jet_truth"   );
    m_match_jet_trk     = has_exact( "match_jet_trk"     );
    m_match_jet_tp      = has_exact( "match_jet_tp"      );
    m_match_jet_vtx     = has_exact( "match_jet_vtx"     );
    m_match_jet_tvtx    = has_exact( "match_jet_tvtx"    );
    m_match_tjet        = has_exact( "match_tjet"        );
    m_match_tjet_truth  = has_exact( "match_tjet_truth"  );
    m_match_tjet_trk    = has_exact( "match_tjet_trk"    );
    m_match_tjet_tp     = has_exact( "match_tjet_tp"     );
    m_match_tjet_vtx    = has_exact( "match_tjet_vtx"    );
    m_match_tjet_tvtx   = has_exact( "match_tjet_tvtx"   );
    m_match_djet        = has_exact( "match_djet"        );
    m_match_djet_truth  = has_exact( "match_djet_truth"  );
    m_match_djet_trk    = has_exact( "match_djet_trk"    );
    m_match_djet_tp     = has_exact( "match_djet_tp"     );
    m_match_djet_vtx    = has_exact( "match_djet_vtx"    );
    m_match_djet_tvtx   = has_exact( "match_djet_tvtx"   );
    
    m_numLeadingJets  = 0; // jets
    m_numLeadingTJets = 0; // truth jets
    m_numLeadingDJets = 0; // dark jets
    m_numVtxTrks      = 0; // secondary vertices
    m_numTVtxTrks     = 0; // truth vertices
    for ( auto configDetail : m_configDetails ) {
      if ( configDetail.compare( 0, 9,  "NLeadJets"  ) == 0 )
	m_numLeadingJets  = std::atoi( configDetail.substr( 9,  std::string::npos ).c_str() );
      if ( configDetail.compare( 0, 10, "NLeadTJets" ) == 0 )
	m_numLeadingTJets = std::atoi( configDetail.substr( 10, std::string::npos ).c_str() );
      if ( configDetail.compare( 0, 10, "NLeadDJets" ) == 0 )
	m_numLeadingDJets = std::atoi( configDetail.substr( 10, std::string::npos ).c_str() );
      if ( configDetail.compare( 0, 8,  "NVtxTrks"   ) == 0 )
	m_numVtxTrks      = std::atoi( configDetail.substr( 8,  std::string::npos ).c_str() );
      if ( configDetail.compare( 0, 9,  "NTVtxTrks"  ) == 0 )
	m_numTVtxTrks     = std::atoi( configDetail.substr( 9,  std::string::npos ).c_str() );
    }
  }
  
} // EJsHelperClasses
