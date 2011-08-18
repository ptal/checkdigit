//  Boost checks/amex.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

// American express.

#ifndef BOOST_CHECKS_AMEX_HPP
#define BOOST_CHECKS_AMEX_HPP

#include <boost/checks/luhn.hpp>

#define AMEX_SIZE 15
#define AMEX_SIZE_WITHOUT_CHECKDIGIT 14

namespace boost {
    namespace checks{

template <unsigned int number_of_virtual_value_skipped = 0>
struct amex_algorithm : boost::checks::luhn_algorithm < number_of_virtual_value_skipped >
{
  static void filter_valid_value_with_pos(const unsigned int current_valid_value, const unsigned int current_value_position )
  {
    const unsigned int real_pos_from_left = AMEX_SIZE - current_value_position - number_of_virtual_value_skipped ;

    if( real_pos_from_left == 1 && current_valid_value != 3)
      throw std::invalid_argument("The Major Industry Identifier of an American Express should be 3.") ;
    else if( real_pos_from_left == 2 && current_valid_value != 4 && current_valid_value != 7 ) 
      throw std::invalid_argument("The Issuer Identification Number of an American Express should be 34 or 37." ) ;
  }
};

typedef amex_algorithm<0> amex_check_algorithm ;
typedef amex_algorithm<1> amex_compute_algorithm ;

template <typename check_range>
bool check_amex (const check_range& check_seq)
{
  return boost::checks::check_sequence<amex_check_algorithm, AMEX_SIZE> ( check_seq ) ;
}

template <typename check_range>
typename boost::checks::amex_compute_algorithm::checkdigit<check_range>::type compute_amex (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<amex_compute_algorithm, AMEX_SIZE_WITHOUT_CHECKDIGIT> ( check_seq ) ;
}


}}
#endif
