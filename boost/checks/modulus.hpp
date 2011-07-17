//  Boost checks/modulus.hpp header file  ------------------------------------//
//  (C) Copyright Pierre Talbot 2011
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_CHECK_MODULUS_HPP
#define BOOST_CHECK_MODULUS_HPP

#ifdef _MSC_VER
    #pragma once
#endif // _MSC_VER

namespace boost {
    namespace checks{

template <typename luhn_iter>
bool check_luhn(luhn_iter &begin, const luhn_iter &end, std::size_t nbr_digits)
{
  // If the number of digits isn't given (equal to 0), we count these.
  if(!nbr_digits)
  {
	luhn_iter iter = begin;
	while(iter != end)
	{
      if(*iter >= '0' && *iter <= '9')
        ++nbr_digits;
	  ++iter;
	}
	// Return false if there is no digit in the expression given.
	if(!nbr_digits)
	{
	  begin = end;
	  return false;
	}
  }
  int sum = 0,v;
  /* We start with the leftmost digit and we multiply by two 
   * if the total number of digit is even. We alternate the multiplication
   * for all the digits. We subtract 9 from the digit greater than 9 
   * after the multiplication. */
  while(nbr_digits > 0 && begin != end)
  {
    if(*begin >= '0' && *begin <= '9')
		sum += (v= (*begin & 15) << (--nbr_digits&1)) - 9 * (v>9);
	++begin;
  }
  // Return true if the number of digit is equal to the number specified and the sum is valid.
  return !nbr_digits && !(sum % 10) ;
}

template <typename luhn_iter>
char compute_luhn(luhn_iter &begin, const luhn_iter &end, std::size_t nbr_digits)
{
  // If the number of digits isn't given (equal to 0), we count these.
  if(!nbr_digits)
  {
	luhn_iter iter = begin;
	while(iter != end)
	{
      if(*iter >= '0' && *iter <= '9')
        ++nbr_digits;
	  ++iter;
	}
	// Return 0 if there is no digit in the expression given.
	if(!nbr_digits)
	{
	  begin = end;
	  return 0;
	}
  }
  int sum = 0,v;
  /* We start with the leftmost digit and we multiply by two 
   * if the total number of digit is odd. We alternate the multiplication
   * for all the digits. We subtract 9 from the digit greater than 9 
   * after the multiplication. */
  while(nbr_digits > 0 && begin != end)
  {
    if(*begin >= '0' && *begin <= '9')
		sum += (v= (*begin & 15) << (nbr_digits--&1)) - 9 * (v>9);
	++begin;
  }
  return (10 - sum % 10) % 10 | '0';
}

template <typename luhn_checkdigit, typename luhn_iter>
luhn_checkdigit compute_luhn(luhn_iter &begin, const luhn_iter &end, std::size_t nbr_digits)
{
  // If the number of digits isn't given (equal to 0), we count these.
  if(!nbr_digits)
  {
	luhn_iter iter = begin;
	while(iter != end)
	{
      if(*iter >= '0' && *iter <= '9')
        ++nbr_digits;
	  ++iter;
	}
	// Return 0 if there is no digit in the expression given.
	if(!nbr_digits)
	{
	  begin = end;
	  return 0;
	}
  }
  int sum = 0,v;
  /* We start with the leftmost digit and we multiply by two 
   * if the total number of digit is even. We alternate the multiplication
   * for all the digits. We subtract 9 from the digit greater than 9 
   * after the multiplication. */
  while(nbr_digits > 0 && begin != end)
  {
    if(*begin >= '0' && *begin <= '9')
		sum += (v= (*begin & 15) << (nbr_digits--&1)) - 9 * (v>9);
	++begin;
  }
  return ((10 - sum % 10) % 10) | '0';
}

template <typename mod10_iter, typename weight_t>
bool check_mod10(mod10_iter &begin, const mod10_iter &end, const weight_t &weight, std::size_t nbr_digits)
{
  // If the weight have a size of zero, we apply a weight of 1 on each digit.
  if( !weight.size() )
    return false;

  // If the number of digits isn't given (equal to 0), we count these.
  if(!nbr_digits)
  {
	mod10_iter iter = begin;
	while(iter != end)
	{
      if(*iter >= '0' && *iter <= '9')
        ++nbr_digits;
	  ++iter;
	}
	// Return false if there is no digit in the expression given.
	if(!nbr_digits)
	{
	  begin = end;
	  return false;
	}
  }
  int sum = 0;
  /* We start with the leftmost digit and we multiply by the weight indicated.
   * The sum of all digits is computed. */
  for(int i=0; nbr_digits > 0 && begin != end; ++i, --nbr_digits)
  {
    if(*begin >= '0' && *begin <= '9')
		sum += (*begin & 15) * weight[i % weight.size()] ;
	++begin;
  }
  // Return true if the number of digit is equal to the number specified and the sum is valid.
  return !nbr_digits && !(sum % 10) ;
}

template <typename mod10_iter, typename weight_t>
char compute_mod10(mod10_iter &begin, const mod10_iter &end, const weight_t &weight, std::size_t nbr_digits)
{
  // If the weight have a size of zero, we apply a weight of 1 on each digit.
  if( !weight.size() )
    return 0;

  // If the number of digits isn't given (equal to 0), we count these.
  if(!nbr_digits)
  {
	mod10_iter iter = begin;
	while(iter != end)
	{
      if(*iter >= '0' && *iter <= '9')
        ++nbr_digits;
	  ++iter;
	}
	// Return false if there is no digit in the expression given.
	if(!nbr_digits)
	{
	  begin = end;
	  return 0;
	}
  }
  int sum = 0;
  /* We start with the leftmost digit and we multiply by the weight indicated.
   * The sum of all digits is computed. */
  for(int i=0; nbr_digits > 0 && begin != end; ++i, --nbr_digits)
  {
    if(*begin >= '0' && *begin <= '9')
		sum += (*begin & 15) * weight[i % weight.size()] ;
	++begin;
  }
  if(nbr_digits > 0)
  {
    begin = end;
    return 0;
  }
  return (10 - sum % 10) % 10 | '0' ;
}

template <typename mod10_checkdigit, typename mod10_iter, typename weight_t>
mod10_checkdigit compute_mod10(mod10_iter &begin, const mod10_iter &end, const weight_t &weight, std::size_t nbr_digits)
{
  if( !weight.size() )
    return 0;

  // If the number of digits isn't given (equal to 0), we count these.
  if(!nbr_digits)
  {
	mod10_iter iter = begin;
	while(iter != end)
	{
      if(*iter >= '0' && *iter <= '9')
        ++nbr_digits;
	  ++iter;
	}
	// Return false if there is no digit in the expression given.
	if(!nbr_digits)
	{
	  begin = end;
	  return 0;
	}
  }
  int sum = 0;
  /* We start with the leftmost digit and we multiply by the weight indicated.
   * The sum of all digits is computed. */
  for(int i=0; nbr_digits > 0 && begin != end; ++i, --nbr_digits)
  {
    if(*begin >= '0' && *begin <= '9')
		sum += (*begin & 15) * weight[i % weight.size()] ;
	++begin;
  }
  if(nbr_digits > 0)
  {
    begin = end;
    return 0;
  }
  return (10 - sum % 10) % 10 | '0' ;
}

template <typename mod11_iter>
bool check_mod11(mod11_iter &begin, const mod11_iter &end, std::size_t nbr_digits)
{
  mod11_iter iter = begin;
  // If the number of digits isn't given (equal to 0), we count these.
  if(!nbr_digits)
  {
	while(iter != end)
	{
      if(*iter >= '0' && *iter <= '9')
        ++nbr_digits;
      else if(*iter == 'x' || *iter == 'X')
      {
        ++nbr_digits;
        break;
      }
	  ++iter;
	}
	// Return false if there is no digit in the expression given.
	if(!nbr_digits)
	{
	  begin = end;
	  return false;
	}
    iter = begin;
  }
  int sum = 0;
  // Sum the n-1 first digit with a weigth of n. (The weigth is the contribution
  // of a digit to the final sum).
  while(nbr_digits > 1 && iter != end)
  {
    if(*begin >= '0' && *begin <= '9')
	  sum += (*begin & 15) * nbr_digits--;
	++begin;
  }
  // Add the check digit to the sum (add 10 if the check digit equals 'x' or 'X').
  while(begin != end)
  {
    if(*begin >= '0' && *begin <= '9')
	{
	  sum += *begin & 15;
	  --nbr_digits;
	  break;
    }
	else if(*begin == 'x' || *begin == 'X')
	{
	  sum += 10;
	  --nbr_digits;
	  break;
	}
	else
	  ++iter;
  }
  // Return true if the number of digit is equal to the number specified and the sum is valid.
  return !nbr_digits && !(sum % 11);
}

template <typename mod11_iter>
char compute_mod11(mod11_iter &begin, const mod11_iter &end, std::size_t nbr_digits)
{
  mod11_iter iter = begin;
  // If the number of digits isn't given (equal to 0), we count these.
  if(!nbr_digits)
  {
	while(iter != end)
	{
      if(*iter >= '0' && *iter <= '9') // 'X' is only the check digit so we ignore it...
        ++nbr_digits;
	  ++iter;
	}
	// Return 0 if there is no digit in the expression given.
	if(!nbr_digits)
	{
	  begin = end;
	  return 0;
	}
    iter = begin;
  }
  int sum = 0;
  // Sum the digits with a weigth of nbr_digits. (The weigth is the contribution
  // of a digit to the final sum).
  ++nbr_digits; // Adding the unknown check digit to the size...
  while(nbr_digits > 1 && iter != end)
  {
    if(*begin >= '0' && *begin <= '9')
	  sum += (*begin & 15) * nbr_digits-- ;
	++begin;
  }
  if(nbr_digits > 1)
    return 0;
  
  // Compute the check digit.
  char check_digit = (11 - sum % 11) %11;
  if(check_digit == 10)
    return 'X';
  return check_digit | '0';
}

template <typename mod11_checkdigit, typename mod11_iter>
mod11_checkdigit compute_mod11(mod11_iter &begin, const mod11_iter &end, std::size_t nbr_digits)
{
  mod11_iter iter = begin;
  // If the number of digits isn't given (equal to 0), we count these.
  if(!nbr_digits)
  {
	while(iter != end)
	{
      if(*iter >= '0' && *iter <= '9') // 'X' is only the check digit so we ignore it...
        ++nbr_digits;
	  ++iter;
	}
	// Return 0 if there is no digit in the expression given.
	if(!nbr_digits)
	{
	  begin = end;
	  return 0;
	}
    iter = begin;
  }
  int sum = 0;
  // Sum the digits with a weigth of nbr_digits. (The weigth is the contribution
  // of a digit to the final sum).
  ++nbr_digits; // Adding the unknown check digit to the size...
  while(nbr_digits > 1 && iter != end)
  {
    if(*begin >= '0' && *begin <= '9')
	  sum += (*begin & 15) * nbr_digits-- ;
	++begin;
  }
  if(nbr_digits > 1)
    return 0;
  
  // Compute the check digit.
  int check_digit = (11 - sum % 11) %11;
  if(check_digit == 10)
    return 'X';
  return check_digit | '0';
}

template <typename mod97_iter>
bool check_mod97(mod97_iter &begin, const mod97_iter &end, std::size_t nbr_digits)
{
  return false;
}

template <typename mod97_iter>
char compute_mod97(mod97_iter &begin, const mod97_iter &end, std::size_t nbr_digits)
{
  return false;
}

} // namespace checks
} // namespace boost

#endif // BOOST_CHECK_MODULUS_HPP

