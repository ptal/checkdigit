//  Boost checks/modulus97.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_MOD97_HPP
#define BOOST_CHECKS_MOD97_HPP

#include <boost/preprocessor/repetition.hpp>
#include <boost/checks/weight.hpp>

namespace boost{
  namespace checks{

    
template <unsigned int weight_value>
struct _mod97_weight
{
  static const unsigned int value = weight_value ;
  typedef _mod97_weight<weight_value * 10 % 97> next ;
};
template<>
struct _mod97_weight<68>
{
  static const unsigned int value = 68 ;
  typedef _mod97_weight type ;
};

#define _next(z,n,unused) next::
#define _MOD97_make_weight(z, n ,unused) _mod97_weight<1>::BOOST_PP_REPEAT(n, _next, ~)value
typedef boost::checks::weight< BOOST_PP_ENUM(96, _MOD97_make_weight, ~) > mod97_weight ;

}}

#endif //BOOST_CHECKS_MOD97_HPP