// Autor: Adam Czubak
// Implementacja metod i operatorów klasy.

#include "investment.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include "check_availability_of_current.h"

Investment::Investment(double funds,
                       double interest_rate,
                       unsigned int years,
                       bool tax_state,
                       unsigned int tax_rate,
                       unsigned int capitalization_number_per_year,
                       std::string investment_current) : funds(funds),
                                                                 interest_rate(interest_rate),
                                                                 years(years),
                                                                 tax_state(tax_state),
                                                                 tax_rate(tax_rate),
                                                                 capitalization_number_per_year(capitalization_number_per_year),
                                                                 investment_current(investment_current){}

double Investment::check_funds()
{
    return funds;
}

void Investment::change_account_state(const double new_funds)
{
    funds = trunc(new_funds * 100) / 100;
}

void Investment::add_funds(const double new_funds)
{
    funds += trunc(new_funds * 100) / 100;
}

double Investment::get_interest_rate()
{
    return (trunc(interest_rate * 100)) / 100;
}

void Investment::change_interest_rate(const double new_interest_rate)
{
    if (new_interest_rate >= 1 && new_interest_rate <= 100)
        interest_rate = new_interest_rate;
    else
        throw std::out_of_range("Interest rate must be between 1 and 100!");
    
}

unsigned int Investment::get_years()
{
    return years;
}

void Investment::set_years(const unsigned int new_years)
{
    if (new_years >= 1)
        years = new_years;
    else
        throw std::logic_error("Years cannot be zero!");
}

bool Investment::get_tax_state()
{
    return tax_state;
}

void Investment::set_tax_state(const bool new_tax_state)
{
    tax_state = new_tax_state;
}

unsigned int Investment::get_tax_rate()
{
    return tax_rate;
}

void Investment::set_tax_rate(const unsigned int new_tax_rate)
{
    tax_rate = new_tax_rate;
}

unsigned int Investment::get_capitalization_number_per_year()
{
    return capitalization_number_per_year;
}

void Investment::set_capitalization_number_per_year(const unsigned int new_capitalization_number)
{
    capitalization_number_per_year = new_capitalization_number;
}

std::string Investment::get_investment_current()
{
    return investment_current;
}

void Investment::set_investment_current(std::string new_investment_current)
{
    bool founded_current = check_availability_of_current(new_investment_current);
    if (founded_current == true)
        investment_current = new_investment_current;
    else
        throw std::invalid_argument("This current is not available!");
}

double Investment::estimate_profits(const double rate_of_interest, const unsigned int years_number, const bool taxes_state, unsigned int taxes_rate, const unsigned int capitalization)
{
    if (taxes_state == false)
        taxes_rate = 0;
    double estimated_profits;
    estimated_profits = funds * pow(1 + rate_of_interest / (
        100 * capitalization), capitalization * years_number) - funds;
    estimated_profits = trunc((estimated_profits - estimated_profits * taxes_rate / 100) * 100) / 100;
    return estimated_profits;
}

double Investment::convert_current(std::string new_current, const double current_conversion_rate)
{
    bool founded_current = check_availability_of_current(new_current);
    if (founded_current == true)
    {
        if (new_current == investment_current)
            throw std::logic_error("Resulting current cannot be the same as the present one!");
        else
        {
            investment_current = new_current;
            funds = (funds * (trunc(current_conversion_rate * 100))) / 100;
        }
    }
    else
        throw std::invalid_argument("This current is not available!");
    return funds;
}

bool Investment::operator==(const Investment& investment_to_check) const 
{
	return (funds == investment_to_check.funds) && 
           (interest_rate == investment_to_check.interest_rate) &&
           (years == investment_to_check.years) &&
           (tax_state == investment_to_check.tax_state) &&
           (tax_rate == investment_to_check.tax_rate) &&
           (capitalization_number_per_year == investment_to_check.capitalization_number_per_year) &&
           (investment_current == investment_to_check.investment_current);
}

Investment& Investment::operator++(int)
{
    funds += 100;
    return *this;
}

Investment& Investment::operator--(int)
{
    funds -= 100;
    return *this;
}

Investment& Investment::operator+=(const Investment& second_investment)
{
    funds += second_investment.funds;
    interest_rate += second_investment.interest_rate;
    years += second_investment.years;
    tax_rate += second_investment.tax_rate;
    capitalization_number_per_year += second_investment.capitalization_number_per_year;
    return *this;
}

Investment& Investment::operator-=(const Investment& second_investment)
{
    funds -= second_investment.funds;
    interest_rate -= second_investment.interest_rate;
    years -= second_investment.years;
    tax_rate -= second_investment.tax_rate;
    capitalization_number_per_year -= second_investment.capitalization_number_per_year;
    return *this;
}

Investment& Investment::operator*=(const Investment& second_investment)
{
    funds *= second_investment.funds;
    interest_rate *= second_investment.interest_rate;
    years *= second_investment.years;
    tax_rate *= second_investment.tax_rate;
    capitalization_number_per_year *= second_investment.capitalization_number_per_year;
    return *this;
}

Investment& Investment::operator/=(const Investment& second_investment)
{
    funds /= second_investment.funds;
    interest_rate /= second_investment.interest_rate;
    years /= second_investment.years;
    tax_rate /= second_investment.tax_rate;
    capitalization_number_per_year /= second_investment.capitalization_number_per_year;
    return *this;
}

Investment Investment::operator+(const Investment& second_investment) const
{
    Investment obj = *this;
    obj.funds += second_investment.funds;
    obj.interest_rate += second_investment.interest_rate;
    obj.years += second_investment.years;
    obj.tax_rate += second_investment.tax_rate;
    obj.capitalization_number_per_year += second_investment.capitalization_number_per_year;
    return obj;
}

Investment Investment::operator-(const Investment& second_investment) const
{
    Investment obj = *this;
    obj.funds -= second_investment.funds;
    obj.interest_rate -= second_investment.interest_rate;
    obj.years -= second_investment.years;
    obj.tax_rate -= second_investment.tax_rate;
    obj.capitalization_number_per_year -= second_investment.capitalization_number_per_year;
    return obj;
}

Investment Investment::operator*(const Investment& second_investment) const
{
    Investment obj = *this;
    obj.funds *= second_investment.funds;
    obj.interest_rate *= second_investment.interest_rate;
    obj.years *= second_investment.years;
    obj.tax_rate *= second_investment.tax_rate;
    obj.capitalization_number_per_year *= second_investment.capitalization_number_per_year;
    return obj;
}

Investment Investment::operator/(const Investment& second_investment) const
{
    Investment obj = *this;
    obj.funds /= second_investment.funds;
    obj.interest_rate /= second_investment.interest_rate;
    obj.years /= second_investment.years;
    obj.tax_rate /= second_investment.tax_rate;
    obj.capitalization_number_per_year /= second_investment.capitalization_number_per_year;
    return obj;
}

bool Investment::operator!=(const Investment& second_investment) const
{
    return !(*this == second_investment);
}

bool Investment::operator<(const Investment& investment_to_check) const 
{
	return (funds < investment_to_check.funds) && 
           (interest_rate < investment_to_check.interest_rate) &&
           (years < investment_to_check.years) &&
           (tax_rate < investment_to_check.tax_rate) &&
           (capitalization_number_per_year < investment_to_check.capitalization_number_per_year);
}

bool Investment::operator>(const Investment& investment_to_check) const 
{
	return (funds> investment_to_check.funds) && 
           (interest_rate> investment_to_check.interest_rate) &&
           (years> investment_to_check.years) &&
           (tax_rate> investment_to_check.tax_rate) &&
           (capitalization_number_per_year> investment_to_check.capitalization_number_per_year);
}

bool Investment::operator<=(const Investment& investment_to_check) const 
{
	return (funds<= investment_to_check.funds) && 
           (interest_rate<= investment_to_check.interest_rate) &&
           (years<= investment_to_check.years) &&
           (tax_rate<= investment_to_check.tax_rate) &&
           (capitalization_number_per_year<= investment_to_check.capitalization_number_per_year);
}

bool Investment::operator>=(const Investment& investment_to_check) const 
{
	return (funds >= investment_to_check.funds) && 
           (interest_rate >= investment_to_check.interest_rate) &&
           (years >= investment_to_check.years) &&
           (tax_rate >= investment_to_check.tax_rate) &&
           (capitalization_number_per_year >= investment_to_check.capitalization_number_per_year);
}

std::ostream& operator<<(std::ostream& os, Investment& investment)
{
    os << "Funds: " << investment.funds << std::endl << "Interest rate: " << investment.interest_rate << std::endl << "Years: " << investment.years << std:: endl 
    << "Tax state: " << investment.tax_state << std::endl << "Tax rate: " << investment.tax_rate << std::endl << "Capitalization number per year: "
    << investment.capitalization_number_per_year << std::endl << "Investment current: " << investment.investment_current << std::endl;
    return os;
}