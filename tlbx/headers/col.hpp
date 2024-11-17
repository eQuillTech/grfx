//colors - P. Ahrenkiel

#ifndef _COL_
#define _COL_

class colRGB
{
protected:
	float _red,_green,_blue;

public:
	colRGB():_red(0),_green(0),_blue(0){}
	colRGB(const float r,const float g,const float b):_red(r),_green(g),_blue(b){}

	float& red(){return _red;}
	float& green(){return _green;}
	float& blue(){return _blue;}

	float red() const{return _red;}
	float green() const{return _green;}
	float blue() const{return _blue;}

	colRGB operator+(const colRGB& c) const;
	colRGB operator-(const colRGB& c) const;
	colRGB operator/(const float x) const;
	friend colRGB operator*(const float x,const colRGB& c);

	static const colRGB Black;
	static const colRGB White;
	static const colRGB Red;
	static const colRGB Green;
	static const colRGB Blue;
	static const colRGB Yellow;
	static const colRGB Magenta;
	static const colRGB Cyan;
	
};

//
class col:public colRGB
{
private:
	float _alpha;

public:
	col():colRGB(),_alpha(1){}
	col(const float r,const float g,const float b,const float a=1.0):colRGB(r,g,b),_alpha(a){}
	col(const colRGB &crgb,const float a=1.0):colRGB(crgb),_alpha(a){}
	
	col operator+(const col& c) const;
	col operator-(const col& c) const;
	
	float& alpha(){return _alpha;}
	float alpha() const{return _alpha;}

	col operator/(const float x) const;
	friend col operator*(const float x,const col& c);
};

#endif

