//3-D scaling - P. Ahrenkiel

#ifndef _SCL3_
#define _SCL3_

#ifndef _TRF3_
#include "trf3.hpp"
#endif

//scl3
class scl3:public trf3
{
private:
	scl3(const trf3 &T):trf3(T){}
	
public:
	scl3(double x);
	//scl3(const scl3 &S) noexcept:trf3(S){}

	scl3 operator*(const scl3 &S) const noexcept{return trf3::operator*(S);}
	scl3 operator/(const scl3 &S) const noexcept{return trf3::operator/(S);}
	scl3 operator*=(const scl3 &S) noexcept{return (*this)=(*this)*(S);}
	scl3 operator/=(const scl3 &S) noexcept{return (*this)=(*this)/(S);}

	scl3 inv() const{return trf3::inv();}
	
	trf3 operator*(const trf3 &T) const noexcept{return trf3::operator*(T);}
	trf3 operator/(const trf3 &T) const noexcept{return trf3::operator/(T);}
};
	
#endif

