#include "test_runner.h"
#include "multiset.hpp"

template<typename Key, typename Compare>
bool operator==(const std::multiset<Key, Compare> &lhs, const ft::multiset<Key, Compare>
&rhs) {
  typename std::multiset<Key, Compare>::const_iterator lbegin = lhs.begin();
  typename std::multiset<Key, Compare>::const_iterator lend = lhs.end();

  typename ft::multiset<Key, Compare>::const_iterator rbegin = rhs.begin();

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

static bool fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp {
  bool operator()(const int &lhs, const int &rhs) const { return lhs < rhs; }
};

static void TestConstructor() {
  std::multiset<int> first;
  ft::multiset<int> ft_first;
  ASSERT_EQUAL(first, ft_first)

  int ints[] = {10, 20, 30, 20, 20};

  std::multiset<int> second(ints, ints + 5);
  ft::multiset<int> ft_second(ints, ints + 5);
  ASSERT_EQUAL(second, ft_second)

  std::multiset<int> third(second);
  ft::multiset<int> ft_third(ft_second);
  ASSERT_EQUAL(third, ft_third)

  std::multiset<int, classcomp> fourth;
  ft::multiset<int, classcomp> ft_fourth;

  bool (*fn_pt)(int, int) = fncomp;
  std::multiset<int, bool (*)(int, int)> fifth(fn_pt);
  ft::multiset<int, bool (*)(int, int)> ft_fifth(fn_pt);
}

static void TestAssignmentOperator() {
  int myints[] = {19, 81, 36, 36, 19};
  std::multiset<int> first(myints, myints + 5);   // multiset with 5 ints
  std::multiset<int> second;                    // empty multiset
  ft::multiset<int> ft_first(myints, myints + 5);   // multiset with 5 ints
  ft::multiset<int> ft_second;                    // empty multiset

  second = first;                          // now second contains the 5 ints
  ft_second = ft_first;                          // now second contains the 5 ints
  first = std::multiset<int>();                 // and first is empty
  ft_first = ft::multiset<int>();                 // and first is empty

  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second);
}

static void TestIterators() {
  int myints[] = {42, 71, 71, 71, 12};
  std::multiset<int> first(myints, myints + 5);
  ft::multiset<int> ft_first(myints, myints + 5);

  ft::multiset<int>::iterator FtFirst = ft_first.begin();
  ft::multiset<int>::iterator FtLast = ft_first.end();
  std::multiset<int>::iterator First = first.begin();
  std::multiset<int>::iterator Last = first.end();
  ft::multiset<int>::const_iterator cFtFirst = ft_first.begin();
  ft::multiset<int>::const_iterator cFtLast = ft_first.end();
  std::multiset<int>::const_iterator cFirst = first.begin();
  std::multiset<int>::const_iterator cLast = first.end();

  ft::multiset<int>::reverse_iterator rFtFirst = ft_first.rbegin();
  ft::multiset<int>::reverse_iterator rFtLast = ft_first.rend();
  std::multiset<int>::reverse_iterator rFirst = first.rbegin();
  std::multiset<int>::reverse_iterator rLast = first.rend();
  ft::multiset<int>::const_reverse_iterator crFtFirst = ft_first.rbegin();
  ft::multiset<int>::const_reverse_iterator crFtLast = ft_first.rend();
  std::multiset<int>::const_reverse_iterator crFirst = first.rbegin();
  std::multiset<int>::const_reverse_iterator crLast = first.rend();

  for (int i = 0; i < 5; ++i) {
	ASSERT(FtFirst != FtLast)
	ASSERT(First != Last)
	ASSERT(cFtFirst != cFtLast)
	ASSERT(cFirst != cLast)
	ASSERT(rFtFirst != rFtLast)
	ASSERT(rFirst != rLast)
	ASSERT(crFtFirst != crFtLast)
	ASSERT(crFirst != crLast)

	ASSERT_EQUAL(*FtFirst, *First)
	ASSERT_EQUAL(*cFtFirst, *cFirst)
	ASSERT_EQUAL(*crFtFirst, *crFirst)
	ASSERT_EQUAL(*rFtFirst, *rFirst)

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
  std::multiset<int> myset;
  ft::multiset<int> ft_myset;

  ASSERT_EQUAL(myset.empty(), ft_myset.empty())
  ASSERT_EQUAL(myset.size(), ft_myset.size())
  myset.insert(10);
  myset.insert(20);
  myset.insert(10);
  ft_myset.insert(10);
  ft_myset.insert(20);
  ft_myset.insert(10);
  ASSERT_EQUAL(myset.empty(), ft_myset.empty())
  ASSERT_EQUAL(myset.size(), ft_myset.size())
  while (!ft_myset.empty()) {
	myset.erase(myset.begin());
	ft_myset.erase(ft_myset.begin());
  }
  ASSERT_EQUAL(myset.empty(), ft_myset.empty())
  ASSERT_EQUAL(myset.size(), ft_myset.size())
}

static void TestInsert() {
  std::multiset<int> myset;
  std::multiset<int>::iterator it;
  ft::multiset<int> ft_myset;
  ft::multiset<int>::iterator ft_it;

  // set some initial values:
  for (int i = 1; i <= 5; ++i) myset.insert(i * 10);    // set: 10 20 30 40 50
  for (int i = 1; i <= 5; ++i) ft_myset.insert(i * 10);    // set: 10 20 30 40 50

  it = myset.insert(25);               // no new element inserted
  ft_it = ft_myset.insert(25);               // no new element inserted

  int myints[] = {5, 10, 15};              // 10 already in set, not inserted
  myset.insert(myints, myints + 3);
  ft_myset.insert(myints, myints + 3);
  ASSERT_EQUAL(myset, ft_myset)
}

static void TestErase() {
  std::multiset<int> myset;
  std::multiset<int>::iterator it;
  ft::multiset<int> ft_myset;
  ft::multiset<int>::iterator ft_it;

  // insert some values:
  for (int i = 1; i < 10; i++) myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90
  for (int i = 1; i < 10; i++) ft_myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90
  ASSERT_EQUAL(myset, ft_myset)

  it = myset.begin();
  ++it;                                         // "it" points now to 20
  ft_it = ft_myset.begin();
  ++ft_it;

  myset.erase(it);
  ft_myset.erase(ft_it);
  ASSERT_EQUAL(myset, ft_myset)

  myset.erase(40);
  ft_myset.erase(40);
  ASSERT_EQUAL(myset, ft_myset)

  it = myset.find(50);
  myset.erase(it, myset.end());
  ft_it = ft_myset.find(50);
  ft_myset.erase(ft_it, ft_myset.end());
  ASSERT_EQUAL(myset, ft_myset)
}

static void TestSwap() {
  int myints[] = {19, 72, 4, 36, 20, 20};
  std::multiset<int> first(myints, myints + 3);
  std::multiset<int> second(myints + 3, myints + 6);
  ft::multiset<int> ft_first(myints, myints + 3);
  ft::multiset<int> ft_second(myints + 3, myints + 6);
  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second)
  first.swap(second);
  ft_first.swap(ft_second);
  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second)
}

static void TestClear() {
  std::multiset<int> myset;
  ft::multiset<int> ft_myset;

  myset.insert(11);
  myset.insert(42);
  myset.insert(11);
  ft_myset.insert(11);
  ft_myset.insert(42);
  ft_myset.insert(11);

  myset.clear();
  ft_myset.clear();
  ASSERT_EQUAL(myset, ft_myset)
  myset.insert(1101);
  myset.insert(2202);
  ft_myset.insert(1101);
  ft_myset.insert(2202);
  ASSERT_EQUAL(myset, ft_myset)
}

static void TestObservers() {
  {
	std::multiset<int> myset;
	int highest;
	ft::multiset<int> ft_myset;
	int ft_highest;

	std::multiset<int>::key_compare mycomp = myset.key_comp();
	ft::multiset<int>::key_compare ft_mycomp = ft_myset.key_comp();

	for (int i = 0; i <= 5; i++) myset.insert(i);
	for (int i = 0; i <= 5; i++) ft_myset.insert(i);

	highest = *myset.rbegin();
	std::multiset<int>::iterator it = myset.begin();
	ft_highest = *ft_myset.rbegin();
	ft::multiset<int>::iterator ft_it = ft_myset.begin();

	do {
	  ASSERT_EQUAL(*it, *ft_it)
	} while (ft_mycomp(*(++ft_it), ft_highest) && mycomp(*(++it), highest));
  }
  {
	std::multiset<int> myset;
	int highest;
	ft::multiset<int> ft_myset;
	int ft_highest;

	std::multiset<int>::value_compare mycomp = myset.value_comp();
	ft::multiset<int>::value_compare ft_mycomp = ft_myset.value_comp();

	for (int i = 0; i <= 5; i++) myset.insert(i);
	for (int i = 0; i <= 5; i++) ft_myset.insert(i);

	highest = *myset.rbegin();
	std::set<int>::iterator it = myset.begin();
	ft_highest = *ft_myset.rbegin();
	ft::set<int>::iterator ft_it = ft_myset.begin();

	do {
	  ASSERT_EQUAL(*it, *ft_it)
	} while (ft_mycomp(*(++ft_it), ft_highest) && mycomp(*(++it), highest));
  }
}

static void TestSetOperation() {
  {
	std::multiset<int> myset;
	std::multiset<int>::iterator it;
	ft::multiset<int> ft_myset;
	ft::multiset<int>::iterator ft_it;


	// set some initial values:
	for (int i = 1; i <= 5; i++) myset.insert(i * 10);    // set: 10 20 30 40 50
	for (int i = 1; i <= 5; i++) ft_myset.insert(i * 10);    // set: 10 20 30 40 50

	it = myset.find(20);
	ft_it = ft_myset.find(20);
	myset.erase(it);
	myset.erase(myset.find(40));
	ft_myset.erase(ft_it);
	ft_myset.erase(ft_myset.find(40));
	ASSERT_EQUAL(myset, ft_myset)
  }
  {
	int myints[] = {10, 73, 12, 22, 73, 73, 12};
	std::multiset<int> myset(myints, myints + 7);
	ft::multiset<int> ft_myset(myints, myints + 7);

	for (int i = 0; i < 100; ++i) {
	  ASSERT_EQUAL(myset.count(i), ft_myset.count(i))
	}
  }
  {
	std::multiset<int> myset;
	std::multiset<int>::iterator itlow, itup;
	ft::multiset<int> ft_myset;
	ft::multiset<int>::iterator ft_itlow, ft_itup;

	for (int i = 1; i < 10; i++) myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90
	for (int i = 1; i < 10; i++) ft_myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

	itlow = myset.lower_bound(30);                //       ^
	itup = myset.upper_bound(40);                 //                   ^
	ft_itlow = ft_myset.lower_bound(30);                //       ^
	ft_itup = ft_myset.upper_bound(40);                 //                   ^


	myset.erase(itlow, itup);                     // 10 20 70 80 90
	ft_myset.erase(ft_itlow, ft_itup);                     // 10 20 70 80 90
	ASSERT_EQUAL(myset, ft_myset)
  }
  {
	int myints[] = {77, 30, 16, 2, 30, 30};
	std::multiset<int> myset(myints, myints + 6);
	ft::multiset<int> ft_myset(myints, myints + 6);

	std::pair<std::multiset<int>::const_iterator, std::multiset<int>::const_iterator> ret;
	ret = myset.equal_range(30);
	std::pair<ft::multiset<int>::const_iterator, ft::multiset<int>::const_iterator> ft_ret;
	ft_ret = ft_myset.equal_range(30);

	myset.erase(ret.first, ret.second);
	ft_myset.erase(ft_ret.first, ft_ret.second);
	ASSERT_EQUAL(myset, ft_myset)
  }
}

void test_multiset() {
  TestRunner tr;

  std::cout << "\033[1;36m";
  std::cout << "\n\n--------TEST MULTISET--------\n\n";
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
