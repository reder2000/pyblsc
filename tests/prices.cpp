#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "fbs.h"

using Catch::Matchers::WithinAbs;



TEST_CASE("CallPutParity", "[select]")
{
	for (double S=0.5; S<1.5; S+=0.01)
	{
		double df = .97;
		double sig = 0.3;
		auto put = FBlsPrice(-1., S, 1., df, 1., sig);
		auto call = FBlsPrice(1., S, 1., df, 1., sig);
		auto parity = (S -1.)* df;
		REQUIRE_THAT(call - put - parity , WithinAbs(0,1e-6));
	}

}

TEST_CASE("Delta", "[select]")
{
	constexpr double eps = 0.5E-6;
	auto delta = [](double CoP, double F, double X, double DF, double Tsigma, double sig)
		{
			return (FBlsPrice(CoP, F + eps, X, DF, Tsigma, sig) - FBlsPrice(CoP, F - eps, X, DF, Tsigma, sig)) / (2 * eps);
		};

	for (auto CoP : { -1,1 } )
	for (double S = 0.5; S < 1.5; S += 0.01)
	{
		double df = .97;
		double sig = 0.3;
		auto delta_f= FBlsGreek(BSGreeks::delta, CoP, S, 1., df, 1., sig);
		REQUIRE_THAT(delta(CoP, S, 1., df, 1., sig)-delta_f, WithinAbs(0, 1e-6));
	}
}

TEST_CASE("Vega", "[select]")
{
	constexpr double eps = 0.5E-6;
	auto delta = [](double CoP, double F, double X, double DF, double Tsigma, double sig)
		{
			return (FBlsPrice(CoP, F , X, DF, Tsigma, sig + eps) - FBlsPrice(CoP, F , X, DF, Tsigma, sig - eps)) / (2 * eps);
		};

	for (auto CoP : { -1,1 })
		for (double S = 0.5; S < 1.5; S += 0.01)
		{
			double df = .97;
			double sig = 0.3;
			auto delta_f = FBlsGreek(BSGreeks::vega, CoP, S, 1., df, 1., sig);
			REQUIRE_THAT(delta(CoP, S, 1., df, 1., sig) - delta_f, WithinAbs(0, 1e-6));
		}
}

TEST_CASE("Gamma", "[select]")
{
	constexpr double eps = 0.5E-6;
	auto delta = [](auto f, double CoP, double F, double X, double DF, double Tsigma, double sig)
		{
			return (f(CoP, F+ eps, X, DF, Tsigma, sig ) - f(CoP, F- eps, X, DF, Tsigma, sig )) / (2 * eps);
		};
	auto delta_func = [](double CoP, double F, double X, double DF, double Tsigma, double sig)
		{
			return FBlsGreek(BSGreeks::delta, CoP, F, X, DF, Tsigma, sig);
		};

	for (auto CoP : { -1,1 })
		for (double S = 0.5; S < 1.5; S += 0.01)
		{
			double df = .97;
			double sig = 0.3;
			auto gamma = FBlsGreek(BSGreeks::gamma, CoP, S, 1., df, 1., sig);
			double gamma_f = delta(delta_func, CoP, S, 1., df, 1., sig);
			REQUIRE_THAT(gamma_f - gamma, WithinAbs(0, 1e-6));
		}
}


TEST_CASE("IV", "[select]")
{
	constexpr double eps = 0.5E-6;

	for (auto CoP : { -1,1 })
		for (double S = 0.5; S < 1.5; S += 0.01)
		{
			double df = .97;
			double sig = 0.3;
			double pr = FBlsPrice(CoP, S, 1., df, 1., sig);
			double iv = FBlsGreek(BSGreeks::implied_volatility, CoP, S, 1., df, 1., pr);
			REQUIRE_THAT(iv-sig, WithinAbs(0, 1e-6));
		}
}



TEST_CASE("IV2", "[select]")
{
	constexpr double eps = 0.5E-6;

	for (auto CoP : { -1,1 })
		for (double sig = 0.05; sig < 2.5; sig += 0.01)
		{
			double df = .97;
			double pr = FBlsPrice(CoP, 1.1, 1., df, 1., sig);
			double iv = FBlsGreek(BSGreeks::implied_volatility, CoP, 1.1, 1., df, 1., pr);
			REQUIRE_THAT(iv - sig, WithinAbs(0, 1e-6));
		}
}