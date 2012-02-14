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
          typename UnaryFunction>
struct prechecksum
{
  typedef UnaryPredicate FilterPredicate;
  typedef UnaryFunction ConversionFunction;

  template <typename BaseIterator>
  struct iterator
  {
    typedef typename boost::transform_iterator<ConversionFunction, 
                                               boost::filter_iterator<FilterPredicate, 
                                                                      BaseIterator> > type;
  };

  FilterPredicate filter;
  ConversionFunction converter;

  template <typename BaseIterator>
  typename iterator<BaseIterator>::type operator()(BaseIterator b, BaseIterator e)
  {
    return iterator<BaseIterator>::type(boost::filter_iterator<FilterPredicate, BaseIterator>(filter, b, e),
                                        converter);
  }
};                                                                                              

template <typename UnaryFunction>
struct prechecksum<no_filter_tag, UnaryFunction>
{
  typedef UnaryFunction ConversionFunction;

  template <typename BaseIterator>
  struct iterator
  {
    typedef typename boost::transform_iterator<ConversionFunction, 
                                               BaseIterator> type;
  };

  ConversionFunction converter;

  template <typename BaseIterator>
  typename iterator<BaseIterator>::type operator()(BaseIterator b, BaseIterator e)
  {
    return iterator<BaseIterator>::type(b, converter);
  }
};                                                                                              

template <typename UnaryPredicate>
struct prechecksum<UnaryPredicate, no_conversion_tag>
{
  typedef UnaryPredicate FilterPredicate;

  template <typename BaseIterator>
  struct iterator
  {
    typedef typename boost::filter_iterator<FilterPredicate, BaseIterator> type;
  };

  FilterPredicate filter;

  template <typename BaseIterator>
  typename iterator<BaseIterator>::type operator()(BaseIterator b, BaseIterator e)
  {
    return iterator<BaseIterator>::type(filter, b, e);
  }
};                                                                                              


} // namespace checks
} // namespace boost

#endif // BOOST_PRECHECKSUM_HPP
