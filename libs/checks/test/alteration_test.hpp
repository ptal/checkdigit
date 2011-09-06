//! \file
// alteration_test.hpp

// Copyright Pierre Talbot 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

//! \brief To test the efficiency of check algorithms in detecting alterations.

#ifndef BOOST_CHECK_TEST_ALTERATION_HPP
#define BOOST_CHECK_TEST_ALTERATION_HPP

template <typename functor>
unsigned int alteration( const functor &compute_checkdigit , int number_of_position_to_test )
{
  unsigned int alteration_failures = 0 ;

  std::string sequence = std::string() ;
  sequence.resize(number_of_position_to_test) ;
  for(int i=0; i < number_of_position_to_test; ++i)
    sequence[i] = '1' ;

  std::string alterate_seq = std::string();
  alterate_seq.resize(number_of_position_to_test) ;

  char checkdigit = compute_checkdigit( sequence );

  for(int i=0; i < number_of_position_to_test; ++i )
  {
    for(int j=0; j < number_of_position_to_test; ++j)
      alterate_seq[j] = '1' ;

    for(int j=0; j < 9; ++j)
    {
      alterate_seq[i] = '0' + ((alterate_seq[i]-'0'+1) % 10) ;

      if( compute_checkdigit( alterate_seq ) == checkdigit )
        ++alteration_failures ;
    }
  }
  return alteration_failures ;
}

#endif // BOOST_CHECK_TEST_ALTERATION_HPP
