//  Boost checks/translation_exception.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECKS_translation_EXCEPTION_HPP
#define BOOST_CHECKS_translation_EXCEPTION_HPP

#include <exception>

namespace boost{
  namespace checks{

  class translation_exception : public std::exception
  {
  };
  
}}

#endif // BOOST_CHECKS_translation_EXCEPTION_HPP