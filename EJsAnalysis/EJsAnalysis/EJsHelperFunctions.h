#ifndef EJsAnalysis_EJsHelperFunctions_H
#define EJsAnalysis_EJsHelperFunctions_H

/* EJsHelperFunctions is a set of generic helper functions for EJsAnalysis,
   not already provided in xAODAnaHelpers's HelperFunctions */

#include <cmath>
#include <vector>
#include <map>
#include <set>

#include <TTree.h>

#include <AthLinks/ElementLink.h>

#include <xAODJet/JetContainer.h>
#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>
#include <xAODTruth/TruthParticleContainer.h>
#include <xAODTruth/TruthVertexContainer.h>

class TLorentzVector;

namespace EJsHelper {

  // --------------- generic helper functions --------------- //

  // element link typedefs
  typedef ElementLink<xAOD::JetContainer>                        JetLink_t;
  typedef ElementLink<xAOD::TrackParticleContainer>              TrackLink_t;
  typedef ElementLink<xAOD::VertexContainer>                     VertexLink_t;
  typedef ElementLink<xAOD::TruthParticleContainer>              TruthParticleLink_t;
  typedef ElementLink<xAOD::TruthVertexContainer>                TruthVertexLink_t;
  typedef std::vector<ElementLink<xAOD::JetContainer>>           JetLinkVector_t;
  typedef std::vector<ElementLink<xAOD::TrackParticleContainer>> TrackLinkVector_t;
  typedef std::vector<ElementLink<xAOD::VertexContainer>>        VertexLinkVector_t;
  typedef std::vector<ElementLink<xAOD::TruthParticleContainer>> TruthParticleLinkVector_t;
  typedef std::vector<ElementLink<xAOD::TruthVertexContainer>>   TruthVertexLinkVector_t;

  // returns dPhi in [-pi, pi] range
  double deltaPhi ( const double&, const double& );

  // returns dR b/w two objects
  double deltaR ( const double&, const double&, const double&, const double& );

  // returns vector of all tracks
  void getAllTracks      ( const xAOD::Vertex*, std::vector<const xAOD::TrackParticle*>& );
  // returns vector of decorated clean tracks
  void getCleanTracks    ( const xAOD::Vertex*, std::vector<const xAOD::TrackParticle*>& );
  // returns vector of decorated filtered tracks
  void getFilteredTracks ( const xAOD::Vertex*, std::vector<const xAOD::TrackParticle*>& );

  // branch connectors
  template <typename T_BR> void connectBranch ( TTree* tree, std::string name, T_BR* variable )
    {
      tree ->SetBranchStatus  ( name.c_str(), 1        );
      tree ->SetBranchAddress ( name.c_str(), variable );
    }
  template <typename T_BR> void connectBranchVec ( TTree* tree, std::string name, std::vector<T_BR>** variable )
    {
      tree->SetBranchStatus  ( name.c_str(),        1 );
      tree->SetBranchAddress ( name.c_str(), variable );
    }


  
  // --------------- region info --------------- //

  // region enums
  enum RegionType { ALL, SEARCH_MINUS_ONE, SEARCH, SIGNAL, VALIDATION };
  // region structures
  struct Region {
    std::string name;
    RegionType  type;
  };
  // fills region structure info given input string
  void fillRegion ( Region&, const std::string );


  // --------------- dv type info --------------- //

  // base dv enums
  enum BaseDVType { BARE, CLEAN, FILTERED, TRIMMED };
  // base dv structures
  struct BaseDV {
    std::string name;
    BaseDVType  type;
  };
  // fills base dv structure info given input string
  void fillBaseDV ( BaseDV&, const std::string );


  
  // --------------- truth helper functions (some taken from VsiPerf/VsiTruthHelper) --------------- //

  // particle decay truth vertex selectors
  bool selectDarkPion ( const xAOD::TruthVertex* );
  bool selectKshort   ( const xAOD::TruthVertex* );
  
  extern std::map<std::string, bool (*) ( const xAOD::TruthVertex* )> pdgIdFuncs;

  // look for (reconstructible) descendants in (LLP) decay chain

  // returns (parent) truth particle corresponding to track
  const xAOD::TruthParticle* getTruthPart       ( const xAOD::TrackParticle* );
  const xAOD::TruthParticle* getParentTruthPart ( const xAOD::TrackParticle* );

  // returns production vertex of (parent) truth particle corresponding to track
  const xAOD::TruthVertex* getProdVtx       ( const xAOD::TrackParticle* );
  const xAOD::TruthVertex* getParentProdVtx ( const xAOD::TrackParticle* );

  // returns truth vertex sum four-vector momentum of outgoing particles
  TLorentzVector truthSumP4 ( const std::set<    const xAOD::TruthParticle* >& );
  TLorentzVector truthSumP4 ( const std::vector< const xAOD::TruthParticle* >& );
  TLorentzVector truthSumP4 ( const std::vector< TLorentzVector >&             );

  // is truth particle stable / interacting / reconstructible / dark ?
  bool isStable          ( const xAOD::TruthParticle* );
  bool isInteracting     ( const xAOD::TruthParticle* );
  bool isDark            ( const xAOD::TruthParticle* );
  
}

# endif // EJsAnalysis_EJsHelperFunctions_H
