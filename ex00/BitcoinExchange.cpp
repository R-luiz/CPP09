#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>

bool BitcoinExchange::isValidDate(const std::string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31) return false;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return day <= 30;
    } else if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        return day <= (isLeapYear ? 29 : 28);
    }

    return true;
}


BitcoinExchange::BitcoinExchange(const std::string& databaseFile) {
    loadDatabase(databaseFile);
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open database file");
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        std::string rate;

        if (std::getline(iss, date, ',') && std::getline(iss, rate)) {
            if (isValidDate(date)) {
                exchangeRates[date] = std::atof(rate.c_str());
            }
        }
    }
}

void BitcoinExchange::processInput(const std::string& inputFile) {
    std::ifstream file(inputFile.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open input file");
    }

    std::string line;
    std::getline(file, line); // Skip header line

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        std::string valueStr;

        if (std::getline(iss, date, ',') && std::getline(iss, valueStr)) {
            date.erase(0, date.find_first_not_of(" \t"));
            date.erase(date.find_last_not_of(" \t") + 1);
            valueStr.erase(0, valueStr.find_first_not_of(" \t"));
            valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

            if (!isValidDate(date)) {
                std::cout << "Error: bad input => " << date << std::endl;
                continue;
            }

            double value = std::atof(valueStr.c_str());
            if (!isValidValue(value)) {
                if (value < 0) {
                    std::cout << "Error: not a positive number." << std::endl;
                } else {
                    std::cout << "Error: too large a number." << std::endl;
                }
                continue;
            }

            double rate = getExchangeRate(date);
            printExchange(date, value, rate);
        } else {
            std::cout << "Error: bad input => " << line << std::endl;
        }
    }
}

double BitcoinExchange::getExchangeRate(const std::string& date) {
    std::map<std::string, double>::iterator it = exchangeRates.lower_bound(date);
    if (it != exchangeRates.begin() && it->first != date) {
        --it;
    }
    return it->second;
}

bool BitcoinExchange::isValidValue(double value) {
    return value >= 0 && value <= 1000;
}

void BitcoinExchange::printExchange(const std::string& date, double value, double rate) {
    std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
}
