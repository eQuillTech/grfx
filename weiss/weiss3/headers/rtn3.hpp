//3-D rotations - P. Ahrenkiel

#ifndef _RTN3_
#define _RTN3_

#ifndef _TRF3_
#include "trf3.hpp"
#endif

class vtr3;

//
class rtn3:public trf3
{
private:
	rtn3(const trf3 &T):trf3(T){}

public:
	rtn3(const vtr3 &V0,const vtr3 &V1,const vtr3 &V2);
	rtn3(const vtr3 &V2,double angle);
	rtn3(const vtr3 &V,const vtr3 &Vp);
	rtn3(const double theta,const double phi,const double rho);
	rtn3(const VtrDir &dir);
	//	rtn3(const rtn3 &R) noexcept:trf3(R){}//copy constructor

	rtn3 operator*(const rtn3 &R) const noexcept{return trf3::operator*(R);}
	rtn3 operator/(const rtn3 &R) const noexcept{return trf3::operator/(R);}
	rtn3 operator*=(const rtn3 &R) noexcept{return trf3::operator*=(R);}
	rtn3 operator/=(const rtn3 &R) noexcept{return trf3::operator/=(R);}
	
	rtn3 inv() const{return trf3::inv();}

	trf3 operator*(const trf3 &T) const noexcept{return trf3::operator*(T);}
	trf3 operator/(const trf3 &T) const noexcept{return trf3::operator/(T);}
	
	vtr3 operator*(const vtr3 &V) const{return trf3::operator*(V);}

	static const rtn3 Ro;
};

#endif

