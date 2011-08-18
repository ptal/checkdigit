//  Boost checks/mastercard.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_MASTERCARD_HPP
#define BOOST_CHECKS_MASTERCARD_HPP

#include <boost/checks/luhn.hpp>

#define MASTERCARD_SIZE 16
#define MASTERCARD_SIZE_WITHOUT_CHECKDIGIT 15

namespace boost {
    namespace checks{


template <unsigned int number_of_virtual_value_skipped = 0>
struct mastercard_algorithm : boost::checks::luhn_algorithm < number_of_virtual_value_skipped >
{
  static void filter_valid_value_with_pos(const unsigned int current_valid_value, const unsigned int current_value_position )
  {
    const unsigned int real_pos_from_left = MASTERCARD_SIZE - current_value_position - number_of_virtual_value_skipped ;

    if( real_pos_from_left == 1 && current_valid_value != 5)
      throw std::invalid_argument("The Major Industry Identifier of a Mastercard should be 5.") ;
    else if( real_pos_from_left == 2 && (current_valid_value == 0 || current_valid_value > 5) ) 
      throw std::invalid_argument("The Issuer Identification Number of an American Express should be between 51 and 55." ) ;
  }
};

typedef mastercard_algorithm<0> mastercard_check_algorithm ;
typedef mastercard_algorithm<1> mastercard_compute_algorithm ;

template <typename check_range>
bool check_mastercard (const check_range& check_seq)
{
  return boost::checks::check_sequence<mastercard_check_algorithm, MASTERCARD_SIZE> ( check_seq ) ;
}

template <typename check_range>
typename boost::checks::mastercard_compute_algorithm::checkdigit<check_range>::type compute_mastercard (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<mastercard_compute_algorithm, MASTERCARD_SIZE_WITHOUT_CHECKDIGIT> ( check_seq ) ;
}


}}
#endif // BOOST_CHECKS_MASTERCARD_HPP

