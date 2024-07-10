#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN {
private:
    std::stack<int> stack;

public:
    RPN();
    int evaluate(const std::string& expression);

private:
    bool isOperator(const std::string& token);
    int performOperation(int a, int b, const std::string& op);
};

#endif