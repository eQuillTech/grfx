//points - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "weiss2.hpp"

using namespace std;

constexpr const pnt2 pnt2::Po(0.,0.);

//
pnt2 pnt2::operator+=(const vtr2 &V)
{
	return *this=(*this)+V;
}

//
pnt2 pnt2::operator-=(const vtr2 &V)
{
	return *this=(*this)-V;
}

//
pnt2 pnt2::operator+(const vtr2 &V) const
{
	return 	pnt2(_x+V.x(),_y+V.y());
}

//
pnt2 pnt2::operator-(const vtr2 &V) const
{
	return pnt2(_x-V.x(),_y-V.y());
}

//
vtr2 pnt2::operator-(const pnt2 &P) const
{
	return vtr2(_x-P._x,_y-P._y);
}

//
bool pnt2::operator==(const pnt2 &P) const
{
	return (_x==P._x)&&(_y==P._y);
}

//
bool pnt2::operator!=(const pnt2 &P) const
{
	return !((*this)==P);
}

	
