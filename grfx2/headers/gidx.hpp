//graphics indices - P. Ahrenkiel

#ifndef _GIDX_
#define _GIDX_

#include "idx2.hpp"

class gidx:public idx2
{
	static const gidx zeroI,xI,xY;
};

typedef arr::arr1<gidx2> gidx2_arr1;

#endif
