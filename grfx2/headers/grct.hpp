//graphics rectangles - P. Ahrenkiel

#ifndef _GRCT_
#define _GRCT_

//#import <UIKit/UIKit.h>
#include "CoreGraphics/CoreGraphics.h"

#ifndef _GPNT_
#include "gpnt.hpp"
#endif

#ifndef _GFRM_
#include "gfrm .hpp"
#endif

class grct:public gfrm 
{
private:

public:
	grct():gfrm (){}
	grct(const double t,const double l,const double b,const double r):gfrm (t,l,b,r){}
	grct(const gpnt tl,const gpnt br):gfrm (tl,br){}
	grct(const gfrm & f):gfrm (f){}
	grct(CGRect R):gfrm (R){}
	grct operator=(const gfrm  &f);

	//
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
