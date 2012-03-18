//  Boost checks/modulus97.hpp header file

//  (C) Copyright Pierre Talbot 2011 - 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate the classic modulus 97 checksum. It provides functions for convenience with the mod97-10 algorithm (ISO/IEC 7064:2003).
*/

#ifndef BOOST_CHECKS_MOD97_HPP
#define BOOST_CHECKS_MOD97_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/preprocessor/repetition.hpp>
#include <boost/checks/weight.hpp>
#include <boost/checks/weighted_sum.hpp>
#include <boost/checks/checksum.hpp> 

namespace boost{
  namespace checks{

/*! \class modulus97_algorithm
    \brief This class can be used to compute or validate a checksum with a basic modulus 97.

    \details  The mod97-10 algorithm (ISO/IEC 7064:2003 Information technology -- Security techniques -- Check character systems) uses two check digits.

    \tparam mod97_weight must meet the weight concept requirements.
    \tparam iteration_sense must meet the iteration_sense concept requirements.
    \tparam checkdigit_size Help functions to provide same behavior on sequence with and without check digits. No "real" value in the sequence will be skipped.

    \remarks This algorithm use two check digits.
*/
  /*!
    \brief Validate a checksum with a simple modulus 97.

    \param checksum is the checksum to validate.

    \returns @c true if the checksum is correct, @c false otherwise.
  */
struct mod97_validation
{
  bool operator()(std::size_t checksum)
  {
    return checksum % 97 == 1;
  }
};
  /*!
    \brief Compute the two check digits with a simple modulus 97.

    \pre checkdigits should have enough reserved place to store the two check digits.
    \post The two check digits are stored into checkdigits.

    \tparam checkdigits_iter must meet the OutputIterator requirements.
    \param checksum is the checksum used to extract the check digit.
    \param checkdigits is the output iterator in which the two check digits will be written.

    \throws translation_exception if the check digits cannot be translated into the check digits_iter type.

    \returns An iterator initialized at one pass to the end of the two check digits.
  */
struct mod97_checkdigit
{
  std::size_t operator()(std::size_t checksum)
  {
    return 98 - (checksum % 97);
  }
};

typedef checkdigit<0, 2> mod97_10_checkdigit;

struct mod97_10_processor
{
  unsigned char weight;
  
  mod97_10_processor() : weight(10) 
  {
  } 

  std::size_t operator()(std::size_t checksum, std::size_t value, std::size_t pos)
  {
    if(pos == 0)
      weight = 1;
    else
      weight = weight * 10 % 97;
    return checksum + value * weight;
  }
};

typedef checksum
<
  mod97_10_processor,
  mod97_validation,
  mod97_checkdigit,
  mod97_10_checkdigit
> mod97_10; 

/*!
    \brief Validate a sequence according to the mod97_10_check_algorithm type.

    \pre check_seq is a valid range.\n size_expected > 0 (enforced by static assert).

    \tparam size_expected is the number of valid value expected in the sequence.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.

    \returns True if the two check digits are correct, false otherwise.
*/
template <size_t size_expected, typename check_range>
bool check_mod97_10 (const check_range& check_seq)
{
  return check_sequence<features<mod97_10, size_expected> >(check_seq);
}

/*!
    \brief Validate a sequence according to the mod97_10_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.

    \returns @c true if the two check digits are correct, @c false otherwise.
*/
template <typename check_range>
bool check_mod97_10(const check_range& check_seq)
{
  return check_sequence<features<mod97_10> >(check_seq);
}

/*!
    \brief Calculate the check digits of a sequence according to the mod97_10_compute_algorithm type.

    \pre check_seq is a valid range.\n size_expected > 0 (enforced by static assert).\n mod97_checkdigits should have enough reserved place to store the two check digits.

    \tparam size_expected is the number of valid value expected in the sequence. (So the check digits are not included.)
    \tparam check_range is a valid range type.
    \tparam checkdigits_iter must meet the OutputIterator requirements.
    \param check_seq is the sequence of value to check.
    \param mod97_checkdigits is the OutputIterator in which the two check digits will be stored.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.
    \throws translation_exception if the check digits cannot be translated into the checkdigits_iter type.

    \returns The check digits are stored into mod97_checkdigits. The range of these is [0..9][0..9].
*/
template <size_t size_expected, typename check_range>
std::size_t compute_mod97_10(const check_range& check_seq)
{
  return compute_checkdigit<features<mod97_10, size_expected> >(check_seq);
}

/*!
    \brief Calculate the check digits of a sequence according to the mod97_10_compute_algorithm type.

    \pre check_seq is a valid range.\n mod97_checkdigits should have enough reserved place to store the two check digits.

    \tparam check_range is a valid range type.
    \tparam checkdigits_iter must meet the OutputIterator requirements.
    \param check_seq is the sequence of value to check.
    \param mod97_checkdigits is the OutputIterator in which the two check digits will be stored.

    \throws std::invalid_argument if check_seq contains no valid value.
    \throws translation_exception if the check digits cannot be translated into the checkdigits_iter type.

    \returns The check digits are stored into mod97_checkdigits. The range of these is [0..9][0..9].
*/
template <typename check_range>
std::size_t compute_mod97_10(const check_range& check_seq)
{
  return compute_checkdigit<features<mod97_10> >(check_seq); 
}


}} // namespace boost   namespace checks

#endif //BOOST_CHECKS_MOD97_HPP
