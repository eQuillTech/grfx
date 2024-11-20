//2-D augmented transformations - P. Ahrenkiel

#ifndef _ATR2_
#define _ATR2_

#ifndef _TLBX_
#include "tlbx.hpp"
#endif

#include "arr.hpp"

#ifndef _VTR2_
#include "vtr2.hpp"
#endif

#ifndef _TRF2_
#include "trf2.hpp"
#endif

//
class atr2
{
protected:
	trf2 _t;
	vtr2 _v;
	
public:
	atr2(const trf2 &T=trf2::To,const vtr2 &V=vtr2::Vo){_t=T;_v=V;}

	vtr2 operator*(const vtr2 &V) const;
	pnt2 operator*(const pnt2 &P) const;

	atr2 operator*(const atr2 &T) const;
	atr2 operator/(const atr2 &T) const;
	atr2 operator*=(const atr2 &T){return *this=T*(*this);}
	atr2 operator/=(const atr2 &T){return *this=*this/T;}

	operator arr::darr2() const;

	trf2 &A(){return _t;}
	vtr2 &b(){return _v;}
	trf2 const &A() const{return _t;}
	vtr2 const &b() const{return _v;}

	atr2 inv() const;
	static atr2 ident();

	static const atr2 Ato;
};

#endif

