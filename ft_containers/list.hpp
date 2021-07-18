#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <cstddef>
#include <limits>

namespace ft {

struct list_node_base_ {
  list_node_base_ *next_;
  list_node_base_ *prev_;
};

template<typename T>
struct list_node_ : public list_node_base_ {
  T data_;
  T *valptr() { return __builtin_addressof(data_); }
  T const *valptr() const { return __builtin_addressof(data_); }

};

template<typename T>
struct list_iterator_ {
  typedef list_iterator_<T> self_;
  typedef list_node_<T> node_;

  typedef ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;

  list_iterator_()
	  : node() {}

  explicit
  list_iterator_(list_node_base_ *x)
	  : node(x) {}

  self_
  const_cast_() const { return *this; }

  reference
  operator*() const { return *static_cast<node_ *>(node)->valptr(); }

  pointer
  operator->() const { return static_cast<node_ *>(node)->valptr(); }

  self_ &
  operator++() {
	node = node->next_;
	return (*this);
  }

  self_
  operator++(int) {
	self_ tmp = *this;
	node = node->next_;
	return tmp;
  }

  self_ &
  operator--() {
	node = node->prev_;
	return (*this);
  }

  self_
  operator--(int) {
	self_ tmp = *this;
	node = node->prev_;
	return tmp;
  }

  friend bool
  operator==(const self_ &x, const self_ &y) { return x.node == y.node; }

  friend bool
  operator!=(const self_ &x, const self_ &y) { return x.node != y.node; }

  list_node_base_ *node;
};

template<typename T>
struct list_const_iterator_ {
  typedef list_const_iterator_<T> self_;
  typedef const list_node_<T> node_;
  typedef list_iterator_<T> iterator;

  typedef ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef const T *pointer;
  typedef const T &reference;

  list_const_iterator_()
	  : node() {}

  explicit list_const_iterator_(const list_node_base_ *x)
	  : node(x) {}

  list_const_iterator_(const iterator &x)
	  : node(x.node) {}

  iterator
  const_cast_() const { return iterator(const_cast<list_node_base_ *>(node)); }

  reference
  operator*() const { return *static_cast<node_ *>(node)->valptr(); }

  pointer
  operator->() const { return static_cast<node_ *>(node)->valptr(); }

  self_ &
  operator++() {
	node = node->next_;
	return (*this);
  }

  self_
  operator++(int) {
	self_ tmp = *this;
	node = node->next_;
	return tmp;
  }

  self_ &
  operator--() {
	node = node->prev_;
	return (*this);
  }

  self_
  operator--(int) {
	self_ tmp = *this;
	node = node->prev_;
	return tmp;
  }

  friend bool
  operator==(const self_ &x, const self_ &y) { return x.node == y.node; }

  friend bool
  operator!=(const self_ &x, const self_ &y) { return x.node != y.node; }

  const list_node_base_ *node;
};

template<typename T>
struct list_reverse_iterator_ {
  typedef list_reverse_iterator_<T> self_;
  typedef list_node_<T> node_;

  typedef ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;

  list_reverse_iterator_()
	  : node() {}

  explicit list_reverse_iterator_(list_node_base_ *x)
	  : node(x) {}

  self_ const_cast_() const { return (*this); }

  reference operator*() const { return *static_cast<node_ *>(node)->valptr(); }

  pointer operator->() const { return static_cast<node_ *>(node)->valptr(); }

  self_ &operator++() {
	node = node->prev_;
	return (*this);
  }

  self_ operator++(int) {
	self_ tmp = *this;
	node = node->prev_;
	return tmp;
  }

  self_ &operator--() {
	node = node->next_;
	return (*this);
  }

  self_ operator--(int) {
	self_ tmp = *this;
	node = node->next_;
	return tmp;
  }

  friend bool operator==(const self_ &x, const self_ &y) { return x.node == y.node; }

  friend bool operator!=(const self_ &x, const self_ &y) { return x.node != y.node; }

  list_node_base_ *node;
};

template<typename T>
struct list_const_reverse_iterator_ {
  typedef list_const_reverse_iterator_<T> self_;
  typedef const list_node_<T> node_;
  typedef list_reverse_iterator_<T> iterator;

  typedef ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef const T *pointer;
  typedef const T &reference;

  list_const_reverse_iterator_()
	  : node() {}

  explicit list_const_reverse_iterator_(const list_node_base_ *x)
	  : node(x) {}

  list_const_reverse_iterator_(const iterator &x)
	  : node(x.node) {}

  iterator const_cast_() const { return iterator(const_cast<list_node_base_ *>(node)); }

  reference operator*() const { return *static_cast<node_ *>(node)->valptr(); }

  pointer operator->() const { return static_cast<node_ *>(node)->valptr(); }

  self_ &operator++() {
	node = node->prev_;
	return (*this);
  }

  self_ operator++(int) {
	self_ tmp = *this;
	node = node->prev_;
	return tmp;
  }

  self_ &operator--() {
	node = node->next_;
	return (*this);
  }

  self_ operator--(int) {
	self_ tmp = *this;
	node = node->next_;
	return tmp;
  }

  friend bool operator==(const self_ &x, const self_ &y) { return x.node == y.node; }

  friend bool operator!=(const self_ &x, const self_ &y) { return x.node != y.node; }

  const list_node_base_ *node;
};

template<typename T>
class list {
 public:
  typedef T value_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef list_iterator_<T> iterator;
  typedef list_const_iterator_<T> const_iterator;
  typedef list_reverse_iterator_<T> reverse_iterator;
  typedef list_const_reverse_iterator_<T> const_reverse_iterator;
  typedef size_t size_type;
  typedef std::ptrdiff_t difference_type;

 protected:
  void
  _init() {
	head_ = new list_node_<T>;
	head_->next_ = head_;
	head_->prev_ = head_;
	current_ = head_;
  }

  void
  _insert(iterator position, const value_type &val) {
	list_node_<T> *new_elem = new list_node_<T>;
	new_elem->data_ = val;
	new_elem->prev_ = position.node->prev_;
	new_elem->next_ = position.node;
	if (position.node->prev_)
	  position.node->prev_->next_ = new_elem;
	position.node->prev_ = new_elem;
	if (position.node == head_)
	  head_ = new_elem;
  }

  void
  _erase(iterator position) {
	if (position.node == head_) {
	  list_node_<T> *tmp = head_;
	  head_ = static_cast<list_node_<T> *>(head_->next_);
	  current_->prev_ = head_;
	  head_->prev_ = current_;
	  delete tmp;
	} else {
	  list_node_<T> *tmp = static_cast<list_node_<T> *>(position.node);
	  tmp->prev_->next_ = tmp->next_;
	  tmp->next_->prev_ = tmp->prev_;
	  if (current_->prev_ == current_)
		head_ = current_;
	  delete tmp;
	}
  }

  template<typename Integer_, typename Value_>
  void
  _initialize_dispatch(Integer_ n, Value_ val, std::__true_type) {
	for (; n; --n)
	  push_back(val);
  }

  template<typename InputIterator>
  void
  _initialize_dispatch(InputIterator first, InputIterator last,
					   std::__false_type) {
	for (; first != last; ++first)
	  push_back(*first);
  }

  template<typename Integer_, typename Value_>
  void
  _insert_dispatch(iterator position, Integer_ n, Value_ val,
				   std::__true_type) {
	for (; n; --n)
	  _insert(position, val);
  }

  template<typename InputIterator>
  void
  _insert_dispatch(iterator position, InputIterator first, InputIterator
  last,
				   std::__false_type) {
	for (; first != last; ++first)
	  position = insert(position, *first);
  }

  list_node_<T> *
  _merge(list_node_<T> *first, list_node_<T> *second) {
	if (first == current_)
	  return (second);

	if (second == current_)
	  return (first);

	if (first->data_ < second->data_) {
	  first->next_ = _merge(static_cast<list_node_<T> *>
							(first->next_), second);
	  first->next_->prev_ = first;
	  first->prev_ = current_;
	  return (first);
	} else {
	  second->next_ = _merge(first,
							 static_cast<list_node_<T> *>(second->next_));
	  second->next_->prev_ = second;
	  second->prev_ = current_;
	  return (second);
	}
  }

  template<typename Compare>
  list_node_<T> *
  _merge(list_node_<T> *first, list_node_<T> *second, Compare comp) {
	if (first == current_)
	  return (second);

	if (second == current_)
	  return (first);

	if (!comp(second->data_, first->data_)) {
	  first->next_ = _merge(static_cast<list_node_<T> *>
							(first->next_), second);
	  first->next_->prev_ = first;
	  first->prev_ = current_;
	  return (first);
	} else {
	  second->next_ = _merge(first,
							 static_cast<list_node_<T> *>(second->next_));
	  second->next_->prev_ = second;
	  second->prev_ = current_;
	  return (second);
	}
  }

  list_node_<T> *
  _split(list_node_<T> *head) {
	list_node_<T> *fast = head;
	list_node_<T> *slow = head;
	while (fast->next_ != current_ && fast->next_->next_ != current_) {
	  fast = static_cast<list_node_<T> *>(fast->next_->next_);
	  slow = static_cast<list_node_<T> *>(slow->next_);
	}
	list_node_<T> *tmp = static_cast<list_node_<T> *>(slow->next_);
	slow->next_ = current_;
	return (tmp);
  }

  list_node_<T> *
  _mergeSort(list_node_<T> *head) {
	if (head == current_ || head->next_ == current_)
	  return head;
	list_node_<T> *second = _split(head);

	head = _mergeSort(head);
	second = _mergeSort(second);

	return (_merge(head, second));
  }

  template<typename Compare>
  list_node_<T> *
  _mergeSort(list_node_<T> *head, Compare comp) {
	if (head == current_ || head->next_ == current_)
	  return head;
	list_node_<T> *second = _split(head);

	head = _mergeSort(head, comp);
	second = _mergeSort(second, comp);

	return (_merge(head, second, comp));
  }

 public:
  /****************************************/
  /*                                      */
  /*           Constructors               */
  /*                                      */
  /****************************************/

  list() { _init(); }

  explicit
  list(size_type n, const value_type &val = value_type()) {
	_init();
	_initialize_dispatch(n, val, std::__true_type());
  }

  template<class InputIterator>
  list(InputIterator first, InputIterator last) {
	_init();
	typedef typename std::__is_integer<InputIterator>::__type Integral;
	_initialize_dispatch(first, last, Integral());
  }

  list(const list &x) {
	_init();
	_initialize_dispatch(x.begin(), x.end(), std::__false_type());
  }

  /****************************************/
  /*                                      */
  /*           Destructor                 */
  /*                                      */
  /****************************************/

  ~list() {
	clear();
	delete current_;
  }

  /****************************************/
  /*                                      */
  /*           Operator=                  */
  /*                                      */
  /****************************************/

  list &
  operator=(list const &list) {
	if (this == &list)
	  return (*this);

	clear();
	_initialize_dispatch(list.begin(), list.end(), std::__false_type());
	return (*this);
  }

  /****************************************/
  /*                                      */
  /*           Iterators                  */
  /*                                      */
  /****************************************/

  iterator
  begin() { return iterator(head_); }

  const_iterator
  begin() const { return const_iterator(head_); }

  iterator
  end() { return iterator(current_); }

  const_iterator
  end() const { return const_iterator(current_); }

  reverse_iterator
  rbegin() { return reverse_iterator(current_->prev_); }

  const_reverse_iterator
  rbegin() const { return const_reverse_iterator(current_->prev_); }

  reverse_iterator
  rend() { return reverse_iterator(head_->prev_); }

  const_reverse_iterator
  rend() const { return const_reverse_iterator(head_->prev_); }

  /****************************************/
  /*                                      */
  /*           Capacity                   */
  /*                                      */
  /****************************************/

  bool
  empty() const { return (head_ == current_); }

  size_type
  size() const {
	size_type count = 0;
	for (list::const_iterator first = begin(); first != end(); ++first)
	  ++count;
	return (count);
  }

  size_type
  max_size() const {
	typedef typename __gnu_cxx::__alloc_traits<std::allocator<T>
	>::template
	rebind<T>::other T_alloc_type;
	typedef __gnu_cxx::__alloc_traits<T_alloc_type> T_alloc_traits;
	typedef typename T_alloc_traits::template
	rebind<list_node_<T> >::other Node_alloc_type_;
	typedef __gnu_cxx::__alloc_traits<Node_alloc_type_>
		Node_alloc_traits_;
	return (Node_alloc_traits_::max_size(Node_alloc_type_()));
  }

  /****************************************/
  /*                                      */
  /*           Element access             */
  /*                                      */
  /****************************************/

  reference
  front() { return (head_->data_); }

  const_reference
  front() const { return (head_->data_); }

  reference
  back() { return ((static_cast<list_node_<T> *>(current_->prev_))->data_); }

  const_reference
  back() const { return ((static_cast<list_node_<T> *>(current_->prev_))->data_); }

  /****************************************/
  /*                                      */
  /*           Modifiers                  */
  /*                                      */
  /****************************************/

  template<typename InputIterator>
  void
  assign(InputIterator first, InputIterator last) {
	clear();
	typedef typename std::__is_integer<InputIterator>::__type Integral;
	_initialize_dispatch(first, last, Integral());
  }

  void
  assign(size_type n, const value_type &val) {
	clear();
	_initialize_dispatch(n, val, std::__true_type());
  }

  void
  push_front(value_type const &val) { _insert(begin(), val); }

  void
  pop_front() { _erase(begin()); }

  void
  push_back(const value_type &val) { _insert(end(), val); }

  void
  pop_back() { _erase(--end()); }

  iterator
  insert(iterator position, value_type const &val) {
	_insert(position, val);
	return (position);
  }

  void
  insert(iterator position,
		 size_type n,
		 value_type const &val) { _insert_dispatch(position, n, val, std::__true_type()); }

  template<typename InputIterator>
  void
  insert(iterator position, InputIterator first, InputIterator last) {
	typedef typename std::__is_integer<InputIterator>::__type Integral;
	_insert_dispatch(position, first, last, Integral());
  }

  iterator
  erase(iterator position) {
	iterator tmp = position++;
	_erase(tmp);
	return (position);
  }

  iterator
  erase(iterator first, iterator last) {
	iterator tmp;
	while (first != last) {
	  tmp = first++;
	  _erase(tmp);
	}
	return (first);
  }

  void
  swap(list &x) {
	list_node_<T> *tmp = head_;
	list_node_<T> *tmp2 = current_;

	head_ = x.head_;
	current_ = x.current_;
	x.head_ = tmp;
	x.current_ = tmp2;
  }

  void
  resize(size_type n, value_type val = value_type()) {
	list::iterator it = begin();
	if (n < size()) {
	  while (n--)
		++it;
	  while (it != end())
		it = erase(it);
	} else {
	  insert(end(), n - size(), val);
	}
  }

  void
  clear() {
	list_node_<T> *tmp;
	while (head_ != current_) {
	  tmp = static_cast<list_node_<T> *>(head_->next_);
	  delete head_;
	  head_ = tmp;
	}
	current_->prev_ = current_;
	current_->next_ = current_;
	head_ = current_;
  }

  /****************************************/
  /*                                      */
  /*           Operations                 */
  /*                                      */
  /****************************************/

  void
  splice(iterator position, list &x) {
	x.head_->prev_ = position.node->prev_;
	x.current_->prev_->next_ = position.node;
	if (position.node == head_)
	  head_ = x.head_;
	position.node->prev_->next_ = x.head_;
	position.node->prev_ = x.current_->prev_;

	x.head_ = x.current_;
	x.current_->next_ = x.current_;
	x.current_->prev_ = x.current_;
  }

  void
  splice(iterator position, list &x, iterator i) {
	i.node->prev_->next_ = i.node->next_;
	i.node->next_->prev_ = i.node->prev_;
	if (i.node == x.head_)
	  x.head_ = static_cast<list_node_<T> *>(i.node->next_);

	i.node->prev_ = position.node->prev_;
	i.node->next_ = position.node;
	if (position.node == head_)
	  head_ = static_cast<list_node_<T> *>(i.node);
	position.node->prev_->next_ = i.node;
	position.node->prev_ = i.node;
  }

  void
  splice(iterator position, list &x, iterator first, iterator last) {
	list_node_base_ *tmp = last.node->prev_;

	first.node->prev_->next_ = last.node;
	last.node->prev_ = first.node->prev_;
	if (first.node == x.head_)
	  x.head_ = static_cast<list_node_<T> *>(last.node);

	first.node->prev_ = position.node->prev_;
	tmp->next_ = position.node;
	if (position.node == head_)
	  head_ = static_cast<list_node_<T> *>(first.node);
	position.node->prev_->next_ = first.node;
	position.node->prev_ = tmp;
  }

  void
  remove(const value_type &val) {
	list::iterator it = begin();
	while (it != end()) {
	  list::iterator tmp = it++;
	  if (*tmp == val)
		_erase(tmp);
	}
  }

  template<typename Predicate>
  void
  remove_if(Predicate pred) {
	list::iterator it = begin();
	while (it != end()) {
	  list::iterator tmp = it++;
	  if (pred(*tmp))
		_erase(tmp);
	}
  }

  void
  unique() {
	list::iterator it = begin();
	list::iterator prev_value;
	bool first_elem = true;

	while (it != end()) {
	  list::iterator tmp = it++;
	  if (first_elem) {
		prev_value = tmp;
		first_elem = false;
		continue;
	  }
	  if (*tmp == *prev_value)
		_erase(tmp);
	  else
		prev_value = tmp;
	}
  }

  template<typename BinaryPredicate>
  void
  unique(BinaryPredicate binary_pred) {
	list::iterator it = begin();
	list::iterator prev_value;
	bool first_elem = true;

	while (it != end()) {
	  list::iterator tmp = it++;
	  if (first_elem) {
		prev_value = tmp;
		first_elem = false;
		continue;
	  }
	  if (binary_pred(*tmp, *prev_value))
		_erase(tmp);
	  else
		prev_value = tmp;
	}
  }

  void
  merge(list &x) {
	list::iterator it_this = begin();
	list::iterator it_x = x.begin();

	if (this == &x)
	  return;
	while (it_x != x.end()) {
	  while (it_this != end() && *it_x >= *it_this)
		++it_this;
	  splice(it_this, x, it_x++);
	}
  }

  template<typename Compare>
  void
  merge(list &x, Compare comp) {
	list::iterator it_this = begin();
	list::iterator it_x = x.begin();

	if (this == &x)
	  return;
	while (it_x != x.end()) {
	  while (!comp(*it_x, *it_this) && it_this != end())
		++it_this;
	  splice(it_this, x, it_x++);
	}
  }

  void
  sort() {
	head_ = _mergeSort(head_);
	current_->next_ = head_;
  }

  template<typename Compare>
  void
  sort(Compare comp) {
	head_ = _mergeSort(head_, comp);
	current_->next_ = head_;
  }

  void
  reverse() {
	while (head_->next_ != current_) {
	  list_node_<T> *tmp = static_cast<list_node_<T> *>(head_->next_);
	  head_->next_ = head_->prev_;
	  head_->prev_ = tmp;
	  head_ = tmp;
	}
	head_->next_ = head_->prev_;
	head_->prev_ = current_;
	current_->prev_ = current_->next_;
	current_->next_ = head_;
  }

 private:
  list_node_<T> *head_;
  list_node_<T> *current_;
};

template<typename T>
bool
operator==(const list<T> &lhs, const list<T> &rhs) {
  if (lhs.size() != rhs.size())
	return (false);
  typename list<T>::const_iterator left = lhs.begin();
  typename list<T>::const_iterator right = rhs.begin();
  while (left != lhs.end()) {
	if (*left == *right) {
	  ++left;
	  ++right;
	  continue;
	}
	return (false);
  }
  return (true);
}

template<typename T>
bool
operator!=(const list<T> &lhs, const list<T> &rhs) {
  if (lhs.size() != rhs.size())
	return (true);
  typename list<T>::const_iterator left = lhs.begin();
  typename list<T>::const_iterator right = rhs.begin();
  while (left != lhs.end()) {
	if (!(*left == *right))
	  return (true);
	++left;
	++right;
  }
  return (false);
}

template<typename T>
bool
operator<(const list<T> &lhs, const list<T> &rhs) {
  typename list<T>::const_iterator left = lhs.begin();
  typename list<T>::const_iterator right = rhs.begin();
  while (left != lhs.end() || right != rhs.end()) {
	if (!(*left < *right) && !(*right < *left)) {
	  ++left;
	  ++right;
	  continue;
	}
	if (*left < *right)
	  return (true);
	return (false);
  }
  if (left == lhs.end() && right == rhs.end())
	return (false);
  if (left == lhs.end())
	return (true);
  return (false);
}

template<typename T>
bool
operator<=(const list<T> &lhs, const list<T> &rhs) {
  typename list<T>::const_iterator left = lhs.begin();
  typename list<T>::const_iterator right = rhs.begin();
  while (left != lhs.end() || right != rhs.end()) {
	if (!(*left < *right) && !(*right < *left)) {
	  ++left;
	  ++right;
	  continue;
	}
	if (!(*right < *left))
	  return (true);
	return (false);
  }
  if (left == lhs.end() && right == rhs.end())
	return (true);
  if (left == lhs.end())
	return (true);
  return (false);
}

template<typename T>
bool
operator>(const list<T> &lhs, const list<T> &rhs) {
  typename list<T>::const_iterator left = lhs.begin();
  typename list<T>::const_iterator right = rhs.begin();
  while (left != lhs.end() || right != rhs.end()) {
	if (!(*left < *right) && !(*right < *left)) {
	  ++left;
	  ++right;
	  continue;
	}
	if (*right < *left)
	  return (true);
	return (false);
  }
  if (left == lhs.end() && right == rhs.end())
	return (false);
  if (right == rhs.end())
	return (true);
  return (false);
}

template<typename T>
bool
operator>=(const list<T> &lhs, const list<T> &rhs) {
  typename list<T>::const_iterator left = lhs.begin();
  typename list<T>::const_iterator right = rhs.begin();
  while (left != lhs.end() || right != rhs.end()) {
	if (!(*left < *right) && !(*right < *left)) {
	  ++left;
	  ++right;
	  continue;
	}
	if (!(*left < *right))
	  return (true);
	return (false);
  }
  if (left == lhs.end() && right == rhs.end())
	return (true);
  if (left == lhs.end())
	return (false);
  return (true);
}

template<typename T>
void
swap(list<T> &x, list<T> &y) { x.swap(y); }
}

#endif
