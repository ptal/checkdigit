//  Boost checks/weighted_sum.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_BASIC_CHECK_ALGO_HPP
#define BOOST_CHECKS_BASIC_CHECK_ALGO_HPP

#include <boost/lexical_cast.hpp>
#include <boost/checks/traduction_exception.hpp>
#include <boost/checks/iteration_sense.hpp>

namespace boost{
  namespace checks{

template <typename iteration_sense, unsigned int number_of_virtual_value_skipped = 0>
struct basic_check_algorithm
{
  typedef iteration_sense iteration_sense ;

  template <typename value>
  static int traduce_to_valid_value(const value &current_value, const unsigned int valid_value_counter )
  {
    int valid_value = 0;
    try{
      valid_value = boost::lexical_cast<int>( current_value ) ;
    }catch( boost::bad_lexical_cast ){
      throw boost::checks::traduction_exception() ;
    }
    return valid_value ;
  }

  static void filter_valid_value_with_pos(const unsigned int current_valid_value, const unsigned int current_value_position )
  {
  }

  template <typename check_range>
  struct checkdigit
  {
    typedef typename boost::range_value<check_range>::type type;
  };
};


}}
#endif //BOOST_CHECKS_BASIC_CHECK_ALGO_HPP