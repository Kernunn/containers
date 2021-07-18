#include "test_runner.h"
#include <map>
#include "map.hpp"

template<typename Key, typename Value, typename Compare>
bool operator==(const std::map<Key, Value, Compare> &lhs,
				const ft::map<Key, Value, Compare>
				&rhs) {
  typename std::map<Key, Value, Compare>::const_iterator lbegin = lhs.begin();
  typename std::map<Key, Value, Compare>::const_iterator lend = lhs.end();

  typename ft::map<Key, Value, Compare>::const_iterator rbegin = rhs.begin();

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
  std::map<char, int> first;
  ft::map<char, int> ft_first;
  ASSERT_EQUAL(first, ft_first)

  first['a'] = 10;
  first['b'] = 30;
  first['c'] = 50;
  first['d'] = 70;
  ft_first['a'] = 10;
  ft_first['b'] = 30;
  ft_first['c'] = 50;
  ft_first['d'] = 70;

  std::map<char, int> second(first.begin(), first.end());
  ft::map<char, int> ft_second(ft_first.begin(), ft_first.end());
  ASSERT_EQUAL(second, ft_second)

  std::map<char, int> third(second);
  ft::map<char, int> ft_third(ft_second);
  ASSERT_EQUAL(third, ft_third)

  std::map<char, int, classcomp> fourth;
  ft::map<char, int, classcomp> ft_fourth;
  ASSERT_EQUAL(fourth, ft_fourth)

  bool (*fn_pt)(char, char) = fncomp;
  std::map<char, int, bool (*)(char, char)> fifth(fn_pt);
  ft::map<char, int, bool (*)(char, char)> ft_fifth(fn_pt);
  ASSERT_EQUAL(fifth, ft_fifth)
}

static void TestAssignmentOperator() {
  std::map<char, int> first;
  std::map<char, int> second;
  ft::map<char, int> ft_first;
  ft::map<char, int> ft_second;

  first['x'] = 8;
  first['y'] = 16;
  first['z'] = 32;
  ft_first['x'] = 8;
  ft_first['y'] = 16;
  ft_first['z'] = 32;

  second = first;
  ft_second = ft_first;

  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second);
}

static void TestIterators() {
  std::map<char, int> first;
  ft::map<char, int> ft_first;

  first['b'] = 100;
  first['a'] = 200;
  first['c'] = 300;
  ft_first['b'] = 100;
  ft_first['a'] = 200;
  ft_first['c'] = 300;

  ft::map<char, int>::iterator FtFirst = ft_first.begin();
  ft::map<char, int>::iterator FtLast = ft_first.end();
  std::map<char, int>::iterator First = first.begin();
  std::map<char, int>::iterator Last = first.end();
  ft::map<char, int>::const_iterator cFtFirst = ft_first.begin();
  ft::map<char, int>::const_iterator cFtLast = ft_first.end();
  std::map<char, int>::const_iterator cFirst = first.begin();
  std::map<char, int>::const_iterator cLast = first.end();

  ft::map<char, int>::reverse_iterator rFtFirst = ft_first.rbegin();
  ft::map<char, int>::reverse_iterator rFtLast = ft_first.rend();
  std::map<char, int>::reverse_iterator rFirst = first.rbegin();
  std::map<char, int>::reverse_iterator rLast = first.rend();
  ft::map<char, int>::const_reverse_iterator crFtFirst = ft_first.rbegin();
  ft::map<char, int>::const_reverse_iterator crFtLast = ft_first.rend();
  std::map<char, int>::const_reverse_iterator crFirst = first.rbegin();
  std::map<char, int>::const_reverse_iterator crLast = first.rend();

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
  std::map<char, int> first;
  ft::map<char, int> ft_first;

  ASSERT_EQUAL(first.empty(), ft_first.empty())
  first['a'] = 10;
  first['b'] = 20;
  first['c'] = 30;
  ft_first['a'] = 10;
  ft_first['b'] = 20;
  ft_first['c'] = 30;

  ASSERT_EQUAL(first.size(), ft_first.size())
  while (!ft_first.empty()) {
	first.erase(first.begin());
	ft_first.erase(ft_first.begin());
  }
  ASSERT_EQUAL(first.empty(), ft_first.empty())
  ASSERT_EQUAL(first.size(), ft_first.size())
}

static void TestOperatorAccess() {
  std::map<char, std::string> first;
  ft::map<char, std::string> ft_first;

  first['a'] = "an element";
  first['b'] = "another element";
  first['c'] = first['b'];
  ft_first['a'] = "an element";
  ft_first['b'] = "another element";
  ft_first['c'] = ft_first['b'];
  ASSERT_EQUAL(first['a'], ft_first['a'])
  ASSERT_EQUAL(first['b'], ft_first['b'])
  ASSERT_EQUAL(first['c'], ft_first['c'])
  ASSERT_EQUAL(first['d'], ft_first['d'])

  ASSERT_EQUAL(first.size(), ft_first.size())
}

static void TestInsert() {
  std::map<char, int> first;
  ft::map<char, int> ft_first;

  first.insert(std::pair<char, int>('a', 100));
  first.insert(std::pair<char, int>('z', 200));
  ft_first.insert(std::pair<char, int>('a', 100));
  ft_first.insert(std::pair<char, int>('z', 200));

  ASSERT_EQUAL(first, ft_first);
  std::pair<std::map<char, int>::iterator, bool> ret;
  std::pair<ft::map<char, int>::iterator, bool> ft_ret;
  ret = first.insert(std::pair<char, int>('z', 500));
  ft_ret = ft_first.insert(std::pair<char, int>('z', 500));
  ASSERT_EQUAL(ret.second, ft_ret.second);
  ASSERT_EQUAL(first, ft_first)

  std::map<char, int>::iterator it = first.begin();
  ft::map<char, int>::iterator ft_it = ft_first.begin();
  first.insert(it, std::pair<char, int>('b', 300));
  first.insert(it, std::pair<char, int>('c', 400));
  ft_first.insert(ft_it, std::pair<char, int>('b', 300));
  ft_first.insert(ft_it, std::pair<char, int>('c', 400));
  ASSERT_EQUAL(first, ft_first)

  std::map<char, int> second;
  ft::map<char, int> ft_second;
  second.insert(first.begin(), first.find('c'));
  ft_second.insert(ft_first.begin(), ft_first.find('c'));
  ASSERT_EQUAL(second, ft_second)
}

static void TestErase() {
  std::map<char, int> first;
  ft::map<char, int> ft_first;
  std::map<char, int>::iterator it;
  ft::map<char, int>::iterator ft_it;

  first['a'] = 10;
  first['b'] = 20;
  first['c'] = 30;
  first['d'] = 40;
  first['e'] = 50;
  first['f'] = 60;
  ft_first['a'] = 10;
  ft_first['b'] = 20;
  ft_first['c'] = 30;
  ft_first['d'] = 40;
  ft_first['e'] = 50;
  ft_first['f'] = 60;

  it = first.find('b');
  ft_it = ft_first.find('b');
  first.erase(it);
  ft_first.erase(ft_it);
  ASSERT_EQUAL(first, ft_first)

  first.erase('c');
  ft_first.erase('c');
  ASSERT_EQUAL(first, ft_first)

  it = first.find('c');
  ft_it = ft_first.find('c');
  first.erase(it, first.end());
  ft_first.erase(ft_it, ft_first.end());
  ASSERT_EQUAL(first, ft_first)
}

static void TestSwap() {
  std::map<char, int> foo, bar;
  ft::map<char, int> ft_foo, ft_bar;

  foo['x'] = 100;
  foo['y'] = 200;
  ft_foo['x'] = 100;
  ft_foo['y'] = 200;

  bar['a'] = 11;
  bar['b'] = 22;
  bar['c'] = 33;
  ft_bar['a'] = 11;
  ft_bar['b'] = 22;
  ft_bar['c'] = 33;
  ASSERT_EQUAL(foo, ft_foo)
  ASSERT_EQUAL(bar, ft_bar)

  foo.swap(bar);
  ft_foo.swap(ft_bar);
  ASSERT_EQUAL(foo, ft_foo)
  ASSERT_EQUAL(bar, ft_bar)
}

static void TestClear() {
  std::map<char, int> foo;
  ft::map<char, int> ft_foo;

  foo['x'] = 100;
  foo['y'] = 200;
  foo['z'] = 300;
  ft_foo['x'] = 100;
  ft_foo['y'] = 200;
  ft_foo['z'] = 300;

  ASSERT_EQUAL(foo, ft_foo)
  foo.clear();
  ft_foo.clear();
  ASSERT_EQUAL(foo, ft_foo)

  foo['a'] = 1101;
  foo['b'] = 2202;
  ft_foo['a'] = 1101;
  ft_foo['b'] = 2202;
  ASSERT_EQUAL(foo, ft_foo)
}

static void TestObservers() {
  std::map<char, int> foo;
  ft::map<char, int> ft_foo;
  std::map<char, int>::key_compare mycomp = foo.key_comp();
  ft::map<char, int>::key_compare ft_mycomp = ft_foo.key_comp();

  foo['a'] = 100;
  foo['b'] = 200;
  foo['c'] = 300;
  ft_foo['a'] = 100;
  ft_foo['b'] = 200;
  ft_foo['c'] = 300;
  ASSERT_EQUAL(foo, ft_foo)

  char highest = foo.rbegin()->first;
  char ft_highest = ft_foo.rbegin()->first;
  ASSERT_EQUAL(highest, ft_highest)

  std::map<char, int>::iterator it = foo.begin();
  ft::map<char, int>::iterator ft_it = ft_foo.begin();

  do {
	ASSERT_EQUAL(it->first, ft_it->first)
	ASSERT_EQUAL(it->second, ft_it->second)
  } while (ft_mycomp((*ft_it++).first, ft_highest) && mycomp((*it++).first, highest));
  ASSERT(ft_it == ft_foo.end())

  foo.clear();
  ft_foo.clear();
  foo['x'] = 1001;
  foo['y'] = 2002;
  foo['z'] = 3003;
  ft_foo['x'] = 1001;
  ft_foo['y'] = 2002;
  ft_foo['z'] = 3003;

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
	std::map<char, int> mymap;
	std::map<char, int>::iterator it;
	ft::map<char, int> ft_mymap;
	ft::map<char, int>::iterator ft_it;

	mymap['a'] = 50;
	mymap['b'] = 100;
	mymap['c'] = 150;
	mymap['d'] = 200;
	ft_mymap['a'] = 50;
	ft_mymap['b'] = 100;
	ft_mymap['c'] = 150;
	ft_mymap['d'] = 200;

	it = mymap.find('b');
	ft_it = ft_mymap.find('b');
	ASSERT_EQUAL(it->first, ft_it->first)
	ASSERT_EQUAL(it->second, ft_it->second)
	if (it != mymap.end())
	  mymap.erase(it);
	if (ft_it != ft_mymap.end())
	  ft_mymap.erase(ft_it);

	ASSERT_EQUAL(mymap.find('a')->second, ft_mymap.find('a')->second)
	ASSERT_EQUAL(mymap.find('c')->second, ft_mymap.find('c')->second)
	ASSERT_EQUAL(mymap.find('d')->second, ft_mymap.find('d')->second)
  }
  {
	std::map<char, int> mymap;
	ft::map<char, int> ft_mymap;
	char c;

	mymap['a'] = 101;
	mymap['c'] = 202;
	mymap['f'] = 303;
	ft_mymap['a'] = 101;
	ft_mymap['c'] = 202;
	ft_mymap['f'] = 303;

	for (c = 'a'; c < 'h'; c++) {ASSERT_EQUAL(mymap.count(c), ft_mymap.count(c))}
  }
  {
	std::map<char, int> mymap;
	std::map<char, int>::iterator itlow, itup;
	ft::map<char, int> ft_mymap;
	ft::map<char, int>::iterator ft_itlow, ft_itup;

	mymap['a'] = 20;
	mymap['b'] = 40;
	mymap['c'] = 60;
	mymap['d'] = 80;
	mymap['e'] = 100;
	ft_mymap['a'] = 20;
	ft_mymap['b'] = 40;
	ft_mymap['c'] = 60;
	ft_mymap['d'] = 80;
	ft_mymap['e'] = 100;

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
	std::map<char, int> mymap;
	ft::map<char, int> ft_mymap;

	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;
	ft_mymap['a'] = 10;
	ft_mymap['b'] = 20;
	ft_mymap['c'] = 30;

	std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret;
	ret = mymap.equal_range('b');
	std::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ft_ret;
	ft_ret = ft_mymap.equal_range('b');

	ASSERT_EQUAL(ret.first->first, ft_ret.first->first)
	ASSERT_EQUAL(ret.second->first, ft_ret.second->first)
  }
}

void test_map() {
  TestRunner tr;

  std::cout << "\033[1;36m";
  std::cout << "\n\n--------TEST MAP--------\n\n";
  std::cout << "\033[0m";
  RUN_TEST(tr, TestConstructor);
  RUN_TEST(tr, TestAssignmentOperator);
  RUN_TEST(tr, TestIterators);
  RUN_TEST(tr, TestCapacity);
  RUN_TEST(tr, TestOperatorAccess);
  RUN_TEST(tr, TestInsert);
  RUN_TEST(tr, TestErase);
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestClear);
  RUN_TEST(tr, TestObservers);
  RUN_TEST(tr, TestSetOperation);
}
