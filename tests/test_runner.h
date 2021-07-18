#pragma once

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "vector.hpp"
#include <list>
#include "list.hpp"
#include "cstdlib"
#include <deque>
#include "deque.hpp"
#include "tree.hpp"
#include "map.hpp"
#include "set.hpp"
#include "multimap.hpp"
#include "multiset.hpp"

using namespace std;

template<typename T>
bool operator==(const std::list<T> &lhs, const ft::list<T> &rhs);

template<typename T>
bool operator==(const std::vector<T> &lhs, const ft::vector<T> &rhs);

template<typename T>
bool operator==(const std::deque<T> &lhs, const ft::deque<T> &rhs);

template<typename Key, typename Value, typename Compare>
bool operator==(const std::map<Key, Value, Compare> &lhs,
				const ft::map<Key, Value, Compare>
				&rhs);

template<typename Key, typename Value, typename Compare>
bool operator==(const std::multimap<Key, Value, Compare> &lhs, const ft::multimap<Key,
																				  Value,
																				  Compare>
&rhs);

template<typename Key, typename Compare>
bool operator==(const std::set<Key, Compare> &lhs, const ft::set<Key, Compare> &rhs);

template<typename Key, typename Compare>
bool operator==(const std::multiset<Key, Compare> &lhs, const ft::multiset<Key, Compare>
&rhs);

template<class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
  os << "{";
  bool first = true;
  for (typename vector<T>::const_iterator it = s.begin(); it != s.end(); ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << *it;
  }
  return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const ft::vector<T> &s) {
  os << "{";
  bool first = true;
  for (typename ft::vector<T>::const_iterator it = s.begin(); it != s.end();
	   ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << *it;
  }
  return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
  os << "{";
  bool first = true;
  for (typename set<T>::const_iterator it = s.begin(); it != s.end(); ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << *it;
  }
  return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const ft::set<T> &s) {
  os << "{";
  bool first = true;
  for (typename ft::set<T>::const_iterator it = s.begin(); it != s.end(); ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << *it;
  }
  return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const multiset<T> &s) {
  os << "{";
  bool first = true;
  for (typename multiset<T>::const_iterator it = s.begin(); it != s.end(); ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << *it;
  }
  return os << "}";
}

template<class T>
ostream &operator<<(ostream &os, const ft::multiset<T> &s) {
  os << "{";
  bool first = true;
  for (typename ft::multiset<T>::const_iterator it = s.begin(); it != s.end(); ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << *it;
  }
  return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
  os << "{";
  bool first = true;
  for (typename map<K, V>::const_iterator it = m.begin(); it != m.end();
	   ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << it->first << ": " << it->second;
  }
  return os << "}";
}

template<class K, class V, class KeyOfValue, class Compare>
ostream &operator<<(ostream &os, const ft::Rb_tree<K, V, KeyOfValue, Compare> &m) {
  os << "{";
  bool first = true;
  for (typename ft::Rb_tree<K, V, KeyOfValue, Compare>::const_iterator it = m.begin();
	   it != m
		   .end();
	   ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << it->first << ": " << it->second;
  }
  return os << "}";
}

template<class K, class V, class Compare>
ostream &operator<<(ostream &os, const ft::map<K, V, Compare> &m) {
  os << "{";
  bool first = true;
  for (typename ft::map<K, V, Compare>::const_iterator it = m.begin(); it != m.end();
	   ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << it->first << ": " << it->second;
  }
  return os << "}";
}

template<class K, class V, class Compare>
ostream &operator<<(ostream &os, const std::map<K, V, Compare> &m) {
  os << "{";
  bool first = true;
  for (typename std::map<K, V, Compare>::const_iterator it = m.begin(); it != m.end();
	   ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << it->first << ": " << it->second;
  }
  return os << "}";
}

template<class K, class V, class Compare>
ostream &operator<<(ostream &os, const std::multimap<K, V, Compare> &m) {
  os << "{";
  bool first = true;
  for (typename std::multimap<K, V, Compare>::const_iterator it = m.begin(); it != m.end();
	   ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << it->first << ": " << it->second;
  }
  return os << "}";
}

template<class K, class V, class Compare>
ostream &operator<<(ostream &os, const ft::multimap<K, V, Compare> &m) {
  os << "{";
  bool first = true;
  for (typename ft::multimap<K, V, Compare>::const_iterator it = m.begin(); it != m.end();
	   ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << it->first << ": " << it->second;
  }
  return os << "}";
}

template<typename T>
ostream &operator<<(ostream &os, const list<T> &l) {
  os << "{";
  bool first = true;
  for (typename list<T>::const_iterator it = l.begin(); it != l.end();
	   ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << *it;
  }
  return os << "}";
}

template<typename T>
ostream &operator<<(ostream &os, const ft::list<T> &l) {
  os << "{";
  bool first = true;
  for (typename ft::list<T>::const_iterator it = l.begin(); it != l.end();
	   ++it) {
	if (!first) {
	  os << ", ";
	}
	first = false;
	os << *it;
  }
  return os << "}";
}

template<typename T>
std::ostream &operator<<(std::ostream &s, const std::deque<T> &v) {
  s.put('[');
  char comma[3] = {'\0', ' ', '\0'};
  for (typename std::deque<T>::const_iterator it = v.begin(); it != v.end();
	   ++it) {
	s << comma << *it;
	comma[0] = ',';
  }
  return s << ']';
}

template<typename T>
std::ostream &operator<<(std::ostream &s, const ft::deque<T> &v) {
  s.put('[');
  char comma[3] = {'\0', ' ', '\0'};
  for (typename ft::deque<T>::const_iterator it = v.begin(); it != v.end();
	   ++it) {
	s << comma << *it;
	comma[0] = ',';
  }
  return s << ']';
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = "") {
  if (!(t == u)) {
	ostringstream os;
	os << "Assertion failed: " << t << " != " << u;
	if (!hint.empty()) {
	  os << " hint: " << hint;
	}
	throw runtime_error(os.str());
  }
}

inline void Assert(bool b, const string &hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
 public:
  TestRunner() : fail_count(0) {}

  template<class TestFunc>
  void RunTest(TestFunc func, const string &test_name) {
	try {
	  func();
	  cout << test_name << "\033[0;32m OK\033[0m" << endl;
	} catch (exception &e) {
	  ++fail_count;
	  cout << test_name << "\033[0;31m fail: " << e.what() << "\033[0m"
		   << endl;
	} catch (...) {
	  ++fail_count;
	  cout << "\033[0;31mUnknown exception caught\033[0m" << endl;
	}
  }

  ~TestRunner() {
	if (fail_count > 0) {
	  cout << fail_count << " unit tests failed. Terminate" << endl;
	  exit(1);
	}
  }

 private:
  int fail_count;
};

#define ASSERT_EQUAL(x, y) {            \
  ostringstream __assert_equal_private_os;                     \
  __assert_equal_private_os << #x << " != " << #y << ", "      \
    << __FILE__ << ":" << __LINE__;     \
  AssertEqual(x, y, __assert_equal_private_os.str());          \
}

#define ASSERT(x) {                     \
  ostringstream os;                     \
  os << #x << " is false, "             \
    << __FILE__ << ":" << __LINE__;     \
  Assert(x, os.str());                  \
}

#define RUN_TEST(tr, func) \
  tr.RunTest(func, #func)
