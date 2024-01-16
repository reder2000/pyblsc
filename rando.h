#pragma once

#include <cmath>

double NormPdf(double x);
 double NormCdf(double x);

//inline double NormCdf(double x)
//{
//	return std::erfc(x);
//}


// boost::math::erf_inv		