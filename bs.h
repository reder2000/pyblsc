//#pragma once
//
////double BlsPrice(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);
////
////double BlsPrice_noQ(double CoP, double S, double X, double R, double Trate, double Tsigma, double sig);
////
////
/////// Black-Scholes delta : -1 put, 1 call
////double BlsDelta(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);
////
/////// Black-Scholes gamma : -1 put, 1 call
////double BlGamma(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);
////
/////// Black-Scholes vega : -1 put, 1 call
////double BlsVega(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);
////
/////// Black-Scholes implied voilatility: -1 put, 1 call
////double BlsImpliedVol(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double price);
////
////double BlsImpliedVol_noQ(double CoP, double S, double X, double R, double Trate, double Tsigma, double price);
////
////double FBlsPrice(double CoP, double F, double df, double X, double Tsigma, double sig);
////double FBlsImpliedVol(double CoP, double F, double df, double X, double Tsigma, double price);
//
//
//// Black & Scholes formula for a forward
//double FBlsPrice(double CoP, double F, double X, double DF, double Tsigma, double sig);
//
//struct VolDeltaVega
//{
//	double _implied_volatility =0 ;
//	double _delta =0 ;
//	double _vega =0 ;
//};