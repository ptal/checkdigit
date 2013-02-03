//  Boost checks/checkdigit.hpp header file
//  (C) Copyright Pierre Talbot 2012
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECK_CHECKDIGIT_HPP
#define BOOST_CHECK_CHECKDIGIT_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <cstddef> // size_t
#include <boost/lexical_cast.hpp>

namespace boost{
  namespace checks{

template <typename Result=char>
struct checkdigit_encoder
{
  typedef Result result_type;
  typedef size_t argument_type;

  result_type operator()(argument_type checksum)
  {
    return boost::lexical_cast<result_type>(checksum);
  }
};

struct checkdigitx_encoder
{
  typedef char result_type;
  typedef size_t argument_type;

  result_type operator()(argument_type checksum)
  {
    if(checksum == 10)
      return 'X';
    else
      return checkdigit_encoder<result_type>()(checksum);
  }
};

template
<
  typename Processor,
  typename Encoder,
  size_t position = 0,
  size_t size = 1
>
struct checkdigit
{
  typedef Processor processor_type;
  typedef Encoder encoder_type;
  static const size_t position_value;
  static const size_t size_value;

  typedef typename Encoder::result_type result_type;
  typedef typename Processor::argument_type argument_type;

  result_type operator()(argument_type value)
  {
    return Encoder()(Processor()(value));
  }
};

template
<
  typename Processor,
  typename Encoder,
  size_t position,
  size_t size
>
const size_t checkdigit<Processor, Encoder, position, size>::position_value = position;

template
<
  typename Processor,
  typename Encoder,
  size_t position,
  size_t size
>
const size_t checkdigit<Processor, Encoder, position, size>::size_value = size;

}} // namespace boost   namespace checks

#endif //BOOST_CHECK_CHECKDIGIT_HPP
