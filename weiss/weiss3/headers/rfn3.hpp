//3-D reflections - P. Ahrenkiel

#ifndef _RFN3_
#define _RFN3_

#ifndef _TRF3_
#include "Trf3.hpp"
#endif

class Vtr3;

//
class Rfn3:public Trf3
{
private:
	Rfn3(const Trf3 &T):Trf3(T){}

public:
	Rfn3(const Vtr3 &V);

	Trf3 operator*(const Trf3 &T) const noexcept{return Trf3::operator*(T);}
	Trf3 operator/(const Trf3 &T) const noexcept{return Trf3::operator/(T);}
};

#endif

