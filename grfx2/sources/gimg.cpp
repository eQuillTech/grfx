//graphics images - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx.hpp"

using namespace std;

//
gimg::gimg(const GimgData& data,const Gfrm &f):Gfrm(f),m_imageR(data.m_imageR)
{
	m_transform.a=1;m_transform.b=0;
	m_transform.c=0;m_transform.d=-1;
	m_transform.tx=0;
	m_transform.ty=imageHeight();//need to update for every draw
}

//
void gimg::doRender(CGContextRef context,const CGRect &Rdest) const
{
	if(m_imageR==nullptr)return;
	CGAffineTransform transform=m_transform;
	transform.ty=2.*Rdest.origin.y+Rdest.size.height;
	CGContextConcatCTM(context,transform);
  CGContextDrawImage(context,Rdest,m_imageR);
}
