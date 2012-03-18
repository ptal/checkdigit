//  Boost checks/upc.hpp header file
//  (C) Copyright Pierre Talbot 2011 - 2012
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
#include <boost/checks/checksum.hpp> 

#include <boost/checks/weight.hpp>
#include <boost/checks/basic_checks.hpp>
#include <boost/checks/modulus10.hpp>
#include <boost/checks/weighted_sum.hpp>

/*!
  \brief This macro defines the size of an UPC-A.
*/
#define UPCA_SIZE 12

namespace boost {
    namespace checks{

/*!
  \brief This is the weight used by UPC system.
*/
typedef weight<1,3> upc_weight;

typedef weighted_sum<upc_weight> upc_processor;

typedef features
<
  checksum
  <
    upc_processor,
    mod10_validation,
    mod10_checkdigit
  >,
  UPCA_SIZE
> upca;

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
  return check_sequence<upca>(check_seq);
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
std::size_t compute_upca(const check_range& check_seq)
{
  return compute_checkdigit<upca>(check_seq);
}

}} // namespace boost   namespace checks
#endif // BOOST_CHECKS_UPCA_HPP
