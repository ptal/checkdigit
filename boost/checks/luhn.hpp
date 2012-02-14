//  Boost checks/luhn.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate sequence with the Luhn algorithm.
*/

#ifndef BOOST_CHECKS_LUHN_INCLUDED
#define BOOST_CHECKS_LUHN_INCLUDED

#ifdef _MSC_VER
  #pragma once
#endif

#include <boost/checks/modulus10.hpp>
#include <boost/checks/checkdigit.hpp>

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost {
    namespace checks{

/*!
  \brief This is the weight used by the Luhn algorithm.
*/
typedef boost::checks::weight<1,2> luhn_weight;

/*! \class luhn_algorithm
    \brief This class can be used to compute or validate checksum with the Luhn algorithm.

    \tparam checkdigit_size Help functions to provide same behavior on sequence with and without check digits. No "real" value in the sequence will be skipped.
*/
struct luhn_algorithm : boost::checks::modulus10_algorithm <luhn_weight>
{
  /*!
    \brief Compute the Luhn algorithm operation on the checksum.

    \post checksum is equal to the new computed checksum.

    \param current_valid_value is the current valid value analysed.
    \param valid_value_counter is the number of valid value already counted (the current value is not included).\n This is also the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).
    \param checksum is the current checksum.

    \remarks This function become obsolete if you don't use luhn_weight. It is using operator "<<" to make internal multiplication.
  */
  static std::size_t process(std::size_t checksum, std::size_t value, std::size_t value_pos)
  {
    std::size_t weighted_value = value << (luhn_weight::at(value_pos) -1);
    return checksum + weighted_value % 10 + weighted_value / 10;
  }
  /*
  template <typename Function>
  struct processor
  {
    Function counter;
    bool weight;
    processor(Function counter) : counter(counter), weight(!(counter()&1)) { } 

    std::size_t operator()(std::size_t checksum, std::size_t value)
    {
      return checksum + value << weight % 10 + value << weight / 10;
    }
  };

  validate_checksum <UnaryPredicate : for the checkdigit validation
  compute_checksum <UnaryFunction : for the computation of the checkdigit

*/
};

/*!
    \brief Validate a sequence according to the luhn_check_algorithm type.

    \pre check_seq is a valid range.\n size_expected > 0 (enforced by static assert).

    \tparam size_expected is the number of valid value expected in the sequence.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.

    \returns @c true if the check digit is correct, false otherwise.
*/
template <size_t size_expected, typename check_range>
bool check_luhn (const check_range& check_seq)
{
  return boost::checks::check_sequence<luhn_algorithm, digit_prechecksum, size_expected>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Validate a sequence according to the luhn_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename check_range>
bool check_luhn (const check_range& check_seq)
{
  return boost::checks::check_sequence<luhn_algorithm, digit_prechecksum (boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Calculate the check digit of a sequence according to the luhn_compute_algorithm type.

    \pre check_seq is a valid range.\n size_expected > 0 (enforced by static assert).

    \tparam size_expected is the number of valid value expected in the sequence. (So the check digit is not included.)
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <size_t size_expected, typename check_range>
std::size_t compute_luhn(const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<luhn_algorithm, digit_prechecksum, size_expected, boost::checks::basic_checkdigit>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Calculate the check digit of a sequence according to the luhn_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename check_range>
std::size_t compute_luhn (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<luhn_algorithm, digit_prechecksum, boost::checks::basic_checkdigit>(boost::rbegin(check_seq), boost::rend(check_seq));
}


}} // namespace boost   namespace checks

#endif // BOOST_CHECKS_LUHN_HPP
