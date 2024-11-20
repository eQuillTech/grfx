//indices - P. Ahrenkiel

#ifndef _IDX3_
#define _IDX3_

#include "arr.hpp"

//predef(s)
class vtr3;
class Axs3;

//indx
class idx3:public crd3
{
private:
	explicit idx3(const crd3 &C):crd3(C){}

public:
	double& h(){return _x;}
	double& k(){return _y;}
	double& l(){return _z;}
	
	double const& h() const{return _x;}
	double const& k() const{return _y;}
	double const& l() const{return _z;}
	
	idx3():crd3(){}
	idx3(const double h,const double k,const double l):crd3(h,k,l){}
	idx3(const arr::darr1 &D):crd3(D){}

	idx3 round() const;
	idx3 operator+(const idx3 &I) const{return idx3(crd3::operator+(I));}
	idx3 operator-(const idx3 &I) const{return idx3(crd3::operator-(I));}
	idx3 operator+=(const idx3 &I){return *this=*this+I;}
	idx3 operator-=(const idx3 &I) {return *this=*this-I;}

	static const idx3 I000;
	static const idx3 I100;
	static const idx3 I010;
	static const idx3 I001;
	static const idx3 I111;

	//
	//Axs3 operator*(const vtr3 &V) const;

//	fl_err read(tfl &T);
	friend std::ostream& operator<<(std::ostream &os,const idx3 &I);
};

idx3 round(const idx3 &I3);


#endif
