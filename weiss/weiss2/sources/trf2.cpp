//transformations - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss2.hpp"

using namespace std;

constexpr const trf2 trf2::To=trf2::ident();

//
trf2::trf2(const arr::darr2 &D)
{
	if((D.size(0)==2)&&(D.size(1)==2))
		for(size_t i=0;i<2;++i)
			for(size_t j=0;j<2;++j)
				_p[i][j]=D(i,j);
	else
		arr::err=-1;
}

//
trf2::operator arr::darr2() const
{
	arr::darr2 A(3,3);
	for(size_t i=0;i<2;++i)
		for(size_t j=0;j<2;++j)
			A(i,j)=_p[i][j];
	return A;
}

//
vtr2 trf2::operator*(const vtr2 &V) const
{
	double x[2]={0.,0.};
	for(size_t i=0;i<2;++i)
		for(size_t j=0;j<2;++j)
			x[i]+=_p[i][j]*V(j);
	return vtr2(x);
}

//
pnt2 trf2::operator*(const pnt2 &P) const
{
	double x[2]={0.,0.};
	for(size_t i=0;i<2;++i)
		for(size_t j=0;j<2;++j)
			x[i]+=_p[i][j]*P(j);
	return pnt2(x);
}
//
trf2 trf2::operator*(const trf2 &T) const
{
	trf2 Tp;
	for(size_t i=0;i<2;++i)
		for(size_t j=0;j<2;++j)
			for(size_t k=0;k<2;++k)
				Tp._p[i][j]+=_p[i][k]*T._p[k][j];
	return Tp;
}

//
trf2 trf2::inv() const
{
	return arr::darr2(*this).inv();
}


//resolve predef
vtr2 vtr2::operator*=(const trf2 &T)
{
	return *this=T*(*this);
}

//resolve predef
pnt2 pnt2::operator*=(const trf2 &T)
{
	return *this=T*(*this);
}

//
trf2 operator*(double x,const trf2 &T)
{
	trf2 Tp;
	for(size_t i=0;i<2;++i)
		for(size_t j=0;j<2;++j)
			Tp._p[i][j]=x*T._p[i][j];
	return Tp;
}

//
trf2 operator/(double x,const trf2 &T)
{
	return x*T.inv();
}
