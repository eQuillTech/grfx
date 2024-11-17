//graphics images - Phil Ahrenkiel

#ifndef _GIMG_
#define _GIMG_
#include "CoreGraphics/CoreGraphics.h"

#ifndef _GRCT_
#include "grct.hpp"
#endif

//
struct GimgData
{
public:
	GimgData(){}
	GimgData(const CGImageRef& imageR):m_imageR(imageR){}
	CGImageRef m_imageR=nullptr;
};

class gimg:public Gfrm
{
private:
	CGImageRef m_imageR=nullptr;
	CGAffineTransform m_transform;
	
public:
	gimg():Gfrm(){}
	gimg(const GimgData& data,const Gfrm &f);
	~gimg(){}

	CGImageRef imageRef(){return m_imageR;}
	const CGImageRef imageRef() const{return m_imageR;}
	CGRect imageFrame() const{return CGRectMake(0,0,imageWidth(),imageHeight());}

	std::size_t imageWidth() const{return m_imageR?CGImageGetWidth(m_imageR):0;}
	std::size_t imageHeight() const{return m_imageR?CGImageGetHeight(m_imageR):0;}
	CGSize imageSize() const{return imageFrame().size;}

	void doRender(CGContextRef context,const CGRect &Rdest) const override;
};
	
typedef arr1<gimg> Gimg_arr1;
typedef arr1<gimg *> Gimg_parr1;

#endif
