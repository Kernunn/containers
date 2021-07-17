#include "set.hpp"
#include "test_runner.h"


template<typename Key, typename Compare>
bool operator==(const std::set<Key, Compare> &lhs, const ft::set<Key, Compare> &rhs) {
  typename std::set<Key, Compare>::const_iterator lbegin = lhs.begin();
  typename std::set<Key, Compare>::const_iterator lend = lhs.end();

  typename ft::set<Key, Compare>::const_iterator rbegin = rhs.begin();

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

static bool fncomp(int lhs, int rhs) { return lhs<rhs; }

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  { return lhs < rhs; }
};

static void TestConstructor()
{
  std::set<int> first;
  ft::set<int> ft_first;
  ASSERT_EQUAL(first, ft_first)

  int ints[] = {10,20,30,40,50};

  std::set<int> second(ints, ints+5);
  ft::set<int> ft_second(ints, ints+5);
  ASSERT_EQUAL(second, ft_second)

  std::set<int> third(second);
  ft::set<int> ft_third(ft_second);
  ASSERT_EQUAL(third, ft_third)

  std::set<int, classcomp> fourth;
  ft::set<int, classcomp> ft_fourth;

  bool (*fn_pt)(int, int) = fncomp;
  std::set<int, bool(*)(int, int)> fifth(fn_pt);
  ft::set<int, bool(*)(int, int)> ft_fifth(fn_pt);
}

static void TestAssignmentOperator() {
  int myints[]={ 12,82,37,64,15 };
  std::set<int> first (myints,myints+5);   // set with 5 ints
  std::set<int> second;                    // empty set
  ft::set<int> ft_first (myints,myints+5);   // set with 5 ints
  ft::set<int> ft_second;                    // empty set

  second = first;                          // now second contains the 5 ints
  ft_second = ft_first;                          // now second contains the 5 ints
  first = std::set<int>();                 // and first is empty
  ft_first = ft::set<int>();                 // and first is empty

  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second);
}


static void TestIterators() {
  int myints[]={ 12,82,37,64,15 };
  std::set<int> first (myints,myints+5);
  ft::set<int> ft_first (myints,myints+5);

  ft::set<int>::iterator FtFirst = ft_first.begin();
  ft::set<int>::iterator FtLast = ft_first.end();
  std::set<int>::iterator First = first.begin();
  std::set<int>::iterator Last = first.end();
  ft::set<int>::const_iterator cFtFirst = ft_first.begin();
  ft::set<int>::const_iterator cFtLast = ft_first.end();
  std::set<int>::const_iterator cFirst = first.begin();
  std::set<int>::const_iterator cLast = first.end();

  ft::set<int>::reverse_iterator rFtFirst = ft_first.rbegin();
  ft::set<int>::reverse_iterator rFtLast = ft_first.rend();
  std::set<int>::reverse_iterator rFirst = first.rbegin();
  std::set<int>::reverse_iterator rLast = first.rend();
  ft::set<int>::const_reverse_iterator crFtFirst = ft_first.rbegin();
  ft::set<int>::const_reverse_iterator crFtLast = ft_first.rend();
  std::set<int>::const_reverse_iterator crFirst = first.rbegin();
  std::set<int>::const_reverse_iterator crLast = first.rend();

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
  std::set<int> myset;
  ft::set<int> ft_myset;

  ASSERT_EQUAL(myset.empty(), ft_myset.empty())
  ASSERT_EQUAL(myset.size(), ft_myset.size())
  myset.insert(20);
  myset.insert(30);
  myset.insert(10);
  ft_myset.insert(20);
  ft_myset.insert(30);
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
  std::set<int> myset;
  std::set<int>::iterator it;
  std::pair<std::set<int>::iterator,bool> ret;
  ft::set<int> ft_myset;
  ft::set<int>::iterator ft_it;
  std::pair<ft::set<int>::iterator,bool> ft_ret;


  // set some initial values:
  for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50
  for (int i=1; i<=5; ++i) ft_myset.insert(i*10);    // set: 10 20 30 40 50

  ret = myset.insert(20);               // no new element inserted
  ft_ret = ft_myset.insert(20);               // no new element inserted

  ASSERT_EQUAL(ret.second, ft_ret.second)
  it = ret.first;
  ft_it = ft_ret.first;

  myset.insert (it,25);                 // max efficiency inserting
  myset.insert (it,24);                 // max efficiency inserting
  myset.insert (it,26);                 // no max efficiency inserting
  ft_myset.insert (ft_it,25);                 // max efficiency inserting
  ft_myset.insert (ft_it,24);                 // max efficiency inserting
  ft_myset.insert (ft_it,26);                 // no max efficiency inserting
  ASSERT_EQUAL(myset, ft_myset)

  int myints[]= {5,10,15};              // 10 already in set, not inserted
  myset.insert (myints,myints+3);
  ft_myset.insert (myints,myints+3);
  ASSERT_EQUAL(myset, ft_myset)
}

static void TestErase() {
  std::set<int> myset;
  std::set<int>::iterator it;
  ft::set<int> ft_myset;
  ft::set<int>::iterator ft_it;


  // insert some values:
  for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90
  for (int i=1; i<10; i++) ft_myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90
  ASSERT_EQUAL(myset, ft_myset)

  it = myset.begin();
  ++it;                                         // "it" points now to 20
  ft_it = ft_myset.begin();
  ++ft_it;

  myset.erase (it);
  ft_myset.erase (ft_it);
  ASSERT_EQUAL(myset, ft_myset)

  myset.erase (40);
  ft_myset.erase (40);
  ASSERT_EQUAL(myset, ft_myset)

  it = myset.find (60);
  myset.erase (it, myset.end());
  ft_it = ft_myset.find (60);
  ft_myset.erase (ft_it, ft_myset.end());
  ASSERT_EQUAL(myset, ft_myset)
}

static void TestSwap() {
  int myints[]={12,75,10,32,20,25};
  std::set<int> first (myints,myints+3);     // 10,12,75
  std::set<int> second (myints+3,myints+6);  // 20,25,32
  ft::set<int> ft_first (myints,myints+3);     // 10,12,75
  ft::set<int> ft_second (myints+3,myints+6);  // 20,25,32
  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second)
  first.swap(second);
  ft_first.swap(ft_second);
  ASSERT_EQUAL(first, ft_first)
  ASSERT_EQUAL(second, ft_second)
}

static void TestClear() {
  std::set<int> myset;
  ft::set<int> ft_myset;

  myset.insert(100);
  myset.insert(200);
  myset.insert(300);
  ft_myset.insert(100);
  ft_myset.insert(200);
  ft_myset.insert(300);

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
	std::set<int> myset;
	int highest;
	ft::set<int> ft_myset;
	int ft_highest;

	std::set<int>::key_compare mycomp = myset.key_comp();
	ft::set<int>::key_compare ft_mycomp = ft_myset.key_comp();

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
  {
	std::set<int> myset;
	int highest;
	ft::set<int> ft_myset;
	int ft_highest;

	std::set<int>::value_compare mycomp = myset.value_comp();
	ft::set<int>::value_compare ft_mycomp = ft_myset.value_comp();

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
	std::set<int> myset;
	std::set<int>::iterator it;
	ft::set<int> ft_myset;
	ft::set<int>::iterator ft_it;


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
	std::set<int> myset;
	ft::set<int> ft_myset;

	// set some initial values:
	for (int i=1; i<5; ++i) myset.insert(i*3);    // set: 3 6 9 12
	for (int i=1; i<5; ++i) ft_myset.insert(i*3);    // set: 3 6 9 12

	for (int i=0; i<10; ++i)
	{
	  ASSERT_EQUAL(myset.count(i), ft_myset.count(i))
	}
  }
  {
	std::set<int> myset;
	std::set<int>::iterator itlow,itup;
	ft::set<int> ft_myset;
	ft::set<int>::iterator ft_itlow,ft_itup;


	for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90
	for (int i=1; i<10; i++) ft_myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

	itlow=myset.lower_bound (30);                //       ^
	itup=myset.upper_bound (60);                 //                   ^
	ft_itlow=ft_myset.lower_bound (30);                //       ^
	ft_itup=ft_myset.upper_bound (60);                 //                   ^


	myset.erase(itlow,itup);                     // 10 20 70 80 90
	ft_myset.erase(ft_itlow,ft_itup);                     // 10 20 70 80 90
	ASSERT_EQUAL(myset, ft_myset)
  }
  {
	std::set<int> myset;
	ft::set<int> ft_myset;

	for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50
	for (int i=1; i<=5; i++) ft_myset.insert(i*10);   // myset: 10 20 30 40 50

	std::pair<std::set<int>::const_iterator,std::set<int>::const_iterator> ret;
	ret = myset.equal_range(30);
	std::pair<ft::set<int>::const_iterator,ft::set<int>::const_iterator> ft_ret;
	ft_ret = ft_myset.equal_range(30);

	ASSERT_EQUAL(*ret.first, *ft_ret.first)
	ASSERT_EQUAL(*ret.second, *ft_ret.second)
  }
}

void	test_set()
{
  TestRunner tr;

  std::cout << "\033[1;36m";
  std::cout << "\n\n--------TEST SET--------\n\n";
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
