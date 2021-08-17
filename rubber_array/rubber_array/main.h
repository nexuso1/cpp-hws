#include <vector>

template<typename T>
class Pole {
public:
	Pole(size_t chunk = 100) : chunk_(chunk) {};
	void push_back(const T& x) {
		resize(size_++);
		(*this)[size_ - 1] = x;
	}
	T& operator[](size_t i) {
		return hrabe_[chunk / i][i % chunk];
	}
	T& at(size_t i) {
		check(i);
		return (*this)[i];
	};

	class iterator {
		iterator();
		iterator(const iterator& it);
		//iterator(...);
		T& operator*();
		bool operator != (const iterator& it2);
		iterator operator++();
	};
	iterator begin() {};
	iterator end() {};

private:
	void check(size_t i) {
		if (i >= size_) {
			throw out_of_range;
		}
	};
	void resize(size_t i) {};
	std::vector<std::unique_ptr<T[]>> hrabe_;
	size_t chunk_;
	size_t size_ = 0;
};
