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
  double N0 = par[0];
  double E0 = par[1];
  double a = par[2];

  return N0 * TMath::Power(E / E0, -a - E / E0);
}

double partial_N0(double *x, double *par) {

  double E = x[0];
  double N0 = par[0];
  double E0 = par[1];
  double a = par[2];

  return TMath::Power(E / E0, -a - E / E0);
}

double partial_E0(double *x, double *par) {

  double E = x[0];
  double N0 = par[0];
  double E0 = par[1];
  double a = par[2];

  double fac1 = TMath::Power(E / E0, -E / E0 - a);
  double fac2 = E / TMath::Power(E0, 2);
  double fac3 = TMath::Log(E / E0) + 1.0 + a * E0 / E;

  return N0 * fac1 * fac2 * fac3;
}

double partial_a(double *x, double *par) {

  double E = x[0];
  double N0 = par[0];
  double E0 = par[1];
  double a = par[2];

  return -N0 * TMath::Log(E / E0) * TMath::Power(E / E0, -a - E / E0);
}
