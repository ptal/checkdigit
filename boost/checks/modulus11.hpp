//  Boost checks/modulus11.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_MOD11_HPP
#define BOOST_CHECKS_MOD11_HPP

#include <boost/lexical_cast.hpp>
#include <boost/checks/traduction_exception.hpp>
#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/basic_checks.hpp>

namespace boost{
  namespace checks{

template <typename mod11_weight, typename iteration_sense, unsigned int number_of_virtual_value_skipped = 0>
struct modulus11_algorithm
{
  typedef iteration_sense iteration_sense ;

  template <typename value>
  static int traduce_to_valid_value(const value &current_value, const unsigned int valid_value_counter )
  {    
    int valid_value = 0;
    try
    {
      valid_value = boost::lexical_cast<int>( current_value ) ;
    }
    catch( boost::bad_lexical_cast )
    {
      if( current_value == 'x' || current_value == 'X' )
        valid_value = 10 ;
      else
        throw boost::checks::traduction_exception() ;
    }
    return valid_value ;
  }

  static void operate_on_valid_value( const int current_valid_value, const unsigned int valid_value_counter, int &checksum )
  {
    int current_weight = mod11_weight::weight_associated_with_pos( valid_value_counter + number_of_virtual_value_skipped ) ;
    checksum += current_valid_value * current_weight ;
  }

  static bool validate_checksum(int checksum)
  {
    return !(checksum % 11) ;
  }

  template <typename checkdigit>
  static typename checkdigit compute_checkdigit( int checksum )
  {
   try
   {
      return boost::lexical_cast<checkdigit>((11 - checksum % 11) %11) ;
   }
   catch( boost::bad_lexical_cast )
   {
      try
      {
        return boost::lexical_cast<checkdigit>('X') ;
      }
      catch( boost::bad_lexical_cast )
      {
        throw boost::checks::traduction_exception() ; 
      }
    }
  }

  template <typename check_range>
  struct checkdigit
  {
    typedef typename boost::range_value<check_range>::type type;
  };
};

typedef boost::checks::weight<1,2,3,4,5,6,7,8,9,10> mod11_weight ;
typedef boost::checks::rightmost mod11_sense ;

typedef modulus11_algorithm<mod11_weight, mod11_sense, 0> mod11_check_algorithm ;
typedef modulus11_algorithm<mod11_weight, mod11_sense, 1> mod11_compute_algorithm ;

template <size_t size_expected, typename check_range>
bool check_modulus11 (const check_range& check_seq)
{
  return boost::checks::check_sequence<mod11_check_algorithm, size_expected> ( check_seq ) ;
}

template <typename check_range>
bool check_modulus11 (const check_range& check_seq)
{
  return boost::checks::check_sequence<mod11_check_algorithm> ( check_seq ) ;
}

template <size_t size_expected, typename check_range>
typename boost::checks::mod11_compute_algorithm::checkdigit<check_range>::type compute_modulus11 (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<mod11_compute_algorithm, size_expected> ( check_seq ) ;
}

template <typename check_range>
typename boost::checks::mod11_compute_algorithm::checkdigit<check_range>::type compute_modulus11 (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<mod11_compute_algorithm> ( check_seq ) ;
}

}}

#endif //BOOST_CHECKS_MOD10_HPP