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
		std::cout << "Original: ";
        sorter.displayResults();  // Display before sorting
        sorter.sort();
		std::cout << "Sorted: ";
        sorter.displayResults();  // Display after sorting
		std::cout << "Time to process a range of " << sorter.getOriginalSize() << " elements with std::vector : " << sorter.getTimeVector() << " us" << std::endl;
		std::cout << "Time to process a range of " << sorter.getOriginalSize() << " elements with std::list : " << sorter.getTimeList() << " us" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}