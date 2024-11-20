//3-D reflections - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

using namespace std;

//
rfn3::rfn3(const vtr3 &V):trf3()
{
	*this=-rtn3(V,trg::Pi);
}
