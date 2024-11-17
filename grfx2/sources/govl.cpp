//graphics ovals - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx.hpp"

using namespace std;

//
govl govl::operator=(const Gfrm &f)
{
	return *this=(govl)f;
}

//
void govl::doFill(CGContextRef context,const CGRect& Rdest) const
{
	CGContextFillEllipseInRect(context,Rdest);
}

//
void govl::doStroke(CGContextRef context,const CGRect& Rdest) const
{
	CGContextStrokeEllipseInRect(context,Rdest);
}
