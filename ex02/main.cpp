#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <positive integers>" << std::endl;
        return 1;
    }

    try {
        PmergeMe sorter;
        sorter.parseInput(argc, argv);
        sorter.displayResults();  // Display before sorting
        sorter.sort();
        sorter.displayResults();  // Display after sorting
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}