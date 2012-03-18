//  Boost checks/weighted_sum.hpp header file
//  (C) Copyright Pierre Talbot 2011 - 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute weighted sum.
*/

#ifndef BOOST_CHECKS_WEIGHTED_SUM_HPP
#define BOOST_CHECKS_WEIGHTED_SUM_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/checks/weight.hpp>
#include <boost/checks/basic_checks.hpp>
#include <boost/checks/basic_check_algorithm.hpp>

namespace boost{
  namespace checks{

/*!
  \brief Compute an operation on the checksum with the current valid value.

  \post The current weight multiplied by the current value is added to the checksum.

  \param current_valid_value is the current valid value analysed.
  \param valid_value_counter is the number of valid values already counted (the current value is not included).\n This is also the position (above the valid values) of the current value analysed (0 <= valid_value_counter < n).
  \param checksum is the current checksum.
*/
template <typename weight>
struct weighted_sum
{
  std::size_t operator()(std::size_t checksum, std::size_t value, std::size_t pos)
  {
    return checksum + value * weight::at(pos);
  }
};

}}// namespace boost   namespace checks

#endif //BOOST_CHECKS_MOD10_HPP
