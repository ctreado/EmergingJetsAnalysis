// (temporary) stack plotting script for EJsAnalysis 1D histograms

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
#include <TSystem.h>

#include <iostream>

void makeStackPlots ( TString  hname  = "nPV",   TString htitle = "MC16d", TString  xtitle = "n PV",  TString  ytitle = "",
		      TString  htype  = "mc16d", TString hreg   = "all",   TString  hobj   = "event", TString  hext   = "pdf",
		      Bool_t   doLogy = true,    Bool_t  doNorm = true,    Bool_t   doLocal = true,   Double_t xmin   = 1.0,   Double_t xmax = -1.0 )
{
  std::cout << "in makeStackPlots()" << std::endl;

  // set path and file names
  // --> paths + root file names may change ...
  TString path = "$EJ_PATH/../run/"; // make sure $EJ_PATH set to local repo dir: 'export EJ_PATH=$(pwd)'
  TString hpath = "";
  TString hfile = "/hist-data-tree.root";
  if ( doLocal ) path += "localOutput/";
  
  std::vector<TString> fname;
  if ( htype.Contains("mc16d_oldoff") ) {
    if ( doLocal ) {
      hpath = "hist-tree/hists.local.MC16d.oldoff.EJ_Model";
      fname.push_back( "A_1400_20"  );
      fname.push_back( "B_1400_20"  );
      fname.push_back( "C_1400_20"  );
      fname.push_back( "A_1000_150" );
      fname.push_back( "B_1000_5"   );
      fname.push_back( "C_1000_75"  );
      fname.push_back( "C_600_20"   );
      fname.push_back( "D_600_300"  );
      fname.push_back( "E_600_75"   );
    }
  }
  else if ( htype.Contains("mc16d_updatetest") ) {
    if ( doLocal ) {
      hpath = "hist-tree/hists.local.MC16d.updatetest.EJ_Model";
      //fname.push_back( "A_1000_150.999999" );
      fname.push_back( "B_1000_5.999999"   );
      //fname.push_back( "A_1000_150.310328" );
      fname.push_back( "B_1000_5.310346"   );
    }
  }
  else if ( htype.Contains("data") ) {
    if ( doLocal ) {
      hpath = "hist-tree/hists.local.data";
      fname.push_back( "17.00328333" );
      fname.push_back( "16.00302872" );
      fname.push_back( "15.00284285" );
    }
  }
  else if ( htype.Contains("truth_pytest") ) {
    if ( doLocal ) {
      hpath = "hist-tree/hists.local.truth.pytest.";
      fname.push_back( "py81.A_1000_150"         );
      fname.push_back( "py81.B_1000_5"           );
      fname.push_back( "py82.A_1000_150"         );
      fname.push_back( "py82.B_1000_5"           );
      fname.push_back( "py82.A_1000_150.211ctau" );
      fname.push_back( "py82.B_1000_5.211ctau"   );
    }
  }
  else if ( htype.Contains("truth_mc15test") ) {
    if ( doLocal ) {
      hpath = "hist-tree/hists.local.truth.mc15test.";
      fname.push_back( "A_1000_150_4TJF"         );
      fname.push_back( "B_1000_5_4TJF"           );
      fname.push_back( "A_1000_150_211ctau_4TJF" );
      fname.push_back( "B_1000_5_211ctau_4TJF"   );
    }
  }
  else if ( htype.Contains("truth_mc15updatetest") ) {
    if ( doLocal ) {
      hpath = "hist-tree/hists.local.truth.mc15updatetest.";
      fname.push_back( "310328.A_1000_150_4TJF" );
      fname.push_back( "310346.B_1000_5_4TJF"   );
      fname.push_back( "999999.A_1000_150_4TJF" );
      fname.push_back( "999999.B_1000_5_4TJF"   );
    }
  }
  else if ( htype.Contains("truth_mc15update") ) {
    if ( doLocal ) {
      hpath = "hist-tree/hists.local.truth.mc15update.";
      fname.push_back( "A_1000_300_4TJF" );
      fname.push_back( "A_1000_150_4TJF" );
      fname.push_back( "A_1000_75_4TJF"  );
      fname.push_back( "A_1000_20_4TJF"  );
      fname.push_back( "A_1000_5_4TJF"   );
      fname.push_back( "A_1000_2_4TJF"   );
      fname.push_back( "A_1000_1_4TJF"   );
      fname.push_back( "A_1000_0p5_4TJF" );
    }
  }

  // set line attributes
  std::vector<Color_t> hcolor;
  if ( htype.Contains("mc16d_oldoff") ) {
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
  else if ( htype.Contains("mc16d_updatetest") ) {
    //hcolor.push_back( kRed  ); // update -- long-lived 4900211
    hcolor.push_back( kRed  );
    //hcolor.push_back( kBlue ); // old -- prompt 4900211
    hcolor.push_back( kBlue );
  }
  else if ( htype.Contains("data") ) {
    hcolor.push_back( kRed       ); // data17
    hcolor.push_back( kBlue      ); // data16
    hcolor.push_back( kGreen + 1 ); // data15
  }
  else if ( htype.Contains("truth_pytest") ) {
    hcolor.push_back( kRed       ); // pythia 8.183
    hcolor.push_back( kRed       );
    hcolor.push_back( kBlue      ); // pythia 8.230 w/ zero 4900211 ctau
    hcolor.push_back( kBlue      );
    hcolor.push_back( kGreen + 1 ); // pythia 8.230 w/ nonzero 4900211 ctau
    hcolor.push_back( kGreen + 1 );
  }
  else if ( htype.Contains("truth_mc15test") ) {
    hcolor.push_back( kBlue      ); // mc15 old official (local jo)
    hcolor.push_back( kBlue      );
    hcolor.push_back( kGreen + 1 ); // mc15 update w/ nonzero 4900211 ctau
    hcolor.push_back( kGreen + 1 );
  }
  else if ( htype.Contains("truth_mc15updatetest") ) {
    hcolor.push_back( kBlue      ); // mc15 old official (official jo)
    hcolor.push_back( kBlue      );
    hcolor.push_back( kGreen + 1 ); // mc15 update w/ nonzero 4900211 ctau (retest)
    hcolor.push_back( kGreen + 1 );
  }
  else if ( htype.Contains("truth_mc15update") ) {
    hcolor.push_back( kRed );
    hcolor.push_back( kPink - 9 );
    hcolor.push_back( kMagenta + 1 );
    hcolor.push_back( kViolet + 1 );
    hcolor.push_back( kBlue );
    hcolor.push_back( kAzure - 9 );
    hcolor.push_back( kCyan + 1 );
    hcolor.push_back( kGreen + 1 );
  }

  // configure legend
  // find fname element w/ longest length
  size_t maxlength = 0;
  size_t maxindex  = 0;
  for ( size_t i = 0; i != fname.size(); ++i ) {
    size_t namelength = fname.at(i).Length();
    if ( namelength > maxlength ) {
      maxlength = namelength;
      maxindex  = i;
    }
  }
  // set position + size of legend box
  Double_t yt     = 0.9000;                             // top of legend (lyt) ---------> default = 0.87
  Double_t xr     = 0.9000;                             // right edge of legend (lxr) --> default = 0.88
  Double_t yint   = 0.0300;                             // y-length per line
  Double_t xint   = 0.0130;                             // x-width per character in fname
  if ( htype.Contains("truth") ) xint = 0.0105;
  Double_t ysh    = yint * fname.size();                // y-length of legend
  Double_t xsh    = xint * fname.at(maxindex).Length(); // x-width of legend
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

  // set normalization
  Double_t norm_factor = 1.;
  TString norm_name = "one";
  
  // initialize canvas
  TCanvas* c1 = new TCanvas();
  
  // initialize stack
  TFile*   f  = 0;
  TH1F*    h  = 0;
  THStack* hs = new THStack( "Stack", htitle );
  
  // fill stack
  for ( size_t i = 0; i != fname.size(); ++i ) {
    f = TFile::Open( path + hpath + fname.at(i) + hfile, "READ" );
    if ( !f ) std::cout << "ZERO POINTER" << std::endl;
    else {
      std::cout << "file pointer: " << f                           << std::endl;
      std::cout << "   file name: " << hpath + fname.at(i) + hfile << std::endl;
    }
    f->cd("EJsHists/nominal/" + hreg);
    // --> need to modify to take variable tree name....

    // get histogram from file
    h = (TH1F*)gDirectory->Get(hname);
    h->SetDirectory(0);
    h->SetStats(0);

    // normalize histogram
    Double_t norm = norm_factor / h->Integral();
    if ( doNorm ) h->Scale( norm );

    // set line attributes
    h->SetLineWidth( 2 );
    h->SetLineColor( hcolor.at(i) );
    h->SetLineStyle( 1 );
    if      ( fname.at(i).Contains( "B_" ) ) h->SetLineStyle( 2 );
    else if ( fname.at(i).Contains( "C_" ) ) h->SetLineStyle( 3 );
    else if ( fname.at(i).Contains( "D_" ) ) h->SetLineStyle( 7 );
    else if ( fname.at(i).Contains( "E_" ) ) h->SetLineStyle( 8 );

    // add legend entries
    l1->AddEntry( h, fname.at(i), "l" );

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
  hs->GetXaxis()->SetRangeUser( xmin, xmax );
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  gPad->RedrawAxis();

  // draw legend
  l1->Draw( "same" );

  // draw text
  atlText  ->Draw( "same" );
  lumiText ->Draw( "same" );

  // save plot
  TString hdir = path + "plots/stack_plots/" + htype + "/" + hreg + "/" + hobj + "/";
  TString hout = hdir + "h_" + hname;
  c1->SaveAs( hout + "." + hext );
  if ( doLogy ) {
    gPad->SetLogy();
    hout += "_logy";
    c1->SaveAs( hout + "." + hext );
  }

  c1->Close();
  
}
