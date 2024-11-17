//3-D transformations - P. Ahrenkiel

#ifndef _TRF3_
#define _TRF3_

#include <simd/simd.h>

#include "tlbx.hpp"
#include "arr.hpp"

class Vtr3;
class Bas3;
class Rtn3;
class Scl3;

//
class Trf3
{
protected:
	double _p[3][3];
	
public:
	Trf3();
	Trf3(const arr::darr2 &D);
	Trf3(const double p[3][3]);

//
	Vtr3 operator*(const Vtr3 &V) const noexcept;

	Trf3 operator+(const Trf3 &T) const;
	Trf3 operator-(const Trf3 &T) const{return -T+(*this);}
	Trf3 operator*(const Trf3 &T) const;
	Trf3 operator/(const Trf3 &T) const{return T.inv()*(*this);}
	Trf3 operator+=(const Trf3 &T){return *this=*this+T;}
	Trf3 operator-=(const Trf3 &T){return *this=*this-T;}
	Trf3 operator*=(const Trf3 &T){return *this=*this*T;}
	Trf3 operator/=(const Trf3 &T){return *this=*this/T;}

	Trf3 operator+() const{return *this;}
	Trf3 operator-() const;

	operator arr::darr2() const;
	Bas3 operator*(const Bas3 &B) const;

//
	double &operator()(const size_t i,const size_t j){return _p[i][j];}
	double const &operator()(const size_t i,const size_t j) const{return _p[i][j];}

	Trf3 T() const{return *this;}
	Trf3 inv() const;
	static Trf3 ident();

	friend std::ostream& operator<<(std::ostream &os,const Trf3 &T);
	friend Trf3 operator*(double x,const Trf3 &T);
	friend Trf3 operator/(double x,const Trf3 &T);

	static const Trf3 To;
	
	operator simd::float3x3();
};

#endif

