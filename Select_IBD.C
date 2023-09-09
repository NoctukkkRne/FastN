#include <iostream>

#include <TAxis.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TString.h>

int main(int argc, char **argv) {

  TCanvas *c = new TCanvas("c", "", 700, 500);

  TString Inputfilename;
  TString Outputfilename;
  TFile **f = new TFile *[3] { nullptr };
  TH1D **h1dPrompt = new TH1D *[3] { nullptr };

  for (int site = 0; site < 3; ++site) {
    Inputfilename = TString::Format("./data_in/AccSub/EH%d_tot.root", site + 1);
    Outputfilename =
        TString::Format("./data_out/AccSub/FastN_EH%d.root", site + 1);
    f[site] = new TFile(Inputfilename, "read");

    h1dPrompt[site] = (TH1D *)f[site]->Get("h1dAcc22Sum");
    h1dPrompt[site]->Rebin(20);
    h1dPrompt[site]->Draw("HIST");

    c->SaveAs(Outputfilename);
  }

  delete[] h1dPrompt;
  delete[] f;

  return 0;
}
