//graphics coordinates - P. Ahrenkiel

#ifndef _GCRD_
#define _GCRD_

#include "CoreGraphics/CoreGraphics.h"

#include "arr.hpp"

class gcrd
{
protected:
	double m_x,m_y;

public:
	gcrd(double x=0.,double y=0.):m_x(x),m_y(y){}
	gcrd(const darr1 &A);

	operator darr1() const;
	double& x(){return m_x;}
	double& y(){return m_y;}
	
	double const& x() const{return m_x;}
	double const& y() const{return m_y;}
	
	double& operator()(const size_t i0);
	double const& operator()(const size_t i0) const;

	gcrd operator+() const{return *this;}
	gcrd operator-() const{return gcrd(-m_x,-m_y);}

	//gcrd operator+(const gcrd &c) const{return darr1(*this)+darr1(c);}
	//gcrd operator-(const gcrd &c) const{return darr1(*this)-darr1(c);}
//	gcrd operator+=(const gcrd &c){return *this=(*this)+c;}
//	gcrd operator-=(const gcrd &c){return *this=(*this)-c;}

protected:
	double sqrlen() const{return m_x*m_x+m_y*m_y;}
	double len() const{return sqrt(sqrlen());}

};

#endif
