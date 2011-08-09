//  Boost checks/luhn.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_LUHN_INCLUDED
#define BOOST_LUHN_INCLUDED

#include <boost/checks/basic_checks.hpp>

namespace boost {
    namespace checks{

template <typename luhn_range, typename size_policy, typename checkdigit_policy>
struct luhn_policy : mod_policy <weight_policy<1,2>, size_policy, checkdigit_policy, rightmost<luhn_range> >
{
  static const unsigned int modulus = 10;

  template <typename character>
  static unsigned int characterToDigit(const character& mod10_character)
  {
    return boost::lexical_cast<unsigned int>(mod10_character);
  }
  template <typename character>
  static character compute_checkdigit( const unsigned int &sum )
  {
    return boost::lexical_cast<character>((10 - sum % 10 ) % 10) ;
  }
  static bool validate_checkdigit( const unsigned int &sum )
  {
    return !(sum % 10);
  }

  typedef unsigned int opdata_type ;

  template <typename opdata_t>
  static void init_opdata ( opdata_t &opdata){ }

  template <typename weight_value, typename opdata_t>
  static void sum_operation(unsigned int &sum, unsigned int &digit, opdata_t &opdata )
  {
    sum += (digit << (weight_value-1)) - 9 * ( digit << (weight_value-1)  > 9) ;
  }
};

template <size_t size_expected, typename luhn_range>
bool check_luhn ( luhn_range luhn_number )
{
  return check_number<luhn_policy<luhn_range, mod_size<size_expected>, checkdigit_included > >( luhn_number ) ;
}

template <typename luhn_range>
bool check_luhn ( luhn_range luhn_number )
{ 
  return check_number<luhn_policy<luhn_range, no_size_set , checkdigit_included > >( luhn_number ) ;
}

template <size_t size_expected, typename luhn_range>
typename boost::range_value<luhn_range>::type compute_luhn ( luhn_range luhn_number )
{
  return compute_number<luhn_policy<luhn_range, mod_size<size_expected>, virtual_checkdigit> >( luhn_number ) ;
}

template <typename luhn_range>
typename boost::range_value<luhn_range>::type compute_luhn ( luhn_range luhn_number )
{ 
  return compute_number<luhn_policy<luhn_range, no_size_set , virtual_checkdigit > >( luhn_number ) ;
}

} // namespace checks
} // namespace boost

#endif
