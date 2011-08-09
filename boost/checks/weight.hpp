//  Boost checks/weight.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECK_WEIGHT_HPP
#define BOOST_CHECK_WEIGHT_HPP

#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

#define BOOST_CHECK_LIMIT_WEIGHTS 10

namespace boost{
  namespace checks{

template <BOOST_PP_ENUM_BINARY_PARAMS(BOOST_CHECK_LIMIT_WEIGHTS, int weight_value, = 0 BOOST_PP_INTERCEPT) >
struct weight
{
  static int weight_associated_with_pos(const unsigned int &value_pos) { return 1; }
};

#define _WEIGHT_factory(z, weight_size ,unused) \
  template<BOOST_PP_ENUM_PARAMS(weight_size , int weight_value)> \
  struct weight<BOOST_PP_ENUM_PARAMS(weight_size, weight_value)> \
  { \
    static int weight_associated_with_pos(const unsigned int &value_pos) \
    { \
      static const int weights[weight_size] = { BOOST_PP_ENUM_PARAMS(weight_size, weight_value) } ; \
      return weights[value_pos % weight_size] ; \
    } \
  } ; 

// Develop the macro _WEIGHT_factory BOOST_CHECK_LIMIT_WEIGHTS times.
BOOST_PP_REPEAT_FROM_TO(1,BOOST_CHECK_LIMIT_WEIGHTS,_WEIGHT_factory,~)
#undef _WEIGHT_factory

}}

#endif //BOOST_CHECK_WEIGHT_HPP