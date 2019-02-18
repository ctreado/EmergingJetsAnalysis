// (temporary) stack plotting script for EJsAnalysis 1D cutflow histograms

#include <TROOT.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <THStack.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLine.h>
#include <TPad.h>
#include <TString.h>
#include <TStyle.h>

#include <iostream>

void makeCutflowStackPlots ( TString hname  = "cutflow",   TString htitle = "",
			     TString xtitle = "",   TString ytitle = "",
			     TString type   = "mc", TString hext = "pdf" )
{
  std::cout << "in makeCutflowStackPlots()" << std::endl;

  // set path and file names
  // --> paths + root file names may change ...
  TString path = "$EJ_PATH/../run/"; // make sure $EJ_PATH set to local repo dir; 'export EJ_PATH=$(pwd)'
  TString hpath = "";
  TString hdir  = path + "/tmp_plots/" + type + "/";
  std::vector<TString> fname;
  std::vector<TString> lname;
  if ( type == "mc" ) {
    hpath = "local.MC16d/data-cutflow/";
    TString pre1 = "mc16_13TeV.3103";
    TString pre2 = ".Pythia8EvtGen_A14NNPDF23LO_EJ_Model";
    TString suf  = "_4jetFilter.deriv.DAOD_EXOT23.e6853_e5984_s3126_r10739_p3663.root";
    std::vector<TString> dsid;
    dsid.push_back( "25" );
    dsid.push_back( "40" );
    dsid.push_back( "55" );
    dsid.push_back( "28" );
    dsid.push_back( "46" );
    dsid.push_back( "59" );
    dsid.push_back( "65" );
    dsid.push_back( "77" );
    dsid.push_back( "94" );
    lname.push_back( "A_1400_20"  );
    lname.push_back( "B_1400_20"  );
    lname.push_back( "C_1400_20"  );
    lname.push_back( "A_1000_150" );
    lname.push_back( "B_1000_5"   );
    lname.push_back( "C_1000_75"  );
    lname.push_back( "C_600_20"   );
    lname.push_back( "D_600_300"  );
    lname.push_back( "E_600_75"   );
    for ( size_t i = 0; i != lname.size(); ++i )
      fname.push_back( pre1 + dsid.at(i) + pre2 + lname.at(i) + suf );
  }
  else if ( type == "data" ) {
    hpath = "local.data/data-cutflow/";
    TString suf1 = ".physics_Main.deriv.DAOD_EXOT23.";
    TString suf2 = "_p3578_p3664.root";
    lname.push_back( "17.00328333" );
    lname.push_back( "16.00302872" );
    lname.push_back( "15.00284285" );
    fname.push_back( "data17_13TeV.00328333" + suf1 + "r10203_r10658" + suf2 );
    fname.push_back( "data16_13TeV.00302872" + suf1 + "r9264_r10573"  + suf2 );
    fname.push_back( "data15_13TeV.00284285" + suf1 + "r9264_r10573"  + suf2 );
  }

  // set line attributes
  std::vector<Color_t> hcolor;
  if ( type == "mc" ) {
    hcolor.push_back( kRed       ); // Xdm-1400
    hcolor.push_back( kRed       );
    hcolor.push_back( kRed       );
    hcolor.push_back( kBlue      ); // Xdm-1000
    hcolor.push_back( kBlue      );
    hcolor.push_back( kBlue      );
    hcolor.push_back( kGreen + 1 ); // Xdm-600 
    hcolor.push_back( kGreen + 1 );
    hcolor.push_back( kGreen + 1 );
  }
  else if ( type == "data" ) {
    hcolor.push_back( kRed       ); // data17
    hcolor.push_back( kBlue      ); // data16
    hcolor.push_back( kGreen + 1 ); // data15
  }

  // configure legend
  // find fname element w/ longest length
  size_t maxlength = 0;
  size_t maxindex  = 0;
  for ( size_t i = 0; i != lname.size(); ++i ) {
    size_t namelength = lname.at(i).Length();
    if ( namelength > maxlength ) {
      maxlength = namelength;
      maxindex  = i;
    }
  }
  // set position + size of legend box
  Double_t yt     = 0.9000;                             // top of legend (lyt) ---------> default = 0.87
  Double_t xr     = 0.9000;                             // right edge of legend (lxr) --> default = 0.88
  Double_t yint   = 0.0300;                             // y-length per line
  Double_t xint   = 0.0130;                             // x-width per character in lname
  Double_t ysh    = yint * lname.size();                // y-length of legend
  Double_t xsh    = xint * lname.at(maxindex).Length(); // x-width of legend
  Double_t yb     = yt - ysh;                           // bottom of legend
  Double_t xl     = xr - xsh;                           // left edge of legend
  Double_t txt_sz = 0.0225;                             // legend text size
  // initialize legend
  TLegend* l1 = new TLegend( xl, yb, xl+xsh, yb+ysh );
  l1->SetFillColor(0);
  l1->SetBorderSize(1);
  l1->SetTextSize(txt_sz);
 
  // configure extra text
  Double_t xtxt    = 0.795;
  Double_t ytxt    = 0.950;
  Double_t ttxt    = 0.0235;
  TString atlStr   = "#it{ATLAS} Internal";
  TString lumiStr  = "#sqrt{s} = 13 TeV";
  TLatex* atlText  = new TLatex( xtxt,         ytxt,         atlStr  );
  TLatex* lumiText = new TLatex( xtxt + 0.025, ytxt - 0.025, lumiStr );
  atlText  ->SetTextSize( ttxt );
  lumiText ->SetTextSize( ttxt );
  atlText  ->SetNDC( kTRUE );
  lumiText ->SetNDC( kTRUE );
  
  // set booleans
  Bool_t doLogy    = true;
  Bool_t normalize = false;

  // set normalization
  Double_t norm_factor = 1.;
  TString norm_name = "one";

  // initialize canvas
  TCanvas* c1 = new TCanvas();

  // initialize stack
  TFile*   f = 0;
  TH1F*    h = 0;
  THStack* hs = new THStack( "Stack", htitle ); 

  // fill stack
  for ( size_t i = 0; i != fname.size(); ++i ) {
    f = TFile::Open( path + hpath + fname.at(i), "READ" );
    if ( !f ) std::cout << "ZERO POINTER" << std::endl;
    else {
      std::cout << "file pointer: " << f                   << std::endl;
      std::cout << "   file name: " << hpath + fname.at(i) << std::endl; 
    }

    // get histogram from file
    h = (TH1F*)f->Get(hname);
    h->SetDirectory(0);
    h->SetStats(0);

    // normalize histogram
    Double_t norm = norm_factor / h->Integral();
    if ( normalize ) h->Scale( norm );

    // set line attributes
    h->SetLineWidth( 2 );
    h->SetLineColor( hcolor.at(i) );
    h->SetLineStyle( 1 );
    if      ( lname.at(i).Contains( "B_" ) ) h->SetLineStyle( 2 );
    else if ( lname.at(i).Contains( "C_" ) ) h->SetLineStyle( 3 );
    else if ( lname.at(i).Contains( "D_" ) ) h->SetLineStyle( 7 );
    else if ( lname.at(i).Contains( "E_" ) ) h->SetLineStyle( 8 );

    // add legend entries
    l1->AddEntry( h, lname.at(i), "l" );

    // add histogram to stack
    hs->Add( h );

    // close file
    f->Close();
  } // end loop over files

  // draw stack
  hs->Draw( "nostack hist" ); // 'hist' = no error bars

  // set axes
  Double_t xoff = 1.25;
  Double_t yoff = 1.25;
  hs->GetXaxis()->SetTitle( xtitle );
  hs->GetYaxis()->SetTitle( ytitle );
  hs->GetXaxis()->SetTitleOffset( xoff );
  hs->GetYaxis()->SetTitleOffset( yoff );
  //hs->GetXaxis()->SetRangeUser( xmin, xmax );
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  gPad->RedrawAxis();

  // draw legend
  l1->Draw( "same" );

  // draw text
  atlText  ->Draw( "same" );
  lumiText ->Draw( "same" );

  // save plot
  TString hout = hdir + hname;
  c1->SaveAs( hout + "." + hext );
  if ( doLogy ) {
    gPad->SetLogy();
    hout += "_logy";
    c1->SaveAs( hout + "." + hext );
  }

  c1->Close();

}
