//  Boost checks/mastercard.hpp header file
// (C)Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0.(See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate a Mastercard credit card number.
*/

#ifndef BOOST_CHECKS_MASTERCARD_HPP
#define BOOST_CHECKS_MASTERCARD_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>

#include <boost/checks/luhn.hpp>

/*!
  \brief This macro defines the size of a Mastercard number.
*/
#define MASTERCARD_SIZE 16
/*!
  \brief This macro defines the size of a Mastercard number without its check digit.
*/
#define MASTERCARD_SIZE_WITHOUT_CHECKDIGIT 15

namespace boost {
    namespace checks{

/*! \class mastercard_algorithm
    \brief This class can be used to compute or validate checksum with the Luhn algorithm, but filter following the Mastercard pattern.

    \tparam checkdigit_size Help functions to provide same behavior on sequence with and without check digits. No "real" value in the sequence will be skipped.
*/
template <std::size_t checkdigit_size = 0>
struct mastercard_algorithm : boost::checks::luhn_algorithm <checkdigit_size>
{
  /*!
    \brief Verify that a number matches the Mastercard pattern.

    \param current_valid_value is the current valid value analysed.
    \param current_value_position is the number of valid values already counted(the current value is not included).\n This is also the position(above the valid values)of the current value analysed(0 <= valid_value_counter < n).

    \throws std::invalid_argument if the first character is not equal to 5 or the second is not between 1 and 5. The exception contains a descriptive message of what was expected.

    \remarks This function use the macro MASTERCARD_SIZE to find the real position from left to right.
  */
  static void filter_valid_value_with_pos(const unsigned int current_valid_value, const unsigned int current_value_position)
  {
    const unsigned int real_pos_from_left = MASTERCARD_SIZE - current_value_position - checkdigit_size;

    if(real_pos_from_left == 1 && current_valid_value != 5)
      throw std::invalid_argument("The Major Industry Identifier of a Mastercard should be 5!");
    else if(real_pos_from_left == 2 && (current_valid_value == 0 || current_valid_value > 5))
      throw std::invalid_argument("The Issuer Identification Number of an Mastercard should be between 51 and 55!");
  }
};

/*!
  \brief This is the type of the Mastercard algorithm for validating a check digit.
*/
typedef mastercard_algorithm<0> mastercard_check_algorithm;
/*!
  \brief This is the type of the Mastercard algorithm for computing a check digit.
*/
typedef mastercard_algorithm<1> mastercard_compute_algorithm;

/*!
    \brief Validate a sequence according to the mastercard_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly MASTERCARD_SIZE digits.
    \throws std::invalid_argument if the two first digits(from the leftmost)don't match the Mastercard pattern.

    \returns True if the check digit is correct, false otherwise.
*/
template <typename check_range>
bool check_mastercard(const check_range& check_seq)
{
  return boost::checks::check_sequence<mastercard_check_algorithm, MASTERCARD_SIZE>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Calculate the check digit of a sequence according to the mastercard_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly MASTERCARD_SIZE_WITHOUT_CHECKDIGIT digits.
    \throws std::invalid_argument if the two first digits(from the leftmost)do not match the Mastercard pattern.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename check_range>
typename boost::range_value<check_range>::type compute_mastercard(const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<mastercard_compute_algorithm, MASTERCARD_SIZE_WITHOUT_CHECKDIGIT>(boost::rbegin(check_seq), boost::rend(check_seq));
}


}} // namespace boost   namespace checks
#endif // BOOST_CHECKS_MASTERCARD_HPP

