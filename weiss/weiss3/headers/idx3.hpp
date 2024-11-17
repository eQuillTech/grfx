//indices - P. Ahrenkiel

#ifndef _IDX3_
#define _IDX3_

#include "arr.hpp"

//predef(s)
class Vtr3;
class Axs3;

//indx
class Idx3:public Crd3
{
private:
	explicit Idx3(const Crd3 &C):Crd3(C){}

public:
	double& h(){return _x;}
	double& k(){return _y;}
	double& l(){return _z;}
	
	double const& h() const{return _x;}
	double const& k() const{return _y;}
	double const& l() const{return _z;}
	
	Idx3():Crd3(){}
	Idx3(const double h,const double k,const double l):Crd3(h,k,l){}
	Idx3(const arr::darr1 &D):Crd3(D){}

	Idx3 round() const;
	Idx3 operator+(const Idx3 &I) const{return Idx3(Crd3::operator+(I));}
	Idx3 operator-(const Idx3 &I) const{return Idx3(Crd3::operator-(I));}
	Idx3 operator+=(const Idx3 &I){return *this=*this+I;}
	Idx3 operator-=(const Idx3 &I) {return *this=*this-I;}

	static const Idx3 I000;
	static const Idx3 I100;
	static const Idx3 I010;
	static const Idx3 I001;
	static const Idx3 I111;

	//
	//Axs3 operator*(const Vtr3 &V) const;

//	fl_err read(tfl &T);
	friend std::ostream& operator<<(std::ostream &os,const Idx3 &I);
};

Idx3 round(const Idx3 &I3);


#endif
