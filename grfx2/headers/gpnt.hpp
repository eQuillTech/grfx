//graphics points - P. Ahrenkiel

#ifndef _GPNT_
#define _GPNT_

#include "CoreGraphics/CoreGraphics.h"

#include "pnt2.hpp"

class gfrm;
class gcmr;

class gpnt:public pnt2
{
public:
	gpnt(double x=0.,double y=0.);
	gpnt(const arr::darr1 &A);

	bool clip(const gfrm  &fClip,const gpnt &pOther,gpnt &pDest) const;
	gpnt map(const gfrm  &fNew,const gfrm  &fOld) const;
	CGPoint map(const CGRect &Rframe,const gfrm &frameF) const;
	CGPoint mapFrac(const CGRect &Rframe,const gfrm &frameF) const;
	
	void doMoveTo(CGContextRef context,const CGRect &Rframe,const gfrm &frameF) const;
	void doLineTo(CGContextRef context,const CGRect &Rframe,const gfrm &frameF) const;

	static void moveTo(CGContextRef context,const CGPoint &P);
	static void lineTo(CGContextRef context,const CGPoint &P);

	friend std::ostream& operator<<(std::ostream &os,const gpnt &p);
	gpnt proj(const gcmr &cmr,const double z) const;
	gpnt invproj(const gcmr &cmr,const double z) const;
};

std::ostream& operator<<(std::ostream &os,const CGPoint &p);

typedef arr::arr1<gpnt> gpnt_arr1;
extern const gpnt_arr1 nullP_arr;

#endif
