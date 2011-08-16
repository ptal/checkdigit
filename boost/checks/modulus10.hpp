//  Boost checks/modulus10.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_MOD10_HPP
#define BOOST_CHECKS_MOD10_HPP

#include <boost/lexical_cast.hpp>
#include <boost/checks/traduction_exception.hpp>
#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/weighted_sum.hpp>

namespace boost{
  namespace checks{

template <typename mod10_weight, typename iteration_sense, unsigned int number_of_virtual_value_skipped = 0>
struct modulus10_algorithm : boost::checks::weighted_sum_algorithm<mod10_weight, iteration_sense, number_of_virtual_value_skipped>
{
  static bool validate_checksum(int checksum)
  {
    return !(checksum % 10) ;
  }

  template <typename checkdigit>
  static typename checkdigit compute_checkdigit( int checksum )
  {
    try{
      return boost::lexical_cast<checkdigit>((10 - checksum % 10) % 10 ) ;
    }catch( boost::bad_lexical_cast ){
      throw boost::checks::traduction_exception() ;
    }
  }
};

}}

#endif //BOOST_CHECKS_MOD10_HPP