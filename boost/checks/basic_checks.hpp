//  Boost checks/modulus.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECK_BASIC_HPP
#define BOOST_CHECK_BASIC_HPP

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

    // Definition of the policy

// Direction : sum the number from the rightmost or the leftmost digit.

template <typename mod_range>
struct rightmost
{
  typedef typename boost::range_reverse_iterator<mod_range>::type mod_iterator ;
  typedef typename mod_range range ;

  static mod_iterator begin(range &mod_number) { return boost::rbegin(mod_number) ; }
  static mod_iterator end(range &mod_number)   { return boost::rend(mod_number) ; }
};

template <typename mod_range>
struct leftmost
{
  typedef typename boost::range_iterator<mod_range>::type mod_iterator ;
  typedef typename mod_range range ;
  static mod_iterator begin(range &mod_number) { return boost::begin(mod_number) ; }
  static mod_iterator end(range &mod_number)   { return boost::end(mod_number) ; }
};

// Size : wait for an expected number of digits or not.

template <size_t digits_expected>
struct mod_size
{
  static bool have_expected_size(unsigned int digits) { return digits == digits_expected ; }
};

struct no_size_set
{ 
  static bool have_expected_size(unsigned int digits) { return true ; }
};

// check digit : included (it's a check) or not, so we want it to be fictive (for a computation of it).
struct fictive_checkdigit
{
  template <typename mod_iter>
  static void skip_checkdigit(unsigned int &digit_counter, mod_iter &iter) { ++digit_counter ; ++iter; }
};

struct checkdigit_included
{
  template <typename mod_iter>
  static void skip_checkdigit(unsigned int &digit_counter, mod_iter &iter) { }
};

// Caution : About to change !!
// Weight policy

// Prototypes for the different size of non-type template argument (weight).
template <BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_CHECK_LIMIT_WEIGHTS, int weight, -1)>
struct weight_policy ;

#define _WEIGHT_factory(z,n,unused) \
  template<BOOST_PP_ENUM_PARAMS(n, int weight)> \
  struct weight_policy<BOOST_PP_ENUM_PARAMS(n, weight)> \
  { typedef typename boost::mpl::vector_c<int BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, weight)> weight ; } ; \

// Develop the macro _WEIGHT_factory BOOST_CHECK_LIMIT_WEIGHTS times.
BOOST_PP_REPEAT_FROM_TO(1,BOOST_CHECK_LIMIT_WEIGHTS,_WEIGHT_factory,~)
#undef _WEIGHT_factory 

// Generic policy

template <typename weight_policy, typename size_policy, typename checkdigit_policy, typename sum_direction>
struct mod_policy
{
  typedef typename sum_direction::mod_iterator mod_iterator ;
  typedef typename sum_direction::range mod_range ;

  typedef typename weight_policy::weight weight ;

  template <typename mod_iter>
  static void skip_checkdigit(unsigned int &digit_counter, mod_iter &iter) { checkdigit_policy::skip_checkdigit(digit_counter, iter); }

  static mod_iterator begin( mod_range &mod_number) { return sum_direction::begin( mod_number ) ; }
  
  static mod_iterator end( mod_range &mod_number) { return sum_direction::end( mod_number ) ; }

  static bool have_expected_size( unsigned int &current_size) { return size_policy::have_expected_size( current_size ) ; }

  template <typename character>
  static unsigned int characterToDigit(const character& mod10_character) = 0;

  template <typename opdata_t>
  static void init_opdata( opdata_t &opdata) = 0;

  template <typename weight_value, typename opdata_t>
  static unsigned int sum_operation(unsigned int &sum, unsigned int &digit, opdata_t &opdata ) = 0;

  static bool validate_checkdigit( const unsigned int &sum ) = 0;

  template <typename character>
  static character compute_checkdigit( const unsigned int &sum ) = 0;
};


// Here specialisation of policy for the handle of integer (return 10 instead of 'X') ? Use macro.. ?
// template<>
// struct policy_mod11<unsigned short> {};
// template <>
// struct policy_mod11<unsigned int>{};
// ...


template <typename character>
struct mod11_policy
{
  static unsigned int characterToDigit(const character& mod11_character)
  {
    return (mod11_character == 'x' || mod11_character == 'X') ? 10 :  boost::lexical_cast<unsigned int>(mod11_character);
  }
  static character compute_checkdigit( const unsigned int &check_digit)
  {
    return (check_digit == 10) ? 'X' : boost::lexical_cast<character>(check_digit) ;
  }
};

// Add to the running sum the digits of the sequence given.
// The digits added are selected according to the position of the weight given.
template<typename mod_policy, typename mod_range, size_t weight_sequence_size>
struct sum_with_weight
{
  private:
  // The position through the weight sequence.
  unsigned int& weight_position ;
  // The number.
  const mod_range& mod_number ;
  // Final sum.
  unsigned int& sum ;
 
  public:
  // Constructor.
  sum_with_weight(const mod_range& r, unsigned int &_sum, unsigned int &_weight_pos) : 
    weight_position(_weight_pos), mod_number(r), sum(_sum) {}
   
  // Treatment : Multiply the weight with the digits accumulate from mod11_number.
  template<typename weight, weight weight_value>
  void operator()(const boost::mpl::integral_c< weight , weight_value >&)
  {
    // Get the iterators
    mod_policy::mod_iterator mod_begin = mod_policy::begin(mod_number) ;
    mod_policy::mod_iterator mod_end = mod_policy::end(mod_number) ;

    // Should we skip a virtual checkdigit ..
    unsigned int digits_counted = 1 ;
    mod_policy::skip_checkdigit(digits_counted, mod_begin) ;

    mod_policy::opdata_type opdata ;
    mod_policy::init_operation_data( opdata );

    for( unsigned int digits_weighted = 0 ; mod_begin != mod_end ; ++mod_begin )
    {
      try{
        unsigned int current_digit = mod_policy::characterToDigit( *mod_begin ) ;
        if ( digits_counted++ % ( weight_position + digits_weighted * weight_size ) == 0 )
        {
          ++digits_weighted ;
          mod_policy::sum_operation<weight_value>(sum, current_digit, opdata ) ;
        }
      } catch( boost::bad_lexical_cast ) {} // Character ignored
    }
    ++weight_position ;
    // If too few or too much digits has been encountered, we throw an exception.
    if(digits_counted == 1 || !mod_policy::have_expected_size( digits_counted ))
      throw std::invalid_argument("Not enough or too much digits found in the sequence");
  }
};

// Internal check function.
template<typename mod_policy, typename mod_range>
unsigned int make_sum(const mod_range& mod_number)
{ 
  // If the sequence is empty we throw an exception.
  if( boost::empty(mod_number) )
    throw std::invalid_argument("Empty sequence");
  // Final sum.
  unsigned int sum = 0;
  unsigned int weight_position = 1 ;
  // For each weight, we call the functor "mod_sum".
  sum_with_weight<mod_policy, mod_range,  boost::mpl::size<mod_policy::weight>::value> mod_sum(mod_number, sum, weight_position);
  boost::mpl::for_each<mod_policy::weight>(mod_sum);
  // We return true if the check digit is correct. We return false otherwise.
  return sum;
}

template <typename mod_policy, typename mod_range>
bool check_number (const mod_range& mod_number)
{
  return mod_policy::validate_checkdigit( make_sum<mod_policy>( mod_number ) ) ;
}

template <typename mod_policy, typename mod_range>
typename boost::range_value<mod_range>::type compute_number (const mod_range& mod_number)
{
  return mod_policy::compute_checkdigit( make_sum<mod_policy>( mod_number ) ) ;
}

/*
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
}*/

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

#endif // BOOST_CHECK_BASIC_HPP

