//math - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "mth.hpp"

namespace mth{

//
double roundoff(double x)
{
	double xp=fabs(x);
	double r=trunc(xp);
	if(xp-r>0.5)r++;
	if(x<0)r*=-1;
	return r; 	
}

//
double magsqr(double *x,const std::size_t N)
{
	double res=0.;
	for(std::size_t i=0;i<N-1;++i)
		res+=sqr(x[i]);
	return res;
}

}
