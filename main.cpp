//////////////////////////////////////////
//	C++ STL Algorithms
//	Naughty Panda @ 2021
//////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>
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

template <typename T>
void print(const T& cnt) {

	//std::copy(std::begin(cnt), std::end(cnt), std::ostream_iterator<???>(std::cout, " "));
	for (const auto& i : cnt) {
		std::cout << i << ' ';
	}
}

int main() {

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

	return 0;
}
