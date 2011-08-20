//  Boost checks/basic_checks.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file basic_checks.hpp
    \brief This file provides a set of basic functions used to compute and validate check digit(s) and checksum.
*/

#ifndef BOOST_CHECK_BASIC_HPP
#define BOOST_CHECK_BASIC_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/checks/limits.hpp>
#include <boost/lexical_cast.hpp>


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
template <typename algorithm, typename size_contract, typename iterator>
int compute_checksum(iterator seq_begin, iterator seq_end )
{
  unsigned int valid_value_counter = 0;
  int checksum = 0 ;
  for(; seq_begin != seq_end && !size_contract::reach_one_past_the_end(valid_value_counter) ; ++seq_begin )
  {
    try{
      int current_valid_value = algorithm::translate_to_valid_value( *seq_begin, valid_value_counter );
      algorithm::filter_valid_value_with_pos( current_valid_value, valid_value_counter ) ;
      algorithm::operate_on_valid_value( current_valid_value, valid_value_counter, checksum ) ;
      ++valid_value_counter ;
    }
    catch( boost::checks::translation_exception ){
    }
  }
  size_contract::respect_size_contract( valid_value_counter );
  return checksum ;
}

/*! 
    \brief Create iterators according to the algorithm::iterator policy. And call the iterator overload version of compute_checksum.
   
    \pre check_seq is a valid range.

    \tparam algorithm is a set of static method use to translate, filter and calculate or verify the checkdigit.
    \tparam size_contract is a contract concerning the size of the sequence.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws size_contract::exception_size_failure If the terms of the contract are not respected.

    \returns The checksum of the sequence calculated with algorithm.
*/

template <typename algorithm, typename size_contract, typename check_range>
int compute_checksum( const check_range &check_seq )
{
  algorithm::iteration_sense::iterator<check_range>::type begin = algorithm::iteration_sense::begin( check_seq );
  algorithm::iteration_sense::iterator<check_range>::type end = algorithm::iteration_sense::end( check_seq );

  return compute_checksum<algorithm, size_contract>( begin, end );
}

/*! 
    \brief Validate a sequence according to algorithm.

    \pre check_seq is a valid range.

    \tparam algorithm is a set of static method use to translate, filter and calculate or verify the checkdigit.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq contains no valid value.

    \returns True if the checkdigit is correct, false otherwise.
*/
template <typename algorithm, typename check_range>
bool check_sequence (const check_range& check_seq)
{
  int checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >( check_seq ) ;
  return algorithm::validate_checksum( checksum ) ;
}

/*! 
    \brief Validate a sequence according to algorithm.

    \pre check_seq is a valid range.\n size_expected > 0 (enforced by static assert).

    \tparam algorithm is a set of static method use to translate, filter and calculate or verify the checkdigit.
    \tparam size_expected is the number of valid value expected in the sequence.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.

    \returns True if the checkdigit is correct, false otherwise.
*/
template <typename algorithm, size_t size_expected, typename check_range>
bool check_sequence (const check_range& check_seq)
{
  int checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >( check_seq ) ;
  return algorithm::validate_checksum( checksum ) ;
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
template <typename algorithm, typename check_range>
typename algorithm::checkdigit<check_range>::type compute_checkdigit (const check_range& check_seq)
{
  int checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >( check_seq ) ;
  return algorithm::compute_checkdigit<typename algorithm::checkdigit<check_range>::type>( checksum ) ;
}

/*! 
    \brief Calculate the check digit of a sequence according to algorithm.

    \pre check_seq is a valid range.\n size_expected > 0 (enforced by static assert).

    \tparam algorithm is a set of static method use to translate, filter and calculate or verify the checkdigit.
    \tparam size_expected is the number of valid value expected in the sequence.
    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain size_expected valid values.

    \returns The check digit of the type of a value in check_seq.
*/
template <typename algorithm, size_t size_expected, typename check_range>
typename algorithm::checkdigit<check_range>::type compute_checkdigit (const check_range& check_seq)
{
  int checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >( check_seq ) ;
  return algorithm::compute_checkdigit<typename algorithm::checkdigit<check_range>::type>( checksum ) ;
}

/*!

    \brief Calculate the checkdigits of a sequence according to algorithm.

    \pre check_seq is a valid range.\n checkdigits is a valid initialized iterator and have enough reserved place to store the check digits. 

    \tparam algorithm is a set of static method use to translate, filter and calculate or verify the checkdigits.
    \tparam check_range is a valid range type.
    \tparam checkdigit_iterator must meet the OutputIterator requirements.
    \param check_seq is the sequence of value to check.
    \param checkdigits is the output iterator in which the check digits will be written.

    \throws std::invalid_argument if check_seq contains no valid value.

    \returns An iterator initialized at one pass the end of checkdigits.
*/
template <typename algorithm, typename check_range,  typename checkdigit_iterator>
typename checkdigit_iterator compute_multicheckdigit (const check_range& check_seq, checkdigit_iterator checkdigits)
{
  int checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >( check_seq ) ;
  return algorithm::compute_multicheckdigit( checksum, checkdigits ) ;
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
template <typename algorithm, size_t size_expected, typename check_range, typename checkdigit_iterator>
typename checkdigit_iterator compute_multicheckdigit (const check_range& check_seq,  checkdigit_iterator checkdigits)
{
  int checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >( check_seq ) ;
  return algorithm::compute_multicheckdigit( checksum, checkdigits ) ;
}

}}
#endif // BOOST_CHECK_BASIC_HPP

