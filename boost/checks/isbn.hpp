//  Boost checks/isbn.hpp header file
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate an International Standard Book Number (ISBN) of size 10 or 13.

    \remarks The ISBN-13 is derived from the EAN number, so EAN macro or type are used.
*/

#ifndef BOOST_CHECKS_ISBN_HPP
#define BOOST_CHECKS_ISBN_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/checks/ean.hpp>
#include <boost/checks/modulus11.hpp>

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>

/*!
  \brief This macro defines the size of an ISBN-10.
*/
#define ISBN10_SIZE 10
/*!
  \brief This macro defines the size of an ISBN-10 without its check digit.
*/
#define ISBN10_SIZE_WITHOUT_CHECKDIGIT 9

namespace boost {
    namespace checks{

/*! \class isbn13_algorithm
    \brief This class can be used to compute or validate checksum with a basic modulus 10 but using a custom filter for the ISBN-13 prefix.

    \tparam checkdigit_size Help functions to provide same behavior on sequence with and without check digits. No "real" value in the sequence will be skipped.
*/
template <std::size_t checkdigit_size>
struct isbn13_algorithm : boost::checks::modulus10_algorithm<boost::checks::ean_weight, checkdigit_size>
{
  /*!
    \brief Verify that a number matches the ISBN-13 pattern.

    \param value is the current valid value analysed.
    \param value_position is the number of valid value already counted (the current value is not included).\n This is also the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).

    \throws std::invalid_argument if the three first character are not equal to 978 or 979. The exception contains a descriptive message of what was expected.

    \remarks This function use the macro EAN13_SIZE to find the real position from left to right.
  */
  template <typename value_type>
  static bool require(const value_type &value, std::size_t value_pos)
  {
    std::size_t real_pos_from_left = EAN13_SIZE - value_pos - checkdigit_size;

    return  (real_pos_from_left != 1 || value == '9') &&
            (real_pos_from_left != 2 || value == '7') &&
            (real_pos_from_left != 3 || value == '8' || value == '9');
  }
};

/*!
  \brief This is the type of the ISBN-13 algorithm for validating a check digit.
*/
typedef boost::checks::isbn13_algorithm<0> isbn13_check_algorithm;
/*!
  \brief This is the type of the ISBN-13 algorithm for computing a check digit.
*/
typedef boost::checks::isbn13_algorithm<1> isbn13_compute_algorithm;

/*!
    \brief Validate a sequence according to the isbn13_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly EAN13_SIZE digits.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename check_range>
bool check_isbn13 (const check_range& check_seq)
{
  return boost::checks::check_sequence<isbn13_check_algorithm, EAN13_SIZE>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Calculate the check digit of a sequence according to the isbn13_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly EAN13_SIZE_WITHOUT_CHECKDIGIT digits.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename check_range>
typename boost::range_value<check_range>::type compute_isbn13 (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<isbn13_compute_algorithm, EAN13_SIZE_WITHOUT_CHECKDIGIT>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Validate a sequence according to the mod11_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly ISBN10_SIZE digits.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename check_range>
bool check_isbn10(const check_range& check_seq)
{
  return boost::checks::check_modulus11<ISBN10_SIZE>(check_seq);
}

/*!
    \brief Calculate the check digit of a sequence according to the mod11_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly ISBN10_SIZE_WITHOUT_CHECKDIGIT digits.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9,X].
*/
template <typename check_range>
typename boost::range_value<check_range>::type compute_isbn10(const check_range& check_seq)
{
  return boost::checks::compute_modulus11<ISBN10_SIZE_WITHOUT_CHECKDIGIT>(check_seq);
}


}} // namespace boost   namespace checks
#endif // BOOST_CHECKS_ISBN_HPP
