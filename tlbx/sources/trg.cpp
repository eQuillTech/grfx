//trigonometry - P. Ahrenkiel

#include <cstdlib>
#include <iostream>
#include <math.h>

#include "mth.hpp"
#include "trg.hpp"

namespace trg {

//
double sinc(double x)
{
	constexpr double tol = 1.e-18;
	if (fabs(x)<tol) return 1.;
	return sin(x)/x;
}

}
