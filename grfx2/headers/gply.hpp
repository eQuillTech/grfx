//graphics polygons - P. Ahrenkiel

#ifndef _GPLY_
#define _GPLY_

#include "CoreGraphics/CoreGraphics.h"


#include "gfgr.h"
#include "gpnt.h"

class gply:public gfgr,public gpnt_arr1
{
private:
	
public:
	gply(const std::size_t N0=0,gpnt* a=NULL);
	gply(const gpnt_arr1& points);

	gply(const gfrm  &f);//copy constructor
	~gply(){}

	double top() const;
	double left() const;
	double bottom() const;
	double right() const;
		
	bool operator==(const gply &p) const;
	
	gply operator+(const gvtr &v) const;
	gply operator-(const gvtr &v) const;
	gply operator/(double x) const;

	gply operator+=(const gvtr &v);
	gply operator-=(const gvtr &v);
	gply operator*=(double x);
	gply operator/=(double x);
	
	gply map(const gfrm &fNew,const gfrm &fOld) const;
	bool isIn(const gpnt &f) const;

	void trace(CGContextRef context,const CGRect &Rframe,const gfrm &frameF) const;
	
	void doFill(CGContextRef context,const CGRect &Rframe,const gfrm &frameF) const override;
	void doStroke(CGContextRef context,const CGRect &Rframe,const gfrm &frameF) const override;

	//
	gpnt center() const;
	gpnt topLeft() const;
	gpnt topRight() const;
	gpnt bottomLeft() const;
	gpnt bottomRight() const;

	double width() const{return fabs(right()-left());}
	double height() const{return fabs(top()-bottom());}

	double area() const;
	bool isCCW() const;
	bool isConvex() const;
	gpnt closestPoint(const gpnt &p,glne &Lclose) const;
	gpnt closestPoint(const gpnt &p) const;
	bool intersection(const glne &L,gpnt &Pint,glne &Lint) const;
	bool intersection(const glne &L,glne &Lint) const;
	gvtr normal(const glne &AB) const;
	double distTo(const gpnt &C) const;
	friend double width(const gply &P){return P.width();}
	friend double height(const gply &P){return P.height();}

	friend std::ostream& operator<<(std::ostream &os,const gply &P);
};

bool triangleIsCCW(gpnt pA,gpnt pB,gpnt pC);
double triangleArea(gpnt pA,gpnt pB,gpnt pC);

typedef arr::arr1<gply> gply_arr1;
//extern const gply nullPly;

#endif
