#include <iostream>
#include <thread>
#include <future>

#include "Parser.h"
#include "Answer.h"
#include "TasksSolver.h"

int main()
{
    std::string path;
    std::cin >> path;
    TasksSolver tasks_solver;
    Answer answer = tasks_solver.solve_file(path);
    std::cout << answer;
    return 0;
}