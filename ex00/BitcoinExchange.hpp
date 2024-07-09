#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <stdexcept>

class BitcoinExchange {
private:
    std::map<std::string, double> exchangeRates;

public:
    BitcoinExchange(const std::string& databaseFile);
    void processInput(const std::string& inputFile);

private:
    void loadDatabase(const std::string& filename);
    double getExchangeRate(const std::string& date);
    bool isValidDate(const std::string& date);
    bool isValidValue(double value);
    void printExchange(const std::string& date, double value, double rate);
};

#endif // BITCOINEXCHANGE_HPP