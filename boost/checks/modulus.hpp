//  Boost checks/modulus.hpp header file
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_MODULUS_HPP
#define BOOST_CHECKS_MODULUS_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef>
#include <boost/static_assert.hpp>

namespace boost{
  namespace checks{

template <size_t mod>
struct modulus
{
  BOOST_STATIC_ASSERT_MSG(mod != 0, "Cannot divide by 0.");

  typedef size_t result_type;
  typedef size_t argument_type;

  static const size_t modulus_value = mod;

  result_type operator()(argument_type value)
  {
    return value % mod;
  }
};

template <size_t mod>
struct modulus_inv
{
  BOOST_STATIC_ASSERT_MSG(mod != 0, "Cannot divide by 0.");

  typedef size_t result_type;
  typedef size_t argument_type;

  static const size_t modulus_value = mod;

  result_type operator()(argument_type value)
  {
    return (mod - (value % mod)) % mod;
  }
};

}}  // namespace boost   namespace checks

#endif //BOOST_CHECKS_MODULUS_HPP
