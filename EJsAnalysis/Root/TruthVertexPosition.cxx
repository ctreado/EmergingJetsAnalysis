#include "EJsAnalysis/TruthVertexPosition.h"
#include "EJsAnalysis/EJsHelperFunctions.h"

using namespace EJs;

TruthVertexPosition :: TruthVertexPosition () {}

TruthVertexPosition :: TruthVertexPosition ( const TruthVertexPosition& truthVtxPos )
{
  m_ID        = truthVtxPos.m_ID;
  m_position  = truthVtxPos.m_position;
  m_truths    = truthVtxPos.m_truths;
  m_tracks    = truthVtxPos.m_tracks;
  m_truth_vtx = truthVtxPos.m_truth_vtx;
}

TruthVertexPosition :: TruthVertexPosition ( const TVector3&          position, const int id,
					     const xAOD::TruthVertex* truthVtx )
{
  m_ID        = id;
  m_position  = position;
  m_truth_vtx = truthVtx;
}

TruthVertexPosition :: TruthVertexPosition ( const xAOD::TruthParticle* truth, const int id,
					     const xAOD::TruthVertex*   truthVtx )
{
  m_ID        = id;
  m_position  = truth->prodVtx()->v4().Vect();
  m_truths     .emplace ( truth );
  m_truth_vtx = truthVtx;
}

TruthVertexPosition :: ~TruthVertexPosition () {}


void TruthVertexPosition :: emplace ( const xAOD::TruthParticle* truth )
{
  m_truths .emplace( truth );
}

void TruthVertexPosition :: emplace ( const xAOD::TrackParticle* track )
{
  m_tracks .emplace( track );
}

void TruthVertexPosition :: storeTracks ( const std::unordered_map<const xAOD::TruthParticle*, const xAOD::TrackParticle*>& hash )
{
  for ( const auto& truth : m_truths )
    if ( hash.find( truth ) != hash.end() )
      m_tracks.emplace( hash.at(truth) );
}

void TruthVertexPosition :: storeTracks ()
{
  for ( const auto& truth : m_truths ) {
    static SG::AuxElement::ConstAccessor<EJsHelper::TrackLink_t> trackAccess("trackLink");
    if ( trackAccess.isAvailable( *truth ) ) {
      try {
	const EJsHelper::TrackLink_t& tracklink = trackAccess( *truth );
	m_tracks.emplace( *tracklink );
      } catch(...){}
    }
  } 
}


int TruthVertexPosition :: ID () const
{
  return m_ID;
}

TVector3 TruthVertexPosition :: position () const
{
  return m_position;
}

const std::set<const xAOD::TruthParticle*>& TruthVertexPosition :: truth_set () const
{
  return m_truths;
}

const std::set<const xAOD::TrackParticle*>& TruthVertexPosition :: track_set () const
{
  return m_tracks;
}

const xAOD::TruthVertex* TruthVertexPosition :: truth_vtx () const
{
  return m_truth_vtx;
}


bool TruthVertexPosition :: isCompatibleWith ( const TVector3& pos, const double threshold ) const
{
  return ( m_position - pos ).Mag() < threshold;
}

bool TruthVertexPosition :: isCompatibleWith ( const xAOD::TruthParticle* truth, const double threshold ) const
{
  return ( m_position - truth->prodVtx()->v4().Vect() ).Mag() < threshold;
}

bool TruthVertexPosition :: find ( const xAOD::TruthParticle* truth ) const
{
  return ( std::find( m_truths.begin(), m_truths.end(), truth ) != m_truths.end() );
}

bool TruthVertexPosition :: find ( const xAOD::TrackParticle* track ) const
{
  return ( std::find( m_tracks.begin(), m_tracks.end(), track ) != m_tracks.end() );
}

bool TruthVertexPosition :: operator < ( const TruthVertexPosition& truthVtxPos ) const
{
  return m_position.Mag() < truthVtxPos.m_position.Mag();
}
