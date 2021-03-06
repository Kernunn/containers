#ifndef ITERATOR_H
#define ITERATOR_H

namespace ft {
struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : public input_iterator_tag {};

struct bidirectional_iterator_tag : public forward_iterator_tag {};

struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template<typename Category, typename T, typename Distance = std::ptrdiff_t,
	typename Pointer = T *, typename Reference = T &>
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

template<typename Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

/// Partial specialization for pointer types.
template<typename T>
struct iterator_traits<T *> {
  typedef random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef T *pointer;
  typedef T &reference;
};

/// Partial specialization for const pointer types.
template<typename T>
struct iterator_traits<const T *> {
  typedef random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const T *pointer;
  typedef const T &reference;
};

template<typename Iterator>
class reverse_iterator
	: public iterator<typename iterator_traits<Iterator>::iterator_category,
					  typename iterator_traits<Iterator>::value_type,
					  typename iterator_traits<Iterator>::difference_type,
					  typename iterator_traits<Iterator>::pointer,
					  typename iterator_traits<Iterator>::reference> {
 protected:
  Iterator current;

  typedef iterator_traits<Iterator> traits_type;

 public:
  typedef Iterator iterator_type;
  typedef typename traits_type::difference_type difference_type;
  typedef typename traits_type::pointer pointer;
  typedef typename traits_type::reference reference;

  reverse_iterator() : current() {}

  explicit
  reverse_iterator(iterator_type x) : current(x) {}

  reverse_iterator(const reverse_iterator &x)
	  : current(x.current) {}

  template<typename Iter>
  reverse_iterator(const reverse_iterator<Iter> &x)
	  : current(x.base()) {}

  iterator_type
  base() const { return current; }

  reference
  operator*() const {
	Iterator tmp = current;
	return *--tmp;
  }

  pointer
  operator->() const {
	Iterator tmp = current;
	--tmp;
	return S_to_pointer(tmp);
  }

  reverse_iterator &
  operator++() {
	--current;
	return *this;
  }

  reverse_iterator
  operator++(int) {
	reverse_iterator tmp = *this;
	--current;
	return tmp;
  }

  reverse_iterator &
  operator--() {
	++current;
	return *this;
  }

  reverse_iterator
  operator--(int) {
	reverse_iterator tmp = *this;
	++current;
	return tmp;
  }

  reverse_iterator
  operator+(difference_type n) const { return reverse_iterator(current - n); }

  reverse_iterator &
  operator+=(difference_type n) {
	current -= n;
	return *this;
  }

  reverse_iterator
  operator-(difference_type n) const { return reverse_iterator(current + n); }

  reverse_iterator &
  operator-=(difference_type n) {
	current += n;
	return *this;
  }

  reference
  operator[](difference_type n) const { return *(*this + n); }

 private:
  template<typename T>
  static T *
  S_to_pointer(T *p) { return p; }

  template<typename T>
  static pointer
  S_to_pointer(T t) { return t.operator->(); }
};

template<typename Iterator>
inline bool
operator==(const reverse_iterator<Iterator> &x,
		   const reverse_iterator<Iterator> &y) { return x.base() == y.base(); }

template<typename Iterator>
inline bool
operator<(const reverse_iterator<Iterator> &x,
		  const reverse_iterator<Iterator> &y) { return y.base() < x.base(); }

template<typename Iterator>
inline bool
operator!=(const reverse_iterator<Iterator> &x,
		   const reverse_iterator<Iterator> &y) { return !(x == y); }

template<typename Iterator>
inline bool
operator>(const reverse_iterator<Iterator> &x,
		  const reverse_iterator<Iterator> &y) { return y < x; }

template<typename Iterator>
inline bool
operator<=(const reverse_iterator<Iterator> &x,
		   const reverse_iterator<Iterator> &y) { return !(y < x); }

template<typename Iterator>
inline bool
operator>=(const reverse_iterator<Iterator> &x,
		   const reverse_iterator<Iterator> &y) { return !(x < y); }

template<typename IteratorL, typename IteratorR>
inline bool
operator==(const reverse_iterator<IteratorL> &x,
		   const reverse_iterator<IteratorR> &y) { return x.base() == y.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator<(const reverse_iterator<IteratorL> &x,
		  const reverse_iterator<IteratorR> &y) { return y.base() < x.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator!=(const reverse_iterator<IteratorL> &x,
		   const reverse_iterator<IteratorR> &y) { return !(x == y); }

template<typename IteratorL, typename IteratorR>
inline bool
operator>(const reverse_iterator<IteratorL> &x,
		  const reverse_iterator<IteratorR> &y) { return y < x; }

template<typename IteratorL, typename IteratorR>
inline bool
operator<=(const reverse_iterator<IteratorL> &x,
		   const reverse_iterator<IteratorR> &y) { return !(y < x); }

template<typename IteratorL, typename IteratorR>
inline bool
operator>=(const reverse_iterator<IteratorL> &x,
		   const reverse_iterator<IteratorR> &y) { return !(x < y); }

template<typename Iterator>
inline typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator> &x,
		  const reverse_iterator<Iterator> &y) { return y.base() - x.base(); }

template<typename IteratorL, typename IteratorR>
inline typename reverse_iterator<IteratorL>::difference_type
operator-(const reverse_iterator<IteratorL> &x,
		  const reverse_iterator<IteratorR> &y) { return y.base() - x.base(); }

template<typename Iterator>
inline reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n,
		  const reverse_iterator<Iterator> &x) {
  return reverse_iterator<Iterator>(x.base() - n);
}
}
#endif
