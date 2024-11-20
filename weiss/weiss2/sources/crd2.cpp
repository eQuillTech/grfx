//3-D coordinates - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "weiss2.hpp"

using namespace std;

//
crd2::crd2(const arr::darr1 &A)
{
	if(A.size()==2)
	{
		for(size_t i=0;i<2;++i)
			_p[i]=A(i);
	}
	else
		arr::err=-1;
}

//
crd2::operator arr::darr1() const
{
	arr::darr1 d(2);
	d(0)=_x;d(1)=_y;
	return d;
}

//
double& crd2::operator()(const size_t i)
{
	if(i<2)
		return _p[i];
	else
		arr::err=-1;
	return _p[1];
}

//
double const& crd2::operator()(const size_t i) const
{
	if(i<2)
		return _p[i];
	else
		arr::err=-1;
	return _p[1];
}
