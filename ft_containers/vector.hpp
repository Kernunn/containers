#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <cstddef>
#include <sstream>
#include <limits>
#include "reverse_iterator.h"
#include "allocator.hpp"

namespace ft {

	template<typename T>
	struct vector_iterator_ {
		typedef vector_iterator_<T>				self_;
		typedef	ptrdiff_t						difference_type;
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef	T								value_type;
		typedef T*								pointer;
		typedef T&								reference;

		vector_iterator_()
		: ptr_() { }

		explicit
		vector_iterator_(pointer ptr)
		: ptr_(ptr) { }

		reference
		operator*() const
		{ return (*ptr_); }

		pointer
		operator->() const
		{ return (ptr_); }

		self_&
		operator++()
		{
			++ptr_;
			return (*this);
		}

		self_
		operator++(int)
		{
			self_ tmp = *this;
			++ptr_;
			return (tmp);
		}

		self_&
		operator--()
		{
			--ptr_;
			return (*this);
		}

		self_
		operator--(int)
		{
			self_ tmp = *this;
			--ptr_;
			return (tmp);
		}

		self_
		operator+(difference_type n) const
		{ return self_(ptr_ + n); }

		self_&
		operator+=(difference_type n)
		{
			ptr_ += n;
			return (*this);
		}

		self_
		operator-(difference_type n) const
		{ return self_(ptr_ - n); }

		self_&
		operator-=(difference_type n)
		{
			ptr_ -= n;
			return (*this);
		}

		reference
		operator[](difference_type n) const
		{ return (*(ptr_ + n)); }

		friend bool
		operator==(const self_& x, const self_& y)
		{ return (x.ptr_ == y.ptr_); }

		friend bool
		operator!=(const self_& x, const self_& y)
		{ return (x.ptr_ != y.ptr_); }

		friend bool
		operator<(const self_ &x, const self_ &y)
		{ return (x.ptr_ < y.ptr_); }

		friend bool
		operator>(const self_ &x, const self_ &y)
		{ return (y.ptr_ < x.ptr_); }

		friend bool
		operator<=(const self_ &x, const self_ &y)
		{ return (!(y.ptr_ < x.ptr_)); }

		friend bool
		operator>=(const self_ &x, const self_ &y)
		{ return (!(x.ptr_ < y.ptr_)); }

		friend self_
		operator+(difference_type n, const self_& x)
		{ return self_(x.ptr_ + n); }

		friend difference_type
		operator-(const self_& x, const self_& y)
		{ return (x.ptr_ - y.ptr_); }

		pointer	ptr_;
	};

	template<typename T>
	struct vector_const_iterator_ {
		typedef vector_const_iterator_<T>		self_;
		typedef	ptrdiff_t						difference_type;
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef	T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;

		vector_const_iterator_()
		: ptr_() { }

		explicit
		vector_const_iterator_(pointer ptr)
		: ptr_(ptr) { }

		vector_const_iterator_(const vector_iterator_<T> &it)
		: ptr_(it.ptr_) { }

		self_&
		operator=(const vector_iterator_<T> &it)
		{
			ptr_ = it.ptr_;
			return (*this);
		}

		reference
		operator*() const
		{ return (*ptr_); }

		pointer
		operator->() const
		{ return (ptr_); }

		self_&
		operator++()
		{
			++ptr_;
			return (*this);
		}

		self_
		operator++(int)
		{
			self_ tmp = *this;
			++ptr_;
			return (tmp);
		}

		self_&
		operator--()
		{
			--ptr_;
			return (*this);
		}

		self_
		operator--(int)
		{
			self_ tmp = *this;
			--ptr_;
			return (tmp);
		}

		self_
		operator+(difference_type n) const
		{ return self_(ptr_ + n); }

		self_&
		operator+=(difference_type n)
		{
			ptr_ += n;
			return (*this);
		}

		self_
		operator-(difference_type n) const
		{ return self_(ptr_ - n); }

		self_&
		operator-=(difference_type n)
		{
			ptr_ -= n;
			return (*this);
		}

		reference
		operator[](difference_type n) const
		{ return (*(ptr_ + n)); }

		friend bool
		operator==(const self_& x, const self_& y)
		{ return (x.ptr_ == y.ptr_); }

		friend bool
		operator!=(const self_& x, const self_& y)
		{ return (x.ptr_ != y.ptr_); }

		friend bool
		operator<(const self_ &x, const self_ &y)
		{ return (x.ptr_ < y.ptr_); }

		friend bool
		operator>(const self_ &x, const self_ &y)
		{ return (y.ptr_ < x.ptr_); }

		friend bool
		operator<=(const self_ &x, const self_ &y)
		{ return (!(y.ptr_ < x.ptr_)); }

		friend bool
		operator>=(const self_ &x, const self_ &y)
		{ return (!(x.ptr_ < y.ptr_)); }

		friend self_
		operator+(difference_type n, const self_& x)
		{ return self_(x.ptr_ + n); }

		friend difference_type
		operator-(const self_& x, const self_& y)
		{ return (x.ptr_ - y.ptr_); }

		pointer	ptr_;
	};

	template <typename T, typename Alloc = ft::Allocator<T> >
	class vector {
	public:
		typedef T										value_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef vector_iterator_<T>						iterator;
		typedef vector_const_iterator_<T>				const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef size_t									size_type;
		typedef ptrdiff_t								difference_type;
		typedef Alloc									allocator_type;

	protected:

		void
		_init()
		{ start_ = finish_ = end_of_storage_ = 0; }

		template<typename Integer_, typename Value_>
		void
		_initialize_dispatch(Integer_ n, Value_ val, std::__true_type)
		{
			for (; n; --n)
				push_back(val);
		}

		template<typename InputIterator>
		void
		_initialize_dispatch(InputIterator first, InputIterator last,
					   std::__false_type)
		{
			for (size_type i = 0; first != last; ++first, ++i)
				push_back(*first);
		}

		template<typename Integer_, typename Value_>
		void
		_insert_dispatch(iterator position, Integer_ n, Value_ val,
				   std::__true_type)
		{
			if (capacity() < size() + n) {
				size_type new_size = size() + n;
				if (new_size == 0)
					new_size = 1;
				pointer tmp = alloc.allocate(new_size);
				difference_type i = 0;
				iterator it = begin();
				for (; it != position; ++i, ++it)
					tmp[i] = *it;
				for (Integer_ j = 0; j < n; ++j)
					tmp[i++] = val;
				for (; it != end(); ++i, ++it)
					tmp[i] = *it;
				for (pointer begin = start_; begin != finish_; ++begin)
					alloc.destroy(begin);
				alloc.deallocate(start_, end_of_storage_ - start_);
				start_ = tmp;
				finish_ = start_ + i;
				end_of_storage_ = start_ + new_size;
			} else {
				reverse_iterator it = rbegin();
				finish_ += n;
				while (it.base().ptr_ != position.ptr_)
				{
					*(it - n) = *it;
					++it;
				}
				*(it - n) = *it;
				for (; n; --n)
					*position++ = val;
			}
		}

		template<typename InputIterator>
		void
		_insert_dispatch(iterator position, InputIterator first, InputIterator
		last,
							 std::__false_type)
		{
			for (; first != last; ++first)
			{
				position = insert(position, *first);
				++position;
			}
		}

	public:
		/****************************************/
		/*                                      */
		/*           Constructors               */
		/*                                      */
		/****************************************/

		explicit
		vector()
		{
			_init();
			alloc = allocator_type();
		}

		explicit
		vector(const allocator_type& alloc) : alloc(alloc)
		{ _init(); }

		explicit
		vector(size_type n, const value_type& val = value_type(), const
		allocator_type& alloc = allocator_type())
		: alloc(alloc)
		{
			_init();
			_initialize_dispatch(n, val, std::__true_type());
		}

		template<typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type&
		alloc = allocator_type())
		: alloc(alloc)
		{
			_init();
			typedef typename std::__is_integer<InputIterator>::__type Integral;
			_initialize_dispatch(first, last, Integral());
		}

		vector(const vector &x)
		{
			_init();
			alloc = allocator_type();
			_initialize_dispatch(x.begin(), x.end(), std::__false_type());
		}

		/****************************************/
		/*                                      */
		/*           Destructor                 */
		/*                                      */
		/****************************************/

		~vector()
		{
			for (pointer begin = start_; begin != finish_; ++begin)
				alloc.destroy(begin);
			alloc.deallocate(start_, end_of_storage_ - start_);
		}

		/****************************************/
		/*                                      */
		/*           Operator=                  */
		/*                                      */
		/****************************************/

		vector&
		operator=(vector v)
		{
			if (this == &v)
				return (*this);

			swap(v);
			return (*this);
		}

		/****************************************/
		/*                                      */
		/*           Iterators                  */
		/*                                      */
		/****************************************/


		iterator begin()
		{ return iterator(start_); }

		const_iterator begin() const
		{ return const_iterator(start_); }

		iterator end()
		{ return iterator(finish_); }

		const_iterator end() const
		{ return const_iterator(finish_); }

		reverse_iterator rbegin()
		{ return reverse_iterator(end()); }

		const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(end()); }

		reverse_iterator rend()
		{ return reverse_iterator(begin()); }

		const_reverse_iterator rend() const
		{ return const_reverse_iterator(begin()); }

		/****************************************/
		/*                                      */
		/*           Capacity                   */
		/*                                      */
		/****************************************/

		size_type
		size() const
		{ return (finish_ - start_); }

		void
		resize(size_type n, value_type val = value_type())
		{
			if (n < size())
			{
				for (iterator it = begin() + n; it != end(); ++it)
					alloc.destroy(it.ptr_);
				finish_ = start_ + n;
			}
			else
				_initialize_dispatch(n - size(), val, std::__true_type());
		}

		size_type
		capacity() const
		{ return (end_of_storage_ - start_); }

		bool
		empty() const
		{ return (start_ == finish_); }

		void
		reserve(size_type n)
		{
			if (n < capacity())
				return ;
			pointer tmp = alloc.allocate(n);
			difference_type i = 0;
			for (; i < finish_ - start_; ++i)
				alloc.construct(tmp + i, start_[i]);
			for (pointer begin = start_; begin != finish_; ++begin)
				alloc.destroy(begin);
			alloc.deallocate(start_, end_of_storage_ - start_);
			start_ = tmp;
			finish_ = start_ + i;
			end_of_storage_ = start_ + n;
		}

		size_type
		size_max() const
		{ return (std::numeric_limits<size_type>::max() / sizeof(T)); }

		/****************************************/
		/*                                      */
		/*           Element access             */
		/*                                      */
		/****************************************/

		reference
		operator[](size_type n)
		{ return (start_[n]); }

		const_reference
		operator[](size_type n) const
		{ return (start_[n]); }

		reference
		at(size_type n)
		{
			if (n >= size())
			{
				std::stringstream ss;
				ss << "vector::_range_check: n (which is " << n << ") >= ";
				ss << "this->size() (which is " << size() << ")";
				throw std::out_of_range(ss.str());
			}
			return (start_[n]);
		}

		const_reference
		at(size_type n) const
		{
			if (n >= size())
			{
				std::stringstream ss;
				ss << "vector::_range_check: n (which is " << n << ") >= ";
				ss << "this->size() (which is " << size() << ")";
				throw std::out_of_range(ss.str());
			}
			return (start_[n]);
		}

		reference
		front()
		{ return (*start_);	}

		const_reference
		front() const
		{ return (*start_);	}

		reference
		back()
		{ return (*(finish_ - 1)); }

		const_reference
		back() const
		{ return (*(finish_ - 1));	}

		/****************************************/
		/*                                      */
		/*           Modifiers                  */
		/*                                      */
		/****************************************/

		template<typename InputIterator>
		void
		assign(InputIterator first, InputIterator last)
		{
			clear();
			typedef typename std::__is_integer<InputIterator>::__type Integral;
			_initialize_dispatch(first, last, Integral());
		}

		void
		assign(size_type n, const value_type &val)
		{
			clear();
			_initialize_dispatch(n, val, std::__true_type());
		}

		void
		push_back(const value_type& val)
		{
			if (finish_ == end_of_storage_)
			{
				size_type new_size = (end_of_storage_ - start_) * 2;
				if (new_size == 0)
					new_size = 1;
				reserve(new_size);
			}
			alloc.construct(finish_, val);
			++finish_;
		}

		void
		pop_back()
		{
			alloc.destroy(finish_ - 1);
			finish_ -= 1;
		}

		iterator
		insert(iterator position, const value_type& val)
		{
			difference_type answer;
			if (finish_ == end_of_storage_) {
				size_type new_size = (end_of_storage_ - start_) * 2;
				if (new_size == 0)
					new_size = 1;
				pointer tmp = alloc.allocate(new_size);
				difference_type i = 0;
				iterator it = begin();
				for (; it != position; ++i, ++it)
					alloc.construct(tmp + i, *it);
				answer = i;
				alloc.construct(tmp + i++, val);
				for (; it != end(); ++i, ++it)
					alloc.construct(tmp + i, *it);
				for (pointer begin = start_; begin != finish_; ++begin)
					alloc.destroy(begin);
				alloc.deallocate(start_, end_of_storage_ - start_);
				start_ = tmp;
				finish_ = start_ + i;
				end_of_storage_ = start_ + new_size;
			} else {
				pointer end = finish_;
				pointer pos = position.ptr_;
				while (end != pos)
				{
					alloc.construct(end, *(end - 1));
					--end;
				}
				alloc.construct(pos, val);
				++finish_;
				return (position);
			}
			return (iterator(start_ + answer));
		}

		void
		insert(iterator position, size_type n, const value_type& val)
		{ _insert_dispatch(position, n, val, std::__true_type()); }

		template<typename InputIterator>
		void
		insert(iterator position, InputIterator first, InputIterator last)
		{
			typedef typename std::__is_integer<InputIterator>::__type Integral;
			_insert_dispatch(position, first, last, Integral());
		}

		iterator
		erase(iterator position)
		{
			iterator it = position + 1;
			alloc.destroy(position.ptr_);
			for (; it != end(); ++it)
				*(it - 1) = *it;
			--finish_;
			return (position);
		}

		iterator
		erase(iterator first, iterator last)
		{
			iterator it = last;
			for (; it != end(); ++it)
			{
				alloc.destroy((it - (last - first)).ptr_);
				*(it - (last - first)) = *it;
			}
			finish_ -= last - first;
			return (first);
		}

		void
		swap(vector& x)
		{
			pointer tmp = x.start_;
			x.start_ = start_;
			start_ = tmp;
			tmp = x.finish_;
			x.finish_ = finish_;
			finish_ = tmp;
			tmp = end_of_storage_;
			x.end_of_storage_ = end_of_storage_;
			end_of_storage_ = tmp;
		}

		void
		clear()
		{
			for (pointer begin = start_; begin != finish_; ++begin)
				alloc.destroy(begin);
			alloc.deallocate(start_, end_of_storage_ - start_);
			_init();
		}

	private:
		pointer	start_;
		pointer finish_;
		pointer end_of_storage_;
		allocator_type	alloc;
	};

	template <typename T>
	bool
	operator==(const vector<T>& lhs, const vector<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename vector<T>::const_iterator left = lhs.begin();
		typename vector<T>::const_iterator right = rhs.begin();
		while (left != lhs.end())
		{
			if (*left == *right)
			{
				++left;
				++right;
				continue;
			}
			return (false);
		}
		return (true);
	}

	template <typename T>
	bool
	operator!=(const vector<T>& lhs, const vector<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (true);
		typename vector<T>::const_iterator left = lhs.begin();
		typename vector<T>::const_iterator right = rhs.begin();
		while (left != lhs.end())
		{
			if (!(*left == *right))
				return (true);
			++left;
			++right;
		}
		return (false);
	}

	template <typename T>
	bool
	operator<(const vector<T>& lhs, const vector<T>& rhs)
	{
		typename vector<T>::const_iterator left = lhs.begin();
		typename vector<T>::const_iterator right = rhs.begin();
		while (left != lhs.end() || right != rhs.end())
		{
			if (!(*left < *right) && !(*right < *left))
			{
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

	template <typename T>
	bool
	operator<=(const vector<T>& lhs, const vector<T>& rhs)
	{
		typename vector<T>::const_iterator left = lhs.begin();
		typename vector<T>::const_iterator right = rhs.begin();
		while (left != lhs.end() || right != rhs.end())
		{
			if (!(*left < *right) && !(*right < *left))
			{
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

	template <typename T>
	bool
	operator>(const vector<T>& lhs, const vector<T>& rhs)
	{
		typename vector<T>::const_iterator left = lhs.begin();
		typename vector<T>::const_iterator right = rhs.begin();
		while (left != lhs.end() || right != rhs.end())
		{
			if (!(*left < *right) && !(*right < *left))
			{
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

	template <typename T>
	bool
	operator>=(const vector<T>& lhs, const vector<T>& rhs)
	{
		typename vector<T>::const_iterator left = lhs.begin();
		typename vector<T>::const_iterator right = rhs.begin();
		while (left != lhs.end() || right != rhs.end())
		{
			if (!(*left < *right) && !(*right < *left))
			{
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
	swap(vector<T> &x, vector<T> &y)
	{ x.swap(y); }
}

#endif
