//  Boost checks/basic_checks.hpp header file
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides a set of basic functions used to compute and validate check digit(s) and checksum.
*/

#ifndef BOOST_CHECK_BASIC_HPP
#define BOOST_CHECK_BASIC_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/lexical_cast.hpp>
#include <boost/checks/limits.hpp>

namespace boost {
  namespace checks{

/*!
    \brief Run through a sequence and calculate the checksum with the algorithm policy class.

    \pre seq_begin and seq_end are valid iterators.

    \tparam algorithm is a set of static method use to translate, filter and calculate or verify the checksum.
    \tparam size_contract is a contract concerning the size of the sequence.
    \tparam iterator Must meet the InputIterator requirements.
    \param seq_begin Beginning of the sequence.
    \param seq_end Ending of the sequence.

    \throws size_contract::exception_size_failure If the terms of the contract are not respected.

    \returns The checksum of the sequence calculated with algorithm.
  */
template <typename algorithm, typename size_contract, typename seq_iterator>
int compute_checksum(seq_iterator seq_begin, seq_iterator seq_end)
{
  unsigned int valid_value_counter = 0;
  int checksum = 0;
  for(; seq_begin != seq_end && !size_contract::reach_one_past_the_end(valid_value_counter); ++seq_begin)
  {
    try
    {
      int current_valid_value = algorithm::translate_to_valid_value(*seq_begin);
      algorithm::filter_valid_value_with_pos(current_valid_value, valid_value_counter);
      algorithm::operate_on_valid_value(current_valid_value, valid_value_counter, checksum);
      ++valid_value_counter;
    }
    catch(boost::checks::translation_exception){
    }
  }
  size_contract::respect_size_contract(valid_value_counter);
  return checksum;
}

/*!
    \brief Validate a sequence according to algorithm.

    \pre check_seq is a valid range.

    \tparam algorithm is a set of static method use to translate, filter and calculate or verify the checkdigit.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.

    \returns @c true if the checkdigit is correct, @c false otherwise.
*/
template <typename algorithm, typename seq_iterator>
bool check_sequence(seq_iterator seq_begin, seq_iterator seq_end)
{
  int checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >(seq_begin, seq_end);
  return algorithm::validate_checksum(checksum);
}

/*!
    \brief Validate a sequence according to algorithm.

    \pre check_seq is a valid range.\n size_expected > 0 (enforced by static assert).

    \tparam algorithm is a set of static method use to translate, filter and calculate or verify the checkdigit.
    \tparam size_expected is the number of valid value expected in the sequence.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.

    \returns @c true if the checkdigit is correct, @c false otherwise.
*/
template <typename algorithm, size_t size_expected, typename seq_iterator>
bool check_sequence(seq_iterator seq_begin, seq_iterator seq_end)
{
  int checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >(seq_begin, seq_end); 
  return algorithm::validate_checksum(checksum);
}

/*!
    \brief Calculate the check digit of a sequence according to algorithm.

    \pre check_seq is a valid range.

    \tparam algorithm is a set of static method use to translate, filter and calculate or verify the checkdigit.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.

    \returns The check digit of the type of a value in check_seq.
*/
template <typename algorithm, typename seq_iterator>
typename seq_iterator::value_type compute_checkdigit(seq_iterator seq_begin, seq_iterator seq_end)
{
  int checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >(seq_begin, seq_end);
  return algorithm::template compute_checkdigit<typename seq_iterator::value_type>(checksum);
}

/*!
    \brief Calculate the check digit of a sequence according to algorithm.

    \pre check_seq is a valid range.\n size_expected > 0 (enforced by static assert).

    \tparam algorithm is a set of static methods used to translate, filter and calculate or verify the checkdigit.
    \tparam size_expected is the number of valid value expected in the sequence.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.

    \returns The check digit of the type of a value in check_seq.
*/
template <typename algorithm, size_t size_expected, typename seq_iterator>
typename seq_iterator::value_type compute_checkdigit(seq_iterator seq_begin, seq_iterator seq_end)
{
  int checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >(seq_begin, seq_end);
  return algorithm::template compute_checkdigit<typename seq_iterator::value_type>(checksum);
}

/*!

    \brief Calculate the checkdigits of a sequence according to algorithm.

    \pre check_seq is a valid range.\n checkdigits is a valid initialized iterator and have enough reserved place to store the check digits.

    \tparam algorithm is a set of static methods used to translate, filter and calculate or verify the checkdigits.
    \tparam check_range is a valid range type.
    \tparam checkdigit_iterator must meet the OutputIterator requirements.
    \param check_seq is the sequence of value to check.
    \param checkdigits is the output iterator in which the check digits will be written.

    \throws std::invalid_argument if check_seq contains no valid value.

    \returns An iterator initialized at one pass the end of checkdigits.
*/
template <typename algorithm, typename seq_iterator, typename checkdigit_iterator>
checkdigit_iterator compute_multicheckdigit (seq_iterator seq_begin, seq_iterator seq_end, checkdigit_iterator checkdigits)
{
  int checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >(seq_begin, seq_end);
  return algorithm::compute_multicheckdigit(checksum, checkdigits);
}

/*!
    \brief Calculate the checkdigits of a sequence according to algorithm.

    \pre check_seq is a valid range.\n checkdigits is a valid initialized iterator and have enough reserved place to store the check digits.\n size_expected > 0 (enforced by static assert).

    \tparam algorithm is a set of static method use to translate, filter and calculate or verify the checkdigits.
    \tparam size_expected is the number of valid value expected in the sequence.
    \tparam check_range is a valid range type.
    \tparam checkdigit_iterator must meet the OutputIterator requirements.
    \param check_seq is the sequence of value to check.
    \param checkdigits is the output iterator in which the check digits will be written.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.

    \returns An iterator initialized at one pass the end of checkdigits.
*/
template <typename algorithm, size_t size_expected, typename seq_iterator, typename checkdigit_iterator>
checkdigit_iterator compute_multicheckdigit (seq_iterator seq_begin, seq_iterator seq_end, checkdigit_iterator checkdigits)
{
  int checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >(seq_begin, seq_end);
  return algorithm::compute_multicheckdigit(checksum, checkdigits);
}

} // namespace checks
} // namespace boost

#endif // BOOST_CHECK_BASIC_HPP
