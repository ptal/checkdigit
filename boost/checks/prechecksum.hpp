//  Boost checks/prechecksum.hpp header file
//  (C) Copyright Pierre Talbot 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief 
*/

#ifndef BOOST_PRECHECKSUM_HPP
#define BOOST_PRECHECKSUM_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>

namespace boost {
  namespace checks{

struct no_filter_tag {};
struct no_conversion_tag {};

template <typename UnaryPredicate,
          typename UnaryFunction,
          typename BaseIterator>
struct prechecksum
{
  typedef UnaryPredicate FilterPredicate;
  typedef UnaryFunction ConversionFunction;

  typedef typename boost::filter_iterator<FilterPredicate, BaseIterator> filter_iterator;

  typedef typename boost::transform_iterator<ConversionFunction, filter_iterator> iterator;

  FilterPredicate filter;
  ConversionFunction converter;

  iterator operator()(BaseIterator b, BaseIterator e)
  {
    return iterator(filter_iterator(filter, b, e), converter);
  }
};                                                                                              

template <typename UnaryFunction,
          typename BaseIterator>
struct prechecksum<no_filter_tag, UnaryFunction, BaseIterator>
{
  typedef UnaryFunction ConversionFunction;

  typedef typename boost::transform_iterator<ConversionFunction, BaseIterator> iterator;

  ConversionFunction converter;
  iterator operator()(BaseIterator b, BaseIterator e)
  {
    return iterator(b, converter);
  }
};                                                                                              

template <typename UnaryPredicate,
          typename BaseIterator>
struct prechecksum<UnaryPredicate, no_conversion_tag, BaseIterator>
{
  typedef UnaryPredicate FilterPredicate;

  typedef typename boost::filter_iterator<FilterPredicate, BaseIterator> iterator;

  FilterPredicate filter;
  iterator operator()(BaseIterator b, BaseIterator e)
  {
    return iterator(filter, b, e);
  }
};                                                                                              


} // namespace checks
} // namespace boost

#endif // BOOST_PRECHECKSUM_HPP
