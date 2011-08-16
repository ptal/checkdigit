//  Boost checks/weighted_sum.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_WEIGHTED_SUM_HPP
#define BOOST_CHECKS_WEIGHTED_SUM_HPP

#include <boost/checks/weight.hpp>
#include <boost/checks/iteration_sense.hpp>
#include <boost/checks/basic_check_algorithm.hpp>

namespace boost{
  namespace checks{

template <typename weight, typename iteration_sense, unsigned int number_of_virtual_value_skipped = 0>
struct weighted_sum_algorithm : boost::checks::basic_check_algorithm< iteration_sense >
{
  static void operate_on_valid_value( const int current_valid_value, const unsigned int valid_value_counter, int &checksum )
  {
    int current_weight = weight::weight_associated_with_pos( valid_value_counter + number_of_virtual_value_skipped ) ;
    checksum += current_valid_value * current_weight ;
  }
};

}}

#endif //BOOST_CHECKS_MOD10_HPP