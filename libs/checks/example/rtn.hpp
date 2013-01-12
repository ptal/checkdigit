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
#include <cstddef>
#include <boost/checks/modulus10.hpp>
#include <boost/checks/checksum.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
//]

//[rtn_preprocessor_tools
#define RTN_SIZE 9

namespace boost{
namespace checks{

typedef weighted_sum<weight<3,7,1> > rtn_processor;
//]

//[rtn_preprocessor_algorithm
typedef checksum
<
  rtn_processor,
  mod10_validation,
  mod10_checkdigit
> rtn_checksum;

typedef features
<
  rtn_checksum,
  RTN_SIZE
> rtn;

//]

//[rtn_functions
template <typename check_range>
bool check_rtn(const check_range& check_seq)
{
  return check_sequence<rtn>(check_seq);
}

template <typename check_range>
size_t compute_rtn(const check_range& check_seq)
{
  return compute_checkdigit<rtn>(check_seq);
}
//]
}}
#endif
