//  Boost checks/translation_exception.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file translation_exception.hpp
    \brief This file provides an exception class used when the translation of a value failed.
*/

#ifndef BOOST_CHECKS_translation_EXCEPTION_HPP
#define BOOST_CHECKS_translation_EXCEPTION_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <exception>

namespace boost{
  namespace checks{
/*! \class translation_exception
    \brief This class provides support for translation failure. For example, sequence value into integer, or integer into check digit type.
*/
  class translation_exception : public std::exception
  {
  };
  
}}

#endif // BOOST_CHECKS_translation_EXCEPTION_HPP