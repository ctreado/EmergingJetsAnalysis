// ROOT macro to run quick plot tests w/ TTree->Draw()

void ttree_draw_test_data() {
  
  // build signal points
  std::vector<TString> year;
  year.push_back( "data18" );
  year.push_back( "data17" );
  year.push_back( "data16" );
  year.push_back( "data15" );

  std::vector<TString> run;
  run.push_back( "00350144" );
  run.push_back( "00357451" );
  run.push_back( "00363830" ); // single data18
  run.push_back( "00331804" ); // single data17
  run.push_back( "00335022" );
  run.push_back( "00340030" );
  run.push_back( "00301973" );
  run.push_back( "00303208" ); // single data16
  run.push_back( "00309440" );
  run.push_back( "00280862" ); // single data15
  run.push_back( "00281411" );
  run.push_back( "00283608" );

  std::vector<TString> tag;
  tag.push_back( "f933_m1831_r10799_p3651"  );
  tag.push_back( "f958_m1831_r10799_p3651"  );
  tag.push_back( "f1002_m1831_r10799_p3651" );
  tag.push_back( "r10203_r10658_p3578"      );
  tag.push_back( "r10258_r10658_p3578"      );
  tag.push_back( "r10426_r10658_p3578"      );
  tag.push_back( "r9264_r10573_p3578"       );
  tag.push_back( "r9264_r10573_p3578"       );
  tag.push_back( "r9264_r10573_p3578"       );
  tag.push_back( "r9264_r10573_p3578"       );
  tag.push_back( "r9264_r10573_p3578"       );
  tag.push_back( "r9264_r10573_p3578"       );

  // set path + file names --> make sure $EJ_PATH set to local repo dir: 'export EJ_PATH=$(pwd)'
  //TString path = "$EJ_PATH/../run/local.";
  TString path = "$EJ_PATH/../output/localOutput/tree/2fbd76f3/local.";
  TString fp   = "/data-tree/";
  TString fn1  = "_13TeV.";
  TString fn2  = ".physics_Main.deriv.DAOD_EXOT23.";
  TString fn3  = "_p3664.root";
  std::vector<TString> fpath;
  std::vector<TString> fname;
  // for ( size_t i = 0; i != run.size(); ++i ) {
  //   //fpath.push_back( path + year.at(i / (run.size()/year.size())) + "." + run.at(i) + fp ); // single runs
  //   fpath.push_back( path + year.at(i / (run.size()/year.size())) + fp                                      );
  //   fname.push_back(        year.at(i / (run.size()/year.size())) + fn1 + run.at(i) + fn2 + tag.at(i) + fn3 );
  // }
  fpath.push_back( path + "data16" + fp );
  fname.push_back( "data16" + fn1 + "00303208" + fn2 + "r9264_r10573_p3578" + fn3 );

  // initialize canvas, file, and tree + loop over samples
  TCanvas *c = 0;
  TFile   *f = 0;
  TTree   *t = 0;
  for ( size_t i = 0; i != fname.size(); ++i ) {
    // set canvas
    c = new TCanvas( "c"+run.at(i), "c"+run.at(i) );
    
    // open file
    f = TFile::Open( fpath.at(i) + fname.at(i), "READ" );
    if ( !f ) std::cout << "ZERO POINTER"                              << std::endl;
    else      std::cout << "file: "       << fpath.at(i) + fname.at(i) << std::endl;

    // cd into ntuple directory
    f->cd("EJsMiniNtup");

    // get nominal tree
    t = (TTree*)gDirectory->Get("nominal");

    // draw variables
    //t->Draw("track_isSelected","track_passSel==0"); 

    //t->Draw("track_pt","track_isSelected && track_pt<1");
    
    //t->Draw("track_d0","fabs(track_d0)>300");
    //t->Draw("track_z0","fabs(track_z0)>1500");

    //t->Draw("track_chi2","track_isSelected && track_chi2>10");
    //t->Draw("track_chi2","track_chi2>10");
    //t->Draw("track_chi2","track_isSelected && track_chi2>7");
    //t->Draw("track_chi2","track_chi2>7 && track_chi2<50");
    //t->Draw("fabs(secVtx_trk_d0)", "secVtx_trk_isAssociated && fabs(secVtx_trk_d0)>20");
    t->Draw("fabs(track_d0)", "fabs(track_d0)>20");
    //t->Draw("secVtx_trk_d0", "secVtx_trk_d0>100");

    //t->Draw("TMath::Prob(track_chiSquared,track_numberDoF)","track_isSelected");
  }
 
}
