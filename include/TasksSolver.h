#pragma once

#include <future>

#include "Parser.h"
#include "Answer.h"

class TasksSolver {
private:
    std::queue<Task> task_queue;
    std::mutex mtx;
    std::condition_variable cv;

    Answer process_futures(const std::vector<Task>& tasks, std::vector<std::future<bool>>& futures) {
        Answer answer;
        for (int i = 0; i < tasks.size(); i++) {
            Task task = tasks[i];
            bool real_intersect = futures[i].get();
            if (real_intersect != task.get_expected_intersect()) {
                answer.add_failed_test(task.get_line_number(), task.get_expected_intersect());
            }
            else {
                answer.add_done_test();
            }
        }
        return answer;
    }
public:
	Answer solve_file(const std::string& path) {
        Parser parser(path);
        auto parse_task = [&]() {
            try {
                parser.parse(task_queue, mtx, cv);
            }
            catch (const std::exception& e) {
                std::cerr << "Error parsing: " << e.what() << std::endl;
            }
            };
        std::thread parse_thread(parse_task);

        std::vector<Task> tasks;
        std::vector<std::future<bool>> futures;

        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this, &parser] { return !task_queue.empty() || parser.is_finished(); });

            if (parser.is_finished() && task_queue.empty()) {
                break;
            }

            if (!task_queue.empty()) {
                Task task = task_queue.front();
                task_queue.pop();
                tasks.push_back(task);

                auto calculate_task = [](Task task) {
                    return task.calculate_real_intersect();
                    };

                futures.emplace_back(std::async(std::launch::async, calculate_task, task));
            }
        }
        parse_thread.join();
        return process_futures(tasks, futures);
	}

    Answer solve_vector(const std::vector<Task>& tasks) {
        std::vector<std::future<bool>> futures;
        futures.reserve(tasks.size());
        for (const auto& task : tasks) {
            auto calculate_task = [](Task task) {
                return task.calculate_real_intersect();
                };
            futures.emplace_back(std::async(std::launch::async, calculate_task, task));
        }
        return process_futures(tasks, futures);
    }
};