//  Boost checks/lexical_filter.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief Provides type encapsulated cctype functions and more for checking sequence.
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
    
/* Check if character is alphanumeric.
*/
template <typename value_type>
struct isalnum : public std::unary_function<value_type, bool>
{
  bool operator()(const value_type &x)
  {
    return std::isalnum(x);
  }
};

/* Check if character is decimal digit plus the special character 'X' (often occurs 
as check digit instead of 10).
*/
template <typename value_type>
struct isdigitx : public std::unary_function<value_type, bool>
{
  bool operator()(const value_type &x)
  {
    return isdigit(x) || x == 'x' || x == 'X';
  }
};

/*
Check if character is alphabetic.
*/
template <typename value_type>
struct isalpha : public std::unary_function<value_type, bool>
{  
  bool operator()(const value_type &x)
  {
    return isalpha(x);
  }
};

/*
Check if character is decimal digit.
*/
template <typename value_type>
struct isdigit : public std::unary_function<value_type, bool>
{
  bool operator()(const value_type &x)
  {
    return isdigit(x);
  }
};


  
}} // namespace boost  namespace checks


#endif // BOOST_CHECKS_LEXICAL_FILTER_HPP