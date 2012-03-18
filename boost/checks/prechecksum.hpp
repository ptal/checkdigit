//  Boost checks/prechecksum.hpp header file
//  (C) Copyright Pierre Talbot 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief 
*/

#ifndef BOOST_CHECK_PRECHECKSUM_HPP
#define BOOST_CHECK_PRECHECKSUM_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <utility>
#include <boost/range.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include <boost/checks/filter.hpp>
#include <boost/checks/conversion.hpp>

namespace boost {
  namespace checks{




template <
          typename Prechecksum,
          typename Iterator
         >
std::pair
< 
  typename Prechecksum::template iterator<Iterator>::type,
  typename Prechecksum::template iterator<Iterator>::type
> 
make_prechecksum(Iterator begin, Iterator end)
{ 
  typedef typename Prechecksum::template iterator<Iterator>::type iter;
  Prechecksum prechecksum;
  return std::make_pair<iter, iter>(prechecksum(begin, end), prechecksum(end, end));
}

template <
          typename Prechecksum,
          typename T
         >
std::pair
< 
  typename Prechecksum::template iterator<typename range_iterator<T>::type>::type,
  typename Prechecksum::template iterator<typename range_iterator<T>::type>::type
> 
make_prechecksum(T &sequence)
{ 
  return make_prechecksum<Prechecksum>(boost::begin(sequence), boost::end(sequence));
}

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
    return typename iterator<BaseIterator>::type(boost::filter_iterator<FilterPredicate, BaseIterator>(filter, b, e),
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
    return typename iterator<BaseIterator>::type(b, converter);
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
    return typename iterator<BaseIterator>::type(filter, b, e);
  }
};                                                                                              

typedef prechecksum<digit_filter, chartodigit> digit_prechecksum; 
typedef prechecksum<digitx_filter, chartodigitx> digitx_prechecksum;

} // namespace checks
} // namespace boost

#endif // BOOST_CHECK_PRECHECKSUM_HPP
