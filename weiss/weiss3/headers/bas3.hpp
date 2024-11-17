//axes - P. Ahrenkiel

#ifndef _AXS_
#define _AXS_

#include "tlbx.hpp"
#include "arr.hpp"

class Pnt3;
class Vtr3;
class Idx3;
class Trf3;
class Atr3;

//Bas3
class Bas3
{
protected:
	Vtr3 _p[3];
	
public:
	Bas3(const Vtr3 &a=Vtr3::Vo,const Vtr3 &b=Vtr3::Vo,const Vtr3 &c=Vtr3::Vo){_p[0]=a;_p[1]=b;_p[2]=c;}
	Bas3(const Vtr3 V[]):Bas3(V[0],V[1],V[2]){}
	Bas3(const arr::darr2 &D);
	
	Vtr3& a(){return _p[0];}
	Vtr3& b(){return _p[1];}
	Vtr3& c(){return _p[2];}
		
	Vtr3 const& a() const{return _p[0];}
	Vtr3 const& b() const{return _p[1];}
	Vtr3 const& c() const{return _p[2];}
	
	Bas3 &B(){return *this;}
	const Bas3 &B() const{return *this;}
	
	Vtr3& operator()(const size_t i){return _p[i];}
	Vtr3 const& operator()(const size_t i) const{return _p[i];}

	Bas3 operator+() const{return *this;}
	Bas3 operator-() const{return Bas3(-_p[0],-_p[1],-_p[2]);}

	operator arr::darr2() const;

	Idx3 dot(const Vtr3 &V) const;
	Idx3 operator*(const Vtr3 &V) const{return dot(V);}
	Vtr3 operator*(const Idx3 &I) const;
	Bas3 operator/(const Trf3 &T) const;
	Bas3 operator*=(const Trf3 &T);
	Bas3 operator/=(const Trf3 &T);

	Trf3 dot(const Bas3 &B) const;
	Trf3 to(const Bas3 &B) const;
	Trf3 operator*(const Bas3 &B) const{return dot(B);}
	Trf3 operator/(const Bas3 &B) const{return to(B);}

	friend std::ostream& operator<<(std::ostream &os,const Bas3 &A);

	Bas3 recip() const;
	double vol() const;
	
	static const Bas3 Bo;
	static const Bas3 Bxyz;
};

Bas3 operator*(double x,const Bas3 &A);
	
Bas3 recip(Bas3 A);
double vol(const Bas3 &A);

//Bas3 operator*(const Trf3 &T,const Bas3 &B);


#endif
