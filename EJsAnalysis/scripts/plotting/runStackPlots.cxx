#include <vector>

#include "makeStackPlots.cxx"
#include "makeCutflowStackPlots.cxx"

void runStackPlots()
{
  std::vector<TString> ptype;
  ptype.push_back( "mc"   );
  ptype.push_back( "data" );

  std::vector<TString> ptitle;
  ptitle.push_back( "mc16d" );
  ptitle.push_back( "data"  );


  for ( size_t i = 0; i != ptype.size(); ++i ) {
    makeStackPlots( "secVtx_n",    ptitle.at(i), "n DVs",         "events / bin", ptype.at(i) );
    makeStackPlots( "secVtx_r",    ptitle.at(i), "DV Lxy [mm]",   "events / bin", ptype.at(i) );
    makeStackPlots( "secVtx_mass", ptitle.at(i), "DV mass [GeV]", "events / bin", ptype.at(i) );
    makeStackPlots( "secVtx_ntrk", ptitle.at(i), "n DV tracks",   "events / bin", ptype.at(i) );

    makeCutflowStackPlots( "cutflow",        ptitle.at(i) + " cutflow",            "", "", ptype.at(i) );
    makeCutflowStackPlots( "cutflow_signal", ptitle.at(i) + " signal cutflow",     "", "", ptype.at(i) );
    makeCutflowStackPlots( "cutflow_valid",  ptitle.at(i) + " validation cutflow", "", "", ptype.at(i) );
  }
}
