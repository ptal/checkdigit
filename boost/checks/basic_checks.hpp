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

#include <cstddef> // std::size_t

#include <boost/checks/translation_exception.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/checks/limits.hpp>

#include <boost/checks/detail/sequence_counter.hpp>

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
template <typename algorithm, 
          typename size_contract, 
          typename seq_iterator,
          typename counter_type>
std::size_t compute_checksum(seq_iterator seq_begin, seq_iterator seq_end, counter_type &counter)
{
  std::size_t checksum = 0;
  bool error = false;
  for(; seq_begin != seq_end && !error && !size_contract::reach_one_past_the_end(*counter); ++seq_begin)
  {
    try
    {
      if(!algorithm::skip(*seq_begin))
      {
        if(!algorithm::require(*seq_begin, *counter))
          error = true;
        else
        {
          std::size_t value = algorithm::convert(*seq_begin);
          checksum = algorithm::process(checksum, value, *counter);
          ++counter;
        }
       }
    }
    catch(boost::checks::translation_exception){
    }
  }
  if(error)
    throw std::invalid_argument("");
  size_contract::respect_size_contract(*counter);
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
template <typename algorithm, 
          typename seq_iterator>
bool check_sequence(seq_iterator seq_begin, seq_iterator seq_end)
{
  boost::checks::detail::simple_counter::type counter = boost::checks::detail::simple_counter()();
  std::size_t checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >(seq_begin, seq_end, counter);
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
template <typename algorithm, 
          std::size_t size_expected, 
          typename seq_iterator>
bool check_sequence(seq_iterator seq_begin, seq_iterator seq_end)
{
  boost::checks::detail::simple_counter::type counter = boost::checks::detail::simple_counter()();
  std::size_t checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >(seq_begin, seq_end, counter); 
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
template <typename algorithm, 
          std::size_t checkdigit_pos, 
          std::size_t checkdigit_size, 
          typename seq_iterator>
typename seq_iterator::value_type compute_checkdigit(seq_iterator seq_begin, seq_iterator seq_end)
{
  typename boost::checks::detail::skip_counter<checkdigit_pos, checkdigit_size>::type counter = boost::checks::detail::skip_counter<checkdigit_pos, checkdigit_size>()();
  std::size_t checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >(seq_begin, seq_end, counter);
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
template <typename algorithm, 
          std::size_t size_expected, 
          std::size_t checkdigit_pos, 
          std::size_t checkdigit_size, 
          typename seq_iterator> 
typename seq_iterator::value_type compute_checkdigit(seq_iterator seq_begin, seq_iterator seq_end)
{
  typename boost::checks::detail::skip_counter<checkdigit_pos, checkdigit_size>::type counter = boost::checks::detail::skip_counter<checkdigit_pos, checkdigit_size>()();
  std::size_t checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >(seq_begin, seq_end, counter);
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
template <typename algorithm, 
          std::size_t checkdigit_pos,
          std::size_t checkdigit_size,
          typename seq_iterator, 
          typename checkdigit_iterator> 
checkdigit_iterator compute_multicheckdigit (seq_iterator seq_begin, seq_iterator seq_end, checkdigit_iterator checkdigits)
{
  typename boost::checks::detail::skip_counter<checkdigit_pos, checkdigit_size>::type counter = boost::checks::detail::skip_counter<checkdigit_pos, checkdigit_size>()();
  std::size_t checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >(seq_begin, seq_end, counter);
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
template <typename algorithm, 
          std::size_t size_expected, 
          std::size_t checkdigit_pos, 
          std::size_t checkdigit_size, 
          typename seq_iterator, 
          typename checkdigit_iterator>
checkdigit_iterator compute_multicheckdigit (seq_iterator seq_begin, seq_iterator seq_end, checkdigit_iterator checkdigits)
{
  typename boost::checks::detail::skip_counter<checkdigit_pos, checkdigit_size>::type counter = boost::checks::detail::skip_counter<checkdigit_pos, checkdigit_size>()();
  std::size_t checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >(seq_begin, seq_end, counter);
  return algorithm::compute_multicheckdigit(checksum, checkdigits);
}

} // namespace checks
} // namespace boost

#endif // BOOST_CHECK_BASIC_HPP
