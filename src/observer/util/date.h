#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "common/rc.h"
#include "sql/parser/parse_defs.h"

inline bool is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0 ) || year % 400 == 0;
}

inline RC string_to_date(const std::string str, int32_t &date)
{
    std::istringstream iss(str);
    std::string token;
    std::vector<int> components;

    // Tokenize the string
    while (std::getline(iss, token, '-')) {
        try {
            components.push_back(std::stoi(token));
        } catch (const std::invalid_argument& e) {
            return RC::INVALID_ARGUMENT;
        }
    }
    
    if (components.size() != 3) {
        return RC::INVALID_ARGUMENT;
    }

    
    
    int year = components[0];
    int month = components[1];
    int day = components[2];;

    //validate
    if(year < 1900 || year > 9999 ||
      (month <= 0 || month > 12) ||
      (day <= 0 || day > 31)){
        return RC::INVALID_ARGUMENT;
    }

    int max_day_in_month[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int max_day = max_day_in_month[month - 1];

    if(day > max_day){
        return RC::INVALID_ARGUMENT;
    }

    if(month == 2 && !is_leap_year(year) && day > 28){
        return RC::INVALID_ARGUMENT;
    }

    date = year * 10000 + month * 100 + day;
    return RC::SUCCESS;
}

inline std::string date_to_string(int32_t date)
{
    int year = date / 10000;
    int month = (date % 10000) / 100;
    int day = date % 100;
    std::stringstream ss;
    ss << year << "-" << std::setw(2) << std::setfill('0') << month << "-" << std::setw(2) << std::setfill('0') << day;
    return ss.str();
}