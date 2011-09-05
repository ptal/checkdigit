//  Boost checks/ean.hpp header file
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate an European Article Numbering (EAN) of size 8 or 13.
*/

#ifndef BOOST_CHECKS_EAN_HPP
#define BOOST_CHECKS_EAN_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/basic_checks.hpp>
#include <boost/checks/modulus10.hpp>

/*!
  \brief This macro defines the size of an EAN-13 (13).
*/
#define EAN13_SIZE 13
/*!
  \brief This macro defines the size of an EAN-13 without its check digit (12).
*/
#define EAN13_SIZE_WITHOUT_CHECKDIGIT 12
/*!
  \brief This macro defines the size of an EAN-8 (8).
*/
#define EAN8_SIZE 8
/*!
  \brief This macro defines the size of a EAN-8 without its check digit (7).
*/
#define EAN8_SIZE_WITHOUT_CHECKDIGIT 7

namespace boost {
    namespace checks{

/*!
  \brief This is the weight used by EAN system.
*/
typedef boost::checks::weight<1,3> ean_weight ;
/*!
  \brief This is the running sense or direction to check an EAN.
*/
typedef boost::checks::rightmost ean_sense ;

/*!
  \brief This is the type of the EAN algorithm for validating a check digit.
*/
typedef boost::checks::modulus10_algorithm< ean_weight, ean_sense, 0> ean_check_algorithm ;
/*!
  \brief This is the type of the EAN algorithm for computing a check digit.
*/
typedef boost::checks::modulus10_algorithm< ean_weight, ean_sense, 1> ean_compute_algorithm ;

/*!
    \brief Validate a sequence according to the ean_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly EAN13_SIZE digits.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename check_range>
bool check_ean13 (const check_range& check_seq)
{
  return boost::checks::check_sequence<ean_check_algorithm, EAN13_SIZE> ( check_seq ) ;
}

/*!
    \brief Calculate the check digit of a sequence according to the ean_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly EAN13_SIZE_WITHOUT_CHECKDIGIT digits.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename check_range>
typename boost::checks::ean_compute_algorithm::checkdigit<check_range>::type compute_ean13 (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<ean_compute_algorithm, EAN13_SIZE_WITHOUT_CHECKDIGIT> ( check_seq ) ;
}

/*!
    \brief Validate a sequence according to the ean_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly EAN8_SIZE digits.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename check_range>
bool check_ean8 (const check_range& check_seq)
{
  return boost::checks::check_sequence<ean_check_algorithm, EAN8_SIZE> ( check_seq ) ;
}

/*!
    \brief Calculate the check digit of a sequence according to the ean_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly EAN8_SIZE_WITHOUT_CHECKDIGIT digits.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename check_range>
typename boost::checks::ean_compute_algorithm::checkdigit<check_range>::type compute_ean8 (const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<ean_compute_algorithm, EAN8_SIZE_WITHOUT_CHECKDIGIT> ( check_seq ) ;
}


}} // namespace boost   namespace checks
#endif // BOOST_CHECKS_EAN_HPP
