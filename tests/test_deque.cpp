#include "deque.hpp"
#include <deque>
#include "test_runner.h"

template<typename T>
bool operator==(const std::deque<T> &lhs, const ft::deque<T> &rhs) {
  if (lhs.size() != rhs.size())
	return (false);
  typename std::deque<T>::const_iterator left = lhs.begin();
  typename ft::deque<T>::const_iterator right = rhs.begin();
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

static void TestConstructor() {
  // constructors used in the same order as described above:
  std::deque<int> first;                         // empty deque of ints
  ft::deque<int> ft_first;
  std::deque<int> second((size_t) 4, 100);      // four ints with value 100
  ft::deque<int> ft_second((size_t) 4, 100);
  // iterating through second
  std::deque<int> third(second.begin(), second.end());
  ft::deque<int> ft_third(ft_second.begin(), ft_second.end());
  std::deque<int> fourth(third);                       // a copy of third
  ft::deque<int> ft_fourth(ft_third);

  ASSERT_EQUAL(first, ft_first);
  ASSERT_EQUAL(second, ft_second);
  ASSERT_EQUAL(third, ft_third);
  ASSERT_EQUAL(fourth, ft_fourth);

  // the iterator constructor can be used to copy arrays:
  int myints[] = {16, 2, 77, 29};
  std::deque<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
  ft::deque<int> ft_fifth(myints, myints + sizeof(myints) / sizeof(int));

  ASSERT_EQUAL(fifth, ft_fifth);

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestConstructor--------\n";
  std::cout << "\033[0m";
  std::cout << "The contents of fifth are: ";
  std::cout << fifth << '\n';
  std::cout << "The contents of ft_fifth are :";
  std::cout << ft_fifth << '\n';
#endif

  std::deque<std::string> words1;
  words1.push_back("the");
  words1.push_back("frogurt");
  words1.push_back("is");
  words1.push_back("also");
  words1.push_back("cursed");

  std::deque<std::string> words2(words1.begin(), words1.end());
  ft::deque<std::string> ft_words2(words1.begin(), words1.end());
  ASSERT_EQUAL(words2, ft_words2);

  // words3 == words1
  std::deque<std::string> words3(words2);
  ft::deque<std::string> ft_words3(ft_words2);
  ASSERT_EQUAL(words3, ft_words3);

  // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
  std::deque<std::string> words4(5, "Mo");
  ft::deque<std::string> ft_words4(5, "Mo");
  ASSERT_EQUAL(words4, ft_words4);

#ifdef PRINT
  std::cout << "words2: " << words2 << '\n';
  std::cout << "ft_words2: " << ft_words2 << '\n';
  std::cout << "words3: " << words3 << '\n';
  std::cout << "ft_words3: " << ft_words3 << '\n';
  std::cout << "words4: " << words4 << '\n';
  std::cout << "ft_words4: " << ft_words4 << '\n';
#endif
}

static void TestAssign() {
  std::deque<int> first(3);    // deque with 3 zero-initialized ints
  std::deque<int> second(5);   // deque with 5 zero-initialized ints
  ft::deque<int> ft_first(3);    // deque with 3 zero-initialized ints
  ft::deque<int> ft_second(5);   // deque with 5 zero-initialized ints

  ASSERT_EQUAL(first, ft_first)

  second = first;
  ft_second = ft_first;
  ASSERT_EQUAL(second, ft_second)
  first = std::deque<int>();
  ft_first = ft::deque<int>();
  ASSERT_EQUAL(first, ft_first)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestAssign--------\n";
  std::cout << "\033[0m";
  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of ft_first: " << int (ft_first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of ft_second: " << int (ft_second.size()) << '\n';
#endif
}

static void TestAssign2() {
  std::deque<int> first;
  std::deque<int> second;
  std::deque<int> third;
  ft::deque<int> ft_first;
  ft::deque<int> ft_second;
  ft::deque<int> ft_third;

  first.assign((size_t) 7, 100);             // 7 ints with a value of 100
  ft_first.assign((size_t) 7, 100);             // 7 ints with a value of 100

  ASSERT_EQUAL(first, ft_first)
  std::deque<int>::iterator it;
  ft::deque<int>::iterator ft_it;
  it = first.begin() + 1;
  ft_it = ft_first.begin() + 1;

  second.assign(it, first.end() - 1); // the 5 central values of first
  ft_second.assign(ft_it, ft_first.end() - 1); // the 5 central values of first
  ASSERT_EQUAL(second, ft_second)

  int myints[] = {1776, 7, 4};
  third.assign(myints, myints + 3);   // assigning from array.
  ft_third.assign(myints, myints + 3);   // assigning from array.

  ASSERT_EQUAL(third, ft_third)

#ifdef PRINT
  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of ft_first: " << int (ft_first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of ft_second: " << int (ft_second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';
  std::cout << "Size of ft_third: " << int (ft_third.size()) << '\n';
#endif
}

static void TestIterators() {
  {
	std::deque<int> mydeque;
	ft::deque<int> ft_mydeque;

	for (int i = 1; i <= 5; i++) mydeque.push_back(i);
	for (int i = 1; i <= 5; i++) ft_mydeque.push_back(i);

	ASSERT_EQUAL(mydeque, ft_mydeque)

#ifdef PRINT
	std::deque<int>::iterator it = mydeque.begin();
	ft::deque<int>::iterator ft_it = ft_mydeque.begin();
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestIterators--------\n";
	std::cout << "\033[0m";
	std::cout << "mydeque contains:";
	while (it != mydeque.end())
		std::cout << ' ' << *it++;
	std::cout << '\n';

	std::cout << "ft_mydeque contains:";
	while (ft_it != ft_mydeque.end())
		std::cout << ' ' << *ft_it++;
	std::cout << '\n';
#endif
  }
  {
	std::deque<int> mydeque(5);  // 5 default-constructed ints
	ft::deque<int> ft_mydeque(5);  // 5 default-constructed ints

	std::deque<int>::reverse_iterator rit = mydeque.rbegin();
	ft::deque<int>::reverse_iterator ft_rit = ft_mydeque.rbegin();

	int i = 0;
	for (rit = mydeque.rbegin(); rit != mydeque.rend(); ++rit)
	  *rit = ++i;

	i = 0;
	for (ft_rit = ft_mydeque.rbegin(); ft_rit != ft_mydeque.rend();
		 ++ft_rit)
	  *ft_rit = ++i;
	ASSERT_EQUAL(mydeque, ft_mydeque)

#ifdef PRINT
	std::cout << "mydeque contains:";
	std::cout << mydeque << '\n';
	std::cout << "ft_mydeque contains:";
	std::cout << ft_mydeque << '\n';
#endif
  }
}

static void TestCapacity() {
  std::deque<int> myints;
  ft::deque<int> ft_myints;
  ASSERT_EQUAL(myints.size(), ft_myints.size())
#ifdef PRINT
  std::cout << "0. size: " << myints.size() << '\n';
  std::cout << "0. ft_size: " << ft_myints.size() << '\n';
#endif

  for (int i = 0; i < 5; i++) myints.push_back(i);
  for (int i = 0; i < 5; i++) ft_myints.push_back(i);
  ASSERT_EQUAL(myints.size(), ft_myints.size())
#ifdef PRINT
  std::cout << "1. size: " << myints.size() << '\n';
  std::cout << "1. ft_size: " << ft_myints.size() << '\n';
#endif

//	myints.insert (myints.begin(),5,100);
//	std::cout << "2. size: " << myints.size() << '\n';
#ifdef PRINT
#endif

//	myints.pop_back();
//	std::cout << "3. size: " << myints.size() << '\n';
#ifdef PRINT
#endif

  std::deque<char> s;
  ft::deque<char> ft_s;
  ASSERT_EQUAL(s.max_size(), ft_s.max_size())
#ifdef PRINT
  std::cout << "Maximum size of a 'deque' is " << s.max_size() << "\n";
  std::cout << "Maximum size of a 'ft_deque' is " << ft_s.max_size() << "\n";
#endif

  std::deque<int> mydeque;
  std::deque<int>::iterator it;
  ft::deque<int> ft_mydeque;
  ft::deque<int>::iterator ft_it;

  // set some initial content:
  for (int i = 1; i < 10; ++i) mydeque.push_back(i);
  for (int i = 1; i < 10; ++i) ft_mydeque.push_back(i);

  mydeque.resize(5);
  ft_mydeque.resize(5);
  ASSERT_EQUAL(mydeque, ft_mydeque)
  mydeque.resize(8, 100);
  ft_mydeque.resize(8, 100);
  ASSERT_EQUAL(mydeque, ft_mydeque)
  mydeque.resize(12);
  ft_mydeque.resize(12);
  ASSERT_EQUAL(mydeque, ft_mydeque)

#ifdef PRINT
  std::cout << "mydeque contains:";
  std::cout << mydeque << '\n';
  std::cout << "ft_mydeque contains:";
  std::cout << ft_mydeque << '\n';
#endif

  std::deque<int> numbers;
  ft::deque<int> ft_numbers;
  ASSERT_EQUAL(numbers.empty(), ft_numbers.empty())
#ifdef PRINT
  std::cout << std::boolalpha;
  std::cout << "Initially, numbers.empty(): " << numbers.empty() << '\n';
  std::cout << "Initially, ft_numbers.empty(): " << ft_numbers.empty() <<
  '\n';
#endif

  numbers.push_back(42);
  numbers.push_back(13317);
  ft_numbers.push_back(42);
  ft_numbers.push_back(13317);
  ASSERT_EQUAL(numbers.empty(), ft_numbers.empty())

#ifdef PRINT
  std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << '\n';
  std::cout << "After adding elements, ft_numbers.empty(): " << ft_numbers
  .empty() << '\n';
#endif
}

static void TestElementAccess() {
  std::deque<int> mydeque(10);   // 10 zero-initialized elements
  std::deque<int>::size_type sz = mydeque.size();
  ft::deque<int> ft_mydeque(10);   // 10 zero-initialized elements
  ft::deque<int>::size_type ft_sz = ft_mydeque.size();

  ASSERT_EQUAL(mydeque, ft_mydeque)
  // assign some values:
  for (unsigned i = 0; i < sz; i++) mydeque[i] = i;
  for (unsigned i = 0; i < ft_sz; i++) ft_mydeque[i] = i;
  ASSERT_EQUAL(mydeque, ft_mydeque)

  // reverse order of elements using operator[]:
  for (unsigned i = 0; i < sz / 2; i++) {
	int temp;
	temp = mydeque[sz - 1 - i];
	mydeque[sz - 1 - i] = mydeque[i];
	mydeque[i] = temp;
	temp = ft_mydeque[sz - 1 - i];
	ft_mydeque[sz - 1 - i] = ft_mydeque[i];
	ft_mydeque[i] = temp;
  }
  ASSERT_EQUAL(mydeque, ft_mydeque)

#ifdef PRINT
  // print content:
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestElementAccess--------\n";
  std::cout << "\033[0m";
  std::cout << "mydeque contains:";
  for (unsigned i=0; i<sz; i++)
	  std::cout << ' ' << mydeque[i];
  std::cout << '\n';
  std::cout << "ft_mydeque contains:";
  for (unsigned i=0; i<ft_sz; i++)
	  std::cout << ' ' << ft_mydeque[i];
  std::cout << '\n';
#endif
  int i = 0;
  try {
	mydeque.at(20) = 100;      // vector::at throws an out-of-range
  }
  catch (const std::out_of_range &oor) {
#ifdef PRINT
	std::cerr << "Out of Range error: " << oor.what() << '\n';
#endif
	i++;
  }
  try {
	ft_mydeque.at(20) = 100;      // vector::at throws an out-of-range
  }
  catch (const std::out_of_range &oor) {
#ifdef PRINT
	std::cerr << "Out of Range error: " << oor.what() << '\n';
#endif
	i++;
  }
  ASSERT_EQUAL(i, 2)

  mydeque.front() -= mydeque.back();
  ft_mydeque.front() -= ft_mydeque.back();
  ASSERT_EQUAL(mydeque.front(), ft_mydeque.front())
#ifdef PRINT
  std::cout << "mydeque.front() is now " << mydeque.front() << '\n';
  std::cout << "ft_mydeque.front() is now " << ft_mydeque.front() << '\n';
#endif
}

static void TestPush() {
  std::deque<int> mydeque(2, 100);     // two ints with a value of 100
  ft::deque<int> ft_mydeque(2, 100);     // two ints with a value of 100
  mydeque.push_front(200);
  ft_mydeque.push_front(200);
  ASSERT_EQUAL(mydeque, ft_mydeque)
  mydeque.push_front(300);
  ft_mydeque.push_front(300);
  ASSERT_EQUAL(mydeque, ft_mydeque)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestPush--------\n";
  std::cout << "\033[0m";
  std::cout << "mydeque contains:";
  std::cout << mydeque << '\n';
  std::cout << "ft_mydeque contains:";
  std::cout << ft_mydeque << '\n';
#endif

  mydeque.push_back(200);
  ft_mydeque.push_back(200);
  ASSERT_EQUAL(mydeque, ft_mydeque)
  mydeque.push_back(300);
  ft_mydeque.push_back(300);
  ASSERT_EQUAL(mydeque, ft_mydeque)

#ifdef PRINT
  std::cout << "mydeque contains:";
  std::cout << mydeque << '\n';
  std::cout << "ft_mydeque contains:";
  std::cout << ft_mydeque << '\n';
#endif
}

static void TestPop() {
  {
	std::deque<int> mydeque;
	ft::deque<int> ft_mydeque;
	int sum(0);
	int ft_sum(0);
	mydeque.push_back(10);
	mydeque.push_back(20);
	mydeque.push_back(30);
	ft_mydeque.push_back(10);
	ft_mydeque.push_back(20);
	ft_mydeque.push_back(30);

	while (!mydeque.empty()) {
	  sum += mydeque.back();
	  mydeque.pop_back();
	}
	while (!ft_mydeque.empty()) {
	  ft_sum += ft_mydeque.back();
	  ft_mydeque.pop_back();
	}

	ASSERT_EQUAL(sum, ft_sum)
#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestPop--------\n";
	std::cout << "\033[0m";
	std::cout << "The elements of mydeque add up to " << sum << '\n';
	std::cout << "The elements of ft_mydeque add up to " << ft_sum << '\n';
#endif
  }
  {
	std::deque<int> mydeque;
	ft::deque<int> ft_mydeque;
	int sum(0);
	int ft_sum(0);
	mydeque.push_back(10);
	mydeque.push_back(20);
	mydeque.push_back(30);
	ft_mydeque.push_back(10);
	ft_mydeque.push_back(20);
	ft_mydeque.push_back(30);

	while (!mydeque.empty()) {
	  sum += mydeque.front();
	  mydeque.pop_front();
	}
	while (!ft_mydeque.empty()) {
	  ft_sum += ft_mydeque.front();
	  ft_mydeque.pop_front();
	}

	ASSERT_EQUAL(sum, ft_sum)
#ifdef PRINT
	std::cout << "The elements of mydeque add up to " << sum << '\n';
	std::cout << "The elements of ft_mydeque add up to " << ft_sum << '\n';
#endif
  }
}

static void TestInsert() {
  std::deque<int> mydeque;
  ft::deque<int> ft_mydeque;

  // set some initial values:
  for (int i = 1; i < 6; i++) mydeque.push_back(i); // 1 2 3 4 5
  for (int i = 1; i < 6; i++) ft_mydeque.push_back(i); // 1 2 3 4 5

  std::deque<int>::iterator it = mydeque.begin();
  ++it;
  ft::deque<int>::iterator ft_it = ft_mydeque.begin();
  ++ft_it;

  it = mydeque.insert(it, 10);                  // 1 10 2 3 4 5
  ft_it = ft_mydeque.insert(ft_it, 10);
  // "it" now points to the newly inserted 10
  ASSERT_EQUAL(mydeque, ft_mydeque);

  mydeque.insert(it, 2, 20);                     // 1 20 20 10 2 3 4 5
  ft_mydeque.insert(ft_it, 2, 20);               // 1 20 20 10 2 3 4 5
  // "it" no longer valid!

  ASSERT_EQUAL(mydeque, ft_mydeque);

  it = mydeque.begin() + 2;
  ft_it = ft_mydeque.begin() + 2;

  std::vector<int> myvector(2, 30);
  std::vector<int> ft_myvector(2, 30);
  mydeque.insert(it, myvector.begin(), myvector.end());
  ft_mydeque.insert(ft_it, ft_myvector.begin(), ft_myvector.end());
  // 1 20 30 30 20 10 2 3 4 5

  ASSERT_EQUAL(mydeque, ft_mydeque);

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestInsert--------\n";
  std::cout << "\033[0m";
  std::cout << "mydeque contains:";
  std::cout << mydeque << '\n';
  std::cout << "ft_mydeque contains:";
  std::cout << ft_mydeque << '\n';
#endif
}

static void TestErase() {
  std::deque<int> mydeque;
  ft::deque<int> ft_mydeque;

  // set some values (from 1 to 10)
  for (int i = 1; i <= 10; i++) mydeque.push_back(i);
  for (int i = 1; i <= 10; i++) ft_mydeque.push_back(i);

  // erase the 6th element
  mydeque.erase(mydeque.begin() + 5);
  ft_mydeque.erase(ft_mydeque.begin() + 5);
  ASSERT_EQUAL(mydeque, ft_mydeque)
  // erase the first 3 elements:
  mydeque.erase(mydeque.begin(), mydeque.begin() + 3);
  ft_mydeque.erase(ft_mydeque.begin(), ft_mydeque.begin() + 3);
  ASSERT_EQUAL(mydeque, ft_mydeque)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestErase--------\n";
  std::cout << "\033[0m";
  std::cout << "mydeque contains:";
  std::cout << mydeque << '\n';
  std::cout << "ft_mydeque contains:";
  std::cout << ft_mydeque << '\n';
#endif
}

static void TestSwap() {
  std::deque<int> foo(3, 100);   // three ints with a value of 100
  std::deque<int> bar(5, 200);   // five ints with a value of 200
  ft::deque<int> ft_foo(3, 100);   // three ints with a value of 100
  ft::deque<int> ft_bar(5, 200);   // five ints with a value of 200

  ASSERT_EQUAL(foo, ft_foo)
  ASSERT_EQUAL(bar, ft_bar)

  foo.swap(bar);
  ft_foo.swap(ft_bar);

  ASSERT_EQUAL(foo, ft_foo)
  ASSERT_EQUAL(bar, ft_bar)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestSwap--------\n";
  std::cout << "\033[0m";
  std::cout << "foo contains:";
  std::cout << foo << '\n';
  std::cout << "ft_foo contains:";
  std::cout << ft_foo << '\n';

  std::cout << "bar contains:";
  std::cout << bar << '\n';
  std::cout << "ft_bar contains:";
  std::cout << ft_bar << '\n';
#endif
  swap(foo, bar);
  swap(ft_foo, ft_bar);
  ASSERT_EQUAL(foo, ft_foo)
  ASSERT_EQUAL(bar, ft_bar)

#ifdef PRINT
  std::cout << "foo contains:";
  std::cout << foo << '\n';
  std::cout << "ft_foo contains:";
  std::cout << ft_foo << '\n';

  std::cout << "bar contains:";
  std::cout << bar << '\n';
  std::cout << "ft_bar contains:";
  std::cout << ft_bar << '\n';
#endif
}

static void TestClear() {
  std::deque<int> mydeque;
  mydeque.push_back(100);
  mydeque.push_back(200);
  mydeque.push_back(300);
  std::deque<int> ft_mydeque;
  ft_mydeque.push_back(100);
  ft_mydeque.push_back(200);
  ft_mydeque.push_back(300);
  ASSERT_EQUAL(mydeque, ft_mydeque)

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestClear--------\n";
  std::cout << "\033[0m";
  std::cout << "mydeque contains:";
  std::cout << mydeque << '\n';
  std::cout << "ft_mydeque contains:";
  std::cout << ft_mydeque << '\n';
#endif

  mydeque.clear();
  mydeque.push_back(1101);
  mydeque.push_back(2202);
  ft_mydeque.clear();
  ft_mydeque.push_back(1101);
  ft_mydeque.push_back(2202);
  ASSERT_EQUAL(mydeque, ft_mydeque)

#ifdef PRINT
  std::cout << "mydeque contains:";
  std::cout << mydeque << '\n';
  std::cout << "ft_mydeque contains:";
  std::cout << ft_mydeque << '\n';
#endif

}

static void TestRelationalOperators() {
  std::deque<int> foo(3, 100);   // three ints with a value of 100
  std::deque<int> bar(2, 200);   // two ints with a value of 200
  ft::deque<int> ft_foo(3, 100);   // three ints with a value of 100
  ft::deque<int> ft_bar(2, 200);   // two ints with a value of 200

  ASSERT_EQUAL((foo == bar), (ft_foo == ft_bar))
  ASSERT_EQUAL((foo != bar), (ft_foo != ft_bar))
  ASSERT_EQUAL((foo < bar), (ft_foo < ft_bar))
  ASSERT_EQUAL((foo > bar), (ft_foo > ft_bar))
  ASSERT_EQUAL((foo <= bar), (ft_foo <= ft_bar))
  ASSERT_EQUAL((foo >= bar), (ft_foo >= ft_bar))
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestRelationalOperators--------\n";
  std::cout << "\033[0m";
  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (ft_foo==ft_bar) std::cout << "ft_foo and ft_bar are equal\n";

  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (ft_foo!=ft_bar) std::cout << "ft_foo and ft_bar are not equal\n";

  if (foo< bar) std::cout << "foo is less than bar\n";
  if (ft_foo< ft_bar) std::cout << "ft_foo is less than ft_bar\n";

  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (ft_foo> ft_bar) std::cout << "ft_foo is greater than ft_bar\n";

  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (ft_foo<=ft_bar) std::cout << "ft_foo is less than or equal to ft_bar\n";

  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
  if (ft_foo>=ft_bar) std::cout << "ft_foo is greater than or equal to "
								"ft_bar\n";
#endif
}

void test_deque() {
  TestRunner tr;

  std::cout << "\033[1;36m";
  std::cout << "\n\n--------TEST DEQUE--------\n\n";
  std::cout << "\033[0m";
  RUN_TEST(tr, TestConstructor);
  RUN_TEST(tr, TestAssign);
  RUN_TEST(tr, TestAssign2);
  RUN_TEST(tr, TestIterators);
  RUN_TEST(tr, TestCapacity);
  RUN_TEST(tr, TestElementAccess);
  RUN_TEST(tr, TestPush);
  RUN_TEST(tr, TestPop);
  RUN_TEST(tr, TestInsert);
  RUN_TEST(tr, TestErase);
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestClear);
  RUN_TEST(tr, TestRelationalOperators);

}