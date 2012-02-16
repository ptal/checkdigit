//  Boost checks/basic_checks.hpp header file
//  (C) Copyright Pierre Talbot 2011 - 2012
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

#include <boost/checks/detail/sequence_counter.hpp>
#include <boost/iterator/filter_iterator.hpp>

namespace boost {
  namespace checks{

struct no_prechecksum_tag {};

static const std::size_t bad_sequence = (std::size_t)-1;

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

// Use bind and boost::ref instead ? But how to deduce type ?
template <typename Iterator>
struct deref
{
  Iterator &iter;
  deref(Iterator &iter) : iter(iter) { }

  std::size_t operator()() const
  {
    return *iter;
  }
};

template <typename algorithm, 
          std::size_t size_expected, 
          typename seq_iterator,
          typename counter_iter>
std::size_t compute_checksum(seq_iterator seq_begin, seq_iterator seq_end, counter_iter &counter)
{
  typedef typename algorithm::template processor<deref<counter_iter> > processor;
  processor process = processor(deref<counter_iter>(counter));

  std::size_t checksum = 0;
  for(; seq_begin != seq_end && *counter < size_expected; ++seq_begin, ++counter)
    checksum = process(checksum, *seq_begin);
  
  if(*counter != size_expected || seq_begin != seq_end)
    return bad_sequence;
  return checksum;
}

template <typename algorithm, 
          typename seq_iterator,
          typename counter_iter>
std::size_t compute_checksum(seq_iterator seq_begin, seq_iterator seq_end, counter_iter &counter)
{
  typedef typename algorithm::template processor<deref<counter_iter> > processor;
  processor process = processor(deref<counter_iter>(counter));
  
  std::size_t checksum = 0; 
  for(; seq_begin != seq_end; ++seq_begin, ++counter)
    checksum = process(checksum, *seq_begin);
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
          typename prechecksum_type, 
          typename seq_iterator>
bool check_sequence(seq_iterator seq_begin, seq_iterator seq_end)
{
  boost::checks::detail::simple_counter::type counter = boost::checks::detail::simple_counter()();
 
  prechecksum_type prechecksum; 
  std::size_t checksum = compute_checksum<algorithm>(prechecksum(seq_begin, seq_end), 
                                                     prechecksum(seq_end, seq_end), 
                                                     counter);
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
          typename prechecksum_type, 
          std::size_t size_expected, 
          typename seq_iterator>
bool check_sequence(seq_iterator seq_begin, seq_iterator seq_end)
{
  boost::checks::detail::simple_counter::type counter = boost::checks::detail::simple_counter()();
  
  prechecksum_type prechecksum;
  std::size_t checksum = compute_checksum<algorithm, size_expected>(prechecksum(seq_begin, seq_end), 
                                                                    prechecksum(seq_end, seq_end), 
                                                                    counter); 
  if(checksum != bad_sequence)
    return algorithm::validate_checksum(checksum);
  return false;
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
          typename prechecksum_type,
          typename checkdigit, 
          typename seq_iterator>
std::size_t compute_checkdigit(seq_iterator seq_begin, seq_iterator seq_end)
{
  typedef typename boost::checks::detail::skip_counter<checkdigit::pos, checkdigit::size> counter_type;
  typename counter_type::type counter = counter_type()();
  prechecksum_type prechecksum;
  std::size_t checksum = compute_checksum<algorithm>(prechecksum(seq_begin, seq_end), 
                                                     prechecksum(seq_end, seq_end),
                                                     counter);
  return algorithm::compute_checkdigit(checksum);
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
          typename prechecksum_type, 
          std::size_t size_expected, 
          typename checkdigit, 
          typename seq_iterator> 
std::size_t compute_checkdigit(seq_iterator seq_begin, seq_iterator seq_end)
{
  typedef typename boost::checks::detail::skip_counter<checkdigit::pos, checkdigit::size> counter_type;
  typename counter_type::type counter = counter_type()();
  prechecksum_type prechecksum;
  std::size_t checksum = compute_checksum<algorithm, size_expected>(prechecksum(seq_begin, seq_end), 
                                                                    prechecksum(seq_end, seq_end),
                                                                    counter);
  if(checksum != size_expected)
    return algorithm::compute_checkdigit(checksum);
  return bad_sequence;
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
          typename prechecksum_type, 
          typename checkdigit,
          typename seq_iterator> 
std::pair<std::size_t, std::size_t> compute_multicheckdigit (seq_iterator seq_begin, seq_iterator seq_end)
{
  typedef typename boost::checks::detail::skip_counter<checkdigit::pos, checkdigit::size> counter_type;
  typename counter_type::type counter = counter_type()();
  prechecksum_type prechecksum;
  std::size_t checksum = compute_checksum<algorithm>(prechecksum(seq_begin, seq_end), 
                                                     prechecksum(seq_end, seq_end),
                                                     counter);
  return algorithm::compute_multicheckdigit(checksum);
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
          typename prechecksum_type, 
          std::size_t size_expected, 
          typename checkdigit, 
          typename seq_iterator>
std::pair<std::size_t, std::size_t> compute_multicheckdigit(seq_iterator seq_begin, seq_iterator seq_end)
{
  typedef typename boost::checks::detail::skip_counter<checkdigit::pos, checkdigit::size> counter_type;
  typename counter_type::type counter = counter_type()();
  prechecksum_type prechecksum;
  std::size_t checksum = compute_checksum<algorithm, size_expected>(prechecksum(seq_begin, seq_end), 
                                                                    prechecksum(seq_end, seq_end),
                                                                    counter);
  if(checksum != bad_sequence)
    return algorithm::compute_multicheckdigit(checksum);
  return std::pair<std::size_t, std::size_t>(bad_sequence, bad_sequence);
}

} // namespace checks
} // namespace boost

#endif // BOOST_CHECK_BASIC_HPP
