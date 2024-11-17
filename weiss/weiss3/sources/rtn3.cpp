//3-D rotations - P. Ahrenkiel

#include <cstdlib>
#include <math.h>

#include "tlbx.hpp"
#include "arr.hpp"
#include "weiss3.hpp"

using namespace std;

const Rtn3 Rtn3::Ro(Vtr3::Vz,0.);

//
Rtn3::Rtn3(const Vtr3 &V0,const Vtr3 &V1,const Vtr3 &V2):Trf3()
{
	Vtr3 V[3];
	
	V[0]=(V1.cross(V2)).norm();
	V[1]=(V2.cross(V0)).norm();
	V[2]=(V0.cross(V1)).norm();
	for(size_t i=0;i<3;i++)
		for(size_t j=0;j<3;j++)
			_p[i][j]=V[j](i);
}

//
Rtn3::Rtn3(const Vtr3 &V,const double angle):Trf3()
{
	Vtr3 u[3];
	if(V.len()>0.)
	{
		u[2]=V.norm();
		u[1]=u[2].cross(Vtr3::Vx);
		u[0]=u[1].cross(u[2]);
		if((u[1].len()==0.)||(u[0].len()==0.))
		{
			u[0]=Vtr3::Vy.cross(u[2]);
			u[1]=u[2].cross(u[0]);
		}
		Rtn3 R(u[0],u[1],u[2]);
		
		Vtr3 up[3];
		up[0]=cos(angle)*Vtr3::Vx+sin(angle)*Vtr3::Vy;
		up[1]=-sin(angle)*Vtr3::Vx+cos(angle)*Vtr3::Vy;
		up[2]=Vtr3::Vz;
		Rtn3 Rp(up[0],up[1],up[2]);		
		*this=R*Rp*(R.inv());
	}
	else
	{
		*this=Trf3::ident();
	}
}

//
Rtn3::Rtn3(const Vtr3 &V,const Vtr3 &Vp):Trf3()
{
	double Lprod=V.len()*Vp.len();
	if(Lprod>0.)
	{
		double angle=acos(V.dot(Vp)/Lprod);
		Vtr3 axisV=V.cross(Vp)/Lprod;
		if(axisV.len()>0.)
			*this=Rtn(axisV,angle);
		else
			*this=Trf3::ident();
	}
}

//
Rtn3::Rtn3(const double theta,const double phi,const double rho):Trf3()
{
	*this=Rtn(Vtr::Vz,phi)*Rtn3(Vtr3::Vy,theta)*Rtn(Vtr::Vz,rho);
}

//
Rtn3::Rtn3(const VtrDir &dir):Trf3()
{
	Vtr3 axisY=dir._axisZ.cross(dir._axisX);
	Rtn3 R_rho(dir._axisZ,dir._rho);
	Rtn3 R_theta(axisY,dir._theta);
	Rtn3 R_phi(dir._axisZ,dir._phi);
	*this=R_phi*R_theta*R_rho;
}

