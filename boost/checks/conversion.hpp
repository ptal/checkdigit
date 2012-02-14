//  Boost checks/conversion.hpp header file
//  (C) Copyright Pierre Talbot 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief
*/

#ifndef BOOST_CHECK_CONVERSION_HPP
#define BOOST_CHECK_CONVERSION_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef> // std::size_t
#include <functional>


namespace boost{
  namespace checks{

struct chartodigit
{
  typedef std::size_t result_type;

  template <typename value_type>
  std::size_t operator()(const value_type &value) const 
  {
    return value - '0';
  }
};


struct chartodigitx
{
  typedef std::size_t result_type;

  template <typename value_type>
  std::size_t operator()(const value_type &value) const
  {
    return value <= '9' ? (value - '0') : 10;
  }
};

}} // namespace boost   namespace checks

#endif //BOOST_CHECK_CONVERSION_HPP
