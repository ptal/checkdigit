//  Boost checks/visa.hpp header file
// (C)Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0.(See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate a Visa credit card number.
*/

#ifndef BOOST_CHECKS_VISA_HPP
#define BOOST_CHECKS_VISA_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/checks/luhn.hpp>

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>

/*!
  \brief This macro defines the size of a Visa number.
*/
#define VISA_SIZE 16
/*!
  \brief This macro defines the size of a Visa number without its check digit.
*/
#define VISA_SIZE_WITHOUT_CHECKDIGIT 15

namespace boost {
    namespace checks{

/*! \class visa_algorithm
    \brief This class can be used to compute or validate checksum with the Luhn algorithm, but filter following the Visa pattern.

    \tparam number_of_virtual_value_skipped Helper functions to provide same behavior on a sequence with and without check digits. No "real" value in the sequence will be skipped.
*/
template <unsigned int number_of_virtual_value_skipped = 0>
struct visa_algorithm : boost::checks::luhn_algorithm <number_of_virtual_value_skipped>
{
  /*!
    \brief Verify that a number matches the Visa pattern.

    \param current_valid_value is the current valid value analysed.
    \param current_value_position is the number of valid value already counted(the current value is not included).\n This is also the position(above the valid values)of the current value analysed(0 <= valid_value_counter < n).

    \throws std::invalid_argument if the first character is not equal to 4. The exception contains a descriptive message of what was expected.

    \remarks This function use the macro VISA_SIZE to find the real position from left to right.
  */
  static void filter_valid_value_with_pos(const unsigned int current_valid_value, const unsigned int current_value_position)
  {
    const unsigned int real_pos_from_left = VISA_SIZE - current_value_position - number_of_virtual_value_skipped;

    if(real_pos_from_left == 1 && current_valid_value != 4)
      throw std::invalid_argument("The Major Industry Identifier of a VISA credit card should be 4!");
  }
};

/*!
  \brief This is the type of the Visa algorithm for validating a check digit.
*/
typedef visa_algorithm<0> visa_check_algorithm;
/*!
  \brief This is the type of the Visa algorithm for computing a check digit.
*/
typedef visa_algorithm<1> visa_compute_algorithm;

/*!
    \brief Validate a sequence according to the visa_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly VISA_SIZE digits.
    \throws std::invalid_argument if the first digit(from the leftmost)doesn't match the Visa pattern.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename check_range>
bool check_visa(const check_range& check_seq)
{
  return boost::checks::check_sequence<visa_check_algorithm, VISA_SIZE>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Calculate the check digit of a sequence according to the visa_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly VISA_SIZE_WITHOUT_CHECKDIGIT digits.
    \throws std::invalid_argument if the first digit(from the leftmost)doESn't match the Visa pattern.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename check_range>
typename boost::range_value<check_range>::type compute_visa(const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<visa_compute_algorithm, VISA_SIZE_WITHOUT_CHECKDIGIT>(boost::rbegin(check_seq), boost::rend(check_seq));
}


}}  // namespace boost   namespace checks
#endif // BOOST_CHECKS_VISA_HPP
