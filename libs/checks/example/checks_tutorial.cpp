//  checks_tutorial.cpp
//! \file
//! \brief Examples of validating and computing check digit(s) with a handcrafted file.
/*! \detail This extension is very useful as there are hundreds of checksum systems
      in use worldwide.
      This example shows how a 'new' checksum system can be programmed
      by providing custom template parameters and macro constants.
      The examples chosen are Routing Transit Number
      http://en.wikipedia.org/wiki/Routing_transit_number (see rtn.hpp)
      and Vehicle Identification Number (see vin.hpp)
*/

// Copyright Pierre Talbot 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file is written to be included from a Quickbook .qbk document.
// It can be compiled by the C++ compiler, and run. Any output can
// also be added here as comment or included or pasted in elsewhere.
// Caution: this file contains Quickbook markup as well as code
// and comments: don't change any of the special comment markups!

#ifdef _MSC_VER
#  pragma warning (disable : 4127)
#endif

// Files containing the 'new' checksum definitions.
#include "rtn.hpp"
//#include "vin.hpp"

int main()
{
  using namespace boost::checks;
  //[rtn_example
  std::string rtn =  "111000025";
  if(check_rtn(rtn))
    std::cout << "The Routing Transit Number (RTN) \"" << rtn << "\" is valid." << std::endl;
  rtn = "11100002";
  std::cout << "The check digit of \"" << rtn << "\" is " << compute_rtn(rtn) << "." << std::endl;
  //]

  //[vin_example
  /*std::string vin = "1M8GDM9AXKP042788";
  if(check_vin(vin))
    std::cout << "The Vehicle Identification Number (VIN) \"" << vin << "\" is valid." << std::endl;

  vin = "1M8GDM9AKP042788";
  std::cout << "The check digit of \"" << vin << "\" is " << compute_vin(vin) << std::endl;*/
  //]
  return 0;
}
/*

//[rtn_example_output

The Routing Transit Number: 111000025 is valid.
The check digit of the number: 11100002 is 5.

//]

//[vin_example_output
The Vehicle Identification Number: 1M8GDM9AXKP042788 is correct.
The check digit of 1M8GDM9AKP042788 is X
//]

*/
