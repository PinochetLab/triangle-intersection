#pragma once

#include <stdexcept>
#include <iostream>
#include <ios>

#include "Triangle.h"

/**
 * @class Task.
 * @brief Class for task (test) about 2 triangles intersection.
 */
class Task
{
	/**
	 * @brief First triangle.
	 */
	Triangle t1;

	/**
	 * @brief Second triangle.
	 */
	Triangle t2;

	/**
	 * @brief Expected bool value of intersection.
	 */
	bool expected = false;

	/**
	 * @brief Line number of task (number of task expected value).
	 */
	int line_number = 0;

public:
	/**
	 * @brief Class constructor.
	 * @param line_number Line number of expected value.
	 */
	Task(int line_number) : line_number(line_number) {}

	/**
	 * @brief Default constructor.
	 */
	Task() = default;

	/**
     * @brief Method for calculate if triangles intersect.
	 * @param p Point.
	 * @return True if triangles intersect.
     */
	bool are_triangles_intersecting() const
	{
		return t1.intersects(t2);
	}

	/**
     * @brief Expected getter.
     */
	bool get_expected() const
	{
		return expected;
	}

	/**
     * @brief Line number getter.
     */
	int get_line_number() const
	{
		return line_number;
	}

	/**
     * @brief Task input for reading from file.
     */
	friend std::istream &operator>>(std::istream &cin, Task &t)
	{
		// Check cin state to throw error.
		if (!(cin >> t.t1))
		{
			throw std::domain_error("incorrect Triangle1 in task on line " + std::to_string(t.line_number));
		}
		if (!(cin >> t.t2))
		{
			throw std::domain_error("incorrect Triangle2 in task on line " + std::to_string(t.line_number));
		}
		if (!(cin >> std::boolalpha >> t.expected >> std::noboolalpha))
		{
			throw std::domain_error("incorrect bool expected value in line " + std::to_string(t.line_number));
		}
		return cin;
	}

	/**
     * @brief Task output for debugging.
     */
	friend std::ostream &operator<<(std::ostream &cout, const Task &t)
	{
		cout << "Task " << t.expected << std::endl;
		cout << "  " << t.t1 << std::endl;
		cout << "  " << t.t2;
		return cout;
	}
};
