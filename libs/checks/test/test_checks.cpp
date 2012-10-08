//! \file test_checks.cpp

// Copyright Pierre Talbot 2011 - 2012.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
//(See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Boost test of various check 'digit' systems.

// See http://www.boost.org/doc/libs/1_46_1/libs/test/doc/html/utf/testing-tools/reference.html

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE "Check Test Suite"
#define BOOST_LIB_DIAGNOSTIC "on"// Show library file details.
// Linking to lib file: libboost_unit_test_framework-vc100-mt-gd-1_47.lib (trunk at 12 Jun 11)

#include <iostream>
#include <iomanip>

#include <boost/test/unit_test.hpp> // Enhanced for unit_test framework autolink
#include <boost/test/included/unit_test.hpp>

#include <boost/checks/precheck.hpp>

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

#include <utility>

#include "alteration_test.hpp"
#include "transposition_test.hpp"

using namespace boost::checks;

template <typename functor>
unsigned int transposition(const functor &compute_checkdigit);

template <typename functor>
unsigned int alteration(const functor &compute_checkdigit , unsigned int number_of_position_to_test);

BOOST_AUTO_TEST_SUITE(use_cases_tests)

BOOST_AUTO_TEST_CASE(visa_tests)
{
  // Checkdigit validation tests.
  std::string visa_valid = "4417 1234 5678 9113";
  std::string visa_invalid = "5417 1234 5678 9113";
  std::string visa_low_size_failure = "417 1234 5678 9113"; // A missing digit '4'.
  std::string visa_big_size_failure = "44417 1234 5678 9113"; // An extra '4' digit.

  // Verify that check_amex(string) == check_amex(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(check_visa(make_precheck<digit>(visa_valid)), check_visa(visa_valid));
  BOOST_CHECK_EQUAL(check_visa(make_precheck<digit>(visa_invalid)), check_visa(visa_invalid));
  BOOST_CHECK_EQUAL(check_visa(make_precheck<digit>(visa_low_size_failure)), check_visa(visa_low_size_failure));
  BOOST_CHECK_EQUAL(check_visa(make_precheck<digit>(visa_big_size_failure)), check_visa(visa_big_size_failure));

  // Verify the check validity.
  BOOST_CHECK(check_visa(visa_valid));
  BOOST_CHECK_EQUAL(check_visa(visa_invalid), false);
  BOOST_CHECK_EQUAL(check_visa(visa_low_size_failure), false);
  BOOST_CHECK_EQUAL(check_visa(visa_big_size_failure), false);

  // Checkdigit computation tests.
  std::string visa_valid_without_checkdigit = "4417 1234 5678 911";
  std::string visa_invalid_without_checkdigit = "5417 1234 5678 911";
  std::string visa_size_error = "4417 1234 5678 91";
  size_t valid_checkdigit = 3;

  // Verify that compute_visa(make_precheck<digit>(string)) == compute_visa(string).
  BOOST_CHECK_EQUAL(compute_visa(make_precheck<digit>(visa_valid_without_checkdigit)), compute_visa(visa_valid_without_checkdigit));

  // Verify the check digit computation.
  BOOST_CHECK_EQUAL(compute_visa(visa_valid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_NE(compute_visa(visa_invalid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_EQUAL(compute_visa(visa_size_error), bad_sequence);
}

BOOST_AUTO_TEST_CASE(amex_tests)
{
  // Checkdigit validation tests.
  std::string amex_valid = "3782 822463 10005";
  std::string amex_low_size_failure = "378 822463 10005";
  std::string amex_big_size_failure = "33782 822463 10005";

  // Verify that check_amex(string) == check_amex(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(check_amex(amex_valid), check_amex(make_precheck<digit>(amex_valid)));
  BOOST_CHECK_EQUAL(check_amex(amex_low_size_failure), check_amex(make_precheck<digit>(amex_low_size_failure)));
  BOOST_CHECK_EQUAL(check_amex(amex_big_size_failure), check_amex(make_precheck<digit>(amex_big_size_failure)));

  // Verify the check validity.
  BOOST_CHECK(check_amex(amex_valid));
  BOOST_CHECK_EQUAL(check_amex(amex_low_size_failure), false);
  BOOST_CHECK_EQUAL(check_amex(amex_big_size_failure), false);

  // Checkdigit computation tests.
  std::string amex_valid_without_checkdigit = "3782 822463 1000";
  std::string amex_invalid_without_checkdigit = "4782 822463 1000";
  std::string amex_size_error = "782 822463 1000";
  size_t valid_checkdigit = 5;

  // Verify that compute_amex(make_precheck<digit>(string)) == compute_amex(string).
  BOOST_CHECK_EQUAL(compute_amex(make_precheck<digit>(amex_valid_without_checkdigit)), compute_amex(amex_valid_without_checkdigit));

  // Verify the check digit computation.
  BOOST_CHECK_EQUAL(compute_amex(amex_valid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_NE(compute_amex(amex_invalid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_EQUAL(compute_amex(amex_size_error), bad_sequence);
}

BOOST_AUTO_TEST_CASE(mastercard_tests)
{
  // Checkdigit validation tests.
  std::string mastercard_valid = "5105 1051 0510 5100";
  std::string mastercard_low_size_failure = "515 1051 0510 5100";
  std::string mastercard_big_size_failure = "51505 1051 0510 5100";

  //  Verify that check_mastercard(string) == check_mastercard(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(check_mastercard(mastercard_valid), check_mastercard(make_precheck<digit>(mastercard_valid)));
  BOOST_CHECK_EQUAL(check_mastercard(mastercard_low_size_failure), check_mastercard(make_precheck<digit>(mastercard_low_size_failure)));
  BOOST_CHECK_EQUAL(check_mastercard(mastercard_big_size_failure), check_mastercard(make_precheck<digit>(mastercard_big_size_failure)));

  // Verify the check validity.
  BOOST_CHECK(check_mastercard(mastercard_valid));
  BOOST_CHECK_EQUAL(check_mastercard(mastercard_low_size_failure), false);
  BOOST_CHECK_EQUAL(check_mastercard(mastercard_big_size_failure), false);

  // Checkdigit computation tests.
  std::string mastercard_valid_without_checkdigit = "5105 1051 0510 510";
  std::string mastercard_invalid_without_checkdigit = "5105 1051 0510 511"; // 511 instead of 510.
  std::string mastercard_size_error = "105 1051 0510 510";
  size_t valid_checkdigit = 0;
  
  // Verify that compute_mastercard(make_precheck<digit>(string)) == compute_mastercard(string).
  BOOST_CHECK_EQUAL(compute_mastercard(mastercard_valid_without_checkdigit), compute_mastercard(make_precheck<digit>(mastercard_valid_without_checkdigit)));

  // Verify the check digit computation.
  BOOST_CHECK_EQUAL(compute_mastercard(mastercard_valid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_NE(compute_mastercard(mastercard_invalid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_EQUAL(compute_mastercard(mastercard_size_error), bad_sequence);
}

BOOST_AUTO_TEST_CASE(ean13_tests)
{
  // Checkdigit validation tests.
  std::string ean13_valid = "5 412983 130028"; // Belgium beer "Bon secours".
  std::string ean13_low_size_failure = "05 412983 130028";
  std::string ean13_big_size_failure = "412983 130028";

  // Verify that check_ean13(string) == check_ean13(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(check_ean13(make_precheck<digit>(ean13_valid)), check_ean13(ean13_valid));
  BOOST_CHECK_EQUAL(check_ean13(make_precheck<digit>(ean13_low_size_failure)), check_ean13(ean13_low_size_failure));
  BOOST_CHECK_EQUAL(check_ean13(make_precheck<digit>(ean13_big_size_failure)), check_ean13(ean13_big_size_failure));

  // Verify the check validity
  BOOST_CHECK(check_ean13(ean13_valid));
  BOOST_CHECK_EQUAL(check_ean13(ean13_low_size_failure), false);
  BOOST_CHECK_EQUAL(check_ean13(ean13_big_size_failure), false);

  // Checkdigit computation tests.
  std::string ean13_valid_without_checkdigit = "5 412983 13002";
  std::string ean13_invalid_without_checkdigit = "1 412983 13002";
  std::string ean13_size_error = " 412983 13002";
  size_t valid_checkdigit = 8;

  // Verify that compute_ean13(string) == compute_ean13(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(compute_ean13(make_precheck<digit>(ean13_valid_without_checkdigit)), compute_ean13(ean13_valid_without_checkdigit));

  // Verify the check digit computation.
  BOOST_CHECK_EQUAL(compute_ean13(ean13_valid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_NE(compute_ean13(ean13_invalid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_EQUAL(compute_ean13(ean13_size_error), bad_sequence);
}


BOOST_AUTO_TEST_CASE(ean8_tests)
{
  // Checkdigit validation tests.
  std::string ean8_valid = "5449 1472"; // Bottle of Coke.
  std::string ean8_low_size_failure = "5449 472";
  std::string ean8_big_size_failure = "05449 1472";

  // Verify that check_ean8(string) == check_ean8(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(check_ean8(make_precheck<digit>(ean8_valid)), check_ean8(ean8_valid));
  BOOST_CHECK_EQUAL(check_ean8(make_precheck<digit>(ean8_low_size_failure)), check_ean8(ean8_low_size_failure));
  BOOST_CHECK_EQUAL(check_ean8(make_precheck<digit>(ean8_big_size_failure)), check_ean8(ean8_big_size_failure));

  // Verify the check validity.
  BOOST_CHECK(check_ean8(ean8_valid));
  BOOST_CHECK_EQUAL(check_ean8(ean8_low_size_failure), false);
  BOOST_CHECK_EQUAL(check_ean8(ean8_big_size_failure), false);

  // Checkdigit computation tests.
  std::string ean8_valid_without_checkdigit = "5449 147";
  std::string ean8_invalid_without_checkdigit = "1449 147";
  std::string ean8_size_error = "5449 14";
  size_t valid_checkdigit = 2;

  // Verify that compute_ean8(string) == compute_ean8(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(compute_ean8(make_precheck<digit>(ean8_valid_without_checkdigit)), compute_ean8(ean8_valid_without_checkdigit));

  // Verify the check digit computation.
  BOOST_CHECK_EQUAL(compute_ean8(ean8_valid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_NE(compute_ean8(ean8_invalid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_EQUAL(compute_ean8(ean8_size_error), bad_sequence);
}

BOOST_AUTO_TEST_CASE(upc_tests)
{
  // Checkdigit validation tests.
  std::string upca_valid = "036000291452"; // Box of tissues.
  std::string upca_invalid = "136000291452";
  std::string upca_low_size_failure = "36000291452";
  std::string upca_big_size_failure = "0036000291452";

  // Verify that check_upc(string) == check_upc(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(check_upca(make_precheck<digit>(upca_valid)), check_upca(upca_valid));
  BOOST_CHECK_EQUAL(check_upca(make_precheck<digit>(upca_invalid)), check_upca(upca_invalid));
  BOOST_CHECK_EQUAL(check_upca(make_precheck<digit>(upca_low_size_failure)), check_upca(upca_low_size_failure));
  BOOST_CHECK_EQUAL(check_upca(make_precheck<digit>(upca_big_size_failure)), check_upca(upca_big_size_failure));

  // Verify the check validity.
  BOOST_CHECK(check_upca(upca_valid));
  BOOST_CHECK_EQUAL(check_upca(upca_invalid), false);
  BOOST_CHECK_EQUAL(check_upca(upca_low_size_failure), false);
  BOOST_CHECK_EQUAL(check_upca(upca_big_size_failure), false);

  // Checkdigit computation tests.
  std::string upca_valid_without_checkdigit = "03600029145";
  std::string upca_invalid_without_checkdigit = "13600029145";
  std::string upca_size_error = "0360002914";
  size_t valid_checkdigit = 2;
  
  // Verify that compute_ean13(string) == compute_ean13(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(compute_upca(make_precheck<digit>(upca_valid_without_checkdigit)), compute_upca(upca_valid_without_checkdigit));

  // Verify the check digit computation.
  BOOST_CHECK_EQUAL(compute_upca(upca_valid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_NE(compute_upca(upca_invalid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_EQUAL(compute_upca(upca_size_error), bad_sequence);
}

BOOST_AUTO_TEST_CASE(isbn13_tests)
{
  // Checkdigit validation tests.
  std::string isbn13_valid = "978-0-13-235088-4"; // Clean Code: a handbook of agile software craftsmanship, Robert C. Martin.
  std::string isbn13_not_valid = "979-0-13-235088-4";
  std::string isbn13_low_size_failure = "978--13-235088-4";
  std::string isbn13_big_size_failure = "978-00-13-235088-4";

  // Verify that check_isbn13(string) == check_isbn13(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(check_isbn13(make_precheck<digit>(isbn13_valid)), check_isbn13(isbn13_valid));
  BOOST_CHECK_EQUAL(check_isbn13(make_precheck<digit>(isbn13_not_valid)), check_isbn13(isbn13_not_valid));
  BOOST_CHECK_EQUAL(check_isbn13(make_precheck<digit>(isbn13_low_size_failure)), check_isbn13(isbn13_low_size_failure));
  BOOST_CHECK_EQUAL(check_isbn13(make_precheck<digit>(isbn13_big_size_failure)), check_isbn13(isbn13_big_size_failure));

  // Verify the check validity.
  BOOST_CHECK(check_isbn13(isbn13_valid));
  BOOST_CHECK_EQUAL(check_isbn13(isbn13_not_valid), false);
  BOOST_CHECK_EQUAL(check_isbn13(isbn13_low_size_failure), false);
  BOOST_CHECK_EQUAL(check_isbn13(isbn13_big_size_failure), false);

  // Checkdigit computation tests.
  std::string isbn13_valid_without_checkdigit = "978-0-13-235088-";
  std::string isbn13_not_valid_without_checkdigit = "979-0-13-235088-"; // 979
  std::string isbn13_size_error = "978-0-13-35088-";

  size_t valid_checkdigit = 4;
  
  // Verify that compute_isbn13(string) == compute_isbn13(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(compute_isbn13(make_precheck<digit>(isbn13_valid_without_checkdigit)), compute_isbn13(isbn13_valid_without_checkdigit));

  // Verify the check digit computation.
  BOOST_CHECK_EQUAL(compute_isbn13(isbn13_valid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_NE(compute_isbn13(isbn13_not_valid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_EQUAL(compute_isbn13(isbn13_size_error), bad_sequence);
}

BOOST_AUTO_TEST_CASE(isbn10_tests)
{
  // Checkdigit validation tests.
  std::string isbn10_valid = "0-201-70073-5"; // The C++ Programming Language, Special Edition, Bjarne Stroustrup.
  std::string isbn10_invalid = "-201-70073-5";
  std::string isbn10_low_size_failure = "00-201-70073-5";
  std::string isbn10_big_size_failure = "-201-70073-5";

  // Verify that check_isbn10(string) == check_isbn10(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(check_isbn10(make_precheck<digitx>(isbn10_valid)), check_isbn10(isbn10_valid));
  BOOST_CHECK_EQUAL(check_isbn10(make_precheck<digitx>(isbn10_invalid)), check_isbn10(isbn10_invalid));
  BOOST_CHECK_EQUAL(check_isbn10(make_precheck<digitx>(isbn10_low_size_failure)), check_isbn10(isbn10_low_size_failure));
  BOOST_CHECK_EQUAL(check_isbn10(make_precheck<digitx>(isbn10_big_size_failure)), check_isbn10(isbn10_big_size_failure));

  // Verify the check validity.
  BOOST_CHECK(check_isbn10(isbn10_valid));
  BOOST_CHECK_EQUAL(check_isbn10(isbn10_invalid), false);
  BOOST_CHECK_EQUAL(check_isbn10(isbn10_low_size_failure), false);
  BOOST_CHECK_EQUAL(check_isbn10(isbn10_big_size_failure), false);

  // Checkdigit computation tests.
  std::string isbn10_valid_without_checkdigit = "0-201-70073-";
  std::string isbn10_invalid_without_checkdigit = "1-201-70073-";
  std::string isbn10_size_error = "0-20-70073-"; // 20 instead of 201
  size_t valid_checkdigit = 5;

  // Verify that compute_isbn10(string) == compute_isbn10(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(compute_isbn10(make_precheck<digitx>(isbn10_valid_without_checkdigit)), compute_isbn10(isbn10_valid_without_checkdigit));

  // Verify the check digit computation.
  BOOST_CHECK_EQUAL(compute_isbn10(isbn10_valid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_NE(compute_isbn10(isbn10_invalid_without_checkdigit), valid_checkdigit);
  BOOST_CHECK_EQUAL(compute_isbn10(isbn10_size_error), bad_sequence);
}

BOOST_AUTO_TEST_CASE(mod97_10_tests)
{
  // Checkdigit validation tests.
  std::string mod97_10_valid = "510007547061111462"; // From a Belgian IBAN
  std::string mod97_10_not_valid = "511007547061111462";
  std::string mod97_10_low_size_failure = "51007547061111462";
  std::string mod97_10_big_size_failure = "5100007547061111462";

  // Verify that check_mod97_10(string) == check_mod97_10(make_precheck<digit>(string)).
  BOOST_CHECK(check_mod97_10(make_precheck<digit>(mod97_10_valid)));
  BOOST_CHECK_EQUAL(check_mod97_10(make_precheck<digit>(mod97_10_not_valid)), check_mod97_10(mod97_10_not_valid));
  BOOST_CHECK_EQUAL(check_mod97_10(make_precheck<digit>(mod97_10_low_size_failure)), check_mod97_10(mod97_10_low_size_failure));
  BOOST_CHECK_EQUAL(check_mod97_10(make_precheck<digit>(mod97_10_big_size_failure)), check_mod97_10(mod97_10_big_size_failure));

  // Verify the check validity.
  BOOST_CHECK(check_mod97_10(mod97_10_valid));
  BOOST_CHECK_EQUAL(check_mod97_10(mod97_10_not_valid), false);
  BOOST_CHECK_EQUAL(check_mod97_10(mod97_10_low_size_failure), false);
  BOOST_CHECK_EQUAL(check_mod97_10(mod97_10_big_size_failure), false);

  // Checkdigit computation tests.
  std::string mod97_10_valid_without_checkdigits = "5100075470611114";
  std::string mod97_10_invalid_without_checkdigits = "5110075470611114";
  std::string mod97_10_size_error = "51100754706111141";

  size_t checkdigits = 62;

  // Verify that compute_isbn10(string) == compute_isbn10(make_precheck<digit>(string)).
  BOOST_CHECK_EQUAL(compute_mod97_10(make_precheck<digit>(mod97_10_valid_without_checkdigits)), compute_mod97_10(mod97_10_valid_without_checkdigits));
  BOOST_CHECK_EQUAL(compute_mod97_10(make_precheck<digit>(mod97_10_invalid_without_checkdigits)), compute_mod97_10(mod97_10_invalid_without_checkdigits));

  // Verify the check digit computation.
  BOOST_CHECK_EQUAL(compute_mod97_10(mod97_10_valid_without_checkdigits), checkdigits);
  BOOST_CHECK_NE(compute_mod97_10(mod97_10_invalid_without_checkdigits), checkdigits);
  BOOST_CHECK_EQUAL(compute_mod97_10<16>(mod97_10_size_error), bad_sequence);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(technical_tests)

struct luhn_functor
{
  template <typename range>
  typename boost::range_value<range>::type operator()(const range &check_range)const
  {
    return compute_luhn(make_precheck<digit>(check_range));
  }
};

struct verhoeff_functor
{
  template <typename range>
  typename boost::range_value<range>::type operator()(const range &check_range)const
  {
    return compute_verhoeff(make_precheck<digit>(check_range));
  }
};

struct modulus11_functor
{
  template <typename range>
  typename boost::range_value<range>::type operator()(const range &check_range)const
  {
    return compute_modulus11(make_precheck<digitx>(check_range));
  }
};

BOOST_AUTO_TEST_CASE(luhn_test)
{
  unsigned int transpositions_failures = transposition(luhn_functor());
  BOOST_CHECK_MESSAGE(transpositions_failures == 2, "" <<(90-transpositions_failures)<< " caught on 90.");

  unsigned int alterations_failures = alteration(luhn_functor(), 2);
  BOOST_CHECK_MESSAGE(alterations_failures == 0, "" <<(18-alterations_failures)<< " caught on 18.");
}

BOOST_AUTO_TEST_CASE(verhoeff_test)
{
  unsigned int transpositions_failures = transposition(verhoeff_functor());
  BOOST_CHECK_MESSAGE(transpositions_failures == 0, "" <<(90-transpositions_failures)<< " caught on 90.");

  unsigned int alterations_failures = alteration(verhoeff_functor(), 20);
  BOOST_CHECK_MESSAGE(alterations_failures == 0, "" <<(180-alterations_failures)<< " caught on 180.");
}

BOOST_AUTO_TEST_CASE(modulus11_test)
{
  unsigned int transpositions_failures = transposition(modulus11_functor());
  BOOST_CHECK_MESSAGE(transpositions_failures == 0, "" <<(90-transpositions_failures)<< " caught on 90.");

  unsigned int alterations_failures = alteration(modulus11_functor(), 10);
  BOOST_CHECK_MESSAGE(alterations_failures == 0, "" <<(90-alterations_failures)<< " caught on 90.");
}

BOOST_AUTO_TEST_SUITE_END()
