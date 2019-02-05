#include "EJsAnalysis/EJsHelperFunctions.h"

namespace EJsHelper {

  // ------------------------------------------------------------------------------------------ //
  
  double deltaPhi ( const double& phi1, const double& phi2 )
  {
    return -remainder( -phi1 + phi2, 2*M_PI );
  }

  double deltaR ( const double& eta1, const double& eta2, const double& phi1, const double& phi2 )
  {
    double dEta = eta1 - eta2;
    double dPhi = deltaPhi( phi1, phi2 );
    double dR = sqrt( pow( dEta, 2 ) + pow( dPhi, 2 ) );

    return dR;
  }

  // ------------------------------------------------------------------------------------------ //

  bool selectDarkPion ( const xAOD::TruthVertex* truthVtx )
  {
    if ( truthVtx->perp() < 0.1 )                               return false;
    if ( truthVtx->nIncomingParticles() != 1 )                  return false;
    auto& links = truthVtx->incomingParticleLinks();
    if ( links.size() != 1 )                                    return false;
    if ( !links.at(0).isValid() )                               return false;
    if ( truthVtx->incomingParticle(0)->absPdgId() != 4900111 ) return false;

    // if we made it this far, truth vertex is a dark pion decay...
    return true;
  }
  
  const xAOD::TruthParticle* getTruthPart ( const xAOD::TrackParticle* trk )
  {
    const xAOD::TruthParticle* tp = 0;
    static SG::AuxElement::ConstAccessor<TruthParticleLink_t> tpAccess("truthParticleLink");
    if ( !tpAccess.isAvailable( *trk ) ) return tp;
    try {
      const TruthParticleLink_t& tpLink = tpAccess( *trk );
      tp = *tpLink;
    } catch(...) {}
    return tp;
  }

  const xAOD::TruthParticle* getParentTruthPart ( const xAOD::TrackParticle* trk )
  {
    const xAOD::TruthParticle* tp = getTruthPart( trk );
    if ( !tp ) return nullptr;
    return tp->parent(0);
  }

  const xAOD::TruthVertex* getProdVtx ( const xAOD::TrackParticle* trk )
  {
    const xAOD::TruthParticle* tp = getTruthPart( trk );
    if ( !tp ) return nullptr;
    return tp->prodVtx();
  }

  const xAOD::TruthVertex* getParentProdVtx ( const xAOD::TrackParticle* trk )
  {
    const xAOD::TruthParticle* tp = getParentTruthPart( trk );
    if ( !tp ) return nullptr;
    return tp->prodVtx();
  }

  // ------------------------------------------------------------------------------------------ //
  
} // namespace EJsHelper
