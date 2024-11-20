//3-D transformations - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

const trf3 trf3::To(trf3::ident());

//
trf3::trf3()
{
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			_p[i][j]=0;
}

//
trf3::trf3(const arr::darr2 &D)
{
	if((D.size(0)==3)&&(D.size(1)==3))
		for(size_t i=0;i<3;++i)
			for(size_t j=0;j<3;++j)
				_p[i][j]=D(i,j);
	else
		arr::err=-1;
}

//
trf3::trf3(const double p[3][3])
{
	memcpy(_p,p,9*sizeof(double));
}

//
trf3::operator arr::darr2() const
{
	arr::darr2 A(3,3);
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			A(i,j)=_p[i][j];
	return A;
}

//
trf3 trf3::operator+(const trf3 &T) const
{
	trf3 Tp;
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			Tp._p[i][j]=_p[i][j]+T._p[i][j];
	return Tp;
}

//
trf3 trf3::operator*(const trf3 &T) const
{
	trf3 Tp;
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			for(size_t k=0;k<3;++k)
				Tp._p[i][j]+=_p[i][k]*T._p[k][j];
	return Tp;
}

//
trf3 trf3::inv() const
{
	return arr::darr2(*this).inv();
}


//
vtr3 trf3::operator*(const vtr3 &V) const noexcept
{
	double x[3]={0.,0.,0.};
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			x[i]+=_p[i][j]*V(j);
	return vtr3(x);
}

//resolve predef
vtr3 vtr3::operator*=(const trf3 &T)
{
	return *this=T*(*this);
}

//
trf3 operator*(double x,const trf3 &T)
{
	trf3 Tp;
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			Tp._p[i][j]=x*T._p[i][j];
	return Tp;
}

//
trf3 operator/(double x,const trf3 &T)
{
	return x*T.inv();
}

//static
trf3 trf3::ident()
{
	return arr::darr2::ident(3,3);
}

//
trf3::operator simd::float3x3()
{
	using simd::float3;
	float3 row0={(float)_p[0][0],(float)_p[0][1],(float)_p[0][2]};
	float3 row1={(float)_p[1][0],(float)_p[1][1],(float)_p[1][2]};
	float3 row2={(float)_p[2][0],(float)_p[2][1],(float)_p[2][2]};
	
	return simd_matrix(row0,row1,row2);
}

trf3 trf3::operator-() const
{
	return -1.*(*this);
}

//
bas3 trf3::operator*(const bas3 &B) const
{
	return bas3(operator*(B.a()),operator*(B.b()),operator*(B.c()));
}

//
std::ostream& operator<<(std::ostream &os,const trf3 &T)
{
	for(size_t i=0;i<3;++i)
	{
		os<<"("<<T._p[i][0]<<","<<T._p[i][1]<<","<<T._p[i][2]<<")\n";
	}
	return os;
}
