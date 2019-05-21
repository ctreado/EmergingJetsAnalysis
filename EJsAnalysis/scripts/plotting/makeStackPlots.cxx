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

void makeStackPlots ( TString  hname  = "",  TString htitle = "",    TString xtitle  = "",    TString  ytitle = "",
		      TString  htype  = "",  TString hreg   = "",    TString  hext   = "pdf", Bool_t   doLogy = true,
		      Bool_t  doNorm = true, Bool_t  doLocal = true, Double_t xmin   = 1.0,   Double_t xmax  = -1.0 )
{
  std::cout << "in makeStackPlots()" << std::endl;

  // build signal points
  std::vector<TString> mod;
  mod.push_back( "A" );
  mod.push_back( "B" );
  mod.push_back( "C" );
  mod.push_back( "D" );
  mod.push_back( "E" );
  std::vector<TString> xdm;
  xdm.push_back( "1400" );
  xdm.push_back( "1000" );
  xdm.push_back( "600"  );
  std::vector<TString> ctau;
  ctau.push_back( "300" );
  ctau.push_back( "150" );
  ctau.push_back( "75"  );
  ctau.push_back( "20"  );
  ctau.push_back( "5"   );
  if ( htype.Contains("update") ) {
    ctau.push_back( "2"   );
    ctau.push_back( "1"   );
    ctau.push_back( "0p5" );
  }
  TString fsuf = "";
  if ( htype.Contains("truth") ) fsuf = "4TJF";
  std::vector<TString> prodtype;
  if ( htype.Contains("truth") ) {
    prodtype.push_back( "mc15update" );
    prodtype.push_back( "mc15oldoff" );
  }
  
  // set path and file names
  // --> paths + root file names may change ...
  TString path = "$EJ_PATH/../run/"; // make sure $EJ_PATH set to local repo dir: 'export EJ_PATH=$(pwd)'
  if ( doLocal ) path += "localOutput/";
  
  TString hpath = "";
  if ( htype.Contains("truth") ) {
    if ( htype.Contains("update") ) {
      if ( doLocal ) hpath = "hist-tree/hists.local.truth.mc15update.";
    }
    else if ( htype.Contains("oldoff") ) {
      if ( doLocal ) hpath = "hist-tree/hists.local.truth.mc15oldoff.";
    }
    else if ( htype.Contains("vs") ) {
      if ( doLocal ) hpath = "hist-tree/hists.local.truth.";
    }
  }
  else if ( htype.Contains("mc16d") ) {
    if ( htype.Contains("updatetest") ) {
      if ( doLocal ) hpath = "hist-tree/hists.local.MC16d.updatetest.EJ_Model";
    }
  }
  if      ( htype.Contains("modelA") )
    hpath += "A_";
  else if ( htype.Contains("modelB") )
    hpath += "B_";
  else if ( htype.Contains("modelC") )
    hpath += "C_";
  else if ( htype.Contains("modelD") )
    hpath += "D_";
  else if ( htype.Contains("modelE") )
    hpath += "E_";

  // string together file names / legend strings
  std::vector<TString> fname;
  std::vector<TString> lname;
  if ( htype.Contains("model") ) {
    for ( size_t i = 0; i != xdm.size(); ++i ) {
      for ( size_t j = 0; j != ctau.size(); ++j ) {
	fname.push_back( xdm.at(i) + "_" + ctau.at(j) + "_" + fsuf );
	lname.push_back( xdm.at(i) + "_" + ctau.at(j)              );
      }
    }
  }
  else if ( htype.Contains("ctau") ) {
    TString ctau = "";
    if      ( htype.Contains("ctau300") ) ctau = "300";
    else if ( htype.Contains("ctau150") ) ctau = "150";
    else if ( htype.Contains("ctau75")  ) ctau = "75";
    else if ( htype.Contains("ctau20")  ) ctau = "20";
    else if ( htype.Contains("ctau5")   ) ctau = "5";
    else if ( htype.Contains("ctau2")   ) ctau = "2";
    else if ( htype.Contains("ctau1")   ) ctau = "1";
    else if ( htype.Contains("ctau0p5") ) ctau = "0p5";
    if ( !htype.Contains("xdm") ) {
      for ( size_t i = 0; i != xdm.size(); ++i ) {
	for ( size_t j = 0; j != mod.size(); ++j ) {
	  fname.push_back( mod.at(j) + "_" + xdm.at(i) + "_" + ctau + "_" + fsuf );
	  lname.push_back( mod.at(j) + "_" + xdm.at(i)                           );
	}
      }
    }
    else {
      TString xdm = "";
      if      ( htype.Contains("xdm1400") ) xdm = "1400";
      else if ( htype.Contains("xdm1000") ) xdm = "1000";
      else if ( htype.Contains("xdm600")  ) xdm = "600";
      for ( size_t i = 0; i != prodtype.size(); ++i ) {
	for ( size_t j = 0; j != mod.size(); ++j ) {
	  fname.push_back( prodtype.at(i) + "." + mod.at(j) + "_" + xdm + "_" + ctau + "_" + fsuf );
	  lname.push_back( prodtype.at(i) + "_" + mod.at(j)                                       );
	}
      }
    }
  }
  else if ( htype.Contains("updatetest") ) {
    if( htype.Contains("mc16d") ) {
      fname.push_back( "A_1000_150.999999" );
      fname.push_back( "B_1000_5.999999"   );
      fname.push_back( "A_1000_150.310328" );
      fname.push_back( "B_1000_5.310346"   );
      lname.push_back( "A_1000_150 (updated)"      );
      lname.push_back( "B_1000_5 (updated)"        );
      lname.push_back( "A_1000_150 (old official)" );
      lname.push_back( "B_1000_5 (old official)"   );
    }
  }

  TString hfile = "/hist-data-tree.root";
  
  // set line attributes
  std::vector<Color_t> hcolor;
  hcolor.push_back( kRed );
  hcolor.push_back( kMagenta );
  hcolor.push_back( kBlue );
  hcolor.push_back( kCyan + 1 );
  hcolor.push_back( kGreen + 1 );
  hcolor.push_back( kOrange - 3 );
  hcolor.push_back( kPink + 10 );
  hcolor.push_back( kViolet - 3 );

  // initialize canvas
  //TCanvas *c1 = new TCanvas( "c1", "" );
  //if ( htype.Contains("truth") ) {
  TCanvas *c1 = new TCanvas( "c1", "", 1000, 650 );
  //c1->SetCanvasSize( 1000, 650 );
  c1->SetRightMargin ( 0.2 );
  //}
  
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
  Double_t xr     = 0.9750;                             // right edge of legend (lxr) --> default = 0.88
  Double_t yint   = 0.0300;                             // y-length per line
  Double_t xint   = 0.0185;                             // x-width per character in lname
  if ( htype.Contains("ctau") ) {
    if      ( !htype.Contains("xdm") ) xint = 0.0250;
    else if (  htype.Contains("xdm") ) xint = 0.0125;
  }
  if ( htype.Contains("updatetest") ) {
    xint = 0.0078;
    xr   = 0.9950;
  }
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
  Double_t xtxt    = 0.850;
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
    if      ( htype.Contains("model") )
      h->SetLineColor( hcolor.at(i % ctau.size()) );
    else if ( htype.Contains("ctau")  )
      h->SetLineColor( hcolor.at(i  % mod.size()) );
    if ( htype.Contains("model") || ( htype.Contains("ctau") && !htype.Contains("xdm") ) ) {
      if      ( fname.at(i).Contains( "1400" ) ) h->SetLineStyle( 1 );
      else if ( fname.at(i).Contains( "1000" ) ) h->SetLineStyle( 2 );
      else if ( fname.at(i).Contains( "600"  ) ) h->SetLineStyle( 3 );
    }
    else if ( htype.Contains("truth") && htype.Contains("ctau") && htype.Contains("xdm") ) {
      if      ( fname.at(i).Contains( "update" ) ) h->SetLineStyle( 1 );
      else if ( fname.at(i).Contains( "oldoff" ) ) h->SetLineStyle( 2 );
    }
    else if ( htype.Contains("updatetest") ) {
      if ( fname.at(i).Contains("A_1000_150" )   ) h->SetLineColor( kRed  );
      else if ( fname.at(i).Contains("B_1000_5") ) h->SetLineColor( kBlue );
      if ( fname.at(i).Contains("999999")        ) h->SetLineStyle( 1     );
      else                                         h->SetLineStyle( 2     );
    }

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
  TString hdir = path + "plots/" + htype + "/";
  TString hout = hdir + "h_" + hreg + "_" + hname;
  c1->SaveAs( hout + "." + hext );
  if ( doLogy ) {
    gPad->SetLogy();
    hout += "_logy";
    c1->SaveAs( hout + "." + hext );
  }

  c1->Close();
  
}
