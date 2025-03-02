
/* Copyright © 2017-2025 Jordan Irwin (AntumDeluge) <antumdeluge@gmail.com>
 *
 * This file is part of the MMLE project & is distributed under the
 * terms of the MIT/X11 license. See: LICENSE.txt
 */

#ifndef MMLE_TIME
#define MMLE_TIME

#include <string>


namespace MMLE {
	namespace Time {

		/** Retrieves current timestamp in milliseconds. */
		extern long long currentTimeMillis();

		/** Formats duration for printing.
		 *
		 *  @param ts
		 *      Process start timestamp (milliseconds).
		 *  @param te
		 *      Process end timestamp (milliseconds).
		 *  @return
		 *      String formatted for readability.
		 */
		extern std::string formatDuration(const long long ts, const long long te);
	}
}

#endif /* MMLE_TIME */
