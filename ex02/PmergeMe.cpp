#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

PmergeMe::PmergeMe() {}

void PmergeMe::parseInput(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (!isPositiveInteger(argv[i])) {
            throw std::runtime_error("Invalid input: " + std::string(argv[i]));
        }
        int num = std::atoi(argv[i]);
        vec.push_back(num);
        lst.push_back(num);
    }
    original = vec;
}

void PmergeMe::sort() {
    clock_t start, end;
    
    start = clock();
    sortVector();
    end = clock();
    double time_vector = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

    start = clock();
    sortList();
    end = clock();
    double time_list = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << time_vector << " us" << std::endl;
    std::cout << "Time to process a range of " << lst.size() << " elements with std::list : " << time_list << " us" << std::endl;
}

void PmergeMe::sortVector() {
    mergeInsertSort(vec);
}

void PmergeMe::sortList() {
    mergeInsertSort(lst);
}

template <typename T>
void PmergeMe::mergeInsertSort(T& container) {
    if (container.size() <= 1) return;

    typename T::iterator mid = container.begin();
    std::advance(mid, container.size() / 2);

    T left(container.begin(), mid);
    T right(mid, container.end());

    mergeInsertSort(left);
    mergeInsertSort(right);

    container.clear();
    std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(container));
}

bool PmergeMe::isPositiveInteger(const std::string& s) const {
    return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
}

void PmergeMe::displayResults() const {
    std::cout << "Before: ";
    for (size_t i = 0; i < original.size(); ++i) {
        std::cout << original[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "After: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}