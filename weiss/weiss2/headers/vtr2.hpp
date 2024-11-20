//2-D vectors - P. Ahrenkiel

#ifndef _VTR2_
#define _VTR2_

#ifndef _ARR_
#include "arr.hpp"
#endif

class pnt2;
class trf2;
class atr2;

//
class vtr2:public crd2
{
public:
	constexpr vtr2():crd2(){}
	constexpr vtr2(double x,double y):crd2(x,y){}
	vtr2(const double x[2]):crd2(x){}
	vtr2(const arr::darr1 &A):crd2(A){}
	vtr2(const vtr2 &V):crd2(V){}
	
	vtr2 operator+() const{return *this;}
	vtr2 operator-() const{return vtr2(-_x,-_y);}
	
	vtr2 operator+(const vtr2 &V) const{return vtr2(_x+V.x(),_y+V.y());}
	vtr2 operator-(const vtr2 &V) const{return vtr2(_x-V.x(),_y-V.y());}

	vtr2 operator+=(const vtr2 &V){return *this=(*this)+V;}
	vtr2 operator-=(const vtr2 &V){return *this=(*this)-V;}
	vtr2 operator*=(double x){return *this=x*(*this);}
	vtr2 operator/=(double x){return *this=(*this)/x;}

	bool operator==(const vtr2 &V) const{return crd2::operator==(V);}
	bool operator!=(const vtr2 &V) const{return !((*this)==V);}

	double dot(const vtr2 &V) const{return _x*V._x+_y*V._y;}
	double cross(const vtr2 &V) const;

	double operator*(const vtr2 &v) const{return dot(v);}
	vtr2 operator/(double x) const{return arr::darr1(*this)/x;}

	inline double sqrlen() const{return crd2::sqrlen();}
	inline double len() const{return crd2::len();}
	vtr2 norm() const{return (*this)/len();}

	friend std::ostream& operator<<(std::ostream &os,const vtr2 &V);
	friend vtr2 operator*(double x,const vtr2 &v){return vtr2(x*v._x,x*v._y);}

//predef
	vtr2 operator*=(const trf2 &T);
	vtr2 operator*=(const atr2 &T);

	static const vtr2 Vo,Vx,Vy;
};
 
inline double dot(const vtr2 &V1,const vtr2 &V2){return V1.dot(V2);}
inline double cross(const vtr2 &V1,const vtr2 &V2){return V1.cross(V2);}
inline double len(const vtr2 &V){return V.len();}
inline vtr2 norm(const vtr2 &V){return V.norm();}

typedef arr::arr1<vtr2> Vtr2_arr1;

#endif
