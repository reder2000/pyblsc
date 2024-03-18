#pragma once
#include <cstddef>
#include <vector>

//double BlsPrice(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);
//
//double BlsPrice_noQ(double CoP, double S, double X, double R, double Trate, double Tsigma, double sig);
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
//double BlsImpliedVol_noQ(double CoP, double S, double X, double R, double Trate, double Tsigma, double price);
//
//double FBlsPrice(double CoP, double F, double df, double X, double Tsigma, double sig);
//double FBlsImpliedVol(double CoP, double F, double df, double X, double Tsigma, double price);


// Black & Scholes formula for a forward
double FBlsPrice(double CoP, double F, double X, double DF, double Tsigma, double sig);

//struct VolDeltaVega
//{
//	double _implied_volatility = 0;
//	double _delta = 0;
//	double _vega = 0;
//};

// BS  greeks
enum class BSGreeks
{
	price=0, delta, gamma, vega, implied_volatility, implied_volatility_jackel
};


// Black & Scholes greek for a forward
double FBlsGreek(BSGreeks greek, double CoP, double F, double X, double DF, double Tsigma, double sig);

// test only
void _FBlsGreeks_seq(double* res, size_t nopts, BSGreeks greek, double CoP, double F, const double* X, double df, double Tsigma, const double* sig, bool par);

void FBlsGreeks_seq(double* res, size_t nopts, BSGreeks greek, double CoP, double F, const double* X, double df, double Tsigma, const double* sig);

//std::vector<double>  FBlsGreeks_seq(BSGreeks greek, double CoP, double F, const std::vector<double>& X, double df, double Tsigma, const std::vector<double>& sig);