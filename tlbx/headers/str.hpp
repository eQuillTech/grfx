//strings - P. Ahrenkiel

#ifndef _STR_
#define _STR_
#include <iostream>
 
class str:public std::string
{
private:
	
public:
	str():std::string(){}
	str(const std::string &s):std::string(s){}
	str(const char *c):std::string(c){}
	str(const char &c);
	str(const double Num,const int nDig);
	str(const float Num,const int nDig);
	str(const long Num);
	str(const int Num);
	str(const int Num,const int nDig);
	
	char *schar() const;
	char *schar(size_t n,size_t pos=0) const;

	str mid(const short pos,const short slen);
	str left(const short slen);
	str right(const short slen);
	bool contains(const str s,short *pos);
	bool containsRight(const str s,short *pos);
	str allcaps();
	
	short len() const;
	void find(str &s,const char delim,const short occurence);
	void find(int &i,const char delim,const short occurence);
	void find(float &f,const char delim,const short occurence);
	
	bool operator==(const char *c);
	str operator+(const str &s);
	str operator+=(const str &s);
	
	int sint();
	float sfloat();
	
	friend std::istream& operator >>(std::istream &is,str &s);
	friend std::ostream& operator <<(std::ostream &os,const str &s);
};

extern const str null_str;
#endif
