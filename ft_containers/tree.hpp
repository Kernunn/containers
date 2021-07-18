#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include <iterator>
#include "reverse_iterator.h"
#include <limits>
#include <iostream>
#include <vector>

namespace ft {
enum Rb_tree_color { red = false, black = true };

struct Rb_tree_node_base {
  typedef Rb_tree_node_base *Base_ptr;
  typedef const Rb_tree_node_base *Const_base_ptr;

  Rb_tree_color color;
  Base_ptr parent;
  Base_ptr left;
  Base_ptr right;

  Rb_tree_node_base() {}

  Rb_tree_node_base(Base_ptr node) {
	color = red;
	parent = node->parent;
	left = node->left;
	right = node->right;
  }
  static Base_ptr
  _s_minimum(Base_ptr x, Base_ptr end) {
	while (x->left != end)
	  x = x->left;
	return x;
  }

  static Const_base_ptr
  _s_minimum(Const_base_ptr x, Const_base_ptr end) {
	while (x->left != end)
	  x = x->left;
	return x;
  }

  static Base_ptr
  _s_maximum(Base_ptr x, Base_ptr end) {
	while (x->right != end)
	  x = x->right;
	return x;
  }

  static Const_base_ptr
  _s_maximum(Const_base_ptr x, Const_base_ptr end) {
	while (x->right != end)
	  x = x->right;
	return x;
  }

};

struct Rb_tree_header {
  Rb_tree_node_base header;
  std::size_t node_count;

  Rb_tree_header() : header() {
	header.color = black;
	reset();
  }

  void
  reset() {
	header.parent = &header;
	header.left = &header;
	header.right = &header;
	node_count = 0;
  }
};

template<typename Val>
struct Rb_tree_node : public Rb_tree_node_base {
  typedef Rb_tree_node<Val> *Link_type;

  Val value_field;

  Rb_tree_node(Val value) : Rb_tree_node_base(), value_field(value) {}

  Rb_tree_node(Val value, Base_ptr node) : Rb_tree_node_base(node), value_field(value) {}

  Val *
  valptr() { return __builtin_addressof(value_field); }

  const Val *
  valptr() const { return __builtin_addressof(value_field); }
};

Rb_tree_node_base *
Rb_tree_increment(Rb_tree_node_base *x, Rb_tree_node_base *end);
const Rb_tree_node_base *
Rb_tree_increment(const Rb_tree_node_base *x, const Rb_tree_node_base *end);

Rb_tree_node_base *
Rb_tree_decrement(Rb_tree_node_base *x, Rb_tree_node_base *end);
const Rb_tree_node_base *
Rb_tree_decrement(const Rb_tree_node_base *x, const Rb_tree_node_base *end);

template<typename Tp>
struct Rb_tree_iterator {
  typedef Tp value_type;
  typedef Tp &reference;
  typedef Tp *pointer;

  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;

  typedef Rb_tree_iterator<Tp> Self;
  typedef Rb_tree_node_base::Base_ptr Base_ptr;
  typedef Rb_tree_node<Tp> *Link_type;

  Rb_tree_iterator()
	  : node() {}

  explicit
  Rb_tree_iterator(Base_ptr x, Base_ptr end)
	  : node(x), end(end) {}

  reference
  operator*() const { return *static_cast<Link_type>(node)->valptr(); }

  pointer
  operator->() const { return static_cast<Link_type>(node)->valptr(); }

  Self &
  operator++() {
	node = Rb_tree_increment(node, end);
	return *this;
  }

  Self
  operator++(int) {
	Self tmp = *this;
	node = Rb_tree_increment(node, end);
	return tmp;
  }

  Self &
  operator--() {
	node = Rb_tree_decrement(node, end);
	return *this;
  }

  Self
  operator--(int) {
	Self tmp = *this;
	node = Rb_tree_decrement(node, end);
	return tmp;
  }

  friend bool
  operator==(const Self &x, const Self &y) { return x.node == y.node; }

  friend bool
  operator!=(const Self &x, const Self &y) { return x.node != y.node; }

  Base_ptr node;
  Base_ptr end;
};

template<typename Tp>
struct Rb_tree_const_iterator {
  typedef Tp value_type;
  typedef const Tp &reference;
  typedef const Tp *pointer;

  typedef Rb_tree_iterator<Tp> iterator;

  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;

  typedef Rb_tree_const_iterator<Tp> Self;
  typedef Rb_tree_node_base::Const_base_ptr Base_ptr;
  typedef const Rb_tree_node<Tp> *Link_type;

  Rb_tree_const_iterator()
	  : node() {}

  explicit
  Rb_tree_const_iterator(Base_ptr x, Base_ptr end)
	  : node(x), end(end) {}

  Rb_tree_const_iterator(const iterator &it)
	  : node(it.node), end(it.end) {}

  iterator
  _const_cast() const {
	return iterator(const_cast<typename iterator::Base_ptr>(node),
					const_cast<typename iterator::Base_ptr>(end));
  }

  reference
  operator*() const { return *static_cast<Link_type>(node)->valptr(); }

  pointer
  operator->() const { return static_cast<Link_type>(node)->valptr(); }

  Self &
  operator++() {
	node = Rb_tree_increment(node, end);
	return *this;
  }

  Self
  operator++(int) {
	Self tmp = *this;
	node = Rb_tree_increment(node, end);
	return tmp;
  }

  Self &
  operator--() {
	node = Rb_tree_decrement(node, end);
	return *this;
  }

  Self
  operator--(int) {
	Self tmp = *this;
	node = Rb_tree_decrement(node, end);
	return tmp;
  }

  friend bool
  operator==(const Self &x, const Self &y) { return x.node == y.node; }

  friend bool
  operator!=(const Self &x, const Self &y) { return x.node != y.node; }

  Base_ptr node;
  Base_ptr end;
};

template<typename Key, typename Val, typename KeyOfValue, typename Compare>
class Rb_tree {
 protected:
  typedef Rb_tree_node_base *Base_ptr;
  typedef const Rb_tree_node_base *Const_base_ptr;
  typedef Rb_tree_node<Val> *Link_type;
  typedef const Rb_tree_node<Val> *Const_Link_type;

 public:
  typedef Key key_type;
  typedef Val value_type;
  typedef Val *pointer;
  typedef const Val *const_pointer;
  typedef Val &reference;
  typedef const Val &const_reference;
  typedef size_t size_type;
  typedef std::ptrdiff_t difference_type;

 protected:
  Rb_tree_header *impl;
  Compare key_compare;

  Base_ptr
  _root() { return impl->header.parent; }

  Const_base_ptr
  _root() const { return impl->header.parent; }

  Base_ptr
  _leftmost() { return impl->header.left; }

  Const_base_ptr
  _leftmost() const { return impl->header.left; }

  Base_ptr
  _rightmost() { return impl->header.right; }

  Const_base_ptr
  _rightmost() const { return impl->header.right; }

  Link_type
  _begin() { return static_cast<Link_type>(impl->header.parent); }

  Const_Link_type
  _begin() const { return static_cast<Const_Link_type>(impl->header.parent); }

  Base_ptr
  _end() { return &impl->header; }

  Const_base_ptr
  _end() const { return &impl->header; }

  static const_reference
  _s_value(Const_Link_type x) { return *x->valptr(); }

  static const Key &
  _s_key(Const_Link_type x) { return KeyOfValue()(*x->valptr()); }

  static Link_type
  _s_left(Base_ptr x) { return static_cast<Link_type>(x->left); }

  static Const_Link_type
  _s_left(Const_base_ptr x) { return static_cast<Const_Link_type>(x->left); }

  static Link_type
  _s_right(Base_ptr x) { return static_cast<Link_type>(x->right); }

  static Const_Link_type
  _s_right(Const_base_ptr x) { return static_cast<Const_Link_type>(x->right); }

  static const_reference
  _s_value(Const_base_ptr x) { return *static_cast<Const_Link_type>(x)->valptr(); }

  static const Key &
  _s_key(Const_base_ptr x) { return _s_key(static_cast<Const_Link_type>(x)); }

  Base_ptr
  _s_minimum(Base_ptr x) { return Rb_tree_node_base::_s_minimum(x, _end()); }

  Const_base_ptr
  _s_minimum(Const_base_ptr x) { return Rb_tree_node_base::_s_minimum(x, _end()); }

  Base_ptr
  _s_maximum(Base_ptr x) { return Rb_tree_node_base::_s_maximum(x, _end()); }

  Const_base_ptr
  _s_maximum(Const_base_ptr x) { return Rb_tree_node_base::_s_maximum(x, _end()); }

 public:

  typedef Rb_tree_iterator<value_type> iterator;
  typedef Rb_tree_const_iterator<value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 protected:
  void
  _leftRotate(Base_ptr x) {
	Base_ptr y = x->right;
	x->right = y->left;
	if (y->left != _end())
	  y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == _end())
	  impl->header.parent = y;
	else if (x == x->parent->left)
	  x->parent->left = y;
	else
	  x->parent->right = y;
	y->left = x;
	x->parent = y;
  }

  void
  _rightRotate(Base_ptr x) {
	Base_ptr y = x->left;
	x->left = y->right;
	if (y->right != _end())
	  y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == _end())
	  impl->header.parent = y;
	else if (x == x->parent->right)
	  x->parent->right = y;
	else
	  x->parent->left = y;
	y->right = x;
	x->parent = y;
  }

  void
  _insertFixUp(Base_ptr z) {
	while (z->parent->color == red) {
	  if (z->parent == z->parent->parent->left) {
		Base_ptr y = z->parent->parent->right;
		if (y->color == red) {
		  z->parent->color = black;
		  y->color = black;
		  z->parent->parent->color = red;
		  z = z->parent->parent;
		} else {
		  if (z == z->parent->right) {
			z = z->parent;
			_leftRotate(z);
		  }
		  z->parent->color = black;
		  z->parent->parent->color = red;
		  _rightRotate(z->parent->parent);
		}
	  } else {
		Base_ptr y = z->parent->parent->left;
		if (y->color == red) {
		  z->parent->color = black;
		  y->color = black;
		  z->parent->parent->color = red;
		  z = z->parent->parent;
		} else {
		  if (z == z->parent->left) {
			z = z->parent;
			_rightRotate(z);
		  }
		  z->parent->color = black;
		  z->parent->parent->color = red;
		  _leftRotate(z->parent->parent);
		}
	  }
	}
	_root()->color = black;
  }

  std::pair<iterator, bool>
  _insert_unique(Base_ptr n) {
	Base_ptr y = _end();
	Base_ptr temp = _root();
	while (temp != _end()) {
	  y = temp;
	  if (key_compare(_s_key(n), _s_key(temp)))
		temp = temp->left;
	  else if (key_compare(_s_key(temp), _s_key(n)))
		temp = temp->right;
	  else {
		return (std::pair<iterator, bool>(iterator(temp, _end()), false));
	  }
	}
	n->parent = y;
	if (y == _end())
	  impl->header.parent = n;
	else if (key_compare(_s_key(n), _s_key(y)))
	  y->left = n;
	else
	  y->right = n;
	n->left = _end();
	n->right = _end();
	impl->node_count++;
	_insertFixUp(n);
	return (std::pair<iterator, bool>(iterator(n, _end()), true));
  }

  void
  _insert_equal(Base_ptr n) {
	Base_ptr y = _end();
	Base_ptr temp = _root();
	while (temp != _end()) {
	  y = temp;
	  if (key_compare(_s_key(n), _s_key(temp)))
		temp = temp->left;
	  else
		temp = temp->right;
	}
	n->parent = y;
	if (y == _end())
	  impl->header.parent = n;
	else if (key_compare(_s_key(n), _s_key(y)))
	  y->left = n;
	else
	  y->right = n;
	n->left = _end();
	n->right = _end();
	impl->node_count++;
	_insertFixUp(n);
  }

  void
  _transplant(Base_ptr u, Base_ptr v) {
	if (u->parent == _end())
	  impl->header.parent = v;
	else if (u == u->parent->left)
	  u->parent->left = v;
	else
	  u->parent->right = v;
	if (v->parent != impl->header.parent)
	  v->parent = u->parent;
  }

  void
  _deleteFixUp(Base_ptr x) {
	while (x != impl->header.parent && x->color == black) {
	  if (x == x->parent->left) {
		Base_ptr w = x->parent->right;
		if (w->color == red) {
		  w->color = black;
		  x->parent->color = red;
		  _leftRotate(x->parent);
		  w = x->parent->right;
		}
		if (w->left->color == black && w->right->color == black) {
		  w->color = red;
		  x = x->parent;
		} else {
		  if (w->right->color == black) {
			w->left->color = black;
			w->color = red;
			_rightRotate(w);
			w = x->parent->right;
		  }
		  w->color = x->parent->color;
		  x->parent->color = black;
		  w->right->color = black;
		  _leftRotate(x->parent);
		  x = impl->header.parent;
		}
	  } else {
		Base_ptr w = x->parent->left;
		if (w->color == red) {
		  w->color = black;
		  x->parent->color = red;
		  _rightRotate(x->parent);
		  w = x->parent->left;
		}
		if (w->left->color == black && w->right->color == black) {
		  w->color = red;
		  x = x->parent;
		} else {
		  if (w->left->color == black) {
			w->right->color = black;
			w->color = red;
			_leftRotate(w);
			w = x->parent->left;
		  }
		  w->color = x->parent->color;
		  x->parent->color = black;
		  w->left->color = black;
		  _rightRotate(x->parent);
		  x = impl->header.parent;
		}
	  }
	}
	x->color = black;
  }

  void
  _delete(Base_ptr z) {
	Base_ptr y = z;
	Base_ptr x;
	Rb_tree_color y_original_color = y->color;
	if (z->left == _end()) {
	  x = z->right;
	  _transplant(z, z->right);
	} else if (z->right == _end()) {
	  x = z->left;
	  _transplant(z, z->left);
	} else {
	  y = _s_minimum(z->right);
	  x = y->right;
	  y_original_color = y->color;
	  if (y->parent == z) {
		if (x->parent != impl->header.parent)
		  x->parent = y;
	  } else {
		_transplant(y, y->right);
		y->right = z->right;
		y->right->parent = y;
	  }
	  if (x == _end())
		x = y;
	  _transplant(z, y);
	  y->left = z->left;
	  y->left->parent = y;
	  y->color = z->color;
	}
	if (y_original_color == black)
	  _deleteFixUp(x);
  }

  iterator
  _lower_bound(Link_type x, Base_ptr y, const Key &k) {
	while (x != _end()) {
	  if (!key_compare(_s_key(x), k)) {
		y = x;
		x = _s_left(x);
	  } else {
		x = _s_right(x);
	  }
	}
	return iterator(y, _end());
  }

  const_iterator
  _lower_bound(Const_Link_type x, Const_base_ptr y, const Key &k) const {
	while (x != _end()) {
	  if (!key_compare(_s_key(x), k)) {
		y = x;
		x = _s_left(x);
	  } else {
		x = _s_right(x);
	  }
	}
	return const_iterator(y, _end());
  }

  iterator
  _upper_bound(Link_type x, Base_ptr y, const Key &k) {
	while (x != _end()) {
	  if (key_compare(k, _s_key(x))) {
		y = x;
		x = _s_left(x);
	  } else {
		x = _s_right(x);
	  }
	}
	return iterator(y, _end());
  }

  const_iterator
  _upper_bound(Const_Link_type x, Const_base_ptr y, const Key &k) const {
	while (x != _end()) {
	  if (key_compare(k, _s_key(x))) {
		y = x;
		x = _s_left(x);
	  } else {
		x = _s_right(x);
	  }
	}
	return const_iterator(y, _end());
  }

 public:
  // allocation/deallocation
  Rb_tree() : impl(new Rb_tree_header) {}

  Rb_tree(const Compare &comp) : impl(new Rb_tree_header), key_compare(comp) {}

  Rb_tree(const Rb_tree &x) : impl(new Rb_tree_header) {
	const_iterator begin = x.begin();
	const_iterator end = x.end();
	while (begin != end) {
	  insert_equal(*begin);
	  begin++;
	}
  }

  void
  deleteAllTree(Link_type x) {
	if (x != _end()) {
	  deleteAllTree(_s_left(x));
	  deleteAllTree(_s_right(x));
	  delete x;
	}
  }

  ~Rb_tree() {
	deleteAllTree(_begin());
	delete impl;
  }

  Rb_tree &
  operator=(const Rb_tree &x) {
	if (this == &x)
	  return *this;
	clear();
	const_iterator begin = x.begin();
	const_iterator end = x.end();
	while (begin != end) {
	  insert_equal(*begin);
	  begin++;
	}
	return *this;
  }

  // Accessors.
  Compare
  key_comp() const { return key_compare; }

  iterator
  begin() { return iterator(impl->header.left, _end()); }

  const_iterator
  begin() const { return const_iterator(impl->header.left, _end()); }

  iterator
  end() { return iterator(_end(), _end()); }

  const_iterator
  end() const { return const_iterator(_end(), _end()); }

  reverse_iterator
  rbegin() { return reverse_iterator(end()); }

  const_reverse_iterator
  rbegin() const { return const_reverse_iterator(end()); }

  reverse_iterator
  rend() { return reverse_iterator(begin()); }

  const_reverse_iterator
  rend() const { return const_reverse_iterator(begin()); }

  bool
  empty() const { return impl->node_count == 0; }

  size_type
  size() const { return impl->node_count; }

  size_type
  max_size() const _GLIBCXX_NOEXCEPT
  { return (std::numeric_limits<size_type>::max() / sizeof(Rb_tree_node<Val>)) - 2; }

  void
  swap(Rb_tree &t) {
	std::swap(impl, t.impl);
	std::swap(key_compare, t.key_compare);
  }

  // Insert/erase.
  std::pair<iterator, bool>
  insert_unique(const_reference value) {
	Link_type node = new Rb_tree_node<Val>(value);
	node->parent = _end();
	node->left = _end();
	node->right = _end();
	node->color = red;
	std::pair<iterator, bool> ret = _insert_unique(node);
	if (ret.second == false) {
	  delete node;
	  return ret;
	} else {
	  if (impl->header.left == _end() ||
		  key_compare(_s_key(node), _s_key(impl->header.left))) {
		impl->header.left = node;
	  }
	  if (impl->header.right == _end() ||
		  key_compare(_s_key(impl->header.right), _s_key(node))) {
		impl->header.right = node;
	  }
	  return (std::pair<iterator, bool>(iterator(node, _end()), true));
	}
  }

  iterator
  insert_equal(const value_type &x) {
	Link_type node = new Rb_tree_node<Val>(x);
	node->parent = _end();
	node->left = _end();
	node->right = _end();
	node->color = red;
	_insert_equal(node);
	if (impl->header.left == _end() ||
		key_compare(_s_key(node), _s_key(impl->header.left))) {
	  impl->header.left = node;
	}
	if (impl->header.right == _end() ||
		key_compare(_s_key(impl->header.right), _s_key(node)) ||
		(!key_compare(_s_key(impl->header.right), _s_key(node)) &&
			!key_compare(_s_key(node), _s_key(impl->header.right)))) {
	  impl->header.right = node;
	}
	return iterator(node, _end());
  }

  iterator
  insert_unique(const_iterator, const_reference x) {
	return insert_unique(x).first;
  }

  iterator
  insert_equal(const_iterator, const_reference x) {
	return insert_equal(x);
  }

  template<typename InputIterator>
  void
  insert_range_unique(InputIterator first, InputIterator last) {
	for (; first != last; ++first) {
	  insert_unique(*first);
	}
  }

  template<typename InputIterator>
  void
  insert_range_equal(InputIterator first, InputIterator last) {
	for (; first != last; ++first) {
	  insert_equal(*first);
	}
  }

  void
  erase(iterator pos) {
	iterator tmp;
	if (_leftmost() == pos.node) {
	  tmp = pos;
	  ++tmp;
	  impl->header.left = tmp.node;
	}
	if (_rightmost() == pos.node) {
	  tmp = pos;
	  --tmp;
	  impl->header.right = tmp.node;
	}
	impl->node_count--;
	_delete(pos.node);
	delete static_cast<Link_type>(pos.node);
  }

  void
  erase(const_iterator pos) {
	erase(pos._const_cast());
  }

  size_type
  erase(const key_type &x) {
	std::pair<iterator, iterator> range = equal_range(x);
	size_type n = 0;
	iterator first = range.first;
	iterator last = range.second;
	while (first != last) {
	  iterator tmp = first++;
	  erase(tmp);
	  n++;
	}
	return n;
  }

  void
  erase(iterator first, iterator last) {
	while (first != last) {
	  iterator tmp = first++;
	  erase(tmp);
	}
  }

  void
  erase(const_iterator first, const_iterator last) {
	erase(first._const_cast(), last._const_cast());
  }

  void
  clear() {
	deleteAllTree(_begin());
	impl->header.parent = &impl->header;
	impl->header.right = &impl->header;
	impl->header.left = &impl->header;
	impl->node_count = 0;
  }

  // Set operations.
  iterator
  find(const key_type &k) {
	iterator j = lower_bound(k);
	if (j == end() || key_compare(k, _s_key(j.node))) {
	  return end();
	}
	return j;
  }

  const_iterator
  find(const key_type &k) const {
	const_iterator j = lower_bound(k);
	if (j == end() || key_compare(k, _s_key(j.node))) {
	  return end();
	}
	return j;
  }

  size_type
  count(const key_type &k) const {
	std::pair<const_iterator, const_iterator> p = equal_range(k);
	const_iterator first = p.first;
	const_iterator last = p.second;
	size_type n = 0;
	for (; first != last; ++first) {
	  n++;
	}
	return n;
  }

  iterator
  lower_bound(const key_type &k) {
	return _lower_bound(_begin(), _end(), k);
  }

  const_iterator
  lower_bound(const key_type &k) const {
	return _lower_bound(_begin(), _end(), k);
  }

  iterator
  upper_bound(const key_type &k) {
	return _upper_bound(_begin(), _end(), k);
  }

  const_iterator
  upper_bound(const key_type &k) const {
	return _upper_bound(_begin(), _end(), k);
  }

  std::pair<iterator, iterator>
  equal_range(const key_type &k) {
	Link_type x = _begin();
	Base_ptr y = _end();
	while (x != _end()) {
	  if (key_compare(_s_key(x), k)) {
		x = _s_right(x);
	  } else if (key_compare(k, _s_key(x))) {
		y = x;
		x = _s_left(x);
	  } else {
		Link_type xu = x;
		Base_ptr yu = y;
		y = x;
		x = _s_left(x);
		xu = _s_right(xu);
		return std::pair<iterator, iterator>(_lower_bound(x, y, k), _upper_bound(xu,
																				 yu,
																				 k));
	  }
	}
	return std::pair<iterator, iterator>(iterator(y, _end()), iterator(y, _end()));
  }

  std::pair<const_iterator, const_iterator>
  equal_range(const key_type &k) const {
	Const_Link_type x = _begin();
	Const_base_ptr y = _end();
	while (x != _end()) {
	  if (key_compare(_s_key(x), k)) {
		x = _s_right(x);
	  } else if (key_compare(k, _s_key(x))) {
		y = x;
		x = _s_left(x);
	  } else {
		Const_Link_type xu = x;
		Const_base_ptr yu = y;
		y = x;
		x = _s_left(x);
		xu = _s_right(xu);
		return std::pair<const_iterator, const_iterator>(_lower_bound(x, y, k),
														 _upper_bound(xu, yu, k));
	  }
	}
	return std::pair<const_iterator, const_iterator>(const_iterator(y, _end()),
													 const_iterator(y, _end()));
  }

  friend bool
  operator==(const Rb_tree &x, const Rb_tree &y) {
	return x.size() == y.size()
		&& std::equal(x.begin(), x.end(), y.begin());
  }

  friend bool
  operator<(const Rb_tree &x, const Rb_tree &y) {
	return std::lexicographical_compare(x.begin(), x.end(),
										y.begin(), y.end());
  }

  friend bool
  operator!=(const Rb_tree &x, const Rb_tree &y) { return !(x == y); }

  friend bool
  operator>(const Rb_tree &x, const Rb_tree &y) { return y < x; }

  friend bool
  operator<=(const Rb_tree &x, const Rb_tree &y) { return !(y < x); }

  friend bool
  operator>=(const Rb_tree &x, const Rb_tree &y) { return !(x < y); }
};

}
#endif
