//graphics rectangles - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "gpnt.hpp"
#include "grct.hpp"

const grct unitR(1,-1,-1,1);

grct::grct():gfrm (){}
grct::grct(const double t,const double l,const double b,const double r):gfrm (t,l,b,r){}
grct::grct(const gpnt tl,const gpnt br):gfrm (tl,br){}
grct::grct(const gfrm & f):gfrm (f){}
grct::grct(CGRect R):gfrm (R){}

//static
void grct::fill(CGContextRef context,const CGRect &Rdest)
{
	CGContextFillRect(context,Rdest);
}

//static
void grct::stroke(CGContextRef context,const CGRect &Rdest)
{
	CGContextStrokeEllipseInRect(context,Rdest);
}

void grct::doFill(CGContextRef context,const CGRect &Rdest) const
{
	grct::fill(context,Rdest);
}

void grct::doStroke(CGContextRef context,const CGRect &Rdest) const
{
	grct::stroke(context,Rdest);
}
