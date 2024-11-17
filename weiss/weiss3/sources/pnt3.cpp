//3-D points - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

constexpr const Pnt3 Pnt3::Po(0.,0.,0.);

//
Pnt3 Pnt3::operator+=(const Vtr3 &V)
{
	return *this=(*this)+V;
}

//
Pnt3 Pnt3::operator-=(const Vtr3 &V)
{
	return *this=(*this)-V;
}

//
Pnt3 Pnt3::operator+(const Vtr3 &V) const
{
	return 	Pnt3(_x+V.x(),_y+V.y(),_z+V.z());
}

//
Pnt3 Pnt3::operator-(const Vtr3 &V) const
{
	return Pnt3(_x-V.x(),_y-V.y(),_z-V.z());
}

//
Vtr3 Pnt3::operator-(const Pnt3 &P) const
{
	return Vtr3(_x-P._x,_y-P._y,_z-P._z);
}

//
Pnt3 Pnt3::operator*(const Atr3 &T) const
{
	return Pnt3::Po+T.A()*(operator-(Pnt3::Po))+T.b();
}

//
Pnt3 Pnt3::operator/(const Atr3 &T) const
{
	return Pnt3::Po+T.A().inv()*(operator-(Pnt3::Po))+T.b();
}

//
bool Pnt3::operator==(const Pnt3 &P) const
{
	return (_x==P._x)&&(_y==P._y)&&(_z==P._z);
}

//
bool Pnt3::operator!=(const Pnt3 &P) const
{
	return !((*this)==P);
}

Pnt3 Pnt3::operator*=(const Atr3 &T)
{
	return *this=T*(*this);
}

Pnt3 Pnt3::operator/=(const Atr3 &T)
{
	return *this=T.inv()*(*this);
}

//
double Pnt3::dist() const
{
	return len();
}
	
//
Pnt3::operator simd::float4()
{
	simd::float4 res={(float)_x,(float)_y,(float)_z,1.f};
	return res;
}

//
Pnt3::operator simd::float3()
{
	simd::float3 res={(float)_x,(float)_y,(float)_z};
	return res;
}
