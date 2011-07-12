//! \file testModulus.cpp

// Copyright Pierre Talbot 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Boost test of various check 'digit' systems.

// See http://www.boost.org/doc/libs/1_46_1/libs/test/doc/html/utf/testing-tools/reference.html

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE "Modulus Check Test Suite"
#define BOOST_LIB_DIAGNOSTIC "on"// Show library file details.
// Linking to lib file: libboost_unit_test_framework-vc100-mt-gd-1_47.lib  (trunk at 12 Jun 11)

#include <iostream>
#include <iomanip>
#include <cassert>
#include <list>

#include <boost/test/unit_test.hpp> // Enhanced for unit_test framework autolink,
#include <boost/checks/checks_fwd.hpp> // Forward declarations.
#include <boost/checks/modulus.hpp> // Modulo algorithms such the Luhn algorithm or the modulus 11 algorithm.

BOOST_AUTO_TEST_SUITE(modulus_minimum_test)
  
BOOST_AUTO_TEST_CASE(luhn_minimum_test)
{
  // empty string
  std::string luhn = "";
  BOOST_CHECK_EQUAL( boost::checks::compute_luhn(luhn.begin(), luhn.end()), 0);
  BOOST_CHECK_EQUAL( boost::checks::check_luhn(luhn.begin(), luhn.end()), false);
  BOOST_CHECK_EQUAL( boost::checks::check_luhn(luhn.begin(), luhn.end(), 0), false);
  BOOST_CHECK_EQUAL( boost::checks::check_luhn(luhn.begin(), luhn.end(), 5), false); // wrong size
  // One digit string
  luhn = "0";
  char check_digit;
  for(int i =0; i<9; ++i)
  {
    BOOST_CHECK_NE( check_digit = boost::checks::compute_luhn(luhn.begin(), luhn.end(), 1), 0);
    luhn += check_digit;
    BOOST_CHECK_EQUAL( boost::checks::check_luhn(luhn.begin(), luhn.end(), 2), true);
    luhn = (char)(i+48);
  }
}

BOOST_AUTO_TEST_CASE(mod10_minimum_test)
{
  // empty string
  std::string mod10 = "";
  BOOST_CHECK_EQUAL( boost::checks::compute_mod10(mod10.begin(), mod10.end(), NULL), 0);
  BOOST_CHECK_EQUAL( boost::checks::check_mod10(mod10.begin(), mod10.end(), NULL), false);
  BOOST_CHECK_EQUAL( boost::checks::check_mod10(mod10.begin(), mod10.end(), NULL, 0), false);
  BOOST_CHECK_EQUAL( boost::checks::check_mod10(mod10.begin(), mod10.end(), NULL, 5), false); // wrong size
  // One digit string
  mod10 = "0";
  char check_digit;
  for(int i =0; i<9; ++i)
  {
    BOOST_CHECK_NE( check_digit = boost::checks::compute_mod10(mod10.begin(), mod10.end(), NULL, 1), 0);
    mod10 += check_digit;
    BOOST_CHECK_EQUAL( boost::checks::check_mod10(mod10.begin(), mod10.end(), NULL, 2), true);
    mod10 = (char)(i+48);
  }
}

BOOST_AUTO_TEST_CASE(mod11_minimum_test)
{
  // empty string
  std::string mod11 = "";
  BOOST_CHECK_EQUAL( boost::checks::compute_mod11(mod11.begin(), mod11.end()), 0);
  BOOST_CHECK_EQUAL( boost::checks::check_mod11(mod11.begin(), mod11.end()), false);
  BOOST_CHECK_EQUAL( boost::checks::check_mod11(mod11.begin(), mod11.end(), 0), false);
  BOOST_CHECK_EQUAL( boost::checks::check_mod11(mod11.begin(), mod11.end(), 5), false); // wrong size
  // One digit string
  mod11 = "0";
  char check_digit;
  for(int i =0; i<9; ++i)
  {
    BOOST_CHECK_NE( check_digit = boost::checks::compute_mod11(mod11.begin(), mod11.end(), 1), 0);
    mod11 += check_digit;
    BOOST_CHECK_EQUAL( boost::checks::check_mod11(mod11.begin(), mod11.end(), 2), true);
    mod11 = (char)(i+48);
  }
}

BOOST_AUTO_TEST_SUITE_END() //modulus_minimum_test

BOOST_AUTO_TEST_SUITE(modulus_remainders_test)

BOOST_AUTO_TEST_CASE(luhn_remainders_test)
{ 
  BOOST_TEST_MESSAGE( "Boost.Checks.Modulus.Luhn : tests on the remainders.");
  // Initialization of the numbers with a odd and even size of digit (10 digits for 10 remainders).
  std::string luhn_numbers_odd[] = 
  {    
    "102345600",
	"102345691",
    "102345642",
    "102345683",
    "102345634",
    "102345675",
    "102345626",
    "102345667",
    "102345618",
    "102345659"
  };
  std::string luhn_numbers_even[] = 
  {    
    "1234567830",
    "1234567871",
    "1234567822",
    "1234567863",
    "1234567814",
    "1234567855",
    "1234567806",
	"1234567897",
    "1234567848",
    "1234567889",
  };
  char check_digit;
  // Test the numbers with a different remainder and an odd and even size of digits.
  for(int i=0; i<10; ++i)
  {
	// Test the validation of the check digit with the luhn algorithm with the size precised.
    BOOST_CHECK( boost::checks::check_luhn ( luhn_numbers_even[i].begin(), luhn_numbers_even[i].end(), luhn_numbers_even[i].size()) );
    BOOST_CHECK( boost::checks::check_luhn ( luhn_numbers_odd[i].begin(),  luhn_numbers_odd[i].end(),  luhn_numbers_odd[i].size() ) );

	// Test the validation of the check digit with the luhn algorithm without the size precised.
	BOOST_CHECK( boost::checks::check_luhn ( luhn_numbers_even[i].begin(), luhn_numbers_even[i].end()) );
    BOOST_CHECK( boost::checks::check_luhn ( luhn_numbers_odd[i].begin(),  luhn_numbers_odd[i].end() ) );

	// Test the equality between the check digit computed and the last digit with the size precised.
	BOOST_CHECK_EQUAL( boost::checks::compute_luhn(luhn_numbers_even[i].begin(), luhn_numbers_even[i].end(), luhn_numbers_even[i].size()-1), *(--luhn_numbers_even[i].end()) );
    BOOST_CHECK_EQUAL( boost::checks::compute_luhn(luhn_numbers_odd[i].begin(),  luhn_numbers_odd[i].end(),  luhn_numbers_odd[i].size()-1),  *(--luhn_numbers_odd[i].end())  );
	
	// Test the equality between the check digit computed and the last digit without the size precised.
	BOOST_CHECK_EQUAL( boost::checks::compute_luhn(luhn_numbers_even[i].begin(), luhn_numbers_even[i].end()-1), *(--luhn_numbers_even[i].end()) );
    BOOST_CHECK_EQUAL( boost::checks::compute_luhn(luhn_numbers_odd[i].begin(),  luhn_numbers_odd[i].end() -1), *(--luhn_numbers_odd[i].end())  );
  
    // Test the coherence between compute and check
    // compute
    BOOST_REQUIRE_NE ( check_digit = boost::checks::compute_luhn(luhn_numbers_even[i].begin(), luhn_numbers_even[i].end(), luhn_numbers_even[i].size()) , 0);
    std::string new_luhn_even = luhn_numbers_even[i] + check_digit ;
    BOOST_REQUIRE_NE ( check_digit = boost::checks::compute_luhn(luhn_numbers_odd[i].begin(), luhn_numbers_odd[i].end(), luhn_numbers_odd[i].size()) , 0);
    std::string new_luhn_odd = luhn_numbers_odd[i] + check_digit ; 
    // check
    BOOST_CHECK_EQUAL( boost::checks::check_luhn( new_luhn_even.begin(), new_luhn_even.end(), new_luhn_even.size()), true);
    BOOST_CHECK_EQUAL( boost::checks::check_luhn( new_luhn_odd.begin(), new_luhn_odd.end(), new_luhn_odd.size()), true);
  }
} // BOOST_AUTO_TEST_CASE(luhn_remainders_test)

BOOST_AUTO_TEST_CASE(mod10_remainders_test)
{
  BOOST_TEST_MESSAGE( "Boost.Checks.Modulus.Modulus10 : tests on the remainders.");
  std::string mod10_numbers_odd[] = 
  {    
    "102345690",
    "102345681",
    "102345672",
    "102345663",
    "102345654",
    "102345645",
    "102345636",
    "102345627",
    "102345618",
    "102345609"
  };
  std::string mod10_numbers_even[] = 
  {    
    "1234567840",
    "1234567831",
    "1234567822",
    "1234567813",
    "1234567804",
    "1234567895",
    "1234567886",
    "1234567877",
    "1234567868",
    "1234567859"
  };
  char check_digit;
  // Test the numbers with a different remainder and an odd and even size of digits.
  for(int i=0; i<10; ++i)
  {
	// Test the validation of the check digit with the mod10 algorithm with the size precised.
    BOOST_CHECK( boost::checks::check_mod10 ( mod10_numbers_even[i].begin(), mod10_numbers_even[i].end(), NULL, mod10_numbers_even[i].size()) );
    BOOST_CHECK( boost::checks::check_mod10 ( mod10_numbers_odd[i].begin(),  mod10_numbers_odd[i].end(),  NULL, mod10_numbers_odd[i].size() ) );
	// Test the validation of the check digit with the mod10 algorithm without the size precised.
	BOOST_CHECK( boost::checks::check_mod10 ( mod10_numbers_even[i].begin(), mod10_numbers_even[i].end(), NULL) );
    BOOST_CHECK( boost::checks::check_mod10 ( mod10_numbers_odd[i].begin(),  mod10_numbers_odd[i].end(),  NULL) );
	// Test the equality between the check digit computed and the last digit with the size precised.
	BOOST_CHECK_EQUAL( boost::checks::compute_mod10(mod10_numbers_even[i].begin(), mod10_numbers_even[i].end(), NULL, mod10_numbers_even[i].size()-1), *(--mod10_numbers_even[i].end()) );
    BOOST_CHECK_EQUAL( boost::checks::compute_mod10(mod10_numbers_odd[i].begin(),  mod10_numbers_odd[i].end(),  NULL, mod10_numbers_odd[i].size()-1),  *(--mod10_numbers_odd[i].end())  );
	// Test the equality between the check digit computed and the last digit without the size precised.
	BOOST_CHECK_EQUAL( boost::checks::compute_mod10(mod10_numbers_even[i].begin(), mod10_numbers_even[i].end()-1, NULL), *(--mod10_numbers_even[i].end()) );
    BOOST_CHECK_EQUAL( boost::checks::compute_mod10(mod10_numbers_odd[i].begin(),  mod10_numbers_odd[i].end() -1, NULL), *(--mod10_numbers_odd[i].end())  );
    // Test the coherence between compute and check
    // compute
    BOOST_REQUIRE_NE ( check_digit = boost::checks::compute_mod10(mod10_numbers_even[i].begin(), mod10_numbers_even[i].end(),NULL, mod10_numbers_even[i].size()) , 0);
    std::string new_mod10_even = mod10_numbers_even[i] + check_digit ;
    BOOST_REQUIRE_NE ( check_digit = boost::checks::compute_mod10(mod10_numbers_odd[i].begin(), mod10_numbers_odd[i].end(), NULL, mod10_numbers_odd[i].size()) , 0);
    std::string new_mod10_odd = mod10_numbers_odd[i] + check_digit ; 
    // check
    BOOST_CHECK_EQUAL( boost::checks::check_mod10( new_mod10_even.begin(), new_mod10_even.end(), NULL, new_mod10_even.size()), true);
    BOOST_CHECK_EQUAL( boost::checks::check_mod10( new_mod10_odd.begin(), new_mod10_odd.end(), NULL, new_mod10_odd.size()), true);
  }
}

BOOST_AUTO_TEST_CASE(mod11_remainders_test)
{
  BOOST_TEST_MESSAGE( "Boost.Checks.Modulus.Modulus11 : tests on the remainders.");
}
BOOST_AUTO_TEST_SUITE_END() //modulus_remainders_test

BOOST_AUTO_TEST_SUITE(modulus_alteration_test)

BOOST_AUTO_TEST_CASE(luhn_alteration_test)
{
  // Initialization of the numbers with a odd and even size of digit (10 digits for 10 remainders).
  std::string luhn_numbers_odd[] = 
  {    
    "102345600",
	"102345691",
    "102345642",
    "102345683",
    "102345634",
    "102345675",
    "102345626",
    "102345667",
    "102345618",
    "102345659"
  };
  std::string luhn_numbers_even[] = 
  {    
    "1234567830",
    "1234567871",
    "1234567822",
    "1234567863",
    "1234567814",
    "1234567855",
    "1234567806",
	"1234567897",
    "1234567848",
    "1234567889",
  };
  // Test the alteration of one digit
  for(int i=0; i<10; ++i)
  {
	// odd : test the alteration on each digits
    for(unsigned int j=0; j< luhn_numbers_odd[i].length(); ++j)
    {
      // alteration + [1|2|3|4|5|6|7|8|9] % 10
	  for(int k=1; k <= 9; ++k)
	  {
        std::string luhn_alterate = luhn_numbers_odd[i] ;
		luhn_alterate[j] = '0' + (luhn_alterate[j] + k) % 58  % 48 ;
		BOOST_CHECK_MESSAGE ( !boost::checks::check_luhn( luhn_alterate.begin(), luhn_alterate.end(), luhn_alterate.size() ), "The digit number " << j << "[" << luhn_numbers_odd[i][j] << "] is altered with "<< luhn_alterate[j] << "." );
		BOOST_CHECK_MESSAGE ( !boost::checks::check_luhn( luhn_alterate.begin(), luhn_alterate.end()),  "The digit number " << j << "[" << luhn_numbers_odd[i][j] << "] is altered with "<< luhn_alterate[j] << "." );
	  }
	}
	// even : test the alteration of each digits
	for(unsigned int j=0; j< luhn_numbers_even[i].length(); ++j)
    {
      // alteration + ([1|2|3|4|5|6|7|8|9] % 10)
	  for(int k=1; k <= 9; ++k)
	  {
        std::string luhn_alterate = luhn_numbers_even[i] ;
		luhn_alterate[j] = '0' + (luhn_alterate[j] + k) % 58 % 48 ;
		BOOST_CHECK_MESSAGE ( !boost::checks::check_luhn( luhn_alterate.begin(), luhn_alterate.end(), luhn_alterate.size() ),  "The digit number " << j << "[" << luhn_numbers_even[i][j] << "] is altered with "<< luhn_alterate[j] << "." );
		BOOST_CHECK_MESSAGE ( !boost::checks::check_luhn( luhn_alterate.begin(), luhn_alterate.end() ),  "The digit number " << j << "[" << luhn_numbers_even[i][j] << "] is altered with "<< luhn_alterate[j] << "." );
	  }
	}
  }
} //BOOST_AUTO_TEST_CASE(luhn_alteration_test)

BOOST_AUTO_TEST_CASE(mod10_alteration_test)
{
  // Initialization of the numbers with a odd and even size of digit (10 digits for 10 remainders).
  std::string mod10_numbers_odd[] = 
  {    
    "102345690",
    "102345681",
    "102345672",
    "102345663",
    "102345654",
    "102345645",
    "102345636",
    "102345627",
    "102345618",
    "102345609"
  };
  std::string mod10_numbers_even[] = 
  {    
    "1234567840",
    "1234567831",
    "1234567822",
    "1234567813",
    "1234567804",
    "1234567895",
    "1234567886",
    "1234567877",
    "1234567868",
    "1234567859"
  };
  // Test the alteration of one digit
  for(int i=0; i<10; ++i)
  {
	// odd : test the alteration on each digits
    for(unsigned int j=0; j< mod10_numbers_odd[i].length(); ++j)
    {
      // alteration + [1|2|3|4|5|6|7|8|9] % 10
	  for(int k=1; k <= 9; ++k)
	  {
        std::string mod10_alterate = mod10_numbers_odd[i] ;
		mod10_alterate[j] = '0' + (mod10_alterate[j] + k) % 58  % 48 ;
		BOOST_CHECK_MESSAGE ( !boost::checks::check_mod10( mod10_alterate.begin(), mod10_alterate.end(), NULL, mod10_alterate.size() ),  "The digit number " << j << "[" << mod10_numbers_odd[i][j] << "] is altered with "<< mod10_alterate[j] << "." );
		BOOST_CHECK_MESSAGE ( !boost::checks::check_mod10( mod10_alterate.begin(), mod10_alterate.end(), NULL),  "The digit number " << j << "[" << mod10_numbers_odd[i][j] << "] is altered with "<< mod10_alterate[j] << "." );
	  }
	}
	// even : test the alteration of each digits
	for(unsigned int j=0; j< mod10_numbers_even[i].length(); ++j)
    {
      // alteration + ([1|2|3|4|5|6|7|8|9] % 10)
	  for(int k=1; k <= 9; ++k)
	  {
        std::string mod10_alterate = mod10_numbers_even[i] ;
		mod10_alterate[j] = '0' + (mod10_alterate[j] + k) % 58 % 48 ;
		BOOST_CHECK_MESSAGE ( !boost::checks::check_mod10( mod10_alterate.begin(), mod10_alterate.end(), NULL, mod10_alterate.size() ), "The digit number " << j << "[" << mod10_numbers_even[i][j] << "] is altered with "<< mod10_alterate[j] << "." );
		BOOST_CHECK_MESSAGE ( !boost::checks::check_mod10( mod10_alterate.begin(), mod10_alterate.end(), NULL ), "The digit number " << j << "[" << mod10_numbers_even[i][j] << "] is altered with "<< mod10_alterate[j] << ".");
	  }
	}
  }
} //BOOST_AUTO_TEST_CASE(mod10_alteration_test)

BOOST_AUTO_TEST_SUITE_END() //modulus_alteration_test

BOOST_AUTO_TEST_SUITE(modulus_transposition_test)

// Transposition of 9 and 0 fails with odd and even tests.
BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES( luhn_transposition_test, 2 )
BOOST_AUTO_TEST_CASE(luhn_transposition_test)
{
  std::string luhn_transposition_odd = "12345678903"; //odd
  std::string luhn_transposition_even = "123456789007"; // even  
  std::string luhn_transposition;
  // for each digits
  for(int i=0; i < 9; ++i)
  {
    // Test a permutation with all the digits remaining
    for(int j=i+1; j < 10; j+=2)
    {
      // Odd
      luhn_transposition = luhn_transposition_odd;
      luhn_transposition[i] = luhn_transposition[j];
      luhn_transposition[j] = luhn_transposition_odd[i];
      BOOST_CHECK_MESSAGE ( !boost::checks::check_luhn( luhn_transposition.begin(), luhn_transposition.end(), luhn_transposition.size() ), "The digit number " << j << "[" << luhn_transposition[j] << "] is transposed with "<< luhn_transposition[i] << "." );
      // Even
      luhn_transposition = luhn_transposition_even;
      luhn_transposition[i] = luhn_transposition[j];
      luhn_transposition[j] = luhn_transposition_even[i];
      BOOST_CHECK_MESSAGE ( !boost::checks::check_luhn( luhn_transposition.begin(), luhn_transposition.end(), luhn_transposition.size() ),  "The digit number " << j << "[" << luhn_transposition[j] << "] is transposed with "<< luhn_transposition[i] << "."  );
    }
  }
} // BOOST_AUTO_TEST_CASE(luhn_transposition_test)

BOOST_AUTO_TEST_SUITE_END() //modulus_transposition_test
  
BOOST_AUTO_TEST_SUITE(modulus_encoding_test)
BOOST_AUTO_TEST_CASE(luhn_encoding_test)
{ 
  std::string raw_luhn = "123456781";
  std::wstring luhn(raw_luhn.begin(), raw_luhn.end());
  std::wstring::iterator iter1 = luhn.begin();
  BOOST_CHECK_EQUAL (boost::checks::compute_luhn<wchar_t>(luhn.begin(), luhn.end()), '4');
  BOOST_CHECK_EQUAL (boost::checks::compute_luhn<wchar_t>(luhn.begin(), luhn.end()), '4');
  
  luhn += '4';
  BOOST_CHECK_EQUAL (boost::checks::check_luhn(luhn.begin(), luhn.end()), true);
} // BOOST_AUTO_TEST_CASE(modulus_encoding_test)

BOOST_AUTO_TEST_SUITE_END() //modulus_encoding_test
  
BOOST_AUTO_TEST_SUITE(modulus_collection_test)
BOOST_AUTO_TEST_CASE(luhn_collection_test)
{ 
	std::list<char> luhn;
    for(char i=48; i < 53; ++i) 
      luhn.push_back(i);
    char check_digit;
    BOOST_REQUIRE_NE( check_digit = boost::checks::compute_luhn(luhn.begin(), luhn.end(), 5) , 0);
    BOOST_REQUIRE_EQUAL( boost::checks::compute_luhn(luhn.begin(), luhn.end()) , check_digit);
    luhn.push_back(check_digit);
    BOOST_CHECK_EQUAL( boost::checks::check_luhn(luhn.begin(), luhn.end(), 6), true);
    BOOST_CHECK_EQUAL( boost::checks::check_luhn(luhn.begin(), luhn.end()), true);
} // BOOST_AUTO_TEST_CASE(luhn_collection_test)

BOOST_AUTO_TEST_CASE(mod10_collection_test)
{ 
	std::list<char> mod10;
    for(char i=48; i < 53; ++i) 
      mod10.push_back(i);
    char check_digit;
    BOOST_REQUIRE_NE( check_digit = boost::checks::compute_mod10(mod10.begin(), mod10.end(), NULL, 5) , 0);
    BOOST_REQUIRE_EQUAL( boost::checks::compute_mod10(mod10.begin(), mod10.end(), NULL) , check_digit);
    mod10.push_back(check_digit);
    BOOST_CHECK_EQUAL( boost::checks::check_mod10(mod10.begin(), mod10.end(), NULL, 6), true);
    BOOST_CHECK_EQUAL( boost::checks::check_mod10(mod10.begin(), mod10.end(), NULL), true);
} // BOOST_AUTO_TEST_CASE(mod10_collection_test)

BOOST_AUTO_TEST_SUITE_END() //modulus_collection_test


BOOST_AUTO_TEST_SUITE(modulus_weight_test)
BOOST_AUTO_TEST_CASE(mod10_weight_test)
{
  // Test with a weight of 1 on each digit
  std::string mod10 = "1234";
  unsigned int weight[] = {1,1,1,1};
  BOOST_CHECK_EQUAL( boost::checks::compute_mod10(mod10.begin(), mod10.end(), weight, 4),
                     boost::checks::compute_mod10(mod10.begin(), mod10.end(), NULL,   4));

  for(int i=0; i<4; ++i) weight[i] = i+1;
  BOOST_CHECK_EQUAL( boost::checks::compute_mod10(mod10.begin(), mod10.end(), weight, 4), '0');
}
BOOST_AUTO_TEST_SUITE_END() //modulus_weight_test