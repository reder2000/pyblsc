#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <fmt/format.h>
#include "bs.h"
#include "bsv.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(pybs, m) {

    m.doc() = "Black Scholes computations";

    m.def("bls_price", &BlsPrice, "Black Scholes price",
        "CoP"_a, "S"_a, "X"_a, "R"_a, "Q"_a, "Trate"_a, "Tsigma"_a, "sig"_a);

    m.def("bls_price_noq", &BlsPrice_noQ, "Black Scholes price",
        "CoP"_a, "S"_a, "X"_a, "R"_a,  "Trate"_a, "Tsigma"_a, "sig"_a);

    m.def("bls_impliedvol_noq", &BlsImpliedVol_noQ  , "Black Scholes implied volatility",
        "CoP"_a, "S"_a, "X"_a, "R"_a, "Trate"_a, "Tsigma"_a, "price"_a);


    m.def("bls_prices", [](py::array_t<double> n_out, py::array_t<double> n_in) {
        auto mu_in = n_in.unchecked<2>();
        auto mu_out = n_out.mutable_unchecked<1>();
        size_t dim = mu_out.shape(0);
        if (mu_in.shape(1) != 8)
            throw std::range_error(fmt::format("BS parameters must be (N x) 8 , not {}", mu_in.shape(0)));

        size_t idim = mu_in.shape(0);
        if (dim != idim)
            throw std::range_error(fmt::format("out size {} is not equal to in suze {}", dim, idim));
        double const* src = mu_in.data(0, 0);
        double* dst = mu_out.mutable_data(0);
        BlsPrices(dst, dim, src);
        }
    );

    m.def("bls_prices_noq", [](py::array_t<double> n_out, py::array_t<double> n_in) {
        auto mu_in = n_in.unchecked<2>();
        auto mu_out = n_out.mutable_unchecked<1>();
        size_t dim = mu_out.shape(0);
        if (mu_in.shape(1) != 7)
            throw std::range_error(fmt::format("BS parameters must be (N x) 7 , not {}", mu_in.shape(1)));

        size_t idim = mu_in.shape(0);
        if (dim != idim)
            throw std::range_error(fmt::format("out size {} is not equal to in suze {}", dim, idim));
        double const* src = mu_in.data(0, 0);
        double* dst = mu_out.mutable_data(0);
        BlsPrices_noQ(dst, dim, src);
        }
    );


    m.def("bls_impliedvols_noq", [](py::array_t<double> n_out, py::array_t<double> n_in) {
        auto mu_in = n_in.unchecked<2>();
        auto mu_out = n_out.mutable_unchecked<1>();
        size_t dim = mu_out.shape(0);
        if (mu_in.shape(1) != 7)
            throw std::range_error(fmt::format("BS parameters must be (N x) 7 , not {}", mu_in.shape(1)));

        size_t idim = mu_in.shape(0);
        if (dim != idim)
            throw std::range_error(fmt::format("out size {} is not equal to in suze {}", dim, idim));
        double const* src = mu_in.data(0, 0);
        double* dst = mu_out.mutable_data(0);
        BlsImpliedVols_noQ(dst, dim, src);
        }
    );


#if !defined(WITH_MKL)
    m.def("bls_prices_noq_mkl", [](py::array_t<double> n_out, py::array_t<double> n_in) {
        auto mu_in = n_in.unchecked<2>();
        auto mu_out = n_out.mutable_unchecked<1>();
        size_t dim = mu_out.shape(0);
        if (mu_in.shape(0) != 7)
            throw std::range_error(fmt::format("BS parameters must be 7 (x N) , not {}", mu_in.shape(0)));

        size_t idim = mu_in.shape(1);
        if (dim != idim)
            throw std::range_error(fmt::format("out size {} is not equal to in suze {}", dim, idim));
        double const* src = mu_in.data(0, 0);
        double* dst = mu_out.mutable_data(0);
        BlsPrices_noQ_mkl(dst, dim, src);
        }
    );
#endif

}
