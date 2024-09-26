#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <filesystem>
#include <stdexcept>

#include "TaskSolver.h"
#include "Answer.h"

static std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + path);
    }

    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}

void test_input_output(const std::string& input_path, const std::string& output_path) {
    TaskSolver solver;
    Answer answer = solver.solve_file(input_path);

    std::string expectedOutput = readFile(output_path);

    std::ostringstream ss;
    ss << answer;
    std::string realOutput = ss.str();

    if (expectedOutput != realOutput) {
        std::ostringstream os;
        os << "assertion error(\n" << expectedOutput << "\n != \n" << realOutput << ")";
        throw std::invalid_argument(os.str());
    }
}

bool check_all_tests() {
    const std::string path = "../test_data/";
    const std::string input_path = path + "input/";
    const std::string output_path = path + "output/";

    bool failure = false;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(input_path)) {
            if (std::filesystem::is_regular_file(entry)) {
                std::string file_name = entry.path().filename().string();
                try {
                    test_input_output(input_path + file_name, output_path + file_name);
                } catch (const std::exception& e) {
                    std::cerr << "error in " << file_name << ": " << e.what() << std::endl;
                    failure = true;
                }
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Unable to access dirtectory: " << e.what() << std::endl;
        failure = true;
    }
    return !failure;
}

int main() {
    if (!check_all_tests()) {
        std::exit(EXIT_FAILURE);
    }
    return 0;
}