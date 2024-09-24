#pragma once

#include <unordered_map>
#include <iostream>

class Answer {
private:
	int done_count = 0;
	int failed_count = 0;
	std::unordered_map<int, bool> expecteds;
public:
	void add_done_test() {
		done_count++;
	}
	void add_failed_test(int line_number, bool expected) {
		failed_count++;
		expecteds[line_number] = expected;
	}
	friend std::ostream& operator << (std::ostream& cout, Answer& c)
	{
		for (const auto& p : c.expecteds) {
			int line_number = p.first;
			bool expected = p.second;
			std::string expected_str = expected ? "true" : "false";
			std::string got_str = !expected ? "true" : "false";
			cout << "line " << line_number << ": expected " << expected_str << ", got " << got_str << std::endl;
		}
		cout << "Tests done " << (c.done_count + c.failed_count) << "/" << c.failed_count << " failed";
		return cout;
	}
};
