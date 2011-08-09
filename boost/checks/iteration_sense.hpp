//  Boost checks/iteration_sense.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECK_ITERATION_SENSE_HPP
#define BOOST_CHECK_ITERATION_SENSE_HPP

#include <boost/range/reverse_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/const_reverse_iterator.hpp>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>

struct rightmost
{

  template <typename seq_range>
  struct iterator
  {
    typedef typename boost::range_const_reverse_iterator<seq_range>::type type ;
  };

  template <typename seq_range>
  static typename iterator<seq_range>::type begin(seq_range &sequence) { return boost::rbegin(sequence) ; }

  template <typename seq_range>
  static typename iterator<seq_range>::type end(seq_range &sequence)   { return boost::rend(sequence) ; }
};

struct leftmost
{
  template <typename seq_range>
  struct iterator
  {
    typedef typename boost::range_const_iterator<seq_range>::type type ;
  };

  template <typename seq_range>
  static typename iterator<seq_range>::type begin(seq_range &sequence) { return boost::begin(sequence) ; }

  template <typename seq_range>
  static typename iterator<seq_range>::type end(seq_range &sequence)   { return boost::end(sequence) ; }
};

#endif // BOOST_CHECKS_ITERATION_SENSE_HPP