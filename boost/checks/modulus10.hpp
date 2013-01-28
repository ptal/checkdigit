//  Boost checks/modulus10.hpp header file
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate classic modulus 10 checksum.
*/

#ifndef BOOST_CHECKS_MOD10_HPP
#define BOOST_CHECKS_MOD10_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef>

namespace boost{
  namespace checks{

struct mod10_inv_checkdigit
{
  char operator()(size_t checksum)
  {
    return ((10 - checksum % 10) % 10) + '0'; 
  }
};

struct mod10_checkdigit
{
  char operator()(size_t checksum)
  {
    return checksum % 10 + '0';
  }
};


}}  // namespace boost   namespace checks

#endif //BOOST_CHECKS_MOD10_HPP
