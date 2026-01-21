//graphics images - Phil Ahrenkiel

#ifndef _GBMP_
#define _GBMP_
#include "CoreGraphics/CoreGraphics.h"

class gbmp
{
private:
	void *_bitmap;
	CGSize _size;
	CGColorSpaceRef _colorSpace;
	uint32_t _bitmapInfo;
	size_t _bitsPerComponent;
	
public:
	gbmp(){}
	gbmp(const CGImageRef& imageR);
	~gbmp();

	void* &bitmap(){return _bitmap;}
	void* const &bitmap() const{return _bitmap;}
	
	CGSize &size(){return _size;}
	CGSize const &size() const{return _size;}
	
};

#endif
