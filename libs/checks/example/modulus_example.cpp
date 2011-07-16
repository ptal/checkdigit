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

// You need to [import modulus_example.cpp]
// [include checks_isbn_example_1] where you want the include info - probably wrong now!
// and then [include checks_isbn_example_2] where you want the program line
// and then [include checks_isbn_output_1] when you want the output


template <typename Out, typename In>
inline Out f(In begin, In end)
{
	return *begin;
}

void test(unsigned int w[])
{
  if(w== NULL)
  {    unsigned int t[1]={1};
  
  w = t;}
}

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

  //] [checks_modulus_example_2]

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

  // Other tests / examples - Obsolete.

 // std::string mod10_test = "471-9-5120-0288-";
  std::string mod11_test = "12345678910";
  unsigned int w[] = {1,2,3,4};
  std::cout << "mod11 : " << boost::checks::compute_mod11( mod11_test.begin(), mod11_test.end(), 11) << std::endl;
  //std::cout << "mod11 : " << boost::checks::check_mod11( mod11_test.begin(), mod11_test.end(), 9) << std::endl;

  std::string luhn_transposition = "12345678900"; // even  
  std::cout << "ok : "<< boost::checks::compute_luhn( luhn_transposition.begin(), luhn_transposition.end(), luhn_transposition.size() ) << std::endl;
  luhn_transposition = "173456289003"; // even  
  
  std::cout << "ko : " << boost::checks::check_luhn( luhn_transposition.begin(), luhn_transposition.end(), luhn_transposition.size() ) << std::endl;
  test(NULL);

  std::string luhn2 = "1234567814";
  std::cout << luhn2[1] << luhn2[2] << std::endl;
  std::wstring luhn1(luhn2.begin(), luhn2.end());
  std::cout << luhn1[1] << luhn1[2] << std::endl;
  std::wstring::iterator iter1 = luhn1.begin();
//  wchar_t w = f<wchar_t>(luhn1.begin(), luhn1.end());
 // std::cout << w;

 std::string luhn_alterate = "1234567871";
 std::cout << boost::checks::check_luhn (luhn_alterate.begin(), luhn_alterate.end(), luhn_alterate.size()) << std::endl;
 std::cout << boost::checks::check_luhn (luhn_alterate.begin(), luhn_alterate.end()) << std::endl;
 luhn_alterate[0] += 9;
 std::cout << luhn_alterate<< std::endl;
 std::cout << boost::checks::check_luhn (luhn_alterate.begin(), luhn_alterate.end(), luhn_alterate.size()) << std::endl;
 std::cout << boost::checks::check_luhn (luhn_alterate.begin(), luhn_alterate.end()) << std::endl;

 std::string testt="12345678900";
 std::cout << boost::checks::compute_luhn(testt.begin(), testt.end(), 10) << std::endl;

 /*
  std::cout <<  boost::checks::check_luhn(luhn1.begin(), luhn1.end(), 10) << std::endl;

	  std::cout <<  boost::checks::compute_luhn<char>(luhn2.begin(), luhn2.end(), 9) << std::endl;
	  std::cout <<  boost::checks::compute_luhn<char>(luhn2.begin(), luhn2.end()) << std::endl;
	   std::cout <<  boost::checks::compute_luhn(luhn2.begin(), luhn2.end(), 9) << std::endl;*/
  return 0;

} // int main()

/*

Example 1
---------
//[checks_modulus_output_1

The number 123455 is a valid luhn number.

//] [/checks_isbn_output_1] 

*/