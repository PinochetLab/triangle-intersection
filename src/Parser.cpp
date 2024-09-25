#include "Parser.h"

void Parser::parse(std::queue<Task>& task_queue, std::mutex& mtx, std::condition_variable& cv) {
	std::string line;
	int line_number = 1;
	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '#') {
			line_number++;
			continue;
		}
		else {
			std::string s2, s3;
			if (!std::getline(file, s2) || !std::getline(file, s3)) {
				finished = true;
				throw std::runtime_error("incorrect task on line " + std::to_string(line_number));
			}
			Task task(line_number + 2);
			line_number += 3;
			std::istringstream ss(line + ' ' + s2 + ' ' + s3);
			try {
				ss >> task;
			} catch (...) {
				finished = true;
				throw;
			}
			{
				std::lock_guard<std::mutex> lock(mtx);
				task_queue.push(task);
			}
			cv.notify_one();
		}
	}
	finished = true;
}
