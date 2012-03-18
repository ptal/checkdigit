//  Boost checks/verhoeff.hpp header file  ------------------------------------//
// (C)Copyright Pierre Talbot 2011 - 2012
//  Distributed under the Boost Software License, Version 1.0.(See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute a Verhoeff checksum.
    \details See http://en.wikipedia.org/wiki/Verhoeff_algorithm
*/

#ifndef BOOST_VERHOEFF_INCLUDED
#define BOOST_VERHOEFF_INCLUDED

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef>

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/checks/checksum.hpp>

#include <boost/checks/weight.hpp>
#include <boost/checks/checkdigit.hpp>
#include <boost/checks/basic_checks.hpp>
#include <boost/checks/basic_check_algorithm.hpp>

namespace boost {
    namespace checks{

/*! \class verhoeff_algorithm
    \brief This class can be used to compute or validate checksum with the Verhoeff algorithm.

    \tparam checkdigit_size Help functions to provide same behavior on sequence with and without check digits. No "real" value in the sequence will be skipped.
*/
  /*!
    \brief Validate the Verhoeff checksum.

    \param checksum is the checksum to validate.

    \returns @c true if the checksum is correct, @c false otherwise.
  */
struct verhoeff_validation
{
  bool operator()(std::size_t checksum)
  {
    return !checksum;
  }
};
  /*!
    \brief Compute the check digit with the Verhoeff inverse table.

    \tparam checkdigit is the type of the check digit desired.
    \param checksum is the checksum used to extract the check digit.

    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The Verhoeff check digit of checksum.
  */
struct verhoeff_checkdigit
{
  static const unsigned char inv[10];
  
  std::size_t operator()(std::size_t checksum)
  {
    return inv[checksum];
  }
};
const unsigned char verhoeff_checkdigit::inv[10] = {0, 4, 3, 2, 1, 5, 6, 7, 8, 9};

/*!
  \brief Compute the Verhoeff scheme on the checksum with the current valid value.

  \post checksum is equal to the new computed checksum.

  \param current_valid_value is the current valid value analysed.
  \param valid_value_counter is the number of valid value already counted(the current value is not included).\n This is also the position(above the valid values)of the current value analysed(0 <= valid_value_counter < n).
  \param checksum is the current checksum.

  \remarks This function use the classic table d and p of the Verhoeff algorithm.
*/
struct verhoeff_processor
{
  static const unsigned char d[10][10];
  static const unsigned char p[8][10];

  verhoeff_processor() { } 

  std::size_t operator()(std::size_t checksum, std::size_t value, std::size_t pos)
  {
    return d[checksum][p[pos % 8][value]];
  }
};

const unsigned char verhoeff_processor::d[10][10] =
{
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
  { 1, 2, 3, 4, 0, 6, 7, 8, 9, 5 },
  { 2, 3, 4, 0, 1, 7, 8, 9, 5, 6 },
  { 3, 4, 0, 1, 2, 8, 9, 5, 6, 7 },
  { 4, 0, 1, 2, 3, 9, 5, 6, 7, 8 },
  { 5, 9, 8, 7, 6, 0, 4, 3, 2, 1 },
  { 6, 5, 9, 8, 7, 1, 0, 4, 3, 2 },
  { 7, 6, 5, 9, 8, 2, 1, 0, 4, 3 },
  { 8, 7, 6, 5, 9, 3, 2, 1, 0, 4 },
  { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }
};

const unsigned char verhoeff_processor::p[8][10] =
{
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
  { 1, 5, 7, 6, 2, 8, 3, 0, 9, 4 },
  { 5, 8, 0, 3, 7, 9, 6, 1, 4, 2 },
  { 8, 9, 1, 6, 0, 4, 3, 5, 2, 7 },
  { 9, 4, 5, 3, 1, 2, 6, 8, 7, 0 },
  { 4, 2, 8, 6, 5, 7, 3, 9, 0, 1 },
  { 2, 7, 9, 3, 8, 0, 6, 4, 1, 5 },
  { 7, 0, 4, 6, 9, 1, 3, 2, 5, 8 }
};

typedef checksum
<
  verhoeff_processor,
  verhoeff_validation,
  verhoeff_checkdigit
> verhoeff;

/*!
    \brief Validate a sequence according to the verhoeff_check_algorithm type.

    \pre check_seq is a valid range.\n size_expected > 0(enforced by static assert).

    \tparam size_expected is the number of valid value expected in the sequence.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <size_t size_expected, typename check_range>
bool check_verhoeff(const check_range& check_seq)
{
  return check_sequence<features<verhoeff, size_expected> >(check_seq);
}

/*!
    \brief Validate a sequence according to the verhoeff_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename check_range>
bool check_verhoeff(const check_range& check_seq)
{
  return check_sequence<features<verhoeff_processor> >(check_seq);
}

/*!
    \brief Calculate the check digit of a sequence according to the verhoeff_compute_algorithm type.

    \pre check_seq is a valid range.\n size_expected > 0(enforced by static assert).

    \tparam size_expected is the number of valid value expected in the sequence.(So the check digit is not included.)
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <size_t size_expected, typename check_range>
std::size_t compute_verhoeff(const check_range& check_seq)
{
  return compute_checkdigit<features<verhoeff, size_expected> >(check_seq);
}

/*!
    \brief Calculate the check digit of a sequence according to the verhoeff_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename check_range>
std::size_t compute_verhoeff(const check_range& check_seq)
{
  return compute_checkdigit<features<verhoeff> >(check_seq);
}

}}
#endif
