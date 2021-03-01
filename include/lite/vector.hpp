#pragma once
#include <cstddef> // std::size_t std::ptrdiff_t
#include <stdexcept> // std::out_of_range
#include <algorithm> // std::fill std::copy
#include <cassert> // std::assert

#ifndef LITE_NOEXCEPT
#  define LITE_NOEXCEPT
#endif // !LITE_NOEXCEPT

#ifndef LITE_CONSTEXPR
#  if defined(__cpp_constexpr)
#    define LITE_CONSTEXPR constexpr
#  else
#    define LITE_CONSTEXPR inline
#  endif // defined(__cpp_constexpr)
#endif // !LITE_CONSTEXPR

#ifndef LITE_NULLPTR
#  define LITE_NULLPTR NULL
#endif // !LITE_NULLPTR

#ifndef LITE_CONSTEXPR_DYNAMIC_ALLOC
#  if defined(__cpp_constexpr_dynamic_alloc)
#    define LITE_CONSTEXPR_DYNAMIC_ALLOC constexpr
#  else
#    define LITE_CONSTEXPR_DYNAMIC_ALLOC inline
#  endif // defined(__cpp_constexpr_dynamic_alloc)
#endif // !LITE_CONSTEXPR_DYNAMIC_ALLOC

namespace lite
{
    template<typename InputIt, typename Size, typename OutputIt>
    LITE_CONSTEXPR OutputIt copy_n(InputIt first, Size count, OutputIt result)
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

        LITE_CONSTEXPR vector() LITE_NOEXCEPT
            : m_data(LITE_NULLPTR)
            , m_size(0)
            , m_capacity(0)
        {
        }

        LITE_CONSTEXPR explicit vector(size_type count)
            : m_data(new T[count])
            , m_size(count)
            , m_capacity(count)
        {
        }

        LITE_CONSTEXPR vector(size_type count, const T& value)
            : m_data(new T[count])
            , m_size(count)
            , m_capacity(count)
        {
            std::fill_n(m_data, count, value);
        }

        LITE_CONSTEXPR_DYNAMIC_ALLOC ~vector()
        {
            clear();
        }

        // 元素訪問

        LITE_CONSTEXPR reference operator[](size_type pos)
        {
#if _DEBUG
            assert(pos < m_size);
#endif // _DEBUG
            return m_data[pos];
        }

        LITE_CONSTEXPR const_reference operator[](size_type pos) const
        {
#if _DEBUG
            assert(pos < m_size);
#endif // _DEBUG
            return m_data[pos];
        }

        LITE_CONSTEXPR reference at(size_type pos)
        {
            if (pos >= m_size)
            {
                throw std::out_of_range;
            }
            return m_data[pos];
        }

        LITE_CONSTEXPR const_reference at(size_type pos) const
        {
            if (pos >= m_size)
            {
                throw std::out_of_range;
            }
            return m_data[pos];
        }

        LITE_CONSTEXPR reference front()
        {
            return m_data[0];
        }

        LITE_CONSTEXPR const_reference front() const
        {
            return m_data[0];
        }

        LITE_CONSTEXPR reference back()
        {
            return m_data[m_size - 1];
        }

        LITE_CONSTEXPR const_reference back() const
        {
            return m_data[m_size - 1];
        }

        LITE_CONSTEXPR T* data() LITE_NOEXCEPT
        {
            return m_data;
        }

        LITE_CONSTEXPR const T* data() const LITE_NOEXCEPT
        {
            return m_data;
        }

        // 迭代器

        LITE_CONSTEXPR iterator begin() LITE_NOEXCEPT
        {
            return &front();
        }

        LITE_CONSTEXPR const_iterator begin() const LITE_NOEXCEPT
        {
            return &front();
        }

        LITE_CONSTEXPR const_iterator cbegin() const LITE_NOEXCEPT
        {
            return &front();
        }

        LITE_CONSTEXPR iterator end() LITE_NOEXCEPT
        {
            return &back() + 1;
        }

        LITE_CONSTEXPR const_iterator end() const LITE_NOEXCEPT
        {
            return &back() + 1;
        }

        LITE_CONSTEXPR const_iterator cend() const LITE_NOEXCEPT
        {
            return &back() + 1;
        }

        LITE_CONSTEXPR reverse_iterator rbegin() LITE_NOEXCEPT
        {
            return &back();
        }

        LITE_CONSTEXPR const_reverse_iterator rbegin() const LITE_NOEXCEPT
        {
            return &back();
        }

        LITE_CONSTEXPR const_reverse_iterator crbegin() const LITE_NOEXCEPT
        {
            return &back();
        }

        LITE_CONSTEXPR reverse_iterator rend() LITE_NOEXCEPT
        {
            return &front() - 1;
        }

        LITE_CONSTEXPR const_reverse_iterator rend() const LITE_NOEXCEPT
        {
            return &front() - 1;
        }

        LITE_CONSTEXPR const_reverse_iterator crend() const LITE_NOEXCEPT
        {
            return &front() - 1;
        }

        // 容量

        LITE_CONSTEXPR bool empty() const LITE_NOEXCEPT
        {
            return m_size == 0UL;
        }

        LITE_CONSTEXPR size_type size() const LITE_NOEXCEPT
        {
            return m_size;
        }

        LITE_CONSTEXPR void reserve(size_type new_cap)
        {
            if (new_cap <= m_capacity)
            {
                return;
            }
            _reserve(new_cap);
        }

        LITE_CONSTEXPR size_type capacity() const LITE_NOEXCEPT
        {
            return m_capacity;
        }

        LITE_CONSTEXPR void shrink_to_fit()
        {
            if (m_size == m_capacity)
            {
                return;
            }
            _reserve(m_size);
        }

        // 修改器

        LITE_CONSTEXPR void clear() LITE_NOEXCEPT
        {
            if (m_data != LITE_NULLPTR)
            {
                _clear();
                m_size = 0UL;
                m_capacity = 0UL;
            }
        }

        //LITE_CONSTEXPR iterator insert(const_iterator pos, const T& value)
        //{
        //    if (m_capacity == m_size)
        //    {
        //        _reserve(m_size * 2);
        //    }
        //}

        LITE_CONSTEXPR void push_back(const T& value)
        {
            if (empty())
            {
                _reserve(1);
            }
            else if (m_capacity == m_size)
            {
                _reserve(m_size * 2);
            }
            m_data[m_size] = value;
            m_size++;
        }

        LITE_CONSTEXPR void pop_back()
        {
#if _DEBUG
            assert(!empty());
#endif // _DEBUG
            m_size--;
        }

        LITE_CONSTEXPR void resize(size_type count)
        {
            if (m_size >= count)
            {
                m_size = count;
                return;
            }
            T* newData = new T[count];
            copy_n(m_data, m_size, newData);
            _clear();
            m_data = newData;
            m_size = count;
            m_capacity = count;
        }

        LITE_CONSTEXPR void resize(size_type count, const value_type& value)
        {
            if (m_size >= count)
            {
                m_size = count;
                return;
            }
            T* newData = new T[count];
            copy_n(m_data, m_size, newData);
            std::fill_n(newData + m_size, count - m_size, value);
            _clear();
            m_data = newData;
            m_size = count;
            m_capacity = count;
        }

    private:
        LITE_CONSTEXPR void _clear() LITE_NOEXCEPT
        {
            delete[] m_data;
            m_data = LITE_NULLPTR;
        }

        LITE_CONSTEXPR void _reserve(size_type new_cap)
        {
            T* newData = new T[new_cap];
            copy_n(m_data, m_size, newData);
            _clear();
            m_data = newData;
            m_capacity = new_cap;
        }

        LITE_CONSTEXPR void _resize(size_type count)
        {
            T* newData = new T[count];
            copy_n(m_data, m_size, newData);
            _clear();
            m_data = newData;
            m_size = count;
            m_capacity = count;
        }

        T* m_data;
        size_type m_size;
        size_type m_capacity;
    };
}
