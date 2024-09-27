#include <future>

#include "TaskSolver.h"
#include "Parser.h"

/**
 * @brief Function to get Answer from tasks and futures.
 * @param tasks Vector of tasks.
 * @param futures Vector of futures (with calculating intersection answers).
 * @return Answer on tasks.
 */
static Answer process_futures(const std::vector<Task> &tasks, std::vector<std::future<bool>> &futures)
{
    Answer answer;
    for (int i = 0; i < tasks.size(); i++)
    {
        Task task = tasks[i];
        bool real_intersect = futures[i].get();
        // If intersection does not match expected, add failed test to answer
        if (real_intersect != task.get_expected())
        {
            answer.add_failed_test(task.get_line_number(), task.get_expected());
        }
        else
        {
            // Else add done test.
            answer.add_done_test();
        }
    }
    return answer;
}

Answer TaskSolver::solve_file(const std::string &path)
{
    // Create a parser.
    Parser parser(path);

    // Promise for catch another thread error, parsing will run in another thread.
    std::promise<void> parse_promise;

    // Task for thread
    auto parse_task = [&]()
    {
        // Try parse and catch error.
        try
        {
            // Parse.
            parser.parse(task_queue, mtx, cv);
            // Everything is good.
            parse_promise.set_value();
        }
        catch (...)
        {
            // Save exception.
            parse_promise.set_exception(std::current_exception());
        }
        // Notify worker thread - parsing is finished.
        cv.notify_all();
    };

    // Create thread for parsing.
    std::thread parse_thread(parse_task);

    // Get future.
    std::future<void> parse_future = parse_promise.get_future();

    // Create tasks vector for pushing tasks from queue.
    std::vector<Task> tasks;
    // Create futures vector for counting tasks jobs.
    std::vector<std::future<bool>> futures;

    while (true)
    {
        // Lock mutex for work with finished and task queue.
        std::unique_lock<std::mutex> lock(mtx);
        // Wait for new task or parsing finishing.
        cv.wait(lock, [this, &parser]
                { return !task_queue.empty() || parser.is_finished(); });

        // If parsing is finished and task queue empty, all tasks are read, break.
        if (parser.is_finished() && task_queue.empty())
        {
            break;
        }

        // Get and pop task.
        Task task = task_queue.front();
        task_queue.pop();

        // Unlock lock for speeding up, next resources belong to current thread.
        lock.unlock();

        // Add task to tasks.
        tasks.push_back(task);

        // Task is to calculate is triangles intersect.
        auto calculate_task = [](Task task)
        {
            return task.are_triangles_intersecting();
        };

        // Add task future to futures.
        futures.emplace_back(std::async(std::launch::async, calculate_task, std::move(task)));
    }

    // Try get parse future and catch error.
    try
    {
        parse_future.get();
    }
    catch (const std::exception &e)
    {
        // Do not forget to hon parse thread.
        parse_thread.join();

        // Throw parse error.
        throw std::runtime_error("Parse error: " + std::string(e.what()));
    }

    // Join parse thread.
    parse_thread.join();

    return process_futures(tasks, futures);
}

Answer TaskSolver::solve_vector(const std::vector<Task> &tasks)
{
    // Create futures vector for tasks jobs.
    std::vector<std::future<bool>> futures;
    // We know tasks count, so can reserve place.
    futures.reserve(tasks.size());

    for (const auto &task : tasks)
    {
        // Task is to calculate if triangles intersect.
        auto calculate_task = [](const Task &task)
        {
            return task.are_triangles_intersecting();
        };
        // Add task future to futures.
        futures.emplace_back(std::async(std::launch::async, calculate_task, task));
    }
    return process_futures(tasks, futures);
}