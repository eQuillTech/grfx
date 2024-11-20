//scalings - P. Ahrenkieltrf2

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss2.hpp"

using namespace std;

//
scl2::scl2(double x):trf2()
{
	for(size_t i=0;i<2;i++)
		for(size_t j=0;j<2;j++)
		{
			_p[i][j]=((i==j)?x:0.);
		}
}
