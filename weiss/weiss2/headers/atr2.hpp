//2-D augmented transformations - P. Ahrenkiel

#ifndef _ATR2_
#define _ATR2_

#ifndef _TLBX_
#include "tlbx.hpp"
#endif

#include "arr.hpp"

#ifndef _VTR2_
#include "Vtr2.hpp"
#endif

#ifndef _TRF2_
#include "Trf2.hpp"
#endif

//
class Atr2
{
protected:
	Trf2 _t;
	Vtr2 _v;
	
public:
	Atr2(const Trf2 &T=Trf2::To,const Vtr2 &V=Vtr2::Vo){_t=T;_v=V;}

	Vtr2 operator*(const Vtr2 &V) const;
	Pnt2 operator*(const Pnt2 &P) const;

	Atr2 operator*(const Atr2 &T) const;
	Atr2 operator/(const Atr2 &T) const;
	Atr2 operator*=(const Atr2 &T){return *this=T*(*this);}
	Atr2 operator/=(const Atr2 &T){return *this=*this/T;}

	operator arr::darr2() const;

	Trf2 &A(){return _t;}
	Vtr2 &b(){return _v;}
	Trf2 const &A() const{return _t;}
	Vtr2 const &b() const{return _v;}

	Atr2 inv() const;
	static Atr2 ident();

	static const Atr2 Ato;
};

#endif

