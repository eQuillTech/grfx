//graphics figures - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "gcmr.hpp"
#include "gfrm.hpp"
#include "gpnt.hpp"
#include "gfgr.hpp"

gfgr::gfgr(){}

void gfgr::doFill(CGContextRef context,const CGRect &Rframe,const gfrm &frameF) const{}
void gfgr::doFill(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const{}
void gfgr::doStroke(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const{}
void gfgr::doStroke(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const{}
void gfgr::doRender(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const{}
void gfgr::doRender(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF,const CGRect &Rext) const{}
void gfgr::doRender(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const{}
void gfgr::doRender(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,const CGRect &Rext) const{}
void gfgr::doRadGradient(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF,CGGradientRef grad,const CGPoint &Pi,const CGPoint &Pf,const double Ri,const double Rf) const{}

void gfgr::doFill(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const gfrm &frameF) const{}
void gfgr::doStroke(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const gfrm &frameF) const{}
void gfgr::doRender(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const gfrm &frameF) const{}

void gfgr::fill(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	doFill(context,Rframe,frameF);
}

void gfgr::fill(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const
{
	gfrm  frameF=camera.plate().proj(camera,z);
	doFill(context,Rframe,frameF);
}

void gfgr::stroke(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF,const float thick) const
{
	CGContextSetLineWidth(context,thick);
	doStroke(context,Rframe,frameF);
}

void gfgr::stroke(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,const float thick) const
{
	CGContextSetLineWidth(context,thick);
	gfrm  frameF=camera.plate().proj(camera,z);
	doStroke(context,Rframe,frameF);
}

void gfgr::render(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	doRender(context,Rframe,frameF);
}
	
void gfgr::render(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF,const gfrm  &extF) const
{
	CGRect Rext=extF.map(Rframe,frameF);
	doRender(context,Rframe,frameF,Rext);
}

void gfgr::render(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const
{
	gfrm  frameF=camera.plate().proj(camera,z);
	doRender(context,Rframe,frameF);
}

void gfgr::render(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,const gfrm  &extF) const
{
	gfrm  frameF=camera.plate().proj(camera,z);
	CGRect Rext=extF.map(Rframe,frameF);
	doRender(context,Rframe,frameF,Rext);
}

void gfgr::radGradient(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,CGGradientRef grad,const gpnt &startP,const gpnt &stopP,const double Ri,const double Rf) const
{
	gfrm  frameF=camera.plate().proj(camera,z);
	CGPoint Pi=startP.map(Rframe,frameF);
	CGPoint Pf=stopP.map(Rframe,frameF);
	doRadGradient(context,Rframe,frameF,grad,Pi,Pf,Ri,Rf);
}

void gfgr::fill(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const gfrm  &frameF) const
{
	CGContextClipToMask(context,Rframe,mask);
	doFill(context,Rframe,frameF);
}

void gfgr::stroke(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const gfrm  &frameF,const float thick) const
{
	CGContextClipToMask(context,Rframe,mask);
	CGContextSetLineWidth(context,thick);
	doStroke(context,Rframe,frameF);
}

void gfgr::render(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const gfrm  &frameF) const
{
	CGContextClipToMask(context,Rframe,mask);
	doRender(context,Rframe,frameF);
}
	
//static
void gfgr::rotate(CGContextRef context,const CGPoint &Paxis, const double ang)
{
	CGContextTranslateCTM(context,Paxis.x,Paxis.y);
	CGContextRotateCTM(context,ang);
	CGContextTranslateCTM(context,-Paxis.x,-Paxis.y);
}

void gfgr::rotate(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF,const gpnt& axisP,const double ang) const
{
	if(ang!=0.)
	{
		CGPoint Paxis=axisP.map(Rframe,frameF);//axis in user coords
		gfgr::rotate(context,Paxis,ang);
	}
}

void gfgr::rotate(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,const gpnt& axisP,const double ang) const
{
	if(ang!=0.)
	{
		gfrm frameF=camera.plate().proj(camera,z);
		CGPoint Paxis=axisP.map(Rframe,frameF);//axis in user coords
		gfgr::rotate(context,Paxis,ang);
	}
}

