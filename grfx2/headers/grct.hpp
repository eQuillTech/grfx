//graphics rectangles - P. Ahrenkiel

#ifndef _GRCT_
#define _GRCT_

//#import <UIKit/UIKit.h>
#include "CoreGraphics/CoreGraphics.h"

#ifndef _GPNT_
#include "gpnt.hpp"
#endif

#ifndef _GFRM_
#include "Gfrm.hpp"
#endif

class grct:public Gfrm
{
private:

public:
	grct():Gfrm(){}
	grct(const double t,const double l,const double b,const double r):Gfrm(t,l,b,r){}
	grct(const gpnt tl,const gpnt br):Gfrm(tl,br){}
	grct(const Gfrm& f):Gfrm(f){}
	grct(CGRect R):Gfrm(R){}
	grct operator=(const Gfrm &f);

	//
	static void fill(CGContextRef context,const CGRect &Rdest);
	static void stroke(CGContextRef context,const CGRect &Rdest);

	//
	void doFill(CGContextRef context,const CGRect &Rdest) const override;
	void doStroke(CGContextRef context,const CGRect &Rdest) const override;
};

std::ostream& operator<<(std::ostream &os,const CGRect &R);

typedef arr1<grct> Grct_arr1;

extern const grct unitR;
#endif
