#include <ios>

#include "Answer.h"

std::ostream& operator << (std::ostream& cout, const Answer& c) {
    for (const auto& p : c.expecteds) {
        int line_number = p.first;
        bool expected = p.second;
        cout << "line " << line_number << ": expected " << std::boolalpha 
                << expected << ", got " << !expected << std::noboolalpha << std::endl;
    }
    int failed_count = c.expecteds.size();
    cout << "Tests done " << c.test_count << "/" << failed_count << " failed" << std::endl;

    int fail_rate_percent = 100;
    if (c.test_count > 0) {
        fail_rate_percent = 100.0 * static_cast<double>(failed_count) / c.test_count;
    }
    cout << "Fail Rate: " << fail_rate_percent << "%";

    return cout;
}