//! \file test_checks.cpp

// Copyright Pierre Talbot 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Boost test of various check 'digit' systems.

// See http://www.boost.org/doc/libs/1_46_1/libs/test/doc/html/utf/testing-tools/reference.html

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE "Check Test Suite"
#define BOOST_LIB_DIAGNOSTIC "on"// Show library file details.
// Linking to lib file: libboost_unit_test_framework-vc100-mt-gd-1_47.lib  (trunk at 12 Jun 11)

#include <iostream>
#include <iomanip>

#include <boost/test/unit_test.hpp> // Enhanced for unit_test framework autolink

#include <boost/checks/luhn.hpp>
#include <boost/checks/verhoeff.hpp>
#include <boost/checks/modulus11.hpp>
#include <boost/checks/modulus97.hpp>
#include <boost/checks/ean.hpp>
#include <boost/checks/isbn.hpp>
#include <boost/checks/upc.hpp>
#include <boost/checks/amex.hpp>
#include <boost/checks/visa.hpp>
#include <boost/checks/mastercard.hpp>
#include <boost/checks/checks_fwd.hpp> // Forward declarations.

#include "alteration_test.hpp"
#include "transposition_test.hpp"

template <typename functor>
unsigned int transposition( const functor &compute_checkdigit );

template <typename functor>
unsigned int alteration( const functor &compute_checkdigit , unsigned int number_of_position_to_test );

BOOST_AUTO_TEST_SUITE( use_cases_tests )

// IIN : Issuer Identification Number.
// MII : Major Industry Identifier.

BOOST_AUTO_TEST_CASE(visa_tests)
{
  std::string visa_valid = "4417 1234 5678 9113" ;
  std::string visa_low_size_failure = "417 1234 5678 9113" ;
  std::string visa_big_size_failure = "44417 1234 5678 9113" ;
  std::string visa_mii_failure = "3417 1234 5678 9113" ;

  BOOST_CHECK ( boost::checks::check_visa (visa_valid) ) ;
  BOOST_CHECK_THROW ( boost::checks::check_visa (visa_low_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_visa (visa_big_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_visa (visa_mii_failure) , std::invalid_argument ) ;

  std::string visa_valid_without_checkdigit = "4417 1234 5678 911" ;
  std::string visa_mii_failure_without_checkdigit = "3417 1234 5678 911" ;

  BOOST_CHECK_EQUAL ( boost::checks::compute_visa (visa_valid_without_checkdigit) , '3' ) ;
  BOOST_CHECK_THROW ( boost::checks::compute_visa (visa_mii_failure_without_checkdigit) , std::invalid_argument ) ;
}

BOOST_AUTO_TEST_CASE(amex_tests)
{
  std::string amex_valid = "3782 822463 10005" ;
  std::string amex_low_size_failure = "378 822463 10005" ;
  std::string amex_big_size_failure = "33782 822463 10005" ;
  std::string amex_mii_failure = "4782 822463 10005" ;
  std::string amex_iin_failure = "3882 822463 10005" ;

  BOOST_CHECK ( boost::checks::check_amex (amex_valid) ) ;
  BOOST_CHECK_THROW ( boost::checks::check_amex (amex_low_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_amex (amex_big_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_amex (amex_mii_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_amex (amex_iin_failure) , std::invalid_argument ) ;

  std::string amex_valid_without_checkdigit = "3782 822463 1000" ;
  std::string amex_mii_failure_without_checkdigit = "4782 822463 1000" ;
  std::string amex_iin_failure_without_checkdigit = "3682 822463 1000" ;

  BOOST_CHECK_EQUAL ( boost::checks::compute_amex (amex_valid_without_checkdigit) , '5' ) ;
  BOOST_CHECK_THROW ( boost::checks::compute_amex (amex_mii_failure_without_checkdigit) , std::invalid_argument ) ;
}

BOOST_AUTO_TEST_CASE(mastercard_tests)
{
  std::string mastercard_valid = "5105 1051 0510 5100" ;
  std::string mastercard_low_size_failure = "515 1051 0510 5100" ;
  std::string mastercard_big_size_failure = "51505 1051 0510 5100" ;
  std::string mastercard_mii_failure = "4105 1051 0510 5100" ;
  std::string mastercard_iin_failure = "5005 1051 0510 5100" ;

  BOOST_CHECK ( boost::checks::check_mastercard (mastercard_valid) ) ;
  BOOST_CHECK_THROW ( boost::checks::check_mastercard (mastercard_low_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_mastercard (mastercard_big_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_mastercard (mastercard_mii_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_mastercard (mastercard_iin_failure) , std::invalid_argument ) ;

  std::string mastercard_valid_without_checkdigit = "5105 1051 0510 510" ;
  std::string mastercard_mii_failure_without_checkdigit = "6105 1051 0510 510" ;
  std::string mastercard_iin_failure_without_checkdigit = "5605 1051 0510 510" ;

  BOOST_CHECK_EQUAL ( boost::checks::compute_mastercard (mastercard_valid_without_checkdigit) , '0' ) ;
  BOOST_CHECK_THROW ( boost::checks::compute_mastercard (mastercard_mii_failure_without_checkdigit) , std::invalid_argument ) ;
}

BOOST_AUTO_TEST_CASE(ean_tests)
{
  std::string ean13_valid = "5 412983 130028" ; // Belgium beer "Bon secours".
  std::string ean13_low_size_failure = "05 412983 130028" ;
  std::string ean13_big_size_failure = "412983 130028" ;

  BOOST_CHECK ( boost::checks::check_ean13 (ean13_valid) ) ;
  BOOST_CHECK_THROW ( boost::checks::check_ean13 (ean13_low_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_ean13 (ean13_big_size_failure) , std::invalid_argument ) ;

  std::string ean13_valid_without_checkdigit = "5 412983 13002" ;
  BOOST_CHECK_EQUAL ( boost::checks::compute_ean13 (ean13_valid_without_checkdigit), '8' ) ; 

  std::string ean8_valid = "5449 1472" ; // Bottle of Coke.
  std::string ean8_low_size_failure = "5449 472" ;
  std::string ean8_big_size_failure = "05449 1472" ;

  BOOST_CHECK ( boost::checks::check_ean8 (ean8_valid) ) ;
  BOOST_CHECK_THROW ( boost::checks::check_ean8 (ean8_low_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_ean8 (ean8_big_size_failure) , std::invalid_argument ) ;

  std::string ean8_valid_without_checkdigit = "5449 147" ;
  BOOST_CHECK_EQUAL ( boost::checks::compute_ean8 (ean8_valid_without_checkdigit), '2' ) ; 
}

BOOST_AUTO_TEST_CASE(upc_tests)
{
  std::string upca_valid = "036000291452" ; // Box of tissues.
  std::string upca_low_size_failure = "36000291452" ;
  std::string upca_big_size_failure = "0036000291452" ;

  BOOST_CHECK ( boost::checks::check_upca (upca_valid) ) ;
  BOOST_CHECK_THROW ( boost::checks::check_upca (upca_low_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_upca (upca_big_size_failure) , std::invalid_argument ) ;

  std::string upca_valid_without_checkdigit = "03600029145" ;
  BOOST_CHECK_EQUAL ( boost::checks::compute_upca (upca_valid_without_checkdigit), '2' ) ; 
}

BOOST_AUTO_TEST_CASE(isbn_tests)
{

  std::string isbn13_valid = "978-0-13-235088-4" ; // Clean Code: a handbook of agile software craftsmanship, Robert C. Martin.
  std::string isbn13_not_valid = "979-0-13-235088-4" ; 
  std::string isbn13_low_size_failure = "978--13-235088-4" ;
  std::string isbn13_big_size_failure = "978-00-13-235088-4" ;
  std::string isbn13_ean_id_failure = "977-0-13-235088-4" ;
  std::string isbn13_ean_id_failure2 = "988-0-13-235088-4" ;
  std::string isbn13_ean_id_failure3 = "878-0-13-235088-4" ;

  BOOST_CHECK ( boost::checks::check_isbn13 (isbn13_valid) ) ;
  BOOST_CHECK ( !boost::checks::check_isbn13 (isbn13_not_valid) ) ;
  BOOST_CHECK_THROW ( boost::checks::check_isbn13 (isbn13_low_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_isbn13 (isbn13_big_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_isbn13 (isbn13_ean_id_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_isbn13 (isbn13_ean_id_failure2) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_isbn13 (isbn13_ean_id_failure3) , std::invalid_argument ) ;

  std::string isbn13_valid_without_checkdigit = "978-0-13-235088-" ;
  std::string isbn13_not_valid_without_checkdigit = "979-0-13-235088-" ; 
  BOOST_CHECK_EQUAL ( boost::checks::compute_isbn13 (isbn13_valid_without_checkdigit), '4' ) ; 
  BOOST_CHECK_NE ( boost::checks::compute_isbn13 (isbn13_not_valid_without_checkdigit), '4' ) ; 

  std::string isbn10_valid = "0-201-70073-5" ; // The C++ Programming Language, Special Edition, Bjarne Stroustrup.
  std::string isbn10_low_size_failure = "00-201-70073-5" ;
  std::string isbn10_big_size_failure = "-201-70073-5" ;

  BOOST_CHECK ( boost::checks::check_isbn10 (isbn10_valid) ) ;
  BOOST_CHECK_THROW ( boost::checks::check_isbn10 (isbn10_low_size_failure) , std::invalid_argument ) ;
  BOOST_CHECK_THROW ( boost::checks::check_isbn10 (isbn10_big_size_failure) , std::invalid_argument ) ;

  std::string isbn10_valid_without_checkdigit = "0-201-70073-" ;
  BOOST_CHECK_EQUAL ( boost::checks::compute_isbn10 (isbn10_valid_without_checkdigit), '5' ) ; 
}

BOOST_AUTO_TEST_CASE(mod97_10_tests)
{
  std::string mod97_10_valid = "510007547061111462" ; // From a Belgium IBAN
  std::string mod97_10_not_valid = "511007547061111462" ; 
  std::string mod97_10_low_size_failure = "51007547061111462" ;
  std::string mod97_10_big_size_failure = "5100007547061111462" ;

  BOOST_CHECK ( boost::checks::check_mod97_10 (mod97_10_valid) ) ;
  BOOST_CHECK ( !boost::checks::check_mod97_10 (mod97_10_not_valid) ) ;
  BOOST_CHECK ( !boost::checks::check_mod97_10 (mod97_10_low_size_failure)) ;
  BOOST_CHECK ( !boost::checks::check_mod97_10 (mod97_10_big_size_failure)) ;

  std::string mod97_10_valid_without_checkdigits = "5100075470611114" ;
  std::string mod97_10_not_valid_without_checkdigits = "5110075470611114" ; 
  
  std::string valid_check_digits = "00" ;
  boost::checks::compute_mod97_10 (mod97_10_valid_without_checkdigits, valid_check_digits.begin() );
  BOOST_CHECK_EQUAL ( valid_check_digits, "62" ) ; 
  
  std::string invalid_check_digits = "00";
  boost::checks::compute_mod97_10 (mod97_10_not_valid_without_checkdigits, invalid_check_digits.begin() );
  BOOST_CHECK_NE ( invalid_check_digits, "62" ) ; 
}

BOOST_AUTO_TEST_SUITE_END()




BOOST_AUTO_TEST_SUITE( technical_tests )

struct luhn_functor
{
  template <typename range>
  typename boost::checks::luhn_compute_algorithm::checkdigit<range>::type operator ()( const range &check_range ) const
  {
    return boost::checks::compute_luhn( check_range ) ;
  }
};

struct verhoeff_functor
{
  template <typename range>
  typename boost::checks::verhoeff_compute_algorithm::checkdigit<range>::type operator ()( const range &check_range ) const
  {
    return boost::checks::compute_verhoeff( check_range ) ;
  }
};

struct modulus11_functor
{
  template <typename range>
  typename boost::checks::mod11_compute_algorithm::checkdigit<range>::type operator ()( const range &check_range ) const
  {
    return boost::checks::compute_modulus11( check_range ) ;
  }
};

BOOST_AUTO_TEST_CASE(luhn_test)
{
  unsigned int transpositions_failures = transposition( luhn_functor() ) ;
  BOOST_CHECK_MESSAGE( transpositions_failures == 2, "" << (90-transpositions_failures) << " catched on 90.") ;

  unsigned int alterations_failures = alteration( luhn_functor() , 2) ;
  BOOST_CHECK_MESSAGE( alterations_failures == 0, "" << (18-alterations_failures) << " catched on 18.") ;
}

BOOST_AUTO_TEST_CASE(verhoeff_test)
{
  unsigned int transpositions_failures = transposition( verhoeff_functor() ) ;
  BOOST_CHECK_MESSAGE( transpositions_failures == 0, "" << (90-transpositions_failures) << " catched on 90.") ;

  unsigned int alterations_failures = alteration( verhoeff_functor() , 20) ;
  BOOST_CHECK_MESSAGE( alterations_failures == 0, "" << (180-alterations_failures) << " catched on 180.") ;
}

BOOST_AUTO_TEST_CASE(modulus11_test)
{
  unsigned int transpositions_failures = transposition( modulus11_functor() ) ;
  BOOST_CHECK_MESSAGE( transpositions_failures == 0, "" << (90-transpositions_failures) << " catched on 90.") ;

  unsigned int alterations_failures = alteration( modulus11_functor() , 10) ;
  BOOST_CHECK_MESSAGE( alterations_failures == 0, "" << (90-alterations_failures) << " catched on 90.") ;
}

BOOST_AUTO_TEST_SUITE_END()
