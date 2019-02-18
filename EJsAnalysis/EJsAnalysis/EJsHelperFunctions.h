#ifndef EJsAnalysis_EJsHelperFunctions_H
#define EJsAnalysis_EJsHelperFunctions_H

/* EJsHelperFunctions is a set of generic helper functions for EJsAnalysis,
   not already provided in xAODAnaHelpers's HelperFunctions */

#include <cmath>
#include <vector>

#include <AthLinks/ElementLink.h>

#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/VertexContainer.h>
#include <xAODTruth/TruthParticleContainer.h>
#include <xAODTruth/TruthVertexContainer.h>

namespace EJsHelper {

  // --- generic helper functions --- //
  
  // returns dPhi in [-pi, pi] range
  double deltaPhi ( const double&, const double& );

  // returns dR b/w two objects
  double deltaR ( const double&, const double&, const double&, const double& );

  // element link typedefs
  typedef ElementLink<xAOD::TrackParticleContainer> TrackLink_t;
  typedef ElementLink<xAOD::VertexContainer> VertexLink_t;
  typedef ElementLink<xAOD::TruthParticleContainer> TruthParticleLink_t;
  typedef ElementLink<xAOD::TruthVertexContainer> TruthVertexLink_t;
  typedef std::vector<ElementLink<xAOD::TrackParticleContainer>> TrackLinkVector_t;
  typedef std::vector<ElementLink<xAOD::VertexContainer>> VertexLinkVector_t;
  typedef std::vector<ElementLink<xAOD::TruthParticleContainer>> TruthParticleLinkVector_t;
  typedef std::vector<ElementLink<xAOD::TruthVertexContainer>> TruthVertexLinkVector_t;


  // --- truth helper functions (taken from VsiPerf/VsiTruthHelper) --- //

  // selects specified particle decay truth vertices
  bool selectDarkPion ( const xAOD::TruthVertex* );
  // other TVs for validation ??

  // look for (reconstructible) descendants in (LLP) decay chain

  // returns (parent) truth particle corresponding to track
  const xAOD::TruthParticle* getTruthPart       ( const xAOD::TrackParticle* );
  const xAOD::TruthParticle* getParentTruthPart ( const xAOD::TrackParticle* );

  // returns production vertex of (parent) truth particle corresponding to track
  const xAOD::TruthVertex* getProdVtx       ( const xAOD::TrackParticle* );
  const xAOD::TruthVertex* getParentProdVtx ( const xAOD::TrackParticle* );
  
}

# endif // EJsAnalysis_EJsHelperFunctions_H
