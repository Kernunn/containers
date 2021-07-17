#include <vector>
#include "vector.hpp"
#include "test_runner.h"

template<typename T>
bool operator==(const std::vector<T> &lhs, const ft::vector<T> &rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	typename std::vector<T>::const_iterator left = lhs.begin();
	typename ft::vector<T>::const_iterator right = rhs.begin();
	while (left != lhs.end())
	{
		if (*left == *right)
		{
			++left;
			++right;
			continue;
		}
		return (false);
	}
	return (true);
}

static void	TestMemberType()
{
	{
		std::vector<int> v(4, 100);
		ft::vector<int> ft_v(4, 100);

		std::vector<int>::value_type tmp1 = 8;
		ft::vector<int>::value_type tmp2 = 8;
		ASSERT_EQUAL(tmp1, tmp2)

		std::vector<int>::reference tmp3 = tmp1;
		ft::vector<int>::reference tmp4 = tmp2;
		ASSERT_EQUAL(tmp3, tmp4)

		std::vector<int>::const_reference tmp5 = tmp1;
		ft::vector<int>::const_reference tmp6 = tmp1;
		ASSERT_EQUAL(tmp5, tmp6)

		tmp3 = 5;
		tmp4 = 5;
		ASSERT_EQUAL(tmp1, tmp2)

		std::vector<int>::pointer tmp7 = &tmp1;
		ft::vector<int>::pointer tmp8 = &tmp2;
		ASSERT_EQUAL(*tmp7, *tmp8)
		*tmp7 = 9;
		*tmp8 = 9;
		ASSERT_EQUAL(tmp1, tmp2)

		std::vector<int>::const_pointer tmp9 = &tmp1;
		ft::vector<int>::const_pointer tmp10 = &tmp2;
		ASSERT_EQUAL(*tmp9, *tmp10)


		std::vector<int>::iterator it;
		ft::vector<int>::iterator ft_it;
		it = v.begin();
		ft_it = ft_v.begin();
		ASSERT_EQUAL(*it, *ft_it)

		it[0] = 5;
		it[1] = 8;
		it[2] = 9;
		it[3] = 10;
		ft_it[0] = 5;
		ft_it[1] = 8;
		ft_it[2] = 9;
		ft_it[3] = 10;
		std::vector<int>::iterator it1(it);
		ft::vector<int>::iterator ft_it1(ft_it);
		ASSERT_EQUAL(*it1, *ft_it1)

		ASSERT_EQUAL((it == it1), (ft_it == ft_it1))
		ASSERT_EQUAL((it != it1), (ft_it != ft_it1))

		ASSERT_EQUAL(*it.operator->(), *ft_it.operator->())
		*it = 6;
		*ft_it = 6;
		ASSERT_EQUAL(v, ft_v)
		++it;
		++ft_it;
		ASSERT_EQUAL(*it, *ft_it)
		it++;
		ft_it++;
		ASSERT_EQUAL(*it, *ft_it)
		*it++;
		*ft_it++;
		ASSERT_EQUAL(*it, *ft_it)
		ASSERT_EQUAL(v, ft_v)
		--it;
		--ft_it;
		ASSERT_EQUAL(*it, *ft_it)
		it--;
		ft_it--;
		ASSERT_EQUAL(*it, *ft_it)
		*it--;
		*ft_it--;
		ASSERT_EQUAL(*it, *ft_it)
		ASSERT_EQUAL(v, ft_v)

		ASSERT_EQUAL(*(it + 2), *(ft_it + 2))
		ASSERT_EQUAL(*(2 + it), *(2 + ft_it))

		it += 2;
		ft_it += 2;
		ASSERT_EQUAL(*it, *ft_it)
		it -= 1;
		ft_it -= 1;
		ASSERT_EQUAL(*it, *ft_it)

		ASSERT_EQUAL(*(it - 1), *(ft_it - 1))
		ASSERT_EQUAL(it - it1, ft_it - ft_it1)

		it[2] = 2;
		ft_it[2] = 2;
		ASSERT_EQUAL(v, ft_v)

		ASSERT_EQUAL((it < it1), (ft_it < ft_it1))
		ASSERT_EQUAL((it > it1), (ft_it > ft_it1))
		ASSERT_EQUAL((it <= it1), (ft_it <= ft_it1))
		ASSERT_EQUAL((it >= it1), (ft_it >= ft_it1))
	}
	{
		std::vector<int> v(4, 100);
		ft::vector<int> ft_v(4, 100);

		std::vector<int>::const_iterator it;
		ft::vector<int>::const_iterator ft_it;
		it = v.begin();
		ft_it = ft_v.begin();
		ASSERT_EQUAL(*it, *ft_it)

		std::vector<int>::const_iterator it1(it);
		ft::vector<int>::const_iterator ft_it1(ft_it);
		ASSERT_EQUAL(*it1, *ft_it1)

		ASSERT_EQUAL((it == it1), (ft_it == ft_it1))
		ASSERT_EQUAL((it != it1), (ft_it != ft_it1))

		ASSERT_EQUAL(*it.operator->(), *ft_it.operator->())
//		*it = 6;
//		*ft_it = 6;
		ASSERT_EQUAL(v, ft_v)
		++it;
		++ft_it;
		ASSERT_EQUAL(*it, *ft_it)
		it++;
		ft_it++;
		ASSERT_EQUAL(*it, *ft_it)
		*it++;
		*ft_it++;
		ASSERT_EQUAL(*it, *ft_it)
		ASSERT_EQUAL(v, ft_v)
		--it;
		--ft_it;
		ASSERT_EQUAL(*it, *ft_it)
		it--;
		ft_it--;
		ASSERT_EQUAL(*it, *ft_it)
		*it--;
		*ft_it--;
		ASSERT_EQUAL(*it, *ft_it)
		ASSERT_EQUAL(v, ft_v)

		ASSERT_EQUAL(*(it + 2), *(ft_it + 2))
		ASSERT_EQUAL(*(2 + it), *(2 + ft_it))

		it += 2;
		ft_it += 2;
		ASSERT_EQUAL(*it, *ft_it)
		it -= 1;
		ft_it -= 1;
		ASSERT_EQUAL(*it, *ft_it)

		ASSERT_EQUAL(*(it - 1), *(ft_it - 1))
		ASSERT_EQUAL(it - it1, ft_it - ft_it1)

//		it[2] = 2;
//		ft_it[2] = 2;
		ASSERT_EQUAL(v, ft_v)

		ASSERT_EQUAL((it < it1), (ft_it < ft_it1))
		ASSERT_EQUAL((it > it1), (ft_it > ft_it1))
		ASSERT_EQUAL((it <= it1), (ft_it <= ft_it1))
		ASSERT_EQUAL((it >= it1), (ft_it >= ft_it1))
	}
	{
		std::vector<int> v(4, 100);
		ft::vector<int> ft_v(4, 100);

		std::vector<int>::reverse_iterator it;
		ft::vector<int>::reverse_iterator ft_it;
		it = v.rbegin();
		ft_it = ft_v.rbegin();
		ASSERT_EQUAL(*it, *ft_it)
		it[0] = 5;
		it[1] = 8;
		it[2] = 9;
		it[3] = 10;
		ft_it[0] = 5;
		ft_it[1] = 8;
		ft_it[2] = 9;
		ft_it[3] = 10;

		std::vector<int>::reverse_iterator it1(it);
		ft::vector<int>::reverse_iterator ft_it1(ft_it);
		ASSERT_EQUAL(*it1, *ft_it1)

		ASSERT_EQUAL((it == it1), (ft_it == ft_it1))
		ASSERT_EQUAL((it != it1), (ft_it != ft_it1))

		ASSERT_EQUAL(*it.operator->(), *ft_it.operator->())
		*it = 6;
		*ft_it = 6;
		ASSERT_EQUAL(v, ft_v)
		++it;
		++ft_it;
		ASSERT_EQUAL(*it, *ft_it)
		it++;
		ft_it++;
		ASSERT_EQUAL(*it, *ft_it)
		*it++;
		*ft_it++;
		ASSERT_EQUAL(*it, *ft_it)
		ASSERT_EQUAL(v, ft_v)
		--it;
		--ft_it;
		ASSERT_EQUAL(*it, *ft_it)
		it--;
		ft_it--;
		ASSERT_EQUAL(*it, *ft_it)
		*it--;
		*ft_it--;
		ASSERT_EQUAL(*it, *ft_it)
		ASSERT_EQUAL(v, ft_v)

		ASSERT_EQUAL(*(it + 2), *(ft_it + 2))
		ASSERT_EQUAL(*(2 + it), *(2 + ft_it))

		it += 2;
		ft_it += 2;
		ASSERT_EQUAL(*it, *ft_it)
		it -= 1;
		ft_it -= 1;
		ASSERT_EQUAL(*it, *ft_it)

		ASSERT_EQUAL(*(it - 1), *(ft_it - 1))
		ASSERT_EQUAL(it - it1, ft_it - ft_it1)

		it[2] = 2;
		ft_it[2] = 2;
		ASSERT_EQUAL(v, ft_v)

		ASSERT_EQUAL((it < it1), (ft_it < ft_it1))
		ASSERT_EQUAL((it > it1), (ft_it > ft_it1))
		ASSERT_EQUAL((it <= it1), (ft_it <= ft_it1))
		ASSERT_EQUAL((it >= it1), (ft_it >= ft_it1))
	}
	{
		std::vector<int> v(4, 100);
		ft::vector<int> ft_v(4, 100);

		std::vector<int>::const_reverse_iterator it;
		ft::vector<int>::const_reverse_iterator ft_it;
		it = v.rbegin();
		ft_it = ft_v.rbegin();
		ASSERT_EQUAL(*it, *ft_it)

		std::vector<int>::const_reverse_iterator it1(it);
		ft::vector<int>::const_reverse_iterator ft_it1(ft_it);
		ASSERT_EQUAL(*it1, *ft_it1)

		ASSERT_EQUAL((it == it1), (ft_it == ft_it1))
		ASSERT_EQUAL((it != it1), (ft_it != ft_it1))

		ASSERT_EQUAL(*it.operator->(), *ft_it.operator->())
	//	*it = 6;
	//	*ft_it = 6;
		ASSERT_EQUAL(v, ft_v)
		++it;
		++ft_it;
		ASSERT_EQUAL(*it, *ft_it)
		it++;
		ft_it++;
		ASSERT_EQUAL(*it, *ft_it)
		*it++;
		*ft_it++;
		ASSERT_EQUAL(*it, *ft_it)
		ASSERT_EQUAL(v, ft_v)
		--it;
		--ft_it;
		ASSERT_EQUAL(*it, *ft_it)
		it--;
		ft_it--;
		ASSERT_EQUAL(*it, *ft_it)
		*it--;
		*ft_it--;
		ASSERT_EQUAL(*it, *ft_it)
		ASSERT_EQUAL(v, ft_v)

		ASSERT_EQUAL(*(it + 2), *(ft_it + 2))
		ASSERT_EQUAL(*(2 + it), *(2 + ft_it))

		it += 2;
		ft_it += 2;
		ASSERT_EQUAL(*it, *ft_it)
		it -= 1;
		ft_it -= 1;
		ASSERT_EQUAL(*it, *ft_it)

		ASSERT_EQUAL(*(it - 1), *(ft_it - 1))
		ASSERT_EQUAL(it - it1, ft_it - ft_it1)

	//	it[2] = 2;
	//	ft_it[2] = 2;
		ASSERT_EQUAL(v, ft_v)

		ASSERT_EQUAL((it < it1), (ft_it < ft_it1))
		ASSERT_EQUAL((it > it1), (ft_it > ft_it1))
		ASSERT_EQUAL((it <= it1), (ft_it <= ft_it1))
		ASSERT_EQUAL((it >= it1), (ft_it >= ft_it1))
	}
}

static void	TestConstructor()
{
	std::vector<int> first;                                // empty vector of ints
	ft::vector<int> ft_first;
	std::vector<int> second ((size_t)4,100);  // four ints with value 100
	ft::vector<int> ft_second ((size_t)4,100);
	std::vector<int> third (second.begin(),second.end());  // iterating through second
	ft::vector<int> ft_third (ft_second.begin(),ft_second.end());
	std::vector<int> fourth (third);                       // a copy of third
	ft::vector<int> ft_fourth (ft_third);

	ASSERT_EQUAL(first, ft_first);
	ASSERT_EQUAL(second, ft_second);
	ASSERT_EQUAL(third, ft_third);
	ASSERT_EQUAL(fourth, ft_fourth);

	// the const_iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,20};
	std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
	ft::vector<int> ft_fifth (myints, myints + sizeof(myints) / sizeof(int) );

	ASSERT_EQUAL(fifth, ft_fifth);

#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestConstructor--------\n";
	std::cout << "\033[0m";
	std::cout << "The contents of fifth are:";
	std::cout << fifth << '\n';
	std::cout << "The contents of ft_fifth are:";
	std::cout << ft_fifth << '\n';
#endif
}

static void	TestOperatorEqual()
{
	std::vector<int> foo (3,0);
	std::vector<int> bar (5,0);
	ft::vector<int> ft_foo (3,0);
	ft::vector<int> ft_bar (5,0);

	bar = foo;
	foo = std::vector<int>();
	ft_bar = ft_foo;
	ft_foo = ft::vector<int>();

	ASSERT_EQUAL(foo, ft_foo);
	ASSERT_EQUAL(bar, ft_bar);

	ASSERT_EQUAL(foo.size(), ft_foo.size());
	ASSERT_EQUAL(bar.size(), ft_bar.size());
#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestOperatorEqual--------\n";
	std::cout << "\033[0m";
	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of ft_foo: " << int(ft_foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';
	std::cout << "Size of ft_bar: " << int(ft_bar.size()) << '\n';
#endif
}

static void	TestIterators()
{
	{
		std::vector<int> myvector;
		ft::vector<int> ft_myvector;
		for (int i = 1; i <= 5; i++) myvector.push_back(i);
		for (int i = 1; i <= 5; i++) ft_myvector.push_back(i);

#ifdef PRINT
		std::cout << "\033[1;35m";
		std::cout << "\n--------TestIterators--------\n";
		std::cout << "\033[0m";
		std::cout << "myvector contains: ";
#endif
		for (std::vector<int>::iterator it = myvector.begin();
			 it != myvector.end(); ++it)
		{
#ifdef PRINT
			std::cout << ' ' << *it;
#endif
		}
#ifdef PRINT
		std::cout << "\n";
		std::cout << "ft_myvector contains: ";
#endif
		for (ft::vector<int>::iterator it = ft_myvector.begin();
			 it != ft_myvector.end(); ++it)
		{
#ifdef PRINT
			std::cout << ' ' << *it;
#endif
		}
	}
	{
		std::vector<int> myvector(5);  // 5 default-constructed ints
		ft::vector<int> ft_myvector(5);  // 5 default-constructed ints

		int i = 0;

		std::vector<int>::reverse_iterator rit = myvector.rbegin();
		ft::vector<int>::reverse_iterator ft_rit = ft_myvector.rbegin();
		for (; rit != myvector.rend(); ++rit)
			*rit = ++i;
		i = 0;
		for (; ft_rit != ft_myvector.rend(); ++ft_rit)
			*ft_rit = ++i;
		ASSERT_EQUAL(myvector, ft_myvector)

#ifdef PRINT
		std::cout << "\n";
		std::cout << "myvector contains:";
#endif
		for (std::vector<int>::iterator it = myvector.begin();
			 it != myvector.end(); ++it)
		{
#ifdef PRINT
			std::cout << ' ' << *it;
#endif
		}
#ifdef PRINT
		std::cout << "\n";
		std::cout << "ft_myvector contains:";
#endif
		for (ft::vector<int>::iterator it = ft_myvector.begin();
			 it != ft_myvector.end(); ++it)
		{
#ifdef PRINT
			std::cout << ' ' << *it;
#endif
		}
#ifdef PRINT
		std::cout << '\n';
#endif
	}
}

static void	TestCapacity()
{
	{
		std::vector<int> myints;
		ft::vector<int> ft_myints;
		ASSERT_EQUAL(myints.size(), ft_myints.size())
#ifdef PRINT
		std::cout << "\033[1;35m";
		std::cout << "\n--------TestCapacity--------\n";
		std::cout << "\033[0m";
		std::cout << "0a. size: " << myints.size() << '\n';
		std::cout << "0b. size: " << ft_myints.size() << '\n';
#endif
		for (int i=0; i<10; i++) myints.push_back(i);
		for (int i=0; i<10; i++) ft_myints.push_back(i);
#ifdef PRINT
		std::cout << "1a. size: " << myints.size() << '\n';
		std::cout << "1b. size: " << ft_myints.size() << '\n';
#endif
		ASSERT_EQUAL(myints.size(), ft_myints.size())

		myints.insert (myints.end(),10,100);
		ft_myints.insert (ft_myints.end(),10,100);
		ASSERT_EQUAL(myints.size(), ft_myints.size())

#ifdef PRINT
		std::cout << "2a. size: " << myints.size() << '\n';
		std::cout << "2b. size: " << ft_myints.size() << '\n';
#endif

		myints.pop_back();
		ft_myints.pop_back();
		ASSERT_EQUAL(myints.size(), ft_myints.size())
#ifdef PRINT
		std::cout << "3a. size: " << myints.size() << '\n';
		std::cout << "3b. size: " << ft_myints.size() << '\n';
#endif
	}
	{
		std::vector<int> myvector;
		ft::vector<int> ft_myvector;

		// set some initial content:
		for (int i=1;i<10;i++) myvector.push_back(i);
		for (int i=1;i<10;i++) ft_myvector.push_back(i);
		ASSERT_EQUAL(myvector, ft_myvector)

		myvector.resize(5);
		ft_myvector.resize(5);
		ASSERT_EQUAL(myvector, ft_myvector)
		myvector.resize(8,100);
		ft_myvector.resize(8,100);
		ASSERT_EQUAL(myvector, ft_myvector)
		myvector.resize(12);
		ft_myvector.resize(12);
		ASSERT_EQUAL(myvector, ft_myvector)

#ifdef PRINT
		std::cout << "myvector contains:";
		std::cout << myvector << '\n';
		std::cout << "myvector contains:";
		std::cout << ft_myvector << '\n';
#endif
	}
	{
		std::vector<int> myvector;
		ft::vector<int> ft_myvector;

		// set some content in the vector:
		for (int i=0; i<100; i++) myvector.push_back(i);
		for (int i=0; i<100; i++) ft_myvector.push_back(i);

		ASSERT_EQUAL(myvector.size(), ft_myvector.size())
		ASSERT_EQUAL(myvector.capacity(),ft_myvector.capacity())
#ifdef PRINT
		std::cout << "size: " << (int) myvector.size() << '\n';
		std::cout << "ft_size: " << (int) ft_myvector.size() << '\n';
		std::cout << "capacity: " << (int) myvector.capacity() << '\n';
		std::cout << "ft_capacity: " << (int) ft_myvector.capacity() << '\n';
#endif
	}
	{
		std::vector<int> myvector;
		ft::vector<int> ft_myvector;
		int sum (0);
		int ft_sum (0);

		for (int i=1;i<=10;i++) myvector.push_back(i);
		for (int i=1;i<=10;i++) ft_myvector.push_back(i);

		while (!myvector.empty())
		{
			sum += myvector.back();
			myvector.pop_back();
		}
		while (!ft_myvector.empty())
		{
			ft_sum += ft_myvector.back();
			ft_myvector.pop_back();
		}
		ASSERT_EQUAL(sum, ft_sum)
#ifdef PRINT
		std::cout << "total: " << sum << '\n';
		std::cout << "ft_total: " << ft_sum << '\n';
#endif
	}
	{
		std::vector<int>::size_type sz;
		ft::vector<int>::size_type ft_sz;

		std::vector<int> foo;
		ft::vector<int> ft_foo;
		sz = foo.capacity();
		ft_sz = ft_foo.capacity();
		ASSERT_EQUAL(sz, ft_sz)
#ifdef PRINT
		std::cout << "making foo grow:\n";
#endif
		for (int i=0; i<100; ++i) {
			foo.push_back(i);
			ft_foo.push_back(i);
			if (sz!=foo.capacity()) {
				sz = foo.capacity();
#ifdef PRINT
				std::cout << "capacity changed: " << sz << '\n';
#endif
			}
			if (ft_sz!=ft_foo.capacity()) {
				ft_sz = ft_foo.capacity();
#ifdef PRINT
				std::cout << "ft_capacity changed: " << ft_sz << '\n';
#endif
			}
			ASSERT_EQUAL(sz, ft_sz)
		}

		std::vector<int> bar;
		ft::vector<int> ft_bar;
		sz = bar.capacity();
		ft_sz = ft_bar.capacity();
		bar.reserve(100);   // this is the only difference with foo above
		ft_bar.reserve(100);   // this is the only difference with foo above
#ifdef PRINT
		std::cout << "making bar grow:\n";
#endif
		for (int i=0; i<100; ++i) {
			bar.push_back(i);
			ft_bar.push_back(i);
			if (sz!=bar.capacity()) {
				sz = bar.capacity();
#ifdef PRINT
				std::cout << "capacity changed: " << sz << '\n';
#endif
			}
			if (ft_sz!=ft_bar.capacity()) {
				ft_sz = ft_bar.capacity();
#ifdef PRINT
				std::cout << "ft_capacity changed: " << ft_sz << '\n';
#endif
			}
			ASSERT_EQUAL(sz, ft_sz)
		}
	}
}

static void	TestElementAccess()
{
	{
		std::vector<int> myvector (10);   // 10 zero-initialized elements
		ft::vector<int> ft_myvector (10);   // 10 zero-initialized elements

		std::vector<int>::size_type sz = myvector.size();
		ft::vector<int>::size_type ft_sz = ft_myvector.size();
		ASSERT_EQUAL(sz, ft_sz)

		// assign some values:
		for (unsigned i=0; i<sz; i++) myvector[i]=i;
		for (unsigned i=0; i<ft_sz; i++) ft_myvector[i]=i;

		// reverse vector using operator[]:
		for (unsigned i=0; i<sz/2; i++)
		{
			int temp;
			temp = myvector[sz-1-i];
			myvector[sz-1-i]=myvector[i];
			myvector[i]=temp;
		}
		for (unsigned i=0; i<ft_sz/2; i++)
		{
			int temp;
			temp = ft_myvector[ft_sz-1-i];
			ft_myvector[ft_sz-1-i]=ft_myvector[i];
			ft_myvector[i]=temp;
		}

		ASSERT_EQUAL(myvector, ft_myvector)
#ifdef PRINT
		std::cout << "\033[1;35m";
		std::cout << "\n--------TestElementAccess--------\n";
		std::cout << "\033[0m";
		std::cout << "myvector contains:";
		for (unsigned i=0; i<sz; i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "ft_myvector contains:";
		for (unsigned i=0; i<ft_sz; i++)
			std::cout << ' ' << ft_myvector[i];
		std::cout << '\n';
#endif
	}
	{
		std::vector<int> myvector(10);
		ft::vector<int> ft_myvector(10);
		int i = 0;
		try {
			myvector.at(20)=100;      // vector::at throws an out-of-range
		}
		catch (const std::out_of_range& oor) {
#ifdef PRINT
			std::cerr << "Out of Range error: " << oor.what() << '\n';
#endif
			i++;
		}
		try {
			ft_myvector.at(20)=100;      // vector::at throws an out-of-range
		}
		catch (const std::out_of_range& oor) {
#ifdef PRINT
			std::cerr << "Out of Range error: " << oor.what() << '\n';
#endif
			i++;
		}
		ASSERT_EQUAL(i, 2)
	}
	{
		std::vector<int> myvector;
		ft::vector<int> ft_myvector;

		myvector.push_back(78);
		myvector.push_back(16);
		ft_myvector.push_back(78);
		ft_myvector.push_back(16);

		// now front equals 78, and back 16

		myvector.front() -= myvector.back();
		ft_myvector.front() -= ft_myvector.back();

		ASSERT_EQUAL(myvector.front(), ft_myvector.front())
#ifdef PRINT
		std::cout << "myvector.front() is now " << myvector.front() << '\n';
		std::cout << "ft_myvector.front() is now " << ft_myvector.front() <<
		'\n';
#endif
	}
}

static void	TestAssign()
{
	std::vector<int> first;
	std::vector<int> second;
	std::vector<int> third;
	ft::vector<int> ft_first;
	ft::vector<int> ft_second;
	ft::vector<int> ft_third;

	first.assign ((size_t)7,100);             // 7 ints with a value of 100
	ft_first.assign ((size_t)7,100);             // 7 ints with a value of 100
	ASSERT_EQUAL(first, ft_first)

	std::vector<int>::iterator it;
	ft::vector<int>::iterator ft_it;
	it=first.begin()+1;
	ft_it=ft_first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first
	ft_second.assign (ft_it,ft_first.end()-1); // the 5 central values of first
	ASSERT_EQUAL(second, ft_second)

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.
	ft_third.assign (myints,myints+3);   // assigning from array.
	ASSERT_EQUAL(third, ft_third)

	ASSERT_EQUAL(first.size(), ft_first.size())
	ASSERT_EQUAL(second.size(), ft_second.size())
	ASSERT_EQUAL(third.size(), ft_third.size())
#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestAssign--------\n";
	std::cout << "\033[0m";
	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of ft_first: " << int (ft_first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	std::cout << "Size of ft_second: " << int (ft_second.size()) << '\n';
	std::cout << "Size of third: " << int (third.size()) << '\n';
	std::cout << "Size of ft_third: " << int (ft_third.size()) << '\n';
#endif
}

static void	TestPopBack()
{
	std::vector<int> myvector;
	ft::vector<int> ft_myvector;
	int sum (0);
	int ft_sum (0);
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);
	ft_myvector.push_back (100);
	ft_myvector.push_back (200);
	ft_myvector.push_back (300);

	while (!myvector.empty())
	{
		sum+=myvector.back();
		myvector.pop_back();
	}
	while (!ft_myvector.empty())
	{
		ft_sum+=ft_myvector.back();
		ft_myvector.pop_back();
	}

	ASSERT_EQUAL(sum, ft_sum)
#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestPopBack--------\n";
	std::cout << "\033[0m";
	std::cout << "The elements of myvector add up to " << sum << '\n';
	std::cout << "The elements of ft_myvector add up to " << ft_sum << '\n';
#endif
}

static void	TestInsert()
{
	std::vector<int> myvector (3,100);
	std::vector<int>::iterator it;
	ft::vector<int> ft_myvector (3,100);
	ft::vector<int>::iterator ft_it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );
	ft_it = ft_myvector.begin();
	ft_it = ft_myvector.insert ( ft_it , 200 );
	ASSERT_EQUAL(myvector, ft_myvector);
	ASSERT_EQUAL(*it, *ft_it)

	myvector.insert (it,2,300);
	ft_myvector.insert (ft_it,2,300);
	ASSERT_EQUAL(myvector, ft_myvector);

	// "it" no longer valid, get a new one:
	it = myvector.begin();
	ft_it = ft_myvector.begin();

	std::vector<int> anothervector (2,400);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());
	ft_myvector.insert (ft_it+2,anothervector.begin(),anothervector.end());
	ASSERT_EQUAL(myvector, ft_myvector);

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);
	ft_myvector.insert (ft_myvector.begin(), myarray, myarray+3);
	ASSERT_EQUAL(myvector, ft_myvector);

#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestInsert--------\n";
	std::cout << "\033[0m";
	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "ft_myvector contains:";
	for (ft_it=ft_myvector.begin(); ft_it<ft_myvector.end(); ft_it++)
		std::cout << ' ' << *ft_it;
	std::cout << '\n';
#endif
}

static void	TestErase()
{
	std::vector<int> myvector;
	ft::vector<int> ft_myvector;
	std::vector<int>::iterator it;
	ft::vector<int>::iterator ft_it;

	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) myvector.push_back(i);
	for (int i=1; i<=10; i++) ft_myvector.push_back(i);

	// erase the 6th element
	it = myvector.erase (myvector.begin()+5);
	ft_it = ft_myvector.erase (ft_myvector.begin()+5);
	ASSERT_EQUAL(myvector, ft_myvector)
	ASSERT_EQUAL(*it, *ft_it)

	// erase the first 3 elements:
	it = myvector.erase (myvector.begin(),myvector.begin()+3);
	ft_it = ft_myvector.erase (ft_myvector.begin(),ft_myvector.begin()+3);
	ASSERT_EQUAL(myvector, ft_myvector)
	ASSERT_EQUAL(*it, *ft_it)

#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestErase--------\n";
	std::cout << "\033[0m";
	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout << "ft_myvector contains:";
	for (unsigned i=0; i<ft_myvector.size(); ++i)
		std::cout << ' ' << ft_myvector[i];
	std::cout << '\n';
#endif
}

static void	TestClear()
{
	std::vector<int> myvector;
	ft::vector<int> ft_myvector;
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);
	ft_myvector.push_back (100);
	ft_myvector.push_back (200);
	ft_myvector.push_back (300);

	ASSERT_EQUAL(myvector, ft_myvector)
#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestClear--------\n";
	std::cout << "\033[0m";
	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout << "ft_myvector contains:";
	for (unsigned i=0; i<ft_myvector.size(); i++)
		std::cout << ' ' << ft_myvector[i];
	std::cout << '\n';
#endif

	myvector.clear();
	ft_myvector.clear();
	ASSERT_EQUAL(myvector, ft_myvector)
	myvector.push_back (1101);
	myvector.push_back (2202);
	ft_myvector.push_back (1101);
	ft_myvector.push_back (2202);
	ASSERT_EQUAL(myvector, ft_myvector)

#ifdef PRINT
	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
	std::cout << "ft_myvector contains:";
	for (unsigned i=0; i<ft_myvector.size(); i++)
		std::cout << ' ' << ft_myvector[i];
	std::cout << '\n';
#endif
}

static void	TestSwapMember()
{
	std::vector<int> foo (3,100);   // three ints with a value of 100
	std::vector<int> bar (5,200);   // five ints with a value of 200
	ft::vector<int> ft_foo (3,100);   // three ints with a value of 100
	ft::vector<int> ft_bar (5,200);   // five ints with a value of 200

	foo.swap(bar);
	ft_foo.swap(ft_bar);
	ASSERT_EQUAL(foo, ft_foo)
	ASSERT_EQUAL(bar, ft_bar)

#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestSwapMember--------\n";
	std::cout << "\033[0m";
	std::cout << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';
	std::cout << "ft_foo contains:";
	for (unsigned i=0; i<ft_foo.size(); i++)
		std::cout << ' ' << ft_foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';
	std::cout << "ft_bar contains:";
	for (unsigned i=0; i<ft_bar.size(); i++)
		std::cout << ' ' << ft_bar[i];
	std::cout << '\n';
#endif
}

static void	TestCompare()
{
	std::vector<int> a(3, 100);
	std::vector<int> b(2, 200);
	ft::vector<int> ft_a(3, 100);
	ft::vector<int> ft_b(2,200);

	ASSERT_EQUAL((a==b), (ft_a==ft_b))
	ASSERT_EQUAL((a!=b), (ft_a!=ft_b))
	ASSERT_EQUAL((a<b), (ft_a<ft_b))
	ASSERT_EQUAL((a>b), (ft_a>ft_b))
	ASSERT_EQUAL((a<=b), (ft_a<=ft_b))
	ASSERT_EQUAL((a>=b), (ft_a>=ft_b))
#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestCompare--------\n";
	std::cout << "\033[0m";
		if (a==b) std::cout << "a and b are equal\n";
		if (ft_a==ft_b) std::cout << "ft_a and ft_b are equal\n";
		if (a!=b) std::cout << "a and b are not equal\n";
		if (ft_a!=ft_b) std::cout << "ft_a and ft_b are not equal\n";
		if (a<b) std::cout << "a is less than b\n";
		if (ft_a<ft_b) std::cout << "ft_a is less than ft_b\n";
		if (a>b) std::cout << "a is greater than b\n";
		if (ft_a>ft_b) std::cout << "ft_a is greater than ft_b\n";
		if (a<=b) std::cout << "a is less than or equal to b\n";
		if (ft_a<=ft_b) std::cout << "ft_a is less than or equal to ft_b\n";
		if (a>=b) std::cout << "a is greater than or equal to b\n";
		if (ft_a>=ft_b) std::cout << "ft_a is greater than or equal to ft_b\n";
#endif
}

static void	TestSwap()
{
	std::vector<int> foo (3,100);   // three ints with a value of 100
	std::vector<int> bar (5,200);   // five ints with a value of 200
	ft::vector<int> ft_foo (3,100);   // three ints with a value of 100
	ft::vector<int> ft_bar (5,200);   // five ints with a value of 200

	std::swap(foo,bar);
	ft::swap(ft_foo,ft_bar);
	ASSERT_EQUAL(foo, ft_foo)
	ASSERT_EQUAL(bar, ft_bar)

#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestSwap--------\n";
	std::cout << "\033[0m";
	std::cout << "foo contains: " << foo << "\n";
	std::cout << "ft_foo contains: " << ft_foo << "\n";
	std::cout << "bar contains: " << bar << "\n";
	std::cout << "ft_bar contains: " << ft_bar << "\n";
#endif
}

void	test_vector()
{
	TestRunner tr;

	std::cout << "\033[1;36m";
	std::cout << "\n\n--------TEST VECTOR--------\n\n";
	std::cout << "\033[0m";
	RUN_TEST(tr, TestMemberType);
	RUN_TEST(tr, TestConstructor);
	RUN_TEST(tr, TestOperatorEqual);
	RUN_TEST(tr, TestIterators);
	RUN_TEST(tr, TestCapacity);
	RUN_TEST(tr, TestElementAccess);
	RUN_TEST(tr, TestAssign);
	RUN_TEST(tr, TestPopBack);
	RUN_TEST(tr, TestInsert);
	RUN_TEST(tr, TestErase);
	RUN_TEST(tr, TestClear);
	RUN_TEST(tr, TestSwapMember);
	RUN_TEST(tr, TestCompare);
	RUN_TEST(tr, TestSwap);
}
