#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <string>

class PmergeMe {
private:
    std::vector<int> vec;
    std::list<int> lst;
    std::vector<int> original;

public:
    PmergeMe();
    void parseInput(int argc, char* argv[]);
    void sort();
    void displayResults() const;

private:
    void sortVector();
    void sortList();
    template <typename T>
    void mergeInsertSort(T& container);
    std::vector<size_t> generateJacobsthalSequence(size_t n);
    bool isPositiveInteger(const std::string& s) const;
};

#endif