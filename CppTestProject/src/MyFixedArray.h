#ifndef __MY_FIXEDARRAY__
#define __MY_FIXEDARRAY__

#include <iostream>
#include <iterator>
#include <algorithm>
#include <assert.h>

template<typename T>
class FixedArray
{
	public:
		class iterator;			// forward declaration
		class const_iterator;	// forward declaration

		FixedArray(size_t size)
			:m_Size(size)
		{
			m_pArray = new T[m_Size]{};
		}

		~FixedArray()
		{
			delete []m_pArray;
		}

		size_t size() { return m_Size; }

		// subscript operator
		T& operator[](size_t index)
		{
			if (index < m_Size)
			{
				return m_pArray[index];
			}
			else
			{
				assert(!"Out of bound.");
			}
		}

		// subscript operator const
		const T& operator[](size_t index) const
		{
			if (index < m_Size)
			{
				return m_pArray[index];
			}
			else
			{
				assert(!"Out of bound.");
			}
		}

		iterator begin()
		{
			return iterator(m_pArray);
		}

		iterator end()
		{
			return iterator(m_pArray + m_Size);
		}

		const_iterator begin() const
		{
			return const_iterator(m_pArray);
		}

		const_iterator end() const
		{
			return const_iterator(m_pArray + m_Size);
		}

		// Start - Iterator class 
		class iterator
		{
			public:
				using self_type = iterator;
				using value_type = T;
				using refernce = T&;
				using pointer= T*;

				using iterator_category = std::forward_iterator_tag;
				using difference_type = ptrdiff_t;

				iterator()
					:ptr_(NULL)
				{}

				iterator(pointer ptr)
					:ptr_(ptr)
				{}

				self_type operator++()			// pre-increment
				{
					ptr_++;
					return *this;
				}

				self_type operator++(int junk)	// post-increment
				{
					self_type temp = *this;
					ptr_++;
					return temp;
				}

				refernce operator*()
				{
					return *ptr_;
				}

				pointer operator->()
				{
					return ptr_;
				}

				bool operator==(const self_type &rhs)
				{
					return ptr_ == rhs.ptr_;
				}

				bool operator!=(const self_type &rhs)
				{
					return ptr_ != rhs.ptr_;
				}

			private:
				pointer ptr_;
		};

		class const_iterator
		{
			public:
				using self_type = const_iterator;
				using value_type = T;
				using refernce = T&;
				using pointer = T*;

				using iterator_category = std::forward_iterator_tag;
				using difference_type = ptrdiff_t;

				const_iterator(pointer ptr)
					:ptr_(ptr)
				{}

				self_type operator++()			// pre-increment
				{
					ptr_++;
					return *this;
				}

				self_type operator++(int junk)	// post-increment
				{
					self_type temp = *this;
					ptr_++;
					return temp;
				}
			
				const refernce operator*() const
				{
					return *ptr_;
				}

				const value_type* operator->() const
				{
					return ptr_;
				}

				bool operator==(const self_type &rhs)
				{
					return ptr_ == rhs.ptr_;
				}

				bool operator!=(const self_type &rhs)
				{
					return ptr_ != rhs.ptr_;
				}

				self_type operator=(const self_type &rhs)
				{
					ptr_ = rhs.ptr_;
					return *this;
				}

			private:
				pointer ptr_;
		};

	private:
		T				*m_pArray;
		size_t			m_Size;
};

#endif	//__MY_FIXEDARRAY__