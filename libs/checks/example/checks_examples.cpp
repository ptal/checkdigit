//! \file
//! \brief Examples of validating and computing check digit(s) with Boost.Checks

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

#include <iterator>

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

  std::string visa_credit_card_number = "4000 0807 0620 0007" ;
  if( boost::checks::check_visa( visa_credit_card_number ) )
    std::cout << "The VISA credit card number : " << visa_credit_card_number << " is valid." << std::endl ;

  std::string amex_credit_card_number = "3458 2531 9273 09" ;
  char amex_checkdigit = boost::checks::compute_amex( amex_credit_card_number ) ;
  std::cout << "The check digit of the American Express number : " << amex_credit_card_number << " is " << amex_checkdigit << "." << std::endl ;

  std::string mastercard_credit_card_number = "5320 1274 8562 157" ;
  mastercard_credit_card_number += boost::checks::compute_mastercard( mastercard_credit_card_number );
  std::cout << "This is a valid Mastercard number : " << mastercard_credit_card_number << std::endl ;

  //] [/checks_example_1]

  std::cout << std::endl ;

  //[checks_example_2

  std::string mod97_10_number = "1234567890123456789" ;
  std::string mod97_10_checkdigits = "  " ;
  boost::checks::compute_mod97_10 ( mod97_10_number , mod97_10_checkdigits.begin() ) ;
  std::cout << "The number : " << mod97_10_number << " have the check digits : " << mod97_10_checkdigits << "." << std::endl ;

  mod97_10_number = "85212547851652  " ;
  boost::checks::compute_mod97_10 ( mod97_10_number , mod97_10_number.end() - 2);
  std::cout << "A complete mod97-10 number : " << mod97_10_number << std::endl ;

  //] [/checks_example_2]

  std::cout << std::endl ;

  //[checks_example_3

  std::string ean13_number = "540011301748" ; // Incorrect size.
  try{
    boost::checks::check_ean13 ( ean13_number ) ;
  }catch ( std::invalid_argument e )
  {
    std::cout << e.what() << std::endl ;
  }

  std::string isbn13_number = "977-0321227256" ; // Third digit altered.
  try{
    boost::checks::check_isbn13( isbn13_number );
  }catch ( std::invalid_argument e )
  {
    std::cout << e.what() << std::endl ;
  }

  //] [/checks_example_3]

  std::cout << std::endl ;

  //[checks_example_4

  std::string isbn10_number = "020163371" ; // More Effective C++: 35 New Ways to Improve Your Programs and Designs, Scott Meyers.
  int isbn10_integer_number[] = {0,2,0,1,6,3,3,7,1} ;

  std::cout << "ISBN10 : " << isbn10_number << ". Check digit : " << boost::checks::compute_isbn10( isbn10_number ) << std::endl ;
  std::cout << "ISBN10 integer version. Check digit : " << boost::checks::compute_isbn10( isbn10_integer_number ) << std::endl ;

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