#pragma once

double BlsPrice(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);


/// Black-Scholes delta : -1 put, 1 call
double BlsDelta(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);

/// Black-Scholes gamma : -1 put, 1 call
double BlGamma(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);

/// Black-Scholes vega : -1 put, 1 call
double BlsVega(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double sig);

/// Black-Scholes implied voilatility: -1 put, 1 call
double BlsImpliedVol(double CoP, double S, double X, double R, double Q, double Trate, double Tsigma, double price);
