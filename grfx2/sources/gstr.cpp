//graphics strings - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx.hpp"

using namespace std;

//
void gstr::doRender(CGContextRef context,const CGRect &Rdest) const
{
	m_text.draw(Rdest);
}
