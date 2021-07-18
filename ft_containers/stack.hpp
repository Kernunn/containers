#ifndef STACK_HPP
#define STACK_HPP

namespace ft {
template<typename T, typename Sequence = ft::deque<T> >
class stack {

  template<typename T1, typename Seq1>
  friend bool
  operator==(const stack<T1, Seq1> &, const stack<T1, Seq1> &);

  template<typename T1, typename Seq1>
  friend bool
  operator<(const stack<T1, Seq1> &, const stack<T1, Seq1> &);

 public:
  typedef typename Sequence::value_type value_type;
  typedef typename Sequence::size_type size_type;
  typedef Sequence container_type;

 protected:
  typedef typename Sequence::reference reference;
  typedef typename Sequence::const_reference const_reference;

  Sequence c;

 public:
  explicit
  stack(const Sequence &c = Sequence())
	  : c(c) {}

  bool
  empty() const { return c.empty(); }

  size_type
  size() const { return c.size(); }

  reference
  top() { return c.back(); }

  const_reference
  top() const { return c.back(); }

  void
  push(const value_type &x) { c.push_back(x); }

  void
  pop() { c.pop_back(); }

};

template<typename T, typename Seq>
inline bool
operator==(const stack<T, Seq> &x, const stack<T, Seq> &y) { return x.c == y.c; }

template<typename T, typename Seq>
inline bool
operator<(const stack<T, Seq> &x, const stack<T, Seq> &y) { return x.c < y.c; }

template<typename T, typename Seq>
inline bool
operator!=(const stack<T, Seq> &x, const stack<T, Seq> &y) { return !(x == y); }

template<typename T, typename Seq>
inline bool
operator>(const stack<T, Seq> &x, const stack<T, Seq> &y) { return y < x; }

template<typename T, typename Seq>
inline bool
operator<=(const stack<T, Seq> &x, const stack<T, Seq> &y) { return !(y < x); }

template<typename T, typename Seq>
inline bool
operator>=(const stack<T, Seq> &x, const stack<T, Seq> &y) { return !(x < y); }

}

#endif
