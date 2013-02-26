// Copyright Pierre Talbot 2011-2013.
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
//(See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CHECKS_RTN_HPP
#define BOOST_CHECKS_RTN_HPP

#include <boost/checks/modulus10.hpp>
#include <boost/checks/checksum.hpp>
#include <boost/checks/precheck.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost{
namespace checks{

//[rtn_checkdigit
typedef mod10_basic_checkdigit rtn_checkdigit;
//]

//[rtn_checksum
#define RTN_SIZE 9
typedef size_checking<RTN_SIZE> rtn_size;
typedef weighted_sum<weight<3,7,1> > rtn_processor;

typedef checksum
<
  rtn_processor,
  rtn_checkdigit,
  rtn_size
> 
rtn_checksum;
//]

//[rtn_algorithm
typedef check_algorithm
<
  rtn_checksum
> 
rtn;
//]

}}
#endif
