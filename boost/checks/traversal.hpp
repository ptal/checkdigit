//  Boost checks/size_check.hpp header file
//  (C) Copyright Pierre Talbot 2013
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECK_TRAVERSAL_HPP
#define BOOST_CHECK_TRAVERSAL_HPP

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

} // namespace checks
} // namespace boost

#endif // BOOST_CHECK_TRAVERSAL_HPP
