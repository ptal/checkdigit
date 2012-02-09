//  Boost checks/sequence_counter.hpp header file
//  (C) Copyright Pierre Talbot 2011 - 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief Counting iterator and skipping iterator.
*/

#ifndef BOOST_CHECKS_SEQUENCE_COUNTER_HPP
#define BOOST_CHECKS_SEQUENCE_COUNTER_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <functional>

namespace boost{
  namespace checks{

namespace detail
{

template <std::size_t skip_at, std::size_t size_to_skip>
struct skipper : public std::unary_function <std::size_t, std::size_t>
{
  std::size_t operator()(std::size_t value_pos) const
  {
    return value_pos + size_to_skip * (value_pos >= skip_at);
  } 
};

struct simple_counter
{
  typedef boost::counting_iterator<std::size_t> type;
  type operator()()
  {
    return type(0);
  }
};

template <std::size_t skip_at, std::size_t size_to_skip>
struct skip_counter
{
  typedef boost::transform_iterator<skipper<skip_at, size_to_skip>, simple_counter::type> type;
  type operator()()
  {
    simple_counter::type iter = simple_counter()();
    return type(iter, skipper<skip_at, size_to_skip>());
  }
};

}
}} // namespace boost   namespace checks

#endif 
