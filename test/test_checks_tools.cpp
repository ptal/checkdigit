//! \file test_checks_tools.cpp

// Copyright Pierre Talbot 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Boost test of tools used by the Boost::checks library.

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE "Check Tools Test Suite"
#define BOOST_LIB_DIAGNOSTIC "on"// Show library file details.

#include <iostream>
#include <iomanip>

#include <boost/test/unit_test.hpp> // Enhanced for unit_test framework autolink.

#include <boost/checks/weight.hpp>
#include <boost/checks/checksum.hpp>


BOOST_AUTO_TEST_CASE(weight_test)
{
  typedef boost::checks::weight<0,1,2,3,4,5,6,7,8,9> number_suite ;
  for(size_t i=0 ; i < 100 ; ++i)
    BOOST_CHECK ( i%10 == number_suite::at( i ) ) ;

  typedef boost::checks::weight<1,1,1,1,1,1> suite_of_1 ;
  for(size_t i=0 ; i < 100; ++i)
    BOOST_CHECK ( 1 == suite_of_1::at( i ) ) ;

  typedef boost::checks::weight<> no_weight_specify ;
  for(size_t i=0 ; i < 100; ++i)
    BOOST_CHECK ( 0 == no_weight_specify::at( i ) ) ;
}