#include <vector>
#include <memory>
#include <exception>

template<typename T>
class Pole {
public:
	Pole(size_t chunk = 100) : chunk_(chunk) {};
	void push_back(const T& x) {
		resize(size_++);
		(*this)[size_ - 1] = x;
	}
	T& operator[](size_t i) {
		return hrabe_[i/chunk_][i % chunk_];
	}

	T& at(size_t i) {
		check(i);
		return (*this)[i];
	};

	class iterator {
	public:
		iterator() { pole_(nullptr); };
		iterator(const iterator& it) {
			pole_ = it.pole_;
			end_ = it.end_;
			pos_ = it.pos_;
		};

		iterator(Pole* pole, int pos, bool end) : pole_(pole), pos_(pos), end_(end) {};

		T& operator*() const {
			return pole_->at(pos_);
		};

		// Compares iterators. All end iterators are the same, and
		// different from every other iterator, otherwise checks if they
		// point to the same element.
		bool operator!=(const iterator& it2) {
			if (it2.end_) {
				return (end_) ? false : true;
			}

			if (end_) {
				return true;
			}

			return **this != *it2;
		};

		// Increments if it's not an end iterator, checks if it's out of range, and 
		// turns it into an end iterator as needed.
		iterator operator++() {
			if (!end_) {
				try {
					pole_->check(pos_ + 1);
					pos_++;
				}

				catch (std::out_of_range& e) {
					end_ = true;
				}
			}

			return *this;
		};
	private:
		Pole* pole_;
		size_t pos_;
		bool end_;
	};

	// If it contains an element, return an iterator to the first,
	// otherwise return end iterator
	iterator begin() {
		if (size_ > 0) {
			return iterator(this, 0, false);
		}

		return end();
	};

	// Return end iterator
	iterator end() {
		return iterator(this, size_, true);
	};

private:
	void check(size_t i) {
		if (i >= size_) {
			throw std::out_of_range("");
		}
	};
	void resize(size_t i) {
		for (size_t k = hrabe_.size(); k <= i; k++) {
			hrabe_.push_back(std::make_unique<T[]>(chunk_));
		}
	};
	std::vector<std::unique_ptr<T[]>> hrabe_;
	size_t chunk_;
	size_t size_ = 0;
};
