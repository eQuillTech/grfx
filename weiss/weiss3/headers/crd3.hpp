//3-D coordinates - P. Ahrenkiel

#ifndef _CRD3_
#define _CRD3_

#include "arr.hpp"

class Crd3
{
protected:
	union
	{
		struct
		{
			double _x,_y,_z;
		};
		double _p[3]; // array representation
	};

	Crd3 operator+() const{return *this;}
	Crd3 operator-() const{return Crd3(-_x,-_y,-_z);}
	
	Crd3 operator+(const Crd3 &c) const{return Crd3(_x+c._x,_y+c._y,_z+c._z);}
	Crd3 operator-(const Crd3 &c) const{return Crd3(_x-c._x,_y-c._y,_z-c._z);}
	
	Crd3 operator+=(const Crd3 &c){return *this=(*this)+c;}
	Crd3 operator-=(const Crd3 &c){return *this=(*this)-c;}
	Crd3 operator*=(double x){return *this=x*(*this);}
	Crd3 operator/=(double x){return *this=(*this)/x;}
	bool operator==(const Crd3 &c) const{return (_x==c._x)&&(_y==c._y)&&(_z==c._z);}
	bool operator!=(const Crd3 &c) const{return !((*this)==c);}

	friend Crd3 operator*(double x,const Crd3 &c){return Crd3(x*c._x,x*c._y,x*c._z);}
	Crd3 operator/(double x) const{return Crd3(_x/x,_y/x,_z/x);}

	double sqrlen() const{return _x*_x+_y*_y+_z*_z;}
	double len() const{return sqrt(sqrlen());}

	double& x(){return _x;}
	double& y(){return _y;}
	double& z(){return _z;}
	
	double const& x() const{return _x;}
	double const& y() const{return _y;}
	double const& z() const{return _z;}

public:
	constexpr Crd3(double x=0.,double y=0.,double z=0.):_x(x),_y(y),_z(z){}
	constexpr Crd3(const double x[3]):_x(x[0]),_y(x[1]),_z(x[2]){}
	Crd3(const arr::darr1 &A);
	
	operator arr::darr1() const;
	
	double& operator()(const size_t i0);
	double const& operator()(const size_t i0) const;
	friend std::ostream& operator<<(std::ostream &os,const Crd3 &C);
};

#endif
