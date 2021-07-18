#include "test_runner.h"
#include "multimap.hpp"

template<typename Key, typename Value, typename Compare>
bool operator==(const std::multimap<Key, Value, Compare> &lhs, const ft::multimap<Key,
																				  Value,
																				  Compare>
&rhs) {
  typename std::multimap<Key, Value, Compare>::const_iterator lbegin = lhs.begin();
  typename std::multimap<Key, Value, Compare>::const_iterator lend = lhs.end();

  typename ft::multimap<Key, Value, Compare>::const_iterator rbegin = rhs.begin();

  if (lhs.size() != rhs.size())
	return false;
  while (lbegin != lend) {
	if (*lbegin != *rbegin)
	  return false;
	++lbegin;
	++rbegin;
  }
  return true;
}

static bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp {
  bool operator()(const char &lhs, const char &rhs) const { return lhs < rhs; }
};

static void TestConstructor() {
  std::multimap<char, int> first;
  ft::multimap<char, int> ft_first;
  ASSERT_EQUAL(first, ft_first)

  first.insert(std::pair<char, int>('a', 10));
  first.insert(std::pair<char, int>('b', 15));
  first.insert(std::pair<char, int>('b', 20));
  first.insert(std::pair<char, int>('c', 25));
  ft_first.insert(std::pair<char, int>('a', 10));
  ft_first.insert(std::pair<char, int>('b', 15));
  ft_first.insert(std::pair<char, int>('b', 20));
  ft_first.insert(std::pair<char, int>('c', 25));
  ASSERT_EQUAL(first, ft_first)

  std::multimap<char, int> second(first.begin(), first.end());
  ft::multimap<char, int> ft_second(ft_first.begin(), ft_first.end());
  ASSERT_EQUAL(second, ft_second)

  std::multimap<char, int> third(second);
  ft::multimap<char, int> ft_third(ft_second);
  ASSERT_EQUAL(third, ft_third)

  std::multimap<char, int, classcomp> fourth;
  ft::multimap<char, int, classcomp> ft_fourth;
  ASSERT_EQUAL(fourth, ft_fourth)

  bool (*fn_pt)(char, char) = fncomp;
  std::multimap<char, int, bool (*)(char, char)> fifth(fn_pt);
  ft::multimap<char, int, bool (*)(char, char)> ft_fifth(fn_pt);
  ASSERT_EQUAL(fifth, ft_fifth)
}

static void TestAssignmentOperator() {
  std::multimap<char, int> first;
  std::multimap<char, int> second;
  ft::multimap<char, int> ft_first;
  ft::multimap<char, int> ft_second;

  first.insert(std::pair<char, int>('x', 32));
  first.insert(std::pair<char, int>('y', 64));
  first.insert(std::pair<char, int>('y', 96));
  first.insert(std::pair<char, int>('z', 128));
  ft_first.insert(std::pair<char, int>('x', 32));
  ft_first.insert(std::pair<char, int>('y', 64));
  ft_first.insert(std::pair<char, int>('y', 96));
  ft_first.insert(std::pair<char, int>('z', 128));

  second = first;
  ft_second = ft_first;

  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second);
}

static void TestIterators() {
  std::multimap<char, int> first;
  ft::multimap<char, int> ft_first;

  first.insert(std::pair<char, int>('a', 10));
  first.insert(std::pair<char, int>('b', 20));
  first.insert(std::pair<char, int>('b', 150));
  ft_first.insert(std::pair<char, int>('a', 10));
  ft_first.insert(std::pair<char, int>('b', 20));
  ft_first.insert(std::pair<char, int>('b', 150));

  ft::multimap<char, int>::iterator FtFirst = ft_first.begin();
  ft::multimap<char, int>::iterator FtLast = ft_first.end();
  std::multimap<char, int>::iterator First = first.begin();
  std::multimap<char, int>::iterator Last = first.end();
  ft::multimap<char, int>::const_iterator cFtFirst = ft_first.begin();
  ft::multimap<char, int>::const_iterator cFtLast = ft_first.end();
  std::multimap<char, int>::const_iterator cFirst = first.begin();
  std::multimap<char, int>::const_iterator cLast = first.end();

  ft::multimap<char, int>::reverse_iterator rFtFirst = ft_first.rbegin();
  ft::multimap<char, int>::reverse_iterator rFtLast = ft_first.rend();
  std::multimap<char, int>::reverse_iterator rFirst = first.rbegin();
  std::multimap<char, int>::reverse_iterator rLast = first.rend();
  ft::multimap<char, int>::const_reverse_iterator crFtFirst = ft_first.rbegin();
  ft::multimap<char, int>::const_reverse_iterator crFtLast = ft_first.rend();
  std::multimap<char, int>::const_reverse_iterator crFirst = first.rbegin();
  std::multimap<char, int>::const_reverse_iterator crLast = first.rend();

  for (int i = 0; i < 2; ++i) {
	ASSERT(FtFirst != FtLast)
	ASSERT(First != Last)
	ASSERT(cFtFirst != cFtLast)
	ASSERT(cFirst != cLast)
	ASSERT(rFtFirst != rFtLast)
	ASSERT(rFirst != rLast)
	ASSERT(crFtFirst != crFtLast)
	ASSERT(crFirst != crLast)

	ASSERT_EQUAL(FtFirst->first, First->first)
	ASSERT_EQUAL(cFtFirst->first, cFirst->first)
	ASSERT_EQUAL(crFtFirst->first, crFirst->first)
	ASSERT_EQUAL(rFtFirst->first, rFirst->first)

	ASSERT_EQUAL(FtFirst->second, First->second)
	ASSERT_EQUAL(cFtFirst->second, cFirst->second)
	ASSERT_EQUAL(crFtFirst->second, crFirst->second)
	ASSERT_EQUAL(rFtFirst->second, rFirst->second)

	++FtFirst;
	++First;
	cFirst++;
	cFtFirst++;
	++rFtFirst;
	++rFirst;
	crFtFirst++;
	crFirst++;
  }
}

static void TestCapacity() {
  std::multimap<char, int> first;
  ft::multimap<char, int> ft_first;

  ASSERT_EQUAL(first.empty(), ft_first.empty())
  ASSERT_EQUAL(first.size(), ft_first.size())
  first.insert(std::pair<char, int>('b', 101));
  first.insert(std::pair<char, int>('b', 202));
  first.insert(std::pair<char, int>('q', 505));
  ft_first.insert(std::pair<char, int>('b', 101));
  ft_first.insert(std::pair<char, int>('b', 202));
  ft_first.insert(std::pair<char, int>('q', 505));

  ASSERT_EQUAL(first.size(), ft_first.size())
  while (!ft_first.empty()) {
	first.erase(first.begin());
	ft_first.erase(ft_first.begin());
  }
  ASSERT_EQUAL(first.empty(), ft_first.empty())
  ASSERT_EQUAL(first.size(), ft_first.size())
}

static void TestInsert() {
  std::multimap<char, int> first;
  ft::multimap<char, int> ft_first;
  std::multimap<char, int>::iterator it;
  ft::multimap<char, int>::iterator ft_it;

  first.insert(std::pair<char, int>('a', 100));
  first.insert(std::pair<char, int>('z', 150));
  it = first.insert(std::pair<char, int>('b', 75));
  ft_first.insert(std::pair<char, int>('a', 100));
  ft_first.insert(std::pair<char, int>('z', 150));
  ft_it = ft_first.insert(std::pair<char, int>('b', 75));
  ASSERT_EQUAL(first, ft_first);

  first.insert(it, std::pair<char, int>('c', 300));
  first.insert(it, std::pair<char, int>('z', 150));
  ft_first.insert(ft_it, std::pair<char, int>('c', 300));
  ft_first.insert(ft_it, std::pair<char, int>('z', 150));
  ASSERT_EQUAL(first, ft_first);

  std::multimap<char, int> second;
  ft::multimap<char, int> ft_second;
  second.insert(first.begin(), first.find('c'));
  ft_second.insert(ft_first.begin(), ft_first.find('c'));
  ASSERT_EQUAL(second, ft_second)
}

static void TestErase() {
  std::multimap<char, int> first;
  ft::multimap<char, int> ft_first;
  std::multimap<char, int>::iterator it;
  ft::multimap<char, int>::iterator ft_it;

  first.insert(std::pair<char, int>('a', 10));
  first.insert(std::pair<char, int>('b', 20));
  first.insert(std::pair<char, int>('b', 30));
  first.insert(std::pair<char, int>('c', 40));
  first.insert(std::pair<char, int>('d', 50));
  first.insert(std::pair<char, int>('d', 60));
  first.insert(std::pair<char, int>('e', 70));
  first.insert(std::pair<char, int>('f', 80));
  ft_first.insert(std::pair<char, int>('a', 10));
  ft_first.insert(std::pair<char, int>('b', 20));
  ft_first.insert(std::pair<char, int>('b', 30));
  ft_first.insert(std::pair<char, int>('c', 40));
  ft_first.insert(std::pair<char, int>('d', 50));
  ft_first.insert(std::pair<char, int>('d', 60));
  ft_first.insert(std::pair<char, int>('e', 70));
  ft_first.insert(std::pair<char, int>('f', 80));

  it = first.find('b');
  ft_it = ft_first.find('b');
  first.erase(it);
  ft_first.erase(ft_it);
  ASSERT_EQUAL(first, ft_first)

  first.erase('d');
  ft_first.erase('d');
  ASSERT_EQUAL(first, ft_first)

  it = first.find('e');
  ft_it = ft_first.find('e');
  first.erase(it, first.end());
  ft_first.erase(ft_it, ft_first.end());
  ASSERT_EQUAL(first, ft_first)
}

static void TestSwap() {
  std::multimap<char, int> foo, bar;
  ft::multimap<char, int> ft_foo, ft_bar;

  foo.insert(std::pair<char, int>('x', 100));
  foo.insert(std::pair<char, int>('y', 200));
  bar.insert(std::pair<char, int>('a', 11));
  bar.insert(std::pair<char, int>('b', 22));
  bar.insert(std::pair<char, int>('a', 55));
  ft_foo.insert(std::pair<char, int>('x', 100));
  ft_foo.insert(std::pair<char, int>('y', 200));
  ft_bar.insert(std::pair<char, int>('a', 11));
  ft_bar.insert(std::pair<char, int>('b', 22));
  ft_bar.insert(std::pair<char, int>('a', 55));

  ASSERT_EQUAL(foo, ft_foo)
  ASSERT_EQUAL(bar, ft_bar)

  foo.swap(bar);
  ft_foo.swap(ft_bar);
  ASSERT_EQUAL(foo, ft_foo)
  ASSERT_EQUAL(bar, ft_bar)
}

static void TestClear() {
  std::multimap<char, int> foo;
  ft::multimap<char, int> ft_foo;

  foo.insert(std::pair<char, int>('b', 80));
  foo.insert(std::pair<char, int>('b', 120));
  foo.insert(std::pair<char, int>('q', 360));
  ft_foo.insert(std::pair<char, int>('b', 80));
  ft_foo.insert(std::pair<char, int>('b', 120));
  ft_foo.insert(std::pair<char, int>('q', 360));

  ASSERT_EQUAL(foo, ft_foo)
  foo.clear();
  ft_foo.clear();
  ASSERT_EQUAL(foo, ft_foo)

  foo.insert(std::pair<char, int>('a', 11));
  foo.insert(std::pair<char, int>('x', 22));
  ft_foo.insert(std::pair<char, int>('a', 11));
  ft_foo.insert(std::pair<char, int>('x', 22));
  ASSERT_EQUAL(foo, ft_foo)
}

static void TestObservers() {
  std::multimap<char, int> foo;
  ft::multimap<char, int> ft_foo;
  std::multimap<char, int>::key_compare mycomp = foo.key_comp();
  ft::multimap<char, int>::key_compare ft_mycomp = ft_foo.key_comp();

  foo.insert(std::pair<char, int>('a', 100));
  foo.insert(std::pair<char, int>('b', 200));
  foo.insert(std::pair<char, int>('b', 211));
  foo.insert(std::pair<char, int>('c', 300));
  ft_foo.insert(std::pair<char, int>('a', 100));
  ft_foo.insert(std::pair<char, int>('b', 200));
  ft_foo.insert(std::pair<char, int>('b', 211));
  ft_foo.insert(std::pair<char, int>('c', 300));
  ASSERT_EQUAL(foo, ft_foo)

  char highest = foo.rbegin()->first;
  char ft_highest = ft_foo.rbegin()->first;
  ASSERT_EQUAL(highest, ft_highest)

  std::multimap<char, int>::iterator it = foo.begin();
  ft::multimap<char, int>::iterator ft_it = ft_foo.begin();

  do {
	ASSERT_EQUAL(it->first, ft_it->first)
	ASSERT_EQUAL(it->second, ft_it->second)
  } while (ft_mycomp((*ft_it++).first, ft_highest) && mycomp((*it++).first, highest));
  ASSERT(ft_it == ft_foo.end())

  foo.clear();
  ft_foo.clear();
  foo.insert(std::pair<char, int>('x', 101));
  foo.insert(std::pair<char, int>('y', 202));
  foo.insert(std::pair<char, int>('y', 252));
  foo.insert(std::pair<char, int>('z', 303));
  ft_foo.insert(std::pair<char, int>('x', 101));
  ft_foo.insert(std::pair<char, int>('y', 202));
  ft_foo.insert(std::pair<char, int>('y', 252));
  ft_foo.insert(std::pair<char, int>('z', 303));

  std::pair<char, int> high = *foo.rbegin();
  std::pair<char, int> ft_high = *ft_foo.rbegin();

  it = foo.begin();
  ft_it = ft_foo.begin();

  do {
	ASSERT_EQUAL(it->first, ft_it->first)
	ASSERT_EQUAL(it->second, ft_it->second)
  } while (ft_foo.value_com()(*ft_it++, ft_high) && foo.value_comp()(*it++, high));
  ASSERT(ft_it == ft_foo.end())
}

static void TestSetOperation() {
  {
	std::multimap<char, int> mymap;
	std::multimap<char, int>::iterator it;
	ft::multimap<char, int> ft_mymap;
	ft::multimap<char, int>::iterator ft_it;

	mymap.insert(std::pair<char, int>('x', 10));
	mymap.insert(std::pair<char, int>('y', 20));
	mymap.insert(std::pair<char, int>('z', 30));
	mymap.insert(std::pair<char, int>('z', 40));
	ft_mymap.insert(std::pair<char, int>('x', 10));
	ft_mymap.insert(std::pair<char, int>('y', 20));
	ft_mymap.insert(std::pair<char, int>('z', 30));
	ft_mymap.insert(std::pair<char, int>('z', 40));

	it = mymap.find('x');
	ft_it = ft_mymap.find('x');
	ASSERT_EQUAL(it->first, ft_it->first)
	ASSERT_EQUAL(it->second, ft_it->second)
	if (it != mymap.end())
	  mymap.erase(it);
	if (ft_it != ft_mymap.end())
	  ft_mymap.erase(ft_it);

	ASSERT_EQUAL(mymap.find('y')->second, ft_mymap.find('y')->second)
	ASSERT_EQUAL(mymap.find('z')->second, ft_mymap.find('z')->second)
  }
  {
	std::multimap<char, int> mymap;
	ft::multimap<char, int> ft_mymap;

	mymap.insert(std::pair<char, int>('x', 50));
	mymap.insert(std::pair<char, int>('y', 100));
	mymap.insert(std::pair<char, int>('y', 150));
	mymap.insert(std::pair<char, int>('y', 200));
	mymap.insert(std::pair<char, int>('z', 250));
	mymap.insert(std::pair<char, int>('z', 300));
	ft_mymap.insert(std::pair<char, int>('x', 50));
	ft_mymap.insert(std::pair<char, int>('y', 100));
	ft_mymap.insert(std::pair<char, int>('y', 150));
	ft_mymap.insert(std::pair<char, int>('y', 200));
	ft_mymap.insert(std::pair<char, int>('z', 250));
	ft_mymap.insert(std::pair<char, int>('z', 300));

	for (char c = 'a'; c < 'z'; c++) {ASSERT_EQUAL(mymap.count(c), ft_mymap.count(c))}
  }
  {
	std::multimap<char, int> mymap;
	std::multimap<char, int>::iterator itlow, itup;
	ft::multimap<char, int> ft_mymap;
	ft::multimap<char, int>::iterator ft_itlow, ft_itup;

	mymap.insert(std::pair<char, int>('a', 10));
	mymap.insert(std::pair<char, int>('b', 121));
	mymap.insert(std::pair<char, int>('c', 1001));
	mymap.insert(std::pair<char, int>('c', 2002));
	mymap.insert(std::pair<char, int>('d', 11011));
	mymap.insert(std::pair<char, int>('e', 44));
	ft_mymap.insert(std::pair<char, int>('a', 10));
	ft_mymap.insert(std::pair<char, int>('b', 121));
	ft_mymap.insert(std::pair<char, int>('c', 1001));
	ft_mymap.insert(std::pair<char, int>('c', 2002));
	ft_mymap.insert(std::pair<char, int>('d', 11011));
	ft_mymap.insert(std::pair<char, int>('e', 44));

	itlow = mymap.lower_bound('b');  // itlow points to b
	itup = mymap.upper_bound('d');   // itup points to e (not d!)
	ft_itlow = ft_mymap.lower_bound('b');  // itlow points to b
	ft_itup = ft_mymap.upper_bound('d');   // itup points to e (not d!)
	ASSERT_EQUAL(itlow->first, ft_itlow->first)
	ASSERT_EQUAL(itup->first, ft_itup->first)
	mymap.erase(itlow, itup);        // erases [itlow,itup)
	ft_mymap.erase(ft_itlow, ft_itup);        // erases [itlow,itup)
	ASSERT_EQUAL(mymap, ft_mymap)
  }
  {
	std::multimap<char, int> mymap;
	ft::multimap<char, int> ft_mymap;

	mymap.insert(std::pair<char, int>('a', 10));
	mymap.insert(std::pair<char, int>('b', 20));
	mymap.insert(std::pair<char, int>('b', 30));
	mymap.insert(std::pair<char, int>('b', 40));
	mymap.insert(std::pair<char, int>('c', 50));
	mymap.insert(std::pair<char, int>('c', 60));
	mymap.insert(std::pair<char, int>('d', 60));
	ft_mymap.insert(std::pair<char, int>('a', 10));
	ft_mymap.insert(std::pair<char, int>('b', 20));
	ft_mymap.insert(std::pair<char, int>('b', 30));
	ft_mymap.insert(std::pair<char, int>('b', 40));
	ft_mymap.insert(std::pair<char, int>('c', 50));
	ft_mymap.insert(std::pair<char, int>('c', 60));
	ft_mymap.insert(std::pair<char, int>('d', 60));

	std::pair<std::multimap<char, int>::iterator, std::multimap<char, int>::iterator> ret;
	ret = mymap.equal_range('b');
	std::pair<ft::multimap<char, int>::iterator, ft::multimap<char, int>::iterator> ft_ret;
	ft_ret = ft_mymap.equal_range('b');
	std::multimap<char, int>::iterator it = ret.first;
	ft::multimap<char, int>::iterator ft_it = ft_ret.first;
	for (; it != ret.second; ++it, ++ft_it) {
	  ASSERT_EQUAL(ret.first->first, ft_ret.first->first)
	  ASSERT_EQUAL(ret.second->first, ft_ret.second->first)
	}
  }
}

void test_multimap() {
  TestRunner tr;

  std::cout << "\033[1;36m";
  std::cout << "\n\n--------TEST MULTIMAP--------\n\n";
  std::cout << "\033[0m";
  RUN_TEST(tr, TestConstructor);
  RUN_TEST(tr, TestAssignmentOperator);
  RUN_TEST(tr, TestIterators);
  RUN_TEST(tr, TestCapacity);
  RUN_TEST(tr, TestInsert);
  RUN_TEST(tr, TestErase);
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestClear);
  RUN_TEST(tr, TestObservers);
  RUN_TEST(tr, TestSetOperation);
}
