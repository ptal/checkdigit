//  Boost checks/checksum.hpp header file
//  (C) Copyright Pierre Talbot 2013
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECK_TYPE_ADAPTOR_HPP
#define BOOST_CHECK_TYPE_ADAPTOR_HPP

#ifdef _MSC_VER
    #pragma once
#endif

#include <boost/mpl/size_t.hpp>
#include <boost/checks/checkdigit.hpp>

namespace boost {
  namespace checks{

// Some tags.
struct checkdigit_pos_tag{};
struct checkdigit_size_tag{};
struct checkdigit_encoder_tag{};
struct checkdigit_processor_tag{};

// The type adaptor structure with specialization on the tag.

template <class CurrentType, class tag, class NewType>
struct type_adaptor
{};

template <class P, class E, size_t p, size_t s, size_t newPos>
struct type_adaptor<checkdigit<P,E,p,s>, checkdigit_pos_tag, boost::mpl::size_t<newPos> >
{
  typedef checkdigit<P,E,newPos,s> type;
};

template <class P, class E, size_t p, size_t s, size_t newSize>
struct type_adaptor<checkdigit<P,E,p,s>, checkdigit_size_tag, boost::mpl::size_t<newSize> >
{
  typedef checkdigit<P,E,p,newSize> type;
};

template <class P, class E, size_t p, size_t s, class NewEncoder>
struct type_adaptor<checkdigit<P,E,p,s>, checkdigit_encoder_tag, NewEncoder>
{
  typedef checkdigit<P,NewEncoder,p,s> type;
};

template <class P, class E, size_t p, size_t s, class NewProcessor>
struct type_adaptor<checkdigit<P,E,p,s>, checkdigit_processor_tag, NewProcessor>
{
  typedef checkdigit<NewProcessor,E,p,s> type;
};

} // namespace checks
} // namespace boost

#endif // BOOST_CHECK_CHECKSUM_HPP
