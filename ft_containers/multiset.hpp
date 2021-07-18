#ifndef FT_CONTAINERS_FT_CONTAINERS_MULTISET_HPP_
#define FT_CONTAINERS_FT_CONTAINERS_MULTISET_HPP_

#include "tree.hpp"

namespace ft {

template<typename Key, typename Compare = std::less<Key> >
class multiset {
 public:
  typedef Key key_type;
  typedef Key value_type;
  typedef Compare key_compare;
  typedef Compare value_compare;

 private:
  typedef Rb_tree<key_type, value_type, std::_Identity<value_type>, key_compare> Rep_type;
  Rep_type t;

 public:
  typedef Key *pointer;
  typedef const Key *const_pointer;
  typedef Key &reference;
  typedef const Key &const_reference;
  typedef typename Rep_type::const_iterator iterator;
  typedef typename Rep_type::const_iterator const_iterator;
  typedef typename Rep_type::const_reverse_iterator reverse_iterator;
  typedef typename Rep_type::const_reverse_iterator const_reverse_iterator;
  typedef typename Rep_type::size_type size_type;
  typedef typename Rep_type::difference_type difference_type;

  /****************************************/
  /*                                      */
  /*           Constructors               */
  /*                                      */
  /****************************************/

  multiset() : t() {}

  explicit
  multiset(const Compare &comp) : t(comp) {}

  template<typename InputIterator>
  multiset(InputIterator first, InputIterator last)
	  : t() { t.insert_range_equal(first, last); }

  template<typename InputIterator>
  multiset(InputIterator first, InputIterator last,
		   const Compare &comp)
	  : t(comp) { t.insert_range_equal(first, last); }

  multiset(const multiset &x)
	  : t(x.t) {}

  multiset &
  operator=(const multiset &x) {
	t = x.t;
	return *this;
  }

  /****************************************/
  /*                                      */
  /*           Observers                  */
  /*                                      */
  /****************************************/

  key_compare
  key_comp() const { return t.key_comp(); }

  value_compare
  value_comp() const { return t.key_comp(); }

  /****************************************/
  /*                                      */
  /*           Iterators                  */
  /*                                      */
  /****************************************/

  iterator
  begin() const { return t.begin(); }

  iterator
  end() const { return t.end(); }

  reverse_iterator
  rbegin() const { return t.rbegin(); }

  reverse_iterator
  rend() const { return t.rend(); }

  /****************************************/
  /*                                      */
  /*           Capacity                   */
  /*                                      */
  /****************************************/

  bool
  empty() const { return t.empty(); }

  size_type
  size() const { return t.size(); }

  size_type
  max_size() const { return t.max_size(); }

  /****************************************/
  /*                                      */
  /*           Modifiers                  */
  /*                                      */
  /****************************************/

  void
  swap(multiset &x) {
	t.swap(x.t);
  }

  iterator
  insert(const value_type &x) { return t.insert_equal(x); }

  iterator
  insert(const_iterator position, const value_type &x) {
	return t.insert_equal(position,
						  x);
  }

  template<typename InputIterator>
  void
  insert(InputIterator first, InputIterator last) {
	t.template insert_range_equal(first,
								  last);
  }

  void
  erase(iterator position) { t.erase(position); }

  size_type
  erase(const key_type &x) { return t.erase(x); }

  void
  erase(iterator first, iterator last) { t.erase(first, last); }

  void
  clear() { t.clear(); }

  /****************************************/
  /*                                      */
  /*           Set operations             */
  /*                                      */
  /****************************************/

  size_type
  count(const key_type &x) const { return t.count(x); }

  iterator
  find(const key_type &x) { return t.find(x); }

  const_iterator
  find(const key_type &x) const { return t.find(x); }

  iterator
  lower_bound(const key_type &x) { return t.lower_bound(x); }

  const_iterator
  lower_bound(const key_type &x) const { return t.lower_bound(x); }

  iterator
  upper_bound(const key_type &x) { return t.upper_bound(x); }

  const_iterator
  upper_bound(const key_type &x) const { return t.upper_bound(x); }

  std::pair<iterator, iterator>
  equal_range(const key_type &x) { return t.equal_range(x); }

  std::pair<const_iterator, const_iterator>
  equal_range(const key_type &x) const { return t.equal_range(x); }

  template<typename K1, typename C1>
  friend bool
  operator==(const multiset<K1, C1> &, const multiset<K1, C1> &);

  template<typename K1, typename C1>
  friend bool
  operator<(const multiset<K1, C1> &, const multiset<K1, C1> &);
};

template<typename Key, typename Compare>
inline bool
operator==(const multiset<Key, Compare> &x, const multiset<Key, Compare> &y) {
  return x.t == y.t;
}

template<typename Key, typename Compare>
inline bool
operator<(const multiset<Key, Compare> &x, const multiset<Key, Compare> &y) {
  return x.t < y.t;
}

template<typename Key, typename Compare>
inline bool
operator!=(const multiset<Key, Compare> &x, const multiset<Key, Compare> &y) {
  return !(x == y);
}

template<typename Key, typename Compare>
inline bool
operator>(const multiset<Key, Compare> &x, const multiset<Key, Compare> &y) {
  return y < x;
}

template<typename Key, typename Compare>
inline bool
operator<=(const multiset<Key, Compare> &x, const multiset<Key, Compare> &y) {
  return !(y < x);
}

template<typename Key, typename Compare>
inline bool
operator>=(const multiset<Key, Compare> &x, const multiset<Key, Compare> &y) {
  return !(x < y);
}

template<typename Key, typename Compare>
inline void
swap(multiset<Key, Compare> &x, multiset<Key, Compare> &y) { x.swap(y); }
}

#endif
