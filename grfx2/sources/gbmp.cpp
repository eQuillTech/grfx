//graphics images - P. Ahrenkiel

#include <cstdlib>
#include "CoreGraphics/CoreGraphics.h"

#include "gbmp.hpp"

gbmp::gbmp(const CGImageRef& imageR)
{
	_size.width=CGImageGetWidth(imageR);
	_size.height=CGImageGetHeight(imageR);
	_colorSpace=CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
	_bitmapInfo=kCGImageAlphaPremultipliedLast;
	_bitsPerComponent=CGImageGetBitsPerComponent(imageR);
	
 	//Create the context
	size_t bytes_per_row=CGImageGetBytesPerRow(imageR);
	size_t byte_count=bytes_per_row*_size.height;
 	_bitmap=calloc(byte_count,sizeof(uint8_t));
  if(_bitmap!=NULL)
	{
		CGContextRef context=CGBitmapContextCreate
		(	_bitmap,
			_size.width,
			_size.height,
			_bitsPerComponent,
			bytes_per_row,
			_colorSpace,
			_bitmapInfo
		);

		CGRect Rdest=CGRectMake(0,0,_size.width,_size.height);
		CGContextDrawImage(context,Rdest,imageR);
		CGContextRelease(context);
	}
}

gbmp::~gbmp()
{
	if(_bitmap)
		free(_bitmap);
}
