#include<iostream>
#include<string>
#include<memory>
#include<vector>

class AbstractVal {
public:
	virtual void print() {};
	virtual ~AbstractVal() {};
	virtual void clone(std::vector<std::unique_ptr<AbstractVal>>& vec) const = 0; // Note to self: =0(NULL) signifies a purely virtual function;
};

class IntVal : public AbstractVal {
public:
	IntVal(int val) : val_(val) {};
	void clone(std::vector<std::unique_ptr<AbstractVal>>& vec) const {
		IntVal temp (val_);
		vec.push_back(std::make_unique<IntVal>(temp));
	}
	inline void print() override {
		std::cout << val_;
	};
	int val_;
};

class DoubleVal : public AbstractVal {
public:
	DoubleVal(double val) : val_(val) {};
	void clone(std::vector<std::unique_ptr<AbstractVal>>& vec) const {
		DoubleVal temp(val_);
		vec.push_back(std::make_unique<DoubleVal>(temp));
	}
	inline void print() override {
		std::cout << val_;
	};
	double val_;
};


class StringVal : public AbstractVal {
public:
	StringVal(std::string val) : val_(val) {};
	void clone(std::vector<std::unique_ptr<AbstractVal>>& vec) const {
		StringVal temp(val_);
		vec.push_back(std::make_unique<StringVal>(temp));
	}
	inline void print() override {
		std::cout << val_;
	};
	std::string val_;
};

class ComplexVal : public AbstractVal {
public:
	ComplexVal(int real, int img) : real_(real), img_(img) {};
	void clone(std::vector<std::unique_ptr<AbstractVal>>& vec) const {
		ComplexVal temp(real_, img_);
		vec.push_back(std::make_unique<ComplexVal>(temp));
	}
	inline void print() override {
		std::cout << real_ << '+' << img_ << 'i';
	};
	int real_, img_;
};

class FractionVal : public AbstractVal {
public:
	FractionVal(int num, int denom) : num_(num), denom_(denom) {};
	void clone(std::vector<std::unique_ptr<AbstractVal>>& vec) const {
		FractionVal temp(num_, denom_);
		vec.push_back(std::make_unique<FractionVal>(temp));
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
		storage_.clear();
		for (auto it = other.storage_.begin(); it != other.storage_.end(); it++) {
			it->get()->clone(storage_);
		}
	};
	void add(std::unique_ptr<AbstractVal> p);
	void print();
	Seznam& operator=(Seznam s);

private:
	std::vector<std::unique_ptr<AbstractVal>> storage_;
};
