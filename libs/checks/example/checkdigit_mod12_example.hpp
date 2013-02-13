// Copyright Pierre Talbot 2013.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file is written to be included from a Quickbook .qbk document.
// It can be compiled by the C++ compiler, and run. Any output can
// also be added here as comment or included or pasted in elsewhere.
// Caution: this file contains Quickbook markup as well as code
// and comments: don't change any of the special comment markups!

//[checkdigit_mod12_example
#include <boost/checks/modulus.hpp>
#include <boost/checks/checkdigit.hpp>

using namespace boost::checks;

// The check digit processor.
typedef modulus<12> mod12_basic;

// The check digit encoder.
struct checkdigit_12_encoder
{
  typedef char result_type;
  typedef size_t argument_type;

  result_type operator()(argument_type checksum)
  {
    if(checksum == 11)
      return 'Y';
    else
      return checkdigitx_encoder<result_type>()(checksum);
  }
};

// The check digit type.
typedef checkdigit<mod12_basic, checkdigit_12_encoder> mod12_basic_checkdigit;
//]