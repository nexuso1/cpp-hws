#ifndef  MAIN_H
#define MAIN_H

#include <memory>
#include <string>
#include <iostream>

class AbstractVal;
class IntVal;
class StringVal;

using valptr = std::unique_ptr<AbstractVal>;

class AbstractVal {
public:
	virtual void print() = 0;
	virtual void copyFrom(AbstractVal&) = 0;

	virtual void copyTo(IntVal &target) = 0;
	virtual void copyTo(StringVal& target) = 0;
};

class IntVal : public AbstractVal {
public:
	IntVal(int val) : val_(val) {};
	void print() override {
		std::cout << val_;
	}

	void copyFrom(AbstractVal& other) override {
		other.copyTo(*this);
	}

	void copyTo(IntVal& target) override {
		target.val_ = val_;
	};
	void copyTo(StringVal& target) override;

	int val_;
};

class StringVal : public AbstractVal {
public:
	StringVal(const std::string& val) : val_(val) {};
	void print() override {
		std::cout << val_;
	}

	void copyFrom(AbstractVal& other) override {
		other.copyTo(*this);
	}

	inline void copyTo(IntVal& target) override {
		target.val_ = std::stoi(val_);
	};
	inline void copyTo(StringVal& target) override {
		target.val_ = val_;
	};

	std::string val_;
};


void IntVal::copyTo(StringVal& target) {
	target.val_ = std::to_string(val_);
}

#endif // ! MAIN_H