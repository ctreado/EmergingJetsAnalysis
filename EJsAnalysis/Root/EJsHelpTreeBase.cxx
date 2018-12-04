#include "EJsAnalysis/EJsHelpTreeBase.h"


using namespace asg::msgUserCode;


EJsHelpTreeBase :: EJsHelpTreeBase ( xAOD::TEvent* event, TTree* tree, TFile* file,
				     const float units, bool debug, xAOD::TStore* store ) :
  HelpTreeBase ( event, tree, file, units, debug, store )
{
  ANA_MSG_DEBUG( "Creating output EJs TTree" );
}

EJsHelpTreeBase :: ~EJsHelpTreeBase() {}


void EJsHelpTreeBase::AddJetsUser ( const std::string detailStr, const std::string jetName )
{
  ANA_MSG_DEBUG( "Adding EJsAnalysis-specific jet branches" );

  m_tree->Branch( (jetName + "_jet_exists").c_str(), &b_jet_exists );
  
}


void EJsHelpTreeBase::FillJetsUser ( const xAOD::Jet*, const std::string jetName )
{
  ANA_MSG_DEBUG( "Filling EJsAnalysis-specific jet branches" );

  b_jet_exists->push_back(1);
}


void EJsHelpTreeBase::ClearJetsUser ( const std::string jetName )
{
  ANA_MSG_DEBUG( "Clearing EJsAnalysis-specific jet branches" );

  b_jet_exists->clear();

}
