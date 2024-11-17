//2-D coordinates - P. Ahrenkiel

#ifndef _CRD2_
#define _CRD2_

#include "arr.hpp"

class Crd2
{
protected:
	union
	{
		struct
		{
			double _x,_y;
		};
		double _p[2]; // array representation
	};

	Crd2 operator+(){return *this;}
	Crd2 operator-(){return Crd2(-_x,-_y);}

	Crd2 const operator+() const{return *this;}
	Crd2 const operator-() const{return Crd2(-_x,-_y);}
	
	Crd2 operator+(const Crd2 &c) const{return Crd2(_x+c._x,_y+c._y);}
	Crd2 operator-(const Crd2 &c) const{return Crd2(_x-c._x,_y-c._y);}
	
	Crd2 operator+=(const Crd2 &c){return *this=(*this)+c;}
	Crd2 operator-=(const Crd2 &c){return *this=(*this)-c;}
	Crd2 operator*=(double x){return *this=x*(*this);}
	Crd2 operator/=(double x){return *this=(*this)/x;}
	bool operator==(const Crd2 &c) const{return (_x==c._x)&&(_y==c._y);}
	bool operator!=(const Crd2 &c) const{return !((*this)==c);}

	friend Crd2 operator*(double x,const Crd2 &c){return Crd2(x*c._x,x*c._y);}
	Crd2 operator/(double x) const{return Crd2(_x/x,_y/x);}

	double sqrlen() const{return _x*_x+_y*_y;}
	double len() const{return sqrt(sqrlen());}

public:
	constexpr Crd2(double x=0.,double y=0.):_x(x),_y(y){}
	constexpr Crd2(const double x[2]):_x(x[0]),_y(x[1]){}
	Crd2(const arr::darr1 &A);
	
	operator arr::darr1() const;
	double& x(){return _x;}
	double& y(){return _y;}
	
	double const& x() const{return _x;}
	double const& y() const{return _y;}
	
	double& operator()(const size_t i0);
	double const& operator()(const size_t i0) const;
	
};

#endif
