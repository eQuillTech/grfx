//graphics ovals - P. Ahrenkiel

#ifndef _GOVL_
#define _GOVL_

#include "CoreGraphics/CoreGraphics.h"

#include "gfrm.hpp"

class govl:public gfrm 
{
public:	
	govl(const double t=0.,const double l=0.,const double b=0.,const double r=0.);
	govl(const gpnt tl,const gpnt br);
	govl(const gfrm  &f);
	govl(const grct &r);
	~govl();

	govl operator=(const gfrm  &f);
	double meanRadius() const;

	void doFill(CGContextRef context,const CGRect& Rdest) const override;
	void doStroke(CGContextRef context,const CGRect& Rdest) const override;
};

#endif
