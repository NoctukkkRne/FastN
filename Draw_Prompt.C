#include <iostream>

#include "Rootneed.h"
#include "jinpingStyle.h"

double func(double *x, double *par);

int main(int argc, char **argv) {

  if (argc != 3) {
    std::cout << "Wrong Input!" << std::endl;
    exit(1);
  }

  TString dataset = argv[1];
  TString site = argv[2];

  TCanvas *c = new TCanvas("c", "", 700, 500);

  TFile *file =
      new TFile("./data_in/Select_Dt_60ns/" + site + "_tot.root", "read");

  TH1D *h = nullptr;
  TH1D *h_Gd = nullptr;
  TH1D *h_LS = nullptr;

  jinpingStyle();

  if (dataset == "P17B") {
    h = (TH1D *)file->Get("h1dPrompt_0");
    h_Gd = (TH1D *)file->Get("h1dPrompt_0_Gd");
    h_LS = (TH1D *)file->Get("h1dPrompt_0_LS");
  } else if (dataset == "Full") {
    h = (TH1D *)file->Get("h1dPrompt_1");
    h_Gd = (TH1D *)file->Get("h1dPrompt_1_Gd");
    h_LS = (TH1D *)file->Get("h1dPrompt_1_LS");
  } else {
    exit(1);
  }

  h->Rebin(20);
  h_Gd->Rebin(20);
  h_LS->Rebin(20);

  h->SetLineColor(kBlack);
  h->SetMarkerColor(kBlack);
  h_Gd->SetLineColor(kBlue);
  h_Gd->SetMarkerColor(kBlue);
  h_LS->SetLineColor(kRed);
  h_LS->SetMarkerColor(kRed);

  h->Draw("HIST");
  h_Gd->Draw("same");
  h_LS->Draw("same");

  c->SaveAs("./data_out/Prompt_" + dataset + "_" + site + ".png");

  return 0;
}

double func(double *x, double *par) {

  double E = x[0];

  double N0 = par[0];
  double E0 = par[1];
  double a = par[2];

  return N0 * pow(E / E0, -a - E / E0);
}
