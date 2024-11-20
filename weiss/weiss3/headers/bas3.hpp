//axes - P. Ahrenkiel

#ifndef _AXS_
#define _AXS_

#include "tlbx.hpp"
#include "arr.hpp"

class pnt3;
class vtr3;
class idx3;
class trf3;
class atr3;

//bas3
class bas3
{
protected:
	vtr3 _p[3];
	
public:
	bas3(const vtr3 &a=vtr3::Vo,const vtr3 &b=vtr3::Vo,const vtr3 &c=vtr3::Vo){_p[0]=a;_p[1]=b;_p[2]=c;}
	bas3(const vtr3 V[]):bas3(V[0],V[1],V[2]){}
	bas3(const arr::darr2 &D);
	
	vtr3& a(){return _p[0];}
	vtr3& b(){return _p[1];}
	vtr3& c(){return _p[2];}
		
	vtr3 const& a() const{return _p[0];}
	vtr3 const& b() const{return _p[1];}
	vtr3 const& c() const{return _p[2];}
	
	bas3 &B(){return *this;}
	const bas3 &B() const{return *this;}
	
	vtr3& operator()(const size_t i){return _p[i];}
	vtr3 const& operator()(const size_t i) const{return _p[i];}

	bas3 operator+() const{return *this;}
	bas3 operator-() const{return bas3(-_p[0],-_p[1],-_p[2]);}

	operator arr::darr2() const;

	idx3 dot(const vtr3 &V) const;
	idx3 operator*(const vtr3 &V) const{return dot(V);}
	vtr3 operator*(const idx3 &I) const;
	bas3 operator/(const trf3 &T) const;
	bas3 operator*=(const trf3 &T);
	bas3 operator/=(const trf3 &T);

	trf3 dot(const bas3 &B) const;
	trf3 to(const bas3 &B) const;
	trf3 operator*(const bas3 &B) const{return dot(B);}
	trf3 operator/(const bas3 &B) const{return to(B);}

	friend std::ostream& operator<<(std::ostream &os,const bas3 &A);

	bas3 recip() const;
	double vol() const;
	
	static const bas3 Bo;
	static const bas3 Bxyz;
};

bas3 operator*(double x,const bas3 &A);
	
bas3 recip(bas3 A);
double vol(const bas3 &A);

//bas3 operator*(const trf3 &T,const bas3 &B);


#endif
