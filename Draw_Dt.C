#include "Rootneed.h"
#include "jinpingStyle.h"

void Usage();

int main(int argc, char **argv) {

  if (argc != 2) {
    Usage();
    exit(1);
  }

  TString site = argv[1];

  TChain *ch = new TChain("Event_OWStag");
  if (site == "EH1" || site == "EH2" || site == "EH3") {
    ch->Add("./data_in/Select_Dt_1000ns/" + site + "_tot.root");
  } else if (site == "All") {
    ch->Add("./data_in/Select_Dt_1000ns/EH1_tot.root");
    ch->Add("./data_in/Select_Dt_1000ns/EH2_tot.root");
    ch->Add("./data_in/Select_Dt_1000ns/EH3_tot.root");
  } else {
    std::cout << "File doesn't exit." << std::endl;
    exit(1);
  }

  jinpingStyle();

  double T2PrevOWSMu = 0.0;
  ch->SetBranchAddress("T2PrevOWSMu", &T2PrevOWSMu);

  TCanvas *c = new TCanvas("c", "", 700, 500);

  TH1D *h = new TH1D("h1dT2PrevOWSMu", "", 99, 10.0, 1000.0);
  h->GetXaxis()->SetTitle("T [ns]");
  h->GetYaxis()->SetTitle("Events / 10ns");

  for (unsigned i = 0; i < ch->GetEntries(); ++i) {
    ch->GetEntry(i);
    h->Fill(T2PrevOWSMu * 1.0e9);
  }

  h->Draw();
  c->SaveAs("./data_out/Dt_" + site + ".png");

  return 0;
}

void Usage() {
  std::cout << "Wrong Input!" << std::endl;
  std::cout << "./Draw_Dt [site], site can be EH1, EH2, EH3 or All."
            << std::endl;
}
