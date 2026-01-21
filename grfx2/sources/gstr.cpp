//graphics strings - P. Ahrenkiel

#include <cstdlib>

#include "CoreGraphics/CoreGraphics.h"

#include "str.hpp"

#include "gpnt.hpp"
#include "gfrm.hpp"
#include "gstr.hpp"

gstr::gstr():gfrm(){m_text="";}
gstr::gstr(const double t,const double l,const double b,const double r,const str s=""):gfrm (t,l,b,r){}
gstr::gstr(const gpnt tl,const gpnt br,const str s=""):gfrm (tl,br){m_text=s;}
gstr::gstr(const gfrm & f,const str s=""):gfrm (f){m_text=s;}
gstr::gstr(CGRect R,const str s=""):gfrm (R){m_text=s;}
gstr::gstr operator=(const gfrm  &f){return *this=gstr(f,m_text);}

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
void gstr::doRender(CGContextRef context,const CGRect &Rdest) const
{
	m_text.draw(Rdest);
}
#endif
