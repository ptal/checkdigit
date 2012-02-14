//  Boost checks/filter.hpp header file
//  (C) Copyright Pierre Talbot 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief Provides a type "checkdigit"
*/

#ifndef BOOST_CHECK_FILTER_HPP
#define BOOST_CHECK_FILTER_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef> // std::size_t
#include <cctype>
#include <functional>

namespace boost{
  namespace checks{

template <typename value_type>
struct digit_filter : public std::unary_function<value_type, bool>
{
  bool operator()(const value_type &value)
  {
    return std::isdigit(static_cast<int>(value));
  }
};

template <typename value_type>
struct digitx_filter : public std::unary_function<value_type, bool>
{
  bool operator()(const value_type &value) 
  {
    return std::isdigit(static_cast<int>(value)) || std::tolower(static_cast<int>(value)) == 'x';
  }
};

}} // namespace boost   namespace checks

#endif //BOOST_CHECK_CHECKDIGIT_HPP