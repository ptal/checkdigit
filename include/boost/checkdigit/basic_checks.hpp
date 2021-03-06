//  Boost checks/basic_checks.hpp header file
//  (C) Copyright Pierre Talbot 2011 - 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides a set of basic functions used to compute and validate check digit(s) and checksum.
*/

#ifndef BOOST_CHECKDIGIT_BASIC_HPP
#define BOOST_CHECKDIGIT_BASIC_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef> // size_t

#include <boost/checkdigit/detail/sequence_counter.hpp>
#include <boost/iterator/filter_iterator.hpp>

namespace boost {
  namespace checkdigit{

static const size_t bad_sequence = (size_t)-1;

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

template <typename processor,
          typename sizePolicy, 
          typename iterator,
          typename counter_iter>
size_t compute_checksum(iterator begin, iterator end, counter_iter &counter)
{
  processor process;
  size_t checksum = 0;
  for(; begin != end && sizePolicy::check(*counter); ++begin, ++counter)
    checksum = process(checksum, *begin, *counter);
  
  if(sizePolicy::overflow(*counter) || begin != end)
    return bad_sequence;
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
template <typename features,
          typename range>
bool check_sequence(const range &x)
{
  boost::checkdigit::detail::simple_counter::type counter = boost::checkdigit::detail::simple_counter()();
  size_t checksum;

  checksum = compute_checksum<typename features::checksum::processor,
                              typename features::size_policy>
                              (features::begin(x), features::end(x), counter);
  if(checksum == bad_sequence)
    return false;

  return chec
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
template <typename features,
          typename range>
size_t compute_checkdigit(const range &x)
{
  typedef typename boost::checkdigit::detail::skip_counter<features::checksum::checkdigit_detail::pos, 
                                                       features::checksum::checkdigit_detail::size
                                                      > counter_type;
  typename counter_type::type counter = counter_type()();

  size_t checksum;

  checksum = compute_checksum<typename features::checksum::processor,
                              typename features::size_policy>
                             (features::begin(x), features::end(x), counter);

  if(checksum == bad_sequence)
    return bad_sequence;
  return typename features::checksum::make_checkdigit()(checksum);
}

} // namespace checkdigit
} // namespace boost

#endif // BOOST_CHECKDIGIT_BASIC_HPP
