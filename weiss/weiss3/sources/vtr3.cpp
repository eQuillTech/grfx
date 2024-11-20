//3-D vectors - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

constexpr const vtr3 vtr3::Vo(0.,0.,0.);
constexpr const vtr3 vtr3::Vx(1.,0.,0.);
constexpr const vtr3 vtr3::Vy(0.,1.,0.);
constexpr const vtr3 vtr3::Vz(0.,0.,1.);
const VtrDir VtrDir::Dir0(vtr3::Vz,vtr3::Vx,0.,0.,0.);

//
vtr3::vtr3(const VtrDir &dir)
{
	*this=rtn3(dir)*dir._axisZ;
}

//
vtr3 vtr3::cross(const vtr3 &V) const
{
	vtr3 Vt;
	for(size_t i=0;i<3;++i)
		Vt._p[i]=_p[mth::cyc(i+1,3)]*V._p[mth::cyc(i+2,3)]
			-_p[mth::cyc(i+2,3)]*V._p[mth::cyc(i+1,3)];
	return Vt;
}

//
bool vtr3::operator==(const vtr3 &V) const
{
	return (_x==V._x)&&(_y==V._y)&&(_z==V._z);
}

//
bool vtr3::operator!=(const vtr3 &V) const
{
	return !((*this)==V);
}

//
std::ostream& operator<<(std::ostream &os,const vtr3 &V)
{
	os<<"("<<V.x()<<","<<V.y()<<","<<V.z()<<")";
	return os;
}

//
vtr3::operator simd::float3()
{
	simd::float3 res={(float)_x,(float)_y,(float)_z};
	return res;
}

//
vtr3 vtr3::operator/(const trf3 &T)
{
	return T.inv()*(*this);
}
