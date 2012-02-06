//  Boost checks/lexical_filter.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief Provides functions specific for checking sequences.
std::ptr_fun to use all the cctype header functions.
*/

#ifndef BOOST_CHECKS_LEXICAL_FILTER_HPP
#define BOOST_CHECKS_LEXICAL_FILTER_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <functional>
#include <cctype>

namespace boost{
  namespace checks{


/* Check if character is decimal digit plus the special character 'X' (often occurs 
as check digit instead of 10).
*/
template <typename value_type>
bool isdigitx(const value_type &x)
{
  return isdigit(x) || x == 'x' || x == 'X';
}

  
}} // namespace boost  namespace checks


#endif // BOOST_CHECKS_LEXICAL_FILTER_HPP