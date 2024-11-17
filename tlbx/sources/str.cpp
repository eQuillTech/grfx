//strings - P. Ahrenkiel

#include <cstdlib>
#include <string>
#include <math.h>

#include "mth.hpp"
#include "str.hpp"

const str null_str;

//
str::str(const char &c):std::string()
{
	char cp[2];
	cp[0]=c;
	cp[1]='\0';
	*this=str(cp);
}

//
str::str(const double Num,const int nDig):std::string()
{
	(std::string)(*this)="";
	if(Num<0)
		*this=str("-");
	
	int nMag=0;

	double  pDig=mth::pwr(10.,nDig);
	double nRem=fabs(Num);
	if(nRem>0.)nMag=(int)log10(nRem);
	if(nMag<0)nMag=0;


	for(int i=nMag;i>=-nDig;i--){

		double p=mth::pwr(10.,(double)i);

		double tVal=mth::roundoff(nRem*pDig)/pDig;
		int nVal=(int)(tVal/p+1./pDig/10.);

		char c=(char)(nVal+(int)'0');/*ascii*/
		if(((int)c>=(int)'0')&&((int)c<=(int)'9'))
			(*this)+=c;

		if((i==0)&&(nDig>0))
			(*this)+=".";/*decimal point*/

		double dVal=mth::roundoff(nRem*pDig);
		double dpVal=mth::roundoff(nVal*p*pDig);
		nRem=(dVal-dpVal)/pDig;
		}
	}
	
//
str::str(const float Num,const int nDig):std::string()
{
	(*this)=str((double)Num,nDig);
}
	
//
str::str(const long Num):std::string()
{
	int nVal;
	if(Num<0)
		(*this)=str("-");
	
	int nMag=0;
	double nRem=fabs(Num);
	if(nRem>0.)nMag=(int)log10(nRem);
		
	if(nMag<0)nMag=0;
	
	for(int i=nMag;i>=0;i--){

		nVal=(int)(nRem/pow(10.,(double)i));
		nRem=nRem-nVal*pow(10.,(double)i);

		char c=(char)(nVal+(int)'0');/*ascii*/
		if((int(c)>=(int)'0')&&(int(c)<=(int)'9'))
			(*this)+=str(c);

		}
}
	
//
str::str(const int Num):std::string()
{
	(*this)=str((long)Num);
}
	
//
str::str(int Num,int nDig):std::string()
{
	(*this)=str(Num);
	while(len()<nDig)
		(std::string)(*this)="0"+(std::string)(*this);
}
	
//
str str::operator+(const str &s)
{
	return (std::string)(*this)+(std::string)s;
}

//
str str::operator+=(const str &s)
{
	return *this=(*this)+s;
}

//
short str::len() const
{
	return size();
}
			
//
char *str::schar(size_t n,size_t pos) const
{
	//copy(c,Lp,pos1);
	size_t L=size();
	size_t pos1=pos;
	size_t pos2=pos+n;

	if(pos1>L-1)
		return NULL;

	if(pos2>L-1)pos2=L-1;
	
	size_t Lp=pos2-pos1+1;
	char *c=new char[Lp+1];
	copy(c,Lp,pos1);
	c[Lp]='\0';
	return c;
}

//
bool str::operator==(const char *c)
{
	return (*this)==str(c);
}

//
char *str::schar() const
{
	return schar(len(),0);
}

//
str str::mid(const short pos,const short slen)
{
	short l=len();
	str res;
	
	short i;
	for(i=pos;(i<pos+slen)&&(i<l);++i)
	{
		char c=(*this)[i];
		res+=c;
	}
	return res;
}

/*
*/
str str::left(const short slen)
{
	return mid(0,slen);
}

//
str str::right(const short slen)
{
	int l=len();
	return mid(l-slen,slen);
}

//
bool str::contains(const str s,short *pos)
{
	short l=s.len();
	short l0=len();
	short i;
	for(i=0;i<l0-l;++i)
	{
		str ssub=mid(i,l);
		if(ssub==s)
		{
			*pos=i;
			return true;
		}
	}
	return false;
}

//
bool str::containsRight(const str s,short *pos)
{
	short l=s.len();
	short l0=len();
	short i;
	for(i=0;i<l0-l;i++)
	{
		short j=(l0-l)-i-1;
		str ssub=mid(j,l);
		if(ssub==s)
		{
			*pos=j;
			return true;
		}
	}
	return false;
}

//
str str::allcaps()
{
	str scap=*this;
	std::size_t L=size();
	for(std::size_t i=0; i<L; i++)
	{
		char c=(*this)[i+1];
		if(('a'<=c)&&(c<='z'))
			c-=(short)'a'-(short)'A';
		scap[i+1]=c;
	}
	return scap;
}

//
void str::find(str &s,const char delim,const short occurence)
{
	size_t L=size();
	
	short jocc=0;
	for(std::size_t i=0;i<L;++i)
	{
		str sc=mid(i,1);
		if(sc==str(delim))
		{
			++jocc;
			if(jocc==occurence)
				break;
			else
				s=str('\0');
		}
		else
			s+=sc;
	}
}

//
void str::find(int &i,const char delim,const short occurence)
{
	str S;
	find(S,delim,occurence);
	i=S.sint();
}

//
void str::find(float &f,const char delim,const short occurence)
{
	str S;
	find(S,delim,occurence);
	f=S.sfloat();
}

//
int str::sint()
{
	return atoi(c_str());
}
	
//
float str::sfloat()
{
	return atof(c_str());
}

//
std::istream& operator>>(std::istream &is,str &s)
{
	is>>(std::string &)(s);
	return is;
}

//
std::ostream& operator<<(std::ostream &os,const str &s)
{
	os<<static_cast<std::string>(s);
	return os;
}

