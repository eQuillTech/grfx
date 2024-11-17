//axes - P. Ahrenkiel

#ifndef _AGS_
#define _AGS_

#include "tlbx.hpp"
#include "arr.hpp"

#ifndef _VTR3_
#include "Vtr3.hpp"
#endif

#ifndef _BAS3_
#include "Bas3.hpp"
#endif

class Pnt3;
class Idx3;
class Trf3;
class Atr3;

//Axs3
class Ags3
{
protected:
	Bas3 _b;
	Pnt3 _p;//translation

public:
	Ags3():_b(Bas3::Bo),_p(Pnt3::Po){}
	Ags3(const Bas3 &b,const Pnt3 &p):_b(b),_p(p){}
	
	Bas3 &B(){return _b;}
	Bas3 const &B() const{return _b;}

	Pnt3 &p(){return _p;}
	Pnt3 const &p() const{return _p;}

	Ags3 &A(){return *this;}
	const Ags3 &A() const{return *this;}

	operator arr::darr2() const;

	Idx3 dot(const Pnt3 &P) const;
	Idx3 operator*(const Pnt3 &P) const{return dot(P);}
	Pnt3 operator*(const Idx3 &I) const;
	Ags3 operator/(const Trf3 &T) const;
	Ags3 operator*=(const Atr3 &T);
	Ags3 operator/=(const Atr3 &T);
	
	Atr3 to(const Ags3 &A) const;
	Atr3 operator/(const Ags3 &A) const{return to(A);}

	Idx3 operator()(const Pnt3 &P) const;
	friend std::ostream& operator<<(std::ostream &os,const Ags3 &A);

	Ags3 recip() const;
	   
	bool isIn(const Pnt3 &P) const;
	operator simd::float4x4();

	static const Ags3 Ao;
};

Ags3 operator*(double x,const Ags3 &A);
	
Ags3 recip(Ags3 A);

#endif
