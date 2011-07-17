//  Boost checks/checks_fwd.hpp header file //

//  (C) Copyright Pierre Talbot 2011

//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org for updates, documentation, and revision history.

// Provides a (perhaps temporary) mainpage for standalone Doxygen.
// This seems a convenient place to put this, but it could go somewhere else?

/*!
\file
\brief Boost.Checks forward declaration of function signatures.
\details This file can be used to copy a function signature,
but is mainly provided for testing purposes.

\mainpage

\b Boost.Checks

This is the standalone Doxygen front page of the Boost.Checks library.

This library provides a collection of functions for validating and creating check digits.

Most are primarily for checking the accuracy of short strings of typed input
(though obviously also provides against a mis-scan
by a device like a bar code or card reader, or transmission error).

The well-known ISBN is a typical example.
All single altered digits, most double altered digits,
and all transpositions of two digits are caught,
and the input rejected as an invalid ISBN.

See Boost.Checks HTML Manual at

  https://svn.boost.org/svn/boost/sandbox/SOC/2011/checks/doc/html/index.html

and/or equivalent PDF Manual at:

  https://svn.boost.org/svn/boost/sandbox/SOC/2011/checks/doc/checks.pdf

Examples are in folder:

  https://svn.boost.org/svn/boost/sandbox/SOC/2011/checks/libs/checks/example/

and C++ include files are in folder:

  https://svn.boost.org/svn/boost/sandbox/SOC/2011/checks/boost/checks/

*/

#ifndef BOOST_CHECK_CHECKS_FWD_HPP
#define BOOST_CHECK_CHECKS_FWD_HPP

#ifdef _MSC_VER
    #pragma once
#endif // _MSC_VER

#include <boost/array.hpp>

namespace boost{
  namespace checks{

// Provides forward declaration of all Boost.Checks functions:

/** Validate the check digit of the number provided with the Luhn algorithm.
 * \tparam luhn_iter Iterator with at least the caracteristics of an input iterator. It The beginning or the ending of a sequence of character. 
 * \param[in,out] begin The beginning of the sequence to check.
 * \param[in] end One off the limit of the sequence to check.
 * \param[in] nbr_digits The number of digits on which the Luhn algorithm will operate. If the size is < 1, the luhn algorithm will validate the check digit with all the digit encountered.
 * \pre The parameters begin and end must be two valid initialized iterators. They represent a sequence of character encoded in big-endian mode in a format compatible with the 7 bits ASCII.
 * \post begin is equal to the position of the check digit plus one if the expression provided is correct, otherwise is equal to end.
 * \returns true is returned if the expression given have a valid check digit and have nbr_digits (or more than 0 digit if nbr_digits is equal to 0).
 */
    template <typename luhn_iter>
    bool check_luhn(luhn_iter &begin, const luhn_iter &end, std::size_t nbr_digits=0);

/** Calculate the check digit of the number provided with the Luhn algorithm.
 * \tparam luhn_iter Iterator with at least the caracteristics of an input iterator. It The beginning or the ending of a sequence of character. 
 * \param[in,out] begin The beginning of the sequence to check.
 * \param[in] end One off the limit of the sequence to check.
 * \param[in] nbr_digits The number of digits on which the Luhn algorithm will operate. If the size is < 1, the luhn algorithm will calculate the check digit with all the digit encountered.
 * \pre begin and end are valid initialized iterators. They represent a sequence of character encoded in big-endian mode in a format compatible with the 7 bits ASCII.
 * \post begin is equal to the position of the last digit encountered plus one if the expression provided is correct, otherwise is equal to end.
 * \returns 0 is returned if the expression given have not nbr_digits (or no digit if nbr_digits is equal to 0). Otherwise the ASCII character of the check digit is returned.
 */
	template <typename luhn_iter>
    char compute_luhn(luhn_iter &begin, const luhn_iter &end, std::size_t nbr_digits=0);
	
/** Calculate the check digit of the number provided with the Luhn algorithm.
 * \tparam luhn_iter Iterator with at least the caracteristics of an input iterator. It The beginning or the ending of a sequence of character. 
 * \tparam luhn_checkdigit Type in which the check digit will be returned.
 * \param[in,out] begin The beginning of the sequence to check.
 * \param[in] end One off the limit of the sequence to check.
 * \param[in] nbr_digits The number of digits on which the Luhn algorithm will operate. If the size is < 1, the luhn algorithm will calculate the check digit with all the digit encountered.
 * \pre begin and end are valid initialized iterators. They represent a sequence of character encoded in big-endian mode in a format compatible with the 7 bits ASCII.
 * \post begin is equal to the position of the last digit encountered plus one if the expression provided is correct, otherwise is equal to end.
 * \returns 0 is returned if the expression given have not nbr_digits (or no digit if nbr_digits is equal to 0). Otherwise the ASCII character of the check digit is returned.
 */
	template <typename luhn_checkdigit, typename luhn_iter>
    luhn_checkdigit compute_luhn(luhn_iter &begin, const luhn_iter &end, std::size_t nbr_digits=0);

/** Validate the check digit of the number provided with the modulus 10 algorithm.
 * \tparam mod10_iter Iterator with at least the caracteristics of an input iterator. It The beginning or the ending of a sequence of character. 
 * \tparam weight_t Contains numeric values (should be unsigned) assigned to the weight of the digits.
 * \param[in,out] begin The beginning of the sequence to check.
 * \param[in] end One off the limit of the sequence to check.
 * \param[in] weight The weight pattern of the sequence starting on the left of the expression. The size of weight should be greater than 0.
 * \param[in] nbr_digits The number of digits on which the modulus 10 algorithm will operate. If the size is < 1, the modulus 10 algorithm will validate the check digit with all the digit encountered.
 * \pre begin and end are valid initialized iterators. They represent a sequence of character encoded in big-endian mode in a format compatible with the 7 bits ASCII.
 * \post begin is equal to the position of the check digit plus one if the expression provided is correct, otherwise is equal to end. 
 * \returns true is returned if the expression given have a valid check digit and have nbr_digits (or more than 0 digit if nbr_digits is equal to 0) and if the size of weight is greater than 0. Returns false otherwise.
 */
    template <typename mod10_iter, typename weight_t >
    bool check_mod10(mod10_iter &begin, const mod10_iter &end, const weight_t &weight, std::size_t nbr_digits=0);

/** Compute the check digit of the number provided with the modulus 10 algorithm.
 * \tparam mod10_iter with at least the caracteristics of an input iterator. It The beginning or the ending of a sequence of character. 
 * \tparam weight_t Contains numeric values (should be unsigned) assigned to the weight of the digits.
 * \param[in,out] begin The beginning of the sequence to check.
 * \param[in] end One off the limit of the sequence to check.
 * \param[in] weight The weight pattern of the sequence starting on the left of the expression. The size of weight should be greater than 0.
 * \param[in] nbr_digits The number of digits on which the modulus 10 algorithm will operate. If the size is < 1, the modulus 10 algorithm will calculate the check digit with all the digit encountered.
 * \pre begin and end are valid initialized iterators. They represent a sequence of character encoded in big-endian mode in a format compatible with the 7 bits ASCII.
 * \post begin is equal to the position of the last digit encountered plus one if the expression provided is correct, otherwise is equal to end.
 * \returns 0 is returned if the expression given have not nbr_digits (or no digit if nbr_digits is equal to 0) or weight have a size of 0. Otherwise the ASCII character of the check digit is returned.
 */
    template <typename mod10_iter, typename weight_t>
    char compute_mod10(mod10_iter &begin, const mod10_iter &end, const weight_t &weight, std::size_t nbr_digits=0);

/** Compute the check digit of the number provided with the modulus 10 algorithm.
 * \tparam mod10_iter Iterator with at least the caracteristics of an input iterator. It The beginning or the ending of a sequence of character. 
 * \tparam mod10_checkdigit Type in which the check digit will be returned.
 * \tparam weight_t Contains numeric values (should be unsigned) assigned to the weight of the digits.
 * \param[in,out] begin The beginning of the sequence to check.
 * \param[in] end One off the limit of the sequence to check.
 * \param[in] weight The weight pattern of the sequence starting on the left of the expression. The size of weight should be greater than 0.
 * \param[in] nbr_digits The number of digits on which the modulus 10 algorithm will operate. If the size is < 1, the modulus 10 algorithm will calculate the check digit with all the digit encountered.
 * \pre begin and end are valid initialized iterators. They represent a sequence of character encoded in big-endian mode in a format compatible with the 7 bits ASCII.
 * \post begin is equal to the position of the last digit encountered plus one if the expression provided is correct, otherwise is equal to end.
 * \returns 0 is returned if the expression given have not nbr_digits (or no digit if nbr_digits is equal to 0) or weight have a size of 0. Otherwise the ASCII character of the check digit is returned.
 */
    template <typename mod10_checkdigit, typename mod10_iter, typename weight_t>
    mod10_checkdigit compute_mod10(mod10_iter &begin, const mod10_iter &end, const weight_t &weight, std::size_t nbr_digits=0);

/** Calculate the check digit of the number provided with the modulus 11 algorithm.
 * \tparam mod11_iter Iterator with at least the caracteristics of an input iterator. It The beginning or the ending of a sequence of character. 
 * \param[in,out] begin The beginning of the sequence to check.
 * \param[in] end One off the limit of the sequence to check.
 * \param[in] nbr_digits The number of digits on which the MOD11 algorithm will operate. If the size is < 1, the MOD11 algorithm will calculate the check digit with all the digit encountered. 
                         If the size isn't precised and if the character 'X' or 'x' is encountered, the end of the number will be considered ; 
                         if the size is precised, the character 'X' or 'x' will be ignored unless it is the last character.
 * \pre begin and end are valid initialized iterators. They represent a sequence of character encoded in big-endian mode in a format compatible with the 7 bits ASCII.
 * \post begin is equal to the position of the last digit encountered plus one if the expression provided is correct, otherwise is equal to end.
 * \returns 0 is returned if the expression given have not nbr_digits (or no digit if nbr_digits is equal to 0). Otherwise the ASCII character of the check digit is returned.
*/
    template <typename mod11_iter>
    bool check_mod11(mod11_iter &begin, const mod11_iter &end, std::size_t nbr_digits=0);

/** Validate the check digit of the number provided with the modulus 11 algorithm.
 * \tparam mod11_iter Iterator with at least the caracteristics of an input iterator. It The beginning or the ending of a sequence of character. 
 * \param[in,out] begin The beginning of the sequence to check.
 * \param[in] end One off the limit of the sequence to check.
 * \param[in] nbr_digits The number of digits on which the Luhn algorithm will operate. If the size is < 1, the luhn algorithm will validate the check digit with all the digit encountered.
 * \pre begin and end are valid initialized iterators. They represent a sequence of character encoded in big-endian mode in a format compatible with the 7 bits ASCII.
 * \post begin is equal to the position of the check digit plus one if the expression provided is correct, otherwise is equal to end.
 * \returns true is returned if the expression given have a valid check digit and have nbr_digits (or more than 0 digit if nbr_digits is equal to 0).
 */
    template <typename mod11_iter>
    char compute_mod11(mod11_iter &begin, const mod11_iter &end, std::size_t nbr_digits=0);

/** Validate the check digit of the number provided with the modulus 11 algorithm.
 * \tparam mod11_iter Iterator with at least the caracteristics of an input iterator. It The beginning or the ending of a sequence of character. 
 * \tparam mod11_checkdigit Type in which the check digit will be returned.
 * \param[in,out] begin The beginning of the sequence to check.
 * \param[in] end One off the limit of the sequence to check.
 * \param[in] nbr_digits The number of digits on which the Luhn algorithm will operate. If the size is < 1, the luhn algorithm will validate the check digit with all the digit encountered.
 * \pre begin and end are valid initialized iterators. They represent a sequence of character encoded in big-endian mode in a format compatible with the 7 bits ASCII. 
 * \post begin is equal to the position of the check digit plus one if the expression provided is correct, otherwise is equal to end.
 * \returns true is returned if the expression given have a valid check digit and have nbr_digits (or more than 0 digit if nbr_digits is equal to 0).
 */
    template <typename mod11_checkdigit, typename mod11_iter>
    mod11_checkdigit compute_mod11(mod11_iter &begin, const mod11_iter &end, std::size_t nbr_digits=0);

    


    /*!!!
The modulus 97 algorithm wait for a sequence of numbers only ! and will not do anything else that sum the digits and calculate the modulus of this sum.
If you need to check an IBAN use the algorithms in iban.hpp */

/** Compute the check digit of the number provided with the modulus 97 algorithm.
 * \tparam mod97_iter Iterator with at least the caracteristics of an input iterator. It represents the beginning or the ending of a sequence of character. 
 * \param[in,out] begin The beginning of the sequence to check.
 * \param[in] end One off the limit of the sequence to check.
 * \param[in] nbr_digits The number of digits on which the modulus 97 algorithm will operate. If the size is < 1, the modulus 97 algorithm will calculate the check digit with all the digit encountered.
 * \pre begin and end are valid initialized iterators. They represent a sequence of character encoded in big-endian mode in a format compatible with the 7 bits ASCII.
 * \post begin is equal to the position of the last digit encountered plus one if the expression provided is correct, otherwise is equal to end.
 * \returns 0 is returned if the expression given have not nbr_digits (or no digit if nbr_digits is equal to 0). Otherwise the ASCII characters of the check digits are returned.
 */

  template <typename mod97_iter>
  char compute_mod97(mod97_iter &begin, const mod97_iter &end, std::size_t nbr_digits=0);

/** Validate the check digit of the number provided with the modulus 97 algorithm.
 * \tparam mod97_iter Iterator with at least the caracteristics of an input iterator. It represents the beginning or the ending of a sequence of character. 
 * \param[in,out] begin The beginning of the sequence to check.
 * \param[in] end One off the limit of the sequence to check.
 * \param[in] nbr_digits The number of digits on which the modulus 97 algorithm will operate. If the size is < 1, the modulus 97 algorithm will validate the check digit with all the digit encountered.
 * \pre begin and end are valid initialized iterators. They represent a sequence of character encoded in big-endian mode in a format compatible with the 7 bits ASCII.
 * \post begin is equal to the position of the check digits plus one if the expression provided is correct, otherwise is equal to end. 
 * \returns true is returned if the expression given have a valid check digit and have nbr_digits (or more than 0 digit if nbr_digits is equal to 0).
 */
    template <typename mod97_iter>
    bool check_mod97(mod97_iter &begin, const mod97_iter &end, std::size_t nbr_digits=0);

  }
}

#endif \\ BOOST_CHECK_CHECKS_FWD_HPP