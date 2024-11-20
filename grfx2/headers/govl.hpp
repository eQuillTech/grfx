//graphics ovals - P. Ahrenkiel

#ifndef _GOVL_
#define _GOVL_

//#import <UIKit/UIKit.h>
#include "CoreGraphics/CoreGraphics.h"

#ifndef _GFRM_
#include "gfrm .h"
#endif

class govl:public gfrm 
{
public:	
	govl(const double t=0.,const double l=0.,const double b=0.,const double r=0.):gfrm (t,l,b,r){}
	govl(const gpnt tl,const gpnt br):gfrm (tl,br){}
	govl(const gfrm  &f):gfrm (f){}
	govl(const grct &r):gfrm (r){}
	~govl(){}

	govl operator=(const gfrm  &f);
	double meanRadius() const{return halfMeanSize();}

	//
	void doFill(CGContextRef context,const CGRect& Rdest) const override;
	void doStroke(CGContextRef context,const CGRect& Rdest) const override;
};

#endif
