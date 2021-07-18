#ifndef FT_CONTAINERS_DEQUE_HPP
#define FT_CONTAINERS_DEQUE_HPP

#include <algorithm>
#include "allocator.hpp"
#include "reverse_iterator.h"
#include "sstream"

namespace ft {
#define DEQUE_BUF_SIZE 512

inline std::size_t _deque_buf_size(std::size_t size) {
  return (size < DEQUE_BUF_SIZE ? std::size_t(DEQUE_BUF_SIZE / size) :
		  std::size_t(1));
}

template<typename T, typename Ref, typename Ptr>
struct Deque_iterator {
  typedef Deque_iterator<T, T &, T *> iterator;
  typedef Deque_iterator<const T, const T &, const T *> const_iterator;
  typedef T *chunk_pointer;
  typedef T **map_pointer;

  static std::size_t _buffer_size() { return _deque_buf_size(sizeof(T)); }

  typedef std::random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef Ptr pointer;
  typedef Ref reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Deque_iterator _Self;

  chunk_pointer cur;
  chunk_pointer first;
  chunk_pointer last;
  map_pointer node;

  Deque_iterator(chunk_pointer x, map_pointer y)
	  : cur(x), first(*y), last(*y + _buffer_size()), node(y) {}

  Deque_iterator()
	  : cur(), first(), last(), node() {}

  Deque_iterator(const iterator &x)
	  : cur(x.cur), first(x.first), last(x.last), node(x.node) {}

  iterator _const_cast() const { return iterator(cur, node); }

  reference
  operator*() const { return *cur; }

  pointer
  operator->() const { return cur; }

  _Self &
  operator++() {
	++cur;
	if (cur == last) {
	  _set_node(node + 1);
	  cur = first;
	}
	return *this;
  }

  _Self
  operator++(int) {
	_Self tmp = *this;
	++*this;
	return tmp;
  }

  _Self &
  operator--() {
	if (cur == first) {
	  _set_node(node - 1);
	  cur = last;
	}
	--cur;
	return *this;
  }

  _Self
  operator--(int) {
	_Self tmp = *this;
	--*this;
	return tmp;
  }

  _Self &
  operator+=(difference_type n) {
	difference_type offset = n + (cur - first);
	if (offset >= 0 && offset < difference_type(_buffer_size())) {
	  cur += n;
	} else {
	  difference_type node_offset = offset > 0 ? offset /
		  difference_type(_buffer_size()) : -difference_type(
		  (-offset - 1) / _buffer_size()) - 1;
	  _set_node(node + node_offset);
	  cur = first + (offset - node_offset * difference_type
		  (_buffer_size()));
	}
	return *this;
  }

  _Self
  operator+(difference_type n) const {
	_Self tmp = *this;
	return tmp += n;
  }

  _Self &
  operator-=(difference_type n) { return *this += -n; }

  _Self
  operator-(difference_type n) const {
	_Self tmp = *this;
	return tmp -= n;
  }

  reference
  operator[](difference_type n) const { return *(*this + n); }

  void
  _set_node(map_pointer new_node) {
	node = new_node;
	first = *new_node;
	last = first + difference_type(_buffer_size());
  }
};

template<typename T, typename Ref, typename Ptr>
inline bool
operator==(const Deque_iterator<T, Ref, Ptr> &x,
		   const Deque_iterator<T, Ref, Ptr> &y) { return x.cur == y.cur; }

template<typename T, typename RefL, typename PtrL,
	typename RefR, typename PtrR>
inline bool
operator==(const Deque_iterator<T, RefL, PtrL> &x,
		   const Deque_iterator<T, RefR, PtrR> &y) { return x.cur == y.cur; }

template<typename T, typename Ref, typename Ptr>
inline bool
operator!=(const Deque_iterator<T, Ref, Ptr> &x,
		   const Deque_iterator<T, Ref, Ptr> &y) { return !(x == y); }

template<typename T, typename RefL, typename PtrL,
	typename RefR, typename PtrR>
inline bool
operator!=(const Deque_iterator<T, RefL, PtrL> &x,
		   const Deque_iterator<T, RefR, PtrR> &y) { return !(x == y); }

template<typename T, typename Ref, typename Ptr>
inline bool
operator<(const Deque_iterator<T, Ref, Ptr> &x,
		  const Deque_iterator<T, Ref, Ptr> &y) {
  return (x.node == y.node) ? (x.cur < y.cur) : (x.node < y.node);
}

template<typename T, typename RefL, typename PtrL,
	typename RefR, typename PtrR>
inline bool
operator<(const Deque_iterator<T, RefL, PtrL> &x,
		  const Deque_iterator<T, RefR, PtrR> &y) {
  return (x.node == y.node) ? (x.cur < y.cur) : (x.node < y.node);
}

template<typename T, typename Ref, typename Ptr>
inline bool
operator>(const Deque_iterator<T, Ref, Ptr> &x,
		  const Deque_iterator<T, Ref, Ptr> &y) { return y < x; }

template<typename T, typename RefL, typename PtrL,
	typename RefR, typename PtrR>
inline bool
operator>(const Deque_iterator<T, RefL, PtrL> &x,
		  const Deque_iterator<T, RefR, PtrR> &y) { return y < x; }

template<typename T, typename Ref, typename Ptr>
inline bool
operator<=(const Deque_iterator<T, Ref, Ptr> &x,
		   const Deque_iterator<T, Ref, Ptr> &y) { return !(y < x); }

template<typename T, typename RefL, typename PtrL,
	typename RefR, typename PtrR>
inline bool
operator<=(const Deque_iterator<T, RefL, PtrL> &x,
		   const Deque_iterator<T, RefR, PtrR> &y) { return !(y < x); }

template<typename T, typename Ref, typename Ptr>
inline bool
operator>=(const Deque_iterator<T, Ref, Ptr> &x,
		   const Deque_iterator<T, Ref, Ptr> &y) { return !(x < y); }

template<typename T, typename RefL, typename PtrL,
	typename RefR, typename PtrR>
inline bool
operator>=(const Deque_iterator<T, RefL, PtrL> &x,
		   const Deque_iterator<T, RefR, PtrR> &y) { return !(x < y); }

template<typename T, typename Ref, typename Ptr>
inline typename Deque_iterator<T, Ref, Ptr>::difference_type
operator-(const Deque_iterator<T, Ref, Ptr> &x,
		  const Deque_iterator<T, Ref, Ptr> &y) {
  return typename Deque_iterator<T, Ref, Ptr>::difference_type
	  (Deque_iterator<T, Ref, Ptr>::_buffer_size())
	  * (x.node - y.node - 1) + (x.cur - x.first)
	  + (y.last - y.cur);
}

template<typename T, typename RefL, typename PtrL,
	typename RefR, typename PtrR>
inline typename Deque_iterator<T, RefL, PtrL>::difference_type
operator-(const Deque_iterator<T, RefL, PtrL> &x,
		  const Deque_iterator<T, RefR, PtrR> &y) {
  return typename Deque_iterator<T, RefL, PtrL>::difference_type
	  (Deque_iterator<T, RefL, PtrL>::_buffer_size())
	  * (x.node - y.node - 1) + (x.cur - x.first)
	  + (y.last - y.cur);
}

template<typename T, typename Ref, typename Ptr>
inline Deque_iterator<T, Ref, Ptr>
operator+(std::ptrdiff_t n, const Deque_iterator<T, Ref, Ptr> &x) { return x + n; }

template<typename ForwardIter, typename T>
inline void
_fill_a(ForwardIter first, ForwardIter last, const T &value) {
  for (; first != last; ++first)
	*first = value;
}

template<typename T>
void
fill(const Deque_iterator<T, T &, T *> &first,
	 const Deque_iterator<T, T &, T *> &last, const T &value) {
  typedef typename Deque_iterator<T, T &, T *>::_Self Self;

  for (typename Self::map_pointer node = first.node + 1; node < last
	  .node; ++node) {
	_fill_a(*node, *node + Self::_buffer_size(), value);
  }

  if (first.node != last.node) {
	_fill_a(first.cur, first.last, value);
	_fill_a(last.first, last.cur, value);
  } else {
	_fill_a(first.cur, last.cur, value);
  }
}

template<typename T>
Deque_iterator<T, T &, T *>
copy(Deque_iterator<T, const T &, const T *> first,
	 Deque_iterator<T, const T &, const T *> last,
	 Deque_iterator<T, T &, T *> result) {
  typedef typename Deque_iterator<T, T &, T *>::_Self Self;
  typedef typename Self::difference_type difference_type;

  difference_type len = last - first;
  while (len > 0) {
	difference_type clen = std::min(len, std::min(first.last - first
		.cur, result.last - result.cur));
	std::copy(first.cur, first.cur + clen, result);
	first += clen;
	result += clen;
	len -= clen;
  }
  return result;
}

template<typename T>
inline Deque_iterator<T, T &, T *>
copy(Deque_iterator<T, T &, T *> first,
	 Deque_iterator<T, T &, T *> last,
	 Deque_iterator<T, T &, T *> result) {
  return copy(Deque_iterator<T, const T &, const T *>(first),
			  Deque_iterator<T, const T &, const T *>(last), result);
}

template<typename T>
Deque_iterator<T, T &, T *>
copy_backward(Deque_iterator<T, const T &, const T *> first,
			  Deque_iterator<T, const T &, const T *> last,
			  Deque_iterator<T, T &, T *> result) {
  typedef typename Deque_iterator<T, T &, T *>::_Self Self;
  typedef typename Self::difference_type difference_type;

  difference_type len = last - first;
  while (len > 0) {
	difference_type llen = last.cur - last.first;
	T *lend = last.cur;

	difference_type rlen = result.cur - result.first;
	T *rend = result.cur;

	if (!llen) {
	  llen = Self::_buffer_size();
	  lend = *(last.node - 1) + llen;
	}

	if (!rlen) {
	  rlen = Self::_buffer_size();
	  rend = *(result.node - 1) + rlen;
	}

	difference_type clen = std::min(len, std::min(llen, rlen));
	std::copy_backward(lend - clen, lend, rend);
	last -= clen;
	result -= clen;
	len -= clen;
  }
  return result;
}

template<typename T>
inline Deque_iterator<T, T &, T *>
copy_backward(Deque_iterator<T, T &, T *> first,
			  Deque_iterator<T, T &, T *> last,
			  Deque_iterator<T, T &, T *> result) {
  return copy_backward(Deque_iterator<T, const T &, const T *>(first),
					   Deque_iterator<T, const T &, const T *>(last), result);
}

template<typename T, typename Alloc>
class Deque_base {
 protected:
  typedef typename Alloc::template rebind<T>::other T_alloc_type;

  typedef T *Ptr;
  typedef const T *Ptr_const;

  typedef typename Alloc::template rebind<Ptr>::other Map_alloc_type;

 public:
  typedef Alloc allocator_type;

  typedef Deque_iterator<T, T &, Ptr> iterator;
  typedef Deque_iterator<T, const T &, const Ptr> const_iterator;

  Deque_base()
	  : impl() { _initialize_map(0); }

  Deque_base(std::size_t num_elements)
	  : impl() { _initialize_map(num_elements); }

  Deque_base(const allocator_type &a, std::size_t num_elements)
	  : impl(a) { _initialize_map(num_elements); }

  Deque_base(const allocator_type &a)
	  : impl(a) {}

  ~Deque_base();

 protected:
  typedef typename iterator::map_pointer map_pointer;

  struct Deque_impl {
	T_alloc_type t_alloc;
	Map_alloc_type map_alloc;
	map_pointer map;
	std::size_t map_size;
	iterator start;
	iterator finish;

	Deque_impl()
		: t_alloc(), map_alloc(), map(), map_size(0), start(), finish
		() {}

	Deque_impl(const T_alloc_type &a)
		: t_alloc(a), map_alloc(a), map(), map_size(0), start(), finish() {}

	void
	_swap_data(Deque_impl &x) {
	  std::swap(this->start, x.start);
	  std::swap(this->finish, x.finish);
	  std::swap(this->map, x.map);
	  std::swap(this->map_size, x.map_size);
	  std::swap(this->t_alloc, x.t_alloc);
	  std::swap(this->map_alloc, x.map_alloc);
	}
  };

  Ptr
  _allocate_node() { return impl.t_alloc.allocate(_deque_buf_size(sizeof(T))); }

  void
  _deallocate_node(Ptr p) { impl.t_alloc.deallocate(p, _deque_buf_size(sizeof(T))); }

  map_pointer
  _allocate_map(std::size_t n) { return impl.map_alloc.allocate(n); }

  void
  _deallocate_map(map_pointer p, std::size_t n) { impl.map_alloc.deallocate(p, n); }

 protected:
  void _initialize_map(std::size_t);
  void _create_nodes(map_pointer start, map_pointer finish);
  void _destroy_nodes(map_pointer start, map_pointer finish);
  enum { _initial_map_size = 8 };

  Deque_impl impl;
};

template<typename T, typename Alloc>
Deque_base<T, Alloc>::~Deque_base() {
  if (this->impl.map) {
	_destroy_nodes(this->impl.start.node, this->impl.finish.node + 1);
	_deallocate_map(this->impl.map, this->impl.map_size);
  }
}

template<typename T, typename Alloc>
void
Deque_base<T, Alloc>::
_initialize_map(std::size_t num_elements) {
  std::size_t num_nodes = (num_elements / _deque_buf_size(sizeof(T)) + 1);
  impl.map_size = std::max((std::size_t) _initial_map_size,
						   std::size_t(num_nodes + 2));
  impl.map = _allocate_map(impl.map_size);

  map_pointer start = (impl.map + (impl.map_size -
	  num_nodes) / 2);
  map_pointer finish = start + num_nodes;

  try { _create_nodes(start, finish); }
  catch (...) {
	_deallocate_map(impl.map, impl.map_size);
	impl.map = map_pointer();
	impl.map_size = 0;
	throw;
  }

  impl.start._set_node(start);
  impl.finish._set_node(finish - 1);
  impl.start.cur = impl.start.first;
  impl.finish.cur = (impl.finish.first + num_elements %
	  _deque_buf_size(sizeof(T)));
}

template<typename T, typename Alloc>
void
Deque_base<T, Alloc>::
_create_nodes(map_pointer start, map_pointer finish) {
  map_pointer cur;
  try {
	for (cur = start; cur < finish; ++cur)
	  *cur = _allocate_node();
  }
  catch (...) {
	_destroy_nodes(start, cur);
	throw;
  }
}

template<typename T, typename Alloc>
void
Deque_base<T, Alloc>::
_destroy_nodes(map_pointer start, map_pointer finish) {
  for (map_pointer n = start; n < finish; ++n)
	_deallocate_node(*n);
}

template<typename T, typename Alloc = ft::Allocator<T> >
class deque : protected Deque_base<T, Alloc> {
 private:
  typedef Deque_base<T, Alloc> Base;
  typedef typename Base::T_alloc_type T_alloc_type;
  typedef typename Base::map_pointer map_pointer;

 public:
  typedef T value_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef typename Base::iterator iterator;
  typedef typename Base::const_iterator const_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Alloc allocator_type;

 protected:
  static std::size_t _buffer_size() { return _deque_buf_size(sizeof(T)); }

  using Base::_initialize_map;
  using Base::_create_nodes;
  using Base::_destroy_nodes;
  using Base::_allocate_node;
  using Base::_deallocate_node;
  using Base::_allocate_map;
  using Base::_deallocate_map;

  using Base::impl;

 protected:
  template<typename ForwardIter, typename T_, typename Alloc_>
  void
  _uninitialized_fill_a(ForwardIter first, ForwardIter last, const T_ &x,
						Alloc_ &alloc) {
	ForwardIter cur = first;
	try {
	  for (; cur != last; ++cur)
		alloc.construct(__builtin_addressof(*cur), x);
	}
	catch (...) {
	  for (; first != cur; ++first)
		alloc.destroy(__builtin_addressof(*first));
	  throw;
	}
  }

  template<typename InputIter, typename ForwardIter, typename Alloc_>
  ForwardIter
  _uninitialized_copy_a(InputIter first, InputIter last, ForwardIter
  result, Alloc_ &alloc) {
	ForwardIter cur = result;
	try {
	  for (; first != last; ++first, ++cur)
		alloc.construct(__builtin_addressof(*cur), *first);
	  return cur;
	}
	catch (...) {
	  for (; result != cur; ++result)
		alloc.destroy(__builtin_addressof(*result));
	  throw;
	}
  }

  template<typename InputIter, typename ForwardIter, typename T_,
	  typename Alloc_>
  inline void
  _uninitialized_copy_fill(InputIter first1, InputIter last1,
						   ForwardIter first2, ForwardIter last2,
						   const T_ &x, Alloc_ alloc) {
	ForwardIter mid2 = _uninitialized_copy_a(first1, last1,
											 first2, alloc);
	try {
	  _uninitialized_fill_a(mid2, last2, x, alloc);
	}
	catch (...) {
	  for (; first2 != mid2; ++first2)
		alloc.destroy(__builtin_addressof(*first2));
	  throw;
	}
  }

  template<typename ForwardIter, typename T_, typename InputIterator,
	  typename Alloc_>
  inline ForwardIter
  _uninitialized_fill_copy(ForwardIter result, ForwardIter mid,
						   const T_ &x, InputIterator first,
						   InputIterator last, Alloc_ &alloc) {
	_uninitialized_fill_a(result, mid, x, alloc);
	try {
	  return _uninitialized_copy_a(first, last, mid, alloc);
	}
	catch (...) {
	  for (; result != mid; ++result)
		alloc.destroy(__builtin_addressof(*result));
	  throw;
	}
  }

  template<typename InputIter1, typename InputIter2,
	  typename ForwardIter, typename _Alloc>
  inline ForwardIter
  _uninitialized_copy_copy(InputIter1 first1,
						   InputIter1 last1,
						   InputIter2 first2,
						   InputIter2 last2,
						   ForwardIter result,
						   _Alloc &alloc) {
	ForwardIter mid = _uninitialized_copy_a(first1, last1, result,
											alloc);
	try {
	  return _uninitialized_copy_a(first2, last2, mid, alloc);
	}
	catch (...) {
	  for (; result != mid; ++result)
		alloc.destroy(__builtin_addressof(*result));
	  throw;
	}
  }
  void
  _fill_initialize(const value_type &value) {
	map_pointer cur;
	try {
	  for (cur = impl.start.node; cur < impl.finish.node; ++cur)
		_uninitialized_fill_a(*cur, *cur + _buffer_size(), value,
							  impl.t_alloc);
	  _uninitialized_fill_a(impl.finish.first, impl.finish.cur, value,
							impl.t_alloc);
	}
	catch (...) {
	  for (iterator first = impl.start, last = iterator
		  (*cur, cur); first != last; ++first)
		impl.t_alloc.destroy(__builtin_addressof(*first));
	  throw;
	}
  }

  template<typename Integer>
  void
  _initialize_dispatch(Integer n, Integer x, std::__true_type) {
	_initialize_map(n);
	_fill_initialize(x);
  }

  template<typename InputIterator>
  void
  _initialize_dispatch(InputIterator first, InputIterator last,
					   std::__false_type) {
	_initialize_map(0);
	try {
	  for (; first != last; ++first)
		push_back(*first);
	}
	catch (...) {
	  clear();
	  throw;
	}
  }

  void
  _reallocate_map(size_type nodes_to_add, bool add_at_front) {
	size_type old_num_nodes = impl.finish.node - impl.start.node + 1;
	size_type new_num_nodes = old_num_nodes + nodes_to_add;

	map_pointer new_nstart;
	if (impl.map_size > 2 * new_num_nodes) {
	  new_nstart = impl.map + (impl.map_size - new_num_nodes) / 2
		  + (add_at_front ? nodes_to_add : 0);
	  if (new_nstart < impl.start.node) {
		std::copy(impl.start.node, impl.finish.node + 1,
				  new_nstart);
	  } else {
		std::copy_backward(impl.start.node, impl.finish.node + 1,
						   new_nstart + old_num_nodes);
	  }
	} else {
	  size_type new_map_size = impl.map_size + std::max(impl
															.map_size, nodes_to_add) + 2;

	  map_pointer new_map = _allocate_map(new_map_size);
	  new_nstart = new_map + (new_map_size - new_num_nodes) / 2
		  + (add_at_front ? nodes_to_add : 0);
	  std::copy(impl.start.node, impl.finish.node + 1, new_nstart);
	  _deallocate_map(impl.map, impl.map_size);

	  impl.map = new_map;
	  impl.map_size = new_map_size;
	}

	impl.start._set_node(new_nstart);
	impl.finish._set_node(new_nstart + old_num_nodes - 1);
  }

  void
  _reserve_map_at_back(size_type nodes_to_add = 1) {
	if (nodes_to_add + 1 > impl.map_size - (impl.finish.node - impl
		.map))
	  _reallocate_map(nodes_to_add, false);
  }

  void
  _reserve_map_at_front(size_type nodes_to_add = 1) {
	if (nodes_to_add > size_type(impl.start.node - impl.map))
	  _reallocate_map(nodes_to_add, true);
  }

  void
  _push_front_aux(const value_type &x) {
	_reserve_map_at_front();
	*(impl.start.node - 1) = _allocate_node();
	try {
	  impl.start._set_node(impl.start.node - 1);
	  impl.start.cur = impl.start.last - 1;
	  impl.t_alloc.construct(impl.start.cur, x);
	}
	catch (...) {
	  ++impl.start;
	  _deallocate_node(*(impl.start.node - 1));
	  throw;
	}
  }

  void
  _push_back_aux(const value_type &x) {
	_reserve_map_at_back();
	*(impl.finish.node + 1) = _allocate_node();
	try {
	  impl.t_alloc.construct(impl.finish.cur, x);
	  impl.finish._set_node(impl.finish.node + 1);
	  impl.finish.cur = impl.finish.first;
	}
	catch (...) {
	  _deallocate_node(*(impl.finish.node + 1));
	  throw;
	}
  }

  void
  _pop_front_aux() {
	impl.t_alloc.destroy(impl.start.cur);
	_deallocate_node(impl.start.first);
	impl.start._set_node(impl.start.node + 1);
	impl.start.cur = impl.start.first;
  }

  void
  _pop_back_aux() {
	_deallocate_node(impl.finish.first);
	impl.finish._set_node(impl.finish.node - 1);
	impl.finish.cur = impl.finish.last - 1;
	impl.t_alloc.destroy(impl.finish.cur);
  }

  void
  _destroy_data(iterator first, iterator last) {
	for (map_pointer node = first.node + 1; node < last.node; ++node)
	  for (pointer begin = *node; begin != *node + _buffer_size(); ++begin)
		impl.t_alloc.destroy(__builtin_addressof(*begin));

	if (first.node != last.node) {
	  for (pointer begin = first.cur, end = first.last; begin != end;
		   ++begin)
		impl.t_alloc.destroy(__builtin_addressof(*begin));
	  for (pointer begin = last.first, end = last.cur; begin != end;
		   ++begin)
		impl.t_alloc.destroy(__builtin_addressof(*begin));
	} else {
	  for (pointer begin = first.cur, end = last.cur; begin != end;
		   ++begin)
		impl.t_alloc.destroy(__builtin_addressof(*begin));
	}
  }

  void
  _erase_at_begin(iterator pos) {
	_destroy_data(begin(), pos);
	_destroy_nodes(impl.start.node, pos.node);
	impl.start = pos;
  }

  void
  _erase_at_end(iterator pos) {
	_destroy_data(pos, end());
	_destroy_nodes(pos.node + 1, impl.finish.node + 1);
	impl.finish = pos;
  }

  void
  _new_elements_at_front(size_type new_elems) {
	size_type new_nodes = ((new_elems + _buffer_size() - 1) /
		_buffer_size());
	_reserve_map_at_front(new_nodes);
	size_type i;
	try {
	  for (i = 1; i <= new_nodes; ++i)
		*(impl.start.node - i) = _allocate_node();
	}
	catch (...) {
	  for (size_type j = 1; j < i; ++j)
		_deallocate_node(*(impl.start.node - j));
	}
  }

  void
  _new_elements_at_back(size_type new_elems) {
	size_type new_nodes = ((new_elems + _buffer_size() - 1) /
		_buffer_size());
	_reserve_map_at_back(new_nodes);
	size_type i;
	try {
	  for (i = 1; i <= new_nodes; ++i)
		*(impl.finish.node + i) = _allocate_node();
	}
	catch (...) {
	  for (size_type j = 1; j < i; ++j)
		_deallocate_node(*(impl.finish.node + j));
	  throw;
	}
  }

  iterator
  _reserve_elements_at_front(size_type n) {
	size_type vacancies = impl.start.cur - impl.start.first;
	if (n > vacancies)
	  _new_elements_at_front(n - vacancies);
	return impl.start - difference_type(n);
  }

  iterator
  _reserve_elements_at_back(size_type n) {
	size_type vacancies = (impl.finish.last - impl.finish.cur) - 1;
	if (n > vacancies)
	  _new_elements_at_back(n - vacancies);
	return impl.finish + difference_type(n);
  }

  template<typename ForwardIter>
  void
  _range_insert_aux(iterator pos, ForwardIter first, ForwardIter last) {
	size_type n = 0;
	for (ForwardIter tmp = first; tmp != last; ++tmp)
	  ++n;
	if (pos.cur == impl.start.cur) {
	  iterator new_start = _reserve_elements_at_front(n);
	  try {
		_uninitialized_copy_a(first, last, new_start, impl.t_alloc);
		impl.start = new_start;
	  }
	  catch (...) {
		_destroy_nodes(new_start.node, impl.start.node);
		throw;
	  }
	} else if (pos.cur == impl.finish.cur) {
	  iterator new_finish = _reserve_elements_at_back(n);
	  try {
		_uninitialized_copy_a(first, last, impl.finish, impl
			.t_alloc);
		impl.finish = new_finish;
	  }
	  catch (...) {
		_destroy_nodes(impl.finish.node + 1, new_finish.node + 1);
		throw;
	  }
	} else {
	  _insert_aux(pos, first, last, n);
	}
  }

  void
  _insert_aux(iterator pos, size_type n, const value_type &x) {
	difference_type elems_before = pos - impl.start;
	size_type length = size();
	value_type x_copy = x;
	if (elems_before < difference_type(length / 2)) {
	  iterator new_start = _reserve_elements_at_front(n);
	  iterator old_start = impl.start;
	  pos = impl.start + elems_before;
	  try {
		if (elems_before >= difference_type(n)) {
		  iterator start_n = impl.start + difference_type(n);
		  _uninitialized_copy_a(impl.start, start_n, new_start,
								impl.t_alloc);
		  impl.start = new_start;
		  std::copy(start_n, pos, old_start);
		  fill(pos - difference_type(n), pos, x_copy);
		} else {
		  _uninitialized_copy_fill(impl.start, pos, new_start,
								   impl.start, x_copy,
								   impl.t_alloc);
		  impl.start = new_start;
		  fill(old_start, pos, x_copy);
		}
	  }
	  catch (...) {
		_destroy_nodes(new_start.node, impl.start.node);
		throw;
	  }
	} else {
	  iterator new_finish = _reserve_elements_at_back(n);
	  iterator old_finish = impl.finish;
	  difference_type elems_after = difference_type(length) -
		  elems_before;
	  pos = impl.finish - elems_after;
	  try {
		if (elems_after > difference_type(n)) {
		  iterator finish_n = impl.finish - difference_type(n);
		  _uninitialized_copy_a(finish_n, impl.finish, impl
			  .finish, impl.t_alloc);
		  impl.finish = new_finish;
		  std::copy_backward(pos, finish_n, old_finish);
		  fill(pos, pos + difference_type(n), x_copy);
		} else {
		  _uninitialized_fill_copy(impl.finish, pos +
									   difference_type(
										   n),
								   x_copy, pos, impl.finish,
								   impl.t_alloc);
		  impl.finish = new_finish;
		  fill(pos, old_finish, x_copy);
		}
	  }
	  catch (...) {
		_destroy_nodes(impl.finish.node + 1, new_finish.node + 1);
		throw;
	  }
	}
  }

  iterator
  _insert_aux(iterator pos, const value_type &x) {
	value_type x_copy = x;
	difference_type index = pos - impl.start;
	if (static_cast<size_type>(index) < size() / 2) {
	  push_front(front());
	  iterator front1 = impl.start;
	  ++front1;
	  iterator front2 = front1;
	  ++front2;
	  pos = impl.start + index;
	  iterator pos1 = pos;
	  ++pos1;
	  copy(front2, pos1, front1);
	} else {
	  push_back(back());
	  iterator back1 = impl.finish;
	  --back1;
	  iterator back2 = back1;
	  --back2;
	  pos = impl.start + index;
	  copy_backward(pos, back2, back1);
	}
	*pos = x_copy;
	return pos;
  }

  void
  _fill_insert(iterator pos, size_type n, const value_type &x) {
	if (pos.cur == impl.start.cur) {
	  iterator new_start = _reserve_elements_at_front(n);
	  try {
		_uninitialized_fill_a(new_start, impl.start, x,
							  impl.t_alloc);
		impl.start = new_start;
	  }
	  catch (...) {
		_destroy_nodes(new_start.node, impl.start.node);
		throw;
	  }
	} else if (pos.cur == impl.finish.cur) {
	  iterator new_finish = _reserve_elements_at_back(n);
	  try {
		_uninitialized_fill_a(impl.finish, new_finish, x,
							  impl.t_alloc);
		impl.finish = new_finish;
	  }
	  catch (...) {
		_destroy_nodes(impl.finish.node + 1, new_finish.node + 1);
		throw;
	  }
	} else {
	  _insert_aux(pos, n, x);
	}
  }

  template<typename ForwardIter>
  void
  _insert_aux(iterator pos, ForwardIter first, ForwardIter last,
			  size_type n) {
	const difference_type elemsbefore = pos - impl.start;
	const size_type length = size();
	if (static_cast<size_type>(elemsbefore) < length / 2) {
	  iterator new_start = _reserve_elements_at_front(n);
	  iterator old_start = impl.start;
	  pos = impl.start + elemsbefore;
	  try {
		if (elemsbefore >= difference_type(n)) {
		  iterator start_n = (impl.start + difference_type(n));
		  _uninitialized_copy_a(impl.start, start_n, new_start,
								impl.t_alloc);
		  impl.start = new_start;
		  std::copy(start_n, pos, old_start);
		  std::copy(first, last, pos - difference_type(n));
		} else {
		  ForwardIter mid = first;
		  for (int i = 0; i < difference_type(n) - elemsbefore;
			   ++i)
			++mid;
		  _uninitialized_copy_copy(impl.start, pos, first, mid,
								   new_start, impl.t_alloc);
		  impl.start = new_start;
		  std::copy(mid, last, old_start);
		}
	  }
	  catch (...) {
		_destroy_nodes(new_start.node, impl.start.node);
		throw;
	  }
	} else {
	  iterator new_finish = _reserve_elements_at_back(n);
	  iterator old_finish = impl.finish;
	  const difference_type elemsafter = difference_type(length) -
		  elemsbefore;
	  pos = impl.finish - elemsafter;
	  try {
		if (elemsafter > difference_type(n)) {
		  iterator finish_n = (impl.finish - difference_type(n));
		  _uninitialized_copy_a(finish_n, impl.finish, impl
			  .finish, impl.t_alloc);
		  impl.finish = new_finish;
		  std::copy_backward(pos, finish_n, old_finish);
		  std::copy(first, last, pos);
		} else {
		  ForwardIter mid = first;
		  for (int i = 0; i < elemsafter; ++i)
			++mid;
		  _uninitialized_copy_copy(mid, last, pos, impl.finish,
								   impl.finish, impl.t_alloc);
		  impl.finish = new_finish;
		  std::copy(first, mid, pos);
		}
	  }
	  catch (...) {
		_destroy_nodes(impl.finish.node + 1, new_finish.node + 1);
		throw;
	  }
	}
  }

  void
  _fill_assign(size_type n, const value_type &val) {
	if (n > size()) {
	  fill(begin(), end(), val);
	  _fill_insert(end(), n - size(), val);
	} else {
	  _erase_at_end(begin() + difference_type(n));
	  fill(begin(), end(), val);
	}
  }

  template<typename InputIter>
  void
  _assign_aux(InputIter first, InputIter last) {
	iterator cur = begin();
	for (; first != last && cur != end(); ++cur, ++first)
	  *cur = *first;
	if (first == last)
	  _erase_at_end(cur);
	else
	  _range_insert_aux(end(), first, last);
  }

  template<typename Integer>
  void
  _assign_dispatch(Integer n, Integer val, std::__true_type) { _fill_assign(n, val); }

  template<typename InputIter>
  void
  _assign_dispatch(InputIter first, InputIter last, std::__false_type) {
	_assign_aux(first,
				last);
  }

  void
  _range_check(size_type n) const {
	if (n >= size()) {
	  std::stringstream ss;
	  ss << "deque::_range_check: n (which is " << n << ")>= ";
	  ss << "this->size() (which is " << size() << ")";
	  throw std::out_of_range(ss.str());
	}
  }

  template<typename Integer>
  void
  _insert_dispatch(iterator pos,
				   Integer n,
				   Integer x,
				   std::__true_type) { _fill_insert(pos, n, x); }

  template<typename InputIter>
  void
  _insert_dispatch(iterator pos, InputIter first, InputIter last,
				   std::__false_type) { _range_insert_aux(pos, first, last); }

  iterator
  _erase(iterator position) {
	iterator next = position;
	++next;
	difference_type index = position - begin();
	if (static_cast<size_type>(index) < (size() >> 1)) {
	  if (position != begin())
		std::copy_backward(begin(), position, next);
	  pop_front();
	} else {
	  if (next != end())
		std::copy(next, end(), position);
	  pop_back();
	}
	return begin() + index;
  }

  iterator
  _erase(iterator first, iterator last) {
	if (first == last)
	  return first;
	else if (first == begin() && last == end()) {
	  clear();
	  return end();
	} else {
	  difference_type n = last - first;
	  difference_type elems_before = first - begin();
	  if (static_cast<size_type>(elems_before) <= (size() - n) / 2) {
		if (first != begin())
		  std::copy_backward(begin(), first, last);
		_erase_at_begin(begin() + n);
	  } else {
		if (last != end())
		  std::copy(last, end(), first);
		_erase_at_end(end() - n);
	  }
	  return begin() + elems_before;
	}
  }

 public:

  /****************************************/
  /*                                      */
  /*           Constructors               */
  /*                                      */
  /****************************************/

  deque() : Base() {}

  explicit
  deque(const allocator_type &a)
	  : Base(a, 0) {}

  explicit
  deque(size_type n, const value_type &value = value_type(),
		const allocator_type &a = allocator_type())
	  : Base(a, n) { _fill_initialize(value); }

  deque(const deque &x)
	  : Base(x.size()) {
	_uninitialized_copy_a(x.begin(), x.end(), this->impl.start,
						  impl.t_alloc);
  }

  template<typename InputIter>
  deque(InputIter first, InputIter last, const allocator_type &a =
  allocator_type())
	  : Base(a) {
	typedef typename std::__is_integer<InputIter>::__type Integral;
	_initialize_dispatch(first, last, Integral());
  }

  /****************************************/
  /*                                      */
  /*           Destructor                 */
  /*                                      */
  /****************************************/

  ~deque() { _destroy_data(begin(), end()); }

  /****************************************/
  /*                                      */
  /*           Operator=                  */
  /*                                      */
  /****************************************/

  deque &
  operator=(const deque &x) {
	if (&x != this) {
	  size_type len = size();
	  if (len >= x.size())
		_erase_at_end(std::copy(x.begin(), x.end(), impl.start));
	  else {
		const_iterator mid = x.begin() + difference_type(len);
		std::copy(x.begin(), mid, impl.start);
		_range_insert_aux(impl.finish, mid, x.end());
	  }
	}
	return *this;
  }

  void
  assign(size_type n, const value_type &val) { _fill_assign(n, val); }

  template<typename InputIter>
  void
  assign(InputIter first, InputIter last) {
	typedef typename std::__is_integer<InputIter>::__type Integral;
	_assign_dispatch(first, last, Integral());
  }

  /****************************************/
  /*                                      */
  /*           Iterators                  */
  /*                                      */
  /****************************************/

  iterator
  begin() { return impl.start; }

  const_iterator
  begin() const { return impl.start; }

  iterator
  end() { return impl.finish; }

  const_iterator
  end() const { return impl.finish; }

  reverse_iterator
  rbegin() { return reverse_iterator(impl.finish); }

  const_reverse_iterator
  rbegin() const { return const_reverse_iterator(impl.finish); }

  reverse_iterator
  rend() { return reverse_iterator(impl.start); }

  const_reverse_iterator
  rend() const { return const_reverse_iterator(impl.start); }

  /****************************************/
  /*                                      */
  /*           Capacity                   */
  /*                                      */
  /****************************************/

  size_type
  size() const { return impl.finish - impl.start; }

  size_type
  max_size() const {
	std::size_t diffmax = __gnu_cxx::__numeric_traits<std::ptrdiff_t
	>::__max;
	std::size_t allocmax = impl.t_alloc.max_size();
	return std::min(diffmax, allocmax);
  }

  void
  resize(size_type new_size, value_type x = value_type()) {
	size_type len = size();
	if (new_size > len)
	  _fill_insert(impl.finish, new_size - len, x);
	else if (new_size < len)
	  _erase_at_end(impl.start + difference_type(new_size));
  }

  bool
  empty() const { return impl.finish == impl.start; }

  /****************************************/
  /*                                      */
  /*           Element access             */
  /*                                      */
  /****************************************/

  reference
  operator[](size_type n) { return impl.start[difference_type(n)]; }

  const_reference
  operator[](size_type n) const { return impl.start[difference_type(n)]; }

  reference
  at(size_type n) {
	_range_check(n);
	return (*this)[n];
  }

  const_reference
  at(size_type n) const {
	_range_check(n);
	return (*this)[n];
  }

  reference
  front() { return *begin(); }

  const_reference
  front() const { return *begin(); }

  reference
  back() {
	iterator tmp = end();
	--tmp;
	return *tmp;
  }

  const_reference
  back() const {
	const_iterator tmp = end();
	--tmp;
	return *tmp;
  }

  /****************************************/
  /*                                      */
  /*           Modifiers                  */
  /*                                      */
  /****************************************/

  void
  push_front(const value_type &x) {
	if (impl.start.cur != impl.start.first) {
	  impl.t_alloc.construct(impl.start.cur - 1, x);
	  --impl.start.cur;
	} else
	  _push_front_aux(x);
  }

  void
  push_back(const value_type &x) {
	if (impl.finish.cur != impl.finish.last - 1) {
	  impl.t_alloc.construct(impl.finish.cur, x);
	  ++impl.finish.cur;
	} else {
	  _push_back_aux(x);
	}
  }

  void
  pop_front() {
	if (impl.start.cur != impl.start.last - 1) {
	  impl.t_alloc.destroy(impl.start.cur);
	  ++impl.start.cur;
	} else {
	  _pop_front_aux();
	}
  }

  void
  pop_back() {
	if (impl.finish.cur != impl.finish.first) {
	  --impl.finish.cur;
	  impl.t_alloc.destroy(impl.finish.cur);
	} else {
	  _pop_back_aux();
	}
  }

  iterator
  insert(iterator position, const value_type &x) {
	if (position.cur == impl.start.cur) {
	  push_front(x);
	  return impl.start;
	} else if (position.cur == impl.finish.cur) {
	  push_back(x);
	  iterator tmp = impl.finish;
	  --tmp;
	  return tmp;
	} else {
	  return _insert_aux(position._const_cast(), x);
	}
  }

  void
  insert(iterator position, size_type n, const value_type &x) {
	_fill_insert(position,
				 n,
				 x);
  }

  template<typename InputIter>
  void
  insert(iterator position, InputIter first, InputIter last) {
	typedef typename std::__is_integer<InputIter>::__type Integral;
	_insert_dispatch(position, first, last, Integral());
  }

  iterator
  erase(iterator position) { return _erase(position._const_cast()); }

  iterator
  erase(iterator first, iterator last) {
	return _erase(first._const_cast(),
				  last._const_cast());
  }

  void
  swap(deque &x) { impl._swap_data(x.impl); }

  void
  clear() { _erase_at_end(begin()); }
};

template<typename T, typename Alloc>
inline bool
operator==(const deque<T, Alloc> &x, const deque<T, Alloc> &y) {
  if (x.size() != y.size())
	return false;
  typename deque<T, Alloc>::const_iterator x_first = x.begin();
  typename deque<T, Alloc>::const_iterator x_last = x.end();
  typename deque<T, Alloc>::const_iterator y_first = y.begin();
  for (; x_first != x_last; ++x_first, ++y_first) {
	if (*x_first != *y_first)
	  return false;
  }
  return true;
}

template<typename T, typename Alloc>
inline bool
operator<(const deque<T, Alloc> &x, const deque<T, Alloc> &y) {
  typename deque<T, Alloc>::const_iterator x_first = x.begin();
  typename deque<T, Alloc>::const_iterator x_last = x.end();
  typename deque<T, Alloc>::const_iterator y_first = y.begin();
  typename deque<T, Alloc>::const_iterator y_last = y.end();
  while (x_first != x_last || y_first != y_last) {
	if (!(*x_first < *y_first) && !(*y_first < *x_first)) {
	  ++x_first;
	  ++y_first;
	  continue;
	}
	if (*x_first < *y_first)
	  return (true);
	return (false);
  }
  if (x_first == x_last && y_first == y_last)
	return (false);
  if (x_first == x_last)
	return (true);
  return (false);
}

template<typename T, typename Alloc>
inline bool
operator!=(const deque<T, Alloc> &x,
		   const deque<T, Alloc> &y) { return !(x == y); }

template<typename T, typename Alloc>
inline bool
operator>(const deque<T, Alloc> &x,
		  const deque<T, Alloc> &y) { return y < x; }

template<typename T, typename Alloc>
inline bool
operator<=(const deque<T, Alloc> &x,
		   const deque<T, Alloc> &y) { return !(y < x); }

template<typename T, typename Alloc>
inline bool
operator>=(const deque<T, Alloc> &x,
		   const deque<T, Alloc> &y) { return !(x < y); }

template<typename T, typename Alloc>
inline void
swap(deque<T, Alloc> &x, deque<T, Alloc> &y) { x.swap(y); }
}
#endif
