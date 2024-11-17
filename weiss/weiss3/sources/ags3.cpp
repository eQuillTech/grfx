//axes - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

const Ags3 Ags3::Ao(Bas3::Bo,Pnt3::Po);

Ags3::operator arr::darr2() const
{
	arr::darr2 D=arr::darr2::ident(4,4);
	D.sub(0,0,3,3)=_b;
	D(0,3)=_p(0);
	D(1,3)=_p(1);
	D(2,3)=_p(2);
	return D;
}

//
Pnt3 Ags3::operator*(const Idx3 &I) const
{
	return _p+_b*I;
}

//
Idx3 Ags3::dot(const Pnt3 &P) const
{
	return _b*(P-_p);
}

//
Ags3 Ags3::recip() const
{
	Bas3 iB=_b.recip();
	Vtr3 V=_p-Pnt3::Po;
	Pnt3 iP=Pnt3::Po+Vtr3(iB.a().dot(V),iB.b().dot(V),iB.c().dot(V));
	return Ags3(iB,iP);
}

//
Idx3 Ags3::operator()(const Pnt3 &P) const
{
	return recip()*P;
}

//
std::ostream& operator<<(std::ostream &os,const Ags3 &A)
{
	os<<A.B()<<"\n"<<A.p()<<"\n";
	return os;
}

//
Atr3 Ags3::to(const Ags3 &A) const
{

	Trf3 T=_b.to(A._b);
	Vtr3 V=-T*(A._p-Pnt3::Po)+(_p-Pnt3::Po);
	return Atr3(T,V);
/*
	Trf3 T=_b.to(A._b);
	Idx3 K=-Bas3::Bxyz*(A._p-Pnt3::Po);
	Vtr3 V=A._b*K+(_p-Pnt3::Po);
	return Atr3(T,V);
	*/
}

//
Ags3 operator*(double x,const Ags3 &A)
{
	return Ags3(x*A.B(),Pnt3::Po+x*(A.p()-Pnt3::Po));
}

//
Ags3 recip(Ags3 A)
{
	return A.recip();
}

//
bool Ags3::isIn(const Pnt3 &P) const
{
	Idx3 I=dot(P);
	double inA=(I.h()>=0.)&&(I.h()<=1.);
	double inB=(I.k()>=0.)&&(I.k()<=1.);
	double inC=(I.l()>=0.)&&(I.l()<=1.);
	return inA&&inB&&inC;
}

//
Ags3 Ags3::operator*=(const Atr3 &T)
{
	return *this=T*(*this);
}

//
Ags3::operator simd::float4x4()
{
	using simd::float4;
	return simd_matrix_from_rows
	(
		(float4){	(float)_b(0).x(), (float)_b(1).x(), (float)_b(2).x(), (float)_p.x() },
		(float4){ (float)_b(0).y(), (float)_b(1).y(), (float)_b(2).y(), (float)_p.y() },
		(float4){ (float)_b(0).z(), (float)_b(1).z(), (float)_b(2).z(), (float)_p.z() },
		(float4){ 0.f, 0.f, 0.f, 1.f }
	);
}
