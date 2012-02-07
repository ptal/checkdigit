//  Boost checks/modulus11.hpp header file  ------------------------------------//
// (C)Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0.(See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate classic modulus 11 checksum.
*/

#ifndef BOOST_CHECKS_MOD11_HPP
#define BOOST_CHECKS_MOD11_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/checks/translation_exception.hpp>
#include <boost/checks/weight.hpp>
#include <boost/checks/basic_checks.hpp>
#include <boost/checks/weighted_sum.hpp>

namespace boost{
  namespace checks{

/*! \class modulus11_algorithm
    \brief This class can be used to compute or validate checksum with a basic modulus 11.

    \tparam mod11_weight must meet the weight concept requirements.
    \tparam iteration_sense must meet the iteration_sense concept requirements.
    \tparam checkdigit_size Help functions to provide same behavior on sequence with and without check digits. No "real" value in the sequence will be skipped.

    \remarks The range of the check digit is [0..10], the tenth element is translated as the letter 'X'.
*/
template <typename mod11_weight, std::size_t checkdigit_size>
struct modulus11_algorithm : boost::checks::weighted_sum_algorithm<mod11_weight, checkdigit_size>
{

  template <typename value_type>
  static bool skip(const value_type &value)
  {
    return !isdigit(value) && value != 'x' && value != 'X';
  }

  /*!
    \brief translate the current value into an integer valid value.

    \tparam value is the type of a value in the sequence.
    \param current_value is the current value analysed in the sequence that must be translated.
    \param valid_value_counter is the number of valid value already counted(the current value is not included).\n This is also the position(above the valid values)of the current value analysed(0 <= valid_value_counter < n).

    \throws boost::checks::translation_exception is thrown if the translation of current_value failed.\n The translation will fail if the current value is not a digit(0 <= i < 10), unless it is the rightmost digit, when the value 10 or the 'x' or 'X' character is allowed.

    \returns the translation of the current value in the range [0..10].
*/
  template <typename value_type>
  static std::size_t translate_to_valid_value(const value_type &value)
  {
    int valid_value = value;
    if(value == 'x' || value == 'X')
      valid_value = 10;
    else if(value > 9)
      throw boost::checks::translation_exception();
    return valid_value;
  }

/* pre: value must be valid */
  template <typename value_type>
  static bool require(const value_type &value, std::size_t value_pos)
  {
    return value_pos == 0 || (value != 'X' && value != 'x');
  }

  /*!
    \brief Validate a checksum with a simple modulus 11.

    \param checksum is the checksum to validate.

    \returns true if the checksum is correct, false otherwise.
  */
  static bool validate_checksum(std::size_t checksum)
  {
    return !(checksum % 11);
  }

  /*!
    \brief Compute the check digit with a simple modulus 11.

    \tparam checkdigit is the type of the check digit desired.
    \param checksum is the checksum used to extract the check digit.

    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The modulus 11 check digit of checksum. 'X' is returned if the check digit value is equal to 10.
  */
  template <typename checkdigit>
  static checkdigit compute_checkdigit(std::size_t checksum)
  {
     return translate_checkdigit<checkdigit>((11 - checksum % 11)% 11);
  }

protected:
  template <typename checkdigit>
  static checkdigit translate_checkdigit(std::size_t _checkdigit)
  {
    if(_checkdigit == 10)
      return static_cast<checkdigit>('X');
    return boost::lexical_cast<checkdigit>(_checkdigit);
  }

};

/*!
  \brief The most common weight pattern used with a modulus 11 algorithm.
*/
typedef boost::checks::weight<1,2,3,4,5,6,7,8,9,10> mod11_weight;

/*!
  \brief This is the type of the most common modulus 11 algorithm for validating a check digit.
*/
typedef modulus11_algorithm<mod11_weight, 0> mod11_check_algorithm;

/*!
  \brief This is the type of the most common modulus 11 algorithm for computing a check digit.
*/
typedef modulus11_algorithm<mod11_weight, 1> mod11_compute_algorithm;

/*!
    \brief Validate a sequence according to the mod11_check_algorithm type.

    \pre check_seq is a valid range.\n size_expected > 0(enforced by static assert).

    \tparam size_expected is the number of valid value expected in the sequence.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.

    \returns @c true if the check digit is correct, false otherwise.
*/
template <size_t size_expected, typename check_range>
bool check_modulus11(const check_range& check_seq)
{
  return boost::checks::check_sequence<mod11_check_algorithm, size_expected>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Validate a sequence according to the mod11_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.

    \returns @c true if the check digit is correct, false otherwise.
*/
template <typename check_range>
bool check_modulus11(const check_range& check_seq)
{
  return boost::checks::check_sequence<mod11_check_algorithm>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Calculate the check digit of a sequence according to the mod11_compute_algorithm type.

    \pre check_seq is a valid range.\n size_expected > 0(enforced by static assert).

    \tparam size_expected is the number of valid value expected in the sequence.(So the check digit is not included.)
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9,X].
*/
template <size_t size_expected, typename check_range>
typename boost::range_value<check_range>::type compute_modulus11(const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<mod11_compute_algorithm, size_expected>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Calculate the check digit of a sequence according to the mod11_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9,X].
*/
template <typename check_range>
typename boost::range_value<check_range>::type compute_modulus11(const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<mod11_compute_algorithm>(boost::rbegin(check_seq), boost::rend(check_seq));
}

}} // namespace boost  namespace checks


#endif //BOOST_CHECKS_MOD10_HPP
