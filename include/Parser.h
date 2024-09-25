#pragma once

#include <fstream>
#include <queue>
#include <string>
#include <sstream>
#include <mutex>

#include "Task.h"

class Parser
{
private:
	std::ifstream file;
	bool finished = false;
public:
	Parser(const std::string& filename) {
		file.open(filename);
		if (!file.is_open()) {
			throw std::runtime_error("Unable to open file: " + filename);
		}
	}

	~Parser() {
		if (file.is_open()) {
			file.close();
		}
	}

	bool is_finished() const {
		return finished;
	}

	void parse(std::queue<Task>& task_queue, std::mutex& mtx, std::condition_variable& cv);
};

