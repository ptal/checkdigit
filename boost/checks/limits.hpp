//  Boost checks/limits.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECK_LIMITS_HPP
#define BOOST_CHECK_LIMITS_HPP

#include <boost/static_assert.hpp>

namespace boost{
  namespace checks{

template <size_t expected_size, class exception_size_failure = std::invalid_argument>
struct strict_size_contract
{
  static void respect_size_contract(size_t valid_values_counted)
  {
    BOOST_STATIC_ASSERT_MSG( expected_size > 0 , "The expected size must be greater than 0" );
    if( valid_values_counted != expected_size )
      throw exception_size_failure("Too few or too much valid values in the sequence.") ;
  }
};

template <class exception_size_failure = std::invalid_argument>
struct no_null_size_contract
{
  static void respect_size_contract(size_t valid_values_counted)
  {
    if( valid_values_counted == 0 )
      throw exception_size_failure("No valid value in this sequence.") ;
  }
};

}}

#endif // BOOST_CHECKS_LIMITS_HPP