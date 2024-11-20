// array examples - P. Ahrenkiel (2024)

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "tlbx.hpp"

#include "arr.hpp"

namespace examples {
 
void example1(){

	arr::darr1 d1({1,2,3});
	std::cout<<d1<<"\n";

	arr::darr2 d2({{4,5,6},{1,7,2,3}});
	std::cout<<d2<<"\n";
	
	arr::darr2 M=arr::darr2::zero(5,6);
	for(std::size_t i=0;i<M.size(0);++i)
		for(std::size_t j=0;j<M.size(1);++j)
			M(i,j)=mth::rndom();
	
	std::cout<<M.rowEschelon()<<"\n";
	
	arr::darr2 V;
	arr::darr2 S=(M*M.T()).diagSymm(V);
	std::cout<<S<<"\n";
	std::cout<<V<<"\n";
	
	M(1,0,1,3)=0.;
	std::cout<<M<<"\n";

	for(size_t i=0;i<M.size(0);i++)
	{
		M.row(i)=i;
		arr::darr1 C=M.row(i);

		std::cout<<"M:\n"<<M<<"\n";
		std::cout<<"C:\n"<<C<<"\n";
	}
}
	
} // namespace examples


int main(int /*argc*/, char* /*argv*/[])
{
	examples::example1();
	return 0;
}
