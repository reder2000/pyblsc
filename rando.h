#pragma once

#include <cmath>

double NormPdf(double x);
 double NormCdf(double x);

//inline double NormCdf(double x)
//{
//	return std::erfc(-x / std::sqrt(2)) / 2;	
//}


// boost::math::erf_inv		