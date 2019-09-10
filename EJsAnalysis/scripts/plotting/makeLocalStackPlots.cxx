// (temporary) stack plotting script for local EJsAnalysis 1D histograms

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

void makeLocalStackPlots ( TString hname   = "nPV",  TString htype  = "mc16d", TString hreg  = "all",
			   TString xtitle  = "",     TString ytitle = "",
			   TString houtdir = "",     TString hext   = "pdf",   TString htree = "nominal", 
			   Bool_t  doNorm  = true,   Bool_t  doLogy = true )
{
  // set sample vectors
  TString hpath = "$EJ_PATH/../output/localOutput/hist-tree/"; // make sure $EJ_PATH set to local repo dir: 'export EJ_PATH=$(pwd)'
  TString hfile = "/hist-data-tree.root";

  // set file, legend names; line colors, styles; stack title
  std::vector<TString> fname;
  std::vector<TString> lname;
  std::vector<Color_t> hcolor;
  std::vector<Int_t>   hstyle;

  std::vector<Color_t> hc;
  hc.push_back( kRed         );
  hc.push_back( kBlue        );
  hc.push_back( kGreen  +  1 );
  hc.push_back( kMagenta     );
  hc.push_back( kCyan   +  1 );
  hc.push_back( kViolet -  3 );
  hc.push_back( kOrange -  3 );
  // look for more colors if need be...

  TString htitle = "";

  // data15 vs 16 vs 17 vs 18
  if ( htype.Contains("data") && !htype.Contains("mc16") ) {
    TString path = "hists.local.data";
    fname.push_back( path + "18.363830" );
    fname.push_back( path + "17.331804" );
    fname.push_back( path + "16.303208" );
    fname.push_back( path + "15.280862" );
    
    lname.push_back( "data18 (r363830)" );
    lname.push_back( "data17 (r331804)" );
    lname.push_back( "data16 (r303208)" );
    lname.push_back( "data15 (r280862)" );

    hcolor.push_back( hc.at(0) );
    hcolor.push_back( hc.at(1) );
    hcolor.push_back( hc.at(2) );
    hcolor.push_back( hc.at(3) );

    htitle = "Data";
    if ( hreg != "all" ) htitle += " [" + hreg + "]";
  }
  // mc16
  else if ( htype.Contains("mc16") ) {

    htitle = "MC16";
    
    // mc16d
    if ( htype.Contains("mc16d") ) {
      
      TString path = "hists.local.MC16d.";
      int hc_n     = 0;
      htitle      += "d";
      
      // all samples or model-by-model
      if ( !htype.Contains("xdm") ) {
	// model-A
	if ( htype.Contains("modA") || htype.Contains("modelA") || !htype.Contains("mod") ) {
	  fname.push_back( path + "312004.EJ_ModelA_1400_20"  );
	  fname.push_back( path + "312008.EJ_ModelA_1000_150" );
	  fname.push_back( path + "312017.EJ_ModelA_600_1"    );
	  
	  lname.push_back( "MC16d.A.1400.20"  );
	  lname.push_back( "MC16d.A.1000.150" );
	  lname.push_back( "MC16d.A.600.1"    );
	  
	  hcolor.push_back( hc.at(0) );
	  hcolor.push_back( hc.at(1) );
	  hcolor.push_back( hc.at(2) );

	  if ( htype.Contains("mod") ) htitle += " (ModelA)";
	}
	// model-B
	if ( htype.Contains("modB") || htype.Contains("modelB") || !htype.Contains("mod") ) {
	  fname.push_back( path + "312022.EJ_ModelB_1400_20" );
	  fname.push_back( path + "312028.EJ_ModelB_1000_5"  );
	  fname.push_back( path + "312031.EJ_ModelB_600_300" );
	  
	  lname.push_back( "MC16d.B.1400.20" );
	  lname.push_back( "MC16d.B.1000.5"  );
	  lname.push_back( "MC16d.B.600.300" );
	  
	  hcolor.push_back( hc.at(0) );
	  hcolor.push_back( hc.at(1) );
	  hcolor.push_back( hc.at(2) );

	  if ( htype.Contains("mod") ) htitle += " (ModelB)";
	}
	// model-C
	if ( htype.Contains("modC") || htype.Contains("modelC") || !htype.Contains("mod") ) {
	  fname.push_back( path + "312039.EJ_ModelC_1400_75" );
	  fname.push_back( path + "312046.EJ_ModelC_1000_5"  );
	  fname.push_back( path + "312052.EJ_ModelC_600_2"   );
	
	  lname.push_back( "MC16d.C.1400.75" );
	  lname.push_back( "MC16d.C.1000.5"  );
	  lname.push_back( "MC16d.C.600.2"   );
	  
	  hcolor.push_back( hc.at(0) );
	  hcolor.push_back( hc.at(1) );
	  hcolor.push_back( hc.at(2) );

	  if ( htype.Contains("mod") ) htitle += " (ModelC)";
	}
	// model-D
	if ( htype.Contains("modD") || htype.Contains("modelD") || !htype.Contains("mod") ) {
	  fname.push_back( path + "312060.EJ_ModelD_1400_2"  );
	  fname.push_back( path + "312066.EJ_ModelD_1000_1"  );
	  fname.push_back( path + "312067.EJ_ModelD_600_300" );
	  
	  lname.push_back( "MC16d.D.1400.2"  );
	  lname.push_back( "MC16d.D.1000.1"  );
	  lname.push_back( "MC16d.D.600.300" );
	  
	  hcolor.push_back( hc.at(0) );
	  hcolor.push_back( hc.at(1) );
	  hcolor.push_back( hc.at(2) );

	  if ( htype.Contains("mod") ) htitle += " (ModelD)";
	}
	// model-E
	if ( htype.Contains("modE") || htype.Contains("modelE") || !htype.Contains("mod") ) {
	  fname.push_back( path + "312075.EJ_ModelE_1400_75"  );
	  fname.push_back( path + "312080.EJ_ModelE_1000_150" );
	  fname.push_back( path + "312090.EJ_ModelE_600_0p5"  );
	  
	  lname.push_back( "MC16d.E.1400.75"  );
	  lname.push_back( "MC16d.E.1000.150" );
	  lname.push_back( "MC16d.E.600.0p5"  );
	  
	  hcolor.push_back( hc.at(0) );
	  hcolor.push_back( hc.at(1) );
	  hcolor.push_back( hc.at(2) );

	  if ( htype.Contains("mod") ) htitle += " (ModelE)";
	}
	hc_n = 2;
      }
      // xdm by xdm
      else {
	// xdm-1400
	if ( htype.Contains("xdm1400") ) {
	  fname.push_back( path + "312004.EJ_ModelA_1400_20" );
	  fname.push_back( path + "312022.EJ_ModelB_1400_20" );
	  fname.push_back( path + "312039.EJ_ModelC_1400_75" );
	  fname.push_back( path + "312060.EJ_ModelD_1400_2"  );
	  fname.push_back( path + "312075.EJ_ModelE_1400_75" );

	  lname.push_back( "MC16d.A.1400.20" );
	  lname.push_back( "MC16d.B.1400.20" );
	  lname.push_back( "MC16d.C.1400.75" );
	  lname.push_back( "MC16d.D.1400.2"  );
	  lname.push_back( "MC16d.E.1400.75" );

	  hcolor.push_back( hc.at(0) );
	  hcolor.push_back( hc.at(1) );
	  hcolor.push_back( hc.at(2) );
	  hcolor.push_back( hc.at(3) );
	  hcolor.push_back( hc.at(4) );

	  htitle += " (Xdm-1400)";
	}
	// xdm-1000
	if ( htype.Contains("xdm1000") ) {
	  fname.push_back( path + "312008.EJ_ModelA_1000_150" );
	  fname.push_back( path + "312028.EJ_ModelB_1000_5"   );
	  fname.push_back( path + "312046.EJ_ModelC_1000_5"   );
	  fname.push_back( path + "312066.EJ_ModelD_1000_1"   );
	  fname.push_back( path + "312080.EJ_ModelE_1000_150" );

	  lname.push_back( "MC16d.A.1000.150" );
	  lname.push_back( "MC16d.B.1000.5"   );
	  lname.push_back( "MC16d.C.1000.5"   );
	  lname.push_back( "MC16d.D.1000.1"   );
	  lname.push_back( "MC16d.E.1000.150" );

	  hcolor.push_back( hc.at(0) );
	  hcolor.push_back( hc.at(1) );
	  hcolor.push_back( hc.at(2) );
	  hcolor.push_back( hc.at(3) );
	  hcolor.push_back( hc.at(4) );

	  htitle += " (Xdm-1000)";
	}
	// xdm-600
	if ( htype.Contains("xdm600") ) {
	  fname.push_back( path + "312017.EJ_ModelA_600_1"   );
	  fname.push_back( path + "312031.EJ_ModelB_600_300" );
	  fname.push_back( path + "312052.EJ_ModelC_600_2"   );
	  fname.push_back( path + "312067.EJ_ModelD_600_300" );
	  fname.push_back( path + "312090.EJ_ModelE_600_0p5" );

	  lname.push_back( "MC16d.A.600.1"   );
	  lname.push_back( "MC16d.B.600.300" );
	  lname.push_back( "MC16d.C.600.2"   );
	  lname.push_back( "MC16d.D.600.300" );
	  lname.push_back( "MC16d.E.600.0p5" );

	  hcolor.push_back( hc.at(0) );
	  hcolor.push_back( hc.at(1) );
	  hcolor.push_back( hc.at(2) );
	  hcolor.push_back( hc.at(3) );
	  hcolor.push_back( hc.at(4) );

	  htitle += " (Xdm-600)";
	}
	hc_n = 4;
      }

      // mc16 vs data17
      if ( htype.Contains("data") ) {
	fname .push_back( "hists.local.data17.331804" );
	lname .push_back( "data17 (r331804)"          );
	hcolor.push_back( hc.at(hc_n + 1) );
	htitle += " vs Data17";
      }
      // mc16d signal vs background
      if ( htype.Contains("bkgd") ) {
	fname .push_back( path + "bkgd.jz4w" );
	lname .push_back( "bkgd_jz4w" );
	hcolor.push_back( hc.at(hc_n + 2) );
	htitle += " vs JZ4W Bkgd";
      }
      if ( hreg != "all" ) htitle += " [" + hreg + "]";
    }
  }

  // initialize canvas
  TCanvas* c1 = new TCanvas( "c1", "" );

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
  Double_t xint   = 0.0100;                             // x-width per character in lname
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
  Double_t xtxt    = 0.845;
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
  TString  norm_name   = "one";
  
  // initialize stack
  TFile*   f  = 0;
  TH1F*    h  = 0;
  THStack* hs = new THStack( "Stack", htitle );

  // fill stack
  for ( size_t i = 0; i != fname.size(); ++i ) {
    f = TFile::Open( hpath + fname.at(i) + hfile, "READ" );
    if ( !f ) std::cout << "ZERO POINTER" << std::endl;
    else {
      std::cout << "file pointer: " << f                           << std::endl;
      std::cout << "   file name: " << hpath + fname.at(i) + hfile << std::endl;
    }
    f->cd( "EJsHists/" + htree + "/" + hreg );

    // get histogram from file
    h = (TH1F*)gDirectory->Get(hname);
    h->SetDirectory(0);
    h->SetStats(0);

    // normalize histograms
    Double_t norm = norm_factor / h->Integral();
    if ( doNorm ) h->Scale( norm );

    // set line attributes
    h->SetLineWidth( 2 );
    h->SetLineColor( hcolor.at(i) );
    h->SetLineStyle( 1 );
    if ( htype.Contains("xdm") ) {
      if      ( fname.at(i).Contains("_1000_") ) h->SetLineStyle( 2 );
      else if ( fname.at(i).Contains("_600_")  ) h->SetLineStyle( 3 );
    }
    else {
      if      ( fname.at(i).Contains( "EJ_ModelB" ) ) h->SetLineStyle( 2 );
      else if ( fname.at(i).Contains( "EJ_ModelC" ) ) h->SetLineStyle( 3 );
      else if ( fname.at(i).Contains( "EJ_ModelD" ) ) h->SetLineStyle( 7 );
      else if ( fname.at(i).Contains( "EJ_ModelE" ) ) h->SetLineStyle( 8 );
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
  TString hdir = hpath + "../plots/";
  if ( houtdir != "" ) hdir += houtdir + "/";
  TString hout = hdir + "h_" + hname + "_" + hreg + "_" + htype;
  c1->SaveAs( hout + "." + hext );
  if ( doLogy ) {
    gPad->SetLogy();
    hout += "_logy";
    c1->SaveAs( hout + "." + hext );
  }

  c1->Close();
}
