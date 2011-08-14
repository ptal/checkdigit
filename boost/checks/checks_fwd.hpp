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

// MPL and PP includes
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/preprocessor/repetition.hpp>
// Range include
#include <boost/range/numeric.hpp>
// Lexical include
#include <boost/lexical_cast.hpp>
#include <boost/checks/modulus10.hpp>

namespace boost{
  namespace checks{

template <size_t size_expected, typename check_range>
bool check_mod10 (const check_range& check_seq);

template <typename check_range>
bool check_mod10 (const check_range& check_seq);

template <size_t size_expected, typename check_range>
typename boost::checks::mod10_algorithm::checkdigit<check_range>::type compute_mod10 (const check_range& check_seq);

template <typename check_range>
typename boost::checks::mod10_algorithm::checkdigit<check_range>::type compute_mod10 (const check_range& check_seq);
  
  
}}
#endif \\ BOOST_CHECK_CHECKS_FWD_HPP