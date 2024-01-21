#include "fbs.h"
#include <algorithm>
#include <cmath>
#include <boost/math/tools/toms748_solve.hpp>
#include "rando.h"
#include <tbb/parallel_for.h>


double FBlsPrice(double CoP, double F, double X, double DF, double Tsigma, double sig)
{
	if (fabs(Tsigma) < 1e-8)
		return std::max(CoP * (X - F), 0.);
	double ssTs = sig * sqrt(Tsigma);
	double d1 = (log(F / X) + sig * sig * Tsigma / 2) / (ssTs);
	double d2 = d1 - (ssTs);
	double res = F * NormCdf(CoP * d1) - X  * NormCdf(CoP * d2);
	res *= CoP * DF;
	return res;
}

double FBlsImpliedVol(double CoP, double F,double X,  double df, double Tsigma, double price)
{
	auto f = [=](double sig)
		{
			//fmt::print("{}/{}/{}")
			double pr = FBlsPrice(CoP, F, X, df, Tsigma, sig);
			return pr - price;
		};
	std::uintmax_t max_iter{ 10 };

	auto pres =
		boost::math::tools::toms748_solve(
			f,
			0.000001,
			10.,
			boost::math::tools::eps_tolerance<double>{},
			max_iter);
	return pres.first;

}

inline double FBlsD1(double F, double X, double Tsigma, double sig)
{
	return (log(F / X) + sig * sig * Tsigma / 2) / (sig * sqrt(Tsigma));
}

inline
double FBlsDelta(double CoP, double F, double X, double df, double Tsigma, double sig)
{
	double res;
	double d1 = FBlsD1(F, X, Tsigma, sig);
	res = CoP * df * NormCdf(CoP * d1);
	return res;
}

inline
double FBlsGamma(double /*CoP*/, double F, double X, double df, double Tsigma, double sig)
{
	if (F < 1e-10) return 0;
	double res;
	double one_upon_sst = 1. / (sig * sqrt(Tsigma));
	double d1 = FBlsD1(F, X, Tsigma, sig);
	res = df * NormCdf(d1) * one_upon_sst / F;
	return res;
}

inline
double FBlsVega(double /*CoP*/, double F, double X, double df, double Tsigma, double sig)
{
	double res;
	double d1 = FBlsD1(F, X, Tsigma, sig);
	res = df * NormCdf(d1) * sqrt(Tsigma) * F;
	return res;

}

double FBlsGreek(BSGreeks greek, double CoP, double F, double X, double df, double Tsigma, double sig)
{
	using funt = decltype(&FBlsDelta);
	static funt funs[5] = {&FBlsPrice, &FBlsDelta, &FBlsGamma, &FBlsVega,&FBlsImpliedVol};
	return funs[static_cast<size_t>(greek)](CoP,F, X, df, Tsigma, sig);

}

// test only
void _FBlsGreeks_seq( double *res, size_t nopts, BSGreeks greek,double CoP, double F, const double *X, double df, double Tsigma, const double *sig, bool par)
{
	using funt = decltype(&FBlsDelta);
	static funt funs[5] = { &FBlsPrice, &FBlsDelta, &FBlsGamma, &FBlsVega,&FBlsImpliedVol };
	if (par) {
		auto f = [&](size_t i)
			{
				res[i] = funs[static_cast<size_t>(greek)](CoP, F, X[i], df, Tsigma, sig[i]);
			};
		tbb::parallel_for((size_t)0, nopts, f);
	}
	else {
		for (size_t i = 0; i < nopts; ++i)
			res[i] = funs[static_cast<size_t>(greek)](CoP, F, X[i], df, Tsigma, sig[i]);
	}
}

//VolDeltaVega FInvBls(double CoP, double F, double X, double df, double Tsigma, double price)
//{
//	VolDeltaVega res;
//	res._implied_volatility = FBlsImpliedVol(CoP, F, X, df, Tsigma, price);
//	res._delta = FBlsDelta(CoP, F, X, df, Tsigma, res._implied_volatility);
//	res._vega= FBlsVega(CoP, F, X, df, Tsigma, res._implied_volatility);
//	return res;
//}

void FBlsGreeks_seq(double* res, size_t nopts, BSGreeks greek, double CoP, double F, const double* X, double df, double Tsigma, const double* sig)
{
	using funt = decltype(&FBlsDelta);
	static funt funs[5] = { &FBlsPrice, &FBlsDelta, &FBlsGamma, &FBlsVega,&FBlsImpliedVol };
	if ((greek == BSGreeks::implied_volatility && nopts>=20) || (nopts>=500))
	{
		auto f = [&](size_t i)
			{
				res[i] = funs[static_cast<size_t>(greek)](CoP, F, X[i], df, Tsigma, sig[i]);
			};
		tbb::parallel_for((size_t)0, nopts, f);
	}
	else {
		for (size_t i = 0; i < nopts; ++i)
			res[i] = funs[static_cast<size_t>(greek)](CoP, F, X[i], df, Tsigma, sig[i]);
	}
}




