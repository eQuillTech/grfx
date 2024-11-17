//points - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "weiss2.hpp"

using namespace std;

constexpr const Pnt2 Pnt2::Po(0.,0.);

//
Pnt2 Pnt2::operator+=(const Vtr2 &V)
{
	return *this=(*this)+V;
}

//
Pnt2 Pnt2::operator-=(const Vtr2 &V)
{
	return *this=(*this)-V;
}

//
Pnt2 Pnt2::operator+(const Vtr2 &V) const
{
	return 	Pnt2(_x+V.x(),_y+V.y());
}

//
Pnt2 Pnt2::operator-(const Vtr2 &V) const
{
	return Pnt2(_x-V.x(),_y-V.y());
}

//
Vtr2 Pnt2::operator-(const Pnt2 &P) const
{
	return Vtr2(_x-P._x,_y-P._y);
}

//
bool Pnt2::operator==(const Pnt2 &P) const
{
	return (_x==P._x)&&(_y==P._y);
}

//
bool Pnt2::operator!=(const Pnt2 &P) const
{
	return !((*this)==P);
}

	
