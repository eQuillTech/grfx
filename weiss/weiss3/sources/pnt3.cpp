//3-D points - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

constexpr const pnt3 pnt3::Po(0.,0.,0.);

//
pnt3 pnt3::operator+=(const vtr3 &V)
{
	return *this=(*this)+V;
}

//
pnt3 pnt3::operator-=(const vtr3 &V)
{
	return *this=(*this)-V;
}

//
pnt3 pnt3::operator+(const vtr3 &V) const
{
	return 	pnt3(_x+V.x(),_y+V.y(),_z+V.z());
}

//
pnt3 pnt3::operator-(const vtr3 &V) const
{
	return pnt3(_x-V.x(),_y-V.y(),_z-V.z());
}

//
vtr3 pnt3::operator-(const pnt3 &P) const
{
	return vtr3(_x-P._x,_y-P._y,_z-P._z);
}

//
pnt3 pnt3::operator*(const atr3 &T) const
{
	return pnt3::Po+T.A()*(operator-(pnt3::Po))+T.b();
}

//
pnt3 pnt3::operator/(const atr3 &T) const
{
	return pnt3::Po+T.A().inv()*(operator-(pnt3::Po))+T.b();
}

//
bool pnt3::operator==(const pnt3 &P) const
{
	return (_x==P._x)&&(_y==P._y)&&(_z==P._z);
}

//
bool pnt3::operator!=(const pnt3 &P) const
{
	return !((*this)==P);
}

pnt3 pnt3::operator*=(const atr3 &T)
{
	return *this=T*(*this);
}

pnt3 pnt3::operator/=(const atr3 &T)
{
	return *this=T.inv()*(*this);
}

//
double pnt3::dist() const
{
	return len();
}
	
//
pnt3::operator simd::float4()
{
	simd::float4 res={(float)_x,(float)_y,(float)_z,1.f};
	return res;
}

//
pnt3::operator simd::float3()
{
	simd::float3 res={(float)_x,(float)_y,(float)_z};
	return res;
}
