//! \file test_checks_tools.cpp

// Copyright Pierre Talbot 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Boost test of tools used by the Boost::checks library.

// See http://www.boost.org/doc/libs/1_47_1/libs/test/doc/html/utf/testing-tools/reference.html

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE "Check Tools Test Suite"
#define BOOST_LIB_DIAGNOSTIC "on"// Show library file details.
// Linking to lib file: libboost_unit_test_framework-vc100-mt-gd-1_47.lib  (trunk at 12 Jun 11)

#include <iostream>
#include <iomanip>

#include <boost/test/unit_test.hpp> // Enhanced for unit_test framework autolink.

#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/limits.hpp>


BOOST_AUTO_TEST_CASE(weight_test)
{
  typedef boost::checks::weight<0,1,2,3,4,5,6,7,8,9> number_suite ;
  for(int i=0 ; i < 100 ; ++i)
    BOOST_CHECK ( i%10 == number_suite::weight_associated_with_pos( i ) ) ;

  typedef boost::checks::weight<1,1,1,1,1,1> suite_of_1 ;
  for(int i=0 ; i < 100; ++i)
    BOOST_CHECK ( 1 == suite_of_1::weight_associated_with_pos( i ) ) ;

  typedef boost::checks::weight<> no_weight_specify ;
  for(int i=0 ; i < 100; ++i)
    BOOST_CHECK ( 0 == no_weight_specify::weight_associated_with_pos( i ) ) ;
}

BOOST_AUTO_TEST_CASE(iteration_sense_test)
{
  typedef boost::checks::leftmost leftmost ;
  typedef boost::checks::rightmost rightmost ;

  std::string sequence = "123456789" ;
  leftmost::iterator<std::string>::type leftmost_begin = leftmost::begin( sequence );
  leftmost::iterator<std::string>::type leftmost_end = leftmost::end( sequence );

  BOOST_CHECK ( '1' == *leftmost_begin ) ;

  rightmost::iterator<std::string>::type rightmost_begin = rightmost::begin( sequence );
  rightmost::iterator<std::string>::type rightmost_end = rightmost::end( sequence );

  BOOST_CHECK ( '9' == *rightmost_begin ) ;

  BOOST_CHECK (*rightmost_begin == *(--leftmost_end) );
  BOOST_CHECK (*leftmost_begin == *(--rightmost_end) );
}

BOOST_AUTO_TEST_CASE(limits_test)
{
  typedef boost::checks::strict_size_contract<5> size_expected ;
  typedef boost::checks::no_null_size_contract<> no_size_expected ;

  size_expected::respect_size_contract( 5 ) ;

  for(int i = 6 ; i < 14 ; ++i)
    BOOST_CHECK_THROW ( size_expected::respect_size_contract( i%10+1 ) , std::invalid_argument )

  for(int i=1 ; i < 10; ++i)
    no_size_expected::respect_size_contract (i) ;

  BOOST_CHECK_THROW ( no_size_expected::respect_size_contract (0), std::invalid_argument )

  for(int i = 0 ; i < 6 ; ++i)
  {
    BOOST_CHECK ( !size_expected::reach_one_past_the_end(i) );
    BOOST_CHECK ( !no_size_expected::reach_one_past_the_end(i) );
  }
  BOOST_CHECK ( size_expected::reach_one_past_the_end(6) );
  BOOST_CHECK ( !no_size_expected::reach_one_past_the_end(6) );

}