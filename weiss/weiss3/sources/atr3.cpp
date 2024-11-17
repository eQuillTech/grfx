//3-D augmented transformations - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

using namespace std;

const Atr3 Atr3::Ato=Atr3();

Atr3::operator arr::darr2() const
{
	arr::darr2 A=arr::darr2::ident(4,4);
	A.sub(0,0,3,3)=arr::darr2(_t);
	A.sub(0,3,3,1)=arr::darr1(_v);
	return A;
}

//
Atr3::Atr3(const Trf3 &T,const Pnt3 &P):_t(T)
{
	_v=(Trf3::ident()-T)*(P-Pnt3::Po);
}

//
Vtr3 Atr3::operator*(const Vtr3 &V) const noexcept
{
	return _t*V;
}

//
Pnt3 Atr3::operator*(const Pnt3 &P) const noexcept
{
	return Pnt3::Po+_t*(P-Pnt3::Po)+_v;
}

//
Atr3 Atr3::operator*(const Atr3 &T) const
{
	return Atr3(_t*T._t,_t*T._v+_v);
}

//
Atr3 Atr3::inv() const
{
	Trf3 iT=_t.inv();
	return Atr3(iT,iT*(-_v));
}

//
Ags3 Atr3::operator*(const Ags3 &A) const
{
	Bas3 Bp=_t*A.B();
	Pnt3 Pp=Pnt3::Po+_t*(A.p()-Pnt3::Po)+_v;
	return Ags3(Bp,Pp);
}

//static
Atr3 Atr3::ident()
{
	return Atr3();
}

//
Atr3::operator simd::float4x4()
{
	using simd::float4;
	return simd_matrix_from_rows
	(
		(float4){	(float)_t(0,0), (float)_t(0,1), (float)_t(0,2), (float)_v.x() },
		(float4){ (float)_t(1,0), (float)_t(1,1), (float)_t(1,2), (float)_v.y() },
		(float4){ (float)_t(2,0), (float)_t(2,1), (float)_t(2,2), (float)_v.z() },
		(float4){ 0.f, 0.f, 0.f, 1.f }
	);
}

//
ostream& operator<<(ostream &os,const Atr3 &T)
{
	os<<T.A()<<"\n"<<T.b()<<"\n";
	return os;
}
