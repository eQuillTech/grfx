//3-D rotations - P. Ahrenkiel

#ifndef _RTN3_
#define _RTN3_

#ifndef _TRF3_
#include "Trf3.hpp"
#endif

class Vtr3;

//
class Rtn3:public Trf3
{
private:
	Rtn3(const Trf3 &T):Trf3(T){}

public:
	Rtn3(const Vtr3 &V0,const Vtr3 &V1,const Vtr3 &V2);
	Rtn3(const Vtr3 &V2,double angle);
	Rtn3(const Vtr3 &V,const Vtr3 &Vp);
	Rtn3(const double theta,const double phi,const double rho);
	Rtn3(const VtrDir &dir);
	//	Rtn3(const Rtn3 &R) noexcept:Trf3(R){}//copy constructor

	Rtn3 operator*(const Rtn3 &R) const noexcept{return Trf3::operator*(R);}
	Rtn3 operator/(const Rtn3 &R) const noexcept{return Trf3::operator/(R);}
	Rtn3 operator*=(const Rtn3 &R) noexcept{return Trf3::operator*=(R);}
	Rtn3 operator/=(const Rtn3 &R) noexcept{return Trf3::operator/=(R);}
	
	Rtn3 inv() const{return Trf3::inv();}

	Trf3 operator*(const Trf3 &T) const noexcept{return Trf3::operator*(T);}
	Trf3 operator/(const Trf3 &T) const noexcept{return Trf3::operator/(T);}
	
	Vtr3 operator*(const Vtr3 &V) const{return Trf3::operator*(V);}

	static const Rtn3 Ro;
};

#endif

