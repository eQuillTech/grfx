//3-D augmented transformations - P. Ahrenkiel

#ifndef _ATR3_
#define _ATR3_

#include <simd/simd.h>

#include "tlbx.hpp"

#include "arr.hpp"

#ifndef _VTR3_
#include "Vtr3.hpp"
#endif

#ifndef _TRF3_
#include "Trf3.hpp"
#endif

class Ags3;

//
class Atr3
{
protected:
	Trf3 _t;
	Vtr3 _v;
	
public:
	explicit Atr3():_t(Trf3::To),_v(Vtr3::Vo){}
	explicit Atr3(const Trf3 &T,const Vtr3 &V):_t(T),_v(V){}
	explicit Atr3(const Trf3 &T):_t(T),_v(Vtr3::Vo){}
	explicit Atr3(const Vtr3 &V):_t(Trf3::To),_v(V){}
	explicit Atr3(const Trf3 &T,const Pnt3 &P);

	Vtr3 operator*(const Vtr3 &V) const noexcept;
	Pnt3 operator*(const Pnt3 &P) const noexcept;

	Atr3 operator*(const Atr3 &T) const;
	Atr3 operator/(const Atr3 &T) const;
	Atr3 operator*=(const Atr3 &T){return *this=T*(*this);}
	Atr3 operator/=(const Atr3 &T){return *this=*this/T;}

	operator arr::darr2() const;
	friend std::ostream& operator<<(std::ostream &os,const Atr3 &T);

	Trf3 &A(){return _t;}
	Vtr3 &b(){return _v;}
	Trf3 const &A() const{return _t;}
	Vtr3 const &b() const{return _v;}

	Ags3 operator*(const Ags3 &A) const;
	Atr3 inv() const;
	static Atr3 ident();

	static const Atr3 Ato;
	
	operator simd::float4x4();
	//simd::float4x4 perspective(const double yTop,const double xLeft,const double yBottom,const double xRight,const double zNear,const double zFar);

};

#endif

