#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <fmt/format.h>
#include "fbs.h"
#include "bsv.h"

namespace py = pybind11;
using namespace pybind11::literals;


void _FBlsGreeks_seq_py(py::array_t<double> n_out, BSGreeks greek, double CoP, double F, py::array_t<double> cX_s, double df, double Tsigma, py::array_t<double> csig_s, bool par)
{
    auto out = n_out.mutable_unchecked<1>();
    auto X_s = cX_s.unchecked<1>();
    auto sig_s = csig_s.unchecked<1>();
    size_t nopts = out.shape(0);
    if (nopts != X_s.shape(0))
        throw std::range_error(fmt::format("results {} and strikes size {} must be equal", out.shape(0), X_s.shape(0)));
    if (sig_s.shape(0) != X_s.shape(0))
        throw std::range_error(fmt::format("strikes size {} and prices/vols {}must be equal", X_s.shape(0), sig_s.shape(0)));
    _FBlsGreeks_seq(out.mutable_data(0), nopts, greek, CoP, F, X_s.data(0), df, Tsigma, sig_s.data(0),par);
}

void FBlsGreeks_seq_py(py::array_t<double> n_out, BSGreeks greek, double CoP, double F, py::array_t<double> cX_s, double df, double Tsigma, py::array_t<double> csig_s)
{
    auto out = n_out.mutable_unchecked<1>();
    auto X_s = cX_s.unchecked<1>();
    auto sig_s = csig_s.unchecked<1>();
    size_t nopts = out.shape(0);
    if (nopts != X_s.shape(0))
        throw std::range_error(fmt::format("results {} and strikes size {} must be equal", out.shape(0), X_s.shape(0)));
    if (sig_s.shape(0) != X_s.shape(0))
        throw std::range_error(fmt::format("strikes size {} and prices/vols {}must be equal", X_s.shape(0), sig_s.shape(0)));
    FBlsGreeks_seq(out.mutable_data(0), nopts, greek, CoP, F, X_s.data(0), df, Tsigma, sig_s.data(0));
}

PYBIND11_MODULE(pybs, m) {

    m.doc() = "Black Scholes computations";

    /*m.def("bls_price_fd", &FBlsPrice, "Black Scholes forward price",
        "CoP"_a, "F"_a, "X"_a, "DF"_a, "Tsigma"_a, "sig"_a);*/

    py::enum_<BSGreeks>(m, "BSGreeks")
        .value("price", BSGreeks::price)
        .value("delta", BSGreeks::delta).value("gamma", BSGreeks::gamma).value("vega", BSGreeks::vega).value("implied_volatility",BSGreeks::implied_volatility);

    m.def("FBlsGreek", &FBlsGreek, "Black Scholes forward price",
        "greek"_a, "CoP"_a, "F"_a, "X"_a, "df"_a, "Tsigma"_a, "sig"_a);

    //m.def("FBlsGreeks_seq", &FBlsGreeks_seq_py, "Black Scholes forward price",
      // "dst"_a , "greek"_a, "CoP"_a, "F"_a, "X_s"_a, "df"_a, "Tsigma"_a, "sig_s"_a, "par"_a);

    m.def("FBlsGreeks_seq", &FBlsGreeks_seq_py, "Black Scholes forward price",
        "dst"_a, "greek"_a, "CoP"_a, "F"_a, "X_s"_a, "df"_a, "Tsigma"_a, "sig_s"_a);


//    m.def("bls_price_noq", &BlsPrice_noQ, "Black Scholes price",
//        "CoP"_a, "S"_a, "X"_a, "R"_a,  "Trate"_a, "Tsigma"_a, "sig"_a);
//
//    m.def("bls_impliedvol_noq", &BlsImpliedVol_noQ  , "Black Scholes implied volatility",
//        "CoP"_a, "S"_a, "X"_a, "R"_a, "Trate"_a, "Tsigma"_a, "price"_a);
//
//
//    m.def("bls_prices", [](py::array_t<double> n_out, py::array_t<double> n_in) {
//        auto mu_in = n_in.unchecked<2>();
//        auto mu_out = n_out.mutable_unchecked<1>();
//        size_t dim = mu_out.shape(0);
//        if (mu_in.shape(1) != 8)
//            throw std::range_error(fmt::format("BS parameters must be (N x) 8 , not {}", mu_in.shape(0)));
//
//        size_t idim = mu_in.shape(0);
//        if (dim != idim)
//            throw std::range_error(fmt::format("out size {} is not equal to in suze {}", dim, idim));
//        double const* src = mu_in.data(0, 0);
//        double* dst = mu_out.mutable_data(0);
//        BlsPrices(dst, dim, src);
//        }
//    );
//
//    m.def("bls_prices_noq", [](py::array_t<double> n_out, py::array_t<double> n_in) {
//        auto mu_in = n_in.unchecked<2>();
//        auto mu_out = n_out.mutable_unchecked<1>();
//        size_t dim = mu_out.shape(0);
//        if (mu_in.shape(1) != 7)
//            throw std::range_error(fmt::format("BS parameters must be (N x) 7 , not {}", mu_in.shape(1)));
//
//        size_t idim = mu_in.shape(0);
//        if (dim != idim)
//            throw std::range_error(fmt::format("out size {} is not equal to in suze {}", dim, idim));
//        double const* src = mu_in.data(0, 0);
//        double* dst = mu_out.mutable_data(0);
//        BlsPrices_noQ(dst, dim, src);
//        }
//    );
//
//
//    m.def("bls_impliedvols_noq", [](py::array_t<double> n_out, py::array_t<double> n_in) {
//        auto mu_in = n_in.unchecked<2>();
//        auto mu_out = n_out.mutable_unchecked<1>();
//        size_t dim = mu_out.shape(0);
//        if (mu_in.shape(1) != 7)
//            throw std::range_error(fmt::format("BS parameters must be (N x) 7 , not {}", mu_in.shape(1)));
//
//        size_t idim = mu_in.shape(0);
//        if (dim != idim)
//            throw std::range_error(fmt::format("out size {} is not equal to in suze {}", dim, idim));
//        double const* src = mu_in.data(0, 0);
//        double* dst = mu_out.mutable_data(0);
//        BlsImpliedVols_noQ(dst, dim, src);
//        }
//    );
//
//
//#if defined(WITH_MKL)
//    m.def("bls_prices_noq_mkl", [](py::array_t<double> n_out, py::array_t<double> n_in) {
//        auto mu_in = n_in.unchecked<2>();
//        auto mu_out = n_out.mutable_unchecked<1>();
//        size_t dim = mu_out.shape(0);
//        if (mu_in.shape(0) != 7)
//            throw std::range_error(fmt::format("BS parameters must be 7 (x N) , not {}", mu_in.shape(0)));
//
//        size_t idim = mu_in.shape(1);
//        if (dim != idim)
//            throw std::range_error(fmt::format("out size {} is not equal to in suze {}", dim, idim));
//        double const* src = mu_in.data(0, 0);
//        double* dst = mu_out.mutable_data(0);
//        BlsPrices_noQ_mkl(dst, dim, src);
//        }
//    );
//#endif

}
