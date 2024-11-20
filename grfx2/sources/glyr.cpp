//graphics layers - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "tlbx.hpp"
#include "grfx2.hpp"

using namespace std;

//
glyr::glyr(const glyrData &data,const gfrm  &frameF):
	gimg(data,frameF),
	m_N_frames(data.m_N_framesX,data.m_N_framesY),m_iFrame(0,0)
{}

// CGContextRef context:
// const CGRect &Rframe: some frame in graphics coords
// const grct &frameF: equivalent frame in world coords
void glyr::doRender(CGContextRef context,const CGRect &Rframe,const gfrm  &frameF) const
{
	double w=width();//width of object in world coords
	double h=height();//height of object in world coords
	
	double hp=double(m_N_frames(1))*h;//full width of Object in game coords
	double wp=double(m_N_frames(0))*w;//full height of Object in game coords
		
	//location of (0,0) Object in world coords
	gpnt pp=topLeft()+(-(double(m_iFrame.i()))*w)*vtr2::Vx+((double(m_iFrame.j()))*h)*vtr2::Vy;
	
	//full dimensions of object in world coords
	gfrm extF(pp.y(),pp.x(),pp.y()-hp,pp.x()+wp);

	render(context,Rframe,frameF,extF);
}
