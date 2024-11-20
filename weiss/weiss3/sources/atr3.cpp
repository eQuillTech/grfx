//3-D augmented transformations - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

using namespace std;

const atr3 atr3::Ato=atr3();

atr3::operator arr::darr2() const
{
	arr::darr2 A=arr::darr2::ident(4,4);
	A.sub(0,0,3,3)=arr::darr2(_t);
	A.sub(0,3,3,1)=arr::darr1(_v);
	return A;
}

//
atr3::atr3(const trf3 &T,const pnt3 &P):_t(T)
{
	_v=(trf3::ident()-T)*(P-pnt3::Po);
}

//
vtr3 atr3::operator*(const vtr3 &V) const noexcept
{
	return _t*V;
}

//
pnt3 atr3::operator*(const pnt3 &P) const noexcept
{
	return pnt3::Po+_t*(P-pnt3::Po)+_v;
}

//
atr3 atr3::operator*(const atr3 &T) const
{
	return atr3(_t*T._t,_t*T._v+_v);
}

//
atr3 atr3::inv() const
{
	trf3 iT=_t.inv();
	return atr3(iT,iT*(-_v));
}

//
ags3 atr3::operator*(const ags3 &A) const
{
	bas3 Bp=_t*A.B();
	pnt3 Pp=pnt3::Po+_t*(A.p()-pnt3::Po)+_v;
	return ags3(Bp,Pp);
}

//static
atr3 atr3::ident()
{
	return atr3();
}

//
atr3::operator simd::float4x4()
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
ostream& operator<<(ostream &os,const atr3 &T)
{
	os<<T.A()<<"\n"<<T.b()<<"\n";
	return os;
}
