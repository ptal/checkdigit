//! \file transposition_test.hpp

// Copyright Pierre Talbot 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_CHECK_TEST_TRANSPOSITION_HPP
#define BOOST_CHECK_TEST_TRANSPOSITION_HPP

template <typename functor>
unsigned int transposition( const functor &compute_checkdigit )
{
  unsigned int transposition_failures = 0 ;

  std::string sequence = "00" ;
  std::string transpose_seq = "00" ;

  for(int i=0; i <= 9; ++i )
  {
    for(int j=0; j <= 9; ++j)
    {
      if(i != j)
      {
        sequence[0] = i | '0' ;
        sequence[1] = j | '0' ;

        transpose_seq[0] = sequence[1] ;
        transpose_seq[1] = sequence[0] ;

        if( compute_checkdigit( sequence ) ==
            compute_checkdigit( transpose_seq) )
            ++transposition_failures ;
      }
    }
  }
  return transposition_failures ;
}

#endif // BOOST_CHECK_TEST_TRANSPOSITION_HPP