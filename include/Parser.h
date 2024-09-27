#pragma once

#include <condition_variable>
#include <stdexcept>
#include <optional>
#include <fstream>
#include <queue>
#include <string>
#include <mutex>

#include "Task.h"

/**
 * @class Parser.
 * @brief Class for parsing file and adding tasks to queue.
 */
class Parser
{
	/**
	 * @brief file with tasks.
	 */
	std::ifstream file;

	/**
	 * @brief Current line number.
	 */
	int line_number = 0;

	/**
	 * This flag shows that parsing ended, so another thread would be able to stop looking for next task.
	 */
	bool finished = false;

	/**
	 * @brief Method for read line skipping empty and comment lines.
	 * @param s Ref for readed string value.
	 * @return True if could to read (file is not ended).
	 */
	bool read_line(std::string &s);

	/**
	 * @brief Method for read n lines ignoring empty and comment lines.
	 * @return Optional string if could read.
	 */
	std::optional<std::string> read_lines(int num);

public:
	/**
	 * @brief Class constructor.
	 * @param path File with tasks path.
	 */
	Parser(const std::string &path)
	{
		file.open(path);

		if (!file.is_open())
		{
			throw std::runtime_error("Unable to open file: " + path);
		}
	}

	/**
	 * @brief Method for check if parsing is finished for another thread.
	 * @return True if parsing is finished.
	 */
	bool is_finished() const
	{
		return finished;
	}

	/**
	 * @brief Method for parsing and pushing tasks.
	 * @param task_queue Task queue.
	 * @param mtx Mutex for resources.
	 * @param cv Conditional variable for resources.
	 * @throw Parse errors.
	 */
	void parse(std::queue<Task> &task_queue, std::mutex &mtx, std::condition_variable &cv);
};
