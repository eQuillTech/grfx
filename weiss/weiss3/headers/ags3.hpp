//axes - P. Ahrenkiel

#ifndef _AGS_
#define _AGS_

#include "tlbx.hpp"
#include "arr.hpp"

#ifndef _VTR3_
#include "vtr3.hpp"
#endif

#ifndef _BAS3_
#include "bas3.hpp"
#endif

class pnt3;
class idx3;
class trf3;
class atr3;

//Axs3
class ags3
{
protected:
	bas3 _b;
	pnt3 _p;//translation

public:
	ags3():_b(bas3::Bo),_p(pnt3::Po){}
	ags3(const bas3 &b,const pnt3 &p):_b(b),_p(p){}
	
	bas3 &B(){return _b;}
	bas3 const &B() const{return _b;}

	pnt3 &p(){return _p;}
	pnt3 const &p() const{return _p;}

	ags3 &A(){return *this;}
	const ags3 &A() const{return *this;}

	operator arr::darr2() const;

	idx3 dot(const pnt3 &P) const;
	idx3 operator*(const pnt3 &P) const{return dot(P);}
	pnt3 operator*(const idx3 &I) const;
	ags3 operator/(const trf3 &T) const;
	ags3 operator*=(const atr3 &T);
	ags3 operator/=(const atr3 &T);
	
	atr3 to(const ags3 &A) const;
	atr3 operator/(const ags3 &A) const{return to(A);}

	idx3 operator()(const pnt3 &P) const;
	friend std::ostream& operator<<(std::ostream &os,const ags3 &A);

	ags3 recip() const;
	   
	bool isIn(const pnt3 &P) const;
	operator simd::float4x4();

	static const ags3 Ao;
};

ags3 operator*(double x,const ags3 &A);
	
ags3 recip(ags3 A);

#endif
