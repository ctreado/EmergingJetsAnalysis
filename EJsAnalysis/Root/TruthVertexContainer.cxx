#include <xAODTruth/TruthVertex.h>
#include <xAODTruth/TruthParticle.h>

#include "EJsAnalysis/TruthVertexContainer.h"
#include "EJsAnalysis/AlgConsts.h"
#include "EJsAnalysis/EJsHelperFunctions.h"

using namespace EJs;

TruthVertexContainer :: TruthVertexContainer ( const std::string& name, const std::string& detailStr, float units, bool mc ) :
  VertexContainer ( name, detailStr, units, mc )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer()", "setting up" );

  m_isDarkPionDecay       = new std::vector<uint8_t>;
  m_ID                    = new std::vector<int>;
  m_x                     = new std::vector<float>;
  m_y                     = new std::vector<float>;
  m_z                     = new std::vector<float>;
  m_r                     = new std::vector<float>;
  m_pt                    = new std::vector<float>;
  m_eta                   = new std::vector<float>;
  m_phi                   = new std::vector<float>;
  m_mass                  = new std::vector<float>;
  m_nOutP                 = new std::vector<int>;
  m_barcode               = new std::vector<int>;
  m_parent_ID             = new std::vector<int>;
  m_parent_pt             = new std::vector<float>;
  m_parent_eta            = new std::vector<float>;
  m_parent_phi            = new std::vector<float>;
  m_parent_E              = new std::vector<float>;
  m_parent_M              = new std::vector<float>;
  m_parent_charge         = new std::vector<float>;
  m_parent_pid            = new std::vector<int>;
  m_parent_status         = new std::vector<int>;
  m_parent_barcode        = new std::vector<int>;
  m_parent_prod_ID        = new std::vector<int>;
  m_parent_prod_x         = new std::vector<float>;
  m_parent_prod_y         = new std::vector<float>;
  m_parent_prod_z         = new std::vector<float>;
  m_parent_prod_r         = new std::vector<float>;
  m_parent_prod_eta       = new std::vector<float>;
  m_parent_prod_phi       = new std::vector<float>;
  m_parent_prod_barcode   = new std::vector<int>;
  m_outP_ID               = new std::vector<std::vector<int>>;
  m_outP_pt               = new std::vector<std::vector<float>>;
  m_outP_eta              = new std::vector<std::vector<float>>;
  m_outP_phi              = new std::vector<std::vector<float>>;
  m_outP_E                = new std::vector<std::vector<float>>;
  m_outP_M                = new std::vector<std::vector<float>>;
  m_outP_charge           = new std::vector<std::vector<float>>;
  m_outP_pid              = new std::vector<std::vector<int>>;
  m_outP_status           = new std::vector<std::vector<int>>;
  m_outP_barcode          = new std::vector<std::vector<int>>;
  m_outP_isReco           = new std::vector<std::vector<uint8_t>>;
  m_outP_recoProb         = new std::vector<std::vector<float>>;
  m_outP_recoID           = new std::vector<std::vector<int>>;
  m_outP_recoIsSelected   = new std::vector<std::vector<uint8_t>>;
  m_outP_recoIsAssociated = new std::vector<std::vector<uint8_t>>;
  
  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_recoVerts ) {
    m_isCloseToRecoVtx             = new std::vector<uint8_t>;
    m_closeRecoVtx_ID              = new std::vector<std::vector<int>>;
    m_closeRecoVtx_distance        = new std::vector<std::vector<float>>;
    m_isClosestToRecoVtx           = new std::vector<uint8_t>;
    m_closestRecoVtx_ID            = new std::vector<std::vector<int>>;
    m_closestRecoVtx_distance      = new std::vector<std::vector<float>>;
    m_isLinkedToRecoVtx            = new std::vector<uint8_t>;
    m_linkedRecoVtx_ID             = new std::vector<std::vector<int>>;
    m_linkedRecoVtx_score          = new std::vector<std::vector<float>>;
    m_isMaxlinkedToRecoVtx         = new std::vector<uint8_t>;
    m_maxlinkedRecoVtx_ID          = new std::vector<std::vector<int>>;
    m_maxlinkedRecoVtx_score       = new std::vector<std::vector<float>>;
    m_isLinkedParentToRecoVtx      = new std::vector<uint8_t>;
    m_linkedParentRecoVtx_ID       = new std::vector<std::vector<int>>;
    m_linkedParentRecoVtx_score    = new std::vector<std::vector<float>>;
    m_isMaxlinkedParentToRecoVtx   = new std::vector<uint8_t>;
    m_maxlinkedParentRecoVtx_ID    = new std::vector<std::vector<int>>;
    m_maxlinkedParentRecoVtx_score = new std::vector<std::vector<float>>;
  }
  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_jets ) {
    m_isTruthJetMatch  = new std::vector<uint8_t>;
    m_truthJetMatch_ID = new std::vector<std::vector<int>>;
    m_truthJetMatch_dR = new std::vector<std::vector<float>>;
    m_isDarkJetMatch   = new std::vector<uint8_t>;
    m_darkJetMatch_ID  = new std::vector<std::vector<int>>;
    m_darkJetMatch_dR  = new std::vector<std::vector<float>>;
    if ( m_infoSwitch.m_emtopo ) {
      m_isEMTopoRecoJetMatch  = new std::vector<uint8_t>;
      m_EMTopoRecoJetMatch_ID = new std::vector<std::vector<int>>;
      m_EMTopoRecoJetMatch_dR = new std::vector<std::vector<float>>;
    }
    if ( m_infoSwitch.m_pflow ) {
      m_isPFlowRecoJetMatch  = new std::vector<uint8_t>;
      m_PFlowRecoJetMatch_ID = new std::vector<std::vector<int>>;
      m_PFlowRecoJetMatch_dR = new std::vector<std::vector<float>>;
    }
  }
}


TruthVertexContainer :: ~TruthVertexContainer ()
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer()", "deleting" );

  delete m_isDarkPionDecay;
  delete m_ID;
  delete m_x;
  delete m_y;
  delete m_z;
  delete m_r;
  delete m_pt;
  delete m_eta;
  delete m_phi;
  delete m_mass;
  delete m_nOutP;
  delete m_barcode;
  delete m_parent_ID;
  delete m_parent_pt;
  delete m_parent_eta;
  delete m_parent_phi;
  delete m_parent_E;
  delete m_parent_M;
  delete m_parent_charge;
  delete m_parent_pid;
  delete m_parent_status;
  delete m_parent_barcode;
  delete m_parent_prod_ID;
  delete m_parent_prod_x;
  delete m_parent_prod_y;
  delete m_parent_prod_z;
  delete m_parent_prod_r;
  delete m_parent_prod_eta;
  delete m_parent_prod_phi;
  delete m_parent_prod_barcode;
  delete m_outP_ID;
  delete m_outP_pt;
  delete m_outP_eta;
  delete m_outP_phi;
  delete m_outP_E;
  delete m_outP_M;
  delete m_outP_charge;
  delete m_outP_pid;
  delete m_outP_status;
  delete m_outP_barcode;
  delete m_outP_isReco;
  delete m_outP_recoProb;
  delete m_outP_recoID;
  delete m_outP_recoIsSelected;
  delete m_outP_recoIsAssociated;

  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_recoVerts ) {
    delete m_isCloseToRecoVtx;
    delete m_closeRecoVtx_ID;
    delete m_closeRecoVtx_distance;
    delete m_isClosestToRecoVtx;
    delete m_closestRecoVtx_ID;
    delete m_closestRecoVtx_distance;
    delete m_isLinkedToRecoVtx;
    delete m_linkedRecoVtx_ID;
    delete m_linkedRecoVtx_score;
    delete m_isMaxlinkedToRecoVtx;
    delete m_maxlinkedRecoVtx_ID;
    delete m_maxlinkedRecoVtx_score;
    delete m_isLinkedParentToRecoVtx;
    delete m_linkedParentRecoVtx_ID;
    delete m_linkedParentRecoVtx_score;
    delete m_isMaxlinkedParentToRecoVtx;
    delete m_maxlinkedParentRecoVtx_ID;
    delete m_maxlinkedParentRecoVtx_score;
  }
  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_jets ) {
    delete m_isTruthJetMatch;
    delete m_truthJetMatch_ID;
    delete m_truthJetMatch_dR;
    delete m_isDarkJetMatch;
    delete m_darkJetMatch_ID;
    delete m_darkJetMatch_dR;
    if ( m_infoSwitch.m_emtopo ) {
      delete m_isEMTopoRecoJetMatch;
      delete m_EMTopoRecoJetMatch_ID;
      delete m_EMTopoRecoJetMatch_dR;
    }
    if ( m_infoSwitch.m_pflow ) {
      delete m_isPFlowRecoJetMatch;
      delete m_PFlowRecoJetMatch_ID;
      delete m_PFlowRecoJetMatch_dR;
    }
  }
}


void TruthVertexContainer :: setTree ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::setTree()", "setting tree" );
  
  VertexContainer::setTree ( tree );

  connectBranch<uint8_t>              ( tree, "isDarkPionDecay",       &m_isDarkPionDecay       );
  connectBranch<int>                  ( tree, "ID",                    &m_ID                    );
  connectBranch<float>                ( tree, "x",                     &m_x                     );
  connectBranch<float>                ( tree, "y",                     &m_y                     );
  connectBranch<float>                ( tree, "z",                     &m_z                     );
  connectBranch<float>                ( tree, "r",                     &m_r                     );
  connectBranch<float>                ( tree, "pt",                    &m_pt                    );
  connectBranch<float>                ( tree, "eta",                   &m_eta                   );
  connectBranch<float>                ( tree, "phi",                   &m_phi                   );
  connectBranch<float>                ( tree, "mass",                  &m_mass                  );
  connectBranch<int>                  ( tree, "nOutP",                 &m_nOutP                 );
  connectBranch<int>                  ( tree, "barcode",               &m_barcode               );
  connectBranch<int>                  ( tree, "parent_ID",             &m_parent_ID             );
  connectBranch<float>                ( tree, "parent_pt",             &m_parent_pt             );
  connectBranch<float>                ( tree, "parent_eta",            &m_parent_eta            );
  connectBranch<float>                ( tree, "parent_phi",            &m_parent_phi            );
  connectBranch<float>                ( tree, "parent_E",              &m_parent_E              );
  connectBranch<float>                ( tree, "parent_M",              &m_parent_M              );
  connectBranch<float>                ( tree, "parent_charge",         &m_parent_charge         );
  connectBranch<int>                  ( tree, "parent_pid",            &m_parent_pid            );
  connectBranch<int>                  ( tree, "parent_status",         &m_parent_status         );
  connectBranch<int>                  ( tree, "parent_barcode",        &m_parent_barcode        );
  connectBranch<int>                  ( tree, "parent_prod_ID",        &m_parent_prod_ID        );
  connectBranch<float>                ( tree, "parent_prod_x",         &m_parent_prod_x         );
  connectBranch<float>                ( tree, "parent_prod_y",         &m_parent_prod_y         );
  connectBranch<float>                ( tree, "parent_prod_z",         &m_parent_prod_z         );
  connectBranch<float>                ( tree, "parent_prod_r",         &m_parent_prod_r         );
  connectBranch<float>                ( tree, "parent_prod_eta",       &m_parent_prod_eta       );
  connectBranch<float>                ( tree, "parent_prod_phi",       &m_parent_prod_phi       );
  connectBranch<int>                  ( tree, "parent_prod_barcode",   &m_parent_prod_barcode   );
  connectBranch<std::vector<int>>     ( tree, "outP_ID",               &m_outP_ID               );
  connectBranch<std::vector<float>>   ( tree, "outP_pt",               &m_outP_pt               );
  connectBranch<std::vector<float>>   ( tree, "outP_eta",              &m_outP_eta              );
  connectBranch<std::vector<float>>   ( tree, "outP_phi",              &m_outP_phi              );
  connectBranch<std::vector<float>>   ( tree, "outP_E",                &m_outP_E                );
  connectBranch<std::vector<float>>   ( tree, "outP_M",                &m_outP_M                );
  connectBranch<std::vector<float>>   ( tree, "outP_charge",           &m_outP_charge           );
  connectBranch<std::vector<int>>     ( tree, "outP_pid",              &m_outP_pid              );
  connectBranch<std::vector<int>>     ( tree, "outP_status",           &m_outP_status           );
  connectBranch<std::vector<int>>     ( tree, "outP_barcode",          &m_outP_barcode          );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isReco",           &m_outP_isReco           );
  connectBranch<std::vector<float>>   ( tree, "outP_recoProb",         &m_outP_recoProb         );
  connectBranch<std::vector<int>>     ( tree, "outP_recoID",           &m_outP_recoID           );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_recoIsSelected",   &m_outP_recoIsSelected   );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_recoIsAssociated", &m_outP_recoIsAssociated );

  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_recoVerts ) {
    connectBranch<uint8_t>            ( tree, "isCloseToRecoVtx",             &m_isCloseToRecoVtx             );
    connectBranch<std::vector<int>>   ( tree, "closeRecoVtx_ID",              &m_closeRecoVtx_ID              );
    connectBranch<std::vector<float>> ( tree, "closeRecoVtx_distance",        &m_closeRecoVtx_distance        );
    connectBranch<uint8_t>            ( tree, "isClosestToRecoVtx",           &m_isClosestToRecoVtx           );
    connectBranch<std::vector<int>>   ( tree, "closestRecoVtx_ID",            &m_closestRecoVtx_ID            );
    connectBranch<std::vector<float>> ( tree, "closestRecoVtx_distance",      &m_closestRecoVtx_distance      );
    connectBranch<uint8_t>            ( tree, "isLinkedToRecoVtx",            &m_isLinkedToRecoVtx            );
    connectBranch<std::vector<int>>   ( tree, "linkedRecoVtx_ID",             &m_linkedRecoVtx_ID             );
    connectBranch<std::vector<float>> ( tree, "linkedRecoVtx_score",          &m_linkedRecoVtx_score          );
    connectBranch<uint8_t>            ( tree, "isMaxlinkedToRecoVtx",         &m_isMaxlinkedToRecoVtx         );
    connectBranch<std::vector<int>>   ( tree, "maxlinkedRecoVtx_ID",          &m_maxlinkedRecoVtx_ID          );
    connectBranch<std::vector<float>> ( tree, "maxlinkedRecoVtx_score",       &m_maxlinkedRecoVtx_score       );
    connectBranch<uint8_t>            ( tree, "isLinkedParentToRecoVtx",      &m_isLinkedParentToRecoVtx      );
    connectBranch<std::vector<int>>   ( tree, "linkedParentRecoVtx_ID",       &m_linkedParentRecoVtx_ID       );
    connectBranch<std::vector<float>> ( tree, "linkedParentRecoVtx_score",    &m_linkedParentRecoVtx_score    );
    connectBranch<uint8_t>            ( tree, "isMaxlinkedParentToRecoVtx",   &m_isMaxlinkedParentToRecoVtx   );
    connectBranch<std::vector<int>>   ( tree, "maxlinkedParentRecoVtx_ID",    &m_maxlinkedParentRecoVtx_ID    );
    connectBranch<std::vector<float>> ( tree, "maxlinkedParentRecoVtx_score", &m_maxlinkedParentRecoVtx_score );
  }
  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_jets ) {
    connectBranch<uint8_t>              ( tree, "isTruthJetMatch",       &m_isTruthJetMatch       );
    connectBranch<std::vector<int>>     ( tree, "truthJetMatch_ID",      &m_truthJetMatch_ID      );
    connectBranch<std::vector<float>>   ( tree, "truthJetMatch_dR",      &m_truthJetMatch_dR      );
    connectBranch<uint8_t>              ( tree, "isDarkJetMatch",        &m_isDarkJetMatch        );
    connectBranch<std::vector<int>>     ( tree, "darkJetMatch_ID",       &m_darkJetMatch_ID       );
    connectBranch<std::vector<float>>   ( tree, "darkJetMatch_dR",       &m_darkJetMatch_dR       );
    if ( m_infoSwitch.m_emtopo ) {
      connectBranch<uint8_t>            ( tree, "isEMTopoRecoJetMatch",  &m_isEMTopoRecoJetMatch  );
      connectBranch<std::vector<int>>   ( tree, "EMTopoRecoJetMatch_ID", &m_EMTopoRecoJetMatch_ID );
      connectBranch<std::vector<float>> ( tree, "EMTopoRecoJetMatch_dR", &m_EMTopoRecoJetMatch_dR );
    }
    if ( m_infoSwitch.m_pflow ) {
      connectBranch<uint8_t>            ( tree, "isPFlowRecoJetMatch",   &m_isPFlowRecoJetMatch   );
      connectBranch<std::vector<int>>   ( tree, "PFlowRecoJetMatch_ID",  &m_PFlowRecoJetMatch_ID  );
      connectBranch<std::vector<float>> ( tree, "PFlowRecoJetMatch_dR",  &m_PFlowRecoJetMatch_dR  );
    }
  }
}


void TruthVertexContainer :: setBranches ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::setBranches()", "setting branches" );
  
  VertexContainer::setBranches ( tree );

  setBranch<uint8_t>              ( tree, "isDarkPionDecay",       m_isDarkPionDecay       );
  setBranch<int>                  ( tree, "ID",                    m_ID                    );
  setBranch<float>                ( tree, "x",                     m_x                     );
  setBranch<float>                ( tree, "y",                     m_y                     );
  setBranch<float>                ( tree, "z",                     m_z                     );
  setBranch<float>                ( tree, "r",                     m_r                     );
  setBranch<float>                ( tree, "pt",                    m_pt                    );
  setBranch<float>                ( tree, "eta",                   m_eta                   );
  setBranch<float>                ( tree, "phi",                   m_phi                   );
  setBranch<float>                ( tree, "mass",                  m_mass                  );
  setBranch<int>                  ( tree, "nOutP",                 m_nOutP                 );
  setBranch<int>                  ( tree, "barcode",               m_barcode               );
  setBranch<int>                  ( tree, "parent_ID",             m_parent_ID             );
  setBranch<float>                ( tree, "parent_pt",             m_parent_pt             );
  setBranch<float>                ( tree, "parent_eta",            m_parent_eta            );
  setBranch<float>                ( tree, "parent_phi",            m_parent_phi            );
  setBranch<float>                ( tree, "parent_E",              m_parent_E              );
  setBranch<float>                ( tree, "parent_M",              m_parent_M              );
  setBranch<float>                ( tree, "parent_charge",         m_parent_charge         );
  setBranch<int>                  ( tree, "parent_pid",            m_parent_pid            );
  setBranch<int>                  ( tree, "parent_status",         m_parent_status         );
  setBranch<int>                  ( tree, "parent_barcode",        m_parent_barcode        );
  setBranch<int>                  ( tree, "parent_prod_ID",        m_parent_prod_ID        );
  setBranch<float>                ( tree, "parent_prod_x",         m_parent_prod_x         );
  setBranch<float>                ( tree, "parent_prod_y",         m_parent_prod_y         );
  setBranch<float>                ( tree, "parent_prod_z",         m_parent_prod_z         );
  setBranch<float>                ( tree, "parent_prod_r",         m_parent_prod_r         );
  setBranch<float>                ( tree, "parent_prod_eta",       m_parent_prod_eta       );
  setBranch<float>                ( tree, "parent_prod_phi",       m_parent_prod_phi       );
  setBranch<int>                  ( tree, "parent_prod_barcode",   m_parent_prod_barcode   );
  setBranch<std::vector<int>>     ( tree, "outP_ID",               m_outP_ID               );
  setBranch<std::vector<float>>   ( tree, "outP_pt",               m_outP_pt               );
  setBranch<std::vector<float>>   ( tree, "outP_eta",              m_outP_eta              );
  setBranch<std::vector<float>>   ( tree, "outP_phi",              m_outP_phi              );
  setBranch<std::vector<float>>   ( tree, "outP_E",                m_outP_E                );
  setBranch<std::vector<float>>   ( tree, "outP_M",                m_outP_M                );
  setBranch<std::vector<float>>   ( tree, "outP_charge",           m_outP_charge           );
  setBranch<std::vector<int>>     ( tree, "outP_pid",              m_outP_pid              );
  setBranch<std::vector<int>>     ( tree, "outP_status",           m_outP_status           );
  setBranch<std::vector<int>>     ( tree, "outP_barcode",          m_outP_barcode          );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isReco",           m_outP_isReco           );
  setBranch<std::vector<float>>   ( tree, "outP_recoProb",         m_outP_recoProb         );
  setBranch<std::vector<int>>     ( tree, "outP_recoID",           m_outP_recoID           );
  setBranch<std::vector<uint8_t>> ( tree, "outP_recoIsSelected",   m_outP_recoIsSelected   );
  setBranch<std::vector<uint8_t>> ( tree, "outP_recoIsAssociated", m_outP_recoIsAssociated );

  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_recoVerts ) {
    setBranch<uint8_t>            ( tree, "isCloseToRecoVtx",             m_isCloseToRecoVtx             );
    setBranch<std::vector<int>>   ( tree, "closeRecoVtx_ID",              m_closeRecoVtx_ID              );
    setBranch<std::vector<float>> ( tree, "closeRecoVtx_distance",        m_closeRecoVtx_distance        );
    setBranch<uint8_t>            ( tree, "isClosestToRecoVtx",           m_isClosestToRecoVtx           );
    setBranch<std::vector<int>>   ( tree, "closestRecoVtx_ID",            m_closestRecoVtx_ID            );
    setBranch<std::vector<float>> ( tree, "closestRecoVtx_distance",      m_closestRecoVtx_distance      );
    setBranch<uint8_t>            ( tree, "isLinkedToRecoVtx",            m_isLinkedToRecoVtx            );
    setBranch<std::vector<int>>   ( tree, "linkedRecoVtx_ID",             m_linkedRecoVtx_ID             );
    setBranch<std::vector<float>> ( tree, "linkedRecoVtx_score",          m_linkedRecoVtx_score          );
    setBranch<uint8_t>            ( tree, "isMaxlinkedToRecoVtx",         m_isMaxlinkedToRecoVtx         );
    setBranch<std::vector<int>>   ( tree, "maxlinkedRecoVtx_ID",          m_maxlinkedRecoVtx_ID          );
    setBranch<std::vector<float>> ( tree, "maxlinkedRecoVtx_score",       m_maxlinkedRecoVtx_score       );
    setBranch<uint8_t>            ( tree, "isLinkedParentToRecoVtx",      m_isLinkedParentToRecoVtx      );
    setBranch<std::vector<int>>   ( tree, "linkedParentRecoVtx_ID",       m_linkedParentRecoVtx_ID       );
    setBranch<std::vector<float>> ( tree, "linkedParentRecoVtx_score",    m_linkedParentRecoVtx_score    );
    setBranch<uint8_t>            ( tree, "isMaxlinkedParentToRecoVtx",   m_isMaxlinkedParentToRecoVtx   );
    setBranch<std::vector<int>>   ( tree, "maxlinkedParentRecoVtx_ID",    m_maxlinkedParentRecoVtx_ID    );
    setBranch<std::vector<float>> ( tree, "maxlinkedParentRecoVtx_score", m_maxlinkedParentRecoVtx_score );
  }
  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_jets ) {
    setBranch<uint8_t>              ( tree, "isTruthJetMatch",       m_isTruthJetMatch       );
    setBranch<std::vector<int>>     ( tree, "truthJetMatch_ID",      m_truthJetMatch_ID      );
    setBranch<std::vector<float>>   ( tree, "truthJetMatch_dR",      m_truthJetMatch_dR      );
    setBranch<uint8_t>              ( tree, "isDarkJetMatch",        m_isDarkJetMatch        );
    setBranch<std::vector<int>>     ( tree, "darkJetMatch_ID",       m_darkJetMatch_ID       );
    setBranch<std::vector<float>>   ( tree, "darkJetMatch_dR",       m_darkJetMatch_dR       );
    if ( m_infoSwitch.m_emtopo ) {
      setBranch<uint8_t>            ( tree, "isEMTopoRecoJetMatch",  m_isEMTopoRecoJetMatch  );
      setBranch<std::vector<int>>   ( tree, "EMTopoRecoJetMatch_ID", m_EMTopoRecoJetMatch_ID );
      setBranch<std::vector<float>> ( tree, "EMTopoRecoJetMatch_dR", m_EMTopoRecoJetMatch_dR );
    }
    if ( m_infoSwitch.m_pflow ) {
      setBranch<uint8_t>            ( tree, "isPFlowRecoJetMatch",   m_isPFlowRecoJetMatch   );
      setBranch<std::vector<int>>   ( tree, "PFlowRecoJetMatch_ID",  m_PFlowRecoJetMatch_ID  );
      setBranch<std::vector<float>> ( tree, "PFlowRecoJetMatch_dR",  m_PFlowRecoJetMatch_dR  );
    }
  }
}


void TruthVertexContainer :: clear ()
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::clear()", "clearing branches" );
  
  VertexContainer::clear ();

  m_isDarkPionDecay       ->clear();
  m_ID                    ->clear();
  m_x                     ->clear();
  m_y                     ->clear();
  m_z                     ->clear();
  m_r                     ->clear();
  m_pt                    ->clear();
  m_eta                   ->clear();
  m_phi                   ->clear();
  m_mass                  ->clear();
  m_nOutP                 ->clear();
  m_barcode               ->clear();
  m_parent_ID             ->clear();
  m_parent_pt             ->clear();
  m_parent_eta            ->clear();
  m_parent_phi            ->clear();
  m_parent_E              ->clear();
  m_parent_M              ->clear();
  m_parent_charge         ->clear();
  m_parent_pid            ->clear();
  m_parent_status         ->clear();
  m_parent_barcode        ->clear();
  m_parent_prod_ID        ->clear();
  m_parent_prod_x         ->clear();
  m_parent_prod_y         ->clear();
  m_parent_prod_z         ->clear();
  m_parent_prod_r         ->clear();
  m_parent_prod_eta       ->clear();
  m_parent_prod_phi       ->clear();
  m_parent_prod_barcode   ->clear();
  m_outP_ID               ->clear();
  m_outP_pt               ->clear();
  m_outP_eta              ->clear();
  m_outP_phi              ->clear();
  m_outP_E                ->clear();
  m_outP_M                ->clear();
  m_outP_charge           ->clear();
  m_outP_pid              ->clear();
  m_outP_status           ->clear();
  m_outP_barcode          ->clear();
  m_outP_isReco           ->clear();
  m_outP_recoProb         ->clear();
  m_outP_recoID           ->clear();
  m_outP_recoIsSelected   ->clear();
  m_outP_recoIsAssociated ->clear();

  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_recoVerts ) {
    m_isCloseToRecoVtx             ->clear();
    m_closeRecoVtx_ID              ->clear();
    m_closeRecoVtx_distance        ->clear();
    m_isClosestToRecoVtx           ->clear();
    m_closestRecoVtx_ID            ->clear();
    m_closestRecoVtx_distance      ->clear();
    m_isLinkedToRecoVtx            ->clear();
    m_linkedRecoVtx_ID             ->clear();
    m_linkedRecoVtx_score          ->clear();
    m_isMaxlinkedToRecoVtx         ->clear();
    m_maxlinkedRecoVtx_ID          ->clear();
    m_maxlinkedRecoVtx_score       ->clear();
    m_isLinkedParentToRecoVtx      ->clear();
    m_linkedParentRecoVtx_ID       ->clear();
    m_linkedParentRecoVtx_score    ->clear();
    m_isMaxlinkedParentToRecoVtx   ->clear();
    m_maxlinkedParentRecoVtx_ID    ->clear();
    m_maxlinkedParentRecoVtx_score ->clear();
  }
  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_jets ) {
    m_isTruthJetMatch         ->clear();
    m_truthJetMatch_ID        ->clear();
    m_truthJetMatch_dR        ->clear();
    m_isDarkJetMatch          ->clear();
    m_darkJetMatch_ID         ->clear();
    m_darkJetMatch_dR         ->clear();
    if ( m_infoSwitch.m_emtopo ) {
      m_isEMTopoRecoJetMatch  ->clear();
      m_EMTopoRecoJetMatch_ID ->clear();
      m_EMTopoRecoJetMatch_dR ->clear();
    }
    if ( m_infoSwitch.m_pflow ) {
      m_isPFlowRecoJetMatch   ->clear();
      m_PFlowRecoJetMatch_ID  ->clear();
      m_PFlowRecoJetMatch_dR  ->clear();
    }
  }
}


void TruthVertexContainer :: FillTruthVertex ( const xAOD::TruthVertex* truthVtx, const std::string treeName )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::FillTruthVertex()", "filling branches" );
  
  VertexContainer::FillVertex ();

  m_isDarkPionDecay ->push_back( EJsHelper::selectDarkPion( truthVtx ) );

  m_ID      ->push_back( AUXDYN( truthVtx, int, "ID" )  );
  m_x       ->push_back( truthVtx->x()                  );
  m_y       ->push_back( truthVtx->y()                  );
  m_z       ->push_back( truthVtx->z()                  );
  m_r       ->push_back( truthVtx->perp()               );
  m_eta     ->push_back( truthVtx->eta()                );
  m_phi     ->push_back( truthVtx->phi()                );
  m_nOutP   ->push_back( truthVtx->nOutgoingParticles() );
  m_barcode ->push_back( truthVtx->barcode()            );

  int   parent_ID      = AlgConsts::invalidInt;
  float parent_pt      = AlgConsts::invalidFloat;
  float parent_eta     = AlgConsts::invalidFloat;
  float parent_phi     = AlgConsts::invalidFloat;
  float parent_E       = AlgConsts::invalidFloat;
  float parent_M       = AlgConsts::invalidFloat;
  float parent_charge  = AlgConsts::invalidFloat;
  float parent_pid     = AlgConsts::invalidInt;
  int   parent_status  = AlgConsts::invalidInt;
  int   parent_barcode = AlgConsts::invalidInt;

  int   pProd_ID      = AlgConsts::invalidInt;
  float pProd_x       = AlgConsts::invalidFloat;
  float pProd_y       = AlgConsts::invalidFloat;
  float pProd_z       = AlgConsts::invalidFloat;
  float pProd_r       = AlgConsts::invalidFloat;
  float pProd_eta     = AlgConsts::invalidFloat;
  float pProd_phi     = AlgConsts::invalidFloat;
  int   pProd_barcode = AlgConsts::invalidInt;
  
  const auto* parent = truthVtx->incomingParticle(0);
  if ( parent ) {
    parent_ID      = AUXDYN( parent, int, "ID" );
    parent_pt      = parent->pt() / m_units;
    parent_eta     = parent->eta();
    parent_phi     = parent->phi();
    parent_E       = parent->e()  / m_units;
    parent_M       = parent->m()  / m_units;
    parent_charge  = parent->charge();
    parent_pid     = parent->pdgId();
    parent_status  = parent->status();
    parent_barcode = parent->barcode();

    const auto* prodVtx = parent->prodVtx();
    if ( prodVtx ) {
      pProd_ID      = AUXDYN( prodVtx, int, "ID" );
      pProd_x       = prodVtx->x();
      pProd_y       = prodVtx->y();
      pProd_z       = prodVtx->z();
      pProd_r       = prodVtx->perp();
      pProd_eta     = prodVtx->eta();
      pProd_phi     = prodVtx->phi();
      pProd_barcode = prodVtx->barcode();
    }
  }

  m_parent_ID      ->push_back( parent_ID      );
  m_parent_pt      ->push_back( parent_pt      );
  m_parent_eta     ->push_back( parent_eta     );
  m_parent_phi     ->push_back( parent_phi     );
  m_parent_E       ->push_back( parent_E       );
  m_parent_M       ->push_back( parent_M       );
  m_parent_charge  ->push_back( parent_charge  );
  m_parent_pid     ->push_back( parent_pid     );
  m_parent_status  ->push_back( parent_status  );
  m_parent_barcode ->push_back( parent_barcode );

  m_parent_prod_ID      ->push_back( pProd_ID      );
  m_parent_prod_x       ->push_back( pProd_x       );
  m_parent_prod_y       ->push_back( pProd_y       );
  m_parent_prod_z       ->push_back( pProd_z       );
  m_parent_prod_r       ->push_back( pProd_r       );
  m_parent_prod_eta     ->push_back( pProd_eta     );
  m_parent_prod_phi     ->push_back( pProd_phi     );
  m_parent_prod_barcode ->push_back( pProd_barcode );

  std::vector<const xAOD::TruthParticle*> outParts;
  
  std::vector<int>     outP_ID;
  std::vector<float>   outP_pt;
  std::vector<float>   outP_eta;
  std::vector<float>   outP_phi;
  std::vector<float>   outP_E;
  std::vector<float>   outP_M;
  std::vector<float>   outP_charge;
  std::vector<int>     outP_pid;
  std::vector<int>     outP_status;
  std::vector<int>     outP_barcode;
  std::vector<uint8_t> outP_isReco;
  std::vector<float>   outP_recoProb;
  std::vector<int>     outP_recoID;
  std::vector<uint8_t> outP_recoIsSelected;
  std::vector<uint8_t> outP_recoIsAssociated;
  
  for ( size_t i = 0; i != truthVtx->nOutgoingParticles(); ++i ) {
    const auto* outP = truthVtx->outgoingParticle(i);
    if ( !outP )           continue;
    outParts      .push_back( outP                                            );
    outP_ID       .push_back( AUXDYN( outP, int, "ID"                       ) );
    outP_pt       .push_back( outP->pt() / m_units                            );
    outP_eta      .push_back( outP->eta()                                     );
    outP_phi      .push_back( outP->phi()                                     );
    outP_E        .push_back( outP->e()  / m_units                            );
    outP_M        .push_back( outP->m()  / m_units                            );
    outP_charge   .push_back( outP->charge()                                  );
    outP_pid      .push_back( outP->pdgId()                                   );
    outP_status   .push_back( outP->status()                                  );
    outP_barcode  .push_back( outP->barcode()                                 );
    outP_isReco   .push_back( AUXDYN( outP, char,   "isTrackMatch"          ) );
    outP_recoProb .push_back( AUXDYN( outP, double, "trackMatchProbability" ) );
    outP_recoID   .push_back( AUXDYN( outP, int,    "ID"                    ) );
    if ( outP->isAvailable<char>("is_selected")   )
      outP_recoIsSelected   .push_back( outP->auxdataConst<char>("is_selected")   );
    if ( outP->isAvailable<char>("is_associated") )
      outP_recoIsAssociated .push_back( outP->auxdataConst<char>("is_associated") );
  }

  const TLorentzVector& sumP4 = EJsHelper::truthSumP4 ( outParts );
  m_pt   ->push_back( sumP4.Pt() / m_units );
  m_mass ->push_back( sumP4.M()  / m_units );

  m_outP_ID               ->push_back( outP_ID               );
  m_outP_pt               ->push_back( outP_pt               );
  m_outP_eta              ->push_back( outP_eta              );
  m_outP_phi              ->push_back( outP_phi              );
  m_outP_E                ->push_back( outP_E                );
  m_outP_M                ->push_back( outP_M                );
  m_outP_charge           ->push_back( outP_charge           );
  m_outP_pid              ->push_back( outP_pid              );
  m_outP_status           ->push_back( outP_status           );
  m_outP_barcode          ->push_back( outP_barcode          );
  m_outP_isReco           ->push_back( outP_isReco           );
  m_outP_recoProb         ->push_back( outP_recoProb         );
  m_outP_recoID           ->push_back( outP_recoID           );
  m_outP_recoIsSelected   ->push_back( outP_recoIsSelected   );
  m_outP_recoIsAssociated ->push_back( outP_recoIsAssociated );

  
  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_recoVerts ) {
    std::vector<int> closeReco_ID;
    std::vector<int> closestReco_ID;
    std::vector<int> linkedReco_ID;
    std::vector<int> maxlinkedReco_ID;
    std::vector<int> linkedPReco_ID;
    std::vector<int> maxlinkedPReco_ID;
    
    uint8_t isCloseToReco = false;
    if ( truthVtx->isAvailable<char>("isCloseToSecondaryVertex") )
      isCloseToReco = truthVtx->auxdataConst<char>("isCloseToSecondaryVertex");
    // access reco vertex links truthVtx close to
    static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> closeRecoAccess("closeSecondaryVertexLinks");
    if ( closeRecoAccess.isAvailable( *truthVtx ) ) {
      const EJsHelper::VertexLinkVector_t& vtxLinks = closeRecoAccess( *truthVtx );
      for ( const auto& link : vtxLinks ) {
	if ( !link.isValid() ) continue;
	closeReco_ID .push_back( AUXDYN( (*link), int, "ID") );
      }
    }  
    
    uint8_t isClosestToReco = false;
    if ( truthVtx->isAvailable<char>("isClosestToSecondaryVertex") )
      isClosestToReco = truthVtx->auxdataConst<char>("isClosestToSecondaryVertex");
    // access reco vertex links truthVtx closest to
    static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> closestRecoAccess("closestSecondaryVertexLinks");
    if ( closestRecoAccess.isAvailable( *truthVtx ) ) {
      const EJsHelper::VertexLinkVector_t& vtxLinks = closestRecoAccess( *truthVtx );
      for ( const auto& link : vtxLinks ) {
	if ( !link.isValid() ) continue;
	closestReco_ID .push_back( AUXDYN( (*link), int, "ID") );
      }
    }
    
    uint8_t isLinkedToReco = false;
    if ( truthVtx->isAvailable<char>("isLinkedToSecondaryVertex") )
      isLinkedToReco = truthVtx->auxdataConst<char>("isLinkedToSecondaryVertex");
    // access reco vertex links truthVtx linked to
    static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> linkRecoAccess("linkedSecondaryVertexLinks");
    if ( linkRecoAccess.isAvailable( *truthVtx ) ) {
      const EJsHelper::VertexLinkVector_t& vtxLinks = linkRecoAccess( *truthVtx );
      for ( const auto& link : vtxLinks ) {
	if ( !link.isValid() ) continue;
	linkedReco_ID .push_back( AUXDYN( (*link), int, "ID") );
      }
    }
    
    uint8_t isMaxlinkedToReco = false;
    if ( truthVtx->isAvailable<char>("isMaxlinkedToSecondaryVertex") )
      isMaxlinkedToReco = truthVtx->auxdataConst<char>("isMaxlinkedToSecondaryVertex");
    // access reco vertex links truthVtx max-linked to
    static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> maxlinkRecoAccess("maxlinkedSecondaryVertexLinks");
    if ( maxlinkRecoAccess.isAvailable( *truthVtx ) ) {
      const EJsHelper::VertexLinkVector_t& vtxLinks = maxlinkRecoAccess( *truthVtx );
      for ( const auto& link : vtxLinks ) {
	if ( !link.isValid() ) continue;
	maxlinkedReco_ID .push_back( AUXDYN( (*link), int, "ID") );
      }
    }
    
    uint8_t isLinkedParentToReco = false;
    if ( truthVtx->isAvailable<char>("isLinkedParentToSecondaryVertex") )
      isLinkedParentToReco = truthVtx->auxdataConst<char>("isLinkedParentToSecondaryVertex");
    // access reco vertex links truthVtx linked parent to
    static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> linkPRecoAccess("linkedParentSecondaryVertexLinks");
    if ( linkPRecoAccess.isAvailable( *truthVtx ) ) {
      const EJsHelper::VertexLinkVector_t& vtxLinks = linkPRecoAccess( *truthVtx );
      for ( const auto& link : vtxLinks ) {
	if ( !link.isValid() ) continue;
	linkedPReco_ID .push_back( AUXDYN( (*link), int, "ID") );
      }
    }
    
    uint8_t isMaxlinkedParentToReco = false;
    if ( truthVtx->isAvailable<char>("isMaxlinkedParentToSecondaryVertex") )
      isMaxlinkedParentToReco = truthVtx->auxdataConst<char>("isMaxlinkedParentToSecondaryVertex");
    // access reco vertex links truthVtx max-linked parent to
    static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> maxlinkPRecoAccess("maxlinkedParentSecondaryVertexLinks");
    if ( maxlinkPRecoAccess.isAvailable( *truthVtx ) ) {
      const EJsHelper::VertexLinkVector_t& vtxLinks = maxlinkPRecoAccess( *truthVtx );
      for ( const auto& link : vtxLinks ) {
	if ( !link.isValid() ) continue;
	maxlinkedPReco_ID .push_back( AUXDYN( (*link), int, "ID") );
      }
    }

    m_isCloseToRecoVtx             ->push_back( isCloseToReco                                                        );
    m_closeRecoVtx_ID              ->push_back( closeReco_ID                                                         );
    m_closeRecoVtx_distance        ->push_back( AUXDYNVEC( truthVtx, float, "closeSecondaryVertexDists"            ) );
    m_isClosestToRecoVtx           ->push_back( isClosestToReco                                                      );
    m_closestRecoVtx_ID            ->push_back( closestReco_ID                                                       );
    m_closestRecoVtx_distance      ->push_back( AUXDYNVEC( truthVtx, float, "closestSecondaryVertexDists"          ) );
    m_isLinkedToRecoVtx            ->push_back( isLinkedToReco                                                       );
    m_linkedRecoVtx_ID             ->push_back( linkedReco_ID                                                        );
    m_linkedRecoVtx_score          ->push_back( AUXDYNVEC( truthVtx, float, "linkedSecondaryVertexScores"          ) );
    m_isMaxlinkedToRecoVtx         ->push_back( isMaxlinkedToReco                                                    );
    m_maxlinkedRecoVtx_ID          ->push_back( maxlinkedReco_ID                                                     );
    m_maxlinkedRecoVtx_score       ->push_back( AUXDYNVEC( truthVtx, float, "maxlinkedSecondaryVertexScores"       ) );
    m_isLinkedParentToRecoVtx      ->push_back( isLinkedParentToReco                                                 );
    m_linkedParentRecoVtx_ID       ->push_back( linkedPReco_ID                                                       );
    m_linkedParentRecoVtx_score    ->push_back( AUXDYNVEC( truthVtx, float, "linkedParentSecondaryVertexScores"    ) );
    m_isMaxlinkedParentToRecoVtx   ->push_back( isMaxlinkedParentToReco                                              );
    m_maxlinkedParentRecoVtx_ID    ->push_back( linkedPReco_ID                                                       );
    m_maxlinkedParentRecoVtx_score ->push_back( AUXDYNVEC( truthVtx, float, "maxlinkedParentSecondaryVertexScores" ) );
  }


  if ( m_infoSwitch.m_isMatched || m_infoSwitch.m_jets ) {
    std::string jet_str = treeName;
    if ( treeName == "nominal" ) jet_str = "";

    uint8_t isTruthJetMatch = false;
    if ( truthVtx->isAvailable<char>("isMatchedToTruthJet") )
      isTruthJetMatch = truthVtx->auxdataConst<char>("isMatchedToTruthJet");
    uint8_t isDarkJetMatch = false;
    if ( truthVtx->isAvailable<char>("isMatchedToDarkJet") )
      isDarkJetMatch = truthVtx->auxdataConst<char>("isMatchedToDarkJet");
    uint8_t isEMTopoJetMatch = false;
    if ( truthVtx->isAvailable<char>("isMatchedToRecoJet_EMTopo" + jet_str) )
      isEMTopoJetMatch = truthVtx->auxdataConst<char>("isMatchedToRecoJet_EMTopo" + jet_str);
    uint8_t isPFlowJetMatch = false;
    if ( truthVtx->isAvailable<char>("isMatchedToRecoJet_PFlow" + jet_str) )
      isPFlowJetMatch = truthVtx->auxdataConst<char>("isMatchedToRecoJet_PFlow" + jet_str);

    m_isTruthJetMatch       ->push_back( isTruthJetMatch                                                  );
    m_truthJetMatch_ID      ->push_back( AUXDYNVEC( truthVtx, int,   "truthJetMatchIDs"                 ) );
    m_truthJetMatch_dR      ->push_back( AUXDYNVEC( truthVtx, float, "truthJetMatchDRs"                 ) );
    m_isDarkJetMatch        ->push_back( isDarkJetMatch                                                   );
    m_darkJetMatch_ID       ->push_back( AUXDYNVEC( truthVtx, int,   "darkJetMatchIDs"                  ) );
    m_darkJetMatch_dR       ->push_back( AUXDYNVEC( truthVtx, float, "darkJetMatchDRs"                  ) );
    m_isEMTopoRecoJetMatch  ->push_back( isEMTopoJetMatch                                                 );
    m_EMTopoRecoJetMatch_ID ->push_back( AUXDYNVEC( truthVtx, int,   "recoJetMatchIDs_EMTopo" + jet_str ) );
    m_EMTopoRecoJetMatch_dR ->push_back( AUXDYNVEC( truthVtx, float, "recoJetMatchDRs_EMTopo" + jet_str ) );
    m_isPFlowRecoJetMatch   ->push_back( isPFlowJetMatch                                                  );
    m_PFlowRecoJetMatch_ID  ->push_back( AUXDYNVEC( truthVtx, int,   "recoJetMatchIDs_PFlow"  + jet_str ) );
    m_PFlowRecoJetMatch_dR  ->push_back( AUXDYNVEC( truthVtx, float, "recoJetMatchDRs_PFlow"  + jet_str ) );
  }
}
