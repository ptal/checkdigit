//  Boost checks/filter.hpp header file
//  (C) Copyright Pierre Talbot 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief Provides a type "checkdigit"
*/

#ifndef BOOST_CHECKDIGIT_FILTER_HPP
#define BOOST_CHECKDIGIT_FILTER_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef> // size_t
#include <cctype>
#include <functional>

namespace boost{
  namespace checkdigit{

struct digit_filter
{
  typedef bool result_type;

  template <typename value_type>
  bool operator()(value_type value) const
  {
    return std::isdigit(value);
  }
};

struct digitx_filter
{
  typedef bool result_type;

  template <typename value_type>
  bool operator()(value_type value) const
  {
    return digit_filter()(value) || std::tolower(value) == 'x';
  }
};

}} // namespace boost   namespace checkdigit

#endif //BOOST_CHECKDIGIT_CHECKDIGIT_HPP
