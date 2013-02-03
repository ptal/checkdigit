// Copyright Pierre Talbot 2013.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
//(See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/doc/libs/1_46_1/libs/test/doc/html/utf/testing-tools/reference.html

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE "Check Test Suite"
#define BOOST_LIB_DIAGNOSTIC "on"// Show library file details.

#include <boost/test/unit_test.hpp> // Enhanced for unit_test framework autolink
#include <boost/test/included/unit_test.hpp>

#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/checks/checkdigit.hpp>
#include <boost/checks/modulus10.hpp>
#include <boost/checks/modulus11.hpp>
#include <boost/checks/modulus97.hpp>
#include <boost/checks/type_adaptor.hpp>

BOOST_AUTO_TEST_SUITE(core_tests)

BOOST_AUTO_TEST_CASE(mod10_checkdigit_test)
{
  using namespace boost::checks;
  mod10_basic_checkdigit c;

  char results_expected[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  for(size_t checksum=0; checksum < 30; ++checksum)
  { 
    BOOST_CHECK_EQUAL(c(checksum), results_expected[checksum%10]);
  }
}

BOOST_AUTO_TEST_CASE(mod10_inv_checkdigit_test)
{
  using namespace boost::checks;
  mod10_inv_checkdigit c;

  char results_expected[] = {'0', '9', '8', '7', '6', '5', '4', '3', '2', '1'};

  for(size_t checksum=0; checksum < 30; ++checksum)
  { 
    BOOST_CHECK_EQUAL(c(checksum), results_expected[checksum%10]);
  }
}

BOOST_AUTO_TEST_CASE(mod11_checkdigit_test)
{
  using namespace boost::checks;
  mod11_basic_checkdigit c;

  char results_expected[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'X'};

  for(size_t checksum=0; checksum < 33; ++checksum)
  {
    BOOST_CHECK_EQUAL(c(checksum), results_expected[checksum%11]);
  }
}

BOOST_AUTO_TEST_CASE(mod11_inv_checkdigit_test)
{
  using namespace boost::checks;
  mod11_inv_checkdigit c;

  char results_expected[] = {'0', 'X', '9', '8', '7', '6', '5', '4', '3', '2', '1'};

  for(size_t checksum=0; checksum < 33; ++checksum)
  {
    BOOST_CHECK_EQUAL(c(checksum), results_expected[checksum%11]);
  }
}

BOOST_AUTO_TEST_CASE(mod97_10_checkdigit_test)
{
  using namespace boost::checks;
  mod97_10_checkdigit c;

  for(size_t checksum=0, res = 98; checksum < 100; ++checksum, --res)
  {
    if(res < 2) res = 98;
    std::string result_expected = boost::lexical_cast<std::string>(res);
    BOOST_CHECK_EQUAL(c(checksum), result_expected);
  }
}

BOOST_AUTO_TEST_CASE(type_adaptor_test)
{
  using namespace boost::checks;
  BOOST_CHECK_EQUAL(mod11_basic_checkdigit::position_value, size_t(0));
  BOOST_CHECK_EQUAL(mod11_basic_checkdigit::size_value, size_t(1));

  typedef type_adaptor<mod11_basic_checkdigit, checkdigit_pos_tag, boost::mpl::size_t<10> >::type mod11_pos_10;
  typedef type_adaptor<mod11_basic_checkdigit, checkdigit_size_tag, boost::mpl::size_t<3> >::type mod11_size_3;

  BOOST_CHECK_EQUAL(mod11_pos_10::position_value, size_t(10));
  BOOST_CHECK_EQUAL(mod11_size_3::size_value, size_t(3));

  typedef type_adaptor<mod11_basic_checkdigit, checkdigit_encoder_tag, mod10_basic_encoder>::type mod11_mod10_encoder;
  typedef type_adaptor<mod11_basic_checkdigit, checkdigit_processor_tag, mod11_inv_basic>::type mod11_inv_type;

  BOOST_MPL_ASSERT((boost::is_same<mod11_mod10_encoder::encoder_type, mod10_basic_encoder>));
  BOOST_MPL_ASSERT((boost::is_same<mod11_inv_type::processor_type, mod11_inv_basic>));
}

BOOST_AUTO_TEST_SUITE_END()