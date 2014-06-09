//! \file
//! \brief Examples of validating and computing check digit(s) with Boost.Checks.

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
#include <exception>
#include <iterator>
#include <boost/lexical_cast.hpp>

//[credit_cards_include_files
#include <boost/checks/visa.hpp>
#include <boost/checks/amex.hpp>
#include <boost/checks/mastercard.hpp>
//]

//[mod97_10_include_file
#include <boost/checks/modulus97.hpp>
//]

//[ean_include_file
#include <boost/checks/ean.hpp>
//]

//[isbn_include_file
#include <boost/checks/isbn.hpp>
//]

#include <boost/checks/checks_fwd.hpp> // Forward declarations.

int main()
{
  //[checks_example_1
  using namespace boost::checks;
  std::string visa = "4000 0807 0620 0007";
  if(check_visa(visa))
    std::cout << "The VISA credit card number : " << visa << " is valid." << std::endl;

  std::string amex = "3458 2531 9273 09";
  size_t amex_checkdigit = compute_amex(amex);
  std::cout << "The check digit of the American Express number \"" << amex << "\" is \'" << amex_checkdigit << "\'." << std::endl;

  std::string mastercard = "5320 1274 8562 157";
  mastercard += boost::lexical_cast<std::string>(compute_mastercard(mastercard));
  std::cout << "\"" << mastercard << "\" is a valid mastercard number." << std::endl;

  //] [/checks_example_1]

  std::cout << std::endl;

  //[checks_example_2

  std::string mod97_10 = "1234567890123456789";
  size_t mod97_10_checkdigits = compute_mod97_10(mod97_10);
  std::cout << "The number \"" << mod97_10 << "\" has the check digits \"" << mod97_10_checkdigits << "\"." << std::endl;

  mod97_10 = "85212547851652";
  mod97_10 += boost::lexical_cast<std::string>(compute_mod97_10(mod97_10));
  std::cout << "A complete mod97-10 number is \"" << mod97_10 << "\"." << std::endl;

  //] [/checks_example_2]

  std::cout << std::endl;

  //[checks_example_3

  std::string ean13 = "540011301748"; // Incorrect size.
  if(!check_ean13(ean13))
    std::cout << "The EAN \"" << ean13 << "\" is not valid." << std::endl;


  std::string isbn13 = "977-0321227256"; // Third digit altered.
  if(!check_isbn13(isbn13))
    std::cout << "The ISBN-13 \"" << isbn13 << "\" is not valid." << std::endl;


  //] [/checks_example_3]

  std::cout << std::endl;

  //[checks_example_4

  std::string isbn10 = "020163371"; // More Effective C++: 35 New Ways to Improve Your Programs and Designs, Scott Meyers.
  int isbn10_int_array[] = {0,2,0,1,6,3,3,7,1};

  std::cout << "ISBN10 : " << isbn10 << ". Check digit : " << compute_isbn10(isbn10) << std::endl;
  std::cout << "ISBN10 integer version. Check digit : " << compute_isbn10(isbn10_int_array) << std::endl;

  //] [/checks_example_4]

  return 0;

} // int main()

/*

Example 1
---------
//[checks_output_1

The VISA credit card number : 4000 0807 0620 0007 is valid.
The check digit of the American Express number : 3458 2531 9273 09 is 4.
This is a valid Mastercard number : 5320 1274 8562 1570

//] [/checks_output_1]

Example 2
---------

//[checks_output_2

The number : 1234567890123456789 have the check digits : 68.
A complete mod97-10 number : 8521254785165211

//] [/checks_output_2]


Example 3
---------

//[checks_output_3

Too few or too much valid values in the sequence.
The third digit should be 8 or 9.

//] [/checks_output_3]

Example 4
---------

//[checks_output_4

ISBN10 : 020163371. Check digit : X
ISBN10 integer version. Check digit : 10

//] [/checks_output_4]
*/