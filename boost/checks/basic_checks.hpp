//  Boost checks/modulus.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECK_BASIC_HPP
#define BOOST_CHECK_BASIC_HPP

#ifdef _MSC_VER
    #pragma once
#endif // _MSC_VER

#include <boost/checks/limits.hpp>
#include <boost/lexical_cast.hpp>


namespace boost {
  namespace checks{

/*! \fn template <typename algorithm, typename size_contract, typename iterator>
        int compute_checksum(iterator seq_begin, iterator seq_end )

    \brief Run through a sequence and calculate the checksum with the algorithm policy class.

    \pre seq_begin and seq_end are valid iterators.

    \tparam algorithm is a set of static method use to traduce, filter and calculate the checksum.
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
      int current_valid_value = algorithm::traduce_to_valid_value( *seq_begin, valid_value_counter );
      algorithm::filter_valid_value_with_pos( current_valid_value, valid_value_counter ) ;
      algorithm::operate_on_valid_value( current_valid_value, valid_value_counter, checksum ) ;
      ++valid_value_counter ;
    }
    catch( boost::checks::traduction_exception ){
    }
  }
  size_contract::respect_size_contract( valid_value_counter );
  return checksum ;
}

/*! \fn template <typename algorithm, typename size_contract, typename check_range>
        int compute_checksum( const check_range &check_seq )

    \brief Create iterators according to the algorithm::iterator policy. And call the iterator overload version of compute_checksum.

    \pre seq_begin and seq_end are valid iterators.

    \tparam algorithm is a set of static method use to traduce, filter and calculate the checksum.
    \tparam size_contract is a contract concerning the size of the sequence.
    \tparam iterator Must meet the InputIterator requirements.
    \param seq_begin Beginning of the sequence.
    \param seq_end Ending of the sequence.

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

template <typename algorithm, typename check_range>
bool check_sequence (const check_range& check_seq)
{
  int checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >( check_seq ) ;
  return algorithm::validate_checksum( checksum ) ;
}

template <typename algorithm, size_t size_expected, typename check_range>
bool check_sequence (const check_range& check_seq)
{
  int checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >( check_seq ) ;
  return algorithm::validate_checksum( checksum ) ;
}

template <typename algorithm, typename check_range>
typename algorithm::checkdigit<check_range>::type compute_checkdigit (const check_range& check_seq)
{
  int checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >( check_seq ) ;
  return algorithm::compute_checkdigit<typename algorithm::checkdigit<check_range>::type>( checksum ) ;
}

template <typename algorithm, size_t size_expected, typename check_range>
typename algorithm::checkdigit<check_range>::type compute_checkdigit (const check_range& check_seq)
{
  int checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >( check_seq ) ;
  return algorithm::compute_checkdigit<typename algorithm::checkdigit<check_range>::type>( checksum ) ;
}


template <typename algorithm, typename check_range,  typename checkdigit_iterator>
typename checkdigit_iterator compute_multicheckdigit (const check_range& check_seq, checkdigit_iterator checkdigits)
{
  int checksum = compute_checksum<algorithm, boost::checks::no_null_size_contract<> >( check_seq ) ;
  return algorithm::compute_multicheckdigit( checksum, checkdigits ) ;
}

template <typename algorithm, size_t size_expected, typename check_range, typename checkdigit_iterator>
typename checkdigit_iterator compute_multicheckdigit (const check_range& check_seq,  checkdigit_iterator checkdigits)
{
  int checksum = compute_checksum<algorithm, boost::checks::strict_size_contract<size_expected> >( check_seq ) ;
  return algorithm::compute_multicheckdigit( checksum, checkdigits ) ;
}

}}
#endif // BOOST_CHECK_BASIC_HPP

