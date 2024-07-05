// BitcoinExchange.hpp
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, double> database;
    void loadDatabase(const std::string& dbFile);
    double getExchangeRate(const std::string& date);
public:
    BitcoinExchange(const std::string& dbFile);
    void processInputFile(const std::string& inputFile);

};

#endif