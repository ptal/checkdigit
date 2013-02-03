//  Boost checks/modulus97.hpp header file

//  (C) Copyright Pierre Talbot 2011 - 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file
    \brief This file provides tools to compute and validate the classic modulus 97 checksum. It provides functions for convenience with the mod97-10 algorithm (ISO/IEC 7064:2003).
*/

#ifndef BOOST_CHECKS_MOD97_HPP
#define BOOST_CHECKS_MOD97_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/checks/weight.hpp>
#include <boost/checks/checkdigit.hpp>

namespace boost{
  namespace checks{

struct mod97
{
  typedef size_t result_type;
  typedef size_t argument_type;

  static const size_t modulus_value = 97;

  result_type operator()(argument_type value)
  {
    return 98 - (value % 97);
  }
};

typedef checkdigit_encoder<std::string> mod97_basic_encoder;
typedef checkdigit<mod97, mod97_basic_encoder, 0, 2> mod97_10_checkdigit;

struct mod97_10_processor
{
  unsigned char weight;
  
  mod97_10_processor() : weight(10) 
  {
  } 

  size_t operator()(size_t checksum, size_t value, size_t pos)
  {
    if(pos == 0)
      weight = 1;
    else
      weight = weight * 10 % 97;
    return checksum + value * weight;
  }
};

}} // namespace boost   namespace checks

#endif //BOOST_CHECKS_MOD97_HPP
