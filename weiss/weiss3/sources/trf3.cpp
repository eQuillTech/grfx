//3-D transformations - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

const Trf3 Trf3::To(Trf3::ident());

//
Trf3::Trf3()
{
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			_p[i][j]=0;
}

//
Trf3::Trf3(const arr::darr2 &D)
{
	if((D.size(0)==3)&&(D.size(1)==3))
		for(size_t i=0;i<3;++i)
			for(size_t j=0;j<3;++j)
				_p[i][j]=D(i,j);
	else
		arr::err=-1;
}

//
Trf3::Trf3(const double p[3][3])
{
	memcpy(_p,p,9*sizeof(double));
}

//
Trf3::operator arr::darr2() const
{
	arr::darr2 A(3,3);
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			A(i,j)=_p[i][j];
	return A;
}

//
Trf3 Trf3::operator+(const Trf3 &T) const
{
	Trf3 Tp;
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			Tp._p[i][j]=_p[i][j]+T._p[i][j];
	return Tp;
}

//
Trf3 Trf3::operator*(const Trf3 &T) const
{
	Trf3 Tp;
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			for(size_t k=0;k<3;++k)
				Tp._p[i][j]+=_p[i][k]*T._p[k][j];
	return Tp;
}

//
Trf3 Trf3::inv() const
{
	return arr::darr2(*this).inv();
}


//
Vtr3 Trf3::operator*(const Vtr3 &V) const noexcept
{
	double x[3]={0.,0.,0.};
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			x[i]+=_p[i][j]*V(j);
	return Vtr3(x);
}

//resolve predef
Vtr3 Vtr3::operator*=(const Trf3 &T)
{
	return *this=T*(*this);
}

//
Trf3 operator*(double x,const Trf3 &T)
{
	Trf3 Tp;
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			Tp._p[i][j]=x*T._p[i][j];
	return Tp;
}

//
Trf3 operator/(double x,const Trf3 &T)
{
	return x*T.inv();
}

//static
Trf3 Trf3::ident()
{
	return arr::darr2::ident(3,3);
}

//
Trf::operator simd::float3x3()
{
	using simd::float3;
	float3 row0={(float)_p[0][0],(float)_p[0][1],(float)_p[0][2]};
	float3 row1={(float)_p[1][0],(float)_p[1][1],(float)_p[1][2]};
	float3 row2={(float)_p[2][0],(float)_p[2][1],(float)_p[2][2]};
	
	return simd_matrix(row0,row1,row2);
}

Trf3 Trf3::operator-() const
{
	return -1.*(*this);
}

//
Bas3 Trf3::operator*(const Bas3 &B) const
{
	return Bas3(operator*(B.a()),operator*(B.b()),operator*(B.c()));
}

//
std::ostream& operator<<(std::ostream &os,const Trf3 &T)
{
	for(size_t i=0;i<3;++i)
	{
		os<<"("<<T._p[i][0]<<","<<T._p[i][1]<<","<<T._p[i][2]<<")\n";
	}
	return os;
}
