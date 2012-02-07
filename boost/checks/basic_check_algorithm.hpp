//  Boost checks/basic_check_algorithm.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides a class that should be used as an "interface" because most of the static functions should be re-implemented using inheritance.

    \remarks The class implements static functions that are common to many algorithms.
*/

#ifndef BOOST_CHECKS_BASIC_CHECK_ALGO_HPP
#define BOOST_CHECKS_BASIC_CHECK_ALGO_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef> // std::size_t
#include <boost/lexical_cast.hpp>
#include <boost/checks/translation_exception.hpp>

namespace boost{
  namespace checks{

/*! \class basic_check_algorithm
    \brief The main check algorithm class that provides every static function that can be overloaded.\n Most of the functions must be re-implemented to have the desired behavior.

    \tparam traversal_direction must meet the iterator_direction concept requirements.
    \tparam checkdigit_size Helper functions to provide the same behavior on sequence with and without checkdigits. No "real" value in the sequence will be skipped.
*/
template <std::size_t checkdigit_size>
struct basic_check_algorithm
{
  template <typename value_type>
  static bool skip(const value_type &value)
  {
    return !isdigit(value);
  }

  /*!
    \brief translate a value of the sequence into an integer valid value.

    \tparam value is the type of a value in the sequence.
    \param current_value is the current value analysed in the sequence that must be translated.
    \param valid_value_counter is the number of valid value(s) already counted (the current value is not included).\n This is also the position (beyond the valid values) of the current value analysed (0 <= valid_value_counter < n).

    \throws boost::checks::translation_exception is thrown if the translation of current_value failed.\n This will automatically throw if the value is not a digit (0 <= i < 10).

    \returns the translation of the current value in the range [0..9].
*/
  template <typename value_type>
  static std::size_t convert(const value_type &value)
  {
    return value - '0';
  }

  /*!
    \brief Validate the checksum.

    \param checksum is the checksum to validate.

    \returns @c true always (unless overloaded to check a sequence).

    \remarks This function should be overloaded if you want to check a sequence.
  */
  static bool validate_checksum(std::size_t checksum)
  {
    return true;
  }

  /*!
    \brief Compute the check digit of a sequence.

    \pre The type checkdigit must provides the default initialisation feature.

    \tparam checkdigit is the type of the check digit desired.
    \param checksum is the checksum used to extract the check digit.

    \returns default initialized value of checkdigit.

    \remarks This function should be overloaded if you want to compute the check digit of a sequence.
  */
  template <typename checkdigit>
  static checkdigit compute_checkdigit(std::size_t checksum)
  {
    return checkdigit();
  }

  /*!
    \brief Compute the check digit(s) of a sequence.

    \pre checkdigits must be a valid initialized iterator.

    \tparam checkdigits_iter must meet the OutputIterator requirements.
    \param checksum is the checksum used to extract the check digit(s).
    \param checkdigits is the iterator with which the check digit(s) will be written.

    \returns checkdigits.

    \remarks This function should be overloaded if you want your algorithm to compute more than one check digit (through it works for just one check digit too).
  */
  template <typename checkdigits_iter>
  static checkdigits_iter compute_multicheckdigit(std::size_t checksum, checkdigits_iter checkdigits)
  {
    return checkdigits;
  }

  /*!
    \brief Compute an operation on the checksum with the current valid value.
    \post Do nothing. The checksum is unchanged.

    \param current_valid_value is the current valid value analysed.
    \param valid_value_counter is the number of valid value(s) already counted (the current value is not included).\n This is also the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).
    \param checksum is the current checksum.

    \remarks This function should be overloaded if you want to calculate the checksum of a sequence.
  */
  static std::size_t process(std::size_t, std::size_t, std::size_t)
  {
    return std::size_t();
  }

  /*!
    \brief Filtering of a valid value according to its position.

    \post Do nothing.

    \param current_valid_value is the current valid value analysed.
    \param current_value_position is the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).

    \remarks This function should be overloaded if you want to filter the values with their positions.
  */
  template <typename value_type>
  static bool require(const value_type&, std::size_t)
  {
    return true;
  }
};


}} // namespace boost  namespace checks

#endif //BOOST_CHECKS_BASIC_CHECK_ALGO_HPP
