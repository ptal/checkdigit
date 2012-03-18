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
  
}} // namespace boost  namespace checks

#endif //BOOST_CHECKS_BASIC_CHECK_ALGO_HPP
