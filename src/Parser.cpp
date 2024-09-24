#include "Parser.h"

void Parser::parse(std::queue<Task>& task_queue, std::mutex& mtx, std::condition_variable& cv) {
	std::string line;
	int line_number = 0;
	while (std::getline(file, line)) {
		line_number++;
		if (line.empty() || line[0] == '#') {
			continue;
		}
		else {
			std::string s2, s3;
			std::getline(file, s2);
			std::getline(file, s3);
			Task task(line_number + 2);
			line_number += 3;
			std::istringstream ss(line + ' ' + s2 + ' ' + s3);
			ss >> task;
			{
				std::lock_guard<std::mutex> lock(mtx);
				task_queue.push(task);
			}
			cv.notify_one();
		}
	}
	finished = true;
}
