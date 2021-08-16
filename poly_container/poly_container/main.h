#include<iostream>
#include<string>
#include<memory>
#include<vector>

class AbstractVal {
public:
	virtual void print() {};
	virtual ~AbstractVal() {};
	virtual AbstractVal* clone() const = NULL; // Note to self: =0(NULL) signifies a purely virtual function;
};

class IntVal : public AbstractVal {
public:
	IntVal(int val) : val_(val) {};
	IntVal* clone() const {
		return new IntVal(val_);
	}
	inline void print() override {
		std::cout << val_;
	};
	int val_;
};

class DoubleVal : public AbstractVal {
public:
	DoubleVal(double val) : val_(val) {};
	DoubleVal* clone() const {
		return new DoubleVal(val_);
	}
	inline void print() override {
		std::cout << val_;
	};
	double val_;
};


class StringVal : public AbstractVal {
public:
	StringVal(std::string val) : val_(val) {};
	StringVal* clone() const {
		return new StringVal(val_);
	}
	inline void print() override {
		std::cout << val_;
	};
	std::string val_;
};

class ComplexVal : public AbstractVal {
public:
	ComplexVal(int real, int img) : real_(real), img_(img) {};
	ComplexVal* clone() const {
		return new ComplexVal(real_, img_);
	}
	inline void print() override {
		std::cout << real_ << '+' << img_;
	};
	int real_, img_;
};

class FractionVal : public AbstractVal {
public:
	FractionVal(int num, int denom) : num_(num), denom_(denom) {};
	FractionVal* clone() const {
		return new FractionVal(num_, denom_);
	}
	inline void print() override {
		std::cout << num_ << '/' << denom_;
	};
	int num_, denom_;
};

class Seznam {
public:
	Seznam() {};
	Seznam(Seznam& other) {
		swap(storage_, other.storage_);
	};
	void add(std::unique_ptr<AbstractVal> p);
	void print();
	Seznam& operator=(Seznam s);

private:
	std::vector<std::unique_ptr<AbstractVal>> storage_;
};
