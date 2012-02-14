//  Boost checks/basic_check_algorithm.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011 - 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides a class that should be used as an "interface" because most of the static functions should be re-implemented using inheritance.

    \remarks The class implements static functions that are common to many algorithms.
*/

#ifndef BOOST_CHECKS_BASIC_CHECK_ALGO_HPP
#define BOOST_CHECKS_BASIC_CHECK_ALGO_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef> // std::size_t
#include <boost/checks/filter.hpp>
#include <boost/checks/conversion.hpp>
#include <boost/checks/prechecksum.hpp>
#include <boost/range.hpp>

namespace boost{
  namespace checks{
  

typedef prechecksum<digit_filter, chartodigit> digit_prechecksum; 

typedef prechecksum<digitx_filter, chartodigitx> digitx_prechecksum;

/*! \class basic_check_algorithm
    \brief The main check algorithm class that provides every static function that can be overloaded.\n Most of the functions must be re-implemented to have the desired behavior.

    \tparam traversal_direction must meet the iterator_direction concept requirements.
    \tparam checkdigit_size Helper functions to provide the same behavior on sequence with and without checkdigits. No "real" value in the sequence will be skipped.
*/
struct basic_check_algorithm
{
  /*!
    \brief Validate the checksum.

    \param checksum is the checksum to validate.

    \returns @c true always (unless overloaded to check a sequence).

    \remarks This function should be overloaded if you want to check a sequence.
  */
  static bool validate_checksum(std::size_t checksum)
  {
    return true;
  }

  /*!
    \brief Compute the check digit of a sequence.

    \pre The type checkdigit must provides the default initialisation feature.

    \tparam checkdigit is the type of the check digit desired.
    \param checksum is the checksum used to extract the check digit.

    \returns default initialized value of checkdigit.

    \remarks This function should be overloaded if you want to compute the check digit of a sequence.
  */
  static std::size_t compute_checkdigit(std::size_t checksum)
  {
    return std::size_t();
  }

  /*!
    \brief Compute the check digit(s) of a sequence.

    \pre checkdigits must be a valid initialized iterator.

    \tparam checkdigits_iter must meet the OutputIterator requirements.
    \param checksum is the checksum used to extract the check digit(s).
    \param checkdigits is the iterator with which the check digit(s) will be written.

    \returns checkdigits.

    \remarks This function should be overloaded if you want your algorithm to compute more than one check digit (through it works for just one check digit too).
  */
  static std::pair<std::size_t, std::size_t> compute_multicheckdigit(std::size_t checksum)
  {
    return std::pair<std::size_t, std::size_t>();
  }

  /*!
    \brief Compute an operation on the checksum with the current valid value.
    \post Do nothing. The checksum is unchanged.

    \param current_valid_value is the current valid value analysed.
    \param valid_value_counter is the number of valid value(s) already counted (the current value is not included).\n This is also the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).
    \param checksum is the current checksum.

    \remarks This function should be overloaded if you want to calculate the checksum of a sequence.
  */
  static std::size_t process(std::size_t, std::size_t, std::size_t)
  {
    return std::size_t();
  }

};


}} // namespace boost  namespace checks

#endif //BOOST_CHECKS_BASIC_CHECK_ALGO_HPP
