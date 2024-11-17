//graphics figures - P. Ahrenkiel

#include <cstdlib>
#include <math.h>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx.hpp"

using namespace std;

//
void Gfgr::fill(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const
{
	doFill(context,Rframe,frameF);
}

//
void Gfgr::fill(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const
{
	Gfrm frameF=camera.plate().proj(camera,z);
	doFill(context,Rframe,frameF);
}

//
void Gfgr::stroke(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF,const float thick) const
{
	CGContextSetLineWidth(context,thick);
	doStroke(context,Rframe,frameF);
}

//
void Gfgr::stroke(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,const float thick) const
{
	CGContextSetLineWidth(context,thick);
	Gfrm frameF=camera.plate().proj(camera,z);
	doStroke(context,Rframe,frameF);
}

//
void Gfgr::render(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const
{
	doRender(context,Rframe,frameF);
}
	
//
void Gfgr::render(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF,const Gfrm &extF) const
{
	CGRect Rext=extF.map(Rframe,frameF);
	doRender(context,Rframe,frameF,Rext);
}

//
void Gfgr::render(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const
{
	Gfrm frameF=camera.plate().proj(camera,z);
	doRender(context,Rframe,frameF);
}

//
void Gfgr::render(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,const Gfrm &extF) const
{
	Gfrm frameF=camera.plate().proj(camera,z);
	CGRect Rext=extF.map(Rframe,frameF);
	doRender(context,Rframe,frameF,Rext);
}

//
void Gfgr::radGradient(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,CGGradientRef grad,const gpnt &startP,const gpnt &stopP,const double Ri,const double Rf) const
{
	Gfrm frameF=camera.plate().proj(camera,z);
	CGPoint Pi=startP.map(Rframe,frameF);
	CGPoint Pf=stopP.map(Rframe,frameF);
	doRadGradient(context,Rframe,frameF,grad,Pi,Pf,Ri,Rf);
}

//
void Gfgr::fill(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const Gfrm &frameF) const
{
	CGContextClipToMask(context,Rframe,mask);
	doFill(context,Rframe,frameF);
}

//
void Gfgr::stroke(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const Gfrm &frameF,const float thick) const
{
	CGContextClipToMask(context,Rframe,mask);
	CGContextSetLineWidth(context,thick);
	doStroke(context,Rframe,frameF);
}

//
void Gfgr::render(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const Gfrm &frameF) const
{
	CGContextClipToMask(context,Rframe,mask);
	doRender(context,Rframe,frameF);
}
	
//static
void Gfgr::rotate(CGContextRef context,const CGPoint &Paxis, const double ang)
{
	CGContextTranslateCTM(context,Paxis.x,Paxis.y);
	CGContextRotateCTM(context,ang);
	CGContextTranslateCTM(context,-Paxis.x,-Paxis.y);
}

//
void Gfgr::rotate(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF,const gpnt& axisP,const double ang) const
{
	if(ang!=0.)
	{
		CGPoint Paxis=axisP.map(Rframe,frameF);//axis in user coords
		Gfgr::rotate(context,Paxis,ang);
	}
}

//
void Gfgr::rotate(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,const gpnt& axisP,const double ang) const
{
	if(ang!=0.)
	{
		Gfrm frameF=camera.plate().proj(camera,z);
		CGPoint Paxis=axisP.map(Rframe,frameF);//axis in user coords
		Gfgr::rotate(context,Paxis,ang);
	}
}

