#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include "main.h"

using namespace std;

template<typename T>
void process(const string& line) {
	// Load numbers
	stringstream lineStream(line);
	vector<T> vec;
	T num;
	while (lineStream >> num) {
		vec.push_back(num);
	}

	// Diff
	auto fnd = process_diff(vec.begin(), vec.end(), 4);
	if (fnd != vec.end()) {
		cout << *fnd;
	}
	cout << endl;

	// Gap
	cout << process_gap(vec.begin(), vec.end()) << endl;

	// Inc
	process_inc(vec.begin(), vec.end());
	for (auto x : vec)
		cout << x << ' ';
	cout << endl;
}



int main()
{
	// Load line
	string intLine;
	string doubleLine;
	getline(cin, intLine);
	getline(cin, doubleLine);

	process<int>(intLine);
	process<double>(doubleLine);

	return 0;
}