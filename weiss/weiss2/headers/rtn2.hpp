//2-D rotations - P. Ahrenkiel

#ifndef _RTN2_
#define _RTN2_

class Vtr2;
class trf2;

//
class rtn2:public trf2
{

public:
	rtn2(const vtr2 &V,const vtr2 &Vp);
	rtn2(const double angle);
	rtn2(const trf2 &T);
	rtn2(const rtn2 &R);//copy constructor

	rtn2 operator*(const rtn2 &R) const;
	rtn2 operator/(const rtn2 &R) const;
	rtn2 operator/=(const rtn2 &R);
	rtn2 inv() const;
};

#endif

