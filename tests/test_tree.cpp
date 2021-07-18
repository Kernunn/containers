#include "test_runner.h"
#include "tree.hpp"

typedef int key;
typedef std::pair<int, int> value_type;
typedef _Select1st<value_type> keyOfValue;
typedef std::less<int> compare;
typedef ft::Rb_tree<key, value_type, keyOfValue, compare>::iterator iter;

static void TestConstructor() {
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree1;
  greater<int> key_compare = std::greater<int>();
  ft::Rb_tree<key, value_type, keyOfValue, greater<int> > tree2(key_compare);

  ASSERT_EQUAL(tree2.size(), size_t(0))
  tree1.insert_unique(value_type(1, 1));
  tree1.insert_unique(value_type(2, 2));
  tree1.insert_unique(value_type(3, 3));
  tree1.insert_unique(value_type(4, 4));
  tree1.insert_unique(value_type(5, 5));
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree3(tree1);
  ASSERT_EQUAL(tree1, tree3)
  tree2.insert_unique(value_type(1, 1));
  tree2.insert_unique(value_type(2, 2));
  tree2.insert_unique(value_type(3, 3));
  tree2.insert_unique(value_type(4, 4));
  tree2.insert_unique(value_type(5, 5));
  std::vector<int> tree1vect;
  std::vector<int> tree2vect;
  ft::Rb_tree<key, value_type, keyOfValue, compare>::const_iterator first = tree1.begin();
  ft::Rb_tree<key, value_type, keyOfValue, compare>::const_iterator last = tree1.end();
  ft::Rb_tree<key, value_type, keyOfValue, greater<int> >::const_reverse_iterator
	  fir = tree2
	  .rbegin();
  ft::Rb_tree<key, value_type, keyOfValue, greater<int> >::const_reverse_iterator
	  las = tree2
	  .rend();

  for (; first != last; first++) {
	tree1vect.push_back((*first).second);
  }
  for (; fir != las; ++fir) {
	tree2vect.push_back((*fir).first);
  }
  ASSERT_EQUAL(tree1vect, tree2vect);
  tree1.insert_unique(value_type(7, 7));
  tree3 = tree1;
  ASSERT_EQUAL(tree3, tree1)
}

static void TestAccessors() {
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree;

  ASSERT_EQUAL(tree.empty(), true)
  ASSERT_EQUAL(tree.size(), std::size_t(0))
  tree.insert_unique(value_type(1, 1));
  tree.insert_unique(value_type(5, 5));
  tree.insert_unique(value_type(3, 3));
  tree.insert_unique(value_type(2, 2));
  tree.insert_unique(value_type(4, 4));
  ASSERT_EQUAL(tree.empty(), false)
  ASSERT_EQUAL(tree.size(), std::size_t(5))
  ft::Rb_tree<key, value_type, keyOfValue, compare>::iterator begin = tree.begin();
  ft::Rb_tree<key, value_type, keyOfValue, compare>::iterator last = tree.end();
  const ft::Rb_tree<key, value_type, keyOfValue, compare> const_tree(tree);
  ft::Rb_tree<key, value_type, keyOfValue, compare>::const_iterator
	  cbeg = const_tree.begin();
  ft::Rb_tree<key, value_type, keyOfValue, compare>::const_iterator
	  clast = const_tree.end();
  while (begin != last && cbeg != clast) {
	ASSERT_EQUAL((*begin).second, (*cbeg).second)
	begin++;
	++cbeg;
  }
  ft::Rb_tree<key, value_type, keyOfValue, compare>::reverse_iterator rbegin = tree
	  .rbegin();
  ft::Rb_tree<key, value_type, keyOfValue, compare>::reverse_iterator rlast = tree.rend();
  ft::Rb_tree<key, value_type, keyOfValue, compare>::const_reverse_iterator crbeg =
	  const_tree.rbegin();
  ft::Rb_tree<key, value_type, keyOfValue, compare>::const_reverse_iterator crlast =
	  const_tree.rend();
  while (rbegin != rlast && crbeg != crlast) {
	ASSERT_EQUAL((*rbegin).second, (*crbeg).second)
	rbegin++;
	++crbeg;
  }
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree3;
  tree3.swap(tree);
  ASSERT_EQUAL(tree.size(), size_t(0))
  ASSERT_EQUAL(tree.empty(), true)
  begin = tree.begin();
  last = tree.end();
  while (begin != last) {
	ASSERT_EQUAL(0, 1)
  }
  begin = tree3.begin();
  last = tree3.end();
  cbeg = const_tree.begin();
  clast = const_tree.end();
  while (begin != last && cbeg != clast) {
	ASSERT_EQUAL((*begin).second, (*cbeg).second)
	begin++;
	++cbeg;
  }
}

static void TestInsert() {
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree;

  std::pair<iter, bool> ret;
  ret = tree.insert_unique(value_type(1, 1));
  ASSERT_EQUAL(ret.second, true);
  ASSERT_EQUAL((*ret.first).second, 1)
  ret = tree.insert_unique(value_type(5, 5));
  ASSERT_EQUAL(ret.second, true);
  ASSERT_EQUAL((*ret.first).second, 5)
  ret = tree.insert_unique(value_type(3, 3));
  ASSERT_EQUAL(ret.second, true);
  ASSERT_EQUAL((*ret.first).second, 3)
  ret = tree.insert_unique(value_type(2, 2));
  ASSERT_EQUAL(ret.second, true);
  ASSERT_EQUAL((*ret.first).second, 2)
  ret = tree.insert_unique(value_type(4, 4));
  ASSERT_EQUAL(ret.second, true);
  ASSERT_EQUAL((*ret.first).second, 4)
  ret = tree.insert_unique(value_type(4, 4));
  ASSERT_EQUAL(ret.second, false);
  ASSERT_EQUAL((*ret.first).second, 4)
  ret = tree.insert_unique(value_type(3, 3));
  ASSERT_EQUAL(ret.second, false);
  ASSERT_EQUAL((*ret.first).second, 3)

  std::vector<int> expected;
  for (int i = 1; i < 6; ++i) {
	expected.push_back(i);
  }
  iter first = tree.begin();
  iter last = tree.end();
  std::vector<int> curr;
  for (; first != last; ++first) {
	curr.push_back((*first).second);
  }
  ASSERT_EQUAL(expected, curr)

  tree.insert_unique(ret.first, value_type(3, 7));
  first = tree.begin();
  last = tree.end();
  curr.clear();
  for (; first != last; ++first) {
	curr.push_back((*first).second);
  }
  ASSERT_EQUAL(expected, curr)

  std::vector<value_type> add;
  add.push_back(value_type(8, 8));
  add.push_back(value_type(9, 9));
  add.push_back(value_type(4, 4));
  tree.insert_range_unique(add.begin(), add.end());
  first = tree.begin();
  last = tree.end();
  curr.clear();
  for (; first != last; ++first) {
	curr.push_back((*first).second);
  }
  expected.push_back(8);
  expected.push_back(9);
  ASSERT_EQUAL(expected, curr)
}

static void TestInsert2() {
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree;

  iter ret;
  ret = tree.insert_equal(value_type(1, 1));
  ASSERT_EQUAL((*ret).second, 1)
  ret = tree.insert_equal(value_type(5, 5));
  ASSERT_EQUAL((*ret).second, 5)
  ret = tree.insert_equal(value_type(3, 3));
  ASSERT_EQUAL((*ret).second, 3)
  ret = tree.insert_equal(value_type(2, 2));
  ASSERT_EQUAL((*ret).second, 2)
  ret = tree.insert_equal(value_type(4, 4));
  ASSERT_EQUAL((*ret).second, 4)
  ret = tree.insert_equal(value_type(4, 4));
  ASSERT_EQUAL((*ret).second, 4)
  ret = tree.insert_equal(value_type(3, 3));
  ASSERT_EQUAL((*ret).second, 3)

  std::vector<int> expected;
  expected.push_back(1);
  expected.push_back(2);
  expected.push_back(3);
  expected.push_back(3);
  expected.push_back(4);
  expected.push_back(4);
  expected.push_back(5);
  iter first = tree.begin();
  iter last = tree.end();
  std::vector<int> curr;
  for (; first != last; ++first) {
	curr.push_back((*first).second);
  }
  ASSERT_EQUAL(expected, curr)

  std::vector<int>::iterator it = expected.begin();
  for (int i = 0; i < 4; ++i) {
	++it;
  }
  expected.insert(it, 7);
  tree.insert_equal(ret, value_type(3, 7));
  first = tree.begin();
  last = tree.end();
  curr.clear();
  for (; first != last; ++first) {
	curr.push_back((*first).second);
  }
  ASSERT_EQUAL(expected, curr)

  std::vector<value_type> add;
  add.push_back(value_type(8, 8));
  add.push_back(value_type(9, 9));
  add.push_back(value_type(4, 4));
  tree.insert_range_equal(add.begin(), add.end());
  first = tree.begin();
  last = tree.end();
  curr.clear();
  for (; first != last; ++first) {
	curr.push_back((*first).second);
  }
  it = expected.begin();
  for (int i = 0; i < 5; ++i) {
	++it;
  }
  expected.insert(it, 4);
  expected.push_back(8);
  expected.push_back(9);
  ASSERT_EQUAL(expected, curr)
}

static void TestSetOperation() {
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree;
  iter it;

  tree.insert_unique(value_type(1, 50));
  tree.insert_unique(value_type(2, 100));
  tree.insert_unique(value_type(3, 150));
  tree.insert_unique(value_type(4, 200));

  it = tree.find(1);
  if (it == tree.end()) ASSERT_EQUAL(1, 0);
  ASSERT_EQUAL(it->second, 50);
  it = tree.find(2);
  if (it == tree.end()) ASSERT_EQUAL(1, 0);
  ASSERT_EQUAL(it->second, 100);
  it = tree.find(3);
  if (it == tree.end()) ASSERT_EQUAL(1, 0);
  ASSERT_EQUAL(it->second, 150);
  it = tree.find(4);
  if (it == tree.end()) ASSERT_EQUAL(1, 0);
  ASSERT_EQUAL(it->second, 200);
  it = tree.find(5);
  if (it != tree.end()) ASSERT_EQUAL(1, 0);

  tree.insert_unique(value_type(7, 7));
  it = tree.lower_bound(2);
  if (it == tree.end()) ASSERT_EQUAL(1, 0);
  ASSERT_EQUAL(it->second, 100);
  it = tree.lower_bound(5);
  if (it == tree.end()) ASSERT_EQUAL(1, 0);
  ASSERT_EQUAL(it->second, 7);

  it = tree.upper_bound(2);
  if (it == tree.end()) ASSERT_EQUAL(1, 0);
  ASSERT_EQUAL(it->second, 150);
  it = tree.upper_bound(5);
  if (it == tree.end()) ASSERT_EQUAL(1, 0);
  ASSERT_EQUAL(it->second, 7);
  it = tree.upper_bound(7);
  if (it != tree.end()) ASSERT_EQUAL(1, 0);
}

static void TestSetOperation2() {
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree;

  tree.insert_unique(value_type(1, 101));
  tree.insert_unique(value_type(3, 202));
  tree.insert_unique(value_type(6, 303));
  ASSERT_EQUAL(tree.count(1), size_t(1));
  ASSERT_EQUAL(tree.count(3), std::size_t(1));
  ASSERT_EQUAL(tree.count(6), size_t(1));
  ASSERT_EQUAL(tree.count(7), size_t(0));
  ASSERT_EQUAL(tree.count(5), std::size_t(0));

  std::pair<iter, iter> ret = tree.equal_range(3);
  ASSERT_EQUAL((*ret.first).second, 202);
  ASSERT_EQUAL((*ret.second).second, 303);
}

static void TestRelationOperation() {
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree1;
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree2;

  ASSERT_EQUAL(tree1 == tree2, true)
  tree1.insert_unique(value_type(1, 1));
  tree2.insert_unique(value_type(1, 2));
  ASSERT_EQUAL(tree1 < tree2, true)
  ASSERT_EQUAL(tree2 > tree1, true)
}

static void TestErase() {
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree;

  for (int i = 1; i < 15; ++i) {
	tree.insert_unique(value_type(i, i));
  }
  tree.erase(tree.find(14));
  std::vector<int> expected;
  for (int i = 1; i < 14; ++i) {
	expected.push_back(i);
  }
  iter first = tree.begin();
  iter last = tree.end();
  std::vector<int> curr;
  while (first != last) {
	curr.push_back((*first).second);
	++first;
  }
  ASSERT_EQUAL(expected, curr);
  tree.clear();
  ASSERT_EQUAL(tree.empty(), true);
  ASSERT_EQUAL(tree.size(), std::size_t(0));
  for (int i = 1; i < 15; ++i) {
	tree.insert_unique(value_type(i, i));
  }
  ASSERT_EQUAL(tree.erase(14), std::size_t(1));
  curr.clear();
  first = tree.begin();
  last = tree.end();
  while (first != last) {
	curr.push_back((*first).second);
	++first;
  }
  ASSERT_EQUAL(curr, expected);

  std::pair<iter, iter> ret = tree.equal_range(14);
  tree.erase(ret.first, ret.second);
  curr.clear();
  first = tree.begin();
  last = tree.end();
  while (first != last) {
	curr.push_back((*first).second);
	++first;
  }
  ASSERT_EQUAL(curr, expected);
}

static void TestErase2() {
  ft::Rb_tree<key, value_type, keyOfValue, compare> tree;

  for (int i = 1; i < 15; ++i) {
	tree.insert_equal(value_type(i, i));
  }
  for (int i = 1; i < 15; ++i) {
	tree.insert_equal(value_type(i, i));
  }
  tree.erase(tree.find(14));
  std::vector<int> expected;
  for (int i = 1; i < 14; ++i) {
	expected.push_back(i);
	expected.push_back(i);
  }
  expected.push_back(14);
  iter first = tree.begin();
  iter last = tree.end();
  std::vector<int> curr;
  while (first != last) {
	curr.push_back((*first).second);
	++first;
  }
  ASSERT_EQUAL(expected, curr);
//  tree.clear();
//  ASSERT_EQUAL(tree.empty(), true);
//  ASSERT_EQUAL(tree.size(), std::size_t(0));
//  for (int i = 1; i < 15; ++i) {
//	tree.insert_equal(value_type(i,i));
//	tree.insert_equal(value_type(i,i));
//  }
//  ASSERT_EQUAL(tree.erase(14), std::size_t(2));
//  curr.clear();
//  first = tree.begin();
//  last = tree.end();
//  while (first != last) {
//	curr.push_back((*first).second);
//	++first;
//  }
//  expected.erase(--expected.end());
//  ASSERT_EQUAL(curr, expected);
//
//  std::pair<iter, iter> ret = tree.equal_range(13);
//  tree.erase(ret.first, ret.second);
//  curr.clear();
//  first = tree.begin();
//  last = tree.end();
//  while (first != last) {
//	curr.push_back((*first).second);
//	++first;
//  }
//  expected.erase(--expected.end());
//  expected.erase(--expected.end());
//  ASSERT_EQUAL(curr, expected);
}

void test_tree() {
  TestRunner tr;

  std::cout << "\033[1;36m";
  std::cout << "\n\n--------TEST TREE--------\n\n";
  std::cout << "\033[0m";
  RUN_TEST(tr, TestConstructor);
  RUN_TEST(tr, TestAccessors);
  RUN_TEST(tr, TestInsert);
  RUN_TEST(tr, TestInsert2);
  RUN_TEST(tr, TestSetOperation);
  RUN_TEST(tr, TestSetOperation2);
  RUN_TEST(tr, TestRelationOperation);
  RUN_TEST(tr, TestErase);
  RUN_TEST(tr, TestErase2);
}