//vectors - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss2.hpp"

using namespace std;

constexpr const vtr2 vtr2::Vo(0.,0.);
constexpr const vtr2 vtr2::Vx(1.,0.);
constexpr const vtr2 vtr2::Vy(0.,1.);

//
double vtr2::cross(const vtr2 &V) const
{
	return _x*V._y-_y*V._x;
}

//
ostream& operator<<(ostream &os,const vtr2 &V)
{
	os<<"("<<V.x()<<","<<V.y()<<")";
	return os;
}



