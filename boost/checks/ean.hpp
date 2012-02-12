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
#include <boost/checks/checkdigit.hpp>
#include <boost/checks/basic_checks.hpp>
#include <boost/checks/modulus10.hpp>

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>

/*!
  \brief This macro defines the size of an EAN-13 (13).
*/
#define EAN13_SIZE 13
/*!
  \brief This macro defines the size of an EAN-8 (8).
*/
#define EAN8_SIZE 8

namespace boost {
    namespace checks{

/*!
  \brief This is the weight used by EAN system.
*/
typedef boost::checks::weight<1,3> ean_weight;
/*!
  \brief This is the type of the EAN algorithm.
*/
typedef boost::checks::modulus10_algorithm<ean_weight> ean_algorithm;

/*!
    \brief Validate a sequence according to the ean_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly EAN13_SIZE digits.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename check_range>
bool check_ean13(const check_range& check_seq)
{
  return boost::checks::check_sequence<ean_algorithm, EAN13_SIZE> (boost::rbegin(check_seq), boost::rend(check_seq));
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
typename boost::range_value<check_range>::type compute_ean13(const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<ean_algorithm, EAN13_SIZE, boost::checks::basic_checkdigit>(boost::rbegin(check_seq), boost::rend(check_seq));
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
  return boost::checks::check_sequence<ean_algorithm, EAN8_SIZE>(boost::rbegin(check_seq), boost::rend(check_seq));
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
typename boost::range_value<check_range>::type compute_ean8(const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<ean_algorithm, EAN8_SIZE, boost::checks::basic_checkdigit>(boost::rbegin(check_seq), boost::rend(check_seq));
}


}} // namespace boost   namespace checks
#endif // BOOST_CHECKS_EAN_HPP
