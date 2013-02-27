//  Boost checks/checksum.hpp header file
//  (C) Copyright Pierre Talbot 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief 
*/

#ifndef BOOST_CHECK_CHECKSUM_HPP
#define BOOST_CHECK_CHECKSUM_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/checks/checkdigit.hpp>

namespace boost {
  namespace checks{

template
<
  typename TernaryFunction,
  typename UnaryPredicate,
  typename UnaryFunction,
  typename Checkdigit = basic_checkdigit,
  typename traversal = reverse_traversal
>
struct checksum : traversal
{
  typedef TernaryFunction processor;
  typedef UnaryPredicate validate_checkdigit;
  typedef UnaryFunction make_checkdigit;
  typedef Checkdigit checkdigit_detail;
};

template
<
  typename Checksum,
  size_t size_expected = 0
>
struct features : Checksum
{
  typedef Checksum checksum;
  typedef enforce_size_policy<size_expected> size_policy;
};

template
<
  typename Checksum
>
struct features<Checksum, 0> : Checksum
{
  typedef Checksum checksum;
  typedef no_size_policy size_policy;
};


} // namespace checks
} // namespace boost

#endif // BOOST_CHECK_CHECKSUM_HPP
