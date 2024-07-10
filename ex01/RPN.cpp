#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <cstdlib>

RPN::RPN() {}

int RPN::evaluate(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (isOperator(token)) {
            if (stack.size() < 2) {
                throw std::runtime_error("Invalid expression");
            }
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            stack.push(performOperation(a, b, token));
        } else {
            char* endptr;
            long num = std::strtol(token.c_str(), &endptr, 10);
            if (*endptr != '\0' || num < 0 || num > 9) {
                throw std::runtime_error("Number out of range");
            }
            stack.push(static_cast<int>(num));
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }
    return stack.top();
}

bool RPN::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPN::performOperation(int a, int b, const std::string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    throw std::runtime_error("Unknown operator");
}