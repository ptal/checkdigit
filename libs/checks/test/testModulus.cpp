//! \file testModulus.cpp

// Copyright Pierre Talbot 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Boost test of various check 'digit' systems.

// See http://www.boost.org/doc/libs/1_46_1/libs/test/doc/html/utf/testing-tools/reference.html

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE "Modulus Check Test Suite"
#define BOOST_LIB_DIAGNOSTIC "on"// Show library file details.
// Linking to lib file: libboost_unit_test_framework-vc100-mt-gd-1_47.lib  (trunk at 12 Jun 11)

#include <iostream>
#include <iomanip>
#include <list>

#include <boost/test/unit_test.hpp> // Enhanced for unit_test framework autolink

#include <boost/checks/luhn.hpp>
#include <boost/checks/modulus10.hpp>
#include <boost/checks/checks_fwd.hpp> // Forward declarations.

#include "alteration_test.hpp"
#include "transposition_test.hpp"

template <typename functor>
unsigned int transposition( const functor &compute_checkdigit );

struct luhn_functor
{
  template <typename range>
  typename boost::checks::luhn_compute_algorithm::checkdigit<range>::type operator ()( const range &check_range ) const
  {
    return boost::checks::compute_luhn( check_range ) ;
  }
};

struct verhoeff_functor
{
  template <typename range>
  typename boost::checks::verhoeff_compute_algorithm::checkdigit<range>::type operator ()( const range &check_range ) const
  {
    return boost::checks::compute_verhoeff( check_range ) ;
  }
};

BOOST_AUTO_TEST_CASE(luhn_test)
{
  unsigned int transpositions_failures = transposition( luhn_functor() ) ;
  BOOST_CHECK_MESSAGE( transpositions_failures == 2, "" << transpositions_failures << " catched on 90.") ;
}

BOOST_AUTO_TEST_CASE(verhoeff_test)
{
  unsigned int transpositions_failures = transposition( verhoeff_functor() ) ;
  BOOST_CHECK_MESSAGE( transpositions_failures == 0, "" << transpositions_failures << " catched on 90.") ;
}