#include <iostream>

#include "Rootneed.h"

TH1D *h1dAccSub;
TH1D *h1dSelect;

void Usage();
double Chi2(double *par);

int main(int argc, char **argv) {

  if (argc != 2) {
    Usage();
    exit(1);
  }

  TString site = argv[1];

  TFile *file_AccSub =
      new TFile("./data_in/AccSub/" + site = "_tot.root", "read");
  TFile *file_Select =
      new TFile("./data_in/Select/" + site + "_tot.root", "read");

  h1dAccSub = (TH1D *)file_AccSub->Get("h1dAccSum");
  h1dSelect = (TH1D *)file_Select->Get("h1dPrompt_0");

  ROOT::Math::Functor *Fcn = new ROOT::Math::Functor(&Chi2, 1);
  ROOT::Minuit2::Minuit2Minimizer *pMinuit =
      new ROOT::Minuit2::Minuit2Minimizer();
  pMinuit->SetFunction(*Fcn);

  return 0;
}

void Usage() {
  std::cout << "Usage: ./Normalization EHx";
  std::cout << std::endl;
}

double Chi2(double *par) {
  double result = 0;

  double N = par[0];

  return result;
}
