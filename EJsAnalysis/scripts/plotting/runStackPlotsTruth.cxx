#include <vector>

#include "makeStackPlots.cxx"
#include "makeCutflowStackPlots.cxx"

void runStackPlotsTruth()
{ 
  std::vector<TString> ptitle;
  //ptitle.push_back( "modelA truth (mc15 update)"       );
  //ptitle.push_back( "modelB truth (mc15 update)"       );
  //ptitle.push_back( "modelC truth (mc15 update)"       );
  //ptitle.push_back( "modelD truth (mc15 update)"       );
  //ptitle.push_back( "modelE truth (mc15 update)"       );
  //ptitle.push_back( "modelA truth (mc15 old-official)" );
  //ptitle.push_back( "modelB truth (mc15 old-official)" );
  //ptitle.push_back( "modelC truth (mc15 old-official)" );
  //ptitle.push_back( "modelD truth (mc15 old-official)" );
  //ptitle.push_back( "modelE truth (mc15 old-official)" );
  ptitle.push_back( "ctau-300 truth (mc15 update)" );
  //ptitle.push_back( "ctau-150 truth (mc15 update)" );
  //ptitle.push_back( "ctau-75 truth (mc15 update)"  );
  //ptitle.push_back( "ctau-20 truth (mc15 update)"  );
  ptitle.push_back( "ctau-5 truth (mc15 update)"   );
  //ptitle.push_back( "ctau-2 truth (mc15 update)"   );
  //ptitle.push_back( "ctau-1 truth (mc15 update)"   );
  ptitle.push_back( "ctau-0.5 truth (mc15 update)" );
  //ptitle.push_back( "ctau-300 truth (mc15 old-official)" );
  //ptitle.push_back( "ctau-150 truth (mc15 old-official)" );
  //ptitle.push_back( "ctau-75 truth (mc15 old-official)"  );
  //ptitle.push_back( "ctau-20 truth (mc15 old-official)"  );
  //ptitle.push_back( "ctau-5 truth (mc15 old-official)"   );
  //ptitle.push_back( "xdm-1400 ctau-300 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-1000 ctau-300 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-600 ctau-300 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-1400 ctau-150 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-1000 ctau-150 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-600 ctau-150 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-1400 ctau-75 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-1000 ctau-75 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-600 ctau-75 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-1400 ctau-20 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-1000 ctau-20 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-600 ctau-20 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-1400 ctau-5 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-1000 ctau-5 truth (mc15 old vs new)" );
  //ptitle.push_back( "xdm-600 ctau-5 truth (mc15 old vs new)" );
  

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
    if ( lowtitle.Contains( "truth" ) ) {
      if      ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "modela"   ) ) ptype = "truth_mc15update_modelA";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "modelb"   ) ) ptype = "truth_mc15update_modelB";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "modelc"   ) ) ptype = "truth_mc15update_modelC";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "modeld"   ) ) ptype = "truth_mc15update_modelD";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "modele"   ) ) ptype = "truth_mc15update_modelE";
      else if ( lowtitle.Contains( "old-off" ) && lowtitle.Contains( "modela"   ) ) ptype = "truth_mc15oldoff_modelA";
      else if ( lowtitle.Contains( "old-off" ) && lowtitle.Contains( "modelb"   ) ) ptype = "truth_mc15oldoff_modelB";
      else if ( lowtitle.Contains( "old-off" ) && lowtitle.Contains( "modelc"   ) ) ptype = "truth_mc15oldoff_modelC";
      else if ( lowtitle.Contains( "old-off" ) && lowtitle.Contains( "modeld"   ) ) ptype = "truth_mc15oldoff_modelD";
      else if ( lowtitle.Contains( "old-off" ) && lowtitle.Contains( "modele"   ) ) ptype = "truth_mc15oldoff_modelE";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "ctau-300" ) ) ptype = "truth_mc15update_ctau300";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "ctau-150" ) ) ptype = "truth_mc15update_ctau150";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "ctau-75"  ) ) ptype = "truth_mc15update_ctau75";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "ctau-20"  ) ) ptype = "truth_mc15update_ctau20";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "ctau-5"   ) ) ptype = "truth_mc15update_ctau5";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "ctau-2"   ) ) ptype = "truth_mc15update_ctau2";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "ctau-1"   ) ) ptype = "truth_mc15update_ctau1";
      else if ( lowtitle.Contains( "update"  ) && lowtitle.Contains( "ctau-0.5" ) ) ptype = "truth_mc15update_ctau0p5";
      else if ( lowtitle.Contains( "old-off" ) && lowtitle.Contains( "ctau-300" ) ) ptype = "truth_mc15oldoff_ctau300";
      else if ( lowtitle.Contains( "old-off" ) && lowtitle.Contains( "ctau-150" ) ) ptype = "truth_mc15oldoff_ctau150";
      else if ( lowtitle.Contains( "old-off" ) && lowtitle.Contains( "ctau-75"  ) ) ptype = "truth_mc15oldoff_ctau75";
      else if ( lowtitle.Contains( "old-off" ) && lowtitle.Contains( "ctau-20"  ) ) ptype = "truth_mc15oldoff_ctau20";
      else if ( lowtitle.Contains( "old-off" ) && lowtitle.Contains( "ctau-5"   ) ) ptype = "truth_mc15oldoff_ctau5";
      else if ( lowtitle.Contains( "vs" ) ) {
	if      ( lowtitle.Contains( "xdm-1400" ) && lowtitle.Contains( "ctau-300" ) ) ptype = "truth_mc15vs_xdm1400_ctau300";
	else if ( lowtitle.Contains( "xdm-1000" ) && lowtitle.Contains( "ctau-300" ) ) ptype = "truth_mc15vs_xdm1000_ctau300";
	else if ( lowtitle.Contains( "xdm-600"  ) && lowtitle.Contains( "ctau-300" ) ) ptype = "truth_mc15vs_xdm600_ctau300";
	else if ( lowtitle.Contains( "xdm-1400" ) && lowtitle.Contains( "ctau-150" ) ) ptype = "truth_mc15vs_xdm1400_ctau150";
	else if ( lowtitle.Contains( "xdm-1000" ) && lowtitle.Contains( "ctau-150" ) ) ptype = "truth_mc15vs_xdm1000_ctau150";
	else if ( lowtitle.Contains( "xdm-600"  ) && lowtitle.Contains( "ctau-150" ) ) ptype = "truth_mc15vs_xdm600_ctau150";
	else if ( lowtitle.Contains( "xdm-1400" ) && lowtitle.Contains( "ctau-75"  ) ) ptype = "truth_mc15vs_xdm1400_ctau75";
	else if ( lowtitle.Contains( "xdm-1000" ) && lowtitle.Contains( "ctau-75"  ) ) ptype = "truth_mc15vs_xdm1000_ctau75";
	else if ( lowtitle.Contains( "xdm-600"  ) && lowtitle.Contains( "ctau-75"  ) ) ptype = "truth_mc15vs_xdm600_ctau75";
	else if ( lowtitle.Contains( "xdm-1400" ) && lowtitle.Contains( "ctau-20"  ) ) ptype = "truth_mc15vs_xdm1400_ctau20";
	else if ( lowtitle.Contains( "xdm-1000" ) && lowtitle.Contains( "ctau-20"  ) ) ptype = "truth_mc15vs_xdm1000_ctau20";
	else if ( lowtitle.Contains( "xdm-600"  ) && lowtitle.Contains( "ctau-20"  ) ) ptype = "truth_mc15vs_xdm600_ctau20";
	else if ( lowtitle.Contains( "xdm-1400" ) && lowtitle.Contains( "ctau-5"   ) ) ptype = "truth_mc15vs_xdm1400_ctau5";
	else if ( lowtitle.Contains( "xdm-1000" ) && lowtitle.Contains( "ctau-5"   ) ) ptype = "truth_mc15vs_xdm1000_ctau5";
	else if ( lowtitle.Contains( "xdm-600"  ) && lowtitle.Contains( "ctau-5"   ) ) ptype = "truth_mc15vs_xdm600_ctau5";
      }
    }

    // loop over plot regions
    for ( size_t j = 0; j != pregion.size(); ++j ) {
      
      TString region       = pregion .at(j);
      TString region_title = region; 
      if      ( region == "all"    ) region_title = "all regions";
      else if ( region == "signal" ) region_title = "signal region";
      else if ( region == "valid"  ) region_title = "validation region";
      
      TString title  = ptitle.at(i) + ": " + region_title;   

      // truth jets
      //makeStackPlots( "NTruthJetHt", title, "N-truth-jet H_{T} [GeV]", "", ptype, region );
      
      makeStackPlots( "truthJet_n",     title, "n truth jets",           "", ptype, region );
      makeStackPlots( "truthJet_pt",    title, "truth jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthJet_pt_l",  title, "truth jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthJet_pt_m",  title, "truth jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthJet_pt_s",  title, "truth jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthJet_eta",   title, "truth jet eta",          "", ptype, region );
      makeStackPlots( "truthJet_phi",   title, "truth jet phi",          "", ptype, region );
      makeStackPlots( "truthJet_E",     title, "truth jet energy [GeV]", "", ptype, region );
      makeStackPlots( "truthJet_M",     title, "truth jet mass [GeV]",   "", ptype, region );
      makeStackPlots( "truthJet_rapid", title, "truth jet rapidity",     "", ptype, region );

      makeStackPlots( "truthJet_girth",          title, "truth jet girth",                                    "", ptype, region );
      makeStackPlots( "truthJet_numConstit",     title, "n truth jet constituents",                           "", ptype, region );
      makeStackPlots( "truthJet_constitPt",      title, "truth jet constituent sum-p_{T} [GeV]",              "", ptype, region );
      makeStackPlots( "truthJet_constit_dR",     title, "truth jet - constituent dR",                         "", ptype, region );
      makeStackPlots( "truthJet_constit_pt",     title, "truth jet constituent p_{T} [GeV]",                  "", ptype, region );
      makeStackPlots( "truthJet_constit_eta",    title, "truth jet constituent eta",                          "", ptype, region );
      makeStackPlots( "truthJet_constit_phi",    title, "truth jet constituent phi",                          "", ptype, region );
      makeStackPlots( "truthJet_constit_E",      title, "truth jet constituent energy [GeV]",                 "", ptype, region );
      makeStackPlots( "truthJet_constit_pdgId",  title, "truth jet constituent pdgId",                        "", ptype, region );
      makeStackPlots( "truthJet_constit_pVtx_r", title, "truth jet constituent production vertex r-pos [mm]", "", ptype, region );
      makeStackPlots( "truthJet_numChrgConstit", title, "n truth jet charged constituents",                   "", ptype, region );
      makeStackPlots( "truthJet_numVisConstit",  title, "n truth jet visible constituents",                   "", ptype, region );

      makeStackPlots( "truthJet_tpCount",       title, "truth-jet-matched truth particle count",           "", ptype, region );
      makeStackPlots( "truthJet_tpPt",          title, "truth-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthJet_tpPt_l",        title, "truth-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthJet_tpPt_m",        title, "truth-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthJet_tpPt_s",        title, "truth-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthJet_tp_dR",         title, "truth-jet - matched-truth-particle dR",            "", ptype, region );
      makeStackPlots( "truthJet_tp_pdgId",      title, "truth-jet-matched truth particle pdgId",           "", ptype, region );
      makeStackPlots( "truthJet_tpChrgCount",   title, "truth-jet-matched charged truth particle count",   "", ptype, region );
      makeStackPlots( "truthJet_tpVisCount",    title, "truth-jet-matched visible truth particle count",   "", ptype, region );
      makeStackPlots( "truthJet_tpDarkCount",   title, "truth-jet-matched dark truth particle count",      "", ptype, region );
      makeStackPlots( "truthJet_tpPidCount",    title, "truth-jet-matched dark pion count",                "", ptype, region );
      makeStackPlots( "truthJet_tpOffPidCount", title, "truth-jet-matched off-diagonal dark pion count",   "", ptype, region );
      makeStackPlots( "truthJet_tpAllPidCount", title, "truth-jet-matched inclusive dark pion count",      "", ptype, region );
	
      makeStackPlots( "truthJet_truthVtxCount",       title, "truth-jet-matched truth vertex count",                              "", ptype, region );
      makeStackPlots( "truthJet_truthVtxPt",          title, "truth-jet-matched truth vertex sum-p_{T} [GeV]",                    "", ptype, region );
      makeStackPlots( "truthJet_truthVtx_dR",         title, "truth-jet - matched-truth vertex dR",                               "", ptype, region );
      makeStackPlots( "truthJet_truthVtx_r",          title, "truth-jet-matched truth vertex r-pos [mm]",                         "", ptype, region );
      makeStackPlots( "truthJet_truthVtx_mass",       title, "truth-jet-matched truth vertex mass [GeV]",                         "", ptype, region );
      makeStackPlots( "truthJet_truthVtxPidCount",    title, "truth-jet-matched truth dark pion decay vertex count",              "", ptype, region );
      makeStackPlots( "truthJet_truthVtxOffPidCount", title, "truth-jet-matched truth off-diagonal dark pion decay vertex count", "", ptype, region );
      makeStackPlots( "truthJet_truthVtxAllPidCount", title, "truth-jet-matched truth inclusive dark pion decay vertex count",    "", ptype, region );
      makeStackPlots( "truthJet_truthVtxDispCount",   title, "truth-jet-matched displaced (r > 0 mm) truth vertex count",         "", ptype, region );

      // truth "emerging" jets (dark-matched)
      makeStackPlots( "truthEJ_n",     title, "n truth emerging jets",           "", ptype, region );
      makeStackPlots( "truthEJ_pt",    title, "truth emerging jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthEJ_pt_l",  title, "truth emerging jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthEJ_pt_m",  title, "truth emerging jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthEJ_pt_s",  title, "truth emerging jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthEJ_eta",   title, "truth emerging jet eta",          "", ptype, region );
      makeStackPlots( "truthEJ_phi",   title, "truth emerging jet phi",          "", ptype, region );
      makeStackPlots( "truthEJ_E",     title, "truth emerging jet energy [GeV]", "", ptype, region );
      makeStackPlots( "truthEJ_M",     title, "truth emerging jet mass [GeV]",   "", ptype, region );
      makeStackPlots( "truthEJ_rapid", title, "truth emerging jet rapidity",     "", ptype, region );
      
      makeStackPlots( "truthEJ_girth",          title, "truth emerging jet girth",                                    "", ptype, region );
      makeStackPlots( "truthEJ_numConstit",     title, "n truth emerging jet constituents",                           "", ptype, region );
      makeStackPlots( "truthEJ_constitPt",      title, "truth emerging jet constituent sum-p_{T} [GeV]",              "", ptype, region );
      makeStackPlots( "truthEJ_constit_dR",     title, "truth emerging jet - constituent dR",                         "", ptype, region );
      makeStackPlots( "truthEJ_constit_pt",     title, "truth emerging jet constituent p_{T} [GeV]",                  "", ptype, region );
      makeStackPlots( "truthEJ_constit_eta",    title, "truth emerging jet constituent eta",                          "", ptype, region );
      makeStackPlots( "truthEJ_constit_phi",    title, "truth emerging jet constituent phi",                          "", ptype, region );
      makeStackPlots( "truthEJ_constit_E",      title, "truth emerging jet constituent energy [GeV]",                 "", ptype, region );
      makeStackPlots( "truthEJ_constit_pdgId",  title, "truth emerging jet constituent pdgId",                        "", ptype, region );
      makeStackPlots( "truthEJ_constit_pVtx_r", title, "truth emerging jet constituent production vertex r-pos [mm]", "", ptype, region );
      makeStackPlots( "truthEJ_numChrgConstit", title, "n truth emerging jet charged constituents",                   "", ptype, region );
      makeStackPlots( "truthEJ_numVisConstit",  title, "n truth emerging jet visible constituents",                   "", ptype, region );

      makeStackPlots( "truthEJ_tpCount",       title, "truth-emerging-jet-matched truth particle count",           "", ptype, region );
      makeStackPlots( "truthEJ_tpPt",          title, "truth-emerging-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthEJ_tpPt_l",        title, "truth-emerging-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthEJ_tpPt_m",        title, "truth-emerging-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthEJ_tpPt_s",        title, "truth-emerging-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthEJ_tp_dR",         title, "truth-emerging-jet - matched-truth-particle dR",            "", ptype, region );
      makeStackPlots( "truthEJ_tp_pdgId",      title, "truth-emerging-jet-matched truth particle pdgId",           "", ptype, region );
      makeStackPlots( "truthEJ_tpChrgCount",   title, "truth-emerging-jet-matched charged truth particle count",   "", ptype, region );
      makeStackPlots( "truthEJ_tpVisCount",    title, "truth-emerging-jet-matched visible truth particle count",   "", ptype, region );
      makeStackPlots( "truthEJ_tpDarkCount",   title, "truth-emerging-jet-matched dark truth particle count",      "", ptype, region );
      makeStackPlots( "truthEJ_tpPidCount",    title, "truth-emerging-jet-matched dark pion count",                "", ptype, region );
      makeStackPlots( "truthEJ_tpOffPidCount", title, "truth-emerging-jet-matched off-diagonal dark pion count",   "", ptype, region );
      makeStackPlots( "truthEJ_tpAllPidCount", title, "truth-emerging-jet-matched inclusive dark pion count",      "", ptype, region );
	
      makeStackPlots( "truthEJ_truthVtxCount",       title, "truth-emerging-jet-matched truth vertex count",                              "", ptype, region );
      makeStackPlots( "truthEJ_truthVtxPt",          title, "truth-emerging-jet-matched truth vertex sum-p_{T} [GeV]",                    "", ptype, region );
      makeStackPlots( "truthEJ_truthVtx_dR",         title, "truth-emerging-jet - matched-truth vertex dR",                               "", ptype, region );
      makeStackPlots( "truthEJ_truthVtx_r",          title, "truth-emerging-jet-matched truth vertex r-pos [mm]",                         "", ptype, region );
      makeStackPlots( "truthEJ_truthVtx_mass",       title, "truth-emerging-jet-matched truth vertex mass [GeV]",                         "", ptype, region );
      makeStackPlots( "truthEJ_truthVtxPidCount",    title, "truth-emerging-jet-matched truth dark pion decay vertex count",              "", ptype, region );
      makeStackPlots( "truthEJ_truthVtxOffPidCount", title, "truth-emerging-jet-matched truth off-diagonal dark pion decay vertex count", "", ptype, region );
      makeStackPlots( "truthEJ_truthVtxAllPidCount", title, "truth-emerging-jet-matched truth inclusive dark pion decay vertex count",    "", ptype, region );
      makeStackPlots( "truthEJ_truthVtxDispCount",   title, "truth-emerging-jet-matched displaced (r > 0 mm) truth vertex count",         "", ptype, region );

      // truth "qcd" jets (not dark-matched)
      makeStackPlots( "truthQCDJ_n",     title, "n truth qcd jets",           "", ptype, region );
      makeStackPlots( "truthQCDJ_pt",    title, "truth qcd jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthQCDJ_pt_l",  title, "truth qcd jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthQCDJ_pt_m",  title, "truth qcd jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthQCDJ_pt_s",  title, "truth qcd jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "truthQCDJ_eta",   title, "truth qcd jet eta",          "", ptype, region );
      makeStackPlots( "truthQCDJ_phi",   title, "truth qcd jet phi",          "", ptype, region );
      makeStackPlots( "truthQCDJ_E",     title, "truth qcd jet energy [GeV]", "", ptype, region );
      makeStackPlots( "truthQCDJ_M",     title, "truth qcd jet mass [GeV]",   "", ptype, region );
      makeStackPlots( "truthQCDJ_rapid", title, "truth qcd jet rapidity",     "", ptype, region );
      
      makeStackPlots( "truthQCDJ_girth",          title, "truth qcd jet girth",                                    "", ptype, region );
      makeStackPlots( "truthQCDJ_numConstit",     title, "n truth qcd jet constituents",                           "", ptype, region );
      makeStackPlots( "truthQCDJ_constitPt",      title, "truth qcd jet constituent sum-p_{T} [GeV]",              "", ptype, region );
      makeStackPlots( "truthQCDJ_constit_dR",     title, "truth qcd jet - constituent dR",                         "", ptype, region );
      makeStackPlots( "truthQCDJ_constit_pt",     title, "truth qcd jet constituent p_{T} [GeV]",                  "", ptype, region );
      makeStackPlots( "truthQCDJ_constit_eta",    title, "truth qcd jet constituent eta",                          "", ptype, region );
      makeStackPlots( "truthQCDJ_constit_phi",    title, "truth qcd jet constituent phi",                          "", ptype, region );
      makeStackPlots( "truthQCDJ_constit_E",      title, "truth qcd jet constituent energy [GeV]",                 "", ptype, region );
      makeStackPlots( "truthQCDJ_constit_pdgId",  title, "truth qcd jet constituent pdgId",                        "", ptype, region );
      makeStackPlots( "truthQCDJ_constit_pVtx_r", title, "truth qcd jet constituent production vertex r-pos [mm]", "", ptype, region );
      makeStackPlots( "truthQCDJ_numChrgConstit", title, "n truth qcd jet charged constituents",                   "", ptype, region );
      makeStackPlots( "truthQCDJ_numVisConstit",  title, "n truth qcd jet visible constituents",                   "", ptype, region );

      makeStackPlots( "truthQCDJ_tpCount",       title, "truth-qcd-jet-matched truth particle count",           "", ptype, region );
      makeStackPlots( "truthQCDJ_tpPt",          title, "truth-qcd-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthQCDJ_tpPt_l",        title, "truth-qcd-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthQCDJ_tpPt_m",        title, "truth-qcd-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthQCDJ_tpPt_s",        title, "truth-qcd-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "truthQCDJ_tp_dR",         title, "truth-qcd-jet - matched-truth-particle dR",            "", ptype, region );
      makeStackPlots( "truthQCDJ_tp_pdgId",      title, "truth-qcd-jet-matched truth particle pdgId",           "", ptype, region );
      makeStackPlots( "truthQCDJ_tpChrgCount",   title, "truth-qcd-jet-matched charged truth particle count",   "", ptype, region );
      makeStackPlots( "truthQCDJ_tpVisCount",    title, "truth-qcd-jet-matched visible truth particle count",   "", ptype, region );
      makeStackPlots( "truthQCDJ_tpDarkCount",   title, "truth-qcd-jet-matched dark truth particle count",      "", ptype, region );
      makeStackPlots( "truthQCDJ_tpPidCount",    title, "truth-qcd-jet-matched dark pion count",                "", ptype, region );
      makeStackPlots( "truthQCDJ_tpOffPidCount", title, "truth-qcd-jet-matched off-diagonal dark pion count",   "", ptype, region );
      makeStackPlots( "truthQCDJ_tpAllPidCount", title, "truth-qcd-jet-matched inclusive dark pion count",      "", ptype, region );
	
      makeStackPlots( "truthQCDJ_truthVtxCount",       title, "truth-qcd-jet-matched truth vertex count",                              "", ptype, region );
      makeStackPlots( "truthQCDJ_truthVtxPt",          title, "truth-qcd-jet-matched truth vertex sum-p_{T} [GeV]",                    "", ptype, region );
      makeStackPlots( "truthQCDJ_truthVtx_dR",         title, "truth-qcd-jet - matched-truth vertex dR",                               "", ptype, region );
      makeStackPlots( "truthQCDJ_truthVtx_r",          title, "truth-qcd-jet-matched truth vertex r-pos [mm]",                         "", ptype, region );
      makeStackPlots( "truthQCDJ_truthVtx_mass",       title, "truth-qcd-jet-matched truth vertex mass [GeV]",                         "", ptype, region );
      makeStackPlots( "truthQCDJ_truthVtxPidCount",    title, "truth-qcd-jet-matched truth dark pion decay vertex count",              "", ptype, region );
      makeStackPlots( "truthQCDJ_truthVtxOffPidCount", title, "truth-qcd-jet-matched truth off-diagonal dark pion decay vertex count", "", ptype, region );
      makeStackPlots( "truthQCDJ_truthVtxAllPidCount", title, "truth-qcd-jet-matched truth inclusive dark pion decay vertex count",    "", ptype, region );
      makeStackPlots( "truthQCDJ_truthVtxDispCount",   title, "truth-qcd-jet-matched displaced (r > 0 mm) truth vertex count",         "", ptype, region );


      // dark jets
      makeStackPlots( "darkJet_n",     title, "n dark jets",           "", ptype, region );
      makeStackPlots( "darkJet_pt",    title, "dark jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "darkJet_pt_l",  title, "dark jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "darkJet_pt_m",  title, "dark jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "darkJet_pt_s",  title, "dark jet p_{T} [GeV]",  "", ptype, region );
      makeStackPlots( "darkJet_eta",   title, "dark jet eta",          "", ptype, region );
      makeStackPlots( "darkJet_phi",   title, "dark jet phi",          "", ptype, region );
      makeStackPlots( "darkJet_E",     title, "dark jet energy [GeV]", "", ptype, region );
      makeStackPlots( "darkJet_M",     title, "dark jet mass [GeV]",   "", ptype, region );
      makeStackPlots( "darkJet_rapid", title, "dark jet rapidity",     "", ptype, region );
      
      makeStackPlots( "darkJet_girth",          title, "dark jet girth",                               "", ptype, region );
      makeStackPlots( "darkJet_numConstit",     title, "n dark jet constituents",                      "", ptype, region );
      makeStackPlots( "darkJet_constitPt",      title, "dark jet constituent sum-p_{T} [GeV]",         "", ptype, region );
      makeStackPlots( "darkJet_constit_dR",     title, "dark jet - constituent dR",                    "", ptype, region );
      makeStackPlots( "darkJet_constit_pt",     title, "dark jet constituent p_{T} [GeV]",             "", ptype, region );
      makeStackPlots( "darkJet_constit_eta",    title, "dark jet constituent eta",                     "", ptype, region );
      makeStackPlots( "darkJet_constit_phi",    title, "dark jet constituent phi",                     "", ptype, region );
      makeStackPlots( "darkJet_constit_E",      title, "dark jet constituent energy [GeV]",            "", ptype, region );
      makeStackPlots( "darkJet_constit_pdgId",  title, "dark jet constituent pdgId",                   "", ptype, region );
      makeStackPlots( "darkJet_constit_dVtx_r", title, "dark jet constituent decay vertex r-pos [mm]", "", ptype, region );

      makeStackPlots( "darkJet_tpCount",       title, "dark-jet-matched truth particle count",           "", ptype, region );
      makeStackPlots( "darkJet_tpPt",          title, "dark-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "darkJet_tpPt_l",        title, "dark-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "darkJet_tpPt_m",        title, "dark-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "darkJet_tpPt_s",        title, "dark-jet-matched truth particle sum-p_{T} [GeV]", "", ptype, region );
      makeStackPlots( "darkJet_tp_dR",         title, "dark-jet - matched-truth-particle dR",            "", ptype, region );
      makeStackPlots( "darkJet_tp_pdgId",      title, "dark-jet-matched truth particle pdgId",           "", ptype, region );
      makeStackPlots( "darkJet_tpChrgCount",   title, "dark-jet-matched charged truth particle count",   "", ptype, region );
      makeStackPlots( "darkJet_tpVisCount",    title, "dark-jet-matched visible truth particle count",   "", ptype, region );
      makeStackPlots( "darkJet_tpDarkCount",   title, "dark-jet-matched dark truth particle count",      "", ptype, region );
      makeStackPlots( "darkJet_tpPidCount",    title, "dark-jet-matched dark pion count",                "", ptype, region );
      makeStackPlots( "darkJet_tpOffPidCount", title, "dark-jet-matched off-diagonal dark pion count",   "", ptype, region );
      makeStackPlots( "darkJet_tpAllPidCount", title, "dark-jet-matched inclusive dark pion count",      "", ptype, region );

      makeStackPlots( "darkJet_truthVtxCount",       title, "dark-jet-matched truth vertex count",                              "", ptype, region );
      makeStackPlots( "darkJet_truthVtxPt",          title, "dark-jet-matched truth vertex sum-p_{T} [GeV]",                    "", ptype, region );
      makeStackPlots( "darkJet_truthVtx_dR",         title, "dark-jet - matched-truth vertex dR",                               "", ptype, region );
      makeStackPlots( "darkJet_truthVtx_r",          title, "dark-jet-matched truth vertex r-pos [mm]",                         "", ptype, region );
      makeStackPlots( "darkJet_truthVtx_mass",       title, "dark-jet-matched truth vertex mass [GeV]",                         "", ptype, region );
      makeStackPlots( "darkJet_truthVtxPidCount",    title, "dark-jet-matched truth dark pion decay vertex count",              "", ptype, region );
      makeStackPlots( "darkJet_truthVtxOffPidCount", title, "dark-jet-matched truth off-diagonal dark pion decay vertex count", "", ptype, region );
      makeStackPlots( "darkJet_truthVtxAllPidCount", title, "dark-jet-matched truth inclusive dark pion decay vertex count",    "", ptype, region );
      makeStackPlots( "darkJet_truthVtxDispCount",   title, "dark-jet-matched displaced (r > 0 mm) truth vertex count",         "", ptype, region );

  
      // truth particles -- all
      makeStackPlots( "tp_n",                title, "n truth particles",                              "", ptype, region );
      makeStackPlots( "tp_pt",               title, "truth particle p_{T} [GeV]",                     "", ptype, region );
      makeStackPlots( "tp_eta",              title, "truth particle eta",                             "", ptype, region );
      makeStackPlots( "tp_phi",              title, "truth particle phi",                             "", ptype, region );
      makeStackPlots( "tp_E",                title, "truth particle energy [GeV]",                    "", ptype, region );
      makeStackPlots( "tp_M",                title, "truth particle mass [GeV]",                      "", ptype, region );
      makeStackPlots( "tp_sumPt",            title, "truth particle sum-p_{T} [GeV]",                 "", ptype, region );
      makeStackPlots( "tp_nCharged",         title, "n charged truth particles",                      "", ptype, region );
      makeStackPlots( "tp_sumPtCharged",     title, "charged truth particle sum-p_{T} [GeV]",         "", ptype, region );
      makeStackPlots( "tp_nStable",          title, "n stable truth particles",                       "", ptype, region );
      makeStackPlots( "tp_sumPtStable",      title, "stable truth particle sum-p_{T} [GeV]",          "", ptype, region );
      makeStackPlots( "tp_nVisible",         title, "n visible truth particles",                      "", ptype, region );
      makeStackPlots( "tp_sumPtVisible",     title, "visible truth particle sum-p_{T} [GeV]",         "", ptype, region );
      makeStackPlots( "tp_nDark",            title, "n dark truth particles",                         "", ptype, region );
      makeStackPlots( "tp_sumPtDark",        title, "dark truth particle sum-p_{T} [GeV]",            "", ptype, region );
      makeStackPlots( "tp_nChargedDark",     title, "n charged dark truth particles",                 "", ptype, region );
      makeStackPlots( "tp_sumPtChargedDark", title, "charged dark truth particle sum-p_{T} [GeV]",    "", ptype, region );
      // truth particles -- scalar mediators
      makeStackPlots( "Xd_n",            title, "n scalar mediators",                           "", ptype, region );
      makeStackPlots( "Xd_pt",           title, "scalar mediator p_{T} [GeV]",                  "", ptype, region );
      makeStackPlots( "Xd_eta",          title, "scalar mediator eta",                          "", ptype, region );
      makeStackPlots( "Xd_phi",          title, "scalar mediator phi",                          "", ptype, region );
      makeStackPlots( "Xd_E",            title, "scalar mediator energy [GeV]",                 "", ptype, region );
      makeStackPlots( "Xd_M",            title, "scalar mediator mass [GeV]",                   "", ptype, region );
      makeStackPlots( "Xd_charge",       title, "scalar mediator charge",                       "", ptype, region );
      makeStackPlots( "Xd_nParents",     title, "n scalar mediator parents",                    "", ptype, region );
      makeStackPlots( "Xd_parentPdgId",  title, "scalar mediator parent pdgId",                 "", ptype, region );
      makeStackPlots( "Xd_parentStatus", title, "scalar mediator parent status",                "", ptype, region );
      makeStackPlots( "Xd_nChildren",    title, "n scalar mediator children",                   "", ptype, region );
      makeStackPlots( "Xd_childPdgId",   title, "scalar mediator child pdgId",                  "", ptype, region );
      makeStackPlots( "Xd_childStatus",  title, "scalar mediator child status",                 "", ptype, region );
      makeStackPlots( "Xd_prodVtx_r",    title, "scalar mediator production vertex r-pos [mm]", "", ptype, region );
      makeStackPlots( "Xd_decayVtx_r",   title, "scalar mediator decay vertex r-pos [mm]",      "", ptype, region );
      // truth particles -- dark quarks
      makeStackPlots( "qd_n",            title, "n dark quarks",                           "", ptype, region );
      makeStackPlots( "qd_pt",           title, "dark quark p_{T} [GeV]",                  "", ptype, region );
      makeStackPlots( "qd_eta",          title, "dark quark eta",                          "", ptype, region );
      makeStackPlots( "qd_phi",          title, "dark quark phi",                          "", ptype, region );
      makeStackPlots( "qd_E",            title, "dark quark energy [GeV]",                 "", ptype, region );
      makeStackPlots( "qd_M",            title, "dark quark mass [GeV]",                   "", ptype, region );
      makeStackPlots( "qd_charge",       title, "dark quark charge",                       "", ptype, region );
      makeStackPlots( "qd_nParents",     title, "n dark quark parents",                    "", ptype, region );
      makeStackPlots( "qd_parentPdgId",  title, "dark quark parent pdgId",                 "", ptype, region );
      makeStackPlots( "qd_parentStatus", title, "dark quark parent status",                "", ptype, region );
      makeStackPlots( "qd_nChildren",    title, "n dark quark children",                   "", ptype, region );
      makeStackPlots( "qd_childPdgId",   title, "dark quark child pdgId",                  "", ptype, region );
      makeStackPlots( "qd_childStatus",  title, "dark quark child status",                 "", ptype, region );
      makeStackPlots( "qd_prodVtx_r",    title, "dark quark production vertex r-pos [mm]", "", ptype, region );
      makeStackPlots( "qd_decayVtx_r",   title, "dark quark decay vertex r-pos [mm]",      "", ptype, region );
      // truth particles -- dark pions
      makeStackPlots( "pid_n",            title, "n dark pions",                           "", ptype, region );
      makeStackPlots( "pid_pt",           title, "dark pion p_{T} [GeV]",                  "", ptype, region );
      makeStackPlots( "pid_eta",          title, "dark pion eta",                          "", ptype, region );
      makeStackPlots( "pid_phi",          title, "dark pion phi",                          "", ptype, region );
      makeStackPlots( "pid_E",            title, "dark pion energy [GeV]",                 "", ptype, region );
      makeStackPlots( "pid_M",            title, "dark pion mass [GeV]",                   "", ptype, region );
      makeStackPlots( "pid_charge",       title, "dark pion charge",                       "", ptype, region );
      makeStackPlots( "pid_nParents",     title, "n dark pion parents",                    "", ptype, region );
      makeStackPlots( "pid_parentPdgId",  title, "dark pion parent pdgId",                 "", ptype, region );
      makeStackPlots( "pid_parentStatus", title, "dark pion parent status",                "", ptype, region );
      makeStackPlots( "pid_nChildren",    title, "n dark pion children",                   "", ptype, region );
      makeStackPlots( "pid_childPdgId",   title, "dark pion child pdgId",                  "", ptype, region );
      makeStackPlots( "pid_childStatus",  title, "dark pion child status",                 "", ptype, region );
      makeStackPlots( "pid_prodVtx_r",    title, "dark pion production vertex r-pos [mm]", "", ptype, region );
      makeStackPlots( "pid_decayVtx_r",   title, "dark pion decay vertex r-pos [mm]",      "", ptype, region );
      // truth particles -- dark rhos
      makeStackPlots( "rhod_n",            title, "n dark rhos",                           "", ptype, region );
      makeStackPlots( "rhod_pt",           title, "dark rho p_{T} [GeV]",                  "", ptype, region );
      makeStackPlots( "rhod_eta",          title, "dark rho eta",                          "", ptype, region );
      makeStackPlots( "rhod_phi",          title, "dark rho phi",                          "", ptype, region );
      makeStackPlots( "rhod_E",            title, "dark rho energy [GeV]",                 "", ptype, region );
      makeStackPlots( "rhod_M",            title, "dark rho mass [GeV]",                   "", ptype, region );
      makeStackPlots( "rhod_charge",       title, "dark rho charge",                       "", ptype, region );
      makeStackPlots( "rhod_nParents",     title, "n dark rho parents",                    "", ptype, region );
      makeStackPlots( "rhod_parentPdgId",  title, "dark rho parent pdgId",                 "", ptype, region );
      makeStackPlots( "rhod_parentStatus", title, "dark rho parent status",                "", ptype, region );
      makeStackPlots( "rhod_nChildren",    title, "n dark rho children",                   "", ptype, region );
      makeStackPlots( "rhod_childPdgId",   title, "dark rho child pdgId",                  "", ptype, region );
      makeStackPlots( "rhod_childStatus",  title, "dark rho child status",                 "", ptype, region );
      makeStackPlots( "rhod_prodVtx_r",    title, "dark rho production vertex r-pos [mm]", "", ptype, region );
      makeStackPlots( "rhod_decayVtx_r",   title, "dark rho decay vertex r-pos [mm]",      "", ptype, region );
      // truth particles -- off-diagonal dark pions
      makeStackPlots( "offpid_n",            title, "n off-diagonal dark pions",                           "", ptype, region );
      makeStackPlots( "offpid_pt",           title, "off-diagonal dark pion p_{T} [GeV]",                  "", ptype, region );
      makeStackPlots( "offpid_eta",          title, "off-diagonal dark pion eta",                          "", ptype, region );
      makeStackPlots( "offpid_phi",          title, "off-diagonal dark pion phi",                          "", ptype, region );
      makeStackPlots( "offpid_E",            title, "off-diagonal dark pion energy [GeV]",                 "", ptype, region );
      makeStackPlots( "offpid_M",            title, "off-diagonal dark pion mass [GeV]",                   "", ptype, region );
      makeStackPlots( "offpid_charge",       title, "off-diagonal dark pion charge",                       "", ptype, region );
      makeStackPlots( "offpid_nParents",     title, "n off-diagonal dark pion parents",                    "", ptype, region );
      makeStackPlots( "offpid_parentPdgId",  title, "off-diagonal dark pion parent pdgId",                 "", ptype, region );
      makeStackPlots( "offpid_parentStatus", title, "off-diagonal dark pion parent status",                "", ptype, region );
      makeStackPlots( "offpid_nChildren",    title, "n off-diagonal dark pion children",                   "", ptype, region );
      makeStackPlots( "offpid_childPdgId",   title, "off-diagonal dark pion child pdgId",                  "", ptype, region );
      makeStackPlots( "offpid_childStatus",  title, "off-diagonal dark pion child status",                 "", ptype, region );
      makeStackPlots( "offpid_prodVtx_r",    title, "off-diagonal dark pion production vertex r-pos [mm]", "", ptype, region );
      makeStackPlots( "offpid_decayVtx_r",   title, "off-diagonal dark pion decay vertex r-pos [mm]",      "", ptype, region );
      // truth particles -- off-diagonal dark rhos
      makeStackPlots( "offrhod_n",            title, "n off-diagonal dark rhos",                           "", ptype, region );
      makeStackPlots( "offrhod_pt",           title, "off-diagonal dark rho p_{T} [GeV]",                  "", ptype, region );
      makeStackPlots( "offrhod_eta",          title, "off-diagonal dark rho eta",                          "", ptype, region );
      makeStackPlots( "offrhod_phi",          title, "off-diagonal dark rho phi",                          "", ptype, region );
      makeStackPlots( "offrhod_E",            title, "off-diagonal dark rho energy [GeV]",                 "", ptype, region );
      makeStackPlots( "offrhod_M",            title, "off-diagonal dark rho mass [GeV]",                   "", ptype, region );
      makeStackPlots( "offrhod_charge",       title, "off-diagonal dark rho charge",                       "", ptype, region );
      makeStackPlots( "offrhod_nParents",     title, "n off-diagonal dark rho parents",                    "", ptype, region );
      makeStackPlots( "offrhod_parentPdgId",  title, "off-diagonal dark rho parent pdgId",                 "", ptype, region );
      makeStackPlots( "offrhod_parentStatus", title, "off-diagonal dark rho parent status",                "", ptype, region );
      makeStackPlots( "offrhod_nChildren",    title, "n off-diagonal dark rho children",                   "", ptype, region );
      makeStackPlots( "offrhod_childPdgId",   title, "off-diagonal dark rho child pdgId",                  "", ptype, region );
      makeStackPlots( "offrhod_childStatus",  title, "off-diagonal dark rho child status",                 "", ptype, region );
      makeStackPlots( "offrhod_prodVtx_r",    title, "off-diagonal dark rho production vertex r-pos [mm]", "", ptype, region );
      makeStackPlots( "offrhod_decayVtx_r",   title, "off-diagonal dark rho decay vertex r-pos [mm]",      "", ptype, region );
      // truth particles -- inclusive dark pions (standard + off-diagonal)
      makeStackPlots( "allpid_n",            title, "n inclusive dark pions",                           "", ptype, region );
      makeStackPlots( "allpid_pt",           title, "inclusive dark pion p_{T} [GeV]",                  "", ptype, region );
      makeStackPlots( "allpid_eta",          title, "inclusive dark pion eta",                          "", ptype, region );
      makeStackPlots( "allpid_phi",          title, "inclusive dark pion phi",                          "", ptype, region );
      makeStackPlots( "allpid_E",            title, "inclusive dark pion energy [GeV]",                 "", ptype, region );
      makeStackPlots( "allpid_M",            title, "inclusive dark pion mass [GeV]",                   "", ptype, region );
      makeStackPlots( "allpid_charge",       title, "inclusive dark pion charge",                       "", ptype, region );
      makeStackPlots( "allpid_nParents",     title, "n inclusive dark pion parents",                    "", ptype, region );
      makeStackPlots( "allpid_parentPdgId",  title, "inclusive dark pion parent pdgId",                 "", ptype, region );
      makeStackPlots( "allpid_parentStatus", title, "inclusive dark pion parent status",                "", ptype, region );
      makeStackPlots( "allpid_nChildren",    title, "n inclusive dark pion children",                   "", ptype, region );
      makeStackPlots( "allpid_childPdgId",   title, "inclusive dark pion child pdgId",                  "", ptype, region );
      makeStackPlots( "allpid_childStatus",  title, "inclusive dark pion child status",                 "", ptype, region );
      makeStackPlots( "allpid_prodVtx_r",    title, "inclusive dark pion production vertex r-pos [mm]", "", ptype, region );
      makeStackPlots( "allpid_decayVtx_r",   title, "inclusive dark pion decay vertex r-pos [mm]",      "", ptype, region );
      // truth particles -- inclusive dark rhos (standard + off-diagonal)
      makeStackPlots( "allrhod_n",            title, "n inclusive dark rhos",                           "", ptype, region );
      makeStackPlots( "allrhod_pt",           title, "inclusive dark rho p_{T} [GeV]",                  "", ptype, region );
      makeStackPlots( "allrhod_eta",          title, "inclusive dark rho eta",                          "", ptype, region );
      makeStackPlots( "allrhod_phi",          title, "inclusive dark rho phi",                          "", ptype, region );
      makeStackPlots( "allrhod_E",            title, "inclusive dark rho energy [GeV]",                 "", ptype, region );
      makeStackPlots( "allrhod_M",            title, "inclusive dark rho mass [GeV]",                   "", ptype, region );
      makeStackPlots( "allrhod_charge",       title, "inclusive dark rho charge",                       "", ptype, region );
      makeStackPlots( "allrhod_nParents",     title, "n inclusive dark rho parents",                    "", ptype, region );
      makeStackPlots( "allrhod_parentPdgId",  title, "inclusive dark rho parent pdgId",                 "", ptype, region );
      makeStackPlots( "allrhod_parentStatus", title, "inclusive dark rho parent status",                "", ptype, region );
      makeStackPlots( "allrhod_nChildren",    title, "n inclusive dark rho children",                   "", ptype, region );
      makeStackPlots( "allrhod_childPdgId",   title, "inclusive dark rho child pdgId",                  "", ptype, region );
      makeStackPlots( "allrhod_childStatus",  title, "inclusive dark rho child status",                 "", ptype, region );
      makeStackPlots( "allrhod_prodVtx_r",    title, "inclusive dark rho production vertex r-pos [mm]", "", ptype, region );
      makeStackPlots( "allrhod_decayVtx_r",   title, "inclusive dark rho decay vertex r-pos [mm]",      "", ptype, region );


      // truth vertices
      makeStackPlots( "truthVtx_n",     title, "n truth vertices",                  "", ptype, region );
      makeStackPlots( "truthVtx_x",     title, "truth vertex x-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_y",     title, "truth vertex y-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_z",     title, "truth vertex z-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_r",     title, "truth vertex r-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_pt",    title, "truth vertex p_{T} [GeV]",          "", ptype, region );
      makeStackPlots( "truthVtx_eta",   title, "truth vertex eta",                  "", ptype, region );
      makeStackPlots( "truthVtx_phi",   title, "truth vertex phi",                  "", ptype, region );
      makeStackPlots( "truthVtx_mass",  title, "truth vertex mass [GeV]",           "", ptype, region );
      makeStackPlots( "truthVtx_nOutP", title, "n truth vertex outgoing particles", "", ptype, region );
      // truth vertices -- dark pion decays
      makeStackPlots( "truthVtx_pid_n",     title, "n truth dark pion decay vertices",                  "", ptype, region );
      makeStackPlots( "truthVtx_pid_x",     title, "truth dark pion decay vertex x-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_pid_y",     title, "truth dark pion decay vertex y-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_pid_z",     title, "truth dark pion decay vertex z-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_pid_r",     title, "truth dark pion decay vertex r-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_pid_pt",    title, "truth dark pion decay vertex p_{T} [GeV]",          "", ptype, region );
      makeStackPlots( "truthVtx_pid_eta",   title, "truth dark pion decay vertex eta",                  "", ptype, region );
      makeStackPlots( "truthVtx_pid_phi",   title, "truth dark pion decay vertex phi",                  "", ptype, region );
      makeStackPlots( "truthVtx_pid_mass",  title, "truth dark pion decay vertex mass [GeV]",           "", ptype, region );
      makeStackPlots( "truthVtx_pid_nOutP", title, "n truth dark pion decay vertex outgoing particles", "", ptype, region );
      // truth vertices -- off-diagonal dark pion decays
      makeStackPlots( "truthVtx_offpid_n",     title, "n truth off-diagonal dark pion decay vertices",                  "", ptype, region );
      makeStackPlots( "truthVtx_offpid_x",     title, "truth off-diagonal dark pion decay vertex x-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_offpid_y",     title, "truth off-diagonal dark pion decay vertex y-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_offpid_z",     title, "truth off-diagonal dark pion decay vertex z-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_offpid_r",     title, "truth off-diagonal dark pion decay vertex r-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_offpid_pt",    title, "truth off-diagonal dark pion decay vertex p_{T} [GeV]",          "", ptype, region );
      makeStackPlots( "truthVtx_offpid_eta",   title, "truth off-diagonal dark pion decay vertex eta",                  "", ptype, region );
      makeStackPlots( "truthVtx_offpid_phi",   title, "truth off-diagonal dark pion decay vertex phi",                  "", ptype, region );
      makeStackPlots( "truthVtx_offpid_mass",  title, "truth off-diagonal dark pion decay vertex mass [GeV]",           "", ptype, region );
      makeStackPlots( "truthVtx_offpid_nOutP", title, "n truth off-diagonal dark pion decay vertex outgoing particles", "", ptype, region );
      // truth vertices -- inclusive dark pion decays (standard + off-diagaonal)
      makeStackPlots( "truthVtx_allpid_n",     title, "n truth inclusive dark pion decay vertices",                  "", ptype, region );
      makeStackPlots( "truthVtx_allpid_x",     title, "truth inclusive dark pion decay vertex x-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_allpid_y",     title, "truth inclusive dark pion decay vertex y-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_allpid_z",     title, "truth inclusive dark pion decay vertex z-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_allpid_r",     title, "truth inclusive dark pion decay vertex r-pos [mm]",           "", ptype, region );
      makeStackPlots( "truthVtx_allpid_pt",    title, "truth inclusive dark pion decay vertex p_{T} [GeV]",          "", ptype, region );
      makeStackPlots( "truthVtx_allpid_eta",   title, "truth inclusive dark pion decay vertex eta",                  "", ptype, region );
      makeStackPlots( "truthVtx_allpid_phi",   title, "truth inclusive dark pion decay vertex phi",                  "", ptype, region );
      makeStackPlots( "truthVtx_allpid_mass",  title, "truth inclusive dark pion decay vertex mass [GeV]",           "", ptype, region );
      makeStackPlots( "truthVtx_allpid_nOutP", title, "n truth inclusive dark pion decay vertex outgoing particles", "", ptype, region );
      // truth vertices -- displaced
      makeStackPlots( "truthVtx_disp_n", title, "n displaced (r > 0 mm) truth vertices", "", ptype, region );
      
    } // end loop over regions

    // cutflows
    makeCutflowStackPlots( "cutflow",        ptitle.at(i) + " cutflow: all regions",       "", "", ptype );
    makeCutflowStackPlots( "cutflow_signal", ptitle.at(i) + " cutflow: signal region",     "", "", ptype );
    makeCutflowStackPlots( "cutflow_valid",  ptitle.at(i) + " cutflow: validation region", "", "", ptype );
    
  } // end loop over data types
  
}
