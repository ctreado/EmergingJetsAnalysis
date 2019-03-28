#include <vector>

#include "makeStackPlots.cxx"
#include "makeCutflowStackPlots.cxx"

void runStackPlots( TString hjet = "jet" )
{ 
  std::vector<TString> ptitle;
  ptitle.push_back( "MC16d" );
  ptitle.push_back( "data"  );

  std::vector<TString> pregion;
  pregion.push_back( "all"    );
  pregion.push_back( "signal" );
  pregion.push_back( "valid"  );

  // --> change "doNorm" boolean to enum (or something), so we can choose to leave unnormalized or normalize one of set of certain values
  // (i.e. noNorm, normOne, normLumi, etc.)

  // --> update code to make new output directory if it doesn't already exist...not sure if this is feasible???

  int nJets    = 4;
  int nVtxTrks = 5;

  // loop over plot titles
  for ( size_t i = 0; i != ptitle.size(); ++i ) {

    // set plot type
    TString lowtitle = ptitle.at(i); lowtitle.ToLower();
    TString ptype    = "";
    if      ( lowtitle.Contains("mc16d") ) ptype = "mc16d";
    else if ( lowtitle.Contains("data")  ) ptype = "data";

    // loop over plot regions
    for ( size_t j = 0; j != pregion.size(); ++j ) {

      
      TString region       = pregion .at(j);
      TString region_title = region; 
      if      ( region == "all"    ) region_title = "all regions";
      else if ( region == "signal" ) region_title = "signal region";
      else if ( region == "valid"  ) region_title = "validation region";
      
      TString title  = ptitle.at(i) + ": " + region_title;

      // event info
      makeStackPlots( "nPV",       title, "n PV",                              "", ptype, region, "event" );
      makeStackPlots( "actualMu",  title, "actual interactions per crossing",  "", ptype, region, "event" );
      makeStackPlots( "averageMu", title, "average interactions per crossing", "", ptype, region, "event" );
      makeStackPlots( "NJetHt",    title, "N-jet H_{T} [GeV]",                 "", ptype, region, "event" );
      // pv info
      makeStackPlots( "pv_x",      title, "PV x-pos [mm]",                     "", ptype, region, "event" );
      makeStackPlots( "pv_y",      title, "PV y-pos [mm]",                     "", ptype, region, "event" );
      makeStackPlots( "pv_z",      title, "PV z-pos [mm]",                     "", ptype, region, "event" );
      makeStackPlots( "pv_r",      title, "PV r-pos [mm]",                     "", ptype, region, "event" );
      makeStackPlots( "pv_phi",    title, "PV phi",                            "", ptype, region, "event" );
      makeStackPlots( "pv_nTrk",   title, "PV n tracks",                       "", ptype, region, "event" );

      
      // jets
      makeStackPlots( hjet + "_n",     title, "n jets",           "", ptype, region, hjet );
      makeStackPlots( hjet + "_pt",    title, "jet p_{T} [GeV]",  "", ptype, region, hjet );
      makeStackPlots( hjet + "_pt_l",  title, "jet p_{T} [GeV]",  "", ptype, region, hjet );
      makeStackPlots( hjet + "_pt_m",  title, "jet p_{T} [GeV]",  "", ptype, region, hjet );
      makeStackPlots( hjet + "_pt_s",  title, "jet p_{T} [GeV]",  "", ptype, region, hjet );
      makeStackPlots( hjet + "_eta",   title, "jet eta",          "", ptype, region, hjet );
      makeStackPlots( hjet + "_phi",   title, "jet phi",          "", ptype, region, hjet );
      makeStackPlots( hjet + "_E",     title, "jet energy [GeV]", "", ptype, region, hjet );
      makeStackPlots( hjet + "_M",     title, "jet mass [GeV]",   "", ptype, region, hjet );
      makeStackPlots( hjet + "_rapid", title, "jet rapidity",     "", ptype, region, hjet );
      makeStackPlots( hjet + "_px",    title, "jet p_{x} [GeV]",  "", ptype, region, hjet );
      makeStackPlots( hjet + "_py",    title, "jet p_{y} [GeV]",  "", ptype, region, hjet );
      makeStackPlots( hjet + "_pz",    title, "jet p_{z} [GeV]",  "", ptype, region, hjet );
      makeStackPlots( hjet + "_Et",    title, "jet E_{T} [GeV]",  "", ptype, region, hjet );
      makeStackPlots( hjet + "_Et_l",  title, "jet E_{T} [GeV]",  "", ptype, region, hjet );
      makeStackPlots( hjet + "_Et_m",  title, "jet E_{T} [GeV]",  "", ptype, region, hjet );
      makeStackPlots( hjet + "_Et_s",  title, "jet E_{T} [GeV]",  "", ptype, region, hjet );
      for ( int ijet = 0; ijet != nJets; ++ijet ) {
      	std::string njet = std::to_string(ijet);
      	makeStackPlots( hjet + njet + "_pt",    title, "jet-" + njet + " p_{T} [GeV]",  "", ptype, region, hjet );
      	makeStackPlots( hjet + njet + "_pt_l",  title, "jet-" + njet + " p_{T} [GeV]",  "", ptype, region, hjet );
      	makeStackPlots( hjet + njet + "_pt_m",  title, "jet-" + njet + " p_{T} [GeV]",  "", ptype, region, hjet );
      	makeStackPlots( hjet + njet + "_pt_s",  title, "jet-" + njet + " p_{T} [GeV]",  "", ptype, region, hjet );
      	makeStackPlots( hjet + njet + "_eta",   title, "jet-" + njet + " eta",          "", ptype, region, hjet );
      	makeStackPlots( hjet + njet + "_phi",   title, "jet-" + njet + " phi",          "", ptype, region, hjet );
      	makeStackPlots( hjet + njet + "_E",     title, "jet-" + njet + " energy [GeV]", "", ptype, region, hjet );
      	makeStackPlots( hjet + njet + "_M",     title, "jet-" + njet + " mass [GeV]",   "", ptype, region, hjet );
      	makeStackPlots( hjet + njet + "_rapid", title, "jet-" + njet + " rapidity",     "", ptype, region, hjet );
      }
      
      makeStackPlots( hjet + "_hecFrac",    title, "jet HEC calo energy fraction", "", ptype, region, hjet );
      makeStackPlots( hjet + "_emFrac",     title, "jet EM calo energy fraction",  "", ptype, region, hjet );
      makeStackPlots( hjet + "_centroidR",  title, "jet centroid R",               "", ptype, region, hjet );
      makeStackPlots( hjet + "_width",      title, "jet width",                    "", ptype, region, hjet );
      makeStackPlots( hjet + "_numConstit", title, "jet n constituents",           "", ptype, region, hjet );

      makeStackPlots( hjet + "_numTrkPt1000",     title, "n jet p_{T} > 1.0 GeV tracks",        "", ptype, region, hjet );
      makeStackPlots( hjet + "_sumPtTrkPt1000",   title, "jet p_{T} > 1.0 GeV track sum-p_{T}", "", ptype, region, hjet );
      makeStackPlots( hjet + "_sumPtTrkPt1000_l", title, "jet p_{T} > 1.0 GeV track sum-p_{T}", "", ptype, region, hjet );
      makeStackPlots( hjet + "_sumPtTrkPt1000_m", title, "jet p_{T} > 1.0 GeV track sum-p_{T}", "", ptype, region, hjet );
      makeStackPlots( hjet + "_sumPtTrkPt1000_s", title, "jet p_{T} > 1.0 GeV track sum-p_{T}", "", ptype, region, hjet );
      makeStackPlots( hjet + "_trkWidthPt1000",   title, "jet p_{T} > 1.0 GeV track width",     "", ptype, region, hjet );
      makeStackPlots( hjet + "_numTrkPt500",      title, "n jet p_{T} > 1.0 GeV tracks",        "", ptype, region, hjet );
      makeStackPlots( hjet + "_sumPtTrkPt500",    title, "jet p_{T} > 0.5 GeV track sum-p_{T}", "", ptype, region, hjet );
      makeStackPlots( hjet + "_sumPtTrkPt500_l",  title, "jet p_{T} > 0.5 GeV track sum-p_{T}", "", ptype, region, hjet );
      makeStackPlots( hjet + "_sumPtTrkPt500_m",  title, "jet p_{T} > 0.5 GeV track sum-p_{T}", "", ptype, region, hjet );
      makeStackPlots( hjet + "_sumPtTrkPt500_s",  title, "jet p_{T} > 0.5 GeV track sum-p_{T}", "", ptype, region, hjet );
      makeStackPlots( hjet + "_trkWidthPt500",    title, "jet p_{T} > 0.5 GeV track width",     "", ptype, region, hjet );

      makeStackPlots(   hjet + "_GhostTrackCount", title, "jet ghost-associated track count",           "", ptype, region, hjet );
      makeStackPlots(   hjet + "_GhostTrackPt",    title, "jet ghost-associated track sum-p_{T} [GeV]", "", ptype, region, hjet );
      makeStackPlots(   hjet + "_GhostTrackPt_l",  title, "jet ghost-associated track sum-p_{T} [GeV]", "", ptype, region, hjet );
      makeStackPlots(   hjet + "_GhostTrackPt_m",  title, "jet ghost-associated track sum-p_{T} [GeV]", "", ptype, region, hjet );
      makeStackPlots(   hjet + "_GhostTrackPt_s",  title, "jet ghost-associated track sum-p_{T} [GeV]", "", ptype, region, hjet );
      if ( !ptype.Contains("data") ) {
      	makeStackPlots( hjet + "_GhostTruthCount", title, "jet ghost-associated truth count",           "", ptype, region, hjet );
      	makeStackPlots( hjet + "_GhostTruthPt",    title, "jet ghost-associated truth sum-p_{T} [GeV]", "", ptype, region, hjet );
      	makeStackPlots( hjet + "_GhostTruthPt_l",  title, "jet ghost-associated truth sum-p_{T} [GeV]", "", ptype, region, hjet );
      	makeStackPlots( hjet + "_GhostTruthPt_m",  title, "jet ghost-associated truth sum-p_{T} [GeV]", "", ptype, region, hjet );
      	makeStackPlots( hjet + "_GhostTruthPt_s",  title, "jet ghost-associated truth sum-p_{T} [GeV]", "", ptype, region, hjet );
      }

      makeStackPlots(   hjet + "_trkCount", title, "jet matched-track count",                    "", ptype, region, hjet );
      makeStackPlots(   hjet + "_trkPt",    title, "jet matched-track sum-p_{T} [GeV]",          "", ptype, region, hjet );
      makeStackPlots(   hjet + "_trkPt_l",  title, "jet matched-track sum-p_{T} [GeV]",          "", ptype, region, hjet );
      makeStackPlots(   hjet + "_trkPt_m",  title, "jet matched-track sum-p_{T} [GeV]",          "", ptype, region, hjet );
      makeStackPlots(   hjet + "_trkPt_s",  title, "jet matched-track sum-p_{T} [GeV]",          "", ptype, region, hjet );
      makeStackPlots(   hjet + "_trk_dR",   title, "jet - matched-track dR",                     "", ptype, region, hjet );
      if ( !ptype.Contains("data") ) {
      	makeStackPlots( hjet + "_tpCount",  title, "jet matched-truth-particle count",           "", ptype, region, hjet );
      	makeStackPlots( hjet + "_tpPt",     title, "jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, hjet );
      	makeStackPlots( hjet + "_tpPt_l",   title, "jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, hjet );
      	makeStackPlots( hjet + "_tpPt_m",   title, "jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, hjet );
      	makeStackPlots( hjet + "_tpPt_s",   title, "jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, hjet );
      	makeStackPlots( hjet + "_tp_dR",    title, "jet - matched-truth-particle dR",            "", ptype, region, hjet );
      }

      makeStackPlots(   hjet + "_secVtxCount",   title, "jet matched-secondary-vertex count",           "", ptype, region, hjet );
      makeStackPlots(   hjet + "_secVtxPt",      title, "jet matched-secondary-vertex sum-p_{T} [GeV]", "", ptype, region, hjet );
      makeStackPlots(   hjet + "_secVtx_dR",     title, "jet - matched-secondary-vertex dR",            "", ptype, region, hjet );
      if ( !ptype.Contains("data") ) {
      	makeStackPlots( hjet + "_truthVtxCount", title, "jet matched-truth-vertex count",               "", ptype, region, hjet );
      	makeStackPlots( hjet + "_truthVtxPt",    title, "jet matched-truth-vertex sum-p_{T} [GeV]",     "", ptype, region, hjet );
      	makeStackPlots( hjet + "_truthVtx_dR",   title, "jet - matched-truth-vertex dR",                "", ptype, region, hjet );
      }
      

      // secondary vertices
      makeStackPlots( "secVtx_n",                title, "n secondary vertices",                            "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_x",                title, "secondary vertex x-pos [mm]",                     "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_y",                title, "secondary vertex y-pos [mm]",                     "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_z",                title, "secondary vertex z-pos [mm]",                     "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_r",                title, "secondary vertex r-pos [mm]",                     "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_r_l",              title, "secondary vertex r-pos [mm]",                     "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_r_s",              title, "secondary vertex r-pos [mm]",                     "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_pt",               title, "secondary vertex p_{T} [GeV]",                    "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_eta",              title, "secondary vertex eta",                            "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_phi",              title, "secondary vertex phi",                            "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_mass",             title, "secondary vertex mass [GeV]",                     "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_mass_l",           title, "secondary vertex mass [GeV]",                     "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_mass_s",           title, "secondary vertex mass [GeV]",                     "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_mass_nonAssoc",    title, "secondary vertex mass (excl. assoc. trks) [GeV]", "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_mass_nonAssoc_l",  title, "secondary vertex mass (excl. assoc. trks) [GeV]", "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_mass_nonAssoc_s",  title, "secondary vertex mass (excl. assoc. trks) [GeV]", "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_chi2",             title, "secondary vertex chi2 / DoF",                     "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_direction",        title, "secondary vertex direction",                      "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_charge",           title, "secondary vertex charge",                         "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_Ht",               title, "secondary vertex scalar sum-p_{T} [GeV]",         "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_minOpAng",         title, "secondary vertex minimum opening angle",          "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_maxOpAng",         title, "secondary vertex maximum opening angle",          "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_mind0",            title, "secondary vertex minimum track d0",               "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_maxd0",            title, "secondary vertex maximum track d0",               "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_minOneTrkRmvMass", title, "secondary vertex minimum n-1-track mass [GeV]",   "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_twoTrkMass",       title, "secondary vertex arbitrary 2-track mass [GeV]",   "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_twoTrkMassRest",   title, "secondary vertex arbitrary n-2-track mass [GeV]", "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_twoTrkCharge",     title, "secondary vertex arbitrary 2-track charge",       "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_ntrk",             title, "secondary vertex n tracks",                       "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_ntrk_sel",         title, "secondary vertex n selected tracks",              "", ptype, region, "secVtx" );
      makeStackPlots( "secVtx_ntrk_assoc",       title, "secondary vertex n associated tracks",            "", ptype, region, "secVtx" );
      for ( int ivtrk = 1; ivtrk != nVtxTrks; ++ivtrk ) {
      	std::string ntrk = std::to_string(ivtrk+1);
      	makeStackPlots( "secVtx" + ntrk + "trk_n",               title, "n " + ntrk + "-track secondary vertices",                       "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_x",               title, ntrk + "-track secondary vertex x-pos [mm]",                     "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_y",               title, ntrk + "-track secondary vertex y-pos [mm]",                     "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_z",               title, ntrk + "-track secondary vertex z-pos [mm]",                     "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_r",               title, ntrk + "-track secondary vertex r-pos [mm]",                     "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_r_l",             title, ntrk + "-track secondary vertex r-pos [mm]",                     "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_r_s",             title, ntrk + "-track secondary vertex r-pos [mm]",                     "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_pt",              title, ntrk + "-track secondary vertex p_{T} [GeV]",                    "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_eta",             title, ntrk + "-track secondary vertex eta",                            "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_phi",             title, ntrk + "-track secondary vertex phi",                            "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_mass",            title, ntrk + "-track secondary vertex mass [GeV]",                     "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_mass_l",          title, ntrk + "-track secondary vertex mass [GeV]",                     "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_mass_s",          title, ntrk + "-track secondary vertex mass [GeV]",                     "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_mass_nonAssoc",   title, ntrk + "-track secondary vertex mass (excl. assoc. trks) [GeV]", "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_mass_nonAssoc_l", title, ntrk + "-track secondary vertex mass (excl. assoc. trks) [GeV]", "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_mass_nonAssoc_s", title, ntrk + "-track secondary vertex mass (excl. assoc. trks) [GeV]", "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_chi2",            title, ntrk + "-track secondary vertex chi2 / DoF",                     "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_direction",       title, ntrk + "-track secondary vertex direction",                      "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_charge",          title, ntrk + "-track secondary vertex charge",                         "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_Ht",              title, ntrk + "-track secondary vertex scalar sum-p_{T} [GeV]",         "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_minOpAng",        title, ntrk + "-track secondary vertex minimum opening angle",          "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_maxOpAng",        title, ntrk + "-track secondary vertex maximum opening angle",          "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_mind0",           title, ntrk + "-track secondary vertex minimum track d0",               "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_maxd0",           title, ntrk + "-track secondary vertex maximum track d0",               "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_ntrk_sel",        title, ntrk + "-track secondary vertex n selected tracks",              "", ptype, region, "secVtx" );
      	makeStackPlots( "secVtx" + ntrk + "trk_ntrk_assoc",      title, ntrk + "-track secondary vertex n associated tracks",            "", ptype, region, "secVtx" );
      }
      
    } // end loop over regions

    // cutflows
    makeCutflowStackPlots( "cutflow",        ptitle.at(i) + " cutflow: all regions",       "", "", ptype );
    makeCutflowStackPlots( "cutflow_signal", ptitle.at(i) + " cutflow: signal region",     "", "", ptype );
    makeCutflowStackPlots( "cutflow_valid",  ptitle.at(i) + " cutflow: validation region", "", "", ptype );
    
  } // end loop over data types
  
}
