#include <xAODTruth/TruthVertex.h>
#include <xAODTruth/TruthParticle.h>

#include "EJsAnalysis/TruthVertexContainer.h"
#include "EJsAnalysis/AlgConsts.h"
#include "EJsAnalysis/EJsHelperFunctions.h"

// CHANGE IS-RECO TO SPECIFIC FUNCTION (RATHER THAN MATCHING)

using namespace EJs;

TruthVertexContainer :: TruthVertexContainer ( const std::string& name, const std::string& detailStr, float units,
					       bool mc, bool emtopo, bool pflow ) :
  VertexContainer ( name, detailStr, units, mc )
{
  m_doEMTopo = emtopo;
  m_doPFlow  = pflow;
  
  if ( m_debug ) Info( "EJs::TruthVertexContainer()", "setting up" );

  m_passSel             = new std::vector<uint8_t>;
  m_llpDecay            = new std::vector<std::string>;
  m_ID                  = new std::vector<int>;
  m_index               = new std::vector<int>;
  m_x                   = new std::vector<float>;
  m_y                   = new std::vector<float>;
  m_z                   = new std::vector<float>;
  m_r                   = new std::vector<float>;
  m_pt                  = new std::vector<float>;
  m_eta                 = new std::vector<float>;
  m_phi                 = new std::vector<float>;
  m_mass                = new std::vector<float>;
  m_nOutP               = new std::vector<int>;
  m_barcode             = new std::vector<int>;
  m_parent_ID           = new std::vector<int>;
  m_parent_index        = new std::vector<int>;
  m_parent_pt           = new std::vector<float>;
  m_parent_eta          = new std::vector<float>;
  m_parent_phi          = new std::vector<float>;
  m_parent_E            = new std::vector<float>;
  m_parent_M            = new std::vector<float>;
  m_parent_charge       = new std::vector<float>;
  m_parent_pdgId        = new std::vector<int>;
  m_parent_status       = new std::vector<int>;
  m_parent_barcode      = new std::vector<int>;
  m_parent_prod_ID      = new std::vector<int>;
  m_parent_prod_index   = new std::vector<int>;
  m_parent_prod_x       = new std::vector<float>;
  m_parent_prod_y       = new std::vector<float>;
  m_parent_prod_z       = new std::vector<float>;
  m_parent_prod_r       = new std::vector<float>;
  m_parent_prod_pt      = new std::vector<float>;
  m_parent_prod_eta     = new std::vector<float>;
  m_parent_prod_phi     = new std::vector<float>;
  m_parent_prod_mass    = new std::vector<float>;
  m_parent_prod_nOutP   = new std::vector<int>;
  m_parent_prod_barcode = new std::vector<int>;
  m_outP_ID             = new std::vector<std::vector<int>>;
  m_outP_index          = new std::vector<std::vector<int>>;
  m_outP_pt             = new std::vector<std::vector<float>>;
  m_outP_eta            = new std::vector<std::vector<float>>;
  m_outP_phi            = new std::vector<std::vector<float>>;
  m_outP_E              = new std::vector<std::vector<float>>;
  m_outP_M              = new std::vector<std::vector<float>>;
  m_outP_charge         = new std::vector<std::vector<float>>;
  m_outP_pdgId          = new std::vector<std::vector<int>>;
  m_outP_status         = new std::vector<std::vector<int>>;
  m_outP_barcode        = new std::vector<std::vector<int>>;
  m_outP_isReco         = new std::vector<std::vector<uint8_t>>;
  m_outP_recoProb       = new std::vector<std::vector<float>>;
  m_outP_recoID         = new std::vector<std::vector<int>>;
  m_outP_recoIndex      = new std::vector<std::vector<int>>;
  m_outP_isSelected     = new std::vector<std::vector<uint8_t>>;
  m_outP_isAssociated   = new std::vector<std::vector<uint8_t>>;
  m_outP_isStable       = new std::vector<std::vector<uint8_t>>;
  m_outP_isInteracting  = new std::vector<std::vector<uint8_t>>;
  m_outP_isDark         = new std::vector<std::vector<uint8_t>>;

  // matched to jets
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      m_truthJetMatch          = new std::vector<uint8_t>;
      m_truthJetMatch_ID       = new std::vector<int>;
      m_truthJetMatch_index    = new std::vector<int>;
      m_truthJetMatch_dR       = new std::vector<float>;
      m_darkJetMatch           = new std::vector<uint8_t>;
      m_darkJetMatch_ID        = new std::vector<int>;
      m_darkJetMatch_index     = new std::vector<int>;
      m_darkJetMatch_dR        = new std::vector<float>;
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	m_emtopoJetMatch       = new std::vector<uint8_t>;
	m_emtopoJetMatch_ID    = new std::vector<int>;
	m_emtopoJetMatch_index = new std::vector<int>;
	m_emtopoJetMatch_dR    = new std::vector<float>;
      }
      if ( m_doPFlow  ) {
	m_pflowJetMatch        = new std::vector<uint8_t>;
	m_pflowJetMatch_ID     = new std::vector<int>;
	m_pflowJetMatch_index  = new std::vector<int>;
	m_pflowJetMatch_dR     = new std::vector<float>;
      }
    }
  }
}


TruthVertexContainer :: ~TruthVertexContainer ()
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer()", "deleting" );

  delete m_passSel;
  delete m_llpDecay;
  delete m_ID;
  delete m_index;
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
  delete m_parent_index;
  delete m_parent_pt;
  delete m_parent_eta;
  delete m_parent_phi;
  delete m_parent_E;
  delete m_parent_M;
  delete m_parent_charge;
  delete m_parent_pdgId;
  delete m_parent_status;
  delete m_parent_barcode;
  delete m_parent_prod_ID;
  delete m_parent_prod_index;
  delete m_parent_prod_x;
  delete m_parent_prod_y;
  delete m_parent_prod_z;
  delete m_parent_prod_r;
  delete m_parent_prod_pt;
  delete m_parent_prod_eta;
  delete m_parent_prod_phi;
  delete m_parent_prod_mass;
  delete m_parent_prod_nOutP;
  delete m_parent_prod_barcode;
  delete m_outP_ID;
  delete m_outP_index;
  delete m_outP_pt;
  delete m_outP_eta;
  delete m_outP_phi;
  delete m_outP_E;
  delete m_outP_M;
  delete m_outP_charge;
  delete m_outP_pdgId;
  delete m_outP_status;
  delete m_outP_barcode;
  delete m_outP_isReco;
  delete m_outP_recoProb;
  delete m_outP_recoID;
  delete m_outP_recoIndex;
  delete m_outP_isSelected;
  delete m_outP_isAssociated;
  delete m_outP_isStable;
  delete m_outP_isInteracting;
  delete m_outP_isDark;

  // matched to jets
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      delete m_truthJetMatch;
      delete m_truthJetMatch_ID;
      delete m_truthJetMatch_index;
      delete m_truthJetMatch_dR;
      delete m_darkJetMatch;
      delete m_darkJetMatch_ID;
      delete m_darkJetMatch_index;
      delete m_darkJetMatch_dR;
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	delete m_emtopoJetMatch;
	delete m_emtopoJetMatch_ID;
	delete m_emtopoJetMatch_index;
	delete m_emtopoJetMatch_dR;
      }
      if ( m_doPFlow  ) {
	delete m_pflowJetMatch;
	delete m_pflowJetMatch_ID;
	delete m_pflowJetMatch_index;
	delete m_pflowJetMatch_dR;
      }
    }
  }
}


void TruthVertexContainer :: setTree ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::setTree()", "setting tree" );

  VertexContainer::setTree ( tree );

  connectBranch<uint8_t>              ( tree, "passSel",             &m_passSel             );
  connectBranch<std::string>          ( tree, "llpDecay",            &m_llpDecay            );
  connectBranch<int>                  ( tree, "ID",                  &m_ID                  );
  connectBranch<int>                  ( tree, "index",               &m_index               );
  connectBranch<float>                ( tree, "x",                   &m_x                   );
  connectBranch<float>                ( tree, "y",                   &m_y                   );
  connectBranch<float>                ( tree, "z",                   &m_z                   );
  connectBranch<float>                ( tree, "r",                   &m_r                   );
  connectBranch<float>                ( tree, "pt",                  &m_pt                  );
  connectBranch<float>                ( tree, "eta",                 &m_eta                 );
  connectBranch<float>                ( tree, "phi",                 &m_phi                 );
  connectBranch<float>                ( tree, "mass",                &m_mass                );
  connectBranch<int>                  ( tree, "nOutP",               &m_nOutP               );
  connectBranch<int>                  ( tree, "barcode",             &m_barcode             );
  connectBranch<int>                  ( tree, "parent_ID",           &m_parent_ID           );
  connectBranch<int>                  ( tree, "parent_index",        &m_parent_index        );
  connectBranch<float>                ( tree, "parent_pt",           &m_parent_pt           );
  connectBranch<float>                ( tree, "parent_eta",          &m_parent_eta          );
  connectBranch<float>                ( tree, "parent_phi",          &m_parent_phi          );
  connectBranch<float>                ( tree, "parent_E",            &m_parent_E            );
  connectBranch<float>                ( tree, "parent_M",            &m_parent_M            );
  connectBranch<float>                ( tree, "parent_charge",       &m_parent_charge       );
  connectBranch<int>                  ( tree, "parent_pdgId",        &m_parent_pdgId        );
  connectBranch<int>                  ( tree, "parent_status",       &m_parent_status       );
  connectBranch<int>                  ( tree, "parent_barcode",      &m_parent_barcode      );
  connectBranch<int>                  ( tree, "parent_prod_ID",      &m_parent_prod_ID      );
  connectBranch<int>                  ( tree, "parent_prod_index",   &m_parent_prod_index   );
  connectBranch<float>                ( tree, "parent_prod_x",       &m_parent_prod_x       );
  connectBranch<float>                ( tree, "parent_prod_y",       &m_parent_prod_y       );
  connectBranch<float>                ( tree, "parent_prod_z",       &m_parent_prod_z       );
  connectBranch<float>                ( tree, "parent_prod_r",       &m_parent_prod_r       );
  connectBranch<float>                ( tree, "parent_prod_pt",      &m_parent_prod_pt      );
  connectBranch<float>                ( tree, "parent_prod_eta",     &m_parent_prod_eta     );
  connectBranch<float>                ( tree, "parent_prod_phi",     &m_parent_prod_phi     );
  connectBranch<float>                ( tree, "parent_prod_mass",    &m_parent_prod_mass    );
  connectBranch<int>                  ( tree, "parent_prod_nOutP",   &m_parent_prod_nOutP   );
  connectBranch<int>                  ( tree, "parent_prod_barcode", &m_parent_prod_barcode );
  connectBranch<std::vector<int>>     ( tree, "outP_ID",             &m_outP_ID             );
  connectBranch<std::vector<int>>     ( tree, "outP_index",          &m_outP_index          );
  connectBranch<std::vector<float>>   ( tree, "outP_pt",             &m_outP_pt             );
  connectBranch<std::vector<float>>   ( tree, "outP_eta",            &m_outP_eta            );
  connectBranch<std::vector<float>>   ( tree, "outP_phi",            &m_outP_phi            );
  connectBranch<std::vector<float>>   ( tree, "outP_E",              &m_outP_E              );
  connectBranch<std::vector<float>>   ( tree, "outP_M",              &m_outP_M              );
  connectBranch<std::vector<float>>   ( tree, "outP_charge",         &m_outP_charge         );
  connectBranch<std::vector<int>>     ( tree, "outP_pdgId",          &m_outP_pdgId          );
  connectBranch<std::vector<int>>     ( tree, "outP_status",         &m_outP_status         );
  connectBranch<std::vector<int>>     ( tree, "outP_barcode",        &m_outP_barcode        );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isReco",         &m_outP_isReco         );
  connectBranch<std::vector<float>>   ( tree, "outP_recoProb",       &m_outP_recoProb       );
  connectBranch<std::vector<int>>     ( tree, "outP_recoID",         &m_outP_recoID         );
  connectBranch<std::vector<int>>     ( tree, "outP_recoIndex",      &m_outP_recoIndex      );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isSelected",     &m_outP_isSelected     );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isAssociated",   &m_outP_isAssociated   );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isStable",       &m_outP_isStable       );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isInteracting",  &m_outP_isInteracting  );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isDark",         &m_outP_isDark         );

  // matched to jets
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      connectBranch<uint8_t>   ( tree, "isTruthJetMatched",    &m_truthJetMatch       );
      connectBranch<int>       ( tree, "truthJetMatch_ID",     &m_truthJetMatch_ID    );
      connectBranch<int>       ( tree, "truthJetMatch_index",  &m_truthJetMatch_index );
      connectBranch<float>     ( tree, "truthJetMatch_dR",     &m_truthJetMatch_dR    );
      connectBranch<uint8_t>   ( tree, "isDarkJetMatched",     &m_darkJetMatch        );
      connectBranch<int>       ( tree, "darkJetMatch_ID",      &m_darkJetMatch_ID     );
      connectBranch<int>       ( tree, "darkJetMatch_index",   &m_darkJetMatch_index  );
      connectBranch<float>     ( tree, "darkJetMatch_dR",      &m_darkJetMatch_dR     );
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	connectBranch<uint8_t> ( tree, "isEMTopoJetMatched",   &m_emtopoJetMatch       );
	connectBranch<int>     ( tree, "EMTopoJetMatch_ID",    &m_emtopoJetMatch_ID    );
	connectBranch<int>     ( tree, "EMTopoJetMatch_index", &m_emtopoJetMatch_index );
	connectBranch<float>   ( tree, "EMTopoJetMatch_dR",    &m_emtopoJetMatch_dR    );
      }
      if ( m_doPFlow  ) {
	connectBranch<uint8_t> ( tree, "isPFlowJetMatched",    &m_pflowJetMatch        );
	connectBranch<int>     ( tree, "PFlowJetMatch_ID",     &m_pflowJetMatch_ID     );
	connectBranch<int>     ( tree, "PFlowJetMatch_index",  &m_pflowJetMatch_index  );
	connectBranch<float>   ( tree, "PFlowJetMatch_dR",     &m_pflowJetMatch_dR     );
      }
    }
  }
}


void TruthVertexContainer :: setBranches ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::setBranches()", "setting branches" );

  VertexContainer::setBranches ( tree );

  setBranch<uint8_t>              ( tree, "passSel",             m_passSel             );
  setBranch<std::string>          ( tree, "llpDecay",            m_llpDecay            );
  setBranch<int>                  ( tree, "ID",                  m_ID                  );
  setBranch<int>                  ( tree, "index",               m_index               );
  setBranch<float>                ( tree, "x",                   m_x                   );
  setBranch<float>                ( tree, "y",                   m_y                   );
  setBranch<float>                ( tree, "z",                   m_z                   );
  setBranch<float>                ( tree, "r",                   m_r                   );
  setBranch<float>                ( tree, "pt",                  m_pt                  );
  setBranch<float>                ( tree, "eta",                 m_eta                 );
  setBranch<float>                ( tree, "phi",                 m_phi                 );
  setBranch<float>                ( tree, "mass",                m_mass                );
  setBranch<int>                  ( tree, "nOutP",               m_nOutP               );
  setBranch<int>                  ( tree, "barcode",             m_barcode             );
  setBranch<int>                  ( tree, "parent_ID",           m_parent_ID           );
  setBranch<int>                  ( tree, "parent_index",        m_parent_index        );
  setBranch<float>                ( tree, "parent_pt",           m_parent_pt           );
  setBranch<float>                ( tree, "parent_eta",          m_parent_eta          );
  setBranch<float>                ( tree, "parent_phi",          m_parent_phi          );
  setBranch<float>                ( tree, "parent_E",            m_parent_E            );
  setBranch<float>                ( tree, "parent_M",            m_parent_M            );
  setBranch<float>                ( tree, "parent_charge",       m_parent_charge       );
  setBranch<int>                  ( tree, "parent_pdgId",        m_parent_pdgId        );
  setBranch<int>                  ( tree, "parent_status",       m_parent_status       );
  setBranch<int>                  ( tree, "parent_barcode",      m_parent_barcode      );
  setBranch<int>                  ( tree, "parent_prod_ID",      m_parent_prod_ID      );
  setBranch<int>                  ( tree, "parent_prod_index",   m_parent_prod_index   );
  setBranch<float>                ( tree, "parent_prod_x",       m_parent_prod_x       );
  setBranch<float>                ( tree, "parent_prod_y",       m_parent_prod_y       );
  setBranch<float>                ( tree, "parent_prod_z",       m_parent_prod_z       );
  setBranch<float>                ( tree, "parent_prod_r",       m_parent_prod_r       );
  setBranch<float>                ( tree, "parent_prod_pt",      m_parent_prod_pt      );
  setBranch<float>                ( tree, "parent_prod_eta",     m_parent_prod_eta     );
  setBranch<float>                ( tree, "parent_prod_phi",     m_parent_prod_phi     );
  setBranch<float>                ( tree, "parent_prod_mass",    m_parent_prod_mass    );
  setBranch<int>                  ( tree, "parent_prod_nOutP",   m_parent_prod_nOutP   );
  setBranch<int>                  ( tree, "parent_prod_barcode", m_parent_prod_barcode );
  setBranch<std::vector<int>>     ( tree, "outP_ID",             m_outP_ID             );
  setBranch<std::vector<int>>     ( tree, "outP_index",          m_outP_index          );
  setBranch<std::vector<float>>   ( tree, "outP_pt",             m_outP_pt             );
  setBranch<std::vector<float>>   ( tree, "outP_eta",            m_outP_eta            );
  setBranch<std::vector<float>>   ( tree, "outP_phi",            m_outP_phi            );
  setBranch<std::vector<float>>   ( tree, "outP_E",              m_outP_E              );
  setBranch<std::vector<float>>   ( tree, "outP_M",              m_outP_M              );
  setBranch<std::vector<float>>   ( tree, "outP_charge",         m_outP_charge         );
  setBranch<std::vector<int>>     ( tree, "outP_pdgId",          m_outP_pdgId          );
  setBranch<std::vector<int>>     ( tree, "outP_status",         m_outP_status         );
  setBranch<std::vector<int>>     ( tree, "outP_barcode",        m_outP_barcode        );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isReco",         m_outP_isReco         );
  setBranch<std::vector<float>>   ( tree, "outP_recoProb",       m_outP_recoProb       );
  setBranch<std::vector<int>>     ( tree, "outP_recoID",         m_outP_recoID         );
  setBranch<std::vector<int>>     ( tree, "outP_recoIndex",      m_outP_recoIndex      );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isSelected",     m_outP_isSelected     );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isAssociated",   m_outP_isAssociated   );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isStable",       m_outP_isStable       );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isInteracting",  m_outP_isInteracting  );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isDark",         m_outP_isDark         );

  // matched to jets
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      setBranch<uint8_t>   ( tree, "isTruthJetMatched",    m_truthJetMatch       );
      setBranch<int>       ( tree, "truthJetMatch_ID",     m_truthJetMatch_ID    );
      setBranch<int>       ( tree, "truthJetMatch_index",  m_truthJetMatch_index );
      setBranch<float>     ( tree, "truthJetMatch_dR",     m_truthJetMatch_dR    );
      setBranch<uint8_t>   ( tree, "isDarkJetMatched",     m_darkJetMatch        );
      setBranch<int>       ( tree, "darkJetMatch_ID",      m_darkJetMatch_ID     );
      setBranch<int>       ( tree, "darkJetMatch_index",   m_darkJetMatch_index  );
      setBranch<float>     ( tree, "darkJetMatch_dR",      m_darkJetMatch_dR     );
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	setBranch<uint8_t> ( tree, "isEMTopoJetMatched",   m_emtopoJetMatch       );
	setBranch<int>     ( tree, "EMTopoJetMatch_ID",    m_emtopoJetMatch_ID    );
	setBranch<int>     ( tree, "EMTopoJetMatch_index", m_emtopoJetMatch_index );
	setBranch<float>   ( tree, "EMTopoJetMatch_dR",    m_emtopoJetMatch_dR    );
      }
      if ( m_doPFlow  ) {
	setBranch<uint8_t> ( tree, "isPFlowJetMatched",    m_pflowJetMatch        );
	setBranch<int>     ( tree, "PFlowJetMatch_ID",     m_pflowJetMatch_ID     );
	setBranch<int>     ( tree, "PFlowJetMatch_index",  m_pflowJetMatch_index  );
	setBranch<float>   ( tree, "PFlowJetMatch_dR",     m_pflowJetMatch_dR     );
      }
    }
  }
}


void TruthVertexContainer :: clear ()
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::clear()", "clearing branches" );

  VertexContainer::clear ();

  m_passSel             ->clear();
  m_llpDecay            ->clear();
  m_ID                  ->clear();
  m_index               ->clear();
  m_x                   ->clear();
  m_y                   ->clear();
  m_z                   ->clear();
  m_r                   ->clear();
  m_pt                  ->clear();
  m_eta                 ->clear();
  m_phi                 ->clear();
  m_mass                ->clear();
  m_nOutP               ->clear();
  m_barcode             ->clear();
  m_parent_ID           ->clear();
  m_parent_index        ->clear();
  m_parent_pt           ->clear();
  m_parent_eta          ->clear();
  m_parent_phi          ->clear();
  m_parent_E            ->clear();
  m_parent_M            ->clear();
  m_parent_charge       ->clear();
  m_parent_pdgId        ->clear();
  m_parent_status       ->clear();
  m_parent_barcode      ->clear();
  m_parent_prod_ID      ->clear();
  m_parent_prod_index   ->clear();
  m_parent_prod_x       ->clear();
  m_parent_prod_y       ->clear();
  m_parent_prod_z       ->clear();
  m_parent_prod_r       ->clear();
  m_parent_prod_pt      ->clear();
  m_parent_prod_eta     ->clear();
  m_parent_prod_phi     ->clear();
  m_parent_prod_mass    ->clear();
  m_parent_prod_nOutP   ->clear();
  m_parent_prod_barcode ->clear();
  m_outP_ID             ->clear();
  m_outP_index          ->clear();
  m_outP_pt             ->clear();
  m_outP_eta            ->clear();
  m_outP_phi            ->clear();
  m_outP_E              ->clear();
  m_outP_M              ->clear();
  m_outP_charge         ->clear();
  m_outP_pdgId          ->clear();
  m_outP_status         ->clear();
  m_outP_barcode        ->clear();
  m_outP_isReco         ->clear();
  m_outP_recoProb       ->clear();
  m_outP_recoID         ->clear();
  m_outP_recoIndex      ->clear();
  m_outP_isSelected     ->clear();
  m_outP_isAssociated   ->clear();
  m_outP_isStable       ->clear();
  m_outP_isInteracting  ->clear();
  m_outP_isDark         ->clear();

  // matched to jets
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      m_truthJetMatch          ->clear();
      m_truthJetMatch_ID       ->clear();
      m_truthJetMatch_index    ->clear();
      m_truthJetMatch_dR       ->clear();
      m_darkJetMatch           ->clear();
      m_darkJetMatch_ID        ->clear();
      m_darkJetMatch_index     ->clear();
      m_darkJetMatch_dR        ->clear();
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	m_emtopoJetMatch       ->clear();
	m_emtopoJetMatch_ID    ->clear();
	m_emtopoJetMatch_index ->clear();
	m_emtopoJetMatch_dR    ->clear();
      }
      if ( m_doPFlow  ) {
	m_pflowJetMatch        ->clear();
	m_pflowJetMatch_ID     ->clear();
	m_pflowJetMatch_index  ->clear();
	m_pflowJetMatch_dR     ->clear();
      }
    }
  }
}


void TruthVertexContainer :: FillTruthVertex ( const xAOD::TruthVertex* truthVtx, const std::vector<std::string>& truthVtxLLPs,
					       const std::string treeName )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::FillTruthVertex()", "filling branches" );

  VertexContainer::FillVertex ();
  
  bool passSel = true;
  if ( truthVtx->isAvailable<char>("passSel") )
    if ( !truthVtx->auxdataConst<char>("passSel") )
      passSel = false;
  m_passSel ->push_back( passSel );

  std::string llpDecayType = "";
  for ( size_t i = 0; i != truthVtxLLPs.size(); ++i )
    if ( EJsHelper::pdgIdFuncs[truthVtxLLPs.at(i)]( truthVtx ) ) llpDecayType = truthVtxLLPs.at(i);
  m_llpDecay ->push_back( llpDecayType );

  m_ID      ->push_back( AUXDYN( truthVtx, int, "ID"    ) );
  m_index   ->push_back( AUXDYN( truthVtx, int, "index" ) );
  m_x       ->push_back( truthVtx->x()                    );
  m_y       ->push_back( truthVtx->y()                    );
  m_z       ->push_back( truthVtx->z()                    );
  m_r       ->push_back( truthVtx->perp()                 );
  m_eta     ->push_back( truthVtx->eta()                  );
  m_phi     ->push_back( truthVtx->phi()                  );
  m_nOutP   ->push_back( truthVtx->nOutgoingParticles()   );
  m_barcode ->push_back( truthVtx->barcode()              );

  int   parent_ID      = AlgConsts::invalidInt;
  int   parent_index   = AlgConsts::invalidInt;
  float parent_pt      = AlgConsts::invalidFloat;
  float parent_eta     = AlgConsts::invalidFloat;
  float parent_phi     = AlgConsts::invalidFloat;
  float parent_E       = AlgConsts::invalidFloat;
  float parent_M       = AlgConsts::invalidFloat;
  float parent_charge  = AlgConsts::invalidFloat;
  float parent_pdgId   = AlgConsts::invalidInt;
  int   parent_status  = AlgConsts::invalidInt;
  int   parent_barcode = AlgConsts::invalidInt;

  int   pProd_ID      = AlgConsts::invalidInt;
  int   pProd_index   = AlgConsts::invalidInt;
  float pProd_x       = AlgConsts::invalidFloat;
  float pProd_y       = AlgConsts::invalidFloat;
  float pProd_z       = AlgConsts::invalidFloat;
  float pProd_r       = AlgConsts::invalidFloat;
  float pProd_pt      = AlgConsts::invalidFloat;
  float pProd_eta     = AlgConsts::invalidFloat;
  float pProd_phi     = AlgConsts::invalidFloat;
  float pProd_mass    = AlgConsts::invalidFloat;
  int   pProd_nOutP   = AlgConsts::invalidInt;
  int   pProd_barcode = AlgConsts::invalidInt;
  
  const auto* parent = truthVtx->incomingParticle(0);
  if ( parent ) {
    parent_ID      = AUXDYN( parent, int, "ID"    );
    parent_index   = AUXDYN( parent, int, "index" );
    parent_pt      = parent->pt() / m_units;
    parent_eta     = parent->eta();
    parent_phi     = parent->phi();
    parent_E       = parent->e()  / m_units;
    parent_M       = parent->m()  / m_units;
    parent_charge  = parent->charge();
    parent_pdgId   = parent->pdgId();
    parent_status  = parent->status();
    parent_barcode = parent->barcode();

    const auto* prodVtx = parent->prodVtx();
    std::vector<const xAOD::TruthParticle*> pProd_outParts;
    if ( prodVtx ) {
      pProd_ID      = AUXDYN( prodVtx, int, "ID"    );
      pProd_index   = AUXDYN( prodVtx, int, "index" );
      pProd_x       = prodVtx->x();
      pProd_y       = prodVtx->y();
      pProd_z       = prodVtx->z();
      pProd_r       = prodVtx->perp();
      pProd_eta     = prodVtx->eta();
      pProd_phi     = prodVtx->phi();
      pProd_nOutP   = prodVtx->nOutgoingParticles();
      pProd_barcode = prodVtx->barcode();

      for ( size_t i = 0; i != prodVtx->nOutgoingParticles(); ++i ) {
	const auto* pProd_outP = prodVtx->outgoingParticle(i);
	if ( !pProd_outP ) continue;
	pProd_outParts .push_back( pProd_outP );
      }
      const TLorentzVector& pProd_sumP4 = EJsHelper::truthSumP4 ( pProd_outParts );
      pProd_pt   = pProd_sumP4.Pt() / m_units;
      pProd_mass = pProd_sumP4.M()  / m_units;
    }
  }

  m_parent_ID      ->push_back( parent_ID      );
  m_parent_index   ->push_back( parent_index   );
  m_parent_pt      ->push_back( parent_pt      );
  m_parent_eta     ->push_back( parent_eta     );
  m_parent_phi     ->push_back( parent_phi     );
  m_parent_E       ->push_back( parent_E       );
  m_parent_M       ->push_back( parent_M       );
  m_parent_charge  ->push_back( parent_charge  );
  m_parent_pdgId   ->push_back( parent_pdgId   );
  m_parent_status  ->push_back( parent_status  );
  m_parent_barcode ->push_back( parent_barcode );

  m_parent_prod_ID      ->push_back( pProd_ID      );
  m_parent_prod_index   ->push_back( pProd_index   );
  m_parent_prod_x       ->push_back( pProd_x       );
  m_parent_prod_y       ->push_back( pProd_y       );
  m_parent_prod_z       ->push_back( pProd_z       );
  m_parent_prod_r       ->push_back( pProd_r       );
  m_parent_prod_pt      ->push_back( pProd_pt      );
  m_parent_prod_eta     ->push_back( pProd_eta     );
  m_parent_prod_phi     ->push_back( pProd_phi     );
  m_parent_prod_mass    ->push_back( pProd_mass    );
  m_parent_prod_nOutP   ->push_back( pProd_nOutP   );
  m_parent_prod_barcode ->push_back( pProd_barcode );

  std::vector<const xAOD::TruthParticle*> outParts;
  
  std::vector<int>     outP_ID;
  std::vector<int>     outP_index;
  std::vector<float>   outP_pt;
  std::vector<float>   outP_eta;
  std::vector<float>   outP_phi;
  std::vector<float>   outP_E;
  std::vector<float>   outP_M;
  std::vector<float>   outP_charge;
  std::vector<int>     outP_pdgId;
  std::vector<int>     outP_status;
  std::vector<int>     outP_barcode;
  std::vector<uint8_t> outP_isReco;
  std::vector<float>   outP_recoProb;
  std::vector<int>     outP_recoID;
  std::vector<int>     outP_recoIndex;
  std::vector<uint8_t> outP_isSelected;
  std::vector<uint8_t> outP_isAssociated;
  std::vector<uint8_t> outP_isStable;
  std::vector<uint8_t> outP_isInteracting;
  std::vector<uint8_t> outP_isDark;
  
  for ( size_t i = 0; i != truthVtx->nOutgoingParticles(); ++i ) {
    const auto* outP = truthVtx->outgoingParticle(i);
    if ( !outP )        continue;
    outParts            .push_back( outP                                           );
    outP_ID             .push_back( AUXDYN( outP, int, "ID"                      ) );
    outP_index          .push_back( AUXDYN( outP, int, "index"                   ) );
    outP_pt             .push_back( outP->pt() / m_units                           );
    outP_eta            .push_back( outP->eta()                                    );
    outP_phi            .push_back( outP->phi()                                    );
    outP_E              .push_back( outP->e()  / m_units                           );
    outP_M              .push_back( outP->m()  / m_units                           );
    outP_charge         .push_back( outP->charge()                                 );
    outP_pdgId          .push_back( outP->pdgId()                                  );
    outP_status         .push_back( outP->status()                                 );
    outP_barcode        .push_back( outP->barcode()                                );
    outP_isReco         .push_back( AUXDYN( outP, char,  "isTrackMatch"          ) ); // CHANGE IMPL
    outP_recoProb       .push_back( AUXDYN( outP, float, "trackMatchProbability" ) ); // CHANGE IMPL
    outP_isStable       .push_back( EJsHelper::isStable      ( outP              ) );
    outP_isInteracting  .push_back( EJsHelper::isInteracting ( outP              ) );
    outP_isDark         .push_back( EJsHelper::isDark        ( outP              ) );
    // get linked track
    int     recoID      = AlgConsts::invalidInt;
    int     recoIndex   = AlgConsts::invalidInt;
    uint8_t recoIsSel   = AlgConsts::invalidUnsigned;
    uint8_t recoIsAssoc = AlgConsts::invalidUnsigned;
    static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> recoAccess("trackLink");
    if ( recoAccess.isAvailable( *outP ) ) {
      try {
	const EJsHelper::TrackLink_t& recoLink = recoAccess( *outP );
	recoID      = AUXDYN( (*recoLink), int,  "ID"            );
	recoIndex   = AUXDYN( (*recoLink), int,  "index"         );
	recoIsSel   = AUXDYN( (*recoLink), char, "is_selected"   );
	recoIsAssoc = AUXDYN( (*recoLink), char, "is_associated" );
      } catch(...){}
    }
    outP_recoID       .push_back( recoID      );
    outP_recoIndex    .push_back( recoIndex   );
    outP_isSelected   .push_back( recoIsSel   );
    outP_isAssociated .push_back( recoIsAssoc );
  }

  const TLorentzVector& sumP4 = EJsHelper::truthSumP4 ( outParts );
  m_pt   ->push_back( sumP4.Pt() / m_units );
  m_mass ->push_back( sumP4.M()  / m_units );

  m_outP_ID            ->push_back( outP_ID            );
  m_outP_index         ->push_back( outP_index         );
  m_outP_pt            ->push_back( outP_pt            );
  m_outP_eta           ->push_back( outP_eta           );
  m_outP_phi           ->push_back( outP_phi           );
  m_outP_E             ->push_back( outP_E             );
  m_outP_M             ->push_back( outP_M             );
  m_outP_charge        ->push_back( outP_charge        );
  m_outP_pdgId         ->push_back( outP_pdgId         );
  m_outP_status        ->push_back( outP_status        );
  m_outP_barcode       ->push_back( outP_barcode       );
  m_outP_isReco        ->push_back( outP_isReco        );
  m_outP_recoProb      ->push_back( outP_recoProb      );
  m_outP_recoID        ->push_back( outP_recoID        );
  m_outP_recoIndex     ->push_back( outP_recoIndex     );
  m_outP_isSelected    ->push_back( outP_isSelected    );
  m_outP_isAssociated  ->push_back( outP_isAssociated  );
  m_outP_isStable      ->push_back( outP_isStable      );
  m_outP_isInteracting ->push_back( outP_isInteracting );
  m_outP_isDark        ->push_back( outP_isDark        );


  // jet matching (jets to which DVs are dR-matched)
  if ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_recoJetMatched || m_infoSwitch.m_truthJetMatched ) {
    std::string jet_str = treeName;
    if ( treeName == "nominal" ) jet_str = "";
    uint8_t isTruthJetMatch  = false;
    if ( truthVtx->isAvailable<char>("isMatchedToTruthJet") )
      isTruthJetMatch  = truthVtx->auxdataConst<char>("isMatchedToTruthJet");
    uint8_t isDarkJetMatch   = false;
    if ( truthVtx->isAvailable<char>("isMatchedToDarkJet")  )
      isDarkJetMatch   = truthVtx->auxdataConst<char>("isMatchedToDarkJet");
    uint8_t isEMTopoJetMatch = false;
    std::string emtopo_str   = "";
    if ( truthVtx->isAvailable<char>("isMatchedToRecoJet_EMTopo" + jet_str) ) {
      isEMTopoJetMatch = truthVtx->auxdataConst<char>("isMatchedToRecoJet_EMTopo" + jet_str);
      emtopo_str       = jet_str;
    }
    else if ( truthVtx->isAvailable<char>("isMatchedToRecoJet_EMTopo") )
      isEMTopoJetMatch = truthVtx->auxdataConst<char>("isMatchedToRecoJet_EMTopo");
    uint8_t isPFlowJetMatch  = false;
    std::string pflow_str    = "";
    if ( truthVtx->isAvailable<char>("isMatchedToRecoJet_PFlow" + jet_str) ) {
      isPFlowJetMatch  = truthVtx->auxdataConst<char>("isMatchedToRecoJet_PFlow" + jet_str);
      pflow_str        = jet_str;
    }
    else if ( truthVtx->isAvailable<char>("isMatchedToRecoJet_PFlow") )
      isPFlowJetMatch  = truthVtx->auxdataConst<char>("isMatchedToRecoJet_PFlow");

    if ( ( m_infoSwitch.m_jetMatched || m_infoSwitch.m_truthJetMatched ) && m_mc ) {
      m_truthJetMatch          ->push_back( isTruthJetMatch                               );
      m_truthJetMatch_ID       ->push_back( AUXDYN( truthVtx, int,   "truthJetMatchID"    ) );
      m_truthJetMatch_index    ->push_back( AUXDYN( truthVtx, int,   "truthJetMatchIndex" ) );
      m_truthJetMatch_dR       ->push_back( AUXDYN( truthVtx, float, "truthJetMatchDR"    ) );
      m_darkJetMatch           ->push_back( isDarkJetMatch                                );
      m_darkJetMatch_ID        ->push_back( AUXDYN( truthVtx, int,   "darkJetMatchID"     ) );
      m_darkJetMatch_index     ->push_back( AUXDYN( truthVtx, int,   "darkJetMatchIndex"  ) );
      m_darkJetMatch_dR        ->push_back( AUXDYN( truthVtx, float, "darkJetMatchDR"     ) );
    }
    if ( m_infoSwitch.m_jetMatched   || m_infoSwitch.m_recoJetMatched  ) {
      if ( m_doEMTopo ) {
	m_emtopoJetMatch       ->push_back( isEMTopoJetMatch                                                 );
	m_emtopoJetMatch_ID    ->push_back( AUXDYN( truthVtx, int,   "recoJetMatchID_EMTopo"    + emtopo_str ) );
	m_emtopoJetMatch_index ->push_back( AUXDYN( truthVtx, int,   "recoJetMatchIndex_EMTopo" + emtopo_str ) );
	m_emtopoJetMatch_dR    ->push_back( AUXDYN( truthVtx, float, "recoJetMatchDR_EMTopo"    + emtopo_str ) );
      }
      if ( m_doPFlow  ) {
	m_pflowJetMatch        ->push_back( isPFlowJetMatch                                                  );
	m_pflowJetMatch_ID     ->push_back( AUXDYN( truthVtx, int,   "recoJetMatchID_PFlow"     + pflow_str  ) );
	m_pflowJetMatch_index  ->push_back( AUXDYN( truthVtx, int,   "recoJetMatchIndex_PFlow"  + pflow_str  ) );
	m_pflowJetMatch_dR     ->push_back( AUXDYN( truthVtx, float, "recoJetMatchDR_PFlow"     + pflow_str  ) );
      }
    }   
  }
}
