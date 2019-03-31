#include <vector>

#include "makeStackPlots.cxx"
#include "makeCutflowStackPlots.cxx"

void runStackPlots( TString hjet = "jet" )
{ 
  std::vector<TString> ptitle;
  //ptitle.push_back( "MC16d" );
  //ptitle.push_back( "data"  );
  ptitle.push_back( "truth" );

  std::vector<TString> pregion;
  pregion.push_back( "all"    );
  //pregion.push_back( "signal" );
  //pregion.push_back( "valid"  );

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
    else if ( lowtitle.Contains("truth") ) ptype = "truth";

    // loop over plot regions
    for ( size_t j = 0; j != pregion.size(); ++j ) {

      
      TString region       = pregion .at(j);
      TString region_title = region; 
      if      ( region == "all"    ) region_title = "all regions";
      else if ( region == "signal" ) region_title = "signal region";
      else if ( region == "valid"  ) region_title = "validation region";
      
      TString title  = ptitle.at(i) + ": " + region_title;

      if ( !ptype.Contains("truth") ) {
	
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

      } // end if not truth

      
      if ( !ptype.Contains("data") ) {
	
	// truth jets
	makeStackPlots( "truthJet_n",     title, "n truth jets",           "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_pt",    title, "truth jet p_{T} [GeV]",  "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_pt_l",  title, "truth jet p_{T} [GeV]",  "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_pt_m",  title, "truth jet p_{T} [GeV]",  "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_pt_s",  title, "truth jet p_{T} [GeV]",  "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_eta",   title, "truth jet eta",          "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_phi",   title, "truth jet phi",          "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_E",     title, "truth jet energy [GeV]", "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_M",     title, "truth jet mass [GeV]",   "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_rapid", title, "truth jet rapidity",     "", ptype, region, "truthJet" );
      
	makeStackPlots( "truthJet_girth",      title, "truth jet girth",                       "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_numConstit", title, "truth jet n constituents",              "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_constitPt",  title, "truth jet constituent sum-p_{T} [GeV]", "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_constit_dR", title, "truth jet - constituent dR",            "", ptype, region, "truthJet" );

	makeStackPlots( "truthJet_tpCount", title, "truth jet matched-truth-particle count",           "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_tpPt",    title, "truth jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_tpPt_l",  title, "truth jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_tpPt_m",  title, "truth jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_tpPt_s",  title, "truth jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, "truthJet" );
	makeStackPlots( "truthJet_tp_dR",   title, "truth jet - matched-truth-particle dR",            "", ptype, region, "truthJet" );


	// dark jets
	makeStackPlots( "darkJet_n",     title, "n dark jets",           "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_pt",    title, "dark jet p_{T} [GeV]",  "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_pt_l",  title, "dark jet p_{T} [GeV]",  "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_pt_m",  title, "dark jet p_{T} [GeV]",  "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_pt_s",  title, "dark jet p_{T} [GeV]",  "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_eta",   title, "dark jet eta",          "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_phi",   title, "dark jet phi",          "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_E",     title, "dark jet energy [GeV]", "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_M",     title, "dark jet mass [GeV]",   "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_rapid", title, "dark jet rapidity",     "", ptype, region, "darkJet" );
      
	makeStackPlots( "darkJet_girth",      title, "dark jet girth",                       "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_numConstit", title, "dark jet n constituents",              "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_constitPt",  title, "dark jet constituent sum-p_{T} [GeV]", "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_constit_dR", title, "dark jet - constituent dR",            "", ptype, region, "darkJet" );

	makeStackPlots( "darkJet_tpCount", title, "dark jet matched-truth-particle count",           "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_tpPt",    title, "dark jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_tpPt_l",  title, "dark jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_tpPt_m",  title, "dark jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_tpPt_s",  title, "dark jet matched-truth-particle sum-p_{T} [GeV]", "", ptype, region, "darkJet" );
	makeStackPlots( "darkJet_tp_dR",   title, "dark jet - matched-truth-particle dR",            "", ptype, region, "darkJet" );

      
	// truth particles -- scalar mediators
	makeStackPlots( "Xd_n",            title, "n scalar mediators",                           "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_pt",           title, "scalar mediator p_{T} [GeV]",                  "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_eta",          title, "scalar mediator eta",                          "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_phi",          title, "scalar mediator phi",                          "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_E",            title, "scalar mediator energy [GeV]",                 "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_M",            title, "scalar mediator mass [GeV]",                   "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_charge",       title, "scalar mediator charge",                       "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_nParents",     title, "n scalar mediator parents",                    "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_parentPdgId",  title, "scalar mediator parent pdgId",                 "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_parentStatus", title, "scalar mediator parent status",                "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_nChildren",    title, "n scalar mediator children",                   "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_childPdgId",   title, "scalar mediator child pdgId",                  "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_childStatus",  title, "scalar mediator child status",                 "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_prodVtx_r",    title, "scalar mediator production vertex r-pos [mm]", "", ptype, region, "truthPart" );
	makeStackPlots( "Xd_decayVtx_r",   title, "scalar mediator decay vertex r-pos [mm]",      "", ptype, region, "truthPart" );
	// truth particles -- dark quarks
	makeStackPlots( "qd_n",            title, "n dark quarks",                           "", ptype, region, "truthPart" );
	makeStackPlots( "qd_pt",           title, "dark quark p_{T} [GeV]",                  "", ptype, region, "truthPart" );
	makeStackPlots( "qd_eta",          title, "dark quark eta",                          "", ptype, region, "truthPart" );
	makeStackPlots( "qd_phi",          title, "dark quark phi",                          "", ptype, region, "truthPart" );
	makeStackPlots( "qd_E",            title, "dark quark energy [GeV]",                 "", ptype, region, "truthPart" );
	makeStackPlots( "qd_M",            title, "dark quark mass [GeV]",                   "", ptype, region, "truthPart" );
	makeStackPlots( "qd_charge",       title, "dark quark charge",                       "", ptype, region, "truthPart" );
	makeStackPlots( "qd_nParents",     title, "n dark quark parents",                    "", ptype, region, "truthPart" );
	makeStackPlots( "qd_parentPdgId",  title, "dark quark parent pdgId",                 "", ptype, region, "truthPart" );
	makeStackPlots( "qd_parentStatus", title, "dark quark parent status",                "", ptype, region, "truthPart" );
	makeStackPlots( "qd_nChildren",    title, "n dark quark children",                   "", ptype, region, "truthPart" );
	makeStackPlots( "qd_childPdgId",   title, "dark quark child pdgId",                  "", ptype, region, "truthPart" );
	makeStackPlots( "qd_childStatus",  title, "dark quark child status",                 "", ptype, region, "truthPart" );
	makeStackPlots( "qd_prodVtx_r",    title, "dark quark production vertex r-pos [mm]", "", ptype, region, "truthPart" );
	makeStackPlots( "qd_decayVtx_r",   title, "dark quark decay vertex r-pos [mm]",      "", ptype, region, "truthPart" );
	// truth particles -- dark pions
	makeStackPlots( "pid_n",            title, "n dark pions",                           "", ptype, region, "truthPart" );
	makeStackPlots( "pid_pt",           title, "dark pion p_{T} [GeV]",                  "", ptype, region, "truthPart" );
	makeStackPlots( "pid_eta",          title, "dark pion eta",                          "", ptype, region, "truthPart" );
	makeStackPlots( "pid_phi",          title, "dark pion phi",                          "", ptype, region, "truthPart" );
	makeStackPlots( "pid_E",            title, "dark pion energy [GeV]",                 "", ptype, region, "truthPart" );
	makeStackPlots( "pid_M",            title, "dark pion mass [GeV]",                   "", ptype, region, "truthPart" );
	makeStackPlots( "pid_charge",       title, "dark pion charge",                       "", ptype, region, "truthPart" );
	makeStackPlots( "pid_nParents",     title, "n dark pion parents",                    "", ptype, region, "truthPart" );
	makeStackPlots( "pid_parentPdgId",  title, "dark pion parent pdgId",                 "", ptype, region, "truthPart" );
	makeStackPlots( "pid_parentStatus", title, "dark pion parent status",                "", ptype, region, "truthPart" );
	makeStackPlots( "pid_nChildren",    title, "n dark pion children",                   "", ptype, region, "truthPart" );
	makeStackPlots( "pid_childPdgId",   title, "dark pion child pdgId",                  "", ptype, region, "truthPart" );
	makeStackPlots( "pid_childStatus",  title, "dark pion child status",                 "", ptype, region, "truthPart" );
	makeStackPlots( "pid_prodVtx_r",    title, "dark pion production vertex r-pos [mm]", "", ptype, region, "truthPart" );
	makeStackPlots( "pid_decayVtx_r",   title, "dark pion decay vertex r-pos [mm]",      "", ptype, region, "truthPart" );
	// truth particles -- dark rhos
	makeStackPlots( "rhod_n",            title, "n dark rhos",                           "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_pt",           title, "dark rho p_{T} [GeV]",                  "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_eta",          title, "dark rho eta",                          "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_phi",          title, "dark rho phi",                          "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_E",            title, "dark rho energy [GeV]",                 "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_M",            title, "dark rho mass [GeV]",                   "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_charge",       title, "dark rho charge",                       "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_nParents",     title, "n dark rho parents",                    "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_parentPdgId",  title, "dark rho parent pdgId",                 "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_parentStatus", title, "dark rho parent status",                "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_nChildren",    title, "n dark rho children",                   "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_childPdgId",   title, "dark rho child pdgId",                  "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_childStatus",  title, "dark rho child status",                 "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_prodVtx_r",    title, "dark rho production vertex r-pos [mm]", "", ptype, region, "truthPart" );
	makeStackPlots( "rhod_decayVtx_r",   title, "dark rho decay vertex r-pos [mm]",      "", ptype, region, "truthPart" );
	// truth particles -- off-diagonal dark pions
	makeStackPlots( "offpid_n",            title, "n off-diagonal dark pions",                           "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_pt",           title, "off-diagonal dark pion p_{T} [GeV]",                  "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_eta",          title, "off-diagonal dark pion eta",                          "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_phi",          title, "off-diagonal dark pion phi",                          "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_E",            title, "off-diagonal dark pion energy [GeV]",                 "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_M",            title, "off-diagonal dark pion mass [GeV]",                   "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_charge",       title, "off-diagonal dark pion charge",                       "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_nParents",     title, "n off-diagonal dark pion parents",                    "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_parentPdgId",  title, "off-diagonal dark pion parent pdgId",                 "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_parentStatus", title, "off-diagonal dark pion parent status",                "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_nChildren",    title, "n off-diagonal dark pion children",                   "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_childPdgId",   title, "off-diagonal dark pion child pdgId",                  "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_childStatus",  title, "off-diagonal dark pion child status",                 "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_prodVtx_r",    title, "off-diagonal dark pion production vertex r-pos [mm]", "", ptype, region, "truthPart" );
	makeStackPlots( "offpid_decayVtx_r",   title, "off-diagonal dark pion decay vertex r-pos [mm]",      "", ptype, region, "truthPart" );
	// truth particles -- off-diagonal dark rhos
	makeStackPlots( "offrhod_n",            title, "n off-diagonal dark rhos",                           "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_pt",           title, "off-diagonal dark rho p_{T} [GeV]",                  "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_eta",          title, "off-diagonal dark rho eta",                          "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_phi",          title, "off-diagonal dark rho phi",                          "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_E",            title, "off-diagonal dark rho energy [GeV]",                 "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_M",            title, "off-diagonal dark rho mass [GeV]",                   "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_charge",       title, "off-diagonal dark rho charge",                       "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_nParents",     title, "n off-diagonal dark rho parents",                    "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_parentPdgId",  title, "off-diagonal dark rho parent pdgId",                 "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_parentStatus", title, "off-diagonal dark rho parent status",                "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_nChildren",    title, "n off-diagonal dark rho children",                   "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_childPdgId",   title, "off-diagonal dark rho child pdgId",                  "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_childStatus",  title, "off-diagonal dark rho child status",                 "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_prodVtx_r",    title, "off-diagonal dark rho production vertex r-pos [mm]", "", ptype, region, "truthPart" );
	makeStackPlots( "offrhod_decayVtx_r",   title, "off-diagonal dark rho decay vertex r-pos [mm]",      "", ptype, region, "truthPart" );
	// truth particles -- inclusive dark pions (standard + off-diagonal)
	makeStackPlots( "allpid_n",            title, "n inclusive dark pions",                           "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_pt",           title, "inclusive dark pion p_{T} [GeV]",                  "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_eta",          title, "inclusive dark pion eta",                          "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_phi",          title, "inclusive dark pion phi",                          "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_E",            title, "inclusive dark pion energy [GeV]",                 "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_M",            title, "inclusive dark pion mass [GeV]",                   "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_charge",       title, "inclusive dark pion charge",                       "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_nParents",     title, "n inclusive dark pion parents",                    "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_parentPdgId",  title, "inclusive dark pion parent pdgId",                 "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_parentStatus", title, "inclusive dark pion parent status",                "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_nChildren",    title, "n inclusive dark pion children",                   "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_childPdgId",   title, "inclusive dark pion child pdgId",                  "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_childStatus",  title, "inclusive dark pion child status",                 "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_prodVtx_r",    title, "inclusive dark pion production vertex r-pos [mm]", "", ptype, region, "truthPart" );
	makeStackPlots( "allpid_decayVtx_r",   title, "inclusive dark pion decay vertex r-pos [mm]",      "", ptype, region, "truthPart" );
	// truth particles -- inclusive dark rhos (standard + off-diagonal)
	makeStackPlots( "allrhod_n",            title, "n inclusive dark rhos",                           "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_pt",           title, "inclusive dark rho p_{T} [GeV]",                  "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_eta",          title, "inclusive dark rho eta",                          "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_phi",          title, "inclusive dark rho phi",                          "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_E",            title, "inclusive dark rho energy [GeV]",                 "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_M",            title, "inclusive dark rho mass [GeV]",                   "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_charge",       title, "inclusive dark rho charge",                       "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_nParents",     title, "n inclusive dark rho parents",                    "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_parentPdgId",  title, "inclusive dark rho parent pdgId",                 "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_parentStatus", title, "inclusive dark rho parent status",                "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_nChildren",    title, "n inclusive dark rho children",                   "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_childPdgId",   title, "inclusive dark rho child pdgId",                  "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_childStatus",  title, "inclusive dark rho child status",                 "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_prodVtx_r",    title, "inclusive dark rho production vertex r-pos [mm]", "", ptype, region, "truthPart" );
	makeStackPlots( "allrhod_decayVtx_r",   title, "inclusive dark rho decay vertex r-pos [mm]",      "", ptype, region, "truthPart" );
	
      } // end if not data
      
    } // end loop over regions

    // cutflows
    if ( !ptype.Contains("truth") ) {
      makeCutflowStackPlots( "cutflow",        ptitle.at(i) + " cutflow: all regions",       "", "", ptype );
      makeCutflowStackPlots( "cutflow_signal", ptitle.at(i) + " cutflow: signal region",     "", "", ptype );
      makeCutflowStackPlots( "cutflow_valid",  ptitle.at(i) + " cutflow: validation region", "", "", ptype );
    }
    
  } // end loop over data types
  
}
