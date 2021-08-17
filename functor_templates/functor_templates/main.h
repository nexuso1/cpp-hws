#include <algorithm>
#include <cmath>

template<typename T>
class diff
{
public:

	// Set value difference to dif, and last_val to val
	diff(T dif, T val) : m_dif(dif), m_last_val(val) {}

	bool operator()(T val) {
		// Return true if |m_last_value - val| >= dif
		bool res = m_last_val - val >= m_dif || m_last_val - val <= -m_dif;
		m_last_val = val;
		return res;
	}

private:
	T m_dif;
    T m_last_val;

};

template<typename T>
class inc {
public:
	inc() {};
	void operator() (T& x) {
		x += i++;
	};

private:
	T i = 1;
};

template<typename T>
class gap
{
public:
    // Initialize first and second value, and set the difference to least possible
    gap(T& x, T& y) : m_first(x), m_second(y) {
        m_largest_diff = std::abs(m_first - m_second);
        m_out = m_second;
    }

    void operator()(T& val) {
        // Move the values forward
        m_first = m_second;
        m_second = val;

        // If the difference of the previous 2 values is >m_largest_diff, set output
        // to current val and update m_largest_diff
        T diff = std::abs(m_first - m_second);
        if (diff > m_largest_diff) {
            m_largest_diff = diff;
            m_out = val;
        }
    }

    T OutputResult() {
        return m_out;
    }

private:
    T m_largest_diff;
    T m_first;
    T m_second;
    T m_out;
};

template<typename It>
void process_inc(It begin, It end) {
	using value_type = typename std::iterator_traits<It>::value_type;
	std::for_each(begin, end, inc<value_type>());
}


template<typename Iter>
Iter process_diff(Iter begin, Iter end, int n) {
	using value_type = typename std::iterator_traits<Iter>::value_type;
	return std::find_if(begin, end, diff<value_type>(n, *begin));
}

template<typename Iter>
typename std::iterator_traits<Iter>::value_type process_gap(Iter begin, Iter end) {
    using value_type = typename std::iterator_traits<Iter>::value_type;
    gap<value_type> g(*begin, *(begin + 1));
    for (auto it = begin + 2; it != end; it++) {
        g(*it);
    }
    return g.OutputResult();
}