//graphics rectangles - P. Ahrenkiel

#ifndef _GRCT_
#define _GRCT_

#include "CoreGraphics/CoreGraphics.h"

#include "gfrm.hpp"

class gpnt;

class grct:public gfrm
{
private:

public:
	grct();
	grct(const double t,const double l,const double b,const double r);
	grct(const gpnt tl,const gpnt br);
	grct(const gfrm & f);
	grct(CGRect R);
	grct operator=(const gfrm  &f);

	static void fill(CGContextRef context,const CGRect &Rdest);
	static void stroke(CGContextRef context,const CGRect &Rdest);

	//
	void doFill(CGContextRef context,const CGRect &Rdest) const override;
	void doStroke(CGContextRef context,const CGRect &Rdest) const override;
};

std::ostream& operator<<(std::ostream &os,const CGRect &R);

typedef arr::arr1<grct> grct_arr1;

extern const grct unitR;
#endif
