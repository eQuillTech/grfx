//2-D transformations - P. Ahrenkiel

#ifndef _TRF2_
#define _TRF2_

#ifndef _TLBX_
#include "tlbx.hpp"
#endif

#include "arr.hpp"

class Vtr2;

//
class Trf2
{
protected:
	union
	{
		struct
		{
			double _00,_01;
			double _10,_11;
		};
		double _p[2][2]; // array representation
	};
	
public:
	constexpr Trf2():_00(0.),_01(0.),_10(0.),_11(0.){}
	constexpr Trf2(const double x[2][2]):_00(x[0][0]),_01(x[0][1]),_10(x[1][0]),_11(x[1][1]){}
	Trf2(const arr::darr2 &D);

//
	Vtr2 operator*(const Vtr2 &V) const;
	Pnt2 operator*(const Pnt2 &P) const;

	Trf2 operator*(const Trf2 &T) const;
	Trf2 operator/(const Trf2 &T) const{return T.inv()*(*this);}
	Trf2 operator*=(const Trf2 &T){return *this=*this*T;}
	Trf2 operator/=(const Trf2 &T){return *this=*this/T;}

	operator arr::darr2() const;

//
	double &operator()(const size_t i,const size_t j){return _p[i][j];}
	double const &operator()(const size_t i,const size_t j) const{return _p[i][j];}

	Trf2 T() const;
	Trf2 inv() const;
	static constexpr const Trf2 ident(){const double x[2][2]={{1.,0.},{0.,1.}};return Trf2(x);}

	friend Trf2 operator*(double x,const Trf2 &T);
	friend Trf2 operator/(double x,const Trf2 &T);

	static const Trf2 To;

};

#endif

