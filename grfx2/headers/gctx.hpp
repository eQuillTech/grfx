//graphics overlays - Phil Ahrenkiel

#ifndef _GCTX_
#define _GCTX_

#include "CoreGraphics/CoreGraphics.h"

#ifndef _GRCT_
#include "grct.hpp"
#endif

//
class gctx:public gfrm 
{
private:
	CGContextRef m_context=nullptr;
	std::size_t m_width;
	std::size_t m_height;
	CFStringRef m_colorSpaceName=kCGColorSpaceGenericRGB;
	uint32_t m_bitmapInfo=kCGImageAlphaPremultipliedLast;
	
public:
	gctx():gfrm (){}
	gctx(std::size_t width,std::size_t height,const gfrm  &f);
	~gctx();

	CGContextRef contextRef(){return m_context;}
	
	CFStringRef colorSpaceName(){return m_colorSpaceName;}
	const CFStringRef colorSpaceName() const{return m_colorSpaceName;}
	
	std::size_t contextWidth() const{return m_width;}
	std::size_t contextHeight() const{return m_height;}
	CGRect contextFrame() const{return CGRectMake(0,0,m_width,m_height);}
	
	void *bitmapData(){return CGBitmapContextGetData(m_context);}

	gimg image(){return gimg(CGBitmapContextCreateImage(m_context),R());}
	const gimg image() const{return gimg(CGBitmapContextCreateImage(m_context),R());}
	
	void doRender(CGContextRef context,const CGRect &Rdest) const override;
};
	
#endif
