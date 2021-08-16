#include <iostream>
#include <vector>
#include <string>
#include "main.h"

using namespace std;

void Seznam::add(unique_ptr<AbstractVal> p) {
	storage_.push_back(move(p));
}

void Seznam::print() {
	for (auto it = storage_.begin(); it != storage_.end(); it++) {
		it->get()->print();
		cout << endl;
	}
}

Seznam& Seznam::operator=(Seznam other) {
	vector <unique_ptr<AbstractVal>>temp;
	for (auto it = storage_.begin(); it != storage_.end(); it++) {
		temp.push_back(make_unique<AbstractVal>(it->get()));
	}
	return *this;
}