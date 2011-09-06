// vin.hpp
//! \file
//! \brief Check and compute the Vehicle Identification Number.
//! This is an example of extending the library for a new checksum type.

// Copyright Pierre Talbot 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CHECKS_VIN_HPP
#define BOOST_CHECKS_VIN_HPP

//[vin_preprocessor_tools
#include <boost/checks/modulus11.hpp>
#include <boost/checks/basic_checks.hpp>

#define VIN_SIZE 17
#define VIN_SIZE_WITHOUT_CHECKDIGIT 16
#define VIN_CHECKDIGIT_POS 8

typedef boost::checks::weight<2,3,4,5,6,7,8,9,10> vin_weight ;
typedef boost::checks::rightmost vin_sense ;
//]

//[vin_struct_header
template <unsigned int number_of_virtual_value_skipped = 0>
struct vin_algorithm : boost::checks::modulus11_algorithm<vin_weight, vin_sense, number_of_virtual_value_skipped>
//]
{
  //[vin_translation_module
  template <typename value>
  static int translate_to_valid_value(const value &current_value, const unsigned int valid_value_counter )
  {
    int valid_value = 0;
    try
    {
      valid_value = boost::lexical_cast<int>( current_value ) ;
    }
    catch( boost::bad_lexical_cast )
    {
      // Transform the value to be between 1 and 26.
      if( current_value >= 'a' && current_value <= 'z' )
        valid_value = current_value - 'a' + 1 ;
      else if( current_value >= 'A' && current_value <= 'Z' )
        valid_value = current_value - 'A' + 1 ;
      else
        throw boost::checks::translation_exception() ;

      if ( valid_value == 9 || valid_value == 15 || valid_value == 17)
        throw std::invalid_argument( "The letter I, O and Q are not allowed." );

      if ( valid_value_counter == VIN_CHECKDIGIT_POS && number_of_virtual_value_skipped == 0)
      {
        if ( valid_value != 24 )
          throw std::invalid_argument( "The check digit should be a digit or X or x." );
        else
          valid_value = 10 ;
        valid_value = 11 - valid_value ;
      }
      else
        valid_value = valid_value % 10 + valid_value / 10 + (valid_value > 18) ;
    }
    if( valid_value > 10)
      throw boost::checks::translation_exception() ;

    return valid_value ;
  }
  //]

  //[vin_operation_module
  static void operate_on_valid_value( const int current_valid_value, const unsigned int valid_value_counter, int &checksum )
  {
    if( number_of_virtual_value_skipped == 0 && valid_value_counter == VIN_CHECKDIGIT_POS )
      checksum += current_valid_value ;
    else
    {
      unsigned int weight_position = valid_value_counter - (number_of_virtual_value_skipped == 0 && valid_value_counter > VIN_CHECKDIGIT_POS) ;
      int current_weight = vin_weight::weight_associated_with_pos( weight_position ) ;
      checksum += current_valid_value * current_weight ;
    }
  }
  //]

  //[vin_compute_checkdigit
  template <typename checkdigit>
  static typename checkdigit compute_checkdigit( int checksum )
  {
    typedef typename boost::checks::modulus11_algorithm<vin_weight, vin_sense, number_of_virtual_value_skipped> mod11 ;
    return mod11::translate_checkdigit<checkdigit>(checksum % 11) ;
  }
  //]
};

//[vin_preprocessor_algorithm
typedef vin_algorithm <0> vin_check_algorithm ;
typedef vin_algorithm <1> vin_compute_algorithm ;
//]

//[vin_functions
template <typename check_range>
bool check_vin (const check_range& check_seq)
{
  return boost::checks::check_sequence<vin_check_algorithm, VIN_SIZE> ( check_seq ) ;
}

template <typename check_range>
typename vin_compute_algorithm::checkdigit<check_range>::type compute_vin (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<vin_compute_algorithm, VIN_SIZE_WITHOUT_CHECKDIGIT> ( check_seq ) ;
}
//]


#endif
