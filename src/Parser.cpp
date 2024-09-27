#include <sstream>

#include "Parser.h"

bool Parser::read_line(std::string &line)
{
    // Ship all empty and comment lines.
    do
    {
        line_number++;

        // File ended.
        if (!std::getline(file, line))
        {
            return false;
        }
    } while (line.empty() || line[0] == '#');

    return true;
}

std::optional<std::string> Parser::read_lines(int num)
{
    std::ostringstream os;
    std::string s;

    // If we cannot read any line, it is not error.
    if (!read_line(s))
    {
        return std::nullopt;
    }

    os << s;
    num--;

    for (; num; num--)
    {
        // If we started to read task and cannot read next line - it is error.
        if (!read_line(s))
        {
            throw std::domain_error("unable to read line " + std::to_string(line_number));
        }

        os << ' ' << s;
    }

    return os.str();
}

void Parser::parse(std::queue<Task> &task_queue, std::mutex &mtx, std::condition_variable &cv)
{
    std::optional<std::string> line;

    // Read all tasks.
    while ((line = read_lines(3)))
    {
        Task task(line_number);

        std::istringstream is(*line);
        // Read task from stream and catch error
        try
        {
            is >> task;
        }
        catch (...)
        {
            /*
            We need to set finished = true, to message another thread that parsing is finished.
            Lock mutex for work with finished.
            */
            std::lock_guard<std::mutex> lock(mtx);
            finished = true;
            throw;
        }
        // Lock mutex for work with task queue.
        std::lock_guard<std::mutex> lock(mtx);
        // Pushing task into queue.
        task_queue.push(task);
        // Notify worker thread.
        cv.notify_one();
    }

    // Lock mutex for work with finished.
    std::lock_guard<std::mutex> lock(mtx);
    finished = true;
}
