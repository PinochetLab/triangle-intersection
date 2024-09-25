#include <iostream>
#include <thread>
#include <future>

#include "Parser.h"
#include "Answer.h"
#include "TasksSolver.h"

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        std::cerr << "path is not passed" << std::endl;
        return 0;
    }
    std::string path(argv[1]);
    TasksSolver tasks_solver;
    try {
        Answer answer = tasks_solver.solve_file(path);
        std::cout << answer;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}