#ifndef _FUNC_H_
#define _FUNC_H_

#include "Global.h"
#include "Rootneed.h"

double Chi2(const double *par);
double expo_poly1(double *x, double *par);
double partial_N0(double *x, double *par);
double partial_E0(double *x, double *par);
double partial_a(double *x, double *par);

#endif
