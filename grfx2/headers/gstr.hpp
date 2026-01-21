//graphics strings - P. Ahrenkiel

#ifndef _GSTR_
#define _GSTR_

#include "CoreGraphics/CoreGraphics.h"

#include "str.hpp"
#include "gfrm.hpp"

class gpnt;

class gstr:public gfrm 
{
private:
	str m_text;
	
public:
	gstr();
	gstr(const double t,const double l,const double b,const double r,const str s="");
	gstr(const gpnt tl,const gpnt br,const str s="");
	gstr(const gfrm & f,const str s="");
	gstr(CGRect R,const str s="");
	gstr operator=(const gfrm  &f);

	#if defined(TARGET_IOS) || defined(TARGET_TVOS)
	void doRender(CGContextRef context,const CGRect &Rdest) const override;
	#endif
};

std::ostream& operator<<(std::ostream &os,const CGRect &R);

typedef arr::arr1<gstr> gstr_arr1;

#endif
