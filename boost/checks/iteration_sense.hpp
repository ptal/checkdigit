//  Boost checks/iteration_sense.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

/*! \file iteration_sense.hpp
    \brief Provides two sense of iteration to run through the sequence from right to left or left to right.
*/


#ifndef BOOST_CHECK_ITERATION_SENSE_HPP
#define BOOST_CHECK_ITERATION_SENSE_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/range/reverse_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/const_reverse_iterator.hpp>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>

namespace boost{
  namespace checks{

/*! \class rightmost
    \brief Policy class that provides methods to run through a sequence from right to left.
*/
struct rightmost
{
  /*! \class iterator
      \brief Template rebinding class used to define the type of a const reverse iterator for seq_range.

      \tparam seq_range The type of the sequence to check.
  */
  template <typename seq_range>
  struct iterator
  {
    typedef typename boost::range_const_reverse_iterator<seq_range>::type type ;
  };

  /*! \fn static typename iterator<seq_range>::type begin(seq_range &sequence)
      \brief Get the beginning of the sequence.

      \tparam seq_range The type of the sequence to check.
      \returns A reverse iterator represents the beginning of the sequence.
  */
  template <typename seq_range>
  static typename iterator<seq_range>::type begin(seq_range &sequence) { return boost::rbegin(sequence) ; }

  /*! \fn static typename iterator<seq_range>::type end(seq_range &sequence)
      \brief Get the ending of the sequence.

      \tparam seq_range The type of the sequence to check.
      \returns A reverse iterator represents one pass the end of the sequence.
  */
  template <typename seq_range>
  static typename iterator<seq_range>::type end(seq_range &sequence)   { return boost::rend(sequence) ; }
};

/*! \class leftmost
    \brief Policy class that provides methods to run through a sequence from left to right.
*/
struct leftmost
{
  /*! \class iterator
      \brief Template rebinding class used to define the type of a const iterator for seq_range.

      \tparam seq_range The type of the sequence to check.
  */
  template <typename seq_range>
  struct iterator
  {
    typedef typename boost::range_const_iterator<seq_range>::type type ;
  };

  /*! \fn static typename iterator<seq_range>::type begin(seq_range &sequence)
      \brief Get the beginning of the sequence.

      \tparam seq_range The type of the sequence to check.
      \returns An iterator represents the beginning of the sequence.
  */
  template <typename seq_range>
  static typename iterator<seq_range>::type begin(seq_range &sequence) { return boost::begin(sequence) ; }
  
  /*! \fn static typename iterator<seq_range>::type end(seq_range &sequence)
      \brief Get the ending of the sequence.

      \tparam seq_range The type of the sequence to check.
      \returns An iterator represents one pass the end of the sequence.
  */
  template <typename seq_range>
  static typename iterator<seq_range>::type end(seq_range &sequence)   { return boost::end(sequence) ; }
};


}}
#endif // BOOST_CHECKS_ITERATION_SENSE_HPP