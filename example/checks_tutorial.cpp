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
#include "vin.hpp"

int main()
{
  using namespace boost::checks;
  //[rtn_example
  std::string rtn_number("111000025");
  std::string rtn_number_without_checkdigit("11100002");

  if(validate<rtn>(rtn_number))
    std::cout << rtn_number << " is a valid RTN." << std::endl;

  boost::optional<rtn::checkdigit_type> checkdigit =
    compute_checkdigit<rtn>(rtn_number_without_checkdigit);
  if(checkdigit)
    std::cout << "The check digit of the RTN \'" << rtn_number_without_checkdigit
              << "\' is \'" << *checkdigit << "\'.\n";
  //]

  //[vin_example
  std::string vin_number("11111111 1 11111111");
  std::string vin_number_without_checkdigit("11111111 11111111");

  if(validate<vin>(vin_number))
    std::cout << vin_number << " is a valid VIN." << std::endl;

  boost::optional<vin::checkdigit_type> checkdigit =
    compute_checkdigit<vin>(vin_number_without_checkdigit);
  if(checkdigit)
    std::cout << "The check digit of the VIN \'" << vin_number_without_checkdigit
              << "\' is \'" << *checkdigit << "\'.\n";
  //]
  return 0;
}
/*

//[rtn_example_output
111000025 is a valid RTN.
The check digit of the RTN '11100002' is '5'.
//]

//[vin_example_output
11111111 1 11111111 is a valid VIN.
The check digit of the VIN '11111111 11111111' is '1'.
//]

*/
