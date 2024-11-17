//3-D points - P. Ahrenkiel

#ifndef _PNT3_
#define _PNT3_

#include <simd/simd.h>

#include "arr.hpp"

#ifndef _CRD3_
#include "Crd3.hpp"
#endif

class Vtr3;
class Trf3;
class Atr3;

//
class Pnt3:public Crd3
{
private:

public:
	explicit Pnt3(const Crd3 &C):Crd3(C){}
	constexpr Pnt3():Crd3(){}
	constexpr Pnt3(double x,double y,double z):Crd3(x,y,z){}
	Pnt3(const arr::darr1 &A):Crd3(A){}

	Pnt3 operator+(const Vtr3 &V) const;
	Pnt3 operator-(const Vtr3 &V) const;
	Pnt3 operator+=(const Vtr3 &V);
	Pnt3 operator-=(const Vtr3 &V);

	Vtr3 operator-(const Pnt3 &P) const;
	
	bool operator==(const Pnt3 &P) const;
	bool operator!=(const Pnt3 &P) const;

	Pnt3 operator*(const Atr3 &T) const;
	Pnt3 operator*=(const Atr3 &T);

	Pnt3 operator/(const Atr3 &T) const;
	Pnt3 operator/=(const Atr3 &T);

	double dist() const;

	double& x(){return _x;}
	double& y(){return _y;}
	double& z(){return _z;}
	
	double const& x() const{return _x;}
	double const& y() const{return _y;}
	double const& z() const{return _z;}

	static const Pnt3 Po;
	operator simd::float4();
	operator simd::float3();
};

//
inline double dist(const Pnt3 &p){return p.dist();}
 
typedef std::vector<Pnt3> Pnt3Vector;

#endif
