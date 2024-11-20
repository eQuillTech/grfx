//3-D vectors - P. Ahrenkiel

#ifndef _VTR3_
#define _VTR3_

#include <simd/simd.h>

#include "arr.hpp"

#ifndef _CRD3_
#include "crd3.hpp"
#endif

class pnt3;
class trf3;
class atr3;
class VtrDir;

//
class vtr3:public crd3
{
private:
	explicit vtr3(const crd3 &C):crd3(C){}
	
public:
	constexpr vtr3():crd3(){}
	constexpr vtr3(double x,double y,double z):crd3(x,y,z){}
	constexpr vtr3(const double x[3]):crd3(x){}
	vtr3(const arr::darr1 &A):crd3(A){}
	vtr3(const vtr3 &V):crd3(V){}
	vtr3(const VtrDir &dir);
	
	vtr3 operator+() const{return *this;}
	vtr3 operator-() const{return vtr3(-_x,-_y,-_z);}
	
	vtr3 operator+(const vtr3 &V) const{return vtr3(_x+V.x(),_y+V.y(),_z+V.z());}
	vtr3 operator-(const vtr3 &V) const{return vtr3(_x-V.x(),_y-V.y(),_z-V.z());}

	bool operator==(const vtr3  &V) const;
	bool operator!=(const vtr3  &V) const;

	vtr3 operator+=(const vtr3 &V){return *this=(*this)+V;}
	vtr3 operator-=(const vtr3 &V){return *this=(*this)-V;}
	vtr3 operator*=(double x){return *this=x*(*this);}
	vtr3 operator/=(double x){return *this=(*this)/x;}

	double& x(){return _x;}
	double& y(){return _y;}
	double& z(){return _z;}
	
	double const& x() const{return _x;}
	double const& y() const{return _y;}
	double const& z() const{return _z;}

	double dot(const vtr3 &V) const{return _x*V._x+_y*V._y+_z*V._z;}
	vtr3 cross(const vtr3 &V) const;

	double operator*(const vtr3 &v) const{return dot(v);}
	vtr3 operator/(double x) const{return arr::darr1(*this)/x;}

	inline double sqrlen() const{return crd3::sqrlen();}
	inline double len() const{return crd3::len();}
	vtr3 norm() const{return (*this)/len();}

	friend std::ostream& operator<<(std::ostream &os,const vtr3 &V);
	friend vtr3 operator*(double x,const vtr3 &V){return vtr3(x*V._x,x*V._y,x*V._z);}

	vtr3 operator/(const trf3 &T);

//predef
	vtr3 operator*=(const trf3 &T);

	static const vtr3 Vo,Vx,Vy,Vz;
	
	operator simd::float3();
};
 
inline double dot(const vtr3 &V1,const vtr3 &V2){return V1.dot(V2);}
inline vtr3 cross(const vtr3 &V1,const vtr3 &V2){return V1.cross(V2);}
inline double len(const vtr3 &V){return V.len();}
inline vtr3 norm(const vtr3 &V){return V.norm();}

//
struct VtrDir
{
	vtr3 _axisZ=vtr3::Vz;
	vtr3 _axisX=vtr3::Vx;
	double _theta=0.;
	double _phi=0.;
	double _rho=0.;
	
	VtrDir():_theta(0.),_phi(0.),_rho(0.),_axisZ(vtr3::Vz),_axisX(vtr3::Vx){}
	VtrDir(const vtr3 &Vz,const vtr3 &Vx,const double theta,const double phi,const double rho):_theta(theta),_phi(phi),_rho(rho),_axisZ(Vz),_axisX(Vx){}
	
	static const VtrDir Dir0;
};

#endif
