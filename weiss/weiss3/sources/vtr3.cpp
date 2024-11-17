//3-D vectors - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

constexpr const Vtr3 Vtr3::Vo(0.,0.,0.);
constexpr const Vtr3 Vtr3::Vx(1.,0.,0.);
constexpr const Vtr3 Vtr3::Vy(0.,1.,0.);
constexpr const Vtr3 Vtr3::Vz(0.,0.,1.);
const VtrDir VtrDir::Dir0(Vtr3::Vz,Vtr3::Vx,0.,0.,0.);

//
Vtr3::Vtr3(const VtrDir &dir)
{
	*this=Rtn(dir)*dir._axisZ;
}

//
Vtr3 Vtr3::cross(const Vtr3 &V) const
{
	Vtr3 Vt;
	for(size_t i=0;i<3;++i)
		Vt._p[i]=_p[mth::cyc(i+1,3)]*V._p[mth::cyc(i+2,3)]
			-_p[mth::cyc(i+2,3)]*V._p[mth::cyc(i+1,3)];
	return Vt;
}

//
bool Vtr3::operator==(const Vtr3 &V) const
{
	return (_x==V._x)&&(_y==V._y)&&(_z==V._z);
}

//
bool Vtr3::operator!=(const Vtr3 &V) const
{
	return !((*this)==V);
}

//
std::ostream& operator<<(std::ostream &os,const Vtr3 &V)
{
	os<<"("<<V.x()<<","<<V.y()<<","<<V.z()<<")";
	return os;
}

//
Vtr3::operator simd::float3()
{
	simd::float3 res={(float)_x,(float)_y,(float)_z};
	return res;
}

//
Vtr3 Vtr3::operator/(const Trf3 &T)
{
	return T.inv()*(*this);
}
