//  Boost checks/amex.hpp header file
//  (C) Copyright Pierre Talbot 2011 - 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate an American Express credit card number.
*/

#ifndef BOOST_CHECKS_AMEX_HPP
#define BOOST_CHECKS_AMEX_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef> // std::size_t

#include <boost/checks/checkdigit.hpp>
#include <boost/checks/luhn.hpp>

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>

/*!
  \brief This macro defines the size of a American Express card number (15).
*/
#define AMEX_SIZE 15

namespace boost {
    namespace checks{

/*!
    \brief Validate a sequence according to the amex_check_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly AMEX_SIZE digits.
    \throws std::invalid_argument if the two first digits (from the leftmost) don't match the Amex pattern.

    \returns @c true if the check digit is correct, @c false otherwise.
*/
template <typename check_range>
bool check_amex (const check_range& check_seq)
{
  return boost::checks::check_sequence<luhn_algorithm, digit_filter, AMEX_SIZE>(boost::rbegin(check_seq), boost::rend(check_seq));
}

/*!
    \brief Calculate the check digit of a sequence according to the amex_compute_algorithm type.

    \pre check_seq is a valid range.

    \tparam check_range is a valid range type.
    \param check_seq is the sequence of value to check.

    \throws std::invalid_argument if check_seq doesn't contain exactly AMEX_SIZE_WITHOUT_CHECKDIGIT digits.
    \throws std::invalid_argument if the two first digits (from the leftmost) don't match the amex pattern.
    \throws boost::checks::translation_exception if the check digit cannot be translated into the checkdigit type.

    \returns The check digit. The check digit is in the range [0..9].
*/
template <typename check_range>
std::size_t compute_amex(const check_range& check_seq)
{
  return boost::checks::compute_checkdigit<luhn_algorithm, digit_filter, AMEX_SIZE, boost::checks::basic_checkdigit>(boost::rbegin(check_seq), boost::rend(check_seq));
}


}} // namespace boost   namespace checks
#endif
