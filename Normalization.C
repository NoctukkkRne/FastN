#include <fstream>
#include <iostream>

#include "Func.h"
#include "Global.h"
#include "Rootneed.h"
#include "TMath.h"
#include "jinpingStyle.h"

void Usage();

int main(int argc, char **argv) {

  if (argc != 5) {
    std::cout << "Wrong input!" << std::endl;
    Usage();
    exit(1);
  }

  jinpingStyle();

  TString dataset = argv[1];
  TString site = argv[2];
  const int BinWidth = atoi(argv[3]);
  const double syst_uncertainty = atoi(argv[4]) / 100.0;

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
      new TFile("./data_in/Select_Dt_300ns/" + site + "_tot.root", "read");

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

  TF1 *func_partial_N0 = new TF1("func_partial_N0", partial_N0, 1.5, 100.0, 3);
  TF1 *func_partial_E0 = new TF1("func_partial_E0", partial_E0, 1.5, 100.0, 3);
  TF1 *func_partial_a = new TF1("func_partial_a", partial_a, 1.5, 100.0, 3);

  TF1 *func_expo_poly1 = new TF1("func_expo_poly1", expo_poly1, 1.5, 100.0, 3);
  func_expo_poly1->SetParNames("N0", "E0", "a");
  func_expo_poly1->SetParameters(50.0 * BinWidth, 100.0, 0.73);
  func_expo_poly1->SetLineColor(kBrownCyan);
  TFitResultPtr fit_res =
      h1dAccSub->Fit("func_expo_poly1", "QS; N0", "", 12.0, 100.0);
  fit_res->Print();

  func_partial_N0->SetParameters(func_expo_poly1->GetParameters());
  func_partial_E0->SetParameters(func_expo_poly1->GetParameters());
  func_partial_a->SetParameters(func_expo_poly1->GetParameters());

  double Integ_hist =
      h1dSelect_norm->Integral(h1dSelect_norm->FindBin(1.5 + 0.01),
                               h1dSelect_norm->FindBin(12.0 - 0.01));
  double Integ_hist_err = Integ_hist * syst_uncertainty;
  double Integ_func = func_expo_poly1->Integral(1.5, 12.0) / BinWidth;
  double Integ_func_err = 0.0;
  Integ_func_err += TMath::Power(func_partial_N0->Integral(1.5, 12.0) /
                                     BinWidth * func_expo_poly1->GetParError(0),
                                 2);
  Integ_func_err += TMath::Power(func_partial_E0->Integral(1.5, 12.0) /
                                     BinWidth * func_expo_poly1->GetParError(1),
                                 2);
  Integ_func_err += TMath::Power(func_partial_a->Integral(1.5, 12.0) /
                                     BinWidth * func_expo_poly1->GetParError(2),
                                 2);
  Integ_func_err = TMath::Sqrt(Integ_func_err);

  lg->AddEntry(h1dSelect_norm, "Normalized fast neutron spectrum");
  lg->AddEntry(h1dAccSub, "Extended IBD spectrum");
  lg->SetX1(0.30);
  lg->SetX2(0.80);
  lg->SetY1(0.65);
  lg->SetY2(0.85);

  TH1D *h1dVoid = new TH1D("h1dVoid", "", 1000 / (BinWidth * 10), 0.0, 100.0);
  h1dVoid->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h1dVoid->GetYaxis()->SetTitle(TString::Format("Events / %dMeV", BinWidth));
  h1dVoid->GetXaxis()->SetRangeUser(0.0, 100.0);
  h1dVoid->GetYaxis()->SetRangeUser(0.0, 1.05 * func_expo_poly1->Eval(1.5));

  h1dVoid->Draw();
  h1dSelect_norm->Draw("same");
  h1dAccSub->GetXaxis()->SetRangeUser(12.0, 100.0);
  h1dAccSub->Draw("same");
  func_expo_poly1->Draw("same");
  lg->Draw("same");

  cv->SaveAs("./data_out/Normalization_" + site +
             TString::Format("_%dMeV.png", BinWidth));

  std::ofstream resfile;
  resfile.open("./data_out/Normalization_" + site + ".csv", std::ios::app);
  resfile << BinWidth << "MeV, ";
  resfile << syst_uncertainty * 100.0 << "%, ";
  resfile << Integ_hist << ", ";
  resfile << Integ_func << ", ";
  resfile << (Integ_func - Integ_hist) / Integ_hist * 100.0 << "%, ";
  resfile << Integ_hist_err << ", ";
  resfile << Integ_func_err << ", ";
  resfile << TMath::Sqrt(TMath::Power(Integ_func_err, 2) +
                         TMath::Power(Integ_hist_err, 2))
          << ", ";
  resfile << std::endl;

  return 0;
}

void Usage() {
  std::cout << "Usage: ./Normalization [dataset] [site] [BinWidth / MeV] "
               "[Uncertainty / %]";
  std::cout << std::endl;
}
