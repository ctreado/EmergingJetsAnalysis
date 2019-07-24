// ROOT macro to run quick plot tests w/ TTree->Draw() for MC samples

void ttree_draw_test_mc() {

  gROOT->ProcessLine("#include <vector>");
  gROOT->ProcessLine("#include <string>");
  gInterpreter->GenerateDictionary("vector<vector<int>>", "vector");
  gInterpreter->GenerateDictionary("vector<vector<string>>", "vector");
  
  // build signal points
  std::vector<TString> dsid;
  //dsid.push_back( "312004" );
  dsid.push_back( "312008" );
  //dsid.push_back( "312017" );
  //dsid.push_back( "312022" );
  //dsid.push_back( "312028" );
  //dsid.push_back( "312031" );
  //dsid.push_back( "312039" );
  //dsid.push_back( "312046" );
  //dsid.push_back( "312052" );
  //dsid.push_back( "312060" );
  //dsid.push_back( "312066" );
  //dsid.push_back( "312067" );
  //dsid.push_back( "312075" );
  //dsid.push_back( "312080" );
  //dsid.push_back( "312090" );
  std::vector<TString> point;
  //point.push_back( "A_1400_20"  );
  point.push_back( "A_1000_150" );
  //point.push_back( "A_600_1"    );
  //point.push_back( "B_1400_20"  );
  //point.push_back( "B_1000_5"   );
  //point.push_back( "B_600_300"  );
  //point.push_back( "C_1400_75"  );
  //point.push_back( "C_1000_5"   );
  //point.push_back( "C_600_2"    );
  //point.push_back( "D_1400_2"   );
  //point.push_back( "D_1000_1"   );
  //point.push_back( "D_600_300"  );
  //point.push_back( "E_1400_75"  );
  //point.push_back( "E_1000_150" );
  //point.push_back( "E_600_0p5"  );

  // set path + file names --> make sure $EJ_PATH set to local repo dir: 'export EJ_PATH=$(pwd)'
  TString path = "$EJ_PATH/../run/local.MC16d";
  TString fp1   = ".EJ_Model";
  TString fp2   = "/data-tree/";
  TString fn1   = "mc16_13TeV.";
  TString fn2   = ".Pythia8EvtGen_A14NNPDF23LO_EJ_Model";
  TString fn3   = "_4jetFilter.deriv.DAOD_EXOT23.e7515_s3126_r10739_p3719.root";
  std::vector<TString> fpath;
  std::vector<TString> fname;
  for ( size_t i = 0; i != dsid.size(); ++i ) {
    fpath.push_back( path + "." + dsid.at(i) + fp1 + point.at(i) + fp2 ); // single runs
    //fpath.push_back( path       + fp2                                  );
    fname.push_back( fn1        + dsid.at(i) + fn2 + point.at(i) + fn3 );
  }

  // initialize canvas, file, and tree + loop over samples
  TCanvas *c = 0;
  TFile   *f = 0;
  TTree   *t = 0;
  for ( size_t i = 0; i != fname.size(); ++i ) {
    // set canvas
    //c = new TCanvas( "c"+dsid.at(i), "c"+dsid.at(i) );
    
    // open file
    f = TFile::Open( fpath.at(i) + fname.at(i), "READ" );
    if ( !f ) std::cout << "ZERO POINTER"                              << std::endl;
    else      std::cout << "file: "       << fpath.at(i) + fname.at(i) << std::endl;

    // cd into ntuple directory
    f->cd("EJsMiniNtup");

    // get nominal tree
    t = (TTree*)gDirectory->Get("nominal");

    std::vector<float>* darkJet_pt = 0;
    t->SetBranchAddress( "darkJet_pt", &darkJet_pt );

    for ( Long64_t j = 0; j != t->GetEntries(); ++j ) {
      t->GetEntry(j);
      // std::cout << "entry " << j << ": ";
      // for ( size_t k = 0; k != darkJet_pt->size(); ++k )
      // 	//if ( j == 5 || j == 50 )
      // 	  std::cout << darkJet_pt->at(k) << " ";
      // //if ( j == 5 || j == 50 )
      // 	std::cout << std::endl;
      std::cout << "entry " << j << ": " << darkJet_pt->size() << std::endl;
    }
    

    // draw variables
    //t->Draw("track_isSelected","track_passSel==0");

    //t->Draw("truthPart_pt","truthPart_pt<10"); 
    //t->Draw("truthPart_pdgId","truthPart_barcode==5000");
    //t->Draw("truthPart_prodVtx_r","truthPart_prodVtx_r!=std::numeric_limits<double>   :: quiet_NaN();");
    //t->Draw("truthPart_prodVtx_r","truthPart_hasProdVtx");
    //t->Draw("truthVtx_llpDecay");
    //t->Draw("jet_GhostTruth_pVtx_llpDecay");

  }
 
}
