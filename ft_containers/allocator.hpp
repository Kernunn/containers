#ifndef FT_CONTAINERS_ALLOCATOR_HPP
#define FT_CONTAINERS_ALLOCATOR_HPP

#include <limits>

namespace ft {
template<typename T>
class StandardAllocPolicy {
 public:
  typedef T value_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

 public:
  template<typename U>
  struct rebind {
	typedef StandardAllocPolicy<U> other;
  };

 public:
  StandardAllocPolicy() {}
  ~StandardAllocPolicy() {}
  StandardAllocPolicy(StandardAllocPolicy const &) {}
  template<typename U>
  explicit StandardAllocPolicy(StandardAllocPolicy<U> const &) {}

  pointer allocate(size_type count, typename
  std::allocator<void>::const_pointer = 0) {
	return reinterpret_cast<pointer>(::operator new(count * sizeof(T)));
  }

  void deallocate(pointer p, size_type) { ::operator delete(p); }

  size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(T); }
};

template<typename T, typename T2>
inline bool operator==(StandardAllocPolicy<T> const &,
					   StandardAllocPolicy<T2> const &) { return true; }

template<typename T, typename OtherAllocator>
inline bool operator==(StandardAllocPolicy<T> const &,
					   OtherAllocator const &) { return false; }

template<typename T>
class ObjectTraits {
 public :
  template<typename U>
  struct rebind {
	typedef ObjectTraits<U> other;
  };

 public :
  ObjectTraits() {}
  ~ObjectTraits() {}
  template<typename U>
  explicit ObjectTraits(ObjectTraits<U> const &) {}

  T *address(T &r) { return &r; }

  T const *address(T const &r) { return &r; }

  void construct(T *p, const T &t) { new(p) T(t); }

  void destroy(T *p) { p->~T(); }
};

template<typename T, typename Policy = StandardAllocPolicy<T>, typename
Traits = ObjectTraits<T> >
class Allocator : public Policy, public Traits {
 private :
  typedef Policy AllocationPolicy;
  typedef Traits TTraits;

 public :
  typedef typename AllocationPolicy::size_type size_type;
  typedef typename AllocationPolicy::difference_type difference_type;
  typedef typename AllocationPolicy::pointer pointer;
  typedef typename AllocationPolicy::const_pointer const_pointer;
  typedef typename AllocationPolicy::reference reference;
  typedef typename AllocationPolicy::const_reference const_reference;
  typedef typename AllocationPolicy::value_type value_type;

 public :
  template<typename U>
  struct rebind {
	typedef Allocator<U, typename AllocationPolicy::template
	rebind<U>::other,
					  typename TTraits::template rebind<U>::other> other;
  };

 public :
  Allocator() {}
  ~Allocator() {}
  Allocator(Allocator const &rhs) : Policy(rhs), Traits(rhs) {}

  template<typename U>
  Allocator(Allocator<U> const &) {}

  template<typename U, typename P, typename T2>
  Allocator(Allocator<U, P, T2> const &rhs): Policy(rhs), Traits(rhs) {}
};

template<typename T, typename P, typename Tr>
inline bool operator==(Allocator<T, P,
								 Tr> const &lhs, Allocator<T,
														   P,
														   Tr> const &rhs) {
  return operator==(static_cast<P &>(lhs),
					static_cast<P &>(rhs));
}

template<typename T, typename P, typename Tr,
	typename T2, typename P2, typename Tr2>
inline bool operator==(Allocator<T, P,
								 Tr> const &lhs,
					   Allocator<T2,
								 P2,
								 Tr2> const &rhs) {
  return operator==(static_cast<P &>(lhs),
					static_cast<P2 &>(rhs));
}

template<typename T, typename P, typename Tr, typename OtherAllocator>
inline bool operator==(Allocator<T, P,
								 Tr> const &lhs,
					   OtherAllocator const &rhs) {
  return operator==(static_cast<P &>(lhs),
					rhs);
}

template<typename T, typename P, typename Tr>
inline bool operator!=(Allocator<T, P, Tr> const &lhs,
					   Allocator<T, P, Tr> const &rhs) { return !operator==(lhs, rhs); }

template<typename T, typename P, typename Tr,
	typename T2, typename P2, typename Tr2>
inline bool operator!=(Allocator<T, P, Tr> const &lhs,
					   Allocator<T2, P2, Tr2> const &rhs) { return !operator==(lhs, rhs); }

template<typename T, typename P, typename Tr,
	typename OtherAllocator>
inline bool operator!=(Allocator<T, P,
								 Tr> const &lhs,
					   OtherAllocator const &rhs) { return !operator==(lhs, rhs); }
}
#endif
