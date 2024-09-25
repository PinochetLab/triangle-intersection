#pragma once

#include <unordered_map>
#include <iostream>

/**
 * @class Answer
 * @brief Class for report about results of tests.
 */
class Answer {
private:
	int test_count = 0; // All test count

	int failed_count = 0; // Failed test count

	std::unordered_map<int, bool> expecteds; // Map<line_number, expected> for autosorting by line_number
public:

	/**
     * @brief Method for adding done(passed) test.
     */
	void add_done_test() {
		test_count++;
	}

	/**
     * @brief Method for adding failed test.
	 * @param line_number Line number of test expected value.
	 * @param expected Test expected value.
     */
	void add_failed_test(int line_number, bool expected) {
		test_count++;
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
		cout << "Tests done " << c.test_count << "/" << c.failed_count << " failed" << std::endl;
		
		int fail_rate_percent = 100;
		if (c.test_count > 0) {
			fail_rate_percent = (int)(100.0 * (double)c.failed_count / c.test_count);
		}
		cout << "Fail Rate: " << fail_rate_percent << "%";

		return cout;
	}
};
