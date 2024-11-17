// math - P. Ahrenkiel

#ifndef _MTH_
#define _MTH_

#include <cstdlib>
#include <math.h>

namespace mth {

inline double sqr(const double x){return x*x;}
inline double sgn(const double x){return (x>0.)?1.:(x<0.)?-1.:0.;}
inline double sgnp(const double x){return (x>0.)?1.:(x<0.)?-1.:1.;}
inline double pwr(const double x,const std::size_t y){return pow(x,y);}
inline double pwr(const double x,const int y){return pow(x,y);}
inline double pwr(const double x,const double y){return pow(x,y);}
inline double logy(const double x,const double y){return log(fabs(x))/log(y);}
inline std::size_t cyc(std::size_t i){while(i>2)i-=3;return i;}
inline std::size_t cyc(std::size_t i, const std::size_t N){while(!(i<N))i-=N;return i;}
inline double Kdelta(std::size_t i, std::size_t j){return (i==j)?1.:0.;}
inline double dexp(const double x){return exp(x);}
inline double dmod(double x,double y){return x-y*floor(x/y);}
inline int mod(const int x,const int y){return (x>=0)?x%y:(y-(-x)%y)%y;}
inline double rndom(){return 1./(RAND_MAX+1.)*rand();}

double roundoff(const double x);
double magsqr(double *x,const size_t N);

} // namespace mth

#endif
