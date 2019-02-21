#include <vector>

#include "make2DPlots.cxx"

void run2DPlots()
{
  std::vector<TString> ptitle;
  ptitle.push_back( "MC16d.EJ_ModelA_1400_20"  );
  ptitle.push_back( "MC16d.EJ_ModelA_1000_150" );
  ptitle.push_back( "MC16d.EJ_ModelB_1400_20"  );
  ptitle.push_back( "MC16d.EJ_ModelB_1000_5"   );
  ptitle.push_back( "MC16d.EJ_ModelC_1400_20"  );
  ptitle.push_back( "MC16d.EJ_ModelC_1000_75"  );
  ptitle.push_back( "MC16d.EJ_ModelC_600_20"   );
  ptitle.push_back( "MC16d.EJ_ModelD_600_300"  );
  ptitle.push_back( "MC16d.EJ_ModelE_600_75"   );
  ptitle.push_back( "data17.00328333" );
  ptitle.push_back( "data16.00302872" );
  ptitle.push_back( "data15.00284285" );

  for ( size_t i = 0; i != ptitle.size(); ++i ) {
    TString lowtitle = ptitle.at(i); lowtitle.ToLower();
    TString ptype = "";
    if      ( lowtitle.Contains("mc16d") ) ptype = "mc16d";
    else if ( lowtitle.Contains("data")  ) ptype = "data";
    
    make2DPlots( "secVtx_r_vs_ntrk",    ptitle.at(i), "n DV tracks", "DV Lxy [mm]",   "events / bin", ptype,
		 "pdf", false, true );
    make2DPlots( "secVtx_mass_vs_ntrk", ptitle.at(i), "n DV tracks", "DV mass [GeV]", "events / bin", ptype,
		 "pdf", false, true );
  }
}
