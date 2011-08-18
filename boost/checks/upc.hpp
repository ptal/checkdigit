//  Boost checks/upc.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

// European Article Numbering 13 and 8.

#ifndef BOOST_CHECKS_UPC_HPP
#define BOOST_CHECKS_UPC_HPP

#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/basic_checks.hpp>
#include <boost/checks/modulus10.hpp>

#define UPCA_SIZE 12
#define UPCA_SIZE_WITHOUT_CHECKDIGIT 11

namespace boost {
    namespace checks{

typedef boost::checks::weight<1,3> upc_weight ;
typedef boost::checks::rightmost upc_sense ;

typedef boost::checks::modulus10_algorithm< upc_weight, upc_sense, 0> upc_check_algorithm ;
typedef boost::checks::modulus10_algorithm< upc_weight, upc_sense, 1> upc_compute_algorithm ;

template <typename check_range>
bool check_upca (const check_range& check_seq)
{
  return boost::checks::check_sequence<upc_check_algorithm, UPCA_SIZE> ( check_seq ) ;
}

template <typename check_range>
typename boost::checks::upc_compute_algorithm::checkdigit<check_range>::type compute_upca (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<upc_compute_algorithm, UPCA_SIZE_WITHOUT_CHECKDIGIT> ( check_seq ) ;
}


}}
#endif // BOOST_CHECKS_UPCA_HPP