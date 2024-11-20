//3-D reflections - P. Ahrenkiel

#ifndef _RFN3_
#define _RFN3_

#ifndef _TRF3_
#include "trf3.hpp"
#endif

class vtr3;

//
class rfn3:public trf3
{
private:
	rfn3(const trf3 &T):trf3(T){}

public:
	rfn3(const vtr3 &V);

	trf3 operator*(const trf3 &T) const noexcept{return trf3::operator*(T);}
	trf3 operator/(const trf3 &T) const noexcept{return trf3::operator/(T);}
};

#endif

