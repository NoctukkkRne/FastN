#include "Func.h"

double Chi2(const double *par) {
  double result = 0.0;

  double N = par[0];

  for (int i = 7; i <= 50; ++i) {
    result +=
        TMath::Power(
            N * h1dSelect->GetBinContent(i) - h1dAccSub->GetBinContent(i), 2) /
        h1dAccSub->GetBinContent(i);
  }

  return result;
}

double expo_poly1(double *x, double *par) {

  double E = x[0];
  double A = par[0];
  double E0 = par[1];
  double a = par[2];

  return A * TMath::Power(E / E0, -a - E / E0);
}
