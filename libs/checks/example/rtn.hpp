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

#include <boost/checks/modulus10.hpp>
#include <boost/checks/checksum.hpp>
#include <boost/checks/precheck.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost{
namespace checks{

//[rtn_checkdigit
typedef checkdigit
<
  mod10_checkdigit
> 
rtn_checkdigit;
//]

//[rtn_checksum
#define RTN_SIZE 9
typedef strict_size_policy<RTN_SIZE> rtn_size;
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

/*
//[rtn_example
int main()
{
  using namespace boost::checks;
  std::string rtn_number("111000025");
  std::string rtn_number_without_checkdigit("11100002");

  if(validate<rtn>(rtn_number))
    std::cout << rtn_number << " is a valid RTN." << std::endl;

  boost::optional<rtn::checkdigit_type> checkdigit =
    compute_checkdigit<rtn>(rtn_number_without_checkdigit);
  if(checkdigit)
    std::cout << "The check digit of the RTN \'" << rtn_number_without_checkdigit
              << "\' is \'" << *checkdigit << "\'.\n";


  return 0;
}
//]

//[rtn_example_res
111000025 is a valid RTN.
The check digit of the RTN '11100002' is '5'.
//]
*/

}}
#endif
