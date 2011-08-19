//  Boost checks/limits.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file limits.hpp
    \brief Provides two types of size contract to manage the expected size of the check sequence.
*/

#ifndef BOOST_CHECK_LIMITS_HPP
#define BOOST_CHECK_LIMITS_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/static_assert.hpp>

namespace boost{
  namespace checks{

/*! \class strict_size_contract
    \brief This is a contract class used to verify that a sequence have the expected size.

    \tparam expected_size The expected size of the sequence. (expected_size > 0, enforced with static assert).
    \tparam exception_size_failure If the size is not respected a exception_size_failure exception will be throwed. Default exception class is std::invalid_argument.
*/
template <size_t expected_size, class exception_size_failure = std::invalid_argument>
struct strict_size_contract
{
  /*! \fn static void respect_size_contract(const size_t valid_value_counter)
    \brief Enforce the size contract.

    \param valid_value_counter Number of valid values in the sequence.
    \throws exception_size_failure If the terms of the contract are not respected. (valid_value_counter != expected_size).
  */
  static void respect_size_contract(const size_t valid_value_counter)
  {
    BOOST_STATIC_ASSERT_MSG( expected_size > 0 , "The expected size must be greater than 0" );
    if( valid_value_counter != expected_size )
      throw exception_size_failure("Too few or too much valid values in the sequence.") ;
  }

  /*! \fn static bool reach_one_past_the_end(const size_t valid_value_counter)
    \brief Tells if the expected interval of value [0..n) is outstripped.

    \param valid_value_counter Number of valid values in the sequence already counted.
    \returns True if valid_value_counter is one past the end of the expected size, false otherwise.
  */
  static bool reach_one_past_the_end(const size_t valid_value_counter)
  {
    BOOST_STATIC_ASSERT_MSG( expected_size > 0 , "The expected size must be greater than 0" );
    return valid_value_counter > expected_size ;
  }
};

/*! \class no_null_size_contract
    \brief This is a contract class used to verify that a sequence have not a size of zero.

    \tparam exception_size_failure If the size is null a exception_size_failure exception will be throwed. Default exception class is std::invalid_argument.
*/
template <class exception_size_failure = std::invalid_argument>
struct no_null_size_contract
{
/*! \fn static void respect_size_contract(const size_t valid_value_counter)
    \brief Enforce the size contract.

    \param valid_value_counter Number of valid values in the sequence.
    \throws exception_size_failure If the terms of the contract are not respected. (valid_value_counter == 0).
  */
  static void respect_size_contract(const size_t valid_value_counter)
  {
    if( valid_value_counter == 0 )
      throw exception_size_failure("No valid value in this sequence.") ;
  }

/*! \fn static bool reach_one_past_the_end(const size_t valid_value_counter)
    \brief Tells if the expected interval of value [0..n) is outstripped.

    \param valid_value_counter Number of valid values in the sequence already counted.
    \returns False.
  */
  static bool reach_one_past_the_end(const size_t valid_value_counter)
  {
    return false ;
  }
};

}}

#endif // BOOST_CHECKS_LIMITS_HPP