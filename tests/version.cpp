
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

#include "MMLE.hpp"


int main() {
	cout << endl;
	cout << "Running version tests ..." << endl;

	// number of run tests
	int tcount = 0;
	// number of passed tests
	int pcount = 0;
	// number of failed tests
	int fcount = 0;
	// return value of tests execution process
	int ret = 0;

	string target = "";
	string result = "";


	// TEST 1-3: version integers

	target = typeid(int).name();

	tcount++;
#ifndef MMLE_VER_MAJ
	result = "UNDEFINED";
#else
	result = typeid(MMLE_VER_MAJ).name();
#endif

	if (target.compare(result) != 0) {
		fcount++;
		ret = 1;
		cerr << "FAIL (test " << tcount << "): Expected type \"" << target << "\" but got \"" << result
				<< "\"" << endl;
	} else {
		pcount ++;
	}

	tcount++;
#ifndef MMLE_VER_MIN
	result = "UNDEFINED";
#else
	result = typeid(MMLE_VER_MIN).name();
#endif

	if (target.compare(result) != 0) {
		fcount++;
		ret = 1;
		cerr << "FAIL (test " << tcount << "): Expected type \"" << target << "\" but got \"" << result
				<< "\"" << endl;
	} else {
		pcount ++;
	}

	tcount++;
#ifndef MMLE_VER_REL
	result = "UNDEFINED";
#else
	result = typeid(MMLE_VER_REL).name();
#endif

	if (target.compare(result) != 0) {
		fcount++;
		ret = 1;
		cerr << "FAIL (test " << tcount << "): Expected type \"" << target << "\" but got \"" << result
				<< "\"" << endl;
	} else {
		pcount ++;
	}


	// TEST 4: version string

	target = typeid(char*).name();

	tcount++;
#ifndef MMLE_VERSION
	result = "UNDEFINED";
#else
	result = typeid(MMLE_VERSION).name();
#endif

	if (target.compare(result) != 0) {
		fcount++;
		ret = 1;
		cerr << "FAIL (test " << tcount << "): Expected type \"" << target << "\" but got \"" << result
				<< "\"" << endl;
	} else {
		pcount ++;
	}


	if (ret == 0) {
		cout << "OK: all tests passed" << endl;
	} else {
		cerr << "FAILURES: " << fcount << " failed tests" << endl;
	}
	cout << pcount << " out of " << tcount << " version tests passing" << endl;

	return ret;
}
