#pragma once

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

#include "Answer.h"
#include "Task.h"

class TaskSolver {
    std::queue<Task> task_queue;
    std::mutex mtx;
    std::condition_variable cv;
public:
	Answer solve_file(const std::string& path);
    Answer solve_vector(const std::vector<Task>& tasks);
};