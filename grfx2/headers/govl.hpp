//graphics ovals - P. Ahrenkiel

#ifndef _GOVL_
#define _GOVL_

//#import <UIKit/UIKit.h>
#include "CoreGraphics/CoreGraphics.h"

#ifndef _GFRM_
#include "Gfrm.h"
#endif

class govl:public Gfrm
{
public:	
	govl(const double t=0.,const double l=0.,const double b=0.,const double r=0.):Gfrm(t,l,b,r){}
	govl(const gpnt tl,const gpnt br):Gfrm(tl,br){}
	govl(const Gfrm &f):Gfrm(f){}
	govl(const grct &r):Gfrm(r){}
	~govl(){}

	govl operator=(const Gfrm &f);
	double meanRadius() const{return halfMeanSize();}

	//
	void doFill(CGContextRef context,const CGRect& Rdest) const override;
	void doStroke(CGContextRef context,const CGRect& Rdest) const override;
};

#endif
