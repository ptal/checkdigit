//  Boost checks/size_check.hpp header file
//  (C) Copyright Pierre Talbot 2013
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKDIGIT_SIZE_CHECK_HPP
#define BOOST_CHECKDIGIT_SIZE_CHECK_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <exception>

namespace boost {
  namespace checkdigit{

class size_failure_exception : public std::exception
{
public:
  virtual const char * what() const throw()
  {
    return "Unexpected size of the sequence.";
  }
};

struct size_failure_error_code_policy
{
  static void fail(){}
};

template <class FailureException = size_failure_exception>
struct size_failure_exception_policy
{
  static void fail()
  {
    throw FailureException;
  }
};

template <size_t N, class SizeFailurePolicy = size_failure_error_code_policy>
struct size_checking
{
  static const size_t size = N;
  typedef SizeFailurePolicy size_failure_policy;
};

struct no_size_checking{};

} // namespace checkdigit
} // namespace boost

#endif // BOOST_CHECKDIGIT_SIZE_CHECK_HPP
