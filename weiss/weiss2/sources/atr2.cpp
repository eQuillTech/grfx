//augmented transformations - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss2.hpp"

using namespace std;

const Atr2 Atr2::Ato=Atr2();

Atr2::operator arr::darr2() const
{
	arr::darr2 A=arr::darr2::ident(3,3);
	A.sub(0,0,2,2)=arr::darr2(_t);
	A.sub(0,2,2,1)=arr::darr1(_v);
	return A;
}

//
Vtr2 Atr2::operator*(const Vtr2 &V) const
{
	return _t*V;
}

//
Pnt2 Atr2::operator*(const Pnt2 &P) const
{
	return _t*P+_v;
}

//
Atr2 Atr2::operator*(const Atr2 &T) const
{
	return Atr2(_t*T._t,_t*T._v+_v);
}

//
Atr2 Atr2::inv() const
{
	Trf2 iT=_t.inv();
	return Atr2(iT,iT*(-_v));
}

//resolve predef
Vtr2 Vtr2::operator*=(const Atr2 &T)
{
	return *this=T*(*this);
}

//resolve predef
Pnt2 Pnt2::operator*=(const Atr2 &T)
{
	return *this=T*(*this);
}

//static
Atr2 Atr2::ident()
{
	return Atr2();
}
