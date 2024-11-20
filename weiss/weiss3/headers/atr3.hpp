//3-D augmented transformations - P. Ahrenkiel

#ifndef _ATR3_
#define _ATR3_

#include <simd/simd.h>

#include "tlbx.hpp"

#include "arr.hpp"

#ifndef _VTR3_
#include "vtr3.hpp"
#endif

#ifndef _TRF3_
#include "trf3.hpp"
#endif

class ags3;

//
class atr3
{
protected:
	trf3 _t;
	vtr3 _v;
	
public:
	explicit atr3():_t(trf3::To),_v(vtr3::Vo){}
	explicit atr3(const trf3 &T,const vtr3 &V):_t(T),_v(V){}
	explicit atr3(const trf3 &T):_t(T),_v(vtr3::Vo){}
	explicit atr3(const vtr3 &V):_t(trf3::To),_v(V){}
	explicit atr3(const trf3 &T,const pnt3 &P);

	vtr3 operator*(const vtr3 &V) const noexcept;
	pnt3 operator*(const pnt3 &P) const noexcept;

	atr3 operator*(const atr3 &T) const;
	atr3 operator/(const atr3 &T) const;
	atr3 operator*=(const atr3 &T){return *this=T*(*this);}
	atr3 operator/=(const atr3 &T){return *this=*this/T;}

	operator arr::darr2() const;
	friend std::ostream& operator<<(std::ostream &os,const atr3 &T);

	trf3 &A(){return _t;}
	vtr3 &b(){return _v;}
	trf3 const &A() const{return _t;}
	vtr3 const &b() const{return _v;}

	ags3 operator*(const ags3 &A) const;
	atr3 inv() const;
	static atr3 ident();

	static const atr3 Ato;
	
	operator simd::float4x4();
	//simd::float4x4 perspective(const double yTop,const double xLeft,const double yBottom,const double xRight,const double zNear,const double zFar);

};

#endif

