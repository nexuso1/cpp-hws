#include <iostream>
#include <memory>
#include "main.h"

using namespace std;

int main() {
	valptr a(make_unique<IntVal>(123));
	valptr b(make_unique<StringVal>("456"));
	valptr c(make_unique<IntVal>(789));

	a->copyFrom(*b);
	a->print();
	cout << endl;

	b->copyFrom(*c);
	b->print();

	return 0;
}