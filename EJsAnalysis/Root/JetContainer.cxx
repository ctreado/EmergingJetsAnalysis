#include "EJsAnalysis/JetContainer.h"
#include "EJsAnalysis/EJsHelperFunctions.h"

using namespace EJs;

JetContainer :: JetContainer ( const std::string& name, const std::string& detailStr, float units, bool mc ) :
  xAH::JetContainer ( name, detailStr, units, mc )
{
  if ( m_debug ) Info( "EJs::JetContainer()", "setting up" );

  m_ID     = new std::vector<int>;
  m_radius = new std::vector<float>;

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

  m_truthVtx_isDarkPionDecay                  = new std::vector<std::vector<uint8_t>>;
  m_truthVtx_ID                               = new std::vector<std::vector<int>>;
  m_truthVtx_barcode                          = new std::vector<std::vector<int>>;
  m_truthVtx_dR                               = new std::vector<std::vector<float>>;
  m_secVtx_ID                                 = new std::vector<std::vector<int>>;
  m_secVtx_dR                                 = new std::vector<std::vector<float>>;
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

  m_tp_ID            = new std::vector<std::vector<int>>;
  m_tp_barcode       = new std::vector<std::vector<int>>;
  m_tp_pid           = new std::vector<std::vector<int>>;
  m_tp_isReco        = new std::vector<std::vector<uint8_t>>;
  m_tp_recoProb      = new std::vector<std::vector<float>>;
  m_tp_recoID        = new std::vector<std::vector<int>>;
  m_tp_dR            = new std::vector<std::vector<float>>;
  m_trk_ID           = new std::vector<std::vector<int>>;
  m_trk_isTruth      = new std::vector<std::vector<uint8_t>>;
  m_trk_truthProb    = new std::vector<std::vector<float>>;
  m_trk_truthID      = new std::vector<std::vector<int>>;
  m_trk_truthBarcode = new std::vector<std::vector<int>>;
  m_trk_truthPid     = new std::vector<std::vector<int>>;
  m_trk_dR           = new std::vector<std::vector<float>>;

  m_constit_E   = new std::vector<std::vector<float>>;
  m_constit_pt  = new std::vector<std::vector<float>>;
  m_constit_eta = new std::vector<std::vector<float>>;
  m_constit_phi = new std::vector<std::vector<float>>;
}


JetContainer :: ~JetContainer ()
{
  if ( m_debug ) Info( "EJs::JetContainer()", "deleting" );

  delete m_ID;
  delete m_radius;

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

  delete m_truthVtx_isDarkPionDecay;
  delete m_truthVtx_ID;
  delete m_truthVtx_barcode;
  delete m_truthVtx_dR;
  delete m_secVtx_ID;
  delete m_secVtx_dR;
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

  delete m_tp_ID;
  delete m_tp_barcode;
  delete m_tp_pid;
  delete m_tp_isReco;
  delete m_tp_recoProb;
  delete m_tp_recoID;
  delete m_tp_dR;
  delete m_trk_ID;
  delete m_trk_isTruth;
  delete m_trk_truthProb;
  delete m_trk_truthID;
  delete m_trk_truthBarcode;
  delete m_trk_truthPid;
  delete m_trk_dR;

  delete m_constit_E;
  delete m_constit_pt;
  delete m_constit_eta;
  delete m_constit_phi;
}


void JetContainer :: setTree ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::JetContainer::setTree()", "setting tree" );

  connectBranch<int>   ( tree, "ID",     &m_ID     );
  connectBranch<float> ( tree, "radius", &m_radius );

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

  connectBranch<std::vector<uint8_t>> ( tree, "truthVtx_isDarkPionDecay",                  &m_truthVtx_isDarkPionDecay                  );
  connectBranch<std::vector<int>>     ( tree, "truthVtx_ID",                               &m_truthVtx_ID                               );
  connectBranch<std::vector<int>>     ( tree, "truthVtx_barcode",                          &m_truthVtx_barcode                          );
  connectBranch<std::vector<float>>   ( tree, "truthVtx_dR",                               &m_truthVtx_dR                               );
  connectBranch<std::vector<int>>     ( tree, "secVtx_ID",                                 &m_secVtx_ID                                 );
  connectBranch<std::vector<float>>   ( tree, "secVtx_dR",                                 &m_secVtx_dR                                 );
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

  connectBranch<std::vector<int>>     ( tree, "tp_ID",            &m_tp_ID            );
  connectBranch<std::vector<int>>     ( tree, "tp_barcode",       &m_tp_barcode       );
  connectBranch<std::vector<int>>     ( tree, "tp_pid",           &m_tp_pid           );
  connectBranch<std::vector<uint8_t>> ( tree, "tp_isReco",        &m_tp_isReco        );
  connectBranch<std::vector<float>>   ( tree, "tp_recoProb",      &m_tp_recoProb      );
  connectBranch<std::vector<int>>     ( tree, "tp_recoID",        &m_tp_recoID        );
  connectBranch<std::vector<float>>   ( tree, "tp_dR",            &m_tp_dR            );
  connectBranch<std::vector<int>>     ( tree, "trk_ID",           &m_trk_ID           );
  connectBranch<std::vector<uint8_t>> ( tree, "trk_isTruth",      &m_trk_isTruth      );
  connectBranch<std::vector<float>>   ( tree, "trk_truthProb",    &m_trk_truthProb    );
  connectBranch<std::vector<int>>     ( tree, "trk_truthID",      &m_trk_truthID      );
  connectBranch<std::vector<int>>     ( tree, "trk_truthBarcode", &m_trk_truthBarcode );
  connectBranch<std::vector<int>>     ( tree, "trk_truthPid",     &m_trk_truthPid     );
  connectBranch<std::vector<float>>   ( tree, "trk_dR",           &m_trk_dR           );
  
  connectBranch<std::vector<float>> ( tree, "constit_E",   &m_constit_E );
  connectBranch<std::vector<float>> ( tree, "constit_pt",  &m_constit_pt );
  connectBranch<std::vector<float>> ( tree, "constit_eta", &m_constit_eta );
  connectBranch<std::vector<float>> ( tree, "constit_phi", &m_constit_phi );
}


void JetContainer :: setBranches ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::JetContainer::setBranches()", "setting branches" );

  setBranch<int>   ( tree, "ID", m_ID );
  setBranch<float> ( tree, "radius", m_radius );

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

  setBranch<std::vector<uint8_t>> ( tree, "truthVtx_isDarkPionDecay",                  m_truthVtx_isDarkPionDecay                  );
  setBranch<std::vector<int>>     ( tree, "truthVtx_ID",                               m_truthVtx_ID                               );
  setBranch<std::vector<int>>     ( tree, "truthVtx_barcode",                          m_truthVtx_barcode                          );
  setBranch<std::vector<float>>   ( tree, "truthVtx_dR",                               m_truthVtx_dR                               );
  setBranch<std::vector<int>>     ( tree, "secVtx_ID",                                 m_secVtx_ID                                 );
  setBranch<std::vector<float>>   ( tree, "secVtx_dR",                                 m_secVtx_dR                                 );
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

  setBranch<std::vector<int>>     ( tree, "tp_ID",            m_tp_ID            );
  setBranch<std::vector<int>>     ( tree, "tp_barcode",       m_tp_barcode       );
  setBranch<std::vector<int>>     ( tree, "tp_pid",           m_tp_pid           );
  setBranch<std::vector<uint8_t>> ( tree, "tp_isReco",        m_tp_isReco        );
  setBranch<std::vector<float>>   ( tree, "tp_recoProb",      m_tp_recoProb      );
  setBranch<std::vector<int>>     ( tree, "tp_recoID",        m_tp_recoID        );
  setBranch<std::vector<float>>   ( tree, "tp_dR",            m_tp_dR            );
  setBranch<std::vector<int>>     ( tree, "trk_ID",           m_trk_ID           );
  setBranch<std::vector<uint8_t>> ( tree, "trk_isTruth",      m_trk_isTruth      );
  setBranch<std::vector<float>>   ( tree, "trk_truthProb",    m_trk_truthProb    );
  setBranch<std::vector<int>>     ( tree, "trk_truthID",      m_trk_truthID      );
  setBranch<std::vector<int>>     ( tree, "trk_truthBarcode", m_trk_truthBarcode );
  setBranch<std::vector<int>>     ( tree, "trk_truthPid",     m_trk_truthPid     );
  setBranch<std::vector<float>>   ( tree, "trk_dR",           m_trk_dR           );

  setBranch<std::vector<float>> ( tree, "constit_E",   m_constit_E );
  setBranch<std::vector<float>> ( tree, "constit_pt",  m_constit_pt );
  setBranch<std::vector<float>> ( tree, "constit_eta", m_constit_eta );
  setBranch<std::vector<float>> ( tree, "constit_phi", m_constit_phi );
}


void JetContainer :: clear ( )
{
  if ( m_debug ) Info( "EJs::JetContainer::clear()", "clearing branches" );

  m_ID     ->clear();
  m_radius ->clear();

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

  m_truthVtx_isDarkPionDecay                  ->clear();
  m_truthVtx_ID                               ->clear();
  m_truthVtx_barcode                          ->clear();
  m_truthVtx_dR                               ->clear();
  m_secVtx_ID                                 ->clear();
  m_secVtx_dR                                 ->clear();
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

  m_tp_ID            ->clear();
  m_tp_barcode       ->clear();
  m_tp_pid           ->clear();
  m_tp_isReco        ->clear();
  m_tp_recoProb      ->clear();
  m_tp_recoID        ->clear();
  m_tp_dR            ->clear();
  m_trk_ID           ->clear();
  m_trk_isTruth      ->clear();
  m_trk_truthProb    ->clear();
  m_trk_truthID      ->clear();
  m_trk_truthBarcode ->clear();
  m_trk_truthPid     ->clear();
  m_trk_dR           ->clear();

  m_constit_E   ->clear();
  m_constit_pt  ->clear();
  m_constit_eta ->clear();
  m_constit_phi ->clear();
}


void JetContainer :: FillJet ( const xAOD::Jet* jet )
{
  if ( m_debug ) Info( "EJs::JetContainer::FillJet()", "filling branches" );

  m_ID     ->push_back( AUXDYN( jet, int, "ID" ) );
  m_radius ->push_back( jet->getSizeParameter()  );

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

  
  std::vector<uint8_t> matchTV_isPid;
  std::vector<int>     matchTV_ID;
  std::vector<int>     matchTV_BC;
  std::vector<int>     matchDV_ID;
  std::vector<uint8_t> matchDV_closeTV_isPid;
  std::vector<int>     matchDV_closeTV_ID;
  std::vector<int>     matchDV_closeTV_BC;
  std::vector<float>   matchDV_closeTV_dist;
  std::vector<uint8_t> matchDV_maxTV_isPid;
  std::vector<int>     matchDV_maxTV_ID;
  std::vector<int>     matchDV_maxTV_BC;
  std::vector<float>   matchDV_maxTV_score;
  std::vector<uint8_t> matchDV_maxPTV_isPid;
  std::vector<int>     matchDV_maxPTV_ID;
  std::vector<int>     matchDV_maxPTV_BC;
  std::vector<float>   matchDV_maxPTV_score;
  
  // access matched truth vertex links
  static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLinkVector_t> matchTVAccess("matchedTruthVertexLinks");
  if ( matchTVAccess.isAvailable( *jet ) ) {
    const EJsHelper::TruthVertexLinkVector_t& matchTVLinks = matchTVAccess( *jet );
    // loop over matched truth vertex links
    for ( const auto& tvlink : matchTVLinks ) {
      if ( !tvlink.isValid() ) continue;
      matchTV_isPid .push_back( EJsHelper::selectDarkPion( (*tvlink) ) );
      matchTV_ID    .push_back( AUXDYN( (*tvlink), int, "ID" )         );
      matchTV_BC    .push_back( (*tvlink)->barcode()                   );
    }
  }
   
  // access matched secondary vertex links
  static SG::AuxElement::ConstAccessor<EJsHelper::VertexLinkVector_t> matchDVAccess("matchedSecondaryVertexLinks");
  if ( matchDVAccess.isAvailable( *jet ) ) {
    const EJsHelper::VertexLinkVector_t& matchDVLinks = matchDVAccess( *jet );
    
    // loop over matched secondary vertex links
    for ( const auto& dvlink : matchDVLinks ) {
      if ( !dvlink.isValid() ) continue;
      matchDV_ID .push_back( AUXDYN( (*dvlink), int, "ID" ) );
      
      // get closest TV link
      static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLink_t> closeTVAccess("closestTruthVertexLink");
      if ( closeTVAccess.isAvailable( **dvlink ) ) {
	try {
	  const EJsHelper::TruthVertexLink_t& closeTVLink = closeTVAccess( **dvlink );
	  matchDV_closeTV_isPid .push_back( EJsHelper::selectDarkPion( (*closeTVLink) ) );
	  matchDV_closeTV_ID    .push_back( AUXDYN( (*closeTVLink), int, "ID" )         );
	  matchDV_closeTV_BC    .push_back( (*closeTVLink)->barcode()                   );
	} catch(...) {}
      }
      matchDV_closeTV_dist .push_back( AUXDYN( (*dvlink), double, "closestTruthVertex_dist" ) );

      // get max-linked TV link
      static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLink_t> maxTVAccess("maxlinkedTruthVertexLink");
      if ( maxTVAccess.isAvailable( **dvlink ) ) {
	try {
	  const EJsHelper::TruthVertexLink_t& maxTVLink = maxTVAccess( **dvlink );
	  matchDV_maxTV_isPid .push_back( EJsHelper::selectDarkPion( (*maxTVLink) ) );
	  matchDV_maxTV_ID    .push_back( AUXDYN( (*maxTVLink), int, "ID" )         );
	  matchDV_maxTV_BC    .push_back( (*maxTVLink)->barcode()                   );
	} catch(...) {}
      }
      matchDV_maxTV_score .push_back( AUXDYN( (*dvlink), double, "maxlinkedTruthVertex_score" ) );

      // get max-linked PTV link
      static SG::AuxElement::ConstAccessor<EJsHelper::TruthVertexLink_t> maxPTVAccess("maxlinkedParentTruthVertexLink");
      if ( maxPTVAccess.isAvailable( **dvlink ) ) {
	try {
	  const EJsHelper::TruthVertexLink_t& maxPTVLink = maxPTVAccess( **dvlink );
	  matchDV_maxPTV_isPid .push_back( EJsHelper::selectDarkPion( (*maxPTVLink ) ) );
	  matchDV_maxPTV_ID    .push_back( AUXDYN( (*maxPTVLink), int, "ID" )          );
	  matchDV_maxPTV_BC    .push_back( (*maxPTVLink)->barcode()                    );
	} catch(...) {}
      }
      matchDV_maxPTV_score .push_back( AUXDYN( (*dvlink), double, "maxlinkedParentTruthVertex_score" ) );
      
    } // end loop over matched DV links
    
  } // end matched secondary vertex link access

  m_truthVtx_isDarkPionDecay                  ->push_back( matchTV_isPid                                        );
  m_truthVtx_ID                               ->push_back( matchTV_ID                                           );
  m_truthVtx_barcode                          ->push_back( matchTV_BC                                           );
  m_truthVtx_dR                               ->push_back( AUXDYNVEC( jet, float, "matchedTruthVertex_dR"     ) );
  m_secVtx_ID                                 ->push_back( matchDV_ID                                           );
  m_secVtx_dR                                 ->push_back( AUXDYNVEC( jet, float, "matchedSecondaryVertex_dR" ) );
  m_secVtx_closestTruth_isDarkPionDecay       ->push_back( matchDV_closeTV_isPid                                );
  m_secVtx_closestTruth_ID                    ->push_back( matchDV_closeTV_ID                                   );
  m_secVtx_closestTruth_barcode               ->push_back( matchDV_closeTV_BC                                   );
  m_secVtx_closestTruth_distance              ->push_back( matchDV_closeTV_dist                                 );
  m_secVtx_maxlinkTruth_isDarkPionDecay       ->push_back( matchDV_maxTV_isPid                                  );
  m_secVtx_maxlinkTruth_ID                    ->push_back( matchDV_maxTV_ID                                     );
  m_secVtx_maxlinkTruth_barcode               ->push_back( matchDV_maxTV_BC                                     );
  m_secVtx_maxlinkTruth_score                 ->push_back( matchDV_maxTV_score                                  );
  m_secVtx_maxlinkParentTruth_isDarkPionDecay ->push_back( matchDV_maxPTV_isPid                                 );
  m_secVtx_maxlinkParentTruth_ID              ->push_back( matchDV_maxPTV_ID                                    );
  m_secVtx_maxlinkParentTruth_barcode         ->push_back( matchDV_maxPTV_BC                                    );
  m_secVtx_maxlinkParentTruth_score           ->push_back( matchDV_maxPTV_score                                 );


  std::vector<int>     tp_ID;
  std::vector<int>     tp_BC;
  std::vector<int>     tp_PID;
  std::vector<uint8_t> tp_isReco;
  std::vector<float>   tp_recoProb;
  std::vector<int>     tp_recoID;
  std::vector<int>     trk_ID;
  std::vector<uint8_t> trk_isTruth;
  std::vector<float>   trk_truthProb;
  std::vector<int>     trk_truthID;
  std::vector<int>     trk_truthBC;
  std::vector<int>     trk_truthPID;
  
  // access matched truth particle links
  static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLinkVector_t> tpAccess("matchedTruthParticleLinks");
  if ( tpAccess.isAvailable( *jet ) ) {
    const EJsHelper::TruthParticleLinkVector_t& tpLinks = tpAccess( *jet );
    
    // loop over matched truth particle links
    for ( const auto& tplink : tpLinks ) {
      if ( !tplink.isValid() ) continue;
      tp_ID  .push_back( AUXDYN( (*tplink), int, "ID" ) );
      tp_BC  .push_back( (*tplink)->barcode()           );
      tp_PID .push_back( (*tplink)->pdgId()             );

      // get linked reco particle (track)
      static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> recoAccess("trackLink");
      if ( recoAccess.isAvailable( **tplink ) ) {
	try {
	  const EJsHelper::TrackLink_t& recoLink = recoAccess( **tplink );
	  tp_recoID .push_back( AUXDYN( (*recoLink), int, "ID" ) );
	} catch(...) {}
      }
      tp_isReco   .push_back( AUXDYN( (*tplink), char,   "isTrackMatch"          ) );
      tp_recoProb .push_back( AUXDYN( (*tplink), double, "trackMatchProbability" ) );
  
    } // end loop over matched truth links
    
  } // end matched truth link access

  // access matched track links
  static SG::AuxElement::ConstAccessor<EJsHelper::TrackLinkVector_t> trkAccess("matchedTrackLinks");
  if ( trkAccess.isAvailable( *jet ) ) {
    const EJsHelper::TrackLinkVector_t& trkLinks = trkAccess( *jet );
    
    // loop over matched track links
    for ( const auto& trklink : trkLinks ) {
      if ( !trklink.isValid() ) continue;
      trk_ID .push_back( AUXDYN( (*trklink), int, "ID" ) );
      
      // get linked truth particle
      bool trackHasTruthLink = false;
      static SG::AuxElement::ConstAccessor<EJsHelper::TruthParticleLink_t> truthAccess("truthParticleLink");
      if ( truthAccess.isAvailable( **trklink ) ) {
	try {
	  const EJsHelper::TruthParticleLink_t& truthLink = truthAccess( **trklink );
	  if ( (*truthLink) ) trackHasTruthLink = true;
	  trk_truthID   .push_back( AUXDYN( (*truthLink), int, "ID" )                        );
	  trk_truthBC   .push_back( (*truthLink)->barcode()                                  );
	  trk_truthPID  .push_back( (*truthLink)->pdgId()                                    );
	} catch(...) {}
      }
      trk_isTruth   .push_back( trackHasTruthLink );
      trk_truthProb .push_back( (*trklink)->auxdataConst<float>("truthMatchProbability") );
      
    } // end loop over matched track links
    
  } // end matched track link access

  m_tp_ID            ->push_back( tp_ID                                              );
  m_tp_barcode       ->push_back( tp_BC                                              );
  m_tp_pid           ->push_back( tp_PID                                             );
  m_tp_isReco        ->push_back( tp_isReco                                          );
  m_tp_recoProb      ->push_back( tp_recoProb                                        );
  m_tp_recoID        ->push_back( tp_recoID                                          );
  m_tp_dR            ->push_back( AUXDYNVEC( jet, float, "matchedTruthParticle_dR" ) );
  m_trk_ID           ->push_back( trk_ID                                             );
  m_trk_isTruth      ->push_back( trk_isTruth                                        );
  m_trk_truthProb    ->push_back( trk_truthProb                                      );
  m_trk_truthID      ->push_back( trk_truthID                                        );
  m_trk_truthBarcode ->push_back( trk_truthBC                                        );
  m_trk_truthPid     ->push_back( trk_truthPID                                       );
  m_trk_dR           ->push_back( AUXDYNVEC( jet, float, "matchedTrack_dR"         ) );

  
  std::vector<float> constit_E;
  std::vector<float> constit_pt;
  std::vector<float> constit_eta;
  std::vector<float> constit_phi;
  
  // access constituents
  xAOD::JetConstituentVector jcv = jet->getConstituents();
  if ( jcv.isValid() ) {
    for ( const auto& jconstit : jcv ) {
      constit_E   .push_back( jconstit->e() / m_units );
      constit_pt  .push_back( jconstit->pt() / m_units );
      constit_eta .push_back( jconstit->eta() );
      constit_phi .push_back( jconstit->phi() );
    }
  }

  m_constit_E   ->push_back( constit_E );
  m_constit_pt  ->push_back( constit_pt );
  m_constit_eta ->push_back( constit_eta );
  m_constit_phi ->push_back( constit_phi );
}
