//  Boost checks/upc.hpp header file
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate an Universal Product Code.
*/

#ifndef BOOST_CHECKS_UPC_HPP
#define BOOST_CHECKS_UPC_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>

#include <boost/checks/weight.hpp>
#include <boost/checks/basic_checks.hpp>
#include <boost/checks/modulus10.hpp>

/*!
  \brief This macro defines the size of an UPC-A.
*/
#define UPCA_SIZE 12

namespace boost {
    namespace checks{

/*!
  \brief This is the weight used by UPC system.
*/
typedef boost::checks::weight<1,3> upc_weight;

/*!
  \brief This is the type of the UPC algorithm.
*/
typedef boost::checks::modulus10_algorithm<upc_weight> upc_algorithm;

/*!
    \brief Validate a sequence according to the upc_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly UPCA_SIZE digits.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename check_range>
bool check_upca (const check_range& check_seq)
{
  return boost::checks::check_sequence<upc_algorithm, UPCA_SIZE>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Calculate the check digit of a sequence according to the upc_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly UPCA_SIZE_WITHOUT_CHECKDIGIT digits.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename check_range>
typename boost::range_value<check_range>::type compute_upca(const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<upc_algorithm, UPCA_SIZE, boost::checks::basic_checkdigit>(boost::rbegin(check_seq), boost::rend(check_seq));
}

}} // namespace boost   namespace checks
#endif // BOOST_CHECKS_UPCA_HPP
