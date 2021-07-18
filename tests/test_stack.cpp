#include "test_runner.h"
#include "stack.hpp"
#include <stack>

static void TestConstructor() {
  std::deque<int> mydeque(3, 100);          // deque with 3 elements
  ft::deque<int> ft_mydeque(3, 100);          // deque with 3 elements
  std::vector<int> myvector(2, 200);        // vector with 2 elements

  std::stack<int> first;                    // empty stack
  std::stack<int> second(mydeque);         // stack initialized to copy of deque
  ft::stack<int> ft_first;                    // empty stack
  ft::stack<int> ft_second(ft_mydeque);         // stack initialized to copy
  // of deque

  std::stack<int, std::vector<int> > third;  // empty stack using vector
  std::stack<int, std::vector<int> > fourth(myvector);
  ft::stack<int, std::vector<int> > ft_third;  // empty stack using vector
  ft::stack<int, std::vector<int> > ft_fourth(myvector);

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestConstructor--------\n";
  std::cout << "\033[0m";
  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of ft_first: " << ft_first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of ft_second: " << ft_second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of ft_third: " << ft_third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';
  std::cout << "size of ft_fourth: " << ft_fourth.size() << '\n';
#endif
}

static void TestEmpty() {
  std::stack<int> mystack;
  ft::stack<int> ft_mystack;
  int sum(0);
  int ft_sum(0);

  for (int i = 1; i <= 10; i++) mystack.push(i);
  for (int i = 1; i <= 10; i++) ft_mystack.push(i);

  while (!mystack.empty()) {
	sum += mystack.top();
	mystack.pop();
  }
  while (!ft_mystack.empty()) {
	ft_sum += ft_mystack.top();
	ft_mystack.pop();
  }

  ASSERT_EQUAL(sum, ft_sum)
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestEmpty--------\n";
  std::cout << "\033[0m";
  std::cout << "total: " << sum << '\n';
  std::cout << "ft_total: " << ft_sum << '\n';
#endif
}

static void TestSize() {
  std::stack<int> myints;
  ft::stack<int> ft_myints;
  ASSERT_EQUAL(myints.size(), ft_myints.size())
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestSize--------\n";
  std::cout << "\033[0m";
  std::cout << "0. size: " << myints.size() << '\n';
  std::cout << "0. ft_size: " << ft_myints.size() << '\n';
#endif

  for (int i = 0; i < 5; i++) myints.push(i);
  for (int i = 0; i < 5; i++) ft_myints.push(i);
  ASSERT_EQUAL(myints.size(), ft_myints.size())
#ifdef PRINT
  std::cout << "1. size: " << myints.size() << '\n';
  std::cout << "1. ft_size: " << ft_myints.size() << '\n';
#endif

  myints.pop();
  ft_myints.pop();
  ASSERT_EQUAL(myints.size(), ft_myints.size())
#ifdef PRINT
  std::cout << "2. size: " << myints.size() << '\n';
  std::cout << "2. ft_size: " << ft_myints.size() << '\n';
#endif
}

static void TestTop() {
  std::stack<int> mystack;
  ft::stack<int> ft_mystack;

  mystack.push(10);
  mystack.push(20);
  ft_mystack.push(10);
  ft_mystack.push(20);

  mystack.top() -= 5;
  ft_mystack.top() -= 5;

  ASSERT_EQUAL(mystack.top(), ft_mystack.top())
#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestTop--------\n";
  std::cout << "\033[0m";
  std::cout << "mystack.top() is now " << mystack.top() << '\n';
  std::cout << "ft_mystack.top() is now " << ft_mystack.top() << '\n';
#endif
}

static void TestPushPop() {
  std::stack<int> mystack;
  ft::stack<int> ft_mystack;

  for (int i = 0; i < 5; ++i) mystack.push(i);
  for (int i = 0; i < 5; ++i) ft_mystack.push(i);

#ifdef PRINT
  std::cout << "\033[1;35m";
  std::cout << "\n--------TestPushPop--------\n";
  std::cout << "\033[0m";
#endif
  while (!mystack.empty()) {
#ifdef PRINT
	std::cout << ' ' << mystack.top();
#endif
	mystack.pop();
  }
#ifdef PRINT
  std::cout << '\n';
#endif

  while (!ft_mystack.empty()) {
#ifdef PRINT
	std::cout << ' ' << ft_mystack.top();
#endif
	ft_mystack.pop();
  }
#ifdef PRINT
  std::cout << '\n';
#endif

}

static void TestRelationalOperators() {
  std::stack<int> foo;   // three ints with a value of 100
  std::stack<int> bar;   // two ints with a value of 200
  ft::stack<int> ft_foo;   // three ints with a value of 100
  ft::stack<int> ft_bar;   // two ints with a value of 200

  for (int i = 0; i < 3; ++i) {
	foo.push(100);
	ft_foo.push(100);
  }
  for (int i = 0; i < 2; ++i) {
	bar.push(200);
	ft_bar.push(200);
  }
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

void test_stack() {
  TestRunner tr;

  std::cout << "\033[1;36m";
  std::cout << "\n\n--------TEST STACK--------\n\n";
  std::cout << "\033[0m";
  RUN_TEST(tr, TestConstructor);
  RUN_TEST(tr, TestEmpty);
  RUN_TEST(tr, TestSize);
  RUN_TEST(tr, TestTop);
  RUN_TEST(tr, TestPushPop);
  RUN_TEST(tr, TestRelationalOperators);
}