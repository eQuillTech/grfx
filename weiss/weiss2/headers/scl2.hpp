//2-D scaling - P. Ahrenkiel

#ifndef _SCL2_
#define _SCL2_

class Trf2;

//Scl2
class Scl2:public Trf2
{

	public:	
	Scl2(double x);

	Scl2 inverse() const;
	
	Scl2 operator*(const Scl2 &S);
	Scl2 operator/(const Scl2 &S);
	Scl2 operator*=(const Scl2 &S);
	Scl2 operator/=(const Scl2 &S);

};
	
#endif

