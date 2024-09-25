#include <iostream>
#include <thread>
#include <future>

#include "Parser.h"
#include "Answer.h"
#include "TaskSolver.h"

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        std::cerr << "path is not passed" << std::endl;
        return 1;
    }
    std::string path(argv[1]);
    TaskSolver task_solver;
    try {
        Answer answer = task_solver.solve_file(path);
        std::cout << answer << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}