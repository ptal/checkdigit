//  Boost checks/modulus97.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_MOD97_HPP
#define BOOST_CHECKS_MOD97_HPP

#include <boost/preprocessor/repetition.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/checks/translation_exception.hpp>
#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/weighted_sum.hpp>

namespace boost{
  namespace checks{

template <typename mod97_weight, typename iteration_sense, unsigned int number_of_virtual_value_skipped = 0>
struct modulus97_algorithm : boost::checks::weighted_sum_algorithm<mod97_weight, iteration_sense, number_of_virtual_value_skipped>
{
  static bool validate_checksum(int checksum)
  {
    return checksum % 97 == 1 ;
  }

  template <typename checkdigits_iter>
  static typename checkdigits_iter compute_multicheckdigit( int checksum, checkdigits_iter checkdigits )
  {
    unsigned int mod97_checkdigits = 98 - (checksum % 97) ;

    try{
      *checkdigits = boost::lexical_cast<checkdigits_iter::value_type>(mod97_checkdigits / 10) ; 
      ++checkdigits;
      *checkdigits = boost::lexical_cast<checkdigits_iter::value_type>(mod97_checkdigits % 10) ; 
      ++checkdigits;
    }
    catch( boost::bad_lexical_cast ){
      throw boost::checks::translation_exception() ;
    }
    return checkdigits;
  }
};

// cf. ISO/IEC 7064:2003 for the mod97-10 algorithm.
template <unsigned int weight_value>
struct make_mod97_weight
{
  static const unsigned int value = weight_value ;
  typedef make_mod97_weight<weight_value * 10 % 97> next ;
};
template<>
struct make_mod97_weight<68>
{
  static const unsigned int value = 68 ;
  typedef make_mod97_weight type ;
};
#define NEXT(z,n,unused) next::
#define MOD97_make_weight(z, n ,unused) make_mod97_weight<1>::BOOST_PP_REPEAT(n, NEXT, ~)value
typedef boost::checks::weight< BOOST_PP_ENUM(96, MOD97_make_weight, ~) > mod97_10_weight ;

typedef boost::checks::rightmost mod97_10_sense ;

typedef modulus97_algorithm< mod97_10_weight, mod97_10_sense, 0 > mod97_10_check_algorithm ;
typedef modulus97_algorithm< mod97_10_weight, mod97_10_sense, 2 > mod97_10_compute_algorithm ;

template <size_t size_expected, typename check_range>
bool check_mod97_10 (const check_range& check_seq)
{
  return boost::checks::check_sequence<mod97_10_check_algorithm, size_expected> ( check_seq ) ;
}

template <typename check_range>
bool check_mod97_10 (const check_range& check_seq)
{
  return boost::checks::check_sequence<mod97_10_check_algorithm> ( check_seq ) ;
}

template <size_t size_expected, typename check_range, typename checkdigits_iter>
typename checkdigits_iter compute_mod97_10 (const check_range& check_seq, checkdigits_iter mod97_checkdigits)
{
  return boost::checks::compute_multicheckdigit<mod97_10_compute_algorithm, size_expected> ( check_seq, mod97_checkdigits ) ;
}

template <typename check_range, typename checkdigits_iter>
typename checkdigits_iter compute_mod97_10 (const check_range& check_seq, checkdigits_iter mod97_checkdigits)
{
  return boost::checks::compute_multicheckdigit<mod97_10_compute_algorithm> ( check_seq, mod97_checkdigits ) ;
}


}}
#endif //BOOST_CHECKS_MOD97_HPP