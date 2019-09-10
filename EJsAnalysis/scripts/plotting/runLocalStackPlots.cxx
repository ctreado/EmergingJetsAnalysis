#include <vector>

#include "makeLocalStackPlots.cxx"

void runLocalStackPlots( )
{
  // htypes = "data", "mc16*[_mod*/_xdm*]", "mc16*_data*", "mc16*_bkgd", "mc16*_data*_bkgd", "data*_bkgd"
  // --> any permutation will work; with mc, data, specifying campaign or year will dictate the other...

  TString hjetStr = "PFlow"; // --> change to input argument
  TString hjetLow = ToLower( hjetStr );
  TString hjetUp  = hjetStr + "Jet";
  TString hjet    = hjetLow + "Jet";

  // --> update code to make new output directory if it doesn't already exist...not sure if this is feasible???
  TString hdir = "ueh_829_" + hjetLow;

  int nJets    = 4; // can these be configurable ?? can we pull this info from somewhere ??
  int nVtxTrks = 5;
  
  std::vector<TString> ptype;
  ptype.push_back( "data"            );
  ptype.push_back( "mc16d"           );
  //ptype.push_back( "mc16d_modA"      );
  //ptype.push_back( "mc16d_modB"      );
  //ptype.push_back( "mc16d_modC"      );
  //ptype.push_back( "mc16d_modD"      );
  //ptype.push_back( "mc16d_modE"      );
  //ptype.push_back( "mc16d_xdm1400"   );
  //ptype.push_back( "mc16d_xdm1000"   );
  //ptype.push_back( "mc16d_xdm600"    );
  ptype.push_back( "mc16d_data"      );
  ptype.push_back( "mc16d_bkgd"      );
  //ptype.push_back( "mc16d_data_bkgd" );

  std::vector<TString> pregion;
  pregion.push_back( "all"    );
  pregion.push_back( "signal" );
  pregion.push_back( "valid"  );

  // --> change "doNorm" boolean to enum (or something)
  // so we can choose to leave unnormalized or normalize one of set of certain values
  // (i.e. noNorm, normOne, normLumi, etc.)
  
  // loop over plot types
  for ( size_t i = 0; i != ptype.size(); ++i ) {
    
    TString type = ptype.at(i);
    
    // loop over plot regions
    for ( size_t j = 0; j != pregion.size(); ++j ) {
      
      TString reg = pregion.at(j);

      // // event info
      // makeLocalStackPlots( "nPV",               type, reg, "n PV",              "", hdir );
      // makeLocalStackPlots( "actualMu",          type, reg, "actualMu",          "", hdir );
      // makeLocalStackPlots( "averageMu",         type, reg, "averageMu",         "", hdir );
      // makeLocalStackPlots( "N" + hjetUp + "Ht", type, reg, "N-jet H_{T} [GeV]", "", hdir );
      // // primary vertex...

      
      // // jets
      // makeLocalStackPlots( hjet + "_n",    type, reg, "n jets",           "", hdir );
      // makeLocalStackPlots( hjet + "_pt",   type, reg, "jet p_{T} [GeV]",  "", hdir );
      // makeLocalStackPlots( hjet + "_pt_l", type, reg, "jet p_{T} [GeV]",  "", hdir );
      // makeLocalStackPlots( hjet + "_pt_m", type, reg, "jet p_{T} [GeV]",  "", hdir );
      // makeLocalStackPlots( hjet + "_pt_s", type, reg, "jet p_{T} [GeV]",  "", hdir );
      // makeLocalStackPlots( hjet + "_eta",  type, reg, "jet eta",          "", hdir );
      // makeLocalStackPlots( hjet + "_phi",  type, reg, "jet phi",          "", hdir );
      // makeLocalStackPlots( hjet + "_E",    type, reg, "jet energy [GeV]", "", hdir );
      // makeLocalStackPlots( hjet + "_M",    type, reg, "jet mass [GeV]",   "", hdir );
      // for ( int ijet = 0; ijet != nJets; ++ijet ) {
      // 	std::string njet = std::to_string(ijet);
      // 	makeLocalStackPlots( hjet + njet + "_pt",  type, reg, "jet-" + njet + "p_{T} [GeV]",  "", hdir );
      // 	makeLocalStackPlots( hjet + njet + "_eta", type, reg, "jet-" + njet + "eta",          "", hdir );
      // 	makeLocalStackPlots( hjet + njet + "_phi", type, reg, "jet-" + njet + "phi",          "", hdir );
      // 	makeLocalStackPlots( hjet + njet + "_E",   type, reg, "jet-" + njet + "energy [GeV]", "", hdir );
      // 	makeLocalStackPlots( hjet + njet + "_M",   type, reg, "jet-" + njet + "mass [GeV]",   "", hdir );
      // }
      
      // makeLocalStackPlots( hjet + "_hecFrac",    type, reg, "jet HEC calo energy fraction", "", hdir );
      // makeLocalStackPlots( hjet + "_emFrac",     type, reg, "jet EM calo energy fraction",  "", hdir );
      // makeLocalStackPlots( hjet + "_centroidR",  type, reg, "jet centroid R",               "", hdir );
      // makeLocalStackPlots( hjet + "_width",      type, reg, "jet width",                    "", hdir );
      // makeLocalStackPlots( hjet + "_numConstit", type, reg, "n jet constituents",           "", hdir );

      // makeLocalStackPlots( hjet + "_trkCount",    type, reg, "jet-matched track count",                      "", hdir );
      // makeLocalStackPlots( hjet + "_trkPt",       type, reg, "jet-matched track sum-p_{T} [GeV]",            "", hdir );
      // makeLocalStackPlots( hjet + "_trk_dR",      type, reg, "jet - matched-track dR",                       "", hdir );

      // makeLocalStackPlots( hjet + "_secVtxCount", type, reg, "jet-matched secondary vertex count",           "", hdir );
      // makeLocalStackPlots( hjet + "_secVtxPt",    type, reg, "jet-matched secondary vertex sum-p_{T} [GeV]", "", hdir );
      // makeLocalStackPlots( hjet + "_secVtx_dR",   type, reg, "jet - matched-secondary vertex dR",            "", hdir );

      
      // // secondary vertices
      // makeLocalStackPlots( "secVtx_n",               type, reg, "n secondary vertices",                    "", hdir );
      // makeLocalStackPlots( "secVtx_z",               type, reg, "secondary vertex z-pos [mm]",             "", hdir );
      // makeLocalStackPlots( "secVtx_r",               type, reg, "secondary vertex r-pos [mm]",             "", hdir );
      // makeLocalStackPlots( "secVtx_r_l",             type, reg, "secondary vertex r-pos [mm]",             "", hdir );
      // makeLocalStackPlots( "secVtx_r_s",             type, reg, "secondary vertex r-pos [mm]",             "", hdir );
      // makeLocalStackPlots( "secVtx_pt",              type, reg, "secondary vertex p_{T} [GeV]",            "", hdir );
      // makeLocalStackPlots( "secVtx_eta",             type, reg, "secondary vertex eta",                    "", hdir );
      // makeLocalStackPlots( "secVtx_phi",             type, reg, "secondary vertex phi",                    "", hdir );
      // makeLocalStackPlots( "secVtx_mass",            type, reg, "secondary vertex mass [GeV]",             "", hdir );
      // makeLocalStackPlots( "secVtx_mass_l",          type, reg, "secondary vertex mass [GeV]",             "", hdir );
      // makeLocalStackPlots( "secVtx_mass_s",          type, reg, "secondary vertex mass [GeV]",             "", hdir );
      // makeLocalStackPlots( "secVtx_mass_nonAssoc",   type, reg, "secondary vertex non-assoc mass [GeV]",   "", hdir );
      // makeLocalStackPlots( "secVtx_mass_nonAssoc_l", type, reg, "secondary vertex non-assoc mass [GeV]",   "", hdir );
      // makeLocalStackPlots( "secVtx_mass_nonAssoc_s", type, reg, "secondary vertex non-assoc mass [GeV]",   "", hdir );
      // makeLocalStackPlots( "secVtx_chi2",            type, reg, "secondary vertex chi2 / DoF",             "", hdir );
      // makeLocalStackPlots( "secVtx_Ht",              type, reg, "secondary vertex scalar sum-p_{T} [GeV]", "", hdir );
      // makeLocalStackPlots( "secVtx_minOpAng",        type, reg, "secondary vertex minimum opening angle",  "", hdir );
      // makeLocalStackPlots( "secVtx_maxOpAng",        type, reg, "secondary vertex maximum opening angle",  "", hdir );
      // makeLocalStackPlots( "secVtx_mind0",           type, reg, "secondary vertex minimum track d0",       "", hdir );
      // makeLocalStackPlots( "secVtx_maxd0",           type, reg, "secondary vertex maximum track d0",       "", hdir );
      // makeLocalStackPlots( "secVtx_twoTrkMass",      type, reg, "secondary vertex 2-track mass [GeV]",     "", hdir );
      // makeLocalStackPlots( "secVtx_ntrk",            type, reg, "secondary vertex n tracks",               "", hdir );
      // makeLocalStackPlots( "secVtx_ntrk_sel",        type, reg, "secondary vertex n selected tracks",      "", hdir );
      // makeLocalStackPlots( "secVtx_ntrk_assoc",      type, reg, "secondary vertex n associated tracks",    "", hdir );
      // for ( int ivtrk = 1; ivtrk != nVtxTrks; ++ivtrk ) {
      // 	std::string ntrk = std::to_string(ivtrk+1);
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_n",
      // 			     type, reg, "n " + ntrk + "-track secondary vertices",             "", hdir );
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_z",
      // 			     type, reg, ntrk + "-track secondary vertex z-pos [mm]",           "", hdir );
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_r",
      // 			     type, reg, ntrk + "-track secondary vertex r-pos [mm]",           "", hdir );
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_r_l",
      // 			     type, reg, ntrk + "-track secondary vertex r-pos [mm]",           "", hdir );
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_r_s",
      // 			     type, reg, ntrk + "-track secondary vertex r-pos [mm]",           "", hdir );
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_phi",
      // 			     type, reg, ntrk + "-track secondary vertex phi",                  "", hdir );
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_mass",
      // 			     type, reg, ntrk + "-track secondary vertex mass [GeV]",           "", hdir );
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_mass_l",
      // 			     type, reg, ntrk + "-track secondary vertex mass [GeV]",           "", hdir );
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_mass_s",
      // 			     type, reg, ntrk + "-track secondary vertex mass [GeV]",           "", hdir );
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_mass_nonAssoc",
      // 			     type, reg, ntrk + "-track secondary vertex non-assoc mass [GeV]", "", hdir );
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_mass_nonAssoc_l",
      // 			     type, reg, ntrk + "-track secondary vertex non-assoc mass [GeV]", "", hdir );
      // 	makeLocalStackPlots( ntrk + "trkSecVtx_mass_nonAssoc_s",
      // 			     type, reg, ntrk + "-track secondary vertex non-assoc mass [GeV]", "", hdir );
      // }


      // if ( !type.Contains("data") ) {
      // 	// truth jets
      // 	makeLocalStackPlots( "truthJet_n",     type, reg, "n truth jets",           "", hdir );
      // 	makeLocalStackPlots( "truthJet_pt",    type, reg, "truth jet p_{T} [GeV]",  "", hdir );
      // 	makeLocalStackPlots( "truthJet_eta",   type, reg, "truth jet eta",          "", hdir );
      // 	makeLocalStackPlots( "truthJet_phi",   type, reg, "truth jet phi",          "", hdir );
      // 	makeLocalStackPlots( "truthJet_E",     type, reg, "truth jet energy [GeV]", "", hdir );
      // 	makeLocalStackPlots( "truthJet_M",     type, reg, "truth jet mass [GeV]",   "", hdir );
	
      // 	makeLocalStackPlots( "truthJet_girth",          type, reg, "truth jet girth",                                    "", hdir );
      // 	makeLocalStackPlots( "truthJet_nConstit",       type, reg, "n truth jet constituents",                           "", hdir );
      // 	makeLocalStackPlots( "truthJet_constitPt",      type, reg, "truth jet constituent sum-p_{T} [GeV]",              "", hdir );
      // 	makeLocalStackPlots( "truthJet_constit_dR",     type, reg, "truth jet - constituent dR",                         "", hdir );
      // 	makeLocalStackPlots( "truthJet_constit_pVtx_r", type, reg, "truth jet constituent production vertex r-pos [mm]", "", hdir );
      // 	makeLocalStackPlots( "truthJet_nChrgConstit",   type, reg, "n truth jet charged constituents",                   "", hdir );
      // 	makeLocalStackPlots( "truthJet_nVisConstit",    type, reg, "n truth jet visible constituents",                   "", hdir );

      // 	makeLocalStackPlots( "truthJet_tpCount",       type, reg, "truth-jet-matched truth particle count",           "", hdir );
      // 	makeLocalStackPlots( "truthJet_tpPt",          type, reg, "truth-jet-matched truth particle sum-p_{T} [GeV]", "", hdir );
      // 	makeLocalStackPlots( "truthJet_tp_dR",         type, reg, "truth-jet - matched-truth-particle dR",            "", hdir );
      // 	makeLocalStackPlots( "truthJet_chrgTpCount",   type, reg, "truth-jet-matched charged truth particle count",   "", hdir );
      // 	makeLocalStackPlots( "truthJet_visTpCount",    type, reg, "truth-jet-matched visible truth particle count",   "", hdir );
      // 	makeLocalStackPlots( "truthJet_darkTpCount",   type, reg, "truth-jet-matched dark truth particle count",      "", hdir );
      // 	makeLocalStackPlots( "truthJet_pidTpCount",    type, reg, "truth-jet-matched dark pion count",                "", hdir );
	
      // 	makeLocalStackPlots( "truthJet_truthVtxCount",     type, reg, "truth-jet-matched truth vertex count",           "", hdir );
      // 	makeLocalStackPlots( "truthJet_truthVtxPt",        type, reg, "truth-jet-matched truth vertex sum-p_{T} [GeV]", "", hdir );
      // 	makeLocalStackPlots( "truthJet_truthVtx_dR",       type, reg, "truth-jet - matched-truth vertex dR",            "", hdir );
      // 	makeLocalStackPlots( "truthJet_truthVtx_r",        type, reg, "truth-jet-matched truth vertex r-pos [mm]",      "", hdir );
      // 	makeLocalStackPlots( "truthJet_truthVtx_mass",     type, reg, "truth-jet-matched truth vertex mass [GeV]",      "", hdir );
      // 	makeLocalStackPlots( "truthJet_pidTruthVtxCount",  type, reg, "truth-jet-matched truth dark pion decay count",  "", hdir );
      // 	makeLocalStackPlots( "truthJet_dispTruthVtxCount", type, reg, "truth-jet-matched displaced truth vertex count", "", hdir );


      // 	// truth particles -- all
      // 	makeLocalStackPlots( "tp_n",            type, reg, "n truth particles",                      "", hdir );
      // 	makeLocalStackPlots( "tp_sumPt",        type, reg, "truth particle sum-p_{T} [GeV]",         "", hdir );
      // 	makeLocalStackPlots( "tp_nCharged",     type, reg, "n charged truth particles",              "", hdir );
      // 	makeLocalStackPlots( "tp_sumPtCharged", type, reg, "charged truth particle sum-p_{T} [GeV]", "", hdir );
      // 	makeLocalStackPlots( "tp_nVisible",     type, reg, "n visible truth particles",              "", hdir );
      // 	makeLocalStackPlots( "tp_visibleSumPt", type, reg, "visible truth particle sum-p_{T} [GeV]", "", hdir ); // fix name
      // 	makeLocalStackPlots( "tp_nDark",        type, reg, "n dark truth particles",                 "", hdir );
      // 	makeLocalStackPlots( "tp_sumPtDark",    type, reg, "dark truth particle sum-p_{T} [GeV]",    "", hdir );
      // 	// truth particles -- scalar mediators
      // 	makeLocalStackPlots( "Xd_n",            type, reg, "n scalar mediators",                     "", hdir );
      // 	makeLocalStackPlots( "Xd_M",            type, reg, "scalar mediator mass [GeV]",             "", hdir );
      // 	makeLocalStackPlots( "Xd_charge",       type, reg, "scalar mediator charge",                 "", hdir );
      // 	makeLocalStackPlots( "Xd_nChildren",    type, reg, "n scalar mediator children",             "", hdir );
      // 	makeLocalStackPlots( "Xd_childPdgId",   type, reg, "scalar mediator child pdgId",            "", hdir );
      // 	makeLocalStackPlots( "Xd_sumPt",        type, reg, "scalar mediator scalar sum-p_{T} [GeV]", "", hdir );
      // 	// truth particles -- dark quarks
      // 	makeLocalStackPlots( "qd_n",            type, reg, "n dark quarks",                          "", hdir );
      // 	makeLocalStackPlots( "qd_M",            type, reg, "dark quark mass [GeV]",                  "", hdir );
      // 	makeLocalStackPlots( "qd_charge",       type, reg, "dark quark charge",                      "", hdir );
      // 	makeLocalStackPlots( "qd_nChildren",    type, reg, "n dark quark children",                  "", hdir );
      // 	makeLocalStackPlots( "qd_childPdgId",   type, reg, "dark quark child pdgId",                 "", hdir );
      // 	makeLocalStackPlots( "qd_sumPt",        type, reg, "dark quark scalar sum-p_{T} [GeV]",      "", hdir );
      // 	// truth particles -- dark pions
      // 	makeLocalStackPlots( "pid_n",           type, reg, "n dark pions",                           "", hdir );
      // 	makeLocalStackPlots( "pid_M",           type, reg, "dark pion mass [GeV]",                   "", hdir );
      // 	makeLocalStackPlots( "pid_charge",      type, reg, "dark pion charge",                       "", hdir );
      // 	makeLocalStackPlots( "pid_nChildren",   type, reg, "n dark pion children",                   "", hdir );
      // 	makeLocalStackPlots( "pid_childPdgId",  type, reg, "dark pion child pdgId",                  "", hdir );
      // 	makeLocalStackPlots( "pid_decayVtx_r",  type, reg, "dark pion decay vertex r-pos [mm]",      "", hdir );
      // 	makeLocalStackPlots( "pid_sumPt",       type, reg, "dark pion scalar sum-p_{T} [GeV]",       "", hdir );
      // 	// truth particles -- dark rhos
      // 	makeLocalStackPlots( "rhod_n",          type, reg, "n dark rhos",                            "", hdir );
      // 	makeLocalStackPlots( "rhod_M",          type, reg, "dark rho mass [GeV]",                    "", hdir );
      // 	makeLocalStackPlots( "rhod_charge",     type, reg, "dark rho charge",                        "", hdir );
      // 	makeLocalStackPlots( "rhod_nChildren",  type, reg, "n dark rho children",                    "", hdir );
      // 	makeLocalStackPlots( "rhod_childPdgId", type, reg, "dark rho child pdgId",                   "", hdir );
      // 	makeLocalStackPlots( "rhod_decayVtx_r", type, reg, "dark rho decay vertex r-pos [mm]",       "", hdir );
      // 	makeLocalStackPlots( "rhod_sumPt",      type, reg, "dark rho scalar sum-p_{T} [GeV]",        "", hdir );
	
	
      // 	// truth vertices
      // 	makeLocalStackPlots( "truthVtx_n",     type, reg, "n truth vertices",                  "", hdir );
      // 	makeLocalStackPlots( "truthVtx_z",     type, reg, "truth vertex z-pos [mm]",           "", hdir );
      // 	makeLocalStackPlots( "truthVtx_r",     type, reg, "truth vertex r-pos [mm]",           "", hdir );
      // 	makeLocalStackPlots( "truthVtx_pt",    type, reg, "truth vertex p_{T} [GeV]",          "", hdir );
      // 	makeLocalStackPlots( "truthVtx_eta",   type, reg, "truth vertex eta",                  "", hdir );
      // 	makeLocalStackPlots( "truthVtx_phi",   type, reg, "truth vertex phi",                  "", hdir );
      // 	makeLocalStackPlots( "truthVtx_mass",  type, reg, "truth vertex mass [GeV]",           "", hdir );
      // 	makeLocalStackPlots( "truthVtx_nOutP", type, reg, "n truth vertex outgoing particles", "", hdir );
      // 	// truth vertices -- dark pion decays
      // 	makeLocalStackPlots( "truthVtxPid_n",     type, reg, "n truth dark pion decay vertices",                  "", hdir );
      // 	makeLocalStackPlots( "truthVtxPid_z",     type, reg, "truth dark pion decay vertex z-pos [mm]",           "", hdir );
      // 	makeLocalStackPlots( "truthVtxPid_r",     type, reg, "truth dark pion decay vertex r-pos [mm]",           "", hdir );
      // 	makeLocalStackPlots( "truthVtxPid_pt",    type, reg, "truth dark pion decay vertex p_{T} [GeV]",          "", hdir );
      // 	makeLocalStackPlots( "truthVtxPid_eta",   type, reg, "truth dark pion decay vertex eta",                  "", hdir );
      // 	makeLocalStackPlots( "truthVtxPid_phi",   type, reg, "truth dark pion decay vertex phi",                  "", hdir );
      // 	makeLocalStackPlots( "truthVtxPid_mass",  type, reg, "truth dark pion decay vertex mass [GeV]",           "", hdir );
      // 	makeLocalStackPlots( "truthVtxPid_nOutP", type, reg, "n truth dark pion decay vertex outgoing particles", "", hdir );
      // } // end if mc
      
    } // end loop over plot regions
    
  } // end loop over plot types
  
}
