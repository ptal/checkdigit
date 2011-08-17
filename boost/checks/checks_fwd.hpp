//  Boost checks/checks_fwd.hpp header file //

//  (C) Copyright Pierre Talbot 2011

//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

// Provides a (perhaps temporary) mainpage for standalone Doxygen.
// This seems a convenient place to put this, but it could go somewhere else?

/*!
\file
\brief Boost.Checks forward declaration of function signatures.
\details This file can be used to copy a function signature,
but is mainly provided for testing purposes.

\mainpage

\b Boost.Checks

This is the standalone Doxygen front page of the Boost.Checks library.

This library provides a collection of functions for validating and creating check digits.

Most are primarily for checking the accuracy of short strings of typed input
(though obviously also provides against a mis-scan
by a device like a bar code or card reader, or transmission error).

The well-known ISBN is a typical example.
All single altered digits, most double altered digits,
and all transpositions of two digits are caught,
and the input rejected as an invalid ISBN.

See Boost.Checks HTML Manual at

  https://svn.boost.org/svn/boost/sandbox/SOC/2011/checks/doc/html/index.html

and/or equivalent PDF Manual at:

  https://svn.boost.org/svn/boost/sandbox/SOC/2011/checks/doc/checks.pdf

Examples are in folder:

  https://svn.boost.org/svn/boost/sandbox/SOC/2011/checks/libs/checks/example/

and C++ include files are in folder:

  https://svn.boost.org/svn/boost/sandbox/SOC/2011/checks/boost/checks/

*/

#ifndef BOOST_CHECK_CHECKS_FWD_HPP
#define BOOST_CHECK_CHECKS_FWD_HPP

#ifdef _MSC_VER
    #pragma once
#endif // _MSC_VER

#include <boost/checks/luhn.hpp>
#include <boost/checks/verhoeff.hpp>
#include <boost/checks/modulus11.hpp>
#include <boost/checks/modulus97.hpp>

namespace boost{
  namespace checks{

// Luhn

template <size_t size_expected, typename check_range>
bool check_luhn (const check_range& check_seq) ;

template <typename check_range>
bool check_luhn (const check_range& check_seq) ;

template <size_t size_expected, typename check_range>
typename boost::checks::luhn_compute_algorithm::checkdigit<check_range>::type compute_luhn (const check_range& check_seq) ;

template <typename check_range>
typename boost::checks::luhn_compute_algorithm::checkdigit<check_range>::type compute_luhn (const check_range& check_seq) ;

// Verhoeff

template <size_t size_expected, typename check_range>
bool check_verhoeff (const check_range& check_seq) ;

template <typename check_range>
bool check_verhoeff (const check_range& check_seq) ;

template <size_t size_expected, typename check_range>
typename boost::checks::verhoeff_compute_algorithm::checkdigit<check_range>::type compute_verhoeff (const check_range& check_seq) ;

template <typename check_range>
typename boost::checks::verhoeff_compute_algorithm::checkdigit<check_range>::type compute_verhoeff (const check_range& check_seq) ;

// Modulus 11

template <size_t size_expected, typename check_range>
bool check_modulus11 (const check_range& check_seq) ;

template <typename check_range>
bool check_modulus11 (const check_range& check_seq) ;

template <size_t size_expected, typename check_range>
typename boost::checks::mod11_compute_algorithm::checkdigit<check_range>::type compute_modulus11 (const check_range& check_seq) ;

template <typename check_range>
typename boost::checks::mod11_compute_algorithm::checkdigit<check_range>::type compute_modulus11 (const check_range& check_seq) ;

// Modulus 97-10 (ISO/IEC 7064:2003)

template <size_t size_expected, typename check_range>
bool check_mod97_10 (const check_range& check_seq) ;

template <typename check_range>
bool check_mod97_10 (const check_range& check_seq) ;

template <size_t size_expected, typename check_range, typename checkdigits_iter>
typename checkdigits_iter compute_mod97_10 (const check_range& check_seq, checkdigits_iter mod97_checkdigits) ;

template <typename check_range, typename checkdigits_iter>
typename checkdigits_iter compute_mod97_10 (const check_range& check_seq, checkdigits_iter mod97_checkdigits) ;

}}
#endif \\ BOOST_CHECK_CHECKS_FWD_HPP