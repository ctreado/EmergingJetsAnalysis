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

  std::vector<TString> pregion;
  pregion.push_back( "all"    );
  pregion.push_back( "signal" );
  pregion.push_back( "valid"  );

  // loop over plot titles
  for ( size_t i = 0; i != ptitle.size(); ++i ) {

    // set plot type
    TString lowtitle = ptitle.at(i); lowtitle.ToLower();
    TString ptype = "";
    if      ( lowtitle.Contains("mc16d") ) ptype = "mc16d";
    else if ( lowtitle.Contains("data")  ) ptype = "data";

    // loop over plot regions
    for (size_t j = 0; j != pregion.size(); ++j ) {

      TString region = pregion .at(j);
      TString title  = ptitle  .at(i);

      // jets vs pileup
      make2DPlots( "jet_n_vs_avgMu",           title, "< #mu >", "n jets",                                       "", ptype, region, "jet" );
      make2DPlots( "jet_pt_vs_avgMu",          title, "< #mu >", "jet p_{T} [GeV] ",                             "", ptype, region, "jet" );
      make2DPlots( "jet_trkCount_vs_avgMu",    title, "< #mu >", "jet matched-track count",                      "", ptype, region, "jet" );
      make2DPlots( "jet_trkPt_vs_avgMu",       title, "< #mu >", "jet matched-track sum-p_{T} [GeV]",            "", ptype, region, "jet" );
      make2DPlots( "jet_trk_dR_vs_avgMu",      title, "< #mu >", "jet - matched-track dR",                       "", ptype, region, "jet" );
      make2DPlots( "jet_secVtxCount_vs_avgMu", title, "< #mu >", "jet matched-secondary-vertex count",           "", ptype, region, "jet" );
      make2DPlots( "jet_secVtxPt_vs_avgMu",    title, "< #mu >", "jet matched-secondary-vertex sum-p_{T} [GeV]", "", ptype, region, "jet" );
      make2DPlots( "jet_secVtx_dR_vs_avgMu",   title, "< #mu >", "jet - matched-secondary-vertex dR",            "", ptype, region, "jet" );
      make2DPlots( "jet_n_vs_actMu",           title,   "#mu",   "n jets",                                       "", ptype, region, "jet" );
      make2DPlots( "jet_pt_vs_actMu",          title,   "#mu",   "jet p_{T} [GeV] ",                             "", ptype, region, "jet" );
      make2DPlots( "jet_trkCount_vs_actMu",    title,   "#mu",   "jet matched-track count",                      "", ptype, region, "jet" );
      make2DPlots( "jet_trkPt_vs_actMu",       title,   "#mu",   "jet matched-track sum-p_{T} [GeV]",            "", ptype, region, "jet" );
      make2DPlots( "jet_trk_dR_vs_actMu",      title,   "#mu",   "jet - matched-track dR",                       "", ptype, region, "jet" );
      make2DPlots( "jet_secVtxCount_vs_actMu", title,   "#mu",   "jet matched-secondary-vertex count",           "", ptype, region, "jet" );
      make2DPlots( "jet_secVtxPt_vs_actMu",    title,   "#mu",   "jet matched-secondary-vertex sum-p_{T} [GeV]", "", ptype, region, "jet" );
      make2DPlots( "jet_secVtx_dR_vs_actMu",   title,   "#mu",   "jet - matched-secondary-vertex dR",            "", ptype, region, "jet" );

      // secondary vertices vs n-tracks
      make2DPlots( "secVtx_r_vs_ntrk",    title, "secondary vertex n tracks", "secondary vertex r-pos [mm]",  "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_pt_vs_ntrk",   title, "secondary vertex n tracks", "secondary vertex p_{T} [GeV]", "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_mass_vs_ntrk", title, "secondary vertex n tracks", "secondary vertex mass [GeV]",  "", ptype, region, "secVtx" );

      // secondary vertices vs pileup
      make2DPlots( "secVtx_n_vs_avgMu",          title, "< #mu >", "n secondary vertices",                 "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_r_vs_avgMu",          title, "< #mu >", "secondary vertex r-pos [mm]",          "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_pt_vs_avgMu",         title, "< #mu >", "secondary vertex p_{T} [GeV]",         "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_eta_vs_avgMu",        title, "< #mu >", "secondary vertex eta",                 "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_phi_vs_avgMu",        title, "< #mu >", "secondary vertex phi",                 "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_mass_vs_avgMu",       title, "< #mu >", "secondary vertex mass [GeV]",          "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_ntrk_vs_avgMu",       title, "< #mu >", "secondary vertex n tracks",            "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_ntrk_sel_vs_avgMu",   title, "< #mu >", "secondary vertex n selected tracks",   "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_ntrk_assoc_vs_avgMu", title, "< #mu >", "secondary vertex n associated tracks", "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_n_vs_actMu",          title,   "#mu",   "n secondary vertices",                 "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_r_vs_actMu",          title,   "#mu",   "secondary vertex r-pos [mm]",          "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_pt_vs_actMu",         title,   "#mu",   "secondary vertex p_{T} [GeV]",         "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_eta_vs_actMu",        title,   "#mu",   "secondary vertex eta",                 "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_phi_vs_actMu",        title,   "#mu",   "secondary vertex phi",                 "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_mass_vs_actMu",       title,   "#mu",   "secondary vertex mass [GeV]",          "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_ntrk_vs_actMu",       title,   "#mu",   "secondary vertex n tracks",            "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_ntrk_sel_vs_actMu",   title,   "#mu",   "secondary vertex n selected tracks",   "", ptype, region, "secVtx" );
      make2DPlots( "secVtx_ntrk_assoc_vs_actMu", title,   "#mu",   "secondary vertex n associated tracks", "", ptype, region, "secVtx" );
      
    } // end loop over regions
    
  } // end loop over data types
  
}
