//graphics overlays - Phil Ahrenkiel

#ifndef _GCTX_
#define _GCTX_

#include "CoreGraphics/CoreGraphics.h"

#include "gfrm.hpp"

class gimg;

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

	CGContextRef contextRef();
	
	CFStringRef colorSpaceName();
	const CFStringRef colorSpaceName() const;
	
	std::size_t contextWidth() const;
	std::size_t contextHeight() const;
	CGRect contextFrame() const;;
	
	void *bitmapData();

	gimg image();
	const gimg image() const;
	
	void doRender(CGContextRef context,const CGRect &Rdest) const override;
};
	
#endif
