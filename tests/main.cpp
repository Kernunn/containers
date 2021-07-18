void test_list();
void test_vector();
void test_deque();
void test_queue();
void test_stack();
void test_map();
void test_tree();
void test_set();
void test_multimap();
void test_multiset();

int main() {
#ifdef LIST
  test_list();
#endif

#ifdef VECTOR
  test_vector();
#endif

#ifdef DEQUE
  test_deque();
#endif

#ifdef QUEUE
  test_queue();
#endif

#ifdef STACK
  test_stack();
#endif

#ifdef TREE
  test_tree();
#endif

#ifdef MAP
  test_map();
#endif

#ifdef SET
  test_set();
#endif

#ifdef MULTIMAP
  test_multimap();
#endif

#ifdef MULTISET
  test_multiset();
#endif
}
