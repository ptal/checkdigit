//  Boost checks/checkdigit.hpp header file
//  (C) Copyright Pierre Talbot 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief Provides a type "checkdigit"
*/

#ifndef BOOST_CHECK_CHECKDIGIT_HPP
#define BOOST_CHECK_CHECKDIGIT_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef> // std::size_t

namespace boost{
  namespace checks{

template <std::size_t checkdigit_pos,
          std::size_t checkdigit_size>
struct checkdigit
{
  static const std::size_t pos = checkdigit_pos;
  static const std::size_t size = checkdigit_size;
};

// A checkdigit at the end of the number for reverse traversal.
typedef checkdigit<0, 1> basic_checkdigit;


}} // namespace boost   namespace checks

#endif //BOOST_CHECK_CHECKDIGIT_HPP
