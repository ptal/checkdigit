// vin.hpp
//! \file
//! \brief Check and compute the Vehicle Identification Number.
//! This is an example of extending the library for a new checksum type.
/*! \detail  Vehicle Identification Number
      http://en.wikipedia.org/wiki/Vehicle_Identification_Number
*/

// Copyright Pierre Talbot 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
//(See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CHECKS_VIN_HPP
#define BOOST_CHECKS_VIN_HPP

//[vin_preprocessor_tools
#include <stdexcept>
#include <boost/checks/precheck.hpp>
#include <boost/checks/checksum.hpp>
#include <boost/checks/modulus11.hpp>
#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>

namespace boost{
namespace checks{


//[vin_checkdigit
#define VIN_CHECKDIGIT_POS 8
#define VIN_CHECKDIGIT_SIZE 1

typedef type_adaptor
<
  mod11_basic_checkdigit, 
  checkdigit_pos_tag, 
  VIN_CHECKDIGIT_POS
>::type
vin_checkdigit;
//]

//[vin_transliteration
struct vin_transliteration
{
  size_t operator()(char value) const 
  {
    char lower_value = std::tolower(value);
    if(value_lower == 'o' || value_lower == 'i' || value_lower == 'q')
      throw transliteration_exception("The letters I, O and Q are not allowed.");
    // If the value is less or equal than 9, we are sure it's a number thanks to the filter.
    if(value <= '9')
      return value - '0';

    size_t res = value_lower - 'a' + 1;
    return res % 10 + res / 10 + (res > 18);
  }
};
//]

//[vin_size
#define VIN_SIZE 17

typedef strict_size_policy<VIN_SIZE> vin_size;
//]

//[vin_processor
typedef weight<2,3,4,5,6,7,8,9,10> vin_weight;
typedef weighted_sum<vin_weight> vin_processor;
//]

//[vin_checksum
typedef checksum
<
  vin_processor,
  vin_checkdigit,
  vin_size,
  vin_transliteration
> 
vin_checksum;
//]

//[vin_algorithm
typedef check_algorithm
<
  vin_checksum
> 
vin;
//]

}}
#endif
