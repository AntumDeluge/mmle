
#include <iostream>
#include <string>

using namespace std;

#include "MMLE.hpp"


int main() {
	cout << endl;
	cout << "Running paths tests ..." << endl;

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


	// TEST 1: normalizing path string

#ifdef WIN32
	target = "path\\to\\foo\\bar";
	string t1 = "path/to/foo/bar";
#else
	target = "path/to/foo/bar";
	string t1 = "path\\to\\foo\\bar";
#endif

	tcount++;
	result = MMLE::Path::norm(t1);

	if (target.compare(result) != 0) {
		cerr << "FAIL (test " << tcount << "): Expected \"" << target << "\" but got \"" << result
				<< "\"" << endl;
		fcount++;
		ret = 1;
	} else {
		pcount++;
	}


	// TEST 2: joining & normalizing path strings

#ifdef WIN32
	string t2s1 = "path/to";
	string t2s2 = "foo/bar";
#else
	string t2s1 = "path\\to";
	string t2s2 = "foo\\bar";
#endif

	tcount++;
	result = MMLE::Path::join(t2s1, t2s2);

	if (target.compare(result) != 0) {
		cerr << "FAIL (test " << tcount << "): Expected \"" << target << "\" but got \"" << result
				<< "\"" << endl;
		fcount++;
		ret = 1;
	} else {
		pcount++;
	}


	// TEST 3: getting path basename

	target = "bar";

#ifdef WIN32
	string t3 = "path/to/foo/bar";
#else
	string t3 = "path\\to\\foo\\bar";
#endif

	tcount++;
	result = MMLE::Path::basename(t3);

	if (target.compare(result) != 0) {
		cerr << "FAIL (test " << tcount << "): Expected \"" << target << "\" but got \"" << result
				<< "\"" << endl;
		fcount++;
		ret = 1;
	} else {
		pcount++;
	}


	// TEST 4: getting & normalizing directory path

#ifdef WIN32
	target = "path\\to\\foo";
	string t4 = "path/to/foo/bar";
#else
	target = "path/to/foo";
	string t4 = "path\\to\\foo\\bar";
#endif

	tcount++;
	result = MMLE::Path::dirname(t4);

	if (target.compare(result) != 0) {
		cerr << "FAIL (test " << tcount << "): Expected \"" << target << "\" but got \"" << result
				<< "\"" << endl;
		fcount++;
		ret = 1;
	} else {
		pcount++;
	}


	if (ret == 0) {
		cout << "OK: all tests passed" << endl;
	} else {
		cerr << "FAILURES: " << fcount << " failed tests" << endl;
	}
	cout << pcount << " out of " << tcount << " paths tests passing" << endl;

	return ret;
}
