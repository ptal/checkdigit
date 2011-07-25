//  Boost checks/modulus.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECK_MODULUS_HPP
#define BOOST_CHECK_MODULUS_HPP

#ifdef _MSC_VER
    #pragma once
#endif // _MSC_VER

// MPL and PP includes
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/preprocessor/repetition.hpp>
// Range include
#include <boost/range/numeric.hpp>
#include <boost/range/empty.hpp>
// Lexical include
#include <boost/lexical_cast.hpp>

#define BOOST_CHECK_LIMIT_WEIGHTS 10 // The maximum number of weights. (non-type template parameters)


namespace boost {
  namespace checks{

// Here specialisation of policy for the handle of integer (return 10 instead of 'X') ? Use macro.. ?
// template<>
// struct policy_mod11<unsigned short> {};
// template <>
// struct policy_mod11<unsigned int>{};
// ...

template <typename character>
struct mod10_policy
{
  static unsigned int modulus() { return 10 ;}
  static unsigned int characterToDigit(const character& mod10_character)
  {
    return boost::lexical_cast<unsigned int>(mod10_character);
  }
  static character return_check_digit( const unsigned int &check_digit )
  {
    return boost::lexical_cast<character>(check_digit) ;
  }
};

template <typename character>
struct mod11_policy
{
  static unsigned int modulus() { return 11 ;}
  static unsigned int characterToDigit(const character& mod11_character)
  {
    return (mod11_character == 'x' || mod11_character == 'X') ? 10 :  boost::lexical_cast<unsigned int>(mod11_character);
  }
  static character return_check_digit( const unsigned int &check_digit)
  {
    return (check_digit == 10) ? 'X' : boost::lexical_cast<character>(check_digit) ;
  }
};

// Add to the running sum the digits of the sequence given.
// The digits added are selected according to the position of the weight given.
template<bool have_checkdigit, typename mod_policy, typename mod_range, size_t weight_sequence_size>
struct sum_with_weight
{
  private:
  // The position through the weight sequence.
  unsigned int weight_position ;
  // The position through the number.
  unsigned int number_position ;
  // The number of digits in the modulus 10 number which are already weighed with the current weight.
  unsigned int digits_weighed ;
  // If we found at least one digit into the mod11_number.
  bool &have_digit ;
  // The last character.
  unsigned int &last_digit ;
  // The number.
  const mod_range& mod_number ;
  // Final sum.
  unsigned int& sum_ ;
 
  public:
  // Constructor.
  sum_with_weight(const mod_range& r, unsigned int &sum, bool &_have_digit,unsigned int &_last_digit) : 
    number_position(1), weight_position(1), digits_weighed(0), have_digit(_have_digit), last_digit(_last_digit), mod_number(r), sum_(sum) {}
    
  // Treatment : Multiply the weight with the digits accumulate from mod11_number.
  template<typename weight, weight weight_value>
  void operator()(const boost::mpl::integral_c< weight , weight_value >&)
  {
    sum_ += weight_value * boost::accumulate(mod_number , unsigned int(), *this );
    // "Unweight" the check_digit only if the number have a check digit (ex : if the number want a check digit, it haven't it yet).
    last_digit *= have_checkdigit ;
    (sum_ -= weight_value * last_digit) += last_digit ;
  }
  // Treatment : If the character is a digit which must be weighed, the addition of the digit and the current sum is returned. 
  //             Otherwise the character is ignored and the current sum is returned without any changes.
  template<typename character>
  unsigned int operator()(const unsigned int &sum, const character& mod_character) 
  {
    unsigned int mod_digit = 0;
    try
    {
      mod_digit = mod_policy::characterToDigit(mod_character);
      if(number_position++ % (weight_position + digits_weighed * weight_sequence_size) == 0)
      {
        ++digits_weighed ;
        have_digit = true ;
      }
      else
        mod_digit = 0 ;

      last_digit = mod_digit ;

     }catch(boost::bad_lexical_cast){ } // Characters ignored.
     return sum + mod_digit;
  }
};

// Internal check function.
template<typename mod_policy, typename weight_sequence, typename mod_range>
bool _check_mod(const mod_range& mod_number)
{ 
  // If the sequence is empty we throw an exception.
  if( boost::empty(mod_number) )
    throw std::invalid_argument("Empty sequence");
  // Final sum.
  unsigned int sum = 0;
  bool have_digit = false ;
  unsigned int last_digit = 0 ;
  // For each weight, we call the functor "mod_sum".
  sum_with_weight<true, mod_policy, mod_range,  boost::mpl::size<weight_sequence>::value> mod_sum(mod_number, sum, have_digit, last_digit);
  boost::mpl::for_each<weight_sequence>(mod_sum);
  // If no digit has been encountered, we throw an exception.
  if(!have_digit)
    throw std::invalid_argument("No digit found in the sequence");
  // We return true if the check digit is correct. We return false otherwise.
  return !(sum % mod_policy::modulus() ) ;
}

// Internal compute function.
template<typename mod_policy, typename weight_sequence, typename mod_range>
typename boost::range_value<mod_range>::type _compute_mod(const mod_range& mod_number)
{ 
  // If the sequence is empty.
  if( boost::empty(mod_number) )
    throw std::invalid_argument("Empty sequence");
  // Final sum.
  unsigned int sum = 0;
  bool have_digit = false;
  unsigned int last_digit ;
  // For each weight, we call the functor "sum_with_weight".
  sum_with_weight<false, mod_policy, mod_range,  boost::mpl::size<weight_sequence>::value> mod_sum(mod_number, sum, have_digit, last_digit);
  boost::mpl::for_each<weight_sequence>(mod_sum);
  if(!have_digit)
    throw std::invalid_argument("No digit found in the sequence");
  // We return the check digit
  return mod_policy::return_check_digit( (mod_policy::modulus() - sum % mod_policy::modulus() ) % mod_policy::modulus() ) ;
}

/*--------------------------------------------------------------------
                   Modulus 10 Algorithm.

Provides check and compute functions.

Note : These functions are the base of many other checks which use
a modulus 10.
----------------------------------------------------------------------*/

// MODULUS 10 CHECK FUNCTION
// Complexity : O(weight_size * number_size)
// Algorithm : For each weight, we run through the number and add to the sum the digit weighed.

// Declaration of the different prototypes. The number of prototypes depends on BOOST_CHECK_LIMIT_WEIGHTS. 

// DEFAULT prototype. If any non-type template argument are passed to the function, we consider a weight of 1.
template<typename mod10_range> 
bool check_mod10(const mod10_range& mod10_number) 
{ return _check_mod<mod10_policy<boost::range_value<mod10_range>::type>, boost::mpl::vector_c<int, 1> >(mod10_number); }

// Prototypes for the different size of non-type template argument (weight).
#define _CHECK_mod10(z,n,unused) \
  template<BOOST_PP_ENUM_PARAMS(n, int weight) BOOST_PP_COMMA_IF(n) typename mod10_range> \
  bool check_mod10(const mod10_range& mod10_number) \
  { return _check_mod<mod10_policy<boost::range_value<mod10_range>::type>, boost::mpl::vector_c<int BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, weight)> >(mod10_number); } \

// Develop the macro _CHECK_mod10 BOOST_CHECK_LIMIT_WEIGHTS times.
BOOST_PP_REPEAT_FROM_TO(1,BOOST_CHECK_LIMIT_WEIGHTS,_CHECK_mod10,~)
#undef _CHECK_mod10


// MODULUS 10 COMPUTE FUNCTION
// Complexity : O(weight_size * number_size)
// Algorithm : For each weight, we run through the number and add to the sum the digit weighed.
 
// Declaration of the different prototypes. The number of prototypes depends on BOOST_CHECK_LIMIT_WEIGHTS. 

// DEFAULT prototype. If any non-type template argument are passed to the function, we consider a weight of 1.
template<typename mod10_range> 
typename boost::range_value<mod10_range>::type compute_mod10(const mod10_range& mod10_number) 
{ return _compute_mod<mod10_policy<boost::range_value<mod10_range>::type>, boost::mpl::vector_c<int, 1> >(mod10_number); }

// Prototypes for the different size of non-type template argument (weight).
#define _COMPUTE_mod10(z,n,unused) \
  template<BOOST_PP_ENUM_PARAMS(n, int weight) BOOST_PP_COMMA_IF(n) typename mod10_range> \
  typename boost::range_value<mod10_range>::type compute_mod10(const mod10_range& mod10_number) \
  { return _compute_mod<mod10_policy<boost::range_value<mod10_range>::type>, boost::mpl::vector_c<int BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, weight)> >(mod10_number); } \

// Develop the macro _COMPUTE_mod10 BOOST_CHECK_LIMIT_WEIGHTS times.
BOOST_PP_REPEAT_FROM_TO(1, BOOST_CHECK_LIMIT_WEIGHTS, _COMPUTE_mod10, ~)
#undef _COMPUTE_mod10


/*--------------------------------------------------------------------
                   Modulus 11 Algorithm.

Provides check and compute functions.
----------------------------------------------------------------------*/

// MODULUS 11 CHECK FUNCTION
// Complexity : O(weight_size * number_size)
// Algorithm : For each weight, we run through the number and add to the sum the digit weighed.

// Declaration of the different prototypes. The number of prototypes depends on BOOST_CHECK_LIMIT_WEIGHTS. 

// DEFAULT prototype. If any non-type template argument are passed to the function, we consider a weight of 1.
template<typename mod11_range> 
bool check_mod11(const mod11_range& mod11_number) 
{ return _check_mod<mod11_policy<boost::range_value<mod11_range>::type>, boost::mpl::vector_c<int, 1> >(mod11_number); }

// Prototypes for the different size of non-type template argument (weight).
#define _CHECK_mod11(z,n,unused) \
  template<BOOST_PP_ENUM_PARAMS(n, int weight) BOOST_PP_COMMA_IF(n) typename mod11_range> \
  bool check_mod11(const mod11_range& mod11_number) \
  { return _check_mod<mod11_policy<boost::range_value<mod11_range>::type>, boost::mpl::vector_c<int BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, weight)> >(mod11_number); } \

// Develop the macro _CHECK_mod11 BOOST_CHECK_LIMIT_WEIGHTS times.
BOOST_PP_REPEAT_FROM_TO(1,BOOST_CHECK_LIMIT_WEIGHTS,_CHECK_mod11,~)
#undef _CHECK_mod11

// MODULUS 11 COMPUTE FUNCTION
// Complexity : O(weight_size * number_size)
// Algorithm : For each weight, we run through the number and add to the sum the digit weighed.


// Declaration of the different prototypes. The number of prototypes depends on BOOST_CHECK_LIMIT_WEIGHTS. 

// DEFAULT prototype. If any non-type template argument are passed to the function, we consider a weight of 1.
template<typename mod11_range> 
typename boost::range_value<mod11_range>::type compute_mod11(const mod11_range& mod11_number) 
{ return _compute_mod<mod11_policy<boost::range_value<mod11_range>::type>, boost::mpl::vector_c<int, 1> >(mod11_number); }

// Prototypes for the different size of non-type template argument (weight).
#define _COMPUTE_mod11(z,n,unused) \
  template<BOOST_PP_ENUM_PARAMS(n, int weight) BOOST_PP_COMMA_IF(n) typename mod11_range> \
  typename boost::range_value<mod11_range>::type compute_mod11(const mod11_range& mod11_number) \
  { return _compute_mod<mod11_policy<boost::range_value<mod11_range>::type>, boost::mpl::vector_c<int BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, weight)> >(mod11_number); } \

// Develop the macro _COMPUTE_mod11 BOOST_CHECK_LIMIT_WEIGHTS times.
BOOST_PP_REPEAT_FROM_TO(1, BOOST_CHECK_LIMIT_WEIGHTS, _COMPUTE_mod11, ~)
#undef _COMPUTE_mod11

/*--------------------------------------------------------------------
                   Modulus 97 Algorithm.

Provides check and compute functions.
----------------------------------------------------------------------*/

template <typename mod97_iter>
bool check_mod97(mod97_iter &begin, const mod97_iter &end, std::size_t nbr_digits)
{
  return false;
}

template <typename mod97_iter>
char compute_mod97(mod97_iter &begin, const mod97_iter &end, std::size_t nbr_digits)
{
  return false;
}

} // namespace checks
} // namespace boost

#endif // BOOST_CHECK_MODULUS_HPP

