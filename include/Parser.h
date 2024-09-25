#pragma once

#include <condition_variable>
#include <stdexcept>
#include <optional>
#include <fstream>
#include <queue>
#include <string>
#include <mutex>

#include "Task.h"

class Parser {
	std::ifstream file;

    int line_number = 0;

	bool finished = false;

    bool read_line(std::string & s);

    std::optional<std::string> read_lines(int num);
public:
	Parser(const std::string& filename) {
		file.open(filename);

		if (!file.is_open()) {
			throw std::runtime_error("Unable to open file: " + filename);
		}
	}

	bool is_finished() const {
		return finished;
	}

	void parse(std::queue<Task>& task_queue, std::mutex& mtx, std::condition_variable& cv);
};

