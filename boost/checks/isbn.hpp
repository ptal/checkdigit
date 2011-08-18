//  Boost checks/isbn.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.


#ifndef BOOST_CHECKS_ISBN_HPP
#define BOOST_CHECKS_ISBN_HPP

#include <boost/checks/ean.hpp>
#include <boost/checks/modulus11.hpp>

#define ISBN10_SIZE 10
#define ISBN10_SIZE_WITHOUT_CHECKDIGIT 9

namespace boost {
    namespace checks{

// ISBN-13

template <unsigned int number_of_virtual_value_skipped = 0>
struct isbn13_algorithm : boost::checks::modulus10_algorithm < boost::checks::ean_weight, boost::checks::ean_sense, number_of_virtual_value_skipped >
{
  static void filter_valid_value_with_pos(const unsigned int current_valid_value, const unsigned int current_value_position )
  {
    const unsigned int real_pos_from_left = EAN13_SIZE - current_value_position - number_of_virtual_value_skipped ;

    if( real_pos_from_left == 1 && current_valid_value != 9)
      throw std::invalid_argument("The first digit should be 9.") ;
    else if( real_pos_from_left == 2 && current_valid_value != 7)
      throw std::invalid_argument("The second digit should be 7.") ;
    else if( real_pos_from_left == 3 && current_valid_value != 8 && current_valid_value != 9)
      throw std::invalid_argument("The third digit should be 8 or 9.") ;
  } 
};

typedef boost::checks::isbn13_algorithm<0> isbn13_check_algorithm ;
typedef boost::checks::isbn13_algorithm<1> isbn13_compute_algorithm ;

template <typename check_range>
bool check_isbn13 (const check_range& check_seq)
{
  return boost::checks::check_sequence<isbn13_check_algorithm, EAN13_SIZE> ( check_seq ) ;
}

template <typename check_range>
typename boost::checks::isbn13_compute_algorithm::checkdigit<check_range>::type compute_isbn13 (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<isbn13_compute_algorithm, EAN13_SIZE_WITHOUT_CHECKDIGIT> ( check_seq ) ;
}


// ISBN-10

template <typename check_range>
bool check_isbn10 (const check_range& check_seq)
{
  return boost::checks::check_modulus11< ISBN10_SIZE >( check_seq );
}

template <typename check_range>
typename boost::checks::mod11_compute_algorithm::checkdigit<check_range>::type compute_isbn10 (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<ISBN10_SIZE_WITHOUT_CHECKDIGIT> ( check_seq ) ;
}


}}
#endif // BOOST_CHECKS_ISBN_HPP
