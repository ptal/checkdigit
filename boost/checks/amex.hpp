//  Boost checks/amex.hpp header file
//  (C) Copyright Pierre Talbot 2011 - 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate an American Express credit card number.
*/

#ifndef BOOST_CHECKS_AMEX_HPP
#define BOOST_CHECKS_AMEX_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef> // std::size_t
#include <boost/checks/luhn.hpp>
#include <boost/checks/checksum.hpp>
 
#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>

/*!
  \brief Size of an American Express card number.
*/
#define AMEX_SIZE 15

namespace boost {
    namespace checks{

/*!
  \brief American express features
  \see luhn AMEX_SIZE
*/

typedef features
<
  luhn,
  AMEX_SIZE
> amex;

/*!
    \brief Check the validity of an American Express card number.

    \tparam range Refer to the <a href="http://www.boost.org/doc/libs/1_48_0/libs/range/doc/html/range/reference/overview.html">range concept</a>.
    
    \param x is the value range to check.

    \returns @c true if the check digit is correct and the length of @c x equals to @c AMEX_SIZE, @c false otherwise.
    
    \see check_sequence amex AMEX_SIZE
*/
template <typename range>
bool check_amex (const range& x)
{
  return check_sequence<amex>(x);
}

bool check_amex(const std::string& x)
{
  return check_sequence<amex>(make_precheck<digit>(x));
}


/*!
    \brief Calculate the check digit of an American Express card number.

    \tparam range Refer to the <a href="http://www.boost.org/doc/libs/1_48_0/libs/range/doc/html/range/reference/overview.html">range concept</a>.
    
    \param x is the value range to check.

    \returns The check digit as an integer in the range [0..9]. If the length of @c x is not equals to @c AMEX_SIZE, @c bad_sequence is returned.

    \see compute_checkdigit bad_sequence amex AMEX_SIZE
*/
template <typename range>
std::size_t compute_amex(const range& x)
{
  return compute_checkdigit<amex>(x);
}

std::size_t compute_amex(const std::string& x)
{
  return compute_checkdigit<amex>(make_precheck<digit>(x));
}

}} // namespace boost   namespace checks
#endif
