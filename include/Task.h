#pragma once

#include "Triangle.h"

class Task {
private:
	Triangle t1, t2;
	bool expected_intersect;
	int line_number;
public:
	Task(int line_number) : t1(), t2(), expected_intersect(), line_number(line_number) {}

	Task() : t1(), t2(), expected_intersect(), line_number() {}

	bool are_triangles_intersect() const {
		return t1.intersects(t2);
	}

	bool get_expected() const {
		return expected_intersect;
	}

	int get_line_number() const {
		return line_number;
	}

	friend std::istream& operator >> (std::istream& cin, Task& t)
	{
		std::string expected_str;
		if (!(cin >> t.t1)) {
			throw std::runtime_error("incorrect Triangle1 in line " + std::to_string(t.line_number));
		}
		if (!(cin >> t.t2)) {
			throw std::runtime_error("incorrect Triangle2 in line " + std::to_string(t.line_number + 1));
		}
		cin >> expected_str;
		if (expected_str == "true") {
			t.expected_intersect = true;
		}
		else if (expected_str == "false") {
			t.expected_intersect = false;
		}
		else {
			std::cout << t.t1 << std::endl << t.t2 << std::endl;
			throw std::domain_error("incorrect bool value: " + expected_str);
		}
		return cin;
	}

	friend std::ostream& operator << (std::ostream& cout, const Task& t)
	{
		cout << "Task " << t.expected_intersect << std::endl;
		cout << "  " << t.t1 << std::endl;
		cout << "  " << t.t2;
		return cout;
	}
};
