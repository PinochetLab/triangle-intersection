#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <filesystem>
#include <stdexcept>

#include "TaskSolver.h"
#include "Answer.h"

/**
 * @brief Function to read file content as string.
 * @param path File path.
 * @return File content as string.
 */
static std::string readFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file: " + path);
    }

    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}

/**
 * @brief Function to compare expected and real output.
 * @param input_path Path of input file.
 * @param output_path Path of expected output file.
 * @throw Logic error if comparison is failed.
 */
void test_input_output(const std::string &input_path, const std::string &output_path)
{
    TaskSolver solver;
    Answer answer = solver.solve_file(input_path);

    std::string expected_output = readFile(output_path);

    std::ostringstream ss;
    ss << answer;
    std::string real_output = ss.str();

    if (expected_output != real_output)
    {
        std::ostringstream os;
        os << "assertion error(\n"
           << expected_output << "\n != \n"
           << real_output << ")";
        throw std::logic_error(os.str());
    }
}

/**
 * @brief Funtion to check all tests in test directory..
 * @return True if all tests passed.
 */
bool check_all_tests()
{
    const std::string path = "../test_data/";
    const std::string input_path = path + "input/";
    const std::string output_path = path + "output/";

    bool failure = false;

    try
    {
        for (const auto &entry : std::filesystem::directory_iterator(input_path))
        {
            if (std::filesystem::is_regular_file(entry))
            {
                std::string file_name = entry.path().filename().string();
                try
                {
                    // Files are named the same.
                    test_input_output(input_path + file_name, output_path + file_name);
                }
                catch (const std::exception &e)
                {
                    // Print file for simplifying debugging.
                    std::cerr << "error in " << file_name << ": " << e.what() << std::endl;
                    failure = true;
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Unable to access dirtectory: " << e.what() << std::endl;
        failure = true;
    }
    return !failure;
}

int main()
{
    if (!check_all_tests())
    {
        std::exit(EXIT_FAILURE);
    }
    return 0;
}