//graphics vectors - P. Ahrenkiel

#ifndef _GVTR_
#define _GVTR_

#include "CoreGraphics/CoreGraphics.h"

#ifndef _ARR_
#include "arr.h"
#endif

#ifndef _GCRD_
#include "gcrd.h"
#endif

class gfrm;

//
class gvtr:public gcrd
{

public:
	gvtr(double x=0.,double y=0.):gcrd(x,y){}
	gvtr(const dbl1 &A):gcrd(A){}
	gvtr(const gcrd &c):gcrd(c){}
	//gvtr(const gpnt &p){*this=p-origP;}
	
	gvtr operator+() const{return *this;}
	gvtr operator-() const{return -gcrd(*this);}
	
	gvtr operator+(const gvtr &v) const{return gvtr(m_x+v.m_x,m_y+v.m_y);}
	gvtr operator-(const gvtr &v) const{return gvtr(m_x-v.m_x,m_y-v.m_y);}
	gvtr operator=(const gvtr &v){m_x=v.m_x;m_y=v.m_y;return *this;}
	
	gvtr operator+=(const gvtr &v){return *this=(*this)+v;}
	gvtr operator-=(const gvtr &v){return *this=(*this)-v;}
	gvtr operator*=(double x){return *this=x*(*this);}
	gvtr operator/=(double x){return *this=(*this)/x;}
	bool operator==(const gvtr &v) const{return (m_x==v.m_x)&&(m_y==v.m_y);}
	bool operator!=(const gvtr &v) const{return !((*this)==v);}

	double operator*(const gvtr &v) const{return m_x*v.m_x+m_y*v.m_y;}
	gvtr operator/(double x) const{return gvtr(m_x/x,m_y/x);}

	double dot(const gvtr &v) const{return (*this)*v;}
	double sqrlen() const{return gcrd::sqrlen();}//double xp=x(), yp=y();return xp*xp+yp*yp;}
	double len() const{return gcrd::len();}
	gvtr norm() const{return dbl1(*this).norm();}

	friend gvtr operator*(double x,const gvtr &v){return gvtr(x*v.m_x,x*v.m_y);}
	friend std::ostream& operator<<(std::ostream &os,const gvtr &V);

};

double dot(const gvtr &V1,const gvtr &V2);
double len(const gvtr &V);
gvtr norm(const gvtr &V);

extern gvtr zeroV,xV,yV;

typedef arr1<gvtr> gvtr_arr1;

#endif
