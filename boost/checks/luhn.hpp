//  Boost checks/luhn.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_LUHN_INCLUDED
#define BOOST_CHECKS_LUHN_INCLUDED

#include <boost/checks/modulus10.hpp>

namespace boost {
    namespace checks{

typedef boost::checks::weight<1,2> luhn_weight ;
typedef boost::checks::rightmost luhn_sense ;

template <unsigned int number_of_virtual_value_skipped = 0>
struct luhn_algorithm : boost::checks::modulus10_algorithm < luhn_weight, luhn_sense, number_of_virtual_value_skipped>
{
  static void operate_on_valid_value( const int current_valid_value, const unsigned int valid_value_counter, int &checksum )
  {
    int current_weight = luhn_weight::weight_associated_with_pos( valid_value_counter + number_of_virtual_value_skipped ) ;
    checksum += (current_valid_value << (current_weight - 1)) - 9 * ( current_valid_value << (current_weight - 1) > 9) ;
  }
};

typedef luhn_algorithm<0> luhn_check_algorithm ;
typedef luhn_algorithm<1> luhn_compute_algorithm ;

template <size_t size_expected, typename check_range>
bool check_luhn (const check_range& check_seq)
{
  return boost::checks::check_sequence<luhn_check_algorithm, size_expected> ( check_seq ) ;
}

template <typename check_range>
bool check_luhn (const check_range& check_seq)
{
  return boost::checks::check_sequence<luhn_check_algorithm> ( check_seq ) ;
}

template <size_t size_expected, typename check_range>
typename boost::checks::luhn_compute_algorithm::checkdigit<check_range>::type compute_luhn (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<luhn_compute_algorithm, size_expected> ( check_seq ) ;
}

template <typename check_range>
typename boost::checks::luhn_compute_algorithm::checkdigit<check_range>::type compute_luhn (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<luhn_compute_algorithm> ( check_seq ) ;
}


}}
#endif // BOOST_CHECKS_LUHN_HPP
