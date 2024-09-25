#pragma once

#include <unordered_map>
#include <ostream>

/**
 * @class Answer
 * @brief Class for report about results of tests.
 */
class Answer {
	int test_count = 0; // All test count

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
		expecteds[line_number] = expected;
	}

	friend std::ostream& operator << (std::ostream& cout, const Answer& c);
};
