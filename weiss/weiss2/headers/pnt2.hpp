//2-D points - P. Ahrenkiel

#ifndef _PNT2_
#define _PNT2_

#ifndef _ARR_
#include "arr.hpp"
#endif

#ifndef _CRD2_
#include "Crd2.hpp"
#endif

class Vtr2;
class Trf2;
class Atr2;

//
class Pnt2:public Crd2
{
public:
	constexpr Pnt2():Crd2(){}
	constexpr Pnt2(double x,double y):Crd2(x,y){}
	Pnt2(const double x[2]):Crd2(x){}
	Pnt2(const Crd2 &C):Crd2(C){}
	Pnt2(const arr::darr1 &A):Crd2(A){}

	Pnt2 operator+(const Vtr2 &V) const;
	Pnt2 operator-(const Vtr2 &V) const;
	Pnt2 operator+=(const Vtr2 &V);
	Pnt2 operator-=(const Vtr2 &V);

	Vtr2 operator-(const Pnt2 &P) const;
	
	bool operator==(const Pnt2 &P) const;
	bool operator!=(const Pnt2 &P) const;

	inline double sqrdist() const{return sqrlen();}
	inline double dist() const{return len();}

	Pnt2 operator*=(const Trf2 &T);
	Pnt2 operator*=(const Atr2 &T);

	Pnt2 neg(){return Crd2::operator-(*this);}
	static const Pnt2 Po;
};

//
inline double sqrdist(const Pnt2 &p){return p.sqrdist();}
inline double dist(const Pnt2 &p){return p.dist();}
 
typedef std::vector<Pnt2> Pnt2Vector;

#endif
