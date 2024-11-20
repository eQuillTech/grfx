//2-D scaling - P. Ahrenkiel

#ifndef _SCL2_
#define _SCL2_

class trf2;

//scl2
class scl2:public trf2
{

	public:	
	scl2(double x);

	scl2 inverse() const;
	
	scl2 operator*(const scl2 &S);
	scl2 operator/(const scl2 &S);
	scl2 operator*=(const scl2 &S);
	scl2 operator/=(const scl2 &S);

};
	
#endif

