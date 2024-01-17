#include "bs.h"
#include <algorithm>
#include <cmath>
#include <boost/math/tools/toms748_solve.hpp>
#include <mkl.h>
#include "rando.h"


///// Black-Scholes price : -1 put, 1 call
//double BlsPrice(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);
//
//
///// Black-Scholes delta : -1 put, 1 call
//double BlsDelta(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);
//
///// Black-Scholes gamma : -1 put, 1 call
//double BlGamma(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);
//
///// Black-Scholes vega : -1 put, 1 call
//double BlsVega(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);
//
///// Black-Scholes implied voilatility: -1 put, 1 call
//double BlsImpliedVol(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double price);
//
//double NormCdf(double x);



inline double BlsD1(double S, double X, double R, double Q, double Trate, double Tsigma, double sig)
{
	return (log(S / X) + (R - Q) * Trate + sig * sig * Tsigma / 2) / (sig * sqrt(Tsigma));
}

inline double BlsD2(double S, double X, double R, double Q, double Trate, double Tsigma, double sig)
{
	if (S == 0)
	{
		if (X == 0)
			return 20;
		else
			return -20;
	}
	if (X == 0) return 20;

	return (log(S / X) + (R - Q) * Trate - sig * sig * Tsigma / 2) / (sig * sqrt(Tsigma));
}

inline double BlsD2(double d1, double Tsigma, double sig)
{
	return d1 - (sig * sqrt(Tsigma));
}


double BlsPrice2(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig)
{
	double d1, d2;
	if (fabs(Tsigma) < 1e-8)
	{
		return std::max(CoP * (X - S), 0.);
	}
	d1 = BlsD1(S, X, R, Q, Trate, Tsigma, sig);
	d2 = BlsD2(d1, Tsigma, sig);
	double res = S * exp(-Q * Trate) * NormCdf(CoP * d1) - X * exp(-R * Trate) * NormCdf(CoP * d2);
	res *= CoP;
	// double put = - S * exp(-Q * Trate) * NormCdf(-d1) + X * exp(-R * Trate) * NormCdf(-d2);
	return res;
}

double BlsPrice(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig)
{
	if (fabs(Tsigma) < 1e-8)
		return std::max(CoP * (X - S), 0.);
	double ssTs = sig * sqrt(Tsigma);
	double d1 = (log(S / X) + (R - Q) * Trate + sig * sig * Tsigma / 2) / (ssTs);
	double d2 = d1 - (ssTs);
	double res = S * exp(-Q * Trate) * NormCdf(CoP * d1) - X * exp(-R * Trate) * NormCdf(CoP * d2);
	res *= CoP;
	// double put = - S * exp(-Q * Trate) * NormCdf(-d1) + X * exp(-R * Trate) * NormCdf(-d2);
	return res;
}

double BlsPrice_noQ(double CoP, double S, double X, double R, double Trate, double Tsigma, double sig)
{
	if (fabs(Tsigma) < 1e-8)
		return std::max(CoP * (X - S), 0.);
	double ssTs = sig * sqrt(Tsigma);
	double d1 = (log(S / X) + (R)*Trate + sig * sig * Tsigma / 2) / (ssTs);
	double d2 = d1 - (ssTs);
	double res = S * NormCdf(CoP * d1) - X * exp(-R * Trate) * NormCdf(CoP * d2);
	res *= CoP;
	// double put = - S * exp(-Q * Trate) * NormCdf(-d1) + X * exp(-R * Trate) * NormCdf(-d2);
	return res;
}

double BlsPrice_noQ2(double CoP, double S, double X, double R, double Trate, double Tsigma, double sig)
{
	if (fabs(Tsigma) < 1e-8)
		return std::max(CoP * (X - S), 0.);
	double ssTs = sig * sqrt(Tsigma);
	double d1 = (log(S / X) + (R)*Trate + sig * sig * Tsigma / 2) / (ssTs);
	double d2 = d1 - (ssTs);
	double res = S * NormCdf(CoP * d1) - X * exp(-R * Trate) * NormCdf(CoP * d2);
	res *= CoP;

	double a = log(S / X);
	double b = -Trate * R;
	double sig_sig_two = sig * sig * 2.;
	double z = Tsigma * sig_sig_two;

	double c = 0.25 * z;
	double e = exp(b);
	double y = 1.0 / sqrt(z);

	double w1 = (a - b + c) * y;
	double w2 = (a - b - c) * y;
	d1 = erf(CoP * w1);
	d2 = erf(CoP * w2);
	d1 = 0.5 + 0.5 * d1;
	d2 = 0.5 + 0.5 * d2;

	res = S * d1 - X * e * d2;
	res *= CoP;

	return res;
}



double BlsDelta(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig)
{
	double res;
	double d1 = BlsD1(S, X, R, Q, Trate, Tsigma, sig);
	res = CoP * exp(-Q * Trate) * NormCdf(CoP * d1);
	//put res = exp(-Q * T) * (rando::NormCdf(d1) - 1);
	return res;
}

double BlsGamma(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig)
{
	double res;
	double unsursdt = 1 / (sig * sqrt(Tsigma));
	if (S < 1e-10) return 0;
	double d1 = BlsD1(S, X, R, Q, Trate, Tsigma, sig);
	res = exp(-Q * Trate) * NormPdf(d1) * unsursdt / S;
	return res;
}

double BlsVega(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig)
{
	double res;
	double d1 = BlsD1(S, X, R, Q, Trate, Tsigma, sig);
	res = exp(-Q * Trate) * S * sqrt(Tsigma) * NormPdf(d1);
	return res;

}


double BlsImpliedVol(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double price)
{
	auto f = [=](double sig)
		{
			return BlsPrice(CoP, S, X, R, Q, Trate, Tsigma, S) - price;
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


double BlsImpliedVol_noQ(double CoP, double S, double X, double R, double Trate, double Tsigma, double price)
{
	auto f = [=](double sig)
		{
			//fmt::print("{}/{}/{}")
			double pr = BlsPrice_noQ(CoP, S, X, R, Trate, Tsigma, sig);
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