#include <TLorentzVector.h>

#include "EJsAnalysis/JetContainer.h"
#include "EJsAnalysis/EJsHelperFunctions.h"
#include "EJsAnalysis/VsiBonsaiTool.h"

using namespace EJs;

JetContainer :: JetContainer ( const std::string& name, const std::string& detailStr, float units, bool mc ) :
  VertexContainer ( name, detailStr, units, mc )
{
  if ( m_debug ) Info( "EJs::JetContainer()", "setting up" );

  m_ID     = new std::vector<int>;
  m_radius = new std::vector<float>;

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    m_isTruthMatched   = new std::vector<uint8_t>;
    m_truthMatchID     = new std::vector<int>;
    m_truthMatchDR     = new std::vector<float>;
    m_truthNonmatchIDs = new std::vector<std::vector<int>>;
    m_truthNonmatchDRs = new std::vector<std::vector<float>>;
    m_isDarkMatched    = new std::vector<uint8_t>;
    m_darkMatchID      = new std::vector<int>;
    m_darkMatchDR      = new std::vector<float>;
    m_darkNonmatchIDs  = new std::vector<std::vector<int>>;
    m_darkNonmatchDRs  = new std::vector<std::vector<float>>;
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    m_secVtx_ID                                   = new std::vector<std::vector<int>>;
    m_secVtx_x                                    = new std::vector<std::vector<float>>;
    m_secVtx_y                                    = new std::vector<std::vector<float>>;
    m_secVtx_z                                    = new std::vector<std::vector<float>>;
    m_secVtx_r                                    = new std::vector<std::vector<float>>;
    m_secVtx_pt                                   = new std::vector<std::vector<float>>;
    m_secVtx_eta                                  = new std::vector<std::vector<float>>;
    m_secVtx_phi                                  = new std::vector<std::vector<float>>;
    m_secVtx_mass                                 = new std::vector<std::vector<float>>;
    m_secVtx_ntrk                                 = new std::vector<std::vector<int>>;
    m_secVtx_dR                                   = new std::vector<std::vector<float>>;
    if ( m_mc ) {
      m_secVtx_closestTruth_isDarkPionDecay       = new std::vector<std::vector<uint8_t>>;
      m_secVtx_closestTruth_ID                    = new std::vector<std::vector<int>>;
      m_secVtx_closestTruth_barcode               = new std::vector<std::vector<int>>;
      m_secVtx_closestTruth_distance              = new std::vector<std::vector<float>>;
      m_secVtx_maxlinkTruth_isDarkPionDecay       = new std::vector<std::vector<uint8_t>>;
      m_secVtx_maxlinkTruth_ID                    = new std::vector<std::vector<int>>;
      m_secVtx_maxlinkTruth_barcode               = new std::vector<std::vector<int>>;
      m_secVtx_maxlinkTruth_score                 = new std::vector<std::vector<float>>;
      m_secVtx_maxlinkParentTruth_isDarkPionDecay = new std::vector<std::vector<uint8_t>>;
      m_secVtx_maxlinkParentTruth_ID              = new std::vector<std::vector<int>>;
      m_secVtx_maxlinkParentTruth_barcode         = new std::vector<std::vector<int>>;
      m_secVtx_maxlinkParentTruth_score           = new std::vector<std::vector<float>>;
      m_truthVtx_isDarkPionDecay                  = new std::vector<std::vector<uint8_t>>;
      m_truthVtx_ID                               = new std::vector<std::vector<int>>;
      m_truthVtx_x                                = new std::vector<std::vector<float>>;
      m_truthVtx_y                                = new std::vector<std::vector<float>>;
      m_truthVtx_z                                = new std::vector<std::vector<float>>;
      m_truthVtx_r                                = new std::vector<std::vector<float>>;
      m_truthVtx_eta                              = new std::vector<std::vector<float>>;
      m_truthVtx_phi                              = new std::vector<std::vector<float>>;
      m_truthVtx_barcode                          = new std::vector<std::vector<int>>;
      m_truthVtx_dR                               = new std::vector<std::vector<float>>;
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    m_trk_ID                = new std::vector<std::vector<int>>;
    m_trk_qOverP            = new std::vector<std::vector<float>>;
    m_trk_E                 = new std::vector<std::vector<float>>;
    m_trk_M                 = new std::vector<std::vector<float>>;
    m_trk_pt                = new std::vector<std::vector<float>>;
    m_trk_eta               = new std::vector<std::vector<float>>;
    m_trk_phi               = new std::vector<std::vector<float>>;
    m_trk_d0                = new std::vector<std::vector<float>>;
    m_trk_z0                = new std::vector<std::vector<float>>;
    m_trk_errd0             = new std::vector<std::vector<float>>;
    m_trk_errz0             = new std::vector<std::vector<float>>;
    m_trk_chi2              = new std::vector<std::vector<float>>;
    m_trk_charge            = new std::vector<std::vector<float>>;
    m_trk_isSelected        = new std::vector<std::vector<uint8_t>>;
    m_trk_isAssociated      = new std::vector<std::vector<uint8_t>>;
    m_trk_dR                = new std::vector<std::vector<float>>;
    if ( m_mc ) {
      m_trk_isTruth         = new std::vector<std::vector<uint8_t>>;
      m_trk_truthProb       = new std::vector<std::vector<float>>;
      m_trk_truthID         = new std::vector<std::vector<int>>;
      m_trk_truthBarcode    = new std::vector<std::vector<int>>;
      m_trk_truthPid        = new std::vector<std::vector<int>>;
      m_tp_ID               = new std::vector<std::vector<int>>;
      m_tp_pt               = new std::vector<std::vector<float>>;
      m_tp_eta              = new std::vector<std::vector<float>>;
      m_tp_phi              = new std::vector<std::vector<float>>;
      m_tp_E                = new std::vector<std::vector<float>>;
      m_tp_M                = new std::vector<std::vector<float>>;
      m_tp_charge           = new std::vector<std::vector<float>>;
      m_tp_pid              = new std::vector<std::vector<int>>;
      m_tp_status           = new std::vector<std::vector<int>>;
      m_tp_barcode          = new std::vector<std::vector<int>>;
      m_tp_dR               = new std::vector<std::vector<float>>;
      m_tp_isReco           = new std::vector<std::vector<uint8_t>>;
      m_tp_recoProb         = new std::vector<std::vector<float>>;
      m_tp_recoID           = new std::vector<std::vector<int>>;
      m_tp_recoIsSelected   = new std::vector<std::vector<uint8_t>>;
      m_tp_recoIsAssociated = new std::vector<std::vector<uint8_t>>;  
    }
  }

  if ( m_infoSwitch.m_ghost ) {
    m_GhostTrack_ID                 = new std::vector<std::vector<int>>;
    m_GhostTrack_m                  = new std::vector<std::vector<float>>;
    m_GhostTrack_errd0              = new std::vector<std::vector<float>>;
    m_GhostTrack_errz0              = new std::vector<std::vector<float>>;
    m_GhostTrack_chi2               = new std::vector<std::vector<float>>;
    m_GhostTrack_charge             = new std::vector<std::vector<float>>;
    m_GhostTrack_isSelected         = new std::vector<std::vector<uint8_t>>;
    m_GhostTrack_isAssociated       = new std::vector<std::vector<uint8_t>>;
    if ( m_mc ) {
      m_GhostTrack_isTruth          = new std::vector<std::vector<uint8_t>>;
      m_GhostTrack_truthProb        = new std::vector<std::vector<float>>;
      m_GhostTrack_truthID          = new std::vector<std::vector<int>>;
      m_GhostTrack_truthBarcode     = new std::vector<std::vector<int>>;
      m_GhostTrack_truthPid         = new std::vector<std::vector<int>>;
      m_GhostTruthCount             = new std::vector<int>;
      m_GhostTruthPt                = new std::vector<float>;
      m_GhostTruth_ID               = new std::vector<std::vector<int>>;
      m_GhostTruth_pt               = new std::vector<std::vector<float>>;
      m_GhostTruth_eta              = new std::vector<std::vector<float>>;
      m_GhostTruth_phi              = new std::vector<std::vector<float>>;
      m_GhostTruth_e                = new std::vector<std::vector<float>>;
      m_GhostTruth_m                = new std::vector<std::vector<float>>;
      m_GhostTruth_charge           = new std::vector<std::vector<float>>;
      m_GhostTruth_pid              = new std::vector<std::vector<int>>;
      m_GhostTruth_status           = new std::vector<std::vector<int>>;
      m_GhostTruth_barcode          = new std::vector<std::vector<int>>;
      m_GhostTruth_isReco           = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_recoProb         = new std::vector<std::vector<float>>;
      m_GhostTruth_recoID           = new std::vector<std::vector<int>>;
      m_GhostTruth_recoIsSelected   = new std::vector<std::vector<uint8_t>>;
      m_GhostTruth_recoIsAssociated = new std::vector<std::vector<uint8_t>>;
    }
  }

  if ( m_infoSwitch.m_constituentAll )
    m_constituent_m = new std::vector<std::vector<float>>;
}


JetContainer :: ~JetContainer ()
{
  if ( m_debug ) Info( "EJs::JetContainer()", "deleting" );

  delete m_ID;
  delete m_radius;

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    delete m_isTruthMatched;
    delete m_truthMatchID;
    delete m_truthMatchDR;
    delete m_truthNonmatchIDs;
    delete m_truthNonmatchDRs;
    delete m_isDarkMatched;
    delete m_darkMatchID;
    delete m_darkMatchDR;
    delete m_darkNonmatchIDs;
    delete m_darkNonmatchDRs;
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    delete m_secVtx_ID;
    delete m_secVtx_x;
    delete m_secVtx_y;
    delete m_secVtx_z;
    delete m_secVtx_r;
    delete m_secVtx_pt;
    delete m_secVtx_eta;
    delete m_secVtx_phi;
    delete m_secVtx_mass;
    delete m_secVtx_ntrk;
    delete m_secVtx_dR;
    if ( m_mc ) {
      delete m_secVtx_closestTruth_isDarkPionDecay;
      delete m_secVtx_closestTruth_ID;
      delete m_secVtx_closestTruth_barcode;
      delete m_secVtx_closestTruth_distance;
      delete m_secVtx_maxlinkTruth_isDarkPionDecay;
      delete m_secVtx_maxlinkTruth_ID;
      delete m_secVtx_maxlinkTruth_barcode;
      delete m_secVtx_maxlinkTruth_score;
      delete m_secVtx_maxlinkParentTruth_isDarkPionDecay;
      delete m_secVtx_maxlinkParentTruth_ID;
      delete m_secVtx_maxlinkParentTruth_barcode;
      delete m_secVtx_maxlinkParentTruth_score;
      delete m_truthVtx_isDarkPionDecay;
      delete m_truthVtx_ID;
      delete m_truthVtx_x;
      delete m_truthVtx_y;
      delete m_truthVtx_z;
      delete m_truthVtx_r;
      delete m_truthVtx_eta;
      delete m_truthVtx_phi;
      delete m_truthVtx_barcode;
      delete m_truthVtx_dR;
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    delete m_trk_ID;
    delete m_trk_qOverP;
    delete m_trk_E;
    delete m_trk_M;
    delete m_trk_pt;
    delete m_trk_eta;
    delete m_trk_phi;
    delete m_trk_d0;
    delete m_trk_z0;
    delete m_trk_errd0;
    delete m_trk_errz0;
    delete m_trk_chi2;
    delete m_trk_charge;
    delete m_trk_isSelected;
    delete m_trk_isAssociated;
    delete m_trk_dR;
    if ( m_mc ) {
      delete m_trk_isTruth;
      delete m_trk_truthProb;
      delete m_trk_truthID;
      delete m_trk_truthBarcode;
      delete m_trk_truthPid;
      delete m_tp_ID;
      delete m_tp_pt;
      delete m_tp_eta;
      delete m_tp_phi;
      delete m_tp_E;
      delete m_tp_M;
      delete m_tp_charge;
      delete m_tp_pid;
      delete m_tp_status;
      delete m_tp_barcode;
      delete m_tp_dR;
      delete m_tp_isReco;
      delete m_tp_recoProb;
      delete m_tp_recoID;
      delete m_tp_recoIsSelected;
      delete m_tp_recoIsAssociated;
    }
  }

  if ( m_infoSwitch.m_ghost ) {
    delete m_GhostTrack_ID;
    delete m_GhostTrack_m;
    delete m_GhostTrack_errd0;
    delete m_GhostTrack_errz0;
    delete m_GhostTrack_chi2;
    delete m_GhostTrack_charge;
    delete m_GhostTrack_isSelected;
    delete m_GhostTrack_isAssociated;
    if ( m_mc ) {
      delete m_GhostTrack_isTruth;
      delete m_GhostTrack_truthProb;
      delete m_GhostTrack_truthID;
      delete m_GhostTrack_truthBarcode;
      delete m_GhostTrack_truthPid;
      delete m_GhostTruthCount;
      delete m_GhostTruthPt;
      delete m_GhostTruth_ID;
      delete m_GhostTruth_pt;
      delete m_GhostTruth_eta; 
      delete m_GhostTruth_phi;
      delete m_GhostTruth_e;
      delete m_GhostTruth_m;
      delete m_GhostTruth_charge;
      delete m_GhostTruth_pid;
      delete m_GhostTruth_status;
      delete m_GhostTruth_barcode;
      delete m_GhostTruth_isReco;
      delete m_GhostTruth_recoProb;
      delete m_GhostTruth_recoID;
      delete m_GhostTruth_recoIsSelected;
      delete m_GhostTruth_recoIsAssociated;
    }
  }

  if ( m_infoSwitch.m_constituentAll )
    delete m_constituent_m;
}


void JetContainer :: setTree ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::JetContainer::setTree()", "setting tree" );

  connectBranch<int>   ( tree, "ID",     &m_ID     );
  connectBranch<float> ( tree, "radius", &m_radius );

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    connectBranch<uint8_t>            ( tree, "isTruthMatched",   &m_isTruthMatched   );
    connectBranch<int>                ( tree, "truthMatchID",     &m_truthMatchID     );
    connectBranch<float>              ( tree, "truthMatchDR",     &m_truthMatchDR     );
    connectBranch<std::vector<int>>   ( tree, "truthNonmatchIDs", &m_truthNonmatchIDs );
    connectBranch<std::vector<float>> ( tree, "truthNonmatchDRs", &m_truthNonmatchDRs );
    connectBranch<uint8_t>            ( tree, "isDarkMatched",    &m_isDarkMatched    );
    connectBranch<int>                ( tree, "darkMatchID",      &m_darkMatchID      );
    connectBranch<float>              ( tree, "darkMatchDR",      &m_darkMatchDR      );
    connectBranch<std::vector<int>>   ( tree, "darkNonmatchIDs",  &m_darkNonmatchIDs  );
    connectBranch<std::vector<float>> ( tree, "darkNonmatchDRs",  &m_darkNonmatchDRs  );
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    connectBranch<std::vector<int>>       ( tree, "secVtx_ID",                                 &m_secVtx_ID                                 );
    connectBranch<std::vector<float>>     ( tree, "secVtx_x",                                  &m_secVtx_x                                  );
    connectBranch<std::vector<float>>     ( tree, "secVtx_y",                                  &m_secVtx_y                                  );
    connectBranch<std::vector<float>>     ( tree, "secVtx_z",                                  &m_secVtx_z                                  );
    connectBranch<std::vector<float>>     ( tree, "secVtx_r",                                  &m_secVtx_r                                  );
    connectBranch<std::vector<float>>     ( tree, "secVtx_pt",                                 &m_secVtx_pt                                 );
    connectBranch<std::vector<float>>     ( tree, "secVtx_eta",                                &m_secVtx_eta                                );
    connectBranch<std::vector<float>>     ( tree, "secVtx_phi",                                &m_secVtx_phi                                );
    connectBranch<std::vector<float>>     ( tree, "secVtx_mass",                               &m_secVtx_mass                               );
    connectBranch<std::vector<int>>       ( tree, "secVtx_ntrk",                               &m_secVtx_ntrk                               );
    connectBranch<std::vector<float>>     ( tree, "secVtx_dR",                                 &m_secVtx_dR                                 );
    if ( m_mc ) {
      connectBranch<std::vector<uint8_t>> ( tree, "secVtx_closestTruth_isDarkPionDecay",       &m_secVtx_closestTruth_isDarkPionDecay       );
      connectBranch<std::vector<int>>     ( tree, "secVtx_closestTruth_ID",                    &m_secVtx_closestTruth_ID                    );
      connectBranch<std::vector<int>>     ( tree, "secVtx_closestTruth_barcode",               &m_secVtx_closestTruth_barcode               );
      connectBranch<std::vector<float>>   ( tree, "secVtx_closestTruth_distance",              &m_secVtx_closestTruth_distance              );
      connectBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkTruth_isDarkPionDecay",       &m_secVtx_maxlinkTruth_isDarkPionDecay       );
      connectBranch<std::vector<int>>     ( tree, "secVtx_maxlinkTruth_ID",                    &m_secVtx_maxlinkTruth_ID                    );
      connectBranch<std::vector<int>>     ( tree, "secVtx_maxlinkTruth_barcode",               &m_secVtx_maxlinkTruth_barcode               );
      connectBranch<std::vector<float>>   ( tree, "secVtx_maxlinkTruth_score",                 &m_secVtx_maxlinkTruth_score                 );
      connectBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkParentTruth_isDarkPionDecay", &m_secVtx_maxlinkParentTruth_isDarkPionDecay );
      connectBranch<std::vector<int>>     ( tree, "secVtx_maxlinkParentTruth_ID",              &m_secVtx_maxlinkParentTruth_ID              );
      connectBranch<std::vector<int>>     ( tree, "secVtx_maxlinkParentTruth_barcode",         &m_secVtx_maxlinkParentTruth_barcode         );
      connectBranch<std::vector<float>>   ( tree, "secVtx_maxlinkParentTruth_score",           &m_secVtx_maxlinkParentTruth_score           );
      connectBranch<std::vector<uint8_t>> ( tree, "truthVtx_isDarkPionDecay",                  &m_truthVtx_isDarkPionDecay                  );
      connectBranch<std::vector<int>>     ( tree, "truthVtx_ID",                               &m_truthVtx_ID                               );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_x",                                &m_truthVtx_x                                );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_y",                                &m_truthVtx_y                                );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_z",                                &m_truthVtx_z                                );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_r",                                &m_truthVtx_r                                );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_eta",                              &m_truthVtx_eta                              );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_phi",                              &m_truthVtx_phi                              );
      connectBranch<std::vector<int>>     ( tree, "truthVtx_barcode",                          &m_truthVtx_barcode                          );
      connectBranch<std::vector<float>>   ( tree, "truthVtx_dR",                               &m_truthVtx_dR                               );
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    
    connectBranch<std::vector<int>>       ( tree, "trk_ID",              &m_trk_ID              );
    connectBranch<std::vector<float>>     ( tree, "trk_qOverP",          &m_trk_qOverP          );
    connectBranch<std::vector<float>>     ( tree, "trk_E",               &m_trk_E               );
    connectBranch<std::vector<float>>     ( tree, "trk_M",               &m_trk_M               );
    connectBranch<std::vector<float>>     ( tree, "trk_pt",              &m_trk_pt              );
    connectBranch<std::vector<float>>     ( tree, "trk_eta",             &m_trk_eta             );
    connectBranch<std::vector<float>>     ( tree, "trk_phi",             &m_trk_phi             );
    connectBranch<std::vector<float>>     ( tree, "trk_d0",              &m_trk_d0              );
    connectBranch<std::vector<float>>     ( tree, "trk_z0",              &m_trk_z0              );
    connectBranch<std::vector<float>>     ( tree, "trk_errd0",           &m_trk_errd0           );
    connectBranch<std::vector<float>>     ( tree, "trk_errz0",           &m_trk_errz0           );
    connectBranch<std::vector<float>>     ( tree, "trk_chi2",            &m_trk_chi2            );
    connectBranch<std::vector<float>>     ( tree, "trk_charge",          &m_trk_charge          );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_isSelected",      &m_trk_isSelected      );
    connectBranch<std::vector<uint8_t>>   ( tree, "trk_isAssociated",    &m_trk_isAssociated    );
    connectBranch<std::vector<float>>     ( tree, "trk_dR",              &m_trk_dR              );
    if ( m_mc ) {
      connectBranch<std::vector<uint8_t>> ( tree, "trk_isTruth",         &m_trk_isTruth         );
      connectBranch<std::vector<float>>   ( tree, "trk_truthProb",       &m_trk_truthProb       );
      connectBranch<std::vector<int>>     ( tree, "trk_truthID",         &m_trk_truthID         );
      connectBranch<std::vector<int>>     ( tree, "trk_truthBarcode",    &m_trk_truthBarcode    );
      connectBranch<std::vector<int>>     ( tree, "trk_truthPid",        &m_trk_truthPid        );
      connectBranch<std::vector<int>>     ( tree, "tp_ID",               &m_tp_ID               );
      connectBranch<std::vector<float>>   ( tree, "tp_pt",               &m_tp_pt               );
      connectBranch<std::vector<float>>   ( tree, "tp_eta",              &m_tp_eta              );
      connectBranch<std::vector<float>>   ( tree, "tp_phi",              &m_tp_phi              );
      connectBranch<std::vector<float>>   ( tree, "tp_E",                &m_tp_E                );
      connectBranch<std::vector<float>>   ( tree, "tp_M",                &m_tp_M                );
      connectBranch<std::vector<float>>   ( tree, "tp_charge",           &m_tp_charge           );
      connectBranch<std::vector<int>>     ( tree, "tp_pid",              &m_tp_pid              );
      connectBranch<std::vector<int>>     ( tree, "tp_status",           &m_tp_status           );
      connectBranch<std::vector<int>>     ( tree, "tp_barcode",          &m_tp_barcode          );
      connectBranch<std::vector<float>>   ( tree, "tp_dR",               &m_tp_dR               );
      connectBranch<std::vector<uint8_t>> ( tree, "tp_isReco",           &m_tp_isReco           );
      connectBranch<std::vector<float>>   ( tree, "tp_recoProb",         &m_tp_recoProb         );
      connectBranch<std::vector<int>>     ( tree, "tp_recoID",           &m_tp_recoID           );
      connectBranch<std::vector<uint8_t>> ( tree, "tp_recoIsSelected",   &m_tp_recoIsSelected   );
      connectBranch<std::vector<uint8_t>> ( tree, "tp_recoIsAssociated", &m_tp_recoIsAssociated );
    }
  }

  if ( m_infoSwitch.m_ghost ) {
    connectBranch<std::vector<int>>       ( tree, "GhostTrack_ID",               &m_GhostTrack_ID               );
    connectBranch<std::vector<float>>     ( tree, "GhostTrack_m",                &m_GhostTrack_m                );
    connectBranch<std::vector<float>>     ( tree, "GhostTrack_errd0",            &m_GhostTrack_errd0            );
    connectBranch<std::vector<float>>     ( tree, "GhostTrack_errz0",            &m_GhostTrack_errz0            );
    connectBranch<std::vector<float>>     ( tree, "GhostTrack_chi2",             &m_GhostTrack_chi2             );
    connectBranch<std::vector<float>>     ( tree, "GhostTrack_charge",           &m_GhostTrack_charge           );
    connectBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSelected",       &m_GhostTrack_isSelected       );
    connectBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isAssociated",     &m_GhostTrack_isAssociated     );
    if ( m_mc ) {
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTrack_isTruth",          &m_GhostTrack_isTruth          );
      connectBranch<std::vector<float>>   ( tree, "GhostTrack_truthProb",        &m_GhostTrack_truthProb        );
      connectBranch<std::vector<int>>     ( tree, "GhostTrack_truthID",          &m_GhostTrack_truthID          );
      connectBranch<std::vector<int>>     ( tree, "GhostTrack_truthBarcode",     &m_GhostTrack_truthBarcode     );
      connectBranch<std::vector<int>>     ( tree, "GhostTrack_truthPid",         &m_GhostTrack_truthPid         );
      connectBranch<int>                  ( tree, "GhostTruthCount",             &m_GhostTruthCount             );
      connectBranch<float>                ( tree, "GhostTruthPt",                &m_GhostTruthPt                );
      connectBranch<std::vector<int>>     ( tree, "GhostTruth_ID",               &m_GhostTruth_ID               );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_pt",               &m_GhostTruth_pt               );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_eta",              &m_GhostTruth_eta              );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_phi",              &m_GhostTruth_phi              );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_e",                &m_GhostTruth_e                );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_m",                &m_GhostTruth_m                );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_charge",           &m_GhostTruth_charge           );
      connectBranch<std::vector<int>>     ( tree, "GhostTruth_pid",              &m_GhostTruth_pid              );
      connectBranch<std::vector<int>>     ( tree, "GhostTruth_status",           &m_GhostTruth_status           );
      connectBranch<std::vector<int>>     ( tree, "GhostTruth_barcode",          &m_GhostTruth_barcode          );
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isReco",           &m_GhostTruth_isReco           );
      connectBranch<std::vector<float>>   ( tree, "GhostTruth_recoProb",         &m_GhostTruth_recoProb         );
      connectBranch<std::vector<int>>     ( tree, "GhostTruth_recoID",           &m_GhostTruth_recoID           );
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTruth_recoIsSelected",   &m_GhostTruth_recoIsSelected   );
      connectBranch<std::vector<uint8_t>> ( tree, "GhostTruth_recoIsAssociated", &m_GhostTruth_recoIsAssociated );
    }
  }
    
  if ( m_infoSwitch.m_constituentAll )
    connectBranch<std::vector<float>> ( tree, "constituent_m", &m_constituent_m );
}


void JetContainer :: setBranches ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::JetContainer::setBranches()", "setting branches" );

  setBranch<int>   ( tree, "ID", m_ID );
  setBranch<float> ( tree, "radius", m_radius );

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    setBranch<uint8_t>            ( tree, "isTruthMatched",   m_isTruthMatched   );
    setBranch<int>                ( tree, "truthMatchID",     m_truthMatchID     );
    setBranch<float>              ( tree, "truthMatchDR",     m_truthMatchDR     );
    setBranch<std::vector<int>>   ( tree, "truthNonmatchIDs", m_truthNonmatchIDs );
    setBranch<std::vector<float>> ( tree, "truthNonmatchDRs", m_truthNonmatchDRs );
    setBranch<uint8_t>            ( tree, "isDarkMatched",    m_isDarkMatched    );
    setBranch<int>                ( tree, "darkMatchID",      m_darkMatchID      );
    setBranch<float>              ( tree, "darkMatchDR",      m_darkMatchDR      );
    setBranch<std::vector<int>>   ( tree, "darkNonmatchIDs",  m_darkNonmatchIDs  );
    setBranch<std::vector<float>> ( tree, "darkNonmatchDRs",  m_darkNonmatchDRs  );
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    setBranch<std::vector<int>>       ( tree, "secVtx_ID",                                 m_secVtx_ID                                 );
    setBranch<std::vector<float>>     ( tree, "secVtx_x",                                  m_secVtx_x                                  );
    setBranch<std::vector<float>>     ( tree, "secVtx_y",                                  m_secVtx_y                                  );
    setBranch<std::vector<float>>     ( tree, "secVtx_z",                                  m_secVtx_z                                  );
    setBranch<std::vector<float>>     ( tree, "secVtx_r",                                  m_secVtx_r                                  );
    setBranch<std::vector<float>>     ( tree, "secVtx_pt",                                 m_secVtx_pt                                 );
    setBranch<std::vector<float>>     ( tree, "secVtx_eta",                                m_secVtx_eta                                );
    setBranch<std::vector<float>>     ( tree, "secVtx_phi",                                m_secVtx_phi                                );
    setBranch<std::vector<float>>     ( tree, "secVtx_mass",                               m_secVtx_mass                               );
    setBranch<std::vector<int>>       ( tree, "secVtx_ntrk",                               m_secVtx_ntrk                               );
    setBranch<std::vector<float>>     ( tree, "secVtx_dR",                                 m_secVtx_dR                                 );
    if ( m_mc ) {
      setBranch<std::vector<uint8_t>> ( tree, "secVtx_closestTruth_isDarkPionDecay",       m_secVtx_closestTruth_isDarkPionDecay       );
      setBranch<std::vector<int>>     ( tree, "secVtx_closestTruth_ID",                    m_secVtx_closestTruth_ID                    );
      setBranch<std::vector<int>>     ( tree, "secVtx_closestTruth_barcode",               m_secVtx_closestTruth_barcode               );
      setBranch<std::vector<float>>   ( tree, "secVtx_closestTruth_distance",              m_secVtx_closestTruth_distance              );
      setBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkTruth_isDarkPionDecay",       m_secVtx_maxlinkTruth_isDarkPionDecay       );
      setBranch<std::vector<int>>     ( tree, "secVtx_maxlinkTruth_ID",                    m_secVtx_maxlinkTruth_ID                    );
      setBranch<std::vector<int>>     ( tree, "secVtx_maxlinkTruth_barcode",               m_secVtx_maxlinkTruth_barcode               );
      setBranch<std::vector<float>>   ( tree, "secVtx_maxlinkTruth_score",                 m_secVtx_maxlinkTruth_score                 );
      setBranch<std::vector<uint8_t>> ( tree, "secVtx_maxlinkParentTruth_isDarkPionDecay", m_secVtx_maxlinkParentTruth_isDarkPionDecay );
      setBranch<std::vector<int>>     ( tree, "secVtx_maxlinkParentTruth_ID",              m_secVtx_maxlinkParentTruth_ID              );
      setBranch<std::vector<int>>     ( tree, "secVtx_maxlinkParentTruth_barcode",         m_secVtx_maxlinkParentTruth_barcode         );
      setBranch<std::vector<float>>   ( tree, "secVtx_maxlinkParentTruth_score",           m_secVtx_maxlinkParentTruth_score           );
      setBranch<std::vector<uint8_t>> ( tree, "truthVtx_isDarkPionDecay",                  m_truthVtx_isDarkPionDecay                  );
      setBranch<std::vector<int>>     ( tree, "truthVtx_ID",                               m_truthVtx_ID                               );
      setBranch<std::vector<float>>   ( tree, "truthVtx_x",                                m_truthVtx_x                                );
      setBranch<std::vector<float>>   ( tree, "truthVtx_y",                                m_truthVtx_y                                );
      setBranch<std::vector<float>>   ( tree, "truthVtx_z",                                m_truthVtx_z                                );
      setBranch<std::vector<float>>   ( tree, "truthVtx_r",                                m_truthVtx_r                                );
      setBranch<std::vector<float>>   ( tree, "truthVtx_eta",                              m_truthVtx_eta                              );
      setBranch<std::vector<float>>   ( tree, "truthVtx_phi",                              m_truthVtx_phi                              );
      setBranch<std::vector<int>>     ( tree, "truthVtx_barcode",                          m_truthVtx_barcode                          );
      setBranch<std::vector<float>>   ( tree, "truthVtx_dR",                               m_truthVtx_dR                               );
    }
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    setBranch<std::vector<int>>       ( tree, "trk_ID",              m_trk_ID              );
    setBranch<std::vector<float>>     ( tree, "trk_qOverP",          m_trk_qOverP          );
    setBranch<std::vector<float>>     ( tree, "trk_E",               m_trk_E               );
    setBranch<std::vector<float>>     ( tree, "trk_M",               m_trk_M               );
    setBranch<std::vector<float>>     ( tree, "trk_pt",              m_trk_pt              );
    setBranch<std::vector<float>>     ( tree, "trk_eta",             m_trk_eta             );
    setBranch<std::vector<float>>     ( tree, "trk_phi",             m_trk_phi             );
    setBranch<std::vector<float>>     ( tree, "trk_d0",              m_trk_d0              );
    setBranch<std::vector<float>>     ( tree, "trk_z0",              m_trk_z0              );
    setBranch<std::vector<float>>     ( tree, "trk_errd0",           m_trk_errd0           );
    setBranch<std::vector<float>>     ( tree, "trk_errz0",           m_trk_errz0           );
    setBranch<std::vector<float>>     ( tree, "trk_chi2",            m_trk_chi2            );
    setBranch<std::vector<float>>     ( tree, "trk_charge",          m_trk_charge          );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_isSelected",      m_trk_isSelected      );
    setBranch<std::vector<uint8_t>>   ( tree, "trk_isAssociated",    m_trk_isAssociated    );
    setBranch<std::vector<float>>     ( tree, "trk_dR",              m_trk_dR              );
    if ( m_mc ) {
      setBranch<std::vector<uint8_t>> ( tree, "trk_isTruth",         m_trk_isTruth         );
      setBranch<std::vector<float>>   ( tree, "trk_truthProb",       m_trk_truthProb       );
      setBranch<std::vector<int>>     ( tree, "trk_truthID",         m_trk_truthID         );
      setBranch<std::vector<int>>     ( tree, "trk_truthBarcode",    m_trk_truthBarcode    );
      setBranch<std::vector<int>>     ( tree, "trk_truthPid",        m_trk_truthPid        );
      setBranch<std::vector<int>>     ( tree, "tp_ID",               m_tp_ID               );
      setBranch<std::vector<float>>   ( tree, "tp_pt",               m_tp_pt               );
      setBranch<std::vector<float>>   ( tree, "tp_eta",              m_tp_eta              );
      setBranch<std::vector<float>>   ( tree, "tp_phi",              m_tp_phi              );
      setBranch<std::vector<float>>   ( tree, "tp_E",                m_tp_E                );
      setBranch<std::vector<float>>   ( tree, "tp_M",                m_tp_M                );
      setBranch<std::vector<float>>   ( tree, "tp_charge",           m_tp_charge           );
      setBranch<std::vector<int>>     ( tree, "tp_pid",              m_tp_pid              );
      setBranch<std::vector<int>>     ( tree, "tp_status",           m_tp_status           );
      setBranch<std::vector<int>>     ( tree, "tp_barcode",          m_tp_barcode          );
      setBranch<std::vector<float>>   ( tree, "tp_dR",               m_tp_dR               );
      setBranch<std::vector<uint8_t>> ( tree, "tp_isReco",           m_tp_isReco           );
      setBranch<std::vector<float>>   ( tree, "tp_recoProb",         m_tp_recoProb         );
      setBranch<std::vector<int>>     ( tree, "tp_recoID",           m_tp_recoID           );
      setBranch<std::vector<uint8_t>> ( tree, "tp_recoIsSelected",   m_tp_recoIsSelected   );
      setBranch<std::vector<uint8_t>> ( tree, "tp_recoIsAssociated", m_tp_recoIsAssociated );
    }
  }

  if ( m_infoSwitch.m_ghost ) {
    setBranch<std::vector<int>>       ( tree, "GhostTrack_ID",               m_GhostTrack_ID               );
    setBranch<std::vector<float>>     ( tree, "GhostTrack_m",                m_GhostTrack_m                );
    setBranch<std::vector<float>>     ( tree, "GhostTrack_errd0",            m_GhostTrack_errd0            );
    setBranch<std::vector<float>>     ( tree, "GhostTrack_errz0",            m_GhostTrack_errz0            );
    setBranch<std::vector<float>>     ( tree, "GhostTrack_chi2",             m_GhostTrack_chi2             );
    setBranch<std::vector<float>>     ( tree, "GhostTrack_charge",           m_GhostTrack_charge           );
    setBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isSelected",       m_GhostTrack_isSelected       );
    setBranch<std::vector<uint8_t>>   ( tree, "GhostTrack_isAssociated",     m_GhostTrack_isAssociated     );
    if ( m_mc ) {
      setBranch<std::vector<uint8_t>> ( tree, "GhostTrack_isTruth",          m_GhostTrack_isTruth          );
      setBranch<std::vector<float>>   ( tree, "GhostTrack_truthProb",        m_GhostTrack_truthProb        );
      setBranch<std::vector<int>>     ( tree, "GhostTrack_truthID",          m_GhostTrack_truthID          );
      setBranch<std::vector<int>>     ( tree, "GhostTrack_truthBarcode",     m_GhostTrack_truthBarcode     );
      setBranch<std::vector<int>>     ( tree, "GhostTrack_truthPid",         m_GhostTrack_truthPid         );
      setBranch<int>                  ( tree, "GhostTruthCount",             m_GhostTruthCount             );
      setBranch<float>                ( tree, "GhostTruthPt",                m_GhostTruthPt                );
      setBranch<std::vector<int>>     ( tree, "GhostTruth_ID",               m_GhostTruth_ID               );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_pt",               m_GhostTruth_pt               );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_eta",              m_GhostTruth_eta              );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_phi",              m_GhostTruth_phi              );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_e",                m_GhostTruth_e                );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_m",                m_GhostTruth_m                );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_charge",           m_GhostTruth_charge           );
      setBranch<std::vector<int>>     ( tree, "GhostTruth_pid",              m_GhostTruth_pid              );
      setBranch<std::vector<int>>     ( tree, "GhostTruth_status",           m_GhostTruth_status           );
      setBranch<std::vector<int>>     ( tree, "GhostTruth_barcode",          m_GhostTruth_barcode          );
      setBranch<std::vector<uint8_t>> ( tree, "GhostTruth_isReco",           m_GhostTruth_isReco           );
      setBranch<std::vector<float>>   ( tree, "GhostTruth_recoProb",         m_GhostTruth_recoProb         );
      setBranch<std::vector<int>>     ( tree, "GhostTruth_recoID",           m_GhostTruth_recoID           );
      setBranch<std::vector<uint8_t>> ( tree, "GhostTruth_recoIsSelected",   m_GhostTruth_recoIsSelected   );
      setBranch<std::vector<uint8_t>> ( tree, "GhostTruth_recoIsAssociated", m_GhostTruth_recoIsAssociated );
    }
  }

  if ( m_infoSwitch.m_constituentAll )
    setBranch<std::vector<float>> ( tree, "constituent_m", m_constituent_m );
}


void JetContainer :: clear ( )
{
  if ( m_debug ) Info( "EJs::JetContainer::clear()", "clearing branches" );

  m_ID     ->clear();
  m_radius ->clear();

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    m_isTruthMatched   ->clear();
    m_truthMatchID     ->clear();
    m_truthMatchDR     ->clear();
    m_truthNonmatchIDs ->clear();
    m_truthNonmatchDRs ->clear();
    m_isDarkMatched    ->clear();
    m_darkMatchID      ->clear();
    m_darkMatchDR      ->clear();
    m_darkNonmatchIDs  ->clear();
    m_darkNonmatchDRs  ->clear();
  }

  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    m_secVtx_ID                                   ->clear();
    m_secVtx_x                                    ->clear();
    m_secVtx_y                                    ->clear();
    m_secVtx_z                                    ->clear();
    m_secVtx_r                                    ->clear();
    m_secVtx_pt                                   ->clear();
    m_secVtx_eta                                  ->clear();
    m_secVtx_phi                                  ->clear();
    m_secVtx_mass                                 ->clear();
    m_secVtx_ntrk                                 ->clear();
    m_secVtx_dR                                   ->clear();
    if ( m_mc ) {
      m_secVtx_closestTruth_isDarkPionDecay       ->clear();
      m_secVtx_closestTruth_ID                    ->clear();
      m_secVtx_closestTruth_barcode               ->clear();
      m_secVtx_closestTruth_distance              ->clear();
      m_secVtx_maxlinkTruth_isDarkPionDecay       ->clear();
      m_secVtx_maxlinkTruth_ID                    ->clear();
      m_secVtx_maxlinkTruth_barcode               ->clear();
      m_secVtx_maxlinkTruth_score                 ->clear();
      m_secVtx_maxlinkParentTruth_isDarkPionDecay ->clear();
      m_secVtx_maxlinkParentTruth_ID              ->clear();
      m_secVtx_maxlinkParentTruth_barcode         ->clear();
      m_secVtx_maxlinkParentTruth_score           ->clear();
      m_truthVtx_isDarkPionDecay                  ->clear();
      m_truthVtx_ID                               ->clear();
      m_truthVtx_x                                ->clear();
      m_truthVtx_y                                ->clear();
      m_truthVtx_z                                ->clear();
      m_truthVtx_r                                ->clear();
      m_truthVtx_eta                              ->clear();
      m_truthVtx_phi                              ->clear();
      m_truthVtx_barcode                          ->clear();
      m_truthVtx_dR                               ->clear();
    }
  }
  
  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {
    m_trk_ID              ->clear();
    m_trk_qOverP          ->clear();
    m_trk_E               ->clear();
    m_trk_M               ->clear();
    m_trk_pt              ->clear();
    m_trk_eta             ->clear();
    m_trk_phi             ->clear();
    m_trk_d0              ->clear();
    m_trk_z0              ->clear();
    m_trk_errd0           ->clear();
    m_trk_errz0           ->clear();
    m_trk_chi2            ->clear();
    m_trk_charge          ->clear();
    m_trk_isSelected      ->clear();
    m_trk_isAssociated    ->clear();
    m_trk_dR              ->clear();
    if ( m_mc ) {
      m_trk_isTruth         ->clear();
      m_trk_truthProb       ->clear();
      m_trk_truthID         ->clear();
      m_trk_truthBarcode    ->clear();
      m_trk_truthPid        ->clear();
      m_tp_ID               ->clear();
      m_tp_pt               ->clear();
      m_tp_eta              ->clear();
      m_tp_phi              ->clear();
      m_tp_E                ->clear();
      m_tp_M                ->clear();
      m_tp_charge           ->clear();
      m_tp_pid              ->clear();
      m_tp_status           ->clear();
      m_tp_barcode          ->clear();
      m_tp_dR               ->clear();
      m_tp_isReco           ->clear();
      m_tp_recoProb         ->clear();
      m_tp_recoID           ->clear();
      m_tp_recoIsSelected   ->clear();
      m_tp_recoIsAssociated ->clear();
    }
  }

  if ( m_infoSwitch.m_ghost ) {
    m_GhostTrack_ID               ->clear();
    m_GhostTrack_m                ->clear();
    m_GhostTrack_errd0            ->clear();
    m_GhostTrack_errz0            ->clear();
    m_GhostTrack_chi2             ->clear();
    m_GhostTrack_charge           ->clear();
    m_GhostTrack_isSelected       ->clear();
    m_GhostTrack_isAssociated     ->clear();
    if ( m_mc ) {
      m_GhostTrack_isTruth          ->clear();
      m_GhostTrack_truthProb        ->clear();
      m_GhostTrack_truthID          ->clear();
      m_GhostTrack_truthBarcode     ->clear();
      m_GhostTrack_truthPid         ->clear();
      m_GhostTruthCount             ->clear();
      m_GhostTruthPt                ->clear();
      m_GhostTruth_ID               ->clear();
      m_GhostTruth_pt               ->clear();
      m_GhostTruth_eta              ->clear();
      m_GhostTruth_phi              ->clear();
      m_GhostTruth_e                ->clear();
      m_GhostTruth_m                ->clear();
      m_GhostTruth_charge           ->clear();
      m_GhostTruth_pid              ->clear();
      m_GhostTruth_status           ->clear();
      m_GhostTruth_barcode          ->clear();
      m_GhostTruth_isReco           ->clear();
      m_GhostTruth_recoProb         ->clear();
      m_GhostTruth_recoID           ->clear();
      m_GhostTruth_recoIsSelected   ->clear();
      m_GhostTruth_recoIsAssociated ->clear();
    }
  }

  if ( m_infoSwitch.m_constituentAll )
    m_constituent_m ->clear();
}


void JetContainer :: FillJet ( const xAOD::Jet* jet )
{
  if ( m_debug ) Info( "EJs::JetContainer::FillJet()", "filling branches" );

  m_ID     ->push_back( AUXDYN( jet, int, "ID" ) );
  m_radius ->push_back( jet->getSizeParameter()  );

  if ( ( m_infoSwitch.m_match || m_infoSwitch.m_truthJets ) && m_mc ) {
    m_isTruthMatched   ->push_back( AUXDYN(    jet, char,   "hasTruthJetMatch"   ) );
    m_truthMatchID     ->push_back( AUXDYN(    jet, int,    "truthJetMatchID"    ) );
    m_truthMatchDR     ->push_back( AUXDYN(    jet, double, "truthJetMatchDR"    ) );
    m_truthNonmatchIDs ->push_back( AUXDYNVEC( jet, int,    "truthJetNoMatchIDs" ) );
    m_truthNonmatchDRs ->push_back( AUXDYNVEC( jet, float,  "truthJetNoMatchDRs" ) );
    m_isDarkMatched    ->push_back( AUXDYN(    jet, char,   "hasDarkJetMatch"    ) );
    m_darkMatchID      ->push_back( AUXDYN(    jet, int,    "darkJetMatchID"     ) );
    m_darkMatchDR      ->push_back( AUXDYN(    jet, double, "darkJetMatchDR"     ) );
    m_darkNonmatchIDs  ->push_back( AUXDYNVEC( jet, int,    "darkJetNoMatchIDs"  ) );
    m_darkNonmatchDRs  ->push_back( AUXDYNVEC( jet, float,  "darkJetNoMatchDRs"  ) );
  }

  
  if ( m_infoSwitch.m_match || m_infoSwitch.m_vertices ) {
    std::vector<int>     matchDV_ID;
    std::vector<float>   matchDV_x;
    std::vector<float>   matchDV_y;
    std::vector<float>   matchDV_z;
    std::vector<float>   matchDV_r;
    std::vector<float>   matchDV_pt;
    std::vector<float>   matchDV_eta;
    std::vector<float>   matchDV_phi;
    std::vector<float>   matchDV_mass;
    std::vector<int>     matchDV_ntrk;
    std::vector<uint8_t> matchDV_closeTV_isPid;
    std::vector<int>     matchDV_closeTV_ID;
    std::vector<int>     matchDV_closeTV_barcode;
    std::vector<float>   matchDV_closeTV_dist;
    std::vector<uint8_t> matchDV_maxTV_isPid;
    std::vector<int>     matchDV_maxTV_ID;
    std::vector<int>     matchDV_maxTV_barcode;
    std::vector<float>   matchDV_maxTV_score;
    std::vector<uint8_t> matchDV_maxPTV_isPid;
    std::vector<int>     matchDV_maxPTV_ID;
    std::vector<int>     matchDV_maxPTV_barcode;
    std::vector<float>   matchDV_maxPTV_score;
    std::vector<uint8_t> matchTV_isPid;
    std::vector<int>     matchTV_ID;
    std::vector<float>   matchTV_x;
    std::vector<float>   matchTV_y;
    std::vector<float>   matchTV_z;
    std::vector<float>   matchTV_r;
    std::vector<float>   matchTV_eta;
    std::vector<float>   matchTV_phi;
    std::vector<int>     matchTV_barcode;
   
    // access matched secondary vertex links
    static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> matchDVAccess("matchedSecondaryVertexLinks");
    if ( matchDVAccess.isAvailable( *jet ) ) {
      const EJsHelper::VertexLinkVector_t& matchDVLinks = matchDVAccess( *jet );
    
      // loop over matched secondary vertex links
      for ( const auto& dvlink : matchDVLinks ) {
	if ( !dvlink.isValid() ) continue;

	// get vertex pt, eta, phi, mass from four-momentum; get filtered tracks
	TLorentzVector dvP4;
	std::vector<const xAOD::TrackParticle*> filteredTracks;
	EJsHelper::getFilteredTracks( (*dvlink), filteredTracks );
	// grab 4-mom from decorator, if available
	if ( (*dvlink)->isAvailable<TLorentzVector>("sumP4") )
	  dvP4 = (*dvlink)->auxdataConst<TLorentzVector>("sumP4");
	// otherwise, calculate from filtered tracks
	else	
	  dvP4 = VsiBonsai::sumP4( filteredTracks );
      
	matchDV_ID   .push_back( AUXDYN( (*dvlink), int, "ID" ) );
	matchDV_x    .push_back( (*dvlink)->x()                 );
	matchDV_y    .push_back( (*dvlink)->y()                 );
	matchDV_z    .push_back( (*dvlink)->z()                 );
	matchDV_r    .push_back( (*dvlink)->position().perp()   );
	matchDV_pt   .push_back( dvP4.Pt() / m_units            );
	matchDV_eta  .push_back( dvP4.Eta()                     );
	matchDV_phi  .push_back( dvP4.Phi()                     );
	matchDV_mass .push_back( dvP4.M()  / m_units            );
	matchDV_ntrk .push_back( filteredTracks.size()          );
      
	// get closest TV link
	static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLink_t> closeTVAccess("closestTruthVertexLink");
	if ( closeTVAccess.isAvailable( **dvlink ) ) {
	  try {
	    const EJsHelper::TruthVertexLink_t& closeTVLink = closeTVAccess( **dvlink );
	    matchDV_closeTV_isPid   .push_back( EJsHelper::selectDarkPion( (*closeTVLink) ) );
	    matchDV_closeTV_ID      .push_back( AUXDYN( (*closeTVLink), int, "ID" )         );
	    matchDV_closeTV_barcode .push_back( (*closeTVLink)->barcode()                   );
	  } catch(...) {}
	}
	matchDV_closeTV_dist .push_back( AUXDYN( (*dvlink), double, "closestTruthVertex_dist" ) );

	// get max-linked TV link
	static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLink_t> maxTVAccess("maxlinkedTruthVertexLink");
	if ( maxTVAccess.isAvailable( **dvlink ) ) {
	  try {
	    const EJsHelper::TruthVertexLink_t& maxTVLink = maxTVAccess( **dvlink );
	    matchDV_maxTV_isPid   .push_back( EJsHelper::selectDarkPion( (*maxTVLink) ) );
	    matchDV_maxTV_ID      .push_back( AUXDYN( (*maxTVLink), int, "ID" )         );
	    matchDV_maxTV_barcode .push_back( (*maxTVLink)->barcode()                   );
	  } catch(...) {}
	}
	matchDV_maxTV_score .push_back( AUXDYN( (*dvlink), double, "maxlinkedTruthVertex_score" ) );

	// get max-linked PTV link
	static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLink_t> maxPTVAccess("maxlinkedParentTruthVertexLink");
	if ( maxPTVAccess.isAvailable( **dvlink ) ) {
	  try {
	    const EJsHelper::TruthVertexLink_t& maxPTVLink = maxPTVAccess( **dvlink );
	    matchDV_maxPTV_isPid   .push_back( EJsHelper::selectDarkPion( (*maxPTVLink ) ) );
	    matchDV_maxPTV_ID      .push_back( AUXDYN( (*maxPTVLink), int, "ID" )          );
	    matchDV_maxPTV_barcode .push_back( (*maxPTVLink)->barcode()                    );
	  } catch(...) {}
	}
	matchDV_maxPTV_score .push_back( AUXDYN( (*dvlink), double, "maxlinkedParentTruthVertex_score" ) );
      
      } // end loop over matched DV links
    
    } // end matched secondary vertex link access

    // access matched truth vertex links
    static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLinkVector_t> matchTVAccess("matchedTruthVertexLinks");
    if ( matchTVAccess.isAvailable( *jet ) ) {
      const EJsHelper::TruthVertexLinkVector_t& matchTVLinks = matchTVAccess( *jet );
      // loop over matched truth vertex links
      for ( const auto& tvlink : matchTVLinks ) {
	if ( !tvlink.isValid() ) continue;
	matchTV_isPid   .push_back( EJsHelper::selectDarkPion( (*tvlink) ) );
	matchTV_ID      .push_back( AUXDYN( (*tvlink), int, "ID" )         );
	matchTV_x       .push_back( (*tvlink)->x()                         );
	matchTV_y       .push_back( (*tvlink)->y()                         );
	matchTV_z       .push_back( (*tvlink)->z()                         );
	matchTV_r       .push_back( (*tvlink)->perp()                      );
	matchTV_eta     .push_back( (*tvlink)->eta()                       );
	matchTV_phi     .push_back( (*tvlink)->phi()                       );
	matchTV_barcode .push_back( (*tvlink)->barcode()                   );
      }
    }

    m_secVtx_ID                                   ->push_back( matchDV_ID                                           );
    m_secVtx_x                                    ->push_back( matchDV_x                                            );
    m_secVtx_y                                    ->push_back( matchDV_y                                            );
    m_secVtx_z                                    ->push_back( matchDV_z                                            );
    m_secVtx_r                                    ->push_back( matchDV_r                                            );
    m_secVtx_pt                                   ->push_back( matchDV_pt                                           );
    m_secVtx_eta                                  ->push_back( matchDV_eta                                          );
    m_secVtx_phi                                  ->push_back( matchDV_phi                                          );
    m_secVtx_mass                                 ->push_back( matchDV_mass                                         );
    m_secVtx_ntrk                                 ->push_back( matchDV_ntrk                                         );
    m_secVtx_dR                                   ->push_back( AUXDYNVEC( jet, float, "matchedSecondaryVertex_dR" ) );
    if ( m_mc ) {
      m_secVtx_closestTruth_isDarkPionDecay       ->push_back( matchDV_closeTV_isPid                                );
      m_secVtx_closestTruth_ID                    ->push_back( matchDV_closeTV_ID                                   );
      m_secVtx_closestTruth_barcode               ->push_back( matchDV_closeTV_barcode                              );
      m_secVtx_closestTruth_distance              ->push_back( matchDV_closeTV_dist                                 );
      m_secVtx_maxlinkTruth_isDarkPionDecay       ->push_back( matchDV_maxTV_isPid                                  );
      m_secVtx_maxlinkTruth_ID                    ->push_back( matchDV_maxTV_ID                                     );
      m_secVtx_maxlinkTruth_barcode               ->push_back( matchDV_maxTV_barcode                                );
      m_secVtx_maxlinkTruth_score                 ->push_back( matchDV_maxTV_score                                  );
      m_secVtx_maxlinkParentTruth_isDarkPionDecay ->push_back( matchDV_maxPTV_isPid                                 );
      m_secVtx_maxlinkParentTruth_ID              ->push_back( matchDV_maxPTV_ID                                    );
      m_secVtx_maxlinkParentTruth_barcode         ->push_back( matchDV_maxPTV_barcode                               );
      m_secVtx_maxlinkParentTruth_score           ->push_back( matchDV_maxPTV_score                                 );
      m_truthVtx_isDarkPionDecay                  ->push_back( matchTV_isPid                                        );
      m_truthVtx_ID                               ->push_back( matchTV_ID                                           );
      m_truthVtx_x                                ->push_back( matchTV_x                                            );
      m_truthVtx_y                                ->push_back( matchTV_y                                            );
      m_truthVtx_z                                ->push_back( matchTV_z                                            );
      m_truthVtx_r                                ->push_back( matchTV_r                                            );
      m_truthVtx_eta                              ->push_back( matchTV_eta                                          );
      m_truthVtx_phi                              ->push_back( matchTV_phi                                          );
      m_truthVtx_barcode                          ->push_back( matchTV_barcode                                      );
      m_truthVtx_dR                               ->push_back( AUXDYNVEC( jet, float, "matchedTruthVertex_dR"     ) );
    }
  }

  
  if ( m_infoSwitch.m_match || m_infoSwitch.m_trackParts ) {   
    std::vector<int>     trk_ID;
    std::vector<float>   trk_qOverP;
    std::vector<float>   trk_E;
    std::vector<float>   trk_M;
    std::vector<float>   trk_pt;
    std::vector<float>   trk_eta;
    std::vector<float>   trk_phi;
    std::vector<float>   trk_d0;
    std::vector<float>   trk_z0;
    std::vector<float>   trk_errd0;
    std::vector<float>   trk_errz0;
    std::vector<float>   trk_chi2;
    std::vector<float>   trk_charge;
    std::vector<uint8_t> trk_isSelected;
    std::vector<uint8_t> trk_isAssociated;
    std::vector<uint8_t> trk_isTruth;
    std::vector<float>   trk_truthProb;
    std::vector<int>     trk_truthID;
    std::vector<int>     trk_truthBarcode;
    std::vector<int>     trk_truthPid;
    std::vector<int>     tp_ID;
    std::vector<float>   tp_pt;
    std::vector<float>   tp_eta;
    std::vector<float>   tp_phi;
    std::vector<float>   tp_E;
    std::vector<float>   tp_M;
    std::vector<float>   tp_charge;
    std::vector<int>     tp_pid;
    std::vector<int>     tp_status;
    std::vector<int>     tp_barcode;
    std::vector<uint8_t> tp_isReco;
    std::vector<float>   tp_recoProb;
    std::vector<int>     tp_recoID;
    std::vector<uint8_t> tp_recoIsSelected;
    std::vector<uint8_t> tp_recoIsAssociated;

    // access matched track links
    static SG::AuxElement::ConstAccessor<EJsHelper::TrackLinkVector_t> trkAccess("matchedTrackLinks");
    if ( trkAccess.isAvailable( *jet ) ) {
      const EJsHelper::TrackLinkVector_t& trkLinks = trkAccess( *jet );
    
      // loop over matched track links
      for ( const auto& trklink : trkLinks ) {
	if ( !trklink.isValid() ) continue;
	trk_ID .push_back( AUXDYN( (*trklink), int, "ID" )                                                   );
	trk_qOverP .push_back( (*trklink)->qOverP() * m_units                                                );
	trk_E      .push_back( (*trklink)->e()      / m_units                                                );
	trk_M      .push_back( (*trklink)->m()      / m_units                                                );
	trk_pt     .push_back( (*trklink)->pt()     / m_units                                                );
	trk_eta    .push_back( (*trklink)->eta()                                                             );
	trk_phi    .push_back( (*trklink)->phi()                                                             );
	trk_d0     .push_back( (*trklink)->d0()                                                              );
	trk_z0     .push_back( (*trklink)->z0()                                                              ); // xAH saves z0 wrt PV ...
	trk_errd0  .push_back( (*trklink)->definingParametersCovMatrix()(0,0)                                );
	trk_errz0  .push_back( (*trklink)->definingParametersCovMatrix()(1,1)                                );
	trk_chi2   .push_back( (*trklink)->chiSquared() / (*trklink)->numberDoF() / AlgConsts::infinitesimal );
	trk_charge .push_back( (*trklink)->charge()                                                          );
	if ( (*trklink)->isAvailable<char>("is_selected")   )
	  trk_isSelected   .push_back( (*trklink)->auxdataConst<char>("is_selected")   );
	if ( (*trklink)->isAvailable<char>("is_associated") )
	  trk_isAssociated .push_back( (*trklink)->auxdataConst<char>("is_associated") );
      
	// get linked truth particle
	bool trackHasTruthLink = false;
	static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLink_t> truthAccess("truthParticleLink");
	if ( truthAccess.isAvailable( **trklink ) ) {
	  try {
	    const EJsHelper::TruthParticleLink_t& truthLink = truthAccess( **trklink );
	    if ( (*truthLink) ) trackHasTruthLink = true;
	    trk_truthID      .push_back( AUXDYN( (*truthLink), int, "ID" ) );
	    trk_truthBarcode .push_back( (*truthLink)->barcode()           );
	    trk_truthPid     .push_back( (*truthLink)->pdgId()             );
	  } catch(...) {}
	}
	trk_isTruth   .push_back( trackHasTruthLink                                        );
	//trk_truthProb .push_back( (*trklink)->auxdataConst<float>("truthMatchProbability") );
      
      } // end loop over matched track links
    
    } // end matched track link access

    // access matched truth particle links
    static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLinkVector_t> tpAccess("matchedTruthParticleLinks");
    if ( tpAccess.isAvailable( *jet ) ) {
      const EJsHelper::TruthParticleLinkVector_t& tpLinks = tpAccess( *jet );
    
      // loop over matched truth particle links
      for ( const auto& tplink : tpLinks ) {
	if ( !tplink.isValid() ) continue;
	tp_ID      .push_back( AUXDYN( (*tplink), int, "ID" ) );
	tp_pt      .push_back( (*tplink)->pt() / m_units      );
	tp_eta     .push_back( (*tplink)->eta()               );
	tp_phi     .push_back( (*tplink)->phi()               );
	tp_E       .push_back( (*tplink)->e()  / m_units      );
	tp_M       .push_back( (*tplink)->m()  / m_units      );
	tp_charge  .push_back( (*tplink)->charge()            );
	tp_pid     .push_back( (*tplink)->pdgId()             );
	tp_status  .push_back( (*tplink)->status()            );
	tp_barcode .push_back( (*tplink)->barcode()           );

	// get linked reco particle (track)
	static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> recoAccess("trackLink");
	if ( recoAccess.isAvailable( **tplink ) ) {
	  try {
	    const EJsHelper::TrackLink_t& recoLink = recoAccess( **tplink );
	    tp_recoID .push_back( AUXDYN( (*recoLink), int, "ID" ) );
	    if ( (*recoLink)->isAvailable<char>("is_selected")   )
	      tp_recoIsSelected   .push_back( (*recoLink)->auxdataConst<char>("is_selected")   );
	    if ( (*recoLink)->isAvailable<char>("is_associated") )
	      tp_recoIsAssociated .push_back( (*recoLink)->auxdataConst<char>("is_associated") );
	  } catch(...) {}
	}
	tp_isReco   .push_back( AUXDYN( (*tplink), char,   "isTrackMatch"          ) );
	tp_recoProb .push_back( AUXDYN( (*tplink), double, "trackMatchProbability" ) );
  
      } // end loop over matched truth links
    
    } // end matched truth link access

    m_trk_ID                ->push_back( trk_ID                                             );
    m_trk_qOverP            ->push_back( trk_qOverP                                         );
    m_trk_E                 ->push_back( trk_E                                              );
    m_trk_M                 ->push_back( trk_M                                              );
    m_trk_pt                ->push_back( trk_pt                                             );
    m_trk_eta               ->push_back( trk_eta                                            );
    m_trk_phi               ->push_back( trk_phi                                            );
    m_trk_d0                ->push_back( trk_d0                                             );
    m_trk_z0                ->push_back( trk_z0                                             );
    m_trk_errd0             ->push_back( trk_errd0                                          );
    m_trk_errz0             ->push_back( trk_errz0                                          );
    m_trk_chi2              ->push_back( trk_chi2                                           );
    m_trk_charge            ->push_back( trk_charge                                         );
    m_trk_isSelected        ->push_back( trk_isSelected                                     );
    m_trk_isAssociated      ->push_back( trk_isAssociated                                   );
    m_trk_dR                ->push_back( AUXDYNVEC( jet, float, "matchedTrack_dR"         ) );
    if ( m_mc ) {
      m_trk_isTruth           ->push_back( trk_isTruth                                        );
      m_trk_truthProb       ->push_back( trk_truthProb                                      );
      m_trk_truthID         ->push_back( trk_truthID                                        );
      m_trk_truthBarcode    ->push_back( trk_truthBarcode                                   );
      m_trk_truthPid        ->push_back( trk_truthPid                                       );
      m_tp_ID               ->push_back( tp_ID                                              );
      m_tp_pt               ->push_back( tp_pt                                              );
      m_tp_eta              ->push_back( tp_eta                                             );
      m_tp_phi              ->push_back( tp_phi                                             );
      m_tp_E                ->push_back( tp_E                                               );
      m_tp_M                ->push_back( tp_M                                               );
      m_tp_charge           ->push_back( tp_charge                                          );
      m_tp_pid              ->push_back( tp_pid                                             );
      m_tp_status           ->push_back( tp_status                                          );
      m_tp_barcode          ->push_back( tp_barcode                                         );
      m_tp_dR               ->push_back( AUXDYNVEC( jet, float, "matchedTruthParticle_dR" ) );
      m_tp_isReco           ->push_back( tp_isReco                                          );
      m_tp_recoProb         ->push_back( tp_recoProb                                        );
      m_tp_recoID           ->push_back( tp_recoID                                          );
      m_tp_recoIsSelected   ->push_back( tp_recoIsSelected                                  );
      m_tp_recoIsAssociated ->push_back( tp_recoIsAssociated                                );
    }
  }


  if ( m_infoSwitch.m_ghost ) {
    std::vector<int>     ghostTrack_ID;
    std::vector<float>   ghostTrack_m;
    std::vector<float>   ghostTrack_errd0;
    std::vector<float>   ghostTrack_errz0;
    std::vector<float>   ghostTrack_chi2;
    std::vector<float>   ghostTrack_charge;
    std::vector<uint8_t> ghostTrack_isSelected;
    std::vector<uint8_t> ghostTrack_isAssociated;
    std::vector<uint8_t> ghostTrack_isTruth;
    std::vector<float>   ghostTrack_truthProb;
    std::vector<int>     ghostTrack_truthID;
    std::vector<int>     ghostTrack_truthBarcode;
    std::vector<int>     ghostTrack_truthPid;
    std::vector<int>     ghostTruth_ID;
    std::vector<float>   ghostTruth_pt;
    std::vector<float>   ghostTruth_eta;
    std::vector<float>   ghostTruth_phi;
    std::vector<float>   ghostTruth_e;
    std::vector<float>   ghostTruth_m;
    std::vector<float>   ghostTruth_charge;
    std::vector<int>     ghostTruth_pid;
    std::vector<int>     ghostTruth_status;
    std::vector<int>     ghostTruth_barcode;
    std::vector<uint8_t> ghostTruth_isReco;
    std::vector<float>   ghostTruth_recoProb;
    std::vector<int>     ghostTruth_recoID;
    std::vector<uint8_t> ghostTruth_recoIsSelected;
    std::vector<uint8_t> ghostTruth_recoIsAssociated;
    
    // access ghost tracks
    static SG::AuxElement::ConstAccessor<std::vector<ElementLink<DataVector<xAOD::IParticle> > > > ghostTrackAccess("GhostTrack");
    if ( ghostTrackAccess.isAvailable( *jet ) ) {
      std::vector<ElementLink<DataVector<xAOD::IParticle> > > ghostTrackLinks = ghostTrackAccess( *jet );
      for ( const auto& ghosttrklink : ghostTrackLinks ) {
	if ( !ghosttrklink.isValid() ) continue;
	const xAOD::TrackParticle* ghosttrack = dynamic_cast<const xAOD::TrackParticle*>( *ghosttrklink );
	ghostTrack_ID      .push_back( AUXDYN( ghosttrack, int, "ID" )                                               );
	ghostTrack_m       .push_back( ghosttrack->m()  / m_units                                                    );
	ghostTrack_errd0   .push_back( ghosttrack->definingParametersCovMatrix()(0,0)                                );
	ghostTrack_errz0   .push_back( ghosttrack->definingParametersCovMatrix()(1,1)                                );
	ghostTrack_chi2    .push_back( ghosttrack->chiSquared() / ghosttrack->numberDoF() / AlgConsts::infinitesimal );
	ghostTrack_charge  .push_back( ghosttrack->charge()                                                          );
	if ( ghosttrack->isAvailable<char>("is_selected")   )
	  ghostTrack_isSelected   .push_back( ghosttrack->auxdataConst<char>("is_selected")   );
	if ( ghosttrack->isAvailable<char>("is_associated") )
	  ghostTrack_isAssociated .push_back( ghosttrack->auxdataConst<char>("is_associated") );
	
	// get linked truth particle
	bool ghosttrackHasTruthLink = false;
	static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLink_t> ghosttruthAccess("truthParticleLink");
	if ( ghosttruthAccess.isAvailable( *ghosttrack ) ) {
	  try {
	    const EJsHelper::TruthParticleLink_t& ghosttruthLink = ghosttruthAccess( *ghosttrack );
	    if ( (*ghosttruthLink) ) ghosttrackHasTruthLink = true;
	    ghostTrack_truthID      .push_back( AUXDYN( (*ghosttruthLink), int, "ID" ) );
	    ghostTrack_truthBarcode .push_back( (*ghosttruthLink)->barcode()           );
	    ghostTrack_truthPid     .push_back( (*ghosttruthLink)->pdgId()             ); 
	  } catch(...) {}
	}
	ghostTrack_isTruth   .push_back( ghosttrackHasTruthLink                                   );
	//ghostTrack_truthProb .push_back( ghosttrack->auxdataConst<float>("truthMatchProbability") );
      }
    }

    // access ghost truth particles
    static SG::AuxElement::ConstAccessor<std::vector<ElementLink<DataVector<xAOD::IParticle> > > > ghostTruthAccess("GhostTruth");
    if ( ghostTruthAccess.isAvailable( *jet ) ) {
      std::vector<ElementLink<DataVector<xAOD::IParticle> > > ghostTruthLinks = ghostTruthAccess( *jet );
      for ( const auto& ghostlink : ghostTruthLinks ) {
	if ( !ghostlink.isValid() ) continue;
	const xAOD::TruthParticle* ghosttruth = dynamic_cast<const xAOD::TruthParticle*>( *ghostlink );
	ghostTruth_ID      .push_back( AUXDYN( ghosttruth, int, "ID" ) );
	ghostTruth_pt      .push_back( ghosttruth->pt() / m_units      );
	ghostTruth_eta     .push_back( ghosttruth->eta()               );
	ghostTruth_phi     .push_back( ghosttruth->phi()               );
	ghostTruth_e       .push_back( ghosttruth->e()  / m_units      );
	ghostTruth_m       .push_back( ghosttruth->m()  / m_units      );
	ghostTruth_charge  .push_back( ghosttruth->charge()            );
	ghostTruth_pid     .push_back( ghosttruth->pdgId()             );
	ghostTruth_status  .push_back( ghosttruth->status()            );
	ghostTruth_barcode .push_back( ghosttruth->barcode()           );
	
	// get linked reco particle (track)
	static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> ghostrecoAccess("trackLink");
	if ( ghostrecoAccess.isAvailable( *ghosttruth ) ) {
	  try {
	    const EJsHelper::TrackLink_t& ghostrecoLink = ghostrecoAccess( *ghosttruth );
	    ghostTruth_recoID .push_back( AUXDYN( (*ghostrecoLink), int, "ID" ) );
	    if ( (*ghostrecoLink)->isAvailable<char>("is_selected")   )
	      ghostTruth_recoIsSelected   .push_back( (*ghostrecoLink)->auxdataConst<char>("is_selected")   );
	    if ( (*ghostrecoLink)->isAvailable<char>("is_associated") )
	      ghostTruth_recoIsAssociated .push_back( (*ghostrecoLink)->auxdataConst<char>("is_associated") );
	  } catch(...) {}
	}
	ghostTruth_isReco   .push_back( AUXDYN( ghosttruth, char,   "isTrackMatch"          ) );
	ghostTruth_recoProb .push_back( AUXDYN( ghosttruth, double, "trackMatchProbability" ) );
      }
    }
    
    m_GhostTrack_ID               ->push_back( ghostTrack_ID                                     );
    m_GhostTrack_m                ->push_back( ghostTrack_m                                      );
    m_GhostTrack_errd0            ->push_back( ghostTrack_errd0                                  );
    m_GhostTrack_errz0            ->push_back( ghostTrack_errz0                                  );
    m_GhostTrack_chi2             ->push_back( ghostTrack_chi2                                   );
    m_GhostTrack_charge           ->push_back( ghostTrack_charge                                 );
    m_GhostTrack_isSelected       ->push_back( ghostTrack_isSelected                             );
    m_GhostTrack_isAssociated     ->push_back( ghostTrack_isAssociated                           );
    if ( m_mc ) {
      m_GhostTrack_isTruth          ->push_back( ghostTrack_isTruth                                );
      m_GhostTrack_truthProb        ->push_back( ghostTrack_truthProb                              );
      m_GhostTrack_truthID          ->push_back( ghostTrack_truthID                                );
      m_GhostTrack_truthBarcode     ->push_back( ghostTrack_truthBarcode                           );
      m_GhostTrack_truthPid         ->push_back( ghostTrack_truthPid                               );
      m_GhostTruthCount             ->push_back( AUXDYN( jet, int,   "GhostTruthCount" )           );
      m_GhostTruthPt                ->push_back( AUXDYN( jet, float, "GhostTruthPt"    ) / m_units );
      m_GhostTruth_ID               ->push_back( ghostTruth_ID                                     );
      m_GhostTruth_pt               ->push_back( ghostTruth_pt                                     );
      m_GhostTruth_eta              ->push_back( ghostTruth_eta                                    );
      m_GhostTruth_phi              ->push_back( ghostTruth_phi                                    );
      m_GhostTruth_e                ->push_back( ghostTruth_e                                      );
      m_GhostTruth_m                ->push_back( ghostTruth_m                                      );
      m_GhostTruth_charge           ->push_back( ghostTruth_charge                                 );
      m_GhostTruth_pid              ->push_back( ghostTruth_pid                                    );
      m_GhostTruth_status           ->push_back( ghostTruth_status                                 );
      m_GhostTruth_barcode          ->push_back( ghostTruth_barcode                                );
      m_GhostTruth_isReco           ->push_back( ghostTruth_isReco                                 );
      m_GhostTruth_recoProb         ->push_back( ghostTruth_recoProb                               );
      m_GhostTruth_recoID           ->push_back( ghostTruth_recoID                                 );
      m_GhostTruth_recoIsSelected   ->push_back( ghostTruth_recoIsSelected                         );
      m_GhostTruth_recoIsAssociated ->push_back( ghostTruth_recoIsAssociated                       );
    }
  }
  

  if ( m_infoSwitch.m_constituentAll ) {
    std::vector<float> constituent_m;
  
    // access constituents
    xAOD::JetConstituentVector jcv = jet->getConstituents();
    if ( jcv.isValid() )
      for ( const auto& jconstit : jcv )
	constituent_m .push_back( jconstit->m() / m_units );

    m_constituent_m ->push_back( constituent_m );
  }

}
