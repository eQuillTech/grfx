//2-D points - P. Ahrenkiel

#ifndef _PNT2_
#define _PNT2_

#ifndef _ARR_
#include "arr.hpp"
#endif

#ifndef _CRD2_
#include "crd2.hpp"
#endif

class vtr2;
class trf2;
class atr2;

//
class pnt2:public crd2
{
public:
	constexpr pnt2():crd2(){}
	constexpr pnt2(double x,double y):crd2(x,y){}
	pnt2(const double x[2]):crd2(x){}
	pnt2(const crd2 &C):crd2(C){}
	pnt2(const arr::darr1 &A):crd2(A){}

	pnt2 operator+(const vtr2 &V) const;
	pnt2 operator-(const vtr2 &V) const;
	pnt2 operator+=(const vtr2 &V);
	pnt2 operator-=(const vtr2 &V);

	vtr2 operator-(const pnt2 &P) const;
	
	bool operator==(const pnt2 &P) const;
	bool operator!=(const pnt2 &P) const;

	inline double sqrdist() const{return sqrlen();}
	inline double dist() const{return len();}

	pnt2 operator*=(const trf2 &T);
	pnt2 operator*=(const atr2 &T);

	pnt2 neg(){return crd2::operator-(*this);}
	static const pnt2 Po;
};

//
inline double sqrdist(const pnt2 &p){return p.sqrdist();}
inline double dist(const pnt2 &p){return p.dist();}
 
typedef std::vector<pnt2> Pnt2Vector;

#endif
