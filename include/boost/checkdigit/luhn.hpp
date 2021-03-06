//  Boost checks/luhn.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate sequence with the Luhn algorithm.
*/

#ifndef BOOST_CHECKDIGIT_LUHN_INCLUDED
#define BOOST_CHECKDIGIT_LUHN_INCLUDED

#ifdef _MSC_VER
  #pragma once
#endif

#include <boost/checkdigit/modulus10.hpp>
#include <boost/checkdigit/checkdigit.hpp>

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>

#include <boost/checkdigit/checksum.hpp> 

namespace boost {
    namespace checkdigit{

/*!
  \brief Compute the Luhn algorithm operation on the checksum.

  \post checksum is equal to the new computed checksum.

  \param current_valid_value is the current valid value analysed.
  \param valid_value_counter is the number of valid value already counted (the current value is not included).\n This is also the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).
  \param checksum is the current checksum.

*/
struct luhn_processor
{
  luhn_processor() {} 

  size_t operator()(size_t checksum, size_t value, size_t pos)
  {
    size_t weighted_value = value << (pos & 1);
    return checksum + weighted_value % 10 + weighted_value / 10;
  }
};

typedef checksum
<
  luhn_processor,
  mod10_validation,
  mod10_checkdigit
>
luhn;

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
  return check_sequence<features<luhn, size_expected> >(check_seq);
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
  return check_sequence<features<luhn> >(check_seq);
}

/*!
    \brief Calculate the check digit of a sequence according to the luhn_compute_algorithm type.

    \pre check_seq is a valid range.\n size_expected > 0 (enforced by static assert).

    \tparam size_expected is the number of valid value expected in the sequence. (So the check digit is not included.)
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.
    \throws boost::checkdigit::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <size_t size_expected, typename check_range>
size_t compute_luhn(const check_range& check_seq)
{
  return compute_checkdigit<features<luhn, size_expected> >(check_seq);
}

/*!
    \brief Calculate the check digit of a sequence according to the luhn_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.
    \throws boost::checkdigit::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename check_range>
size_t compute_luhn (const check_range& check_seq)
{
  return compute_checkdigit<features<luhn> >(check_seq);
}


}} // namespace boost   namespace checkdigit

#endif // BOOST_CHECKDIGIT_LUHN_HPP
