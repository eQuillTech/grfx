//axes - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

const ags3 ags3::Ao(bas3::Bo,pnt3::Po);

ags3::operator arr::darr2() const
{
	arr::darr2 D=arr::darr2::ident(4,4);
	D.sub(0,0,3,3)=_b;
	D(0,3)=_p(0);
	D(1,3)=_p(1);
	D(2,3)=_p(2);
	return D;
}

//
pnt3 ags3::operator*(const idx3 &I) const
{
	return _p+_b*I;
}

//
idx3 ags3::dot(const pnt3 &P) const
{
	return _b*(P-_p);
}

//
ags3 ags3::recip() const
{
	bas3 iB=_b.recip();
	vtr3 V=_p-pnt3::Po;
	pnt3 iP=pnt3::Po+vtr3(iB.a().dot(V),iB.b().dot(V),iB.c().dot(V));
	return ags3(iB,iP);
}

//
idx3 ags3::operator()(const pnt3 &P) const
{
	return recip()*P;
}

//
std::ostream& operator<<(std::ostream &os,const ags3 &A)
{
	os<<A.B()<<"\n"<<A.p()<<"\n";
	return os;
}

//
atr3 ags3::to(const ags3 &A) const
{

	trf3 T=_b.to(A._b);
	vtr3 V=-T*(A._p-pnt3::Po)+(_p-pnt3::Po);
	return atr3(T,V);
/*
	trf3 T=_b.to(A._b);
	idx3 K=-bas3::Bxyz*(A._p-pnt3::Po);
	vtr3 V=A._b*K+(_p-pnt3::Po);
	return atr3(T,V);
	*/
}

//
ags3 operator*(double x,const ags3 &A)
{
	return ags3(x*A.B(),pnt3::Po+x*(A.p()-pnt3::Po));
}

//
ags3 recip(ags3 A)
{
	return A.recip();
}

//
bool ags3::isIn(const pnt3 &P) const
{
	idx3 I=dot(P);
	double inA=(I.h()>=0.)&&(I.h()<=1.);
	double inB=(I.k()>=0.)&&(I.k()<=1.);
	double inC=(I.l()>=0.)&&(I.l()<=1.);
	return inA&&inB&&inC;
}

//
ags3 ags3::operator*=(const atr3 &T)
{
	return *this=T*(*this);
}

//
ags3::operator simd::float4x4()
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
