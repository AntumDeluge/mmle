
#include <iostream>

using namespace std;

#include "MMLE.hpp"


int main() {
	cout << endl;
	cout << "Running strings tests ..." << endl;

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
	bool result_b = false;
	string t_in = "";


	// TEST 1-4: replacing characters

	t_in = "foo/bar/baz";
	target = "foobarbaz";

	tcount++;
	result = MMLE::String::replaceAll(t_in, "/", "");

	if (target.compare(result) != 0) {
		cerr << "FAIL (test " << tcount << "): Expected \"" << target << "\" but got \"" << result
				<< "\"" << endl;
		fcount++;
		ret = 1;
	} else {
		pcount++;
	}

	target = "foo__bar__baz";

	tcount++;
	result = MMLE::String::replaceAll(t_in, "/", "__");

	if (target.compare(result) != 0) {
		cerr << "FAIL (test " << tcount << "): Expected \"" << target << "\" but got \"" << result
				<< "\"" << endl;
		fcount++;
		ret = 1;
	} else {
		pcount++;
	}

	target = "foo/bar/baz";

	tcount++;
	result = MMLE::String::replaceAll(t_in, "/oa", "");

	if (target.compare(result) != 0) {
		cerr << "FAIL (test " << tcount << "): Expected \"" << target << "\" but got \"" << result
				<< "\"" << endl;
		fcount++;
		ret = 1;
	} else {
		pcount++;
	}

	target = "f/bar/baz";

	tcount++;
	result = MMLE::String::replaceAll(t_in, "oo", "");

	if (target.compare(result) != 0) {
		cerr << "FAIL (test " << tcount << "): Expected \"" << target << "\" but got \"" << result
				<< "\"" << endl;
		fcount++;
		ret = 1;
	} else {
		pcount++;
	}


	// TEST 5-8: checking for empty strings

	tcount++;
	result_b = MMLE::String::checkEmptyString("");

	if (!result_b) {
		fcount++;
		ret = 1;
		cerr << "FAIL (test " << tcount << "): Expected " << !result_b << " but got " << result_b
				<< endl;
	} else {
		pcount++;
	}

	tcount++;
	result_b = MMLE::String::checkEmptyString(" \t	\r\n");

	if (!result_b) {
		fcount++;
		ret = 1;
		cerr << "FAIL (test " << tcount << "): Expected " << !result_b << " but got " << result_b
				<< endl;
	} else {
		pcount++;
	}

	tcount++;
	result_b = MMLE::String::checkEmptyString("f \t	\r\n");

	if (result_b) {
		fcount++;
		ret = 1;
		cerr << "FAIL (test " << tcount << "): Expected " << !result_b << " but got " << result_b
				<< endl;
	} else {
		pcount++;
	}

	tcount++;
	result_b = MMLE::String::checkEmptyString(" \t	f\r\n");

	if (result_b) {
		fcount++;
		ret = 1;
		cerr << "FAIL (test " << tcount << "): Expected " << !result_b << " but got " << result_b
				<< endl;
	} else {
		pcount++;
	}

	tcount++;
	result_b = MMLE::String::checkEmptyString(" \t	\r\nf");

	if (result_b) {
		fcount++;
		ret = 1;
		cerr << "FAIL (test " << tcount << "): Expected " << !result_b << " but got " << result_b
				<< endl;
	} else {
		pcount++;
	}


	if (ret == 0) {
		cout << "OK: all tests passed" << endl;
	} else {
		cerr << "FAILURES: " << fcount << " failed tests" << endl;
	}
	cout << pcount << " out of " << tcount << " strings tests passing" << endl;

	return ret;
}
