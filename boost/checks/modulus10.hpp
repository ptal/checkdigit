//  Boost checks/modulus10.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_MOD10_HPP
#define BOOST_CHECKS_MOD10_HPP

#include <boost/lexical_cast.hpp>
#include <boost/checks/traduction_exception.hpp>

namespace boost{
  namespace checks{

template <typename mod10_weight, unsigned int number_of_virtual_value_skipped = 0>
struct modulus10_algorithm
{
  template <typename value>
  static unsigned int traduce_to_valid_value(const value &current_value, const unsigned int valid_value_counter )
  {
    unsigned int valid_value = 0;
    try{
      valid_value = boost::lexical_cast<unsigned int>( current_value ) ;
    }catch( boost::bad_lexical_cast ){
      throw traduction_exception() ;
    }
    return valid_value ;
  }

  static void operate_on_valid_value( const int current_valid_value, const unsigned int valid_value_counter, int &checksum )
  {
    int current_weight = mod10_weight::weight_associated_with_pos( valid_value_counter + number_of_virtual_value_skipped )
    checksum += current_valid_value * current_weight ;
  }

};

}}

#endif //BOOST_CHECKS_MOD10_HPP