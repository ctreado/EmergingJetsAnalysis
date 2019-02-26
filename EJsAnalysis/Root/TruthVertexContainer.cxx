#include <xAODTruth/TruthVertex.h>
#include <xAODTruth/TruthParticle.h>

#include "EJsAnalysis/TruthVertexContainer.h"
#include "EJsAnalysis/AlgConsts.h"
#include "EJsAnalysis/EJsHelperFunctions.h"

using namespace EJs;

TruthVertexContainer :: TruthVertexContainer ( const std::string& name, const std::string& detailStr, float units ) :
  VertexContainer ( name, detailStr, units )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer()", "setting up" );

  m_isDarkPionDecay     = new std::vector<uint8_t>;
  m_ID                  = new std::vector<int>;
  m_barcode             = new std::vector<int>;
  m_x                   = new std::vector<float>;
  m_y                   = new std::vector<float>;
  m_z                   = new std::vector<float>;
  m_r                   = new std::vector<float>;
  m_eta                 = new std::vector<float>;
  m_phi                 = new std::vector<float>;
  m_parent_ID           = new std::vector<int>;
  m_parent_barcode      = new std::vector<int>;
  m_parent_pt           = new std::vector<float>;
  m_parent_eta          = new std::vector<float>;
  m_parent_phi          = new std::vector<float>;
  m_parent_charge       = new std::vector<float>;
  m_parent_pid          = new std::vector<int>;
  m_parent_prod_ID      = new std::vector<int>;
  m_parent_prod_barcode = new std::vector<int>;
  m_parent_prod_x       = new std::vector<float>;
  m_parent_prod_y       = new std::vector<float>;
  m_parent_prod_z       = new std::vector<float>;
  m_parent_prod_r       = new std::vector<float>;
  m_parent_prod_eta     = new std::vector<float>;
  m_parent_prod_phi     = new std::vector<float>;
  m_outP_ID             = new std::vector<std::vector<int>>;
  m_outP_barcode        = new std::vector<std::vector<int>>;
  m_outP_pt             = new std::vector<std::vector<float>>;
  m_outP_eta            = new std::vector<std::vector<float>>;
  m_outP_phi            = new std::vector<std::vector<float>>;
  m_outP_charge         = new std::vector<std::vector<float>>;
  m_outP_pid            = new std::vector<std::vector<int>>;
  m_outP_isReco         = new std::vector<std::vector<uint8_t>>;
  m_outP_recoProb       = new std::vector<std::vector<float>>;
}


TruthVertexContainer :: ~TruthVertexContainer ()
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer()", "deleting" );

  delete m_isDarkPionDecay;
  delete m_ID;
  delete m_barcode;
  delete m_x;
  delete m_y;
  delete m_z;
  delete m_r;
  delete m_eta;
  delete m_phi;
  delete m_parent_ID;
  delete m_parent_barcode;
  delete m_parent_pt;
  delete m_parent_eta;
  delete m_parent_phi;
  delete m_parent_charge;
  delete m_parent_pid;
  delete m_parent_prod_ID;
  delete m_parent_prod_barcode;
  delete m_parent_prod_x;
  delete m_parent_prod_y;
  delete m_parent_prod_z;
  delete m_parent_prod_r;
  delete m_parent_prod_eta;
  delete m_parent_prod_phi;
  delete m_outP_ID;
  delete m_outP_barcode;
  delete m_outP_pt;
  delete m_outP_eta;
  delete m_outP_phi;
  delete m_outP_charge;
  delete m_outP_pid;
  delete m_outP_isReco;
  delete m_outP_recoProb;
}


void TruthVertexContainer :: setTree ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::setTree()", "setting tree" );
  
  VertexContainer::setTree ( tree );

  connectBranch<uint8_t>              ( tree, "isDarkPionDecay",     &m_isDarkPionDecay     );
  connectBranch<int>                  ( tree, "ID",                  &m_ID                  );
  connectBranch<int>                  ( tree, "barcode",             &m_barcode             );
  connectBranch<float>                ( tree, "x",                   &m_x                   );
  connectBranch<float>                ( tree, "y",                   &m_y                   );
  connectBranch<float>                ( tree, "z",                   &m_z                   );
  connectBranch<float>                ( tree, "r",                   &m_r                   );
  connectBranch<float>                ( tree, "eta",                 &m_eta                 );
  connectBranch<float>                ( tree, "phi",                 &m_phi                 );
  connectBranch<int>                  ( tree, "parent_ID",           &m_parent_ID           );
  connectBranch<int>                  ( tree, "parent_barcode",      &m_parent_barcode      );
  connectBranch<float>                ( tree, "parent_pt",           &m_parent_pt           );
  connectBranch<float>                ( tree, "parent_eta",          &m_parent_eta          );
  connectBranch<float>                ( tree, "parent_phi",          &m_parent_phi          );
  connectBranch<float>                ( tree, "parent_charge",       &m_parent_charge       );
  connectBranch<int>                  ( tree, "parent_pid",          &m_parent_pid          );
  connectBranch<int>                  ( tree, "parent_prod_ID",      &m_parent_prod_ID      );
  connectBranch<int>                  ( tree, "parent_prod_barcode", &m_parent_prod_barcode );
  connectBranch<float>                ( tree, "parent_prod_x",       &m_parent_prod_x       );
  connectBranch<float>                ( tree, "parent_prod_y",       &m_parent_prod_y       );
  connectBranch<float>                ( tree, "parent_prod_z",       &m_parent_prod_z       );
  connectBranch<float>                ( tree, "parent_prod_r",       &m_parent_prod_r       );
  connectBranch<float>                ( tree, "parent_prod_eta",     &m_parent_prod_eta     );
  connectBranch<float>                ( tree, "parent_prod_phi",     &m_parent_prod_phi     );
  connectBranch<std::vector<int>>     ( tree, "outP_ID",             &m_outP_ID             );
  connectBranch<std::vector<int>>     ( tree, "outP_barcode",        &m_outP_barcode        );
  connectBranch<std::vector<float>>   ( tree, "outP_pt",             &m_outP_pt             );
  connectBranch<std::vector<float>>   ( tree, "outP_eta",            &m_outP_eta            );
  connectBranch<std::vector<float>>   ( tree, "outP_phi",            &m_outP_phi            );
  connectBranch<std::vector<float>>   ( tree, "outP_charge",         &m_outP_charge         );
  connectBranch<std::vector<int>>     ( tree, "outP_pid",            &m_outP_pid            );
  connectBranch<std::vector<uint8_t>> ( tree, "outP_isReco",         &m_outP_isReco         );
  connectBranch<std::vector<float>>   ( tree, "outP_recoProb",       &m_outP_recoProb       );
}


void TruthVertexContainer :: setBranches ( TTree* tree )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::setBranches()", "setting branches" );
  
  VertexContainer::setBranches ( tree );

  setBranch<uint8_t>              ( tree, "isDarkPionDecay",     m_isDarkPionDecay     );
  setBranch<int>                  ( tree, "ID",                  m_ID                  );
  setBranch<int>                  ( tree, "barcode",             m_barcode             );
  setBranch<float>                ( tree, "x",                   m_x                   );
  setBranch<float>                ( tree, "y",                   m_y                   );
  setBranch<float>                ( tree, "z",                   m_z                   );
  setBranch<float>                ( tree, "r",                   m_r                   );
  setBranch<float>                ( tree, "eta",                 m_eta                 );
  setBranch<float>                ( tree, "phi",                 m_phi                 );
  setBranch<int>                  ( tree, "parent_ID",           m_parent_ID           );
  setBranch<int>                  ( tree, "parent_barcode",      m_parent_barcode      );
  setBranch<float>                ( tree, "parent_pt",           m_parent_pt           );
  setBranch<float>                ( tree, "parent_eta",          m_parent_eta          );
  setBranch<float>                ( tree, "parent_phi",          m_parent_phi          );
  setBranch<float>                ( tree, "parent_charge",       m_parent_charge       );
  setBranch<int>                  ( tree, "parent_pid",          m_parent_pid          );
  setBranch<int>                  ( tree, "parent_prod_ID",      m_parent_prod_ID      );
  setBranch<int>                  ( tree, "parent_prod_barcode", m_parent_prod_barcode );
  setBranch<float>                ( tree, "parent_prod_x",       m_parent_prod_x       );
  setBranch<float>                ( tree, "parent_prod_y",       m_parent_prod_y       );
  setBranch<float>                ( tree, "parent_prod_z",       m_parent_prod_z       );
  setBranch<float>                ( tree, "parent_prod_r",       m_parent_prod_r       );
  setBranch<float>                ( tree, "parent_prod_eta",     m_parent_prod_eta     );
  setBranch<float>                ( tree, "parent_prod_phi",     m_parent_prod_phi     );
  setBranch<std::vector<int>>     ( tree, "outP_ID",             m_outP_ID             );
  setBranch<std::vector<int>>     ( tree, "outP_barcode",        m_outP_barcode        );
  setBranch<std::vector<float>>   ( tree, "outP_pt",             m_outP_pt             );
  setBranch<std::vector<float>>   ( tree, "outP_eta",            m_outP_eta            );
  setBranch<std::vector<float>>   ( tree, "outP_phi",            m_outP_phi            );
  setBranch<std::vector<float>>   ( tree, "outP_charge",         m_outP_charge         );
  setBranch<std::vector<int>>     ( tree, "outP_pid",            m_outP_pid            );
  setBranch<std::vector<uint8_t>> ( tree, "outP_isReco",         m_outP_isReco         );
  setBranch<std::vector<float>>   ( tree, "outP_recoProb",       m_outP_recoProb       );
}


void TruthVertexContainer :: clear ()
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::clear()", "clearing branches" );
  
  VertexContainer::clear ();

  m_isDarkPionDecay     ->clear();
  m_ID                  ->clear();
  m_barcode             ->clear();
  m_x                   ->clear();
  m_y                   ->clear();
  m_z                   ->clear();
  m_r                   ->clear();
  m_eta                 ->clear();
  m_phi                 ->clear();
  m_parent_ID           ->clear();
  m_parent_barcode      ->clear();
  m_parent_pt           ->clear();
  m_parent_eta          ->clear();
  m_parent_phi          ->clear();
  m_parent_charge       ->clear();
  m_parent_pid          ->clear();
  m_parent_prod_ID      ->clear();
  m_parent_prod_barcode ->clear();
  m_parent_prod_x       ->clear();
  m_parent_prod_y       ->clear();
  m_parent_prod_z       ->clear();
  m_parent_prod_r       ->clear();
  m_parent_prod_eta     ->clear();
  m_parent_prod_phi     ->clear();
  m_outP_ID             ->clear();
  m_outP_barcode        ->clear();
  m_outP_pt             ->clear();
  m_outP_eta            ->clear();
  m_outP_phi            ->clear();
  m_outP_charge         ->clear();
  m_outP_pid            ->clear();
  m_outP_isReco         ->clear();
  m_outP_recoProb       ->clear();
}


void TruthVertexContainer :: FillTruthVertex ( const xAOD::TruthVertex* truthVtx )
{
  if ( m_debug ) Info( "EJs::TruthVertexContainer::FillTruthVertex()", "filling branches" );
  
  VertexContainer::FillVertex ();

  m_isDarkPionDecay ->push_back( EJsHelper::selectDarkPion( truthVtx ) );

  m_ID      ->push_back( AUXDYN( truthVtx, int, "ID" ) );
  m_barcode ->push_back( truthVtx->barcode()           );
  m_x       ->push_back( truthVtx->x()                 );
  m_y       ->push_back( truthVtx->y()                 );
  m_z       ->push_back( truthVtx->z()                 );
  m_r       ->push_back( truthVtx->perp()              );
  m_eta     ->push_back( truthVtx->eta()               );
  m_phi     ->push_back( truthVtx->phi()               );

  int   parent_ID      = AlgConsts::invalidInt;
  int   parent_barcode = AlgConsts::invalidInt;
  float parent_pt      = AlgConsts::invalidFloat;
  float parent_eta     = AlgConsts::invalidFloat;
  float parent_phi     = AlgConsts::invalidFloat;
  float parent_charge  = AlgConsts::invalidFloat;
  float parent_pid     = AlgConsts::invalidInt;

  int   pProd_ID      = AlgConsts::invalidInt;
  int   pProd_barcode = AlgConsts::invalidInt;
  float pProd_x       = AlgConsts::invalidFloat;
  float pProd_y       = AlgConsts::invalidFloat;
  float pProd_z       = AlgConsts::invalidFloat;
  float pProd_r       = AlgConsts::invalidFloat;
  float pProd_eta     = AlgConsts::invalidFloat;
  float pProd_phi     = AlgConsts::invalidFloat;
  
  const auto* parent = truthVtx->incomingParticle(0);
  if ( parent ) {
    parent_ID      = AUXDYN( parent, int, "ID" );
    parent_barcode = parent->barcode();
    parent_pt      = parent->pt() / m_units;
    parent_eta     = parent->eta();
    parent_phi     = parent->phi();
    parent_charge  = parent->charge();
    parent_pid     = parent->pdgId();

    const auto* prodVtx = parent->prodVtx();
    if ( prodVtx ) {
      pProd_ID      = AUXDYN( prodVtx, int, "ID" );
      pProd_barcode = prodVtx->barcode();
      pProd_x       = prodVtx->x();
      pProd_y       = prodVtx->y();
      pProd_z       = prodVtx->z();
      pProd_r       = prodVtx->perp();
      pProd_eta     = prodVtx->eta();
      pProd_phi     = prodVtx->phi();
    }
  }

  m_parent_ID      ->push_back( parent_ID      );
  m_parent_barcode ->push_back( parent_barcode );
  m_parent_pt      ->push_back( parent_pt      );
  m_parent_eta     ->push_back( parent_eta     );
  m_parent_phi     ->push_back( parent_phi     );
  m_parent_charge  ->push_back( parent_charge  );
  m_parent_pid     ->push_back( parent_pid     );

  m_parent_prod_ID      ->push_back( pProd_ID      );
  m_parent_prod_barcode ->push_back( pProd_barcode );
  m_parent_prod_x       ->push_back( pProd_x       );
  m_parent_prod_y       ->push_back( pProd_y       );
  m_parent_prod_z       ->push_back( pProd_z       );
  m_parent_prod_r       ->push_back( pProd_r       );
  m_parent_prod_eta     ->push_back( pProd_eta     );
  m_parent_prod_phi     ->push_back( pProd_phi     );

  std::vector<int>     outP_ID;
  std::vector<int>     outP_barcode;
  std::vector<float>   outP_pt;
  std::vector<float>   outP_eta;
  std::vector<float>   outP_phi;
  std::vector<float>   outP_charge;
  std::vector<int>     outP_pid;
  std::vector<uint8_t> outP_isReco;
  std::vector<float>   outP_recoProb;
  
  for ( size_t i = 0; i != truthVtx->nOutgoingParticles(); ++i ) {
    const auto* outP = truthVtx->outgoingParticle(i);
    if ( !outP )           continue;
    outP_ID      .push_back( AUXDYN( outP, int, "ID" ) );
    outP_barcode .push_back( outP->barcode()           );
    outP_pt      .push_back( outP->pt() / m_units      );
    outP_eta     .push_back( outP->eta()               );
    outP_phi     .push_back( outP->phi()               );
    outP_charge  .push_back( outP->charge()            );
    outP_pid     .push_back( outP->pdgId()             );
    if ( outP->isAvailable<char>("isTrkMatch") )
      outP_isReco   .push_back( outP->auxdataConst<char>("isTrkMatch")     );
    if ( outP->isAvailable<double>("trkMatchProb") )
      outP_recoProb .push_back( outP->auxdataConst<double>("trkMatchProb") );
  }

  m_outP_ID       ->push_back( outP_ID       );
  m_outP_barcode  ->push_back( outP_barcode  );
  m_outP_pt       ->push_back( outP_pt       );
  m_outP_eta      ->push_back( outP_eta      );
  m_outP_phi      ->push_back( outP_phi      );
  m_outP_charge   ->push_back( outP_charge   );
  m_outP_pid      ->push_back( outP_pid      );
  m_outP_isReco   ->push_back( outP_isReco   );
  m_outP_recoProb ->push_back( outP_recoProb ); 
}
