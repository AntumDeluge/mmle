
/* Copyright © 2017-2025 Jordan Irwin (AntumDeluge) <antumdeluge@gmail.com>
 *
 * This file is part of the MMLE project & is distributed under the
 * terms of the MIT/X11 license. See: LICENSE.txt
 */

using namespace std;

#include "MMLE/String.hpp"


string MMLE::String::replaceAll(string st, const string a, const string b) {
	if (a == b) {
		// don't get stuck in an infinite loop
		return st;
	}

	// number of characters to replace
	int to_replace = a.length();
	int pos = st.find(a);
	while (pos > -1) {
		st = st.substr(0, pos) + b + st.substr(pos + to_replace, st.length() - pos);
		pos = st.find(a);
	}

	return st;
}


bool MMLE::String::checkEmptyString(const string st) {
	if (st.empty()) {
		return true;
	}

	if (st.find_first_not_of(' ') == string::npos) {
		if (st.find_first_not_of('\t') == string::npos) {
			if (st.find_first_not_of('\n') == string::npos) {
				if (st.find_first_not_of('\r') == string::npos) {
					return true;
				}
			}
		}
	}

	return false;
}
