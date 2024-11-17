//graphics layers - P. Ahrenkiel

#ifndef _GLYR_
#define _GLYR_

//#import <UIKit/UIKit.h>
#include "CoreGraphics/CoreGraphics.h"

#ifndef _GRFX_
#include "grfx.hpp"
#endif

//
struct GlyrData:public GimgData
{
public:
	GlyrData():GimgData(){}
	GlyrData(const GimgData& data):GimgData(data){}
	short m_N_framesX=1;
	short m_N_framesY=1;
};

//
class Glyr:public gimg
{
private:
	gidx m_N_frames;//number of frames in x-y
	gidx m_iFrame;//frame indices
	
public:
	Glyr():gimg(){}
	Glyr(const GlyrData &data,const Gfrm &frameF);
	~Glyr(){}
	
	std::size_t& Nx(){return m_N_frames(0);}
	std::size_t& Ny(){return m_N_frames(1);}
	std::size_t& iX(){return m_iFrame.i();}
	std::size_t& iY(){return m_iFrame.j();}
	gidx index(){return m_iFrame;}

	std::size_t const& Nx() const{return m_N_frames(0);}
	std::size_t const& Ny() const{return m_N_frames(1);}
	std::size_t const& iX() const{return m_iFrame.i();}
	std::size_t const& iY() const{return m_iFrame.j();}
	gidx const index() const{return m_iFrame;}

	Glyr* Nx(const std::size_t& Nx){m_N_frames(0)=Nx;return this;}
	Glyr* Ny(const std::size_t& Ny){m_N_frames(1)=Ny;return this;}
	Glyr* iX(const std::size_t& iX){m_iFrame(0)=iX;return this;}
	Glyr* iY(const std::size_t& iY){m_iFrame(1)=iY;return this;}
	Glyr* index(const gidx& frame){m_iFrame.i()=frame.i();m_iFrame.j()=frame.j();return this;}
	Glyr* index(const gpnt& P){m_iFrame(0)=P.x();m_iFrame(1)=P.y();return this;}
	
	void doRender(CGContextRef context,const CGRect &Rframe,const Gfrm &frameF) const override;
};

#endif
