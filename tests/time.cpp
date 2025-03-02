
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

#include "MMLE.hpp"


int main() {
	cout << endl;
	cout << "Running time tests ..." << endl;

	// number of run tests
	int tcount = 0;
	// number of passed tests
	int pcount = 0;
	// number of failed tests
	int fcount = 0;
	// return value of tests execution process
	int ret = 0;

	int target = 0;
	int duration = 0;
	long long t_start = 0;


	// TEST 1-2: duration

	// low precision (3 seconds)
	target = 3;

	tcount++;
	t_start = MMLE::Time::currentTimeMillis();
	for (int idx = 0; idx < 100; idx++) {
		this_thread::sleep_for(chrono::milliseconds(50));
		duration = (MMLE::Time::currentTimeMillis() - t_start) / 1000;
		if (duration >= target) {
			break;
		}
	}

	if (duration != target) {
		fcount++;
		ret = 1;
		cerr << "FAIL (test " << tcount << "): Expected " << target << "s but got " << duration
				<< "s" << endl;
	} else {
		pcount++;
	}

	// high precision (3000 milliseconds)
	target = 3000;

	tcount++;
	t_start = MMLE::Time::currentTimeMillis();
	for (int idx = 0; idx < 100; idx++) {
		this_thread::sleep_for(chrono::milliseconds(50));
		duration = MMLE::Time::currentTimeMillis() - t_start;
		if (duration >= target) {
			break;
		}
	}

	// allow for 50ms buffer
	if (duration - target > 50) {
		fcount++;
		ret = 1;
		cerr << "FAIL (test " << tcount << "): Expected " << target << "ms but got " << duration
				<< "ms" << endl;
	} else {
		pcount++;
	}


	if (ret == 0) {
		cout << "OK: all tests passed" << endl;
	} else {
		cerr << "FAILURES: " << fcount << " failed tests" << endl;
	}
	cout << pcount << " out of " << tcount << " time tests passing" << endl;

	return ret;
}
