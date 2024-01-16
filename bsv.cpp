#include "bsv.h"
#include <tuple>
#include "bs.h"
#include <tbb/parallel_for.h>

#include <fmt/format.h>


constexpr size_t v_limit = 50	;


///// Black-Scholes price : -1 put, 1 call
void BlsPrices(double * dest , size_t dim, double const *src )
{
	auto f = [dest, src](size_t i)
		{
			auto psrc = src + 8 * i;
			double  CoP, S, X, R, Q, Trate, Tsigma, sig;
			std::tie(CoP, S, X, R, Q, Trate, Tsigma, sig) = std::make_tuple(*psrc, *(psrc+1), *(psrc + 2), *(psrc + 3), *(psrc + 4), *(psrc + 5), *(psrc + 6), *(psrc + 7)	 );
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
#if 0
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

