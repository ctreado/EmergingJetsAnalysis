// (temporary) 2D-[PUT TYPE HERE] plotting script for EJsAnalysis 2D histograms

#include <TROOT.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLine.h>
#include <TPad.h>
#include <TString.h>
#include <TStyle.h>

#include <iostream>

void make2DPlots ( TString  hname  = "",   TString htitle  = "",   TString  xtitle = "",  TString  ytitle = "",    TString  ztitle = "",
		   TString  htype  = "",   TString hreg    = "",   TString  hobj   = "",  TString  hext   = "pdf", Bool_t   doLogx = false,
		   Bool_t   doLogy = true, Bool_t  doLocal = true, Double_t xmin   = 1.0, Double_t xmax   = -1.0,  Double_t ymin   = 1.0,
		   Double_t ymax   = -1.0, Int_t   rebinx  = 1,    Int_t    rebiny = 1 )
{
  std::cout << "in make2DPlots()" << std::endl;

  // set path and file names
  // --> paths + root file names may change ...
  TString path  = "$EJ_PATH/../run/"; // make sure $EJ_PATH set to local repo dir: 'export EJ_PATH=$(pwd)'
  //TString hpath = "hists.local." + htitle;
  TString hpath = "";
  TString hfile = "/hist-data-tree.root";
  if ( doLocal ) {
    path += "localOutput/";
    if      ( htype.Contains("mc16d") ) hpath = "hist-tree/hists.local." + htitle;
    else if ( htype.Contains("data")  ) hpath = "hist-tree/hists.local." + htitle;
  }

  // get histogram from file
  TFile* f = TFile::Open( path + hpath + hfile, "READ" );
  if ( !f ) std::cout << "ZERO POINTER" << std::endl;
  else {
    std::cout << "file pointer: " << f             << std::endl;
    std::cout << "   file name: " << hpath + hfile << std::endl;
  }
  f->cd("EJsHists/nominal/" + hreg);

  // set histogram title
  TString region_title = hreg;
  if      ( hreg == "all"    ) region_title = "all regions";
  else if ( hreg == "signal" ) region_title = "signal region";
  else if ( hreg == "valid"  ) region_title = "validation region";
  TString title = htitle + ": " + region_title;
      
  TH2F* h = (TH2F*)gDirectory->Get(hname);
  h->SetDirectory(0);
  h->SetStats(0);
  h->SetTitle( title );

  // get stats
  Int_t    nEvents = h->GetEntries();
  Double_t meanX   = h->GetMean(1);
  Double_t meanY   = h->GetMean(2);
  Double_t stddevX = h->GetRMS(1);
  Double_t stddevY = h->GetRMS(2);
  
  // set stats strings
  TString nEventsStr; nEventsStr. Form( "%i",   nEvents );
  TString meanXStr;   meanXStr.   Form( "%.3f", meanX   );
  TString meanYStr;   meanYStr.   Form( "%.3f", meanY   );
  TString stddevXStr; stddevXStr. Form( "%.3f", stddevX );
  TString stddevYStr; stddevYStr. Form( "%.3f", stddevY );
  
  // configure extra text
  Double_t xtxt = 0.15; Double_t ytxt = 0.935; Double_t ttxt = 0.0235;
  TString atlStr  = "#it{ATLAS} Internal";
  TString lumiStr = "#sqrt{s} = 13TeV";
  TString nStr    = "# events = " + nEventsStr;
  TString mXStr   = "x mean   = " + meanXStr;
  TString mYStr   = "y mean   = " + meanYStr;
  TString wXStr   = "x stddev = " + stddevXStr;
  TString wYStr   = "y stddev = " + stddevYStr;
  TLatex* atlText  = new TLatex( xtxt,         ytxt,         atlStr  );
  TLatex* lumiText = new TLatex( xtxt + 0.025, ytxt - 0.025, lumiStr );
  TLatex* nText    = new TLatex( xtxt + 0.525, ytxt - 0.10,  nStr    );
  TLatex* mXText   = new TLatex( xtxt + 0.525, ytxt - 0.125,  mXStr   );
  TLatex* mYText   = new TLatex( xtxt + 0.525, ytxt - 0.15,  mYStr   );
  TLatex* wXText   = new TLatex( xtxt + 0.525, ytxt - 0.175,  wXStr   );
  TLatex* wYText   = new TLatex( xtxt + 0.525, ytxt - 0.20,  wYStr   );
  atlText  ->SetTextSize( ttxt );
  lumiText ->SetTextSize( ttxt );
  nText    ->SetTextSize( ttxt );
  mXText   ->SetTextSize( ttxt );
  mYText   ->SetTextSize( ttxt );
  wXText   ->SetTextSize( ttxt );
  wYText   ->SetTextSize( ttxt );
  atlText  ->SetNDC( kTRUE );
  lumiText ->SetNDC( kTRUE );
  nText    ->SetNDC( kTRUE );
  mXText   ->SetNDC( kTRUE );
  mYText   ->SetNDC( kTRUE );
  wXText   ->SetNDC( kTRUE );
  wYText   ->SetNDC( kTRUE );
  

  // set axes titles + offsets
  Double_t xoff = 1.25;
  Double_t yoff = 1.25;
  Double_t zoff = 1.25;
  h->GetXaxis()->SetTitleOffset( xoff );
  h->GetYaxis()->SetTitleOffset( yoff );
  h->GetZaxis()->SetTitleOffset( zoff );
  h->GetXaxis()->SetTitle( xtitle );
  h->GetYaxis()->SetTitle( ytitle );
  h->GetZaxis()->SetTitle( ztitle );
  
  // set axes ranges + rebin
  h->Rebin2D( rebinx, rebiny );
  h->GetXaxis()->SetRangeUser( xmin, xmax );
  h->GetYaxis()->SetRangeUser( ymin, ymax );

  // initialize canvas
  TCanvas *c1 = new TCanvas();
  c1->SetRightMargin( 0.15 );
  
  // draw plot
  h->Draw("colz");

  // draw text
  atlText  ->Draw( "same" );
  lumiText ->Draw( "same" );
  nText    ->Draw( "same" );
  mXText   ->Draw( "same" );
  mYText   ->Draw( "same" );
  wXText   ->Draw( "same" );
  wYText   ->Draw( "same" );

  // set axes ticks
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  gPad->RedrawAxis();

  // save plot
  TString hdir  = path + "/plots/2d_plots/" + htype + "/" + hreg + "/" + hobj + "/";
  TString hout = hdir + htitle + "." + hname;
  c1->SaveAs( hout + "." + hext );
  if ( doLogx || doLogy ) {
    if ( doLogx ) {
      gPad->SetLogx();
      hout += "_logyx";
    }
    if ( doLogy ) {
      gPad->SetLogy();
      hout += "_logy";
    }
    c1->SaveAs( hout + "." + hext );
  }

  // close file
  f->Close();

  // close canvas
  c1->Close();

}
