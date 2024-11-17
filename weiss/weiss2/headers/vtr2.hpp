//2-D vectors - P. Ahrenkiel

#ifndef _VTR2_
#define _VTR2_

#ifndef _ARR_
#include "arr.hpp"
#endif

class Pnt2;
class Trf2;
class Atr2;

//
class Vtr2:public Crd2
{
public:
	constexpr Vtr2():Crd2(){}
	constexpr Vtr2(double x,double y):Crd2(x,y){}
	Vtr2(const double x[2]):Crd2(x){}
	Vtr2(const arr::darr1 &A):Crd2(A){}
	Vtr2(const Vtr2 &V):Crd2(V){}
	
	Vtr2 operator+() const{return *this;}
	Vtr2 operator-() const{return Vtr2(-_x,-_y);}
	
	Vtr2 operator+(const Vtr2 &V) const{return Vtr2(_x+V.x(),_y+V.y());}
	Vtr2 operator-(const Vtr2 &V) const{return Vtr2(_x-V.x(),_y-V.y());}

	Vtr2 operator+=(const Vtr2 &V){return *this=(*this)+V;}
	Vtr2 operator-=(const Vtr2 &V){return *this=(*this)-V;}
	Vtr2 operator*=(double x){return *this=x*(*this);}
	Vtr2 operator/=(double x){return *this=(*this)/x;}

	bool operator==(const Vtr2 &V) const{return Crd2::operator==(V);}
	bool operator!=(const Vtr2 &V) const{return !((*this)==V);}

	double dot(const Vtr2 &V) const{return _x*V._x+_y*V._y;}
	double cross(const Vtr2 &V) const;

	double operator*(const Vtr2 &v) const{return dot(v);}
	Vtr2 operator/(double x) const{return arr::darr1(*this)/x;}

	inline double sqrlen() const{return Crd2::sqrlen();}
	inline double len() const{return Crd2::len();}
	Vtr2 norm() const{return (*this)/len();}

	friend std::ostream& operator<<(std::ostream &os,const Vtr2 &V);
	friend Vtr2 operator*(double x,const Vtr2 &v){return Vtr2(x*v._x,x*v._y);}

//predef
	Vtr2 operator*=(const Trf2 &T);
	Vtr2 operator*=(const Atr2 &T);

	static const Vtr2 Vo,Vx,Vy;
};
 
inline double dot(const Vtr2 &V1,const Vtr2 &V2){return V1.dot(V2);}
inline double cross(const Vtr2 &V1,const Vtr2 &V2){return V1.cross(V2);}
inline double len(const Vtr2 &V){return V.len();}
inline Vtr2 norm(const Vtr2 &V){return V.norm();}

typedef arr::arr1<Vtr2> Vtr2_arr1;

#endif
