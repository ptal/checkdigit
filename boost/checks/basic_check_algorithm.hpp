//  Boost checks/basic_check_algorithm.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file basic_check_algorithm.hpp
    \brief This file provides a class that should be used as an "interface" because most of the static functions should be re-implemented using inheritance.

    \remarks The class implements static functions that often common to many algorithms.
*/

#ifndef BOOST_CHECKS_BASIC_CHECK_ALGO_HPP
#define BOOST_CHECKS_BASIC_CHECK_ALGO_HPP

#ifdef _MSC_VER
    #pragma once
#endif


#include <boost/lexical_cast.hpp>
#include <boost/checks/translation_exception.hpp>
#include <boost/checks/iteration_sense.hpp>

namespace boost{
  namespace checks{

/*! \class basic_check_algorithm
    \brief The main check algorithm class that provides every static functions that can be overloaded.\n Most of the functions must be re-implemented to have the desired behavior.

    \tparam iteration_sense must meet the iteration_sense concept requirements.
    \tparam number_of_virtual_value_skipped Help functions to provide same behavior on sequence with and without checkdigits. No "real" value in the sequence will be skipped.
*/
template <typename iteration_sense, unsigned int number_of_virtual_value_skipped = 0>
struct basic_check_algorithm
{
  /*!
    \brief This is the sense of the iteration (begins with the right or the leftmost value).
  */
  typedef iteration_sense iteration_sense ;

  /*!
    \brief translate a value of the sequence into an integer valid value.

    \tparam value is the type of a value in the sequence.
    \param current_value is the current value analysed in the sequence that must be translated.
    \param valid_value_counter is the number of valid value already counted (the current value is not included).\n This is also the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).

    \throws boost::checks::translation_exception is throwed if the translation of current_value failed.\n This will automaticaly throws if the value is not a digit (0 <= i < 11).

    \returns the translation of the current value in the range [0..9].
*/
  template <typename value>
  static int translate_to_valid_value(const value &current_value, const unsigned int valid_value_counter )
  {
    int valid_value = 0;
    try{
      valid_value = boost::lexical_cast<int>( current_value ) ;
      if( valid_value > 9)
        throw boost::checks::translation_exception() ;
    }catch( boost::bad_lexical_cast ){
      throw boost::checks::translation_exception() ;
    }
    return valid_value ;
  }

  /*!
    \brief Validate the checksum.

    \param checksum is the checksum to validate.

    \returns true.

    \remarks This function should be overload if you want to check a sequence.
  */
  static bool validate_checksum(int checksum)
  {
    return true;
  }

  /*!
    \brief Compute the check digit of a sequence.

    \pre The type checkdigit must provides the default initialisation feature.

    \tparam checkdigit is the type of the check digit desired.
    \param checksum is the checksum used to extract the check digit.

    \returns default initialized value of checkdigit.

    \remarks This function should be overload if you want to compute the check digit of a sequence.
  */
  template <typename checkdigit>
  static typename checkdigit compute_checkdigit( int checksum )
  {
    return checkdigit() ;
  }  

  /*!
    \brief Compute the check digit(s) of a sequence.

    \pre checkdigits must be a valid initialized iterator.

    \tparam checkdigits_iter must meet the OutputIterator requirements.
    \param checksum is the checksum used to extract the check digit(s).
    \param checkdigits is the iterator in which the check digit(s) will be written.

    \returns checkdigits.

    \remarks This function should be overload if you want your algorithm compute more than one check digit (through it works for one check digit too).
  */
  template <typename checkdigits_iter>
  static typename checkdigits_iter compute_multicheckdigit( int checksum, checkdigits_iter checkdigits )
  {
    return checkdigits ;
  }

  /*!
    \brief Compute an operation on the checksum with the current valid value
    \post Do nothing. The checksum is inchanged.

    \param current_valid_value is the current valid value analysed.
    \param valid_value_counter is the number of valid value already counted (the current value is not included).\n This is also the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).
    \param checksum is the current checksum.

    \remarks This function should be overload if you want to calculate the checksum of a sequence.
  */
  static void operate_on_valid_value( const int current_valid_value, const unsigned int valid_value_counter, int &checksum )
  {
  }

  /*!
    \brief Filtering of a valid value according to its position.

    \post Do nothing.

    \param current_valid_value is the current valid value analysed.
    \param current_value_position is the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).

    \remarks This function should be overload if you want to filter the values with their positions.
  */
  static void filter_valid_value_with_pos(const unsigned int current_valid_value, const unsigned int current_value_position )
  {
  }

  /*! \class checkdigit
      \brief Template rebinding class used to define the type of the check digit(s) of check_range.

      \tparam check_range The type of the sequence to check.

      \remarks This function should be overload if you want to change the type of the check digit.
  */
  template <typename check_range>
  struct checkdigit
  {
    typedef typename boost::range_value<check_range>::type type;
  };
};


}}
#endif //BOOST_CHECKS_BASIC_CHECK_ALGO_HPP