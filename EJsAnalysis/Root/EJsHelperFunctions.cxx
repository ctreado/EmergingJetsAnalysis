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

  void getAllTracks ( const xAOD::Vertex* vtx, std::vector<const xAOD::TrackParticle*>& allTrks )
  {
    for ( size_t itrk = 0; itrk != vtx->nTrackParticles(); ++itrk ) {
      const auto* trk = vtx->trackParticle(itrk);
      allTrks.push_back( trk );
    }
  }
  
  void getCleanTracks ( const xAOD::Vertex* vtx, std::vector<const xAOD::TrackParticle*>& cleanTrks )
  {
    for ( size_t itrk = 0; itrk != vtx->nTrackParticles(); ++itrk ) {
      const auto* trk = vtx->trackParticle(itrk);
      bool trk_isClean = true;
      if ( trk->isAvailable<char>("isClean") ) trk_isClean = trk->auxdataConst<char>("isClean");
      if ( trk_isClean )                       cleanTrks.push_back( trk );
    }
  }
  
  void getFilteredTracks ( const xAOD::Vertex* vtx, std::vector<const xAOD::TrackParticle*>& filtTrks )
  {
    for ( size_t itrk = 0; itrk != vtx->nTrackParticles(); ++itrk ) {
      const auto* trk = vtx->trackParticle(itrk);
      bool trk_isFilt = true;
      if ( trk->isAvailable<char>("isFiltered") ) trk_isFilt = trk->auxdataConst<char>("isFiltered");
      if ( trk_isFilt )                           filtTrks.push_back( trk );
    }
  }

  // ------------------------------------------------------------------------------------------ //

  void fillRegion ( Region& region, const std::string region_name )
  {
    std::string     regionName = region_name;
    enum RegionType regionType;
    if      ( regionName == "search-minus-one" || regionName == "srch-1"   ) regionType = SEARCH_MINUS_ONE;
    else if ( regionName == "search"           || regionName == "srch"     ) regionType = SEARCH;
    else if ( regionName == "signal"           || regionName == "sgnl"     ) regionType = SIGNAL;
    else if ( regionName == "validation"       || regionName == "valid"    ) regionType = VALIDATION;
    else {
      regionName = "all";
      regionType = ALL; // default
    }

    region .name = regionName;
    region .type = regionType;
  }

  // ------------------------------------------------------------------------------------------ //

  void fillBaseDV ( BaseDV& baseDV, const std::string baseDV_name )
  {
    std::string     baseDVName = baseDV_name;
    enum BaseDVType baseDVType;
    if      ( baseDVName == "clean"                            ) baseDVType = CLEAN;
    else if ( baseDVName == "filtered" || baseDVName == "filt" ) baseDVType = FILTERED;
    else if ( baseDVName == "trimmed"  || baseDVName == "trim" ) baseDVType = TRIMMED;
    else {
      baseDVName = "bare";
      baseDVType = BARE; // default
    }

    baseDV .name = baseDVName;
    baseDV .type = baseDVType;
  }
  
  // ------------------------------------------------------------------------------------------ //

  std::map<std::string, bool (*) ( const xAOD::TruthVertex* )> pdgIdFuncs;

  auto registerFunc = []() {
    pdgIdFuncs[ "DarkPion" ] = EJsHelper::selectDarkPion;
    pdgIdFuncs[ "Kshort"   ] = EJsHelper::selectKshort;
    return true;
  };

  bool registerPdgIdFuncs = registerFunc();
  
  bool selectDarkPion ( const xAOD::TruthVertex* truthVtx )
  {
    if ( truthVtx->nIncomingParticles() != 1 )                  return false;
    auto& links = truthVtx->incomingParticleLinks();
    if ( links.size() != 1 )                                    return false;
    if ( !links.at(0).isValid() )                               return false;
    if ( truthVtx->incomingParticle(0)->absPdgId() != 4900111 &&
	 truthVtx->incomingParticle(0)->absPdgId() != 4900211 ) return false;

    // if we made it this far, truth vertex is a dark pion decay...
    return true;
  }

  bool selectKshort ( const xAOD::TruthVertex* truthVtx ) // for testing...
  {
    if ( truthVtx->nIncomingParticles() != 1 )              return false;
    auto& links = truthVtx->incomingParticleLinks();
    if ( links.size() != 1 )                                return false;
    if ( !links.at(0).isValid() )                           return false;
    if ( truthVtx->incomingParticle(0)->absPdgId() != 310 ) return false;

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


  TLorentzVector truthSumP4 ( const std::set< const xAOD::TruthParticle* >& truthParts )
  {
    TLorentzVector v;
    for ( const auto& tp : truthParts ) v += tp->p4();
    return v;
  }

  TLorentzVector truthSumP4 ( const std::vector< const xAOD::TruthParticle* >& truthParts )
  {
    TLorentzVector v;
    for ( const auto& tp : truthParts ) v += tp->p4();
    return v;
  }

  TLorentzVector truthSumP4 ( const std::vector< TLorentzVector >& truthParts )
  {
    TLorentzVector v;
    for ( const auto& tp : truthParts ) v += tp;
    return v;
  }

  
  // from Reconstruction/Jet/JetSimTools/Root/JetTruthParticleSelectorTool.cxx
  bool isStable ( const xAOD::TruthParticle* tp )
  {
    if ( tp->barcode() >= 200000 ) return false; // G4 particle
    if ( tp->absPdgId() == 21 && tp->p4().E() == 0 ) return false; // zero-energy gluon
    return ( ( tp->status() % 1000 == 1 ) || // fully stable
	     ( tp->status() % 1000 == 2 && tp->hasDecayVtx() &&
	       tp->decayVtx() != NULL   && tp->decayVtx()->barcode() < -200000 ) ); // gen-stable
  }

  // from Reconstruction/Jet/JetSimTools/Root/JetTruthParticleSelectorTool.cxx
  bool isInteracting ( const xAOD::TruthParticle* tp )
  {
    if ( !isStable( tp ) ) return false;
    const int pid = tp->absPdgId();
    if ( pid == 12 || pid == 14 || pid == 16 ) return false; // neutrinos
    if ( ( tp->status() % 1000 == 1 ) &&
	 ( pid == 1000022 || pid == 1000024 || pid == 5100022 ||
	   pid == 39      || pid == 1000039 || pid == 5000039 ) ) return false; // susy
    return true;
  }

  bool isDark ( const xAOD::TruthParticle* tp )
  {
    return ( tp->absPdgId() > 4.9e6 && tp->absPdgId() < 5.0e6 );
  }

  // ------------------------------------------------------------------------------------------ //
  
} // namespace EJsHelper
