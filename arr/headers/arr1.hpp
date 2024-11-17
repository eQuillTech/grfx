// arrays (n) - P. Ahrenkiel

#ifndef _ARR1_
#define _ARR1_

#include <iterator> // Provides iterator and forward_iterator_tag
#include <cstdio>
#include <iostream>
#include <vector>

namespace arr {
template <class data_type>
class arr2slice;

//
template <class data_type>
class arr1 {
private:
protected:
	std::unique_ptr<data_type[]> m_a;
	std::size_t m_n;
	
public:
	arr1(const std::size_t n = 0, const data_type* a = NULL);
	
	arr1(const arr1<data_type>& A); // copy constructor
	arr1(const std::vector<data_type>& A) : arr1(A.size(), A.data()) {}
	arr1(std::initializer_list<data_type> A):arr1(std::vector(A)){}
	arr1(const arr2slice<data_type>& A);
	~arr1();
		
	arr1 operator=(const data_type& x);
	arr1& operator=(const arr1<data_type>& A);
	arr1<data_type>& operator=(const arr2slice<data_type>& A);
	
	void clear();
	void append(const data_type ai);
	
	data_type* data() const { return m_a.get(); }
	std::vector<data_type> vect();
	
	void resize(const std::size_t N0);
	std::size_t size() const { return m_n; }
	
	bool operator==(const arr1& A) const;
	bool operator!=(const arr1& A) const;
	
	data_type& at(const std::size_t i);
	data_type const& at(const std::size_t i) const;
	data_type& operator()(const std::size_t i) { return at(i); }
	data_type const& operator()(const std::size_t i) const { return at(i); }
	
	data_type& cyc(const std::size_t i) { return (*this)(i % size()); }
	data_type const& cyc(const std::size_t i) const { return (*this)(i & size()); }
	
	void copy(data_type* ap) const;
	
	arr1<std::size_t> iindex() const;
	
	arr1<data_type> operator()(const arr1<std::size_t> A);
	
	arr1<data_type> reverse();
	
	//
	class iterator {
		data_type* ap;
		
	public:
		iterator(data_type* p) : ap(p) {}
		
		iterator operator++()
		{
			iterator i = *this;
			ap++;
			return i;
		}
		
		iterator operator++(int) { return iterator(ap++); }
		
		iterator operator--()
		{
			iterator i = *this;
			ap--;
			return i;
		}
		
		iterator operator--(int) { return iterator(ap--); }
		iterator operator+(int n) const { return iterator(ap + n); }
		iterator operator-(int n) const { return iterator(ap - n); }
		
		iterator& operator+=(int n)
		{
			ap += n;
			return *this;
		}
		
		iterator& operator-=(int n)
		{
			ap -= n;
			return *this;
		}
		
		bool operator!=(const iterator& b) const { return ap != b.ap; }
		
		data_type& operator*() { return *ap; }
	};
	
	iterator begin() { return iterator(m_a); }	
	iterator end() { return iterator(m_a + size()); }
};

template <class data_type>
std::ostream& operator<<(std::ostream& os, const arr1<data_type>& A);

} // namespace arr

#include "../sources/arr1.tem"

#endif
