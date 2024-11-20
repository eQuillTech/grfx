//graphics rectangles - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx2.hpp"

using namespace std;

const grct unitR(1,-1,-1,1);

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

//
void grct::doFill(CGContextRef context,const CGRect &Rdest) const
{
	grct::fill(context,Rdest);
}

//
void grct::doStroke(CGContextRef context,const CGRect &Rdest) const
{
	grct::stroke(context,Rdest);
}
