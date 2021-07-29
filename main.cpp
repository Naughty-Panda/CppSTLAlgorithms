//////////////////////////////////////////
//	C++ STL Algorithms
//	Naughty Panda @ 2021
//////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>

//////////////////////////////////////////
//	4.1
//////////////////////////////////////////

template <typename T>
void insert_sorted(std::vector<T>& vec, const T& val) {

	// val <= first element
	if (*std::begin(vec) >= val) {
		vec.insert(std::begin(vec), val);
		return;
	}

	// val >= last element
	if (*(std::end(vec) - 1) <= val) {
		vec.push_back(val);
		return;
	}

	// val is in the container range
	// why do we need "typename"???
	typename std::vector<T>::const_iterator it = std::find_if((std::begin(vec) + 1), (std::end(vec) - 1), [&val](const T& i) { return val <= i; });
	vec.insert(it, val);
}

// Using STL algorithm "lower_bound"
template <typename C, typename V>
void insert_sorted_v2(C& container, const V& value) {

	// why do we need "typename"???
	typename C::iterator it = std::lower_bound(std::begin(container), std::end(container), value);
	*std::inserter(container, it) = value;
}

//////////////////////////////////////////
//	4.2
//////////////////////////////////////////

float CalculateError(const std::vector<float>& cnt1, const std::vector<int>& cnt2) {

	auto error_func = [](const auto& i1, const auto& i2) -> float { float i = i1 - i2; return i * i; };
	return std::inner_product(std::begin(cnt1), std::end(cnt1), std::begin(cnt2), 0.0f, std::plus<>(), error_func) / static_cast<float>(cnt1.size());
}

template <typename T>
void print(const T& cnt) {

	//std::copy(std::begin(cnt), std::end(cnt), std::ostream_iterator<???>(std::cout, " "));
	for (const auto& i : cnt) {
		std::cout << i << ' ';
	}
}

int main() {

	//////////////////////////////////////////
	//	4.1
	//////////////////////////////////////////

	// Default std::vector
	std::vector<int> vec{ 1,2,3,4,5,6,7,8,9 };
	print(vec);

	// Using first function
	std::cout << "\n\nFirst function with std::vector:\n";
	insert_sorted(vec, 0);
	print(vec);

	std::cout << '\n';
	insert_sorted(vec, 6);
	print(vec);

	std::cout << '\n';
	insert_sorted(vec, 12);
	print(vec);

	// Using second function
	std::cout << "\n\nSecond function with std::vector:\n";
	insert_sorted_v2(vec, 3);
	print(vec);

	std::cout << '\n';
	insert_sorted_v2(vec, 15);
	print(vec);

	std::cout << '\n';
	insert_sorted_v2(vec, -3);
	print(vec);

	// Default std::list
	std::cout << "\n\nSecond function with std::list:\n";
	std::list<float> l{ .3f, .5f, .67f, .78f, .947f };
	print(l);

	// Using second function with std::list<float>
	insert_sorted_v2(l, .56f);
	std::cout << '\n';
	print(l);

	insert_sorted_v2(l, 1.02f);
	std::cout << '\n';
	print(l);

	//////////////////////////////////////////
	//	4.2
	//////////////////////////////////////////

	float angle = 0.0f;
	std::vector<float> analog(100);
	std::vector<int> digital(100);

	// Generating values for analog signal
	std::generate(std::begin(analog), std::end(analog), [&angle]() { angle += 3.6f; return std::sinf(angle) * 360; });
	// Transforming analog values into digital signal
	std::transform(std::begin(analog), std::end(analog), std::begin(digital), [](const auto& i) { return static_cast<int>(std::roundf(i)); });

	std::cout << "\n\nAnalog signal:\n";
	print(analog);
	std::cout << "\n\nDigital signal:\n";
	print(digital);

	// Calculating error
	std::cout << "\n\nError between analog and digital: " << CalculateError(analog, digital);

	return 0;
}
