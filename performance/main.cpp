#include "main.h"

#include <functional>


struct PerformanceTest {
    std::string name;
    std::function<void()> test_function;
};


std::vector<PerformanceTest> performance_tests = {
    {"Perft", run_perft},
    {"Alpha-Beta", run_alpha_beta},
};


int main() {
    int test_n;
    std::cout << "Select a test to run:" << std::endl;
    for (int i = 0; i < performance_tests.size(); i++) {
        std::cout << i + 1 << ". " << performance_tests[i].name << std::endl;
    }
    std::cin >> test_n;
    performance_tests[test_n - 1].test_function();

}