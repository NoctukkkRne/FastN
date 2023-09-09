#include <iostream>

#include <TAxis.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TString.h>
#include <TTree.h>

const int Xbins = 1000;
const int Ybins = 120;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Wrong Input!" << std::endl;
    exit(1);
  }

  int Run, Det, PrevMuTag, PrevOWSnhit, PrevIWSnhit, Fold;
  double T2PrevMu, T2PrevPlMu, T2PrevOWSMu, T2PrevIWSMu, T2PrevAdMu, T2PrevShMu,
      T2PrevNetMu;
  double TrigNum[20], TrigType[20], E[20], X[20], Y[20], Z[20], D2First[20],
      T2PrevSubEvt[20];
  double DT;
  bool InGd;
  int period;

  TString site = argv[1];
  TChain *ch = new TChain("Event");

  ch->SetBranchAddress("Run", &Run);
  ch->SetBranchAddress("Det", &Det);
  ch->SetBranchAddress("T2PrevMu", &T2PrevMu);
  ch->SetBranchAddress("T2PrevPlMu", &T2PrevPlMu);
  ch->SetBranchAddress("T2PrevOWSMu", &T2PrevOWSMu);
  ch->SetBranchAddress("T2PrevIWSMu", &T2PrevIWSMu);
  ch->SetBranchAddress("T2PrevAdMu", &T2PrevAdMu);
  ch->SetBranchAddress("T2PrevShMu", &T2PrevShMu);
  ch->SetBranchAddress("T2PrevNetMu", &T2PrevNetMu);
  ch->SetBranchAddress("PrevMuTag", &PrevMuTag);
  ch->SetBranchAddress("PrevOWSnhit", &PrevOWSnhit);
  ch->SetBranchAddress("PrevIWSnhit", &PrevIWSnhit);
  ch->SetBranchAddress("Fold", &Fold);
  ch->SetBranchAddress("TrigNum", &TrigNum);
  ch->SetBranchAddress("TrigType", &TrigType);
  ch->SetBranchAddress("E", &E);
  ch->SetBranchAddress("X", &X);
  ch->SetBranchAddress("Y", &Y);
  ch->SetBranchAddress("Z", &Z);
  ch->SetBranchAddress("D2First", &D2First);
  ch->SetBranchAddress("T2PrevSubEvt", &T2PrevSubEvt);

  TString inputfilename =
      "/dybfs/users/sunhaozhe/DATA/FastN/Retw/sync_thucali/Output/" + site +
      "/*.TWin.root";
  ch->Add(inputfilename);

  TString outputfilename =
      "/dybfs/users/sunhaozhe/DATA/FastN/Select/" + site + "_tot.root";
  TFile *f = new TFile(outputfilename, "recreate");

  TTree *Event_OWStag = new TTree("Event_OWStag", "OWS-tag events");
  Event_OWStag->Branch("Run", &Run, "Run/I");
  Event_OWStag->Branch("Det", &Det, "Det/I");
  Event_OWStag->Branch("T2PrevMu", &T2PrevMu, "T2PrevMu/D");
  Event_OWStag->Branch("T2PrevPlMu", &T2PrevPlMu, "T2PrevPlMu/D");
  Event_OWStag->Branch("T2PrevOWSMu", &T2PrevOWSMu, "T2PrevOWSMu/D");
  Event_OWStag->Branch("T2PrevIWSMu", &T2PrevIWSMu, "T2PrevIWSMu/D");
  Event_OWStag->Branch("T2PrevAdMu", &T2PrevAdMu, "T2PrevAdMu/D");
  Event_OWStag->Branch("T2PrevShMu", &T2PrevShMu, "T2PrevShMu/D");
  Event_OWStag->Branch("T2PrevNetMu", &T2PrevNetMu, "T2PrevNetMu/D");
  Event_OWStag->Branch("PrevMuTag", &PrevMuTag, "PrevMuTag/I");
  Event_OWStag->Branch("PrevOWSnhit", &PrevOWSnhit, "PrevOWSnhit/I");
  Event_OWStag->Branch("PrevIWSnhit", &PrevIWSnhit, "PrevIWSnhit/I");
  Event_OWStag->Branch("TrigNum", &TrigNum, "TrigNum[2]/I");
  Event_OWStag->Branch("TrigType", &TrigType, "TrigType[2]/I");
  Event_OWStag->Branch("E", &E, "E[2]/I");
  Event_OWStag->Branch("X", &X, "X[2]/I");
  Event_OWStag->Branch("Y", &Y, "Y[2]/I");
  Event_OWStag->Branch("Z", &Z, "Z[2]/I");
  Event_OWStag->Branch("D2First", &D2First, "D2First[2]/D");
  Event_OWStag->Branch("T2PrevSubEvt", &T2PrevSubEvt, "T2PrevSubEvt[2]/D");
  Event_OWStag->Branch("DT", &DT, "DT/D");

  TH2D *h2dEnergy[3][7] = {{nullptr}};
  TH1D *h1dPrompt[3][7] = {{nullptr}};
  for (int k = 0; k < 3; ++k) {
    for (int j = 0; j < 5; ++j) {
      if (j == 0) {
        h2dEnergy[k][j] = new TH2D(TString::Format("h2dEnergy_%d", k), "",
                                   Xbins, 0.0, 100.0, Ybins, 0.0, 12.0);
        h1dPrompt[k][j] =
            new TH1D(TString::Format("h1dPrompt_%d", k), "", Xbins, 0.0, 100.0);
        continue;
      }
      h2dEnergy[k][j] = new TH2D(TString::Format("h2dEnergy_%d_%d", k, j), "",
                                 Xbins, 0.0, 100.0, Ybins, 0.0, 12.0);
      h1dPrompt[k][j] = new TH1D(TString::Format("h1dPrompt_%d_%d", k, j), "",
                                 Xbins, 0.0, 100.0);
    }
    h2dEnergy[k][5] = new TH2D(TString::Format("h2dEnergy_%d_Gd", k), "", Xbins,
                               0.0, 100.0, Ybins, 0.0, 12.0);
    h2dEnergy[k][6] = new TH2D(TString::Format("h2dEnergy_%d_LS", k), "", Xbins,
                               0.0, 100.0, Ybins, 0.0, 12.0);
    h1dPrompt[k][5] =
        new TH1D(TString::Format("h1dPrompt_%d_Gd", k), "", Xbins, 0.0, 100.0);
    h1dPrompt[k][6] =
        new TH1D(TString::Format("h1dPrompt_%d_LS", k), "", Xbins, 0.0, 100.0);
  }

  for (unsigned i = 0; i < ch->GetEntries(); ++i) {
    ch->GetEntry(i);
    DT = D2First[1] + 1000.0 / 600.0 * T2PrevSubEvt[1] * 1.0e6;
    InGd = (sqrt(pow(X[0], 2) + pow(Y[0], 2)) < sqrt(2.5) * 1000.0) &&
           (-1400.0 < Z[0] && Z[0] < 1400.0);

    if (Fold == 2                                    // Double Coincident
        && PrevMuTag == 11000                        // OWS-tag
        && T2PrevOWSMu < 300.0e-9                    // OWS Relation
        && (T2PrevOWSMu + T2PrevSubEvt[1]) > 15.0e-6 // Not Muon-decay Event
        && T2PrevIWSMu > 1200.0e-6                   // IWS Muon Veto
        && T2PrevAdMu > 1200.0e-6                    // Ad Muon Veto
        && T2PrevShMu > 1200.0e-6                    // Shower Muon Veto
        && E[0] < 100.0                              // Prompt High Energy Cut
        && DT < 800.0                                // DT Cut
    ) {

      Event_OWStag->Fill();
      if (Run <= 72455) {
        period = 1;
      } else {
        period = 2;
      }

      h2dEnergy[period][0]->Fill(E[0], E[1]);
      h1dPrompt[period][0]->Fill(E[0]);

      if (InGd) {
        h2dEnergy[period][5]->Fill(E[0], E[1]);
        h1dPrompt[period][5]->Fill(E[0]);
      } else {
        h2dEnergy[period][6]->Fill(E[0], E[1]);
        h1dPrompt[period][6]->Fill(E[0]);
      }

      h2dEnergy[period][Det]->Fill(E[0], E[1]);
      h1dPrompt[period][Det]->Fill(E[0]);
    }
  }

  for (int j = 0; j < 7; ++j) {
    h2dEnergy[0][j]->Add(h2dEnergy[1][j], h2dEnergy[2][j], 1.0, 1.0);
    h1dPrompt[0][j]->Add(h1dPrompt[1][j], h1dPrompt[2][j], 1.0, 1.0);
  }

  Event_OWStag->Write();
  for (int k = 0; k < 3; ++k) {
    for (int j = 0; j < 7; ++j) {
      h2dEnergy[k][j]->Write();
      h1dPrompt[k][j]->Write();
    }
  }

  f->Close();

  return 0;
}
