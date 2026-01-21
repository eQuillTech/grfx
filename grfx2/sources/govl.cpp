//graphics ovals - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "gfrm.hpp"
#include "grct.hpp"
#include "govl.hpp"

govl::govl(const double t=0.,const double l=0.,const double b=0.,const double r=0.):gfrm (t,l,b,r){}
govl::govl(const gpnt tl,const gpnt br):gfrm (tl,br){}
govl::govl(const gfrm  &f):gfrm(f){}
govl::govl(const grct &r):gfrm(r){}
~govl::govl(){}
	
govl govl::operator=(const gfrm  &f)
{
	return *this=(govl)f;
}

double govl::meanRadius() const{return halfMeanSize();}
	
void govl::doFill(CGContextRef context,const CGRect& Rdest) const
{
	CGContextFillEllipseInRect(context,Rdest);
}

void govl::doStroke(CGContextRef context,const CGRect& Rdest) const
{
	CGContextStrokeEllipseInRect(context,Rdest);
}
