//3-D reflections - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

using namespace std;

//
Rfn3::Rfn3(const Vtr3 &V):Trf3()
{
	*this=-Rtn3(V,trg::Pi);
}
