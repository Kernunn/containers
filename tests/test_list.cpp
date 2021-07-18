#include <iostream>
#include "list.hpp"
#include <list>
#include <string>
#include <vector>
#include <cmath>
#include "test_runner.h"

template<typename T>
bool operator==(const std::list<T> &lhs, const ft::list<T> &rhs) {
  if (lhs.size() != rhs.size())
	return (false);
  typename std::list<T>::const_iterator left = lhs.begin();
  typename ft::list<T>::const_iterator right = rhs.begin();
  while (left != lhs.end()) {
	if (*left == *right) {
	  ++left;
	  ++right;
	  continue;
	}
	return (false);
  }
  return (true);
}

template<typename T>
static void print_list(std::list<T> const &list, std::string const &str) {
  std::cout << "The contents of " << str << " are: ";
  for (typename std::list<T>::const_iterator it = list.begin();
	   it != list.end(); it++)
	std::cout << *it << ' ';
  std::cout << '\n';
}

template<typename T>
static void print_list(ft::list<T> const &list, std::string const &str) {
  std::cout << "The contents of " << str << " are: ";
  for (typename ft::list<T>::const_iterator it = list.begin();
	   it != list.end(); it++)
	std::cout << *it << ' ';
  std::cout << '\n';
}

// a predicate implemented as a function:
bool single_digit(const int &value) { return (value < 10); }

// a predicate implemented as a class:
struct is_odd {
  bool operator()(const int &value) { return (value % 2) == 1; }
};

// a binary predicate implemented as a function:
bool same_integral_part(double first, double second) {
  return (int(first) == int(second));
}

// a binary predicate implemented as a class:
struct is_near {
  bool operator()(double first, double second) { return (fabs(first - second) < 5.0); }
};

// compare only integral part:
bool mycomparison(double first, double second) { return (int(first) < int(second)); }

bool compare_nocase(const std::string &first, const std::string &second) {
  unsigned int i = 0;
  while ((i < first.length()) && (i < second.length())) {
	if (tolower(first[i]) < tolower(second[i])) return true;
	else if (tolower(first[i]) > tolower(second[i])) return false;
	++i;
  }
  return (first.length() < second.length());
}

static void TestMemberTypes() {
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestMemberType--------\n";
  std::cout << "\033[0m";
  std::list<int>::value_type tmp = 8;
  ft::list<int>::value_type tmp2 = 8;
  std::cout << tmp << " " << tmp2 << "\n";

  std::list<int>::reference tmp3 = tmp;
  ft::list<int>::reference tmp4 = tmp;
  std::cout << tmp3 << " " << tmp4 << "\n";

  std::list<int>::const_reference tmp5 = tmp2;
  ft::list<int>::const_reference tmp6 = tmp2;
  std::cout << tmp5 << " " << tmp6 << "\n";

  std::list<int>::pointer tmp7 = &tmp;
  ft::list<int>::pointer tmp8 = &tmp;
  std::cout << *tmp7 << " " << *tmp8 << "\n";


  std::list<int>::const_pointer tmp9 = &tmp;
  ft::list<int>::const_pointer tmp10 = &tmp;
  std::cout << *tmp9 << " " << *tmp10 << "\n";

  std::list<int>::size_type tmp11 = tmp;
  ft::list<int>::size_type tmp12 = tmp;
  std::cout << tmp11 << " " << tmp12 << "\n";

  std::list<int>::difference_type tmp13 = tmp7 - tmp7;
  ft::list<int>::difference_type tmp14 = tmp8 - tmp8;
  std::cout << tmp13 << " " << tmp14 << "\n";
#endif
}

static void TestConstructor() {
  // constructors used in the same order as described above:
  // empty list of ints
  std::list<int> first;
  ft::list<int> ft_first;
  ASSERT_EQUAL(first, ft_first);

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestConstructor--------\n";
  std::cout << "\033[0m";
  print_list(first, "first");
  print_list(ft_first, "ft_first");
  std::cout << "\n";
#endif

  // four ints with value 100
  std::list<int> second((size_t) 4, 100);
  ft::list<int> ft_second((size_t) 4, 100);
  ASSERT_EQUAL(second, ft_second);

#ifdef PRINT
  print_list(second, "second");
  print_list(ft_second, "ft_second");
  std::cout << "\n";
#endif

  // iterating through second
  std::list<int> third(second.begin(), second.end());
  ft::list<int> ft_third(ft_second.begin(), ft_second.end());
  ASSERT_EQUAL(third, ft_third);

#ifdef PRINT
  print_list(third, "third");
  print_list(ft_third, "ft_third");
  std::cout << "\n";
#endif

  // a copy of third
  std::list<int> fourth(third);
  ft::list<int> ft_fourth(ft_third);
  ASSERT_EQUAL(fourth, ft_fourth);

#ifdef PRINT
  print_list(fourth, "fourth");
  print_list(ft_fourth, "ft_fourth");
  std::cout << "\n";
#endif

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16, 2, 77, 29};
  std::list<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
  ft::list<int> ft_fifth(myints, myints + sizeof(myints) / sizeof
	  (int));
  ASSERT_EQUAL(fifth, ft_fifth);

#ifdef PRINT
  print_list(fifth, "fifth");
  print_list(ft_fifth, "ft_fifth");
  std::cout << "\n";
#endif
}

static void TestOperatorEqual() {
  std::list<int> first(3);      // list of 3 zero-initialized ints
  std::list<int> second(5);     // list of 5 zero-initialized ints
  ft::list<int> ft_first(3);
  ft::list<int> ft_second(5);     // list of 5 zero-initialized ints

  second = first;
  first = std::list<int>();

  ft_second = ft_first;
  ASSERT_EQUAL(second, ft_second);
  ft_first = ft::list<int>();
  ASSERT_EQUAL(first, ft_first);
  ASSERT_EQUAL(first.size(), ft_first.size());
  ASSERT_EQUAL(second.size(), ft_second.size());
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestOperator=--------\n";
  std::cout << "\033[0m";
  print_list(first, "first");
  print_list(ft_first, "ft_first");
  print_list(second, "second");
  print_list(ft_second, "ft_second");
  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of ft_first: " << int (ft_first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of ft_second: " << int (ft_second.size()) << '\n';
#endif
}

static void TestIterators() {
  int myints[] = {75, 23, 65, 42, 13};
  std::list<int> mylist(myints, myints + 5);
  ft::list<int> ft_mylist(myints, myints + 5);

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestIterators--------\n";
  std::cout << "\033[0m";
  std::cout << "mylist contains:";
#endif
  for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it) {
#ifdef PRINT
	std::cout << ' ' << *it;
#endif
  }
#ifdef PRINT
  std::cout << '\n';
#endif

#ifdef PRINT
  std::cout << "ft_mylist contains:";
#endif
  for (ft::list<int>::iterator it = ft_mylist.begin(); it != ft_mylist.end
	  (); ++it) {
#ifdef PRINT
	std::cout << ' ' << *it;
#endif
  }
#ifdef PRINT
  std::cout << '\n';
#endif

#ifdef PRINT
  std::cout << "ft_mylist contains:";
#endif
  for (ft::list<int>::const_iterator it = ft_mylist.begin(); it != ft_mylist
	  .end
		  (); ++it) {
#ifdef PRINT
	std::cout << ' ' << *it;
#endif
  }
#ifdef PRINT
  std::cout << '\n';
#endif

#ifdef PRINT
  std::cout << "mylist backwards:";
#endif
  for (std::list<int>::reverse_iterator rit = mylist.rbegin(); rit != mylist.rend();
	   ++rit) {
#ifdef PRINT
	std::cout << ' ' << *rit;
#endif
  }
#ifdef PRINT
  std::cout << '\n';
#endif

#ifdef PRINT
  std::cout << "ft_mylist backwards:";
#endif
  for (ft::list<int>::reverse_iterator rit = ft_mylist.rbegin();
	   rit != ft_mylist.rend(); ++rit) {
#ifdef PRINT
	std::cout << ' ' << *rit;
#endif
  }
#ifdef PRINT
  std::cout << '\n';
#endif

#ifdef PRINT
  std::cout << "ft_mylist backwards:";
#endif
  for (ft::list<int>::const_reverse_iterator rit = ft_mylist.rbegin();
	   rit != ft_mylist.rend(); ++rit) {
#ifdef PRINT
	std::cout << ' ' << *rit;
#endif
  }
#ifdef PRINT
  std::cout << '\n';
#endif
}

static void TestCapacity() {
  std::list<int> list;
  ft::list<int> ft_list;
  ASSERT_EQUAL(list.empty(), ft_list.empty())
  ASSERT_EQUAL(list.size(), ft_list.size())
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestCapacity--------\n";
  std::cout << "\033[0m";
  if (list.empty())
	  std::cout << "list is empty\n";
  if (ft_list.empty())
	  std::cout << "ft_list is empty\n";
  std::cout << "size list: " << list.size() << "\n";
  std::cout << "size ft_list: " << ft_list.size() << "\n";
#endif
  list.push_back(1);
  ft_list.push_back(1);
  list.push_back(2);
  ft_list.push_back(2);
  ASSERT_EQUAL(list.empty(), ft_list.empty())
  ASSERT_EQUAL(list.size(), ft_list.size())
#ifdef PRINT
  if (list.empty())
	  std::cout << "list is empty\n";
  else
	  std::cout << "size list: " << list.size() << "\n";
  if (ft_list.empty())
	  std::cout << "ft_list is empty\n";
  else
	  std::cout << "size ft_list: " << ft_list.size() << "\n";
#endif
  ASSERT_EQUAL(list.max_size(), ft_list.max_size())
}

static void TestElementAccess() {
  std::list<int> mylist;
  ft::list<int> ft_mylist;

  mylist.push_back(77);
  mylist.push_back(22);
  ft_mylist.push_back(77);
  ft_mylist.push_back(22);

  // now front equals 77, and back 22

  mylist.front() -= mylist.back();
  ft_mylist.front() -= ft_mylist.back();
  ASSERT_EQUAL(mylist.front(), ft_mylist.front())
  ASSERT_EQUAL(mylist.back(), ft_mylist.back())
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestElement access--------\n";
  std::cout << "\033[0m";
  std::cout << "mylist.front() is now " << mylist.front() << '\n';
  std::cout << "ft_mylist.front() is now " << ft_mylist.front() << '\n';

  const ft::list<int> const_list(2, 6);
  std::cout << const_list.front() << " " << const_list.back() << "\n";
#endif
}

static void TestAssign() {
  std::list<int> first;
  std::list<int> second;
  ft::list<int> ft_first;
  ft::list<int> ft_second;

  first.assign((size_t) 7, 100);
  second.assign(first.begin(), first.end());
  ft_first.assign((size_t) 7, 100);
  ft_second.assign(ft_first.begin(), ft_first.end());
  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second)
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestAsign--------\n";
  std::cout << "\033[0m";
	  print_list(first, "first");
	  print_list(ft_first, "ft_first");
	  print_list(second, "second");
	  print_list(ft_second, "ft_second");
#endif
  int myints[] = {1776, 7, 4};
  first.assign(myints, myints + 3);            // assigning from array
  ft_first.assign(myints, myints + 3);            // assigning from array
  ASSERT_EQUAL(first, ft_first)

#ifdef PRINT
  print_list(first, "first");
  print_list(ft_first, "ft_first");

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of ft_first: " << int (ft_first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of ft_second: " << int (ft_second.size()) << '\n';
#endif
}

static void TestPushPop() {
  std::list<int> mylist(2, 100);         // two ints with a value of 100
  ft::list<int> ft_mylist(2, 100);      // two ints with a value of 100
  mylist.push_front(200);
  mylist.push_front(300);
  ft_mylist.push_front(200);
  ft_mylist.push_front(300);

  ASSERT_EQUAL(mylist, ft_mylist)
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestPushPop--------\n";
  std::cout << "\033[0m";
	  print_list(mylist, "mylist");
	  print_list(ft_mylist, "ft_mylist");
#endif

  while (!mylist.empty())
	mylist.pop_front();
  while (!ft_mylist.empty())
	ft_mylist.pop_front();

  ASSERT_EQUAL(mylist.size(), ft_mylist.size())
#ifdef PRINT
  std::cout << "Size of mylist is " << mylist.size() << "\n";
  std::cout << "Size of ft_mylist is " << ft_mylist.size() << "\n";
#endif

  mylist.push_back(400);
  mylist.push_back(500);
  ft_mylist.push_back(400);
  ft_mylist.push_back(500);

  ASSERT_EQUAL(mylist, ft_mylist)
#ifdef PRINT
  print_list(mylist, "mylist");
  print_list(ft_mylist, "ft_mylist");
#endif

  while (!mylist.empty())
	mylist.pop_back();
  while (!ft_mylist.empty())
	ft_mylist.pop_back();

#ifdef PRINT
  std::cout << "Size of mylist is " << mylist.size() << "\n";
  std::cout << "Size of ft_mylist is " << ft_mylist.size() << "\n";
#endif
}

static void TestInsert() {
  std::list<int> mylist;
  std::list<int>::iterator it;
  ft::list<int> ft_mylist;
  ft::list<int>::iterator ft_it;

  // set some initial values:
  for (int i = 1; i <= 5; ++i) mylist.push_back(i); // 1 2 3 4 5
  for (int i = 1; i <= 5; ++i) ft_mylist.push_back(i); // 1 2 3 4 5

  it = mylist.begin();
  ++it;       // it points now to number 2
  ft_it = ft_mylist.begin();
  ++ft_it;       // it points now to number 2

  mylist.insert(it, 10);                        // 1 10 2 3 4 5
  ft_mylist.insert(ft_it, 10);                 // 1 10 2 3 4 5
  ASSERT_EQUAL(mylist, ft_mylist)

  // "it" still points to number 2
  mylist.insert(it, (size_t) 2, 20);                // 1 10 20 20 2 3 4 5
  ft_mylist.insert(ft_it, (size_t) 2, 20);          // 1 10 20 20 2 3 4 5
  ASSERT_EQUAL(mylist, ft_mylist)

  --it;       // it points now to the second 20
  --ft_it;       // it points now to the second 20

  std::vector<int> myvector(2, 30);
  mylist.insert(it, myvector.begin(), myvector.end());
  ft_mylist.insert(ft_it, myvector.begin(), myvector.end());
  // 1 10 20 30 30 20 2 3 4 5
  ASSERT_EQUAL(mylist, ft_mylist)
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestInsert--------\n";
  std::cout << "\033[0m";
	  print_list(mylist, "mylist");
	  print_list(ft_mylist, "ft_mylist");
#endif
}

static void TestErase() {
  std::list<int> mylist;
  std::list<int>::iterator it1, it2;
  ft::list<int> ft_mylist;
  ft::list<int>::iterator ft_it1, ft_it2;

  // set some values:
  for (int i = 1; i < 10; ++i) mylist.push_back(i * 10);
  for (int i = 1; i < 10; ++i) ft_mylist.push_back(i * 10);

  // 10 20 30 40 50 60 70 80 90
  it1 = it2 = mylist.begin();
  std::advance(it2, 6);
  ++it1;
  ft_it1 = ft_it2 = ft_mylist.begin();
  std::advance(ft_it2, 6);
  ++ft_it1;

  it1 = mylist.erase(it1);   // 10 30 40 50 60 70 80 90
  it1 = mylist.erase(it1);   // 10 40 50 60 70 80 90
  ft_it1 = ft_mylist.erase(ft_it1);   // 10 30 40 50 60 70 80 90
  ft_it1 = ft_mylist.erase(ft_it1);   // 10 40 50 60 70 80 90
  ASSERT_EQUAL(mylist, ft_mylist)

  it2 = mylist.erase(it2);   // 10 30 40 50 60 80 90
  ft_it2 = ft_mylist.erase(ft_it2);   // 10 30 40 50 60 80 90
  ASSERT_EQUAL(mylist, ft_mylist)

  ++it1;
  --it2;
  ++ft_it1;
  --ft_it2;

  mylist.erase(it1, it2);     // 10 30 60 80 90
  ft_mylist.erase(ft_it1, ft_it2);     // 10 30 60 80 90
  ASSERT_EQUAL(mylist, ft_mylist)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestErase--------\n";
  std::cout << "\033[0m";
	  print_list(mylist, "mylist");
	  print_list(ft_mylist, "ft_mylist");
#endif
}

static void TestSwapMember() {
  std::list<int> first(3, 100);   // three ints with a value of 100
  std::list<int> second(5, 200);  // five ints with a value of 200
  ft::list<int> ft_first(3, 100);   // three ints with a value of 100
  ft::list<int> ft_second(5, 200);  // five ints with a value of 200

  first.swap(second);
  ft_first.swap(ft_second);
  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestSwap--------\n";
  std::cout << "\033[0m";
	  print_list(first, "first");
	  print_list(ft_first, "ft_first");
	  print_list(second, "second");
	  print_list(ft_second, "ft_second");
#endif
}

static void TestResize() {
  std::list<int> mylist;
  ft::list<int> ft_mylist;

  // set some initial content:
  for (int i = 1; i < 10; ++i) mylist.push_back(i);
  for (int i = 1; i < 10; ++i) ft_mylist.push_back(i);

  mylist.resize(5);
  ft_mylist.resize(5);
  ASSERT_EQUAL(mylist, ft_mylist)
  mylist.resize(8, 100);
  ft_mylist.resize(8, 100);
  ASSERT_EQUAL(mylist, ft_mylist)
  mylist.resize(12);
  ft_mylist.resize(12);
  ASSERT_EQUAL(mylist, ft_mylist)
  mylist.resize(7);
  ft_mylist.resize(7);
  ASSERT_EQUAL(mylist, ft_mylist)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestResize--------\n";
  std::cout << "\033[0m";
	  print_list(mylist, "mylist");
	  print_list(ft_mylist, "ft_mylist");
#endif
}

static void TestClear() {
  std::list<int> mylist;
  std::list<int>::iterator it;
  ft::list<int> ft_mylist;
  ft::list<int>::iterator ft_it;

  mylist.push_back(100);
  mylist.push_back(200);
  mylist.push_back(300);
  ft_mylist.push_back(100);
  ft_mylist.push_back(200);
  ft_mylist.push_back(300);

  ASSERT_EQUAL(mylist, ft_mylist)
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestClear--------\n";
  std::cout << "\033[0m";
	  print_list(mylist, "mylist");
	  print_list(ft_mylist, "ft_mylist");
#endif

  mylist.clear();
  ft_mylist.clear();
  mylist.push_back(1101);
  mylist.push_back(2202);
  ft_mylist.push_back(1101);
  ft_mylist.push_back(2202);
  ASSERT_EQUAL(mylist, ft_mylist)

#ifdef PRINT
  print_list(mylist, "mylist");
  print_list(ft_mylist, "ft_mylist");
#endif
}

static void TestSplice() {
  std::list<int> mylist1, mylist2;
  std::list<int>::iterator it;
  ft::list<int> ft_mylist1, ft_mylist2;
  ft::list<int>::iterator ft_it;

  // set some initial values:
  for (int i = 1; i <= 4; ++i)
	mylist1.push_back(i);      // mylist1: 1 2 3 4
  for (int i = 1; i <= 4; ++i)
	ft_mylist1.push_back(i);      // ft_mylist1: 1 2 3 4

  for (int i = 1; i <= 3; ++i)
	mylist2.push_back(i * 10);   // mylist2: 10 20 30
  for (int i = 1; i <= 3; ++i)
	ft_mylist2.push_back(i * 10);   // ft_mylist2: 10 20 30

  it = mylist1.begin();
  ++it;                         // points to 2
  ft_it = ft_mylist1.begin();
  ++ft_it;                         // points to 2

  mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
  ft_mylist1.splice(ft_it, ft_mylist2); // ft_mylist1: 1 10 20 30 2 3 4
  // mylist2 (empty)
  // "it" still points to 2 (the 5th element)
  ASSERT_EQUAL(mylist1, ft_mylist1)

  mylist2.splice(mylist2.begin(), mylist1, it);
  ft_mylist2.splice(ft_mylist2.begin(), ft_mylist1, ft_it);
  // mylist1: 1 10 20 30 3 4
  // mylist2: 2
  // "it" is now invalid.
  ASSERT_EQUAL(mylist2, ft_mylist2)
  it = mylist1.begin();
  std::advance(it, 3);           // "it" points now to 30
  ft_it = ft_mylist1.begin();
  std::advance(ft_it, 3);           // "ft_it" points now to 30

  mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
  ft_mylist1.splice(ft_mylist1.begin(), ft_mylist1, ft_it, ft_mylist1
	  .end());
  // mylist1: 30 3 4 1 10 20
  ASSERT_EQUAL(mylist1, ft_mylist1)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestSplice--------\n";
  std::cout << "\033[0m";
	  print_list(mylist1, "mylist1");
	  print_list(ft_mylist1, "ft_mylist1");
	  print_list(mylist2, "mylist2");
	  print_list(ft_mylist2, "ft_mylist2");
#endif
}

static void TestRemove() {
  int myints[] = {17, 89, 7, 14};
  std::list<int> mylist(myints, myints + 4);
  ft::list<int> ft_mylist(myints, myints + 4);

  mylist.remove(89);
  ft_mylist.remove(89);
  ASSERT_EQUAL(mylist, ft_mylist)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestRemove--------\n";
  std::cout << "\033[0m";
	  print_list(mylist, "mylist");
	  print_list(ft_mylist, "ft_mylist");
#endif
}

static void TestRemoveIf() {
  int myints[] = {15, 36, 7, 17, 20, 39, 4, 1};
  std::list<int> mylist(myints, myints + 8);   // 15 36 7 17 20 39 4 1
  ft::list<int> ft_mylist(myints, myints + 8);   // 15 36 7 17 20 39 4 1

  mylist.remove_if(single_digit);           // 15 36 17 20 39
  ft_mylist.remove_if(single_digit);           // 15 36 17 20 39
  ASSERT_EQUAL(mylist, ft_mylist)

  mylist.remove_if(is_odd());               // 36 20
  ft_mylist.remove_if(is_odd());               // 36 20
  ASSERT_EQUAL(mylist, ft_mylist)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestRemoveIf--------\n";
  std::cout << "\033[0m";
	  print_list(mylist, "mylist");
	  print_list(ft_mylist, "ft_mylist");
#endif
}

static void TestUnique() {
  double mydoubles[] = {2.72, 3.14, 12.15, 12.77, 12.77,
						15.3, 72.25, 72.25, 73.0, 73.35};
  std::list<double> mylist(mydoubles, mydoubles + 10);
  ft::list<double> ft_mylist(mydoubles, mydoubles + 10);

  mylist.unique();           //  2.72,  3.14, 12.15, 12.77
  // 15.3,  72.25, 73.0,  73.35
  ft_mylist.unique();
  ASSERT_EQUAL(mylist, ft_mylist)

  mylist.unique(same_integral_part);  //  2.72,  3.14, 12.15
  // 15.3,  72.25, 73.0
  ft_mylist.unique(same_integral_part);
  ASSERT_EQUAL(mylist, ft_mylist)

  mylist.unique(is_near());           //  2.72, 12.15, 72.25
  ft_mylist.unique(is_near());           //  2.72, 12.15, 72.25
  ASSERT_EQUAL(mylist, ft_mylist)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestUnique--------\n";
  std::cout << "\033[0m";
	  print_list(mylist, "mylist");
	  print_list(ft_mylist, "ft_mylist");
#endif
}

static void TestMerge() {
  std::list<double> first, second;
  ft::list<double> ft_first, ft_second;

  first.push_back(2.2);
  first.push_back(2.9);
  first.push_back(3.1);
  ft_first.push_back(2.2);
  ft_first.push_back(2.9);
  ft_first.push_back(3.1);

  second.push_back(1.4);
  second.push_back(3.7);
  second.push_back(7.1);
  ft_second.push_back(1.4);
  ft_second.push_back(3.7);
  ft_second.push_back(7.1);

  first.merge(second);
  ft_first.merge(ft_second);
  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second)

  // (second is now empty)

  second.push_back(2.1);
  ft_second.push_back(2.1);

  first.merge(second, mycomparison);
  ft_first.merge(ft_second, mycomparison);
  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestMerge--------\n";
  std::cout << "\033[0m";
	  print_list(first, "first");
	  print_list(ft_first, "ft_first");
	  print_list(second, "second");
	  print_list(ft_second, "ft_second");
#endif
}

static void TestSort() {
  std::list<std::string> mylist;
  ft::list<std::string> ft_mylist;

  mylist.push_back("one");
  mylist.push_back("two");
  mylist.push_back("Three");
  ft_mylist.push_back("one");
  ft_mylist.push_back("two");
  ft_mylist.push_back("Three");

  mylist.sort();
  ft_mylist.sort();
  ASSERT_EQUAL(mylist, ft_mylist)

  mylist.sort(compare_nocase);
  ft_mylist.sort(compare_nocase);
  ASSERT_EQUAL(mylist, ft_mylist)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestSort--------\n";
  std::cout << "\033[0m";
	  print_list(mylist, "mylist");
	  print_list(ft_mylist, "ft_mylist");
#endif
}

static void TestReverse() {
  std::list<int> mylist;
  ft::list<int> ft_mylist;

  for (int i = 1; i < 10; ++i) mylist.push_back(i);
  for (int i = 1; i < 10; ++i) ft_mylist.push_back(i);

  mylist.reverse();
  ft_mylist.reverse();
  ASSERT_EQUAL(mylist, ft_mylist)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestReverse--------\n";
  std::cout << "\033[0m";
	  print_list(mylist, "mylist");
	  print_list(ft_mylist, "ft_mylist");
#endif
}

static void TestCompare() {
  std::list<int> a;
  std::list<int> b;
  std::list<int> c;
  ft::list<int> ft_a;
  ft::list<int> ft_b;
  ft::list<int> ft_c;

  a.push_back(10);
  a.push_back(20);
  a.push_back(30);
  b.push_back(10);
  b.push_back(20);
  b.push_back(30);
  c.push_back(30);
  c.push_back(20);
  c.push_back(10);
  ft_a.push_back(10);
  ft_a.push_back(20);
  ft_a.push_back(30);
  ft_b.push_back(10);
  ft_b.push_back(20);
  ft_b.push_back(30);
  ft_c.push_back(30);
  ft_c.push_back(20);
  ft_c.push_back(10);

  ASSERT_EQUAL((a == b), (ft_a == ft_b))
  ASSERT_EQUAL((b != c), (ft_b != ft_c))
  ASSERT_EQUAL((b < c), (ft_b < ft_c))
  ASSERT_EQUAL((c > b), (ft_c > ft_b))
  ASSERT_EQUAL((a <= b), (ft_a <= ft_b))
  ASSERT_EQUAL((a >= b), (ft_a >= ft_b))
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestCompare--------\n";
  std::cout << "\033[0m";
	  if (a==b) std::cout << "a and b are equal\n";
	  if (ft_a==ft_b) std::cout << "ft_a and ft_b are equal\n";
	  if (b!=c) std::cout << "b and c are not equal\n";
	  if (ft_b!=ft_c) std::cout << "ft_b and ft_c are not equal\n";
	  if (b<c) std::cout << "b is less than c\n";
	  if (ft_b<ft_c) std::cout << "ft_b is less than ft_c\n";
	  if (c>b) std::cout << "c is greater than b\n";
	  if (ft_c>ft_b) std::cout << "ft_c is greater than ft_b\n";
	  if (a<=b) std::cout << "a is less than or equal to b\n";
	  if (ft_a<=ft_b) std::cout << "ft_a is less than or equal to ft_b\n";
	  if (a>=b) std::cout << "a is greater than or equal to b\n";
	  if (ft_a>=ft_b) std::cout << "ft_a is greater than or equal to ft_b\n";
#endif
}

static void TestSwap() {
  std::list<int> foo(3, 100);   // three ints with a value of 100
  std::list<int> bar(5, 200);   // five ints with a value of 200
  ft::list<int> ft_foo(3, 100);   // three ints with a value of 100
  ft::list<int> ft_bar(5, 200);   // five ints with a value of 200

  std::swap(foo, bar);
  ft::swap(ft_foo, ft_bar);
  ASSERT_EQUAL(foo, ft_foo)
  ASSERT_EQUAL(bar, ft_bar)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestSwap--------\n";
  std::cout << "\033[0m";
	  print_list(foo, "foo");
	  print_list(ft_foo, "ft_foo");
	  print_list(bar, "bar");
	  print_list(ft_bar, "ft_bar");
#endif
}

void test_list() {
  TestRunner tr;

  std::cout << "\033[1;36m";
  std::cout << "\n\n-------TEST LIST----------\n\n";
  std::cout << "\033[0m";
  RUN_TEST(tr, TestMemberTypes);
  RUN_TEST(tr, TestConstructor);
  RUN_TEST(tr, TestOperatorEqual);
  RUN_TEST(tr, TestIterators);
  RUN_TEST(tr, TestCapacity);
  RUN_TEST(tr, TestElementAccess);
  RUN_TEST(tr, TestAssign);
  RUN_TEST(tr, TestPushPop);
  RUN_TEST(tr, TestInsert);
  RUN_TEST(tr, TestErase);
  RUN_TEST(tr, TestSwapMember);
  RUN_TEST(tr, TestResize);
  RUN_TEST(tr, TestClear);
  RUN_TEST(tr, TestSplice);
  RUN_TEST(tr, TestRemove);
  RUN_TEST(tr, TestRemoveIf);
  RUN_TEST(tr, TestUnique);
  RUN_TEST(tr, TestMerge);
  RUN_TEST(tr, TestSort);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestCompare);
  RUN_TEST(tr, TestSwap);
}
