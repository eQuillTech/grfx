//graphics strings - P. Ahrenkiel

#ifndef _GSTR_
#define _GSTR_

//#import <UIKit/UIKit.h>
#include "CoreGraphics/CoreGraphics.h"

#ifndef _GPNT_
#include "gpnt.hpp"
#endif

#ifndef _GFRM_
#include "Gfrm.hpp"
#endif

class gstr:public Gfrm
{
private:
	str m_text;
	
public:
	gstr():Gfrm(){m_text="";}
	gstr(const double t,const double l,const double b,const double r,const str s=""):Gfrm(t,l,b,r){}
	gstr(const gpnt tl,const gpnt br,const str s=""):Gfrm(tl,br){m_text=s;}
	gstr(const Gfrm& f,const str s=""):Gfrm(f){m_text=s;}
	gstr(CGRect R,const str s=""):Gfrm(R){m_text=s;}
	gstr operator=(const Gfrm &f){return *this=gstr(f,m_text);}

	//
	void doRender(CGContextRef context,const CGRect &Rdest) const override;

};

std::ostream& operator<<(std::ostream &os,const CGRect &R);

typedef arr1<gstr> Gstr_arr1;

#endif
