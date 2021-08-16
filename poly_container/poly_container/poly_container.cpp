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
	storage_.clear();
	for (auto it = other.storage_.begin(); it != other.storage_.end(); it++) {
		it->get()->clone(storage_);
	}
	return *this;
}