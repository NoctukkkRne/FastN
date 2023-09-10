#include "jinpingStyle.h"
// all users - please change the name of this file to jinpingStyle.C
// Commits to jinpingdocs svn of .C files are not allowed
// #define colzsubtraction_show
// #define nowhite_show
void jinpingStyle() {

  // define names for colours
  /*Int_t black  = 1;
  Int_t red    = 2;
  Int_t green  = 3;
  Int_t blue   = 4;
  Int_t yellow = 5;
  Int_t magenta= 6;
  Int_t cyan   = 7;
  Int_t purple = 9;
  */

  ////////////////////////////////////////////////////////////////////
  // PURPOSE:
  //
  // This macro defines a standard style for (black-and-white)
  // "publication quality" LHCb ROOT plots.
  //
  // USAGE:
  //
  // Include the lines
  //   gROOT->ProcessLine(".L jinpingstyle.C");
  //   jinpingStyle();
  // at the beginning of your root macro.
  //
  // Example usage is given in myPlot.C
  //
  // COMMENTS:
  //
  // Font:
  //
  // The font is chosen to be 132, this is Times New Roman (like the text of
  //  your document) with precision 2.
  //
  // "Landscape histograms":
  //
  // The style here is designed for more or less square plots.
  // For longer histograms, or canvas with many pads, adjustements are needed.
  // For instance, for a canvas with 1x5 histograms:
  //  TCanvas* c1 = new TCanvas("c1", "L0 muons", 600, 800);
  //  c1->Divide(1,5);
  //  Adaptions like the following will be needed:
  //  jinpingStyle->SetTickLength(0.05,"x");
  //  jinpingStyle->SetTickLength(0.01,"y");
  //  jinpingStyle->SetLabelSize(0.15,"x");
  //  jinpingStyle->SetLabelSize(0.1,"y");
  //  jinpingStyle->SetStatW(0.15);
  //  jinpingStyle->SetStatH(0.5);
  //
  // Authors: Thomas Schietinger, Andrew Powell, Chris Parkes, Niels Tuning
  // Maintained by Editorial board member (currently Niels)
  //----------------------------------------------------------------
  // Edited by Jinjing Li at Tsinghua University
  // Mail: lijj16@mails.tsinghua.edu.cn
  // Time: June 9. 2018
  ///////////////////////////////////////////////////////////////////

  // Use times new roman, precision 2
  Int_t jinpingFont = 132; // Old LHCb style: 62;
  // Line thickness
  Double_t jinpingWidth = 2.00; // Old LHCb style: 3.00;
  // Text size
  Double_t jinpingTSize = 0.05;

  // use plain black on white colors
  gROOT->SetStyle("Plain");
  TStyle *jinpingStyle = new TStyle("jinpingStyle", "JinPing plots style");

  // jinpingStyle->SetErrorX(0); //  don't suppress the error bar along X

  jinpingStyle->SetFillColor(1);
  jinpingStyle->SetFillStyle(1001); // solid
  jinpingStyle->SetFrameFillColor(0);
  jinpingStyle->SetFrameBorderMode(0);
  jinpingStyle->SetPadBorderMode(0);
  jinpingStyle->SetPadColor(0);
  jinpingStyle->SetCanvasBorderMode(0);
  jinpingStyle->SetCanvasColor(0);
  jinpingStyle->SetStatColor(0);
  jinpingStyle->SetLegendBorderSize(0);

  // If you want the usual gradient palette (blue -> red)
  // jinpingStyle->SetPalette(1);//1 for root5 style
  // If you want colors that correspond to gray scale in black and white:
  // int colors[8] = {0,1,2,3,4,5,6,7};
  // jinpingStyle->SetPalette(8,colors);
  const Int_t NRGBs = 7;
  const Int_t NCont = 512;
#ifndef colzsubtraction_show
  Double_t stops[NRGBs] = {0.00, 0.0000, 0.00002, 0.3, 0.6, 0.85, 1.00};
#endif

  Double_t _red[NRGBs] = {0.00, 1.00, 1.00, 0.42, 0.87, 1.00, 0.51};
  Double_t _green[NRGBs] = {0.05, 1.00, 1.00, 0.76, 1.00, 0.20, 0.00};
  Double_t _blue[NRGBs] = {0.87, 1.00, 1.00, 0.21, 0.12, 0.00, 0.00};

#ifdef colzsubtraction_show
  Double_t stops[NRGBs] = {0.00, 0.025, 0.04, 0.3, 0.65, 0.85, 1.00};
  // Double_t stops[NRGBs] = { 0.00, 0.35, 0.40, 0.45, 0.65, 0.85, 1.00 };
  // Double_t stops[NRGBs] = { 0.00, 0.5, 0.501, 0.55, 0.65, 0.85, 1.00 };
  // Double_t stops[NRGBs] = { 0.00, 0.06, 0.15, 0.25, 0.65, 0.85, 1.00 };
#endif

#ifdef nowhite_show
  Double_t stops[NRGBs] = {0.00, 0.15, 0.35, 0.50, 0.65, 0.85, 1.00};
  Double_t _red[NRGBs] = {0.00, 0.00, 0.12, 0.42, 0.87, 1.00, 0.51};
  Double_t _green[NRGBs] = {0.00, 0.20, 1.00, 0.76, 1.00, 0.20, 0.00};
  Double_t _blue[NRGBs] = {0.51, 1.00, 0.87, 0.21, 0.12, 0.00, 0.00};
#endif

  TColor::CreateGradientColorTable(NRGBs, stops, _red, _green, _blue, NCont);
  jinpingStyle->SetNumberContours(NCont);

  // set the paper & margin sizes
  jinpingStyle->SetPaperSize(20, 26);
  jinpingStyle->SetPadTopMargin(0.10);
  jinpingStyle->SetPadRightMargin(0.15); // increase to 0.2 for colz plots
  jinpingStyle->SetPadBottomMargin(0.16);
  jinpingStyle->SetPadLeftMargin(0.14);

  // use large fonts
  jinpingStyle->SetLegendFont(jinpingFont);
  jinpingStyle->SetTextFont(jinpingFont);
  jinpingStyle->SetTextSize(jinpingTSize);
  jinpingStyle->SetLabelFont(jinpingFont, "x");
  jinpingStyle->SetLabelFont(jinpingFont, "y");
  jinpingStyle->SetLabelFont(jinpingFont, "z");
  jinpingStyle->SetLabelSize(jinpingTSize, "x");
  jinpingStyle->SetLabelSize(jinpingTSize, "y");
  jinpingStyle->SetLabelSize(jinpingTSize, "z");
  jinpingStyle->SetTitleFont(jinpingFont);
  jinpingStyle->SetTitleFont(jinpingFont, "x");
  jinpingStyle->SetTitleFont(jinpingFont, "y");
  jinpingStyle->SetTitleFont(jinpingFont, "z");
  jinpingStyle->SetTitleSize(1.2 * jinpingTSize, "x");
  jinpingStyle->SetTitleSize(1.2 * jinpingTSize, "y");
  jinpingStyle->SetTitleSize(1.2 * jinpingTSize, "z");

  // use medium bold lines and thick markers
  jinpingStyle->SetLineWidth(jinpingWidth);
  jinpingStyle->SetFrameLineWidth(jinpingWidth);
  jinpingStyle->SetHistLineWidth(jinpingWidth);
  jinpingStyle->SetFuncWidth(jinpingWidth);
  jinpingStyle->SetGridWidth(jinpingWidth);
  jinpingStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes
  jinpingStyle->SetMarkerStyle(20);
  jinpingStyle->SetMarkerSize(1.0);

  // label offsets
  jinpingStyle->SetLabelOffset(0.010, "X");
  jinpingStyle->SetLabelOffset(0.010, "Y");

  // by default, do not display histogram decorations:
  jinpingStyle->SetOptStat(0);
  // jinpingStyle->SetOptStat("emr");  // show only nent -e , mean - m , rms -r
  //  full opts at http://root.cern.ch/root/html/TStyle.html#TStyle:SetOptStat
  jinpingStyle->SetStatFormat("6.3g"); // specified as c printf options
  jinpingStyle->SetOptTitle(0);
  // jinpingStyle->SetOptFit(0);
  // jinpingStyle->SetOptFit(1011); // order is probability, Chi2, errors,
  // parameters
  jinpingStyle->SetOptFit(1);

  // titles
  jinpingStyle->SetTitleOffset(0.95, "X");
  jinpingStyle->SetTitleOffset(0.95, "Y");
  jinpingStyle->SetTitleOffset(1.2, "Z");
  jinpingStyle->SetTitleFillColor(0);
  jinpingStyle->SetTitleStyle(0);
  jinpingStyle->SetTitleBorderSize(0);
  jinpingStyle->SetTitleFont(jinpingFont, "title");
  jinpingStyle->SetTitleX(0.0);
  jinpingStyle->SetTitleY(1.0);
  jinpingStyle->SetTitleW(1.0);
  jinpingStyle->SetTitleH(0.05);

  // look of the statistics box:
  jinpingStyle->SetStatBorderSize(0);
  jinpingStyle->SetStatFont(jinpingFont);
  jinpingStyle->SetStatFontSize(0.05);
  jinpingStyle->SetStatX(0.9);
  jinpingStyle->SetStatY(0.9);
  jinpingStyle->SetStatW(0.25);
  jinpingStyle->SetStatH(0.15);
  // jinpingStyle->SetStatW(0.20);
  // jinpingStyle->SetStatH(0.10);

  // put tick marks on top and RHS of plots
  jinpingStyle->SetPadTickX(1);
  jinpingStyle->SetPadTickY(1);

  // histogram divisions: only 5 in x to avoid label overlaps
  jinpingStyle->SetNdivisions(505, "x"); // 505 or 510 is nice
  jinpingStyle->SetNdivisions(510, "y");

  gROOT->SetStyle("jinpingStyle");
  gROOT->ForceStyle();

  TGaxis::SetMaxDigits(3);
  // add LHCb label
  TPaveText *jinpingName =
      new TPaveText(jinpingStyle->GetPadLeftMargin() + 0.05,
                    0.87 - jinpingStyle->GetPadTopMargin(),
                    jinpingStyle->GetPadLeftMargin() + 0.20,
                    0.95 - jinpingStyle->GetPadTopMargin(), "BRNDC");
  jinpingName->AddText("JinPing");
  jinpingName->SetFillColor(0);
  jinpingName->SetTextAlign(12);
  jinpingName->SetBorderSize(0);

  TText *jinpingLabel = new TText();
  jinpingLabel->SetTextFont(jinpingFont);
  jinpingLabel->SetTextColor(1);
  jinpingLabel->SetTextSize(jinpingTSize);
  jinpingLabel->SetTextAlign(12);

  TLatex *jinpingLatex = new TLatex();
  jinpingLatex->SetTextFont(jinpingFont);
  jinpingLatex->SetTextColor(1);
  jinpingLatex->SetTextSize(jinpingTSize);
  jinpingLatex->SetTextAlign(12);
}
