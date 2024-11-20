//augmented transformations - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss2.hpp"

using namespace std;

const atr2 atr2::Ato=atr2();

atr2::operator arr::darr2() const
{
	arr::darr2 A=arr::darr2::ident(3,3);
	A.sub(0,0,2,2)=arr::darr2(_t);
	A.sub(0,2,2,1)=arr::darr1(_v);
	return A;
}

//
vtr2 atr2::operator*(const vtr2 &V) const
{
	return _t*V;
}

//
pnt2 atr2::operator*(const pnt2 &P) const
{
	return _t*P+_v;
}

//
atr2 atr2::operator*(const atr2 &T) const
{
	return atr2(_t*T._t,_t*T._v+_v);
}

//
atr2 atr2::inv() const
{
	trf2 iT=_t.inv();
	return atr2(iT,iT*(-_v));
}

//resolve predef
vtr2 vtr2::operator*=(const atr2 &T)
{
	return *this=T*(*this);
}

//resolve predef
pnt2 pnt2::operator*=(const atr2 &T)
{
	return *this=T*(*this);
}

//static
atr2 atr2::ident()
{
	return atr2();
}
