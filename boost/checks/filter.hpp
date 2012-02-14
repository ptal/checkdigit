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

struct digit_filter
{
  typedef bool result_type;

  template <typename value_type>
  bool operator()(const value_type &value)
  {
    return value >= '0' && value <= '9';
  }
};

struct digitx_filter
{
  typedef bool result_type;

  template <typename value_type>
  bool operator()(const value_type &value) 
  {
    return (value >= '0' && value <= '9') || std::tolower(value) == 'x';
  }
};

}} // namespace boost   namespace checks

#endif //BOOST_CHECK_CHECKDIGIT_HPP
