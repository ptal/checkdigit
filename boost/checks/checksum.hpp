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

#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost {
  namespace checks{


struct reverse_traversal 
{
  template <typename Range>
  struct iterator
  {
    typedef typename boost::range_reverse_iterator<Range>::type type;
  };

  template <typename Range>
  static typename iterator<Range>::type begin(Range &x)
  {
    return boost::rbegin(x);
  }

  template <typename Range>
  static typename iterator<Range>::type end(Range &x)
  {
    return boost::rend(x);
  }                                                                       
};

struct forward_traversal 
{
  template <typename Range>
  struct iterator
  {
    typedef typename boost::range_iterator<Range>::type type;
  };

  template <typename Range>
  static typename iterator<Range>::type begin(Range &x)
  {
    return boost::begin(x);
  }

  template <typename Range>
  static typename iterator<Range>::type end(Range &x)
  {
    return boost::end(x);
  }                                                                       
};

struct no_size_policy
{
  static bool check(std::size_t pos)
  {
    return true;
  }
  static bool overflow(std::size_t pos)
  {
    return false;
  }
};

template <std::size_t size_expected>
struct enforce_size_policy
{
  static bool check(std::size_t pos)
  {
    return pos < size_expected;
  }
  static bool overflow(std::size_t pos)
  {
    return pos != size_expected;
  }
};

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
  std::size_t size_expected = 0
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
