#include <fstream>
#include <iostream>

#include "Func.h"
#include "Global.h"
#include "Rootneed.h"
#include "jinpingStyle.h"

void Usage();

int main(int argc, char **argv) {

  if (argc != 4) {
    std::cout << "Wrong input!" << std::endl;
    Usage();
    exit(1);
  }

  jinpingStyle();

  TString dataset = argv[1];
  TString site = argv[2];
  int BinWidth = atoi(argv[3]);

  TCanvas *cv = new TCanvas("c", "", 700, 500);
  TLegend *lg = new TLegend();

  TFile *file_AccSub = nullptr;
  if (dataset == "P17B") {
    file_AccSub =
        new TFile("./data_in/AccSub_P17B/" + site + "_tot.root", "read");
  } else if (dataset == "Full") {
    file_AccSub = new TFile("./data_in/AccSub/" + site + "_tot.root", "read");
  } else {
    exit(1);
  }
  TFile *file_Select =
      new TFile("./data_in/Select/" + site + "_tot.root", "read");

  h1dAccSub = (TH1D *)file_AccSub->Get("h1dAcc22Sum");
  if (dataset == "P17B") {
    h1dSelect = (TH1D *)file_Select->Get("h1dPrompt_1");
  } else if (dataset == "Full") {
    h1dSelect = (TH1D *)file_Select->Get("h1dPrompt_0");
  } else {
    exit(1);
  }

  h1dAccSub->SetName("h1dAccSub");
  h1dSelect->SetName("h1dSelect");

  double A = h1dAccSub->Integral(h1dAccSub->FindBin(12.0 + 0.01),
                                 h1dAccSub->FindBin(100.0 - 0.01)) /
             h1dSelect->Integral(h1dSelect->FindBin(12.0 + 0.01),
                                 h1dSelect->FindBin(100.0 - 0.01));

  h1dAccSub->Rebin(BinWidth * 10);
  h1dSelect->Rebin(BinWidth * 10);

  TH1D *h1dSelect_norm = new TH1D(*h1dSelect);
  h1dSelect_norm->Reset();
  h1dSelect_norm->SetName("h1dSelect_norm");
  h1dSelect_norm->Add(h1dSelect, A);

  h1dAccSub->SetMarkerColor(kRed);
  h1dAccSub->SetLineColor(kRed);
  h1dSelect_norm->SetMarkerColor(kBlue);
  h1dSelect_norm->SetLineColor(kBlue);

  h1dSelect_norm->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h1dSelect_norm->GetYaxis()->SetTitle(
      TString::Format("Events / %dMeV", BinWidth));

  h1dSelect_norm->GetXaxis()->SetRangeUser(0.0, 100.0);
  h1dSelect_norm->GetYaxis()->SetRangeUser(0.0,
                                           1.25 * h1dSelect_norm->GetMaximum());

  TF1 *func_expo_poly1 = new TF1("func_expo_poly1", expo_poly1, 0.0, 100.0, 3);
  func_expo_poly1->SetParNames("N", "E0", "a");
  func_expo_poly1->SetParameters(50.0 * BinWidth, 100.0, 0.73);
  func_expo_poly1->SetLineColor(kBrownCyan);
  TFitResultPtr fit_res =
      h1dSelect_norm->Fit("func_expo_poly1", "QS; N0", "", 12.0, 100.0);
  fit_res->Print();

  double Integ_hist =
      h1dSelect_norm->Integral(h1dSelect_norm->FindBin(1.5 + 0.01),
                               h1dSelect_norm->FindBin(12.0 - 0.01));
  double Integ_func = func_expo_poly1->Integral(1.5, 12.0) / BinWidth;

  lg->AddEntry(h1dSelect_norm, "Normalized fast neutron spectrum");
  lg->AddEntry(h1dAccSub, "Extended IBD spectrum");
  lg->SetX1(0.30);
  lg->SetX2(0.80);
  lg->SetY1(0.65);
  lg->SetY2(0.85);

  h1dSelect_norm->Draw("");
  h1dAccSub->Draw("same");
  func_expo_poly1->Draw("same");
  lg->Draw("same");

  cv->SaveAs("./data_out/Normalization_" + site +
             TString::Format("_%dMeV.png", BinWidth));

  std::ofstream resfile;
  resfile.open("./data_out/Normalization_" + site + ".txt", std::ios::app);
  resfile << BinWidth << ":  ";
  resfile << Integ_hist << "  " << Integ_func << "  "
          << (Integ_func - Integ_hist) / Integ_hist * 100.0 << "%" << std::endl;

  return 0;
}

void Usage() {
  std::cout << "Usage: ./Normalization [dataset] [site] [BinWidth / MeV]";
  std::cout << std::endl;
}
