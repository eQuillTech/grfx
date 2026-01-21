//graphics images - Phil Ahrenkiel

#ifndef _GIMG_
#define _GIMG_

#include "CoreGraphics/CoreGraphics.h"

class grct;

struct gimgData
{
public:
	gimgData(){}
	gimgData(const CGImageRef& imageR):m_imageR(imageR){}
	CGImageRef m_imageR=nullptr;
};

class gimg:public gfrm2
{
private:
	CGImageRef m_imageR=nullptr;
	CGAffineTransform m_transform;
	
public:
	gimg():gfrm(){}
	gimg(const gimgData& data,const gfrm  &f);
	~gimg(){}

	CGImageRef imageRef();
	const CGImageRef imageRef() const;
	CGRect imageFrame() const;

	std::size_t imageWidth() const;
	std::size_t imageHeight() const;
	CGSize imageSize() const;

	void doRender(CGContextRef context,const CGRect &Rdest) const override;
};
	
typedef arr::arr1<gimg> Gimg_arr1;
typedef arr::arr1<gimg *> Gimg_parr1;

#endif
