
/* Copyright © 2017-2025 Jordan Irwin (AntumDeluge) <antumdeluge@gmail.com>
 *
 * This file is part of the MMLE project & is distributed under the
 * terms of the MIT/X11 license. See: LICENSE.txt
 */

#ifndef MMLE_STRING
#define MMLE_STRING

#include <string>


namespace MMLE {
	namespace String {

		/** Replaces all instances of substring in a string.
		 *
		 *  @param st
		 *      Source string.
		 *  @param a
		 *      Substring to be replaced.
		 *  @param b
		 *      String to be inserted in place.
		 *  @return
		 *      String.
		 */
		std::string replaceAll(std::string st, const std::string a, const std::string b);

		/** Checks for an empty string.
		 *
		 *  Checks string length & if contains only whitespace characters.
		 *
		 *  @param st
		 *      String to be checked.
		 *  @return
		 *      `true` if empty or only whitepace characters found.
		 */
		bool checkEmptyString(const std::string st);
	}
}

#endif /* MMLE_STRING */
