#include <xAODAnaHelpers/HelperFunctions.h>

#include "EJsAnalysis/EJsHistogramManager.h"


EJsHistogramManager :: EJsHistogramManager ( std::string name, std::string detailStr ) :
  HistogramManager ( name, detailStr )
{
  m_debug = false;

  if ( m_debug ) Info( "EJsHistogramManager()", "setting up" );

  m_secVtx_x             = new std::vector<float>;
  m_secVtx_y             = new std::vector<float>;
  m_secVtx_z             = new std::vector<float>;
  m_secVtx_r             = new std::vector<float>;
  m_secVtx_pt            = new std::vector<float>;
  m_secVtx_eta           = new std::vector<float>;
  m_secVtx_phi           = new std::vector<float>;
  m_secVtx_mass          = new std::vector<float>;
  m_secVtx_mass_nonAssoc = new std::vector<float>;
}


EJsHistogramManager :: ~EJsHistogramManager ()
{
  if ( m_debug ) Info( "EJsHistogramManager()", "deleting" );

  delete m_secVtx_x;
  delete m_secVtx_y;
  delete m_secVtx_z;
  delete m_secVtx_r;
  delete m_secVtx_pt;
  delete m_secVtx_eta;
  delete m_secVtx_phi;
  delete m_secVtx_mass;
  delete m_secVtx_mass_nonAssoc;
}



StatusCode EJsHistogramManager :: connectSecVerts ( TTree* tree, const std::string secVtxName,
						    const std::string secVtxDetailStr )
{
  if ( m_debug ) Info( "EJsHistogramManager::connectSecVerts()",
		       "connecting secondary vertex branches" );

  // create info switch instance
  m_secVtxInfoSwitch = new EJsHelperClasses::SecondaryVertexInfoSwitch( secVtxDetailStr );

  std::string name = secVtxName;
  
  tree->SetBranchStatus  ( ("n"+name).c_str(), 1           );
  tree->SetBranchAddress ( ("n"+name).c_str(), &m_secVtx_n );

  using namespace HelperFunctions;
  connectBranch<float> ( name, tree, "x",             &m_secVtx_x             );
  connectBranch<float> ( name, tree, "y",             &m_secVtx_y             );
  connectBranch<float> ( name, tree, "z",             &m_secVtx_z             );
  connectBranch<float> ( name, tree, "r",             &m_secVtx_r             );
  connectBranch<float> ( name, tree, "pt",            &m_secVtx_pt            );
  connectBranch<float> ( name, tree, "eta",           &m_secVtx_eta           );
  connectBranch<float> ( name, tree, "phi",           &m_secVtx_phi           );
  connectBranch<float> ( name, tree, "mass",          &m_secVtx_mass          );
  connectBranch<float> ( name, tree, "mass_nonAssoc", &m_secVtx_mass_nonAssoc );

  
  //if ( m_secVtxInfoSwitch->m_tracks ) std::cout << "info switch works" << std::endl;

  // delete info switch instance
  delete m_secVtxInfoSwitch;

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: initialize ( const std::string secVtxDetailStr )
{
  if ( m_debug ) Info( "EJsHistogramManger::initialize()", "booking histograms" );

  // create info switch instances
  m_secVtxInfoSwitch = new EJsHelperClasses::SecondaryVertexInfoSwitch( secVtxDetailStr );

  
  // book histograms -- use info switches
  // ... see if we can parse detailStr (maybe with range of indices) to separate
  // info switches by corresponding object type

  h_secVtx_n             = book( m_name, "secVtx_n",             "n secondary vertices",                   10,     0,   10 );
  h_secVtx_x             = book( m_name, "secVtx_x",             "secondary vertex x-pos [mm]",           100, -1000, 1000 );
  h_secVtx_y             = book( m_name, "secVtx_y",             "secondary vertex y-pos [mm]",           100, -1000, 1000 );
  h_secVtx_z             = book( m_name, "secVtx_z",             "secondary vertex z-pos [mm]",           100, -1500, 1500 );
  h_secVtx_r             = book( m_name, "secVtx_r",             "secondary vertex r-pos [mm]",           100,     0, 1000 );
  h_secVtx_pt            = book( m_name, "secVtx_pt",            "secondary vertex p_{T} [GeV]",          100,     0,  100 );
  h_secVtx_eta           = book( m_name, "secVtx_eta",           "secondary vertex eta",                  100,    -5,    5 );
  h_secVtx_phi           = book( m_name, "secVtx_phi",           "secondary vertex phi",                  100,  -3.5,  3.5 );
  h_secVtx_mass          = book( m_name, "secVtx_mass",          "secondary vertex mass [GeV]",           100,     0,   50 );
  h_secVtx_mass_nonAssoc = book( m_name, "secVtx_mass_nonAssoc", "secondary vertex non-assoc mass [GeV]", 100,     0,   50 );

  
  // delete info switch instances
  delete m_secVtxInfoSwitch;

  return StatusCode::SUCCESS;
}



StatusCode EJsHistogramManager :: execute ( TTree* tree, Long64_t treeEntry,
					    const std::string secVtxDetailStr )
{
  if ( m_debug ) Info( "EJsHistogramManager::execute()", "filling histograms" );

  // create info switch instances
  m_secVtxInfoSwitch = new EJsHelperClasses::SecondaryVertexInfoSwitch( secVtxDetailStr );

  // fill histograms -- use info switches

  tree->GetEntry( treeEntry );

  h_secVtx_n->Fill( m_secVtx_n );
  
  for ( size_t i = 0; i != m_secVtx_x->size(); ++i ) {
    h_secVtx_x             ->Fill( m_secVtx_x->at(i)             );
    h_secVtx_y             ->Fill( m_secVtx_y->at(i)             );
    h_secVtx_z             ->Fill( m_secVtx_z->at(i)             );
    h_secVtx_r             ->Fill( m_secVtx_r->at(i)             );
    h_secVtx_pt            ->Fill( m_secVtx_pt->at(i)            );
    h_secVtx_eta           ->Fill( m_secVtx_eta->at(i)           );
    h_secVtx_phi           ->Fill( m_secVtx_phi->at(i)           );
    h_secVtx_mass          ->Fill( m_secVtx_mass->at(i)          );
    h_secVtx_mass_nonAssoc ->Fill( m_secVtx_mass_nonAssoc->at(i) );
  }

  // delete info switch instances
  delete m_secVtxInfoSwitch;

  return StatusCode::SUCCESS;
}
