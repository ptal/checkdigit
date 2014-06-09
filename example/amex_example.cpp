// Copyright Pierre Talbot 2013.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file is written to be included from a Quickbook .qbk document.
// It can be compiled by the C++ compiler, and run. Any output can
// also be added here as comment or included or pasted in elsewhere.
// Caution: this file contains Quickbook markup as well as code
// and comments: don't change any of the special comment markups!

//[amex_example
#include <string>
#include <boost/checkdigit/amex.hpp>

using namespace boost::checkdigit;

int main()
{
  std::string amex_no("3782-822463-1000");
  boost::optional<char> checkdigit = compute_checkdigit<amex>(amex_no);
  amex_no += *checkdigit;
  if(validate<amex>(amex_no))
    std::cout << amex_no << " is a valid american express card number." << std::endl;
}
//]