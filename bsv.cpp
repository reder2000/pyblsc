#include "bsv.h"
#include <tuple>
#include "fbs.h"
#include <tbb/parallel_for.h>


#if defined(sldkjgslkdjglk)

#include <fmt/format.h>
//#include <mkl.h>


// #include <BS_thread_pool.hpp> // BS::thread_pool
// #include <future>             // std::future

constexpr size_t v_limit = 5000;


///// Black-Scholes price : -1 put, 1 call
void BlsPrices(double* dest, size_t dim, double const* src)
{
	auto f = [&dest, &src](size_t i)
		{
			auto psrc = src + 8 * i;
			double  CoP, S, X, R, Q, Trate, Tsigma, sig;
			std::tie(CoP, S, X, R, Q, Trate, Tsigma, sig) = std::make_tuple(*psrc, *(psrc + 1), *(psrc + 2), *(psrc + 3), *(psrc + 4), *(psrc + 5), *(psrc + 6), *(psrc + 7));
			// fmt::print("{},{},{},{},{},{},{},{}\n", CoP, S, X, R, Q, Trate, Tsigma, sig);
			*(dest + i) = BlsPrice(CoP, S, X, R, Q, Trate, Tsigma, sig);
		};
	if (dim < v_limit) {
		for (size_t i = 0; i < dim; ++i)
		{
			f(i);
		}
	}
	else
	{
#if 1
		tbb::parallel_for((size_t)0, dim, f);
#else
		auto apply = [&](const tbb::blocked_range<size_t>& r)
			{
				for (auto i = r.begin(); i != r.end(); ++i)
					f(i);
			};
		tbb::parallel_for(tbb::blocked_range<size_t>(0, dim), apply);
#endif	
	}
}


void BlsPrices_noQ2(double* dest, size_t dim, double const* src)
{
	auto f = [&dest, &src](size_t i)
		{
			auto psrc = src + 7 * i;
			double  CoP, S, X, R, Trate, Tsigma, sig;
			std::tie(CoP, S, X, R, Trate, Tsigma, sig) = std::make_tuple(*psrc, *(psrc + 1), *(psrc + 2), *(psrc + 3), *(psrc + 4), *(psrc + 5), *(psrc + 6));
			// fmt::print("{},{},{},{},{},{},{},{}\n", CoP, S, X, R, Q, Trate, Tsigma, sig);
			*(dest + i) = BlsPrice_noQ(CoP, S, X, R, Trate, Tsigma, sig);
		};
	if (dim < v_limit) {
		for (size_t i = 0; i < dim; ++i)
		{
			f(i);
		}
	}
	else
	{
#if 1
		tbb::parallel_for((size_t)0, dim, f);
#else
		auto apply = [&](const tbb::blocked_range<size_t>& r)
			{
				for (auto i = r.begin(); i != r.end(); ++i)
					f(i);
			};
		tbb::parallel_for(tbb::blocked_range<size_t>(0, dim), apply);
#endif	
	}
}

constexpr size_t v_limit2 = 1000;
constexpr size_t v_limit2_ch = 500;


void BlsPrices_noQ(double* dest, size_t dim, double const* src)
{


	auto f = [&](size_t i)
		{
			auto psrc = src + 7 * i;
			double  CoP, S, X, R, Trate, Tsigma, sig;
			std::tie(CoP, S, X, R, Trate, Tsigma, sig) = std::make_tuple(*psrc, *(psrc + 1), *(psrc + 2), *(psrc + 3), *(psrc + 4), *(psrc + 5), *(psrc + 6));
			// fmt::print("{},{},{},{},{},{},{},{}\n", CoP, S, X, R, Q, Trate, Tsigma, sig);
			*(dest + i) = BlsPrice_noQ(CoP, S, X, R, Trate, Tsigma, sig);
			// std::this_thread::sleep_for(std::chrono::milliseconds(1));
		};
	if (dim < v_limit2_ch) {
		for (size_t i = 0; i < dim; ++i)
		{
			f(i);
		}
	}
	else
	{
#if 1
		std::vector<std::pair<size_t, size_t>> v;
		v.reserve(dim / v_limit2 + 1);
		size_t i = 0;
		while (i < dim)
		{
			size_t j = std::min(i + v_limit2_ch, dim);
			v.push_back({ i, j });
			i = j;
		}
		auto g = [&](size_t j)
			{
				//fmt::print("{}/{}...", v[j].first, v[j].second);
				for (size_t i = v[j].first; i < v[j].second; i++)
					f(i);
			};

#if 1
		tbb::parallel_for((size_t)0, v.size(), g);
#else
		auto apply = [&](const tbb::blocked_range<size_t>& r)
			{
				for (auto i = r.begin(); i != r.end(); ++i)
					f(i);
			};
		tbb::parallel_for(tbb::blocked_range<size_t>(0, dim), apply);
#endif
#else
		BS::thread_pool pool(12);
		BS::multi_future<void> loop_future = pool.submit_loop((size_t)0, dim, f, v_limit2_ch);
		loop_future.wait();
#endif
	}
}

constexpr size_t iv_v_limit = 2500;

void BlsImpliedVols_noQ2(double* dest, size_t dim, double const* src)
{
	auto f = [&dest, &src](size_t i)
		{
			auto psrc = src + 7 * i;
			double  CoP, S, X, R, Trate, Tsigma, price;
			std::tie(CoP, S, X, R, Trate, Tsigma, price) = std::make_tuple(*psrc, *(psrc + 1), *(psrc + 2), *(psrc + 3), *(psrc + 4), *(psrc + 5), *(psrc + 6));
			// fmt::print("{},{},{},{},{},{},{},{}\n", CoP, S, X, R, Q, Trate, Tsigma, sig);
			*(dest + i) = BlsImpliedVol_noQ(CoP, S, X, R, Trate, Tsigma, price);
		};
	if (dim < iv_v_limit) {
		for (size_t i = 0; i < dim; ++i)
		{
			f(i);
		}
	}
	else
	{
#if 1
		tbb::parallel_for((size_t)0, dim, f);
#else
		auto apply = [&](const tbb::blocked_range<size_t>& r)
			{
				for (auto i = r.begin(); i != r.end(); ++i)
					f(i);
			};
		tbb::parallel_for(tbb::blocked_range<size_t>(0, dim), apply);
#endif	
	}
}

constexpr size_t iv_v_limit2 = 30;

void BlsImpliedVols_noQ(double* dest, size_t dim, double const* src)
{


	auto f = [&dest, &src, &dim](size_t i)
		{
			auto psrc = src + 7 * i;
			double  CoP, S, X, R, Trate, Tsigma, price;
			std::tie(CoP, S, X, R, Trate, Tsigma, price) = std::make_tuple(*psrc, *(psrc + 1), *(psrc + 2), *(psrc + 3), *(psrc + 4), *(psrc + 5), *(psrc + 6));
			// fmt::print("{},{},{},{},{},{},{},{}\n", CoP, S, X, R, Q, Trate, Tsigma, sig);
			*(dest + i) = BlsImpliedVol_noQ(CoP, S, X, R, Trate, Tsigma, price);
		};
	if (dim < iv_v_limit2) {
		for (size_t i = 0; i < dim; ++i)
		{
			f(i);
		}
	}
	else
	{
		std::vector<std::pair<size_t, size_t>> v;
		v.reserve(dim / iv_v_limit2 + 1);
		size_t i = 0;
		while (i < dim)
		{
			size_t j = std::min(i + iv_v_limit2, dim);
			v.push_back({ i, j });
			i = j;
		}
		auto g = [&](size_t j)
			{
				for (size_t i = v[j].first; i < v[j].second; i++)
					f(i);
			};

#if 1
		tbb::parallel_for((size_t)0, v.size(), g);
#else
		auto apply = [&](const tbb::blocked_range<size_t>& r)
			{
				for (auto i = r.begin(); i != r.end(); ++i)
					f(i);
			};
		tbb::parallel_for(tbb::blocked_range<size_t>(0, dim), apply);
#endif	
	}
}


#if defined(WITH_MKL)

constexpr size_t NBUF = 1024;


void BlackScholesFormula_MKL(double* __restrict vres, int nopt,
	const double* __restrict CoP, const double* __restrict S, const double* __restrict X, const double* __restrict R, const double* __restrict Trate,
	const double* __restrict Tsigma, const double* __restrict sig)
{
	int i;

	//#pragma omp parallel for                                 \
	//        shared(s0, x, t, vcall, vput, mr, sig_sig_two, nopt) \
	//        default(none)
	for (i = 0; i < nopt; i += NBUF)
	{
		int j;
		double* a, * b, * c, * y, * z, * e, * ss, * a_b, * tss;
		double* d1, * d2, * w1, * w2;
		__declspec(align(16)) double Buffer[NBUF * 7];
		// This computes vector length for the last iteration of the loop
		// in case nopt is not exact multiple of NBUF
#define MY_MIN(x, y) ((x) < (y)) ? (x) : (y)
		int nbuf = MY_MIN(NBUF, nopt - i);

		a = Buffer + NBUF * 0;          w1 = a; d1 = w1;
		c = Buffer + NBUF * 1;          w2 = c; d2 = w2;
		b = Buffer + NBUF * 2; e = b;
		z = Buffer + NBUF * 3; y = z;
		ss = Buffer + NBUF * 4;
		a_b = Buffer + NBUF * 5;
		tss = Buffer + NBUF * 6;
		// double mr = -r;
		// double sig_sig_two = sig * sig * 2.;


		// Must set VML accuracy in each thread
		vmlSetMode(VML_HA);

		//  double a = log(S/X);
		vdDiv(nbuf, S + i, X + i, a);
		vdLn(nbuf, a, a);
		vdMul(nbuf, sig + i, sig + i, ss);
		vdMul(nbuf, R, Trate, b);
		vdSub(nbuf, a, b, a_b);
		vdMul(nbuf, Tsigma, ss, z);

#pragma simd
		for (j = 0; j < nbuf; j++)
		{
			// double b = -Trate * R;
			// b[j] = - Trate[i + j] * R[i+j];
			// a-b
			// a[j] = a[j] - b[j];
			// z[j] = Tsigma[i + j] * ss[i+j]  * 2.0;
			z[j] *= 2;
			c[j] = 0.25 * z[j];
		}
		//  double z = Tsigma    * sig_sig_two;
		// double y = 1.0 / sqrt(z);
		vdInvSqrt(nbuf, z, y);
		vdExp(nbuf, b, e);

		vdAdd(nbuf, a_b, c, ss);
		vdMul(nbuf, ss, y, w1);
		vdSub(nbuf, a_b, c, ss);
		vdMul(nbuf, ss, y, w2);

#pragma simd
		//for (j = 0; j < nbuf; j++)
		//{
		//    double aj = a[j];
		//    double cj = c[j];
		//    w1[j] = (aj + cj) * y[j];
		//    w2[j] = (aj - cj) * y[j];
		//}

		vdErf(nbuf, w1, d1);
		vdErf(nbuf, w2, d2);

#pragma simd
		for (j = 0; j < nbuf; j++)
		{
			d1[j] = 0.5 + 0.5 * d1[j];
			d2[j] = 0.5 + 0.5 * d2[j];
			ss[i + j] = S[i + j] * d1[j] - X[i + j] * e[j] * d2[j];
		}
		vdMul(nbuf, ss, CoP, vres);
	}
}


void BlsPrices_noQ_mkl(double* dest, size_t dim, double const* src)
{
	const double* CoP, * S, * X, * R, * Trate, * Tsigma, * sig;
	std::tie(CoP, S, X, R, Trate, Tsigma, sig) = std::make_tuple(src, src + dim, src + dim * 2, src + dim * 3, src + dim * 4, src + dim * 5, src + dim * 6);
	BlackScholesFormula_MKL(dest, dim, CoP, S, X, R, Trate, Tsigma, sig);
}

#endif

double BlsImpliedVols_fd_expanded(double* dest, size_t dim, double CoP, double F, double df, double* X, double Tsigma, double* prices)
{
	auto f = [&](size_t i)
		{
			*(dest + i) = BlsImpliedVolF(CoP, F, X[i], df, Tsigma, prices[i]);
		};
	if (dim < iv_v_limit2) {
		for (size_t i = 0; i < dim; ++i)
		{
			f(i);
		}
	}
	else
	{
		std::vector<std::pair<size_t, size_t>> v;
		v.reserve(dim / iv_v_limit2 + 1);
		size_t i = 0;
		while (i < dim)
		{
			size_t j = std::min(i + iv_v_limit2, dim);
			v.push_back({ i, j });
			i = j;
		}
		auto g = [&](size_t j)
			{
				for (size_t i = v[j].first; i < v[j].second; i++)
					f(i);
			};

		tbb::parallel_for((size_t)0, v.size(), g);
	}

}

#endif // defined(sldkjgslkdjglk)

void FBlsPrices(double* dest, size_t dim, double const* src) {
	auto f = [&dest, &src](size_t i)
		{
			auto psrc = src + 6 * i;
			double  CoP, F, X, df, Tsigma, sig;
			std::tie(CoP, F, X, df, Tsigma, sig) = std::make_tuple(*psrc, *(psrc + 1), *(psrc + 2), *(psrc + 3), *(psrc + 4), *(psrc + 5));
			*(dest + i) = FBlsPrice(CoP, F, X, df, Tsigma, sig);
		};
	if (dim < 50) {
		for (size_t i = 0; i < dim; ++i)
			f(i);
	}
	else
	{
#if 1
		tbb::parallel_for((size_t)0, dim, f);
#else
		auto apply = [&](const tbb::blocked_range<size_t>& r)
			{
				for (auto i = r.begin(); i != r.end(); ++i)
					f(i);
			};
		tbb::parallel_for(tbb::blocked_range<size_t>(0, dim), apply);
#endif	
	}
}

void FBlsImpliedVols(double* dest, size_t dim, double const* src);

// forwards implied vols 
double FBlsImpliedVols_per_strike(double* dest, size_t dim, double CoP, double F, double df, double* X, double Tsigma, double* prices);