//  Boost checks/modulus11.hpp header file  ------------------------------------//
// (C)Copyright Pierre Talbot 2011 - 2012
//  Distributed under the Boost Software License, Version 1.0.(See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_MOD11_HPP
#define BOOST_CHECKS_MOD11_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/checks/weight.hpp>
#include <boost/checks/modulus.hpp>
#include <boost/checks/checkdigit.hpp>

namespace boost{
  namespace checks{

typedef modulus<11> mod11_basic;
typedef modulus_inv<11> mod11_inv_basic;
typedef checkdigitx_encoder mod11_basic_encoder;

typedef checkdigit<mod11_basic, mod11_basic_encoder> mod11_basic_checkdigit;
typedef checkdigit<mod11_inv_basic, mod11_basic_encoder> mod11_inv_checkdigit;

typedef weight<1,2,3,4,5,6,7,8,9,10> mod11_weight;

}} // namespace boost  namespace checks


#endif //BOOST_CHECKS_MOD10_HPP
