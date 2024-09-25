#include <sstream>

#include "Parser.h"

bool Parser::read_line(std::string & line) {
    do {
        line_number++;

        if (!std::getline(file, line)) {
	    	return false;
        }
    } while (line.empty() || line[0] == '#');

    return true;
}

std::optional<std::string> Parser::read_lines(int num) {
    std::ostringstream os;
    std::string s;

    if (!read_line(s)) {
        return std::nullopt;
    }

    os << s;
    num--;

    for (; num; num--) {
        if (!read_line(s)) {
			throw std::domain_error("unable to read line " + std::to_string(line_number));
        }

        os << ' ' << s;
    }

    return os.str();
}

void Parser::parse(std::queue<Task>& task_queue, std::mutex& mtx, std::condition_variable& cv) {
	std::optional<std::string> line;

	while ((line = read_lines(3))) {
		Task task(line_number);

		std::istringstream is(*line);
		try {
			is >> task;
		} catch (...) {
		    std::lock_guard<std::mutex> lock(mtx);
			finished = true;
			throw;
		}

		std::lock_guard<std::mutex> lock(mtx);
		task_queue.push(task);
		cv.notify_one();
	}

	std::lock_guard<std::mutex> lock(mtx);
	finished = true;
}
