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

template <typename algorithm, typename size_contract, typename iterator>
int compute_checksum(const iterator &seq_begin, const iterator &seq_end )
{
  iterator seq_begin_cpy = iterator(seq_begin) ;
  unsigned int valid_value_counter = 0;
  int checksum = 0 ;
  while( seq_begin_cpy != seq_end )
  {
    try{
      int current_valid_value = algorithm::traduce_to_valid_value( *seq_begin_cpy, valid_value_counter );
      algorithm::operate_on_valid_value( current_valid_value, valid_value_counter, checksum ) ;
      ++valid_value_counter ;
    }catch( boost::checks::traduction_exception ){
    }
    ++seq_begin_cpy ;
  }
  size_contract::respect_size_contract( valid_value_counter );
  return checksum ;
}

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


}}
#endif // BOOST_CHECK_BASIC_HPP

