#ifndef EJsAnalysis_TruthVertexPosition_H
#define EJsAnalysis_TruthVertexPosition_H

/* TruthVertexPosition class (based on Hideyuki Oide's VsiPerf::TruthVertexPos class:
   https://gitlab.cern.ch/Atlas-Inner-Tracking/SecVtxPUBNote/blob/master/Code/VSIPerf/include/TruthVertexPos.h)
   to collect position and associated truth and track particle information for truth LLP decays */

#include <set>
#include <unordered_map>

#include <TVector3.h>

#include <xAODTruth/TruthParticle.h>
#include <xAODTruth/TruthVertex.h>
#include <xAODTracking/TrackParticle.h>

namespace EJs {

  class TruthVertexPosition {
  public:
    // constructors
    TruthVertexPosition (); // default
    TruthVertexPosition ( const TruthVertexPosition&                             );
    TruthVertexPosition ( const TVector3&             /*pos*/,  const int id = 0, const xAOD::TruthVertex* truthVtx = 0 );
    TruthVertexPosition ( const xAOD::TruthParticle* /*truth*/, const int id = 0, const xAOD::TruthVertex* truthVtx = 0 );

    // destructor
    virtual ~TruthVertexPosition ();

    void emplace     ( const xAOD::TruthParticle* truth );
    void emplace     ( const xAOD::TrackParticle* track );
    void storeTracks ( const std::unordered_map<const xAOD::TruthParticle*, const xAOD::TrackParticle*>& hash );
    void storeTracks ();

    int      ID        () const;
    TVector3 position  () const;
    const std::set<const xAOD::TruthParticle*>& truth_set () const;
    const std::set<const xAOD::TrackParticle*>& track_set () const;
    const                xAOD::TruthVertex*     truth_vtx () const;

    bool isCompatibleWith ( const TVector3&            pos,   const double threshold = 1.0 ) const;
    bool isCompatibleWith ( const xAOD::TruthParticle* truth, const double threshold = 1.0 ) const;
    bool find             ( const xAOD::TruthParticle* truth                               ) const;
    bool find             ( const xAOD::TrackParticle* track                               ) const;
    bool operator <       ( const TruthVertexPosition& truthVtxPos                         ) const;


  private:
    int      m_ID;
    TVector3 m_position;
    std::set<const xAOD::TruthParticle*> m_truths;
    std::set<const xAOD::TrackParticle*> m_tracks;
    const          xAOD::TruthVertex*    m_truth_vtx;

  };
  
} // EJs

#endif // EJsAnalysis_TruthVertexPosition_H
