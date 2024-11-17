//2-D rotations - P. Ahrenkiel

#ifndef _RTN2_
#define _RTN2_

class Vtr2;
class Trf2;

//
class Rtn2:public Trf2
{

public:
	Rtn2(const Vtr2 &V,const Vtr2 &Vp);
	Rtn2(const double angle);
	Rtn2(const Trf2 &T);
	Rtn2(const Rtn2 &R);//copy constructor

	Rtn2 operator*(const Rtn2 &R) const;
	Rtn2 operator/(const Rtn2 &R) const;
	Rtn2 operator/=(const Rtn2 &R);
	Rtn2 inv() const;
};

#endif

