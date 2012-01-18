//  Boost checks/amex.hpp header file
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate an American Express credit card number.
*/

#ifndef BOOST_CHECKS_AMEX_HPP
#define BOOST_CHECKS_AMEX_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/checks/luhn.hpp>

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>

/*!
  \brief This macro defines the size of a American Express card number (15).
*/
#define AMEX_SIZE 15
/*!
  \brief This macro defines the size of a American Express card number without its check digit (14).
*/
#define AMEX_SIZE_WITHOUT_CHECKDIGIT 14

namespace boost {
    namespace checks{

/*! \class amex_algorithm
    \brief This class can be used to compute or validate checksum with the Luhn algorithm, but filter following the Amex pattern.

    \tparam number_of_virtual_value_skipped Help functions to provide same behavior on sequence with and without check digits. No "real" value in the sequence will be skipped.
*/
template <unsigned int number_of_virtual_value_skipped = 0>
struct amex_algorithm : boost::checks::luhn_algorithm <number_of_virtual_value_skipped>
{
  /*!
    \brief Verify that a number matches the Amex pattern.

    \param current_valid_value is the current valid value analysed.
    \param current_value_position is the number of valid value already counted (the current value is not included).\n This is also the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).

    \throws std::invalid_argument if the first character is not equal to 3 or the second is not equal to 4 or 7. The exception contains a descriptive message of what was expected.

    \remarks This function use the macro AMEX_SIZE to find the real position from left to right.
  */
  static void filter_valid_value_with_pos(const unsigned int current_valid_value, const unsigned int current_value_position)
  {
    const unsigned int real_pos_from_left = AMEX_SIZE - current_value_position - number_of_virtual_value_skipped;

    if(real_pos_from_left == 1 && current_valid_value != 3)
      throw std::invalid_argument("The Major Industry Identifier of an American Express should be 3!");
    else if(real_pos_from_left == 2 && current_valid_value != 4 && current_valid_value != 7)
      throw std::invalid_argument("The Issuer Identification Number of an American Express should be 34 or 37!");
  }
};

/*!
  \brief This is the type of the Amex algorithm for validating a check digit.
*/
typedef amex_algorithm<0> amex_check_algorithm; 
/*!
  \brief This is the type of the Amex algorithm for computing a check digit.
*/
typedef amex_algorithm<1> amex_compute_algorithm;

/*!
    \brief Validate a sequence according to the amex_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly AMEX_SIZE digits.
    \throws std::invalid_argument if the two first digits (from the leftmost) don't match the Amex pattern.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename check_range>
bool check_amex (const check_range& check_seq)
{
  return boost::checks::check_sequence<amex_check_algorithm, AMEX_SIZE>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Calculate the check digit of a sequence according to the amex_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly AMEX_SIZE_WITHOUT_CHECKDIGIT digits.
    \throws std::invalid_argument if the two first digits (from the leftmost) don't match the amex pattern.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename check_range>
typename boost::range_value<check_range>::type compute_amex(const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<amex_compute_algorithm, AMEX_SIZE_WITHOUT_CHECKDIGIT>(boost::rbegin(check_seq), boost::rend(check_seq));
}


}} // namespace boost   namespace checks
#endif
