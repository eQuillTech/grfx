//3-D scaling - P. Ahrenkiel

#ifndef _SCL3_
#define _SCL3_

#ifndef _TRF3_
#include "Trf3.hpp"
#endif

//Scl3
class Scl3:public Trf3
{
private:
	Scl3(const Trf3 &T):Trf3(T){}
	
public:
	Scl3(double x);
	//Scl3(const Scl3 &S) noexcept:Trf3(S){}

	Scl3 operator*(const Scl3 &S) const noexcept{return Trf3::operator*(S);}
	Scl3 operator/(const Scl3 &S) const noexcept{return Trf3::operator/(S);}
	Scl3 operator*=(const Scl3 &S) noexcept{return (*this)=(*this)*(S);}
	Scl3 operator/=(const Scl3 &S) noexcept{return (*this)=(*this)/(S);}

	Scl3 inv() const{return Trf3::inv();}
	
	Trf3 operator*(const Trf3 &T) const noexcept{return Trf3::operator*(T);}
	Trf3 operator/(const Trf3 &T) const noexcept{return Trf3::operator/(T);}
};
	
#endif

