//  Boost checks/verhoeff.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_VERHOEFF_INCLUDED
#define BOOST_VERHOEFF_INCLUDED

#include <boost/lexical_cast.hpp>
#include <boost/checks/traduction_exception.hpp>
#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/basic_checks.hpp>
#include <boost/checks/basic_check_algorithm.hpp>

namespace boost {
    namespace checks{

typedef boost::checks::rightmost verhoeff_iteration_sense ;

template <unsigned int number_of_virtual_value_skipped = 0>
struct verhoeff_algorithm : boost::checks::basic_check_algorithm<verhoeff_iteration_sense, number_of_virtual_value_skipped>
{
  static void operate_on_valid_value( const int current_valid_value, const unsigned int valid_value_counter, int &checksum )
  {
    static const unsigned int d[10][10] =
    {
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
      { 1, 2, 3, 4, 0, 6, 7, 8, 9, 5 },
      { 2, 3, 4, 0, 1, 7, 8, 9, 5, 6 },
      { 3, 4, 0, 1, 2, 8, 9, 5, 6, 7 },
      { 4, 0, 1, 2, 3, 9, 5, 6, 7, 8 },
      { 5, 9, 8, 7, 6, 0, 4, 3, 2, 1 },
      { 6, 5, 9, 8, 7, 1, 0, 4, 3, 2 },
      { 7, 6, 5, 9, 8, 2, 1, 0, 4, 3 },
      { 8, 7, 6, 5, 9, 3, 2, 1, 0, 4 },
      { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }
    };

    static const unsigned int p[8][10] =
    {
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
      { 1, 5, 7, 6, 2, 8, 3, 0, 9, 4 },
      { 5, 8, 0, 3, 7, 9, 6, 1, 4, 2 },
      { 8, 9, 1, 6, 0, 4, 3, 5, 2, 7 },
      { 9, 4, 5, 3, 1, 2, 6, 8, 7, 0 },
      { 4, 2, 8, 6, 5, 7, 3, 9, 0, 1 },
      { 2, 7, 9, 3, 8, 0, 6, 4, 1, 5 },
      { 7, 0, 4, 6, 9, 1, 3, 2, 5, 8 }
    };

    checksum = d[ checksum ][ p[ (valid_value_counter + number_of_virtual_value_skipped) % 8 ][ current_valid_value ] ] ;
  }

  static bool validate_checksum(int checksum)
  {
    return !checksum ;
  }

  template <typename checkdigit>
  static typename checkdigit compute_checkdigit( int checksum )
  {
    static const unsigned int inv[] = { 0, 4, 3, 2, 1, 5, 6, 7, 8, 9 } ;

    try
    {
      return boost::lexical_cast<checkdigit>( inv[checksum] ) ;
    }
    catch( boost::bad_lexical_cast )
    {
      throw boost::checks::traduction_exception() ;
    }
  }
};


typedef verhoeff_algorithm<0> verhoeff_check_algorithm ;
typedef verhoeff_algorithm<1> verhoeff_compute_algorithm ;

template <size_t size_expected, typename check_range>
bool check_verhoeff (const check_range& check_seq)
{
  return boost::checks::check_sequence<verhoeff_check_algorithm, size_expected> ( check_seq ) ;
}

template <typename check_range>
bool check_verhoeff (const check_range& check_seq)
{
  return boost::checks::check_sequence<verhoeff_check_algorithm> ( check_seq ) ;
}

template <size_t size_expected, typename check_range>
typename boost::checks::verhoeff_compute_algorithm::checkdigit<check_range>::type compute_verhoeff (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<verhoeff_compute_algorithm, size_expected> ( check_seq ) ;
}

template <typename check_range>
typename boost::checks::verhoeff_compute_algorithm::checkdigit<check_range>::type compute_verhoeff (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<verhoeff_compute_algorithm> ( check_seq ) ;
}

} // namespace checks
} // namespace boost

#endif
