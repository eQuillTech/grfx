//3-D transformations - P. Ahrenkiel

#ifndef _TRF3_
#define _TRF3_

#include <simd/simd.h>

#include "tlbx.hpp"
#include "arr.hpp"

class vtr3;
class bas3;
class rtn3;
class scl3;

//
class trf3
{
protected:
	double _p[3][3];
	
public:
	trf3();
	trf3(const arr::darr2 &D);
	trf3(const double p[3][3]);

//
	vtr3 operator*(const vtr3 &V) const noexcept;

	trf3 operator+(const trf3 &T) const;
	trf3 operator-(const trf3 &T) const{return -T+(*this);}
	trf3 operator*(const trf3 &T) const;
	trf3 operator/(const trf3 &T) const{return T.inv()*(*this);}
	trf3 operator+=(const trf3 &T){return *this=*this+T;}
	trf3 operator-=(const trf3 &T){return *this=*this-T;}
	trf3 operator*=(const trf3 &T){return *this=*this*T;}
	trf3 operator/=(const trf3 &T){return *this=*this/T;}

	trf3 operator+() const{return *this;}
	trf3 operator-() const;

	operator arr::darr2() const;
	bas3 operator*(const bas3 &B) const;

//
	double &operator()(const size_t i,const size_t j){return _p[i][j];}
	double const &operator()(const size_t i,const size_t j) const{return _p[i][j];}

	trf3 T() const{return *this;}
	trf3 inv() const;
	static trf3 ident();

	friend std::ostream& operator<<(std::ostream &os,const trf3 &T);
	friend trf3 operator*(double x,const trf3 &T);
	friend trf3 operator/(double x,const trf3 &T);

	static const trf3 To;
	
	operator simd::float3x3();
};

#endif

