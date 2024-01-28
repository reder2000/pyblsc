#pragma once
#include <cstddef>

void FBlsPrices(double* dest, size_t dim, double const* src);

void FBlsImpliedVols(double* dest, size_t dim, double const* src);

// forwards implied vols 
// double FBlsImpliedVols_per_strike(double* dest, size_t dim, double CoP, double F, double df, double* X, double Tsigma, double* prices);	