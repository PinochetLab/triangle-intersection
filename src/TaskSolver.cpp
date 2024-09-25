#include <future>

#include "TaskSolver.h"
#include "Parser.h"

static Answer process_futures(const std::vector<Task>& tasks, std::vector<std::future<bool>>& futures) {
    Answer answer;
    for (int i = 0; i < tasks.size(); i++) {
        Task task = tasks[i];
        bool real_intersect = futures[i].get();
        if (real_intersect != task.get_expected()) {
            answer.add_failed_test(task.get_line_number(), task.get_expected());
        }
        else {
            answer.add_done_test();
        }
    }
    return answer;
}

Answer TaskSolver::solve_file(const std::string& path) {
    Parser parser(path);

    std::promise<void> promise;

    auto parse_task = [&]() {
        try {
            parser.parse(task_queue, mtx, cv);
            promise.set_value();
        }
        catch (...) {
            promise.set_exception(std::current_exception());
        }
        cv.notify_all();
    };

    std::thread parse_thread(parse_task);

    std::future<void> future = promise.get_future();

    std::vector<Task> tasks;
    std::vector<std::future<bool>> futures;

    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this, &parser] { return !task_queue.empty() || parser.is_finished(); });

        if (parser.is_finished() && task_queue.empty()) {
            break;
        }

        Task task = task_queue.front();
        task_queue.pop();
        tasks.push_back(task);

        auto calculate_task = [](Task task) {
            return task.are_triangles_intersect();
        };

        futures.emplace_back(std::async(std::launch::async, calculate_task, std::move(task)));
    }

    try {
        future.get();
    } catch(const std::exception& e) {
        parse_thread.join();
        throw std::runtime_error("Parse error: " + std::string(e.what()));
    }

    parse_thread.join();

    return process_futures(tasks, futures);
}

Answer TaskSolver::solve_vector(const std::vector<Task>& tasks) {
    std::vector<std::future<bool>> futures;
    futures.reserve(tasks.size());
    for (const auto& task : tasks) {
        auto calculate_task = [](const Task& task) {
            return task.are_triangles_intersect();
        };
        futures.emplace_back(std::async(std::launch::async, calculate_task, task));
    }
    return process_futures(tasks, futures);
}