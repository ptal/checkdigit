//! \file
//! \brief Examples of the functions provided in the file modulus.hpp

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


#include <iostream>
#include <string>

#include <sstream>
#include <fstream> 

#include <iterator>

#include <boost/checks/checks_fwd.hpp> // Forward declarations.
//[modulus_include_file
#include <boost/checks/modulus.hpp>
//] [/modulus_include_file]

int main()
{
  //[checks_modulus_example_1

  std::string luhn_number = "123455" ; // Initialisation
  // Verification
  if( boost::checks::check_luhn( luhn_number.begin(), luhn_number.end(), 6) )
    std::cout << "The number " << luhn_number << " is a valid luhn number." << std::endl;

  //] [/checks_modulus_example_1]

  //[checks_modulus_example_2

  std::wifstream mod11_ifile("files/checks_file_unicode_input.txt", std::ios::in);
  std::wofstream mod11_ofile("files/checks_file_unicode_output.txt", std::ios::out | std::ios::trunc );

  std::wstring tmp_mod11_number ;

  while( std::getline(mod11_ifile, tmp_mod11_number) )
  {
    wchar_t check_digit = boost::checks::compute_mod11<wchar_t>(tmp_mod11_number.begin(), tmp_mod11_number.end() );
    mod11_ofile << tmp_mod11_number << " check digit : " << check_digit << std::endl ;
  }
  mod11_ofile.close();
  mod11_ifile.close();

  //] [/checks_modulus_example_2]

  //[checks_modulus_example_3

  // Design the weight pattern for the Routing transit number (RTN)
  boost::array<unsigned int, 3> rtn_weight_pattern = {3,7,1};

  std::string rtn_number = "12345678" ;

  rtn_number += boost::checks::compute_mod10(rtn_number.begin(), rtn_number.end(), rtn_weight_pattern, 8) ;

  if ( boost::checks::check_mod10( rtn_number.begin(), rtn_number.end(), rtn_weight_pattern, 9) )
    std::cout << "The routing transit number (RTN) : " << rtn_number << " is valid." << std::endl ;

  //] [/checks_modulus_example_3]

  //[checks_modulus_example_4

  // Create a string with numbers
  std::string luhn_numbers = "";
  for(int i=9; i >= 0; --i)
  {
		std::ostringstream num_gen;
		num_gen << 1023456 << i ;
		std::string num = num_gen.str();
		char checkdigit = boost::checks::compute_luhn(num.begin(), num.end(), num.size());
		luhn_numbers = luhn_numbers + num + checkdigit ;
  }

  // Check all the numbers from this string
  std::string::iterator luhn_iter = luhn_numbers.begin();
  while(luhn_iter != luhn_numbers.end())
    if(boost::checks::check_luhn(luhn_iter, luhn_numbers.end(), 9))
      std::cout << "The number is valid." << std::endl;
    else
      std::cout << "The number is invalid." << std::endl;
  //] [/checks_modulus_example_4]

  return 0;

} // int main()

/*

Example 1
---------
//[checks_modulus_output_1

The number 123455 is a valid luhn number.

//] [/checks_isbn_output_1] 

Example 3
---------

//[checks_modulus_output_3

The routing transit number (RTN) : 123456780 is valid.

//] [/checks_modulus_output_3]


Example 4
---------

//[checks_modulus_output_4

The number is valid.
The number is valid.
The number is valid.
The number is valid.
The number is valid.
The number is valid.
The number is valid.
The number is valid.
The number is valid.
The number is valid.

//] [/checks_modulus_output_4]
*/