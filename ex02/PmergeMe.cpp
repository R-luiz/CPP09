#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <utility>

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
	this->time_vector = time_vector;
	this->time_list = time_list;
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

    std::vector<std::pair<typename T::value_type, typename T::value_type> > pairs;
    typename T::iterator it = container.begin();
    while (it != container.end()) {
        typename T::value_type first = *it++;
        if (it != container.end()) {
            typename T::value_type second = *it++;
            pairs.push_back(std::make_pair(std::min(first, second), std::max(first, second)));
        } else {
            pairs.push_back(std::make_pair(first, first));
        }
    }

    std::vector<typename T::value_type> largerElements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        largerElements.push_back(pairs[i].second);
    }
    if (largerElements.size() > 1) {
        mergeInsertSort(largerElements);
    }

    T result;
    result.push_back(pairs[0].first);
    for (size_t i = 0; i < largerElements.size(); ++i) {
        result.push_back(largerElements[i]);
    }

    std::vector<size_t> jacobsthal = generateJacobsthalSequence(pairs.size());
    for (size_t i = 1; i < jacobsthal.size() && jacobsthal[i] <= pairs.size(); ++i) {
        for (size_t j = jacobsthal[i]; j > jacobsthal[i-1]; --j) {
            if (j <= pairs.size() && j > 1) {
                typename T::value_type element = pairs[j-1].first;
                typename T::iterator insertPos = std::lower_bound(result.begin(), result.end(), element);
                result.insert(insertPos, element);
            }
        }
    }
    container = result;
}

std::vector<size_t> PmergeMe::generateJacobsthalSequence(size_t n) {
    std::vector<size_t> sequence;
    sequence.push_back(0);
    sequence.push_back(1);
    while (sequence.back() < n) {
        size_t next = sequence[sequence.size() - 1] + 2 * sequence[sequence.size() - 2];
        if (next > n) break;
        sequence.push_back(next);
    }
    return sequence;
}

bool PmergeMe::isPositiveInteger(const std::string& s) const {
    return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
}

void PmergeMe::displayResults() const {
    for (size_t i = 0; i < original.size(); ++i) {
        std::cout << original[i] << " ";
    }
    std::cout << std::endl;
}

int PmergeMe::getTimeVector() const {
	return time_vector;
}

int PmergeMe::getTimeList() const {
	return time_list;
}

int PmergeMe::getOriginalSize() const {
	return original.size();
}
