//graphics points - P. Ahrenkiel

#ifndef _GPNT_
#define _GPNT_

#include "CoreGraphics/CoreGraphics.h"

#include "arr.hpp"
#include "weiss.hpp"

class Gfrm;
class gcmr;

class gpnt:public pnt2
{
public:
	gpnt(double x=0.,double y=0.):pnt2(x,y){}
	gpnt(const darr1 &A):pnt2(A){}
	gpnt(const Crd2 &C):pnt2(C){}

	//bool operator==(const gpnt &p) const{return (_x==p._x)&&(_y==p._y);}
	//bool operator!=(const gpnt &p) const{return !((*this)==p);}
	
	//gpnt operator+() const{return *this;}
	//gpnt operator-() const{pnt2 P(*this);return -P;}

	bool clip(const Gfrm &fClip,const gpnt &pOther,gpnt &pDest) const;
	gpnt map(const Gfrm &fNew,const Gfrm &fOld) const;
	CGPoint map(const CGRect &Rframe,const Gfrm &frameF) const;
	CGPoint mapFrac(const CGRect &Rframe,const Gfrm &frameF) const;
	
	void doMoveTo(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const;
	void doLineTo(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const;

	static void moveTo(CGContextRef context,const CGPoint &P);
	static void lineTo(CGContextRef context,const CGPoint &P);

	friend std::ostream& operator<<(std::ostream &os,const gpnt &p);
	gpnt proj(const gcmr &cmr,const double z) const;
	gpnt invproj(const gcmr &cmr,const double z) const;
};

std::ostream& operator<<(std::ostream &os,const CGPoint &p);

typedef arr1<gpnt> Gpnt_arr1;
extern const Gpnt_arr1 nullP_arr;

#endif
