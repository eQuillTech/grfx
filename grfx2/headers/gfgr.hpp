//graphics figures - P. Ahrenkiel

#ifndef _GFGR_
#define _GFGR_

//#import <UIKit/UIKit.h>
#include "CoreGraphics/CoreGraphics.h"

#ifndef _GPNT_
#include "gpnt.h"
#endif

class gcmr;

class Gfgr
{
private:

public:
	Gfgr(){}

	//
	virtual void doFill(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const{}
	virtual void doFill(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const{}
	virtual void doStroke(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const{}
	virtual void doStroke(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const{}
	virtual void doRender(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const{}
	virtual void doRender(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF,const CGRect &Rext) const{}
	virtual void doRender(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const{}
	virtual void doRender(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,const CGRect &Rext) const{}
	virtual void doRadGradient(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF,CGGradientRef grad,const CGPoint &Pi,const CGPoint &Pf,const double Ri,const double Rf) const{}

	void fill(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const;
	void fill(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const;
	void stroke(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF,const float thick) const;
	void stroke(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,const float thick) const;
	void render(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const;
	void render(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF,const Gfrm &extF) const;
	void render(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z) const;
	void render(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,const Gfrm &extF) const;
	void radGradient(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,CGGradientRef grad,const gpnt &pStart,const gpnt &pStop,const double Ri,const double Rf) const;

	//masked
	virtual void doFill(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const Gfrm &frameF) const{}
	virtual void doStroke(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const Gfrm &frameF) const{}
	virtual void doRender(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const Gfrm &frameF) const{}

	void fill(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const Gfrm &frameF) const;
	void stroke(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const Gfrm &frameF,const float thick) const;
	void render(CGContextRef context,CGImageRef mask,const CGRect &Rframe,const Gfrm &frameF) const;
	
	//
	static void rotate(CGContextRef context,const CGPoint &Paxis,const double ang);
	void rotate(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF,const gpnt& axisP,const double ang) const;
	void rotate(CGContextRef context,const CGRect &Rframe,const gcmr &camera,const double z,const gpnt& axisP,const double ang) const;
	

};

#endif
