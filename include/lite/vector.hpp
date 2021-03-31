#pragma once
#include <cstddef> // std::size_t std::ptrdiff_t
#include <stdexcept> // std::out_of_range
#include <algorithm> // std::fill std::copy
#include <cassert> // std::assert
#include <iterator> // iterator_traits
#include <utility> // std::move
#include <climits> //

#ifndef HAS_CXX_11
#  if __cplusplus >= 201103L
#    define HAS_CXX_11 1
#  else
#    define HAS_CXX_11 0
#  endif // __cplusplus >= 201103L
#endif // !HAS_CXX_11

#ifndef HAS_TYPE_TRAITS
#  if HAS_CXX_11 || defined(HAS_BOOST)
#    define HAS_TYPE_TRAITS 1
#  else
#    define HAS_TYPE_TRAITS 0
#  endif // HAS_CXX_11
#endif // !HAS_TYPE_TRAITS

#if !defined(ENABLE_IF) && !defined(IS_CLASS)
#  if HAS_CXX_11
#    include <type_traits>
#    define ENABLE_IF std::enable_if
#    define IS_CLASS std::is_class
#  elif defined(HAS_BOOST)
#    include <boost/type_traits.hpp>
#    define ENABLE_IF boost::enable_if_
#    define IS_CLASS boost::is_class
#  endif // HAS_CXX_11
#endif

#ifndef ULLONG_MAX
#  if _UI64_MAX
#    define ULLONG_MAX _UI64_MAX
#  endif // _UI64_MAX
#endif // !ULLONG_MAX

#ifndef NOEXCEPT
#  define NOEXCEPT
#endif // !NOEXCEPT

#ifndef CONSTEXPR
#  if defined(__cpp_constexpr)
#    define CONSTEXPR constexpr
#  else
#    define CONSTEXPR inline
#  endif // defined(__cpp_constexpr)
#endif // !CONSTEXPR

#ifndef NULLPTR
#  define NULLPTR NULL
#endif // !NULLPTR

#ifndef CONSTEXPR_DYNAMIC_ALLOC
#  if defined(__cpp_constexpr_dynamic_alloc)
#    define CONSTEXPR_DYNAMIC_ALLOC constexpr
#  else
#    define CONSTEXPR_DYNAMIC_ALLOC inline
#  endif // defined(__cpp_constexpr_dynamic_alloc)
#endif // !CONSTEXPR_DYNAMIC_ALLOC

namespace lite
{
    template<typename InputIt, typename Size, typename OutputIt>
    CONSTEXPR OutputIt copy_n(InputIt first, Size count, OutputIt result)
    {
        return std::copy(first, first + count, result);
    }

    template<typename T>
    class vector
    {
    public:
        typedef T value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type* iterator;
        typedef const value_type* const_iterator;
        typedef value_type* reverse_iterator;
        typedef const value_type* const_reverse_iterator;

        CONSTEXPR vector() NOEXCEPT // 1
            : m_data(NULLPTR)
            , m_size(0)
            , m_capacity(0)
        {
        }

        CONSTEXPR explicit vector(size_type count) // 4
            : m_data(_create(count))
            , m_size(count)
            , m_capacity(count)
        {
        }

        CONSTEXPR vector(size_type count, const T& value) // 3
            : m_data(_create(count))
            , m_size(count)
            , m_capacity(count)
        {
            std::fill_n(m_data, count, value);
        }

        CONSTEXPR_DYNAMIC_ALLOC ~vector()
        {
            clear();
        }

        // 元素訪問

        CONSTEXPR reference operator[](size_type pos)
        {
#if _DEBUG
            assert(pos < m_size);
#endif // _DEBUG
            return m_data[pos];
        }

        CONSTEXPR const_reference operator[](size_type pos) const
        {
#if _DEBUG
            assert(pos < m_size);
#endif // _DEBUG
            return m_data[pos];
        }

        CONSTEXPR reference at(size_type pos)
        {
            if (pos >= m_size)
            {
                throw std::out_of_range("out_of_range");
            }
            return m_data[pos];
        }

        CONSTEXPR const_reference at(size_type pos) const
        {
            if (pos >= m_size)
            {
                throw std::out_of_range("out_of_range");
            }
            return m_data[pos];
        }

        CONSTEXPR reference front()
        {
#if _DEBUG
            assert(!empty());
#endif // _DEBUG
            return m_data[0];
        }

        CONSTEXPR const_reference front() const
        {
#if _DEBUG
            assert(!empty());
#endif // _DEBUG
            return m_data[0];
        }

        CONSTEXPR reference back()
        {
#if _DEBUG
            assert(!empty());
#endif // _DEBUG
            return m_data[m_size - 1];
        }

        CONSTEXPR const_reference back() const
        {
#if _DEBUG
            assert(!empty());
#endif // _DEBUG
            return m_data[m_size - 1];
        }

        CONSTEXPR T* data() NOEXCEPT
        {
            return m_data;
        }

        CONSTEXPR const T* data() const NOEXCEPT
        {
            return m_data;
        }

        // 迭代器

        CONSTEXPR iterator begin() NOEXCEPT
        {
            return &front();
        }

        CONSTEXPR const_iterator begin() const NOEXCEPT
        {
            return &front();
        }

        CONSTEXPR const_iterator cbegin() const NOEXCEPT
        {
            return &front();
        }

        CONSTEXPR iterator end() NOEXCEPT
        {
            return &back() + 1;
        }

        CONSTEXPR const_iterator end() const NOEXCEPT
        {
            return &back() + 1;
        }

        CONSTEXPR const_iterator cend() const NOEXCEPT
        {
            return &back() + 1;
        }

        CONSTEXPR reverse_iterator rbegin() NOEXCEPT
        {
            return &back();
        }

        CONSTEXPR const_reverse_iterator rbegin() const NOEXCEPT
        {
            return &back();
        }

        CONSTEXPR const_reverse_iterator crbegin() const NOEXCEPT
        {
            return &back();
        }

        CONSTEXPR reverse_iterator rend() NOEXCEPT
        {
            return &front() - 1;
        }

        CONSTEXPR const_reverse_iterator rend() const NOEXCEPT
        {
            return &front() - 1;
        }

        CONSTEXPR const_reverse_iterator crend() const NOEXCEPT
        {
            return &front() - 1;
        }

        // 容量

        CONSTEXPR bool empty() const NOEXCEPT
        {
            return m_size == 0UL;
        }

        CONSTEXPR size_type size() const NOEXCEPT
        {
            return m_size;
        }

        CONSTEXPR size_type max_size() const NOEXCEPT
        {
            return UULONG_MAX;
        }

        CONSTEXPR void reserve(size_type new_cap)
        {
            if (new_cap <= m_capacity)
            {
                return;
            }
            _reserve(new_cap);
        }

        CONSTEXPR size_type capacity() const NOEXCEPT
        {
            return m_capacity;
        }

        CONSTEXPR void shrink_to_fit()
        {
            if (m_size == m_capacity)
            {
                return;
            }
            _reserve(m_size);
        }

        // 修改器

        CONSTEXPR void clear() NOEXCEPT
        {
            if (m_data != NULLPTR)
            {
                _clear();
                m_size = 0UL;
                m_capacity = 0UL;
            }
        }

        CONSTEXPR iterator insert(const_iterator pos, const T& value) // 1
        {
            return insert(pos, 1, value);
        }

        CONSTEXPR iterator insert(const_iterator pos, size_type count, const T& value) // 3
        {
            difference_type offset = pos - begin();
            for (size_type i = 0U; i < count; i++)
            {
                push_back(value);
            }
            std::rotate(begin() + offset, end() - count, end());
            return begin() + offset;
        }

        CONSTEXPR iterator erase(const_iterator pos) //1
        {
            return erase(pos, pos + 1);
        }

        CONSTEXPR iterator erase(const_iterator first, const_iterator last) //2
        {
#if _DEBUG
            assert(begin() <= first && first < end());
#endif // _DEBUG
            difference_type fst = first - begin();
            difference_type lst = last - begin();
            std::rotate(begin() + fst, begin() + lst, end());
            for (difference_type i = 0U; i < lst - fst; i++)
            {
                pop_back();
            }
            return begin() + fst;
        }

        CONSTEXPR void push_back(const T& value) // 1
        {
            _push_back();
            m_data[m_size] = value;
            m_size++;
        }

#if defined(__cpp_rvalue_references)
        CONSTEXPR void push_back(T&& value) // 2
        {
            _push_back();
            m_data[m_size] = std::move(value);
            m_size++;
        }
#endif // defined(__cpp_rvalue_references)

#if defined(__cpp_rvalue_references)
        template<typename... Args>
        CONSTEXPR reference emplace_back(Args&&... args)
        {
            push_back(T(std::forward<Args>(args)...));
            return back();
        }
#endif // defined(__cpp_rvalue_references)

        CONSTEXPR void pop_back()
        {
#if _DEBUG
            assert(!empty());
#endif // _DEBUG
            m_size--;
        }

        CONSTEXPR void resize(size_type count)
        {
            if (m_size >= count)
            {
                m_size = count;
                return;
            }

            _reserve(count);
            m_size = count;
        }

        CONSTEXPR void resize(size_type count, const value_type& value)
        {
            if (m_size >= count)
            {
                std::fill_n(m_data + m_size, count - m_size, value);
                m_size = count;
                return;
            }

            _reserve(count);
            std::fill_n(m_data + m_size, count - m_size, value);
            m_size = count;
        }

        CONSTEXPR void swap(vector& other) NOEXCEPT
        {
            vector<T> temp;
            temp._set(*this);
            _set(other);
            other._set(temp);
        }

    private:
#if HAS_TYPE_TRAITS
        template<typename U>
        typename ENABLE_IF<IS_CLASS<U>::value, U>::type* _create(size_type count)
        {
            return reinterpret_cast<U*>(new char[count * sizeof(U)]);
        }

        template<typename U>
        typename ENABLE_IF<!IS_CLASS<U>::value, U>::type* _create(size_type count)
        {
            return new U[count];
        }

        template<typename U>
        void _destory(U* data, typename ENABLE_IF<IS_CLASS<U>::value, U>::type* = 0)
        {
            for (size_t i = 0; i < m_size; i++)
            {
                (m_data + i)->~U();
            }
        }

        template<typename U>
        void _destory(U* data, typename ENABLE_IF<!IS_CLASS<U>::value, U>::type* = 0)
        {
            delete[] m_data;
        }
#else
        T* _create(size_type count)
        {
            return new T[count];
        }

        void _destory(T* data)
        {
            delete[] m_data;
        }
#endif // HAS_TYPE_TRAITS

        CONSTEXPR void _set(vector& other) NOEXCEPT
        {
            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_data = NULLPTR;
        }

        CONSTEXPR void _clear() NOEXCEPT
        {
            _destory(m_data);
            m_data = NULLPTR;
        }

        CONSTEXPR void _reserve(size_type new_cap)
        {
            T* newData = _create<T>(new_cap);
            copy_n(m_data, m_size, newData);
            _clear();
            m_data = newData;
            m_capacity = new_cap;
        }

        CONSTEXPR void _push_back()
        {
            if (empty())
            {
                _reserve(1);
            }
            else if (m_capacity == m_size)
            {
                _reserve(m_size * 2);
            }
        }

        T* m_data;
        size_type m_size;
        size_type m_capacity;
    };

    template<typename T>
    CONSTEXPR void swap(vector<T>& lhs, vector<T>& rhs) NOEXCEPT
    {
        lhs.swap(rhs);
    }
}
