//graphics overlays - P. Ahrenkiel
//see https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/dq_context/dq_context.html#//apple_ref/doc/uid/TP30001066-CH203-CJBHBFFE

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "gfrm.hpp"
#include "gimg.hpp"
#include "gctx.hpp"

gctx::gctx(size_t width,size_t height,const gfrm  &f):gfrm (f),m_width(width),m_height(height)
{
	size_t bytesPerRow=(m_width*4);
	size_t byteCount=(bytesPerRow*m_height);
 
 	//Create the context
 	void *bitmapData=calloc(byteCount,sizeof(uint8_t));
  if(bitmapData==NULL)
	{
		return;
	}
	CGColorSpaceRef colorSpace=CGColorSpaceCreateWithName(m_colorSpaceName);
	m_context=CGBitmapContextCreate
	(	bitmapData,
		m_width,
		m_height,
		8, // bits per component
		bytesPerRow,
		colorSpace,
		m_bitmapInfo
	);
	if(m_context==NULL)
	{
		free (bitmapData);
		fprintf (stderr, "Context not created!");
		return;
	}
	CGColorSpaceRelease(colorSpace);
}

gctx::~gctx()
{
	void *bitmapData=CGBitmapContextGetData(m_context);
  CGContextRelease(m_context);
	if(bitmapData)
		free(bitmapData);
}

void gctx::doRender(CGContextRef context,const CGRect &Rdest) const
{
	//gimg(CGBitmapContextCreateImage(m_context),R());
	//gimg img(CGImageCreateWithMask(CGBitmapContextCreateImage(m_context),imageRef()),R());
  image().doRender(context,Rdest);
}

CGContextRef gctx::contextRef(){return m_context;}

CFStringRef gctx::colorSpaceName(){return m_colorSpaceName;}
const CFStringRef gctx::colorSpaceName() const{return m_colorSpaceName;}

std::size_t gctx::contextWidth() const{return m_width;}
std::size_t gctx::contextHeight() const{return m_height;}
CGRect gctx::contextFrame() const{return CGRectMake(0,0,m_width,m_height);}

void *gctx::bitmapData(){return CGBitmapContextGetData(m_context);}

gimg gctx::image(){return gimg(CGBitmapContextCreateImage(m_context),R());}
const gimg gctx::image() const{return gimg(CGBitmapContextCreateImage(m_context),R());}
