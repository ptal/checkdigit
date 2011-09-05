//  Boost checks/modulus10.hpp header file
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate classic modulus 10 checksum.
*/

#ifndef BOOST_CHECKS_MOD10_HPP
#define BOOST_CHECKS_MOD10_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/lexical_cast.hpp>
#include <boost/checks/translation_exception.hpp>
#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/weighted_sum.hpp>

namespace boost{
  namespace checks{

/*! \class modulus10_algorithm
    \brief This class can be used to compute or validate checksum with a basic modulus 10.

    \tparam mod10_weight must meet the weight concept requirements.
    \tparam iteration_sense must meet the iteration_sense concept requirements.
    \tparam number_of_virtual_value_skipped Help functions to provide same behavior on sequence with and without check digits. No "real" value in the sequence will be skipped.
*/
template <typename mod10_weight, typename iteration_sense, unsigned int number_of_virtual_value_skipped = 0>
struct modulus10_algorithm : boost::checks::weighted_sum_algorithm<mod10_weight, iteration_sense, number_of_virtual_value_skipped>
{
  /*!
    \brief Validate a checksum with a simple modulus 10.

    \param checksum is the checksum to validate.

    \returns @c true if the checksum is correct, @c false otherwise.
  */
  static bool validate_checksum(int checksum)
  {
    return !(checksum % 10) ;
  }

  /*!
    \brief Compute the check digit with a simple modulus 10.

    \tparam checkdigit is the type of the check digit desired.
    \param checksum is the checksum used to extract the check digit.

    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The modulus 10 check digit of checksum.
  */
  template <typename checkdigit>
  static typename checkdigit compute_checkdigit( int checksum )
  {
    try{
      return boost::lexical_cast<checkdigit>((10 - checksum % 10) % 10 ) ;
    }catch( boost::bad_lexical_cast ){
      throw boost::checks::translation_exception() ;
    }
  }
};

}}  // namespace boost   namespace checks

#endif //BOOST_CHECKS_MOD10_HPP
