//3-D coordinates - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "weiss3.hpp"

using namespace std;

//
Crd3::Crd3(const arr::darr1 &A)
{
	if(A.size()==3)
	{
		for(size_t i=0;i<3;++i)
			_p[i]=A(i);
	}
	else
		arr::err=-1;
}

//
Crd3::operator arr::darr1() const
{
	arr::darr1 d(3);
	d(0)=_x;d(1)=_y;d(2)=_z;
	return d;
}

//
double& Crd3::operator()(const size_t i)
{
	if(i<3)
		return _p[i];
	else
		arr::err=-1;
	return _p[2];
}

//
double const& Crd3::operator()(const size_t i) const
{
	if(i<3)
		return _p[i];
	else
		arr::err=-1;
	return _p[2];
}

//friend
ostream& operator<<(ostream &os,const Crd3 &C)
{
	os<<"("<<C.x()<<","<<C.y()<<","<<C.z()<<")";
	return os;
}
