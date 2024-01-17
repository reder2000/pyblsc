#pragma once

void BlsPrices(double* dest, size_t dim, double const* src);
void BlsPrices_noQ(double* dest, size_t dim, double const* src);

void BlsImpliedVols_noQ(double* dest, size_t dim, double const* src);

#if !	defined(WITH_MKL)
void BlsPrices_noQ_mkl(double* dest, size_t dim, double const* src);
#endif