//  Boost checks/weight.hpp header file
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief Provides a template overriden struct to encapsulate a compile-time weight sequence.
*/

#ifndef BOOST_CHECK_WEIGHT_HPP
#define BOOST_CHECK_WEIGHT_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

/*! \def BOOST_CHECK_LIMIT_WEIGHTS
    \brief The BOOST_CHECK_LIMIT_WEIGHTS macro defines the maximum number of weights accepted by the library.

    \remarks This macro expands to 100. For compile-time saving, you can decrease it if the algorithm(s) used have a lower weight size sequence.
    A contrario, you can increase it till 236 (see Boost.Preprocessor for more details about this limit.)
*/
#define BOOST_CHECK_LIMIT_WEIGHTS 100

namespace boost{
  namespace checks{

/*! \class weight
    \brief The weight metafunction encapsulate 0 to BOOST_CHECK_LIMIT_WEIGHTS weights.
    \tparam weight_value The weights are implicitly linked to a position through a sequence. No weight means an equal weight of 1 for all the digits.

    \remarks There are BOOST_CHECK_LIMIT_WEIGHTS partial specialisations of this class.
*/
template <BOOST_PP_ENUM_BINARY_PARAMS(BOOST_CHECK_LIMIT_WEIGHTS, int weight_value, = 0 BOOST_PP_INTERCEPT) >
struct weight
{
/*! \fn static int weight_associated_with_pos(const unsigned int value_pos)
    \brief Get the weight at the current value position.

    \param value_pos is the position of the current value. (0 <= value_pos < n).
    \returns The weight value at the position value_pos.
  */
  static int weight_associated_with_pos(const unsigned int value_pos) { return 1; }
};

#define _WEIGHT_factory(z, weight_size ,unused) \
  template<BOOST_PP_ENUM_PARAMS(weight_size , int weight_value)> \
  struct weight<BOOST_PP_ENUM_PARAMS(weight_size, weight_value)> \
  { \
    static int weight_associated_with_pos(const unsigned int value_pos) \
    { \
      static const int weights[weight_size] = { BOOST_PP_ENUM_PARAMS(weight_size, weight_value) } ; \
      return weights[value_pos % weight_size] ; \
    } \
  } ;

// Develop the macro _WEIGHT_factory BOOST_CHECK_LIMIT_WEIGHTS times.
BOOST_PP_REPEAT_FROM_TO(1,BOOST_CHECK_LIMIT_WEIGHTS,_WEIGHT_factory,~)
#undef _WEIGHT_factory

}} // namespace boost   namespace checks

#endif //BOOST_CHECK_WEIGHT_HPP
