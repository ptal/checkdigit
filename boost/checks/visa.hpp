//  Boost checks/visa.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_VISA_HPP
#define BOOST_CHECKS_VISA_HPP

#include <boost/checks/luhn.hpp>

#define VISA_SIZE 16
#define VISA_SIZE_WITHOUT_CHECKDIGIT 15

namespace boost {
    namespace checks{


template <unsigned int number_of_virtual_value_skipped = 0>
struct visa_algorithm : boost::checks::luhn_algorithm < number_of_virtual_value_skipped >
{
  static void filter_valid_value_with_pos(const unsigned int current_valid_value, const unsigned int current_value_position )
  {
    const unsigned int real_pos_from_left = VISA_SIZE - current_value_position - number_of_virtual_value_skipped ;

    if( real_pos_from_left == 1 && current_valid_value != 4)
      throw std::invalid_argument("The Major Industry Identifier of a VISA credit card should be 4.") ;
  } 
};

typedef visa_algorithm<0> visa_check_algorithm ;
typedef visa_algorithm<1> visa_compute_algorithm ;

template <typename check_range>
bool check_visa (const check_range& check_seq)
{
  return boost::checks::check_sequence<visa_check_algorithm, VISA_SIZE> ( check_seq ) ;
}

template <typename check_range>
typename boost::checks::visa_compute_algorithm::checkdigit<check_range>::type compute_visa (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<visa_compute_algorithm, VISA_SIZE_WITHOUT_CHECKDIGIT> ( check_seq ) ;
}


}}
#endif // BOOST_CHECKS_VISA_HPP
