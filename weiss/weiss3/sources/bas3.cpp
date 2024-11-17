//axes - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

const Bas3 Bas3::Bo(Vtr3::Vo,Vtr3::Vo,Vtr3::Vo);
const Bas3 Bas3::Bxyz(Vtr3::Vx,Vtr3::Vy,Vtr3::Vz);

//
Bas3::Bas3(const arr::darr2 &D)
{
	if((D.size(0)==3)&&(D.size(1)==3))
	{
		for(size_t i=0;i<3;++i)
			for(size_t j=0;j<3;++j)
				_p[i](j)=D(i,j);
	}
	else
		arr::err=-1;
}

//
Bas3::operator arr::darr2() const
{
	arr::darr2 A=arr::darr2::ident(3,3);
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			A(i,j)=_p[i](j);
	return A;
}

//
Idx3 Bas3::dot(const Vtr3 &V) const
{
	return Idx3(_p[0].dot(V),_p[1].dot(V),_p[2].dot(V));
}

//
Vtr3 Bas3::operator*(const Idx3 &I) const
{
	Vtr3 V=Vtr::Vo;
	for(size_t i=0;i<3;i++)
		V+=I(i)*_p[i];
	return V;
}

//
Bas3 Bas3::recip() const
{
	double v=vol();
	Vtr V[3];
	for(size_t i=0;i<3;++i)
		V[i]=_p[mth::cyc(i+1,3)].cross(_p[mth::cyc(i+2,3)])/v;
	return Bas3(V);
}
	
//
double Bas3::vol() const
{
	return a().dot(b().cross(c()));
}

//
std::ostream& operator<<(std::ostream &os,const Bas3 &A)
{
	os<<A.a()<<std::endl;
	os<<A.b()<<std::endl;
	os<<A.c()<<std::endl;
	return os;
}

//
Trf3 Bas3::dot(const Bas3 &B) const
{
	Trf3 T;
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
			T(i,j)=_p[i].dot(B._p[j]);
	return T;
}

// returns (*this)*B.inv()
Trf3 Bas3::to(const Bas3 &B) const
{
	Bas3 Br=B.recip();
	Trf3 T;
	for(size_t i=0;i<3;++i)
		for(size_t j=0;j<3;++j)
		{
			double x(0.);
			for(size_t k=0;k<3;++k)
				x+=_p[k](i)*Br._p[k](j);
			T(i,j)=x;
		}
	return T;
}

//
Bas3 Bas3::operator/(const Trf3 &T) const
{
	return T.inv()*(*this);
}

//
Bas3 Bas3::operator*=(const Trf3 &T)
{
	return *this=T*(*this);
}

//
Bas3 Bas3::operator/=(const Trf3 &T)
{
	return *this=(*this)/T;
}

//
Bas3 operator*(double x,const Bas3 &A)
{
	return Bas3(x*A(0),x*A(1),x*A(2));
}

//
Bas3 recip(Bas3 A)
{
	return A.recip();
}

//
double vol(const Bas3 &A)
{
	return A.vol();
}

/*
//
Bas3 operator*(const Trf3 &T,const Bas3 &B)
{
	return Bas3(T*(B.a()),T*(B.b()),T*(B.c()));
}
*/
