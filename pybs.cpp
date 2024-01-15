#include <pybind11/pybind11.h>
#include "bs.h"

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(pybs, m) {

	m.doc() = "Black Scholes computations";

	m.def("bls_price", &BlsPrice, "Black Scholes price",
		"CoP"_a, "S"_a, "X"_a, "R"_a, "Q"_a, "Trate"_a, "Tsigma"_a, "sig"_a);
}

