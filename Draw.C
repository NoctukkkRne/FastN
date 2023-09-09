#include <iostream>

#include <TCanvas.h>
#include <TF1.h>
#include <TFile.h>
#include <TFitResult.h>
#include <TFitResultPtr.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TTree.h>

double func(double *x, double *par);

int main(int argc, char **argv) {
  TCanvas *c = new TCanvas("c", "", 700, 500);

  TFile *file = new TFile("./data_in/EH1.root", "read");
  TH1D *h = (TH1D *)file->Get("h1dPrompt");
  TF1 *f = new TF1("func", func, 0.0, 100.0, 3);

  f->SetParNames("N0", "E0", "a");
  f->SetParameters(100.0, 128.0, 0.73);

  TFitResultPtr Res = h->Fit("func", "QS", "", 12.0, 100.0);
  Res->Print();
  h->Draw();

  c->SaveAs("./data_out/Prompt.png");

  return 0;
}

double func(double *x, double *par) {

  double E = x[0];

  double N0 = par[0];
  double E0 = par[1];
  double a = par[2];

  return N0 * pow(E / E0, -a - E / E0);
}
