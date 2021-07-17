#include "test_runner.h"
#include <queue>
#include "queue.hpp"

static void TestConstructor()
{
	std::deque<int> mydeck (3,100);        // deque with 3 elements
	ft::deque<int> ft_mydeck (3,100);        // deque with 3 elements
	std::list<int> mylist (2,200);         // list with 2 elements

	std::queue<int> first;                 // empty queue
	std::queue<int> second(mydeck);       // queue initialized to copy of deque
	ft::queue<int> ft_first;                 // empty queue
	ft::queue<int> ft_second(ft_mydeck);  // queue initialized to copy of deque

	std::queue<int,std::list<int> > third; // empty queue with list as underlying container
	std::queue<int,std::list<int> > fourth (mylist);
	ft::queue<int,std::list<int> > ft_third; // empty queue with list as
	// underlying container
	ft::queue<int,std::list<int> > ft_fourth (mylist);

	ASSERT_EQUAL(first.size(), ft_first.size())
	ASSERT_EQUAL(second.size(), ft_second.size())
	ASSERT_EQUAL(third.size(), ft_third.size())
	ASSERT_EQUAL(fourth.size(), ft_fourth.size())
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

static void TestEmpty()
{
	std::queue<int> myqueue;
	ft::queue<int> ft_myqueue;
	int sum (0);
	int ft_sum (0);

	for (int i=1;i<=10;i++) myqueue.push(i);
	for (int i=1;i<=10;i++) ft_myqueue.push(i);

	while (!myqueue.empty())
	{
		sum += myqueue.front();
		myqueue.pop();
	}
	while (!ft_myqueue.empty())
	{
		ft_sum += ft_myqueue.front();
		ft_myqueue.pop();
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

static void TestSize()
{
	std::queue<int> myints;
	ft::queue<int> ft_myints;
	ASSERT_EQUAL(myints.size(), ft_myints.size())
#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestSize--------\n";
	std::cout << "\033[0m";
	std::cout << "0. size: " << myints.size() << '\n';
	std::cout << "0. ft_size: " << ft_myints.size() << '\n';
#endif

	for (int i=0; i<5; i++) myints.push(i);
	for (int i=0; i<5; i++) ft_myints.push(i);
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

static void TestFront()
{
	std::queue<int> myqueue;
	ft::queue<int> ft_myqueue;

	myqueue.push(77);
	myqueue.push(16);
	ft_myqueue.push(77);
	ft_myqueue.push(16);

	myqueue.front() -= myqueue.back();    // 77-16=61
	ft_myqueue.front() -= ft_myqueue.back();    // 77-16=61

	ASSERT_EQUAL(myqueue.front(), ft_myqueue.front())
#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestFront--------\n";
	std::cout << "\033[0m";
	std::cout << "myqueue.front() is now " << myqueue.front() << '\n';
	std::cout << "ft_myqueue.front() is now " << ft_myqueue.front() << '\n';
#endif

}

static void TestBack()
{
	std::queue<int> myqueue;
	ft::queue<int> ft_myqueue;

	myqueue.push(12);
	myqueue.push(75);   // this is now the back
	ft_myqueue.push(12);
	ft_myqueue.push(75);   // this is now the back

	myqueue.back() -= myqueue.front();
	ft_myqueue.back() -= ft_myqueue.front();

	ASSERT_EQUAL(myqueue.back(), ft_myqueue.back())
#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestBack--------\n";
	std::cout << "\033[0m";
	std::cout << "myqueue.back() is now " << myqueue.back() << '\n';
	std::cout << "ft_myqueue.back() is now " << ft_myqueue.back() << '\n';
#endif
}

static void TestPushPop()
{
	std::queue<int> myqueue;
	ft::queue<int> ft_myqueue;

	for (int i=0; i<5; i++) myqueue.push(i);
	for (int i=0; i<5; i++) ft_myqueue.push(i);

#ifdef PRINT
	std::cout << "\033[1;35m";
	std::cout << "\n--------TestPushPop--------\n";
	std::cout << "\033[0m";
#endif
	while (!myqueue.empty())
	{
		ASSERT_EQUAL(myqueue.front(), ft_myqueue.front())
#ifdef PRINT
		std::cout << ' ' << myqueue.front();
		std::cout << ' ' << ft_myqueue.front();
#endif
		myqueue.pop();
		ft_myqueue.pop();
	}
#ifdef PRINT
	std::cout << '\n';
#endif
}

static void TestRelationalOperators()
{
	std::queue<int> foo;   // three ints with a value of 100
	std::queue<int> bar;   // two ints with a value of 200
	ft::queue<int> ft_foo;   // three ints with a value of 100
	ft::queue<int> ft_bar;   // two ints with a value of 200

	for (int i = 0; i < 3; ++i)
	{
		foo.push(100);
		ft_foo.push(100);
	}
	for (int i = 0; i < 2; ++i)
	{
		bar.push(200);
		ft_bar.push(200);
	}
	ASSERT_EQUAL((foo==bar), (ft_foo==ft_bar))
	ASSERT_EQUAL((foo!=bar), (ft_foo!=ft_bar))
	ASSERT_EQUAL((foo<bar), (ft_foo<ft_bar))
	ASSERT_EQUAL((foo>bar), (ft_foo>ft_bar))
	ASSERT_EQUAL((foo<=bar), (ft_foo<=ft_bar))
	ASSERT_EQUAL((foo>=bar), (ft_foo>=ft_bar))
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

void test_queue()
{
	TestRunner tr;

	std::cout << "\033[1;36m";
	std::cout << "\n\n--------TEST QUEUE--------\n\n";
	std::cout << "\033[0m";
	RUN_TEST(tr, TestConstructor);
	RUN_TEST(tr, TestEmpty);
	RUN_TEST(tr, TestSize);
	RUN_TEST(tr, TestFront);
	RUN_TEST(tr, TestBack);
	RUN_TEST(tr, TestPushPop);
	RUN_TEST(tr, TestRelationalOperators);
}