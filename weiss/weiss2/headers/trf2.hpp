//2-D transformations - P. Ahrenkiel

#ifndef _TRF2_
#define _TRF2_

#ifndef _TLBX_
#include "tlbx.hpp"
#endif

#include "arr.hpp"

class vtr2;

//
class trf2
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
	constexpr trf2():_00(0.),_01(0.),_10(0.),_11(0.){}
	constexpr trf2(const double x[2][2]):_00(x[0][0]),_01(x[0][1]),_10(x[1][0]),_11(x[1][1]){}
	trf2(const arr::darr2 &D);

//
	vtr2 operator*(const vtr2 &V) const;
	pnt2 operator*(const pnt2 &P) const;

	trf2 operator*(const trf2 &T) const;
	trf2 operator/(const trf2 &T) const{return T.inv()*(*this);}
	trf2 operator*=(const trf2 &T){return *this=*this*T;}
	trf2 operator/=(const trf2 &T){return *this=*this/T;}

	operator arr::darr2() const;

//
	double &operator()(const size_t i,const size_t j){return _p[i][j];}
	double const &operator()(const size_t i,const size_t j) const{return _p[i][j];}

	trf2 T() const;
	trf2 inv() const;
	static constexpr const trf2 ident(){const double x[2][2]={{1.,0.},{0.,1.}};return trf2(x);}

	friend trf2 operator*(double x,const trf2 &T);
	friend trf2 operator/(double x,const trf2 &T);

	static const trf2 To;

};

#endif

