#ifndef FT_CONTAINERS_FT_CONTAINERS_MULTIMAP_HPP_
#define FT_CONTAINERS_FT_CONTAINERS_MULTIMAP_HPP_


#include "tree.hpp"

namespace ft {
template <typename Key, typename Value, typename Compare = std::less<Key> >
class multimap {
 public:
  typedef Key							key_type;
  typedef Value							mapped_type;
  typedef std::pair<const Key, Value>	value_type;
  typedef Compare						key_compare;

 public:
  class value_compare : public std::binary_function<value_type, value_type, bool> {
	friend class multimap<Key, Value, Compare>;
   protected:
	Compare comp;

	value_compare(Compare c) : comp(c) { }

   public:
	typedef bool		result_type;
	typedef value_type	first_argument_type;
	typedef value_type	second_argument_type;
	bool operator()(const value_type& x, const value_type& y) const
	{ return comp(x.first, y.first); }
  };

 private:
  typedef Rb_tree<key_type, value_type, std::_Select1st<value_type>, key_compare> Rep_type;

  Rep_type t;

 public:
  typedef value_type*								pointer;
  typedef const value_type*							const_pointer;
  typedef value_type&								reference;
  typedef const value_type&							const_reference;
  typedef typename Rep_type::iterator				iterator;
  typedef typename Rep_type::const_iterator			const_iterator;
  typedef typename Rep_type::size_type				size_type;
  typedef typename Rep_type::difference_type		difference_type;
  typedef typename Rep_type::reverse_iterator		reverse_iterator;
  typedef typename Rep_type::const_reverse_iterator	const_reverse_iterator;

  /****************************************/
  /*                                      */
  /*           Constructors               */
  /*                                      */
  /****************************************/

  multimap() : t() { }

  explicit
  multimap(const Compare& comp) :t(comp) { }

  multimap(const multimap& x) : t(x.t) { }

  template<typename InputIter>
  multimap(InputIter first, InputIter last) : t()
  { t.insert_range_equal(first, last); }

  template<typename InputIter>
  multimap(InputIter first, InputIter last, const Compare& comp)
	  : t(comp)
  { t.insert_range_equal(first, last); }

  /****************************************/
  /*                                      */
  /*           Assignment operator        */
  /*                                      */
  /****************************************/

  multimap&
  operator=(const multimap& x) {
	t = x.t;
	return *this;
  }

  /****************************************/
  /*                                      */
  /*           Iterators                  */
  /*                                      */
  /****************************************/

  iterator
  begin()
  { return t.begin(); }

  const_iterator
  begin() const
  { return t.begin(); }

  iterator
  end()
  { return t.end(); }

  const_iterator
  end() const
  { return t.end(); }

  reverse_iterator
  rbegin()
  { return t.rbegin(); }

  const_reverse_iterator
  rbegin() const
  { return t.rbegin(); }

  reverse_iterator
  rend()
  { return t.rend(); }

  const_reverse_iterator
  rend() const
  { return t.rend(); }

  /****************************************/
  /*                                      */
  /*           Capacity                   */
  /*                                      */
  /****************************************/

  bool
  empty() const
  { return t.empty(); }

  size_type
  size() const
  { return t.size(); }

  size_type
  max_size() const
  { return t.max_size(); }

  /****************************************/
  /*                                      */
  /*           Modifiers                  */
  /*                                      */
  /****************************************/

  iterator
  insert(const value_type& x)
  { return t.insert_equal(x); }

  iterator
  insert(iterator position, const value_type& x)
  { return t.insert_equal(position, x); }

  template<typename InputIterator>
  void
  insert(InputIterator first, InputIterator last)
  { t.insert_range_equal(first, last); }

  void
  erase(iterator position)
  { t.erase(position); }

  size_type
  erase(const key_type& x)
  { return t.erase(x); }

  void
  erase(iterator first, iterator last)
  { t.erase(first, last); }

  void
  swap(multimap &x)
  { t.swap(x.t); }

  void
  clear()
  { t.clear(); }

  /****************************************/
  /*                                      */
  /*           Observers                  */
  /*                                      */
  /****************************************/

  key_compare
  key_comp() const
  { return t.key_comp(); }

  value_compare
  value_com() const
  { return value_compare(t.key_comp()); }

  /****************************************/
  /*                                      */
  /*           Map operations             */
  /*                                      */
  /****************************************/

  iterator
  find(const key_type& x)
  { return t.find(x); }

  const_iterator
  find(const key_type& x) const
  { return t.find(x); }

  size_type
  count(const key_type& x) const
  { return t.count(x); }

  iterator
  lower_bound(const key_type& x)
  { return t.lower_bound(x); }

  const_iterator
  lower_bound(const key_type& x) const
  { return t.lower_bound(x); }

  iterator
  upper_bound(const key_type& x)
  { return t.upper_bound(x); }

  const_iterator
  upper_bound(const key_type& x) const
  { return t.upper_bound(x); }

  std::pair<iterator, iterator>
  equal_range(const key_type& x)
  { return t.equal_range(x); }

  std::pair<const_iterator, const_iterator>
  equal_range(const key_type& x) const
  { return t.equal_range(x); }

  template<typename K, typename V, typename C>
  friend bool
  operator==(const multimap<K, V, C>&, const multimap<K, V, C>&);


  template<typename K, typename V, typename C>
  friend bool
  operator<(const multimap<K, V, C>&, const multimap<K, V, C>&);
};

template<typename Key, typename Value, typename Compare>
inline bool
operator==(const multimap<Key, Value, Compare>& x, const multimap<Key, Value, Compare>& y)
{ return x.t == y.t; }


template<typename Key, typename Value, typename Compare>
inline bool
operator<(const multimap<Key, Value, Compare>& x, const multimap<Key, Value, Compare>& y)
{ return x.t < y.t; }


template<typename Key, typename Value, typename Compare>
inline bool
operator!=(const multimap<Key, Value, Compare>& x, const multimap<Key, Value, Compare>& y)
{ return !(x == y); }


template<typename Key, typename Value, typename Compare>
inline bool
operator>(const multimap<Key, Value, Compare>& x, const multimap<Key, Value, Compare>& y)
{ return y < x; }


template<typename Key, typename Value, typename Compare>
inline bool
operator<=(const multimap<Key, Value, Compare>& x, const multimap<Key, Value, Compare>& y)
{ return !(y < x); }


template<typename Key, typename Value, typename Compare>
inline bool
operator>=(const multimap<Key, Value, Compare>& x, const multimap<Key, Value, Compare>& y)
{ return !(x < y); }


template<typename Key, typename Value, typename Compare>
inline void
swap(multimap<Key, Value, Compare>& x, multimap<Key, Value, Compare>& y)
{ x.swap(y); }
}

#endif
