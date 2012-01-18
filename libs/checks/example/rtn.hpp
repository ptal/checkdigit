// rtn.hpp
//! \file
//! \brief Check and compute the Routing Transit Number(RTN)
//! as an example of implementing a new checksum type.
/*! \detail Routing Transit Number
      http://en.wikipedia.org/wiki/Routing_transit_number
*/

// Copyright Pierre Talbot 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
//(See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CHECKS_RTN_HPP
#define BOOST_CHECKS_RTN_HPP

//[rtn_include_files
#include <boost/checks/modulus10.hpp>
#include <boost/checks/basic_checks.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
//]

//[rtn_preprocessor_tools
#define RTN_SIZE 9
#define RTN_SIZE_WITHOUT_CHECKDIGIT 8

typedef boost::checks::weight<3,7,1> rtn_weight;
//]

//[rtn_preprocessor_algorithm
typedef boost::checks::modulus10_algorithm<rtn_weight, 0> rtn_check_algorithm;
typedef boost::checks::modulus10_algorithm<rtn_weight, 0> rtn_compute_algorithm;
//]

//[rtn_functions
template <typename check_range>
bool check_rtn(const check_range& check_seq)
{
  return boost::checks::check_sequence<rtn_check_algorithm, RTN_SIZE>(boost::begin(check_seq), boost::end(check_seq));
}

template <typename check_range>
typename rtn_compute_algorithm::checkdigit<check_range>::type compute_rtn(const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<rtn_compute_algorithm, RTN_SIZE_WITHOUT_CHECKDIGIT>(boost::begin(check_seq), boost::end(check_seq));
}
//]

#endif
