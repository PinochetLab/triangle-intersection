#pragma once

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

#include "Answer.h"
#include "Task.h"

/**
 * @class TaskSolver.
 * @brief Class for manipulating and solving tasks.
 */
class TaskSolver {
    /**
     * @brief Task queue.
     */
    std::queue<Task> task_queue;

    /**
     * @brief Mutex for resources.
     */
    std::mutex mtx;

    /**
     * @brief Conditional variable for resources.
     */
    std::condition_variable cv;
public:
    /**
	 * @brief Method for solve tasks for file.
	 * @param path File path.
	 * @return Answer on tasks.
	 */
	Answer solve_file(const std::string& path);

    /**
	 * @brief Method for solve tasks from vector without parsing.
	 * @param tasks Vector with tasks.
	 * @return Answer on tasks.
	 */
    Answer solve_vector(const std::vector<Task>& tasks);
};