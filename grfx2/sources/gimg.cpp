//graphics images - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "gfrm.hpp"
#include "gimg.hpp"

gimg::gimg(const gimgData& data,const gfrm &f):gfrm(f),m_imageR(data.m_imageR)
{
	m_transform.a=1;m_transform.b=0;
	m_transform.c=0;m_transform.d=-1;
	m_transform.tx=0;
	m_transform.ty=imageHeight();//need to update for every draw
}

void gimg::doRender(CGContextRef context,const CGRect &Rdest) const
{
	if(m_imageR==nullptr)return;
	CGAffineTransform transform=m_transform;
	transform.ty=2.*Rdest.origin.y+Rdest.size.height;
	CGContextConcatCTM(context,transform);
  CGContextDrawImage(context,Rdest,m_imageR);
}


CGImageRef gimg::imageRef(){return m_imageR;}
const CGImageRef gimg::imageRef() const{return m_imageR;}
CGRect gimg::imageFrame() const{return CGRectMake(0,0,imageWidth(),imageHeight());}

std::size_t gimg::imageWidth() const{return m_imageR?CGImageGetWidth(m_imageR):0;}
std::size_t gimg::imageHeight() const{return m_imageR?CGImageGetHeight(m_imageR):0;}
CGSize gimg::imageSize() const{return imageFrame().size;}
