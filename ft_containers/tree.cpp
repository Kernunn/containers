#include "tree.hpp"

namespace ft {
Rb_tree_node_base *
Rb_tree_increment(Rb_tree_node_base *x, Rb_tree_node_base *end) {
  if (x->right != end)
	return Rb_tree_node_base::_s_minimum(x->right, end);
  Rb_tree_node_base *y = x->parent;
  while (y != end && x == y->right) {
	x = y;
	y = y->parent;
  }
  return y;
}

const Rb_tree_node_base *
Rb_tree_increment(const Rb_tree_node_base *x, const Rb_tree_node_base *end) {
  if (x->right != end)
	return Rb_tree_node_base::_s_minimum(x->right, end);
  Rb_tree_node_base *y = x->parent;
  while (y != end && x == y->right) {
	x = y;
	y = y->parent;
  }
  return y;
}

Rb_tree_node_base *
Rb_tree_decrement(Rb_tree_node_base *x, Rb_tree_node_base *end) {
  if (x == end) {
	return end->right;
  }
  if (x->left != end)
	return Rb_tree_node_base::_s_maximum(x->left, end);
  Rb_tree_node_base *y = x->parent;
  while (y != end && x == y->left) {
	x = y;
	y = y->parent;
  }
  return y;
}

const Rb_tree_node_base *
Rb_tree_decrement(const Rb_tree_node_base *x, const Rb_tree_node_base *end) {
  if (x == end) {
	return end->right;
  }
  if (x->left != end)
	return Rb_tree_node_base::_s_maximum(x->left, end);
  Rb_tree_node_base *y = x->parent;
  while (y != end && x == y->left) {
	x = y;
	y = y->parent;
  }
  return y;
}
}