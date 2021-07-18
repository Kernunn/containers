#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace ft {
template<typename T, typename Sequence = deque<T> >
class queue {

  template<typename T1, typename Seq1>
  friend bool
  operator==(const queue<T1, Seq1> &, const queue<T1, Seq1> &);

  template<typename T1, typename Seq1>
  friend bool
  operator<(const queue<T1, Seq1> &, const queue<T1, Seq1> &);

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
  queue(const Sequence &c = Sequence())
	  : c(c) {}

  bool
  empty() const { return c.empty(); }

  size_type
  size() const { return c.size(); }

  reference
  front() { return c.front(); }

  const_reference
  front() const { return c.front(); }

  reference
  back() { return c.back(); }

  const_reference
  back() const { return c.back(); }

  void
  push(const value_type &x) { c.push_back(x); }

  void
  pop() { c.pop_front(); }

};

template<typename T, typename Seq>
inline bool
operator==(const queue<T, Seq> &x, const queue<T, Seq> &y) { return x.c == y.c; }

template<typename T, typename Seq>
inline bool
operator<(const queue<T, Seq> &x, const queue<T, Seq> &y) { return x.c < y.c; }

template<typename T, typename Seq>
inline bool
operator!=(const queue<T, Seq> &x, const queue<T, Seq> &y) { return !(x == y); }

template<typename T, typename Seq>
inline bool
operator>(const queue<T, Seq> &x, const queue<T, Seq> &y) { return y < x; }

template<typename T, typename Seq>
inline bool
operator<=(const queue<T, Seq> &x, const queue<T, Seq> &y) { return !(y < x); }

template<typename T, typename Seq>
inline bool
operator>=(const queue<T, Seq> &x, const queue<T, Seq> &y) { return !(x < y); }

}
#endif
