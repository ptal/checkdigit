//  Boost checks/ean.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

// European Article Numbering 13 and 8.

#ifndef BOOST_CHECKS_EAN_HPP
#define BOOST_CHECKS_EAN_HPP

#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/basic_checks.hpp>
#include <boost/checks/modulus10.hpp>

#define EAN13_SIZE 13
#define EAN13_SIZE_WITHOUT_CHECKDIGIT 12
#define EAN8_SIZE 8 
#define EAN8_SIZE_WITHOUT_CHECKDIGIT 7

namespace boost {
    namespace checks{

typedef boost::checks::weight<1,3> ean_weight ;
typedef boost::checks::rightmost ean_sense ;

typedef boost::checks::modulus10_algorithm< ean_weight, ean_sense, 0> ean_check_algorithm ;
typedef boost::checks::modulus10_algorithm< ean_weight, ean_sense, 1> ean_compute_algorithm ;

template <typename check_range>
bool check_ean13 (const check_range& check_seq)
{
  return boost::checks::check_sequence<ean_check_algorithm, EAN13_SIZE> ( check_seq ) ;
}

template <typename check_range>
typename boost::checks::ean_compute_algorithm::checkdigit<check_range>::type compute_ean13 (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<ean_compute_algorithm, EAN13_SIZE_WITHOUT_CHECKDIGIT> ( check_seq ) ;
}

template <typename check_range>
bool check_ean8 (const check_range& check_seq)
{
  return boost::checks::check_sequence<ean_check_algorithm, EAN8_SIZE> ( check_seq ) ;
}

template <typename check_range>
typename boost::checks::ean_compute_algorithm::checkdigit<check_range>::type compute_ean8 (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<ean_compute_algorithm, EAN8_SIZE_WITHOUT_CHECKDIGIT> ( check_seq ) ;
}


}}
#endif // BOOST_CHECKS_EAN_HPP
