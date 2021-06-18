#pragma once
#ifndef CXX_VER
#  if __cplusplus >= 202002L
#    define CXX_VER 2020
#  elif __cplusplus >= 201703L
#    define CXX_VER 2017
#  elif __cplusplus >= 201103L
#    define CXX_VER 2011
#  else
#    define CXX_VER 1998
#  endif
#endif

#if CXX_VER < 2020
#  include <cstddef> // std::size_t std::ptrdiff_t
#  include <climits> // ULLONG_MAX
#  include <cassert> // std::assert

#  include <stdexcept> // std::out_of_range
#  include <algorithm> // std::fill std::copy
#  include <iterator> // iterator_traits
#  include <utility> // std::move
#endif

#ifndef HAS_TYPE_TRAITS
#  if (CXX_VER >= 2011) || defined(HAS_BOOST)
#    define HAS_TYPE_TRAITS 1
#  else
#    define HAS_TYPE_TRAITS 0
#  endif
#endif

#if CXX_VER >= 2011
#  include <type_traits>
#elif defined(HAS_BOOST)
#  include <boost/type_traits.hpp>
#endif

#if HAS_TYPE_TRAITS

#  ifndef ENABLE_IF
#    if CXX_VER >= 2011
#      define ENABLE_IF std::enable_if
#    elif defined(HAS_BOOST)
#      define ENABLE_IF boost::enable_if_
#    endif
#  endif

#  ifndef IS_CLASS
#    if CXX_VER >= 2011
#      define IS_CLASS std::is_class
#    elif defined(HAS_BOOST)
#      define IS_CLASS boost::is_class
#    endif
#  endif

#  ifndef ENABLE_IF_T
#    if CXX_VER >= 2017
#      define ENABLE_IF_T(x, y) std::enable_if_t<x, y>
#    else
#      define ENABLE_IF_T(x, y) typename ENABLE_IF<x, y>::type
#    endif
#  endif

#  ifndef IS_CLASS_V
#    if CXX_VER >= 2017
#      define IS_CLASS_V(x) std::is_class_v<x>
#    else
#      define IS_CLASS_V(x) IS_CLASS<x>::value
#    endif
#  endif

#endif

#ifndef ULLONG_MAX
#  define ULLONG_MAX 0xffffffffffffffffui64
#endif

#ifndef NOEXCEPT
#  define NOEXCEPT
#endif

#ifndef CONSTEXPR
#  if defined(__cpp_constexpr)
#    define CONSTEXPR constexpr
#  else
#    define CONSTEXPR inline
#  endif
#endif

#ifndef NULLPTR
#  define NULLPTR NULL
#endif

#ifndef CONSTEXPR_DYNAMIC_ALLOC
#  if defined(__cpp_constexpr_dynamic_alloc)
#    define CONSTEXPR_DYNAMIC_ALLOC constexpr
#  else
#    define CONSTEXPR_DYNAMIC_ALLOC inline
#  endif
#endif
