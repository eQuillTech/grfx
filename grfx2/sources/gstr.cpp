//graphics strings - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx2.hpp"

using namespace std;

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
//
void gstr::doRender(CGContextRef context,const CGRect &Rdest) const
{
	m_text.draw(Rdest);
}
#endif
