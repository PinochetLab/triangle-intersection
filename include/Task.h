#pragma once

#include <stdexcept>
#include <iostream>
#include <ios>

#include "Triangle.h"

class Task {
	Triangle t1, t2;
	bool expected = false;
	int line_number = 0;
public:
	Task(int line_number) : line_number(line_number) {}

	Task() = default;

	bool are_triangles_intersect() const {
		return t1.intersects(t2);
	}

	bool get_expected() const {
		return expected;
	}

	int get_line_number() const {
		return line_number;
	}

	friend std::istream& operator >> (std::istream& cin, Task& t) {
		if (!(cin >> t.t1)) {
			throw std::domain_error("incorrect Triangle1 in task on line " + std::to_string(t.line_number));
		}
		if (!(cin >> t.t2)) {
			throw std::domain_error("incorrect Triangle2 in task on line " + std::to_string(t.line_number));
		}
		if (!(cin >> std::boolalpha >> t.expected >> std::noboolalpha)) {
			throw std::domain_error("incorrect bool expected value in line " + std::to_string(t.line_number));
		}
		return cin;
	}

	friend std::ostream& operator << (std::ostream& cout, const Task& t) {
		cout << "Task " << t.expected << std::endl;
		cout << "  " << t.t1 << std::endl;
		cout << "  " << t.t2;
		return cout;
	}
};
