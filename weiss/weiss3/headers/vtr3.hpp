//3-D vectors - P. Ahrenkiel

#ifndef _VTR3_
#define _VTR3_

#include <simd/simd.h>

#include "arr.hpp"

#ifndef _CRD3_
#include "Crd3.hpp"
#endif

class Pnt3;
class Trf3;
class Atr3;
class VtrDir;

//
class Vtr3:public Crd3
{
private:
	explicit Vtr3(const Crd3 &C):Crd3(C){}
	
public:
	constexpr Vtr3():Crd3(){}
	constexpr Vtr3(double x,double y,double z):Crd3(x,y,z){}
	constexpr Vtr3(const double x[3]):Crd3(x){}
	Vtr3(const arr::darr1 &A):Crd3(A){}
	Vtr3(const Vtr3 &V):Crd3(V){}
	Vtr3(const VtrDir &dir);
	
	Vtr3 operator+() const{return *this;}
	Vtr3 operator-() const{return Vtr3(-_x,-_y,-_z);}
	
	Vtr3 operator+(const Vtr3 &V) const{return Vtr3(_x+V.x(),_y+V.y(),_z+V.z());}
	Vtr3 operator-(const Vtr3 &V) const{return Vtr3(_x-V.x(),_y-V.y(),_z-V.z());}

	bool operator==(const Vtr3  &V) const;
	bool operator!=(const Vtr3  &V) const;

	Vtr3 operator+=(const Vtr3 &V){return *this=(*this)+V;}
	Vtr3 operator-=(const Vtr3 &V){return *this=(*this)-V;}
	Vtr3 operator*=(double x){return *this=x*(*this);}
	Vtr3 operator/=(double x){return *this=(*this)/x;}

	double& x(){return _x;}
	double& y(){return _y;}
	double& z(){return _z;}
	
	double const& x() const{return _x;}
	double const& y() const{return _y;}
	double const& z() const{return _z;}

	double dot(const Vtr3 &V) const{return _x*V._x+_y*V._y+_z*V._z;}
	Vtr3 cross(const Vtr3 &V) const;

	double operator*(const Vtr3 &v) const{return dot(v);}
	Vtr3 operator/(double x) const{return arr::darr1(*this)/x;}

	inline double sqrlen() const{return Crd3::sqrlen();}
	inline double len() const{return Crd3::len();}
	Vtr3 norm() const{return (*this)/len();}

	friend std::ostream& operator<<(std::ostream &os,const Vtr3 &V);
	friend Vtr3 operator*(double x,const Vtr3 &V){return Vtr3(x*V._x,x*V._y,x*V._z);}

	Vtr3 operator/(const Trf3 &T);

//predef
	Vtr3 operator*=(const Trf3 &T);

	static const Vtr3 Vo,Vx,Vy,Vz;
	
	operator simd::float3();
};
 
inline double dot(const Vtr3 &V1,const Vtr3 &V2){return V1.dot(V2);}
inline Vtr3 cross(const Vtr3 &V1,const Vtr3 &V2){return V1.cross(V2);}
inline double len(const Vtr3 &V){return V.len();}
inline Vtr3 norm(const Vtr3 &V){return V.norm();}

//
struct VtrDir
{
	Vtr3 _axisZ=Vtr3::Vz;
	Vtr3 _axisX=Vtr3::Vx;
	double _theta=0.;
	double _phi=0.;
	double _rho=0.;
	
	VtrDir():_theta(0.),_phi(0.),_rho(0.),_axisZ(Vtr3::Vz),_axisX(Vtr3::Vx){}
	VtrDir(const Vtr3 &Vz,const Vtr3 &Vx,const double theta,const double phi,const double rho):_theta(theta),_phi(phi),_rho(rho),_axisZ(Vz),_axisX(Vx){}
	
	static const VtrDir Dir0;
};

#endif
