// Autor: Adam Czubak
// Wydzielona funkcja sprawdzająca dostępność danej waluty oraz umożliwiająca jej wprowadzanie z małych liter.

#ifndef CHECK_AVAILABILITY_OF_CURRENT_H
#define CHECK_AVAILABILITY_OF_CURRENT_H
#include <iostream>
#include <vector>
#include <algorithm>

bool check_availability_of_current(std::string & new_investment_current_check)
{
    std::vector<std::string> currents{"EUR", "USD", "CHF", "GBP", "PLN"};
    std::transform(new_investment_current_check.begin(), new_investment_current_check.end(), new_investment_current_check.begin(), ::toupper);
    auto founded_current_index = std::find(currents.begin(), currents.end(), new_investment_current_check);
    if (founded_current_index != currents.end())
        return true;
    else
        return false;
}

#endif