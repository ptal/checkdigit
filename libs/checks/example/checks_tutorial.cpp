//! \file checks_tutorial.cpp
//! \brief Examples of validating and computing check digit(s) with a homecraft file.

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

#include "rtn.hpp"
#include "vin.hpp"

int main()
{
  //[rtn_example
  std::string rtn_number =  "111000025" ;
  if ( check_rtn ( rtn_number ) )
    std::cout << "The Routing Transit Number: " << rtn_number << " is valid." << std::endl ;
  rtn_number = "11100002";
  std::cout << "The check digit of the number: " << rtn_number << " is " << compute_rtn (rtn_number ) << "." << std::endl ;
  //]

  //[vin_example
  std::string vin_number = "1M8GDM9AXKP042788";
  if ( check_vin ( vin_number ) )
    std::cout << "The Vehicle Identification Number: " << vin_number << " is correct." << std::endl ;

  vin_number = "1M8GDM9AKP042788" ;
  std::cout << "The check digit of " << vin_number << " is " << compute_vin ( vin_number) << std::endl ;
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
*/