//3-D scalings - P. Ahrenkieltrf3trf3

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

//
scl3::scl3(double x):trf3()
{
	*this=x*trf3::ident();
}
